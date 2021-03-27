#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

int check(int rightBound, int leftBound) {
	int errorFlag;
	int element;
	errorFlag = scanf_s("%d", &element);
	if (rightBound != 0) {
		while (!errorFlag || element > rightBound || element < leftBound) {
			printf("Incorrect input. Try again\n");
			rewind(stdin);
			errorFlag = scanf_s("%d", &element);
		}
	}
	else {
		while (!errorFlag || element < leftBound) {
			printf("Incorrect input. Try again\n");
			rewind(stdin);
			errorFlag = scanf_s("%d", &element);
		}
	}
	system("CLS");
	return element;
}
int stringLength(char* string) {
	int i = 0;
	while (1) {
		if (string[i] == '\n' || string[i] == '\0')break;
		i++;
	}
	return i;
}
int menu() {
	int choice;
	printf("[1] - hello\n[2] - input information\n[3] - print information\n[4] - search your number\n[5] - move of curent set\n[0] - go out\n");
	choice = check(5, 0);
	return choice;
}
void addSpace(FILE* file, int number, fpos_t *endSet) {
	fseek(file, 0, 2);
	while (number > 0) {
		fprintf(file, "%c", ' ');
		fgetpos(file, endSet);
		number--;
	}
	fgetpos(file, endSet);

}
void move(FILE* file, fpos_t endSet, fpos_t curentSet) {
	int moveNumber;
	char symbol;
	printf("Enter\n");
	moveNumber = check(0, 0);
	system("cls");


	addSpace(file, moveNumber, &endSet);
	fseek(file, 0, 2);
	fgetpos(file, &endSet);

	int numberInfo = endSet-moveNumber;
	curentSet = numberInfo - 1;
	endSet--;

	fseek(file, 0, 2);

	while (numberInfo > 0) {

		fsetpos(file, &curentSet);
		fscanf(file, "%c", &symbol);
		curentSet--;


		fsetpos(file, &endSet);
		fprintf(file, "%c", symbol);
		endSet--;
		numberInfo--;
	}

	fseek(file, 0, 0);

	while (moveNumber > 0) {
		fprintf(file, "%c", ' ');
		moveNumber--;
	}
}
void search(FILE* file) {
	system("cls");
	int match = 0;
	int searchNumber, curentNumber;
	printf("Enter your number\n");
	searchNumber = check(0, 0);
	system("cls");
	while (!feof(file))
	{
		fscanf(file, "%d", &curentNumber);
		if (feof(file)) {
			rewind(stdin);
			break;
		}
		if (curentNumber == searchNumber) {
			match++;
		}
	}
	printf("Your number: %d\nMatch: %d",searchNumber, match);
	printf("\n\n");
}
void inputInfo(FILE *file, fpos_t* endSet) {
	printf("Enter numbers\nTap ENTER, if you want to end this operation\n");
	char addInformation;
	fsetpos(file, &endSet);
	getchar();
	while (1) {

		scanf_s("%c", &addInformation);

			if (addInformation!=' '&& (addInformation < '0' || addInformation>'9')) {
				
				addInformation = '\n';
				break;
			}
		if (addInformation == '\n') {
			fprintf(file, "%c", ' ');
			fgetpos(file, &endSet);
			break;
		}

		fprintf(file, "%c", addInformation);
	}
	fgetpos(file, &endSet);

}
void outputInfo(FILE* file) {
	system("cls");
	char symbol;
	printf("Your file's content:\n");
	rewind(stdin);
	fseek(file, 0, 0);
	while (!feof(file)) {
		fscanf(file, "%c", &symbol);
		if (feof(file))
			break;
		printf("%c", symbol);
	}
	rewind(stdin);
	printf("\n\n\n");
}

void inputInfoB(FILE* file, fpos_t* endSet);
void outputInfoB(FILE* file);
void searchB(FILE* file);
void changeB(FILE* file, fpos_t endSet, fpos_t curentSet);

