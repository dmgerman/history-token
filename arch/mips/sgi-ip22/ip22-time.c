multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Time operations for IP22 machines. Original code may come from&n; * Ralf Baechle or David S. Miller (sorry guys, i&squot;m really not sure)&n; *&n; * Copyright (C) 2001 by Ladislav Michl&n; * Copyright (C) 2003 Ralf Baechle (ralf@linux-mips.org)&n; */
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/ds1286.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/ioc.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
macro_line|#include &lt;asm/sgi/ip22.h&gt;
multiline_comment|/*&n; * note that mktime uses month from 1 to 12 while to_tm&n; * uses 0 to 11.&n; */
DECL|function|indy_rtc_get_time
r_static
r_int
r_int
id|indy_rtc_get_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|yrs
comma
id|mon
comma
id|day
comma
id|hrs
comma
id|min
comma
id|sec
suffix:semicolon
r_int
r_int
id|save_control
suffix:semicolon
id|save_control
op_assign
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_CMD
)braket
op_amp
l_int|0xff
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_CMD
)braket
op_assign
id|save_control
op_or
id|RTC_TE
suffix:semicolon
id|sec
op_assign
id|BCD2BIN
c_func
(paren
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_SECONDS
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
id|min
op_assign
id|BCD2BIN
c_func
(paren
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_MINUTES
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
id|hrs
op_assign
id|BCD2BIN
c_func
(paren
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_HOURS
)braket
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|day
op_assign
id|BCD2BIN
c_func
(paren
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_DATE
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
id|mon
op_assign
id|BCD2BIN
c_func
(paren
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_MONTH
)braket
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|yrs
op_assign
id|BCD2BIN
c_func
(paren
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_YEAR
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_CMD
)braket
op_assign
id|save_control
suffix:semicolon
r_if
c_cond
(paren
id|yrs
OL
l_int|45
)paren
id|yrs
op_add_assign
l_int|30
suffix:semicolon
r_if
c_cond
(paren
(paren
id|yrs
op_add_assign
l_int|40
)paren
OL
l_int|70
)paren
id|yrs
op_add_assign
l_int|100
suffix:semicolon
r_return
id|mktime
c_func
(paren
id|yrs
op_plus
l_int|1900
comma
id|mon
comma
id|day
comma
id|hrs
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
DECL|function|indy_rtc_set_time
r_static
r_int
id|indy_rtc_set_time
c_func
(paren
r_int
r_int
id|tim
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
r_int
r_int
id|save_control
suffix:semicolon
id|to_tm
c_func
(paren
id|tim
comma
op_amp
id|tm
)paren
suffix:semicolon
id|tm.tm_mon
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* tm_mon starts at zero */
id|tm.tm_year
op_sub_assign
l_int|1940
suffix:semicolon
r_if
c_cond
(paren
id|tm.tm_year
op_ge
l_int|100
)paren
id|tm.tm_year
op_sub_assign
l_int|100
suffix:semicolon
id|save_control
op_assign
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_CMD
)braket
op_amp
l_int|0xff
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_CMD
)braket
op_assign
id|save_control
op_or
id|RTC_TE
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_YEAR
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_MONTH
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_DATE
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_HOURS
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_MINUTES
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_SECONDS
)braket
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_HUNDREDTH_SECOND
)braket
op_assign
l_int|0
suffix:semicolon
id|hpc3c0-&gt;rtcregs
(braket
id|RTC_CMD
)braket
op_assign
id|save_control
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dosample
r_static
r_int
r_int
id|dosample
c_func
(paren
r_void
)paren
(brace
id|u32
id|ct0
comma
id|ct1
suffix:semicolon
r_volatile
id|u8
id|msb
comma
id|lsb
suffix:semicolon
multiline_comment|/* Start the counter. */
id|sgint-&gt;tcword
op_assign
(paren
id|SGINT_TCWORD_CNT2
op_or
id|SGINT_TCWORD_CALL
op_or
id|SGINT_TCWORD_MRGEN
)paren
suffix:semicolon
id|sgint-&gt;tcnt2
op_assign
id|SGINT_TCSAMP_COUNTER
op_amp
l_int|0xff
suffix:semicolon
id|sgint-&gt;tcnt2
op_assign
id|SGINT_TCSAMP_COUNTER
op_rshift
l_int|8
suffix:semicolon
multiline_comment|/* Get initial counter invariant */
id|ct0
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Latch and spin until top byte of counter2 is zero */
r_do
(brace
id|sgint-&gt;tcword
op_assign
id|SGINT_TCWORD_CNT2
op_or
id|SGINT_TCWORD_CLAT
suffix:semicolon
id|lsb
op_assign
id|sgint-&gt;tcnt2
suffix:semicolon
id|msb
op_assign
id|sgint-&gt;tcnt2
suffix:semicolon
id|ct1
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|msb
)paren
suffix:semicolon
multiline_comment|/* Stop the counter. */
id|sgint-&gt;tcword
op_assign
(paren
id|SGINT_TCWORD_CNT2
op_or
id|SGINT_TCWORD_CALL
op_or
id|SGINT_TCWORD_MSWST
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Return the difference, this is how far the r4k counter increments&n;&t; * for every 1/HZ seconds. We round off the nearest 1 MHz of master&n;&t; * clock (= 1000000 / HZ / 2).&n;&t; */
multiline_comment|/*return (ct1 - ct0 + (500000/HZ/2)) / (500000/HZ) * (500000/HZ);*/
r_return
(paren
id|ct1
op_minus
id|ct0
)paren
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
op_star
(paren
l_int|500000
op_div
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Here we need to calibrate the cycle counter to at least be close.&n; */
DECL|function|indy_time_init
r_static
id|__init
r_void
id|indy_time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|r4k_ticks
(braket
l_int|3
)braket
suffix:semicolon
r_int
r_int
id|r4k_tick
suffix:semicolon
multiline_comment|/* &n;&t; * Figure out the r4k offset, the algorithm is very simple and works in&n;&t; * _all_ cases as long as the 8254 counter register itself works ok (as&n;&t; * an interrupt driving timer it does not because of bug, this is why&n;&t; * we are using the onchip r4k counter/compare register to serve this&n;&t; * purpose, but for r4k_offset calculation it will work ok for us).&n;&t; * There are other very complicated ways of performing this calculation&n;&t; * but this one works just fine so I am not going to futz around. ;-)&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Calibrating system timer... &quot;
)paren
suffix:semicolon
id|dosample
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Prime cache. */
id|dosample
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Prime cache. */
multiline_comment|/* Zero is NOT an option. */
r_do
(brace
id|r4k_ticks
(braket
l_int|0
)braket
op_assign
id|dosample
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|r4k_ticks
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_do
(brace
id|r4k_ticks
(braket
l_int|1
)braket
op_assign
id|dosample
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|r4k_ticks
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r4k_ticks
(braket
l_int|0
)braket
op_ne
id|r4k_ticks
(braket
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;warning: timer counts differ, retrying... &quot;
)paren
suffix:semicolon
id|r4k_ticks
(braket
l_int|2
)braket
op_assign
id|dosample
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r4k_ticks
(braket
l_int|2
)braket
op_eq
id|r4k_ticks
(braket
l_int|0
)braket
op_logical_or
id|r4k_ticks
(braket
l_int|2
)braket
op_eq
id|r4k_ticks
(braket
l_int|1
)braket
)paren
id|r4k_tick
op_assign
id|r4k_ticks
(braket
l_int|2
)braket
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;disagreement, using average... &quot;
)paren
suffix:semicolon
id|r4k_tick
op_assign
(paren
id|r4k_ticks
(braket
l_int|0
)braket
op_plus
id|r4k_ticks
(braket
l_int|1
)braket
op_plus
id|r4k_ticks
(braket
l_int|2
)braket
)paren
op_div
l_int|3
suffix:semicolon
)brace
)brace
r_else
id|r4k_tick
op_assign
id|r4k_ticks
(braket
l_int|0
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d [%d.%04d MHz CPU]&bslash;n&quot;
comma
(paren
r_int
)paren
id|r4k_tick
comma
(paren
r_int
)paren
(paren
id|r4k_tick
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
)paren
comma
(paren
r_int
)paren
(paren
id|r4k_tick
op_mod
(paren
l_int|500000
op_div
id|HZ
)paren
)paren
)paren
suffix:semicolon
id|mips_hpt_frequency
op_assign
id|r4k_tick
op_star
id|HZ
suffix:semicolon
)brace
multiline_comment|/* Generic SGI handler for (spurious) 8254 interrupts */
DECL|function|indy_8254timer_irq
r_void
id|indy_8254timer_irq
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
id|SGI_8254_0_IRQ
suffix:semicolon
id|ULONG
id|cnt
suffix:semicolon
r_char
id|c
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Oops, got 8254 interrupt.&bslash;n&quot;
)paren
suffix:semicolon
id|ArcRead
c_func
(paren
l_int|0
comma
op_amp
id|c
comma
l_int|1
comma
op_amp
id|cnt
)paren
suffix:semicolon
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|indy_r4k_timer_interrupt
r_void
id|indy_r4k_timer_interrupt
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
id|SGI_TIMER_IRQ
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|timer_interrupt
c_func
(paren
id|irq
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|setup_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
id|irqaction
)paren
suffix:semicolon
DECL|function|indy_timer_setup
r_static
r_void
id|indy_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
multiline_comment|/* over-write the handler, we use our own way */
id|irq-&gt;handler
op_assign
id|no_action
suffix:semicolon
multiline_comment|/* setup irqaction */
id|setup_irq
c_func
(paren
id|SGI_TIMER_IRQ
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|ip22_time_init
r_void
id|__init
id|ip22_time_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* setup hookup functions */
id|rtc_get_time
op_assign
id|indy_rtc_get_time
suffix:semicolon
id|rtc_set_time
op_assign
id|indy_rtc_set_time
suffix:semicolon
id|board_time_init
op_assign
id|indy_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|indy_timer_setup
suffix:semicolon
)brace
eof
