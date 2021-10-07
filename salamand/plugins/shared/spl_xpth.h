//****************************************************************************
//
// Copyright (c) ALTAP, spol. s r.o. All rights reserved.
//
// This is a part of the Altap Salamander SDK library.
//
// The SDK is provided "AS IS" and without warranty of any kind and 
// ALTAP EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS AND IMPLIED, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE and NON-INFRINGEMENT.
//
//****************************************************************************

#ifndef __SPL_XPTH_H
#define __SPL_XPTH_H

#ifdef _MSC_VER
#pragma pack(push, enter_include_spl_xpth)   // aby byly struktury nezavisle na nastavenem zarovnavani
#pragma pack(4)
#endif // _MSC_VER
#ifdef __BORLANDC__
#pragma option -a4
#endif // __BORLANDC__

//
// ****************************************************************************
// CXpThemeSupportAbstract
//
// metody volaji dynamicky nactenou knihovnu UXTHEME.DLL

class CXpThemeSupportAbstract
{
  public:
    //---------------------------------------------------------------------------
    //  OpenThemeData()     - Open the theme data for the specified HWND and
    //                        semi-colon separated list of class names.
    //
    //                        OpenThemeData() will try each class name, one at
    //                        a time, and use the first matching theme info
    //                        found.  If a match is found, a theme handle
    //                        to the data is returned.  If no match is found,
    //                        a "NULL" handle is returned.
    //
    //                        When the window is destroyed or a WM_THEMECHANGED
    //                        msg is received, "CloseThemeData()" should be
    //                        called to close the theme handle.
    //
    //  hwnd                - window handle of the control/window to be themed
    //
    //  pszClassList        - class name (or list of names) to match to theme data
    //                        section.  if the list contains more than one name,
    //                        the names are tested one at a time for a match.
    //                        If a match is found, OpenThemeData() returns a
    //                        theme handle associated with the matching class.
    //                        This param is a list (instead of just a single
    //                        class name) to provide the class an opportunity
    //                        to get the "best" match between the class and
    //                        the current theme.  For example, a button might
    //                        pass L"OkButton, Button" if its ID=ID_OK.  If
    //                        the current theme has an entry for OkButton,
    //                        that will be used.  Otherwise, we fall back on
    //                        the normal Button entry.
    //---------------------------------------------------------------------------
    virtual HTHEME WINAPI OpenThemeData(HWND hwnd, LPCWSTR pszClassList) = 0;

    //---------------------------------------------------------------------------
    //  CloseTHemeData()    - closes the theme data handle.  This should be done
    //                        when the window being themed is destroyed or
    //                        whenever a WM_THEMECHANGED msg is received
    //                        (followed by an attempt to create a new Theme data
    //                        handle).
    //
    //  hTheme              - open theme data handle (returned from prior call
    //                        to OpenThemeData() API).
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI CloseThemeData(HTHEME hTheme) = 0;

    //---------------------------------------------------------------------------
    //    functions for basic drawing support
    //---------------------------------------------------------------------------
    // The following methods are the theme-aware drawing services.
    // Controls/Windows are defined in drawable "parts" by their author: a
    // parent part and 0 or more child parts.  Each of the parts can be
    // described in "states" (ex: disabled, hot, pressed).
    //---------------------------------------------------------------------------
    // For the list of all themed classes and the definition of all
    // parts and states, see the file "tmschmea.h".
    //---------------------------------------------------------------------------
    // Each of the below methods takes a "iPartId" param to specify the
    // part and a "iStateId" to specify the state of the part.
    // "iStateId=0" refers to the root part.  "iPartId" = "0" refers to
    // the root class.
    //-----------------------------------------------------------------------
    // Note: draw operations are always scaled to fit (and not to exceed)
    // the specified "Rect".
    //-----------------------------------------------------------------------

    //------------------------------------------------------------------------
    //  DrawThemeBackground()
    //                      - draws the theme-specified border and fill for
    //                        the "iPartId" and "iStateId".  This could be
    //                        based on a bitmap file, a border and fill, or
    //                        other image description.
    //
    //  hTheme              - theme data handle
    //  hdc                 - HDC to draw into
    //  iPartId             - part number to draw
    //  iStateId            - state number (of the part) to draw
    //  pRect               - defines the size/location of the part
    //  pClipRect           - optional clipping rect (don't draw outside it)
    //------------------------------------------------------------------------
    virtual HRESULT WINAPI DrawThemeBackground(HTHEME hTheme, HDC hdc,
                                               int iPartId, int iStateId, const RECT *pRect,
                                               OPTIONAL const RECT *pClipRect) = 0;

