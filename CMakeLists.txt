cmake_minimum_required(VERSION 3.20)
project(snf)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JANSSON REQUIRED jansson)

add_subdirectory(src)

install(TARGETS ${PROJECT_NAME} DESTINATION ~/.local/bin)
