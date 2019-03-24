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
#include <item.h>
#include <user.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <iomanip>

namespace auction_engine {

namespace print {

const int entry_width = 16;

template<typename T>
inline void printEntry(T t) {
  std::cout << std::left << std::setw(entry_width) << std::setfill(' ') << t;
}

inline void printLine(const int num_fields) {
  for (int i=0; i<num_fields; ++i) {
    std::cout << std::setw(entry_width) << std::setfill('-');
  }
  std::cout << std::endl;
}


void printBid(Bid& bid) {
  std::cout << "{ Bid" << std::endl;
  std::cout << "Item: " << bid.item.getName() << std::endl;
  std::cout << "Number: " << bid.number << std::endl;
  std::cout << "Owner: " << bid.owner.getName() << std::endl;
  std::cout << "Value: " << bid.value << std::endl;
  std::cout << "}" << std::endl;
}

void printItem(Item& item) {
  std::cout << "{ Item" << std::endl;
  std::cout << "Name: " << item.getName() << std::endl;
  std::cout << "ID: " << item.getId() << std::endl;
  std::cout << "Number of bids: " << item.getBids().size() << std::endl;
  std::cout << "Current bid value: ";
  item.getCurrentBid() ? std::cout << item.getCurrentBid()->value
      : std::cout << item.getStartingValue();
  std::cout << std::endl;
  std::cout << "}" << std::endl;
}

void printUser(User& user) {
  std::cout << "{ User" << std::endl;
  std::cout << "Name: " << user.getName() << std::endl;
  std::cout << "ID: " << user.getId() << std::endl;
  std::cout << "Funds: " << user.getFunds() << std::endl;
  std::cout << "Number of items bid on: " << user.getItemsBidOn().size() <<
      std::endl;
  std::cout << "}" << std::endl;
}

void printBidList(std::vector<Bid*> bids) {
  printEntry("Item Name");
  printEntry("Bid Number");
  printEntry("Placed By");
  printEntry("Value");
  std::cout << std::endl;
  printLine(4);
  for (Bid* bid: bids) {
    printEntry(bid->item.getName());
    printEntry(bid->number);
    printEntry(bid->owner.getName());
    printEntry(bid->value);
    std::cout << std::endl;
  }
}

void printItemList(std::vector<Item*> items) {
  printEntry("Item Name");
  printEntry("Item ID");
  printEntry("Current Bid");
  printEntry("Sold?");
  std::cout << std::endl;
  printLine(4);
  for (Item* item: items) {
    printEntry(item->getName());
    printEntry(item->getId());
    printEntry(item->getCurrentBid()->value);
    item->isSold() ? printEntry("Yes") : printEntry("No");
    std::cout << std::endl;
  }
}

void printUserList(std::vector<User*> users) {
  printEntry("User Name");
  printEntry("User ID");
  printEntry("Funds");
  printEntry("Items Bid On");
  std::cout << std::endl;
  printLine(4);
  for (User* user: users) {
    printEntry(user->getName());
    printEntry(user->getId());
    printEntry(user->getFunds());
    printEntry(user->getItemsBidOn().size());
    std::cout << std::endl;
  }
}


}  // namespace print

}  // namespace auction_engine
