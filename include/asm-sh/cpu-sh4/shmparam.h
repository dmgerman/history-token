multiline_comment|/*&n; * include/asm-sh/cpu-sh4/shmparam.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH4_SHMPARAM_H
DECL|macro|__ASM_CPU_SH4_SHMPARAM_H
mdefine_line|#define __ASM_CPU_SH4_SHMPARAM_H
multiline_comment|/*&n; * SH-4 has D-cache alias issue&n; */
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA (PAGE_SIZE*4)&t;&t; /* attach addr a multiple of this */
macro_line|#endif /* __ASM_CPU_SH4_SHMPARAM_H */
eof
