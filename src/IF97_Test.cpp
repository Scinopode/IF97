/*
 * IF97_Test.cpp
 *
 *  Created on: 09.05.2014
 *      Author: boettche
 */

 #include <iostream>
 #include <cmath>

#include <vector>
#include "IAPWS-IF97.h"

struct VerificationData
{
	double T; 	// Temperature in K
	double p;  // pressure in Pa
	double v;  // specific volume in m^3/kg
	double r;  // density in kg/m^3
	double h;  // specific enthalphy in J/kg
	double u;  // specific internal energy in J/kg
	double s;  // specific entropy in J/kg/K
	double cp; // specific isobaric heat capacity in J/kg/K
	double cv; // specific isochoric heat capacity in J/kg/K
	double w;  // speed of sound in m/s
};

struct VerificationDataThermalConductivity
{
	double T; 	// Temperature in K
	double p;  // pressure in Pa
	double l;
};

std::vector<VerificationData> check;
std::vector<VerificationDataThermalConductivity> checkThermalConductivity;


void SetVerificatioonDataThermalConductivity ()
{
	VerificationDataThermalConductivity V;

	V.T=273.15;V.p=100000;V.l=561.1; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=500000;V.l=561.3; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=1000000;V.l=561.6; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=2500000;V.l=562.4; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=5000000;V.l=563.8; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=7500000;V.l=565.2; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=10000000;V.l=566.5; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=12500000;V.l=567.9; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=15000000;V.l=569.3; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=17500000;V.l=570.7; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=20000000;V.l=572.1; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=22500000;V.l=573.4; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=25000000;V.l=574.8; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=27500000;V.l=576.2; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=30000000;V.l=577.5; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=35000000;V.l=580.2; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=40000000;V.l=582.9; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=45000000;V.l=585.6; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=50000000;V.l=588.2; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=55000000;V.l=590.8;  checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=60000000;V.l=593.3; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=65000000;V.l=595.8; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=70000000;V.l=598.3; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=75000000;V.l=600.7; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=80000000;V.l=603.1; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=85000000;V.l=605.4; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=90000000;V.l=607.7; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=95000000;V.l=610; checkThermalConductivity.push_back(V);
	V.T=273.15;V.p=100000000;V.l=612.2; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=100000;V.l=607.2; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=500000;V.l=607.4; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=1000000;V.l=607.6; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=2500000;V.l=608.3; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=5000000;V.l=609.4; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=7500000;V.l=610.6; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=10000000;V.l=611.7; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=12500000;V.l=612.8; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=15000000;V.l=614; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=17500000;V.l=615.1; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=20000000;V.l=616.2; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=22500000;V.l=617.4; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=25000000;V.l=618.5; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=27500000;V.l=619.7; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=30000000;V.l=620.8; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=35000000;V.l=623.1; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=40000000;V.l=625.3; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=45000000;V.l=627.6; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=50000000;V.l=629.8; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=55000000;V.l=632.1; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=60000000;V.l=634.3; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=65000000;V.l=636.5; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=70000000;V.l=638.7; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=75000000;V.l=640.9; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=80000000;V.l=643; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=85000000;V.l=645.1; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=90000000;V.l=647.3; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=95000000;V.l=649.3; checkThermalConductivity.push_back(V);
	V.T=298.15;V.p=100000000;V.l=651.4; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=100000;V.l=643.6; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=500000;V.l=643.8; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=1000000;V.l=644; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=2500000;V.l=644.7; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=5000000;V.l=645.9; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=7500000;V.l=647; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=10000000;V.l=648.2; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=12500000;V.l=649.4; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=15000000;V.l=650.5; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=17500000;V.l=651.7; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=20000000;V.l=652.8; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=22500000;V.l=654; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=25000000;V.l=655.2; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=27500000;V.l=656.3; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=30000000;V.l=657.5; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=35000000;V.l=659.8; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=40000000;V.l=662.1; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=45000000;V.l=664.4; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=50000000;V.l=666.7; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=55000000;V.l=669; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=60000000;V.l=671.3; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=65000000;V.l=673.5; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=70000000;V.l=675.8; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=75000000;V.l=678; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=80000000;V.l=680.3; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=85000000;V.l=682.5; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=90000000;V.l=684.7; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=95000000;V.l=686.8; checkThermalConductivity.push_back(V);
	V.T=323.15;V.p=100000000;V.l=689; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=100000;V.l=666.8; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=500000;V.l=667; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=1000000;V.l=667.2; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=2500000;V.l=668; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=5000000;V.l=669.2; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=7500000;V.l=670.5; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=10000000;V.l=671.7; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=12500000;V.l=673; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=15000000;V.l=674.2; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=17500000;V.l=675.5; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=20000000;V.l=676.7; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=22500000;V.l=678; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=25000000;V.l=679.2; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=27500000;V.l=680.4; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=30000000;V.l=681.7; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=35000000;V.l=684.2; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=40000000;V.l=686.6; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=45000000;V.l=689.1; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=50000000;V.l=691.5; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=55000000;V.l=694; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=60000000;V.l=696.4; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=65000000;V.l=698.8; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=70000000;V.l=701.2; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=75000000;V.l=703.6; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=80000000;V.l=705.9; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=85000000;V.l=708.3; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=90000000;V.l=710.6; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=95000000;V.l=712.9; checkThermalConductivity.push_back(V);
	V.T=348.15;V.p=100000000;V.l=715.2; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=100000;V.l=25.08; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=500000;V.l=679.3; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=1000000;V.l=679.6; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=2500000;V.l=680.4; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=5000000;V.l=681.8; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=7500000;V.l=683.1; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=10000000;V.l=684.5; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=12500000;V.l=685.9; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=15000000;V.l=687.2; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=17500000;V.l=688.6; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=20000000;V.l=689.9; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=22500000;V.l=691.3; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=25000000;V.l=692.6; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=27500000;V.l=694; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=30000000;V.l=695.3; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=35000000;V.l=698; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=40000000;V.l=700.7; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=45000000;V.l=703.3; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=50000000;V.l=706; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=55000000;V.l=708.6; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=60000000;V.l=711.2; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=65000000;V.l=713.9; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=70000000;V.l=716.4; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=75000000;V.l=719; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=80000000;V.l=721.6; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=85000000;V.l=724.1; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=90000000;V.l=726.7; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=95000000;V.l=729.2; checkThermalConductivity.push_back(V);
	V.T=373.15;V.p=100000000;V.l=731.7; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=100000;V.l=28.86; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=500000;V.l=682.1; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=1000000;V.l=682.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=2500000;V.l=683.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=5000000;V.l=685.1; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=7500000;V.l=686.8; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=10000000;V.l=688.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=12500000;V.l=690.1; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=15000000;V.l=691.8; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=17500000;V.l=693.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=20000000;V.l=695.1; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=22500000;V.l=696.7; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=25000000;V.l=698.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=27500000;V.l=700; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=30000000;V.l=701.7; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=35000000;V.l=704.9; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=40000000;V.l=708.2; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=45000000;V.l=711.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=50000000;V.l=714.6; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=55000000;V.l=717.8; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=60000000;V.l=721; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=65000000;V.l=724.1; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=70000000;V.l=727.2; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=75000000;V.l=730.4; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=80000000;V.l=733.5; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=85000000;V.l=736.6; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=90000000;V.l=739.7; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=95000000;V.l=742.7; checkThermalConductivity.push_back(V);
	V.T=423.15;V.p=100000000;V.l=745.8; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=100000;V.l=33.28; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=500000;V.l=34.93; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=1000000;V.l=37.21; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=2500000;V.l=664.1; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=5000000;V.l=666.3; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=7500000;V.l=668.5; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=10000000;V.l=670.6; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=12500000;V.l=672.7; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=15000000;V.l=674.9; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=17500000;V.l=676.9; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=20000000;V.l=679; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=22500000;V.l=681.1; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=25000000;V.l=683.2; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=27500000;V.l=685.2; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=30000000;V.l=687.2; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=35000000;V.l=691.3; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=40000000;V.l=695.3; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=45000000;V.l=699.2; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=50000000;V.l=703.1; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=55000000;V.l=707; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=60000000;V.l=710.9; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=65000000;V.l=714.7; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=70000000;V.l=718.5; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=75000000;V.l=722.2; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=80000000;V.l=726; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=85000000;V.l=729.7; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=90000000;V.l=733.4; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=95000000;V.l=737.1; checkThermalConductivity.push_back(V);
	V.T=473.15;V.p=100000000;V.l=740.8; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=100000;V.l=38.17; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=500000;V.l=39.18; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=1000000;V.l=40.52; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=2500000;V.l=45.16; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=5000000;V.l=622.5; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=7500000;V.l=625.7; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=10000000;V.l=628.8; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=12500000;V.l=631.8; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=15000000;V.l=634.8; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=17500000;V.l=637.7; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=20000000;V.l=640.5; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=22500000;V.l=643.4; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=25000000;V.l=646.1; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=27500000;V.l=648.9; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=30000000;V.l=651.6; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=35000000;V.l=656.8; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=40000000;V.l=662; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=45000000;V.l=667; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=50000000;V.l=671.9; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=55000000;V.l=676.8; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=60000000;V.l=681.5; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=65000000;V.l=686.2; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=70000000;V.l=690.7; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=75000000;V.l=695.3; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=80000000;V.l=699.7; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=85000000;V.l=704.2; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=90000000;V.l=708.5; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=95000000;V.l=712.9; checkThermalConductivity.push_back(V);
	V.T=523.15;V.p=100000000;V.l=717.1; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=100000;V.l=43.42; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=500000;V.l=44.09; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=1000000;V.l=44.96; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=2500000;V.l=47.82; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=5000000;V.l=53.85; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=7500000;V.l=63.12; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=10000000;V.l=550.7; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=12500000;V.l=556.2; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=15000000;V.l=561.4; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=17500000;V.l=566.5; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=20000000;V.l=571.3; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=22500000;V.l=575.9; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=25000000;V.l=580.3; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=27500000;V.l=584.7; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=30000000;V.l=588.8; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=35000000;V.l=596.8; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=40000000;V.l=604.3; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=45000000;V.l=611.5; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=50000000;V.l=618.3; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=55000000;V.l=624.9; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=60000000;V.l=631.2; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=65000000;V.l=637.3; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=70000000;V.l=643.2; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=75000000;V.l=648.9; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=80000000;V.l=654.4; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=85000000;V.l=659.8; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=90000000;V.l=665.1; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=95000000;V.l=670.3; checkThermalConductivity.push_back(V);
	V.T=573.15;V.p=100000000;V.l=675.3; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=100000;V.l=48.97; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=500000;V.l=49.45; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=1000000;V.l=50.07; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=2500000;V.l=52.06; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=5000000;V.l=55.99; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=7500000;V.l=61.05; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=10000000;V.l=68.09; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=12500000;V.l=79.11; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=15000000;V.l=100.9; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=17500000;V.l=452.2; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=20000000;V.l=463.2; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=22500000;V.l=472.7; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=25000000;V.l=481.1; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=27500000;V.l=488.8; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=30000000;V.l=496; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=35000000;V.l=509; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=40000000;V.l=520.7; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=45000000;V.l=531.5; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=50000000;V.l=541.5; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=55000000;V.l=550.8; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=60000000;V.l=559.6; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=65000000;V.l=568; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=70000000;V.l=575.9; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=75000000;V.l=583.4; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=80000000;V.l=590.7; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=85000000;V.l=597.6; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=90000000;V.l=604.3; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=95000000;V.l=610.7; checkThermalConductivity.push_back(V);
	V.T=623.15;V.p=100000000;V.l=617; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=100000;V.l=51.83; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=500000;V.l=52.26; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=1000000;V.l=52.8; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=2500000;V.l=54.53; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=5000000;V.l=57.87; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=7500000;V.l=61.99; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=10000000;V.l=67.34; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=12500000;V.l=74.66; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=15000000;V.l=85.5; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=17500000;V.l=103.6; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=20000000;V.l=141.5; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=22500000;V.l=439.4; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=25000000;V.l=410.8; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=27500000;V.l=425.8; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=30000000;V.l=438; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=35000000;V.l=457.3; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=40000000;V.l=472.8; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=45000000;V.l=486.2; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=50000000;V.l=498.2; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=55000000;V.l=509.1; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=60000000;V.l=519.2; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=65000000;V.l=528.7; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=70000000;V.l=537.6; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=75000000;V.l=546.1; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=80000000;V.l=554.2; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=85000000;V.l=561.9; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=90000000;V.l=569.3; checkThermalConductivity.push_back(V);
	V.T=648.15;V.p=95000000;V.l=576.4; checkThermalConductivity.push_back(V);
V.T=648.15;V.p=100000000;V.l=583.2; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=100000;V.l=54.76; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=500000;V.l=55.14; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=1000000;V.l=55.62; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=2500000;V.l=57.15; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=5000000;V.l=60.06; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=7500000;V.l=63.56; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=10000000;V.l=67.88; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=12500000;V.l=73.38; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=15000000;V.l=80.66; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=17500000;V.l=90.73; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=20000000;V.l=105.4; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=22500000;V.l=128.4; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=25000000;V.l=168; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=27500000;V.l=245.1; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=30000000;V.l=331.4; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=35000000;V.l=384.3; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=40000000;V.l=413.9; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=45000000;V.l=434.8; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=50000000;V.l=451.3; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=55000000;V.l=465.2; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=60000000;V.l=477.4; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=65000000;V.l=488.4; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=70000000;V.l=498.5; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=75000000;V.l=507.9; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=80000000;V.l=516.8; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=85000000;V.l=525.2; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=90000000;V.l=533.2; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=95000000;V.l=540.9; checkThermalConductivity.push_back(V);
V.T=673.15;V.p=100000000;V.l=548.2; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=100000;V.l=57.74; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=500000;V.l=58.08; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=1000000;V.l=58.52; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=2500000;V.l=59.9; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=5000000;V.l=62.49; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=7500000;V.l=65.54; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=10000000;V.l=69.18; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=12500000;V.l=73.61; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=15000000;V.l=79.1; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=17500000;V.l=86.07; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=20000000;V.l=95.09; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=22500000;V.l=107; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=25000000;V.l=123.1; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=27500000;V.l=145.2; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=30000000;V.l=175.5; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=35000000;V.l=257.2; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=40000000;V.l=323.1; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=45000000;V.l=363; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=50000000;V.l=391; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=55000000;V.l=412.4; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=60000000;V.l=429.6; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=65000000;V.l=444.1; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=70000000;V.l=456.8; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=75000000;V.l=468; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=80000000;V.l=478.3; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=85000000;V.l=487.8; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=90000000;V.l=496.6; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=95000000;V.l=504.9; checkThermalConductivity.push_back(V);
V.T=698.15;V.p=100000000;V.l=512.8; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=100000;V.l=60.77; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=500000;V.l=61.09; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=1000000;V.l=61.49; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=2500000;V.l=62.75; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=5000000;V.l=65.1; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=7500000;V.l=67.82; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=10000000;V.l=70.99; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=12500000;V.l=74.72; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=15000000;V.l=79.16; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=17500000;V.l=84.5; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=20000000;V.l=90.99; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=22500000;V.l=98.96; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=25000000;V.l=108.8; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=27500000;V.l=121; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=30000000;V.l=136; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=35000000;V.l=176.1; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=40000000;V.l=226.6; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=45000000;V.l=275.1; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=50000000;V.l=314.9; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=55000000;V.l=345.8; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=60000000;V.l=370.5; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=65000000;V.l=390.8; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=70000000;V.l=408; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=75000000;V.l=422.7; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=80000000;V.l=435.7; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=85000000;V.l=447.2; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=90000000;V.l=457.7; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=95000000;V.l=467.3; checkThermalConductivity.push_back(V);
V.T=723.15;V.p=100000000;V.l=476.2; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=100000;V.l=63.85; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=500000;V.l=64.15; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=1000000;V.l=64.52; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=2500000;V.l=65.69; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=5000000;V.l=67.86; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=7500000;V.l=70.33; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=10000000;V.l=73.16; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=12500000;V.l=76.41; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=15000000;V.l=80.17; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=17500000;V.l=84.54; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=20000000;V.l=89.65; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=22500000;V.l=95.63; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=25000000;V.l=102.7; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=27500000;V.l=110.9; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=30000000;V.l=120.6; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=35000000;V.l=144.8; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=40000000;V.l=175.7; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=45000000;V.l=211.1; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=50000000;V.l=246.5; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=55000000;V.l=279; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=60000000;V.l=307.5; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=65000000;V.l=331.9; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=70000000;V.l=353; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=75000000;V.l=371.4; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=80000000;V.l=387.5; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=85000000;V.l=401.9; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=90000000;V.l=414.7; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=95000000;V.l=426.2; checkThermalConductivity.push_back(V);
V.T=748.15;V.p=100000000;V.l=436.8; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=100000;V.l=66.98; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=500000;V.l=67.26; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=1000000;V.l=67.61; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=2500000;V.l=68.71; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=5000000;V.l=70.74; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=7500000;V.l=73.03; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=10000000;V.l=75.61; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=12500000;V.l=78.52; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=15000000;V.l=81.83; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=17500000;V.l=85.57; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=20000000;V.l=89.84; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=22500000;V.l=94.68; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=25000000;V.l=100.2; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=27500000;V.l=106.5; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=30000000;V.l=113.6; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=35000000;V.l=130.6; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=40000000;V.l=151.5; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=45000000;V.l=176; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=50000000;V.l=202.7; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=55000000;V.l=229.7; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=60000000;V.l=255.5; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=65000000;V.l=279.5; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=70000000;V.l=301.3; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=75000000;V.l=321; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=80000000;V.l=338.8; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=85000000;V.l=354.9; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=90000000;V.l=369.5; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=95000000;V.l=382.8; checkThermalConductivity.push_back(V);
V.T=773.15;V.p=100000000;V.l=394.9; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=100000;V.l=73.36; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=500000;V.l=73.61; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=1000000;V.l=73.94; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=2500000;V.l=74.95; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=5000000;V.l=76.79; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=7500000;V.l=78.84; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=10000000;V.l=81.11; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=12500000;V.l=83.61; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=15000000;V.l=86.38; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=17500000;V.l=89.43; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=20000000;V.l=92.78; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=22500000;V.l=96.47; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=25000000;V.l=100.5; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=27500000;V.l=104.9; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=30000000;V.l=109.8; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=35000000;V.l=120.7; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=40000000;V.l=133.4; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=45000000;V.l=147.8; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=50000000;V.l=163.6; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=55000000;V.l=180.6; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=60000000;V.l=198.1; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=65000000;V.l=215.6; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=70000000;V.l=232.7; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=75000000;V.l=249.1; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=80000000;V.l=264.8; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=85000000;V.l=279.7; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=90000000;V.l=293.7; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=95000000;V.l=306.9; checkThermalConductivity.push_back(V);
V.T=823.15;V.p=100000000;V.l=319.4; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=100000;V.l=79.9; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=500000;V.l=80.14; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=1000000;V.l=80.44; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=2500000;V.l=81.4; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=5000000;V.l=83.13; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=7500000;V.l=85.04; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=10000000;V.l=87.14; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=12500000;V.l=89.43; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=15000000;V.l=91.92; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=17500000;V.l=94.62; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=20000000;V.l=97.55; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=22500000;V.l=100.7; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=25000000;V.l=104.1; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=27500000;V.l=107.8; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=30000000;V.l=111.7; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=35000000;V.l=120.3; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=40000000;V.l=129.9; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=45000000;V.l=140.5; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=50000000;V.l=152; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=55000000;V.l=164.2; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=60000000;V.l=176.9; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=65000000;V.l=189.8; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=70000000;V.l=202.7; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=75000000;V.l=215.3; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=80000000;V.l=227.6; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=85000000;V.l=239.5; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=90000000;V.l=250.8; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=95000000;V.l=261.7; checkThermalConductivity.push_back(V);
V.T=873.15;V.p=100000000;V.l=272.1; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=100000;V.l=86.57; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=500000;V.l=86.8; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=1000000;V.l=87.1; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=2500000;V.l=88.02; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=5000000;V.l=89.67; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=7500000;V.l=91.49; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=10000000;V.l=93.48; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=12500000;V.l=95.63; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=15000000;V.l=97.96; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=17500000;V.l=100.5; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=20000000;V.l=103.2; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=22500000;V.l=106; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=25000000;V.l=109.1;  checkThermalConductivity.push_back(V);
V.T=923.15;V.p=27500000;V.l=112.3; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=30000000;V.l=115.8; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=35000000;V.l=123.2; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=40000000;V.l=131.4; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=45000000;V.l=140.3; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=50000000;V.l=149.7; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=55000000;V.l=159.7; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=60000000;V.l=169.9; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=65000000;V.l=180.4; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=70000000;V.l=190.9; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=75000000;V.l=201.2; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=80000000;V.l=211.4; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=85000000;V.l=221.1; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=90000000;V.l=230.5; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=95000000;V.l=239.5; checkThermalConductivity.push_back(V);
V.T=923.15;V.p=100000000;V.l=248; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=100000;V.l=93.38; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=500000;V.l=93.6; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=1000000;V.l=93.88; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=2500000;V.l=94.76; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=5000000;V.l=96.35; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=7500000;V.l=98.09;  checkThermalConductivity.push_back(V);
V.T=973.15;V.p=10000000;V.l=99.98; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=12500000;V.l=102; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=15000000;V.l=104.2; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=17500000;V.l=106.6; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=20000000;V.l=109.1; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=22500000;V.l=111.8; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=25000000;V.l=114.6; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=27500000;V.l=117.6; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=30000000;V.l=120.8; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=35000000;V.l=127.5; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=40000000;V.l=134.8; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=45000000;V.l=142.6; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=50000000;V.l=150.9; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=55000000;V.l=159.6; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=60000000;V.l=168.5; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=65000000;V.l=177.5; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=70000000;V.l=186.5; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=75000000;V.l=195.5; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=80000000;V.l=204.3; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=85000000;V.l=212.7; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=90000000;V.l=220.9; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=95000000;V.l=228.7; checkThermalConductivity.push_back(V);
V.T=973.15;V.p=100000000;V.l=236; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=100000;V.l=100.3; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=500000;V.l=100.5; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=1000000;V.l=100.8; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=2500000;V.l=101.6; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=5000000;V.l=103.1; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=7500000;V.l=104.8; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=10000000;V.l=106.6; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=12500000;V.l=108.5; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=15000000;V.l=110.6; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=17500000;V.l=112.8; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=20000000;V.l=115.2; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=22500000;V.l=117.7; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=25000000;V.l=120.3; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=27500000;V.l=123.1; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=30000000;V.l=126; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=35000000;V.l=132.2; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=40000000;V.l=138.9; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=45000000;V.l=146; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=50000000;V.l=153.4; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=55000000;V.l=161.2; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=60000000;V.l=169.1; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=65000000;V.l=177.2; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=70000000;V.l=185.2; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=75000000;V.l=193.2; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=80000000;V.l=201; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=85000000;V.l=208.6; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=90000000;V.l=215.9; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=95000000;V.l=222.9; checkThermalConductivity.push_back(V);
V.T=1023.15;V.p=100000000;V.l=229.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=100000;V.l=107.3; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=500000;V.l=107.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=1000000;V.l=107.8; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=2500000;V.l=108.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=5000000;V.l=109.9; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=7500000;V.l=111.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=10000000;V.l=113.2; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=12500000;V.l=115; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=15000000;V.l=116.9;  checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=17500000;V.l=119; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=20000000;V.l=121.2; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=22500000;V.l=123.6; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=25000000;V.l=126;  checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=27500000;V.l=128.6; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=30000000;V.l=131.3; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=35000000;V.l=137; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=40000000;V.l=143.2; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=45000000;V.l=149.7; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=50000000;V.l=156.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=55000000;V.l=163.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=60000000;V.l=170.7; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=65000000;V.l=177.9; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=70000000;V.l=185.2; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=75000000;V.l=192.4; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=80000000;V.l=199.5; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=85000000;V.l=206.4; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=90000000;V.l=213; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=95000000;V.l=219.4; checkThermalConductivity.push_back(V);
V.T=1073.15;V.p=100000000;V.l=225.4; checkThermalConductivity.push_back(V);


}

