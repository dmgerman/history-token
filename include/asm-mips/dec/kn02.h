multiline_comment|/*&n; * Hardware info about DEC DECstation 5000/2xx systems (otherwise known&n; * as 3max or kn02.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by curteousy of Chris Fraser.&n; *&n; * This file is under construction - you were warned!&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02_H 
DECL|macro|__ASM_MIPS_DEC_KN02_H
mdefine_line|#define __ASM_MIPS_DEC_KN02_H 
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Motherboard regs (kseg1 addresses)&n; */
DECL|macro|KN02_CSR_ADDR
mdefine_line|#define KN02_CSR_ADDR&t;KSEG1ADDR(0x1ff00000)&t;/* system control &amp; status reg */
multiline_comment|/*&n; * Some port addresses...&n; * FIXME: these addresses are incomplete and need tidying up!&n; */
DECL|macro|KN02_RTC_BASE
mdefine_line|#define KN02_RTC_BASE&t;KSEG1ADDR(0x1fe80000)
DECL|macro|KN02_DZ11_BASE
mdefine_line|#define KN02_DZ11_BASE&t;KSEG1ADDR(0x1fe00000)
DECL|macro|KN02_CSR_BNK32M
mdefine_line|#define KN02_CSR_BNK32M&t;(1&lt;&lt;10)&t;&t;&t;/* 32M stride */
multiline_comment|/*&n; * Interrupt enable Bits&n; */
DECL|macro|KN02_SLOT0
mdefine_line|#define KN02_SLOT0&t;(1&lt;&lt;16)
DECL|macro|KN02_SLOT1
mdefine_line|#define KN02_SLOT1&t;(1&lt;&lt;17)
DECL|macro|KN02_SLOT2
mdefine_line|#define KN02_SLOT2&t;(1&lt;&lt;18)
DECL|macro|KN02_SLOT5
mdefine_line|#define KN02_SLOT5&t;(1&lt;&lt;21)
DECL|macro|KN02_SLOT6
mdefine_line|#define KN02_SLOT6&t;(1&lt;&lt;22)
DECL|macro|KN02_SLOT7
mdefine_line|#define KN02_SLOT7&t;(1&lt;&lt;23)
macro_line|#endif /* __ASM_MIPS_DEC_KN02_H */
eof
