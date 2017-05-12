
// RoutePlanning1.0Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RoutePlanning1.0.h"
#include "RoutePlanning1.0Dlg.h"
#include "afxdialogex.h"
#include "RB_Tree.h"
#include <sstream>
#include <gl/glut.h>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

bool cmp(struct point a, struct point b)
{
	return a.x<b.x;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRoutePlanning10Dlg �Ի���



CRoutePlanning10Dlg::CRoutePlanning10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROUTEPLANNING10_DIALOG, pParent)
	, m_NumTriangle1(0)
	, m_NumTriangle2(0)
	, extract1(0)
	, extract2(0)
	, extract3(0)
	, extract4(0)
	, SliceDistance(0)
	, SliceNum(0)
	, Direction(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoutePlanning10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_NumTriangle1);
	DDX_Text(pDX, IDC_EDIT7, m_NumTriangle2);
	DDX_Text(pDX, IDC_EDIT3, extract1);
	DDX_Text(pDX, IDC_EDIT4, extract2);
	DDX_Text(pDX, IDC_EDIT5, extract3);
	DDX_Text(pDX, IDC_EDIT6, extract4);
	DDX_Text(pDX, IDC_EDIT9, SliceDistance);
	DDX_Text(pDX, IDC_EDIT8, SliceNum);
	DDX_Text(pDX, IDC_EDIT10, Direction);
}

BEGIN_MESSAGE_MAP(CRoutePlanning10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILEBROWSER, &CRoutePlanning10Dlg::OnBnClickedFilebrowser)
	ON_EN_CHANGE(IDC_EDIT1, &CRoutePlanning10Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_GETPLANE, &CRoutePlanning10Dlg::OnBnClickedGetplane)
	ON_BN_CLICKED(IDC_SHOWGRAPH, &CRoutePlanning10Dlg::OnBnClickedShowgraph)
	ON_BN_CLICKED(IDC_ROUTEPLANNING, &CRoutePlanning10Dlg::OnBnClickedRouteplanning)
END_MESSAGE_MAP()


// CRoutePlanning10Dlg ��Ϣ�������

BOOL CRoutePlanning10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRoutePlanning10Dlg::InitializeOpenGL(); 
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRoutePlanning10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRoutePlanning10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRoutePlanning10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRoutePlanning10Dlg::OnBnClickedFilebrowser()
{
	BROWSEINFO bi;                        //BROWSEINFO          
	wchar_t Buffer[512] = _T("");        
	wchar_t dirBuff[MAX_PATH];

	bi.hwndOwner = m_hWnd;                                            //m_hWnd��ĳ���������
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;                                        //����ѡ���Ŀ¼���Ļ�����   
	bi.lpszTitle = _T("ѡ��ǰ�ļ�");                                //�����Ĵ��ڵ�������ʾ   
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	//bi.ulFlags = BIF_NEWDIALOGSTYLE;                                    //ֻ����Ŀ¼��������־��MSDN   
	bi.lpfn = NULL;                                                   //�ص���������ʱ������   
	bi.lParam = 0;
	bi.iImage = 0;
	//LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);               //������ʾѡ��Ի���
	ITEMIDLIST* pidl = ::SHBrowseForFolder(&bi);                        //��ʾ�������ڣ�ITEMIDLIST����Ҫ
	if (::SHGetPathFromIDList(pidl, dirBuff))                            //��ITEMIDLIST�еõ�Ŀ¼��������·��   
	{
		//�򿪳ɹ�
		GetDlgItem(IDC_EDIT1)->SetWindowText(dirBuff);               //�༭����ʾ�ļ���ַ
		GetDlgItem(IDC_SHOWGRAPH)->EnableWindow(TRUE);               //ͼ����ʾ��ť����
		GetDlgItem(IDC_ROUTEPLANNING)->EnableWindow(TRUE);               //·���滮��ť����	
		GetDlgItem(IDC_GETPLANE)->EnableWindow(TRUE);               //ƽ����ȡ��ť����
		m_FileName = ws2char(dirBuff);		 //wchar_t����ת��Ϊchar����
		m_Body = HandleSTL(m_FileName,m_Tree);    //��ȡ������STL
	    //ReadFile(m_FileName);               //��ȡ�ļ�	              
		UpdateData(TRUE);                         //�ӿؼ������л�ȡ��ֵ
		m_NumTriangle1 = NumTriangle1;            //�༭����ʾ��ȡǰ����Ƭ��Ŀ
		UpdateData(FALSE); 

		/******��ʾԭʼ����******/
		SHOWPICTURE1();

	}
}

void CRoutePlanning10Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������	
}


