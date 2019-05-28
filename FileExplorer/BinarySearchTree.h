#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <iostream>
using namespace std;

/**
*	트리 순회 방법 종류
*/
enum TraversalMode { INORDER, PREORDER, POSTORDER };

// Tree를 구성하는 Node (node data, left 포인터, right 포인터)
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
	// 생성자
	BinarySearchTree();
	// 소멸자
	~BinarySearchTree() { }

	/**
	*	@brief	Tree가 Empty인지 확인
	*	@pre	none
	*	@post	none
	*	@return	Tree가 비어있으면 true리턴, 아니면 false 리턴
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Tree가 Full인지 확인
	*	@pre	none
	*	@post	none
	*	@return	Tree가 Full이면 true 리턴, 아니면 false 리턴
	*/
	bool IsFull() const;

	/**
	*	@brief	Tree를 비운다
	*	@pre	none
	*	@post	none
	*/
	void MakeEmpty();

	/**
	*	@brief	Tree에 node가 몇 개인지 확인함
	*	@pre	none
	*	@post	none
	*	@return	Tree의 node 개수를 리턴
	*/
	int GetLength() const;

	/**
	*	@brief	Tree에 새 node를 추가한다
	*	@pre	none
	*   @param  data    추가할 data
	*	@post	Tree에 새 node가 추가됨
	*/
	void Insert(T value);

	/**
	*	@brief	Tree에서 지우고자 하는 node를 찾고 지움
	*	@pre	Tree가 초기화되어 있어야 함
	*   @param  data  지울 데이터
	*	@post	Tree에서 입력한 node가 삭제됨
	*/
	void Remove(T data);

	/**
	*	@brief	입력한 값의 node를 Tree에서 검색함
	*	@pre	찾고자 하는 data 설정
	*	@post	node가 Tree에 있는지 검색결과를 알려줌
	*   @retrun 노드를 찾으면 true를 반환
	*/
	bool Search(T& data) const;

	/**
	*	@brief	Tree의 node를 스크린에 출력한다.
	*	@pre	none
	*   @param  os    output stream
	*   @param  order    순회 방법(출력 순서) 지정
	*	@post	스크린에 Tree가 InOrder, PreOrder, PostOrder 방법으로 각각 출력됨.
	*/
	void Print(ostream &os, TraversalMode order) const;

private:
	/**
	*	@brief	tree 노드 뒤에 새 노드 삽입
	*	@pre	삽입할 tree와 value가 초기화되어 있어야 함
	*   @param  tree    이어 붙일 대상 트리
	*   @param  key   삽입할 데이터
	*	@post	Tree에 새 node가 추가됨
	*   @return 추가한 노드의 포인터
	*/
	Node<T>* Insert(Node<T>* tree, T key);

	/**
	*	@brief	입력한 값의 node를 Tree에서 검색함
	*	@pre	찾을 대상 tree와 찾고자 하는 key 설정
	*   @param  tree 검색할 대상 트리(혹은 서브트리)
	*   @param  key  검색할 데이터
	*   @return 찾은 노드의 포인터
	*	@post	None
	*/
	Node<T>* Search(Node<T>* tree, T key);

	/**
	*	@brief	하위 노드들을 모두 제거함
	*	@pre	파괴할 tree 설정
	*   @param  tree 파괴할 대상 트리(혹은 서브트리)
	*	@post	파라미터 tree의 하위 노드들의 메모리가 해제됨
	*/
	void DestroyTree(Node<T>* tree);

	/**
	*	@brief	하위 노드 중 가장 값이 큰 노드를 찾음
	*	@pre	찾을 tree 설정
	*   @param  tree 최댓값 찾을 대상 트리(혹은 서브트리)
	*	@post	None.
	*   @return 최댓값 저장하는 노드의 포인터 반환
	*/
	Node<T>* FindMax(Node<T>* tree);

	/**
	*	@brief	tree 하위 노드 중 최댓값일 때 이를 제거하는 동작
	*	@pre	max_node가 tree의 최댓값 노드여야 함.
	*   @param  tree 노드 제거할 대상 트리(혹은 서브트리)
	*   @param  max_node  최댓값 노드
	*	@post	max_node가 제거됨
	*   @return 노드 제거 후 남은 노드 재귀적으로 갱신하기 위한 반환값
	*/
	Node<T>* RemoveMaxNode(Node<T>* tree, Node<T>* max_node);

	/**
	*	@brief	하위 노드 중 key와 값이 일치하는 노드 제거
	*	@pre	찾을 tree 설정
	*   @param  tree 노드 제거할 대상 트리(혹은 서브트리)
	*   @param  key  제거할 노드의 key
	*	@post	key와 일치하는 노드가 제거됨
	*   @return 노드 제거 후 남은 노드 연결하기 위한 반환값
	*/
	Node<T>* Remove(Node<T>* tree, T key);

	/**
	*	@brief	트리에 포함된 노드의 개수를 셈
	*	@pre	찾을 tree 설정
	*   @param  tree 노드 갯수 셀 대상 트리(혹은 서브트리)
	*	@post	None.
	*   @return 노드의 개수를 반환
	*/
	int CountNodes(Node<T>* tree);

	/**
	*	@brief	트리를 inorder로 순회하며 출력. Left - Center - Right 순서.
	*	@pre	찾을 tree 설정
	*   @param  tree 출력할 대상 트리
	*   @param  os output stream
	*	@post	None.
	*/
	void PrintInOrderTraversal(Node<T>* tree, ostream& os);

	/**
	*	@brief	트리를 preorder로 순회하며 출력. Center - Left - Right 순서.
	*	@pre	찾을 tree 설정
	*   @param  tree 출력할 대상 트리
	*   @param  os output stream
	*	@post	None.
	*/
	void PrintPreOrderTraversal(Node<T>* tree, ostream& os);

	/**
	*	@brief	트리를 postorder로 순회하며 출력. Left - Right - Center 순서.
	*	@pre	찾을 tree 설정
	*   @param  tree 출력할 대상 트리
	*   @param  os output stream
	*	@post	None.
	*/
	void PrintPostOrderTraversal(Node<T>* tree, ostream& os);


	Node<T>* root_;		// Node 타입의 root
};

