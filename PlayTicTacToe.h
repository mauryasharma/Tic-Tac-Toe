#if !defined(AFX_PLAYTICTACTOE_H__B0D958C2_F7AB_11D5_BD6A_444553540000__INCLUDED_)
#define AFX_PLAYTICTACTOE_H__B0D958C2_F7AB_11D5_BD6A_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayTicTacToe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayTicTacToe dialog

#define EX 'X'
#define OH 'O'


struct Square{
	CRect rect;
	bool Selected;
	char Mark;
};


class CPlayTicTacToe : public CDialog
{
	Square Squares[9];
	int CurrPos;
	int Turn;
	CWnd *wnd;
	CDC *pDC;
	bool GameOver;

// Construction
public:
	CPlayTicTacToe(CWnd* pParent = NULL);   // standard constructor
	

	int GameType;
// Dialog Data
	//{{AFX_DATA(CPlayTicTacToe)
	enum { IDD = IDD_PLAY };
	CButton	m_Play;
	UINT	m_Drawn;
	UINT	m_P1Won;
	UINT	m_P2Won;
	CString	m_P1;
	CString	m_P2;
	CString	m_Pd;
	CString	m_Turn;
	//}}AFX_DATA

	void InitSquare();
	bool IsGameOver();
	bool IsSquareMarked(int Sq);
	int InSquare(CPoint point);
	void DrawMark(int Sqno);
	int FindFirstEmpty();
	char GetMark(int Sq);
	char FindWinner();
	bool IWon();
	bool IsGameDrawn();
	bool Player1Won();
	bool Player2Won();
	void PlayMyMove();
	void DisplayGamesStatus();
	void WhoWon();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayTicTacToe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayTicTacToe)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYTICTACTOE_H__B0D958C2_F7AB_11D5_BD6A_444553540000__INCLUDED_)
