#pragma once
#define MaxSize 1000
#define InitSize 100
//#define ElemType int
#define ElemType BiTree

//顺序栈的结构
typedef struct SqStack{
    ElemType data[MaxSize];
    int top;
};

//链栈的结构
typedef struct LinkNode {
    ElemType data;
    struct LinkNode* next;
}*LinkStack;

//顺序栈的操作
void InitStack(SqStack& S)
{
    S.top = -1;
}

bool StackIsEmpty(SqStack S)
{
    return S.top == -1;
}

bool StackPush(SqStack& S, ElemType e)
{
    if (S.top == MaxSize - 1)
        return false;
    else
    {
        S.data[++S.top] = e;
        return true;
    }
}

bool StackPop(SqStack& S)
{
    if (S.top == -1)
        return false;
    else
        S.top--;
    return true;
}

ElemType StackTop(SqStack& S)
{
    if (S.top == -1)
        return false;
    return S.data[S.top];
}