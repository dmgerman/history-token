multiline_comment|/*&n; * scsi_sysfs.c&n; *&n; * SCSI sysfs interface routines.&n; *&n; * Created to pull SCSI mid layer sysfs routines into one file.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &quot;scsi_priv.h&quot;
macro_line|#include &quot;scsi_logging.h&quot;
r_static
r_struct
(brace
DECL|member|value
r_enum
id|scsi_device_state
id|value
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|sdev_states
)brace
id|sdev_states
(braket
)braket
op_assign
(brace
(brace
id|SDEV_CREATED
comma
l_string|&quot;created&quot;
)brace
comma
(brace
id|SDEV_RUNNING
comma
l_string|&quot;running&quot;
)brace
comma
(brace
id|SDEV_CANCEL
comma
l_string|&quot;cancel&quot;
)brace
comma
(brace
id|SDEV_DEL
comma
l_string|&quot;deleted&quot;
)brace
comma
(brace
id|SDEV_QUIESCE
comma
l_string|&quot;quiesce&quot;
)brace
comma
(brace
id|SDEV_OFFLINE
comma
l_string|&quot;offline&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|scsi_device_state_name
r_const
r_char
op_star
id|scsi_device_state_name
c_func
(paren
r_enum
id|scsi_device_state
id|state
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
op_assign
l_int|NULL
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
r_sizeof
(paren
id|sdev_states
)paren
op_div
r_sizeof
(paren
id|sdev_states
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdev_states
(braket
id|i
)braket
dot
id|value
op_eq
id|state
)paren
(brace
id|name
op_assign
id|sdev_states
(braket
id|i
)braket
dot
id|name
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|name
suffix:semicolon
)brace
DECL|function|check_set
r_static
r_int
id|check_set
c_func
(paren
r_int
r_int
op_star
id|val
comma
r_char
op_star
id|src
)paren
(brace
r_char
op_star
id|last
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|src
comma
l_string|&quot;-&quot;
comma
l_int|20
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|val
op_assign
id|SCAN_WILD_CARD
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Doesn&squot;t check for int overflow&n;&t;&t; */
op_star
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|src
comma
op_amp
id|last
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|last
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scsi_scan
r_static
r_int
id|scsi_scan
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_const
r_char
op_star
id|str
)paren
(brace
r_char
id|s1
(braket
l_int|15
)braket
comma
id|s2
(braket
l_int|15
)braket
comma
id|s3
(braket
l_int|15
)braket
comma
id|junk
suffix:semicolon
r_int
r_int
id|channel
comma
id|id
comma
id|lun
suffix:semicolon
r_int
id|res
suffix:semicolon
id|res
op_assign
id|sscanf
c_func
(paren
id|str
comma
l_string|&quot;%10s %10s %10s %c&quot;
comma
id|s1
comma
id|s2
comma
id|s3
comma
op_amp
id|junk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|check_set
c_func
(paren
op_amp
id|channel
comma
id|s1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|check_set
c_func
(paren
op_amp
id|id
comma
id|s2
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|check_set
c_func
(paren
op_amp
id|lun
comma
id|s3
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|res
op_assign
id|scsi_scan_host_selected
c_func
(paren
id|shost
comma
id|channel
comma
id|id
comma
id|lun
comma
l_int|1
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * shost_show_function: macro to create an attr function that can be used to&n; * show a non-bit field.&n; */
DECL|macro|shost_show_function
mdefine_line|#define shost_show_function(name, field, format_string)&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##name (struct class_device *class_dev, char *buf)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct Scsi_Host *shost = class_to_shost(class_dev);&t;&t;&bslash;&n;&t;return snprintf (buf, 20, format_string, shost-&gt;field);&t;&t;&bslash;&n;}
multiline_comment|/*&n; * shost_rd_attr: macro to create a function and attribute variable for a&n; * read only field.&n; */
DECL|macro|shost_rd_attr2
mdefine_line|#define shost_rd_attr2(name, field, format_string)&t;&t;&t;&bslash;&n;&t;shost_show_function(name, field, format_string)&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(name, S_IRUGO, show_##name, NULL);
DECL|macro|shost_rd_attr
mdefine_line|#define shost_rd_attr(field, format_string) &bslash;&n;shost_rd_attr2(field, field, format_string)
multiline_comment|/*&n; * Create the actual show/store functions and data structures.&n; */
DECL|function|store_scan
r_static
id|ssize_t
id|store_scan
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
id|Scsi_Host
op_star
id|shost
op_assign
id|class_to_shost
c_func
(paren
id|class_dev
)paren
suffix:semicolon
r_int
id|res
suffix:semicolon
id|res
op_assign
id|scsi_scan
c_func
(paren
id|shost
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|0
)paren
id|res
op_assign
id|count
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
suffix:semicolon
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|scan
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|store_scan
)paren
suffix:semicolon
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
id|shost_rd_attr2
c_func
(paren
id|proc_name
comma
id|hostt-&gt;proc_name
comma
l_string|&quot;%s&bslash;n&quot;
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
op_amp
id|class_device_attr_proc_name
comma
op_amp
id|class_device_attr_scan
comma
l_int|NULL
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
r_int
r_int
id|flags
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
id|spin_lock_irqsave
c_func
(paren
id|sdev-&gt;host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sdev-&gt;siblings
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sdev-&gt;same_target_siblings
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|sdev-&gt;starved_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;single_lun
op_logical_and
op_decrement
id|sdev-&gt;sdev_target-&gt;starget_refcnt
op_eq
l_int|0
)paren
id|kfree
c_func
(paren
id|sdev-&gt;sdev_target
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|sdev-&gt;host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;request_queue
)paren
id|scsi_free_queue
c_func
(paren
id|sdev-&gt;request_queue
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sdev-&gt;inquiry
)paren
suffix:semicolon
id|kfree
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
r_struct
id|scsi_device
op_star
id|sdp
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
(paren
id|sdp-&gt;inq_periph_qual
op_eq
id|SCSI_INQ_PQ_CON
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
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
op_logical_neg
id|error
)paren
(brace
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
id|bus_unregister
c_func
(paren
op_amp
id|scsi_bus_type
)paren
suffix:semicolon
)brace
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
mdefine_line|#define sdev_rd_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;sdev_show_function(field, format_string)&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO, sdev_show_##field, NULL);
multiline_comment|/*&n; * sdev_rd_attr: create a function and attribute variable for a&n; * read/write field.&n; */
DECL|macro|sdev_rw_attr
mdefine_line|#define sdev_rw_attr(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;sdev_show_function(field, format_string)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;sdev_store_##field (struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev;&t;&t;&t;&t;&t;&bslash;&n;&t;sdev = to_scsi_device(dev);&t;&t;&t;&t;&t;&bslash;&n;&t;snscanf (buf, 20, format_string, &amp;sdev-&gt;field);&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO | S_IWUSR, sdev_show_##field, sdev_store_##field);
multiline_comment|/* Currently we don&squot;t export bit fields, but we might in future,&n; * so leave this code in */
macro_line|#if 0
multiline_comment|/*&n; * sdev_rd_attr: create a function and attribute variable for a&n; * read/write bit field.&n; */
mdefine_line|#define sdev_rw_attr_bit(field)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;sdev_show_function(field, &quot;%d&bslash;n&quot;)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;sdev_store_##field (struct device *dev, const char *buf, size_t count)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev;&t;&t;&t;&t;&t;&bslash;&n;&t;ret = scsi_sdev_check_buf_bit(buf);&t;&t;&t;&t;&bslash;&n;&t;if (ret &gt;= 0)&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sdev = to_scsi_device(dev);&t;&t;&t;&t;&bslash;&n;&t;&t;sdev-&gt;field = ret;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = count;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static DEVICE_ATTR(field, S_IRUGO | S_IWUSR, sdev_show_##field, sdev_store_##field);
multiline_comment|/*&n; * scsi_sdev_check_buf_bit: return 0 if buf is &quot;0&quot;, return 1 if buf is &quot;1&quot;,&n; * else return -EINVAL.&n; */
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
macro_line|#endif
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
r_static
id|ssize_t
DECL|function|sdev_show_timeout
id|sdev_show_timeout
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
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|snprintf
(paren
id|buf
comma
l_int|20
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|sdev-&gt;timeout
op_div
id|HZ
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|sdev_store_timeout
id|sdev_store_timeout
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
id|scsi_device
op_star
id|sdev
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sscanf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
op_amp
id|timeout
)paren
suffix:semicolon
id|sdev-&gt;timeout
op_assign
id|timeout
op_star
id|HZ
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|timeout
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|sdev_show_timeout
comma
id|sdev_store_timeout
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
suffix:semicolon
DECL|function|sdev_store_delete
r_static
id|ssize_t
id|sdev_store_delete
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
id|buf
comma
r_int
id|count
)paren
(brace
id|scsi_remove_device
c_func
(paren
id|to_scsi_device
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DEVICE_ATTR
c_func
(paren
r_delete
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|sdev_store_delete
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|store_state_field
id|store_state_field
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
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_enum
id|scsi_device_state
id|state
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
r_sizeof
(paren
id|sdev_states
)paren
op_div
r_sizeof
(paren
id|sdev_states
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|sdev_states
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|sdev_states
(braket
id|i
)braket
dot
id|name
comma
id|buf
comma
id|len
)paren
op_eq
l_int|0
op_logical_and
id|buf
(braket
id|len
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|state
op_assign
id|sdev_states
(braket
id|i
)braket
dot
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|state
)paren
)paren
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
DECL|function|show_state_field
id|show_state_field
c_func
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
r_struct
id|scsi_device
op_star
id|sdev
op_assign
id|to_scsi_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
id|scsi_device_state_name
c_func
(paren
id|sdev-&gt;sdev_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
l_int|20
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
)brace
id|DEVICE_ATTR
c_func
(paren
id|state
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|show_state_field
comma
id|store_state_field
)paren
suffix:semicolon
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
id|dev_attr_vendor
comma
op_amp
id|dev_attr_model
comma
op_amp
id|dev_attr_rev
comma
op_amp
id|dev_attr_rescan
comma
op_amp
id|dev_attr_delete
comma
op_amp
id|dev_attr_state
comma
op_amp
id|dev_attr_timeout
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
multiline_comment|/**&n; * scsi_sysfs_add_sdev - add scsi device to sysfs&n; * @sdev:&t;scsi_device to add&n; *&n; * Return value:&n; * &t;0 on Success / non-zero on Failure&n; **/
DECL|function|scsi_sysfs_add_sdev
r_int
id|scsi_sysfs_add_sdev
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_struct
id|class_device_attribute
op_star
op_star
id|attrs
suffix:semicolon
r_int
id|error
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_RUNNING
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|error
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
)brace
multiline_comment|/* take a reference for the sdev_classdev; this is&n;&t; * released by the sdev_class .release */
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
id|sdev-&gt;transport_classdev
dot
r_class
)paren
(brace
id|error
op_assign
id|class_device_add
c_func
(paren
op_amp
id|sdev-&gt;transport_classdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|clean_device2
suffix:semicolon
multiline_comment|/* take a reference for the transport_classdev; this&n;&t;&t; * is released by the transport_class .release */
id|get_device
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
)brace
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
(brace
id|scsi_remove_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
(brace
id|scsi_remove_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|sdev-&gt;transport_classdev
dot
r_class
)paren
(brace
id|attrs
op_assign
id|sdev-&gt;host-&gt;transportt-&gt;attrs
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
(brace
id|error
op_assign
id|class_device_create_file
c_func
(paren
op_amp
id|sdev-&gt;transport_classdev
comma
id|attrs
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
(brace
id|scsi_remove_device
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|clean_device2
suffix:colon
id|class_device_del
c_func
(paren
op_amp
id|sdev-&gt;sdev_classdev
)paren
suffix:semicolon
id|clean_device
suffix:colon
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_CANCEL
)paren
suffix:semicolon
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
multiline_comment|/**&n; * scsi_remove_device - unregister a device from the scsi bus&n; * @sdev:&t;scsi_device to unregister&n; **/
DECL|function|scsi_remove_device
r_void
id|scsi_remove_device
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_if
c_cond
(paren
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_CANCEL
)paren
op_ne
l_int|0
)paren
r_return
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
id|sdev-&gt;transport_classdev
dot
r_class
)paren
id|class_device_unregister
c_func
(paren
op_amp
id|sdev-&gt;transport_classdev
)paren
suffix:semicolon
id|device_del
c_func
(paren
op_amp
id|sdev-&gt;sdev_gendev
)paren
suffix:semicolon
id|scsi_device_set_state
c_func
(paren
id|sdev
comma
id|SDEV_DEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;host-&gt;hostt-&gt;slave_destroy
)paren
id|sdev-&gt;host-&gt;hostt
op_member_access_from_pointer
id|slave_destroy
c_func
(paren
id|sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdev-&gt;host-&gt;transportt-&gt;cleanup
)paren
id|sdev-&gt;host-&gt;transportt
op_member_access_from_pointer
id|cleanup
c_func
(paren
id|sdev
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
r_return
id|error
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
r_return
id|error
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* A blank transport template that is used in drivers that don&squot;t&n; * yet implement Transport Attributes */
DECL|variable|blank_transport_template
r_struct
id|scsi_transport_template
id|blank_transport_template
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
eof
