multiline_comment|/* &n; * iSCSI transport class definitions&n; *&n; * Copyright (C) IBM Corporation, 2004&n; * Copyright (C) Mike Christie, 2004&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_transport.h&gt;
macro_line|#include &lt;scsi/scsi_transport_iscsi.h&gt;
DECL|macro|ISCSI_SESSION_ATTRS
mdefine_line|#define ISCSI_SESSION_ATTRS 20
DECL|macro|ISCSI_HOST_ATTRS
mdefine_line|#define ISCSI_HOST_ATTRS 2
DECL|struct|iscsi_internal
r_struct
id|iscsi_internal
(brace
DECL|member|t
r_struct
id|scsi_transport_template
id|t
suffix:semicolon
DECL|member|fnt
r_struct
id|iscsi_function_template
op_star
id|fnt
suffix:semicolon
multiline_comment|/*&n;&t; * We do not have any private or other attrs.&n;&t; */
DECL|member|session_attrs
r_struct
id|class_device_attribute
op_star
id|session_attrs
(braket
id|ISCSI_SESSION_ATTRS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|host_attrs
r_struct
id|class_device_attribute
op_star
id|host_attrs
(braket
id|ISCSI_HOST_ATTRS
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_iscsi_internal
mdefine_line|#define to_iscsi_internal(tmpl) container_of(tmpl, struct iscsi_internal, t)
r_static
id|DECLARE_TRANSPORT_CLASS
c_func
(paren
id|iscsi_transport_class
comma
l_string|&quot;iscsi_transport&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|DECLARE_TRANSPORT_CLASS
c_func
(paren
id|iscsi_host_class
comma
l_string|&quot;iscsi_host&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * iSCSI target and session attrs&n; */
DECL|macro|iscsi_session_show_fn
mdefine_line|#define iscsi_session_show_fn(field, format)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_session_##field(struct class_device *cdev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_target *starget = transport_class_to_starget(cdev);&t;&bslash;&n;&t;struct Scsi_Host *shost = dev_to_shost(starget-&gt;dev.parent);&t;&bslash;&n;&t;struct iscsi_internal *i = to_iscsi_internal(shost-&gt;transportt); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;get_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;fnt-&gt;get_##field(starget);&t;&t;&t;&t;&bslash;&n;&t;return snprintf(buf, 20, format&quot;&bslash;n&quot;, iscsi_##field(starget));&t;&bslash;&n;}
DECL|macro|iscsi_session_rd_attr
mdefine_line|#define iscsi_session_rd_attr(field, format)&t;&t;&t;&t;&bslash;&n;&t;iscsi_session_show_fn(field, format)&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_session_##field, NULL);
id|iscsi_session_rd_attr
c_func
(paren
id|tpgt
comma
l_string|&quot;%hu&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|tsih
comma
l_string|&quot;%2x&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|max_recv_data_segment_len
comma
l_string|&quot;%u&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|max_burst_len
comma
l_string|&quot;%u&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|first_burst_len
comma
l_string|&quot;%u&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|def_time2wait
comma
l_string|&quot;%hu&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|def_time2retain
comma
l_string|&quot;%hu&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|max_outstanding_r2t
comma
l_string|&quot;%hu&quot;
)paren
suffix:semicolon
id|iscsi_session_rd_attr
c_func
(paren
id|erl
comma
l_string|&quot;%d&quot;
)paren
suffix:semicolon
DECL|macro|iscsi_session_show_bool_fn
mdefine_line|#define iscsi_session_show_bool_fn(field)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_session_bool_##field(struct class_device *cdev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_target *starget = transport_class_to_starget(cdev);&t;&bslash;&n;&t;struct Scsi_Host *shost = dev_to_shost(starget-&gt;dev.parent);&t;&bslash;&n;&t;struct iscsi_internal *i = to_iscsi_internal(shost-&gt;transportt); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;get_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;fnt-&gt;get_##field(starget);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (iscsi_##field(starget))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return sprintf(buf, &quot;Yes&bslash;n&quot;);&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;No&bslash;n&quot;);&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|iscsi_session_rd_bool_attr
mdefine_line|#define iscsi_session_rd_bool_attr(field)&t;&t;&t;&t;&bslash;&n;&t;iscsi_session_show_bool_fn(field)&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_session_bool_##field, NULL);
DECL|variable|initial_r2t
id|iscsi_session_rd_bool_attr
c_func
(paren
id|initial_r2t
)paren
suffix:semicolon
DECL|variable|immediate_data
id|iscsi_session_rd_bool_attr
c_func
(paren
id|immediate_data
)paren
suffix:semicolon
DECL|variable|data_pdu_in_order
id|iscsi_session_rd_bool_attr
c_func
(paren
id|data_pdu_in_order
)paren
suffix:semicolon
DECL|variable|data_sequence_in_order
id|iscsi_session_rd_bool_attr
c_func
(paren
id|data_sequence_in_order
)paren
suffix:semicolon
DECL|macro|iscsi_session_show_digest_fn
mdefine_line|#define iscsi_session_show_digest_fn(field)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_##field(struct class_device *cdev, char *buf)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_target *starget = transport_class_to_starget(cdev);&t;&bslash;&n;&t;struct Scsi_Host *shost = dev_to_shost(starget-&gt;dev.parent);&t;&bslash;&n;&t;struct iscsi_internal *i = to_iscsi_internal(shost-&gt;transportt); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;get_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;fnt-&gt;get_##field(starget);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (iscsi_##field(starget))&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return sprintf(buf, &quot;CRC32C&bslash;n&quot;);&t;&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;None&bslash;n&quot;);&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|iscsi_session_rd_digest_attr
mdefine_line|#define iscsi_session_rd_digest_attr(field)&t;&t;&t;&t;&bslash;&n;&t;iscsi_session_show_digest_fn(field)&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_##field, NULL);
DECL|variable|header_digest
id|iscsi_session_rd_digest_attr
c_func
(paren
id|header_digest
)paren
suffix:semicolon
DECL|variable|data_digest
id|iscsi_session_rd_digest_attr
c_func
(paren
id|data_digest
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_port
id|show_port
c_func
(paren
r_struct
id|class_device
op_star
id|cdev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|scsi_target
op_star
id|starget
op_assign
id|transport_class_to_starget
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|starget-&gt;dev.parent
)paren
suffix:semicolon
r_struct
id|iscsi_internal
op_star
id|i
op_assign
id|to_iscsi_internal
c_func
(paren
id|shost-&gt;transportt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;fnt-&gt;get_port
)paren
id|i-&gt;fnt
op_member_access_from_pointer
id|get_port
c_func
(paren
id|starget
)paren
suffix:semicolon
r_return
id|snprintf
c_func
(paren
id|buf
comma
l_int|20
comma
l_string|&quot;%hu&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|iscsi_port
c_func
(paren
id|starget
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|port
comma
id|S_IRUGO
comma
id|show_port
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_ip_address
id|show_ip_address
c_func
(paren
r_struct
id|class_device
op_star
id|cdev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|scsi_target
op_star
id|starget
op_assign
id|transport_class_to_starget
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|starget-&gt;dev.parent
)paren
suffix:semicolon
r_struct
id|iscsi_internal
op_star
id|i
op_assign
id|to_iscsi_internal
c_func
(paren
id|shost-&gt;transportt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;fnt-&gt;get_ip_address
)paren
id|i-&gt;fnt
op_member_access_from_pointer
id|get_ip_address
c_func
(paren
id|starget
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iscsi_addr_type
c_func
(paren
id|starget
)paren
op_eq
id|AF_INET
)paren
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iscsi_sin_addr
c_func
(paren
id|starget
)paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|iscsi_addr_type
c_func
(paren
id|starget
)paren
op_eq
id|AF_INET6
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|NIP6
c_func
(paren
id|iscsi_sin6_addr
c_func
(paren
id|starget
)paren
)paren
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|ip_address
comma
id|S_IRUGO
comma
id|show_ip_address
comma
l_int|NULL
)paren
suffix:semicolon
r_static
id|ssize_t
DECL|function|show_isid
id|show_isid
c_func
(paren
r_struct
id|class_device
op_star
id|cdev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|scsi_target
op_star
id|starget
op_assign
id|transport_class_to_starget
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|starget-&gt;dev.parent
)paren
suffix:semicolon
r_struct
id|iscsi_internal
op_star
id|i
op_assign
id|to_iscsi_internal
c_func
(paren
id|shost-&gt;transportt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;fnt-&gt;get_isid
)paren
id|i-&gt;fnt
op_member_access_from_pointer
id|get_isid
c_func
(paren
id|starget
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%02x%02x%02x%02x%02x%02x&bslash;n&quot;
comma
id|iscsi_isid
c_func
(paren
id|starget
)paren
(braket
l_int|0
)braket
comma
id|iscsi_isid
c_func
(paren
id|starget
)paren
(braket
l_int|1
)braket
comma
id|iscsi_isid
c_func
(paren
id|starget
)paren
(braket
l_int|2
)braket
comma
id|iscsi_isid
c_func
(paren
id|starget
)paren
(braket
l_int|3
)braket
comma
id|iscsi_isid
c_func
(paren
id|starget
)paren
(braket
l_int|4
)braket
comma
id|iscsi_isid
c_func
(paren
id|starget
)paren
(braket
l_int|5
)braket
)paren
suffix:semicolon
)brace
r_static
id|CLASS_DEVICE_ATTR
c_func
(paren
id|isid
comma
id|S_IRUGO
comma
id|show_isid
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n; * This is used for iSCSI names. Normally, we follow&n; * the transport class convention of having the lld&n; * set the field, but in these cases the value is&n; * too large.&n; */
DECL|macro|iscsi_session_show_str_fn
mdefine_line|#define iscsi_session_show_str_fn(field)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_session_str_##field(struct class_device *cdev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ssize_t ret = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct scsi_target *starget = transport_class_to_starget(cdev);&t;&bslash;&n;&t;struct Scsi_Host *shost = dev_to_shost(starget-&gt;dev.parent);&t;&bslash;&n;&t;struct iscsi_internal *i = to_iscsi_internal(shost-&gt;transportt); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;get_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = i-&gt;fnt-&gt;get_##field(starget, buf, PAGE_SIZE);&t;&bslash;&n;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|iscsi_session_rd_str_attr
mdefine_line|#define iscsi_session_rd_str_attr(field)&t;&t;&t;&t;&bslash;&n;&t;iscsi_session_show_str_fn(field)&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_session_str_##field, NULL);
DECL|variable|target_name
id|iscsi_session_rd_str_attr
c_func
(paren
id|target_name
)paren
suffix:semicolon
DECL|variable|target_alias
id|iscsi_session_rd_str_attr
c_func
(paren
id|target_alias
)paren
suffix:semicolon
multiline_comment|/*&n; * iSCSI host attrs&n; */
multiline_comment|/*&n; * Again, this is used for iSCSI names. Normally, we follow&n; * the transport class convention of having the lld set&n; * the field, but in these cases the value is too large.&n; */
DECL|macro|iscsi_host_show_str_fn
mdefine_line|#define iscsi_host_show_str_fn(field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static ssize_t&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;show_host_str_##field(struct class_device *cdev, char *buf)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int ret = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct Scsi_Host *shost = transport_class_to_shost(cdev);&t;&bslash;&n;&t;struct iscsi_internal *i = to_iscsi_internal(shost-&gt;transportt); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;get_##field)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ret = i-&gt;fnt-&gt;get_##field(shost, buf, PAGE_SIZE);&t;&bslash;&n;&t;return ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|iscsi_host_rd_str_attr
mdefine_line|#define iscsi_host_rd_str_attr(field)&t;&t;&t;&t;&t;&bslash;&n;&t;iscsi_host_show_str_fn(field)&t;&t;&t;&t;&t;&bslash;&n;static CLASS_DEVICE_ATTR(field, S_IRUGO, show_host_str_##field, NULL);
DECL|variable|initiator_name
id|iscsi_host_rd_str_attr
c_func
(paren
id|initiator_name
)paren
suffix:semicolon
DECL|variable|initiator_alias
id|iscsi_host_rd_str_attr
c_func
(paren
id|initiator_alias
)paren
suffix:semicolon
DECL|macro|SETUP_SESSION_RD_ATTR
mdefine_line|#define SETUP_SESSION_RD_ATTR(field)&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;show_##field) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;session_attrs[count] = &amp;class_device_attr_##field;&t;&bslash;&n;&t;&t;count++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|SETUP_HOST_RD_ATTR
mdefine_line|#define SETUP_HOST_RD_ATTR(field)&t;&t;&t;&t;&t;&bslash;&n;&t;if (i-&gt;fnt-&gt;show_##field) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i-&gt;host_attrs[count] = &amp;class_device_attr_##field;&t;&bslash;&n;&t;&t;count++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|function|iscsi_host_match
r_static
r_int
id|iscsi_host_match
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
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
id|iscsi_internal
op_star
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_is_host_device
c_func
(paren
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;transportt
op_logical_or
id|shost-&gt;transportt-&gt;host_attrs
dot
r_class
op_ne
op_amp
id|iscsi_host_class
dot
r_class
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|to_iscsi_internal
c_func
(paren
id|shost-&gt;transportt
)paren
suffix:semicolon
r_return
op_amp
id|i-&gt;t.host_attrs
op_eq
id|cont
suffix:semicolon
)brace
DECL|function|iscsi_target_match
r_static
r_int
id|iscsi_target_match
c_func
(paren
r_struct
id|attribute_container
op_star
id|cont
comma
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
id|iscsi_internal
op_star
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_is_target_device
c_func
(paren
id|dev
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|shost
op_assign
id|dev_to_shost
c_func
(paren
id|dev-&gt;parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost-&gt;transportt
op_logical_or
id|shost-&gt;transportt-&gt;host_attrs
dot
r_class
op_ne
op_amp
id|iscsi_host_class
dot
r_class
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|to_iscsi_internal
c_func
(paren
id|shost-&gt;transportt
)paren
suffix:semicolon
r_return
op_amp
id|i-&gt;t.target_attrs
op_eq
id|cont
suffix:semicolon
)brace
r_struct
id|scsi_transport_template
op_star
DECL|function|iscsi_attach_transport
id|iscsi_attach_transport
c_func
(paren
r_struct
id|iscsi_function_template
op_star
id|fnt
)paren
(brace
r_struct
id|iscsi_internal
op_star
id|i
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iscsi_internal
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
id|iscsi_internal
)paren
)paren
suffix:semicolon
id|i-&gt;fnt
op_assign
id|fnt
suffix:semicolon
id|i-&gt;t.target_attrs.attrs
op_assign
op_amp
id|i-&gt;session_attrs
(braket
l_int|0
)braket
suffix:semicolon
id|i-&gt;t.target_attrs
dot
r_class
op_assign
op_amp
id|iscsi_transport_class
dot
r_class
suffix:semicolon
id|i-&gt;t.target_attrs.match
op_assign
id|iscsi_target_match
suffix:semicolon
id|attribute_container_register
c_func
(paren
op_amp
id|i-&gt;t.target_attrs
)paren
suffix:semicolon
id|i-&gt;t.target_size
op_assign
r_sizeof
(paren
r_struct
id|iscsi_class_session
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|tsih
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|isid
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|header_digest
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|data_digest
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|target_name
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|target_alias
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|port
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|tpgt
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|ip_address
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|initial_r2t
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|immediate_data
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|max_recv_data_segment_len
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|max_burst_len
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|first_burst_len
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|def_time2wait
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|def_time2retain
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|max_outstanding_r2t
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|data_pdu_in_order
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|data_sequence_in_order
)paren
suffix:semicolon
id|SETUP_SESSION_RD_ATTR
c_func
(paren
id|erl
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|count
OG
id|ISCSI_SESSION_ATTRS
)paren
suffix:semicolon
id|i-&gt;session_attrs
(braket
id|count
)braket
op_assign
l_int|NULL
suffix:semicolon
id|i-&gt;t.host_attrs.attrs
op_assign
op_amp
id|i-&gt;host_attrs
(braket
l_int|0
)braket
suffix:semicolon
id|i-&gt;t.host_attrs
dot
r_class
op_assign
op_amp
id|iscsi_host_class
dot
r_class
suffix:semicolon
id|i-&gt;t.host_attrs.match
op_assign
id|iscsi_host_match
suffix:semicolon
id|attribute_container_register
c_func
(paren
op_amp
id|i-&gt;t.host_attrs
)paren
suffix:semicolon
id|i-&gt;t.host_size
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|SETUP_HOST_RD_ATTR
c_func
(paren
id|initiator_name
)paren
suffix:semicolon
id|SETUP_HOST_RD_ATTR
c_func
(paren
id|initiator_alias
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|count
OG
id|ISCSI_HOST_ATTRS
)paren
suffix:semicolon
id|i-&gt;host_attrs
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
DECL|variable|iscsi_attach_transport
id|EXPORT_SYMBOL
c_func
(paren
id|iscsi_attach_transport
)paren
suffix:semicolon
DECL|function|iscsi_release_transport
r_void
id|iscsi_release_transport
c_func
(paren
r_struct
id|scsi_transport_template
op_star
id|t
)paren
(brace
r_struct
id|iscsi_internal
op_star
id|i
op_assign
id|to_iscsi_internal
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
DECL|variable|iscsi_release_transport
id|EXPORT_SYMBOL
c_func
(paren
id|iscsi_release_transport
)paren
suffix:semicolon
DECL|function|iscsi_transport_init
r_static
id|__init
r_int
id|iscsi_transport_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|transport_class_register
c_func
(paren
op_amp
id|iscsi_transport_class
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_return
id|transport_class_register
c_func
(paren
op_amp
id|iscsi_host_class
)paren
suffix:semicolon
)brace
DECL|function|iscsi_transport_exit
r_static
r_void
id|__exit
id|iscsi_transport_exit
c_func
(paren
r_void
)paren
(brace
id|transport_class_unregister
c_func
(paren
op_amp
id|iscsi_host_class
)paren
suffix:semicolon
id|transport_class_unregister
c_func
(paren
op_amp
id|iscsi_transport_class
)paren
suffix:semicolon
)brace
DECL|variable|iscsi_transport_init
id|module_init
c_func
(paren
id|iscsi_transport_init
)paren
suffix:semicolon
DECL|variable|iscsi_transport_exit
id|module_exit
c_func
(paren
id|iscsi_transport_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mike Christie&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;iSCSI Transport Attributes&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
