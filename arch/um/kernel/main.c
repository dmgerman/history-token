multiline_comment|/*&n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/resource.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/user.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;mode.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;uml-config.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;os.h&quot;
multiline_comment|/* Set in set_stklim, which is called from main and __wrap_malloc.&n; * __wrap_malloc only calls it if main hasn&squot;t started.&n; */
DECL|variable|stacksizelim
r_int
r_int
id|stacksizelim
suffix:semicolon
multiline_comment|/* Set in main */
DECL|variable|linux_prog
r_char
op_star
id|linux_prog
suffix:semicolon
DECL|macro|PGD_BOUND
mdefine_line|#define PGD_BOUND (4 * 1024 * 1024)
DECL|macro|STACKSIZE
mdefine_line|#define STACKSIZE (8 * 1024 * 1024)
DECL|macro|THREAD_NAME_LEN
mdefine_line|#define THREAD_NAME_LEN (256)
DECL|function|set_stklim
r_static
r_void
id|set_stklim
c_func
(paren
r_void
)paren
(brace
r_struct
id|rlimit
id|lim
suffix:semicolon
r_if
c_cond
(paren
id|getrlimit
c_func
(paren
id|RLIMIT_STACK
comma
op_amp
id|lim
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;getrlimit&quot;
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
(paren
id|lim.rlim_cur
op_eq
id|RLIM_INFINITY
)paren
op_logical_or
(paren
id|lim.rlim_cur
OG
id|STACKSIZE
)paren
)paren
(brace
id|lim.rlim_cur
op_assign
id|STACKSIZE
suffix:semicolon
r_if
c_cond
(paren
id|setrlimit
c_func
(paren
id|RLIMIT_STACK
comma
op_amp
id|lim
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;setrlimit&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|stacksizelim
op_assign
(paren
id|lim.rlim_cur
op_plus
id|PGD_BOUND
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|PGD_BOUND
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|do_uml_initcalls
r_static
id|__init
r_void
id|do_uml_initcalls
c_func
(paren
r_void
)paren
(brace
id|initcall_t
op_star
id|call
suffix:semicolon
id|call
op_assign
op_amp
id|__uml_initcall_start
suffix:semicolon
r_while
c_loop
(paren
id|call
OL
op_amp
id|__uml_initcall_end
)paren
(brace
suffix:semicolon
(paren
op_star
id|call
)paren
(paren
)paren
suffix:semicolon
id|call
op_increment
suffix:semicolon
)brace
)brace
DECL|function|last_ditch_exit
r_static
r_void
id|last_ditch_exit
c_func
(paren
r_int
id|sig
)paren
(brace
id|CHOOSE_MODE
c_func
(paren
id|kmalloc_ok
op_assign
l_int|0
comma
(paren
r_void
)paren
l_int|0
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGINT
comma
id|SIG_DFL
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGTERM
comma
id|SIG_DFL
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGHUP
comma
id|SIG_DFL
)paren
suffix:semicolon
id|uml_cleanup
c_func
(paren
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_extern
r_int
id|uml_exitcode
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
r_char
op_star
op_star
id|new_argv
suffix:semicolon
id|sigset_t
id|mask
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
multiline_comment|/* Enable all signals except SIGIO - in some environments, we can&n;&t; * enter with some signals blocked&n;&t; */
id|sigemptyset
c_func
(paren
op_amp
id|mask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|mask
comma
id|SIGIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigprocmask
c_func
(paren
id|SIG_SETMASK
comma
op_amp
id|mask
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;sigprocmask&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef UML_CONFIG_MODE_TT
multiline_comment|/* Allocate memory for thread command lines */
r_if
c_cond
(paren
id|argc
OL
l_int|2
op_logical_or
id|strlen
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
OL
id|THREAD_NAME_LEN
op_minus
l_int|1
)paren
(brace
r_char
id|padding
(braket
id|THREAD_NAME_LEN
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|THREAD_NAME_LEN
op_minus
l_int|2
)braket
op_assign
l_char|&squot; &squot;
comma
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
id|new_argv
op_assign
id|malloc
c_func
(paren
(paren
id|argc
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_argv
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;Allocating extended argv&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|new_argv
(braket
l_int|0
)braket
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|new_argv
(braket
l_int|1
)braket
op_assign
id|padding
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
op_le
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
id|new_argv
(braket
id|i
)braket
op_assign
id|argv
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|new_argv
(braket
id|argc
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|execvp
c_func
(paren
id|new_argv
(braket
l_int|0
)braket
comma
id|new_argv
)paren
suffix:semicolon
id|perror
c_func
(paren
l_string|&quot;execing with extended args&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
id|linux_prog
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
id|set_stklim
c_func
(paren
)paren
suffix:semicolon
id|new_argv
op_assign
id|malloc
c_func
(paren
(paren
id|argc
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_argv
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;Mallocing argv&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
id|new_argv
(braket
id|i
)braket
op_assign
id|strdup
c_func
(paren
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_argv
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;Mallocing an arg&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|new_argv
(braket
id|argc
)braket
op_assign
l_int|NULL
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGINT
comma
id|last_ditch_exit
comma
id|SA_ONESHOT
op_or
id|SA_NODEFER
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGTERM
comma
id|last_ditch_exit
comma
id|SA_ONESHOT
op_or
id|SA_NODEFER
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGHUP
comma
id|last_ditch_exit
comma
id|SA_ONESHOT
op_or
id|SA_NODEFER
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|do_uml_initcalls
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|linux_main
c_func
(paren
id|argc
comma
id|argv
)paren
suffix:semicolon
multiline_comment|/* Reboot */
r_if
c_cond
(paren
id|ret
)paren
(brace
r_int
id|err
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Let any pending signals fire, then disable them.  This&n;&t;&t; * ensures that they won&squot;t be delivered after the exec, when&n;&t;&t; * they are definitely not expected.&n;&t;&t; */
id|unblock_signals
c_func
(paren
)paren
suffix:semicolon
id|disable_timer
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|deactivate_all_fds
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;deactivate_all_fds failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|execvp
c_func
(paren
id|new_argv
(braket
l_int|0
)braket
comma
id|new_argv
)paren
suffix:semicolon
id|perror
c_func
(paren
l_string|&quot;Failed to exec kernel&quot;
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|uml_exitcode
suffix:semicolon
)brace
DECL|macro|CAN_KMALLOC
mdefine_line|#define CAN_KMALLOC() &bslash;&n;&t;(kmalloc_ok &amp;&amp; CHOOSE_MODE((os_getpid() != tracing_pid), 1))
r_extern
r_void
op_star
id|__real_malloc
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|function|__wrap_malloc
r_void
op_star
id|__wrap_malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CAN_KMALLOC
c_func
(paren
)paren
)paren
(brace
r_return
id|__real_malloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|size
op_le
id|PAGE_SIZE
)paren
(brace
multiline_comment|/* finding contiguos pages can be hard*/
id|ret
op_assign
id|um_kmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
r_else
id|ret
op_assign
id|um_vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/* glibc people insist that if malloc fails, errno should be&n;&t; * set by malloc as well. So we do.&n;&t; */
r_if
c_cond
(paren
id|ret
op_eq
l_int|NULL
)paren
(brace
id|errno
op_assign
id|ENOMEM
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|__wrap_calloc
r_void
op_star
id|__wrap_calloc
c_func
(paren
r_int
id|n
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|ptr
op_assign
id|__wrap_malloc
c_func
(paren
id|n
op_star
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|n
op_star
id|size
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
r_extern
r_void
id|__real_free
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|high_physmem
suffix:semicolon
DECL|function|__wrap_free
r_void
id|__wrap_free
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
multiline_comment|/* We need to know how the allocation happened, so it can be correctly&n;&t; * freed.  This is done by seeing what region of memory the pointer is&n;&t; * in -&n;&t; * &t;physical memory - kmalloc/kfree&n;&t; *&t;kernel virtual memory - vmalloc/vfree&n;&t; * &t;anywhere else - malloc/free&n;&t; * If kmalloc is not yet possible, then the kernel memory regions&n;&t; * may not be set up yet, and the variables not initialized.  So,&n;&t; * free is called.&n;&t; *&n;&t; * CAN_KMALLOC is checked because it would be bad to free a buffer&n;&t; * with kmalloc/vmalloc after they have been turned off during&n;&t; * shutdown.&n;&t; */
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|uml_physmem
)paren
op_logical_and
(paren
id|addr
OL
id|high_physmem
)paren
)paren
(brace
r_if
c_cond
(paren
id|CAN_KMALLOC
c_func
(paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|start_vm
)paren
op_logical_and
(paren
id|addr
OL
id|end_vm
)paren
)paren
(brace
r_if
c_cond
(paren
id|CAN_KMALLOC
c_func
(paren
)paren
)paren
(brace
id|vfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
)brace
r_else
id|__real_free
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
