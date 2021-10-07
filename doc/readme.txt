Welcome to SDK for Altap Salamander 3.08!

Product Description:
  The Altap Salamander Software Development Kit is set of tools, documentation
  and code samples you need to create plugins (add-ons) that can run inside 
  Altap Salamander.
  
  Please note: the Altap Salamander SDK is for programmers; if you are 
  not a programmer this package probably doesn't contain much useful 
  information.

License:
  Please read Altap Salamander SDK License Agreement in license.txt file.
  
Requirements:
  -Microsoft Windows 2000, XP, Vista, Windows 7, Windows 8.1, or Windows 10.
  -Microsoft Visual C++ 2008 or Microsoft Visual Studio 2015 (C++)
  -Microsoft HTML Help Workshop 1.3 as help compiler (optional)

Documentation:
  Due to lack of time the documentation is available only in Czech as
  comments in the header files. We hope the community will help us 
  translate it to English and convert to HTML/PDF format.
  
  For the beginning we have prepared description (in English) how to
  build DemoPlug, DemoView, DemoMenu, and UnFAT plugins (Altap Salamander
  sample plugins). We believe it is a good idea to base your own plugins
  on these sample plugins. Continue reading in the samples.txt file.

Developer Support & Community
  Altap Salamander plugin development is discussed on the support forum
  http://forum.altap.cz/ in the "Plugins Development" section.
  If you have questions or need technical support, please use this forum.

Content:
  Build Files
    Header files and libraries needed to compile and link plugins.
  Documentation
    Comments in the header files, sample plugins how-to-build.
  Sample Plugins
    Sample plugins: DemoPlug (archiver, file system, viewer, menu
    extension, thumbnail loader), DemoView (viewer, menu extension,
    thumbnail loader), DemoMenu (menu extension), and UnFAT (archiver,
    only unpacker).
  Tools
    Altap Trace Server.
  Testing  
    Special x64 and x86 builds of Altap Salamander with trace messages.
    It checks and reports many things, so it can make debugging of your
    plugin much easier.
  Debugger Visualizers
    You can learn VC2008/VC2015 debugger how to properly show data in
    ALTAP's data arrays (TDirectArray and TIndirectArray).

Download:
  The latest version of Altap Salamander SDK for release and beta versions
  can be downloaded from http://www.altap.cz/salamander/downloads/sdk/.
  If you want to get SDK for Preview Build versions released in Early Access
  Program (EAP), go to http://www.altap.cz/salamander/downloads/eap/.

Getting Started: 
  -Download Altap Salamander SDK
  -Extract it to some working directory (default should be C:\AS_SDK)
  -Walk through basic documentation in the DOC directory:
   readme.txt, license.txt
  -Read the trace_server.txt and start Trace Server
  -Read the samples.txt and try to build sample plugins (x64 and x86 versions)
   and add them to enclosed x64 and x86 special builds of Altap Salamander.
