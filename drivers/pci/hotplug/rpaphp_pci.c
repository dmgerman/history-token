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
id|dbg
c_func
(paren
l_string|&quot;Enter rpaphp_find_pci_dev() full_name=%s bus_id=%s&bslash;n&quot;
comma
id|dn-&gt;full_name
comma
id|bus_id
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
id|dbg
c_func
(paren
l_string|&quot;rpaphp_find_pci_dev(): found dev=%p&bslash;n&bslash;n&quot;
comma
id|dev
)paren
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
DECL|function|rpaphp_find_adapter_pdev
r_static
r_struct
id|pci_dev
op_star
id|rpaphp_find_adapter_pdev
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
id|slot-&gt;dn-&gt;child
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
id|dbg
c_func
(paren
l_string|&quot;%s: can&squot;t find pdev of adapter in slot[%s]&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
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
DECL|function|rpaphp_fixup_new_pci_devices
r_static
r_void
id|rpaphp_fixup_new_pci_devices
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
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
id|pcibios_fixup_device_resources
c_func
(paren
id|dev
comma
id|bus
)paren
suffix:semicolon
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
r_void
DECL|function|rpaphp_pci_config_device
id|rpaphp_pci_config_device
c_func
(paren
r_struct
id|pci_bus
op_star
id|pci_bus
comma
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_int
id|num
suffix:semicolon
id|num
op_assign
id|pci_scan_slot
c_func
(paren
id|pci_bus
comma
id|PCI_DEVFN
c_func
(paren
id|PCI_SLOT
c_func
(paren
id|dn-&gt;devfn
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
id|pci_bus
)paren
suffix:semicolon
id|pci_bus_add_devices
c_func
(paren
id|pci_bus
)paren
suffix:semicolon
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
comma
r_struct
id|device_node
op_star
id|dn
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************&n; rpaphp_pci_config_dn() will recursively configure all devices under the &n; given slot-&gt;dn and return the dn&squot;s pci_dev.&n; *****************************************************************************/
r_static
r_struct
id|pci_dev
op_star
DECL|function|rpaphp_pci_config_dn
id|rpaphp_pci_config_dn
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
id|local
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|local
op_assign
id|dn-&gt;child
suffix:semicolon
id|local
suffix:semicolon
id|local
op_assign
id|local-&gt;sibling
)paren
(brace
id|rpaphp_pci_config_device
c_func
(paren
id|bus
comma
id|local
)paren
suffix:semicolon
id|dev
op_assign
id|rpaphp_find_pci_dev
c_func
(paren
id|local
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rpaphp_pci_config_bridge
c_func
(paren
id|dev
comma
id|local
)paren
)paren
r_return
l_int|NULL
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
comma
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_if
c_cond
(paren
id|dev
op_logical_and
id|dn-&gt;child
)paren
(brace
multiline_comment|/* dn is a PCI bridge node */
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
id|u8
id|sec_busno
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
id|child
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
id|child
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
l_int|0
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|child-&gt;name
comma
l_string|&quot;PCI Bus #%02x&quot;
comma
id|child-&gt;number
)paren
suffix:semicolon
multiline_comment|/* Fixup subordinate bridge bases and resureces */
id|pcibios_fixup_bus
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/* may need do more stuff here */
id|rpaphp_pci_config_dn
c_func
(paren
id|dn
comma
id|dev-&gt;subordinate
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|rpaphp_config_pci_adapter
r_static
r_struct
id|pci_dev
op_star
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
op_assign
l_int|NULL
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
id|eeh_add_device_early
c_func
(paren
id|slot-&gt;dn-&gt;child
)paren
suffix:semicolon
id|dev
op_assign
id|rpaphp_pci_config_dn
c_func
(paren
id|slot-&gt;dn
comma
id|pci_bus
)paren
suffix:semicolon
id|eeh_add_device_late
c_func
(paren
id|dev
)paren
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
id|dev
op_assign
l_int|NULL
suffix:semicolon
)brace
m_exit
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;Exit %s: pci_dev %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev
ques
c_cond
l_string|&quot;found&quot;
suffix:colon
l_string|&quot;not found&quot;
)paren
suffix:semicolon
r_return
id|dev
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
op_logical_neg
id|slot-&gt;dev.pci_dev
)paren
(brace
id|info
c_func
(paren
l_string|&quot;%s: no card in slot[%s]&bslash;n&quot;
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
multiline_comment|/* remove the device from the pci core */
id|eeh_remove_device
c_func
(paren
id|slot-&gt;dev.pci_dev
)paren
suffix:semicolon
id|pci_remove_bus_device
c_func
(paren
id|slot-&gt;dev.pci_dev
)paren
suffix:semicolon
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;%s: adapter in slot[%s] unconfigured.&bslash;n&quot;
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
id|dbg
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
id|dbg
c_func
(paren
l_string|&quot;%s: no pci_dev for bridge dn %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
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
id|slot-&gt;dev.pci_dev
op_assign
l_int|NULL
suffix:semicolon
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
id|slot-&gt;dev.pci_dev
op_assign
id|rpaphp_find_adapter_pdev
c_func
(paren
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;dev.pci_dev
)paren
(brace
id|slot-&gt;state
op_assign
id|CONFIGURED
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* DLPAR add as opposed to &n;&t;&t;&t; * boot time */
id|slot-&gt;state
op_assign
id|NOT_CONFIGURED
suffix:semicolon
)brace
)brace
r_return
l_int|0
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
r_if
c_cond
(paren
id|rc
)paren
id|dealloc_slot_struct
c_func
(paren
id|slot
)paren
suffix:semicolon
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
l_string|&quot;%s : slot[%s] is occupid.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slot-&gt;dev.pci_dev
op_assign
id|rpaphp_config_pci_adapter
c_func
(paren
id|slot
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|slot-&gt;state
op_assign
id|CONFIGURED
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;%s: PCI adapter %s in slot[%s] has been configured&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|pci_name
c_func
(paren
id|slot-&gt;dev.pci_dev
)paren
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
r_if
c_cond
(paren
id|slot-&gt;state
op_ne
id|NOT_VALID
)paren
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_ON
)paren
suffix:semicolon
r_else
id|rpaphp_set_attention_status
c_func
(paren
id|slot
comma
id|LED_ID
)paren
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
eof
