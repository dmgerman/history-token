multiline_comment|/*&n; *  linux/include/asm-arm/arch-arc/oldlatches.h&n; *&n; *  Copyright (C) 1996 Russell King, Dave Gilbert&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Modifications:&n; *   04-04-1998&t;PJB/RMK&t;Merged arc and a5k versions&n; */
macro_line|#ifndef _ASM_ARCH_OLDLATCH_H
DECL|macro|_ASM_ARCH_OLDLATCH_H
mdefine_line|#define _ASM_ARCH_OLDLATCH_H
DECL|macro|LATCHA_FDSEL0
mdefine_line|#define LATCHA_FDSEL0    (1&lt;&lt;0)
DECL|macro|LATCHA_FDSEL1
mdefine_line|#define LATCHA_FDSEL1    (1&lt;&lt;1)
DECL|macro|LATCHA_FDSEL2
mdefine_line|#define LATCHA_FDSEL2    (1&lt;&lt;2)
DECL|macro|LATCHA_FDSEL3
mdefine_line|#define LATCHA_FDSEL3    (1&lt;&lt;3)
DECL|macro|LATCHA_FDSELALL
mdefine_line|#define LATCHA_FDSELALL  (0xf)
DECL|macro|LATCHA_SIDESEL
mdefine_line|#define LATCHA_SIDESEL   (1&lt;&lt;4)
DECL|macro|LATCHA_MOTOR
mdefine_line|#define LATCHA_MOTOR     (1&lt;&lt;5)
DECL|macro|LATCHA_INUSE
mdefine_line|#define LATCHA_INUSE     (1&lt;&lt;6)
DECL|macro|LATCHA_CHANGERST
mdefine_line|#define LATCHA_CHANGERST (1&lt;&lt;7)
DECL|macro|LATCHB_FDCDENSITY
mdefine_line|#define LATCHB_FDCDENSITY  (1&lt;&lt;1)
DECL|macro|LATCHB_FDCRESET
mdefine_line|#define LATCHB_FDCRESET    (1&lt;&lt;3)
DECL|macro|LATCHB_PRINTSTROBE
mdefine_line|#define LATCHB_PRINTSTROBE (1&lt;&lt;4)
multiline_comment|/* newval=(oldval &amp; mask)|newdata */
r_void
id|oldlatch_bupdate
c_func
(paren
r_int
r_char
id|mask
comma
r_int
r_char
id|newdata
)paren
suffix:semicolon
multiline_comment|/* newval=(oldval &amp; mask)|newdata */
r_void
id|oldlatch_aupdate
c_func
(paren
r_int
r_char
id|mask
comma
r_int
r_char
id|newdata
)paren
suffix:semicolon
macro_line|#endif
eof
