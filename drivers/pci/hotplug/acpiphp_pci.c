multiline_comment|/*&n; * ACPI PCI HotPlug PCI configuration space management&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001,2002 IBM Corp.&n; * Copyright (C) 2002 Takayoshi Kochi (t-kochi@bq.jp.nec.com)&n; * Copyright (C) 2002 Hiroshi Aono (h-aono@ap.jp.nec.com)&n; * Copyright (C) 2002 NEC Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;t-kochi@bq.jp.nec.com&gt;&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;../pci.h&quot;
macro_line|#include &quot;pci_hotplug.h&quot;
macro_line|#include &quot;acpiphp.h&quot;
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;acpiphp_pci&quot;
multiline_comment|/* allocate mem/pmem/io resource to a new function */
DECL|function|init_config_space
r_static
r_int
id|init_config_space
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
(brace
id|u32
id|bar
comma
id|len
suffix:semicolon
id|u32
id|address
(braket
)braket
op_assign
(brace
id|PCI_BASE_ADDRESS_0
comma
id|PCI_BASE_ADDRESS_1
comma
id|PCI_BASE_ADDRESS_2
comma
id|PCI_BASE_ADDRESS_3
comma
id|PCI_BASE_ADDRESS_4
comma
id|PCI_BASE_ADDRESS_5
comma
l_int|0
)brace
suffix:semicolon
r_int
id|count
suffix:semicolon
r_struct
id|acpiphp_bridge
op_star
id|bridge
suffix:semicolon
r_struct
id|pci_resource
op_star
id|res
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pbus
suffix:semicolon
r_int
id|bus
comma
id|device
comma
id|function
suffix:semicolon
r_int
r_int
id|devfn
suffix:semicolon
id|u16
id|tmp
suffix:semicolon
id|bridge
op_assign
id|func-&gt;slot-&gt;bridge
suffix:semicolon
id|pbus
op_assign
id|bridge-&gt;pci_bus
suffix:semicolon
id|bus
op_assign
id|bridge-&gt;bus
suffix:semicolon
id|device
op_assign
id|func-&gt;slot-&gt;device
suffix:semicolon
id|function
op_assign
id|func-&gt;function
suffix:semicolon
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
id|device
comma
id|function
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|address
(braket
id|count
)braket
suffix:semicolon
id|count
op_increment
)paren
(brace
multiline_comment|/* for 6 BARs */
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|pci_bus_read_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
op_amp
id|bar
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bar
)paren
multiline_comment|/* This BAR is not implemented */
r_continue
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Device %02x.%02x BAR %d wants %x&bslash;n&quot;
comma
id|device
comma
id|function
comma
id|count
comma
id|bar
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bar
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
multiline_comment|/* This is IO */
id|len
op_assign
id|bar
op_amp
l_int|0xFFFFFFFC
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;len in IO %x, BAR %d&bslash;n&quot;
comma
id|len
comma
id|count
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_get_io_resource
c_func
(paren
op_amp
id|bridge-&gt;io_head
comma
id|len
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot allocate requested io for %02x:%02x.%d len %x&bslash;n&quot;
comma
id|bus
comma
id|device
comma
id|function
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
(paren
id|u32
)paren
id|res-&gt;base
)paren
suffix:semicolon
id|res-&gt;next
op_assign
id|func-&gt;io_head
suffix:semicolon
id|func-&gt;io_head
op_assign
id|res
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is Memory */
r_if
c_cond
(paren
id|bar
op_amp
id|PCI_BASE_ADDRESS_MEM_PREFETCH
)paren
(brace
multiline_comment|/* pfmem */
id|len
op_assign
id|bar
op_amp
l_int|0xFFFFFFF0
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;len in PFMEM %x, BAR %d&bslash;n&quot;
comma
id|len
comma
id|count
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_get_resource
c_func
(paren
op_amp
id|bridge-&gt;p_mem_head
comma
id|len
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot allocate requested pfmem for %02x:%02x.%d len %x&bslash;n&quot;
comma
id|bus
comma
id|device
comma
id|function
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
(paren
id|u32
)paren
id|res-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bar
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
multiline_comment|/* takes up another dword */
id|dbg
c_func
(paren
l_string|&quot;inside the pfmem 64 case, count %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
(paren
id|u32
)paren
(paren
id|res-&gt;base
op_rshift
l_int|32
)paren
)paren
suffix:semicolon
)brace
id|res-&gt;next
op_assign
id|func-&gt;p_mem_head
suffix:semicolon
id|func-&gt;p_mem_head
op_assign
id|res
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* regular memory */
id|len
op_assign
id|bar
op_amp
l_int|0xFFFFFFF0
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;len in MEM %x, BAR %d&bslash;n&quot;
comma
id|len
comma
id|count
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_get_resource
c_func
(paren
op_amp
id|bridge-&gt;mem_head
comma
id|len
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot allocate requested pfmem for %02x:%02x.%d len %x&bslash;n&quot;
comma
id|bus
comma
id|device
comma
id|function
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
(paren
id|u32
)paren
id|res-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bar
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
multiline_comment|/* takes up another dword */
id|dbg
c_func
(paren
l_string|&quot;inside mem 64 case, reg. mem, count %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|address
(braket
id|count
)braket
comma
(paren
id|u32
)paren
(paren
id|res-&gt;base
op_rshift
l_int|32
)paren
)paren
suffix:semicolon
)brace
id|res-&gt;next
op_assign
id|func-&gt;mem_head
suffix:semicolon
id|func-&gt;mem_head
op_assign
id|res
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* disable expansion rom */
id|pci_bus_write_config_dword
c_func
(paren
id|pbus
comma
id|devfn
comma
id|PCI_ROM_ADDRESS
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* set PCI parameters from _HPP */
id|pci_bus_write_config_byte
c_func
(paren
id|pbus
comma
id|devfn
comma
id|PCI_CACHE_LINE_SIZE
comma
id|bridge-&gt;hpp.cache_line_size
)paren
suffix:semicolon
id|pci_bus_write_config_byte
c_func
(paren
id|pbus
comma
id|devfn
comma
id|PCI_LATENCY_TIMER
comma
id|bridge-&gt;hpp.latency_timer
)paren
suffix:semicolon
id|pci_bus_read_config_word
c_func
(paren
id|pbus
comma
id|devfn
comma
id|PCI_COMMAND
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;hpp.enable_SERR
)paren
id|tmp
op_or_assign
id|PCI_COMMAND_SERR
suffix:semicolon
r_if
c_cond
(paren
id|bridge-&gt;hpp.enable_PERR
)paren
id|tmp
op_or_assign
id|PCI_COMMAND_PARITY
suffix:semicolon
id|pci_bus_write_config_word
c_func
(paren
id|pbus
comma
id|devfn
comma
id|PCI_COMMAND
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* detect_used_resource - subtract resource under dev from bridge */
DECL|function|detect_used_resource
r_static
r_int
id|detect_used_resource
(paren
r_struct
id|acpiphp_bridge
op_star
id|bridge
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|bar
comma
id|len
suffix:semicolon
id|u64
id|base
suffix:semicolon
id|u32
id|address
(braket
)braket
op_assign
(brace
id|PCI_BASE_ADDRESS_0
comma
id|PCI_BASE_ADDRESS_1
comma
id|PCI_BASE_ADDRESS_2
comma
id|PCI_BASE_ADDRESS_3
comma
id|PCI_BASE_ADDRESS_4
comma
id|PCI_BASE_ADDRESS_5
comma
l_int|0
)brace
suffix:semicolon
r_int
id|count
suffix:semicolon
r_struct
id|pci_resource
op_star
id|res
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|address
(braket
id|count
)braket
suffix:semicolon
id|count
op_increment
)paren
(brace
multiline_comment|/* for 6 BARs */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
op_amp
id|bar
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bar
)paren
multiline_comment|/* This BAR is not implemented */
r_continue
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
multiline_comment|/* This is IO */
id|base
op_assign
id|bar
op_amp
l_int|0xFFFFFFFC
suffix:semicolon
id|len
op_and_assign
l_int|0xFFFFFFFC
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;BAR[%d] %08x - %08x (IO)&bslash;n&quot;
comma
id|count
comma
(paren
id|u32
)paren
id|base
comma
(paren
id|u32
)paren
id|base
op_plus
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_get_resource_with_base
c_func
(paren
op_amp
id|bridge-&gt;io_head
comma
id|base
comma
id|len
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is Memory */
id|base
op_assign
id|bar
op_amp
l_int|0xFFFFFFF0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_MEM_PREFETCH
)paren
(brace
multiline_comment|/* pfmem */
id|len
op_and_assign
l_int|0xFFFFFFF0
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
multiline_comment|/* takes up another dword */
id|dbg
c_func
(paren
l_string|&quot;prefetch mem 64&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;BAR[%d] %08x - %08x (PMEM)&bslash;n&quot;
comma
id|count
comma
(paren
id|u32
)paren
id|base
comma
(paren
id|u32
)paren
id|base
op_plus
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_get_resource_with_base
c_func
(paren
op_amp
id|bridge-&gt;p_mem_head
comma
id|base
comma
id|len
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* regular memory */
id|len
op_and_assign
l_int|0xFFFFFFF0
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
multiline_comment|/* takes up another dword */
id|dbg
c_func
(paren
l_string|&quot;mem 64&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;BAR[%d] %08x - %08x (MEM)&bslash;n&quot;
comma
id|count
comma
(paren
id|u32
)paren
id|base
comma
(paren
id|u32
)paren
id|base
op_plus
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_get_resource_with_base
c_func
(paren
op_amp
id|bridge-&gt;mem_head
comma
id|base
comma
id|len
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
id|bar
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* detect_pci_resource_bus - subtract resource under pci_bus */
DECL|function|detect_used_resource_bus
r_static
r_void
id|detect_used_resource_bus
c_func
(paren
r_struct
id|acpiphp_bridge
op_star
id|bridge
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|list_for_each
(paren
id|l
comma
op_amp
id|bus-&gt;devices
)paren
(brace
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|l
)paren
suffix:semicolon
id|detect_used_resource
c_func
(paren
id|bridge
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* XXX recursive call */
r_if
c_cond
(paren
id|dev-&gt;subordinate
)paren
id|detect_used_resource_bus
c_func
(paren
id|bridge
comma
id|dev-&gt;subordinate
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * acpiphp_detect_pci_resource - detect resources under bridge&n; * @bridge: detect all resources already used under this bridge&n; *&n; * collect all resources already allocated for all devices under a bridge.&n; */
DECL|function|acpiphp_detect_pci_resource
r_int
id|acpiphp_detect_pci_resource
(paren
r_struct
id|acpiphp_bridge
op_star
id|bridge
)paren
(brace
id|detect_used_resource_bus
c_func
(paren
id|bridge
comma
id|bridge-&gt;pci_bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * acpiphp_init_slot_resource - gather resource usage information of a slot&n; * @slot: ACPI slot object to be checked, should have valid pci_dev member&n; *&n; * TBD: PCI-to-PCI bridge case&n; *      use pci_dev-&gt;resource[]&n; */
DECL|function|acpiphp_init_func_resource
r_int
id|acpiphp_init_func_resource
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
(brace
id|u64
id|base
suffix:semicolon
id|u32
id|bar
comma
id|len
suffix:semicolon
id|u32
id|address
(braket
)braket
op_assign
(brace
id|PCI_BASE_ADDRESS_0
comma
id|PCI_BASE_ADDRESS_1
comma
id|PCI_BASE_ADDRESS_2
comma
id|PCI_BASE_ADDRESS_3
comma
id|PCI_BASE_ADDRESS_4
comma
id|PCI_BASE_ADDRESS_5
comma
l_int|0
)brace
suffix:semicolon
r_int
id|count
suffix:semicolon
r_struct
id|pci_resource
op_star
id|res
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|func-&gt;pci_dev
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Hot-pluggable device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|address
(braket
id|count
)braket
suffix:semicolon
id|count
op_increment
)paren
(brace
multiline_comment|/* for 6 BARs */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
op_amp
id|bar
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bar
)paren
multiline_comment|/* This BAR is not implemented */
r_continue
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
(brace
multiline_comment|/* This is IO */
id|base
op_assign
id|bar
op_amp
l_int|0xFFFFFFFC
suffix:semicolon
id|len
op_and_assign
l_int|0xFFFFFFFC
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;BAR[%d] %08x - %08x (IO)&bslash;n&quot;
comma
id|count
comma
(paren
id|u32
)paren
id|base
comma
(paren
id|u32
)paren
id|base
op_plus
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_make_resource
c_func
(paren
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_goto
id|no_memory
suffix:semicolon
id|res-&gt;next
op_assign
id|func-&gt;io_head
suffix:semicolon
id|func-&gt;io_head
op_assign
id|res
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is Memory */
id|base
op_assign
id|bar
op_amp
l_int|0xFFFFFFF0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_MEM_PREFETCH
)paren
(brace
multiline_comment|/* pfmem */
id|len
op_and_assign
l_int|0xFFFFFFF0
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
multiline_comment|/* takes up another dword */
id|dbg
c_func
(paren
l_string|&quot;prefetch mem 64&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;BAR[%d] %08x - %08x (PMEM)&bslash;n&quot;
comma
id|count
comma
(paren
id|u32
)paren
id|base
comma
(paren
id|u32
)paren
id|base
op_plus
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_make_resource
c_func
(paren
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_goto
id|no_memory
suffix:semicolon
id|res-&gt;next
op_assign
id|func-&gt;p_mem_head
suffix:semicolon
id|func-&gt;p_mem_head
op_assign
id|res
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* regular memory */
id|len
op_and_assign
l_int|0xFFFFFFF0
suffix:semicolon
id|len
op_assign
op_complement
id|len
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
(brace
multiline_comment|/* takes up another dword */
id|dbg
c_func
(paren
l_string|&quot;mem 64&bslash;n&quot;
)paren
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;BAR[%d] %08x - %08x (MEM)&bslash;n&quot;
comma
id|count
comma
(paren
id|u32
)paren
id|base
comma
(paren
id|u32
)paren
id|base
op_plus
id|len
op_minus
l_int|1
)paren
suffix:semicolon
id|res
op_assign
id|acpiphp_make_resource
c_func
(paren
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_goto
id|no_memory
suffix:semicolon
id|res-&gt;next
op_assign
id|func-&gt;mem_head
suffix:semicolon
id|func-&gt;mem_head
op_assign
id|res
suffix:semicolon
)brace
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|address
(braket
id|count
)braket
comma
id|bar
)paren
suffix:semicolon
)brace
macro_line|#if 1
id|acpiphp_dump_func_resource
c_func
(paren
id|func
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|no_memory
suffix:colon
id|err
c_func
(paren
l_string|&quot;out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|acpiphp_free_resource
c_func
(paren
op_amp
id|func-&gt;io_head
)paren
suffix:semicolon
id|acpiphp_free_resource
c_func
(paren
op_amp
id|func-&gt;mem_head
)paren
suffix:semicolon
id|acpiphp_free_resource
c_func
(paren
op_amp
id|func-&gt;p_mem_head
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * acpiphp_configure_slot - allocate PCI resources&n; * @slot: slot to be configured&n; *&n; * initializes a PCI functions on a device inserted&n; * into the slot&n; *&n; */
DECL|function|acpiphp_configure_slot
r_int
id|acpiphp_configure_slot
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
(brace
r_struct
id|acpiphp_func
op_star
id|func
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|u8
id|hdr
suffix:semicolon
id|u32
id|dvid
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|is_multi
op_assign
l_int|0
suffix:semicolon
id|pci_bus_read_config_byte
c_func
(paren
id|slot-&gt;bridge-&gt;pci_bus
comma
id|PCI_DEVFN
c_func
(paren
id|slot-&gt;device
comma
l_int|0
)paren
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_amp
l_int|0x80
)paren
id|is_multi
op_assign
l_int|1
suffix:semicolon
id|list_for_each
(paren
id|l
comma
op_amp
id|slot-&gt;funcs
)paren
(brace
id|func
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|acpiphp_func
comma
id|sibling
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_multi
op_logical_or
id|func-&gt;function
op_eq
l_int|0
)paren
(brace
id|pci_bus_read_config_dword
c_func
(paren
id|slot-&gt;bridge-&gt;pci_bus
comma
id|PCI_DEVFN
c_func
(paren
id|slot-&gt;device
comma
id|func-&gt;function
)paren
comma
id|PCI_VENDOR_ID
comma
op_amp
id|dvid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dvid
op_ne
l_int|0xffffffff
)paren
(brace
id|retval
op_assign
id|init_config_space
c_func
(paren
id|func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * acpiphp_configure_function - configure PCI function&n; * @func: function to be configured&n; *&n; * initializes a PCI functions on a device inserted&n; * into the slot&n; *&n; */
DECL|function|acpiphp_configure_function
r_int
id|acpiphp_configure_function
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
(brace
multiline_comment|/* all handled by the pci core now */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * acpiphp_unconfigure_function - unconfigure PCI function&n; * @func: function to be unconfigured&n; *&n; */
DECL|function|acpiphp_unconfigure_function
r_int
id|acpiphp_unconfigure_function
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
(brace
r_struct
id|acpiphp_bridge
op_star
id|bridge
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if pci_dev is NULL, ignore it */
r_if
c_cond
(paren
op_logical_neg
id|func-&gt;pci_dev
)paren
r_goto
id|err_exit
suffix:semicolon
id|pci_remove_bus_device
c_func
(paren
id|func-&gt;pci_dev
)paren
suffix:semicolon
multiline_comment|/* free all resources */
id|bridge
op_assign
id|func-&gt;slot-&gt;bridge
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|acpiphp_move_resource
c_func
(paren
op_amp
id|func-&gt;io_head
comma
op_amp
id|bridge-&gt;io_head
)paren
suffix:semicolon
id|acpiphp_move_resource
c_func
(paren
op_amp
id|func-&gt;mem_head
comma
op_amp
id|bridge-&gt;mem_head
)paren
suffix:semicolon
id|acpiphp_move_resource
c_func
(paren
op_amp
id|func-&gt;p_mem_head
comma
op_amp
id|bridge-&gt;p_mem_head
)paren
suffix:semicolon
id|acpiphp_move_resource
c_func
(paren
op_amp
id|func-&gt;bus_head
comma
op_amp
id|bridge-&gt;bus_head
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|bridge-&gt;res_lock
)paren
suffix:semicolon
id|err_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
eof
