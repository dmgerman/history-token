multiline_comment|/*&n; *  linux/arch/m68knommu/kernel/process.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; *&n; *  68060 fixes by Jesper Skov&n; *&n; *  uClinux changes&n; *  Copyright (C) 2000-2002, David McCullough &lt;davidm@snapgear.com&gt;&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The idle loop on an m68knommu..&n; */
DECL|function|default_idle
r_void
id|default_idle
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
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|__asm__
c_func
(paren
l_string|&quot;stop #0x2000&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|idle
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
op_assign
id|default_idle
suffix:semicolon
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|idle
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
r_if
c_cond
(paren
id|mach_reset
)paren
id|mach_reset
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mach_halt
)paren
id|mach_halt
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mach_power_off
)paren
id|mach_power_off
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
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
l_string|&quot;Format %02x  Vector: %04x  PC: %08lx  Status: %04x    %s&bslash;n&quot;
comma
id|regs-&gt;format
comma
id|regs-&gt;vector
comma
id|regs-&gt;pc
comma
id|regs-&gt;sr
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
l_string|&quot;ORIG_D0: %08lx  D0: %08lx  A2: %08lx  A1: %08lx&bslash;n&quot;
comma
id|regs-&gt;orig_d0
comma
id|regs-&gt;d0
comma
id|regs-&gt;a2
comma
id|regs-&gt;a1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;A0: %08lx  D5: %08lx  D4: %08lx&bslash;n&quot;
comma
id|regs-&gt;a0
comma
id|regs-&gt;d5
comma
id|regs-&gt;d4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;D3: %08lx  D2: %08lx  D1: %08lx&bslash;n&quot;
comma
id|regs-&gt;d3
comma
id|regs-&gt;d2
comma
id|regs-&gt;d1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;sr
op_amp
id|PS_S
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;USP: %08lx&bslash;n&quot;
comma
id|rdusp
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a kernel thread&n; */
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
r_int
id|retval
suffix:semicolon
r_int
id|clone_arg
op_assign
id|flags
op_or
id|CLONE_VM
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel&t;%%sp, %%d2&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%5, %%d1&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%1, %%d0&bslash;n&bslash;t&quot;
l_string|&quot;trap&t;#0&bslash;n&bslash;t&quot;
l_string|&quot;cmpl&t;%%sp, %%d2&bslash;n&bslash;t&quot;
l_string|&quot;jeq&t;1f&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%3, %%sp@-&bslash;n&bslash;t&quot;
l_string|&quot;jsr&t;%4@&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%2, %%d0&bslash;n&bslash;t&quot;
l_string|&quot;trap&t;#0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|__NR_clone
)paren
comma
l_string|&quot;i&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;a&quot;
(paren
id|arg
)paren
comma
l_string|&quot;a&quot;
(paren
id|fn
)paren
comma
l_string|&quot;a&quot;
(paren
id|clone_arg
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;%d0&quot;
comma
l_string|&quot;%d1&quot;
comma
l_string|&quot;%d2&quot;
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_FPU
r_int
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|current-&gt;thread.fs
op_assign
id|__USER_DS
suffix:semicolon
macro_line|#ifdef CONFIG_FPU
r_if
c_cond
(paren
op_logical_neg
id|FPU_IS_EMU
)paren
id|asm
r_volatile
(paren
l_string|&quot;.chip 68k/68881&bslash;n&bslash;t&quot;
l_string|&quot;frestore %0@&bslash;n&bslash;t&quot;
l_string|&quot;.chip 68k&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|zero
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * &quot;m68k_fork()&quot;.. By the time we get here, the&n; * non-volatile registers have also been saved on the&n; * stack. We do some ugly pointer stuff here.. (see&n; * also copy_thread)&n; */
DECL|function|m68k_fork
id|asmlinkage
r_int
id|m68k_fork
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* fork almost works, enough to trick you into looking elsewhere :-( */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|m68k_vfork
id|asmlinkage
r_int
id|m68k_vfork
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|rdusp
c_func
(paren
)paren
comma
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|m68k_clone
id|asmlinkage
r_int
id|m68k_clone
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
id|clone_flags
suffix:semicolon
r_int
r_int
id|newsp
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
multiline_comment|/* syscall2 puts clone_flags in d1 and usp in d2 */
id|clone_flags
op_assign
id|regs-&gt;d1
suffix:semicolon
id|newsp
op_assign
id|regs-&gt;d2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|clone_flags
op_amp
op_complement
id|CLONE_IDLETASK
comma
id|newsp
comma
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
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
id|topstk
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
r_struct
id|switch_stack
op_star
id|childstack
comma
op_star
id|stack
suffix:semicolon
r_int
r_int
id|stack_offset
comma
op_star
id|retp
suffix:semicolon
id|stack_offset
op_assign
id|KTHREAD_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|childregs
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
id|p-&gt;thread_info
op_plus
id|stack_offset
)paren
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;d0
op_assign
l_int|0
suffix:semicolon
id|retp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|regs
)paren
suffix:semicolon
id|stack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|retp
)paren
op_minus
l_int|1
suffix:semicolon
id|childstack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|childregs
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childstack
op_assign
op_star
id|stack
suffix:semicolon
id|childstack-&gt;retpc
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|p-&gt;thread.usp
op_assign
id|usp
suffix:semicolon
id|p-&gt;thread.ksp
op_assign
(paren
r_int
r_int
)paren
id|childstack
suffix:semicolon
multiline_comment|/*&n;&t; * Must save the current SFC/DFC value, NOT the value when&n;&t; * the parent was last descheduled - RGH  10-08-96&n;&t; */
id|p-&gt;thread.fs
op_assign
id|get_fs
c_func
(paren
)paren
dot
id|seg
suffix:semicolon
macro_line|#ifdef CONFIG_FPU
r_if
c_cond
(paren
op_logical_neg
id|FPU_IS_EMU
)paren
(brace
multiline_comment|/* Copy the current fpu state */
id|asm
r_volatile
(paren
l_string|&quot;fsave %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|p-&gt;thread.fpstate
(braket
l_int|0
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;thread.fpstate
(braket
l_int|0
)braket
)paren
id|asm
r_volatile
(paren
l_string|&quot;fmovemx %/fp0-%/fp7,%0&bslash;n&bslash;t&quot;
l_string|&quot;fmoveml %/fpiar/%/fpcr/%/fpsr,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|p-&gt;thread.fp
(braket
l_int|0
)braket
)paren
comma
l_string|&quot;m&quot;
(paren
id|p-&gt;thread.fpcntl
(braket
l_int|0
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* Restore the state in case the fpu was busy */
id|asm
r_volatile
(paren
l_string|&quot;frestore %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|p-&gt;thread.fpstate
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fill in the fpu structure for a core dump.  */
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
r_struct
id|user_m68kfp_struct
op_star
id|fpu
)paren
(brace
macro_line|#ifdef CONFIG_FPU
r_char
id|fpustate
(braket
l_int|216
)braket
suffix:semicolon
r_if
c_cond
(paren
id|FPU_IS_EMU
)paren
(brace
r_int
id|i
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu-&gt;fpcntl
comma
id|current-&gt;thread.fpcntl
comma
l_int|12
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|fpu-&gt;fpregs
comma
id|current-&gt;thread.fp
comma
l_int|96
)paren
suffix:semicolon
multiline_comment|/* Convert internal fpu reg representation&n;&t;&t; * into long double format&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|24
suffix:semicolon
id|i
op_add_assign
l_int|3
)paren
id|fpu-&gt;fpregs
(braket
id|i
)braket
op_assign
(paren
(paren
id|fpu-&gt;fpregs
(braket
id|i
)braket
op_amp
l_int|0xffff0000
)paren
op_lshift
l_int|15
)paren
op_or
(paren
(paren
id|fpu-&gt;fpregs
(braket
id|i
)braket
op_amp
l_int|0x0000ffff
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* First dump the fpu context to avoid protocol violation.  */
id|asm
r_volatile
(paren
l_string|&quot;fsave %0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|fpustate
(braket
l_int|0
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpustate
(braket
l_int|0
)braket
)paren
r_return
l_int|0
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;fmovem %/fpiar/%/fpcr/%/fpsr,%0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|fpu-&gt;fpcntl
(braket
l_int|0
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;fmovemx %/fp0-%/fp7,%0&quot;
op_scope_resolution
l_string|&quot;m&quot;
(paren
id|fpu-&gt;fpregs
(braket
l_int|0
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
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
r_struct
id|switch_stack
op_star
id|sw
suffix:semicolon
multiline_comment|/* changed the size calculations - should hopefully work better. lbt */
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|rdusp
c_func
(paren
)paren
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
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_sub_assign
id|dump-&gt;u_tsize
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dump-&gt;start_stack
OL
id|TASK_SIZE
)paren
id|dump-&gt;u_ssize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|TASK_SIZE
op_minus
id|dump-&gt;start_stack
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_ar0
op_assign
(paren
r_struct
id|user_regs_struct
op_star
)paren
(paren
(paren
r_int
)paren
op_amp
id|dump-&gt;regs
op_minus
(paren
r_int
)paren
id|dump
)paren
suffix:semicolon
id|sw
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|regs
)paren
op_minus
l_int|1
suffix:semicolon
id|dump-&gt;regs.d1
op_assign
id|regs-&gt;d1
suffix:semicolon
id|dump-&gt;regs.d2
op_assign
id|regs-&gt;d2
suffix:semicolon
id|dump-&gt;regs.d3
op_assign
id|regs-&gt;d3
suffix:semicolon
id|dump-&gt;regs.d4
op_assign
id|regs-&gt;d4
suffix:semicolon
id|dump-&gt;regs.d5
op_assign
id|regs-&gt;d5
suffix:semicolon
id|dump-&gt;regs.d6
op_assign
id|sw-&gt;d6
suffix:semicolon
id|dump-&gt;regs.d7
op_assign
id|sw-&gt;d7
suffix:semicolon
id|dump-&gt;regs.a0
op_assign
id|regs-&gt;a0
suffix:semicolon
id|dump-&gt;regs.a1
op_assign
id|regs-&gt;a1
suffix:semicolon
id|dump-&gt;regs.a2
op_assign
id|regs-&gt;a2
suffix:semicolon
id|dump-&gt;regs.a3
op_assign
id|sw-&gt;a3
suffix:semicolon
id|dump-&gt;regs.a4
op_assign
id|sw-&gt;a4
suffix:semicolon
id|dump-&gt;regs.a5
op_assign
id|sw-&gt;a5
suffix:semicolon
id|dump-&gt;regs.a6
op_assign
id|sw-&gt;a6
suffix:semicolon
id|dump-&gt;regs.d0
op_assign
id|regs-&gt;d0
suffix:semicolon
id|dump-&gt;regs.orig_d0
op_assign
id|regs-&gt;orig_d0
suffix:semicolon
id|dump-&gt;regs.stkadj
op_assign
id|regs-&gt;stkadj
suffix:semicolon
id|dump-&gt;regs.sr
op_assign
id|regs-&gt;sr
suffix:semicolon
id|dump-&gt;regs.pc
op_assign
id|regs-&gt;pc
suffix:semicolon
id|dump-&gt;regs.fmtvec
op_assign
(paren
id|regs-&gt;format
op_lshift
l_int|12
)paren
op_or
id|regs-&gt;vector
suffix:semicolon
multiline_comment|/* dump floating point stuff */
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;m68kfp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Generic dumping code. Used for panic and debug.&n; */
DECL|function|dump
r_void
id|dump
c_func
(paren
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
op_star
id|sp
suffix:semicolon
r_int
r_char
op_star
id|tp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nCURRENT PROCESS:&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;COMM=%s PID=%d&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;TEXT=%08x-%08x DATA=%08x-%08x BSS=%08x-%08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;start_code
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;end_code
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;start_data
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;end_data
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;end_data
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;brk
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;USER-STACK=%08x  KERNEL-STACK=%08x&bslash;n&bslash;n&quot;
comma
(paren
r_int
)paren
id|current-&gt;mm-&gt;start_stack
comma
(paren
r_int
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|current
)paren
op_plus
id|KTHREAD_SIZE
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PC: %08lx&bslash;n&quot;
comma
id|fp-&gt;pc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SR: %08lx    SP: %08lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|fp-&gt;sr
comma
(paren
r_int
)paren
id|fp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;d0: %08lx    d1: %08lx    d2: %08lx    d3: %08lx&bslash;n&quot;
comma
id|fp-&gt;d0
comma
id|fp-&gt;d1
comma
id|fp-&gt;d2
comma
id|fp-&gt;d3
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;d4: %08lx    d5: %08lx    a0: %08lx    a1: %08lx&bslash;n&quot;
comma
id|fp-&gt;d4
comma
id|fp-&gt;d5
comma
id|fp-&gt;a0
comma
id|fp-&gt;a1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nUSP: %08x   TRAPFRAME: %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|rdusp
c_func
(paren
)paren
comma
(paren
r_int
r_int
)paren
id|fp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nCODE:&quot;
)paren
suffix:semicolon
id|tp
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|fp-&gt;pc
)paren
op_minus
l_int|0x20
suffix:semicolon
r_for
c_loop
(paren
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|tp
comma
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|0x40
)paren
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|0x10
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n%08x: &quot;
comma
(paren
r_int
)paren
(paren
id|tp
op_plus
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
(paren
r_int
)paren
op_star
id|sp
op_increment
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nKERNEL STACK:&quot;
)paren
suffix:semicolon
id|tp
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|fp
)paren
op_minus
l_int|0x40
suffix:semicolon
r_for
c_loop
(paren
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|tp
comma
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|0xc0
)paren
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|0x10
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n%08x: &quot;
comma
(paren
r_int
)paren
(paren
id|tp
op_plus
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
(paren
r_int
)paren
op_star
id|sp
op_increment
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nUSER STACK:&quot;
)paren
suffix:semicolon
id|tp
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|rdusp
c_func
(paren
)paren
op_minus
l_int|0x10
)paren
suffix:semicolon
r_for
c_loop
(paren
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|tp
comma
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|0x80
)paren
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|0x10
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n%08x: &quot;
comma
(paren
r_int
)paren
(paren
id|tp
op_plus
id|i
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
(paren
r_int
)paren
op_star
id|sp
op_increment
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&quot;
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
id|name
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
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
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
op_amp
id|name
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
id|name
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
id|argv
comma
id|envp
comma
id|regs
)paren
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched&t;((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched&t;((unsigned long) scheduling_functions_end_here)
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
id|fp
comma
id|pc
suffix:semicolon
r_int
r_int
id|stack_page
suffix:semicolon
r_int
id|count
op_assign
l_int|0
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
id|stack_page
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|fp
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|p-&gt;thread.ksp
)paren
op_member_access_from_pointer
id|a6
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|fp
OL
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|task_struct
)paren
op_logical_or
id|fp
op_ge
l_int|8184
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|pc
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|fp
)paren
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* FIXME: This depends on the order of these functions. */
r_if
c_cond
(paren
id|pc
OL
id|first_sched
op_logical_or
id|pc
op_ge
id|last_sched
)paren
r_return
id|pc
suffix:semicolon
id|fp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|fp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|switch_stack
op_star
id|sw
op_assign
(paren
r_struct
id|switch_stack
op_star
)paren
id|tsk-&gt;thread.ksp
suffix:semicolon
multiline_comment|/* Check whether the thread is blocked in resume() */
r_if
c_cond
(paren
id|sw-&gt;retpc
OG
(paren
r_int
r_int
)paren
id|scheduling_functions_start_here
op_logical_and
id|sw-&gt;retpc
OL
(paren
r_int
r_int
)paren
id|scheduling_functions_end_here
)paren
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|sw-&gt;a6
)paren
(braket
l_int|1
)braket
suffix:semicolon
r_else
r_return
id|sw-&gt;retpc
suffix:semicolon
)brace
eof
