CC = g++
CFLAGS  = -g -Wall -I lib/glfw-3.3.6/include -I lib/glew-2.1.0/include -I lib/glm
LFLAG = -lopengl32 -L lib/glfw-3.3.6/StaticLib -lglfw3 -L lib/glew-2.1.0/lib/Release/x64 -lglew32

main: main.o vector3D.o particule.o
	$(CC) $(LFLAGS) -o main main.o vector3D.o

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

test: testOpenGL.o
	$(CC) $(LFLAGS) -o testOpenGL testOpenGL.o

testOpenGL.o: testOpenGL.cpp 
	$(CC) $(CFLAGS) -c testOpenGL.cpp

clean:
	$(RM) main