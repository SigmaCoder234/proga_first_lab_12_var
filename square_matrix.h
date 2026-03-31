#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "type_info.h"

typedef struct {
    void* data;
    int size;
    const TypeInfo* typeInfo;
} SquareMatrix;

// Инициализирует матрицу
SquareMatrix* initMatrix(int size, const TypeInfo* typeInfo);

// Освобождает память, выделенную под матрицу
void freeMatrix(SquareMatrix* matrix);

// Задает значение элемента матрицы по заданным индексам
void setElement(SquareMatrix* matrix, int row, int col, const void* value);

// Возвращает указатель на элемент матрицы по заданным индексам
void* getElement(const SquareMatrix* matrix, int row, int col);

// Выводит матрицу
void printMatrix(const SquareMatrix* matrix);

#endif