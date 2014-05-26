
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Box.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

	BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
		ON_WM_CREATE()
		ON_WM_SETFOCUS()
		ON_UPDATE_COMMAND_UI(ID_INDICATOR_POS, OnUpdatePos)

	END_MESSAGE_MAP()

	static UINT indicators[] =
	{
		ID_SEPARATOR,           // 상태 줄 표시기
		ID_INDICATOR_POS,		//상태바에 마우스 위치 표시 구역 할당
		ID_SEPARATOR,			// 너비 높이 상태 표시 구역 할당
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
	};

	// CMainFrame 생성/소멸

	CMainFrame::CMainFrame()
	{
		// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	}

	CMainFrame::~CMainFrame()
	{
	}

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;

		// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
		if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
		{
			TRACE0("뷰 창을 만들지 못했습니다.\n");
			return -1;
		}

		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("상태 표시줄을 만들지 못했습니다.\n");
			return -1;      // 만들지 못했습니다.
		}

		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

		//툴바 생성 코드
		if(!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | 
			CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
		{
			TRACE0("도구 모음을 만들지 못했습니다.\n");
			return -1;
		}	

		m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);		//프레임 윈도우와 결합 할 수 있는 상태
		EnableDocking(CBRS_ALIGN_ANY);					//자식 컨트롤바가 자신에게 결합되도록 허용하고자 호출
		DockControlBar(&m_wndToolBar);					//도구모음이 프레임 윈도우에 붙음
		

		return 0;
	}

	BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
	{
		if( !CFrameWnd::PreCreateWindow(cs) )
			return FALSE;
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
		cs.lpszClass = AfxRegisterWndClass(0);
		return TRUE;
	}

	// CMainFrame 진단

#ifdef _DEBUG
	void CMainFrame::AssertValid() const
	{
		CFrameWnd::AssertValid();
	}

	void CMainFrame::Dump(CDumpContext& dc) const
	{
		CFrameWnd::Dump(dc);
	}
#endif //_DEBUG


	// CMainFrame 메시지 처리기

	void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
	{
		// 뷰 창으로 포커스를 이동합니다.
		m_wndView.SetFocus();
	}

	BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
	{
		// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
		if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;

		// 그렇지 않으면 기본 처리합니다.
		return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}


	//상태바 갱신 핸들러 정의
	void CMainFrame::OnUpdatePos(CCmdUI* pCmdUI)
	{
		pCmdUI->Enable();		//CCmdUI::Enable() 함수 호출
	}
