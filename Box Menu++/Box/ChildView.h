
// ChildView.h : CChildView 클래스의 인터페이스
//2009253050 손승범


#pragma once


// CChildView 창

class CChildView : public CWnd
{
#define COLOR_INDEX 100			//컬러 구별 배열 변수 인덱스 개수 설정

	CArray<CRect, CRect&> boxes; // 박스 객체 리스트
	int current;
	char differ[COLOR_INDEX];	//컬러 구별 배열 변수
	int index;					//컬러 구별 배열 변수 인덱스
	bool move;
	//bool ctrl_error;			//컨트롤 누르고 빈공간 누를시 에러체크 변수
	int startx;
	int starty;
	int width;					//박스 너비
	int height;					//박스 높이

// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	COLORREF m_color;

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
};

