//5. Реализовать программу для простейшего моделирования линейного списка на основе массива с указателями-индексами.

#include <stdio.h>;
#include <iostream>
#include <string>

#define SIZE 5

using namespace std;

typedef struct s_list
{
	string data;
	int next;
} t_list;

void zeroing(t_list sp[])
{
	int i = 1;
	while (i < SIZE)
	{
		sp[i].data = "";
		sp[i].next = -1;
		i++;
	}
}

int queue_empty(int N)
{
	if (N == 1)
	{
		return 1;
	}
	else if (N != SIZE)
	{
		return 2;
	}
	else if (N == SIZE)
	{
		return 0;
	}
}

void push_after(t_list sp[], string data, string elem, int& N)
{
	int j = 0;
	int i = sp[0].next;

	while (sp[i].data != elem && sp[i].next != 0)
		i = sp[i].next;
	while (sp[j].next != -1)
		j++;
	sp[j].data = data;
	sp[j].next = sp[i].next;
	sp[i].next = j;
	N++;
}

void push_before(t_list sp[], string data, string elem, int& N)
{
	int j = 0;
	int i = 0;

	if (queue_empty(N)) {
		cout << "Operation \"insert before\" cannot be applied to an empty list" << endl;
	}
	else {
		while (sp[i].next != 0 && sp[sp[i].next].data != elem)
			i = sp[i].next;
		while (sp[j].next != -1)
			j++;
		sp[j].data = data;
		sp[j].next = sp[i].next;
		sp[i].next = j;
		N++;
	}
}

void pop(t_list* sp, string data, int& N)
{
	int i = sp[0].next;
	int j = 0;

	while (sp[i].data != data && i != 0)
	{
		j = i;
		i = sp[i].next;
	}

	if (sp[i].data == data)
	{
		sp[j].next = sp[i].next;
		sp[i].data = "";
		sp[i].next = -1;
		N--;
	}
}

void print(t_list sp[])
{
	int i = sp[0].next;
	while (i != 0)
	{
		cout << sp[i].data << " ";
		i = sp[i].next;
	}
	cout << endl;
}

int main()
{
	t_list sp[SIZE];
	int N = 1;
	char a;
	char insert;
	string data;
	string elem;

	zeroing(sp);
	sp[0].next = 0;
	sp[0].data = "head";

	while (true)
	{
		cout << "--------------------------------------" << endl;
		cout << "Check for empty......................1" << endl;
		cout << "Add element..........................2" << endl;
		cout << "Delete element.......................3" << endl;
		cout << "Print list...........................4" << endl;
		cout << "--------------------------------------" << endl;
		cout << "Enter value: ";

		cin >> a;
		if (a < '1' || a > '4')
			cout << "Incorrect entry" << endl;
		else
		{
			switch (a)
			{
				case '1':
					if (queue_empty(N) == 0)
						cout << "List is full" << endl;
					else if (queue_empty(N) == 1)
						cout << "List is empty" << endl;
					else
						cout << "List isn't empty" << endl;
					break;
				case '2':
					if (queue_empty(N) == 0)
						cout << "List is full" << endl;
					else
					{
						cout << "Enter element: ";
						cin >> data;
						cout << "After which element to insert: ";
						cin >> elem;
						cout << "Insert before or after element? 0 - before; 1 - after\n";
						cin >> insert;
						if (insert == '1')
							push_after(sp, data, elem, N);
						else if (insert == '0')
							push_before(sp, data, elem, N);
					}
					break;
				case '3':
					if (queue_empty(N) == 1)
						cout << "List is empty" << endl;
					else
					{
						cout << "Enter element: ";
						cin >> data;
						pop(sp, data, N);
					}
					break;
				case '4':
					if (queue_empty(N) == 1)
						cout << "List is empty" << endl;
					else print(sp);
					break;
			}
		}
	}
	return 0;
}