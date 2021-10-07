VC2008
======

We have prepared patch for autoexp.dat file. This patch learns VC2008 debugger how to
properly show data in ALTAP's data arrays (TDirectArray and TIndirectArray, see
arraylt.h in Shared directory). In preview tooltip it displays count of items in array
and the list of items. When you click [+] icon in tooltip, you can see other parameters
of array and again list of items. If you have more items in array, we recommend to add
array to Watch window because it has scrollbar, you can watch up to one million items
here (it is Watch window limit).

We have stored original autoexp.dat file (autoexp.dat.original) and its patched
version (autoexp.dat) in vc2008 subdirectory.

You will find autoexp.dat in your MSVC installation directory: e.g.
C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Packages\Debugger\autoexp.dat.



VC2015
======

VC2015 uses .natvis files instead of autoexp.dat. Copy altap.natvis file
from subdirectory vc2015 to %VS140COMNTOOLS%..\Packages\Debugger\Visualizers (VC 2015).

When you start new debugging session in VC2015, this file will be loaded and you can
enjoy properly shown data in ALTAP's data arrays (TDirectArray and TIndirectArray, see
arraylt.h in Shared directory).
