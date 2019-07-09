
// RemoveFilesDlg.h : header file
//

#pragma once
#include <vector>

// CRemoveFilesDlg dialog
class CRemoveFilesDlg : public CDialogEx
{
// Construction
public:
	CRemoveFilesDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOVEFILES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
//Dialog data
private:
	CString outFolder;
	std::string outFolderSTD;
	CTime toDate;
	CTime fromDate;
	std::vector<std::string> filesInDirectoryToDelete;
	BOOL created;
	BOOL modified;
	BOOL accessed;

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
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnEnChangeEditFolderChose();
	afx_msg void OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepickerTo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
	BOOL CheckIfTimeInRange(CTime stCreate, CTime stModify, CTime stAccessed);
	void RemoveSelectedFiles(std::vector<std::string> filesInDirectoryToDelete);
};
