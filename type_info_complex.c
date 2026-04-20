#include "type_info_complex.h"
#include <stdio.h>
#include <stdlib.h>

// Выводит значение элемента
static void printComplex(const void* a) {
    const Complex* c = (const Complex*)a;
    if (c->im >= 0) {
        printf("%5.2f+%5.2fi ", c->re, c->im);
    }

    else {
        printf("%5.2f%5.2fi ", c->re, c->im);
    }
}

// Складывает два комплексных числа
static void addComplex(void* res, const void* a, const void* b) {
    Complex* r = (Complex*)res;
    const Complex* ca = (const Complex*)a;
    const Complex* cb = (const Complex*)b;
    r->re = ca->re + cb->re;
    r->im = ca->im + cb->im;
}

// Умножает два комплексных числа
static void mulComplex(void* res, const void* a, const void* b) {
    Complex* r = (Complex*)res;
    const Complex* ca = (const Complex*)a;
    const Complex* cb = (const Complex*)b;
    double temp_re = ca->re * cb->re - ca->im * cb->im;
    double temp_im = ca->re * cb->im + ca->im * cb->re;
    r->re = temp_re;
    r->im = temp_im;
}

// Устанавливает значение комплексного числа в ноль
static void zeroComplex(void* res) {
    Complex* r = (Complex*)res;
    r->re = 0.0;
    r->im = 0.0;
}

static TypeInfo* complexTypeInfo = NULL;

// Возвращает информацию о типе
const TypeInfo* getComplexTypeInfo() {
    if (complexTypeInfo == NULL) {
        complexTypeInfo = (TypeInfo*)malloc(sizeof(TypeInfo));
        if (complexTypeInfo) {
            complexTypeInfo->size = sizeof(Complex);
            complexTypeInfo->print = printComplex;
            complexTypeInfo->add = addComplex;
            complexTypeInfo->mul = mulComplex;
            complexTypeInfo->zero = zeroComplex;
        }
    }
    return complexTypeInfo;
}