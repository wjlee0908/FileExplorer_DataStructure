#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <iostream>
using namespace std;

/**
*	Ʈ�� ��ȸ ��� ����
*/
enum TraversalMode { INORDER, PREORDER, POSTORDER };

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
	void Insert(T value);

	/**
	*	@brief	Tree���� ������� �ϴ� node�� ã�� ����
	*	@pre	Tree�� �ʱ�ȭ�Ǿ� �־�� ��
	*   @param  data  ���� ������
	*	@post	Tree���� �Է��� node�� ������
	*/
	void Remove(T data);

	/**
	*	@brief	�Է��� ���� node�� Tree���� �˻���
	*	@pre	ã���� �ϴ� data ����
	*	@post	node�� Tree�� �ִ��� �˻������ �˷���
	*   @retrun ��带 ã���� true�� ��ȯ
	*/
	bool Search(T& data) const;

	/**
	*	@brief	Tree�� node�� ��ũ���� ����Ѵ�.
	*	@pre	none
	*   @param  os    output stream
	*   @param  order    ��ȸ ���(��� ����) ����
	*	@post	��ũ���� Tree�� InOrder, PreOrder, PostOrder ������� ���� ��µ�.
	*/
	void Print(ostream &os, TraversalMode order) const;

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

	/**
	*	@brief	Ʈ���� ���Ե� ����� ������ ��
	*	@pre	ã�� tree ����
	*   @param  tree ��� ���� �� ��� Ʈ��(Ȥ�� ����Ʈ��)
	*	@post	None.
	*   @return ����� ������ ��ȯ
	*/
	int CountNodes(Node<T>* tree);

	/**
	*	@brief	Ʈ���� inorder�� ��ȸ�ϸ� ���. Left - Center - Right ����.
	*	@pre	ã�� tree ����
	*   @param  tree ����� ��� Ʈ��
	*   @param  os output stream
	*	@post	None.
	*/
	void PrintInOrderTraversal(Node<T>* tree, ostream& os);

	/**
	*	@brief	Ʈ���� preorder�� ��ȸ�ϸ� ���. Center - Left - Right ����.
	*	@pre	ã�� tree ����
	*   @param  tree ����� ��� Ʈ��
	*   @param  os output stream
	*	@post	None.
	*/
	void PrintPreOrderTraversal(Node<T>* tree, ostream& os);

	/**
	*	@brief	Ʈ���� postorder�� ��ȸ�ϸ� ���. Left - Right - Center ����.
	*	@pre	ã�� tree ����
	*   @param  tree ����� ��� Ʈ��
	*   @param  os output stream
	*	@post	None.
	*/
	void PrintPostOrderTraversal(Node<T>* tree, ostream& os);


	Node<T>* root_;		// Node Ÿ���� root
};

// ������
template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root_ = NULL;
}

// Tree�� ����ִ��� Ȯ��
template<typename T>
bool BinarySearchTree<T>::IsEmpty()const
{
	if (root_ == NULL)			// root ��尡 NULL�� ��� true ����
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
	DestroyTree(root_);
}

// Tree�� node������ �˷���
template<typename T>
int BinarySearchTree<T>::GetLength() const
{
	return CountNodes(root_);			// node ������ ���� �Լ� ȣ��
}

// Tree�� ���ο� node �߰�
template<typename T>
void BinarySearchTree<T>::Insert(T value)
{
	Insert(root_, value);    // root node tree�� �߰�
}

// Tree�� node�� ����
template<typename T>
void BinarySearchTree<T>::Remove(T data)
{
	Remove(root_, data);					// �����ϴ� node �����ϴ� �Լ��� ȣ��
}

// Tree���� ã���� �ϴ� ���� node�� �˻�
template<typename T>
bool BinarySearchTree<T>::Search(T& data) const
{
	Node<T>* found_node = Search(root_, data);
	if (found_node != nullptr) {
		data = found_node->data;
		return true;
	}
	else {
		return false;
	}
}

// Tree�� node�� ��ũ���� ����Ѵ�.
template<typename T>
void BinarySearchTree<T>::Print(ostream & os, TraversalMode order) const
{
	switch (order)
	{
	case INORDER:
		PrintInOrderTraversal(root_, os);			// InOrder ������� ���
		break;
	case PREORDER:
		PrintPreOrderTraversal(root_, os);			// PreOrder ������� ���
		break;
	case POSTORDER:
		PrintPostOrderTraversal(root_, os);			// PostOrder ������� ���
		break;
	default:
		break;
	}
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

// Ʈ���� ���Ե� ����� ������ ��
template<typename T>
int BinarySearchTree<T>::CountNodes(Node<T>* tree)
{
	if (tree == nullptr)		// root ��尡 null�ϰ�� 0�� ����
		return 0;
	else
		// ����, ������ ����Ʈ�� ��������� ȣ��
		// ȣ��� ������ 1 ����
		return CountNodes(tree->left) + CountNodes(tree->right) + 1;		
}

// Ʈ���� inorder�� ��ȸ�ϸ� ���. Left - Center - Right ����.
template<typename T>
void BinarySearchTree<T>::PrintInOrderTraversal(Node<T>* tree, ostream & os)
{
	if (tree != NULL)								// root�� �����ϴ� ���
	{
		PrintInOrderTraversal(tree->left, os);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		os << tree->data;							// root ���
		PrintInOrderTraversal(tree->right, os);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}

// Ʈ���� preorder�� ��ȸ�ϸ� ���. Center - Left - Right ����.
template<typename T>
void BinarySearchTree<T>::PrintPreOrderTraversal(Node<T>* tree, ostream & os)
{
	if (tree != NULL)								// root�� �����ϴ� ���
	{
		out << tree->data;							// root ���
		PrintInOrderTraversal(tree->left, os);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		PrintInOrderTraversal(tree->right, os);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
	}
}

// Ʈ���� postorder�� ��ȸ�ϸ� ���. Left - Right - Center ����.
template<typename T>
void BinarySearchTree<T>::PrintPostOrderTraversal(Node<T>* tree, ostream & os)
{
	if (tree != NULL)								// root�� �����ϴ� ���
	{
		PrintInOrderTraversal(tree->left, os);		// root�� �������� ���� �ٽ� InOrder �Լ� ȣ��
		PrintInOrderTraversal(tree->right, os);	// root�� ���������� ���� �ٽ� InOrder �Լ� ȣ��
		out << tree->data;							// root ���
	}
}

#endif // _BINARY_SEARCH_TREE_H