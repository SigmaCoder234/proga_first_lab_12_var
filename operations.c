#include "operations.h"
#include <stdlib.h>

// Складывает две матрицы
OpStatus addMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b) {
    if (!res || !a || !b || !a->data || !b->data || !res->data) {
        return OP_ERROR_NULL_POINTER;
    }

    if (a->size != b->size || res->size != a->size) {
        return OP_ERROR_SIZE_MISMATCH;
    }

    if (a->typeInfo != b->typeInfo || a->typeInfo != res->typeInfo) {
        return OP_ERROR_TYPE_MISMATCH;
    }

    for (int i = 0; i < a->size * a->size; i++) {
        void* ptrA = (char*)a->data + i * a->typeInfo->size;
        void* ptrB = (char*)b->data + i * b->typeInfo->size;
        void* ptrRes = (char*)res->data + i * res->typeInfo->size;
        a->typeInfo->add(ptrRes, ptrA, ptrB);
    }

    return OP_SUCCESS;
}

// Умножает две матрицы
OpStatus multiplyMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b) {
    if (!res || !a || !b || !a->data || !b->data || !res->data) {
        return OP_ERROR_NULL_POINTER;
    }

    if (a->size != b->size || res->size != a->size) {
        return OP_ERROR_SIZE_MISMATCH;
    }

    if (a->typeInfo != b->typeInfo || a->typeInfo != res->typeInfo) {
        return OP_ERROR_TYPE_MISMATCH;
    }

    void* temp = malloc(a->typeInfo->size);
    if (!temp) {
        return OP_ERROR_MEMORY;
    }

    for (int i = 0; i < a->size; i++) {
        for (int j = 0; j < a->size; j++) {
            void* ptrRes = getElement(res, i, j);
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

    return OP_SUCCESS;
}

// Умножает матрицу на скаляр
OpStatus MatrixByScalar(SquareMatrix* res, const SquareMatrix* a, const void* scalar) {
    if (!res || !a || !scalar || !a->data || !res->data) {
        return OP_ERROR_NULL_POINTER;
    }

    if (res->size != a->size) {
        return OP_ERROR_SIZE_MISMATCH;
    }

    if (a->typeInfo != res->typeInfo) {
        return OP_ERROR_TYPE_MISMATCH;
    }

    for (int i = 0; i < a->size * a->size; i++) {
        void* ptrA = (char*)a->data + i * a->typeInfo->size;
        void* ptrRes = (char*)res->data + i * res->typeInfo->size;
        a->typeInfo->mul(ptrRes, ptrA, scalar);
    }

    return OP_SUCCESS;
}