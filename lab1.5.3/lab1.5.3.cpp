//			Реализовать программу, выполняющую следующий набор операций с двоичными деревьями :
//			•	поиск вершины с заданным значением информационной части
//			•	добавление левого или правого потомка для заданной вершины
//			•	построчный вывод дерева с помощью основных правил обхода
//			•	уничтожение всего дерева


#include <iostream>
#include <string>

using namespace std;

int N; //количество вершин в дереве

bool founded = false; //признак успешности поиска, глобальная переменная

struct Tp
{
	int value; //описание информационной части
	Tp* Left; //переменная-указатель на левый элемент
	Tp* Right; //переменная-указатель на правый элемент
} *pRoot, *pParent;


void Forward(Tp* pCurrent, int level) //обход в прямом направлении
{
	if (pCurrent != NULL) {
		string str; //обработка корневой вершины pCurrent
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Forward(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев

		Forward(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
	}
}

void Symmetric(Tp* pCurrent, int level) //симметричный обход
{
	if (pCurrent != NULL)
	{
		Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев

		string str; //обработка корневой вершины pCurrent
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
	}
}

void Back_Symmetric(Tp* pCurrent, int level)//обратно-симметричный обход
{
	if (pCurrent != NULL)
	{
		Back_Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев

		string str; //обработка корневой вершины
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Back_Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
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

void Print_tree()
{
	cout << "\n Line output in direct order:\n\n";
	Forward(pRoot, 0);

	cout << "\n Line output in symmetric order:\n\n";
	Symmetric(pRoot, 0);

	cout << "\n Line output in reverse order:\n\n";
	Back_Symmetric(pRoot, 0);
}

void Find(Tp* pCurrent, int elem)
{
	//    founded = false;
	if (!founded)
		if (pCurrent != NULL)
		{
			if (pCurrent->value == elem)
			{
				founded = true;
				pParent = pCurrent;
			}
			else {
				Find(pCurrent->Left, elem); // поиск в левом поддереве
				Find(pCurrent->Right, elem); // поиск в  правых поддереве
			}
		}
}

Tp* Add_Tp(Tp* pTemp, int value) {
	pTemp = new Tp;
	pTemp->Left = NULL;
	pTemp->Right = NULL;
	pTemp->value = value;
	return pTemp;
}

void Add_elem() {
	int value, n;

	if (pRoot != NULL)
	{
		cout << endl << "Enter the value of the tree-point where you want to add the new item: ";
		cin >> value;
		founded = false;
		Find(pRoot, value); 

		if (founded)
		{
			founded = false;
			if (pParent->Left == NULL || pParent->Right == NULL)
			{
				cout << endl << "Enter the value you want to assign to the tree-point: ";
				cin >> value;
			}
			if (pParent->Left == NULL && pParent->Right == NULL)
			{
				cout << endl << "Tree-point doesn't have any child. Which tree-point to add (1 - left-child; 2 - right-child: ";
				cin >> n;

				while ((n != 1) && (n != 2))
				{
					cout << " Incorrect value. Repeat enter: "; 
					cin >> n;
				}
				if (n == 1)
				{
					pParent->Left = Add_Tp(pParent->Left, value);
					cout << " tree-point successfully added as left-child of parent tree-point" << endl;
				}
				if (n == 2)
				{
					pParent->Right = Add_Tp(pParent->Right, value);
					cout << " tree-point successfully added as right-child of parent tree-point" << endl;
				}
			}
			else if (pParent->Left == NULL)
			{
				pParent->Left = Add_Tp(pParent->Left, value);
				cout << " tree-point successfully added as left-child of parent tree-point" << endl;
			}
			else if (pParent->Right == NULL)
			{
				pParent->Right = Add_Tp(pParent->Right, value);
				cout << " tree-point successfully added as right-child of parent tree-point" << endl;
			}
			else
			{
				cout << " Adding is impossible: parent tree-point already has who children  \n"; 
				return;
			}
			Print_tree();
		}

		else cout << " parent tree-point '" << value << "' not found \n";
	}
	else 
	{
		pRoot = new Tp; 
		cout << endl << "Enter the value of the root tree-point: ";
		cin >> value;

		pRoot->Left = NULL;
		pRoot->Right = NULL;
		pRoot->value = value;
		cout << " Root tree-point '" << pRoot->value << "' successfully created \n";
	}
}

int main()
{
	pRoot = NULL;
	int c = -1;

	while (true)
	{

		cout << "---------------------------------------" << endl;
		cout << "Search for the node...................1" << endl;
		cout << "Add element...........................2" << endl;
		cout << "Print tree............................3" << endl;
		cout << "Delete tree...........................4" << endl;
		cout << "---------------------------------------" << endl;
		cout << endl << "Enter the number: ";
		cin >> c;
		cout << endl;

		if (c < 1 || c > 4)
		{
			cout << "Incorrect value" << endl;
		}
		else
		{
			switch (c)
			{
			case 1:
				int elem;
				cout << endl<< "Enter element : ";
				cin >> elem;

				founded = false;
				Find(pRoot, elem);
				if (founded)
				{
					cout << " Tree-point '" << elem << "' found"<<endl;
					founded = false;
				}
				else
					cout << " Tree-point '" << elem << "' not found" << endl;
				break;
			case 2:
				Add_elem();
				break;
			case 3:
				Print_tree();
				break;
			case 4:
				Clean(pRoot);
				pRoot = NULL;
				break;
			}
		}
	}
}
