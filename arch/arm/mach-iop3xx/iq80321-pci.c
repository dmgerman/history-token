multiline_comment|/*&n; * arch/arm/mach-iop3xx/iq80321-pci.c&n; *&n; * PCI support for the Intel IQ80321 reference board&n; *&n; * Author: Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright (C) 2002 Rory Bolt&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
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
mdefine_line|#define INTA&t;IRQ_IQ80321_INTA
DECL|macro|INTB
mdefine_line|#define INTB&t;IRQ_IQ80321_INTB
DECL|macro|INTC
mdefine_line|#define INTC&t;IRQ_IQ80321_INTC
DECL|macro|INTD
mdefine_line|#define INTD&t;IRQ_IQ80321_INTD
DECL|macro|INTE
mdefine_line|#define INTE&t;IRQ_IQ80321_I82544
DECL|typedef|irq_table
r_typedef
id|u8
id|irq_table
(braket
l_int|4
)braket
suffix:semicolon
DECL|variable|pci_irq_table
r_static
id|irq_table
id|pci_irq_table
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&t; * PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; * A       B       C       D&n;&t; */
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
multiline_comment|/* Gig-E */
(brace
id|INTD
comma
id|INTC
comma
id|INTD
comma
id|INTA
)brace
comma
multiline_comment|/* Unused */
(brace
id|INTC
comma
id|INTD
comma
id|INTA
comma
id|INTB
)brace
comma
multiline_comment|/* PCI-X Slot */
)brace
suffix:semicolon
r_static
r_inline
r_int
id|__init
DECL|function|iq80321_map_irq
id|iq80321_map_irq
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
l_int|2
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|iq80321_setup
r_static
r_int
id|iq80321_setup
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
r_switch
c_cond
(paren
id|nr
)paren
(brace
r_case
l_int|0
suffix:colon
id|sys-&gt;map_irq
op_assign
id|iq80321_map_irq
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|iop321_setup
c_func
(paren
id|nr
comma
id|sys
)paren
suffix:semicolon
)brace
DECL|function|iq80321_preinit
r_static
r_void
id|iq80321_preinit
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
id|iq80321_pci
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
id|iq80321_setup
comma
dot
id|scan
op_assign
id|iop321_scan_bus
comma
dot
id|preinit
op_assign
id|iq80321_preinit
comma
)brace
suffix:semicolon
DECL|function|iq80321_pci_init
r_static
r_int
id|__init
id|iq80321_pci_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_iq80321
c_func
(paren
)paren
)paren
id|pci_common_init
c_func
(paren
op_amp
id|iq80321_pci
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|iq80321_pci_init
id|subsys_initcall
c_func
(paren
id|iq80321_pci_init
)paren
suffix:semicolon
eof
