multiline_comment|/*&n; * &t;dscore.h&n; *&n; * Copyright (c) 2004 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; * &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef __DSCORE_H
DECL|macro|__DSCORE_H
mdefine_line|#define __DSCORE_H
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/* COMMAND TYPE CODES */
DECL|macro|CONTROL_CMD
mdefine_line|#define CONTROL_CMD&t;&t;&t;0x00
DECL|macro|COMM_CMD
mdefine_line|#define COMM_CMD&t;&t;&t;0x01
DECL|macro|MODE_CMD
mdefine_line|#define MODE_CMD&t;&t;&t;0x02
multiline_comment|/* CONTROL COMMAND CODES */
DECL|macro|CTL_RESET_DEVICE
mdefine_line|#define CTL_RESET_DEVICE&t;&t;0x0000
DECL|macro|CTL_START_EXE
mdefine_line|#define CTL_START_EXE&t;&t;&t;0x0001
DECL|macro|CTL_RESUME_EXE
mdefine_line|#define CTL_RESUME_EXE&t;&t;&t;0x0002
DECL|macro|CTL_HALT_EXE_IDLE
mdefine_line|#define CTL_HALT_EXE_IDLE&t;&t;0x0003
DECL|macro|CTL_HALT_EXE_DONE
mdefine_line|#define CTL_HALT_EXE_DONE&t;&t;0x0004
DECL|macro|CTL_FLUSH_COMM_CMDS
mdefine_line|#define CTL_FLUSH_COMM_CMDS&t;&t;0x0007
DECL|macro|CTL_FLUSH_RCV_BUFFER
mdefine_line|#define CTL_FLUSH_RCV_BUFFER&t;&t;0x0008
DECL|macro|CTL_FLUSH_XMT_BUFFER
mdefine_line|#define CTL_FLUSH_XMT_BUFFER&t;&t;0x0009
DECL|macro|CTL_GET_COMM_CMDS
mdefine_line|#define CTL_GET_COMM_CMDS&t;&t;0x000A
multiline_comment|/* MODE COMMAND CODES */
DECL|macro|MOD_PULSE_EN
mdefine_line|#define MOD_PULSE_EN&t;&t;&t;0x0000
DECL|macro|MOD_SPEED_CHANGE_EN
mdefine_line|#define MOD_SPEED_CHANGE_EN&t;&t;0x0001
DECL|macro|MOD_1WIRE_SPEED
mdefine_line|#define MOD_1WIRE_SPEED&t;&t;&t;0x0002
DECL|macro|MOD_STRONG_PU_DURATION
mdefine_line|#define MOD_STRONG_PU_DURATION&t;&t;0x0003
DECL|macro|MOD_PULLDOWN_SLEWRATE
mdefine_line|#define MOD_PULLDOWN_SLEWRATE&t;&t;0x0004
DECL|macro|MOD_PROG_PULSE_DURATION
mdefine_line|#define MOD_PROG_PULSE_DURATION&t;&t;0x0005
DECL|macro|MOD_WRITE1_LOWTIME
mdefine_line|#define MOD_WRITE1_LOWTIME&t;&t;0x0006
DECL|macro|MOD_DSOW0_TREC
mdefine_line|#define MOD_DSOW0_TREC&t;&t;&t;0x0007
multiline_comment|/* COMMUNICATION COMMAND CODES */
DECL|macro|COMM_ERROR_ESCAPE
mdefine_line|#define COMM_ERROR_ESCAPE&t;&t;0x0601
DECL|macro|COMM_SET_DURATION
mdefine_line|#define COMM_SET_DURATION&t;&t;0x0012
DECL|macro|COMM_BIT_IO
mdefine_line|#define COMM_BIT_IO&t;&t;&t;0x0020
DECL|macro|COMM_PULSE
mdefine_line|#define COMM_PULSE&t;&t;&t;0x0030
DECL|macro|COMM_1_WIRE_RESET
mdefine_line|#define COMM_1_WIRE_RESET&t;&t;0x0042
DECL|macro|COMM_BYTE_IO
mdefine_line|#define COMM_BYTE_IO&t;&t;&t;0x0052
DECL|macro|COMM_MATCH_ACCESS
mdefine_line|#define COMM_MATCH_ACCESS&t;&t;0x0064
DECL|macro|COMM_BLOCK_IO
mdefine_line|#define COMM_BLOCK_IO&t;&t;&t;0x0074
DECL|macro|COMM_READ_STRAIGHT
mdefine_line|#define COMM_READ_STRAIGHT&t;&t;0x0080
DECL|macro|COMM_DO_RELEASE
mdefine_line|#define COMM_DO_RELEASE&t;&t;&t;0x6092
DECL|macro|COMM_SET_PATH
mdefine_line|#define COMM_SET_PATH&t;&t;&t;0x00A2
DECL|macro|COMM_WRITE_SRAM_PAGE
mdefine_line|#define COMM_WRITE_SRAM_PAGE&t;&t;0x00B2
DECL|macro|COMM_WRITE_EPROM
mdefine_line|#define COMM_WRITE_EPROM&t;&t;0x00C4
DECL|macro|COMM_READ_CRC_PROT_PAGE
mdefine_line|#define COMM_READ_CRC_PROT_PAGE&t;&t;0x00D4
DECL|macro|COMM_READ_REDIRECT_PAGE_CRC
mdefine_line|#define COMM_READ_REDIRECT_PAGE_CRC&t;0x21E4
DECL|macro|COMM_SEARCH_ACCESS
mdefine_line|#define COMM_SEARCH_ACCESS&t;&t;0x00F4
multiline_comment|/* Communication command bits */
DECL|macro|COMM_TYPE
mdefine_line|#define COMM_TYPE&t;&t;&t;0x0008
DECL|macro|COMM_SE
mdefine_line|#define COMM_SE&t;&t;&t;&t;0x0008
DECL|macro|COMM_D
mdefine_line|#define COMM_D&t;&t;&t;&t;0x0008
DECL|macro|COMM_Z
mdefine_line|#define COMM_Z&t;&t;&t;&t;0x0008
DECL|macro|COMM_CH
mdefine_line|#define COMM_CH&t;&t;&t;&t;0x0008
DECL|macro|COMM_SM
mdefine_line|#define COMM_SM&t;&t;&t;&t;0x0008
DECL|macro|COMM_R
mdefine_line|#define COMM_R&t;&t;&t;&t;0x0008
DECL|macro|COMM_IM
mdefine_line|#define COMM_IM&t;&t;&t;&t;0x0001
DECL|macro|COMM_PS
mdefine_line|#define COMM_PS&t;&t;&t;&t;0x4000
DECL|macro|COMM_PST
mdefine_line|#define COMM_PST&t;&t;&t;0x4000
DECL|macro|COMM_CIB
mdefine_line|#define COMM_CIB&t;&t;&t;0x4000
DECL|macro|COMM_RTS
mdefine_line|#define COMM_RTS&t;&t;&t;0x4000
DECL|macro|COMM_DT
mdefine_line|#define COMM_DT&t;&t;&t;&t;0x2000
DECL|macro|COMM_SPU
mdefine_line|#define COMM_SPU&t;&t;&t;0x1000
DECL|macro|COMM_F
mdefine_line|#define COMM_F&t;&t;&t;&t;0x0800
DECL|macro|COMM_NTP
mdefine_line|#define COMM_NTP&t;&t;&t;0x0400
DECL|macro|COMM_ICP
mdefine_line|#define COMM_ICP&t;&t;&t;0x0200
DECL|macro|COMM_RST
mdefine_line|#define COMM_RST&t;&t;&t;0x0100
DECL|macro|PULSE_PROG
mdefine_line|#define PULSE_PROG&t;&t;&t;0x01
DECL|macro|PULSE_SPUE
mdefine_line|#define PULSE_SPUE&t;&t;&t;0x02
DECL|macro|BRANCH_MAIN
mdefine_line|#define BRANCH_MAIN&t;&t;&t;0xCC
DECL|macro|BRANCH_AUX
mdefine_line|#define BRANCH_AUX&t;&t;&t;0x33
multiline_comment|/*&n; * Duration of the strong pull-up pulse in milliseconds.&n; */
DECL|macro|PULLUP_PULSE_DURATION
mdefine_line|#define PULLUP_PULSE_DURATION&t;&t;750
multiline_comment|/* Status flags */
DECL|macro|ST_SPUA
mdefine_line|#define ST_SPUA&t;&t;&t;&t;0x01  /* Strong Pull-up is active */
DECL|macro|ST_PRGA
mdefine_line|#define ST_PRGA&t;&t;&t;&t;0x02  /* 12V programming pulse is being generated */
DECL|macro|ST_12VP
mdefine_line|#define ST_12VP&t;&t;&t;&t;0x04  /* external 12V programming voltage is present */
DECL|macro|ST_PMOD
mdefine_line|#define ST_PMOD&t;&t;&t;&t;0x08  /* DS2490 powered from USB and external sources */
DECL|macro|ST_HALT
mdefine_line|#define ST_HALT&t;&t;&t;&t;0x10  /* DS2490 is currently halted */
DECL|macro|ST_IDLE
mdefine_line|#define ST_IDLE&t;&t;&t;&t;0x20  /* DS2490 is currently idle */
DECL|macro|ST_EPOF
mdefine_line|#define ST_EPOF&t;&t;&t;&t;0x80
DECL|macro|SPEED_NORMAL
mdefine_line|#define SPEED_NORMAL&t;&t;&t;0x00
DECL|macro|SPEED_FLEXIBLE
mdefine_line|#define SPEED_FLEXIBLE&t;&t;&t;0x01
DECL|macro|SPEED_OVERDRIVE
mdefine_line|#define SPEED_OVERDRIVE&t;&t;&t;0x02
DECL|macro|NUM_EP
mdefine_line|#define NUM_EP&t;&t;&t;&t;4
DECL|macro|EP_CONTROL
mdefine_line|#define EP_CONTROL&t;&t;&t;0
DECL|macro|EP_STATUS
mdefine_line|#define EP_STATUS&t;&t;&t;1
DECL|macro|EP_DATA_OUT
mdefine_line|#define EP_DATA_OUT&t;&t;&t;2
DECL|macro|EP_DATA_IN
mdefine_line|#define EP_DATA_IN&t;&t;&t;3
DECL|struct|ds_device
r_struct
id|ds_device
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|intf
r_struct
id|usb_interface
op_star
id|intf
suffix:semicolon
DECL|member|ep
r_int
id|ep
(braket
id|NUM_EP
)braket
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ds_status
r_struct
id|ds_status
(brace
DECL|member|enable
id|u8
id|enable
suffix:semicolon
DECL|member|speed
id|u8
id|speed
suffix:semicolon
DECL|member|pullup_dur
id|u8
id|pullup_dur
suffix:semicolon
DECL|member|ppuls_dur
id|u8
id|ppuls_dur
suffix:semicolon
DECL|member|pulldown_slew
id|u8
id|pulldown_slew
suffix:semicolon
DECL|member|write1_time
id|u8
id|write1_time
suffix:semicolon
DECL|member|write0_time
id|u8
id|write0_time
suffix:semicolon
DECL|member|reserved0
id|u8
id|reserved0
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
DECL|member|command0
id|u8
id|command0
suffix:semicolon
DECL|member|command1
id|u8
id|command1
suffix:semicolon
DECL|member|command_buffer_status
id|u8
id|command_buffer_status
suffix:semicolon
DECL|member|data_out_buffer_status
id|u8
id|data_out_buffer_status
suffix:semicolon
DECL|member|data_in_buffer_status
id|u8
id|data_in_buffer_status
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
)brace
suffix:semicolon
r_int
id|ds_touch_bit
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
comma
id|u8
op_star
)paren
suffix:semicolon
r_int
id|ds_read_byte
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_int
id|ds_read_bit
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_int
id|ds_write_byte
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
)paren
suffix:semicolon
r_int
id|ds_write_bit
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
)paren
suffix:semicolon
r_int
id|ds_start_pulse
c_func
(paren
r_struct
id|ds_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|ds_set_speed
c_func
(paren
r_struct
id|ds_device
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|ds_reset
c_func
(paren
r_struct
id|ds_device
op_star
comma
r_struct
id|ds_status
op_star
)paren
suffix:semicolon
r_int
id|ds_detect
c_func
(paren
r_struct
id|ds_device
op_star
comma
r_struct
id|ds_status
op_star
)paren
suffix:semicolon
r_int
id|ds_stop_pulse
c_func
(paren
r_struct
id|ds_device
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|ds_device
op_star
id|ds_get_device
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ds_put_device
c_func
(paren
r_struct
id|ds_device
op_star
)paren
suffix:semicolon
r_int
id|ds_write_block
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|ds_read_block
c_func
(paren
r_struct
id|ds_device
op_star
comma
id|u8
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __DSCORE_H */
eof
