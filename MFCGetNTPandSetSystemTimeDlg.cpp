
// MFCGetNTPandSetSystemTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCGetNTPandSetSystemTime.h"
#include "MFCGetNTPandSetSystemTimeDlg.h"
#include "afxdialogex.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#pragma comment (lib,"Ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
struct NTPPacket
{
	union{
		struct _ControlWord
		{
			unsigned int uLI:2;
			unsigned int uVersion:3;
			unsigned int uMode:3;
			unsigned int uStratum:8;

			int nPoll:8;
			int nPrecision:8;
		};

		int nControlWord;
	};

	int nRootDelay;
	int nRootDispersion;
	int nReferenceIdentifier;

	__int64 n64ReferenceTimestamp;
	__int64 n64OriginateTimestamp;
	__int64 n64ReceiveTimestamp;

	int nTransmitTimestampSeconds;
	int nTransmitTimesStampFractions;
};

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCGetNTPandSetSystemTimeDlg 对话框



CMFCGetNTPandSetSystemTimeDlg::CMFCGetNTPandSetSystemTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCGetNTPandSetSystemTimeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGetNTPandSetSystemTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_time);
}

BEGIN_MESSAGE_MAP(CMFCGetNTPandSetSystemTimeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCGetNTPandSetSystemTimeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCGetNTPandSetSystemTimeDlg 消息处理程序

BOOL CMFCGetNTPandSetSystemTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCGetNTPandSetSystemTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCGetNTPandSetSystemTimeDlg::OnPaint()
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
HCURSOR CMFCGetNTPandSetSystemTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCGetNTPandSetSystemTimeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	time_t t;
	CString dlpstr;
	if(Get_Time_t(t)==0)
	{
		dlpstr="获取时间错误";
		displaymsg(dlpstr);
		return;
	}
	tm temptm;
	
	localtime_s(&temptm,&t);
	SYSTEMTIME st={1900+temptm.tm_year,1+temptm.tm_mon,temptm.tm_wday,temptm.tm_mday,temptm.tm_hour,temptm.tm_min,temptm.tm_sec,0};
	//BOOL re=SetSystemTime(&st);
	BOOL re=SetLocalTime(&st);
	//if(re==TRUE)
	//	MessageBox("true");
	//else
	//	MessageBox("false");
	CString dstr;
	char buf[80]={0};
	dstr.Format("%4d-%d-%d %d:%d:%d",temptm.tm_year+1900,temptm.tm_mon+1,temptm.tm_mday,temptm.tm_hour,temptm.tm_min,temptm.tm_sec);
	displaymsg(dstr);
	//displaymsg(
}

void CMFCGetNTPandSetSystemTimeDlg::displaymsg(CString str)
{
	m_edit_time.SetWindowText(str);
	UpdateData(FALSE);
}

int CMFCGetNTPandSetSystemTimeDlg::Get_Time_t(time_t &ttime)
{
	ttime=0;
	WSADATA wsaData;

	char hoststr[]="ntp.ntsc.ac.cn";

	int iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iResult!=0) return 0;
	int result,count;
	int sockfd=0;

	//域名转ip
	struct hostent *hptr=NULL;
	if((hptr=gethostbyname(hoststr))==NULL)
	{
		WSACleanup();
		return 0;
	}

	sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockfd<0)
		{
			WSACleanup();
			return 0;
	}
	fd_set pending_data;
	timeval block_time;
	NTPPacket ntpSend={0};
	ntpSend.nControlWord=0x1B;
	NTPPacket ntpRecv;
	SOCKADDR_IN addr_server;
	addr_server.sin_family=AF_INET;
	addr_server.sin_port=htons(123);
	CopyMemory(&addr_server.sin_addr.S_un.S_addr,hptr->h_addr_list[0],hptr->h_length);
	SOCKADDR_IN sock;
	int len=sizeof(sock);
	if((result=sendto(sockfd,(const char*)&ntpSend,sizeof(NTPPacket),0,(SOCKADDR*)&addr_server,sizeof(SOCKADDR)))<0)
	{
		int err=WSAGetLastError();
		WSACleanup();
		return 0;
	}
	FD_ZERO(&pending_data);
	FD_SET(sockfd,&pending_data);
	block_time.tv_sec=10;//10秒超时
	block_time.tv_usec=0;
	if(select(sockfd+1,&pending_data,NULL,NULL,&block_time)>0)
	{
		if((count=recvfrom(sockfd,(char*)&ntpRecv,sizeof(NTPPacket),0,(SOCKADDR*)&sock,&len))>0)
			ttime=ntohl(ntpRecv.nTransmitTimestampSeconds)-2208988800;
	}
	closesocket(sockfd);
	WSACleanup();
	return 1;
}