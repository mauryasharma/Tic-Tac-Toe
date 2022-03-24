// PlayTicTacToe.cpp : implementation file
//

#include "stdafx.h"
#include "Tic Tac Toe.h"
#include "PlayTicTacToe.h"
#include "wingdi.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayTicTacToe dialog


CPlayTicTacToe::CPlayTicTacToe(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayTicTacToe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayTicTacToe)
	m_Drawn = 0;
	m_P1Won = 0;
	m_P2Won = 0;
	m_P1 = _T("");
	m_P2 = _T("");
	m_Pd = _T("");
	m_Turn = _T("");
	//}}AFX_DATA_INIT
}


void CPlayTicTacToe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayTicTacToe)
	DDX_Control(pDX, IDC_PLAY, m_Play);
	DDX_Text(pDX, IDC_EDITD, m_Drawn);
	DDX_Text(pDX, IDC_EDITP1, m_P1Won);
	DDX_Text(pDX, IDC_EDITP2, m_P2Won);
	DDX_Text(pDX, IDC_P1, m_P1);
	DDX_Text(pDX, IDC_P2, m_P2);
	DDX_Text(pDX, IDC_PD, m_Pd);
	DDX_Text(pDX, IDC_TURN, m_Turn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayTicTacToe, CDialog)
	//{{AFX_MSG_MAP(CPlayTicTacToe)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayTicTacToe message handlers

BOOL CPlayTicTacToe::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayTicTacToe::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_P1Won = m_P2Won = m_Drawn = 0;

	m_P1 = "Player1 Won:";
	
	if (GameType == 1)
		m_P2 = "Computer Won:";
	else
		m_P2 = "Player2 Won:";
	CurrPos = 0;
	UpdateData(FALSE);
	srand((unsigned)time( NULL ));
	Turn = rand()%2;
	Turn++;
	GameOver = FALSE;
	m_Play.EnableWindow(FALSE);

	CRect r;
	CPoint p;

	wnd = dc.GetWindow();
	pDC = wnd->GetDC();
	
	InitSquare();

	COLORREF bg = RGB(255,255,150);
	CBrush myBrush1(bg);
	CRect rect;
	rect.left = Squares[0].rect.left;
	rect.top = Squares[0].rect.top;
	rect.right = Squares[8].rect.right;
	rect.bottom = Squares[8].rect.bottom;
	pDC->FillRect(rect,&myBrush1);
	
	p.x = 180;
	p.y = 150;

	r.left= 10;
	r.top= 10;
	r.right = r.left+p.x;
	r.bottom= r.top+p.y;

	
	COLORREF lines = RGB(100,100,180);

	CPen myPen(PS_SOLID,3,lines);
	
	pDC->SelectObject(&myPen);
	pDC->MoveTo(r.left,r.top+60);
	pDC->LineTo(r.left+180,r.top+60);

	pDC->MoveTo(r.left,r.top+120);
	pDC->LineTo(r.left+180,r.top+120);

	pDC->MoveTo(r.left+60,r.top);
	pDC->LineTo(r.left+60,r.top+180);

	pDC->MoveTo(r.left+120,r.top);
	pDC->LineTo(r.left+120,r.top+180);

	COLORREF bar = RGB(255,50,50);
	CBrush myBrush(bar);
	rect.left = Squares[0].rect.left;
	rect.top = Squares[0].rect.top;
	rect.right = Squares[0].rect.right-5;
	rect.bottom = Squares[0].rect.bottom-5;
	//pDC->FillRect(rect,&myBrush);
	if (Turn == 1)
		PlayMyMove();
}

int CPlayTicTacToe::InSquare(CPoint point)
{
	int i;
	for (i=0;i<=8;i++)
		if (point.x >= Squares[i].rect.left && 
			point.x <= Squares[i].rect.right &&
			point.y >= Squares[i].rect.top &&
			point.y <= Squares[i].rect.bottom)
			return i;
	if (i > 8)
		return -1;
}

bool CPlayTicTacToe::IsSquareMarked(int Sq)
{
	if (Squares[Sq].Selected == TRUE)
		return TRUE;
	else
		return FALSE;
}

char CPlayTicTacToe::GetMark(int Sq){
	return Squares[Sq].Mark;
}

char CPlayTicTacToe::FindWinner()
{
	int WinPattern[8][3] ={
		0,1,2,
		3,4,5,
		6,7,8,
		0,3,6,
		1,4,7,
		2,5,8,
		0,4,8,
		2,4,6
		};

	int i;

	for (i=0;i<8;i++){

		if (GetMark(WinPattern[i][0])== EX &&
			GetMark(WinPattern[i][1])== EX &&
			GetMark(WinPattern[i][2])== EX)

			return EX;

		if (GetMark(WinPattern[i][0])== OH &&
			GetMark(WinPattern[i][1])== OH &&
			GetMark(WinPattern[i][2])== OH)

			return OH;
	}
	return 0;
}


