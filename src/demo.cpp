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
#include <sstream>
#include <iomanip>

int main() {
  /* Create Auction instance */
  auction_engine::Auction auction;

  /* Create and add users */
  printf("[Creating users Alice, Bob, Carol, Dean, and Edgar...]\n");
  std::vector<std::string> users = { "Alice", "Bob", "Carol", "Dean", "Edgar" };
  std::vector<uint32_t> funds = { 16000, 4902, 792, 0, 1024 };
  for (int i=0; i<users.size(); ++i) {
    auction.addUser(users[i], funds[i]);
  }
  /* Print list */
  auction_engine::print::printUserList(auction, auction.getUsers());
  std::cout << std::endl;

  /* Create and add items */
  std::cout << "[ Creating items Rug, Sunflowers, Ficus, and Pineapple... ]"
            << std::endl;
  std::vector<std::string> items = { "Rug", "Sunflowers", "Ficus", 
                                     "pineapple" };
  std::vector<uint32_t> starting_values = { 70, 1853, 120, 60 };
  for (int i=0; i<items.size(); ++i) {
    auction.addItem(items[i], starting_values[i]);
  }
  /* Print list */
  auction_engine::print::printItemList(auction, auction.getItems());
  std::cout << std::endl;

  /* Get easy access to users */
  std::vector<uint32_t> user_ids = auction.getUsers();
  const auction_engine::User* alice, *bob, *carol, *dean, *edgar;
  auction.getUser(user_ids[0], alice);
  auction.getUser(user_ids[1], bob);
  auction.getUser(user_ids[2], carol);
  auction.getUser(user_ids[3], dean);
  auction.getUser(user_ids[4], edgar);

  /* Get easy access to items */
  std::vector<uint32_t> item_ids = auction.getItems();
  const auction_engine::Item* rug, *sunflowers, *ficus, *pineapple;
  auction.getItem(item_ids[0], rug);
  auction.getItem(item_ids[1], sunflowers);
  auction.getItem(item_ids[2], ficus);
  auction.getItem(item_ids[3], pineapple);

  /* Open items */
  std::cout << "[ Opening all items... ]" << std::endl;
  auction.openItem(rug->getId());
  auction.openItem(sunflowers->getId());
  auction.openItem(ficus->getId());
  auction.openItem(pineapple->getId());
  auction_engine::print::printItemList(auction, auction.getOpenItems());
  std::cout << std::endl;

  auction_engine::Status status = auction.placeBid(
      ficus->getId(), 
      alice->getId(), 
      190);
  const auction_engine::Bid* cur_bid = ficus->getCurrentBid();
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      ficus->getId(),
      bob->getId(),
      300);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  std::cout << "[ Make bid less than the user's total funds. Should return "
            << "an error. ]" << std::endl;
  auction_engine::print::printUser(auction, dean->getId());
  status = auction.placeBid(
      ficus->getId(),
      dean->getId(),
      200);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }
  
  std::cout << "[ Make bid less than the item's current value. Should return "
            << "an error. ]" << std::endl;
  auction_engine::print::printItem(auction, ficus->getId());
  status = auction.placeBid(
      ficus->getId(),
      edgar->getId(),
      200);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  std::cout << "[ Make bid on non-existant item. Should return an error. ]"
            << std::endl;
  status = auction.placeBid(
      50,
      alice->getId(),
      451);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  std::cout << "[ Make bid by non-existant user. Should return an error. ]"
            << std::endl;
  status = auction.placeBid(
      ficus->getId(),
      17,
      451);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      rug->getId(),
      carol->getId(),
      100);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }
  status = auction.placeBid(
      rug->getId(),
      bob->getId(),
      120);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      rug->getId(),
      alice->getId(),
      150);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      rug->getId(),
      edgar->getId(),
      180);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      sunflowers->getId(),
      bob->getId(),
      1900);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      sunflowers->getId(),
      alice->getId(),
      2000);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      rug->getId(),
      alice->getId(),
      250);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      rug->getId(),
      edgar->getId(),
      280);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      rug->getId(),
      carol->getId(),
      300);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      sunflowers->getId(),
      bob->getId(),
      2048);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  status = auction.placeBid(
      sunflowers->getId(),
      alice->getId(),
      2800);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  
  }

  std::cout << "[ Make bid greater than the user's available funds, but not "
            << "greater than their available funds. This should return an "
            << "error. ]" << std::endl;
  auction_engine::print::printUser(auction, carol->getId());
  status = auction.placeBid(
      pineapple->getId(),
      carol->getId(),
      300);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  std::cout << "[ Selling the ficus and sunflowers. The total funds of the "
            << "winners should decrease and the available funds of the losers "
            << "should increase by their respective bid values. ]" << std::endl;
  auction_engine::print::printUserList(auction, auction.getUsers());
  auction_engine::print::printBidList(auction, ficus->getBids());
  auction_engine::print::printBidList(auction, sunflowers->getBids());
  auction.sellItem(ficus->getId());
  auction.sellItem(sunflowers->getId());
  auction_engine::print::printUserList(auction, auction.getUsers());
  std::cout << std::endl;

  std::cout << "[ Make bid on sold item. This should return an error. ]"
            << std::endl;
  status = auction.placeBid(
      sunflowers->getId(),
      alice->getId(),
      2900);
  if (!status.ok()) {
    std::cout << "ERROR: " << status.error_message();
    std::cout << std::endl << std::endl;
  }

  return 0;
}
