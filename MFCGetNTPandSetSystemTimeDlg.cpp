
// MFCGetNTPandSetSystemTimeDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCGetNTPandSetSystemTimeDlg �Ի���



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


// CMFCGetNTPandSetSystemTimeDlg ��Ϣ�������

BOOL CMFCGetNTPandSetSystemTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCGetNTPandSetSystemTimeDlg::OnPaint()
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
HCURSOR CMFCGetNTPandSetSystemTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCGetNTPandSetSystemTimeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	time_t t;
	CString dlpstr;
	if(Get_Time_t(t)==0)
	{
		dlpstr="��ȡʱ�����";
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

	//����תip
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
	block_time.tv_sec=10;//10�볬ʱ
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