multiline_comment|/* $Id: sigcontext.h,v 1.1 2000/07/10 16:32:31 bjornw Exp $ */
macro_line|#ifndef _ASM_CRIS_SIGCONTEXT_H
DECL|macro|_ASM_CRIS_SIGCONTEXT_H
mdefine_line|#define _ASM_CRIS_SIGCONTEXT_H
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/* This struct is saved by setup_frame in signal.c, to keep the current context while&n;   a signal handler is executed. It&squot;s restored by sys_sigreturn.&n;   &n;   To keep things simple, we use pt_regs here even though normally you just specify&n;   the list of regs to save. Then we can use copy_from_user on the entire regs instead&n;   of a bunch of get_user&squot;s as well...&n;&n;*/
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|regs
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/* needs to be first */
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* usp before stacking this gunk on it */
)brace
suffix:semicolon
macro_line|#endif
eof
