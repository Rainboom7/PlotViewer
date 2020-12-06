#ifndef PARAMETRIC
#define PARAMETRIC


typedef double(*Func)(double);

 class ParametricFunction {
 protected:
	 double t_min = 0, t_max = 1;
	 Func first;
	 Func second;
 public:
	 virtual double getDecartX(double) = 0;
	 virtual double getDecartY(double) = 0;
	 void setBorders(double t_min, double t_max) {
		 this->t_min = t_min;
		 this->t_max = t_max;
	 }
	 double getMin() {
		 return this->t_min;
	 }
	 double getMax() {
		 return this->t_max;
	 }
	 void setFunctions(Func first, Func second) {
		 this->first = first;
		 this->second = second;
	 }
	

};
#endif PARAMETRIC