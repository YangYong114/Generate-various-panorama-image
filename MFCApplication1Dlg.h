
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

// MFCApplication1Dlg.h : header file
//

#pragma once

using namespace std;
using namespace cv;
// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool CalStitching();
	afx_msg void OnBnClickedImpbtn();
	void CreateBitmapInfo(int w, int h, int bpp);
	void DrawImage();
//	CEdit m_editCnt;
	BITMAPINFO* m_pBitmapInfo;

	
	Mat m_matResImage;
//	CEdit m_editWid;
//	CEdit m_editHei;
//	afx_msg void OnBnClickedStabtn();
	
	afx_msg void OnBnClickedExpbtn();
//	CComboBox m_cmbShape;
	CProgressCtrl m_prgBar;
	CStatic m_proLable;
	int m_nCounter;
//	bool m_staBtn;
	CWinThread* m_pThread;
	HANDLE hThread;
	
	CStatic m_disCnt;
	
	CBitmap m_background;

	vector<string> f_name;
//	afx_msg void OnBnClickedBtnhelp();

//	afx_msg void OnBnClickedStartstbtn();
	CButton m_pStStitchBtn;
	CButton m_pExpBtn;
	afx_msg void OnBnClickedStartstbtn();
	afx_msg void OnBnClickedBtnhelp();
	
};
