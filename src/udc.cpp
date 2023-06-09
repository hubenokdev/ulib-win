/*
 * =====================================================================================
 *
 *       Filename:  udc.cpp
 *
 *    Description:  implement UDevContext
 *
 *        Version:  1.0
 *        Created:  2009-8-23 4:48:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  huys (hys), huys03@gmail.com
 *        Company:  hu
 *
 * =====================================================================================
 */

#define _WIN32_WINNT 0x0500
#define WINVER 0x0500

#include <windows.h>
#include <tchar.h>

#include <cassert>

#include "udc.h"

UDevContext::UDevContext()
: UGDIObject(),
  m_hOldBrush(NULL),
  m_hOldPen(NULL)
{}

UDevContext::~UDevContext()
{}

bool UDevContext::attach(HDC hdc)
{
    assert(NULL == m_hObj);
    m_hObj = hdc;
    return true;
}

bool UDevContext::dettach()
{
    assert(NULL != m_hObj);
    m_hObj = NULL;
    return true;
}

bool UDevContext::getDC( HWND hWnd )
{
    return NULL != (m_hObj = ::GetDC(hWnd));
}

int UDevContext::saveDC()
{
    return ::SaveDC((HDC)m_hObj);
}

BOOL UDevContext::restoreDC(int nSaveDC)
{
    return ::RestoreDC((HDC)m_hObj, nSaveDC);
}

huys::Color UDevContext::setPenColor(huys::Color clr)
{
    //    Select DC_PEN so you can change the color of the pen with
    //    COLORREF SetDCPenColor(HDC hdc, COLORREF color)
    ::SelectObject((HDC)m_hObj, ::GetStockObject(DC_PEN));
    return ::SetDCPenColor((HDC)m_hObj, clr);
}

huys::Color UDevContext::setBrushColor(huys::Color clr)
{
    //    Select DC_BRUSH so you can change the brush color from the
    //    default WHITE_BRUSH to any other color
    ::SelectObject((HDC)m_hObj, ::GetStockObject(DC_BRUSH));
    return ::SetDCBrushColor((HDC)m_hObj, clr);
}

huys::Color UDevContext::getPenColor()
{
#ifdef _MSC_VER
    return ::GetDCPenColor((HDC)m_hObj);
#else
    return 0;
#endif
}

huys::Color UDevContext::getBrushColor()
{
#ifdef _MSC_VER
    return ::GetDCBrushColor((HDC)m_hObj);
#else
    return 0;
#endif
}

HGDIOBJ UDevContext::getCurObj(UINT uObjectType)
{
    return ::GetCurrentObject((HDC)m_hObj, uObjectType);
}

HANDLE UDevContext::selectObj(HANDLE hObj)
{
    return ::SelectObject((HDC)m_hObj, hObj);
}

int UDevContext::setStretchBltMode( int iStretchMode )
{
    return ::SetStretchBltMode(*this, iStretchMode);
}

BOOL UDevContext::stretchBlt( int nXOriginDest,
                              int nYOriginDest,
                              int nWidthDest,
                              int nHeightDest,
                              HDC hdcSrc,
                              int nXOriginSrc,
                              int nYOriginSrc,
                              int nWidthSrc,
                              int nHeightSrc,
                              DWORD dwRop )
{
    return ::StretchBlt(*this, nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest, hdcSrc,
        nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop );
}

BOOL UDevContext::bitBlt( int nXOriginDest,
                             int nYOriginDest,
                             int nWidthDest,
                             int nHeightDest,
                             HDC hdcSrc,
                             int nXOriginSrc,
                             int nYOriginSrc,
                             DWORD dwRop )
{
    return ::BitBlt(*this, nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest, hdcSrc,
        nXOriginSrc, nYOriginSrc, dwRop );
}

BOOL UDevContext::bitBlt(LPRECT lpRect, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, DWORD dwRop)
{
    return this->bitBlt(lpRect->left, lpRect->top,
                        lpRect->right - lpRect->left,
                        lpRect->bottom - lpRect->top,
                        hdcSrc, nXOriginSrc, nYOriginSrc, dwRop);
}

