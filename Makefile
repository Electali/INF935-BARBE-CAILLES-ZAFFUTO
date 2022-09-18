CC = g++
CFLAGS  = -g -Wall

main: main.o vector3D.o particule.o
	$(CC) $(CFLAGS) -o main main.o vector3D.o

main.o: main.cpp vector3D.h particule.h
	$(CC) $(CFLAGS) -c main.cpp  
        
vector3D.o : vector3D.h

particule.o : particule.h

clean:
	$(RM) main 