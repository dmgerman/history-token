multiline_comment|/*&n; *  arch/s390/kernel/process.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Hartmut Penner (hp@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *&n; *  Derived from &quot;arch/i386/kernel/process.c&quot;&n; *    Copyright (C) 1995, Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
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
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|variable|semaphore_wake_lock
id|spinlock_t
id|semaphore_wake_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_fork&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * The idle loop on a S390...&n; */
DECL|variable|wait_psw
r_static
id|psw_t
id|wait_psw
suffix:semicolon
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|init_idle
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;nice
op_assign
l_int|20
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
id|wait_psw.mask
op_assign
id|_WAIT_PSW_MASK
suffix:semicolon
id|wait_psw.addr
op_assign
(paren
r_int
r_int
)paren
op_logical_and
id|idle_wakeup
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|softirq_pending
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* load wait psw */
id|asm
r_volatile
(paren
l_string|&quot;lpswe %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|wait_psw
)paren
)paren
suffix:semicolon
id|idle_wakeup
suffix:colon
)brace
)brace
multiline_comment|/*&n;  As all the register will only be made displayable to the root&n;  user ( via printk ) or checking if the uid of the user is 0 from&n;  the /proc filesystem please god this will be secure enough DJB.&n;  The lines are given one at a time so as not to chew stack space in&n;  printk on a crash &amp; also for the proc filesystem when you get&n;  0 returned you know you&squot;ve got all the lines&n; */
DECL|function|sprintf_regs
r_static
r_int
id|sprintf_regs
c_func
(paren
r_int
id|line
comma
r_char
op_star
id|buff
comma
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|linelen
op_assign
l_int|0
suffix:semicolon
r_int
id|regno
comma
id|chaincnt
suffix:semicolon
id|u64
id|backchain
comma
id|prev_backchain
comma
id|endchain
suffix:semicolon
id|u64
id|ksp
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|mode
op_assign
l_string|&quot;???&quot;
suffix:semicolon
r_enum
(brace
id|sp_linefeed
comma
id|sp_psw
comma
id|sp_ksp
comma
id|sp_gprs
comma
id|sp_gprs1
comma
id|sp_gprs2
comma
id|sp_gprs3
comma
id|sp_gprs4
comma
id|sp_gprs5
comma
id|sp_gprs6
comma
id|sp_gprs7
comma
id|sp_gprs8
comma
id|sp_acrs
comma
id|sp_acrs1
comma
id|sp_acrs2
comma
id|sp_acrs3
comma
id|sp_acrs4
comma
id|sp_kern_backchain
comma
id|sp_kern_backchain1
)brace
suffix:semicolon
r_if
c_cond
(paren
id|task
)paren
id|ksp
op_assign
id|task-&gt;thread.ksp
suffix:semicolon
r_if
c_cond
(paren
id|regs
op_logical_and
op_logical_neg
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
)paren
id|ksp
op_assign
id|regs-&gt;gprs
(braket
l_int|15
)braket
suffix:semicolon
r_if
c_cond
(paren
id|regs
)paren
id|mode
op_assign
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
ques
c_cond
l_string|&quot;User&quot;
suffix:colon
l_string|&quot;Kernel&quot;
suffix:semicolon
r_switch
c_cond
(paren
id|line
)paren
(brace
r_case
id|sp_linefeed
suffix:colon
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sp_psw
suffix:colon
r_if
c_cond
(paren
id|regs
)paren
(brace
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%s PSW:    %016lx %016lx&bslash;n&quot;
comma
id|mode
comma
(paren
r_int
r_int
)paren
id|regs-&gt;psw.mask
comma
(paren
r_int
r_int
)paren
id|regs-&gt;psw.addr
)paren
suffix:semicolon
)brace
r_else
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;pt_regs=NULL some info unavailable&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sp_ksp
suffix:colon
id|linelen
op_assign
id|sprintf
c_func
(paren
op_amp
id|buff
(braket
id|linelen
)braket
comma
l_string|&quot;task: %016lx ksp: %016lx pt_regs: %016lx&bslash;n&quot;
comma
(paren
id|addr_t
)paren
id|task
comma
(paren
id|addr_t
)paren
id|ksp
comma
(paren
id|addr_t
)paren
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sp_gprs
suffix:colon
r_if
c_cond
(paren
id|regs
)paren
(brace
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%s GPRS:&bslash;n&quot;
comma
id|mode
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|sp_gprs1
dot
dot
dot
id|sp_gprs8
suffix:colon
r_if
c_cond
(paren
id|regs
)paren
(brace
id|regno
op_assign
(paren
id|line
op_minus
id|sp_gprs1
)paren
op_star
l_int|2
suffix:semicolon
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%016lx  %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
id|regno
)braket
comma
id|regs-&gt;gprs
(braket
id|regno
op_plus
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|sp_acrs
suffix:colon
r_if
c_cond
(paren
id|regs
)paren
(brace
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%s ACRS:&bslash;n&quot;
comma
id|mode
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|sp_acrs1
dot
dot
dot
id|sp_acrs4
suffix:colon
r_if
c_cond
(paren
id|regs
)paren
(brace
id|regno
op_assign
(paren
id|line
op_minus
id|sp_acrs1
)paren
op_star
l_int|4
suffix:semicolon
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%08x  %08x  %08x  %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
id|regno
)braket
comma
id|regs-&gt;acrs
(braket
id|regno
op_plus
l_int|1
)braket
comma
id|regs-&gt;acrs
(braket
id|regno
op_plus
l_int|2
)braket
comma
id|regs-&gt;acrs
(braket
id|regno
op_plus
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|sp_kern_backchain
suffix:colon
r_if
c_cond
(paren
id|regs
op_logical_and
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_PROBLEM_STATE
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ksp
)paren
id|linelen
op_assign
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;Kernel BackChain          CallChain&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|ksp
)paren
(brace
id|backchain
op_assign
id|ksp
op_amp
id|PSW_ADDR_MASK
suffix:semicolon
id|endchain
op_assign
(paren
(paren
id|backchain
op_amp
(paren
op_minus
id|THREAD_SIZE
)paren
)paren
op_plus
id|THREAD_SIZE
)paren
suffix:semicolon
id|prev_backchain
op_assign
id|backchain
op_minus
l_int|1
suffix:semicolon
id|line
op_sub_assign
id|sp_kern_backchain1
suffix:semicolon
r_for
c_loop
(paren
id|chaincnt
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|chaincnt
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|backchain
op_eq
l_int|0
)paren
op_logical_or
(paren
id|backchain
op_ge
id|endchain
)paren
op_logical_or
(paren
id|chaincnt
op_ge
l_int|8
)paren
op_logical_or
(paren
id|prev_backchain
op_ge
id|backchain
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chaincnt
op_eq
id|line
)paren
(brace
id|linelen
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buff
(braket
id|linelen
)braket
comma
l_string|&quot;       %016lx   [&lt;%016lx&gt;]&bslash;n&quot;
comma
id|backchain
comma
op_star
(paren
id|u64
op_star
)paren
(paren
id|backchain
op_plus
l_int|112
)paren
op_amp
id|PSW_ADDR_MASK
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|prev_backchain
op_assign
id|backchain
suffix:semicolon
id|backchain
op_assign
(paren
op_star
(paren
(paren
id|u64
op_star
)paren
id|backchain
)paren
)paren
op_amp
id|PSW_ADDR_MASK
suffix:semicolon
)brace
)brace
)brace
r_return
id|linelen
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
r_char
id|buff
(braket
l_int|80
)braket
suffix:semicolon
r_int
id|line
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU:    %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, stackpage=%016lX)&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
l_int|4096
op_plus
(paren
id|addr_t
)paren
id|current
)paren
suffix:semicolon
r_for
c_loop
(paren
id|line
op_assign
l_int|0
suffix:semicolon
id|sprintf_regs
c_func
(paren
id|line
comma
id|buff
comma
id|current
comma
id|regs
)paren
suffix:semicolon
id|line
op_increment
)paren
id|printk
c_func
(paren
id|buff
)paren
suffix:semicolon
)brace
DECL|function|task_show_regs
r_char
op_star
id|task_show_regs
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|line
comma
id|len
suffix:semicolon
r_for
c_loop
(paren
id|line
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|line
op_increment
)paren
(brace
id|len
op_assign
id|sprintf_regs
c_func
(paren
id|line
comma
id|buffer
comma
id|task
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
)brace
r_return
id|buffer
suffix:semicolon
)brace
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
id|clone_arg
op_assign
id|flags
op_or
id|CLONE_VM
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;     slgr  2,2&bslash;n&quot;
l_string|&quot;     lgr   3,%1&bslash;n&quot;
l_string|&quot;     lg    4,%6&bslash;n&quot;
multiline_comment|/* load kernel stack ptr of parent */
l_string|&quot;     svc   %b2&bslash;n&quot;
multiline_comment|/* Linux system call*/
l_string|&quot;     clg   4,%6&bslash;n&quot;
multiline_comment|/* compare ksp&squot;s: child or parent ? */
l_string|&quot;     je    0f&bslash;n&quot;
multiline_comment|/* parent - jump*/
l_string|&quot;     lg    15,%6&bslash;n&quot;
multiline_comment|/* fix kernel stack pointer*/
l_string|&quot;     aghi  15,%7&bslash;n&quot;
l_string|&quot;     xc    0(160,15),0(15)&bslash;n&quot;
multiline_comment|/* clear save area */
l_string|&quot;     lgr   2,%4&bslash;n&quot;
multiline_comment|/* load argument*/
l_string|&quot;     basr  14,%5&bslash;n&quot;
multiline_comment|/* call fn*/
l_string|&quot;     svc   %b3&bslash;n&quot;
multiline_comment|/* Linux system call*/
l_string|&quot;0:   lgr   %0,2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|clone_arg
)paren
comma
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
l_string|&quot;d&quot;
(paren
id|arg
)paren
comma
l_string|&quot;a&quot;
(paren
id|fn
)paren
comma
l_string|&quot;i&quot;
(paren
id|__LC_KERNEL_STACK
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|STACK_FRAME_OVERHEAD
)paren
suffix:colon
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_return
id|retval
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
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
id|current-&gt;used_math
op_assign
l_int|0
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_USEDFPU
suffix:semicolon
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
id|new_stackp
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
id|stack_frame
(brace
r_int
r_int
id|back_chain
suffix:semicolon
r_int
r_int
id|eos
suffix:semicolon
r_int
r_int
id|glue1
suffix:semicolon
r_int
r_int
id|glue2
suffix:semicolon
r_int
r_int
id|scratch
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|gprs
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* gprs 6 -15                       */
r_int
r_int
id|fprs
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* fpr 4 and 6                      */
r_int
r_int
id|empty
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#if CONFIG_REMOTE_DEBUG
r_struct
id|gdb_pt_regs
id|childregs
suffix:semicolon
macro_line|#else
r_struct
id|pt_regs
id|childregs
suffix:semicolon
macro_line|#endif
)brace
op_star
id|frame
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
(paren
l_int|4
op_star
id|PAGE_SIZE
op_plus
(paren
r_int
r_int
)paren
id|p
)paren
op_minus
l_int|1
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|stack_frame
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|frame
)paren
op_amp
op_minus
l_int|8L
)paren
suffix:semicolon
id|p-&gt;thread.regs
op_assign
op_amp
id|frame-&gt;childregs
suffix:semicolon
id|p-&gt;thread.ksp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|frame-&gt;childregs
op_assign
op_star
id|regs
suffix:semicolon
id|frame-&gt;childregs.gprs
(braket
l_int|15
)braket
op_assign
id|new_stackp
suffix:semicolon
id|frame-&gt;back_chain
op_assign
id|frame-&gt;eos
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* new return point is ret_from_sys_call */
id|frame-&gt;gprs
(braket
l_int|8
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ret_from_fork
suffix:semicolon
multiline_comment|/* fake return stack for resume(), don&squot;t go back to schedule */
id|frame-&gt;gprs
(braket
l_int|9
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|frame-&gt;childregs.old_ilc
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* We are not single stepping an svc */
multiline_comment|/* save fprs, if used in last task */
id|save_fp_regs
c_func
(paren
op_amp
id|p-&gt;thread.fp_regs
)paren
suffix:semicolon
id|p-&gt;thread.user_seg
op_assign
id|__pa
c_func
(paren
(paren
r_int
r_int
)paren
id|p-&gt;mm-&gt;pgd
)paren
op_or
id|_REGION_TABLE
suffix:semicolon
multiline_comment|/* Don&squot;t copy debug registers */
id|memset
c_func
(paren
op_amp
id|p-&gt;thread.per_info
comma
l_int|0
comma
r_sizeof
(paren
id|p-&gt;thread.per_info
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.gprs
(braket
l_int|15
)braket
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_struct
id|pt_regs
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
r_int
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|clone_flags
op_assign
id|regs.gprs
(braket
l_int|3
)braket
suffix:semicolon
id|newsp
op_assign
id|regs.orig_gpr2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.gprs
(braket
l_int|15
)braket
suffix:semicolon
id|ret
op_assign
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
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * This is trivial, and on the face of it looks like it&n; * could equally well be done in user mode.&n; *&n; * Not so, for quite unobvious reasons - register pressure.&n; * In user mode vfork() cannot have a stack frame, and if&n; * done by calling the &quot;clone()&quot; system call directly, you&n; * do not have enough call-clobbered registers to hold all&n; * the information you need.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
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
id|regs.gprs
(braket
l_int|15
)braket
comma
op_amp
id|regs
comma
l_int|0
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
op_star
)paren
id|regs.orig_gpr2
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
op_star
op_star
)paren
id|regs.gprs
(braket
l_int|3
)braket
comma
(paren
r_char
op_star
op_star
)paren
id|regs.gprs
(braket
l_int|4
)braket
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
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|current-&gt;thread.fp_regs.fpc
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;sr  0,0&bslash;n&bslash;t&quot;
l_string|&quot;sfpc 0,0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;0&quot;
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
multiline_comment|/*&n; * fill in the FPU structure for a core dump.&n; */
DECL|function|dump_fpu
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
id|save_fp_regs
c_func
(paren
id|fpregs
)paren
suffix:semicolon
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
id|regs-&gt;gprs
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
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;regs.gprs
(braket
l_int|0
)braket
comma
id|regs
comma
r_sizeof
(paren
id|s390_regs
)paren
)paren
suffix:semicolon
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;regs.fp_regs
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|dump-&gt;regs.per_info
comma
op_amp
id|current-&gt;thread.per_info
comma
r_sizeof
(paren
id|per_struct
)paren
)paren
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
id|r14
comma
id|r15
comma
id|bc
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
id|r15
op_assign
id|p-&gt;thread.ksp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack_page
op_logical_or
id|r15
OL
id|stack_page
op_logical_or
id|r15
op_ge
l_int|16380
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|bc
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|r15
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|bc
OL
id|stack_page
op_logical_or
id|bc
op_ge
l_int|16380
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|r14
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|bc
op_plus
l_int|112
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r14
OL
id|first_sched
op_logical_or
id|r14
op_ge
id|last_sched
)paren
r_return
id|r14
suffix:semicolon
id|bc
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|bc
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
DECL|macro|last_sched
macro_line|#undef last_sched
DECL|macro|first_sched
macro_line|#undef first_sched
eof
