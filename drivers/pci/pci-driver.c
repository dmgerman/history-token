multiline_comment|/*&n; * drivers/pci/pci-driver.c&n; *&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; *  Registration of PCI drivers and handling of hot-pluggable devices.&n; */
multiline_comment|/**&n; * pci_match_device - Tell if a PCI device structure has a matching PCI device id structure&n; * @ids: array of PCI device id structures to search in&n; * @dev: the PCI device structure to match against&n; * &n; * Used by a driver to check whether a PCI device present in the&n; * system is in its list of supported devices.Returns the matching&n; * pci_device_id structure or %NULL if there is no match.&n; */
r_const
r_struct
id|pci_device_id
op_star
DECL|function|pci_match_device
id|pci_match_device
c_func
(paren
r_const
r_struct
id|pci_device_id
op_star
id|ids
comma
r_const
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_while
c_loop
(paren
id|ids-&gt;vendor
op_logical_or
id|ids-&gt;subvendor
op_logical_or
id|ids-&gt;class_mask
)paren
(brace
r_if
c_cond
(paren
(paren
id|ids-&gt;vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;vendor
op_eq
id|dev-&gt;vendor
)paren
op_logical_and
(paren
id|ids-&gt;device
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;device
op_eq
id|dev-&gt;device
)paren
op_logical_and
(paren
id|ids-&gt;subvendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;subvendor
op_eq
id|dev-&gt;subsystem_vendor
)paren
op_logical_and
(paren
id|ids-&gt;subdevice
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;subdevice
op_eq
id|dev-&gt;subsystem_device
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|ids
op_member_access_from_pointer
r_class
op_xor
id|dev
op_member_access_from_pointer
r_class
)paren
op_amp
id|ids-&gt;class_mask
)paren
)paren
r_return
id|ids
suffix:semicolon
id|ids
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pci_device_probe
r_static
r_int
id|pci_device_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_driver
op_star
id|drv
op_assign
id|list_entry
c_func
(paren
id|dev-&gt;driver
comma
r_struct
id|pci_driver
comma
id|driver
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
id|list_entry
c_func
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;probe
)paren
id|error
op_assign
id|drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|pci_dev
comma
id|drv-&gt;id_table
)paren
suffix:semicolon
r_return
id|error
OG
l_int|0
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|pci_device_remove
r_static
r_int
id|pci_device_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|flags
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
id|list_entry
c_func
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;driver
)paren
(brace
r_struct
id|pci_driver
op_star
id|drv
op_assign
id|list_entry
c_func
(paren
id|dev-&gt;driver
comma
r_struct
id|pci_driver
comma
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;remove
)paren
id|drv
op_member_access_from_pointer
id|remove
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_device_suspend
r_static
r_int
id|pci_device_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
(paren
r_struct
id|pci_dev
op_star
)paren
id|list_entry
c_func
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev-&gt;driver
)paren
(brace
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_SAVE_STATE
op_logical_and
id|pci_dev-&gt;driver-&gt;save_state
)paren
id|error
op_assign
id|pci_dev-&gt;driver
op_member_access_from_pointer
id|save_state
c_func
(paren
id|pci_dev
comma
id|state
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|level
op_eq
id|SUSPEND_POWER_DOWN
op_logical_and
id|pci_dev-&gt;driver-&gt;suspend
)paren
id|error
op_assign
id|pci_dev-&gt;driver
op_member_access_from_pointer
id|suspend
c_func
(paren
id|pci_dev
comma
id|state
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|pci_device_resume
r_static
r_int
id|pci_device_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
(paren
r_struct
id|pci_dev
op_star
)paren
id|list_entry
c_func
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev-&gt;driver
)paren
(brace
r_if
c_cond
(paren
id|level
op_eq
id|RESUME_POWER_ON
op_logical_and
id|pci_dev-&gt;driver-&gt;resume
)paren
id|pci_dev-&gt;driver
op_member_access_from_pointer
id|resume
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_register_driver - register a new pci driver&n; * @drv: the driver structure to register&n; * &n; * Adds the driver structure to the list of registered drivers&n; * Returns the number of pci devices which were claimed by the driver&n; * during registration.  The driver remains registered even if the&n; * return value is zero.&n; */
r_int
DECL|function|pci_register_driver
id|pci_register_driver
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* initialize common driver fields */
id|drv-&gt;driver.name
op_assign
id|drv-&gt;name
suffix:semicolon
id|drv-&gt;driver.bus
op_assign
op_amp
id|pci_bus_type
suffix:semicolon
id|drv-&gt;driver.probe
op_assign
id|pci_device_probe
suffix:semicolon
id|drv-&gt;driver.resume
op_assign
id|pci_device_resume
suffix:semicolon
id|drv-&gt;driver.suspend
op_assign
id|pci_device_suspend
suffix:semicolon
id|drv-&gt;driver.remove
op_assign
id|pci_device_remove
suffix:semicolon
multiline_comment|/* register with core */
id|count
op_assign
id|driver_register
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
r_return
id|count
ques
c_cond
id|count
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_unregister_driver - unregister a pci driver&n; * @drv: the driver structure to unregister&n; * &n; * Deletes the driver structure from the list of registered PCI drivers,&n; * gives it a chance to clean up by calling its remove() function for&n; * each device it was responsible for, and marks those devices as&n; * driverless.&n; */
r_void
DECL|function|pci_unregister_driver
id|pci_unregister_driver
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
id|put_driver
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
)brace
DECL|variable|pci_compat_driver
r_static
r_struct
id|pci_driver
id|pci_compat_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;compat&quot;
)brace
suffix:semicolon
multiline_comment|/**&n; * pci_dev_driver - get the pci_driver of a device&n; * @dev: the device to query&n; *&n; * Returns the appropriate pci_driver structure or %NULL if there is no &n; * registered driver for the device.&n; */
r_struct
id|pci_driver
op_star
DECL|function|pci_dev_driver
id|pci_dev_driver
c_func
(paren
r_const
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;driver
)paren
r_return
id|dev-&gt;driver
suffix:semicolon
r_else
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
op_le
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_BUSY
)paren
r_return
op_amp
id|pci_compat_driver
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_bus_bind - Tell if a PCI device structure has a matching PCI device id structure&n; * @ids: array of PCI device id structures to search in&n; * @dev: the PCI device structure to match against&n; * &n; * Used by a driver to check whether a PCI device present in the&n; * system is in its list of supported devices.Returns the matching&n; * pci_device_id structure or %NULL if there is no match.&n; */
DECL|function|pci_bus_bind
r_static
r_int
id|pci_bus_bind
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
id|list_entry
c_func
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
r_struct
id|pci_driver
op_star
id|pci_drv
op_assign
id|list_entry
c_func
(paren
id|drv
comma
r_struct
id|pci_driver
comma
id|driver
)paren
suffix:semicolon
r_const
r_struct
id|pci_device_id
op_star
id|ids
op_assign
id|pci_drv-&gt;id_table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ids
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ids-&gt;vendor
op_logical_or
id|ids-&gt;subvendor
op_logical_or
id|ids-&gt;class_mask
)paren
(brace
r_if
c_cond
(paren
(paren
id|ids-&gt;vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;vendor
op_eq
id|pci_dev-&gt;vendor
)paren
op_logical_and
(paren
id|ids-&gt;device
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;device
op_eq
id|pci_dev-&gt;device
)paren
op_logical_and
(paren
id|ids-&gt;subvendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;subvendor
op_eq
id|pci_dev-&gt;subsystem_vendor
)paren
op_logical_and
(paren
id|ids-&gt;subdevice
op_eq
id|PCI_ANY_ID
op_logical_or
id|ids-&gt;subdevice
op_eq
id|pci_dev-&gt;subsystem_device
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|ids
op_member_access_from_pointer
r_class
op_xor
id|pci_dev
op_member_access_from_pointer
r_class
)paren
op_amp
id|ids-&gt;class_mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|ids
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_bus_type
r_struct
id|bus_type
id|pci_bus_type
op_assign
(brace
id|name
suffix:colon
l_string|&quot;pci&quot;
comma
id|bind
suffix:colon
id|pci_bus_bind
comma
)brace
suffix:semicolon
DECL|function|pci_driver_init
r_static
r_int
id|__init
id|pci_driver_init
c_func
(paren
r_void
)paren
(brace
r_return
id|bus_register
c_func
(paren
op_amp
id|pci_bus_type
)paren
suffix:semicolon
)brace
DECL|variable|pci_driver_init
id|subsys_initcall
c_func
(paren
id|pci_driver_init
)paren
suffix:semicolon
DECL|variable|pci_match_device
id|EXPORT_SYMBOL
c_func
(paren
id|pci_match_device
)paren
suffix:semicolon
DECL|variable|pci_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pci_register_driver
)paren
suffix:semicolon
DECL|variable|pci_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pci_unregister_driver
)paren
suffix:semicolon
DECL|variable|pci_dev_driver
id|EXPORT_SYMBOL
c_func
(paren
id|pci_dev_driver
)paren
suffix:semicolon
eof
