VC2019
======

VC2019 uses .natvis files instead of autoexp.dat. Copy altap.natvis file
from subdirectory vc2019 to %VS142COMNTOOLS%..\Packages\Debugger\Visualizers (VC 2019).

When you start new debugging session in VC2019, this file will be loaded and you can
enjoy properly shown data in ALTAP's data arrays (TDirectArray and TIndirectArray, see
arraylt.h in Shared directory).
