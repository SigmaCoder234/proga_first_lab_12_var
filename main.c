#include <stdio.h>
#include <stdlib.h>
#include "type_info_double.h"
#include "type_info_complex.h"
#include "square_matrix.h"
#include "operations.h"

int run_all_tests();

// Если is_double = 0, читаем int по адресу value_ptr.
// Если is_double = 1, читаем double по адресу value_ptr.
static void safe_input(void* value_ptr, int is_double) {
    int res;
    while (1) {
        if (is_double) {
            res = scanf("%lf", (double*)value_ptr);
        }

        else {
            res = scanf("%d", (int*)value_ptr);
        }

        // Очищаем буфер до конца строки в любом случае
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1) {
            break; // Ввод корректен, выходим из цикла
        }

        else {
            printf("Invalid input. Please try again: ");
        }
    }
}

// Выбор типа элементов матрицы
static const TypeInfo* chooseType() {
    int choice;
    printf("\nChoose element type:\n");
    printf("1 - double (real numbers)\n");
    printf("2 - complex (complex numbers)\n");

    while (1) {
        printf("Your choice (1 or 2): ");
        safe_input(&choice, 0);
        if (choice == 1) return getDoubleTypeInfo();
        if (choice == 2) return getComplexTypeInfo();
        printf("Error: input must be 1 or 2.\n");
    }
}

// Заполняет матрицу значениями
static void fill_matrix(SquareMatrix* m, const char* name) {
    if (!m) return;
    printf("\nFilling matrix %s\n", name);

    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            if (m->typeInfo == getDoubleTypeInfo()) {
                double val;
                printf("%s[%d][%d] = ", name, i, j);
                safe_input(&val, 1);
                setElement(m, i, j, &val);
            }

            else { // Complex
                Complex val;
                printf("%s[%d][%d] Re = ", name, i, j);
                safe_input(&val.re, 1);
                printf("%s[%d][%d] Im = ", name, i, j);
                safe_input(&val.im, 1);
                setElement(m, i, j, &val);
                }
            }
        }
    printf("Matrix %s has been filled!\n", name);
}

// Ввод скаляра
static void input_scalar(const TypeInfo* ti, void* scalar) {
    if (ti == getDoubleTypeInfo()) {
        printf("Enter a real number: ");
        safe_input(scalar, 1);
    }

    else { // Complex
        Complex* c = (Complex*)scalar;
        printf("Enter the real part: ");
        safe_input(&c->re, 1);
        printf("Enter the imaginary part: ");
        safe_input(&c->im, 1);
    }
}

void printMenu() {
    printf("\n======================= Menu =========================\n");
    printf("| 1 - Initialize matrix A                              |\n");
    printf("| 2 - Initialize matrix B                              |\n");
    printf("| 3 - Fill matrix A                                    |\n");
    printf("| 4 - Fill matrix B                                    |\n");
    printf("| 5 - Show matrices A and B                            |\n");
    printf("| 6 - Add matrices (C = A + B)                         |\n");
    printf("| 7 - Multiply matrices (C = A * B)                    |\n");
    printf("| 8 - Multiply a matrix by a scalar                    |\n");
    printf("| 9 - Run tests                                        |\n");
    printf("| 0 - Exit                                             |\n");
    printf("========================================================\n");
    printf("Your choice: ");
}

