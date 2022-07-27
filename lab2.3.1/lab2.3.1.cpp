//          Реализовать специальные методы сортировки :
//          
//          - Простейшую карманную с использованием второго массива и без него
//          - Обобщенную карманную сортировку с повторяющимися ключами и дополнительными списками
//          - Поразрядную сортировку

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

int* a = NULL; //будущий массив
int N = 0; //размер массива (колчиество элементов)
int max_key = 0; // Размер максимального ключа

struct List
{
	int key = -1;
	List* next = NULL;
	List* tail = NULL;
} *ls = NULL, * head = NULL;

void Print(int* arr)
{
	cout << endl << "Array status:  " << endl;

	for (int i = 0; i < N; i++)
		cout << arr[i] << " ";

	cout << endl;
}

int* copy_of_array()
{
	int* b = new int[N];

	for (int i = 0; i < N; i++)
		b[i] = a[i];

	return b;
}

void Create_Array(int n)
{
	N = 0;
	cout << "How mach elements to generate [1 — 1000]: ";

	while (N < 1 || N > 1000)
	{
		cin >> N;

		if (N < 1 || N >1000)
			cout << "Incorrect value. Retry: ";
	}

	if (a != NULL)  // Если массив непустой (обновление массива)
		delete[] a;

	a = new int[N];

	if (n == 1)
	{
		for (int i = 0; i < N; i++)
			a[i] = i;

		max_key = N;
	}
	else if (n == 2)
	{
		max_key = N - N / 3; 

		for (int i = 0; i < max_key; i++)
			a[i] = i;

		for (int i = max_key; i < N; i++)
			a[i] = rand() % max_key;
	}

	int temp, r;

	for (int i = 0; i < N; i++)
	{
		r = rand() % N;
		temp = a[i];
		a[i] = a[r];
		a[r] = temp;
	}

	cout << endl << "Array has created successfully  " << endl;
	Print(a);
}

void pocket_sort()
{
	Create_Array(1);
	cout << endl << "Pocket sort: ";

	int* b = copy_of_array();
	int temp, n = -1;

	cout << "Use second array?  " << endl << " 1 - Yes, 0 - No: ";
	cin >> n;

	while ((n < 0) || (n > 1))
	{
		cout << "Invalid value. Retry: ";
		cin >> n;
	}

	if (n == 0)
	{
		for (int i = 0; i < N; i++)
		{
			while (b[i] != i)
			{
				temp = b[b[i]];
				b[b[i]] = b[i];
				b[i] = temp;
			}
		}
	}
	else if (n == 1)
	{
		int* second_arr = new int[N];

		for (int i = 0; i < N; i++)
			second_arr[b[i]] = b[i];

		delete[] b;

		b = second_arr;
	}

	Print(b);
	delete[] b;
}

void clear(List* pTemp)
{
	if (pTemp->next != NULL)
		clear(pTemp->next);

	delete pTemp;
}

int* convert_list_to_array(List* _head)
{
	List* pCurrent = _head;
	int* c = new int[N];

	for (int i = 0; i < N; i++)
	{
		c[i] = pCurrent->key;
		pCurrent = pCurrent->next;
	}

	return c;
}

// ФУНКЦИЯ ОБЪЕДИНЕНИЯ МАССИВА С ДОПОЛНИТЕЛЬНЫМИ СПИСКАМИ В ОДИН СПИСОК
List* unite(List* _ls)
{
	List* head = new List;

	head->key = _ls[0].key;
	head->next = _ls[0].next;
	head->tail = _ls[0].tail;

	List* pCurrent = head;

	for (int i = 0; i < max_key - 1; i++)
	{
		if (_ls[i].tail != NULL)
			pCurrent = _ls[i].tail;

		pCurrent->next = new List;
		pCurrent = pCurrent->next;
		pCurrent->key = _ls[i + 1].key;
		pCurrent->next = _ls[i + 1].next;
		pCurrent->tail = _ls[i + 1].tail;
	}

	return head;
}

// ОБОБЩЕННАЯ КАРМАННАЯ СОРТИРОВКА С ПОВТОРЯЮЩИМИСЯ КЛЮЧАМИ И ДОПОЛНИТЕЛЬНЫМИ СПИСКАМИ
void sorting_general_pocket()
{
	Create_Array(2);
	cout << endl << "General pocket sort: ";

	int* b = copy_of_array();
	ls = new List[max_key];

	for (int i = 0; i < N; i++) 
	{
		if (ls[b[i]].key == -1) 
			ls[b[i]].key = b[i];

		else if (ls[b[i]].next == NULL)
		{
			ls[b[i]].next = new List;
			ls[b[i]].tail = ls[b[i]].next;
			ls[b[i]].next->key = b[i];
		}

		else if (ls[b[i]].tail->next == NULL)
		{
			ls[b[i]].tail->next = new List;
			ls[b[i]].tail->next->key = b[i];
			ls[b[i]].tail = ls[b[i]].tail->next;
		}
	}

	head = unite(ls);
	b = convert_list_to_array(head); 
	head = NULL;

	Print(b);

	delete[] b;
	delete[] ls;
}

void sorting_radix()
{
	Create_Array(2);
	cout << endl << "Radix sort... " << endl;
	int* b = copy_of_array();
	int k = 0, temp = max_key;

	while (temp != 0)
	{ 
		temp = temp / 10;
		k++;
	}

	int x, _max;
	for (int i = 1; i <= k; i++)
	{ 
		ls = new List[10];

		for (int j = 0; j < N; j++)
		{
			x = b[j];
			for (int z = 1; z < i; z++)
				x = x / 10; 

			x = x % 10;     

			if (ls[x].key == -1)  
				ls[x].key = b[j];

			else if (ls[x].next == NULL)   
			{ 
				ls[x].next = new List;
				ls[x].tail = ls[x].next;
				ls[x].next->key = b[j];
			}
			else if (ls[x].tail->next == NULL)  
			{
				ls[x].tail->next = new List;
				ls[x].tail->next->key = b[j];
				ls[x].tail = ls[x].tail->next;
			}
		}
		_max = max_key;
		max_key = 10; 
		head = unite(ls);
		max_key = _max;
		b = convert_list_to_array(head);

		clear(head);
		head = NULL;

		Print(b);
		delete[] ls;
	}
	delete[] b;
}

int main()
{ 
	srand(time(NULL));

	int c;

	while (true)
	{
		c = -1;
		cout << "-------------------------------------------------- " << endl
			<< "Pocket sort.....................................1" << endl
			<< "General pocket sort.............................2" << endl
			<< "Radix sort......................................3" << endl
			<< "Exit............................................4" << endl << endl
			<< "Enter the number: ";

		cin >> c;

		while ((c < 0) || (c > 3))
		{
			cout << "Incorrect value. Retry: ";
			cin >> c;
		}
		switch (c)
		{
		case 1:
			pocket_sort();
			break;
		case 2:
			sorting_general_pocket();
			break;
		case 3:
			sorting_radix();
			break;
		case 4:
			break;
		}
	}

		delete[] a;
		return 0;
}

