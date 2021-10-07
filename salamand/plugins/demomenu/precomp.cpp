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

// projekt DemoMenu obsahuje tri skupiny modulu
//
// 1) modul precomp.cpp, ktery postavi demomenu.pch (/Yc"precomp.h")
// 2) moduly vyuzivajici demomenu.pch (/Yu"precomp.h")
// 3) commony maji vlastni, automaticky generovany WINDOWS.PCH
//    (/YX"windows.h" /Fp"$(OutDir)\WINDOWS.PCH")
