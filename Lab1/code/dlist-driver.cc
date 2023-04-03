#include "dlist.h"
#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

#define NUM_RANGE 100

void InsertItem(int which, DLList *list, int key)
{
    printf("%d 插入元素 %d \n", which, key);
    list->SortedInsert3(NULL, key);
}

void RemoveItem(int which, DLList *list, int key)
{
    printf("%d 删除了元素 %d \n", which, key);
    list->SortedRemove(key);
}

void PrintList(int which, DLList *list)
{
    printf("Print List from %d: ", which);
    list->ShowList();
}
//在list随机有序的插入n个随机数  两个强制装换的位置不同
void genItem2List(DLList *list, int n)
{
    int *item, key;

    // generating new rand() seed for each iteration
    static int random = 0;
    random++;
    srand(unsigned(time(0)) + random);

    for (int i = 0; i < n; i++)
    {
        item = new int;
        *item = rand() % NUM_RANGE;
        key = rand() % NUM_RANGE;
        cout << "Insert: key->" << key << endl;
        list->SortedInsert((void *)item, key); //差别在这
        list->ShowList1();
    }
}
void genItem2List2(DLList *list, int n,int which)
{
    int *item, key;

    // generating new rand() seed for each iteration
    static int random = 0;
    random++;
    srand(unsigned(time(0)) + random);

    for (int i = 0; i < n; i++)
    {
        item = new int;
        *item = rand() % NUM_RANGE;
        key = rand() % NUM_RANGE;
        cout << "thread:which" << which <<" Insert: key->" << key << endl;
        list->SortedInsert2((void *)item, key); //差别在这
        list->ShowList1();
    }
}

//在list随机删除n个数
void delItemFromList(DLList *list, int n)
{
    int k, key;
    srand((int)time(0));

    for (int i = 0; i < n; i++)
    {
        int number = 0;
        number = list->CountList();
        if (list->IsEmpty())
        {
            k = rand() % number;
            key = list->FoundKey(k);
            list->SortedRemove(key);
            cout << "Remove: key->" << key << endl;
            list->ShowList2();
        }
        else
        {
            cout << "List emptied." << endl;
            return;
        }
    }
}
