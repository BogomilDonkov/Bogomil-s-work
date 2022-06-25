#include <iostream>
#include <iomanip>
//#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <time.h>

using namespace std;

struct elem {
    int key;
    elem* left;
    elem* right;
};
elem* root = NULL;

bool add(elem*& p, int n);
void preorder(elem*& p);
bool parent_search(elem* &p,int n,int&x);

int main()
{
    setlocale(LC_ALL, "BG");

    int n, k, x;
    char ch = 'y';

    cout << "Въведете елементи на дървото:\n";

    while (cin >> n)
    {
        if (add(root, n))
        {
            cout << "\nВие успешно добавихте " << n << " към дървото\n";
        }
        else
        {
            cout <<n << "\nвече съществува като елемент в дървото\n";
        }
    }
    cin.clear();
    cin.ignore(223, '\n');

    preorder(root);

    while (ch == 'Y' || ch == 'y')
    {
        cout << "\n\nВъведи число за търсене в дървото: ";
        while (!(cin >> k))
        {
            cout << "\nError: Enter number! :";
            cin.clear();
            cin.ignore(223, '\n');

        }
        if(parent_search(root, k, x))
        {
            cout << "\nРодителя на "<<k<<" е "<<x;
        }
        else if(root->key==k)
        {
            cout << "\nЕлемента " << k << ",който търсите е корен на дървото";
        }
        else
        {
            cout << "\nЕлемента не съществува в дървото";
        }

        cout << "\nИскате ли да потърсите пак ?(Y/N)";
        //ch = _getch();
        cin >> ch;
    }  
    return 0;
}

//Добавяне на Елемент
bool add(elem*& p, int n)
{     
    if (p)
    {
        if (n < p->key) //Ако (n<p->key) продължаваме наляво
        {
            add(p->left, n);
        }
        else if (n > p->key) //Ако (n>p->key) продължаваме надясно
        {
            add(p->right, n);
        }
        else
        {
            return false; //Ако (n==p->key) връщаме false (следователно не въвеждаме нова стойност в дървото)
        }
    }
    else
    {
        elem* t = new elem;
        t->key = n;
        t->left = NULL;
        t->right = NULL;
        p = t; return true;
    }
}

//Извеждане на всички елементи от дървото
void preorder(elem*& p)
{
    if (p)
    {
        cout << p->key<<" ";
        preorder(p->left);
        preorder(p->right);
    }
}

//Търси родителя на въведения от потребителя елемент
bool parent_search(elem* &p, int n,int &x)
{   
    if (p)
    {     
        if (p->left)
        {
            if (p->left->key == n)
            {
                x = p->key; return true;
            }
        }
        if (p->right)
        {
            if (p->right->key == n)
            {
                x = p->key; return true;
            }
        }
        if(parent_search(p->left, n, x)) { return true; }
        if(parent_search(p->right, n, x)) { return true; }
    }
    return false;
}

/*Задача 11.Да се състави програма на С / С++,
която използва функция за търсене на родител на
определен елемент в дадено двоично дърво за търсене.
*/