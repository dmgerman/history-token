multiline_comment|/*&n; * Hardware info about DEC DECstation 5000/2x0 systems (otherwise known&n; * as 3max+ or kn03.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by curteousy of Chris Fraser.&n; * Copyright (C) 2000  Maciej W. Rozycki&n; *&n; * These are addresses which have to be known early in the boot process.&n; * For other addresses refer to tc.h ioasic_addrs.h and friends.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN03_H 
DECL|macro|__ASM_MIPS_DEC_KN03_H
mdefine_line|#define __ASM_MIPS_DEC_KN03_H 
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Some port addresses...&n; * FIXME: these addresses are incomplete and need tidying up!&n; */
DECL|macro|KN03_IOASIC_BASE
mdefine_line|#define KN03_IOASIC_BASE&t;KSEG1ADDR(0x1f840000)&t;/* I/O ASIC */
DECL|macro|KN03_RTC_BASE
mdefine_line|#define KN03_RTC_BASE&t;&t;KSEG1ADDR(0x1fa00000)&t;/* RTC */
DECL|macro|KN03_MCR_BASE
mdefine_line|#define KN03_MCR_BASE&t;&t;KSEG1ADDR(0x1fac0000)&t;/* MCR */
DECL|macro|KN03_MCR_BNK32M
mdefine_line|#define KN03_MCR_BNK32M&t;&t;(1&lt;&lt;10)&t;&t;&t;/* 32M stride */
DECL|macro|KN03_MCR_ECCEN
mdefine_line|#define KN03_MCR_ECCEN&t;&t;(1&lt;&lt;13)&t;&t;&t;/* ECC enabled */
DECL|macro|KN03_IOASIC_REG
mdefine_line|#define KN03_IOASIC_REG(r)&t;(KN03_IOASIC_BASE+(r))
macro_line|#endif /* __ASM_MIPS_DEC_KN03_H */
eof
