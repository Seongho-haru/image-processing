
// 20200815_image_projectView.cpp: CMy20200815imageprojectView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include <cmath>

#include "CAngleInDialog.h"
#include <Vfw.h>
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20200815_image_project.h"
#endif

#include "20200815_image_projectDoc.h"
#include "20200815_image_projectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20200815imageprojectView

IMPLEMENT_DYNCREATE(CMy20200815imageprojectView, CScrollView)

BEGIN_MESSAGE_MAP(CMy20200815imageprojectView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
//	ON_COMMAND(MESSAGE, &CMy20200815imageprojectView::OnSendMessage)
	ON_COMMAND(ID_PIXEL_ADD, &CMy20200815imageprojectView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUBTRACTION, &CMy20200815imageprojectView::OnPixelSubtraction)
	ON_COMMAND(ID_PIXEL_MULTIPLICATION, &CMy20200815imageprojectView::OnPixelMultiplication)
	ON_COMMAND(ID_PIXEL_DIVISION, &CMy20200815imageprojectView::OnPixelDivision)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CMy20200815imageprojectView::OnHistogramEqualization)
//	ON_COMMAND(ID_HISTOGRAM_STRETCHING, &CMy20200815imageprojectView::OnHistogramStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CMy20200815imageprojectView::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CMy20200815imageprojectView::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUBTRACTION, &CMy20200815imageprojectView::OnPixelTwoImageSubtraction)
	ON_COMMAND(ID_PIXEL_STRETCHING, &CMy20200815imageprojectView::OnPixelStretching)
	ON_COMMAND(ID_REGION_MEANING, &CMy20200815imageprojectView::OnRegionMeaning)
	ON_COMMAND(ID_REGION_SHARPNING, &CMy20200815imageprojectView::OnRegionSharpning)
	ON_COMMAND(ID_REGION_PREWITT, &CMy20200815imageprojectView::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERT, &CMy20200815imageprojectView::OnRegionRobert)
	ON_COMMAND(ID_REGION_SOBEL, &CMy20200815imageprojectView::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CMy20200815imageprojectView::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CMy20200815imageprojectView::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CMy20200815imageprojectView::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CMy20200815imageprojectView::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CMy20200815imageprojectView::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CMy20200815imageprojectView::OnMopologyDilation)
	ON_COMMAND(ID_OPENING, &CMy20200815imageprojectView::OnOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CMy20200815imageprojectView::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CMy20200815imageprojectView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CMy20200815imageprojectView::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CMy20200815imageprojectView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUBSAMPLING, &CMy20200815imageprojectView::OnGeometryZoomoutMeanSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CMy20200815imageprojectView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CMy20200815imageprojectView::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CMy20200815imageprojectView::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CMy20200815imageprojectView::OnGeometryFlip)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CMy20200815imageprojectView::OnGeometryWarping)
//	ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_COMMAND(ID_AVI_VIEW, &CMy20200815imageprojectView::OnAviView)
END_MESSAGE_MAP()

// CMy20200815imageprojectView 생성/소멸

CMy20200815imageprojectView::CMy20200815imageprojectView() noexcept
{
	bAVIModes = false;

}

CMy20200815imageprojectView::~CMy20200815imageprojectView()
{
}

BOOL CMy20200815imageprojectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMy20200815imageprojectView 그리기

