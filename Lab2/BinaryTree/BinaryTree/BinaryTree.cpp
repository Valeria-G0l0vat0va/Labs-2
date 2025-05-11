#include<iostream>
#include"BinaryTree.h"
#include <algorithm>

BinaryTree::Node::Node(int key, Node *leftChild, Node *rightChild)
	:m_key(key), m_leftChild(leftChild), m_rightChild(rightChild)
{}

int BinaryTree::Node::key() const
{
	return m_key;
}

void BinaryTree::Node::setKey(const int key)
{
	m_key = key;
}

void BinaryTree::Node::setLeftChild(Node* leftChild)
{
	m_leftChild = leftChild;
}

void BinaryTree::Node::setRightChild(Node* rightChild)
{
	m_rightChild = rightChild;
}

BinaryTree::Node* BinaryTree::Node::getLeftChild() const
{
	return m_leftChild;
}

BinaryTree::Node* BinaryTree::Node::getRightChild() const
{
	return m_rightChild;
}

BinaryTree::BinaryTree(const BinaryTree& other)
{
	m_root = CopyTree(other.m_root);
}

BinaryTree::Node* BinaryTree::CopyTree(Node* root)
{
	if (!root)
		return nullptr;
	Node* newNode = new Node(root->key());
	newNode->setLeftChild(CopyTree(root->getLeftChild()));
	newNode->setRightChild(CopyTree(root->getRightChild()));
	return newNode;
}

BinaryTree::BinaryTree(BinaryTree&& other) 
	:m_root(other.m_root)
{
	other.m_root = nullptr;
}

BinaryTree::~BinaryTree()
{
	clear();
}
BinaryTree::Node* BinaryTree::root() const
{
	return m_root;
}

void BinaryTree::clear()
{
	if (m_root) {
		clear(m_root);
		m_root = nullptr;
	}
}

void BinaryTree::clear(Node* node)
{
	if (!node)
		return;
	clear(node->getLeftChild());
	clear(node->getRightChild());

	delete node;
}

bool BinaryTree::isEmpty() const
{
	return m_root == nullptr;
}

int BinaryTree::Height(Node* root) const
{
	if (!root)
		return 0;
	int leftHeight = Height(root->getLeftChild());
	int rightHeight = Height(root->getRightChild());
	return 1 + std::max(leftHeight, rightHeight);
}

int BinaryTree::Count(Node* root) const
{
	if (!root)
		return 0;
	return 1 + Count(root->getLeftChild()) + Count(root->getRightChild());
}

int BinaryTree::findMinimum(Node* root) {
	if (!root) {
		return INT_MAX;
	}

	int minValue= root->key();

	int leftMinValue = findMinimum(root->getLeftChild());
	int rightMinValue = findMinimum(root->getRightChild());
	if (leftMinValue < minValue)
		minValue = leftMinValue;
	if (rightMinValue < minValue)
		minValue = rightMinValue;

	return minValue;
}

int BinaryTree::findMaximum(Node* root) {
	if (!root) {
		return INT_MIN;
	}

	int maxValue = root->key();

	int leftMaxValue = findMaximum(root->getLeftChild());
	int rightMaxValue = findMaximum(root->getRightChild());
	if (leftMaxValue > maxValue) {
		maxValue = leftMaxValue;
	}
	if (rightMaxValue > maxValue) {
		maxValue = rightMaxValue;
	}
	return maxValue;
}

BinaryTree::Node* BinaryTree::addNode(Node* root, int key)
{
	if (!root)
	{
		root = new Node(key);
	}
	else if (rand() % 2)
	{
		root->setLeftChild(addNode(root->getLeftChild(), key));
	}
	else {
		root->setRightChild(addNode(root->getRightChild(), key));
	}
	return root;
}

void BinaryTree::addKey(int key)
{
	m_root = addNode(m_root, key);
}

bool BinaryTree::removeNode(Node* root, Node* node)
{
	Node* nodeParent = findParent(root, node);
	Node* replacementNode = nullptr;
	if (!node)
		return false;
	if (!node->getLeftChild() && !node->getRightChild()) {
		replacementNode = nullptr;
		if (nodeParent) {
			if (nodeParent->getLeftChild() == node)
				nodeParent->setLeftChild(replacementNode);
			else
				nodeParent->setRightChild(replacementNode);
		}
		else
			root = nullptr;
		delete node;
	}
	else if (!node->getLeftChild() || !node->getRightChild())
	{
		if (node->getLeftChild()) {
			replacementNode->getLeftChild();
		}
		nodeParent->setLeftChild(nullptr);
		delete node;
		nodeParent->setLeftChild(replacementNode);
		if (node->getRightChild()) {
			replacementNode->getRightChild();
		}
		nodeParent->setRightChild(nullptr);
		delete node;
		nodeParent->setRightChild(replacementNode);
	}
	else{
		replacementNode = findSheet(node->getRightChild());
		Node* replacementParent = findParent(root, replacementNode);
		if (replacementParent != node)
		{
			replacementParent->setLeftChild(replacementNode->getRightChild());
			replacementNode->setLeftChild(node->getRightChild());
		}
		replacementNode->setLeftChild(node->getLeftChild());
		if (nodeParent)
		{
			if (nodeParent->getLeftChild() == node)
				nodeParent->setLeftChild(replacementNode);
			else
				nodeParent->setRightChild(replacementNode);
		}
		else
			root = replacementNode;
		
		delete node;
	}
}

BinaryTree::Node* BinaryTree::findSheet(Node* node) const {
	if (!node)
		return nullptr;
	while (node->getLeftChild() || node->getRightChild())
	{
		if (node->getLeftChild())
			node = node->getLeftChild();
		else
			node = node->getRightChild();
	}
	return node;
}

BinaryTree::Node* BinaryTree::findParent(Node* root, Node* node) const
{
	if (!root)
		return nullptr;
	if (root->getLeftChild() == node || root->getRightChild() == node)
		return root;
	Node* leftResult = findParent(root->getLeftChild(), node);
	if (leftResult)
		return leftResult;
	else
		return findParent(root->getRightChild(), node);
}

bool BinaryTree::removeNodeKey(int key)
{
	Node* node = nlrSearch(m_root, key);
	if (!node) {
		return false;
	}
	removeNode(m_root,node);
	return true;
}

BinaryTree::Node* BinaryTree::nlrSearch(Node* root, int key)const
{
	if (!root || root->key() == key) {
		return root;
	}
	Node* subTreeSearchResults = nlrSearch(root->getLeftChild(), key);
	if (!subTreeSearchResults) {
		subTreeSearchResults = nlrSearch(root->getRightChild(), key);
	}
	return subTreeSearchResults;
}

std::vector<int> BinaryTree::ascendingKey() const
{
	std::vector<int> keys;
	getKeys(m_root, keys);
	std::sort(keys.begin(), keys.end());
	return keys;
}
void BinaryTree::getKeys(Node* root, std::vector<int>&keys) const {
	if (!root)
		return;
		getKeys(root->getLeftChild(), keys);
		getKeys(root->getRightChild(), keys);
		keys.push_back(root->key());
}

void BinaryTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) {
		return;
	}
	printHorizontal(root->getRightChild(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->key() << std::endl;
	printHorizontal(root->getLeftChild(), marginLeft + levelSpacing, levelSpacing);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
	if (this != &other) {
		clear();
		m_root = CopyTree(other.m_root);
	}
	return *this;

}