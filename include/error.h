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

#include <status.h>
#include <string>
#include <sstream>

/**
 * \file
 * \brief This file contains functions for error status gereration
 */

namespace auction_engine {
namespace error {

/// Base case for \c concatArgs(const T& t, const Args&... args) 
template <typename T>
std::string concatArgs(const T& t) {
  std::stringstream ss;
  ss << t;
  return ss.str();
}

/// Function to concatenate multiple arguments of error message into string.
template <typename T, typename... Args>
std::string concatArgs(const T& t, const Args&... args) {
  std::stringstream ss;
  ss << t;
  ss << concatArgs(args...);
  return ss.str();
}

/// Function to create \c INSUFFICIENT_FUNDS error status.
template <typename... Args>
::auction_engine::Status InsufficientFunds(Args... args) {
  return ::auction_engine::Status(::auction_engine::error::INSUFFICIENT_FUNDS,
      concatArgs(args...));
}
/// Function to test whether error status has code \c INSUFFICIENT_FUNDS.
inline bool IsInsufficientFunds(::auction_engine::Status& status) {
  return status.code() == ::auction_engine::error::INSUFFICIENT_FUNDS;
}

/// Function to create \c INVALID_BID error status.
template <typename... Args>
::auction_engine::Status InvalidBid(Args... args) {
  return ::auction_engine::Status(::auction_engine::error::INVALID_BID,
      concatArgs(args...));
}
/// Function to test whether error status has code \c INVALID_BID.
inline bool IsInvalidBid(::auction_engine::Status& status) {
  return status.code() == ::auction_engine::error::INVALID_BID;
}

/// Function to create \c NOT_FOUND error status.
template <typename... Args>
::auction_engine::Status NotFound(Args... args) {
  return ::auction_engine::Status(::auction_engine::error::NOT_FOUND,
      concatArgs(args...));
}
/// Function to test whether error status has code \c NOT_FOUND.
inline bool IsNotFound(::auction_engine::Status& status) {
  return status.code() == ::auction_engine::error::NOT_FOUND;
}

/// Function to create \c ITEM_UNAVAILABLE error status.
template <typename... Args>
::auction_engine::Status ItemUnavailable(Args... args) {
  return ::auction_engine::Status(::auction_engine::error::ITEM_UNAVAILABLE,
      concatArgs(args...));
}
/// Function to test whether error status has code \c ITEM_UNAVAILABLE.
inline bool IsItemUnavailable(::auction_engine::Status& status) {
  return status.code() == ::auction_engine::error::ITEM_UNAVAILABLE;
}

/// Function to create \c NAME_TAKEN error status.
template <typename... Args>
::auction_engine::Status NameTaken(Args... args) {
  return ::auction_engine::Status(::auction_engine::error::NAME_TAKEN,
      concatArgs(args...));
}
/// Function to test whether error status has code \c NAME_TAKEN.
inline bool IsNameTaken(::auction_engine::Status& status) {
  return status.code() == ::auction_engine::error::NAME_TAKEN;
}

}  // namespace error
}  // namespace auction_engine
