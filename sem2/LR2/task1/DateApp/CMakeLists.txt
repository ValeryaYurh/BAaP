cmake_minimum_required(VERSION 3.16)
project(DateApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUI ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(DateApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    date.cpp
    date.h
    datestorage.cpp
    datestorage.h
    datetests.cpp
    datetests.h
)

target_link_libraries(DateApp Qt6::Core Qt6::Widgets Qt6::Gui)
target_include_directories(DateApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
