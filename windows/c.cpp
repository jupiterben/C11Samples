/**
*
* TipListCtrl.cpp *-Implementation of the class CTipListCtrl.
* Origin:     Shine Kumar's CListCtrlEx.cpp
* @author:     Zhang Xieshen
* @version:    1.00    Date: 08/15/2007
*/
 
 
// TipListCtrl.cpp : implementation file
//
 
#include "stdafx.h"
#include "Test1.h"
#include "TipListCtrl.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CTipListCtrl
 
 
/*  *************************************************************************** */
/** 
@fn:CTipListCtrl
@brief:Constructor    
@param      Nil
@return:void
@pre:Nil
@todo:Nil
@warning:Nil
@author:Zhang Xieshen
@version:1.0
@date:15-08-2005
*/
/*  *************************************************************************** */
CTipListCtrl::CTipListCtrl()
{
 
 
}
 
 
/*  *************************************************************************** */
/** 
@fn:~CTipListCtrl
@brief:Destructor    
@param      Nil
@return:void
@pre:Nil
@todo:Nil
@warning:Nil
@author:Zhang Xieshen
@version:1.0
@date:15-08-2007
*/
/*  *************************************************************************** */
CTipListCtrl::~CTipListCtrl()
{
 
 
}
 
 
BEGIN_MESSAGE_MAP(CTipListCtrl, CListCtrl)
//{
{
AFX_MSG_MAP(CTipListCtrl)
// NOTE - the ClassWizard will add and remove mapping macros here.
ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
//
}
}AFX_MSG_MAP
END_MESSAGE_MAP()
 
