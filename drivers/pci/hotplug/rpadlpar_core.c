multiline_comment|/*&n; * Interface for Dynamic Logical Partitioning of I/O Slots on&n; * RPA-compliant PPC64 platform.&n; *&n; * John Rose &lt;johnrose@austin.ibm.com&gt;&n; * Linda Xie &lt;lxie@us.ibm.com&gt;&n; *&n; * October 2003&n; *&n; * Copyright (C) 2003 IBM.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;../pci.h&quot;
macro_line|#include &quot;rpaphp.h&quot;
macro_line|#include &quot;rpadlpar.h&quot;
r_static
id|DECLARE_MUTEX
c_func
(paren
id|rpadlpar_sem
)paren
suffix:semicolon
DECL|function|find_php_slot_vio_node
r_static
r_struct
id|device_node
op_star
id|find_php_slot_vio_node
c_func
(paren
r_char
op_star
id|drc_name
)paren
(brace
r_struct
id|device_node
op_star
id|child
suffix:semicolon
r_struct
id|device_node
op_star
id|parent
op_assign
id|of_find_node_by_name
c_func
(paren
l_int|NULL
comma
l_string|&quot;vdevice&quot;
)paren
suffix:semicolon
r_char
op_star
id|loc_code
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|child
op_assign
id|of_get_next_child
c_func
(paren
id|parent
comma
l_int|NULL
)paren
suffix:semicolon
id|child
suffix:semicolon
id|child
op_assign
id|of_get_next_child
c_func
(paren
id|parent
comma
id|child
)paren
)paren
(brace
id|loc_code
op_assign
id|get_property
c_func
(paren
id|child
comma
l_string|&quot;ibm,loc-code&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loc_code
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|loc_code
comma
id|drc_name
comma
id|strlen
c_func
(paren
id|drc_name
)paren
)paren
)paren
r_return
id|child
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|find_php_slot_pci_node
r_static
r_struct
id|device_node
op_star
id|find_php_slot_pci_node
c_func
(paren
r_char
op_star
id|drc_name
)paren
(brace
r_struct
id|device_node
op_star
id|np
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_while
c_loop
(paren
(paren
id|np
op_assign
id|of_find_node_by_type
c_func
(paren
id|np
comma
l_string|&quot;pci&quot;
)paren
)paren
)paren
r_if
c_cond
(paren
id|is_hotplug_capable
c_func
(paren
id|np
)paren
)paren
(brace
id|name
op_assign
id|rpaphp_get_drc_name
c_func
(paren
id|np
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
op_logical_and
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|drc_name
comma
id|name
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|np
suffix:semicolon
)brace
DECL|function|find_slot
r_static
r_struct
id|slot
op_star
id|find_slot
c_func
(paren
r_char
op_star
id|drc_name
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
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|slot-&gt;location
comma
id|drc_name
)paren
op_eq
l_int|0
)paren
r_return
id|slot
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|rpadlpar_claim_one_bus
r_static
r_void
id|rpadlpar_claim_one_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
r_struct
id|list_head
op_star
id|ld
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child_bus
suffix:semicolon
r_for
c_loop
(paren
id|ld
op_assign
id|b-&gt;devices.next
suffix:semicolon
id|ld
op_ne
op_amp
id|b-&gt;devices
suffix:semicolon
id|ld
op_assign
id|ld-&gt;next
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|ld
)paren
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
id|list_for_each_entry
c_func
(paren
id|child_bus
comma
op_amp
id|b-&gt;children
comma
id|node
)paren
id|rpadlpar_claim_one_bus
c_func
(paren
id|child_bus
)paren
suffix:semicolon
)brace
DECL|function|pci_add_secondary_bus
r_static
r_int
id|pci_add_secondary_bus
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_struct
id|pci_dev
op_star
id|bridge_dev
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dn-&gt;phb
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child
suffix:semicolon
id|u8
id|sec_busno
suffix:semicolon
multiline_comment|/* Get busno of downstream bus */
id|pci_read_config_byte
c_func
(paren
id|bridge_dev
comma
id|PCI_SECONDARY_BUS
comma
op_amp
id|sec_busno
)paren
suffix:semicolon
multiline_comment|/* Allocate and add to children of bridge_dev-&gt;bus */
id|child
op_assign
id|pci_add_new_bus
c_func
(paren
id|bridge_dev-&gt;bus
comma
id|bridge_dev
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: could not add secondary bus&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|1
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
multiline_comment|/* Fixup subordinate bridge bases and resources */
id|pcibios_fixup_bus
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/* Claim new bus resources */
id|rpadlpar_claim_one_bus
c_func
(paren
id|bridge_dev-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;last_busno
OL
id|child-&gt;number
)paren
id|hose-&gt;last_busno
op_assign
id|child-&gt;number
suffix:semicolon
id|dn-&gt;bussubno
op_assign
id|child-&gt;number
suffix:semicolon
multiline_comment|/* ioremap() for child bus */
r_if
c_cond
(paren
id|remap_bus_range
c_func
(paren
id|child
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: could not ioremap() child bus&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlpar_pci_add_bus
r_static
r_struct
id|pci_dev
op_star
id|dlpar_pci_add_bus
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dn-&gt;phb
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Scan phb bus for EADS device, adding new one to bus-&gt;devices */
r_if
c_cond
(paren
op_logical_neg
id|pci_scan_single_device
c_func
(paren
id|hose-&gt;bus
comma
id|dn-&gt;devfn
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: found no device on bus&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Add new devices to global lists.  Register in proc, sysfs. */
id|pci_bus_add_devices
c_func
(paren
id|hose-&gt;bus
)paren
suffix:semicolon
multiline_comment|/* Confirm new bridge dev was created */
id|dev
op_assign
id|rpaphp_find_pci_dev
c_func
(paren
id|dn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to add pci device&bslash;n&quot;
comma
id|__FUNCTION__
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
op_ne
id|PCI_HEADER_TYPE_BRIDGE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unexpected header type %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev-&gt;hdr_type
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_add_secondary_bus
c_func
(paren
id|dn
comma
id|dev
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
DECL|function|dlpar_pci_remove_bus
r_static
r_int
id|dlpar_pci_remove_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|bridge_dev
)paren
(brace
r_struct
id|pci_bus
op_star
id|secondary_bus
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge_dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unexpected null device&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|secondary_bus
op_assign
id|bridge_dev-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
id|unmap_bus_range
c_func
(paren
id|secondary_bus
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to unmap bus range&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|pci_remove_bus_device
c_func
(paren
id|bridge_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dlpar_add_pci_slot
r_static
r_inline
r_int
id|dlpar_add_pci_slot
c_func
(paren
r_char
op_star
id|drc_name
comma
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* Add pci bus */
id|dev
op_assign
id|dlpar_pci_add_bus
c_func
(paren
id|dn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to add bus %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drc_name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * dlpar_add_slot - DLPAR add an I/O Slot&n; * @drc_name: drc-name of newly added slot&n; *&n; * Make the hotplug module and the kernel aware&n; * of a newly added I/O Slot.&n; * Return Codes -&n; * 0&t;&t;&t;Success&n; * -ENODEV&t;&t;Not a valid drc_name&n; * -EINVAL&t;&t;Slot already added&n; * -ERESTARTSYS&t;&t;Signalled before obtaining lock&n; * -EIO&t;&t;&t;Internal PCI Error&n; */
DECL|function|dlpar_add_slot
r_int
id|dlpar_add_slot
c_func
(paren
r_char
op_star
id|drc_name
)paren
(brace
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|rpadlpar_sem
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
multiline_comment|/* Check for existing hotplug slot */
r_if
c_cond
(paren
id|find_slot
c_func
(paren
id|drc_name
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|dn
op_assign
id|find_php_slot_vio_node
c_func
(paren
id|drc_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dn
)paren
(brace
id|dn
op_assign
id|find_php_slot_pci_node
c_func
(paren
id|drc_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
)paren
id|rc
op_assign
id|dlpar_add_pci_slot
c_func
(paren
id|drc_name
comma
id|dn
)paren
suffix:semicolon
r_else
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
multiline_comment|/* Add hotplug slot for new VIOA or PCI */
r_if
c_cond
(paren
op_logical_neg
id|rc
op_logical_and
id|rpaphp_add_slot
c_func
(paren
id|dn
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to add hotplug slot %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drc_name
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
m_exit
suffix:colon
id|up
c_func
(paren
op_amp
id|rpadlpar_sem
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; * dlpar_remove_vio_slot - DLPAR remove a virtual I/O Slot&n; * @drc_name: drc-name of newly added slot&n; *&n; * Remove the kernel and hotplug representations&n; * of an I/O Slot.&n; * Return Codes:&n; * 0&t;&t;&t;Success&n; * -EIO&t;&t;&t;Internal  Error&n; */
DECL|function|dlpar_remove_vio_slot
r_int
id|dlpar_remove_vio_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_char
op_star
id|drc_name
)paren
(brace
multiline_comment|/* Remove hotplug slot */
r_if
c_cond
(paren
id|rpaphp_remove_slot
c_func
(paren
id|slot
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to remove hotplug slot %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drc_name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * dlpar_remove_slot - DLPAR remove a PCI I/O Slot&n; * @drc_name: drc-name of newly added slot&n; *&n; * Remove the kernel and hotplug representations&n; * of a PCI I/O Slot.&n; * Return Codes:&n; * 0&t;&t;&t;Success&n; * -ENODEV&t;&t;Not a valid drc_name&n; * -EIO&t;&t;&t;Internal PCI Error&n; */
DECL|function|dlpar_remove_pci_slot
r_int
id|dlpar_remove_pci_slot
c_func
(paren
r_struct
id|slot
op_star
id|slot
comma
r_char
op_star
id|drc_name
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge_dev
suffix:semicolon
id|bridge_dev
op_assign
id|slot-&gt;bridge
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge_dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unexpected null bridge device&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Remove hotplug slot */
r_if
c_cond
(paren
id|rpaphp_remove_slot
c_func
(paren
id|slot
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to remove hotplug slot %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drc_name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Remove pci bus */
r_if
c_cond
(paren
id|dlpar_pci_remove_bus
c_func
(paren
id|bridge_dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to remove pci bus %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drc_name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * dlpar_remove_slot - DLPAR remove an I/O Slot&n; * @drc_name: drc-name of newly added slot&n; *&n; * Remove the kernel and hotplug representations&n; * of an I/O Slot.&n; * Return Codes:&n; * 0&t;&t;&t;Success&n; * -ENODEV&t;&t;Not a valid drc_name&n; * -EINVAL&t;&t;Slot already removed&n; * -ERESTARTSYS&t;&t;Signalled before obtaining lock&n; * -EIO&t;&t;&t;Internal Error&n; */
DECL|function|dlpar_remove_slot
r_int
id|dlpar_remove_slot
c_func
(paren
r_char
op_star
id|drc_name
)paren
(brace
r_struct
id|slot
op_star
id|slot
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|rpadlpar_sem
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|find_php_slot_vio_node
c_func
(paren
id|drc_name
)paren
op_logical_and
op_logical_neg
id|find_php_slot_pci_node
c_func
(paren
id|drc_name
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|slot
op_assign
id|find_slot
c_func
(paren
id|drc_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|slot
)paren
(brace
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|slot-&gt;dev_type
)paren
(brace
r_case
id|PCI_DEV
suffix:colon
id|rc
op_assign
id|dlpar_remove_pci_slot
c_func
(paren
id|slot
comma
id|drc_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIO_DEV
suffix:colon
id|rc
op_assign
id|dlpar_remove_vio_slot
c_func
(paren
id|slot
comma
id|drc_name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
m_exit
suffix:colon
id|up
c_func
(paren
op_amp
id|rpadlpar_sem
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|is_dlpar_capable
r_static
r_inline
r_int
id|is_dlpar_capable
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,configure-connector&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
id|rc
op_ne
id|RTAS_UNKNOWN_SERVICE
)paren
suffix:semicolon
)brace
DECL|function|rpadlpar_io_init
r_int
id|__init
id|rpadlpar_io_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_dlpar_capable
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: partition not DLPAR capable&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|rc
op_assign
id|dlpar_sysfs_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|rpadlpar_io_exit
r_void
id|rpadlpar_io_exit
c_func
(paren
r_void
)paren
(brace
id|dlpar_sysfs_exit
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|rpadlpar_io_init
id|module_init
c_func
(paren
id|rpadlpar_io_init
)paren
suffix:semicolon
DECL|variable|rpadlpar_io_exit
id|module_exit
c_func
(paren
id|rpadlpar_io_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
