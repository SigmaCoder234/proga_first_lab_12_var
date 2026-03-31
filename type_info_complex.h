#ifndef TYPE_INFO_COMPLEX_H
#define TYPE_INFO_COMPLEX_H

#include "type_info.h"

// Структура для представления комплексного числа
typedef struct {
    double re;
    double im;
} Complex;

// Возвращает информацию о типе Complex
const TypeInfo* getComplexTypeInfo();

#endif