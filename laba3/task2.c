#include <stdio.h>
#include <locale.h>
int main() {

	int  k, kk, kol=0, sum=0, n, a, i, r;
	setlocale(LC_ALL, "Russian");
	printf(" введите n\n");
	scanf_s("%d", &n);
	for (r=0; n<=0; r++ ){ // число должно быть натуральным (n>0)
	printf(" число n - натуральное, введите еще раз\n");
	scanf_s("%d", &n);
	}
	printf("введите числа а1...аn\n");
	for (i=0; i<n; i++)
	{
		scanf_s( "%d", &a);
		k = a % 5;
		kk = a % 7;
		if (k == 0 && kk != 0) {
			kol++; // количество таких чисел
			sum += a; // их сумма 
		}
          
	}
	printf("kol %d\nsum %d", kol, sum);
}
