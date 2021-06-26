#include "Tree.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <stddef.h>

Tree::Tree() { this->rootnode = NULL; }
Tree::Tree(int data) {
	TreeNode *node = new TreeNode(data);
	this->rootnode = node;
}

void Tree::insert(int data) {
	TreeNode *node = new TreeNode(data);
	TreeNode *cursor = this->rootnode;

	if (cursor == NULL) {
		this->rootnode = node;
		return;
	}
	while (1) {
		int value = cursor->getData();
		if (value < data) {
			if (cursor->getRight() == NULL) {
				cursor->setRight(node);
				break;
			}
			else {
				cursor = cursor->getRight();
			}
		}
		else {
			if (cursor->getLeft() == NULL) {
				cursor->setLeft(node);
				break;
			}
			else {
				cursor = cursor->getLeft();
			}
		}
	}
	return;
}
void Tree::display() {
	display(this->rootnode);
	return;
}

void Tree::display(TreeNode *curNode) {
	if (curNode == NULL)
		return;

	display(curNode->getLeft());
	std::cout << "  ";
	std::cout << curNode->getData();
	display(curNode->getRight());
	return;
}

bool Tree::search(int data) {
	TreeNode *cursor = this->rootnode;

	if (cursor == NULL) {
		return false;
	}
	while (1) {
		int value = cursor->getData();

		if (value < data) {
			if (cursor->getRight() != NULL) {
				std::cout << " " << value;
				cursor = cursor->getRight();
			}
			else {
				std::cout << " " << value << std::endl;
				std::cout << data << " search failed" << std::endl;
				return false;
			}
		}
		else if (value > data) {
			if (cursor->getLeft() != NULL) {
				std::cout << " " << value;
				cursor = cursor->getLeft();
			}
			else {
				std::cout << " " << value << std::endl;
				std::cout << data << " search success!" << std::endl;
				return false;
			}
		}
		else {
			std::cout << " " << value << std::endl;
			std::cout << data << " search success!" << std::endl;
			return true;
		}
	}
}

int Tree::getMax(TreeNode *curNode) {
	TreeNode *root = curNode->getLeft(); //curNode는 root의 하나 위에 꺼
	int decide = 1;
	while (1) {
		if (root->getRight() != NULL) {
			TreeNode *temp = root;
			root = root->getRight();
			curNode = temp; //root는 오른쪽으로 curNode는 원래 root로
			decide = 2;
		}
		else if (root->getLeft() == NULL && root->getRight() == NULL) {
			int temp = root->getData();
			root = NULL;
			if (decide == 1)
				curNode->setLeft(NULL);
			else if (decide == 2)
				curNode->setRight(NULL);
			return temp;
		}
		else if (root->getLeft() != NULL && root->getRight() == NULL) { //왼쪽은 있고 오른쪽은 없을 때
			int tempnum = root->getData();
			TreeNode *temp = root->getLeft();
			curNode->setRight(temp);
			root = NULL;
			return tempnum;
		}
	}
}

bool Tree::remove(int data) {
	TreeNode *cursor = this->rootnode;
	TreeNode *upNode = NULL;
	int decide = 0;

	if (cursor == NULL) {
		return false;
	}
	while (1) {
		int value = cursor->getData();

		if (value < data) {
			if (cursor->getRight() != NULL) {
				upNode = cursor;
				cursor = cursor->getRight();
				decide = 2;
			}
			else {
				std::cout << data << " remove failed" << std::endl;
				return false;
			}
		}
		else if (value > data) {
			if (cursor->getLeft() != NULL) {
				upNode = cursor;
				cursor = cursor->getLeft();
				decide = 1;
			}
			else {
				std::cout << data << " remove failed" << std::endl;
				return false;
			}
		}
		else if (value == data) {
			if (cursor->getRight() == NULL && cursor->getLeft() == NULL) { //왼쪽 X, 오른쪽 X
				cursor = NULL;
				if (decide == 1) 
					upNode->setLeft(NULL);
				else if (decide == 2)
					upNode->setRight(NULL);
				std::cout << data << " remove success!" << std::endl;
				return true;
			}
			else if (cursor->getRight() == NULL && cursor->getLeft() != NULL) { //왼쪽 O, 오른쪽 X
				if (decide == 1) {
					upNode->setLeft(cursor->getLeft());
					cursor = NULL;
				}
				else if (decide == 2) {
					upNode->setRight(cursor->getLeft());
					cursor = NULL;
				}
				std::cout << data << " remove success!" << std::endl;
				return true;
			}
			else if (cursor->getRight() != NULL && cursor->getLeft() == NULL) { //왼쪽 X, 오른쪽 O
				if (decide == 1) {
					upNode->setLeft(cursor->getRight());
					cursor = NULL;
				}
				else if (decide == 2) {
					upNode->setRight(cursor->getRight());
					cursor = NULL;
				}
				std::cout << data << " remove success!" << std::endl;
				return true;
			}
			else if (cursor->getRight() != NULL && cursor->getLeft() != NULL) {
				int a = getMax(cursor);
				cursor->setData(a);
				std::cout << data << " remove success!" << std::endl;
				return true;
			}
		}
	}
}

