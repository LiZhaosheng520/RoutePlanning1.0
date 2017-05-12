
// RoutePlanning1.0Dlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

bool cmp(struct point a, struct point b)
{
	return a.x<b.x;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRoutePlanning10Dlg 对话框



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


// CRoutePlanning10Dlg 消息处理程序

BOOL CRoutePlanning10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRoutePlanning10Dlg::InitializeOpenGL(); 
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRoutePlanning10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRoutePlanning10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRoutePlanning10Dlg::OnBnClickedFilebrowser()
{
	BROWSEINFO bi;                        //BROWSEINFO          
	wchar_t Buffer[512] = _T("");        
	wchar_t dirBuff[MAX_PATH];

	bi.hwndOwner = m_hWnd;                                            //m_hWnd你的程序主窗口
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;                                        //返回选择的目录名的缓冲区   
	bi.lpszTitle = _T("选择当前文件");                                //弹出的窗口的文字提示   
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	//bi.ulFlags = BIF_NEWDIALOGSTYLE;                                    //只返回目录。其他标志看MSDN   
	bi.lpfn = NULL;                                                   //回调函数，有时很有用   
	bi.lParam = 0;
	bi.iImage = 0;
	//LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);               //调用显示选择对话框
	ITEMIDLIST* pidl = ::SHBrowseForFolder(&bi);                        //显示弹出窗口，ITEMIDLIST很重要
	if (::SHGetPathFromIDList(pidl, dirBuff))                            //在ITEMIDLIST中得到目录名的整个路径   
	{
		//打开成功
		GetDlgItem(IDC_EDIT1)->SetWindowText(dirBuff);               //编辑框显示文件地址
		GetDlgItem(IDC_SHOWGRAPH)->EnableWindow(TRUE);               //图像显示按钮启用
		GetDlgItem(IDC_ROUTEPLANNING)->EnableWindow(TRUE);               //路径规划按钮启用	
		GetDlgItem(IDC_GETPLANE)->EnableWindow(TRUE);               //平面提取按钮启用
		m_FileName = ws2char(dirBuff);		 //wchar_t类型转化为char类型
		m_Body = HandleSTL(m_FileName,m_Tree);    //读取并处理STL
	    //ReadFile(m_FileName);               //读取文件	              
		UpdateData(TRUE);                         //从控件变量中获取数值
		m_NumTriangle1 = NumTriangle1;            //编辑框显示提取前三角片数目
		UpdateData(FALSE); 

		/******显示原始画面******/
		SHOWPICTURE1();

	}
}

void CRoutePlanning10Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码	
}


