﻿//     Реализовать линейный динамический двунаправленный список со следующим набором операций :
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
} *pHead, *pStack;

int list_empty(node* pHead)
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

void push(string data, string elem)
{
    node* temp;
    node* curr;
    temp = new node();
    temp->Data = data;
    temp->next = NULL;
    curr = pHead;
    while (curr->Data != elem && curr->next != NULL)
        curr = curr->next;
    if (curr->next == NULL)
    {
        temp->next = NULL;
        curr->next = temp;
    }
    else
    {
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

    while (temp->Data != data && temp->next != NULL)
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

void print(node* curr)
{
    if (list_empty(pHead))
    {
        cout << "List is empty" << endl;
    }
    else
    {
        node* head = curr;
        curr = curr->next;
        while (curr != head)
        {
            cout << curr->Data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
}

int main()
{
    pHead = new node();
    pHead->Data = "";
    pHead->next = pHead;
    pHead->prev = pHead;
    pStack = new node();
    pStack->Data = "";
    pStack->next = NULL;
    char a;
    int  c;
    string data, elem;
    a = '0';
    while (a != 'q') {

        cout << "Check for empty......................1" << endl;
        cout << "Add element..........................2" << endl;
        cout << "Delete element.......................3" << endl;
        cout << "Print list...........................4" << endl;
        cout << "Print stack..........................5" << endl;

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
                    if (list_empty(pHead))
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
                    push(data, elem);
                    break;
                case 3:
                    if (list_empty(pHead))
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
                    print(pStack->next);
                    break;
            }
        }
    }
}
