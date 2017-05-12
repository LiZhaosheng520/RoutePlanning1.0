
// RoutePlanning1.0Dlg.h : ͷ�ļ�
//
#include "RB_Tree.h"
#pragma once
#include <vector>
using namespace std;
// CRoutePlanning10Dlg �Ի���
class CRoutePlanning10Dlg : public CDialogEx
{
// ����
public:
	CRoutePlanning10Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROUTEPLANNING10_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	struct facet                       //һ��������Ƭ
	{
		float N[3];                    //������
		float Vertex[3][3];              //��������
	};
	//����ȫ�ֱ���
	vector<facet> facetlist;            //���е���������Ϣ
	struct Body m_Body;                 //define body
	RB_Tree m_Tree;
	struct FindBody m_findbody;        //��ȡ���body

	int NumTriangle1;                   //��ȡǰ����Ƭ��Ŀ
	int NumTriangle2;                   //��ȡ������Ƭ��Ŀ
	int m_NumTriangle1;                 //��1��������Ŀ
	int m_NumTriangle2;                 //��2��������Ŀ
	float m_extract[3];                //��ȡƽ��ʱ�ķ���������ֵ            
	float m_Threshold;                   //define threshold
	float extract1;
	float extract2;
	float extract3;
	float extract4;
	struct FindBody find_plane(struct Body m_Body, float m_N[3], float m_Threshold);
	bool FindedTriangle(float N1[3], float N2[3], float m_Threshold);

	/****OpenGL����******/
public:
	CDC *m_pDC;
	HGLRC m_hRC;
	bool InitializeOpenGL();                  //OpenGL��ʼ��
	bool SetupPixelFormat();                 //���ظ�ʽ��
	void GetSize();                       //��ȡλ��
	void SHOWPICTURE1();
	afx_msg void OnBnClickedShowgraph();
	afx_msg void OnBnClickedRouteplanning();
	
	/********·���滮**********/
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
