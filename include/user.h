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
#include <string>
#include <vector>
#include <stdint.h>

/* Forward Declarations */
struct Bid;
class Item;

/**
 * \brief User class.
 * 
 * This class stores information related to a single user in the auction and
 * provides a function to bid on items.
 */
class User {
public:
  User(uint32_t id, std::string name, uint32_t funds=0)
      : id(id), name(name), funds(funds) {}

	/// Return the user's id.
	const uint32_t getId() const { return id; }

	/// Return the user's bids.
	std::vector<Bid*> getBids() const { return bids_placed; }

  /// Return all items the user has bid on.
  std::vector<Item*> getItemsBidOn() const { return items_bid_on; }

	/**
	 * \brief Place a bid on an item.
   *
   * \param item
   *    An \c Item object specifying the item to bid on.
   *
   * This places a bid on an item for a user. If the item is not registered in
   * the auction, if the item is not the currently open for bidding in the
   * auction, if the \c value passed is not higher than the current bid on
   * the item, of if the \c value passed is greater than the user's available
   * funds, an exception is thrown and the function returns \c false.
   *
   * \param value
   *    An \c uint32_t specifying the value of the bid. If the bid is successful
   *    this value will be subtracted from the user's \c funds.
   *
   * \return \c true if the bid was successfully placed, \c false otherwise.
   */
	bool placeBid(Item* item, uint32_t value);

protected:
  const uint32_t id;                ///< Id of user.
  std::string name;                 ///< Name of user.
  uint32_t funds;                   ///< Total funds available to the user. 
  std::vector<Bid*> bids_placed;     ///< Bids the user has placed.
  std::vector<Item*> items_bid_on;   ///< Items user has bid on.
};
