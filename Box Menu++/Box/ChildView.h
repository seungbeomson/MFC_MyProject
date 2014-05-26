
// ChildView.h : CChildView Ŭ������ �������̽�
//2009253050 �ս¹�


#pragma once


// CChildView â

class CChildView : public CWnd
{
#define COLOR_INDEX 100			//�÷� ���� �迭 ���� �ε��� ���� ����

	CArray<CRect, CRect&> boxes; // �ڽ� ��ü ����Ʈ
	int current;
	char differ[COLOR_INDEX];	//�÷� ���� �迭 ����
	int index;					//�÷� ���� �迭 ���� �ε���
	bool move;
	//bool ctrl_error;			//��Ʈ�� ������ ����� ������ ����üũ ����
	int startx;
	int starty;
	int width;					//�ڽ� �ʺ�
	int height;					//�ڽ� ����

// �����Դϴ�.
public:
	CChildView();

// Ư���Դϴ�.
public:
	COLORREF m_color;

// �۾��Դϴ�.
public:

// �������Դϴ�.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildView();

	// ������ �޽��� �� �Լ�
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

