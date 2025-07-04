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
	virtual ~BinaryTree();
	Node* root() const;
	void clear();
	bool isEmpty() const;
	int Height(Node* root) const;
	int Count(Node* root) const;
	virtual int findMinimum(Node* root);
	virtual int findMaximum(Node* root);
	virtual Node* addNode(Node* root, int key);
	void addKey(int key);
	virtual bool removeNode(Node* root, Node* node);
	bool removeNodeKey(int key);
	Node* nlrSearch(Node* root, int key)const;
	virtual std::vector<int> ascendingKey() const;
	BinaryTree& operator=(const BinaryTree& other);
	void printHorizontal(Node* root, int marginLeft = 0, int levelSpacing = 5) const;
private:
	Node* CopyTree(Node* root);
	void clear(Node* node);
	Node* findLeaf(Node* node) const;
	
	
protected:
	virtual Node* findParent(Node* root, Node* node) const;
	virtual void getKeys(Node* root, std::vector<int>& keys) const;
	Node* m_root = nullptr;

};