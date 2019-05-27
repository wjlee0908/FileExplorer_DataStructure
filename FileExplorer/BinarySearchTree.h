#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <iostream>
using namespace std;

// Tree�� �����ϴ� Node (node data, left ������, right ������)
template<typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;
};

// Binary Search Tree 
template<typename T>
class BinarySearchTree
{
public:
	// ������
	BinarySearchTree();
	// �Ҹ���
	~BinarySearchTree() { }

	/**
	*	@brief	Tree�� Empty���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� ��������� true����, �ƴϸ� false ����
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Tree�� Full���� Ȯ��
	*	@pre	none
	*	@post	none
	*	@return	Tree�� Full�̸� true ����, �ƴϸ� false ����
	*/
	bool IsFull() const;

	/**
	*	@brief	Tree�� ����
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree�� node�� �� ������ Ȯ����
	*	@pre	none
	*	@post	none
	*	@return	Tree�� node ������ ����
	*/
	int GetLength() const;

	/**
	*	@brief	Tree�� �� node�� �߰��Ѵ�
	*	@pre	none
	*   @param  data    �߰��� data
	*	@post	Tree�� �� node�� �߰���
	*/
	void Add(T data);

	/**
	*	@brief	Tree���� ������� �ϴ� node�� ã�� ����
	*	@pre	Tree�� �ʱ�ȭ�Ǿ� �־�� ��
	*   @param  data  ���� ������
	*	@post	Tree���� �Է��� node�� ������
	*/
	void DeleteItem(T data);

	/**
	*	@brief	�Է��� ���� node�� Tree���� �˻���
	*	@pre	ã���� �ϴ� data�� �˻������ ���� found ����
	*	@post	node�� Tree�� �ִ��� �˻������ �˷���
	*/
	void RetrieveItem(T& data, bool &found)const;

	/**
	*	@brief	Tree�� node�� ��ũ���� ����Ѵ�.
	*	@pre	none
	*	@post	��ũ���� Tree�� InOrder, PreOrder, PostOrder ������� ���� ��µ�.
	*/
	void PrintTree(ostream &out)const;

private:
	/**
	*	@brief	tree ��� �ڿ� �� ��� ����
	*	@pre	������ tree�� value�� �ʱ�ȭ�Ǿ� �־�� ��
	*   @param  tree    �̾� ���� ��� Ʈ��
	*   @param  key   ������ ������
	*	@post	Tree�� �� node�� �߰���
	*   @return �߰��� ����� ������
	*/
	Node<T>* Insert(Node<T>* tree, T key);

	/**
	*	@brief	�Է��� ���� node�� Tree���� �˻���
	*	@pre	ã�� ��� tree�� ã���� �ϴ� key ����
	*   @param  tree �˻��� ��� Ʈ��(Ȥ�� ����Ʈ��)
	*   @param  key  �˻��� ������
	*   @return ã�� ����� ������
	*	@post	None
	*/
	Node<T>* Search(Node<T>* tree, T key);

	/**
	*	@brief	���� ������ ��� ������
	*	@pre	�ı��� tree ����
	*   @param  tree �ı��� ��� Ʈ��(Ȥ�� ����Ʈ��)
	*	@post	�Ķ���� tree�� ���� ������ �޸𸮰� ������
	*/
	void DestroyTree(Node<T>* tree);

	/**
	*	@brief	���� ��� �� ���� ���� ū ��带 ã��
	*	@pre	ã�� tree ����
	*   @param  tree �ִ� ã�� ��� Ʈ��(Ȥ�� ����Ʈ��)
	*	@post	None.
	*   @return �ִ� �����ϴ� ����� ������ ��ȯ
	*/
	Node<T>* FindMax(Node<T>* tree);

	/**
	*	@brief	tree ���� ��� �� �ִ��� �� �̸� �����ϴ� ����
	*	@pre	max_node�� tree�� �ִ� ��忩�� ��.
	*   @param  tree ��� ������ ��� Ʈ��(Ȥ�� ����Ʈ��)
	*   @param  max_node  �ִ� ���
	*	@post	max_node�� ���ŵ�
	*   @return ��� ���� �� ���� ��� ��������� �����ϱ� ���� ��ȯ��
	*/
	Node<T>* RemoveMaxNode(Node<T>* tree, Node<T>* max_node);

