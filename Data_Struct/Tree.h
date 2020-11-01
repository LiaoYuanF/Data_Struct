#pragma once
#define MaxSize 1000
#define InitSize 100
#define ElemType int

typedef struct BiTNode {
    ElemType data;
    struct BiTNode* lchild, * rchild;
}*BiTree;


typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode* lchild, * rchild;
    int ltag, rtag;
}ThreadNode, *ThreadTree;