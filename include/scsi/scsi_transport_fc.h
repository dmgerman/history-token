multiline_comment|/* &n; *  FiberChannel transport specific attributes exported to sysfs.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SCSI_TRANSPORT_FC_H
DECL|macro|SCSI_TRANSPORT_FC_H
mdefine_line|#define SCSI_TRANSPORT_FC_H
macro_line|#include &lt;linux/config.h&gt;
r_struct
id|scsi_transport_template
suffix:semicolon
DECL|struct|fc_starget_attrs
r_struct
id|fc_starget_attrs
(brace
multiline_comment|/* aka fc_target_attrs */
DECL|member|port_id
r_int
id|port_id
suffix:semicolon
DECL|member|node_name
r_uint64
id|node_name
suffix:semicolon
DECL|member|port_name
r_uint64
id|port_name
suffix:semicolon
DECL|member|dev_loss_tmo
r_uint32
id|dev_loss_tmo
suffix:semicolon
multiline_comment|/* Remote Port loss timeout in seconds. */
DECL|member|dev_loss_timer
r_struct
id|timer_list
id|dev_loss_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|fc_starget_port_id
mdefine_line|#define fc_starget_port_id(x) &bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;port_id)
DECL|macro|fc_starget_node_name
mdefine_line|#define fc_starget_node_name(x) &bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;node_name)
DECL|macro|fc_starget_port_name
mdefine_line|#define fc_starget_port_name(x)&t;&bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;port_name)
DECL|macro|fc_starget_dev_loss_tmo
mdefine_line|#define fc_starget_dev_loss_tmo(x) &bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;dev_loss_tmo)
DECL|macro|fc_starget_dev_loss_timer
mdefine_line|#define fc_starget_dev_loss_timer(x) &bslash;&n;&t;(((struct fc_starget_attrs *)&amp;(x)-&gt;starget_data)-&gt;dev_loss_timer)
DECL|struct|fc_host_attrs
r_struct
id|fc_host_attrs
(brace
DECL|member|link_down_tmo
r_uint32
id|link_down_tmo
suffix:semicolon
multiline_comment|/* Link Down timeout in seconds. */
DECL|member|link_down_timer
r_struct
id|timer_list
id|link_down_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|fc_host_link_down_tmo
mdefine_line|#define fc_host_link_down_tmo(x) &bslash;&n;&t;(((struct fc_host_attrs *)&amp;(x)-&gt;shost_data)-&gt;link_down_tmo)
DECL|macro|fc_host_link_down_timer
mdefine_line|#define fc_host_link_down_timer(x) &bslash;&n;&t;(((struct fc_host_attrs *)&amp;(x)-&gt;shost_data)-&gt;link_down_timer)
multiline_comment|/* The functions by which the transport class and the driver communicate */
DECL|struct|fc_function_template
r_struct
id|fc_function_template
(brace
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
DECL|member|get_starget_dev_loss_tmo
r_void
(paren
op_star
id|get_starget_dev_loss_tmo
)paren
(paren
r_struct
id|scsi_target
op_star
)paren
suffix:semicolon
DECL|member|set_starget_dev_loss_tmo
r_void
(paren
op_star
id|set_starget_dev_loss_tmo
)paren
(paren
r_struct
id|scsi_target
op_star
comma
r_uint32
)paren
suffix:semicolon
DECL|member|get_host_link_down_tmo
r_void
(paren
op_star
id|get_host_link_down_tmo
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|member|set_host_link_down_tmo
r_void
(paren
op_star
id|set_host_link_down_tmo
)paren
(paren
r_struct
id|Scsi_Host
op_star
comma
r_uint32
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * The driver sets these to tell the transport class it&n;&t; * wants the attributes displayed in sysfs.  If the show_ flag&n;&t; * is not set, the attribute will be private to the transport&n;&t; * class &n;&t; */
DECL|member|show_starget_port_id
r_int
r_int
id|show_starget_port_id
suffix:colon
l_int|1
suffix:semicolon
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
DECL|member|show_starget_dev_loss_tmo
r_int
r_int
id|show_starget_dev_loss_tmo
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_host_link_down_tmo
r_int
r_int
id|show_host_link_down_tmo
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Private Attributes */
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
r_int
id|fc_target_block
c_func
(paren
r_struct
id|scsi_target
op_star
id|starget
)paren
suffix:semicolon
r_void
id|fc_target_unblock
c_func
(paren
r_struct
id|scsi_target
op_star
id|starget
)paren
suffix:semicolon
r_int
id|fc_host_block
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
suffix:semicolon
r_void
id|fc_host_unblock
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
suffix:semicolon
macro_line|#endif /* SCSI_TRANSPORT_FC_H */
eof
