#include "Matrix.h"
#include <random>
#include <functional>


Matrix::Matrix()
{
	this->size = 0;
	this->matrix = nullptr;
}

Matrix::Matrix(int n)
{
	this->size = n;
	this->matrix = new int* [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(Matrix& m)
{
	this->size = m.size;
	this->matrix = new int* [size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = m.matrix[i][j];
		}
	}
}

Matrix::~Matrix()
{
	if (this->size != 0 && this->matrix != nullptr)
	{
		for (int i = 0; i < this->size; i++)
		{
			delete (matrix[i]);
		}
		delete matrix;
	}
}

Matrix& Matrix::sum(Matrix& m)
{
	Matrix* result;
	result = new Matrix(m.size);
	if (m.size == this->size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result->matrix[i][j] = m.matrix[i][j] + matrix[i][j];
			}
		}
		return *result;
	}
}

void Matrix::random_filling()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = rand();
		}
	}
}

Matrix& Matrix::product(Matrix& m)
{
	Matrix* result;
	result = new Matrix(m.size);
	if (m.size == this->size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result->matrix[i][j] = 0;
				for (int k = 0; k < size; k++)
				{
					result->matrix[i][j] += matrix[i][k] * m.matrix[k][j];
				}
			}
		}
		return *result;
	}
}

void prod_metho(Matrix& a, Matrix& b, Matrix& res, int begin, int end)
{
	for(int i = begin; i < end; i++)
	{
		for(int j = 0; j < res.get_size(); j++)
		{
			for(int k = 0; k < res.get_size(); k++)
			{
				res.matrix[i][j] = res.matrix[i][j] + a.matrix[i][k] * b.matrix[k][j];
			}
			
		}
	}
}




Matrix& Matrix::parallel_product(Matrix& m, const int amount_of_threads)
{
	Matrix* result;
	result = new Matrix(m.size);
	std::vector<std::thread> threads;
	threads.resize(amount_of_threads);
	int step = size / amount_of_threads;
	//std::thread tmp;
	if (m.size == this->size)
	{
		for (int i = 0; i < amount_of_threads; i++)
		{
			int cur_step = i * step;
			if (i == amount_of_threads - 1)
			{
				threads[i] = (std::thread(&prod_metho, std::ref(*this), std::ref(m), std::ref(*result), cur_step,
				                          size));
			}
			else
			{
				threads[i] = (std::thread(&prod_metho, std::ref(*this), std::ref(m), std::ref(*result), cur_step,
				                          cur_step + step));
			}
		}
	}
	for(int i = threads.size() - 1; i >= 0; i--)
	{
		threads[i].join();
		std::thread::id tmp = threads[i].get_id();
		std::cout << "Thread "<< tmp << " has finished." << std::endl;
	}
	return *result;
}

int Matrix::get_size()
{
	return this->size;
}

int Matrix::get_val(int i, int j)
{
	return matrix[i][j];
}


Matrix& Matrix::operator=(Matrix m)
{
	if (this == &m)
	{
		return *this;
	}

	this->size = m.size;
	this->matrix = new int* [size];
	for (int i = 0; i < size; i++)
	{
		this->matrix[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			this->matrix[i][j] = m.matrix[i][j];
		}
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, Matrix& m)
{
	for (int i = 0; i < m.size; i++)
	{
		for (int j = 0; j < m.size; j++)
		{
			out << m.matrix[i][j];
			out << ' ';
		}
		out << std::endl;
	}
	out << std::endl;
	return out;
}
