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
#include <status.h>
#include <item.h>
#include <user.h>
#include <string>
#include <vector>
#include <map>
#include <stdint.h>

namespace auction_engine {

/* Forward Declarations  */
struct Bid;
class User;
class Item;

/**
 * \brief Auction class
 *
 * This class stores high level information about an auction and provides
 * functionality 
 */
class Auction {
public:
  Auction() : item_id_counter(0), user_id_counter(0), revenue(0) {} 

  /// Return all items registered in the auction.
  std::vector<uint32_t> getItems();

  /// Return all items open in the auction.
  std::vector<uint32_t> const& getOpenItems() const { 
    return open_items; 
  }

  /// Returns \c true if \c item is registered in the auction, \c false 
  /// otherwise.
  bool isItemRegistered(uint32_t item_id);

  /// Returns \c true if \c user is registered with the auction, \c false
  /// otherwise.
  bool isUserRegistered(uint32_t user_id);

  /// Returns \c true if \c item is open in the auction, \c false otherwise.
  bool isOpen(uint32_t item_id);

  /// Return all users registered in the auction.
  std::vector<uint32_t> getUsers();

  /// Return a single user
  std::unique_ptr<User> const& getUser(uint32_t user_id) { return users[user_id]; }

  /// Return a single item
  std::unique_ptr<Item> const& getItem(uint32_t item_id) { return items[item_id]; }

  /**
   * \brief Add an item to the auction.
   *
   *  This registers a new \c Item in with auction. The item's \c name and 
   *  (optional) \c starting_value are passed as parameters. If the \c name 
   *  passed is already in use by another item in the auction, the return \c 
   *  Status will contain an error code and message. The item's \c id is 
   *  assigned using the class's \c item_id_counter. 
   *
   * \param name
   *    A \c string specifying the name of the item.
   *
   * \param starting_value
   *    An optional \c uint23_t specifying the value bidding will start at for 
   *    the item. Defaults to 0.
   *
   * \return \c Status containing error code and message.
   */
  Status addItem(std::string name, uint32_t starting_value=0);

  /**
   * \brief Add a user to the auction
   *
   * This registers a new \c User with the auction. The user's \c name and
   * (optional) \c funds are passed as parameters. If the \c name passed is
   * already in use by another user in the auction, the return \c Status will 
   * contain an error code and message. The user's \c id is assigned using the
   * class's \c user_id_counter. 
   *
   * \param name
   *    A \c string specifying the name of the user.
   *
   * \param funds
   *    An optional uint32_t specifying the amount of funds to initialize the
   *    user with. Defaults to 0.
   *
   * \return \c Status containing error code and message.
   */
  Status addUser(std::string name, uint32_t funds=0);

  /**
   * \brief Open a registered item for bidding.
   *
   * This opens a registered \c Item in the auction for bidding. Bids cannot be
   * placed on an item unless it is open. If the item is not registered in the
   * auction, or if the item has already been sold, 
   * the return \c Status will contain an error code and message. If the item is
   * already open, the function just returns with an OK status.
   *
   * \param item
   *    An \c Item to open for auction. 
   *
   * \return \c Status containing error code and message.
   */
  Status openItemForBidding(uint32_t item_id);

  /**
   * \brief Close an open item for bidding.
   *
   * This closes an open \c Item for bidding. If the item is not already open, 
   * the return \c Status will contain an error code and message.
   *
   * \param item
   *    An \c Item that is currently open to close for bidding. 
   *
   * \param sell
   *    An optional \c bool that specifies whether to mark the item sold upon
   *    closing or not. If the item is sold it's selling value is added to the
   *    auction revenue. Defaults to \c false.
   *
   * \return \c Status containing error code and message.
   */
  Status closeItemForBidding(uint32_t item_id, bool sell=false);
  
  /**
   * \brief Place a bid on an item.
   *
   * This places a bid on an item for a user. If the item is not registered in
   * the auction, if the item is not the currently open for bidding in the
   * auction, if the \c value passed is not higher than the current bid on
   * the item, of if the \c value passed is greater than the user's available
   * funds, the return \c Status will contain an error code and message.
   *
   * \param item_id
   *    The id of the item to bid on.
   *
   * \param user_id
   *    The id of the user placing the bid.
   *
   * \param value
   *    An \c uint32_t specifying the value of the bid. If the bid is successful
   *    this value will be subtracted from the user's \c funds.
   *
   * \return \c Status containing error code and message.
   */
  Status placeBid(uint32_t item_id, uint32_t user_id, uint32_t value);

protected:
  std::map<uint32_t, std::unique_ptr<Item>> items;  ///< Items registered in the auction.
  std::vector<uint32_t> open_items;       ///< Item IDs currently open for bidding.
  std::map<uint32_t, std::unique_ptr<User>> users;         ///< Users Registered in the auction.
  uint32_t item_id_counter;               ///< Counter for assigning item ids.
  uint32_t user_id_counter;               ///< Counter for assigning user ids.
  uint32_t revenue;                       ///< Total revenue of the auction.
  const int entry_width = 16;
};

}  // namespace auction_engine

