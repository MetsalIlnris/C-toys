#pragma once

#include"PQueue.h"
//#include"compress.h"
#include<cstdlib>
#include<map>

//const int DefaultSize = 20;//缺省权值集合大小

template<typename Item>
struct huffNode {
	huffNode() {}
	Item data;
	int freq;
	huffNode<Item>* left;
	huffNode<Item>* right;
	huffNode<Item>(Item _c, int f, huffNode<Item>* l = nullptr, huffNode<Item>* r = nullptr)
		: data(_c), freq(f), left(l), right(r) {}
	bool operator<(const huffNode<Item>& node) const { 
		return freq > node.freq;
	}
	bool operator>(const huffNode<Item>& node) const { 
		return freq < node.freq;
	}
};


//**************************************//
//          HUFFMAN  TREE               //
//**************************************//

template<typename Item>
class huffTree {
public:
	huffTree(const std::map<Item, int>& afMap);
	~huffTree();
	void huffmanCode(std::map<Item, std::string>& codeMap);
	huffNode<Item> getHuffTree() { return q.check_head(); }
private:
	static bool _isLeaf(huffNode<Item>* n) {
		return n->left == nullptr && n->right == nullptr;
	}
	void _deleteTree(huffNode<Item>* n);
	void _makehuffTree();
	void _huffmanCode(huffNode<Item>* root, std::string& prefix,
		std::map<Item, std::string>& codeMap);
private:
    PQueue<huffNode<Item>> q;
};

template<typename Item>
huffTree<Item>::huffTree(const std::map<Item, int>& afMap) {
	for (auto i : afMap) {
		huffNode<Item> n(i.first, i.second);
		q.push(n);
	}
	_makehuffTree();
}

template<typename Item>
huffTree<Item>::~huffTree() {
	huffNode<Item> node = q.check_head();
	_deleteTree(node.left);
	_deleteTree(node.right);
}

template<typename Item>
void huffTree<Item>::huffmanCode(std::map<Item, std::string>& codeMap) {
	huffNode<Item> node = q.check_head();
	std::string prefix;
	_huffmanCode(&node, prefix, codeMap);
}

template<typename Item>
void huffTree<Item>::_deleteTree(huffNode<Item>* n) {
	if (!n) return;
	_deleteTree(n->left);
	_deleteTree(n->right);
	delete n;
}

template<typename Item>
void huffTree<Item>::_makehuffTree() {
	while (q.size() != 1) {
		huffNode<Item>* left = new huffNode<Item>(q.check_head()); q.pop();
		huffNode<Item>* right = new huffNode<Item>(q.check_head()); q.pop();
		huffNode<Item> node('R', left->freq + right->freq, left, right);
		q.push(node);
	}
}

template<typename Item>
void huffTree<Item>::_huffmanCode(huffNode<Item>* root, std::string& prefix,
	std::map<Item, std::string>& codeMap) {
	std::string tmp = prefix;
	if (root->left != nullptr) {
		prefix += '0';
		if (_isLeaf(root->left)) {
			codeMap[root->left->data] = prefix;
		}
		else {
			_huffmanCode(root->left, prefix, codeMap);
		}
	}
	if (root->right != nullptr) {
		prefix = tmp;
		prefix += '1';
		if (_isLeaf(root->right)) {
			codeMap[root->right->data] = prefix;
		}
		else {
			_huffmanCode(root->right, prefix, codeMap);
		}
	}
}