
// RoutePlanning1.0Dlg.h : 头文件
//
#include "RB_Tree.h"
#pragma once
#include <vector>
using namespace std;
// CRoutePlanning10Dlg 对话框
class CRoutePlanning10Dlg : public CDialogEx
{
// 构造
public:
	CRoutePlanning10Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROUTEPLANNING10_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFilebrowser();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedGetplane();
public:
	char *m_FileName;
	char* ws2char(wchar_t* WStr);
	void ReadFile(char* cfilename);
	void ReadASCII(char* buffer);
	struct Body HandleSTL(char* cfilename, RB_Tree tree);
	
public:
	struct facet                       //一个三角面片
	{
		float N[3];                    //法向量
		float Vertex[3][3];              //三个顶点
	};
	//定义全局变量
	vector<facet> facetlist;            //所有的三角形信息
	struct Body m_Body;                 //define body
	RB_Tree m_Tree;
	struct FindBody m_findbody;        //提取后的body

	int NumTriangle1;                   //提取前三角片数目
	int NumTriangle2;                   //提取后三角片数目
	int m_NumTriangle1;                 //框1三角形数目
	int m_NumTriangle2;                 //框2三角形数目
	float m_extract[3];                //提取平面时的法向量和阈值            
	float m_Threshold;                   //define threshold
	float extract1;
	float extract2;
	float extract3;
	float extract4;
	struct FindBody find_plane(struct Body m_Body, float m_N[3], float m_Threshold);
	bool FindedTriangle(float N1[3], float N2[3], float m_Threshold);

	/****OpenGL部分******/
public:
	CDC *m_pDC;
	HGLRC m_hRC;
	bool InitializeOpenGL();                  //OpenGL初始化
	bool SetupPixelFormat();                 //像素格式化
	void GetSize();                       //获取位置
	void SHOWPICTURE1();
	afx_msg void OnBnClickedShowgraph();
	afx_msg void OnBnClickedRouteplanning();
	
	/********路径规划**********/
public:
	float SliceDistance;      //edit box variable
	int SliceNum;             //edit box variable
	float m_SliceDistance;    //
	int m_SliceNum;

	vector<vector<point>> intersections1;   //unordered set of intersection      
	vector<vector<point>> intersections2;   //ordered set of intersection
	CString Direction;
	CString m_Direction;
	void ShowRoute(CString m, int n);
};