void SetVerificationData ()
{
	VerificationData V;

	// verification for Region 1 accorting to Table 5.
	V.T = 300.0; V.p = 3.0e6; V.v = 0.100215168e-2; V.h = 0.115331273e3; V.u = 0.112324818e3;
	V.s = 0.392294792; V.cp = 0.417301218e4; V.w = 0.150773921e4; V.r=1/V.v; V.cv=-1; check.push_back(V);
	V.T = 300.0; V.p = 80.0e6; V.v = 0.971180894e-3; V.h = 0.184142828e3; V.u = 0.106448356e3;
	V.s = 0.368563852; V.cp = 0.401008987e1; V.w = 0.163469054e4; V.r=1/V.v; V.cv=-1; check.push_back(V);
	V.T = 500.0; V.p = 3.0e6; V.v = 0.120241800e-2; V.h = 0.975542239e3; V.u = 0.971934985e3;
	V.s = 0.258041912e1; V.cp = 0.465580682e1; V.w = 0.124071337e4; V.r=1/V.v; V.cv=-1; check.push_back(V);

	// verification for Region 2 accorting to Table 15.
	V.T = 300; V.p = 0.0035e6; V.v = 0.394913866e2 ; V.h = 0.254991145e4; V.u = 0.241169160e4;
	V.s = 0.852238967e1; V.cp = 0.191300162e1; V.w = 0.427920172e3; V.r=1/V.v; V.cv=-1; check.push_back(V);
	V.T = 700; V.p = 0.0035e6; V.v = 0.923015898e2; V.h = 0.333568375e4; V.u = 0.301262819e4;
	V.s = 0.101749996e2; V.cp = 0.208141274e1; V.w = 0.644289068e3; V.r=1/V.v; V.cv=-1; check.push_back(V);
	V.T = 700; V.p = 30e6; V.v = 0.542946619e-2; V.h = 0.263149474e4; V.u = 0.246861076e4;
	V.s = 0.517540298e1; V.cp = 0.103505092e2; V.w = 0.480386523e3; V.r=1/V.v; V.cv=-1; check.push_back(V);

	// verification for Region 3 accorting to Table 33.
	V.T = 650;	V.p = 25.5837018e6;	V.v = 0.002;	V.h = 0.186343019e4;	V.u = 0.181226279e4;	V.s = 0.405427273e1;
	V.cp = 0.138935717e2;	V.w = 0.50200554e3;	V.r= 500;	V.cv=-1;	check.push_back(V);
	V.T = 650;	V.p = 22.2930643e6;	V.v = 0.005;	V.h = 0.237512401e4;	V.u = 0.226365868e4;	V.s = 0.485438792e1;
	V.cp = 0.446579342e2;	V.w = 0.383444594e3;	V.r=200;	V.cv=-1;	check.push_back(V);
	V.T = 750;	V.p = 78.3095639e6;	V.v = 0.002;	V.h = 0.225868845e4;	V.u = 0.210206932e4;	V.s = 0.446971906e1;
	V.cp = 0.634165359e1;	V.w = 0.760696041e3;	V.r=500;	V.cv=-1;	check.push_back(V);

	// verification for Region 5 accorting to Table 42.
	V.T = 1500;	V.p = 0.5e6;	V.v = 0.138455090e1;	V.h = 0.521976855e4;	V.u = 0.452749310e4;	V.s = 0.965408875e1;
	V.cp = 0.261609445e1;	V.w = 0.917068690e3;	V.r=1/V.v;	V.cv=-1;	check.push_back(V);
	V.T = 1500;	V.p = 30e6;	V.v = 0.230761299e-1;	V.h = 0.516723514e4;	V.u = 0.447495124e4;	V.s = 0.772970133e1;
	V.cp = 0.272724314e1;	V.w = 0.928548002e3;	V.r=1/V.v;	V.cv=-1;	check.push_back(V);
	V.T = 2000;	V.p = 30e6;	V.v = 0.311385219e-1;	V.h = 0.657122604e4;	V.u = 0.563707038e4;	V.s = 0.853640523e1;
	V.cp = 0.288569882e1;	V.w = 0.106736948e4;	V.r=1/V.v;	V.cv=-1;	check.push_back(V);

	V.T = -1; V.p=-1; V.v=-1; V.r=-1; V.h = -1; V.u = -1; V.s= -1; V.cp = -1; V.cv=-1; V.w=-1;

	V.p=100000;V.T=273.15;V.r=999.84;check.push_back(V);
	V.p=500000;V.T=273.15;V.r=1000;check.push_back(V);
	V.p=1000000;V.T=273.15;V.r=1000.3;check.push_back(V);
	V.p=2000000;V.T=273.15;V.r=1000.8;check.push_back(V);
	V.p=3000000;V.T=273.15;V.r=1001.3;check.push_back(V);
	V.p=4000000;V.T=273.15;V.r=1001.8;check.push_back(V);
	V.p=5000000;V.T=273.15;V.r=1002.3;check.push_back(V);
	V.p=6000000;V.T=273.15;V.r=1002.8;check.push_back(V);
	V.p=7000000;V.T=273.15;V.r=1003.3;check.push_back(V);
	V.p=8000000;V.T=273.15;V.r=1003.8;check.push_back(V);
	V.p=9000000;V.T=273.15;V.r=1004.3;check.push_back(V);
	V.p=10000000;V.T=273.15;V.r=1004.8;check.push_back(V);
	V.p=15000000;V.T=273.15;V.r=1007.3;check.push_back(V);
	V.p=20000000;V.T=273.15;V.r=1009.7;check.push_back(V);
	V.p=25000000;V.T=273.15;V.r=1012.2;check.push_back(V);
	V.p=30000000;V.T=273.15;V.r=1014.5;check.push_back(V);
	V.p=35000000;V.T=273.15;V.r=1016.9;check.push_back(V);
	V.p=40000000;V.T=273.15;V.r=1019.2;check.push_back(V);
	V.p=45000000;V.T=273.15;V.r=1021.5;check.push_back(V);
	V.p=50000000;V.T=273.15;V.r=1023.8;check.push_back(V);
	V.p=60000000;V.T=273.15;V.r=1028.3;check.push_back(V);
	V.p=70000000;V.T=273.15;V.r=1032.7;check.push_back(V);
	V.p=80000000;V.T=273.15;V.r=1037;check.push_back(V);
	V.p=100000;V.T=298.15;V.r=997.05;check.push_back(V);
	V.p=500000;V.T=298.15;V.r=997.23;check.push_back(V);
	V.p=1000000;V.T=298.15;V.r=997.45;check.push_back(V);
	V.p=2000000;V.T=298.15;V.r=997.9;check.push_back(V);
	V.p=3000000;V.T=298.15;V.r=998.35;check.push_back(V);
	V.p=4000000;V.T=298.15;V.r=998.8;check.push_back(V);
	V.p=5000000;V.T=298.15;V.r=999.24;check.push_back(V);
	V.p=6000000;V.T=298.15;V.r=999.69;check.push_back(V);
	V.p=7000000;V.T=298.15;V.r=1000.1;check.push_back(V);
	V.p=8000000;V.T=298.15;V.r=1000.6;check.push_back(V);
	V.p=9000000;V.T=298.15;V.r=1001;check.push_back(V);
	V.p=10000000;V.T=298.15;V.r=1001.5;check.push_back(V);
	V.p=15000000;V.T=298.15;V.r=1003.7;check.push_back(V);
	V.p=20000000;V.T=298.15;V.r=1005.8;check.push_back(V);
	V.p=25000000;V.T=298.15;V.r=1008;check.push_back(V);
	V.p=30000000;V.T=298.15;V.r=1010.1;check.push_back(V);
	V.p=35000000;V.T=298.15;V.r=1012.2;check.push_back(V);
	V.p=40000000;V.T=298.15;V.r=1014.3;check.push_back(V);
	V.p=45000000;V.T=298.15;V.r=1016.4;check.push_back(V);
	V.p=50000000;V.T=298.15;V.r=1018.4;check.push_back(V);
	V.p=60000000;V.T=298.15;V.r=1022.5;check.push_back(V);
	V.p=70000000;V.T=298.15;V.r=1026.4;check.push_back(V);
	V.p=80000000;V.T=298.15;V.r=1030.3;check.push_back(V);
	V.p=100000;V.T=323.15;V.r=988.05;check.push_back(V);
	V.p=500000;V.T=323.15;V.r=988.22;check.push_back(V);
	V.p=1000000;V.T=323.15;V.r=988.44;check.push_back(V);
	V.p=2000000;V.T=323.15;V.r=988.87;check.push_back(V);
	V.p=3000000;V.T=323.15;V.r=989.3;check.push_back(V);
	V.p=4000000;V.T=323.15;V.r=989.74;check.push_back(V);
	V.p=5000000;V.T=323.15;V.r=990.17;check.push_back(V);
	V.p=6000000;V.T=323.15;V.r=990.6;check.push_back(V);
	V.p=7000000;V.T=323.15;V.r=991.03;check.push_back(V);
	V.p=8000000;V.T=323.15;V.r=991.46;check.push_back(V);
	V.p=9000000;V.T=323.15;V.r=991.88;check.push_back(V);
	V.p=10000000;V.T=323.15;V.r=992.31;check.push_back(V);
	V.p=15000000;V.T=323.15;V.r=994.43;check.push_back(V);
	V.p=20000000;V.T=323.15;V.r=996.53;check.push_back(V);
	V.p=25000000;V.T=323.15;V.r=998.6;check.push_back(V);
	V.p=30000000;V.T=323.15;V.r=1000.7;check.push_back(V);
	V.p=35000000;V.T=323.15;V.r=1002.7;check.push_back(V);
	V.p=40000000;V.T=323.15;V.r=1004.7;check.push_back(V);
	V.p=45000000;V.T=323.15;V.r=1006.7;check.push_back(V);
	V.p=50000000;V.T=323.15;V.r=1008.7;check.push_back(V);
	V.p=60000000;V.T=323.15;V.r=1012.6;check.push_back(V);
	V.p=70000000;V.T=323.15;V.r=1016.4;check.push_back(V);
	V.p=80000000;V.T=323.15;V.r=1020.1;check.push_back(V);
	V.p=100000;V.T=348.15;V.r=974.86;check.push_back(V);
	V.p=500000;V.T=348.15;V.r=975.03;check.push_back(V);
	V.p=1000000;V.T=348.15;V.r=975.25;check.push_back(V);
	V.p=2000000;V.T=348.15;V.r=975.7;check.push_back(V);
	V.p=3000000;V.T=348.15;V.r=976.14;check.push_back(V);
	V.p=4000000;V.T=348.15;V.r=976.58;check.push_back(V);
	V.p=5000000;V.T=348.15;V.r=977.02;check.push_back(V);
	V.p=6000000;V.T=348.15;V.r=977.45;check.push_back(V);
	V.p=7000000;V.T=348.15;V.r=977.89;check.push_back(V);
	V.p=8000000;V.T=348.15;V.r=978.33;check.push_back(V);
	V.p=9000000;V.T=348.15;V.r=978.76;check.push_back(V);
	V.p=10000000;V.T=348.15;V.r=979.19;check.push_back(V);
	V.p=15000000;V.T=348.15;V.r=981.35;check.push_back(V);
	V.p=20000000;V.T=348.15;V.r=983.48;check.push_back(V);
	V.p=25000000;V.T=348.15;V.r=985.58;check.push_back(V);
	V.p=30000000;V.T=348.15;V.r=987.66;check.push_back(V);
	V.p=35000000;V.T=348.15;V.r=989.72;check.push_back(V);
	V.p=40000000;V.T=348.15;V.r=991.76;check.push_back(V);
	V.p=45000000;V.T=348.15;V.r=993.77;check.push_back(V);
	V.p=50000000;V.T=348.15;V.r=995.77;check.push_back(V);
	V.p=60000000;V.T=348.15;V.r=999.69;check.push_back(V);
	V.p=70000000;V.T=348.15;V.r=1003.5;check.push_back(V);
	V.p=80000000;V.T=348.15;V.r=1007.3;check.push_back(V);
	V.p=100000;V.T=373.15;V.r=0.5896;check.push_back(V);
	V.p=500000;V.T=373.15;V.r=958.54;check.push_back(V);
	V.p=1000000;V.T=373.15;V.r=958.77;check.push_back(V);
	V.p=2000000;V.T=373.15;V.r=959.24;check.push_back(V);
	V.p=3000000;V.T=373.15;V.r=959.71;check.push_back(V);
	V.p=4000000;V.T=373.15;V.r=960.17;check.push_back(V);
	V.p=5000000;V.T=373.15;V.r=960.64;check.push_back(V);
	V.p=6000000;V.T=373.15;V.r=961.1;check.push_back(V);
	V.p=7000000;V.T=373.15;V.r=961.56;check.push_back(V);
	V.p=8000000;V.T=373.15;V.r=962.02;check.push_back(V);
	V.p=9000000;V.T=373.15;V.r=962.47;check.push_back(V);
	V.p=10000000;V.T=373.15;V.r=962.93;check.push_back(V);
	V.p=15000000;V.T=373.15;V.r=965.2;check.push_back(V);
	V.p=20000000;V.T=373.15;V.r=967.43;check.push_back(V);
	V.p=25000000;V.T=373.15;V.r=969.64;check.push_back(V);
	V.p=30000000;V.T=373.15;V.r=971.82;check.push_back(V);
	V.p=35000000;V.T=373.15;V.r=973.97;check.push_back(V);
	V.p=40000000;V.T=373.15;V.r=976.1;check.push_back(V);
	V.p=45000000;V.T=373.15;V.r=978.19;check.push_back(V);
	V.p=50000000;V.T=373.15;V.r=980.27;check.push_back(V);
	V.p=60000000;V.T=373.15;V.r=984.34;check.push_back(V);
	V.p=70000000;V.T=373.15;V.r=988.32;check.push_back(V);
	V.p=80000000;V.T=373.15;V.r=992.22;check.push_back(V);
	V.p=100000;V.T=398.15;V.r=0.5503;check.push_back(V);
	V.p=500000;V.T=398.15;V.r=939.16;check.push_back(V);
	V.p=1000000;V.T=398.15;V.r=939.41;check.push_back(V);
	V.p=2000000;V.T=398.15;V.r=939.92;check.push_back(V);
	V.p=3000000;V.T=398.15;V.r=940.43;check.push_back(V);
	V.p=4000000;V.T=398.15;V.r=940.93;check.push_back(V);
	V.p=5000000;V.T=398.15;V.r=941.43;check.push_back(V);
	V.p=6000000;V.T=398.15;V.r=941.93;check.push_back(V);
	V.p=7000000;V.T=398.15;V.r=942.43;check.push_back(V);
	V.p=8000000;V.T=398.15;V.r=942.93;check.push_back(V);
	V.p=9000000;V.T=398.15;V.r=943.43;check.push_back(V);
	V.p=10000000;V.T=398.15;V.r=943.92;check.push_back(V);
	V.p=15000000;V.T=398.15;V.r=946.37;check.push_back(V);
	V.p=20000000;V.T=398.15;V.r=948.78;check.push_back(V);
	V.p=25000000;V.T=398.15;V.r=951.16;check.push_back(V);
	V.p=30000000;V.T=398.15;V.r=953.5;check.push_back(V);
	V.p=35000000;V.T=398.15;V.r=955.8;check.push_back(V);
	V.p=40000000;V.T=398.15;V.r=958.07;check.push_back(V);
	V.p=45000000;V.T=398.15;V.r=960.31;check.push_back(V);
	V.p=50000000;V.T=398.15;V.r=962.52;check.push_back(V);
	V.p=60000000;V.T=398.15;V.r=966.85;check.push_back(V);
	V.p=70000000;V.T=398.15;V.r=971.07;check.push_back(V);
	V.p=80000000;V.T=398.15;V.r=975.18;check.push_back(V);
	V.p=100000;V.T=423.15;V.r=0.5163;check.push_back(V);
	V.p=500000;V.T=423.15;V.r=917.02;check.push_back(V);
	V.p=1000000;V.T=423.15;V.r=917.3;check.push_back(V);
	V.p=2000000;V.T=423.15;V.r=917.87;check.push_back(V);
	V.p=3000000;V.T=423.15;V.r=918.43;check.push_back(V);
	V.p=4000000;V.T=423.15;V.r=919;check.push_back(V);
	V.p=5000000;V.T=423.15;V.r=919.56;check.push_back(V);
	V.p=6000000;V.T=423.15;V.r=920.11;check.push_back(V);
	V.p=7000000;V.T=423.15;V.r=920.67;check.push_back(V);
	V.p=8000000;V.T=423.15;V.r=921.22;check.push_back(V);
	V.p=9000000;V.T=423.15;V.r=921.77;check.push_back(V);
	V.p=10000000;V.T=423.15;V.r=922.32;check.push_back(V);
	V.p=15000000;V.T=423.15;V.r=925.03;check.push_back(V);
	V.p=20000000;V.T=423.15;V.r=927.69;check.push_back(V);
	V.p=25000000;V.T=423.15;V.r=930.3;check.push_back(V);
	V.p=30000000;V.T=423.15;V.r=932.86;check.push_back(V);
	V.p=35000000;V.T=423.15;V.r=935.38;check.push_back(V);
	V.p=40000000;V.T=423.15;V.r=937.86;check.push_back(V);
	V.p=45000000;V.T=423.15;V.r=940.3;check.push_back(V);
	V.p=50000000;V.T=423.15;V.r=942.7;check.push_back(V);
	V.p=60000000;V.T=423.15;V.r=947.39;check.push_back(V);
	V.p=70000000;V.T=423.15;V.r=951.94;check.push_back(V);
	V.p=80000000;V.T=423.15;V.r=956.36;check.push_back(V);
	V.p=100000;V.T=473.15;V.r=0.4603;check.push_back(V);
	V.p=500000;V.T=473.15;V.r=2.3528;check.push_back(V);
	V.p=1000000;V.T=473.15;V.r=4.8543;check.push_back(V);
	V.p=2000000;V.T=473.15;V.r=865.01;check.push_back(V);
	V.p=3000000;V.T=473.15;V.r=865.77;check.push_back(V);
	V.p=4000000;V.T=473.15;V.r=866.52;check.push_back(V);
	V.p=5000000;V.T=473.15;V.r=867.27;check.push_back(V);
	V.p=6000000;V.T=473.15;V.r=868.02;check.push_back(V);
	V.p=7000000;V.T=473.15;V.r=868.75;check.push_back(V);
	V.p=8000000;V.T=473.15;V.r=869.49;check.push_back(V);
	V.p=9000000;V.T=473.15;V.r=870.22;check.push_back(V);
	V.p=10000000;V.T=473.15;V.r=870.95;check.push_back(V);
	V.p=15000000;V.T=473.15;V.r=874.51;check.push_back(V);
	V.p=20000000;V.T=473.15;V.r=877.97;check.push_back(V);
	V.p=25000000;V.T=473.15;V.r=881.34;check.push_back(V);
	V.p=30000000;V.T=473.15;V.r=884.62;check.push_back(V);
	V.p=35000000;V.T=473.15;V.r=887.82;check.push_back(V);
	V.p=40000000;V.T=473.15;V.r=890.94;check.push_back(V);
	V.p=45000000;V.T=473.15;V.r=893.99;check.push_back(V);
	V.p=50000000;V.T=473.15;V.r=896.98;check.push_back(V);
	V.p=60000000;V.T=473.15;V.r=902.75;check.push_back(V);
	V.p=70000000;V.T=473.15;V.r=908.29;check.push_back(V);
	V.p=80000000;V.T=473.15;V.r=913.62;check.push_back(V);
	V.p=100000;V.T=523.15;V.r=0.4156;check.push_back(V);
	V.p=500000;V.T=523.15;V.r=2.1078;check.push_back(V);
	V.p=1000000;V.T=523.15;V.r=4.2967;check.push_back(V);
	V.p=2000000;V.T=523.15;V.r=8.9699;check.push_back(V);
	V.p=3000000;V.T=523.15;V.r=14.16;check.push_back(V);
	V.p=4000000;V.T=523.15;V.r=798.92;check.push_back(V);
	V.p=5000000;V.T=523.15;V.r=800.08;check.push_back(V);
	V.p=6000000;V.T=523.15;V.r=801.23;check.push_back(V);
	V.p=7000000;V.T=523.15;V.r=802.37;check.push_back(V);
	V.p=8000000;V.T=523.15;V.r=803.49;check.push_back(V);
	V.p=9000000;V.T=523.15;V.r=804.6;check.push_back(V);
	V.p=10000000;V.T=523.15;V.r=805.7;check.push_back(V);
	V.p=15000000;V.T=523.15;V.r=811.02;check.push_back(V);
	V.p=20000000;V.T=523.15;V.r=816.09;check.push_back(V);
	V.p=25000000;V.T=523.15;V.r=820.92;check.push_back(V);
	V.p=30000000;V.T=523.15;V.r=825.55;check.push_back(V);
	V.p=35000000;V.T=523.15;V.r=830;check.push_back(V);
	V.p=40000000;V.T=523.15;V.r=834.28;check.push_back(V);
	V.p=45000000;V.T=523.15;V.r=838.41;check.push_back(V);
	V.p=50000000;V.T=523.15;V.r=842.4;check.push_back(V);
	V.p=60000000;V.T=523.15;V.r=850.02;check.push_back(V);
	V.p=70000000;V.T=523.15;V.r=857.2;check.push_back(V);
	V.p=80000000;V.T=523.15;V.r=864;check.push_back(V);
	V.p=100000;V.T=573.15;V.r=0.379;check.push_back(V);
	V.p=500000;V.T=573.15;V.r=1.9135;check.push_back(V);
	V.p=1000000;V.T=573.15;V.r=3.8763;check.push_back(V);
	V.p=2000000;V.T=573.15;V.r=7.9681;check.push_back(V);
	V.p=3000000;V.T=573.15;V.r=12.319;check.push_back(V);
	V.p=4000000;V.T=573.15;V.r=16.987;check.push_back(V);
	V.p=5000000;V.T=573.15;V.r=22.052;check.push_back(V);
	V.p=6000000;V.T=573.15;V.r=27.631;check.push_back(V);
	V.p=7000000;V.T=573.15;V.r=33.905;check.push_back(V);
	V.p=8000000;V.T=573.15;V.r=41.186;check.push_back(V);
	V.p=9000000;V.T=573.15;V.r=713.07;check.push_back(V);
	V.p=10000000;V.T=573.15;V.r=715.29;check.push_back(V);
	V.p=15000000;V.T=573.15;V.r=725.55;check.push_back(V);
	V.p=20000000;V.T=573.15;V.r=734.71;check.push_back(V);
	V.p=25000000;V.T=573.15;V.r=743.01;check.push_back(V);
	V.p=30000000;V.T=573.15;V.r=750.64;check.push_back(V);
	V.p=35000000;V.T=573.15;V.r=757.72;check.push_back(V);
	V.p=40000000;V.T=573.15;V.r=764.34;check.push_back(V);
	V.p=45000000;V.T=573.15;V.r=770.57;check.push_back(V);
	V.p=50000000;V.T=573.15;V.r=776.46;check.push_back(V);
	V.p=60000000;V.T=573.15;V.r=787.38;check.push_back(V);
	V.p=70000000;V.T=573.15;V.r=797.36;check.push_back(V);
	V.p=80000000;V.T=573.15;V.r=806.58;check.push_back(V);


}

