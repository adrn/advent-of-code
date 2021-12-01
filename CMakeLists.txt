cmake_minimum_required (VERSION 3.5)

project(AOC2021 LANGUAGES CXX)

find_package(Curses REQUIRED)
message(STATUS "${CURSES_LIBRARIES}")
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB_RECURSE days RELATIVE ${CMAKE_CURRENT_LIST_DIR} day*/*.cpp)
foreach(day ${days})
  get_filename_component(day_name ${day} NAME_WE)
  get_filename_component(day_dir ${day} DIRECTORY)
  add_executable(${day_name} ${day})
  target_compile_options(${day_name} PUBLIC -fPIC -std=c++17)
  target_include_directories(${day_name} PUBLIC ${day_dir})
#   target_link_libraries(${day_name} ${CURSES_LIBRARIES})
  set_property(TARGET ${day_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endforeach()

