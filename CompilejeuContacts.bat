@echo off

g++ -c -Ofast -s src/progs/jeuContacts.cpp -I lib/glfw-3.3.6/include -I lib/glew-2.1.0/include -I lib/glm

g++ *.o -o JeuContacts.exe -lopengl32 -L lib/glfw-3.3.6/StaticLib -lglfw3 -L lib/glew-2.1.0/lib/Release/x64 -lglew32

del *.o