multiline_comment|/*&n; * device.h - generic, centralized driver model&n; *&n; * Copyright (c) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; * This is a relatively simple centralized driver model.&n; * The data structures were mainly lifted directly from the PCI&n; * driver model. These are thought to be the common fields that&n; * are relevant to all device buses.&n; *&n; * All the devices are arranged in a tree. All devices should&n; * have some sort of parent bus of whom they are children of.&n; * Devices should not be direct children of the system root.&n; *&n; * Device drivers should not directly call the device_* routines&n; * or access the contents of struct device directly. Instead,&n; * abstract that from the drivers and write bus-specific wrappers&n; * that do it for you.&n; *&n; * See Documentation/driver-model.txt for more information.&n; */
macro_line|#ifndef _DEVICE_H_
DECL|macro|_DEVICE_H_
mdefine_line|#define _DEVICE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|DEVICE_NAME_SIZE
mdefine_line|#define DEVICE_NAME_SIZE&t;50
DECL|macro|DEVICE_NAME_HALF
mdefine_line|#define DEVICE_NAME_HALF&t;__stringify(20)&t;/* Less than half to accommodate slop */
DECL|macro|DEVICE_ID_SIZE
mdefine_line|#define DEVICE_ID_SIZE&t;&t;32
DECL|macro|BUS_ID_SIZE
mdefine_line|#define BUS_ID_SIZE&t;&t;16
r_enum
(brace
DECL|enumerator|SUSPEND_NOTIFY
id|SUSPEND_NOTIFY
comma
DECL|enumerator|SUSPEND_SAVE_STATE
id|SUSPEND_SAVE_STATE
comma
DECL|enumerator|SUSPEND_DISABLE
id|SUSPEND_DISABLE
comma
DECL|enumerator|SUSPEND_POWER_DOWN
id|SUSPEND_POWER_DOWN
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|RESUME_POWER_ON
id|RESUME_POWER_ON
comma
DECL|enumerator|RESUME_RESTORE_STATE
id|RESUME_RESTORE_STATE
comma
DECL|enumerator|RESUME_ENABLE
id|RESUME_ENABLE
comma
)brace
suffix:semicolon
DECL|enum|device_state
r_enum
id|device_state
(brace
DECL|enumerator|DEVICE_UNINITIALIZED
id|DEVICE_UNINITIALIZED
op_assign
l_int|0
comma
DECL|enumerator|DEVICE_INITIALIZED
id|DEVICE_INITIALIZED
op_assign
l_int|1
comma
DECL|enumerator|DEVICE_REGISTERED
id|DEVICE_REGISTERED
op_assign
l_int|2
comma
DECL|enumerator|DEVICE_GONE
id|DEVICE_GONE
op_assign
l_int|3
comma
)brace
suffix:semicolon
r_struct
id|device
suffix:semicolon
r_struct
id|device_driver
suffix:semicolon
r_struct
id|device_class
suffix:semicolon
DECL|struct|bus_type
r_struct
id|bus_type
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|subsys
r_struct
id|subsystem
id|subsys
suffix:semicolon
DECL|member|drvsubsys
r_struct
id|subsystem
id|drvsubsys
suffix:semicolon
DECL|member|devsubsys
r_struct
id|subsystem
id|devsubsys
suffix:semicolon
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
DECL|member|match
r_int
(paren
op_star
id|match
)paren
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
suffix:semicolon
DECL|member|add
r_struct
id|device
op_star
(paren
op_star
id|add
)paren
(paren
r_struct
id|device
op_star
id|parent
comma
r_char
op_star
id|bus_id
)paren
suffix:semicolon
DECL|member|hotplug
r_int
(paren
op_star
id|hotplug
)paren
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
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|bus_register
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|bus_unregister
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_struct
id|bus_type
op_star
id|get_bus
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|put_bus
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* iterator helpers for buses */
r_int
id|bus_for_each_dev
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
comma
r_struct
id|device
op_star
id|start
comma
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|device
op_star
comma
r_void
op_star
)paren
)paren
suffix:semicolon
r_int
id|bus_for_each_drv
c_func
(paren
r_struct
id|bus_type
op_star
id|bus
comma
r_struct
id|device_driver
op_star
id|start
comma
r_void
op_star
id|data
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|device_driver
op_star
comma
r_void
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/* driverfs interface for exporting bus attributes */
DECL|struct|bus_attribute
r_struct
id|bus_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|bus_type
op_star
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|bus_type
op_star
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BUS_ATTR
mdefine_line|#define BUS_ATTR(_name,_mode,_show,_store)&t;&bslash;&n;struct bus_attribute bus_attr_##_name = { &t;&t;&bslash;&n;&t;.attr = {.name = __stringify(_name), .mode = _mode },&t;&bslash;&n;&t;.show&t;= _show,&t;&t;&t;&t;&bslash;&n;&t;.store&t;= _store,&t;&t;&t;&t;&bslash;&n;};
r_extern
r_int
id|bus_create_file
c_func
(paren
r_struct
id|bus_type
op_star
comma
r_struct
id|bus_attribute
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bus_remove_file
c_func
(paren
r_struct
id|bus_type
op_star
comma
r_struct
id|bus_attribute
op_star
)paren
suffix:semicolon
DECL|struct|device_driver
r_struct
id|device_driver
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|bus
r_struct
id|bus_type
op_star
id|bus
suffix:semicolon
DECL|member|devclass
r_struct
id|device_class
op_star
id|devclass
suffix:semicolon
DECL|member|unload_sem
r_struct
id|semaphore
id|unload_sem
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|class_list
r_struct
id|list_head
id|class_list
suffix:semicolon
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|shutdown
r_void
(paren
op_star
id|shutdown
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
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
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|driver_register
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_void
id|driver_unregister
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_struct
id|device_driver
op_star
id|get_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
suffix:semicolon
r_extern
r_void
id|put_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
suffix:semicolon
multiline_comment|/* driverfs interface for exporting driver attributes */
DECL|struct|driver_attribute
r_struct
id|driver_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|device_driver
op_star
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|device_driver
op_star
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DRIVER_ATTR
mdefine_line|#define DRIVER_ATTR(_name,_mode,_show,_store)&t;&bslash;&n;struct driver_attribute driver_attr_##_name = { &t;&t;&bslash;&n;&t;.attr = {.name = __stringify(_name), .mode = _mode },&t;&bslash;&n;&t;.show&t;= _show,&t;&t;&t;&t;&bslash;&n;&t;.store&t;= _store,&t;&t;&t;&t;&bslash;&n;};
r_extern
r_int
id|driver_create_file
c_func
(paren
r_struct
id|device_driver
op_star
comma
r_struct
id|driver_attribute
op_star
)paren
suffix:semicolon
r_extern
r_void
id|driver_remove_file
c_func
(paren
r_struct
id|device_driver
op_star
comma
r_struct
id|driver_attribute
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * device classes&n; */
DECL|struct|device_class
r_struct
id|device_class
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|devnum
id|u32
id|devnum
suffix:semicolon
DECL|member|subsys
r_struct
id|subsystem
id|subsys
suffix:semicolon
DECL|member|devsubsys
r_struct
id|subsystem
id|devsubsys
suffix:semicolon
DECL|member|drvsubsys
r_struct
id|subsystem
id|drvsubsys
suffix:semicolon
DECL|member|drivers
r_struct
id|list_head
id|drivers
suffix:semicolon
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
DECL|member|add_device
r_int
(paren
op_star
id|add_device
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|member|remove_device
r_void
(paren
op_star
id|remove_device
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|member|hotplug
r_int
(paren
op_star
id|hotplug
)paren
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
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|devclass_register
c_func
(paren
r_struct
id|device_class
op_star
)paren
suffix:semicolon
r_extern
r_void
id|devclass_unregister
c_func
(paren
r_struct
id|device_class
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|device_class
op_star
id|get_devclass
c_func
(paren
r_struct
id|device_class
op_star
)paren
suffix:semicolon
r_extern
r_void
id|put_devclass
c_func
(paren
r_struct
id|device_class
op_star
)paren
suffix:semicolon
DECL|struct|devclass_attribute
r_struct
id|devclass_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|device_class
op_star
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|device_class
op_star
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEVCLASS_ATTR
mdefine_line|#define DEVCLASS_ATTR(_name,_str,_mode,_show,_store)&t;&bslash;&n;struct devclass_attribute devclass_attr_##_name = { &t;&t;&bslash;&n;&t;.attr = {.name&t;= _str,&t;.mode&t;= _mode },&t;&bslash;&n;&t;.show&t;= _show,&t;&t;&t;&t;&bslash;&n;&t;.store&t;= _store,&t;&t;&t;&t;&bslash;&n;};
r_extern
r_int
id|devclass_create_file
c_func
(paren
r_struct
id|device_class
op_star
comma
r_struct
id|devclass_attribute
op_star
)paren
suffix:semicolon
r_extern
r_void
id|devclass_remove_file
c_func
(paren
r_struct
id|device_class
op_star
comma
r_struct
id|devclass_attribute
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * device interfaces&n; * These are the logical interfaces of device classes. &n; * These entities map directly to specific userspace interfaces, like &n; * device nodes.&n; * Interfaces are registered with the device class they belong to. When&n; * a device is registered with the class, each interface&squot;s add_device &n; * callback is called. It is up to the interface to decide whether or not&n; * it supports the device.&n; */
r_struct
id|intf_data
suffix:semicolon
DECL|struct|device_interface
r_struct
id|device_interface
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|devclass
r_struct
id|device_class
op_star
id|devclass
suffix:semicolon
DECL|member|subsys
r_struct
id|subsystem
id|subsys
suffix:semicolon
DECL|member|devnum
id|u32
id|devnum
suffix:semicolon
DECL|member|add_device
r_int
(paren
op_star
id|add_device
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
DECL|member|remove_device
r_int
(paren
op_star
id|remove_device
)paren
(paren
r_struct
id|intf_data
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|interface_register
c_func
(paren
r_struct
id|device_interface
op_star
)paren
suffix:semicolon
r_extern
r_void
id|interface_unregister
c_func
(paren
r_struct
id|device_interface
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * intf_data - per-device data for an interface&n; * Each interface typically has a per-device data structure &n; * that it allocates. It should embed one of these structures &n; * in that structure and call interface_add_data() to add it&n; * to the device&squot;s list.&n; * That will also enumerate the device within the interface&n; * and create a driverfs symlink for it.&n; */
DECL|struct|intf_data
r_struct
id|intf_data
(brace
DECL|member|intf
r_struct
id|device_interface
op_star
id|intf
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|intf_num
id|u32
id|intf_num
suffix:semicolon
DECL|member|dev_entry
r_struct
id|list_head
id|dev_entry
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|interface_add_data
c_func
(paren
r_struct
id|intf_data
op_star
)paren
suffix:semicolon
DECL|struct|device
r_struct
id|device
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in sibling list */
DECL|member|bus_list
r_struct
id|list_head
id|bus_list
suffix:semicolon
multiline_comment|/* node in bus&squot;s list */
DECL|member|class_list
r_struct
id|list_head
id|class_list
suffix:semicolon
DECL|member|driver_list
r_struct
id|list_head
id|driver_list
suffix:semicolon
DECL|member|children
r_struct
id|list_head
id|children
suffix:semicolon
DECL|member|intf_list
r_struct
id|list_head
id|intf_list
suffix:semicolon
DECL|member|parent
r_struct
id|device
op_star
id|parent
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* descriptive ascii string */
DECL|member|bus_id
r_char
id|bus_id
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
multiline_comment|/* position on parent bus */
DECL|member|bus
r_struct
id|bus_type
op_star
id|bus
suffix:semicolon
multiline_comment|/* type of bus device is on */
DECL|member|driver
r_struct
id|device_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* which driver has allocated this&n;&t;&t;&t;&t;&t;   device */
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* data private to the driver */
DECL|member|class_num
id|u32
id|class_num
suffix:semicolon
multiline_comment|/* class-enumerated value */
DECL|member|class_data
r_void
op_star
id|class_data
suffix:semicolon
multiline_comment|/* class-specific data */
DECL|member|platform_data
r_void
op_star
id|platform_data
suffix:semicolon
multiline_comment|/* Platform specific data (e.g. ACPI,&n;&t;&t;&t;&t;&t;   BIOS data relevant to device) */
DECL|member|power_state
id|u32
id|power_state
suffix:semicolon
multiline_comment|/* Current operating state. In&n;&t;&t;&t;&t;&t;   ACPI-speak, this is D0-D3, D0&n;&t;&t;&t;&t;&t;   being fully functional, and D3&n;&t;&t;&t;&t;&t;   being off. */
DECL|member|saved_state
r_int
r_char
op_star
id|saved_state
suffix:semicolon
multiline_comment|/* saved device state */
DECL|member|dma_mask
id|u64
op_star
id|dma_mask
suffix:semicolon
multiline_comment|/* dma mask (if dma&squot;able device) */
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_struct
id|device
op_star
DECL|function|list_to_dev
id|list_to_dev
c_func
(paren
r_struct
id|list_head
op_star
id|node
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|device
comma
id|node
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
op_star
DECL|function|dev_get_drvdata
id|dev_get_drvdata
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;driver_data
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dev_set_drvdata
id|dev_set_drvdata
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
id|dev-&gt;driver_data
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/*&n; * High level routines for use by the bus drivers&n; */
r_extern
r_int
id|device_register
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|device_unregister
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|device_initialize
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|device_add
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|device_del
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* driverfs interface for exporting device attributes */
DECL|struct|device_attribute
r_struct
id|device_attribute
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEVICE_ATTR
mdefine_line|#define DEVICE_ATTR(_name,_mode,_show,_store) &bslash;&n;struct device_attribute dev_attr_##_name = { &t;&t;&bslash;&n;&t;.attr = {.name = __stringify(_name), .mode = _mode },&t;&bslash;&n;&t;.show&t;= _show,&t;&t;&t;&t;&bslash;&n;&t;.store&t;= _store,&t;&t;&t;&t;&bslash;&n;};
r_extern
r_int
id|device_create_file
c_func
(paren
r_struct
id|device
op_star
id|device
comma
r_struct
id|device_attribute
op_star
id|entry
)paren
suffix:semicolon
r_extern
r_void
id|device_remove_file
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_attribute
op_star
id|attr
)paren
suffix:semicolon
multiline_comment|/*&n; * Platform &quot;fixup&quot; functions - allow the platform to have their say&n; * about devices and actions that the general device layer doesn&squot;t&n; * know about.&n; */
multiline_comment|/* Notify platform of device discovery */
r_extern
r_int
(paren
op_star
id|platform_notify
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|platform_notify_remove
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/**&n; * get_device - atomically increment the reference count for the device.&n; *&n; */
r_extern
r_struct
id|device
op_star
id|get_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|put_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* drivers/base/sys.c */
DECL|struct|sys_root
r_struct
id|sys_root
(brace
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|sysdev
r_struct
id|device
id|sysdev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|sys_register_root
c_func
(paren
r_struct
id|sys_root
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sys_unregister_root
c_func
(paren
r_struct
id|sys_root
op_star
)paren
suffix:semicolon
DECL|struct|sys_device
r_struct
id|sys_device
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|root
r_struct
id|sys_root
op_star
id|root
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|sys_device_register
c_func
(paren
r_struct
id|sys_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sys_device_unregister
c_func
(paren
r_struct
id|sys_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|bus_type
id|system_bus_type
suffix:semicolon
multiline_comment|/* drivers/base/platform.c */
DECL|struct|platform_device
r_struct
id|platform_device
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|platform_device_register
c_func
(paren
r_struct
id|platform_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|platform_device_unregister
c_func
(paren
r_struct
id|platform_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|bus_type
id|platform_bus_type
suffix:semicolon
multiline_comment|/* drivers/base/power.c */
r_extern
r_int
id|device_suspend
c_func
(paren
id|u32
id|state
comma
id|u32
id|level
)paren
suffix:semicolon
r_extern
r_void
id|device_resume
c_func
(paren
id|u32
id|level
)paren
suffix:semicolon
r_extern
r_void
id|device_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* drivers/base/firmware.c */
r_extern
r_int
id|firmware_register
c_func
(paren
r_struct
id|subsystem
op_star
)paren
suffix:semicolon
r_extern
r_void
id|firmware_unregister
c_func
(paren
r_struct
id|subsystem
op_star
)paren
suffix:semicolon
multiline_comment|/* debugging and troubleshooting/diagnostic helpers. */
DECL|macro|dev_printk
mdefine_line|#define dev_printk(sev, dev, format, arg...)&t;&bslash;&n;&t;printk(sev &quot;%s %s: &quot; format , (dev).driver-&gt;name , (dev).bus_id , ## arg)
macro_line|#ifdef DEBUG
DECL|macro|dev_dbg
mdefine_line|#define dev_dbg(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_DEBUG , (dev) , format , ## arg)
macro_line|#else
DECL|macro|dev_dbg
mdefine_line|#define dev_dbg(dev, format, arg...) do {} while (0)
macro_line|#endif
DECL|macro|dev_err
mdefine_line|#define dev_err(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_ERR , (dev) , format , ## arg)
DECL|macro|dev_info
mdefine_line|#define dev_info(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_INFO , (dev) , format , ## arg)
DECL|macro|dev_warn
mdefine_line|#define dev_warn(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_WARNING , (dev) , format , ## arg)
macro_line|#endif /* _DEVICE_H_ */
eof
