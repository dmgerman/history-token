multiline_comment|/*&n; * Standard Hot Plug Controller Driver&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; * Copyright (C) 2003-2004 Intel Corporation&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;, &lt;dely.l.sy@intel.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;shpchp.h&quot;
macro_line|#include &quot;shpchprm.h&quot;
multiline_comment|/* Global variables */
DECL|variable|shpchp_debug
r_int
id|shpchp_debug
suffix:semicolon
DECL|variable|shpchp_poll_mode
r_int
id|shpchp_poll_mode
suffix:semicolon
DECL|variable|shpchp_poll_time
r_int
id|shpchp_poll_time
suffix:semicolon
DECL|variable|shpchp_ctrl_list
r_struct
id|controller
op_star
id|shpchp_ctrl_list
suffix:semicolon
multiline_comment|/* = NULL */
DECL|variable|shpchp_slot_list
r_struct
id|pci_func
op_star
id|shpchp_slot_list
(braket
l_int|256
)braket
suffix:semicolon
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.4&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Dan Zink &lt;dan.zink@compaq.com&gt;, Greg Kroah-Hartman &lt;greg@kroah.com&gt;, Dely Sy &lt;dely.l.sy@intel.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;Standard Hot Plug PCI Controller Driver&quot;
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
id|shpchp_debug
comma
r_bool
comma
l_int|644
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|shpchp_poll_mode
comma
r_bool
comma
l_int|644
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|shpchp_poll_time
comma
r_int
comma
l_int|644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|shpchp_debug
comma
l_string|&quot;Debugging mode enabled or not&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|shpchp_poll_mode
comma
l_string|&quot;Using polling mechanism for hot-plug events or not&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|shpchp_poll_time
comma
l_string|&quot;Polling mechanism frequency, in seconds&quot;
)paren
suffix:semicolon
DECL|macro|SHPC_MODULE_NAME
mdefine_line|#define SHPC_MODULE_NAME &quot;shpchp&quot;
r_static
r_int
id|shpc_start_thread
(paren
r_void
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
r_static
r_int
id|get_max_bus_speed
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
r_static
r_int
id|get_cur_bus_speed
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
DECL|variable|shpchp_hotplug_slot_ops
r_static
r_struct
id|hotplug_slot_ops
id|shpchp_hotplug_slot_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|set_attention_status
op_assign
id|set_attention_status
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
dot
id|get_max_bus_speed
op_assign
id|get_max_bus_speed
comma
dot
id|get_cur_bus_speed
op_assign
id|get_cur_bus_speed
comma
)brace
suffix:semicolon
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
(paren
r_struct
id|slot
op_star
)paren
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
DECL|function|init_slots
r_static
r_int
id|init_slots
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
r_struct
id|slot
op_star
id|new_slot
suffix:semicolon
id|u8
id|number_of_slots
suffix:semicolon
id|u8
id|slot_device
suffix:semicolon
id|u32
id|slot_number
comma
id|sun
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|number_of_slots
op_assign
id|ctrl-&gt;num_slots
suffix:semicolon
id|slot_device
op_assign
id|ctrl-&gt;slot_device_offset
suffix:semicolon
id|slot_number
op_assign
id|ctrl-&gt;first_slot
suffix:semicolon
r_while
c_loop
(paren
id|number_of_slots
)paren
(brace
id|new_slot
op_assign
(paren
r_struct
id|slot
op_star
)paren
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
id|new_slot
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|new_slot
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
id|new_slot-&gt;hotplug_slot
op_assign
id|kmalloc
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
id|new_slot-&gt;hotplug_slot
)paren
(brace
id|kfree
(paren
id|new_slot
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|new_slot-&gt;hotplug_slot
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
id|new_slot-&gt;hotplug_slot-&gt;info
op_assign
id|kmalloc
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
id|new_slot-&gt;hotplug_slot-&gt;info
)paren
(brace
id|kfree
(paren
id|new_slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|new_slot-&gt;hotplug_slot-&gt;info
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
id|new_slot-&gt;hotplug_slot-&gt;name
op_assign
id|kmalloc
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
id|new_slot-&gt;hotplug_slot-&gt;name
)paren
(brace
id|kfree
(paren
id|new_slot-&gt;hotplug_slot-&gt;info
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|new_slot-&gt;magic
op_assign
id|SLOT_MAGIC
suffix:semicolon
id|new_slot-&gt;ctrl
op_assign
id|ctrl
suffix:semicolon
id|new_slot-&gt;bus
op_assign
id|ctrl-&gt;slot_bus
suffix:semicolon
id|new_slot-&gt;device
op_assign
id|slot_device
suffix:semicolon
id|new_slot-&gt;hpc_ops
op_assign
id|ctrl-&gt;hpc_ops
suffix:semicolon
r_if
c_cond
(paren
id|shpchprm_get_physical_slot_number
c_func
(paren
id|ctrl
comma
op_amp
id|sun
comma
id|new_slot-&gt;bus
comma
id|new_slot-&gt;device
)paren
)paren
(brace
id|kfree
(paren
id|new_slot-&gt;hotplug_slot-&gt;info
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|new_slot-&gt;number
op_assign
id|sun
suffix:semicolon
id|new_slot-&gt;hp_slot
op_assign
id|slot_device
op_minus
id|ctrl-&gt;slot_device_offset
suffix:semicolon
multiline_comment|/* register this slot with the hotplug pci core */
id|new_slot-&gt;hotplug_slot
op_member_access_from_pointer
r_private
op_assign
id|new_slot
suffix:semicolon
id|make_slot_name
c_func
(paren
id|new_slot-&gt;hotplug_slot-&gt;name
comma
id|SLOT_NAME_SIZE
comma
id|new_slot
)paren
suffix:semicolon
id|new_slot-&gt;hotplug_slot-&gt;release
op_assign
op_amp
id|release_slot
suffix:semicolon
id|new_slot-&gt;hotplug_slot-&gt;ops
op_assign
op_amp
id|shpchp_hotplug_slot_ops
suffix:semicolon
id|new_slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_power_status
c_func
(paren
id|new_slot
comma
op_amp
(paren
id|new_slot-&gt;hotplug_slot-&gt;info-&gt;power_status
)paren
)paren
suffix:semicolon
id|new_slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_attention_status
c_func
(paren
id|new_slot
comma
op_amp
(paren
id|new_slot-&gt;hotplug_slot-&gt;info-&gt;attention_status
)paren
)paren
suffix:semicolon
id|new_slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_latch_status
c_func
(paren
id|new_slot
comma
op_amp
(paren
id|new_slot-&gt;hotplug_slot-&gt;info-&gt;latch_status
)paren
)paren
suffix:semicolon
id|new_slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_adapter_status
c_func
(paren
id|new_slot
comma
op_amp
(paren
id|new_slot-&gt;hotplug_slot-&gt;info-&gt;adapter_status
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Registering bus=%x dev=%x hp_slot=%x sun=%x slot_device_offset=%x&bslash;n&quot;
comma
id|new_slot-&gt;bus
comma
id|new_slot-&gt;device
comma
id|new_slot-&gt;hp_slot
comma
id|new_slot-&gt;number
comma
id|ctrl-&gt;slot_device_offset
)paren
suffix:semicolon
id|result
op_assign
id|pci_hp_register
(paren
id|new_slot-&gt;hotplug_slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|err
(paren
l_string|&quot;pci_hp_register failed with error %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot-&gt;hotplug_slot-&gt;info
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot-&gt;hotplug_slot-&gt;name
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|kfree
(paren
id|new_slot
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|new_slot-&gt;next
op_assign
id|ctrl-&gt;slot
suffix:semicolon
id|ctrl-&gt;slot
op_assign
id|new_slot
suffix:semicolon
id|number_of_slots
op_decrement
suffix:semicolon
id|slot_device
op_increment
suffix:semicolon
id|slot_number
op_add_assign
id|ctrl-&gt;slot_num_inc
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_slots
r_static
r_void
id|cleanup_slots
c_func
(paren
r_const
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
r_struct
id|slot
op_star
id|old_slot
suffix:semicolon
id|old_slot
op_assign
id|ctrl-&gt;slot
suffix:semicolon
id|ctrl-&gt;slot
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|old_slot
)paren
(brace
id|pci_hp_deregister
c_func
(paren
id|old_slot-&gt;hotplug_slot
)paren
suffix:semicolon
id|old_slot
op_assign
id|old_slot-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|get_ctlr_slot_config
r_static
r_int
id|get_ctlr_slot_config
c_func
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
r_int
id|num_ctlr_slots
suffix:semicolon
r_int
id|first_device_num
suffix:semicolon
r_int
id|physical_slot_num
suffix:semicolon
r_int
id|updown
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|rc
op_assign
id|shpc_get_ctlr_slot_config
c_func
(paren
id|ctrl
comma
op_amp
id|num_ctlr_slots
comma
op_amp
id|first_device_num
comma
op_amp
id|physical_slot_num
comma
op_amp
id|updown
comma
op_amp
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: get_ctlr_slot_config fail for b:d (%x:%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ctrl-&gt;bus
comma
id|ctrl-&gt;device
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|ctrl-&gt;num_slots
op_assign
id|num_ctlr_slots
suffix:semicolon
id|ctrl-&gt;slot_device_offset
op_assign
id|first_device_num
suffix:semicolon
id|ctrl-&gt;first_slot
op_assign
id|physical_slot_num
suffix:semicolon
id|ctrl-&gt;slot_num_inc
op_assign
id|updown
suffix:semicolon
multiline_comment|/* either -1 or 1 */
id|dbg
c_func
(paren
l_string|&quot;%s: num_slot(0x%x) 1st_dev(0x%x) psn(0x%x) updown(%d) for b:d (%x:%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|num_ctlr_slots
comma
id|first_device_num
comma
id|physical_slot_num
comma
id|updown
comma
id|ctrl-&gt;bus
comma
id|ctrl-&gt;device
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set_attention_status - Turns the Amber LED for a slot on, off or blink&n; */
DECL|function|set_attention_status
r_static
r_int
id|set_attention_status
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|hotplug_slot-&gt;info-&gt;attention_status
op_assign
id|status
suffix:semicolon
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|set_attention_status
c_func
(paren
id|slot
comma
id|status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|enable_slot
r_static
r_int
id|enable_slot
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
r_return
id|shpchp_enable_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
DECL|function|disable_slot
r_static
r_int
id|disable_slot
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
r_return
id|shpchp_disable_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
DECL|function|get_power_status
r_static
r_int
id|get_power_status
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|retval
op_assign
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_power_status
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
op_star
id|value
op_assign
id|hotplug_slot-&gt;info-&gt;power_status
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_attention_status
r_static
r_int
id|get_attention_status
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|retval
op_assign
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_attention_status
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
op_star
id|value
op_assign
id|hotplug_slot-&gt;info-&gt;attention_status
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_latch_status
r_static
r_int
id|get_latch_status
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|retval
op_assign
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_latch_status
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
op_star
id|value
op_assign
id|hotplug_slot-&gt;info-&gt;latch_status
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_adapter_status
r_static
r_int
id|get_adapter_status
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
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|retval
op_assign
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_adapter_status
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
op_star
id|value
op_assign
id|hotplug_slot-&gt;info-&gt;adapter_status
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_max_bus_speed
r_static
r_int
id|get_max_bus_speed
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
r_enum
id|pci_bus_speed
op_star
id|value
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|retval
op_assign
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_max_bus_speed
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
op_star
id|value
op_assign
id|PCI_SPEED_UNKNOWN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_cur_bus_speed
r_static
r_int
id|get_cur_bus_speed
(paren
r_struct
id|hotplug_slot
op_star
id|hotplug_slot
comma
r_enum
id|pci_bus_speed
op_star
id|value
)paren
(brace
r_struct
id|slot
op_star
id|slot
op_assign
id|get_slot
(paren
id|hotplug_slot
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
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
id|retval
op_assign
id|slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_cur_bus_speed
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
op_star
id|value
op_assign
id|PCI_SPEED_UNKNOWN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shpc_probe
r_static
r_int
id|shpc_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_int
id|rc
suffix:semicolon
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
r_struct
id|slot
op_star
id|t_slot
suffix:semicolon
r_int
id|first_device_num
suffix:semicolon
multiline_comment|/* first PCI device number supported by this SHPC */
r_int
id|num_ctlr_slots
suffix:semicolon
multiline_comment|/* number of slots supported by this SHPC */
id|ctrl
op_assign
(paren
r_struct
id|controller
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|controller
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctrl
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s : out of memory&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|err_out_none
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ctrl
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|controller
)paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;DRV_thread pid = %d&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|rc
op_assign
id|shpc_init
c_func
(paren
id|ctrl
comma
id|pdev
comma
(paren
id|php_intr_callback_t
)paren
id|shpchp_handle_attention_button
comma
(paren
id|php_intr_callback_t
)paren
id|shpchp_handle_switch_change
comma
(paren
id|php_intr_callback_t
)paren
id|shpchp_handle_presence_change
comma
(paren
id|php_intr_callback_t
)paren
id|shpchp_handle_power_fault
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
l_string|&quot;%s: controller initialization failed&bslash;n&quot;
comma
id|SHPC_MODULE_NAME
)paren
suffix:semicolon
r_goto
id|err_out_free_ctrl
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s: controller initialization success&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ctrl-&gt;pci_dev
op_assign
id|pdev
suffix:semicolon
multiline_comment|/* pci_dev of the P2P bridge */
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|ctrl
)paren
suffix:semicolon
id|ctrl-&gt;pci_bus
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|ctrl-&gt;pci_bus
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctrl-&gt;pci_bus
)paren
(brace
id|err
c_func
(paren
l_string|&quot;out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_out_unmap_mmio_region
suffix:semicolon
)brace
id|memcpy
(paren
id|ctrl-&gt;pci_bus
comma
id|pdev-&gt;bus
comma
r_sizeof
(paren
op_star
id|ctrl-&gt;pci_bus
)paren
)paren
suffix:semicolon
id|ctrl-&gt;bus
op_assign
id|pdev-&gt;bus-&gt;number
suffix:semicolon
id|ctrl-&gt;slot_bus
op_assign
id|pdev-&gt;subordinate-&gt;number
suffix:semicolon
id|ctrl-&gt;device
op_assign
id|PCI_SLOT
c_func
(paren
id|pdev-&gt;devfn
)paren
suffix:semicolon
id|ctrl-&gt;function
op_assign
id|PCI_FUNC
c_func
(paren
id|pdev-&gt;devfn
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;ctrl bus=0x%x, device=%x, function=%x, irq=%x&bslash;n&quot;
comma
id|ctrl-&gt;bus
comma
id|ctrl-&gt;device
comma
id|ctrl-&gt;function
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Save configuration headers for this and subordinate PCI buses&n;&t; */
id|rc
op_assign
id|get_ctlr_slot_config
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|err
c_func
(paren
id|msg_initialization_err
comma
id|rc
)paren
suffix:semicolon
r_goto
id|err_out_free_ctrl_bus
suffix:semicolon
)brace
id|first_device_num
op_assign
id|ctrl-&gt;slot_device_offset
suffix:semicolon
id|num_ctlr_slots
op_assign
id|ctrl-&gt;num_slots
suffix:semicolon
multiline_comment|/* Store PCI Config Space for all devices on this bus */
id|rc
op_assign
id|shpchp_save_config
c_func
(paren
id|ctrl
comma
id|ctrl-&gt;slot_bus
comma
id|num_ctlr_slots
comma
id|first_device_num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: unable to save PCI configuration data, error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|rc
)paren
suffix:semicolon
r_goto
id|err_out_free_ctrl_bus
suffix:semicolon
)brace
multiline_comment|/* Get IO, memory, and IRQ resources for new devices */
id|rc
op_assign
id|shpchprm_find_available_resources
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|ctrl-&gt;add_support
op_assign
op_logical_neg
id|rc
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
l_string|&quot;shpchprm_find_available_resources = %#x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|err
c_func
(paren
l_string|&quot;unable to locate PCI configuration resources for hot plug add.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out_free_ctrl_bus
suffix:semicolon
)brace
multiline_comment|/* Setup the slot information structures */
id|rc
op_assign
id|init_slots
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|err
c_func
(paren
id|msg_initialization_err
comma
l_int|6
)paren
suffix:semicolon
r_goto
id|err_out_free_ctrl_slot
suffix:semicolon
)brace
multiline_comment|/* Now hpc_functions (slot-&gt;hpc_ops-&gt;functions) are ready  */
id|t_slot
op_assign
id|shpchp_find_slot
c_func
(paren
id|ctrl
comma
id|first_device_num
)paren
suffix:semicolon
multiline_comment|/* Check for operation bus speed */
id|rc
op_assign
id|t_slot-&gt;hpc_ops
op_member_access_from_pointer
id|get_cur_bus_speed
c_func
(paren
id|t_slot
comma
op_amp
id|ctrl-&gt;speed
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: t_slot-&gt;hp_slot %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|t_slot-&gt;hp_slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_logical_or
id|ctrl-&gt;speed
op_eq
id|PCI_SPEED_UNKNOWN
)paren
(brace
id|err
c_func
(paren
id|SHPC_MODULE_NAME
l_string|&quot;: Can&squot;t get current bus speed. Set to 33MHz PCI.&bslash;n&quot;
)paren
suffix:semicolon
id|ctrl-&gt;speed
op_assign
id|PCI_SPEED_33MHz
suffix:semicolon
)brace
multiline_comment|/* Finish setting up the hot plug ctrl device */
id|ctrl-&gt;next_event
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shpchp_ctrl_list
)paren
(brace
id|shpchp_ctrl_list
op_assign
id|ctrl
suffix:semicolon
id|ctrl-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|ctrl-&gt;next
op_assign
id|shpchp_ctrl_list
suffix:semicolon
id|shpchp_ctrl_list
op_assign
id|ctrl
suffix:semicolon
)brace
id|shpchp_create_ctrl_files
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_free_ctrl_slot
suffix:colon
id|cleanup_slots
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|err_out_free_ctrl_bus
suffix:colon
id|kfree
c_func
(paren
id|ctrl-&gt;pci_bus
)paren
suffix:semicolon
id|err_out_unmap_mmio_region
suffix:colon
id|ctrl-&gt;hpc_ops
op_member_access_from_pointer
id|release_ctlr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|err_out_free_ctrl
suffix:colon
id|kfree
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|err_out_none
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|shpc_start_thread
r_static
r_int
id|shpc_start_thread
c_func
(paren
r_void
)paren
(brace
r_int
id|loop
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Initialize + Start the notification/polling mechanism &bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|shpchp_event_start_thread
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;shpchp_event_start_thread() failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;Initialize slot lists&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* One slot list for each bus in the system */
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|256
suffix:semicolon
id|loop
op_increment
)paren
(brace
id|shpchp_slot_list
(braket
id|loop
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
r_static
r_inline
r_void
id|__exit
DECL|function|free_shpchp_res
id|free_shpchp_res
c_func
(paren
r_struct
id|pci_resource
op_star
id|res
)paren
(brace
r_struct
id|pci_resource
op_star
id|tres
suffix:semicolon
r_while
c_loop
(paren
id|res
)paren
(brace
id|tres
op_assign
id|res
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|tres
)paren
suffix:semicolon
)brace
)brace
DECL|function|unload_shpchpd
r_static
r_void
id|__exit
id|unload_shpchpd
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_func
op_star
id|next
suffix:semicolon
r_struct
id|pci_func
op_star
id|TempSlot
suffix:semicolon
r_int
id|loop
suffix:semicolon
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
r_struct
id|controller
op_star
id|tctrl
suffix:semicolon
id|ctrl
op_assign
id|shpchp_ctrl_list
suffix:semicolon
r_while
c_loop
(paren
id|ctrl
)paren
(brace
id|cleanup_slots
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;io_head
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;mem_head
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;p_mem_head
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;bus_head
)paren
suffix:semicolon
id|kfree
(paren
id|ctrl-&gt;pci_bus
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: calling release_ctlr&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ctrl-&gt;hpc_ops
op_member_access_from_pointer
id|release_ctlr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|tctrl
op_assign
id|ctrl
suffix:semicolon
id|ctrl
op_assign
id|ctrl-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|tctrl
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|256
suffix:semicolon
id|loop
op_increment
)paren
(brace
id|next
op_assign
id|shpchp_slot_list
(braket
id|loop
)braket
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
l_int|NULL
)paren
(brace
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;io_head
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;mem_head
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;p_mem_head
)paren
suffix:semicolon
id|free_shpchp_res
c_func
(paren
id|ctrl-&gt;bus_head
)paren
suffix:semicolon
id|TempSlot
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|TempSlot
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Stop the notification mechanism */
id|shpchp_event_stop_thread
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|shpcd_pci_tbl
r_static
r_struct
id|pci_device_id
id|shpcd_pci_tbl
(braket
)braket
op_assign
(brace
(brace
dot
r_class
op_assign
(paren
(paren
id|PCI_CLASS_BRIDGE_PCI
op_lshift
l_int|8
)paren
op_or
l_int|0x00
)paren
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_ANY_ID
comma
dot
id|device
op_assign
id|PCI_ANY_ID
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
multiline_comment|/* end: all zeroes */
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|shpcd_pci_tbl
)paren
suffix:semicolon
DECL|variable|shpc_driver
r_static
r_struct
id|pci_driver
id|shpc_driver
op_assign
(brace
dot
id|name
op_assign
id|SHPC_MODULE_NAME
comma
dot
id|id_table
op_assign
id|shpcd_pci_tbl
comma
dot
id|probe
op_assign
id|shpc_probe
comma
multiline_comment|/* remove:&t;shpc_remove_one, */
)brace
suffix:semicolon
DECL|function|shpcd_init
r_static
r_int
id|__init
id|shpcd_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_PCI_SHPC_POLL_EVENT_MODE
id|shpchp_poll_mode
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|retval
op_assign
id|shpc_start_thread
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|error_hpc_init
suffix:semicolon
id|retval
op_assign
id|shpchprm_init
c_func
(paren
id|PCI
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|retval
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|shpc_driver
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: pci_module_init = %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
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
)brace
id|error_hpc_init
suffix:colon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|shpchprm_cleanup
c_func
(paren
)paren
suffix:semicolon
id|shpchp_event_stop_thread
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|shpchprm_print_pirt
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|shpcd_cleanup
r_static
r_void
id|__exit
id|shpcd_cleanup
c_func
(paren
r_void
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;unload_shpchpd()&bslash;n&quot;
)paren
suffix:semicolon
id|unload_shpchpd
c_func
(paren
)paren
suffix:semicolon
id|shpchprm_cleanup
c_func
(paren
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;pci_unregister_driver&bslash;n&quot;
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|shpc_driver
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; version: &quot;
id|DRIVER_VERSION
l_string|&quot; unloaded&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|shpcd_init
id|module_init
c_func
(paren
id|shpcd_init
)paren
suffix:semicolon
DECL|variable|shpcd_cleanup
id|module_exit
c_func
(paren
id|shpcd_cleanup
)paren
suffix:semicolon
eof
