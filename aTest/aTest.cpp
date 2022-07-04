//			Построение и обработка двоичных деревьев поиска.Реализовать программу, выполняющую следующий набор операций с деревьями поиска :
//			•	поиск вершины с заданным значением ключа с выводом счетчика числа появлений данного ключа
//			•	добавление новой вершины в соответствии со значением ее ключа или увеличение счетчика числа появлений
//			•	построчный вывод дерева в наглядном виде с помощью обратно - симметричного обхода
//			•	вывод всех вершин в одну строку по порядку следования ключей с указанием для каждой вершины значения ее счетчика появлений
//			•	удаление вершины с заданным значением ключа



#include <iostream>
#include <string>

using namespace std;

int N;

bool founded = false;

struct Tp
{
	int value;
	int counter;
	Tp* Left;
	Tp* Right;
} *pRoot = NULL, * pParent = NULL;

void Symmetric(Tp* pCurrent)
{
	if (pCurrent != NULL)
	{
		Symmetric(pCurrent->Left);

		cout << pCurrent->value << "(" << pCurrent->counter << "); ";

		Symmetric(pCurrent->Right);
	}
}

void Back_Symmetric(Tp* pCurrent, int level)
{
	if (pCurrent != NULL)
	{
		string str;

		Back_Symmetric(pCurrent->Right, level + 1);

		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Back_Symmetric(pCurrent->Left, level + 1);
	}
}

void Clean(Tp* pCurrent)
{
	if (pCurrent != NULL)
	{
		Clean(pCurrent->Left);
		Clean(pCurrent->Right);
		delete pCurrent;
	}
};

Tp* Find(int elem)
{
	Tp* pCurrent = pRoot;
	pParent = NULL;
	bool Stop = false;

	while ((pCurrent != NULL) && (!Stop))
	{
		if (elem < pCurrent->value)
		{
			pParent = pCurrent;
			pCurrent = pCurrent->Left;
		}
		else if (elem > pCurrent->value)
		{
			pParent = pCurrent;
			pCurrent = pCurrent->Right;
		}
		else
			Stop = true;
	}
	return pCurrent;
}

Tp* Add_Tp(Tp* pTemp, int value)
{
	pTemp = new Tp;
	pTemp->Left = NULL;
	pTemp->Right = NULL;
	pTemp->value = value;
	return pTemp;
}

Tp* AddRecursive(Tp* pCurrent, int value)
{
	if (pCurrent == NULL)
	{
		pCurrent = new Tp;
		pCurrent->value = value;
		pCurrent->Left = pCurrent->Right = NULL;
		pCurrent->counter = 1;
	}
	else
	{
		if (value < pCurrent->value)
			pCurrent->Left = AddRecursive(pCurrent->Left, value);
		else if (value > pCurrent->value)
			pCurrent->Right = AddRecursive(pCurrent->Right, value);
		else
			pCurrent->counter++;
	}
	return pCurrent;
}

void AddNonRecursive(int value)
{
	if (pRoot == NULL)
	{
		pRoot = new Tp;
		pRoot->Left = pRoot->Right = NULL;
		pRoot->value = value;
		pRoot->counter = 1;
	}
	else
	{
		Tp* pParent = NULL;
		Tp* pCurrent = pRoot;

		while (pCurrent != NULL)
		{
			pParent = pCurrent;

			if (value < pCurrent->value)
				pCurrent = pCurrent->Left;
			else if (value > pCurrent->value)
				pCurrent = pCurrent->Right;
			else
			{
				pCurrent = NULL;
				pCurrent->counter++;
			}
		}
		if (value < pParent->value)
		{
			pCurrent = new Tp;
			pCurrent->Left = NULL;
			pCurrent->Right = NULL;
			pCurrent->counter = 1;
			pCurrent->value = value;
			pParent->Left = pCurrent;
		}
		else if (value > pParent->value)
		{
			pCurrent = new Tp;
			pCurrent->Left = pCurrent->Right = NULL;
			pCurrent->counter = 1;
			pCurrent->value = value;
			pParent->Right = pCurrent;
		}
	}
}

