multiline_comment|/*&n; * Hardware info about DEC DECstation DS2100/3100 systems (otherwise known&n; * as pmax or kn01.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by curteousy of Chris Fraser.&n; *&n; * This file is under construction - you were warned!&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN01_H 
DECL|macro|__ASM_MIPS_DEC_KN01_H
mdefine_line|#define __ASM_MIPS_DEC_KN01_H 
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Some port addresses...&n; * FIXME: these addresses are incomplete and need tidying up!&n; */
DECL|macro|KN01_LANCE_BASE
mdefine_line|#define KN01_LANCE_BASE (KSEG1ADDR(0x18000000)) /* 0xB8000000 */
DECL|macro|KN01_DZ11_BASE
mdefine_line|#define KN01_DZ11_BASE&t;(KSEG1ADDR(0x1c000000)) /* 0xBC000000 */
DECL|macro|KN01_RTC_BASE
mdefine_line|#define KN01_RTC_BASE&t;(KSEG1ADDR(0x1d000000)) /* 0xBD000000 */
macro_line|#endif /* __ASM_MIPS_DEC_KN01_H */
eof
