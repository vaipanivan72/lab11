#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Очищення буфера для захисту від некоректного введення
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функція для звільнення пам'яті матриці
void free_matrix(int **a, int n) {
    if (a != NULL) {
        for (int i = 0; i < n; i++) {
            free(a[i]);
        }
        free(a);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int **a = NULL;
    int n = 0, m = 0;
    int choice;

    while (1) {
        printf("--- ГОЛОВНЕ МЕНЮ ---\n");
        printf("1. Створити та заповнити матрицю випадковими числами\n");
        printf("2. Знайти суму найбільших елементів рядків\n");
        printf("3. Вивести поточну матрицю на екран\n");
        printf("4. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть число від 1 до 4.\n");
            clear_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                // Якщо матриця вже існувала, видаляємо її перед створенням нової
                free_matrix(a, n);
                a = NULL;

                printf("Введіть кількість рядків (n): ");
                while (scanf("%d", &n) != 1 || n <= 0) {
                    printf("Некоректне n! Введіть додатне ціле число: ");
                    clear_buffer();
                }
                printf("Введіть кількість стовпців (m): ");
                while (scanf("%d", &m) != 1 || m <= 0) {
                    printf("Некоректне m! Введіть додатне ціле число: ");
                    clear_buffer();
                }

                // Динамічне виділення пам'яті під масив покажчиків
                a = (int**)malloc(n * sizeof(int*));
                if (a == NULL) { return 1; }

                for (int i = 0; i < n; i++) {
                    // Виділення пам'яті під кожен рядок[cite: 1]
                    a[i] = (int*)malloc(m * sizeof(int));
                    for (int j = 0; j < m; j++) {
                        // Генерація чисел у діапазоні [-100; 100]
                        a[i][j] = rand() % 201 - 100;
                    }
                }
                printf("Матрицю %dx%d успішно згенеровано.\n", n, m);
                break;

            case 2:
                if (a == NULL) {
                    printf("Помилка: спочатку створіть матрицю (пункт 1).\n");
                } else {
                    int total_sum = 0;
                    printf("\nПроміжні результати (максимуми рядків):\n");
                    for (int i = 0; i < n; i++) {
                        int max_val = a[i][0];
                        for (int j = 1; j < m; j++) {
                            if (a[i][j] > max_val) max_val = a[i][j];
                        }
                        printf("Рядок %d: %d\n", i + 1, max_val);
                        total_sum += max_val;
                    }
                    printf("Кінцевий результат (загальна сума): %d\n", total_sum);
                }
                break;

            case 3:
                if (a == NULL) {
                    printf("Матриця порожня.\n");
                } else {
                    printf("\nПоточна матриця:\n");
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {
                            printf("%5d ", a[i][j]);
                        }
                        printf("\n");
                    }
                }
                break;

            case 4:
                free_matrix(a, n); // Звільнення пам'яті перед виходом[cite: 1]
                printf("Програму завершено.\n");
                return 0;

            default:
                printf("Такого пункту не існує.\n");
        }
    }
}