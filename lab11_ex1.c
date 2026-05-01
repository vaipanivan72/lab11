#include <stdio.h>
#include <stdlib.h>

// Функція для очищення буфера введення (захист від зациклення при помилках)
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    
    int *a = NULL;
    int n = 0, choice, i, count;

    while (1) {
        printf("\n--- МЕНЮ КЕРУВАННЯ ---\n");
        printf("1. Ввести новий масив (динамічно)\n");
        printf("2. Виконати завдання (підрахунок сусідств різних знаків)\n");
        printf("3. Вивести поточний масив\n");
        printf("4. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть номер пункту меню (число).\n");
            clear_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                // Видалення старого масиву, якщо він був створений раніше
                if (a != NULL) {
                    free(a);
                    a = NULL;
                }

                printf("Введіть кількість елементів n: ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    printf("Помилка: n має бути цілим додатним числом.\n");
                    clear_buffer();
                    break;
                }

                // Виділення динамічної пам'яті
                a = (int*)malloc(n * sizeof(int));
                if (a == NULL) {
                    printf("Критична помилка: не вдалося виділити пам'ять.\n");
                    return 1;
                }

                printf("Введіть %d цілих чисел:\n", n);
                for (i = 0; i < n; i++) {
                    printf("a[%d] = ", i);
                    while (scanf("%d", &a[i]) != 1) {
                        printf("Некоректні дані! Введіть ціле число для a[%d]: ", i);
                        clear_buffer();
                    }
                }
                printf("Масив успішно створено.\n");
                break;

            case 2:
                if (a == NULL || n < 2) {
                    printf("Помилка: спочатку створіть масив принаймні з 2 елементів.\n");
                } else {
                    count = 0;
                    // Алгоритм згідно варіанту 4
                    for (i = 0; i < n - 1; i++) {
                        if ((a[i] > 0 && a[i+1] < 0) || (a[i] < 0 && a[i+1] > 0)) {
                            count++;
                        }
                    }
                    printf("\nРезультат: знайдено %d сусідств з різними знаками.\n", count);
                }
                break;

            case 3:
                if (a == NULL) {
                    printf("Масив порожній.\n");
                } else {
                    printf("Поточний масив: ");
                    for (i = 0; i < n; i++) {
                        printf("%d ", a[i]);
                    }
                    printf("\n");
                }
                break;

            case 4:
                // Звільнення пам'яті перед виходом
                if (a != NULL) {
                    free(a);
                }
                printf("Програму завершено.\n");
                return 0;

            default:
                printf("Такого пункту не існує. Спробуйте ще раз.\n");
        }
    }
}