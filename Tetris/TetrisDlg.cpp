
// TetrisDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTetrisDlg �Ի���



CTetrisDlg::CTetrisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTetrisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()


// CTetrisDlg ��Ϣ�������

BOOL CTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetGameRuler();
	SetTimer(BlockMoveTimerID,delta,NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTetrisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTetrisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		{
			//Draw
			CPaintDC dc(this);

			CRect rectWnd;
			GetWindowRect(&rectWnd);
			int nWidth = rectWnd.Width();
			int nHeight= rectWnd.Height();

			CDC MemDC;
			CBitmap MemBitmap;
			MemDC.CreateCompatibleDC (&dc);
			MemBitmap.CreateCompatibleBitmap(&dc,nWidth,nHeight);

			CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
			MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

			POINT point[2];

			point[0].x = OffsizeX;
			point[0].y = OffsizeY;
			point[1].x = OffsizeX;
			point[1].y = OffsizeY + GridHeight * (MapHeight );
			MemDC.Polyline(point, 2);

			point[0].x = OffsizeX + GridWidth * (MapWidth );
			point[0].y = OffsizeY;
			point[1].x = OffsizeX + GridWidth * (MapWidth );
			point[1].y = OffsizeY + GridHeight * (MapHeight );
			MemDC.Polyline(point, 2);

			//for(int i = 0; i < MapWidth; ++i)
			//{
			//	dc.Polyline(point, 2);
			//	point[0].x = point[0].x + GridWidth;
			//	point[1].x = point[1].x + GridWidth;
			//}

			point[0].x = OffsizeX;
			point[0].y = OffsizeY;
			point[1].x = OffsizeX + GridWidth * (MapWidth );
			point[1].y = OffsizeY;
			MemDC.Polyline(point, 2);

			point[0].x = OffsizeX;
			point[0].y = OffsizeY + GridHeight * (MapHeight );
			point[1].x = OffsizeX + GridWidth * (MapWidth );
			point[1].y = OffsizeY + GridHeight * (MapHeight );
			MemDC.Polyline(point, 2);

			//for(int i = 0; i < MapHeight; ++i)
			//{
			//	dc.Polyline(point, 2);

			//	point[0].y += GridHeight;
			//	point[1].y += GridHeight;
			//}

			//Draw Chessboard
			RECT rect;
			Chessboard& cb=GetChessboard();

			for(int x = 0; x < MapWidth; x = x + 1)
			{
				for(int y = 0; y < MapHeight; y = y + 1)
				{
					if(cb.GetIdOfPoint(ChessPoint(x,y)) == GridSnake)
					{
						MemDC.SelectStockObject(BLACK_BRUSH);

						rect.left = OffsizeX + x * GridWidth+1;
						rect.top = OffsizeY + y * GridHeight+1;
						rect.right = rect.left + GridWidth-1;
						rect.bottom = rect.top + GridHeight-1;

						MemDC.Rectangle(&rect);
					}
					else if(cb.GetIdOfPoint(ChessPoint(x,y)) == GridFood)
					{
						MemDC.SelectStockObject(WHITE_BRUSH);

						rect.left = OffsizeX + x * GridWidth+1;
						rect.top = OffsizeY + y * GridHeight+1;
						rect.right = rect.left + GridWidth-1;
						rect.bottom = rect.top + GridHeight-1;

						MemDC.Rectangle(&rect);
					}
				}
			}

			//Draw Block
			for(auto i=GetBlock().begin();i!=GetBlock().end();i++)
			{
				MemDC.SelectStockObject(WHITE_BRUSH);

				rect.left = OffsizeX + (i->x+GetBlock().GetPosition().x) * GridWidth+1;
				rect.top = OffsizeY + (i->y+GetBlock().GetPosition().y) * GridHeight+1;
				rect.right = rect.left + GridWidth-1;
				rect.bottom = rect.top + GridHeight-1;

				MemDC.Rectangle(&rect);
			}

			//Draw the next Block
			MemDC.TextOutW(OffsizeX*2 +  MapWidth * GridWidth,OffsizeY,L"Next :");
			Block next(GetGameRuler().GetNextShape());
			for(auto i=next.begin();i!=next.end();i++)
			{
				MemDC.SelectStockObject(GRAY_BRUSH);

				rect.left = OffsizeX*2 + (i->x + MapWidth) * GridWidth ;
				rect.top = OffsizeY+OffsizeX + (i->y) * GridHeight+1;
				rect.right = rect.left + GridWidth-1;
				rect.bottom = rect.top + GridHeight-1;

				MemDC.Rectangle(&rect);
			}
			CString score;
			score.Format(L"Score : %d",GetGameRuler().GetLinesKilled());
			MemDC.TextOutW(OffsizeX*2 +  MapWidth * GridWidth,OffsizeY+GridWidth*7,score);


			dc.BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			MemBitmap.DeleteObject();
			MemDC.DeleteDC();
		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CTetrisDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate();
	if (GetGameRuler().Go(CP(Direction::Down))==Result::Lose)
	{
		KillTimer(BlockMoveTimerID);
		MessageBox(L"You Lose");
	}
	Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}


void CTetrisDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case 'W':
		GetGameRuler().Rotate();
		break;
	case 'A':
		GetGameRuler().Go(CP(Direction::Left));
		break;

	case 'D':
		GetGameRuler().Go(CP(Direction::Right));
		break;
	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTetrisDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nChar)
	{
	case 'S':
		while (GetGameRuler().Go(CP(Direction::Down))!=Result::Check);
		//GetGameRuler().Go(CP(Direction::Down));
		break;
	default:
		break;
	}

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}
