multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/sa1111.c&n; *&n; * SA1111 support&n; *&n; * Original code by John Dorsey&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This file contains all generic SA1111 support.&n; *&n; * All initialization functions provided here are intended to be called&n; * from machine specific code with proper arguments when required.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware/sa1111.h&gt;
macro_line|#include &quot;sa1111.h&quot;
DECL|variable|sa1111
r_struct
id|sa1111_device
op_star
id|sa1111
suffix:semicolon
DECL|variable|sa1111
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111
)paren
suffix:semicolon
multiline_comment|/*&n; * SA1111 interrupt support.  Since clearing an IRQ while there are&n; * active IRQs causes the interrupt output to pulse, the upper levels&n; * will call us again if there are more interrupts to process.&n; */
r_static
r_void
DECL|function|sa1111_irq_handler
id|sa1111_irq_handler
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
id|stat0
comma
id|stat1
comma
id|i
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
id|stat0
op_assign
id|INTSTATCLR0
suffix:semicolon
id|stat1
op_assign
id|INTSTATCLR1
suffix:semicolon
r_if
c_cond
(paren
id|stat0
op_eq
l_int|0
op_logical_and
id|stat1
op_eq
l_int|0
)paren
(brace
id|do_bad_IRQ
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|IRQ_SA1111_START
suffix:semicolon
id|stat0
suffix:semicolon
id|i
op_increment
comma
id|stat0
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|stat0
op_amp
l_int|1
)paren
id|do_edge_IRQ
c_func
(paren
id|i
comma
id|irq_desc
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IRQ_SA1111_START
op_plus
l_int|32
suffix:semicolon
id|stat1
suffix:semicolon
id|i
op_increment
comma
id|stat1
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|stat1
op_amp
l_int|1
)paren
id|do_edge_IRQ
c_func
(paren
id|i
comma
id|irq_desc
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* For level-based interrupts */
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|macro|SA1111_IRQMASK_LO
mdefine_line|#define SA1111_IRQMASK_LO(x)&t;(1 &lt;&lt; (x - IRQ_SA1111_START))
DECL|macro|SA1111_IRQMASK_HI
mdefine_line|#define SA1111_IRQMASK_HI(x)&t;(1 &lt;&lt; (x - IRQ_SA1111_START - 32))
DECL|function|sa1111_ack_lowirq
r_static
r_void
id|sa1111_ack_lowirq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|INTSTATCLR0
op_assign
id|SA1111_IRQMASK_LO
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1111_mask_lowirq
r_static
r_void
id|sa1111_mask_lowirq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|INTEN0
op_and_assign
op_complement
id|SA1111_IRQMASK_LO
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1111_unmask_lowirq
r_static
r_void
id|sa1111_unmask_lowirq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|INTEN0
op_or_assign
id|SA1111_IRQMASK_LO
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Attempt to re-trigger the interrupt.  The SA1111 contains a register&n; * (INTSET) which claims to do this.  However, in practice no amount of&n; * manipulation of INTEN and INTSET guarantees that the interrupt will&n; * be triggered.  In fact, its very difficult, if not impossible to get&n; * INTSET to re-trigger the interrupt.&n; */
DECL|function|sa1111_rerun_lowirq
r_static
r_void
id|sa1111_rerun_lowirq
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
id|SA1111_IRQMASK_LO
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|i
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INTPOL0
op_xor_assign
id|mask
suffix:semicolon
id|INTPOL0
op_xor_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|INTSTATCLR1
op_amp
id|mask
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|8
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Danger Will Robinson: failed to &quot;
l_string|&quot;re-trigger IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1111_type_lowirq
r_static
r_int
id|sa1111_type_lowirq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|flags
)paren
(brace
r_int
r_int
id|mask
op_assign
id|SA1111_IRQMASK_LO
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|flags
op_amp
id|__IRQT_RISEDGE
)paren
op_xor
op_logical_neg
(paren
id|flags
op_amp
id|__IRQT_FALEDGE
)paren
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IRQ%d: %s edge&bslash;n&quot;
comma
id|irq
comma
id|flags
op_amp
id|__IRQT_RISEDGE
ques
c_cond
l_string|&quot;rising&quot;
suffix:colon
l_string|&quot;falling&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|__IRQT_RISEDGE
)paren
id|INTPOL0
op_and_assign
op_complement
id|mask
suffix:semicolon
r_else
id|INTPOL0
op_or_assign
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1111_low_chip
r_static
r_struct
id|irqchip
id|sa1111_low_chip
op_assign
(brace
id|ack
suffix:colon
id|sa1111_ack_lowirq
comma
id|mask
suffix:colon
id|sa1111_mask_lowirq
comma
id|unmask
suffix:colon
id|sa1111_unmask_lowirq
comma
id|rerun
suffix:colon
id|sa1111_rerun_lowirq
comma
id|type
suffix:colon
id|sa1111_type_lowirq
comma
)brace
suffix:semicolon
DECL|function|sa1111_ack_highirq
r_static
r_void
id|sa1111_ack_highirq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|INTSTATCLR1
op_assign
id|SA1111_IRQMASK_HI
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1111_mask_highirq
r_static
r_void
id|sa1111_mask_highirq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|INTEN1
op_and_assign
op_complement
id|SA1111_IRQMASK_HI
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1111_unmask_highirq
r_static
r_void
id|sa1111_unmask_highirq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|INTEN1
op_or_assign
id|SA1111_IRQMASK_HI
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Attempt to re-trigger the interrupt.  The SA1111 contains a register&n; * (INTSET) which claims to do this.  However, in practice no amount of&n; * manipulation of INTEN and INTSET guarantees that the interrupt will&n; * be triggered.  In fact, its very difficult, if not impossible to get&n; * INTSET to re-trigger the interrupt.&n; */
DECL|function|sa1111_rerun_highirq
r_static
r_void
id|sa1111_rerun_highirq
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
id|SA1111_IRQMASK_HI
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|i
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|INTPOL1
op_xor_assign
id|mask
suffix:semicolon
id|INTPOL1
op_xor_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|INTSTATCLR1
op_amp
id|mask
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|8
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Danger Will Robinson: failed to &quot;
l_string|&quot;re-trigger IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|sa1111_type_highirq
r_static
r_int
id|sa1111_type_highirq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|flags
)paren
(brace
r_int
r_int
id|mask
op_assign
id|SA1111_IRQMASK_HI
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|flags
op_amp
id|__IRQT_RISEDGE
)paren
op_xor
op_logical_neg
(paren
id|flags
op_amp
id|__IRQT_FALEDGE
)paren
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IRQ%d: %s edge&bslash;n&quot;
comma
id|irq
comma
id|flags
op_amp
id|__IRQT_RISEDGE
ques
c_cond
l_string|&quot;rising&quot;
suffix:colon
l_string|&quot;falling&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|__IRQT_RISEDGE
)paren
id|INTPOL1
op_and_assign
op_complement
id|mask
suffix:semicolon
r_else
id|INTPOL1
op_or_assign
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1111_high_chip
r_static
r_struct
id|irqchip
id|sa1111_high_chip
op_assign
(brace
id|ack
suffix:colon
id|sa1111_ack_highirq
comma
id|mask
suffix:colon
id|sa1111_mask_highirq
comma
id|unmask
suffix:colon
id|sa1111_unmask_highirq
comma
id|rerun
suffix:colon
id|sa1111_rerun_highirq
comma
id|type
suffix:colon
id|sa1111_type_highirq
comma
)brace
suffix:semicolon
DECL|function|sa1111_init_irq
r_static
r_void
id|__init
id|sa1111_init_irq
c_func
(paren
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
id|request_mem_region
c_func
(paren
id|_INTTEST0
comma
l_int|512
comma
l_string|&quot;irqs&quot;
)paren
suffix:semicolon
multiline_comment|/* disable all IRQs */
id|INTEN0
op_assign
l_int|0
suffix:semicolon
id|INTEN1
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * detect on rising edge.  Note: Feb 2001 Errata for SA1111&n;&t; * specifies that S0ReadyInt and S1ReadyInt should be &squot;1&squot;.&n;&t; */
id|INTPOL0
op_assign
l_int|0
suffix:semicolon
id|INTPOL1
op_assign
id|SA1111_IRQMASK_HI
c_func
(paren
id|S0_READY_NINT
)paren
op_or
id|SA1111_IRQMASK_HI
c_func
(paren
id|S1_READY_NINT
)paren
suffix:semicolon
multiline_comment|/* clear all IRQs */
id|INTSTATCLR0
op_assign
op_complement
l_int|0
suffix:semicolon
id|INTSTATCLR1
op_assign
op_complement
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|IRQ_GPAIN0
suffix:semicolon
id|irq
op_le
id|SSPROR
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
id|sa1111_low_chip
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
id|AUDXMTDMADONEA
suffix:semicolon
id|irq
op_le
id|S1_BVD1_STSCHG
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
id|sa1111_high_chip
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
op_or
id|IRQF_PROBE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Register SA1111 interrupt&n;&t; */
id|set_irq_type
c_func
(paren
id|irq_nr
comma
id|IRQT_RISING
)paren
suffix:semicolon
id|set_irq_chained_handler
c_func
(paren
id|irq_nr
comma
id|sa1111_irq_handler
)paren
suffix:semicolon
)brace
DECL|function|sa1111_suspend
r_static
r_int
id|sa1111_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1111_resume
r_static
r_int
id|sa1111_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1111_device_driver
r_static
r_struct
id|device_driver
id|sa1111_device_driver
op_assign
(brace
id|suspend
suffix:colon
id|sa1111_suspend
comma
id|resume
suffix:colon
id|sa1111_resume
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;sa1111_probe - probe for a single SA1111 chip.&n; *&t;@phys_addr: physical address of device.&n; *&n; *&t;Probe for a SA1111 chip.  This must be called&n; *&t;before any other SA1111-specific code.&n; *&n; *&t;Returns:&n; *&t;%-ENODEV&t;device not found.&n; *&t;%-EBUSY&t;&t;physical address already marked in-use.&n; *&t;%0&t;&t;successful.&n; */
r_static
r_int
id|__init
DECL|function|sa1111_probe
id|sa1111_probe
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
r_int
r_int
id|phys_addr
)paren
(brace
r_struct
id|sa1111_device
op_star
id|sa
suffix:semicolon
r_int
r_int
id|id
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|sa
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sa1111_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sa
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|sa
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sa1111_device
)paren
)paren
suffix:semicolon
id|sa-&gt;resource.name
op_assign
l_string|&quot;SA1111&quot;
suffix:semicolon
id|sa-&gt;resource.start
op_assign
id|phys_addr
suffix:semicolon
id|sa-&gt;resource.end
op_assign
id|phys_addr
op_plus
l_int|0x2000
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|sa-&gt;resource
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* eventually ioremap... */
id|sa-&gt;base
op_assign
(paren
r_void
op_star
)paren
l_int|0xf4000000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sa-&gt;base
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Probe for the chip.  Only touch the SBI registers.&n;&t; */
id|id
op_assign
id|readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_SKID
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id
op_amp
id|SKID_ID_MASK
)paren
op_ne
id|SKID_SA1111_ID
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;SA1111 not detected: ID = %08lx&bslash;n&quot;
comma
id|id
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|unmap
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We found the chip.&n;&t; */
id|strcpy
c_func
(paren
id|sa-&gt;dev.name
comma
l_string|&quot;SA1111&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|sa-&gt;dev.bus_id
comma
l_string|&quot;%8.8lx&quot;
comma
id|phys_addr
)paren
suffix:semicolon
id|sa-&gt;dev.parent
op_assign
id|parent
suffix:semicolon
id|sa-&gt;dev.driver
op_assign
op_amp
id|sa1111_device_driver
suffix:semicolon
id|ret
op_assign
id|device_register
c_func
(paren
op_amp
id|sa-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
l_string|&quot;sa1111 device_register failed: %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SA1111 Microprocessor Companion Chip: &quot;
l_string|&quot;silicon revision %lx, metal revision %lx&bslash;n&quot;
comma
(paren
id|id
op_amp
id|SKID_SIREV_MASK
)paren
op_rshift
l_int|4
comma
(paren
id|id
op_amp
id|SKID_MTREV_MASK
)paren
)paren
suffix:semicolon
id|sa1111
op_assign
id|sa
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|unmap
suffix:colon
singleline_comment|//&t;iounmap(sa-&gt;base);
id|release
suffix:colon
id|release_resource
c_func
(paren
op_amp
id|sa-&gt;resource
)paren
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|sa
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Bring the SA1111 out of reset.  This requires a set procedure:&n; *  1. nRESET asserted (by hardware)&n; *  2. CLK turned on from SA1110&n; *  3. nRESET deasserted&n; *  4. VCO turned on, PLL_BYPASS turned off&n; *  5. Wait lock time, then assert RCLKEn&n; *  7. PCR set to allow clocking of individual functions&n; *&n; * Until we&squot;ve done this, the only registers we can access are:&n; *   SBI_SKCR&n; *   SBI_SMCR&n; *   SBI_SKID&n; */
DECL|function|sa1111_wake
r_void
id|sa1111_wake
c_func
(paren
r_void
)paren
(brace
r_struct
id|sa1111_device
op_star
id|sa
op_assign
id|sa1111
suffix:semicolon
r_int
r_int
id|flags
comma
id|r
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * First, set up the 3.6864MHz clock on GPIO 27 for the SA-1111:&n;&t; * (SA-1110 Developer&squot;s Manual, section 9.1.2.1)&n;&t; */
id|GAFR
op_or_assign
id|GPIO_32_768kHz
suffix:semicolon
id|GPDR
op_or_assign
id|GPIO_32_768kHz
suffix:semicolon
id|TUCR
op_assign
id|TUCR_3_6864MHz
suffix:semicolon
multiline_comment|/*&n;&t; * Turn VCO on, and disable PLL Bypass.&n;&t; */
id|r
op_assign
id|readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_SKCR
)paren
suffix:semicolon
id|r
op_and_assign
op_complement
id|SKCR_VCO_OFF
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|sa-&gt;base
op_plus
id|SA1111_SKCR
)paren
suffix:semicolon
id|r
op_or_assign
id|SKCR_PLL_BYPASS
op_or
id|SKCR_OE_EN
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|sa-&gt;base
op_plus
id|SA1111_SKCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait lock time.  SA1111 manual _doesn&squot;t_&n;&t; * specify a figure for this!  We choose 100us.&n;&t; */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable RCLK.  We also ensure that RDYEN is set.&n;&t; */
id|r
op_or_assign
id|SKCR_RCLKEN
op_or
id|SKCR_RDYEN
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|sa-&gt;base
op_plus
id|SA1111_SKCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait 14 RCLK cycles for the chip to finish coming out&n;&t; * of reset. (RCLK=24MHz).  This is 590ns.&n;&t; */
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure all clocks are initially off.&n;&t; */
id|writel
c_func
(paren
l_int|0
comma
id|sa-&gt;base
op_plus
id|SA1111_SKPCR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sa1111_doze
r_void
id|sa1111_doze
c_func
(paren
r_void
)paren
(brace
r_struct
id|sa1111_device
op_star
id|sa
op_assign
id|sa1111
suffix:semicolon
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
id|readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_SKPCR
)paren
op_amp
id|SKPCR_UCLKEN
)paren
(brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SA1111 doze mode refused&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|writel
c_func
(paren
id|readl
c_func
(paren
id|sa-&gt;base
op_plus
id|SA1111_SKCR
)paren
op_amp
op_complement
id|SKCR_RCLKEN
comma
id|sa-&gt;base
op_plus
id|SA1111_SKCR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure the SA1111 shared memory controller.&n; */
DECL|function|sa1111_configure_smc
r_void
id|sa1111_configure_smc
c_func
(paren
r_int
id|sdram
comma
r_int
r_int
id|drac
comma
r_int
r_int
id|cas_latency
)paren
(brace
r_struct
id|sa1111_device
op_star
id|sa
op_assign
id|sa1111
suffix:semicolon
r_int
r_int
id|smcr
op_assign
id|SMCR_DTIM
op_or
id|SMCR_MBGE
op_or
id|FInsrt
c_func
(paren
id|drac
comma
id|SMCR_DRAC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cas_latency
op_eq
l_int|3
)paren
id|smcr
op_or_assign
id|SMCR_CLAT
suffix:semicolon
id|writel
c_func
(paren
id|smcr
comma
id|sa-&gt;base
op_plus
id|SA1111_SMCR
)paren
suffix:semicolon
)brace
multiline_comment|/* According to the &quot;Intel StrongARM SA-1111 Microprocessor Companion&n; * Chip Specification Update&quot; (June 2000), erratum #7, there is a&n; * significant bug in Serial Audio Controller DMA. If the SAC is&n; * accessing a region of memory above 1MB relative to the bank base,&n; * it is important that address bit 10 _NOT_ be asserted. Depending&n; * on the configuration of the RAM, bit 10 may correspond to one&n; * of several different (processor-relative) address bits.&n; *&n; * This routine only identifies whether or not a given DMA address&n; * is susceptible to the bug.&n; */
DECL|function|sa1111_check_dma_bug
r_int
id|sa1111_check_dma_bug
c_func
(paren
id|dma_addr_t
id|addr
)paren
(brace
r_int
r_int
id|physaddr
op_assign
id|SA1111_DMA_ADDR
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
multiline_comment|/* Section 4.6 of the &quot;Intel StrongARM SA-1111 Development Module&n;&t; * User&squot;s Guide&quot; mentions that jumpers R51 and R52 control the&n;&t; * target of SA-1111 DMA (either SDRAM bank 0 on Assabet, or&n;&t; * SDRAM bank 1 on Neponset). The default configuration selects&n;&t; * Assabet, so any address in bank 1 is necessarily invalid.&n;&t; */
r_if
c_cond
(paren
(paren
id|machine_is_assabet
c_func
(paren
)paren
op_logical_or
id|machine_is_pfs168
c_func
(paren
)paren
)paren
op_logical_and
id|addr
op_ge
l_int|0xc8000000
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* The bug only applies to buffers located more than one megabyte&n;&t; * above the start of the target bank:&n;&t; */
r_if
c_cond
(paren
id|physaddr
OL
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|FExtr
c_func
(paren
id|SBI_SMCR
comma
id|SMCR_DRAC
)paren
)paren
(brace
r_case
l_int|01
suffix:colon
multiline_comment|/* 10 row + bank address bits, A&lt;20&gt; must not be set */
r_if
c_cond
(paren
id|physaddr
op_amp
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|02
suffix:colon
multiline_comment|/* 11 row + bank address bits, A&lt;23&gt; must not be set */
r_if
c_cond
(paren
id|physaddr
op_amp
(paren
l_int|1
op_lshift
l_int|23
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|03
suffix:colon
multiline_comment|/* 12 row + bank address bits, A&lt;24&gt; must not be set */
r_if
c_cond
(paren
id|physaddr
op_amp
(paren
l_int|1
op_lshift
l_int|24
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|04
suffix:colon
multiline_comment|/* 13 row + bank address bits, A&lt;25&gt; must not be set */
r_if
c_cond
(paren
id|physaddr
op_amp
(paren
l_int|1
op_lshift
l_int|25
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|05
suffix:colon
multiline_comment|/* 14 row + bank address bits, A&lt;20&gt; must not be set */
r_if
c_cond
(paren
id|physaddr
op_amp
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|06
suffix:colon
multiline_comment|/* 15 row + bank address bits, A&lt;20&gt; must not be set */
r_if
c_cond
(paren
id|physaddr
op_amp
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s(): invalid SMCR DRAC value 0%lo&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|FExtr
c_func
(paren
id|SBI_SMCR
comma
id|SMCR_DRAC
)paren
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
DECL|variable|sa1111_check_dma_bug
id|EXPORT_SYMBOL
c_func
(paren
id|sa1111_check_dma_bug
)paren
suffix:semicolon
DECL|function|sa1111_init
r_int
id|sa1111_init
c_func
(paren
r_struct
id|device
op_star
id|parent
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|irq
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|sa1111_probe
c_func
(paren
id|parent
comma
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * We found it.  Wake the chip up.&n;&t; */
id|sa1111_wake
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The SDRAM configuration of the SA1110 and the SA1111 must&n;&t; * match.  This is very important to ensure that SA1111 accesses&n;&t; * don&squot;t corrupt the SDRAM.  Note that this ungates the SA1111&squot;s&n;&t; * MBGNT signal, so we must have called sa1110_mb_disable()&n;&t; * beforehand.&n;&t; */
id|sa1111_configure_smc
c_func
(paren
l_int|1
comma
id|FExtr
c_func
(paren
id|MDCNFG
comma
id|MDCNFG_SA1110_DRAC0
)paren
comma
id|FExtr
c_func
(paren
id|MDCNFG
comma
id|MDCNFG_SA1110_TDL0
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We only need to turn on DCLK whenever we want to use the&n;&t; * DMA.  It can otherwise be held firmly in the off position.&n;&t; */
id|SKPCR
op_or_assign
id|SKPCR_DCLKEN
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the SA1110 memory bus request and grant signals.&n;&t; */
id|sa1110_mb_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise SA1111 IRQs&n;&t; */
id|sa1111_init_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
