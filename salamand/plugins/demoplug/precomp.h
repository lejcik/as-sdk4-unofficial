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

#pragma once

#define WIN32_LEAN_AND_MEAN // exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <CommDlg.h>
#include <ShellAPI.h>
#include <shlobj.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif // _MSC_VER
#include <limits.h>
#include <process.h>
#include <commctrl.h>
#include <ostream>
#include <stdio.h>
#include <time.h>

#if defined(_DEBUG) && defined(_MSC_VER)  // without passing file+line to 'new' operator, list of memory leaks shows only 'crtdbg.h(552)'
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// If DEMOPLUG_COMPATIBLE_WITH_300 is defined, plugin is compiled as compatible with Salamander 3.0
// (otherwise it is compiled for current version of Salamander and later).
// NOTE: the ideal is to define DEMOPLUG_COMPATIBLE_WITH_300 for whole plugin project
//       in Project Settings. DemoPlug defines it here just to make adding/removing easier.
#define DEMOPLUG_COMPATIBLE_WITH_300

#ifdef DEMOPLUG_COMPATIBLE_WITH_300
#define SALSDK_COMPATIBLE_WITH_VER 102    // 64 = Altap Salamander 4.0 (SDK will be defined to be compatible with version 3.0)
#endif // DEMOPLUG_COMPATIBLE_WITH_300

#include "versinfo.rh2"

#include "spl_com.h"
#include "spl_base.h"
#include "spl_arc.h"
#include "spl_gen.h"
#include "spl_fs.h"
#include "spl_menu.h"
#include "spl_thum.h"
#include "spl_view.h"
#include "spl_vers.h"
#include "spl_gui.h"

#include "dbg.h"
#include "mhandles.h"
#include "arraylt.h"
#include "winliblt.h"
#include "auxtools.h"
#include "dialogs.h"
#include "demoplug.h"
#include "demoplug.rh"
#include "demoplug.rh2"
#include "lang\lang.rh"

#ifdef __BORLANDC__
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif // __BORLANDC__
