multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 - 2000 Ralf Baechle&n; */
macro_line|#ifndef _ASM_FLOPPY_H
DECL|macro|_ASM_FLOPPY_H
mdefine_line|#define _ASM_FLOPPY_H
DECL|function|fd_cacheflush
r_static
r_inline
r_void
id|fd_cacheflush
c_func
(paren
r_char
op_star
id|addr
comma
r_int
id|size
)paren
(brace
id|dma_cache_wback_inv
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
DECL|macro|MAX_BUFFER_SECTORS
mdefine_line|#define MAX_BUFFER_SECTORS 24
multiline_comment|/*&n; * And on Mips&squot;s the CMOS info fails also ...&n; *&n; * FIXME: This information should come from the ARC configuration tree&n; *        or whereever a particular machine has stored this ...&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE &t;&t;fd_drive_type(0)
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE&t;&t;fd_drive_type(1)
DECL|macro|FDC1
mdefine_line|#define FDC1&t;&t;&t;fd_getfdaddr1();
DECL|macro|N_FDC
mdefine_line|#define N_FDC 1&t;&t;&t;/* do you *really* want a second controller? */
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
multiline_comment|/*&n; * The DMA channel used by the floppy controller cannot access data at&n; * addresses &gt;= 16MB&n; *&n; * Went back to the 1MB limit, as some people had problems with the floppy&n; * driver otherwise. It doesn&squot;t matter much for performance anyway, as most&n; * floppy accesses go through the track buffer.&n; *&n; * On MIPSes using vdma, this actually means that *all* transfers go thru&n; * the * track buffer since 0x1000000 is always smaller than KSEG0/1.&n; * Actually this needs to be a bit more complicated since the so much different&n; * hardware available with MIPS CPUs ...&n; */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) ((unsigned long)(a)/K_64 != ((unsigned long)(a) + (s) - 1) / K_64)
DECL|macro|EXTRA_FLOPPY_PARAMS
mdefine_line|#define EXTRA_FLOPPY_PARAMS
macro_line|#include &lt;floppy.h&gt;
macro_line|#endif /* _ASM_FLOPPY_H */
eof
