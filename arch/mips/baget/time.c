multiline_comment|/*&n; * time.c: Baget/MIPS specific time handling details&n; *&n; * Copyright (C) 1998 Gleb Raiko &amp; Vladimir Roganov&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/baget/baget.h&gt;
multiline_comment|/*&n; *  To have precision clock, we need to fix available clock frequency&n; */
DECL|macro|FREQ_NOM
mdefine_line|#define FREQ_NOM  79125  /* Baget frequency ratio */
DECL|macro|FREQ_DEN
mdefine_line|#define FREQ_DEN  10000
DECL|function|timer_intr_valid
r_static
r_inline
r_int
id|timer_intr_valid
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
r_int
id|ticks
comma
id|valid_ticks
suffix:semicolon
r_if
c_cond
(paren
id|ticks
op_increment
op_star
id|FREQ_DEN
op_ge
id|valid_ticks
op_star
id|FREQ_NOM
)paren
(brace
multiline_comment|/*&n;&t;&t; *  We need no overflow checks,&n;&t;&t; *  due baget unable to work 3000 years...&n;&t;&t; *  At least without reboot...&n;&t;&t; */
id|valid_ticks
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|timer_interrupt
r_void
r_static
id|timer_interrupt
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
r_if
c_cond
(paren
id|timer_intr_valid
c_func
(paren
)paren
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
DECL|function|timer_enable
r_static
r_void
id|__init
id|timer_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|ss0cr0
op_assign
id|vic_inb
c_func
(paren
id|VIC_SS0CR0
)paren
suffix:semicolon
id|ss0cr0
op_and_assign
op_complement
id|VIC_SS0CR0_TIMER_FREQ_MASK
suffix:semicolon
id|ss0cr0
op_or_assign
id|VIC_SS0CR0_TIMER_FREQ_1000HZ
suffix:semicolon
id|vic_outb
c_func
(paren
id|ss0cr0
comma
id|VIC_SS0CR0
)paren
suffix:semicolon
id|vic_outb
c_func
(paren
id|VIC_INT_IPL
c_func
(paren
l_int|6
)paren
op_or
id|VIC_INT_NOAUTO
op_or
id|VIC_INT_EDGE
op_or
id|VIC_INT_LOW
op_or
id|VIC_INT_ENABLE
comma
id|VIC_LINT2
)paren
suffix:semicolon
)brace
DECL|variable|timer_irq
r_static
r_struct
id|irqaction
id|timer_irq
op_assign
(brace
id|timer_interrupt
comma
id|SA_INTERRUPT
comma
id|CPU_MASK_NONE
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|setup_baget_irq
c_func
(paren
id|BAGET_VIC_TIMER_IRQ
comma
op_amp
id|timer_irq
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;time_init: unable request irq for system timer&bslash;n&quot;
)paren
suffix:semicolon
id|timer_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t call sti() here, because it is too early for baget */
)brace
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
id|seq
suffix:semicolon
r_do
(brace
id|seq
op_assign
id|read_seqbegin
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|tv-&gt;tv_sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|tv-&gt;tv_usec
op_assign
id|xtime.tv_nsec
op_div
l_int|1000
suffix:semicolon
)brace
r_while
c_loop
(paren
id|read_seqretry
c_func
(paren
op_amp
id|xtime_lock
comma
id|seq
)paren
)paren
suffix:semicolon
)brace
DECL|variable|do_gettimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_gettimeofday
)paren
suffix:semicolon
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
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
id|xtime.tv_nsec
op_assign
id|tv-&gt;tv_usec
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
id|write_sequnlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
)brace
DECL|variable|do_settimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_settimeofday
)paren
suffix:semicolon
eof
