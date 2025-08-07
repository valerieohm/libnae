load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "libnae",
    srcs = ["src/vertex.cpp", "src/edge.cpp", "src/obj.cpp"],
    hdrs = ["include/types.h", "include/obj.h", "include/edge.h", "include/vertex.h"],
    includes = ["include"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)
