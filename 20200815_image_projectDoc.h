
// 20200815_image_projectDoc.h: CMy20200815imageprojectDoc 클래스의 인터페이스
//


#pragma once


class CMy20200815imageprojectDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMy20200815imageprojectDoc() noexcept;
	DECLARE_DYNCREATE(CMy20200815imageprojectDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMy20200815imageprojectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//unsigned char InputImg[256][256];
	//unsigned char Resultumg[256][256];
	//unsigned char InputImg2[256][256];

	//이중 포인터 사용
	unsigned char **InputImg;
	unsigned char **ResultImg;
	unsigned char **InputImg2;

	void LoadSecondImageFile(CArchive& ar);

	int ImageWidth;
	int ImageHeight;
	int depth; //1 = 흑백 , 3 = 컬러
	void LoadImageFile(CArchive& ar);

	int gImageWidth;
	int gImageHeight;
	unsigned char** gResultImg;
};
