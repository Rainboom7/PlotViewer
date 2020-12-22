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
Coordinates findVectForOnePointAndOX(Coordinates v) {
	Coordinates oX = Coordinates(0, v.y, v.z);
	auto t = 2;
	return Coordinates(v.x + t * (oX.x - v.x), v.y + t * (oX.y - v.y), v.z + t * (oX.z - v.z));

}
Coordinates findVectForTwoPoints(Coordinates v1,Coordinates v2) {
	auto t = 2;
	return Coordinates(v1.x + t * (v2.x - v1.x), v1.y + t * (v2.y - v1.y), v1.z + t * (v2.z - v1.z));
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
void DebugMatrix(Matrix<> matr, string matrixName) {
	ofstream f("debug.txt",ios::app);
	f << matrixName << endl;
	f << matr<<endl;
	f.close();
}