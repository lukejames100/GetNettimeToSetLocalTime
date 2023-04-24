
// MFCGetNTPandSetSystemTimeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMFCGetNTPandSetSystemTimeDlg 对话框
class CMFCGetNTPandSetSystemTimeDlg : public CDialogEx
{
// 构造
public:
	CMFCGetNTPandSetSystemTimeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCGETNTPANDSETSYSTEMTIME_DIALOG };

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
	CEdit m_edit_time;
	afx_msg void OnBnClickedButton1();
	void displaymsg(CString str);
	int Get_Time_t(time_t &ttime);
};
