/*
 * IAPWS-IF97.h
 *
 *  Created on: 09.05.2014
 *      Author: Norbert Boettcher
 */

#ifndef IAPWS_IF97_H_
#define IAPWS_IF97_H_

class IF97{
private:

	static const double nB23[5];
	static const double nRegion1[34];
	static const double nRegion2[43];
	static const double n0Region2[9];
	static const double nRegion3[40];
	static const double nRegion4[10];
	static const double n0Region5[6];
	static const double nRegion5[6];

	static const short IRegion1[34];
	static const short IRegion2[43];
	static const short IRegion3[40];
	static const short IRegion5[6];

	static const short JRegion1[34];
	static const short JRegion2[43];
	static const short J0Region2[9];
	static const short JRegion3[40];
	static const short J0Region5[6];
	static const short JRegion5[6];

	static const double specificGasConstant; // J/kg/K

	static const double criticalTemperature; //K
	static const double criticalPressure; // MPa
	static const double criticalDensity; // kg/m^3

	static const double tripplePointTemperature; //K
	static const double tripplePointpressure; // Pa

	static const double p_star_Region1; // Pa
	static const double p_star_Region2; // Pa
	static const double p_star_Region4; // Pa
	static const double p_star_Region5; // Pa

	static const double T_star_Region1; // K
	static const double T_star_Region2; // K
	static const double T_star_Region4; // K
	static const double T_star_Region5; // K

	// Gibbs energy function and its derivatives for Region 1
	double gamma_region1 (const double p, const double T) const;
	double gamma_p_region1 (const double p, const double T) const;
	double gamma_pp_region1 (double p, const double T) const;
	double gamma_t_region1 (double p, const double T) const;
	double gamma_tt_region1 (double p, const double T) const;
	double gamma_pt_region1 (double p, const double T) const;


	// Gibbs energy function and its derivatives for Region 2
	double gamma_0_region2 (const double p, const double T) const;
	double gamma_p_0_region2 (const double p) const;
	double gamma_pp_0_region2 (const double p) const;
	double gamma_t_0_region2 (const double T) const;
	double gamma_tt_0_region2 (const double T) const;
	double gamma_pt_0_region2 (void) const;

	double gamma_r_region2 (const double p, const double T) const;
	double gamma_p_r_region2 (const double p,const  double T) const;
	double gamma_pp_r_region2 (const double p,const  double T) const;
	double gamma_t_r_region2 (const double p,const  double T) const;
	double gamma_tt_r_region2 (const double p,const  double T) const;
	double gamma_pt_r_region2 (const double p,const  double T) const;

	// specific Helmholtz free energy function and its derivatives for Region 3
	double phi_region3 (const double rho, const double T) const;
	double phi_d_region3 (const double rho, const double T) const;
	double phi_t_region3 (const double rho, const double T) const;
	double phi_dd_region3 (const double rho, const double T) const;
	double phi_tt_region3 (const double rho, const double T) const;
	double phi_dt_region3 (const double rho, const double T) const;
	// Gibbs energy function and its derivatives for Region 5
	double gamma_0_region5 (const double p, const double T) const;
	double gamma_r_region5 (const double p, const double T) const;
	double gamma_p_0_region5(const double p) const;
	double gamma_p_r_region5(const double p, const double T) const;
	double gamma_t_0_region5(const double T) const;
	double gamma_t_r_region5(const double p, const double T) const;
	double gamma_tt_0_region5(const double T) const;
	double gamma_tt_r_region5(const double p, const double T) const;
	double gamma_pt_r_region5(const double p, const double T) const;
	double gamma_pp_r_region5(const double p, const double T) const;

	short RegionSelection (const double p,const  double T) const;
	double PressureRegion3( const double rho, const double T) const;


	// curves determining the border between region 2 and region 3
	double B23Equation_T (const double p) const;
	double B23Equation_p (const double T) const;

	// equations for thermal conductivity
	double lambda_0(const double T) const;
public:
	IF97();

	double SpecificVolume( const double p, const double T) const;
	double Density( const double p, const double T) const;
	double DensityBisectionR3(const double p, const double T) const;

	double SpecificEntropy ( const double p, const double T) const;
	double SpecificInternalEnergy ( const double p, const double T) const;
	double SpecificEnthalpy ( const double p, const double T) const;
	double SpecificIsobaricHeatcapacity ( const double p, const double T) const;
	double SpecificIsochoricHeatcapacity ( const double p, const double T) const;
	double SpeedOfSound ( const double p, const double T) const;

	double SaturationPressure (const double T) const;
	double SaturationTemperature (const double p) const;

	double ThermalConductivity (const double p, const double T) const;

};


#endif /* IAPWS_IF97_H_ */
