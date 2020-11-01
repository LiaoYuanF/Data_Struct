#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;

template<class T>
struct Node {
	T key;
	Node<T>* lchild;
	Node<T>* rchild;
	Node<T>(T k) : key(k), lchild(nullptr), rchild(nullptr) {}
};

template<class T>
class AVLTree {
private:
	Node<T>* root;
public:
	AVLTree() :root(nullptr) {};
	Node<T>* getRoot() { return root; }
	void printTree();
	Node<T>* llRotation(Node<T>*);
	Node<T>* lrRotation(Node<T>*);
	Node<T>* rrRotation(Node<T>*);
	Node<T>* rlRotation(Node<T>*);
	void balance(Node<T>*);
	void insert(const T&);
	bool remove(Node<T>*, Node<T>*, T);
	int getDepth(Node<T>*);
	int getBalanceFactor(Node<T>*);
	Node<T>* findMin(Node<T>*);
	Node<T>* findMax(Node<T>*);
	void fixUp();
	Node<T>* find(Node<T>* node, T key);
};

template<class T>
void AVLTree<T>::printTree() {  //��α���
	Node<T>* pos = root;  //��ǰλ��
	Node<T>* flag = root;  //��ĩ��ʶ

	queue<Node<T>*> q;
	q.push(root);  //���ڵ����

	while (!q.empty()) {  //���зǿ�
		Node<T>* node = q.front();
		q.pop();  //��������
		cout << node->key << '\t';

		if (node->lchild != nullptr) {  //���ӷǿ������
			q.push(node->lchild);
			pos = node->lchild;
		}

		if (node->rchild != nullptr) {  //�Һ��ӷǿ������
			q.push(node->rchild);
			pos = node->rchild;
		}

		if (node == flag) {  //�ִ��ĩ
			flag = pos;
			cout << "\n";
		}
	}
}

template<class T>
void AVLTree<T>::insert(const T& key) {
	Node<T>* node = new Node<T>(key);
	if (root == nullptr) {
		root = node;
		return;
	}
	Node<T>* pos = root;
	while (true) {  //���Ҳ���λ��
		if (node->key < pos->key) {
			if (pos->lchild == nullptr) {
				pos->lchild = node;
				fixUp();
				return;
			}   //end if
			else
				pos = pos->lchild;
		}  //end if
		else if (node->key > pos->key) {
			if (pos->rchild == nullptr) {
				pos->rchild = node;
				fixUp();
				return;
			}  //end if
			else
				pos = pos->rchild;
		}  //end if
		else
			return;  //�������д˽ڵ����޲���
	}  
}

template<class T>
int AVLTree<T>::getDepth(Node<T>* node) {
	if (node == nullptr)
		return 0;
	return max(getDepth(node->lchild), getDepth(node->rchild)) + 1;
}

template<class T>
int AVLTree<T>::getBalanceFactor(Node<T>* node) {  //ƽ������ = ��������-��������
	return getDepth(node->lchild) - getDepth(node->rchild);
}

template<class T>
void AVLTree<T>::balance(Node<T>* node) {
	int bf = getBalanceFactor(node);
	if (bf > 1) {
		if (getBalanceFactor(node->lchild) > 0)
			root = llRotation(node);
		else
			root = lrRotation(node);
	}
	else if (bf < -1) {
		if (getBalanceFactor(node->rchild) > 0)
			root = rlRotation(node);
		else
			root = rrRotation(node);
	}
	return;
}

template<class T>
Node<T>* AVLTree<T>::llRotation(Node<T>* node) {  //����ڵ�����������ߣ�����
	Node<T>* temp = node->lchild;
	node->lchild = temp->rchild;
	temp->rchild = node;
	return temp;
}

template<class T>
Node<T>* AVLTree<T>::lrRotation(Node<T>* node) {  //����ڵ����������ұ�
	Node<T>* temp = node->lchild;
	node->lchild = rrRotation(temp);
	return llRotation(node);
}

template<class T>
Node<T>* AVLTree<T>::rlRotation(Node<T>* node) {  //����ڵ������������
	Node<T>* temp = node->rchild;
	node->rchild = llRotation(temp);
	return rrRotation(node);
}

