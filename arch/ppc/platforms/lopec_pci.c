multiline_comment|/*&n; * arch/ppc/platforms/lopec_pci.c&n; * &n; * PCI setup routines for the Motorola LoPEC.&n; *&n; * Author: Dan Cox&n; *         danc@mvista.com (or, alternately, source@mvista.com)&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/open_pic.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
r_static
r_inline
r_int
id|__init
DECL|function|lopec_map_irq
id|lopec_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_int
id|irq
suffix:semicolon
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 11 - Winbond */
(brace
l_int|22
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 12 - SCSI */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 13 - nothing */
(brace
l_int|17
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 14 - 82559 Ethernet */
(brace
l_int|27
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 15 - USB */
(brace
l_int|23
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 16 - PMC slot 1 */
(brace
l_int|24
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 17 - PMC slot 2 */
(brace
l_int|25
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 18 - PCI slot */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 19 - nothing */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 20 - nothing */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 21 - nothing */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 22 - nothing */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 23 - nothing */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 24 - PMC slot 1b */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* ID 25 - nothing */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
multiline_comment|/* ID 26 - PMC Slot 2b */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|11
comma
id|max_idsel
op_assign
l_int|26
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
id|irq
op_assign
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
r_void
id|__init
DECL|function|lopec_setup_winbond_83553
id|lopec_setup_winbond_83553
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
r_int
id|devfn
suffix:semicolon
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
l_int|11
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* IDE interrupt routing (primary 14, secondary 15) */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x43
comma
l_int|0xef
)paren
suffix:semicolon
multiline_comment|/* PCI interrupt routing */
id|early_write_config_word
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x44
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* ISA-PCI address decoder */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x48
comma
l_int|0xf0
)paren
suffix:semicolon
multiline_comment|/* RTC, kb, not used in PPC */
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x4d
comma
l_int|0x00
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x4e
comma
l_int|0x04
)paren
suffix:semicolon
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
l_int|11
comma
l_int|1
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x09
comma
l_int|0x8f
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|devfn
comma
l_int|0x40
comma
l_int|0x00ff0011
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|lopec_find_bridges
id|lopec_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
suffix:semicolon
id|hose-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|mpc10x_bridge_init
c_func
(paren
id|hose
comma
id|MPC10X_MEM_MAP_B
comma
id|MPC10X_MEM_MAP_B
comma
id|MPC10X_MAPB_EUMB_BASE
)paren
op_eq
l_int|0
)paren
(brace
id|hose-&gt;mem_resources
(braket
l_int|0
)braket
dot
id|end
op_assign
l_int|0xffffffff
suffix:semicolon
id|lopec_setup_winbond_83553
c_func
(paren
id|hose
)paren
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
)paren
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
id|ppc_md.pci_map_irq
op_assign
id|lopec_map_irq
suffix:semicolon
)brace
)brace
eof