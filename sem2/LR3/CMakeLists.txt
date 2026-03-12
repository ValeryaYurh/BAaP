cmake_minimum_required(VERSION 3.16)
project(LR3)


set(FILE_NAME_CPP "main.cpp")
set(CPP_SOURCES task1 task2 task3 task4)


add_executable(task1 task1/main.cpp)
add_executable(task2 task2/main.cpp)
add_executable(task3 task3/main.cpp)

add_executable(task4 task4/main.cpp)