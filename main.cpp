#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "Matrix.h"
#include "MatrixOperations.h"

using namespace std;

static string importFilePath;

static string defaultImportFilePath = "in.txt";
static string defaultExportFilePath = "out.txt";

void printGeneralInfo();

static string receiveAndValidateFilePathForImportData();

static Matrix* receiveMatrixFromInputFileStream(ifstream& inputFileStream);

static string receiveAndValidateFilePathForExportData();

void exportMatrixToFile(Matrix* matrix, ofstream& outputFileStream);

int main() {

    printGeneralInfo();

    importFilePath = receiveAndValidateFilePathForImportData();

    ifstream inputFileStream (importFilePath, ios::in);

    Matrix* matrix = receiveMatrixFromInputFileStream(inputFileStream);

    MatrixOperations::printIndexesOfTheFirstSaddleElement(matrix);

    string exportFilePath = receiveAndValidateFilePathForExportData();

    MatrixOperations::exchangeCornerValues(matrix);

    ofstream outputFileStream(exportFilePath, ios::out);

    exportMatrixToFile(matrix, outputFileStream);

    return 0;
}

void printGeneralInfo() {

    cout << "Project 'Lab 2_1'" << endl;
    cout << "This project has been created by Kostiantyn Dementiev" << endl;
    cout << "Student of K-18 group" << endl;
    cout << "Tasks: " << endl;
    cout << "Task number 98 - print indexes of first saddle element in the matrix" << endl;
    cout << "Task number 138 - exchange the values in the upper left and lower right corners of the matrix" << endl;
}

static std::string removeSpaces(std::string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

static string getFileSeparator() {
#ifdef _WIN32
    return "\\";
##elifdef defined(_WIN64)
    return "\\";
#else
    return "/";
#endif
}

static string receiveAndValidateFilePathForImportData() {

    string filePath;
    string input;
    bool validFilePath = false;

    cout << "Please, enter file path for import matrix info: " << endl;

    string cwd = filesystem::current_path().string() + getFileSeparator() + "../";

    while (!validFilePath) {

        cin >> input;
        removeSpaces(input);

        filePath = cwd + input;

        if (filePath.empty()) {

            return defaultImportFilePath;

        } else {

            try {

                ifstream myfile (filePath);

                if (!myfile.is_open()) {

                    throw runtime_error("Not valid");
                }

                validFilePath = true;

            } catch (runtime_error er) {

                cout << "Your file could not be opened. Please, enter file path once more" << endl;
            }
        }
    }

    return filePath;
}

static string receiveAndValidateFilePathForExportData() {

    string filePath;
    string input;
    bool validFilePath = false;

    cout << "Please, enter file path for export matrix: " << endl;

    string cwd = filesystem::current_path().string() + getFileSeparator() + "../";

    while (!validFilePath) {

        cin >> input;
        removeSpaces(input);

        filePath = cwd + input;

        if (filePath.empty()) {

            return defaultImportFilePath;

        } else {

            try {

                ifstream myfile (filePath);

                if (!myfile.is_open()) {

                    throw runtime_error("Not valid");
                }

                validFilePath = true;

            } catch (runtime_error er) {

                cout << "Your file could not be opened. Please, enter file path once more" << endl;
            }
        }
    }

    return filePath;
}

static Matrix* receiveMatrixFromInputFileStream(ifstream& inputFileStream) {

    try  {
        string firstLine;
        getline(inputFileStream, firstLine);

        int dimensions[2];

        istringstream iss(firstLine);
        string s;

        int dimensionCounter = 0;
        while ( getline( iss, s, ' ' ) ) {

            dimensions[dimensionCounter] = stoi(s, 0, 10);
            dimensionCounter++;

        }
        const int inputLinesAmount = dimensions[0];
        const int inputColumnsAmount = dimensions[1];

        Matrix* matrix = new Matrix;
        matrix -> setLinesAmount(inputLinesAmount);
        matrix -> setColumnsAmount(inputColumnsAmount);
        matrix -> initializeMatrixArray();

        int linesCounter = 0;
        string line;
        while (getline (inputFileStream, line)) {
            if (!line.empty()) {

                istringstream iss(line);
                string s;
                int columnsCounter = 0;

                while ( getline( iss, s, ' ' ) ) {

                    matrix->setElementByLineIndexAndColumnIndex(linesCounter, columnsCounter, stoi(s, 0, 10));
                    columnsCounter++;
                }

                if (columnsCounter != inputColumnsAmount) {
                    throw runtime_error(importFilePath + ": INPUT ERROR");
                }
            }
            linesCounter++;
        }

        if (linesCounter != inputLinesAmount) {
            throw runtime_error(importFilePath + ": INPUT ERROR");
        }
        inputFileStream.close();

        return matrix;

    } catch (runtime_error err) {

        cerr << err.what();
    }
}

void exportMatrixToFile(Matrix* matrix, ofstream& outputFileStream) {

    int maxMatrixElement = 0;
    for (int line = 0; line < matrix->getLinesAmount(); line++) {
        for (int col = 0; col < matrix->getColumnsAmount(); col++) {

            if (maxMatrixElement < matrix->getElementByLineIndexAndColumnIndex(line,col)) {
                maxMatrixElement = matrix->getElementByLineIndexAndColumnIndex(line,col);
            }
        }
    }

    int maxElementLength = to_string(maxMatrixElement).length();
    for (int line = 0; line < matrix->getLinesAmount(); line++) {

        string matrixLine;

        for (int col = 0; col < matrix->getColumnsAmount(); col++) {

            int element = matrix->getElementByLineIndexAndColumnIndex(line,col);

            if (to_string(element).length() != maxElementLength) {
                int spacesAmount = maxElementLength - to_string(element).length();

                for (int i = 0; i < spacesAmount; i++) {

                    matrixLine += " ";

                }
            }

            matrixLine += to_string(element) + " ";
        }

        outputFileStream << matrixLine << endl;
    }
}