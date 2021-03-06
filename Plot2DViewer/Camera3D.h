#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include <windows.h>
#include "Camera2D.h"
#include "Matrix.h"
#include "Coordinates.h"


class Camera3D:public Camera2D {
	protected:
	Coordinates Ov, T, N;
	double D=32;
	Matrix<>    WorldToView;
	Matrix<>    ViewToProjection;
	Matrix<>	WorldToProjection;
	void UpdateCamera() {
	//	if (isSet(this->N) && isSet(this->T)&& this->D!=0) {
			Coordinates i = MultiplyNorm(T, N);
			Coordinates k = Normalize(N);
			Coordinates j = Multiply(k, i);
			double Swv[16] = {
			 i.x,i.y,i.z,-(i.x*Ov.x + i.y*Ov.y + i.z*Ov.z),
			 j.x,j.y,j.z,-(j.x*Ov.x + j.y*Ov.y + j.z*Ov.z),
			 k.x,k.y,k.z,-(k.x*Ov.x + k.y*Ov.y + k.z*Ov.z),
			 0  , 0 , 0 ,                1
			};
			this->WorldToView = Matrix<>(4, Swv);
			double Svp[12] =
			{
			1,   0,      0,    0,
			0,   1,      0,    0,
			0,   0, -1.0 / D  ,1
			};
			this->ViewToProjection = Matrix<>(3,4, Svp);
			this->WorldToProjection = this->ViewToProjection*this->WorldToView;
		//}

	}
public:
		Camera3D(double L,double B,double R,double T) 
			: Ov(Coordinates(0,0,0)), N(Coordinates(0,0,1)), T(Coordinates(0,1,0)),Camera2D(L,B,R,T)
	{
			UpdateCamera();
	}
		Camera3D(Coordinates Ov, Coordinates N, Coordinates cT,double D,double L, double B, double R, double T) 
			: Ov(Ov), N(N), T(cT),D(D), Camera2D(L, B, R, T)
	{
			UpdateCamera();
	}
		Coordinates getT() { return this->T; }
		Coordinates getN() { return this->N; }

	void setOv(Coordinates Ov) {
		this->Ov = Ov;
		UpdateCamera();
	}
	void setT(Coordinates T) {
		this->T = T;
		UpdateCamera();
	}
	void setN(Coordinates N) {
		this->N = N;
		UpdateCamera();
	}
	void setD(double D) {
		this->D = D;
		UpdateCamera();
	}

};





#endif CAMERA_3D_H