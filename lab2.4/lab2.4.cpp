//                Построить бесконфликтную хеш-таблицу для заданного набора текстовых ключей. 
//                Число ключей (и размер таблицы) равен 10. 
//                В качестве ключей взять 10 любых служебных слов языка Паскаль. 
//                Для преобразования текстовых ключей в числовые значения использовать суммирование кодов символов текстового ключа: код (End) = код (E) + код (n) + код (d). 
//                Преобразование числового кода ключа в значение индекса выполнить с помощью простейшей хеш-функции, которая берет остаток от целочисленного деления кода на размер хеш-таблицы (в задании – 10).
//     
//			 •	ввести подобранные ключи и расположить их в ячейках хеш - таблицы в соответствии со значением хеш - функции
//           •	вывести хеш - таблицу на экран
//           •	организовать циклический поиск разных ключей, как имеющихся в таблице(с выводом местоположения), так и отсутствующих : вычислить для ключа значение хеш - функции и сравнить содержимое соответствующей ячейки таблицы с исходным ключом
//               
//               


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

string* a = NULL;
int N = 10;

string keys[] = { "START", "STOP", "END", "RETURN", "GET", "STRING", "IF", "ELSE", "THIS", "PRIVATE" };  


string get_key()
{
	string str;
	cin >> str;
	return str;
}

bool key_found(string key)
{
	bool x = false;

	for (int i = 0; i < N; i++)
	{
		if (key == keys[i])
		{
			x = true;
			break;
		}
	}

	return x;
}

int get_code(string key)
{
	int code = 0;

	for (int i = 0; i < key.length(); i++)
	{
		code += (int)key[i];
	}

	cout << "Code of the key: " << code << "" << endl;
	code = code % N;
	cout << "After application of the hash-function, the element index is equal: " << code << "" << endl;
	return code;
}
 
void Print(int* b)
{
	cout << endl << "Array: " << endl;

	for (int i = 0; i < N; i++)
		cout << b[i] << "";

	cout << "" << endl;
}

bool push(string key)
{
	cout << "Key: " << key << "" << endl;

	int code = 0;

	if (key_found(key))
	{
		code = get_code(key);

		if (a[code] != key)
		{
			a[code] = key;

			return true;
		}
		else
			cout << endl << "The element has already been added " << endl;
	}
	else
		cout << endl << "Key is not possible" << endl;
	return false;
}

int main()
{
	int k = 0;
	int	code = 0;

	string str;

	a = new string[N];

	for (int i = 0; i < N; i++)
		a[i] = "<empty>";

	int c;

	while (true)
	{
		c = -1;

		cout << "Choose a key : GET, STRING, IF, ELSE, THIS, PRIVATE, START, STOP, END, RETURN" << endl << endl
			<< "----------------------------------" << endl
			<< "Add new element..................1" << endl
			<< "Search for an element............2" << endl
			<< "Print state of the table.........3" << endl
			<< "Fill the table automatically.....4" << endl
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
			if (k < N)
			{
				cout << "Enter the string: ";
				if (push(get_key()))
				{
					k++;
					cout << "Element added" << endl;
				}
				else
					cout << "Element not added" << endl;
			}
			else
				cout << "All cells of the table are already filled" << endl;
			break;
		case 2:
			cout << "Enter the key: ";
			str = get_key();
			code = get_code(str);
			if (str == a[code])
				cout << "Element found " << code << "" << endl;
			else
				cout << "Element not found" << endl;

			break;
		case 3:
			cout << "Content of the hash-table:" << endl;

			for (int i = 0; i < N; i++)
				cout << i << ") " << a[i] << "" << endl;

			break;
		case 4:
			for (int i = 0; i < N; i++)
				push(keys[i]);

			k = N;

			break;
		case 5:
			cout << "Enter the element to delete: ";

			str = get_key();
			code = get_code(str);

			if (str == a[code])
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
