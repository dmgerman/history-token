multiline_comment|/*&n; * firmware_class.c - Multi purpose firmware loading support&n; *&n; * Copyright (c) 2003 Manuel Estrada Sainz &lt;ranty@debian.org&gt;&n; *&n; * Please see Documentation/firmware_class/ for more information.&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &quot;base.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Manuel Estrada Sainz &lt;ranty@debian.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Multi purpose firmware loading support&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|FW_STATUS_LOADING
id|FW_STATUS_LOADING
comma
DECL|enumerator|FW_STATUS_DONE
id|FW_STATUS_DONE
comma
DECL|enumerator|FW_STATUS_ABORT
id|FW_STATUS_ABORT
comma
)brace
suffix:semicolon
DECL|variable|loading_timeout
r_static
r_int
id|loading_timeout
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* In seconds */
multiline_comment|/* fw_lock could be moved to &squot;struct firmware_priv&squot; but since it is just&n; * guarding for corner cases a global lock should be OK */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|fw_lock
)paren
suffix:semicolon
DECL|struct|firmware_priv
r_struct
id|firmware_priv
(brace
DECL|member|fw_id
r_char
id|fw_id
(braket
id|FIRMWARE_NAME_MAX
)braket
suffix:semicolon
DECL|member|completion
r_struct
id|completion
id|completion
suffix:semicolon
DECL|member|attr_data
r_struct
id|bin_attribute
id|attr_data
suffix:semicolon
DECL|member|fw
r_struct
id|firmware
op_star
id|fw
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|alloc_size
r_int
id|alloc_size
suffix:semicolon
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|fw_load_abort
id|fw_load_abort
c_func
(paren
r_struct
id|firmware_priv
op_star
id|fw_priv
)paren
(brace
id|set_bit
c_func
(paren
id|FW_STATUS_ABORT
comma
op_amp
id|fw_priv-&gt;status
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|fw_priv-&gt;completion
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|firmware_timeout_show
id|firmware_timeout_show
c_func
(paren
r_struct
r_class
op_star
r_class
comma
r_char
op_star
id|buf
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|loading_timeout
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * firmware_timeout_store:&n; * Description:&n; *&t;Sets the number of seconds to wait for the firmware.  Once&n; *&t;this expires an error will be return to the driver and no&n; *&t;firmware will be provided.&n; *&n; *&t;Note: zero means &squot;wait for ever&squot;&n; *  &n; **/
r_static
id|ssize_t
DECL|function|firmware_timeout_store
id|firmware_timeout_store
c_func
(paren
r_struct
r_class
op_star
r_class
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
id|loading_timeout
op_assign
id|simple_strtol
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|CLASS_ATTR
c_func
(paren
id|timeout
comma
l_int|0644
comma
id|firmware_timeout_show
comma
id|firmware_timeout_store
)paren
suffix:semicolon
r_static
r_void
id|fw_class_dev_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
suffix:semicolon
r_int
id|firmware_class_hotplug
c_func
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
DECL|variable|firmware_class
r_static
r_struct
r_class
id|firmware_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;firmware&quot;
comma
dot
id|hotplug
op_assign
id|firmware_class_hotplug
comma
dot
id|release
op_assign
id|fw_class_dev_release
comma
)brace
suffix:semicolon
r_int
DECL|function|firmware_class_hotplug
id|firmware_class_hotplug
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
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
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|scratch
op_assign
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|buffer_size
OL
(paren
id|FIRMWARE_NAME_MAX
op_plus
l_int|10
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|num_envp
OL
l_int|1
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
c_func
(paren
id|scratch
comma
l_string|&quot;FIRMWARE=%s&quot;
comma
id|fw_priv-&gt;fw_id
)paren
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|firmware_loading_show
id|firmware_loading_show
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_int
id|loading
op_assign
id|test_bit
c_func
(paren
id|FW_STATUS_LOADING
comma
op_amp
id|fw_priv-&gt;status
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|loading
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * firmware_loading_store: - loading control file&n; * Description:&n; *&t;The relevant values are: &n; *&n; *&t; 1: Start a load, discarding any previous partial load.&n; *&t; 0: Conclude the load and handle the data to the driver code.&n; *&t;-1: Conclude the load with an error and discard any written data.&n; **/
r_static
id|ssize_t
DECL|function|firmware_loading_store
id|firmware_loading_store
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
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
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_int
id|loading
op_assign
id|simple_strtol
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|loading
)paren
(brace
r_case
l_int|1
suffix:colon
id|down
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|fw_priv-&gt;fw-&gt;data
)paren
suffix:semicolon
id|fw_priv-&gt;fw-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|fw_priv-&gt;fw-&gt;size
op_assign
l_int|0
suffix:semicolon
id|fw_priv-&gt;alloc_size
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|FW_STATUS_LOADING
comma
op_amp
id|fw_priv-&gt;status
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FW_STATUS_LOADING
comma
op_amp
id|fw_priv-&gt;status
)paren
)paren
(brace
id|complete
c_func
(paren
op_amp
id|fw_priv-&gt;completion
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|FW_STATUS_LOADING
comma
op_amp
id|fw_priv-&gt;status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthrough */
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unexpected value (%d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|loading
)paren
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
op_minus
l_int|1
suffix:colon
id|fw_load_abort
c_func
(paren
id|fw_priv
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|loading
comma
l_int|0644
comma
id|firmware_loading_show
comma
id|firmware_loading_store
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|firmware_data_read
id|firmware_data_read
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|offset
comma
r_int
id|count
)paren
(brace
r_struct
id|class_device
op_star
id|class_dev
op_assign
id|to_class_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_struct
id|firmware
op_star
id|fw
suffix:semicolon
id|ssize_t
id|ret_count
op_assign
id|count
suffix:semicolon
id|down
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
id|fw
op_assign
id|fw_priv-&gt;fw
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FW_STATUS_DONE
comma
op_amp
id|fw_priv-&gt;status
)paren
)paren
(brace
id|ret_count
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OG
id|fw-&gt;size
)paren
(brace
id|ret_count
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_plus
id|ret_count
OG
id|fw-&gt;size
)paren
id|ret_count
op_assign
id|fw-&gt;size
op_minus
id|offset
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
comma
id|fw-&gt;data
op_plus
id|offset
comma
id|ret_count
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
r_return
id|ret_count
suffix:semicolon
)brace
r_static
r_int
DECL|function|fw_realloc_buffer
id|fw_realloc_buffer
c_func
(paren
r_struct
id|firmware_priv
op_star
id|fw_priv
comma
r_int
id|min_size
)paren
(brace
id|u8
op_star
id|new_data
suffix:semicolon
r_if
c_cond
(paren
id|min_size
op_le
id|fw_priv-&gt;alloc_size
)paren
r_return
l_int|0
suffix:semicolon
id|new_data
op_assign
id|vmalloc
c_func
(paren
id|fw_priv-&gt;alloc_size
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to alloc buffer&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* Make sure that we don&squot;t keep incomplete data */
id|fw_load_abort
c_func
(paren
id|fw_priv
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|fw_priv-&gt;alloc_size
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|fw_priv-&gt;fw-&gt;data
)paren
(brace
id|memcpy
c_func
(paren
id|new_data
comma
id|fw_priv-&gt;fw-&gt;data
comma
id|fw_priv-&gt;fw-&gt;size
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|fw_priv-&gt;fw-&gt;data
)paren
suffix:semicolon
)brace
id|fw_priv-&gt;fw-&gt;data
op_assign
id|new_data
suffix:semicolon
id|BUG_ON
c_func
(paren
id|min_size
OG
id|fw_priv-&gt;alloc_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * firmware_data_write:&n; *&n; * Description:&n; *&n; *&t;Data written to the &squot;data&squot; attribute will be later handled to&n; *&t;the driver as a firmware image.&n; **/
r_static
id|ssize_t
DECL|function|firmware_data_write
id|firmware_data_write
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|buffer
comma
id|loff_t
id|offset
comma
r_int
id|count
)paren
(brace
r_struct
id|class_device
op_star
id|class_dev
op_assign
id|to_class_dev
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_struct
id|firmware
op_star
id|fw
suffix:semicolon
id|ssize_t
id|retval
suffix:semicolon
id|down
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
id|fw
op_assign
id|fw_priv-&gt;fw
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|FW_STATUS_DONE
comma
op_amp
id|fw_priv-&gt;status
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
id|fw_realloc_buffer
c_func
(paren
id|fw_priv
comma
id|offset
op_plus
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
id|memcpy
c_func
(paren
id|fw-&gt;data
op_plus
id|offset
comma
id|buffer
comma
id|count
)paren
suffix:semicolon
id|fw-&gt;size
op_assign
id|max_t
c_func
(paren
r_int
comma
id|offset
op_plus
id|count
comma
id|fw-&gt;size
)paren
suffix:semicolon
id|retval
op_assign
id|count
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|firmware_attr_data_tmpl
r_static
r_struct
id|bin_attribute
id|firmware_attr_data_tmpl
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;data&quot;
comma
dot
id|mode
op_assign
l_int|0644
)brace
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|read
op_assign
id|firmware_data_read
comma
dot
id|write
op_assign
id|firmware_data_write
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|fw_class_dev_release
id|fw_class_dev_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fw_priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|firmware_class_timeout
id|firmware_class_timeout
c_func
(paren
id|u_long
id|data
)paren
(brace
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
(paren
r_struct
id|firmware_priv
op_star
)paren
id|data
suffix:semicolon
id|fw_load_abort
c_func
(paren
id|fw_priv
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|fw_setup_class_device_id
id|fw_setup_class_device_id
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* XXX warning we should watch out for name collisions */
id|strlcpy
c_func
(paren
id|class_dev-&gt;class_id
comma
id|dev-&gt;bus_id
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|fw_setup_class_device
id|fw_setup_class_device
c_func
(paren
r_struct
id|firmware
op_star
id|fw
comma
r_struct
id|class_device
op_star
op_star
id|class_dev_p
comma
r_const
r_char
op_star
id|fw_name
comma
r_struct
id|device
op_star
id|device
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|firmware_priv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|class_device
op_star
id|class_dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|class_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
op_star
id|class_dev_p
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fw_priv
op_logical_or
op_logical_neg
id|class_dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: kmalloc failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error_kfree
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fw_priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fw_priv
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|class_dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|class_dev
)paren
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|fw_priv-&gt;completion
)paren
suffix:semicolon
id|fw_priv-&gt;attr_data
op_assign
id|firmware_attr_data_tmpl
suffix:semicolon
id|strlcpy
c_func
(paren
id|fw_priv-&gt;fw_id
comma
id|fw_name
comma
id|FIRMWARE_NAME_MAX
)paren
suffix:semicolon
id|fw_setup_class_device_id
c_func
(paren
id|class_dev
comma
id|device
)paren
suffix:semicolon
id|class_dev-&gt;dev
op_assign
id|device
suffix:semicolon
id|fw_priv-&gt;timeout.function
op_assign
id|firmware_class_timeout
suffix:semicolon
id|fw_priv-&gt;timeout.data
op_assign
(paren
id|u_long
)paren
id|fw_priv
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|fw_priv-&gt;timeout
)paren
suffix:semicolon
id|class_dev
op_member_access_from_pointer
r_class
op_assign
op_amp
id|firmware_class
suffix:semicolon
id|class_set_devdata
c_func
(paren
id|class_dev
comma
id|fw_priv
)paren
suffix:semicolon
id|retval
op_assign
id|class_device_register
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: class_device_register failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|error_kfree
suffix:semicolon
)brace
id|fw_priv-&gt;fw
op_assign
id|fw
suffix:semicolon
id|retval
op_assign
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|fw_priv-&gt;attr_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: sysfs_create_bin_file failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|error_unreg_class_dev
suffix:semicolon
)brace
id|retval
op_assign
id|class_device_create_file
c_func
(paren
id|class_dev
comma
op_amp
id|class_device_attr_loading
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: class_device_create_file failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|error_remove_data
suffix:semicolon
)brace
op_star
id|class_dev_p
op_assign
id|class_dev
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|error_remove_data
suffix:colon
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|fw_priv-&gt;attr_data
)paren
suffix:semicolon
id|error_unreg_class_dev
suffix:colon
id|class_device_unregister
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|error_kfree
suffix:colon
id|kfree
c_func
(paren
id|fw_priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_void
DECL|function|fw_remove_class_device
id|fw_remove_class_device
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
id|firmware_priv
op_star
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|class_device_remove_file
c_func
(paren
id|class_dev
comma
op_amp
id|class_device_attr_loading
)paren
suffix:semicolon
id|sysfs_remove_bin_file
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|fw_priv-&gt;attr_data
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
multiline_comment|/** &n; * request_firmware: - request firmware to hotplug and wait for it&n; * Description:&n; *&t;@firmware will be used to return a firmware image by the name&n; *&t;of @name for device @device.&n; *&n; *&t;Should be called from user context where sleeping is allowed.&n; *&n; *&t;@name will be use as $FIRMWARE in the hotplug environment and&n; *&t;should be distinctive enough not to be confused with any other&n; *&t;firmware image for this or any other device.&n; **/
r_int
DECL|function|request_firmware
id|request_firmware
c_func
(paren
r_const
r_struct
id|firmware
op_star
op_star
id|firmware_p
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|device
op_star
id|device
)paren
(brace
r_struct
id|class_device
op_star
id|class_dev
suffix:semicolon
r_struct
id|firmware_priv
op_star
id|fw_priv
suffix:semicolon
r_struct
id|firmware
op_star
id|firmware
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|firmware_p
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|firmware_p
op_assign
id|firmware
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|firmware
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|firmware
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: kmalloc(struct firmware) failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|firmware
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|firmware
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|fw_setup_class_device
c_func
(paren
id|firmware
comma
op_amp
id|class_dev
comma
id|name
comma
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|error_kfree_fw
suffix:semicolon
id|fw_priv
op_assign
id|class_get_devdata
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loading_timeout
)paren
(brace
id|fw_priv-&gt;timeout.expires
op_assign
id|jiffies
op_plus
id|loading_timeout
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|fw_priv-&gt;timeout
)paren
suffix:semicolon
)brace
id|wait_for_completion
c_func
(paren
op_amp
id|fw_priv-&gt;completion
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FW_STATUS_DONE
comma
op_amp
id|fw_priv-&gt;status
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|fw_priv-&gt;timeout
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fw_priv-&gt;fw-&gt;size
op_logical_or
id|test_bit
c_func
(paren
id|FW_STATUS_ABORT
comma
op_amp
id|fw_priv-&gt;status
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|release_firmware
c_func
(paren
id|fw_priv-&gt;fw
)paren
suffix:semicolon
op_star
id|firmware_p
op_assign
l_int|NULL
suffix:semicolon
)brace
id|fw_priv-&gt;fw
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|fw_lock
)paren
suffix:semicolon
id|fw_remove_class_device
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|error_kfree_fw
suffix:colon
id|kfree
c_func
(paren
id|firmware
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; * release_firmware: - release the resource associated with a firmware image&n; **/
r_void
DECL|function|release_firmware
id|release_firmware
c_func
(paren
r_const
r_struct
id|firmware
op_star
id|fw
)paren
(brace
r_if
c_cond
(paren
id|fw
)paren
(brace
id|vfree
c_func
(paren
id|fw-&gt;data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fw
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * register_firmware: - provide a firmware image for later usage&n; * &n; * Description:&n; *&t;Make sure that @data will be available by requesting firmware @name.&n; *&n; *&t;Note: This will not be possible until some kind of persistence&n; *&t;is available.&n; **/
r_void
DECL|function|register_firmware
id|register_firmware
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
multiline_comment|/* This is meaningless without firmware caching, so until we&n;&t; * decide if firmware caching is reasonable just leave it as a&n;&t; * noop */
)brace
multiline_comment|/* Async support */
DECL|struct|firmware_work
r_struct
id|firmware_work
(brace
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|device
r_struct
id|device
op_star
id|device
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|cont
r_void
(paren
op_star
id|cont
)paren
(paren
r_const
r_struct
id|firmware
op_star
id|fw
comma
r_void
op_star
id|context
)paren
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
DECL|function|request_firmware_work_func
id|request_firmware_work_func
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|firmware_work
op_star
id|fw_work
op_assign
id|arg
suffix:semicolon
r_const
r_struct
id|firmware
op_star
id|fw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|WARN_ON
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|daemonize
c_func
(paren
l_string|&quot;%s/%s&quot;
comma
l_string|&quot;firmware&quot;
comma
id|fw_work-&gt;name
)paren
suffix:semicolon
id|request_firmware
c_func
(paren
op_amp
id|fw
comma
id|fw_work-&gt;name
comma
id|fw_work-&gt;device
)paren
suffix:semicolon
id|fw_work
op_member_access_from_pointer
id|cont
c_func
(paren
id|fw
comma
id|fw_work-&gt;context
)paren
suffix:semicolon
id|release_firmware
c_func
(paren
id|fw
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|fw_work-&gt;module
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fw_work
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * request_firmware_nowait:&n; *&n; * Description:&n; *&t;Asynchronous variant of request_firmware() for contexts where&n; *&t;it is not possible to sleep.&n; *&n; *&t;@cont will be called asynchronously when the firmware request is over.&n; *&n; *&t;@context will be passed over to @cont.&n; *&n; *&t;@fw may be %NULL if firmware request fails.&n; *&n; **/
r_int
DECL|function|request_firmware_nowait
id|request_firmware_nowait
c_func
(paren
r_struct
id|module
op_star
id|module
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|device
op_star
id|device
comma
r_void
op_star
id|context
comma
r_void
(paren
op_star
id|cont
)paren
(paren
r_const
r_struct
id|firmware
op_star
id|fw
comma
r_void
op_star
id|context
)paren
)paren
(brace
r_struct
id|firmware_work
op_star
id|fw_work
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|firmware_work
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fw_work
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|module
)paren
)paren
(brace
id|kfree
c_func
(paren
id|fw_work
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
op_star
id|fw_work
op_assign
(paren
r_struct
id|firmware_work
)paren
(brace
dot
id|module
op_assign
id|module
comma
dot
id|name
op_assign
id|name
comma
dot
id|device
op_assign
id|device
comma
dot
id|context
op_assign
id|context
comma
dot
id|cont
op_assign
id|cont
comma
)brace
suffix:semicolon
id|ret
op_assign
id|kernel_thread
c_func
(paren
id|request_firmware_work_func
comma
id|fw_work
comma
id|CLONE_FS
op_or
id|CLONE_FILES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|fw_work
op_member_access_from_pointer
id|cont
c_func
(paren
l_int|NULL
comma
id|fw_work-&gt;context
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|firmware_class_init
id|firmware_class_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|class_register
c_func
(paren
op_amp
id|firmware_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: class_register failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|error
op_assign
id|class_create_file
c_func
(paren
op_amp
id|firmware_class
comma
op_amp
id|class_attr_timeout
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: class_create_file failed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|class_unregister
c_func
(paren
op_amp
id|firmware_class
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|firmware_class_exit
id|firmware_class_exit
c_func
(paren
r_void
)paren
(brace
id|class_remove_file
c_func
(paren
op_amp
id|firmware_class
comma
op_amp
id|class_attr_timeout
)paren
suffix:semicolon
id|class_unregister
c_func
(paren
op_amp
id|firmware_class
)paren
suffix:semicolon
)brace
DECL|variable|firmware_class_init
id|module_init
c_func
(paren
id|firmware_class_init
)paren
suffix:semicolon
DECL|variable|firmware_class_exit
id|module_exit
c_func
(paren
id|firmware_class_exit
)paren
suffix:semicolon
DECL|variable|release_firmware
id|EXPORT_SYMBOL
c_func
(paren
id|release_firmware
)paren
suffix:semicolon
DECL|variable|request_firmware
id|EXPORT_SYMBOL
c_func
(paren
id|request_firmware
)paren
suffix:semicolon
DECL|variable|request_firmware_nowait
id|EXPORT_SYMBOL
c_func
(paren
id|request_firmware_nowait
)paren
suffix:semicolon
DECL|variable|register_firmware
id|EXPORT_SYMBOL
c_func
(paren
id|register_firmware
)paren
suffix:semicolon
DECL|variable|firmware_class
id|EXPORT_SYMBOL
c_func
(paren
id|firmware_class
)paren
suffix:semicolon
eof