void CMy20200815imageprojectView::OnDraw(CDC* pDC)
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	// pDC->TextOutA(100, 100, "안녕하세요");

	int x, y;
	if (bAVIModes) {
		loadAviFile(pDC);
		bAVIModes = false;
		return;
	}
	if (pDoc->InputImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++)
			{
				for (x = 0; x < pDoc->ImageWidth; x++)
				{
					pDC->SetPixel(x , y, RGB(pDoc->InputImg[y][x],
						pDoc->InputImg[y][x],
						pDoc->InputImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
			{
				for (x = 0; x < pDoc->ImageWidth; x++)
				{
					pDC->SetPixel(x , y, RGB(pDoc->InputImg[y][x*3+0],
						pDoc->InputImg[y][x*3+1],
						pDoc->InputImg[y][x*3+2]));
				}
			}
		}
		
	}
	if (pDoc->ResultImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++)
			{
				for (x = 0; x < pDoc->ImageWidth; x++)
				{
					pDC->SetPixel(x+(pDoc->ImageWidth + 20)*1, y, RGB(pDoc->ResultImg[y][x],
						pDoc->ResultImg[y][x],
						pDoc->ResultImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
			{
				for (x = 0; x < pDoc->ImageWidth; x++)
				{
					pDC->SetPixel(x + (pDoc->ImageWidth + 20) * 1, y, RGB(pDoc->ResultImg[y][x * 3 + 0],
						pDoc->ResultImg[y][x * 3 + 1],
						pDoc->ResultImg[y][x * 3 + 2]));
				}
			}
		}

	}
	if (pDoc->InputImg2 != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++)
			{
				for (x = 0; x < pDoc->ImageWidth; x++)
				{
					pDC->SetPixel(x + (pDoc->ImageWidth + 20) * 2, y, RGB(pDoc->InputImg2[y][x],
						pDoc->InputImg2[y][x],
						pDoc->InputImg2[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++)
			{
				for (x = 0; x < pDoc->ImageWidth; x++)
				{
					pDC->SetPixel(x + (pDoc->ImageWidth + 20) * 2, y, RGB(pDoc->InputImg2[y][x * 3 + 0],
						pDoc->InputImg2[y][x * 3 + 1],
						pDoc->InputImg2[y][x * 3 + 2]));
				}
			}
		}

	}
	if (pDoc->gResultImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->gImageHeight; y++)
			{
				for (x = 0; x < pDoc->gImageWidth; x++)
				{
					pDC->SetPixel(x + (pDoc->gImageWidth + 20) * 0, y + (pDoc->ImageHeight + 20) * 1, RGB(pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->gImageHeight; y++)
			{
				for (x = 0; x < pDoc->gImageWidth; x++)
				{
					pDC->SetPixel(x + (pDoc->gImageWidth + 20) * 0, y + (pDoc->ImageHeight + 20) * 1, RGB(pDoc->gResultImg[y][x * 3 + 0],
						pDoc->gResultImg[y][x * 3 + 1],
						pDoc->gResultImg[y][x * 3 + 2]));
				}
			}
		}

	}
}

void CMy20200815imageprojectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMy20200815imageprojectView 인쇄

BOOL CMy20200815imageprojectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy20200815imageprojectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy20200815imageprojectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy20200815imageprojectView 진단

#ifdef _DEBUG
void CMy20200815imageprojectView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy20200815imageprojectView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy20200815imageprojectDoc* CMy20200815imageprojectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20200815imageprojectDoc)));
	return (CMy20200815imageprojectDoc*)m_pDocument;
}
#endif //_DEBUG

//void CMy20200815imageprojectView::OnSendMessage()
//{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	AfxMessageBox("안녕하세요");
//}


void CMy20200815imageprojectView::OnPixelAdd()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (pDoc->InputImg == NULL) return;
	int value;
	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			value = pDoc->InputImg[y][x] + 40;
			if (value > 255) value = 255;
			else if (value < 0)value = 0;
			else
				pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelSubtraction()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int value;
	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = pDoc->InputImg[y][x] - 40;
			if (value > 255) value = 255;
			else if (value < 0)value = 0;
			else
				pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelMultiplication()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int value;
	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = pDoc->InputImg[y][x] * 1.2;
			if (value > 255) value = 255;
			else if (value < 0)value = 0;
			else
				pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelDivision()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int value;
	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = pDoc->InputImg[y][x] / 1.2;
			if (value > 255) value = 255;
			else if (value < 0)value = 0;
			else
				pDoc->ResultImg[y][x] = value;
		}
	}
	Invalidate();
}


