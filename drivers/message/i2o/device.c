multiline_comment|/*&n; *&t;Functions to handle I2O devices&n; *&n; *&t;Copyright (C) 2004&t;Markus Lidel &lt;Markus.Lidel@shadowconnect.com&gt;&n; *&n; *&t;This program is free software; you can redistribute it and/or modify it&n; *&t;under the terms of the GNU General Public License as published by the&n; *&t;Free Software Foundation; either version 2 of the License, or (at your&n; *&t;option) any later version.&n; *&n; *&t;Fixes/additions:&n; *&t;&t;Markus Lidel &lt;Markus.Lidel@shadowconnect.com&gt;&n; *&t;&t;&t;initial version.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/i2o.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/* Exec OSM functions */
r_extern
r_struct
id|bus_type
id|i2o_bus_type
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_issue_claim - claim or release a device&n; *&t;@dev: I2O device to claim or release&n; *&t;@cmd: claim or release command&n; *&t;@type: type of claim&n; *&n; *&t;Issue I2O UTIL_CLAIM or UTIL_RELEASE messages. The message to be sent&n; *&t;is set by cmd. dev is the I2O device which should be claim or&n; *&t;released and the type is the claim type (see the I2O spec).&n; *&n; *&t;Returs 0 on success or negative error code on failure.&n; */
DECL|function|i2o_device_issue_claim
r_static
r_inline
r_int
id|i2o_device_issue_claim
c_func
(paren
r_struct
id|i2o_device
op_star
id|dev
comma
id|u32
id|cmd
comma
id|u32
id|type
)paren
(brace
r_struct
id|i2o_message
op_star
id|msg
suffix:semicolon
id|u32
id|m
suffix:semicolon
id|m
op_assign
id|i2o_msg_get_wait
c_func
(paren
id|dev-&gt;iop
comma
op_amp
id|msg
comma
id|I2O_TIMEOUT_MESSAGE_GET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
id|I2O_QUEUE_EMPTY
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
id|writel
c_func
(paren
id|FIVE_WORD_MSG_SIZE
op_or
id|SGL_OFFSET_0
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|cmd
op_lshift
l_int|24
op_or
id|HOST_TID
op_lshift
l_int|12
op_or
id|dev-&gt;lct_data.tid
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|type
comma
op_amp
id|msg-&gt;body
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
id|i2o_msg_post_wait
c_func
(paren
id|dev-&gt;iop
comma
id|m
comma
l_int|60
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * &t;i2o_device_claim - claim a device for use by an OSM&n; *&t;@dev: I2O device to claim&n; *&t;@drv: I2O driver which wants to claim the device&n; *&n; *&t;Do the leg work to assign a device to a given OSM. If the claim succeed&n; *&t;the owner of the rimary. If the attempt fails a negative errno code&n; *&t;is returned. On success zero is returned.&n; */
DECL|function|i2o_device_claim
r_int
id|i2o_device_claim
c_func
(paren
r_struct
id|i2o_device
op_star
id|dev
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|rc
op_assign
id|i2o_device_issue_claim
c_func
(paren
id|dev
comma
id|I2O_CMD_UTIL_CLAIM
comma
id|I2O_CLAIM_PRIMARY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|pr_debug
c_func
(paren
l_string|&quot;claim of device %d succeded&bslash;n&quot;
comma
id|dev-&gt;lct_data.tid
)paren
suffix:semicolon
r_else
id|pr_debug
c_func
(paren
l_string|&quot;claim of device %d failed %d&bslash;n&quot;
comma
id|dev-&gt;lct_data.tid
comma
id|rc
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_claim_release - release a device that the OSM is using&n; *&t;@dev: device to release&n; *&t;@drv: driver which claimed the device&n; *&n; *&t;Drop a claim by an OSM on a given I2O device.&n; *&n; *&t;AC - some devices seem to want to refuse an unclaim until they have&n; *&t;finished internal processing. It makes sense since you don&squot;t want a&n; *&t;new device to go reconfiguring the entire system until you are done.&n; *&t;Thus we are prepared to wait briefly.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_device_claim_release
r_int
id|i2o_device_claim_release
c_func
(paren
r_struct
id|i2o_device
op_star
id|dev
)paren
(brace
r_int
id|tries
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *      If the controller takes a nonblocking approach to&n;&t; *      releases we have to sleep/poll for a few times.&n;&t; */
r_for
c_loop
(paren
id|tries
op_assign
l_int|0
suffix:semicolon
id|tries
OL
l_int|10
suffix:semicolon
id|tries
op_increment
)paren
(brace
id|rc
op_assign
id|i2o_device_issue_claim
c_func
(paren
id|dev
comma
id|I2O_CMD_UTIL_RELEASE
comma
id|I2O_CLAIM_PRIMARY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
r_break
suffix:semicolon
id|ssleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|pr_debug
c_func
(paren
l_string|&quot;claim release of device %d succeded&bslash;n&quot;
comma
id|dev-&gt;lct_data.tid
)paren
suffix:semicolon
r_else
id|pr_debug
c_func
(paren
l_string|&quot;claim release of device %d failed %d&bslash;n&quot;
comma
id|dev-&gt;lct_data.tid
comma
id|rc
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_release - release the memory for a I2O device&n; *&t;@dev: I2O device which should be released&n; *&n; *&t;Release the allocated memory. This function is called if refcount of&n; *&t;device reaches 0 automatically.&n; */
DECL|function|i2o_device_release
r_static
r_void
id|i2o_device_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|i2o_device
op_star
id|i2o_dev
op_assign
id|to_i2o_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Release I2O device %s&bslash;n&quot;
comma
id|dev-&gt;bus_id
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i2o_dev
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_class_release - Remove I2O device attributes&n; *&t;@cd: I2O class device which is added to the I2O device class&n; *&n; *&t;Removes attributes from the I2O device again. Also search each device&n; *&t;on the controller for I2O devices which refert to this device as parent&n; *&t;or user and remove this links also.&n; */
DECL|function|i2o_device_class_release
r_static
r_void
id|i2o_device_class_release
c_func
(paren
r_struct
id|class_device
op_star
id|cd
)paren
(brace
r_struct
id|i2o_device
op_star
id|i2o_dev
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|i2o_controller
op_star
id|c
suffix:semicolon
id|i2o_dev
op_assign
id|to_i2o_device
c_func
(paren
id|cd-&gt;dev
)paren
suffix:semicolon
id|c
op_assign
id|i2o_dev-&gt;iop
suffix:semicolon
id|sysfs_remove_link
c_func
(paren
op_amp
id|i2o_dev-&gt;device.kobj
comma
l_string|&quot;parent&quot;
)paren
suffix:semicolon
id|sysfs_remove_link
c_func
(paren
op_amp
id|i2o_dev-&gt;device.kobj
comma
l_string|&quot;user&quot;
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|c-&gt;devices
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;lct_data.parent_tid
op_eq
id|i2o_dev-&gt;lct_data.tid
)paren
id|sysfs_remove_link
c_func
(paren
op_amp
id|tmp-&gt;device.kobj
comma
l_string|&quot;parent&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;lct_data.user_tid
op_eq
id|i2o_dev-&gt;lct_data.tid
)paren
id|sysfs_remove_link
c_func
(paren
op_amp
id|tmp-&gt;device.kobj
comma
l_string|&quot;user&quot;
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
multiline_comment|/* I2O device class */
DECL|variable|i2o_device_class
r_static
r_struct
r_class
id|i2o_device_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i2o_device&quot;
comma
dot
id|release
op_assign
id|i2o_device_class_release
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_alloc - Allocate a I2O device and initialize it&n; *&n; *&t;Allocate the memory for a I2O device and initialize locks and lists&n; *&n; *&t;Returns the allocated I2O device or a negative error code if the device&n; *&t;could not be allocated.&n; */
DECL|function|i2o_device_alloc
r_static
r_struct
id|i2o_device
op_star
id|i2o_device_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|i2o_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;list
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|dev-&gt;device.bus
op_assign
op_amp
id|i2o_bus_type
suffix:semicolon
id|dev-&gt;device.release
op_assign
op_amp
id|i2o_device_release
suffix:semicolon
id|dev-&gt;classdev
dot
r_class
op_assign
op_amp
id|i2o_device_class
suffix:semicolon
id|dev-&gt;classdev.dev
op_assign
op_amp
id|dev-&gt;device
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_add - allocate a new I2O device and add it to the IOP&n; *&t;@iop: I2O controller where the device is on&n; *&t;@entry: LCT entry of the I2O device&n; *&n; *&t;Allocate a new I2O device and initialize it with the LCT entry. The&n; *&t;device is appended to the device list of the controller.&n; *&n; *&t;Returns a pointer to the I2O device on success or negative error code&n; *&t;on failure.&n; */
DECL|function|i2o_device_add
r_struct
id|i2o_device
op_star
id|i2o_device_add
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|i2o_lct_entry
op_star
id|entry
)paren
(brace
r_struct
id|i2o_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|i2o_device_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: unable to allocate i2o device&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
id|dev-&gt;lct_data
op_assign
op_star
id|entry
suffix:semicolon
id|snprintf
c_func
(paren
id|dev-&gt;device.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%d:%03x&quot;
comma
id|c-&gt;unit
comma
id|dev-&gt;lct_data.tid
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|dev-&gt;classdev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%d:%03x&quot;
comma
id|c-&gt;unit
comma
id|dev-&gt;lct_data.tid
)paren
suffix:semicolon
id|dev-&gt;iop
op_assign
id|c
suffix:semicolon
id|dev-&gt;device.parent
op_assign
op_amp
id|c-&gt;device
suffix:semicolon
id|device_register
c_func
(paren
op_amp
id|dev-&gt;device
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;list
comma
op_amp
id|c-&gt;devices
)paren
suffix:semicolon
id|class_device_register
c_func
(paren
op_amp
id|dev-&gt;classdev
)paren
suffix:semicolon
id|i2o_driver_notify_device_add_all
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;I2O device %s added&bslash;n&quot;
comma
id|dev-&gt;device.bus_id
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_remove - remove an I2O device from the I2O core&n; *&t;@dev: I2O device which should be released&n; *&n; *&t;Is used on I2O controller removal or LCT modification, when the device&n; *&t;is removed from the system. Note that the device could still hang&n; *&t;around until the refcount reaches 0.&n; */
DECL|function|i2o_device_remove
r_void
id|i2o_device_remove
c_func
(paren
r_struct
id|i2o_device
op_star
id|i2o_dev
)paren
(brace
id|i2o_driver_notify_device_remove_all
c_func
(paren
id|i2o_dev
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|i2o_dev-&gt;classdev
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|i2o_dev-&gt;list
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|i2o_dev-&gt;device
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_parse_lct - Parse a previously fetched LCT and create devices&n; *&t;@c: I2O controller from which the LCT should be parsed.&n; *&n; *&t;The Logical Configuration Table tells us what we can talk to on the&n; *&t;board. For every entry we create an I2O device, which is registered in&n; *&t;the I2O core.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_device_parse_lct
r_int
id|i2o_device_parse_lct
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_struct
id|i2o_device
op_star
id|dev
comma
op_star
id|tmp
suffix:semicolon
id|i2o_lct
op_star
id|lct
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|max
suffix:semicolon
id|down
c_func
(paren
op_amp
id|c-&gt;lct_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;lct
)paren
id|kfree
c_func
(paren
id|c-&gt;lct
)paren
suffix:semicolon
id|lct
op_assign
id|c-&gt;dlct.virt
suffix:semicolon
id|c-&gt;lct
op_assign
id|kmalloc
c_func
(paren
id|lct-&gt;table_size
op_star
l_int|4
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c-&gt;lct
)paren
(brace
id|up
c_func
(paren
op_amp
id|c-&gt;lct_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lct-&gt;table_size
op_star
l_int|4
OG
id|c-&gt;dlct.len
)paren
(brace
id|memcpy_fromio
c_func
(paren
id|c-&gt;lct
comma
id|c-&gt;dlct.virt
comma
id|c-&gt;dlct.len
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|c-&gt;lct_lock
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|memcpy_fromio
c_func
(paren
id|c-&gt;lct
comma
id|c-&gt;dlct.virt
comma
id|lct-&gt;table_size
op_star
l_int|4
)paren
suffix:semicolon
id|lct
op_assign
id|c-&gt;lct
suffix:semicolon
id|max
op_assign
(paren
id|lct-&gt;table_size
op_minus
l_int|3
)paren
op_div
l_int|9
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;LCT has %d entries (LCT size: %d)&bslash;n&quot;
comma
id|max
comma
id|lct-&gt;table_size
)paren
suffix:semicolon
multiline_comment|/* remove devices, which are not in the LCT anymore */
id|list_for_each_entry_safe
c_func
(paren
id|dev
comma
id|tmp
comma
op_amp
id|c-&gt;devices
comma
id|list
)paren
(brace
r_int
id|found
op_assign
l_int|0
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
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|lct-&gt;lct_entry
(braket
id|i
)braket
dot
id|tid
op_eq
id|dev-&gt;lct_data.tid
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|i2o_device_remove
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* add new devices, which are new in the LCT */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|dev
comma
id|tmp
comma
op_amp
id|c-&gt;devices
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|lct-&gt;lct_entry
(braket
id|i
)braket
dot
id|tid
op_eq
id|dev-&gt;lct_data.tid
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|i2o_device_add
c_func
(paren
id|c
comma
op_amp
id|lct-&gt;lct_entry
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|c-&gt;lct_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_class_show_class_id - Displays class id of I2O device&n; *&t;@cd: class device of which the class id should be displayed&n; *&t;@buf: buffer into which the class id should be printed&n; *&n; *&t;Returns the number of bytes which are printed into the buffer.&n; */
DECL|function|i2o_device_class_show_class_id
r_static
id|ssize_t
id|i2o_device_class_show_class_id
c_func
(paren
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|i2o_device
op_star
id|dev
op_assign
id|to_i2o_device
c_func
(paren
id|cd-&gt;dev
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%03x&bslash;n&quot;
comma
id|dev-&gt;lct_data.class_id
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
op_plus
l_int|1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_class_show_tid - Displays TID of I2O device&n; *&t;@cd: class device of which the TID should be displayed&n; *&t;@buf: buffer into which the class id should be printed&n; *&n; *&t;Returns the number of bytes which are printed into the buffer.&n; */
DECL|function|i2o_device_class_show_tid
r_static
id|ssize_t
id|i2o_device_class_show_tid
c_func
(paren
r_struct
id|class_device
op_star
id|cd
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|i2o_device
op_star
id|dev
op_assign
id|to_i2o_device
c_func
(paren
id|cd-&gt;dev
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%03x&bslash;n&quot;
comma
id|dev-&gt;lct_data.tid
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
op_plus
l_int|1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I2O device class attributes */
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|class_id
comma
id|S_IRUGO
comma
id|i2o_device_class_show_class_id
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|tid
comma
id|S_IRUGO
comma
id|i2o_device_class_show_tid
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_class_add - Adds attributes to the I2O device&n; *&t;@cd: I2O class device which is added to the I2O device class&n; *&n; *&t;This function get called when a I2O device is added to the class. It&n; *&t;creates the attributes for each device and creates user/parent symlink&n; *&t;if necessary.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_device_class_add
r_static
r_int
id|i2o_device_class_add
c_func
(paren
r_struct
id|class_device
op_star
id|cd
)paren
(brace
r_struct
id|i2o_device
op_star
id|i2o_dev
comma
op_star
id|tmp
suffix:semicolon
r_struct
id|i2o_controller
op_star
id|c
suffix:semicolon
id|i2o_dev
op_assign
id|to_i2o_device
c_func
(paren
id|cd-&gt;dev
)paren
suffix:semicolon
id|c
op_assign
id|i2o_dev-&gt;iop
suffix:semicolon
id|class_device_create_file
c_func
(paren
id|cd
comma
op_amp
id|class_device_attr_class_id
)paren
suffix:semicolon
id|class_device_create_file
c_func
(paren
id|cd
comma
op_amp
id|class_device_attr_tid
)paren
suffix:semicolon
multiline_comment|/* create user entries for this device */
id|tmp
op_assign
id|i2o_iop_find_device
c_func
(paren
id|i2o_dev-&gt;iop
comma
id|i2o_dev-&gt;lct_data.user_tid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
id|sysfs_create_link
c_func
(paren
op_amp
id|i2o_dev-&gt;device.kobj
comma
op_amp
id|tmp-&gt;device.kobj
comma
l_string|&quot;user&quot;
)paren
suffix:semicolon
multiline_comment|/* create user entries refering to this device */
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|c-&gt;devices
comma
id|list
)paren
r_if
c_cond
(paren
id|tmp-&gt;lct_data.user_tid
op_eq
id|i2o_dev-&gt;lct_data.tid
)paren
id|sysfs_create_link
c_func
(paren
op_amp
id|tmp-&gt;device.kobj
comma
op_amp
id|i2o_dev-&gt;device.kobj
comma
l_string|&quot;user&quot;
)paren
suffix:semicolon
multiline_comment|/* create parent entries for this device */
id|tmp
op_assign
id|i2o_iop_find_device
c_func
(paren
id|i2o_dev-&gt;iop
comma
id|i2o_dev-&gt;lct_data.parent_tid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
id|sysfs_create_link
c_func
(paren
op_amp
id|i2o_dev-&gt;device.kobj
comma
op_amp
id|tmp-&gt;device.kobj
comma
l_string|&quot;parent&quot;
)paren
suffix:semicolon
multiline_comment|/* create parent entries refering to this device */
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|c-&gt;devices
comma
id|list
)paren
r_if
c_cond
(paren
id|tmp-&gt;lct_data.parent_tid
op_eq
id|i2o_dev-&gt;lct_data.tid
)paren
id|sysfs_create_link
c_func
(paren
op_amp
id|tmp-&gt;device.kobj
comma
op_amp
id|i2o_dev-&gt;device.kobj
comma
l_string|&quot;parent&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I2O device class interface */
DECL|variable|i2o_device_class_interface
r_static
r_struct
id|class_interface
id|i2o_device_class_interface
op_assign
(brace
dot
r_class
op_assign
op_amp
id|i2o_device_class
comma
dot
id|add
op_assign
id|i2o_device_class_add
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Run time support routines&n; */
multiline_comment|/*&t;Issue UTIL_PARAMS_GET or UTIL_PARAMS_SET&n; *&n; *&t;This function can be used for all UtilParamsGet/Set operations.&n; *&t;The OperationList is given in oplist-buffer,&n; *&t;and results are returned in reslist-buffer.&n; *&t;Note that the minimum sized reslist is 8 bytes and contains&n; *&t;ResultCount, ErrorInfoSize, BlockStatus and BlockSize.&n; */
DECL|function|i2o_parm_issue
r_int
id|i2o_parm_issue
c_func
(paren
r_struct
id|i2o_device
op_star
id|i2o_dev
comma
r_int
id|cmd
comma
r_void
op_star
id|oplist
comma
r_int
id|oplen
comma
r_void
op_star
id|reslist
comma
r_int
id|reslen
)paren
(brace
r_struct
id|i2o_message
op_star
id|msg
suffix:semicolon
id|u32
id|m
suffix:semicolon
id|u32
op_star
id|res32
op_assign
(paren
id|u32
op_star
)paren
id|reslist
suffix:semicolon
id|u32
op_star
id|restmp
op_assign
(paren
id|u32
op_star
)paren
id|reslist
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_struct
id|i2o_dma
id|res
suffix:semicolon
r_struct
id|i2o_controller
op_star
id|c
op_assign
id|i2o_dev-&gt;iop
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|c-&gt;pdev-&gt;dev
suffix:semicolon
id|res.virt
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|i2o_dma_alloc
c_func
(paren
id|dev
comma
op_amp
id|res
comma
id|reslen
comma
id|GFP_KERNEL
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|m
op_assign
id|i2o_msg_get_wait
c_func
(paren
id|c
comma
op_amp
id|msg
comma
id|I2O_TIMEOUT_MESSAGE_GET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
op_eq
id|I2O_QUEUE_EMPTY
)paren
(brace
id|i2o_dma_free
c_func
(paren
id|dev
comma
op_amp
id|res
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
id|writel
c_func
(paren
id|cmd
op_lshift
l_int|24
op_or
id|HOST_TID
op_lshift
l_int|12
op_or
id|i2o_dev-&gt;lct_data.tid
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
op_amp
id|msg-&gt;body
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0x4C000000
op_or
id|oplen
comma
op_amp
id|msg-&gt;body
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
multiline_comment|/* OperationList */
id|memcpy_toio
c_func
(paren
op_amp
id|msg-&gt;body
(braket
id|i
)braket
comma
id|oplist
comma
id|oplen
)paren
suffix:semicolon
id|i
op_add_assign
(paren
id|oplen
op_div
l_int|4
op_plus
(paren
id|oplen
op_mod
l_int|4
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xD0000000
op_or
id|res.len
comma
op_amp
id|msg-&gt;body
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
multiline_comment|/* ResultList */
id|writel
c_func
(paren
id|res.phys
comma
op_amp
id|msg-&gt;body
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
id|writel
c_func
(paren
id|I2O_MESSAGE_SIZE
c_func
(paren
id|i
op_plus
r_sizeof
(paren
r_struct
id|i2o_message
)paren
op_div
l_int|4
)paren
op_or
id|SGL_OFFSET_5
comma
op_amp
id|msg-&gt;u.head
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|rc
op_assign
id|i2o_msg_post_wait_mem
c_func
(paren
id|c
comma
id|m
comma
l_int|10
comma
op_amp
id|res
)paren
suffix:semicolon
multiline_comment|/* This only looks like a memory leak - don&squot;t &quot;fix&quot; it. */
r_if
c_cond
(paren
id|rc
op_eq
op_minus
id|ETIMEDOUT
)paren
r_return
id|rc
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|reslist
comma
id|res.virt
comma
id|res.len
)paren
suffix:semicolon
id|i2o_dma_free
c_func
(paren
id|dev
comma
op_amp
id|res
)paren
suffix:semicolon
multiline_comment|/* Query failed */
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate number of bytes of Result LIST&n;&t; * We need to loop through each Result BLOCK and grab the length&n;&t; */
id|restmp
op_assign
id|res32
op_plus
l_int|1
suffix:semicolon
id|len
op_assign
l_int|1
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
(paren
id|res32
(braket
l_int|0
)braket
op_amp
l_int|0X0000FFFF
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|restmp
(braket
l_int|0
)braket
op_amp
l_int|0x00FF0000
)paren
(brace
multiline_comment|/* BlockStatus != SUCCESS */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s - Error:&bslash;n  ErrorInfoSize = 0x%02x, &quot;
l_string|&quot;BlockStatus = 0x%02x, BlockSize = 0x%04x&bslash;n&quot;
comma
(paren
id|cmd
op_eq
id|I2O_CMD_UTIL_PARAMS_SET
)paren
ques
c_cond
l_string|&quot;PARAMS_SET&quot;
suffix:colon
l_string|&quot;PARAMS_GET&quot;
comma
id|res32
(braket
l_int|1
)braket
op_rshift
l_int|24
comma
(paren
id|res32
(braket
l_int|1
)braket
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
comma
id|res32
(braket
l_int|1
)braket
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *      If this is the only request,than we return an error&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|res32
(braket
l_int|0
)braket
op_amp
l_int|0x0000FFFF
)paren
op_eq
l_int|1
)paren
(brace
r_return
op_minus
(paren
(paren
id|res32
(braket
l_int|1
)braket
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
multiline_comment|/* -BlockStatus */
)brace
)brace
id|len
op_add_assign
id|restmp
(braket
l_int|0
)braket
op_amp
l_int|0x0000FFFF
suffix:semicolon
multiline_comment|/* Length of res BLOCK */
id|restmp
op_add_assign
id|restmp
(braket
l_int|0
)braket
op_amp
l_int|0x0000FFFF
suffix:semicolon
multiline_comment|/* Skip to next BLOCK */
)brace
r_return
(paren
id|len
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* bytes used by result list */
)brace
multiline_comment|/*&n; *&t; Query one field group value or a whole scalar group.&n; */
DECL|function|i2o_parm_field_get
r_int
id|i2o_parm_field_get
c_func
(paren
r_struct
id|i2o_device
op_star
id|i2o_dev
comma
r_int
id|group
comma
r_int
id|field
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
(brace
id|u16
id|opblk
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|0
comma
id|I2O_PARAMS_FIELD_GET
comma
id|group
comma
l_int|1
comma
id|field
)brace
suffix:semicolon
id|u8
id|resblk
(braket
l_int|8
op_plus
id|buflen
)braket
suffix:semicolon
multiline_comment|/* 8 bytes for header */
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
id|field
op_eq
op_minus
l_int|1
)paren
multiline_comment|/* whole group */
id|opblk
(braket
l_int|4
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|size
op_assign
id|i2o_parm_issue
c_func
(paren
id|i2o_dev
comma
id|I2O_CMD_UTIL_PARAMS_GET
comma
id|opblk
comma
r_sizeof
(paren
id|opblk
)paren
comma
id|resblk
comma
r_sizeof
(paren
id|resblk
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|resblk
op_plus
l_int|8
comma
id|buflen
)paren
suffix:semicolon
multiline_comment|/* cut off header */
r_if
c_cond
(paren
id|size
OG
id|buflen
)paren
r_return
id|buflen
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set a scalar group value or a whole group.&n; */
DECL|function|i2o_parm_field_set
r_int
id|i2o_parm_field_set
c_func
(paren
r_struct
id|i2o_device
op_star
id|i2o_dev
comma
r_int
id|group
comma
r_int
id|field
comma
r_void
op_star
id|buf
comma
r_int
id|buflen
)paren
(brace
id|u16
op_star
id|opblk
suffix:semicolon
id|u8
id|resblk
(braket
l_int|8
op_plus
id|buflen
)braket
suffix:semicolon
multiline_comment|/* 8 bytes for header */
r_int
id|size
suffix:semicolon
id|opblk
op_assign
id|kmalloc
c_func
(paren
id|buflen
op_plus
l_int|64
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opblk
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: no memory for operation buffer.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|opblk
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* operation count */
id|opblk
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pad */
id|opblk
(braket
l_int|2
)braket
op_assign
id|I2O_PARAMS_FIELD_SET
suffix:semicolon
id|opblk
(braket
l_int|3
)braket
op_assign
id|group
suffix:semicolon
r_if
c_cond
(paren
id|field
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* whole group */
id|opblk
(braket
l_int|4
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|opblk
op_plus
l_int|5
comma
id|buf
comma
id|buflen
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* single field */
id|opblk
(braket
l_int|4
)braket
op_assign
l_int|1
suffix:semicolon
id|opblk
(braket
l_int|5
)braket
op_assign
id|field
suffix:semicolon
id|memcpy
c_func
(paren
id|opblk
op_plus
l_int|6
comma
id|buf
comma
id|buflen
)paren
suffix:semicolon
)brace
id|size
op_assign
id|i2o_parm_issue
c_func
(paren
id|i2o_dev
comma
id|I2O_CMD_UTIL_PARAMS_SET
comma
id|opblk
comma
l_int|12
op_plus
id|buflen
comma
id|resblk
comma
r_sizeof
(paren
id|resblk
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|opblk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|buflen
)paren
r_return
id|buflen
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;if oper == I2O_PARAMS_TABLE_GET, get from all rows&n; * &t;&t;if fieldcount == -1 return all fields&n; *&t;&t;&t;ibuf and ibuflen are unused (use NULL, 0)&n; * &t;&t;else return specific fields&n; *  &t;&t;&t;ibuf contains fieldindexes&n; *&n; * &t;if oper == I2O_PARAMS_LIST_GET, get from specific rows&n; * &t;&t;if fieldcount == -1 return all fields&n; *&t;&t;&t;ibuf contains rowcount, keyvalues&n; * &t;&t;else return specific fields&n; *&t;&t;&t;fieldcount is # of fieldindexes&n; *  &t;&t;&t;ibuf contains fieldindexes, rowcount, keyvalues&n; *&n; *&t;You could also use directly function i2o_issue_params().&n; */
DECL|function|i2o_parm_table_get
r_int
id|i2o_parm_table_get
c_func
(paren
r_struct
id|i2o_device
op_star
id|dev
comma
r_int
id|oper
comma
r_int
id|group
comma
r_int
id|fieldcount
comma
r_void
op_star
id|ibuf
comma
r_int
id|ibuflen
comma
r_void
op_star
id|resblk
comma
r_int
id|reslen
)paren
(brace
id|u16
op_star
id|opblk
suffix:semicolon
r_int
id|size
suffix:semicolon
id|size
op_assign
l_int|10
op_plus
id|ibuflen
suffix:semicolon
r_if
c_cond
(paren
id|size
op_mod
l_int|4
)paren
id|size
op_add_assign
l_int|4
op_minus
id|size
op_mod
l_int|4
suffix:semicolon
id|opblk
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opblk
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2o: no memory for query buffer.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|opblk
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* operation count */
id|opblk
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pad */
id|opblk
(braket
l_int|2
)braket
op_assign
id|oper
suffix:semicolon
id|opblk
(braket
l_int|3
)braket
op_assign
id|group
suffix:semicolon
id|opblk
(braket
l_int|4
)braket
op_assign
id|fieldcount
suffix:semicolon
id|memcpy
c_func
(paren
id|opblk
op_plus
l_int|5
comma
id|ibuf
comma
id|ibuflen
)paren
suffix:semicolon
multiline_comment|/* other params */
id|size
op_assign
id|i2o_parm_issue
c_func
(paren
id|dev
comma
id|I2O_CMD_UTIL_PARAMS_GET
comma
id|opblk
comma
id|size
comma
id|resblk
comma
id|reslen
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|opblk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|reslen
)paren
r_return
id|reslen
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;i2o_device_init - Initialize I2O devices&n; *&n; *&t;Registers the I2O device class.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_device_init
r_int
id|i2o_device_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|class_register
c_func
(paren
op_amp
id|i2o_device_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
r_return
id|class_interface_register
c_func
(paren
op_amp
id|i2o_device_class_interface
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_device_exit - I2O devices exit function&n; *&n; *&t;Unregisters the I2O device class.&n; */
DECL|function|i2o_device_exit
r_void
id|i2o_device_exit
c_func
(paren
r_void
)paren
(brace
id|class_interface_register
c_func
(paren
op_amp
id|i2o_device_class_interface
)paren
suffix:semicolon
id|class_unregister
c_func
(paren
op_amp
id|i2o_device_class
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|i2o_device_claim
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_device_claim
)paren
suffix:semicolon
DECL|variable|i2o_device_claim_release
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_device_claim_release
)paren
suffix:semicolon
DECL|variable|i2o_parm_field_get
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_parm_field_get
)paren
suffix:semicolon
DECL|variable|i2o_parm_field_set
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_parm_field_set
)paren
suffix:semicolon
DECL|variable|i2o_parm_table_get
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_parm_table_get
)paren
suffix:semicolon
DECL|variable|i2o_parm_issue
id|EXPORT_SYMBOL
c_func
(paren
id|i2o_parm_issue
)paren
suffix:semicolon
eof
