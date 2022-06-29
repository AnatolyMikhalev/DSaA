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

//ОПИСАНИЕ СТРУКТУРЫ ДЕРЕВА TreePoint
struct Tp {
	int value; //описание информационной части
	Tp* Left; //переменная-указатель на левый элемент
	Tp* Right; //переменная-указатель на правый элемент
} *pRoot; //глобальная переменная для корневой вершины.


Tp* AddNodes(Tp* pCurrent, int aN) { //ДОБАВЛЕНИЕ ВЕРШИН (ПОСТРОЕНИЕ ИСД)
	Tp* pTemp;
	int Nl, Nr;
	if (aN == 0)  // если нет вершин для размещения
		return NULL; // формируем пустую ссылку
	else {
		Nl = aN / 2; //число вершин слева
		Nr = aN - Nl - 1; //число вершин справа
		pTemp = new Tp; //создаем корень поддерева, выделяем память
		pTemp -> value = rand() % 100; //заносим в информационную часть случайное целое число в интервале от 0 до 99
		pTemp -> Left = AddNodes(pTemp->Left, Nl); // уходим на создание левого поддерева
		pTemp -> Right = AddNodes(pTemp->Right, Nr);
		pCurrent = pTemp;
		return pTemp; //возвращаем адрес созданного корня
	}
}


void Forward(Tp* pCurrent, int level) { //обход в прямом направлении
	if (pCurrent != NULL) {
		string str; //обработка корневой вершины pCurrent
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Forward(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
		Forward(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
	}
}

void Symmetric(Tp* pCurrent, int level) { //симметричный обход
	if (pCurrent != NULL) {
		Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев

		string str; //обработка корневой вершины pCurrent
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
	}
}

void Back_Symmetric(Tp* pCurrent, int level) {//обратный обход
	if (pCurrent != NULL) {
		Back_Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев

		string str; //обработка корневой вершины
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << pCurrent->value << "\n";

		Back_Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
	}
}

void Clean(Tp* pCurrent) {
	if (pCurrent != NULL) {
		Clean(pCurrent->Left);
		Clean(pCurrent->Right);
		delete pCurrent;
	}
};

int main()
{

	setlocale(LC_ALL, "Rus");
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
			cout << " ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДЕРЕВО С ЧИСЛОМ ВЕРШИН '" << N << "' СОЗДАНО\n";

			cout << "\n Line output in direct order:\n\n";
			Forward(pRoot, 0);

			cout << "\n Line output in symmetric order:\n\n";
			Symmetric(pRoot, 0);

			cout << "\n Line output in reverse order:\n\n";
			Back_Symmetric(pRoot, 0);

			Clean(pRoot);

		}
	}
}
