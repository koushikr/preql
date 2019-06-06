/*
 * Copyright 2019 Koushik R <rkoushik.14@gmail.com>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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


