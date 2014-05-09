/*
 * IF97_Test.cpp
 *
 *  Created on: 09.05.2014
 *      Author: boettche
 */

 #include <iostream>
#include "IAPWS-IF97.h"


int main() {

	IF97 eos;

	for (double p=8000.0; p<11000.0; p+=100)
		{
			std::cout << p << " " << eos.Density(p,320.0) << std::endl;
		}



	for (double p=100000; p<1000000; p+=100000)
	{
		std::cout << p << "  " << eos.Density(p,500) << std::endl;
	}


	return 0;
}




