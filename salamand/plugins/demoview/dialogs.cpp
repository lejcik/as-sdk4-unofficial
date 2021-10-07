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

#include "precomp.h"

//****************************************************************************
//
// CCommonDialog
//

CCommonDialog::CCommonDialog(HINSTANCE hInstance, int resID, HWND hParent, CObjectOrigin origin)
: CDialog(hInstance, resID, hParent, origin)
{
}

CCommonDialog::CCommonDialog(HINSTANCE hInstance, int resID, int helpID, HWND hParent, CObjectOrigin origin)
: CDialog(hInstance, resID, helpID, hParent, origin)
{
}

INT_PTR
CCommonDialog::DialogProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_INITDIALOG:
    {
      // horizontalni i vertikalni vycentrovani dialogu k parentu
      if (Parent != NULL)
        SalamanderGeneral->MultiMonCenterWindow(HWindow, Parent, TRUE);
      break; // chci focus od DefDlgProc
    }
  }
  return CDialog::DialogProc(uMsg, wParam, lParam);
}

void
CCommonDialog::NotifDlgJustCreated()
{
  SalamanderGUI->ArrangeHorizontalLines(HWindow);
}

//
// ****************************************************************************
// CCommonPropSheetPage
//

void
CCommonPropSheetPage::NotifDlgJustCreated()
{
  SalamanderGUI->ArrangeHorizontalLines(HWindow);
}

//
// ****************************************************************************
// CConfigPageViewer
//

CConfigPageViewer::CConfigPageViewer()
  : CCommonPropSheetPage(NULL, HLanguage, IDD_CFGPAGEVIEWER, IDD_CFGPAGEVIEWER, PSP_HASHELP, NULL)
{
}

void
CConfigPageViewer::Transfer(CTransferInfo &ti)
{
  ti.RadioButton(IDC_CFG_SAVEPOSONCLOSE, 1, CfgSavePosition);
  ti.RadioButton(IDC_CFG_SETBYMAINWINDOW, 0, CfgSavePosition);
}

//
// ****************************************************************************
// CConfigDialog
//

// pomocny objekt pro centrovani konfiguracniho dialogu k parentovi
class CCenteredPropertyWindow: public CWindow
{
  protected:
    virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
      switch (uMsg)
      {
        case WM_WINDOWPOSCHANGING:
        {
          WINDOWPOS *pos = (WINDOWPOS *)lParam;
          if (pos->flags & SWP_SHOWWINDOW)
          {
            HWND hParent = GetParent(HWindow);
            if (hParent != NULL)
              SalamanderGeneral->MultiMonCenterWindow(HWindow, hParent, TRUE);
          }
          break;
        }

        case WM_APP + 1000:   // mame se odpojit od dialogu (uz je vycentrovano)
        {
          DetachWindow();
          delete this;  // trochu prasarna, ale uz se 'this' nikdo ani nedotkne, takze pohoda
          return 0;
        }
      }
      return CWindow::WindowProc(uMsg, wParam, lParam);
    }
};

#ifndef LPDLGTEMPLATEEX
#include <pshpack1.h>
typedef struct DLGTEMPLATEEX
{
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD cDlgItems;
    short x;
    short y;
    short cx;
    short cy;
} DLGTEMPLATEEX, *LPDLGTEMPLATEEX;
#include <poppack.h>
#endif // LPDLGTEMPLATEEX

// pomocny call-back pro centrovani konfiguracniho dialogu k parentovi a vyhozeni '?' buttonku z captionu
int CALLBACK CenterCallback(HWND HWindow, UINT uMsg, LPARAM lParam)
{
  if (uMsg == PSCB_INITIALIZED)   // pripojime se na dialog
  {
    CCenteredPropertyWindow *wnd = new CCenteredPropertyWindow;
    if (wnd != NULL)
    {
      wnd->AttachToWindow(HWindow);
      if (wnd->HWindow == NULL) delete wnd;  // okno neni pripojeny, zrusime ho uz tady
      else
      {
        PostMessage(wnd->HWindow, WM_APP + 1000, 0, 0);  // pro odpojeni CCenteredPropertyWindow od dialogu
      }
    }
  }
  if (uMsg == PSCB_PRECREATE)   // odstraneni '?' buttonku z headeru property sheetu
  {
    // Remove the DS_CONTEXTHELP style from the dialog box template
    if (((LPDLGTEMPLATEEX)lParam)->signature == 0xFFFF) ((LPDLGTEMPLATEEX)lParam)->style &= ~DS_CONTEXTHELP;
    else ((LPDLGTEMPLATE)lParam)->style &= ~DS_CONTEXTHELP;
  }
  return 0;
}

CConfigDialog::CConfigDialog(HWND parent)
           : CPropertyDialog(parent, HLanguage, LoadStr(IDS_CFG_TITLE),
                             LastCfgPage, PSH_USECALLBACK | PSH_NOAPPLYNOW | PSH_HASHELP,
                             NULL, &LastCfgPage, CenterCallback)
{
  Add(&PageViewer);
}
