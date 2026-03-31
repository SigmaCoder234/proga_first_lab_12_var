#include "square_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Инициализирует матрицу
SquareMatrix* initMatrix(int size, const TypeInfo* typeInfo) {
    if (size <= 0 || typeInfo == NULL) return NULL;
    SquareMatrix* matrix = (SquareMatrix*)malloc(sizeof(SquareMatrix));
    if (!matrix) return NULL;
    
    matrix->size = size;
    matrix->typeInfo = typeInfo;
    matrix->data = malloc(size * size * typeInfo->size);
    
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }
    
    for (int i = 0; i < size * size; i++) {
        void* ptr = (char*)matrix->data + i * typeInfo->size;
        typeInfo->zero(ptr);
    }
    
    return matrix;
}

// Освобождает память, выделенную под матрицу
void freeMatrix(SquareMatrix* matrix) {
    if (matrix) {
        if (matrix->data) free(matrix->data);
        free(matrix);
    }
}

// Задает значение элемента матрицы по заданным индексам
void setElement(SquareMatrix* matrix, int row, int col, const void* value) {
    if (!matrix || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size) return;
    void* ptr = (char*)matrix->data + (row * matrix->size + col) * matrix->typeInfo->size;
    memcpy(ptr, value, matrix->typeInfo->size);
}

// Возвращает указатель на элемент матрицы по заданным индексам
void* getElement(const SquareMatrix* matrix, int row, int col) {
    if (!matrix || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size) return NULL;
    return (char*)matrix->data + (row * matrix->size + col) * matrix->typeInfo->size;
}

// Выводит матрицу
void printMatrix(const SquareMatrix* matrix) {
    if (!matrix) return;
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            void* ptr = getElement(matrix, i, j);
            matrix->typeInfo->print(ptr);
        }
        printf("\n");
    }
}