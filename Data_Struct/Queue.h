#pragma once
#define MaxSize 1000
#define InitSize 100
#define ElemType BiTree
#include <malloc.h>

//˳�����
typedef struct SqQueue{
    ElemType data[MaxSize];
    int front, rear;
};


//��ʽ����
typedef struct QueueNode {
    ElemType data;
    struct QueueNode* next;
};

typedef struct LinkQueue {
    QueueNode* front;
    QueueNode* rear;
};


//ѭ�����г�ʼ��
void InitQueue(SqQueue& Q)
{
    Q.front = 0;
    Q.rear = 0;
}

//ѭ�������п�
bool QueueIsEmpty(SqQueue Q)
{
    return Q.front == Q.rear;
}

//ѭ����������
bool QueueIsFull(SqQueue Q)
{
    return (Q.rear + 1) % MaxSize == Q.front;
}


//ѭ�����н���
bool EnQueue(SqQueue& Q, ElemType e)
{
    if (QueueIsFull(Q))
        return false;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}


//ѭ�����г���
ElemType DeQueue(SqQueue& Q)
{
    if (QueueIsEmpty(Q))
        return false;
    ElemType e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return e;
}

//������г���
int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}


//��ʽ���г�ʼ��
void InitLinkQueue(LinkQueue& Q)
{
    Q.front = (QueueNode*)malloc(sizeof(QueueNode));
    Q.rear = (QueueNode*)malloc(sizeof(QueueNode));
    Q.front->next = NULL;
}

//��ʽ�����п�
bool LinkQueueIsEmpty(LinkQueue Q)
{
    return Q.front == Q.rear;
}

//��ʽ���н���
void EnLinkQueue(LinkQueue& Q, ElemType e)
{
    QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
    s->data = e;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

//��ʽ���г���
ElemType EnLinkQueue(LinkQueue& Q)
{
    if (LinkQueueIsEmpty)
        return false;
    ElemType e = Q.front->next->data;
    Q.front->next = Q.front->next->next;
    return e;
}