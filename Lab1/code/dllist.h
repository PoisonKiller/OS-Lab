#ifndef DLIST_H
#define DLIST_H

class DLLElement
{
public:
    DLLElement(void *itemPtr, int sortKey); // initialize a list element

    DLLElement *next; // next element on list
                      // NULL if this is the last
    DLLElement *prev; // previous element on list
                      // NULL if this is the first

    int key;    // priority, for a sorted list
    void *item; // pointer to item on the list
};

class DLList
{
public:
    DLList();  // initialize the list
    ~DLList(); // de-allocate the list

    void Prepend(void *item);  // add to head of list (set key = min_key-1)
    void Append(void *item);   // add to tail of list (set key = max_key+1)
    void *Remove(int *keyPtr); // remove from head of list
    // return true if list has elements             
    bool IsEmpty(); 
    // routines to put/get items on/off list in order (sorted by key)
    void SortedInsert(void *item, int sortKey);
    void SortedInsert2(void *item, int sortKey);
    void SortedInsert3(void *item, int sortKey);
    // remove first item with key==sortKey
    void *SortedRemove(int sortKey);
    //求链表长度
    int CountList();
    //第n个结点的key值
    int FoundKey(int n);
    // 打印整个链表 因为线程的切换会导致两次连续打印 所以区分是插入时打印还是删除时打印
    void ShowList();
    void ShowList1();
    void ShowList2();
    //逆序打印链表
    void ReverseShowList();
    // test
    void Print();
private:
    DLLElement *first; // head of the list, NULL if empty
    DLLElement *last;  // last element of the list, NULL if empty
};
#endif
