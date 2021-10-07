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
#include <shlobj.h>
#include <crtdbg.h>
#include <limits.h>
#include <process.h>
#include <commctrl.h>
#include <ostream>
#include <stdio.h>
#include <time.h>
#include <tchar.h>

#if defined(_DEBUG) && defined(_MSC_VER)  // without passing file+line to 'new' operator, list of memory leaks shows only 'crtdbg.h(552)'
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "versinfo.rh2"

#include "spl_com.h"
#include "spl_base.h"
#include "spl_arc.h"
#include "spl_gen.h"
#include "spl_file.h"
#include "spl_fs.h"
#include "spl_menu.h"
#include "spl_thum.h"
#include "spl_view.h"
#include "spl_gui.h"
#include "spl_vers.h"

#include "dbg.h"
#include "mhandles.h"
#include "arraylt.h"
#include "winliblt.h"
#include "auxtools.h"
