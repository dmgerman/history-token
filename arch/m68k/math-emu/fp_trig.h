multiline_comment|/*&n;&n;  fp_trig.h: floating-point math routines for the Linux-m68k&n;  floating point emulator.&n;&n;  Copyright (c) 1998 David Huggins-Daines.&n;&n;  I hereby give permission, free of charge, to copy, modify, and&n;  redistribute this software, in source or binary form, provided that&n;  the above copyright notice and the following disclaimer are included&n;  in all such copies.&n;&n;  THIS SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITH ABSOLUTELY NO WARRANTY, REAL&n;  OR IMPLIED.&n;&n;*/
macro_line|#ifndef FP_TRIG_H
DECL|macro|FP_TRIG_H
mdefine_line|#define FP_TRIG_H
macro_line|#include &quot;fp_emu.h&quot;
multiline_comment|/* floating point trigonometric instructions:&n;&n;   the arguments to these are in the &quot;internal&quot; extended format, that&n;   is, an &quot;exploded&quot; version of the 96-bit extended fp format used by&n;   the 68881.&n;&n;   they return a status code, which should end up in %d0, if all goes&n;   well.  */
macro_line|#endif /* FP_TRIG__H */
eof
