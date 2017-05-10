
#include "RB_Tree.h"

using namespace std;

bool RB_Tree::Empty()           //判断是否为空, 真为1
{
	if (this->m_root == this->m_nullNode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

struct Node* RB_Tree::RB_find(float x, float y, float z, struct Node* m_index)          //查询
{
	//struct Node* m_index = m_root;       //根结点指针
	while (m_index != m_nullNode)
	{
		if ((x < m_index->vertex[0]) || ((x == m_index->vertex[0]) && (y < m_index->vertex[1])) || ((x == m_index->vertex[0]) && (y == m_index->vertex[1]) && (z < m_index->vertex[2])))
		{
			m_index = m_index->left;
		}
		else if ((x > m_index->vertex[0]) || ((x == m_index->vertex[0]) && (y > m_index->vertex[1])) || ((x == m_index->vertex[0]) && (y == m_index->vertex[1]) && (z > m_index->vertex[2])))
		{
			m_index = m_index->right;
		}
		else
		{
			break;
		}
	}
	return m_index;
}

/*插入结点*/
bool RB_Tree::Insert(float x, float y, float z,struct Node* m_index)
{
	struct Node* insert_point = m_nullNode;
	//struct Node* m_index = m_root;
	while (m_index != m_nullNode)
	{
		insert_point = m_index;
		if ((x < m_index->vertex[0]) || ((x == m_index->vertex[0]) && (y < m_index->vertex[1])) || ((x == m_index->vertex[0]) && (y == m_index->vertex[1]) && (z < m_index->vertex[2])))
		{
			m_index = m_index->left;
		}
		else if ((x > m_index->vertex[0]) || ((x == m_index->vertex[0]) && (y > m_index->vertex[1])) || ((x == m_index->vertex[0]) && (y == m_index->vertex[1]) && (z > m_index->vertex[2])))
		{
			m_index = m_index->right;
		}
		else
		{
			return false;       //说明树中存在要插入的数，返回false
		}
	}
	struct Node* insert_node = new struct Node();
	insert_node->vertex[0] = x;
	insert_node->vertex[1] = y;
	insert_node->vertex[2] = z;
	insert_node->RB_COLOR = RED;
	insert_node->right = m_nullNode;
	insert_node->left = m_nullNode;
	if (insert_point == m_nullNode)       //如果插入时是一棵空树
	{
		m_root = insert_node;
		m_root->parent = m_nullNode;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		m_nullNode->parent = m_root;
	}
	else
	{
		if ((x < insert_point->vertex[0]) || ((x == insert_point->vertex[0]) && (y < insert_point->vertex[1])) || ((x == insert_point->vertex[0]) && (y == insert_point->vertex[1]) && (z < insert_point->vertex[2])))
		{
			insert_point->left = insert_node;
		}
		else
		{
			insert_point->right = insert_node;
		}
		insert_node->parent = insert_point;
	}
	InsertFixUp(insert_node);    //调用InsertFixUp修复红黑树性质
	return true;
}

/*修复红黑树性质*/
void  RB_Tree::InsertFixUp(struct Node* node)
{
	while (node->parent->RB_COLOR == RED)
	{
		if (node->parent == node->parent->parent->left)   //  
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->RB_COLOR == RED)   //插入情况1，z的叔叔y是红色的。  
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)  //插入情况2：z的叔叔y是黑色的，。  
			{
				if (node == node->parent->right) //且z是右孩子  
				{
					node = node->parent;
					RotateLeft(node);
				}
				//else                 //插入情况3：z的叔叔y是黑色的，但z是左孩子。  
				//{  
				node->parent->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				RotateRight(node->parent->parent);
				//}
			}
		}
		else //这部分是针对为插入情况1中，z的父亲现在作为祖父的右孩子了的情况，而写的。  
			 //15 else (same as then clause with "right" and "left" exchanged)  
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->RB_COLOR == RED)
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				uncle->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);     //与上述代码相比，左旋改为右旋  
				}
				//else  
				//{  
				node->parent->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				RotateLeft(node->parent->parent);   //右旋改为左旋，即可。  
													//}  
			}
		}
	}
	m_root->RB_COLOR = BLACK;
}
/*左旋代码实现*/
bool  RB_Tree::RotateLeft(struct Node* node)
{
	if (node == m_nullNode || node->right == m_nullNode)
	{
		return false;//can't rotate  
	}
	struct Node* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != m_nullNode)
	{
		lower_right->left->parent = node;
	}
	if (node->parent == m_nullNode) //rotate node is root  
	{
		m_root = lower_right;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		//m_nullNode->parent = m_root;  
	}
	else
	{
		if (node == node->parent->left)
		{
			node->parent->left = lower_right;
		}
		else
		{
			node->parent->right = lower_right;
		}
	}
	node->parent = lower_right;
	lower_right->left = node;
	return true;
}

