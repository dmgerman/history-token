multiline_comment|/*&n; * Various machine type macros&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1998, 2000 Harald Koerfgen&n; */
macro_line|#ifndef __ASM_DEC_MACHTYPE_H 
DECL|macro|__ASM_DEC_MACHTYPE_H
mdefine_line|#define __ASM_DEC_MACHTYPE_H 
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|macro|TURBOCHANNEL
mdefine_line|#define TURBOCHANNEL&t;(mips_machtype == MACH_DS5000_200 || &bslash;&n;&t;&t;&t; mips_machtype == MACH_DS5000_1XX || &bslash;&n;&t;&t;&t; mips_machtype == MACH_DS5000_XX  || &bslash;&n;&t;&t;&t; mips_machtype == MACH_DS5000_2X0)
DECL|macro|IOASIC
mdefine_line|#define IOASIC&t;&t;(mips_machtype == MACH_DS5000_1XX || &bslash;&n;&t;&t;&t; mips_machtype == MACH_DS5000_XX  || &bslash;&n;&t;&t;&t; mips_machtype == MACH_DS5000_2X0)
macro_line|#endif
eof
