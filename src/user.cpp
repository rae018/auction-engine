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

#include <vector>
#include <stdint.h>
#include <map>

#include "bid.h"
#include "item.h"
#include "user.h"

namespace auction_engine {

const std::vector<uint32_t> User::getItemsBidOn() const {
  std::vector<uint32_t> items_bid_on;
  for (const auto& kv: bids_placed)
    items_bid_on.push_back(kv.first);
  return items_bid_on;
}

const std::vector<const Bid*> User::getBids() const { 
  std::vector<const Bid*> bids;
  for (const auto& kv: bids_placed)
    bids.insert(bids.cend(), kv.second.cbegin(), kv.second.cend());
  return bids;
}

uint32_t User::getBidValueOnItem(uint32_t item_id) const {
  if (bids_placed.count(item_id))
    return bids_placed.at(item_id).back()->value;
  else
    return 0;
}

void User::addBid(const Bid& bid) {
  if (bids_placed.count(bid.item_id)) {
    available_funds = available_funds - bid.value + \
                      bids_placed[bid.item_id].back()->value;
  } else {
    available_funds -= bid.value;
  }
  bids_placed[bid.item_id].push_back(&bid);
}

void User::reportBidResult(uint32_t item_id, bool won) {
  const Bid* bid = bids_placed.at(item_id).back();
  if (won) {
    funds -= bid->value;
    items_won.push_back(item_id);
  } else {
    available_funds += bid->value;
  }
}
}  // namespace auction_engine
