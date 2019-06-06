/* 
 * File:   Utils.cpp
 * Author: anmol
 * 
 * Created on 20 December, 2010, 3:33 AM
 */
#include <iostream>
#include <stdio.h>
#include "Utils.h"

using namespace std;

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}

void Utils::pressEnter()
{
cin.clear() ;// just to ensure there's no junk in the stream which
cout << "Press Enter / Return to continue...\n";
cin.ignore(1,0);
}

void Utils::strreverse(char* begin, char* end) {

	char aux;

	while(end>begin)

		aux=*end, *end--=*begin, *begin++=aux;

}

void Utils::itoa(int value, char* str, int base) {

	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	char* wstr=str;

	int sign;



	// Validate base

	if (base<2 || base>35){ *wstr='\0'; return; }



	// Take care of sign

	if ((sign=value) < 0) value = -value;



	// Conversion. Number is reversed.

	do *wstr++ = num[value%base]; while(value/=base);

	if(sign<0) *wstr++='-';

	*wstr='\0';



	// Reverse string

	strreverse(str,wstr-1);

}


