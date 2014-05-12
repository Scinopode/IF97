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

#include "IAPWS-IF97.h"



const double IF97::nB23[5] = { 0.34805185628969e3, -.11671859879975e1, 0.10192970039326e-2, 0.57254459862746e3, 0.13918839778870e2};

const double IF97::nRegion1[34] = { 0.14632971213167, -0.84548187169114, -0.37563603672040e1, 0.33855169168385e1, -0.95791963387872,
		 0.15772038513228,    -0.16616417199501e-1,   0.81214629983568e-3,  0.28319080123804e-3,  -0.60706301565874e-3, -0.18990068218419e-1,
		-0.32529748770505e-1, -0.21841717175414e-1,  -0.52838357969930e-4, -0.47184321073267e-3,  -0.30001780793026e-3,  0.47661393906987e-4,
		-0.44141845330846e-5, -0.72694996297594e-15, -0.31679644845054e-4, -0.28270797985312e-5,  -0.85205128120103e-9, -0.22425281908000e-5,
		-0.65171222895601e-6, -0.14341729937924e-12, -0.40516996860117e-6, -0.12734301741641e-8,  -0.17424871230634e-9, -0.68762131295531e-18,
		 0.14478307828521e-19, 0.26335781662795e-22, -0.11947622640071e-22, 0.18228094581404e-23, -0.93537087292458e-25};

const double IF97::nRegion4[10] =  { 0.11670521452767e4, -0.72421316703206e6, -0.17073846940092e2, 0.12020824702470e5,
		-0.32325550322333e7, 0.14915108613530e2, -0.48232657361591e4, 0.40511340542057e6, -0.23855557567849, 0.65017534844798e3};

const double IF97::nRegion2[43] = {-0.17731742473213e-2, -0.17834862292358e-1, -0.45996013696365e-1, -0.57581259083432e-1,
		-0.50325278727930e-1,  -0.33032641670203e-4,  -0.18948987516315e-3,  -0.39392777243355e-2,  -0.43797295650573e-1,
		-0.26674547914087e-4,  0.20481737692309e-7,	0.43870667284435e-6,  -0.32277677238570e-4,  -0.15033924542148e-2,
		-0.40668253562649e-1,  -0.78847309559367e-9,	0.12790717852285e-7,  0.48225372718507e-6,  0.22922076337661e-5,
		-0.16714766451061e-10, -0.21171472321355e-2,	-0.23895741934104e2,   -0.59059564324270e-17, -0.12621808899101e-5,
		-0.38946842435739e-1,  0.11256211360459e-10, -0.82311340897998e1,   0.19809712802088e-7,  0.10406965210174e-18,
		-0.10234747095929e-12, -0.10018179379511e-8,	-0.80882908646985e-10, 0.10693031879409,     -0.33662250574171,
		0.89185845355421e-24, 0.30629316876232e-12,	-0.42002467698208e-5,  -0.59056029685639e-25, 0.37826947613457e-5,
		-0.12768608934681e-14, 0.73087610595061e-28,	0.55414715350778e-16, -0.94369707241210e-6};

const double IF97::n0Region2[9] = {-0.96927686500217e01, 0.10086655968018e02,-0.56087911283020e-2, 0.71452738081455e-1,-0.40710498223928,
		0.14240819171444e01,-0.43839511319450e01,-0.28408632460772, 0.21268463753307e-1};

const short IF97::IRegion1[34] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2,
		2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 8, 8, 21, 23, 29, 30, 31, 32};

const short IF97::JRegion1[34] = {-2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -1, 0, 1, 3, -3,
		0, 1, 3, 17, -4, 0, 6, -5, -2, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41};

const short IF97::IRegion2[43]= { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5,
		6, 6, 6, 7, 7, 7, 8, 8, 9, 10, 10, 10, 16, 16, 18, 20, 20, 20, 21, 22, 23, 24, 24, 24};

const short IF97::JRegion2[43] = { 0, 1, 2, 3, 6, 1, 2, 4, 7, 36, 0, 1, 3, 6, 35, 1, 2, 3, 7, 3,
		16, 35, 0, 11, 25, 8, 36, 13, 4, 10, 14, 29, 50, 57, 20, 35, 48, 21, 53, 39, 26, 40, 58};

const short IF97::J0Region2[9] = {0, 1, -5, -4, -3, -2, -1, 2, 3};


