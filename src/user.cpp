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

void User::addBid(const Bid& bid) {
  bids_placed.push_back(&bid);

  for (int i=bids_placed.size(); i>0; --i) {
    uint32_t cur_item_id = bids_placed[i-1]->item_id;

    const Item* cur_item, *bid_item;
    auction.getItem(cur_item_id, cur_item);
    auction.getItem(bid.item_id, bid_item);

    if (cur_item->getId() > bid_item->getId()) {
      bids_placed[i] = bids_placed[i-1];
    } else {
      bids_placed[i] = &bid;
      break;
    }
  }
}

void User::addItem(uint32_t item_id) {
  items_bid_on.push_back(item_id);

  for (int i=items_bid_on.size(); i>0; --i) {
    if (items_bid_on[i-1] > item_id) {
      items_bid_on[i] = items_bid_on[i-1];
    } else {
      items_bid_on[i] = item_id;
      break;
    }
  }
}
}  // namespace auction_engine

