#pragma once

#include "serializable.h"
#include <stdexcept>

template <class T>
class Matrix : public Serializable {
	int height;
	int width;
	T* pData;
public:
	Matrix(int height = 1, int width = 1) :height(height), width(width) {
		if (height == 0 || width == 0) throw std::invalid_argument("Height or width can not be equal to 0!");
		pData = new T[height*width];
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pData[i*width + j] = T();
			}
		}
	}

	Matrix(const Matrix& m) {
		height = m.getHeight();
		width = m.getWidth();
		pData = new T[height*width];
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pData[i*width + j] = m[i * (m.getWidth()) + j];
			}
		}
	}

	int getHeight() const { return height; }
	int getWidth() const { return width; }

	Matrix operator+(Matrix m) { //throws error if the two matrices are not of equal size
		if ((width == m.getWidth()) && (height == m.getHeight())) {
			Matrix newMatrix(height, width);
			//We have to iterate through all three matrices - we add the values of the first and second matrices, and store them in the third one
			Matrix::Iterator it1 = begin();
			Matrix::Iterator it2 = m.begin();
			Matrix::Iterator it3 = newMatrix.begin();
			while (it1 != end()) { //Doesn't matter which iterator we check, as the three matrices are of equal size and they all increment at the same time
				*it3++ = *it1++ + *it2++;
			}
			return newMatrix;
		} else {
			throw std::runtime_error("The two Matrices can not be added!");
		}
	}

	Matrix operator*(int i) {
		Matrix newMatrix(width, height);
		newMatrix = *this;
		Matrix::Iterator it = begin();
		while (it != end()) {
			*it++ = *it * i;
		}
		return newMatrix;
	}

	Matrix operator*(Matrix m) { //throws error if the two matrices are not able to be multipled
		if (width != m.getHeight()) {
			throw std::runtime_error("The two Matrices can not be multiplied!");
		} else {
			Matrix newMatrix(m.getWidth(), height);
			newMatrix.fill(0);
			//Not done with iterators as that would be unnecessarily complicated - this way it's only necessarily complicated
			int x2 = 0;
			int y2 = 0;
			if (height < m.getWidth()) {
				for (int y1 = 0; y1 < height; y1++) {
					for (int x2 = 0; x2 < m.getWidth(); x2++) {
						for (int x1 = 0; x1 < width; x1++) {
							newMatrix[y1*newMatrix.getWidth() + x2] += pData[y1*width + x1] * m[y2*m.getWidth() + x2]; //newMatrix[x2][y1] += pData[x1][y1] * m[x2][y2];
							y2++;
						}
						y2 = 0;
					}
				}
			} else {
				for (int x2 = 0; x2 < height; x2++) {
					for (int y1 = 0; y1 < m.getWidth(); y1++) {
						for (int x1 = 0; x1 < width; x1++) {
							newMatrix[y1*newMatrix.getWidth() + x2] += pData[y1*width + x1] * m[y2*m.getWidth() + x2]; //newMatrix[x2][y1] += pData[x1][y1] * m[x2][y2];
							y2++;
						}
						y2 = 0;
					}
				}

			}
			return newMatrix;
		}
	}

	T& operator[](int index) const { //returns the indexth element of pData array
		return pData[index];
	}

	Matrix& operator=(Matrix m) {
		delete[] pData;
		height = m.getHeight();
		width = m.getWidth();
		pData = new T[height*width];
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pData[i*width + j] = m[i*m.getWidth() + j];
			}
		}
		return *this;
	}

	void fill(T t) {
		Iterator it = begin();
		while (it != end()) {
			*it++ = t;
		}
	}

	class Iterator {
		T* currentPointer;
	public:
		Iterator(T* currentPointer) :currentPointer(currentPointer) {}

		Iterator operator++(int) {
			Iterator oldIterator = *this;
			currentPointer++;
			return oldIterator;
		}

		bool operator !=(Iterator const & that) {
			return this->currentPointer != that.currentPointer;
		}

		void operator=(T t) {
			*currentPointer = t;
		}

		T& operator*() {
			return *currentPointer;
		}
	};

	Iterator begin() {
		return Iterator(&(pData[0]));
	}

	Iterator end() {
		return Iterator(&(pData[height*width]));
	}

	void write(std::ostream& os) const {
		//TODO
	}

	void read(std::istream& is) {
		//TODO
	}

	~Matrix() {
		delete[] pData;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T> m) {
	Matrix<T>::Iterator it = m.begin();
	int i = 0;
	while (it != m.end()) {
		os << *it++ << " ";
		if (++i % m.getWidth() == 0) os << std::endl;
	}
	return os;
}