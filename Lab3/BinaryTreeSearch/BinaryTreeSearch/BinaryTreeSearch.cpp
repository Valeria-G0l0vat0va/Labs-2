#include"BinaryTreeSearch.h"

BinaryTreeSearch::BinaryTreeSearch()
	:BinaryTree()
{}

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other)
	:BinaryTree(other)
{}

int BinaryTreeSearch::findMinimum(Node* root)
{
	Node* nimNode = findMin(root);
	if (minNode)
		return INT_MAX;
	return minNode->key();
}

int BinaryTreeSearch::findMaximum(Node* root)
{
	if (!root)
		return INT_MIN;
	while (root->getRightChild())
		root = root->getRightChild();
	return root->key();
}

BinaryTreeSearch::Node* BinaryTreeSearch::addNode(Node* root, int key) 
{
	if (!root)
	{
		root = new Node(key);
	}
	else if (key<root->key())
	{
		root->setLeftChild(addNode(root->getLeftChild(), key));
	}
	else {
		root->setRightChild(addNode(root->getRightChild(), key));
	}
	return root;
}

bool BinaryTreeSearch::removeNode(Node* root, Node* node)
{
	if (!node)
		return false;
	Node* nodeParent = findParent(root, node);
	Node* replacementNode = nullptr;
	if (!node->getLeftChild() && !node->getRightChild()) {
		replacementNode = nullptr;
	}
	else if (!node->getLeftChild() || !node->getRightChild())
	{
		if (node->getLeftChild()) {
			replacementNode = node->getLeftChild();
		}
		else
			replacementNode = node->getRightChild();
	}
	else
	{
		replacementNode = findMin(node->getRightChild());
		Node* replacementParent = findParent(root, replacementNode);
		if (replacementNode != node->getRightChild())
		{
			if (replacementParent) {
				if (replacementParent->getLeftChild() == replacementNode)
					replacementParent->setLeftChild(nullptr);
				else
					replacementParent->setRightChild(nullptr);
			}
			replacementNode->setRightChild(node->getRightChild());
		}
		replacementNode->setLeftChild(node->getLeftChild());

	}
	if (nodeParent) {
		if (nodeParent->getLeftChild() == node)
			nodeParent->setLeftChild(replacementNode);
		else
			nodeParent->setRightChild(replacementNode);
	}
	else
		m_root = replacementNode;
	delete node;
	return true;
}

BinaryTreeSearch::Node* BinaryTreeSearch::findMin(Node* node) const {
	if (!node)
		return nullptr;
	while (node->getLeftChild()) {
		node = node->getLeftChild();
	}
	return node;
}

BinaryTreeSearch::Node* BinaryTreeSearch::findParent(Node* root, Node* node) const
{
	if (!root)
		return nullptr;
	if (root->getLeftChild() == node || root->getRightChild() == node)
		return root;
	if (node->key() < root->key())
		return findParent(root->getLeftChild(),node);
	else
		return findParent(root->getRightChild(), node);
}


std::vector<int> BinaryTreeSearch::ascendingKey() const
{
	std::vector<int> keys;
	getKeys(m_root, keys);
	return keys;
}
void BinaryTreeSearch::getKeys(Node* root, std::vector<int>& keys) const {
	if (!root)
		return;
	getKeys(root->getLeftChild(), keys);
	keys.push_back(root->key());
	getKeys(root->getRightChild(), keys);
}
	