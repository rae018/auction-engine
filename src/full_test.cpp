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

#include <auction.h>
#include <bid.h>
#include <error.h>
#include <item.h>
#include <print.h>
#include <status.h>
#include <user.h>
#include <iostream>

int main() {
  /* Create Auction instance */
  auction_engine::Auction auction;

  /* Create and add users */
  std::vector<std::string> users = { "Alice", "Bob", "Carol", "Dean", "Edgar" };
  std::vector<uint32_t> funds = { 217, 492, 16, 0, 1024 };
  for (int i=0; i<users.size(); ++i) {
    auction.addUser(users[i], funds[i]);
    auction_engine::print::printUser(auction, i);
  }
  /* Print list */
  auction_engine::print::printUserList(auction, auction.getUsers());

  /* Try getting individual user */
  std::vector<uint32_t> user_ids = auction.getUsers();
  const auction_engine::User* alice;
  auction.getUser(user_ids[0], alice);
  auction_engine::print::printUser(auction, alice->getId());

  /* Create and add items */
  std::vector<std::string> items = { "Rug", "Sunflowers", "Cleansing Fire" };
  std::vector<uint32_t> starting_values = { 70, 1853, 99999 };
  for (int i=0; i<items.size(); ++i) {
    auction.addItem(items[i], starting_values[i]);
    auction_engine::print::printItem(auction, i);
  }
  /* Print list */
  auction_engine::print::printItemList(auction, auction.getItems());

  /* Try getting individual item */
  std::vector<uint32_t> item_ids = auction.getItems();
  const auction_engine::Item* rug;
  auction.getItem(item_ids[0], rug);

  return 0;
}
