multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef CAPIDTMF_H_  
DECL|macro|CAPIDTMF_H_
mdefine_line|#define CAPIDTMF_H_
multiline_comment|/*---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------*/
DECL|macro|CAPIDTMF_TONE_GROUP_COUNT
mdefine_line|#define CAPIDTMF_TONE_GROUP_COUNT            2
DECL|macro|CAPIDTMF_LOW_GROUP_FREQUENCIES
mdefine_line|#define CAPIDTMF_LOW_GROUP_FREQUENCIES       4
DECL|macro|CAPIDTMF_HIGH_GROUP_FREQUENCIES
mdefine_line|#define CAPIDTMF_HIGH_GROUP_FREQUENCIES      4
DECL|macro|DSPDTMF_RX_SENSITIVITY_LOW_DEFAULT
mdefine_line|#define DSPDTMF_RX_SENSITIVITY_LOW_DEFAULT&t;50&t;/* -52 dBm */
DECL|macro|DSPDTMF_RX_SENSITIVITY_HIGH_DEFAULT
mdefine_line|#define DSPDTMF_RX_SENSITIVITY_HIGH_DEFAULT&t;50&t;/* -52 dBm */
DECL|macro|DSPDTMF_RX_HIGH_EXCEEDING_LOW_DEFAULT
mdefine_line|#define DSPDTMF_RX_HIGH_EXCEEDING_LOW_DEFAULT&t;10&t;/* dB */
DECL|macro|DSPDTMF_RX_LOW_EXCEEDING_HIGH_DEFAULT
mdefine_line|#define DSPDTMF_RX_LOW_EXCEEDING_HIGH_DEFAULT&t;10&t;/* dB */
DECL|macro|DSPDTMF_RX_HARMONICS_SEL_DEFAULT
mdefine_line|#define DSPDTMF_RX_HARMONICS_SEL_DEFAULT&t;12&t;/* dB */
DECL|macro|CAPIDTMF_RECV_BASE_FREQUENCY_COUNT
mdefine_line|#define CAPIDTMF_RECV_BASE_FREQUENCY_COUNT   (CAPIDTMF_LOW_GROUP_FREQUENCIES + CAPIDTMF_HIGH_GROUP_FREQUENCIES)
DECL|macro|CAPIDTMF_RECV_GUARD_FREQUENCY_COUNT
mdefine_line|#define CAPIDTMF_RECV_GUARD_FREQUENCY_COUNT  8
DECL|macro|CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT
mdefine_line|#define CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT  (CAPIDTMF_RECV_BASE_FREQUENCY_COUNT + CAPIDTMF_RECV_GUARD_FREQUENCY_COUNT)
DECL|macro|CAPIDTMF_RECV_POSITIVE_COEFF_COUNT
mdefine_line|#define CAPIDTMF_RECV_POSITIVE_COEFF_COUNT   16
DECL|macro|CAPIDTMF_RECV_NEGATIVE_COEFF_COUNT
mdefine_line|#define CAPIDTMF_RECV_NEGATIVE_COEFF_COUNT   (CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT - CAPIDTMF_RECV_POSITIVE_COEFF_COUNT)
DECL|macro|CAPIDTMF_RECV_ACCUMULATE_CYCLES
mdefine_line|#define CAPIDTMF_RECV_ACCUMULATE_CYCLES      205
DECL|macro|CAPIDTMF_RECV_FUNDAMENTAL_OFFSET
mdefine_line|#define CAPIDTMF_RECV_FUNDAMENTAL_OFFSET     (0xff35L * 2)
DECL|macro|CAPIDTMF_RECV_FUNDAMENTAL_DECREMENT
mdefine_line|#define CAPIDTMF_RECV_FUNDAMENTAL_DECREMENT  (0x0028L * 2)
DECL|macro|CAPIDTMF_RECV_DIGIT_BUFFER_SIZE
mdefine_line|#define CAPIDTMF_RECV_DIGIT_BUFFER_SIZE      32
DECL|macro|CAPIDTMF_RECV_STATE_IDLE
mdefine_line|#define CAPIDTMF_RECV_STATE_IDLE             0x00
DECL|macro|CAPIDTMF_RECV_STATE_DTMF_ACTIVE
mdefine_line|#define CAPIDTMF_RECV_STATE_DTMF_ACTIVE      0x01
DECL|struct|tag_capidtmf_recv_state
r_typedef
r_struct
id|tag_capidtmf_recv_state
(brace
DECL|member|digit_buffer
id|byte
id|digit_buffer
(braket
id|CAPIDTMF_RECV_DIGIT_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|digit_write_pos
id|word
id|digit_write_pos
suffix:semicolon
DECL|member|digit_read_pos
id|word
id|digit_read_pos
suffix:semicolon
DECL|member|indication_state
id|word
id|indication_state
suffix:semicolon
DECL|member|indication_state_ack
id|word
id|indication_state_ack
suffix:semicolon
DECL|member|goertzel_buffer
r_int
id|goertzel_buffer
(braket
l_int|2
)braket
(braket
id|CAPIDTMF_RECV_TOTAL_FREQUENCY_COUNT
)braket
suffix:semicolon
DECL|member|min_gap_duration
id|word
id|min_gap_duration
suffix:semicolon
DECL|member|min_digit_duration
id|word
id|min_digit_duration
suffix:semicolon
DECL|member|cycle_counter
id|word
id|cycle_counter
suffix:semicolon
DECL|member|current_digit_on_time
id|word
id|current_digit_on_time
suffix:semicolon
DECL|member|current_digit_off_time
id|word
id|current_digit_off_time
suffix:semicolon
DECL|member|current_digit_value
id|byte
id|current_digit_value
suffix:semicolon
DECL|member|state
id|byte
id|state
suffix:semicolon
DECL|typedef|t_capidtmf_recv_state
)brace
id|t_capidtmf_recv_state
suffix:semicolon
DECL|struct|tag_capidtmf_state
r_typedef
r_struct
id|tag_capidtmf_state
(brace
DECL|member|ulaw
id|byte
id|ulaw
suffix:semicolon
DECL|member|recv
id|t_capidtmf_recv_state
id|recv
suffix:semicolon
DECL|typedef|t_capidtmf_state
)brace
id|t_capidtmf_state
suffix:semicolon
id|word
id|capidtmf_recv_indication
(paren
id|t_capidtmf_state
op_star
id|p_state
comma
id|byte
op_star
id|buffer
)paren
suffix:semicolon
r_void
id|capidtmf_recv_block
(paren
id|t_capidtmf_state
op_star
id|p_state
comma
id|byte
op_star
id|buffer
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|capidtmf_init
(paren
id|t_capidtmf_state
op_star
id|p_state
comma
id|byte
id|ulaw
)paren
suffix:semicolon
r_void
id|capidtmf_recv_enable
(paren
id|t_capidtmf_state
op_star
id|p_state
comma
id|word
id|min_digit_duration
comma
id|word
id|min_gap_duration
)paren
suffix:semicolon
r_void
id|capidtmf_recv_disable
(paren
id|t_capidtmf_state
op_star
id|p_state
)paren
suffix:semicolon
DECL|macro|capidtmf_indication
mdefine_line|#define capidtmf_indication(p_state,buffer)  (((p_state)-&gt;recv.indication_state != (p_state)-&gt;recv.indication_state_ack) ?    capidtmf_recv_indication (p_state, buffer) : 0)
DECL|macro|capidtmf_recv_process_block
mdefine_line|#define capidtmf_recv_process_block(p_state,buffer,length)  { if ((p_state)-&gt;recv.state != CAPIDTMF_RECV_STATE_IDLE) capidtmf_recv_block (p_state, buffer, length); }
multiline_comment|/*---------------------------------------------------------------------------*/
multiline_comment|/*---------------------------------------------------------------------------*/
macro_line|#endif  
eof
