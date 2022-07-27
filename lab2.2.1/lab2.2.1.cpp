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
int n = 0;

void Print(int* b)
{
	cout << endl << "array status: " << endl;

	for (int i = 0; i < n; i++)
		cout << b[i] << " ";

	cout << "" << endl;
}

//создание копии исходного массива
int* copy_of_array()
{
	int* b = new int[n];

	for (int i = 0; i < n; i++)
		b[i] = arr[i];

	return b;
}

void Create_Array()
{
	n = 0;
	cout << "How mach elements to generate: ";

	while (n < 1 || n > 10000)
	{
		cin >> n;
		if (n < 1 || n >10000) cout << "Invalid value. Retry: ";
	}

	if (arr != NULL)
		delete[] arr;

	arr = new int[n];

	srand(time(NULL));

	for (int i = 0; i < n; i++)
		arr[i] = rand() % 100;

}

void sorting_bubble()
{
	compares = 0;
	changes = 0;
	int* b = copy_of_array();
	int temp;

	cout << endl << "Bubble sort: " << endl;

	for (int i = 0; i < n; i++)
		for (int j = n - 1; j > i; j--)
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

void inserts_sort()
{
	compares = 0;
	changes = 0;
	int* b = copy_of_array();
	int temp = 0;
	int i = 0;
	int j = 0;
	cout << endl << "Insertions sort" << endl;

	for (i = 1; i < n; i++)
	{
		temp = b[i];
		j = i - 1;
		compares++;

		while (j > -1 && temp < b[j])
		{
			b[j + 1] = b[j];

			if (j != i - 1) // произошла перестановка 
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

void choice_sort()
{
	int* b = copy_of_array();
	int temp = 0;
	int	i = 0;
	int	j = 0;
	int	k = 0;

	compares = 0;
	changes = 0;

	cout << endl << "Sort by choice" << endl;

	for (i = 0; i < n; i++)
	{
		k = i;
		temp = b[i];

		for (j = i + 1; j < n; j++)
		{
			if (b[j] < temp)
			{
				k = j;
				temp = b[j];
			}
			compares++;
		}

		if (b[i] == temp) //если перестановок не было
			changes--;

		b[k] = b[i];
		b[i] = temp;
		changes++;
	}

	Print(b);

	cout << endl << "Number of comparisons: " << compares << endl
		<< "Number of changes: " << changes << "" << endl;

	delete[] b;
}

void sorting_shell()
{
	int* b = copy_of_array();
	int temp = 0, i = 0, j = 0, k = 0;
	int t = (log(n) / log(2) - 1); // число шагов группировки
	int h[] = { 1, 3, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8194 };

	cout << endl << "Shell sort" << endl;

	for (int m = t - 1; m > -1; m--)
	{
		k = h[m];

		for (i = k; i < n; i++)
		{
			temp = b[i];
			j = i - k;
			compares++;

			while (j > -1 && temp < b[j])
			{
				b[j + k] = b[j];

				if (j != i - k) //ЕСЛИ ПРОИЗОШЛА ПЕРЕСТАНОВКА ВО ВНУТРЕННЕМ ЦИКЛЕ
					changes++;

				j = j - k;
				compares++;
			}

			if (b[j + 1] == temp) //ЕСЛИ ПЕРЕСТАНОВОК НЕ БЫЛО
				changes--;

			b[j + k] = temp;
			changes++;
		}
	}
	Print(b);

	cout << endl << "Number of comparisons: " << compares << endl
		<< "Number of changes: " << changes << "" << endl;
	delete[] b;
	compares = 0;
	changes = 0;
}

void sorting_quick(int left, int right, int* b)
{
	int i, j, sred, temp;

	i = left;
	j = right;

	if (b == arr)
		b = copy_of_array();

	sred = b[(left + right) / 2];

	cout << endl << "Quick sort" << endl;

	do
	{
		compares++;
		while (b[i] < sred)
		{
			i++;
			compares++;
		}

		compares++;

		while (b[j] > sred)
		{
			j--;
			compares++;
		}

		compares++;

		if (i <= j)
		{
			temp = b[i];
			b[i] = b[j];
			b[j] = temp;
			i++; j--;
			changes++;
		}

		compares++;
	} while (i < j);

	compares++;

	if (left < j)
		sorting_quick(left, j, b);

	compares++;

	if (i < right)
		sorting_quick(i, right, b);

	if (left == 0 && right == (n - 1)) {
		Print(b);
		cout << endl << "Number of comparisons: " << compares << endl
			<< "Number of changes: " << changes << "" << endl;
		delete[] b;
		compares = 0;
		changes = 0;
	}
}

void sito(int al, int ar, int* b) {
	int i = al;
	int	j = 2 * al;
	int	x = b[al];

	compares++;

	if ((j < ar) && (b[j + 1] < b[j]))
		j++;

	compares++;

	while ((j <= ar) && (b[j] < x))
	{
		b[i] = b[j];
		i = j;
		j = 2 * j;
		compares++;

		if ((j < ar) && (b[j + 1] < b[j]))
			j++;

		compares++;
	}

	b[i] = x;
	changes++;

	Print(b);
}

void sorting_pyramidal()
{
	int* b = copy_of_array(); //СОЗДАЕМ КОПИЮ ИСХОДНОГО МАССИВА
	int left = (n / 2);
	int right = n - 1; // ОПРЕДЕЛЕНИЕ ГРАНИЦ ПРАВОЙ ПОЛОВИНЫ МАССИВА
	int temp;

	compares++;

	cout << endl << "Piramidal sort" << endl;

	while (left > 0) // построение пирамиды
	{
		left--;
		sito(left, right, b);
		compares++;
	}

	compares++;

	while (right > 0)// сортировка
	{
		changes++;
		temp = b[0]; 
		b[0] = b[right]; 
		b[right] = temp;
		right--;

		sito(left, right, b);
		compares++;
	}

	Print(b);

	cout << endl << "Number of comparisons: " << compares << endl
		<< "Number of changes: " << changes << "" << endl;

	delete[] b;
	compares = 0; changes = 0;

}

int main()
{
	setlocale(LC_ALL, "rus");

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
			<< "Shell sort..................................4" << endl
			<< "Quick sort..................................5" << endl
			<< "Piramidal sort..............................6" << endl
			<< "Update array................................7" << endl
			<< "Exit........................................8" << endl << endl
			<< "Enter the number: ";
		cin >> c;

		while ((c < 0) || (c > 8))
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
			inserts_sort();
			break;
		case 3:
			Print(arr);
			choice_sort();
			break;
		case 4:
			Print(arr);
			sorting_shell();
			break;
		case 5:
			Print(arr);
			sorting_quick(0, n - 1, arr);
			break;
		case 6:
			Print(arr);
			sorting_pyramidal();
			break;
		case 7:
			Create_Array();
			break;
		case 8:
			break;
		}
	}

	delete[] arr;
	return 0;
}
