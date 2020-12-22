#pragma once
#include<cmath>
#include"AffineTransfrom3D.h"
struct Coordinates {

public:double x, y, z;
   Coordinates(): x(0), y(0), z(0)
   {
   };
   Coordinates(double x,double y,double  z) : x(x), y(y), z(z)
   {
   }
};
double getNorm(Coordinates c1) {
	return sqrt(c1.x*c1.x + c1.y*c1.y + c1.z*c1.z);
}
Coordinates Multiply(Coordinates c1, Coordinates c2) {
	Coordinates result;
	result.x = c1.y*c2.z - c2.y*c1.z;
	result.y = -c1.x*c2.z + c2.x*c1.z;
	result.z = c1.x*c2.y - c2.y*c1.x;
	return result;
}
Coordinates MultiplyNorm(Coordinates c1, Coordinates c2) {
	Coordinates result;
	result.x = c1.y*c2.z-c2.y*c1.z;
	result.y = -c1.x*c2.z + c2.x*c1.z;
	result.z = c1.x*c2.y - c2.y*c1.x;
	double norm = getNorm(result);
	if (norm > 0) {
		result.x /= norm;
		result.y /= norm;
		result.z /= norm;
	}
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

Coordinates SpinAroundPointY(Coordinates vect,Coordinates vect2,double t) {
	t /= 180;
	double vert[4] = { vect.x,vect.y,vect.z,1 };
	Matrix<double>res = Matrix<double>(4,1, vert);
	double x1 = vect2.x - vect.x;
	double y1 = vect2.y - vect.y;
	double z1=	vect2.z - vect.z;
	Matrix <> result = Translation(x1,y1 ,z1 )*Rotation3DY(t)*Translation(-x1,-y1,-z1)*res;
	Coordinates  resultingVector;
	resultingVector.x = result.getCell(0,0);
	resultingVector.y = result.getCell(1, 0);
	resultingVector.z = result.getCell(2, 0);
	return resultingVector;
}
Coordinates SpinAroundPoint(Coordinates vect,Coordinates around, double t) {
	Coordinates v= Normalize(around);
	double A = v.x;
	double B = v.y;
	double C = v.z;
	double coords_arr[3] = { vect.x,vect.y,vect.z };
	Matrix<double>coords = Matrix<double>(3,1, coords_arr);
	double RL_arr[9] = {
		(B*B + C * C)*cos(t) + A * A  ,       (-cos(t) + 1)*A*B - sin(t)*C , (-cos(t) + 1)*A*C + sin(t)*B,
		(-cos(t) + 1)*A*B + sin(t)*C  ,    (A*A + C * C)*cos(t) + B * B    ,-A * sin(t) + (-cos(t) + 1)*B*C,
		(-cos(t) + 1)*A*C - B * sin(t),       A*sin(t) + (-cos(t) + 1)*B*C ,(A*A + B * B)*cos(t) + C * C
	};
	Matrix<double>RL = Matrix<double>(3, RL_arr);
	Matrix<double>res = RL * coords;
	Coordinates resultingVector = Coordinates(res.getCell(0,0), res.getCell(1, 0), res.getCell(2, 0));
	return resultingVector;
}