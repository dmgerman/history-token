multiline_comment|/* &n; *  FiberChannel transport specific attributes exported to sysfs.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &lt;scsi/scsi_transport_fc.h&gt;
DECL|macro|FC_PRINTK
mdefine_line|#define FC_PRINTK(x, l, f, a...)&t;printk(l &quot;scsi(%d:%d:%d:%d): &quot; f, (x)-&gt;host-&gt;host_no, (x)-&gt;channel, (x)-&gt;id, (x)-&gt;lun , ##a)
r_static
r_void
id|transport_class_release
c_func
(paren
r_struct
id|class_device
op_star
id|class_dev
)paren
suffix:semicolon
DECL|macro|FC_NUM_ATTRS
mdefine_line|#define FC_NUM_ATTRS &t;3&t;/* increase this if you add attributes */
DECL|macro|FC_OTHER_ATTRS
mdefine_line|#define FC_OTHER_ATTRS &t;0&t;/* increase this if you add &quot;always on&quot;&n;&t;&t;&t;&t; * attributes */
DECL|struct|fc_internal
r_struct
id|fc_internal
(brace
DECL|member|t
r_struct
id|scsi_transport_template
id|t
suffix:semicolon
DECL|member|f
r_struct
id|fc_function_template
op_star
id|f
suffix:semicolon
multiline_comment|/* The actual attributes */
DECL|member|private_attrs
r_struct
id|class_device_attribute
id|private_attrs
(braket
id|FC_NUM_ATTRS
)braket
suffix:semicolon
multiline_comment|/* The array of null terminated pointers to attributes&n;&t; * needed by scsi_sysfs.c */
DECL|member|attrs
r_struct
id|class_device_attribute
op_star
id|attrs
(braket
id|FC_NUM_ATTRS
op_plus
id|FC_OTHER_ATTRS
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_fc_internal
mdefine_line|#define to_fc_internal(tmpl)&t;container_of(tmpl, struct fc_internal, t)
DECL|variable|fc_transport_class
r_struct
r_class
id|fc_transport_class
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;fc_transport&quot;
comma
dot
id|release
op_assign
id|transport_class_release
comma
)brace
suffix:semicolon
DECL|function|fc_transport_init
r_static
id|__init
r_int
id|fc_transport_init
c_func
(paren
r_void
)paren
(brace
r_return
id|class_register
c_func
(paren
op_amp
id|fc_transport_class
)paren
suffix:semicolon
)brace
DECL|function|fc_transport_exit
r_static
r_void
id|__exit
id|fc_transport_exit
c_func
(paren
r_void
)paren
(brace
id|class_unregister
c_func
(paren
op_amp
id|fc_transport_class
)paren
suffix:semicolon
)brace
DECL|function|fc_setup_transport_attrs
r_static
r_int
id|fc_setup_transport_attrs
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
multiline_comment|/* I&squot;m not sure what values are invalid.  We should pick some invalid&n;&t; * values for the defaults */
id|fc_node_name
c_func
(paren
id|sdev
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
id|fc_port_name
c_func
(paren
id|sdev
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
id|fc_port_id
c_func
(paren
id|sdev
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|transport_class_release
r_static
r_void
id|transport_class_release
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
op_assign
id|transport_class_to_sdev
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
DECL|macro|fc_transport_show_function
mdefine_line|#define fc_transport_show_function(field, format_string, cast)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_fc_transport_##field (struct class_device *cdev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev = transport_class_to_sdev(cdev);&t;&bslash;&n;&t;struct fc_transport_attrs *tp;&t;&t;&t;&t;&t;&bslash;&n;&t;struct fc_internal *i = to_fc_internal(sdev-&gt;host-&gt;transportt);&t;&bslash;&n;&t;tp = (struct fc_transport_attrs *)&amp;sdev-&gt;transport_data;&t;&bslash;&n;&t;if (i-&gt;f-&gt;get_##field)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;f-&gt;get_##field(sdev);&t;&t;&t;&t;&bslash;&n;&t;return snprintf(buf, 20, format_string, cast tp-&gt;field);&t;&bslash;&n;}
DECL|macro|fc_transport_store_function
mdefine_line|#define fc_transport_store_function(field, format_string)&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;store_fc_transport_##field(struct class_device *cdev, const char *buf,&t;&bslash;&n;&t;&t;&t;   size_t count)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_device *sdev = transport_class_to_sdev(cdev);&t;&bslash;&n;&t;struct fc_internal *i = to_fc_internal(sdev-&gt;host-&gt;transportt);&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;val = simple_strtoul(buf, NULL, 0);&t;&t;&t;&t;&bslash;&n;&t;i-&gt;f-&gt;set_##field(sdev, val);&t;&t;&t;&t;&t;&bslash;&n;&t;return count;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|fc_transport_rd_attr
mdefine_line|#define fc_transport_rd_attr(field, format_string)&t;&t;&t;&bslash;&n;&t;fc_transport_show_function(field, format_string, )&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO,&t;&t;&t;&t;&bslash;&n;&t;&t;&t; show_fc_transport_##field, NULL)
DECL|macro|fc_transport_rd_attr_cast
mdefine_line|#define fc_transport_rd_attr_cast(field, format_string, cast)&t;&t;&bslash;&n;&t;fc_transport_show_function(field, format_string, (cast))&t;&bslash;&n;static CLASS_DEVICE_ATTR( field, S_IRUGO,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;  show_fc_transport_##field, NULL)
DECL|macro|fc_transport_rw_attr
mdefine_line|#define fc_transport_rw_attr(field, format_string)&t;&t;&t;&bslash;&n;&t;fc_transport_show_function(field, format_string, )&t;&t;&bslash;&n;&t;fc_transport_store_function(field, format_string)&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO | S_IWUSR,&t;&t;&t;&bslash;&n;&t;&t;&t;show_fc_transport_##field,&t;&t;&t;&bslash;&n;&t;&t;&t;store_fc_transport_##field)
multiline_comment|/* the FiberChannel Tranport Attributes: */
id|fc_transport_rd_attr_cast
c_func
(paren
id|node_name
comma
l_string|&quot;0x%llx&bslash;n&quot;
comma
r_int
r_int
r_int
)paren
suffix:semicolon
id|fc_transport_rd_attr_cast
c_func
(paren
id|port_name
comma
l_string|&quot;0x%llx&bslash;n&quot;
comma
r_int
r_int
r_int
)paren
suffix:semicolon
id|fc_transport_rd_attr
c_func
(paren
id|port_id
comma
l_string|&quot;0x%06x&bslash;n&quot;
)paren
suffix:semicolon
DECL|macro|SETUP_ATTRIBUTE_RD
mdefine_line|#define SETUP_ATTRIBUTE_RD(field)&t;&t;&t;&t;&bslash;&n;&t;i-&gt;private_attrs[count] = class_device_attr_##field;&t;&bslash;&n;&t;i-&gt;private_attrs[count].attr.mode = S_IRUGO;&t;&t;&bslash;&n;&t;i-&gt;private_attrs[count].store = NULL;&t;&t;&t;&bslash;&n;&t;i-&gt;attrs[count] = &amp;i-&gt;private_attrs[count];&t;&t;&bslash;&n;&t;if (i-&gt;f-&gt;show_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;count++
DECL|macro|SETUP_ATTRIBUTE_RW
mdefine_line|#define SETUP_ATTRIBUTE_RW(field)&t;&t;&t;&t;&bslash;&n;&t;i-&gt;private_attrs[count] = class_device_attr_##field;&t;&bslash;&n;&t;if (!i-&gt;f-&gt;set_##field) {&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;private_attrs[count].attr.mode = S_IRUGO;&t;&bslash;&n;&t;&t;i-&gt;private_attrs[count].store = NULL;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;i-&gt;attrs[count] = &amp;i-&gt;private_attrs[count];&t;&t;&bslash;&n;&t;if (i-&gt;f-&gt;show_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;count++
r_struct
id|scsi_transport_template
op_star
DECL|function|fc_attach_transport
id|fc_attach_transport
c_func
(paren
r_struct
id|fc_function_template
op_star
id|ft
)paren
(brace
r_struct
id|fc_internal
op_star
id|i
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|fc_internal
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|i
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|i
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fc_internal
)paren
)paren
suffix:semicolon
id|i-&gt;t.attrs
op_assign
op_amp
id|i-&gt;attrs
(braket
l_int|0
)braket
suffix:semicolon
id|i-&gt;t
dot
r_class
op_assign
op_amp
id|fc_transport_class
suffix:semicolon
id|i-&gt;t.setup
op_assign
op_amp
id|fc_setup_transport_attrs
suffix:semicolon
id|i-&gt;t.size
op_assign
r_sizeof
(paren
r_struct
id|fc_transport_attrs
)paren
op_minus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i-&gt;f
op_assign
id|ft
suffix:semicolon
id|SETUP_ATTRIBUTE_RD
c_func
(paren
id|port_id
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE_RD
c_func
(paren
id|port_name
)paren
suffix:semicolon
id|SETUP_ATTRIBUTE_RD
c_func
(paren
id|node_name
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|count
OG
id|FC_NUM_ATTRS
)paren
suffix:semicolon
multiline_comment|/* Setup the always-on attributes here */
id|i-&gt;attrs
(braket
id|count
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
op_amp
id|i-&gt;t
suffix:semicolon
)brace
DECL|variable|fc_attach_transport
id|EXPORT_SYMBOL
c_func
(paren
id|fc_attach_transport
)paren
suffix:semicolon
DECL|function|fc_release_transport
r_void
id|fc_release_transport
c_func
(paren
r_struct
id|scsi_transport_template
op_star
id|t
)paren
(brace
r_struct
id|fc_internal
op_star
id|i
op_assign
id|to_fc_internal
c_func
(paren
id|t
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|variable|fc_release_transport
id|EXPORT_SYMBOL
c_func
(paren
id|fc_release_transport
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Martin Hicks&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;FC Transport Attributes&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|fc_transport_init
id|module_init
c_func
(paren
id|fc_transport_init
)paren
suffix:semicolon
DECL|variable|fc_transport_exit
id|module_exit
c_func
(paren
id|fc_transport_exit
)paren
suffix:semicolon
eof
