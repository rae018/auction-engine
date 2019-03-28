/* Copyright [yyyy] [name of copyright owner]                                                       
                                                                                    
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

#include <error_codes.h>
#include <string>

namespace auction_engine {

/**
 * \brief Status class for returning error codes.
 *
 * This class stores information related to error codes returned for certain
 * operations. 
 */
class Status {
public:
  /// Constructor for successful status.
  Status() {}

  /// Create ok status.
  static Status OK() { return Status(); }

  /// Returns \c true if status contains no error, \c false otherwise.
  bool ok() const { return state == NULL; }

  /// Constructor for status with error code and message.
  Status(auction_engine::error::Code code, std::string msg);

  /// Returns the status error code.
  auction_engine::error::Code code() const {
    return ok() ? auction_engine::error::OK : state->code;
  }

  /// Returns the status error message.
  std::string error_message() const {
    return ok() ? std::string() : state->msg;
  }
  
private:
  // This state is NULL if there is no error (error::Code == OK) signifying an 
  // OK status. Otherwise it contains the error code and message.
  struct State {
    auction_engine::error::Code code;
    std::string msg;
  };
  std::unique_ptr<State> state;
};
}  // namespace auction_engine
