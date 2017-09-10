cmake_minimum_required(VERSION 2.8)
project("Heizung")
set(CMAKE_CXX_FLAGS "-g -Wall -DPC_TEST")

# google test setup
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(gtest_SOURCE_DIR googletest)
include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}
  heizung)

# compile google test code into libs
add_library(gtest ${gtest_SOURCE_DIR}/src/gtest-all.cc)
add_library(gtest_main ${gtest_SOURCE_DIR}/src/gtest_main.cc)

# set up source files to be tested and build library
set(heizung_srcs heizung/heizung.cpp)
add_library(heizung ${heizung_srcs})

# build test executables
add_executable(test_heizung test/test_heizung.cc)
target_link_libraries(test_heizung heizung gtest_main gtest Threads::Threads)

# --- generating and building the python interface ---
option (python_ffi "Python test interface" OFF)
if (python_ffi)
    # set up my shared library
    add_library(heizung SHARED ${heizung_srcs})

    # define python interface and add dependency to shared library
    add_custom_command (
        OUTPUT _python_interface.c _python_interface.o
        DEPENDS python_interface_builder.py heizung/test.h
        COMMAND python python_interface_builder.py
        )
    add_custom_target(python_interface ALL DEPENDS _python_interface.c)
    add_dependencies(python_interface heizung)
endif()
