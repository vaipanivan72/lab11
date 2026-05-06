#include <stdio.h>
#include <stdlib.h>

// --- ПРОТОТИПИ ФУНКЦІЙ ---
void clear_buffer();
int* create_array(int *n);
void process_array(int *a, int n);
void print_array(int *a, int n);
void free_memory(int **a);

int main() {
    int *a = NULL;
    int n = 0;
    int choice;

    while (1) {
        printf("\n--- МЕНЮ КЕРУВАННЯ ---\n");
        printf("1. Ввести новий масив\n");
        printf("2. Виконати завдання (підрахунок різних знаків)\n");
        printf("3. Вивести поточний масив\n");
        printf("4. Вихід\n");
        printf("Ваш вибір: ");

        if (scanf("%d", &choice) != 1) {
            printf("Помилка: введіть число.\n");
            clear_buffer();
            continue;
        }

        switch (choice) {
            case 1:
                free_memory(&a); // Очищуємо стару пам'ять перед створенням нової
                a = create_array(&n);
                break;

            case 2:
                process_array(a, n);
                break;

            case 3:
                print_array(a, n);
                break;

            case 4:
                free_memory(&a);
                printf("Програму завершено.\n");
                return 0;

            default:
                printf("Такого пункту не існує.\n");
        }
    }
}

// --- РЕАЛІЗАЦІЯ ФУНКЦІЙ ---

// Очищення буфера після неправильного введення
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функція для створення масиву та введення даних
int* create_array(int *n) {
    printf("Введіть кількість елементів n: ");
    while (scanf("%d", n) != 1 || *n <= 0) {
        printf("Помилка: введіть ціле додатне число: ");
        clear_buffer();
    }

    int *arr = (int*)malloc((*n) * sizeof(int));
    if (arr == NULL) {
        printf("Критична помилка пам'яті!\n");
        exit(1);
    }

    printf("Введіть %d цілих чисел:\n", *n);
    for (int i = 0; i < *n; i++) {
        printf("a[%d] = ", i);
        while (scanf("%d", &arr[i]) != 1) {
            printf("Некоректні дані! Введіть ціле число: ");
            clear_buffer();
        }
    }
    printf("Масив успішно створено.\n");
    return arr;
}

// Функція для виконання основного завдання (алгоритм)
void process_array(int *a, int n) {
    if (a == NULL || n < 2) {
        printf("Помилка: масив занадто малий або не створений.\n");
        return;
    }

    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        // Перевірка на різні знаки (добуток менше 0)
        // Обробляємо випадок, коли 0 не вважається ні додатним, ні від'ємним
        if ((a[i] > 0 && a[i+1] < 0) || (a[i] < 0 && a[i+1] > 0)) {
            count++;
        }
    }
    printf("\nРезультат: знайдено %d сусідств з різними знаками.\n", count);
}

// Функція для виведення масиву
void print_array(int *a, int n) {
    if (a == NULL) {
        printf("Масив порожній.\n");
        return;
    }
    printf("Поточний масив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Функція для безпечного звільнення пам'яті
void free_memory(int **a) {
    if (*a != NULL) {
        free(*a);
        *a = NULL;
    }
}
