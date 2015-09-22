cmake_minimum_required(VERSION 3.2)
project(cpp-sandbox)

add_executable(do_lower_bound
  src/main_lower_bound.cpp)
set_property(TARGET do_lower_bound PROPERTY CXX_STANDARD 14)