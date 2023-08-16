# manusoft-regio
Windows registry I/O classes

This is a set of simple registry I/O classes for reading and writing
Windows registry keys.

The implementation is all inline in a single header. Just include the
header in your Windows project:

#include "RegIO.h"

The following classes are provided, each in both ANSI and Unicode
variants with a neutral typedef:
- RegKey
    => basic registry key open/close wrapper
- RegKeyPriority
    => wrap a key in HKCU and HKLM
- RegKeyCULM
    => prioritize HKCU key
- RegKeyLMCU
    => prioritize HKLM key
- RegKeyReadOnly
    => read-only access
- RegKeyLM
    => wrap HKLM key
- RegKeyCU
    => wrap HKCU key
- RegKeyLMReadOnly
    => wrap read-only HKLM key
- RegKeyCUReadOnly
    => wrap read-only HKCU key

The following utility functions are provided:
- RegRemoveKey()
    => delete a RegKey
- RegCopyKey()
    => copy a RegKey
