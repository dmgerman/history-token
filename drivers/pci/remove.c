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
DECL|function|pci_free_resources
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
