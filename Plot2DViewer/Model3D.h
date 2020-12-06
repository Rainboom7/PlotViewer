#pragma once
#ifndef MODEL3D_H
#define MODEL3D_H

#include "Matrix.h"
#include"AffineTransfrom3D.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Utils.h"

class Model3D
{
	//�� ����� ����������� 2 �����
	//bool ��������� ��� ����� � ����� ������ �����
private:
	 Matrix<> Vertices;
	 Matrix<> InitialVertices;
	 Matrix<> ProjectedVertices;
	 Matrix<int> Faces;
	 Matrix<int> Edges;
	 Matrix<double> CumulativeAT;
public:
	Model3D();//����������� �� ���������;
	Model3D(const Matrix<int>, const Matrix<double>); // ����������� �������� ������ �� �������� ����� ������ � ����� ������;
	Model3D(string, string); // ����������� �������� ������ �� ������ ������, � ������� ����� ����� ������ � ����� ������;
	Model3D(int, int);//����������� � ������� M � L
	void SetEdges(); //�������� ����� ���� �� �������� ����� ������
	Matrix<> GetVertices();//��������� ����� ������, ����� ������ � ����� ����;
	Matrix<int> GetFaces();//��������� ����� ������, ����� ������ � ����� ����;
	Matrix<int> GetEdges();//��������� ����� ������, ����� ������ � ����� ����;
	double GetVertexX(int);//��������� ��������� ������� ������ � �������� �������;
	double GetVertexY(int); //��������� ��������� ������� ������ � �������� �������;
	double GetVertexZ(int); //��������� ��������� ������� ������ � �������� �������;
	void Apply(Matrix<>); // ���������� � ������ ��������� ��������������, ��������� ����� ��������;
	void Apply(); // ���������� � ������ ������������ �������� ��������������;
	void Project(Matrix<>); // ������������� ������.
private:
	//???????������ �� ������������ ����� �� ������
	void setEdges() {
		int K = this->Faces.getRows() * 2;
		int* edgeArray = new int[K * 2];
		int k = 0;
		for (int i = 0; i < this->Faces.getRows(); i++)
		{
			edgeArray[k] = this->Faces.getCell(i, 0);
			k++;
			edgeArray[k] = this->Faces.getCell(i, 1);
			k++;

			edgeArray[k] = this->Faces.getCell(i, 1);
			k++;
			edgeArray[k] = this->Faces.getCell(i, 2);
			k++;

		}
		this->Edges = Matrix<int>(K, 2, edgeArray);
		
}

};
Model3D::Model3D()
	:Vertices(Matrix<double>()), InitialVertices(Matrix<double>()), ProjectedVertices(Matrix<double>()), Faces(Matrix<int>()),Edges(Matrix<int>()), CumulativeAT(Identity3D())
{
}
Model3D::Model3D(const Matrix<int> faces, const Matrix<double> vertices)
	:Vertices(vertices), InitialVertices(Matrix<double>()), ProjectedVertices(Matrix<double>()), Faces(faces), CumulativeAT(Identity3D())
{
	SetEdges();
}
Model3D::Model3D(string facesFilePath , string verticesFilePath)
	:Vertices(readVerticesFromFile(verticesFilePath)),Faces(readFacesFromFile(facesFilePath)), InitialVertices(Matrix<double>()), ProjectedVertices(Matrix<double>()), CumulativeAT(Identity3D())
{
	SetEdges();
}
Model3D::Model3D(int M, int L)
	: Vertices(Matrix<double>(4,M)), InitialVertices(Matrix<double>(4,M)), ProjectedVertices(Matrix<double>(4,M)), Faces(Matrix<int>(L, 3)), CumulativeAT(Identity3D())
{
	SetEdges();
}
void Model3D:: Apply(Matrix<> AT) {
	this->CumulativeAT = (AT * this->CumulativeAT);
}
void Model3D::Apply() {
	this->Vertices = this->CumulativeAT*this->InitialVertices;
}
//??WhoKnows
void Model3D::Project(Matrix<> P) {
	this->Vertices = P*this->ProjectedVertices;
}

#endif MODEL3D_H