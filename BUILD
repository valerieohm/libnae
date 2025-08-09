load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "libnae",
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/*.h"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    copts = ["-g", "-O0"],  # Add debug info and disable optimization
    linkstatic = 1,
)