multiline_comment|/*&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * Galileo Technology chip interrupt handler&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
multiline_comment|/*&n; * These are interrupt handlers for the GT on-chip interrupts.  They all come&n; * in to the MIPS on a single interrupt line, and have to be handled and ack&squot;ed&n; * differently than other MIPS interrupts.&n; */
DECL|function|gt64120_irq
r_static
r_void
id|gt64120_irq
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
id|irq_src
comma
id|int_high_src
comma
id|irq_src_mask
comma
id|int_high_src_mask
suffix:semicolon
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
id|irq_src
op_assign
id|GT_READ
c_func
(paren
id|GT_INTRCAUSE_OFS
)paren
suffix:semicolon
id|irq_src_mask
op_assign
id|GT_READ
c_func
(paren
id|GT_INTRMASK_OFS
)paren
suffix:semicolon
id|int_high_src
op_assign
id|GT_READ
c_func
(paren
id|GT_HINTRCAUSE_OFS
)paren
suffix:semicolon
id|int_high_src_mask
op_assign
id|GT_READ
c_func
(paren
id|GT_HINTRMASK_OFS
)paren
suffix:semicolon
id|irq_src
op_assign
id|irq_src
op_amp
id|irq_src_mask
suffix:semicolon
id|int_high_src
op_assign
id|int_high_src
op_amp
id|int_high_src_mask
suffix:semicolon
r_if
c_cond
(paren
id|irq_src
op_amp
l_int|0x00000800
)paren
(brace
multiline_comment|/* Check for timer interrupt */
id|handled
op_assign
l_int|1
suffix:semicolon
id|irq_src
op_and_assign
op_complement
l_int|0x00000800
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
)brace
id|GT_WRITE
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
l_int|0
)paren
suffix:semicolon
id|GT_WRITE
c_func
(paren
id|GT_HINTRCAUSE_OFS
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initializes timer using galileo&squot;s built in timer.&n; */
macro_line|#ifdef CONFIG_SYSCLK_100
DECL|macro|Sys_clock
mdefine_line|#define Sys_clock (100 * 1000000)&t;
singleline_comment|// 100 MHz
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCLK_83
DECL|macro|Sys_clock
mdefine_line|#define Sys_clock (83.333 * 1000000)&t;
singleline_comment|// 83.333 MHz
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCLK_75
DECL|macro|Sys_clock
mdefine_line|#define Sys_clock (75 * 1000000)&t;
singleline_comment|// 75 MHz
macro_line|#endif
multiline_comment|/*&n; * This will ignore the standard MIPS timer interrupt handler that is passed in&n; * as *irq (=irq0 in ../kernel/time.c).  We will do our own timer interrupt&n; * handling.&n; */
DECL|function|gt64120_time_init
r_void
id|gt64120_time_init
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|irqaction
id|timer
suffix:semicolon
multiline_comment|/* Disable timer first */
id|GT_WRITE
c_func
(paren
id|GT_TC_CONTROL_OFS
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Load timer value for 100 Hz */
id|GT_WRITE
c_func
(paren
id|GT_TC3_OFS
comma
id|Sys_clock
op_div
l_int|100
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the IRQ structure entry for the timer.  Since we&squot;re too early&n;&t; * in the boot process to use the &quot;request_irq()&quot; call, we&squot;ll hard-code&n;&t; * the values to the correct interrupt line.&n;&t; */
id|timer.handler
op_assign
id|gt64120_irq
suffix:semicolon
id|timer.flags
op_assign
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
suffix:semicolon
id|timer.name
op_assign
l_string|&quot;timer&quot;
suffix:semicolon
id|timer.dev_id
op_assign
l_int|NULL
suffix:semicolon
id|timer.next
op_assign
l_int|NULL
suffix:semicolon
id|timer.mask
op_assign
id|CPU_MASK_NONE
suffix:semicolon
id|irq_desc
(braket
id|GT_TIMER
)braket
dot
id|action
op_assign
op_amp
id|timer
suffix:semicolon
id|enable_irq
c_func
(paren
id|GT_TIMER
)paren
suffix:semicolon
multiline_comment|/* Enable timer ints */
id|GT_WRITE
c_func
(paren
id|GT_TC_CONTROL_OFS
comma
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* clear Cause register first */
id|GT_WRITE
c_func
(paren
id|GT_INTRCAUSE_OFS
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Unmask timer int */
id|GT_WRITE
c_func
(paren
id|GT_INTRMASK_OFS
comma
l_int|0x800
)paren
suffix:semicolon
multiline_comment|/* Clear High int register */
id|GT_WRITE
c_func
(paren
id|GT_HINTRCAUSE_OFS
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Mask All interrupts at High cause interrupt */
id|GT_WRITE
c_func
(paren
id|GT_HINTRMASK_OFS
comma
l_int|0x0
)paren
suffix:semicolon
)brace
eof
