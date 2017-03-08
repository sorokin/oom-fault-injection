cmake_minimum_required(VERSION 2.8)

project(OOM_FAULT_INJECTION)

add_library(oom-fault-injection SHARED main.cpp)
target_link_libraries(oom-fault-injection -ldl)
