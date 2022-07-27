//Реализовать программу, выполняющую стандартный набор операций с кольцевой очередью на основе массива

#include <stdio.h>;
#include <iostream>
#include <string>

using namespace std;

int queue_empty(int N) 
{
    if (N == 0)
    {
        return 1;
    }
    else if (N != 10)
    {
        return 2;
    }
    else if (N == 10) {
        return 0;
    }
}

void push(int sp[], int& Last, int data, int& N) {
    if (queue_empty(N) == 0) 
    {
        cout << "Очередь заполнена" << endl;
    }
    else if (N == 0) 
    {
        sp[Last] = data;
        N++;
    }
    else 
    {
        if (Last == 9) {
            Last = 0;
        }
        else {
            Last++;
        }
        sp[Last] = data;
        N++;
    }
}


void pop(int* sp, int& First, int& N) 
{
    if (queue_empty(N) == 1) {
        cout << "Очередь пуста" << endl;
    }
    else
    {
        cout << "Удалён - " << sp[First] << endl;
        sp[First] = 0;
        if (First == 9) {
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
                std::cout << "Неверный ввод\nПовторите ввод\n->";
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
                cout << "Неверный ввод\nслишком большое значение\nПовторите ввод\n->";
                flag = true;
            }

        }
    }
    return flag;
}

void main()
{
    setlocale(LC_ALL, "Rus");
    int sp[10];
    int First = 0;
    int Last = 0;
    int N = 0;

    while (true) {

        cout << "Проверка пустоты очереди............................1" << endl;
        cout << "Добавление элемента в вершину очереди...............2" << endl;
        cout << "Удаление элемента из начала очереди.................3" << endl;
        cout << "Вывод текущего состояния очереди на экран...........4" << endl;

        char a;
        int b;
        cin >> a;
        if (a < '1' || a > '4') {
            cout << "Неверное значение" << endl;
        }
        else {
            switch (a)
            {
            case '1':
                if (queue_empty(N) == 0)
                {
                    cout << "Очередь заполнена" << endl;
                }
                else if (queue_empty(N) == 1)
                {
                    cout << "Очередь пуста" << endl;
                }
                else
                {
                    cout << "Очередь не пуста" << endl;
                }
                break;
            case '2':
                cout << "Введите элемент: ";
                if (!getNumber(&b)) {
                    push(sp, Last, b, N);
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