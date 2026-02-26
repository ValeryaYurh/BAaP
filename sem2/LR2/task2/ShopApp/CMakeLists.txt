cmake_minimum_required(VERSION 3.16)
project(ShopApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_executable(ShopApp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    product.h
    product.cpp
    productfile.h
    productfile.cpp
    agevalidator.h
    agevalidator.cpp
)

target_link_libraries(ShopApp PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

set_target_properties(ShopApp PROPERTIES MACOSX_BUNDLE TRUE)
