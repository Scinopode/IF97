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
#include <functional>

#include "Iterators.h"
#include "IAPWS-IF97.h"



const double IF97::nB23[5] = { 0.34805185628969e3, -.11671859879975e1, 0.10192970039326e-2, 0.57254459862746e3, 0.13918839778870e2};

const double IF97::nRegion1[34] = { 0.14632971213167, -0.84548187169114, -0.37563603672040e1, 0.33855169168385e1, -0.95791963387872,
		0.15772038513228,    -0.16616417199501e-1,   0.81214629983568e-3,  0.28319080123804e-3,  -0.60706301565874e-3, -0.18990068218419e-1,
		-0.32529748770505e-1, -0.21841717175414e-1,  -0.52838357969930e-4, -0.47184321073267e-3,  -0.30001780793026e-3,  0.47661393906987e-4,
		-0.44141845330846e-5, -0.72694996297594e-15, -0.31679644845054e-4, -0.28270797985312e-5,  -0.85205128120103e-9, -0.22425281908000e-5,
		-0.65171222895601e-6, -0.14341729937924e-12, -0.40516996860117e-6, -0.12734301741641e-8,  -0.17424871230634e-9, -0.68762131295531e-18,
		0.14478307828521e-19, 0.26335781662795e-22, -0.11947622640071e-22, 0.18228094581404e-23, -0.93537087292458e-25};
const double IF97::n0Region2[9] = {-0.96927686500217e01, 0.10086655968018e02,-0.56087911283020e-2, 0.71452738081455e-1,-0.40710498223928,
		0.14240819171444e01,-0.43839511319450e01,-0.28408632460772, 0.21268463753307e-1};
const double IF97::nRegion2[43] = {-0.17731742473213e-2, -0.17834862292358e-1, -0.45996013696365e-1, -0.57581259083432e-1,
		-0.50325278727930e-1,  -0.33032641670203e-4,  -0.18948987516315e-3,  -0.39392777243355e-2,  -0.43797295650573e-1,
		-0.26674547914087e-4,  0.20481737692309e-7,	0.43870667284435e-6,  -0.32277677238570e-4,  -0.15033924542148e-2,
		-0.40668253562649e-1,  -0.78847309559367e-9,	0.12790717852285e-7,  0.48225372718507e-6,  0.22922076337661e-5,
		-0.16714766451061e-10, -0.21171472321355e-2,	-0.23895741934104e2,   -0.59059564324270e-17, -0.12621808899101e-5,
		-0.38946842435739e-1,  0.11256211360459e-10, -0.82311340897998e1,   0.19809712802088e-7,  0.10406965210174e-18,
		-0.10234747095929e-12, -0.10018179379511e-8,	-0.80882908646985e-10, 0.10693031879409,     -0.33662250574171,
		0.89185845355421e-24, 0.30629316876232e-12,	-0.42002467698208e-5,  -0.59056029685639e-25, 0.37826947613457e-5,
		-0.12768608934681e-14, 0.73087610595061e-28,	0.55414715350778e-16, -0.94369707241210e-6};
const double IF97::nRegion3[40] = { 0.10658070028513e1,-0.15732845290239e2, 0.20944396974307e2,-0.76867707878716e1,
		0.26185947787954e1,-0.28080781148620e1, 0.12053369696517e1,-0.84566812812502e-2,-0.12654315477714e1,-0.11524407806681e1,
		0.88521043984318,-0.64207765181607, 0.38493460186671,-0.85214708824206, 0.48972281541877e1,-0.30502617256965e1, 0.39420536879154e-1,
		0.12558408424308,-0.27999329698710,0.13899799569460e1,-0.20189915023570e1,-0.82147637173963e-2,-0.47596035734923, 0.43984074473500e-1,
		-0.44476435428739, 0.90572070719733, 0.70522450087967, 0.10770512626332,-0.32913623258954,-0.50871062041158,-0.22175400873096e-1,
		0.94260751665092e-1, 0.16436278447961,-0.13503372241348e-1,-0.14834345352472e-1, 0.57922953628084e-3, 0.32308904703711e-2, 0.80964802996215e-4,
		-0.16557679795037e-3,-0.44923899061815e-4};
