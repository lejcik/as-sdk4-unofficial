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

// ****************************************************************************
// SEKCE MENU
// ****************************************************************************

BOOL WINAPI
CPluginInterfaceForMenuExt::ExecuteMenuItem(CSalamanderForOperationsAbstract *salamander,
                                            HWND parent, int id, DWORD eventMask)
{
  switch (id)
  {
    case MENUCMD_TESTCMD:
    {
      SalamanderGeneral->ShowMessageBox("You are trying Test Command.", LoadStr(IDS_PLUGINNAME), MSGBOX_INFO);
//      SalamanderGeneral->SetUserWorkedOnPanelPath(PANEL_SOURCE);  // tento prikaz povazujeme za praci s cestou (objevi se v Alt+F12)
      break;
    }

    default: SalamanderGeneral->ShowMessageBox("Unknown command.", LoadStr(IDS_PLUGINNAME), MSGBOX_ERROR); break;
  }
  return FALSE;  // neodznacovat polozky v panelu
}

BOOL WINAPI
CPluginInterfaceForMenuExt::HelpForMenuItem(HWND parent, int id)
{
  int helpID = 0;
  switch (id)
  {
    case MENUCMD_TESTCMD: helpID = IDH_TESTCMD; break;
  }
  if (helpID != 0) SalamanderGeneral->OpenHtmlHelp(parent, HHCDisplayContext, helpID, FALSE);
  return helpID != 0;
}
