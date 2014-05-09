/******************************************************************************
 *
 * Name        : IAPWS-IF97
 * Author      : Norbert Boettcher
 *             : May 2014
 * Description : Industrial Formulation 1997 of the Thermodynamic Properties of
 *               Water and Steam
 ******************************************************************************/

#include <iostream>
#include <numeric>
#include <cassert>
#include <math.h>

class IF97{
private:
	void GetIF97Parameters();
	double nB23[5];

	double nRegion1[34];
	double IRegion1[34];
	double JRegion1[34];

	double nRegion2[43];
	double IRegion2[43];
	double JRegion2[43];

	double nRegion4[10];

	static const double a[3];

	static const double specificGasConstant = 0.461526e3; // J/kg/K
	static const double criticalTemperature = 647.096; //K
	static const double criticalPressure = 22.064; // MPa
	static const double criticalDensity = 322; // kg/m^3

	static const double tripplePointTemperature = 273.16; //K
	static const double tripplePointpressure = 611.657; // Pa

	static const double p_star_Region1 = 16.53e6; // Pa
	static const double p_star_Region2 = 1.0e6; // Pa
	static const double p_star_Region4 = 1.0e6; // Pa


	static const double T_star_Region1 = 1386; // Pa
	static const double T_star_Region2 = 540; // Pa
	static const double T_star_Region4 = 1; // Pa

	// Gibbs energy function and its derivatives for Region 1
	double gamma_region1 (double p, double T);
	double gamma_p_region1 (double p, double T);
	double gamma_pp_region1 (double p, double T);
	double gamma_t_region1 (double p, double T);
	double gamma_tt_region1 (double p, double T);
	double gamma_pt_region1 (double p, double T);


	// Gibbs energy function and its derivatives for Region 2
	double gamma_0_region2 (double p, double T);
	double gamma_p_0_region2 (double p);
	double gamma_pp_0_region2 (double p);
	double gamma_t_0_region2 (double T);
	double gamma_tt_0_region2 (double T);
	double gamma_pt_0_region2 (void);

	double gamma_r_region2 (double p, double T);
	double gamma_p_r_region2 (double p, double T);
	double gamma_pp_r_region2 (double p, double T);
	double gamma_t_r_region2 (double p, double T);
	double gamma_tt_r_region2 (double p, double T);
	double gamma_pt_r_region2 (double p, double T);


	short RegionSelection (double p, double T);

	// curves determining the border between region 2 and region 3
	double B23Equation_T (const double T) const;
	double B23Equation_p (double p);

public:
	IF97()
	{
		GetIF97Parameters();
	}
	double Density( double p, double T);

	double SpecificEntropy ( double p, double T);
	double SpecificInternalEnergy ( double p, double T);
	double SpecificEnthalpy ( double p, double T);
	double SpecificIsobaricHeatcapacity ( double p, double T);
	double SpecificIsochoricHeatcapacity ( double p, double T);
	double SpeedOfSound ( double p, double T);



	double SpecificVolume( double p, double T);

	double SaturationPressure (double T);
	double SaturationTemperature (double p);


};

const double IF97::a[3]={0,0,0};


short IF97::RegionSelection (double p, double T)
{
	short Region = -1;
	const double saturationPressure = SaturationPressure(T);

	if ((T>=273.15)&&(T<=623.15))
	{
		if ((p>=saturationPressure)&&(p<=100e6))
			return 1;
		else if ((p>0)&&(p<=saturationPressure))
			Region = 2;
	}
	else if ((T>623.15)&&(T<=863.15))
	{
		if ((p>0)&&(p<=B23Equation_p(T)))
			Region = 2;
	}
	else if ((T>863.15)&&(T<=1073.15))
	{
		if ((p>0)&&(p<=100e6))
			Region = 2;
	}
	else if ((T>=1073.15)&&(T<=2273.15))
	{
		if ((p>0)&&(p<=50e6))
			Region = 5;
	}

	return Region;
}

