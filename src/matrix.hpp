#pragma once

#include "serializable.h"
#include <stdexcept>

template <class T>
class Matrix : public Serializable {
	int width;
	int height;
	T** pData;
public:
	Matrix(int width = 1, int height = 1) :width(width), height(height) {
		pData = new T*[width];
		for (int i = 0; i < width; i++) {
			pData[i] = new T[height];
		}
	}

	Matrix(const Matrix& m) {
		width = m.getWidth();
		height = m.getHeight();
		pData = new T*[width];
		for (int i = 0; i < width; i++) {
			pData[i] = new T[height];
			for (int j = 0; j < height; j++) {
				pData[i][j] = m[i][j];
			}
		}
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	Matrix operator+(Matrix m) { //throws error if the two matrices are not of equal size
		if ((width == m.getWidth()) && (height == m.getHeight())) {
			Matrix newMatrix(width, height);
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
							newMatrix[x2][y1] += pData[x1][y1] * m[x2][y2];
							y2++;
						}
						y2 = 0;
					}
				}
			} else {
				for (int x2 = 0; x2 < height; x2++) {
					for (int y1 = 0; y1 < m.getWidth(); y1++) {
						for (int x1 = 0; x1 < width; x1++) {
							newMatrix[x2][y1] += pData[x1][y1] * m[x2][y2];
							y2++;
						}
						y2 = 0;
					}
				} //TODO: CHECK IF THIS ACTUALLY WORKS (bocsi ha nem, pedig én átgondoltam és jónak tûnt :(  )

			}
			return newMatrix;
		}
	}

	T* operator[](int index) const { //returns the indexth row of pData array
		return pData[index];
	}

	Matrix operator=(Matrix m) {
		delete[] pData; //TODO operator=
	}

	void print() {
		//TODO print
	}

	void fill(T t) {
		//TODO fill
	}

	class Iterator {
		T* currentPointer;
		int currentX = 0;
		int currentY = 0;
		//TODO not sure if actually needed
		bool iterateRight = true; //If false, the iteration goes column by column instead of row by row
	public:
		Iterator(T* currentPointer) :currentPointer(currentPointer) {}

		Iterator& operator++(int) {
			Iterator oldIterator = *this;

			if (iterateRight) {
				if (currentX++ == width) {
					currentX = 0;
					currentY++;
				}
				if (currentY == height) {
					currentPointer = end();
				} else {
					currentPointer = pData[currentX][currentY];
				}
			} else { //We iterate downwards - useful with Matrix multiplication
				if (currentY++ == height) {
					currentY = 0;
					currentX++;
				}
				if (currentX == width) {
					currentPointer = end();
				} else {
					currentPointer = pData[currentX][currentY];
				}
			}

			return oldIterator;
		}

		bool operator !=(Iterator const & that) {
			return this->currentPointer != that.currentPointer;
		}

		T& operator*() {
			return *currentPointer;
		}
	};

	Iterator begin() {
		currentX = 0;
		currentY = 0;
		currentPointer = pData[0][0];
		return currentPointer;
	}

	Iterator end() {
		currentX = width - 1;
		currentY = height - 1;
		currentPointer
	}

	~Matrix() {
		for (int i = 0; i < width; i++) {
			delete[] pData[i];
		}
		delete[] pData;
	}
};
