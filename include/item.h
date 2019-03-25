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

#include <bid.h>
#include <user.h>
#include <auction.h>
#include <string>
#include <vector>
#include <stdint.h>

namespace auction_engine {

/* Forward Declarations */
struct Bid;
class User;
class Auction;

/**
 * \brief Item class.
 *
 * This class stores information related to a single item in the auction.
 */
class Item {
public:
  Item(Auction& auction, uint32_t id, std::string name, 
      uint32_t starting_value=0)
      : auction(auction), id(id), name(name), starting_value(starting_value) {}

  /// Return all bids placed on the item.
  std::vector<Bid*> getBids() const { return bids; }

  /// Return the item's id.
  const uint32_t getId() const { return id; }

  /// Return the item's name.
  const std::string getName() const { return name; }

  /// Return whether the item has sold or not.
  bool isSold() const { return sold; }

  /// Mark the item as sold.
  void sell() { sold = true; }

  /// Return the current bid on the item.
  Bid* getCurrentBid() const { 
    if (bids.back())
      return bids.back();
    else
      return nullptr;
  }

  /// Return the starting value of the item.
  const uint32_t getStartingValue() const { return starting_value; }

  /**
   * \brief Adds a bid to the item. Assume \c bid is a valid bid.
   *
   * \param Bid
   *    The bid to place on the item 
   */
  void addBid(Bid& bid) { bids.push_back(&bid); }

protected:
  const uint32_t id;          ///< Id of item.
  std::string name;           ///< Name of item.
  std::vector<Bid*> bids;     ///< All bids placed on the item.
  uint32_t starting_value;    ///< Starting value of item.
  bool sold;                  ///< Whether the item is sold or not.
  Auction& auction;           ///< The \c Auction this item is a part of.
};
}  // namespace auction_engine
