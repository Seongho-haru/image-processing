#pragma once
#include "afxdialogex.h"


// CAngleInDialog 대화 상자

class CAngleInDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAngleInDialog)

public:
	CAngleInDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAngleInDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditAngleIn();
	int m_iAngle;
};
