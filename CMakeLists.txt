cmake_minimum_required (VERSION 2.8.3)
project(auction_engine)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(demo

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
  src/demo.cpp
  src/item.cpp
  src/print.cpp
  src/status.cpp
  src/user.cpp
)

add_executable(auction_test

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
  src/auction_test.cpp
  src/item.cpp
  src/print.cpp
  src/status.cpp
  src/user.cpp
)

add_executable(item_test

  # Header files
  include/bid.h
  include/auction.h
  include/error.h
  include/error_codes.h
  include/item.h
  include/print.h
  include/user.h
  include/status.h

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
  include/bid.h
  include/auction.h
  include/error.h
  include/error_codes.h
  include/item.h
  include/print.h
  include/user.h
  include/status.h

  # Source code files
  src/item.cpp
  src/auction.cpp
  src/user_test.cpp
  src/print.cpp
  src/user.cpp
  src/status.cpp
)
