multiline_comment|/*&n; * include/asm-v850/sigcontext.h -- Signal contexts&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SIGCONTEXT_H__
DECL|macro|__V850_SIGCONTEXT_H__
mdefine_line|#define __V850_SIGCONTEXT_H__
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|regs
r_struct
id|pt_regs
id|regs
suffix:semicolon
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __V850_SIGCONTEXT_H__ */
eof
