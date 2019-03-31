#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "textcorrection.h"
#include <stdlib.h>


console_input (char *parr) {
	
}
file_input() {

}
string reallocate_buffer(string str) { //Функция выделения дополнительной памяти
	string newstr;
	newstr.len = str.len;
	newstr.word = malloc(sizeof(char) * (str.len + SIZE));	//Размер новой строки на SIZE больше предыдущей
	
	for (int i = 0; i < str.len; i++) {
		newstr.word[i] = str.word[i];	//Посимвольное копирование
	}

	free(str.word);
	return newstr;
}
string trim_buffer(string str) {	//Функция освобождения лишней памяти
	string newstr;
	newstr.len = str.len;
	newstr.word = malloc(sizeof(char) * newstr.len);
	
	for (int i = 0; i < str.len; i++) {
		newstr.word[i] = str.word[i];
	}

	free(str.word);
	return newstr;
}
string GetText(FILE *fp, char terminator) {	//Функция считывания строки до символа terminator
	char temp;
	string str;

	str.len = 0;
	str.word = malloc(sizeof(char) * (SIZE));
	
	int i = 0;
	printf("Your simbols: \n");
	while (((temp = getc(fp)) != terminator) && (temp != EOF)) {
		if (fp != stdin) {
			printf("%c", temp);
		}
		//Посимвольный ввод
		str.word[i] = temp;
		i++;	
		str.len++;

		if (i % SIZE == 0) {	//Проверка на заполненность выделенной памяти. Здесь i - фактически колличество введённых символов
			str = reallocate_buffer(str);
		}
	}
	str = trim_buffer(str);
	return str;
}
//Функция посимвольного вывода
void put_string(string str) {
	for (int i = 0; i < str.len; i++) {
		putchar(str.word[i]);
	}
}

int main() {
	char ch;
	do {
		string str;
		char termin;

		printf("Input terminator: \n");
		termin = getchar();
		getchar();

		FILE *fp;
		char iotype;
		printf("Input type of insertion(s - stdio/f - file): ");
		scanf_s("%c", &iotype);
		getchar();

		if (iotype == 'S' || iotype == 's') {
			fp = stdin;
		}
		else if (iotype == 'F' || iotype == 'f') {
			fp = fopen("Text.txt", "r");
		}
		else {
			printf("Mistake :)");
			fp = NULL;
		}

		if (fp == NULL) {
			printf("File opening error!\n");
		}
		else {
			str = GetText(fp, termin);
			str = correct_str(str);

			printf("\nFinal string: \n");
			put_string(str);
		}
		//Повтор программы
		printf("\nDo you wish to restart program? (y/n)\n");
		scanf_s("%c", &ch);
		getchar();

		fclose(fp);
	} while (ch == 'y' || ch == 'Y');
	return 0;
}