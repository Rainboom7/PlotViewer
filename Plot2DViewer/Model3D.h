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
	Matrix<> GetVertices()//��������� ����� ������, ����� ������ � ����� ����;
	{
		return this->Vertices;
	}
	Matrix<> GetProjectedVertices()
	{
		return this->ProjectedVertices;
	}
	Matrix<int> GetFaces()//��������� ����� ������, ����� ������ � ����� ����;
	{
		return this->Faces;
	}
	Matrix<int> GetEdges() //��������� ����� ������, ����� ������ � ����� ����;
	{
		return this->Edges;
	}
	double GetVertexX(int n)//��������� ��������� ������� ������ � �������� �������;
	{
		return this->Vertices.getCell(0, n) / this->Vertices.getCell(3, n);
	}
	double GetVertexY(int n) //��������� ��������� ������� ������ � �������� �������;
	{
		return this->Vertices.getCell(1, n) / this->Vertices.getCell(3, n);
	}
	double GetVertexZ(int n) //��������� ��������� ������� ������ � �������� �������;
	{
		return this->Vertices.getCell(2, n)/this->Vertices.getCell(3,n);
	}

	void Apply(Matrix<>); // ���������� � ������ ��������� ��������������, ��������� ����� ��������;
	void Apply(); // ���������� � ������ ������������ �������� ��������������;
	void Project(Matrix<>); // ������������� ������.

};
Model3D::Model3D()
	:Vertices(Matrix<double>()), InitialVertices(Matrix<double>()), ProjectedVertices(Matrix<double>()), Faces(Matrix<int>()),Edges(Matrix<int>()), CumulativeAT(Identity3D())
{
}
Model3D::Model3D(const Matrix<int> faces, const Matrix<double> vertices)
	:Vertices(vertices), InitialVertices(this->Vertices), ProjectedVertices(Matrix<double>(3,this->Vertices.getCols())), Faces(faces), CumulativeAT(Identity3D())
{
	SetEdges();
}
Model3D::Model3D(string facesFilePath , string verticesFilePath)
	:Vertices(readVerticesFromFile(verticesFilePath)),Faces(readFacesFromFile(facesFilePath)), InitialVertices(this->Vertices), ProjectedVertices(Matrix<double>(3,this->Vertices.getCols())), CumulativeAT(Identity3D())
{
	SetEdges();
}
Model3D::Model3D(int M, int L)
	: Vertices(Matrix<double>(4,M)), InitialVertices(Matrix<double>(4,M)), ProjectedVertices(Matrix<double>(3,M)), Faces(Matrix<int>(L, 3)), CumulativeAT(Identity3D())
{
	SetEdges();
}
void Model3D:: Apply(Matrix<> AT) {
	DebugMatrix(AT, "At:");
	this->CumulativeAT = (AT * this->CumulativeAT);
	DebugMatrix(this->CumulativeAT, "Cumulative:");
}
void Model3D::Apply() {
	this->Vertices = this->CumulativeAT*this->InitialVertices;
	DebugMatrix(this->Vertices, "Vertices:");

}
//??WhoKnows
void Model3D::Project(Matrix<> P) {
	this->ProjectedVertices = P*this->Vertices;
}
void Model3D::SetEdges() {
	int K = this->Faces.getRows() * 3;
	int* edgeArray = new int[K * 3];
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

		edgeArray[k] = this->Faces.getCell(i, 0);
		k++;
		edgeArray[k] = this->Faces.getCell(i, 2);
		k++;

	}
	this->Edges = Matrix<int>(K, 2, edgeArray);
}
#endif MODEL3D_H