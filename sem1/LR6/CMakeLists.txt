cmake_minimum_required(VERSION 3.18)
project(LR6)

# ========================================
# Базовые настройки компиляции
# ========================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_CXX_CLANG_TIDY "/opt/homebrew/opt/llvm/bin/clang-tidy;-checks=*")
set(SANITIZER "address;thread")

# ========================================
# Исполняемые файлы задач
# ========================================
add_executable(Task_1 Task_1/Task_1.cpp Task_1/find.cpp)
add_executable(Task_2 Task_2/Task_2.cpp Task_2/receipt_calc.cpp)
add_executable(Task_3 Task_3/Task_3.cpp Task_3/res.cpp)

# Можно добавить больше задач по аналогии
# add_executable(Task_4 src/Task_4.cpp src/Task_4_func.cpp)

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

add_executable(
  gtest1
  Task_1/gtest1.cpp   # tests for Task_1
  Task_1/find.cpp
)

target_link_libraries(gtest1 GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(gtest1)

add_executable(
  gtest2
  Task_2/gtest2.cpp   # tests for Task_2
  Task_2/receipt_calc.cpp
)

target_link_libraries(gtest2 GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(gtest2)

add_executable(
  gtest3
  Task_3/gtest3.cpp   # tests for Task_3
  Task_3/res.cpp
)

target_link_libraries(gtest3 GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(gtest3)