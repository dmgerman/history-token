multiline_comment|/*&n; * scsi_sysfs.c&n; *&n; * SCSI sysfs interface routines.&n; *&n; * Created to pull SCSI mid layer sysfs routines into one file.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;scsi_priv.h&quot;
multiline_comment|/*&n; * shost_show_function: macro to create an attr function that can be used to&n; * show a non-bit field.&n; */
DECL|macro|shost_show_function
mdefine_line|#define shost_show_function(field, format_string)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field (struct class_device *class_dev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct Scsi_Host *shost = class_to_shost(class_dev);&t;&t;&bslash;&n;&t;return snprintf (buf, 20, format_string, shost-&gt;field);&t;&bslash;&n;}
multiline_comment|/*&n; * shost_rd_attr: macro to create a function and attribute variable for a&n; * read only field.&n; */
DECL|macro|shost_rd_attr
mdefine_line|#define shost_rd_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;shost_show_function(field, format_string)&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_##field, NULL)
multiline_comment|/*&n; * Create the actual show/store functions and data structures.&n; */
id|shost_rd_attr
c_func
(paren
id|unique_id
comma
l_string|&quot;%u&bslash;n&quot;
)paren
suffix:semicolon
id|shost_rd_attr
c_func
(paren
id|host_busy
comma
l_string|&quot;%hu&bslash;n&quot;
)paren
suffix:semicolon
id|shost_rd_attr
c_func
(paren
id|cmd_per_lun
comma
l_string|&quot;%hd&bslash;n&quot;
)paren
suffix:semicolon
id|shost_rd_attr
c_func
(paren
id|sg_tablesize
comma
l_string|&quot;%hu&bslash;n&quot;
)paren
suffix:semicolon
id|shost_rd_attr
c_func
(paren
id|unchecked_isa_dma
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|scsi_sysfs_shost_attrs
r_static
r_struct
id|class_device_attribute
op_star
id|scsi_sysfs_shost_attrs
(braket
)braket
op_assign
(brace
op_amp
id|class_device_attr_unique_id
comma
op_amp
id|class_device_attr_host_busy
comma
op_amp
id|class_device_attr_cmd_per_lun
comma
op_amp
id|class_device_attr_sg_tablesize
comma
op_amp
id|class_device_attr_unchecked_isa_dma
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|scsi_host_cls_release
r_static
r_void
id|scsi_host_cls_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
id|shost
op_assign
id|class_to_shost
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
)brace
DECL|function|scsi_host_dev_release
r_static
r_void
id|scsi_host_dev_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_struct
id|device
op_star
id|parent
suffix:semicolon
id|parent
op_assign
id|dev-&gt;parent
suffix:semicolon
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|dev
)paren
suffix:semicolon
id|scsi_free_shost
c_func
(paren
id|shost
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
DECL|variable|shost_class
r_struct
r_class
id|shost_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scsi_host&quot;
comma
dot
id|release
op_assign
id|scsi_host_cls_release
comma
)brace
suffix:semicolon
DECL|function|scsi_device_cls_release
r_static
r_void
id|scsi_device_cls_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
id|sdev
op_assign
id|class_to_sdev
c_func
(paren
id|class_dev
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
)brace
DECL|function|scsi_device_dev_release
r_static
r_void
id|scsi_device_dev_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
r_struct
id|device
op_star
id|parent
suffix:semicolon
id|parent
op_assign
id|dev-&gt;parent
suffix:semicolon
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|scsi_free_sdev
c_func
(paren
id|sdev
)paren
suffix:semicolon
id|put_device
c_func
(paren
id|parent
)paren
suffix:semicolon
)brace
DECL|variable|sdev_class
r_struct
r_class
id|sdev_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scsi_device&quot;
comma
dot
id|release
op_assign
id|scsi_device_cls_release
comma
)brace
suffix:semicolon
multiline_comment|/* all probing is done in the individual -&gt;probe routines */
DECL|function|scsi_bus_match
r_static
r_int
id|scsi_bus_match
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
id|gendrv
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|scsi_bus_type
r_struct
id|bus_type
id|scsi_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scsi&quot;
comma
dot
id|match
op_assign
id|scsi_bus_match
comma
)brace
suffix:semicolon
DECL|function|scsi_sysfs_register
r_int
id|scsi_sysfs_register
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
id|bus_register
c_func
(paren
op_amp
id|scsi_bus_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|class_register
c_func
(paren
op_amp
id|shost_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|bus_unregister
suffix:semicolon
id|error
op_assign
id|class_register
c_func
(paren
op_amp
id|sdev_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|class_unregister
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|class_unregister
suffix:colon
id|class_unregister
c_func
(paren
op_amp
id|shost_class
)paren
suffix:semicolon
id|bus_unregister
suffix:colon
id|bus_unregister
c_func
(paren
op_amp
id|scsi_bus_type
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|scsi_sysfs_unregister
r_void
id|scsi_sysfs_unregister
c_func
(paren
r_void
)paren
(brace
id|class_unregister
c_func
(paren
op_amp
id|sdev_class
)paren
suffix:semicolon
id|class_unregister
c_func
(paren
op_amp
id|shost_class
)paren
suffix:semicolon
id|bus_unregister
c_func
(paren
op_amp
id|scsi_bus_type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sdev_show_function: macro to create an attr function that can be used to&n; * show a non-bit field.&n; */
DECL|macro|sdev_show_function
mdefine_line|#define sdev_show_function(field, format_string)&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;sdev_show_##field (struct device *dev, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev;&t;&t;&t;&t;&t;&bslash;&n;&t;sdev = to_scsi_device(dev);&t;&t;&t;&t;&t;&bslash;&n;&t;return snprintf (buf, 20, format_string, sdev-&gt;field);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;
multiline_comment|/*&n; * sdev_rd_attr: macro to create a function and attribute variable for a&n; * read only field.&n; */
DECL|macro|sdev_rd_attr
mdefine_line|#define sdev_rd_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;sdev_show_function(field, format_string)&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, sdev_show_##field, NULL)
multiline_comment|/*&n; * sdev_rd_attr: create a function and attribute variable for a&n; * read/write field.&n; */
DECL|macro|sdev_rw_attr
mdefine_line|#define sdev_rw_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;sdev_show_function(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;sdev_store_##field (struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev;&t;&t;&t;&t;&t;&bslash;&n;&t;sdev = to_scsi_device(dev);&t;&t;&t;&t;&t;&bslash;&n;&t;snscanf (buf, 20, format_string, &amp;sdev-&gt;field);&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO | S_IWUSR, sdev_show_##field, sdev_store_##field)
multiline_comment|/*&n; * sdev_rd_attr: create a function and attribute variable for a&n; * read/write bit field.&n; */
DECL|macro|sdev_rw_attr_bit
mdefine_line|#define sdev_rw_attr_bit(field)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sdev_show_function(field, &quot;%d&bslash;n&quot;)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;sdev_store_##field (struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev;&t;&t;&t;&t;&t;&bslash;&n;&t;ret = scsi_sdev_check_buf_bit(buf);&t;&t;&t;&t;&bslash;&n;&t;if (ret &gt;= 0)&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sdev = to_scsi_device(dev);&t;&t;&t;&t;&bslash;&n;&t;&t;sdev-&gt;field = ret;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = count;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO | S_IWUSR, sdev_show_##field, sdev_store_##field)
multiline_comment|/*&n; * scsi_sdev_check_buf_bit: return 0 if buf is &quot;0&quot;, return 1 if buf is &quot;1&quot;,&n; * else return -EINVAL.&n; */
DECL|function|scsi_sdev_check_buf_bit
r_static
r_int
id|scsi_sdev_check_buf_bit
c_func
(paren
r_const
r_char
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
op_logical_or
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
id|buf
(braket
l_int|2
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;1&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * Create the actual show/store functions and data structures.&n; */
id|sdev_rd_attr
(paren
id|device_blocked
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|queue_depth
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|type
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|scsi_level
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|access_count
comma
l_string|&quot;%d&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|vendor
comma
l_string|&quot;%.8s&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|model
comma
l_string|&quot;%.16s&bslash;n&quot;
)paren
suffix:semicolon
id|sdev_rd_attr
(paren
id|rev
comma
l_string|&quot;%.4s&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|online
id|sdev_rw_attr_bit
(paren
id|online
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|store_rescan_field
id|store_rescan_field
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
id|scsi_rescan_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|rescan
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|store_rescan_field
)paren
multiline_comment|/* Default template for device attributes.  May NOT be modified */
DECL|variable|scsi_sysfs_sdev_attrs
r_static
r_struct
id|device_attribute
op_star
id|scsi_sysfs_sdev_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_device_blocked
comma
op_amp
id|dev_attr_queue_depth
comma
op_amp
id|dev_attr_type
comma
op_amp
id|dev_attr_scsi_level
comma
op_amp
id|dev_attr_access_count
comma
op_amp
id|dev_attr_vendor
comma
op_amp
id|dev_attr_model
comma
op_amp
id|dev_attr_rev
comma
op_amp
id|dev_attr_online
comma
op_amp
id|dev_attr_rescan
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|attr_overridden
r_static
r_struct
id|device_attribute
op_star
id|attr_overridden
c_func
(paren
r_struct
id|device_attribute
op_star
op_star
id|attrs
comma
r_struct
id|device_attribute
op_star
id|attr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attrs
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attrs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|attrs
(braket
id|i
)braket
op_member_access_from_pointer
id|attr.name
comma
id|attr-&gt;attr.name
)paren
)paren
r_return
id|attrs
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|attr_add
r_static
r_int
id|attr_add
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
(brace
r_struct
id|device_attribute
op_star
id|base_attr
suffix:semicolon
multiline_comment|/*&n;&t; * Spare the caller from having to copy things it&squot;s not interested in.&n;&t; */
id|base_attr
op_assign
id|attr_overridden
c_func
(paren
id|scsi_sysfs_sdev_attrs
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base_attr
)paren
(brace
multiline_comment|/* extend permissions */
id|attr-&gt;attr.mode
op_or_assign
id|base_attr-&gt;attr.mode
suffix:semicolon
multiline_comment|/* override null show/store with default */
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;show
)paren
id|attr-&gt;show
op_assign
id|base_attr-&gt;show
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;store
)paren
id|attr-&gt;store
op_assign
id|base_attr-&gt;store
suffix:semicolon
)brace
r_return
id|device_create_file
c_func
(paren
id|dev
comma
id|attr
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_device_register - register a scsi device with the scsi bus&n; * @sdev:&t;scsi_device to register&n; *&n; * Return value:&n; * &t;0 on Success / non-zero on Failure&n; **/
DECL|function|scsi_device_register
r_int
id|scsi_device_register
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_int
id|error
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|set_bit
c_func
(paren
id|SDEV_ADD
comma
op_amp
id|sdev-&gt;sdev_state
)paren
suffix:semicolon
id|device_initialize
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|sdev-&gt;sdev_gendev.bus_id
comma
l_string|&quot;%d:%d:%d:%d&quot;
comma
id|sdev-&gt;host-&gt;host_no
comma
id|sdev-&gt;channel
comma
id|sdev-&gt;id
comma
id|sdev-&gt;lun
)paren
suffix:semicolon
id|sdev-&gt;sdev_gendev.parent
op_assign
op_amp
id|sdev-&gt;host-&gt;shost_gendev
suffix:semicolon
id|sdev-&gt;sdev_gendev.bus
op_assign
op_amp
id|scsi_bus_type
suffix:semicolon
id|sdev-&gt;sdev_gendev.release
op_assign
id|scsi_device_dev_release
suffix:semicolon
id|class_device_initialize
c_func
(paren
op_amp
id|sdev-&gt;sdev_classdev
)paren
suffix:semicolon
id|sdev-&gt;sdev_classdev.dev
op_assign
op_amp
id|sdev-&gt;sdev_gendev
suffix:semicolon
id|sdev-&gt;sdev_classdev
dot
r_class
op_assign
op_amp
id|sdev_class
suffix:semicolon
id|snprintf
c_func
(paren
id|sdev-&gt;sdev_classdev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;%d:%d:%d:%d&quot;
comma
id|sdev-&gt;host-&gt;host_no
comma
id|sdev-&gt;channel
comma
id|sdev-&gt;id
comma
id|sdev-&gt;lun
)paren
suffix:semicolon
id|error
op_assign
id|device_add
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
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
id|KERN_INFO
l_string|&quot;error 1&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|get_device
c_func
(paren
id|sdev-&gt;sdev_gendev.parent
)paren
suffix:semicolon
id|error
op_assign
id|class_device_add
c_func
(paren
op_amp
id|sdev-&gt;sdev_classdev
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
id|KERN_INFO
l_string|&quot;error 2&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|clean_device
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|get_device
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;host-&gt;hostt-&gt;sdev_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sdev-&gt;host-&gt;hostt-&gt;sdev_attrs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|error
op_assign
id|attr_add
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
comma
id|sdev-&gt;host-&gt;hostt-&gt;sdev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|scsi_device_unregister
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|scsi_sysfs_sdev_attrs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|attr_overridden
c_func
(paren
id|sdev-&gt;host-&gt;hostt-&gt;sdev_attrs
comma
id|scsi_sysfs_sdev_attrs
(braket
id|i
)braket
)paren
)paren
(brace
id|error
op_assign
id|device_create_file
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
comma
id|scsi_sysfs_sdev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|scsi_device_unregister
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
id|clean_device
suffix:colon
id|device_del
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_device_unregister - unregister a device from the scsi bus&n; * @sdev:&t;scsi_device to unregister&n; **/
DECL|function|scsi_device_unregister
r_void
id|scsi_device_unregister
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_struct
r_class
op_star
r_class
op_assign
id|class_get
c_func
(paren
op_amp
id|sdev_class
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|sdev-&gt;sdev_classdev
)paren
suffix:semicolon
r_if
c_cond
(paren
r_class
)paren
(brace
id|down_write
c_func
(paren
op_amp
r_class
op_member_access_from_pointer
id|subsys.rwsem
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|SDEV_DEL
comma
op_amp
id|sdev-&gt;sdev_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;access_count
op_eq
l_int|0
)paren
id|device_del
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
r_class
op_member_access_from_pointer
id|subsys.rwsem
)paren
suffix:semicolon
)brace
id|put_device
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
id|class_put
c_func
(paren
op_amp
id|sdev_class
)paren
suffix:semicolon
)brace
DECL|function|scsi_register_driver
r_int
id|scsi_register_driver
c_func
(paren
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
id|drv-&gt;bus
op_assign
op_amp
id|scsi_bus_type
suffix:semicolon
r_return
id|driver_register
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|function|scsi_register_interface
r_int
id|scsi_register_interface
c_func
(paren
r_struct
id|class_interface
op_star
id|intf
)paren
(brace
id|intf
op_member_access_from_pointer
r_class
op_assign
op_amp
id|sdev_class
suffix:semicolon
r_return
id|class_interface_register
c_func
(paren
id|intf
)paren
suffix:semicolon
)brace
DECL|function|scsi_sysfs_init_host
r_void
id|scsi_sysfs_init_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
id|device_initialize
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|shost-&gt;shost_gendev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;host%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|shost-&gt;shost_gendev.name
comma
id|DEVICE_NAME_SIZE
comma
l_string|&quot;%s&quot;
comma
id|shost-&gt;hostt-&gt;proc_name
)paren
suffix:semicolon
id|shost-&gt;shost_gendev.release
op_assign
id|scsi_host_dev_release
suffix:semicolon
id|class_device_initialize
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|shost-&gt;shost_classdev.dev
op_assign
op_amp
id|shost-&gt;shost_gendev
suffix:semicolon
id|shost-&gt;shost_classdev
dot
r_class
op_assign
op_amp
id|shost_class
suffix:semicolon
id|snprintf
c_func
(paren
id|shost-&gt;shost_classdev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;host%d&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
)brace
DECL|function|class_attr_overridden
r_static
r_struct
id|class_device_attribute
op_star
id|class_attr_overridden
c_func
(paren
r_struct
id|class_device_attribute
op_star
op_star
id|attrs
comma
r_struct
id|class_device_attribute
op_star
id|attr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attrs
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|attrs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|attrs
(braket
id|i
)braket
op_member_access_from_pointer
id|attr.name
comma
id|attr-&gt;attr.name
)paren
)paren
r_return
id|attrs
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|class_attr_add
r_static
r_int
id|class_attr_add
c_func
(paren
r_struct
id|class_device
op_star
id|classdev
comma
r_struct
id|class_device_attribute
op_star
id|attr
)paren
(brace
r_struct
id|class_device_attribute
op_star
id|base_attr
suffix:semicolon
multiline_comment|/*&n;&t; * Spare the caller from having to copy things it&squot;s not interested in.&n;&t; */
id|base_attr
op_assign
id|class_attr_overridden
c_func
(paren
id|scsi_sysfs_shost_attrs
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base_attr
)paren
(brace
multiline_comment|/* extend permissions */
id|attr-&gt;attr.mode
op_or_assign
id|base_attr-&gt;attr.mode
suffix:semicolon
multiline_comment|/* override null show/store with default */
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;show
)paren
id|attr-&gt;show
op_assign
id|base_attr-&gt;show
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr-&gt;store
)paren
id|attr-&gt;store
op_assign
id|base_attr-&gt;store
suffix:semicolon
)brace
r_return
id|class_device_create_file
c_func
(paren
id|classdev
comma
id|attr
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_sysfs_add_host - add scsi host to subsystem&n; * @shost:     scsi host struct to add to subsystem&n; * @dev:       parent struct device pointer&n; **/
DECL|function|scsi_sysfs_add_host
r_int
id|scsi_sysfs_add_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|error
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;shost_gendev.parent
)paren
id|shost-&gt;shost_gendev.parent
op_assign
id|dev
ques
c_cond
id|dev
suffix:colon
op_amp
id|legacy_bus
suffix:semicolon
id|error
op_assign
id|device_add
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|set_bit
c_func
(paren
id|SHOST_ADD
comma
op_amp
id|shost-&gt;shost_state
)paren
suffix:semicolon
id|get_device
c_func
(paren
id|shost-&gt;shost_gendev.parent
)paren
suffix:semicolon
id|error
op_assign
id|class_device_add
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|clean_device
suffix:semicolon
id|get_device
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shost-&gt;hostt-&gt;shost_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|shost-&gt;hostt-&gt;shost_attrs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|error
op_assign
id|class_attr_add
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
comma
id|shost-&gt;hostt-&gt;shost_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|clean_class
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|scsi_sysfs_shost_attrs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|class_attr_overridden
c_func
(paren
id|shost-&gt;hostt-&gt;shost_attrs
comma
id|scsi_sysfs_shost_attrs
(braket
id|i
)braket
)paren
)paren
(brace
id|error
op_assign
id|class_device_create_file
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
comma
id|scsi_sysfs_shost_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|clean_class
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
id|clean_class
suffix:colon
id|class_device_del
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|clean_device
suffix:colon
id|device_del
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_sysfs_remove_host - remove scsi host from subsystem&n; * @shost:     scsi host to remove from subsystem&n; **/
DECL|function|scsi_sysfs_remove_host
r_void
id|scsi_sysfs_remove_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|shost-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|SHOST_DEL
comma
op_amp
id|shost-&gt;shost_state
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|shost-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|shost-&gt;shost_classdev
)paren
suffix:semicolon
id|device_del
c_func
(paren
op_amp
id|shost-&gt;shost_gendev
)paren
suffix:semicolon
)brace
eof
