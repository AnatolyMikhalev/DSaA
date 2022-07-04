//     –еализовать линейный динамический двунаправленный список списков
//		Х	полный проход по всей структуре
//		Х	поиск заданного элемента
//		Х	добавление нового элемента в массив с пустым св€занным списком
//		Х	добавление нового элемента в св€занный список
//		Х	удаление элемента из св€занного списка
//		Х	удаление элемента из базового массива


#include <iostream>
#include <string>

using namespace std;

struct SubList
{
	string Data;
	SubList* next;
};

struct MainList
{
	MainList* next;
	SubList* FirstSub;
} *pHead;

inline void initMainList() {
	pHead = new MainList();
	pHead->next = pHead;
	pHead->FirstSub = NULL;
}

int isMainListEmpty()
{
	if (pHead->next == pHead)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isSubListEmpty(SubList* FirstSub)
{
	if (FirstSub->next == FirstSub)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void pushSublist(string data, SubList* FirstSub)
{
	SubList* temp;
	SubList* curr;
	string elem;
	int choice = 0;

	temp = new SubList();
	temp->Data = data;

	cout << "Enter the element of the list where you want to add the new item: ";
	cin >> elem;

	cout << "Insert before or after element? 0 - before; 1 - after: ";
	cin >> choice;

	if (choice == 1)
	{
		curr = FirstSub->next;

		while (curr->next != FirstSub && curr->Data != elem)
			curr = curr->next;

		temp->next = curr->next;
		curr->next = temp;
	}
	else if (choice == 0)
	{
		curr = FirstSub;

		if (isSubListEmpty(FirstSub))
		{
			cout << "Operation \"insert before\" cannot be applied to an empty list" << endl;
		}
		else
		{
			while (curr->next != FirstSub && curr->next->Data != elem)
				curr = curr->next;

			temp->next = curr->next;
			curr->next = temp;
		}
	}
}

void pushInMainEmptySublist(string data)
{
	MainList* temp;
	MainList* curr;
	string elem;
	int choice = 0;

	temp = new MainList();
	temp->FirstSub = new SubList();
	temp->FirstSub->Data = "";
	temp->FirstSub->next = temp->FirstSub;

	cout << "Enter the name of the header of the list where you want to add the new item: ";
	cin >> elem;

	cout << "Insert before or after list? 0 - before; 1 - after: ";
	cin >> choice;

	if (choice == 1)
	{
		curr = pHead->next;

		while (curr->next != pHead && curr->FirstSub->next->Data != elem)
			curr = curr->next;

		temp->next = curr->next;
		curr->next = temp;

		pushSublist(data, temp->FirstSub);
	}
	else if (choice == 0)
	{
		if (isMainListEmpty())
		{
			cout << "Operation \"insert before\" cannot be applied to an empty Main list" << endl;
		}
		else
		{
			curr = pHead;

			while (curr->next != pHead && curr->next->FirstSub->next->Data != elem)
				curr = curr->next;

			temp->next = curr->next;
			curr->next = temp;

			pushSublist(data, temp->FirstSub);
		}
	}
}

void pushInMain(string data)
{
	MainList* curr;

	string elem, head;
	int choice = 0;

	curr = pHead->next;

	cout << "Enter the name of the header of the list where you want to add the new item: ";
	cin >> head;

	while ((curr->next != pHead) && (curr->FirstSub->next->Data != head))
		curr = curr->next;

	if (curr->next == pHead && curr->FirstSub == nullptr)
		cout << "Such list doesn't exist" << endl;
	else
		pushSublist(data, curr->FirstSub);
}

void pushElem()
{
	string data, elem;
	int choice = 0;

	cout << "Enter item: ";
	cin >> data;

	cout << "Insert item into empty linked list? 0 - no; 1 - yes: ";
	cin >> choice;

	if (choice == 1)
	{
		pushInMainEmptySublist(data);
	}
	else if (choice == 0)
	{
		pushInMain(data);
	}
}

void popElemFromSublist(SubList* FirstSub)
{
	SubList* temp = FirstSub->next;
	SubList* temp1 = FirstSub;
	string data;

	cout << "Enter the item of the list which you want to erase: ";
	cin >> data;

	while (temp->Data != data && temp->next != FirstSub)
	{
		temp = temp->next;
		temp1 = temp1->next;
	}

	if (temp->Data != data)
		cout << "Such element does not exists"<<endl;
	else
	{
		temp1->next = temp->next;
		temp->Data = "";
		temp->next = NULL;
		delete temp;
	}
}

void popElem()
{
	MainList* curr = pHead->next;
	MainList* prevCurr = pHead;

	string head;

	cout << "Enter the name of the header of the list where you want to erase the item: ";
	cin >> head;

	while ((curr->next != pHead) && (curr->FirstSub->next->Data != head))
	{
		curr = curr->next;
		prevCurr = prevCurr->next;
	}

	if (curr->next == pHead && curr->FirstSub == nullptr)
		cout << "Such list doesn't exist" << endl;
	else
	{
		popElemFromSublist(curr->FirstSub);

		if (isSubListEmpty(curr->FirstSub))
		{
			prevCurr->next = curr->next;
			curr->FirstSub->Data = "";
			curr->FirstSub->next = NULL;
			curr->FirstSub = NULL;
			curr->next = NULL;
			delete curr;
		}
	}
}

void popList()
{
	MainList* curr = pHead->next;
	MainList* prevCurr = pHead;

	string head;

	cout << "Enter the name of the header of the list where you want to erase the item: ";
	cin >> head;

	while ((curr->next != pHead) && (curr->FirstSub->next->Data != head))
	{
		curr = curr->next;
		prevCurr = prevCurr->next;
	}

	if (curr->next == pHead && curr->FirstSub == nullptr)
		cout << "Such list doesn't exist" << endl;
	else
	{
		SubList* temp = curr->FirstSub->next;
		SubList* temp1 = curr->FirstSub;

		while (temp1->next != curr->FirstSub)
		{
			temp1->next = temp->next;
			temp->Data = "";
			temp->next = NULL;
			delete temp;

			temp = temp1->next;
		}

		if (isSubListEmpty(curr->FirstSub))
		{
			prevCurr->next = curr->next;
			curr->FirstSub->Data = "";
			curr->FirstSub->next = NULL;
			curr->FirstSub = NULL;
			curr->next = NULL;
			delete curr;
		}
	}
}

void printSubList(MainList* CurrMain)
{
	SubList* curr = CurrMain->FirstSub;

	if (isSubListEmpty(curr))
		cout << "SubList is empty" << " ";
	else
	{
		do
		{
			cout << curr->Data << " ";
			curr = curr->next;
		} while (curr != CurrMain->FirstSub);
	}
	cout << endl;
}

void printMainList()
{
	int choice = -1;

	if (isMainListEmpty())
		cout << "Main list is empty" << endl;
	else
	{
		MainList* CurrMain;

		CurrMain = pHead->next;
		while (CurrMain != pHead)
		{
			printSubList(CurrMain);
			CurrMain = CurrMain->next;
		}
		cout << endl;
	}
}

int main()
{
	char a;
	char insert;
	int  c;
	string data;

	a = '0';

	initMainList();

	while (a != 'q') {

		cout << "--------------------------------------" << endl;
		cout << "Check for empty......................1" << endl;
		cout << "Add element..........................2" << endl;
		cout << "Delete element.......................3" << endl;
		cout << "Delete SubList.......................4" << endl;
		cout << "Print list...........................5" << endl;
		cout << "--------------------------------------" << endl;

		cin >> c;

		if (c < 1 || c > 6)
		{
			cout << "Incorrect value" << endl;
		}
		else
		{
			switch (c)
			{
			case 1:
				if (isMainListEmpty())
					cout << "List is empty" << endl;
				else
					cout << "List isn't empty" << endl;
				break;
			case 2:
				pushElem();
				break;
			case 3:
				if (isMainListEmpty())
					cout << "List is empty" << endl;
				else
					popElem();
				break;
			case 4:
				if (isMainListEmpty())
					cout << "List is empty" << endl;
				else
				{
					popList();
				}
				break;
			case 5:
				printMainList();
				break;
			}
		}
	}
}
