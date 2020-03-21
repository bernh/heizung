Design
======

Arduino entry point in heizung.ino
Main implementation in heizung.cpp with entry point loop_heizung()



LiquidCrystal_I2C
=================

https://github.com/johnrickman/LiquidCrystal_I2C 
version 1.1.4 committed 

Test
====

Compile via 'cmake .' and 'make'

Unit Tests
----------

Executable: test_heizung
Implementation in test/test_heizung.cc
Architecture:
- test_heizungs.cc implements set_outputs() and temperatur_messung()


Python Tests
------------



