#ifndef _LIBRARY_H_	 //to prevent it from being compiled every time we make a small change
#define _LIBRARY_H_		//in case we have no changes it will compile it again

#include <stdio.h>


void read();
void do_ping(char direccion[], char b[]);
void empty(char b[]);
void adapters();
void delete();
void dns();
void vation(char b[]);
void compare();
void netsh(char b[]);
void op();

#endif