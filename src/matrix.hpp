#pragma once

#include "serializable.h"
#include <stdexcept>

template <class T>
class Matrix : public Serializable {
	int height;
	int width;
	T** pData;
public:
	Matrix(int height = 1, int width= 1) :height(height), width(width) {
		pData = new T*[height];
		for (int i = 0; i < height; i++) {
			pData[i] = new T[width];
			//TODO: remove this
			for (int j = 0; j < width; j++) {
				pData[i][j] = 1;
			}
			//TODO: endremove
		}
		std::cout << "pData pointer address: " << static_cast<void*>(pData) << std::endl;
		std::cout << "Original matrix:" << std::endl;
		print();
	}

	Matrix(const Matrix& m) {
		height = m.getHeight();
		width = m.getWidth();
		pData = new T*[height];
		for (int i = 0; i < height; i++) {
			pData[i] = new T[width];
			for (int j = 0; j < width; j++) {
				pData[i][j] = m[i][j];
			}
		}
	}

	int getHeight() const { return height; }
	int getWidth() const { return width; }

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
		for (int i = 0; i < width; i++) {
			delete[] pData[i];
		}
		delete[] pData; //TODO operator=
		height = m.getHeight();
		width = m.getWidth();
		pData = new T*[height];
		for (int i = 0; i < height; i++) {
			pData[i] = new T[width];
			for (int j = 0; j < width; j++) {
				pData[i][j] = m[i][j];
			}
		}
	}

	void print() {
		//TODO do it with iterators
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << " " << pData[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void fill(T t) {
		Iterator it = begin();
		do {
			*it = t;
		} while (it++ != end());
	}

	class Iterator {
		T* currentPointer;
		int currentPos;
		int maxPos;
	public:
		Iterator(T* currentPointer, int currentX, int currentY, int height, int width) :currentPointer(currentPointer), currentPos((currentX + 1) * (currentY + 1)), maxPos(width * height) {}

		Iterator operator++(int) {
			Iterator oldIterator = *this;
			currentPointer++;

			/*if (currentX++ == width) { //If we get to the last row, we want to reset the X coordinate
				currentX = 0;
				currentY++;
			}
			if (currentY == height) { //The last column is actually (height-1), so if we get here that means we are past the last item
				currentPointer = &(pData[width - 1][height - 1]); //end()
			} else {
				currentPointer = &(pData[currentX][currentY]);
			}
			*/
			if (currentPos++ > maxPos) {
				throw std::runtime_error("Iterator out of bounds");
			}
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
		return Iterator(&(pData[0][0]), 0, 0, height, width);
	}

	Iterator end() {
		return Iterator(&(pData[height- 1][width- 1]), 0, 0, height - 1, width- 1);
	}

	~Matrix() {
		for (int i = 0; i < width; i++) {
			delete[] pData[i];
		}
		delete[] pData;
	}
};
