multiline_comment|/*&n; *  linux/kernel/panic.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * This function is used through-out the kernel (including mm and fs)&n; * to indicate a major problem.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
id|asmlinkage
r_void
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* it&squot;s really int */
DECL|variable|panic_timeout
r_int
id|panic_timeout
suffix:semicolon
DECL|variable|panic_notifier_list
r_struct
id|notifier_block
op_star
id|panic_notifier_list
suffix:semicolon
DECL|function|panic_setup
r_static
r_int
id|__init
id|panic_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|panic_timeout
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;panic=&quot;
comma
id|panic_setup
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;panic - halt the system&n; *&t;@fmt: The text string to print&n; *&n; *&t;Display a message, then perform cleanups. Functions in the panic&n; *&t;notifier list are called after the filesystem cache is flushed (when possible).&n; *&n; *&t;This function never returns.&n; */
DECL|function|panic
id|NORET_TYPE
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
macro_line|#if defined(CONFIG_ARCH_S390)
r_int
r_int
id|caller
op_assign
(paren
r_int
r_int
)paren
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Kernel panic: %s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;In interrupt handler - not syncing&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;pid
)paren
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;In idle task - not syncing&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|notifier_call_chain
c_func
(paren
op_amp
id|panic_notifier_list
comma
l_int|0
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|panic_timeout
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t; &t; * Delay timeout seconds before rebooting the machine. &n;&t;&t; * We can&squot;t use the &quot;normal&quot; timers since we just panicked..&n;&t; &t; */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Rebooting in %d seconds..&quot;
comma
id|panic_timeout
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|panic_timeout
op_star
l_int|1000
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Should we run the reboot notifier. For the moment Im&n;&t;&t; *&t;choosing not too. It might crash, be corrupt or do&n;&t;&t; *&t;more harm than good for other reasons.&n;&t;&t; */
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#ifdef __sparc__
(brace
r_extern
r_int
id|stop_a_enabled
suffix:semicolon
multiline_comment|/* Make sure the user can actually press L1-A */
id|stop_a_enabled
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Press L1-A to return to the boot prom&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_S390)
id|disabled_wait
c_func
(paren
id|caller
)paren
suffix:semicolon
macro_line|#endif
id|__sti
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
(brace
id|CHECK_EMERGENCY_SYNC
)brace
)brace
multiline_comment|/**&n; *&t;print_tainted - return a string to represent the kernel taint state.&n; *&n; *  &squot;P&squot; - Proprietory module has been loaded.&n; *  &squot;F&squot; - Module has been forcibly loaded.&n; *  &squot;S&squot; - SMP with CPUs not designed for SMP.&n; *&n; *&t;The string is overwritten by the next call to print_taint().&n; */
DECL|function|print_tainted
r_const
r_char
op_star
id|print_tainted
c_func
(paren
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tainted
)paren
(brace
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;Tainted: %c%c%c&quot;
comma
id|tainted
op_amp
id|TAINT_PROPRIETORY_MODULE
ques
c_cond
l_char|&squot;P&squot;
suffix:colon
l_char|&squot;G&squot;
comma
id|tainted
op_amp
id|TAINT_FORCED_MODULE
ques
c_cond
l_char|&squot;F&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|tainted
op_amp
id|TAINT_UNSAFE_SMP
ques
c_cond
l_char|&squot;S&squot;
suffix:colon
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
r_else
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;Not tainted&quot;
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
DECL|variable|tainted
r_int
id|tainted
op_assign
l_int|0
suffix:semicolon
eof
