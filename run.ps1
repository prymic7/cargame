//Compiler code
g++.exe main.cpp -o game.exe -O1 -Wall -Wno-missing-braces -I includes/ -L lib/ -lraylib -lgdi32 -lwinmm -static-libgcc -static-libstdc++

//if this doenst work, try
g++.exe main.cpp -o game.exe -O1 -Wall -Wno-missing-braces -I includes/ -L lib/ -lraylib -lgdi32 -lwinmm
