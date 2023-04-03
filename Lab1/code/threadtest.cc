// threadtest.cc
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield,
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include <ctime>
#include "dllist.h"

// 增加 extern
extern void InsertItem(int which, DLList *list, int key);
extern void RemoveItem(int which, DLList *list, int key);
extern void genItem2List(DLList *dlist, int N);
extern void genItem2List2(DLList *dlist, int N,int which);
extern void genItem2List3(DLList *dlist, int N);
extern void delItemFromList(DLList *dlist, int N);
extern void PrintList(int which, DLList *list);

// testnum is set in main.cc
//默认情况
int testnum = 1;
int threadNum = 2;
int oprNum = 2;
bool flag; //标记线程是否可以yield
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

DLList *list = new DLList(); // the common list

char *
getName(int i)
{
    switch (i)
    {
        case 0:
            return "forked thread 0";
        case 1:
            return "forked thread 1";
        case 2:
            return "forked thread 2";
        case 3:
            return "forked thread 3";
        case 4:
            return "forked thread 4";
        case 5:
            return "forked thread 5";
        case 6:
            return "forked thread 6";
        case 7:
            return "forked thread 7";
        case 8:
            return "forked thread 8";
        case 9:
            return "forked thread 9";
        case 10:
            return "forked thread 10";
        default:
            return "forked thread 00";
    }
}
void DllistTest(int witch)
{ //展示双向链表
    genItem2List(list, 5);
    list->ReverseShowList();//逆序打印
    delItemFromList(list, 3);
    list->ReverseShowList();
}
void DllistTest1(int which)
{ //共享内存
    printf("Inserting items in thread %d\n", which);
    genItem2List(list, oprNum);
    currentThread->Yield();
    printf("Removing items in thread %d\n", which);
    delItemFromList(list, oprNum);
}

void DllistTest2(int which)
{ //覆盖和断链
    genItem2List2(list, oprNum,which);
    genItem2List2(list, oprNum,which);
}

void DllistTest3(int which)
{ //乱序
    printf("Thread {%d} start.\n", which);
    if (which == 1)
    {
        InsertItem(which, list, 1);
        InsertItem(which, list, 10);
        InsertItem(which, list, 0);
        InsertItem(which, list, 5);
        PrintList(which, list); // 此处发生线程切换
        InsertItem(which, list, 3);
        InsertItem(which, list, 7);
        PrintList(which, list);
    }
    else
    { // which == 2
        PrintList(which, list);
        InsertItem(which, list, 3);
        PrintList(which, list);
    }
}

void toDllistTest(VoidFunctionPtr func)
{
    DEBUG('t', "Entering  toDllistTest\n");
    Thread *t;
    for (int i = 0; i < threadNum; i++)
    {
        t = new Thread(getName(i + 1));
        t->Fork(func, i + 1);
    }
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------
void ThreadTest()
{
    printf("Entering test %d\n", testnum);
    switch (testnum)
    {
        case 1:
            toDllistTest(DllistTest);
            break;
        case 2: // switch out of function
            toDllistTest(DllistTest1);
            break;
        case 3: // insert to the empty list causing one item coving the other one
            toDllistTest(DllistTest2);
            break;
        case 4: // delete item  at  one time
            toDllistTest(DllistTest3);
            break;
        default:
            printf("No test specified.\n");
            break;
    }
}
