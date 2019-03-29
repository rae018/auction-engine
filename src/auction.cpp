/* Copyright 2019 Reed Evans. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <bid.h>
#include <auction.h>
#include <item.h>
#include <user.h>
#include <error.h>
#include <status.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <stdint.h>

namespace auction_engine {

std::vector<uint32_t> const Auction::getItems() const {
  std::vector<uint32_t> item_id_vec;
  for (const auto& kv: items)
    item_id_vec.push_back(kv.first);
  return item_id_vec;
}

std::vector<uint32_t> const Auction::getUsers() const {
  std::vector<uint32_t> user_id_vec;
  for (const auto& kv: users)
    user_id_vec.push_back(kv.first);
  return user_id_vec;
}

bool Auction::isItemRegistered(uint32_t item_id) const {
  return items.count(item_id);

}

bool Auction::isUserRegistered(uint32_t user_id) const {
  return users.count(user_id);
}

bool Auction::isOpen(uint32_t item_id) const {
  return std::binary_search(open_items.cbegin(), open_items.cend(), item_id);
}

bool Auction::isSold(uint32_t item_id) const {
  return std::binary_search(sold_items.cbegin(), sold_items.cend(), item_id);
}

Status Auction::getItem(uint32_t item_id, const Item*& item) const {
  if (isItemRegistered(item_id)) {
    item = items.at(item_id).get();
    return Status::OK();
  } else {
    return error::NotFound(
        "Item ID ",
        item_id,
        "is not registered in the auction.");
  }
}

Status Auction::getUser(uint32_t user_id, const User*& user) const {
  if (isUserRegistered(user_id)) {
    user = users.at(user_id).get();
    return Status::OK();
  } else {
    return error::NotFound(
        "User ID ",
        user_id, 
        "is not registered in the auction.");
  }
}

Status Auction::addItem(std::string name, uint32_t starting_value) {
  for (const auto& kv: items) {
    if (name == kv.second->getName()) {
      return error::NameTaken(
          "An item with name \"", 
          name,
          "\"already exists.");
    }
  }

  // Create and add item
  items[item_id_counter] = std::make_unique<Item>(*this, item_id_counter,
      name, starting_value);
  item_id_counter++;

  return Status::OK();
}

Status Auction::addUser(std::string name, uint32_t funds) {
  for (const auto& kv: users) {
    if (name == kv.second->getName()) {
      return error::NameTaken(
          "A user with name \"",
          name,
          "\"already exists.");
    }
  }

  // Create and add user
  users[user_id_counter] = std::make_unique<User>(*this, user_id_counter,
      name, funds);
  user_id_counter++;

  return Status::OK();
}

Status Auction::openItem(uint32_t item_id) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isItemRegistered(item_id)) {
    return error::NotFound(
        "Item ",
        item_id,
        " is not registered in the auction.");
  }

  const Item* item = items.at(item_id).get();

  // Check if item is sold, return ITEM_UNAVAILABLE if not
  if (isSold(item_id)) {
    return error::ItemUnavailable(
        "Item \"",
        item->getName(),
        "\" has been sold.");
  }

  // Check if item is already open, if not add it.
  if (!isOpen(item_id)) {
    auto it = std::upper_bound(open_items.cbegin(), open_items.cend(), item_id);
    open_items.insert(it, item_id);

  }

  return Status::OK();
}

Status Auction::sellItem(uint32_t item_id) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isItemRegistered(item_id)) {
    return error::NotFound(
        "Item \"",
        item_id,
        "\" is not registered in the auction.");
  }

  const Item* item = items.at(item_id).get();

  // Check if item is sold, return ITEM_UNAVAILABLE if not
  if (isSold(item_id)) {
    return error::ItemUnavailable(
        "Item \"",
        item->getName(),
        "\" has been sold.");
  } 

  if (item->getBids().empty()) {
    return error::NoBid(
        "No bids have been placed on Item \"",
        item->getName(),
        "\".");
  }

  auto it = std::upper_bound(sold_items.cbegin(), sold_items.cend(), item_id);
  sold_items.insert(it, item_id);
  revenue += item->getCurrentValue();
  // TODO: subtract winning bid from users total funds
  // TODO: add losing bids back to users available funds
  std::vector<uint32_t> bidding_users = users_for_item.at(item_id);
  uint32_t winning_user = item->getCurrentBid()->user_id;
  for (auto it: bidding_users)
    users[it]->reportBidResult(item_id, it==winning_user);

  return Status::OK();
}

Status Auction::closeItem(uint32_t item_id, bool sell) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isItemRegistered(item_id)) {
    return error::NotFound(
        "Item \"",
        item_id,
        "\" is not registered in the auction.");
  }

  // If item is open, find it in open items, sell it, and close it
  if (isOpen(item_id)) {
    auto it = std::lower_bound(open_items.cbegin(), open_items.cend(), item_id);
    open_items.erase(it+1);
  } else {
    // Item is closed. Return error code if trying to sell a sold item
    if (sell && isSold(item_id)) {
      return error::ItemUnavailable(
          "Item \"",
          items.at(item_id)->getName(),
          "\" has been sold.");
    }
  }

  // Item is not sold. Sell if specified.
  if (sell)
    return sellItem(item_id); 
  else 
    return Status::OK();
}

Status Auction::placeBid(uint32_t item_id, uint32_t user_id, uint32_t value) {
  if (!isItemRegistered(item_id)) {
    return error::NotFound(
        "Item \"",
        item_id,
        "\" is not registered in the auction.");
  }

  if (!isUserRegistered(user_id)) {
    return error::NotFound(
        "User \"",
        user_id,
        "\" is not registered in the auction.");
  }

  Item* item = items.at(item_id).get();
  User* user = users.at(user_id).get();

  if (!isOpen(item_id)) {
    return error::ItemUnavailable(
        "Item \"",
        item->getName(),
        "\" is not currently open in the auction.");
  }

  if (isSold(item_id)) {
    return error::ItemUnavailable(
        "Item \"",
        item->getName(),
        "\" is already sold.");
  }

  // The amount the user can bid on this item is what they've already bid plus
  // their available funds i.e. they can up the bid by their available funds.
  if (value > user->getAvailableFunds() + user->getBidValueOnItem(item_id)) {
    return error::InsufficientFunds(
        "Attempted bid value ",
        value,
        " is greater than user's available funds.");
  }
  
  const uint32_t current_value = item->getCurrentValue();
  // The new bid must be strictly greater than the current bid, unless no bids 
  // have been made, in which case it can be greater than or equal to the 
  // starting value.
  if ((!item->getBids().empty() && value < current_value) ||
      value <= current_value) {
    return error::InvalidBid(
        "Attempted bid value ",
        value,
        " is not higher than the current value ",
        current_value, ".");
  }

  // If the user hasn't bid on the item yet, add them to the list.
  if (!user->getBidValueOnItem(item_id))
    users_for_item[item_id].push_back(user_id);

  const Bid* current_bid = item->getCurrentBid();
  uint16_t bid_number = current_bid ? current_bid->number+1 : 0;
  const Bid* bid = new Bid(value, user_id, item_id, bid_number);

  user->addBid(*bid);
  item->addBid(*bid);

  return Status::OK();
}
}  // namespace auction_engine