// 생성자
template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root_ = NULL;
}

// Tree가 비어있는지 확인
template<typename T>
bool BinarySearchTree<T>::IsEmpty()const
{
	if (root_ == NULL)			// root 노드가 NULL인 경우 true 리턴
		return true;
	else
		return false;			// root 노드가 NULL이 아닌 경우 false 리턴
}

// Tree가 Full인지 확인
template<typename T>
bool BinarySearchTree<T>::IsFull()const
{
	Node* room;					// 임시의 node를 만들고
	try
	{
		room = new Node;		// 새 노드를 추가할 수 있는지 확인
		delete room;			// 임시로 만든 room 노드를 지움
		return false;			// isFull에 대한 false 리턴
	}
	catch (std::bad_alloc exception)		// 더 이상 아이템 추가를 할 수 없고 Full일 경우
	{
		return true;					// isFull에 대한 true 리턴
	}
}

// Tree를 비움
template<typename T>
void BinarySearchTree<T>::MakeEmpty()
{
	DestroyTree(root_);
}

// Tree의 node개수를 알려줌
template<typename T>
int BinarySearchTree<T>::GetLength() const
{
	return CountNodes(root_);			// node 개수를 새는 함수 호출
}

// Tree에 새로운 node 추가
template<typename T>
void BinarySearchTree<T>::Insert(T value)
{
	Insert(root_, value);    // root node tree에 추가
}

// Tree의 node를 지움
template<typename T>
void BinarySearchTree<T>::Remove(T data)
{
	Remove(root_, data);					// 존재하는 node 삭제하는 함수를 호출
}

// Tree에서 찾고자 하는 값의 node를 검색
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

// Tree의 node를 스크린에 출력한다.
template<typename T>
void BinarySearchTree<T>::Print(ostream & os, TraversalMode order) const
{
	switch (order)
	{
	case INORDER:
		PrintInOrderTraversal(root_, os);			// InOrder 방법으로 출력
		break;
	case PREORDER:
		PrintPreOrderTraversal(root_, os);			// PreOrder 방법으로 출력
		break;
	case POSTORDER:
		PrintPostOrderTraversal(root_, os);			// PostOrder 방법으로 출력
		break;
	default:
		break;
	}
}

// tree 하위에 새 노드 추가
template<typename T>
Node<T>* BinarySearchTree<T>::Insert(Node<T>* tree, T key)
{
	// base case : 빈 트리에 도달하여 새 노드 삽입
	if (tree == nullptr) {
		Node<T>* new_tree = new Node;
		new_tree->left = nullptr;
		new_tree->right = nullptr;
		new_tree->data = key;
		return new_tree;
	}

	// 데이터의 대소에 따라 왼쪽 또는 오른쪽 서브트리에 삽입
	if (key < tree->data) {
		// 삽입한 노드를 왼쪽 서브트리로 지정
		// 삽입된 경우 아니면 실제 tree->left가 바뀌지는 않음
		// (원래 서브트리 포인터가 그대로 반환되기 때문)
		tree->left = Insert(tree->left, key);
	}
	else {
		// 크다면 오른쪽 서브트리로 지정
		tree->right = Insert(tree->right, key);
	}

	return tree;
}

// tree 하위 노드 중 data가 key인 노드를 검색
template<typename T>
Node<T>* BinarySearchTree<T>::Search(Node<T>* tree, T key)
{
	// 찾다가 빈 트리에 도달하면, 검색 실패
	if (tree == nullptr) {
		return nullptr;
	}
	// key node를 찾으면, 반환하고 끝냄
	else if (key == tree->data) {
		return tree;
	}
	// 그 외의 경우에는 대소 비교한 결과에 따라 왼쪽이나 오른쪽 서브트리를 계속 탐색
	else if (key < tree->data) {
		return Search(tree->left, key);
	}
	else {
		return Search(tree->right, key);
	}
}

