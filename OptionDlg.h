#pragma once


// OptionDlg dialog

class OptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OptionDlg)

public:
	OptionDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~OptionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editMomory;
	CEdit m_editQuality;
	int m_val;

	afx_msg void OnBnClickedOk();
	int m_pWidthRd;
	int m_pWidthPxNum;
	int m_pHeiPxNum;
	int m_nImgRotRd;
	int m_nRenOptRd;
	afx_msg void OnBnClickedWidrd();
//	CEdit m_pWidCTL;
	CEdit m_pWidCTL;
	CEdit m_pHeiCTL;
	CEdit m_pSclCTL;
	afx_msg void OnBnClickedHeird();
	afx_msg void OnBnClickedScaleperd();
	afx_msg void OnBnClickedRennonrd();
	afx_msg void OnBnClickedRndlinrd();
	afx_msg void OnBnClickedRndmurd();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	CEdit m_pMinCTL;
	CEdit m_pMatCTL;
	CEdit m_pBlendBanCTL;
	CEdit m_pBlendSigCTL;
	CEdit m_pGainSigCTL;
	CEdit m_pGainMeanCTL;
//	int m_nMatEdt;
	int m_nMinRd;
};
