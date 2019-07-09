
// RemoveFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RemoveFiles.h"
#include "RemoveFilesDlg.h"
#include "afxdialogex.h"
#include <filesystem>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CRemoveFilesDlg dialog



CRemoveFilesDlg::CRemoveFilesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REMOVEFILES_DIALOG, pParent),
	outFolder(_T("C:"))
	, fromDate(time(0))
	, toDate(time(0))
	, created(FALSE)
	, modified(FALSE)
	, accessed(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRemoveFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FOLDER_CHOSE, outFolder);
	DDX_Check(pDX, IDC_CHECK_MODIFIED, modified);
	DDX_Check(pDX, IDC_CHECK_CREATED, created);
	DDX_Check(pDX, IDC_CHECK_ACCESSED, accessed);
}

BEGIN_MESSAGE_MAP(CRemoveFilesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CRemoveFilesDlg::OnBnClickedButtonBrowse)
	ON_EN_CHANGE(IDC_EDIT_FOLDER_CHOSE, &CRemoveFilesDlg::OnEnChangeEditFolderChose)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_FROM, &CRemoveFilesDlg::OnDatetimechangeDatetimepickerFrom)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TO, &CRemoveFilesDlg::OnDtnDatetimechangeDatetimepickerTo)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CRemoveFilesDlg::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CRemoveFilesDlg message handlers

BOOL CRemoveFilesDlg::OnInitDialog()
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

	ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRemoveFilesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRemoveFilesDlg::OnPaint()
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
HCURSOR CRemoveFilesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRemoveFilesDlg::OnBnClickedButtonBrowse()
{
	UpdateData();
	CShellManager* pShellManager = theApp.GetShellManager();
	ASSERT_VALID(pShellManager);
	if (pShellManager->BrowseForFolder(outFolder, this, _T("C:")))
	{
		std::wstring ws(outFolder);
		std::string str(ws.begin(), ws.end());
		outFolderSTD = str;
		UpdateData(FALSE);
	}
}






void CRemoveFilesDlg::OnEnChangeEditFolderChose()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}





void CRemoveFilesDlg::OnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	fromDate = pDTChange->st;
	*pResult = 0;
}


void CRemoveFilesDlg::OnDtnDatetimechangeDatetimepickerTo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	toDate = pDTChange->st;
	*pResult = 0;
}

BOOL CRemoveFilesDlg::CheckIfTimeInRange(CTime stCreate, CTime stModify, CTime stAccessed)
{
	if (created)
	{
		if (stCreate > fromDate && stCreate < toDate)
		{
			return TRUE;
		}
	}
	else if (modified)
	{
		if (stModify > fromDate && stModify < toDate)
		{
			return TRUE;
		}
	}
	else if (accessed)
	{
		if (stAccessed > fromDate && stAccessed < toDate)
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}

}

void CRemoveFilesDlg::RemoveSelectedFiles(std::vector<std::string> filesInDirectoryToDelete)
{
	for (auto const& entry : filesInDirectoryToDelete) {
		std::experimental::filesystem::remove(entry);
	}
}

void CRemoveFilesDlg::OnBnClickedButtonDelete()
{

	try
	{
		//Update checkbox info
		UpdateData();

		//Get all names
		std::experimental::filesystem::recursive_directory_iterator iter(outFolderSTD);
		std::experimental::filesystem::recursive_directory_iterator end;

		while (iter != end)
		{
			
			
			
			//handle time
			HANDLE hFileMap;
			FILETIME ftCreate, ftModify, ftAccess;
			SYSTEMTIME stCreate, stModify, stAccess;
			hFileMap = CreateFileA(iter->path().string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFileMap == INVALID_HANDLE_VALUE)
			{
				std::error_code ec;
			}

			if (!GetFileTime(hFileMap, &ftCreate, &ftAccess ,&ftModify))
			{
				std::error_code ec;
				
			}
			FileTimeToSystemTime(&ftAccess, &stAccess);
			FileTimeToSystemTime(&ftCreate, &stCreate);
			FileTimeToSystemTime(&ftModify, &stModify);
			


			

			//Check if time in range
			BOOL ifADD = CheckIfTimeInRange(stCreate, stModify, stAccess);
			if (ifADD)
			{
				//check if not directory
				if (!std::experimental::filesystem::is_directory(iter->path()))
				{				
					filesInDirectoryToDelete.push_back(iter->path().string());
				}

			}

			std::error_code ec;
			iter.increment(ec);
			//Close File
			CloseHandle(hFileMap);

		}

		RemoveSelectedFiles(filesInDirectoryToDelete);

	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception :: " << e.what();
	}

}




