multiline_comment|/*&n; * Hardware info about DEC DECstation 5000/1xx systems (otherwise known&n; * as 3min or kn02ba. Apllies to the Personal DECstations 5000/xx (otherwise known&n; * as maxine or kn02ca) as well.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by curteousy of Chris Fraser.&n; * Copyright (C) 2000  Maciej W. Rozycki&n; *&n; * These are addresses which have to be known early in the boot process.&n; * For other addresses refer to tc.h ioasic_addrs.h and friends.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02XA_H 
DECL|macro|__ASM_MIPS_DEC_KN02XA_H
mdefine_line|#define __ASM_MIPS_DEC_KN02XA_H 
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Some port addresses...&n; * FIXME: these addresses are incomplete and need tidying up!&n; */
DECL|macro|KN02XA_IOASIC_BASE
mdefine_line|#define KN02XA_IOASIC_BASE&t;KSEG1ADDR(0x1c040000)&t;/* I/O ASIC */
DECL|macro|KN02XA_RTC_BASE
mdefine_line|#define KN02XA_RTC_BASE&t;&t;KSEG1ADDR(0x1c200000)&t;/* RTC */
DECL|macro|KN02XA_IOASIC_REG
mdefine_line|#define KN02XA_IOASIC_REG(r)&t;(KN02XA_IOASIC_BASE+(r))
macro_line|#endif /* __ASM_MIPS_DEC_KN02XA_H */
eof
