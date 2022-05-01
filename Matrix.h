//
// Created by user on 30.04.22.
//

#ifndef LAB_2_1_MATRIX_H
#define LAB_2_1_MATRIX_H

class Matrix {
private:
    int linesAmount;
    int columnsAmount;
    int ** matrixArr{};

public:
    Matrix();

    int getLinesAmount();
    void setLinesAmount(int lines_amount);

    int getColumnsAmount();
    void setColumnsAmount(int columns_amount);

    int **getMatrixArr() const;

    Matrix(Matrix&& x) noexcept;

    Matrix(int lines_amount, int columns_amount);

    Matrix& operator = (Matrix&& x) noexcept;

    ~Matrix();

    void initializeMatrixArray();

    int getElementByLineIndexAndColumnIndex(int lineIndex, int columnIndex);

    void setElementByLineIndexAndColumnIndex(int lineIndex, int columnIndex, int value);
};

#endif //LAB_2_1_MATRIX_H