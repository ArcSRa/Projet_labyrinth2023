cmake_minimum_required(VERSION 3.13)
project(testcpp)

set(CMAKE_CXX_STANDARD 14)



find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})



add_executable(testcpp fenetre_graphique.cpp grille.hpp vue.hpp )

target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})