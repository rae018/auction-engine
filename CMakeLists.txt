cmake_minimum_required (VERSION 2.8.3)
project(auction_engine)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(demo

  # Header files
  src/auction.h
  src/bid.h
  src/error.h
  src/error_codes.h
  src/item.h
  src/print.h
  src/status.h
  src/user.h

  # Source code files
  src/auction.cpp
  src/demo.cpp
  src/item.cpp
  src/print.cpp
  src/status.cpp
  src/user.cpp
)

add_executable(auction_test

  # Header files
  src/auction.h
  src/bid.h
  src/error.h
  src/error_codes.h
  src/item.h
  src/print.h
  src/status.h
  src/user.h

  # Source code files
  src/auction.cpp
  src/auction_test.cpp
  src/item.cpp
  src/print.cpp
  src/status.cpp
  src/user.cpp
)

add_executable(item_test

  # Header files
  src/bid.h
  src/auction.h
  src/error.h
  src/error_codes.h
  src/item.h
  src/print.h
  src/user.h
  src/status.h

  # Source code files
  src/item.cpp
  src/auction.cpp
  src/item_test.cpp
  src/print.cpp
  src/user.cpp
  src/status.cpp
)

add_executable(user_test

  # Header files
  src/bid.h
  src/auction.h
  src/error.h
  src/error_codes.h
  src/item.h
  src/print.h
  src/user.h
  src/status.h

  # Source code files
  src/item.cpp
  src/auction.cpp
  src/user_test.cpp
  src/print.cpp
  src/user.cpp
  src/status.cpp
)
