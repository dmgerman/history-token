multiline_comment|/*&n; * Driver for Digigram VX soundcards&n; *&n; * Definitions of DSP commands&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __VX_CMD_H
DECL|macro|__VX_CMD_H
mdefine_line|#define __VX_CMD_H
r_enum
(brace
DECL|enumerator|CMD_VERSION
id|CMD_VERSION
comma
DECL|enumerator|CMD_SUPPORTED
id|CMD_SUPPORTED
comma
DECL|enumerator|CMD_TEST_IT
id|CMD_TEST_IT
comma
DECL|enumerator|CMD_SEND_IRQA
id|CMD_SEND_IRQA
comma
DECL|enumerator|CMD_IBL
id|CMD_IBL
comma
DECL|enumerator|CMD_ASYNC
id|CMD_ASYNC
comma
DECL|enumerator|CMD_RES_PIPE
id|CMD_RES_PIPE
comma
DECL|enumerator|CMD_FREE_PIPE
id|CMD_FREE_PIPE
comma
DECL|enumerator|CMD_CONF_PIPE
id|CMD_CONF_PIPE
comma
DECL|enumerator|CMD_ABORT_CONF_PIPE
id|CMD_ABORT_CONF_PIPE
comma
DECL|enumerator|CMD_PARAM_OUTPUT_PIPE
id|CMD_PARAM_OUTPUT_PIPE
comma
DECL|enumerator|CMD_STOP_PIPE
id|CMD_STOP_PIPE
comma
DECL|enumerator|CMD_PIPE_STATE
id|CMD_PIPE_STATE
comma
DECL|enumerator|CMD_PIPE_SPL_COUNT
id|CMD_PIPE_SPL_COUNT
comma
DECL|enumerator|CMD_CAN_START_PIPE
id|CMD_CAN_START_PIPE
comma
DECL|enumerator|CMD_SIZE_HBUFFER
id|CMD_SIZE_HBUFFER
comma
DECL|enumerator|CMD_START_STREAM
id|CMD_START_STREAM
comma
DECL|enumerator|CMD_START_ONE_STREAM
id|CMD_START_ONE_STREAM
comma
DECL|enumerator|CMD_PAUSE_STREAM
id|CMD_PAUSE_STREAM
comma
DECL|enumerator|CMD_PAUSE_ONE_STREAM
id|CMD_PAUSE_ONE_STREAM
comma
DECL|enumerator|CMD_STREAM_OUT_LEVEL_ADJUST
id|CMD_STREAM_OUT_LEVEL_ADJUST
comma
DECL|enumerator|CMD_STOP_STREAM
id|CMD_STOP_STREAM
comma
DECL|enumerator|CMD_FORMAT_STREAM_OUT
id|CMD_FORMAT_STREAM_OUT
comma
DECL|enumerator|CMD_FORMAT_STREAM_IN
id|CMD_FORMAT_STREAM_IN
comma
DECL|enumerator|CMD_GET_STREAM_STATE
id|CMD_GET_STREAM_STATE
comma
DECL|enumerator|CMD_DROP_BYTES_AWAY
id|CMD_DROP_BYTES_AWAY
comma
DECL|enumerator|CMD_GET_REMAINING_BYTES
id|CMD_GET_REMAINING_BYTES
comma
DECL|enumerator|CMD_CONNECT_AUDIO
id|CMD_CONNECT_AUDIO
comma
DECL|enumerator|CMD_AUDIO_LEVEL_ADJUST
id|CMD_AUDIO_LEVEL_ADJUST
comma
DECL|enumerator|CMD_AUDIO_VU_PIC_METER
id|CMD_AUDIO_VU_PIC_METER
comma
DECL|enumerator|CMD_GET_AUDIO_LEVELS
id|CMD_GET_AUDIO_LEVELS
comma
DECL|enumerator|CMD_GET_NOTIFY_EVENT
id|CMD_GET_NOTIFY_EVENT
comma
DECL|enumerator|CMD_INFO_NOTIFIED
id|CMD_INFO_NOTIFIED
comma
DECL|enumerator|CMD_ACCESS_IO_FCT
id|CMD_ACCESS_IO_FCT
comma
DECL|enumerator|CMD_STATUS_R_BUFFERS
id|CMD_STATUS_R_BUFFERS
comma
DECL|enumerator|CMD_UPDATE_R_BUFFERS
id|CMD_UPDATE_R_BUFFERS
comma
DECL|enumerator|CMD_LOAD_EFFECT_CONTEXT
id|CMD_LOAD_EFFECT_CONTEXT
comma
DECL|enumerator|CMD_EFFECT_ONE_PIPE
id|CMD_EFFECT_ONE_PIPE
comma
DECL|enumerator|CMD_MODIFY_CLOCK
id|CMD_MODIFY_CLOCK
comma
DECL|enumerator|CMD_STREAM1_OUT_SET_N_LEVELS
id|CMD_STREAM1_OUT_SET_N_LEVELS
comma
DECL|enumerator|CMD_PURGE_STREAM_DCMDS
id|CMD_PURGE_STREAM_DCMDS
comma
DECL|enumerator|CMD_NOTIFY_PIPE_TIME
id|CMD_NOTIFY_PIPE_TIME
comma
DECL|enumerator|CMD_LOAD_EFFECT_CONTEXT_PACKET
id|CMD_LOAD_EFFECT_CONTEXT_PACKET
comma
DECL|enumerator|CMD_RELIC_R_BUFFER
id|CMD_RELIC_R_BUFFER
comma
DECL|enumerator|CMD_RESYNC_AUDIO_INPUTS
id|CMD_RESYNC_AUDIO_INPUTS
comma
DECL|enumerator|CMD_NOTIFY_STREAM_TIME
id|CMD_NOTIFY_STREAM_TIME
comma
DECL|enumerator|CMD_STREAM_SAMPLE_COUNT
id|CMD_STREAM_SAMPLE_COUNT
comma
DECL|enumerator|CMD_CONFIG_TIME_CODE
id|CMD_CONFIG_TIME_CODE
comma
DECL|enumerator|CMD_GET_TIME_CODE
id|CMD_GET_TIME_CODE
comma
DECL|enumerator|CMD_MANAGE_SIGNAL
id|CMD_MANAGE_SIGNAL
comma
DECL|enumerator|CMD_PARAMETER_STREAM_OUT
id|CMD_PARAMETER_STREAM_OUT
comma
DECL|enumerator|CMD_READ_BOARD_FREQ
id|CMD_READ_BOARD_FREQ
comma
DECL|enumerator|CMD_GET_STREAM_LEVELS
id|CMD_GET_STREAM_LEVELS
comma
DECL|enumerator|CMD_PURGE_PIPE_DCMDS
id|CMD_PURGE_PIPE_DCMDS
comma
singleline_comment|// CMD_SET_STREAM_OUT_EFFECTS,
singleline_comment|// CMD_GET_STREAM_OUT_EFFECTS,
DECL|enumerator|CMD_CONNECT_MONITORING
id|CMD_CONNECT_MONITORING
comma
DECL|enumerator|CMD_STREAM2_OUT_SET_N_LEVELS
id|CMD_STREAM2_OUT_SET_N_LEVELS
comma
DECL|enumerator|CMD_CANCEL_R_BUFFERS
id|CMD_CANCEL_R_BUFFERS
comma
DECL|enumerator|CMD_NOTIFY_END_OF_BUFFER
id|CMD_NOTIFY_END_OF_BUFFER
comma
DECL|enumerator|CMD_GET_STREAM_VU_METER
id|CMD_GET_STREAM_VU_METER
comma
DECL|enumerator|CMD_LAST_INDEX
id|CMD_LAST_INDEX
)brace
suffix:semicolon
DECL|struct|vx_cmd_info
r_struct
id|vx_cmd_info
(brace
DECL|member|opcode
r_int
r_int
id|opcode
suffix:semicolon
multiline_comment|/* command word */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* command length (in words) */
DECL|member|st_type
r_int
id|st_type
suffix:semicolon
multiline_comment|/* status type (RMH_SSIZE_XXX) */
DECL|member|st_length
r_int
id|st_length
suffix:semicolon
multiline_comment|/* fixed length */
)brace
suffix:semicolon
multiline_comment|/* Family and code op of some DSP requests. */
DECL|macro|CODE_OP_PIPE_TIME
mdefine_line|#define CODE_OP_PIPE_TIME                       0x004e0000
DECL|macro|CODE_OP_START_STREAM
mdefine_line|#define CODE_OP_START_STREAM                    0x00800000
DECL|macro|CODE_OP_PAUSE_STREAM
mdefine_line|#define CODE_OP_PAUSE_STREAM                    0x00810000
DECL|macro|CODE_OP_OUT_STREAM_LEVEL
mdefine_line|#define CODE_OP_OUT_STREAM_LEVEL                0x00820000
DECL|macro|CODE_OP_UPDATE_R_BUFFERS
mdefine_line|#define CODE_OP_UPDATE_R_BUFFERS                0x00840000
DECL|macro|CODE_OP_OUT_STREAM1_LEVEL_CURVE
mdefine_line|#define CODE_OP_OUT_STREAM1_LEVEL_CURVE         0x00850000
DECL|macro|CODE_OP_OUT_STREAM2_LEVEL_CURVE
mdefine_line|#define CODE_OP_OUT_STREAM2_LEVEL_CURVE         0x00930000
DECL|macro|CODE_OP_OUT_STREAM_FORMAT
mdefine_line|#define CODE_OP_OUT_STREAM_FORMAT               0x00860000
DECL|macro|CODE_OP_STREAM_TIME
mdefine_line|#define CODE_OP_STREAM_TIME                     0x008f0000
DECL|macro|CODE_OP_OUT_STREAM_EXTRAPARAMETER
mdefine_line|#define CODE_OP_OUT_STREAM_EXTRAPARAMETER       0x00910000
DECL|macro|CODE_OP_OUT_AUDIO_LEVEL
mdefine_line|#define CODE_OP_OUT_AUDIO_LEVEL                 0x00c20000
DECL|macro|NOTIFY_LAST_COMMAND
mdefine_line|#define NOTIFY_LAST_COMMAND     0x00400000
multiline_comment|/* Values for a user delay */
DECL|macro|DC_DIFFERED_DELAY
mdefine_line|#define DC_DIFFERED_DELAY       (1&lt;&lt;BIT_DIFFERED_COMMAND)
DECL|macro|DC_NOTIFY_DELAY
mdefine_line|#define DC_NOTIFY_DELAY         (1&lt;&lt;BIT_NOTIFIED_COMMAND)
DECL|macro|DC_HBUFFER_DELAY
mdefine_line|#define DC_HBUFFER_DELAY        (1&lt;&lt;BIT_TIME_RELATIVE_TO_BUFFER)
DECL|macro|DC_MULTIPLE_DELAY
mdefine_line|#define DC_MULTIPLE_DELAY       (1&lt;&lt;BIT_RESERVED)
DECL|macro|DC_STREAM_TIME_DELAY
mdefine_line|#define DC_STREAM_TIME_DELAY    (1&lt;&lt;BIT_STREAM_TIME)
DECL|macro|DC_CANCELLED_DELAY
mdefine_line|#define DC_CANCELLED_DELAY      (1&lt;&lt;BIT_CANCELLED_COMMAND)
multiline_comment|/* Values for tiDelayed field in TIME_INFO structure,&n; * and for pbPause field in PLAY_BUFFER_INFO structure&n; */
DECL|macro|BIT_DIFFERED_COMMAND
mdefine_line|#define BIT_DIFFERED_COMMAND                0
DECL|macro|BIT_NOTIFIED_COMMAND
mdefine_line|#define BIT_NOTIFIED_COMMAND                1
DECL|macro|BIT_TIME_RELATIVE_TO_BUFFER
mdefine_line|#define BIT_TIME_RELATIVE_TO_BUFFER         2
DECL|macro|BIT_RESERVED
mdefine_line|#define BIT_RESERVED                        3
DECL|macro|BIT_STREAM_TIME
mdefine_line|#define BIT_STREAM_TIME                     4
DECL|macro|BIT_CANCELLED_COMMAND
mdefine_line|#define BIT_CANCELLED_COMMAND               5
multiline_comment|/* Access to the &quot;Size&quot; field of the response of the CMD_GET_NOTIFY_EVENT request. */
DECL|macro|GET_NOTIFY_EVENT_SIZE_FIELD_MASK
mdefine_line|#define GET_NOTIFY_EVENT_SIZE_FIELD_MASK    0x000000ff
multiline_comment|/* DSP commands general masks */
DECL|macro|OPCODE_MASK
mdefine_line|#define OPCODE_MASK                 0x00ff0000
DECL|macro|DSP_DIFFERED_COMMAND_MASK
mdefine_line|#define DSP_DIFFERED_COMMAND_MASK   0x0000C000
multiline_comment|/* Notifications (NOTIFY_INFO) */
DECL|macro|ALL_CMDS_NOTIFIED
mdefine_line|#define ALL_CMDS_NOTIFIED                   0x0000  
singleline_comment|// reserved
DECL|macro|START_STREAM_NOTIFIED
mdefine_line|#define START_STREAM_NOTIFIED               0x0001
DECL|macro|PAUSE_STREAM_NOTIFIED
mdefine_line|#define PAUSE_STREAM_NOTIFIED               0x0002
DECL|macro|OUT_STREAM_LEVEL_NOTIFIED
mdefine_line|#define OUT_STREAM_LEVEL_NOTIFIED           0x0003
DECL|macro|OUT_STREAM_PARAMETER_NOTIFIED
mdefine_line|#define OUT_STREAM_PARAMETER_NOTIFIED       0x0004  
singleline_comment|// left for backward compatibility
DECL|macro|OUT_STREAM_FORMAT_NOTIFIED
mdefine_line|#define OUT_STREAM_FORMAT_NOTIFIED          0x0004
DECL|macro|PIPE_TIME_NOTIFIED
mdefine_line|#define PIPE_TIME_NOTIFIED                  0x0005
DECL|macro|OUT_AUDIO_LEVEL_NOTIFIED
mdefine_line|#define OUT_AUDIO_LEVEL_NOTIFIED            0x0006
DECL|macro|OUT_STREAM_LEVEL_CURVE_NOTIFIED
mdefine_line|#define OUT_STREAM_LEVEL_CURVE_NOTIFIED     0x0007
DECL|macro|STREAM_TIME_NOTIFIED
mdefine_line|#define STREAM_TIME_NOTIFIED                0x0008
DECL|macro|OUT_STREAM_EXTRAPARAMETER_NOTIFIED
mdefine_line|#define OUT_STREAM_EXTRAPARAMETER_NOTIFIED  0x0009
DECL|macro|UNKNOWN_COMMAND_NOTIFIED
mdefine_line|#define UNKNOWN_COMMAND_NOTIFIED            0xffff
multiline_comment|/* Output pipe parameters setting */
DECL|macro|MASK_VALID_PIPE_MPEG_PARAM
mdefine_line|#define MASK_VALID_PIPE_MPEG_PARAM      0x000040
DECL|macro|MASK_VALID_PIPE_BACKWARD_PARAM
mdefine_line|#define MASK_VALID_PIPE_BACKWARD_PARAM  0x000020
DECL|macro|MASK_SET_PIPE_MPEG_PARAM
mdefine_line|#define MASK_SET_PIPE_MPEG_PARAM        0x000002
DECL|macro|MASK_SET_PIPE_BACKWARD_PARAM
mdefine_line|#define MASK_SET_PIPE_BACKWARD_PARAM    0x000001
DECL|macro|MASK_DSP_WORD
mdefine_line|#define MASK_DSP_WORD           0x00FFFFFF
DECL|macro|MASK_ALL_STREAM
mdefine_line|#define MASK_ALL_STREAM         0x00FFFFFF
DECL|macro|MASK_DSP_WORD_LEVEL
mdefine_line|#define MASK_DSP_WORD_LEVEL     0x000001FF
DECL|macro|MASK_FIRST_FIELD
mdefine_line|#define MASK_FIRST_FIELD        0x0000001F
DECL|macro|FIELD_SIZE
mdefine_line|#define FIELD_SIZE              5
DECL|macro|COMMAND_RECORD_MASK
mdefine_line|#define COMMAND_RECORD_MASK     0x000800
multiline_comment|/* PipeManagement definition bits (PIPE_DECL_INFO) */
DECL|macro|P_UNDERRUN_SKIP_SOUND_MASK
mdefine_line|#define P_UNDERRUN_SKIP_SOUND_MASK&t;&t;&t;&t;0x01
DECL|macro|P_PREPARE_FOR_MPEG3_MASK
mdefine_line|#define P_PREPARE_FOR_MPEG3_MASK&t;&t;&t;&t;0x02
DECL|macro|P_DO_NOT_RESET_ANALOG_LEVELS
mdefine_line|#define P_DO_NOT_RESET_ANALOG_LEVELS&t;&t;&t;0x04
DECL|macro|P_ALLOW_UNDER_ALLOCATION_MASK
mdefine_line|#define P_ALLOW_UNDER_ALLOCATION_MASK&t;&t;&t;0x08
DECL|macro|P_DATA_MODE_MASK
mdefine_line|#define P_DATA_MODE_MASK&t;&t;&t;&t;0x10
DECL|macro|P_ASIO_BUFFER_MANAGEMENT_MASK
mdefine_line|#define P_ASIO_BUFFER_MANAGEMENT_MASK&t;&t;&t;0x20
DECL|macro|BIT_SKIP_SOUND
mdefine_line|#define BIT_SKIP_SOUND&t;&t;&t;&t;&t;0x08&t;
singleline_comment|// bit 3
DECL|macro|BIT_DATA_MODE
mdefine_line|#define BIT_DATA_MODE&t;&t;&t;&t;&t;0x10&t;
singleline_comment|// bit 4
multiline_comment|/* Bits in the CMD_MODIFY_CLOCK request. */
DECL|macro|CMD_MODIFY_CLOCK_FD_BIT
mdefine_line|#define CMD_MODIFY_CLOCK_FD_BIT     0x00000001
DECL|macro|CMD_MODIFY_CLOCK_T_BIT
mdefine_line|#define CMD_MODIFY_CLOCK_T_BIT      0x00000002
DECL|macro|CMD_MODIFY_CLOCK_S_BIT
mdefine_line|#define CMD_MODIFY_CLOCK_S_BIT      0x00000004
multiline_comment|/* Access to the results of the CMD_GET_TIME_CODE RMH. */
DECL|macro|TIME_CODE_V_MASK
mdefine_line|#define TIME_CODE_V_MASK            0x00800000
DECL|macro|TIME_CODE_N_MASK
mdefine_line|#define TIME_CODE_N_MASK            0x00400000
DECL|macro|TIME_CODE_B_MASK
mdefine_line|#define TIME_CODE_B_MASK            0x00200000
DECL|macro|TIME_CODE_W_MASK
mdefine_line|#define TIME_CODE_W_MASK            0x00100000
multiline_comment|/* Values for the CMD_MANAGE_SIGNAL RMH. */
DECL|macro|MANAGE_SIGNAL_TIME_CODE
mdefine_line|#define MANAGE_SIGNAL_TIME_CODE     0x01
DECL|macro|MANAGE_SIGNAL_MIDI
mdefine_line|#define MANAGE_SIGNAL_MIDI          0x02
multiline_comment|/* Values for the CMD_CONFIG_TIME_CODE RMH. */
DECL|macro|CONFIG_TIME_CODE_CANCEL
mdefine_line|#define CONFIG_TIME_CODE_CANCEL     0x00001000
multiline_comment|/* Mask to get only the effective time from the&n; * high word out of the 2 returned by the DSP&n; */
DECL|macro|PCX_TIME_HI_MASK
mdefine_line|#define PCX_TIME_HI_MASK        0x000fffff
multiline_comment|/* Values for setting a H-Buffer time */
DECL|macro|HBUFFER_TIME_HIGH
mdefine_line|#define HBUFFER_TIME_HIGH       0x00200000
DECL|macro|HBUFFER_TIME_LOW
mdefine_line|#define HBUFFER_TIME_LOW        0x00000000
DECL|macro|NOTIFY_MASK_TIME_HIGH
mdefine_line|#define NOTIFY_MASK_TIME_HIGH   0x00400000
DECL|macro|MULTIPLE_MASK_TIME_HIGH
mdefine_line|#define MULTIPLE_MASK_TIME_HIGH 0x00100000
DECL|macro|STREAM_MASK_TIME_HIGH
mdefine_line|#define STREAM_MASK_TIME_HIGH   0x00800000
multiline_comment|/*&n; *&n; */
r_void
id|vx_init_rmh
c_func
(paren
r_struct
id|vx_rmh
op_star
id|rmh
comma
r_int
r_int
id|cmd
)paren
suffix:semicolon
multiline_comment|/**&n; * vx_send_pipe_cmd_params - fill first command word for pipe commands&n; * @rmh: the rmh to be modified&n; * @is_capture: 0 = playback, 1 = capture operation&n; * @param1: first pipe-parameter&n; * @param2: second pipe-parameter&n; */
DECL|function|vx_set_pipe_cmd_params
r_static
r_inline
r_void
id|vx_set_pipe_cmd_params
c_func
(paren
r_struct
id|vx_rmh
op_star
id|rmh
comma
r_int
id|is_capture
comma
r_int
id|param1
comma
r_int
id|param2
)paren
(brace
r_if
c_cond
(paren
id|is_capture
)paren
id|rmh-&gt;Cmd
(braket
l_int|0
)braket
op_or_assign
id|COMMAND_RECORD_MASK
suffix:semicolon
id|rmh-&gt;Cmd
(braket
l_int|0
)braket
op_or_assign
(paren
(paren
(paren
id|u32
)paren
id|param1
op_amp
id|MASK_FIRST_FIELD
)paren
op_lshift
id|FIELD_SIZE
)paren
op_amp
id|MASK_DSP_WORD
suffix:semicolon
r_if
c_cond
(paren
id|param2
)paren
id|rmh-&gt;Cmd
(braket
l_int|0
)braket
op_or_assign
(paren
(paren
id|u32
)paren
id|param2
op_amp
id|MASK_FIRST_FIELD
)paren
op_amp
id|MASK_DSP_WORD
suffix:semicolon
)brace
multiline_comment|/**&n; * vx_set_stream_cmd_params - fill first command word for stream commands&n; * @rmh: the rmh to be modified&n; * @is_capture: 0 = playback, 1 = capture operation&n; * @pipe: the pipe index (zero-based)&n; */
DECL|function|vx_set_stream_cmd_params
r_static
r_inline
r_void
id|vx_set_stream_cmd_params
c_func
(paren
r_struct
id|vx_rmh
op_star
id|rmh
comma
r_int
id|is_capture
comma
r_int
id|pipe
)paren
(brace
r_if
c_cond
(paren
id|is_capture
)paren
id|rmh-&gt;Cmd
(braket
l_int|0
)braket
op_or_assign
id|COMMAND_RECORD_MASK
suffix:semicolon
id|rmh-&gt;Cmd
(braket
l_int|0
)braket
op_or_assign
(paren
(paren
(paren
id|u32
)paren
id|pipe
op_amp
id|MASK_FIRST_FIELD
)paren
op_lshift
id|FIELD_SIZE
)paren
op_amp
id|MASK_DSP_WORD
suffix:semicolon
)brace
macro_line|#endif /* __VX_CMD_H */
eof
