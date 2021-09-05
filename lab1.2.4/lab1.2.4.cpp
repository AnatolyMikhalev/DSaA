#include <stdio.h>;
#include <iostream>

using namespace std;

struct node
{
    int Data;
    node* next;
};

int stack_empty(node* top) {
    if (top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(node** top, int data) {
    node* temp;
    temp = new node();
    temp->Data = data;
    if (top == NULL) {
        *top = temp;
    }
    else
    {
        temp->next = *top;
        *top = temp;
    }
}

void push_alt(node** top, node** altop) {

    node* temp = *top;
    *top = temp->next;

    temp->next = *altop;
    *altop = temp;

}

void push_random(node** top, int N) {
    srand(time(NULL));
    int data;
    for (int i = 0; i < N; i++) {
        data = rand() % 99 + 1;
        push(top, data);
    }

}

void pop(node** top) {
    if (stack_empty(*top))
    {
        cout << "Стек пуст" << endl;
    }
    else
    {
        node* temp = *top;
        *top = temp->next;
        delete temp;
    }

}

void print(node* top) {
    node* temp = top;
    while (temp != NULL)
    {
        cout << temp->Data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void main()
{
    setlocale(LC_ALL, "Rus");
    node* sp = NULL;
    node* altsp = NULL;

    while (true) {

        cout << "Проверка пустоты стека                            1" << endl;
        cout << "Добавление элемента в вершину стека               2" << endl;
        cout << "Удаление элемента из вершины стека                3" << endl;
        cout << "Вывод текущего состояния стека на экран           4" << endl;
        cout << "Занесение нескольких значений                     5" << endl;
        cout << "Вывод текущего состояния вспомогательного стека   6" << endl;

        int a;
        cin >> a;

        switch (a)
        {
        case 1:
            if (stack_empty(sp))
            {
                cout << "Стек пуст" << endl;
            }
            else
            {
                cout << "Стек не пуст" << endl;
            }
            break;
        case 2:
            if (stack_empty(altsp)) {
                cout << "Введите элемент: ";
                cin >> a;
                push(&sp, a);
            }
            else
            {
                cout << "Взять элемент из вспомогательного стека? " << endl << "Да  - 1" << endl << "Нет - 0" << endl;
                cin >> a;
                if (a) {
                    push_alt(&altsp, &sp);
                }
                else {
                    cout << "Введите элемент: ";
                    cin >> a;
                    push(&sp, a);
                }
            }
            break;
        case 3:
            cout << "Перенести элемент во вспомогательный список?" << endl << "Да  - 1" << endl << "Нет - 0" << endl;
            cin >> a;
            if (a) {
                push_alt(&sp, &altsp);
            }
            else
            {
                pop(&sp);
            }
            break;
        case 4:
            print(sp);
            break;
        case 5:
            cout << "Введите количество элементов: ";
            cin >> a;
            push_random(&sp, a);
            break;
        case 6:
            print(altsp);
            break;
        }
    }
}