multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2000.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    1.9&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_EICON_TRACE_IDI_IFC_H__
DECL|macro|__DIVA_EICON_TRACE_IDI_IFC_H__
mdefine_line|#define __DIVA_EICON_TRACE_IDI_IFC_H__
r_void
op_star
id|SuperTraceOpenAdapter
(paren
r_int
id|AdapterNumber
)paren
suffix:semicolon
r_int
id|SuperTraceCloseAdapter
(paren
r_void
op_star
id|AdapterHandle
)paren
suffix:semicolon
r_int
id|SuperTraceWrite
(paren
r_void
op_star
id|AdapterHandle
comma
r_const
r_void
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|SuperTraceReadRequest
(paren
r_void
op_star
id|AdapterHandle
comma
r_const
r_char
op_star
id|name
comma
id|byte
op_star
id|data
)paren
suffix:semicolon
r_int
id|SuperTraceGetNumberOfChannels
(paren
r_void
op_star
id|AdapterHandle
)paren
suffix:semicolon
r_int
id|SuperTraceASSIGN
(paren
r_void
op_star
id|AdapterHandle
comma
id|byte
op_star
id|data
)paren
suffix:semicolon
r_int
id|SuperTraceREMOVE
(paren
r_void
op_star
id|AdapterHandle
)paren
suffix:semicolon
r_int
id|SuperTraceTraceOnRequest
c_func
(paren
r_void
op_star
id|hAdapter
comma
r_const
r_char
op_star
id|name
comma
id|byte
op_star
id|data
)paren
suffix:semicolon
r_int
id|SuperTraceWriteVar
(paren
r_void
op_star
id|AdapterHandle
comma
id|byte
op_star
id|data
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|var
comma
id|byte
id|type
comma
id|byte
id|var_length
)paren
suffix:semicolon
r_int
id|SuperTraceExecuteRequest
(paren
r_void
op_star
id|AdapterHandle
comma
r_const
r_char
op_star
id|name
comma
id|byte
op_star
id|data
)paren
suffix:semicolon
DECL|struct|_diva_strace_path2action
r_typedef
r_struct
id|_diva_strace_path2action
(brace
DECL|member|path
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Full path to variable            */
DECL|member|variable
r_void
op_star
id|variable
suffix:semicolon
multiline_comment|/* Variable that will receive value */
DECL|typedef|diva_strace_path2action_t
)brace
id|diva_strace_path2action_t
suffix:semicolon
DECL|macro|DIVA_MAX_MANAGEMENT_TRANSFER_SIZE
mdefine_line|#define DIVA_MAX_MANAGEMENT_TRANSFER_SIZE 4096
DECL|struct|_diva_strace_context
r_typedef
r_struct
id|_diva_strace_context
(brace
DECL|member|instance
id|diva_strace_library_interface_t
id|instance
suffix:semicolon
DECL|member|Adapter
r_int
id|Adapter
suffix:semicolon
DECL|member|hAdapter
r_void
op_star
id|hAdapter
suffix:semicolon
DECL|member|Channels
r_int
id|Channels
suffix:semicolon
DECL|member|req_busy
r_int
id|req_busy
suffix:semicolon
DECL|member|e
id|ENTITY
id|e
suffix:semicolon
DECL|member|request
id|IDI_CALL
id|request
suffix:semicolon
DECL|member|XData
id|BUFFERS
id|XData
suffix:semicolon
DECL|member|RData
id|BUFFERS
id|RData
suffix:semicolon
DECL|member|buffer
id|byte
id|buffer
(braket
id|DIVA_MAX_MANAGEMENT_TRANSFER_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|removal_state
r_int
id|removal_state
suffix:semicolon
DECL|member|general_b_ch_event
r_int
id|general_b_ch_event
suffix:semicolon
DECL|member|general_fax_event
r_int
id|general_fax_event
suffix:semicolon
DECL|member|general_mdm_event
r_int
id|general_mdm_event
suffix:semicolon
DECL|member|rc_ok
id|byte
id|rc_ok
suffix:semicolon
multiline_comment|/*&n;&t;&t;Initialization request state machine&n;&t;&t;*/
DECL|member|ChannelsTraceActive
r_int
id|ChannelsTraceActive
suffix:semicolon
DECL|member|ModemTraceActive
r_int
id|ModemTraceActive
suffix:semicolon
DECL|member|FaxTraceActive
r_int
id|FaxTraceActive
suffix:semicolon
DECL|member|IncomingCallsCallsActive
r_int
id|IncomingCallsCallsActive
suffix:semicolon
DECL|member|IncomingCallsConnectedActive
r_int
id|IncomingCallsConnectedActive
suffix:semicolon
DECL|member|OutgoingCallsCallsActive
r_int
id|OutgoingCallsCallsActive
suffix:semicolon
DECL|member|OutgoingCallsConnectedActive
r_int
id|OutgoingCallsConnectedActive
suffix:semicolon
DECL|member|trace_mask_init
r_int
id|trace_mask_init
suffix:semicolon
DECL|member|audio_trace_init
r_int
id|audio_trace_init
suffix:semicolon
DECL|member|bchannel_init
r_int
id|bchannel_init
suffix:semicolon
DECL|member|trace_length_init
r_int
id|trace_length_init
suffix:semicolon
DECL|member|trace_on
r_int
id|trace_on
suffix:semicolon
DECL|member|trace_events_down
r_int
id|trace_events_down
suffix:semicolon
DECL|member|l1_trace
r_int
id|l1_trace
suffix:semicolon
DECL|member|l2_trace
r_int
id|l2_trace
suffix:semicolon
multiline_comment|/*&n;&t;&t;Trace&bslash;Event Enable&n;&t;&t;*/
DECL|member|trace_event_mask
id|word
id|trace_event_mask
suffix:semicolon
DECL|member|current_trace_event_mask
id|word
id|current_trace_event_mask
suffix:semicolon
DECL|member|audio_tap_mask
id|dword
id|audio_tap_mask
suffix:semicolon
DECL|member|current_audio_tap_mask
id|dword
id|current_audio_tap_mask
suffix:semicolon
DECL|member|current_eye_pattern_mask
id|dword
id|current_eye_pattern_mask
suffix:semicolon
DECL|member|audio_tap_pending
r_int
id|audio_tap_pending
suffix:semicolon
DECL|member|eye_pattern_pending
r_int
id|eye_pattern_pending
suffix:semicolon
DECL|member|bchannel_trace_mask
id|dword
id|bchannel_trace_mask
suffix:semicolon
DECL|member|current_bchannel_trace_mask
id|dword
id|current_bchannel_trace_mask
suffix:semicolon
DECL|member|lines
id|diva_trace_line_state_t
id|lines
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|parse_entries
r_int
id|parse_entries
suffix:semicolon
DECL|member|cur_parse_entry
r_int
id|cur_parse_entry
suffix:semicolon
DECL|member|parse_table
id|diva_strace_path2action_t
op_star
id|parse_table
suffix:semicolon
DECL|member|user_proc_table
id|diva_trace_library_user_interface_t
id|user_proc_table
suffix:semicolon
DECL|member|line_parse_entry_first
r_int
id|line_parse_entry_first
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|line_parse_entry_last
r_int
id|line_parse_entry_last
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|modem_parse_entry_first
r_int
id|modem_parse_entry_first
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|modem_parse_entry_last
r_int
id|modem_parse_entry_last
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|fax_parse_entry_first
r_int
id|fax_parse_entry_first
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|fax_parse_entry_last
r_int
id|fax_parse_entry_last
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|statistic_parse_first
r_int
id|statistic_parse_first
suffix:semicolon
DECL|member|statistic_parse_last
r_int
id|statistic_parse_last
suffix:semicolon
DECL|member|mdm_statistic_parse_first
r_int
id|mdm_statistic_parse_first
suffix:semicolon
DECL|member|mdm_statistic_parse_last
r_int
id|mdm_statistic_parse_last
suffix:semicolon
DECL|member|fax_statistic_parse_first
r_int
id|fax_statistic_parse_first
suffix:semicolon
DECL|member|fax_statistic_parse_last
r_int
id|fax_statistic_parse_last
suffix:semicolon
DECL|member|line_init_event
id|dword
id|line_init_event
suffix:semicolon
DECL|member|modem_init_event
id|dword
id|modem_init_event
suffix:semicolon
DECL|member|fax_init_event
id|dword
id|fax_init_event
suffix:semicolon
DECL|member|pending_line_status
id|dword
id|pending_line_status
suffix:semicolon
DECL|member|pending_modem_status
id|dword
id|pending_modem_status
suffix:semicolon
DECL|member|pending_fax_status
id|dword
id|pending_fax_status
suffix:semicolon
DECL|member|clear_call_command
id|dword
id|clear_call_command
suffix:semicolon
DECL|member|outgoing_ifc_stats
r_int
id|outgoing_ifc_stats
suffix:semicolon
DECL|member|incoming_ifc_stats
r_int
id|incoming_ifc_stats
suffix:semicolon
DECL|member|modem_ifc_stats
r_int
id|modem_ifc_stats
suffix:semicolon
DECL|member|fax_ifc_stats
r_int
id|fax_ifc_stats
suffix:semicolon
DECL|member|b1_ifc_stats
r_int
id|b1_ifc_stats
suffix:semicolon
DECL|member|b2_ifc_stats
r_int
id|b2_ifc_stats
suffix:semicolon
DECL|member|d1_ifc_stats
r_int
id|d1_ifc_stats
suffix:semicolon
DECL|member|d2_ifc_stats
r_int
id|d2_ifc_stats
suffix:semicolon
DECL|member|Interface
id|diva_trace_interface_state_t
id|Interface
suffix:semicolon
DECL|member|InterfaceStat
id|diva_ifc_statistics_t
id|InterfaceStat
suffix:semicolon
DECL|typedef|diva_strace_context_t
)brace
id|diva_strace_context_t
suffix:semicolon
DECL|struct|_diva_man_var_header
r_typedef
r_struct
id|_diva_man_var_header
(brace
DECL|member|escape
id|byte
id|escape
suffix:semicolon
DECL|member|length
id|byte
id|length
suffix:semicolon
DECL|member|management_id
id|byte
id|management_id
suffix:semicolon
DECL|member|type
id|byte
id|type
suffix:semicolon
DECL|member|attribute
id|byte
id|attribute
suffix:semicolon
DECL|member|status
id|byte
id|status
suffix:semicolon
DECL|member|value_length
id|byte
id|value_length
suffix:semicolon
DECL|member|path_length
id|byte
id|path_length
suffix:semicolon
DECL|typedef|diva_man_var_header_t
)brace
id|diva_man_var_header_t
suffix:semicolon
macro_line|#endif
eof
