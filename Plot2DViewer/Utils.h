#pragma once
#include "Matrix.h"
#include <fstream>
double* findABC(double x1, double y1, double x2, double y2) {
	double * ABC = new double[3];
	double a = y1 - y2;
	double b = x2 - x1;
	double c = x1*y2-x2*y1;
	ABC[0] = a;
	ABC[1] = b;
	ABC[2] = c;
	return ABC;
}

Matrix<> readVerticesFromFile(string filePath) {
		ifstream f(filePath);
		int m;
		f >> m;
		Matrix<> vertex = Matrix<double>(4, m);
		f >> vertex;
		return vertex;
}
Matrix<int> readFacesFromFile(string filePath) {
	ifstream f(filePath);
	int l;
	f >> l;
	Matrix<int> faces = Matrix<int>(l, 3);
	f >> faces;
	return faces;
}