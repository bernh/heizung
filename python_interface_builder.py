from cffi import FFI
ffibuilder = FFI()

with open("src/test.h") as f:
    c_interface = f.read()

ffibuilder.set_source("_python_interface",
    c_interface,
    libraries=["heizung"],
    library_dirs=["."])
ffibuilder.cdef(c_interface)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)

