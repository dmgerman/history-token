multiline_comment|/*&n; * linux/arch/arm/mach-h720x/cpu-h7202.c&n; *&n; * Copyright (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *               2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *               2004 Sascha Hauer    &lt;s.hauer@pengutronix.de&gt;&n; *&n; * processor specific stuff for the Hynix h7201&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;linux/device.h&gt;
DECL|variable|h7202ps2_resources
r_static
r_struct
id|resource
id|h7202ps2_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0x8002c000
comma
dot
id|end
op_assign
l_int|0x8002c040
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
id|IRQ_PS2
comma
dot
id|end
op_assign
id|IRQ_PS2
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|h7202ps2_device
r_static
r_struct
id|platform_device
id|h7202ps2_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;h7202ps2&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|h7202ps2_resources
)paren
comma
dot
id|resource
op_assign
id|h7202ps2_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|h7202ps2_device
comma
)brace
suffix:semicolon
r_extern
r_int
r_int
id|h720x_gettimeoffset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|h720x_init_irq
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Although we have two interrupt lines for the timers, we only have one&n; * status register which clears all pending timer interrupts on reading. So&n; * we have to handle all timer interrupts in one place.&n; */
r_static
r_void
DECL|function|h7202_timerx_demux_handler
id|h7202_timerx_demux_handler
c_func
(paren
r_int
r_int
id|irq_unused
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|mask
comma
id|irq
suffix:semicolon
id|mask
op_assign
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TIMER_TOPSTAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|TSTAT_T0INT
)paren
(brace
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_eq
id|TSTAT_T0INT
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
id|irq
op_assign
id|IRQ_TIMER1
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_while
c_loop
(paren
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
id|irq
op_increment
suffix:semicolon
id|desc
op_increment
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Timer interrupt handler&n; */
r_static
id|irqreturn_t
DECL|function|h7202_timer_interrupt
id|h7202_timer_interrupt
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
id|h7202_timerx_demux_handler
c_func
(paren
l_int|0
comma
l_int|NULL
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * mask multiplexed timer irq&squot;s&n; */
DECL|function|mask_timerx_irq
r_static
r_void
r_inline
id|mask_timerx_irq
(paren
id|u32
id|irq
)paren
(brace
r_int
r_int
id|bit
suffix:semicolon
id|bit
op_assign
l_int|2
op_lshift
(paren
(paren
id|irq
op_eq
id|IRQ_TIMER64B
)paren
ques
c_cond
l_int|4
suffix:colon
(paren
id|irq
op_minus
id|IRQ_TIMER1
)paren
)paren
suffix:semicolon
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TIMER_TOPCTRL
)paren
op_and_assign
op_complement
id|bit
suffix:semicolon
)brace
multiline_comment|/*&n; * unmask multiplexed timer irq&squot;s&n; */
DECL|function|unmask_timerx_irq
r_static
r_void
r_inline
id|unmask_timerx_irq
(paren
id|u32
id|irq
)paren
(brace
r_int
r_int
id|bit
suffix:semicolon
id|bit
op_assign
l_int|2
op_lshift
(paren
(paren
id|irq
op_eq
id|IRQ_TIMER64B
)paren
ques
c_cond
l_int|4
suffix:colon
(paren
id|irq
op_minus
id|IRQ_TIMER1
)paren
)paren
suffix:semicolon
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TIMER_TOPCTRL
)paren
op_or_assign
id|bit
suffix:semicolon
)brace
DECL|variable|h7202_timerx_chip
r_static
r_struct
id|irqchip
id|h7202_timerx_chip
op_assign
(brace
dot
id|ack
op_assign
id|mask_timerx_irq
comma
dot
id|mask
op_assign
id|mask_timerx_irq
comma
dot
id|unmask
op_assign
id|unmask_timerx_irq
comma
)brace
suffix:semicolon
DECL|variable|h7202_timer_irq
r_static
r_struct
id|irqaction
id|h7202_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;h7202 Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|h7202_timer_interrupt
)brace
suffix:semicolon
multiline_comment|/*&n; * Setup TIMER0 as system timer&n; */
DECL|function|h7202_init_time
r_void
id|__init
id|h7202_init_time
c_func
(paren
r_void
)paren
(brace
id|gettimeoffset
op_assign
id|h720x_gettimeoffset
suffix:semicolon
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TM0_PERIOD
)paren
op_assign
id|LATCH
suffix:semicolon
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TM0_CTRL
)paren
op_assign
id|TM_RESET
suffix:semicolon
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TM0_CTRL
)paren
op_assign
id|TM_REPEAT
op_or
id|TM_START
suffix:semicolon
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TIMER_TOPCTRL
)paren
op_assign
id|ENABLE_TM0_INTR
op_or
id|TIMER_ENABLE_BIT
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_TIMER0
comma
op_amp
id|h7202_timer_irq
)paren
suffix:semicolon
)brace
DECL|function|h7202_init_irq
r_void
id|__init
id|h7202_init_irq
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
id|CPU_REG
(paren
id|GPIO_E_VIRT
comma
id|GPIO_MASK
)paren
op_assign
l_int|0x0
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_TIMER1
suffix:semicolon
id|irq
OL
id|IRQ_CHAINED_TIMERX
c_func
(paren
id|NR_TIMERX_IRQS
)paren
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|mask_timerx_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|h7202_timerx_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_edge_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_VALID
)paren
suffix:semicolon
)brace
id|set_irq_chained_handler
c_func
(paren
id|IRQ_TIMERX
comma
id|h7202_timerx_demux_handler
)paren
suffix:semicolon
id|h720x_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|init_hw_h7202
r_void
id|__init
id|init_hw_h7202
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Enable clocks */
id|CPU_REG
(paren
id|PMU_BASE
comma
id|PMU_PLL_CTRL
)paren
op_or_assign
id|PLL_2_EN
op_or
id|PLL_1_EN
op_or
id|PLL_3_MUTE
suffix:semicolon
(paren
r_void
)paren
id|platform_add_devices
c_func
(paren
id|devices
comma
id|ARRAY_SIZE
c_func
(paren
id|devices
)paren
)paren
suffix:semicolon
)brace
eof
