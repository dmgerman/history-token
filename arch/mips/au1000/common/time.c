multiline_comment|/*&n; * Copyright (C) 2001 MontaVista Software, ppopov@mvista.com&n; * Copied and modified Carsten Langgaard&squot;s time.c&n; *&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can distribute it and/or modify it&n; *  under the terms of the GNU General Public License (Version 2) as&n; *  published by the Free Software Foundation.&n; *&n; *  This program is distributed in the hope it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; *  for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Setting up the clock on the MIPS boards.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
r_extern
r_void
id|startup_match20_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|do_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|variable|missed_heart_beats
r_int
r_int
id|missed_heart_beats
op_assign
l_int|0
suffix:semicolon
DECL|variable|r4k_offset
r_static
r_int
r_int
id|r4k_offset
suffix:semicolon
multiline_comment|/* Amount to increment compare reg each time */
DECL|variable|r4k_cur
r_static
r_int
r_int
id|r4k_cur
suffix:semicolon
multiline_comment|/* What counter should be at next timer irq */
r_extern
r_int
r_int
id|mips_counter_frequency
suffix:semicolon
multiline_comment|/* Cycle counter value at the previous timer interrupt.. */
DECL|variable|timerhi
DECL|variable|timerlo
r_static
r_int
r_int
id|timerhi
op_assign
l_int|0
comma
id|timerlo
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|macro|MATCH20_INC
mdefine_line|#define MATCH20_INC 328
r_extern
r_void
id|startup_match20_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|last_pc0
DECL|variable|last_match20
r_static
r_int
r_int
id|last_pc0
comma
id|last_match20
suffix:semicolon
macro_line|#endif
DECL|variable|time_lock
r_static
id|spinlock_t
id|time_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|ack_r4ktimer
r_static
r_inline
r_void
id|ack_r4ktimer
c_func
(paren
r_int
r_int
id|newval
)paren
(brace
id|write_c0_compare
c_func
(paren
id|newval
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * There are a lot of conceptually broken versions of the MIPS timer interrupt&n; * handler floating around.  This one is rather different, but the algorithm&n; * is provably more robust.&n; */
DECL|variable|wtimer
r_int
r_int
id|wtimer
suffix:semicolon
DECL|function|mips_timer_interrupt
r_void
id|mips_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
op_assign
l_int|63
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
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
)paren
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_PM
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unexpected CP0 interrupt&bslash;n&quot;
)paren
suffix:semicolon
id|regs-&gt;cp0_status
op_and_assign
op_complement
id|IE_IRQ5
suffix:semicolon
multiline_comment|/* disable CP0 interrupt */
r_return
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|r4k_offset
op_eq
l_int|0
)paren
r_goto
id|null
suffix:semicolon
r_do
(brace
id|count
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
id|timerhi
op_add_assign
(paren
id|count
OL
id|timerlo
)paren
suffix:semicolon
multiline_comment|/* Wrap around */
id|timerlo
op_assign
id|count
suffix:semicolon
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|r4k_cur
op_add_assign
id|r4k_offset
suffix:semicolon
id|ack_r4ktimer
c_func
(paren
id|r4k_cur
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
r_int
r_int
)paren
id|read_c0_count
c_func
(paren
)paren
op_minus
id|r4k_cur
)paren
OL
l_int|0x7fffffff
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|softirq_pending
c_func
(paren
id|cpu
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
id|null
suffix:colon
id|ack_r4ktimer
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
DECL|function|counter0_irq
r_void
id|counter0_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pc0
suffix:semicolon
r_int
id|time_elapsed
suffix:semicolon
r_static
r_int
id|jiffie_drift
op_assign
l_int|0
suffix:semicolon
id|kstat_cpu
c_func
(paren
l_int|0
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_M20
)paren
(brace
multiline_comment|/* should never happen! */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;counter 0 w status eror&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pc0
op_assign
id|au_readl
c_func
(paren
id|SYS_TOYREAD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pc0
OL
id|last_match20
)paren
(brace
multiline_comment|/* counter overflowed */
id|time_elapsed
op_assign
(paren
l_int|0xffffffff
op_minus
id|last_match20
)paren
op_plus
id|pc0
suffix:semicolon
)brace
r_else
(brace
id|time_elapsed
op_assign
id|pc0
op_minus
id|last_match20
suffix:semicolon
)brace
r_while
c_loop
(paren
id|time_elapsed
OG
l_int|0
)paren
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|time_elapsed
op_sub_assign
id|MATCH20_INC
suffix:semicolon
id|last_match20
op_add_assign
id|MATCH20_INC
suffix:semicolon
id|jiffie_drift
op_increment
suffix:semicolon
)brace
id|last_pc0
op_assign
id|pc0
suffix:semicolon
id|au_writel
c_func
(paren
id|last_match20
op_plus
id|MATCH20_INC
comma
id|SYS_TOYMATCH2
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* our counter ticks at 10.009765625 ms/tick, we we&squot;re running&n;&t; * almost 10uS too slow per tick.&n;&t; */
r_if
c_cond
(paren
id|jiffie_drift
op_ge
l_int|999
)paren
(brace
id|jiffie_drift
op_sub_assign
l_int|999
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* increment jiffies by one */
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * Figure out the r4k offset, the amount to increment the compare&n; * register for each time tick.&n; * Use the Programmable Counter 1 to do this.&n; */
DECL|function|cal_r4koff
r_int
r_int
id|cal_r4koff
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
r_int
r_int
id|cpu_speed
suffix:semicolon
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_int
r_int
id|counter
suffix:semicolon
r_int
id|trim_divide
op_assign
l_int|16
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|time_lock
comma
id|flags
)paren
suffix:semicolon
id|counter
op_assign
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|counter
op_or
id|SYS_CNTRL_EN1
comma
id|SYS_COUNTER_CNTRL
)paren
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_T1S
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|trim_divide
op_minus
l_int|1
comma
id|SYS_RTCTRIM
)paren
suffix:semicolon
multiline_comment|/* RTC now ticks at 32.768/16 kHz */
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_T1S
)paren
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_C1S
)paren
suffix:semicolon
id|au_writel
(paren
l_int|0
comma
id|SYS_TOYWRITE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_C1S
)paren
suffix:semicolon
id|start
op_assign
id|au_readl
c_func
(paren
id|SYS_RTCREAD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* wait for the beginning of a new tick */
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_RTCREAD
)paren
OL
id|start
)paren
suffix:semicolon
multiline_comment|/* Start r4k counter. */
id|write_c0_count
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
(paren
l_int|32768
op_div
id|trim_divide
)paren
op_div
l_int|2
suffix:semicolon
multiline_comment|/* wait 0.5 seconds */
r_while
c_loop
(paren
id|end
OG
id|au_readl
c_func
(paren
id|SYS_RTCREAD
)paren
)paren
suffix:semicolon
id|count
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
id|cpu_speed
op_assign
id|count
op_star
l_int|2
suffix:semicolon
id|mips_counter_frequency
op_assign
id|count
suffix:semicolon
id|set_au1x00_uart_baud_base
c_func
(paren
(paren
(paren
id|cpu_speed
)paren
op_div
l_int|4
)paren
op_div
l_int|16
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|time_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|cpu_speed
op_div
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|au1x_time_init
r_void
id|__init
id|au1x_time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|est_freq
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;calculating r4koff... &quot;
)paren
suffix:semicolon
id|r4k_offset
op_assign
id|cal_r4koff
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08lx(%d)&bslash;n&quot;
comma
id|r4k_offset
comma
(paren
r_int
)paren
id|r4k_offset
)paren
suffix:semicolon
singleline_comment|//est_freq = 2*r4k_offset*HZ;
id|est_freq
op_assign
id|r4k_offset
op_star
id|HZ
suffix:semicolon
id|est_freq
op_add_assign
l_int|5000
suffix:semicolon
multiline_comment|/* round */
id|est_freq
op_sub_assign
id|est_freq
op_mod
l_int|10000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU frequency %d.%02d MHz&bslash;n&quot;
comma
id|est_freq
op_div
l_int|1000000
comma
(paren
id|est_freq
op_mod
l_int|1000000
)paren
op_star
l_int|100
op_div
l_int|1000000
)paren
suffix:semicolon
id|set_au1x00_speed
c_func
(paren
id|est_freq
)paren
suffix:semicolon
id|set_au1x00_lcd_clock
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// program the LCD clock
id|r4k_cur
op_assign
(paren
id|read_c0_count
c_func
(paren
)paren
op_plus
id|r4k_offset
)paren
suffix:semicolon
id|write_c0_compare
c_func
(paren
id|r4k_cur
)paren
suffix:semicolon
multiline_comment|/* no RTC on the pb1000 */
id|xtime.tv_sec
op_assign
l_int|0
suffix:semicolon
singleline_comment|//xtime.tv_usec = 0;
macro_line|#ifdef CONFIG_PM
multiline_comment|/*&n;&t; * setup counter 0, since it keeps ticking after a&n;&t; * &squot;wait&squot; instruction has been executed. The CP0 timer and&n;&t; * counter 1 do NOT continue running after &squot;wait&squot;&n;&t; *&n;&t; * It&squot;s too early to call request_irq() here, so we handle&n;&t; * counter 0 interrupt as a special irq and it doesn&squot;t show&n;&t; * up under /proc/interrupts.&n;&t; */
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_C0S
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0
comma
id|SYS_TOYWRITE
)paren
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_C0S
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|SYS_WAKEMSK
)paren
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
comma
id|SYS_WAKEMSK
)paren
suffix:semicolon
id|au_writel
c_func
(paren
op_complement
l_int|0
comma
id|SYS_WAKESRC
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_M20
)paren
suffix:semicolon
multiline_comment|/* setup match20 to interrupt once every 10ms */
id|last_pc0
op_assign
id|last_match20
op_assign
id|au_readl
c_func
(paren
id|SYS_TOYREAD
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|last_match20
op_plus
id|MATCH20_INC
comma
id|SYS_TOYMATCH2
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_M20
)paren
suffix:semicolon
id|startup_match20_interrupt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|//set_c0_status(ALLINTS);
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|au1x_timer_setup
r_void
id|__init
id|au1x_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
)brace
multiline_comment|/* This is for machines which generate the exact clock. */
DECL|macro|USECS_PER_JIFFY
mdefine_line|#define USECS_PER_JIFFY (1000000/HZ)
DECL|macro|USECS_PER_JIFFY_FRAC
mdefine_line|#define USECS_PER_JIFFY_FRAC (0x100000000*1000000/HZ&amp;0xffffffff)
macro_line|#ifndef CONFIG_PM
r_static
r_int
r_int
DECL|function|div64_32
id|div64_32
c_func
(paren
r_int
r_int
id|v1
comma
r_int
r_int
id|v2
comma
r_int
r_int
id|v3
)paren
(brace
r_int
r_int
id|r0
suffix:semicolon
id|do_div64_32
c_func
(paren
id|r0
comma
id|v1
comma
id|v2
comma
id|v3
)paren
suffix:semicolon
r_return
id|r0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|do_fast_gettimeoffset
r_static
r_int
r_int
id|do_fast_gettimeoffset
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PM
r_int
r_int
id|pc0
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
id|pc0
op_assign
id|au_readl
c_func
(paren
id|SYS_TOYREAD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pc0
OL
id|last_pc0
)paren
(brace
id|offset
op_assign
l_int|0xffffffff
op_minus
id|last_pc0
op_plus
id|pc0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;offset over: %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|offset
)paren
suffix:semicolon
)brace
r_else
(brace
id|offset
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
(paren
id|pc0
op_minus
id|last_pc0
)paren
op_star
l_int|305
)paren
op_div
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pc0
op_minus
id|last_pc0
)paren
OG
l_int|2
op_star
id|MATCH20_INC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;huge offset %x, last_pc0 %x last_match20 %x pc0 %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|offset
comma
(paren
r_int
)paren
id|last_pc0
comma
(paren
r_int
)paren
id|last_match20
comma
(paren
r_int
)paren
id|pc0
)paren
suffix:semicolon
)brace
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_return
id|offset
suffix:semicolon
macro_line|#else
id|u32
id|count
suffix:semicolon
r_int
r_int
id|res
comma
id|tmp
suffix:semicolon
r_int
r_int
id|r0
suffix:semicolon
multiline_comment|/* Last jiffy when do_fast_gettimeoffset() was called. */
r_static
r_int
r_int
id|last_jiffies
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|quotient
suffix:semicolon
multiline_comment|/*&n;&t; * Cached &quot;1/(clocks per usec)*2^32&quot; value.&n;&t; * It has to be recalculated once each jiffy.&n;&t; */
r_static
r_int
r_int
id|cached_quotient
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|jiffies
suffix:semicolon
id|quotient
op_assign
id|cached_quotient
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
id|last_jiffies
op_ne
id|tmp
)paren
(brace
id|last_jiffies
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|last_jiffies
op_ne
l_int|0
)paren
(brace
id|r0
op_assign
id|div64_32
c_func
(paren
id|timerhi
comma
id|timerlo
comma
id|tmp
)paren
suffix:semicolon
id|quotient
op_assign
id|div64_32
c_func
(paren
id|USECS_PER_JIFFY
comma
id|USECS_PER_JIFFY_FRAC
comma
id|r0
)paren
suffix:semicolon
id|cached_quotient
op_assign
id|quotient
suffix:semicolon
)brace
)brace
multiline_comment|/* Get last timer tick in absolute kernel time */
id|count
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|count
op_sub_assign
id|timerlo
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;multu&bslash;t%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;mfhi&bslash;t%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|count
)paren
comma
l_string|&quot;r&quot;
(paren
id|quotient
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * Due to possible jiffies inconsistencies, we need to check&n;&t; * the result so that we&squot;ll get a timer that is monotonic.&n;&t; */
r_if
c_cond
(paren
id|res
op_ge
id|USECS_PER_JIFFY
)paren
id|res
op_assign
id|USECS_PER_JIFFY
op_minus
l_int|1
suffix:semicolon
r_return
id|res
suffix:semicolon
macro_line|#endif
)brace
eof
