# ==========================================
# Name: Anurag Prashant Umale              =
# Student Id: 1887255                      =
# E-mail: aumale@ucsc.edu                  =
# File: Makefile						   =
# Class: CSE 101 Spring 2023               =
# ==========================================

CC = g++
CFLAGS = -std=c++17 -Wall

all: DictionaryTest Order WordFrequency

DictionaryTest: DictionaryTest.o Dictionary.o
	$(CC) -o $@ $^

Order: Order.o Dictionary.o
	$(CC) -o $@ $^

WordFrequency: WordFrequency.o Dictionary.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f DictionaryTest Dictionary Order WordFrequency *.o

cleanText:
	rm -f *.txt

cleandir:
	rm -r backup

checkOrder:
	valgrind --leak-check=full ./Order in out

checkTest:
	valgrind --leak-check=full ./DictionaryTest

checkWord:
	valgrind --leak-check=full ./WordFrequency in out
