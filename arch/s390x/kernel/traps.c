multiline_comment|/*&n; *  arch/s390/kernel/traps.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *&n; *  Derived from &quot;arch/i386/kernel/traps.c&quot;&n; *    Copyright (C) 1991, 1992 Linus Torvalds&n; */
multiline_comment|/*&n; * &squot;Traps.c&squot; handles hardware traps and faults after we have saved some&n; * state in &squot;asm.s&squot;.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#if CONFIG_REMOTE_DEBUG
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
multiline_comment|/* Called from entry.S only */
r_extern
r_void
id|handle_per_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|typedef|pgm_check_handler_t
r_typedef
r_void
id|pgm_check_handler_t
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|pgm_check_table
id|pgm_check_handler_t
op_star
id|pgm_check_table
(braket
l_int|128
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
macro_line|#ifdef CONFIG_PROCESS_DEBUG
DECL|variable|sysctl_userprocess_debug
r_int
id|sysctl_userprocess_debug
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|sysctl_userprocess_debug
r_int
id|sysctl_userprocess_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_extern
id|pgm_check_handler_t
id|do_protection_exception
suffix:semicolon
r_extern
id|pgm_check_handler_t
id|do_segment_exception
suffix:semicolon
r_extern
id|pgm_check_handler_t
id|do_region_exception
suffix:semicolon
r_extern
id|pgm_check_handler_t
id|do_page_exception
suffix:semicolon
macro_line|#ifdef CONFIG_PFAULT
r_extern
r_int
id|pfault_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pfault_fini
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pfault_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|__u16
id|error_code
)paren
suffix:semicolon
DECL|variable|ext_int_pfault
r_static
id|ext_int_info_t
id|ext_int_pfault
suffix:semicolon
macro_line|#endif
DECL|variable|kstack_depth_to_print
r_static
r_int
id|kstack_depth_to_print
op_assign
l_int|20
suffix:semicolon
multiline_comment|/*&n; * If the address is either in the .text section of the&n; * kernel, or in the vmalloc&squot;ed module regions, it *may* &n; * be the address of a calling routine&n; */
r_extern
r_char
id|_stext
comma
id|_etext
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
multiline_comment|/* FIXME: Accessed without a lock --RR */
r_extern
r_struct
id|list_head
id|modules
suffix:semicolon
DECL|function|kernel_text_address
r_static
r_inline
r_int
id|kernel_text_address
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|module
op_star
id|mod
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
op_amp
id|_stext
op_logical_and
id|addr
op_le
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
r_return
l_int|1
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|mod
comma
op_amp
id|modules
comma
id|list
)paren
(brace
multiline_comment|/* mod_bound tests for addr being inside the vmalloc&squot;ed&n;&t;&t; * module area. Of course it&squot;d be better to test only&n;&t;&t; * for the .text subset... */
r_if
c_cond
(paren
id|mod_bound
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
l_int|0
comma
id|mod
)paren
)paren
(brace
id|retval
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else
DECL|function|kernel_text_address
r_static
r_inline
r_int
id|kernel_text_address
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
op_amp
id|_stext
op_logical_and
id|addr
op_le
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|show_trace
r_void
id|show_trace
c_func
(paren
r_int
r_int
op_star
id|stack
)paren
(brace
r_int
r_int
id|backchain
comma
id|low_addr
comma
id|high_addr
comma
id|ret_addr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack
)paren
id|stack
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|stack
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Call Trace: &quot;
)paren
suffix:semicolon
id|low_addr
op_assign
(paren
r_int
r_int
)paren
id|stack
suffix:semicolon
id|high_addr
op_assign
(paren
id|low_addr
op_amp
(paren
op_minus
id|THREAD_SIZE
)paren
)paren
op_plus
id|THREAD_SIZE
suffix:semicolon
multiline_comment|/* Skip the first frame (biased stack) */
id|backchain
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|low_addr
suffix:semicolon
multiline_comment|/* Print up to 8 lines */
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
r_if
c_cond
(paren
id|backchain
OL
id|low_addr
op_logical_or
id|backchain
op_ge
id|high_addr
)paren
r_break
suffix:semicolon
id|ret_addr
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|backchain
op_plus
l_int|112
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kernel_text_address
c_func
(paren
id|ret_addr
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|3
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n   &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[&lt;%016lx&gt;] &quot;
comma
id|ret_addr
)paren
suffix:semicolon
id|low_addr
op_assign
id|backchain
suffix:semicolon
id|backchain
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|backchain
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_trace_task
r_void
id|show_trace_task
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
multiline_comment|/*&n;&t; * We can&squot;t print the backtrace of a running process. It is&n;&t; * unreliable at best and can cause kernel oopses.&n;&t; */
r_if
c_cond
(paren
id|tsk-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
suffix:semicolon
id|show_trace
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|tsk-&gt;thread.ksp
)paren
suffix:semicolon
)brace
DECL|function|show_stack
r_void
id|show_stack
c_func
(paren
r_int
r_int
op_star
id|sp
)paren
(brace
r_int
r_int
op_star
id|stack
suffix:semicolon
r_int
id|i
suffix:semicolon
singleline_comment|// debugging aid: &quot;show_stack(NULL);&quot; prints the
singleline_comment|// back trace for this cpu.
r_if
c_cond
(paren
id|sp
op_eq
l_int|NULL
)paren
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|sp
suffix:semicolon
id|stack
op_assign
id|sp
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
id|kstack_depth_to_print
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|addr_t
)paren
id|stack
op_amp
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|4
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n       &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%016lx &quot;
comma
op_star
id|stack
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
id|show_trace
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The architecture-independent dump_stack generator&n; */
DECL|function|dump_stack
r_void
id|dump_stack
c_func
(paren
r_void
)paren
(brace
id|show_stack
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|show_registers
r_void
id|show_registers
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|mm_segment_t
id|old_fs
suffix:semicolon
r_char
op_star
id|mode
suffix:semicolon
r_int
id|i
suffix:semicolon
id|mode
op_assign
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
ques
c_cond
l_string|&quot;User&quot;
suffix:colon
l_string|&quot;Krnl&quot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s PSW : %016lx %016lx&bslash;n&quot;
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
id|printk
c_func
(paren
l_string|&quot;%s GPRS: %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|mode
comma
id|regs-&gt;gprs
(braket
l_int|0
)braket
comma
id|regs-&gt;gprs
(braket
l_int|1
)braket
comma
id|regs-&gt;gprs
(braket
l_int|2
)braket
comma
id|regs-&gt;gprs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|4
)braket
comma
id|regs-&gt;gprs
(braket
l_int|5
)braket
comma
id|regs-&gt;gprs
(braket
l_int|6
)braket
comma
id|regs-&gt;gprs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|8
)braket
comma
id|regs-&gt;gprs
(braket
l_int|9
)braket
comma
id|regs-&gt;gprs
(braket
l_int|10
)braket
comma
id|regs-&gt;gprs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|12
)braket
comma
id|regs-&gt;gprs
(braket
l_int|13
)braket
comma
id|regs-&gt;gprs
(braket
l_int|14
)braket
comma
id|regs-&gt;gprs
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s ACRS: %08x %08x %08x %08x&bslash;n&quot;
comma
id|mode
comma
id|regs-&gt;acrs
(braket
l_int|0
)braket
comma
id|regs-&gt;acrs
(braket
l_int|1
)braket
comma
id|regs-&gt;acrs
(braket
l_int|2
)braket
comma
id|regs-&gt;acrs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|4
)braket
comma
id|regs-&gt;acrs
(braket
l_int|5
)braket
comma
id|regs-&gt;acrs
(braket
l_int|6
)braket
comma
id|regs-&gt;acrs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|8
)braket
comma
id|regs-&gt;acrs
(braket
l_int|9
)braket
comma
id|regs-&gt;acrs
(braket
l_int|10
)braket
comma
id|regs-&gt;acrs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;           %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|12
)braket
comma
id|regs-&gt;acrs
(braket
l_int|13
)braket
comma
id|regs-&gt;acrs
(braket
l_int|14
)braket
comma
id|regs-&gt;acrs
(braket
l_int|15
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Print the first 20 byte of the instruction stream at the&n;&t; * time of the fault.&n;&t; */
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
r_else
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s Code: &quot;
comma
id|mode
)paren
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
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|c
comma
(paren
r_char
op_star
)paren
(paren
id|regs-&gt;psw.addr
op_plus
id|i
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; Bad PSW.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|c
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* This is called from fs/proc/array.c */
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
id|buf
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
id|regs
op_assign
id|__KSTK_PTREGS
c_func
(paren
id|task
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;task: %016lx, ksp: %016lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|task
comma
id|task-&gt;thread.ksp
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;User PSW : %016lx %016lx&bslash;n&quot;
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
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;User GPRS: %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|0
)braket
comma
id|regs-&gt;gprs
(braket
l_int|1
)braket
comma
id|regs-&gt;gprs
(braket
l_int|2
)braket
comma
id|regs-&gt;gprs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;           %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|4
)braket
comma
id|regs-&gt;gprs
(braket
l_int|5
)braket
comma
id|regs-&gt;gprs
(braket
l_int|6
)braket
comma
id|regs-&gt;gprs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;           %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|8
)braket
comma
id|regs-&gt;gprs
(braket
l_int|9
)braket
comma
id|regs-&gt;gprs
(braket
l_int|10
)braket
comma
id|regs-&gt;gprs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;           %016lx %016lx %016lx %016lx&bslash;n&quot;
comma
id|regs-&gt;gprs
(braket
l_int|12
)braket
comma
id|regs-&gt;gprs
(braket
l_int|13
)braket
comma
id|regs-&gt;gprs
(braket
l_int|14
)braket
comma
id|regs-&gt;gprs
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;User ACRS: %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|0
)braket
comma
id|regs-&gt;acrs
(braket
l_int|1
)braket
comma
id|regs-&gt;acrs
(braket
l_int|2
)braket
comma
id|regs-&gt;acrs
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;           %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|4
)braket
comma
id|regs-&gt;acrs
(braket
l_int|5
)braket
comma
id|regs-&gt;acrs
(braket
l_int|6
)braket
comma
id|regs-&gt;acrs
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;           %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|8
)braket
comma
id|regs-&gt;acrs
(braket
l_int|9
)braket
comma
id|regs-&gt;acrs
(braket
l_int|10
)braket
comma
id|regs-&gt;acrs
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;           %08x %08x %08x %08x&bslash;n&quot;
comma
id|regs-&gt;acrs
(braket
l_int|12
)braket
comma
id|regs-&gt;acrs
(braket
l_int|13
)braket
comma
id|regs-&gt;acrs
(braket
l_int|14
)braket
comma
id|regs-&gt;acrs
(braket
l_int|15
)braket
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|variable|die_lock
id|spinlock_t
id|die_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|die
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %04lx&bslash;n&quot;
comma
id|str
comma
id|err
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|do_trap
r_static
r_void
r_inline
id|do_trap
c_func
(paren
r_int
id|interruption_code
comma
r_int
id|signr
comma
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
id|siginfo_t
op_star
id|info
)paren
(brace
multiline_comment|/*&n;&t; * We got all needed information from the lowcore and can&n;&t; * now safely switch on interrupts.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|tsk-&gt;thread.trap_no
op_assign
id|interruption_code
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|info
)paren
id|force_sig_info
c_func
(paren
id|signr
comma
id|info
comma
id|tsk
)paren
suffix:semicolon
r_else
id|force_sig
c_func
(paren
id|signr
comma
id|tsk
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SYSCTL
macro_line|#ifdef CONFIG_PROCESS_DEBUG
id|printk
c_func
(paren
l_string|&quot;User process fault: interruption code 0x%lX&bslash;n&quot;
comma
id|interruption_code
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
r_if
c_cond
(paren
id|sysctl_userprocess_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;User process fault: interruption code 0x%lX&bslash;n&quot;
comma
id|interruption_code
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
r_int
r_int
id|fixup
op_assign
id|search_exception_table
c_func
(paren
id|regs-&gt;psw.addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fixup
)paren
id|regs-&gt;psw.addr
op_assign
id|fixup
suffix:semicolon
r_else
id|die
c_func
(paren
id|str
comma
id|regs
comma
id|interruption_code
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_check_address
r_static
r_inline
r_void
op_star
id|get_check_address
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|regs-&gt;psw.addr
op_minus
id|S390_lowcore.pgm_ilc
)paren
suffix:semicolon
)brace
DECL|function|do_debugger_trap
r_int
id|do_debugger_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|signal
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
(brace
id|force_sig
c_func
(paren
id|signal
comma
id|current
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
macro_line|#if CONFIG_REMOTE_DEBUG
r_if
c_cond
(paren
id|gdb_stub_initialised
)paren
(brace
id|gdb_stub_handle_exception
c_func
(paren
id|regs
comma
id|signal
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DO_ERROR
mdefine_line|#define DO_ERROR(signr, str, name) &bslash;&n;asmlinkage void name(struct pt_regs * regs, long interruption_code) &bslash;&n;{ &bslash;&n;&t;do_trap(interruption_code, signr, str, regs, NULL); &bslash;&n;}
DECL|macro|DO_ERROR_INFO
mdefine_line|#define DO_ERROR_INFO(signr, str, name, sicode, siaddr) &bslash;&n;asmlinkage void name(struct pt_regs * regs, long interruption_code) &bslash;&n;{ &bslash;&n;        siginfo_t info; &bslash;&n;        info.si_signo = signr; &bslash;&n;        info.si_errno = 0; &bslash;&n;        info.si_code = sicode; &bslash;&n;        info.si_addr = (void *)siaddr; &bslash;&n;        do_trap(interruption_code, signr, str, regs, &amp;info); &bslash;&n;}
id|DO_ERROR
c_func
(paren
id|SIGSEGV
comma
l_string|&quot;Unknown program exception&quot;
comma
id|default_trap_handler
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGBUS
comma
l_string|&quot;addressing exception&quot;
comma
id|addressing_exception
comma
id|BUS_ADRERR
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGILL
comma
l_string|&quot;execute exception&quot;
comma
id|execute_exception
comma
id|ILL_ILLOPN
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGFPE
comma
l_string|&quot;fixpoint divide exception&quot;
comma
id|divide_exception
comma
id|FPE_INTDIV
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGILL
comma
l_string|&quot;operand exception&quot;
comma
id|operand_exception
comma
id|ILL_ILLOPN
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGILL
comma
l_string|&quot;privileged operation&quot;
comma
id|privileged_op
comma
id|ILL_PRVOPC
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGILL
comma
l_string|&quot;special operation exception&quot;
comma
id|special_op_exception
comma
id|ILL_ILLOPN
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGILL
comma
l_string|&quot;specification exception&quot;
comma
id|specification_exception
comma
id|ILL_ILLOPN
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
id|DO_ERROR_INFO
c_func
(paren
id|SIGILL
comma
l_string|&quot;translation exception&quot;
comma
id|translation_exception
comma
id|ILL_ILLOPN
comma
id|get_check_address
c_func
(paren
id|regs
)paren
)paren
r_static
r_inline
r_void
DECL|function|do_fp_trap
id|do_fp_trap
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|location
comma
r_int
id|fpc
comma
r_int
id|interruption_code
)paren
(brace
id|siginfo_t
id|si
suffix:semicolon
id|si.si_signo
op_assign
id|SIGFPE
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_addr
op_assign
id|location
suffix:semicolon
id|si.si_code
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FPC[2] is Data Exception Code */
r_if
c_cond
(paren
(paren
id|fpc
op_amp
l_int|0x00000300
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* bits 6 and 7 of DXC are 0 iff IEEE exception */
r_if
c_cond
(paren
id|fpc
op_amp
l_int|0x8000
)paren
multiline_comment|/* invalid fp operation */
id|si.si_code
op_assign
id|FPE_FLTINV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fpc
op_amp
l_int|0x4000
)paren
multiline_comment|/* div by 0 */
id|si.si_code
op_assign
id|FPE_FLTDIV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fpc
op_amp
l_int|0x2000
)paren
multiline_comment|/* overflow */
id|si.si_code
op_assign
id|FPE_FLTOVF
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fpc
op_amp
l_int|0x1000
)paren
multiline_comment|/* underflow */
id|si.si_code
op_assign
id|FPE_FLTUND
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fpc
op_amp
l_int|0x0800
)paren
multiline_comment|/* inexact */
id|si.si_code
op_assign
id|FPE_FLTRES
suffix:semicolon
)brace
id|current-&gt;thread.ieee_instruction_pointer
op_assign
(paren
id|addr_t
)paren
id|location
suffix:semicolon
id|do_trap
c_func
(paren
id|interruption_code
comma
id|SIGFPE
comma
l_string|&quot;floating point exception&quot;
comma
id|regs
comma
op_amp
id|si
)paren
suffix:semicolon
)brace
DECL|function|illegal_op
id|asmlinkage
r_void
id|illegal_op
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|interruption_code
)paren
(brace
id|__u8
id|opcode
(braket
l_int|6
)braket
suffix:semicolon
id|__u16
op_star
id|location
suffix:semicolon
r_int
id|do_sig
op_assign
l_int|0
suffix:semicolon
id|location
op_assign
(paren
id|__u16
op_star
)paren
id|get_check_address
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We got all needed information from the lowcore and can&n;&t; * now safely switch on interrupts.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* WARNING don&squot;t change this check back to */
multiline_comment|/* int problem_state=(regs-&gt;psw.mask &amp; PSW_MASK_PSTATE); */
multiline_comment|/* &amp; then doing if(problem_state) an int is too small for this */
multiline_comment|/* check on 64 bit. */
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
(brace
id|get_user
c_func
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
comma
id|location
)paren
suffix:semicolon
)brace
r_else
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_assign
op_star
(paren
(paren
id|__u16
op_star
)paren
id|location
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
(paren
id|__u16
op_star
)paren
id|opcode
)paren
op_eq
id|S390_BREAKPOINT_U16
)paren
(brace
r_if
c_cond
(paren
id|do_debugger_trap
c_func
(paren
id|regs
comma
id|SIGTRAP
)paren
)paren
(brace
id|do_sig
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|do_sig
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|do_sig
)paren
id|do_trap
c_func
(paren
id|interruption_code
comma
id|SIGILL
comma
l_string|&quot;illegal operation&quot;
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|data_exception
id|asmlinkage
r_void
id|data_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|interruption_code
)paren
(brace
id|__u16
op_star
id|location
suffix:semicolon
id|location
op_assign
(paren
id|__u16
op_star
)paren
id|get_check_address
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We got all needed information from the lowcore and can&n;&t; * now safely switch on interrupts.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;stfpc %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|current-&gt;thread.fp_regs.fpc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;thread.fp_regs.fpc
op_amp
id|FPC_DXC_MASK
)paren
id|do_fp_trap
c_func
(paren
id|regs
comma
id|location
comma
id|current-&gt;thread.fp_regs.fpc
comma
id|interruption_code
)paren
suffix:semicolon
r_else
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
id|ILL_ILLOPN
suffix:semicolon
id|info.si_addr
op_assign
id|location
suffix:semicolon
id|do_trap
c_func
(paren
id|interruption_code
comma
id|SIGILL
comma
l_string|&quot;data exception&quot;
comma
id|regs
comma
op_amp
id|info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* init is done in lowcore.S and head.S */
DECL|function|trap_init
r_void
id|__init
id|trap_init
c_func
(paren
r_void
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|pgm_check_table
(braket
id|i
)braket
op_assign
op_amp
id|default_trap_handler
suffix:semicolon
id|pgm_check_table
(braket
l_int|1
)braket
op_assign
op_amp
id|illegal_op
suffix:semicolon
id|pgm_check_table
(braket
l_int|2
)braket
op_assign
op_amp
id|privileged_op
suffix:semicolon
id|pgm_check_table
(braket
l_int|3
)braket
op_assign
op_amp
id|execute_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|4
)braket
op_assign
op_amp
id|do_protection_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|5
)braket
op_assign
op_amp
id|addressing_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|6
)braket
op_assign
op_amp
id|specification_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|7
)braket
op_assign
op_amp
id|data_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|9
)braket
op_assign
op_amp
id|divide_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x12
)braket
op_assign
op_amp
id|translation_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x13
)braket
op_assign
op_amp
id|special_op_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x15
)braket
op_assign
op_amp
id|operand_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x10
)braket
op_assign
op_amp
id|do_segment_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x11
)braket
op_assign
op_amp
id|do_page_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x1C
)braket
op_assign
op_amp
id|privileged_op
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x38
)braket
op_assign
op_amp
id|addressing_exception
suffix:semicolon
id|pgm_check_table
(braket
l_int|0x3B
)braket
op_assign
op_amp
id|do_region_exception
suffix:semicolon
macro_line|#ifdef CONFIG_PFAULT
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
(brace
multiline_comment|/* request the 0x2603 external interrupt */
r_if
c_cond
(paren
id|register_early_external_interrupt
c_func
(paren
l_int|0x2603
comma
id|pfault_interrupt
comma
op_amp
id|ext_int_pfault
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t request external interrupt 0x2603&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Try to get pfault pseudo page faults going.&n;&t;&t; */
r_if
c_cond
(paren
id|pfault_init
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Tough luck, no pfault. */
id|unregister_early_external_interrupt
c_func
(paren
l_int|0x2603
comma
id|pfault_interrupt
comma
op_amp
id|ext_int_pfault
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
DECL|function|handle_per_exception
r_void
id|handle_per_exception
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_PSTATE
)paren
(brace
id|per_struct
op_star
id|per_info
op_assign
op_amp
id|current-&gt;thread.per_info
suffix:semicolon
id|per_info-&gt;lowcore.words.perc_atmid
op_assign
id|S390_lowcore.per_perc_atmid
suffix:semicolon
id|per_info-&gt;lowcore.words.address
op_assign
id|S390_lowcore.per_address
suffix:semicolon
id|per_info-&gt;lowcore.words.access_id
op_assign
id|S390_lowcore.per_access_id
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_debugger_trap
c_func
(paren
id|regs
comma
id|SIGTRAP
)paren
)paren
(brace
multiline_comment|/* I&squot;ve seen this possibly a task structure being reused ? */
id|printk
c_func
(paren
l_string|&quot;Spurious per exception detected&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;switching off per tracing for this task.&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* Hopefully switching off per tracing will help us survive */
id|regs-&gt;psw.mask
op_and_assign
op_complement
id|PSW_MASK_PER
suffix:semicolon
)brace
)brace
eof
