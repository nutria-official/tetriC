 gcc ./src/*.c -o tetric.exe -O1 -Wall -Werror -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lm -static-libgcc -static-libstdc++
