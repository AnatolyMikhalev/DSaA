//              Реализовать метод внутреннего хеширования.Исходные ключи – любые слова(например – фамилии).
//              Размер хеш - таблицы должен задаваться в программе с помощью константы m.
//              Хеш - функция – такая же, что и в задании 1, но делить надо на константу m.
//              В случае возникновения конфликта при попытке размещения в таблице нового ключа, для него ищется первое свободное по порядку место по формуле
//              j = ((h(ключ) + i)  mod  m) + 1, где  i = 0, 1, 2, . . ., m - 2
//              
//              Программа должна выполнять следующие действия :
//              •	добавление нового ключа в таблицу с подсчетом сделанных при этом сравнений
//              •	поиск заданного ключа в таблице с подсчетом сделанных при этом сравнений
//              •	вывод текущего состояния таблицы на экран


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

string* a = NULL;
int m = 17;
int all_comparisons = 0;
int comparisons = 0;

string keys[] = { "START", "STOP", "END", "RETURN", "GET", "STRING", "IF", "ELSE", "THIS", "PRIVATE" };


string get_key()
{
	string key;
	cin >> key;
	return key;
}

int get_code(string key)
{
	int code = 0;

	for (int i = 0; i < key.length(); i++)
	{
		code += (int)key[i];
	}

	cout << "Code of the key: " << code << "" << endl;
	code = code % m;
	cout << "After application of the hash-function, the element index is equal: " << code << "" << endl;
	return code;
}

void Print(int* b)
{
	cout << endl << "Array: " << endl;

	for (int i = 0; i < m; i++)
		cout << b[i] << "";

	cout << "" << endl;
}

int search(string key)
{
	int i = 1;
	int code = 0;

	cout << "Key: " << key << "" << endl;

	code = get_code(key);

	while (a[code] != "<empty>" && a[code] != key && i <= m - 2)
	{
		//j = ((h(ключ) + i)  mod  m) + 1, где  i = 0, 1, 2, . . ., m - 2
		code = ((get_code(key) + i) % m);// +1;
		i++;
	}

	cout << endl << "Comparison count  " << i << endl;

	if (a[code] == key)
		return code;

	return -1;
}

bool push(string key)
{
	int i = 1;
	int code = 0;

	cout << "Key: " << key << "" << endl;

	code = get_code(key);

	while (a[code] != "<empty>" && a[code] != key && i <= m - 2)
	{
		//j = ((h(ключ) + i)  mod  m) + 1, где  i = 0, 1, 2, . . ., m - 2
		code = ((get_code(key) + i) % m);// +1;
		i++;
	}

	cout << endl << "Comparison count  " << i << endl;


	if (a[code] == "<empty>")
	{
		a[code] = key;

		return true;
	}
	else if (a[code] == key)
		cout << endl << "The element has already been added " << endl;
	else
		cout << endl << "The table is full " << endl;

	return false;
}

void push_random(string str)
{
	string concat;

	comparisons++;

	if (search(str) == -1)
	{
		push(str);
	}
	else
	{
		concat = str.substr(1, str.length()) + str[0];

		push_random(concat);
	}
}

void random()
{
	srand(time(NULL));
	int r;
	string str, concat;

	//str = "sfsffgd0";
//
	//str = keys[r];

	//str.substr()

	for (int i = 0; i < 10; i++)
	{
		r = rand() % 10;
		comparisons = 1;

		if (search(keys[r]) == -1)
		{
			push(keys[r]);
		}
		else
		{
			str = keys[r];

			concat = str.substr(1, str.length()) + str[0];

			push_random(concat);
		}

		all_comparisons += comparisons;
	}
}


int main()
{
	int	code = 0;

	string str;

	a = new string[m];

	for (int i = 0; i < m; i++)
		a[i] = "<empty>";

	int c;

	while (true)
	{
		c = -1;

		cout << "----------------------------------" << endl
			<< "Add new element..................1" << endl
			<< "Search for an element............2" << endl
			<< "Print state of the table.........3" << endl
			<< "Fill table with random keys......4" << endl
			<< "Delete element...................5" << endl
			<< "Exit.............................6" << endl
			<< "----------------------------------" << endl
			<< "Enter the number: ";

		cin >> c;

		while ((c < 1) || (c > 6))
		{
			cout << "Incorrect value. Retry: ";
			cin >> c;
		}
		cout << endl;


		switch (c)
		{
		case 1:
			cout << "Enter the string: ";

			if (push(get_key()))
				cout << "Element added" << endl;
			else
				cout << "Element not added" << endl;

			break;
		case 2:
			cout << "Enter the key: ";

			if (search(get_key()) != -1)
				cout << "Element found " << endl;
			else
				cout << "Element not found" << endl;

			break;
		case 3:
			cout << "Content of the hash-table:" << endl;

			for (int i = 0; i < m; i++)
				cout << i << ") " << a[i] << "" << endl;

			break;
		case 4:
			random();

			cout << "Number of comparisions: " << all_comparisons << endl << endl;

			break;
		case 5:
			cout << "Enter the element to delete: ";

			str = get_key();
			code = search(str);

			if (code != -1)
			{
				cout << "Element " << str << " has been found in cell " << code << endl;
				a[code] = "<empty>";
				cout << "Element has been deleted" << endl;
			}
			else
				cout << "Element not found " << endl;

			break;
		case 6:
			break;
		}
	}

	delete[] a;
	return 0;
}
