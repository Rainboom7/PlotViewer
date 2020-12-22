
#ifndef AFFINE_TRANSFORM3D_H
#define AFFINE_TRANSFORM3D_H
#include"Coordinates.h"
#include "Matrix.h"
#include <cmath>

//1)Поворот вокруг оси которая проходит  через любую точку модели  и сонаправлена Ox на фи
//2)Поворот вокруг оси которая проходит через 2 заданные точки модели на фи
//p.s составной поворот для совмещения вектора с Ox
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
Matrix<> Rotation3DX(double c, double s)
{
	auto r = 1.0 / sqrt(c*c + s * s);
	double sin_t =  s*r;
	double cos_t =  c*r;
	double T[16] =
	{
		1,   0   ,    0  , 0,
		0, cos_t,-sin_t, 0,
		0, sin_t, cos_t, 0,
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
Matrix<> Rotation3DY(double c,double s)
{
	double r = 1.0 / sqrt(c*c + s * s);
	double sin_t = r * s;
	double cos_t = r * c;
	double T[16] =
	{
		cos_t,   0   ,  sin_t  , 0,
		0,        1   ,   0    , 0,
		-sin_t , 0   , cos_t    , 0,
		0      ,  0   ,  0      , 1
	};
	return Matrix<>(4, T);
}




Matrix<> RotationL0(double t)
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

//1)Поворот вокруг оси которая проходит  через любую точку модели  и сонаправлена Ox на фи
Matrix<> RotationFirst(double y, double z, double t)
{
	return Translation(0, y, z)*Rotation3DX(t)*Translation(0, -y, -z);

}
Matrix<> Rotation(double y, double z, double t)
{
	return Translation(0, y, z)*Rotation3DX(t)*Translation(0, -y, -z);

}
//2)Поворот вокруг оси которая проходит через 2 заданные точки модели на фи
Matrix<> RotationSecond(double x1,double y1,double z1,double x2,double y2,double z2,double t)
{
	double a = x2 - x1;
	double b = y2 - y1;
	double c = z2 - z1;


	if (c == 0)
	{
		double cos_a = a;// sqrt(a*a + b * b  );
		double sin_a = b; // sqrt(a*a + b * b  );
		return
			Translation(x1, y1, z1)*
						Rotation3DZ(cos_a, sin_a)*
											Rotation3DX(t)*
						Rotation3DZ(cos_a, -sin_a)*
			Translation(-x1, -y1, -z1);
	}
	else
	{
		double r = sqrt(b*b + c * c);
		double cos_a = a;// sqrt(a*a + b * b + c * c);
		double sin_a = r;// sqrt(a*a + b * b + c * c);
		return
			Translation(x1, y1, z1) *
					Rotation3DX(b, c) *
								Rotation3DZ(cos_a, sin_a)*
												Rotation3DX(t)*
								Rotation3DZ(cos_a, -sin_a)*
					Rotation3DX(b , -c )*
			Translation(-x1, -y1, -z1);
	}
		

//
	//if(x2>x1)
	//	return Translation(0, b, c)*Rotation3DZ(x2,z2) *Rotation3DY(x2, y2)*Rotation3DX(t) *Rotation3DY(x2, -y2) *Rotation3DZ(x2, -z2) *Translation(0, -b, -c);
	//else
	//	return Translation(0, b, c)*Rotation3DZ(x1, z1)*Rotation3DY(x1, y1)*Rotation3DX(-t)*Rotation3DY(x1, -y1) *Rotation3DZ(x1, -z1) *Translation(0, -b, -c);

}


#endif AFFINE_TRANSFORM3D_H
