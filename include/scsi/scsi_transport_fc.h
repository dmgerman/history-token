multiline_comment|/* &n; *  FiberChannel transport specific attributes exported to sysfs.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *  ========&n; *&n; *  Copyright (C) 2004-2005   James Smart, Emulex Corporation&n; *    Rewrite for host, target, device, and remote port attributes,&n; *    statistics, and service functions...&n; *&n; */
macro_line|#ifndef SCSI_TRANSPORT_FC_H
DECL|macro|SCSI_TRANSPORT_FC_H
mdefine_line|#define SCSI_TRANSPORT_FC_H
macro_line|#include &lt;linux/config.h&gt;
r_struct
id|scsi_transport_template
suffix:semicolon
multiline_comment|/*&n; * FC Port definitions - Following FC HBAAPI guidelines&n; *&n; * Note: Not all binary values for the different fields match HBAAPI.&n; *  Instead, we use densely packed ordinal values or enums.&n; *  We get away with this as we never present the actual binary values&n; *  externally. For sysfs, we always present the string that describes&n; *  the value. Thus, an admin doesn&squot;t need a magic HBAAPI decoder ring&n; *  to understand the values. The HBAAPI user-space library is free to&n; *  convert the strings into the HBAAPI-specified binary values.&n; *&n; * Note: Not all HBAAPI-defined values are contained in the definitions&n; *  below. Those not appropriate to an fc_host (e.g. FCP initiator) have&n; *  been removed.&n; */
multiline_comment|/*&n; * fc_port_type: If you alter this, you also need to alter scsi_transport_fc.c&n; * (for the ascii descriptions).&n; */
DECL|enum|fc_port_type
r_enum
id|fc_port_type
(brace
DECL|enumerator|FC_PORTTYPE_UNKNOWN
id|FC_PORTTYPE_UNKNOWN
comma
DECL|enumerator|FC_PORTTYPE_OTHER
id|FC_PORTTYPE_OTHER
comma
DECL|enumerator|FC_PORTTYPE_NOTPRESENT
id|FC_PORTTYPE_NOTPRESENT
comma
DECL|enumerator|FC_PORTTYPE_NPORT
id|FC_PORTTYPE_NPORT
comma
multiline_comment|/* Attached to FPort */
DECL|enumerator|FC_PORTTYPE_NLPORT
id|FC_PORTTYPE_NLPORT
comma
multiline_comment|/* (Public) Loop w/ FLPort */
DECL|enumerator|FC_PORTTYPE_LPORT
id|FC_PORTTYPE_LPORT
comma
multiline_comment|/* (Private) Loop w/o FLPort */
DECL|enumerator|FC_PORTTYPE_PTP
id|FC_PORTTYPE_PTP
comma
multiline_comment|/* Point to Point w/ another NPort */
)brace
suffix:semicolon
multiline_comment|/*&n; * fc_port_state: If you alter this, you also need to alter scsi_transport_fc.c&n; * (for the ascii descriptions).&n; */
DECL|enum|fc_port_state
r_enum
id|fc_port_state
(brace
DECL|enumerator|FC_PORTSTATE_UNKNOWN
id|FC_PORTSTATE_UNKNOWN
comma
DECL|enumerator|FC_PORTSTATE_NOTPRESENT
id|FC_PORTSTATE_NOTPRESENT
comma
DECL|enumerator|FC_PORTSTATE_ONLINE
id|FC_PORTSTATE_ONLINE
comma
DECL|enumerator|FC_PORTSTATE_OFFLINE
id|FC_PORTSTATE_OFFLINE
comma
multiline_comment|/* User has taken Port Offline */
DECL|enumerator|FC_PORTSTATE_BLOCKED
id|FC_PORTSTATE_BLOCKED
comma
DECL|enumerator|FC_PORTSTATE_BYPASSED
id|FC_PORTSTATE_BYPASSED
comma
DECL|enumerator|FC_PORTSTATE_DIAGNOSTICS
id|FC_PORTSTATE_DIAGNOSTICS
comma
DECL|enumerator|FC_PORTSTATE_LINKDOWN
id|FC_PORTSTATE_LINKDOWN
comma
DECL|enumerator|FC_PORTSTATE_ERROR
id|FC_PORTSTATE_ERROR
comma
DECL|enumerator|FC_PORTSTATE_LOOPBACK
id|FC_PORTSTATE_LOOPBACK
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * FC Classes of Service&n; * Note: values are not enumerated, as they can be &quot;or&squot;d&quot; together&n; * for reporting (e.g. report supported_classes). If you alter this list,&n; * you also need to alter scsi_transport_fc.c (for the ascii descriptions).&n; */
DECL|macro|FC_COS_UNSPECIFIED
mdefine_line|#define FC_COS_UNSPECIFIED&t;&t;0
DECL|macro|FC_COS_CLASS1
mdefine_line|#define FC_COS_CLASS1&t;&t;&t;2
DECL|macro|FC_COS_CLASS2
mdefine_line|#define FC_COS_CLASS2&t;&t;&t;4
DECL|macro|FC_COS_CLASS3
mdefine_line|#define FC_COS_CLASS3&t;&t;&t;8
DECL|macro|FC_COS_CLASS4
mdefine_line|#define FC_COS_CLASS4&t;&t;&t;0x10
DECL|macro|FC_COS_CLASS6
mdefine_line|#define FC_COS_CLASS6&t;&t;&t;0x40
multiline_comment|/* &n; * FC Port Speeds&n; * Note: values are not enumerated, as they can be &quot;or&squot;d&quot; together&n; * for reporting (e.g. report supported_speeds). If you alter this list,&n; * you also need to alter scsi_transport_fc.c (for the ascii descriptions).&n; */
DECL|macro|FC_PORTSPEED_UNKNOWN
mdefine_line|#define FC_PORTSPEED_UNKNOWN&t;&t;0 /* Unknown - transceiver&n;&t;&t;&t;&t;&t;     incapable of reporting */
DECL|macro|FC_PORTSPEED_1GBIT
mdefine_line|#define FC_PORTSPEED_1GBIT&t;&t;1
DECL|macro|FC_PORTSPEED_2GBIT
mdefine_line|#define FC_PORTSPEED_2GBIT&t;&t;2
DECL|macro|FC_PORTSPEED_10GBIT
mdefine_line|#define FC_PORTSPEED_10GBIT&t;&t;4
DECL|macro|FC_PORTSPEED_4GBIT
mdefine_line|#define FC_PORTSPEED_4GBIT&t;&t;8
DECL|macro|FC_PORTSPEED_NOT_NEGOTIATED
mdefine_line|#define FC_PORTSPEED_NOT_NEGOTIATED&t;(1 &lt;&lt; 15) /* Speed not established */
multiline_comment|/*&n; * fc_tgtid_binding_type: If you alter this, you also need to alter&n; * scsi_transport_fc.c (for the ascii descriptions).&n; */
DECL|enum|fc_tgtid_binding_type
r_enum
id|fc_tgtid_binding_type
(brace
DECL|enumerator|FC_TGTID_BIND_NONE
id|FC_TGTID_BIND_NONE
comma
DECL|enumerator|FC_TGTID_BIND_BY_WWPN
id|FC_TGTID_BIND_BY_WWPN
comma
DECL|enumerator|FC_TGTID_BIND_BY_WWNN
id|FC_TGTID_BIND_BY_WWNN
comma
DECL|enumerator|FC_TGTID_BIND_BY_ID
id|FC_TGTID_BIND_BY_ID
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * FC Remote Port Roles&n; * Note: values are not enumerated, as they can be &quot;or&squot;d&quot; together&n; * for reporting (e.g. report roles). If you alter this list,&n; * you also need to alter scsi_transport_fc.c (for the ascii descriptions).&n; */
DECL|macro|FC_RPORT_ROLE_UNKNOWN
mdefine_line|#define FC_RPORT_ROLE_UNKNOWN&t;&t;&t;0x00
DECL|macro|FC_RPORT_ROLE_FCP_TARGET
mdefine_line|#define FC_RPORT_ROLE_FCP_TARGET&t;&t;0x01
DECL|macro|FC_RPORT_ROLE_FCP_INITIATOR
mdefine_line|#define FC_RPORT_ROLE_FCP_INITIATOR&t;&t;0x02
DECL|macro|FC_RPORT_ROLE_IP_PORT
mdefine_line|#define FC_RPORT_ROLE_IP_PORT&t;&t;&t;0x04
multiline_comment|/*&n; * fc_rport_identifiers: This set of data contains all elements&n; * to uniquely identify a remote FC port. The driver uses this data&n; * to report the existence of a remote FC port in the topology. Internally,&n; * the transport uses this data for attributes and to manage consistent&n; * target id bindings.&n; */
DECL|struct|fc_rport_identifiers
r_struct
id|fc_rport_identifiers
(brace
DECL|member|node_name
id|u64
id|node_name
suffix:semicolon
DECL|member|port_name
id|u64
id|port_name
suffix:semicolon
DECL|member|port_id
id|u32
id|port_id
suffix:semicolon
DECL|member|roles
id|u32
id|roles
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Macro for use in defining Remote Port attributes */
DECL|macro|FC_RPORT_ATTR
mdefine_line|#define FC_RPORT_ATTR(_name,_mode,_show,_store)&t;&t;&t;&t;&bslash;&n;struct class_device_attribute class_device_attr_rport_##_name = &t;&bslash;&n;&t;__ATTR(_name,_mode,_show,_store)
multiline_comment|/*&n; * FC Remote Port Attributes&n; *&n; * This structure exists for each remote FC port that a LLDD notifies&n; * the subsystem of.  A remote FC port may or may not be a SCSI Target,&n; * also be a SCSI initiator, IP endpoint, etc. As such, the remote&n; * port is considered a separate entity, independent of &quot;role&quot; (such&n; * as scsi target).&n; *&n; * --&n; *&n; * Attributes are based on HBAAPI V2.0 definitions. Only those&n; * attributes that are determinable by the local port (aka Host)&n; * are contained.&n; *&n; * Fixed attributes are not expected to change. The driver is&n; * expected to set these values after successfully calling&n; * fc_remote_port_add(). The transport fully manages all get functions&n; * w/o driver interaction.&n; *&n; * Dynamic attributes are expected to change. The driver participates&n; * in all get/set operations via functions provided by the driver.&n; *&n; * Private attributes are transport-managed values. They are fully&n; * managed by the transport w/o driver interaction.&n; */
DECL|struct|fc_rport
r_struct
id|fc_rport
(brace
multiline_comment|/* aka fc_starget_attrs */
multiline_comment|/* Fixed Attributes */
DECL|member|maxframe_size
id|u32
id|maxframe_size
suffix:semicolon
DECL|member|supported_classes
id|u32
id|supported_classes
suffix:semicolon
multiline_comment|/* Dynamic Attributes */
DECL|member|dev_loss_tmo
id|u32
id|dev_loss_tmo
suffix:semicolon
multiline_comment|/* Remote Port loss timeout in seconds. */
multiline_comment|/* Private (Transport-managed) Attributes */
DECL|member|node_name
id|u64
id|node_name
suffix:semicolon
DECL|member|port_name
id|u64
id|port_name
suffix:semicolon
DECL|member|port_id
id|u32
id|port_id
suffix:semicolon
DECL|member|roles
id|u32
id|roles
suffix:semicolon
DECL|member|port_state
r_enum
id|fc_port_state
id|port_state
suffix:semicolon
multiline_comment|/* Will only be ONLINE or UNKNOWN */
DECL|member|scsi_target_id
id|u32
id|scsi_target_id
suffix:semicolon
multiline_comment|/* exported data */
DECL|member|dd_data
r_void
op_star
id|dd_data
suffix:semicolon
multiline_comment|/* Used for driver-specific storage */
multiline_comment|/* internal data */
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|number
id|u32
id|number
suffix:semicolon
DECL|member|peers
r_struct
id|list_head
id|peers
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|dev_loss_work
r_struct
id|work_struct
id|dev_loss_work
suffix:semicolon
DECL|member|scan_work
r_struct
id|work_struct
id|scan_work
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
)paren
suffix:semicolon
DECL|macro|dev_to_rport
mdefine_line|#define&t;dev_to_rport(d)&t;&t;&t;&t;&bslash;&n;&t;container_of(d, struct fc_rport, dev)
DECL|macro|transport_class_to_rport
mdefine_line|#define transport_class_to_rport(classdev)&t;&bslash;&n;&t;dev_to_rport(classdev-&gt;dev)
DECL|macro|rport_to_shost
mdefine_line|#define rport_to_shost(r)&t;&t;&t;&bslash;&n;&t;dev_to_shost(r-&gt;dev.parent)
DECL|macro|FC_SCSI_SCAN_DELAY
mdefine_line|#define FC_SCSI_SCAN_DELAY&t;&t;(1 * HZ)&t;/* 1 second delay */
multiline_comment|/*&n; * FC SCSI Target Attributes&n; *&n; * The SCSI Target is considered an extention of a remote port (as&n; * a remote port can be more than a SCSI Target). Within the scsi&n; * subsystem, we leave the Target as a separate entity. Doing so&n; * provides backward compatibility with prior FC transport api&squot;s,&n; * and lets remote ports be handled entirely within the FC transport&n; * and independently from the scsi subsystem. The drawback is that&n; * some data will be duplicated.&n; */
DECL|struct|fc_starget_attrs
r_struct
id|fc_starget_attrs
(brace
multiline_comment|/* aka fc_target_attrs */
multiline_comment|/* Dynamic Attributes */
DECL|member|node_name
id|u64
id|node_name
suffix:semicolon
DECL|member|port_name
id|u64
id|port_name
suffix:semicolon
DECL|member|port_id
id|u32
id|port_id
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|fc_starget_node_name
mdefine_line|#define fc_starget_node_name(x) &bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;node_name)
DECL|macro|fc_starget_port_name
mdefine_line|#define fc_starget_port_name(x)&t;&bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;port_name)
DECL|macro|fc_starget_port_id
mdefine_line|#define fc_starget_port_id(x) &bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;port_id)
DECL|macro|starget_to_rport
mdefine_line|#define starget_to_rport(s)&t;&t;&t;&bslash;&n;&t;scsi_is_fc_rport(s-&gt;dev.parent) ? dev_to_rport(s-&gt;dev.parent) : NULL
multiline_comment|/*&n; * FC Local Port (Host) Statistics&n; */
multiline_comment|/* FC Statistics - Following FC HBAAPI v2.0 guidelines */
DECL|struct|fc_host_statistics
r_struct
id|fc_host_statistics
(brace
multiline_comment|/* port statistics */
DECL|member|seconds_since_last_reset
id|u64
id|seconds_since_last_reset
suffix:semicolon
DECL|member|tx_frames
id|u64
id|tx_frames
suffix:semicolon
DECL|member|tx_words
id|u64
id|tx_words
suffix:semicolon
DECL|member|rx_frames
id|u64
id|rx_frames
suffix:semicolon
DECL|member|rx_words
id|u64
id|rx_words
suffix:semicolon
DECL|member|lip_count
id|u64
id|lip_count
suffix:semicolon
DECL|member|nos_count
id|u64
id|nos_count
suffix:semicolon
DECL|member|error_frames
id|u64
id|error_frames
suffix:semicolon
DECL|member|dumped_frames
id|u64
id|dumped_frames
suffix:semicolon
DECL|member|link_failure_count
id|u64
id|link_failure_count
suffix:semicolon
DECL|member|loss_of_sync_count
id|u64
id|loss_of_sync_count
suffix:semicolon
DECL|member|loss_of_signal_count
id|u64
id|loss_of_signal_count
suffix:semicolon
DECL|member|prim_seq_protocol_err_count
id|u64
id|prim_seq_protocol_err_count
suffix:semicolon
DECL|member|invalid_tx_word_count
id|u64
id|invalid_tx_word_count
suffix:semicolon
DECL|member|invalid_crc_count
id|u64
id|invalid_crc_count
suffix:semicolon
multiline_comment|/* fc4 statistics  (only FCP supported currently) */
DECL|member|fcp_input_requests
id|u64
id|fcp_input_requests
suffix:semicolon
DECL|member|fcp_output_requests
id|u64
id|fcp_output_requests
suffix:semicolon
DECL|member|fcp_control_requests
id|u64
id|fcp_control_requests
suffix:semicolon
DECL|member|fcp_input_megabytes
id|u64
id|fcp_input_megabytes
suffix:semicolon
DECL|member|fcp_output_megabytes
id|u64
id|fcp_output_megabytes
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * FC Local Port (Host) Attributes&n; *&n; * Attributes are based on HBAAPI V2.0 definitions.&n; * Note: OSDeviceName is determined by user-space library&n; *&n; * Fixed attributes are not expected to change. The driver is&n; * expected to set these values after successfully calling scsi_add_host().&n; * The transport fully manages all get functions w/o driver interaction.&n; *&n; * Dynamic attributes are expected to change. The driver participates&n; * in all get/set operations via functions provided by the driver.&n; *&n; * Private attributes are transport-managed values. They are fully&n; * managed by the transport w/o driver interaction.&n; */
DECL|macro|FC_FC4_LIST_SIZE
mdefine_line|#define FC_FC4_LIST_SIZE&t;&t;32
DECL|macro|FC_SYMBOLIC_NAME_SIZE
mdefine_line|#define FC_SYMBOLIC_NAME_SIZE&t;&t;256
DECL|macro|FC_VERSION_STRING_SIZE
mdefine_line|#define FC_VERSION_STRING_SIZE&t;&t;64
DECL|macro|FC_SERIAL_NUMBER_SIZE
mdefine_line|#define FC_SERIAL_NUMBER_SIZE&t;&t;80
DECL|struct|fc_host_attrs
r_struct
id|fc_host_attrs
(brace
multiline_comment|/* Fixed Attributes */
DECL|member|node_name
id|u64
id|node_name
suffix:semicolon
DECL|member|port_name
id|u64
id|port_name
suffix:semicolon
DECL|member|supported_classes
id|u32
id|supported_classes
suffix:semicolon
DECL|member|supported_fc4s
id|u8
id|supported_fc4s
(braket
id|FC_FC4_LIST_SIZE
)braket
suffix:semicolon
DECL|member|symbolic_name
r_char
id|symbolic_name
(braket
id|FC_SYMBOLIC_NAME_SIZE
)braket
suffix:semicolon
DECL|member|supported_speeds
id|u32
id|supported_speeds
suffix:semicolon
DECL|member|maxframe_size
id|u32
id|maxframe_size
suffix:semicolon
DECL|member|serial_number
r_char
id|serial_number
(braket
id|FC_SERIAL_NUMBER_SIZE
)braket
suffix:semicolon
multiline_comment|/* Dynamic Attributes */
DECL|member|port_id
id|u32
id|port_id
suffix:semicolon
DECL|member|port_type
r_enum
id|fc_port_type
id|port_type
suffix:semicolon
DECL|member|port_state
r_enum
id|fc_port_state
id|port_state
suffix:semicolon
DECL|member|active_fc4s
id|u8
id|active_fc4s
(braket
id|FC_FC4_LIST_SIZE
)braket
suffix:semicolon
DECL|member|speed
id|u32
id|speed
suffix:semicolon
DECL|member|fabric_name
id|u64
id|fabric_name
suffix:semicolon
multiline_comment|/* Private (Transport-managed) Attributes */
DECL|member|tgtid_bind_type
r_enum
id|fc_tgtid_binding_type
id|tgtid_bind_type
suffix:semicolon
multiline_comment|/* internal data */
DECL|member|rports
r_struct
id|list_head
id|rports
suffix:semicolon
DECL|member|rport_bindings
r_struct
id|list_head
id|rport_bindings
suffix:semicolon
DECL|member|next_rport_number
id|u32
id|next_rport_number
suffix:semicolon
DECL|member|next_target_id
id|u32
id|next_target_id
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|fc_host_node_name
mdefine_line|#define fc_host_node_name(x) &bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;node_name)
DECL|macro|fc_host_port_name
mdefine_line|#define fc_host_port_name(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;port_name)
DECL|macro|fc_host_supported_classes
mdefine_line|#define fc_host_supported_classes(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;supported_classes)
DECL|macro|fc_host_supported_fc4s
mdefine_line|#define fc_host_supported_fc4s(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;supported_fc4s)
DECL|macro|fc_host_symbolic_name
mdefine_line|#define fc_host_symbolic_name(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;symbolic_name)
DECL|macro|fc_host_supported_speeds
mdefine_line|#define fc_host_supported_speeds(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;supported_speeds)
DECL|macro|fc_host_maxframe_size
mdefine_line|#define fc_host_maxframe_size(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;maxframe_size)
DECL|macro|fc_host_serial_number
mdefine_line|#define fc_host_serial_number(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;serial_number)
DECL|macro|fc_host_port_id
mdefine_line|#define fc_host_port_id(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;port_id)
DECL|macro|fc_host_port_type
mdefine_line|#define fc_host_port_type(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;port_type)
DECL|macro|fc_host_port_state
mdefine_line|#define fc_host_port_state(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;port_state)
DECL|macro|fc_host_active_fc4s
mdefine_line|#define fc_host_active_fc4s(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;active_fc4s)
DECL|macro|fc_host_speed
mdefine_line|#define fc_host_speed(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;speed)
DECL|macro|fc_host_fabric_name
mdefine_line|#define fc_host_fabric_name(x)&t;&bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;fabric_name)
DECL|macro|fc_host_tgtid_bind_type
mdefine_line|#define fc_host_tgtid_bind_type(x) &bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;tgtid_bind_type)
DECL|macro|fc_host_rports
mdefine_line|#define fc_host_rports(x) &bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;rports)
DECL|macro|fc_host_rport_bindings
mdefine_line|#define fc_host_rport_bindings(x) &bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;rport_bindings)
DECL|macro|fc_host_next_rport_number
mdefine_line|#define fc_host_next_rport_number(x) &bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;next_rport_number)
DECL|macro|fc_host_next_target_id
mdefine_line|#define fc_host_next_target_id(x) &bslash;&n;&t;(((struct fc_host_attrs *)(x)-&gt;shost_data)-&gt;next_target_id)
multiline_comment|/* The functions by which the transport class and the driver communicate */
DECL|struct|fc_function_template
r_struct
id|fc_function_template
(brace
DECL|member|get_rport_dev_loss_tmo
r_void
(paren
op_star
id|get_rport_dev_loss_tmo
)paren
(paren
r_struct
id|fc_rport
op_star
)paren
suffix:semicolon
DECL|member|set_rport_dev_loss_tmo
r_void
(paren
op_star
id|set_rport_dev_loss_tmo
)paren
(paren
r_struct
id|fc_rport
op_star
comma
id|u32
)paren
suffix:semicolon
DECL|member|get_starget_node_name
r_void
(paren
op_star
id|get_starget_node_name
)paren
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
DECL|member|get_starget_port_name
r_void
(paren
op_star
id|get_starget_port_name
)paren
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
DECL|member|get_starget_port_id
r_void
(paren
op_star
id|get_starget_port_id
)paren
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
DECL|member|get_host_port_id
r_void
(paren
op_star
id|get_host_port_id
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|get_host_port_type
r_void
(paren
op_star
id|get_host_port_type
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|get_host_port_state
r_void
(paren
op_star
id|get_host_port_state
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|get_host_active_fc4s
r_void
(paren
op_star
id|get_host_active_fc4s
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|get_host_speed
r_void
(paren
op_star
id|get_host_speed
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|get_host_fabric_name
r_void
(paren
op_star
id|get_host_fabric_name
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|get_fc_host_stats
r_struct
id|fc_host_statistics
op_star
(paren
op_star
id|get_fc_host_stats
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|reset_fc_host_stats
r_void
(paren
op_star
id|reset_fc_host_stats
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/* allocation lengths for host-specific data */
DECL|member|dd_fcrport_size
id|u32
id|dd_fcrport_size
suffix:semicolon
multiline_comment|/* &n;&t; * The driver sets these to tell the transport class it&n;&t; * wants the attributes displayed in sysfs.  If the show_ flag&n;&t; * is not set, the attribute will be private to the transport&n;&t; * class &n;&t; */
multiline_comment|/* remote port fixed attributes */
DECL|member|show_rport_maxframe_size
r_int
r_int
id|show_rport_maxframe_size
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_rport_supported_classes
r_int
r_int
id|show_rport_supported_classes
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_rport_dev_loss_tmo
r_int
r_int
id|show_rport_dev_loss_tmo
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * target dynamic attributes&n;&t; * These should all be &quot;1&quot; if the driver uses the remote port&n;&t; * add/delete functions (so attributes reflect rport values).&n;&t; */
DECL|member|show_starget_node_name
r_int
r_int
id|show_starget_node_name
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_starget_port_name
r_int
r_int
id|show_starget_port_name
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_starget_port_id
r_int
r_int
id|show_starget_port_id
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* host fixed attributes */
DECL|member|show_host_node_name
r_int
r_int
id|show_host_node_name
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_port_name
r_int
r_int
id|show_host_port_name
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_supported_classes
r_int
r_int
id|show_host_supported_classes
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_supported_fc4s
r_int
r_int
id|show_host_supported_fc4s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_symbolic_name
r_int
r_int
id|show_host_symbolic_name
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_supported_speeds
r_int
r_int
id|show_host_supported_speeds
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_maxframe_size
r_int
r_int
id|show_host_maxframe_size
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_serial_number
r_int
r_int
id|show_host_serial_number
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* host dynamic attributes */
DECL|member|show_host_port_id
r_int
r_int
id|show_host_port_id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_port_type
r_int
r_int
id|show_host_port_type
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_port_state
r_int
r_int
id|show_host_port_state
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_active_fc4s
r_int
r_int
id|show_host_active_fc4s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_speed
r_int
r_int
id|show_host_speed
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_fabric_name
r_int
r_int
id|show_host_fabric_name
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|scsi_transport_template
op_star
id|fc_attach_transport
c_func
(paren
r_struct
id|fc_function_template
op_star
)paren
suffix:semicolon
r_void
id|fc_release_transport
c_func
(paren
r_struct
id|scsi_transport_template
op_star
)paren
suffix:semicolon
r_void
id|fc_remove_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_struct
id|fc_rport
op_star
id|fc_remote_port_add
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_int
id|channel
comma
r_struct
id|fc_rport_identifiers
op_star
id|ids
)paren
suffix:semicolon
r_void
id|fc_remote_port_delete
c_func
(paren
r_struct
id|fc_rport
op_star
id|rport
)paren
suffix:semicolon
r_void
id|fc_remote_port_rolechg
c_func
(paren
r_struct
id|fc_rport
op_star
id|rport
comma
id|u32
id|roles
)paren
suffix:semicolon
r_int
id|fc_remote_port_block
c_func
(paren
r_struct
id|fc_rport
op_star
id|rport
)paren
suffix:semicolon
r_void
id|fc_remote_port_unblock
c_func
(paren
r_struct
id|fc_rport
op_star
id|rport
)paren
suffix:semicolon
r_int
id|scsi_is_fc_rport
c_func
(paren
r_const
r_struct
id|device
op_star
)paren
suffix:semicolon
macro_line|#endif /* SCSI_TRANSPORT_FC_H */
eof
