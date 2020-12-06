#ifndef ELLYPTIC
#define ELLYPTIC
#define _USE_MATH_DEFINES
#include <cmath>
#include "ParametricFuntion.h"


class EllipticFunction : public ParametricFunction {
private:
	double c;
public:
	EllipticFunction(double c)  {
		this->c = c;
		this->t_max = 2 * M_PI;
		this->t_min = 0;
	}

	double getDecartX(double t) override {
		if (this->first != NULL && this->second != NULL)
			return c * cosh(first(t))*cos(second(t));
	}
	double getDecartY(double t) override {
		if (this->first != NULL && this->second != NULL)
			return c * sinh(first(t))*sin(second(t));
	}


};
#endif ELLYPTIC
