// Tic Tac Toe.h : main header file for the TIC TAC TOE application
//

#if !defined(AFX_TICTACTOE_H__BE17EF12_DAAB_11D5_BD69_444553540000__INCLUDED_)
#define AFX_TICTACTOE_H__BE17EF12_DAAB_11D5_BD69_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTicTacToeApp:
// See Tic Tac Toe.cpp for the implementation of this class
//

class CTicTacToeApp : public CWinApp
{
public:
	CTicTacToeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTicTacToeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTicTacToeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TICTACTOE_H__BE17EF12_DAAB_11D5_BD69_444553540000__INCLUDED_)
