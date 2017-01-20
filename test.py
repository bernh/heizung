import os
from _python_interface import ffi, lib

os.environ["LD_LIBRARY_PATH"] = "."

lib.setup()
lib.loop()
