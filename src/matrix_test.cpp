#include "matrix.hpp"

int main() {
	Matrix<int> m1(10, 10);
	Matrix<int> m2(20, 20);
	Matrix<int> m3 = m1 + m2;
	m1.fill(10);
}