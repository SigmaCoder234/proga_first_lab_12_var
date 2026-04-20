#include "operations.h"
#include <stdlib.h>

// ========= сделать возврат инфы об ошибках если что-то пошло не так =========

// Складывает две матрицы
void addMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b) {
    if (!res || !a || !b || !a->data || !b->data || !res->data ||
        a->size != b->size || res->size != a->size || a->typeInfo != b->typeInfo || a->typeInfo != res->typeInfo) return;

    for (int i = 0; i < a->size * a->size; i++) {
        void* ptrA = (char*)a->data + i * a->typeInfo->size;
        void* ptrB = (char*)b->data + i * b->typeInfo->size;
        void* ptrRes = (char*)res->data + i * res->typeInfo->size;
        a->typeInfo->add(ptrRes, ptrA, ptrB);
    }
}

// Умножает две матрицы
void multiplyMatrices(SquareMatrix* res, const SquareMatrix* a, const SquareMatrix* b) {
    if (!res || !a || !b || !a->data || !b->data || !res->data ||
        a->size != b->size || res->size != a->size || a->typeInfo != b->typeInfo || a->typeInfo != res->typeInfo) return;

    void* temp = malloc(a->typeInfo->size);
    if (!temp) return;

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
}

// Умножает матрицу на скаляр
void MatrixByScalar(SquareMatrix* res, const SquareMatrix* a, const void* scalar) {
    if (!res || !a || !scalar || !a->data || !res->data || res->size != a->size || a->typeInfo != res->typeInfo) return;

    for (int i = 0; i < a->size * a->size; i++) {
        void* ptrA = (char*)a->data + i * a->typeInfo->size;
        void* ptrRes = (char*)res->data + i * res->typeInfo->size;
        a->typeInfo->mul(ptrRes, ptrA, scalar);
    }
}