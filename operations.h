#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "square_matrix.h"
#include "errors.h"

// Складывает две матрицы
OpStatus addMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b);

// Умножает две матрицы
OpStatus multiplyMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b);

// Умножает матрицу на скаляр
OpStatus MatrixByScalar(SquareMatrix* res, const SquareMatrix* a, const void* scalar);

#endif