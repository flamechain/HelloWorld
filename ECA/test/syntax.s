.include "test.inc"

.start _start

struc test
    name2   dword 2
    name    dword ? ; name, type, default value
ends test

_start:
    call testproc
