multiline_comment|/*&n; * device.h - generic, centralized driver model&n; *&n; * Copyright (c) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; * This is a relatively simple centralized driver model.&n; * The data structures were mainly lifted directly from the PCI&n; * driver model. These are thought to be the common fields that&n; * are relevant to all device buses.&n; *&n; * All the devices are arranged in a tree. All devices should&n; * have some sort of parent bus of whom they are children of.&n; * Devices should not be direct children of the system root.&n; *&n; * Device drivers should not directly call the device_* routines&n; * or access the contents of struct device directly. Instead,&n; * abstract that from the drivers and write bus-specific wrappers&n; * that do it for you.&n; *&n; * See Documentation/driver-model.txt for more information.&n; */
macro_line|#ifndef _DEVICE_H_
DECL|macro|_DEVICE_H_
mdefine_line|#define _DEVICE_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/driverfs_fs.h&gt;
DECL|macro|DEVICE_NAME_SIZE
mdefine_line|#define DEVICE_NAME_SIZE&t;80
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
r_enum
(brace
DECL|enumerator|REMOVE_NOTIFY
id|REMOVE_NOTIFY
comma
DECL|enumerator|REMOVE_FREE_RESOURCES
id|REMOVE_FREE_RESOURCES
comma
)brace
suffix:semicolon
r_struct
id|device
suffix:semicolon
r_struct
id|iobus
suffix:semicolon
DECL|struct|device_driver
r_struct
id|device_driver
(brace
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
comma
id|u32
id|flags
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
id|stage
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
id|stage
)paren
suffix:semicolon
)brace
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
DECL|member|parent
r_struct
id|iobus
op_star
id|parent
suffix:semicolon
multiline_comment|/* parent bus */
DECL|member|subordinate
r_struct
id|iobus
op_star
id|subordinate
suffix:semicolon
multiline_comment|/* only valid if this device is a&n;&t;&t;&t;&t;&t;   bridge device */
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
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for the device to ensure two&n;&t;&t;&t;&t;&t;   different layers don&squot;t access it at&n;&t;&t;&t;&t;&t;   the same time. */
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
multiline_comment|/* refcount to make sure the device&n;&t;&t;&t;&t;&t; * persists for the right amount of time */
DECL|member|dir
r_struct
id|driver_dir_entry
id|dir
suffix:semicolon
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
multiline_comment|/* Platform specific data (e.g. ACPI,&n;&t;&t;&t;&t;&t;   BIOS data relevant to device */
DECL|member|current_state
id|u32
id|current_state
suffix:semicolon
multiline_comment|/* Current operating state. In&n;&t;&t;&t;&t;&t;   ACPI-speak, this is D0-D3, D0&n;&t;&t;&t;&t;&t;   being fully functional, and D3&n;&t;&t;&t;&t;&t;   being off. */
DECL|member|saved_state
r_int
r_char
op_star
id|saved_state
suffix:semicolon
multiline_comment|/* saved device state */
)brace
suffix:semicolon
multiline_comment|/*&n; * struct bus_type - descriptor for a type of bus&n; * There are some instances when you need to know what type of bus a&n; * device is on. Instead of having some sort of enumerated integer type,&n; * each struct iobus will have a pointer to a struct bus_type that gives&n; * actually meaningful data.&n; * There should be one struct bus_type for each type of bus (one for PCI,&n; * one for USB, etc).&n; */
DECL|struct|iobus_driver
r_struct
id|iobus_driver
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* ascii descriptor of type of bus */
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in global list of bus drivers */
DECL|member|scan
r_int
(paren
op_star
id|scan
)paren
(paren
r_struct
id|iobus
op_star
)paren
suffix:semicolon
DECL|member|add_device
r_int
(paren
op_star
id|add_device
)paren
(paren
r_struct
id|iobus
op_star
comma
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|iobus
r_struct
id|iobus
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for bus */
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
multiline_comment|/* node in sibling list */
DECL|member|parent
r_struct
id|iobus
op_star
id|parent
suffix:semicolon
multiline_comment|/* parent bus */
DECL|member|children
r_struct
id|list_head
id|children
suffix:semicolon
multiline_comment|/* children buses */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* children devices */
DECL|member|self
r_struct
id|device
op_star
id|self
suffix:semicolon
multiline_comment|/* pointer to controlling device */
DECL|member|dir
r_struct
id|driver_dir_entry
id|dir
suffix:semicolon
multiline_comment|/* driverfs directory */
DECL|member|name
r_char
id|name
(braket
id|DEVICE_NAME_SIZE
)braket
suffix:semicolon
DECL|member|bus_id
r_char
id|bus_id
(braket
id|BUS_ID_SIZE
)braket
suffix:semicolon
DECL|member|driver
r_struct
id|iobus_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* bus operations */
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
r_struct
id|iobus
op_star
DECL|function|list_to_iobus
id|list_to_iobus
c_func
(paren
r_const
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
id|iobus
comma
id|node
)paren
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
r_int
id|iobus_register
c_func
(paren
r_struct
id|iobus
op_star
id|iobus
)paren
suffix:semicolon
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
id|driver_file_entry
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
r_const
r_char
op_star
id|name
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
r_extern
r_int
id|device_driver_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* device and bus locking helpers.&n; *&n; * FIXME: Is there anything else we need to do?&n; */
DECL|function|lock_device
r_static
r_inline
r_void
id|lock_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|unlock_device
r_static
r_inline
r_void
id|unlock_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * get_device - atomically increment the reference count for the device.&n; *&n; */
DECL|function|get_device
r_static
r_inline
r_void
id|get_device
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;refcount
)paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;refcount
)paren
suffix:semicolon
)brace
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
DECL|function|lock_iobus
r_static
r_inline
r_void
id|lock_iobus
c_func
(paren
r_struct
id|iobus
op_star
id|iobus
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|iobus-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|unlock_iobus
r_static
r_inline
r_void
id|unlock_iobus
c_func
(paren
r_struct
id|iobus
op_star
id|iobus
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|iobus-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|get_iobus
r_static
r_inline
r_void
id|get_iobus
c_func
(paren
r_struct
id|iobus
op_star
id|iobus
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|iobus-&gt;refcount
)paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|iobus-&gt;refcount
)paren
suffix:semicolon
)brace
r_extern
r_void
id|put_iobus
c_func
(paren
r_struct
id|iobus
op_star
id|iobus
)paren
suffix:semicolon
macro_line|#endif /* _DEVICE_H_ */
eof