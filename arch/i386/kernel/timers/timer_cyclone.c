multiline_comment|/*&t;Cyclone-timer: &n; *&t;&t;This code implements timer_ops for the cyclone counter found&n; *&t;&t;on IBM x440, x360, and other Summit based systems.&n; *&n; *&t;Copyright (C) 2002 IBM, John Stultz (johnstul@us.ibm.com)&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
r_extern
id|spinlock_t
id|i8253_lock
suffix:semicolon
r_extern
r_int
r_int
id|jiffies
suffix:semicolon
r_extern
r_int
r_int
id|calibrate_tsc
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Number of usecs that the last interrupt was delayed */
DECL|variable|delay_at_last_interrupt
r_static
r_int
id|delay_at_last_interrupt
suffix:semicolon
DECL|macro|CYCLONE_CBAR_ADDR
mdefine_line|#define CYCLONE_CBAR_ADDR 0xFEB00CD0
DECL|macro|CYCLONE_PMCC_OFFSET
mdefine_line|#define CYCLONE_PMCC_OFFSET 0x51A0
DECL|macro|CYCLONE_MPMC_OFFSET
mdefine_line|#define CYCLONE_MPMC_OFFSET 0x51D0
DECL|macro|CYCLONE_MPCS_OFFSET
mdefine_line|#define CYCLONE_MPCS_OFFSET 0x51A8
DECL|macro|CYCLONE_TIMER_FREQ
mdefine_line|#define CYCLONE_TIMER_FREQ 100000000
DECL|macro|CYCLONE_TIMER_MASK
mdefine_line|#define CYCLONE_TIMER_MASK (((u64)1&lt;&lt;40)-1) /* 40 bit mask */
DECL|variable|use_cyclone
r_int
id|use_cyclone
op_assign
l_int|0
suffix:semicolon
DECL|variable|cyclone_timer
r_static
id|u32
op_star
r_volatile
id|cyclone_timer
suffix:semicolon
multiline_comment|/* Cyclone MPMC0 register */
DECL|variable|last_cyclone_low
r_static
id|u32
id|last_cyclone_low
suffix:semicolon
DECL|variable|last_cyclone_high
r_static
id|u32
id|last_cyclone_high
suffix:semicolon
DECL|variable|monotonic_base
r_static
r_int
r_int
r_int
id|monotonic_base
suffix:semicolon
DECL|variable|monotonic_lock
r_static
id|rwlock_t
id|monotonic_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* helper macro to atomically read both cyclone counter registers */
DECL|macro|read_cyclone_counter
mdefine_line|#define read_cyclone_counter(low,high) &bslash;&n;&t;do{ &bslash;&n;&t;&t;high = cyclone_timer[1]; low = cyclone_timer[0]; &bslash;&n;&t;} while (high != cyclone_timer[1]);
DECL|function|mark_offset_cyclone
r_static
r_void
id|mark_offset_cyclone
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
id|last_cyclone_low
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
r_int
r_int
id|this_offset
comma
id|last_offset
suffix:semicolon
id|write_lock
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
id|last_cyclone_high
op_lshift
l_int|32
)paren
op_or
id|last_cyclone_low
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
id|read_cyclone_counter
c_func
(paren
id|last_cyclone_low
comma
id|last_cyclone_high
)paren
suffix:semicolon
multiline_comment|/* read values for delay_at_last_interrupt */
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|count
op_or_assign
id|inb
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|i8253_lock
)paren
suffix:semicolon
multiline_comment|/* lost tick compensation */
id|delta
op_assign
id|last_cyclone_low
op_minus
id|delta
suffix:semicolon
id|delta
op_div_assign
(paren
id|CYCLONE_TIMER_FREQ
op_div
l_int|1000000
)paren
suffix:semicolon
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
id|jiffies
op_add_assign
id|lost
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* update the monotonic base value */
id|this_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|last_cyclone_high
op_lshift
l_int|32
)paren
op_or
id|last_cyclone_low
suffix:semicolon
id|monotonic_base
op_add_assign
(paren
id|this_offset
op_minus
id|last_offset
)paren
op_amp
id|CYCLONE_TIMER_MASK
suffix:semicolon
id|write_unlock
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
multiline_comment|/* catch corner case where tick rollover &n;&t; * occured between cyclone and pit reads&n;&t; */
r_if
c_cond
(paren
id|abs
c_func
(paren
id|delay
op_minus
id|delay_at_last_interrupt
)paren
OG
l_int|900
)paren
(brace
id|jiffies
op_increment
suffix:semicolon
)brace
)brace
DECL|function|get_offset_cyclone
r_static
r_int
r_int
id|get_offset_cyclone
c_func
(paren
r_void
)paren
(brace
id|u32
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cyclone_timer
)paren
(brace
r_return
id|delay_at_last_interrupt
suffix:semicolon
)brace
multiline_comment|/* Read the cyclone timer */
id|offset
op_assign
id|cyclone_timer
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* .. relative to previous jiffy */
id|offset
op_assign
id|offset
op_minus
id|last_cyclone_low
suffix:semicolon
multiline_comment|/* convert cyclone ticks to microseconds */
multiline_comment|/* XXX slow, can we speed this up? */
id|offset
op_assign
id|offset
op_div
(paren
id|CYCLONE_TIMER_FREQ
op_div
l_int|1000000
)paren
suffix:semicolon
multiline_comment|/* our adjusted time offset in microseconds */
r_return
id|delay_at_last_interrupt
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|monotonic_clock_cyclone
r_static
r_int
r_int
r_int
id|monotonic_clock_cyclone
c_func
(paren
r_void
)paren
(brace
id|u32
id|now_low
comma
id|now_high
suffix:semicolon
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
r_int
r_int
id|ret
suffix:semicolon
multiline_comment|/* atomically read monotonic base &amp; last_offset */
id|read_lock_irq
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
id|last_cyclone_high
op_lshift
l_int|32
)paren
op_or
id|last_cyclone_low
suffix:semicolon
id|base
op_assign
id|monotonic_base
suffix:semicolon
id|read_unlock_irq
c_func
(paren
op_amp
id|monotonic_lock
)paren
suffix:semicolon
multiline_comment|/* Read the cyclone counter */
id|read_cyclone_counter
c_func
(paren
id|now_low
comma
id|now_high
)paren
suffix:semicolon
id|this_offset
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|now_high
op_lshift
l_int|32
)paren
op_or
id|now_low
suffix:semicolon
multiline_comment|/* convert to nanoseconds */
id|ret
op_assign
id|base
op_plus
(paren
(paren
id|this_offset
op_minus
id|last_offset
)paren
op_amp
id|CYCLONE_TIMER_MASK
)paren
suffix:semicolon
r_return
id|ret
op_star
(paren
l_int|1000000000
op_div
id|CYCLONE_TIMER_FREQ
)paren
suffix:semicolon
)brace
DECL|function|init_cyclone
r_static
r_int
id|__init
id|init_cyclone
c_func
(paren
r_char
op_star
id|override
)paren
(brace
id|u32
op_star
id|reg
suffix:semicolon
id|u32
id|base
suffix:semicolon
multiline_comment|/* saved cyclone base address */
id|u32
id|pageaddr
suffix:semicolon
multiline_comment|/* page that contains cyclone_timer register */
id|u32
id|offset
suffix:semicolon
multiline_comment|/* offset from pageaddr to cyclone_timer register */
r_int
id|i
suffix:semicolon
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
l_string|&quot;cyclone&quot;
comma
l_int|7
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*make sure we&squot;re on a summit box*/
r_if
c_cond
(paren
op_logical_neg
id|use_cyclone
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Summit chipset: Starting Cyclone Counter.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* find base address */
id|pageaddr
op_assign
(paren
id|CYCLONE_CBAR_ADDR
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|offset
op_assign
(paren
id|CYCLONE_CBAR_ADDR
)paren
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|set_fixmap_nocache
c_func
(paren
id|FIX_CYCLONE_TIMER
comma
id|pageaddr
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|u32
op_star
)paren
(paren
id|fix_to_virt
c_func
(paren
id|FIX_CYCLONE_TIMER
)paren
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid CBAR register.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|base
op_assign
op_star
id|reg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid CBAR value.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* setup PMCC */
id|pageaddr
op_assign
(paren
id|base
op_plus
id|CYCLONE_PMCC_OFFSET
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|offset
op_assign
(paren
id|base
op_plus
id|CYCLONE_PMCC_OFFSET
)paren
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|set_fixmap_nocache
c_func
(paren
id|FIX_CYCLONE_TIMER
comma
id|pageaddr
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|u32
op_star
)paren
(paren
id|fix_to_virt
c_func
(paren
id|FIX_CYCLONE_TIMER
)paren
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid PMCC register.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|reg
(braket
l_int|0
)braket
op_assign
l_int|0x00000001
suffix:semicolon
multiline_comment|/* setup MPCS */
id|pageaddr
op_assign
(paren
id|base
op_plus
id|CYCLONE_MPCS_OFFSET
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|offset
op_assign
(paren
id|base
op_plus
id|CYCLONE_MPCS_OFFSET
)paren
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|set_fixmap_nocache
c_func
(paren
id|FIX_CYCLONE_TIMER
comma
id|pageaddr
)paren
suffix:semicolon
id|reg
op_assign
(paren
id|u32
op_star
)paren
(paren
id|fix_to_virt
c_func
(paren
id|FIX_CYCLONE_TIMER
)paren
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid MPCS register.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|reg
(braket
l_int|0
)braket
op_assign
l_int|0x00000001
suffix:semicolon
multiline_comment|/* map in cyclone_timer */
id|pageaddr
op_assign
(paren
id|base
op_plus
id|CYCLONE_MPMC_OFFSET
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|offset
op_assign
(paren
id|base
op_plus
id|CYCLONE_MPMC_OFFSET
)paren
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|set_fixmap_nocache
c_func
(paren
id|FIX_CYCLONE_TIMER
comma
id|pageaddr
)paren
suffix:semicolon
id|cyclone_timer
op_assign
(paren
id|u32
op_star
)paren
(paren
id|fix_to_virt
c_func
(paren
id|FIX_CYCLONE_TIMER
)paren
op_plus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cyclone_timer
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Could not find valid MPMC register.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*quick test to make sure its ticking*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|old
op_assign
id|cyclone_timer
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|stall
op_assign
l_int|100
suffix:semicolon
r_while
c_loop
(paren
id|stall
op_decrement
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cyclone_timer
(braket
l_int|0
)braket
op_eq
id|old
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Summit chipset: Counter not counting! DISABLED&bslash;n&quot;
)paren
suffix:semicolon
id|cyclone_timer
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
multiline_comment|/* init cpu_khz.&n;&t; * XXX - This should really be done elsewhere, &n;&t; * &t;&t;and in a more generic fashion. -johnstul@us.ibm.com&n;&t; */
r_if
c_cond
(paren
id|cpu_has_tsc
)paren
(brace
r_int
r_int
id|tsc_quotient
op_assign
id|calibrate_tsc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsc_quotient
)paren
(brace
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
)brace
)brace
multiline_comment|/* Everything looks good! */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|delay_cyclone
r_static
r_void
id|delay_cyclone
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
r_if
c_cond
(paren
op_logical_neg
id|cyclone_timer
)paren
(brace
r_return
suffix:semicolon
)brace
id|bclock
op_assign
id|cyclone_timer
(braket
l_int|0
)braket
suffix:semicolon
r_do
(brace
id|rep_nop
c_func
(paren
)paren
suffix:semicolon
id|now
op_assign
id|cyclone_timer
(braket
l_int|0
)braket
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
multiline_comment|/************************************************************/
multiline_comment|/* cyclone timer_opts struct */
DECL|variable|timer_cyclone
r_struct
id|timer_opts
id|timer_cyclone
op_assign
(brace
dot
id|init
op_assign
id|init_cyclone
comma
dot
id|mark_offset
op_assign
id|mark_offset_cyclone
comma
dot
id|get_offset
op_assign
id|get_offset_cyclone
comma
dot
id|monotonic_clock
op_assign
id|monotonic_clock_cyclone
comma
dot
id|delay
op_assign
id|delay_cyclone
comma
)brace
suffix:semicolon
eof
