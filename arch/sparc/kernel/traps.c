multiline_comment|/* $Id: traps.c,v 1.64 2000/09/03 15:00:49 anton Exp $&n; * arch/sparc/kernel/traps.c&n; *&n; * Copyright 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright 2000 Jakub Jelinek (jakub@redhat.com)&n; */
multiline_comment|/*&n; * I hate traps on the sparc, grrr...&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;  /* for jiffies */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
multiline_comment|/* #define TRAP_DEBUG */
DECL|struct|trap_trace_entry
r_struct
id|trap_trace_entry
(brace
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|trap_curbuf
r_int
id|trap_curbuf
op_assign
l_int|0
suffix:semicolon
DECL|variable|trapbuf
r_struct
id|trap_trace_entry
id|trapbuf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|syscall_trace_entry
r_void
id|syscall_trace_entry
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s[%d]: &quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scall&lt;%d&gt; (could be %d)&bslash;n&quot;
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_G1
)braket
comma
(paren
r_int
)paren
id|regs-&gt;u_regs
(braket
id|UREG_I0
)braket
)paren
suffix:semicolon
)brace
DECL|function|syscall_trace_exit
r_void
id|syscall_trace_exit
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
)brace
DECL|function|sun4m_nmi
r_void
id|sun4m_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|afsr
comma
id|afar
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Aieee: sun4m NMI received!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX HyperSparc hack XXX */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov 0x500, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;lda [%%g1] 0x4, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov 0x600, %%g1&bslash;n&bslash;t&quot;
l_string|&quot;lda [%%g1] 0x4, %1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|afsr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|afar
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;afsr=%08lx afar=%08lx&bslash;n&quot;
comma
id|afsr
comma
id|afar
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;you lose buddy boy...&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sun4d_nmi
r_void
id|sun4d_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Aieee: sun4d NMI received!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;you lose buddy boy...&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|instruction_dump
r_void
id|instruction_dump
(paren
r_int
r_int
op_star
id|pc
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|pc
)paren
op_amp
l_int|3
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|3
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%c%08lx%c&quot;
comma
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&lt;&squot;
comma
id|pc
(braket
id|i
)braket
comma
id|i
ques
c_cond
l_char|&squot; &squot;
suffix:colon
l_char|&squot;&gt;&squot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__SAVE
mdefine_line|#define __SAVE __asm__ __volatile__(&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot;)
DECL|macro|__RESTORE
mdefine_line|#define __RESTORE __asm__ __volatile__(&quot;restore %g0, %g0, %g0&bslash;n&bslash;t&quot;)
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_int
id|die_counter
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Amuse the user. */
id|printk
c_func
(paren
l_string|&quot;              &bslash;&bslash;|/ ____ &bslash;&bslash;|/&bslash;n&quot;
l_string|&quot;              &bslash;&quot;@&squot;/ ,. &bslash;&bslash;`@&bslash;&quot;&bslash;n&quot;
l_string|&quot;              /_| &bslash;&bslash;__/ |_&bslash;&bslash;&bslash;n&quot;
l_string|&quot;                 &bslash;&bslash;__U_/&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s(%d): %s [#%d]&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|str
comma
op_increment
id|die_counter
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__SAVE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
id|__RESTORE
suffix:semicolon
(brace
r_struct
id|reg_window
op_star
id|rw
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
id|regs-&gt;u_regs
(braket
id|UREG_FP
)braket
suffix:semicolon
multiline_comment|/* Stop the back trace when we hit userland or we&n;&t;&t; * find some badly aligned kernel stack. Set an upper&n;&t;&t; * bound in case our stack is trashed and we loop.&n;&t;&t; */
r_while
c_loop
(paren
id|rw
op_logical_and
id|count
op_increment
OL
l_int|30
op_logical_and
(paren
(paren
(paren
r_int
r_int
)paren
id|rw
)paren
op_ge
id|PAGE_OFFSET
)paren
op_logical_and
op_logical_neg
(paren
(paren
(paren
r_int
r_int
)paren
id|rw
)paren
op_amp
l_int|0x7
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Caller[%08lx]&quot;
comma
id|rw-&gt;ins
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;: %s&bslash;n&quot;
comma
id|rw-&gt;ins
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|rw
op_assign
(paren
r_struct
id|reg_window
op_star
)paren
id|rw-&gt;ins
(braket
l_int|6
)braket
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Instruction DUMP:&quot;
)paren
suffix:semicolon
id|instruction_dump
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;pc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
(brace
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|do_hw_interrupt
r_void
id|do_hw_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|type
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0x80
)paren
(brace
multiline_comment|/* Sun OS&squot;s puke from bad traps, Linux survives! */
id|printk
c_func
(paren
l_string|&quot;Unimplemented Sparc TRAP, type = %02lx&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Whee... Hello Mr. Penguin&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Kernel bad trap&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLTRP
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|regs-&gt;pc
suffix:semicolon
id|info.si_trapno
op_assign
id|type
op_minus
l_int|0x80
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_illegal_instruction
r_void
id|do_illegal_instruction
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
r_extern
r_int
id|do_user_muldiv
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|psr
op_amp
id|PSR_PS
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Kernel illegal instruction&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#ifdef TRAP_DEBUG
id|printk
c_func
(paren
l_string|&quot;Ill instr. at pc=%08lx instruction is %08lx&bslash;n&quot;
comma
id|regs-&gt;pc
comma
op_star
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;pc
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|do_user_muldiv
(paren
id|regs
comma
id|pc
)paren
)paren
r_return
suffix:semicolon
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLOPC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_priv_instruction
r_void
id|do_priv_instruction
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|psr
op_amp
id|PSR_PS
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Penguin instruction from Penguin mode??!?!&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_PRVOPC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX User may want to be allowed to do this. XXX */
DECL|function|do_memaccess_unaligned
r_void
id|do_memaccess_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psr
op_amp
id|PSR_PS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KERNEL MNA at pc %08lx npc %08lx called by %08lx&bslash;n&quot;
comma
id|pc
comma
id|npc
comma
id|regs-&gt;u_regs
(braket
id|UREG_RETPC
)braket
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;BOGUS&quot;
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* die_if_kernel(&quot;Kernel MNA access&quot;, regs); */
)brace
macro_line|#if 0
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
id|instruction_dump
(paren
(paren
r_int
r_int
op_star
)paren
id|regs-&gt;pc
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;do_MNA!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGBUS
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|BUS_ADRALN
suffix:semicolon
id|info.si_addr
op_assign
multiline_comment|/* FIXME: Should dig out mna address */
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
r_extern
r_void
id|fpsave
c_func
(paren
r_int
r_int
op_star
id|fpregs
comma
r_int
r_int
op_star
id|fsr
comma
r_void
op_star
id|fpqueue
comma
r_int
r_int
op_star
id|fpqdepth
)paren
suffix:semicolon
r_extern
r_void
id|fpload
c_func
(paren
r_int
r_int
op_star
id|fpregs
comma
r_int
r_int
op_star
id|fsr
)paren
suffix:semicolon
DECL|variable|init_fsr
r_static
r_int
r_int
id|init_fsr
op_assign
l_int|0x0UL
suffix:semicolon
DECL|variable|init_fregs
r_static
r_int
r_int
id|init_fregs
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
op_assign
(brace
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
comma
op_complement
l_int|0UL
)brace
suffix:semicolon
DECL|function|do_fpd_trap
r_void
id|do_fpd_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
multiline_comment|/* Sanity check... */
r_if
c_cond
(paren
id|psr
op_amp
id|PSR_PS
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Kernel gets FloatingPenguinUnit disabled trap&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|put_psr
c_func
(paren
id|get_psr
c_func
(paren
)paren
op_or
id|PSR_EF
)paren
suffix:semicolon
multiline_comment|/* Allow FPU ops. */
id|regs-&gt;psr
op_or_assign
id|PSR_EF
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_task_used_math
)paren
(brace
multiline_comment|/* Other processes fpu state, save away */
r_struct
id|task_struct
op_star
id|fptask
op_assign
id|last_task_used_math
suffix:semicolon
id|fpsave
c_func
(paren
op_amp
id|fptask-&gt;thread.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|fptask-&gt;thread.fsr
comma
op_amp
id|fptask-&gt;thread.fpqueue
(braket
l_int|0
)braket
comma
op_amp
id|fptask-&gt;thread.fpqdepth
)paren
suffix:semicolon
)brace
id|last_task_used_math
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
id|fpload
c_func
(paren
op_amp
id|current-&gt;thread.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;thread.fsr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Set initial sane state. */
id|fpload
c_func
(paren
op_amp
id|init_fregs
(braket
l_int|0
)braket
comma
op_amp
id|init_fsr
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;used_math
)paren
(brace
id|fpload
c_func
(paren
op_amp
id|init_fregs
(braket
l_int|0
)braket
comma
op_amp
id|init_fsr
)paren
suffix:semicolon
id|current-&gt;used_math
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|fpload
c_func
(paren
op_amp
id|current-&gt;thread.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;thread.fsr
)paren
suffix:semicolon
)brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|_TIF_USEDFPU
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|fake_regs
r_static
r_int
r_int
id|fake_regs
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|variable|fake_fsr
r_static
r_int
r_int
id|fake_fsr
suffix:semicolon
DECL|variable|fake_queue
r_static
r_int
r_int
id|fake_queue
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|variable|fake_depth
r_static
r_int
r_int
id|fake_depth
suffix:semicolon
r_extern
r_int
id|do_mathemu
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|function|do_fpe_trap
r_void
id|do_fpe_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
r_static
r_int
id|calls
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
r_int
id|fsr
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_struct
id|task_struct
op_star
id|fpt
op_assign
id|last_task_used_math
suffix:semicolon
macro_line|#else
r_struct
id|task_struct
op_star
id|fpt
op_assign
id|current
suffix:semicolon
macro_line|#endif
id|put_psr
c_func
(paren
id|get_psr
c_func
(paren
)paren
op_or
id|PSR_EF
)paren
suffix:semicolon
multiline_comment|/* If nobody owns the fpu right now, just clear the&n;&t; * error into our fake static buffer and hope it don&squot;t&n;&t; * happen again.  Thank you crashme...&n;&t; */
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|fpt
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
(paren
id|fpt-&gt;thread_info-&gt;flags
op_amp
id|_TIF_USEDFPU
)paren
)paren
(brace
macro_line|#endif
id|fpsave
c_func
(paren
op_amp
id|fake_regs
(braket
l_int|0
)braket
comma
op_amp
id|fake_fsr
comma
op_amp
id|fake_queue
(braket
l_int|0
)braket
comma
op_amp
id|fake_depth
)paren
suffix:semicolon
id|regs-&gt;psr
op_and_assign
op_complement
id|PSR_EF
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fpsave
c_func
(paren
op_amp
id|fpt-&gt;thread.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|fpt-&gt;thread.fsr
comma
op_amp
id|fpt-&gt;thread.fpqueue
(braket
l_int|0
)braket
comma
op_amp
id|fpt-&gt;thread.fpqdepth
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_FPU
id|printk
c_func
(paren
l_string|&quot;Hmm, FP exception, fsr was %016lx&bslash;n&quot;
comma
id|fpt-&gt;thread.fsr
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
(paren
id|fpt-&gt;thread.fsr
op_amp
l_int|0x1c000
)paren
)paren
(brace
multiline_comment|/* switch on the contents of the ftt [floating point trap type] field */
macro_line|#ifdef DEBUG_FPU
r_case
(paren
l_int|1
op_lshift
l_int|14
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;IEEE_754_exception&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
(paren
l_int|2
op_lshift
l_int|14
)paren
suffix:colon
multiline_comment|/* unfinished_FPop (underflow &amp; co) */
r_case
(paren
l_int|3
op_lshift
l_int|14
)paren
suffix:colon
multiline_comment|/* unimplemented_FPop (quad stuff, maybe sqrt) */
id|ret
op_assign
id|do_mathemu
c_func
(paren
id|regs
comma
id|fpt
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef DEBUG_FPU
r_case
(paren
l_int|4
op_lshift
l_int|14
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;sequence_error (OS bug...)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|5
op_lshift
l_int|14
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;hardware_error (uhoh!)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
l_int|6
op_lshift
l_int|14
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;invalid_fp_register (user error)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* DEBUG_FPU */
)brace
multiline_comment|/* If we successfully emulated the FPop, we pretend the trap never happened :-&gt; */
r_if
c_cond
(paren
id|ret
)paren
(brace
id|fpload
c_func
(paren
op_amp
id|current-&gt;thread.float_regs
(braket
l_int|0
)braket
comma
op_amp
id|current-&gt;thread.fsr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* nope, better SIGFPE the offending process... */
macro_line|#ifdef CONFIG_SMP
id|fpt-&gt;thread_info-&gt;flags
op_and_assign
op_complement
id|_TIF_USEDFPU
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|psr
op_amp
id|PSR_PS
)paren
(brace
multiline_comment|/* The first fsr store/load we tried trapped,&n;&t;&t; * the second one will not (we hope).&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;WARNING: FPU exception from kernel mode. at pc=%08lx&bslash;n&quot;
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|regs-&gt;npc
suffix:semicolon
id|regs-&gt;npc
op_add_assign
l_int|4
suffix:semicolon
id|calls
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|calls
OG
l_int|2
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Too many Penguin-FPU traps from kernel mode&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|fsr
op_assign
id|fpt-&gt;thread.fsr
suffix:semicolon
id|info.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|__SI_FAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fsr
op_amp
l_int|0x1c000
)paren
op_eq
(paren
l_int|1
op_lshift
l_int|14
)paren
)paren
(brace
r_if
c_cond
(paren
id|fsr
op_amp
l_int|0x10
)paren
id|info.si_code
op_assign
id|FPE_FLTINV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fsr
op_amp
l_int|0x08
)paren
id|info.si_code
op_assign
id|FPE_FLTOVF
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fsr
op_amp
l_int|0x04
)paren
id|info.si_code
op_assign
id|FPE_FLTUND
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fsr
op_amp
l_int|0x02
)paren
id|info.si_code
op_assign
id|FPE_FLTDIV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fsr
op_amp
l_int|0x01
)paren
id|info.si_code
op_assign
id|FPE_FLTRES
suffix:semicolon
)brace
id|send_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|info
comma
id|fpt
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|regs-&gt;psr
op_and_assign
op_complement
id|PSR_EF
suffix:semicolon
r_if
c_cond
(paren
id|calls
OG
l_int|0
)paren
(brace
id|calls
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|handle_tag_overflow
r_void
id|handle_tag_overflow
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|psr
op_amp
id|PSR_PS
)paren
(brace
id|die_if_kernel
c_func
(paren
l_string|&quot;Penguin overflow trap from kernel mode&quot;
comma
id|regs
)paren
suffix:semicolon
)brace
id|info.si_signo
op_assign
id|SIGEMT
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|EMT_TAGOVF
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGEMT
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|handle_watchpoint
r_void
id|handle_watchpoint
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
macro_line|#ifdef TRAP_DEBUG
id|printk
c_func
(paren
l_string|&quot;Watchpoint detected at PC %08lx NPC %08lx PSR %08lx&bslash;n&quot;
comma
id|pc
comma
id|npc
comma
id|psr
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|psr
op_amp
id|PSR_PS
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Tell me what a watchpoint trap is, and I&squot;ll then deal &quot;
l_string|&quot;with such a beast...&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|handle_reg_access
r_void
id|handle_reg_access
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef TRAP_DEBUG
id|printk
c_func
(paren
l_string|&quot;Register Access Exception at PC %08lx NPC %08lx PSR %08lx&bslash;n&quot;
comma
id|pc
comma
id|npc
comma
id|psr
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGBUS
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|BUS_OBJERR
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGBUS
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|handle_cp_disabled
r_void
id|handle_cp_disabled
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_COPROC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|handle_cp_exception
r_void
id|handle_cp_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef TRAP_DEBUG
id|printk
c_func
(paren
l_string|&quot;Co-Processor Exception at PC %08lx NPC %08lx PSR %08lx&bslash;n&quot;
comma
id|pc
comma
id|npc
comma
id|psr
)paren
suffix:semicolon
macro_line|#endif
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_COPROC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|handle_hw_divzero
r_void
id|handle_hw_divzero
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|npc
comma
r_int
r_int
id|psr
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
id|info.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|FPE_INTDIV
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
id|__user
op_star
)paren
id|pc
suffix:semicolon
id|info.si_trapno
op_assign
l_int|0
suffix:semicolon
id|send_sig_info
c_func
(paren
id|SIGFPE
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
DECL|function|do_BUG
r_void
id|do_BUG
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
(brace
singleline_comment|// bust_spinlocks(1);   XXX Not in our original BUG()
id|printk
c_func
(paren
l_string|&quot;kernel BUG at %s:%d!&bslash;n&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Since we have our mappings set up, on multiprocessors we can spin them&n; * up here so that timer interrupts work during initialization.&n; */
r_extern
r_void
id|sparc_cpu_startup
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|linux_smp_still_initting
r_int
id|linux_smp_still_initting
suffix:semicolon
DECL|variable|thiscpus_tbr
r_int
r_int
id|thiscpus_tbr
suffix:semicolon
DECL|variable|thiscpus_mid
r_int
id|thiscpus_mid
suffix:semicolon
DECL|function|trap_init
r_void
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|thread_info_offsets_are_bolixed_pete
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Force linker to barf if mismatched */
r_if
c_cond
(paren
id|TI_UWINMASK
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|uwinmask
)paren
op_logical_or
id|TI_TASK
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|task
)paren
op_logical_or
id|TI_EXECDOMAIN
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|exec_domain
)paren
op_logical_or
id|TI_FLAGS
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|flags
)paren
op_logical_or
id|TI_CPU
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|cpu
)paren
op_logical_or
id|TI_PREEMPT
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|preempt_count
)paren
op_logical_or
id|TI_SOFTIRQ
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|softirq_count
)paren
op_logical_or
id|TI_HARDIRQ
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|hardirq_count
)paren
op_logical_or
id|TI_KSP
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|ksp
)paren
op_logical_or
id|TI_KPC
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|kpc
)paren
op_logical_or
id|TI_KPSR
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|kpsr
)paren
op_logical_or
id|TI_KWIM
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|kwim
)paren
op_logical_or
id|TI_REG_WINDOW
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|reg_window
)paren
op_logical_or
id|TI_RWIN_SPTRS
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|rwbuf_stkptrs
)paren
op_logical_or
id|TI_W_SAVED
op_ne
m_offsetof
(paren
r_struct
id|thread_info
comma
id|w_saved
)paren
)paren
id|thread_info_offsets_are_bolixed_pete
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Attach to the address space of init_task. */
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
multiline_comment|/* NOTE: Other cpus have this done as they are started&n;&t; *       up on SMP.&n;&t; */
)brace
eof
