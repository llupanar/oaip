// Даны действительные числа a, b, c. 
//Удвоить числа, если a >=b>=c и заменить их абсолютными значениями, если это не так.
#include <stdio.h>
#include <iostream> // для scanf_s
#include <windows.h> //для команды system
int main (){
	float a, b, c; 
	printf("a, b, c\n");
	scanf_s("%f%f%f", &a, &b, &c);
	system("CLS"); //чистка экрана
if (a >= b && b>= c) 
{
	a *= a;
	b *= b;
	c *= c;
}
else { 
	a = fabs(a); // абсолютное значение
	b = fabs(b);
	c = fabs(c);
}
printf("rezult %f %f %f\n", a, b, c);
return 0;
}
