multiline_comment|/*&n; *  linux/arch/arm26/kernel/process.c&n; *&n; *  Copyright (C) 2003 Ian Molton - adapted for ARM26&n; *  Copyright (C) 1996-2000 Russell King - Converted to ARM.&n; *  Origional Copyright (C) 1995  Linus Torvalds&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_const
r_char
op_star
id|processor_modes
(braket
)braket
suffix:semicolon
r_extern
r_void
id|setup_mm_for_reboot
c_func
(paren
r_char
id|mode
)paren
suffix:semicolon
DECL|variable|hlt_counter
r_static
r_volatile
r_int
id|hlt_counter
suffix:semicolon
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
DECL|function|nohlt_setup
r_static
r_int
id|__init
id|nohlt_setup
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|hlt_counter
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hlt_setup
r_static
r_int
id|__init
id|hlt_setup
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|hlt_counter
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nohlt&quot;
comma
id|nohlt_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;hlt&quot;
comma
id|hlt_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * The following aren&squot;t currently used.&n; */
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
DECL|variable|pm_power_off
r_void
(paren
op_star
id|pm_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * This is our default idle handler.  We need to disable&n; * interrupts here to ensure we don&squot;t miss a wakeup call.&n; */
DECL|function|default_idle
r_void
id|default_idle
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
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|hlt_counter
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The idle thread.  We try to conserve power, while trying to keep&n; * overall latency low.  The architecture specific idle is passed&n; * a value to indicate the level of &quot;idleness&quot; of the system.&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
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
id|leds_event
c_func
(paren
id|led_idle_start
)paren
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
id|leds_event
c_func
(paren
id|led_idle_end
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|reboot_mode
r_static
r_char
id|reboot_mode
op_assign
l_char|&squot;h&squot;
suffix:semicolon
DECL|function|reboot_setup
r_int
id|__init
id|reboot_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|reboot_mode
op_assign
id|str
(braket
l_int|0
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;reboot=&quot;
comma
id|reboot_setup
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
id|leds_event
c_func
(paren
id|led_halted
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
id|leds_event
c_func
(paren
id|led_halted
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pm_power_off
)paren
id|pm_power_off
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
multiline_comment|/*&n;&t; * Clean and disable cache, and turn off interrupts&n;&t; */
id|cpu_proc_fin
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the mm system that we are going to reboot -&n;&t; * we may need it to insert some 1:1 mappings so that&n;&t; * soft boot works.&n;&t; */
id|setup_mm_for_reboot
c_func
(paren
id|reboot_mode
)paren
suffix:semicolon
multiline_comment|/*&n;         * copy branch instruction to reset location and call it&n;         */
op_star
(paren
r_int
r_int
op_star
)paren
l_int|0
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
l_int|0x03800000
suffix:semicolon
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
l_int|0
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Whoops - the architecture was unable to reboot.&n;&t; * Tell the user! Should never happen...&n;&t; */
id|mdelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Reboot failed -- System halted&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
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
r_int
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|condition_codes
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pc : [&lt;%08lx&gt;]    lr : [&lt;%08lx&gt;]    %s&bslash;n&quot;
l_string|&quot;sp : %08lx  ip : %08lx  fp : %08lx&bslash;n&quot;
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
comma
id|regs-&gt;ARM_lr
comma
id|print_tainted
c_func
(paren
)paren
comma
id|regs-&gt;ARM_sp
comma
id|regs-&gt;ARM_ip
comma
id|regs-&gt;ARM_fp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r10: %08lx  r9 : %08lx  r8 : %08lx&bslash;n&quot;
comma
id|regs-&gt;ARM_r10
comma
id|regs-&gt;ARM_r9
comma
id|regs-&gt;ARM_r8
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx&bslash;n&quot;
comma
id|regs-&gt;ARM_r7
comma
id|regs-&gt;ARM_r6
comma
id|regs-&gt;ARM_r5
comma
id|regs-&gt;ARM_r4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx&bslash;n&quot;
comma
id|regs-&gt;ARM_r3
comma
id|regs-&gt;ARM_r2
comma
id|regs-&gt;ARM_r1
comma
id|regs-&gt;ARM_r0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Flags: %c%c%c%c&quot;
comma
id|flags
op_amp
id|PSR_N_BIT
ques
c_cond
l_char|&squot;N&squot;
suffix:colon
l_char|&squot;n&squot;
comma
id|flags
op_amp
id|PSR_Z_BIT
ques
c_cond
l_char|&squot;Z&squot;
suffix:colon
l_char|&squot;z&squot;
comma
id|flags
op_amp
id|PSR_C_BIT
ques
c_cond
l_char|&squot;C&squot;
suffix:colon
l_char|&squot;c&squot;
comma
id|flags
op_amp
id|PSR_V_BIT
ques
c_cond
l_char|&squot;V&squot;
suffix:colon
l_char|&squot;v&squot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  IRQs o%s  FIQs o%s  Mode %s  Segment %s&bslash;n&quot;
comma
id|interrupts_enabled
c_func
(paren
id|regs
)paren
ques
c_cond
l_string|&quot;n&quot;
suffix:colon
l_string|&quot;ff&quot;
comma
id|fast_interrupts_enabled
c_func
(paren
id|regs
)paren
ques
c_cond
l_string|&quot;n&quot;
suffix:colon
l_string|&quot;ff&quot;
comma
id|processor_modes
(braket
id|processor_mode
c_func
(paren
id|regs
)paren
)braket
comma
id|get_fs
c_func
(paren
)paren
op_eq
id|get_ds
c_func
(paren
)paren
ques
c_cond
l_string|&quot;kernel&quot;
suffix:colon
l_string|&quot;user&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_fpregs
r_void
id|show_fpregs
c_func
(paren
r_struct
id|user_fp
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
op_star
id|p
suffix:semicolon
r_char
id|type
suffix:semicolon
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|regs-&gt;fpregs
op_plus
id|i
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|regs-&gt;ftype
(braket
id|i
)braket
)paren
(brace
r_case
l_int|1
suffix:colon
id|type
op_assign
l_char|&squot;f&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|type
op_assign
l_char|&squot;d&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|type
op_assign
l_char|&squot;e&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|type
op_assign
l_char|&squot;?&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;init_flag
)paren
id|type
op_assign
l_char|&squot;?&squot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  f%d(%c): %08lx %08lx %08lx%c&quot;
comma
id|i
comma
id|type
comma
id|p
(braket
l_int|0
)braket
comma
id|p
(braket
l_int|1
)braket
comma
id|p
(braket
l_int|2
)braket
comma
id|i
op_amp
l_int|1
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;FPSR: %08lx FPCR: %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;fpsr
comma
(paren
r_int
r_int
)paren
id|regs-&gt;fpcr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Task structure and kernel stack allocation.&n; */
DECL|variable|thread_info_head
r_static
r_int
r_int
op_star
id|thread_info_head
suffix:semicolon
DECL|variable|nr_thread_info
r_static
r_int
r_int
id|nr_thread_info
suffix:semicolon
r_extern
r_int
r_int
id|get_page_8k
c_func
(paren
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|free_page_8k
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
singleline_comment|// FIXME - is this valid?
DECL|macro|EXTRA_TASK_STRUCT
mdefine_line|#define EXTRA_TASK_STRUCT&t;0
DECL|macro|ll_alloc_task_struct
mdefine_line|#define ll_alloc_task_struct()&t;((struct thread_info *)get_page_8k(GFP_KERNEL))
DECL|macro|ll_free_task_struct
mdefine_line|#define ll_free_task_struct(p)  free_page_8k((unsigned long)(p))
singleline_comment|//FIXME - do we use *task param below looks like we dont, which is ok?
singleline_comment|//FIXME - if EXTRA_TASK_STRUCT is zero we can optimise the below away permanently. *IF* its supposed to be zero.
DECL|function|alloc_thread_info
r_struct
id|thread_info
op_star
id|alloc_thread_info
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_struct
id|thread_info
op_star
id|thread
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|EXTRA_TASK_STRUCT
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
id|thread_info_head
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|thread_info_head
op_assign
(paren
r_int
r_int
op_star
)paren
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|nr_thread_info
op_sub_assign
l_int|1
suffix:semicolon
)brace
id|thread
op_assign
(paren
r_struct
id|thread_info
op_star
)paren
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|thread
)paren
id|thread
op_assign
id|ll_alloc_task_struct
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSRQ
multiline_comment|/*&n;&t; * The stack must be cleared if you want SYSRQ-T to&n;&t; * give sensible stack usage information&n;&t; */
r_if
c_cond
(paren
id|thread
)paren
(brace
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|thread
suffix:semicolon
id|memzero
c_func
(paren
id|p
op_plus
id|KERNEL_STACK_SIZE
comma
id|KERNEL_STACK_SIZE
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|thread
suffix:semicolon
)brace
DECL|function|free_thread_info
r_void
id|free_thread_info
c_func
(paren
r_struct
id|thread_info
op_star
id|thread
)paren
(brace
r_if
c_cond
(paren
id|EXTRA_TASK_STRUCT
op_logical_and
id|nr_thread_info
OL
id|EXTRA_TASK_STRUCT
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|thread
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|thread_info_head
suffix:semicolon
id|thread_info_head
op_assign
id|p
suffix:semicolon
id|nr_thread_info
op_add_assign
l_int|1
suffix:semicolon
)brace
r_else
id|ll_free_task_struct
c_func
(paren
id|thread
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
id|thread_info
op_star
id|thread
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tsk-&gt;thread.debug
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|debug_info
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|thread-&gt;fpstate
comma
l_int|0
comma
r_sizeof
(paren
r_union
id|fp_state
)paren
)paren
suffix:semicolon
id|current-&gt;used_math
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
)brace
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
r_int
DECL|function|copy_thread
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
id|esp
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
id|thread_info
op_star
id|thread
op_assign
id|p-&gt;thread_info
suffix:semicolon
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
id|childregs
op_assign
id|__get_user_regs
c_func
(paren
id|thread
)paren
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;ARM_r0
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;ARM_sp
op_assign
id|esp
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|thread-&gt;cpu_context
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpu_context_save
)paren
)paren
suffix:semicolon
id|thread-&gt;cpu_context.sp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|thread-&gt;cpu_context.pc
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
op_or
id|MODE_SVC26
op_or
id|PSR_I_BIT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the fpe structure for a core dump...&n; */
DECL|function|dump_fpu
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user_fp
op_star
id|fp
)paren
(brace
r_struct
id|thread_info
op_star
id|thread
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
r_int
id|used_math
op_assign
id|current-&gt;used_math
suffix:semicolon
r_if
c_cond
(paren
id|used_math
)paren
id|memcpy
c_func
(paren
id|fp
comma
op_amp
id|thread-&gt;fpstate.soft
comma
r_sizeof
(paren
op_star
id|fp
)paren
)paren
suffix:semicolon
r_return
id|used_math
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
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
id|tsk-&gt;mm-&gt;start_code
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;ARM_sp
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
id|tsk-&gt;mm-&gt;end_code
op_minus
id|tsk-&gt;mm-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
id|tsk-&gt;mm-&gt;brk
op_minus
id|tsk-&gt;mm-&gt;start_data
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|0
)braket
op_assign
id|tsk-&gt;thread.debug.bp
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|1
)braket
op_assign
id|tsk-&gt;thread.debug.bp
(braket
l_int|1
)braket
dot
id|address
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|2
)braket
op_assign
id|tsk-&gt;thread.debug.bp
(braket
l_int|0
)braket
dot
id|insn
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|3
)braket
op_assign
id|tsk-&gt;thread.debug.bp
(braket
l_int|1
)braket
dot
id|insn
suffix:semicolon
id|dump-&gt;u_debugreg
(braket
l_int|4
)braket
op_assign
id|tsk-&gt;thread.debug.nsaved
suffix:semicolon
r_if
c_cond
(paren
id|dump-&gt;start_stack
OL
l_int|0x04000000
)paren
id|dump-&gt;u_ssize
op_assign
(paren
l_int|0x04000000
op_minus
id|dump-&gt;start_stack
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;u_fp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE! Only a kernel-only process(ie the swapper or direct descendants&n; * who haven&squot;t done an &quot;execve()&quot;) should use this: it will work within&n; * a system call from a &quot;real&quot; process, but the process memory space will&n; * not be free&squot;d until both the parent and the child have exited.&n; * FIXME - taken from arm32&n; */
DECL|function|kernel_thread
id|pid_t
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
r_register
r_int
r_int
id|r0
id|asm
c_func
(paren
l_string|&quot;r0&quot;
)paren
op_assign
id|flags
op_or
id|CLONE_VM
op_or
id|CLONE_UNTRACED
suffix:semicolon
r_register
r_int
r_int
id|r1
id|asm
c_func
(paren
l_string|&quot;r1&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_register
id|pid_t
id|__ret
id|asm
c_func
(paren
l_string|&quot;r0&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|__syscall
c_func
(paren
id|clone
)paren
l_string|&quot;       @ kernel_thread sys_clone       &bslash;n&bslash;&n;        movs    %0, r0          @ if we are the child           &bslash;n&bslash;&n;        bne     1f                                              &bslash;n&bslash;&n;        mov     fp, #0          @ ensure that fp is zero        &bslash;n&bslash;&n;        mov     r0, %4                                          &bslash;n&bslash;&n;        mov     lr, pc                                          &bslash;n&bslash;&n;        mov     pc, %3                                          &bslash;n&bslash;&n;        b       sys_exit                                        &bslash;n&bslash;&n;1:      &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|r0
)paren
comma
l_string|&quot;r&quot;
(paren
id|r1
)paren
comma
l_string|&quot;r&quot;
(paren
id|fn
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg
)paren
suffix:colon
l_string|&quot;lr&quot;
)paren
suffix:semicolon
r_return
id|__ret
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
id|lr
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
l_int|4096
op_plus
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|fp
op_assign
id|thread_saved_fp
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|fp
template_param
l_int|4092
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|lr
op_assign
id|pc_pointer
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|fp
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lr
template_param
id|last_sched
)paren
r_return
id|lr
suffix:semicolon
id|fp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|fp
op_minus
l_int|12
)paren
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
