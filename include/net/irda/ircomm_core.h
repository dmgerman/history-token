multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_core.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Wed Jun  9 08:58:43 1999&n; * Modified at:   Mon Dec 13 11:52:29 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#ifndef IRCOMM_CORE_H
DECL|macro|IRCOMM_CORE_H
mdefine_line|#define IRCOMM_CORE_H
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/ircomm_event.h&gt;
DECL|macro|IRCOMM_MAGIC
mdefine_line|#define IRCOMM_MAGIC 0x98347298
DECL|macro|IRCOMM_HEADER_SIZE
mdefine_line|#define IRCOMM_HEADER_SIZE 1
r_struct
id|ircomm_cb
suffix:semicolon
multiline_comment|/* Forward decl. */
multiline_comment|/*&n; * A small call-table, so we don&squot;t have to check the service-type whenever&n; * we want to do something&n; */
r_typedef
r_struct
(brace
DECL|member|data_request
r_int
(paren
op_star
id|data_request
)paren
(paren
r_struct
id|ircomm_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
id|clen
)paren
suffix:semicolon
DECL|member|connect_request
r_int
(paren
op_star
id|connect_request
)paren
(paren
r_struct
id|ircomm_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_struct
id|ircomm_info
op_star
)paren
suffix:semicolon
DECL|member|connect_response
r_int
(paren
op_star
id|connect_response
)paren
(paren
r_struct
id|ircomm_cb
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
DECL|member|disconnect_request
r_int
(paren
op_star
id|disconnect_request
)paren
(paren
r_struct
id|ircomm_cb
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_struct
id|ircomm_info
op_star
)paren
suffix:semicolon
DECL|typedef|call_t
)brace
id|call_t
suffix:semicolon
DECL|struct|ircomm_cb
r_struct
id|ircomm_cb
(brace
DECL|member|queue
id|irda_queue_t
id|queue
suffix:semicolon
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|notify
id|notify_t
id|notify
suffix:semicolon
DECL|member|issue
id|call_t
id|issue
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
multiline_comment|/* Which TTY line we are using */
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
DECL|member|lsap
r_struct
id|lsap_cb
op_star
id|lsap
suffix:semicolon
DECL|member|dlsap_sel
id|__u8
id|dlsap_sel
suffix:semicolon
multiline_comment|/* Destination LSAP/TSAP selector */
DECL|member|slsap_sel
id|__u8
id|slsap_sel
suffix:semicolon
multiline_comment|/* Source LSAP/TSAP selector */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* Source device address (link we are using) */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Destination device address */
DECL|member|max_header_size
r_int
id|max_header_size
suffix:semicolon
multiline_comment|/* Header space we must reserve for each frame */
DECL|member|max_data_size
r_int
id|max_data_size
suffix:semicolon
multiline_comment|/* The amount of data we can fill in each frame */
DECL|member|flow_status
id|LOCAL_FLOW
id|flow_status
suffix:semicolon
multiline_comment|/* Used by ircomm_lmp */
DECL|member|pkt_count
r_int
id|pkt_count
suffix:semicolon
multiline_comment|/* Number of frames we have sent to IrLAP */
DECL|member|service_type
id|__u8
id|service_type
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|ircomm
suffix:semicolon
r_struct
id|ircomm_cb
op_star
id|ircomm_open
c_func
(paren
id|notify_t
op_star
id|notify
comma
id|__u8
id|service_type
comma
r_int
id|line
)paren
suffix:semicolon
r_int
id|ircomm_close
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
suffix:semicolon
r_int
id|ircomm_data_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|ircomm_data_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|ircomm_process_data
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|ircomm_control_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|ircomm_connect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|__u8
id|dlsap_sel
comma
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u8
id|service_type
)paren
suffix:semicolon
r_void
id|ircomm_connect_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|ircomm_connect_confirm
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
r_int
id|ircomm_connect_response
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_int
id|ircomm_disconnect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_void
id|ircomm_disconnect_indication
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ircomm_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|ircomm_flow_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|LOCAL_FLOW
id|flow
)paren
suffix:semicolon
DECL|macro|ircomm_is_connected
mdefine_line|#define ircomm_is_connected(self) (self-&gt;state == IRCOMM_CONN)
macro_line|#endif
eof
