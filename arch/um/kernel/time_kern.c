multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/unistd.h&quot;
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/spinlock.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/delay.h&quot;
macro_line|#include &quot;asm/irq.h&quot;
macro_line|#include &quot;asm/param.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;mode.h&quot;
DECL|variable|jiffies_64
id|u64
id|jiffies_64
suffix:semicolon
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
DECL|function|hz
r_int
id|hz
c_func
(paren
r_void
)paren
(brace
r_return
id|HZ
suffix:semicolon
)brace
multiline_comment|/* Changed at early boot */
DECL|variable|timer_irq_inited
r_int
id|timer_irq_inited
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* missed_ticks will be modified after kernel memory has been &n; * write-protected, so this puts it in a section which will be left &n; * write-enabled.&n; */
DECL|variable|missed_ticks
r_int
id|__attribute__
(paren
(paren
id|__section__
(paren
l_string|&quot;.unprotected&quot;
)paren
)paren
)paren
id|missed_ticks
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|timer_irq
r_void
id|timer_irq
c_func
(paren
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|current-&gt;thread_info-&gt;cpu
comma
id|ticks
op_assign
id|missed_ticks
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_irq_inited
)paren
(brace
r_return
suffix:semicolon
)brace
id|missed_ticks
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ticks
op_decrement
)paren
(brace
id|do_IRQ
c_func
(paren
id|TIMER_IRQ
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
DECL|function|boot_timer_handler
r_void
id|boot_timer_handler
c_func
(paren
r_int
id|sig
)paren
(brace
r_struct
id|pt_regs
id|regs
suffix:semicolon
id|CHOOSE_MODE
c_func
(paren
(paren
r_void
)paren
(paren
id|UPT_SC
c_func
(paren
op_amp
id|regs.regs
)paren
op_assign
(paren
r_struct
id|sigcontext
op_star
)paren
(paren
op_amp
id|sig
op_plus
l_int|1
)paren
)paren
comma
(paren
r_void
)paren
(paren
id|regs.regs.skas.is_user
op_assign
l_int|0
)paren
)paren
suffix:semicolon
id|do_timer
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
)brace
DECL|function|um_timer
r_void
id|um_timer
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|timer
c_func
(paren
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
DECL|function|um_time
r_int
id|um_time
c_func
(paren
r_int
op_star
id|tloc
)paren
(brace
r_struct
id|timeval
id|now
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|now
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tloc
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|now.tv_sec
comma
id|tloc
)paren
)paren
id|now.tv_sec
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|now.tv_sec
suffix:semicolon
)brace
DECL|function|um_stime
r_int
id|um_stime
c_func
(paren
r_int
op_star
id|tptr
)paren
(brace
r_int
id|value
suffix:semicolon
r_struct
id|timeval
r_new
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|value
comma
id|tptr
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_new
dot
id|tv_sec
op_assign
id|value
suffix:semicolon
r_new
dot
id|tv_usec
op_assign
l_int|0
suffix:semicolon
id|do_settimeofday
c_func
(paren
op_amp
r_new
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* XXX Needs to be moved under sys-i386 */
DECL|function|__delay
r_void
id|__delay
c_func
(paren
id|um_udelay_t
id|time
)paren
(brace
multiline_comment|/* Stolen from the i386 __loop_delay */
r_int
id|d0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 2f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %0&bslash;n&bslash;tjns 2b&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|d0
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|time
)paren
)paren
suffix:semicolon
)brace
DECL|function|__udelay
r_void
id|__udelay
c_func
(paren
id|um_udelay_t
id|usecs
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
id|n
op_assign
(paren
id|loops_per_jiffy
op_star
id|HZ
op_star
id|usecs
)paren
op_div
l_int|1000000
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|__const_udelay
r_void
id|__const_udelay
c_func
(paren
id|um_udelay_t
id|usecs
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
id|n
op_assign
(paren
id|loops_per_jiffy
op_star
id|HZ
op_star
id|usecs
)paren
op_div
l_int|1000000
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|timer_handler
r_void
id|timer_handler
c_func
(paren
r_int
id|sig
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|update_process_times
c_func
(paren
id|user_context
c_func
(paren
id|UPT_SP
c_func
(paren
id|regs
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|current-&gt;thread_info-&gt;cpu
op_eq
l_int|0
)paren
(brace
id|timer_irq
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
DECL|variable|timer_spinlock
r_static
id|spinlock_t
id|timer_spinlock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|time_lock
r_void
id|time_lock
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|timer_spinlock
)paren
suffix:semicolon
)brace
DECL|function|time_unlock
r_void
id|time_unlock
c_func
(paren
r_void
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|timer_spinlock
)paren
suffix:semicolon
)brace
DECL|function|timer_init
r_int
id|__init
id|timer_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|CHOOSE_MODE
c_func
(paren
id|user_time_init_tt
c_func
(paren
)paren
comma
id|user_time_init_skas
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|request_irq
c_func
(paren
id|TIMER_IRQ
comma
id|um_timer
comma
id|SA_INTERRUPT
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;timer_init : request_irq failed - &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|timer_irq_inited
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|timer_init
id|__initcall
c_func
(paren
id|timer_init
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
