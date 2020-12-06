#ifndef MODEL2D_H
#define MODEL2D_H
#include "Matrix.h"
#include "AffineTransform.h"
#include <iostream>
#include <fstream>

class Model2D
{
//из файла конструктор 2 файла
//bool процедура для ввода в фалйе размер задан
private:
	Matrix<double> vertex;
	Matrix<double> initial_vertex;
	Matrix<double> edges;
	Matrix<double> cumulativeAT;
public:
	Model2D();
	Model2D(int, int);
	
	Model2D(Matrix<double>, Matrix<double>);
	void setVertices(Matrix<double>);
	void setEdges(Matrix<double>);
	bool getVerticesFromFile(ifstream &f);
	bool getEdgesFromFile(ifstream &f);
	Matrix<double> getEdges() { return this->edges; }
	Matrix<double> getVertices() { return this->vertex; }
	void apply(Matrix<double>);
	void apply();
	double getPrismCenterX() {
		return
		(this->getVertices().getCell(0, 0) + this->getVertices().getCell(0, 1) + this->getVertices().getCell(0, 2)) / 3.0;
	}
	double getPrismCenterY() {
		return
		(this->getVertices().getCell(1, 0) + this->getVertices().getCell(1, 1) + this->getVertices().getCell(1, 2)) / 3.0;
	}


};

Model2D::Model2D()
	:vertex(Matrix<double>()), initial_vertex(Matrix<double>()),edges(Matrix<double>()),cumulativeAT(Identity())
{
}
Model2D::Model2D(int K, int M)
	: vertex(Matrix<double>(3, M)), initial_vertex(Matrix<double>(3, M)), edges(Matrix<double>(K, 2)), cumulativeAT(Identity())
{
}
Model2D::Model2D(Matrix<double> vertex, Matrix<double> edges)
	:vertex(vertex),initial_vertex(vertex),edges(edges),cumulativeAT(Identity())
{
}
void Model2D:: setVertices(Matrix<double> vertex) 

{
	this->vertex = vertex;
	this->initial_vertex = vertex;
}
void Model2D:: setEdges(Matrix<double> edges) 
{
	this->edges = edges;
}

void Model2D::apply(Matrix<double> AT) 
{
	this->cumulativeAT = (AT * this->cumulativeAT);
}
void Model2D::apply()
{
	this->vertex = (  this->cumulativeAT*this->initial_vertex);
}
bool Model2D::getVerticesFromFile(ifstream &f) {
	if (!f.is_open()) 
	{
		return 0;
	}
	//auto tmp = this->vertex;
	try {
		int m;
		f >> m;
		this->vertex = Matrix<double>(3, m);
		f >> this->vertex;
		this->initial_vertex = this->vertex;
	}
	catch(exception e){
	//	this->vertex = tmp;
		return 0;
	}
	return 1;
}
bool Model2D::getEdgesFromFile(ifstream &f) {
	if (!f.is_open())
	{
		return 0;
	}
	auto tmp = this->edges;
	try {
		int k;
		f >> k;
		this->edges = Matrix<double>(k, 2);
		f >> this->edges;
	}
	catch (exception e) {
		this->edges = tmp;
		return 0;
	}
	return 1;
}




#endif MODEL2D_H