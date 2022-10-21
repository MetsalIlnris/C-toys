#pragma once

//用链表实现二叉树

#include<iostream>
#include<cstdlib>
#include"Queue.h"

template<typename>struct TreeNode;
template<typename Item>std::ostream& operator<<(std::ostream& os, const TreeNode<Item>& TNode);

//二叉树的结点

template<typename Item>
struct TreeNode {
	Item data;
	TreeNode<Item>* rightChild;
	TreeNode<Item>* leftChild;
	TreeNode<Item>* parent;
	void clearNode();
	void assignAsLeaf(Item item) { data = item; rightChild = NULL; leftChild = NULL; }
	friend std::ostream& operator<< <Item>(std::ostream& os, const TreeNode<Item>& TNode);
};

template<typename Item>
void TreeNode<Item>::clearNode() {
	if (this != NULL) {
		if (rightChild != NULL)rightChild->clearNode();
		if (leftChild != NULL)leftChild->clearNode();
		delete this;
	}
}

template<typename Item>
std::ostream& operator<< (std::ostream& os, const TreeNode<Item>& TNode) {
	std::cout << TNode.data;
	return os;
}

//二叉树定义

template<typename Item>
class BinaryTree
{
private:
	int Height;
protected:
	struct TreeNode<Item>* root;
	int NodeAmount;

public:
	BinaryTree();
	BinaryTree(BinaryTree& BT);
	~BinaryTree();

	void clear() { root->clearNode(); root = NULL; } //清空二叉树
	int height() { return Height; }
	int size() { return NodeAmount; }
	bool isempty() { return root == NULL; }

	bool swapTree();
	Queue<TreeNode<Item>> find(Item item);
private:
	bool swapTree(TreeNode<Item>*& root);
	bool find(Item& item, TreeNode<Item>*& root,Queue<TreeNode<Item>>& finderQueue);

	//四种遍历方法
public:
	void preOrder();
	void inOrder();
	void postOrder();
	void levelOrder();

	//四种遍历方法调用的内部函数
private:
	void preOrder(TreeNode<Item>*& BTroot);
	void inOrder(TreeNode<Item>*& BTroot);
	void postOrder(TreeNode<Item>*& BTroot);
	void levelOrder(TreeNode<Item>*& BTroot);

};

//****************构造函数****************

template<typename Item>
BinaryTree<Item>::BinaryTree() {
	root = NULL;
	NodeAmount = 0;
	Height = 0;
}

template<typename Item>
BinaryTree<Item>::BinaryTree(BinaryTree& BT) {

}

template<typename Item>
BinaryTree<Item>::~BinaryTree() {
	clear();
}

//**************** swap & find ****************

template<typename Item>
bool BinaryTree<Item>::swapTree() {
	if (root->rightChild != NULL)swapTree(root->rightChild);
	if (root->leftChild != NULL)swapTree(root->leftChild);
	TreeNode<Item>* cac = root->leftChild;
	root->leftChild = root->rightChild;
	root->rightChild = cac;
	return true;
}

template<typename Item>
bool BinaryTree<Item>::swapTree(TreeNode<Item>*& root) {
	if (root->rightChild != NULL)swapTree(root->rightChild);
	if (root->leftChild != NULL)swapTree(root->leftChild);
	TreeNode<Item>* cac = root->leftChild;
	root->leftChild = root->rightChild;
	root->rightChild = cac;
	return true;
}

template<typename Item>
Queue<TreeNode<Item>> BinaryTree<Item>::find(Item item) {
	Queue<TreeNode<Item>> finderQueue;
	if (root->data = item) {
		finderQueue.push(*root);
		return finderQueue;//如果找到直接退出
	}
	if (root->rightChild != NULL) {
		if (find(item, root->rightChild, finderQueue)) {
			finderQueue.push(*root);
			return finderQueue;//如果找到直接退出
		}
	}
	if (root->leftChild != NULL) {
		if (find(item, root->leftChild, finderQueue)) {
			finderQueue.push(*root);
			return finderQueue;//如果找到直接退出
		}
	}
	return finderQueue;
}

template<typename Item>
bool BinaryTree<Item>::find(Item& item, TreeNode<Item>*& root,Queue<TreeNode<Item>>& finderQueue) {
	if (root->data = item) {
		finderQueue.push(*root);
		return true;//如果找到直接退出
	}
	if (root->rightChild != NULL) {
		if (find(item, root->rightChild, finderQueue)) {
			finderQueue.push(*root);
			return true;//如果找到直接退出
		}
	}
	if (root->leftChild != NULL) {
		if (find(item, root->leftChild, finderQueue)) {
			finderQueue.push(*root);
			return true;//如果找到直接退出
		}
	}
	else return false;
}

//二叉树遍历：7个方法

template<typename Item>
void BinaryTree<Item>::preOrder() {
	std::cout << *root << ' ';
	if (root->rightChild != NULL)preOrder(root->rightChild);
	if (root->leftChild != NULL)preOrder(root->leftChild);
}

template<typename Item>
void BinaryTree<Item>::inOrder() {
	if (root->rightChild != NULL)inOrder(root->rightChild);
	std::cout << *root << ' ';
	if (root->leftChild != NULL)inOrder(root->leftChild);
}

template<typename Item>
void BinaryTree<Item>::postOrder() {
	if (root->rightChild != NULL)postOrder(root->rightChild);
	if (root->leftChild != NULL)postOrder(root->leftChild);
	std::cout << *root << ' ';
}

template<typename Item>
void BinaryTree<Item>::levelOrder() {
	Queue<TreeNode<Item>*> cache;
	TreeNode<Item>* cur = root;
	while (cur != NULL) {
		std::cout << *cur;
		if (cur->leftChild != NULL)cache.push(cur->leftChild);
		if (cur->rightChild != NULL)cache.push(cur->rightChild);
		if (!cache.pop(cur))break;
	}
}

template<typename Item>
void BinaryTree<Item>::preOrder(TreeNode<Item>*& BTroot) {
	std::cout << *BTroot << ' ';
	if (BTroot->leftChild != NULL)preOrder(BTroot->leftChild);
	if (BTroot->rightChild != NULL)preOrder(BTroot->rightChild);
}

template<typename Item>
void BinaryTree<Item>::inOrder(TreeNode<Item>*& BTroot) {
	if (BTroot->leftChild != NULL)inOrder(BTroot->leftChild);
	std::cout << *BTroot << ' ';
	if (BTroot->rightChild != NULL)inOrder(BTroot->rightChild);
}

template<typename Item>
void BinaryTree<Item>::postOrder(TreeNode<Item>*& BTroot) {
	if (BTroot->leftChild != NULL)inOrder(BTroot->leftChild);
	if (BTroot->rightChild != NULL)inOrder(BTroot->rightChild);
	std::cout << *BTroot << ' ';
}