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
#include <stdint.h>

namespace auction_engine {

// TODO: Fill in all of these function defs

bool Auction::isRegistered(User& user) const {
  return true;
}

bool Auction::isRegistered(Item& item) const {
  return true;
}

bool Auction::isOpen(Item& item) const {
  return true;
}

Status Auction::addItem(std::string name, uint32_t starting_value) {
  return Status();
}

Status Auction::addUser(std::string name, uint32_t funds) {
  return Status();
}

Status openItemForBidding(Item& item) {
  return Status();
}

Status closeItemForBidding(Item& item, bool sell=false) {
  return Status();
}

}  // namespace auction_engine

