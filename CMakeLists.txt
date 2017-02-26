cmake_minimum_required(VERSION 2.8)

project(Deasystem)

  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()

# Find source files
file(GLOB SOURCES "src/*.cpp" "src/Filetypes/*.cpp")

# Include header files
include_directories("inc")
include_directories("inc/Filetypes")

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADER_TYPES include/Filetypes/*.hpp)
install(DIRECTORY "inc/" DESTINATION include/${PROJECT_NAME})
