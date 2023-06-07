cmake_minimum_required(VERSION 3.13)
project(Labyrinthe1)

set(CMAKE_CXX_STANDARD 14)



find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})



add_executable(Labyrinthe1 main.cpp Lab_window.cpp Lab_window.hpp graph.hpp Labyrinthe.hpp )

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})