bool CPlayTicTacToe::IsGameDrawn()
{
	int i;
	for (i=0;i<=8;i++){
		if (!IsSquareMarked(i))
			return FALSE;
	}
	m_Drawn++;
	GameOver = TRUE;
	return TRUE;
}

bool CPlayTicTacToe::Player1Won()
{
	if (FindWinner() == EX){
		GameOver = TRUE;
		m_P1Won++;
		return TRUE;
	}
	else{
		GameOver = FALSE;
		return FALSE;
	}
}

bool CPlayTicTacToe::IWon()
{
	if (FindWinner() == OH){
		GameOver = TRUE;
		m_P2Won++;
		return TRUE;
	}
	else{
		GameOver = FALSE;
		return FALSE;
	}
}

void CPlayTicTacToe::WhoWon()
{
	if (Player1Won())
	{
		//Player1 Won
	}
	if (IWon())
	{
		//Computer Won
	}
	if (IsGameDrawn())
	{
		//Game Drawn
	}	
}

void CPlayTicTacToe::PlayMyMove()
{

	int i;
	//Attemp to win the game
	if (!IsSquareMarked(0) && GetMark(1) == OH && GetMark(2) == OH ||
		!IsSquareMarked(0) && GetMark(3) == OH && GetMark(6) == OH ||
		!IsSquareMarked(0) && GetMark(4) == OH && GetMark(8) == OH){

		//DrawBar(0, WHITE);
		//CurrPos = DrawMark(0, OH);
		DrawMark(0);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(1) && GetMark(0) == OH && GetMark(2) == OH ||
		!IsSquareMarked(1) && GetMark(4) == OH && GetMark(7) == OH){

		//DrawBar(1, WHITE);
		//CurrPos = DrawMark(1, OH);
		DrawMark(1);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(2) && GetMark(0) == OH && GetMark(1) == OH ||
		!IsSquareMarked(2) && GetMark(5) == OH && GetMark(8) == OH ||
		!IsSquareMarked(2) && GetMark(4) == OH && GetMark(6) == OH){

		//DrawBar(2, WHITE);
		//CurrPos = DrawMark(2, OH);
		DrawMark(2);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(3) && GetMark(4) == OH && GetMark(5) == OH ||
		!IsSquareMarked(3) && GetMark(0) == OH && GetMark(6) == OH){

		//DrawBar(3, WHITE);
		//CurrPos = DrawMark(3, OH);
		DrawMark(3);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(4) && GetMark(3) == OH && GetMark(5) == OH ||
		!IsSquareMarked(4) && GetMark(1) == OH && GetMark(7) == OH ||
		!IsSquareMarked(4) && GetMark(0) == OH && GetMark(8) == OH){

		//DrawBar(4, WHITE);
		//CurrPos = DrawMark(4, OH);
		DrawMark(4);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(5) && GetMark(3) == OH && GetMark(4) == OH ||
		!IsSquareMarked(5) && GetMark(2) == OH && GetMark(8) == OH){

		//DrawBar(5, WHITE);
		//CurrPos = DrawMark(5, OH);
		DrawMark(5);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(6) && GetMark(7) == OH && GetMark(8) == OH ||
		!IsSquareMarked(6) && GetMark(0) == OH && GetMark(3) == OH ||
		!IsSquareMarked(6) && GetMark(4) == OH && GetMark(2) == OH){

		//DrawBar(6, WHITE);
		//CurrPos = DrawMark(6, OH);
		DrawMark(6);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(7) && GetMark(6) == OH && GetMark(8) == OH ||
		!IsSquareMarked(7) && GetMark(1) == OH && GetMark(4) == OH){

		//DrawBar(7, WHITE);
		//CurrPos = DrawMark(7, OH);
		DrawMark(7);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(8) && GetMark(6) == OH && GetMark(7) == OH ||
		!IsSquareMarked(8) && GetMark(2) == OH && GetMark(5) == OH ||
		!IsSquareMarked(8) && GetMark(0) == OH && GetMark(4) == OH){

		//DrawBar(8, WHITE);
		//CurrPos = DrawMark(8, OH);
		DrawMark(8);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	//Attempt not to loose
	if (!IsSquareMarked(0) && GetMark(1) == EX && GetMark(2) == EX ||
		!IsSquareMarked(0) && GetMark(3) == EX && GetMark(6) == EX ||
		!IsSquareMarked(0) && GetMark(4) == EX && GetMark(8) == EX){

		//DrawBar(0, WHITE);
		//CurrPos = DrawMark(0, OH);
		DrawMark(9);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(1) && GetMark(0) == EX && GetMark(2) == EX ||
		!IsSquareMarked(1) && GetMark(4) == EX && GetMark(7) == EX){

		//DrawBar(1, WHITE);
		//CurrPos = DrawMark(1, OH);
		DrawMark(1);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(2) && GetMark(0) == EX && GetMark(1) == EX ||
		!IsSquareMarked(2) && GetMark(5) == EX && GetMark(8) == EX ||
		!IsSquareMarked(2) && GetMark(4) == EX && GetMark(6) == EX){

		//DrawBar(2, WHITE);
		//CurrPos = DrawMark(2, OH);
		DrawMark(2);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(3) && GetMark(4) == EX && GetMark(5) == EX ||
		!IsSquareMarked(3) && GetMark(0) == EX && GetMark(6) == EX){

		//DrawBar(3, WHITE);
		//CurrPos = DrawMark(3, OH);
		DrawMark(3);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(4) && GetMark(3) == EX && GetMark(5) == EX ||
		!IsSquareMarked(4) && GetMark(1) == EX && GetMark(7) == EX ||
		!IsSquareMarked(4) && GetMark(0) == EX && GetMark(8) == EX){

		//DrawBar(4, WHITE);
		//CurrPos = DrawMark(4, OH);
		DrawMark(4);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(5) && GetMark(3) == EX && GetMark(4) == EX ||
		!IsSquareMarked(5) && GetMark(2) == EX && GetMark(8) == EX){

		//DrawBar(5, WHITE);
		//CurrPos = DrawMark(5, OH);
		DrawMark(5);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(6) && GetMark(7) == EX && GetMark(8) == EX ||
		!IsSquareMarked(6) && GetMark(0) == EX && GetMark(3) == EX ||
		!IsSquareMarked(6) && GetMark(4) == EX && GetMark(2) == EX){

		//DrawBar(6, WHITE);
		//CurrPos = DrawMark(6, OH);
		DrawMark(6);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(7) && GetMark(6) == EX && GetMark(8) == EX ||
		!IsSquareMarked(7) && GetMark(1) == EX && GetMark(4) == EX){

		//DrawBar(7, WHITE);
		//CurrPos = DrawMark(7, OH);
		DrawMark(7);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(8) && GetMark(6) == EX && GetMark(7) == EX ||
		!IsSquareMarked(8) && GetMark(2) == EX && GetMark(5) == EX ||
		!IsSquareMarked(8) && GetMark(0) == EX && GetMark(4) == EX){

		//DrawBar(8, WHITE);
		//CurrPos = DrawMark(8, OH);
		DrawMark(8);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}


	//Occupy center
	if (!IsSquareMarked(4)){
		//DrawBar(4, WHITE);
		//CurrPos = DrawMark(4, OH);
		DrawMark(4);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	//Occupy available corner
	if (!IsSquareMarked(0)){
		//DrawBar(0, WHITE);
		//CurrPos = DrawMark(0, OH);
		DrawMark(0);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(2)){
		//DrawBar(2, WHITE);
		//CurrPos = DrawMark(2, OH);
		DrawMark(2);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(6)){
		//DrawBar(6, WHITE);
		//CurrPos = DrawMark(6, OH);
		DrawMark(6);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	if (!IsSquareMarked(8)){
		//DrawBar(8, WHITE);
		//CurrPos = DrawMark(8, OH);
		DrawMark(8);
		if (CurrPos>=0)
			//DrawBar(CurrPos, RED);
			;
		return;
	}

	//Occupy empty slot
	for (i=0;i<=8;i++){
		if (!IsSquareMarked(i)){
			//DrawBar(i, WHITE);
			//CurrPos = DrawMark(i, OH);
			DrawMark(i);
			if (CurrPos>=0)
				//DrawBar(CurrPos, RED);
				;
			return;
		}
	}
}

void CPlayTicTacToe::DrawMark(int Sqno)
{
	COLORREF ln = RGB(100,100,180);

	CPen myPen(PS_SOLID,3,ln);

	COLORREF bg = RGB(255,255,150);
	CBrush myBrush(bg);
	pDC->SelectObject(&myBrush);
	
	pDC->SelectObject(&myPen);
	
	if (!Squares[Sqno].Selected && !GameOver)
	{
		Squares[Sqno].Selected = TRUE;
		if (Turn == 1) //Draw 'X'
		{	
			Turn = 2;
			pDC->MoveTo(Squares[Sqno].rect.left+5,Squares[Sqno].rect.top+5);
			pDC->LineTo(Squares[Sqno].rect.right-5,Squares[Sqno].rect.bottom-5);
	
			pDC->MoveTo(Squares[Sqno].rect.right-5,Squares[Sqno].rect.top+5);
			pDC->LineTo(Squares[Sqno].rect.left+5,Squares[Sqno].rect.bottom-5);
			
			//dc.MoveTo(Squares[Sqno].rect.left+5,Squares[Sqno].rect.top+5);
			//dc.LineTo(Squares[Sqno].rect.right-5,Squares[Sqno].rect.bottom-5);
	
			//dc.MoveTo(Squares[Sqno].rect.right-5,Squares[Sqno].rect.top+5);
			//dc.LineTo(Squares[Sqno].rect.left+5,Squares[Sqno].rect.bottom-5);
			Squares[Sqno].Mark = EX;
		}
		else//Draw 'O'
		{
			Turn = 1;
			CRect rect;
			rect.left = Squares[Sqno].rect.left+5;
			rect.top = Squares[Sqno].rect.top+5;
			rect.right = Squares[Sqno].rect.right-5;
			rect.bottom  = Squares[Sqno].rect.bottom-5;
			pDC->Ellipse(rect);			
			Squares[Sqno].Mark = OH;
		}
		WhoWon();
	}	
}
void CPlayTicTacToe::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	int Square;
	Square = InSquare(point);
	if (Turn == 2 && Square>=0 && Square<=8 && !IsSquareMarked(Square))
	{
		DrawMark(Square);
		WhoWon();
		
	}
	if (!GameOver)
	{
		if (GameType == 1)
			PlayMyMove();
		WhoWon();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CPlayTicTacToe::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CPlayTicTacToe::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CPlayTicTacToe::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CPlayTicTacToe::OnPlay() 
{
	// TODO: Add your control notification handler code here
	OnPaint();
}

void CPlayTicTacToe::InitSquare(){
	/*Left Top Square*/

	CRect r;

	int w,h;
	//r.left= (Maxx-180)/2;
	//r.top= (Maxy-150)/2;
	
	r.left = 10;
	r.top = 10;	
	r.right = r.left+180;
	r.bottom = r.top+150;

	w = 60,
	h = 60;

	/*Left top square*/
	Squares[0].rect.left = r.left;
	Squares[0].rect.top = r.top;
	Squares[0].rect.right = r.left+w;
	Squares[0].rect.bottom = r.top+h;
	Squares[0].Selected= FALSE;
	Squares[0].Mark = 0;
	/*Middle Top Square*/
	Squares[1].rect.left = r.left+w;
	Squares[1].rect.top = r.top;
	Squares[1].rect.right = r.left+w*2;
	Squares[1].rect.bottom = r.top+h;
	Squares[1].Selected= FALSE;
	Squares[1].Mark = 0;
	/*Right Top Square*/
	Squares[2].rect.left = r.left+w*2;
	Squares[2].rect.top = r.top;
	Squares[2].rect.right = r.left+w*3;
	Squares[2].rect.bottom = r.top+h;
	Squares[2].Selected= FALSE;
	Squares[2].Mark = 0;

	/*Left Middle Square*/
	Squares[3].rect.left = r.left;
	Squares[3].rect.top = r.top+h;
	Squares[3].rect.right = r.left+w;;
	Squares[3].rect.bottom = r.top+h*2;
	Squares[3].Selected= FALSE;
	Squares[3].Mark = 0;
	/*Middle Middle Square*/
	Squares[4].rect.left = r.left+w;
	Squares[4].rect.top = r.top+h;
	Squares[4].rect.right = r.left+w*2;
	Squares[4].rect.bottom = r.top+h*2;
	Squares[4].Selected= FALSE;
	Squares[4].Mark = 0;
	/*Right Middle Square*/
	Squares[5].rect.left = r.left+w*2;
	Squares[5].rect.top = r.top+h;
	Squares[5].rect.right = r.left+w*3;
	Squares[5].rect.bottom = r.top+h*2;;
	Squares[5].Selected= FALSE;
	Squares[5].Mark = 0;

	/*Left Bottom Square*/
	Squares[6].rect.left = r.left;
	Squares[6].rect.top = r.top+h*2;
	Squares[6].rect.right = r.left+w;
	Squares[6].rect.bottom = r.top+h*3;
	Squares[6].Selected= FALSE;
	Squares[6].Mark = 0;
	/*Middle Bottom Square*/
	Squares[7].rect.left = r.left+w;
	Squares[7].rect.top = r.top+h*2;
	Squares[7].rect.right = r.left+w*2;
	Squares[7].rect.bottom = r.top+h*3;
	Squares[7].Selected= FALSE;
	Squares[7].Mark = 0;
	/*Right Bottom Square*/
	Squares[8].rect.left = r.left+w*2;
	Squares[8].rect.top = r.top+h*2;
	Squares[8].rect.right = r.left+w*3;
	Squares[8].rect.bottom = r.top+h*3;
	Squares[8].Selected= FALSE;
	Squares[8].Mark = 0;
}
