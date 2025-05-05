#pragma once

#include<vector>

class BinaryTree
{
public:
	class Node
	{
	public:
		Node(int key = 0, Node* leftChild = nullptr, Node* rightChild = nullptr);
		~Node() = default;
		int key() const;
		void setKey(const int key);
		void setLeftChild(Node* leftChild);
		void setRightChild(Node* rightChild);
		Node* getLeftChild() const;
		Node* getRightChild() const;

	private:
		int m_key = 0;
		Node* m_leftChild = nullptr;
		Node* m_rightChild = nullptr;
	};
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other);
	~BinaryTree();
	Node* root() const;
	void clear();
	bool isEmpty() const;
	int Height(Node* root) const;
	int Count(Node* root) const;
	int findMinimum(Node* root);
	int findMaximum(Node* root);
	Node* addNode(Node* root, int key);
	bool removeNode(Node* root, Node* node);
	bool removeNodeKey(int key);
	Node* nlrSearch(Node* root, int key)const;
	std::vector<int> ascendingKey() const;
	BinaryTree& operator=(const BinaryTree& other);
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
private:
	Node* CopyTree(Node* root);
	void clear(Node* node);
	Node* findSheet(Node* node) const;
	Node* findParent(Node* root, Node* node) const;
	void getKeys(Node* root, std::vector<int>& keys) const;
	Node* m_root = nullptr;

};