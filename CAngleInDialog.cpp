// CAngleInDialog.cpp: 구현 파일
//

#include "pch.h"
#include "20200815_image_project.h"
#include "afxdialogex.h"
#include "CAngleInDialog.h"


// CAngleInDialog 대화 상자

IMPLEMENT_DYNAMIC(CAngleInDialog, CDialogEx)

CAngleInDialog::CAngleInDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ANGLE, pParent)
	, m_iAngle(0)
{

}

CAngleInDialog::~CAngleInDialog()
{
}

void CAngleInDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ANGLE_IN, m_iAngle);
}


BEGIN_MESSAGE_MAP(CAngleInDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ANGLE_IN, &CAngleInDialog::OnEnChangeEditAngleIn)
END_MESSAGE_MAP()


// CAngleInDialog 메시지 처리기


void CAngleInDialog::OnEnChangeEditAngleIn()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
