#include <assert.h>
#include <iostream>
#include <stdlib.h>

#include "BinaryTreeTester.h"

BinaryTreeTester::BinaryTreeTester(const bool useConsoleOutput,
                                   const bool enableAllTests)
    : m_useConsoleOutput(useConsoleOutput)
    , m_addAndCountCheckEnabled(enableAllTests)
    , m_destructorCheckEnabled(enableAllTests)
    , m_removeCheckEnabled(enableAllTests)
    , m_clearCheckEnabled(enableAllTests)
    , m_assignCheckEnabled(enableAllTests)
    , m_heightCheckEnabled(enableAllTests)
{}

void BinaryTreeTester::test(const int size)
{
    m_maxSize = size;

    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();
}

bool BinaryTreeTester::useConsoleOutput() const
{
    return m_useConsoleOutput;
}

bool BinaryTreeTester::addAndCountCheckEnabled() const
{
    return m_addAndCountCheckEnabled;
}

bool BinaryTreeTester::destructorCheckEnabled() const
{
    return m_destructorCheckEnabled;
}

bool BinaryTreeTester::removeCheckEnabled() const
{
    return m_removeCheckEnabled;
}

bool BinaryTreeTester::clearCheckEnabled() const
{
    return m_clearCheckEnabled;
}

bool BinaryTreeTester::assignCheckEnabled() const
{
    return m_assignCheckEnabled;
}

bool BinaryTreeTester::heightCheckEnabled() const
{
    return m_heightCheckEnabled;
}

void BinaryTreeTester::setUseConsoleOutput(const bool enabled)
{
    m_useConsoleOutput = enabled;
}

void BinaryTreeTester::setAddAndCountCheckEnabled(const bool enabled)
{
    m_addAndCountCheckEnabled = enabled;
}

void BinaryTreeTester::setDestructorCheckEnabled(const bool enabled)
{
    m_destructorCheckEnabled = enabled;
}

void BinaryTreeTester::setRemoveCheckEnabled(const bool enabled)
{
    m_removeCheckEnabled = enabled;
}

void BinaryTreeTester::setClearCheckEnabled(const bool enabled)
{
    m_clearCheckEnabled = enabled;
}

void BinaryTreeTester::setAssignCheckEnabled(const bool enabled)
{
    m_assignCheckEnabled = enabled;
}

void BinaryTreeTester::setHeightCheckEnabled(const bool enabled)
{
    m_heightCheckEnabled = enabled;
}

int BinaryTreeTester::invalidKey() const
{
    return -(rand() % m_maxSize + 1);
}

BinaryTree *BinaryTreeTester::allocateTree()
{
    return new BinaryTree;
}

void BinaryTreeTester::deallocateTree(BinaryTree *tree)
{
    delete tree;
}

void BinaryTreeTester::addAndCount()
{
    if (!m_addAndCountCheckEnabled) {
        return;
    }

    BinaryTree *tree = allocateTree();
    check_addAndCount(tree, 0);

    std::vector<int> nodeKeys = generateKeys();
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree->addKey(nodeKeys[i]);
        check_addAndCount(tree, i + 1);
    }

    deallocateTree(tree);
}

void BinaryTreeTester::check_addAndCount(const BinaryTree *tree, const int size)
{
    assert(tree->Count(tree->root()) == size);
}

void BinaryTreeTester::destructor()
{
    if (!m_destructorCheckEnabled) {
        return;
    }

    const int runsCount = 200;
	for (int i = 0; i < runsCount; i++)
    {
        BinaryTree *tree = allocateTree();
        std::vector<int> nodeKeys = generateKeys();
        for (int i = 0 ; i < m_maxSize; ++i) {
            tree->addKey(nodeKeys[i]);
        }
		deallocateTree(tree);
    }
    std::cout << "BinaryTreeTester::destructor ended. Press any key to continue..." << std::endl;
	getchar();
	
}

/*
 * [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
 * removedNodeIndex = 3
 * nodeKeys[removedNodeIndex] = 3
 *
 * [0, 1, 2, 4, 5, 6, 7, 8, 9]
 * removedNodeIndex = 4
 * nodeKeys[removedNodeIndex] = 5
 *
 * [0, 1, 2, 4, 6, 7, 8, 9]
 *
 */

void BinaryTreeTester::remove()
{
    if (!m_removeCheckEnabled) {
        return;
    }

    BinaryTree *tree = allocateTree();
    check_remove(tree, invalidKey(), false, 0);

    std::vector<int> nodeKeys = generateKeys();
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree->addKey(nodeKeys[i]);
    }

    while (!nodeKeys.empty()) {
        int removedNodeIndex = rand() % nodeKeys.size();

        check_remove(tree, invalidKey(), false, nodeKeys.size());
        check_remove(tree, nodeKeys[removedNodeIndex], true, nodeKeys.size() - 1);
        nodeKeys.erase(nodeKeys.begin() + removedNodeIndex);

        if (m_useConsoleOutput) {
            tree->printHorizontal(tree->root());
        }
    }

    if (m_useConsoleOutput) {
        tree->printHorizontal(tree->root());
    }

    check_remove(tree, invalidKey(), false, nodeKeys.size());
	deallocateTree(tree);
}

void BinaryTreeTester::check_remove(BinaryTree *tree, const int key,
                                    const bool result, const int size)
{
    assert(tree->removeNodeKey(key) == result);
    assert(tree->Count(tree->root()) == size);
}

void BinaryTreeTester::clear()
{
    if (!m_clearCheckEnabled) {
        return;
    }

    BinaryTree *tree = allocateTree();
	for (int i = 0; i < 200; i++)
    {
        std::vector<int> nodeKeys = generateKeys();
        for (int i = 0 ; i < m_maxSize; ++i) {
            tree->addKey(nodeKeys[i]);
        }
		tree->clear();
		check_clear(tree, 0);
    }
    deallocateTree(tree);
    std::cout << "BinaryTreeTester::clear ended. Press any key to continue..." << std::endl;
	getchar();
}

