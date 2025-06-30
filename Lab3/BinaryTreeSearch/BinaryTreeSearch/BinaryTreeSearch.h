#pragma once
#include "../../../Lab2/BinaryTree/BinaryTree/BinaryTree.h"
#include<vector>


class BinaryTreeSearch : public BinaryTree
{
public:
	BinaryTreeSearch();
	BinaryTreeSearch(const BinaryTreeSearch& other);
	~BinaryTreeSearch() override = default;
	BinaryTreeSearch& operator=(const BinaryTreeSearch& other) = default;
	using BinaryTree::addKey;
	using BinaryTree::removeNodeKey;
protected:
	int findMinimum(Node* root) override;
	int findMaximum(Node* root) override;
	Node* addNode(Node* root, int key) override;
	bool removeNode(Node* root, Node* node) override;
	std::vector<int> ascendingKey() const override;
	void getKeys(Node* root, std::vector<int>& keys) const override;
	Node* findParent(Node* root, Node* node) const override;
private:
	Node* findMin(Node* node) const;
};
	