/////////////////////////////////////////////////////////////////////////////
// CTipListCtrl message handlers
 
 
/*  *************************************************************************** */
/** 
@fn:OnToolTipText
@brief:Display the tooltip text whel mouse over on a cell. Modify this
            function to change the text displayed in the Tool Tip. Refer to Shine
Kumar's work in 2005.
@param:UINT id
@param:NMHDR* pNMHDR
@param:LRESULT* pResult
@return:BOOL
@pre:Nil
@todo:Nil
@warning:Nil
@author:Zhang Xieshen
@version:1.0
@date:15-08-2007
*/
/*  *************************************************************************** */
BOOL CTipListCtrl::OnToolTipText(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
 
// Need to handle both ANSI and UNICODE versions of the message
TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
CString strTipText;
UINT nID = (UINT)pNMHDR->idFrom;
 
if (0 == nID)  // Notification in NT from automatically
    {
 
        return FALSE;   // created tooltip
     
}
int row = ((nID-1) >> 10) & 0x3fffff ;
int col = (nID-1) & 0x3ff;
 
// Use Item's name as the tool tip. Change this for something different.
// Like use its file size, etc.
strTipText = GetItemText(row, col);
 
#ifndef _UNICODE
 
if (pNMHDR->code == TTN_NEEDTEXTA)
    {
 
lstrcpyn(pTTTA->szText, strTipText, 80);
     
}
else
    {
 
_mbstowcsz(pTTTW->szText, strTipText, 80);
     
}
#else
if (pNMHDR->code == TTN_NEEDTEXTA)
    {
 
_wcstombsz(pTTTA->szText, strTipText, 80);
     
}
else
    {
 
lstrcpyn(pTTTW->szText, strTipText, 80);
     
}
#endif
*pResult = 0;
 
return TRUE;    // message was handled
 
}
 
 
/*  *************************************************************************** */
/** 
@fn:OnToolHitTest
@brief:
@param:CPoint& point
                Point to be tested.
@param:     RECT* cellrect
                To hold the bounding rect
@param:     int* col
                To hold the column index
@return:int
                Row index on success, -1 otherwise
@pre:Nil
@todo:Nil
@warning:Nil
@author:Zhang Xieshen
@version:1.0
@date:15-08-2007
*/
/*  *************************************************************************** */
int CTipListCtrl::OnToolHitTest(CPoint point, TOOLINFO *pTI) const
{
 
int row, col;
RECT cellrect;
row = CellRectFromPoint(point, &cellrect, &col );
 
if ( row == -1 ) 
{
 
return -1;
 
}
 
pTI->hwnd = m_hWnd;
pTI->uId = (UINT)((row<<10)+(col&0x3ff)+1);
pTI->lpszText = LPSTR_TEXTCALLBACK;
 
pTI->rect = cellrect;
 
return (int)pTI->uId;
 
}
 
 
/*  *************************************************************************** */
/** 
@fn:CellRectFromPoint
@brief:Determine the row, col and bounding rect of a cell
@param:CPoint& point
                Point to be tested.
@param:     RECT* cellrect
                To hold the bounding rect
@param:     int* col
                To hold the column index
@return:int
                Row index on success, -1 otherwise
@pre:Nil
@todo:Nil
@warning:Nil
@author:Zhang Xieshen
@version:1.0
@date:15-08-2007
*/
/*  *************************************************************************** */
int CTipListCtrl::CellRectFromPoint(CPoint &point, RECT *cellrect, int *col) const
{
 
int colnum;
int nColumnCount;
CHeaderCtrl* pHeader;
 
// If not REPORT style for the list, then use 1 column
// Otherwise, find the column in the report style view.
if (LVS_REPORT != (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK))
{
 
// Window is not Report style, so no headers. Deal with it!
nColumnCount = 1;
 
}
else
{
 
// Get the number of columns in Report style.
pHeader = (CHeaderCtrl*)GetDlgItem(0);
nColumnCount = pHeader->GetItemCount();
 
}
 
// Get the top and bottom row visible
int row = GetTopIndex();
int bottom = row + GetCountPerPage();
if (bottom > GetItemCount())
    {
 
bottom = GetItemCount();
     
}
 
// Loop through the visible rows
for (;row <= bottom; ++row)
{
 
// Get bounding rect of item and check whether point falls in it.
CRect rect, rectLabel;
if (LVS_REPORT != (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK))
{
 
// If not Report style, get label / icon boundaries.
GetItemRect(row, &rect, LVIR_ICON);
GetItemRect(row, &rectLabel, LVIR_LABEL);
 
}
else
{
 
// If Report style, get bounds of cell.
GetItemRect(row, &rect, LVIR_BOUNDS);
 
}
 
if (rect.PtInRect(point) ||
rectLabel.PtInRect(point))
{
 
bool InLabel = false;
 
// Store which part user clicked on if in ICON view,
// clicked the Label or the Icon?
if (rect.PtInRect(point))
{
 
InLabel = false;
 
}
else if (rectLabel.PtInRect(point))
{
 
InLabel = true;
 
}
 
// Now find the column
for (colnum = 0; colnum < nColumnCount; ++colnum)
{
 
// Getting column width
int colwidth;
if (LVS_REPORT != (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK))
{
 
colwidth = 100000; // don't count colwidth.
 
}
else
{
 
// If REPORT, check inside column width.
colwidth = GetColumnWidth(colnum);
 
}
 
if ((point.x >= rect.left 
&& point.x <= (rect.left + colwidth)) ||
(point.x >= rectLabel.left
&& point.x <= (rectLabel.left + colwidth)))
{
 
RECT rectClient;
GetClientRect(&rectClient);
if(NULL != col)
                    {
 
                        *col = colnum;
                     
}
rect.right = rect.left + colwidth;
rectLabel.right = rectLabel.left + colwidth;
 
// Make sure that the right extent does not exceed
// the client area
if (rect.right > rectClient.right) 
                    {
 
rect.right = rectClient.right;
                     
}
if (rectLabel.right > rectClient.right)
                    {
 
rectLabel.right = rectClient.right;
                     
}
if (!InLabel)
{
 
*cellrect = rect;
 
}
else
{
 
*cellrect = rectLabel;
 
}
return row;
 
}
rect.left += colwidth;
rectLabel.left += colwidth;
 
}
 
}
 
}
 
return -1;
 
}