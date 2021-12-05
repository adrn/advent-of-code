cmake_minimum_required (VERSION 3.5)

project(AOC2021 LANGUAGES CXX)

message(STATUS "Starting build process!")

find_package(Curses REQUIRED)
message(STATUS "${CURSES_LIBRARIES}")
include_directories(${CURSES_INCLUDE_DIR})

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Solution scripts:
file(GLOB_RECURSE days RELATIVE ${CMAKE_CURRENT_LIST_DIR} day*/*.cpp)
foreach(day ${days})
  message(STATUS "Found day: ${day}")
  get_filename_component(day_base ${day} NAME_WE)
  get_filename_component(day_dir ${day} DIRECTORY)
  add_executable(${day_base} ${day})
  target_compile_options(${day_base} PUBLIC -fPIC -std=c++17)
  target_include_directories(${day_base} PUBLIC ${day_dir})
  target_include_directories(${day_base} PUBLIC include)
  target_link_libraries(${day_base} ${CURSES_LIBRARIES})
  target_link_libraries(${day_base}  Eigen3::Eigen)
  set_property(TARGET ${day_base} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

  # Link any data files:
  file(GLOB_RECURSE datafiles RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${day_base}/*.txt)
  foreach(datafile ${datafiles})
    get_filename_component(datafile_name ${datafile} NAME)
    message(STATUS "Found data file in ${day_base}: ${datafile}")
    message(STATUS "Linking data file from ${CMAKE_SOURCE_DIR}/${datafile} to ${CMAKE_CURRENT_BINARY_DIR}/bin/${datafile_name}")

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
    add_custom_command(TARGET ${day_base} PRE_BUILD
                       COMMAND ${CMAKE_COMMAND} -E create_symlink
                       ${CMAKE_SOURCE_DIR}/${datafile} ${CMAKE_CURRENT_BINARY_DIR}/data/${datafile_name})
  endforeach()
endforeach()