char* CRoutePlanning10Dlg::ws2char(wchar_t* WStr)
{
	//��wchar_t����ת��Ϊchar����
	char* CStr;
	int len = WideCharToMultiByte(CP_ACP, 0, WStr, wcslen(WStr), NULL, 0, NULL, NULL);
	CStr = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, WStr, wcslen(WStr), CStr, len, NULL, NULL);
	CStr[len] = '\0';
	return CStr;
}


void CRoutePlanning10Dlg::ReadFile(char* cfilename)
{
	FILE * pFile;
	long lSize;
	char* buffer;
	size_t result;
	fopen_s(&pFile, cfilename, "rb");

	/* ��ȡ�ļ���С */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* �����ڴ�洢�����ļ� */
	buffer = (char*)malloc(sizeof(char)*lSize);

	/* ���ļ�������buffer�� */
	result = fread(buffer, 1, lSize, pFile);

	/* ������ʾ���ر��ļ����ͷ��ڴ� */
	fclose(pFile);

	if (buffer[79] != '\0')//�жϸ�ʽ
	{
		ReadASCII(buffer);
	}
	free(buffer);
}


void CRoutePlanning10Dlg::ReadASCII(char* buffer)
{
	NumTriangle1 = 0;
	float vertex[3][3];
	facet m_facet;
	string name, useless;
	stringstream ss(buffer);
	ss >> name >> name;
	ss.get();
	ss >> useless;   //���facet
	//һ��ѭ������һ��������Ƭ
	do {
		float n[3];
		if (useless != "facet")
			break;
		else
		{
			ss >> useless >> n[0] >> n[1] >> n[2];                //���뷨����
		}
		getline(ss, useless);
		getline(ss, useless);

		ss >> useless >> vertex[0][0] >> vertex[0][1] >> vertex[0][2];
		ss >> useless >> vertex[1][0] >> vertex[1][1] >> vertex[1][2];
		ss >> useless >> vertex[2][0] >> vertex[2][1] >> vertex[2][2];
		for (int i = 0; i < 3; i++)
		{
			m_facet.N[i] = n[i];
			for (int j = 0; j < 3; j++)
			{
				m_facet.Vertex[i][j] = vertex[i][j];
			}
		}
		facetlist.push_back(m_facet);

		NumTriangle1++;
		getline(ss, useless);
		getline(ss, useless);
		getline(ss, useless);
		ss >> useless;
	} 
	while (useless != "endsolid");
}


void CRoutePlanning10Dlg::OnBnClickedGetplane()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_extract[0] = extract1;
	m_extract[1] = extract2;
	m_extract[2] = extract3;
	m_Threshold = extract4;
	UpdateData(FALSE);
	m_findbody = find_plane(m_Body, m_extract, m_Threshold);
	UpdateData(TRUE);                         //�ӿؼ������л�ȡ��ֵ
	m_NumTriangle2 = m_findbody.m_FindTriangleLink.size();            //�༭����ʾ��ȡǰ����Ƭ��Ŀ
	UpdateData(FALSE);
}


struct Body CRoutePlanning10Dlg::HandleSTL(char* cfilename, RB_Tree tree)
{
	struct Body m_body;
	ReadFile(cfilename);
	int num = NumTriangle1;
	for (int i = 0; i <num; i++)   	//����num��������Ƭ����ÿ��������Ƭ����
	{
		//һ��ѭ��������һ����Ƭface
		float m_vertex[3][3];            //�����εĶ��������
		struct Triangle *c_triangle = new Triangle();      //������ָ��
		struct Node *m_Node[3];          //�������

		for (int j = 0; j < 3; j++)        //������
		{
			c_triangle->N[j] = facetlist[i].N[j];
		}
		for (int q = 0; q < 3; q++)              //һ����Ƭ����������
		{
			for (int n = 0; n < 3; n++)          //ÿ������x,y,z����
			{
				m_vertex[q][n] = facetlist[i].Vertex[q][n];
			}
		}

		//�����½�㣬������У����ٲ���
		vector<int> flagInsert;
		for (int m = 0; m < 3; m++)
		{
			m_Node[m] = tree.RB_find(m_vertex[m][0], m_vertex[m][1], m_vertex[m][2], tree.m_root);
			if (m_Node[m] == tree.m_nullNode)        //˵��û���ҵ�
			{
				flagInsert.push_back(m);
				tree.Insert(m_vertex[m][0], m_vertex[m][1], m_vertex[m][2], tree.m_root);              //���û�д˵㣬���뵽�������
				m_Node[m] = tree.RB_find(m_vertex[m][0], m_vertex[m][1], m_vertex[m][2], tree.m_root);    //������ٴβ���,�õ�������ָ��
			}
		}
		//��������з���������������û�еģ�Ҫ��������
		for (int j = 0; j < 3; j++)         //����
		{
			for (int k = 0; k < 3; k++)
			{
				if (j != k)                //����
				{
					int flag = 0;
					for (int m = 0; m < (int)m_Node[j]->AdjoinNode.size(); m++)
					{
						if (m_Node[j]->AdjoinNode[m] == m_Node[k])          //�����д��ڴ�Ԫ��
							flag = 1;
					}
					if (flag == 0)         //˵�������ڴ�Ԫ��
						m_Node[j]->AdjoinNode.push_back(m_Node[k]);
				}
			}
		}
		//�������ε�ָ�븳������
		for (int j = 0; j < 3; j++)
		{
			m_Node[j]->IncludeTriangel.push_back(c_triangle);
		}

		//���µ���뵽body������
		for (int j = 0; j <(int)flagInsert.size(); j++)
		{
			m_body.nodeLink.push_back(m_Node[flagInsert[j]]);
		}
		m_body.triangleLink.push_back(c_triangle);           //��������Ƭ����Body��
	}