BOOL UDevContext::patBlt( int nLeft,
                          int nTop,
                          int nWidth,
                          int nHeight,
                          DWORD dwRop)
{
    return ::PatBlt(*this, nLeft, nTop, nWidth, nHeight, dwRop);
}

void UDevContext::setMapMode( int nMode )
{
    ::SetMapMode((HDC)m_hObj, nMode);
}

int UDevContext::getMapMode()
{
    return ::GetMapMode((HDC)m_hObj);
}

BOOL UDevContext::rectangle(int nLeft, int nTop, int nRight, int nBottom)
{
    return ::Rectangle((HDC)m_hObj, nLeft, nTop, nRight, nBottom);
}

BOOL UDevContext::rectangle(LPCRECT lpRect)
{
    return rectangle(lpRect->left, lpRect->top,
        lpRect->right, lpRect->bottom);
}

int UDevContext::fillRect( LPCRECT lpRect, HBRUSH hBrush )
{
    return ::FillRect((HDC)m_hObj, lpRect, hBrush);
}

int UDevContext::frameRect(LPCRECT lpRect, HBRUSH hBrush)
{
    return ::FrameRect((HDC)m_hObj, lpRect, hBrush);
}

BOOL UDevContext::invertRect(LPCRECT lpRect)
{
    return ::InvertRect((HDC)m_hObj, lpRect);
}

BOOL UDevContext::roundRect(int nLeft, int nTop, int nRight, int nBottom, int nWidth, int nHeight)
{
    return ::RoundRect((HDC)m_hObj, nLeft, nTop, nRight, nBottom, nWidth, nHeight);
}

BOOL UDevContext::roundRect(LPCRECT lpRect, const POINT pt)
{
    return this->roundRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom,
        pt.x, pt.y);
}

void UDevContext::setViewportOrg( int x, int y )
{
    ::SetViewportOrgEx((HDC)m_hObj, x, y, NULL);
}

void UDevContext::setWindowOrg( int x, int y )
{
    ::SetWindowOrgEx((HDC)m_hObj, x, y, NULL);
}

BOOL UDevContext::DPToLP(LPPOINT lpPoints, int nCount)
{
    return ::DPtoLP((HDC)m_hObj, lpPoints, nCount);
}

BOOL UDevContext::LPToDP(LPPOINT lpPoints, int nCount)
{
    return ::LPtoDP((HDC)m_hObj, lpPoints, nCount);
}

BOOL UDevContext::textOut( int nX, int nY, LPCTSTR lpString, int cbString )
{
    return ::TextOut((HDC)m_hObj, nX, nY, lpString, cbString);
}

BOOL UDevContext::textOutEx( int nX, int nY, LPCTSTR lpText )
{
	return this->textOut(nX, nY, lpText, lstrlen(lpText));	
}

int UDevContext::drawText( LPCTSTR lpchText, int nCount, LPRECT lpRect, UINT uFormat )
{
    return ::DrawText((HDC)m_hObj, lpchText, nCount, lpRect, uFormat);
}

int UDevContext::drawTextEx( LPTSTR lpchText, int nCount, LPRECT lpRect, UINT uFormat, LPDRAWTEXTPARAMS lpDTParams /*= NULL*/ )
{
    return ::DrawTextEx((HDC)m_hObj, lpchText, nCount, lpRect, uFormat, lpDTParams);
}

BOOL UDevContext::extTextOut(int x, int y, UINT fuOptions, LPRECT lpRect, LPCTSTR lpchText, int nCount, const INT *lpDx)
{
    return ::ExtTextOut((HDC)m_hObj, x, y, fuOptions, lpRect, lpchText, nCount, lpDx);
}

BOOL UDevContext::getTextExtentPoint32(LPCTSTR lpString, int c, LPSIZE lpSize)
{
    return ::GetTextExtentPoint32((HDC)m_hObj, lpString, c, lpSize);
}

