multiline_comment|/*&n; * arch/arm/mach-ixp2000/common.c&n; *&n; * Common routines used by all IXP2400/2800 based platforms.&n; *&n; * Author: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright 2004 (C) MontaVista Software, Inc. &n; *&n; * Based on work Copyright (C) 2002-2003 Intel Corporation&n; * &n; * This file is licensed under the terms of the GNU General Public&n; * License version 2. This program is licensed &quot;as is&quot; without any &n; * warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|ixp2000_slowport_lock
)paren
suffix:semicolon
DECL|variable|ixp2000_slowport_irq_flags
r_static
r_int
r_int
id|ixp2000_slowport_irq_flags
suffix:semicolon
multiline_comment|/*************************************************************************&n; * Slowport access routines&n; *************************************************************************/
DECL|function|ixp2000_acquire_slowport
r_void
id|ixp2000_acquire_slowport
c_func
(paren
r_struct
id|slowport_cfg
op_star
id|new_cfg
comma
r_struct
id|slowport_cfg
op_star
id|old_cfg
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ixp2000_slowport_lock
comma
id|ixp2000_slowport_irq_flags
)paren
suffix:semicolon
id|old_cfg-&gt;CCR
op_assign
op_star
id|IXP2000_SLOWPORT_CCR
suffix:semicolon
id|old_cfg-&gt;WTC
op_assign
op_star
id|IXP2000_SLOWPORT_WTC2
suffix:semicolon
id|old_cfg-&gt;RTC
op_assign
op_star
id|IXP2000_SLOWPORT_RTC2
suffix:semicolon
id|old_cfg-&gt;PCR
op_assign
op_star
id|IXP2000_SLOWPORT_PCR
suffix:semicolon
id|old_cfg-&gt;ADC
op_assign
op_star
id|IXP2000_SLOWPORT_ADC
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_CCR
comma
id|new_cfg-&gt;CCR
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_WTC2
comma
id|new_cfg-&gt;WTC
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_RTC2
comma
id|new_cfg-&gt;RTC
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_PCR
comma
id|new_cfg-&gt;PCR
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_ADC
comma
id|new_cfg-&gt;ADC
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_release_slowport
r_void
id|ixp2000_release_slowport
c_func
(paren
r_struct
id|slowport_cfg
op_star
id|old_cfg
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_CCR
comma
id|old_cfg-&gt;CCR
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_WTC2
comma
id|old_cfg-&gt;WTC
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_RTC2
comma
id|old_cfg-&gt;RTC
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_PCR
comma
id|old_cfg-&gt;PCR
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_ADC
comma
id|old_cfg-&gt;ADC
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ixp2000_slowport_lock
comma
id|ixp2000_slowport_irq_flags
)paren
suffix:semicolon
)brace
multiline_comment|/*************************************************************************&n; * Chip specific mappings shared by all IXP2000 systems&n; *************************************************************************/
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ixp2000_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
r_virtual
op_assign
id|IXP2000_CAP_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_CAP_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_CAP_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
dot
r_virtual
op_assign
id|IXP2000_INTCTL_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_INTCTL_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_INTCTL_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
dot
r_virtual
op_assign
id|IXP2000_PCI_CREG_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_PCI_CREG_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_PCI_CREG_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
dot
r_virtual
op_assign
id|IXP2000_PCI_CSR_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_PCI_CSR_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_PCI_CSR_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
dot
r_virtual
op_assign
id|IXP2000_PCI_IO_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_PCI_IO_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_PCI_IO_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
dot
r_virtual
op_assign
id|IXP2000_PCI_CFG0_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_PCI_CFG0_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_PCI_CFG0_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
comma
(brace
dot
r_virtual
op_assign
id|IXP2000_PCI_CFG1_VIRT_BASE
comma
dot
id|physical
op_assign
id|IXP2000_PCI_CFG1_PHYS_BASE
comma
dot
id|length
op_assign
id|IXP2000_PCI_CFG1_SIZE
comma
dot
id|type
op_assign
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|variable|ixp2000_serial_port
r_static
r_struct
id|uart_port
id|ixp2000_serial_port
op_assign
(brace
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
(paren
id|IXP2000_UART_VIRT_BASE
op_plus
l_int|3
)paren
comma
dot
id|mapbase
op_assign
id|IXP2000_UART_PHYS_BASE
op_plus
l_int|3
comma
dot
id|irq
op_assign
id|IRQ_IXP2000_UART
comma
dot
id|flags
op_assign
id|UPF_SKIP_TEST
comma
dot
id|iotype
op_assign
id|UPIO_MEM
comma
dot
id|regshift
op_assign
l_int|2
comma
dot
id|uartclk
op_assign
l_int|50000000
comma
dot
id|line
op_assign
l_int|0
comma
dot
id|type
op_assign
id|PORT_XSCALE
comma
dot
id|fifosize
op_assign
l_int|16
)brace
suffix:semicolon
DECL|function|ixp2000_map_io
r_void
id|__init
id|ixp2000_map_io
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_int
id|processor_id
suffix:semicolon
multiline_comment|/*&n;&t; * On IXP2400 CPUs we need to use MT_IXP2000_DEVICE for&n;&t; * tweaking the PMDs so XCB=101. On IXP2800s we use the normal&n;&t; * PMD flags.&n;&t; */
r_if
c_cond
(paren
(paren
id|processor_id
op_amp
l_int|0xfffffff0
)paren
op_eq
l_int|0x69054190
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enabling IXP2400 erratum #66 workaround&bslash;n&quot;
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
id|ARRAY_SIZE
c_func
(paren
id|ixp2000_io_desc
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ixp2000_io_desc
(braket
id|i
)braket
dot
id|type
op_assign
id|MT_IXP2000_DEVICE
suffix:semicolon
)brace
)brace
id|iotable_init
c_func
(paren
id|ixp2000_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|ixp2000_io_desc
)paren
)paren
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|ixp2000_serial_port
)paren
suffix:semicolon
multiline_comment|/* Set slowport to 8-bit mode.  */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_SLOWPORT_FRM
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*************************************************************************&n; * Timer-tick functions for IXP2000&n; *************************************************************************/
DECL|variable|ticks_per_jiffy
r_static
r_int
id|ticks_per_jiffy
suffix:semicolon
DECL|variable|ticks_per_usec
r_static
r_int
id|ticks_per_usec
suffix:semicolon
DECL|variable|next_jiffy_time
r_static
r_int
id|next_jiffy_time
suffix:semicolon
DECL|function|ixp2000_gettimeoffset
r_int
r_int
id|ixp2000_gettimeoffset
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
id|offset
op_assign
id|next_jiffy_time
op_minus
op_star
id|IXP2000_T4_CSR
suffix:semicolon
r_return
id|offset
op_div
id|ticks_per_usec
suffix:semicolon
)brace
DECL|function|ixp2000_timer_interrupt
r_static
r_int
id|ixp2000_timer_interrupt
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
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
multiline_comment|/* clear timer 1 */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T1_CLR
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|next_jiffy_time
op_minus
op_star
id|IXP2000_T4_CSR
)paren
OG
id|ticks_per_jiffy
)paren
(brace
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
id|next_jiffy_time
op_sub_assign
id|ticks_per_jiffy
suffix:semicolon
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
DECL|variable|ixp2000_timer_irq
r_static
r_struct
id|irqaction
id|ixp2000_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IXP2000 Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|ixp2000_timer_interrupt
)brace
suffix:semicolon
DECL|function|ixp2000_init_time
r_void
id|__init
id|ixp2000_init_time
c_func
(paren
r_int
r_int
id|tick_rate
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T1_CLR
comma
l_int|0
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T4_CLR
comma
l_int|0
)paren
suffix:semicolon
id|ticks_per_jiffy
op_assign
(paren
id|tick_rate
op_plus
id|HZ
op_div
l_int|2
)paren
op_div
id|HZ
suffix:semicolon
id|ticks_per_usec
op_assign
id|tick_rate
op_div
l_int|1000000
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T1_CLD
comma
id|ticks_per_jiffy
op_minus
l_int|1
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T1_CTL
comma
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We use T4 as a monotonic counter to track missed jiffies&n;&t; */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T4_CLD
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_T4_CTL
comma
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|next_jiffy_time
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* register for interrupt */
id|setup_irq
c_func
(paren
id|IRQ_IXP2000_TIMER1
comma
op_amp
id|ixp2000_timer_irq
)paren
suffix:semicolon
)brace
multiline_comment|/*************************************************************************&n; * GPIO helpers&n; *************************************************************************/
DECL|variable|GPIO_IRQ_rising_edge
r_static
r_int
r_int
id|GPIO_IRQ_rising_edge
suffix:semicolon
DECL|variable|GPIO_IRQ_falling_edge
r_static
r_int
r_int
id|GPIO_IRQ_falling_edge
suffix:semicolon
DECL|variable|GPIO_IRQ_level_low
r_static
r_int
r_int
id|GPIO_IRQ_level_low
suffix:semicolon
DECL|variable|GPIO_IRQ_level_high
r_static
r_int
r_int
id|GPIO_IRQ_level_high
suffix:semicolon
DECL|function|gpio_line_config
r_void
id|gpio_line_config
c_func
(paren
r_int
id|line
comma
r_int
id|style
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|style
op_eq
id|GPIO_OUT
)paren
(brace
multiline_comment|/* if it&squot;s an output, it ain&squot;t an interrupt anymore */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_PDSR
comma
(paren
l_int|1
op_lshift
id|line
)paren
)paren
suffix:semicolon
id|GPIO_IRQ_falling_edge
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
id|GPIO_IRQ_rising_edge
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
id|GPIO_IRQ_level_low
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
id|GPIO_IRQ_level_high
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|line
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_FEDR
comma
id|GPIO_IRQ_falling_edge
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_REDR
comma
id|GPIO_IRQ_rising_edge
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_LSHR
comma
id|GPIO_IRQ_level_high
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_LSLR
comma
id|GPIO_IRQ_level_low
)paren
suffix:semicolon
id|irq_desc
(braket
id|line
op_plus
id|IRQ_IXP2000_GPIO0
)braket
dot
id|valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|style
op_eq
id|GPIO_IN
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_PDCR
comma
(paren
l_int|1
op_lshift
id|line
)paren
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*************************************************************************&n; * IRQ handling IXP2000&n; *************************************************************************/
DECL|function|ixp2000_GPIO_irq_handler
r_static
r_void
id|ixp2000_GPIO_irq_handler
c_func
(paren
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|status
op_assign
op_star
id|IXP2000_GPIO_INST
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
op_plus
id|IRQ_IXP2000_GPIO0
suffix:semicolon
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|i
op_plus
id|IRQ_IXP2000_GPIO0
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|ixp2000_GPIO_irq_mask_ack
r_static
r_void
id|ixp2000_GPIO_irq_mask_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_INCR
comma
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IRQ_IXP2000_GPIO0
)paren
)paren
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_INST
comma
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IRQ_IXP2000_GPIO0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_GPIO_irq_mask
r_static
r_void
id|ixp2000_GPIO_irq_mask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_INCR
comma
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IRQ_IXP2000_GPIO0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_GPIO_irq_unmask
r_static
r_void
id|ixp2000_GPIO_irq_unmask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_INSR
comma
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|IRQ_IXP2000_GPIO0
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ixp2000_GPIO_irq_chip
r_static
r_struct
id|irqchip
id|ixp2000_GPIO_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|ixp2000_GPIO_irq_mask_ack
comma
dot
id|mask
op_assign
id|ixp2000_GPIO_irq_mask
comma
dot
id|unmask
op_assign
id|ixp2000_GPIO_irq_unmask
)brace
suffix:semicolon
DECL|function|ixp2000_pci_irq_mask
r_static
r_void
id|ixp2000_pci_irq_mask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|temp
op_assign
op_star
id|IXP2000_PCI_XSCALE_INT_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|IRQ_IXP2000_PCIA
)paren
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_PCI_XSCALE_INT_ENABLE
comma
(paren
id|temp
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|26
)paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|irq
op_eq
id|IRQ_IXP2000_PCIB
)paren
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_PCI_XSCALE_INT_ENABLE
comma
(paren
id|temp
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_pci_irq_unmask
r_static
r_void
id|ixp2000_pci_irq_unmask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|temp
op_assign
op_star
id|IXP2000_PCI_XSCALE_INT_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|IRQ_IXP2000_PCIA
)paren
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_PCI_XSCALE_INT_ENABLE
comma
(paren
id|temp
op_or
(paren
l_int|1
op_lshift
l_int|26
)paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|irq
op_eq
id|IRQ_IXP2000_PCIB
)paren
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_PCI_XSCALE_INT_ENABLE
comma
(paren
id|temp
op_or
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ixp2000_pci_irq_chip
r_static
r_struct
id|irqchip
id|ixp2000_pci_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|ixp2000_pci_irq_mask
comma
dot
id|mask
op_assign
id|ixp2000_pci_irq_mask
comma
dot
id|unmask
op_assign
id|ixp2000_pci_irq_unmask
)brace
suffix:semicolon
DECL|function|ixp2000_irq_mask
r_static
r_void
id|ixp2000_irq_mask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_IRQ_ENABLE_CLR
comma
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
DECL|function|ixp2000_irq_unmask
r_static
r_void
id|ixp2000_irq_unmask
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_IRQ_ENABLE_SET
comma
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ixp2000_irq_chip
r_static
r_struct
id|irqchip
id|ixp2000_irq_chip
op_assign
(brace
dot
id|ack
op_assign
id|ixp2000_irq_mask
comma
dot
id|mask
op_assign
id|ixp2000_irq_mask
comma
dot
id|unmask
op_assign
id|ixp2000_irq_unmask
)brace
suffix:semicolon
DECL|function|ixp2000_init_irq
r_void
id|__init
id|ixp2000_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Mask all sources&n;&t; */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_IRQ_ENABLE_CLR
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_FIQ_ENABLE_CLR
comma
l_int|0xffffffff
)paren
suffix:semicolon
multiline_comment|/* clear all GPIO edge/level detects */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_REDR
comma
l_int|0
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_FEDR
comma
l_int|0
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_LSHR
comma
l_int|0
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_LSLR
comma
l_int|0
)paren
suffix:semicolon
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_GPIO_INCR
comma
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* clear PCI interrupt sources */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_PCI_XSCALE_INT_ENABLE
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Certain bits in the IRQ status register of the &n;&t; * IXP2000 are reserved. Instead of trying to map&n;&t; * things non 1:1 from bit position to IRQ number,&n;&t; * we mark the reserved IRQs as invalid. This makes&n;&t; * our mask/unmask code much simpler.&n;&t; */
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_IXP2000_SOFT_INT
suffix:semicolon
id|irq
op_le
id|IRQ_IXP2000_THDB3
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|1
op_lshift
id|irq
)paren
op_amp
id|IXP2000_VALID_IRQ_MASK
)paren
(brace
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|ixp2000_irq_chip
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
)paren
suffix:semicolon
)brace
r_else
id|set_irq_flags
c_func
(paren
id|irq
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * GPIO IRQs are invalid until someone sets the interrupt mode&n;&t; * by calling gpio_line_set();&n;&t; */
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_IXP2000_GPIO0
suffix:semicolon
id|irq
op_le
id|IRQ_IXP2000_GPIO7
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
id|ixp2000_GPIO_irq_chip
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
l_int|0
)paren
suffix:semicolon
)brace
id|set_irq_chained_handler
c_func
(paren
id|IRQ_IXP2000_GPIO
comma
id|ixp2000_GPIO_irq_handler
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable PCI irqs.  The actual PCI[AB] decoding is done in&n;&t; * entry-macro.S, so we don&squot;t need a chained handler for the&n;&t; * PCI interrupt source.&n;&t; */
id|ixp2000_reg_write
c_func
(paren
id|IXP2000_IRQ_ENABLE_SET
comma
(paren
l_int|1
op_lshift
id|IRQ_IXP2000_PCI
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_IXP2000_PCIA
suffix:semicolon
id|irq
op_le
id|IRQ_IXP2000_PCIB
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
id|ixp2000_pci_irq_chip
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
)paren
suffix:semicolon
)brace
)brace
eof