const double IF97::nRegion4[10] =  { 0.11670521452767e4, -0.72421316703206e6, -0.17073846940092e2, 0.12020824702470e5,
		-0.32325550322333e7, 0.14915108613530e2, -0.48232657361591e4, 0.40511340542057e6, -0.23855557567849, 0.65017534844798e3};
const double IF97::n0Region5[6] = {-0.13179983674201e2,0.68540841634434e1,-0.24805148933466e-1,0.36901534980333,-0.31161318213925e1,-0.32961626538917};
const double IF97::nRegion5[6] = {0.15736404855259e-2,0.90153761673944e-3,-0.50270077677648e-2,0.22440037409485e-5,-0.41163275453471e-5,0.37919454822955e-7};

const short IF97::IRegion1[34] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2,
		2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 8, 8, 21, 23, 29, 30, 31, 32};
const short IF97::IRegion2[43]= { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5,
		6, 6, 6, 7, 7, 7, 8, 8, 9, 10, 10, 10, 16, 16, 18, 20, 20, 20, 21, 22, 23, 24, 24, 24};
const short IF97::IRegion3[40]= { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3,
		3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 8, 9, 9, 10, 10, 11};
const short IF97::IRegion5[6]= {1, 1, 1, 2, 2, 3};

const short IF97::JRegion1[34] = {-2, -1, 0, 1, 2, 3, 4, 5, -9, -7, -1, 0, 1, 3, -3,
		0, 1, 3, 17, -4, 0, 6, -5, -2, 10, -8, -11, -6, -29, -31, -38, -39, -40, -41};
const short IF97::JRegion2[43] = { 0, 1, 2, 3, 6, 1, 2, 4, 7, 36, 0, 1, 3, 6, 35, 1, 2, 3, 7, 3,
		16, 35, 0, 11, 25, 8, 36, 13, 4, 10, 14, 29, 50, 57, 20, 35, 48, 21, 53, 39, 26, 40, 58};
const short IF97::JRegion3[40] = { 0, 0, 1, 2, 7, 10, 12, 23, 2, 6, 15, 17, 0, 2, 6, 7, 22, 26, 0, 2, 4,
		16, 26, 0, 2, 4, 26, 1, 3, 26, 0, 2, 26, 2, 26, 2, 26, 0, 1, 26};
const short IF97::J0Region2[9] = {0, 1, -5, -4, -3, -2, -1, 2, 3};
const short IF97::J0Region5[6]= {0, 1, -3, -2, -1, 2};
const short IF97::JRegion5[6]= {1, 2, 3, 3, 9, 7};

const double IF97::specificGasConstant = 0.461526e3; // J/kg/K
const double IF97::criticalTemperature = 647.096; //K
const double IF97::criticalPressure = 22.064; // MPa
const double IF97::criticalDensity = 322; // kg/m^3

const double IF97::tripplePointTemperature = 273.16; //K
const double IF97::tripplePointpressure = 611.657; // Pa

const double IF97::p_star_Region1 = 16.53e6; // Pa
const double IF97::p_star_Region2 = 1.0e6; // Pa
const double IF97::p_star_Region4 = 1.0e6; // Pa
const double IF97::p_star_Region5 = 1.0e6; // Pa

