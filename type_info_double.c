#include "type_info_double.h"
#include <stdio.h>

// Выводит значение
static void printDouble(const void* a) { printf("%7.2f ", *(const double*)a); }

// Складывает два значения
static void addDouble(void* res, const void* a, const void* b) { *(double*)res = *(const double*)a + *(const double*)b; }

// Умножает два значения
static void mulDouble(void* res, const void* a, const void* b) { *(double*)res = *(const double*)a * *(const double*)b; }

// Устанавливает значение в ноль
static void zeroDouble(void* res) { *(double*)res = 0.0; }

static const TypeInfo doubleTypeInfo = { sizeof(double), printDouble, addDouble, mulDouble, zeroDouble };

// Возвращает информацию о типе double
const TypeInfo* getDoubleTypeInfo() { return &doubleTypeInfo; }