import os
os.environ["LD_LIBRARY_PATH"] = "."

from _python_interface import ffi, lib



@ffi.def_extern()
def temperatur_messung(ptc_id):
    return 10 * ptc_id


lib.setup()
lib.loop()
