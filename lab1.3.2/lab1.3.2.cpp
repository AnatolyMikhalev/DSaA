//Реализовать программу для простейшего моделирования линейного списка с помощью массива

#include <stdio.h>;
#include <iostream>
#include <string>
#define SIZE 5

using namespace std;

typedef struct s_list
{
    string data;
} t_list;

void zeroing(t_list sp[])
{
    int i = 0;
    while (i < SIZE)
    {
        sp[i].data = "-1";
        i++;
    }
}

int queue_empty(int N)
{
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

int ft_isNumber(string str)
{
    int isd = 1;
    int i = 0;
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]))
        {
            return 0;
            i++;
        }
        i++;
    }
    return 1;
}

int ft_strcmp(string str1, string str2)
{
    if (ft_isNumber(str1) && ft_isNumber(str2))
    {
        if (str1.length() != str2.length())
        {
            return str1.length() < str2.length() ? -1 : 1;
        }
        else
        {
            for (int i = 0; ; i++)
            {
                if (str1[i] != str2[i])
                    return str1[i] < str2[i] ? -1 : 1;
            }
        }
    }
    else
    {
        for (int i = 0; ; i++)
        {
            if (str1[i] == '\0')
                return -1;
            if (str2[i] == '\0')
                return 1;
            if (str1[i] != str2[i])
                return str1[i] < str2[i] ? -1 : 1;
        }
    }
}

void push(t_list sp[], string data, int& N)
{
    int temp;
    int j;
    int i = 0;

    if (N == 0)
    {
        sp[i].data = data;
        N++;
    }
    else
    {
        while (ft_strcmp(sp[i].data, data) == -1 && i < N)
            i++;
        j = N;
        while (j > i)
        {
            sp[j].data = sp[j - 1].data;
            j--;
        }
        sp[i].data = data;
        N++;
    }
}

void pop(t_list* sp, string data, int &N)
{
    int i = 0;
    int j;

    while (sp[i].data != data && sp[i].data != "-1" && i < SIZE)
        i++;

    if (sp[i].data == data)
    {
        while (i < N - 1)
        {
            sp[i].data = sp[i + 1].data;
            i++;
        }
        sp[N - 1].data = "-1";
    }
    N--;
}

void print(t_list sp[], int N)
{
    int i = 0;
    while (i < N)
    {
        cout << sp[i].data << " ";
        i++;
    }
    cout << endl;
}

void main()
{
    t_list sp[SIZE];
    int N = 0;
    char a;
    string data;

    zeroing(sp);
    while (true) {

        cout << "Check for empty......................1" << endl;
        cout << "Add element..........................2" << endl;
        cout << "Delete element.......................3" << endl;
        cout << "Print queue..........................4" << endl;

        cin >> a;
        if (a < '1' || a > '4')
            cout << "Incorrect entry" << endl;
        else
        {
            switch (a)
            {
            case '1':
                if (queue_empty(N) == 0)
                    cout << "Queue is full" << endl;
                else if (queue_empty(N) == 1)
                    cout << "Queue is empty" << endl;
                else
                    cout << "Queue isn't empty" << endl;
                break;
            case '2':
                if (queue_empty(N) == 0)
                    cout << "Queue is full" << endl;
                else
                {
                    cout << "Enter element: ";
                    cin >> data;
                    push(sp, data, N);
                }
                break;
            case '3':
                if (queue_empty(N) == 1)
                    cout << "Queue is empty" << endl;
                else
                {
                    cout << "Enter element: ";
                    cin >> data;
                    pop(sp, data, N);
                }
                break;
            case '4':
                if (queue_empty(N) == 1)
                    cout << "Queue is empty" << endl;
                else print(sp, N);
                break;
            }
        }
    }
}