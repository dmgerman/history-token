multiline_comment|/*&n; * PCI HotPlug Core Functions&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#ifndef _PCI_HOTPLUG_H
DECL|macro|_PCI_HOTPLUG_H
mdefine_line|#define _PCI_HOTPLUG_H
multiline_comment|/* These values come from the PCI Hotplug Spec */
DECL|enum|pci_bus_speed
r_enum
id|pci_bus_speed
(brace
DECL|enumerator|PCI_SPEED_33MHz
id|PCI_SPEED_33MHz
op_assign
l_int|0x00
comma
DECL|enumerator|PCI_SPEED_66MHz
id|PCI_SPEED_66MHz
op_assign
l_int|0x01
comma
DECL|enumerator|PCI_SPEED_66MHz_PCIX
id|PCI_SPEED_66MHz_PCIX
op_assign
l_int|0x02
comma
DECL|enumerator|PCI_SPEED_100MHz_PCIX
id|PCI_SPEED_100MHz_PCIX
op_assign
l_int|0x03
comma
DECL|enumerator|PCI_SPEED_133MHz_PCIX
id|PCI_SPEED_133MHz_PCIX
op_assign
l_int|0x04
comma
DECL|enumerator|PCI_SPEED_66MHz_PCIX_266
id|PCI_SPEED_66MHz_PCIX_266
op_assign
l_int|0x09
comma
DECL|enumerator|PCI_SPEED_100MHz_PCIX_266
id|PCI_SPEED_100MHz_PCIX_266
op_assign
l_int|0x0a
comma
DECL|enumerator|PCI_SPEED_133MHz_PCIX_266
id|PCI_SPEED_133MHz_PCIX_266
op_assign
l_int|0x0b
comma
DECL|enumerator|PCI_SPEED_66MHz_PCIX_533
id|PCI_SPEED_66MHz_PCIX_533
op_assign
l_int|0x11
comma
DECL|enumerator|PCI_SPEED_100MHz_PCIX_533
id|PCI_SPEED_100MHz_PCIX_533
op_assign
l_int|0X12
comma
DECL|enumerator|PCI_SPEED_133MHz_PCIX_533
id|PCI_SPEED_133MHz_PCIX_533
op_assign
l_int|0x13
comma
DECL|enumerator|PCI_SPEED_UNKNOWN
id|PCI_SPEED_UNKNOWN
op_assign
l_int|0xff
comma
)brace
suffix:semicolon
r_struct
id|hotplug_slot
suffix:semicolon
DECL|struct|hotplug_slot_attribute
r_struct
id|hotplug_slot_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|hotplug_slot
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|hotplug_slot
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_hotplug_attr
mdefine_line|#define to_hotplug_attr(n) container_of(n, struct hotplug_slot_attribute, attr);
multiline_comment|/**&n; * struct hotplug_slot_ops -the callbacks that the hotplug pci core can use&n; * @owner: The module owner of this structure&n; * @enable_slot: Called when the user wants to enable a specific pci slot&n; * @disable_slot: Called when the user wants to disable a specific pci slot&n; * @set_attention_status: Called to set the specific slot&squot;s attention LED to&n; * the specified value&n; * @hardware_test: Called to run a specified hardware test on the specified&n; * slot.&n; * @get_power_status: Called to get the current power status of a slot.&n; * &t;If this field is NULL, the value passed in the struct hotplug_slot_info&n; * &t;will be used when this value is requested by a user.&n; * @get_attention_status: Called to get the current attention status of a slot.&n; *&t;If this field is NULL, the value passed in the struct hotplug_slot_info&n; *&t;will be used when this value is requested by a user.&n; * @get_latch_status: Called to get the current latch status of a slot.&n; *&t;If this field is NULL, the value passed in the struct hotplug_slot_info&n; *&t;will be used when this value is requested by a user.&n; * @get_adapter_status: Called to get see if an adapter is present in the slot or not.&n; *&t;If this field is NULL, the value passed in the struct hotplug_slot_info&n; *&t;will be used when this value is requested by a user.&n; * @get_max_bus_speed: Called to get the max bus speed for a slot.&n; *&t;If this field is NULL, the value passed in the struct hotplug_slot_info&n; *&t;will be used when this value is requested by a user.&n; * @get_cur_bus_speed: Called to get the current bus speed for a slot.&n; *&t;If this field is NULL, the value passed in the struct hotplug_slot_info&n; *&t;will be used when this value is requested by a user.&n; *&n; * The table of function pointers that is passed to the hotplug pci core by a&n; * hotplug pci driver.  These functions are called by the hotplug pci core when&n; * the user wants to do something to a specific slot (query it for information,&n; * set an LED, enable / disable power, etc.)&n; */
DECL|struct|hotplug_slot_ops
r_struct
id|hotplug_slot_ops
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|enable_slot
r_int
(paren
op_star
id|enable_slot
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|disable_slot
r_int
(paren
op_star
id|disable_slot
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|set_attention_status
r_int
(paren
op_star
id|set_attention_status
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
id|value
)paren
suffix:semicolon
DECL|member|hardware_test
r_int
(paren
op_star
id|hardware_test
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u32
id|value
)paren
suffix:semicolon
DECL|member|get_power_status
r_int
(paren
op_star
id|get_power_status
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
DECL|member|get_attention_status
r_int
(paren
op_star
id|get_attention_status
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
DECL|member|get_latch_status
r_int
(paren
op_star
id|get_latch_status
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
DECL|member|get_adapter_status
r_int
(paren
op_star
id|get_adapter_status
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u8
op_star
id|value
)paren
suffix:semicolon
DECL|member|get_max_bus_speed
r_int
(paren
op_star
id|get_max_bus_speed
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_enum
id|pci_bus_speed
op_star
id|value
)paren
suffix:semicolon
DECL|member|get_cur_bus_speed
r_int
(paren
op_star
id|get_cur_bus_speed
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_enum
id|pci_bus_speed
op_star
id|value
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct hotplug_slot_info - used to notify the hotplug pci core of the state of the slot&n; * @power: if power is enabled or not (1/0)&n; * @attention_status: if the attention light is enabled or not (1/0)&n; * @latch_status: if the latch (if any) is open or closed (1/0)&n; * @adapter_present: if there is a pci board present in the slot or not (1/0)&n; *&n; * Used to notify the hotplug pci core of the status of a specific slot.&n; */
DECL|struct|hotplug_slot_info
r_struct
id|hotplug_slot_info
(brace
DECL|member|power_status
id|u8
id|power_status
suffix:semicolon
DECL|member|attention_status
id|u8
id|attention_status
suffix:semicolon
DECL|member|latch_status
id|u8
id|latch_status
suffix:semicolon
DECL|member|adapter_status
id|u8
id|adapter_status
suffix:semicolon
DECL|member|max_bus_speed
r_enum
id|pci_bus_speed
id|max_bus_speed
suffix:semicolon
DECL|member|cur_bus_speed
r_enum
id|pci_bus_speed
id|cur_bus_speed
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * struct hotplug_slot - used to register a physical slot with the hotplug pci core&n; * @name: the name of the slot being registered.  This string must&n; * be unique amoung slots registered on this system.&n; * @ops: pointer to the &amp;struct hotplug_slot_ops to be used for this slot&n; * @info: pointer to the &amp;struct hotplug_slot_info for the inital values for&n; * this slot.&n; * @private: used by the hotplug pci controller driver to store whatever it&n; * needs.&n; */
DECL|struct|hotplug_slot
r_struct
id|hotplug_slot
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|ops
r_struct
id|hotplug_slot_ops
op_star
id|ops
suffix:semicolon
DECL|member|info
r_struct
id|hotplug_slot_info
op_star
id|info
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* Variables below this are for use only by the hotplug pci core. */
DECL|member|slot_list
r_struct
id|list_head
id|slot_list
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_hotplug_slot
mdefine_line|#define to_hotplug_slot(n) container_of(n, struct hotplug_slot, kobj)
r_extern
r_int
id|pci_hp_register
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|pci_hp_deregister
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|pci_hp_change_slot_info
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_struct
id|hotplug_slot_info
op_star
id|info
)paren
suffix:semicolon
macro_line|#endif
eof
