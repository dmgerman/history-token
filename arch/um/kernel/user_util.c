multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;limits.h&gt;
macro_line|#include &lt;sys/mman.h&gt; 
macro_line|#include &lt;setjmp.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;sys/utsname.h&gt;
macro_line|#include &lt;sys/param.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &quot;asm/types.h&quot;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;wait.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;helper.h&quot;
macro_line|#include &quot;uml-config.h&quot;
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE _POSIX_ARG_MAX
multiline_comment|/* Changed in linux_main and setup_arch, which run before SMP is started */
DECL|variable|command_line
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|function|add_arg
r_void
id|add_arg
c_func
(paren
r_char
op_star
id|cmd_line
comma
r_char
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cmd_line
)paren
op_plus
id|strlen
c_func
(paren
id|arg
)paren
op_plus
l_int|1
OG
id|COMMAND_LINE_SIZE
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;add_arg: Too much command line!&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|cmd_line
)paren
OG
l_int|0
)paren
(brace
id|strcat
c_func
(paren
id|cmd_line
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|strcat
c_func
(paren
id|cmd_line
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|stop
r_void
id|stop
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|sleep
c_func
(paren
l_int|1000000
)paren
suffix:semicolon
)brace
)brace
DECL|function|stack_protections
r_void
id|stack_protections
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_int
id|prot
op_assign
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
suffix:semicolon
r_if
c_cond
(paren
id|mprotect
c_func
(paren
(paren
r_void
op_star
)paren
id|address
comma
id|page_size
c_func
(paren
)paren
comma
id|prot
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;protecting stack failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|task_protections
r_void
id|task_protections
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|guard
op_assign
id|address
op_plus
id|page_size
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|stack
op_assign
id|guard
op_plus
id|page_size
c_func
(paren
)paren
suffix:semicolon
r_int
id|prot
op_assign
l_int|0
comma
id|pages
suffix:semicolon
macro_line|#ifdef notdef
r_if
c_cond
(paren
id|mprotect
c_func
(paren
(paren
r_void
op_star
)paren
id|stack
comma
id|page_size
c_func
(paren
)paren
comma
id|prot
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;protecting guard page failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
macro_line|#endif
id|pages
op_assign
(paren
l_int|1
op_lshift
id|UML_CONFIG_KERNEL_STACK_ORDER
)paren
op_minus
l_int|2
suffix:semicolon
id|prot
op_assign
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
suffix:semicolon
r_if
c_cond
(paren
id|mprotect
c_func
(paren
(paren
r_void
op_star
)paren
id|stack
comma
id|pages
op_star
id|page_size
c_func
(paren
)paren
comma
id|prot
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;protecting stack failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|wait_for_stop
r_int
id|wait_for_stop
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
comma
r_int
id|cont_type
comma
r_void
op_star
id|relay
)paren
(brace
id|sigset_t
op_star
id|relay_signals
op_assign
id|relay
suffix:semicolon
r_int
id|status
comma
id|ret
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|ret
op_assign
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
id|WUNTRACED
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
OL
l_int|0
)paren
op_logical_or
op_logical_neg
id|WIFSTOPPED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_ne
id|sig
)paren
)paren
(brace
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
l_string|&quot;wait failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;process %d exited with status %d&bslash;n&quot;
comma
id|pid
comma
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;process %d exited with signal %d&bslash;n&quot;
comma
id|pid
comma
id|WTERMSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGVTALRM
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGALRM
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGIO
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGPROF
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGCHLD
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGWINCH
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGINT
)paren
)paren
(brace
id|ptrace
c_func
(paren
id|cont_type
comma
id|pid
comma
l_int|0
comma
id|WSTOPSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|relay_signals
op_ne
l_int|NULL
)paren
op_logical_and
id|sigismember
c_func
(paren
id|relay_signals
comma
id|WSTOPSIG
c_func
(paren
id|status
)paren
)paren
)paren
(brace
id|ptrace
c_func
(paren
id|cont_type
comma
id|pid
comma
l_int|0
comma
id|WSTOPSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;process %d stopped with signal %d&bslash;n&quot;
comma
id|pid
comma
id|WSTOPSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;wait_for_stop failed to wait for %d to stop &quot;
l_string|&quot;with %d&bslash;n&quot;
comma
id|pid
comma
id|sig
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
)brace
DECL|function|raw
r_int
id|raw
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|termios
id|tt
suffix:semicolon
r_int
id|err
suffix:semicolon
id|CATCH_EINTR
c_func
(paren
id|err
op_assign
id|tcgetattr
c_func
(paren
id|fd
comma
op_amp
id|tt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tcgetattr failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
id|cfmakeraw
c_func
(paren
op_amp
id|tt
)paren
suffix:semicolon
id|CATCH_EINTR
c_func
(paren
id|err
op_assign
id|tcsetattr
c_func
(paren
id|fd
comma
id|TCSADRAIN
comma
op_amp
id|tt
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tcsetattr failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
id|errno
suffix:semicolon
)brace
multiline_comment|/* XXX tcsetattr could have applied only some changes&n;&t; * (and cfmakeraw() is a set of changes) */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_machinename
r_void
id|setup_machinename
c_func
(paren
r_char
op_star
id|machine_out
)paren
(brace
r_struct
id|utsname
id|host
suffix:semicolon
id|uname
c_func
(paren
op_amp
id|host
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|machine_out
comma
id|host.machine
)paren
suffix:semicolon
)brace
DECL|variable|host_info
r_char
id|host_info
(braket
(paren
id|_UTSNAME_LENGTH
op_plus
l_int|1
)paren
op_star
l_int|4
op_plus
id|_UTSNAME_NODENAME_LENGTH
op_plus
l_int|1
)braket
suffix:semicolon
DECL|function|setup_hostinfo
r_void
id|setup_hostinfo
c_func
(paren
r_void
)paren
(brace
r_struct
id|utsname
id|host
suffix:semicolon
id|uname
c_func
(paren
op_amp
id|host
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|host_info
comma
l_string|&quot;%s %s %s %s %s&quot;
comma
id|host.sysname
comma
id|host.nodename
comma
id|host.release
comma
id|host.version
comma
id|host.machine
)paren
suffix:semicolon
)brace
DECL|function|setjmp_wrapper
r_int
id|setjmp_wrapper
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
comma
r_void
op_star
)paren
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
id|sigjmp_buf
id|buf
suffix:semicolon
r_int
id|n
suffix:semicolon
id|n
op_assign
id|sigsetjmp
c_func
(paren
id|buf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
id|va_start
c_func
(paren
id|args
comma
id|proc
)paren
suffix:semicolon
(paren
op_star
id|proc
)paren
(paren
op_amp
id|buf
comma
op_amp
id|args
)paren
suffix:semicolon
)brace
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
