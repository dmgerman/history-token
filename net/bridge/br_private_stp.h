multiline_comment|/*&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_private_stp.h,v 1.3 2001/02/05 06:03:47 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _BR_PRIVATE_STP_H
DECL|macro|_BR_PRIVATE_STP_H
mdefine_line|#define _BR_PRIVATE_STP_H
DECL|macro|BPDU_TYPE_CONFIG
mdefine_line|#define BPDU_TYPE_CONFIG 0
DECL|macro|BPDU_TYPE_TCN
mdefine_line|#define BPDU_TYPE_TCN 0x80
DECL|struct|br_config_bpdu
r_struct
id|br_config_bpdu
(brace
DECL|member|topology_change
r_int
id|topology_change
suffix:colon
l_int|1
suffix:semicolon
DECL|member|topology_change_ack
r_int
id|topology_change_ack
suffix:colon
l_int|1
suffix:semicolon
DECL|member|root
id|bridge_id
id|root
suffix:semicolon
DECL|member|root_path_cost
r_int
id|root_path_cost
suffix:semicolon
DECL|member|bridge_id
id|bridge_id
id|bridge_id
suffix:semicolon
DECL|member|port_id
id|port_id
id|port_id
suffix:semicolon
DECL|member|message_age
r_int
id|message_age
suffix:semicolon
DECL|member|max_age
r_int
id|max_age
suffix:semicolon
DECL|member|hello_time
r_int
id|hello_time
suffix:semicolon
DECL|member|forward_delay
r_int
id|forward_delay
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* called under bridge lock */
DECL|function|br_is_designated_port
r_static
r_inline
r_int
id|br_is_designated_port
c_func
(paren
r_const
r_struct
id|net_bridge_port
op_star
id|p
)paren
(brace
r_return
op_logical_neg
id|memcmp
c_func
(paren
op_amp
id|p-&gt;designated_bridge
comma
op_amp
id|p-&gt;br-&gt;bridge_id
comma
l_int|8
)paren
op_logical_and
(paren
id|p-&gt;designated_port
op_eq
id|p-&gt;port_id
)paren
suffix:semicolon
)brace
multiline_comment|/* br_stp.c */
r_extern
r_void
id|br_become_root_bridge
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
r_extern
r_void
id|br_config_bpdu_generation
c_func
(paren
r_struct
id|net_bridge
op_star
)paren
suffix:semicolon
r_extern
r_void
id|br_configuration_update
c_func
(paren
r_struct
id|net_bridge
op_star
)paren
suffix:semicolon
r_extern
r_void
id|br_port_state_selection
c_func
(paren
r_struct
id|net_bridge
op_star
)paren
suffix:semicolon
r_extern
r_void
id|br_received_config_bpdu
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
comma
r_struct
id|br_config_bpdu
op_star
id|bpdu
)paren
suffix:semicolon
r_extern
r_void
id|br_received_tcn_bpdu
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_transmit_config
c_func
(paren
r_struct
id|net_bridge_port
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|br_transmit_tcn
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
r_extern
r_void
id|br_topology_change_detection
c_func
(paren
r_struct
id|net_bridge
op_star
id|br
)paren
suffix:semicolon
multiline_comment|/* br_stp_bpdu.c */
r_extern
r_void
id|br_send_config_bpdu
c_func
(paren
r_struct
id|net_bridge_port
op_star
comma
r_struct
id|br_config_bpdu
op_star
)paren
suffix:semicolon
r_extern
r_void
id|br_send_tcn_bpdu
c_func
(paren
r_struct
id|net_bridge_port
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
