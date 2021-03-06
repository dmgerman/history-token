multiline_comment|/*&n; * linux/arch/arm/mach-h720x/common.c&n; *&n; * Copyright (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *               2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *               2004 Sascha Hauer    &lt;s.hauer@pengutronix.de&gt;&n; *&n; * common stuff for Hynix h720x processors&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/mach/dma.h&gt;
macro_line|#if 0
mdefine_line|#define IRQDBG(args...) printk(args)
macro_line|#else
DECL|macro|IRQDBG
mdefine_line|#define IRQDBG(args...) do {} while(0)
macro_line|#endif
DECL|function|arch_dma_init
r_void
id|__init
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
(brace
)brace
multiline_comment|/*&n; * Return usecs since last timer reload&n; * (timercount * (usecs perjiffie)) / (ticks per jiffie)&n; */
DECL|function|h720x_gettimeoffset
r_int
r_int
id|h720x_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|CPU_REG
(paren
id|TIMER_VIRT
comma
id|TM0_COUNT
)paren
op_star
id|tick_usec
)paren
op_div
id|LATCH
suffix:semicolon
)brace
multiline_comment|/*&n; * mask Global irq&squot;s&n; */
DECL|function|mask_global_irq
r_static
r_void
id|mask_global_irq
(paren
r_int
r_int
id|irq
)paren
(brace
id|CPU_REG
(paren
id|IRQC_VIRT
comma
id|IRQC_IER
)paren
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * unmask Global irq&squot;s&n; */
DECL|function|unmask_global_irq
r_static
r_void
id|unmask_global_irq
(paren
r_int
r_int
id|irq
)paren
(brace
id|CPU_REG
(paren
id|IRQC_VIRT
comma
id|IRQC_IER
)paren
op_or_assign
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ack GPIO irq&squot;s&n; * Ack only for edge triggered int&squot;s valid&n; */
DECL|function|ack_gpio_irq
r_static
r_void
r_inline
id|ack_gpio_irq
c_func
(paren
id|u32
id|irq
)paren
(brace
id|u32
id|reg_base
op_assign
id|GPIO_VIRT
c_func
(paren
id|IRQ_TO_REGNO
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|u32
id|bit
op_assign
id|IRQ_TO_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CPU_REG
(paren
id|reg_base
comma
id|GPIO_EDGE
)paren
op_amp
id|bit
)paren
)paren
id|CPU_REG
(paren
id|reg_base
comma
id|GPIO_CLR
)paren
op_assign
id|bit
suffix:semicolon
)brace
multiline_comment|/*&n; * mask GPIO irq&squot;s&n; */
DECL|function|mask_gpio_irq
r_static
r_void
r_inline
id|mask_gpio_irq
c_func
(paren
id|u32
id|irq
)paren
(brace
id|u32
id|reg_base
op_assign
id|GPIO_VIRT
c_func
(paren
id|IRQ_TO_REGNO
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|u32
id|bit
op_assign
id|IRQ_TO_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
id|CPU_REG
(paren
id|reg_base
comma
id|GPIO_MASK
)paren
op_and_assign
op_complement
id|bit
suffix:semicolon
)brace
multiline_comment|/*&n; * unmask GPIO irq&squot;s&n; */
DECL|function|unmask_gpio_irq
r_static
r_void
r_inline
id|unmask_gpio_irq
c_func
(paren
id|u32
id|irq
)paren
(brace
id|u32
id|reg_base
op_assign
id|GPIO_VIRT
c_func
(paren
id|IRQ_TO_REGNO
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|u32
id|bit
op_assign
id|IRQ_TO_BIT
c_func
(paren
id|irq
)paren
suffix:semicolon
id|CPU_REG
(paren
id|reg_base
comma
id|GPIO_MASK
)paren
op_or_assign
id|bit
suffix:semicolon
)brace
r_static
r_void
DECL|function|h720x_gpio_handler
id|h720x_gpio_handler
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
id|irq
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
id|IRQDBG
c_func
(paren
l_string|&quot;%s irq: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
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
(brace
id|IRQDBG
c_func
(paren
l_string|&quot;handling irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
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
)brace
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
r_static
r_void
DECL|function|h720x_gpioa_demux_handler
id|h720x_gpioa_demux_handler
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
c_func
(paren
id|GPIO_A_VIRT
comma
id|GPIO_STAT
)paren
suffix:semicolon
id|irq
op_assign
id|IRQ_CHAINED_GPIOA
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|IRQDBG
c_func
(paren
l_string|&quot;%s mask: 0x%08x irq: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|mask
comma
id|irq
)paren
suffix:semicolon
id|h720x_gpio_handler
c_func
(paren
id|mask
comma
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|h720x_gpiob_demux_handler
id|h720x_gpiob_demux_handler
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
c_func
(paren
id|GPIO_B_VIRT
comma
id|GPIO_STAT
)paren
suffix:semicolon
id|irq
op_assign
id|IRQ_CHAINED_GPIOB
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|IRQDBG
c_func
(paren
l_string|&quot;%s mask: 0x%08x irq: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|mask
comma
id|irq
)paren
suffix:semicolon
id|h720x_gpio_handler
c_func
(paren
id|mask
comma
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|h720x_gpioc_demux_handler
id|h720x_gpioc_demux_handler
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
c_func
(paren
id|GPIO_C_VIRT
comma
id|GPIO_STAT
)paren
suffix:semicolon
id|irq
op_assign
id|IRQ_CHAINED_GPIOC
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|IRQDBG
c_func
(paren
l_string|&quot;%s mask: 0x%08x irq: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|mask
comma
id|irq
)paren
suffix:semicolon
id|h720x_gpio_handler
c_func
(paren
id|mask
comma
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|h720x_gpiod_demux_handler
id|h720x_gpiod_demux_handler
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
c_func
(paren
id|GPIO_D_VIRT
comma
id|GPIO_STAT
)paren
suffix:semicolon
id|irq
op_assign
id|IRQ_CHAINED_GPIOD
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|IRQDBG
c_func
(paren
l_string|&quot;%s mask: 0x%08x irq: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|mask
comma
id|irq
)paren
suffix:semicolon
id|h720x_gpio_handler
c_func
(paren
id|mask
comma
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CPU_H7202
r_static
r_void
DECL|function|h720x_gpioe_demux_handler
id|h720x_gpioe_demux_handler
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
c_func
(paren
id|GPIO_E_VIRT
comma
id|GPIO_STAT
)paren
suffix:semicolon
id|irq
op_assign
id|IRQ_CHAINED_GPIOE
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|IRQDBG
c_func
(paren
l_string|&quot;%s mask: 0x%08x irq: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|mask
comma
id|irq
)paren
suffix:semicolon
id|h720x_gpio_handler
c_func
(paren
id|mask
comma
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|h720x_global_chip
r_static
r_struct
id|irqchip
id|h720x_global_chip
op_assign
(brace
dot
id|ack
op_assign
id|mask_global_irq
comma
dot
id|mask
op_assign
id|mask_global_irq
comma
dot
id|unmask
op_assign
id|unmask_global_irq
comma
)brace
suffix:semicolon
DECL|variable|h720x_gpio_chip
r_static
r_struct
id|irqchip
id|h720x_gpio_chip
op_assign
(brace
dot
id|ack
op_assign
id|ack_gpio_irq
comma
dot
id|mask
op_assign
id|mask_gpio_irq
comma
dot
id|unmask
op_assign
id|unmask_gpio_irq
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize IRQ&squot;s, mask all, enable multiplexed irq&squot;s&n; */
DECL|function|h720x_init_irq
r_void
id|__init
id|h720x_init_irq
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/* Mask global irq&squot;s */
id|CPU_REG
(paren
id|IRQC_VIRT
comma
id|IRQC_IER
)paren
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* Mask all multiplexed irq&squot;s */
id|CPU_REG
(paren
id|GPIO_A_VIRT
comma
id|GPIO_MASK
)paren
op_assign
l_int|0x0
suffix:semicolon
id|CPU_REG
(paren
id|GPIO_B_VIRT
comma
id|GPIO_MASK
)paren
op_assign
l_int|0x0
suffix:semicolon
id|CPU_REG
(paren
id|GPIO_C_VIRT
comma
id|GPIO_MASK
)paren
op_assign
l_int|0x0
suffix:semicolon
id|CPU_REG
(paren
id|GPIO_D_VIRT
comma
id|GPIO_MASK
)paren
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* Initialize global IRQ&squot;s, fast path */
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_GLBL_IRQS
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|h720x_global_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize multiplexed IRQ&squot;s, slow path */
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_CHAINED_GPIOA
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
op_le
id|IRQ_CHAINED_GPIOD
c_func
(paren
l_int|31
)paren
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|h720x_gpio_chip
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
id|IRQ_GPIOA
comma
id|h720x_gpioa_demux_handler
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIOB
comma
id|h720x_gpiob_demux_handler
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIOC
comma
id|h720x_gpioc_demux_handler
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|IRQ_GPIOD
comma
id|h720x_gpiod_demux_handler
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_H7202
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_CHAINED_GPIOE
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
op_le
id|IRQ_CHAINED_GPIOE
c_func
(paren
l_int|31
)paren
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|h720x_gpio_chip
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
id|IRQ_GPIOE
comma
id|h720x_gpioe_demux_handler
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Enable multiplexed irq&squot;s */
id|CPU_REG
(paren
id|IRQC_VIRT
comma
id|IRQC_IER
)paren
op_assign
id|IRQ_ENA_MUX
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|h720x_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_VIRT
comma
id|IO_PHYS
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* Initialize io tables */
DECL|function|h720x_map_io
r_void
id|__init
id|h720x_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|h720x_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|h720x_io_desc
)paren
)paren
suffix:semicolon
)brace
eof
