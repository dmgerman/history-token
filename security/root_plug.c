multiline_comment|/*&n; * Root Plug sample LSM module&n; *&n; * Originally written for a Linux Journal.&n; *&n; * Copyright (C) 2002 Greg Kroah-Hartman &lt;greg@kroah.com&gt;&n; *&n; * Prevents any programs running with egid == 0 if a specific USB device&n; * is not present in the system.  Yes, it can be gotten around, but is a&n; * nice starting point for people to play with, and learn the LSM&n; * interface.&n; *&n; * If you want to turn this into something with a semblance of security,&n; * you need to hook the task_* functions also.&n; *&n; * See http://www.linuxjournal.com/article.php?sid=6279 for more information&n; * about this code.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2 of the&n; *&t;License.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
multiline_comment|/* flag to keep track of how we were registered */
DECL|variable|secondary
r_static
r_int
id|secondary
suffix:semicolon
multiline_comment|/* default is a generic type of usb to serial converter */
DECL|variable|vendor_id
r_static
r_int
id|vendor_id
op_assign
l_int|0x0557
suffix:semicolon
DECL|variable|product_id
r_static
r_int
id|product_id
op_assign
l_int|0x2008
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|vendor_id
comma
l_string|&quot;h&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vendor_id
comma
l_string|&quot;USB Vendor ID of device to look for&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|product_id
comma
l_string|&quot;h&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|product_id
comma
l_string|&quot;USB Product ID of device to look for&quot;
)paren
suffix:semicolon
multiline_comment|/* should we print out debug messages */
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debug enabled or not&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SECURITY_ROOTPLUG_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME THIS_MODULE-&gt;name
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME &quot;root_plug&quot;
macro_line|#endif
DECL|macro|dbg
mdefine_line|#define dbg(fmt, arg...)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (debug)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_DEBUG &quot;%s: %s: &quot; fmt ,&t;&bslash;&n;&t;&t;&t;&t;MY_NAME , __FUNCTION__ , &t;&bslash;&n;&t;&t;&t;&t;## arg);&t;&t;&t;&bslash;&n;&t;} while (0)
r_extern
r_struct
id|list_head
id|usb_bus_list
suffix:semicolon
r_extern
r_struct
id|semaphore
id|usb_bus_list_lock
suffix:semicolon
DECL|function|match_device
r_static
r_int
id|match_device
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_int
id|child
suffix:semicolon
id|dbg
(paren
l_string|&quot;looking at vendor %d, product %d&bslash;n&quot;
comma
id|dev-&gt;descriptor.idVendor
comma
id|dev-&gt;descriptor.idProduct
)paren
suffix:semicolon
multiline_comment|/* see if this device matches */
r_if
c_cond
(paren
(paren
id|dev-&gt;descriptor.idVendor
op_eq
id|vendor_id
)paren
op_logical_and
(paren
id|dev-&gt;descriptor.idProduct
op_eq
id|product_id
)paren
)paren
(brace
id|dbg
(paren
l_string|&quot;found the device!&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* look through all of the children of this device */
r_for
c_loop
(paren
id|child
op_assign
l_int|0
suffix:semicolon
id|child
OL
id|dev-&gt;maxchild
suffix:semicolon
op_increment
id|child
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;children
(braket
id|child
)braket
)paren
(brace
id|retval
op_assign
id|match_device
(paren
id|dev-&gt;children
(braket
id|child
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
r_goto
m_exit
suffix:semicolon
)brace
)brace
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|find_usb_device
r_static
r_int
id|find_usb_device
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|buslist
suffix:semicolon
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
id|down
(paren
op_amp
id|usb_bus_list_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|buslist
op_assign
id|usb_bus_list.next
suffix:semicolon
id|buslist
op_ne
op_amp
id|usb_bus_list
suffix:semicolon
id|buslist
op_assign
id|buslist-&gt;next
)paren
(brace
id|bus
op_assign
id|container_of
(paren
id|buslist
comma
r_struct
id|usb_bus
comma
id|bus_list
)paren
suffix:semicolon
id|retval
op_assign
id|match_device
c_func
(paren
id|bus-&gt;root_hub
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
r_goto
m_exit
suffix:semicolon
)brace
m_exit
suffix:colon
id|up
(paren
op_amp
id|usb_bus_list_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|rootplug_bprm_check_security
r_static
r_int
id|rootplug_bprm_check_security
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
id|dbg
(paren
l_string|&quot;file %s, e_uid = %d, e_gid = %d&bslash;n&quot;
comma
id|bprm-&gt;filename
comma
id|bprm-&gt;e_uid
comma
id|bprm-&gt;e_gid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bprm-&gt;e_gid
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|find_usb_device
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|dbg
(paren
l_string|&quot;e_gid = 0, and device not found, &quot;
l_string|&quot;task not allowed to run...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rootplug_security_ops
r_static
r_struct
id|security_operations
id|rootplug_security_ops
op_assign
(brace
multiline_comment|/* Use the capability functions for some of the hooks */
dot
id|ptrace
op_assign
id|cap_ptrace
comma
dot
id|capget
op_assign
id|cap_capget
comma
dot
id|capset_check
op_assign
id|cap_capset_check
comma
dot
id|capset_set
op_assign
id|cap_capset_set
comma
dot
id|capable
op_assign
id|cap_capable
comma
dot
id|bprm_compute_creds
op_assign
id|cap_bprm_compute_creds
comma
dot
id|bprm_set_security
op_assign
id|cap_bprm_set_security
comma
dot
id|task_post_setuid
op_assign
id|cap_task_post_setuid
comma
dot
id|task_kmod_set_label
op_assign
id|cap_task_kmod_set_label
comma
dot
id|task_reparent_to_init
op_assign
id|cap_task_reparent_to_init
comma
dot
id|bprm_check_security
op_assign
id|rootplug_bprm_check_security
comma
)brace
suffix:semicolon
DECL|function|rootplug_init
r_static
r_int
id|__init
id|rootplug_init
(paren
r_void
)paren
(brace
multiline_comment|/* register ourselves with the security framework */
r_if
c_cond
(paren
id|register_security
(paren
op_amp
id|rootplug_security_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure registering Root Plug module with the kernel&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* try registering with primary module */
r_if
c_cond
(paren
id|mod_reg_security
(paren
id|MY_NAME
comma
op_amp
id|rootplug_security_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure registering Root Plug &quot;
l_string|&quot; module with primary security module.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|secondary
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Root Plug module initialized, &quot;
l_string|&quot;vendor_id = %4.4x, product id = %4.4x&bslash;n&quot;
comma
id|vendor_id
comma
id|product_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rootplug_exit
r_static
r_void
id|__exit
id|rootplug_exit
(paren
r_void
)paren
(brace
multiline_comment|/* remove ourselves from the security framework */
r_if
c_cond
(paren
id|secondary
)paren
(brace
r_if
c_cond
(paren
id|mod_unreg_security
(paren
id|MY_NAME
comma
op_amp
id|rootplug_security_ops
)paren
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure unregistering Root Plug &quot;
l_string|&quot; module with primary module.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|unregister_security
(paren
op_amp
id|rootplug_security_ops
)paren
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Failure unregistering Root Plug &quot;
l_string|&quot;module with the kernel&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Root Plug module removed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|rootplug_init
id|module_init
(paren
id|rootplug_init
)paren
suffix:semicolon
DECL|variable|rootplug_exit
id|module_exit
(paren
id|rootplug_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Root Plug sample LSM module, written for Linux Journal article&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