    //-------------------------------------------------------------------------
    //  DrawThemeText()     - draws the text using the theme-specified
    //                        color and font for the "iPartId" and
    //                        "iStateId".
    //
    //  hTheme              - theme data handle
    //  hdc                 - HDC to draw into
    //  iPartId             - part number to draw
    //  iStateId            - state number (of the part) to draw
    //  pszText             - actual text to draw
    //  dwCharCount         - number of chars to draw (-1 for all)
    //  dwTextFlags         - same as DrawText() "uFormat" param
    //  dwTextFlags2        - additional drawing options
    //  pRect               - defines the size/location of the part
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI DrawThemeText(HTHEME hTheme, HDC hdc, int iPartId,
                                         int iStateId, LPCWSTR pszText, int iCharCount,
                                         DWORD dwTextFlags, DWORD dwTextFlags2,
                                         const RECT *pRect) = 0;

    //-------------------------------------------------------------------------
    //  GetThemeBackgroundContentRect()
    //                      - gets the size of the content for the theme-defined
    //                        background.  This is usually the area inside
    //                        the borders or Margins.
    //
    //      hTheme          - theme data handle
    //      hdc             - (optional) device content to be used for drawing
    //      iPartId         - part number to draw
    //      iStateId        - state number (of the part) to draw
    //      pBoundingRect   - the outer RECT of the part being drawn
    //      pContentRect    - RECT to receive the content area
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeBackgroundContentRect(HTHEME hTheme, OPTIONAL HDC hdc,
                                                         int iPartId, int iStateId,
                                                         const RECT *pBoundingRect,
                                                         OUT RECT *pContentRect) = 0;

    //-------------------------------------------------------------------------
    //  GetThemeBackgroundExtent() - calculates the size/location of the theme-
    //                               specified background based on the
    //                               "pContentRect".
    //
    //      hTheme          - theme data handle
    //      hdc             - (optional) device content to be used for drawing
    //      iPartId         - part number to draw
    //      iStateId        - state number (of the part) to draw
    //      pContentRect    - RECT that defines the content area
    //      pBoundingRect   - RECT to receive the overall size/location of part
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeBackgroundExtent(HTHEME hTheme, OPTIONAL HDC hdc,
                                                    int iPartId, int iStateId,
                                                    const RECT *pContentRect,
                                                    OUT RECT *pExtentRect) = 0;

    //-------------------------------------------------------------------------
    //  GetThemePartSize() - returns the specified size of the theme part
    //
    //  hTheme              - theme data handle
    //  hdc                 - HDC to select font into & measure against
    //  iPartId             - part number to retrieve size for
    //  iStateId            - state number (of the part)
    //  prc                 - (optional) rect for part drawing destination
    //  eSize               - the type of size to be retreived
    //  psz                 - receives the specified size of the part
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemePartSize(HTHEME hTheme, HDC hdc, int iPartId,
                                            int iStateId, OPTIONAL RECT *prc,
                                            enum THEMESIZE eSize, OUT SIZE *psz) = 0;


    //-------------------------------------------------------------------------
    //  GetThemeTextExtent() - calculates the size/location of the specified
    //                         text when rendered in the Theme Font.
    //
    //  hTheme              - theme data handle
    //  hdc                 - HDC to select font & measure into
    //  iPartId             - part number to draw
    //  iStateId            - state number (of the part)
    //  pszText             - the text to be measured
    //  dwCharCount         - number of chars to draw (-1 for all)
    //  dwTextFlags         - same as DrawText() "uFormat" param
    //  pszBoundingRect     - optional: to control layout of text
    //  pszExtentRect       - receives the RECT for text size/location
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeTextExtent(HTHEME hTheme, HDC hdc,
                                              int iPartId, int iStateId, LPCWSTR pszText,
                                              int iCharCount, DWORD dwTextFlags,
                                              OPTIONAL const RECT *pBoundingRect,
                                              OUT RECT *pExtentRect) = 0;

