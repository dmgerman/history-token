multiline_comment|/*&n; *  linux/arch/arm/kernel/process.c&n; *&n; *  Copyright (C) 1996-2000 Russell King - Converted to ARM.&n; *  Original Copyright (C) 1995  Linus Torvalds&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/kallsyms.h&gt;
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
macro_line|#include &lt;asm/arch/system.h&gt;
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
id|arch_idle
c_func
(paren
)paren
suffix:semicolon
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
id|preempt_disable
c_func
(paren
)paren
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
id|preempt_enable
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
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
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
multiline_comment|/*&n;&t; * Now call the architecture specific reboot code.&n;&t; */
id|arch_reset
c_func
(paren
id|reboot_mode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Whoops - the architecture was unable to reboot.&n;&t; * Tell the user!&n;&t; */
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
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
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
id|print_symbol
c_func
(paren
l_string|&quot;PC is at %s&bslash;n&quot;
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;LR is at %s&bslash;n&quot;
comma
id|regs-&gt;ARM_lr
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
l_string|&quot;  IRQs o%s  FIQs o%s  Mode %s%s  Segment %s&bslash;n&quot;
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
id|thumb_mode
c_func
(paren
id|regs
)paren
ques
c_cond
l_string|&quot; (T)&quot;
suffix:colon
l_string|&quot;&quot;
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
(brace
r_int
r_int
id|ctrl
comma
id|transbase
comma
id|dac
suffix:semicolon
id|__asm__
(paren
l_string|&quot;&t;mrc p15, 0, %0, c1, c0&bslash;n&quot;
l_string|&quot;&t;mrc p15, 0, %1, c2, c0&bslash;n&quot;
l_string|&quot;&t;mrc p15, 0, %2, c3, c0&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctrl
)paren
comma
l_string|&quot;=r&quot;
(paren
id|transbase
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dac
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Control: %04X  Table: %08X  DAC: %08X&bslash;n&quot;
comma
id|ctrl
comma
id|transbase
comma
id|dac
)paren
suffix:semicolon
)brace
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
DECL|macro|EXTRA_TASK_STRUCT
mdefine_line|#define EXTRA_TASK_STRUCT&t;4
DECL|macro|ll_alloc_task_struct
mdefine_line|#define ll_alloc_task_struct() ((struct thread_info *) __get_free_pages(GFP_KERNEL,1))
DECL|macro|ll_free_task_struct
mdefine_line|#define ll_free_task_struct(p) free_pages((unsigned long)(p),1)
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
DECL|function|default_fp_init
r_static
r_void
id|default_fp_init
c_func
(paren
r_union
id|fp_state
op_star
id|fp
)paren
(brace
id|memset
c_func
(paren
id|fp
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
)brace
DECL|variable|fp_init
r_void
(paren
op_star
id|fp_init
)paren
(paren
r_union
id|fp_state
op_star
)paren
op_assign
id|default_fp_init
suffix:semicolon
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
id|tsk-&gt;used_math
op_assign
l_int|0
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
id|fp_init
c_func
(paren
op_amp
id|thread-&gt;fpstate
)paren
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
id|stack_start
comma
r_int
r_int
id|stk_sz
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
(paren
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
id|thread
op_plus
id|THREAD_SIZE
op_minus
l_int|8
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
id|childregs-&gt;ARM_r0
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;ARM_sp
op_assign
id|stack_start
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
id|insn.arm
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
id|insn.arm
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
multiline_comment|/*&n; * Shuffle the argument into the correct register before calling the&n; * thread function.  r1 is the thread argument, r2 is the pointer to&n; * the thread function, and r3 points to the exit function.&n; */
r_extern
r_void
id|kernel_thread_helper
c_func
(paren
r_void
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.align&bslash;n&quot;
l_string|&quot;&t;.type&t;kernel_thread_helper, #function&bslash;n&quot;
l_string|&quot;kernel_thread_helper:&bslash;n&quot;
l_string|&quot;&t;mov&t;r0, r1&bslash;n&quot;
l_string|&quot;&t;mov&t;lr, r3&bslash;n&quot;
l_string|&quot;&t;mov&t;pc, r2&bslash;n&quot;
l_string|&quot;&t;.size&t;kernel_thread_helper, . - kernel_thread_helper&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Create a kernel thread.&n; */
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
id|regs.ARM_r1
op_assign
(paren
r_int
r_int
)paren
id|arg
suffix:semicolon
id|regs.ARM_r2
op_assign
(paren
r_int
r_int
)paren
id|fn
suffix:semicolon
id|regs.ARM_r3
op_assign
(paren
r_int
r_int
)paren
id|do_exit
suffix:semicolon
id|regs.ARM_pc
op_assign
(paren
r_int
r_int
)paren
id|kernel_thread_helper
suffix:semicolon
id|regs.ARM_cpsr
op_assign
id|SVC_MODE
suffix:semicolon
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
id|p-&gt;thread_info
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
