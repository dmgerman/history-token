multiline_comment|/*&n; * lib/bust_spinlocks.c&n; *&n; * Provides a minimal bust_spinlocks for architectures which don&squot;t have one of their own.&n; *&n; * bust_spinlocks() clears any spinlocks which would prevent oops, die(), BUG()&n; * and panic() information from reaching the user.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
r_extern
id|spinlock_t
id|timerlist_lock
suffix:semicolon
DECL|function|bust_spinlocks
r_void
id|bust_spinlocks
c_func
(paren
r_int
id|yes
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|timerlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|yes
)paren
(brace
id|oops_in_progress
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_int
id|loglevel_save
op_assign
id|console_loglevel
suffix:semicolon
macro_line|#ifdef CONFIG_VT
id|unblank_screen
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|oops_in_progress
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * OK, the message is on the console.  Now we call printk()&n;&t;&t; * without oops_in_progress set so that printk() will give klogd&n;&t;&t; * and the blanked console a poke.  Hold onto your hats...&n;&t;&t; */
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
multiline_comment|/* NMI oopser may have shut the console up */
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|console_loglevel
op_assign
id|loglevel_save
suffix:semicolon
)brace
)brace
eof
