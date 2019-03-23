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

#include <user.h>
#include <stdint.h>

namespace auction_engine {

/**
 * \brief Bid data structure.
 *
 * This data structure records all information related to a bid in the auction.
 */
struct Bid {
  /// Value of the bid.
  uint32_t value;

  /// User that placed the bid.
  User *owner;

  /// Item the bid was placed on.
  Item item;

  /// Number of the bid for the item it was placed on.
  uint16_t number;
};

}  // namespace auction_engine
