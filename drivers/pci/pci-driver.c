multiline_comment|/*&n; * drivers/pci/pci-driver.c&n; *&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/pci-dynids.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; *  Registration of PCI drivers and handling of hot-pluggable devices.&n; */
multiline_comment|/**&n; * pci_match_one_device - Tell if a PCI device structure has a matching&n; *                        PCI device id structure&n; * @id: single PCI device id structure to match&n; * @dev: the PCI device structure to match against&n; * &n; * Returns the matching pci_device_id structure or %NULL if there is no match.&n; */
r_static
r_inline
r_const
r_struct
id|pci_device_id
op_star
DECL|function|pci_match_one_device
id|pci_match_one_device
c_func
(paren
r_const
r_struct
id|pci_device_id
op_star
id|id
comma
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
(paren
id|id-&gt;vendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|id-&gt;vendor
op_eq
id|dev-&gt;vendor
)paren
op_logical_and
(paren
id|id-&gt;device
op_eq
id|PCI_ANY_ID
op_logical_or
id|id-&gt;device
op_eq
id|dev-&gt;device
)paren
op_logical_and
(paren
id|id-&gt;subvendor
op_eq
id|PCI_ANY_ID
op_logical_or
id|id-&gt;subvendor
op_eq
id|dev-&gt;subsystem_vendor
)paren
op_logical_and
(paren
id|id-&gt;subdevice
op_eq
id|PCI_ANY_ID
op_logical_or
id|id-&gt;subdevice
op_eq
id|dev-&gt;subsystem_device
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|id
op_member_access_from_pointer
r_class
op_xor
id|dev
op_member_access_from_pointer
r_class
)paren
op_amp
id|id-&gt;class_mask
)paren
)paren
r_return
id|id
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_match_device - Tell if a PCI device structure has a matching&n; *                    PCI device id structure&n; * @ids: array of PCI device id structures to search in&n; * @dev: the PCI device structure to match against&n; * &n; * Used by a driver to check whether a PCI device present in the&n; * system is in its list of supported devices.Returns the matching&n; * pci_device_id structure or %NULL if there is no match.&n; */
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
id|pci_match_one_device
c_func
(paren
id|ids
comma
id|dev
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
multiline_comment|/**&n; * pci_device_probe_static()&n; * &n; * returns 0 and sets pci_dev-&gt;driver when drv claims pci_dev, else error.&n; */
r_static
r_int
DECL|function|pci_device_probe_static
id|pci_device_probe_static
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
comma
r_struct
id|pci_dev
op_star
id|pci_dev
)paren
(brace
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_const
r_struct
id|pci_device_id
op_star
id|id
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv-&gt;id_table
)paren
r_return
id|error
suffix:semicolon
id|id
op_assign
id|pci_match_device
c_func
(paren
id|drv-&gt;id_table
comma
id|pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
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
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
(brace
id|pci_dev-&gt;driver
op_assign
id|drv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_device_probe_dynamic()&n; * &n; * Walk the dynamic ID list looking for a match.&n; * returns 0 and sets pci_dev-&gt;driver when drv claims pci_dev, else error.&n; */
r_static
r_int
DECL|function|pci_device_probe_dynamic
id|pci_device_probe_dynamic
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
comma
r_struct
id|pci_dev
op_star
id|pci_dev
)paren
(brace
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|dynid
op_star
id|dynid
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|drv-&gt;dynids.lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|drv-&gt;dynids.list
)paren
(brace
id|dynid
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|dynid
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_match_one_device
c_func
(paren
op_amp
id|dynid-&gt;id
comma
id|pci_dev
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|drv-&gt;dynids.lock
)paren
suffix:semicolon
id|error
op_assign
id|drv
op_member_access_from_pointer
id|probe
c_func
(paren
id|pci_dev
comma
op_amp
id|dynid-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
(brace
id|pci_dev-&gt;driver
op_assign
id|drv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|drv-&gt;dynids.lock
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * __pci_device_probe()&n; * &n; * returns 0  on success, else error.&n; * side-effect: pci_dev-&gt;driver is set to drv when drv claims pci_dev.&n; */
r_static
r_int
DECL|function|__pci_device_probe
id|__pci_device_probe
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
comma
r_struct
id|pci_dev
op_star
id|pci_dev
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_dev-&gt;driver
op_logical_and
id|drv-&gt;probe
)paren
(brace
id|error
op_assign
id|pci_device_probe_static
c_func
(paren
id|drv
comma
id|pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|pci_device_probe_dynamic
c_func
(paren
id|drv
comma
id|pci_dev
)paren
suffix:semicolon
)brace
r_return
id|error
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
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
id|drv
op_assign
id|to_pci_driver
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
id|pci_dev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_get_dev
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
id|error
op_assign
id|__pci_device_probe
c_func
(paren
id|drv
comma
id|pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|pci_put_dev
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_return
id|error
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
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pci_driver
op_star
id|drv
op_assign
id|pci_dev-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
(brace
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
id|pci_dev-&gt;driver
op_assign
l_int|NULL
suffix:semicolon
)brace
id|pci_put_dev
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
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
id|to_pci_dev
c_func
(paren
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
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_dev-&gt;driver
)paren
(brace
multiline_comment|/* We may not call PCI drivers resume at&n;&t;&t;   RESUME_POWER_ON because interrupts are not yet&n;&t;&t;   working at that point. Calling resume at&n;&t;&t;   RESUME_RESTORE_STATE seems like solution. */
r_if
c_cond
(paren
id|level
op_eq
id|RESUME_RESTORE_STATE
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
r_static
r_inline
r_void
DECL|function|dynid_init
id|dynid_init
c_func
(paren
r_struct
id|dynid
op_star
id|dynid
)paren
(brace
id|memset
c_func
(paren
id|dynid
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dynid
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dynid-&gt;node
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * store_new_id&n; * @ pdrv&n; * @ buf&n; * @ count&n; *&n; * Adds a new dynamic pci device ID to this driver,&n; * and causes the driver to probe for all devices again.&n; */
r_static
r_inline
id|ssize_t
DECL|function|store_new_id
id|store_new_id
c_func
(paren
r_struct
id|device_driver
op_star
id|driver
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|dynid
op_star
id|dynid
suffix:semicolon
r_struct
id|bus_type
op_star
id|bus
suffix:semicolon
r_struct
id|pci_driver
op_star
id|pdrv
op_assign
id|to_pci_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
id|__u32
id|vendor
op_assign
id|PCI_ANY_ID
comma
id|device
op_assign
id|PCI_ANY_ID
comma
id|subvendor
op_assign
id|PCI_ANY_ID
comma
id|subdevice
op_assign
id|PCI_ANY_ID
comma
r_class
op_assign
l_int|0
comma
id|class_mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|driver_data
op_assign
l_int|0
suffix:semicolon
r_int
id|fields
op_assign
l_int|0
suffix:semicolon
id|fields
op_assign
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%x %x %x %x %x %x %lux&quot;
comma
op_amp
id|vendor
comma
op_amp
id|device
comma
op_amp
id|subvendor
comma
op_amp
id|subdevice
comma
op_amp
r_class
comma
op_amp
id|class_mask
comma
op_amp
id|driver_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fields
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dynid
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dynid
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dynid
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dynid_init
c_func
(paren
id|dynid
)paren
suffix:semicolon
id|dynid-&gt;id.vendor
op_assign
id|vendor
suffix:semicolon
id|dynid-&gt;id.device
op_assign
id|device
suffix:semicolon
id|dynid-&gt;id.subvendor
op_assign
id|subvendor
suffix:semicolon
id|dynid-&gt;id.subdevice
op_assign
id|subdevice
suffix:semicolon
id|dynid-&gt;id
dot
r_class
op_assign
r_class
suffix:semicolon
id|dynid-&gt;id.class_mask
op_assign
id|class_mask
suffix:semicolon
id|dynid-&gt;id.driver_data
op_assign
id|pdrv-&gt;dynids.use_driver_data
ques
c_cond
id|driver_data
suffix:colon
l_int|0UL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pdrv-&gt;dynids.lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|pdrv-&gt;dynids.list
comma
op_amp
id|dynid-&gt;node
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|pdrv-&gt;dynids.lock
)paren
suffix:semicolon
id|bus
op_assign
id|get_bus
c_func
(paren
id|pdrv-&gt;driver.bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus
)paren
(brace
r_if
c_cond
(paren
id|get_driver
c_func
(paren
op_amp
id|pdrv-&gt;driver
)paren
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|driver_attach
c_func
(paren
op_amp
id|pdrv-&gt;driver
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|bus-&gt;subsys.rwsem
)paren
suffix:semicolon
id|put_driver
c_func
(paren
op_amp
id|pdrv-&gt;driver
)paren
suffix:semicolon
)brace
id|put_bus
c_func
(paren
id|bus
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
id|DRIVER_ATTR
c_func
(paren
id|new_id
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|store_new_id
)paren
suffix:semicolon
DECL|macro|kobj_to_pci_driver
mdefine_line|#define kobj_to_pci_driver(obj) container_of(obj, struct device_driver, kobj)
DECL|macro|attr_to_driver_attribute
mdefine_line|#define attr_to_driver_attribute(obj) container_of(obj, struct driver_attribute, attr)
r_static
id|ssize_t
DECL|function|pci_driver_attr_show
id|pci_driver_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|device_driver
op_star
id|driver
op_assign
id|kobj_to_pci_driver
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|driver_attribute
op_star
id|dattr
op_assign
id|attr_to_driver_attribute
c_func
(paren
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_driver
c_func
(paren
id|driver
)paren
)paren
(brace
r_if
c_cond
(paren
id|dattr-&gt;show
)paren
id|ret
op_assign
id|dattr
op_member_access_from_pointer
id|show
c_func
(paren
id|driver
comma
id|buf
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|pci_driver_attr_store
id|pci_driver_attr_store
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|device_driver
op_star
id|driver
op_assign
id|kobj_to_pci_driver
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|driver_attribute
op_star
id|dattr
op_assign
id|attr_to_driver_attribute
c_func
(paren
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|get_driver
c_func
(paren
id|driver
)paren
)paren
(brace
r_if
c_cond
(paren
id|dattr-&gt;store
)paren
id|ret
op_assign
id|dattr
op_member_access_from_pointer
id|store
c_func
(paren
id|driver
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|put_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|pci_driver_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|pci_driver_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|pci_driver_attr_show
comma
dot
id|store
op_assign
id|pci_driver_attr_store
comma
)brace
suffix:semicolon
DECL|variable|pci_driver_kobj_type
r_static
r_struct
id|kobj_type
id|pci_driver_kobj_type
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|pci_driver_sysfs_ops
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|pci_populate_driver_dir
id|pci_populate_driver_dir
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;probe
op_ne
l_int|NULL
)paren
id|error
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|drv-&gt;driver.kobj
comma
op_amp
id|driver_attr_new_id.attr
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|pci_init_dynids
id|pci_init_dynids
c_func
(paren
r_struct
id|pci_dynids
op_star
id|dynids
)paren
(brace
id|memset
c_func
(paren
id|dynids
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dynids
)paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dynids-&gt;lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dynids-&gt;list
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pci_free_dynids
id|pci_free_dynids
c_func
(paren
r_struct
id|pci_driver
op_star
id|drv
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|n
suffix:semicolon
r_struct
id|dynid
op_star
id|dynid
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|drv-&gt;dynids.lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|n
comma
op_amp
id|drv-&gt;dynids.list
)paren
(brace
id|dynid
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|dynid
comma
id|node
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dynid-&gt;node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dynid
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|drv-&gt;dynids.lock
)paren
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
id|drv-&gt;driver.kobj.ktype
op_assign
op_amp
id|pci_driver_kobj_type
suffix:semicolon
id|pci_init_dynids
c_func
(paren
op_amp
id|drv-&gt;dynids
)paren
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
r_if
c_cond
(paren
id|count
op_ge
l_int|0
)paren
(brace
id|pci_populate_driver_dir
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
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
id|driver_unregister
c_func
(paren
op_amp
id|drv-&gt;driver
)paren
suffix:semicolon
id|pci_free_dynids
c_func
(paren
id|drv
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
dot
id|name
op_assign
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
multiline_comment|/**&n; * pci_bus_match - Tell if a PCI device structure has a matching PCI device id structure&n; * @ids: array of PCI device id structures to search in&n; * @dev: the PCI device structure to match against&n; * &n; * Used by a driver to check whether a PCI device present in the&n; * system is in its list of supported devices.Returns the matching&n; * pci_device_id structure or %NULL if there is no match.&n; */
DECL|function|pci_bus_match
r_static
r_int
id|pci_bus_match
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
r_const
r_struct
id|pci_dev
op_star
id|pci_dev
op_assign
id|to_pci_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|pci_driver
op_star
id|pci_drv
op_assign
id|to_pci_driver
c_func
(paren
id|drv
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
r_const
r_struct
id|pci_device_id
op_star
id|found_id
suffix:semicolon
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|dynid
op_star
id|dynid
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
id|found_id
op_assign
id|pci_match_device
c_func
(paren
id|ids
comma
id|pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found_id
)paren
r_return
l_int|1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|pci_drv-&gt;dynids.lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|pos
comma
op_amp
id|pci_drv-&gt;dynids.list
)paren
(brace
id|dynid
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|dynid
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_match_one_device
c_func
(paren
op_amp
id|dynid-&gt;id
comma
id|pci_dev
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|pci_drv-&gt;dynids.lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|pci_drv-&gt;dynids.lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_get_dev - increments the reference count of the pci device structure&n; * @dev: the device being referenced&n; *&n; * Each live reference to a device should be refcounted.&n; *&n; * Drivers for PCI devices should normally record such references in&n; * their probe() methods, when they bind to a device, and release&n; * them by calling pci_put_dev(), in their disconnect() methods.&n; *&n; * A pointer to the device with the incremented reference counter is returned.&n; */
DECL|function|pci_get_dev
r_struct
id|pci_dev
op_star
id|pci_get_dev
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|device
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|get_device
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
r_return
id|to_pci_dev
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_put_dev - release a use of the pci device structure&n; * @dev: device that&squot;s been disconnected&n; *&n; * Must be called when a user of a device is finished with it.  When the last&n; * user of the device calls this function, the memory of the device is freed.&n; */
DECL|function|pci_put_dev
r_void
id|pci_put_dev
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
id|dev
)paren
id|put_device
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|variable|pci_bus_type
r_struct
id|bus_type
id|pci_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pci&quot;
comma
dot
id|match
op_assign
id|pci_bus_match
comma
dot
id|hotplug
op_assign
id|pci_hotplug
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
id|postcore_initcall
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
DECL|variable|pci_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_type
)paren
suffix:semicolon
DECL|variable|pci_get_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pci_get_dev
)paren
suffix:semicolon
DECL|variable|pci_put_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pci_put_dev
)paren
suffix:semicolon
eof
