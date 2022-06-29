//		Построение и обход идеально сбалансированных двоичных деревьев.
//		Реализовать программу, выполняющую следующий набор операций :
//		•	построение идеально сбалансированного двоичного дерева с заданным числом вершин
//		•	построчный вывод дерева на основе процедуры обхода в прямом порядке
//		•	построчный вывод дерева на основе процедуры обхода в симметричном порядке
//		•	построчный вывод дерева на основе процедуры обхода в обратно - симметричном порядке


#include <iostream>
#include <string>

using namespace std;

int N; //количество вершин в дереве

struct Tp 
{
	int value;
	Tp* Left;
	Tp* Right;
} *pRoot;

struct Stack 
{
	int level;			//уровень вершины
	Tp* ptrNode;		//указатели на пройденную вершину дерева
	Stack* next;		//указатели на следующий элемент стека
} *sp;

void initStack(Tp* pRoot) 
{
	sp = new Stack;
	sp->ptrNode = pRoot;
	sp->level = -1;
	sp->next = NULL;
}

bool isStackEmpty() 
{
	if (sp->level < 0) return 1;
	else return 0;
}

Tp* AddNodes(Tp* pCurrent, int aN)
{
	Tp* pTemp;
	int Nl, Nr;
	if (aN == 0)		// если нет вершин для размещения
		return NULL;	// формируем пустую ссылку
	else
	{
		Nl = aN / 2; //число вершин слева
		Nr = aN - Nl - 1; //число вершин справа
		pTemp = new Tp; //создаем корень поддерева, выделяем память
		pTemp->value = rand() % 100; //заносим в информационную часть случайное целое число в интервале от 0 до 99
		pTemp->Left = AddNodes(pTemp->Left, Nl); // уходим на создание левого поддерева
		pTemp->Right = AddNodes(pTemp->Right, Nr);
		pCurrent = pTemp;
		return pTemp; //возвращаем адрес созданного корня
	}
}


void Forward(Tp* pCurrent, int level)
{
	if (pCurrent != NULL)
	{
		string str;

		for (int i = 0; i < level; i++) //обработка корневой вершины
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Forward(pCurrent->Left, level + 1); //обработка всех левых поддеревьев

		Forward(pCurrent->Right, level + 1); //обработка всех правых поддеревьев
	}
}

void Symmetric(Tp* pCurrent, int level)
{
	if (pCurrent != NULL)
	{
		string str;

		Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев

		for (int i = 0; i < level; i++) //обработка корневой вершины 
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
	}
}

void Back_Symmetric(Tp* pCurrent, int level)
{
	if (pCurrent != NULL)
	{
		string str;

		Back_Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев

		for (int i = 0; i < level; i++) //обработка корневой вершины
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Back_Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
	}
}

void Nonrecursive() 
{
	initStack(pRoot);
	Tp* pCurrent = pRoot; //начинаем с корневой вершины дерева
	bool Stop = false;
	int level = 0;

	while (!Stop) 
	{
		while (pCurrent != NULL) 
		{
			Stack* item = new Stack; 
			item->level = level;
			item->ptrNode = pCurrent;
			item->next = sp;
			sp = item;

			pCurrent = pCurrent->Left;
			level++;
		}

		if (isStackEmpty())
			Stop = true;
		else					//обработка и вывод вершины
		{ 
			string str = "";			

			level = sp->level;
			pCurrent = sp->ptrNode;

			for (int i = 0; i < level; i++)			//обработка корневой вершины pCurrent
				str += "     ";

			cout << " " << str << (pCurrent->value) << "\n";

			sp = sp->next;

			pCurrent = pCurrent->Right;
			level++;
		}
	}
}

void Clean(Tp* pCurrent) {
	if (pCurrent != NULL)
	{
		Clean(pCurrent->Left);
		Clean(pCurrent->Right);
		delete pCurrent;
	}
};

int main()
{
	srand(time(NULL));
	cout << "Randomizer initialized" << endl;

	while (true) {

		cout << "How many nodes to generate in a perfectly balanced tree: " << endl;

		cin >> N;

		if (N < 1 || N > 99)
			cout << "Incorrect value" << endl;
		else
		{
			pRoot = AddNodes(pRoot, N);

			cout << "\n Line output in direct order:\n\n";
			Forward(pRoot, 0);

			cout << "\n Line output in symmetric order:\n\n";
			Symmetric(pRoot, 0);

			cout << "\n Line output in reverse order:\n\n";
			Back_Symmetric(pRoot, 0);

			cout << "\n Line output in nonrecurcive order:\n\n";
			Nonrecursive();

			Clean(pRoot);
		}
	}
}
