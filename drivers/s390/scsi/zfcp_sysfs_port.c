multiline_comment|/*&n; * linux/drivers/s390/scsi/zfcp_sysfs_port.c&n; *&n; * FCP adapter driver for IBM eServer zSeries&n; *&n; * sysfs port related routines&n; *&n; * Copyright (C) 2003 IBM Entwicklung GmbH, IBM Corporation&n; * Authors:&n; *      Martin Peschke &lt;mpeschke@de.ibm.com&gt;&n; *&t;Heiko Carstens &lt;heiko.carstens@de.ibm.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|ZFCP_SYSFS_PORT_C_REVISION
mdefine_line|#define ZFCP_SYSFS_PORT_C_REVISION &quot;$Revision: 1.26 $&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &quot;zfcp_ext.h&quot;
macro_line|#include &quot;zfcp_def.h&quot;
DECL|macro|ZFCP_LOG_AREA
mdefine_line|#define ZFCP_LOG_AREA                   ZFCP_LOG_AREA_CONFIG
DECL|macro|ZFCP_LOG_AREA_PREFIX
mdefine_line|#define ZFCP_LOG_AREA_PREFIX            ZFCP_LOG_AREA_PREFIX_CONFIG
multiline_comment|/**&n; * zfcp_sysfs_port_release - gets called when a struct device port is released&n; * @dev: pointer to belonging device&n; */
r_void
DECL|function|zfcp_sysfs_port_release
id|zfcp_sysfs_port_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
id|port
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|zfcp_port_dequeue
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * ZFCP_DEFINE_PORT_ATTR&n; * @_name:   name of show attribute&n; * @_format: format string&n; * @_value:  value to print&n; *&n; * Generates attributes for a port.&n; */
DECL|macro|ZFCP_DEFINE_PORT_ATTR
mdefine_line|#define ZFCP_DEFINE_PORT_ATTR(_name, _format, _value)                    &bslash;&n;static ssize_t zfcp_sysfs_port_##_name##_show(struct device *dev,        &bslash;&n;                                              char *buf)                 &bslash;&n;{                                                                        &bslash;&n;        struct zfcp_port *port;                                          &bslash;&n;                                                                         &bslash;&n;        port = dev_get_drvdata(dev);                                     &bslash;&n;        return sprintf(buf, _format, _value);                            &bslash;&n;}                                                                        &bslash;&n;                                                                         &bslash;&n;static DEVICE_ATTR(_name, S_IRUGO, zfcp_sysfs_port_##_name##_show, NULL);
id|ZFCP_DEFINE_PORT_ATTR
c_func
(paren
id|status
comma
l_string|&quot;0x%08x&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|port-&gt;status
)paren
)paren
suffix:semicolon
id|ZFCP_DEFINE_PORT_ATTR
c_func
(paren
id|wwnn
comma
l_string|&quot;0x%016llx&bslash;n&quot;
comma
id|port-&gt;wwnn
)paren
suffix:semicolon
id|ZFCP_DEFINE_PORT_ATTR
c_func
(paren
id|d_id
comma
l_string|&quot;0x%06x&bslash;n&quot;
comma
id|port-&gt;d_id
)paren
suffix:semicolon
id|ZFCP_DEFINE_PORT_ATTR
c_func
(paren
id|scsi_id
comma
l_string|&quot;0x%x&bslash;n&quot;
comma
id|port-&gt;scsi_id
)paren
suffix:semicolon
multiline_comment|/**&n; * zfcp_sysfs_unit_add_store - add a unit to sysfs tree&n; * @dev: pointer to belonging device&n; * @buf: pointer to input buffer&n; * @count: number of bytes in buffer&n; *&n; * Store function of the &quot;unit_add&quot; attribute of a port.&n; */
r_static
id|ssize_t
DECL|function|zfcp_sysfs_unit_add_store
id|zfcp_sysfs_unit_add_store
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
id|fcp_lun_t
id|fcp_lun
suffix:semicolon
r_char
op_star
id|endp
suffix:semicolon
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|zfcp_data.config_sema
)paren
suffix:semicolon
id|port
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_test_mask
c_func
(paren
id|ZFCP_STATUS_COMMON_REMOVE
comma
op_amp
id|port-&gt;status
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|fcp_lun
op_assign
id|simple_strtoull
c_func
(paren
id|buf
comma
op_amp
id|endp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|endp
op_plus
l_int|1
)paren
OL
(paren
id|buf
op_plus
id|count
)paren
)paren
r_goto
id|out
suffix:semicolon
id|unit
op_assign
id|zfcp_unit_enqueue
c_func
(paren
id|port
comma
id|fcp_lun
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unit
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|zfcp_port_get
c_func
(paren
id|port
)paren
suffix:semicolon
multiline_comment|/* try to open unit only if adapter is online */
r_if
c_cond
(paren
id|port-&gt;adapter-&gt;ccw_device-&gt;online
op_eq
l_int|1
)paren
id|zfcp_erp_unit_reopen
c_func
(paren
id|unit
comma
id|ZFCP_STATUS_COMMON_ERP_FAILED
)paren
suffix:semicolon
id|zfcp_unit_put
c_func
(paren
id|unit
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|zfcp_data.config_sema
)paren
suffix:semicolon
r_return
id|retval
ques
c_cond
id|retval
suffix:colon
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|unit_add
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|zfcp_sysfs_unit_add_store
)paren
suffix:semicolon
multiline_comment|/**&n; * zfcp_sysfs_unit_remove_store - remove a unit from sysfs tree&n; * @dev: pointer to belonging device&n; * @buf: pointer to input buffer&n; * @count: number of bytes in buffer&n; */
r_static
id|ssize_t
DECL|function|zfcp_sysfs_unit_remove_store
id|zfcp_sysfs_unit_remove_store
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
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
r_struct
id|zfcp_unit
op_star
id|unit
suffix:semicolon
id|fcp_lun_t
id|fcp_lun
suffix:semicolon
r_char
op_star
id|endp
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|zfcp_data.config_sema
)paren
suffix:semicolon
id|port
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_test_mask
c_func
(paren
id|ZFCP_STATUS_COMMON_REMOVE
comma
op_amp
id|port-&gt;status
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|fcp_lun
op_assign
id|simple_strtoull
c_func
(paren
id|buf
comma
op_amp
id|endp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|endp
op_plus
l_int|1
)paren
OL
(paren
id|buf
op_plus
id|count
)paren
)paren
r_goto
id|out
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|zfcp_data.config_lock
)paren
suffix:semicolon
id|unit
op_assign
id|zfcp_get_unit_by_lun
c_func
(paren
id|port
comma
id|fcp_lun
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_logical_and
(paren
id|atomic_read
c_func
(paren
op_amp
id|unit-&gt;refcount
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|zfcp_unit_get
c_func
(paren
id|unit
)paren
suffix:semicolon
id|atomic_set_mask
c_func
(paren
id|ZFCP_STATUS_COMMON_REMOVE
comma
op_amp
id|unit-&gt;status
)paren
suffix:semicolon
id|list_move
c_func
(paren
op_amp
id|unit-&gt;list
comma
op_amp
id|port-&gt;unit_remove_lh
)paren
suffix:semicolon
)brace
r_else
(brace
id|unit
op_assign
l_int|NULL
suffix:semicolon
)brace
id|write_unlock_irq
c_func
(paren
op_amp
id|zfcp_data.config_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unit
)paren
(brace
id|retval
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|zfcp_erp_unit_shutdown
c_func
(paren
id|unit
comma
l_int|0
)paren
suffix:semicolon
id|zfcp_erp_wait
c_func
(paren
id|unit-&gt;port-&gt;adapter
)paren
suffix:semicolon
id|zfcp_unit_put
c_func
(paren
id|unit
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|unit-&gt;sysfs_device
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|zfcp_data.config_sema
)paren
suffix:semicolon
r_return
id|retval
ques
c_cond
id|retval
suffix:colon
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|unit_remove
comma
id|S_IWUSR
comma
l_int|NULL
comma
id|zfcp_sysfs_unit_remove_store
)paren
suffix:semicolon
multiline_comment|/**&n; * zfcp_sysfs_port_failed_store - failed state of port&n; * @dev: pointer to belonging device&n; * @buf: pointer to input buffer&n; * @count: number of bytes in buffer&n; *&n; * Store function of the &quot;failed&quot; attribute of a port.&n; * If a &quot;0&quot; gets written to &quot;failed&quot;, error recovery will be&n; * started for the belonging port.&n; */
r_static
id|ssize_t
DECL|function|zfcp_sysfs_port_failed_store
id|zfcp_sysfs_port_failed_store
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
r_struct
id|zfcp_port
op_star
id|port
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_char
op_star
id|endp
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|zfcp_data.config_sema
)paren
suffix:semicolon
id|port
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_test_mask
c_func
(paren
id|ZFCP_STATUS_COMMON_REMOVE
comma
op_amp
id|port-&gt;status
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|endp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|endp
op_plus
l_int|1
)paren
OL
(paren
id|buf
op_plus
id|count
)paren
)paren
op_logical_or
(paren
id|val
op_ne
l_int|0
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* restart error recovery only if adapter is online */
r_if
c_cond
(paren
id|port-&gt;adapter-&gt;ccw_device-&gt;online
op_ne
l_int|1
)paren
(brace
id|retval
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|zfcp_erp_modify_port_status
c_func
(paren
id|port
comma
id|ZFCP_STATUS_COMMON_RUNNING
comma
id|ZFCP_SET
)paren
suffix:semicolon
id|zfcp_erp_port_reopen
c_func
(paren
id|port
comma
id|ZFCP_STATUS_COMMON_ERP_FAILED
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|zfcp_data.config_sema
)paren
suffix:semicolon
r_return
id|retval
ques
c_cond
id|retval
suffix:colon
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; * zfcp_sysfs_port_failed_show - failed state of port&n; * @dev: pointer to belonging device&n; * @buf: pointer to input buffer&n; *&n; * Show function of &quot;failed&quot; attribute of port. Will be&n; * &quot;0&quot; if port is working, otherwise &quot;1&quot;.&n; */
r_static
id|ssize_t
DECL|function|zfcp_sysfs_port_failed_show
id|zfcp_sysfs_port_failed_show
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
id|zfcp_port
op_star
id|port
suffix:semicolon
id|port
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_test_mask
c_func
(paren
id|ZFCP_STATUS_COMMON_ERP_FAILED
comma
op_amp
id|port-&gt;status
)paren
)paren
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;1&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|failed
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|zfcp_sysfs_port_failed_show
comma
id|zfcp_sysfs_port_failed_store
)paren
suffix:semicolon
multiline_comment|/**&n; * zfcp_sysfs_port_in_recovery_show - recovery state of port&n; * @dev: pointer to belonging device&n; * @buf: pointer to input buffer&n; * &n; * Show function of &quot;in_recovery&quot; attribute of port. Will be&n; * &quot;0&quot; if no error recovery is pending for port, otherwise &quot;1&quot;.&n; */
r_static
id|ssize_t
DECL|function|zfcp_sysfs_port_in_recovery_show
id|zfcp_sysfs_port_in_recovery_show
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
id|zfcp_port
op_star
id|port
suffix:semicolon
id|port
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_test_mask
c_func
(paren
id|ZFCP_STATUS_COMMON_ERP_INUSE
comma
op_amp
id|port-&gt;status
)paren
)paren
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;1&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|in_recovery
comma
id|S_IRUGO
comma
id|zfcp_sysfs_port_in_recovery_show
comma
l_int|NULL
)paren
suffix:semicolon
DECL|variable|zfcp_port_common_attrs
r_static
r_struct
id|attribute
op_star
id|zfcp_port_common_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_failed.attr
comma
op_amp
id|dev_attr_in_recovery.attr
comma
op_amp
id|dev_attr_status.attr
comma
op_amp
id|dev_attr_wwnn.attr
comma
op_amp
id|dev_attr_d_id.attr
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|zfcp_port_common_attr_group
r_static
r_struct
id|attribute_group
id|zfcp_port_common_attr_group
op_assign
(brace
dot
id|attrs
op_assign
id|zfcp_port_common_attrs
comma
)brace
suffix:semicolon
DECL|variable|zfcp_port_no_ns_attrs
r_static
r_struct
id|attribute
op_star
id|zfcp_port_no_ns_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_unit_add.attr
comma
op_amp
id|dev_attr_unit_remove.attr
comma
op_amp
id|dev_attr_scsi_id.attr
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|zfcp_port_no_ns_attr_group
r_static
r_struct
id|attribute_group
id|zfcp_port_no_ns_attr_group
op_assign
(brace
dot
id|attrs
op_assign
id|zfcp_port_no_ns_attrs
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * zfcp_sysfs_create_port_files - create sysfs port files&n; * @dev: pointer to belonging device&n; *&n; * Create all attributes of the sysfs representation of a port.&n; */
r_int
DECL|function|zfcp_sysfs_port_create_files
id|zfcp_sysfs_port_create_files
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|flags
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|zfcp_port_common_attr_group
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|ZFCP_STATUS_PORT_NAMESERVER
)paren
op_logical_or
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|retval
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|zfcp_port_no_ns_attr_group
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|sysfs_remove_group
c_func
(paren
op_amp
id|dev-&gt;kobj
comma
op_amp
id|zfcp_port_common_attr_group
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|ZFCP_LOG_AREA
macro_line|#undef ZFCP_LOG_AREA
DECL|macro|ZFCP_LOG_AREA_PREFIX
macro_line|#undef ZFCP_LOG_AREA_PREFIX
eof