void CMy20200815imageprojectView::OnHistogramEqualization()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int x, y, k;
	int hist[256],sum[256];
	int acc_hist=0;
	int N = pDoc->ImageHeight * pDoc->ImageWidth;

	for (k = 0; k < 256; k++) hist[k] = 0; //밝기 크기

	//히스토그램 구하기
	for (y = 0; y < pDoc->ImageHeight; y++) 
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			hist[pDoc->InputImg[y][x]]++;
		}
	//누적분포 구하기
	for (k = 0; k < 256; k++) 
	{
		acc_hist += hist[k];
		sum[k] = acc_hist;
 	}

	//
	for (y = 0; y < pDoc->ImageHeight; y++) 
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			k = pDoc->InputImg[y][x];
			pDoc->ResultImg[y][x] = (float)sum[k] * 256/N;
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelBinarization()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int x, y;
	int threadhold = 128;

	for (y = 0; y < pDoc->ImageHeight; y++) 
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			if (pDoc->InputImg[y][x] > threadhold) pDoc->ResultImg[y][x] = 255;
			else pDoc->ResultImg[y][x] = 0;
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelTwoImageAdd()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	CFileDialog dig(true);
	CFile file;
	if (dig.DoModal() == IDCANCEL) return;

	file.Open(dig.GetPathName(),CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
	
	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{	
			if (pDoc->depth == 1) {
				pDoc->ResultImg[y][x] = pDoc->InputImg[y][x] * 0.5 + pDoc->InputImg2[y][x] * 0.5;
			}
			else {
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[y][x * 3 + 0] * 0.5 + pDoc->InputImg2[y][x * 3] * 0.5;
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[y][x * 3 + 1] * 0.5 + pDoc->InputImg2[y][x * 1] * 0.5;
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[y][x * 3 + 2] * 0.5 + pDoc->InputImg2[y][x * 2] * 0.5;
			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelTwoImageSubtraction()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	CFileDialog dig(true);
	CFile file;
	if (dig.DoModal() == IDCANCEL) return;

	file.Open(dig.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x, y;
	int value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = abs(pDoc->InputImg[y][x] - pDoc->InputImg2[y][x] );
			if (value > 150) value = 255;
			else value = 0;
			pDoc->ResultImg[y][x] = value;
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnPixelStretching()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int max = 255;
	int min = 0;
	int k, y, x,value,hist[256];

	for (k = 0; k < 256; k++) hist[k] = 0; //밝기 크기

	//히스토그램 구하기
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			hist[pDoc->InputImg[y][x]]++;
		}

	//max값 구하기 
	for (int i = 256; i > 0; i--) {
		if (hist[i] != 0) {
			max = i;
			break;
		}
	}

	//min값 구하기 
	for (int i = 0; i < 256; i++) {
		if (hist[i] != 0) {
			min = i;
			break;
		}
	}

	// 이미지 처리
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = (int)((double)(pDoc->InputImg[y][x] - min) / (max - min) * 255);
			pDoc->ResultImg[y][x] = value;
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnRegionMeaning()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	float mask[3][3] = { 
		{1 / 9.0,1 / 9.0,1 / 9.0},
		{1 / 9.0,1 / 9.0,1 / 9.0},
		{1 / 9.0,1 / 9.0,1 / 9.0} };
	
	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, mask, 0, pDoc->depth);
	Invalidate();
}


void CMy20200815imageprojectView::Convolve(unsigned char** InImg, unsigned char** Resmg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y,i,j;
	int sum,rsum,gsum,bsum;
	for (y = 1; y < rows-1; y++)
		for (x = 1; x < cols-1; x++) {
			if (depth == 1) {
				sum = 0;
				for (j = 0; j < 3; j++) 
					for (i = 0; i < 3; i++) {
						sum += InImg[y + j - 1][x + i - 1] * mask[j][i];
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				Resmg[y][x] = sum;
			}
			else {
				rsum = 0;
				gsum = 0;
				bsum = 0;
				for (j = 0; j < 3; j++) 
					for (i = 0; i < 3; i++) {
						rsum += InImg[y + j - 1][(x + i - 1) * 3 + 0] * mask[j][i];
						gsum += InImg[y + j - 1][(x + i - 1) * 3 + 1] * mask[j][i];
						bsum += InImg[y + j - 1][(x + i - 1) * 3 + 2] * mask[j][i];
					}
				rsum += bias;
				gsum += bias;
				bsum += bias;
				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;
				Resmg[y][x * 3 + 0] = rsum;
				Resmg[y][x * 3 + 1] = gsum;
				Resmg[y][x * 3 + 2] = bsum;
				
			}
			
		}

}


void CMy20200815imageprojectView::OnRegionSharpning()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	float mask[3][3] = {	
		{0 ,-1, 0},
		{-1, 5,-1},
		{0 ,-1, 0} };

	Convolve(pDoc->InputImg, pDoc->ResultImg, pDoc->ImageWidth, pDoc->ImageHeight, mask, 0, pDoc->depth);
	Invalidate();
}


void CMy20200815imageprojectView::OnRegionPrewitt()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	float maskH[3][3] = { {-1,0,0},
						  {1,0,-1},
						  {1,0,-1} };
	float maskV[3][3] = { {1 , 1, 1},
						  {0 , 0, 0},
						  {-1,-1,-1} };
	int i;
	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, maskV, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, maskH, 0, pDoc->depth);

	int x, y;
	int sum;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{	
			sum = sqrt(Er[y][x]* Er[y][x] + Ec[y][x]*Ec[y][x]);
			if (sum > 255) sum = 255;
			else if (sum < 0) sum = 0;
			pDoc->ResultImg[y][x] = sum;
		}
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
	}
	free(Er);
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Ec[i]);
	}
	free(Ec);
	Invalidate();
}


