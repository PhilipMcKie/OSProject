CC=gcc
all: COMHAN time date help
COMHAN: COMHAN.o stringlib.o PCB.o
	$(CC) -g -o COMHAN src/o/COMHAN.o src/o/stringlib.o src/o/PCB.o

COMHAN.o: #COMHAN.c stringlib.c
	$(CC) -c src/COMHAN.c -o src/o/COMHAN.o

stringlib.o:
	$(CC) -g -c src/stringlib.c -o src/o/stringlib.o

PCB.o:
	$(CC) -g -c src/PCB.c -o src/o/PCB.o
time: time.o
	$(CC) -o bin/time src/o/time.o
time.o:
	$(CC) -o src/o/time.o -c src/time.c

date: date.o
	$(CC) -o bin/date src/o/date.o
date.o:
	$(CC) -o src/o/date.o -c src/date.c

help: help.o
	$(CC) -o bin/help src/o/help.o
help.o:
	$(CC) -o src/o/help.o -c src/help.c
