#include <stdio.h>
#include <iostream>
#include <string>
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
//
//void push_random(node** top, int N) {
//    srand(time(NULL));
//    int data;
//    for (int i = 0; i < N; i++) {
//        data = rand() % 99 + 1;
//        push(top, data);
//    }
//
//}
void pop(node** pFirst) {
    if (queue_empty(*pFirst))
    {
        cout << "Queue is empty" << endl;
    }
    else
    {
        node* temp = *pFirst;
        *pFirst = temp->next;
        delete temp;
    }

}

void print(node* pFirst) {
    node* temp = pFirst;
    while (temp != NULL)
    {
        cout << temp->Data << " ";
        temp = temp->next;
    }
    cout << endl;
}

/*bool getNumber(int* i)
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        string str;
        cin >> str;
        for (char c : str)
        {
            if (c < '0' || c >'9')
            {
                std::cout << "incorrect input\nTry again\n->";
                flag = true;
                break;
            }
        }

        if (flag == false)
        {
            try
            {
                *i = stoi(str);
            }
            catch (out_of_range)
            {
                cout << "�������� ����\n������� ������� ��������\n��������� ����\n->";
                flag = true;
            }

        }
    }
    return flag;
}*/

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
    a = '0';
    while (a != 'q') {

        cout << "Check for empty......................1" << endl;
        cout << "Add element..........................2" << endl;
        cout << "Delete element.......................3" << endl;
        cout << "Print queue..........................4" << endl;

        b = 1 + rand() % 100;

        cin >> c;

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
            cin >> b;
            push(&pFirst, &pLast, b);
            break;
        case 3:
            pop(&pFirst);
            break;
        case 4:
            print(pFirst);
            break;
        }
    }
}