	/**
	*	@brief	���� ��� �� key�� ���� ��ġ�ϴ� ��� ����
	*	@pre	ã�� tree ����
	*   @param  tree ��� ������ ��� Ʈ��(Ȥ�� ����Ʈ��)
	*   @param  key  ������ ����� key
	*	@post	key�� ��ġ�ϴ� ��尡 ���ŵ�
	*   @return ��� ���� �� ���� ��� �����ϱ� ���� ��ȯ��
	*/
	Node<T>* Remove(Node<T>* tree, T key);



	Node<T>* root;		// Node Ÿ���� root
};

// ������
template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = NULL;
}

// Tree�� ����ִ��� Ȯ��
template<typename T>
bool BinarySearchTree<T>::IsEmpty()const
{
	if (root == NULL)			// root ��尡 NULL�� ��� true ����
		return true;
	else
		return false;			// root ��尡 NULL�� �ƴ� ��� false ����
}

// Tree�� Full���� Ȯ��
template<typename T>
bool BinarySearchTree<T>::IsFull()const
{
	Node* room;					// �ӽ��� node�� �����
	try
	{
		room = new Node;		// �� ��带 �߰��� �� �ִ��� Ȯ��
		delete room;			// �ӽ÷� ���� room ��带 ����
		return false;			// isFull�� ���� false ����
	}
	catch (std::bad_alloc exception)		// �� �̻� ������ �߰��� �� �� ���� Full�� ���
	{
		return true;					// isFull�� ���� true ����
	}
}

// Tree�� ���
template<typename T>
void BinarySearchTree<T>::MakeEmpty()
{
	MakeEmptyTree(root);				// Tree �ʱ�ȭ �Լ� ȣ��
}

// Tree�� node������ �˷���
template<typename T>
int BinarySearchTree<T>::GetLength()const
{
	return CountNodes(root);			// node ������ ���� �Լ� ȣ��
}

// Tree�� ���ο� node �߰�
template<typename T>
void BinarySearchTree<T>::Add(T data)
{
	Insert(root, data);					// �� node �߰��ϴ� �Լ� ȣ��
}

// Tree�� node�� ����
template<typename T>
void BinarySearchTree<T>::DeleteItem(T data)
{
	Delete(root, data);					// �����ϴ� node �����ϴ� �Լ��� ȣ��
}

// Tree���� ã���� �ϴ� ���� node�� �˻�
template<typename T>
void BinarySearchTree<T>::RetrieveItem(T& data, bool &found)const
{
	Retrieve(root, data, found);		// Tree �˻� �Լ� ȣ��
}

// Tree�� node�� ������ ������ �����
template<typename T>
void BinarySearchTree<T>::PrintTree(ostream &out)const
{
	cout << "[InOrder]" << endl;
	PrintInOrderTraversal(root, out);			// InOrder ������� ���
	cout << endl << "[PreOrder]" << endl;
	PrintPreOrderTraversal(root, out);			// PreOrder ������� ���
	cout << endl << "[PostOrder]" << endl;
	PrintPostOrderTraversal(root, out);			// PostOrder ������� ���
}

// tree ������ �� ��� �߰�
template<typename T>
Node<T>* BinarySearchTree<T>::Insert(Node<T>* tree, T key)
{
	// base case : �� Ʈ���� �����Ͽ� �� ��� ����
	if (tree == nullptr) {
		Node<T>* new_tree = new Node;
		new_tree->left = nullptr;
		new_tree->right = nullptr;
		new_tree->data = key;
		return new_tree;
	}

	// �������� ��ҿ� ���� ���� �Ǵ� ������ ����Ʈ���� ����
	if (key < tree->data) {
		// ������ ��带 ���� ����Ʈ���� ����
		// ���Ե� ��� �ƴϸ� ���� tree->left�� �ٲ����� ����
		// (���� ����Ʈ�� �����Ͱ� �״�� ��ȯ�Ǳ� ����)
		tree->left = Insert(tree->left, key);
	}
	else {
		// ũ�ٸ� ������ ����Ʈ���� ����
		tree->right = Insert(tree->right, key);
	}

	return tree;
}

// tree ���� ��� �� data�� key�� ��带 �˻�
template<typename T>
Node<T>* BinarySearchTree<T>::Search(Node<T>* tree, T key)
{
	// ã�ٰ� �� Ʈ���� �����ϸ�, �˻� ����
	if (tree == nullptr) {
		return nullptr;
	}
	// key node�� ã����, ��ȯ�ϰ� ����
	else if (key == tree->data) {
		return tree;
	}
	// �� ���� ��쿡�� ��� ���� ����� ���� �����̳� ������ ����Ʈ���� ��� Ž��
	else if (key < tree->data) {
		return Search(tree->left, key);
	}
	else {
		return Search(tree->right, key);
	}
}

