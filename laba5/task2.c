#include <stdio.h>
#include<locale.h>
#include <malloc.h>
#include<time.h>
#include <windows.h>

int main() {

	int i, j;
	int n, win, lose, draw, sum = 0, pr = 0, per = 0, per1=0, d;
	int** a;

	setlocale(LC_ALL, "Russian"); //русификация
	do // Размерность массива и проверка на корректный ввод
	{
		system("CLS");
		printf("Введите число команд\n");
		rewind(stdin); 
		d = scanf_s("%d", &n);
	} while (!d || n <= 1); 
	
	a = (int**)malloc(n * sizeof(int*)); // Выделение памяти под указатели на строки

	srand(time(NULL));// Заполнение массива рандомными значениями от 0 до 2
	for (i = 0; i < n; i++) { 
		a[i] = (int*)malloc(n * sizeof(int)); // Выделение памяти под строки
		   for (j = 0; j < n; j++) {
			   if (i == j)
				   a[i][j] = 0;
			  else /*if (i == 4 || i==5)
				   a[i][j] = 1; // Для проверки задания б) 
				                //Слишком мала вероятность выполнения условия
				else*/
			a[i][j] = rand() % 3 - 0;
		    }   
	}

	printf("Итоги матча:\n");// Вывод массива на экран
	for (i = 0; i < n; i++) { 
		for (j = 0; j < n; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}

	printf("Номера команд, у которых нет поражений:");
	for (i = 0; i < n; i++) {
		win = 0;
		lose = 0;
		draw = 0;
		for (j = 0; j < n; j++) {
			if (i == j)
				continue;
			else
			switch (a[i][j]) {
			case 1: win++;
				break;
			case 0: lose++;
				break;
			case 2: draw++;
				break;
			}
		}
		if (win > ((n - 1) / 2)) //Команды, выигр. больше половины игр
			per++;

		if (win > lose) 
			sum++;

		if (lose==0) {
			printf("%3d", ++i);
			i--;
			pr++; //Для проверки налачия команд без проигрышей
		}
	}
	if (pr == 0)
		printf("отсутствуют");
    
	printf("\nЧисло команд, у которых больше побед, чем проигрышей: %d\n", sum);

	if (per != 0) {
  
		if (per != 1) {
			printf("%d команды выиграли более половины игр", per);
		}
		else printf("Одна команда выиграла более половины игр");
	}
	else printf("Ни одна команда не выиграла более половины игр");
	free(a);
	}
