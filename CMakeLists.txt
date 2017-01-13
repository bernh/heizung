cmake_minimum_required(VERSION 2.8)
project("Heizung")
set(CMAKE_C_FLAGS "-g -Wall")

# set up my source files lists
set(heizung_srcs src/heizung.c src/heizung_test.c)

# set up my executables
add_executable(heizung ${heizung_srcs})