char* CRoutePlanning10Dlg::ws2char(wchar_t* WStr)
{
	//将wchar_t类型转变为char类型
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

	/* 获取文件大小 */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* 分配内存存储整个文件 */
	buffer = (char*)malloc(sizeof(char)*lSize);

	/* 将文件拷贝到buffer中 */
	result = fread(buffer, 1, lSize, pFile);

	/* 结束演示，关闭文件并释放内存 */
	fclose(pFile);

	if (buffer[79] != '\0')//判断格式
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
	ss >> useless;   //输出facet
	//一个循环读入一个三角面片
	do {
		float n[3];
		if (useless != "facet")
			break;
		else
		{
			ss >> useless >> n[0] >> n[1] >> n[2];                //读入法向量
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
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_extract[0] = extract1;
	m_extract[1] = extract2;
	m_extract[2] = extract3;
	m_Threshold = extract4;
	UpdateData(FALSE);
	m_findbody = find_plane(m_Body, m_extract, m_Threshold);
	UpdateData(TRUE);                         //从控件变量中获取数值
	m_NumTriangle2 = m_findbody.m_FindTriangleLink.size();            //编辑框显示提取前三角片数目
	UpdateData(FALSE);
}


struct Body CRoutePlanning10Dlg::HandleSTL(char* cfilename, RB_Tree tree)
{
	struct Body m_body;
	ReadFile(cfilename);
	int num = NumTriangle1;
	for (int i = 0; i <num; i++)   	//读入num个三角面片，对每个三角面片处理
	{
		//一个循环，读入一个面片face
		float m_vertex[3][3];            //三角形的顶点的坐标
		struct Triangle *c_triangle = new Triangle();      //三角形指针
		struct Node *m_Node[3];          //三个结点

		for (int j = 0; j < 3; j++)        //法向量
		{
			c_triangle->N[j] = facetlist[i].N[j];
		}
		for (int q = 0; q < 3; q++)              //一个面片的三个顶点
		{
			for (int n = 0; n < 3; n++)          //每个顶点x,y,z坐标
			{
				m_vertex[q][n] = facetlist[i].Vertex[q][n];
			}
		}

		//插入新结点，如果含有，则不再插入
		vector<int> flagInsert;
		for (int m = 0; m < 3; m++)
		{
			m_Node[m] = tree.RB_find(m_vertex[m][0], m_vertex[m][1], m_vertex[m][2], tree.m_root);
			if (m_Node[m] == tree.m_nullNode)        //说明没有找到
			{
				flagInsert.push_back(m);
				tree.Insert(m_vertex[m][0], m_vertex[m][1], m_vertex[m][2], tree.m_root);              //如果没有此点，插入到红黑树中
				m_Node[m] = tree.RB_find(m_vertex[m][0], m_vertex[m][1], m_vertex[m][2], tree.m_root);    //插入后再次查找,得到插入点的指针
			}
		}
		//对三点进行分析，对于邻域中没有的，要加入邻域
		for (int j = 0; j < 3; j++)         //三点
		{
			for (int k = 0; k < 3; k++)
			{
				if (j != k)                //两点
				{
					int flag = 0;
					for (int m = 0; m < (int)m_Node[j]->AdjoinNode.size(); m++)
					{
						if (m_Node[j]->AdjoinNode[m] == m_Node[k])          //邻域中存在此元素
							flag = 1;
					}
					if (flag == 0)         //说明不存在此元素
						m_Node[j]->AdjoinNode.push_back(m_Node[k]);
				}
			}
		}
		//将三角形的指针赋给顶点
		for (int j = 0; j < 3; j++)
		{
			m_Node[j]->IncludeTriangel.push_back(c_triangle);
		}

		//将新点加入到body链表中
		for (int j = 0; j <(int)flagInsert.size(); j++)
		{
			m_body.nodeLink.push_back(m_Node[flagInsert[j]]);
		}
		m_body.triangleLink.push_back(c_triangle);           //将三角面片加入Body中
	}

	//对每个三角面片分析，给TriangleLink的顶点赋值
	for (int i = 0; i < num; i++)
	{
		float m_vertex[3][3];            //三角形的顶点的坐标
		for (int q = 0; q < 3; q++)              //一个面片的三个顶点
		{
			for (int n = 0; n < 3; n++)          //每个顶点x,y,z坐标
			{
				m_vertex[q][n] = facetlist[i].Vertex[q][n];
			}
		}
		for (int j = 0; j < 3; j++)
		{
			m_body.triangleLink[i]->Vtrg[j] = tree.RB_find(m_vertex[j][0], m_vertex[j][1], m_vertex[j][2], tree.m_root);
		}
	}

	//建立边
	for (int i = 0; i < num; i++)
	{
		struct Node* m_Node[3];
		struct Edge* m_Edge[3];
		m_Edge[0] = new Edge();       //初始化三个指针
		m_Edge[1] = new Edge();
		m_Edge[2] = new Edge();

		int m_NumEdge = 0;
		for (int j = 0; j < 3; j++)
		{
			m_Node[j] = m_body.triangleLink[i]->Vtrg[j];
		}
		//对三条边进行分析，m_Node[j]点和m_Node[k]点，在j点邻域中寻找k,找到了就加入
		for (int j = 0; j < (3 - 1); j++)
		{
			for (int k = j + 1; k < 3; k++)
			{
				int flag = 0;
				for (int m = 0; m <(int)m_Node[j]->AdjoinNode.size(); m++)
				{
					if (m_Node[k] == m_Node[j]->AdjoinNode[m])       //说明找到了
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

	//建立Node和边的关系
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

	//建立triangle和triangle的关系
	for (int i = 0; i < num; i++)   //三角形
	{
		int m_Numeg = 0;
		//加入三条边指针
		for (int j = 0; j < (3 - 1); j++)                        //三条边
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

	//加入邻接三角形
	for (int i = 0; i < num; i++)
	{
		//加入邻接三角形指针
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < (int)m_body.triangleLink[i]->Eg[j]->EdgeAdjoinTriangle.size(); k++)   //每条边的邻接三角形
			{
				if (m_body.triangleLink[i] != m_body.triangleLink[i]->Eg[j]->EdgeAdjoinTriangle[k])     //说明为邻接三角形
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
	vector<struct Triangle*> m_FindTriangleLink;    //符合情况的三角片
	vector<struct Edge*> m_ActiveEdgeLink;          //活性边
	vector<struct Edge*> m_NoActiveEdgeLink;        //边界的边
	struct Edge *m_actedge;           //临时活性边
	struct Triangle *m_actriangle;    //临时三角形
	struct FindBody m_findbody;
	int m_num = 1;
	//遍历所有的三角形，先找到一个符合情况的三角形，加入到TrLink和EdgeLink中并终止循环
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
	//遍历边列表，若邻三角形符合情况，则拓展边，若不符合，加入到非活性边表中
	while (m_ActiveEdgeLink.size())
	{
		vector<struct Edge*> m_InsertActiveEdgeLink;          //临时要插入活性边列表
		vector<struct Edge*> m_DeleteActiveEdgeLink;          //临时要删除的活性边列表

		int num = (int)m_ActiveEdgeLink.size();
		//遍历活性边，看邻三角面片是否符合情况
		for (int i = 0; i < num; i++)      //循环寻找活性边，第一次三条边
		{
			m_actedge = m_ActiveEdgeLink[i];   //临时活性边
			if (m_actedge->EdgeAdjoinTriangle.size() == 1)   //活性边的另一侧为空，直接删除此活性边，同时在临界边中加入
			{
				m_DeleteActiveEdgeLink.push_back(m_actedge);
				m_NoActiveEdgeLink.push_back(m_actedge);
			}
			else
			{
				for (int j = 0; j < 2; j++)        //对每条边循环两次，查看两个邻三角形，如果第一个是已加入的三角形，继续，如果第一次就是新的三角形，b循环
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
					//链表中不存在这个三角形，需要插入
					if (flag == 0)
					{
						//邻三角形符合情况
						if (FindedTriangle(m_actriangle->N, m_N, m_Threshold))
						{
							m_FindTriangleLink.push_back(m_ActiveEdgeLink[i]->EdgeAdjoinTriangle[j]);          //三角形加入到链表中
																											   //删除这个活性边
							m_DeleteActiveEdgeLink.push_back(m_actedge);
							for (int k = 0; k < 3; k++)
							{
								if (m_actriangle->Eg[k] != m_actedge)
								{
									int flag_edge = 0;
									for (int m = 0; m < (int)m_ActiveEdgeLink.size(); m++)
									{
										if (m_actriangle->Eg[k] == m_ActiveEdgeLink[m])    //边在链表中，加入到删除链表中
										{
											m_DeleteActiveEdgeLink.push_back(m_actriangle->Eg[k]);
											flag_edge = 1;
											break;
										}
									}
									for (int m = 0; m < (int)m_InsertActiveEdgeLink.size(); m++)
									{
										if (m_actriangle->Eg[k] == m_InsertActiveEdgeLink[m])   //边在要加入的链表中，直接删除
										{
											//在In
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
									if (flag_edge == 0)     //边不在链表，需要加入
									{
										m_InsertActiveEdgeLink.push_back(m_actriangle->Eg[k]);
									}
								}
							}

						}
						//邻三角形不符合情况，将此边加入到临界边链表，同时活性边链表中删除此表
						else
						{
							m_NoActiveEdgeLink.push_back(m_actedge);             //边界边中加入  
							m_DeleteActiveEdgeLink.push_back(m_actedge);         //活性边中删除

						}
						break;
					}
				}
			}

		}

		//活性边该插入
		for (int i = 0; i < (int)m_InsertActiveEdgeLink.size(); i++)
		{
			m_ActiveEdgeLink.push_back(m_InsertActiveEdgeLink[i]);
		}

		//活性边删除
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
	//获取设备DC，该DC为PictureControl的设备
	if (m_pDC == NULL)
	{//如果返回DC为空，则创建DC失败
		return FALSE;
	}
	if (!SetupPixelFormat())
	{//像素格式化函数，简单的说就是指定绘图要用的像素格式，必须格式化，下面有像素格式化的函数体。
		return FALSE;
	}
	//创建绘图描述表
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());

	if (m_hRC == 0)
	{//	创建失败		
		return FALSE;
	}
	// 使绘图描述表为当前调用现程的当前绘图描述表
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		return FALSE;
	}
	//设置清除色
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
	//取到控件的矩形块。
	cx = rect.Width();
	cy = rect.Height();
	GLdouble aspect_ratio; // width/height ratio
	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	// select the full client area
	glViewport(0, 0, cx, cy);
	//指定绘图区域，起点为00，右下为cx,cy
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//此方法视为加载。使。。。生效
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
					if (m_flag1)       //这个边包含了此截面
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
					if (m_flag1)       //这个边包含了此截面
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
					if (m_flag1)       //这个边包含了此截面
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
	}//路径规划结束，以下为显示

	 // TODO: 在此添加控件通知处理程序代码
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