void CMy20200815imageprojectView::OnRegionRobert()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	float maskH[3][3] = { {1,0,-1},
						  {1,0,-1},
						  {1,0,-1} };
	float maskV[3][3] = { {1 , 1, 1},
						  {0 , 0, 0},
						  {-1,-1,-1} };
	int i;
	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, maskV, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, maskH, 0, pDoc->depth);

	int x, y;
	int sum;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			sum = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
			if (sum > 255) sum = 255;
			else if (sum < 0) sum = 0;
			pDoc->ResultImg[y][x] = sum;
		}
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
	}
	free(Er);
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Ec[i]);
	}
	free(Ec);
	Invalidate();
}


void CMy20200815imageprojectView::OnRegionSobel()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	float maskH[3][3] = { {1,0,-1},
						  {2,0,-2},
						  {1,0,-1} };
	float maskV[3][3] = { {-1, -2,-1},
						  {0 , 0, 0},
						  {1 , 2, 1} };
	int i;
	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, maskV, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, maskH, 0, pDoc->depth);

	int x, y;
	int sum;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			sum = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
			if (sum > 255) sum = 255;
			else if (sum < 0) sum = 0;
			pDoc->ResultImg[y][x] = sum;
		}
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Er[i]);
	}
	free(Er);
	for (i = 0; i < pDoc->ImageHeight; i++) {
		free(Ec[i]);
	}
	free(Ec);
	Invalidate();
}


