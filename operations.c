#include "operations.h"
#include <stdlib.h>

// Складывает две матрицы
SquareMatrix* addMatrices(const SquareMatrix* a, const SquareMatrix* b) {
    if (!a || !b || a->size != b->size || a->typeInfo != b->typeInfo) return NULL;
    SquareMatrix* result = initMatrix(a->size, a->typeInfo);
    if (!result) return NULL;

    for (int i = 0; i < a->size * a->size; i++) {
        void* ptrA = (char*)a->data + i * a->typeInfo->size;
        void* ptrB = (char*)b->data + i * b->typeInfo->size;
        void* ptrRes = (char*)result->data + i * result->typeInfo->size;
        a->typeInfo->add(ptrRes, ptrA, ptrB);
    }
    return result;
}

// Умножает две матрицы
SquareMatrix* multiplyMatrices(const SquareMatrix* a, const SquareMatrix* b) {
    if (!a || !b || a->size != b->size || a->typeInfo != b->typeInfo) return NULL;
    SquareMatrix* result = initMatrix(a->size, a->typeInfo);
    if (!result) return NULL;

    void* temp = malloc(a->typeInfo->size);
    if (!temp) { freeMatrix(result); return NULL; }

    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < a->size; j++) {
            void* ptrRes = getElement(result, i, j);
            a->typeInfo->zero(ptrRes);
            for (int k = 0; k < a->size; k++) {
                void* ptrA = getElement(a, i, k);
                void* ptrB = getElement(b, k, j);
                a->typeInfo->mul(temp, ptrA, ptrB);
                a->typeInfo->add(ptrRes, ptrRes, temp);
            }
        }
    }
    free(temp);
    return result;
}

// Умножает матрицу на скаляр
SquareMatrix* MatrixByScalar(const SquareMatrix* a, const void* scalar) {
    if (!a || !scalar) return NULL;
    SquareMatrix* result = initMatrix(a->size, a->typeInfo);
    if (!result) return NULL;

    for (int i = 0; i < a->size * a->size; i++) {
        void* ptrA = (char*)a->data + i * a->typeInfo->size;
        void* ptrRes = (char*)result->data + i * result->typeInfo->size;
        a->typeInfo->mul(ptrRes, ptrA, scalar);
    }
    return result;
}