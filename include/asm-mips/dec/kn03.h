multiline_comment|/*&n; * Hardware info about DEC DECstation 5000/2x0 systems (otherwise known&n; * as 3max+ or kn03.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by curteousy of Chris Fraser.&n; *&n; * These are addresses which have to be known early in the boot process.&n; * For other addresses refer to tc.h ioasic_addrs.h and friends.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN03_H 
DECL|macro|__ASM_MIPS_DEC_KN03_H
mdefine_line|#define __ASM_MIPS_DEC_KN03_H 
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Motherboard regs (kseg1 addresses)&n; */
DECL|macro|KN03_SSR_ADDR
mdefine_line|#define KN03_SSR_ADDR&t;KSEG1ADDR(0x1f840100)&t;/* system control &amp; status reg */
DECL|macro|KN03_SIR_ADDR
mdefine_line|#define KN03_SIR_ADDR&t;KSEG1ADDR(0x1f840110)&t;/* system interrupt reg */
DECL|macro|KN03_SIRM_ADDR
mdefine_line|#define KN03_SIRM_ADDR&t;KSEG1ADDR(0x1f840120)&t;/* system interrupt mask reg */
multiline_comment|/*&n; * Some port addresses...&n; * FIXME: these addresses are incomplete and need tidying up!&n; */
DECL|macro|KN03_RTC_BASE
mdefine_line|#define KN03_RTC_BASE&t;(KSEG1ADDR(0x1f800000 + 0x200000)) /* ASIC + SL8 */
macro_line|#endif /* __ASM_MIPS_DEC_KN03_H */
eof
