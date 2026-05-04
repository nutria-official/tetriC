x86_64-w64-mingw32-gcc -static -o mygame.exe main.c \
  -I/path/to/raylib/src \
  -L/path/to/raylib/src \
  -lraylib -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32