void IF97::GetIF97Parameters()
{

	nB23[0]=0.34805185628969e3;
	nB23[1]=-.11671859879975e1;
	nB23[2]=0.10192970039326e-2;
	nB23[3]=0.57254459862746e3;
	nB23[4]=0.13918839778870e2;

	nRegion1[0] = 0.14632971213167;
	nRegion1[1] = -0.84548187169114;
	nRegion1[2] = -0.37563603672040e1;
	nRegion1[3] = 0.33855169168385e1;
	nRegion1[4] = -0.95791963387872;
	nRegion1[5] = 0.15772038513228;
	nRegion1[6] = -0.16616417199501e-1;
	nRegion1[7] = 0.81214629983568e-3;
	nRegion1[8] = 0.28319080123804e-3;
	nRegion1[9] = -0.60706301565874e-3;
	nRegion1[10] = -0.18990068218419e-1;
	nRegion1[11] = -0.32529748770505e-1;
	nRegion1[12] = -0.21841717175414e-1;
	nRegion1[13] = -0.52838357969930e-4;
	nRegion1[14] = -0.47184321073267e-3;
	nRegion1[15] = -0.30001780793026e-3;
	nRegion1[16] = 0.47661393906987e-4;
	nRegion1[17] = -0.44141845330846e-5;
	nRegion1[18] = -0.72694996297594e-15;
	nRegion1[19] = -0.31679644845054e-4;
	nRegion1[20] = -0.28270797985312e-5;
	nRegion1[21] = -0.85205128120103e-9;
	nRegion1[22] = -0.22425281908000e-5;
	nRegion1[23] = -0.65171222895601e-6;
	nRegion1[24] = -0.14341729937924e-12;
	nRegion1[25] = -0.40516996860117e-6;
	nRegion1[26] = -0.12734301741641e-8;
	nRegion1[27] = -0.17424871230634e-9;
	nRegion1[28] = -0.68762131295531e-18;
	nRegion1[29] = 0.14478307828521e-19;
	nRegion1[30] = 0.26335781662795e-22;
	nRegion1[31] = -0.11947622640071e-22;
	nRegion1[32] = 0.18228094581404e-23;
	nRegion1[33] = -0.93537087292458e-25;

	IRegion1[0] = 0.;
	IRegion1[1] = 0.;
	IRegion1[2] = 0.;
	IRegion1[3] = 0.;
	IRegion1[4] = 0.;
	IRegion1[5] = 0.;
	IRegion1[6] = 0.;
	IRegion1[7] = 0.;
	IRegion1[8] = 1.;
	IRegion1[9] = 1.;
	IRegion1[10] = 1.;
	IRegion1[11] = 1.;
	IRegion1[12] = 1.;
	IRegion1[13] = 1.;
	IRegion1[14] = 2.;
	IRegion1[15] = 2.;
	IRegion1[16] = 2.;
	IRegion1[17] = 2.;
	IRegion1[18] = 2.;
	IRegion1[19] = 3.;
	IRegion1[20] = 3.;
	IRegion1[21] = 3.;
	IRegion1[22] = 4.;
	IRegion1[23] = 4.;
	IRegion1[24] = 4.;
	IRegion1[25] = 5.;
	IRegion1[26] = 8.;
	IRegion1[27] = 8.;
	IRegion1[28] = 21.;
	IRegion1[29] = 23.;
	IRegion1[30] = 29.;
	IRegion1[31] = 30.;
	IRegion1[32] = 31.;
	IRegion1[33] = 32.;

	JRegion1[0] = -2.;
	JRegion1[1] = -1.;
	JRegion1[2] = 0.;
	JRegion1[3] = 1.;
	JRegion1[4] = 2.;
	JRegion1[5] = 3.;
	JRegion1[6] = 4.;
	JRegion1[7] = 5.;
	JRegion1[8] = -9.;
	JRegion1[9] = -7.;
	JRegion1[10] = -1.;
	JRegion1[11] = 0.;
	JRegion1[12] = 1.;
	JRegion1[13] = 3.;
	JRegion1[14] = -3.;
	JRegion1[15] = 0.;
	JRegion1[16] = 1.;
	JRegion1[17] = 3.;
	JRegion1[18] = 17.;
	JRegion1[19] = -4.;
	JRegion1[20] = 0.;
	JRegion1[21] = 6.;
	JRegion1[22] = -5.;
	JRegion1[23] = -2.;
	JRegion1[24] = 10.;
	JRegion1[25] = -8.;
	JRegion1[26] = -11.;
	JRegion1[27] = -6.;
	JRegion1[28] = -29.;
	JRegion1[29] = -31.;
	JRegion1[30] = -38.;
	JRegion1[31] = -39.;
	JRegion1[32] = -40.;
	JRegion1[33] = -41.;


	IRegion2[0]= 1;
	IRegion2[1]= 1;
	IRegion2[2]= 1;
	IRegion2[3]= 1;
	IRegion2[4]= 1;
	IRegion2[5]= 2;
	IRegion2[6]= 2;
	IRegion2[7]= 2;
	IRegion2[8]= 2;
	IRegion2[9]= 2;
	IRegion2[10]= 3;
	IRegion2[11]= 3;
	IRegion2[12]= 3;
	IRegion2[13]= 3;
	IRegion2[14]= 3;
	IRegion2[15]= 4;
	IRegion2[16]= 4;
	IRegion2[17]= 4;
	IRegion2[18]= 5;
	IRegion2[19]= 6;
	IRegion2[20]= 6;
	IRegion2[21]= 6;
	IRegion2[22]= 7;
	IRegion2[23]= 7;
	IRegion2[24]= 7;
	IRegion2[25]= 8;
	IRegion2[26]= 8;
	IRegion2[27]= 9;
	IRegion2[28]= 10;
	IRegion2[29]= 10;
	IRegion2[30]= 10;
	IRegion2[31]= 16;
	IRegion2[32]= 16;
	IRegion2[33]= 18;
	IRegion2[34]= 20;
	IRegion2[35]= 20;
	IRegion2[36]= 20;
	IRegion2[37]= 21;
	IRegion2[38]= 22;
	IRegion2[39]= 23;
	IRegion2[40]= 24;
	IRegion2[41]= 24;
	IRegion2[42]= 24;


	JRegion2[0] = 0;
	JRegion2[1] = 1;
	JRegion2[2] = 2;
	JRegion2[3] = 3;
	JRegion2[4] = 6;
	JRegion2[5] = 1;
	JRegion2[6] = 2;
	JRegion2[7] = 4;
	JRegion2[8] = 7;
	JRegion2[9] = 36;
	JRegion2[10] = 0;
	JRegion2[11] = 1;
	JRegion2[12] = 3;
	JRegion2[13] = 6;
	JRegion2[14] = 35;
	JRegion2[15] = 1;
	JRegion2[16] = 2;
	JRegion2[17] = 3;
	JRegion2[18] = 7;
	JRegion2[19] = 3;
	JRegion2[20] = 16;
	JRegion2[21] = 35;
	JRegion2[22] = 0;
	JRegion2[23] = 11;
	JRegion2[24] = 25;
	JRegion2[25] = 8;
	JRegion2[26] = 36;
	JRegion2[27] = 13;
	JRegion2[28] = 4;
	JRegion2[29] = 10;
	JRegion2[30] = 14;
	JRegion2[31] = 29;
	JRegion2[32] = 50;
	JRegion2[33] = 57;
	JRegion2[34] = 20;
	JRegion2[35] = 35;
	JRegion2[36] = 48;
	JRegion2[37] = 21;
	JRegion2[38] = 53;
	JRegion2[39] = 39;
	JRegion2[40] = 26;
	JRegion2[41] = 40;
	JRegion2[42] = 58;

	nRegion2[0] = 0.17731742473213e-2;
	nRegion2[1] = 0.17834862292358e-1;
	nRegion2[2] = 0.45996013696365e-1;
	nRegion2[3] = 0.57581259083432e-1;
	nRegion2[4] = 0.50325278727930e-1;
	nRegion2[5] = 0.33032641670203e-4;
	nRegion2[6] = 0.18948987516315e-3;
	nRegion2[7] = 0.39392777243355e-2;
	nRegion2[8] = 0.43797295650573e-1;
	nRegion2[9] = 0.26674547914087e-4;
	nRegion2[10] = 0.20481737692309e-7;
	nRegion2[11] = 0.43870667284435e-6;
	nRegion2[12] = 0.32277677238570e-4;
	nRegion2[13] = 0.15033924542148e-2;
	nRegion2[14] = 0.40668253562649e-1;
	nRegion2[15] = 0.78847309559367e-9;
	nRegion2[16] = 0.12790717852285e-7;
	nRegion2[17] = 0.48225372718507e-6;
	nRegion2[18] = 0.22922076337661e-5;
	nRegion2[19] = 0.16714766451061e-10;
	nRegion2[20] = 0.21171472321355e-2;
	nRegion2[21] = 0.23895741934104e2;
	nRegion2[22] = 0.59059564324270e-17;
	nRegion2[23] = 0.12621808899101e-5;
	nRegion2[24] = 0.38946842435739e-1;
	nRegion2[25] = 0.11256211360459e-10;
	nRegion2[26] = 0.82311340897998e1;
	nRegion2[27] = 0.19809712802088e-7;
	nRegion2[28] = 0.10406965210174e-18;
	nRegion2[29] = 0.10234747095929e-12;
	nRegion2[30] = 0.10018179379511e-8;
	nRegion2[31] = 0.80882908646985e-10;
	nRegion2[32] = 0.10693031879409;
	nRegion2[33] = 0.33662250574171;
	nRegion2[34] = 0.89185845355421e-24;
	nRegion2[35] = 0.30629316876232e-12;
	nRegion2[36] = 0.42002467698208e-5;
	nRegion2[37] = 0.59056029685639e-25;
	nRegion2[38] = 0.37826947613457e-5;
	nRegion2[39] = 0.12768608934681e-14;
	nRegion2[40] = 0.73087610595061e-28;
	nRegion2[41] = 0.55414715350778e-16;
	nRegion2[42] = 0.94369707241210e-6;

	nRegion4[0] =  0.11670521452767e4;
	nRegion4[1] = -0.72421316703206e6;
	nRegion4[2] = -0.17073846940092e2;
	nRegion4[3] =  0.12020824702470e5;
	nRegion4[4] = -0.32325550322333e7;
	nRegion4[5] =  0.14915108613530e2;
	nRegion4[6] = -0.48232657361591e4;
	nRegion4[7] =  0.40511340542057e6;
	nRegion4[8] = -0.23855557567849;
	nRegion4[9] =  0.65017534844798e3;

}