// ���� ���� ��� ����
template<typename T>
void BinarySearchTree<T>::DestroyTree(Node<T>* tree)
{
	if (tree != nullptr) {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		delete tree;
	}
}

// ���� ��� �� ���� ���� ū ��带 ã��
template<typename T>
Node<T>* BinarySearchTree<T>::FindMax(Node<T>* tree)
{
	// ��� ������ ����Ʈ���� ���� Ž��
	if (tree == nullptr) {
		return nullptr;
	}
	if (tree->right == nullptr) {
		return tree;
	}
	return FindMax(tree->right)
}

// �ִ� ��带 �Է¹޾� tree���� �����ϰ� �ٽ� ������ �°� ������
template<typename T>
Node<T>* BinarySearchTree<T>::RemoveMaxNode(Node<T>* tree, Node<T>* max_node)
{
	// defensive coding
	if (tree == nullptr) {
		return NULL;
	}
	// �ִ� ��� ã������ ��ü �۾�
	if (tree == max_node) {
		// �ִ��̸� right�� NULL
		// left subtree�� ���ٸ� null�� ��ȯ�ϰ� �ִ� ���� null�� ��ü�Ǿ� ���ŵ�
		// �ִٸ� ���� ��忡 �����
		return max_node->left;
	}
	// ��� ȣ�⸶�� right subtree�� max node�� ���� Ʈ���� ��ü��
	tree->right = RemoveMaxNode(tree->right, max_node);
}

// ���� ��� �� key�� ���� ��ġ�ϴ� ��� ����
template<typename T>
Node<T>* BinarySearchTree<T>::Remove(Node<T>* tree, T key)
{
	if (tree == nullptr) {
		return nullptr;
	}
	if (tree->data == key) {
		// ���� ��尡 1���� ��
		if (tree->left == nullptr) {
			Node<T>* right_subtree = tree->right;
			delete tree;
			// ���� ��尡 ���ٸ� NULL ��ȯ
			return right_subtree;
		}
		if (tree->right == nullptr) {
			Node<T>* left_subtree = tree->left;
			delete tree;
			// ���� if���� left�� null�� �ƴϾ����Ƿ� ��ȿ�� ��� ��ȯ
			return left_subtree;
		}

		// ���� ����� ���� ����Ʈ���� �ִ��� ���� ���� ��ü�ϱ�
		// ���� ����Ʈ���� � �����ٵ� ũ��, right�����ٴ� ���� �׻� ����
		Node<T>* max_node = FindMax(tree->left); // ����
		max_node->left = RemoveMaxNode(tree->left, max_node); // ����, ����
		max_node->right = tree->right; // ���ŵ� key ��� ��ü
		delete tree;
		return max_node;
	}
	else if (key < tree->data) {
		tree->left = Remove(tree->left, key);
	}
	else {
		tree->right = Remove(tree->right, key);
	}
	return tree;
}

/////////////////////////////Global functions//////////////////////////
// Tree�� �ʱ�ȭ�ϴ� �Լ�
template<typename T>
void MakeEmptyTree(Node<T>*& root)
{
	root = NULL;			// root ��带 Null�� ��
}

// Tree�� node ������ ���� �Լ�
template<typename T>
int CountNodes(Node<T>* root)
{
	if (root == NULL)		// root ��尡 null�ϰ�� 0�� ����
		return 0;
	else
		return CountNodes(root->left) + CountNodes(root->right) + 1;		// ����� ����, �����ʿ� ���� ����� ȣ��� root�� �ش��ϴ� 1�� ���ؼ� ���� ����
}

// BinarySearchTree�� ���ο� ��� �߰�
template<typename T>
void Insert2(Node<T>*& root, T data)
{
	if (root == NULL)				// root�� null�� ��� 
	{
		root = new Node<T>;	// root ��� ����
		root->left = NULL;			// root ����̹Ƿ� left�� right�� NULL�� ����
		root->right = NULL;
		root->data = data;			// root ����� ��
	}
	else if (root->data > data)		// root�� �����ϰ�, �� ���� ���ο� data ������ Ŭ ��
		Insert(root->left, data);	// root�� �������� Insert �Լ� �ٽ� ȣ��
	else if (root->data < data)		// root�� �����ϰ�, �� ���� ���ο� data ������ ���� ��
		Insert(root->right, data);	// root�� ���������� Insert �Լ� �ٽ� ȣ��
}

