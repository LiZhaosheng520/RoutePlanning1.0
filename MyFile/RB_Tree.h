#pragma once
#include<string>  
#include<sstream>  
#include<fstream>  
#include<vector>
#include "RoutePlanning1.0Dlg.h"
using namespace std;
class RB_Tree
{
public:
	struct Node* m_nullNode;         //新的结点
	struct Node* m_root;            //根结点
public:
	RB_Tree()            //默认构造函数  红黑树的初始化
	{
		
		this->m_nullNode = new struct Node();
		this->m_root = m_nullNode;
		this->m_nullNode->right = this->m_root;
		this->m_nullNode->left = this->m_root;
		this->m_nullNode->parent = this->m_root;
		this->m_nullNode->RB_COLOR = BLACK;
	}
	bool Empty();
	struct Node* RB_find(float x, float y, float z,struct Node* m_index);
	bool Insert(float x, float y, float z, struct Node* m_index);
	void InsertFixUp(struct Node* node);
	bool RotateLeft(struct Node* node);
	bool RotateRight(struct Node* node);
	bool Delete(float x, float y, float z);
	void DeleteFixUp(struct Node* node);
	inline struct Node* RB_Tree::InOrderSuccessor(struct Node* node);
	void InOrderTraverse(struct Node* node);

};