int main() {
    SquareMatrix* A = NULL;
    SquareMatrix* B = NULL;

    int choice = -1;
    while (choice != 0) {
        printMenu();
        safe_input(&choice, 0);

        switch (choice) {
            case 1: {
                if (A) {
                    freeMatrix(A); A = NULL;
                }

                printf("\n--- Matrix A Initialization ---\n");
                const TypeInfo* ti = chooseType();
                int size;
                while (1) {
                    printf("Enter matrix dimension (N > 0): ");
                    safe_input(&size, 0);
                    if (size > 0) break;
                    printf("Dimension must be greater than zero!\n");
                }

                A = initMatrix(size, ti);

                if (A) {
                    printf("\nMatrix A (%dx%d) created successfully!\n", size, size);
                }

                else {
                    printf("\nMemory allocation error for Matrix A!\n");
                }
                break;
            }

            case 2: {
                if (B) {
                    freeMatrix(B); B = NULL;
                }
                
                printf("\n--- Matrix B Initialization ---\n");
                const TypeInfo* ti = chooseType();
                int size;
                while (1) {
                    printf("Enter matrix dimension (N > 0): ");
                    safe_input(&size, 0);
                    if (size > 0) break;
                    printf("Dimension must be greater than zero!\n");
                }

                B = initMatrix(size, ti);
                
                if (B) {
                    printf("\nMatrix B (%dx%d) created successfully!\n", size, size);
                }

                else {
                    printf("\nMemory allocation error for Matrix B!\n");
                }

                break;
            }
            
            case 3:
                if (!A) {
                    printf("\nInitialize matrix A first (option 1)!\n");
                }

                else {
                    fill_matrix(A, "A");
                }

                break;
                
            case 4:
                if (!B) {
                    printf("\nInitialize matrix B first (option 2)!\n");
                }

                else {
                    fill_matrix(B, "B");
                }

                break;
                
            case 5:
                if (!A && !B) {
                    printf("\nInitialize matrices first (options 1 or 2)!\n");
                    break;
                }

                if (A) {
                    printf("\nMatrix A:\n");
                    printMatrix(A);
                }

                else {
                    printf("\nMatrix A is not initialized.\n");
                }

                if (B) {
                    printf("\nMatrix B:\n");
                    printMatrix(B);
                }

                else {
                    printf("\nMatrix B is not initialized.\n");
                }

                break;
                
            case 6: {
                if (!A || !B) {
                    printf("\nInitialize both matrices first (options 1 and 2)!\n");
                    break;
                }

                SquareMatrix* C = addMatrices(A, B);
                if (C) {
                    printf("\nAddition result (A + B):\n");
                    printMatrix(C);
                    freeMatrix(C);
                }

                else {
                    printf("\nError during matrix addition! (Check sizes and types)\n");
                }

                break;
            }
            
            case 7: {
                if (!A || !B) {
                    printf("\nInitialize both matrices first (options 1 and 2)!\n");
                    break;
                }

                SquareMatrix* C = multiplyMatrices(A, B);
                if (C) {
                    printf("\nMultiplication result (A * B):\n");
                    printMatrix(C);
                    freeMatrix(C);
                }

                else {
                    printf("\nError during matrix multiplication! (Check sizes and types)\n");
                }

                break;
            }
            
            case 8: {
                if (!A && !B) {
                    printf("\nInitialize at least one matrix first (options 1 or 2)!\n");
                    break;
                }

                SquareMatrix* targetMatrix = NULL;
                if (A && B) {
                    int matrixChoice;
                    while(1) {
                        printf("\nChoose matrix to multiply by scalar (1 for A, 2 for B): ");
                        safe_input(&matrixChoice, 0);
                        if (matrixChoice == 1) {
                            targetMatrix = A;
                            break;
                        }

                        else if (matrixChoice == 2) {
                            targetMatrix = B;
                            break;
                        }
                        printf("Error: input must be 1 or 2.\n");
                    }
                }

                else if (A) {
                    targetMatrix = A;
                }

                else {
                    targetMatrix = B;
                }

                void* scalar = malloc(targetMatrix->typeInfo->size);
                if (!scalar) {
                    printf("\nMemory allocation error!\n");
                    break;
                }
                
                input_scalar(targetMatrix->typeInfo, scalar);
                
                SquareMatrix* C = MatrixByScalar(targetMatrix, scalar);
                if (C) {
                    printf("\nScalar multiplication result:\n");
                    printMatrix(C);
                    freeMatrix(C);
                }

                else {
                    printf("\nError during multiplication!\n");
                }

                free(scalar);
                break;
            }
            
            case 9:
                run_all_tests();
                break;

            case 0:
                break;
                
            default:
                printf("\nInvalid menu option. Please try again.\n");
                break;
        }
    }

    if (A) freeMatrix(A);
    if (B) freeMatrix(B);
    
    return 0;
}