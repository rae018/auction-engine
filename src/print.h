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

#pragma once

#include <vector>

#include "bid.h"
#include "item.h"
#include "user.h"

namespace auction_engine {
namespace print {
  
void printBid(const Auction& auction, const Bid& bid);

void printItem(const Auction& auction, uint32_t item_id);

void printUser(const Auction& auction, uint32_t user_id);

void printBidList(const Auction& auction, const std::vector<const Bid*> bids);

void printItemList(const Auction& auction, const std::vector<uint32_t> item_ids);

void printUserList(const Auction& auction, const std::vector<uint32_t> user_ids);

}  // namespace print
}  // namespace auction_engine