void CMy20200815imageprojectView::OnRegionAverageFiltering()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int x, y, i, j, sum, rsum, gsum, bsum;

	// 5 * 5영역의 평균값
	for (y = 2; y < pDoc->ImageHeight-2; y++)
		for (x = 2; x < pDoc->ImageWidth -2; x++)
		{
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = -2; j <= +2; j++)
					for (i = -2; i <= +2; i++)
					{
						sum += pDoc->InputImg[y + j][x + i];
					}
				sum /= 25;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				pDoc->ResultImg[y][x] = sum;
			}
			else {
				rsum = 0;
				gsum = 0;
				bsum = 0;
				for (j = -2; j <= +2; j++)
					for (i = -2; i <= +2; i++)
					{
						rsum += pDoc->InputImg[y + j][(3 * (x + i)) + 0];
						gsum += pDoc->InputImg[y + j][(3 * (x + i)) + 1];
						bsum += pDoc->InputImg[y + j][(3 * (x + i)) + 2];
					}
				rsum /= 25;
				gsum /= 25;
				bsum /= 25;
				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;
				pDoc->ResultImg[y][x * 3 + 0] = rsum;
				pDoc->ResultImg[y][x * 3 + 1] = gsum;
				pDoc->ResultImg[y][x * 3 + 2] = bsum;
			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnRegionMedianFiltering()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int x, y, i, j,temp;
	int n[9];

	// 5 * 5영역의 평균값
	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			/*
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++) {
					n[(j + 1) * 3 + (i + 1)] = pDoc->InputImg[y + j][x + i];
				}
			*/

			if (pDoc->depth == 1) {
				n[0] = pDoc->InputImg[y - 1][x - 1];
				n[1] = pDoc->InputImg[y - 1][x - 0];
				n[2] = pDoc->InputImg[y - 1][x + 1];
				n[3] = pDoc->InputImg[y - 0][x - 1];
				n[4] = pDoc->InputImg[y - 0][x - 0];
				n[5] = pDoc->InputImg[y - 0][x + 1];
				n[6] = pDoc->InputImg[y + 1][x - 1];
				n[7] = pDoc->InputImg[y + 1][x - 0];
				n[8] = pDoc->InputImg[y + 1][x + 1];

				//버블정렬 => 오름차순

				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][x] = n[4];
			}
			else {
				// red
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 0];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 0];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 0];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 0];

				//버블정렬 => 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][x*3+0] = n[4];

				// green
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 1];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 1];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 1];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 1];

				//버블정렬 => 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][x*3+1] = n[4];

				// blue
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 2];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 2];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 2];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 2];

				//버블정렬 => 오름차순
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++) {
						if (n[j] > n[j + 1]) {
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
					}
				pDoc->ResultImg[y][x*3+2] = n[4];
			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnMopologyColorGray(){
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for(y = 0; y<pDoc -> ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			gray = (pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3;
			pDoc->InputImg[y][3 * x + 0] = gray;
			pDoc->InputImg[y][3 * x + 1] = gray;
			pDoc->InputImg[y][3 * x + 2] = gray;
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnMopologyBinarization()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int x, y;
	int th = 100;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			
			if (pDoc->depth == 1) {
				if (pDoc->InputImg[y][x] > th)
					pDoc->InputImg[y][x] = 255;
				else
					pDoc->InputImg[y][x] = 0;
			}
			else {
				if (pDoc->InputImg[y][3 * x + 0] > th) {
					pDoc->InputImg[y][3 * x + 0] = 255;
					pDoc->InputImg[y][3 * x + 1] = 255;
					pDoc->InputImg[y][3 * x + 2] = 255;
				}
				else {
					pDoc->InputImg[y][3 * x + 0] = 0;
					pDoc->InputImg[y][3 * x + 1] = 0;
					pDoc->InputImg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnMopologyErosion()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int x, y, min, i, j;
	int rmin, gmin, bmin;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++) {
			
			if (pDoc->depth==1) {
				min = 255;
				for (i = -1; i <= 1; i++)
					for (j = -1; j <= 1; j++) {
						if (min > pDoc->InputImg[y + i][x + j]) {
							min = pDoc->InputImg[y + i][x + j];
						}
					}
				pDoc->ResultImg[y][x] = min;
			}
			else {
				rmin = 255;
				gmin = 255;
				bmin = 255;
				for (i = -1; i <= 1; i++)
					for (j = -1; j <= 1; j++) {
						if (rmin > pDoc->InputImg[y + i][3 * (x + j) + 0]) rmin = pDoc->InputImg[y + i][3 * (x + j) + 0];
						if (gmin > pDoc->InputImg[y + i][3 * (x + j) + 1]) gmin = pDoc->InputImg[y + i][3 * (x + j) + 1];
						if (bmin > pDoc->InputImg[y + i][3 * (x + j) + 2]) bmin = pDoc->InputImg[y + i][3 * (x + j) + 2];
					}
				pDoc->ResultImg[y][3 * (x + j) + 0] = rmin;
				pDoc->ResultImg[y][3 * (x + j) + 1] = gmin;
				pDoc->ResultImg[y][3 * (x + j) + 2] = bmin;
			}
			
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnMopologyDilation()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int x, y, max, i, j;
	int rmax, gmax, bmax;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++) {
			if (pDoc->depth == 1) {
				max = 0;
				for (i = -1; i <= 1; i++)
					for (j = -1; j <= 1; j++) {
						if (max < pDoc->InputImg[y + i][x + j]) {
							max = pDoc->InputImg[y + i][x + j];
						}
					}
				pDoc->ResultImg[y][x] = max;
			}
			else {
				rmax = 0;
				gmax = 0;
				bmax = 0;
				for (i = -1; i <= 1; i++)
					for (j = -1; j <= 1; j++) {
						if (rmax < pDoc->InputImg[y + i][3*(x + j)+0]) rmax = pDoc->InputImg[y + i][3 * (x + j) + 0];
						if (gmax < pDoc->InputImg[y + i][3*(x + j)+1]) gmax = pDoc->InputImg[y + i][3 * (x + j) + 1];
						if (bmax < pDoc->InputImg[y + i][3*(x + j)+2]) bmax = pDoc->InputImg[y + i][3 * (x + j) + 2];
					}
				pDoc->ResultImg[y][3 * x + 0] = rmax;
				pDoc->ResultImg[y][3 * x + 1] = gmax;
				pDoc->ResultImg[y][3 * x + 2] = bmax;

			}
			
		}
	Invalidate();
}


void CMy20200815imageprojectView::CopyResultToInput()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	int y, x;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++) {
			pDoc->InputImg[y][x] = pDoc->ResultImg[y][x];
		}
}

void CMy20200815imageprojectView::OnOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
}


void CMy20200815imageprojectView::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
}