/**************************************************************************************************************
 *  The Saturation-Pressure Equation
 *  International Association for the Properties of water and Steam
 *  Industrial Formulation 1997
 *
 *  Revised Release, August 2007
 *  Author: NB, May 2014
 **************************************************************************************************************/
double IF97::SaturationPressure( double T)
{
	if ((T<273.15)||(T>647.096))
		return -1;

	const double theta = T/T_star_Region4+nRegion4[8]/((T/T_star_Region4)-nRegion4[9]);

	const double A = theta*theta+nRegion4[0]*theta+nRegion4[1];
	const double B = nRegion4[2]*theta*theta + nRegion4[3]*theta + nRegion4[4];
	const double C = nRegion4[5]*theta*theta + nRegion4[6]*theta + nRegion4[7];;

	const double saturationPressure = pow(2*C/(-B+sqrt(B*B-4*A*C)), (int)4);

	return saturationPressure*1e6; // Saturation pressure in Pa
}

/**************************************************************************************************************
 *  The Saturation-Temperature Equation (Backward Equation)
 *  International Association for the Properties of water and Steam
 *  Industrial Formulation 1997
 *
 *  Revised Release, August 2007
 *  Author: NB, May 2014
 **************************************************************************************************************/
double IF97::SaturationTemperature( double p)
{
	if ((p>=611.213)&&(p<=22064000.0))
	{
		double beta = pow(p/p_star_Region4,0.25);

		double E = beta*beta + nRegion4[2]*beta + nRegion4[5];
		double F = nRegion4[0]*beta*beta + nRegion4[3]*beta + nRegion4[6];
		double G = nRegion4[1]*beta*beta + nRegion4[4]*beta + nRegion4[7];

		double D = 2*G/(-F-sqrt(F*F-4*E*G));

		double saturationTemperature = 0.5*(nRegion4[9]+D-sqrt((nRegion4[9]+D)*(nRegion4[9]+D)-4*(nRegion4[8]+nRegion4[9]*D)));

		return saturationTemperature;
	}
	else
		return -1; // invalid pressure range
}


