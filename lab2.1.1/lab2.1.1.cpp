//			Реализовать программу, объединяющую простейшие методы сортировки массивов :
//			
//			- сортировку обменом(метод пузырька)
//			- сортировку выбором
//			- сортировку вставками

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int* arr = NULL;
int compares = 0;
int changes = 0;
int num = 0;

void Print(int* b)
{
	cout << endl << "array status: " << endl;

	for (int i = 0; i < num; i++)
		cout << b[i] << " ";

	cout << "" << endl;
}

//создание копии исходного массива
int* copy_of_array()
{
	int* b = new int[num];

	for (int i = 0; i < num; i++)
		b[i] = arr[i];

	return b;
}

void Create_Array()
{
	num = 0;
	cout << "How mach elements to generate: ";

	while (num < 1 || num > 10000)
	{
		cin >> num;
		if (num < 1 || num >10000) cout << "Invalid value. Retry: ";
	}

	if (arr != NULL)
		delete[] arr;

	arr = new int[num];

	srand(time(NULL));

	for (int i = 0; i < num; i++)
		arr[i] = rand() % 100;

}

void sorting_bubble()
{
	compares = 0;
	changes = 0;
	int* b = copy_of_array();
	int temp;

	cout << endl << "Bubble sort: " << endl;

	for (int i = 0; i < num; i++)
		for (int j = num - 1; j > i; j--)
		{
			compares++;

			if (b[j - 1] > b[j])
			{
				temp = b[j - 1];
				b[j - 1] = b[j];
				b[j] = temp;
				changes++;
			}
		}

	Print(b);

	cout << endl << "Number of comparisons: " << compares << endl
		<< "Number of changes: " << changes << "" << endl;

	delete[] b;
}

void sorting_inserts()
{
	compares = 0; changes = 0;
	int* b = copy_of_array();
	int temp = 0, i = 0, j = 0;
	cout << endl << "Insertions sort" << endl;
	for (i = 1; i < num; i++)
	{
		temp = b[i];
		j = i - 1;
		compares++;

		while (j > -1 && temp < b[j])
		{
			b[j + 1] = b[j];

			if (j != i - 1) //если произошла перестановка во внутреннем цикле
				changes++;

			j--;
			compares++;
		}

		if (b[j + 1] == temp) //если перестановок не было
			changes--;

		b[j + 1] = temp;
		changes++;
	}

	Print(b);

	cout << endl << "Number of comparisons: " << compares << endl
		<< "Number of changes: " << changes << "" << endl;

	delete[] b;
}

void sorting_choice()
{
	compares = 0;
	changes = 0;
	int* b = copy_of_array();
	int min = 0, i = 0, j = 0, k = 0;
	cout << endl << "Sort by choice" << endl;

	for (i = 0; i < num; i++)
	{
		k = i;
		min = b[i];
		for (j = i + 1; j < num; j++)
		{
			if (b[j] < min)
			{
				k = j; min = b[j];
			}
			compares++;
		}

		if (b[i] == min) //если перестановок не было
			changes--;

		b[k] = b[i];
		b[i] = min;
		changes++;
	}

	Print(b);

	cout << endl << "Number of comparisons: " << compares << endl
		<< "Number of changes: " << changes << "" << endl;

	delete[] b;
}

int main()
{
	Create_Array();
	Print(arr);
	int c = -1;

	while (true)
	{
		c = -1;
		cout << "--------------------------------------------------" << endl
			<< "Bubble sort.................................1" << endl
			<< "Insertions sort.............................2" << endl
			<< "Sort by choice..............................3" << endl
			<< "All methods.................................4" << endl
			<< "Update array................................5" << endl
			<< "Exit........................................6" << endl << endl
			<< "Enter the number: ";
		cin >> c;

		while ((c < 0) || (c > 5))
		{
			cout << endl << "Incorrect value. Retry: ";
			cin >> c;
		}
		switch (c)
		{
		case 1:
			Print(arr);
			sorting_bubble();
			break;
		case 2:
			Print(arr);
			sorting_inserts();
			break;
		case 3:
			Print(arr);
			sorting_choice();
			break;
		case 4:
			Print(arr);
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			sorting_bubble();
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			sorting_inserts();
			cout << "----------------------------------------------------------------------------------------------------" << endl;
			sorting_choice();
			break;
		case 5:
			Create_Array();
			break;
		case 6:
			break;
		}
	}

	delete[] arr;
	return 0;
}