	//��ÿ��������Ƭ��������TriangleLink�Ķ��㸳ֵ
	for (int i = 0; i < num; i++)
	{
		float m_vertex[3][3];            //�����εĶ��������
		for (int q = 0; q < 3; q++)              //һ����Ƭ����������
		{
			for (int n = 0; n < 3; n++)          //ÿ������x,y,z����
			{
				m_vertex[q][n] = facetlist[i].Vertex[q][n];
			}
		}
		for (int j = 0; j < 3; j++)
		{
			m_body.triangleLink[i]->Vtrg[j] = tree.RB_find(m_vertex[j][0], m_vertex[j][1], m_vertex[j][2], tree.m_root);
		}
	}

	//������
	for (int i = 0; i < num; i++)
	{
		struct Node* m_Node[3];
		struct Edge* m_Edge[3];
		m_Edge[0] = new Edge();       //��ʼ������ָ��
		m_Edge[1] = new Edge();
		m_Edge[2] = new Edge();

		int m_NumEdge = 0;
		for (int j = 0; j < 3; j++)
		{
			m_Node[j] = m_body.triangleLink[i]->Vtrg[j];
		}
		//�������߽��з�����m_Node[j]���m_Node[k]�㣬��j��������Ѱ��k,�ҵ��˾ͼ���
		for (int j = 0; j < (3 - 1); j++)
		{
			for (int k = j + 1; k < 3; k++)
			{
				int flag = 0;
				for (int m = 0; m <(int)m_Node[j]->AdjoinNode.size(); m++)
				{
					if (m_Node[k] == m_Node[j]->AdjoinNode[m])       //˵���ҵ���
					{
						flag = 1;
					}
				}
				if (flag == 1)
				{
					m_Edge[m_NumEdge]->Vedg[0] = m_Node[j];
					m_Edge[m_NumEdge]->Vedg[1] = m_Node[k];
					for (int m = 0; m < (int)m_Node[j]->IncludeTriangel.size(); m++)
					{
						for (int n = 0; n < (int)m_Node[k]->IncludeTriangel.size(); n++)
						{
							if (m_Node[j]->IncludeTriangel[m] == m_Node[k]->IncludeTriangel[n])
							{
								m_Edge[m_NumEdge]->EdgeAdjoinTriangle.push_back(m_Node[j]->IncludeTriangel[m]);
							}
						}
					}

					m_body.edgeLink.push_back(m_Edge[m_NumEdge]);
					vector<struct Node*>::iterator it;
					for (it = m_body.triangleLink[i]->Vtrg[j]->AdjoinNode.begin(); it != m_body.triangleLink[i]->Vtrg[j]->AdjoinNode.end();)
					{
						if (*it == m_Node[k])
							it = m_body.triangleLink[i]->Vtrg[j]->AdjoinNode.erase(it);
						else
							++it;
					}

					for (it = m_body.triangleLink[i]->Vtrg[k]->AdjoinNode.begin(); it != m_body.triangleLink[i]->Vtrg[k]->AdjoinNode.end();)
					{
						if (*it == m_Node[j])
							it = m_body.triangleLink[i]->Vtrg[k]->AdjoinNode.erase(it);
						else
							++it;
					}
					m_NumEdge++;
				}
			}
		}
	}

	//����Node�ͱߵĹ�ϵ
	for (int i = 0; i <(int)m_body.nodeLink.size(); i++)
	{
		for (int j = 0; j < (int)m_body.edgeLink.size(); j++)
		{
			if ((m_body.nodeLink[i] == m_body.edgeLink[j]->Vedg[0]) || (m_body.nodeLink[i] == m_body.edgeLink[j]->Vedg[1]))
			{
				m_body.nodeLink[i]->IncludeEdge.push_back(m_body.edgeLink[j]);
			}
		}
	}