const double IF97::T_star_Region1 = 1386; // K
const double IF97::T_star_Region2 = 540; // K
const double IF97::T_star_Region4 = 1; // K
const double IF97::T_star_Region5 = 1000; // K


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
	if ((T>=273.15)&&(T<=623.15)&&(p>=saturationPressure)&&(p<=100.0e6))
		return 1;
	//Region 2:
	const double p_B23 = B23Equation_p(T);
	if (
			((T>=273.15)&&(T<=623.15)  && (p>=0) && (p<=saturationPressure)) ||
			((T>623.15) &&(T<=863.15)  && (p>0)  && (p<p_B23)) ||
			((T>863.15) &&(T<=1073.15) && (p>0)  && (p<=100.0e6))	)
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
	return nB23[3]+sqrt(((p/1.0e6)-nB23[4])/nB23[2]);  // temperature in K
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 1
 *  Basic Equation
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_region1(const double p, const double T) const
{
	double gamma = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma += nRegion1[i]*pow(7.1-pi, IRegion1[i])*pow(tau-1.222, JRegion1[i]);
	}

	return gamma;
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
 *  First derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_t_region1(const double p, const double T) const
{
	double gamma_t = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma_t += nRegion1[i]*pow(7.1-pi, IRegion1[i])*JRegion1[i]*pow(tau-1.222, JRegion1[i]-1);
	}

	return gamma_t;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 1
 *  second derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_pp_region1(const double p, const double T) const
{
	double gamma_pp = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma_pp += nRegion1[i]*IRegion1[i]*(IRegion1[i]-1)*pow(7.1-pi, IRegion1[i]-2)*pow(tau-1.222, JRegion1[i]);
	}

	return gamma_pp;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 1
 *  Second derivative with respect to specific pressure and temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_pt_region1(const double p, const double T) const
{
	double gamma_pt = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma_pt += -nRegion1[i]*IRegion1[i]*pow(7.1-pi, IRegion1[i]-1)*JRegion1[i]*pow(tau-1.222, JRegion1[i]-1);
	}

	return gamma_pt;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 1
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_tt_region1(const double p, const double T) const
{
	double gamma_tt = 0;
	double pi = p/p_star_Region1;
	double tau = T_star_Region1/T;

	for (size_t i=0; i<34; i++)
	{
		gamma_tt += nRegion1[i]*pow(7.1-pi, IRegion1[i])*JRegion1[i]*(JRegion1[i]-1.)*pow(tau-1.222, JRegion1[i]-2.);
	}

	return gamma_tt;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - ideal part
 *  Basic equation
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_0_region2(const double p, const double T) const
{
	double gamma_0 = 0;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<9; i++)
	{
		gamma_0 += n0Region2[i]*pow(tau, J0Region2[i]);
	}

	return log(p/p_star_Region2)+gamma_0;
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
 *  Dimensionless Gibbs free energy for region 2 - ideal part
 *  First derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_t_0_region2(const double T) const
{
	double gamma_t = 0;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<9; i++)
	{
		gamma_t += n0Region2[i]*J0Region2[i]*pow(tau, J0Region2[i]-1);
	}

	return gamma_t;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  Basic equation
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_r_region2(const double p, const double T) const
{
	double gamma = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;
	for (size_t i=0; i<43; i++)
	{
		gamma += nRegion2[i]*pow(pi,IRegion2[i])*pow(tau-0.5,JRegion2[i]);
	}
	return gamma;
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
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  first derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_t_r_region2(const double p, const double T) const
{
	double gamma_p = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;
	for (size_t i=0; i<43; i++)
	{
		gamma_p += nRegion2[i]*pow(pi,IRegion2[i])*JRegion2[i]*pow(tau-0.5,JRegion2[i]-1);
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
	double gamma_tt = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<43; i++)
	{
		gamma_tt += nRegion2[i]*pow(pi, IRegion2[i])*JRegion2[i]*(JRegion2[i]-1)*pow(tau-0.5, JRegion2[i]-2.);
	}

	return gamma_tt;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  Second derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_pp_r_region2(const double p, const double T) const
{
	double gamma_pp = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<43; i++)
	{
		gamma_pp += nRegion2[i]*IRegion2[i]*(IRegion2[i]-1)*pow(pi, IRegion2[i]-2)*pow(tau-0.5, JRegion2[i]);
	}

	return gamma_pp;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  Second derivative with respect to specific temperature and pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_pt_r_region2(const double p, const double T) const
{
	double gamma_pt = 0;
	double pi = p/p_star_Region2;
	double tau = T_star_Region2/T;

	for (size_t i=0; i<43; i++)
	{
		gamma_pt += nRegion2[i]*IRegion2[i]*pow(pi, IRegion2[i]-1)*JRegion2[i]*pow(tau-0.5, JRegion2[i]-1.);
	}

	return gamma_pt;
}
/**************************************************************************************************************
 *  Dimensionless Helmholtz free energy for region 3
 *  basic function
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::phi_region3 (const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	double tau = criticalTemperature/T;

	double phi = nRegion3[0]*log(delta);

	for (size_t i=1; i<40; i++)
	{
		phi += nRegion3[i]*pow(delta, IRegion3[i])*pow(tau, JRegion3[i]);
	}

	return phi;
}
/**************************************************************************************************************
 *  Dimensionless Helmholtz free energy for region 3
 *  First derivative with respect to specific density
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::phi_d_region3 (const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	double tau = criticalTemperature/T;

	double phi_d = nRegion3[0]/delta;

	for (size_t i=1; i<40; i++)
	{
		phi_d += nRegion3[i]*IRegion3[i]*pow(delta, IRegion3[i]-1)*pow(tau, JRegion3[i]);
	}

	return phi_d;
}
/**************************************************************************************************************
 *  Dimensionless Helmholtz free energy for region 3
 *  Second derivative with respect to specific density
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::phi_dd_region3 (const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	double tau = criticalTemperature/T;

	double phi_dd = -nRegion3[0]/delta/delta;

	for (size_t i=1; i<40; i++)
	{
		phi_dd += nRegion3[i]*IRegion3[i]*(IRegion3[i]-1)*pow(delta, IRegion3[i]-2)*pow(tau, JRegion3[i]);
	}

	return phi_dd;
}
/**************************************************************************************************************
 *  Dimensionless Helmholtz free energy for region 3
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::phi_tt_region3 (const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	double tau = criticalTemperature/T;

	double phi_tt = 0;

	for (size_t i=1; i<40; i++)
	{
		phi_tt += nRegion3[i]*pow(delta, IRegion3[i])*JRegion3[i]*(JRegion3[i]-1)*pow(tau, JRegion3[i]-2);
	}

	return phi_tt;
}
/**************************************************************************************************************
 *  Dimensionless Helmholtz free energy for region 3
 *  Second derivative with respect to specific density and temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::phi_dt_region3 (const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	double tau = criticalTemperature/T;

	double phi_dt = 0;

	for (size_t i=1; i<40; i++)
	{
		phi_dt += nRegion3[i]*IRegion3[i]*pow(delta, IRegion3[i]-1)*JRegion3[i]*pow(tau, JRegion3[i]-1);
	}

	return phi_dt;
}
/**************************************************************************************************************
 *  Dimensionless Helmholtz free energy for region 3
 *  First derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::phi_t_region3 (const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	double tau = criticalTemperature/T;

	double phi_t = 0;

	for (size_t i=1; i<40; i++)
	{
		phi_t += nRegion3[i]*pow(delta, IRegion3[i])*JRegion3[i]*pow(tau, JRegion3[i]-1);
	}

	return phi_t;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - ideal part
 *  Basic equation
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_0_region5(const double p, const double T) const
{
	double gamma_0 = 0;
	double tau = T_star_Region5/T;

	for (size_t i=0; i<6; i++)
	{
		gamma_0 += n0Region5[i]*pow(tau, J0Region5[i]);
	}

	return log(p/p_star_Region5)+gamma_0;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  Basic equation
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_r_region5(const double p, const double T) const
{
	double gamma = 0;
	double pi = p/p_star_Region5;
	double tau = T_star_Region5/T;
	for (size_t i=0; i<9; i++)
	{
		gamma += nRegion5[i]*pow(pi,IRegion5[i])*pow(tau-0.5,JRegion5[i]);
	}
	return gamma;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 5
 *  First derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_p_0_region5(const double p) const
{
	return p_star_Region5/p;

}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  first derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_p_r_region5(const double p, const double T) const
{
	double gamma_p = 0;
	double pi = p/p_star_Region5;
	double tau = T_star_Region5/T;
	for (size_t i=0; i<6; i++)
	{
		gamma_p += nRegion5[i]*IRegion5[i]*pow(pi,IRegion5[i]-1)*pow(tau,JRegion5[i]);
	}
	return gamma_p;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - ideal part
 *  First derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_t_0_region5(const double T) const
{
	double gamma_t = 0;
	double tau = T_star_Region5/T;

	for (size_t i=0; i<6; i++)
	{
		gamma_t += n0Region5[i]*J0Region5[i]*pow(tau, J0Region5[i]-1);
	}

	return gamma_t;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  first derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_t_r_region5(const double p, const double T) const
{
	double gamma_p = 0;
	double pi = p/p_star_Region5;
	double tau = T_star_Region5/T;
	for (size_t i=0; i<6; i++)
	{
		gamma_p += nRegion5[i]*pow(pi,IRegion5[i])*JRegion5[i]*pow(tau,JRegion5[i]-1);
	}
	return gamma_p;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 5 - ideal part
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_tt_0_region5(const double T) const
{
	double gamma_p = 0;
	double tau = T_star_Region5/T;

	for (size_t i=0; i<6; i++)
	{
		gamma_p += n0Region5[i]*J0Region5[i]*(J0Region5[i]-1)*pow(tau, J0Region5[i]-2);
	}

	return gamma_p;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 5 - real part
 *  Second derivative with respect to specific temperature
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_tt_r_region5(const double p, const double T) const
{
	double gamma_tt = 0;
	double pi = p/p_star_Region5;
	double tau = T_star_Region5/T;

	for (size_t i=0; i<6; i++)
	{
		gamma_tt += nRegion5[i]*pow(pi, IRegion5[i])*JRegion5[i]*(JRegion5[i]-1)*pow(tau, JRegion5[i]-2.);
	}

	return gamma_tt;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 5 - real part
 *  Second derivative with respect to specific temperature and pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_pt_r_region5(const double p, const double T) const
{
	double gamma_pt = 0;
	double pi = p/p_star_Region5;
	double tau = T_star_Region5/T;

	for (size_t i=0; i<6; i++)
	{
		gamma_pt += nRegion5[i]*IRegion5[i]*pow(pi, IRegion5[i]-1)*JRegion5[i]*pow(tau, JRegion5[i]-1.);
	}

	return gamma_pt;
}
/**************************************************************************************************************
 *  Dimensionless Gibbs free energy for region 2 - real part
 *  Second derivative with respect to specific pressure
 *  IAPWS-IF97 - Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::gamma_pp_r_region5(const double p, const double T) const
{
	double gamma_pp = 0;
	double pi = p/p_star_Region5;
	double tau = T_star_Region5/T;

	for (size_t i=0; i<43; i++)
	{
		gamma_pp += nRegion5[i]*IRegion5[i]*(IRegion5[i]-1)*pow(pi, IRegion5[i]-2)*pow(tau, JRegion5[i]);
	}

	return gamma_pp;
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
	case 3:
			return DensityRegion3(p,T);
		break;
	case 5:
		return 1/(specificGasConstant*T/p_star_Region5*(gamma_p_0_region5(p)+gamma_p_r_region5(p,T)));
		break;
	default: return -1;
	}
}
/**************************************************************************************************************
 *  Iterative Density function for region 3
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::DensityRegion3(const double p, const double T) const
{

	// Pressure as lambda function with bound p and T; requires only density as argument;
	auto Pressure = [&p, &T, this](const double c) { return p-this->PressureRegion3(c,T); };

	double rho_max = 800.; //should be larger than max density in region 3
	double rho_min = 1.; //should be much smaller than min density in region 3

	//double density = Bisection(Pressure,rho_min,rho_max);
	double density = zbrent(Pressure,rho_min,rho_max,1e-9);

	return density;

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
	case 3:
		return 1.0/DensityRegion3(p,T);
		break;
	case 5:
		return specificGasConstant*T/p_star_Region5*(gamma_p_0_region5(p)+gamma_p_r_region5(p,T));
		break;
	default: return -1;
	}

}
/**************************************************************************************************************
 *  Pressure function for region 3
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::PressureRegion3( const double rho, const double T) const
{
	double delta = rho/criticalDensity;
	return rho*specificGasConstant*T*delta*phi_d_region3(rho,T);
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
	case 3:
	{
		double rho = DensityRegion3(p,T);
		double delta = rho/criticalDensity;
		double tau = criticalTemperature/T;
		double phi_d = phi_d_region3(rho,T);
		double phi_tt = phi_tt_region3(rho,T);
		double phi_dd = phi_dd_region3(rho,T);
		double phi_dt = phi_dt_region3(rho,T);

		return specificGasConstant*(-tau*tau*phi_tt*(delta*phi_d-delta*tau*phi_dt)*(delta*phi_d-delta*tau*phi_dt)/(2*delta*phi_d+delta*delta*phi_dd));

		break;
	}
	case 5:
		return -(specificGasConstant*(T_star_Region5/T)*(T_star_Region5/T)*(gamma_tt_0_region5(T)+gamma_tt_r_region5(p,T)));
		break;
	default: return -1;
	}

}
/**************************************************************************************************************
 *  Specific Entrpoy Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpecificEntropy( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
		return specificGasConstant*(T_star_Region1/T*gamma_t_region1(p,T)-gamma_region1(p,T));
		break;
	case 2:
		return specificGasConstant*(T_star_Region2/T*(gamma_t_0_region2(T)+gamma_t_r_region2(p,T))-(gamma_0_region2(p,T)+gamma_r_region2(p,T)));
		break;
	case 3:
	{
		double rho = DensityRegion3(p,T);
		return specificGasConstant*(criticalTemperature*phi_t_region3(rho,T)-phi_region3(rho,T));
	}
		return -1;
		break;
	case 5:
		return specificGasConstant*(T_star_Region5/T*(gamma_t_0_region5(T)+gamma_t_r_region5(p,T))-(gamma_0_region5(p,T)+gamma_r_region5(p,T)));
		break;
	default: return -1;
	}
}
/**************************************************************************************************************
 *  Specific Isochoric Heat Capacity Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpecificIsochoricHeatcapacity( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
	{
		double tau = T_star_Region1/T;
		double gamma_x = (gamma_p_region1(p,T)-tau*gamma_pt_region1(p,T));
		return specificGasConstant*(-1*tau*tau*gamma_tt_region1(p,T)+(gamma_x*gamma_x/gamma_pp_region1(p,T)));
		break;
	}
	case 2:
	{
		double tau = T_star_Region2/T;
		double pi = p/p_star_Region2;
		double gamma_x = (1+pi*gamma_p_r_region2(p,T)-tau*pi*gamma_pt_r_region2(p,T));
		return specificGasConstant*	(
				-1*tau*tau*(gamma_tt_0_region2(T)+gamma_tt_r_region2(p,T))
				-(gamma_x*gamma_x/(1-pi*pi*gamma_pp_r_region2(p,T))));
		break;
	}

	case 3://Todo: c_p for region 3
		return -1;
		break;
	case 5:
	{
		double tau = T_star_Region5/T;
		double pi = p/p_star_Region5;
		double gamma_x = (1+pi*gamma_p_r_region5(p,T)-tau*pi*gamma_pt_r_region5(p,T));
		return specificGasConstant*	(
				-1*tau*tau*(gamma_tt_0_region5(T)+gamma_tt_r_region5(p,T))
				-(gamma_x*gamma_x/(1-pi*pi*gamma_pp_r_region5(p,T))));
		break;
	}
	default: return -1;
	}
}
/**************************************************************************************************************
 *  Specific Internal Energy Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpecificInternalEnergy( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
	{
		double pi = p/p_star_Region1;
		double tau = T_star_Region1/T;
		return specificGasConstant*T*(tau*gamma_t_region1(p,T)-pi*gamma_p_region1(p,T));
		break;
	}
	case 2:
	{
		double pi = p/p_star_Region2;
		double tau = T_star_Region2/T;
		return specificGasConstant*T*(tau*(gamma_t_0_region2(T)-gamma_t_r_region2(p,T))-pi*(gamma_p_0_region2(p)+gamma_p_r_region2(p,T)));
		break;
	}

	case 3:
	{
		double rho = DensityRegion3(p,T);
		return specificGasConstant*criticalTemperature*phi_t_region3(rho,T);
		break;
	}
	case 5:
	{
		double pi = p/p_star_Region5;
		double tau = T_star_Region5/T;
		return specificGasConstant*T*(tau*(gamma_t_0_region5(T)-gamma_t_r_region5(p,T))-pi*(gamma_p_0_region5(p)+gamma_p_r_region5(p,T)));
		break;
	}
	default: return -1;
	}
}
/**************************************************************************************************************
 *  Specific Enthalpy Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpecificEnthalpy( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
		return specificGasConstant*T_star_Region1*gamma_t_region1(p,T);
		break;
	case 2:
		return specificGasConstant*T_star_Region2*(gamma_t_0_region2(T)+gamma_t_r_region2(p,T));
		break;
	case 3:
	{
		double rho = DensityRegion3(p,T);
		return specificGasConstant*T*(criticalTemperature/T*phi_t_region3(rho,T)+rho/criticalDensity*phi_d_region3(rho,T));
		break;
	}
	case 5:
		return specificGasConstant*T_star_Region5*(gamma_t_0_region5(T)+gamma_t_r_region5(p,T));
		break;
	default: return -1;
	}
}
/**************************************************************************************************************
 *  Speed of Sound Equation
 *  IAPWS-IF97
 *  Revised Release, August 2007
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::SpeedOfSound( const double p, const double T) const
{
	const short Region = RegionSelection(p,T);
	assert(Region>=1&&Region<=5);

	switch (Region)
	{
	case 1:
	{
		double gamma_p = gamma_p_region1(p,T);
		double gamma_pp = gamma_pp_region1(p,T);
		double gamma_pt = gamma_pt_region1(p,T);
		double gamma_tt = gamma_tt_region1(p,T);
		double tau = T_star_Region1/T;

		return sqrt(gamma_p*gamma_p*specificGasConstant*T/((gamma_p-tau*gamma_pt)*(gamma_p-tau*gamma_pt)/(tau*tau*gamma_tt)-gamma_pp));
		break;
	}
	case 2:
	{
		double gamma_p_r = gamma_p_r_region2(p,T);
		double gamma_pp_r = gamma_pp_r_region2(p,T);
		double gamma_pt_r = gamma_pt_r_region2(p,T);
		double gamma_tt_0 = gamma_tt_0_region2(T);
		double gamma_tt_r = gamma_tt_r_region2(p,T);

		double tau = T_star_Region2/T;
		double pi = p/p_star_Region2;

		return sqrt(specificGasConstant*T*
				(1+2*pi*gamma_p_r+pi*pi*gamma_p_r*gamma_p_r)/
				( (1-pi*pi*gamma_pp_r)+ (1+pi*gamma_p_r-tau*pi*gamma_pt_r)*(1+pi*gamma_p_r-tau*pi*gamma_pt_r)/(tau*tau*(gamma_tt_0+gamma_tt_r)) )
		);

		break;
	}

	case 3:
	{
		double rho = DensityRegion3(p,T);
		double delta = rho/criticalDensity;
		double tau = criticalTemperature/T;

		double phi_d = phi_d_region3(rho,T);
		double phi_dd = phi_dd_region3(rho,T);
		double phi_dt = phi_dt_region3(rho,T);
		double phi_tt = phi_tt_region3(rho,T);

		return sqrt(specificGasConstant*T*
				(2*delta*phi_d+delta*delta*phi_dd-
				((delta*phi_d-delta*tau*phi_dt)*(delta*phi_d-delta*tau*phi_dt))/(tau*tau*phi_tt)));
		break;
	}
	case 5:
	{
		double gamma_p_r = gamma_p_r_region5(p,T);
		double gamma_pp_r = gamma_pp_r_region5(p,T);
		double gamma_pt_r = gamma_pt_r_region5(p,T);
		double gamma_tt_0 = gamma_tt_0_region5(T);
		double gamma_tt_r = gamma_tt_r_region5(p,T);

		double tau = T_star_Region5/T;
		double pi = p/p_star_Region5;

		return sqrt(specificGasConstant*T*
				(1+2*pi*gamma_p_r+pi*pi*gamma_p_r*gamma_p_r)/
				( (1-pi*pi*gamma_pp_r)+ (1+pi*gamma_p_r-tau*pi*gamma_pt_r)*(1+pi*gamma_p_r-tau*pi*gamma_pt_r)/(tau*tau*(gamma_tt_0+gamma_tt_r)) )
		);

		break;
	}
	default: return -1;
	}
}
/**************************************************************************************************************
 *  Lambda_0 equation
 *  IAPWS-IF97
 *  Revised Release, August 2008
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::lambda_0(const double T) const
{
	double _T = T/647.226;
	double L[4] = {1.0, 6.978267, 2.599096, -0.998254};
	double lamda = 0;

	for (size_t i=0; i<4; i++)
	{
		lamda += L[i]/pow(_T,i);
	}

	return sqrt(_T)/lamda;
}
/**************************************************************************************************************
 *  Lambda_1 equation
 *  IAPWS-IF97
 *  Revised Release, August 2008
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::lambda_1(const double T, const double rho) const
{
	double _T = T/647.226;
	double _rho = rho/317.763;
	double L[5][6] = {{1.3293046,-0.40452437,0.24409490,0.018660751,-0.12961068,0.044809953},
			{1.7018363,-2.2156845,1.6511057,-0.7673602,0.37283344,-0.11203160},
			{5.2243158,-10.124111,4.9874687,-0.27297694,-0.43083393,0.13333849},
			{8.7127675,-9.5000611,4.3786606,-0.91783782,0.0,0.0},
			{-1.8525999,0.9340469,0.0,0.0,0.0,0.0}};

	double lamda = 0;

	for (size_t i=0; i<5; i++)
		for (size_t j=0; j<6; j++)
		{
			lamda += L[i][j]*pow(1/_T-1, i)*pow(_rho-1, j);
		}

	return exp(lamda*_rho);
}
/**************************************************************************************************************
 *  Mu_0 equation
 *  IAPWS-IF97
 *  Revised Release, August 2008
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::mu_0(const double T) const
{
	double _T = T/647.226;

	return 0;
}
/**************************************************************************************************************
 *  Mu_0 equation
 *  IAPWS-IF97
 *  Revised Release, August 2008
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::mu_1(const double T, const double rho) const
{
	double _T = T/647.226;

	return 0;
}
/**************************************************************************************************************
 *  Lambda_2 equation
 *  IAPWS-IF97
 *  Revised Release, August 2008
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::lambda_2(const double T, const double rho) const
{
	// Lambda_2 will be ignored at the moment, since it is unimportant in other than the critical region.
	// To solve Lambda_2, we need to account for dp/dt at constant rho, which could be expansive.
	// Feel free to implement lamda_3 by yourself, the IAPWS Formulation for General and Scientific use
	// is recommended to produce the partial derivative.

	return 0;
}
/**************************************************************************************************************
 *  Thermal conductivity equation
 *  IAPWS-IF97
 *  Revised Release, August 2008
 *  NB, May 2014
 **************************************************************************************************************/
double IF97::ThermalConductivity( const double p, const double T) const
{
	if (((T>=273.15)&&(T<=398.15)&&(p<=400.0e6)) ||
		((T>398.15)&&(T<=523.15)&&(p<=200.0e6)) ||
		((T>523.15)&&(T<=673.15)&&(p<=150.0e6)) ||
		((T>673.15)&&(T<=1073.15)&&(p<=100.0e6)))
	{
		double rho = Density(p, T);
		return 0.4945*(lambda_0(T)*lambda_1(T, rho)+lambda_2(T, rho));
	}
	else return -1;
}
