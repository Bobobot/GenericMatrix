#include "matrix.hpp"

#include <iostream>

int main() {
	Matrix<int> m1(5, 6);
	std::cout << "Original m1:" << std::endl;
	std::cout << m1;
	std::cout << "End of m1" << std::endl;
	Matrix<int> m2(6, 5);
	std::cout << "Original m2:" << std::endl;
	std::cout << m2;
	std::cout << "End of m2" << std::endl;
	m1[0] = 1;
	m1[1] = 2;
	m1[2] = 3;
	m2[0] = 1;
	m2[1] = 2;
	m2[2] = 3;
	std::cout << m1;
	std::cout << m2;
	Matrix<int> m3(1, 2);
	std::cout << "m3 multiplicatoin:\n";
	m3 = m1 * m2;
	std::cout << std::endl << std::endl << m3;
}