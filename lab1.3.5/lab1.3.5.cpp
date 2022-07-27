//6.	Реализовать линейный динамический список со стандартным набором операций.
//		•	добавить глобальную ссылочную переменную для хранения адреса вершины стека
//		•	в начале главной программы создать пустой вспомогательный список(стек)
//		•	в основное меню добавить возможность просмотра вспомогательного списка(стека)
//		•	изменить процедуру удаления элемента из основного списка, заменив операцию освобождения памяти операциями добавления удаленного элемента во вспомогательный список(стек)
//		•	добавить обычную процедуру вывода вспомогательного списка(стека)

#include <iostream>
#include <string>

using namespace std;

struct node
{
	string Data;
	node* next;
} *pHead, * pStack;

int queue_empty(node* pHead)
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

void push_after(string data, string elem)
{
	node* temp;
	node* curr;
	temp = new node();
	temp->Data = data;
	temp->next = NULL;
	curr = pHead;
	while (curr->Data != elem && curr->next != pHead)
		curr = curr->next;
	
	temp->next = curr->next;
	curr->next = temp;
}

void push_before(string data, string elem)
{

	if (queue_empty(pHead)) 
	{
		cout << "Operation \"insert before\" cannot be applied to an empty list" << endl;
	}
	else 
	{
		node* temp;
		node* curr;
		temp = new node();
		temp->Data = data;
		temp->next = NULL;
		curr = pHead;

		while (curr->next != NULL && curr->next->Data != elem)
			curr = curr->next;
		
		temp->next = curr->next;
		curr->next = temp;
		
	}

}

void pop(string data)
{
	int choice = -1;
	node* temp = pHead->next;
	node* temp1 = pHead;

	while ((choice != 0) && (choice != 1))
	{
		cout << "Is it really possible to delete an element or add it to the auxiliary stack?\n 0 - Delete with memory release\n 1 - Add to auxiliary stack\n\n Enter the command number: ";
		cin >> choice;
	}

	while (temp->Data != data && temp->next != pHead)
	{
		temp = temp->next;
		temp1 = temp1->next;
	}

	if (temp->Data != data)
		cout << "Such element does not exists";
	else
	{
		if (choice == 0)
		{
			temp1->next = temp->next;
			temp->Data = "";
			temp->next = nullptr;
			delete temp;
		}
		else
		{
			temp1->next = temp->next;
			temp->next = pStack->next;
			pStack->next = temp;
		}
	}
}

void print(node* temp)
{
	if (queue_empty(pHead))
	{
		cout << "List is empty" << endl;
	}
	else
	{
		while (temp != pHead)
		{
			cout << temp->Data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

void printStack(node* temp)
{
	if (queue_empty(pHead))
	{
		cout << "Stack is empty" << endl;
	}
	else
	{
		while (temp != NULL)
		{
			cout << temp->Data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

int main()
{
	pHead = new node();
	pHead->Data = "";
	pHead->next = pHead;
	pStack = new node();
	pStack->Data = "";
	pStack->next = NULL;
	char a;
	char insert;
	int  c;
	string data, elem;
	a = '0';
	while (a != 'q') {

		cout << "--------------------------------------" << endl;
		cout << "Check for empty......................1" << endl;
		cout << "Add element..........................2" << endl;
		cout << "Delete element.......................3" << endl;
		cout << "Print list...........................4" << endl;
		cout << "Print stack..........................5" << endl;
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
				if (queue_empty(pHead))
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
				if (queue_empty(pHead))
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
				print(pHead->next);
				break;
			case 5:
				printStack(pStack->next);
				break;
			}
		}
	}
}
