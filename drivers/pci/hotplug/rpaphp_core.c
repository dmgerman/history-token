multiline_comment|/*&n; * PCI Hot Plug Controller Driver for RPA-compliant PPC64 platform.&n; * Copyright (C) 2003 Linda Xie &lt;lxie@us.ibm.com&gt;&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;lxie@us.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/eeh.h&gt;       /* for eeh_add_device() */
macro_line|#include &lt;asm/rtas.h&gt;&t;&t;/* rtas_call */
macro_line|#include &lt;asm/pci-bridge.h&gt;&t;/* for pci_controller */
macro_line|#include &quot;../pci.h&quot;&t;&t;/* for pci_add_new_bus */
multiline_comment|/* and pci_do_scan_bus */
macro_line|#include &quot;rpaphp.h&quot;
macro_line|#include &quot;pci_hotplug.h&quot;
DECL|variable|debug
r_int
id|debug
suffix:semicolon
DECL|variable|rpaphp_sem
r_static
r_struct
id|semaphore
id|rpaphp_sem
suffix:semicolon
DECL|variable|rpaphp_slot_head
id|LIST_HEAD
c_func
(paren
id|rpaphp_slot_head
)paren
suffix:semicolon
DECL|variable|num_slots
r_int
id|num_slots
suffix:semicolon
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.1&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Linda Xie &lt;lxie@us.ibm.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;RPA HOT Plug PCI Controller Driver&quot;
DECL|macro|MAX_LOC_CODE
mdefine_line|#define MAX_LOC_CODE 128
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
r_static
r_int
id|enable_slot
c_func
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
c_func
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
c_func
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
c_func
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
c_func
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
c_func
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
c_func
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
suffix:semicolon
DECL|variable|rpaphp_hotplug_slot_ops
r_struct
id|hotplug_slot_ops
id|rpaphp_hotplug_slot_ops
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
id|get_attention_status
op_assign
id|get_attention_status
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
)brace
suffix:semicolon
DECL|function|rpaphp_get_attention_status
r_static
r_int
id|rpaphp_get_attention_status
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_return
id|slot-&gt;hotplug_slot-&gt;info-&gt;attention_status
suffix:semicolon
)brace
multiline_comment|/**&n; * set_attention_status - set attention LED&n; * echo 0 &gt; attention -- set LED OFF&n; * echo 1 &gt; attention -- set LED ON&n; * echo 2 &gt; attention -- set LED ID(identify, light is blinking)&n; *&n; */
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
id|value
)paren
(brace
r_int
id|retval
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
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
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
id|retval
op_assign
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_OFF
)paren
suffix:semicolon
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
id|retval
op_assign
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_ON
)paren
suffix:semicolon
id|hotplug_slot-&gt;info-&gt;attention_status
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|retval
op_assign
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_ID
)paren
suffix:semicolon
id|hotplug_slot-&gt;info-&gt;attention_status
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * get_power_status - get power status of a slot&n; * @hotplug_slot: slot to get status&n; * @value: pointer to store status&n; *&n; *&n; */
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
r_int
id|retval
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
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
id|retval
op_assign
id|rpaphp_get_power_status
c_func
(paren
id|slot
comma
id|value
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * get_attention_status - get attention LED status&n; *&n; *&n; */
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
r_int
id|retval
op_assign
l_int|0
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
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
op_star
id|value
op_assign
id|rpaphp_get_attention_status
c_func
(paren
id|slot
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
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
(paren
r_struct
id|slot
op_star
)paren
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
multiline_comment|/*  have to go through this */
r_switch
c_cond
(paren
id|slot-&gt;dev_type
)paren
(brace
r_case
id|PCI_DEV
suffix:colon
id|retval
op_assign
id|rpaphp_get_pci_adapter_status
c_func
(paren
id|slot
comma
l_int|0
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIO_DEV
suffix:colon
id|retval
op_assign
id|rpaphp_get_vio_adapter_status
c_func
(paren
id|slot
comma
l_int|0
comma
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|get_max_bus_speed
r_static
r_int
id|get_max_bus_speed
c_func
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
(paren
r_struct
id|slot
op_star
)paren
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|slot-&gt;type
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
op_star
id|value
op_assign
id|PCI_SPEED_33MHz
suffix:semicolon
multiline_comment|/* speed for case 1-6 */
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
r_case
l_int|8
suffix:colon
op_star
id|value
op_assign
id|PCI_SPEED_66MHz
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
r_case
l_int|14
suffix:colon
op_star
id|value
op_assign
id|PCI_SPEED_66MHz_PCIX
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
r_case
l_int|15
suffix:colon
op_star
id|value
op_assign
id|PCI_SPEED_100MHz_PCIX
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
r_case
l_int|16
suffix:colon
op_star
id|value
op_assign
id|PCI_SPEED_133MHz_PCIX
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|value
op_assign
id|PCI_SPEED_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpaphp_remove_slot
r_int
id|rpaphp_remove_slot
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
op_assign
l_int|0
suffix:semicolon
r_struct
id|hotplug_slot
op_star
id|php_slot
op_assign
id|slot-&gt;hotplug_slot
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|slot-&gt;rpaphp_slot_list
)paren
suffix:semicolon
multiline_comment|/* remove &quot;php_location&quot; file */
id|rpaphp_sysfs_remove_attr_location
c_func
(paren
id|php_slot
)paren
suffix:semicolon
id|retval
op_assign
id|pci_hp_deregister
c_func
(paren
id|php_slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|err
c_func
(paren
l_string|&quot;Problem unregistering a slot %s&bslash;n&quot;
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|num_slots
op_decrement
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - Exit: rc[%d]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|is_php_dn
r_static
r_int
id|is_php_dn
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
op_star
op_star
id|indexes
comma
r_int
op_star
op_star
id|names
comma
r_int
op_star
op_star
id|types
comma
r_int
op_star
op_star
id|power_domains
)paren
(brace
op_star
id|indexes
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,drc-indexes&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|indexes
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* &amp;names[1] contains NULL terminated slot names */
op_star
id|names
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,drc-names&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|names
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* &amp;types[1] contains NULL terminated slot types */
op_star
id|types
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,drc-types&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|types
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* power_domains[1...n] are the slot power domains */
op_star
id|power_domains
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,drc-power-domains&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|power_domains
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|dn-&gt;name
comma
l_string|&quot;pci&quot;
)paren
op_eq
l_int|0
op_logical_and
op_logical_neg
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,fw-pci-hot-plug-ctrl&quot;
comma
l_int|NULL
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|is_vdevice_root
r_static
r_inline
r_int
id|is_vdevice_root
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_return
op_logical_neg
id|strcmp
c_func
(paren
id|dn-&gt;name
comma
l_string|&quot;vdevice&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * rpaphp_add_slot: Add  Hot Plug slot(s) to sysfs&n; *&n; */
DECL|function|rpaphp_add_slot
r_int
id|rpaphp_add_slot
c_func
(paren
r_struct
id|device_node
op_star
id|dn
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
r_int
op_star
id|indexes
comma
op_star
id|names
comma
op_star
id|types
comma
op_star
id|power_domains
suffix:semicolon
r_char
op_star
id|name
comma
op_star
id|type
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Entry %s: dn-&gt;full_name=%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dn-&gt;full_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn-&gt;parent
op_logical_and
id|is_vdevice_root
c_func
(paren
id|dn-&gt;parent
)paren
)paren
(brace
multiline_comment|/* register a VIO device */
id|retval
op_assign
id|register_vio_slot
c_func
(paren
id|dn
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* register PCI devices */
r_if
c_cond
(paren
id|dn-&gt;name
op_ne
l_int|0
op_logical_and
id|strcmp
c_func
(paren
id|dn-&gt;name
comma
l_string|&quot;pci&quot;
)paren
op_eq
l_int|0
op_logical_and
id|is_php_dn
c_func
(paren
id|dn
comma
op_amp
id|indexes
comma
op_amp
id|names
comma
op_amp
id|types
comma
op_amp
id|power_domains
)paren
)paren
(brace
id|name
op_assign
(paren
r_char
op_star
)paren
op_amp
id|names
(braket
l_int|1
)braket
suffix:semicolon
id|type
op_assign
(paren
r_char
op_star
)paren
op_amp
id|types
(braket
l_int|1
)braket
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
id|indexes
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
comma
id|name
op_add_assign
(paren
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
)paren
comma
id|type
op_add_assign
(paren
id|strlen
c_func
(paren
id|type
)paren
op_plus
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot
op_assign
id|alloc_slot_struct
c_func
(paren
id|dn
comma
id|indexes
(braket
id|i
op_plus
l_int|1
)braket
comma
id|name
comma
id|power_domains
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|slot-&gt;type
op_assign
id|simple_strtoul
c_func
(paren
id|type
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;type
template_param
l_int|16
)paren
id|slot-&gt;type
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|register_pci_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
multiline_comment|/* for indexes */
)brace
multiline_comment|/* end of PCI device_node */
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Exit: num_slots=%d rc[%d]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|num_slots
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|init_rpa
r_static
r_int
id|__init
id|init_rpa
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
multiline_comment|/* initialize internal data structure etc. */
r_for
c_loop
(paren
id|dn
op_assign
id|find_all_nodes
c_func
(paren
)paren
suffix:semicolon
id|dn
suffix:semicolon
id|dn
op_assign
id|dn-&gt;next
)paren
id|rpaphp_add_slot
c_func
(paren
id|dn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_slots
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
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
comma
op_star
id|n
suffix:semicolon
r_struct
id|slot
op_star
id|slot
suffix:semicolon
multiline_comment|/*&n;&t; * Unregister all of our slots with the pci_hotplug subsystem,&n;&t; * and free up all memory that we had allocated.&n;&t; * memory will be freed in release_slot callback. &n;&t; */
id|list_for_each_safe
c_func
(paren
id|tmp
comma
id|n
comma
op_amp
id|rpaphp_slot_head
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
id|rpaphp_slot_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|slot-&gt;rpaphp_slot_list
)paren
suffix:semicolon
id|pci_hp_deregister
c_func
(paren
id|slot-&gt;hotplug_slot
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|rpaphp_init
r_static
r_int
id|__init
id|rpaphp_init
c_func
(paren
r_void
)paren
(brace
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot; version: &quot;
id|DRIVER_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* read all the PRA info from the system */
r_return
id|init_rpa
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rpaphp_exit
r_static
r_void
id|__exit
id|rpaphp_exit
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
)brace
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
r_int
id|retval
op_assign
l_int|0
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
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;state
op_eq
id|CONFIGURED
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: %s is already enabled&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;ENABLING SLOT %s&bslash;n&quot;
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|slot-&gt;dev_type
)paren
(brace
r_case
id|PCI_DEV
suffix:colon
id|retval
op_assign
id|rpaphp_enable_pci_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIO_DEV
suffix:colon
id|retval
op_assign
id|rpaphp_enable_vio_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Exit: rc[%d]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
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
r_int
id|retval
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
id|hotplug_slot
op_member_access_from_pointer
r_private
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s - Entry: slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;state
op_eq
id|NOT_CONFIGURED
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: %s is already disabled&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;DISABLING SLOT %s&bslash;n&quot;
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|slot-&gt;dev_type
)paren
(brace
r_case
id|PCI_DEV
suffix:colon
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_ID
)paren
suffix:semicolon
id|retval
op_assign
id|rpaphp_unconfig_pci_adapter
c_func
(paren
id|slot
)paren
suffix:semicolon
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_OFF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIO_DEV
suffix:colon
id|retval
op_assign
id|rpaphp_unconfig_vio_adapter
c_func
(paren
id|slot
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
)brace
id|up
c_func
(paren
op_amp
id|rpaphp_sem
)paren
suffix:semicolon
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;%s - Exit: rc[%d]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|rpaphp_init
id|module_init
c_func
(paren
id|rpaphp_init
)paren
suffix:semicolon
DECL|variable|rpaphp_exit
id|module_exit
c_func
(paren
id|rpaphp_exit
)paren
suffix:semicolon
DECL|variable|rpaphp_add_slot
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|rpaphp_add_slot
)paren
suffix:semicolon
DECL|variable|rpaphp_remove_slot
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|rpaphp_remove_slot
)paren
suffix:semicolon
DECL|variable|rpaphp_slot_head
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|rpaphp_slot_head
)paren
suffix:semicolon
eof
