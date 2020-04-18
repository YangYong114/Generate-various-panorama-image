// OptionDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication1.h"
#include "OptionDlg.h"
#include "afxdialogex.h"


// OptionDlg dialog

IMPLEMENT_DYNAMIC(OptionDlg, CDialogEx)

OptionDlg::OptionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPTIONDLG, pParent)
	, m_pWidthRd(0)
	, m_pWidthPxNum(0)
	, m_pHeiPxNum(0)
	, m_nImgRotRd(0)
	, m_nRenOptRd(0)
	
	, m_nMinRd(0)
{

}

OptionDlg::~OptionDlg()
{
}

void OptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOMORY, m_editMomory);
	DDX_Control(pDX, IDC_QUALITY, m_editQuality);
	DDX_Radio(pDX, IDC_WIDRD, m_pWidthRd);
	DDX_Text(pDX, IDC_WIDEDT, m_pWidthPxNum);
	DDX_Text(pDX, IDC_HEIEDT, m_pHeiPxNum);
	DDX_Radio(pDX, IDC_IMGNONRD, m_nImgRotRd);
	DDX_Radio(pDX, IDC_RENNONRD, m_nRenOptRd);

	DDX_Control(pDX, IDC_WIDEDT, m_pWidCTL);
	DDX_Control(pDX, IDC_HEIEDT, m_pHeiCTL);
	DDX_Control(pDX, IDC_EDIT1, m_pSclCTL);
	DDX_Control(pDX, IDC_MINSZEDT, m_pMinCTL);
	DDX_Control(pDX, IDC_EDIT2, m_pMatCTL);
	DDX_Control(pDX, IDC_BLENDBEDT, m_pBlendBanCTL);
	DDX_Control(pDX, IDC_BLENDSEDT, m_pBlendSigCTL);
	DDX_Control(pDX, IDC_GAINSGEDT, m_pGainSigCTL);
	DDX_Control(pDX, IDC_GAINMNEDT, m_pGainMeanCTL);

	DDX_Radio(pDX, IDC_RADIO5, m_nMinRd);
}


BEGIN_MESSAGE_MAP(OptionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &OptionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_WIDRD, &OptionDlg::OnBnClickedWidrd)
	ON_BN_CLICKED(IDC_HEIRD, &OptionDlg::OnBnClickedHeird)
	ON_BN_CLICKED(IDC_SCALEPERD, &OptionDlg::OnBnClickedScaleperd)
	ON_BN_CLICKED(IDC_RENNONRD, &OptionDlg::OnBnClickedRennonrd)
	ON_BN_CLICKED(IDC_RNDLINRD, &OptionDlg::OnBnClickedRndlinrd)
	ON_BN_CLICKED(IDC_RNDMURD, &OptionDlg::OnBnClickedRndmurd)
	ON_BN_CLICKED(IDC_RADIO5, &OptionDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &OptionDlg::OnBnClickedRadio6)
END_MESSAGE_MAP()


// OptionDlg message handlers


BOOL OptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_editMomory.SetWindowTextW(_T("0.5"));
	m_editQuality.SetWindowTextW(_T("100"));
	// TODO:  Add extra initialization here
	m_val = 100;
	m_pBlendBanCTL.EnableWindow(false);
	m_pBlendSigCTL.EnableWindow(false);
	m_pGainMeanCTL.EnableWindow(false);
	m_pGainSigCTL.EnableWindow(false);
	m_pHeiCTL.EnableWindow(false);
	m_pSclCTL.EnableWindow(false);
	m_pWidCTL.EnableWindow(true);
	m_pMinCTL.EnableWindow(true);
	m_pMatCTL.EnableWindow(false);
	m_pWidthPxNum = 1024;
	m_pHeiPxNum = 768;
	m_pWidCTL.SetWindowTextW(_T("1920"));
	m_pHeiCTL.SetWindowTextW(_T("1080"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void OptionDlg::OnBnClickedOk()
{
	CString ql;
	m_editQuality.GetWindowTextW(ql);
	m_val = _wtoi(ql);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void OptionDlg::OnBnClickedWidrd()
{
	m_pHeiCTL.EnableWindow(false);
	m_pSclCTL.EnableWindow(false);
	m_pWidCTL.EnableWindow(true);

	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedHeird()
{
	m_pWidCTL.EnableWindow(false);
	m_pSclCTL.EnableWindow(false);
	m_pHeiCTL.EnableWindow(true);

	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedScaleperd()
{
	m_pHeiCTL.EnableWindow(false);
	m_pWidCTL.EnableWindow(false);
	m_pSclCTL.EnableWindow(true);

	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedRennonrd()
{
	m_pBlendBanCTL.EnableWindow(false);
	m_pBlendSigCTL.EnableWindow(false);
	m_pGainMeanCTL.EnableWindow(false);
	m_pGainSigCTL.EnableWindow(false);
	
	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedRndlinrd()
{
	m_pBlendBanCTL.EnableWindow(false);
	m_pBlendSigCTL.EnableWindow(false);
	m_pGainMeanCTL.EnableWindow(false);
	m_pGainSigCTL.EnableWindow(false);

	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedRndmurd()
{
	m_pBlendBanCTL.EnableWindow(true);
	m_pBlendSigCTL.EnableWindow(true);
	m_pGainMeanCTL.EnableWindow(true);
	m_pGainSigCTL.EnableWindow(true);

	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedRadio5()
{
	m_pMinCTL.EnableWindow(true);
	m_pMatCTL.EnableWindow(false);

	// TODO: Add your control notification handler code here
}


void OptionDlg::OnBnClickedRadio6()
{
	m_pMinCTL.EnableWindow(false);
	m_pMatCTL.EnableWindow(true);

	// TODO: Add your control notification handler code here
}
