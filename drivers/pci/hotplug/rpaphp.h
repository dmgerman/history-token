multiline_comment|/*&n; * PCI Hot Plug Controller Driver for RPA-compliant PPC64 platform.&n; *&n; * Copyright (C) 2003 Linda Xie &lt;lxie@us.ibm.com&gt;&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;lxie@us.ibm.com&gt;,&n; *&n; */
macro_line|#ifndef _PPC64PHP_H
DECL|macro|_PPC64PHP_H
mdefine_line|#define _PPC64PHP_H
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pci_hotplug.h&quot;
DECL|macro|DR_INDICATOR
mdefine_line|#define DR_INDICATOR 9002
DECL|macro|DR_ENTITY_SENSE
mdefine_line|#define DR_ENTITY_SENSE 9003
DECL|macro|POWER_ON
mdefine_line|#define POWER_ON&t;100
DECL|macro|POWER_OFF
mdefine_line|#define POWER_OFF&t;0
DECL|macro|LED_OFF
mdefine_line|#define LED_OFF&t;&t;0
DECL|macro|LED_ON
mdefine_line|#define LED_ON&t;&t;1&t;/* continuous on */
DECL|macro|LED_ID
mdefine_line|#define LED_ID&t;&t;2&t;/* slow blinking */
DECL|macro|LED_ACTION
mdefine_line|#define LED_ACTION&t;3&t;/* fast blinking */
multiline_comment|/* Error status from rtas_get-sensor */
DECL|macro|NEED_POWER
mdefine_line|#define NEED_POWER    -9000&t;/* slot must be power up and unisolated to get state */
DECL|macro|PWR_ONLY
mdefine_line|#define PWR_ONLY      -9001&t;/* slot must be powerd up to get state, leave isolated */
DECL|macro|ERR_SENSE_USE
mdefine_line|#define ERR_SENSE_USE -9002&t;/* No DR operation will succeed, slot is unusable  */
multiline_comment|/* Sensor values from rtas_get-sensor */
DECL|macro|EMPTY
mdefine_line|#define EMPTY           0&t;/* No card in slot */
DECL|macro|PRESENT
mdefine_line|#define PRESENT         1&t;/* Card in slot */
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;rpaphp&quot;
r_extern
r_int
id|debug
suffix:semicolon
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (debug)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_DEBUG &quot;%s: &quot; format,&t;&bslash;&n;&t;&t;&t;&t;MY_NAME , ## arg); &t;&t;&bslash;&n;&t;} while (0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format, MY_NAME , ## arg)
DECL|macro|SLOT_MAGIC
mdefine_line|#define SLOT_MAGIC&t;0x67267322
multiline_comment|/* slot types */
DECL|macro|VIO_DEV
mdefine_line|#define VIO_DEV&t;1
DECL|macro|PCI_DEV
mdefine_line|#define PCI_DEV&t;2
multiline_comment|/* slot states */
DECL|macro|NOT_VALID
mdefine_line|#define&t;NOT_VALID&t;3
DECL|macro|NOT_CONFIGURED
mdefine_line|#define&t;NOT_CONFIGURED&t;2
DECL|macro|CONFIGURED
mdefine_line|#define&t;CONFIGURED&t;1
DECL|macro|EMPTY
mdefine_line|#define&t;EMPTY&t;&t;0
multiline_comment|/*&n; * struct slot - slot information for each *physical* slot&n; */
DECL|struct|slot
r_struct
id|slot
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|power_domain
id|u32
id|power_domain
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|location
r_char
op_star
id|location
suffix:semicolon
DECL|member|dn
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
multiline_comment|/* slot&squot;s device_node in OFDT */
multiline_comment|/* dn has phb info */
DECL|member|bridge
r_struct
id|pci_dev
op_star
id|bridge
suffix:semicolon
multiline_comment|/* slot&squot;s pci_dev in pci_devices */
r_union
(brace
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* pci_dev of device in this slot */
multiline_comment|/* it will be used for unconfig */
multiline_comment|/* NULL if slot is empty */
DECL|member|vio_dev
r_struct
id|vio_dev
op_star
id|vio_dev
suffix:semicolon
multiline_comment|/* vio_dev of the device in this slot */
DECL|member|dev
)brace
id|dev
suffix:semicolon
DECL|member|dev_type
id|u8
id|dev_type
suffix:semicolon
multiline_comment|/* VIO or PCI */
DECL|member|hotplug_slot
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
suffix:semicolon
DECL|member|rpaphp_slot_list
r_struct
id|list_head
id|rpaphp_slot_list
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|hotplug_slot_ops
id|rpaphp_hotplug_slot_ops
suffix:semicolon
r_extern
r_struct
id|list_head
id|rpaphp_slot_head
suffix:semicolon
r_extern
r_int
id|num_slots
suffix:semicolon
multiline_comment|/* function prototypes */
multiline_comment|/* rpaphp_pci.c */
r_extern
r_struct
id|pci_dev
op_star
id|rpaphp_find_pci_dev
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_claim_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|resource
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_enable_pci_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|register_pci_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_unconfig_pci_adapter
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_get_pci_adapter_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_int
id|is_init
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
multiline_comment|/* rpaphp_core.c */
r_extern
r_int
id|rpaphp_add_slot
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_remove_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
multiline_comment|/* rpaphp_vio.c */
r_extern
r_int
id|rpaphp_get_vio_adapter_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_int
id|is_init
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_unconfig_vio_adapter
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|register_vio_slot
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_enable_vio_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
multiline_comment|/* rpaphp_slot.c */
r_extern
r_void
id|dealloc_slot_struct
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_struct
id|slot
op_star
id|alloc_slot_struct
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|drc_index
comma
r_char
op_star
id|drc_name
comma
r_int
id|power_domain
)paren
suffix:semicolon
r_extern
r_int
id|register_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_get_power_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
r_extern
r_int
id|rpaphp_set_attention_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
id|u8
id|status
)paren
suffix:semicolon
r_extern
r_void
id|rpaphp_sysfs_remove_attr_location
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _PPC64PHP_H */
eof