// 하위 노드들 모두 제거
template<typename T>
void BinarySearchTree<T>::DestroyTree(Node<T>* tree)
{
	if (tree != nullptr) {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		delete tree;
	}
}

// 하위 노드 중 가장 값이 큰 노드를 찾음
template<typename T>
Node<T>* BinarySearchTree<T>::FindMax(Node<T>* tree)
{
	// 계속 오른쪽 서브트리로 가서 탐색
	if (tree == nullptr) {
		return nullptr;
	}
	if (tree->right == nullptr) {
		return tree;
	}
	return FindMax(tree->right)
}

// 최댓값 노드를 입력받아 tree에서 제거하고 다시 순서에 맞게 연결함
template<typename T>
Node<T>* BinarySearchTree<T>::RemoveMaxNode(Node<T>* tree, Node<T>* max_node)
{
	// defensive coding
	if (tree == nullptr) {
		return NULL;
	}
	// 최댓값 노드 찾았으면 교체 작업
	if (tree == max_node) {
		// 최댓값이면 right는 NULL
		// left subtree가 없다면 null을 반환하고 최댓값 노드는 null로 대체되어 제거됨
		// 있다면 상위 노드에 연결됨
		return max_node->left;
	}
	// 재귀 호출마다 right subtree를 max node가 없는 트리로 교체함
	tree->right = RemoveMaxNode(tree->right, max_node);
}

// 하위 노드 중 key와 값이 일치하는 노드 제거
template<typename T>
Node<T>* BinarySearchTree<T>::Remove(Node<T>* tree, T key)
{
	if (tree == nullptr) {
		return nullptr;
	}
	if (tree->data == key) {
		// 하위 노드가 1개일 때
		if (tree->left == nullptr) {
			Node<T>* right_subtree = tree->right;
			delete tree;
			// 하위 노드가 없다면 NULL 반환
			return right_subtree;
		}
		if (tree->right == nullptr) {
			Node<T>* left_subtree = tree->left;
			delete tree;
			// 앞의 if에서 left가 null이 아니었으므로 유효한 노드 반환
			return left_subtree;
		}

		// 제거 대상의 왼쪽 서브트리의 최댓값을 제거 대상과 교체하기
		// 왼쪽 서브트리의 어떤 값보다도 크고, right값보다는 원래 항상 작음
		Node<T>* max_node = FindMax(tree->left); // 저장
		max_node->left = RemoveMaxNode(tree->left, max_node); // 제거, 정렬
		max_node->right = tree->right; // 제거된 key 노드 대체
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

// 트리에 포함된 노드의 개수를 셈
template<typename T>
int BinarySearchTree<T>::CountNodes(Node<T>* tree)
{
	if (tree == nullptr)		// root 노드가 null일경우 0을 리턴
		return 0;
	else
		// 왼쪽, 오른쪽 서브트리 재귀적으로 호출
		// 호출될 때마다 1 증가
		return CountNodes(tree->left) + CountNodes(tree->right) + 1;		
}

// 트리를 inorder로 순회하며 출력. Left - Center - Right 순서.
template<typename T>
void BinarySearchTree<T>::PrintInOrderTraversal(Node<T>* tree, ostream & os)
{
	if (tree != NULL)								// root가 존재하는 경우
	{
		PrintInOrderTraversal(tree->left, os);		// root의 왼쪽으로 가서 다시 InOrder 함수 호출
		os << tree->data;							// root 출력
		PrintInOrderTraversal(tree->right, os);	// root의 오른쪽으로 가서 다시 InOrder 함수 호출
	}
}

// 트리를 preorder로 순회하며 출력. Center - Left - Right 순서.
template<typename T>
void BinarySearchTree<T>::PrintPreOrderTraversal(Node<T>* tree, ostream & os)
{
	if (tree != NULL)								// root가 존재하는 경우
	{
		out << tree->data;							// root 출력
		PrintInOrderTraversal(tree->left, os);		// root의 왼쪽으로 가서 다시 InOrder 함수 호출
		PrintInOrderTraversal(tree->right, os);	// root의 오른쪽으로 가서 다시 InOrder 함수 호출
	}
}

// 트리를 postorder로 순회하며 출력. Left - Right - Center 순서.
template<typename T>
void BinarySearchTree<T>::PrintPostOrderTraversal(Node<T>* tree, ostream & os)
{
	if (tree != NULL)								// root가 존재하는 경우
	{
		PrintInOrderTraversal(tree->left, os);		// root의 왼쪽으로 가서 다시 InOrder 함수 호출
		PrintInOrderTraversal(tree->right, os);	// root의 오른쪽으로 가서 다시 InOrder 함수 호출
		out << tree->data;							// root 출력
	}
}

#endif // _BINARY_SEARCH_TREE_H