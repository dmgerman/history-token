multiline_comment|/*&n; * PCI Hot Plug Controller Driver for RPA-compliant PPC64 platform.&n; * Copyright (C) 2003 Linda Xie &lt;lxie@us.ibm.com&gt;&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;lxie@us.ibm.com&gt;&n; *&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &quot;../pci.h&quot;&t;&t;/* for pci_add_new_bus */
macro_line|#include &quot;rpaphp.h&quot;
DECL|function|rpaphp_find_pci_dev
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
(brace
r_struct
id|pci_dev
op_star
id|retval_dev
op_assign
l_int|NULL
comma
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_char
id|bus_id
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|bus_id
comma
l_string|&quot;%04x:%02x:%02x.%d&quot;
comma
id|dn-&gt;phb-&gt;global_number
comma
id|dn-&gt;busno
comma
id|PCI_SLOT
c_func
(paren
id|dn-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dn-&gt;devfn
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|bus_id
)paren
)paren
(brace
id|retval_dev
op_assign
id|dev
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|retval_dev
suffix:semicolon
)brace
DECL|variable|rpaphp_find_pci_dev
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|rpaphp_find_pci_dev
)paren
suffix:semicolon
DECL|function|rpaphp_claim_resource
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
(brace
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|dev-&gt;resource
(braket
id|resource
)braket
suffix:semicolon
r_struct
id|resource
op_star
id|root
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|res
)paren
suffix:semicolon
r_char
op_star
id|dtype
op_assign
id|resource
OL
id|PCI_BRIDGE_RESOURCES
ques
c_cond
l_string|&quot;device&quot;
suffix:colon
l_string|&quot;bridge&quot;
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|root
op_ne
l_int|NULL
)paren
(brace
id|err
op_assign
id|request_resource
c_func
(paren
id|root
comma
id|res
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|err
c_func
(paren
l_string|&quot;PCI: %s region %d of %s %s [%lx:%lx]&bslash;n&quot;
comma
id|root
ques
c_cond
l_string|&quot;Address space collision on&quot;
suffix:colon
l_string|&quot;No parent found for&quot;
comma
id|resource
comma
id|dtype
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|res-&gt;start
comma
id|res-&gt;end
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|rpaphp_claim_resource
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|rpaphp_claim_resource
)paren
suffix:semicolon
DECL|function|rpaphp_find_bridge_pdev
r_static
r_struct
id|pci_dev
op_star
id|rpaphp_find_bridge_pdev
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_return
id|rpaphp_find_pci_dev
c_func
(paren
id|slot-&gt;dn
)paren
suffix:semicolon
)brace
DECL|function|rpaphp_get_sensor_state
r_static
r_int
id|rpaphp_get_sensor_state
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_int
op_star
id|state
)paren
(brace
r_int
id|rc
suffix:semicolon
r_int
id|setlevel
suffix:semicolon
id|rc
op_assign
id|rtas_get_sensor
c_func
(paren
id|DR_ENTITY_SENSE
comma
id|slot-&gt;index
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
r_if
c_cond
(paren
id|rc
op_eq
id|NEED_POWER
op_logical_or
id|rc
op_eq
id|PWR_ONLY
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s: slot must be power up to get sensor-state&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* some slots have to be powered up &n;&t;&t;&t; * before get-sensor will succeed.&n;&t;&t;&t; */
id|rc
op_assign
id|rtas_set_power_level
c_func
(paren
id|slot-&gt;power_domain
comma
id|POWER_ON
comma
op_amp
id|setlevel
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
l_string|&quot;%s: power on slot[%s] failed rc=%d.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
comma
id|rc
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
id|rtas_get_sensor
c_func
(paren
id|DR_ENTITY_SENSE
comma
id|slot-&gt;index
comma
id|state
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|rc
op_eq
id|ERR_SENSE_USE
)paren
id|info
c_func
(paren
l_string|&quot;%s: slot is unusable&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_else
id|err
c_func
(paren
l_string|&quot;%s failed to get sensor state&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; * get_pci_adapter_status - get the status of a slot&n; * &n; * 0-- slot is empty&n; * 1-- adapter is configured&n; * 2-- adapter is not configured&n; * 3-- not valid&n; */
DECL|function|rpaphp_get_pci_adapter_status
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
(brace
r_int
id|state
comma
id|rc
suffix:semicolon
op_star
id|value
op_assign
id|NOT_VALID
suffix:semicolon
id|rc
op_assign
id|rpaphp_get_sensor_state
c_func
(paren
id|slot
comma
op_amp
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
m_exit
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
id|PRESENT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_init
)paren
multiline_comment|/* at run-time slot-&gt;state can be changed by */
multiline_comment|/* config/unconfig adapter */
op_star
id|value
op_assign
id|slot-&gt;state
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;dn-&gt;child
)paren
id|dbg
c_func
(paren
l_string|&quot;%s: %s is not valid OFDT node&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;dn-&gt;full_name
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rpaphp_find_pci_dev
c_func
(paren
id|slot-&gt;dn-&gt;child
)paren
)paren
op_star
id|value
op_assign
id|CONFIGURED
suffix:semicolon
r_else
(brace
id|err
c_func
(paren
l_string|&quot;%s: can&squot;t find pdev of adapter in slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;dn-&gt;full_name
)paren
suffix:semicolon
op_star
id|value
op_assign
id|NOT_CONFIGURED
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|EMPTY
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;slot is empty&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|value
op_assign
id|state
suffix:semicolon
)brace
m_exit
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* Must be called before pci_bus_add_devices */
r_static
r_void
DECL|function|rpaphp_fixup_new_pci_devices
id|rpaphp_fixup_new_pci_devices
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|fix_bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
multiline_comment|/*&n;&t;&t; * Skip already-present devices (which are on the&n;&t;&t; * global device list.)&n;&t;&t; */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|dev-&gt;global_list
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|fix_bus
)paren
(brace
id|pcibios_fixup_device_resources
c_func
(paren
id|dev
comma
id|bus
)paren
suffix:semicolon
)brace
id|pci_read_irq_line
c_func
(paren
id|dev
)paren
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
id|PCI_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;parent
op_logical_or
op_logical_neg
id|r-&gt;start
op_logical_or
op_logical_neg
id|r-&gt;flags
)paren
r_continue
suffix:semicolon
id|rpaphp_claim_resource
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_static
r_int
id|rpaphp_pci_config_bridge
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************&n; rpaphp_pci_config_slot() will  configure all devices under the &n; given slot-&gt;dn and return the the first pci_dev.&n; *****************************************************************************/
r_static
r_struct
id|pci_dev
op_star
DECL|function|rpaphp_pci_config_slot
id|rpaphp_pci_config_slot
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|device_node
op_star
id|eads_first_child
op_assign
id|dn-&gt;child
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|num
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Enter %s: dn=%s bus=%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dn-&gt;full_name
comma
id|bus-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eads_first_child
)paren
(brace
multiline_comment|/* pci_scan_slot should find all children of EADs */
id|num
op_assign
id|pci_scan_slot
c_func
(paren
id|bus
comma
id|PCI_DEVFN
c_func
(paren
id|PCI_SLOT
c_func
(paren
id|eads_first_child-&gt;devfn
)paren
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
)paren
(brace
id|rpaphp_fixup_new_pci_devices
c_func
(paren
id|bus
comma
l_int|1
)paren
suffix:semicolon
id|pci_bus_add_devices
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
id|dev
op_assign
id|rpaphp_find_pci_dev
c_func
(paren
id|eads_first_child
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|err
c_func
(paren
l_string|&quot;No new device found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_BRIDGE
)paren
id|rpaphp_pci_config_bridge
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
)brace
DECL|function|rpaphp_pci_config_bridge
r_static
r_int
id|rpaphp_pci_config_bridge
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|sec_busno
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child_bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|child_dev
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Enter %s:  BRIDGE dev=%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/* get busno of downstream bus */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_SECONDARY_BUS
comma
op_amp
id|sec_busno
)paren
suffix:semicolon
multiline_comment|/* add to children of PCI bridge dev-&gt;bus */
id|child_bus
op_assign
id|pci_add_new_bus
c_func
(paren
id|dev-&gt;bus
comma
id|dev
comma
id|sec_busno
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child_bus
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: could not add second bus&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|child_bus-&gt;name
comma
l_string|&quot;PCI Bus #%02x&quot;
comma
id|child_bus-&gt;number
)paren
suffix:semicolon
multiline_comment|/* do pci_scan_child_bus */
id|pci_scan_child_bus
c_func
(paren
id|child_bus
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|child_dev
comma
op_amp
id|child_bus-&gt;devices
comma
id|bus_list
)paren
(brace
id|eeh_add_device_late
c_func
(paren
id|child_dev
)paren
suffix:semicolon
)brace
multiline_comment|/* fixup new pci devices without touching bus struct */
id|rpaphp_fixup_new_pci_devices
c_func
(paren
id|child_bus
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Make the discovered devices available */
id|pci_bus_add_devices
c_func
(paren
id|child_bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|enable_eeh
r_static
r_void
id|enable_eeh
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_struct
id|device_node
op_star
id|sib
suffix:semicolon
r_for
c_loop
(paren
id|sib
op_assign
id|dn-&gt;child
suffix:semicolon
id|sib
suffix:semicolon
id|sib
op_assign
id|sib-&gt;sibling
)paren
id|enable_eeh
c_func
(paren
id|sib
)paren
suffix:semicolon
id|eeh_add_device_early
c_func
(paren
id|dn
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
DECL|function|print_slot_pci_funcs
r_static
r_void
id|print_slot_pci_funcs
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_struct
id|list_head
op_star
id|l
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;dev_type
op_eq
id|PCI_DEV
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci_funcs of slot[%s]&bslash;n&quot;
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|slot-&gt;dev.pci_funcs
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&t;pci_funcs is EMPTY&bslash;n&quot;
)paren
suffix:semicolon
id|list_for_each
(paren
id|l
comma
op_amp
id|slot-&gt;dev.pci_funcs
)paren
(brace
r_struct
id|rpaphp_pci_func
op_star
id|func
op_assign
id|list_entry
c_func
(paren
id|l
comma
r_struct
id|rpaphp_pci_func
comma
id|sibling
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&t;FOUND dev=%s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|func-&gt;pci_dev
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
macro_line|#else
DECL|function|print_slot_pci_funcs
r_static
r_void
id|print_slot_pci_funcs
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
DECL|function|init_slot_pci_funcs
r_static
r_int
id|init_slot_pci_funcs
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_struct
id|device_node
op_star
id|child
suffix:semicolon
r_for
c_loop
(paren
id|child
op_assign
id|slot-&gt;dn-&gt;child
suffix:semicolon
id|child
op_ne
l_int|NULL
suffix:semicolon
id|child
op_assign
id|child-&gt;sibling
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|rpaphp_find_pci_dev
c_func
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
(brace
r_struct
id|rpaphp_pci_func
op_star
id|func
suffix:semicolon
id|func
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|rpaphp_pci_func
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|func
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|func
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rpaphp_pci_func
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|func-&gt;sibling
)paren
suffix:semicolon
id|func-&gt;pci_dev
op_assign
id|pdev
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|func-&gt;sibling
comma
op_amp
id|slot-&gt;dev.pci_funcs
)paren
suffix:semicolon
id|print_slot_pci_funcs
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
c_func
(paren
l_string|&quot;%s: dn=%s has no pci_dev&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|child-&gt;full_name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rpaphp_config_pci_adapter
r_static
r_int
id|rpaphp_config_pci_adapter
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_struct
id|pci_bus
op_star
id|pci_bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Entry %s: slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;bridge
)paren
(brace
id|pci_bus
op_assign
id|slot-&gt;bridge-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_bus
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: can&squot;t find bus structure&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|enable_eeh
c_func
(paren
id|slot-&gt;dn
)paren
suffix:semicolon
id|dev
op_assign
id|rpaphp_pci_config_slot
c_func
(paren
id|slot-&gt;dn
comma
id|pci_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: can&squot;t find any devices.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* associate corresponding pci_dev */
id|rc
op_assign
id|init_slot_pci_funcs
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
m_exit
suffix:semicolon
id|print_slot_pci_funcs
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|slot-&gt;dev.pci_funcs
)paren
)paren
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* slot is not enabled */
id|err
c_func
(paren
l_string|&quot;slot doesn&squot;t have pci_dev structure&bslash;n&quot;
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Exit %s:  rc=%d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|rc
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|rpaphp_eeh_remove_bus_device
r_static
r_void
id|rpaphp_eeh_remove_bus_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|eeh_remove_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_BRIDGE
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|dev-&gt;subordinate
suffix:semicolon
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|ln
op_assign
id|bus-&gt;devices.next
suffix:semicolon
id|ln
op_ne
op_amp
id|bus-&gt;devices
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
id|rpaphp_eeh_remove_bus_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
DECL|function|rpaphp_unconfig_pci_adapter
r_int
id|rpaphp_unconfig_pci_adapter
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
id|list_head
op_star
id|ln
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Entry %s: slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|slot-&gt;dev.pci_funcs
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: slot[%s] doesn&squot;t have any devices.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* remove the devices from the pci core */
id|list_for_each
(paren
id|ln
comma
op_amp
id|slot-&gt;dev.pci_funcs
)paren
(brace
r_struct
id|rpaphp_pci_func
op_star
id|func
suffix:semicolon
id|func
op_assign
id|list_entry
c_func
(paren
id|ln
comma
r_struct
id|rpaphp_pci_func
comma
id|sibling
)paren
suffix:semicolon
r_if
c_cond
(paren
id|func-&gt;pci_dev
)paren
(brace
id|rpaphp_eeh_remove_bus_device
c_func
(paren
id|func-&gt;pci_dev
)paren
suffix:semicolon
id|pci_remove_bus_device
c_func
(paren
id|func-&gt;pci_dev
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|func
)paren
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|slot-&gt;dev.pci_funcs
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s: devices in slot[%s] unconfigured.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Exit %s, rc=0x%x&bslash;n&quot;
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
DECL|function|setup_pci_hotplug_slot_info
r_static
r_int
id|setup_pci_hotplug_slot_info
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s Initilize the PCI slot&squot;s hotplug-&gt;info structure ...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|rpaphp_get_power_status
c_func
(paren
id|slot
comma
op_amp
id|slot-&gt;hotplug_slot-&gt;info-&gt;power_status
)paren
suffix:semicolon
id|rpaphp_get_pci_adapter_status
c_func
(paren
id|slot
comma
l_int|1
comma
op_amp
id|slot-&gt;hotplug_slot-&gt;info
op_member_access_from_pointer
id|adapter_status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;hotplug_slot-&gt;info-&gt;adapter_status
op_eq
id|NOT_VALID
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: NOT_VALID: skip dn-&gt;full_name=%s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;dn-&gt;full_name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_pci_slot
r_static
r_int
id|setup_pci_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
id|slot-&gt;bridge
op_assign
id|rpaphp_find_bridge_pdev
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot-&gt;bridge
)paren
(brace
multiline_comment|/* slot being added doesn&squot;t have pci_dev yet */
id|err
c_func
(paren
l_string|&quot;%s: no pci_dev for bridge dn %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_goto
id|exit_rc
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;%s set slot-&gt;name to %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pci_name
c_func
(paren
id|slot-&gt;bridge
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|slot-&gt;name
comma
id|pci_name
c_func
(paren
id|slot-&gt;bridge
)paren
)paren
suffix:semicolon
multiline_comment|/* find slot&squot;s pci_dev if it&squot;s not empty */
r_if
c_cond
(paren
id|slot-&gt;hotplug_slot-&gt;info-&gt;adapter_status
op_eq
id|EMPTY
)paren
(brace
id|slot-&gt;state
op_assign
id|EMPTY
suffix:semicolon
multiline_comment|/* slot is empty */
)brace
r_else
(brace
multiline_comment|/* slot is occupied */
r_if
c_cond
(paren
op_logical_neg
(paren
id|slot-&gt;dn-&gt;child
)paren
)paren
(brace
multiline_comment|/* non-empty slot has to have child */
id|err
c_func
(paren
l_string|&quot;%s: slot[%s]&squot;s device_node doesn&squot;t have child for adapter&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_goto
id|exit_rc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|init_slot_pci_funcs
c_func
(paren
id|slot
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;%s: init_slot_pci_funcs failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|exit_rc
suffix:semicolon
)brace
id|print_slot_pci_funcs
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|slot-&gt;dev.pci_funcs
)paren
)paren
(brace
id|slot-&gt;state
op_assign
id|CONFIGURED
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* DLPAR add as opposed to &n;&t;&t; &t; * boot time */
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|exit_rc
suffix:colon
id|dealloc_slot_struct
c_func
(paren
id|slot
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|register_pci_slot
r_int
id|register_pci_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
)paren
(brace
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;dev_type
op_assign
id|PCI_DEV
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;type
op_eq
id|EMBEDDED
)paren
id|slot-&gt;removable
op_assign
id|EMBEDDED
suffix:semicolon
r_else
id|slot-&gt;removable
op_assign
id|HOTPLUG
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|slot-&gt;dev.pci_funcs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setup_pci_hotplug_slot_info
c_func
(paren
id|slot
)paren
)paren
r_goto
id|exit_rc
suffix:semicolon
r_if
c_cond
(paren
id|setup_pci_slot
c_func
(paren
id|slot
)paren
)paren
r_goto
id|exit_rc
suffix:semicolon
id|rc
op_assign
id|register_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
id|exit_rc
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|rpaphp_enable_pci_slot
r_int
id|rpaphp_enable_pci_slot
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
comma
id|state
suffix:semicolon
id|retval
op_assign
id|rpaphp_get_sensor_state
c_func
(paren
id|slot
comma
op_amp
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: sensor state[%d]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|state
)paren
suffix:semicolon
multiline_comment|/* if slot is not empty, enable the adapter */
r_if
c_cond
(paren
id|state
op_eq
id|PRESENT
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s : slot[%s] is occupied.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|retval
op_assign
id|rpaphp_config_pci_adapter
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|slot-&gt;state
op_assign
id|CONFIGURED
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: PCI devices in slot[%s] has been configured&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: no pci_dev struct for adapter in slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|EMPTY
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;%s : slot[%s] is empty&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|EMPTY
suffix:semicolon
)brace
r_else
(brace
id|err
c_func
(paren
l_string|&quot;%s: slot[%s] is in invalid state&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|NOT_VALID
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
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
DECL|function|rpaphp_find_hotplug_slot
r_struct
id|hotplug_slot
op_star
id|rpaphp_find_hotplug_slot
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
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
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
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
id|bus
op_assign
id|slot-&gt;bridge-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* shouldn&squot;t be here */
r_for
c_loop
(paren
id|ln
op_assign
id|bus-&gt;devices.next
suffix:semicolon
id|ln
op_ne
op_amp
id|bus-&gt;devices
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_eq
id|dev
)paren
r_return
id|slot-&gt;hotplug_slot
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|rpaphp_find_hotplug_slot
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|rpaphp_find_hotplug_slot
)paren
suffix:semicolon
eof
