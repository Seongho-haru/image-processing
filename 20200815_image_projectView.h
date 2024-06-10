
// 20200815_image_projectView.h: CMy20200815imageprojectView 클래스의 인터페이스
//

#pragma once


class CMy20200815imageprojectView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMy20200815imageprojectView() noexcept;
	DECLARE_DYNCREATE(CMy20200815imageprojectView)

// 특성입니다.
public:
	CMy20200815imageprojectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy20200815imageprojectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSendMessage();
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSubtraction();
	afx_msg void OnPixelMultiplication();
	afx_msg void OnPixelDivision();
	afx_msg void OnHistogramEqualization();
//	afx_msg void OnHistogramStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSubtraction();
	afx_msg void OnPixelStretching();
	afx_msg void OnRegionMeaning();
	void Convolve(unsigned char** InImg, unsigned char** Resmg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSharpning();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRobert();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	void CopyResultToInput();
	afx_msg void OnOpening();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSubsampling();
	afx_msg void OnGeometryZoomoutAvg();
	afx_msg void OnGeometryRotate();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnGeometryWarping();
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	CString AVIFileName;
	bool bAVIModes;
	void loadAviFile(CDC* pDC);
};

#ifndef _DEBUG  // 20200815_image_projectView.cpp의 디버그 버전
inline CMy20200815imageprojectDoc* CMy20200815imageprojectView::GetDocument() const
   { return reinterpret_cast<CMy20200815imageprojectDoc*>(m_pDocument); }
#endif

