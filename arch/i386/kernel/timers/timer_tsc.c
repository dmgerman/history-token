multiline_comment|/*&n; * This code largely moved from arch/i386/kernel/time.c.&n; * See comments there for proper credits.&n; *&n; * 2004-06-25    Jesper Juhl&n; *      moved mark_offset_tsc below cpufreq_delayed_get to avoid gcc 3.4&n; *      failing to inline.&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* processor.h for distable_tsc flag */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;io_ports.h&quot;
macro_line|#include &quot;mach_timer.h&quot;
macro_line|#include &lt;asm/hpet.h&gt;
macro_line|#ifdef CONFIG_HPET_TIMER
DECL|variable|hpet_usec_quotient
r_static
r_int
r_int
id|hpet_usec_quotient
suffix:semicolon
DECL|variable|hpet_last
r_static
r_int
r_int
id|hpet_last
suffix:semicolon
DECL|variable|timer_tsc
r_static
r_struct
id|timer_opts
id|timer_tsc
suffix:semicolon
macro_line|#endif
r_static
r_inline
r_void
id|cpufreq_delayed_get
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__initdata
r_int
id|tsc_disable
id|__initdata
op_assign
l_int|0
suffix:semicolon
r_extern
id|spinlock_t
id|i8253_lock
suffix:semicolon
DECL|variable|use_tsc
r_static
r_int
id|use_tsc
suffix:semicolon
multiline_comment|/* Number of usecs that the last interrupt was delayed */
DECL|variable|delay_at_last_interrupt
r_static
r_int
id|delay_at_last_interrupt
suffix:semicolon
DECL|variable|last_tsc_low
r_static
r_int
r_int
id|last_tsc_low
suffix:semicolon
multiline_comment|/* lsb 32 bits of Time Stamp Counter */
DECL|variable|last_tsc_high
r_static
r_int
r_int
id|last_tsc_high
suffix:semicolon
multiline_comment|/* msb 32 bits of Time Stamp Counter */
DECL|variable|monotonic_base
r_static
r_int
r_int
r_int
id|monotonic_base
suffix:semicolon
DECL|variable|monotonic_lock
r_static
id|seqlock_t
id|monotonic_lock
op_assign
id|SEQLOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* convert from cycles(64bits) =&gt; nanoseconds (64bits)&n; *  basic equation:&n; *&t;&t;ns = cycles / (freq / ns_per_sec)&n; *&t;&t;ns = cycles * (ns_per_sec / freq)&n; *&t;&t;ns = cycles * (10^9 / (cpu_mhz * 10^6))&n; *&t;&t;ns = cycles * (10^3 / cpu_mhz)&n; *&n; *&t;Then we use scaling math (suggested by george@mvista.com) to get:&n; *&t;&t;ns = cycles * (10^3 * SC / cpu_mhz) / SC&n; *&t;&t;ns = cycles * cyc2ns_scale / SC&n; *&n; *&t;And since SC is a constant power of two, we can convert the div&n; *  into a shift.   &n; *&t;&t;&t;-johnstul@us.ibm.com &quot;math is hard, lets go shopping!&quot;&n; */
DECL|variable|cyc2ns_scale
r_static
r_int
r_int
id|cyc2ns_scale
suffix:semicolon
DECL|macro|CYC2NS_SCALE_FACTOR
mdefine_line|#define CYC2NS_SCALE_FACTOR 10 /* 2^10, carefully chosen */
DECL|function|set_cyc2ns_scale
r_static
r_inline
r_void
id|set_cyc2ns_scale
c_func
(paren
r_int
r_int
id|cpu_mhz
)paren
(brace
id|cyc2ns_scale
op_assign
(paren
l_int|1000
op_lshift
id|CYC2NS_SCALE_FACTOR
)paren
op_div
id|cpu_mhz
suffix:semicolon
)brace
DECL|function|cycles_2_ns
r_static
r_inline
r_int
r_int
r_int
id|cycles_2_ns
c_func
(paren
r_int
r_int
r_int
id|cyc
)paren
(brace
r_return
(paren
id|cyc
op_star
id|cyc2ns_scale
)paren
op_rshift
id|CYC2NS_SCALE_FACTOR
suffix:semicolon
)brace
DECL|variable|count2
r_static
r_int
id|count2
suffix:semicolon
multiline_comment|/* counter for mark_offset_tsc() */
multiline_comment|/* Cached *multiplier* to convert TSC counts to microseconds.&n; * (see the equation below).&n; * Equal to 2^32 * (1 / (clocks per usec) ).&n; * Initialized in time_init.&n; */
DECL|variable|fast_gettimeoffset_quotient
r_static
r_int
r_int
id|fast_gettimeoffset_quotient
suffix:semicolon
DECL|function|get_offset_tsc
r_static
r_int
r_int
id|get_offset_tsc
c_func
(paren
r_void
)paren
(brace
r_register
r_int
r_int
id|eax
comma
id|edx
suffix:semicolon
multiline_comment|/* Read the Time Stamp Counter */
id|rdtsc
c_func
(paren
id|eax
comma
id|edx
)paren
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy (32 bits is enough) */
id|eax
op_sub_assign
id|last_tsc_low
suffix:semicolon
multiline_comment|/* tsc_low delta */
multiline_comment|/*&n;         * Time offset = (tsc_low delta) * fast_gettimeoffset_quotient&n;         *             = (tsc_low delta) * (usecs_per_clock)&n;         *             = (tsc_low delta) * (usecs_per_jiffy / clocks_per_jiffy)&n;&t; *&n;&t; * Using a mull instead of a divl saves up to 31 clock cycles&n;&t; * in the critical path.&n;         */
id|__asm__
c_func
(paren
l_string|&quot;mull %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|fast_gettimeoffset_quotient
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
)paren
suffix:semicolon
multiline_comment|/* our adjusted time offset in microseconds */
r_return
id|delay_at_last_interrupt
op_plus
id|edx
suffix:semicolon
)brace
DECL|function|monotonic_clock_tsc
r_static
r_int
r_int
r_int
id|monotonic_clock_tsc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|last_offset
comma
id|this_offset
comma
id|base
suffix:semicolon
r_int
id|seq
suffix:semicolon
multiline_comment|/* atomically read monotonic base &amp; last_offset */
r_do
(brace
id|seq
op_assign
id|read_seqbegin
c_func
(paren
op_amp
id|monotonic_lock
)paren
suffix:semicolon
id|last_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|last_tsc_high
op_lshift
l_int|32
)paren
op_or
id|last_tsc_low
suffix:semicolon
id|base
op_assign
id|monotonic_base
suffix:semicolon
)brace
r_while
c_loop
(paren
id|read_seqretry
c_func
(paren
op_amp
id|monotonic_lock
comma
id|seq
)paren
)paren
suffix:semicolon
multiline_comment|/* Read the Time Stamp Counter */
id|rdtscll
c_func
(paren
id|this_offset
)paren
suffix:semicolon
multiline_comment|/* return the value in ns */
r_return
id|base
op_plus
id|cycles_2_ns
c_func
(paren
id|this_offset
op_minus
id|last_offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Scheduler clock - returns current time in nanosec units.&n; */
DECL|function|sched_clock
r_int
r_int
r_int
id|sched_clock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|this_offset
suffix:semicolon
multiline_comment|/*&n;&t; * In the NUMA case we dont use the TSC as they are not&n;&t; * synchronized across all CPUs.&n;&t; */
macro_line|#ifndef CONFIG_NUMA
r_if
c_cond
(paren
op_logical_neg
id|use_tsc
)paren
macro_line|#endif
multiline_comment|/* no locking but a rare wrong value is not a big deal */
r_return
id|jiffies_64
op_star
(paren
l_int|1000000000
op_div
id|HZ
)paren
suffix:semicolon
multiline_comment|/* Read the Time Stamp Counter */
id|rdtscll
c_func
(paren
id|this_offset
)paren
suffix:semicolon
multiline_comment|/* return the value in ns */
r_return
id|cycles_2_ns
c_func
(paren
id|this_offset
)paren
suffix:semicolon
)brace
DECL|function|delay_tsc
r_static
r_void
id|delay_tsc
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
r_int
r_int
id|bclock
comma
id|now
suffix:semicolon
id|rdtscl
c_func
(paren
id|bclock
)paren
suffix:semicolon
r_do
(brace
id|rep_nop
c_func
(paren
)paren
suffix:semicolon
id|rdtscl
c_func
(paren
id|now
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|now
op_minus
id|bclock
)paren
OL
id|loops
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HPET_TIMER
DECL|function|mark_offset_tsc_hpet
r_static
r_void
id|mark_offset_tsc_hpet
c_func
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|this_offset
comma
id|last_offset
suffix:semicolon
r_int
r_int
id|offset
comma
id|temp
comma
id|hpet_current
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|monotonic_lock
)paren
suffix:semicolon
id|last_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|last_tsc_high
op_lshift
l_int|32
)paren
op_or
id|last_tsc_low
suffix:semicolon
multiline_comment|/*&n;&t; * It is important that these two operations happen almost at&n;&t; * the same time. We do the RDTSC stuff first, since it&squot;s&n;&t; * faster. To avoid any inconsistencies, we need interrupts&n;&t; * disabled locally.&n;&t; */
multiline_comment|/*&n;&t; * Interrupts are just disabled locally since the timer irq&n;&t; * has the SA_INTERRUPT flag set. -arca&n;&t; */
multiline_comment|/* read Pentium cycle counter */
id|hpet_current
op_assign
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
suffix:semicolon
id|rdtsc
c_func
(paren
id|last_tsc_low
comma
id|last_tsc_high
)paren
suffix:semicolon
multiline_comment|/* lost tick compensation */
id|offset
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CMP
)paren
op_minus
id|hpet_tick
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
(paren
id|offset
op_minus
id|hpet_last
)paren
OG
id|hpet_tick
)paren
op_logical_and
(paren
id|hpet_last
op_ne
l_int|0
)paren
)paren
)paren
(brace
r_int
id|lost_ticks
op_assign
(paren
id|offset
op_minus
id|hpet_last
)paren
op_div
id|hpet_tick
suffix:semicolon
id|jiffies_64
op_add_assign
id|lost_ticks
suffix:semicolon
)brace
id|hpet_last
op_assign
id|hpet_current
suffix:semicolon
multiline_comment|/* update the monotonic base value */
id|this_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|last_tsc_high
op_lshift
l_int|32
)paren
op_or
id|last_tsc_low
suffix:semicolon
id|monotonic_base
op_add_assign
id|cycles_2_ns
c_func
(paren
id|this_offset
op_minus
id|last_offset
)paren
suffix:semicolon
id|write_sequnlock
c_func
(paren
op_amp
id|monotonic_lock
)paren
suffix:semicolon
multiline_comment|/* calculate delay_at_last_interrupt */
multiline_comment|/*&n;&t; * Time offset = (hpet delta) * ( usecs per HPET clock )&n;&t; *             = (hpet delta) * ( usecs per tick / HPET clocks per tick)&n;&t; *             = (hpet delta) * ( hpet_usec_quotient ) / (2^32)&n;&t; * Where,&n;&t; * hpet_usec_quotient = (2^32 * usecs per tick)/HPET clocks per tick&n;&t; */
id|delay_at_last_interrupt
op_assign
id|hpet_current
op_minus
id|offset
suffix:semicolon
id|ASM_MUL64_REG
c_func
(paren
id|temp
comma
id|delay_at_last_interrupt
comma
id|hpet_usec_quotient
comma
id|delay_at_last_interrupt
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_FREQ
macro_line|#include &lt;linux/workqueue.h&gt;
DECL|variable|cpufreq_delayed_issched
r_static
r_int
r_int
id|cpufreq_delayed_issched
op_assign
l_int|0
suffix:semicolon
DECL|variable|cpufreq_init
r_static
r_int
r_int
id|cpufreq_init
op_assign
l_int|0
suffix:semicolon
DECL|variable|cpufreq_delayed_get_work
r_static
r_struct
id|work_struct
id|cpufreq_delayed_get_work
suffix:semicolon
DECL|function|handle_cpufreq_delayed_get
r_static
r_void
id|handle_cpufreq_delayed_get
c_func
(paren
r_void
op_star
id|v
)paren
(brace
r_int
r_int
id|cpu
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
(brace
id|cpufreq_get
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
id|cpufreq_delayed_issched
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* if we notice lost ticks, schedule a call to cpufreq_get() as it tries&n; * to verify the CPU frequency the timing core thinks the CPU is running&n; * at is still correct.&n; */
DECL|function|cpufreq_delayed_get
r_static
r_inline
r_void
id|cpufreq_delayed_get
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cpufreq_init
op_logical_and
op_logical_neg
id|cpufreq_delayed_issched
)paren
(brace
id|cpufreq_delayed_issched
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Losing some ticks... checking if CPU frequency changed.&bslash;n&quot;
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|cpufreq_delayed_get_work
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* If the CPU frequency is scaled, TSC-based delays will need a different&n; * loops_per_jiffy value to function properly.&n; */
DECL|variable|ref_freq
r_static
r_int
r_int
id|ref_freq
op_assign
l_int|0
suffix:semicolon
DECL|variable|loops_per_jiffy_ref
r_static
r_int
r_int
id|loops_per_jiffy_ref
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|variable|fast_gettimeoffset_ref
r_static
r_int
r_int
id|fast_gettimeoffset_ref
op_assign
l_int|0
suffix:semicolon
DECL|variable|cpu_khz_ref
r_static
r_int
r_int
id|cpu_khz_ref
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_static
r_int
DECL|function|time_cpufreq_notifier
id|time_cpufreq_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cpufreq_freqs
op_star
id|freq
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ne
id|CPUFREQ_RESUMECHANGE
)paren
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ref_freq
)paren
(brace
id|ref_freq
op_assign
id|freq-&gt;old
suffix:semicolon
id|loops_per_jiffy_ref
op_assign
id|cpu_data
(braket
id|freq-&gt;cpu
)braket
dot
id|loops_per_jiffy
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|fast_gettimeoffset_ref
op_assign
id|fast_gettimeoffset_quotient
suffix:semicolon
id|cpu_khz_ref
op_assign
id|cpu_khz
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
id|val
op_eq
id|CPUFREQ_PRECHANGE
op_logical_and
id|freq-&gt;old
OL
id|freq
op_member_access_from_pointer
r_new
)paren
op_logical_or
(paren
id|val
op_eq
id|CPUFREQ_POSTCHANGE
op_logical_and
id|freq-&gt;old
OG
id|freq
op_member_access_from_pointer
r_new
)paren
op_logical_or
(paren
id|val
op_eq
id|CPUFREQ_RESUMECHANGE
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|freq-&gt;flags
op_amp
id|CPUFREQ_CONST_LOOPS
)paren
)paren
id|cpu_data
(braket
id|freq-&gt;cpu
)braket
dot
id|loops_per_jiffy
op_assign
id|cpufreq_scale
c_func
(paren
id|loops_per_jiffy_ref
comma
id|ref_freq
comma
id|freq
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|cpu_khz
)paren
id|cpu_khz
op_assign
id|cpufreq_scale
c_func
(paren
id|cpu_khz_ref
comma
id|ref_freq
comma
id|freq
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|use_tsc
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|freq-&gt;flags
op_amp
id|CPUFREQ_CONST_LOOPS
)paren
)paren
(brace
id|fast_gettimeoffset_quotient
op_assign
id|cpufreq_scale
c_func
(paren
id|fast_gettimeoffset_ref
comma
id|freq
op_member_access_from_pointer
r_new
comma
id|ref_freq
)paren
suffix:semicolon
id|set_cyc2ns_scale
c_func
(paren
id|cpu_khz
op_div
l_int|1000
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
id|val
op_ne
id|CPUFREQ_RESUMECHANGE
)paren
id|write_sequnlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|time_cpufreq_notifier_block
r_static
r_struct
id|notifier_block
id|time_cpufreq_notifier_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|time_cpufreq_notifier
)brace
suffix:semicolon
DECL|function|cpufreq_tsc
r_static
r_int
id|__init
id|cpufreq_tsc
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|cpufreq_delayed_get_work
comma
id|handle_cpufreq_delayed_get
comma
l_int|NULL
)paren
suffix:semicolon
id|ret
op_assign
id|cpufreq_register_notifier
c_func
(paren
op_amp
id|time_cpufreq_notifier_block
comma
id|CPUFREQ_TRANSITION_NOTIFIER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|cpufreq_init
op_assign
l_int|1
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|cpufreq_tsc
id|core_initcall
c_func
(paren
id|cpufreq_tsc
)paren
suffix:semicolon
macro_line|#else /* CONFIG_CPU_FREQ */
DECL|function|cpufreq_delayed_get
r_static
r_inline
r_void
id|cpufreq_delayed_get
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif 
DECL|function|mark_offset_tsc
r_static
r_void
id|mark_offset_tsc
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|lost
comma
id|delay
suffix:semicolon
r_int
r_int
id|delta
op_assign
id|last_tsc_low
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|countmp
suffix:semicolon
r_static
r_int
id|count1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
r_int
id|this_offset
comma
id|last_offset
suffix:semicolon
r_static
r_int
id|lost_count
op_assign
l_int|0
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|monotonic_lock
)paren
suffix:semicolon
id|last_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|last_tsc_high
op_lshift
l_int|32
)paren
op_or
id|last_tsc_low
suffix:semicolon
multiline_comment|/*&n;&t; * It is important that these two operations happen almost at&n;&t; * the same time. We do the RDTSC stuff first, since it&squot;s&n;&t; * faster. To avoid any inconsistencies, we need interrupts&n;&t; * disabled locally.&n;&t; */
multiline_comment|/*&n;&t; * Interrupts are just disabled locally since the timer irq&n;&t; * has the SA_INTERRUPT flag set. -arca&n;&t; */
multiline_comment|/* read Pentium cycle counter */
id|rdtsc
c_func
(paren
id|last_tsc_low
comma
id|last_tsc_high
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|PIT_MODE
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
id|PIT_CH0
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|count
op_or_assign
id|inb
c_func
(paren
id|PIT_CH0
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/*&n;&t; * VIA686a test code... reset the latch if count &gt; max + 1&n;&t; * from timer_pit.c - cjb&n;&t; */
r_if
c_cond
(paren
id|count
OG
id|LATCH
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x34
comma
id|PIT_MODE
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
id|PIT_CH0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
id|PIT_CH0
)paren
suffix:semicolon
id|count
op_assign
id|LATCH
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pit_latch_buggy
)paren
(brace
multiline_comment|/* get center value of last 3 time lutch */
r_if
c_cond
(paren
(paren
id|count2
op_ge
id|count
op_logical_and
id|count
op_ge
id|count1
)paren
op_logical_or
(paren
id|count1
op_ge
id|count
op_logical_and
id|count
op_ge
id|count2
)paren
)paren
(brace
id|count2
op_assign
id|count1
suffix:semicolon
id|count1
op_assign
id|count
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|count1
op_ge
id|count2
op_logical_and
id|count2
op_ge
id|count
)paren
op_logical_or
(paren
id|count
op_ge
id|count2
op_logical_and
id|count2
op_ge
id|count1
)paren
)paren
(brace
id|countmp
op_assign
id|count
suffix:semicolon
id|count
op_assign
id|count2
suffix:semicolon
id|count2
op_assign
id|count1
suffix:semicolon
id|count1
op_assign
id|countmp
suffix:semicolon
)brace
r_else
(brace
id|count2
op_assign
id|count1
suffix:semicolon
id|count1
op_assign
id|count
suffix:semicolon
id|count
op_assign
id|count1
suffix:semicolon
)brace
)brace
multiline_comment|/* lost tick compensation */
id|delta
op_assign
id|last_tsc_low
op_minus
id|delta
suffix:semicolon
(brace
r_register
r_int
r_int
id|eax
comma
id|edx
suffix:semicolon
id|eax
op_assign
id|delta
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mull %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;rm&quot;
(paren
id|fast_gettimeoffset_quotient
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
)paren
suffix:semicolon
id|delta
op_assign
id|edx
suffix:semicolon
)brace
id|delta
op_add_assign
id|delay_at_last_interrupt
suffix:semicolon
id|lost
op_assign
id|delta
op_div
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|delay
op_assign
id|delta
op_mod
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lost
op_ge
l_int|2
)paren
(brace
id|jiffies_64
op_add_assign
id|lost
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* sanity check to ensure we&squot;re not always losing ticks */
r_if
c_cond
(paren
id|lost_count
op_increment
OG
l_int|100
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Losing too many ticks!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;TSC cannot be used as a timesource.  &bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Possible reasons for this are:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  You&squot;re running with Speedstep,&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  You don&squot;t have DMA enabled for your hard disk (see hdparm),&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  Incorrect TSC synchronization on an SMP system (see dmesg).&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Falling back to a sane timesource now.&bslash;n&quot;
)paren
suffix:semicolon
id|clock_fallback
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* ... but give the TSC a fair chance */
r_if
c_cond
(paren
id|lost_count
OG
l_int|25
)paren
id|cpufreq_delayed_get
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|lost_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* update the monotonic base value */
id|this_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|last_tsc_high
op_lshift
l_int|32
)paren
op_or
id|last_tsc_low
suffix:semicolon
id|monotonic_base
op_add_assign
id|cycles_2_ns
c_func
(paren
id|this_offset
op_minus
id|last_offset
)paren
suffix:semicolon
id|write_sequnlock
c_func
(paren
op_amp
id|monotonic_lock
)paren
suffix:semicolon
multiline_comment|/* calculate delay_at_last_interrupt */
id|count
op_assign
(paren
(paren
id|LATCH
op_minus
l_int|1
)paren
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|delay_at_last_interrupt
op_assign
(paren
id|count
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
multiline_comment|/* catch corner case where tick rollover occured&n;&t; * between tsc and pit reads (as noted when&n;&t; * usec delta is &gt; 90% # of usecs/tick)&n;&t; */
r_if
c_cond
(paren
id|lost
op_logical_and
id|abs
c_func
(paren
id|delay
op_minus
id|delay_at_last_interrupt
)paren
OG
(paren
l_int|900000
op_div
id|HZ
)paren
)paren
id|jiffies_64
op_increment
suffix:semicolon
)brace
DECL|function|init_tsc
r_static
r_int
id|__init
id|init_tsc
c_func
(paren
r_char
op_star
id|override
)paren
(brace
multiline_comment|/* check clock override */
r_if
c_cond
(paren
id|override
(braket
l_int|0
)braket
op_logical_and
id|strncmp
c_func
(paren
id|override
comma
l_string|&quot;tsc&quot;
comma
l_int|3
)paren
)paren
(brace
macro_line|#ifdef CONFIG_HPET_TIMER
r_if
c_cond
(paren
id|is_hpet_enabled
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Warning: clock= override failed. Defaulting to tsc&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * If we have APM enabled or the CPU clock speed is variable&n;&t; * (CPU stops clock on HLT or slows clock to save power)&n;&t; * then the TSC timestamps may diverge by up to 1 jiffy from&n;&t; * &squot;real time&squot; but nothing will break.&n;&t; * The most frequent case is that the CPU is &quot;woken&quot; from a halt&n;&t; * state by the timer interrupt itself, so we get 0 error. In the&n;&t; * rare cases where a driver would &quot;wake&quot; the CPU and request a&n;&t; * timestamp, the maximum error is &lt; 1 jiffy. But timestamps are&n;&t; * still perfectly ordered.&n;&t; * Note that the TSC counter will be reset if APM suspends&n;&t; * to disk; this won&squot;t break the kernel, though, &squot;cuz we&squot;re&n;&t; * smart.  See arch/i386/kernel/apm.c.&n;&t; */
multiline_comment|/*&n; &t; *&t;Firstly we have to do a CPU check for chips with&n; &t; * &t;a potentially buggy TSC. At this point we haven&squot;t run&n; &t; *&t;the ident/bugs checks so we must run this hook as it&n; &t; *&t;may turn off the TSC flag.&n; &t; *&n; &t; *&t;NOTE: this doesn&squot;t yet handle SMP 486 machines where only&n; &t; *&t;some CPU&squot;s have a TSC. Thats never worked and nobody has&n; &t; *&t;moaned if you have the only one in the world - you fix it!&n; &t; */
id|count2
op_assign
id|LATCH
suffix:semicolon
multiline_comment|/* initialize counter for mark_offset_tsc() */
r_if
c_cond
(paren
id|cpu_has_tsc
)paren
(brace
r_int
r_int
id|tsc_quotient
suffix:semicolon
macro_line|#ifdef CONFIG_HPET_TIMER
r_if
c_cond
(paren
id|is_hpet_enabled
c_func
(paren
)paren
)paren
(brace
r_int
r_int
id|result
comma
id|remain
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Using TSC for gettimeofday&bslash;n&quot;
)paren
suffix:semicolon
id|tsc_quotient
op_assign
id|calibrate_tsc_hpet
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|timer_tsc.mark_offset
op_assign
op_amp
id|mark_offset_tsc_hpet
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Math to calculate hpet to usec multiplier&n;&t;&t;&t; * Look for the comments at get_offset_tsc_hpet()&n;&t;&t;&t; */
id|ASM_DIV64_REG
c_func
(paren
id|result
comma
id|remain
comma
id|hpet_tick
comma
l_int|0
comma
id|KERNEL_TICK_USEC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remain
OG
(paren
id|hpet_tick
op_rshift
l_int|1
)paren
)paren
id|result
op_increment
suffix:semicolon
multiline_comment|/* rounding the result */
id|hpet_usec_quotient
op_assign
id|result
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
id|tsc_quotient
op_assign
id|calibrate_tsc
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tsc_quotient
)paren
(brace
id|fast_gettimeoffset_quotient
op_assign
id|tsc_quotient
suffix:semicolon
id|use_tsc
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;We could be more selective here I suspect&n;&t;&t;&t; *&t;and just enable this for the next intel chips ?&n;&t;&t;&t; */
multiline_comment|/* report CPU clock rate in Hz.&n;&t;&t;&t; * The formula is (10^6 * 2^32) / (2^32 * 1 / (clocks/us)) =&n;&t;&t;&t; * clock/second. Our precision is about 100 ppm.&n;&t;&t;&t; */
(brace
r_int
r_int
id|eax
op_assign
l_int|0
comma
id|edx
op_assign
l_int|1000
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|cpu_khz
)paren
comma
l_string|&quot;=d&quot;
(paren
id|edx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|tsc_quotient
)paren
comma
l_string|&quot;0&quot;
(paren
id|eax
)paren
comma
l_string|&quot;1&quot;
(paren
id|edx
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Detected %lu.%03lu MHz processor.&bslash;n&quot;
comma
id|cpu_khz
op_div
l_int|1000
comma
id|cpu_khz
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
id|set_cyc2ns_scale
c_func
(paren
id|cpu_khz
op_div
l_int|1000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_X86_TSC
multiline_comment|/* disable flag for tsc.  Takes effect by clearing the TSC cpu flag&n; * in cpu/common.c */
DECL|function|tsc_setup
r_static
r_int
id|__init
id|tsc_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|tsc_disable
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|function|tsc_setup
r_static
r_int
id|__init
id|tsc_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;notsc: Kernel compiled with CONFIG_X86_TSC, &quot;
l_string|&quot;cannot disable TSC.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|__setup
c_func
(paren
l_string|&quot;notsc&quot;
comma
id|tsc_setup
)paren
suffix:semicolon
multiline_comment|/************************************************************/
multiline_comment|/* tsc timer_opts struct */
DECL|variable|timer_tsc
r_static
r_struct
id|timer_opts
id|timer_tsc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tsc&quot;
comma
dot
id|mark_offset
op_assign
id|mark_offset_tsc
comma
dot
id|get_offset
op_assign
id|get_offset_tsc
comma
dot
id|monotonic_clock
op_assign
id|monotonic_clock_tsc
comma
dot
id|delay
op_assign
id|delay_tsc
comma
)brace
suffix:semicolon
DECL|variable|timer_tsc_init
r_struct
id|init_timer_opts
id|__initdata
id|timer_tsc_init
op_assign
(brace
dot
id|init
op_assign
id|init_tsc
comma
dot
id|opts
op_assign
op_amp
id|timer_tsc
comma
)brace
suffix:semicolon
eof