    //-------------------------------------------------------------------------
    //  GetThemeTextMetrics()
    //                      - returns info about the theme-specified font
    //                        for the part/state passed in.
    //
    //  hTheme              - theme data handle
    //  hdc                 - optional: HDC for screen context
    //  iPartId             - part number to draw
    //  iStateId            - state number (of the part)
    //  ptm                 - receives the font info
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeTextMetrics(HTHEME hTheme, OPTIONAL HDC hdc,
                                               int iPartId, int iStateId,
                                               OUT TEXTMETRICW* ptm) = 0;

    //-------------------------------------------------------------------------
    //  GetThemeBackgroundRegion()
    //                      - computes the region for a regular or partially
    //                        transparent theme-specified background that is
    //                        bound by the specified "pRect".
    //                        If the rectangle is empty, sets the HRGN to NULL
    //                        and return S_FALSE.
    //
    //  hTheme              - theme data handle
    //  hdc                 - optional HDC to draw into (DPI scaling)
    //  iPartId             - part number to draw
    //  iStateId            - state number (of the part)
    //  pRect               - the RECT used to draw the part
    //  pRegion             - receives handle to calculated region
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeBackgroundRegion(HTHEME hTheme, OPTIONAL HDC hdc,
                                                    int iPartId, int iStateId,
                                                    const RECT *pRect,
                                                    OUT HRGN *pRegion) = 0;

    //-------------------------------------------------------------------------
    //  HitTestThemeBackground()
    //                      - returns a HitTestCode (a subset of the values
    //                        returned by WM_NCHITTEST) for the point "ptTest"
    //                        within the theme-specified background
    //                        (bound by pRect).  "pRect" and "ptTest" should
    //                        both be in the same coordinate system
    //                        (client, screen, etc).
    //
    //      hTheme          - theme data handle
    //      hdc             - HDC to draw into
    //      iPartId         - part number to test against
    //      iStateId        - state number (of the part)
    //      pRect           - the RECT used to draw the part
    //      hrgn            - optional region to use; must be in same coordinates as
    //                      -    pRect and pTest.
    //      ptTest          - the hit point to be tested
    //      dwOptions       - HTTB_xxx constants
    //      pwHitTestCode   - receives the returned hit test code - one of:
    //
    //                        HTNOWHERE, HTLEFT, HTTOPLEFT, HTBOTTOMLEFT,
    //                        HTRIGHT, HTTOPRIGHT, HTBOTTOMRIGHT,
    //                        HTTOP, HTBOTTOM, HTCLIENT
    //-------------------------------------------------------------------------
    virtual HRESULT WINAPI HitTestThemeBackground(HTHEME hTheme, OPTIONAL HDC hdc, int iPartId,
                                                  int iStateId, DWORD dwOptions, const RECT *pRect,
                                                  OPTIONAL HRGN hrgn, POINT ptTest,
                                                  OUT WORD *pwHitTestCode) = 0;