/*******************************************************************************************************
 * Empty constructor
 ******************************************************************************************************/
IF97::IF97(){}

short IF97::RegionSelection (const double p, const double T) const
{
	//Region 5:
	if ((T>=1073.15)&&(T<=2273.15)&&(p>=0)&&(p<=50e6))
		return 5;
	//Region 1:
	const double saturationPressure = SaturationPressure(T);
	if ((T>=273.15)&&(T<=623.15)&&(p>=saturationPressure)&&(p<=100e6))
		return 1;
	//Region 2:
	const double p_B23 = B23Equation_p(T);
	if (
			((T>=273.15)&&(T<=623.15)  && (p>=0) && (p<=saturationPressure)) ||
			((T>623.15) &&(T<=863.15)  && (p>0)  && (p<p_B23)) ||
			((T>863.15) &&(T<=1073.15) && (p>0)  && (p<100e6))	)
		return 2;
	//Region 3:
	const double T_B23 = B23Equation_T(p);
	if ((T>623.15)&&(T<T_B23)&&(p>=p_B23)&&(p<=100e6))
		return 3;

	return -1;
}

/**************************************************************************************************************
 *  The Saturation-Pressure Equation
 *  International Association for the Properties of water and Steam
 *  Industrial Formulation 1997
 *
 *  Revised Release, August 2007
 *  Author: NB, May 2014
 **************************************************************************************************************/
double IF97::SaturationPressure( const double T) const
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
double IF97::SaturationTemperature(const  double p) const
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
double IF97::B23Equation_p (const  double T) const
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
 *  Dimensionless Gibbs free energy for region 1
 *  First derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_p_region1(const double p, const double T) const
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
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 1
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_tt_region1(const double p, const double T) const
{
	double gamma_p = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma_p += nRegion1[i]*pow(7.1-pi, IRegion1[i])*JRegion1[i]*(JRegion1[i]-1.)*pow(tau-1.222, JRegion1[i]-2.);
	}

	return gamma_p;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - ideal part
 *  First derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_p_0_region2(const double p) const
{
	return p_star_Region2/p;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  first derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_p_r_region2(const double p, const double T) const
{
	double gamma_p = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;
	for (size_t i=0; i<43; i++)
	{
		gamma_p += nRegion2[i]*IRegion2[i]*pow(pi,IRegion2[i]-1)*pow(tau-0.5,JRegion2[i]);
	}
	return gamma_p;
}

/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - ideal part
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_tt_0_region2(const double T) const
{
	double gamma_p = 0;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<9; i++)
	{
		gamma_p += n0Region2[i]*J0Region2[i]*(J0Region2[i]-1)*pow(tau, J0Region2[i]-2);
	}

	return gamma_p;
}

/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_tt_r_region2(const double p, const double T) const
{
	double gamma_p = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<43; i++)
	{
		gamma_p += nRegion2[i]*pow(pi, IRegion2[i])*JRegion2[i]*(JRegion2[i]-1)*pow(tau-0.5, JRegion2[i]-2.);
	}

	return gamma_p;
}
/**************************************************************************************************************
 *  Density Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::Density( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
		return 1/(specificGasConstant*T/p_star_Region1*gamma_p_region1(p,T));
		break;
	case 2:
		return 1/(specificGasConstant*T/p_star_Region2*(gamma_p_0_region2(p)+gamma_p_r_region2(p,T)));
		break;
	default: return -1;
	}

}

/**************************************************************************************************************
 *  Specific Volume Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpecificVolume( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
		return specificGasConstant*T/p_star_Region1*gamma_p_region1(p,T);
		break;
	case 2:
		return specificGasConstant*T/p_star_Region2*(gamma_p_0_region2(p)+gamma_p_r_region2(p,T));
		break;
	default: return -1;
	}

}

/**************************************************************************************************************
 *  Specific isobaric heat capacity
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpecificIsobaricHeatcapacity( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
		return -(specificGasConstant*(T_star_Region1/T)*(T_star_Region1/T)*gamma_tt_region1(p, T));
		break;
	case 2:
		return -(specificGasConstant*(T_star_Region2/T)*(T_star_Region2/T)*(gamma_tt_0_region2(T)+gamma_tt_r_region2(p,T)));
		break;
	default: return -1;
	}

}
