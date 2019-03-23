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
#include <user.h>
#include <string>
#include <vector>
#include <stdint.h>

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
  std::vector<Item*> getItems() const { return items; }

  /// Return all users registered in the auction.
  std::vector<User*> getUsers() const { return users; }

  /**
   * \brief Add an item to the auction.
   *
   *  This registers a new item in with auction. The item's \c name and 
   *  (optional) \c starting_value are passed as parameters. If the \c name 
   *  passed is already in use by another item in the auction, an exception is 
   *  thrown and the function returns \c false. The item's \c id is assigned 
   *  using the class's \c item_id_counter. 
   *
   * \param name
   *    A \c string specifying the name of the item.
   *
   * \param starting_value
   *    An optional \c uint23_t specifying the value bidding will start at for 
   *    the item. Defaults to 0.
   *
   * \return \c true if the item was added successfully, \c false otherwise.
   */
  bool addItem(std::string name, uint32_t starting_value=0);

  /**
   * \brief Add a user to the auction
   *
   * This registers a new user with the auction. The user's \c name and
   * (optional) \c funds are passed as parameters. If the \c name passed is
   * already in use by another user in the auction, an exception is thrown and
   * the funtion returns \c false. The user's \c id is assigned using the
   * class's \c user_id_counter. 
   *
   * \param name
   *    A \c string specifying the name of the user.
   *
   * \param funds
   *    An optional uint32_t specifying the amount of funds to initialize the
   *    user with. Defaults to 0.
   *
   * \return \c true if the user was added successfully, \c false otherwise.
   */
  bool addUser(std::string name, uint32_t funds=0);

  /**
   * \brief Open a registered item for bidding.
   *
   * This opens a registered item in the auction for bidding. Bids cannot be
   * placed on an item unless it is open. If the item is not registered in the
   * auction, if the item is already open, or if the item has already been sold, 
   * an exception is thrown and the function returns \c false. 
   *
   * \param item
   *    An \c Item to open for auction. 
   *
   * \return \c true if the item was successfulled opened for auction, \c false
   * otherwise.
   */
  bool openItemForBidding(Item* item);

  /**
   * \brief Close an open item for bidding.
   *
   * This closes an open item for bidding. If the item is not already open, an
   * exception is thrown and the function returns \c false.
   *
   * \param item
   *    An \c Item that is currently open to close for bidding. 
   *
   * \param sell
   *    An optional \c bool that specifies whether to mark the item sold upon
   *    closing or not. If the item is sold it's selling value is added to the
   *    auction revenue. Defaults to \c false.
   *
   * \return \c true of the item was successfully closed, \c false otherwise.
   */
   bool closeItemForBidding(Item* item, bool sell=false);

protected:
  std::vector<Item*> items;                ///< Items registered in the auction.
  std::vector<Item*> open_bidding_items;   ///< Items currently open for bidding.
  std::vector<User*> users;                ///< Users Registered in the auction.
  uint32_t item_id_counter;               ///< Counter for assigning item ids.
  uint32_t user_id_counter;               ///< Counter for assigning user ids.
  uint32_t revenue;                       ///< Total revenue of the auction.
};

