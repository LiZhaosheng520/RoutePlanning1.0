
#include "RB_Tree.h"

using namespace std;

bool RB_Tree::Empty()           //�ж��Ƿ�Ϊ��, ��Ϊ1
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

struct Node* RB_Tree::RB_find(float x, float y, float z, struct Node* m_index)          //��ѯ
{
	//struct Node* m_index = m_root;       //�����ָ��
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

/*������*/
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
			return false;       //˵�����д���Ҫ�������������false
		}
	}
	struct Node* insert_node = new struct Node();
	insert_node->vertex[0] = x;
	insert_node->vertex[1] = y;
	insert_node->vertex[2] = z;
	insert_node->RB_COLOR = RED;
	insert_node->right = m_nullNode;
	insert_node->left = m_nullNode;
	if (insert_point == m_nullNode)       //�������ʱ��һ�ÿ���
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
	InsertFixUp(insert_node);    //����InsertFixUp�޸����������
	return true;
}

/*�޸����������*/
void  RB_Tree::InsertFixUp(struct Node* node)
{
	while (node->parent->RB_COLOR == RED)
	{
		if (node->parent == node->parent->parent->left)   //  
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->RB_COLOR == RED)   //�������1��z������y�Ǻ�ɫ�ġ�  
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)  //�������2��z������y�Ǻ�ɫ�ģ���  
			{
				if (node == node->parent->right) //��z���Һ���  
				{
					node = node->parent;
					RotateLeft(node);
				}
				//else                 //�������3��z������y�Ǻ�ɫ�ģ���z�����ӡ�  
				//{  
				node->parent->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				RotateRight(node->parent->parent);
				//}
			}
		}
		else //�ⲿ�������Ϊ�������1�У�z�ĸ���������Ϊ�游���Һ����˵��������д�ġ�  
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
					RotateRight(node);     //������������ȣ�������Ϊ����  
				}
				//else  
				//{  
				node->parent->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				RotateLeft(node->parent->parent);   //������Ϊ���������ɡ�  
													//}  
			}
		}
	}
	m_root->RB_COLOR = BLACK;
}
/*��������ʵ��*/
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

//��������ʵ��  
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
			if (brother->RB_COLOR == RED)   //���1��x���ֵ�w�Ǻ�ɫ�ġ�  
			{
				brother->RB_COLOR = BLACK;
				node->parent->RB_COLOR = RED;
				RotateLeft(node->parent);
			}
			else     //���2��x���ֵ�w�Ǻ�ɫ�ģ�  
			{
				if (brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK)
					//��w���������Ӷ��Ǻ�ɫ�ġ�  
				{
					brother->RB_COLOR = RED;
					node = node->parent;
				}
				else if (brother->right->RB_COLOR == BLACK)
					//���3��x���ֵ�w�Ǻ�ɫ�ģ�w���Һ����Ǻ�ɫ��w�������Ǻ�ɫ����  
				{
					brother->RB_COLOR = RED;
					brother->left->RB_COLOR = BLACK;
					RotateRight(brother);
				}
				//else if(brother->right->RB_COLOR == RED)  
				//���4��x���ֵ�w�Ǻ�ɫ�ģ���w���Һ���ʱ��ɫ�ġ�  
				//{  
				brother->RB_COLOR = node->parent->RB_COLOR;
				node->parent->RB_COLOR = BLACK;
				brother->right->RB_COLOR = BLACK;
				RotateLeft(node->parent);
				node = m_root;
				//}  
			}
		}
		else  //������������������1�У�node��Ϊ�Һ��Ӷ������ġ�  
			  //22        else (same as then clause with "right" and "left" exchanged)  
			  //ͬ����ԭ��һ�£�ֻ������������Ϊ����������������Ϊ���������ɡ��������벻�䡣  
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
	m_nullNode->parent = m_root;   //���node��Ϊ����㣬  
	node->RB_COLOR = BLACK;    //����Ϊ��ɫ��  
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