void CMy20200815imageprojectView::OnGeometryZoominPixelCopy()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int scale_x = 3;
	int scale_y = 3;

	int i,j, x, y;

	pDoc->gImageWidth = pDoc->ImageWidth * scale_x;
	pDoc->gImageHeight = pDoc->ImageHeight * scale_y;

	//메모리 활당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향사상
	/*
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			for (j = 0; j < scale_y; j++) {
				for (i = 0; i < scale_x; i++) {
					pDoc->gResultImg[y * scale_y+j][x * scale_x+i] = pDoc->InputImg[y][x];
				}
			}
		}*/
	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->gResultImg[y][x] = pDoc->InputImg[y / scale_y][x / scale_x];
			}
			else {
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y / scale_y][3 * (x / scale_x) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y / scale_y][3 * (x / scale_x) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y / scale_y][3 * (x / scale_x) + 2];
			}
		}
	
	Invalidate();
}


void CMy20200815imageprojectView::OnGeometryZoominInterpolation()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	float scale_x = 1.7;
	float scale_y = 1.2;

	float src_x, src_y;
	int E, F;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;

	int i, j, x, y;

	pDoc->gImageWidth = pDoc->ImageWidth * scale_x+1;
	pDoc->gImageHeight = pDoc->ImageHeight * scale_y+1;

	//메모리 활당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++) 
		{
			src_x = x / scale_x;
			src_y = y / scale_y;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;

			Bx = Ax + 1;
			By = Ay;

			Cx = Ax;
			Cy = Ay +1;

			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;


			if (pDoc->depth == 1) {
				E = (1 - alpha) * pDoc->InputImg[Ay][Ax] + alpha * pDoc->InputImg[By][Bx];
				F = (1 - alpha) * pDoc->InputImg[Cy][Cx] + alpha * pDoc->InputImg[Dy][Dx];

				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else {
				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 0] + alpha * pDoc->InputImg[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 0] + alpha * pDoc->InputImg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 1] + alpha * pDoc->InputImg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 1] + alpha * pDoc->InputImg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 2] + alpha * pDoc->InputImg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 2] + alpha * pDoc->InputImg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;

			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnGeometryZoomoutSubsampling()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int scale_x = 3; // 1/3을 의미
	int scale_y = 3;
	int x, y, i;

	if (pDoc->gResultImg != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
		pDoc->gResultImg = NULL;
	}
	pDoc->gImageWidth = pDoc->ImageWidth / scale_x;
	pDoc->gImageHeight = pDoc->ImageHeight / scale_y;

	//메모리 활당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1) {
				pDoc->gResultImg[y][x] = pDoc->InputImg[y * scale_y][x * scale_x];
			}
			else {
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y * scale_y][3 * (x * scale_x) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y * scale_y][3 * (x * scale_x) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y * scale_y][3 * (x * scale_x) + 2];
			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnGeometryZoomoutMeanSubsampling()
{
	OnRegionMeaning();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}


void CMy20200815imageprojectView::OnGeometryZoomoutAvg()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int scale_x = 3; // 1/3을 의미
	int scale_y = 2;
	int x, y, i, sum, j;
	int src_x, src_y;
	int rsum, gsum, bsum;

	if (pDoc->gResultImg != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
		pDoc->gResultImg = NULL;
	}
	pDoc->gImageWidth = pDoc->ImageWidth / scale_x +1;
	pDoc->gImageHeight = pDoc->ImageHeight / scale_y+1;

	//메모리 활당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향 사상
	for (y = 0; y < pDoc->ImageHeight; y+=scale_y)
		for (x = 0; x < pDoc->ImageWidth; x+=scale_x)
		{
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = 0; j < scale_y; j++) {
					for (i = 0; i < scale_x; i++) {
						src_x = x + i;
						src_y = y + j;
						if (src_x > pDoc->ImageWidth - 1)src_x = pDoc->ImageWidth - 1;
						if (src_y > pDoc->ImageHeight - 1)src_y = pDoc->ImageHeight - 1;
						sum += pDoc->InputImg[src_y][src_x];
					}

				}
				pDoc->gResultImg[y / scale_y][x / scale_x] = sum / (scale_x * scale_y);
			}
			else {
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < scale_y; j++) {
					for (i = 0; i < scale_x; i++) {
						src_x = x + i;
						src_y = y + j;
						if (src_x > pDoc->ImageWidth - 1)src_x = pDoc->ImageWidth - 1;
						if (src_y > pDoc->ImageHeight - 1)src_y = pDoc->ImageHeight - 1;
						rsum += pDoc->InputImg[src_y][3 * src_x + 0];
						gsum += pDoc->InputImg[src_y][3 * src_x + 1];
						bsum += pDoc->InputImg[src_y][3 * src_x + 2];
					}
				}
				pDoc->gResultImg[y / scale_y][3 * (x / scale_x) + 0] = rsum / (scale_x * scale_y);
				pDoc->gResultImg[y / scale_y][3 * (x / scale_x) + 1] = gsum / (scale_x * scale_y);
				pDoc->gResultImg[y / scale_y][3 * (x / scale_x) + 2] = bsum / (scale_x * scale_y);
			}
		}
	Invalidate();
}