int main()
{
	int choice;
	int numbers=6;
	char fileName[40];
	int i;

	FILE* file;
	fpos_t curentSet=0, endSet=0;

	while (1)
	{

		printf("[1] - text mode\n[2] - binary mode\n[0] - go out\n");
		choice = check(2, 0);
		if (choice == 0)break;
		else {
			printf("Enter the name of your file\n");
			getchar();
			fgets(fileName, 35, stdin);
			i = stringLength(fileName);
			fileName[i++] = '.';
			fileName[i++] = 't';
			fileName[i++] = 'x';
			fileName[i++] = 't';
			fileName[i] = '\0';

			if (choice == 1) {
				while (1) {
					rewind(stdin);
					choice = menu();
					if (choice == 0)break;
					switch (choice) {
					case 1: 
						printf("You are so cute! Hello :)\n");
					break;

					case 2: if ((file = fopen(fileName, "a+")) == NULL) {
						printf("ERROR\n");
						exit(111);
					}
						  fsetpos(file, &endSet);
						  inputInfo(file, endSet);
						  fclose(file);
						  
						  break;
					case 3:

						if ((file = fopen(fileName, "r")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}
						fsetpos(file, &endSet);
						outputInfo(file);
						fclose(file); break;
						
						break;
					case 4: 
						if ((file = fopen(fileName, "r")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}
						fsetpos(file, &endSet);
						search(file);
						fclose(file); break;
						
					case 5: 
						if ((file = fopen(fileName, "r+")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}

						fsetpos(file, &endSet);
						move(file, endSet, curentSet);
						fclose(file);
						break;
					}

				}
			}



			else {
				while (1) {
					choice = menu();
					if (choice == 0)break;

					switch (choice) {
					case 1:
						printf("AWWWWWwWWW! Hello :)\n");
						break;
					case 2:
						if ((file = fopen(fileName, "w+b")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}
						fsetpos(file, &endSet);
						inputInfoB(file, &endSet);
						fclose(file);
						break;
					case 3:
						if ((file = fopen(fileName, "rb")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}
						fsetpos(file, &endSet);
						outputInfoB(file);
						fclose(file);
						break;
					case 4:
						if ((file = fopen(fileName, "r+b")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}
						fsetpos(file, &endSet);
						searchB(file);
						fclose(file);
						break;
					case 5:
						if ((file = fopen(fileName, "r+b")) == NULL) {
							printf("ERROR\n");
							exit(111);
						}
						fsetpos(file, &endSet);
						changeB(file, endSet, curentSet);
						fclose(file);
						break;
					}
				}
			}
		}
	}
	return 0;
}
void inputInfoB(FILE* file, fpos_t* endSet) {

	printf("Enter numbers\nTap ENTER, if you want to end this operation\n");
	char addInformation;
	fsetpos(file, &endSet);
	getchar();
	while (1) {

		scanf_s("%c", &addInformation);
		if (addInformation != ' ' && (addInformation < '0' || addInformation>'9')) {
			addInformation = '\n';
			break;
		}
		if (addInformation == '\n') {
			fwrite(' ', sizeof(char), 1, file);
			fgetpos(file, &endSet);
			break;
		}

		fwrite(&addInformation, sizeof(char), 1, file);
	}
	fgetpos(file, &endSet);

}
void outputInfoB(FILE* file) {
	system("cls");
	printf("Your file's content:\n");
	rewind(file);
	fseek(file, 0, 0);
	char symbol;
	while (1) {
		fread(&symbol, sizeof(int), 1, file);
		if (feof(file)) break;
		printf("%c", symbol);
	}
}
void searchB(FILE* file) {
	system("cls");
	int match = 0;
	int searchNumber, curentNumber;
	printf("Enter your number\n");
	searchNumber = check(0, 0);
	system("cls");
	while (!feof(file))
	{
		fread(&curentNumber, sizeof(int), 1, file);
		if (feof(file)) {
			rewind(stdin);
			break;
		}
		if (curentNumber == searchNumber) {
			match++;
		}
	}
	printf("Your number: %d\nMatch: %d", searchNumber, match);
	printf("\n\n");
}
void changeB(FILE* file, fpos_t endSet, fpos_t curentSet) {
	system("cls");
	int max = 0;
	int pos = 0;
	int searchNumber, curentNumber;
	printf("Enter your number\n");
	searchNumber = check(0, 0);
	system("cls");
	fread(&curentNumber, sizeof(int), 1, file);
	max = curentNumber;
	while (!feof(file))
	{
		fread(&curentNumber, sizeof(int), 1, file);
		if (feof(file)) {
			rewind(stdin);
			break;
		}
		if (curentNumber > max) {
			max = curentNumber;
		}
	}
	rewind(file);
	fseek(file, 0 * sizeof(char), SEEK_SET);

	while (!feof(file))
	{
		char maxNumber[5];
		fread(&curentNumber, sizeof(char), 1, file);
		if (feof(file)) {
			rewind(stdin);
			break;
		}
		if (curentNumber == max) {
			itoa(max, maxNumber, 10);
			fseek(file, pos * sizeof(max), SEEK_SET);
			fwrite(&maxNumber, sizeof(max), 1, file);
		}
	}
	printf("\n\n");
}
