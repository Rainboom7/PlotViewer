#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
private:
	int rows,cols;
	Cell **cells;
	void AllocateCells(int,int);
	void FreeCells();
public:
	Matrix() : rows(0),cols(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int);							// Конструктор нулевой кв.матрицы
	Matrix(int,int);							// Конструктор нулевой прямоуг. матрицы
	Matrix(int, Cell*);							// Конструктор кв.матрицы из списка						
	Matrix(int,int, Cell*);						// Конструктор прямоуг.матрицы из списка
	~Matrix();								  // Деструктор
    

	Matrix transpose();
	Cell getCell(int i, int j) { return cells[i][j]; }
	void setCell(int i,int  j,Cell value) { cells[i][j]=value; }
	int getRows() { return this->rows; }
	int getCols() { return this->cols; }
	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};


template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{

	AllocateCells(M.rows,M.cols);
	for (int i = 0; i < M.rows; i++)
		for (int j = 0; j < M.cols; j++)
			cells[i][j] = M.cells[i][j];
}
template <typename Cell>
Matrix<Cell> Matrix<Cell>::transpose()
{
	Matrix<> newMatrix( this->cols, this->rows );
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			newMatrix(j, i) = cells[i][j];
	return newMatrix;
}
template <typename Cell>
Matrix<Cell>::Matrix(int Size)
{

	AllocateCells(Size,Size);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = 0;
}
template <typename Cell>
Matrix<Cell>::Matrix(int rows,int cols)
{

	AllocateCells(rows,cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = 0;
}
template <typename Cell>
Matrix<Cell>::Matrix(int Size, Cell* list)
{
	AllocateCells(Size,Size);
	int k = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			cells[i][j] = list[k];
			++k;
		}
}

template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols, Cell* list)
{
	int k = 0;
	AllocateCells(rows,cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			cells[i][j] = list[k];
			++k;
		}
}


template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if ((rows != M.rows)&&(cols!=M.cols))
	{
		FreeCells();
		AllocateCells(M.rows,M.cols);
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if ((rows == M.rows)&&(cols==M.cols))
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if ((rows == M.rows) && (cols == M.cols))
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	if (this->cols != M.rows)
		throw exception("Bad matrix sizes");
	Matrix<Cell> res(this->rows, M.cols);
		for (int i = 0; i < this->rows; i++)
			for (int j = 0; j < M.cols; j++)
					for (int k = 0; k < this->cols; k++)		
						res.cells[i][j] += this->cells[i][k] * M.cells[k][j];
	return res;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int Rows,int Cols)
{
	rows = Rows;
	cols = Cols;
	cells = new Cell*[Rows];
	for (int i = 0; i < Rows; i++)
		cells[i] = new Cell[Cols];
	
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i < rows; i++)
		delete cells[i];
	delete cells;
	rows = 0;
	cols = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.rows; i++)
		for (int j = 0; j < M.cols; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.rows; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.cols; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H
