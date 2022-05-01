//
// Created by user on 30.04.22.
//

#include "Matrix.h"
#include <iostream>
#include <string>

using namespace std;

Matrix::Matrix() {

};

Matrix::Matrix(Matrix &&x) noexcept : matrixArr(x.matrixArr) {
    x.matrixArr = nullptr;
}

Matrix &Matrix::operator=(Matrix &&x) noexcept {

    if (&x == this) {
        return *this;
    }

//        delete matrix;

    *matrixArr = *x.matrixArr;

    return *this;
}

Matrix::Matrix(int lines_amount, int columns_amount) {
    linesAmount = lines_amount;
    columnsAmount = columns_amount;
    matrixArr = (int**) new int*[lines_amount];

    for (int i = 0; i < lines_amount; i++) {
        matrixArr[i] = (int*) new int[columns_amount];
    }

    for (int i = 0; i < lines_amount; i++) {
        for (int j = 0; j < columns_amount; j++) {
            matrixArr[i][j] = 0;
        }
    }
}

Matrix::~Matrix() {
//    delete matrixArr;
}

int Matrix::getElementByLineIndexAndColumnIndex(int lineIndex, int columnIndex) {

//    cout << "Actual lines amount: " + to_string(linesAmount) + ", column amount: " + to_string(columnsAmount) + "\n";

    try {

//        if (this -> linesAmount <= linesAmount || this -> columnsAmount <= columnIndex) {
//            throw runtime_error("[" + to_string(lineIndex) + "," + to_string(columnIndex) + "]: OUT OF RANGE");
//        }

        return matrixArr[lineIndex][columnIndex];

    } catch (exception ex) {
        cerr << ex.what();
    }
}

int Matrix::getLinesAmount() {
    return linesAmount;
}

void Matrix::setLinesAmount(int lines_amount) {
    linesAmount = lines_amount;
}

int Matrix::getColumnsAmount() {
    return columnsAmount;
}

void Matrix::setColumnsAmount(int columns_amount) {
    columnsAmount = columns_amount;
}

void Matrix::setElementByLineIndexAndColumnIndex(int lineIndex, int columnIndex, int value) {

    if (lineIndex >= linesAmount || columnIndex >= columnsAmount) {
        throw runtime_error("[" + to_string(lineIndex) + "," + to_string(columnIndex) + "]: OUT OF RANGE");
    }

    this -> matrixArr[lineIndex][columnIndex] = value;
}

int **Matrix::getMatrixArr() const {
    return matrixArr;
}

void Matrix::setMatrixArr(int **matrixArr) {
    Matrix::matrixArr = matrixArr;
}

void Matrix::initializeMatrixArray() {
    matrixArr = (int**) new int*[linesAmount];

    for (int i = 0; i < linesAmount; i++) {
        matrixArr[i] = (int*) new int[columnsAmount];
    }

    for (int i = 0; i < linesAmount; i++) {
        for (int j = 0; j < columnsAmount; j++) {
            matrixArr[i][j] = 0;
        }
    }
}
