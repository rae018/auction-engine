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

inline void printTest(std::string test) {                                           
  std::cout << std::left << std::setw(48) << std::setfill('.');                     
  std::cout << test;                                                                
}
inline void printTestResult(bool result) {                                          
  if (result) std::cout << "PASSED";                                                
  else std::cout << "FAILED";                                                       
  std::cout << std::endl;                                                           
                                                                                    
} 

int main() {
  /* Create Auction instance */
  auction_engine::Auction auction;

  /* Create and add users */
  printTest("Testing Auction::addUser()...");
  std::vector<std::string> users = { "Alice", "Bob", "Carol", "Dean", "Edgar" };
  std::vector<uint32_t> funds = { 16000, 4902, 792, 0, 1024 };
  for (int i=0; i<users.size(); ++i) {
    auction.addUser(users[i], funds[i]);
  }
  printTestResult(auction.getUsers().size() == 5);
  /* Print list */
  // auction_engine::print::printUserList(auction, auction.getUsers());
  // std::cout << std::endl;

  /* Try getting individual user */
  printTest("Testing Auction::getUser()...");
  std::vector<uint32_t> user_ids = auction.getUsers();
  const auction_engine::User* alice, *bob, *carol, *dean, *edgar;
  auction.getUser(user_ids[0], alice);
  auction.getUser(user_ids[1], bob);
  auction.getUser(user_ids[2], carol);
  auction.getUser(user_ids[3], dean);
  auction.getUser(user_ids[4], edgar);
  printTestResult(alice->getId() == user_ids[0] &&
                  alice->getTotalFunds() == funds[0] &&
                  alice->getName() == users[0]);
  // auction_engine::print::printUser(auction, alice->getId());

  /* Create and add items */
  printTest("Testing Auction::addItem()...");
  std::vector<std::string> items = { "Rug", "Sunflowers", "Ficus" };
  std::vector<uint32_t> starting_values = { 70, 1853, 120 };
  for (int i=0; i<items.size(); ++i) {
    auction.addItem(items[i], starting_values[i]);
  }
  printTestResult(auction.getItems().size() == 3);
  /* Print list */
  // auction_engine::print::printItemList(auction, auction.getItems());
  // std::cout << std::endl;

  /* Try getting individual item */
  printTest("Testing Auction::getItem()...");
  std::vector<uint32_t> item_ids = auction.getItems();
  const auction_engine::Item* rug, *sunflowers, *ficus;
  auction.getItem(item_ids[0], rug);
  auction.getItem(item_ids[1], sunflowers);
  auction.getItem(item_ids[2], ficus);
  printTestResult(ficus->getId() == item_ids[2] &&
                  ficus->getName() == items[2] &&
                  ficus->getStartingValue() == starting_values[2]);
  // auction_engine::print::printItem(auction, ficus->getId());

  printTest("Testing Auction::isUserRegistered()...");
  uint32_t max_user_id = user_ids.at(user_ids.size()-1);
  printTestResult(auction.isUserRegistered(user_ids.at(max_user_id)) && 
                  !auction.isUserRegistered(max_user_id+1));

  printTest("Testing Auction::isItemRegistered()...");
  uint32_t max_item_id = item_ids.at(item_ids.size()-1);
  printTestResult(auction.isItemRegistered(max_item_id) && 
                  !auction.isItemRegistered(max_item_id+1));

  /* Start Bidding */
  printTest("Testing Auction::isOpen()...");
  auction.openItem(ficus->getId());
  printTestResult(!auction.isOpen(rug->getId()) &&
                  auction.isOpen(ficus->getId()));

  auction_engine::Status status = auction.placeBid(
      ficus->getId(), 
      alice->getId(), 
      190);
  const auction_engine::Bid* cur_bid = ficus->getCurrentBid();
  if (!status.ok()) std::cout << status.error_message() << std::endl;
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  if (!status.ok()) std::cout << status.error_message() << std::endl;
  status = auction.placeBid(
      ficus->getId(),
      bob->getId(),
      300);
  if (!status.ok()) std::cout << status.error_message() << std::endl;
  status = auction.placeBid(
      ficus->getId(),
      dean->getId(),
      200);
  if (!status.ok()) std::cout << status.error_message() << std::endl;
  status = auction.placeBid(
      ficus->getId(),
      edgar->getId(),
      200);
  if (!status.ok()) std::cout << status.error_message() << std::endl;
  printTest("Testing Auction::placeBid()...");
  printTestResult(ficus->getBids().size() == 3); 
  auction_engine::print::printBidList(auction, ficus->getBids());

  /* Make a bunch of bids */
  status = auction.placeBid(
      rug->getId(),
      carol->getId(),
      100);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);
  status = auction.placeBid(
      ficus->getId(),
      carol->getId(),
      250);






  printTest("Testind Auction::sellItem()...");
  auction.sellItem(ficus->getId());
  printTestResult(auction.isSold(ficus->getId()) &&
                  auction.getRevenue() == ficus->getCurrentValue());

  printTest("Testing Auction::isSold()...");
  printTestResult(auction.isSold(ficus->getId()));

  return 0;
}
