macro_line|#ifndef _ASM_IA64_A_OUT_H
DECL|macro|_ASM_IA64_A_OUT_H
mdefine_line|#define _ASM_IA64_A_OUT_H
multiline_comment|/*&n; * No a.out format has been (or should be) defined so this file is&n; * just a dummy that allows us to get binfmt_elf compiled.  It&n; * probably would be better to clean up binfmt_elf.c so it does not&n; * necessarily depend on there being a.out support.&n; *&n; * Modified 1998-2002&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;, Hewlett-Packard Co.&n; */
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|exec
r_struct
id|exec
(brace
DECL|member|a_info
r_int
r_int
id|a_info
suffix:semicolon
DECL|member|a_text
r_int
r_int
id|a_text
suffix:semicolon
DECL|member|a_data
r_int
r_int
id|a_data
suffix:semicolon
DECL|member|a_bss
r_int
r_int
id|a_bss
suffix:semicolon
DECL|member|a_entry
r_int
r_int
id|a_entry
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(x)&t;0
DECL|macro|N_DATADDR
mdefine_line|#define N_DATADDR(x)&t;0
DECL|macro|N_BSSADDR
mdefine_line|#define N_BSSADDR(x)&t;0
DECL|macro|N_DRSIZE
mdefine_line|#define N_DRSIZE(x)&t;0
DECL|macro|N_TRSIZE
mdefine_line|#define N_TRSIZE(x)&t;0
DECL|macro|N_SYMSIZE
mdefine_line|#define N_SYMSIZE(x)&t;0
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(x)&t;0
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/ustack.h&gt;
macro_line|#endif
macro_line|#endif /* _ASM_IA64_A_OUT_H */
eof
