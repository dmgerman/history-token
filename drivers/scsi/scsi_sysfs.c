multiline_comment|/*&n; * scsi_sysfs.c&n; *&n; * SCSI sysfs interface routines.&n; *&n; * Created to pull SCSI mid layer sysfs routines into one file.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
multiline_comment|/**&n; * scsi_host_class_name_show - copy out the SCSI host name&n; * @dev:&t;&t;device to check&n; * @page:&t;&t;copy data into this area&n; * @count:&t;&t;number of bytes to copy&n; * @off:&t;&t;start at this offset in page&n; * Return:&n; *     number of bytes written into page.&n; **/
DECL|function|scsi_host_class_name_show
r_static
id|ssize_t
id|scsi_host_class_name_show
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|page
comma
r_int
id|count
comma
id|loff_t
id|off
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
id|shost
op_assign
id|to_scsi_host
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|page
comma
id|count
comma
l_string|&quot;scsi%d&bslash;n&quot;
comma
id|shost-&gt;host_no
)paren
suffix:semicolon
)brace
id|DEVICE_ATTR
c_func
(paren
id|class_name
comma
id|S_IRUGO
comma
id|scsi_host_class_name_show
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|scsi_host_class_add_dev
r_static
r_int
id|scsi_host_class_add_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|device_create_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_class_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scsi_host_class_rm_dev
r_static
r_void
id|scsi_host_class_rm_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|device_remove_file
c_func
(paren
id|dev
comma
op_amp
id|dev_attr_class_name
)paren
suffix:semicolon
)brace
DECL|variable|shost_devclass
r_struct
id|device_class
id|shost_devclass
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scsi-host&quot;
comma
dot
id|add_device
op_assign
id|scsi_host_class_add_dev
comma
dot
id|remove_device
op_assign
id|scsi_host_class_rm_dev
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * scsi_bus_match:&n; * @dev:&n; * @dev_driver:&n; *&n; * Return value:&n; **/
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
id|dev_driver
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;sg&quot;
comma
id|dev_driver-&gt;name
)paren
)paren
(brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|dev-&gt;bus_id
comma
l_string|&quot;:gen&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;st&quot;
comma
id|dev_driver-&gt;name
)paren
)paren
(brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|dev-&gt;bus_id
comma
l_string|&quot;:mt&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;sd&quot;
comma
id|dev_driver-&gt;name
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|strstr
c_func
(paren
id|dev-&gt;bus_id
comma
l_string|&quot;:gen&quot;
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|strstr
c_func
(paren
id|dev-&gt;bus_id
comma
l_string|&quot;:mt&quot;
)paren
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|scsi_bus_type
r_static
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
id|bus_register
c_func
(paren
op_amp
id|scsi_bus_type
)paren
suffix:semicolon
id|devclass_register
c_func
(paren
op_amp
id|shost_devclass
)paren
suffix:semicolon
r_return
l_int|0
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
id|devclass_unregister
c_func
(paren
op_amp
id|shost_devclass
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
multiline_comment|/**&n; * scsi_upper_driver_register - register upper level driver.&n; * @sdev_tp:&t;Upper level driver to register with the scsi bus.&n; *&n; * Return value:&n; * &t;0 on Success / non-zero on Failure&n; **/
DECL|function|scsi_upper_driver_register
r_int
id|scsi_upper_driver_register
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
id|sdev_tp
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|sdev_tp-&gt;scsi_driverfs_driver.bus
op_assign
op_amp
id|scsi_bus_type
suffix:semicolon
id|error
op_assign
id|driver_register
c_func
(paren
op_amp
id|sdev_tp-&gt;scsi_driverfs_driver
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_upper_driver_unregister - unregister upper level driver &n; * @sdev_tp:&t;Upper level driver to unregister with the scsi bus.&n; *&n; **/
DECL|function|scsi_upper_driver_unregister
r_void
id|scsi_upper_driver_unregister
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
id|sdev_tp
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|sdev_tp-&gt;scsi_driverfs_driver
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_device_type_read - copy out the SCSI type&n; * @dev:&t;&t;device to check&n; * @page:&t;&t;copy data into this area&n; * @count:&t;&t;number of bytes to copy&n; * @off:&t;&t;start at this offset in page&n; *&n; * Return:&n; *     number of bytes written into page.&n; **/
DECL|function|scsi_device_type_read
r_static
id|ssize_t
id|scsi_device_type_read
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|page
comma
r_int
id|count
comma
id|loff_t
id|off
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
id|type
suffix:semicolon
r_if
c_cond
(paren
id|off
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sdev-&gt;type
OG
id|MAX_SCSI_DEVICE_CODE
)paren
op_logical_or
(paren
id|scsi_device_types
(braket
(paren
r_int
)paren
id|sdev-&gt;type
)braket
op_eq
l_int|NULL
)paren
)paren
id|type
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
r_else
id|type
op_assign
id|scsi_device_types
(braket
(paren
r_int
)paren
id|sdev-&gt;type
)braket
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|page
comma
id|count
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create dev_attr_type. This is different from the dev_attr_type in scsi&n; * upper level drivers.&n; */
r_static
id|DEVICE_ATTR
c_func
(paren
id|type
comma
id|S_IRUGO
comma
id|scsi_device_type_read
comma
l_int|NULL
)paren
suffix:semicolon
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
suffix:semicolon
id|sprintf
c_func
(paren
id|sdev-&gt;sdev_driverfs_dev.bus_id
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
id|sdev-&gt;sdev_driverfs_dev.parent
op_assign
id|sdev-&gt;host-&gt;host_gendev
suffix:semicolon
id|sdev-&gt;sdev_driverfs_dev.bus
op_assign
op_amp
id|scsi_bus_type
suffix:semicolon
id|error
op_assign
id|device_register
c_func
(paren
op_amp
id|sdev-&gt;sdev_driverfs_dev
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
id|device_create_file
c_func
(paren
op_amp
id|sdev-&gt;sdev_driverfs_dev
comma
op_amp
id|dev_attr_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|device_unregister
c_func
(paren
op_amp
id|sdev-&gt;sdev_driverfs_dev
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
id|device_remove_file
c_func
(paren
op_amp
id|sdev-&gt;sdev_driverfs_dev
comma
op_amp
id|dev_attr_type
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|sdev-&gt;sdev_driverfs_dev
)paren
suffix:semicolon
)brace
eof
