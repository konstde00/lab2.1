//
// Created by user on 30.04.22.
//

#include <iostream>
#include <string>
#include "Matrix.h"
#include "MatrixOperations.h"

//index countdown starts with 0 (element in left higher corner will have index [0;0]
void MatrixOperations::printIndexesOfTheFirstSaddleElement(Matrix* matrix) {
    //example
    int counter = 1;

    int lineMaximums[matrix->getLinesAmount()];
    int columnMinimums[matrix->getColumnsAmount()];

    //getting line maximums
    for (int line = 0; line < matrix->getLinesAmount(); line++) {

        int lineMaximum = matrix->getElementByLineIndexAndColumnIndex(line, 0);
        for (int col = 0; col < matrix->getColumnsAmount(); col++) {

            if (lineMaximum < matrix->getElementByLineIndexAndColumnIndex(line, col)) {
                lineMaximum = matrix->getElementByLineIndexAndColumnIndex(line, col);
            }
        }

        lineMaximums[line] = lineMaximum;
    }

    //getting column minimums
    for (int col = 0; col < matrix->getColumnsAmount(); col++) {

        int columnMinimum = matrix->getElementByLineIndexAndColumnIndex(0, col);
        for (int line = 0; line < matrix->getLinesAmount(); line++) {

            if (columnMinimum > matrix->getElementByLineIndexAndColumnIndex(line, col)) {
                columnMinimum = matrix->getElementByLineIndexAndColumnIndex(line, col);
            }
        }

        columnMinimums[col] = columnMinimum;
    }

    string output;
    for (int line = 0; line < matrix->getLinesAmount(); line++) {
        for (int col = 0; col < matrix->getColumnsAmount(); col++) {

            if (columnMinimums[col] == lineMaximums[line]) {
                output = "Indexes of first saddle element: "
                         + string ("[", 1) + to_string(line) + ";" + to_string(col) + "] \n";
                break;
            }
        }
    }

    if (output.empty()) {
        output = "Saddle elements were not found \n";
    }

    cout << output;
}

void MatrixOperations::exchangeCornerValues(Matrix* matrix) {

    if (matrix->getColumnsAmount() != matrix->getLinesAmount()) {

        cout << "Exchanging corner values is not possible because matrix is not square";
    } else {

        int dimensionValue = matrix->getLinesAmount() - 1;

        for (int line = 0; line < dimensionValue; line++) {

            for (int col = 0; col < dimensionValue; col++) {

                if (line + col < dimensionValue) {

                    int x = matrix->getElementByLineIndexAndColumnIndex(line, col);
                    int y = matrix->getElementByLineIndexAndColumnIndex(dimensionValue - col, dimensionValue - line);
                    matrix->setElementByLineIndexAndColumnIndex(line, col, y);
                    matrix->setElementByLineIndexAndColumnIndex(dimensionValue - col, dimensionValue - line, x);
                }
            }
        }
    }
}
