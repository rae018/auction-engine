cc_library(
    name = "auction",
    srcs = ["auction.cpp", "user.cpp", "item.cpp", "status.cpp", "print.cpp"],
    hdrs = ["auction.h", "user.h", "item.h", "status.h", "bid.h", "print.h", 
            "error.h", "error_codes.h"],
)

cc_binary(
    name = "demo",
    srcs = ["demo.cpp"],
    deps = [
        ":auction",
    ],
)

cc_binary(
    name = "auction_test",
    srcs = ["auction_test.cpp"],
    deps = [
        ":auction",
    ],
)

cc_binary(
    name = "user_test",
    srcs = ["user_test.cpp"],
    deps = [
        ":auction",
    ],
)

cc_binary(
    name = "item_test",
    srcs = ["item_test.cpp"],
    deps = [
        ":auction",
    ],
)
