multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999, 2003 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_A_OUT_H
DECL|macro|_ASM_A_OUT_H
mdefine_line|#define _ASM_A_OUT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#endif
DECL|struct|exec
r_struct
id|exec
(brace
DECL|member|a_info
r_int
r_int
id|a_info
suffix:semicolon
multiline_comment|/* Use macros N_MAGIC, etc for access */
DECL|member|a_text
r_int
id|a_text
suffix:semicolon
multiline_comment|/* length of text, in bytes */
DECL|member|a_data
r_int
id|a_data
suffix:semicolon
multiline_comment|/* length of data, in bytes */
DECL|member|a_bss
r_int
id|a_bss
suffix:semicolon
multiline_comment|/* length of uninitialized data area for&n;&t;&t;&t;&t;    file, in bytes */
DECL|member|a_syms
r_int
id|a_syms
suffix:semicolon
multiline_comment|/* length of symbol table data in file,&n;&t;&t;&t;&t;   in bytes */
DECL|member|a_entry
r_int
id|a_entry
suffix:semicolon
multiline_comment|/* start address */
DECL|member|a_trsize
r_int
id|a_trsize
suffix:semicolon
multiline_comment|/* length of relocation info for text, in&n;&t;&t;&t;&t;    bytes */
DECL|member|a_drsize
r_int
id|a_drsize
suffix:semicolon
multiline_comment|/* length of relocation info for data, in bytes */
)brace
suffix:semicolon
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(a)&t;((a).a_trsize)
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(a)&t;((a).a_drsize)
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(a)&t;((a).a_syms)
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;TASK_SIZE
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP&t;(current-&gt;thread.mflags &amp; MF_32BIT_ADDR ? TASK_SIZE32 : TASK_SIZE)
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _ASM_A_OUT_H */
eof
