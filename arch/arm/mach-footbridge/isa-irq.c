multiline_comment|/*&n; *  linux/arch/arm/mach-footbridge/irq.c&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   22-Aug-1998 RMK&t;Restructured IRQ routines&n; *   03-Sep-1998 PJB&t;Merged CATS support&n; *   20-Jan-1998 RMK&t;Started merge of EBSA286, CATS and NetWinder&n; *   26-Jan-1999 PJB&t;Don&squot;t use IACK on CATS&n; *   16-Mar-1999 RMK&t;Added autodetect of ISA PICs&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|function|isa_mask_pic_lo_irq
r_static
r_void
id|isa_mask_pic_lo_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PIC_MASK_LO
)paren
op_or
id|mask
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
)brace
DECL|function|isa_ack_pic_lo_irq
r_static
r_void
id|isa_ack_pic_lo_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PIC_MASK_LO
)paren
op_or
id|mask
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x20
comma
id|PIC_LO
)paren
suffix:semicolon
)brace
DECL|function|isa_unmask_pic_lo_irq
r_static
r_void
id|isa_unmask_pic_lo_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PIC_MASK_LO
)paren
op_amp
op_complement
id|mask
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
)brace
DECL|variable|isa_lo_chip
r_static
r_struct
id|irqchip
id|isa_lo_chip
op_assign
(brace
id|ack
suffix:colon
id|isa_ack_pic_lo_irq
comma
id|mask
suffix:colon
id|isa_mask_pic_lo_irq
comma
id|unmask
suffix:colon
id|isa_unmask_pic_lo_irq
comma
)brace
suffix:semicolon
DECL|function|isa_mask_pic_hi_irq
r_static
r_void
id|isa_mask_pic_hi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PIC_MASK_HI
)paren
op_or
id|mask
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
)brace
DECL|function|isa_ack_pic_hi_irq
r_static
r_void
id|isa_ack_pic_hi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PIC_MASK_HI
)paren
op_or
id|mask
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x62
comma
id|PIC_LO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x20
comma
id|PIC_HI
)paren
suffix:semicolon
)brace
DECL|function|isa_unmask_pic_hi_irq
r_static
r_void
id|isa_unmask_pic_hi_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|PIC_MASK_HI
)paren
op_amp
op_complement
id|mask
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
)brace
DECL|variable|isa_hi_chip
r_static
r_struct
id|irqchip
id|isa_hi_chip
op_assign
(brace
id|ack
suffix:colon
id|isa_ack_pic_hi_irq
comma
id|mask
suffix:colon
id|isa_mask_pic_hi_irq
comma
id|unmask
suffix:colon
id|isa_unmask_pic_hi_irq
comma
)brace
suffix:semicolon
DECL|function|no_action
r_static
r_void
id|no_action
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
)brace
r_static
r_void
DECL|function|isa_irq_handler
id|isa_irq_handler
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
r_int
id|isa_irq
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|PCIIACK_BASE
suffix:semicolon
r_if
c_cond
(paren
id|isa_irq
OL
id|_ISA_IRQ
c_func
(paren
l_int|0
)paren
op_logical_or
id|isa_irq
op_ge
id|_ISA_IRQ
c_func
(paren
l_int|16
)paren
)paren
(brace
id|do_bad_IRQ
c_func
(paren
id|isa_irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|desc
op_assign
id|irq_desc
op_plus
id|isa_irq
suffix:semicolon
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|isa_irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|variable|irq_cascade
r_static
r_struct
id|irqaction
id|irq_cascade
op_assign
(brace
id|handler
suffix:colon
id|no_action
comma
id|name
suffix:colon
l_string|&quot;cascade&quot;
comma
)brace
suffix:semicolon
DECL|variable|pic1_resource
r_static
r_struct
id|resource
id|pic1_resource
op_assign
(brace
l_string|&quot;pic1&quot;
comma
l_int|0x20
comma
l_int|0x3f
)brace
suffix:semicolon
DECL|variable|pic2_resource
r_static
r_struct
id|resource
id|pic2_resource
op_assign
(brace
l_string|&quot;pic2&quot;
comma
l_int|0xa0
comma
l_int|0xbf
)brace
suffix:semicolon
DECL|function|isa_init_irq
r_void
id|__init
id|isa_init_irq
c_func
(paren
r_int
r_int
id|host_irq
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Setup, and then probe for an ISA PIC&n;&t; * If the PIC is not there, then we&n;&t; * ignore the PIC.&n;&t; */
id|outb
c_func
(paren
l_int|0x11
comma
id|PIC_LO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|_ISA_IRQ
c_func
(paren
l_int|0
)paren
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
multiline_comment|/* IRQ number&t;&t;*/
id|outb
c_func
(paren
l_int|0x04
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
multiline_comment|/* Slave on Ch2&t;&t;*/
id|outb
c_func
(paren
l_int|0x01
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
multiline_comment|/* x86&t;&t;&t;*/
id|outb
c_func
(paren
l_int|0xf5
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
multiline_comment|/* pattern: 11110101&t;*/
id|outb
c_func
(paren
l_int|0x11
comma
id|PIC_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|_ISA_IRQ
c_func
(paren
l_int|8
)paren
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
multiline_comment|/* IRQ number&t;&t;*/
id|outb
c_func
(paren
l_int|0x02
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
multiline_comment|/* Slave on Ch1&t;&t;*/
id|outb
c_func
(paren
l_int|0x01
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
multiline_comment|/* x86&t;&t;&t;*/
id|outb
c_func
(paren
l_int|0xfa
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
multiline_comment|/* pattern: 11111010&t;*/
id|outb
c_func
(paren
l_int|0x0b
comma
id|PIC_LO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0b
comma
id|PIC_HI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|PIC_MASK_LO
)paren
op_eq
l_int|0xf5
op_logical_and
id|inb
c_func
(paren
id|PIC_MASK_HI
)paren
op_eq
l_int|0xfa
)paren
(brace
id|outb
c_func
(paren
l_int|0xff
comma
id|PIC_MASK_LO
)paren
suffix:semicolon
multiline_comment|/* mask all IRQs&t;*/
id|outb
c_func
(paren
l_int|0xff
comma
id|PIC_MASK_HI
)paren
suffix:semicolon
multiline_comment|/* mask all IRQs&t;*/
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IRQ: ISA PIC not found&bslash;n&quot;
)paren
suffix:semicolon
id|host_irq
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host_irq
op_ne
(paren
r_int
r_int
)paren
op_minus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|irq
op_assign
id|_ISA_IRQ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|irq
OL
id|_ISA_IRQ
c_func
(paren
l_int|8
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
id|isa_lo_chip
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
r_for
c_loop
(paren
id|irq
op_assign
id|_ISA_IRQ
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|irq
OL
id|_ISA_IRQ
c_func
(paren
l_int|16
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
id|isa_hi_chip
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
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic1_resource
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic2_resource
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|IRQ_ISA_CASCADE
comma
op_amp
id|irq_cascade
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|host_irq
comma
id|isa_irq_handler
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * On the NetWinder, don&squot;t automatically&n;&t;&t; * enable ISA IRQ11 when it is requested.&n;&t;&t; * There appears to be a missing pull-up&n;&t;&t; * resistor on this line.&n;&t;&t; */
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|set_irq_flags
c_func
(paren
id|_ISA_IRQ
c_func
(paren
l_int|11
)paren
comma
id|IRQF_VALID
op_or
id|IRQF_PROBE
op_or
id|IRQF_NOAUTOEN
)paren
suffix:semicolon
)brace
)brace
eof