/**************************************************************************************************************
 *  Auxiliary Equation for the boundary between region 2 and region 3
 *  International Association for the Properties of water and Steam
 *  Industrial Formulation 1997
 *
 *	pressure version
 *  Revised Release, August 2007
 *  Author: NB, May 2014
 **************************************************************************************************************/
double IF97::B23Equation_p ( double T)
{
	return (nB23[0]+nB23[1]*T+nB23[2]*T*T) * 1e6;  // Pressure in Pa
}
/**************************************************************************************************************
 *  Auxiliary Equation for the boundary between region 2 and region 3
 *  International Association for the Properties of water and Steam
 *  Industrial Formulation 1997
 *
 *	temperature version
 *  Revised Release, August 2007
 *  Author: NB, May 2014
 **************************************************************************************************************/
double IF97::B23Equation_T (const  double p) const
{
	return nB23[3]+sqrt((p-nB23[4])/nB23[2]);  // temperature in K
}

/**************************************************************************************************************
 *  Dimensionless Gibbs free energy gamma for region 1
 *  International Association for the Properties of water and Steam
 *  Industrial Formulation 1997
 *
 *	temperature version
 *  Revised Release, August 2007
 *  Author: NB, May 2014
 **************************************************************************************************************/

double IF97::gamma_p_region1(double p, double T)
{
	double gamma_p = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma_p += -nRegion1[i]*IRegion1[i]*pow(7.1-pi, IRegion1[i]-1)*pow(tau-1.222, JRegion1[i]);
	}

	return gamma_p;
}

double IF97::gamma_p_0_region2(double p)
{
	return p_star_Region2/p;
}

double IF97::gamma_p_r_region2(double p, double T)
{
	double gamma_p = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;
	for (size_t i=0; i<34; i++)
	{
		gamma_p += nRegion2[i]*IRegion2[i]*pow(pi,IRegion2[i]-1)*pow(tau-0.5,JRegion1[i]);
	}
	return gamma_p;
}


double IF97::Density( double p, double T)
{
	short Region = RegionSelection(p,T);
	assert(Region==1||Region==2);

	double density = -1;
	switch (Region)
	{
	case 1:
		density = 1/(specificGasConstant*T/p_star_Region1*gamma_p_region1(p,T));
		break;
	case 2:
		density = 1/(specificGasConstant*T/p_star_Region1*(gamma_p_0_region2(p)+gamma_p_r_region2(p,T)));
		break;
	default: return -1;
	}

    return density;
}



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
