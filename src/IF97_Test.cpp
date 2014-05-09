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

	std::cout << eos.Density(100000,300) << std::endl;
	std::cout << eos.Density(100000,500) << std::endl;
	std::cout << eos.Density(1000000,1200) << std::endl;


	for (double T=280; T<400; T+=1)
	{
		std::cout << T << "  " << eos.Density(1e5,T) << std::endl;
	}


	return 0;
}




