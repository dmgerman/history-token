multiline_comment|/*&n; *  linux/arch/x86-64/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; * &n; *  X86-64 port&n; *&t;Andi Kleen.&n; * &n; *  $Id: process.c,v 1.38 2002/01/15 10:08:03 ak Exp $&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/prctl.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
id|asmlinkage
r_extern
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|kernel_thread_flags
r_int
r_int
id|kernel_thread_flags
op_assign
id|CLONE_VM
op_or
id|CLONE_UNTRACED
suffix:semicolon
DECL|variable|hlt_counter
id|atomic_t
id|hlt_counter
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n; * Powermanagement idle function, if any..&n; */
DECL|variable|pm_idle
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|disable_hlt
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|hlt_counter
)paren
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
id|atomic_dec
c_func
(paren
op_amp
id|hlt_counter
)paren
suffix:semicolon
)brace
DECL|variable|enable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|enable_hlt
)paren
suffix:semicolon
multiline_comment|/*&n; * We use this if we don&squot;t have any better&n; * idle routine..&n; */
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|hlt_counter
)paren
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|safe_halt
c_func
(paren
)paren
suffix:semicolon
r_else
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * On SMP it&squot;s slightly faster (but much more power-consuming!)&n; * to poll the -&gt;need_resched flag instead of waiting for the&n; * cross-CPU IPI to arrive. Use this option with caution.&n; */
DECL|function|poll_idle
r_static
r_void
id|poll_idle
(paren
r_void
)paren
(brace
r_int
id|oldval
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Deal with another CPU just having chosen a thread to&n;&t; * run here:&n;&t; */
id|oldval
op_assign
id|test_and_clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;2:&quot;
l_string|&quot;testl %0,%1;&quot;
l_string|&quot;rep; nop;&quot;
l_string|&quot;je 2b;&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|_TIF_NEED_RESCHED
)paren
comma
l_string|&quot;m&quot;
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
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
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
op_assign
id|pm_idle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idle
)paren
id|idle
op_assign
id|default_idle
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|idle
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This uses new MONITOR/MWAIT instructions on P4 processors with PNI,&n; * which can obviate IPI to trigger checking of need_resched.&n; * We execute MONITOR against need_resched and enter optimized wait state&n; * through MWAIT. Whenever someone changes need_resched, we would be woken&n; * up from MWAIT (without an IPI).&n; */
DECL|function|mwait_idle
r_static
r_void
id|mwait_idle
c_func
(paren
r_void
)paren
(brace
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
r_do
(brace
id|__monitor
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
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
id|__mwait
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
suffix:semicolon
id|clear_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
)brace
)brace
DECL|function|select_idle_routine
r_void
id|__init
id|select_idle_routine
c_func
(paren
r_const
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_static
r_int
id|printed
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_MWAIT
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Skip, if setup has overridden idle.&n;&t;&t; * Also, take care of system with asymmetric CPUs.&n;&t;&t; * Use, mwait_idle only if all cpus support it.&n;&t;&t; * If not, we fallback to default_idle()&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pm_idle
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|printed
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;using mwait in idle threads.&bslash;n&quot;
)paren
suffix:semicolon
id|printed
op_assign
l_int|1
suffix:semicolon
)brace
id|pm_idle
op_assign
id|mwait_idle
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
id|pm_idle
op_assign
id|default_idle
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|idle_setup
r_static
r_int
id|__init
id|idle_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;poll&quot;
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;using polling idle threads.&bslash;n&quot;
)paren
suffix:semicolon
id|pm_idle
op_assign
id|poll_idle
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;idle=&quot;
comma
id|idle_setup
)paren
suffix:semicolon
multiline_comment|/* Prints also some state that isn&squot;t saved in the pt_regs */
DECL|function|__show_regs
r_void
id|__show_regs
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
id|cr0
op_assign
l_int|0L
comma
id|cr2
op_assign
l_int|0L
comma
id|cr3
op_assign
l_int|0L
comma
id|cr4
op_assign
l_int|0L
comma
id|fs
comma
id|gs
comma
id|shadowgs
suffix:semicolon
r_int
r_int
id|fsindex
comma
id|gsindex
suffix:semicolon
r_int
r_int
id|ds
comma
id|cs
comma
id|es
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|print_modules
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pid: %d, comm: %.20s %s %s&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|print_tainted
c_func
(paren
)paren
comma
id|UTS_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RIP: %04lx:[&lt;%016lx&gt;] &quot;
comma
id|regs-&gt;cs
op_amp
l_int|0xffff
comma
id|regs-&gt;rip
)paren
suffix:semicolon
id|printk_address
c_func
(paren
id|regs-&gt;rip
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nRSP: %04lx:%016lx  EFLAGS: %08lx&bslash;n&quot;
comma
id|regs-&gt;ss
comma
id|regs-&gt;rsp
comma
id|regs-&gt;eflags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RAX: %016lx RBX: %016lx RCX: %016lx&bslash;n&quot;
comma
id|regs-&gt;rax
comma
id|regs-&gt;rbx
comma
id|regs-&gt;rcx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RDX: %016lx RSI: %016lx RDI: %016lx&bslash;n&quot;
comma
id|regs-&gt;rdx
comma
id|regs-&gt;rsi
comma
id|regs-&gt;rdi
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RBP: %016lx R08: %016lx R09: %016lx&bslash;n&quot;
comma
id|regs-&gt;rbp
comma
id|regs-&gt;r8
comma
id|regs-&gt;r9
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R10: %016lx R11: %016lx R12: %016lx&bslash;n&quot;
comma
id|regs-&gt;r10
comma
id|regs-&gt;r11
comma
id|regs-&gt;r12
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R13: %016lx R14: %016lx R15: %016lx&bslash;n&quot;
comma
id|regs-&gt;r13
comma
id|regs-&gt;r14
comma
id|regs-&gt;r15
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%ds,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ds
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%cs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cs
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%es,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|es
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fsindex
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|gsindex
)paren
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|fs
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_GS_BASE
comma
id|gs
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|shadowgs
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr0
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr2
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr3, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr3
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr4, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr4
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FS:  %016lx(%04x) GS:%016lx(%04x) knlGS:%016lx&bslash;n&quot;
comma
id|fs
comma
id|fsindex
comma
id|gs
comma
id|gsindex
comma
id|shadowgs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CS:  %04x DS: %04x ES: %04x CR0: %016lx&bslash;n&quot;
comma
id|cs
comma
id|ds
comma
id|es
comma
id|cr0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CR2: %016lx CR3: %016lx CR4: %016lx&bslash;n&quot;
comma
id|cr2
comma
id|cr3
comma
id|cr4
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
id|__show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|show_trace
c_func
(paren
op_amp
id|regs-&gt;rsp
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
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|me-&gt;thread.io_bitmap_ptr
)paren
(brace
r_struct
id|tss_struct
op_star
id|tss
op_assign
id|init_tss
op_plus
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|me-&gt;thread.io_bitmap_ptr
)paren
suffix:semicolon
id|me-&gt;thread.io_bitmap_ptr
op_assign
l_int|NULL
suffix:semicolon
id|tss-&gt;io_bitmap_base
op_assign
id|INVALID_IO_BITMAP_OFFSET
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
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
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_struct
id|thread_info
op_star
id|t
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;flags
op_amp
id|_TIF_ABI_PENDING
)paren
id|t-&gt;flags
op_xor_assign
(paren
id|_TIF_ABI_PENDING
op_or
id|_TIF_IA32
)paren
suffix:semicolon
id|tsk-&gt;thread.debugreg0
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.debugreg1
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.debugreg2
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.debugreg3
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.debugreg6
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;thread.debugreg7
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|tsk-&gt;thread.tls_array
comma
l_int|0
comma
r_sizeof
(paren
id|tsk-&gt;thread.tls_array
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Forget coprocessor state..&n;&t; */
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;used_math
op_assign
l_int|0
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
r_if
c_cond
(paren
id|dead_task-&gt;mm
)paren
(brace
r_if
c_cond
(paren
id|dead_task-&gt;mm-&gt;context.size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: dead process %8s still has LDT? &lt;%p/%d&gt;&bslash;n&quot;
comma
id|dead_task-&gt;comm
comma
id|dead_task-&gt;mm-&gt;context.ldt
comma
id|dead_task-&gt;mm-&gt;context.size
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|set_32bit_tls
r_static
r_inline
r_void
id|set_32bit_tls
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
r_int
id|tls
comma
id|u32
id|addr
)paren
(brace
r_struct
id|user_desc
id|ud
op_assign
(brace
dot
id|base_addr
op_assign
id|addr
comma
dot
id|limit
op_assign
l_int|0xfffff
comma
dot
id|seg_32bit
op_assign
l_int|1
comma
dot
id|limit_in_pages
op_assign
l_int|1
comma
dot
id|useable
op_assign
l_int|1
comma
)brace
suffix:semicolon
r_struct
id|n_desc_struct
op_star
id|desc
op_assign
(paren
r_void
op_star
)paren
id|t-&gt;thread.tls_array
suffix:semicolon
id|desc
op_add_assign
id|tls
suffix:semicolon
id|desc-&gt;a
op_assign
id|LDT_entry_a
c_func
(paren
op_amp
id|ud
)paren
suffix:semicolon
id|desc-&gt;b
op_assign
id|LDT_entry_b
c_func
(paren
op_amp
id|ud
)paren
suffix:semicolon
)brace
DECL|function|read_32bit_tls
r_static
r_inline
id|u32
id|read_32bit_tls
c_func
(paren
r_struct
id|task_struct
op_star
id|t
comma
r_int
id|tls
)paren
(brace
r_struct
id|desc_struct
op_star
id|desc
op_assign
(paren
r_void
op_star
)paren
id|t-&gt;thread.tls_array
suffix:semicolon
id|desc
op_add_assign
id|tls
suffix:semicolon
r_return
id|desc-&gt;base0
op_or
(paren
(paren
(paren
id|u32
)paren
id|desc-&gt;base1
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
(paren
id|u32
)paren
id|desc-&gt;base2
)paren
op_lshift
l_int|24
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets called before we allocate a new thread and copy&n; * the current task into it.&n; */
DECL|function|prepare_to_copy
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|unlazy_fpu
c_func
(paren
id|tsk
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
id|rsp
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
r_int
id|err
suffix:semicolon
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
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
id|childregs-&gt;rax
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;rsp
op_assign
id|rsp
suffix:semicolon
r_if
c_cond
(paren
id|rsp
op_eq
op_complement
l_int|0UL
)paren
(brace
id|childregs-&gt;rsp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
)brace
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;thread.rsp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.rsp0
op_assign
(paren
r_int
r_int
)paren
(paren
id|childregs
op_plus
l_int|1
)paren
suffix:semicolon
id|p-&gt;thread.userrsp
op_assign
id|me-&gt;thread.userrsp
suffix:semicolon
id|set_ti_thread_flag
c_func
(paren
id|p-&gt;thread_info
comma
id|TIF_FORK
)paren
suffix:semicolon
id|p-&gt;thread.fs
op_assign
id|me-&gt;thread.fs
suffix:semicolon
id|p-&gt;thread.gs
op_assign
id|me-&gt;thread.gs
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.gsindex
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.fsindex
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%es,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.es
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%ds,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.ds
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|me-&gt;thread.io_bitmap_ptr
op_ne
l_int|NULL
)paren
)paren
(brace
id|p-&gt;thread.io_bitmap_ptr
op_assign
id|kmalloc
c_func
(paren
id|IO_BITMAP_BYTES
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;thread.io_bitmap_ptr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|p-&gt;thread.io_bitmap_ptr
comma
id|me-&gt;thread.io_bitmap_ptr
comma
id|IO_BITMAP_BYTES
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set a new TLS for the child thread?&n;&t; */
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
(brace
macro_line|#ifdef CONFIG_IA32_EMULATION
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_IA32
)paren
)paren
id|err
op_assign
id|ia32_child_tls
c_func
(paren
id|p
comma
id|childregs
)paren
suffix:semicolon
r_else
macro_line|#endif&t; 
id|err
op_assign
id|do_arch_prctl
c_func
(paren
id|p
comma
id|ARCH_SET_FS
comma
id|childregs-&gt;r8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|err
op_logical_and
id|p-&gt;thread.io_bitmap_ptr
)paren
id|kfree
c_func
(paren
id|p-&gt;thread.io_bitmap_ptr
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * This special macro can be used to load a debugging register&n; */
DECL|macro|loaddebug
mdefine_line|#define loaddebug(thread,r) set_debug(thread-&gt;debugreg ## r, r)
multiline_comment|/*&n; *&t;switch_to(x,y) should switch tasks from x to y.&n; *&n; * This could still be optimized: &n; * - fold all the options into a flag word and test it with a single test.&n; * - could test fs/gs bitsliced&n; */
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
id|prev_p
comma
r_struct
id|task_struct
op_star
id|next_p
)paren
(brace
r_struct
id|thread_struct
op_star
id|prev
op_assign
op_amp
id|prev_p-&gt;thread
comma
op_star
id|next
op_assign
op_amp
id|next_p-&gt;thread
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
op_assign
id|init_tss
op_plus
id|cpu
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|prev_p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reload esp0, LDT and the page table pointer:&n;&t; */
id|tss-&gt;rsp0
op_assign
id|next-&gt;rsp0
suffix:semicolon
multiline_comment|/* &n;&t; * Switch DS and ES.&n;&t; * This won&squot;t pick up thread selector changes, but I guess that is ok.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %%es,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|prev-&gt;es
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;es
op_or
id|prev-&gt;es
)paren
)paren
id|loadsegment
c_func
(paren
id|es
comma
id|next-&gt;es
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ds,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|prev-&gt;ds
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;ds
op_or
id|prev-&gt;ds
)paren
)paren
id|loadsegment
c_func
(paren
id|ds
comma
id|next-&gt;ds
)paren
suffix:semicolon
id|load_TLS
c_func
(paren
id|next
comma
id|cpu
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Switch FS and GS.&n;&t; */
(brace
r_int
id|fsindex
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=g&quot;
(paren
id|fsindex
)paren
)paren
suffix:semicolon
multiline_comment|/* segment register != 0 always requires a reload. &n;&t;&t;   also reload when it has changed. &n;&t;&t;   when prev process used 64bit base always reload&n;&t;&t;   to avoid an information leak. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|fsindex
op_or
id|next-&gt;fsindex
op_or
id|prev-&gt;fs
)paren
)paren
(brace
id|loadsegment
c_func
(paren
id|fs
comma
id|next-&gt;fsindex
)paren
suffix:semicolon
multiline_comment|/* check if the user used a selector != 0&n;&t;                 * if yes clear 64bit base, since overloaded base&n;                         * is always mapped to the Null selector&n;                         */
r_if
c_cond
(paren
id|fsindex
)paren
id|prev-&gt;fs
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* when next process has a 64bit base use it */
r_if
c_cond
(paren
id|next-&gt;fs
)paren
id|wrmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|next-&gt;fs
)paren
suffix:semicolon
id|prev-&gt;fsindex
op_assign
id|fsindex
suffix:semicolon
)brace
(brace
r_int
id|gsindex
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=g&quot;
(paren
id|gsindex
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|gsindex
op_or
id|next-&gt;gsindex
op_or
id|prev-&gt;gs
)paren
)paren
(brace
id|load_gs_index
c_func
(paren
id|next-&gt;gsindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gsindex
)paren
id|prev-&gt;gs
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|next-&gt;gs
)paren
id|wrmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|next-&gt;gs
)paren
suffix:semicolon
id|prev-&gt;gsindex
op_assign
id|gsindex
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Switch the PDA context.&n;&t; */
id|prev-&gt;userrsp
op_assign
id|read_pda
c_func
(paren
id|oldrsp
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|oldrsp
comma
id|next-&gt;userrsp
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|pcurrent
comma
id|next_p
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|kernelstack
comma
(paren
r_int
r_int
)paren
id|next_p-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
id|PDA_STACKOFFSET
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now maybe reload the debug registers&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;debugreg7
)paren
)paren
(brace
id|loaddebug
c_func
(paren
id|next
comma
l_int|0
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|1
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|2
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* no 4 and 5 */
id|loaddebug
c_func
(paren
id|next
comma
l_int|6
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|7
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Handle the IO bitmap &n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|prev-&gt;io_bitmap_ptr
op_logical_or
id|next-&gt;io_bitmap_ptr
)paren
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;io_bitmap_ptr
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 2 cachelines copy ... not good, but not that&n;&t;&t;&t; * bad either. Anyone got something better?&n;&t;&t;&t; * This only affects processes which use ioperm().&n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|tss-&gt;io_bitmap
comma
id|next-&gt;io_bitmap_ptr
comma
id|IO_BITMAP_BYTES
)paren
suffix:semicolon
id|tss-&gt;io_bitmap_base
op_assign
id|IO_BITMAP_OFFSET
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * a bitmap offset pointing outside of the TSS limit&n;&t;&t;&t; * causes a nicely controllable SIGSEGV if a process&n;&t;&t;&t; * tries to use a port IO instruction. The first&n;&t;&t;&t; * sys_ioperm() call sets up the bitmap properly.&n;&t;&t;&t; */
id|tss-&gt;io_bitmap_base
op_assign
id|INVALID_IO_BITMAP_OFFSET
suffix:semicolon
)brace
)brace
r_return
id|prev_p
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
id|asmlinkage
DECL|function|sys_execve
r_int
id|sys_execve
c_func
(paren
r_char
id|__user
op_star
id|name
comma
r_char
id|__user
op_star
id|__user
op_star
id|argv
comma
r_char
id|__user
op_star
id|__user
op_star
id|envp
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
r_return
id|error
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
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|set_personality_64bit
r_void
id|set_personality_64bit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* inherit personality from parent */
multiline_comment|/* Make sure to be in 64bit mode */
id|clear_thread_flag
c_func
(paren
id|TIF_IA32
)paren
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
op_star
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs-&gt;rsp
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
r_void
id|__user
op_star
id|parent_tid
comma
r_void
id|__user
op_star
id|child_tid
comma
r_struct
id|pt_regs
op_star
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
id|regs-&gt;rsp
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
id|parent_tid
comma
id|child_tid
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
id|regs-&gt;rsp
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
id|stack
suffix:semicolon
id|u64
id|fp
comma
id|rip
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
id|stack
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;thread.rsp
template_param
id|stack
op_plus
id|THREAD_SIZE
)paren
r_return
l_int|0
suffix:semicolon
id|fp
op_assign
op_star
(paren
id|u64
op_star
)paren
(paren
id|p-&gt;thread.rsp
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|fp
template_param
(paren
r_int
r_int
)paren
id|stack
op_plus
id|THREAD_SIZE
)paren
r_return
l_int|0
suffix:semicolon
id|rip
op_assign
op_star
(paren
id|u64
op_star
)paren
(paren
id|fp
op_plus
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_sched_functions
c_func
(paren
id|rip
)paren
)paren
r_return
id|rip
suffix:semicolon
id|fp
op_assign
op_star
(paren
id|u64
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
DECL|function|do_arch_prctl
r_int
id|do_arch_prctl
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
id|code
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|doit
op_assign
id|task
op_eq
id|current
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ARCH_SET_GS
suffix:colon
r_if
c_cond
(paren
id|addr
op_ge
id|TASK_SIZE
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* handle small bases via the GDT because that&squot;s faster to &n;&t;&t;   switch. */
r_if
c_cond
(paren
id|addr
op_le
l_int|0xffffffff
)paren
(brace
id|set_32bit_tls
c_func
(paren
id|task
comma
id|GS_TLS
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|doit
)paren
(brace
id|load_TLS
c_func
(paren
op_amp
id|task-&gt;thread
comma
id|cpu
)paren
suffix:semicolon
id|load_gs_index
c_func
(paren
id|GS_TLS_SEL
)paren
suffix:semicolon
)brace
id|task-&gt;thread.gsindex
op_assign
id|GS_TLS_SEL
suffix:semicolon
id|task-&gt;thread.gs
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|task-&gt;thread.gsindex
op_assign
l_int|0
suffix:semicolon
id|task-&gt;thread.gs
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|doit
)paren
(brace
id|load_gs_index
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
id|checking_wrmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_SET_FS
suffix:colon
multiline_comment|/* Not strictly needed for fs, but do it for symmetry&n;&t;&t;   with gs */
r_if
c_cond
(paren
id|addr
op_ge
id|TASK_SIZE
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* handle small bases via the GDT because that&squot;s faster to &n;&t;&t;   switch. */
r_if
c_cond
(paren
id|addr
op_le
l_int|0xffffffff
)paren
(brace
id|set_32bit_tls
c_func
(paren
id|task
comma
id|FS_TLS
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|doit
)paren
(brace
id|load_TLS
c_func
(paren
op_amp
id|task-&gt;thread
comma
id|cpu
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|FS_TLS_SEL
)paren
)paren
suffix:semicolon
)brace
id|task-&gt;thread.fsindex
op_assign
id|FS_TLS_SEL
suffix:semicolon
id|task-&gt;thread.fs
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|task-&gt;thread.fsindex
op_assign
l_int|0
suffix:semicolon
id|task-&gt;thread.fs
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|doit
)paren
(brace
multiline_comment|/* set the selector to 0 to not confuse&n;&t;&t;&t;&t;   __switch_to */
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%fs&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|checking_wrmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|addr
)paren
suffix:semicolon
)brace
)brace
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_GET_FS
suffix:colon
(brace
r_int
r_int
id|base
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.fsindex
op_eq
id|FS_TLS_SEL
)paren
id|base
op_assign
id|read_32bit_tls
c_func
(paren
id|task
comma
id|FS_TLS
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|doit
)paren
(brace
id|rdmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|base
)paren
suffix:semicolon
)brace
r_else
id|base
op_assign
id|task-&gt;thread.fs
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|base
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|ARCH_GET_GS
suffix:colon
(brace
r_int
r_int
id|base
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.gsindex
op_eq
id|GS_TLS_SEL
)paren
id|base
op_assign
id|read_32bit_tls
c_func
(paren
id|task
comma
id|GS_TLS
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|doit
)paren
(brace
id|rdmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|base
)paren
suffix:semicolon
)brace
r_else
id|base
op_assign
id|task-&gt;thread.gs
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|base
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_arch_prctl
r_int
id|sys_arch_prctl
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|do_arch_prctl
c_func
(paren
id|current
comma
id|code
comma
id|addr
)paren
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
op_star
id|pp
comma
id|ptregs
suffix:semicolon
id|pp
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|tsk-&gt;thread.rsp0
)paren
suffix:semicolon
op_decrement
id|pp
suffix:semicolon
id|ptregs
op_assign
op_star
id|pp
suffix:semicolon
id|ptregs.cs
op_and_assign
l_int|0xffff
suffix:semicolon
id|ptregs.ss
op_and_assign
l_int|0xffff
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
eof
