multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;setjmp.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;frame_user.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;task.h&quot;
macro_line|#include &quot;mode.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|kill_child_dead
r_void
id|kill_child_dead
c_func
(paren
r_int
id|pid
)paren
(brace
id|kill
c_func
(paren
id|pid
comma
id|SIGKILL
)paren
suffix:semicolon
id|kill
c_func
(paren
id|pid
comma
id|SIGCONT
)paren
suffix:semicolon
r_while
c_loop
(paren
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
l_int|0
)paren
OG
l_int|0
)paren
(brace
id|kill
c_func
(paren
id|pid
comma
id|SIGCONT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Unlocked - don&squot;t care if this is a bit off */
DECL|variable|nsegfaults
r_int
id|nsegfaults
op_assign
l_int|0
suffix:semicolon
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|is_write
r_int
id|is_write
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
DECL|member|is_user
r_int
id|is_user
suffix:semicolon
DECL|variable|segfault_record
)brace
id|segfault_record
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|segv_handler
r_void
id|segv_handler
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
r_int
id|index
comma
id|max
suffix:semicolon
r_if
c_cond
(paren
id|UPT_IS_USER
c_func
(paren
id|regs
)paren
op_logical_and
op_logical_neg
id|UPT_SEGV_IS_FIXABLE
c_func
(paren
id|regs
)paren
)paren
(brace
id|bad_segv
c_func
(paren
id|UPT_FAULT_ADDR
c_func
(paren
id|regs
)paren
comma
id|UPT_IP
c_func
(paren
id|regs
)paren
comma
id|UPT_FAULT_WRITE
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|max
op_assign
r_sizeof
(paren
id|segfault_record
)paren
op_div
r_sizeof
(paren
id|segfault_record
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|index
op_assign
id|next_trap_index
c_func
(paren
id|max
)paren
suffix:semicolon
id|nsegfaults
op_increment
suffix:semicolon
id|segfault_record
(braket
id|index
)braket
dot
id|address
op_assign
id|UPT_FAULT_ADDR
c_func
(paren
id|regs
)paren
suffix:semicolon
id|segfault_record
(braket
id|index
)braket
dot
id|pid
op_assign
id|os_getpid
c_func
(paren
)paren
suffix:semicolon
id|segfault_record
(braket
id|index
)braket
dot
id|is_write
op_assign
id|UPT_FAULT_WRITE
c_func
(paren
id|regs
)paren
suffix:semicolon
id|segfault_record
(braket
id|index
)braket
dot
id|sp
op_assign
id|UPT_SP
c_func
(paren
id|regs
)paren
suffix:semicolon
id|segfault_record
(braket
id|index
)braket
dot
id|is_user
op_assign
id|UPT_IS_USER
c_func
(paren
id|regs
)paren
suffix:semicolon
id|segv
c_func
(paren
id|UPT_FAULT_ADDR
c_func
(paren
id|regs
)paren
comma
id|UPT_IP
c_func
(paren
id|regs
)paren
comma
id|UPT_FAULT_WRITE
c_func
(paren
id|regs
)paren
comma
id|UPT_IS_USER
c_func
(paren
id|regs
)paren
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|usr2_handler
r_void
id|usr2_handler
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
id|CHOOSE_MODE
c_func
(paren
id|syscall_handler_tt
c_func
(paren
id|sig
comma
id|regs
)paren
comma
(paren
r_void
)paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|sig_info
r_struct
id|signal_info
id|sig_info
(braket
)braket
op_assign
(brace
(braket
id|SIGTRAP
)braket
(brace
dot
id|handler
op_assign
id|relay_signal
comma
dot
id|is_irq
op_assign
l_int|0
)brace
comma
(braket
id|SIGFPE
)braket
(brace
dot
id|handler
op_assign
id|relay_signal
comma
dot
id|is_irq
op_assign
l_int|0
)brace
comma
(braket
id|SIGILL
)braket
(brace
dot
id|handler
op_assign
id|relay_signal
comma
dot
id|is_irq
op_assign
l_int|0
)brace
comma
(braket
id|SIGWINCH
)braket
(brace
dot
id|handler
op_assign
id|winch
comma
dot
id|is_irq
op_assign
l_int|1
)brace
comma
(braket
id|SIGBUS
)braket
(brace
dot
id|handler
op_assign
id|bus_handler
comma
dot
id|is_irq
op_assign
l_int|0
)brace
comma
(braket
id|SIGSEGV
)braket
(brace
dot
id|handler
op_assign
id|segv_handler
comma
dot
id|is_irq
op_assign
l_int|0
)brace
comma
(braket
id|SIGIO
)braket
(brace
dot
id|handler
op_assign
id|sigio_handler
comma
dot
id|is_irq
op_assign
l_int|1
)brace
comma
(braket
id|SIGVTALRM
)braket
(brace
dot
id|handler
op_assign
id|timer_handler
comma
dot
id|is_irq
op_assign
l_int|1
)brace
comma
(braket
id|SIGALRM
)braket
(brace
dot
id|handler
op_assign
id|timer_handler
comma
dot
id|is_irq
op_assign
l_int|1
)brace
comma
(braket
id|SIGUSR2
)braket
(brace
dot
id|handler
op_assign
id|usr2_handler
comma
dot
id|is_irq
op_assign
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|function|sig_handler
r_void
id|sig_handler
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
id|CHOOSE_MODE_PROC
c_func
(paren
id|sig_handler_common_tt
comma
id|sig_handler_common_skas
comma
id|sig
comma
op_amp
id|sc
)paren
suffix:semicolon
)brace
r_extern
r_int
id|timer_irq_inited
suffix:semicolon
DECL|function|alarm_handler
r_void
id|alarm_handler
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
r_if
c_cond
(paren
op_logical_neg
id|timer_irq_inited
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sig
op_eq
id|SIGALRM
)paren
(brace
id|switch_timers
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|CHOOSE_MODE_PROC
c_func
(paren
id|sig_handler_common_tt
comma
id|sig_handler_common_skas
comma
id|sig
comma
op_amp
id|sc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGALRM
)paren
(brace
id|switch_timers
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_longjmp
r_void
id|do_longjmp
c_func
(paren
r_void
op_star
id|b
comma
r_int
id|val
)paren
(brace
id|jmp_buf
op_star
id|buf
op_assign
id|b
suffix:semicolon
id|siglongjmp
c_func
(paren
op_star
id|buf
comma
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
