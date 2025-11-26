cmake_minimum_required(VERSION 3.18)
project(LR7)

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
add_executable(Task_1 include/tools.cpp task1.cpp)
# add_executable(Task_2 Task_2/Task_2.cpp Task_2/receipt_calc.cpp)
# add_executable(Task_3 Task_3/Task_3.cpp Task_3/res.cpp)