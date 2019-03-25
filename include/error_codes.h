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

namespace auction_engine {
namespace error {

  enum Code {                                                           
  // No error, returned on success                                                  
  OK,                                                                               
                                                                                    
  // User placed bid with value greater than their funds.                           
  INSUFFICIENT_FUNDS,                                                               
                                                                                    
  // User placed bid with value less or equal to the current bid's value or the     
  // item was not open for bidding.                                                 
  INVALID_BID,                                                                      
                                                                                    
  // Reference to item or user not registered in auction was made                   
  NOT_FOUND,      

  // Item is not open for bidding
  ITEM_UNAVAILABLE,
                                                                                    
  // Item or user registered with name that is already in use.                      
  NAME_TAKEN                                                                        
};  

}  // namespace error
}  // namespace auction_engine
