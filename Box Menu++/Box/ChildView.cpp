
// ChildView.cpp : CChildView Ŭ������ ����
//2009253050 �ս¹�

#include "stdafx.h"
#include "Box.h"
#include "ChildView.h"
#include "MainFrm.h"		//���콺 ��ǥ ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_color = RGB(0, 0, 0);				//�ʱⰪ ������
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
END_MESSAGE_MAP()


// CChildView �޽��� ó����

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	//���� ��ȭ Ȯ�ο�
	CFont font;
	font.CreatePointFont(300,_T("�ü�"));
	dc.SelectObject(&font);
	dc.SetTextColor(m_color);

	CRect rect;
	GetClientRect(&rect);
	CString str = _T("�޴� �׽�Ʈ");
	dc.DrawText(str, &rect, DT_CENTER | DT_CENTER | DT_SINGLELINE);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_COPYPEN);

	//���� �����ؼ� �ڽ� ��� ����
	for(int i=0; i<boxes.GetCount(); i++) {
		CPen pen;
		if(differ[i] == 'R'){			//�÷����� �迭�� 'R' �϶� ����� ������ ����
			pen.CreatePen(PS_SOLID, 1, RGB(255,0,0));

		}else if(differ[i] == 'G'){		//�÷����� �迭�� 'G' �϶� ����� �ʷϻ� ����
			pen.CreatePen(PS_SOLID, 1, RGB(0,255,0));

		}else if(differ[i] == 'B'){		//�÷����� �迭�� 'B' �϶� ����� �Ķ��� ����
			pen.CreatePen(PS_SOLID, 1, RGB(0,0,255));

		}else if(differ[i] == ' ')		//�÷����� �迭�� ' ' �϶� ����� ������ ����
			pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));


		dc.SelectObject(&pen);	//������ ����� ����
		dc.Rectangle(boxes[i].left, boxes[i].top, boxes[i].right, boxes[i].bottom);

	}

	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	startx = point.x;
	starty = point.y;

	// ��Ʈ��Ű�� ������ ���콺 ��Ŭ��
	if ( nFlags & MK_CONTROL ) {
		current = -1;
		for(int i=0; i<boxes.GetCount(); i++) {
			if ( boxes[i].left <= point.x && point.x <= boxes[i].right ||
				boxes[i].right <= point.x && point.x <= boxes[i].left ) {

					if (boxes[i].top <= point.y && point.y <= boxes[i].bottom ||
						boxes[i].bottom <= point.y && point.y <= boxes[i].top) {

							current = i;
							move = true;
							break;
					}
			}	
		}
		//ctrl_error = true;		//���콺 �����Ͱ� �ڽ� �� ������ �ƴҰ��
	}

	//��Ʈ��Ű ������ �ʾ��� ��
	else {
		CRect* box = new CRect(point.x, point.y, point.x, point.y);
		boxes.Add(*box);
		current = boxes.GetCount() - 1;
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	if ( nFlags & MK_LBUTTON ) {
		
			if (move == false) {

				CClientDC dc(this);
				dc.SelectStockObject(NULL_BRUSH);
				dc.SetROP2(R2_NOT);

				dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

				//�ڽ� ������ ũ�� ����
				boxes[current].right = point.x;
				boxes[current].bottom = point.y;


				dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

			} else{
				CClientDC dc(this);
				dc.SelectStockObject(NULL_BRUSH);

				//�ڽ� �̵�
				boxes[current].left   += point.x - startx;
				boxes[current].top    += point.y - starty;
				boxes[current].right  += point.x - startx;
				boxes[current].bottom += point.y - starty;

				startx = point.x;
				starty = point.y;

				Invalidate () ;		//�ڽ� �̵��� ���� ��ȭ ������ �ٸ� �ڽ��� ���� ����

			}
	}

	CWnd::OnMouseMove(nFlags, point);
}