	//����triangle��triangle�Ĺ�ϵ
	for (int i = 0; i < num; i++)   //������
	{
		int m_Numeg = 0;
		//����������ָ��
		for (int j = 0; j < (3 - 1); j++)                        //������
		{
			for (int k = j + 1; k < 3; k++)
			{
				for (int m = 0; m < (int)m_body.edgeLink.size(); m++)
				{
					if (((m_body.triangleLink[i]->Vtrg[j] == m_body.edgeLink[m]->Vedg[0]) && (m_body.triangleLink[i]->Vtrg[k] == m_body.edgeLink[m]->Vedg[1])) || ((m_body.triangleLink[i]->Vtrg[j] == m_body.edgeLink[m]->Vedg[1]) && (m_body.triangleLink[i]->Vtrg[k] == m_body.edgeLink[m]->Vedg[0])))
					{
						m_body.triangleLink[i]->Eg[m_Numeg] = m_body.edgeLink[m];
						m_Numeg++;
					}
				}
			}
		}
	}

	//�����ڽ�������
	for (int i = 0; i < num; i++)
	{
		//�����ڽ�������ָ��
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < (int)m_body.triangleLink[i]->Eg[j]->EdgeAdjoinTriangle.size(); k++)   //ÿ���ߵ��ڽ�������
			{
				if (m_body.triangleLink[i] != m_body.triangleLink[i]->Eg[j]->EdgeAdjoinTriangle[k])     //˵��Ϊ�ڽ�������
				{
					m_body.triangleLink[i]->AdjoinTriangle.push_back(m_body.triangleLink[i]->Eg[j]->EdgeAdjoinTriangle[k]);
				}
			}
		}
	}

	return m_body;
}


