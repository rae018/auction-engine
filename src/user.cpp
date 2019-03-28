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
#include <vector>
#include <stdint.h>

namespace auction_engine {

bool User::alreadyBidOnItem(uint32_t item_id) const {
  return std::binary_search(items_bid_on.cbegin(), items_bid_on.cend(),
                            item_id);
}

void User::addItem(uint32_t item_id) {
  auto it = std::upper_bound(items_bid_on.cbegin(), items_bid_on.cend(),
                             item_id);
  items_bid_on.insert(it, item_id);
}

void User::addBid(const Bid& bid) {
  auto it = std::upper_bound(bids_placed.cbegin(), bids_placed.cend(), &bid);
  bids_placed.insert(it, &bid);
}
}  // namespace auction_engine

