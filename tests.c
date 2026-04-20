#include "square_matrix.h"
#include "operations.h"
#include "type_info_double.h"
#include "type_info_complex.h"
#include <assert.h>
#include <stdio.h>

// тесты на возвращение ошибок и обработку колец

// Тестирует инициализацию матрицы и установку/получение элементов для double
static void test_init_matrix_double() {
    printf("test_init_matrix_double... ");
    SquareMatrix m = {0};
    initMatrix(&m, 2, getDoubleTypeInfo());
    assert(m.data != NULL);
    assert(m.size == 2);
    assert(m.typeInfo == getDoubleTypeInfo());
    
    // Проверка нулевого значения по умолчанию
    double val_default = *(double*)getElement(&m, 0, 0);
    assert(val_default == 0.0);
    
    // Установка и получение значения
    double set_val = 42.5;
    setElement(&m, 1, 1, &set_val);
    double get_val = *(double*)getElement(&m, 1, 1);
    assert(get_val == 42.5);
    
    freeMatrix(&m);
    printf("OK\n");
}

// Тестирует инициализацию матрицы и установку/получение элементов для complex
static void test_init_matrix_complex() {
    printf("test_init_matrix_complex... ");
    SquareMatrix m = {0};
    initMatrix(&m, 2, getComplexTypeInfo());
    assert(m.data != NULL);
    assert(m.size == 2);
    assert(m.typeInfo == getComplexTypeInfo());
    
    // Проверка нулевого значения по умолчанию
    Complex val_default = *(Complex*)getElement(&m, 0, 0);
    assert(val_default.re == 0.0 && val_default.im == 0.0);
    
    // Установка и получение значения
    Complex set_val = {1.0, 2.0};
    setElement(&m, 1, 1, &set_val);
    Complex get_val = *(Complex*)getElement(&m, 1, 1);
    assert(get_val.re == 1.0 && get_val.im == 2.0);
    
    freeMatrix(&m);
    printf("OK\n");
}

// Тестирует сложение матриц типа double
static void test_add_matrix_double() {
    printf("test_add_matrix_double... ");
    SquareMatrix m1 = {0}, m2 = {0}, res = {0};
    initMatrix(&m1, 2, getDoubleTypeInfo());
    initMatrix(&m2, 2, getDoubleTypeInfo());
    initMatrix(&res, 2, getDoubleTypeInfo());
    
    double v1 = 5.0, v2 = 7.0;
    setElement(&m1, 0, 0, &v1);
    setElement(&m2, 0, 0, &v2);
    
    addMatrices(&res, &m1, &m2);
    assert(*(double*)getElement(&res, 0, 0) == 12.0);
    
    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&res);
    printf("OK\n");
}

// Тестирует сложение матриц типа complex
static void test_add_matrix_complex() {
    printf("test_add_matrix_complex... ");
    SquareMatrix m1 = {0}, m2 = {0}, res = {0};
    initMatrix(&m1, 1, getComplexTypeInfo());
    initMatrix(&m2, 1, getComplexTypeInfo());
    initMatrix(&res, 1, getComplexTypeInfo());
    
    Complex c1 = {1.0, 2.0};
    Complex c2 = {3.0, 4.0};
    setElement(&m1, 0, 0, &c1);
    setElement(&m2, 0, 0, &c2);
    
    addMatrices(&res, &m1, &m2);
    Complex* res_c = (Complex*)getElement(&res, 0, 0);
    assert(res_c->re == 4.0 && res_c->im == 6.0);

    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&res);
    printf("OK\n");
}

// Тестирует умножение матриц типа double
static void test_multiply_matrix_double() {
    printf("test_multiply_matrix_double... ");
    SquareMatrix m1 = {0}, m2 = {0}, res = {0};
    initMatrix(&m1, 2, getDoubleTypeInfo());
    initMatrix(&m2, 2, getDoubleTypeInfo());
    initMatrix(&res, 2, getDoubleTypeInfo());
    
    double v;
    v = 1.0; setElement(&m1, 0, 0, &v); v = 2.0; setElement(&m1, 0, 1, &v);
    v = 3.0; setElement(&m1, 1, 0, &v); v = 4.0; setElement(&m1, 1, 1, &v);
    
    v = 2.0; setElement(&m2, 0, 0, &v); v = 0.0; setElement(&m2, 0, 1, &v);
    v = 1.0; setElement(&m2, 1, 0, &v); v = 2.0; setElement(&m2, 1, 1, &v);
    
    multiplyMatrices(&res, &m1, &m2);

    assert(*(double*)getElement(&res, 0, 0) == 4.0);
    assert(*(double*)getElement(&res, 0, 1) == 4.0);
    assert(*(double*)getElement(&res, 1, 0) == 10.0);
    assert(*(double*)getElement(&res, 1, 1) == 8.0);
    
    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&res);
    printf("OK\n");
}

