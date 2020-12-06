#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров L, R, B, T
	L=-20,
	R=20,
	B=-20,
	T=20;
//	a = 5;
double Parabola(double x)
{
	return x*x-2;
}

double Sinusoid(double x)
{
	return sin(x);
}

double parametricCircleX(double t) {
	return 1;
}
double parametricCircleY(double t) {
	return t;
}

double parametricSpiralX(double t) {
	return t/4;
}
double parametricSpiralY(double t) {
	return t;
}