int main() {

	IF97 eos;


	SetVerificatioonDataThermalConductivity();
	double err = 0;
	for (size_t i=0; i<checkThermalConductivity.size(); i++)
	{
		double T = checkThermalConductivity[i].T;
		double p = checkThermalConductivity[i].p;
		double l = checkThermalConductivity[i].l*1e-3;
		double l_ = eos.ThermalConductivity(p,T);
		double sq = ((l-l_)/l)*((l-l_)/l);
		std::cout << i << " " << err << " " << err/i  << std::endl;
	}

	SetVerificationData ();
	size_t error_count = 0;
	size_t checkSize = check.size();


	for (size_t i=0; i<checkSize; i++)
	{
		double T= check[i].T;
		double p= check[i].p;
		double v_0 = check[i].v;
		double r_0 = check[i].r;
		double h_0 = check[i].h;
		double u_0 = check[i].u;
		double s_0 = check[i].s;
		double cp_0 = check[i].cp;
		double cv_0 = check[i].cv;
		double w_0 = check[i].w;

		double v = eos.SpecificVolume(p,T);
		double r = eos.Density(p,T);
		double h = eos.SpecificEnthalpy(p,T);
		double u = eos.SpecificInternalEnergy(p,T);
		double s = eos.SpecificEntropy(p,T);
		double cp = eos.SpecificIsobaricHeatcapacity(p,T);
		double cv = eos.SpecificIsochoricHeatcapacity(p,T);
		double w = eos.SpeedOfSound(p,T);

		double err_v = (v_0-v)/v_0;
		double err_r = (r_0-r)/r_0;
		double err_h = (h_0-h)/h_0;
		double err_u = (u_0-u)/u_0;
		double err_s = (s_0-s)/s_0;
		double err_cp = (cp_0-cp)/cp_0;
		double err_cv = (cv_0-cv)/cv_0;
		double err_w = (w_0-w)/w_0;

		std::cout.precision(16);

		if ((v_0 > 0)&&(err_v > 1e-6))
		{
			std::cout << "v, target   : " << v_0 << ", actual-value: " << v << " abs. Err: " << v_0-v << " rel.Err: " << err_v << std::endl;
			error_count ++;
		}
		if ((r_0 > 0)&&(err_r > 1e-3)){
			error_count ++;
			std::cout << "r, target : " << r_0 << ", value: " << r << " abs.Err: " << r_0-r << " rel.Err: " << err_r << std::endl;
			}
		if ((h_0 > 0)&&(err_h > 1e-3)){
			error_count ++;
			std::cout << "h, target : " << h_0 << ", value: " << h << " abs.Err: " << h_0-h << " rel.Err: " << err_h << std::endl;
		}
		if ((u_0 > 0)&&(err_u > 1e-3)){
			error_count ++;
			std::cout << "u, target : " << u_0 << ", value: " << u << " abs.Err: " << u_0-u << " rel.Err: " << err_u << std::endl;
		}
		if ((s_0 > 0)&&(err_s > 1e-3)){
			error_count ++;
			std::cout << "s, target : " << s_0 << ", value: " << s << " abs.Err: " << s_0-s << " rel.Err: " << err_s << std::endl;
		}
		if ((cp_0 > 0)&&(err_cp > 1e-3)){
			error_count ++;
			std::cout << "cp, target: " << cp_0 << ", value: " << cp << " abs.Err: " << cp_0-cp << " rel.Err: " << err_cp << std::endl;
		}
		if ((cv_0 > 0)&&(err_cv > 1e-3)){
			error_count ++;
			std::cout << "cv, target: " << cv_0 << ", value: " << cv << " abs.Err: " << cv_0-cv << " rel.Err: " << err_cv << std::endl;
		}
		if ((w_0 > 0)&&(err_w > 1e-3)){
			error_count ++;
			std::cout << "w, target : " << w_0 << ", value: " << w << " abs.Err: " << w_0-w << " rel.Err: " << err_w << std::endl;
		}



	}

	std::cout << error_count << " errors out of " << checkSize << " datasets. (" << (double)error_count/(double)checkSize*100. << "%)." << std::endl;




	std::cout << eos.SpecificIsobaricHeatcapacity(3000000,300) << std::endl;
	std::cout << eos.SpecificIsobaricHeatcapacity(80000000,300) << std::endl;
	std::cout << eos.SpecificIsobaricHeatcapacity(3000000,500) << std::endl;

	std::cout.precision(16);
	std::cout << eos.SpecificVolume(3500,300) << " " << eos.SpecificIsobaricHeatcapacity(3500,300) << std::endl;
	std::cout << eos.SpecificVolume(3500,700) << " " << eos.SpecificIsobaricHeatcapacity(3500,700) << std::endl;
	std::cout << eos.SpecificVolume(30e6,700) << " " << eos.SpecificIsobaricHeatcapacity(30e6,700) << std::endl;


	std::cout << eos.Density(0.255837018e8,650) << " " << 1/eos.Density(0.255837018e8,650)<< std::endl;
	std::cout << eos.Density(0.222930643e8,650) << " " << 1/eos.Density(0.222930643e8,650)<< std::endl;
	std::cout << eos.Density(0.783095639e8,750) << " " << 1/eos.Density(0.783095639e8,750)<< std::endl;



	std::cout << eos.Density(100000,300) << std::endl;
	std::cout << eos.Density(100000,500) << std::endl;
	std::cout << eos.Density(1000000,1200) << std::endl;




	return 0;
}