// Тестирует умножение матриц типа complex
static void test_multiply_matrix_complex() {
    printf("test_multiply_matrix_complex... ");
    SquareMatrix m1 = {0}, m2 = {0}, res = {0};
    initMatrix(&m1, 2, getComplexTypeInfo());
    initMatrix(&m2, 2, getComplexTypeInfo());
    initMatrix(&res, 2, getComplexTypeInfo());

    Complex i_val = {0.0, 1.0};
    Complex zero_val = {0.0, 0.0};
    Complex minus_one_val = {-1.0, 0.0};

    setElement(&m1, 0, 0, &i_val);
    setElement(&m1, 0, 1, &zero_val);
    setElement(&m1, 1, 0, &zero_val);
    setElement(&m1, 1, 1, &i_val);

    setElement(&m2, 0, 0, &i_val);
    setElement(&m2, 0, 1, &zero_val);
    setElement(&m2, 1, 0, &zero_val);
    setElement(&m2, 1, 1, &i_val);

    multiplyMatrices(&res, &m1, &m2);

    Complex* res_00 = (Complex*)getElement(&res, 0, 0);
    Complex* res_01 = (Complex*)getElement(&res, 0, 1);
    Complex* res_10 = (Complex*)getElement(&res, 1, 0);
    Complex* res_11 = (Complex*)getElement(&res, 1, 1);

    assert(res_00->re == minus_one_val.re && res_00->im == minus_one_val.im);
    assert(res_01->re == zero_val.re && res_01->im == zero_val.im);
    assert(res_10->re == zero_val.re && res_10->im == zero_val.im);
    assert(res_11->re == minus_one_val.re && res_11->im == minus_one_val.im);

    freeMatrix(&m1);
    freeMatrix(&m2);
    freeMatrix(&res);
    printf("OK\n");
}

// Тестирует умножение матрицы типа double на скаляр
static void test_scalar_multiply_double() {
    printf("test_scalar_multiply_double... ");
    SquareMatrix m = {0}, res = {0};
    initMatrix(&m, 1, getDoubleTypeInfo());
    initMatrix(&res, 1, getDoubleTypeInfo());
    
    double val = 5.0;
    setElement(&m, 0, 0, &val);
    
    double scalar = 2.0;
    
    MatrixByScalar(&res, &m, &scalar);
    
    double* res_d = (double*)getElement(&res, 0, 0);
    assert(*res_d == 10.0);
    
    freeMatrix(&m);
    freeMatrix(&res);
    printf("OK\n");
}

// Тестирует умножение матрицы типа complex на скаляр
static void test_scalar_multiply_complex() {
    printf("test_scalar_multiply_complex... ");
    SquareMatrix m = {0}, res = {0};
    initMatrix(&m, 1, getComplexTypeInfo());
    initMatrix(&res, 1, getComplexTypeInfo());
    
    Complex c1 = {1.0, 2.0};
    setElement(&m, 0, 0, &c1);
    
    Complex scalar = {2.0, -1.0};
    
    MatrixByScalar(&res, &m, &scalar);
    
    Complex* res_c = (Complex*)getElement(&res, 0, 0);
    assert(res_c->re == 4.0);
    assert(res_c->im == 3.0);
    
    freeMatrix(&m);
    freeMatrix(&res);
    printf("OK\n");
}


// Тестирует обработку ошибок
static void test_error_handling() {
    printf("test_error_handling... ");
    SquareMatrix m = {0}, res = {0};
    initMatrix(&m, 2, getDoubleTypeInfo());
    initMatrix(&res, 2, getDoubleTypeInfo());

    addMatrices(&res, &m, NULL); // Сложение с NULL
    multiplyMatrices(&res, NULL, &m); // Умножение с NULL
    MatrixByScalar(&res, NULL, NULL); // Умножение на скаляр с NULL
    
    // Тест на несовместимые размеры
    SquareMatrix m_diff_size = {0};
    initMatrix(&m_diff_size, 3, getDoubleTypeInfo());
    addMatrices(&res, &m, &m_diff_size);
    multiplyMatrices(&res, &m, &m_diff_size);
    freeMatrix(&m_diff_size);

    // Тест на несовместимые типы
    SquareMatrix m_diff_type = {0};
    initMatrix(&m_diff_type, 2, getComplexTypeInfo());
    addMatrices(&res, &m, &m_diff_type);
    multiplyMatrices(&res, &m, &m_diff_type);
    freeMatrix(&m_diff_type);

    freeMatrix(&m);
    freeMatrix(&res);
    printf("OK\n");
}

// Запускает все тесты
int run_all_tests() {
    printf("\n========= Running tests =========\n\n");
    test_init_matrix_double();
    test_init_matrix_complex();
    test_add_matrix_double();
    test_add_matrix_complex();
    test_multiply_matrix_double();
    test_multiply_matrix_complex();
    test_scalar_multiply_double();
    test_scalar_multiply_complex();
    test_error_handling();
    printf("\n====== All tests passed! ======\n\n");
    return 0;
}