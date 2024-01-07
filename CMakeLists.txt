cmake_minimum_required(VERSION 3.4...3.28)
project(SimpleLib VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_TESTING "Build test executables" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Project-wide setup
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/lib)

# Dependencies
# TODO: Add find_package() calls here

# Targets
add_subdirectory(src)

# Testing
if(BUILD_TESTING)
  enable_testing()

  # TODO: If you have a test driver, call find_package(... REQUIRED) here
  add_subdirectory(tests)
endif()

# Installation
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../install" CACHE PATH "" FORCE)
endif()

include(GNUInstallDirs)
install(EXPORT ${PROJECT_NAME}Config
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