//右旋代码实现  
bool  RB_Tree::RotateRight(struct Node* node)
{
	if (node == m_nullNode || node->left == m_nullNode)
	{
		return false;//can't rotate  
	}
	struct Node* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != m_nullNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == m_nullNode) //node is root  
	{
		m_root = lower_left;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		//m_nullNode->parent = m_root;  
	}
	else
	{
		if (node == node->parent->right)
		{
			node->parent->right = lower_left;
		}
		else
		{
			node->parent->left = lower_left;
		}
	}
	node->parent = lower_left;
	lower_left->right = node;
	return true;
}
bool RB_Tree::Delete(float x, float y, float z)
{
	Node* delete_point = RB_find(x, y, z,m_root);
	if (delete_point == m_nullNode)
	{
		return false;
	}
	if (delete_point->left != m_nullNode && delete_point->right != m_nullNode)
	{
		struct Node* successor = InOrderSuccessor(delete_point);
		delete_point->vertex[0] = successor->vertex[0];
		delete_point->vertex[1] = successor->vertex[1];
		delete_point->vertex[2] = successor->vertex[2];
		delete_point = successor;
	}
	struct Node* delete_point_child;
	if (delete_point->right != m_nullNode)
	{
		delete_point_child = delete_point->right;
	}
	else if (delete_point->left != m_nullNode)
	{
		delete_point_child = delete_point->left;
	}
	else
	{
		delete_point_child = m_nullNode;
	}
	delete_point_child->parent = delete_point->parent;
	if (delete_point->parent == m_nullNode)//delete root node  
	{
		m_root = delete_point_child;
		m_nullNode->parent = m_root;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
	}
	else if (delete_point == delete_point->parent->right)
	{
		delete_point->parent->right = delete_point_child;
	}
	else
	{
		delete_point->parent->left = delete_point_child;
	}
	if (delete_point->RB_COLOR == BLACK && !(delete_point_child == m_nullNode && delete_point_child->parent == m_nullNode))
	{
		DeleteFixUp(delete_point_child);
	}
	delete delete_point;
	return true;
}
void RB_Tree::DeleteFixUp(struct Node* node)
{
	while (node != m_root && node->RB_COLOR == BLACK)
	{
		if (node == node->parent->left)
		{
			struct Node* brother = node->parent->right;
			if (brother->RB_COLOR == RED)   //情况1：x的兄弟w是红色的。  
			{
				brother->RB_COLOR = BLACK;
				node->parent->RB_COLOR = RED;
				RotateLeft(node->parent);
			}
			else     //情况2：x的兄弟w是黑色的，  
			{
				if (brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK)
					//且w的俩个孩子都是黑色的。  
				{
					brother->RB_COLOR = RED;
					node = node->parent;
				}
				else if (brother->right->RB_COLOR == BLACK)
					//情况3：x的兄弟w是黑色的，w的右孩子是黑色（w的左孩子是红色）。  
				{
					brother->RB_COLOR = RED;
					brother->left->RB_COLOR = BLACK;
					RotateRight(brother);
				}
				//else if(brother->right->RB_COLOR == RED)  
				//情况4：x的兄弟w是黑色的，且w的右孩子时红色的。  
				//{  
				brother->RB_COLOR = node->parent->RB_COLOR;
				node->parent->RB_COLOR = BLACK;
				brother->right->RB_COLOR = BLACK;
				RotateLeft(node->parent);
				node = m_root;
				//}  
			}
		}
		else  //下述情况针对上面的情况1中，node作为右孩子而阐述的。  
			  //22        else (same as then clause with "right" and "left" exchanged)  
			  //同样，原理一致，只是遇到左旋改为右旋，遇到右旋改为左旋，即可。其它代码不变。  
		{
			Node* brother = node->parent->left;
			if (brother->RB_COLOR == RED)
			{
				brother->RB_COLOR = BLACK;
				node->parent->RB_COLOR = RED;
				RotateRight(node->parent);
			}
			else
			{
				if (brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK)
				{
					brother->RB_COLOR = RED;
					node = node->parent;
				}
				else if (brother->left->RB_COLOR == BLACK)
				{
					brother->RB_COLOR = RED;
					brother->right->RB_COLOR = BLACK;
					RotateLeft(brother);
				}
				//else if(brother->left->RB_COLOR==RED)  
				//{  
				brother->RB_COLOR = node->parent->RB_COLOR;
				node->parent->RB_COLOR = BLACK;
				brother->left->RB_COLOR = BLACK;
				RotateRight(node->parent);
				node = m_root;
				//}  
			}
		}
	}
	m_nullNode->parent = m_root;   //最后将node置为根结点，  
	node->RB_COLOR = BLACK;    //并改为黑色。  
}
inline Node* RB_Tree::InOrderSuccessor(Node* node)
{
	if (node == m_nullNode)       //null node has no successor  
	{
		return m_nullNode;
	}
	Node* result = node->right;   //get node's right node  
	while (result != m_nullNode)        //try to find node's right subtree's left most node  
	{
		if (result->left != m_nullNode)
		{
			result = result->left;
		}
		else
		{
			break;
		}
	}                              //after while loop result==null or result's left child is null  
	if (result == m_nullNode)
	{
		Node* index = node->parent;
		result = node;
		while (index != m_nullNode && result == index->right)
		{
			result = index;
			index = index->parent;
		}
		result = index;         //first parent's left or null  
	}
	return result;
}


void RB_Tree::InOrderTraverse(Node* node)
{
	if (node == m_nullNode)
	{
		return;
	}
	else
	{
		RB_Tree::InOrderTraverse(node->left);
		cout << node->vertex[0]<<" "<< node->vertex[1] <<" "<<node->vertex[2] << endl;
		RB_Tree::InOrderTraverse(node->right);
	}
}
