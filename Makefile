#
# Makefile for libogcom - Oceangate lib
#
# Created 11/05/2020 - Phil Brooks
#
# Copywrite 2020 - Oceangate Inc.
#
#
#
#

CC=g++
CC_OPTS=-O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 
all: ogcomlib
clean:
	rm -f *.o *.a 

SSocket.o: SSocket.cpp SSocket.h
	$(CC) $(CC_OPTS) SSocket.cpp 

UDPSSocket.o: UDPSSocket.cpp UDPSSocket.h
	$(CC) $(CC_OPTS) UDPSSocket.cpp 


ogcomlib: SSocket.o UDPSSocket.o
	ar crs libogcom.a SSocket.o UDPSSocket.o 
