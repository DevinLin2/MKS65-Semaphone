all: control.o write.o
	gcc -o control control.o
	gcc -o write write.o

control.o: control.c control.h
	gcc -c control.c control.h

write.o: write.c control.h
	gcc -c write.c control.h
