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

std::vector<VerificationData> check;

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