struct FindBody CRoutePlanning10Dlg::find_plane(struct Body m_Body, float m_N[3], float m_Threshold)
{
	vector<struct Triangle*> m_FindTriangleLink;    //�������������Ƭ
	vector<struct Edge*> m_ActiveEdgeLink;          //���Ա�
	vector<struct Edge*> m_NoActiveEdgeLink;        //�߽�ı�
	struct Edge *m_actedge;           //��ʱ���Ա�
	struct Triangle *m_actriangle;    //��ʱ������
	struct FindBody m_findbody;
	int m_num = 1;
	//�������е������Σ����ҵ�һ����������������Σ����뵽TrLink��EdgeLink�в���ֹѭ��
	for (int i = 0; i <(int)m_Body.triangleLink.size(); i++)
	{
		if (FindedTriangle(m_Body.triangleLink[i]->N, m_N, m_Threshold))
		{
			m_FindTriangleLink.push_back(m_Body.triangleLink[i]);
			for (int j = 0; j < 3; j++)
			{
				m_ActiveEdgeLink.push_back(m_Body.triangleLink[i]->Eg[j]);
			}
			break;
		}
	}
	//�������б����������η������������չ�ߣ��������ϣ����뵽�ǻ��Ա߱���
	while (m_ActiveEdgeLink.size())
	{
		vector<struct Edge*> m_InsertActiveEdgeLink;          //��ʱҪ������Ա��б�
		vector<struct Edge*> m_DeleteActiveEdgeLink;          //��ʱҪɾ���Ļ��Ա��б�

		int num = (int)m_ActiveEdgeLink.size();
		//�������Աߣ�����������Ƭ�Ƿ�������
		for (int i = 0; i < num; i++)      //ѭ��Ѱ�һ��Աߣ���һ��������
		{
			m_actedge = m_ActiveEdgeLink[i];   //��ʱ���Ա�
			if (m_actedge->EdgeAdjoinTriangle.size() == 1)   //���Աߵ���һ��Ϊ�գ�ֱ��ɾ���˻��Աߣ�ͬʱ���ٽ���м���
			{
				m_DeleteActiveEdgeLink.push_back(m_actedge);
				m_NoActiveEdgeLink.push_back(m_actedge);
			}
			else
			{
				for (int j = 0; j < 2; j++)        //��ÿ����ѭ�����Σ��鿴�����������Σ������һ�����Ѽ���������Σ������������һ�ξ����µ������Σ�bѭ��
				{
					m_actriangle = m_actedge->EdgeAdjoinTriangle[j];
					int flag = 0;
					for (int k = 0; k <(int)m_FindTriangleLink.size(); k++)
					{
						if (m_actriangle == m_FindTriangleLink[k])
						{
							flag = 1;
							break;
						}
					}
					//�����в�������������Σ���Ҫ����
					if (flag == 0)
					{
						//�������η������
						if (FindedTriangle(m_actriangle->N, m_N, m_Threshold))
						{
							m_FindTriangleLink.push_back(m_ActiveEdgeLink[i]->EdgeAdjoinTriangle[j]);          //�����μ��뵽������
																											   //ɾ��������Ա�
							m_DeleteActiveEdgeLink.push_back(m_actedge);
							for (int k = 0; k < 3; k++)
							{
								if (m_actriangle->Eg[k] != m_actedge)
								{
									int flag_edge = 0;
									for (int m = 0; m < (int)m_ActiveEdgeLink.size(); m++)
									{
										if (m_actriangle->Eg[k] == m_ActiveEdgeLink[m])    //���������У����뵽ɾ��������
										{
											m_DeleteActiveEdgeLink.push_back(m_actriangle->Eg[k]);
											flag_edge = 1;
											break;
										}
									}
									for (int m = 0; m < (int)m_InsertActiveEdgeLink.size(); m++)
									{
										if (m_actriangle->Eg[k] == m_InsertActiveEdgeLink[m])   //����Ҫ����������У�ֱ��ɾ��
										{
											//��In
											vector<struct Edge*>::iterator it;
											for (it = m_InsertActiveEdgeLink.begin(); it != m_InsertActiveEdgeLink.end();)
											{
												if (*it == m_actedge)
												{
													it = m_InsertActiveEdgeLink.erase(it);
												}
												else
												{
													++it;
												}
											}
											flag_edge = 1;
											break;
										}
									}
									if (flag_edge == 0)     //�߲���������Ҫ����
									{
										m_InsertActiveEdgeLink.push_back(m_actriangle->Eg[k]);
									}
								}
							}

						}
						//�������β�������������˱߼��뵽�ٽ������ͬʱ���Ա�������ɾ���˱�
						else
						{
							m_NoActiveEdgeLink.push_back(m_actedge);             //�߽���м���  
							m_DeleteActiveEdgeLink.push_back(m_actedge);         //���Ա���ɾ��

						}
						break;
					}
				}
			}

		}

		//���Ա߸ò���
		for (int i = 0; i < (int)m_InsertActiveEdgeLink.size(); i++)
		{
			m_ActiveEdgeLink.push_back(m_InsertActiveEdgeLink[i]);
		}

		//���Ա�ɾ��
		vector<struct Edge*>::iterator it;
		for (int i = 0; i < (int)m_DeleteActiveEdgeLink.size(); i++)
		{
			for (it = m_ActiveEdgeLink.begin(); it != m_ActiveEdgeLink.end();)
			{
				if (*it == m_DeleteActiveEdgeLink[i])
				{
					it = m_ActiveEdgeLink.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		m_InsertActiveEdgeLink.clear();
		m_DeleteActiveEdgeLink.clear();
		//cout << m_num++<<endl;
	}

	m_findbody.m_FindTriangleLink = m_FindTriangleLink;
	m_findbody.m_NoActiveEdgeLink = m_NoActiveEdgeLink;
	return m_findbody;
}


bool CRoutePlanning10Dlg::FindedTriangle(float N1[3], float N2[3], float m_Threshold)
{
	if ((N1[0] * N2[0] + N1[1] * N2[1] + N1[2] * N2[2]) > (m_Threshold))
		return 1;
	else
		return 0;
}


bool CRoutePlanning10Dlg::InitializeOpenGL()
{
	m_pDC = new CClientDC(GetDlgItem(IDC_SHOWPICTURE));
	//��ȡ�豸DC����DCΪPictureControl���豸
	if (m_pDC == NULL)
	{//�������DCΪ�գ��򴴽�DCʧ��
		return FALSE;
	}
	if (!SetupPixelFormat())
	{//���ظ�ʽ���������򵥵�˵����ָ����ͼҪ�õ����ظ�ʽ�������ʽ�������������ظ�ʽ���ĺ����塣
		return FALSE;
	}
	//������ͼ������
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());

	if (m_hRC == 0)
	{//	����ʧ��		
		return FALSE;
	}
	// ʹ��ͼ������Ϊ��ǰ�����̵ֳĵ�ǰ��ͼ������
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		return FALSE;
	}
	//�������ɫ
	GetSize();
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	return TRUE;
}


bool CRoutePlanning10Dlg::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int m_nPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

void CRoutePlanning10Dlg::GetSize()
{
	int cx;
	int cy;
	CRect rect;
	GetDlgItem(IDC_SHOWPICTURE)->GetClientRect(rect);
	//ȡ���ؼ��ľ��ο顣
	cx = rect.Width();
	cy = rect.Height();
	GLdouble aspect_ratio; // width/height ratio
	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	// select the full client area
	glViewport(0, 0, cx, cy);
	//ָ����ͼ�������Ϊ00������Ϊcx,cy
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//�˷�����Ϊ���ء�ʹ��������Ч
	gluPerspective(30.0f, aspect_ratio, .05f, 1000.0f);
	//glOrtho()
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void CRoutePlanning10Dlg::SHOWPICTURE1()
{
	GetSize();
	glClearColor(1.0f,1.0f,1.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	//gluLookAt(-1, -1, 1, 1, 1, -1.88675, 0, 0, 1);
	glTranslatef(-70.0f, 0.0f, -420.0f);
	glRotatef(-40, 1.0f, 0.0f, 0.0f);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);						// Rotate The Triangle On The Y axis ( NEW )
	

	//X
	//glLineWidth(3);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(20.0f, 0.0f, 0.0f);
	//glEnd();
	//glBegin(GL_TRIANGLES);
	//glVertex3f(20.0f, 0.0f, -1.4f);
	//glVertex3f(20.0f, 0.0f, 1.4f);
	//glVertex3f(21.8f, 0.0f, 0.0f);
	//glEnd();
	//glRasterPos3f(21.0f, 0.0f, -2.2f);
	//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
	////Y
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 10.0f, 0.0f);
	//glEnd();
	//glBegin(GL_TRIANGLES);
	//glVertex3f(-0.6f, 10.0f, 0.0f);
	//glVertex3f(0.6f, 10.0f, 0.0f);
	//glVertex3f(0.0f, 12.0f, 0.0f);
	//glEnd();
	//glRasterPos3f(2.0f, 5.0f, 0.0f);
	//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	////Z
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glBegin(GL_LINES);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, 20.0f);
	//glEnd();
	//glBegin(GL_TRIANGLES);
	//glVertex3f(-1.4f, 0.0f, 20.0f);
	//glVertex3f(1.4f, 0.0f, 20.0f);
	//glVertex3f(0.0f, 0.0f, 22.0f);
	//glEnd();
	//glRasterPos3f(-6.0f, 0.0f, 20.0f);
	//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Z');

