/*  *************************************************************************** */
/**
@file:TipListCtrl.h
@brief:This file will define the class CTipListCtrl.
Origin:Shine Kumar's CListCtrlEx.h
@author:Zhang Xieshen
@date:15-08-2007
@todo:  Nil
*/
/*  *************************************************************************** */
 
 
#if !defined(AFX_TIPLISTCTRL_H__2F4CB81A_24EB_48E2_BA4D_1568A7702A0B__INCLUDED_)
#define AFX_TIPLISTCTRL_H__2F4CB81A_24EB_48E2_BA4D_1568A7702A0B__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipListCtrl.h : header file
//
 
 
/*  *************************************************************************** */
/** 
@class:CTipListCtrl
@brief:This class is derived from CListCtrl. The purpose of this class is
            to create a list control with ToolTips.
@author:Zhang Xieshen
@pre:   Nil
@todo:Nil
@warning:Nil
@version:1.0
@date:15-08-2007
*/
/*  **************************************************************************** */
 
 
/////////////////////////////////////////////////////////////////////////////
// CTipListCtrl window
 
class CTipListCtrl : public CListCtrl
{
 
// Construction
public:
CTipListCtrl();
 
// Attributes
public:
 
// Operations
public:
 
// Overrides
// ClassWizard generated virtual function overrides
//{
{
AFX_VIRTUAL(CTipListCtrl)
//
}
}AFX_VIRTUAL
 
// Implementation
public:
virtual ~CTipListCtrl();
 
// Generated message map functions
protected:
//{
{
AFX_MSG(CTipListCtrl)
// NOTE - the ClassWizard will add and remove member functions here.
//
}
}AFX_MSG
 
private:
int CellRectFromPoint(CPoint& point, RECT* cellrect, int* col) const;
int OnToolHitTest(CPoint point, TOOLINFO * pTI) const;
afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
 
DECLARE_MESSAGE_MAP()
 
};
 
/////////////////////////////////////////////////////////////////////////////
 
//{
{
AFX_INSERT_LOCATION
}
}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
 
#endif // !defined(AFX_TIPLISTCTRL_H__2F4CB81A_24EB_48E2_BA4D_1568A7702A0B__INCLUDED_)