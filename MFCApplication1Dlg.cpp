
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"


#include <vector>
#include <string.h>
#include <math.h>
#include "OptionDlg.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

#ifdef HAVE_OPENCV_XFEATURES2D
#include "opencv2/xfeatures2d/nonfree.hpp"
#endif


#define TEMP_BUFFER_SIZE 1004
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



using namespace std;
using namespace cv;
using namespace cv::detail; 
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nCounter = 0;
	f_name.clear();
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);



	DDX_Control(pDX, IDC_PRGBAR, m_prgBar);
	DDX_Control(pDX, IDC_PROLBL, m_proLable);


	DDX_Control(pDX, IDC_STARTSTBTN, m_pStStitchBtn);
	DDX_Control(pDX, IDC_EXPBTN, m_pExpBtn);
	
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_IMPBTN, &CMFCApplication1Dlg::OnBnClickedImpbtn)
ON_BN_CLICKED(IDC_EXPBTN, &CMFCApplication1Dlg::OnBnClickedExpbtn)

ON_WM_DESTROY()



ON_BN_CLICKED(IDC_STARTSTBTN, &CMFCApplication1Dlg::OnBnClickedStartstbtn)
ON_BN_CLICKED(IDC_BTNHELP, &CMFCApplication1Dlg::OnBnClickedBtnhelp)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	m_prgBar.SetRange(0, 1000);
	m_prgBar.SetPos(0);
	m_proLable.SetWindowTextW(_T("Ready"));
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

		
}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::CreateBitmapInfo(int w, int h, int bpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete[]m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (bpp == 8)
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	else // 24 or 32bit
		m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = bpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (bpp == 8)
	{
		for (int i = 0; i < 256; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = w;
	m_pBitmapInfo->bmiHeader.biHeight = -h;
}

void CMFCApplication1Dlg::DrawImage()
{
	CClientDC dc(GetDlgItem(IDC_RESPIC));

	CRect rect;
	GetDlgItem(IDC_RESPIC)->GetClientRect(&rect);

	SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_matResImage.cols, m_matResImage.rows, m_matResImage.data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}


void CMFCApplication1Dlg::OnBnClickedImpbtn()
{
	f_name.clear();

	CTime cTime = CTime::GetCurrentTime();
	
	
	
		CString str = _T("Image file(*.BMP, *.GIF, *.JPG, *.bmp, *.gif, *.jpg, *.tif, *.png) | *.BMP; *.GIF; *.JPG; *.bmp; *.gif; *.jpg; *.tif; *.png | All file(*.*) | *.* || ");
		
		CString File;

		CString strFileList;

		CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, str, this);

		const int c_cMaxFiles = 400;

		const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;

		dlg.GetOFN().lpstrFile = strFileList.GetBuffer(c_cbBuffSize);

		dlg.GetOFN().nMaxFile = c_cbBuffSize;
		int cnt = 0;
		CString fname[1500];
		if (dlg.DoModal() == IDOK)
		{
			for (POSITION pos = dlg.GetStartPosition(); pos != NULL;)
            {
				File = dlg.GetNextPathName(pos);
				fname[cnt++] = File;
			}

		}
		
		if (cnt == 0) return;
		m_proLable.SetWindowTextW(_T("Importing..."));
		CString temp;
		char file_path[10005];
		Mat img;
        int step = 1000 / cnt - 1;
		int curPos = 0;
		

		for (int i = 0; i < cnt; i++) {		
			temp = fname[i];
			WideCharToMultiByte(CP_ACP, 0, temp.GetBuffer(0), -1, file_path, TEMP_BUFFER_SIZE, 0, 0);
			f_name.push_back(file_path);
			curPos += step;
			m_prgBar.SetPos(curPos);
		}
		m_prgBar.SetPos(1000);
		m_proLable.SetWindowTextW(_T("Import Complete"));

}



void CMFCApplication1Dlg::OnBnClickedExpbtn()
{
	if (!m_matResImage.empty()) {
		static TCHAR BASED_CODE szFilter[] = _T("Image file(*.BMP, *.GIF, *.JPG, *.jpg, *.png, *.bmp, *.tiff, *.gif) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif;*.png |All file(*.*)|*.*||");

		CFileDialog dlg(FALSE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);

		if (IDOK == dlg.DoModal())
		{
			char szTemp[100] = "";

			CString pathName = dlg.GetPathName();
			WideCharToMultiByte(CP_ACP, 0, pathName.GetBuffer(0), -1, szTemp, TEMP_BUFFER_SIZE, 0, 0);
			cv::imwrite(szTemp, m_matResImage);
			
			f_name.clear();

            #ifndef ONLINE_JUDGE
                FILE* stream;
                freopen_s(&stream, "report.txt", "w", stdout);
            #endif



            CTime data = GetCurrentTime();
            printf("Date: %d %d %d", data.GetYear(), data.GetMonth(), data.GetDay());
            MessageBox(_T("It was saved successfully."));
            f_name.clear();

		}

	}
	else {

		MessageBox(_T("You don't have result image. Please do stitch working."));
	}
}






bool CMFCApplication1Dlg::CalStitching() {
  

        Mat result;
        string result_name = "result.jpg";
        int num_images = f_name.size();
        vector<Mat> m_vImages;

        Mat temp;

        int step = 500 / num_images - 1;
        int curPos = 0;
       
        for (int i = 0; i < num_images; i++) {
            curPos += step;
            m_prgBar.SetPos(curPos);
            temp = imread(f_name[i]);
            if (temp.empty()) return false;
			resize(temp, temp, Size(1024, 768));
            m_vImages.push_back(temp);
        }
        
        m_prgBar.SetPos(500);


		Mat pano;
		Stitcher::Mode mode = Stitcher::SCANS;
		Ptr<Stitcher> stitcher = Stitcher::create(mode);
		Stitcher::Status status = stitcher->stitch(m_vImages, result);
        if (status != Stitcher::OK) return false;
	
		std::vector<cv::Point> nonBlackList;
		nonBlackList.reserve(result.rows * result.cols);
        m_prgBar.SetPos(1000);

		for (int j = 0; j < result.rows; ++j)
			for (int i = 0; i < result.cols; ++i)
			{
				// if not black: add to the list
				if (result.at<cv::Vec3b>(j, i) != cv::Vec3b(0, 0, 0))
				{
					nonBlackList.push_back(cv::Point(i, j));
				}
			}

		// create bounding rect around those points
		cv::Rect bb = cv::boundingRect(nonBlackList);
        cv::imwrite(result_name, result(bb));
        m_vImages.clear();
        return true;
        
}



void CMFCApplication1Dlg::OnBnClickedStartstbtn()
{
  
    UpdateData(true);
    if (f_name.size() != 0) {
        OptionDlg dlg;

        if (f_name.size() >= 2) {
            if (dlg.DoModal() == IDOK) {



                m_proLable.SetWindowTextW(_T("Stitching..."));
                m_prgBar.SetPos(0);
                m_pStStitchBtn.SetWindowTextW(_T("Stop Stitching"));
                bool result_flg = CalStitching();
                if (!result_flg) {
                    MessageBox(_T("Can't stitching from choosen images"));
                    return;
                }
                Mat pano;
                pano = imread("result.jpg");
                m_matResImage = pano.clone();
				cv::resize(m_matResImage, m_matResImage, Size(dlg.m_pWidthPxNum, dlg.m_pHeiPxNum));
                CreateBitmapInfo(m_matResImage.cols, m_matResImage.rows, m_matResImage.channels() * 8);
                DrawImage();
                m_prgBar.SetPos(1000);
                MessageBox(_T("Stitching was successful."));

                m_proLable.SetWindowTextW(_T("Ready"));
                m_prgBar.SetPos(0);
                m_pStStitchBtn.SetWindowTextW(_T("Start Stitching"));

            }
        }
        else {

            MessageBox(_T("Please import over 2 Images "));
            f_name.clear();

        }

    }
    else {
        MessageBox(_T("Please import Images to stitch"));
        f_name.clear();
        return;
    }
    // TODO: Add your control notification handler code here
}


void CMFCApplication1Dlg::OnBnClickedBtnhelp()
{
    CAboutDlg test;
    test.DoModal();
    // TODO: Add your control notification handler code here
}