template<class T>
Node<T>* AVLTree<T>::rrRotation(Node<T>* node) {  //����ڵ�����������ߣ�����
	Node<T>* temp = node->rchild;
	node->rchild = temp->lchild;
	temp->lchild = node;
	return temp;
}

template<class T>
bool AVLTree<T>::remove(Node<T>* node, Node<T>* parent, T key) {
	Node<T>* temp = nullptr;
	if (node == nullptr)  
		return false;
	else if (key < node->key)
		return remove(node->lchild, node, key);
	else if (key > node->key)
		return remove(node->rchild, node, key);
	else if (node->lchild && node->rchild) {  //ɾ���ڵ���������Ҳ��������

		if (getDepth(node->lchild) > getDepth(node->rchild)) {  //�������ߣ�ǰ�����
			temp = findMax(node->lchild);
			node->key = temp->key;
			return remove(node->lchild, node, node->key);
		}
		else {  //���������������������������
			temp = findMin(node->rchild);
			node->key = temp->key;
			return remove(node->rchild, node, node->key);
		}
	}
	else {
		if ((node->lchild && node->rchild == nullptr)) {  //ɾ���ڵ����������Һ���
			temp = findMax(node->lchild);
			node->key = temp->key;
			return remove(node->lchild, node, node->key);
		}
		else if (node->rchild && node->lchild == nullptr) {  //ɾ���ڵ����Һ���������
			temp = findMin(node->rchild);
			node->key = temp->key;
			return remove(node->rchild, node, node->key);
		}  //end if
		else {  //ɾ���ڵ����յݹ鵽ɾ��Ҷ�ӽڵ�
			if (node == parent->lchild)  //���ڵ�ָ���ÿ�
				parent->lchild = nullptr;
			else
				parent->rchild = nullptr;
			delete node;  //�ͷ��ӽڵ�
			node = nullptr;

			fixUp();
		}
	}  //end else
	return true;
}

template<class T>
void AVLTree<T>::fixUp() {
	Node<T>* temp = this->root;  //�Զ����µ�����
	while (1)  //Ѱ��ʧ��Ľڵ�
	{
		if (getBalanceFactor(temp) == 2) {
			if (fabs(getBalanceFactor(temp->lchild)) == 1)
				break;
			else
				temp = temp->lchild;
		}
		else if (getBalanceFactor(temp) == -2) {
			if (fabs(getBalanceFactor(temp->rchild)) == 1)
				break;
			else
				temp = temp->rchild;
		}
		else break;
	}
	balance(temp);
	return;
}

template<class T>
Node<T>* AVLTree<T>::find(Node<T>* node, T key) {
	while (node != nullptr && key != node->key) {  //��������
		if (key < node->key)
			node = node->lchild;
		else
			node = node->rchild;
	}
	if (node == nullptr)
		cout << "Element " << key << " doesn't exist!" << endl;
	else
		cout << "Element " << key << " exists." << endl;
	return node;
}

template<class T>
Node<T>* AVLTree<T>::findMax(Node<T>* node) {
	if (node != nullptr) {
		while (node->rchild)
			node = node->rchild;
	}
	return node;
}

template<class T>
Node<T>* AVLTree<T>::findMin(Node<T>* node) {
	if (node != nullptr) {
		if (node->lchild == nullptr)  //����Ϊ�գ���ǰ�ڵ�����������
			return node;
		else
			return findMin(node->lchild);  //���Ӳ�Ϊ�գ�������������
	}
	else
		return nullptr;  //��������nullptr
}

int main() {
	int arr[]{ 7,4,8,5,1,6 };//ll:738512����;rr:7385129ɾ��2;rl:7385124ɾ��4;lr:748516����
	AVLTree<int> avl;
	for (int i = 0; i < 6; i++)
	{
		avl.insert(arr[i]);
	}
	avl.printTree();
	avl.find(avl.getRoot(), 8);
	avl.remove(avl.getRoot(), nullptr, 8);
	avl.printTree();
}