void Add_elem()
{
	int value, n;
	cout << endl << "Enter key of tree-point at new tree-point: ";
	cin >> value;
	cout << endl << "Which method of adding to use?\n 1 - Recursive method\n 2 - Nonrecursive method: ";
	cin >> n;
	while ((n != 1) && (n != 2))
	{
		cout << "Incorrect value. Retry: ";
		cin >> n;
	}
	if (n == 1)
		pRoot = AddRecursive(pRoot, value);
	if (n == 2)
		AddNonRecursive(value);
	cout << "Tree-point with a key '" << value << "' added... \n";
}

void Create_Random_Tree()
{
	int num = -1;

	while (num <= 0)
	{
		cout << "How many tree-points to generate: ";
		cin >> num;

		if (num <= 0)
			cout << "Incorrect value. Retry.";
		else
		{
			for (int i = 0; i < num; i++)
				pRoot = AddRecursive(pRoot, rand() % 100);
			cout << "Binary search tree with number of tree-points '" << num << "' created" << endl;
		}
	}
}

Tp* Changer(Tp* p)
{
	if (p->Right != NULL)
		p = Changer(p->Right);
	return p;
};

Tp* DeleteNode(Tp* pCurrent, int value)
{
	if (pCurrent == NULL)
	{
		//cout << "Tree-point doesn't found"<<endl;  
	}
	else if (value < pCurrent->value)
		pCurrent->Left = DeleteNode(pCurrent->Left, value);

	else if (value > pCurrent->value)
		pCurrent->Right = DeleteNode(pCurrent->Right, value);

	else
	{
		if (pCurrent->counter > 1)
			pCurrent->counter--;

		else
		{
			Tp* pTemp = pCurrent;

			if (pTemp->Right == NULL)
				pCurrent = pTemp->Left;

			else if (pTemp->Left == NULL)
				pCurrent = pTemp->Right;

			else if ((pTemp->Right == NULL) && (pTemp->Left == NULL))
				pCurrent = NULL;

			else
			{
				Tp* p = Changer(pCurrent->Left);
				p = Find(p->value);
				cout << "Value of changer tree-point is: " << p->value << endl << "Value of Parent tree-point is: " << pParent->value << endl;

				pParent->Left = p->Left;
				pCurrent->value = p->value; //ЗАМЕНЯЕМ ИНФ. ЧАСТЬ УДАЛЯЕМОЙ ВЕРШИНЫ
				pCurrent->Left = DeleteNode(pCurrent->Left, p->value);
				pTemp = p;
				return pCurrent;

			}
			delete pTemp;
		}
	}
	return pCurrent;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	cout << "Randomizer initialized" << endl;

	int c = -1;
	Tp* pTemp;

	while (true)
	{
		cout << "--------------------------------------------------" << endl;
		cout << "Create a randon-tree.............................1" << endl;
		cout << "Add element......................................2" << endl;
		cout << "Search for the tree-point........................3" << endl;
		cout << "Print the tree in back-symmetric form............4" << endl;
		cout << "Print all tree-points in ascenting order.........5" << endl;
		cout << "Delete tree-point................................6" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl << "Enter the number: ";
		cin >> c;
		cout << endl;

		if (c < 1 || c > 6)
		{
			cout << "Incorrect value" << endl;
		}
		else
		{
			switch (c)
			{
			case 1:
				Create_Random_Tree();
				break;
			case 2:
				Add_elem();
				break;
			case 3:
				int elem;
				cout << endl << "Enter the key you want to find: ";
				cin >> elem;
				pTemp = Find(elem);
				if (pTemp != NULL)
					cout << "Tree-point with a key '" << elem << "' found. Number of appearances: " << pTemp->counter << endl;
				else
					cout << "Tree-point with a key '" << elem << "' not found" << endl;
				break;
			case 4:
				if (pRoot != NULL)
				{
					cout << endl << "Print tree in ascending order" << endl << endl;;
					Symmetric(pRoot);
					cout << endl;
				}
				else
					cout << "Tree is empty" << endl << endl;
				break;
			case 5:
				if (pRoot != NULL)
				{
					cout << endl << "Print tree in back-symmetric order: " << endl << endl;
					Back_Symmetric(pRoot, 0);
					cout << endl;
				}
				else
					cout << " Tree is empty" << endl << endl;
				break;
			case 6:
				int value;
				cout << endl << "Enter the key of the tree-point you want to delete: ";
				cin >> value;
				pRoot = DeleteNode(pRoot, value);
				cout << "Tree-point with a key '" << value << "' deleted..." << endl;
				Back_Symmetric(pRoot, 0);
				break;
			}
		}
	}
}
