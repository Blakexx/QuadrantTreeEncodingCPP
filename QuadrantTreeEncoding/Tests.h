#pragma once
#include "Library.h"
#include "Matrix.h"

template<typename T>
Matrix<T>* generateMatrix(size_t rows, size_t cols, double fullness, function<size_t(size_t,vector<size_t>&)> pointPicker, function<T(size_t, size_t)> valuePicker, T defaultValue) {
    size_t count = (size_t)round(rows * cols * fullness);
    vector<size_t> points;
    Matrix<T>* matrix = new Matrix<T>(rows,cols);
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            matrix->set(r, c, defaultValue);
            points.push_back(r*cols+c);
        }
    }
    for (size_t num = 0; num < count; num++) {
        size_t point = pointPicker(num, points);
        size_t r = point / cols;
        size_t c = point % cols;
        matrix->set(r,c,valuePicker(r,c));
    }
    return matrix;
}

template<typename T>
void printMatrix(Matrix<T>* matrix) {
    size_t rows = matrix->getRows(), cols = matrix->getCols();
    for (size_t r = 0; r < rows; r++) {
        cout << "[";
        for (size_t c = 0; c < cols; c++) {
            cout << matrix->get(r, c);
            if (c < cols - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        cout << endl;
    }
}

template<typename T>
inline T readData(string name, function<bool(T)> tester) {
    T value;
    bool failed = false;
    do {
        cin.clear();
        if (failed) {
            cin.ignore(1000, '\n');
        }
        cout << endl << name << ": ";
        cin >> value;
        failed = cin.fail();
    } while (failed || !tester(value));
    return value;
}

//void readWriteTester(double fullness, double cachePercent);

//void printIf(string toPrint, bool doPrint);

//double* runSetTests(bool doPrint);