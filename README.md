# Kitsune v0.2-prealpha
This is a simple tool that will convert a pixel image file into
the 2bpp, 4bpp or 8bpp bitplane format used by the SNES to display objects with
corresponding palette data. Kitsune uses Qt.

## Usage
After compiling and starting Kitsune, use the File menu to open a file and
the Image menu to export a Tileset. The format can be switched in the
Settings menu between 2bpp and 4bpp(8bpp implementation is missing as of
yet).

Note that this was written in a nightly session, so it is highly unoptimized
and experimental. Use at own risk. Was successfully tested on Windows with Cgywin
and Linux.

## Compilation
Run first `qmake` and then `make` to compile Kitsune. The executable is
placed in the subdirectory `build`. There is no release build or automatic
installation as of yet. You need to run it from the build directory.
