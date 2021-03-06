multiline_comment|/*&n; * PCI autoconfiguration library&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * Copyright 2000, 2001 MontaVista Software Inc.&n; * Copyright 2001 Bradley D. LaRonde &lt;brad@ltc.com&gt;&n; * Copyright 2003 Paul Mundt &lt;lethal@linux-sh.org&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * Modified for MIPS by Jun Sun, jsun@mvista.com&n; *&n; * . Simplify the interface between pci_auto and the rest: a single function.&n; * . Assign resources from low address to upper address.&n; * . change most int to u32.&n; *&n; * Further modified to include it as mips generic code, ppopov@mvista.com.&n; *&n; * 2001-10-26  Bradley D. LaRonde &lt;brad@ltc.com&gt;&n; * - Add a top_bus argument to the &quot;early config&quot; functions so that&n; *   they can set a fake parent bus pointer to convince the underlying&n; *   pci ops to use type 1 configuration for sub busses.&n; * - Set bridge base and limit registers correctly.&n; * - Align io and memory base properly before and after bridge setup.&n; * - Don&squot;t fall through to pci_setup_bars for bridge.&n; * - Reformat the debug output to look more like lspci&squot;s output.&n; *&n; * Cloned for SuperH by M. R. Brown, mrbrown@0xd6.org&n; *&n; * 2003-08-05  Paul Mundt &lt;lethal@linux-sh.org&gt;&n; * - Don&squot;t update the BAR values on systems that already have valid addresses&n; *   and don&squot;t want these updated for whatever reason, by way of a new config&n; *   option check. However, we still read in the old BAR values so that they&n; *   can still be reported through the debug output.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|DEBUG
macro_line|#undef&t;DEBUG
macro_line|#ifdef &t;DEBUG
DECL|macro|DBG
mdefine_line|#define&t;DBG(x...)&t;printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define&t;DBG(x...)&t;
macro_line|#endif
multiline_comment|/*&n; * These functions are used early on before PCI scanning is done&n; * and all of the pci_dev and pci_bus structures have been created.&n; */
DECL|function|fake_pci_dev
r_static
r_struct
id|pci_dev
op_star
id|fake_pci_dev
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|busnr
comma
r_int
id|devfn
)paren
(brace
r_static
r_struct
id|pci_dev
id|dev
suffix:semicolon
r_static
r_struct
id|pci_bus
id|bus
suffix:semicolon
id|dev.bus
op_assign
op_amp
id|bus
suffix:semicolon
id|dev.sysdata
op_assign
id|hose
suffix:semicolon
id|dev.devfn
op_assign
id|devfn
suffix:semicolon
id|bus.number
op_assign
id|busnr
suffix:semicolon
id|bus.ops
op_assign
id|hose-&gt;pci_ops
suffix:semicolon
r_if
c_cond
(paren
id|busnr
op_ne
id|top_bus
)paren
(brace
multiline_comment|/* Fake a parent bus structure. */
id|bus.parent
op_assign
op_amp
id|bus
suffix:semicolon
)brace
r_else
id|bus.parent
op_assign
l_int|NULL
suffix:semicolon
r_return
op_amp
id|dev
suffix:semicolon
)brace
DECL|macro|EARLY_PCI_OP
mdefine_line|#define EARLY_PCI_OP(rw, size, type)&t;&t;&t;&t;&t;&bslash;&n;int early_##rw##_config_##size(struct pci_channel *hose,&t;&t;&bslash;&n;&t;int top_bus, int bus, int devfn, int offset, type value)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return pci_##rw##_config_##size(&t;&t;&t;&t;&bslash;&n;&t;&t;fake_pci_dev(hose, top_bus, bus, devfn),&t;&t;&bslash;&n;&t;&t;offset, value);&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|EARLY_PCI_OP
c_func
(paren
id|read
comma
id|byte
comma
id|u8
op_star
)paren
id|EARLY_PCI_OP
c_func
(paren
id|read
comma
id|word
comma
id|u16
op_star
)paren
id|EARLY_PCI_OP
c_func
(paren
id|read
comma
id|dword
comma
id|u32
op_star
)paren
id|EARLY_PCI_OP
c_func
(paren
id|write
comma
id|byte
comma
id|u8
)paren
id|EARLY_PCI_OP
c_func
(paren
id|write
comma
id|word
comma
id|u16
)paren
id|EARLY_PCI_OP
c_func
(paren
id|write
comma
id|dword
comma
id|u32
)paren
DECL|variable|io_resource_inuse
r_static
r_struct
id|resource
op_star
id|io_resource_inuse
suffix:semicolon
DECL|variable|mem_resource_inuse
r_static
r_struct
id|resource
op_star
id|mem_resource_inuse
suffix:semicolon
DECL|variable|pciauto_lower_iospc
r_static
id|u32
id|pciauto_lower_iospc
suffix:semicolon
DECL|variable|pciauto_upper_iospc
r_static
id|u32
id|pciauto_upper_iospc
suffix:semicolon
DECL|variable|pciauto_lower_memspc
r_static
id|u32
id|pciauto_lower_memspc
suffix:semicolon
DECL|variable|pciauto_upper_memspc
r_static
id|u32
id|pciauto_upper_memspc
suffix:semicolon
r_static
r_void
id|__init
DECL|function|pciauto_setup_bars
id|pciauto_setup_bars
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|bar_limit
)paren
(brace
id|u32
id|bar_response
comma
id|bar_size
comma
id|bar_value
suffix:semicolon
id|u32
id|bar
comma
id|addr_mask
comma
id|bar_nr
op_assign
l_int|0
suffix:semicolon
id|u32
op_star
id|upper_limit
suffix:semicolon
id|u32
op_star
id|lower_limit
suffix:semicolon
r_int
id|found_mem64
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|bar
op_assign
id|PCI_BASE_ADDRESS_0
suffix:semicolon
id|bar
op_le
id|bar_limit
suffix:semicolon
id|bar
op_add_assign
l_int|4
)paren
(brace
macro_line|#if !defined(CONFIG_SH_HS7751RVOIP) &amp;&amp; !defined(CONFIG_SH_RTS7751R2D)
id|u32
id|bar_addr
suffix:semicolon
multiline_comment|/* Read the old BAR value */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
op_amp
id|bar_addr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Tickle the BAR and get the response */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
op_amp
id|bar_response
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_SH_HS7751RVOIP) &amp;&amp; !defined(CONFIG_SH_RTS7751R2D)
multiline_comment|/* &n;&t;&t; * Write the old BAR value back out, only update the BAR&n;&t;&t; * if we implicitly want resources to be updated, which&n;&t;&t; * is done by the generic code further down. -- PFM.&n;&t;&t; */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
id|bar_addr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* If BAR is not implemented go to the next BAR */
r_if
c_cond
(paren
op_logical_neg
id|bar_response
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Workaround for a BAR that doesn&squot;t use its upper word,&n;&t;&t; * like the ALi 1535D+ PCI DC-97 Controller Modem (M5457).&n;&t;&t; * bdl &lt;brad@ltc.com&gt;&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bar_response
op_amp
l_int|0xffff0000
)paren
)paren
id|bar_response
op_or_assign
l_int|0xffff0000
suffix:semicolon
id|retry
suffix:colon
multiline_comment|/* Check the BAR type and set our address mask */
r_if
c_cond
(paren
id|bar_response
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
(brace
id|addr_mask
op_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|upper_limit
op_assign
op_amp
id|pciauto_upper_iospc
suffix:semicolon
id|lower_limit
op_assign
op_amp
id|pciauto_lower_iospc
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;        I/O&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|bar_response
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
op_eq
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
id|found_mem64
op_assign
l_int|1
suffix:semicolon
id|addr_mask
op_assign
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|upper_limit
op_assign
op_amp
id|pciauto_upper_memspc
suffix:semicolon
id|lower_limit
op_assign
op_amp
id|pciauto_lower_memspc
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;        Mem&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Calculate requested size */
id|bar_size
op_assign
op_complement
(paren
id|bar_response
op_amp
id|addr_mask
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Allocate a base address */
id|bar_value
op_assign
(paren
(paren
op_star
id|lower_limit
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|bar_size
op_minus
l_int|1
)paren
)paren
op_plus
id|bar_size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bar_value
op_plus
id|bar_size
)paren
OG
op_star
id|upper_limit
)paren
(brace
r_if
c_cond
(paren
id|bar_response
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
(brace
r_if
c_cond
(paren
id|io_resource_inuse-&gt;child
)paren
(brace
id|io_resource_inuse
op_assign
id|io_resource_inuse-&gt;child
suffix:semicolon
id|pciauto_lower_iospc
op_assign
id|io_resource_inuse-&gt;start
suffix:semicolon
id|pciauto_upper_iospc
op_assign
id|io_resource_inuse-&gt;end
op_plus
l_int|1
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|mem_resource_inuse-&gt;child
)paren
(brace
id|mem_resource_inuse
op_assign
id|mem_resource_inuse-&gt;child
suffix:semicolon
id|pciauto_lower_memspc
op_assign
id|mem_resource_inuse-&gt;start
suffix:semicolon
id|pciauto_upper_memspc
op_assign
id|mem_resource_inuse-&gt;end
op_plus
l_int|1
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
)brace
id|DBG
c_func
(paren
l_string|&quot; unavailable -- skipping, value %x size %x&bslash;n&quot;
comma
id|bar_value
comma
id|bar_size
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI_AUTO_UPDATE_RESOURCES
multiline_comment|/* Write it out and update our limit */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
id|bar_value
)paren
suffix:semicolon
macro_line|#endif
op_star
id|lower_limit
op_assign
id|bar_value
op_plus
id|bar_size
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we are a 64-bit decoder then increment to the&n;&t;&t; * upper 32 bits of the bar and force it to locate&n;&t;&t; * in the lower 4GB of memory.&n;&t;&t; */
r_if
c_cond
(paren
id|found_mem64
)paren
(brace
id|bar
op_add_assign
l_int|4
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
l_int|0x00000000
)paren
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot; at 0x%.8x [size=0x%x]&bslash;n&quot;
comma
id|bar_value
comma
id|bar_size
)paren
suffix:semicolon
id|bar_nr
op_increment
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|pciauto_prescan_setup_bridge
id|pciauto_prescan_setup_bridge
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
)paren
(brace
multiline_comment|/* Configure bus number registers */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PRIMARY_BUS
comma
id|current_bus
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SECONDARY_BUS
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Align memory and I/O to 1MB and 4KB boundaries. */
id|pciauto_lower_memspc
op_assign
(paren
id|pciauto_lower_memspc
op_plus
(paren
l_int|0x100000
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x100000
op_minus
l_int|1
)paren
suffix:semicolon
id|pciauto_lower_iospc
op_assign
(paren
id|pciauto_lower_iospc
op_plus
(paren
l_int|0x1000
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set base (lower limit) of address range behind bridge. */
id|early_write_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_MEMORY_BASE
comma
id|pciauto_lower_memspc
op_rshift
l_int|16
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_BASE
comma
(paren
id|pciauto_lower_iospc
op_amp
l_int|0x0000f000
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_BASE_UPPER16
comma
id|pciauto_lower_iospc
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t support prefetchable memory for now, so disable */
id|early_write_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PREF_MEMORY_BASE
comma
l_int|0
)paren
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PREF_MEMORY_LIMIT
comma
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pciauto_postscan_setup_bridge
id|pciauto_postscan_setup_bridge
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
)paren
(brace
id|u32
id|temp
suffix:semicolon
multiline_comment|/*&n;&t; * [jsun] we always bump up baselines a little, so that if there&n;&t; * nothing behind P2P bridge, we don&squot;t wind up overlapping IO/MEM&n;&t; * spaces.&n;&t; */
id|pciauto_lower_memspc
op_add_assign
l_int|1
suffix:semicolon
id|pciauto_lower_iospc
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* Configure bus number registers */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
id|sub_bus
)paren
suffix:semicolon
multiline_comment|/* Set upper limit of address range behind bridge. */
id|early_write_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_MEMORY_LIMIT
comma
id|pciauto_lower_memspc
op_rshift
l_int|16
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_LIMIT
comma
(paren
id|pciauto_lower_iospc
op_amp
l_int|0x0000f000
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_LIMIT_UPPER16
comma
id|pciauto_lower_iospc
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Align memory and I/O to 1MB and 4KB boundaries. */
id|pciauto_lower_memspc
op_assign
(paren
id|pciauto_lower_memspc
op_plus
(paren
l_int|0x100000
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x100000
op_minus
l_int|1
)paren
suffix:semicolon
id|pciauto_lower_iospc
op_assign
(paren
id|pciauto_lower_iospc
op_plus
(paren
l_int|0x1000
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Enable memory and I/O accesses, enable bus master */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|temp
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|temp
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pciauto_prescan_setup_cardbus_bridge
id|pciauto_prescan_setup_cardbus_bridge
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
)paren
(brace
multiline_comment|/* Configure bus number registers */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PRIMARY_BUS
comma
id|current_bus
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SECONDARY_BUS
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Align memory and I/O to 4KB and 4 byte boundaries. */
id|pciauto_lower_memspc
op_assign
(paren
id|pciauto_lower_memspc
op_plus
(paren
l_int|0x1000
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
id|pciauto_lower_iospc
op_assign
(paren
id|pciauto_lower_iospc
op_plus
(paren
l_int|0x4
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x4
op_minus
l_int|1
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CB_MEMORY_BASE_0
comma
id|pciauto_lower_memspc
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CB_IO_BASE_0
comma
id|pciauto_lower_iospc
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pciauto_postscan_setup_cardbus_bridge
id|pciauto_postscan_setup_cardbus_bridge
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
)paren
(brace
id|u32
id|temp
suffix:semicolon
macro_line|#if !defined(CONFIG_SH_HS7751RVOIP) &amp;&amp; !defined(CONFIG_SH_RTS7751R2D)
multiline_comment|/*&n;&t; * [jsun] we always bump up baselines a little, so that if there&n;&t; * nothing behind P2P bridge, we don&squot;t wind up overlapping IO/MEM&n;&t; * spaces.&n;&t; */
id|pciauto_lower_memspc
op_add_assign
l_int|1
suffix:semicolon
id|pciauto_lower_iospc
op_add_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Configure subordinate bus number.  The PCI subsystem&n;&t; * bus scan will renumber buses (reserving three additional&n;&t; * for this PCI&lt;-&gt;CardBus bridge for the case where a CardBus&n;&t; * adapter contains a P2P or CB2CB bridge.&n;&t; */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
id|sub_bus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reserve an additional 4MB for mem space and 16KB for&n;&t; * I/O space.  This should cover any additional space&n;&t; * requirement of unusual CardBus devices with&n;&t; * additional bridges that can consume more address space.&n;&t; *&n;&t; * Although pcmcia-cs currently will reprogram bridge&n;&t; * windows, the goal is to add an option to leave them&n;&t; * alone and use the bridge window ranges as the regions&n;&t; * that are searched for free resources upon hot-insertion&n;&t; * of a device.  This will allow a PCI&lt;-&gt;CardBus bridge&n;&t; * configured by this routine to happily live behind a&n;&t; * P2P bridge in a system.&n;&t; */
macro_line|#if defined(CONFIG_SH_HS7751RVOIP) || defined(CONFIG_SH_RTS7751R2D)
id|pciauto_lower_memspc
op_add_assign
l_int|0x00400000
suffix:semicolon
id|pciauto_lower_iospc
op_add_assign
l_int|0x00004000
suffix:semicolon
macro_line|#endif
multiline_comment|/* Align memory and I/O to 4KB and 4 byte boundaries. */
id|pciauto_lower_memspc
op_assign
(paren
id|pciauto_lower_memspc
op_plus
(paren
l_int|0x1000
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
id|pciauto_lower_iospc
op_assign
(paren
id|pciauto_lower_iospc
op_plus
(paren
l_int|0x4
op_minus
l_int|1
)paren
)paren
op_amp
op_complement
(paren
l_int|0x4
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Set up memory and I/O filter limits, assume 32-bit I/O space */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CB_MEMORY_LIMIT_0
comma
id|pciauto_lower_memspc
op_minus
l_int|1
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CB_IO_LIMIT_0
comma
id|pciauto_lower_iospc
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Enable memory and I/O accesses, enable bus master */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|temp
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|temp
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
)brace
DECL|macro|PCIAUTO_IDE_MODE_MASK
mdefine_line|#define&t;PCIAUTO_IDE_MODE_MASK&t;&t;0x05
r_static
r_int
id|__init
DECL|function|pciauto_bus_scan
id|pciauto_bus_scan
c_func
(paren
r_struct
id|pci_channel
op_star
id|hose
comma
r_int
id|top_bus
comma
r_int
id|current_bus
)paren
(brace
r_int
id|sub_bus
suffix:semicolon
id|u32
id|pci_devfn
comma
id|pci_class
comma
id|cmdstat
comma
id|found_multi
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|vid
comma
id|did
suffix:semicolon
r_int
r_char
id|header_type
suffix:semicolon
r_int
id|devfn_start
op_assign
l_int|0
suffix:semicolon
r_int
id|devfn_stop
op_assign
l_int|0xff
suffix:semicolon
id|sub_bus
op_assign
id|current_bus
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;first_devfn
)paren
id|devfn_start
op_assign
id|hose-&gt;first_devfn
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;last_devfn
)paren
id|devfn_stop
op_assign
id|hose-&gt;last_devfn
suffix:semicolon
r_for
c_loop
(paren
id|pci_devfn
op_assign
id|devfn_start
suffix:semicolon
id|pci_devfn
OL
id|devfn_stop
suffix:semicolon
id|pci_devfn
op_increment
)paren
(brace
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
op_logical_and
op_logical_neg
id|found_multi
)paren
r_continue
suffix:semicolon
id|early_read_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_VENDOR_ID
comma
op_amp
id|vid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vid
op_eq
l_int|0xffff
)paren
r_continue
suffix:semicolon
id|early_read_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|header_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
)paren
id|found_multi
op_assign
id|header_type
op_amp
l_int|0x80
suffix:semicolon
id|early_read_config_word
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_DEVICE_ID
comma
op_amp
id|did
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|pci_class
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%.2x:%.2x.%x Class %.4x: %.4x:%.4x&quot;
comma
id|current_bus
comma
id|PCI_SLOT
c_func
(paren
id|pci_devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
comma
id|pci_class
op_rshift
l_int|16
comma
id|vid
comma
id|did
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_class
op_amp
l_int|0xff
)paren
id|DBG
c_func
(paren
l_string|&quot; (rev %.2x)&quot;
comma
id|pci_class
op_amp
l_int|0xff
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_CLASS_BRIDGE_PCI
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;        Bridge: primary=%.2x, secondary=%.2x&bslash;n&quot;
comma
id|current_bus
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SH_HS7751RVOIP) || defined(CONFIG_SH_RTS7751R2D)
id|pciauto_setup_bars
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_1
)paren
suffix:semicolon
macro_line|#endif
id|pciauto_prescan_setup_bridge
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Scanning sub bus %.2x, I/O 0x%.8x, Mem 0x%.8x&bslash;n&quot;
comma
id|sub_bus
op_plus
l_int|1
comma
id|pciauto_lower_iospc
comma
id|pciauto_lower_memspc
)paren
suffix:semicolon
id|sub_bus
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|top_bus
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Back to bus %.2x&bslash;n&quot;
comma
id|current_bus
)paren
suffix:semicolon
id|pciauto_postscan_setup_bridge
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pci_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_CLASS_BRIDGE_CARDBUS
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;  CARDBUS  Bridge: primary=%.2x, secondary=%.2x&bslash;n&quot;
comma
id|current_bus
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: Found CardBus bridge, device %d function %d&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|pci_devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
)paren
suffix:semicolon
multiline_comment|/* Place CardBus Socket/ExCA registers */
id|pciauto_setup_bars
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_0
)paren
suffix:semicolon
id|pciauto_prescan_setup_cardbus_bridge
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Scanning sub bus %.2x, I/O 0x%.8x, Mem 0x%.8x&bslash;n&quot;
comma
id|sub_bus
op_plus
l_int|1
comma
id|pciauto_lower_iospc
comma
id|pciauto_lower_memspc
)paren
suffix:semicolon
id|sub_bus
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|top_bus
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Back to bus %.2x, sub_bus is %x&bslash;n&quot;
comma
id|current_bus
comma
id|sub_bus
)paren
suffix:semicolon
id|pciauto_postscan_setup_cardbus_bridge
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pci_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_CLASS_STORAGE_IDE
)paren
(brace
r_int
r_char
id|prg_iface
suffix:semicolon
id|early_read_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CLASS_PROG
comma
op_amp
id|prg_iface
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|prg_iface
op_amp
id|PCIAUTO_IDE_MODE_MASK
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Skipping legacy mode IDE controller&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Found a peripheral, enable some standard&n;&t;&t; * settings&n;&t;&t; */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmdstat
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|cmdstat
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_SH_HS7751RVOIP) &amp;&amp; !defined(CONFIG_SH_RTS7751R2D)
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x80
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Allocate PCI I/O and/or memory space */
id|pciauto_setup_bars
c_func
(paren
id|hose
comma
id|top_bus
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_5
)paren
suffix:semicolon
)brace
r_return
id|sub_bus
suffix:semicolon
)brace
r_int
id|__init
DECL|function|pciauto_assign_resources
id|pciauto_assign_resources
c_func
(paren
r_int
id|busno
comma
r_struct
id|pci_channel
op_star
id|hose
)paren
(brace
multiline_comment|/* setup resource limits */
id|io_resource_inuse
op_assign
id|hose-&gt;io_resource
suffix:semicolon
id|mem_resource_inuse
op_assign
id|hose-&gt;mem_resource
suffix:semicolon
id|pciauto_lower_iospc
op_assign
id|io_resource_inuse-&gt;start
suffix:semicolon
id|pciauto_upper_iospc
op_assign
id|io_resource_inuse-&gt;end
op_plus
l_int|1
suffix:semicolon
id|pciauto_lower_memspc
op_assign
id|mem_resource_inuse-&gt;start
suffix:semicolon
id|pciauto_upper_memspc
op_assign
id|mem_resource_inuse-&gt;end
op_plus
l_int|1
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Autoconfig PCI channel 0x%p&bslash;n&quot;
comma
id|hose
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Scanning bus %.2x, I/O 0x%.8x:0x%.8x, Mem 0x%.8x:0x%.8x&bslash;n&quot;
comma
id|busno
comma
id|pciauto_lower_iospc
comma
id|pciauto_upper_iospc
comma
id|pciauto_lower_memspc
comma
id|pciauto_upper_memspc
)paren
suffix:semicolon
r_return
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|busno
comma
id|busno
)paren
suffix:semicolon
)brace
eof
