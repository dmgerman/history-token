multiline_comment|/*&n; * Hardware info about DEC DECstation 5000/1xx systems (otherwise known&n; * as 3min or kn02ba. Apllies to the Personal DECstations 5000/xx (otherwise known&n; * as maxine or kn02ca) as well.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by curteousy of Chris Fraser.&n; *&n; * These are addresses which have to be known early in the boot process.&n; * For other addresses refer to tc.h ioasic_addrs.h and friends.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02XA_H 
DECL|macro|__ASM_MIPS_DEC_KN02XA_H
mdefine_line|#define __ASM_MIPS_DEC_KN02XA_H 
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Motherboard regs (kseg1 addresses)&n; */
DECL|macro|KN02XA_SSR_ADDR
mdefine_line|#define KN02XA_SSR_ADDR&t;&t;KSEG1ADDR(0x1c040100)&t;/* system control &amp; status reg */
DECL|macro|KN02XA_SIR_ADDR
mdefine_line|#define KN02XA_SIR_ADDR&t;&t;KSEG1ADDR(0x1c040110)&t;/* system interrupt reg */
DECL|macro|KN02XA_SIRM_ADDR
mdefine_line|#define KN02XA_SIRM_ADDR&t;KSEG1ADDR(0x1c040120)&t;/* system interrupt mask reg */
multiline_comment|/*&n; * Some port addresses...&n; * FIXME: these addresses are incomplete and need tidying up!&n; */
DECL|macro|KN02XA_RTC_BASE
mdefine_line|#define KN02XA_RTC_BASE&t;(KSEG1ADDR(0x1c000000 + 0x200000)) /* ASIC + SL8 */
macro_line|#endif /* __ASM_MIPS_DEC_KN02XA_H */
eof
