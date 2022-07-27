//           Реализовать метод открытого хеширования.Исходные ключи – любые слова(например – фамилии).
//       Размер хеш - таблицы должен задаваться в программе с помощью константы m.
//       Хеш - функция – такая же, что и в задании 1, но делить надо на константу m.
//       В случае возникновения конфликта при попытке размещения в таблице нового ключа этот ключ добавляется в конец вспомогательного списка.
//       Это требует включения в каждую ячейку хеш - таблицы двух указателей на начало и конец вспомогательного списка.
//  
//      Программа должна выполнять следующие действия :
//      •	добавление нового ключа в таблицу с подсчетом сделанных при этом сравнений
//      •	поиск заданного ключа в таблице с подсчетом сделанных при этом сравнений
//      •	вывод текущего состояния таблицы на экран
//      •	удаление заданного ключа из таблицы
//  
//      Алгоритм удаления :
//      •	вычислить хеш - функцию и организовать поиск удаляемого элемента в таблице
//      •	если удаляемый элемент найден в ячейке таблицы, то эта ячейка либо становится пустой(если связанный с ней список пуст), 
//  		либо в нее записывается значение из первого элемента списка с соответствующим  изменением указателей
//      •	если удаляемый элемент найден в списке, то производится его удаление с изменением указателей


#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

struct s_list
{
	string Data;
	s_list* next;
};

struct node
{
	string Data;
	s_list* first;
	s_list* last;
};

node* a = NULL;
int m = 19;
int all_comparisons = 0;
int comparisons = 0;

string keys[] = { "STARTING", "COMMAND", "ENDLESS", "RETURN", "GETING", "STRING", "IFELSE", "NEVER", "THISIS", "PRIVATE" };

void zeroing()
{
	for (int i = 0; i < m; i++)
	{
		a[i].Data = "<empty>";
		a[i].first = NULL;
		a[i].last = NULL;
	}
}

int isEmpty(node elem)
{
	if (elem.Data == "<empty>")
		return 1;

	if (elem.first == NULL)
		return 2;

	return 0;
}

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

bool search(string key)
{
	comparisons = 1;
	int code = 0;

	code = get_code(key);

	if (isEmpty(a[code]) == 1)
		return 0;
	else if (isEmpty(a[code]) == 2)
	{
		if (a[code].Data == key)
			return 1;
		return 0;
	}
	else
	{
		if (a[code].Data == key)
			return 1;

		s_list* temp = a[code].first;
		comparisons++;

		while (temp->Data != key && temp->next != NULL)
		{
			temp = temp->next;
			comparisons++;
		}

		if (temp->Data != key)
			return 0;
	}
}

bool pop(string key, int code)
{
	if (search(key) == 0)
		return false;
	else if (isEmpty(a[code]) == 2)
	{
		a[code].Data = "<empty>";

		return true;
	}
	else
	{
		if (a[code].Data == key)
		{
			s_list* temp = a[code].first;

			a[code].Data = temp->Data;
			a[code].first = temp->next;

			temp->Data = "";
			temp->next = NULL;
			delete temp;
		}
		else if (a[code].first->next == NULL)
		{
			s_list* temp = a[code].first;

			temp->Data = "";
			temp->next = NULL;
			delete temp;

			a[code].first = NULL;
			a[code].last = NULL;
		}
		else
		{
			if (a[code].first->Data == key)
			{
				s_list* temp = a[code].first;

				a[code].first = temp->next;

				temp->Data = "";
				temp->next = NULL;
				delete temp;
			}
			else
			{
				s_list* temp = a[code].first->next;
				s_list* temp1 = a[code].first;

				while (temp->Data != key)
				{
					temp = temp->next;
					temp1 = temp1->next;
				}

				if (temp->next == NULL)
				{
					s_list* temp = a[code].first;

					a[code].last = temp1;

					temp->Data = "";
					temp->next = NULL;
					delete temp;
				}
				else
				{
					temp1->next = temp->next;
					temp->Data = "";
					temp->next = nullptr;
					delete temp;
				}
			}
		}
	}

	return true;
}

void print(node head)
{
	cout << head.Data << " ";

	if (isEmpty(head) == 0)
	{
		s_list* temp = head.first;

		while (temp != NULL)
		{
			cout << temp->Data << " ";

			temp = temp->next;
		}
	}

	cout << endl;
}

bool push(string key)
{
	int i = 1;
	int code = 0;

	cout << "Key: " << key << "" << endl;

	if (search(key) != 0)
		return false;

	code = get_code(key);

	if (isEmpty(a[code]) == 1)
	{
		a[code].Data = key;
	}
	else if (isEmpty(a[code]) == 2)
	{
		s_list* elem = new s_list();

		elem->Data = key;
		elem->next = NULL;

		a[code].first = elem;
		a[code].last = elem;
	}
	else if (isEmpty(a[code]) == 0)
	{
		s_list* elem = new s_list();

		elem->Data = key;
		elem->next = NULL;

		a[code].last->next = elem;
		a[code].last = elem;
	}

	return true;
}

void push_random(string str)
{
	string concat;

	comparisons++;

	if (search(str) == 0)
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

	for (int i = 0; i < 20; i++)
	{
		r = rand() % 10;
		comparisons = 1;

		if (search(keys[r]) == 0)
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

	a = new node[m];

	zeroing();

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

			if (search(get_key()) != 0)
				cout << "Element found " << endl;
			else
				cout << "Element not found" << endl;

			cout << endl << "Comparison count  " << comparisons << endl;

			comparisons = 0;

			break;
		case 3:
			cout << "Content of the hash-table:" << endl;

			for (int i = 0; i < m; i++)
				print(a[i]);

			break;
		case 4:
			random();

			cout << "Number of comparisions: " << all_comparisons << endl << endl;

			break;
		case 5:

			if (code != -1)
			{

				string str;

				cout << "Enter the element to delete: ";

				str = get_key();
				code = get_code(str);

				if (pop(str, code))
				{
					cout << "Element " << str << " has been found in cell " << code << endl;
					cout << "Element has been deleted" << endl;
				}
				else
				{
					cout << "Element doesn't exist" << endl;
				}
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
