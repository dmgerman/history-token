multiline_comment|/* $Id: a.out.h,v 1.1 1999/08/18 23:37:50 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_A_OUT_H
DECL|macro|_ASM_A_OUT_H
mdefine_line|#define _ASM_A_OUT_H
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
multiline_comment|/* length of uninitialized data area for file, in bytes */
DECL|member|a_syms
r_int
id|a_syms
suffix:semicolon
multiline_comment|/* length of symbol table data in file, in bytes */
DECL|member|a_entry
r_int
id|a_entry
suffix:semicolon
multiline_comment|/* start address */
DECL|member|a_trsize
r_int
id|a_trsize
suffix:semicolon
multiline_comment|/* length of relocation info for text, in bytes */
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
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP (current-&gt;thread.mflags &amp; MF_32BIT ? 0x7fff8000 : TASK_SIZE)
macro_line|#endif
macro_line|#endif /* _ASM_A_OUT_H */
eof
