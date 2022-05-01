//
// Created by user on 30.04.22.
//

#ifndef LAB_2_1_MATRIXOPERATIONS_H
#define LAB_2_1_MATRIXOPERATIONS_H

#include <string>
#include "Matrix.h"

using namespace std;

class MatrixOperations {

public:
    static void printIndexesOfTheFirstSaddleElement(Matrix* matrix);

    static void exchangeCornerValues(Matrix* matrix);
};

#endif //LAB_2_1_MATRIXOPERATIONS_H
