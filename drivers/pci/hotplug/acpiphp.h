multiline_comment|/*&n; * ACPI PCI Hot Plug Controller Driver&n; *&n; * Copyright (c) 1995,2001 Compaq Computer Corporation&n; * Copyright (c) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (c) 2001 IBM Corp.&n; * Copyright (c) 2002 Hiroshi Aono (h-aono@ap.jp.nec.com)&n; * Copyright (c) 2002 Takayoshi Kochi (t-kouchi@cq.jp.nec.com)&n; * Copyright (c) 2002 NEC Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;gregkh@us.ibm.com&gt;,&n; *&t;&t;    &lt;h-aono@ap.jp.nec.com&gt;,&n; *&t;&t;    &lt;t-kouchi@cq.jp.nec.com&gt;&n; *&n; */
macro_line|#ifndef _ACPIPHP_H
DECL|macro|_ACPIPHP_H
mdefine_line|#define _ACPIPHP_H
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;pci_hotplug.h&quot;
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (acpiphp_debug)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_DEBUG &quot;%s: &quot; format,&t;&bslash;&n;&t;&t;&t;&t;MY_NAME , ## arg); &t;&t;&bslash;&n;&t;} while (0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|SLOT_MAGIC
mdefine_line|#define SLOT_MAGIC&t;0x67267322
multiline_comment|/* name size which is used for entries in pcihpfs */
DECL|macro|SLOT_NAME_SIZE
mdefine_line|#define SLOT_NAME_SIZE&t;32&t;&t;/* ACPI{_SUN}-{BUS}:{DEV} */
r_struct
id|acpiphp_bridge
suffix:semicolon
r_struct
id|acpiphp_slot
suffix:semicolon
r_struct
id|pci_resource
suffix:semicolon
multiline_comment|/*&n; * struct slot - slot information for each *physical* slot&n; */
DECL|struct|slot
r_struct
id|slot
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|number
id|u8
id|number
suffix:semicolon
DECL|member|hotplug_slot
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
suffix:semicolon
DECL|member|slot_list
r_struct
id|list_head
id|slot_list
suffix:semicolon
DECL|member|acpi_slot
r_struct
id|acpiphp_slot
op_star
id|acpi_slot
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct pci_resource - describes pci resource (mem, pfmem, io, bus)&n; */
DECL|struct|pci_resource
r_struct
id|pci_resource
(brace
DECL|member|next
r_struct
id|pci_resource
op_star
id|next
suffix:semicolon
DECL|member|base
id|u64
id|base
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct hpp_param - ACPI 2.0 _HPP Hot Plug Parameters&n; * @cache_line_size in DWORD&n; * @latency_timer in PCI clock&n; * @enable_SERR 0 or 1&n; * @enable_PERR 0 or 1&n; */
DECL|struct|hpp_param
r_struct
id|hpp_param
(brace
DECL|member|cache_line_size
id|u8
id|cache_line_size
suffix:semicolon
DECL|member|latency_timer
id|u8
id|latency_timer
suffix:semicolon
DECL|member|enable_SERR
id|u8
id|enable_SERR
suffix:semicolon
DECL|member|enable_PERR
id|u8
id|enable_PERR
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct acpiphp_bridge - PCI bridge information&n; *&n; * for each bridge device in ACPI namespace&n; */
DECL|struct|acpiphp_bridge
r_struct
id|acpiphp_bridge
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|slots
r_struct
id|acpiphp_slot
op_star
id|slots
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|nr_slots
r_int
id|nr_slots
suffix:semicolon
DECL|member|seg
id|u8
id|seg
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|sub
id|u8
id|sub
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* This bus (host bridge) or Secondary bus (PCI-to-PCI bridge) */
DECL|member|pci_bus
r_struct
id|pci_bus
op_star
id|pci_bus
suffix:semicolon
multiline_comment|/* PCI-to-PCI bridge device */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* ACPI 2.0 _HPP parameters */
DECL|member|hpp
r_struct
id|hpp_param
id|hpp
suffix:semicolon
DECL|member|res_lock
id|spinlock_t
id|res_lock
suffix:semicolon
multiline_comment|/* available resources on this bus */
DECL|member|mem_head
r_struct
id|pci_resource
op_star
id|mem_head
suffix:semicolon
DECL|member|p_mem_head
r_struct
id|pci_resource
op_star
id|p_mem_head
suffix:semicolon
DECL|member|io_head
r_struct
id|pci_resource
op_star
id|io_head
suffix:semicolon
DECL|member|bus_head
r_struct
id|pci_resource
op_star
id|bus_head
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct acpiphp_slot - PCI slot information&n; *&n; * PCI slot information for each *physical* PCI slot&n; */
DECL|struct|acpiphp_slot
r_struct
id|acpiphp_slot
(brace
DECL|member|next
r_struct
id|acpiphp_slot
op_star
id|next
suffix:semicolon
DECL|member|bridge
r_struct
id|acpiphp_bridge
op_star
id|bridge
suffix:semicolon
multiline_comment|/* parent */
DECL|member|funcs
r_struct
id|list_head
id|funcs
suffix:semicolon
multiline_comment|/* one slot may have different&n;&t;&t;&t;&t;&t;   objects (i.e. for each function) */
DECL|member|crit_sect
r_struct
id|semaphore
id|crit_sect
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
multiline_comment|/* slot id (serial #) for hotplug core */
DECL|member|device
id|u8
id|device
suffix:semicolon
multiline_comment|/* pci device# */
DECL|member|sun
id|u32
id|sun
suffix:semicolon
multiline_comment|/* ACPI _SUN (slot unique number) */
DECL|member|slotno
id|u32
id|slotno
suffix:semicolon
multiline_comment|/* slot number relative to bridge */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* see below */
)brace
suffix:semicolon
multiline_comment|/**&n; * struct acpiphp_func - PCI function information&n; *&n; * PCI function information for each object in ACPI namespace&n; * typically 8 objects per slot (i.e. for each PCI function)&n; */
DECL|struct|acpiphp_func
r_struct
id|acpiphp_func
(brace
DECL|member|slot
r_struct
id|acpiphp_slot
op_star
id|slot
suffix:semicolon
multiline_comment|/* parent */
DECL|member|sibling
r_struct
id|list_head
id|sibling
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|function
id|u8
id|function
suffix:semicolon
multiline_comment|/* pci function# */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* see below */
multiline_comment|/* resources used for this function */
DECL|member|mem_head
r_struct
id|pci_resource
op_star
id|mem_head
suffix:semicolon
DECL|member|p_mem_head
r_struct
id|pci_resource
op_star
id|p_mem_head
suffix:semicolon
DECL|member|io_head
r_struct
id|pci_resource
op_star
id|io_head
suffix:semicolon
DECL|member|bus_head
r_struct
id|pci_resource
op_star
id|bus_head
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* PCI bus bridge HID */
DECL|macro|ACPI_PCI_HOST_HID
mdefine_line|#define ACPI_PCI_HOST_HID&t;&t;&quot;PNP0A03&quot;
multiline_comment|/* PCI BRIDGE type */
DECL|macro|BRIDGE_TYPE_HOST
mdefine_line|#define BRIDGE_TYPE_HOST&t;&t;0
DECL|macro|BRIDGE_TYPE_P2P
mdefine_line|#define BRIDGE_TYPE_P2P&t;&t;&t;1
multiline_comment|/* ACPI _STA method value (ignore bit 4; battery present) */
DECL|macro|ACPI_STA_PRESENT
mdefine_line|#define ACPI_STA_PRESENT&t;&t;(0x00000001)
DECL|macro|ACPI_STA_ENABLED
mdefine_line|#define ACPI_STA_ENABLED&t;&t;(0x00000002)
DECL|macro|ACPI_STA_SHOW_IN_UI
mdefine_line|#define ACPI_STA_SHOW_IN_UI&t;&t;(0x00000004)
DECL|macro|ACPI_STA_FUNCTIONING
mdefine_line|#define ACPI_STA_FUNCTIONING&t;&t;(0x00000008)
DECL|macro|ACPI_STA_ALL
mdefine_line|#define ACPI_STA_ALL&t;&t;&t;(0x0000000f)
multiline_comment|/* bridge flags */
DECL|macro|BRIDGE_HAS_STA
mdefine_line|#define BRIDGE_HAS_STA&t;&t;(0x00000001)
DECL|macro|BRIDGE_HAS_EJ0
mdefine_line|#define BRIDGE_HAS_EJ0&t;&t;(0x00000002)
DECL|macro|BRIDGE_HAS_HPP
mdefine_line|#define BRIDGE_HAS_HPP&t;&t;(0x00000004)
DECL|macro|BRIDGE_HAS_PS0
mdefine_line|#define BRIDGE_HAS_PS0&t;&t;(0x00000010)
DECL|macro|BRIDGE_HAS_PS1
mdefine_line|#define BRIDGE_HAS_PS1&t;&t;(0x00000020)
DECL|macro|BRIDGE_HAS_PS2
mdefine_line|#define BRIDGE_HAS_PS2&t;&t;(0x00000040)
DECL|macro|BRIDGE_HAS_PS3
mdefine_line|#define BRIDGE_HAS_PS3&t;&t;(0x00000080)
multiline_comment|/* slot flags */
DECL|macro|SLOT_POWEREDON
mdefine_line|#define SLOT_POWEREDON&t;&t;(0x00000001)
DECL|macro|SLOT_ENABLED
mdefine_line|#define SLOT_ENABLED&t;&t;(0x00000002)
DECL|macro|SLOT_MULTIFUNCTION
mdefine_line|#define SLOT_MULTIFUNCTION&t;(x000000004)
multiline_comment|/* function flags */
DECL|macro|FUNC_HAS_STA
mdefine_line|#define FUNC_HAS_STA&t;&t;(0x00000001)
DECL|macro|FUNC_HAS_EJ0
mdefine_line|#define FUNC_HAS_EJ0&t;&t;(0x00000002)
DECL|macro|FUNC_HAS_PS0
mdefine_line|#define FUNC_HAS_PS0&t;&t;(0x00000010)
DECL|macro|FUNC_HAS_PS1
mdefine_line|#define FUNC_HAS_PS1&t;&t;(0x00000020)
DECL|macro|FUNC_HAS_PS2
mdefine_line|#define FUNC_HAS_PS2&t;&t;(0x00000040)
DECL|macro|FUNC_HAS_PS3
mdefine_line|#define FUNC_HAS_PS3&t;&t;(0x00000080)
multiline_comment|/* not yet */
DECL|macro|SLOT_SUPPORT_66MHZ
mdefine_line|#define SLOT_SUPPORT_66MHZ&t;(0x00010000)
DECL|macro|SLOT_SUPPORT_100MHZ
mdefine_line|#define SLOT_SUPPORT_100MHZ&t;(0x00020000)
DECL|macro|SLOT_SUPPORT_133MHZ
mdefine_line|#define SLOT_SUPPORT_133MHZ&t;(0x00040000)
DECL|macro|SLOT_SUPPORT_PCIX
mdefine_line|#define SLOT_SUPPORT_PCIX&t;(0x00080000)
multiline_comment|/* function prototypes */
multiline_comment|/* acpiphp_glue.c */
r_extern
r_int
id|acpiphp_glue_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|acpiphp_glue_exit
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_get_num_slots
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|acpiphp_slot
op_star
id|get_slot_from_id
(paren
r_int
id|id
)paren
suffix:semicolon
DECL|typedef|acpiphp_callback
r_typedef
r_int
(paren
op_star
id|acpiphp_callback
)paren
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_for_each_slot
(paren
id|acpiphp_callback
id|fn
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_check_bridge
(paren
r_struct
id|acpiphp_bridge
op_star
id|bridge
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_enable_slot
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_disable_slot
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
id|u8
id|acpiphp_get_power_status
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
id|u8
id|acpiphp_get_attention_status
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
id|u8
id|acpiphp_get_latch_status
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
id|u8
id|acpiphp_get_adapter_status
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
multiline_comment|/* acpiphp_pci.c */
r_extern
r_struct
id|pci_dev
op_star
id|acpiphp_allocate_pcidev
(paren
r_struct
id|pci_bus
op_star
id|pbus
comma
r_int
id|dev
comma
r_int
id|fn
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_configure_slot
(paren
r_struct
id|acpiphp_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_configure_function
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_unconfigure_function
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_detect_pci_resource
(paren
r_struct
id|acpiphp_bridge
op_star
id|bridge
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_init_func_resource
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
suffix:semicolon
multiline_comment|/* acpiphp_res.c */
r_extern
r_struct
id|pci_resource
op_star
id|acpiphp_get_io_resource
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
comma
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|pci_resource
op_star
id|acpiphp_get_max_resource
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
comma
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|pci_resource
op_star
id|acpiphp_get_resource
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
comma
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|pci_resource
op_star
id|acpiphp_get_resource_with_base
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
comma
id|u64
id|base
comma
id|u32
id|size
)paren
suffix:semicolon
r_extern
r_int
id|acpiphp_resource_sort_and_combine
(paren
r_struct
id|pci_resource
op_star
op_star
id|head
)paren
suffix:semicolon
r_extern
r_struct
id|pci_resource
op_star
id|acpiphp_make_resource
(paren
id|u64
id|base
comma
id|u32
id|length
)paren
suffix:semicolon
r_extern
r_void
id|acpiphp_move_resource
(paren
r_struct
id|pci_resource
op_star
op_star
id|from
comma
r_struct
id|pci_resource
op_star
op_star
id|to
)paren
suffix:semicolon
r_extern
r_void
id|acpiphp_free_resource
(paren
r_struct
id|pci_resource
op_star
op_star
id|res
)paren
suffix:semicolon
r_extern
r_void
id|acpiphp_dump_resource
(paren
r_struct
id|acpiphp_bridge
op_star
id|bridge
)paren
suffix:semicolon
multiline_comment|/* debug */
r_extern
r_void
id|acpiphp_dump_func_resource
(paren
r_struct
id|acpiphp_func
op_star
id|func
)paren
suffix:semicolon
multiline_comment|/* debug */
multiline_comment|/* variables */
r_extern
r_int
id|acpiphp_debug
suffix:semicolon
macro_line|#endif /* _ACPIPHP_H */
eof