void BinaryTreeTester::check_clear(const BinaryTree *tree, const int size)
{
    assert(tree->Count(tree->root()) == size);
}

void BinaryTreeTester::assign()
{
    if (!m_assignCheckEnabled) {
        return;
    }

    BinaryTree tree1;

    std::vector<int> nodeKeys = generateKeys();
    for (int i = 0 ; i < m_maxSize; ++i) {
        tree1.addKey(nodeKeys[i]);
    }

    BinaryTree tree2 = tree1; //Конструктор копирования
    check_assign(&tree1, &tree2);

    tree1 = tree1; //Присваивание самому себе
    check_assign(&tree1, &tree2); //Проверяем, что tree1 не сломалось

    tree1 = tree2; //Присваивание одинаковых по размеру деревьев
    check_assign(&tree1, &tree2);

    BinaryTree tree3;
    tree1 = tree3; //Присваивание дерева меньшего размера
    check_assign(&tree1, &tree3);

    tree3 = tree2; //Присваивание дерева большего размера
    check_assign(&tree2, &tree3);
}

void BinaryTreeTester::check_assign(const BinaryTree *first,
                                    const BinaryTree *second)
{
    const int size = first->Count(first->root());
    assert(size == second->Count(second->root()));

    TreeNodes firstTreeNodes = treeNodes(first);
    TreeNodes secondTreeNodes = treeNodes(second);

    for (int i = 0; i < size; ++i) {
        assert(firstTreeNodes[i] != secondTreeNodes[i]);
        assert(firstTreeNodes[i]->key() == secondTreeNodes[i]->key());
    }
}

BinaryTreeTester::TreeNodes BinaryTreeTester::treeNodes(const BinaryTree *tree)
{
    TreeNodes nodes;
	
    TreeNodes nodesToProcess;
	nodesToProcess.push_back(tree->root());
	while (!nodesToProcess.empty()) {
        BinaryTree::Node *node = nodesToProcess.front();
		if (node != nullptr) {
            nodesToProcess.push_back(node->getLeftChild());
            nodesToProcess.push_back(node->getRightChild());
			nodes.push_back(node);
        }
        nodesToProcess.erase(nodesToProcess.begin());
	}
	
	return nodes;
}

std::vector<int> BinaryTreeTester::generateKeys()
{
    std::vector<int> orderedKeys;
    for (int i = 0; i < m_maxSize; ++i) {
        orderedKeys.push_back(i);
    }

    std::vector<int> keys;
    while (!orderedKeys.empty()) {
        int i = rand() % orderedKeys.size();
        keys.push_back(orderedKeys[i]);
        orderedKeys.erase(orderedKeys.begin() + i);
    }

    return keys;
}

void BinaryTreeTester::height()
{
    if (!m_heightCheckEnabled) {
        return;
    }

    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTester::check_height(const BinaryTree &tree, const int height)
{
    assert(tree.Height(tree.root()) == height);
}

void BinaryTreeTester::height_trivialCases()
{
    BinaryTree tree;
    check_height(tree, 0);
    tree.addKey(0);
    check_height(tree, 1);
}

void BinaryTreeTester::height_longOnlyLeftSubtree()
{
    BinaryTree longTree;
    longTree.addKey(0);
    BinaryTree::Node *runner = longTree.root();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setLeftChild(new BinaryTree::Node(i));
        runner = runner->getLeftChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyRightSubtree()
{
    BinaryTree longTree;
    longTree.addKey(0);
    BinaryTree::Node *runner = longTree.root();
    for (int i = 1; i < m_maxSize; ++i) {
        runner->setRightChild(new BinaryTree::Node(i));
        runner = runner->getRightChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    BinaryTree longTree;
    longTree.addKey(0);
    BinaryTree::Node *leftRunner = longTree.root();
    BinaryTree::Node *rightRunner = longTree.root();
    for (int i = 1; i < m_maxSize/2; ++i) {
        leftRunner->setLeftChild(new BinaryTree::Node(i));
        leftRunner = leftRunner->getLeftChild();
        check_height(longTree, i + 1);
        
        rightRunner->setRightChild(new BinaryTree::Node(i));
        rightRunner = rightRunner->getRightChild();
        check_height(longTree, i + 1);
    }
}

void BinaryTreeTester::height_longRandomZigzagSubtrees()
{
    BinaryTree longTree;
    longTree.addKey(0);
    BinaryTree::Node *leftRunner = longTree.root();
    BinaryTree::Node *rightRunner = longTree.root();

    leftRunner->setLeftChild(new BinaryTree::Node(1));
    leftRunner = leftRunner->getLeftChild();
    rightRunner->setRightChild(new BinaryTree::Node(1));
    rightRunner = rightRunner->getRightChild();

    for (int i = 2; i < m_maxSize/2; ++i) {
        if (rand() % 2 == 0) 
        {
            leftRunner->setLeftChild(new BinaryTree::Node(i));
            leftRunner = leftRunner->getLeftChild();
        }
        else 
        {
            leftRunner->setRightChild(new BinaryTree::Node(i));
            leftRunner = leftRunner->getRightChild();
        }
        check_height(longTree, i + 1);

        if (rand() % 2 == 0)
        {
            rightRunner->setLeftChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getLeftChild();
        }
        else 
        {
            rightRunner->setRightChild(new BinaryTree::Node(i));
            rightRunner = rightRunner->getRightChild();
        }
        check_height(longTree, i + 1);
    }
}
