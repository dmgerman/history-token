multiline_comment|/*&n; * ACPI PCI Hot Plug Controller Driver&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; * Copyright (C) 2002 Hiroshi Aono (h-aono@ap.jp.nec.com)&n; * Copyright (C) 2002,2003 Takayoshi Kochi (t-kochi@bq.jp.nec.com)&n; * Copyright (C) 2002,2003 NEC Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;gregkh@us.ibm.com&gt;,&n; *&t;&t;    &lt;t-kochi@bq.jp.nec.com&gt;&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;pci_hotplug.h&quot;
macro_line|#include &quot;acpiphp.h&quot;
r_static
id|LIST_HEAD
c_func
(paren
id|slot_list
)paren
suffix:semicolon
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;&quot;acpiphp&quot;
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|variable|acpiphp_debug
r_int
id|acpiphp_debug
suffix:semicolon
multiline_comment|/* local variables */
DECL|variable|num_slots
r_static
r_int
id|num_slots
suffix:semicolon
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.4&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Greg Kroah-Hartman &lt;gregkh@us.ibm.com&gt;, Takayoshi Kochi &lt;t-kochi@bq.jp.nec.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;ACPI Hot Plug PCI Controller Driver&quot;
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debugging mode enabled or not&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_bool
comma
l_int|644
)paren
suffix:semicolon
r_static
r_int
id|enable_slot
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
r_static
r_int
id|disable_slot
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
suffix:semicolon
r_static
r_int
id|set_attention_status
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
r_static
r_int
id|get_power_status
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
r_static
r_int
id|get_address
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
id|u32
op_star
id|value
)paren
suffix:semicolon
r_static
r_int
id|get_latch_status
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
r_static
r_int
id|get_adapter_status
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
DECL|variable|acpi_hotplug_slot_ops
r_static
r_struct
id|hotplug_slot_ops
id|acpi_hotplug_slot_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|enable_slot
op_assign
id|enable_slot
comma
dot
id|disable_slot
op_assign
id|disable_slot
comma
dot
id|set_attention_status
op_assign
id|set_attention_status
comma
dot
id|get_power_status
op_assign
id|get_power_status
comma
dot
id|get_latch_status
op_assign
id|get_latch_status
comma
dot
id|get_adapter_status
op_assign
id|get_adapter_status
comma
dot
id|get_address
op_assign
id|get_address
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * enable_slot - power on and enable a slot&n; * @hotplug_slot: slot to enable&n; *&n; * Actual tasks are done in acpiphp_enable_slot()&n; *&n; */
DECL|function|enable_slot
r_static
r_int
id|enable_slot
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
multiline_comment|/* enable the specified slot */
r_return
id|acpiphp_enable_slot
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * disable_slot - disable and power off a slot&n; * @hotplug_slot: slot to disable&n; *&n; * Actual tasks are done in acpiphp_disable_slot()&n; *&n; */
DECL|function|disable_slot
r_static
r_int
id|disable_slot
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
multiline_comment|/* disable the specified slot */
r_return
id|acpiphp_disable_slot
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * set_attention_status - set attention LED&n; *&n; * TBD:&n; * ACPI doesn&squot;t have known method to manipulate&n; * attention status LED.&n; *&n; */
DECL|function|set_attention_status
r_static
r_int
id|set_attention_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
id|u8
id|status
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* FIXME turn light off */
id|hotplug_slot-&gt;info-&gt;attention_status
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
multiline_comment|/* FIXME turn light on */
id|hotplug_slot-&gt;info-&gt;attention_status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * get_power_status - get power status of a slot&n; * @hotplug_slot: slot to get status&n; * @value: pointer to store status&n; *&n; * Some platforms may not implement _STA method properly.&n; * In that case, the value returned may not be reliable.&n; *&n; */
DECL|function|get_power_status
r_static
r_int
id|get_power_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
id|u8
op_star
id|value
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
op_star
id|value
op_assign
id|acpiphp_get_power_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * get_latch_status - get latch status of a slot&n; * @hotplug_slot: slot to get status&n; * @value: pointer to store status&n; *&n; * ACPI doesn&squot;t provide any formal means to access latch status.&n; * Instead, we fake latch status from _STA&n; *&n; */
DECL|function|get_latch_status
r_static
r_int
id|get_latch_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
id|u8
op_star
id|value
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
op_star
id|value
op_assign
id|acpiphp_get_latch_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * get_adapter_status - get adapter status of a slot&n; * @hotplug_slot: slot to get status&n; * @value: pointer to store status&n; *&n; * ACPI doesn&squot;t provide any formal means to access adapter status.&n; * Instead, we fake adapter status from _STA&n; *&n; */
DECL|function|get_adapter_status
r_static
r_int
id|get_adapter_status
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
id|u8
op_star
id|value
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
op_star
id|value
op_assign
id|acpiphp_get_adapter_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * get_address - get pci address of a slot&n; * @hotplug_slot: slot to get status&n; * @busdev: pointer to struct pci_busdev (seg, bus, dev)&n; *&n; */
DECL|function|get_address
r_static
r_int
id|get_address
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
id|u32
op_star
id|value
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
op_star
id|value
op_assign
id|acpiphp_get_address
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_acpi
r_static
r_int
id|__init
id|init_acpi
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
multiline_comment|/* initialize internal data structure etc. */
id|retval
op_assign
id|acpiphp_glue_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* read initial number of slots */
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|num_slots
op_assign
id|acpiphp_get_num_slots
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_slots
op_eq
l_int|0
)paren
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * make_slot_name - make a slot name that appears in pcihpfs&n; * @slot: slot to name&n; *&n; */
DECL|function|make_slot_name
r_static
r_void
id|make_slot_name
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
id|snprintf
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;name
comma
id|SLOT_NAME_SIZE
comma
l_string|&quot;%u&quot;
comma
id|slot-&gt;acpi_slot-&gt;sun
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * release_slot - free up the memory used by a slot&n; * @hotplug_slot: slot to free&n; */
DECL|function|release_slot
r_static
r_void
id|release_slot
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - physical_slot = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|hotplug_slot-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;info
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * init_slots - initialize &squot;struct slot&squot; structures for each slot&n; *&n; */
DECL|function|init_slots
r_static
r_int
id|__init
id|init_slots
c_func
(paren
r_void
)paren
(brace
r_struct
id|slot
op_star
id|slot
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_slots
suffix:semicolon
op_increment
id|i
)paren
(brace
id|slot
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|slot
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot
)paren
r_goto
id|error
suffix:semicolon
id|memset
c_func
(paren
id|slot
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|slot
)paren
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hotplug_slot
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;hotplug_slot
)paren
r_goto
id|error_slot
suffix:semicolon
id|memset
c_func
(paren
id|slot-&gt;hotplug_slot
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hotplug_slot
)paren
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hotplug_slot_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;hotplug_slot-&gt;info
)paren
r_goto
id|error_hpslot
suffix:semicolon
id|memset
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;info
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hotplug_slot_info
)paren
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|SLOT_NAME_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;hotplug_slot-&gt;name
)paren
r_goto
id|error_info
suffix:semicolon
id|slot-&gt;magic
op_assign
id|SLOT_MAGIC
suffix:semicolon
id|slot-&gt;number
op_assign
id|i
suffix:semicolon
id|slot-&gt;hotplug_slot
op_member_access_from_pointer
r_private
op_assign
id|slot
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;release
op_assign
op_amp
id|release_slot
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;ops
op_assign
op_amp
id|acpi_hotplug_slot_ops
suffix:semicolon
id|slot-&gt;acpi_slot
op_assign
id|get_slot_from_id
c_func
(paren
id|i
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info-&gt;power_status
op_assign
id|acpiphp_get_power_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info-&gt;attention_status
op_assign
id|acpiphp_get_attention_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info-&gt;latch_status
op_assign
id|acpiphp_get_latch_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info-&gt;adapter_status
op_assign
id|acpiphp_get_adapter_status
c_func
(paren
id|slot-&gt;acpi_slot
)paren
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info-&gt;max_bus_speed
op_assign
id|PCI_SPEED_UNKNOWN
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;info-&gt;cur_bus_speed
op_assign
id|PCI_SPEED_UNKNOWN
suffix:semicolon
id|make_slot_name
c_func
(paren
id|slot
)paren
suffix:semicolon
id|retval
op_assign
id|pci_hp_register
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|err
c_func
(paren
l_string|&quot;pci_hp_register failed with error %d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
id|release_slot
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* add slot to our internal list */
id|list_add
c_func
(paren
op_amp
id|slot-&gt;slot_list
comma
op_amp
id|slot_list
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;Slot [%s] registered&bslash;n&quot;
comma
id|slot-&gt;hotplug_slot-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
id|error_info
suffix:colon
id|kfree
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;info
)paren
suffix:semicolon
id|error_hpslot
suffix:colon
id|kfree
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|error_slot
suffix:colon
id|kfree
c_func
(paren
id|slot
)paren
suffix:semicolon
id|error
suffix:colon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|cleanup_slots
r_static
r_void
id|__exit
id|cleanup_slots
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
comma
op_star
id|n
suffix:semicolon
r_struct
id|slot
op_star
id|slot
suffix:semicolon
id|list_for_each_safe
(paren
id|tmp
comma
id|n
comma
op_amp
id|slot_list
)paren
(brace
multiline_comment|/* memory will be freed in release_slot callback */
id|slot
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|slot
comma
id|slot_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|slot-&gt;slot_list
)paren
suffix:semicolon
id|pci_hp_deregister
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
)brace
)brace
DECL|function|acpiphp_init
r_static
r_int
id|__init
id|acpiphp_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; version: &quot;
id|DRIVER_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|acpiphp_debug
op_assign
id|debug
suffix:semicolon
multiline_comment|/* read all the ACPI info from the system */
id|retval
op_assign
id|init_acpi
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|init_slots
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|acpiphp_exit
r_static
r_void
id|__exit
id|acpiphp_exit
c_func
(paren
r_void
)paren
(brace
id|cleanup_slots
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* deallocate internal data structures etc. */
id|acpiphp_glue_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|acpiphp_init
id|module_init
c_func
(paren
id|acpiphp_init
)paren
suffix:semicolon
DECL|variable|acpiphp_exit
id|module_exit
c_func
(paren
id|acpiphp_exit
)paren
suffix:semicolon
eof
