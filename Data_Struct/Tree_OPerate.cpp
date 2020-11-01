#include "Tree.h"
#include "Stack.h"
#include "Queue.h"

void visit(BiTree T)
{
    //do anything interesting
}

//先序遍历
void Preorder_1(BiTree T)
{
    if (T)
    {
        visit(T);
        Preorder_1(T->lchild);
        Preorder_1(T->rchild);
    }
}

void Preorder_2(BiTree T)
{
    SqStack S;
    InitStack(S);
    auto p = T;
    while ((p or !StackIsEmpty(S)))
    {
        if (p)
        {
            visit(p);
            StackPush(S,p);
            p = p->lchild;
        }
        else
        {
            p = StackTop(S)->rchild;
            StackPop(S);
        }
    }
}

//中序遍历
void Inorder_1(BiTree T)
{
    if (T)
    {
        Preorder_1(T->lchild);
        visit(T);
        Preorder_1(T->rchild);
    }
}

void Inorder_2(BiTree T)
{
    SqStack S;
    InitStack(S);
    auto p = T;
    while ((p or !StackIsEmpty(S)))
    {
        if (p)
        {
            StackPush(S, p);
            p = p->lchild;
        }
        else
        {
            p = StackTop(S);
            visit(p);
            p = p->rchild;
            StackPop(S);
        }
    }
}

//后序遍历
void Postorder_1(BiTree T)
{
    if (T)
    {
        Preorder_1(T->lchild);
        Preorder_1(T->rchild);
        visit(T);
    }
}

//后续非递归
//遍历中右左,然后倒序



//层次遍历
void LevelOrder(BiTree T)
{
    SqQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    while (!QueueIsEmpty(Q))
    {
        auto p = DeQueue(Q);
        visit(p);
        if (p->lchild)
            EnQueue(Q, p->lchild);
        if (p->rchild)
            EnQueue(Q, p->rchild);
    }
}

//中序线索化
void CreateInTread(ThreadTree T)
{
    auto p = T;
    while (T)
    {
        InThread(T, p);
        p->rchild = NULL;
        p->rtag = 1;
    }
}

void InThread(ThreadTree& T, ThreadTree& p)
{
    if (T)
    {
        InThread(T->lchild, p);
        if (!T->lchild)
        {
            T->lchild = p;
            T->ltag = 1;
        }
        if (p && (!p->lchild))
        {
            p->rchild = T;
            p->rtag = 1;
        }
        p = T;
        InThread(T->rchild, p);
    }
}


//二叉排序树的插入
bool BST_Create(BiTree &T,int key)
{
    if (!T)
    {
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T->data = key;
        T->lchild = NULL;
        T->rchild = NULL;
        return 1;
    }
    else
    {
        if (key == T->data)
            return 0;
        if (key > T->data)
            return BST_Create(T->rchild, key);
        if (key < T->data)
            return BST_Create(T->lchild, key);      
    }
}

//二叉排序树的查找
BiTree BST_Search(BiTree T,int key)
{
    while (T and key != T->data)
    {
        if (key > T->data)
            T = T->rchild;
        else
            T = T->lchild;
    }
    return T;
}