cmake_minimum_required(VERSION 2.8)
project("Heizung")
set(CMAKE_C_FLAGS "-g -Wall")

# set up my source files lists
set(heizung_srcs src/heizung.c src/ptc.c)

# set up my shared library
add_library(heizung SHARED ${heizung_srcs})

# define python interface and add dependency to shared library
add_custom_command (
    OUTPUT _python_interface.c _python_interface.o
    COMMAND python python_interface_builder.py
    )
add_custom_target(python_interface ALL DEPENDS _python_interface.c)
add_dependencies(python_interface heizung)