//-----------------------���콺 ��Ŭ�� �� �Ҷ��� �������� �ڽ� ������ �����Ͽ���. ---------------------------

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// ���� ��Ʈ�� �������� �϶�(�ڽ� �̵��� or ���ܻ�Ȳ)
	if ( nFlags & MK_CONTROL ){
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		Invalidate () ;		//���� ����޴� Ŀ�ǵ� ���� ���� ���� �ڽ� �� �״�� �̵�

		index = -1;			//�÷����� �迭 �ε��� �ʱ�ȭ 
		current = -1;
		move    = false;
		//ctrl_error = false;

	}

	//��Ʈ�� Ű ������ ���� ���� �϶�
	else if ( current != -1 ) {

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		//dc.SetROP2(R2_COPYPEN);

		// �ڽ� �� ���� ����
		CPen pen;								//�ڽ��� �׸� �� ��ü ����
		pen.CreatePen(PS_SOLID, 1, m_color);	//�޴� ����, ���� 1�� PS_SOLID ��Ÿ�� ������ ����
		dc.SelectObject(&pen);					//���ο� �� ����

		// �ڽ� ���� ������ ���� �� char �迭 ���� differ Ȱ��
		index = current;	//�ڽ� ��ȣ�� �÷����� �迭 �ε��� ��ġ

		if (m_color == RGB(255,0,0)){
			differ[index] = 'R';				//������ �϶�  �÷����� �迭��'R'����
		}else if(m_color == RGB(0,255,0)){
			differ[index] = 'G';				//�ʷϻ� �϶�  �÷����� �迭��'G'����
		}else if(m_color == RGB(0,0,255)){
			differ[index] = 'B';				//�Ķ��� �϶�  �÷����� �迭��'B'����
		}else
			differ[index] = ' ';				//�� �̿ܿ�(����) �÷����� �迭��' '����

		dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

		index = -1;			//�÷����� �迭 �ε��� �ʱ�ȭ 
		current = -1;
		move    = false;
		//ctrl_error = false;
	}

	width = point.x - startx;;				//�ڽ� �ʺ�
	height = point.y - starty;				//�ڽ� ����
	
	//�ʺ� ���̰� ������ ��� ����� ����
	if(width < 0)
		width = -width;
	if(height < 0)
		height = -height;

	//�ڽ� �����ּ� ��ǥ ���¹ٿ� ���
	CString sbox, sbox_info ;
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	sbox.Format(_T("(%4d,%4d)"), startx, starty);			//�ڽ� ���� ��ġ ����
	pMainFrame->m_wndStatusBar.SetPaneText(1, sbox);			//�ڽ� ���� �ּ� ���¹� �ε��� 1�� ���

	sbox_info.Format(_T("(%4d,%4d)"), width, height);		////�ڽ� �ʺ�,���� ����
	pMainFrame->m_wndStatusBar.SetPaneText(2, sbox_info);	//�ڽ� �ʺ�,���� ���¹� �ε��� 2�� ���

	CWnd::OnLButtonUp(nFlags, point);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	current = -1;
	move    = false;
	//ctrl_error = false;		//��Ʈ�� ���� ����

	return 0;
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	startx = point.x;
	starty = point.y;

	for(int i=boxes.GetCount()-1; i>=0; i--) {		//�ֱ� �ڽ����� 
		if ( boxes[i].left <= point.x && point.x <= boxes[i].right ||
			boxes[i].right <= point.x && point.x <= boxes[i].left ) {

				if (boxes[i].top <= point.y && point.y <= boxes[i].bottom ||
					boxes[i].bottom <= point.y && point.y <= boxes[i].top) {

						current = i;			//���� box ��ȣ ����

						CClientDC dc(this);
						dc.SelectStockObject(NULL_BRUSH);
						dc.SetROP2(R2_WHITE);	// ������� ����

						dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);
						boxes.RemoveAt (current, 1) ;
						break;
				}
		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}

//���� ��� �ڵ鷯
void CChildView::OnColorRed()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_color = RGB(255, 0, 0);		//COLORREF Ÿ�� ���� m_color�� ���������� ����
	//differ[index] = 'R';
	//index++;
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_color = RGB(0, 255, 0);		//COLORREF Ÿ�� ���� m_color�� �ʷϻ����� ����
	//differ[index] = 'G';
	//index++;
	Invalidate();
}


void CChildView::OnColorBlue()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_color = RGB(0, 0, 255);		//COLORREF Ÿ�� ���� m_color�� �Ķ������� ����
	//differ[index] = 'B';
	//index++;
	Invalidate();
}


//�޴� �׸� ���� �ڵ鷯
void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI -> SetCheck(m_color == RGB(255,0,0));		//������ �޴� ���ý� üũ ǥ��
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI -> SetCheck(m_color == RGB(0,255,0));		//�ʷϻ� �޴� ���ý� üũ ǥ��
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI -> SetCheck(m_color == RGB(0,0,255));		//�Ķ��� �޴� ���ý� üũ ǥ��
}
