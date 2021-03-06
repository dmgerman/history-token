multiline_comment|/*&n; * PCI Hot Plug Controller Skeleton Driver - 0.2&n; *&n; * Copyright (C) 2001,2003 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001,2003 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * This driver is to be used as a skeleton driver to be show how to interface&n; * with the pci hotplug core easily.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pci_hotplug.h&quot;
DECL|struct|slot
r_struct
id|slot
(brace
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
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|slot_list
)paren
suffix:semicolon
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;&quot;pcihp_skeleton&quot;
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (debug)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk (KERN_DEBUG &quot;%s: &quot; format &quot;&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;&t;MY_NAME , ## arg); &t;&t;&bslash;&n;&t;} while (0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format &quot;&bslash;n&quot;, MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format &quot;&bslash;n&quot;, MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format &quot;&bslash;n&quot;, MY_NAME , ## arg)
multiline_comment|/* local variables */
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|variable|num_slots
r_static
r_int
id|num_slots
suffix:semicolon
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.3&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Greg Kroah-Hartman &lt;greg@kroah.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;Hot Plug PCI Controller Skeleton Driver&quot;
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
id|module_param
c_func
(paren
id|debug
comma
r_bool
comma
l_int|0644
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
id|hardware_test
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
id|get_attention_status
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
DECL|variable|skel_hotplug_slot_ops
r_static
r_struct
id|hotplug_slot_ops
id|skel_hotplug_slot_ops
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
id|hardware_test
op_assign
id|hardware_test
comma
dot
id|get_power_status
op_assign
id|get_power_status
comma
dot
id|get_attention_status
op_assign
id|get_attention_status
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
)brace
suffix:semicolon
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
r_int
id|retval
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Fill in code here to enable the specified slot&n;&t; */
r_return
id|retval
suffix:semicolon
)brace
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
r_int
id|retval
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Fill in code here to disable the specified slot&n;&t; */
r_return
id|retval
suffix:semicolon
)brace
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
r_struct
id|slot
op_star
id|slot
op_assign
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
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
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Fill in code here to turn light off&n;&t;&t;&t; */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Fill in code here to turn light on&n;&t;&t;&t; */
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hardware_test
r_static
r_int
id|hardware_test
c_func
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
id|u32
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
r_int
id|retval
op_assign
l_int|0
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
r_switch
c_cond
(paren
id|value
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Specify a test here */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Specify another test here */
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
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
r_int
id|retval
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Fill in logic to get the current power status of the specific&n;&t; * slot and store it in the *value location.&n;&t; */
r_return
id|retval
suffix:semicolon
)brace
DECL|function|get_attention_status
r_static
r_int
id|get_attention_status
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
r_int
id|retval
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Fill in logic to get the current attention status of the specific&n;&t; * slot and store it in the *value location.&n;&t; */
r_return
id|retval
suffix:semicolon
)brace
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
r_int
id|retval
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Fill in logic to get the current latch status of the specific&n;&t; * slot and store it in the *value location.&n;&t; */
r_return
id|retval
suffix:semicolon
)brace
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
r_int
id|retval
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Fill in logic to get the current adapter status of the specific&n;&t; * slot and store it in the *value location.&n;&t; */
r_return
id|retval
suffix:semicolon
)brace
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
DECL|macro|SLOT_NAME_SIZE
mdefine_line|#define SLOT_NAME_SIZE&t;10
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
multiline_comment|/*&n;&t; * Stupid way to make a filename out of the slot name.&n;&t; * replace this if your hardware provides a better way to name slots.&n;&t; */
id|snprintf
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;name
comma
id|SLOT_NAME_SIZE
comma
l_string|&quot;%d&quot;
comma
id|slot-&gt;number
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
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
suffix:semicolon
r_struct
id|hotplug_slot_info
op_star
id|info
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Create a structure for each slot, and register that slot&n;&t; * with the pci_hotplug subsystem.&n;&t; */
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
id|hotplug_slot
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
id|hotplug_slot
)paren
r_goto
id|error_slot
suffix:semicolon
id|memset
c_func
(paren
id|hotplug_slot
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
id|slot-&gt;hotplug_slot
op_assign
id|hotplug_slot
suffix:semicolon
id|info
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
id|info
)paren
r_goto
id|error_hpslot
suffix:semicolon
id|memset
c_func
(paren
id|info
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
id|hotplug_slot-&gt;info
op_assign
id|info
suffix:semicolon
id|name
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
id|name
)paren
r_goto
id|error_info
suffix:semicolon
id|hotplug_slot-&gt;name
op_assign
id|name
suffix:semicolon
id|slot-&gt;number
op_assign
id|i
suffix:semicolon
id|hotplug_slot
op_member_access_from_pointer
r_private
op_assign
id|slot
suffix:semicolon
id|hotplug_slot-&gt;release
op_assign
op_amp
id|release_slot
suffix:semicolon
id|make_slot_name
c_func
(paren
id|slot
)paren
suffix:semicolon
id|hotplug_slot-&gt;ops
op_assign
op_amp
id|skel_hotplug_slot_ops
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Initilize the slot info structure with some known&n;&t;&t; * good values.&n;&t;&t; */
id|info-&gt;power_status
op_assign
id|get_power_status
c_func
(paren
id|slot
)paren
suffix:semicolon
id|info-&gt;attention_status
op_assign
id|get_attention_status
c_func
(paren
id|slot
)paren
suffix:semicolon
id|info-&gt;latch_status
op_assign
id|get_latch_status
c_func
(paren
id|slot
)paren
suffix:semicolon
id|info-&gt;adapter_status
op_assign
id|get_adapter_status
c_func
(paren
id|slot
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;registering slot %d&bslash;n&quot;
comma
id|i
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
r_goto
id|error_name
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
)brace
r_return
l_int|0
suffix:semicolon
id|error_name
suffix:colon
id|kfree
c_func
(paren
id|name
)paren
suffix:semicolon
id|error_info
suffix:colon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
id|error_hpslot
suffix:colon
id|kfree
c_func
(paren
id|hotplug_slot
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
id|retval
suffix:semicolon
)brace
DECL|function|cleanup_slots
r_static
r_void
id|__exit
id|cleanup_slots
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|list_head
op_star
id|next
suffix:semicolon
r_struct
id|slot
op_star
id|slot
suffix:semicolon
multiline_comment|/*&n;&t; * Unregister all of our slots with the pci_hotplug subsystem.&n;&t; * Memory will be freed in release_slot() callback after slot&squot;s&n;&t; * lifespan is finished.&n;&t; */
id|list_for_each_safe
c_func
(paren
id|tmp
comma
id|next
comma
op_amp
id|slot_list
)paren
(brace
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
DECL|function|pcihp_skel_init
r_static
r_int
id|__init
id|pcihp_skel_init
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
multiline_comment|/*&n;&t; * Do specific initialization stuff for your driver here&n;&t; * Like initializing your controller hardware (if any) and&n;&t; * determining the number of slots you have in the system&n;&t; * right now.&n;&t; */
id|num_slots
op_assign
l_int|5
suffix:semicolon
r_return
id|init_slots
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pcihp_skel_exit
r_static
r_void
id|__exit
id|pcihp_skel_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Clean everything up.&n;&t; */
id|cleanup_slots
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|pcihp_skel_init
id|module_init
c_func
(paren
id|pcihp_skel_init
)paren
suffix:semicolon
DECL|variable|pcihp_skel_exit
id|module_exit
c_func
(paren
id|pcihp_skel_exit
)paren
suffix:semicolon
eof
