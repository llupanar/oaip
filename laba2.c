#include<stdio.h>

int main() {

	int f = 0, s = 0, k = 0;
	char mas[16] = { "  hello world  " };

	for (int i = 0; i<15; i++) {
		if (mas[i] != ' ') {
			s++;
			if (f == 0) {
				k++;
				f = 1;
			}
		}
		else {
			f = 0;
		}
	}
	
	printf("%.2f", (float)s / k);
	
}
