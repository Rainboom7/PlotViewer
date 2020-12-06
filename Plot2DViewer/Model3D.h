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
	//из файла конструктор 2 файла
	//bool процедура для ввода в фалйе размер задан
private:
	 Matrix<> Vertices;
	 Matrix<> InitialVertices;
	 Matrix<> ProjectedVertices;
	 Matrix<int> Faces;
	 Matrix<int> Edges;
	 Matrix<double> CumulativeAT;
public:
	Model3D();//конструктор по умолчанию;
	Model3D(const Matrix<int>, const Matrix<double>); // конструктор создания модели по заданным карте вершин и карте граней;
	Model3D(string, string); // конструктор создания модели по именам файлов, в которых лежат карта вершин и карта граней;
	Model3D(int, int);//конструктор с данными M и L
	void SetEdges(); //создание карты рёбер по заданной карте граней
	Matrix<> GetVertices();//получение карты вершин, карты граней и карты рёбер;
	Matrix<int> GetFaces();//получение карты вершин, карты граней и карты рёбер;
	Matrix<int> GetEdges();//получение карты вершин, карты граней и карты рёбер;
	double GetVertexX(int);//получение координат вершины модели с заданным номером;
	double GetVertexY(int); //получение координат вершины модели с заданным номером;
	double GetVertexZ(int); //получение координат вершины модели с заданным номером;
	void Apply(Matrix<>); // применение к модели аффинного преобразования, заданного своей матрицей;
	void Apply(); // применение к модели накопленного афинного преобразования;
	void Project(Matrix<>); // проецирование модели.
private:
	//???????Вопрос по формированию ребер из граней
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