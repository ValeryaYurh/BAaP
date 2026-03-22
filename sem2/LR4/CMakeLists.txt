cmake_minimum_required(VERSION 3.16)
project(LR12)


set(FILE_NAME_CPP "main.cpp")
set(CPP_SOURCES task1 task2 task3)


add_executable(heap task1/heap/main.cpp)
add_executable(quick task1/quick/main.cpp)
add_executable(merge task1/merge/main.cpp)
add_executable(binsearch task1/binsearch/main.cpp)
add_executable(interpol task2/interpol/main.cpp)
add_executable(binpow task2/binpow/main.cpp)
add_executable(t3 task3/main.cpp)