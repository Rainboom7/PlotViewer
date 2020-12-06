#pragma once
#include<cmath>
struct Coordinates {

public:double x, y, z;
   Coordinates(): x(0), y(0), z(0)
   {
   }
};
double getNorm(Coordinates c1) {
	return sqrt(c1.x*c1.x + c1.y*c1.y + c1.z*c1.z);
}
Coordinates Multiply(Coordinates c1, Coordinates c2) {
	Coordinates result;
	result.x = c1.x*c2.x;
	result.y = c1.y*c2.y;
	result.x = c1.z*c2.z;
	return result;
}
Coordinates MultiplyNorm(Coordinates c1, Coordinates c2) {
	Coordinates result;
	result.x = c1.x*c2.x;
	result.y = c1.y*c2.y;
	result.x = c1.z*c2.z;
	double norm = getNorm(result);
	result.x /= norm;
	result.y /= norm;
	result.z /= norm;
	return result;
}
Coordinates MultiplyNorm(Coordinates c1, Coordinates c2) {
	Coordinates result;
	result.x = c1.x*c2.x;
	result.y = c1.y*c2.y;
	result.x = c1.z*c2.z;
	double norm = getNorm(result);
	result.x /= norm;
	result.y /= norm;
	result.z /= norm;
	return result;
}
Coordinates Normalize(Coordinates c1) {
	double norm = getNorm(c1);
	c1.x /= norm;
	c1.y /= norm;
	c1.z /= norm;
	return c1;
}
bool isSet(Coordinates coord) {
	return coord.x != 0 || coord.x || 0 && coord.y || 0;
}