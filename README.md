# Kitsune
This is a simple tool that will convert a pixel image file into
the 2bpp or 4bpp bitplane format used by the SNES to display objects with a maximum
of one palette consisting 16 colors.

## Usage
Kitsune as of yet is a simple command line tool, that will require 3 commandline
arguments:
```
-f filename.png
-b 2bpp or 4bpp
-o outputname
```
Example:
```
kitsune -f mario.png -b 4bpp -o Mario_Sprites
```
This will create two files: `Mario_Sprites.bin` and `Mario_Sprites.pal`. The first
will contain the CHR data that will be in VRAM, the latter the palette data that
will be located in CGRAM. The palette file will be exactly 32 bytes long(16 colors),
missing colors will be filled up with black(BGR555: $00).

Note that this was written in a nightly session, so it is highly unoptimized
and experimental. Use at own risk. Was successfully tested on Windows with Cgywin
and Linux.
