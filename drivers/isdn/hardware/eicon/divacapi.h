multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*#define DEBUG */
DECL|macro|IMPLEMENT_DTMF
mdefine_line|#define IMPLEMENT_DTMF 1
DECL|macro|IMPLEMENT_LINE_INTERCONNECT2
mdefine_line|#define IMPLEMENT_LINE_INTERCONNECT2 1
DECL|macro|IMPLEMENT_ECHO_CANCELLER
mdefine_line|#define IMPLEMENT_ECHO_CANCELLER 1
DECL|macro|IMPLEMENT_RTP
mdefine_line|#define IMPLEMENT_RTP 1
DECL|macro|IMPLEMENT_T38
mdefine_line|#define IMPLEMENT_T38 1
DECL|macro|IMPLEMENT_FAX_SUB_SEP_PWD
mdefine_line|#define IMPLEMENT_FAX_SUB_SEP_PWD 1
DECL|macro|IMPLEMENT_V18
mdefine_line|#define IMPLEMENT_V18 1
DECL|macro|IMPLEMENT_DTMF_TONE
mdefine_line|#define IMPLEMENT_DTMF_TONE 1
DECL|macro|IMPLEMENT_PIAFS
mdefine_line|#define IMPLEMENT_PIAFS 1
DECL|macro|IMPLEMENT_FAX_PAPER_FORMATS
mdefine_line|#define IMPLEMENT_FAX_PAPER_FORMATS 1
DECL|macro|IMPLEMENT_VOWN
mdefine_line|#define IMPLEMENT_VOWN 1
DECL|macro|IMPLEMENT_CAPIDTMF
mdefine_line|#define IMPLEMENT_CAPIDTMF 1
DECL|macro|IMPLEMENT_FAX_NONSTANDARD
mdefine_line|#define IMPLEMENT_FAX_NONSTANDARD 1
DECL|macro|VSWITCH_SUPPORT
mdefine_line|#define VSWITCH_SUPPORT 1
DECL|macro|IMPLEMENT_LINE_INTERCONNECT
mdefine_line|#define IMPLEMENT_LINE_INTERCONNECT 0
DECL|macro|IMPLEMENT_MARKED_OK_AFTER_FC
mdefine_line|#define IMPLEMENT_MARKED_OK_AFTER_FC 1
macro_line|#include &quot;capidtmf.h&quot;
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Common API internal definitions                                  */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|MAX_APPL
mdefine_line|#define MAX_APPL 240
DECL|macro|MAX_NCCI
mdefine_line|#define MAX_NCCI           127
DECL|macro|MSG_IN_QUEUE_SIZE
mdefine_line|#define MSG_IN_QUEUE_SIZE  ((4096 + 3) &amp; 0xfffc)  /* must be multiple of 4 */
DECL|macro|MSG_IN_OVERHEAD
mdefine_line|#define MSG_IN_OVERHEAD    sizeof(APPL   *)
DECL|macro|MAX_NL_CHANNEL
mdefine_line|#define MAX_NL_CHANNEL     255
DECL|macro|MAX_DATA_B3
mdefine_line|#define MAX_DATA_B3        8
DECL|macro|MAX_DATA_ACK
mdefine_line|#define MAX_DATA_ACK       MAX_DATA_B3
DECL|macro|MAX_MULTI_IE
mdefine_line|#define MAX_MULTI_IE       6
DECL|macro|MAX_MSG_SIZE
mdefine_line|#define MAX_MSG_SIZE       256
DECL|macro|MAX_MSG_PARMS
mdefine_line|#define MAX_MSG_PARMS      10
DECL|macro|MAX_CPN_MASK_SIZE
mdefine_line|#define MAX_CPN_MASK_SIZE  16
DECL|macro|MAX_MSN_CONFIG
mdefine_line|#define MAX_MSN_CONFIG     10
DECL|macro|EXT_CONTROLLER
mdefine_line|#define EXT_CONTROLLER     0x80
DECL|macro|CODEC
mdefine_line|#define CODEC              0x01
DECL|macro|CODEC_PERMANENT
mdefine_line|#define CODEC_PERMANENT    0x02
DECL|macro|ADV_VOICE
mdefine_line|#define ADV_VOICE          0x03
DECL|macro|MAX_CIP_TYPES
mdefine_line|#define MAX_CIP_TYPES      5  /* kind of CIP types for group optimization */
DECL|macro|C_IND_MASK_DWORDS
mdefine_line|#define C_IND_MASK_DWORDS  ((MAX_APPL+32) &gt;&gt; 5)
DECL|macro|FAX_CONNECT_INFO_BUFFER_SIZE
mdefine_line|#define FAX_CONNECT_INFO_BUFFER_SIZE  256
DECL|macro|NCPI_BUFFER_SIZE
mdefine_line|#define NCPI_BUFFER_SIZE              256
DECL|macro|MAX_CHANNELS_PER_PLCI
mdefine_line|#define MAX_CHANNELS_PER_PLCI         8
DECL|macro|MAX_INTERNAL_COMMAND_LEVELS
mdefine_line|#define MAX_INTERNAL_COMMAND_LEVELS   4
DECL|macro|INTERNAL_REQ_BUFFER_SIZE
mdefine_line|#define INTERNAL_REQ_BUFFER_SIZE      272
DECL|macro|INTERNAL_IND_BUFFER_SIZE
mdefine_line|#define INTERNAL_IND_BUFFER_SIZE      768
DECL|macro|DTMF_PARAMETER_BUFFER_SIZE
mdefine_line|#define DTMF_PARAMETER_BUFFER_SIZE    12
DECL|macro|ADV_VOICE_COEF_BUFFER_SIZE
mdefine_line|#define ADV_VOICE_COEF_BUFFER_SIZE    50
DECL|macro|LI_PLCI_B_QUEUE_ENTRIES
mdefine_line|#define LI_PLCI_B_QUEUE_ENTRIES       256
DECL|typedef|APPL
r_typedef
r_struct
id|_APPL
id|APPL
suffix:semicolon
DECL|typedef|PLCI
r_typedef
r_struct
id|_PLCI
id|PLCI
suffix:semicolon
DECL|typedef|NCCI
r_typedef
r_struct
id|_NCCI
id|NCCI
suffix:semicolon
DECL|typedef|DIVA_CAPI_ADAPTER
r_typedef
r_struct
id|_DIVA_CAPI_ADAPTER
id|DIVA_CAPI_ADAPTER
suffix:semicolon
DECL|typedef|DATA_B3_DESC
r_typedef
r_struct
id|_DATA_B3_DESC
id|DATA_B3_DESC
suffix:semicolon
DECL|typedef|DATA_ACK_DESC
r_typedef
r_struct
id|_DATA_ACK_DESC
id|DATA_ACK_DESC
suffix:semicolon
DECL|typedef|MANUFACTURER_PROFILE
r_typedef
r_struct
id|manufacturer_profile_s
id|MANUFACTURER_PROFILE
suffix:semicolon
DECL|typedef|FAX_NCPI
r_typedef
r_struct
id|fax_ncpi_s
id|FAX_NCPI
suffix:semicolon
DECL|typedef|API_PARSE
r_typedef
r_struct
id|api_parse_s
id|API_PARSE
suffix:semicolon
DECL|typedef|API_SAVE
r_typedef
r_struct
id|api_save_s
id|API_SAVE
suffix:semicolon
DECL|typedef|MSN_CONFIG
r_typedef
r_struct
id|msn_config_s
id|MSN_CONFIG
suffix:semicolon
DECL|typedef|MSN_CONFIG_MAX
r_typedef
r_struct
id|msn_config_max_s
id|MSN_CONFIG_MAX
suffix:semicolon
DECL|typedef|MSN_LD
r_typedef
r_struct
id|msn_ld_s
id|MSN_LD
suffix:semicolon
DECL|struct|manufacturer_profile_s
r_struct
id|manufacturer_profile_s
(brace
DECL|member|private_options
id|dword
id|private_options
suffix:semicolon
DECL|member|rtp_primary_payloads
id|dword
id|rtp_primary_payloads
suffix:semicolon
DECL|member|rtp_additional_payloads
id|dword
id|rtp_additional_payloads
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fax_ncpi_s
r_struct
id|fax_ncpi_s
(brace
DECL|member|options
id|word
id|options
suffix:semicolon
DECL|member|format
id|word
id|format
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|msn_config_s
r_struct
id|msn_config_s
(brace
DECL|member|msn
id|byte
id|msn
(braket
id|MAX_CPN_MASK_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|msn_config_max_s
r_struct
id|msn_config_max_s
(brace
DECL|member|msn_conf
id|MSN_CONFIG
id|msn_conf
(braket
id|MAX_MSN_CONFIG
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|msn_ld_s
r_struct
id|msn_ld_s
(brace
DECL|member|low
id|dword
id|low
suffix:semicolon
DECL|member|high
id|dword
id|high
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|api_parse_s
r_struct
id|api_parse_s
(brace
DECL|member|length
id|word
id|length
suffix:semicolon
DECL|member|info
id|byte
op_star
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|api_save_s
r_struct
id|api_save_s
(brace
DECL|member|parms
id|API_PARSE
id|parms
(braket
id|MAX_MSG_PARMS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|info
id|byte
id|info
(braket
id|MAX_MSG_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_DATA_B3_DESC
r_struct
id|_DATA_B3_DESC
(brace
DECL|member|Handle
id|word
id|Handle
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|Flags
id|word
id|Flags
suffix:semicolon
DECL|member|Length
id|word
id|Length
suffix:semicolon
DECL|member|P
r_void
op_star
id|P
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_DATA_ACK_DESC
r_struct
id|_DATA_ACK_DESC
(brace
DECL|member|Handle
id|word
id|Handle
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|t_std_internal_command
r_typedef
r_void
(paren
op_star
id|t_std_internal_command
)paren
(paren
id|dword
id|Id
comma
id|PLCI
op_star
id|plci
comma
id|byte
id|Rc
)paren
suffix:semicolon
multiline_comment|/************************************************************************/
multiline_comment|/* Don&squot;t forget to adapt dos.asm after changing the _APPL structure!!!! */
DECL|struct|_APPL
r_struct
id|_APPL
(brace
DECL|member|Id
id|word
id|Id
suffix:semicolon
DECL|member|NullCREnable
id|word
id|NullCREnable
suffix:semicolon
DECL|member|CDEnable
id|word
id|CDEnable
suffix:semicolon
DECL|member|S_Handle
id|dword
id|S_Handle
suffix:semicolon
DECL|member|s_function
id|LIST_ENTRY
id|s_function
suffix:semicolon
DECL|member|s_context
id|dword
id|s_context
suffix:semicolon
DECL|member|s_count
id|word
id|s_count
suffix:semicolon
DECL|member|s_next
id|APPL
op_star
id|s_next
suffix:semicolon
DECL|member|xbuffer_used
id|byte
op_star
id|xbuffer_used
suffix:semicolon
DECL|member|xbuffer_internal
r_void
op_star
op_star
id|xbuffer_internal
suffix:semicolon
DECL|member|xbuffer_ptr
r_void
op_star
op_star
id|xbuffer_ptr
suffix:semicolon
DECL|member|queue
id|byte
op_star
id|queue
suffix:semicolon
DECL|member|queue_size
id|word
id|queue_size
suffix:semicolon
DECL|member|queue_free
id|word
id|queue_free
suffix:semicolon
DECL|member|queue_read
id|word
id|queue_read
suffix:semicolon
DECL|member|queue_write
id|word
id|queue_write
suffix:semicolon
DECL|member|queue_signal
id|word
id|queue_signal
suffix:semicolon
DECL|member|msg_lost
id|byte
id|msg_lost
suffix:semicolon
DECL|member|appl_flags
id|byte
id|appl_flags
suffix:semicolon
DECL|member|Number
id|word
id|Number
suffix:semicolon
DECL|member|MaxBuffer
id|word
id|MaxBuffer
suffix:semicolon
DECL|member|MaxNCCI
id|byte
id|MaxNCCI
suffix:semicolon
DECL|member|MaxNCCIData
id|byte
id|MaxNCCIData
suffix:semicolon
DECL|member|MaxDataLength
id|word
id|MaxDataLength
suffix:semicolon
DECL|member|NCCIDataFlowCtrlTimer
id|word
id|NCCIDataFlowCtrlTimer
suffix:semicolon
DECL|member|ReceiveBuffer
id|byte
op_star
id|ReceiveBuffer
suffix:semicolon
DECL|member|DataNCCI
id|word
op_star
id|DataNCCI
suffix:semicolon
DECL|member|DataFlags
id|word
op_star
id|DataFlags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_PLCI
r_struct
id|_PLCI
(brace
DECL|member|Sig
id|ENTITY
id|Sig
suffix:semicolon
DECL|member|NL
id|ENTITY
id|NL
suffix:semicolon
DECL|member|RNum
id|word
id|RNum
suffix:semicolon
DECL|member|RFlags
id|word
id|RFlags
suffix:semicolon
DECL|member|RData
id|BUFFERS
id|RData
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|XData
id|BUFFERS
id|XData
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|NData
id|BUFFERS
id|NData
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|adapter
id|DIVA_CAPI_ADAPTER
op_star
id|adapter
suffix:semicolon
DECL|member|appl
id|APPL
op_star
id|appl
suffix:semicolon
DECL|member|relatedPTYPLCI
id|PLCI
op_star
id|relatedPTYPLCI
suffix:semicolon
DECL|member|Id
id|byte
id|Id
suffix:semicolon
DECL|member|State
id|byte
id|State
suffix:semicolon
DECL|member|sig_req
id|byte
id|sig_req
suffix:semicolon
DECL|member|nl_req
id|byte
id|nl_req
suffix:semicolon
DECL|member|SuppState
id|byte
id|SuppState
suffix:semicolon
DECL|member|channels
id|byte
id|channels
suffix:semicolon
DECL|member|tel
id|byte
id|tel
suffix:semicolon
DECL|member|B1_resource
id|byte
id|B1_resource
suffix:semicolon
DECL|member|B2_prot
id|byte
id|B2_prot
suffix:semicolon
DECL|member|B3_prot
id|byte
id|B3_prot
suffix:semicolon
DECL|member|command
id|word
id|command
suffix:semicolon
DECL|member|m_command
id|word
id|m_command
suffix:semicolon
DECL|member|internal_command
id|word
id|internal_command
suffix:semicolon
DECL|member|number
id|word
id|number
suffix:semicolon
DECL|member|req_in_start
id|word
id|req_in_start
suffix:semicolon
DECL|member|req_in
id|word
id|req_in
suffix:semicolon
DECL|member|req_out
id|word
id|req_out
suffix:semicolon
DECL|member|msg_in_write_pos
id|word
id|msg_in_write_pos
suffix:semicolon
DECL|member|msg_in_read_pos
id|word
id|msg_in_read_pos
suffix:semicolon
DECL|member|msg_in_wrap_pos
id|word
id|msg_in_wrap_pos
suffix:semicolon
DECL|member|data_sent_ptr
r_void
op_star
id|data_sent_ptr
suffix:semicolon
DECL|member|data_sent
id|byte
id|data_sent
suffix:semicolon
DECL|member|send_disc
id|byte
id|send_disc
suffix:semicolon
DECL|member|sig_global_req
id|byte
id|sig_global_req
suffix:semicolon
DECL|member|sig_remove_id
id|byte
id|sig_remove_id
suffix:semicolon
DECL|member|nl_global_req
id|byte
id|nl_global_req
suffix:semicolon
DECL|member|nl_remove_id
id|byte
id|nl_remove_id
suffix:semicolon
DECL|member|b_channel
id|byte
id|b_channel
suffix:semicolon
DECL|member|adv_nl
id|byte
id|adv_nl
suffix:semicolon
DECL|member|manufacturer
id|byte
id|manufacturer
suffix:semicolon
DECL|member|call_dir
id|byte
id|call_dir
suffix:semicolon
DECL|member|hook_state
id|byte
id|hook_state
suffix:semicolon
DECL|member|spoofed_msg
id|byte
id|spoofed_msg
suffix:semicolon
DECL|member|ptyState
id|byte
id|ptyState
suffix:semicolon
DECL|member|cr_enquiry
id|byte
id|cr_enquiry
suffix:semicolon
DECL|member|hangup_flow_ctrl_timer
id|word
id|hangup_flow_ctrl_timer
suffix:semicolon
DECL|member|ncci_ring_list
id|word
id|ncci_ring_list
suffix:semicolon
DECL|member|inc_dis_ncci_table
id|byte
id|inc_dis_ncci_table
(braket
id|MAX_CHANNELS_PER_PLCI
)braket
suffix:semicolon
DECL|member|internal_command_queue
id|t_std_internal_command
id|internal_command_queue
(braket
id|MAX_INTERNAL_COMMAND_LEVELS
)braket
suffix:semicolon
DECL|member|c_ind_mask_table
id|dword
id|c_ind_mask_table
(braket
id|C_IND_MASK_DWORDS
)braket
suffix:semicolon
DECL|member|group_optimization_mask_table
id|dword
id|group_optimization_mask_table
(braket
id|C_IND_MASK_DWORDS
)braket
suffix:semicolon
DECL|member|RBuffer
id|byte
id|RBuffer
(braket
l_int|200
)braket
suffix:semicolon
DECL|member|msg_in_queue
id|dword
id|msg_in_queue
(braket
id|MSG_IN_QUEUE_SIZE
op_div
r_sizeof
(paren
id|dword
)paren
)braket
suffix:semicolon
DECL|member|saved_msg
id|API_SAVE
id|saved_msg
suffix:semicolon
DECL|member|B_protocol
id|API_SAVE
id|B_protocol
suffix:semicolon
DECL|member|fax_connect_info_length
id|byte
id|fax_connect_info_length
suffix:semicolon
DECL|member|fax_connect_info_buffer
id|byte
id|fax_connect_info_buffer
(braket
id|FAX_CONNECT_INFO_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|fax_edata_ack_length
id|byte
id|fax_edata_ack_length
suffix:semicolon
DECL|member|nsf_control_bits
id|word
id|nsf_control_bits
suffix:semicolon
DECL|member|ncpi_state
id|byte
id|ncpi_state
suffix:semicolon
DECL|member|ncpi_buffer
id|byte
id|ncpi_buffer
(braket
id|NCPI_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|internal_req_buffer
id|byte
id|internal_req_buffer
(braket
id|INTERNAL_REQ_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|internal_ind_buffer
id|byte
id|internal_ind_buffer
(braket
id|INTERNAL_IND_BUFFER_SIZE
op_plus
l_int|3
)braket
suffix:semicolon
DECL|member|requested_options_conn
id|dword
id|requested_options_conn
suffix:semicolon
DECL|member|requested_options
id|dword
id|requested_options
suffix:semicolon
DECL|member|B1_facilities
id|word
id|B1_facilities
suffix:semicolon
DECL|member|adjust_b_parms_msg
id|API_SAVE
op_star
id|adjust_b_parms_msg
suffix:semicolon
DECL|member|adjust_b_facilities
id|word
id|adjust_b_facilities
suffix:semicolon
DECL|member|adjust_b_command
id|word
id|adjust_b_command
suffix:semicolon
DECL|member|adjust_b_ncci
id|word
id|adjust_b_ncci
suffix:semicolon
DECL|member|adjust_b_mode
id|word
id|adjust_b_mode
suffix:semicolon
DECL|member|adjust_b_state
id|word
id|adjust_b_state
suffix:semicolon
DECL|member|adjust_b_restore
id|byte
id|adjust_b_restore
suffix:semicolon
DECL|member|dtmf_rec_active
id|byte
id|dtmf_rec_active
suffix:semicolon
DECL|member|dtmf_rec_pulse_ms
id|word
id|dtmf_rec_pulse_ms
suffix:semicolon
DECL|member|dtmf_rec_pause_ms
id|word
id|dtmf_rec_pause_ms
suffix:semicolon
DECL|member|dtmf_send_requests
id|byte
id|dtmf_send_requests
suffix:semicolon
DECL|member|dtmf_send_pulse_ms
id|word
id|dtmf_send_pulse_ms
suffix:semicolon
DECL|member|dtmf_send_pause_ms
id|word
id|dtmf_send_pause_ms
suffix:semicolon
DECL|member|dtmf_cmd
id|word
id|dtmf_cmd
suffix:semicolon
DECL|member|dtmf_msg_number_queue
id|word
id|dtmf_msg_number_queue
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|dtmf_parameter_length
id|byte
id|dtmf_parameter_length
suffix:semicolon
DECL|member|dtmf_parameter_buffer
id|byte
id|dtmf_parameter_buffer
(braket
id|DTMF_PARAMETER_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|capidtmf_state
id|t_capidtmf_state
id|capidtmf_state
suffix:semicolon
DECL|member|li_bchannel_id
id|byte
id|li_bchannel_id
suffix:semicolon
multiline_comment|/* BRI: 1..2, PRI: 1..32 */
DECL|member|li_channel_bits
id|byte
id|li_channel_bits
suffix:semicolon
DECL|member|li_notify_update
id|byte
id|li_notify_update
suffix:semicolon
DECL|member|li_cmd
id|word
id|li_cmd
suffix:semicolon
DECL|member|li_write_command
id|word
id|li_write_command
suffix:semicolon
DECL|member|li_write_channel
id|word
id|li_write_channel
suffix:semicolon
DECL|member|li_plci_b_write_pos
id|word
id|li_plci_b_write_pos
suffix:semicolon
DECL|member|li_plci_b_read_pos
id|word
id|li_plci_b_read_pos
suffix:semicolon
DECL|member|li_plci_b_req_pos
id|word
id|li_plci_b_req_pos
suffix:semicolon
DECL|member|li_plci_b_queue
id|dword
id|li_plci_b_queue
(braket
id|LI_PLCI_B_QUEUE_ENTRIES
)braket
suffix:semicolon
DECL|member|ec_cmd
id|word
id|ec_cmd
suffix:semicolon
DECL|member|ec_idi_options
id|word
id|ec_idi_options
suffix:semicolon
DECL|member|ec_tail_length
id|word
id|ec_tail_length
suffix:semicolon
DECL|member|tone_last_indication_code
id|byte
id|tone_last_indication_code
suffix:semicolon
DECL|member|vswitchstate
id|byte
id|vswitchstate
suffix:semicolon
DECL|member|vsprot
id|byte
id|vsprot
suffix:semicolon
DECL|member|vsprotdialect
id|byte
id|vsprotdialect
suffix:semicolon
DECL|member|notifiedcall
id|byte
id|notifiedcall
suffix:semicolon
multiline_comment|/* Flag if it is a spoofed call */
DECL|member|rx_dma_descriptor
r_int
id|rx_dma_descriptor
suffix:semicolon
DECL|member|rx_dma_magic
id|dword
id|rx_dma_magic
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_NCCI
r_struct
id|_NCCI
(brace
DECL|member|data_out
id|byte
id|data_out
suffix:semicolon
DECL|member|data_pending
id|byte
id|data_pending
suffix:semicolon
DECL|member|data_ack_out
id|byte
id|data_ack_out
suffix:semicolon
DECL|member|data_ack_pending
id|byte
id|data_ack_pending
suffix:semicolon
DECL|member|DBuffer
id|DATA_B3_DESC
id|DBuffer
(braket
id|MAX_DATA_B3
)braket
suffix:semicolon
DECL|member|DataAck
id|DATA_ACK_DESC
id|DataAck
(braket
id|MAX_DATA_ACK
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_DIVA_CAPI_ADAPTER
r_struct
id|_DIVA_CAPI_ADAPTER
(brace
DECL|member|request
id|IDI_CALL
id|request
suffix:semicolon
DECL|member|Id
id|byte
id|Id
suffix:semicolon
DECL|member|max_plci
id|byte
id|max_plci
suffix:semicolon
DECL|member|max_listen
id|byte
id|max_listen
suffix:semicolon
DECL|member|listen_active
id|byte
id|listen_active
suffix:semicolon
DECL|member|plci
id|PLCI
op_star
id|plci
suffix:semicolon
DECL|member|ch_ncci
id|byte
id|ch_ncci
(braket
id|MAX_NL_CHANNEL
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ncci_ch
id|byte
id|ncci_ch
(braket
id|MAX_NCCI
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ncci_plci
id|byte
id|ncci_plci
(braket
id|MAX_NCCI
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ncci_state
id|byte
id|ncci_state
(braket
id|MAX_NCCI
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ncci_next
id|byte
id|ncci_next
(braket
id|MAX_NCCI
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ncci
id|NCCI
id|ncci
(braket
id|MAX_NCCI
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ch_flow_control
id|byte
id|ch_flow_control
(braket
id|MAX_NL_CHANNEL
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Used by XON protocol */
DECL|member|ch_flow_control_pending
id|byte
id|ch_flow_control_pending
suffix:semicolon
DECL|member|ch_flow_plci
id|byte
id|ch_flow_plci
(braket
id|MAX_NL_CHANNEL
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|last_flow_control_ch
r_int
id|last_flow_control_ch
suffix:semicolon
DECL|member|Info_Mask
id|dword
id|Info_Mask
(braket
id|MAX_APPL
)braket
suffix:semicolon
DECL|member|CIP_Mask
id|dword
id|CIP_Mask
(braket
id|MAX_APPL
)braket
suffix:semicolon
DECL|member|Notification_Mask
id|dword
id|Notification_Mask
(braket
id|MAX_APPL
)braket
suffix:semicolon
DECL|member|codec_listen
id|PLCI
op_star
id|codec_listen
(braket
id|MAX_APPL
)braket
suffix:semicolon
DECL|member|requested_options_table
id|dword
id|requested_options_table
(braket
id|MAX_APPL
)braket
suffix:semicolon
DECL|member|profile
id|API_PROFILE
id|profile
suffix:semicolon
DECL|member|man_profile
id|MANUFACTURER_PROFILE
id|man_profile
suffix:semicolon
DECL|member|manufacturer_features
id|dword
id|manufacturer_features
suffix:semicolon
DECL|member|AdvCodecFLAG
id|byte
id|AdvCodecFLAG
suffix:semicolon
DECL|member|AdvCodecPLCI
id|PLCI
op_star
id|AdvCodecPLCI
suffix:semicolon
DECL|member|AdvSignalPLCI
id|PLCI
op_star
id|AdvSignalPLCI
suffix:semicolon
DECL|member|AdvSignalAppl
id|APPL
op_star
id|AdvSignalAppl
suffix:semicolon
DECL|member|TelOAD
id|byte
id|TelOAD
(braket
l_int|23
)braket
suffix:semicolon
DECL|member|TelOSA
id|byte
id|TelOSA
(braket
l_int|23
)braket
suffix:semicolon
DECL|member|scom_appl_disable
id|byte
id|scom_appl_disable
suffix:semicolon
DECL|member|automatic_lawPLCI
id|PLCI
op_star
id|automatic_lawPLCI
suffix:semicolon
DECL|member|automatic_law
id|byte
id|automatic_law
suffix:semicolon
DECL|member|u_law
id|byte
id|u_law
suffix:semicolon
DECL|member|adv_voice_coef_length
id|byte
id|adv_voice_coef_length
suffix:semicolon
DECL|member|adv_voice_coef_buffer
id|byte
id|adv_voice_coef_buffer
(braket
id|ADV_VOICE_COEF_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|li_pri
id|byte
id|li_pri
suffix:semicolon
DECL|member|li_channels
id|byte
id|li_channels
suffix:semicolon
DECL|member|li_base
id|word
id|li_base
suffix:semicolon
DECL|member|adapter_disabled
id|byte
id|adapter_disabled
suffix:semicolon
DECL|member|group_optimization_enabled
id|byte
id|group_optimization_enabled
suffix:semicolon
multiline_comment|/* use application groups if enabled */
DECL|member|sdram_bar
id|dword
id|sdram_bar
suffix:semicolon
DECL|member|flag_dynamic_l1_down
id|byte
id|flag_dynamic_l1_down
suffix:semicolon
multiline_comment|/* for hunt groups:down layer 1 if no appl present*/
DECL|member|FlowControlIdTable
id|byte
id|FlowControlIdTable
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|FlowControlSkipTable
id|byte
id|FlowControlSkipTable
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|os_card
r_void
op_star
id|os_card
suffix:semicolon
multiline_comment|/* pointer to associated OS dependent adapter structure */
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Application flags                                                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|APPL_FLAG_OLD_LI_SPEC
mdefine_line|#define APPL_FLAG_OLD_LI_SPEC           0x01
DECL|macro|APPL_FLAG_PRIV_EC_SPEC
mdefine_line|#define APPL_FLAG_PRIV_EC_SPEC          0x02
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* API parameter definitions                                        */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|X75_TTX
mdefine_line|#define X75_TTX         1       /* x.75 for ttx                     */
DECL|macro|TRF
mdefine_line|#define TRF             2       /* transparent with hdlc framing    */
DECL|macro|TRF_IN
mdefine_line|#define TRF_IN          3       /* transparent with hdlc fr. inc.   */
DECL|macro|SDLC
mdefine_line|#define SDLC            4       /* sdlc, sna layer-2                */
DECL|macro|X75_BTX
mdefine_line|#define X75_BTX         5       /* x.75 for btx                     */
DECL|macro|LAPD
mdefine_line|#define LAPD            6       /* lapd (Q.921)                     */
DECL|macro|X25_L2
mdefine_line|#define X25_L2          7       /* x.25 layer-2                     */
DECL|macro|V120_L2
mdefine_line|#define V120_L2         8       /* V.120 layer-2 protocol           */
DECL|macro|V42_IN
mdefine_line|#define V42_IN          9       /* V.42 layer-2 protocol, incomming */
DECL|macro|V42
mdefine_line|#define V42            10       /* V.42 layer-2 protocol            */
DECL|macro|MDM_ATP
mdefine_line|#define MDM_ATP        11       /* AT Parser built in the L2        */
DECL|macro|X75_V42BIS
mdefine_line|#define X75_V42BIS     12       /* ISO7776 (X.75 SLP) modified to support V.42 bis compression */
DECL|macro|RTPL2_IN
mdefine_line|#define RTPL2_IN       13       /* RTP layer-2 protocol, incomming  */
DECL|macro|RTPL2
mdefine_line|#define RTPL2          14       /* RTP layer-2 protocol             */
DECL|macro|V120_V42BIS
mdefine_line|#define V120_V42BIS    15       /* V.120 layer-2 protocol supporting V.42 bis compression */
DECL|macro|T70NL
mdefine_line|#define T70NL           1
DECL|macro|X25PLP
mdefine_line|#define X25PLP          2
DECL|macro|T70NLX
mdefine_line|#define T70NLX          3
DECL|macro|TRANSPARENT_NL
mdefine_line|#define TRANSPARENT_NL  4
DECL|macro|ISO8208
mdefine_line|#define ISO8208         5
DECL|macro|T30
mdefine_line|#define T30             6
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* FAX interface to IDI                                             */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|CAPI_MAX_HEAD_LINE_SPACE
mdefine_line|#define CAPI_MAX_HEAD_LINE_SPACE        89
DECL|macro|CAPI_MAX_DATE_TIME_LENGTH
mdefine_line|#define CAPI_MAX_DATE_TIME_LENGTH       18
DECL|macro|T30_MAX_STATION_ID_LENGTH
mdefine_line|#define T30_MAX_STATION_ID_LENGTH       20
DECL|macro|T30_MAX_SUBADDRESS_LENGTH
mdefine_line|#define T30_MAX_SUBADDRESS_LENGTH       20
DECL|macro|T30_MAX_PASSWORD_LENGTH
mdefine_line|#define T30_MAX_PASSWORD_LENGTH         20
DECL|typedef|T30_INFO
r_typedef
r_struct
id|t30_info_s
id|T30_INFO
suffix:semicolon
DECL|struct|t30_info_s
r_struct
id|t30_info_s
(brace
DECL|member|code
id|byte
id|code
suffix:semicolon
DECL|member|rate_div_2400
id|byte
id|rate_div_2400
suffix:semicolon
DECL|member|resolution
id|byte
id|resolution
suffix:semicolon
DECL|member|data_format
id|byte
id|data_format
suffix:semicolon
DECL|member|pages_low
id|byte
id|pages_low
suffix:semicolon
DECL|member|pages_high
id|byte
id|pages_high
suffix:semicolon
DECL|member|operating_mode
id|byte
id|operating_mode
suffix:semicolon
DECL|member|control_bits_low
id|byte
id|control_bits_low
suffix:semicolon
DECL|member|control_bits_high
id|byte
id|control_bits_high
suffix:semicolon
DECL|member|feature_bits_low
id|byte
id|feature_bits_low
suffix:semicolon
DECL|member|feature_bits_high
id|byte
id|feature_bits_high
suffix:semicolon
DECL|member|recording_properties
id|byte
id|recording_properties
suffix:semicolon
DECL|member|universal_6
id|byte
id|universal_6
suffix:semicolon
DECL|member|universal_7
id|byte
id|universal_7
suffix:semicolon
DECL|member|station_id_len
id|byte
id|station_id_len
suffix:semicolon
DECL|member|head_line_len
id|byte
id|head_line_len
suffix:semicolon
DECL|member|station_id
id|byte
id|station_id
(braket
id|T30_MAX_STATION_ID_LENGTH
)braket
suffix:semicolon
multiline_comment|/* byte          head_line[];      */
multiline_comment|/* byte          sub_sep_length;   */
multiline_comment|/* byte          sub_sep_field[];  */
multiline_comment|/* byte          pwd_length;       */
multiline_comment|/* byte          pwd_field[];      */
multiline_comment|/* byte          nsf_info_length;   */
multiline_comment|/* byte          nsf_info_field[];  */
)brace
suffix:semicolon
DECL|macro|T30_RESOLUTION_R8_0385
mdefine_line|#define T30_RESOLUTION_R8_0385          0x00
DECL|macro|T30_RESOLUTION_R8_0770_OR_200
mdefine_line|#define T30_RESOLUTION_R8_0770_OR_200   0x01
DECL|macro|T30_RESOLUTION_R8_1540
mdefine_line|#define T30_RESOLUTION_R8_1540          0x02
DECL|macro|T30_RESOLUTION_R16_1540_OR_400
mdefine_line|#define T30_RESOLUTION_R16_1540_OR_400  0x04
DECL|macro|T30_RESOLUTION_R4_0385_OR_100
mdefine_line|#define T30_RESOLUTION_R4_0385_OR_100   0x08
DECL|macro|T30_RESOLUTION_300_300
mdefine_line|#define T30_RESOLUTION_300_300          0x10
DECL|macro|T30_RESOLUTION_INCH_BASED
mdefine_line|#define T30_RESOLUTION_INCH_BASED       0x40
DECL|macro|T30_RESOLUTION_METRIC_BASED
mdefine_line|#define T30_RESOLUTION_METRIC_BASED     0x80
DECL|macro|T30_RECORDING_WIDTH_ISO_A4
mdefine_line|#define T30_RECORDING_WIDTH_ISO_A4      0
DECL|macro|T30_RECORDING_WIDTH_ISO_B4
mdefine_line|#define T30_RECORDING_WIDTH_ISO_B4      1
DECL|macro|T30_RECORDING_WIDTH_ISO_A3
mdefine_line|#define T30_RECORDING_WIDTH_ISO_A3      2
DECL|macro|T30_RECORDING_WIDTH_COUNT
mdefine_line|#define T30_RECORDING_WIDTH_COUNT       3
DECL|macro|T30_RECORDING_LENGTH_ISO_A4
mdefine_line|#define T30_RECORDING_LENGTH_ISO_A4     0
DECL|macro|T30_RECORDING_LENGTH_ISO_B4
mdefine_line|#define T30_RECORDING_LENGTH_ISO_B4     1
DECL|macro|T30_RECORDING_LENGTH_UNLIMITED
mdefine_line|#define T30_RECORDING_LENGTH_UNLIMITED  2
DECL|macro|T30_RECORDING_LENGTH_COUNT
mdefine_line|#define T30_RECORDING_LENGTH_COUNT      3
DECL|macro|T30_MIN_SCANLINE_TIME_00_00_00
mdefine_line|#define T30_MIN_SCANLINE_TIME_00_00_00  0
DECL|macro|T30_MIN_SCANLINE_TIME_05_05_05
mdefine_line|#define T30_MIN_SCANLINE_TIME_05_05_05  1
DECL|macro|T30_MIN_SCANLINE_TIME_10_05_05
mdefine_line|#define T30_MIN_SCANLINE_TIME_10_05_05  2
DECL|macro|T30_MIN_SCANLINE_TIME_10_10_10
mdefine_line|#define T30_MIN_SCANLINE_TIME_10_10_10  3
DECL|macro|T30_MIN_SCANLINE_TIME_20_10_10
mdefine_line|#define T30_MIN_SCANLINE_TIME_20_10_10  4
DECL|macro|T30_MIN_SCANLINE_TIME_20_20_20
mdefine_line|#define T30_MIN_SCANLINE_TIME_20_20_20  5
DECL|macro|T30_MIN_SCANLINE_TIME_40_20_20
mdefine_line|#define T30_MIN_SCANLINE_TIME_40_20_20  6
DECL|macro|T30_MIN_SCANLINE_TIME_40_40_40
mdefine_line|#define T30_MIN_SCANLINE_TIME_40_40_40  7
DECL|macro|T30_MIN_SCANLINE_TIME_RES_8
mdefine_line|#define T30_MIN_SCANLINE_TIME_RES_8     8
DECL|macro|T30_MIN_SCANLINE_TIME_RES_9
mdefine_line|#define T30_MIN_SCANLINE_TIME_RES_9     9
DECL|macro|T30_MIN_SCANLINE_TIME_RES_10
mdefine_line|#define T30_MIN_SCANLINE_TIME_RES_10    10
DECL|macro|T30_MIN_SCANLINE_TIME_10_10_05
mdefine_line|#define T30_MIN_SCANLINE_TIME_10_10_05  11
DECL|macro|T30_MIN_SCANLINE_TIME_20_10_05
mdefine_line|#define T30_MIN_SCANLINE_TIME_20_10_05  12
DECL|macro|T30_MIN_SCANLINE_TIME_20_20_10
mdefine_line|#define T30_MIN_SCANLINE_TIME_20_20_10  13
DECL|macro|T30_MIN_SCANLINE_TIME_40_20_10
mdefine_line|#define T30_MIN_SCANLINE_TIME_40_20_10  14
DECL|macro|T30_MIN_SCANLINE_TIME_40_40_20
mdefine_line|#define T30_MIN_SCANLINE_TIME_40_40_20  15
DECL|macro|T30_MIN_SCANLINE_TIME_COUNT
mdefine_line|#define T30_MIN_SCANLINE_TIME_COUNT     16
DECL|macro|T30_DATA_FORMAT_SFF
mdefine_line|#define T30_DATA_FORMAT_SFF             0
DECL|macro|T30_DATA_FORMAT_ASCII
mdefine_line|#define T30_DATA_FORMAT_ASCII           1
DECL|macro|T30_DATA_FORMAT_NATIVE
mdefine_line|#define T30_DATA_FORMAT_NATIVE          2
DECL|macro|T30_DATA_FORMAT_COUNT
mdefine_line|#define T30_DATA_FORMAT_COUNT           3
DECL|macro|T30_OPERATING_MODE_STANDARD
mdefine_line|#define T30_OPERATING_MODE_STANDARD     0
DECL|macro|T30_OPERATING_MODE_CLASS2
mdefine_line|#define T30_OPERATING_MODE_CLASS2       1
DECL|macro|T30_OPERATING_MODE_CLASS1
mdefine_line|#define T30_OPERATING_MODE_CLASS1       2
DECL|macro|T30_OPERATING_MODE_CAPI
mdefine_line|#define T30_OPERATING_MODE_CAPI         3
DECL|macro|T30_OPERATING_MODE_CAPI_NEG
mdefine_line|#define T30_OPERATING_MODE_CAPI_NEG     4
DECL|macro|T30_OPERATING_MODE_COUNT
mdefine_line|#define T30_OPERATING_MODE_COUNT        5
multiline_comment|/* EDATA transmit messages */
DECL|macro|EDATA_T30_DIS
mdefine_line|#define EDATA_T30_DIS         0x01
DECL|macro|EDATA_T30_FTT
mdefine_line|#define EDATA_T30_FTT         0x02
DECL|macro|EDATA_T30_MCF
mdefine_line|#define EDATA_T30_MCF         0x03
DECL|macro|EDATA_T30_PARAMETERS
mdefine_line|#define EDATA_T30_PARAMETERS  0x04
multiline_comment|/* EDATA receive messages */
DECL|macro|EDATA_T30_DCS
mdefine_line|#define EDATA_T30_DCS         0x81
DECL|macro|EDATA_T30_TRAIN_OK
mdefine_line|#define EDATA_T30_TRAIN_OK    0x82
DECL|macro|EDATA_T30_EOP
mdefine_line|#define EDATA_T30_EOP         0x83
DECL|macro|EDATA_T30_MPS
mdefine_line|#define EDATA_T30_MPS         0x84
DECL|macro|EDATA_T30_EOM
mdefine_line|#define EDATA_T30_EOM         0x85
DECL|macro|EDATA_T30_DTC
mdefine_line|#define EDATA_T30_DTC         0x86
DECL|macro|EDATA_T30_PAGE_END
mdefine_line|#define EDATA_T30_PAGE_END    0x87   /* Indicates end of page data. Reserved, but not implemented ! */
DECL|macro|EDATA_T30_EOP_CAPI
mdefine_line|#define EDATA_T30_EOP_CAPI    0x88
DECL|macro|T30_SUCCESS
mdefine_line|#define T30_SUCCESS                        0
DECL|macro|T30_ERR_NO_DIS_RECEIVED
mdefine_line|#define T30_ERR_NO_DIS_RECEIVED            1
DECL|macro|T30_ERR_TIMEOUT_NO_RESPONSE
mdefine_line|#define T30_ERR_TIMEOUT_NO_RESPONSE        2
DECL|macro|T30_ERR_RETRY_NO_RESPONSE
mdefine_line|#define T30_ERR_RETRY_NO_RESPONSE          3
DECL|macro|T30_ERR_TOO_MANY_REPEATS
mdefine_line|#define T30_ERR_TOO_MANY_REPEATS           4
DECL|macro|T30_ERR_UNEXPECTED_MESSAGE
mdefine_line|#define T30_ERR_UNEXPECTED_MESSAGE         5
DECL|macro|T30_ERR_UNEXPECTED_DCN
mdefine_line|#define T30_ERR_UNEXPECTED_DCN             6
DECL|macro|T30_ERR_DTC_UNSUPPORTED
mdefine_line|#define T30_ERR_DTC_UNSUPPORTED            7
DECL|macro|T30_ERR_ALL_RATES_FAILED
mdefine_line|#define T30_ERR_ALL_RATES_FAILED           8
DECL|macro|T30_ERR_TOO_MANY_TRAINS
mdefine_line|#define T30_ERR_TOO_MANY_TRAINS            9
DECL|macro|T30_ERR_RECEIVE_CORRUPTED
mdefine_line|#define T30_ERR_RECEIVE_CORRUPTED          10
DECL|macro|T30_ERR_UNEXPECTED_DISC
mdefine_line|#define T30_ERR_UNEXPECTED_DISC            11
DECL|macro|T30_ERR_APPLICATION_DISC
mdefine_line|#define T30_ERR_APPLICATION_DISC           12
DECL|macro|T30_ERR_INCOMPATIBLE_DIS
mdefine_line|#define T30_ERR_INCOMPATIBLE_DIS           13
DECL|macro|T30_ERR_INCOMPATIBLE_DCS
mdefine_line|#define T30_ERR_INCOMPATIBLE_DCS           14
DECL|macro|T30_ERR_TIMEOUT_NO_COMMAND
mdefine_line|#define T30_ERR_TIMEOUT_NO_COMMAND         15
DECL|macro|T30_ERR_RETRY_NO_COMMAND
mdefine_line|#define T30_ERR_RETRY_NO_COMMAND           16
DECL|macro|T30_ERR_TIMEOUT_COMMAND_TOO_LONG
mdefine_line|#define T30_ERR_TIMEOUT_COMMAND_TOO_LONG   17
DECL|macro|T30_ERR_TIMEOUT_RESPONSE_TOO_LONG
mdefine_line|#define T30_ERR_TIMEOUT_RESPONSE_TOO_LONG  18
DECL|macro|T30_ERR_NOT_IDENTIFIED
mdefine_line|#define T30_ERR_NOT_IDENTIFIED             19
DECL|macro|T30_ERR_SUPERVISORY_TIMEOUT
mdefine_line|#define T30_ERR_SUPERVISORY_TIMEOUT        20
DECL|macro|T30_ERR_TOO_LONG_SCAN_LINE
mdefine_line|#define T30_ERR_TOO_LONG_SCAN_LINE         21
multiline_comment|/* #define T30_ERR_RETRY_NO_PAGE_AFTER_MPS    22 */
DECL|macro|T30_ERR_RETRY_NO_PAGE_RECEIVED
mdefine_line|#define T30_ERR_RETRY_NO_PAGE_RECEIVED     23
DECL|macro|T30_ERR_RETRY_NO_DCS_AFTER_FTT
mdefine_line|#define T30_ERR_RETRY_NO_DCS_AFTER_FTT     24
DECL|macro|T30_ERR_RETRY_NO_DCS_AFTER_EOM
mdefine_line|#define T30_ERR_RETRY_NO_DCS_AFTER_EOM     25
DECL|macro|T30_ERR_RETRY_NO_DCS_AFTER_MPS
mdefine_line|#define T30_ERR_RETRY_NO_DCS_AFTER_MPS     26
DECL|macro|T30_ERR_RETRY_NO_DCN_AFTER_MCF
mdefine_line|#define T30_ERR_RETRY_NO_DCN_AFTER_MCF     27
DECL|macro|T30_ERR_RETRY_NO_DCN_AFTER_RTN
mdefine_line|#define T30_ERR_RETRY_NO_DCN_AFTER_RTN     28
DECL|macro|T30_ERR_RETRY_NO_CFR
mdefine_line|#define T30_ERR_RETRY_NO_CFR               29
DECL|macro|T30_ERR_RETRY_NO_MCF_AFTER_EOP
mdefine_line|#define T30_ERR_RETRY_NO_MCF_AFTER_EOP     30
DECL|macro|T30_ERR_RETRY_NO_MCF_AFTER_EOM
mdefine_line|#define T30_ERR_RETRY_NO_MCF_AFTER_EOM     31
DECL|macro|T30_ERR_RETRY_NO_MCF_AFTER_MPS
mdefine_line|#define T30_ERR_RETRY_NO_MCF_AFTER_MPS     32
DECL|macro|T30_ERR_SUB_SEP_UNSUPPORTED
mdefine_line|#define T30_ERR_SUB_SEP_UNSUPPORTED        33
DECL|macro|T30_ERR_PWD_UNSUPPORTED
mdefine_line|#define T30_ERR_PWD_UNSUPPORTED            34
DECL|macro|T30_ERR_SUB_SEP_PWD_UNSUPPORTED
mdefine_line|#define T30_ERR_SUB_SEP_PWD_UNSUPPORTED    35
DECL|macro|T30_ERR_INVALID_COMMAND_FRAME
mdefine_line|#define T30_ERR_INVALID_COMMAND_FRAME      36
DECL|macro|T30_ERR_UNSUPPORTED_PAGE_CODING
mdefine_line|#define T30_ERR_UNSUPPORTED_PAGE_CODING    37
DECL|macro|T30_ERR_INVALID_PAGE_CODING
mdefine_line|#define T30_ERR_INVALID_PAGE_CODING        38
DECL|macro|T30_ERR_INCOMPATIBLE_PAGE_CONFIG
mdefine_line|#define T30_ERR_INCOMPATIBLE_PAGE_CONFIG   39
DECL|macro|T30_ERR_TIMEOUT_FROM_APPLICATION
mdefine_line|#define T30_ERR_TIMEOUT_FROM_APPLICATION   40
DECL|macro|T30_ERR_V34FAX_NO_REACTION_ON_MARK
mdefine_line|#define T30_ERR_V34FAX_NO_REACTION_ON_MARK 41
DECL|macro|T30_ERR_V34FAX_TRAINING_TIMEOUT
mdefine_line|#define T30_ERR_V34FAX_TRAINING_TIMEOUT    42
DECL|macro|T30_ERR_V34FAX_UNEXPECTED_V21
mdefine_line|#define T30_ERR_V34FAX_UNEXPECTED_V21      43
DECL|macro|T30_ERR_V34FAX_PRIMARY_CTS_ON
mdefine_line|#define T30_ERR_V34FAX_PRIMARY_CTS_ON      44
DECL|macro|T30_ERR_V34FAX_TURNAROUND_POLLING
mdefine_line|#define T30_ERR_V34FAX_TURNAROUND_POLLING  45
DECL|macro|T30_ERR_V34FAX_V8_INCOMPATIBILITY
mdefine_line|#define T30_ERR_V34FAX_V8_INCOMPATIBILITY  46
DECL|macro|T30_CONTROL_BIT_DISABLE_FINE
mdefine_line|#define T30_CONTROL_BIT_DISABLE_FINE       0x0001
DECL|macro|T30_CONTROL_BIT_ENABLE_ECM
mdefine_line|#define T30_CONTROL_BIT_ENABLE_ECM         0x0002
DECL|macro|T30_CONTROL_BIT_ECM_64_BYTES
mdefine_line|#define T30_CONTROL_BIT_ECM_64_BYTES       0x0004
DECL|macro|T30_CONTROL_BIT_ENABLE_2D_CODING
mdefine_line|#define T30_CONTROL_BIT_ENABLE_2D_CODING   0x0008
DECL|macro|T30_CONTROL_BIT_ENABLE_T6_CODING
mdefine_line|#define T30_CONTROL_BIT_ENABLE_T6_CODING   0x0010
DECL|macro|T30_CONTROL_BIT_ENABLE_UNCOMPR
mdefine_line|#define T30_CONTROL_BIT_ENABLE_UNCOMPR     0x0020
DECL|macro|T30_CONTROL_BIT_ACCEPT_POLLING
mdefine_line|#define T30_CONTROL_BIT_ACCEPT_POLLING     0x0040
DECL|macro|T30_CONTROL_BIT_REQUEST_POLLING
mdefine_line|#define T30_CONTROL_BIT_REQUEST_POLLING    0x0080
DECL|macro|T30_CONTROL_BIT_MORE_DOCUMENTS
mdefine_line|#define T30_CONTROL_BIT_MORE_DOCUMENTS     0x0100
DECL|macro|T30_CONTROL_BIT_ACCEPT_SUBADDRESS
mdefine_line|#define T30_CONTROL_BIT_ACCEPT_SUBADDRESS  0x0200
DECL|macro|T30_CONTROL_BIT_ACCEPT_SEL_POLLING
mdefine_line|#define T30_CONTROL_BIT_ACCEPT_SEL_POLLING 0x0400
DECL|macro|T30_CONTROL_BIT_ACCEPT_PASSWORD
mdefine_line|#define T30_CONTROL_BIT_ACCEPT_PASSWORD    0x0800
DECL|macro|T30_CONTROL_BIT_ENABLE_V34FAX
mdefine_line|#define T30_CONTROL_BIT_ENABLE_V34FAX      0x1000
DECL|macro|T30_CONTROL_BIT_EARLY_CONNECT
mdefine_line|#define T30_CONTROL_BIT_EARLY_CONNECT      0x2000
DECL|macro|T30_CONTROL_BIT_ALL_FEATURES
mdefine_line|#define T30_CONTROL_BIT_ALL_FEATURES  (T30_CONTROL_BIT_ENABLE_ECM | T30_CONTROL_BIT_ENABLE_2D_CODING |   T30_CONTROL_BIT_ENABLE_T6_CODING | T30_CONTROL_BIT_ENABLE_UNCOMPR |   T30_CONTROL_BIT_ENABLE_V34FAX)
DECL|macro|T30_FEATURE_BIT_FINE
mdefine_line|#define T30_FEATURE_BIT_FINE               0x0001
DECL|macro|T30_FEATURE_BIT_ECM
mdefine_line|#define T30_FEATURE_BIT_ECM                0x0002
DECL|macro|T30_FEATURE_BIT_ECM_64_BYTES
mdefine_line|#define T30_FEATURE_BIT_ECM_64_BYTES       0x0004
DECL|macro|T30_FEATURE_BIT_2D_CODING
mdefine_line|#define T30_FEATURE_BIT_2D_CODING          0x0008
DECL|macro|T30_FEATURE_BIT_T6_CODING
mdefine_line|#define T30_FEATURE_BIT_T6_CODING          0x0010
DECL|macro|T30_FEATURE_BIT_UNCOMPR_ENABLED
mdefine_line|#define T30_FEATURE_BIT_UNCOMPR_ENABLED    0x0020
DECL|macro|T30_FEATURE_BIT_POLLING
mdefine_line|#define T30_FEATURE_BIT_POLLING            0x0040
DECL|macro|T30_FEATURE_BIT_MORE_DOCUMENTS
mdefine_line|#define T30_FEATURE_BIT_MORE_DOCUMENTS     0x0100
DECL|macro|T30_FEATURE_BIT_V34FAX
mdefine_line|#define T30_FEATURE_BIT_V34FAX             0x1000
DECL|macro|T30_NSF_CONTROL_BIT_ENABLE_NSF
mdefine_line|#define T30_NSF_CONTROL_BIT_ENABLE_NSF     0x0001
DECL|macro|T30_NSF_CONTROL_BIT_RAW_INFO
mdefine_line|#define T30_NSF_CONTROL_BIT_RAW_INFO       0x0002
DECL|macro|T30_NSF_CONTROL_BIT_NEGOTIATE_IND
mdefine_line|#define T30_NSF_CONTROL_BIT_NEGOTIATE_IND  0x0004
DECL|macro|T30_NSF_CONTROL_BIT_NEGOTIATE_RESP
mdefine_line|#define T30_NSF_CONTROL_BIT_NEGOTIATE_RESP 0x0008
DECL|macro|T30_NSF_ELEMENT_NSF_FIF
mdefine_line|#define T30_NSF_ELEMENT_NSF_FIF            0x00
DECL|macro|T30_NSF_ELEMENT_NSC_FIF
mdefine_line|#define T30_NSF_ELEMENT_NSC_FIF            0x01
DECL|macro|T30_NSF_ELEMENT_NSS_FIF
mdefine_line|#define T30_NSF_ELEMENT_NSS_FIF            0x02
DECL|macro|T30_NSF_ELEMENT_COMPANY_NAME
mdefine_line|#define T30_NSF_ELEMENT_COMPANY_NAME       0x03
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Analog modem definitions                                         */
multiline_comment|/*------------------------------------------------------------------*/
DECL|typedef|ASYNC_FORMAT
r_typedef
r_struct
id|async_s
id|ASYNC_FORMAT
suffix:semicolon
DECL|struct|async_s
r_struct
id|async_s
(brace
DECL|member|pe
r_int
id|pe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|parity
r_int
id|parity
suffix:colon
l_int|2
suffix:semicolon
DECL|member|spare
r_int
id|spare
suffix:colon
l_int|2
suffix:semicolon
DECL|member|stp
r_int
id|stp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ch_len
r_int
id|ch_len
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// 3th octett in CAI
)brace
suffix:semicolon
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* PLCI/NCCI states                                                 */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|IDLE
mdefine_line|#define IDLE                    0
DECL|macro|OUTG_CON_PENDING
mdefine_line|#define OUTG_CON_PENDING        1
DECL|macro|INC_CON_PENDING
mdefine_line|#define INC_CON_PENDING         2
DECL|macro|INC_CON_ALERT
mdefine_line|#define INC_CON_ALERT           3
DECL|macro|INC_CON_ACCEPT
mdefine_line|#define INC_CON_ACCEPT          4
DECL|macro|INC_ACT_PENDING
mdefine_line|#define INC_ACT_PENDING         5
DECL|macro|LISTENING
mdefine_line|#define LISTENING               6
DECL|macro|CONNECTED
mdefine_line|#define CONNECTED               7
DECL|macro|OUTG_DIS_PENDING
mdefine_line|#define OUTG_DIS_PENDING        8
DECL|macro|INC_DIS_PENDING
mdefine_line|#define INC_DIS_PENDING         9
DECL|macro|LOCAL_CONNECT
mdefine_line|#define LOCAL_CONNECT           10
DECL|macro|INC_RES_PENDING
mdefine_line|#define INC_RES_PENDING         11
DECL|macro|OUTG_RES_PENDING
mdefine_line|#define OUTG_RES_PENDING        12
DECL|macro|SUSPENDING
mdefine_line|#define SUSPENDING              13
DECL|macro|ADVANCED_VOICE_SIG
mdefine_line|#define ADVANCED_VOICE_SIG      14
DECL|macro|ADVANCED_VOICE_NOSIG
mdefine_line|#define ADVANCED_VOICE_NOSIG    15
DECL|macro|RESUMING
mdefine_line|#define RESUMING                16
DECL|macro|INC_CON_CONNECTED_ALERT
mdefine_line|#define INC_CON_CONNECTED_ALERT 17
DECL|macro|OUTG_REJ_PENDING
mdefine_line|#define OUTG_REJ_PENDING        18
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* auxilliary states for supplementary services                     */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|IDLE
mdefine_line|#define IDLE                0
DECL|macro|HOLD_REQUEST
mdefine_line|#define HOLD_REQUEST        1
DECL|macro|HOLD_INDICATE
mdefine_line|#define HOLD_INDICATE       2
DECL|macro|CALL_HELD
mdefine_line|#define CALL_HELD           3
DECL|macro|RETRIEVE_REQUEST
mdefine_line|#define RETRIEVE_REQUEST    4
DECL|macro|RETRIEVE_INDICATION
mdefine_line|#define RETRIEVE_INDICATION 5
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Capi IE + Msg types                                              */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ESC_CAUSE
mdefine_line|#define ESC_CAUSE        0x800|CAU          /* Escape cause element */
DECL|macro|ESC_MSGTYPE
mdefine_line|#define ESC_MSGTYPE      0x800|MSGTYPEIE    /* Escape message type  */
DECL|macro|ESC_CHI
mdefine_line|#define ESC_CHI          0x800|CHI          /* Escape channel id    */
DECL|macro|ESC_LAW
mdefine_line|#define ESC_LAW          0x800|BC           /* Escape law info      */
DECL|macro|ESC_CR
mdefine_line|#define ESC_CR           0x800|CRIE         /* Escape CallReference */
DECL|macro|ESC_PROFILE
mdefine_line|#define ESC_PROFILE      0x800|PROFILEIE    /* Escape profile       */
DECL|macro|ESC_SSEXT
mdefine_line|#define ESC_SSEXT        0x800|SSEXTIE      /* Escape Supplem. Serv.*/
DECL|macro|ESC_VSWITCH
mdefine_line|#define ESC_VSWITCH      0x800|VSWITCHIE    /* Escape VSwitch       */
DECL|macro|CST
mdefine_line|#define CST              0x14               /* Call State i.e.      */
DECL|macro|PI
mdefine_line|#define PI               0x1E               /* Progress Indicator   */
DECL|macro|NI
mdefine_line|#define NI               0x27               /* Notification Ind     */
DECL|macro|CONN_NR
mdefine_line|#define CONN_NR          0x4C               /* Connected Number     */
DECL|macro|CONG_RNR
mdefine_line|#define CONG_RNR         0xBF               /* Congestion RNR       */
DECL|macro|CONG_RR
mdefine_line|#define CONG_RR          0xB0               /* Congestion RR        */
DECL|macro|RESERVED
mdefine_line|#define RESERVED         0xFF               /* Res. for future use  */
DECL|macro|ON_BOARD_CODEC
mdefine_line|#define ON_BOARD_CODEC   0x02               /* external controller  */
DECL|macro|HANDSET
mdefine_line|#define HANDSET          0x04               /* Codec+Handset(Pro11) */
DECL|macro|HOOK_SUPPORT
mdefine_line|#define HOOK_SUPPORT     0x01               /* activate Hook signal */
DECL|macro|SCR
mdefine_line|#define SCR              0x7a               /* unscreened number    */
DECL|macro|HOOK_OFF_REQ
mdefine_line|#define HOOK_OFF_REQ     0x9001             /* internal conn req    */
DECL|macro|HOOK_ON_REQ
mdefine_line|#define HOOK_ON_REQ      0x9002             /* internal disc req    */
DECL|macro|SUSPEND_REQ
mdefine_line|#define SUSPEND_REQ      0x9003             /* internal susp req    */
DECL|macro|RESUME_REQ
mdefine_line|#define RESUME_REQ       0x9004             /* internal resume req  */
DECL|macro|USELAW_REQ
mdefine_line|#define USELAW_REQ       0x9005             /* internal law    req  */
DECL|macro|LISTEN_SIG_ASSIGN_PEND
mdefine_line|#define LISTEN_SIG_ASSIGN_PEND  0x9006
DECL|macro|PERM_LIST_REQ
mdefine_line|#define PERM_LIST_REQ    0x900a             /* permanent conn DCE   */
DECL|macro|C_HOLD_REQ
mdefine_line|#define C_HOLD_REQ       0x9011
DECL|macro|C_RETRIEVE_REQ
mdefine_line|#define C_RETRIEVE_REQ   0x9012
DECL|macro|C_NCR_FAC_REQ
mdefine_line|#define C_NCR_FAC_REQ    0x9013
DECL|macro|PERM_COD_ASSIGN
mdefine_line|#define PERM_COD_ASSIGN  0x9014
DECL|macro|PERM_COD_CALL
mdefine_line|#define PERM_COD_CALL    0x9015
DECL|macro|PERM_COD_HOOK
mdefine_line|#define PERM_COD_HOOK    0x9016
DECL|macro|PERM_COD_CONN_PEND
mdefine_line|#define PERM_COD_CONN_PEND 0x9017           /* wait for connect_con */
DECL|macro|PTY_REQ_PEND
mdefine_line|#define PTY_REQ_PEND     0x9018
DECL|macro|CD_REQ_PEND
mdefine_line|#define CD_REQ_PEND      0x9019
DECL|macro|CF_START_PEND
mdefine_line|#define CF_START_PEND    0x901a
DECL|macro|CF_STOP_PEND
mdefine_line|#define CF_STOP_PEND     0x901b
DECL|macro|ECT_REQ_PEND
mdefine_line|#define ECT_REQ_PEND     0x901c
DECL|macro|GETSERV_REQ_PEND
mdefine_line|#define GETSERV_REQ_PEND 0x901d
DECL|macro|BLOCK_PLCI
mdefine_line|#define BLOCK_PLCI       0x901e
DECL|macro|INTERR_NUMBERS_REQ_PEND
mdefine_line|#define INTERR_NUMBERS_REQ_PEND         0x901f
DECL|macro|INTERR_DIVERSION_REQ_PEND
mdefine_line|#define INTERR_DIVERSION_REQ_PEND       0x9020
DECL|macro|MWI_ACTIVATE_REQ_PEND
mdefine_line|#define MWI_ACTIVATE_REQ_PEND           0x9021
DECL|macro|MWI_DEACTIVATE_REQ_PEND
mdefine_line|#define MWI_DEACTIVATE_REQ_PEND         0x9022
DECL|macro|SSEXT_REQ_COMMAND
mdefine_line|#define SSEXT_REQ_COMMAND               0x9023
DECL|macro|SSEXT_NC_REQ_COMMAND
mdefine_line|#define SSEXT_NC_REQ_COMMAND            0x9024
DECL|macro|START_L1_SIG_ASSIGN_PEND
mdefine_line|#define START_L1_SIG_ASSIGN_PEND        0x9025
DECL|macro|REM_L1_SIG_ASSIGN_PEND
mdefine_line|#define REM_L1_SIG_ASSIGN_PEND          0x9026
DECL|macro|CONF_BEGIN_REQ_PEND
mdefine_line|#define CONF_BEGIN_REQ_PEND             0x9027
DECL|macro|CONF_ADD_REQ_PEND
mdefine_line|#define CONF_ADD_REQ_PEND               0x9028
DECL|macro|CONF_SPLIT_REQ_PEND
mdefine_line|#define CONF_SPLIT_REQ_PEND             0x9029
DECL|macro|CONF_DROP_REQ_PEND
mdefine_line|#define CONF_DROP_REQ_PEND              0x902a
DECL|macro|CONF_ISOLATE_REQ_PEND
mdefine_line|#define CONF_ISOLATE_REQ_PEND           0x902b
DECL|macro|CONF_REATTACH_REQ_PEND
mdefine_line|#define CONF_REATTACH_REQ_PEND          0x902c
DECL|macro|VSWITCH_REQ_PEND
mdefine_line|#define VSWITCH_REQ_PEND                0x902d
DECL|macro|GET_MWI_STATE
mdefine_line|#define GET_MWI_STATE                   0x902e
DECL|macro|CCBS_REQUEST_REQ_PEND
mdefine_line|#define CCBS_REQUEST_REQ_PEND           0x902f
DECL|macro|CCBS_DEACTIVATE_REQ_PEND
mdefine_line|#define CCBS_DEACTIVATE_REQ_PEND        0x9030
DECL|macro|CCBS_INTERROGATE_REQ_PEND
mdefine_line|#define CCBS_INTERROGATE_REQ_PEND       0x9031
DECL|macro|NO_INTERNAL_COMMAND
mdefine_line|#define NO_INTERNAL_COMMAND             0
DECL|macro|DTMF_COMMAND_1
mdefine_line|#define DTMF_COMMAND_1                  1
DECL|macro|DTMF_COMMAND_2
mdefine_line|#define DTMF_COMMAND_2                  2
DECL|macro|DTMF_COMMAND_3
mdefine_line|#define DTMF_COMMAND_3                  3
DECL|macro|MIXER_COMMAND_1
mdefine_line|#define MIXER_COMMAND_1                 4
DECL|macro|MIXER_COMMAND_2
mdefine_line|#define MIXER_COMMAND_2                 5
DECL|macro|MIXER_COMMAND_3
mdefine_line|#define MIXER_COMMAND_3                 6
DECL|macro|ADV_VOICE_COMMAND_CONNECT_1
mdefine_line|#define ADV_VOICE_COMMAND_CONNECT_1     7
DECL|macro|ADV_VOICE_COMMAND_CONNECT_2
mdefine_line|#define ADV_VOICE_COMMAND_CONNECT_2     8
DECL|macro|ADV_VOICE_COMMAND_CONNECT_3
mdefine_line|#define ADV_VOICE_COMMAND_CONNECT_3     9
DECL|macro|ADV_VOICE_COMMAND_DISCONNECT_1
mdefine_line|#define ADV_VOICE_COMMAND_DISCONNECT_1  10
DECL|macro|ADV_VOICE_COMMAND_DISCONNECT_2
mdefine_line|#define ADV_VOICE_COMMAND_DISCONNECT_2  11
DECL|macro|ADV_VOICE_COMMAND_DISCONNECT_3
mdefine_line|#define ADV_VOICE_COMMAND_DISCONNECT_3  12
DECL|macro|ADJUST_B_RESTORE_1
mdefine_line|#define ADJUST_B_RESTORE_1              13
DECL|macro|ADJUST_B_RESTORE_2
mdefine_line|#define ADJUST_B_RESTORE_2              14
DECL|macro|RESET_B3_COMMAND_1
mdefine_line|#define RESET_B3_COMMAND_1              15
DECL|macro|SELECT_B_COMMAND_1
mdefine_line|#define SELECT_B_COMMAND_1              16
DECL|macro|FAX_CONNECT_INFO_COMMAND_1
mdefine_line|#define FAX_CONNECT_INFO_COMMAND_1      17
DECL|macro|FAX_CONNECT_INFO_COMMAND_2
mdefine_line|#define FAX_CONNECT_INFO_COMMAND_2      18
DECL|macro|FAX_ADJUST_B23_COMMAND_1
mdefine_line|#define FAX_ADJUST_B23_COMMAND_1        19
DECL|macro|FAX_ADJUST_B23_COMMAND_2
mdefine_line|#define FAX_ADJUST_B23_COMMAND_2        20
DECL|macro|EC_COMMAND_1
mdefine_line|#define EC_COMMAND_1                    21
DECL|macro|EC_COMMAND_2
mdefine_line|#define EC_COMMAND_2                    22
DECL|macro|EC_COMMAND_3
mdefine_line|#define EC_COMMAND_3                    23
DECL|macro|RTP_CONNECT_B3_REQ_COMMAND_1
mdefine_line|#define RTP_CONNECT_B3_REQ_COMMAND_1    24
DECL|macro|RTP_CONNECT_B3_REQ_COMMAND_2
mdefine_line|#define RTP_CONNECT_B3_REQ_COMMAND_2    25
DECL|macro|RTP_CONNECT_B3_REQ_COMMAND_3
mdefine_line|#define RTP_CONNECT_B3_REQ_COMMAND_3    26
DECL|macro|RTP_CONNECT_B3_RES_COMMAND_1
mdefine_line|#define RTP_CONNECT_B3_RES_COMMAND_1    27
DECL|macro|RTP_CONNECT_B3_RES_COMMAND_2
mdefine_line|#define RTP_CONNECT_B3_RES_COMMAND_2    28
DECL|macro|RTP_CONNECT_B3_RES_COMMAND_3
mdefine_line|#define RTP_CONNECT_B3_RES_COMMAND_3    29
DECL|macro|HOLD_SAVE_COMMAND_1
mdefine_line|#define HOLD_SAVE_COMMAND_1             30
DECL|macro|RETRIEVE_RESTORE_COMMAND_1
mdefine_line|#define RETRIEVE_RESTORE_COMMAND_1      31
DECL|macro|FAX_DISCONNECT_COMMAND_1
mdefine_line|#define FAX_DISCONNECT_COMMAND_1        32
DECL|macro|FAX_DISCONNECT_COMMAND_2
mdefine_line|#define FAX_DISCONNECT_COMMAND_2        33
DECL|macro|FAX_DISCONNECT_COMMAND_3
mdefine_line|#define FAX_DISCONNECT_COMMAND_3        34
DECL|macro|FAX_EDATA_ACK_COMMAND_1
mdefine_line|#define FAX_EDATA_ACK_COMMAND_1         35
DECL|macro|FAX_EDATA_ACK_COMMAND_2
mdefine_line|#define FAX_EDATA_ACK_COMMAND_2         36
DECL|macro|FAX_CONNECT_ACK_COMMAND_1
mdefine_line|#define FAX_CONNECT_ACK_COMMAND_1       37
DECL|macro|FAX_CONNECT_ACK_COMMAND_2
mdefine_line|#define FAX_CONNECT_ACK_COMMAND_2       38
DECL|macro|STD_INTERNAL_COMMAND_COUNT
mdefine_line|#define STD_INTERNAL_COMMAND_COUNT      39
DECL|macro|UID
mdefine_line|#define UID              0x2d               /* User Id for Mgmt      */
DECL|macro|CALL_DIR_OUT
mdefine_line|#define CALL_DIR_OUT             0x01       /* call direction of initial call */
DECL|macro|CALL_DIR_IN
mdefine_line|#define CALL_DIR_IN              0x02
DECL|macro|CALL_DIR_ORIGINATE
mdefine_line|#define CALL_DIR_ORIGINATE       0x04       /* DTE/DCE direction according to */
DECL|macro|CALL_DIR_ANSWER
mdefine_line|#define CALL_DIR_ANSWER          0x08       /*   state of B-Channel Operation */
DECL|macro|CALL_DIR_FORCE_OUTG_NL
mdefine_line|#define CALL_DIR_FORCE_OUTG_NL   0x10       /* for RESET_B3 reconnect, after DISC_B3... */
DECL|macro|AWAITING_MANUF_CON
mdefine_line|#define AWAITING_MANUF_CON 0x80             /* command spoofing flags */
DECL|macro|SPOOFING_REQUIRED
mdefine_line|#define SPOOFING_REQUIRED  0xff
DECL|macro|AWAITING_SELECT_B
mdefine_line|#define AWAITING_SELECT_B  0xef
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* B_CTRL / DSP_CTRL                                                */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|DSP_CTRL_OLD_SET_MIXER_COEFFICIENTS
mdefine_line|#define DSP_CTRL_OLD_SET_MIXER_COEFFICIENTS     0x01
DECL|macro|DSP_CTRL_SET_BCHANNEL_PASSIVATION_BRI
mdefine_line|#define DSP_CTRL_SET_BCHANNEL_PASSIVATION_BRI   0x02
DECL|macro|DSP_CTRL_SET_DTMF_PARAMETERS
mdefine_line|#define DSP_CTRL_SET_DTMF_PARAMETERS            0x03
DECL|macro|MANUFACTURER_FEATURE_SLAVE_CODEC
mdefine_line|#define MANUFACTURER_FEATURE_SLAVE_CODEC          0x00000001L
DECL|macro|MANUFACTURER_FEATURE_FAX_MORE_DOCUMENTS
mdefine_line|#define MANUFACTURER_FEATURE_FAX_MORE_DOCUMENTS   0x00000002L
DECL|macro|MANUFACTURER_FEATURE_HARDDTMF
mdefine_line|#define MANUFACTURER_FEATURE_HARDDTMF             0x00000004L
DECL|macro|MANUFACTURER_FEATURE_SOFTDTMF_SEND
mdefine_line|#define MANUFACTURER_FEATURE_SOFTDTMF_SEND        0x00000008L
DECL|macro|MANUFACTURER_FEATURE_DTMF_PARAMETERS
mdefine_line|#define MANUFACTURER_FEATURE_DTMF_PARAMETERS      0x00000010L
DECL|macro|MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE
mdefine_line|#define MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE     0x00000020L
DECL|macro|MANUFACTURER_FEATURE_FAX_SUB_SEP_PWD
mdefine_line|#define MANUFACTURER_FEATURE_FAX_SUB_SEP_PWD      0x00000040L
DECL|macro|MANUFACTURER_FEATURE_V18
mdefine_line|#define MANUFACTURER_FEATURE_V18                  0x00000080L
DECL|macro|MANUFACTURER_FEATURE_MIXER_CH_CH
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_CH_CH          0x00000100L
DECL|macro|MANUFACTURER_FEATURE_MIXER_CH_PC
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_CH_PC          0x00000200L
DECL|macro|MANUFACTURER_FEATURE_MIXER_PC_CH
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_PC_CH          0x00000400L
DECL|macro|MANUFACTURER_FEATURE_MIXER_PC_PC
mdefine_line|#define MANUFACTURER_FEATURE_MIXER_PC_PC          0x00000800L
DECL|macro|MANUFACTURER_FEATURE_ECHO_CANCELLER
mdefine_line|#define MANUFACTURER_FEATURE_ECHO_CANCELLER       0x00001000L
DECL|macro|MANUFACTURER_FEATURE_RTP
mdefine_line|#define MANUFACTURER_FEATURE_RTP                  0x00002000L
DECL|macro|MANUFACTURER_FEATURE_T38
mdefine_line|#define MANUFACTURER_FEATURE_T38                  0x00004000L
DECL|macro|MANUFACTURER_FEATURE_TRANSP_DELIVERY_CONF
mdefine_line|#define MANUFACTURER_FEATURE_TRANSP_DELIVERY_CONF 0x00008000L
DECL|macro|MANUFACTURER_FEATURE_XONOFF_FLOW_CONTROL
mdefine_line|#define MANUFACTURER_FEATURE_XONOFF_FLOW_CONTROL  0x00010000L
DECL|macro|MANUFACTURER_FEATURE_OOB_CHANNEL
mdefine_line|#define MANUFACTURER_FEATURE_OOB_CHANNEL          0x00020000L
DECL|macro|MANUFACTURER_FEATURE_IN_BAND_CHANNEL
mdefine_line|#define MANUFACTURER_FEATURE_IN_BAND_CHANNEL      0x00040000L
DECL|macro|MANUFACTURER_FEATURE_IN_BAND_FEATURE
mdefine_line|#define MANUFACTURER_FEATURE_IN_BAND_FEATURE      0x00080000L
DECL|macro|MANUFACTURER_FEATURE_PIAFS
mdefine_line|#define MANUFACTURER_FEATURE_PIAFS                0x00100000L
DECL|macro|MANUFACTURER_FEATURE_DTMF_TONE
mdefine_line|#define MANUFACTURER_FEATURE_DTMF_TONE            0x00200000L
DECL|macro|MANUFACTURER_FEATURE_FAX_PAPER_FORMATS
mdefine_line|#define MANUFACTURER_FEATURE_FAX_PAPER_FORMATS    0x00400000L
DECL|macro|MANUFACTURER_FEATURE_OK_FC_LABEL
mdefine_line|#define MANUFACTURER_FEATURE_OK_FC_LABEL          0x00800000L
DECL|macro|MANUFACTURER_FEATURE_VOWN
mdefine_line|#define MANUFACTURER_FEATURE_VOWN                 0x01000000L
DECL|macro|MANUFACTURER_FEATURE_XCONNECT
mdefine_line|#define MANUFACTURER_FEATURE_XCONNECT             0x02000000L
DECL|macro|MANUFACTURER_FEATURE_DMACONNECT
mdefine_line|#define MANUFACTURER_FEATURE_DMACONNECT           0x04000000L
DECL|macro|MANUFACTURER_FEATURE_AUDIO_TAP
mdefine_line|#define MANUFACTURER_FEATURE_AUDIO_TAP            0x08000000L
DECL|macro|MANUFACTURER_FEATURE_FAX_NONSTANDARD
mdefine_line|#define MANUFACTURER_FEATURE_FAX_NONSTANDARD      0x10000000L
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* DTMF interface to IDI                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|DTMF_DIGIT_TONE_LOW_GROUP_697_HZ
mdefine_line|#define DTMF_DIGIT_TONE_LOW_GROUP_697_HZ        0x00
DECL|macro|DTMF_DIGIT_TONE_LOW_GROUP_770_HZ
mdefine_line|#define DTMF_DIGIT_TONE_LOW_GROUP_770_HZ        0x01
DECL|macro|DTMF_DIGIT_TONE_LOW_GROUP_852_HZ
mdefine_line|#define DTMF_DIGIT_TONE_LOW_GROUP_852_HZ        0x02
DECL|macro|DTMF_DIGIT_TONE_LOW_GROUP_941_HZ
mdefine_line|#define DTMF_DIGIT_TONE_LOW_GROUP_941_HZ        0x03
DECL|macro|DTMF_DIGIT_TONE_LOW_GROUP_MASK
mdefine_line|#define DTMF_DIGIT_TONE_LOW_GROUP_MASK          0x03
DECL|macro|DTMF_DIGIT_TONE_HIGH_GROUP_1209_HZ
mdefine_line|#define DTMF_DIGIT_TONE_HIGH_GROUP_1209_HZ      0x00
DECL|macro|DTMF_DIGIT_TONE_HIGH_GROUP_1336_HZ
mdefine_line|#define DTMF_DIGIT_TONE_HIGH_GROUP_1336_HZ      0x04
DECL|macro|DTMF_DIGIT_TONE_HIGH_GROUP_1477_HZ
mdefine_line|#define DTMF_DIGIT_TONE_HIGH_GROUP_1477_HZ      0x08
DECL|macro|DTMF_DIGIT_TONE_HIGH_GROUP_1633_HZ
mdefine_line|#define DTMF_DIGIT_TONE_HIGH_GROUP_1633_HZ      0x0c
DECL|macro|DTMF_DIGIT_TONE_HIGH_GROUP_MASK
mdefine_line|#define DTMF_DIGIT_TONE_HIGH_GROUP_MASK         0x0c
DECL|macro|DTMF_DIGIT_TONE_CODE_0
mdefine_line|#define DTMF_DIGIT_TONE_CODE_0                  0x07
DECL|macro|DTMF_DIGIT_TONE_CODE_1
mdefine_line|#define DTMF_DIGIT_TONE_CODE_1                  0x00
DECL|macro|DTMF_DIGIT_TONE_CODE_2
mdefine_line|#define DTMF_DIGIT_TONE_CODE_2                  0x04
DECL|macro|DTMF_DIGIT_TONE_CODE_3
mdefine_line|#define DTMF_DIGIT_TONE_CODE_3                  0x08
DECL|macro|DTMF_DIGIT_TONE_CODE_4
mdefine_line|#define DTMF_DIGIT_TONE_CODE_4                  0x01
DECL|macro|DTMF_DIGIT_TONE_CODE_5
mdefine_line|#define DTMF_DIGIT_TONE_CODE_5                  0x05
DECL|macro|DTMF_DIGIT_TONE_CODE_6
mdefine_line|#define DTMF_DIGIT_TONE_CODE_6                  0x09
DECL|macro|DTMF_DIGIT_TONE_CODE_7
mdefine_line|#define DTMF_DIGIT_TONE_CODE_7                  0x02
DECL|macro|DTMF_DIGIT_TONE_CODE_8
mdefine_line|#define DTMF_DIGIT_TONE_CODE_8                  0x06
DECL|macro|DTMF_DIGIT_TONE_CODE_9
mdefine_line|#define DTMF_DIGIT_TONE_CODE_9                  0x0a
DECL|macro|DTMF_DIGIT_TONE_CODE_STAR
mdefine_line|#define DTMF_DIGIT_TONE_CODE_STAR               0x03
DECL|macro|DTMF_DIGIT_TONE_CODE_HASHMARK
mdefine_line|#define DTMF_DIGIT_TONE_CODE_HASHMARK           0x0b
DECL|macro|DTMF_DIGIT_TONE_CODE_A
mdefine_line|#define DTMF_DIGIT_TONE_CODE_A                  0x0c
DECL|macro|DTMF_DIGIT_TONE_CODE_B
mdefine_line|#define DTMF_DIGIT_TONE_CODE_B                  0x0d
DECL|macro|DTMF_DIGIT_TONE_CODE_C
mdefine_line|#define DTMF_DIGIT_TONE_CODE_C                  0x0e
DECL|macro|DTMF_DIGIT_TONE_CODE_D
mdefine_line|#define DTMF_DIGIT_TONE_CODE_D                  0x0f
DECL|macro|DTMF_UDATA_REQUEST_SEND_DIGITS
mdefine_line|#define DTMF_UDATA_REQUEST_SEND_DIGITS            16
DECL|macro|DTMF_UDATA_REQUEST_ENABLE_RECEIVER
mdefine_line|#define DTMF_UDATA_REQUEST_ENABLE_RECEIVER        17
DECL|macro|DTMF_UDATA_REQUEST_DISABLE_RECEIVER
mdefine_line|#define DTMF_UDATA_REQUEST_DISABLE_RECEIVER       18
DECL|macro|DTMF_UDATA_INDICATION_DIGITS_SENT
mdefine_line|#define DTMF_UDATA_INDICATION_DIGITS_SENT         16
DECL|macro|DTMF_UDATA_INDICATION_DIGITS_RECEIVED
mdefine_line|#define DTMF_UDATA_INDICATION_DIGITS_RECEIVED     17
DECL|macro|DTMF_UDATA_INDICATION_MODEM_CALLING_TONE
mdefine_line|#define DTMF_UDATA_INDICATION_MODEM_CALLING_TONE  18
DECL|macro|DTMF_UDATA_INDICATION_FAX_CALLING_TONE
mdefine_line|#define DTMF_UDATA_INDICATION_FAX_CALLING_TONE    19
DECL|macro|DTMF_UDATA_INDICATION_ANSWER_TONE
mdefine_line|#define DTMF_UDATA_INDICATION_ANSWER_TONE         20
DECL|macro|UDATA_REQUEST_MIXER_TAP_DATA
mdefine_line|#define UDATA_REQUEST_MIXER_TAP_DATA        27
DECL|macro|UDATA_INDICATION_MIXER_TAP_DATA
mdefine_line|#define UDATA_INDICATION_MIXER_TAP_DATA     27
DECL|macro|DTMF_LISTEN_ACTIVE_FLAG
mdefine_line|#define DTMF_LISTEN_ACTIVE_FLAG        0x01
DECL|macro|DTMF_SEND_DIGIT_FLAG
mdefine_line|#define DTMF_SEND_DIGIT_FLAG           0x01
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Mixer interface to IDI                                           */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|LI2_FLAG_PCCONNECT_A_B
mdefine_line|#define LI2_FLAG_PCCONNECT_A_B 0x40000000
DECL|macro|LI2_FLAG_PCCONNECT_B_A
mdefine_line|#define LI2_FLAG_PCCONNECT_B_A 0x80000000
DECL|macro|MIXER_BCHANNELS_BRI
mdefine_line|#define MIXER_BCHANNELS_BRI    2
DECL|macro|MIXER_IC_CHANNELS_BRI
mdefine_line|#define MIXER_IC_CHANNELS_BRI  MIXER_BCHANNELS_BRI
DECL|macro|MIXER_IC_CHANNEL_BASE
mdefine_line|#define MIXER_IC_CHANNEL_BASE  MIXER_BCHANNELS_BRI
DECL|macro|MIXER_CHANNELS_BRI
mdefine_line|#define MIXER_CHANNELS_BRI     (MIXER_BCHANNELS_BRI + MIXER_IC_CHANNELS_BRI)
DECL|macro|MIXER_CHANNELS_PRI
mdefine_line|#define MIXER_CHANNELS_PRI     32
DECL|typedef|LI_CONFIG
r_typedef
r_struct
id|li_config_s
id|LI_CONFIG
suffix:semicolon
DECL|struct|xconnect_card_address_s
r_struct
id|xconnect_card_address_s
(brace
DECL|member|low
id|dword
id|low
suffix:semicolon
DECL|member|high
id|dword
id|high
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xconnect_transfer_address_s
r_struct
id|xconnect_transfer_address_s
(brace
DECL|member|card_address
r_struct
id|xconnect_card_address_s
id|card_address
suffix:semicolon
DECL|member|offset
id|dword
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|li_config_s
r_struct
id|li_config_s
(brace
DECL|member|adapter
id|DIVA_CAPI_ADAPTER
op_star
id|adapter
suffix:semicolon
DECL|member|plci
id|PLCI
op_star
id|plci
suffix:semicolon
DECL|member|send_b
r_struct
id|xconnect_transfer_address_s
id|send_b
suffix:semicolon
DECL|member|send_pc
r_struct
id|xconnect_transfer_address_s
id|send_pc
suffix:semicolon
DECL|member|flag_table
id|byte
op_star
id|flag_table
suffix:semicolon
multiline_comment|/* dword aligned and sized */
DECL|member|coef_table
id|byte
op_star
id|coef_table
suffix:semicolon
multiline_comment|/* dword aligned and sized */
DECL|member|channel
id|byte
id|channel
suffix:semicolon
DECL|member|curchnl
id|byte
id|curchnl
suffix:semicolon
DECL|member|chflags
id|byte
id|chflags
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|LI_CONFIG
op_star
id|li_config_table
suffix:semicolon
r_extern
id|word
id|li_total_channels
suffix:semicolon
DECL|macro|LI_CHANNEL_INVOLVED
mdefine_line|#define LI_CHANNEL_INVOLVED        0x01
DECL|macro|LI_CHANNEL_ACTIVE
mdefine_line|#define LI_CHANNEL_ACTIVE          0x02
DECL|macro|LI_CHANNEL_TX_DATA
mdefine_line|#define LI_CHANNEL_TX_DATA         0x04
DECL|macro|LI_CHANNEL_RX_DATA
mdefine_line|#define LI_CHANNEL_RX_DATA         0x08
DECL|macro|LI_CHANNEL_CONFERENCE
mdefine_line|#define LI_CHANNEL_CONFERENCE      0x10
DECL|macro|LI_CHANNEL_ADDRESSES_SET
mdefine_line|#define LI_CHANNEL_ADDRESSES_SET   0x80
DECL|macro|LI_CHFLAG_MONITOR
mdefine_line|#define LI_CHFLAG_MONITOR          0x01
DECL|macro|LI_CHFLAG_MIX
mdefine_line|#define LI_CHFLAG_MIX              0x02
DECL|macro|LI_CHFLAG_LOOP
mdefine_line|#define LI_CHFLAG_LOOP             0x04
DECL|macro|LI_FLAG_INTERCONNECT
mdefine_line|#define LI_FLAG_INTERCONNECT       0x01
DECL|macro|LI_FLAG_MONITOR
mdefine_line|#define LI_FLAG_MONITOR            0x02
DECL|macro|LI_FLAG_MIX
mdefine_line|#define LI_FLAG_MIX                0x04
DECL|macro|LI_FLAG_PCCONNECT
mdefine_line|#define LI_FLAG_PCCONNECT          0x08
DECL|macro|LI_FLAG_CONFERENCE
mdefine_line|#define LI_FLAG_CONFERENCE         0x10
DECL|macro|LI_FLAG_ANNOUNCEMENT
mdefine_line|#define LI_FLAG_ANNOUNCEMENT       0x20
DECL|macro|LI_COEF_CH_CH
mdefine_line|#define LI_COEF_CH_CH              0x01
DECL|macro|LI_COEF_CH_PC
mdefine_line|#define LI_COEF_CH_PC              0x02
DECL|macro|LI_COEF_PC_CH
mdefine_line|#define LI_COEF_PC_CH              0x04
DECL|macro|LI_COEF_PC_PC
mdefine_line|#define LI_COEF_PC_PC              0x08
DECL|macro|LI_COEF_CH_CH_SET
mdefine_line|#define LI_COEF_CH_CH_SET          0x10
DECL|macro|LI_COEF_CH_PC_SET
mdefine_line|#define LI_COEF_CH_PC_SET          0x20
DECL|macro|LI_COEF_PC_CH_SET
mdefine_line|#define LI_COEF_PC_CH_SET          0x40
DECL|macro|LI_COEF_PC_PC_SET
mdefine_line|#define LI_COEF_PC_PC_SET          0x80
DECL|macro|LI_REQ_SILENT_UPDATE
mdefine_line|#define LI_REQ_SILENT_UPDATE       0xffff
DECL|macro|LI_PLCI_B_LAST_FLAG
mdefine_line|#define LI_PLCI_B_LAST_FLAG        ((dword) 0x80000000L)
DECL|macro|LI_PLCI_B_DISC_FLAG
mdefine_line|#define LI_PLCI_B_DISC_FLAG        ((dword) 0x40000000L)
DECL|macro|LI_PLCI_B_SKIP_FLAG
mdefine_line|#define LI_PLCI_B_SKIP_FLAG        ((dword) 0x20000000L)
DECL|macro|LI_PLCI_B_FLAG_MASK
mdefine_line|#define LI_PLCI_B_FLAG_MASK        ((dword) 0xe0000000L)
DECL|macro|UDATA_REQUEST_SET_MIXER_COEFS_BRI
mdefine_line|#define UDATA_REQUEST_SET_MIXER_COEFS_BRI       24
DECL|macro|UDATA_REQUEST_SET_MIXER_COEFS_PRI_SYNC
mdefine_line|#define UDATA_REQUEST_SET_MIXER_COEFS_PRI_SYNC  25
DECL|macro|UDATA_REQUEST_SET_MIXER_COEFS_PRI_ASYN
mdefine_line|#define UDATA_REQUEST_SET_MIXER_COEFS_PRI_ASYN  26
DECL|macro|UDATA_INDICATION_MIXER_COEFS_SET
mdefine_line|#define UDATA_INDICATION_MIXER_COEFS_SET        24
DECL|macro|MIXER_FEATURE_ENABLE_TX_DATA
mdefine_line|#define MIXER_FEATURE_ENABLE_TX_DATA        0x0001
DECL|macro|MIXER_FEATURE_ENABLE_RX_DATA
mdefine_line|#define MIXER_FEATURE_ENABLE_RX_DATA        0x0002
DECL|macro|MIXER_COEF_LINE_CHANNEL_MASK
mdefine_line|#define MIXER_COEF_LINE_CHANNEL_MASK        0x1f
DECL|macro|MIXER_COEF_LINE_FROM_PC_FLAG
mdefine_line|#define MIXER_COEF_LINE_FROM_PC_FLAG        0x20
DECL|macro|MIXER_COEF_LINE_TO_PC_FLAG
mdefine_line|#define MIXER_COEF_LINE_TO_PC_FLAG          0x40
DECL|macro|MIXER_COEF_LINE_ROW_FLAG
mdefine_line|#define MIXER_COEF_LINE_ROW_FLAG            0x80
DECL|macro|UDATA_REQUEST_XCONNECT_FROM
mdefine_line|#define UDATA_REQUEST_XCONNECT_FROM         28
DECL|macro|UDATA_INDICATION_XCONNECT_FROM
mdefine_line|#define UDATA_INDICATION_XCONNECT_FROM      28
DECL|macro|UDATA_REQUEST_XCONNECT_TO
mdefine_line|#define UDATA_REQUEST_XCONNECT_TO           29
DECL|macro|UDATA_INDICATION_XCONNECT_TO
mdefine_line|#define UDATA_INDICATION_XCONNECT_TO        29
DECL|macro|XCONNECT_CHANNEL_PORT_B
mdefine_line|#define XCONNECT_CHANNEL_PORT_B             0x0000
DECL|macro|XCONNECT_CHANNEL_PORT_PC
mdefine_line|#define XCONNECT_CHANNEL_PORT_PC            0x8000
DECL|macro|XCONNECT_CHANNEL_PORT_MASK
mdefine_line|#define XCONNECT_CHANNEL_PORT_MASK          0x8000
DECL|macro|XCONNECT_CHANNEL_NUMBER_MASK
mdefine_line|#define XCONNECT_CHANNEL_NUMBER_MASK        0x7fff
DECL|macro|XCONNECT_CHANNEL_PORT_COUNT
mdefine_line|#define XCONNECT_CHANNEL_PORT_COUNT         2
DECL|macro|XCONNECT_SUCCESS
mdefine_line|#define XCONNECT_SUCCESS           0x0000
DECL|macro|XCONNECT_ERROR
mdefine_line|#define XCONNECT_ERROR             0x0001
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Echo canceller interface to IDI                                  */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PRIVATE_ECHO_CANCELLER
mdefine_line|#define PRIVATE_ECHO_CANCELLER         0
DECL|macro|PRIV_SELECTOR_ECHO_CANCELLER
mdefine_line|#define PRIV_SELECTOR_ECHO_CANCELLER   255
DECL|macro|EC_ENABLE_OPERATION
mdefine_line|#define EC_ENABLE_OPERATION            1
DECL|macro|EC_DISABLE_OPERATION
mdefine_line|#define EC_DISABLE_OPERATION           2
DECL|macro|EC_FREEZE_COEFFICIENTS
mdefine_line|#define EC_FREEZE_COEFFICIENTS         3
DECL|macro|EC_RESUME_COEFFICIENT_UPDATE
mdefine_line|#define EC_RESUME_COEFFICIENT_UPDATE   4
DECL|macro|EC_RESET_COEFFICIENTS
mdefine_line|#define EC_RESET_COEFFICIENTS          5
DECL|macro|EC_DISABLE_NON_LINEAR_PROCESSING
mdefine_line|#define EC_DISABLE_NON_LINEAR_PROCESSING     0x0001
DECL|macro|EC_DO_NOT_REQUIRE_REVERSALS
mdefine_line|#define EC_DO_NOT_REQUIRE_REVERSALS          0x0002
DECL|macro|EC_DETECT_DISABLE_TONE
mdefine_line|#define EC_DETECT_DISABLE_TONE               0x0004
DECL|macro|EC_SUCCESS
mdefine_line|#define EC_SUCCESS                           0
DECL|macro|EC_UNSUPPORTED_OPERATION
mdefine_line|#define EC_UNSUPPORTED_OPERATION             1
DECL|macro|EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ
mdefine_line|#define EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ   1
DECL|macro|EC_BYPASS_DUE_TO_REVERSED_2100HZ
mdefine_line|#define EC_BYPASS_DUE_TO_REVERSED_2100HZ     2
DECL|macro|EC_BYPASS_RELEASED
mdefine_line|#define EC_BYPASS_RELEASED                   3
DECL|macro|DSP_CTRL_SET_LEC_PARAMETERS
mdefine_line|#define DSP_CTRL_SET_LEC_PARAMETERS          0x05
DECL|macro|LEC_ENABLE_ECHO_CANCELLER
mdefine_line|#define LEC_ENABLE_ECHO_CANCELLER            0x0001
DECL|macro|LEC_ENABLE_2100HZ_DETECTOR
mdefine_line|#define LEC_ENABLE_2100HZ_DETECTOR           0x0002
DECL|macro|LEC_REQUIRE_2100HZ_REVERSALS
mdefine_line|#define LEC_REQUIRE_2100HZ_REVERSALS         0x0004
DECL|macro|LEC_MANUAL_DISABLE
mdefine_line|#define LEC_MANUAL_DISABLE                   0x0008
DECL|macro|LEC_ENABLE_NONLINEAR_PROCESSING
mdefine_line|#define LEC_ENABLE_NONLINEAR_PROCESSING      0x0010
DECL|macro|LEC_FREEZE_COEFFICIENTS
mdefine_line|#define LEC_FREEZE_COEFFICIENTS              0x0020
DECL|macro|LEC_RESET_COEFFICIENTS
mdefine_line|#define LEC_RESET_COEFFICIENTS               0x8000
DECL|macro|LEC_MAX_SUPPORTED_TAIL_LENGTH
mdefine_line|#define LEC_MAX_SUPPORTED_TAIL_LENGTH        32
DECL|macro|LEC_UDATA_INDICATION_DISABLE_DETECT
mdefine_line|#define LEC_UDATA_INDICATION_DISABLE_DETECT  9
DECL|macro|LEC_DISABLE_TYPE_CONTIGNUOUS_2100HZ
mdefine_line|#define LEC_DISABLE_TYPE_CONTIGNUOUS_2100HZ  0x00
DECL|macro|LEC_DISABLE_TYPE_REVERSED_2100HZ
mdefine_line|#define LEC_DISABLE_TYPE_REVERSED_2100HZ     0x01
DECL|macro|LEC_DISABLE_RELEASED
mdefine_line|#define LEC_DISABLE_RELEASED                 0x02
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* RTP interface to IDI                                             */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|B1_RTP
mdefine_line|#define B1_RTP                  31
DECL|macro|B2_RTP
mdefine_line|#define B2_RTP                  31
DECL|macro|B3_RTP
mdefine_line|#define B3_RTP                  31
DECL|macro|PRIVATE_RTP
mdefine_line|#define PRIVATE_RTP                    1
DECL|macro|RTP_PRIM_PAYLOAD_PCMU_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_PCMU_8000     0
DECL|macro|RTP_PRIM_PAYLOAD_1016_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_1016_8000     1
DECL|macro|RTP_PRIM_PAYLOAD_G726_32_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G726_32_8000  2
DECL|macro|RTP_PRIM_PAYLOAD_GSM_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_8000      3
DECL|macro|RTP_PRIM_PAYLOAD_G723_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G723_8000     4
DECL|macro|RTP_PRIM_PAYLOAD_DVI4_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_DVI4_8000     5
DECL|macro|RTP_PRIM_PAYLOAD_DVI4_16000
mdefine_line|#define RTP_PRIM_PAYLOAD_DVI4_16000    6
DECL|macro|RTP_PRIM_PAYLOAD_LPC_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_LPC_8000      7
DECL|macro|RTP_PRIM_PAYLOAD_PCMA_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_PCMA_8000     8
DECL|macro|RTP_PRIM_PAYLOAD_G722_16000
mdefine_line|#define RTP_PRIM_PAYLOAD_G722_16000    9
DECL|macro|RTP_PRIM_PAYLOAD_QCELP_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_QCELP_8000    12
DECL|macro|RTP_PRIM_PAYLOAD_G728_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G728_8000     14
DECL|macro|RTP_PRIM_PAYLOAD_G729_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_G729_8000     18
DECL|macro|RTP_PRIM_PAYLOAD_GSM_HR_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_HR_8000   30
DECL|macro|RTP_PRIM_PAYLOAD_GSM_EFR_8000
mdefine_line|#define RTP_PRIM_PAYLOAD_GSM_EFR_8000  31
DECL|macro|RTP_ADD_PAYLOAD_BASE
mdefine_line|#define RTP_ADD_PAYLOAD_BASE           32
DECL|macro|RTP_ADD_PAYLOAD_RED
mdefine_line|#define RTP_ADD_PAYLOAD_RED            32
DECL|macro|RTP_ADD_PAYLOAD_CN_8000
mdefine_line|#define RTP_ADD_PAYLOAD_CN_8000        33
DECL|macro|RTP_ADD_PAYLOAD_DTMF
mdefine_line|#define RTP_ADD_PAYLOAD_DTMF           34
DECL|macro|RTP_SUCCESS
mdefine_line|#define RTP_SUCCESS                         0
DECL|macro|RTP_ERR_SSRC_OR_PAYLOAD_CHANGE
mdefine_line|#define RTP_ERR_SSRC_OR_PAYLOAD_CHANGE      1
DECL|macro|UDATA_REQUEST_RTP_RECONFIGURE
mdefine_line|#define UDATA_REQUEST_RTP_RECONFIGURE       64
DECL|macro|UDATA_INDICATION_RTP_CHANGE
mdefine_line|#define UDATA_INDICATION_RTP_CHANGE         65
DECL|macro|BUDATA_REQUEST_QUERY_RTCP_REPORT
mdefine_line|#define BUDATA_REQUEST_QUERY_RTCP_REPORT    1
DECL|macro|BUDATA_INDICATION_RTCP_REPORT
mdefine_line|#define BUDATA_INDICATION_RTCP_REPORT       1
DECL|macro|RTP_CONNECT_OPTION_DISC_ON_SSRC_CHANGE
mdefine_line|#define RTP_CONNECT_OPTION_DISC_ON_SSRC_CHANGE    0x00000001L
DECL|macro|RTP_CONNECT_OPTION_DISC_ON_PT_CHANGE
mdefine_line|#define RTP_CONNECT_OPTION_DISC_ON_PT_CHANGE      0x00000002L
DECL|macro|RTP_CONNECT_OPTION_DISC_ON_UNKNOWN_PT
mdefine_line|#define RTP_CONNECT_OPTION_DISC_ON_UNKNOWN_PT     0x00000004L
DECL|macro|RTP_CONNECT_OPTION_NO_SILENCE_TRANSMIT
mdefine_line|#define RTP_CONNECT_OPTION_NO_SILENCE_TRANSMIT    0x00010000L
DECL|macro|RTP_PAYLOAD_OPTION_VOICE_ACTIVITY_DETECT
mdefine_line|#define RTP_PAYLOAD_OPTION_VOICE_ACTIVITY_DETECT  0x0001
DECL|macro|RTP_PAYLOAD_OPTION_DISABLE_POST_FILTER
mdefine_line|#define RTP_PAYLOAD_OPTION_DISABLE_POST_FILTER    0x0002
DECL|macro|RTP_PAYLOAD_OPTION_G723_LOW_CODING_RATE
mdefine_line|#define RTP_PAYLOAD_OPTION_G723_LOW_CODING_RATE   0x0100
DECL|macro|RTP_PACKET_FILTER_IGNORE_UNKNOWN_SSRC
mdefine_line|#define RTP_PACKET_FILTER_IGNORE_UNKNOWN_SSRC     0x00000001L
DECL|macro|RTP_CHANGE_FLAG_SSRC_CHANGE
mdefine_line|#define RTP_CHANGE_FLAG_SSRC_CHANGE               0x00000001L
DECL|macro|RTP_CHANGE_FLAG_PAYLOAD_TYPE_CHANGE
mdefine_line|#define RTP_CHANGE_FLAG_PAYLOAD_TYPE_CHANGE       0x00000002L
DECL|macro|RTP_CHANGE_FLAG_UNKNOWN_PAYLOAD_TYPE
mdefine_line|#define RTP_CHANGE_FLAG_UNKNOWN_PAYLOAD_TYPE      0x00000004L
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* T.38 interface to IDI                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|B1_T38
mdefine_line|#define B1_T38                  30
DECL|macro|B2_T38
mdefine_line|#define B2_T38                  30
DECL|macro|B3_T38
mdefine_line|#define B3_T38                  30
DECL|macro|PRIVATE_T38
mdefine_line|#define PRIVATE_T38                    2
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* PIAFS interface to IDI                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|B1_PIAFS
mdefine_line|#define B1_PIAFS                29
DECL|macro|B2_PIAFS
mdefine_line|#define B2_PIAFS                29
DECL|macro|PRIVATE_PIAFS
mdefine_line|#define PRIVATE_PIAFS           29 
multiline_comment|/*&n;  B2 configuration for PIAFS:&n;+---------------------+------+-----------------------------------------+&n;| PIAFS Protocol      | byte | Bit 1 - Protocol Speed                  |&n;| Speed configuration |      |         0 - 32K                         |&n;|                     |      |         1 - 64K (default)               |&n;|                     |      | Bit 2 - Variable Protocol Speed         |&n;|                     |      |         0 - Speed is fix                |&n;|                     |      |         1 - Speed is variable (default) |&n;+---------------------+------+-----------------------------------------+&n;| Direction           | word | Enable compression/decompression for    |&n;|                     |      | 0: All direction                        |&n;|                     |      | 1: disable outgoing data                |&n;|                     |      | 2: disable incomming data               |&n;|                     |      | 3: disable both direction (default)     |&n;+---------------------+------+-----------------------------------------+&n;| Number of code      | word | Parameter P1 of V.42bis in accordance   |&n;| words               |      | with V.42bis                            |&n;+---------------------+------+-----------------------------------------+&n;| Maximum String      | word | Parameter P2 of V.42bis in accordance   |&n;| Length              |      | with V.42bis                            |&n;+---------------------+------+-----------------------------------------+&n;| control (UDATA)     | byte | enable PIAFS control communication      |&n;| abilities           |      |                                         |&n;+---------------------+------+-----------------------------------------+&n;*/
DECL|macro|PIAFS_UDATA_ABILITIES
mdefine_line|#define PIAFS_UDATA_ABILITIES  0x80
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* FAX SUB/SEP/PWD extension                                        */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PRIVATE_FAX_SUB_SEP_PWD
mdefine_line|#define PRIVATE_FAX_SUB_SEP_PWD        3
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* V.18 extension                                                   */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PRIVATE_V18
mdefine_line|#define PRIVATE_V18                    4
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* DTMF TONE extension                                              */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|DTMF_GET_SUPPORTED_DETECT_CODES
mdefine_line|#define DTMF_GET_SUPPORTED_DETECT_CODES  0xf8
DECL|macro|DTMF_GET_SUPPORTED_SEND_CODES
mdefine_line|#define DTMF_GET_SUPPORTED_SEND_CODES    0xf9
DECL|macro|DTMF_LISTEN_TONE_START
mdefine_line|#define DTMF_LISTEN_TONE_START           0xfa
DECL|macro|DTMF_LISTEN_TONE_STOP
mdefine_line|#define DTMF_LISTEN_TONE_STOP            0xfb
DECL|macro|DTMF_SEND_TONE
mdefine_line|#define DTMF_SEND_TONE                   0xfc
DECL|macro|DTMF_LISTEN_MF_START
mdefine_line|#define DTMF_LISTEN_MF_START             0xfd
DECL|macro|DTMF_LISTEN_MF_STOP
mdefine_line|#define DTMF_LISTEN_MF_STOP              0xfe
DECL|macro|DTMF_SEND_MF
mdefine_line|#define DTMF_SEND_MF                     0xff
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_1
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_1               0x10
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_2
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_2               0x11
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_3
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_3               0x12
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_4
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_4               0x13
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_5
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_5               0x14
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_6
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_6               0x15
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_7
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_7               0x16
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_8
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_8               0x17
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_9
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_9               0x18
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_0
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_0               0x19
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_K1
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_K1              0x1a
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_K2
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_K2              0x1b
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_KP
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_KP              0x1c
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_S1
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_S1              0x1d
DECL|macro|DTMF_MF_DIGIT_TONE_CODE_ST
mdefine_line|#define DTMF_MF_DIGIT_TONE_CODE_ST              0x1e
DECL|macro|DTMF_DIGIT_CODE_COUNT
mdefine_line|#define DTMF_DIGIT_CODE_COUNT                   16
DECL|macro|DTMF_MF_DIGIT_CODE_BASE
mdefine_line|#define DTMF_MF_DIGIT_CODE_BASE                 DSP_DTMF_DIGIT_CODE_COUNT
DECL|macro|DTMF_MF_DIGIT_CODE_COUNT
mdefine_line|#define DTMF_MF_DIGIT_CODE_COUNT                15
DECL|macro|DTMF_TOTAL_DIGIT_CODE_COUNT
mdefine_line|#define DTMF_TOTAL_DIGIT_CODE_COUNT             (DSP_MF_DIGIT_CODE_BASE + DSP_MF_DIGIT_CODE_COUNT)
DECL|macro|DTMF_TONE_DIGIT_BASE
mdefine_line|#define DTMF_TONE_DIGIT_BASE                    0x80
DECL|macro|DTMF_SIGNAL_NO_TONE
mdefine_line|#define DTMF_SIGNAL_NO_TONE                     (DTMF_TONE_DIGIT_BASE + 0)
DECL|macro|DTMF_SIGNAL_UNIDENTIFIED_TONE
mdefine_line|#define DTMF_SIGNAL_UNIDENTIFIED_TONE           (DTMF_TONE_DIGIT_BASE + 1)
DECL|macro|DTMF_SIGNAL_DIAL_TONE
mdefine_line|#define DTMF_SIGNAL_DIAL_TONE                   (DTMF_TONE_DIGIT_BASE + 2)
DECL|macro|DTMF_SIGNAL_PABX_INTERNAL_DIAL_TONE
mdefine_line|#define DTMF_SIGNAL_PABX_INTERNAL_DIAL_TONE     (DTMF_TONE_DIGIT_BASE + 3)
DECL|macro|DTMF_SIGNAL_SPECIAL_DIAL_TONE
mdefine_line|#define DTMF_SIGNAL_SPECIAL_DIAL_TONE           (DTMF_TONE_DIGIT_BASE + 4)   /* stutter dial tone */
DECL|macro|DTMF_SIGNAL_SECOND_DIAL_TONE
mdefine_line|#define DTMF_SIGNAL_SECOND_DIAL_TONE            (DTMF_TONE_DIGIT_BASE + 5)
DECL|macro|DTMF_SIGNAL_RINGING_TONE
mdefine_line|#define DTMF_SIGNAL_RINGING_TONE                (DTMF_TONE_DIGIT_BASE + 6)
DECL|macro|DTMF_SIGNAL_SPECIAL_RINGING_TONE
mdefine_line|#define DTMF_SIGNAL_SPECIAL_RINGING_TONE        (DTMF_TONE_DIGIT_BASE + 7)
DECL|macro|DTMF_SIGNAL_BUSY_TONE
mdefine_line|#define DTMF_SIGNAL_BUSY_TONE                   (DTMF_TONE_DIGIT_BASE + 8)
DECL|macro|DTMF_SIGNAL_CONGESTION_TONE
mdefine_line|#define DTMF_SIGNAL_CONGESTION_TONE             (DTMF_TONE_DIGIT_BASE + 9)   /* reorder tone */
DECL|macro|DTMF_SIGNAL_SPECIAL_INFORMATION_TONE
mdefine_line|#define DTMF_SIGNAL_SPECIAL_INFORMATION_TONE    (DTMF_TONE_DIGIT_BASE + 10)
DECL|macro|DTMF_SIGNAL_COMFORT_TONE
mdefine_line|#define DTMF_SIGNAL_COMFORT_TONE                (DTMF_TONE_DIGIT_BASE + 11)
DECL|macro|DTMF_SIGNAL_HOLD_TONE
mdefine_line|#define DTMF_SIGNAL_HOLD_TONE                   (DTMF_TONE_DIGIT_BASE + 12)
DECL|macro|DTMF_SIGNAL_RECORD_TONE
mdefine_line|#define DTMF_SIGNAL_RECORD_TONE                 (DTMF_TONE_DIGIT_BASE + 13)
DECL|macro|DTMF_SIGNAL_CALLER_WAITING_TONE
mdefine_line|#define DTMF_SIGNAL_CALLER_WAITING_TONE         (DTMF_TONE_DIGIT_BASE + 14)
DECL|macro|DTMF_SIGNAL_CALL_WAITING_TONE
mdefine_line|#define DTMF_SIGNAL_CALL_WAITING_TONE           (DTMF_TONE_DIGIT_BASE + 15)
DECL|macro|DTMF_SIGNAL_PAY_TONE
mdefine_line|#define DTMF_SIGNAL_PAY_TONE                    (DTMF_TONE_DIGIT_BASE + 16)
DECL|macro|DTMF_SIGNAL_POSITIVE_INDICATION_TONE
mdefine_line|#define DTMF_SIGNAL_POSITIVE_INDICATION_TONE    (DTMF_TONE_DIGIT_BASE + 17)
DECL|macro|DTMF_SIGNAL_NEGATIVE_INDICATION_TONE
mdefine_line|#define DTMF_SIGNAL_NEGATIVE_INDICATION_TONE    (DTMF_TONE_DIGIT_BASE + 18)
DECL|macro|DTMF_SIGNAL_WARNING_TONE
mdefine_line|#define DTMF_SIGNAL_WARNING_TONE                (DTMF_TONE_DIGIT_BASE + 19)
DECL|macro|DTMF_SIGNAL_INTRUSION_TONE
mdefine_line|#define DTMF_SIGNAL_INTRUSION_TONE              (DTMF_TONE_DIGIT_BASE + 20)
DECL|macro|DTMF_SIGNAL_CALLING_CARD_SERVICE_TONE
mdefine_line|#define DTMF_SIGNAL_CALLING_CARD_SERVICE_TONE   (DTMF_TONE_DIGIT_BASE + 21)
DECL|macro|DTMF_SIGNAL_PAYPHONE_RECOGNITION_TONE
mdefine_line|#define DTMF_SIGNAL_PAYPHONE_RECOGNITION_TONE   (DTMF_TONE_DIGIT_BASE + 22)
DECL|macro|DTMF_SIGNAL_CPE_ALERTING_SIGNAL
mdefine_line|#define DTMF_SIGNAL_CPE_ALERTING_SIGNAL         (DTMF_TONE_DIGIT_BASE + 23)
DECL|macro|DTMF_SIGNAL_OFF_HOOK_WARNING_TONE
mdefine_line|#define DTMF_SIGNAL_OFF_HOOK_WARNING_TONE       (DTMF_TONE_DIGIT_BASE + 24)
DECL|macro|DTMF_SIGNAL_INTERCEPT_TONE
mdefine_line|#define DTMF_SIGNAL_INTERCEPT_TONE              (DTMF_TONE_DIGIT_BASE + 63)
DECL|macro|DTMF_SIGNAL_MODEM_CALLING_TONE
mdefine_line|#define DTMF_SIGNAL_MODEM_CALLING_TONE          (DTMF_TONE_DIGIT_BASE + 64)
DECL|macro|DTMF_SIGNAL_FAX_CALLING_TONE
mdefine_line|#define DTMF_SIGNAL_FAX_CALLING_TONE            (DTMF_TONE_DIGIT_BASE + 65)
DECL|macro|DTMF_SIGNAL_ANSWER_TONE
mdefine_line|#define DTMF_SIGNAL_ANSWER_TONE                 (DTMF_TONE_DIGIT_BASE + 66)
DECL|macro|DTMF_SIGNAL_REVERSED_ANSWER_TONE
mdefine_line|#define DTMF_SIGNAL_REVERSED_ANSWER_TONE        (DTMF_TONE_DIGIT_BASE + 67)
DECL|macro|DTMF_SIGNAL_ANSAM_TONE
mdefine_line|#define DTMF_SIGNAL_ANSAM_TONE                  (DTMF_TONE_DIGIT_BASE + 68)
DECL|macro|DTMF_SIGNAL_REVERSED_ANSAM_TONE
mdefine_line|#define DTMF_SIGNAL_REVERSED_ANSAM_TONE         (DTMF_TONE_DIGIT_BASE + 69)
DECL|macro|DTMF_SIGNAL_BELL103_ANSWER_TONE
mdefine_line|#define DTMF_SIGNAL_BELL103_ANSWER_TONE         (DTMF_TONE_DIGIT_BASE + 70)
DECL|macro|DTMF_SIGNAL_FAX_FLAGS
mdefine_line|#define DTMF_SIGNAL_FAX_FLAGS                   (DTMF_TONE_DIGIT_BASE + 71)
DECL|macro|DTMF_SIGNAL_G2_FAX_GROUP_ID
mdefine_line|#define DTMF_SIGNAL_G2_FAX_GROUP_ID             (DTMF_TONE_DIGIT_BASE + 72)
DECL|macro|DTMF_SIGNAL_HUMAN_SPEECH
mdefine_line|#define DTMF_SIGNAL_HUMAN_SPEECH                (DTMF_TONE_DIGIT_BASE + 73)
DECL|macro|DTMF_SIGNAL_ANSWERING_MACHINE_390
mdefine_line|#define DTMF_SIGNAL_ANSWERING_MACHINE_390       (DTMF_TONE_DIGIT_BASE + 74)
DECL|macro|DTMF_MF_LISTEN_ACTIVE_FLAG
mdefine_line|#define DTMF_MF_LISTEN_ACTIVE_FLAG     0x02
DECL|macro|DTMF_SEND_MF_FLAG
mdefine_line|#define DTMF_SEND_MF_FLAG              0x02
DECL|macro|DTMF_TONE_LISTEN_ACTIVE_FLAG
mdefine_line|#define DTMF_TONE_LISTEN_ACTIVE_FLAG   0x04
DECL|macro|DTMF_SEND_TONE_FLAG
mdefine_line|#define DTMF_SEND_TONE_FLAG            0x04
DECL|macro|PRIVATE_DTMF_TONE
mdefine_line|#define PRIVATE_DTMF_TONE              5
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* FAX paper format extension                                       */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PRIVATE_FAX_PAPER_FORMATS
mdefine_line|#define PRIVATE_FAX_PAPER_FORMATS      6
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* V.OWN extension                                                  */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PRIVATE_VOWN
mdefine_line|#define PRIVATE_VOWN                   7
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* FAX non-standard facilities extension                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|PRIVATE_FAX_NONSTANDARD
mdefine_line|#define PRIVATE_FAX_NONSTANDARD        8
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* Advanced voice                                                   */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|ADV_VOICE_WRITE_ACTIVATION
mdefine_line|#define ADV_VOICE_WRITE_ACTIVATION    0
DECL|macro|ADV_VOICE_WRITE_DEACTIVATION
mdefine_line|#define ADV_VOICE_WRITE_DEACTIVATION  1
DECL|macro|ADV_VOICE_WRITE_UPDATE
mdefine_line|#define ADV_VOICE_WRITE_UPDATE        2
DECL|macro|ADV_VOICE_OLD_COEF_COUNT
mdefine_line|#define ADV_VOICE_OLD_COEF_COUNT    6
DECL|macro|ADV_VOICE_NEW_COEF_BASE
mdefine_line|#define ADV_VOICE_NEW_COEF_BASE     (ADV_VOICE_OLD_COEF_COUNT * sizeof(word))
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* B1 resource switching                                            */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|B1_FACILITY_LOCAL
mdefine_line|#define B1_FACILITY_LOCAL  0x01
DECL|macro|B1_FACILITY_MIXER
mdefine_line|#define B1_FACILITY_MIXER  0x02
DECL|macro|B1_FACILITY_DTMFX
mdefine_line|#define B1_FACILITY_DTMFX  0x04
DECL|macro|B1_FACILITY_DTMFR
mdefine_line|#define B1_FACILITY_DTMFR  0x08
DECL|macro|B1_FACILITY_VOICE
mdefine_line|#define B1_FACILITY_VOICE  0x10
DECL|macro|B1_FACILITY_EC
mdefine_line|#define B1_FACILITY_EC     0x20
DECL|macro|ADJUST_B_MODE_SAVE
mdefine_line|#define ADJUST_B_MODE_SAVE          0x0001
DECL|macro|ADJUST_B_MODE_REMOVE_L23
mdefine_line|#define ADJUST_B_MODE_REMOVE_L23    0x0002
DECL|macro|ADJUST_B_MODE_SWITCH_L1
mdefine_line|#define ADJUST_B_MODE_SWITCH_L1     0x0004
DECL|macro|ADJUST_B_MODE_NO_RESOURCE
mdefine_line|#define ADJUST_B_MODE_NO_RESOURCE   0x0008
DECL|macro|ADJUST_B_MODE_ASSIGN_L23
mdefine_line|#define ADJUST_B_MODE_ASSIGN_L23    0x0010
DECL|macro|ADJUST_B_MODE_USER_CONNECT
mdefine_line|#define ADJUST_B_MODE_USER_CONNECT  0x0020
DECL|macro|ADJUST_B_MODE_CONNECT
mdefine_line|#define ADJUST_B_MODE_CONNECT       0x0040
DECL|macro|ADJUST_B_MODE_RESTORE
mdefine_line|#define ADJUST_B_MODE_RESTORE       0x0080
DECL|macro|ADJUST_B_START
mdefine_line|#define ADJUST_B_START                     0
DECL|macro|ADJUST_B_SAVE_MIXER_1
mdefine_line|#define ADJUST_B_SAVE_MIXER_1              1
DECL|macro|ADJUST_B_SAVE_DTMF_1
mdefine_line|#define ADJUST_B_SAVE_DTMF_1               2
DECL|macro|ADJUST_B_REMOVE_L23_1
mdefine_line|#define ADJUST_B_REMOVE_L23_1              3
DECL|macro|ADJUST_B_REMOVE_L23_2
mdefine_line|#define ADJUST_B_REMOVE_L23_2              4
DECL|macro|ADJUST_B_SAVE_EC_1
mdefine_line|#define ADJUST_B_SAVE_EC_1                 5
DECL|macro|ADJUST_B_SAVE_DTMF_PARAMETER_1
mdefine_line|#define ADJUST_B_SAVE_DTMF_PARAMETER_1     6
DECL|macro|ADJUST_B_SAVE_VOICE_1
mdefine_line|#define ADJUST_B_SAVE_VOICE_1              7
DECL|macro|ADJUST_B_SWITCH_L1_1
mdefine_line|#define ADJUST_B_SWITCH_L1_1               8
DECL|macro|ADJUST_B_SWITCH_L1_2
mdefine_line|#define ADJUST_B_SWITCH_L1_2               9
DECL|macro|ADJUST_B_RESTORE_VOICE_1
mdefine_line|#define ADJUST_B_RESTORE_VOICE_1           10
DECL|macro|ADJUST_B_RESTORE_VOICE_2
mdefine_line|#define ADJUST_B_RESTORE_VOICE_2           11
DECL|macro|ADJUST_B_RESTORE_DTMF_PARAMETER_1
mdefine_line|#define ADJUST_B_RESTORE_DTMF_PARAMETER_1  12
DECL|macro|ADJUST_B_RESTORE_DTMF_PARAMETER_2
mdefine_line|#define ADJUST_B_RESTORE_DTMF_PARAMETER_2  13
DECL|macro|ADJUST_B_RESTORE_EC_1
mdefine_line|#define ADJUST_B_RESTORE_EC_1              14
DECL|macro|ADJUST_B_RESTORE_EC_2
mdefine_line|#define ADJUST_B_RESTORE_EC_2              15
DECL|macro|ADJUST_B_ASSIGN_L23_1
mdefine_line|#define ADJUST_B_ASSIGN_L23_1              16
DECL|macro|ADJUST_B_ASSIGN_L23_2
mdefine_line|#define ADJUST_B_ASSIGN_L23_2              17
DECL|macro|ADJUST_B_CONNECT_1
mdefine_line|#define ADJUST_B_CONNECT_1                 18
DECL|macro|ADJUST_B_CONNECT_2
mdefine_line|#define ADJUST_B_CONNECT_2                 19
DECL|macro|ADJUST_B_CONNECT_3
mdefine_line|#define ADJUST_B_CONNECT_3                 20
DECL|macro|ADJUST_B_CONNECT_4
mdefine_line|#define ADJUST_B_CONNECT_4                 21
DECL|macro|ADJUST_B_RESTORE_DTMF_1
mdefine_line|#define ADJUST_B_RESTORE_DTMF_1            22
DECL|macro|ADJUST_B_RESTORE_DTMF_2
mdefine_line|#define ADJUST_B_RESTORE_DTMF_2            23
DECL|macro|ADJUST_B_RESTORE_MIXER_1
mdefine_line|#define ADJUST_B_RESTORE_MIXER_1           24
DECL|macro|ADJUST_B_RESTORE_MIXER_2
mdefine_line|#define ADJUST_B_RESTORE_MIXER_2           25
DECL|macro|ADJUST_B_RESTORE_MIXER_3
mdefine_line|#define ADJUST_B_RESTORE_MIXER_3           26
DECL|macro|ADJUST_B_RESTORE_MIXER_4
mdefine_line|#define ADJUST_B_RESTORE_MIXER_4           27
DECL|macro|ADJUST_B_RESTORE_MIXER_5
mdefine_line|#define ADJUST_B_RESTORE_MIXER_5           28
DECL|macro|ADJUST_B_RESTORE_MIXER_6
mdefine_line|#define ADJUST_B_RESTORE_MIXER_6           29
DECL|macro|ADJUST_B_RESTORE_MIXER_7
mdefine_line|#define ADJUST_B_RESTORE_MIXER_7           30
DECL|macro|ADJUST_B_END
mdefine_line|#define ADJUST_B_END                       31
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* XON Protocol def&squot;s                                               */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|N_CH_XOFF
mdefine_line|#define N_CH_XOFF               0x01
DECL|macro|N_XON_SENT
mdefine_line|#define N_XON_SENT              0x02
DECL|macro|N_XON_REQ
mdefine_line|#define N_XON_REQ               0x04
DECL|macro|N_XON_CONNECT_IND
mdefine_line|#define N_XON_CONNECT_IND       0x08
DECL|macro|N_RX_FLOW_CONTROL_MASK
mdefine_line|#define N_RX_FLOW_CONTROL_MASK  0x3f
DECL|macro|N_OK_FC_PENDING
mdefine_line|#define N_OK_FC_PENDING         0x80
DECL|macro|N_TX_FLOW_CONTROL_MASK
mdefine_line|#define N_TX_FLOW_CONTROL_MASK  0xc0
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* NCPI state                                                       */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|NCPI_VALID_CONNECT_B3_IND
mdefine_line|#define NCPI_VALID_CONNECT_B3_IND  0x01
DECL|macro|NCPI_VALID_CONNECT_B3_ACT
mdefine_line|#define NCPI_VALID_CONNECT_B3_ACT  0x02
DECL|macro|NCPI_VALID_DISC_B3_IND
mdefine_line|#define NCPI_VALID_DISC_B3_IND     0x04
DECL|macro|NCPI_CONNECT_B3_ACT_SENT
mdefine_line|#define NCPI_CONNECT_B3_ACT_SENT   0x08
DECL|macro|NCPI_NEGOTIATE_B3_SENT
mdefine_line|#define NCPI_NEGOTIATE_B3_SENT     0x10
DECL|macro|NCPI_MDM_CTS_ON_RECEIVED
mdefine_line|#define NCPI_MDM_CTS_ON_RECEIVED   0x40
DECL|macro|NCPI_MDM_DCD_ON_RECEIVED
mdefine_line|#define NCPI_MDM_DCD_ON_RECEIVED   0x80
multiline_comment|/*------------------------------------------------------------------*/
eof