#define Pi 3.141592
void CMy20200815imageprojectView::OnGeometryRotate()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int angle = 30;//dgree 

	int i, x, y, Cx, Cy, Oy;
	int xdiff, ydiff;
	int x_source, y_source;
	float radian;

	CAngleInDialog dlg;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	if (pDoc->gResultImg != NULL) {
		for (i = 0; i < pDoc->gImageHeight; i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
		pDoc->gResultImg = NULL;
	}
	radian = Pi / 180 * angle;

	pDoc->gImageWidth = pDoc->ImageHeight * fabs(cos(Pi / 2 - radian)) + pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(Pi / 2 - radian));

	//메모리 활당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++) {
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	

	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	//y의 마지막 
	Oy = pDoc->ImageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	//역방향 사상
	for (y = -ydiff; y< pDoc->gImageHeight-ydiff; y++) {
		for (x = -xdiff; x< pDoc->gImageWidth; x++) {
			x_source = ((Oy - y) - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Oy - (((Oy - y) - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);
			if (pDoc->depth == 1) {

				if (x_source<0 || x_source> pDoc->ImageWidth - 1 || y_source<0 || y_source>pDoc->ImageHeight - 1)
					pDoc->gResultImg[y + ydiff][x + xdiff] = 0;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->InputImg[y_source][x_source];
			}
			else {
				if (x_source<0 || x_source> pDoc->ImageWidth - 1 || y_source<0 || y_source>pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 0;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 0;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 0;
				}
				else {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImg[y_source][3*x_source+0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImg[y_source][3*x_source+1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImg[y_source][3*x_source+2];
				}
			}
		}
	}
	Invalidate();
}


void CMy20200815imageprojectView::OnGeometryMirror()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int x, y;
	for(y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->ResultImg[y][x] = pDoc->InputImg[y][pDoc->ImageWidth - 1 - x];
			}
			else {
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	Invalidate();
}


void CMy20200815imageprojectView::OnGeometryFlip()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();

	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				pDoc->ResultImg[pDoc->ImageHeight - 1 - y][x] = pDoc->InputImg[y][x];
			}
			else {
				pDoc->ResultImg[pDoc->ImageHeight - 1 - y][3 * x + 0] = pDoc->InputImg[y][3 * x + 0];
				pDoc->ResultImg[pDoc->ImageHeight - 1 - y][3 * x + 1] = pDoc->InputImg[y][3 * x + 1];
				pDoc->ResultImg[pDoc->ImageHeight - 1 - y][3 * x + 2] = pDoc->InputImg[y][3 * x + 2];
			}
		}
	Invalidate();
}

