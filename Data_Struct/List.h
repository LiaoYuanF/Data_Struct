#pragma once
#define MaxSize 1000
#define InitSize 100
#define ElemType int
#include <malloc.h>

//˳���ľ�̬����
typedef struct SqList {
    ElemType data[MaxSize];
    int current_length;
}SqList;

//˳���Ķ�̬����
typedef struct SeqList {
    ElemType *data;
    int max_length, current_length;
}SeqList;


//������
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

//˫����
typedef struct DNode {
    ElemType data;
    struct DNode* prior;
    struct DNode* next;
}DNode, *DLinkList;

//��̬����
typedef struct {
    ElemType data;
    int next;
}SLinkList[MaxSize];

//˳������
bool List_insert(SqList& L, int i, ElemType e)
{
    if (i < 1 or i > L.current_length + 1)
        return false;
    if (L.current_length >= MaxSize)
        return false;
    for (int j = L.current_length + 1; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.current_length++;
    return true;
}

//˳���ɾ��
bool List_Delete(SqList& L, int i, ElemType& e)
{
    if (i < 1 or i > L.current_length + 1)
        return false;
    e = L.data[i];
    for (int j = i; j <= L.current_length; j++)
        L.data[j] = L.data[j + 1];
    L.current_length--;
    return true;
}

//˳������
int List_search(SqList& L, ElemType& e)
{
    for (int i = 0; i <= L.current_length; i++)
    {
        if (L.data[i] == e)
            return i + 1;
    }
    return false;
}

//ͷ�巨��������
LinkList List_HeadInsert(LinkList& L, ElemType datalist[], ElemType number)
{
    LNode* s;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    for (int i = 0; i < number; i++)
    {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = datalist[i];
        s->next = L->next;
        L->next = s;
    }
    return L;
}

//β�巨��������
LinkList List_TailInsert(LinkList& L, ElemType datalist[], ElemType number)
{
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode* s, * r = L;
    for (int i = 0; i < number; i++)
    {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = datalist[i];
        s->next = r->next;
        r->next = s;
        r = r->next;
    }
    return L;
}