	glLineWidth(1);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < (int)m_Body.edgeLink.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(m_Body.edgeLink[i]->Vedg[0]->vertex[0], m_Body.edgeLink[i]->Vedg[0]->vertex[1], m_Body.edgeLink[i]->Vedg[0]->vertex[2]);
		glVertex3f(m_Body.edgeLink[i]->Vedg[1]->vertex[0], m_Body.edgeLink[i]->Vedg[1]->vertex[1], m_Body.edgeLink[i]->Vedg[1]->vertex[2]);
		glEnd();
	}
	glFinish();
	// Now Swap the buffers
	SwapBuffers(m_pDC->GetSafeHdc());
}


void CRoutePlanning10Dlg::OnBnClickedShowgraph()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetSize();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix						
	glTranslatef(-70.0f, 0.0f, -420.0f);
	glRotatef(-40, 1.0f, 0.0f, 0.0f);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);						// Rotate The Triangle On The Y axis ( NEW )
	glLineWidth(2);

	for (int i = 0; i < (int)m_findbody.m_NoActiveEdgeLink.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(m_findbody.m_NoActiveEdgeLink[i]->Vedg[0]->vertex[0], m_findbody.m_NoActiveEdgeLink[i]->Vedg[0]->vertex[1], m_findbody.m_NoActiveEdgeLink[i]->Vedg[0]->vertex[2]);
		glVertex3f(m_findbody.m_NoActiveEdgeLink[i]->Vedg[1]->vertex[0], m_findbody.m_NoActiveEdgeLink[i]->Vedg[1]->vertex[1], m_findbody.m_NoActiveEdgeLink[i]->Vedg[1]->vertex[2]);
		glEnd();
	}
	glFinish();
	// Now Swap the buffers
	SwapBuffers(m_pDC->GetSafeHdc());
}


void CRoutePlanning10Dlg::OnBnClickedRouteplanning()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_SliceDistance = SliceDistance;
	m_Direction = Direction;
	UpdateData(FALSE);

	if (m_Direction == "x")
	{
		ShowRoute(m_Direction,0);
	}
	else if (m_Direction == "y")
	{
		ShowRoute(m_Direction, 1);
	}
	else if (m_Direction == "z")
	{
		ShowRoute(m_Direction, 2);
	}
	

	glFinish();
	// Now Swap the buffers
	SwapBuffers(m_pDC->GetSafeHdc());
}


