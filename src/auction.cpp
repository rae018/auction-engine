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
#include <algorithm>
#include <stdint.h>

namespace auction_engine {

bool Auction::isRegistered(std::unique_ptr<User>& user) {
  std::vector<std::unique_ptr<User>>::iterator it = std::find(users.begin(),
      users.end(), user);
  if (it != users.end())
    return true;
  else
    return false;
}

bool Auction::isRegistered(Item& item) {
  std::vector<Item*>::iterator it = std::find(items.begin(), items.end(),
      &item);
  if (it != items.end())
    return true;
  else
    return false;
}

bool Auction::isOpen(Item& item) {
  std::vector<Item*>::iterator it = std::find(open_items.begin(),
      open_items.end(), &item);
  if (it != open_items.end())
    return true;
  else
    return false;
}

Status Auction::addItem(std::string name, uint32_t starting_value) {
  for (Item* item: items) {
    if (name == item->getName()) {
      return error::NameTaken("An item with name \"", 
          name, "\"already exists.");
    }
  }

  // Create and add item
  Item new_item(*this, item_id_counter++, name, starting_value);
  items.push_back(&new_item);

  return Status();
}

Status Auction::addUser(std::string name, uint32_t funds) {
  for (auto const& user: users) {
    if (name == user->getName()) {
      return error::NameTaken("A user with name \"",
          name, "\"already exists.");
    }
  }

  // Create and add user
  //User* new_user = new User(*this, user_id_counter++, name, funds);
  //std::shared_ptr<User> new_user = std::make_shared<User>(*this, 
  //    user_id_counter++, name, funds);
  std::unique_ptr<User> new_user(new User(*this, user_id_counter++, name,
      funds));
  users.push_back(std::move(new_user));

  return Status();
}

Status Auction::openItemForBidding(Item& item) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isRegistered(item)) {
    return error::NotFound("Item \"",
        item.getName(), "\" is not registered in the auction.");
  }

  // Check if item is sold, return ITEM_UNAVAILABLE if not
  if (item.isSold()) {
    return error::ItemUnavailable("Item \"",
        item.getName(), "\" has been sold.");
  }

  // Check if item is already open, if not add it.
  if (!isOpen(item))
    open_items.push_back(&item);

  return Status();
}

Status Auction::closeItemForBidding(Item& item, bool sell) {
  // Check if item is registered, return NOT_FOUND if not
  if (!isRegistered(item)) {
    return error::NotFound("Item \"",
        item.getName(), "\" is not registered in the auction.");
  }

  // If item is open, find it in open items, sell it, and close it
  if (isOpen(item)) {
    std::vector<Item*>::iterator it = std::find(open_items.begin(),
        open_items.end(), &item);
    open_items.erase(it);
  } else {
    // Item is closed. Return error code if trying to sell a sold item
    if (sell && item.isSold()) {
      return error::ItemUnavailable("Item \"",
          item.getName(), "\" has been sold.");
    }
  }

  // Item is not sold. Sell if specified.
  if (sell) {
    item.sell();
    revenue += item.getCurrentBid()->value;
  }

  return Status();
}

}  // namespace auction_engine

