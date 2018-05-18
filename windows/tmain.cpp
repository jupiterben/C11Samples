#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
      
#define WND_CLASS_NAME TEXT("Scratch")
      
HINSTANCE g_hinst;      
HWND g_hwndTT;
LPCTSTR g_szTooltipMsg = TEXT("Hello World!");

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpcs)
{
BOOL ret = FALSE;

// Create the tooltip window
g_hwndTT = CreateWindow
  (
  TOOLTIPS_CLASS,
  NULL,
  TTS_NOPREFIX,
  CW_USEDEFAULT, CW_USEDEFAULT,
  CW_USEDEFAULT, CW_USEDEFAULT,
  hwnd,
  NULL,
  g_hinst,
  NULL
  );
if (g_hwndTT != NULL)
{
  // Tell the tooltip to register itself using the entire scratch
  // window’s client area as the active region.
  TOOLINFO ti = { sizeof(ti) };
  ti.uFlags = TTF_SUBCLASS;
  ti.hwnd = hwnd;
  ti.hinst = g_hinst;
  ti.uId = 0;
  ti.lpszText = TEXT("Hello world!");
  if (GetClientRect(hwnd, &ti.rect))
  {
      if (SendMessage(g_hwndTT, TTM_ADDTOOL, 0, (LPARAM)&ti))
      {
          ret = TRUE;
      }
  }
}

// If there were any failures, clean up the allocated objects
if (!ret)
{
  if (g_hwndTT)
      DestroyWindow(g_hwndTT);
}

return ret;
}
 
void OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}
      
void DrawToolTipContent(HDC hdc, RECT* prc)
{
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, prc->left, prc->top, g_szTooltipMsg,
		lstrlen(g_szTooltipMsg));
}

LRESULT OnToolTipCustomDraw(NMTTCUSTOMDRAW* pcd)
{
    switch (pcd->nmcd.dwDrawStage)
    {
    case CDDS_PREPAINT:
        {
            // Set the text and back colors of default text so it
            // becomes invisible
            COLORREF clrBg = (COLORREF) SendMessage(g_hwndTT,
                                                    TTM_GETTIPBKCOLOR,
                                                    0, 0);
            SetTextColor(pcd->nmcd.hdc, clrBg);
            SetBkColor(pcd->nmcd.hdc, clrBg);
            return CDRF_NOTIFYPOSTPAINT;
        }
    case CDDS_POSTPAINT:
        {
            DrawToolTipContent(pcd->nmcd.hdc, &pcd->nmcd.rc);
            return CDRF_SKIPDEFAULT;
        }
    }
      
    return CDRF_DODEFAULT;
}


// Determine the required size of the client area of the tooltip
BOOL GetToolTipContentSize(SIZE* psz)
{
BOOL ret = FALSE;

HDC hdc = GetDC(g_hwndTT);
if (hdc != NULL)
{
  HFONT hfontTT = (HFONT) SendMessage(g_hwndTT, WM_GETFONT, 0, 0);
  HFONT hfontTTOld = (HFONT) SelectObject(hdc, hfontTT);
  if (hfontTTOld != NULL)
  {
      SIZE szText;
      if (GetTextExtentPoint32(hdc, g_szTooltipMsg,
                               lstrlen(g_szTooltipMsg), &szText))
      {
          psz->cx = szText.cx;
          psz->cy = szText.cy;
          ret = TRUE;
      }

      SelectObject(hdc, hfontTTOld);
  }

  ReleaseDC(g_hwndTT, hdc);
}

return ret;
}

// Determine the required client rectangle of the tooltip to fit the
// text
BOOL GetToolTipContentRect(RECT* prc)
{
BOOL ret = FALSE;

SIZE sz;
if (GetToolTipContentSize(&sz))
{
  if (GetWindowRect(g_hwndTT, prc))
  {
      prc->right = prc->left + sz.cx;
      prc->bottom = prc->top + sz.cy;
      ret = TRUE;
  }
}

return ret;
}

// When the tooltip is being shown, size it to fit the content
LRESULT OnToolTipShow(NMHDR* pnm)
{
LRESULT ret = 0;
RECT rc;

if (GetToolTipContentRect(&rc))
{
  // Adjust the rectangle to be the proper size to contain the
  // content
  if (SendMessage(g_hwndTT, TTM_ADJUSTRECT, TRUE, (LPARAM) &rc))
  {
      // Resize and move the tooltip accordingly
      if (SetWindowPos(g_hwndTT, NULL, rc.left, rc.top,
                       rc.right - rc.left, rc.bottom - rc.top,
                       SWP_NOZORDER | SWP_NOACTIVATE))
      {
          ret = TRUE;
      }
  }
}

return ret;
}

LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR* pnm)
{
if (pnm->hwndFrom == g_hwndTT)
{
  switch (pnm->code)
  {
  case TTN_SHOW:
      return OnToolTipShow(pnm);
  case NM_CUSTOMDRAW:
      return OnToolTipCustomDraw((NMTTCUSTOMDRAW*) pnm);
  }
}

return 0;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam,
	LPARAM lParam)
{
	switch (uiMsg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_NOTIFY, OnNotify);
	}

	return DefWindowProc(hwnd, uiMsg, wParam, lParam);
}

BOOL RegisterWindowClass()
{
	WNDCLASS wc;
	ATOM atom;

	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hinst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WND_CLASS_NAME;

	atom = RegisterClass(&wc);
	return (atom != 0);
}

int WINAPI _tWinMain(HINSTANCE hinst, HINSTANCE hinstPrev,
                     LPTSTR lpCmdLine, int nCmdShow)
{
    INITCOMMONCONTROLSEX icc;
    int ret = EXIT_FAILURE;
      
    g_hinst = hinst;
      
    // We will need the tooltip common control
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES;
    if (InitCommonControlsEx(&icc))
    {
        if (RegisterWindowClass())
        {
            HWND hwnd = CreateWindow
                (
                WND_CLASS_NAME,
                TEXT("Scratch"),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT,
                CW_USEDEFAULT, CW_USEDEFAULT,
                NULL,
                NULL,
                hinst,
                0
                );
            if (hwnd != NULL)
            {
                MSG msg;
      
                (void) ShowWindow(hwnd, nCmdShow);
                while (GetMessage(&msg, NULL, 0, 0)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
      
                ret = EXIT_SUCCESS;
            }
        }
    }
      
    return ret;
}