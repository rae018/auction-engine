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
  uint32_t id = 16;
  std::string name = "ItemName";
  uint32_t starting_value = 100;
  auction_engine::Auction auction; 

  std::cout << "Creating Item object...";
  std::unique_ptr<auction_engine::Item> item(new auction_engine::Item(
      auction,
      id,
      name));
  item.reset(new auction_engine::Item(
      auction,
      id,
      name,
      starting_value));
  std::cout << "Item object initialized" << std::endl;

  printTest("Testing Item::getId()...");
  printTestResult(item->getId() == id);

  printTest("Testing Item::getName()...");
  printTestResult(item->getName() == name);

  printTest("Testing Item::getStartingValue()...");
  printTestResult(item->getStartingValue() == starting_value);

  uint32_t bid_value = 212;
  uint32_t bid_user_id = 71;
  uint32_t bid_number = 9;
  const auction_engine::Bid bid(bid_value, bid_user_id, id, bid_number);

  printTest("Testing Item::addBid()...");
  item->addBid(bid);
  printTestResult(true);

  printTest("Testing Item::getBid()...");
  printTestResult(item->getCurrentBid()->item_id == id &&
                  item->getCurrentBid()->user_id == bid_user_id &&
                  item->getCurrentBid()->number == bid_number &&
                  item->getCurrentBid()->value == bid_value);

  printTest("Testing Item::getCurrentValue()...");
  printTestResult(item->getCurrentValue() == bid.value);

  return 0;
}
