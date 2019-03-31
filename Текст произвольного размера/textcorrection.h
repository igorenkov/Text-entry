#pragma once
#define SIZE 5
typedef struct string_info {
	char *word;
	int len;
}string;

string replace_symb(string str, int i, char a);

string delete_symb(string str, int i);

string insert_symb(string str, int i, char a);

string correct_str(string str);

string reallocate_buffer(string str);

string trim_buffer(string str);