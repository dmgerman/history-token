macro_line|#ifndef _ASM_PPC64_SIGCONTEXT_H
DECL|macro|_ASM_PPC64_SIGCONTEXT_H
mdefine_line|#define _ASM_PPC64_SIGCONTEXT_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|struct|sigcontext_struct
r_struct
id|sigcontext_struct
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
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PPC64_SIGCONTEXT_H */
eof
