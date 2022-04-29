//     Реализовать линейный динамический двунаправленный список со следующим набором операций :
//     •	просмотр списка в прямом и обратном направлениях
//     •	поиск заданного элемента в прямом и обратном направлениях
//     •	добавление элемента перед или после заданного
//     •	удаление заданного элемента

#include <iostream>
#include <string>

using namespace std;

struct node
{
	string Data;
	node* next;
	node* prev;
} *pHead;

int list_empty()
{
	if (pHead->next == pHead && pHead->prev == pHead)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void push_after(string data, string elem)
{
	node* temp;
	node* curr;
	temp = new node();
	temp->Data = data;
	curr = pHead;

	if (list_empty())
	{
		curr->prev = temp;
		curr->next = temp;
		temp->prev = curr;
		temp->next = curr;
	}
	else
	{
		while (curr->Data != elem && curr->next != pHead)
			curr = curr->next;
		if (curr->next == pHead)
		{
			temp->next = pHead;
			temp->prev = curr;
			curr->next = temp;
			pHead->prev = temp;
		}
		else
		{
			temp->next = curr->next;
			temp->prev = curr;
			curr->next->prev = temp;
			curr->next = temp;
		}
	}
}

void push_before(string data, string elem)
{
	node* temp;
	node* curr;
	temp = new node();
	temp->Data = data;
	curr = pHead;

	if (list_empty())
	{
		curr->prev = temp;
		curr->next = temp;
		temp->prev = curr;
		temp->next = curr;
	}
	else
	{
		while (curr->next != pHead && curr->next->Data != elem)
			curr = curr->next;
		if (curr->next == pHead)
		{
			temp->next = pHead;
			temp->prev = curr;
			curr->next = temp;
			pHead->prev = temp;
		}
		else
		{
			temp->next = curr->next;
			temp->prev = curr;
			curr->next->prev = temp;
			curr->next = temp;
		}
	}
}

void pop(string data)
{
	node* temp = pHead->next;

	while (temp->Data != data && temp->next != pHead)
	{
		temp = temp->next;
	}

	if (temp->Data != data)
		cout << "Such element does not exists";
	else
	{
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;

		temp->next = nullptr;
		temp->prev = nullptr;
		delete temp;
	}
}

void print()
{
	int choice = -1;
	node* curr;

	if (list_empty())
	{
		cout << "List is empty" << endl;
	}
	else
	{
		while ((choice != 0) && (choice != 1))
		{
			cout << "Print forward or reverse?\n 0 - forward\n 1 - reverse\n\n Enter the command number: ";
			cin >> choice;
		}
		switch (choice)
		{
			case 0:
				curr = pHead->next;
				while (curr != pHead)
				{
					cout << curr->Data << " ";
					curr = curr->next;
				}
				cout << endl;
				break;
			case 1:
				curr = pHead->prev;
				while (curr != pHead)
				{
					cout << curr->Data << " ";
					curr = curr->prev;
				}
				cout << endl;
				break;
		}
	}
}

int main()
{
	pHead = new node();
	pHead->Data = "";
	pHead->next = pHead;
	pHead->prev = pHead;
	char a;
	char insert;
	int  c;
	string data, elem;
	a = '0';
	while (a != 'q') {

		cout << endl;
		cout << "Check for empty......................1" << endl;
		cout << "Add element..........................2" << endl;
		cout << "Delete element.......................3" << endl;
		cout << "Print list...........................4" << endl;

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
				if (list_empty())
				{
					cout << "List is empty" << endl;
				}
				else
				{
					cout << "List isn't empty" << endl;
				}
				break;
			case 2:
				cout << "Enter element: ";
				cin >> data;
				cout << "After which element to insert: ";
				cin >> elem;
				cout << "Insert before or after element? 0 - before; 1 - after\n";
				cin >> insert;
				if (insert == '1')
					push_after(data, elem);
				else if (insert == '0')
					push_before(data, elem);
				break;
			case 3:
				if (list_empty())
				{
					cout << "List is empty" << endl;
				}
				else
				{
					cout << "Enter element: ";
					cin >> data;
					pop(data);
				}
				break;
			case 4:
				print();
				break;
			}
		}
	}
}
