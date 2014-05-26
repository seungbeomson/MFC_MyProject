
// ChildView.cpp : CChildView 클래스의 구현
//2009253050 손승범

#include "stdafx.h"
#include "Box.h"
#include "ChildView.h"
#include "MainFrm.h"		//마우스 좌표 출력

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_color = RGB(0, 0, 0);				//초기값 검정색
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


// CChildView 메시지 처리기

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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	//색상 변화 확인용
	CFont font;
	font.CreatePointFont(300,_T("궁서"));
	dc.SelectObject(&font);
	dc.SetTextColor(m_color);

	CRect rect;
	GetClientRect(&rect);
	CString str = _T("메뉴 테스트");
	dc.DrawText(str, &rect, DT_CENTER | DT_CENTER | DT_SINGLELINE);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_COPYPEN);

	//색상 구분해서 박스 출력 루프
	for(int i=0; i<boxes.GetCount(); i++) {
		CPen pen;
		if(differ[i] == 'R'){			//컬러구분 배열이 'R' 일때 펜색상 빨간색 설정
			pen.CreatePen(PS_SOLID, 1, RGB(255,0,0));

		}else if(differ[i] == 'G'){		//컬러구분 배열이 'G' 일때 펜색상 초록색 설정
			pen.CreatePen(PS_SOLID, 1, RGB(0,255,0));

		}else if(differ[i] == 'B'){		//컬러구분 배열이 'B' 일때 펜색상 파란색 설정
			pen.CreatePen(PS_SOLID, 1, RGB(0,0,255));

		}else if(differ[i] == ' ')		//컬러구분 배열이 ' ' 일때 펜색상 검은색 설정
			pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));


		dc.SelectObject(&pen);	//설정된 펜색상 선택
		dc.Rectangle(boxes[i].left, boxes[i].top, boxes[i].right, boxes[i].bottom);

	}

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	startx = point.x;
	starty = point.y;

	// 컨트롤키를 누르고 마우스 좌클릭
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
		//ctrl_error = true;		//마우스 포인터가 박스 안 범위가 아닐경우
	}

	//컨트롤키 누르지 않았을 때
	else {
		CRect* box = new CRect(point.x, point.y, point.x, point.y);
		boxes.Add(*box);
		current = boxes.GetCount() - 1;
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	if ( nFlags & MK_LBUTTON ) {
		
			if (move == false) {

				CClientDC dc(this);
				dc.SelectStockObject(NULL_BRUSH);
				dc.SetROP2(R2_NOT);

				dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

				//박스 생성시 크기 변경
				boxes[current].right = point.x;
				boxes[current].bottom = point.y;


				dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

			} else{
				CClientDC dc(this);
				dc.SelectStockObject(NULL_BRUSH);

				//박스 이동
				boxes[current].left   += point.x - startx;
				boxes[current].top    += point.y - starty;
				boxes[current].right  += point.x - startx;
				boxes[current].bottom += point.y - starty;

				startx = point.x;
				starty = point.y;

				Invalidate () ;		//박스 이동시 색깔 변화 없으며 다른 박스에 영향 없음

			}
	}

	CWnd::OnMouseMove(nFlags, point);
}


//-----------------------마우스 좌클릭 업 할때를 기준으로 박스 선색상 설정하였음. ---------------------------

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 먼저 컨트롤 누른상태 일때(박스 이동시 or 예외상황)
	if ( nFlags & MK_CONTROL ){
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		Invalidate () ;		//현재 색상메뉴 커맨드 영향 없이 원래 박스 색 그대로 이동

		index = -1;			//컬러구분 배열 인덱스 초기화 
		current = -1;
		move    = false;
		//ctrl_error = false;

	}

	//컨트롤 키 누르지 않은 상태 일때
	else if ( current != -1 ) {

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		//dc.SetROP2(R2_COPYPEN);

		// 박스 선 색상 설정
		CPen pen;								//박스를 그릴 펜 객체 생성
		pen.CreatePen(PS_SOLID, 1, m_color);	//메뉴 색상값, 폭은 1인 PS_SOLID 스타일 펜으로 지정
		dc.SelectObject(&pen);					//새로운 펜 선택

		// 박스 색상 정보가 있을 때 char 배열 변수 differ 활용
		index = current;	//박스 번호와 컬러구분 배열 인덱스 일치

		if (m_color == RGB(255,0,0)){
			differ[index] = 'R';				//빨간색 일때  컬러구분 배열에'R'저장
		}else if(m_color == RGB(0,255,0)){
			differ[index] = 'G';				//초록색 일때  컬러구분 배열에'G'저장
		}else if(m_color == RGB(0,0,255)){
			differ[index] = 'B';				//파란색 일때  컬러구분 배열에'B'저장
		}else
			differ[index] = ' ';				//그 이외에(검정) 컬러구분 배열에' '저장

		dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

		index = -1;			//컬러구분 배열 인덱스 초기화 
		current = -1;
		move    = false;
		//ctrl_error = false;
	}

	width = point.x - startx;;				//박스 너비
	height = point.y - starty;				//박스 높이
	
	//너비 높이가 음수일 경우 양수로 변경
	if(width < 0)
		width = -width;
	if(height < 0)
		height = -height;

	//박스 시작주소 좌표 상태바에 출력
	CString sbox, sbox_info ;
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	sbox.Format(_T("(%4d,%4d)"), startx, starty);			//박스 시작 위치 설정
	pMainFrame->m_wndStatusBar.SetPaneText(1, sbox);			//박스 시작 주소 상태바 인덱스 1에 출력

	sbox_info.Format(_T("(%4d,%4d)"), width, height);		////박스 너비,높이 설정
	pMainFrame->m_wndStatusBar.SetPaneText(2, sbox_info);	//박스 너비,높이 상태바 인덱스 2에 출력

	CWnd::OnLButtonUp(nFlags, point);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	current = -1;
	move    = false;
	//ctrl_error = false;		//컨트롤 에러 구분

	return 0;
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	startx = point.x;
	starty = point.y;

	for(int i=boxes.GetCount()-1; i>=0; i--) {		//최근 박스부터 
		if ( boxes[i].left <= point.x && point.x <= boxes[i].right ||
			boxes[i].right <= point.x && point.x <= boxes[i].left ) {

				if (boxes[i].top <= point.y && point.y <= boxes[i].bottom ||
					boxes[i].bottom <= point.y && point.y <= boxes[i].top) {

						current = i;			//지울 box 번호 설정

						CClientDC dc(this);
						dc.SelectStockObject(NULL_BRUSH);
						dc.SetROP2(R2_WHITE);	// 흰색으로 지움

						dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);
						boxes.RemoveAt (current, 1) ;
						break;
				}
		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}

//색상값 명령 핸들러
void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(255, 0, 0);		//COLORREF 타입 변수 m_color값 빨간색으로 설정
	//differ[index] = 'R';
	//index++;
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 255, 0);		//COLORREF 타입 변수 m_color값 초록색으로 설정
	//differ[index] = 'G';
	//index++;
	Invalidate();
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 0, 255);		//COLORREF 타입 변수 m_color값 파란색으로 설정
	//differ[index] = 'B';
	//index++;
	Invalidate();
}


//메뉴 항목 갱신 핸들러
void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI -> SetCheck(m_color == RGB(255,0,0));		//빨간색 메뉴 선택시 체크 표시
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI -> SetCheck(m_color == RGB(0,255,0));		//초록색 메뉴 선택시 체크 표시
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI -> SetCheck(m_color == RGB(0,0,255));		//파란색 메뉴 선택시 체크 표시
}
