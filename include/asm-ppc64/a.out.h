macro_line|#ifndef __PPC64_A_OUT_H__
DECL|macro|__PPC64_A_OUT_H__
mdefine_line|#define __PPC64_A_OUT_H__
macro_line|#include &lt;asm/ppcdebug.h&gt;
multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
multiline_comment|/* 64-bit user address space is less PGDIR_SIZE due to pgd_index() bug. */
DECL|macro|STACK_TOP_USER64
mdefine_line|#define STACK_TOP_USER64 (TASK_SIZE_USER64 - PGDIR_SIZE)
multiline_comment|/* Give 32-bit user space a full 4G address space to live in. */
DECL|macro|STACK_TOP_USER32
mdefine_line|#define STACK_TOP_USER32 (TASK_SIZE_USER32)
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP ((test_thread_flag(TIF_32BIT) || &bslash;&n;&t;&t;(ppcdebugset(PPCDBG_BINFMT_32ADDR))) ? &bslash;&n;&t;&t;STACK_TOP_USER32 : STACK_TOP_USER64)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __PPC64_A_OUT_H__ */
eof