// ���� ū ���� ã�� �Լ� 
template<typename T>
void GetPredecessor(Node<T> *root, T& data)
{
	while (root->right != NULL)			// root�� �������� ������ ���
		root = root->right;				// root�� ������ ��尪�� root�� ������ �Ѵ�
	data = root->data;					// root ����� ���� data�� �����Ѵ�.
}

// ������� ��带 ã���� ������ Ʈ������ �� ��带 ����� �Լ�
template<typename T>
void DeleteNode(Node<T> *&root)
{
	T data;
	Node<T>* tempPtr;			// �ӽ� ��带 �����ϰ� root ��带 �ӽ� ��忡 ����
	tempPtr = root;

	if (root->left == NULL)				// ���ʳ�尡 ���� ��
	{
		root = root->right;				// ������ ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	}
	else if (root->right == NULL)		// �����ʳ�尡 ���� ��
	{
		root = root->left;				// ���� ��尡 root�� �ǵ��� �����ϰ� �ӽó�带 ����
		delete tempPtr;
	}
	else
	{
		GetPredecessor(root->left, data);	// �߰��� �ִ� ��带 ����� ���� �� (left, right, child ��� ���� ���)
		root->data = data;					// ������� ��庸�� ���� ���� �߿� ���� ū ��带 ã��
		Delete(root->left, data);			// �� ���� ���� ��忡 ���縦 �ؼ� ���� ��ó�� ������
	}
}

// ���� ������� �ϴ� ��带 ã�� recursive �Լ�
template<typename T>
void Delete(Node<T> *&root, T data)
{
	if (data < root->data)				// root��尪���� data��尡 ���� ��
		Delete(root->left, data);		// ���ʳ��� ���� delete�Լ� ȣ��
	else if (data > root->data)			// root��尪���� data��尡 Ŭ ��
		Delete(root->right, data);		// �����ʳ��� ���� delete�Լ� ȣ��
	else
		DeleteNode(root);				// ã���� �ϴ� ���� ��ġ�ϴ� ��� deletenode �Լ� ȣ��
}

// Tree���� node�� �˻��ϴ� �Լ�
template<typename T>
void Retrieve(Node<T> *root, T& data, bool &found)
{
	if (root == NULL)						// root�� NULL�� ��� found�� false 
		found = false;
	else if (data < root->data)				// ã���� �ϴ� �����۰��� root������ ���� �� 
		Retrieve(root->left, data, found);	// ���� ���� ���� retrieve �Լ� ȣ��
	else if (data > root->data)				// ã���� �ϴ� �����۰��� root������ Ŭ ��
		Retrieve(root->right, data, found);	// ������ ���� ���� retrieve �Լ� ȣ��
	else
	{										// ã���� �ϴ� ���� ��ġ�� ��
		data = root->data;					// data�� ��� ������ ����
		found = true;						// found���� true�� �ؼ� ã�� ������ ����
	}
}

// InOrder ������� ����ϴ� �Լ� 
template<typename T>
void PrintInOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintInOrderTraversal(root->left, out);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		out << root->data;							// root ���
		PrintInOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}

// PreOrder ������� ����ϴ� �Լ�
template<typename T>
void PrintPreOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		out << root->data;							// root�� ���� ���
		PrintPreOrderTraversal(root->left, out);	// root�� �������� ���� PreOrder �Լ� �ٽ� ȣ��
		PrintPreOrderTraversal(root->right, out);	// root�� ���������� ���� PreOrder �Լ� �ٽ� ȣ��
	}
}

// PostOrder ������� ����ϴ� �Լ�
template<typename T>
void PrintPostOrderTraversal(Node<T>* root, ostream& out)
{
	if (root != NULL)								// root�� �����ϴ� ���
	{
		PrintPostOrderTraversal(root->left, out);	// root�� �������� ���� �ٽ� PostOrder �Լ� ȣ��
		PrintPostOrderTraversal(root->right, out);	// root�� ���������� ���� �ٽ� PostOrder �Լ� ȣ��
		out << root->data;							// root�� �� ���
	}
}

#endif // !_BINARY_SEARCH_TREE_H