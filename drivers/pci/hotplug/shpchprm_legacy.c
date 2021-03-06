multiline_comment|/*&n; * SHPCHPRM Legacy: PHP Resource Manager for Non-ACPI/Legacy platform&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; * Copyright (C) 2003-2004 Intel Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;,&lt;dely.l.sy@intel.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_IA64
macro_line|#include &lt;asm/iosapic.h&gt;
macro_line|#endif
macro_line|#include &quot;shpchp.h&quot;
macro_line|#include &quot;shpchprm.h&quot;
macro_line|#include &quot;shpchprm_legacy.h&quot;
DECL|variable|shpchp_rom_start
r_static
r_void
id|__iomem
op_star
id|shpchp_rom_start
suffix:semicolon
DECL|variable|unused_IRQ
r_static
id|u16
id|unused_IRQ
suffix:semicolon
DECL|function|shpchprm_cleanup
r_void
id|shpchprm_cleanup
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|shpchp_rom_start
)paren
id|iounmap
c_func
(paren
id|shpchp_rom_start
)paren
suffix:semicolon
)brace
DECL|function|shpchprm_print_pirt
r_int
id|shpchprm_print_pirt
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shpchprm_get_physical_slot_number
r_int
id|shpchprm_get_physical_slot_number
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
id|u32
op_star
id|sun
comma
id|u8
id|busnum
comma
id|u8
id|devnum
)paren
(brace
r_int
id|offset
op_assign
id|devnum
op_minus
id|ctrl-&gt;slot_device_offset
suffix:semicolon
op_star
id|sun
op_assign
(paren
id|u8
)paren
(paren
id|ctrl-&gt;first_slot
op_plus
id|ctrl-&gt;slot_num_inc
op_star
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Find the Hot Plug Resource Table in the specified region of memory */
DECL|function|detect_HRT_floating_pointer
r_static
r_void
id|__iomem
op_star
id|detect_HRT_floating_pointer
c_func
(paren
r_void
id|__iomem
op_star
id|begin
comma
r_void
id|__iomem
op_star
id|end
)paren
(brace
r_void
id|__iomem
op_star
id|fp
suffix:semicolon
r_void
id|__iomem
op_star
id|endp
suffix:semicolon
id|u8
id|temp1
comma
id|temp2
comma
id|temp3
comma
id|temp4
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
id|endp
op_assign
(paren
id|end
op_minus
r_sizeof
(paren
r_struct
id|hrt
)paren
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|fp
op_assign
id|begin
suffix:semicolon
id|fp
op_le
id|endp
suffix:semicolon
id|fp
op_add_assign
l_int|16
)paren
(brace
id|temp1
op_assign
id|readb
c_func
(paren
id|fp
op_plus
id|SIG0
)paren
suffix:semicolon
id|temp2
op_assign
id|readb
c_func
(paren
id|fp
op_plus
id|SIG1
)paren
suffix:semicolon
id|temp3
op_assign
id|readb
c_func
(paren
id|fp
op_plus
id|SIG2
)paren
suffix:semicolon
id|temp4
op_assign
id|readb
c_func
(paren
id|fp
op_plus
id|SIG3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp1
op_eq
l_char|&squot;$&squot;
op_logical_and
id|temp2
op_eq
l_char|&squot;H&squot;
op_logical_and
id|temp3
op_eq
l_char|&squot;R&squot;
op_logical_and
id|temp4
op_eq
l_char|&squot;T&squot;
)paren
(brace
id|status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
id|fp
op_assign
l_int|NULL
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Discovered Hotplug Resource Table at %p&bslash;n&quot;
comma
id|fp
)paren
suffix:semicolon
r_return
id|fp
suffix:semicolon
)brace
multiline_comment|/*&n; * shpchprm_find_available_resources&n; *&n; *  Finds available memory, IO, and IRQ resources for programming&n; *  devices which may be added to the system&n; *  this function is for hot plug ADD!&n; *&n; * returns 0 if success&n; */
DECL|function|shpchprm_find_available_resources
r_int
id|shpchprm_find_available_resources
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
id|u8
id|populated_slot
suffix:semicolon
id|u8
id|bridged_slot
suffix:semicolon
r_void
id|__iomem
op_star
id|one_slot
suffix:semicolon
r_struct
id|pci_func
op_star
id|func
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|10
comma
id|index
op_assign
l_int|0
suffix:semicolon
id|u32
id|temp_dword
comma
id|rc
suffix:semicolon
id|ulong
id|temp_ulong
suffix:semicolon
r_struct
id|pci_resource
op_star
id|mem_node
suffix:semicolon
r_struct
id|pci_resource
op_star
id|p_mem_node
suffix:semicolon
r_struct
id|pci_resource
op_star
id|io_node
suffix:semicolon
r_struct
id|pci_resource
op_star
id|bus_node
suffix:semicolon
r_void
id|__iomem
op_star
id|rom_resource_table
suffix:semicolon
r_struct
id|pci_bus
id|lpci_bus
comma
op_star
id|pci_bus
suffix:semicolon
id|u8
id|cfgspc_irq
comma
id|temp
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|lpci_bus
comma
id|ctrl-&gt;pci_bus
comma
r_sizeof
(paren
id|lpci_bus
)paren
)paren
suffix:semicolon
id|pci_bus
op_assign
op_amp
id|lpci_bus
suffix:semicolon
id|rom_resource_table
op_assign
id|detect_HRT_floating_pointer
c_func
(paren
id|shpchp_rom_start
comma
id|shpchp_rom_start
op_plus
l_int|0xffff
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;rom_resource_table = %p&bslash;n&quot;
comma
id|rom_resource_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rom_resource_table
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Sum all resources and setup resource maps */
id|unused_IRQ
op_assign
id|readl
c_func
(paren
id|rom_resource_table
op_plus
id|UNUSED_IRQ
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;unused_IRQ = %x&bslash;n&quot;
comma
id|unused_IRQ
)paren
suffix:semicolon
id|temp
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|unused_IRQ
)paren
(brace
r_if
c_cond
(paren
id|unused_IRQ
op_amp
l_int|1
)paren
(brace
id|shpchp_disk_irq
op_assign
id|temp
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unused_IRQ
op_assign
id|unused_IRQ
op_rshift
l_int|1
suffix:semicolon
id|temp
op_increment
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;shpchp_disk_irq= %d&bslash;n&quot;
comma
id|shpchp_disk_irq
)paren
suffix:semicolon
id|unused_IRQ
op_assign
id|unused_IRQ
op_rshift
l_int|1
suffix:semicolon
id|temp
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|unused_IRQ
)paren
(brace
r_if
c_cond
(paren
id|unused_IRQ
op_amp
l_int|1
)paren
(brace
id|shpchp_nic_irq
op_assign
id|temp
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unused_IRQ
op_assign
id|unused_IRQ
op_rshift
l_int|1
suffix:semicolon
id|temp
op_increment
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;shpchp_nic_irq= %d&bslash;n&quot;
comma
id|shpchp_nic_irq
)paren
suffix:semicolon
id|unused_IRQ
op_assign
id|readl
c_func
(paren
id|rom_resource_table
op_plus
id|PCIIRQ
)paren
suffix:semicolon
id|temp
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|ctrl-&gt;pci_dev
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|cfgspc_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shpchp_nic_irq
)paren
(brace
id|shpchp_nic_irq
op_assign
id|cfgspc_irq
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|shpchp_disk_irq
)paren
(brace
id|shpchp_disk_irq
op_assign
id|cfgspc_irq
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;shpchp_disk_irq, shpchp_nic_irq= %d, %d&bslash;n&quot;
comma
id|shpchp_disk_irq
comma
id|shpchp_nic_irq
)paren
suffix:semicolon
id|one_slot
op_assign
id|rom_resource_table
op_plus
r_sizeof
(paren
r_struct
id|hrt
)paren
suffix:semicolon
id|i
op_assign
id|readb
c_func
(paren
id|rom_resource_table
op_plus
id|NUMBER_OF_ENTRIES
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;number_of_entries = %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|readb
c_func
(paren
id|one_slot
op_plus
id|SECONDARY_BUS
)paren
)paren
r_return
(paren
l_int|1
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;dev|IO base|length|MEMbase|length|PM base|length|PB SB MB&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_logical_and
id|readb
c_func
(paren
id|one_slot
op_plus
id|SECONDARY_BUS
)paren
)paren
(brace
id|u8
id|dev_func
op_assign
id|readb
c_func
(paren
id|one_slot
op_plus
id|DEV_FUNC
)paren
suffix:semicolon
id|u8
id|primary_bus
op_assign
id|readb
c_func
(paren
id|one_slot
op_plus
id|PRIMARY_BUS
)paren
suffix:semicolon
id|u8
id|secondary_bus
op_assign
id|readb
c_func
(paren
id|one_slot
op_plus
id|SECONDARY_BUS
)paren
suffix:semicolon
id|u8
id|max_bus
op_assign
id|readb
c_func
(paren
id|one_slot
op_plus
id|MAX_BUS
)paren
suffix:semicolon
id|u16
id|io_base
op_assign
id|readw
c_func
(paren
id|one_slot
op_plus
id|IO_BASE
)paren
suffix:semicolon
id|u16
id|io_length
op_assign
id|readw
c_func
(paren
id|one_slot
op_plus
id|IO_LENGTH
)paren
suffix:semicolon
id|u16
id|mem_base
op_assign
id|readw
c_func
(paren
id|one_slot
op_plus
id|MEM_BASE
)paren
suffix:semicolon
id|u16
id|mem_length
op_assign
id|readw
c_func
(paren
id|one_slot
op_plus
id|MEM_LENGTH
)paren
suffix:semicolon
id|u16
id|pre_mem_base
op_assign
id|readw
c_func
(paren
id|one_slot
op_plus
id|PRE_MEM_BASE
)paren
suffix:semicolon
id|u16
id|pre_mem_length
op_assign
id|readw
c_func
(paren
id|one_slot
op_plus
id|PRE_MEM_LENGTH
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%2.2x |  %4.4x | %4.4x |  %4.4x | %4.4x |  %4.4x | %4.4x |%2.2x %2.2x %2.2x&bslash;n&quot;
comma
id|dev_func
comma
id|io_base
comma
id|io_length
comma
id|mem_base
comma
id|mem_length
comma
id|pre_mem_base
comma
id|pre_mem_length
comma
id|primary_bus
comma
id|secondary_bus
comma
id|max_bus
)paren
suffix:semicolon
multiline_comment|/* If this entry isn&squot;t for our controller&squot;s bus, ignore it */
r_if
c_cond
(paren
id|primary_bus
op_ne
id|ctrl-&gt;slot_bus
)paren
(brace
id|i
op_decrement
suffix:semicolon
id|one_slot
op_add_assign
r_sizeof
(paren
r_struct
id|slot_rt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* find out if this entry is for an occupied slot */
id|temp_dword
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|pci_bus-&gt;number
op_assign
id|primary_bus
suffix:semicolon
id|pci_bus_read_config_dword
c_func
(paren
id|pci_bus
comma
id|dev_func
comma
id|PCI_VENDOR_ID
comma
op_amp
id|temp_dword
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;temp_D_word = %x&bslash;n&quot;
comma
id|temp_dword
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp_dword
op_ne
l_int|0xFFFFFFFF
)paren
(brace
id|index
op_assign
l_int|0
suffix:semicolon
id|func
op_assign
id|shpchp_slot_find
c_func
(paren
id|primary_bus
comma
id|dev_func
op_rshift
l_int|3
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|func
op_logical_and
(paren
id|func-&gt;function
op_ne
(paren
id|dev_func
op_amp
l_int|0x07
)paren
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;func = %p b:d:f(%x:%x:%x)&bslash;n&quot;
comma
id|func
comma
id|primary_bus
comma
id|dev_func
op_rshift
l_int|3
comma
id|index
)paren
suffix:semicolon
id|func
op_assign
id|shpchp_slot_find
c_func
(paren
id|primary_bus
comma
id|dev_func
op_rshift
l_int|3
comma
id|index
op_increment
)paren
suffix:semicolon
)brace
multiline_comment|/* If we can&squot;t find a match, skip this table entry */
r_if
c_cond
(paren
op_logical_neg
id|func
)paren
(brace
id|i
op_decrement
suffix:semicolon
id|one_slot
op_add_assign
r_sizeof
(paren
r_struct
id|slot_rt
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* this may not work and shouldn&squot;t be used */
r_if
c_cond
(paren
id|secondary_bus
op_ne
id|primary_bus
)paren
id|bridged_slot
op_assign
l_int|1
suffix:semicolon
r_else
id|bridged_slot
op_assign
l_int|0
suffix:semicolon
id|populated_slot
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|populated_slot
op_assign
l_int|0
suffix:semicolon
id|bridged_slot
op_assign
l_int|0
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;slot populated =%s &bslash;n&quot;
comma
id|populated_slot
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
multiline_comment|/* If we&squot;ve got a valid IO base, use it */
id|temp_ulong
op_assign
id|io_base
op_plus
id|io_length
suffix:semicolon
r_if
c_cond
(paren
(paren
id|io_base
)paren
op_logical_and
(paren
id|temp_ulong
op_le
l_int|0x10000
)paren
)paren
(brace
id|io_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io_node
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|io_node-&gt;base
op_assign
(paren
id|ulong
)paren
id|io_base
suffix:semicolon
id|io_node-&gt;length
op_assign
(paren
id|ulong
)paren
id|io_length
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;found io_node(base, length) = %x, %x&bslash;n&quot;
comma
id|io_node-&gt;base
comma
id|io_node-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|populated_slot
)paren
(brace
id|io_node-&gt;next
op_assign
id|ctrl-&gt;io_head
suffix:semicolon
id|ctrl-&gt;io_head
op_assign
id|io_node
suffix:semicolon
)brace
r_else
(brace
id|io_node-&gt;next
op_assign
id|func-&gt;io_head
suffix:semicolon
id|func-&gt;io_head
op_assign
id|io_node
suffix:semicolon
)brace
)brace
multiline_comment|/* If we&squot;ve got a valid memory base, use it */
id|temp_ulong
op_assign
id|mem_base
op_plus
id|mem_length
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mem_base
)paren
op_logical_and
(paren
id|temp_ulong
op_le
l_int|0x10000
)paren
)paren
(brace
id|mem_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_node
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mem_node-&gt;base
op_assign
(paren
id|ulong
)paren
id|mem_base
op_lshift
l_int|16
suffix:semicolon
id|mem_node-&gt;length
op_assign
(paren
id|ulong
)paren
(paren
id|mem_length
op_lshift
l_int|16
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;found mem_node(base, length) = %x, %x&bslash;n&quot;
comma
id|mem_node-&gt;base
comma
id|mem_node-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|populated_slot
)paren
(brace
id|mem_node-&gt;next
op_assign
id|ctrl-&gt;mem_head
suffix:semicolon
id|ctrl-&gt;mem_head
op_assign
id|mem_node
suffix:semicolon
)brace
r_else
(brace
id|mem_node-&gt;next
op_assign
id|func-&gt;mem_head
suffix:semicolon
id|func-&gt;mem_head
op_assign
id|mem_node
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * If we&squot;ve got a valid prefetchable memory base, and&n;&t;&t; * the base + length isn&squot;t greater than 0xFFFF&n;&t;&t; */
id|temp_ulong
op_assign
id|pre_mem_base
op_plus
id|pre_mem_length
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pre_mem_base
)paren
op_logical_and
(paren
id|temp_ulong
op_le
l_int|0x10000
)paren
)paren
(brace
id|p_mem_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p_mem_node
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|p_mem_node-&gt;base
op_assign
(paren
id|ulong
)paren
id|pre_mem_base
op_lshift
l_int|16
suffix:semicolon
id|p_mem_node-&gt;length
op_assign
(paren
id|ulong
)paren
id|pre_mem_length
op_lshift
l_int|16
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;found p_mem_node(base, length) = %x, %x&bslash;n&quot;
comma
id|p_mem_node-&gt;base
comma
id|p_mem_node-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|populated_slot
)paren
(brace
id|p_mem_node-&gt;next
op_assign
id|ctrl-&gt;p_mem_head
suffix:semicolon
id|ctrl-&gt;p_mem_head
op_assign
id|p_mem_node
suffix:semicolon
)brace
r_else
(brace
id|p_mem_node-&gt;next
op_assign
id|func-&gt;p_mem_head
suffix:semicolon
id|func-&gt;p_mem_head
op_assign
id|p_mem_node
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * If we&squot;ve got a valid bus number, use it&n;&t;&t; * The second condition is to ignore bus numbers on&n;&t;&t; * populated slots that don&squot;t have PCI-PCI bridges&n;&t;&t; */
r_if
c_cond
(paren
id|secondary_bus
op_logical_and
(paren
id|secondary_bus
op_ne
id|primary_bus
)paren
)paren
(brace
id|bus_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus_node
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|bus_node-&gt;base
op_assign
(paren
id|ulong
)paren
id|secondary_bus
suffix:semicolon
id|bus_node-&gt;length
op_assign
(paren
id|ulong
)paren
(paren
id|max_bus
op_minus
id|secondary_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;found bus_node(base, length) = %x, %x&bslash;n&quot;
comma
id|bus_node-&gt;base
comma
id|bus_node-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|populated_slot
)paren
(brace
id|bus_node-&gt;next
op_assign
id|ctrl-&gt;bus_head
suffix:semicolon
id|ctrl-&gt;bus_head
op_assign
id|bus_node
suffix:semicolon
)brace
r_else
(brace
id|bus_node-&gt;next
op_assign
id|func-&gt;bus_head
suffix:semicolon
id|func-&gt;bus_head
op_assign
id|bus_node
suffix:semicolon
)brace
)brace
id|i
op_decrement
suffix:semicolon
id|one_slot
op_add_assign
r_sizeof
(paren
r_struct
id|slot_rt
)paren
suffix:semicolon
)brace
multiline_comment|/* If all of the following fail, we don&squot;t have any resources for hot plug add */
id|rc
op_assign
l_int|1
suffix:semicolon
id|rc
op_and_assign
id|shpchp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;mem_head
)paren
)paren
suffix:semicolon
id|rc
op_and_assign
id|shpchp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;p_mem_head
)paren
)paren
suffix:semicolon
id|rc
op_and_assign
id|shpchp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;io_head
)paren
)paren
suffix:semicolon
id|rc
op_and_assign
id|shpchp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;bus_head
)paren
)paren
suffix:semicolon
r_return
(paren
id|rc
)paren
suffix:semicolon
)brace
DECL|function|shpchprm_set_hpp
r_int
id|shpchprm_set_hpp
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_struct
id|pci_func
op_star
id|func
comma
id|u8
id|card_type
)paren
(brace
id|u32
id|rc
suffix:semicolon
id|u8
id|temp_byte
suffix:semicolon
r_struct
id|pci_bus
id|lpci_bus
comma
op_star
id|pci_bus
suffix:semicolon
r_int
r_int
id|devfn
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|lpci_bus
comma
id|ctrl-&gt;pci_bus
comma
r_sizeof
(paren
id|lpci_bus
)paren
)paren
suffix:semicolon
id|pci_bus
op_assign
op_amp
id|lpci_bus
suffix:semicolon
id|pci_bus-&gt;number
op_assign
id|func-&gt;bus
suffix:semicolon
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
id|func-&gt;device
comma
id|func-&gt;function
)paren
suffix:semicolon
id|temp_byte
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* hard coded value for LT */
r_if
c_cond
(paren
id|card_type
op_eq
id|PCI_HEADER_TYPE_BRIDGE
)paren
(brace
multiline_comment|/* set subordinate Latency Timer */
id|rc
op_assign
id|pci_bus_write_config_byte
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_SEC_LATENCY_TIMER
comma
id|temp_byte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: set secondary LT error. b:d:f(%02x:%02x:%02x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|func-&gt;bus
comma
id|func-&gt;device
comma
id|func-&gt;function
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
)brace
multiline_comment|/* set base Latency Timer */
id|rc
op_assign
id|pci_bus_write_config_byte
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_LATENCY_TIMER
comma
id|temp_byte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: set LT error. b:d:f(%02x:%02x:%02x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|func-&gt;bus
comma
id|func-&gt;device
comma
id|func-&gt;function
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* set Cache Line size */
id|temp_byte
op_assign
l_int|0x08
suffix:semicolon
multiline_comment|/* hard coded value for CLS */
id|rc
op_assign
id|pci_bus_write_config_byte
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_CACHE_LINE_SIZE
comma
id|temp_byte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: set CLS error. b:d:f(%02x:%02x:%02x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|func-&gt;bus
comma
id|func-&gt;device
comma
id|func-&gt;function
)paren
suffix:semicolon
)brace
multiline_comment|/* set enable_perr */
multiline_comment|/* set enable_serr */
r_return
id|rc
suffix:semicolon
)brace
DECL|function|shpchprm_enable_card
r_void
id|shpchprm_enable_card
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
comma
r_struct
id|pci_func
op_star
id|func
comma
id|u8
id|card_type
)paren
(brace
id|u16
id|command
comma
id|bcommand
suffix:semicolon
r_struct
id|pci_bus
id|lpci_bus
comma
op_star
id|pci_bus
suffix:semicolon
r_int
r_int
id|devfn
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|lpci_bus
comma
id|ctrl-&gt;pci_bus
comma
r_sizeof
(paren
id|lpci_bus
)paren
)paren
suffix:semicolon
id|pci_bus
op_assign
op_amp
id|lpci_bus
suffix:semicolon
id|pci_bus-&gt;number
op_assign
id|func-&gt;bus
suffix:semicolon
id|devfn
op_assign
id|PCI_DEVFN
c_func
(paren
id|func-&gt;device
comma
id|func-&gt;function
)paren
suffix:semicolon
id|rc
op_assign
id|pci_bus_read_config_word
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
id|command
op_or_assign
id|PCI_COMMAND_PARITY
op_or
id|PCI_COMMAND_SERR
op_or
id|PCI_COMMAND_MASTER
op_or
id|PCI_COMMAND_INVALIDATE
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
suffix:semicolon
id|rc
op_assign
id|pci_bus_write_config_word
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_COMMAND
comma
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card_type
op_eq
id|PCI_HEADER_TYPE_BRIDGE
)paren
(brace
id|rc
op_assign
id|pci_bus_read_config_word
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_BRIDGE_CONTROL
comma
op_amp
id|bcommand
)paren
suffix:semicolon
id|bcommand
op_or_assign
id|PCI_BRIDGE_CTL_PARITY
op_or
id|PCI_BRIDGE_CTL_SERR
op_or
id|PCI_BRIDGE_CTL_NO_ISA
suffix:semicolon
id|rc
op_assign
id|pci_bus_write_config_word
c_func
(paren
id|pci_bus
comma
id|devfn
comma
id|PCI_BRIDGE_CONTROL
comma
id|bcommand
)paren
suffix:semicolon
)brace
)brace
DECL|function|legacy_shpchprm_init_pci
r_static
r_int
id|legacy_shpchprm_init_pci
c_func
(paren
r_void
)paren
(brace
id|shpchp_rom_start
op_assign
id|ioremap
c_func
(paren
id|ROM_PHY_ADDR
comma
id|ROM_PHY_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shpchp_rom_start
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Could not ioremap memory region for ROM&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shpchprm_init
r_int
id|shpchprm_init
c_func
(paren
r_enum
id|php_ctlr_type
id|ctrl_type
)paren
(brace
r_int
id|retval
suffix:semicolon
r_switch
c_cond
(paren
id|ctrl_type
)paren
(brace
r_case
id|PCI
suffix:colon
id|retval
op_assign
id|legacy_shpchprm_init_pci
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
