multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;task.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;syscall_user.h&quot;
macro_line|#include &quot;tt.h&quot;
multiline_comment|/* XXX Bogus */
DECL|macro|ERESTARTSYS
mdefine_line|#define ERESTARTSYS&t;512
DECL|macro|ERESTARTNOINTR
mdefine_line|#define ERESTARTNOINTR&t;513
DECL|macro|ERESTARTNOHAND
mdefine_line|#define ERESTARTNOHAND&t;514
DECL|function|syscall_handler_tt
r_void
id|syscall_handler_tt
c_func
(paren
r_int
id|sig
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_void
op_star
id|sc
suffix:semicolon
r_int
id|result
suffix:semicolon
r_int
id|index
comma
id|syscall
suffix:semicolon
id|syscall
op_assign
id|UPT_SYSCALL_NR
c_func
(paren
id|regs
)paren
suffix:semicolon
id|sc
op_assign
id|UPT_SC
c_func
(paren
id|regs
)paren
suffix:semicolon
id|SC_START_SYSCALL
c_func
(paren
id|sc
)paren
suffix:semicolon
id|index
op_assign
id|record_syscall_start
c_func
(paren
id|syscall
)paren
suffix:semicolon
id|syscall_trace
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|execute_syscall
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* regs-&gt;sc may have changed while the system call ran (there may&n;&t; * have been an interrupt or segfault), so it needs to be refreshed.&n;&t; */
id|UPT_SC
c_func
(paren
id|regs
)paren
op_assign
id|sc
suffix:semicolon
id|SC_SET_SYSCALL_RETURN
c_func
(paren
id|sc
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_eq
op_minus
id|ERESTARTNOHAND
)paren
op_logical_or
(paren
id|result
op_eq
op_minus
id|ERESTARTSYS
)paren
op_logical_or
(paren
id|result
op_eq
op_minus
id|ERESTARTNOINTR
)paren
)paren
(brace
id|do_signal
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
id|syscall_trace
c_func
(paren
)paren
suffix:semicolon
id|record_syscall_end
c_func
(paren
id|index
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|do_syscall
r_int
id|do_syscall
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
r_int
r_int
id|proc_regs
(braket
id|FRAME_SIZE
)braket
suffix:semicolon
r_union
id|uml_pt_regs
op_star
id|regs
suffix:semicolon
r_int
id|syscall
suffix:semicolon
r_if
c_cond
(paren
id|ptrace_getregs
c_func
(paren
id|pid
comma
id|proc_regs
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;Couldn&squot;t read registers&quot;
)paren
suffix:semicolon
)brace
id|syscall
op_assign
id|PT_SYSCALL_NR
c_func
(paren
id|proc_regs
)paren
suffix:semicolon
id|regs
op_assign
id|TASK_REGS
c_func
(paren
id|task
)paren
suffix:semicolon
id|UPT_SYSCALL_NR
c_func
(paren
id|regs
)paren
op_assign
id|syscall
suffix:semicolon
r_if
c_cond
(paren
id|syscall
OL
l_int|1
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|syscall
op_ne
id|__NR_sigreturn
)paren
op_logical_and
(paren
(paren
r_int
r_int
op_star
)paren
id|PT_IP
c_func
(paren
id|proc_regs
)paren
op_ge
op_amp
id|_stext
)paren
op_logical_and
(paren
(paren
r_int
r_int
op_star
)paren
id|PT_IP
c_func
(paren
id|proc_regs
)paren
op_le
op_amp
id|_etext
)paren
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;I&squot;m tracing myself and I can&squot;t get out&quot;
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
id|PT_SYSCALL_NR_OFFSET
comma
id|__NR_getpid
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;do_syscall : Nullifying syscall failed, &quot;
l_string|&quot;errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
