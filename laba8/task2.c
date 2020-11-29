#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <windows.h>

void sort_alf(char** t, int n, int k);
void sort_zp(char** t, int n, int k);
void prntf(char** t, int n);

int main() {
	setlocale(LC_ALL, "Russian");

	char** text;
	int i, n, k;
	int rass = 0;
	do {
		system("CLS");
		printf("Введите количество paботников\n");
		rewind(stdin);
		scanf_s("%d", &n);
		system("CLS");
		printf("Введите длину строк\n");
		rewind(stdin);
		scanf_s("%d", &k);
	} while (!n || n < 2 || !k || k < 2);
	system("CLS");

	text = (char**)malloc(n * sizeof(char*)); // выделение памяти под указатели на указатели
	if (!text) {
		printf("Недостаточно памяти");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		text[i] = (char*)malloc(k * sizeof(char)); //выделение памяти под строки
		if (!text[i]) {
			printf("Недостаточно памяти");
			return 0;
		}
	}
	//Ввод		
	for (i = 0; i < n; i++)
	{
		rewind(stdin);
		printf("введите информацию о %d сотруднике\n", i + 1);
		fgets(text[i], k, stdin);
	}
	system("CLS");
	prntf(text, n);
	printf("Рассортировать по алфавиту 1 \n Рассортировать по з/п 2\n Оба варианта 3\n");
	do {
		scanf_s("%d", &rass);
	} while (!rass || rass > 4 || rass < 0);
	switch (rass) {
	case 1: system("CLS");  sort_alf(text, n, k); break;
	case 2:	system("CLS");  sort_zp(text, n, k); break;
	case 3: 	system("CLS"); sort_alf(text, n, k); sort_zp(text, n, k); break;
	}
	for (i = 0; i < n; i++) {
		free(text[i]);
	}
	free(text); //освобождение памяти

	return 0;
}

void prntf(char** t, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; t[i][j] != '\0'; j++) {
			printf("%c", t[i][j]);
		}
	}
}

void sort_alf(char** t, int n, int k){
	char* add;
	int i, j, y;
	add = (char*)malloc(k * sizeof(char));

	for (i = 0; i < n; i++) { //сортировка пузырьком
		y = 0;
		for (j = n - 1; j > i; j--) {
			if (t[j - 1][y] > t[j][y]) {
				add = t[j - 1];
				t[j - 1] = t[j];
				t[j] = add;
			}
			if (t[j - 1][y] == t[j][y]) //При совпадении первых букв будут сравниваться следующие
			{
				for (y; t[j][y] != EOF && t[j - 1][y] != EOF; y++) {
					if (t[j - 1][y] > t[j][y]) {
						add = t[j - 1];
						t[j - 1] = t[j];
						t[j] = add;
						break;
					}
				}
			}
		}
	}
	printf("Сотрудники по алфавиту\n");
	prntf(t, n);

}

void sort_zp(char** t, int n, int k) {
	char* add;
	int hun, ten, one;
	int** add_, i, j;
	int index=0, fl=0, sum=0, check;
	add = (char*)malloc(k * sizeof(char)); 
	add_ = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		add_[i] = (int*)malloc(13 * sizeof(int));
	}
	//Зануление доп. матрицы
	for (i = 0; i < n; i++) {
		for (j = 0; j < 13; j++) {
			add_[i][j]= 0;
		}
	}
	//Перевод из char в int
	for (i = 0; i < n; i++) {
		fl = 0;
		index = 0;
		check = 0;
		for (j = 0; t[i][j] != '\0'; j++) {
			if (t[i][j] >= '0' && t[i][j] <= '9'&& check<=12) {
				switch (fl) {
				case 0: hun = (int)t[i][j] - 48; break;
				case 1: ten = (int)t[i][j] - 48; break;
				case 2: one = (int)t[i][j] - 48; break;
				}
				fl ++;

				if (t[i][j + 1] == 'b'|| t[i][j + 1] == ' ' ) {
					fl = 0;
					add_[i][index] = 100 * hun + 10 * ten + one;
					index++;
					check++;
				}
			}
			
		}
		
	}
	//Подсчет общих сумм
	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j < 12; j++) {
			sum += add_[i][j];
		}
		add_[i][12] = sum;
	}
	
	//Сортировка пузырьком
	for (i = 0; i < n; i++) {
		for (j = n - 1; j > i; j--) {
			if (add_[j - 1][12]>add_[j][12]) {
				fl = add_[j - 1][12];  
				add_[j - 1][12] = add_[j][12];
				add_[j][12] = fl;/*Идея такова: сортировка значений 
									   общих сумм и соответсвующих им строк
									   происходит одновременно*/
				add = t[j - 1];
				t[j - 1] = t[j];
				t[j] = add;
			}
		}
	}
	printf("Сотрудники по возрастанию общей з/п:\n");
	prntf(t, n);
	printf("Список общих з/п:\n");

	for (i = 0; i < n; i++) {
			printf("%4d\n", add_[i][12]);
		}
}
