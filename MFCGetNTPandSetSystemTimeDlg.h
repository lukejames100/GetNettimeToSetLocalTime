
// MFCGetNTPandSetSystemTimeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMFCGetNTPandSetSystemTimeDlg �Ի���
class CMFCGetNTPandSetSystemTimeDlg : public CDialogEx
{
// ����
public:
	CMFCGetNTPandSetSystemTimeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCGETNTPANDSETSYSTEMTIME_DIALOG };

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
	CEdit m_edit_time;
	afx_msg void OnBnClickedButton1();
	void displaymsg(CString str);
	int Get_Time_t(time_t &ttime);
};
