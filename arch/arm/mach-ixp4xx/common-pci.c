multiline_comment|/*&n; * arch/arm/mach-ixp4xx/common-pci.c &n; *&n; * IXP4XX PCI routines for all platforms&n; *&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002 Intel Corporation.&n; * Copyright (C) 2003 Greg Ungerer &lt;gerg@snapgear.com&gt;&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
multiline_comment|/*&n; * IXP4xx PCI read function is dependent on whether we are &n; * running A0 or B0 (AppleGate) silicon.&n; */
DECL|variable|ixp4xx_pci_read
r_int
(paren
op_star
id|ixp4xx_pci_read
)paren
(paren
id|u32
id|addr
comma
id|u32
id|cmd
comma
id|u32
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Base address for PCI regsiter region&n; */
DECL|variable|ixp4xx_pci_reg_base
r_int
r_int
id|ixp4xx_pci_reg_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * PCI cfg an I/O routines are done by programming a &n; * command/byte enable register, and then read/writing&n; * the data from a data regsiter. We need to ensure&n; * these transactions are atomic or we will end up&n; * with corrupt data on the bus or in a driver.&n; */
DECL|variable|ixp4xx_pci_lock
r_static
id|spinlock_t
id|ixp4xx_pci_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Read from PCI config space&n; */
DECL|function|crp_read
r_static
r_void
id|crp_read
c_func
(paren
id|u32
id|ad_cbe
comma
id|u32
op_star
id|data
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
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|PCI_CRP_AD_CBE
op_assign
id|ad_cbe
suffix:semicolon
op_star
id|data
op_assign
op_star
id|PCI_CRP_RDATA
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write to PCI config space&n; */
DECL|function|crp_write
r_static
r_void
id|crp_write
c_func
(paren
id|u32
id|ad_cbe
comma
id|u32
id|data
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
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|PCI_CRP_AD_CBE
op_assign
id|CRP_AD_CBE_WRITE
op_or
id|ad_cbe
suffix:semicolon
op_star
id|PCI_CRP_WDATA
op_assign
id|data
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|check_master_abort
r_static
r_inline
r_int
id|check_master_abort
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* check Master Abort bit after access */
r_int
r_int
id|isr
op_assign
op_star
id|PCI_ISR
suffix:semicolon
r_if
c_cond
(paren
id|isr
op_amp
id|PCI_ISR_PFE
)paren
(brace
multiline_comment|/* make sure the Master Abort bit is reset */
op_star
id|PCI_ISR
op_assign
id|PCI_ISR_PFE
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_read_errata
r_int
id|ixp4xx_pci_read_errata
c_func
(paren
id|u32
id|addr
comma
id|u32
id|cmd
comma
id|u32
op_star
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|PCI_NP_AD
op_assign
id|addr
suffix:semicolon
multiline_comment|/* &n;&t; * PCI workaround  - only works if NP PCI space reads have &n;&t; * no side effects!!! Read 8 times. last one will be good.&n;&t; */
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
op_star
id|PCI_NP_CBE
op_assign
id|cmd
suffix:semicolon
op_star
id|data
op_assign
op_star
id|PCI_NP_RDATA
suffix:semicolon
op_star
id|data
op_assign
op_star
id|PCI_NP_RDATA
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_master_abort
c_func
(paren
)paren
)paren
(brace
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_read_no_errata
r_int
id|ixp4xx_pci_read_no_errata
c_func
(paren
id|u32
id|addr
comma
id|u32
id|cmd
comma
id|u32
op_star
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|PCI_NP_AD
op_assign
id|addr
suffix:semicolon
multiline_comment|/* set up and execute the read */
op_star
id|PCI_NP_CBE
op_assign
id|cmd
suffix:semicolon
multiline_comment|/* the result of the read is now in NP_RDATA */
op_star
id|data
op_assign
op_star
id|PCI_NP_RDATA
suffix:semicolon
r_if
c_cond
(paren
id|check_master_abort
c_func
(paren
)paren
)paren
(brace
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_write
r_int
id|ixp4xx_pci_write
c_func
(paren
id|u32
id|addr
comma
id|u32
id|cmd
comma
id|u32
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|PCI_NP_AD
op_assign
id|addr
suffix:semicolon
multiline_comment|/* set up the write */
op_star
id|PCI_NP_CBE
op_assign
id|cmd
suffix:semicolon
multiline_comment|/* execute the write by writing to NP_WDATA */
op_star
id|PCI_NP_WDATA
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|check_master_abort
c_func
(paren
)paren
)paren
(brace
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ixp4xx_pci_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ixp4xx_config_addr
r_static
id|u32
id|ixp4xx_config_addr
c_func
(paren
id|u8
id|bus_num
comma
id|u16
id|devfn
comma
r_int
id|where
)paren
(brace
id|u32
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus_num
)paren
(brace
multiline_comment|/* type 0 */
id|addr
op_assign
id|BIT
c_func
(paren
l_int|32
op_minus
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
)paren
op_or
(paren
(paren
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|where
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* type 1 */
id|addr
op_assign
(paren
id|bus_num
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
)paren
op_lshift
l_int|11
)paren
op_or
(paren
(paren
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|where
op_amp
op_complement
l_int|3
)paren
op_or
l_int|1
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Mask table, bits to mask for quantity of size 1, 2 or 4 bytes.&n; * 0 and 3 are not valid indexes...&n; */
DECL|variable|bytemask
r_static
id|u32
id|bytemask
(braket
)braket
op_assign
(brace
multiline_comment|/*0*/
l_int|0
comma
multiline_comment|/*1*/
l_int|0xff
comma
multiline_comment|/*2*/
l_int|0xffff
comma
multiline_comment|/*3*/
l_int|0
comma
multiline_comment|/*4*/
l_int|0xffffffff
comma
)brace
suffix:semicolon
DECL|function|local_byte_lane_enable_bits
r_static
id|u32
id|local_byte_lane_enable_bits
c_func
(paren
id|u32
id|n
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
r_return
(paren
l_int|0xf
op_amp
op_complement
id|BIT
c_func
(paren
id|n
)paren
)paren
op_lshift
id|CRP_AD_CBE_BESL
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
r_return
(paren
l_int|0xf
op_amp
op_complement
(paren
id|BIT
c_func
(paren
id|n
)paren
op_or
id|BIT
c_func
(paren
id|n
op_plus
l_int|1
)paren
)paren
)paren
op_lshift
id|CRP_AD_CBE_BESL
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|0xffffffff
suffix:semicolon
)brace
DECL|function|local_read_config
r_static
r_int
id|local_read_config
c_func
(paren
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
id|u32
id|n
comma
id|data
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;local_read_config from %d size %d&bslash;n&quot;
comma
id|where
comma
id|size
)paren
suffix:semicolon
id|n
op_assign
id|where
op_mod
l_int|4
suffix:semicolon
id|crp_read
c_func
(paren
id|where
op_amp
op_complement
l_int|3
comma
op_amp
id|data
)paren
suffix:semicolon
op_star
id|value
op_assign
(paren
id|data
op_rshift
(paren
l_int|8
op_star
id|n
)paren
)paren
op_amp
id|bytemask
(braket
id|size
)braket
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;local_read_config read %#x&bslash;n&quot;
comma
op_star
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|local_write_config
r_static
r_int
id|local_write_config
c_func
(paren
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|data
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;local_write_config %#x to %d size %d&bslash;n&quot;
comma
id|value
comma
id|where
comma
id|size
)paren
suffix:semicolon
id|n
op_assign
id|where
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
id|local_byte_lane_enable_bits
c_func
(paren
id|n
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|byte_enables
op_eq
l_int|0xffffffff
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|data
op_assign
id|value
op_lshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
id|crp_write
c_func
(paren
(paren
id|where
op_amp
op_complement
l_int|3
)paren
op_or
id|byte_enables
comma
id|data
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|byte_lane_enable_bits
r_static
id|u32
id|byte_lane_enable_bits
c_func
(paren
id|u32
id|n
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
l_int|1
)paren
r_return
(paren
l_int|0xf
op_amp
op_complement
id|BIT
c_func
(paren
id|n
)paren
)paren
op_lshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|2
)paren
r_return
(paren
l_int|0xf
op_amp
op_complement
(paren
id|BIT
c_func
(paren
id|n
)paren
op_or
id|BIT
c_func
(paren
id|n
op_plus
l_int|1
)paren
)paren
)paren
op_lshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|0xffffffff
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_read_config
r_static
r_int
id|ixp4xx_pci_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
id|u16
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|value
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|addr
comma
id|data
suffix:semicolon
id|u8
id|bus_num
op_assign
id|bus-&gt;number
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;read_config from %d size %d dev %d:%d:%d&bslash;n&quot;
comma
id|where
comma
id|size
comma
id|bus_num
comma
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
)paren
suffix:semicolon
op_star
id|value
op_assign
l_int|0xffffffff
suffix:semicolon
id|n
op_assign
id|where
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
id|byte_lane_enable_bits
c_func
(paren
id|n
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|byte_enables
op_eq
l_int|0xffffffff
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|addr
op_assign
id|ixp4xx_config_addr
c_func
(paren
id|bus_num
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_read
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_CONFIGREAD
comma
op_amp
id|data
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
op_star
id|value
op_assign
(paren
id|data
op_rshift
(paren
l_int|8
op_star
id|n
)paren
)paren
op_amp
id|bytemask
(braket
id|size
)braket
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;read_config_byte read %#x&bslash;n&quot;
comma
op_star
id|value
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_write_config
r_static
r_int
id|ixp4xx_pci_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
id|u16
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|value
)paren
(brace
id|u32
id|n
comma
id|byte_enables
comma
id|addr
comma
id|data
suffix:semicolon
id|u8
id|bus_num
op_assign
id|bus-&gt;number
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;write_config_byte %#x to %d size %d dev %d:%d:%d&bslash;n&quot;
comma
id|value
comma
id|where
comma
id|size
comma
id|bus_num
comma
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
)paren
suffix:semicolon
id|n
op_assign
id|where
op_mod
l_int|4
suffix:semicolon
id|byte_enables
op_assign
id|byte_lane_enable_bits
c_func
(paren
id|n
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|byte_enables
op_eq
l_int|0xffffffff
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|addr
op_assign
id|ixp4xx_config_addr
c_func
(paren
id|bus_num
comma
id|devfn
comma
id|where
)paren
suffix:semicolon
id|data
op_assign
id|value
op_lshift
(paren
l_int|8
op_star
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ixp4xx_pci_write
c_func
(paren
id|addr
comma
id|byte_enables
op_or
id|NP_CMD_CONFIGWRITE
comma
id|data
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|ixp4xx_ops
r_struct
id|pci_ops
id|ixp4xx_ops
op_assign
(brace
dot
id|read
op_assign
id|ixp4xx_pci_read_config
comma
dot
id|write
op_assign
id|ixp4xx_pci_write_config
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * PCI abort handler&n; */
DECL|function|abort_handler
r_static
r_int
id|abort_handler
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|isr
comma
id|status
suffix:semicolon
id|isr
op_assign
op_star
id|PCI_ISR
suffix:semicolon
id|local_read_config
c_func
(paren
id|PCI_STATUS
comma
l_int|2
comma
op_amp
id|status
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;PCI: abort_handler addr = %#lx, isr = %#x, &quot;
l_string|&quot;status = %#x&bslash;n&quot;
comma
id|addr
comma
id|isr
comma
id|status
)paren
suffix:semicolon
multiline_comment|/* make sure the Master Abort bit is reset */
op_star
id|PCI_ISR
op_assign
id|PCI_ISR_PFE
suffix:semicolon
id|status
op_or_assign
id|PCI_STATUS_REC_MASTER_ABORT
suffix:semicolon
id|local_write_config
c_func
(paren
id|PCI_STATUS
comma
l_int|2
comma
id|status
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If it was an imprecise abort, then we need to correct the&n;&t; * return address to be _after_ the instruction.&n;&t; */
r_if
c_cond
(paren
id|fsr
op_amp
(paren
l_int|1
op_lshift
l_int|10
)paren
)paren
id|regs-&gt;ARM_pc
op_add_assign
l_int|4
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup DMA mask to 64MB on PCI devices. Ignore all other devices.&n; */
DECL|function|ixp4xx_pci_platform_notify
r_static
r_int
id|ixp4xx_pci_platform_notify
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus
op_eq
op_amp
id|pci_bus_type
)paren
(brace
op_star
id|dev-&gt;dma_mask
op_assign
id|SZ_64M
op_minus
l_int|1
suffix:semicolon
id|dev-&gt;coherent_dma_mask
op_assign
id|SZ_64M
op_minus
l_int|1
suffix:semicolon
id|dmabounce_register_dev
c_func
(paren
id|dev
comma
l_int|2048
comma
l_int|4096
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_platform_notify_remove
r_static
r_int
id|ixp4xx_pci_platform_notify_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus
op_eq
op_amp
id|pci_bus_type
)paren
(brace
id|dmabounce_unregister_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_needs_bounce
r_int
id|dma_needs_bounce
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_addr
comma
r_int
id|size
)paren
(brace
r_return
(paren
id|dev-&gt;bus
op_eq
op_amp
id|pci_bus_type
)paren
op_logical_and
(paren
(paren
id|dma_addr
op_plus
id|size
)paren
op_ge
id|SZ_64M
)paren
suffix:semicolon
)brace
DECL|function|ixp4xx_pci_preinit
r_void
id|__init
id|ixp4xx_pci_preinit
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|processor_id
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mrc p15, 0, %0, cr0, cr0, 0;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|processor_id
)paren
suffix:colon
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Determine which PCI read method to use&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|processor_id
op_amp
l_int|0xf
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: IXP4xx A0 silicon detected - &quot;
l_string|&quot;PCI Non-Prefetch Workaround Enabled&bslash;n&quot;
)paren
suffix:semicolon
id|ixp4xx_pci_read
op_assign
id|ixp4xx_pci_read_errata
suffix:semicolon
)brace
r_else
id|ixp4xx_pci_read
op_assign
id|ixp4xx_pci_read_no_errata
suffix:semicolon
multiline_comment|/* hook in our fault handler for PCI errors */
id|hook_fault_code
c_func
(paren
l_int|16
op_plus
l_int|6
comma
id|abort_handler
comma
id|SIGBUS
comma
l_string|&quot;imprecise external abort&quot;
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;setup PCI-AHB(inbound) and AHB-PCI(outbound) address mappings&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * We use identity AHB-&gt;PCI address translation&n;&t; * in the 0x48000000 to 0x4bffffff address space&n;&t; */
op_star
id|PCI_PCIMEMBASE
op_assign
l_int|0x48494A4B
suffix:semicolon
multiline_comment|/* &n;&t; * We also use identity PCI-&gt;AHB address translation&n;&t; * in 4 16MB BARs that begin at the physical memory start&n;&t; */
op_star
id|PCI_AHBMEMBASE
op_assign
(paren
id|PHYS_OFFSET
op_amp
l_int|0xFF000000
)paren
op_plus
(paren
(paren
id|PHYS_OFFSET
op_amp
l_int|0xFF000000
)paren
op_rshift
l_int|8
)paren
op_plus
(paren
(paren
id|PHYS_OFFSET
op_amp
l_int|0xFF000000
)paren
op_rshift
l_int|16
)paren
op_plus
(paren
(paren
id|PHYS_OFFSET
op_amp
l_int|0xFF000000
)paren
op_rshift
l_int|24
)paren
op_plus
l_int|0x00010203
suffix:semicolon
r_if
c_cond
(paren
op_star
id|PCI_CSR
op_amp
id|PCI_CSR_HOST
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: IXP4xx is host&bslash;n&quot;
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;setup BARs in controller&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We configure the PCI inbound memory windows to be &n;&t;&t; * 1:1 mapped to SDRAM&n;&t;&t; */
id|local_write_config
c_func
(paren
id|PCI_BASE_ADDRESS_0
comma
l_int|4
comma
id|PHYS_OFFSET
op_plus
l_int|0x00000000
)paren
suffix:semicolon
id|local_write_config
c_func
(paren
id|PCI_BASE_ADDRESS_1
comma
l_int|4
comma
id|PHYS_OFFSET
op_plus
l_int|0x01000000
)paren
suffix:semicolon
id|local_write_config
c_func
(paren
id|PCI_BASE_ADDRESS_2
comma
l_int|4
comma
id|PHYS_OFFSET
op_plus
l_int|0x02000000
)paren
suffix:semicolon
id|local_write_config
c_func
(paren
id|PCI_BASE_ADDRESS_3
comma
l_int|4
comma
id|PHYS_OFFSET
op_plus
l_int|0x03000000
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Enable CSR window at 0xff000000.&n;&t;&t; */
id|local_write_config
c_func
(paren
id|PCI_BASE_ADDRESS_4
comma
l_int|4
comma
l_int|0xff000008
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Enable the IO window to be way up high, at 0xfffffc00&n;&t;&t; */
id|local_write_config
c_func
(paren
id|PCI_BASE_ADDRESS_5
comma
l_int|4
comma
l_int|0xfffffc01
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: IXP4xx is target - No bus scan performed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: IXP4xx Using %s access for memory space&bslash;n&quot;
comma
macro_line|#ifndef CONFIG_IXP4XX_INDIRECT_PCI
l_string|&quot;direct&quot;
macro_line|#else
l_string|&quot;indirect&quot;
macro_line|#endif
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;clear error bits in ISR&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|PCI_ISR
op_assign
id|PCI_ISR_PSE
op_or
id|PCI_ISR_PFE
op_or
id|PCI_ISR_PPE
op_or
id|PCI_ISR_AHBE
suffix:semicolon
multiline_comment|/*&n;&t; * Set Initialize Complete in PCI Control Register: allow IXP4XX to&n;&t; * respond to PCI configuration cycles. Specify that the AHB bus is&n;&t; * operating in big endian mode. Set up byte lane swapping between &n;&t; * little-endian PCI and the big-endian AHB bus &n;&t; */
macro_line|#ifdef __ARMEB__
op_star
id|PCI_CSR
op_assign
id|PCI_CSR_IC
op_or
id|PCI_CSR_ABE
op_or
id|PCI_CSR_PDS
op_or
id|PCI_CSR_ADS
suffix:semicolon
macro_line|#else
op_star
id|PCI_CSR
op_assign
id|PCI_CSR_IC
suffix:semicolon
macro_line|#endif
id|pr_debug
c_func
(paren
l_string|&quot;DONE&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ixp4xx_setup
r_int
id|ixp4xx_setup
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
op_star
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* &n;&t;&t; * If we&squot;re out of memory this early, something is wrong,&n;&t;&t; * so we might as well catch it here.&n;&t;&t; */
id|panic
c_func
(paren
l_string|&quot;PCI: unable to allocate resources?&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|res
)paren
op_star
l_int|2
)paren
suffix:semicolon
id|local_write_config
c_func
(paren
id|PCI_COMMAND
comma
l_int|2
comma
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_MEMORY
)paren
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;PCI I/O Space&quot;
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0x00001000
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|end
op_assign
l_int|0xffff0000
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|name
op_assign
l_string|&quot;PCI Memory Space&quot;
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|start
op_assign
l_int|0x48000000
suffix:semicolon
macro_line|#ifndef CONFIG_IXP4XX_INDIRECT_PCI
id|res
(braket
l_int|1
)braket
dot
id|end
op_assign
l_int|0x4bffffff
suffix:semicolon
macro_line|#else
id|res
(braket
l_int|1
)braket
dot
id|end
op_assign
l_int|0x4fffffff
suffix:semicolon
macro_line|#endif
id|res
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|res
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|res
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|0
)braket
op_assign
op_amp
id|res
(braket
l_int|0
)braket
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|res
(braket
l_int|1
)braket
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|platform_notify
op_assign
id|ixp4xx_pci_platform_notify
suffix:semicolon
id|platform_notify_remove
op_assign
id|ixp4xx_pci_platform_notify_remove
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ixp4xx_scan_bus
r_struct
id|pci_bus
op_star
id|ixp4xx_scan_bus
c_func
(paren
r_int
id|nr
comma
r_struct
id|pci_sys_data
op_star
id|sys
)paren
(brace
r_return
id|pci_scan_bus
c_func
(paren
id|sys-&gt;busnr
comma
op_amp
id|ixp4xx_ops
comma
id|sys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We override these so we properly do dmabounce otherwise drivers&n; * are able to set the dma_mask to 0xffffffff and we can no longer&n; * trap bounces. :(&n; *&n; * We just return true on everyhing except for &lt; 64MB in which case &n; * we will fail miseralby and die since we can&squot;t handle that case.&n; */
r_int
DECL|function|pci_set_dma_mask
id|pci_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_ge
id|SZ_64M
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_int
DECL|function|pci_dac_set_dma_mask
id|pci_dac_set_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_ge
id|SZ_64M
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_int
DECL|function|pci_set_consistent_dma_mask
id|pci_set_consistent_dma_mask
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_ge
id|SZ_64M
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|variable|pci_set_dma_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_dma_mask
)paren
suffix:semicolon
DECL|variable|pci_dac_set_dma_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dac_set_dma_mask
)paren
suffix:semicolon
DECL|variable|pci_set_consistent_dma_mask
id|EXPORT_SYMBOL
c_func
(paren
id|pci_set_consistent_dma_mask
)paren
suffix:semicolon
DECL|variable|ixp4xx_pci_read
id|EXPORT_SYMBOL
c_func
(paren
id|ixp4xx_pci_read
)paren
suffix:semicolon
DECL|variable|ixp4xx_pci_write
id|EXPORT_SYMBOL
c_func
(paren
id|ixp4xx_pci_write
)paren
suffix:semicolon
eof
