/*
 * Iterators.h
 *
 *  Created on: 15.05.2014
 *      Author: boettche
 */

#ifndef ITERATORS_H_
#define ITERATORS_H_

#include <cmath>
#include <limits>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <class T>
inline const T sgn(const T &a, const T &b) {
    return b >= 0 ? (a>=0 ? a : -a) : (a>=0 ? -a : a);}

inline const float sgn(const float &a, const double &b) {
	return b >= 0 ? (a>=0 ? a : -a) : (a>=0 ? -a : a);}

inline const double sgn(const double &a, const float &b) {
    return b >= 0 ? (a>=0 ? a : -a) : (a>=0 ? -a : a);}

template <typename F>
double Bisection (F&& f, double a, double b)
{
	double fa = f(a);
	double fb = f(b);

	if (fa*fb > 0)  // f(a) and f(b) should have different signs.
		return -1;	// If they haven't, there is either no root
					// between a and be, or there are more then one roots.

	const int maxIterations = 1000;
	const double eps = 1.0e-2;

	int iteration = 0;

	while (iteration < maxIterations)
	{
		iteration++;
		double c = (a+b)/2.;
		double fc = f(c);
		if (fabs(fc)<eps)
			return c;
		if (fa*fc > 0)
			a=c;
		else
			b=c;
	}

	return -1.0;
};

template <typename F>
double zbrent(F&& f, double a, double b, const double tol)
{
	const int ITMAX=100;
	const double EPS=std::numeric_limits<double>::epsilon();
	int iter;
	double c,d,e,min1,min2;
	double fa=f(a);
	double fb=f(b);
	double fc,p,q,r,s,tol1,xm;

	if ((fa > 0.0 && fb > 0.0) || (fa < 0.0 && fb < 0.0))
		return -1;

	fc=fb;
	for (iter=0;iter<ITMAX;iter++) {
		if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0)) {
			c=a;
			fc=fa;
			e=d=b-a;
		}
		if (fabs(fc) < fabs(fb)) {
			a=b;
			b=c;
			c=a;
			fa=fb;
			fb=fc;
			fc=fa;
		}
		tol1=2.0*EPS*fabs(b)+0.5*tol;
		xm=0.5*(c-b);
		if (fabs(xm) <= tol1 || fb == 0.0) return b;
		if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {
			s=fb/fa;
			if (a == c) {
				p=2.0*xm*s;
				q=1.0-s;
			} else {
				q=fa/fc;
				r=fb/fc;
				p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
				q=(q-1.0)*(r-1.0)*(s-1.0);
			}
			if (p > 0.0) q = -q;
			p=fabs(p);
			min1=3.0*xm*q-fabs(tol1*q);
			min2=fabs(e*q);
			if (2.0*p < (min1 < min2 ? min1 : min2)) {
				e=d;
				d=p/q;
			} else {
				d=xm;
				e=d;
			}
		} else {
			d=xm;
			e=d;
		}
		a=b;
		fa=fb;
		if (fabs(d) > tol1)
			b += d;
		else
			b += sgn(tol1,xm);
			fb=f(b);
	}
	return -1.0;
}


#endif /* ITERATORS_H_ */
