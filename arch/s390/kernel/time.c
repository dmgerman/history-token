multiline_comment|/*&n; *  arch/s390/kernel/time.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  Derived from &quot;arch/i386/kernel/time.c&quot;&n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/s390_ext.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* change this if you have some constant time drift */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY     ((unsigned long) 1000000/HZ)
DECL|macro|CLK_TICKS_PER_JIFFY
mdefine_line|#define CLK_TICKS_PER_JIFFY ((unsigned long) USECS_PER_JIFFY &lt;&lt; 12)
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|variable|jiffies_64
id|u64
id|jiffies_64
suffix:semicolon
DECL|variable|ext_int_info_timer
r_static
id|ext_int_info_t
id|ext_int_info_timer
suffix:semicolon
DECL|variable|init_timer_cc
r_static
r_uint64
id|init_timer_cc
suffix:semicolon
r_extern
id|rwlock_t
id|xtime_lock
suffix:semicolon
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|function|tod_to_timeval
r_void
id|tod_to_timeval
c_func
(paren
id|__u64
id|todval
comma
r_struct
id|timeval
op_star
id|xtime
)paren
(brace
r_const
r_int
id|high_bit
op_assign
l_int|0x80000000L
suffix:semicolon
r_const
r_int
id|c_f4240
op_assign
l_int|0xf4240L
suffix:semicolon
r_const
r_int
id|c_7a120
op_assign
l_int|0x7a120
suffix:semicolon
multiline_comment|/* We have to divide the 64 bit value todval by 4096&n;&t; * (because the 2^12 bit is the one that changes every &n;         * microsecond) and then split it into seconds and&n;         * microseconds. A value of max (2^52-1) divided by&n;         * the value 0xF4240 can yield a max result of approx&n;         * (2^32.068). Thats to big to fit into a signed int&n;&t; *   ... hacking time!&n;         */
id|asm
r_volatile
(paren
l_string|&quot;L     2,%1&bslash;n&bslash;t&quot;
l_string|&quot;LR    3,2&bslash;n&bslash;t&quot;
l_string|&quot;SRL   2,12&bslash;n&bslash;t&quot;
l_string|&quot;SLL   3,20&bslash;n&bslash;t&quot;
l_string|&quot;L     4,%O1+4(%R1)&bslash;n&bslash;t&quot;
l_string|&quot;SRL   4,12&bslash;n&bslash;t&quot;
l_string|&quot;OR    3,4&bslash;n&bslash;t&quot;
multiline_comment|/* now R2/R3 contain (todval &gt;&gt; 12) */
l_string|&quot;SR    4,4&bslash;n&bslash;t&quot;
l_string|&quot;CL    2,%2&bslash;n&bslash;t&quot;
l_string|&quot;JL    .+12&bslash;n&bslash;t&quot;
l_string|&quot;S     2,%2&bslash;n&bslash;t&quot;
l_string|&quot;L     4,%3&bslash;n&bslash;t&quot;
l_string|&quot;D     2,%4&bslash;n&bslash;t&quot;
l_string|&quot;OR    3,4&bslash;n&bslash;t&quot;
l_string|&quot;ST    2,%O0+4(%R0)&bslash;n&bslash;t&quot;
l_string|&quot;ST    3,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|xtime
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|todval
)paren
comma
l_string|&quot;m&quot;
(paren
id|c_7a120
)paren
comma
l_string|&quot;m&quot;
(paren
id|high_bit
)paren
comma
l_string|&quot;m&quot;
(paren
id|c_f4240
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
)paren
suffix:semicolon
)brace
DECL|function|do_gettimeoffset
r_static
r_inline
r_int
r_int
id|do_gettimeoffset
c_func
(paren
r_void
)paren
(brace
id|__u64
id|now
suffix:semicolon
id|asm
(paren
l_string|&quot;STCK 0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|now
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|now
op_assign
(paren
id|now
op_minus
id|init_timer_cc
)paren
op_rshift
l_int|12
suffix:semicolon
multiline_comment|/* We require the offset from the latest update of xtime */
id|now
op_sub_assign
(paren
id|__u64
)paren
id|wall_jiffies
op_star
id|USECS_PER_JIFFY
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|now
suffix:semicolon
)brace
multiline_comment|/*&n; * This version of gettimeofday has microsecond resolution.&n; */
DECL|function|do_gettimeofday
r_void
id|do_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|usec
comma
id|sec
suffix:semicolon
id|read_lock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_assign
id|xtime.tv_usec
op_plus
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|read_unlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|usec
op_ge
l_int|1000000
)paren
(brace
id|usec
op_sub_assign
l_int|1000000
suffix:semicolon
id|sec
op_increment
suffix:semicolon
)brace
id|tv-&gt;tv_sec
op_assign
id|sec
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|usec
suffix:semicolon
)brace
DECL|function|do_settimeofday
r_void
id|do_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
id|write_lock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_usec&n;&t; * correctly. However, the value in this location is&n;&t; * is value at the last tick.&n;&t; * Discover what correction gettimeofday&n;&t; * would have done, and then undo it!&n;&t; */
id|tv-&gt;tv_usec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tv-&gt;tv_usec
OL
l_int|0
)paren
(brace
id|tv-&gt;tv_usec
op_add_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_decrement
suffix:semicolon
)brace
id|xtime
op_assign
op_star
id|tv
suffix:semicolon
id|time_adjust
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* stop active adjtime() */
id|time_status
op_or_assign
id|STA_UNSYNC
suffix:semicolon
id|time_maxerror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|time_esterror
op_assign
id|NTP_PHASE_LIMIT
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
macro_line|#ifdef CONFIG_SMP
r_extern
id|__u16
id|boot_cpu_addr
suffix:semicolon
macro_line|#endif
DECL|function|do_comparator_interrupt
r_static
r_void
id|do_comparator_interrupt
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
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
id|cpu
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set clock comparator for next tick&n;&t; */
id|S390_lowcore.jiffy_timer
op_add_assign
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SCKC %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|S390_lowcore.jiffy_timer
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|S390_lowcore.cpu_data.cpu_addr
op_eq
id|boot_cpu_addr
)paren
id|write_lock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|update_process_times
c_func
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S390_lowcore.cpu_data.cpu_addr
op_eq
id|boot_cpu_addr
)paren
(brace
id|do_timer
c_func
(paren
id|regs
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
macro_line|#else
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|irq_exit
c_func
(paren
id|cpu
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the clock comparator on the current CPU&n; */
DECL|function|init_cpu_timer
r_void
id|init_cpu_timer
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cr0
suffix:semicolon
multiline_comment|/* allow clock comparator timer interrupt */
id|asm
r_volatile
(paren
l_string|&quot;STCTL 0,0,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|cr0
)paren
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|cr0
op_or_assign
l_int|0x800
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;LCTL 0,0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|cr0
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|S390_lowcore.jiffy_timer
op_assign
(paren
id|__u64
)paren
id|jiffies
op_star
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|S390_lowcore.jiffy_timer
op_add_assign
id|init_timer_cc
op_plus
id|CLK_TICKS_PER_JIFFY
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;SCKC %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|S390_lowcore.jiffy_timer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the TOD clock and the CPU timer of&n; * the boot cpu.&n; */
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
id|__u64
id|set_time_cc
suffix:semicolon
r_int
id|cc
suffix:semicolon
multiline_comment|/* kick the TOD clock */
id|asm
r_volatile
(paren
l_string|&quot;STCK 0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;IPM  %0&bslash;n&bslash;t&quot;
l_string|&quot;SRL  %0,28&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cc
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|init_timer_cc
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cc
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* clock in set state: all is fine */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* clock in non-set state: FIXME */
id|printk
c_func
(paren
l_string|&quot;time_init: TOD clock in non-set state&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* clock in error state: FIXME */
id|printk
c_func
(paren
l_string|&quot;time_init: TOD clock in error state&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* clock in stopped or not-operational state: FIXME */
id|printk
c_func
(paren
l_string|&quot;time_init: TOD clock stopped/non-operational&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* set xtime */
id|set_time_cc
op_assign
id|init_timer_cc
op_minus
l_int|0x8126d60e46000000LL
op_plus
(paren
l_int|0x3c26700LL
op_star
l_int|1000000
op_star
l_int|4096
)paren
suffix:semicolon
id|tod_to_timeval
c_func
(paren
id|set_time_cc
comma
op_amp
id|xtime
)paren
suffix:semicolon
multiline_comment|/* request the 0x1004 external interrupt */
r_if
c_cond
(paren
id|register_early_external_interrupt
c_func
(paren
l_int|0x1004
comma
id|do_comparator_interrupt
comma
op_amp
id|ext_int_info_timer
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t request external interrupt 0x1004&quot;
)paren
suffix:semicolon
multiline_comment|/* init CPU timer */
id|init_cpu_timer
c_func
(paren
)paren
suffix:semicolon
)brace
eof
