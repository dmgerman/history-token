multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*&n; * These are routines to set up and handle interrupts from the&n; * sb1250 general purpose timer 0.  We&squot;re using the timer as a&n; * system clock, so we set it up to run at 100 Hz.  On every&n; * interrupt, we update our idea of what the time of day is,&n; * then call do_timer() in the architecture-independent kernel&n; * code to do general bookkeeping (e.g. update jiffies, run&n; * bottom halves, etc.)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_int.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_scd.h&gt;
DECL|macro|IMR_IP2_VAL
mdefine_line|#define IMR_IP2_VAL&t;K_INT_MAP_I0
DECL|macro|IMR_IP3_VAL
mdefine_line|#define IMR_IP3_VAL&t;K_INT_MAP_I1
DECL|macro|IMR_IP4_VAL
mdefine_line|#define IMR_IP4_VAL&t;K_INT_MAP_I2
r_extern
r_int
id|sb1250_steal_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
DECL|function|sb1250_time_init
r_void
id|sb1250_time_init
c_func
(paren
r_void
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
r_int
id|irq
op_assign
id|K_INT_TIMER_0
op_plus
id|cpu
suffix:semicolon
multiline_comment|/* Only have 4 general purpose timers */
r_if
c_cond
(paren
id|cpu
OG
l_int|3
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpu
)paren
(brace
multiline_comment|/* Use our own gettimeoffset() routine */
id|do_gettimeoffset
op_assign
id|sb1250_gettimeoffset
suffix:semicolon
)brace
id|sb1250_mask_irq
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* Map the timer interrupt to ip[4] of this cpu */
id|__raw_writeq
c_func
(paren
id|IMR_IP4_VAL
comma
id|KSEG1
op_plus
id|A_IMR_REGISTER
c_func
(paren
id|cpu
comma
id|R_IMR_INTERRUPT_MAP_BASE
)paren
op_plus
(paren
id|irq
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
multiline_comment|/* the general purpose timer ticks at 1 Mhz independent if the rest of the system */
multiline_comment|/* Disable the timer and set up the count */
id|__raw_writeq
c_func
(paren
l_int|0
comma
id|KSEG1
op_plus
id|A_SCD_TIMER_REGISTER
c_func
(paren
id|cpu
comma
id|R_SCD_TIMER_CFG
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SIMULATION
id|__raw_writeq
c_func
(paren
l_int|50000
op_div
id|HZ
comma
id|KSEG1
op_plus
id|A_SCD_TIMER_REGISTER
c_func
(paren
id|cpu
comma
id|R_SCD_TIMER_INIT
)paren
)paren
suffix:semicolon
macro_line|#else
id|__raw_writeq
c_func
(paren
l_int|1000000
op_div
id|HZ
comma
id|KSEG1
op_plus
id|A_SCD_TIMER_REGISTER
c_func
(paren
id|cpu
comma
id|R_SCD_TIMER_INIT
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set the timer running */
id|__raw_writeq
c_func
(paren
id|M_SCD_TIMER_ENABLE
op_or
id|M_SCD_TIMER_MODE_CONTINUOUS
comma
id|KSEG1
op_plus
id|A_SCD_TIMER_REGISTER
c_func
(paren
id|cpu
comma
id|R_SCD_TIMER_CFG
)paren
)paren
suffix:semicolon
id|sb1250_unmask_irq
c_func
(paren
id|cpu
comma
id|irq
)paren
suffix:semicolon
id|sb1250_steal_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This interrupt is &quot;special&quot; in that it doesn&squot;t use the request_irq&n;&t; * way to hook the irq line.  The timer interrupt is initialized early&n;&t; * enough to make this a major pain, and it&squot;s also firing enough to&n;&t; * warrant a bit of special case code.  sb1250_timer_interrupt is&n;&t; * called directly from irq_handler.S when IP[4] is set during an&n;&t; * interrupt&n;&t; */
)brace
DECL|function|sb1250_timer_interrupt
r_void
id|sb1250_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_extern
id|asmlinkage
r_void
id|ll_local_timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
id|irq
op_assign
id|K_INT_TIMER_0
op_plus
id|cpu
suffix:semicolon
multiline_comment|/* Reset the timer */
id|____raw_writeq
c_func
(paren
id|M_SCD_TIMER_ENABLE
op_or
id|M_SCD_TIMER_MODE_CONTINUOUS
comma
id|KSEG1
op_plus
id|A_SCD_TIMER_REGISTER
c_func
(paren
id|cpu
comma
id|R_SCD_TIMER_CFG
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * CPU 0 handles the global timer interrupt job&n;&t; */
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
id|ll_timer_interrupt
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * every CPU should do profiling and process accouting&n;&t; */
id|ll_local_timer_interrupt
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We use our own do_gettimeoffset() instead of the generic one,&n; * because the generic one does not work for SMP case.&n; * In addition, since we use general timer 0 for system time,&n; * we can get accurate intra-jiffy offset without calibration.&n; */
DECL|function|sb1250_gettimeoffset
r_int
r_int
id|sb1250_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|count
op_assign
id|__raw_readq
c_func
(paren
id|KSEG1
op_plus
id|A_SCD_TIMER_REGISTER
c_func
(paren
l_int|0
comma
id|R_SCD_TIMER_CNT
)paren
)paren
suffix:semicolon
r_return
l_int|1000000
op_div
id|HZ
op_minus
id|count
suffix:semicolon
)brace
eof
