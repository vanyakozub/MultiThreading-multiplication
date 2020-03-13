#include"Matrix.h"
#include <ctime>




int main()
{
	Matrix m1 (1600);
	m1.random_filling();
	//std::cout << m1;
	Matrix m2 (1600);
	m2.random_filling();
	//std::cout << m2;
	clock_t t0 = clock();
	Matrix m3 (m1.product(m2));
	clock_t t1 = clock();
	//std::cout << m3;
	std::cout << "Done in: "<<(double)(t1 - t0)/CLOCKS_PER_SEC << std::endl;

	int amount = 16;
	clock_t t3 = clock();
	Matrix m4 = m1.parallel_product(m2, amount);
	clock_t t4 = clock();
	//std::cout << m4;
	std::cout << "Done with " << amount <<" threads!" << std::endl;

	std::cout <<"In: " << (double)(t4 - t3) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
