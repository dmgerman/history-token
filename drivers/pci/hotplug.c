macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
r_static
r_void
id|pci_free_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|function|pci_hotplug
r_int
id|pci_hotplug
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
op_star
id|envp
comma
r_int
id|num_envp
comma
r_char
op_star
id|buffer
comma
r_int
id|buffer_size
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_char
op_star
id|scratch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pdev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|scratch
op_assign
id|buffer
suffix:semicolon
multiline_comment|/* stuff we want to pass to /sbin/hotplug */
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|snprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_CLASS=%04X&quot;
comma
id|pdev
op_member_access_from_pointer
r_class
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|scratch
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|snprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_ID=%04X:%04X&quot;
comma
id|pdev-&gt;vendor
comma
id|pdev-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|scratch
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|snprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_SUBSYS_ID=%04X:%04X&quot;
comma
id|pdev-&gt;subsystem_vendor
comma
id|pdev-&gt;subsystem_device
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_increment
id|length
suffix:semicolon
id|scratch
op_add_assign
id|length
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|length
op_add_assign
id|snprintf
(paren
id|scratch
comma
id|buffer_size
op_minus
id|length
comma
l_string|&quot;PCI_SLOT_NAME=%s&quot;
comma
id|pdev-&gt;slot_name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer_size
op_minus
id|length
op_le
l_int|0
)paren
op_logical_or
(paren
id|i
op_ge
id|num_envp
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|envp
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_visit_bus
r_static
r_int
id|pci_visit_bus
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_bus
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pci_dev_wrapped
id|wrapped_dev
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;scanning bus %02x&bslash;n&quot;
comma
id|wrapped_bus-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;pre_visit_pci_bus
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|pre_visit_pci_bus
c_func
(paren
id|wrapped_bus
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
id|ln
op_assign
id|wrapped_bus-&gt;bus-&gt;devices.next
suffix:semicolon
r_while
c_loop
(paren
id|ln
op_ne
op_amp
id|wrapped_bus-&gt;bus-&gt;devices
)paren
(brace
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|wrapped_dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_dev_wrapped
)paren
)paren
suffix:semicolon
id|wrapped_dev.dev
op_assign
id|dev
suffix:semicolon
id|result
op_assign
id|pci_visit_dev
c_func
(paren
id|fn
comma
op_amp
id|wrapped_dev
comma
id|wrapped_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fn-&gt;post_visit_pci_bus
)paren
id|result
op_assign
id|fn
op_member_access_from_pointer
id|post_visit_pci_bus
c_func
(paren
id|wrapped_bus
comma
id|wrapped_parent
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_visit_bridge
r_static
r_int
id|pci_visit_bridge
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|pci_bus_wrapped
id|wrapped_bus
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;scanning bridge %02x, %02x&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|wrapped_dev-&gt;dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|wrapped_dev-&gt;dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
id|bus
op_assign
id|wrapped_dev-&gt;dev-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
id|bus
)paren
(brace
id|memset
c_func
(paren
op_amp
id|wrapped_bus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_bus_wrapped
)paren
)paren
suffix:semicolon
id|wrapped_bus.bus
op_assign
id|bus
suffix:semicolon
id|result
op_assign
id|pci_visit_bus
c_func
(paren
id|fn
comma
op_amp
id|wrapped_bus
comma
id|wrapped_dev
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_visit_dev - scans the pci buses.&n; * Every bus and every function is presented to a custom&n; * function that can act upon it.&n; */
DECL|function|pci_visit_dev
r_int
id|pci_visit_dev
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|wrapped_dev
ques
c_cond
id|wrapped_dev-&gt;dev
suffix:colon
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;pre_visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|pre_visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
(brace
r_case
id|PCI_CLASS_BRIDGE_PCI
suffix:colon
id|result
op_assign
id|pci_visit_bridge
c_func
(paren
id|fn
comma
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|DBG
c_func
(paren
l_string|&quot;scanning device %02x, %02x&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn-&gt;visit_pci_dev
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fn-&gt;post_visit_pci_dev
)paren
id|result
op_assign
id|fn
op_member_access_from_pointer
id|post_visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|pci_visit_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pci_visit_dev
)paren
suffix:semicolon
DECL|function|pci_destroy_dev
r_static
r_void
id|pci_destroy_dev
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_proc_detach_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Remove the device from the device lists, and prevent any further&n;&t; * list accesses from this device */
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;bus_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;global_list
)paren
suffix:semicolon
id|dev-&gt;bus_list.next
op_assign
id|dev-&gt;bus_list.prev
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;global_list.next
op_assign
id|dev-&gt;global_list.prev
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|pci_free_resources
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_remove_device_safe - remove an unused hotplug device&n; * @dev: the device to remove&n; *&n; * Delete the device structure from the device lists and &n; * notify userspace (/sbin/hotplug), but only if the device&n; * in question is not being used by a driver.&n; * Returns 0 on success.&n; */
DECL|function|pci_remove_device_safe
r_int
id|pci_remove_device_safe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|pci_dev_driver
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|pci_destroy_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_remove_device_safe
id|EXPORT_SYMBOL
c_func
(paren
id|pci_remove_device_safe
)paren
suffix:semicolon
r_static
r_void
DECL|function|pci_free_resources
id|pci_free_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
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
id|res
op_assign
id|dev-&gt;resource
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;parent
)paren
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * pci_remove_bus_device - remove a PCI device and any children&n; * @dev: the device to remove&n; *&n; * Remove a PCI device from the device lists, informing the drivers&n; * that the device has been removed.  We also remove any subordinate&n; * buses and children in a depth-first manner.&n; *&n; * For each device we remove, delete the device structure from the&n; * device lists, remove the /proc entry, and notify userspace&n; * (/sbin/hotplug).&n; */
DECL|function|pci_remove_bus_device
r_void
id|pci_remove_bus_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;subordinate
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|dev-&gt;subordinate
suffix:semicolon
id|pci_remove_behind_bridge
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_proc_detach_bus
c_func
(paren
id|b
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|b-&gt;node
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pci_bus_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|b
)paren
suffix:semicolon
id|dev-&gt;subordinate
op_assign
l_int|NULL
suffix:semicolon
)brace
id|pci_destroy_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_remove_behind_bridge - remove all devices behind a PCI bridge&n; * @dev: PCI bridge device&n; *&n; * Remove all devices on the bus, except for the parent bridge.&n; * This also removes any child buses, and any devices they may&n; * contain in a depth-first manner.&n; */
DECL|function|pci_remove_behind_bridge
r_void
id|pci_remove_behind_bridge
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
id|l
comma
op_star
id|n
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;subordinate
)paren
(brace
id|list_for_each_safe
c_func
(paren
id|l
comma
id|n
comma
op_amp
id|dev-&gt;subordinate-&gt;devices
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
id|l
)paren
suffix:semicolon
id|pci_remove_bus_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|pci_remove_bus_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_remove_bus_device
)paren
suffix:semicolon
DECL|variable|pci_remove_behind_bridge
id|EXPORT_SYMBOL
c_func
(paren
id|pci_remove_behind_bridge
)paren
suffix:semicolon
eof
