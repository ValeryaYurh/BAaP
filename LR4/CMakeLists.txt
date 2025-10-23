cmake_minimum_required(VERSION 3.18)
project(LR4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_OSX_ARCHITECTURES arm64)

# ==========================
# Task executables
# ==========================
add_executable(Task_1 Task_1/Task_1.cpp Task_1/dubelems.cpp)
add_executable(Task_2 Task_2/Task_2.cpp Task_2/sumodd.cpp)
add_executable(Task_3 Task_3/Task_3.cpp Task_3/get_sum_odd.cpp)
add_executable(Task_4 LabWork4_PartC/Task_4/Task_4.c  LabWork4_PartC/Task_4/max_diag.c)
add_executable(Task_5 LabWork4_PartC/Task_5/Task_5.c  LabWork4_PartC/Task_5/num_mine.c)
add_executable(Task_6 LabWork4_PartC/Task_6/Task_6.c  LabWork4_PartC/Task_6/magic_square.c)

# ==========================
# GoogleTest
# ==========================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Single test executable for Task_1 and Task_2
add_executable(
  gtests
  gtests/gtests.cpp   # tests for Task_1
  Task_1/dubelems.cpp
  Task_2/sumodd.cpp
  Task_3/get_sum_odd.cpp  #
  LabWork4_PartC/Task_4/max_diag.c
  LabWork4_PartC/Task_5/num_mine.c
  LabWork4_PartC/Task_6/magic_square.c
)
target_link_libraries(gtests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(gtests)
