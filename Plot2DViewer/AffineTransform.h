#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include "Matrix.h"

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, T);
}
Matrix<> Identity()
{
	double T[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, T);

}
Matrix<> Rotation(double t)
{
	t *= 180;
	double R[9] = {
		cos(t), -sin(t), 0,
		sin(t),  cos(t), 0,
		0,         0   , 1 };
	return Matrix<>(3, R);
}
//������ ������ ������
Matrix<> RotationCenter(double t,double x, double y)
{
		return  Translation(x,y)*Rotation(t) *Translation(-x,-y);
}	
Matrix<> Rotation(double c, double s)
{
	double r = 1.0/sqrt(c*c + s * s);
	double sin_t = r*s;
	double cos_t = r*c;
	double R[9] = {
		cos_t, -sin_t, 0,
		sin_t,  cos_t, 0,
		0,         0   , 1 };
	return Matrix<>(3, R);
}
Matrix<> Scaling(double kx, double ky)
{
	double S[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1 };
	return Matrix<>(3, S);
}

Matrix<> MappingX()
{
	double M[9] = {
		1, 0, 0,
		0, -1, 0,
		0, 0, 1 };
	return Matrix<>(3, M);
}

Matrix<> MappingY()
{
	double M[9] = {
		-1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, M);
}
//��������� ������������ ������ ����� ������������
Matrix<> MappingLine(double a, double b,double c)
{
	double norm = 1.0 / (a*a+b * b);
	double x0 = -a * c*norm;
	double y0 = -b * c*norm;

	return Translation(x0, y0) *Rotation(a, b)*MappingY()*Rotation(a, -b)*Translation(-x0, -y0);
}
Matrix<> Mapping0()
{
	double M0[9] = {
		-1, 0, 0,
		0, -1, 0,
		0, 0, 1 };
	return Matrix<>(3, M0);
}


// ����� ��������� ����������� �������, ������������ ������� ������� ��:
// Identity() - ������������� ��;
// Rotation(t) - ������� �� ���� t;
// Rotation(c, s) - ������� �� ����, ������� � ����� �������� ��������������� ��������� c � s;
// Scaling(kx, ky) - ���������������;
// Mapping (��������� ���� ���������) - �� �������, ��� �������� ������ ��������� ����� ������������ ������� Scaling.

// � ���������� ������� ������������ ����������� ������� �� ������.
// �������������� ���� � ������ �������� �������� ������.
// ��������, ����� �������, ��������� ��������� �������,
// � ����������� ���������������� ��������� � �������������.

#endif AFFINE_TRANSFORM_H
