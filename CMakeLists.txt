cmake_minimum_required(VERSION 2.8)
project("Heizung")
set(CMAKE_C_FLAGS "-g -Wall")

# set up my source files lists
set(heizung_srcs src/heizung.c src/ptc.c)

# set up my shared library
add_library(heizung SHARED ${heizung_srcs})
