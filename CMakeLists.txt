project(WeBook)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 REQUIRED
    Core
    widgets
)

add_subdirectory(src)

# install resources
add_subdirectory(resources)

# install resources
add_subdirectory(usr/share/icons)

