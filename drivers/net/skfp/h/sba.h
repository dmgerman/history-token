multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Synchronous Bandwith Allocation (SBA) structs&n; */
macro_line|#ifndef _SBA_
DECL|macro|_SBA_
mdefine_line|#define _SBA_
macro_line|#include &quot;h/mbuf.h&quot;
macro_line|#include &quot;h/sba_def.h&quot;
macro_line|#ifdef&t;SBA
multiline_comment|/* Timer Cell Template */
DECL|struct|timer_cell
r_struct
id|timer_cell
(brace
DECL|member|next_ptr
r_struct
id|timer_cell
op_star
id|next_ptr
suffix:semicolon
DECL|member|prev_ptr
r_struct
id|timer_cell
op_star
id|prev_ptr
suffix:semicolon
DECL|member|start_time
id|u_long
id|start_time
suffix:semicolon
DECL|member|node_var
r_struct
id|s_sba_node_vars
op_star
id|node_var
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Node variables&n; */
DECL|struct|s_sba_node_vars
r_struct
id|s_sba_node_vars
(brace
DECL|member|change_resp_flag
id|u_char
id|change_resp_flag
suffix:semicolon
DECL|member|report_resp_flag
id|u_char
id|report_resp_flag
suffix:semicolon
DECL|member|change_req_flag
id|u_char
id|change_req_flag
suffix:semicolon
DECL|member|report_req_flag
id|u_char
id|report_req_flag
suffix:semicolon
DECL|member|change_amount
r_int
id|change_amount
suffix:semicolon
DECL|member|node_overhead
r_int
id|node_overhead
suffix:semicolon
DECL|member|node_payload
r_int
id|node_payload
suffix:semicolon
DECL|member|node_status
id|u_long
id|node_status
suffix:semicolon
DECL|member|deallocate_status
id|u_char
id|deallocate_status
suffix:semicolon
DECL|member|timer_state
id|u_char
id|timer_state
suffix:semicolon
DECL|member|report_cnt
id|u_short
id|report_cnt
suffix:semicolon
DECL|member|lastrep_req_tranid
r_int
id|lastrep_req_tranid
suffix:semicolon
DECL|member|mac_address
r_struct
id|fddi_addr
id|mac_address
suffix:semicolon
DECL|member|node_sessions
r_struct
id|s_sba_sessions
op_star
id|node_sessions
suffix:semicolon
DECL|member|timer
r_struct
id|timer_cell
id|timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Session variables&n; */
DECL|struct|s_sba_sessions
r_struct
id|s_sba_sessions
(brace
DECL|member|deallocate_status
id|u_long
id|deallocate_status
suffix:semicolon
DECL|member|session_overhead
r_int
id|session_overhead
suffix:semicolon
DECL|member|min_segment_size
id|u_long
id|min_segment_size
suffix:semicolon
DECL|member|session_payload
r_int
id|session_payload
suffix:semicolon
DECL|member|session_status
id|u_long
id|session_status
suffix:semicolon
DECL|member|sba_category
id|u_long
id|sba_category
suffix:semicolon
DECL|member|lastchg_req_tranid
r_int
id|lastchg_req_tranid
suffix:semicolon
DECL|member|session_id
id|u_short
id|session_id
suffix:semicolon
DECL|member|class
id|u_char
r_class
suffix:semicolon
DECL|member|fddi2
id|u_char
id|fddi2
suffix:semicolon
DECL|member|max_t_neg
id|u_long
id|max_t_neg
suffix:semicolon
DECL|member|next_session
r_struct
id|s_sba_sessions
op_star
id|next_session
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|s_sba
r_struct
id|s_sba
(brace
DECL|member|node
r_struct
id|s_sba_node_vars
id|node
(braket
id|MAX_NODES
)braket
suffix:semicolon
DECL|member|session
r_struct
id|s_sba_sessions
id|session
(braket
id|MAX_SESSIONS
)braket
suffix:semicolon
DECL|member|free_session
r_struct
id|s_sba_sessions
op_star
id|free_session
suffix:semicolon
multiline_comment|/* points to the first */
multiline_comment|/* free session */
DECL|member|tail_timer
r_struct
id|timer_cell
op_star
id|tail_timer
suffix:semicolon
multiline_comment|/* points to the last timer cell */
multiline_comment|/*&n;&t; * variables for allocation actions&n;&t; */
DECL|member|total_payload
r_int
id|total_payload
suffix:semicolon
multiline_comment|/* Total Payload */
DECL|member|total_overhead
r_int
id|total_overhead
suffix:semicolon
multiline_comment|/* Total Overhead */
DECL|member|sba_allocatable
r_int
id|sba_allocatable
suffix:semicolon
multiline_comment|/* allocatable sync bandwidth */
multiline_comment|/*&n;&t; * RAF message receive parameters&n;&t; */
DECL|member|msg_path_index
r_int
id|msg_path_index
suffix:semicolon
multiline_comment|/* Path Type */
DECL|member|msg_sba_pl_req
r_int
id|msg_sba_pl_req
suffix:semicolon
multiline_comment|/* Payload Request */
DECL|member|msg_sba_ov_req
r_int
id|msg_sba_ov_req
suffix:semicolon
multiline_comment|/* Overhead Request */
DECL|member|msg_mib_pl
r_int
id|msg_mib_pl
suffix:semicolon
multiline_comment|/* Current Payload for this Path */
DECL|member|msg_mib_ov
r_int
id|msg_mib_ov
suffix:semicolon
multiline_comment|/* Current Overhead for this Path*/
DECL|member|msg_category
r_int
id|msg_category
suffix:semicolon
multiline_comment|/* Category of the Allocation */
DECL|member|msg_max_t_neg
id|u_long
id|msg_max_t_neg
suffix:semicolon
multiline_comment|/* longest T_Neg acceptable */
DECL|member|msg_min_seg_siz
id|u_long
id|msg_min_seg_siz
suffix:semicolon
multiline_comment|/* minimum segement size */
DECL|member|sm
r_struct
id|smt_header
op_star
id|sm
suffix:semicolon
multiline_comment|/* points to the rec message */
DECL|member|msg_alloc_addr
r_struct
id|fddi_addr
op_star
id|msg_alloc_addr
suffix:semicolon
multiline_comment|/* Allocation Address */
multiline_comment|/*&n;&t; * SBA variables&n;&t; */
DECL|member|sba_t_neg
id|u_long
id|sba_t_neg
suffix:semicolon
multiline_comment|/* holds the last T_NEG */
DECL|member|sba_max_alloc
r_int
id|sba_max_alloc
suffix:semicolon
multiline_comment|/* the parsed value of SBAAvailable */
multiline_comment|/*&n;&t; * SBA state machine variables&n;&t; */
DECL|member|sba_next_state
r_int
id|sba_next_state
suffix:semicolon
multiline_comment|/* the next state of the SBA */
DECL|member|sba_command
r_char
id|sba_command
suffix:semicolon
multiline_comment|/* holds the execuded SBA cmd */
DECL|member|sba_available
id|u_char
id|sba_available
suffix:semicolon
multiline_comment|/* parsed value after possible check */
)brace
suffix:semicolon
macro_line|#endif&t;/* SBA */
multiline_comment|/*&n;&t; * variables for the End Station Support&n;&t; */
DECL|struct|s_ess
r_struct
id|s_ess
(brace
multiline_comment|/*&n;&t; * flags and counters&n;&t; */
DECL|member|sync_bw_available
id|u_char
id|sync_bw_available
suffix:semicolon
multiline_comment|/* is set if sync bw is allocated */
DECL|member|local_sba_active
id|u_char
id|local_sba_active
suffix:semicolon
multiline_comment|/* set when a local sba is available */
DECL|member|raf_act_timer_poll
r_char
id|raf_act_timer_poll
suffix:semicolon
multiline_comment|/* activate the timer to send allc req */
DECL|member|timer_count
r_char
id|timer_count
suffix:semicolon
multiline_comment|/* counts every timer function call */
DECL|member|sba_reply_pend
id|SMbuf
op_star
id|sba_reply_pend
suffix:semicolon
multiline_comment|/* local reply for the sba is pending */
multiline_comment|/*&n;&t; * variables for the ess bandwidth control&n;&t; */
DECL|member|sync_bw
r_int
id|sync_bw
suffix:semicolon
multiline_comment|/* holds the allocaed sync bw */
DECL|member|alloc_trans_id
id|u_long
id|alloc_trans_id
suffix:semicolon
multiline_comment|/* trans id of the last alloc req */
)brace
suffix:semicolon
macro_line|#endif
eof
