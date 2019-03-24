cmake_minimum_required (VERSION 2.8.3)
project(auction_engine)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(auction_engine

  # Header files
  include/auction.h
  include/bid.h
  include/error.h
  include/error_codes.h
  include/item.h
  include/print.h
  include/status.h
  include/user.h

  # Source code files
  src/auction.cpp
  src/full_test.cpp
  src/item.cpp
  src/print.cpp
  src/status.cpp
  src/user.cpp
)
