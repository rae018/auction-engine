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

#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <iomanip>

#include "bid.h"
#include "auction.h"
#include "item.h"
#include "user.h"

/*
 * =======================================================================
 *   WARNING    WARNING    WARNING    WARNING    WARNING    WARNING
 * =======================================================================
 *   These functions will only print valid values correctly and do no
 *   error checking whatsoever. If you send it garbage it will print 
 *   garbage. 
 * =======================================================================
 */

namespace auction_engine {
namespace print {

const int kEntryWidth = 16;

template<typename T>
inline void printEntry(T t) {
  std::cout << std::left << std::setw(kEntryWidth) << std::setfill(' ') << t;
}
inline void printLine(const int num_fields) {
  for (int i=0; i<num_fields; ++i) {
    std::cout << std::setw(kEntryWidth) << std::setfill('-') << "";
  }
  std::cout << std::endl;
}

void printBid(const Auction& auction, const Bid& bid) {
  const Item* item;
  auction.getItem(bid.item_id, item);
  const User* user;
  auction.getUser(bid.user_id, user);
  std::cout << "{ BID" << std::endl;
  std::cout << "  Item: " << item->getName() << std::endl;
  std::cout << "  Number: " << bid.number << std::endl;
  std::cout << "  Owner: " << user->getName() << std::endl;
  std::cout << "  Value: " << bid.value << std::endl;
  std::cout << "}" << std::endl;
}

void printItem(const Auction& auction, const uint32_t item_id) {
  const Item* item;
  auction.getItem(item_id, item);
  std::cout << "{ ITEM" << std::endl;
  std::cout << "  Name: " << item->getName() << std::endl;
  std::cout << "  ID: " << item->getId() << std::endl;
  std::cout << "  Number of bids: " << item->getBids().size() << std::endl;
  std::cout << "  Current value: ";
  std::cout << item->getCurrentValue() << std::endl;
  std::cout << "}" << std::endl;
}

void printUser(const Auction& auction, const uint32_t user_id) {
  const User* user;
  auction.getUser(user_id, user);
  std::cout << "{ USER" << std::endl;
  std::cout << "  Name: " << user->getName() << std::endl;
  std::cout << "  ID: " << user->getId() << std::endl;
  std::cout << "  Total Funds: " << user->getTotalFunds() << std::endl;
  std::cout << "  Available Funds: " << user->getAvailableFunds() << std::endl;
  std::cout << "  Number of items bid on: " << user->getItemsBidOn().size() <<
      std::endl;
  std::cout << "}" << std::endl;
}

void printBidList(const Auction& auction, const std::vector<const Bid*> bids) {
  printEntry("Item Name");
  printEntry("Bid Number");
  printEntry("Placed By");
  printEntry("Value");
  std::cout << std::endl;
  printLine(4);
  for (const Bid* bid: bids) {
    const Item* item;
    auction.getItem(bid->item_id, item);
    const User* user;
    auction.getUser(bid->user_id, user);
    printEntry(item->getName());
    printEntry(bid->number);
    printEntry(user->getName());
    printEntry(bid->value);
    std::cout << std::endl;
  }
  printLine(4);
}

void printItemList(const Auction& auction,
                   const std::vector<uint32_t> item_ids) {
  printEntry("Item Name");
  printEntry("Item ID");
  printEntry("Current Value");
  printEntry("Sold?");
  std::cout << std::endl;
  printLine(4);
  for (auto const& item_id: item_ids) {
    const Item* item;
    auction.getItem(item_id, item);
    printEntry(item->getName());
    printEntry(item->getId());
    printEntry(item->getCurrentValue());
    auction.isSold(item->getId()) ? printEntry("Yes") : printEntry("No");
    std::cout << std::endl;
  }
  printLine(4);
}

void printUserList(const Auction& auction,
                   const std::vector<uint32_t> user_ids) {
  printEntry("User Name");
  printEntry("User ID");
  printEntry("Total Funds");
  printEntry("Avail. Funds");
  printEntry("# Items Bid On");
  std::cout << std::endl;
  printLine(5);
  for (auto const& user_id: user_ids) {
    const User* user;
    auction.getUser(user_id, user);
    printEntry(user->getName());
    printEntry(user->getId());
    printEntry(user->getTotalFunds());
    printEntry(user->getAvailableFunds());
    printEntry(user->getItemsBidOn().size());
    std::cout << std::endl;
  }
  printLine(5);
}
}  // namespace print
}  // namespace auction_engine
