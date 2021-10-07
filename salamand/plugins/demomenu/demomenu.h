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

#ifndef __DEMOMENU_H
#define __DEMOMENU_H

// globalni data
extern HINSTANCE DLLInstance;  // handle k SPL-ku - jazykove nezavisle resourcy
extern HINSTANCE HLanguage;    // handle k SLG-cku - jazykove zavisle resourcy

// obecne rozhrani Salamandera - platne od startu az do ukonceni pluginu
extern CSalamanderGeneralAbstract *SalamanderGeneral;

char *LoadStr(int resID);

// prikazy pluginoveho menu
#define MENUCMD_TESTCMD  1

//
// ****************************************************************************
// CPluginInterface
//

class CPluginInterfaceForMenuExt: public CPluginInterfaceForMenuExtAbstract
{
  public:
    virtual DWORD WINAPI GetMenuItemState(int id, DWORD eventMask) {return 0;}
    virtual BOOL WINAPI ExecuteMenuItem(CSalamanderForOperationsAbstract *salamander, HWND parent,
                                        int id, DWORD eventMask);
    virtual BOOL WINAPI HelpForMenuItem(HWND parent, int id);
    virtual void WINAPI BuildMenu(HWND parent, CSalamanderBuildMenuAbstract *salamander) {}
};

class CPluginInterface: public CPluginInterfaceAbstract
{
  public:
    virtual void WINAPI About(HWND parent);

    virtual BOOL WINAPI Release(HWND parent, BOOL force) {return TRUE;}

    virtual void WINAPI LoadConfiguration(HWND parent, HKEY regKey, CSalamanderRegistryAbstract *registry) {}
    virtual void WINAPI SaveConfiguration(HWND parent, HKEY regKey, CSalamanderRegistryAbstract *registry) {}
    virtual void WINAPI Configuration(HWND parent) {}

    virtual void WINAPI Connect(HWND parent, CSalamanderConnectAbstract *salamander);

    virtual void WINAPI ReleasePluginDataInterface(CPluginDataInterfaceAbstract *pluginData) {}

    virtual CPluginInterfaceForArchiverAbstract * WINAPI GetInterfaceForArchiver() {return NULL;}
    virtual CPluginInterfaceForViewerAbstract * WINAPI GetInterfaceForViewer() {return NULL;}
    virtual CPluginInterfaceForMenuExtAbstract * WINAPI GetInterfaceForMenuExt();
    virtual CPluginInterfaceForFSAbstract * WINAPI GetInterfaceForFS() {return NULL;}
    virtual CPluginInterfaceForThumbLoaderAbstract * WINAPI GetInterfaceForThumbLoader() {return NULL;}

    virtual void WINAPI Event(int event, DWORD param) {}
    virtual void WINAPI ClearHistory(HWND parent) {}
    virtual void WINAPI AcceptChangeOnPathNotification(const char *path, BOOL includingSubdirs) {}

    virtual BOOL WINAPI UninstallUnregisteredComponents(HWND parent, char *componentsDescr, BOOL *uninstallSPL,
                                                        BOOL *uninstallLangDir, const char *pluginDir,
                                                        CDynamicString *deleteFileList) {return FALSE;}

    virtual void WINAPI PasswordManagerEvent(HWND parent, int event) {}
};

// rozhrani pluginu poskytnute Salamanderovi
extern CPluginInterface PluginInterface;

// otevre About okno
void OnAbout(HWND hParent);

#endif // __DEMOMENU_H
