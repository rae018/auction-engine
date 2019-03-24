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
#include <error.h>
#include <status.h>
#include <string>
#include <vector>
#include <stdint.h>

namespace auction_engine {

void User::addBid(Bid& bid) {
  bids_placed.push_back(bids_placed.back());
  for (int i=bids_placed.size(); i>0; --i) {
    Item cur_item = bids_placed[i-1]->item;
    if (cur_item.getId() > bid.item.getId()) {
      bids_placed[i] = bids_placed[i-1];
    } else {
      bids_placed[i] = &bid;
      break;
    }
  }
}

void User::addItem(Item& item) {
  items_bid_on.push_back(items_bid_on.back());
  for (int i=items_bid_on.size(); i>0; --i) {
    if (items_bid_on[i-1]->getId() > item.getId()) {
      items_bid_on[i] = items_bid_on[i-1];
    } else {
      items_bid_on[i] = &item;
      break;
    }
  }
}


Status User::placeBid(Item& item, uint32_t value) {
  Bid* current_bid = item.getCurrentBid();

  if (value > funds) {
    return error::InsufficientFunds("Attempted bid value ",
        value, " is greater than user's available funds.");
  }

  if (!auction.isRegistered(item)) {
    return error::NotFound("Item ",
        item.getName(), " is not registered in the auction.");
  }

  if (!auction.isOpen(item)) {
    return error::ItemClosed("Item ",
        item.getName(), " is not currently open in the auction.");
  }

  if (current_bid && value <= current_bid->value) {
    return error::InvalidBid("Attempted bid value ",
        value, " is not higher than the current bid value ",
        current_bid->value, " .");
  } else if (value < item.getStartingValue()) {
    return error::InvalidBid("Attempted bid value ",
        value, " is not higher than the starting bid value ",
        item.getStartingValue(), " .");
  }
  
  // Create bid
  Bid bid(value, *this, item);

  // Add bid to user's placed bids, sorting by item id and bid value.
  addBid(bid);

  // Add item to user's items bid on
  addItem(item);

  // Place bid on item.
  item.addBid(bid);


  return Status();

}


}  // namespace auction_engine