huys::Color UDevContext::setBKColor( huys::Color clr )
{
    return ::SetBkColor((HDC)m_hObj, clr);
}

int UDevContext::setBKMode( int iMode )
{
    return ::SetBkMode((HDC)m_hObj, iMode);
}

int UDevContext::getBKMode()
{
    return ::GetBkMode((HDC)m_hObj);
}

huys::Color UDevContext::getBKColor()
{
    return ::GetBkColor((HDC)m_hObj);
}

BOOL UDevContext::drawLine( int nX1, int nY1, int nX2, int nY2 )
{
    return ::MoveToEx((HDC)m_hObj, nX1, nY1, NULL) &&
           ::LineTo((HDC)m_hObj, nX2, nY2);
}

BOOL UDevContext::polygon(const POINT *lpPoints, int nCount)
{
    return ::Polygon((HDC)m_hObj, lpPoints, nCount);
}

BOOL UDevContext::moveTo(int x, int y)
{
    return ::MoveToEx((HDC)m_hObj, x, y, NULL);
}

BOOL UDevContext::lineTo(int x, int y)
{
    return ::LineTo((HDC)m_hObj, x, y);
}

huys::Color UDevContext::setPixel(int x, int y, huys::Color clr)
{
    return ::SetPixel((HDC)m_hObj, x, y, clr);
}

huys::Color UDevContext::getPixel(int x, int y)
{
    return ::GetPixel((HDC)m_hObj, x, y);
}

huys::Color UDevContext::getTextColor()
{
    return ::GetTextColor((HDC)m_hObj);
}

huys::Color UDevContext::setTextColor( huys::Color clr )
{
    return ::SetTextColor((HDC)m_hObj, clr);
}

void UDevContext::fillSolidRect( LPCRECT lpRect, huys::Color clr )
{  
    this->setBKColor(clr);
    this->extTextOut(0, 0, ETO_OPAQUE, (LPRECT)lpRect, NULL, 0, NULL);
}

void UDevContext::fillSolidRect( int x, int y, int cx, int cy, huys::Color clr )
{
    huys::URectL rect(x, y, x + cx, y + cy);
    this->fillSolidRect(rect, clr);
}

void UDevContext::draw3dRect( int x, int y, int cx, int cy, huys::Color clrTopLeft, huys::Color clrBottomRight ) /* BOOL roundRect(int nLeft, int nTop, int nRight, int nBottom, int nWidth, int nHeight)*/
{
    fillSolidRect(x, y, cx - 1, 1, clrTopLeft);
    fillSolidRect(x, y, 1, cy - 1, clrTopLeft);
    fillSolidRect(x + cx, y, -1, cy, clrBottomRight);
	fillSolidRect(x, y + cy, cx, -1, clrBottomRight);
}

void UDevContext::draw3dRect(LPCRECT lpRect, huys::Color clrTopLeft, huys::Color clrBottomRight )
{
    draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left,
		lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
}

void UDevContext::floodFill( int x, int y, huys::Color crColor )
{
    ::FloodFill((HDC)m_hObj, x, y, crColor);
}

UPaintDC::UPaintDC(HWND hWnd)
{
    m_hWnd = hWnd;
    m_hObj = ::BeginPaint(m_hWnd, &m_ps);
}

UPaintDC::~UPaintDC()
{
    ::EndPaint(m_hWnd, &m_ps);
}

UPrivateDC::UPrivateDC(HWND hWnd)
: m_hWnd(hWnd)
{
    m_hObj = ::GetDC(m_hWnd);
}

UPrivateDC::~UPrivateDC()
{
    ::ReleaseDC(m_hWnd, (HDC)m_hObj);
}

USmartDC::USmartDC(HDC hdc)
{
    attach(hdc);
}

USmartDC::~USmartDC()
{
    dettach();
}

UMemDC::UMemDC(HDC hdc)
{
    m_hObj = ::CreateCompatibleDC(hdc);
}

UMemDC::~UMemDC()
{
}
