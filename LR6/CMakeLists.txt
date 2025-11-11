cmake_minimum_required(VERSION 3.18)
project(LR6)

# ========================================
# Базовые настройки компиляции
# ========================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES arm64)

# # Санитайзеры (Address, Undefined, Thread)
# set(SANITIZER_FLAGS "-fsanitize=address,undefined,thread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS} -Wall -Wextra -pedantic")

 # ========================================
 # Подключение GoogleTest
 # ========================================
 # include(FetchContent)

# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
# enable_testing()

# ========================================
# Исполняемые файлы задач
# ========================================
add_executable(Task_1 Task_1/Task_1.cpp Task_1/find.cpp)
# add_executable(Task_2 Task_2/Task_2.cpp Task_2/Task_2_func.cpp)
# add_executable(Task_3 Task_3/Task_3.cpp Task_3/Task_3_func.cpp)

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

# Single test executable for Task_1 and Task_2
add_executable(
  gtest1
  Task_1/gtest1.cpp   # tests for Task_1
  Task_1/find.cpp
)
target_link_libraries(gtest1 GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(gtest1)