multiline_comment|/* $Id: time.c,v 1.60 2002/01/23 14:33:55 davem Exp $&n; * linux/arch/sparc/kernel/time.c&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; *&n; * Chris Davis (cdavis@cois.on.ca) 03/27/1998&n; * Added support for the intersil on the sun4/4200&n; *&n; * Gleb Raiko (rajko@mech.math.msu.su) 08/18/1998&n; * Support for MicroSPARC-IIep, PCI CPU.&n; *&n; * This file handles the Sparc specific time handling details.&n; *&n; * 1997-09-10&t;Updated NTP code according to technical memorandum Jan &squot;96&n; *&t;&t;&quot;A Kernel Model for Precision Timekeeping&quot; by Dave Mills&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/mostek.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/machines.h&gt;
macro_line|#include &lt;asm/sun4paddr.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pcic.h&gt;
r_extern
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|variable|jiffies_64
id|u64
id|jiffies_64
op_assign
id|INITIAL_JIFFIES
suffix:semicolon
DECL|variable|jiffies_64
id|EXPORT_SYMBOL
c_func
(paren
id|jiffies_64
)paren
suffix:semicolon
DECL|variable|rtc_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|rtc_lock
)paren
suffix:semicolon
DECL|variable|sp_clock_typ
r_enum
id|sparc_clock_type
id|sp_clock_typ
suffix:semicolon
DECL|variable|mostek_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|mostek_lock
)paren
suffix:semicolon
DECL|variable|mstk48t02_regs
r_void
id|__iomem
op_star
id|mstk48t02_regs
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mstk48t08_regs
r_static
r_struct
id|mostek48t08
op_star
id|mstk48t08_regs
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|sbus_do_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
DECL|variable|intersil_clock
r_struct
id|intersil
op_star
id|intersil_clock
suffix:semicolon
DECL|macro|intersil_cmd
mdefine_line|#define intersil_cmd(intersil_reg, intsil_cmd) intersil_reg-&gt;int_cmd_reg = &bslash;&n;&t;(intsil_cmd)
DECL|macro|intersil_intr
mdefine_line|#define intersil_intr(intersil_reg, intsil_cmd) intersil_reg-&gt;int_intr_reg = &bslash;&n;&t;(intsil_cmd)
DECL|macro|intersil_start
mdefine_line|#define intersil_start(intersil_reg) intersil_cmd(intersil_reg, &bslash;&n;&t;( INTERSIL_START | INTERSIL_32K | INTERSIL_NORMAL | INTERSIL_24H |&bslash;&n;&t;  INTERSIL_INTR_ENABLE))
DECL|macro|intersil_stop
mdefine_line|#define intersil_stop(intersil_reg) intersil_cmd(intersil_reg, &bslash;&n;&t;( INTERSIL_STOP | INTERSIL_32K | INTERSIL_NORMAL | INTERSIL_24H |&bslash;&n;&t;  INTERSIL_INTR_ENABLE))
DECL|macro|intersil_read_intr
mdefine_line|#define intersil_read_intr(intersil_reg, towhere) towhere = &bslash;&n;&t;intersil_reg-&gt;int_intr_reg
macro_line|#endif
DECL|function|profile_pc
r_int
r_int
id|profile_pc
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_extern
r_char
id|__copy_user_begin
(braket
)braket
comma
id|__copy_user_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|__atomic_begin
(braket
)braket
comma
id|__atomic_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|__bzero_begin
(braket
)braket
comma
id|__bzero_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|__bitops_begin
(braket
)braket
comma
id|__bitops_end
(braket
)braket
suffix:semicolon
r_int
r_int
id|pc
op_assign
id|regs-&gt;pc
suffix:semicolon
r_if
c_cond
(paren
id|in_lock_functions
c_func
(paren
id|pc
)paren
op_logical_or
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|__copy_user_begin
op_logical_and
id|pc
OL
(paren
r_int
r_int
)paren
id|__copy_user_end
)paren
op_logical_or
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|__atomic_begin
op_logical_and
id|pc
OL
(paren
r_int
r_int
)paren
id|__atomic_end
)paren
op_logical_or
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|__bzero_begin
op_logical_and
id|pc
OL
(paren
r_int
r_int
)paren
id|__bzero_end
)paren
op_logical_or
(paren
id|pc
op_ge
(paren
r_int
r_int
)paren
id|__bitops_begin
op_logical_and
id|pc
OL
(paren
r_int
r_int
)paren
id|__bitops_end
)paren
)paren
id|pc
op_assign
id|regs-&gt;u_regs
(braket
id|UREG_RETPC
)braket
suffix:semicolon
r_return
id|pc
suffix:semicolon
)brace
DECL|variable|master_l10_counter
id|__volatile__
r_int
r_int
op_star
id|master_l10_counter
suffix:semicolon
DECL|variable|master_l10_limit
id|__volatile__
r_int
r_int
op_star
id|master_l10_limit
suffix:semicolon
multiline_comment|/*&n; * timer_interrupt() needs to keep up the real-time clock,&n; * as well as call the &quot;do_timer()&quot; routine every clocktick&n; */
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE (tick_nsec / 1000)
DECL|function|timer_interrupt
id|irqreturn_t
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
multiline_comment|/* last time the cmos clock got updated */
r_static
r_int
id|last_rtc_update
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|profile_tick
c_func
(paren
id|CPU_PROFILING
comma
id|regs
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Protect counter clear so that do_gettimeoffset works */
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
r_if
c_cond
(paren
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4
op_or
id|SM_4_260
)paren
)paren
op_logical_or
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4
op_or
id|SM_4_110
)paren
)paren
)paren
(brace
r_int
id|temp
suffix:semicolon
id|intersil_read_intr
c_func
(paren
id|intersil_clock
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* re-enable the irq */
id|enable_pil_irq
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#endif
id|clear_clock_irq
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
macro_line|#ifndef CONFIG_SMP
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
macro_line|#endif
multiline_comment|/* Determine when to update the Mostek clock. */
r_if
c_cond
(paren
(paren
id|time_status
op_amp
id|STA_UNSYNC
)paren
op_eq
l_int|0
op_logical_and
id|xtime.tv_sec
OG
id|last_rtc_update
op_plus
l_int|660
op_logical_and
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_ge
l_int|500000
op_minus
(paren
(paren
r_int
)paren
id|TICK_SIZE
)paren
op_div
l_int|2
op_logical_and
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
op_le
l_int|500000
op_plus
(paren
(paren
r_int
)paren
id|TICK_SIZE
)paren
op_div
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|set_rtc_mmss
c_func
(paren
id|xtime.tv_sec
)paren
op_eq
l_int|0
)paren
id|last_rtc_update
op_assign
id|xtime.tv_sec
suffix:semicolon
r_else
id|last_rtc_update
op_assign
id|xtime.tv_sec
op_minus
l_int|600
suffix:semicolon
multiline_comment|/* do it again in 60 s */
)brace
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* Kick start a stopped clock (procedure from the Sun NVRAM/hostid FAQ). */
DECL|function|kick_start_clock
r_static
r_void
id|__init
id|kick_start_clock
c_func
(paren
r_void
)paren
(brace
r_struct
id|mostek48t02
op_star
id|regs
op_assign
(paren
r_struct
id|mostek48t02
op_star
)paren
id|mstk48t02_regs
suffix:semicolon
r_int
r_char
id|sec
suffix:semicolon
r_int
id|i
comma
id|count
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;CLOCK: Clock was stopped. Kick start &quot;
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
multiline_comment|/* Turn on the kick start bit to start the oscillator. */
id|regs-&gt;creg
op_or_assign
id|MSTK_CREG_WRITE
suffix:semicolon
id|regs-&gt;sec
op_and_assign
op_complement
id|MSTK_STOP
suffix:semicolon
id|regs-&gt;hour
op_or_assign
id|MSTK_KICK_START
suffix:semicolon
id|regs-&gt;creg
op_and_assign
op_complement
id|MSTK_CREG_WRITE
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
multiline_comment|/* Delay to allow the clock oscillator to start. */
id|sec
op_assign
id|MSTK_REG_SEC
c_func
(paren
id|regs
)paren
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_while
c_loop
(paren
id|sec
op_eq
id|MSTK_REG_SEC
c_func
(paren
id|regs
)paren
)paren
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|100000
suffix:semicolon
id|count
op_increment
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|sec
op_assign
id|regs-&gt;sec
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
multiline_comment|/* Turn off kick start and set a &quot;valid&quot; time and date. */
id|regs-&gt;creg
op_or_assign
id|MSTK_CREG_WRITE
suffix:semicolon
id|regs-&gt;hour
op_and_assign
op_complement
id|MSTK_KICK_START
suffix:semicolon
id|MSTK_SET_REG_SEC
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|MSTK_SET_REG_MIN
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|MSTK_SET_REG_HOUR
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|MSTK_SET_REG_DOW
c_func
(paren
id|regs
comma
l_int|5
)paren
suffix:semicolon
id|MSTK_SET_REG_DOM
c_func
(paren
id|regs
comma
l_int|1
)paren
suffix:semicolon
id|MSTK_SET_REG_MONTH
c_func
(paren
id|regs
comma
l_int|8
)paren
suffix:semicolon
id|MSTK_SET_REG_YEAR
c_func
(paren
id|regs
comma
l_int|1996
op_minus
id|MSTK_YEAR_ZERO
)paren
suffix:semicolon
id|regs-&gt;creg
op_and_assign
op_complement
id|MSTK_CREG_WRITE
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
multiline_comment|/* Ensure the kick start bit is off. If it isn&squot;t, turn it off. */
r_while
c_loop
(paren
id|regs-&gt;hour
op_amp
id|MSTK_KICK_START
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;CLOCK: Kick start still on!&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
id|regs-&gt;creg
op_or_assign
id|MSTK_CREG_WRITE
suffix:semicolon
id|regs-&gt;hour
op_and_assign
op_complement
id|MSTK_KICK_START
suffix:semicolon
id|regs-&gt;creg
op_and_assign
op_complement
id|MSTK_CREG_WRITE
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;CLOCK: Kick start procedure successful.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Return nonzero if the clock chip battery is low. */
DECL|function|has_low_battery
r_static
id|__inline__
r_int
id|has_low_battery
c_func
(paren
r_void
)paren
(brace
r_struct
id|mostek48t02
op_star
id|regs
op_assign
(paren
r_struct
id|mostek48t02
op_star
)paren
id|mstk48t02_regs
suffix:semicolon
r_int
r_char
id|data1
comma
id|data2
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
id|data1
op_assign
id|regs-&gt;eeprom
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Read some data. */
id|regs-&gt;eeprom
(braket
l_int|0
)braket
op_assign
op_complement
id|data1
suffix:semicolon
multiline_comment|/* Write back the complement. */
id|data2
op_assign
id|regs-&gt;eeprom
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Read back the complement. */
id|regs-&gt;eeprom
(braket
l_int|0
)braket
op_assign
id|data1
suffix:semicolon
multiline_comment|/* Restore the original value. */
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
r_return
(paren
id|data1
op_eq
id|data2
)paren
suffix:semicolon
multiline_comment|/* Was the write blocked? */
)brace
multiline_comment|/* Probe for the real time clock chip on Sun4 */
DECL|function|sun4_clock_probe
r_static
id|__inline__
r_void
id|sun4_clock_probe
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SUN4
r_int
id|temp
suffix:semicolon
r_struct
id|resource
id|r
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4
op_or
id|SM_4_330
)paren
)paren
(brace
id|sp_clock_typ
op_assign
id|MSTK48T02
suffix:semicolon
id|r.start
op_assign
id|sun4_clock_physaddr
suffix:semicolon
id|mstk48t02_regs
op_assign
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mostek48t02
)paren
comma
l_int|NULL
)paren
suffix:semicolon
id|mstk48t08_regs
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* To catch weirdness */
id|intersil_clock
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* just in case */
multiline_comment|/* Kick start the clock if it is completely stopped. */
r_if
c_cond
(paren
id|mostek_read
c_func
(paren
id|mstk48t02_regs
op_plus
id|MOSTEK_SEC
)paren
op_amp
id|MSTK_STOP
)paren
id|kick_start_clock
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4
op_or
id|SM_4_260
)paren
)paren
(brace
multiline_comment|/* intersil setup code */
id|printk
c_func
(paren
l_string|&quot;Clock: INTERSIL at %8x &quot;
comma
id|sun4_clock_physaddr
)paren
suffix:semicolon
id|sp_clock_typ
op_assign
id|INTERSIL
suffix:semicolon
id|r.start
op_assign
id|sun4_clock_physaddr
suffix:semicolon
id|intersil_clock
op_assign
(paren
r_struct
id|intersil
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|intersil_clock
)paren
comma
l_string|&quot;intersil&quot;
)paren
suffix:semicolon
id|mstk48t02_regs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* just be sure */
id|mstk48t08_regs
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ditto */
multiline_comment|/* initialise the clock */
id|intersil_intr
c_func
(paren
id|intersil_clock
comma
id|INTERSIL_INT_100HZ
)paren
suffix:semicolon
id|intersil_start
c_func
(paren
id|intersil_clock
)paren
suffix:semicolon
id|intersil_read_intr
c_func
(paren
id|intersil_clock
comma
id|temp
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|0x80
)paren
)paren
id|intersil_read_intr
c_func
(paren
id|intersil_clock
comma
id|temp
)paren
suffix:semicolon
id|intersil_read_intr
c_func
(paren
id|intersil_clock
comma
id|temp
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|0x80
)paren
)paren
id|intersil_read_intr
c_func
(paren
id|intersil_clock
comma
id|temp
)paren
suffix:semicolon
id|intersil_stop
c_func
(paren
id|intersil_clock
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* Probe for the mostek real time clock chip. */
DECL|function|clock_probe
r_static
id|__inline__
r_void
id|clock_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_prom_registers
id|clk_reg
(braket
l_int|2
)braket
suffix:semicolon
r_char
id|model
(braket
l_int|128
)braket
suffix:semicolon
r_register
r_int
id|node
comma
id|cpuunit
comma
id|bootbus
suffix:semicolon
r_struct
id|resource
id|r
suffix:semicolon
id|cpuunit
op_assign
id|bootbus
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
multiline_comment|/* Determine the correct starting PROM node for the probe. */
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;obio&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4d
suffix:colon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|bootbus
op_assign
id|prom_searchsiblings
c_func
(paren
id|prom_getchild
c_func
(paren
id|cpuunit
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;cpu-unit&quot;
)paren
)paren
comma
l_string|&quot;bootbus&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;CLOCK: Unsupported architecture!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find the PROM node describing the real time clock. */
id|sp_clock_typ
op_assign
id|MSTK_INVALID
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;eeprom&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;CLOCK: No clock found!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the model name and setup everything up. */
id|model
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|prom_getstring
c_func
(paren
id|node
comma
l_string|&quot;model&quot;
comma
id|model
comma
r_sizeof
(paren
id|model
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|model
comma
l_string|&quot;mk48t02&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|sp_clock_typ
op_assign
id|MSTK48T02
suffix:semicolon
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|clk_reg
comma
r_sizeof
(paren
id|clk_reg
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;clock_probe: FAILED!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
id|prom_apply_generic_ranges
(paren
id|bootbus
comma
id|cpuunit
comma
id|clk_reg
comma
l_int|1
)paren
suffix:semicolon
r_else
id|prom_apply_obio_ranges
c_func
(paren
id|clk_reg
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Map the clock register io area read-only */
id|r.flags
op_assign
id|clk_reg
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
id|r.start
op_assign
id|clk_reg
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
id|mstk48t02_regs
op_assign
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mostek48t02
)paren
comma
l_string|&quot;mk48t02&quot;
)paren
suffix:semicolon
id|mstk48t08_regs
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* To catch weirdness */
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|model
comma
l_string|&quot;mk48t08&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|sp_clock_typ
op_assign
id|MSTK48T08
suffix:semicolon
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|clk_reg
comma
r_sizeof
(paren
id|clk_reg
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;clock_probe: FAILED!&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4d
)paren
id|prom_apply_generic_ranges
(paren
id|bootbus
comma
id|cpuunit
comma
id|clk_reg
comma
l_int|1
)paren
suffix:semicolon
r_else
id|prom_apply_obio_ranges
c_func
(paren
id|clk_reg
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Map the clock register io area read-only */
multiline_comment|/* XXX r/o attribute is somewhere in r.flags */
id|r.flags
op_assign
id|clk_reg
(braket
l_int|0
)braket
dot
id|which_io
suffix:semicolon
id|r.start
op_assign
id|clk_reg
(braket
l_int|0
)braket
dot
id|phys_addr
suffix:semicolon
id|mstk48t08_regs
op_assign
(paren
r_struct
id|mostek48t08
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mostek48t08
)paren
comma
l_string|&quot;mk48t08&quot;
)paren
suffix:semicolon
id|mstk48t02_regs
op_assign
op_amp
id|mstk48t08_regs-&gt;regs
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;CLOCK: Unknown model name &squot;%s&squot;&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Report a low battery voltage condition. */
r_if
c_cond
(paren
id|has_low_battery
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;NVRAM: Low battery voltage!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Kick start the clock if it is completely stopped. */
r_if
c_cond
(paren
id|mostek_read
c_func
(paren
id|mstk48t02_regs
op_plus
id|MOSTEK_SEC
)paren
op_amp
id|MSTK_STOP
)paren
id|kick_start_clock
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sbus_time_init
r_void
id|__init
id|sbus_time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
r_struct
id|mostek48t02
op_star
id|mregs
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
r_int
id|temp
suffix:semicolon
r_struct
id|intersil
op_star
id|iregs
suffix:semicolon
macro_line|#endif
id|BTFIXUPSET_CALL
c_func
(paren
id|bus_do_settimeofday
comma
id|sbus_do_settimeofday
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|btfixup
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ARCH_SUN4
)paren
id|sun4_clock_probe
c_func
(paren
)paren
suffix:semicolon
r_else
id|clock_probe
c_func
(paren
)paren
suffix:semicolon
id|sparc_init_timers
c_func
(paren
id|timer_interrupt
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
r_if
c_cond
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4
op_or
id|SM_4_330
)paren
)paren
(brace
macro_line|#endif
id|mregs
op_assign
(paren
r_struct
id|mostek48t02
op_star
)paren
id|mstk48t02_regs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mregs
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Something wrong, clock regs not mapped yet.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
id|mregs-&gt;creg
op_or_assign
id|MSTK_CREG_READ
suffix:semicolon
id|sec
op_assign
id|MSTK_REG_SEC
c_func
(paren
id|mregs
)paren
suffix:semicolon
id|min
op_assign
id|MSTK_REG_MIN
c_func
(paren
id|mregs
)paren
suffix:semicolon
id|hour
op_assign
id|MSTK_REG_HOUR
c_func
(paren
id|mregs
)paren
suffix:semicolon
id|day
op_assign
id|MSTK_REG_DOM
c_func
(paren
id|mregs
)paren
suffix:semicolon
id|mon
op_assign
id|MSTK_REG_MONTH
c_func
(paren
id|mregs
)paren
suffix:semicolon
id|year
op_assign
id|MSTK_CVT_YEAR
c_func
(paren
id|MSTK_REG_YEAR
c_func
(paren
id|mregs
)paren
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
(paren
id|INITIAL_JIFFIES
op_mod
id|HZ
)paren
op_star
(paren
id|NSEC_PER_SEC
op_div
id|HZ
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|wall_to_monotonic
comma
op_minus
id|xtime.tv_sec
comma
op_minus
id|xtime.tv_nsec
)paren
suffix:semicolon
id|mregs-&gt;creg
op_and_assign
op_complement
id|MSTK_CREG_READ
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|mostek_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
)brace
r_else
r_if
c_cond
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4
op_or
id|SM_4_260
)paren
)paren
(brace
multiline_comment|/* initialise the intersil on sun4 */
id|iregs
op_assign
id|intersil_clock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iregs
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Something wrong, clock regs not mapped yet.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|intersil_intr
c_func
(paren
id|intersil_clock
comma
id|INTERSIL_INT_100HZ
)paren
suffix:semicolon
id|disable_pil_irq
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|intersil_stop
c_func
(paren
id|iregs
)paren
suffix:semicolon
id|intersil_read_intr
c_func
(paren
id|intersil_clock
comma
id|temp
)paren
suffix:semicolon
id|temp
op_assign
id|iregs-&gt;clk.int_csec
suffix:semicolon
id|sec
op_assign
id|iregs-&gt;clk.int_sec
suffix:semicolon
id|min
op_assign
id|iregs-&gt;clk.int_min
suffix:semicolon
id|hour
op_assign
id|iregs-&gt;clk.int_hour
suffix:semicolon
id|day
op_assign
id|iregs-&gt;clk.int_day
suffix:semicolon
id|mon
op_assign
id|iregs-&gt;clk.int_month
suffix:semicolon
id|year
op_assign
id|MSTK_CVT_YEAR
c_func
(paren
id|iregs-&gt;clk.int_year
)paren
suffix:semicolon
id|enable_pil_irq
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|intersil_start
c_func
(paren
id|iregs
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
(paren
id|INITIAL_JIFFIES
op_mod
id|HZ
)paren
op_star
(paren
id|NSEC_PER_SEC
op_div
id|HZ
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|wall_to_monotonic
comma
op_minus
id|xtime.tv_sec
comma
op_minus
id|xtime.tv_nsec
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%u/%u/%u %u:%u:%u&bslash;n&quot;
comma
id|day
comma
id|mon
comma
id|year
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Now that OBP ticker has been silenced, it is safe to enable IRQ. */
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|time_init
r_void
id|__init
id|time_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PCI
r_extern
r_void
id|pci_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcic_present
c_func
(paren
)paren
)paren
(brace
id|pci_time_init
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|sbus_time_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_gettimeoffset
r_extern
id|__inline__
r_int
r_int
id|do_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_return
(paren
op_star
id|master_l10_counter
op_rshift
l_int|10
)paren
op_amp
l_int|0x1fffff
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns nanoseconds&n; * XXX This is a suboptimal implementation.&n; */
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
r_return
(paren
r_int
r_int
r_int
)paren
id|jiffies
op_star
(paren
l_int|1000000000
op_div
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/* Ok, my cute asm atomicity trick doesn&squot;t work anymore.&n; * There are just too many variables that need to be protected&n; * now (both members of xtime, wall_jiffies, et al.)&n; */
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
id|seq
suffix:semicolon
r_int
r_int
id|usec
comma
id|sec
suffix:semicolon
r_int
r_int
id|max_ntp_tick
op_assign
id|tick_usec
op_minus
id|tickadj
suffix:semicolon
r_do
(brace
r_int
r_int
id|lost
suffix:semicolon
id|seq
op_assign
id|read_seqbegin_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|usec
op_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
id|lost
op_assign
id|jiffies
op_minus
id|wall_jiffies
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If time_adjust is negative then NTP is slowing the clock&n;&t;&t; * so make sure not to go into next possible interval.&n;&t;&t; * Better to lose some accuracy than have time go backwards..&n;&t;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|time_adjust
OL
l_int|0
)paren
)paren
(brace
id|usec
op_assign
id|min
c_func
(paren
id|usec
comma
id|max_ntp_tick
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lost
)paren
id|usec
op_add_assign
id|lost
op_star
id|max_ntp_tick
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|lost
)paren
)paren
id|usec
op_add_assign
id|lost
op_star
id|tick_usec
suffix:semicolon
id|sec
op_assign
id|xtime.tv_sec
suffix:semicolon
id|usec
op_add_assign
(paren
id|xtime.tv_nsec
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|read_seqretry_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|seq
comma
id|flags
)paren
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
DECL|variable|do_gettimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_gettimeofday
)paren
suffix:semicolon
DECL|function|do_settimeofday
r_int
id|do_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
r_int
id|ret
suffix:semicolon
id|write_seqlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|ret
op_assign
id|bus_do_settimeofday
c_func
(paren
id|tv
)paren
suffix:semicolon
id|write_sequnlock_irq
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|clock_was_set
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|do_settimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_settimeofday
)paren
suffix:semicolon
DECL|function|sbus_do_settimeofday
r_static
r_int
id|sbus_do_settimeofday
c_func
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
id|time_t
id|wtm_sec
comma
id|sec
op_assign
id|tv-&gt;tv_sec
suffix:semicolon
r_int
id|wtm_nsec
comma
id|nsec
op_assign
id|tv-&gt;tv_nsec
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|tv-&gt;tv_nsec
op_ge
id|NSEC_PER_SEC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * This is revolting. We need to set &quot;xtime&quot; correctly. However, the&n;&t; * value in this location is the value at the most recent update of&n;&t; * wall time.  Discover what correction gettimeofday() would have&n;&t; * made, and then undo it!&n;&t; */
id|nsec
op_sub_assign
l_int|1000
op_star
(paren
id|do_gettimeoffset
c_func
(paren
)paren
op_plus
(paren
id|jiffies
op_minus
id|wall_jiffies
)paren
op_star
(paren
id|USEC_PER_SEC
op_div
id|HZ
)paren
)paren
suffix:semicolon
id|wtm_sec
op_assign
id|wall_to_monotonic.tv_sec
op_plus
(paren
id|xtime.tv_sec
op_minus
id|sec
)paren
suffix:semicolon
id|wtm_nsec
op_assign
id|wall_to_monotonic.tv_nsec
op_plus
(paren
id|xtime.tv_nsec
op_minus
id|nsec
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|xtime
comma
id|sec
comma
id|nsec
)paren
suffix:semicolon
id|set_normalized_timespec
c_func
(paren
op_amp
id|wall_to_monotonic
comma
id|wtm_sec
comma
id|wtm_nsec
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you won&squot;t notice until after reboot!&n; */
DECL|function|set_rtc_mmss
r_static
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|real_seconds
comma
id|real_minutes
comma
id|mostek_minutes
suffix:semicolon
r_struct
id|mostek48t02
op_star
id|regs
op_assign
(paren
r_struct
id|mostek48t02
op_star
)paren
id|mstk48t02_regs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef CONFIG_SUN4
r_struct
id|intersil
op_star
id|iregs
op_assign
id|intersil_clock
suffix:semicolon
r_int
id|temp
suffix:semicolon
macro_line|#endif
multiline_comment|/* Not having a register set can lead to trouble. */
r_if
c_cond
(paren
op_logical_neg
id|regs
)paren
(brace
macro_line|#ifdef CONFIG_SUN4
r_if
c_cond
(paren
op_logical_neg
id|iregs
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|temp
op_assign
id|iregs-&gt;clk.int_csec
suffix:semicolon
id|mostek_minutes
op_assign
id|iregs-&gt;clk.int_min
suffix:semicolon
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|mostek_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|mostek_minutes
)paren
OL
l_int|30
)paren
(brace
id|intersil_stop
c_func
(paren
id|iregs
)paren
suffix:semicolon
id|iregs-&gt;clk.int_sec
op_assign
id|real_seconds
suffix:semicolon
id|iregs-&gt;clk.int_min
op_assign
id|real_minutes
suffix:semicolon
id|intersil_start
c_func
(paren
id|iregs
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_mmss: can&squot;t update from %d to %d&bslash;n&quot;
comma
id|mostek_minutes
comma
id|real_minutes
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mostek_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Read the current RTC minutes. */
id|regs-&gt;creg
op_or_assign
id|MSTK_CREG_READ
suffix:semicolon
id|mostek_minutes
op_assign
id|MSTK_REG_MIN
c_func
(paren
id|regs
)paren
suffix:semicolon
id|regs-&gt;creg
op_and_assign
op_complement
id|MSTK_CREG_READ
suffix:semicolon
multiline_comment|/*&n;&t; * since we&squot;re only adjusting minutes and seconds,&n;&t; * don&squot;t interfere with hour overflow. This avoids&n;&t; * messing with unknown time zones but requires your&n;&t; * RTC not to be off by more than 15 minutes&n;&t; */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|mostek_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|mostek_minutes
)paren
OL
l_int|30
)paren
(brace
id|regs-&gt;creg
op_or_assign
id|MSTK_CREG_WRITE
suffix:semicolon
id|MSTK_SET_REG_SEC
c_func
(paren
id|regs
comma
id|real_seconds
)paren
suffix:semicolon
id|MSTK_SET_REG_MIN
c_func
(paren
id|regs
comma
id|real_minutes
)paren
suffix:semicolon
id|regs-&gt;creg
op_and_assign
op_complement
id|MSTK_CREG_WRITE
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mostek_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mostek_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
eof
