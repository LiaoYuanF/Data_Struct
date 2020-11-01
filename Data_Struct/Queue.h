#pragma once
#define MaxSize 1000
#define InitSize 100
#define ElemType BiTree
#include <malloc.h>

//顺序队列
typedef struct SqQueue{
    ElemType data[MaxSize];
    int front, rear;
};


//链式队列
typedef struct QueueNode {
    ElemType data;
    struct QueueNode* next;
};

typedef struct LinkQueue {
    QueueNode* front;
    QueueNode* rear;
};


//循环队列初始化
void InitQueue(SqQueue& Q)
{
    Q.front = 0;
    Q.rear = 0;
}

//循环队列判空
bool QueueIsEmpty(SqQueue Q)
{
    return Q.front == Q.rear;
}

//循环队列判满
bool QueueIsFull(SqQueue Q)
{
    return (Q.rear + 1) % MaxSize == Q.front;
}


//循环队列进队
bool EnQueue(SqQueue& Q, ElemType e)
{
    if (QueueIsFull(Q))
        return false;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}


//循环队列出队
ElemType DeQueue(SqQueue& Q)
{
    if (QueueIsEmpty(Q))
        return false;
    ElemType e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return e;
}

//计算队列长度
int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}


//链式队列初始化
void InitLinkQueue(LinkQueue& Q)
{
    Q.front = (QueueNode*)malloc(sizeof(QueueNode));
    Q.rear = (QueueNode*)malloc(sizeof(QueueNode));
    Q.front->next = NULL;
}

//链式队列判空
bool LinkQueueIsEmpty(LinkQueue Q)
{
    return Q.front == Q.rear;
}

//链式队列进队
void EnLinkQueue(LinkQueue& Q, ElemType e)
{
    QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
    s->data = e;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

//链式队列出队
ElemType EnLinkQueue(LinkQueue& Q)
{
    if (LinkQueueIsEmpty)
        return false;
    ElemType e = Q.front->next->data;
    Q.front->next = Q.front->next->next;
    return e;
}