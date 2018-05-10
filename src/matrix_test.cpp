#include "matrix.hpp"
#include "memtrace.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>

int main() {
	//Initializing random generation for later
	srand(time(0));

	//Testing addition
	Matrix<int> m1(5, 6); //Creating two matrices
	Matrix<int> m2(5, 6);
	m1.fill(4); //Filling the matrices
	m2.fill(20);
	Matrix<int> m3; //Testing constructor with no parameters
	m3 = m1 + m2; //Testing operator= and operator+
	std::cout << m3; //Testing operator<<
	Matrix<int> m4 = m1 + m3; //Testing copy constructor and operator+

	//Testing multiplication with another matrix
	Matrix<int> m5(30, 10); //Creating two matrices
	Matrix<int> m6(10, 30);
	m5.fill(2);
	m6.fill(3);
	Matrix<int> m7 = m5*m6; //Testing operator* 
	Matrix<int> m8(4, 20); //Creating a matrix with a deliberately bad size for multiplication - we expect it to be overridden
	m8 = m5*m6;
	std::cout << m8;

	//Testing multiplication with another object
	Matrix<int> m9(5, 10);
	m9.fill(2);
	Matrix<int> m10 = m9 * 2;
	std::cout << m10;

	//Testing error handling
	Matrix<int> m11(5, 6); //Creating two matrices that can not be added by definition
	Matrix<int> m12(10, 20); 
	try {
		Matrix<int> m13 = m11 + m12;
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	Matrix<int> m14(10, 20); //Creating two matrices that can not be multiplied by definition
	Matrix<int> m15(30, 40);
	try {
		Matrix<int> m16 = m14*m15;
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}

	//Testing iterators
	Matrix<int> m17(5, 10);
	Matrix<int>::Iterator it = m17.begin();
	while (it != m17.end()) {
		*it++ = rand() % 90 + 10; //The matrix is filled with random values from 10-99
	}

	//Testing serializability
	std::stringstream ss;
	std::cout << m17;
	m17.write(ss);
	Matrix<int> m18;
	m18.read(ss);
	std::cout << m18; //Should be the same as m15
}