macro_line|#ifndef __ASM_SH64_SIGCONTEXT_H
DECL|macro|__ASM_SH64_SIGCONTEXT_H
mdefine_line|#define __ASM_SH64_SIGCONTEXT_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/sigcontext.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
multiline_comment|/* CPU registers */
DECL|member|sc_regs
r_int
r_int
r_int
id|sc_regs
(braket
l_int|63
)braket
suffix:semicolon
DECL|member|sc_tregs
r_int
r_int
r_int
id|sc_tregs
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sc_pc
r_int
r_int
r_int
id|sc_pc
suffix:semicolon
DECL|member|sc_sr
r_int
r_int
r_int
id|sc_sr
suffix:semicolon
multiline_comment|/* FPU registers */
DECL|member|sc_fpregs
r_int
r_int
r_int
id|sc_fpregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_fpscr
r_int
r_int
id|sc_fpscr
suffix:semicolon
DECL|member|sc_fpvalid
r_int
r_int
id|sc_fpvalid
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASM_SH64_SIGCONTEXT_H */
eof
