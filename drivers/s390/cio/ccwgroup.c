multiline_comment|/*&n; *  drivers/s390/cio/ccwgroup.c&n; *  bus driver for ccwgroup&n; *   $Revision: 1.7 $&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *                       IBM Corporation&n; *    Author(s): Arnd Bergmann (arndb@de.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/ccwgroup.h&gt;
multiline_comment|/* In Linux 2.4, we had a channel device layer called &quot;chandev&quot;&n; * that did all sorts of obscure stuff for networking devices.&n; * This is another driver that serves as a replacement for just&n; * one of its functions, namely the translation of single subchannels&n; * to devices that use multiple subchannels.&n; */
multiline_comment|/* a device matches a driver if all its slave devices match the same&n; * entry of the driver */
r_static
r_int
DECL|function|ccwgroup_bus_match
id|ccwgroup_bus_match
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
id|ccwgroup_device
op_star
id|gdev
suffix:semicolon
r_struct
id|ccwgroup_driver
op_star
id|gdrv
suffix:semicolon
id|gdev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|ccwgroup_device
comma
id|dev
)paren
suffix:semicolon
id|gdrv
op_assign
id|container_of
c_func
(paren
id|drv
comma
r_struct
id|ccwgroup_driver
comma
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gdev-&gt;creator_id
op_eq
id|gdrv-&gt;driver_id
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ccwgroup_hotplug
id|ccwgroup_hotplug
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
multiline_comment|/* TODO */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ccwgroup_bus_type
r_static
r_struct
id|bus_type
id|ccwgroup_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ccwgroup&quot;
comma
dot
id|match
op_assign
id|ccwgroup_bus_match
comma
dot
id|hotplug
op_assign
id|ccwgroup_hotplug
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|ccwgroup_release
id|ccwgroup_release
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ccwgroup_device
op_star
id|gdev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|gdev
op_assign
id|to_ccwgroupdev
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
id|gdev-&gt;count
suffix:semicolon
id|i
op_increment
)paren
id|put_device
c_func
(paren
op_amp
id|gdev-&gt;cdev
(braket
id|i
)braket
op_member_access_from_pointer
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gdev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * try to add a new ccwgroup device for one driver&n; * argc and argv[] are a list of bus_id&squot;s of devices&n; * belonging to the driver.&n; */
r_int
DECL|function|ccwgroup_create
id|ccwgroup_create
c_func
(paren
r_struct
id|device
op_star
id|root
comma
r_int
r_int
id|creator_id
comma
r_struct
id|ccw_driver
op_star
id|cdrv
comma
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
r_struct
id|ccwgroup_device
op_star
id|gdev
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|256
)paren
multiline_comment|/* disallow dumb users */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|gdev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|gdev
)paren
op_plus
id|argc
op_star
r_sizeof
(paren
id|gdev-&gt;cdev
(braket
l_int|0
)braket
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdev
)paren
r_return
op_minus
id|ENOMEM
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
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gdev-&gt;cdev
(braket
id|i
)braket
op_assign
id|get_ccwdev_by_busid
c_func
(paren
id|cdrv
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* all devices have to be of the same type in&n;&t;&t; * order to be grouped */
r_if
c_cond
(paren
op_logical_neg
id|gdev-&gt;cdev
(braket
id|i
)braket
op_logical_or
id|gdev-&gt;cdev
(braket
id|i
)braket
op_member_access_from_pointer
id|id.driver_info
op_ne
id|gdev-&gt;cdev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|id.driver_info
)paren
r_goto
id|error
suffix:semicolon
)brace
op_star
id|gdev
op_assign
(paren
r_struct
id|ccwgroup_device
)paren
(brace
dot
id|creator_id
op_assign
id|creator_id
comma
dot
id|count
op_assign
id|argc
comma
dot
id|dev
op_assign
(brace
dot
id|bus
op_assign
op_amp
id|ccwgroup_bus_type
comma
dot
id|parent
op_assign
id|root
comma
dot
id|release
op_assign
op_amp
id|ccwgroup_release
comma
)brace
comma
)brace
suffix:semicolon
id|snprintf
(paren
id|gdev-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%s&quot;
comma
id|gdev-&gt;cdev
(braket
l_int|0
)braket
op_member_access_from_pointer
id|dev.bus_id
)paren
suffix:semicolon
multiline_comment|/* TODO: make symlinks for sysfs */
r_return
id|device_register
c_func
(paren
op_amp
id|gdev-&gt;dev
)paren
suffix:semicolon
id|error
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|gdev-&gt;cdev
(braket
id|i
)braket
)paren
id|put_device
c_func
(paren
op_amp
id|gdev-&gt;cdev
(braket
id|i
)braket
op_member_access_from_pointer
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gdev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|init_ccwgroup
id|init_ccwgroup
(paren
r_void
)paren
(brace
r_return
id|bus_register
(paren
op_amp
id|ccwgroup_bus_type
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|cleanup_ccwgroup
id|cleanup_ccwgroup
(paren
r_void
)paren
(brace
id|bus_unregister
(paren
op_amp
id|ccwgroup_bus_type
)paren
suffix:semicolon
)brace
DECL|variable|init_ccwgroup
id|module_init
c_func
(paren
id|init_ccwgroup
)paren
suffix:semicolon
DECL|variable|cleanup_ccwgroup
id|module_exit
c_func
(paren
id|cleanup_ccwgroup
)paren
suffix:semicolon
multiline_comment|/************************** driver stuff ******************************/
r_static
r_int
DECL|function|ccwgroup_set_online
id|ccwgroup_set_online
c_func
(paren
r_struct
id|ccwgroup_device
op_star
id|gdev
)paren
(brace
r_struct
id|ccwgroup_driver
op_star
id|gdrv
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|gdev-&gt;state
op_eq
id|CCWGROUP_ONLINE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdev-&gt;dev.driver
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|gdrv
op_assign
id|to_ccwgroupdrv
(paren
id|gdev-&gt;dev.driver
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|gdrv
op_member_access_from_pointer
id|set_online
c_func
(paren
id|gdev
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|gdev-&gt;state
op_assign
id|CCWGROUP_ONLINE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ccwgroup_set_offline
id|ccwgroup_set_offline
c_func
(paren
r_struct
id|ccwgroup_device
op_star
id|gdev
)paren
(brace
r_struct
id|ccwgroup_driver
op_star
id|gdrv
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|gdev-&gt;state
op_eq
id|CCWGROUP_OFFLINE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gdev-&gt;dev.driver
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|gdrv
op_assign
id|to_ccwgroupdrv
(paren
id|gdev-&gt;dev.driver
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|gdrv
op_member_access_from_pointer
id|set_offline
c_func
(paren
id|gdev
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|gdev-&gt;state
op_assign
id|CCWGROUP_OFFLINE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ccwgroup_online_store
id|ccwgroup_online_store
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
(brace
r_struct
id|ccwgroup_device
op_star
id|gdev
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
id|gdev
op_assign
id|to_ccwgroupdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;driver
)paren
r_return
id|count
suffix:semicolon
id|value
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|1
)paren
id|ccwgroup_set_online
c_func
(paren
id|gdev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|value
op_eq
l_int|0
)paren
id|ccwgroup_set_offline
c_func
(paren
id|gdev
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ccwgroup_online_show
id|ccwgroup_online_show
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
(brace
r_int
id|online
suffix:semicolon
id|online
op_assign
(paren
id|to_ccwgroupdev
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|state
op_eq
id|CCWGROUP_ONLINE
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
id|online
ques
c_cond
l_string|&quot;yes&bslash;n&quot;
suffix:colon
l_string|&quot;no&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|online
comma
l_int|0644
comma
id|ccwgroup_online_show
comma
id|ccwgroup_online_store
)paren
suffix:semicolon
r_static
r_int
DECL|function|ccwgroup_probe
id|ccwgroup_probe
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ccwgroup_device
op_star
id|gdev
suffix:semicolon
r_struct
id|ccwgroup_driver
op_star
id|gdrv
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|gdev
op_assign
id|to_ccwgroupdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|gdrv
op_assign
id|to_ccwgroupdrv
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_online
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: device %s&bslash;n&quot;
comma
id|__func__
comma
id|gdev-&gt;dev.name
)paren
suffix:semicolon
id|ret
op_assign
id|gdrv-&gt;probe
ques
c_cond
id|gdrv
op_member_access_from_pointer
id|probe
c_func
(paren
id|gdev
)paren
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_online
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|ccwgroup_remove
id|ccwgroup_remove
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|ccwgroup_device
op_star
id|gdev
suffix:semicolon
r_struct
id|ccwgroup_driver
op_star
id|gdrv
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|gdev
op_assign
id|to_ccwgroupdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|gdrv
op_assign
id|to_ccwgroupdrv
c_func
(paren
id|dev-&gt;driver
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;%s: device %s&bslash;n&quot;
comma
id|__func__
comma
id|gdev-&gt;dev.name
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_online
)paren
suffix:semicolon
id|ccwgroup_set_offline
c_func
(paren
id|gdev
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|gdrv
op_logical_and
id|gdrv-&gt;remove
)paren
ques
c_cond
id|gdrv
op_member_access_from_pointer
id|remove
c_func
(paren
id|gdev
)paren
suffix:colon
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|ccwgroup_driver_register
id|ccwgroup_driver_register
(paren
r_struct
id|ccwgroup_driver
op_star
id|cdriver
)paren
(brace
multiline_comment|/* register our new driver with the core */
id|cdriver-&gt;driver
op_assign
(paren
r_struct
id|device_driver
)paren
(brace
dot
id|bus
op_assign
op_amp
id|ccwgroup_bus_type
comma
dot
id|name
op_assign
id|cdriver-&gt;name
comma
dot
id|probe
op_assign
id|ccwgroup_probe
comma
dot
id|remove
op_assign
id|ccwgroup_remove
comma
)brace
suffix:semicolon
r_return
id|driver_register
c_func
(paren
op_amp
id|cdriver-&gt;driver
)paren
suffix:semicolon
)brace
r_void
DECL|function|ccwgroup_driver_unregister
id|ccwgroup_driver_unregister
(paren
r_struct
id|ccwgroup_driver
op_star
id|cdriver
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|cdriver-&gt;driver
)paren
suffix:semicolon
)brace
r_int
DECL|function|ccwgroup_probe_ccwdev
id|ccwgroup_probe_ccwdev
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|ccwgroup_remove_ccwdev
id|ccwgroup_remove_ccwdev
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ccwgroup_driver_register
id|EXPORT_SYMBOL
c_func
(paren
id|ccwgroup_driver_register
)paren
suffix:semicolon
DECL|variable|ccwgroup_driver_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|ccwgroup_driver_unregister
)paren
suffix:semicolon
DECL|variable|ccwgroup_create
id|EXPORT_SYMBOL
c_func
(paren
id|ccwgroup_create
)paren
suffix:semicolon
DECL|variable|ccwgroup_probe_ccwdev
id|EXPORT_SYMBOL
c_func
(paren
id|ccwgroup_probe_ccwdev
)paren
suffix:semicolon
DECL|variable|ccwgroup_remove_ccwdev
id|EXPORT_SYMBOL
c_func
(paren
id|ccwgroup_remove_ccwdev
)paren
suffix:semicolon
eof