    //------------------------------------------------------------------------
    //  DrawThemeEdge()     - Similar to the DrawEdge() API, but uses part colors
    //                        and is high-DPI aware
    //  hTheme              - theme data handle
    //  hdc                 - HDC to draw into
    //  iPartId             - part number to draw
    //  iStateId            - state number of part
    //  pDestRect           - the RECT used to draw the line(s)
    //  uEdge               - Same as DrawEdge() API
    //  uFlags              - Same as DrawEdge() API
    //  pContentRect        - Receives the interior rect if (uFlags & BF_ADJUST)
    //------------------------------------------------------------------------
    virtual HRESULT WINAPI DrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
                                         const RECT *pDestRect, UINT uEdge, UINT uFlags,
                                         OPTIONAL OUT RECT *pContentRect) = 0;


    //------------------------------------------------------------------------
    //  DrawThemeIcon()     - draws an image within an imagelist based on
    //                        a (possible) theme-defined effect.
    //
    //  hTheme              - theme data handle
    //  hdc                 - HDC to draw into
    //  iPartId             - part number to draw
    //  iStateId            - state number of part
    //  pRect               - the RECT to draw the image within
    //  himl                - handle to IMAGELIST
    //  iImageIndex         - index into IMAGELIST (which icon to draw)
    //------------------------------------------------------------------------
    virtual HRESULT WINAPI DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId,
                                         int iStateId, const RECT *pRect,
                                         HIMAGELIST himl, int iImageIndex) = 0;

    //---------------------------------------------------------------------------
    //  IsThemePartDefined() - returns TRUE if the theme has defined parameters
    //                         for the specified "iPartId" and "iStateId".
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number to find definition for
    //  iStateId            - state number of part
    //---------------------------------------------------------------------------
    virtual BOOL WINAPI IsThemePartDefined(HTHEME hTheme, int iPartId, int iStateId) = 0;

    //---------------------------------------------------------------------------
    //  IsThemeBackgroundPartiallyTransparent()
    //                      - returns TRUE if the theme specified background for
    //                        the part/state has transparent pieces or
    //                        alpha-blended pieces.
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //---------------------------------------------------------------------------
    virtual BOOL WINAPI IsThemeBackgroundPartiallyTransparent(HTHEME hTheme, int iPartId,
                                                              int iStateId) = 0;

    //---------------------------------------------------------------------------
    //    lower-level theme information services
    //---------------------------------------------------------------------------
    // The following methods are getter routines for each of the Theme Data types.
    // Controls/Windows are defined in drawable "parts" by their author: a
    // parent part and 0 or more child parts.  Each of the parts can be
    // described in "states" (ex: disabled, hot, pressed).
    //---------------------------------------------------------------------------
    // Each of the below methods takes a "iPartId" param to specify the
    // part and a "iStateId" to specify the state of the part.
    // "iStateId=0" refers to the root part.  "iPartId" = "0" refers to
    // the root class.
    //-----------------------------------------------------------------------
    // Each method also take a "iPropId" param because multiple instances of
    // the same primitive type can be defined in the theme schema.
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //  GetThemeColor()     - Get the value for the specified COLOR property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  pColor              - receives the value of the property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeColor(HTHEME hTheme, int iPartId,
                                         int iStateId, int iPropId,
                                         OUT COLORREF *pColor) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeMetric()    - Get the value for the specified metric/size
    //                        property
    //
    //  hTheme              - theme data handle
    //  hdc                 - (optional) hdc to be drawn into (DPI scaling)
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  piVal               - receives the value of the property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeMetric(HTHEME hTheme, OPTIONAL HDC hdc, int iPartId,
                                          int iStateId, int iPropId, OUT int *piVal) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeString()    - Get the value for the specified string property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  pszBuff             - receives the string property value
    //  cchMaxBuffChars     - max. number of chars allowed in pszBuff
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeString(HTHEME hTheme, int iPartId,
                                          int iStateId, int iPropId, OUT LPWSTR pszBuff,
                                          int cchMaxBuffChars) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeBool()      - Get the value for the specified BOOL property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  pfVal               - receives the value of the property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeBool(HTHEME hTheme, int iPartId,
                                        int iStateId, int iPropId, OUT BOOL *pfVal) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeInt()       - Get the value for the specified int property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  piVal               - receives the value of the property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeInt(HTHEME hTheme, int iPartId,
                                       int iStateId, int iPropId, OUT int *piVal) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeEnumValue() - Get the value for the specified ENUM property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  piVal               - receives the value of the enum (cast to int*)
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeEnumValue(HTHEME hTheme, int iPartId,
                                             int iStateId, int iPropId,
                                             OUT int *piVal) = 0;

    //-----------------------------------------------------------------------
    //  GetThemePosition()  - Get the value for the specified position
    //                        property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  pPoint              - receives the value of the position property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemePosition(HTHEME hTheme, int iPartId,
                                            int iStateId, int iPropId,
                                            OUT POINT *pPoint) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeFont()      - Get the value for the specified font property
    //
    //  hTheme              - theme data handle
    //  hdc                 - (optional) hdc to be drawn to (DPI scaling)
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  pFont               - receives the value of the LOGFONT property
    //                        (scaled for the current logical screen dpi)
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeFont(HTHEME hTheme, OPTIONAL HDC hdc, int iPartId,
                                        int iStateId, int iPropId, OUT LOGFONTW *pFont) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeRect()      - Get the value for the specified RECT property
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to get the value for
    //  pRect               - receives the value of the RECT property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeRect(HTHEME hTheme, int iPartId,
                                        int iStateId, int iPropId, OUT RECT *pRect) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeMargins()   - Get the value for the specified MARGINS property
    //
    //      hTheme          - theme data handle
    //      hdc             - (optional) hdc to be used for drawing
    //      iPartId         - part number
    //      iStateId        - state number of part
    //      iPropId         - the property number to get the value for
    //      prc             - RECT for area to be drawn into
    //      pMargins        - receives the value of the MARGINS property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeMargins(HTHEME hTheme, OPTIONAL HDC hdc, int iPartId,
                                           int iStateId, int iPropId, OPTIONAL RECT *prc,
                                           OUT MARGINS *pMargins) = 0;

    //-----------------------------------------------------------------------
    //  GetThemeIntList()   - Get the value for the specified INTLIST struct
    //
    //      hTheme          - theme data handle
    //      iPartId         - part number
    //      iStateId        - state number of part
    //      iPropId         - the property number to get the value for
    //      pIntList        - receives the value of the INTLIST property
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeIntList(HTHEME hTheme, int iPartId,
                                           int iStateId, int iPropId,
                                           OUT INTLIST *pIntList) = 0;

    //-----------------------------------------------------------------------
    //  GetThemePropertyOrigin()
    //                      - searches for the specified theme property
    //                        and sets "pOrigin" to indicate where it was
    //                        found (or not found)
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to search for
    //  pOrigin             - receives the value of the property origin
    //-----------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemePropertyOrigin(HTHEME hTheme, int iPartId,
                                                  int iStateId, int iPropId,
                                                  OUT enum PROPERTYORIGIN *pOrigin) = 0;

    //---------------------------------------------------------------------------
    //  SetWindowTheme()
    //                      - redirects an existing Window to use a different
    //                        section of the current theme information than its
    //                        class normally asks for.
    //
    //  hwnd                - the handle of the window (cannot be NULL)
    //
    //  pszSubAppName       - app (group) name to use in place of the calling
    //                        app's name.  If NULL, the actual calling app
    //                        name will be used.
    //
    //  pszSubIdList        - semicolon separated list of class Id names to
    //                        use in place of actual list passed by the
    //                        window's class.  if NULL, the id list from the
    //                        calling class is used.
    //---------------------------------------------------------------------------
    // The Theme Manager will remember the "pszSubAppName" and the
    // "pszSubIdList" associations thru the lifetime of the window (even
    // if themes are subsequently changed).  The window is sent a
    // "WM_THEMECHANGED" msg at the end of this call, so that the new
    // theme can be found and applied.
    //---------------------------------------------------------------------------
    // When "pszSubAppName" or "pszSubIdList" are NULL, the Theme Manager
    // removes the previously remember association.  To turn off theme-ing for
    // the specified window, you can pass an empty string (L"") so it
    // won't match any section entries.
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName,
                                          LPCWSTR pszSubIdList) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeFilename()  - Get the value for the specified FILENAME property.
    //
    //  hTheme              - theme data handle
    //  iPartId             - part number
    //  iStateId            - state number of part
    //  iPropId             - the property number to search for
    //  pszThemeFileName    - output buffer to receive the filename
    //  cchMaxBuffChars     - the size of the return buffer, in chars
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeFilename(HTHEME hTheme, int iPartId,
                                            int iStateId, int iPropId,
                                            OUT LPWSTR pszThemeFileName,
                                            int cchMaxBuffChars) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysColor()  - Get the value of the specified System color.
    //
    //  hTheme              - the theme data handle.  if non-NULL, will return
    //                        color from [SysMetrics] section of theme.
    //                        if NULL, will return the global system color.
    //
    //  iColorId            - the system color index defined in winuser.h
    //---------------------------------------------------------------------------
    virtual COLORREF WINAPI GetThemeSysColor(HTHEME hTheme, int iColorId) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysColorBrush()
    //                      - Get the brush for the specified System color.
    //
    //  hTheme              - the theme data handle.  if non-NULL, will return
    //                        brush matching color from [SysMetrics] section of
    //                        theme.  if NULL, will return the brush matching
    //                        global system color.
    //
    //  iColorId            - the system color index defined in winuser.h
    //---------------------------------------------------------------------------
    virtual HBRUSH WINAPI GetThemeSysColorBrush(HTHEME hTheme, int iColorId) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysBool()   - Get the boolean value of specified System metric.
    //
    //  hTheme              - the theme data handle.  if non-NULL, will return
    //                        BOOL from [SysMetrics] section of theme.
    //                        if NULL, will return the specified system boolean.
    //
    //  iBoolId             - the TMT_XXX BOOL number (first BOOL
    //                        is TMT_FLATMENUS)
    //---------------------------------------------------------------------------
    virtual BOOL WINAPI GetThemeSysBool(HTHEME hTheme, int iBoolId) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysSize()   - Get the value of the specified System size metric.
    //                        (scaled for the current logical screen dpi)
    //
    //  hTheme              - the theme data handle.  if non-NULL, will return
    //                        size from [SysMetrics] section of theme.
    //                        if NULL, will return the global system metric.
    //
    //  iSizeId             - the following values are supported when
    //                        hTheme is non-NULL:
    //
    //                          SM_CXBORDER   (border width)
    //                          SM_CXVSCROLL  (scrollbar width)
    //                          SM_CYHSCROLL  (scrollbar height)
    //                          SM_CXSIZE     (caption width)
    //                          SM_CYSIZE     (caption height)
    //                          SM_CXSMSIZE   (small caption width)
    //                          SM_CYSMSIZE   (small caption height)
    //                          SM_CXMENUSIZE (menubar width)
    //                          SM_CYMENUSIZE (menubar height)
    //
    //                        when hTheme is NULL, iSizeId is passed directly
    //                        to the GetSystemMetrics() function
    //---------------------------------------------------------------------------
    virtual int WINAPI GetThemeSysSize(HTHEME hTheme, int iSizeId) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysFont()   - Get the LOGFONT for the specified System font.
    //
    //  hTheme              - the theme data handle.  if non-NULL, will return
    //                        font from [SysMetrics] section of theme.
    //                        if NULL, will return the specified system font.
    //
    //  iFontId             - the TMT_XXX font number (first font
    //                        is TMT_CAPTIONFONT)
    //
    //  plf                 - ptr to LOGFONT to receive the font value.
    //                        (scaled for the current logical screen dpi)
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeSysFont(HTHEME hTheme, int iFontId, OUT LOGFONTW *plf) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysString() - Get the value of specified System string metric.
    //
    //  hTheme              - the theme data handle (required)
    //
    //  iStringId           - must be one of the following values:
    //
    //                          TMT_CSSNAME
    //                          TMT_XMLNAME
    //
    //  pszStringBuff       - the buffer to receive the string value
    //
    //  cchMaxStringChars   - max. number of chars that pszStringBuff can hold
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeSysString(HTHEME hTheme, int iStringId,
                                             OUT LPWSTR pszStringBuff, int cchMaxStringChars) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeSysInt() - Get the value of specified System int.
    //
    //  hTheme              - the theme data handle (required)
    //
    //  iIntId              - must be one of the following values:
    //
    //                          TMT_DPIX
    //                          TMT_DPIY
    //                          TMT_MINCOLORDEPTH
    //
    //  piValue             - ptr to int to receive value
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue) = 0;

    //---------------------------------------------------------------------------
    //  IsThemeActive()     - can be used to test if a system theme is active
    //                        for the current user session.
    //
    //                        use the API "IsAppThemed()" to test if a theme is
    //                        active for the calling process.
    //---------------------------------------------------------------------------
    virtual BOOL WINAPI IsThemeActive() = 0;

    //---------------------------------------------------------------------------
    //  IsAppThemed()       - returns TRUE if a theme is active and available to
    //                        the current process
    //---------------------------------------------------------------------------
    virtual BOOL WINAPI IsAppThemed() = 0;


    //---------------------------------------------------------------------------
    //  GetWindowTheme()    - if window is themed, returns its most recent
    //                        HTHEME from OpenThemeData() - otherwise, returns
    //                        NULL.
    //
    //      hwnd            - the window to get the HTHEME of
    //---------------------------------------------------------------------------
    virtual HTHEME WINAPI GetWindowTheme(HWND hwnd) = 0;

    //---------------------------------------------------------------------------
    //  EnableThemeDialogTexture()
    //
    //  - Enables/disables dialog background theme.  This method can be used to
    //    tailor dialog compatibility with child windows and controls that
    //    may or may not coordinate the rendering of their client area backgrounds
    //    with that of their parent dialog in a manner that supports seamless
    //    background texturing.
    //
    //      hdlg         - the window handle of the target dialog
    //      dwFlags      - ETDT_ENABLE to enable the theme-defined dialog background texturing,
    //                     ETDT_DISABLE to disable background texturing,
    //                     ETDT_ENABLETAB to enable the theme-defined background
    //                          texturing using the Tab texture
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags) = 0;

    //---------------------------------------------------------------------------
    //  IsThemeDialogTextureEnabled()
    //
    //  - Reports whether the dialog supports background texturing.
    //
    //      hdlg         - the window handle of the target dialog
    //---------------------------------------------------------------------------
    virtual BOOL WINAPI IsThemeDialogTextureEnabled(HWND hwnd) = 0;


    //---------------------------------------------------------------------------
    //  GetThemeAppProperties()
    //                      - returns the app property flags that control theming
    //---------------------------------------------------------------------------
    virtual DWORD WINAPI GetThemeAppProperties() = 0;

    //---------------------------------------------------------------------------
    //  SetThemeAppProperties()
    //                      - sets the flags that control theming within the app
    //
    //      dwFlags         - the flag values to be set
    //---------------------------------------------------------------------------
    virtual void WINAPI SetThemeAppProperties(DWORD dwFlags) = 0;

    //---------------------------------------------------------------------------
    //  GetCurrentThemeName()
    //                      - Get the name of the current theme in-use.
    //                        Optionally, return the ColorScheme name and the
    //                        Size name of the theme.
    //
    //  pszThemeFileName    - receives the theme path & filename
    //  cchMaxNameChars     - max chars allowed in pszNameBuff
    //
    //  pszColorBuff        - (optional) receives the canonical color scheme name
    //                        (not the display name)
    //  cchMaxColorChars    - max chars allowed in pszColorBuff
    //
    //  pszSizeBuff         - (optional) receives the canonical size name
    //                        (not the display name)
    //  cchMaxSizeChars     - max chars allowed in pszSizeBuff
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI GetCurrentThemeName(OUT LPWSTR pszThemeFileName, int cchMaxNameChars,
                                               OUT OPTIONAL LPWSTR pszColorBuff, int cchMaxColorChars,
                                               OUT OPTIONAL LPWSTR pszSizeBuff, int cchMaxSizeChars) = 0;

    //---------------------------------------------------------------------------
    //  GetThemeDocumentationProperty()
    //                      - Get the value for the specified property name from
    //                        the [documentation] section of the themes.ini file
    //                        for the specified theme.  If the property has been
    //                        localized in the theme files string table, the
    //                        localized version of the property value is returned.
    //
    //  pszThemeFileName    - filename of the theme file to query
    //  pszPropertyName     - name of the string property to retreive a value for
    //  pszValueBuff        - receives the property string value
    //  cchMaxValChars      - max chars allowed in pszValueBuff
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI GetThemeDocumentationProperty(LPCWSTR pszThemeName, LPCWSTR pszPropertyName,
                                                         OUT LPWSTR pszValueBuff, int cchMaxValChars) = 0;

    //---------------------------------------------------------------------------
    //  Theme API Error Handling
    //
    //      All functions in the Theme API not returning an HRESULT (THEMEAPI_)
    //      use the WIN32 function "SetLastError()" to record any call failures.
    //
    //      To retreive the error code of the last failure on the
    //      current thread for these type of API's, use the WIN32 function
    //      "GetLastError()".
    //
    //      All Theme API error codes (HRESULT's and GetLastError() values)
    //      should be normal win32 errors which can be formatted into
    //      strings using the Win32 API FormatMessage().
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // DrawThemeParentBackground()
    //                      - used by partially-transparent or alpha-blended
    //                        child controls to draw the part of their parent
    //                        that they appear in front of.
    //
    //  hwnd                - handle of the child control
    //  hdc                 - hdc of the child control
    //  prc                 - (optional) rect that defines the area to be
    //                        drawn (CHILD coordinates)
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI DrawThemeParentBackground(HWND hwnd, HDC hdc, OPTIONAL RECT* prc) = 0;

    //---------------------------------------------------------------------------
    //  EnableTheming()     - enables or disables themeing for the current user
    //                        in the current and future sessions.
    //
    //  fEnable             - if FALSE, disable theming & turn themes off.
    //                      - if TRUE, enable themeing and, if user previously
    //                        had a theme active, make it active now.
    //---------------------------------------------------------------------------
    virtual HRESULT WINAPI EnableTheming(BOOL fEnable) = 0;
};

#ifdef _MSC_VER
#pragma pack(pop, enter_include_spl_xpth)
#endif // _MSC_VER
#ifdef __BORLANDC__
#pragma option -a
#endif // __BORLANDC__

#endif // __SPL_XPTH_H
