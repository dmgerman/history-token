multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
DECL|function|do_exec
r_void
id|do_exec
c_func
(paren
r_int
id|old_pid
comma
r_int
id|new_pid
)paren
(brace
r_int
r_int
id|regs
(braket
id|FRAME_SIZE
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptrace
c_func
(paren
id|PTRACE_ATTACH
comma
id|new_pid
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|ptrace
c_func
(paren
id|PTRACE_CONT
comma
id|new_pid
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|waitpid
c_func
(paren
id|new_pid
comma
l_int|0
comma
id|WUNTRACED
)paren
OL
l_int|0
)paren
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;do_exec failed to attach proc - errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptrace_getregs
c_func
(paren
id|old_pid
comma
id|regs
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;do_exec failed to get registers - errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|kill
c_func
(paren
id|old_pid
comma
id|SIGKILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptrace_setregs
c_func
(paren
id|new_pid
comma
id|regs
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;do_exec failed to start new proc - errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
