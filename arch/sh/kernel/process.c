multiline_comment|/* $Id: process.c,v 1.28 2004/05/05 16:54:23 lethal Exp $&n; *&n; *  linux/arch/sh/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  SuperH version:  Copyright (C) 1999, 2000  Niibe Yutaka &amp; Kaz Kojima&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/platform.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#if defined(CONFIG_SH_HS7751RVOIP)
macro_line|#include &lt;asm/hs7751rvoip/hs7751rvoip.h&gt;
macro_line|#elif defined(CONFIG_SH_RTS7751R2D)
macro_line|#include &lt;asm/rts7751r2d/rts7751r2d.h&gt;
macro_line|#endif
DECL|variable|hlt_counter
r_static
r_int
id|hlt_counter
op_assign
l_int|0
suffix:semicolon
DECL|variable|ubc_usercnt
r_int
id|ubc_usercnt
op_assign
l_int|0
suffix:semicolon
DECL|macro|HARD_IDLE_TIMEOUT
mdefine_line|#define HARD_IDLE_TIMEOUT (HZ / 3)
DECL|function|disable_hlt
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_increment
suffix:semicolon
)brace
DECL|variable|disable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|disable_hlt
)paren
suffix:semicolon
DECL|function|enable_hlt
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_decrement
suffix:semicolon
)brace
DECL|variable|enable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|enable_hlt
)paren
suffix:semicolon
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|hlt_counter
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|cpu_sleep
c_func
(paren
)paren
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
id|default_idle
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
multiline_comment|/* SR.BL=1 and invoke address error to let CPU reset (manual reset) */
id|asm
r_volatile
(paren
l_string|&quot;ldc %0, sr&bslash;n&bslash;t&quot;
l_string|&quot;mov.l @%1, %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
l_int|0x10000000
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x80000001
)paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SH_HS7751RVOIP)
r_int
r_int
id|value
suffix:semicolon
id|value
op_assign
id|ctrl_inw
c_func
(paren
id|PA_OUTPORTR
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
(paren
id|value
op_amp
l_int|0xffdf
)paren
comma
id|PA_OUTPORTR
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_SH_RTS7751R2D)
id|ctrl_outw
c_func
(paren
l_int|0x0001
comma
id|PA_POWOFF
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
id|cpu_sleep
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SH_HS7751RVOIP)
r_int
r_int
id|value
suffix:semicolon
id|value
op_assign
id|ctrl_inw
c_func
(paren
id|PA_OUTPORTR
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
(paren
id|value
op_amp
l_int|0xffdf
)paren
comma
id|PA_OUTPORTR
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_SH_RTS7751R2D)
id|ctrl_outw
c_func
(paren
l_int|0x0001
comma
id|PA_POWOFF
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
DECL|function|show_regs
r_void
id|show_regs
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pid : %d, Comm: %20s&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;PC is at %s&bslash;n&quot;
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PC  : %08lx SP  : %08lx SR  : %08lx &quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;regs
(braket
l_int|15
)braket
comma
id|regs-&gt;sr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
id|printk
c_func
(paren
l_string|&quot;TEA : %08x    &quot;
comma
id|ctrl_inl
c_func
(paren
id|MMU_TEA
)paren
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;                  &quot;
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R0  : %08lx R1  : %08lx R2  : %08lx R3  : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|0
)braket
comma
id|regs-&gt;regs
(braket
l_int|1
)braket
comma
id|regs-&gt;regs
(braket
l_int|2
)braket
comma
id|regs-&gt;regs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R4  : %08lx R5  : %08lx R6  : %08lx R7  : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|4
)braket
comma
id|regs-&gt;regs
(braket
l_int|5
)braket
comma
id|regs-&gt;regs
(braket
l_int|6
)braket
comma
id|regs-&gt;regs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R8  : %08lx R9  : %08lx R10 : %08lx R11 : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|8
)braket
comma
id|regs-&gt;regs
(braket
l_int|9
)braket
comma
id|regs-&gt;regs
(braket
l_int|10
)braket
comma
id|regs-&gt;regs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R12 : %08lx R13 : %08lx R14 : %08lx&bslash;n&quot;
comma
id|regs-&gt;regs
(braket
l_int|12
)braket
comma
id|regs-&gt;regs
(braket
l_int|13
)braket
comma
id|regs-&gt;regs
(braket
l_int|14
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MACH: %08lx MACL: %08lx GBR : %08lx PR  : %08lx&bslash;n&quot;
comma
id|regs-&gt;mach
comma
id|regs-&gt;macl
comma
id|regs-&gt;gbr
comma
id|regs-&gt;pr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re in kernel mode, dump the stack too..&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
r_extern
r_void
id|show_task
c_func
(paren
r_int
r_int
op_star
id|sp
)paren
suffix:semicolon
r_int
r_int
id|sp
op_assign
id|regs-&gt;regs
(braket
l_int|15
)braket
suffix:semicolon
id|show_task
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|sp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Create a kernel thread&n; */
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; */
r_extern
r_void
id|kernel_thread_helper
c_func
(paren
r_void
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.align 5&bslash;n&quot;
l_string|&quot;kernel_thread_helper:&bslash;n&bslash;t&quot;
l_string|&quot;jsr&t;@r5&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;1f, r1&bslash;n&bslash;t&quot;
l_string|&quot;jsr&t;@r1&bslash;n&bslash;t&quot;
l_string|&quot; mov&t;r0, r4&bslash;n&bslash;t&quot;
l_string|&quot;.align 2&bslash;n&bslash;t&quot;
l_string|&quot;1:.long do_exit&quot;
)paren
suffix:semicolon
DECL|function|kernel_thread
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
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
)paren
(brace
multiline_comment|/* Don&squot;t use this in BL=1(cli).  Or else, CPU resets! */
r_struct
id|pt_regs
id|regs
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|regs
comma
l_int|0
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
id|regs.regs
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|arg
suffix:semicolon
id|regs.regs
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
id|fn
suffix:semicolon
id|regs.pc
op_assign
(paren
r_int
r_int
)paren
id|kernel_thread_helper
suffix:semicolon
id|regs.sr
op_assign
(paren
l_int|1
op_lshift
l_int|30
)paren
suffix:semicolon
multiline_comment|/* Ok, create the new process.. */
r_return
id|do_fork
c_func
(paren
id|flags
op_or
id|CLONE_VM
op_or
id|CLONE_UNTRACED
comma
l_int|0
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;thread.ubc_pc
)paren
(brace
id|current-&gt;thread.ubc_pc
op_assign
l_int|0
suffix:semicolon
id|ubc_usercnt
op_sub_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SH_FPU)
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|tsk-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* Forget lazy FPU state */
id|clear_fpu
c_func
(paren
id|tsk
comma
id|regs
)paren
suffix:semicolon
id|clear_used_math
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|release_thread
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
multiline_comment|/* do nothing */
)brace
multiline_comment|/* Fill in the fpu structure for a core dump.. */
DECL|function|dump_fpu
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
r_int
id|fpvalid
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(CONFIG_SH_FPU)
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|fpvalid
op_assign
op_logical_neg
op_logical_neg
id|tsk_used_math
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
id|unlazy_fpu
c_func
(paren
id|tsk
comma
id|regs
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.fpu.hard
comma
r_sizeof
(paren
op_star
id|fpu
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|fpvalid
suffix:semicolon
)brace
multiline_comment|/* &n; * Capture the user space registers if the task is not running (in user space)&n; */
DECL|function|dump_task_regs
r_int
id|dump_task_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_gregset_t
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
id|ptregs
suffix:semicolon
id|ptregs
op_assign
op_star
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|tsk-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
macro_line|#ifdef CONFIG_SH_DSP
op_minus
r_sizeof
(paren
r_struct
id|pt_dspregs
)paren
macro_line|#endif
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|elf_core_copy_regs
c_func
(paren
id|regs
comma
op_amp
id|ptregs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|dump_task_fpu
id|dump_task_fpu
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_fpregset_t
op_star
id|fpu
)paren
(brace
r_int
id|fpvalid
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(CONFIG_SH_FPU)
id|fpvalid
op_assign
op_logical_neg
op_logical_neg
id|tsk_used_math
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fpvalid
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|tsk-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|tsk
comma
id|regs
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu
comma
op_amp
id|tsk-&gt;thread.fpu.hard
comma
r_sizeof
(paren
op_star
id|fpu
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|fpvalid
suffix:semicolon
)brace
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|copy_thread
r_int
id|copy_thread
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_int
r_int
id|unused
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
macro_line|#if defined(CONFIG_SH_FPU)
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|tsk
comma
id|regs
)paren
suffix:semicolon
id|p-&gt;thread.fpu
op_assign
id|tsk-&gt;thread.fpu
suffix:semicolon
id|copy_to_stopped_child_used_math
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#endif
id|childregs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|THREAD_SIZE
op_plus
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
)paren
macro_line|#ifdef CONFIG_SH_DSP
op_minus
r_sizeof
(paren
r_struct
id|pt_dspregs
)paren
macro_line|#endif
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|childregs-&gt;regs
(braket
l_int|15
)braket
op_assign
id|usp
suffix:semicolon
)brace
r_else
(brace
id|childregs-&gt;regs
(braket
l_int|15
)braket
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
op_plus
id|THREAD_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
(brace
id|childregs-&gt;gbr
op_assign
id|childregs-&gt;regs
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|childregs-&gt;regs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set return value for child */
id|p-&gt;thread.sp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.pc
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|p-&gt;thread.ubc_pc
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
DECL|function|dump_thread
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
id|current-&gt;mm-&gt;start_code
suffix:semicolon
id|dump-&gt;start_data
op_assign
id|current-&gt;mm-&gt;start_data
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;regs
(braket
l_int|15
)braket
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
id|current-&gt;mm-&gt;end_code
op_minus
id|dump-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_minus
id|dump-&gt;start_data
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
(paren
id|current-&gt;mm-&gt;start_stack
op_minus
id|dump-&gt;start_stack
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/* Debug registers will come here. */
id|dump-&gt;regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
c_func
(paren
id|regs
comma
op_amp
id|dump-&gt;fpu
)paren
suffix:semicolon
)brace
multiline_comment|/* Tracing by user break controller.  */
r_static
r_void
DECL|function|ubc_set_tracing
id|ubc_set_tracing
c_func
(paren
r_int
id|asid
comma
r_int
r_int
id|pc
)paren
(brace
id|ctrl_outl
c_func
(paren
id|pc
comma
id|UBC_BARA
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t have any ASID settings for the SH-2! */
r_if
c_cond
(paren
id|cpu_data-&gt;type
op_ne
id|CPU_SH7604
)paren
id|ctrl_outb
c_func
(paren
id|asid
comma
id|UBC_BASRA
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|UBC_BAMRA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_data-&gt;type
op_eq
id|CPU_SH7729
)paren
(brace
id|ctrl_outw
c_func
(paren
id|BBR_INST
op_or
id|BBR_READ
op_or
id|BBR_CPU
comma
id|UBC_BBRA
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|BRCR_PCBA
op_or
id|BRCR_PCTE
comma
id|UBC_BRCR
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctrl_outw
c_func
(paren
id|BBR_INST
op_or
id|BBR_READ
comma
id|UBC_BBRA
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|BRCR_PCBA
comma
id|UBC_BRCR
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;switch_to(x,y) should switch tasks from x to y.&n; *&n; */
DECL|function|__switch_to
r_struct
id|task_struct
op_star
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|task_struct
op_star
id|next
)paren
(brace
macro_line|#if defined(CONFIG_SH_FPU)
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|prev-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|prev
comma
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PREEMPT
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|prev-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
macro_line|#ifdef CONFIG_SH_DSP
op_minus
r_sizeof
(paren
r_struct
id|pt_dspregs
)paren
macro_line|#endif
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
id|regs-&gt;regs
(braket
l_int|15
)braket
op_ge
l_int|0xc0000000
)paren
(brace
r_int
id|offset
op_assign
(paren
r_int
)paren
id|regs-&gt;regs
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* Reset stack pointer: clear critical region mark */
id|regs-&gt;regs
(braket
l_int|15
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;pc
OL
id|regs-&gt;regs
(braket
l_int|0
)braket
)paren
multiline_comment|/* Go to rewind point */
id|regs-&gt;pc
op_assign
id|regs-&gt;regs
(braket
l_int|0
)braket
op_plus
id|offset
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Restore the kernel mode register&n;&t; *   &t;k7 (r7_bank1)&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;ldc&t;%0, r7_bank&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|next-&gt;thread_info
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
multiline_comment|/* If no tasks are using the UBC, we&squot;re done */
r_if
c_cond
(paren
id|ubc_usercnt
op_eq
l_int|0
)paren
multiline_comment|/* If no tasks are using the UBC, we&squot;re done */
suffix:semicolon
r_else
r_if
c_cond
(paren
id|next-&gt;thread.ubc_pc
op_logical_and
id|next-&gt;mm
)paren
(brace
id|ubc_set_tracing
c_func
(paren
id|next-&gt;mm-&gt;context
op_amp
id|MMU_CONTEXT_ASID_MASK
comma
id|next-&gt;thread.ubc_pc
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|UBC_BBRA
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|UBC_BBRB
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|prev
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
macro_line|#ifdef CONFIG_MMU
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.regs
(braket
l_int|15
)braket
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* fork almost works, enough to trick you into looking elsewhere :-( */
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|newsp
comma
r_int
r_int
id|parent_tidptr
comma
r_int
r_int
id|child_tidptr
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.regs
(braket
l_int|15
)braket
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
op_amp
id|regs
comma
l_int|0
comma
(paren
r_int
id|__user
op_star
)paren
id|parent_tidptr
comma
(paren
r_int
id|__user
op_star
)paren
id|child_tidptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is trivial, and on the face of it looks like it&n; * could equally well be done in user mode.&n; *&n; * Not so, for quite unobvious reasons - register pressure.&n; * In user mode vfork() cannot have a stack frame, and if&n; * done by calling the &quot;clone()&quot; system call directly, you&n; * do not have enough call-clobbered registers to hold all&n; * the information you need.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs.regs
(braket
l_int|15
)braket
comma
op_amp
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|ufilename
comma
r_char
op_star
op_star
id|uargv
comma
r_char
op_star
op_star
id|uenvp
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
id|__user
op_star
)paren
id|ufilename
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
id|__user
op_star
id|__user
op_star
)paren
id|uargv
comma
(paren
r_char
id|__user
op_star
id|__user
op_star
)paren
id|uenvp
comma
op_amp
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
(brace
id|task_lock
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|task_unlock
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|schedule_frame
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * The same comment as on the Alpha applies here, too ...&n;&t; */
id|pc
op_assign
id|thread_saved_pc
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_sched_functions
c_func
(paren
id|pc
)paren
)paren
(brace
id|schedule_frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
(paren
r_int
)paren
id|p-&gt;thread.sp
)paren
(braket
l_int|1
)braket
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
op_star
)paren
id|schedule_frame
)paren
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_return
id|pc
suffix:semicolon
)brace
DECL|function|break_point_trap
id|asmlinkage
r_void
id|break_point_trap
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
multiline_comment|/* Clear tracing.  */
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|UBC_BBRA
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
l_int|0
comma
id|UBC_BBRB
)paren
suffix:semicolon
id|current-&gt;thread.ubc_pc
op_assign
l_int|0
suffix:semicolon
id|ubc_usercnt
op_sub_assign
l_int|1
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|break_point_trap_software
id|asmlinkage
r_void
id|break_point_trap_software
c_func
(paren
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
id|regs.pc
op_sub_assign
l_int|2
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
)brace
eof
