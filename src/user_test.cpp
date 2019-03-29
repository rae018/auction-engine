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
#include <error.h>
#include <item.h>
#include <print.h>
#include <status.h>
#include <auction.h>
#include <string>
#include <memory>
#include <user.h>
#include <iostream>
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
  uint32_t user_id = 16;
  std::string user_name = "UserName";
  uint32_t funds = 100;
  auction_engine::Auction auction; 

  std::cout << "Creating User object...";
  std::unique_ptr<auction_engine::User> user(new auction_engine::User(
      auction,
      user_id,
      user_name));
  user.reset(new auction_engine::User(
      auction,
      user_id,
      user_name,
      funds));
  std::cout << "User object initialized" << std::endl;

  printTest("Testing User::getId()...");
  printTestResult(user->getId() == user_id);

  printTest("Testing User::getName()...");
  printTestResult(user->getName() == user_name);

  printTest("Testing User::getTotalFunds()...");
  printTestResult(user->getTotalFunds() == funds);

  uint32_t item_id = 71;
  std::string item_name = "Ficus";
  uint32_t starting_value = 30;
  std::unique_ptr<auction_engine::Item> item(new auction_engine::Item(
      auction,
      item_id,
      item_name,
      starting_value));

  printTest("Testing User::addBid()...");
  uint32_t bid_value = 212;
  uint32_t bid_number = 9;
  const auction_engine::Bid bid(bid_value, user_id, item_id, bid_number);
  user->addBid(bid);
  printTestResult(user->getBids().size() == 1);


  return 0;
}
