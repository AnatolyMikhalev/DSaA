//Реализовать программу для простейшего моделирования линейного списка с помощью массива

#include <stdio.h>;
#include <iostream>
#include <string>
#define SIZE 2

using namespace std;

int queue_empty(int N) {
    if (N == 0)
    {
        return 1;
    }
    else if (N != SIZE)
    {
        return 2;
    }
    else if (N == SIZE) {
        return 0;
    }
}

void push(int sp[], int& Last, int data, int& N) {
    if (N == 0)
    {
        sp[Last] = data;
        N++;
    }
    else
    {
        if (Last == SIZE - 1)
        {
            Last = 0;
        }
        else
        {
            Last++;
        }
        sp[Last] = data;
        N++;
    }
}

void pop(int* sp, int& First, int& N)
{
    if (queue_empty(N) == 1)
    {
        cout << "Queue is empty" << endl;
    }
    else
    {
        cout << "Removed - " << sp[First] << endl;
        sp[First] = 0;
        if (First == SIZE - 1) {
            First = 0;
        }
        else {
            First++;
        }
        N--;
    }
}

void print(int sp[], int First, int Last)
{
    int i = 0;
    while (First != Last)
    {
        cout << sp[First] << " ";
        if (First == 9) {
            First = 0;
        }
        else {
            First++;
        }
    }
    if (First == Last) {
        cout << sp[First] << " ";
    }
    cout << endl;
}

bool getNumber(int* i)
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
                std::cout << "Invalid entry \nRepeat entry\n->";
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
                cout << "Invalid entry \ntoo large value \nRepeat entry\n->";
                flag = true;
            }

        }
    }
    return flag;
}

void main()
{
    setlocale(LC_ALL, "Rus");
    int sp[SIZE];
    int First = 0;
    int Last = 0;
    int N = 0;
    char a;
    int b;

    while (true) {

        cout << "Check for empty......................1" << endl;
        cout << "Add element..........................2" << endl;
        cout << "Delete element.......................3" << endl;
        cout << "Print queue..........................4" << endl;

        cin >> a;
        if (a < '1' || a > '4')
            cout << "Incorrect value" << endl;
        else
        {
            switch (a)
            {
            case '1':
                if (queue_empty(N) == 0)
                {
                    cout << "Queue is full" << endl;
                }
                else if (queue_empty(N) == 1)
                {
                    cout << "Queue is empty" << endl;
                }
                else
                {
                    cout << "Queue isn't empty" << endl;
                }
                break;
            case '2':
                if (queue_empty(N) == 0)
                {
                    cout << "Queue is full" << endl;
                }
                else
                {
                    cout << "Enter element: ";
                    if (!getNumber(&b)) {
                        push(sp, Last, b, N);
                    }
                }
                break;
            case '3':
                pop(sp, First, N);
                break;
            case '4':
                print(sp, First, Last);
                break;
            }
        }
    }
}