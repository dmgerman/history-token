multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;errno.h&gt;
DECL|macro|__FRAME_OFFSETS
mdefine_line|#define __FRAME_OFFSETS
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_constants.h&quot;
DECL|function|ptrace_getregs
r_int
id|ptrace_getregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs_out
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_GETREGS
comma
id|pid
comma
l_int|0
comma
id|regs_out
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_setregs
r_int
id|ptrace_setregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_SETREGS
comma
id|pid
comma
l_int|0
comma
id|regs
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_pokeuser
r_void
id|ptrace_pokeuser
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;ptrace_pokeuser&quot;
)paren
suffix:semicolon
)brace
DECL|macro|DS
mdefine_line|#define DS 184
DECL|macro|ES
mdefine_line|#define ES 192
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS     0x2b
DECL|function|arch_enter_kernel
r_void
id|arch_enter_kernel
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
(brace
)brace
DECL|function|arch_leave_kernel
r_void
id|arch_leave_kernel
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
(brace
macro_line|#ifdef UM_USER_CS
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|CS
comma
id|UM_USER_CS
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;POKEUSER CS failed&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|DS
comma
id|__USER_DS
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;POKEUSER DS failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|ES
comma
id|__USER_DS
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;POKEUSER ES failed&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
