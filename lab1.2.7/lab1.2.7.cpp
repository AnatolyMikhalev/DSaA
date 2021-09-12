//Написать программу для моделирования работы очереди со случайным числом добавляемых и удаляемых элементов.
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

struct node
{
    char Data;
    node* next;
};

int queue_empty(node* pFirst) {
    if (pFirst == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(node** pFirst, node** pLast, char data) {
    node* temp;
    temp = new node();
    temp->Data = data;
    temp->next = NULL;
    if (queue_empty(*pFirst)) {
        *pFirst = temp;
        *pLast = temp;
    }
    else
    {
        (*pLast)->next = temp;
        *pLast = temp;
    }
}

void pop(node** pFirst) {
    if (queue_empty(*pFirst))
    {
        cout << "Queue is empty" << endl;
    }
    else
    {
        node* temp = *pFirst;
        *pFirst = temp->next;
        temp->Data = NULL;
        temp->next = nullptr;
        delete temp;
    }

}

void print(node* pFirst) {
    node* temp = pFirst;
    if (queue_empty(pFirst))
    {
        cout << "Queue is empty" << endl;
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

void modeling(node **pFirst, node **pLast) {
    cout << "\nQUEUE MODELING\n";
    char key = '\0';
    char symbol;
    int n, x; 
    cout << "Press <q> to quit the queue simulation mode\n";
    while (key != 'q') {
        Sleep(2);
        if (queue_empty(*pFirst)) x = 1; 
        else x = (rand() % 100 % 2 == 0);

        if (x == 1) {
            n = rand() % 3 + 1;

            if (_kbhit()) 
                key = _getch();
            if (key == 'q') break;
                cout << "\nGeneration and addition " << n << " item(s) to queue\n";
            Sleep(800);
            for (int i = 0; i < n; i++) {
                symbol = static_cast<char>(65 + rand() % 26);
                push(pFirst, pLast, symbol);
            }
        }
        else { 
            n = rand() % 4 + 1; 
//            n = rand() % 4 + 1;
            if (_kbhit()) 
                key = _getch(); 
            if (key == 'q') break;
            cout << "\nRemoval " << n << " item (s) from the queue...\n";
            Sleep(800);
            for (int i = 0; i < n; i++)
                if (!queue_empty(*pFirst))
                    pop(pFirst);
        }
        cout << "Press <q> to quit the queue simulation mode\n";
        if (_kbhit())
            key = _getch(); 
        if (key == 'q') break;
        cout << "Queue state: ";
        if (_kbhit()) key = _getch();
        print(*pFirst);
    }
}

int ft_input()
{
    string str;
    cin >> str;
    if (str.length() != 1)
    {
        return 9;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    node* pFirst = NULL;
    node* pLast = NULL;

    srand(time(NULL));
    cout << "Randomizer initialized" << endl;
    char a;
    int  b;
    int  c;
    char d;
    a = '0';
    while (a != 'q') {

        cout << "Check for empty......................1" << endl;
        cout << "Add element..........................2" << endl;
        cout << "Delete element.......................3" << endl;
        cout << "Print queue..........................4" << endl;
        cout << "Queue modeling.......................5" << endl;

        b = 1 + rand() % 100;

        cin >> c;

        if (c < 1 || c > 5) 
        {
            cout << "Incorrect value" << endl;
        }
        else
        {
            switch (c)
            {
            case 1:
                if (queue_empty(pFirst))
                {
                    cout << "Queue is empty" << endl;
                }
                else
                {
                    cout << "Queue isn't empty" << endl;
                }
                break;
            case 2:
                cout << "Enter element: ";
                cin >> d;
                push(&pFirst, &pLast, d);
                break;
            case 3:
                pop(&pFirst);
                break;
            case 4:
                print(pFirst);
                break;
            case 5:
                modeling(&pFirst, &pLast);
                break;
            }
        }
    }
}
