multiline_comment|/*&n; * arch/arm/mach-ixp4xx/common.c&n; *&n; * Generic code shared across all IXP4XX platforms&n; *&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2002 (c) Intel Corporation&n; * Copyright 2003-2004 (c) MontaVista, Software, Inc. &n; * &n; * This file is licensed under  the terms of the GNU General Public &n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
multiline_comment|/*************************************************************************&n; * GPIO acces functions&n; *************************************************************************/
multiline_comment|/*&n; * Configure GPIO line for input, interrupt, or output operation&n; *&n; * TODO: Enable/disable the irq_desc based on interrupt or output mode.&n; * TODO: Should these be named ixp4xx_gpio_?&n; */
DECL|function|gpio_line_config
r_void
id|gpio_line_config
c_func
(paren
id|u8
id|line
comma
id|u32
id|style
)paren
(brace
id|u32
id|enable
suffix:semicolon
r_volatile
id|u32
op_star
id|int_reg
suffix:semicolon
id|u32
id|int_style
suffix:semicolon
id|enable
op_assign
op_star
id|IXP4XX_GPIO_GPOER
suffix:semicolon
r_if
c_cond
(paren
id|style
op_amp
id|IXP4XX_GPIO_OUT
)paren
(brace
id|enable
op_and_assign
op_complement
(paren
(paren
l_int|1
)paren
op_lshift
id|line
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|style
op_amp
id|IXP4XX_GPIO_IN
)paren
(brace
id|enable
op_or_assign
(paren
(paren
l_int|1
)paren
op_lshift
id|line
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|style
op_amp
id|IXP4XX_GPIO_INTSTYLE_MASK
)paren
(brace
r_case
(paren
id|IXP4XX_GPIO_ACTIVE_HIGH
)paren
suffix:colon
id|int_style
op_assign
id|IXP4XX_GPIO_STYLE_ACTIVE_HIGH
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|IXP4XX_GPIO_ACTIVE_LOW
)paren
suffix:colon
id|int_style
op_assign
id|IXP4XX_GPIO_STYLE_ACTIVE_LOW
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|IXP4XX_GPIO_RISING_EDGE
)paren
suffix:colon
id|int_style
op_assign
id|IXP4XX_GPIO_STYLE_RISING_EDGE
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|IXP4XX_GPIO_FALLING_EDGE
)paren
suffix:colon
id|int_style
op_assign
id|IXP4XX_GPIO_STYLE_FALLING_EDGE
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|IXP4XX_GPIO_TRANSITIONAL
)paren
suffix:colon
id|int_style
op_assign
id|IXP4XX_GPIO_STYLE_TRANSITIONAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|int_style
op_assign
id|IXP4XX_GPIO_STYLE_ACTIVE_HIGH
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line
op_ge
l_int|8
)paren
(brace
multiline_comment|/* pins 8-15 */
id|line
op_sub_assign
l_int|8
suffix:semicolon
id|int_reg
op_assign
id|IXP4XX_GPIO_GPIT2R
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* pins 0-7 */
id|int_reg
op_assign
id|IXP4XX_GPIO_GPIT1R
suffix:semicolon
)brace
multiline_comment|/* Clear the style for the appropriate pin */
op_star
id|int_reg
op_and_assign
op_complement
(paren
id|IXP4XX_GPIO_STYLE_CLEAR
op_lshift
(paren
id|line
op_star
id|IXP4XX_GPIO_STYLE_SIZE
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the new style */
op_star
id|int_reg
op_or_assign
(paren
id|int_style
op_lshift
(paren
id|line
op_star
id|IXP4XX_GPIO_STYLE_SIZE
)paren
)paren
suffix:semicolon
)brace
op_star
id|IXP4XX_GPIO_GPOER
op_assign
id|enable
suffix:semicolon
)brace
DECL|variable|gpio_line_config
id|EXPORT_SYMBOL
c_func
(paren
id|gpio_line_config
)paren
suffix:semicolon
multiline_comment|/*************************************************************************&n; * IXP4xx chipset I/O mapping&n; *************************************************************************/
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ixp4xx_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
multiline_comment|/* UART, Interrupt ctrl, GPIO, timers, NPEs, MACs, USB .... */
dot
r_virtual
op_assign
id|IXP4XX_PERIPHERAL_BASE_VIRT
comma
dot
id|physical
op_assign
id|IXP4XX_PERIPHERAL_BASE_PHYS
comma
dot
id|length
op_assign
id|IXP4XX_PERIPHERAL_REGION_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
multiline_comment|/* Expansion Bus Config Registers */
dot
r_virtual
op_assign
id|IXP4XX_EXP_CFG_BASE_VIRT
comma
dot
id|physical
op_assign
id|IXP4XX_EXP_CFG_BASE_PHYS
comma
dot
id|length
op_assign
id|IXP4XX_EXP_CFG_REGION_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
multiline_comment|/* PCI Registers */
dot
r_virtual
op_assign
id|IXP4XX_PCI_CFG_BASE_VIRT
comma
dot
id|physical
op_assign
id|IXP4XX_PCI_CFG_BASE_PHYS
comma
dot
id|length
op_assign
id|IXP4XX_PCI_CFG_REGION_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|ixp4xx_map_io
r_void
id|__init
id|ixp4xx_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|ixp4xx_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ixp4xx_io_desc
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*************************************************************************&n; * IXP4xx chipset IRQ handling&n; *&n; * TODO: GPIO IRQs should be marked invalid until the user of the IRQ&n; *       (be it PCI or something else) configures that GPIO line&n; *       as an IRQ. Also, we should use a different chip structure for &n; *       level-based GPIO vs edge-based GPIO. Currently nobody needs this as &n; *       all HW that&squot;s publically available uses level IRQs, so we&squot;ll&n; *       worry about it if/when we have HW to test.&n; **************************************************************************/
DECL|function|ixp4xx_irq_mask
r_static
r_void
id|ixp4xx_irq_mask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
op_star
id|IXP4XX_ICMR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
DECL|function|ixp4xx_irq_mask_ack
r_static
r_void
id|ixp4xx_irq_mask_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ixp4xx_irq_mask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|ixp4xx_irq_unmask
r_static
r_void
id|ixp4xx_irq_unmask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_static
r_int
id|irq2gpio
(braket
id|NR_IRQS
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
)brace
suffix:semicolon
r_int
id|line
op_assign
id|irq2gpio
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * This only works for LEVEL gpio IRQs as per the IXP4xx developer&squot;s&n;&t; * manual. If edge-triggered, need to move it to the mask_ack.&n;&t; * Nobody seems to be using the edge-triggered mode on the GPIOs. &n;&t; */
r_if
c_cond
(paren
id|line
OG
l_int|0
)paren
id|gpio_line_isr_clear
c_func
(paren
id|line
)paren
suffix:semicolon
op_star
id|IXP4XX_ICMR
op_or_assign
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ixp4xx_irq_chip
r_static
r_struct
id|irqchip
id|ixp4xx_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|ixp4xx_irq_mask_ack
comma
dot
id|mask
op_assign
id|ixp4xx_irq_mask
comma
dot
id|unmask
op_assign
id|ixp4xx_irq_unmask
comma
)brace
suffix:semicolon
DECL|function|ixp4xx_init_irq
r_void
id|__init
id|ixp4xx_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Route all sources to IRQ instead of FIQ */
op_star
id|IXP4XX_ICLR
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* Disable all interrupt */
op_star
id|IXP4XX_ICMR
op_assign
l_int|0x0
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_irq_chip
c_func
(paren
id|i
comma
op_amp
id|ixp4xx_irq_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|i
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|i
comma
id|IRQF_VALID
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*************************************************************************&n; * IXP4xx timer tick&n; * We use OS timer1 on the CPU for the timer tick and the timestamp &n; * counter as a source of real clock ticks to account for missed jiffies.&n; *************************************************************************/
DECL|variable|last_jiffy_time
r_static
r_int
r_volatile
id|last_jiffy_time
suffix:semicolon
DECL|macro|CLOCK_TICKS_PER_USEC
mdefine_line|#define CLOCK_TICKS_PER_USEC&t;(CLOCK_TICK_RATE / USEC_PER_SEC)
multiline_comment|/* IRQs are disabled before entering here from do_gettimeofday() */
DECL|function|ixp4xx_gettimeoffset
r_static
r_int
r_int
id|ixp4xx_gettimeoffset
c_func
(paren
r_void
)paren
(brace
id|u32
id|elapsed
suffix:semicolon
id|elapsed
op_assign
op_star
id|IXP4XX_OSTS
op_minus
id|last_jiffy_time
suffix:semicolon
r_return
id|elapsed
op_div
id|CLOCK_TICKS_PER_USEC
suffix:semicolon
)brace
DECL|function|ixp4xx_timer_interrupt
r_static
id|irqreturn_t
id|ixp4xx_timer_interrupt
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
multiline_comment|/* Clear Pending Interrupt by writing &squot;1&squot; to it */
op_star
id|IXP4XX_OSST
op_assign
id|IXP4XX_OSST_TIMER_1_PEND
suffix:semicolon
multiline_comment|/*&n;&t; * Catch up with the real idea of time&n;&t; */
r_do
(brace
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|last_jiffy_time
op_add_assign
id|LATCH
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_star
id|IXP4XX_OSTS
op_minus
id|last_jiffy_time
)paren
OG
id|LATCH
)paren
(brace
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_extern
r_int
r_int
(paren
op_star
id|gettimeoffset
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|timer_irq
r_static
r_struct
id|irqaction
id|timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP4xx Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
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
id|gettimeoffset
op_assign
id|ixp4xx_gettimeoffset
suffix:semicolon
id|timer_irq.handler
op_assign
id|ixp4xx_timer_interrupt
suffix:semicolon
multiline_comment|/* Clear Pending Interrupt by writing &squot;1&squot; to it */
op_star
id|IXP4XX_OSST
op_assign
id|IXP4XX_OSST_TIMER_1_PEND
suffix:semicolon
multiline_comment|/* Setup the Timer counter value */
op_star
id|IXP4XX_OSRT1
op_assign
(paren
id|LATCH
op_amp
op_complement
id|IXP4XX_OST_RELOAD_MASK
)paren
op_or
id|IXP4XX_OST_ENABLE
suffix:semicolon
multiline_comment|/* Reset time-stamp counter */
op_star
id|IXP4XX_OSTS
op_assign
l_int|0
suffix:semicolon
id|last_jiffy_time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Connect the interrupt handler and enable the interrupt */
id|setup_irq
c_func
(paren
id|IRQ_IXP4XX_TIMER1
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
)brace
eof
