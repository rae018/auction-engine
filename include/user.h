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

#include <bid.h>
#include <item.h>
#include <auction.h>
#include <string>
#include <vector>
#include <stdint.h>

namespace auction_engine {

/* Forward Declarations */
struct Bid;
class Item;
class Auction;

/**
 * \brief User class.
 * 
 * This class stores information related to a single user in the auction and
 * provides a function to bid on items.
 */
class User {
public:
  User(const Auction& auction, uint32_t id, std::string name, uint32_t funds=0)
      : auction(auction), id(id), name(name), funds(funds),
        available_funds(funds) {}
      
  /// Return the user's id.
  const uint32_t getId() const { return id; }

  /// Return the user's name.
  const std::string getName() const { return name; }
  
  /// Return the user's bids.
  const std::vector<const Bid*> getBids() const { return bids_placed; }

  /// Return the user's available funds.
  uint32_t getAvailableFunds() const { return funds; }

  /// Return the user's total funds.
  uint32_t getTotalFunds() const { return funds; }

  /// Return all items the user has bid on.
  std::vector<uint32_t> getItemsBidOn() const { return items_bid_on; }

  /**
   * Checks if the user has already bid on a item.
   *
   * \param item_id
   *    The ID of the \c Item to be checked.
   *
   * \return \c true if the user has bid on this item, \c false otherwise.
   */
  bool alreadyBidOnItem(uint32_t item_id) const;

  /**
   * \brief Add an item to the user's items bid on.
   *
   * This adds an item to the user's \c items_bid_on member. Items are ordered
   * such that they are ordered by their id.
   *
   * \param item
   *    The item to add.
   */
  void addItem(uint32_t item_id);

  /**
   * \brief Add a bid to the user's placed bids.
   *
   * This adds a bid to the user's \c placed_bids member. The bids are inserted
   * such that they are sorted by their item's id and bid value.
   *
   * \param bid
   *    The bid to add.
   */
  void addBid(const Bid& bid);

protected:
  /// Id of user.
  const uint32_t id;
  /// Name of user.
  std::string name;
  /// Total funds of the user.
  uint32_t funds;
  /// Funds available. This is the total funds minus any standing bids.
  uint32_t available_funds;
  /// Bids the user has placed.
  std::vector<const Bid*> bids_placed;
  /// \c Item IDs for the items the user has bid on.
  std::vector<uint32_t> items_bid_on;
  /// The \c Auction this user is a part of.
  const Auction& auction;           ///< The \c Auction this user is a part of.
};
}  // namespace auction_engine
