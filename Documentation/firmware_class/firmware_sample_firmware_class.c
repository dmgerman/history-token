multiline_comment|/*&n; * firmware_sample_firmware_class.c -&n; *&n; * Copyright (c) 2003 Manuel Estrada Sainz &lt;ranty@debian.org&gt;&n; *&n; * NOTE: This is just a probe of concept, if you think that your driver would&n; * be well served by this mechanism please contact me first.&n; *&n; * DON&squot;T USE THIS CODE AS IS&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &quot;linux/firmware.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Manuel Estrada Sainz &lt;ranty@debian.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Hackish sample for using firmware class directly&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|to_class_dev
r_static
r_inline
r_struct
id|class_device
op_star
id|to_class_dev
c_func
(paren
r_struct
id|kobject
op_star
id|obj
)paren
(brace
r_return
id|container_of
c_func
(paren
id|obj
comma
r_struct
id|class_device
comma
id|kobj
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|to_class_dev_attr
r_struct
id|class_device_attribute
op_star
id|to_class_dev_attr
c_func
(paren
r_struct
id|attribute
op_star
id|_attr
)paren
(brace
r_return
id|container_of
c_func
(paren
id|_attr
comma
r_struct
id|class_device_attribute
comma
id|attr
)paren
suffix:semicolon
)brace
r_int
id|sysfs_create_bin_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
)paren
suffix:semicolon
r_int
id|sysfs_remove_bin_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|bin_attribute
op_star
id|attr
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
DECL|member|loading
id|s32
id|loading
suffix:colon
l_int|2
suffix:semicolon
DECL|member|abort
id|u32
m_abort
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
r_class
id|firmware_class
suffix:semicolon
DECL|function|firmware_loading_show
r_static
id|ssize_t
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
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|fw_priv-&gt;loading
)paren
suffix:semicolon
)brace
DECL|function|firmware_loading_store
r_static
id|ssize_t
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
id|prev_loading
op_assign
id|fw_priv-&gt;loading
suffix:semicolon
id|fw_priv-&gt;loading
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
id|fw_priv-&gt;loading
)paren
(brace
r_case
op_minus
l_int|1
suffix:colon
multiline_comment|/* abort load an panic */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* setup load */
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|prev_loading
op_eq
l_int|1
)paren
(brace
multiline_comment|/* finish load and get the device back to working&n;&t;&t;&t; * state */
)brace
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
DECL|function|firmware_data_read
r_static
id|ssize_t
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
multiline_comment|/* read from the devices firmware memory */
r_return
id|count
suffix:semicolon
)brace
DECL|function|firmware_data_write
r_static
id|ssize_t
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
multiline_comment|/* write to the devices firmware memory */
r_return
id|count
suffix:semicolon
)brace
DECL|variable|firmware_attr_data
r_static
r_struct
id|bin_attribute
id|firmware_attr_data
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
DECL|function|fw_setup_class_device
r_static
r_int
id|fw_setup_class_device
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
r_if
c_cond
(paren
op_logical_neg
id|fw_priv
)paren
(brace
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
id|strncpy
c_func
(paren
id|fw_priv-&gt;fw_id
comma
id|fw_name
comma
id|FIRMWARE_NAME_MAX
)paren
suffix:semicolon
id|fw_priv-&gt;fw_id
(braket
id|FIRMWARE_NAME_MAX
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|strncpy
c_func
(paren
id|class_dev-&gt;class_id
comma
id|device-&gt;bus_id
comma
id|BUS_ID_SIZE
)paren
suffix:semicolon
id|class_dev-&gt;class_id
(braket
id|BUS_ID_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|class_dev-&gt;dev
op_assign
id|device
suffix:semicolon
id|class_dev
op_member_access_from_pointer
r_class
op_assign
op_amp
id|firmware_class
comma
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
id|error_free_fw_priv
suffix:semicolon
)brace
id|retval
op_assign
id|sysfs_create_bin_file
c_func
(paren
op_amp
id|class_dev-&gt;kobj
comma
op_amp
id|firmware_attr_data
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
id|firmware_attr_data
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
id|error_free_fw_priv
suffix:colon
id|kfree
c_func
(paren
id|fw_priv
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|fw_remove_class_device
r_static
r_void
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
id|firmware_attr_data
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
id|class_dev
)paren
suffix:semicolon
)brace
DECL|variable|class_dev
r_static
r_struct
id|class_device
op_star
id|class_dev
suffix:semicolon
DECL|variable|my_device
r_static
r_struct
id|device
id|my_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Sample Device&quot;
comma
dot
id|bus_id
op_assign
l_string|&quot;my_dev0&quot;
comma
)brace
suffix:semicolon
DECL|function|firmware_sample_init
r_static
r_int
id|__init
id|firmware_sample_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|device_initialize
c_func
(paren
op_amp
id|my_device
)paren
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|class_dev
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
id|fw_setup_class_device
c_func
(paren
id|class_dev
comma
l_string|&quot;my_firmware_image&quot;
comma
op_amp
id|my_device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|kfree
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|firmware_sample_exit
r_static
r_void
id|__exit
id|firmware_sample_exit
c_func
(paren
r_void
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
id|fw_remove_class_device
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
DECL|variable|firmware_sample_init
id|module_init
c_func
(paren
id|firmware_sample_init
)paren
suffix:semicolon
DECL|variable|firmware_sample_exit
id|module_exit
c_func
(paren
id|firmware_sample_exit
)paren
suffix:semicolon
eof
