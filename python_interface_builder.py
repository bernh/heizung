from cffi import FFI
ffibuilder = FFI()

with open("heizung/test.h") as f:
    c_interface = f.read()

ffibuilder.set_source("_python_interface",
    c_interface,
    libraries=["heizung"],
    library_dirs=["."])
ffibuilder.cdef(c_interface +
"""
    extern "Python+C" int temperatur_messung(int ptc_id);
""")


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)

