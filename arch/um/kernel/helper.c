multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;sys/signal.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|struct|helper_data
r_struct
id|helper_data
(brace
DECL|member|pre_exec
r_void
(paren
op_star
id|pre_exec
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|pre_data
r_void
op_star
id|pre_data
suffix:semicolon
DECL|member|argv
r_char
op_star
op_star
id|argv
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Debugging aid, changed only from gdb */
DECL|variable|helper_pause
r_int
id|helper_pause
op_assign
l_int|0
suffix:semicolon
DECL|function|helper_hup
r_static
r_void
id|helper_hup
c_func
(paren
r_int
id|sig
)paren
(brace
)brace
DECL|function|helper_child
r_static
r_int
id|helper_child
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|helper_data
op_star
id|data
op_assign
id|arg
suffix:semicolon
r_char
op_star
op_star
id|argv
op_assign
id|data-&gt;argv
suffix:semicolon
r_if
c_cond
(paren
id|helper_pause
)paren
(brace
id|signal
c_func
(paren
id|SIGHUP
comma
id|helper_hup
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;pre_exec
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
id|data-&gt;pre_exec
)paren
(paren
id|data-&gt;pre_data
)paren
suffix:semicolon
)brace
id|execvp
c_func
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;execvp of &squot;%s&squot; failed - errno = %d&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
comma
id|errno
)paren
suffix:semicolon
id|write
c_func
(paren
id|data-&gt;fd
comma
op_amp
id|errno
comma
r_sizeof
(paren
id|errno
)paren
)paren
suffix:semicolon
id|_exit
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|run_helper
r_int
id|run_helper
c_func
(paren
r_void
(paren
op_star
id|pre_exec
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|pre_data
comma
r_char
op_star
op_star
id|argv
comma
r_int
r_int
op_star
id|stack_out
)paren
(brace
r_struct
id|helper_data
id|data
suffix:semicolon
r_int
r_int
id|stack
comma
id|sp
suffix:semicolon
r_int
id|pid
comma
id|fds
(braket
l_int|2
)braket
comma
id|err
comma
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stack_out
op_ne
l_int|NULL
)paren
op_logical_and
(paren
op_star
id|stack_out
op_ne
l_int|0
)paren
)paren
(brace
id|stack
op_assign
op_star
id|stack_out
suffix:semicolon
)brace
r_else
id|stack
op_assign
id|alloc_stack
c_func
(paren
l_int|0
comma
id|um_in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stack
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|err
op_assign
id|os_pipe
c_func
(paren
id|fds
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper : pipe failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fcntl
c_func
(paren
id|fds
(braket
l_int|1
)braket
comma
id|F_SETFD
comma
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper : setting FD_CLOEXEC failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|sp
op_assign
id|stack
op_plus
id|page_size
c_func
(paren
)paren
op_minus
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|data.pre_exec
op_assign
id|pre_exec
suffix:semicolon
id|data.pre_data
op_assign
id|pre_data
suffix:semicolon
id|data.argv
op_assign
id|argv
suffix:semicolon
id|data.fd
op_assign
id|fds
(braket
l_int|1
)braket
suffix:semicolon
id|pid
op_assign
id|clone
c_func
(paren
id|helper_child
comma
(paren
r_void
op_star
)paren
id|sp
comma
id|CLONE_VM
op_or
id|SIGCHLD
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper : clone failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|close
c_func
(paren
id|fds
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|n
op_assign
id|read
c_func
(paren
id|fds
(braket
l_int|0
)braket
comma
op_amp
id|err
comma
r_sizeof
(paren
id|err
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper : read on pipe failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ne
l_int|0
)paren
(brace
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|pid
op_assign
op_minus
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stack_out
op_eq
l_int|NULL
)paren
(brace
id|free_stack
c_func
(paren
id|stack
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
op_star
id|stack_out
op_assign
id|stack
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
DECL|function|run_helper_thread
r_int
id|run_helper_thread
c_func
(paren
r_int
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
comma
r_int
r_int
op_star
id|stack_out
comma
r_int
id|stack_order
)paren
(brace
r_int
r_int
id|stack
comma
id|sp
suffix:semicolon
r_int
id|pid
comma
id|status
suffix:semicolon
id|stack
op_assign
id|alloc_stack
c_func
(paren
id|stack_order
comma
id|um_in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stack
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sp
op_assign
id|stack
op_plus
(paren
id|page_size
c_func
(paren
)paren
op_lshift
id|stack_order
)paren
op_minus
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|pid
op_assign
id|clone
c_func
(paren
id|proc
comma
(paren
r_void
op_star
)paren
id|sp
comma
id|flags
op_or
id|SIGCHLD
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper_thread : clone failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stack_out
op_eq
l_int|NULL
)paren
(brace
id|pid
op_assign
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper_thread - wait failed, errno = %d&bslash;n&quot;
comma
id|pid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WEXITSTATUS
c_func
(paren
id|status
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;run_helper_thread - thread returned status &quot;
l_string|&quot;0x%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
id|free_stack
c_func
(paren
id|stack
comma
id|stack_order
)paren
suffix:semicolon
)brace
r_else
op_star
id|stack_out
op_assign
id|stack
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
DECL|function|helper_wait
r_int
id|helper_wait
c_func
(paren
r_int
id|pid
comma
r_int
id|block
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
id|WNOHANG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;helper_wait : waitpid failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
