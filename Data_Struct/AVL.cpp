#define ElemType int

typedef struct TNode {
    ElemType data;
    struct TNode *lchild, *rchild;
}*Tree;

class AVLTree {
private:
    Tree root;
public:
    Tree getRoot()
    {
        return root;
    }


};

