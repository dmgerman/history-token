multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
multiline_comment|/* XXX FIXME : Ensure that SIGIO and SIGVTALRM can&squot;t happen immediately&n; * after setting up syscall stack&n; * block SIGVTALRM in any code that&squot;s under wait_for_stop&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/time.h&gt;
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
multiline_comment|/* XXX Bogus */
DECL|macro|ERESTARTSYS
mdefine_line|#define ERESTARTSYS&t;512
DECL|macro|ERESTARTNOINTR
mdefine_line|#define ERESTARTNOINTR&t;513
DECL|macro|ERESTARTNOHAND
mdefine_line|#define ERESTARTNOHAND&t;514
r_struct
(brace
DECL|member|syscall
r_int
id|syscall
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|result
r_int
id|result
suffix:semicolon
DECL|member|start
r_struct
id|timeval
id|start
suffix:semicolon
DECL|member|end
r_struct
id|timeval
id|end
suffix:semicolon
DECL|variable|syscall_record
)brace
id|syscall_record
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|syscall_index
r_int
id|syscall_index
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|kern_timer_on
suffix:semicolon
DECL|function|syscall_handler
r_void
id|syscall_handler
c_func
(paren
r_int
id|sig
comma
r_struct
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
id|lock_syscall
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|syscall_index
op_eq
l_int|1024
)paren
(brace
id|syscall_index
op_assign
l_int|0
suffix:semicolon
)brace
id|index
op_assign
id|syscall_index
suffix:semicolon
id|syscall_index
op_increment
suffix:semicolon
id|unlock_syscall
c_func
(paren
)paren
suffix:semicolon
id|syscall
op_assign
id|regs-&gt;syscall
suffix:semicolon
id|sc
op_assign
id|regs-&gt;sc
suffix:semicolon
id|sc_to_regs
c_func
(paren
id|regs
comma
id|sc
comma
id|syscall
)paren
suffix:semicolon
id|SC_START_SYSCALL
c_func
(paren
id|sc
)paren
suffix:semicolon
id|syscall_record
(braket
id|index
)braket
dot
id|syscall
op_assign
id|syscall
suffix:semicolon
id|syscall_record
(braket
id|index
)braket
dot
id|pid
op_assign
id|current_pid
c_func
(paren
)paren
suffix:semicolon
id|syscall_record
(braket
id|index
)braket
dot
id|result
op_assign
l_int|0xdeadbeef
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|syscall_record
(braket
id|index
)braket
dot
id|start
comma
l_int|NULL
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
id|regs-&gt;sc
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
id|syscall_record
(braket
id|index
)braket
dot
id|result
op_assign
id|result
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|syscall_record
(braket
id|index
)braket
dot
id|end
comma
l_int|NULL
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
r_struct
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