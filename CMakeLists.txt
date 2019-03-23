cmake_minimum_required (VERSION 2.8.3)
project(auction_engine)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(auction_engine

  # Header files
  include/bid.h
  include/auction.h
  include/item.h
  include/user.h

  # Source code files
  src/auction.cpp
  src/full_test.cpp
  src/item.cpp
  src/user.cpp
)
