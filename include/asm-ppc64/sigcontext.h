macro_line|#ifndef _ASM_PPC64_SIGCONTEXT_H
DECL|macro|_ASM_PPC64_SIGCONTEXT_H
mdefine_line|#define _ASM_PPC64_SIGCONTEXT_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|signal
r_int
id|signal
suffix:semicolon
DECL|member|_pad0
r_int
id|_pad0
suffix:semicolon
DECL|member|handler
r_int
r_int
id|handler
suffix:semicolon
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
DECL|member|gp_regs
id|elf_gregset_t
id|gp_regs
suffix:semicolon
DECL|member|fp_regs
id|elf_fpregset_t
id|fp_regs
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PPC64_SIGCONTEXT_H */
eof
