#include "textcorrection.h"
#include <stdio.h>
#include <string.h>
//Функция замены i-го символа в строке на "a"
string replace_symb(string str, int i, char a) {
	str.word[i] = a;
	return str;
}
//Функция удаления i-го символа из строки
string delete_symb(string str, int i) {

	for (int j = i; j < str.len - 1; j++) {
		str.word[j] = str.word[j + 1];
	}
	str.len--;
	return str;
}
//Функция вставки символа "a" на i-ю позицию в строке
string insert_symb(string str, int i, char a) {

	for (int j = str.len; j > i - 1; j--) {
		str.word[j] = str.word[j - 1];
	}
	str.word[i] = a;
	str.len++;
	return str;
}
//Функция корректировки строки
string correct_str(string str) {
	int memory = str.len;
	for (int i = 0; i < str.len; i++) {
		if (str.word[0] == ' ') {	//Проверка на пробелы перед первой буквой
			str = delete_symb(str, 0);
			i--;
		}
		else if (str.word[0] >= 'a' && str.word[0] <= 'z') {	//Проверка на строчную первую букву
			str.word[0] -= 32;
		}
		else if (str.word[i] == ' ' && str.word[i + 1] == ' ') {	//Проверка на два подряд идущих пробела
			str = delete_symb(str, i);
			i--;
		}
		else if (str.word[i] == ' ' && (str.word[i + 1] == '.' || str.word[i + 1] == ',')) {	//Проверка на отсутствие пробела перед знаком препинания
			str = delete_symb(str, i);
			i--;
		}
		else if (str.word[i] == ' ' && (str.word[i - 1] == '.' || str.word[i - 1] == '?' || str.word[i - 1] == '!') && (str.word[i + 1] >= 'a' && str.word[i + 1] <= 'z')) {	//Проверка на строчную букву в начале предложения
			str.word[i + 1] -= 32;
		}
		else if ((str.word[i] == ',' || str.word[i] == ':' || str.word[i] == ';' || str.word[i] == '.') && str.word[i + 1] != ' ') {	//Проверка на пробел после после конца предложения
			
			//Выделение памяти, если при добавлении пробелов в строчку память полностью заполнена
			if (str.len == memory) {
				str = reallocate_buffer(str);
				memory = str.len + SIZE;
			}
			str = insert_symb(str, i + 1, ' ');
		}

	}
	//Освобождение лишней памяти
	str = trim_buffer(str);

	return str;
}
