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
#include <iomanip>
#include <iostream>

namespace auction_engine {

std::vector<uint32_t> const Auction::getItems() const {
  std::vector<uint32_t> item_id_vec;
  for (auto it=items.begin(); it!=items.end(); ++it)
    item_id_vec.push_back(it->first);
  return item_id_vec;
}

std::vector<uint32_t> const Auction::getUsers() const {
  std::vector<uint32_t> user_id_vec;
  for (auto it=users.begin(); it!=users.end(); ++it)
    user_id_vec.push_back(it->first);
  return user_id_vec;
}

bool Auction::isItemRegistered(uint32_t item_id) const {
  return items.count(item_id);

}

bool Auction::isUserRegistered(uint32_t user_id) const {
  return users.count(user_id);
}

bool Auction::isOpen(uint32_t item_id) const {
  std::vector<uint32_t>::const_iterator it = std::find(
      open_items.begin(), open_items.end(), item_id);
  return it != open_items.end();
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

Status Auction::openItemForBidding(uint32_t item_id) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isItemRegistered(item_id)) {
    return error::NotFound(
        "Item \"",
        item_id,
        "\" is not registered in the auction.");
  }

  // Check if item is sold, return ITEM_UNAVAILABLE if not
  if (items.at(item_id)->isSold()) {
    return error::ItemUnavailable(
        "Item \"",
        items.at(item_id)->getName(),
        "\" has been sold.");
  }

  // Check if item is already open, if not add it.
  if (!isOpen(item_id))
    open_items.push_back(item_id);

  return Status::OK();
}

Status Auction::closeItemForBidding(uint32_t item_id, bool sell) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isItemRegistered(item_id)) {
    return error::NotFound(
        "Item \"",
        item_id,
        "\" is not registered in the auction.");
  }

  // If item is open, find it in open items, sell it, and close it
  if (isOpen(item_id)) {
    std::vector<uint32_t>::iterator it = std::find(
        open_items.begin(), open_items.end(), item_id);
    open_items.erase(it);
  } else {
    // Item is closed. Return error code if trying to sell a sold item
    if (sell && items.at(item_id)->isSold()) {
      return error::ItemUnavailable(
          "Item \"",
          items.at(item_id)->getName(),
          "\" has been sold.");
    }
  }

  // Item is not sold. Sell if specified.
  if (sell) {
    items.at(item_id)->sell();
    revenue += items.at(item_id)->getCurrentBid()->value;
  }

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

  if (value > user->getFunds()) {
    return error::InsufficientFunds(
        "Attempted bid value ",
        value,
        " is greater than user's available funds.");
  }

  const Bid* current_bid = item->getCurrentBid();

  if (current_bid && value <= current_bid->value) {
    return error::InvalidBid(
        "Attempted bid value ",
        value,
        " is not higher than the current bid value ",
        current_bid->value, " .");
  } else if (value < item->getStartingValue()) {
    return error::InvalidBid(
        "Attempted bid value ",
        value,
        " is not higher than the starting bid value ",
        item->getStartingValue(), " .");
  }

  Bid bid(value, user_id, item_id);
  user->addBid(bid);
  user->addItem(item_id);
  item->addBid(bid);

  return Status::OK();
}
}  // namespace auction_engine

