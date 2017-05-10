#pragma once
#include <vector>

using namespace std;

/************定义结构体*********/
enum COLOR { RED, BLACK };

struct Node
{
	Node()            //类成员初始化
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	};
	//树中存放的信息
	Node* left;
	Node* right;
	Node* parent;
	COLOR RB_COLOR;
	float vertex[3];                                     //坐标
	vector<struct Node*> AdjoinNode;                     //邻接点
	vector<struct Edge*> IncludeEdge;                    //包含该点的边
	vector<struct Triangle*> IncludeTriangel;            //包含该点的三角形
};//结点类结束

struct Body
{
	vector<struct Node*> nodeLink;
	vector<struct Edge*> edgeLink;
	vector<struct Triangle*> triangleLink;
};
struct Edge
{
	struct Node* Vedg[2];              //定义两个顶点指针
	vector<Triangle*> EdgeAdjoinTriangle;    //边的邻接三角形
};

struct Triangle
{
	struct Node* Vtrg[3];    //三个顶点指针
	float  N[3];                    //法向量
	struct Edge *Eg[3];                 //三条边指针
	vector<struct Triangle*> AdjoinTriangle;   //邻接三角形
};
struct FindBody
{
	vector<struct Triangle*>  m_FindTriangleLink;    //三角形的格式是提取平面前的，邻三角形一般还是3个
	vector<struct Edge*> m_NoActiveEdgeLink;
};
struct point
{
	float x;
	float y;
	float z;
};