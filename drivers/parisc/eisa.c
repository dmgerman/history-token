multiline_comment|/*&n; * eisa.c - provide support for EISA adapters in PA-RISC machines&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Copyright (c) 2001 Matthew Wilcox for Hewlett Packard&n; * Copyright (c) 2001 Daniel Engstrom &lt;5116@telia.com&gt;&n; *&n; * There are two distinct EISA adapters.  Mongoose is found in machines&n; * before the 712; then the Wax ASIC is used.  To complicate matters, the&n; * Wax ASIC also includes a PS/2 and RS-232 controller, but those are&n; * dealt with elsewhere; this file is concerned only with the EISA portions&n; * of Wax.&n; * &n; * &n; * HINT:&n; * -----&n; * To allow an ISA card to work properly in the EISA slot you need to&n; * set an edge trigger level. This may be done on the palo command line &n; * by adding the kernel parameter &quot;eisa_irq_edge=n,n2,[...]]&quot;, with &n; * n and n2 as the irq levels you want to use.&n; * &n; * Example: &quot;eisa_irq_edge=10,11&quot; allows ISA cards to operate at &n; * irq levels 10 and 11.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/parisc-device.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/eisa_bus.h&gt;
macro_line|#include &lt;asm/eisa_eeprom.h&gt;
macro_line|#if 0
mdefine_line|#define EISA_DBG(msg, arg... ) printk(KERN_DEBUG &quot;eisa: &quot; msg , ## arg )
macro_line|#else
DECL|macro|EISA_DBG
mdefine_line|#define EISA_DBG(msg, arg... )  
macro_line|#endif
DECL|macro|SNAKES_EEPROM_BASE_ADDR
mdefine_line|#define SNAKES_EEPROM_BASE_ADDR 0xF0810400
DECL|macro|MIRAGE_EEPROM_BASE_ADDR
mdefine_line|#define MIRAGE_EEPROM_BASE_ADDR 0xF00C0400
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|eisa_irq_lock
)paren
suffix:semicolon
DECL|variable|eisa_eeprom_addr
r_void
id|__iomem
op_star
id|eisa_eeprom_addr
suffix:semicolon
multiline_comment|/* We can only have one EISA adapter in the system because neither&n; * implementation can be flexed.&n; */
DECL|struct|eisa_ba
r_static
r_struct
id|eisa_ba
(brace
DECL|member|hba
r_struct
id|pci_hba_data
id|hba
suffix:semicolon
DECL|member|eeprom_addr
r_int
r_int
id|eeprom_addr
suffix:semicolon
DECL|member|root
r_struct
id|eisa_root_device
id|root
suffix:semicolon
DECL|variable|eisa_dev
)brace
id|eisa_dev
suffix:semicolon
multiline_comment|/* Port ops */
DECL|function|eisa_permute
r_static
r_inline
r_int
r_int
id|eisa_permute
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|port
op_amp
l_int|0x300
)paren
(brace
r_return
l_int|0xfc000000
op_or
(paren
(paren
id|port
op_amp
l_int|0xfc00
)paren
op_rshift
l_int|6
)paren
op_or
(paren
(paren
id|port
op_amp
l_int|0x3f8
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|port
op_amp
l_int|7
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0xfc000000
op_or
id|port
suffix:semicolon
)brace
)brace
DECL|function|eisa_in8
r_int
r_char
id|eisa_in8
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|EISA_bus
)paren
r_return
id|gsc_readb
c_func
(paren
id|eisa_permute
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
r_return
l_int|0xff
suffix:semicolon
)brace
DECL|function|eisa_in16
r_int
r_int
id|eisa_in16
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|EISA_bus
)paren
r_return
id|le16_to_cpu
c_func
(paren
id|gsc_readw
c_func
(paren
id|eisa_permute
c_func
(paren
id|port
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0xffff
suffix:semicolon
)brace
DECL|function|eisa_in32
r_int
r_int
id|eisa_in32
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|EISA_bus
)paren
r_return
id|le32_to_cpu
c_func
(paren
id|gsc_readl
c_func
(paren
id|eisa_permute
c_func
(paren
id|port
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0xffffffff
suffix:semicolon
)brace
DECL|function|eisa_out8
r_void
id|eisa_out8
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|EISA_bus
)paren
id|gsc_writeb
c_func
(paren
id|data
comma
id|eisa_permute
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|eisa_out16
r_void
id|eisa_out16
c_func
(paren
r_int
r_int
id|data
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|EISA_bus
)paren
id|gsc_writew
c_func
(paren
id|cpu_to_le16
c_func
(paren
id|data
)paren
comma
id|eisa_permute
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|function|eisa_out32
r_void
id|eisa_out32
c_func
(paren
r_int
r_int
id|data
comma
r_int
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|EISA_bus
)paren
id|gsc_writel
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|data
)paren
comma
id|eisa_permute
c_func
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PCI
multiline_comment|/* We call these directly without PCI.  See asm/io.h. */
DECL|variable|eisa_in8
id|EXPORT_SYMBOL
c_func
(paren
id|eisa_in8
)paren
suffix:semicolon
DECL|variable|eisa_in16
id|EXPORT_SYMBOL
c_func
(paren
id|eisa_in16
)paren
suffix:semicolon
DECL|variable|eisa_in32
id|EXPORT_SYMBOL
c_func
(paren
id|eisa_in32
)paren
suffix:semicolon
DECL|variable|eisa_out8
id|EXPORT_SYMBOL
c_func
(paren
id|eisa_out8
)paren
suffix:semicolon
DECL|variable|eisa_out16
id|EXPORT_SYMBOL
c_func
(paren
id|eisa_out16
)paren
suffix:semicolon
DECL|variable|eisa_out32
id|EXPORT_SYMBOL
c_func
(paren
id|eisa_out32
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Interrupt handling */
multiline_comment|/* cached interrupt mask registers */
DECL|variable|master_mask
r_static
r_int
id|master_mask
suffix:semicolon
DECL|variable|slave_mask
r_static
r_int
id|slave_mask
suffix:semicolon
multiline_comment|/* the trig level can be set with the&n; * eisa_irq_edge=n,n,n commandline parameter &n; * We should really read this from the EEPROM &n; * in the furure. &n; */
multiline_comment|/* irq 13,8,2,1,0 must be edge */
DECL|variable|eisa_irq_level
r_static
r_int
r_int
id|eisa_irq_level
suffix:semicolon
multiline_comment|/* default to edge triggered */
multiline_comment|/* called by free irq */
DECL|function|eisa_disable_irq
r_static
r_void
id|eisa_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;disable irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* just mask for now */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
(brace
id|slave_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|slave_mask
comma
l_int|0xa1
)paren
suffix:semicolon
)brace
r_else
(brace
id|master_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|master_mask
comma
l_int|0x21
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic0 mask %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0x21
)paren
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic1 mask %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0xa1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* called by request irq */
DECL|function|eisa_enable_irq
r_static
r_void
id|eisa_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;enable irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
(brace
id|slave_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|slave_mask
comma
l_int|0xa1
)paren
suffix:semicolon
)brace
r_else
(brace
id|master_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|master_mask
comma
l_int|0x21
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic0 mask %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0x21
)paren
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic1 mask %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0xa1
)paren
)paren
suffix:semicolon
)brace
DECL|function|eisa_startup_irq
r_static
r_int
r_int
id|eisa_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|eisa_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|eisa_interrupt_type
r_static
r_struct
id|hw_interrupt_type
id|eisa_interrupt_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;EISA&quot;
comma
dot
id|startup
op_assign
id|eisa_startup_irq
comma
dot
id|shutdown
op_assign
id|eisa_disable_irq
comma
dot
id|enable
op_assign
id|eisa_enable_irq
comma
dot
id|disable
op_assign
id|eisa_disable_irq
comma
dot
id|ack
op_assign
id|no_ack_irq
comma
dot
id|end
op_assign
id|no_end_irq
comma
)brace
suffix:semicolon
DECL|function|eisa_irq
r_static
id|irqreturn_t
id|eisa_irq
c_func
(paren
r_int
id|wax_irq
comma
r_void
op_star
id|intr_dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
op_assign
id|gsc_readb
c_func
(paren
l_int|0xfc01f000
)paren
suffix:semicolon
multiline_comment|/* EISA supports 16 irqs */
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* read IRR command */
id|eisa_out8
c_func
(paren
l_int|0x0a
comma
l_int|0x20
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
l_int|0x0a
comma
l_int|0xa0
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;irq IAR %02x 8259-1 irr %02x 8259-2 irr %02x&bslash;n&quot;
comma
id|irq
comma
id|eisa_in8
c_func
(paren
l_int|0x20
)paren
comma
id|eisa_in8
c_func
(paren
l_int|0xa0
)paren
)paren
suffix:semicolon
multiline_comment|/* read ISR command */
id|eisa_out8
c_func
(paren
l_int|0x0a
comma
l_int|0x20
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
l_int|0x0a
comma
l_int|0xa0
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;irq 8259-1 isr %02x imr %02x 8259-2 isr %02x imr %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0x20
)paren
comma
id|eisa_in8
c_func
(paren
l_int|0x21
)paren
comma
id|eisa_in8
c_func
(paren
l_int|0xa0
)paren
comma
id|eisa_in8
c_func
(paren
l_int|0xa1
)paren
)paren
suffix:semicolon
id|irq
op_and_assign
l_int|0xf
suffix:semicolon
multiline_comment|/* mask irq and write eoi */
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
(brace
id|slave_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|slave_mask
comma
l_int|0xa1
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
l_int|0x60
op_or
(paren
id|irq
op_amp
l_int|7
)paren
comma
l_int|0xa0
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to slave */
id|eisa_out8
c_func
(paren
l_int|0x62
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to master-IRQ2 */
)brace
r_else
(brace
id|master_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|master_mask
comma
l_int|0x21
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
l_int|0x60
op_or
id|irq
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to master */
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
id|__do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* unmask */
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
(brace
id|slave_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|slave_mask
comma
l_int|0xa1
)paren
suffix:semicolon
)brace
r_else
(brace
id|master_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|master_mask
comma
l_int|0x21
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|dummy_irq2_handler
r_static
id|irqreturn_t
id|dummy_irq2_handler
c_func
(paren
r_int
id|_
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;eisa: uhh, irq2?&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|irq2_action
r_static
r_struct
id|irqaction
id|irq2_action
op_assign
(brace
dot
id|handler
op_assign
id|dummy_irq2_handler
comma
dot
id|name
op_assign
l_string|&quot;cascade&quot;
comma
)brace
suffix:semicolon
DECL|function|init_eisa_pic
r_static
r_void
id|init_eisa_pic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
l_int|0xff
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* mask during init */
id|eisa_out8
c_func
(paren
l_int|0xff
comma
l_int|0xa1
)paren
suffix:semicolon
multiline_comment|/* mask during init */
multiline_comment|/* master pic */
id|eisa_out8
c_func
(paren
l_int|0x11
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* ICW1 */
id|eisa_out8
c_func
(paren
l_int|0x00
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* ICW2 */
id|eisa_out8
c_func
(paren
l_int|0x04
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* ICW3 */
id|eisa_out8
c_func
(paren
l_int|0x01
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* ICW4 */
id|eisa_out8
c_func
(paren
l_int|0x40
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* OCW2 */
multiline_comment|/* slave pic */
id|eisa_out8
c_func
(paren
l_int|0x11
comma
l_int|0xa0
)paren
suffix:semicolon
multiline_comment|/* ICW1 */
id|eisa_out8
c_func
(paren
l_int|0x08
comma
l_int|0xa1
)paren
suffix:semicolon
multiline_comment|/* ICW2 */
id|eisa_out8
c_func
(paren
l_int|0x02
comma
l_int|0xa1
)paren
suffix:semicolon
multiline_comment|/* ICW3 */
id|eisa_out8
c_func
(paren
l_int|0x01
comma
l_int|0xa1
)paren
suffix:semicolon
multiline_comment|/* ICW4 */
id|eisa_out8
c_func
(paren
l_int|0x40
comma
l_int|0xa0
)paren
suffix:semicolon
multiline_comment|/* OCW2 */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|slave_mask
op_assign
l_int|0xff
suffix:semicolon
id|master_mask
op_assign
l_int|0xfb
suffix:semicolon
id|eisa_out8
c_func
(paren
id|slave_mask
comma
l_int|0xa1
)paren
suffix:semicolon
multiline_comment|/* OCW1 */
id|eisa_out8
c_func
(paren
id|master_mask
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* OCW1 */
multiline_comment|/* setup trig level */
id|EISA_DBG
c_func
(paren
l_string|&quot;EISA edge/level %04x&bslash;n&quot;
comma
id|eisa_irq_level
)paren
suffix:semicolon
id|eisa_out8
c_func
(paren
id|eisa_irq_level
op_amp
l_int|0xff
comma
l_int|0x4d0
)paren
suffix:semicolon
multiline_comment|/* Set all irq&squot;s to edge  */
id|eisa_out8
c_func
(paren
(paren
id|eisa_irq_level
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x4d1
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic0 mask %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0x21
)paren
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic1 mask %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0xa1
)paren
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic0 edge/level %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0x4d0
)paren
)paren
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;pic1 edge/level %02x&bslash;n&quot;
comma
id|eisa_in8
c_func
(paren
l_int|0x4d1
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|eisa_irq_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Device initialisation */
DECL|macro|is_mongoose
mdefine_line|#define is_mongoose(dev) (dev-&gt;id.sversion == 0x00076)
DECL|function|eisa_probe
r_static
r_int
id|__devinit
id|eisa_probe
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_int
id|i
comma
id|result
suffix:semicolon
r_char
op_star
id|name
op_assign
id|is_mongoose
c_func
(paren
id|dev
)paren
ques
c_cond
l_string|&quot;Mongoose&quot;
suffix:colon
l_string|&quot;Wax&quot;
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s EISA Adapter found at 0x%08lx&bslash;n&quot;
comma
id|name
comma
id|dev-&gt;hpa
)paren
suffix:semicolon
id|eisa_dev.hba.dev
op_assign
id|dev
suffix:semicolon
id|eisa_dev.hba.iommu
op_assign
id|ccio_get_iommu
c_func
(paren
id|dev
)paren
suffix:semicolon
id|eisa_dev.hba.lmmio_space.name
op_assign
l_string|&quot;EISA&quot;
suffix:semicolon
id|eisa_dev.hba.lmmio_space.start
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xfc000000
)paren
suffix:semicolon
id|eisa_dev.hba.lmmio_space.end
op_assign
id|F_EXTEND
c_func
(paren
l_int|0xffbfffff
)paren
suffix:semicolon
id|eisa_dev.hba.lmmio_space.flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|result
op_assign
id|ccio_request_resource
c_func
(paren
id|dev
comma
op_amp
id|eisa_dev.hba.lmmio_space
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EISA: failed to claim EISA Bus address space!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|eisa_dev.hba.io_space.name
op_assign
l_string|&quot;EISA&quot;
suffix:semicolon
id|eisa_dev.hba.io_space.start
op_assign
l_int|0
suffix:semicolon
id|eisa_dev.hba.io_space.end
op_assign
l_int|0xffff
suffix:semicolon
id|eisa_dev.hba.lmmio_space.flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|result
op_assign
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|eisa_dev.hba.io_space
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EISA: failed to claim EISA Bus port space!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|pcibios_register_hba
c_func
(paren
op_amp
id|eisa_dev.hba
)paren
suffix:semicolon
id|result
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|eisa_irq
comma
id|SA_SHIRQ
comma
l_string|&quot;EISA&quot;
comma
op_amp
id|eisa_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EISA: request_irq failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Reserve IRQ2 */
id|irq_desc
(braket
l_int|2
)braket
dot
id|action
op_assign
op_amp
id|irq2_action
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|eisa_interrupt_type
suffix:semicolon
)brace
id|EISA_bus
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;num_addrs
)paren
(brace
multiline_comment|/* newer firmware hand out the eeprom address */
id|eisa_dev.eeprom_addr
op_assign
id|dev-&gt;addr
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* old firmware, need to figure out the box */
r_if
c_cond
(paren
id|is_mongoose
c_func
(paren
id|dev
)paren
)paren
(brace
id|eisa_dev.eeprom_addr
op_assign
id|SNAKES_EEPROM_BASE_ADDR
suffix:semicolon
)brace
r_else
(brace
id|eisa_dev.eeprom_addr
op_assign
id|MIRAGE_EEPROM_BASE_ADDR
suffix:semicolon
)brace
)brace
id|eisa_eeprom_addr
op_assign
id|ioremap
c_func
(paren
id|eisa_dev.eeprom_addr
comma
id|HPEE_MAX_LENGTH
)paren
suffix:semicolon
id|result
op_assign
id|eisa_enumerator
c_func
(paren
id|eisa_dev.eeprom_addr
comma
op_amp
id|eisa_dev.hba.io_space
comma
op_amp
id|eisa_dev.hba.lmmio_space
)paren
suffix:semicolon
id|init_eisa_pic
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
multiline_comment|/* FIXME : Don&squot;t enumerate the bus twice. */
id|eisa_dev.root.dev
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|dev-&gt;dev.driver_data
op_assign
op_amp
id|eisa_dev.root
suffix:semicolon
id|eisa_dev.root.bus_base_addr
op_assign
l_int|0
suffix:semicolon
id|eisa_dev.root.res
op_assign
op_amp
id|eisa_dev.hba.io_space
suffix:semicolon
id|eisa_dev.root.slots
op_assign
id|result
suffix:semicolon
id|eisa_dev.root.dma_mask
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* wild guess */
r_if
c_cond
(paren
id|eisa_root_register
(paren
op_amp
id|eisa_dev.root
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;EISA: Failed to register EISA root&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|eisa_tbl
r_static
r_struct
id|parisc_device_id
id|eisa_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_BA
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00076
)brace
comma
multiline_comment|/* Mongoose */
(brace
id|HPHW_BA
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00090
)brace
comma
multiline_comment|/* Wax EISA */
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|parisc
comma
id|eisa_tbl
)paren
suffix:semicolon
DECL|variable|eisa_driver
r_static
r_struct
id|parisc_driver
id|eisa_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;EISA Bus Adapter&quot;
comma
dot
id|id_table
op_assign
id|eisa_tbl
comma
dot
id|probe
op_assign
id|eisa_probe
comma
)brace
suffix:semicolon
DECL|function|eisa_init
r_void
id|__init
id|eisa_init
c_func
(paren
r_void
)paren
(brace
id|register_parisc_driver
c_func
(paren
op_amp
id|eisa_driver
)paren
suffix:semicolon
)brace
DECL|variable|eisa_irq_configured
r_static
r_int
r_int
id|eisa_irq_configured
suffix:semicolon
DECL|function|eisa_make_irq_level
r_void
id|eisa_make_irq_level
c_func
(paren
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
id|eisa_irq_configured
op_amp
(paren
l_int|1
op_lshift
id|num
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IRQ %d polarity configured twice (last to level)&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
)brace
id|eisa_irq_level
op_or_assign
(paren
l_int|1
op_lshift
id|num
)paren
suffix:semicolon
multiline_comment|/* set the corresponding bit */
id|eisa_irq_configured
op_or_assign
(paren
l_int|1
op_lshift
id|num
)paren
suffix:semicolon
multiline_comment|/* set the corresponding bit */
)brace
DECL|function|eisa_make_irq_edge
r_void
id|eisa_make_irq_edge
c_func
(paren
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
id|eisa_irq_configured
op_amp
(paren
l_int|1
op_lshift
id|num
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IRQ %d polarity configured twice (last to edge)&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
)brace
id|eisa_irq_level
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|num
)paren
suffix:semicolon
multiline_comment|/* clear the corresponding bit */
id|eisa_irq_configured
op_or_assign
(paren
l_int|1
op_lshift
id|num
)paren
suffix:semicolon
multiline_comment|/* set the corresponding bit */
)brace
DECL|function|eisa_irq_setup
r_static
r_int
id|__init
id|eisa_irq_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|cur
op_assign
id|str
suffix:semicolon
r_int
id|val
suffix:semicolon
id|EISA_DBG
c_func
(paren
l_string|&quot;IRQ setup&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_ne
l_int|NULL
)paren
(brace
r_char
op_star
id|pe
suffix:semicolon
id|val
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|cur
comma
op_amp
id|pe
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
l_int|15
op_logical_or
id|val
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;eisa: EISA irq value are 0-15&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
op_eq
l_int|2
)paren
(brace
id|val
op_assign
l_int|9
suffix:semicolon
)brace
id|eisa_make_irq_edge
c_func
(paren
id|val
)paren
suffix:semicolon
multiline_comment|/* clear the corresponding bit */
id|EISA_DBG
c_func
(paren
l_string|&quot;setting IRQ %d to edge-triggered mode&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;,&squot;
)paren
)paren
)paren
(brace
id|cur
op_increment
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;eisa_irq_edge=&quot;
comma
id|eisa_irq_setup
)paren
suffix:semicolon
eof
