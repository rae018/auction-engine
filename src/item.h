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

# pragma once

#include <string>
#include <vector>
#include <stdint.h>

#include "bid.h"
#include "auction.h"

namespace auction_engine {

/* Forward Declarations */
struct Bid;
class Auction;

/**
 * \brief Item class.
 *
 * This class stores information related to a single item in the auction.
 */
class Item {
public:
  Item(const Auction& auction, uint32_t id, std::string name, 
       uint32_t starting_value=0)
      : auction(auction),
        id(id),
        name(name),
        starting_value(starting_value) {}

  /// Return all bids placed on the item.
  std::vector<const Bid*> getBids() const { return bids; }

  /// Return the item's id.
  const uint32_t getId() const { return id; }

  /// Return the item's name.
  const std::string getName() const { return name; }

  /// Return the current bid on the item.
  const Bid* getCurrentBid() const { 
    return bids.empty() ? nullptr : bids.back();
  }

  /// Return the current value of the item.
  const uint32_t getCurrentValue() const;

  /// Return the starting value of the item.
  const uint32_t getStartingValue() const { return starting_value; }

  /**
   * \brief Adds a bid to the item. Assume \c bid is a valid bid.
   *
   * \param Bid
   *    The bid to place on the item 
   */
  void addBid(const Bid& bid) { bids.push_back(&bid); }

protected:
  /// The \c Auction this item is a part of.
  const Auction& auction;
  /// Id of item.
  const uint32_t id;
  /// Name of item.
  std::string name;
  /// All bids placed on the item.
  std::vector<const Bid*> bids;
  /// Starting value of item.
  uint32_t starting_value;
};
}  // namespace auction_engine
