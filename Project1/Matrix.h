#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <thread>

class Matrix
{
private: int size;
public: int** matrix;
public:
	Matrix();
	Matrix(int n);
	Matrix(Matrix& m);
	~Matrix();
	Matrix& sum(Matrix &m);
	void random_filling();
	Matrix& product(Matrix &m);
	void prod_method(/*Matrix& b, Matrix& res, */int begin, int end);
	Matrix& parallel_product(Matrix& m, int amount_of_threads);
	int get_size();
	int get_val(int i, int j);
	//Matrix& operator= (Matrix& m);
	Matrix& operator=(Matrix m);
	friend std::ostream& operator<<(std::ostream& out,  Matrix  &m);
	//std::string operator<<(Matrix m);
};


#endif
