multiline_comment|/*&n; * RPA Virtual I/O device functions &n; * Copyright (C) 2004 Linda Xie &lt;lxie@us.ibm.com&gt;&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;lxie@us.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;rpaphp.h&quot;
DECL|function|location_read_file
r_static
id|ssize_t
id|location_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|php_slot
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|value
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
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
id|php_slot
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot
)paren
r_return
id|retval
suffix:semicolon
id|value
op_assign
id|slot-&gt;location
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_location
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_location
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;phy_location&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
)brace
comma
dot
id|show
op_assign
id|location_read_file
comma
)brace
suffix:semicolon
DECL|function|rpaphp_sysfs_add_attr_location
r_static
r_void
id|rpaphp_sysfs_add_attr_location
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
(brace
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_location.attr
)paren
suffix:semicolon
)brace
DECL|function|rpaphp_sysfs_remove_attr_location
r_void
id|rpaphp_sysfs_remove_attr_location
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
(brace
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_location.attr
)paren
suffix:semicolon
)brace
multiline_comment|/* free up the memory user by a slot */
DECL|function|rpaphp_release_slot
r_static
r_void
id|rpaphp_release_slot
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
ques
c_cond
(paren
r_struct
id|slot
op_star
)paren
id|hotplug_slot
op_member_access_from_pointer
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|dealloc_slot_struct
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
DECL|function|dealloc_slot_struct
r_void
id|dealloc_slot_struct
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
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
r_return
suffix:semicolon
)brace
DECL|function|alloc_slot_struct
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
(brace
r_struct
id|slot
op_star
id|slot
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Enter alloc_slot_struct(): dn-&gt;full_name=%s drc_index=0x%x drc_name=%s&bslash;n&quot;
comma
id|dn-&gt;full_name
comma
id|drc_index
comma
id|drc_name
)paren
suffix:semicolon
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
r_return
(paren
l_int|NULL
)paren
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
(brace
id|kfree
c_func
(paren
id|slot
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
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
(brace
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
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
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
id|BUS_ID_SIZE
op_plus
l_int|1
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
(brace
id|kfree
c_func
(paren
id|slot-&gt;hotplug_slot-&gt;info
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
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|slot-&gt;location
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|drc_name
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;location
)paren
(brace
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
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|slot-&gt;name
op_assign
id|slot-&gt;hotplug_slot-&gt;name
suffix:semicolon
id|slot-&gt;dn
op_assign
id|dn
suffix:semicolon
id|slot-&gt;index
op_assign
id|drc_index
suffix:semicolon
id|strcpy
c_func
(paren
id|slot-&gt;location
comma
id|drc_name
)paren
suffix:semicolon
id|slot-&gt;power_domain
op_assign
id|power_domain
suffix:semicolon
id|slot-&gt;magic
op_assign
id|SLOT_MAGIC
suffix:semicolon
id|slot-&gt;hotplug_slot
op_member_access_from_pointer
r_private
op_assign
id|slot
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;ops
op_assign
op_amp
id|rpaphp_hotplug_slot_ops
suffix:semicolon
id|slot-&gt;hotplug_slot-&gt;release
op_assign
op_amp
id|rpaphp_release_slot
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Exit alloc_slot_struct(): slot-&gt;dn-&gt;full_name=%s drc_index=0x%x drc_name=%s&bslash;n&quot;
comma
id|slot-&gt;dn-&gt;full_name
comma
id|slot-&gt;index
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_return
(paren
id|slot
)paren
suffix:semicolon
)brace
DECL|function|register_slot
r_int
id|register_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_int
id|retval
suffix:semicolon
r_char
op_star
id|vio_uni_addr
op_assign
l_int|NULL
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s registering slot:path[%s] index[%x], name[%s] pdomain[%x] type[%d]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;dn-&gt;full_name
comma
id|slot-&gt;index
comma
id|slot-&gt;name
comma
id|slot-&gt;power_domain
comma
id|slot-&gt;type
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
id|rpaphp_release_slot
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
r_return
(paren
id|retval
)paren
suffix:semicolon
)brace
multiline_comment|/* create &quot;phy_locatoin&quot; file */
id|rpaphp_sysfs_add_attr_location
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
multiline_comment|/* add slot to our internal list */
id|dbg
c_func
(paren
l_string|&quot;%s adding slot[%s] to rpaphp_slot_list&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|slot-&gt;rpaphp_slot_list
comma
op_amp
id|rpaphp_slot_head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vio_uni_addr
)paren
id|info
c_func
(paren
l_string|&quot;Slot [%s](vio_uni_addr=%s) registered&bslash;n&quot;
comma
id|slot-&gt;name
comma
id|vio_uni_addr
)paren
suffix:semicolon
r_else
id|info
c_func
(paren
l_string|&quot;Slot [%s](bus_id=%s) registered&bslash;n&quot;
comma
id|slot-&gt;name
comma
id|pci_name
c_func
(paren
id|slot-&gt;bridge
)paren
)paren
suffix:semicolon
id|num_slots
op_increment
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|rpaphp_get_power_status
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
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|rtas_get_power_level
c_func
(paren
id|slot-&gt;power_domain
comma
(paren
r_int
op_star
)paren
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|err
c_func
(paren
l_string|&quot;failed to get power-level for slot(%s), rc=0x%x&bslash;n&quot;
comma
id|slot-&gt;name
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|rpaphp_set_attention_status
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
(brace
r_int
id|rc
suffix:semicolon
multiline_comment|/* status: LED_OFF or LED_ON */
id|rc
op_assign
id|rtas_set_indicator
c_func
(paren
id|DR_INDICATOR
comma
id|slot-&gt;index
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
id|err
c_func
(paren
l_string|&quot;slot(%s) set attention-status(%d) failed! rc=0x%x&bslash;n&quot;
comma
id|slot-&gt;name
comma
id|status
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
