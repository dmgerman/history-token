multiline_comment|/*&n; *  linux/arch/i386/kernel/time_hpet.c&n; *  This code largely copied from arch/x86_64/kernel/time.c&n; *  See that file for credits.&n; *&n; *  2003-06-30    Venkatesh Pallipadi - Additional changes for HPET support&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/hpet.h&gt;
macro_line|#include &lt;linux/hpet.h&gt;
DECL|variable|hpet_period
r_int
r_int
id|hpet_period
suffix:semicolon
multiline_comment|/* fsecs / HPET clock */
DECL|variable|hpet_tick
r_int
r_int
id|hpet_tick
suffix:semicolon
multiline_comment|/* hpet clks count per tick */
DECL|variable|hpet_address
r_int
r_int
id|hpet_address
suffix:semicolon
multiline_comment|/* hpet memory map physical address */
DECL|variable|use_hpet
r_static
r_int
id|use_hpet
suffix:semicolon
multiline_comment|/* can be used for runtime check of hpet */
DECL|variable|boot_hpet_disable
r_static
r_int
id|boot_hpet_disable
suffix:semicolon
multiline_comment|/* boottime override for HPET timer */
DECL|variable|hpet_virt_address
r_static
r_void
id|__iomem
op_star
id|hpet_virt_address
suffix:semicolon
multiline_comment|/* hpet kernel virtual address */
DECL|macro|FSEC_TO_USEC
mdefine_line|#define FSEC_TO_USEC (1000000000UL)
DECL|function|hpet_readl
r_int
id|hpet_readl
c_func
(paren
r_int
r_int
id|a
)paren
(brace
r_return
id|readl
c_func
(paren
id|hpet_virt_address
op_plus
id|a
)paren
suffix:semicolon
)brace
DECL|function|hpet_writel
r_void
id|hpet_writel
c_func
(paren
r_int
r_int
id|d
comma
r_int
r_int
id|a
)paren
(brace
id|writel
c_func
(paren
id|d
comma
id|hpet_virt_address
op_plus
id|a
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
multiline_comment|/*&n; * HPET counters dont wrap around on every tick. They just change the&n; * comparator value and continue. Next tick can be caught by checking&n; * for a change in the comparator value. Used in apic.c.&n; */
DECL|function|wait_hpet_tick
r_void
id|__init
id|wait_hpet_tick
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start_cmp_val
comma
id|end_cmp_val
suffix:semicolon
id|start_cmp_val
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CMP
)paren
suffix:semicolon
r_do
(brace
id|end_cmp_val
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CMP
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start_cmp_val
op_eq
id|end_cmp_val
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|hpet_timer_stop_set_go
r_static
r_int
id|hpet_timer_stop_set_go
c_func
(paren
r_int
r_int
id|tick
)paren
(brace
r_int
r_int
id|cfg
suffix:semicolon
multiline_comment|/*&n;&t; * Stop the timers and reset the main counter.&n;&t; */
id|cfg
op_assign
id|hpet_readl
c_func
(paren
id|HPET_CFG
)paren
suffix:semicolon
id|cfg
op_and_assign
op_complement
id|HPET_CFG_ENABLE
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_CFG
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
l_int|0
comma
id|HPET_COUNTER
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
l_int|0
comma
id|HPET_COUNTER
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up timer 0, as periodic with first interrupt to happen at&n;&t; * hpet_tick, and period also hpet_tick.&n;&t; */
id|cfg
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T0_CFG
)paren
suffix:semicolon
id|cfg
op_or_assign
id|HPET_TN_ENABLE
op_or
id|HPET_TN_PERIODIC
op_or
id|HPET_TN_SETVAL
op_or
id|HPET_TN_32BIT
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_T0_CFG
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
id|tick
comma
id|HPET_T0_CMP
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * Go!&n; &t; */
id|cfg
op_assign
id|hpet_readl
c_func
(paren
id|HPET_CFG
)paren
suffix:semicolon
id|cfg
op_or_assign
id|HPET_CFG_ENABLE
op_or
id|HPET_CFG_LEGACY
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_CFG
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether HPET was found by ACPI boot parse. If yes setup HPET&n; * counter 0 for kernel base timer.&n; */
DECL|function|hpet_enable
r_int
id|__init
id|hpet_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|id
suffix:semicolon
r_int
r_int
id|tick_fsec_low
comma
id|tick_fsec_high
suffix:semicolon
multiline_comment|/* tick in femto sec */
r_int
r_int
id|hpet_tick_rem
suffix:semicolon
r_if
c_cond
(paren
id|boot_hpet_disable
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpet_address
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hpet_virt_address
op_assign
id|ioremap_nocache
c_func
(paren
id|hpet_address
comma
id|HPET_MMAP_SIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Read the period, compute tick and quotient.&n;&t; */
id|id
op_assign
id|hpet_readl
c_func
(paren
id|HPET_ID
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We are checking for value &squot;1&squot; or more in number field.&n;&t; * So, we are OK with HPET_EMULATE_RTC part too, where we need&n;&t; * to have atleast 2 timers.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|id
op_amp
id|HPET_ID_NUMBER
)paren
op_logical_or
op_logical_neg
(paren
id|id
op_amp
id|HPET_ID_LEGSUP
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|hpet_period
op_assign
id|hpet_readl
c_func
(paren
id|HPET_PERIOD
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hpet_period
OL
id|HPET_MIN_PERIOD
)paren
op_logical_or
(paren
id|hpet_period
OG
id|HPET_MAX_PERIOD
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * 64 bit math&n;&t; * First changing tick into fsec&n;&t; * Then 64 bit div to find number of hpet clk per tick&n;&t; */
id|ASM_MUL64_REG
c_func
(paren
id|tick_fsec_low
comma
id|tick_fsec_high
comma
id|KERNEL_TICK_USEC
comma
id|FSEC_TO_USEC
)paren
suffix:semicolon
id|ASM_DIV64_REG
c_func
(paren
id|hpet_tick
comma
id|hpet_tick_rem
comma
id|hpet_period
comma
id|tick_fsec_low
comma
id|tick_fsec_high
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hpet_tick_rem
OG
(paren
id|hpet_period
op_rshift
l_int|1
)paren
)paren
id|hpet_tick
op_increment
suffix:semicolon
multiline_comment|/* rounding the result */
r_if
c_cond
(paren
id|hpet_timer_stop_set_go
c_func
(paren
id|hpet_tick
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|use_hpet
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef&t;CONFIG_HPET
(brace
r_struct
id|hpet_data
id|hd
suffix:semicolon
r_int
r_int
id|ntimer
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hd
comma
l_int|0
comma
r_sizeof
(paren
id|hd
)paren
)paren
suffix:semicolon
id|ntimer
op_assign
id|hpet_readl
c_func
(paren
id|HPET_ID
)paren
suffix:semicolon
id|ntimer
op_assign
(paren
id|ntimer
op_amp
id|HPET_ID_NUMBER
)paren
op_rshift
id|HPET_ID_NUMBER_SHIFT
suffix:semicolon
id|ntimer
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Register with driver.&n;&t;&t; * Timer0 and Timer1 is used by platform.&n;&t;&t; */
id|hd.hd_address
op_assign
id|hpet_virt_address
suffix:semicolon
id|hd.hd_nirqs
op_assign
id|ntimer
suffix:semicolon
id|hd.hd_flags
op_assign
id|HPET_DATA_PLATFORM
suffix:semicolon
id|hpet_reserve_timer
c_func
(paren
op_amp
id|hd
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_HPET_EMULATE_RTC
id|hpet_reserve_timer
c_func
(paren
op_amp
id|hd
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|hd.hd_irq
(braket
l_int|0
)braket
op_assign
id|HPET_LEGACY_8254
suffix:semicolon
id|hd.hd_irq
(braket
l_int|1
)braket
op_assign
id|HPET_LEGACY_RTC
suffix:semicolon
r_if
c_cond
(paren
id|ntimer
OG
l_int|2
)paren
(brace
r_struct
id|hpet
id|__iomem
op_star
id|hpet
suffix:semicolon
r_struct
id|hpet_timer
id|__iomem
op_star
id|timer
suffix:semicolon
r_int
id|i
suffix:semicolon
id|hpet
op_assign
id|hpet_virt_address
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
comma
id|timer
op_assign
op_amp
id|hpet-&gt;hpet_timers
(braket
l_int|2
)braket
suffix:semicolon
id|i
OL
id|ntimer
suffix:semicolon
id|timer
op_increment
comma
id|i
op_increment
)paren
id|hd.hd_irq
(braket
id|i
)braket
op_assign
(paren
id|timer-&gt;hpet_config
op_amp
id|Tn_INT_ROUTE_CNF_MASK
)paren
op_rshift
id|Tn_INT_ROUTE_CNF_SHIFT
suffix:semicolon
)brace
id|hpet_alloc
c_func
(paren
op_amp
id|hd
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|wait_timer_tick
op_assign
id|wait_hpet_tick
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpet_reenable
r_int
id|hpet_reenable
c_func
(paren
r_void
)paren
(brace
r_return
id|hpet_timer_stop_set_go
c_func
(paren
id|hpet_tick
)paren
suffix:semicolon
)brace
DECL|function|is_hpet_enabled
r_int
id|is_hpet_enabled
c_func
(paren
r_void
)paren
(brace
r_return
id|use_hpet
suffix:semicolon
)brace
DECL|function|is_hpet_capable
r_int
id|is_hpet_capable
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|boot_hpet_disable
op_logical_and
id|hpet_address
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpet_setup
r_static
r_int
id|__init
id|hpet_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;disable&quot;
comma
id|str
comma
l_int|7
)paren
)paren
id|boot_hpet_disable
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;hpet=&quot;
comma
id|hpet_setup
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HPET_EMULATE_RTC
multiline_comment|/* HPET in LegacyReplacement Mode eats up RTC interrupt line. When, HPET&n; * is enabled, we support RTC interrupt functionality in software.&n; * RTC has 3 kinds of interrupts:&n; * 1) Update Interrupt - generate an interrupt, every sec, when RTC clock&n; *    is updated&n; * 2) Alarm Interrupt - generate an interrupt at a specific time of day&n; * 3) Periodic Interrupt - generate periodic interrupt, with frequencies&n; *    2Hz-8192Hz (2Hz-64Hz for non-root user) (all freqs in powers of 2)&n; * (1) and (2) above are implemented using polling at a frequency of&n; * 64 Hz. The exact frequency is a tradeoff between accuracy and interrupt&n; * overhead. (DEFAULT_RTC_INT_FREQ)&n; * For (3), we use interrupts at 64Hz or user specified periodic&n; * frequency, whichever is higher.&n; */
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
r_extern
id|irqreturn_t
id|rtc_interrupt
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
suffix:semicolon
DECL|macro|DEFAULT_RTC_INT_FREQ
mdefine_line|#define DEFAULT_RTC_INT_FREQ &t;64
DECL|macro|RTC_NUM_INTS
mdefine_line|#define RTC_NUM_INTS &t;&t;1
DECL|variable|UIE_on
r_static
r_int
r_int
id|UIE_on
suffix:semicolon
DECL|variable|prev_update_sec
r_static
r_int
r_int
id|prev_update_sec
suffix:semicolon
DECL|variable|AIE_on
r_static
r_int
r_int
id|AIE_on
suffix:semicolon
DECL|variable|alarm_time
r_static
r_struct
id|rtc_time
id|alarm_time
suffix:semicolon
DECL|variable|PIE_on
r_static
r_int
r_int
id|PIE_on
suffix:semicolon
DECL|variable|PIE_freq
r_static
r_int
r_int
id|PIE_freq
op_assign
id|DEFAULT_RTC_INT_FREQ
suffix:semicolon
DECL|variable|PIE_count
r_static
r_int
r_int
id|PIE_count
suffix:semicolon
DECL|variable|hpet_rtc_int_freq
r_static
r_int
r_int
id|hpet_rtc_int_freq
suffix:semicolon
multiline_comment|/* RTC interrupt frequency */
multiline_comment|/*&n; * Timer 1 for RTC, we do not use periodic interrupt feature,&n; * even if HPET supports periodic interrupts on Timer 1.&n; * The reason being, to set up a periodic interrupt in HPET, we need to&n; * stop the main counter. And if we do that everytime someone diables/enables&n; * RTC, we will have adverse effect on main kernel timer running on Timer 0.&n; * So, for the time being, simulate the periodic interrupt in software.&n; *&n; * hpet_rtc_timer_init() is called for the first time and during subsequent&n; * interuppts reinit happens through hpet_rtc_timer_reinit().&n; */
DECL|function|hpet_rtc_timer_init
r_int
id|hpet_rtc_timer_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cfg
comma
id|cnt
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_hpet_enabled
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Set the counter 1 and enable the interrupts.&n;&t; */
r_if
c_cond
(paren
id|PIE_on
op_logical_and
(paren
id|PIE_freq
OG
id|DEFAULT_RTC_INT_FREQ
)paren
)paren
id|hpet_rtc_int_freq
op_assign
id|PIE_freq
suffix:semicolon
r_else
id|hpet_rtc_int_freq
op_assign
id|DEFAULT_RTC_INT_FREQ
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cnt
op_assign
id|hpet_readl
c_func
(paren
id|HPET_COUNTER
)paren
suffix:semicolon
id|cnt
op_add_assign
(paren
(paren
id|hpet_tick
op_star
id|HZ
)paren
op_div
id|hpet_rtc_int_freq
)paren
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cnt
comma
id|HPET_T1_CMP
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cfg
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T1_CFG
)paren
suffix:semicolon
id|cfg
op_or_assign
id|HPET_TN_ENABLE
op_or
id|HPET_TN_SETVAL
op_or
id|HPET_TN_32BIT
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_T1_CFG
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpet_rtc_timer_reinit
r_static
r_void
id|hpet_rtc_timer_reinit
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cfg
comma
id|cnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|PIE_on
op_or
id|AIE_on
op_or
id|UIE_on
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|PIE_on
op_logical_and
(paren
id|PIE_freq
OG
id|DEFAULT_RTC_INT_FREQ
)paren
)paren
id|hpet_rtc_int_freq
op_assign
id|PIE_freq
suffix:semicolon
r_else
id|hpet_rtc_int_freq
op_assign
id|DEFAULT_RTC_INT_FREQ
suffix:semicolon
multiline_comment|/* It is more accurate to use the comparator value than current count.*/
id|cnt
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T1_CMP
)paren
suffix:semicolon
id|cnt
op_add_assign
id|hpet_tick
op_star
id|HZ
op_div
id|hpet_rtc_int_freq
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cnt
comma
id|HPET_T1_CMP
)paren
suffix:semicolon
id|cfg
op_assign
id|hpet_readl
c_func
(paren
id|HPET_T1_CFG
)paren
suffix:semicolon
id|cfg
op_or_assign
id|HPET_TN_ENABLE
op_or
id|HPET_TN_SETVAL
op_or
id|HPET_TN_32BIT
suffix:semicolon
id|hpet_writel
c_func
(paren
id|cfg
comma
id|HPET_T1_CFG
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * The functions below are called from rtc driver.&n; * Return 0 if HPET is not being used.&n; * Otherwise do the necessary changes and return 1.&n; */
DECL|function|hpet_mask_rtc_irq_bit
r_int
id|hpet_mask_rtc_irq_bit
c_func
(paren
r_int
r_int
id|bit_mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_hpet_enabled
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bit_mask
op_amp
id|RTC_UIE
)paren
id|UIE_on
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bit_mask
op_amp
id|RTC_PIE
)paren
id|PIE_on
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bit_mask
op_amp
id|RTC_AIE
)paren
id|AIE_on
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpet_set_rtc_irq_bit
r_int
id|hpet_set_rtc_irq_bit
c_func
(paren
r_int
r_int
id|bit_mask
)paren
(brace
r_int
id|timer_init_reqd
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_hpet_enabled
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|PIE_on
op_or
id|AIE_on
op_or
id|UIE_on
)paren
)paren
id|timer_init_reqd
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bit_mask
op_amp
id|RTC_UIE
)paren
(brace
id|UIE_on
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bit_mask
op_amp
id|RTC_PIE
)paren
(brace
id|PIE_on
op_assign
l_int|1
suffix:semicolon
id|PIE_count
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bit_mask
op_amp
id|RTC_AIE
)paren
(brace
id|AIE_on
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timer_init_reqd
)paren
id|hpet_rtc_timer_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpet_set_alarm_time
r_int
id|hpet_set_alarm_time
c_func
(paren
r_int
r_char
id|hrs
comma
r_int
r_char
id|min
comma
r_int
r_char
id|sec
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_hpet_enabled
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|alarm_time.tm_hour
op_assign
id|hrs
suffix:semicolon
id|alarm_time.tm_min
op_assign
id|min
suffix:semicolon
id|alarm_time.tm_sec
op_assign
id|sec
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpet_set_periodic_freq
r_int
id|hpet_set_periodic_freq
c_func
(paren
r_int
r_int
id|freq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_hpet_enabled
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|PIE_freq
op_assign
id|freq
suffix:semicolon
id|PIE_count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpet_rtc_dropped_irq
r_int
id|hpet_rtc_dropped_irq
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_hpet_enabled
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpet_rtc_interrupt
id|irqreturn_t
id|hpet_rtc_interrupt
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
r_struct
id|rtc_time
id|curr_time
suffix:semicolon
r_int
r_int
id|rtc_int_flag
op_assign
l_int|0
suffix:semicolon
r_int
id|call_rtc_interrupt
op_assign
l_int|0
suffix:semicolon
id|hpet_rtc_timer_reinit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UIE_on
op_or
id|AIE_on
)paren
(brace
id|rtc_get_rtc_time
c_func
(paren
op_amp
id|curr_time
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|UIE_on
)paren
(brace
r_if
c_cond
(paren
id|curr_time.tm_sec
op_ne
id|prev_update_sec
)paren
(brace
multiline_comment|/* Set update int info, call real rtc int routine */
id|call_rtc_interrupt
op_assign
l_int|1
suffix:semicolon
id|rtc_int_flag
op_assign
id|RTC_UF
suffix:semicolon
id|prev_update_sec
op_assign
id|curr_time.tm_sec
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|PIE_on
)paren
(brace
id|PIE_count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PIE_count
op_ge
id|hpet_rtc_int_freq
op_div
id|PIE_freq
)paren
(brace
multiline_comment|/* Set periodic int info, call real rtc int routine */
id|call_rtc_interrupt
op_assign
l_int|1
suffix:semicolon
id|rtc_int_flag
op_or_assign
id|RTC_PF
suffix:semicolon
id|PIE_count
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|AIE_on
)paren
(brace
r_if
c_cond
(paren
(paren
id|curr_time.tm_sec
op_eq
id|alarm_time.tm_sec
)paren
op_logical_and
(paren
id|curr_time.tm_min
op_eq
id|alarm_time.tm_min
)paren
op_logical_and
(paren
id|curr_time.tm_hour
op_eq
id|alarm_time.tm_hour
)paren
)paren
(brace
multiline_comment|/* Set alarm int info, call real rtc int routine */
id|call_rtc_interrupt
op_assign
l_int|1
suffix:semicolon
id|rtc_int_flag
op_or_assign
id|RTC_AF
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|call_rtc_interrupt
)paren
(brace
id|rtc_int_flag
op_or_assign
(paren
id|RTC_IRQF
op_or
(paren
id|RTC_NUM_INTS
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|rtc_interrupt
c_func
(paren
id|rtc_int_flag
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
macro_line|#endif
eof
