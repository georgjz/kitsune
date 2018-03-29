# Kitsune v0.2-prealpha
This is a simple tool that will convert a pixel image file into
the 2bpp, 4bpp or 8bpp bitplane format used by the SNES to display objects with
corresponding palette data. Kitsune uses Qt.

## Usage
After compiling and starting Kitsune, use the File menu to open a file and
the Image menu to export a Tile Set. The format can be switched in the
Settings menu between 2bpp and 4bpp(8bpp implementation is missing as of
yet).

Note that this was written in a nightly session, so it is highly unoptimized
and experimental. Use at own risk. Was successfully tested on Windows with Cgywin
and Linux.

## Compilation
Run first `qmake` and then `make` to compile Kitsune. The executable is
placed in the subdirectory `build`. Optionally, you can use `make install` to
add Kitsune to your system, but it is discouraged as of now. This software is
still experimental.

To build the code documentation, move to the `doc` directory and run doxygen:
```
$ doxygen Doxyfile
```
This will create a new directory `html` which will contain the code documentation.
Open `index.html` to get to the starting page of the documentation.
