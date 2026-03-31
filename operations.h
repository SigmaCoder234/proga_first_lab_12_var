#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "square_matrix.h"

// Складывает две матрицы
SquareMatrix* addMatrices(const SquareMatrix* a, const SquareMatrix* b);

// Умножает две матрицы
SquareMatrix* multiplyMatrices(const SquareMatrix* a, const SquareMatrix* b);

// Умножает матрицу на скаляр
SquareMatrix* MatrixByScalar(const SquareMatrix* a, const void* scalar);

#endif