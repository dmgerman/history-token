multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;wait.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;sys/syscall.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;frame_user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|capture_stack
r_static
r_int
id|capture_stack
c_func
(paren
r_int
(paren
op_star
id|child
)paren
(paren
r_void
op_star
id|arg
)paren
comma
r_void
op_star
id|arg
comma
r_void
op_star
id|sp
comma
r_int
r_int
id|top
comma
r_void
op_star
op_star
id|data_out
)paren
(brace
r_int
r_int
id|regs
(braket
id|FRAME_SIZE
)braket
suffix:semicolon
r_int
id|pid
comma
id|status
comma
id|n
comma
id|len
suffix:semicolon
multiline_comment|/* Start the child as a thread */
id|pid
op_assign
id|clone
c_func
(paren
id|child
comma
id|sp
comma
id|CLONE_VM
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
id|printf
c_func
(paren
l_string|&quot;capture_stack : clone failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for it to stop itself and continue it with a SIGUSR1 to force &n;&t; * it into the signal handler.&n;&t; */
id|n
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
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : waitpid failed - errno = %d&bslash;n&quot;
comma
id|errno
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
id|SIGSTOP
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;capture_stack : Expected SIGSTOP, &quot;
l_string|&quot;got status = 0x%x&bslash;n&quot;
comma
id|status
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
id|ptrace
c_func
(paren
id|PTRACE_CONT
comma
id|pid
comma
l_int|0
comma
id|SIGUSR1
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : PTRACE_CONT failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for it to stop itself again and grab its registers again.  &n;&t; * At this point, the handler has stuffed the addresses of&n;&t; * sig, sc, and SA_RESTORER in raw.&n;&t; */
id|n
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
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : waitpid failed - errno = %d&bslash;n&quot;
comma
id|errno
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
id|SIGSTOP
)paren
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;capture_stack : Expected SIGSTOP, &quot;
l_string|&quot;got status = 0x%x&bslash;n&quot;
comma
id|status
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
id|ptrace
c_func
(paren
id|PTRACE_GETREGS
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
id|printf
c_func
(paren
l_string|&quot;capture_stack : PTRACE_GETREGS failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* It has outlived its usefulness, so continue it so it can exit */
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_CONT
comma
id|pid
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : PTRACE_CONT failed - errno = %d&bslash;n&quot;
comma
id|errno
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
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : waitpid failed - errno = %d&bslash;n&quot;
comma
id|errno
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
op_logical_neg
id|WIFSIGNALED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WTERMSIG
c_func
(paren
id|status
)paren
op_ne
l_int|9
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : Expected exit signal 9, &quot;
l_string|&quot;got status = 0x%x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* The frame that we want is the top of the signal stack */
id|len
op_assign
id|top
op_minus
id|PT_SP
c_func
(paren
id|regs
)paren
suffix:semicolon
op_star
id|data_out
op_assign
id|malloc
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|data_out
op_eq
l_int|NULL
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_stack : malloc failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_star
id|data_out
comma
(paren
r_void
op_star
)paren
id|PT_SP
c_func
(paren
id|regs
)paren
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|struct|common_raw
r_struct
id|common_raw
(brace
DECL|member|stack
r_void
op_star
id|stack
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|sig
r_int
r_int
id|sig
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
DECL|member|arch
r_struct
id|arch_frame_data_raw
id|arch
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SA_RESTORER
mdefine_line|#define SA_RESTORER (0x04000000)
DECL|typedef|old_sigset_t
r_typedef
r_int
r_int
id|old_sigset_t
suffix:semicolon
DECL|struct|old_sigaction
r_struct
id|old_sigaction
(brace
DECL|member|handler
id|__sighandler_t
id|handler
suffix:semicolon
DECL|member|sa_mask
id|old_sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_void
(paren
op_star
id|sa_restorer
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|function|child_common
r_static
r_void
id|child_common
c_func
(paren
r_struct
id|common_raw
op_star
id|common
comma
id|sighandler_t
id|handler
comma
r_int
id|restorer
comma
r_int
id|flags
)paren
(brace
id|stack_t
id|ss
op_assign
(paren
(paren
id|stack_t
)paren
(brace
dot
id|ss_sp
op_assign
id|common-&gt;stack
comma
dot
id|ss_flags
op_assign
l_int|0
comma
dot
id|ss_size
op_assign
id|common-&gt;size
)brace
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_TRACEME
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;PTRACE_TRACEME failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sigaltstack
c_func
(paren
op_amp
id|ss
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;sigaltstack failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|kill
c_func
(paren
id|getpid
c_func
(paren
)paren
comma
id|SIGKILL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|restorer
)paren
(brace
r_struct
id|sigaction
id|sa
suffix:semicolon
id|sa.sa_handler
op_assign
id|handler
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|sa.sa_mask
)paren
suffix:semicolon
id|sa.sa_flags
op_assign
id|SA_ONSTACK
op_or
id|flags
suffix:semicolon
id|err
op_assign
id|sigaction
c_func
(paren
id|SIGUSR1
comma
op_amp
id|sa
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|old_sigaction
id|sa
suffix:semicolon
id|sa.handler
op_assign
id|handler
suffix:semicolon
id|sa.sa_mask
op_assign
l_int|0
suffix:semicolon
id|sa.sa_flags
op_assign
(paren
id|SA_ONSTACK
op_or
id|flags
)paren
op_amp
op_complement
id|SA_RESTORER
suffix:semicolon
id|err
op_assign
id|syscall
c_func
(paren
id|__NR_sigaction
comma
id|SIGUSR1
comma
op_amp
id|sa
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;sigaction failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|kill
c_func
(paren
id|getpid
c_func
(paren
)paren
comma
id|SIGKILL
)paren
suffix:semicolon
)brace
id|os_stop_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Changed only during early boot */
DECL|variable|signal_frame_sc
r_struct
id|sc_frame
id|signal_frame_sc
suffix:semicolon
DECL|variable|signal_frame_sc_sr
r_struct
id|sc_frame
id|signal_frame_sc_sr
suffix:semicolon
DECL|struct|sc_frame_raw
r_struct
id|sc_frame_raw
(brace
DECL|member|common
r_struct
id|common_raw
id|common
suffix:semicolon
DECL|member|sc
r_int
r_int
id|sc
suffix:semicolon
DECL|member|restorer
r_int
id|restorer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Changed only during early boot */
DECL|variable|raw_sc
r_static
r_struct
id|sc_frame_raw
op_star
id|raw_sc
op_assign
l_int|NULL
suffix:semicolon
DECL|function|sc_handler
r_static
r_void
id|sc_handler
c_func
(paren
r_int
id|sig
comma
r_struct
id|sigcontext
id|sc
)paren
(brace
id|raw_sc-&gt;common.sig
op_assign
(paren
r_int
r_int
)paren
op_amp
id|sig
suffix:semicolon
id|raw_sc-&gt;common.sr
op_assign
id|frame_restorer
c_func
(paren
)paren
suffix:semicolon
id|raw_sc-&gt;common.sp
op_assign
id|frame_sp
c_func
(paren
)paren
suffix:semicolon
id|raw_sc-&gt;sc
op_assign
(paren
r_int
r_int
)paren
op_amp
id|sc
suffix:semicolon
id|setup_arch_frame_raw
c_func
(paren
op_amp
id|raw_sc-&gt;common.arch
comma
op_amp
id|sc
op_plus
l_int|1
comma
id|raw_sc-&gt;common.sr
)paren
suffix:semicolon
id|os_stop_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|kill
c_func
(paren
id|getpid
c_func
(paren
)paren
comma
id|SIGKILL
)paren
suffix:semicolon
)brace
DECL|function|sc_child
r_static
r_int
id|sc_child
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|raw_sc
op_assign
id|arg
suffix:semicolon
id|child_common
c_func
(paren
op_amp
id|raw_sc-&gt;common
comma
(paren
id|sighandler_t
)paren
id|sc_handler
comma
id|raw_sc-&gt;restorer
comma
l_int|0
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Changed only during early boot */
DECL|variable|signal_frame_si
r_struct
id|si_frame
id|signal_frame_si
suffix:semicolon
DECL|struct|si_frame_raw
r_struct
id|si_frame_raw
(brace
DECL|member|common
r_struct
id|common_raw
id|common
suffix:semicolon
DECL|member|sip
r_int
r_int
id|sip
suffix:semicolon
DECL|member|si
r_int
r_int
id|si
suffix:semicolon
DECL|member|ucp
r_int
r_int
id|ucp
suffix:semicolon
DECL|member|uc
r_int
r_int
id|uc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Changed only during early boot */
DECL|variable|raw_si
r_static
r_struct
id|si_frame_raw
op_star
id|raw_si
op_assign
l_int|NULL
suffix:semicolon
DECL|function|si_handler
r_static
r_void
id|si_handler
c_func
(paren
r_int
id|sig
comma
id|siginfo_t
op_star
id|si
comma
r_struct
id|ucontext
op_star
id|ucontext
)paren
(brace
id|raw_si-&gt;common.sig
op_assign
(paren
r_int
r_int
)paren
op_amp
id|sig
suffix:semicolon
id|raw_si-&gt;common.sr
op_assign
id|frame_restorer
c_func
(paren
)paren
suffix:semicolon
id|raw_si-&gt;common.sp
op_assign
id|frame_sp
c_func
(paren
)paren
suffix:semicolon
id|raw_si-&gt;sip
op_assign
(paren
r_int
r_int
)paren
op_amp
id|si
suffix:semicolon
id|raw_si-&gt;si
op_assign
(paren
r_int
r_int
)paren
id|si
suffix:semicolon
id|raw_si-&gt;ucp
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ucontext
suffix:semicolon
id|raw_si-&gt;uc
op_assign
(paren
r_int
r_int
)paren
id|ucontext
suffix:semicolon
id|setup_arch_frame_raw
c_func
(paren
op_amp
id|raw_si-&gt;common.arch
comma
id|ucontext-&gt;uc_mcontext.fpregs
comma
id|raw_si-&gt;common.sr
)paren
suffix:semicolon
id|os_stop_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|kill
c_func
(paren
id|getpid
c_func
(paren
)paren
comma
id|SIGKILL
)paren
suffix:semicolon
)brace
DECL|function|si_child
r_static
r_int
id|si_child
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|raw_si
op_assign
id|arg
suffix:semicolon
id|child_common
c_func
(paren
op_amp
id|raw_si-&gt;common
comma
(paren
id|sighandler_t
)paren
id|si_handler
comma
l_int|1
comma
id|SA_SIGINFO
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|relative_sr
r_static
r_int
id|relative_sr
c_func
(paren
r_int
r_int
id|sr
comma
r_int
id|sr_index
comma
r_void
op_star
id|stack
comma
r_void
op_star
id|framep
)paren
(brace
r_int
r_int
op_star
id|srp
op_assign
(paren
r_int
r_int
op_star
)paren
id|sr
suffix:semicolon
r_int
r_int
id|frame
op_assign
(paren
r_int
r_int
)paren
id|framep
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|srp
op_amp
id|PAGE_MASK
)paren
op_eq
(paren
r_int
r_int
)paren
id|stack
)paren
(brace
op_star
id|srp
op_sub_assign
id|sr
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|frame
op_plus
id|sr_index
)paren
)paren
op_assign
op_star
id|srp
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|capture_stack_common
r_static
r_int
r_int
id|capture_stack_common
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
r_struct
id|common_raw
op_star
id|common_in
comma
r_void
op_star
id|top
comma
r_void
op_star
id|sigstack
comma
r_int
id|stack_len
comma
r_struct
id|frame_common
op_star
id|common_out
)paren
(brace
r_int
r_int
id|sig_top
op_assign
(paren
r_int
r_int
)paren
id|sigstack
op_plus
id|stack_len
comma
id|base
suffix:semicolon
id|common_in-&gt;stack
op_assign
(paren
r_void
op_star
)paren
id|sigstack
suffix:semicolon
id|common_in-&gt;size
op_assign
id|stack_len
suffix:semicolon
id|common_out-&gt;len
op_assign
id|capture_stack
c_func
(paren
id|proc
comma
id|arg
comma
id|top
comma
id|sig_top
comma
op_amp
id|common_out-&gt;data
)paren
suffix:semicolon
id|base
op_assign
id|sig_top
op_minus
id|common_out-&gt;len
suffix:semicolon
id|common_out-&gt;sig_index
op_assign
id|common_in-&gt;sig
op_minus
id|base
suffix:semicolon
id|common_out-&gt;sp_index
op_assign
id|common_in-&gt;sp
op_minus
id|base
suffix:semicolon
id|common_out-&gt;sr_index
op_assign
id|common_in-&gt;sr
op_minus
id|base
suffix:semicolon
id|common_out-&gt;sr_relative
op_assign
id|relative_sr
c_func
(paren
id|common_in-&gt;sr
comma
id|common_out-&gt;sr_index
comma
id|sigstack
comma
id|common_out-&gt;data
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
DECL|function|capture_signal_stack
r_void
id|capture_signal_stack
c_func
(paren
r_void
)paren
(brace
r_struct
id|sc_frame_raw
id|raw_sc
suffix:semicolon
r_struct
id|si_frame_raw
id|raw_si
suffix:semicolon
r_void
op_star
id|stack
comma
op_star
id|sigstack
suffix:semicolon
r_int
r_int
id|top
comma
id|sig_top
comma
id|base
suffix:semicolon
id|stack
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|PAGE_SIZE
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_PRIVATE
op_or
id|MAP_ANONYMOUS
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|sigstack
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|PAGE_SIZE
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_PRIVATE
op_or
id|MAP_ANONYMOUS
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stack
op_eq
id|MAP_FAILED
)paren
op_logical_or
(paren
id|sigstack
op_eq
id|MAP_FAILED
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_signal_stack : mmap failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|top
op_assign
(paren
r_int
r_int
)paren
id|stack
op_plus
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|sig_top
op_assign
(paren
r_int
r_int
)paren
id|sigstack
op_plus
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* Get the sigcontext, no sigrestorer layout */
id|raw_sc.restorer
op_assign
l_int|0
suffix:semicolon
id|base
op_assign
id|capture_stack_common
c_func
(paren
id|sc_child
comma
op_amp
id|raw_sc
comma
op_amp
id|raw_sc.common
comma
(paren
r_void
op_star
)paren
id|top
comma
id|sigstack
comma
id|PAGE_SIZE
comma
op_amp
id|signal_frame_sc.common
)paren
suffix:semicolon
id|signal_frame_sc.sc_index
op_assign
id|raw_sc.sc
op_minus
id|base
suffix:semicolon
id|setup_arch_frame
c_func
(paren
op_amp
id|raw_sc.common.arch
comma
op_amp
id|signal_frame_sc.common.arch
)paren
suffix:semicolon
multiline_comment|/* Ditto for the sigcontext, sigrestorer layout */
id|raw_sc.restorer
op_assign
l_int|1
suffix:semicolon
id|base
op_assign
id|capture_stack_common
c_func
(paren
id|sc_child
comma
op_amp
id|raw_sc
comma
op_amp
id|raw_sc.common
comma
(paren
r_void
op_star
)paren
id|top
comma
id|sigstack
comma
id|PAGE_SIZE
comma
op_amp
id|signal_frame_sc_sr.common
)paren
suffix:semicolon
id|signal_frame_sc_sr.sc_index
op_assign
id|raw_sc.sc
op_minus
id|base
suffix:semicolon
id|setup_arch_frame
c_func
(paren
op_amp
id|raw_sc.common.arch
comma
op_amp
id|signal_frame_sc_sr.common.arch
)paren
suffix:semicolon
multiline_comment|/* And the siginfo layout */
id|base
op_assign
id|capture_stack_common
c_func
(paren
id|si_child
comma
op_amp
id|raw_si
comma
op_amp
id|raw_si.common
comma
(paren
r_void
op_star
)paren
id|top
comma
id|sigstack
comma
id|PAGE_SIZE
comma
op_amp
id|signal_frame_si.common
)paren
suffix:semicolon
id|signal_frame_si.sip_index
op_assign
id|raw_si.sip
op_minus
id|base
suffix:semicolon
id|signal_frame_si.si_index
op_assign
id|raw_si.si
op_minus
id|base
suffix:semicolon
id|signal_frame_si.ucp_index
op_assign
id|raw_si.ucp
op_minus
id|base
suffix:semicolon
id|signal_frame_si.uc_index
op_assign
id|raw_si.uc
op_minus
id|base
suffix:semicolon
id|setup_arch_frame
c_func
(paren
op_amp
id|raw_si.common.arch
comma
op_amp
id|signal_frame_si.common.arch
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|munmap
c_func
(paren
id|stack
comma
id|PAGE_SIZE
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|munmap
c_func
(paren
id|sigstack
comma
id|PAGE_SIZE
)paren
OL
l_int|0
)paren
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;capture_signal_stack : munmap failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
