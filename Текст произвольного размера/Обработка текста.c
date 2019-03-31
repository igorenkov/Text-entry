#include "textcorrection.h"
#include <stdio.h>
#include <string.h>
//������� ������ i-�� ������� � ������ �� "a"
string replace_symb(string str, int i, char a) {
	str.word[i] = a;
	return str;
}
//������� �������� i-�� ������� �� ������
string delete_symb(string str, int i) {

	for (int j = i; j < str.len - 1; j++) {
		str.word[j] = str.word[j + 1];
	}
	str.len--;
	return str;
}
//������� ������� ������� "a" �� i-� ������� � ������
string insert_symb(string str, int i, char a) {

	for (int j = str.len; j > i - 1; j--) {
		str.word[j] = str.word[j - 1];
	}
	str.word[i] = a;
	str.len++;
	return str;
}
//������� ������������� ������
string correct_str(string str) {
	int memory = str.len;
	for (int i = 0; i < str.len; i++) {
		if (str.word[0] == ' ') {	//�������� �� ������� ����� ������ ������
			str = delete_symb(str, 0);
			i--;
		}
		else if (str.word[0] >= 'a' && str.word[0] <= 'z') {	//�������� �� �������� ������ �����
			str.word[0] -= 32;
		}
		else if (str.word[i] == ' ' && str.word[i + 1] == ' ') {	//�������� �� ��� ������ ������ �������
			str = delete_symb(str, i);
			i--;
		}
		else if (str.word[i] == ' ' && (str.word[i + 1] == '.' || str.word[i + 1] == ',')) {	//�������� �� ���������� ������� ����� ������ ����������
			str = delete_symb(str, i);
			i--;
		}
		else if (str.word[i] == ' ' && (str.word[i - 1] == '.' || str.word[i - 1] == '?' || str.word[i - 1] == '!') && (str.word[i + 1] >= 'a' && str.word[i + 1] <= 'z')) {	//�������� �� �������� ����� � ������ �����������
			str.word[i + 1] -= 32;
		}
		else if ((str.word[i] == ',' || str.word[i] == ':' || str.word[i] == ';' || str.word[i] == '.') && str.word[i + 1] != ' ') {	//�������� �� ������ ����� ����� ����� �����������
			
			//��������� ������, ���� ��� ���������� �������� � ������� ������ ��������� ���������
			if (str.len == memory) {
				str = reallocate_buffer(str);
				memory = str.len + SIZE;
			}
			str = insert_symb(str, i + 1, ' ');
		}

	}
	//������������ ������ ������
	str = trim_buffer(str);

	return str;
}
