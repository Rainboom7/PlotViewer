/*
#include "Model3D.h"
using namespace std;

void test1() {
	
			Matrix<int> M(2);
			cout << "Input M ->\n ";
			cin >> M;
		
	double a[6] = { 2, 1, 3, 0, 1, 1 };
	double b[9] = { 1, 0, 1, 0, 1, 3, 0, 0, 1 };

	Matrix<> A(3,2, a);
	Matrix<> B(3, b);

	cout << A << endl << B;
	Matrix<> C = B * A;
	cout << endl << "C =" << endl << C;
	
	cout << endl << "A =" << endl << A
		<< endl << "B =" << endl << B
		<< endl << "C =" << endl << C
		<< endl << "A+B =" << endl << (A + B)
		<< endl << "A-B =" << endl << (A - B)
		<< endl << "T(1,2) =" << endl << Translation(1, 2);
	system("pause");

}

void test2() {

	double v[6] = { 2, 1, 3, 0, 1, 1 };
	Matrix<> V(3, 2, v);
	double e[2] = { 1, 2 };
	cout << V;
	Matrix<double> E(1, 2, e);
	Model2D model(V, E);
	cout << endl << "Identity:" << endl << model.cumulativeAT;
	cout<< endl << "Edges:" << endl << model.getEdges()
		<< endl << "Vertices before AT:" << endl << model.getVertices();
	cout << "cumul before" << endl;

	cout << model.cumulativeAT;
	model.apply(Translation(1, 3));
	model.apply();
	cout << "cumul after" << endl;
	cout << model.cumulativeAT;
	cout
		<< endl << "Vertices after AT:" << endl << model.getVertices();
		
	system("pause");

}

void test3() 
{


Model2D test_model;
ifstream f_edg("input_edg.txt");
ifstream f_vert("input_vert.txt");
test_model.getEdgesFromFile(f_edg);
test_model.getVerticesFromFile(f_vert);
cout <<"edges"<<endl<< test_model.edges;
cout << "vertex"<<endl<<test_model.vertex;
f_edg.close();
f_vert.close();
system("pause");
}


void test3d_1() {
	Model3D model;
}
void main()
{
	
	
}
*/
