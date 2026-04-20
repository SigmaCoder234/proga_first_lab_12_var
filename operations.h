#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "square_matrix.h"

// Складывает две матрицы
void addMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b);

// Умножает две матрицы
void multiplyMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b);

// Умножает матрицу на скаляр
void MatrixByScalar(SquareMatrix* res, const SquareMatrix* a, const void* scalar);

#endif