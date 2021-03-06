multiline_comment|/*&n; * arch/arm/mach-iop3xx/iq80321-pci.c&n; *&n; * PCI support for the Intel IQ80321 reference board&n; *&n; * Author: Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright (C) 2002 Rory Bolt&n; * Copyright (C) 2004 Intel Corp.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/*&n; * The following macro is used to lookup irqs in a standard table&n; * format for those systems that do not already have PCI&n; * interrupts properly routed.  We assume 1 &lt;= pin &lt;= 4&n; */
DECL|macro|PCI_IRQ_TABLE_LOOKUP
mdefine_line|#define PCI_IRQ_TABLE_LOOKUP(minid,maxid)&t;&bslash;&n;({ int _ctl_ = -1;&t;&t;&t;&t;&bslash;&n;   unsigned int _idsel = idsel - minid;&t;&t;&bslash;&n;   if (_idsel &lt;= maxid)&t;&t;&t;&t;&bslash;&n;      _ctl_ = pci_irq_table[_idsel][pin-1];&t;&bslash;&n;   _ctl_; })
DECL|macro|INTA
mdefine_line|#define INTA&t;IRQ_IQ31244_INTA
DECL|macro|INTB
mdefine_line|#define INTB&t;IRQ_IQ31244_INTB
DECL|macro|INTC
mdefine_line|#define INTC&t;IRQ_IQ31244_INTC
DECL|macro|INTD
mdefine_line|#define INTD&t;IRQ_IQ31244_INTD
DECL|macro|INTE
mdefine_line|#define INTE&t;IRQ_IQ31244_I82546
r_static
r_inline
r_int
id|__init
DECL|function|iq31244_map_irq
id|iq31244_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|idsel
comma
id|u8
id|pin
)paren
(brace
r_static
r_int
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
(brace
multiline_comment|/*&n;&t;&t; * PCI IDSEL/INTPIN-&gt;INTLINE&n;&t;&t; * A       B       C       D&n;&t;&t; */
macro_line|#ifdef CONFIG_ARCH_EP80219
(brace
id|INTB
comma
id|INTB
comma
id|INTB
comma
id|INTB
)brace
comma
multiline_comment|/* CFlash */
(brace
id|INTE
comma
id|INTE
comma
id|INTE
comma
id|INTE
)brace
comma
multiline_comment|/* 82551 Pro 100 */
(brace
id|INTD
comma
id|INTD
comma
id|INTD
comma
id|INTD
)brace
comma
multiline_comment|/* PCI-X Slot */
(brace
id|INTC
comma
id|INTC
comma
id|INTC
comma
id|INTC
)brace
comma
multiline_comment|/* SATA   */
macro_line|#else
(brace
id|INTB
comma
id|INTB
comma
id|INTB
comma
id|INTB
)brace
comma
multiline_comment|/* CFlash */
(brace
id|INTC
comma
id|INTC
comma
id|INTC
comma
id|INTC
)brace
comma
multiline_comment|/* SATA   */
(brace
id|INTD
comma
id|INTD
comma
id|INTD
comma
id|INTD
)brace
comma
multiline_comment|/* PCI-X Slot */
(brace
id|INTE
comma
id|INTE
comma
id|INTE
comma
id|INTE
)brace
comma
multiline_comment|/* 82546 GigE */
macro_line|#endif 
singleline_comment|// CONFIG_ARCH_EP80219
)brace
suffix:semicolon
id|BUG_ON
c_func
(paren
id|pin
template_param
l_int|4
)paren
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
c_func
(paren
l_int|0
comma
l_int|7
)paren
suffix:semicolon
)brace
DECL|function|iq31244_setup
r_static
r_int
id|iq31244_setup
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
op_ne
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
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
op_logical_neg
id|res
)paren
id|panic
c_func
(paren
l_string|&quot;PCI: unable to alloc resources&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|resource
)paren
op_star
l_int|2
)paren
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|start
op_assign
id|IOP321_PCI_LOWER_IO_VA
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|end
op_assign
id|IOP321_PCI_UPPER_IO_VA
suffix:semicolon
id|res
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;IQ31244 PCI I/O Space&quot;
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
id|start
op_assign
id|IOP321_PCI_LOWER_MEM_PA
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|end
op_assign
id|IOP321_PCI_UPPER_MEM_PA
suffix:semicolon
id|res
(braket
l_int|1
)braket
dot
id|name
op_assign
l_string|&quot;IQ31244 PCI Memory Space&quot;
suffix:semicolon
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
id|sys-&gt;mem_offset
op_assign
id|IOP321_PCI_MEM_OFFSET
suffix:semicolon
id|sys-&gt;io_offset
op_assign
id|IOP321_PCI_IO_OFFSET
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
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|iq31244_preinit
r_static
r_void
id|iq31244_preinit
c_func
(paren
r_void
)paren
(brace
id|iop321_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|hw_pci
id|iq31244_pci
id|__initdata
op_assign
(brace
dot
id|swizzle
op_assign
id|pci_std_swizzle
comma
dot
id|nr_controllers
op_assign
l_int|1
comma
dot
id|setup
op_assign
id|iq31244_setup
comma
dot
id|scan
op_assign
id|iop321_scan_bus
comma
dot
id|preinit
op_assign
id|iq31244_preinit
comma
dot
id|map_irq
op_assign
id|iq31244_map_irq
)brace
suffix:semicolon
DECL|function|iq31244_pci_init
r_static
r_int
id|__init
id|iq31244_pci_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_iq31244
c_func
(paren
)paren
)paren
id|pci_common_init
c_func
(paren
op_amp
id|iq31244_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|iq31244_pci_init
id|subsys_initcall
c_func
(paren
id|iq31244_pci_init
)paren
suffix:semicolon
eof
