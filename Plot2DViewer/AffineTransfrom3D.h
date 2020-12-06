
#ifndef AFFINE_TRANSFORM3D_H
#define AFFINE_TRANSFORM3D_H
#include "Matrix.h"

Matrix<> Translation(double x, double y,double z)
{
	double T[16] = 
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return Matrix<>(4, T);
}
Matrix<> Identity3D()
{
	double T[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return Matrix<>(4, T);

}
Matrix<> Rotation3DZ(double t)
{
	double T[16] =
	{
		cos(t), -sin(t), 0, 0,
		sin(t),  cos(t), 0, 0,
		0     ,     0  , 1, 0,
		0,          0  , 0, 1
	};
	return Matrix<>(4, T);
}
Matrix<> Rotation3DX(double t)
{
	double T[16] =
	{
		1,   0   ,    0  , 0,
		0, cos(t),-sin(t), 0,
		0, sin(t), cos(t), 0,
		0,    0  ,  0    , 1
	};
	return Matrix<>(4, T);
}
Matrix<> Rotation3DY(double t)
{
	double T[16] =
	{
		cos(t),   0   ,   sin(t)  , 0,
		0,        1   ,   0       , 0,
		-sin(t) , 0   , cos(t)    , 0,
		0      ,  0   ,  0         , 1
	};
	return Matrix<>(4, T);
}
Matrix<> Rotation3DZ(double c, double s)
{
	double r = 1.0 / sqrt(c*c + s * s);
	double sin_t = r * s;
	double cos_t = r * c;
	double T[16] =
	{
		cos_t, -sin_t, 0, 0,
		sin_t,  cos_t, 0, 0,
		0    ,   0  , 1, 0,
		0    ,   0  , 0, 1
	};
	return Matrix<>(4, T);
}
Matrix<> Scaling(double kx, double ky,double kz)
{
	double S[16] = {
		kx, 0, 0, 0,
		0 ,ky, 0, 0,
		0 , 0, kz,0,
	    0 , 0, 0, 1
	};
	return Matrix<>(4, S);
}

Matrix<> MappingXY()
{
	double S[16] = {
		1,0, 0, 0,
		0,1, 0, 0,
		0,0,-1, 0,
		0,0, 0, 1
	};
	return Matrix<>(4, S);
}

Matrix<> MappingYZ()
{
	double S[16] = {
	   -1,0,  0, 0,
		0,1,  0, 0,
		0,0,  1, 0,
		0,0,  0, 1
	};
	return Matrix<>(4, S);
}
Matrix<> MappingZX()
{
	double S[16] = {
	    1, 0,  0, 0,
		0,-1,  0, 0,
		0, 0,  1, 0,
		0, 0,  0, 1
	};
	return Matrix<>(4, S);
}
Matrix<> MappingApplicat()
{
	double S[16] = {
	   -1, 0,  0, 0,
		0,-1,  0, 0,
		0, 0,  1, 0,
		0, 0,  0, 1
	};
	return Matrix<>(4, S);
}
Matrix<> MappingAbsciss()
{
	double S[16] = {
	    1, 0,  0, 0,
		0,-1,  0, 0,
		0, 0, -1, 0,
		0, 0,  0, 1
	};
	return Matrix<>(4, S);
}
Matrix<> MappingOrdinat()
{
	double S[16] = {
	   -1, 0,  0, 0,
		0, 1,  0, 0,
		0, 0, -1, 0,
		0, 0,  0, 1
	};
	return Matrix<>(4, S);
}


Matrix<> Mapping03D()
{
	double S[16] = {
	   -1, 0,  0, 0,
		0,-1,  0, 0,
		0, 0, -1, 0,
		0, 0,  0, 1
	};
	return Matrix<>(4, S);
}



#endif AFFINE_TRANSFORM3D_H
