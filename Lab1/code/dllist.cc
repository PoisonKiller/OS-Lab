#include "dllist.h"
#include "system.h"
#include <cstdio>

DLLElement::DLLElement(void *itemPtr, int sortKey)
{
    next = NULL;
    prev = NULL;
    key = sortKey;
    item = itemPtr;
}

DLList::DLList()
{
    // 创建头节点
    first = NULL;
    last = NULL;
}

DLList::~DLList()
{
    while (first != NULL)
    {
        DLLElement *p = first;
        first = first->next;
        delete p;
    }
}
// 插入头节点
void DLList::Prepend(void *item)
{
    if (first == NULL)
    {
        DLLElement *_new = new DLLElement(item, 1);
        first = _new;
        last = _new;
        return;
    }
    else
    {
        DLLElement *_new = new DLLElement(NULL, first->key - 1);
        first->prev = _new;
        _new->next = first;
        first = _new;
        return;
    }
}
// 插入尾节点
void DLList::Append(void *item)
{
    if (last == NULL)
    {
        DLLElement *_new = new DLLElement(item, 1);
        first = _new;
        last = _new;
        return;
    }
    else
    {
        DLLElement *_new = new DLLElement(NULL, first->key - 1);
        last->next = _new;
        _new->prev = last;
        last = _new;
        return;
    }
}
// 移除头节点
void *DLList::Remove(int *keyPtr)
{
    if (first == NULL)
        return NULL;
    else
    {
        DLLElement *p = first;
        first = first->next;
        return p;
    }
}
// 链表是否为空
bool DLList::IsEmpty()
{
    return (!first && !last) ? false : true;
}

void DLList::SortedInsert(void *item, int sortKey)
{ // 按顺序插入
    DLLElement *p = first;
    DLLElement *_new = new DLLElement(item, sortKey);
    if (first == NULL)
    {
        first = _new;
        last = _new;
        return;
    }
    if (sortKey < first->key)
    { // 插入第一个
        _new->next = first;
        first->prev = _new;
        first = _new;
        return;
    }
    while (p->next != NULL)
    { // 插入中间
        p = p->next;
        if (sortKey < p->key)
        {
            _new->next = p;
            _new->prev = p->prev;
            p->prev->next = _new;
            p->prev = _new;
            return;
        }
    }
    if (sortKey >= p->key)
    { // 插入最后一个
        _new->prev = p;
        p->next = _new;
        last = _new;
    }
};

void DLList::SortedInsert2(void *item, int sortKey)
{ //覆盖和断链测试
    DLLElement *p = first;
    DLLElement *_new = new DLLElement(item, sortKey);
    if (first == NULL)
    {
        first = _new;
        last = _new;
        return;
    }
    if (sortKey < first->key)
    { // 插入第一个
        _new->next = first;
        currentThread->Yield();
        first->prev = _new;
        first = _new;
        return;
    }
    while (p->next != NULL)
    { // 插入中间
        p = p->next;
        if (sortKey < p->key)
        {
            _new->next = p;
            currentThread->Yield();
            _new->prev = p->prev;
            p->prev->next = _new;
            p->prev = _new;
            return;
        }
    }
    if (sortKey >= p->key)
    { // 插入最后一个
        _new->prev = p;
        currentThread->Yield();
        p->next = _new;
        last = _new;
    }
};

void DLList::SortedInsert3(void *item, int sortKey)
{ //乱序插入测试
    DLLElement *p = first;
    DLLElement *_new = new DLLElement(item, sortKey);
    if (first == NULL)
    {
        first = _new;
        last = _new;
        return;
    }
    if (sortKey < first->key)
    { // 插入第一个
        _new->next = first;
        first->prev = _new;
        first = _new;
        return;
    }
    while (p->next != NULL)
    { // 插入中间
        p = p->next;
        if (sortKey < p->key)
        {
            _new->next = p;
            _new->prev = p->prev;
            currentThread->Yield(); //! 这个地放做强制线程切换，测试链表插入过程中发生线程切换的情况。
            p->prev->next = _new;
            p->prev = _new;
            return;
        }
    }
    if (sortKey >= p->key)
    { // 插入最后一个
        _new->prev = p;
        p->next = _new;
        last = _new;
    }
};

// 删除第一个符合条件的节点
void *DLList::SortedRemove(int sortKey)
{
    DLLElement *p = first;
    if (p == NULL)
        return NULL;
    if (first->key == sortKey)
    {
        first = first->next;
        return first;
    };
    while (p->next != first)
    {
        p = p->next;
        if (p->key == sortKey)
        {
            p->prev->next = p->next;
            if (p->next != NULL)
                p->next->prev = p->prev;
            else
                last = p->prev;
            return p;
        }
    }
    return NULL;
};

// print list
void DLList::ShowList()
{
    DLLElement *p = first;
    if (p == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (p->next != NULL)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("%d\n", p->key); // 最后一个
}
// print list 插入时打印
void DLList::ShowList1()
{
    DLLElement *p = first;
    if (p == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("插入后打印: ");
    while (p->next != NULL)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("%d\n", p->key); // 最后一个
}
// print list 删除时打印
void DLList::ShowList2()
{
    DLLElement *p = first;
    if (p == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("删除后打印: ");
    while (p->next != NULL)
    {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("%d\n", p->key); // 最后一个
}
// print list 删除时打印
void DLList::ReverseShowList()
{
    DLLElement *p = last;
    if (p == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("逆序打印:");
    while (p->prev != NULL)
    {
        printf("%d ", p->key);
        p = p->prev;
    }
    printf("%d\n", p->key); // 最后一个
}
//求链表长度
int DLList::CountList()
{
    int number = 0;
    DLLElement *p = first;
    if (p == NULL)
    {
        return 0;
    }
    while (p != NULL)
    {
        number++;
        p = p->next;
    }
    return number;
}
//第n个结点的key值
int DLList::FoundKey(int n)
{
    DLLElement *p = first;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        p = p->next;
    }
    return p->key;
}
