#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct offPckgs {
    char title[20];    // Название 
    char producer[20]; // Производитель
    int count;         // Кол-во составных частей
    float price;       // Цена
};

void addParamByHand(offPckgs **fpckgs, int *size, int *capacity) {
    setlocale(LC_ALL, "rus");
    printf("Введите наименование: ");            scanf("%s", &(*fpckgs)[*size].title);
    printf("Введите производителя: ");           scanf("%s", &(*fpckgs)[*size].producer);
    printf("Введите кол-во составных частей: "); scanf("%d", &(*fpckgs)[*size].count);
    printf("Введите цену: ");                    scanf("%lf", &(*fpckgs)[*size].price);
    
    (*size)++;

    if (*size >= *capacity) {
        *capacity *= 2;
        *fpckgs = (offPckgs *)realloc(*fpckgs, *capacity * sizeof(offPckgs));
    }
}

void addParamByRandom(offPckgs** fpckgs, int* size, int* capacity) {
    setlocale(LC_ALL, "rus");
    printf("Введите размер таблицы(1-20): ");            scanf("%s", &(*fpckgs)[*size].title);
    printf("Введите производителя: ");           scanf("%s", &(*fpckgs)[*size].producer);
    printf("Введите кол-во составных частей: "); scanf("%d", &(*fpckgs)[*size].count);
    printf("Введите цену: ");                    scanf("%lf", &(*fpckgs)[*size].price);

    (*size)++;

    if (*size >= *capacity) {
        *capacity *= 2;
        *fpckgs = (offPckgs*)realloc(*fpckgs, *capacity * sizeof(offPckgs));
    }
}

void printTable(offPckgs *fpckgs, int size) {
    setlocale(LC_ALL, "rus");
    printf("|-------------------------------------------------------------|\n");
    printf("|                        Офисные пакеты                       |\n");
    printf("|-------------------------------------------------------------|\n");
    printf("| Наименование | Производитель | Кол-во сост.частей | Цена($) |\n");
    printf("|--------------|---------------|--------------------|---------|\n");
    if (size == 0)
    printf("|                    Пока тут ничего нет...                   |\n");

    for (int i = 0; i < size; i++)
        printf("|%-13s | %-13s | %-18d | %-7lf |\n", fpckgs[i].title, fpckgs[i].producer, fpckgs[i].count, fpckgs[i].price);

    printf("|-------------------------------------------------------------|\n");
}

void print_highest(offPckgs *goods, int size) {
    double max = goods[0].price;
    int imax = 0;

    for (int i = 1; i < size; i++) {
        if (goods[i].count > max) {
            max = goods[i].price;
            imax = i;
        }
    }

    printf("The highest price of goods is %.2lf (good is %s)\n", max, goods[imax].title);
}

void print_lowest(offPckgs *goods, int size) {
    double min = goods[0].price;
    int imin = 0;

    for (int i = 1; i < size; i++) {
        if (goods[i].count < min) {
            min = goods[i].price;
            imin = i;
        }
    }

    printf("The lowest price of goods is %.2lf (good is %s)\n", min, goods[imin].title);
}

void printMenu() {
    system("cls");  // очищаем экран
    setlocale(LC_ALL, "rus");
    printf("Что нужно сделать?\n");
    printf("1. Добавить данные в таблицу в ручную\n");
    printf("2. Добавить случайные данные в таблицу\n");
    printf("3. Напечатать таблицу\n");
    printf("4. Print the highest price\n");
    printf("5. Print the lowest price\n");
    printf("6. Выход из программы\n");
    printf(">");
}

int getPoint(int count) {
    setlocale(LC_ALL, "rus");
    int variant;
    char s[100]; // строка для считывания введённых данных
    scanf("%s", s); // считываем строку

    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (sscanf(s, "%d", &variant) != 1 || variant < 1 || variant > count) {
        printf("Что-то пошло не так...\nПопробуйте снова: "); 
        scanf("%s", s); // считываем строку повторно
    }

    return variant;
}

int main() {
    setlocale(LC_ALL, "rus");
    int point;        // выбранный пункт меню
    int size = 0;     // количество элементов массива 
    int capacity = 1; // Место которое занимает массив

    offPckgs *goods = (offPckgs *)malloc(capacity * sizeof(offPckgs)); // выделяем память под массив 

    do {
        printMenu(); // выводим меню на экран

        point = getPoint(6); // получаем номер выбранного пункта меню

        switch (point) {
            case 1:
                addParamByHand(&goods, &size, &capacity);
                break;

            case 2:
                addParamByRandom(&goods, &size, &capacity);
                break;

            case 3:
                printTable(goods, size);
                break;

            case 4:
                print_highest(goods, size);
                break;

            case 5:
                print_lowest(goods, size);
                break;
        }
        if (point != 6)
            system("pause"); 
    } 
    while (point != 6);
    return 0;
}