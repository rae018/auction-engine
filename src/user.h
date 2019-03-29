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

#include <string>
#include <vector>
#include <stdint.h>
#include <map>

#include "bid.h"
#include "item.h"
#include "auction.h"

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
  
  /// Return all of the user's bids.
  const std::vector<const Bid*> getBids() const;

  /// Return the user's available funds.
  uint32_t getAvailableFunds() const { return available_funds; }

  /// Return the user's total funds.
  uint32_t getTotalFunds() const { return funds; }

  /// Return all items the user has bid on.
  const std::vector<uint32_t> getItemsBidOn() const;

  /// Returh all items the user has won.
  const std::vector<uint32_t> getItemsWon() const { return items_won; }
  
  /**
   * \brief Returns the value of the users highest bid on an item
   * 
   * \param item_id
   *    The ID of the \c Item for which to get the highest bid value.
   *
   * \return The highest bid value if the user has placed a bid on the passed
   * item, 0 otherwise.
   */
  uint32_t getBidValueOnItem(uint32_t item_id) const;

  /**
   * Checks if the user has already bid on a item.
   *
   * \param item_id
   *    The ID of the \c Item to be checked.
   *
   * \return \c true if the user has bid on this item, \c false otherwise.
   */
  bool alreadyBidOnItem(uint32_t item_id) const {
    return bids_placed.count(item_id);
  }

  /**
   * \brief Add a bid to the user's placed bids.
   *
   * This adds a bid to the user's \c placed_bids map. This map is indexed by
   * item IDs and the values are all bids the user has placed on that item.
   *
   * \param bid
   *    The bid to add.
   */
  void addBid(const Bid& bid);

  void reportBidResult(uint32_t item_id, bool won);

protected:
  /// The \c Auction this user is a part of.
  const Auction& auction;
  /// Id of user.
  const uint32_t id;
  /// Name of user.
  std::string name;
  /// Total funds of the user.
  uint32_t funds;
  /// Funds available. This is the total funds minus any standing bids.
  uint32_t available_funds;
  /// \c Bids the user has placed, indexed by item id.
  std::map<uint32_t, std::vector<const Bid*>> bids_placed;
  /// The \c Items this user has won.
  std::vector<uint32_t> items_won;
};
}  // namespace auction_engine
