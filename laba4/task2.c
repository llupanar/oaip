// Даны два целочисленных массива a1,…,an и b1,…,bn. 
//Вывести на печать все пары индексов, для которых a[i]* b[i] > 10.
//Подсчитать число пар и сумму этих произведений.

#include <stdio.h>
#include <locale.h>
#define SIZE 3

int main() {
	int a[SIZE], b[SIZE];
	int i, j, k = 0, f, sum=0;
	setlocale(LC_ALL, "Russian"); //русификация

	for (i = 0; i < SIZE; i++) {
		printf("введите элемент массива а\n");
		scanf_s("%d", &a[i]);
	}
	for (j = 0; j < SIZE; j++) {
		printf("введите элемент массива b\n");
		scanf_s("%d", &b[j]);
	}

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			f = a[i] * b[j];
			if (f > 10) {
				printf("а[%d] и b[%d]\n", i, j); //вывод необходимых индексов
				k++; // количество
				sum += f; //сумма произведений
			}
		}
	}
		printf("количество %d\nсумма %d\n", k, sum);
}
