multiline_comment|/*&n; *  linux/arch/h8300/kernel/process.c&n; *&n; * Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; *  Based on:&n; *&n; *  linux/arch/m68knommu/kernel/process.c&n; *&n; *  Copyright (C) 1998  D. Jeff Dionne &lt;jeff@ryeham.ee.ryerson.ca&gt;,&n; *                      Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; *                      The Silver Hammer Group, Ltd.&n; *&n; *  linux/arch/m68k/kernel/process.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; *&n; *  68060 fixes by Jesper Skov&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
multiline_comment|/*&n; * The idle loop on an H8/300..&n; */
macro_line|#if !defined(CONFIG_H8300H_SIM) &amp;&amp; !defined(CONFIG_H8S_SIM)
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
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sleep&quot;
)paren
suffix:semicolon
id|local_irq_disable
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
macro_line|#else
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
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;jmp @@0&quot;
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sleep&quot;
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;sleep&quot;
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
l_string|&quot;&bslash;nPC: %08lx  Status: %02x&quot;
comma
id|regs-&gt;pc
comma
id|regs-&gt;ccr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nORIG_ER0: %08lx ER0: %08lx ER1: %08lx&quot;
comma
id|regs-&gt;orig_er0
comma
id|regs-&gt;er0
comma
id|regs-&gt;er1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nER2: %08lx ER3: %08lx ER4: %08lx ER5: %08lx&quot;
comma
id|regs-&gt;er2
comma
id|regs-&gt;er3
comma
id|regs-&gt;er4
comma
id|regs-&gt;er5
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nER6&squot; %08lx &quot;
comma
id|regs-&gt;er6
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
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|clone_arg
op_assign
id|flags
op_or
id|CLONE_VM
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov.l sp,er3&bslash;n&bslash;t&quot;
l_string|&quot;sub.l er2,er2&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %2,er1&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1,er0&bslash;n&bslash;t&quot;
l_string|&quot;trapa #0&bslash;n&bslash;t&quot;
l_string|&quot;cmp.l sp,er3&bslash;n&bslash;t&quot;
l_string|&quot;beq 1f&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %4,er0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %3,er1&bslash;n&bslash;t&quot;
l_string|&quot;jsr @er1&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %5,er0&bslash;n&bslash;t&quot;
l_string|&quot;trapa #0&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|__NR_clone
)paren
comma
l_string|&quot;g&quot;
(paren
id|clone_arg
)paren
comma
l_string|&quot;g&quot;
(paren
id|fn
)paren
comma
l_string|&quot;g&quot;
(paren
id|arg
)paren
comma
l_string|&quot;i&quot;
(paren
id|__NR_exit
)paren
suffix:colon
l_string|&quot;er0&quot;
comma
l_string|&quot;er1&quot;
comma
l_string|&quot;er2&quot;
comma
l_string|&quot;er3&quot;
)paren
suffix:semicolon
id|set_fs
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
)brace
multiline_comment|/*&n; * &quot;h8300_fork()&quot;.. By the time we get here, the&n; * non-volatile registers have also been saved on the&n; * stack. We do some ugly pointer stuff here.. (see&n; * also copy_thread)&n; */
DECL|function|h8300_fork
id|asmlinkage
r_int
id|h8300_fork
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|h8300_vfork
id|asmlinkage
r_int
id|h8300_vfork
c_func
(paren
r_struct
id|pt_regs
op_star
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
)brace
DECL|function|h8300_clone
id|asmlinkage
r_int
id|h8300_clone
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
multiline_comment|/* syscall2 puts clone_flags in er1 and usp in er2 */
id|clone_flags
op_assign
id|regs-&gt;er1
suffix:semicolon
id|newsp
op_assign
id|regs-&gt;er2
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
r_return
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
id|childregs-&gt;retpc
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|childregs-&gt;er0
op_assign
l_int|0
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
id|childregs
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
id|dump-&gt;u_ar0
op_assign
(paren
r_struct
id|user_regs_struct
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
op_amp
id|dump-&gt;regs
)paren
)paren
op_minus
(paren
(paren
r_int
)paren
(paren
id|dump
)paren
)paren
)paren
suffix:semicolon
id|dump-&gt;regs.er0
op_assign
id|regs-&gt;er0
suffix:semicolon
id|dump-&gt;regs.er1
op_assign
id|regs-&gt;er1
suffix:semicolon
id|dump-&gt;regs.er2
op_assign
id|regs-&gt;er2
suffix:semicolon
id|dump-&gt;regs.er3
op_assign
id|regs-&gt;er3
suffix:semicolon
id|dump-&gt;regs.er4
op_assign
id|regs-&gt;er4
suffix:semicolon
id|dump-&gt;regs.er5
op_assign
id|regs-&gt;er5
suffix:semicolon
id|dump-&gt;regs.er6
op_assign
id|regs-&gt;er6
suffix:semicolon
id|dump-&gt;regs.orig_er0
op_assign
id|regs-&gt;orig_er0
suffix:semicolon
id|dump-&gt;regs.ccr
op_assign
id|regs-&gt;ccr
suffix:semicolon
id|dump-&gt;regs.pc
op_assign
id|regs-&gt;pc
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
comma
r_int
id|dummy
comma
dot
dot
dot
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
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|dummy
op_minus
l_int|4
)paren
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
r_return
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|tsk-&gt;thread.esp0
)paren
op_member_access_from_pointer
id|pc
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
id|pt_regs
op_star
)paren
id|p-&gt;thread.ksp
)paren
op_member_access_from_pointer
id|er6
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
id|thread_info
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
r_if
c_cond
(paren
op_logical_neg
id|in_sched_functions
c_func
(paren
id|pc
)paren
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
eof
