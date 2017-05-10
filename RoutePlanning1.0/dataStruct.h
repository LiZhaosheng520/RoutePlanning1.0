#pragma once
#include <vector>

using namespace std;

/************����ṹ��*********/
enum COLOR { RED, BLACK };

struct Node
{
	Node()            //���Ա��ʼ��
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	};
	//���д�ŵ���Ϣ
	Node* left;
	Node* right;
	Node* parent;
	COLOR RB_COLOR;
	float vertex[3];                                     //����
	vector<struct Node*> AdjoinNode;                     //�ڽӵ�
	vector<struct Edge*> IncludeEdge;                    //�����õ�ı�
	vector<struct Triangle*> IncludeTriangel;            //�����õ��������
};//��������

struct Body
{
	vector<struct Node*> nodeLink;
	vector<struct Edge*> edgeLink;
	vector<struct Triangle*> triangleLink;
};
struct Edge
{
	struct Node* Vedg[2];              //������������ָ��
	vector<Triangle*> EdgeAdjoinTriangle;    //�ߵ��ڽ�������
};

struct Triangle
{
	struct Node* Vtrg[3];    //��������ָ��
	float  N[3];                    //������
	struct Edge *Eg[3];                 //������ָ��
	vector<struct Triangle*> AdjoinTriangle;   //�ڽ�������
};
struct FindBody
{
	vector<struct Triangle*>  m_FindTriangleLink;    //�����εĸ�ʽ����ȡƽ��ǰ�ģ���������һ�㻹��3��
	vector<struct Edge*> m_NoActiveEdgeLink;
};
struct point
{
	float x;
	float y;
	float z;
};