void CRoutePlanning10Dlg::ShowRoute(CString m, int n)    //m:x y z;  n:0 1 2
{
	float m_min = 0;
	float m_max = 0;
	vector<float> Y;
	for (int i = 0; i < (int)m_findbody.m_FindTriangleLink.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_min > m_findbody.m_FindTriangleLink[i]->Vtrg[j]->vertex[n])
			{
				m_min = m_findbody.m_FindTriangleLink[i]->Vtrg[j]->vertex[n];
			}
			if (m_max < m_findbody.m_FindTriangleLink[i]->Vtrg[j]->vertex[n])
			{
				m_max = m_findbody.m_FindTriangleLink[i]->Vtrg[j]->vertex[n];
			}
		}
	}

	m_SliceNum = (int)(m_max - m_min) / m_SliceDistance;
	UpdateData(TRUE);
	SliceNum = m_SliceNum;
	UpdateData(FALSE);
	for (int i = 0; i < m_SliceNum; i++)
	{
		Y.push_back(m_min + m_SliceDistance / 2 + m_SliceDistance*i);
	}
	for (int i = 0; i < (int)Y.size(); i++)
	{
		vector<struct point> m_points;
		for (int j = 0; j < (int)m_findbody.m_FindTriangleLink.size(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				struct point m_point;
				if (m == "x")
				{
					m_point.x = Y[i];
					struct Node *m_Node1 = m_findbody.m_FindTriangleLink[j]->Eg[k]->Vedg[0];   //Node 0
					struct Node *m_Node2 = m_findbody.m_FindTriangleLink[j]->Eg[k]->Vedg[1];   //Node 1
					int m_flag1 = 0;
					int m_flag2 = 0;
					if (m_Node1->vertex[0] < Y[i] && Y[i]< m_Node2->vertex[0])
					{
						m_point.y = (m_point.x - m_Node1->vertex[0])*(m_Node2->vertex[1] - m_Node1->vertex[1]) / (m_Node2->vertex[0] - m_Node1->vertex[0]) + m_Node1->vertex[1];
						m_point.z = (m_point.x - m_Node1->vertex[0])*(m_Node2->vertex[2] - m_Node1->vertex[2]) / (m_Node2->vertex[0] - m_Node1->vertex[0]) + m_Node1->vertex[2];
						m_flag1 = 1;
					}
					if (m_Node1->vertex[0] > Y[i] && Y[i]> m_Node2->vertex[0])
					{
						m_point.y = (m_point.x - m_Node2->vertex[0])*(m_Node1->vertex[1] - m_Node2->vertex[1]) / (m_Node1->vertex[0] - m_Node2->vertex[0]) + m_Node2->vertex[1];
						m_point.z = (m_point.x - m_Node2->vertex[0])*(m_Node1->vertex[2] - m_Node2->vertex[2]) / (m_Node1->vertex[0] - m_Node2->vertex[0]) + m_Node2->vertex[2];
						m_flag1 = 1;
					}
					if (m_flag1)       //����߰����˴˽���
					{
						if (m_points.size() == 0)
						{
							m_points.push_back(m_point);
						}
						for (int i = 0; i < (int)m_points.size(); i++)
						{
							if ((m_points[i].x == m_point.x) && (m_points[i].y == m_point.y) && (m_points[i].z == m_point.z))
							{
								m_flag2 = 1;
								break;
							}
						}
						if (m_flag2 == 0)
						{
							m_points.push_back(m_point);
						}
					}
				}
				else if (m == "y")
				{
					m_point.y = Y[i];
					struct Node *m_Node1 = m_findbody.m_FindTriangleLink[j]->Eg[k]->Vedg[0];   //Node 0
					struct Node *m_Node2 = m_findbody.m_FindTriangleLink[j]->Eg[k]->Vedg[1];   //Node 1
					int m_flag1 = 0;
					int m_flag2 = 0;
					if (m_Node1->vertex[1] < Y[i] && Y[i]< m_Node2->vertex[1])
					{
						m_point.x = (m_point.y - m_Node1->vertex[1])*(m_Node2->vertex[0] - m_Node1->vertex[0]) / (m_Node2->vertex[1] - m_Node1->vertex[1]) + m_Node1->vertex[0];
						m_point.z = (m_point.y - m_Node1->vertex[1])*(m_Node2->vertex[2] - m_Node1->vertex[2]) / (m_Node2->vertex[1] - m_Node1->vertex[1]) + m_Node1->vertex[2];
						m_flag1 = 1;
					}
					if (m_Node1->vertex[1] > Y[i] && Y[i]> m_Node2->vertex[1])
					{
						m_point.x = (m_point.y - m_Node2->vertex[1])*(m_Node1->vertex[0] - m_Node2->vertex[0]) / (m_Node1->vertex[1] - m_Node2->vertex[1]) + m_Node2->vertex[0];
						m_point.z = (m_point.y - m_Node2->vertex[1])*(m_Node1->vertex[2] - m_Node2->vertex[2]) / (m_Node1->vertex[1] - m_Node2->vertex[1]) + m_Node2->vertex[2];
						m_flag1 = 1;
					}
					if (m_flag1)       //����߰����˴˽���
					{
						if (m_points.size() == 0)
						{
							m_points.push_back(m_point);
						}
						for (int i = 0; i < (int)m_points.size(); i++)
						{
							if ((m_points[i].x == m_point.x) && (m_points[i].y == m_point.y) && (m_points[i].z == m_point.z))
							{
								m_flag2 = 1;
								break;
							}
						}
						if (m_flag2 == 0)
						{
							m_points.push_back(m_point);
						}
					}
				}
				else
				{
					m_point.z = Y[i];
					struct Node *m_Node1 = m_findbody.m_FindTriangleLink[j]->Eg[k]->Vedg[0];   //Node 0
					struct Node *m_Node2 = m_findbody.m_FindTriangleLink[j]->Eg[k]->Vedg[1];   //Node 1
					int m_flag1 = 0;
					int m_flag2 = 0;
					if (m_Node1->vertex[2] < Y[i] && Y[i]< m_Node2->vertex[2])
					{
						m_point.x = (m_point.z - m_Node1->vertex[2])*(m_Node2->vertex[0] - m_Node1->vertex[0]) / (m_Node2->vertex[2] - m_Node1->vertex[2]) + m_Node1->vertex[0];
						m_point.y = (m_point.z - m_Node1->vertex[2])*(m_Node2->vertex[2] - m_Node1->vertex[2]) / (m_Node2->vertex[2] - m_Node1->vertex[2]) + m_Node1->vertex[1];
						m_flag1 = 1;
					}
					if (m_Node1->vertex[1] > Y[i] && Y[i]> m_Node2->vertex[1])
					{
						m_point.x = (m_point.z - m_Node2->vertex[2])*(m_Node1->vertex[0] - m_Node2->vertex[0]) / (m_Node1->vertex[2] - m_Node2->vertex[2]) + m_Node2->vertex[0];
						m_point.y = (m_point.z - m_Node2->vertex[2])*(m_Node1->vertex[2] - m_Node2->vertex[2]) / (m_Node1->vertex[2] - m_Node2->vertex[2]) + m_Node2->vertex[1];
						m_flag1 = 1;
					}
					if (m_flag1)       //����߰����˴˽���
					{
						if (m_points.size() == 0)
						{
							m_points.push_back(m_point);
						}
						for (int i = 0; i < (int)m_points.size(); i++)
						{
							if ((m_points[i].x == m_point.x) && (m_points[i].y == m_point.y) && (m_points[i].z == m_point.z))
							{
								m_flag2 = 1;
								break;
							}
						}
						if (m_flag2 == 0)
						{
							m_points.push_back(m_point);
						}
					}
				}

			}
		}
		intersections1.push_back(m_points);
	}
	for (int i = 0; i < (int)intersections1.size(); i++)
	{
		vector<struct point> m_vector;
		m_vector = intersections1[i];
		sort(m_vector.begin(), m_vector.end(), cmp);
		intersections2.push_back(m_vector);
	}//·���滮����������Ϊ��ʾ

	 // TODO: �ڴ���ӿؼ�֪ͨ����������
	GetSize();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix						
	glTranslatef(-70.0f, 0.0f, -420.0f);
	glRotatef(-40, 1.0f, 0.0f, 0.0f);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);						// Rotate The Triangle On The Y axis ( NEW )

	glLineWidth(2);
	for (int i = 0; i < (int)m_findbody.m_NoActiveEdgeLink.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex3f(m_findbody.m_NoActiveEdgeLink[i]->Vedg[0]->vertex[0], m_findbody.m_NoActiveEdgeLink[i]->Vedg[0]->vertex[1], m_findbody.m_NoActiveEdgeLink[i]->Vedg[0]->vertex[2]);
		glVertex3f(m_findbody.m_NoActiveEdgeLink[i]->Vedg[1]->vertex[0], m_findbody.m_NoActiveEdgeLink[i]->Vedg[1]->vertex[1], m_findbody.m_NoActiveEdgeLink[i]->Vedg[1]->vertex[2]);
		glEnd();
	}
	glLineWidth(1);
	for (int i = 0; i < (int)intersections2.size(); i++)
	{
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < (int)intersections2[i].size(); j++)
		{
			glVertex3f(intersections2[i][j].x, intersections2[i][j].y, intersections2[i][j].z);
		}
		glEnd();
	}
}
