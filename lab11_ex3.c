#include <stdio.h>
#include <stdlib.h>

// Функція для очищення буфера введення
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функція для пошуку нульових елементів та їх номерів
void find_zeros(int *arr, int n) {
    int count = 0;
    int found = 0;

    printf("\n--- Аналіз масиву ---\n");
    printf("Порядкові номери нульових елементів: ");

    for (int i = 0; i < n; i++) {
        // Перевірка елемента на рівність нулю
        if (arr[i] == 0) {
            // Виводимо порядковий номер (індекс + 1)
            printf("%d ", i + 1);
            count++;
            found = 1;
        }
    }

    if (!found) {
        printf("нульові елементи відсутні.");
    }

    printf("\nЗагальна кількість нульових елементів: %d\n", count);
}

int main() {
    int *a = NULL;
    int n = 0;
    int choice;

    while (1) {
        printf("\n--- ГОЛОВНЕ МЕНЮ ---\n");
        printf("1. Створити масив та ввести дані\n");
        printf("2. Знайти нульові елементи (виконати функцію)\n");
        printf("3. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть число.\n");
            clear_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                // Звільнення пам'яті, якщо масив вже існував
                if (a != NULL) {
                    free(a);
                    a = NULL;
                }

                printf("Введіть розмір масиву: ");
                while (scanf("%d", &n) != 1 || n <= 0) {
                    printf("Некоректний розмір! Введіть додатне число: ");
                    clear_buffer();
                }

                // Динамічне виділення пам'яті
                a = (int*)malloc(n * sizeof(int));
                if (a == NULL) {
                    printf("Помилка виділення пам'яті!\n");
                    return 1;
                }

                printf("Введіть %d елементів масиву:\n", n);
                for (int i = 0; i < n; i++) {
                    printf("a[%d] = ", i);
                    while (scanf("%d", &a[i]) != 1) {
                        printf("Помилка! Введіть ціле число для a[%d]: ", i);
                        clear_buffer();
                    }
                }
                break;

            case 2:
                if (a == NULL) {
                    printf("Помилка: спочатку створіть масив.\n");
                } else {
                    // Виклик розробленої функції
                    find_zeros(a, n);
                }
                break;

            case 3:
                // Обов'язкове звільнення пам'яті перед виходом
                if (a != NULL) {
                    free(a);
                }
                printf("Програму завершено.\n");
                return 0;

            default:
                printf("Неправильний вибір.\n");
        }
    }
}