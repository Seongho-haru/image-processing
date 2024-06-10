
// 20200815_image_projectDoc.cpp: CMy20200815imageprojectDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20200815_image_project.h"
#endif

#include "20200815_image_projectDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRT_SECURE_NO_WARNNIFS

// CMy20200815imageprojectDoc

IMPLEMENT_DYNCREATE(CMy20200815imageprojectDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy20200815imageprojectDoc, CDocument)
END_MESSAGE_MAP()


// CMy20200815imageprojectDoc 생성/소멸

CMy20200815imageprojectDoc::CMy20200815imageprojectDoc() noexcept
{	
	InputImg = NULL;
	ResultImg = NULL;
	InputImg2 = NULL;
	gResultImg = NULL;
}

CMy20200815imageprojectDoc::~CMy20200815imageprojectDoc()
{
	int i;
	if (InputImg != NULL) {
		for ( i = 0; i < ImageHeight; i++) 
			free(InputImg[i]);
		free(InputImg);
	}
	if (InputImg2 != NULL) {
		for ( i = 0; i < ImageHeight; i++) 
			free(InputImg2[i]);
		free(InputImg2);
	}
	if (ResultImg != NULL) {
		for ( i = 0; i < ImageHeight; i++) 
			free(ResultImg[i]);
		free(ResultImg);
	}
	if (gResultImg != NULL) {
		for (i = 0; i < gImageHeight; i++) 
			free(gResultImg[i]);
		free(gResultImg);
	}
}


BOOL CMy20200815imageprojectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy20200815imageprojectDoc serialization

void CMy20200815imageprojectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar.Write(ResultImg, 256 * 256);
	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy20200815imageprojectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMy20200815imageprojectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy20200815imageprojectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy20200815imageprojectDoc 진단

#ifdef _DEBUG
void CMy20200815imageprojectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy20200815imageprojectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CMy20200815imageprojectDoc::LoadSecondImageFile(CArchive& ar)
{
	char type[16], buf[256];
	int maxValue, i,width,height,d;

	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	bool isbmp = false;

	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0) {
		ar.ReadString(type, 15);

		do { //#으로 시작하는 문자는 버려야하기때문에 사용
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &width, &height);

		do { //#으로 시작하는 문자는 버려야하기때문에 사용
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) d = 1;
		else d = 3;

	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0) {
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256 x 256크기의 파일만 사용가능 합니다.");
			return;
		}
		height = 256;
		width = 256;
		d = 1;
	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0) {
		//bmpmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		//BMP파일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) return;

		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));

		width = bih.biWidth;
		height = bih.biHeight;
		d = bih.biBitCount / 8;

		if (depth == 1) {
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}

	if (ImageHeight != height || ImageWidth != width || depth != d) {
		AfxMessageBox("가로,새로,색상수가 같아야만 처리할수 있습니다.");
		return;
	}
	InputImg2 = (unsigned char**)malloc(height * sizeof(unsigned char*));
	for (i = 0; i < height; i++) {
		InputImg2[i] = (unsigned char*)malloc(width * d);
	}
	//파일에서 데이터 읽기
	if (!isbmp) {
		//파일에서 읽어서 저장
		for (i = 0; i < height; i++) {
			ar.Read(InputImg2[i], width * d);
		}
	}
	else {
		//파일에서 읽어서 저장
		BYTE nu[4];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (i = 0; i < ImageHeight; i++) {
			if (depth == 1) {
				ar.Read(InputImg2[ImageHeight -1-i], ImageWidth * depth);
			}
			else {
				for (int j = 0; j < ImageWidth; j++) {
					BYTE r, g, b;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);

					InputImg2[ImageHeight - 1 - i][3 * j + 0] = r;
					InputImg2[ImageHeight - 1 - i][3 * j + 1] = g;
					InputImg2[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}
			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}
}


void CMy20200815imageprojectDoc::LoadImageFile(CArchive& ar)
{
	char type[16], buf[256];
	int maxValue,i;

	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	bool isbmp = false;

	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0) {
		ar.ReadString(type, 15);

		do { //#으로 시작하는 문자는 버려야하기때문에 사용
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d %d", &ImageWidth, &ImageHeight);

		do { //#으로 시작하는 문자는 버려야하기때문에 사용
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;

	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0) {
		//bmpmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		//BMP파일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) return;

		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));

		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1) {
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0) {
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256 x 256크기의 파일만 사용가능 합니다.");
			return;
		}
		ImageHeight = 256;
		ImageWidth = 256;
		depth = 1;
	}

	//메모리 활당
	InputImg = (unsigned char **)malloc(ImageHeight*sizeof(unsigned char*));
	ResultImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < ImageHeight; i++) {
		InputImg[i] = (unsigned char*)malloc(ImageWidth * depth);
		ResultImg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp) {
		//파일에서 읽어서 저장
		for (i = 0; i < ImageHeight; i++) {
			ar.Read(InputImg[i], ImageWidth * depth);
		}
	}
	else {
		//파일에서 읽어서 저장
		BYTE nu[4];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (i = 0; i < ImageHeight; i++) {
			if (depth == 1) {
				ar.Read(InputImg[ImageHeight - 1 - i], ImageWidth * depth);
			}
			else {
				for (int j = 0; j < ImageWidth; j++) {
					BYTE r, g, b;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);

					InputImg[ImageHeight - 1 - i][3 * j + 0] = r;
					InputImg[ImageHeight - 1 - i][3 * j + 1] = g;
					InputImg[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}
			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}
}