typedef struct  {
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = { 100,100,150,150 };
control_line mctrl_dest = { 100,100,200,200 };

void CMy20200815imageprojectView::OnGeometryWarping()
{
	CMy20200815imageprojectDoc* pDoc = GetDocument();
	control_line source_lines[5] = { {100, 100, 150, 150},
	   {0, 0, pDoc->ImageWidth - 1, 0},
	   {pDoc->ImageWidth - 1, 0, pDoc->ImageWidth - 1, pDoc->ImageHeight - 1},
	   {pDoc->ImageWidth - 1, pDoc->ImageHeight - 1, 0, pDoc->ImageHeight - 1},
	   {0, pDoc->ImageHeight - 1, 0, 0} };

	control_line dest_lines[5] = { {100, 100, 200, 200},
	   {0, 0, pDoc->ImageWidth - 1, 0},
	   {pDoc->ImageWidth - 1, 0, pDoc->ImageWidth - 1, pDoc->ImageHeight - 1},
	   {pDoc->ImageWidth - 1, pDoc->ImageHeight - 1, 0, pDoc->ImageHeight - 1},
	   {0, pDoc->ImageHeight - 1, 0, 0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;
	double u;
	double h;
	double d;
	double tx, ty;
	double xp, yp;

	double weight;
	double totalWeight;
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, x2, y1, y2;
	int src_x1, src_y1, src_x2, src_y2;

	double src_line_length, dest_line_length;
	int num_lines = 5;         // 제어선의 수
	int line;
	int source_x, source_y;
	int last_row, last_col;
	last_row = pDoc->ImageHeight- 1;
	last_col = pDoc->ImageWidth - 1;

	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth; x++) {
			tx = 0.0;
			ty = 0.0;
			totalWeight = 0.0;

			for (line = 0; line < num_lines; line++) {
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / (double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = (double)((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0) d = sqrt((double)(x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1) d = sqrt((double)(x - x2) * (x - x2) + (y - y2) * (y - y2));
				else d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((double)(src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow((pow((double)(dest_line_length),p) / (a + d)) , b); 

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalWeight += weight;
			}
			source_x = x + (int)(tx / totalWeight + 0.5);
			source_y = y + (int)(ty / totalWeight + 0.5);

			if (source_x < 0) source_x = 0;
			if (source_x > last_col) source_x = last_col;
			if (source_y < 0) source_y = 0;
			if (source_y > last_row) source_y = last_row;
			if (pDoc->depth == 1) {
				pDoc->ResultImg[y][x] = pDoc->InputImg[source_y][source_x];
			}
			else {
				pDoc->ResultImg[y][3 * x + 0] = pDoc->InputImg[source_y][3 * source_x + 0];
				pDoc->ResultImg[y][3 * x + 1] = pDoc->InputImg[source_y][3 * source_x + 1];
				pDoc->ResultImg[y][3 * x + 2] = pDoc->InputImg[source_y][3 * source_x + 2];
			}
			
		}
	}
	Invalidate();
}
CPoint mpos_st, mpos_end;

void CMy20200815imageprojectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMy20200815imageprojectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;
	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);
	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);

	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;

	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax > Bx)	mctrl_source.Px = Ax + (Bx - Ax) / 2;
	else			mctrl_source.Px = Ax + (Ax - Bx) / 2;
	if (Ay > By)	mctrl_source.Py = Ay + (By - Ay) / 2;
	else			mctrl_source.Py = Ay + (Ay - By) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;
	CScrollView::OnLButtonUp(nFlags, point);
}


void CMy20200815imageprojectView::OnAviView()
{
	CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Avi화일(*.avi)|*.avi|모든화일|*.*|");

	if(dlg.DoModal()==IDOK){
		AVIFileName = dlg.GetPathName();
		bAVIModes = true;
		Invalidate();
	}
}


void CMy20200815imageprojectView::loadAviFile(CDC* pDC)
{
	LPBITMAPINFOHEADER pbmih;
	PAVIFILE pavi;
	PAVISTREAM pstm = NULL;
	PGETFRAME pfrm = NULL;
	AVIFILEINFO fi;
	AVISTREAMINFO si;
	int stm;
	int frame;
	int x, y;
	unsigned char* image;
	LPBITMAPCOREHEADER pbmpih;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ | OF_SHARE_DENY_NONE,NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++) {
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO) {
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			
			for (frame = 0; frame < si.dwLength; frame++) {
				pbmih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmih) continue;
				image = (unsigned char*)((LPSTR)pbmih + (WORD)pbmih->biSize);
				/*
				for (y = 0; y < fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++)
						pDC->SetPixel(x, fi.dwHeight - y - 1,
							RGB(
								image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]
							)
						);*/
				pDC->SetStretchBltMode(COLORONCOLOR);
				::SetDIBitsToDevice(pDC->GetSafeHdc(),
					0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth,
					image,(BITMAPINFO*)pbmih,DIB_RGB_COLORS);
				Sleep(33);
			}
		}
	}
	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();

}
