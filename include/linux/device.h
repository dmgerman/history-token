multiline_comment|/*&n; * device.h - generic, centralized driver model&n; *&n; * Copyright (c) 2001-2003 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; * This file is released under the GPLv2&n; *&n; * See Documentation/driver-model/ for more information.&n; */
macro_line|#ifndef _DEVICE_H_
DECL|macro|_DEVICE_H_
mdefine_line|#define _DEVICE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|DEVICE_NAME_SIZE
mdefine_line|#define DEVICE_NAME_SIZE&t;50
DECL|macro|DEVICE_NAME_HALF
mdefine_line|#define DEVICE_NAME_HALF&t;__stringify(20)&t;/* Less than half to accommodate slop */
DECL|macro|DEVICE_ID_SIZE
mdefine_line|#define DEVICE_ID_SIZE&t;&t;32
DECL|macro|BUS_ID_SIZE
mdefine_line|#define BUS_ID_SIZE&t;&t;KOBJ_NAME_LEN
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
r_struct
id|device
suffix:semicolon
r_struct
id|device_driver
suffix:semicolon
r_struct
r_class
suffix:semicolon
r_struct
id|class_device
suffix:semicolon
r_struct
id|class_simple
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
DECL|member|drivers
r_struct
id|kset
id|drivers
suffix:semicolon
DECL|member|devices
r_struct
id|kset
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
r_int
id|bus_rescan_devices
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
r_extern
r_struct
id|bus_type
op_star
id|find_bus
c_func
(paren
r_char
op_star
id|name
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
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BUS_ATTR
mdefine_line|#define BUS_ATTR(_name,_mode,_show,_store)&t;&bslash;&n;struct bus_attribute bus_attr_##_name = __ATTR(_name,_mode,_show,_store)
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
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DRIVER_ATTR
mdefine_line|#define DRIVER_ATTR(_name,_mode,_show,_store)&t;&bslash;&n;struct driver_attribute driver_attr_##_name = __ATTR(_name,_mode,_show,_store)
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
DECL|struct|class
r_struct
r_class
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
DECL|member|children
r_struct
id|list_head
id|children
suffix:semicolon
DECL|member|interfaces
r_struct
id|list_head
id|interfaces
suffix:semicolon
DECL|member|hotplug
r_int
(paren
op_star
id|hotplug
)paren
(paren
r_struct
id|class_device
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
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|class_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|class_release
r_void
(paren
op_star
id|class_release
)paren
(paren
r_struct
r_class
op_star
r_class
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|class_register
c_func
(paren
r_struct
r_class
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_unregister
c_func
(paren
r_struct
r_class
op_star
)paren
suffix:semicolon
r_extern
r_struct
r_class
op_star
id|class_get
c_func
(paren
r_struct
r_class
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_put
c_func
(paren
r_struct
r_class
op_star
)paren
suffix:semicolon
DECL|struct|class_attribute
r_struct
id|class_attribute
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
r_class
op_star
comma
r_char
op_star
id|buf
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
r_class
op_star
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CLASS_ATTR
mdefine_line|#define CLASS_ATTR(_name,_mode,_show,_store)&t;&t;&t;&bslash;&n;struct class_attribute class_attr_##_name = __ATTR(_name,_mode,_show,_store) 
r_extern
r_int
id|class_create_file
c_func
(paren
r_struct
r_class
op_star
comma
r_const
r_struct
id|class_attribute
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_remove_file
c_func
(paren
r_struct
r_class
op_star
comma
r_const
r_struct
id|class_attribute
op_star
)paren
suffix:semicolon
DECL|struct|class_device
r_struct
id|class_device
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|class
r_struct
r_class
op_star
r_class
suffix:semicolon
multiline_comment|/* required */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* not necessary, but nice to have */
DECL|member|class_data
r_void
op_star
id|class_data
suffix:semicolon
multiline_comment|/* class-specific data */
DECL|member|class_id
r_char
id|class_id
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
multiline_comment|/* unique to this class */
)brace
suffix:semicolon
r_static
r_inline
r_void
op_star
DECL|function|class_get_devdata
id|class_get_devdata
(paren
r_struct
id|class_device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;class_data
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|class_set_devdata
id|class_set_devdata
(paren
r_struct
id|class_device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
id|dev-&gt;class_data
op_assign
id|data
suffix:semicolon
)brace
r_extern
r_int
id|class_device_register
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_device_unregister
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_device_initialize
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|class_device_add
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_device_del
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|class_device_rename
c_func
(paren
r_struct
id|class_device
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|class_device
op_star
id|class_device_get
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_device_put
c_func
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
DECL|struct|class_device_attribute
r_struct
id|class_device_attribute
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
id|class_device
op_star
comma
r_char
op_star
id|buf
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
id|class_device
op_star
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CLASS_DEVICE_ATTR
mdefine_line|#define CLASS_DEVICE_ATTR(_name,_mode,_show,_store)&t;&t;&bslash;&n;struct class_device_attribute class_device_attr_##_name = &t;&bslash;&n;&t;__ATTR(_name,_mode,_show,_store)
r_extern
r_int
id|class_device_create_file
c_func
(paren
r_struct
id|class_device
op_star
comma
r_const
r_struct
id|class_device_attribute
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_device_remove_file
c_func
(paren
r_struct
id|class_device
op_star
comma
r_const
r_struct
id|class_device_attribute
op_star
)paren
suffix:semicolon
DECL|struct|class_interface
r_struct
id|class_interface
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|class
r_struct
r_class
op_star
r_class
suffix:semicolon
DECL|member|add
r_int
(paren
op_star
id|add
)paren
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|class_device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|class_interface_register
c_func
(paren
r_struct
id|class_interface
op_star
)paren
suffix:semicolon
r_extern
r_void
id|class_interface_unregister
c_func
(paren
r_struct
id|class_interface
op_star
)paren
suffix:semicolon
multiline_comment|/* interface for class simple stuff */
r_extern
r_struct
id|class_simple
op_star
id|class_simple_create
c_func
(paren
r_struct
id|module
op_star
id|owner
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|class_simple_destroy
c_func
(paren
r_struct
id|class_simple
op_star
id|cs
)paren
suffix:semicolon
r_extern
r_struct
id|class_device
op_star
id|class_simple_device_add
c_func
(paren
r_struct
id|class_simple
op_star
id|cs
comma
id|dev_t
id|dev
comma
r_struct
id|device
op_star
id|device
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|4
comma
l_int|5
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|class_simple_set_hotplug
c_func
(paren
r_struct
id|class_simple
op_star
comma
r_int
(paren
op_star
id|hotplug
)paren
(paren
r_struct
id|class_device
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
)paren
suffix:semicolon
r_extern
r_void
id|class_simple_device_remove
c_func
(paren
id|dev_t
id|dev
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
DECL|member|platform_data
r_void
op_star
id|platform_data
suffix:semicolon
multiline_comment|/* Platform specific data (e.g. ACPI,&n;&t;&t;&t;&t;&t;   BIOS data relevant to device) */
DECL|member|power
r_struct
id|dev_pm_info
id|power
suffix:semicolon
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
DECL|member|detach_state
id|u32
id|detach_state
suffix:semicolon
multiline_comment|/* State to enter when device is&n;&t;&t;&t;&t;&t;   detached from its driver. */
DECL|member|dma_mask
id|u64
op_star
id|dma_mask
suffix:semicolon
multiline_comment|/* dma mask (if dma&squot;able device) */
DECL|member|coherent_dma_mask
id|u64
id|coherent_dma_mask
suffix:semicolon
multiline_comment|/* Like dma_mask, but for&n;&t;&t;&t;&t;&t;     alloc_coherent mappings as&n;&t;&t;&t;&t;&t;     not all hardware supports&n;&t;&t;&t;&t;&t;     64 bit addresses for consistent&n;&t;&t;&t;&t;&t;     allocations such descriptors. */
DECL|member|dma_pools
r_struct
id|list_head
id|dma_pools
suffix:semicolon
multiline_comment|/* dma pools (if dma&squot;ble) */
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
r_extern
r_int
id|device_for_each_child
c_func
(paren
r_struct
id|device
op_star
comma
r_void
op_star
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
multiline_comment|/*&n; * Manual binding of a device to driver. See drivers/base/bus.c &n; * for information on use.&n; */
r_extern
r_void
id|device_bind_driver
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
id|device_release_driver
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
id|driver_attach
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
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
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEVICE_ATTR
mdefine_line|#define DEVICE_ATTR(_name,_mode,_show,_store) &bslash;&n;struct device_attribute dev_attr_##_name = __ATTR(_name,_mode,_show,_store)
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
r_extern
r_struct
id|device
op_star
id|device_find
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|bus_type
op_star
id|bus
)paren
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
DECL|member|num_resources
id|u32
id|num_resources
suffix:semicolon
DECL|member|resource
r_struct
id|resource
op_star
id|resource
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_platform_device
mdefine_line|#define to_platform_device(x) container_of((x), struct platform_device, dev)
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
r_extern
r_struct
id|device
id|platform_bus
suffix:semicolon
multiline_comment|/* drivers/base/power.c */
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
mdefine_line|#define dev_printk(level, dev, format, arg...)&t;&bslash;&n;&t;printk(level &quot;%s %s: &quot; format , (dev)-&gt;driver ? (dev)-&gt;driver-&gt;name : &quot;&quot; , (dev)-&gt;bus_id , ## arg)
macro_line|#ifdef DEBUG
DECL|macro|dev_dbg
mdefine_line|#define dev_dbg(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_DEBUG , dev , format , ## arg)
macro_line|#else
DECL|macro|dev_dbg
mdefine_line|#define dev_dbg(dev, format, arg...) do { (void)(dev); } while (0)
macro_line|#endif
DECL|macro|dev_err
mdefine_line|#define dev_err(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_ERR , dev , format , ## arg)
DECL|macro|dev_info
mdefine_line|#define dev_info(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_INFO , dev , format , ## arg)
DECL|macro|dev_warn
mdefine_line|#define dev_warn(dev, format, arg...)&t;&t;&bslash;&n;&t;dev_printk(KERN_WARNING , dev , format , ## arg)
multiline_comment|/* Create alias, so I can be autoloaded. */
DECL|macro|MODULE_ALIAS_CHARDEV
mdefine_line|#define MODULE_ALIAS_CHARDEV(major,minor) &bslash;&n;&t;MODULE_ALIAS(&quot;char-major-&quot; __stringify(major) &quot;-&quot; __stringify(minor))
DECL|macro|MODULE_ALIAS_CHARDEV_MAJOR
mdefine_line|#define MODULE_ALIAS_CHARDEV_MAJOR(major) &bslash;&n;&t;MODULE_ALIAS(&quot;char-major-&quot; __stringify(major) &quot;-*&quot;)
macro_line|#endif /* _DEVICE_H_ */
eof
