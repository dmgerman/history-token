multiline_comment|/*&n; * isdnhdlc.c  --  General purpose ISDN HDLC decoder.&n; *&n; *Copyright (C) 2002&t;Wolfgang M&#xfffd;es      &lt;wolfgang@iksw-muees.de&gt;&n; *&t;&t;2001 &t;Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 &t;Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/crc-ccitt.h&gt;
macro_line|#include &quot;isdnhdlc.h&quot;
multiline_comment|/*-------------------------------------------------------------------*/
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Wolfgang M&#xfffd;es &lt;wolfgang@iksw-muees.de&gt;, &quot;
l_string|&quot;Frode Isaksen &lt;fisaksen@bewan.com&gt;, &quot;
l_string|&quot;Kai Germaschewski &lt;kai.germaschewski@gmx.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;General purpose ISDN HDLC decoder&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------*/
multiline_comment|/* bit swap table.&n; * Very handy for devices with different bit order,&n; * and neccessary for each transparent B-channel access for all&n; * devices which works with this HDLC decoder without bit reversal.&n; */
DECL|variable|isdnhdlc_bit_rev_tab
r_const
r_int
r_char
id|isdnhdlc_bit_rev_tab
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x80
comma
l_int|0x40
comma
l_int|0xC0
comma
l_int|0x20
comma
l_int|0xA0
comma
l_int|0x60
comma
l_int|0xE0
comma
l_int|0x10
comma
l_int|0x90
comma
l_int|0x50
comma
l_int|0xD0
comma
l_int|0x30
comma
l_int|0xB0
comma
l_int|0x70
comma
l_int|0xF0
comma
l_int|0x08
comma
l_int|0x88
comma
l_int|0x48
comma
l_int|0xC8
comma
l_int|0x28
comma
l_int|0xA8
comma
l_int|0x68
comma
l_int|0xE8
comma
l_int|0x18
comma
l_int|0x98
comma
l_int|0x58
comma
l_int|0xD8
comma
l_int|0x38
comma
l_int|0xB8
comma
l_int|0x78
comma
l_int|0xF8
comma
l_int|0x04
comma
l_int|0x84
comma
l_int|0x44
comma
l_int|0xC4
comma
l_int|0x24
comma
l_int|0xA4
comma
l_int|0x64
comma
l_int|0xE4
comma
l_int|0x14
comma
l_int|0x94
comma
l_int|0x54
comma
l_int|0xD4
comma
l_int|0x34
comma
l_int|0xB4
comma
l_int|0x74
comma
l_int|0xF4
comma
l_int|0x0C
comma
l_int|0x8C
comma
l_int|0x4C
comma
l_int|0xCC
comma
l_int|0x2C
comma
l_int|0xAC
comma
l_int|0x6C
comma
l_int|0xEC
comma
l_int|0x1C
comma
l_int|0x9C
comma
l_int|0x5C
comma
l_int|0xDC
comma
l_int|0x3C
comma
l_int|0xBC
comma
l_int|0x7C
comma
l_int|0xFC
comma
l_int|0x02
comma
l_int|0x82
comma
l_int|0x42
comma
l_int|0xC2
comma
l_int|0x22
comma
l_int|0xA2
comma
l_int|0x62
comma
l_int|0xE2
comma
l_int|0x12
comma
l_int|0x92
comma
l_int|0x52
comma
l_int|0xD2
comma
l_int|0x32
comma
l_int|0xB2
comma
l_int|0x72
comma
l_int|0xF2
comma
l_int|0x0A
comma
l_int|0x8A
comma
l_int|0x4A
comma
l_int|0xCA
comma
l_int|0x2A
comma
l_int|0xAA
comma
l_int|0x6A
comma
l_int|0xEA
comma
l_int|0x1A
comma
l_int|0x9A
comma
l_int|0x5A
comma
l_int|0xDA
comma
l_int|0x3A
comma
l_int|0xBA
comma
l_int|0x7A
comma
l_int|0xFA
comma
l_int|0x06
comma
l_int|0x86
comma
l_int|0x46
comma
l_int|0xC6
comma
l_int|0x26
comma
l_int|0xA6
comma
l_int|0x66
comma
l_int|0xE6
comma
l_int|0x16
comma
l_int|0x96
comma
l_int|0x56
comma
l_int|0xD6
comma
l_int|0x36
comma
l_int|0xB6
comma
l_int|0x76
comma
l_int|0xF6
comma
l_int|0x0E
comma
l_int|0x8E
comma
l_int|0x4E
comma
l_int|0xCE
comma
l_int|0x2E
comma
l_int|0xAE
comma
l_int|0x6E
comma
l_int|0xEE
comma
l_int|0x1E
comma
l_int|0x9E
comma
l_int|0x5E
comma
l_int|0xDE
comma
l_int|0x3E
comma
l_int|0xBE
comma
l_int|0x7E
comma
l_int|0xFE
comma
l_int|0x01
comma
l_int|0x81
comma
l_int|0x41
comma
l_int|0xC1
comma
l_int|0x21
comma
l_int|0xA1
comma
l_int|0x61
comma
l_int|0xE1
comma
l_int|0x11
comma
l_int|0x91
comma
l_int|0x51
comma
l_int|0xD1
comma
l_int|0x31
comma
l_int|0xB1
comma
l_int|0x71
comma
l_int|0xF1
comma
l_int|0x09
comma
l_int|0x89
comma
l_int|0x49
comma
l_int|0xC9
comma
l_int|0x29
comma
l_int|0xA9
comma
l_int|0x69
comma
l_int|0xE9
comma
l_int|0x19
comma
l_int|0x99
comma
l_int|0x59
comma
l_int|0xD9
comma
l_int|0x39
comma
l_int|0xB9
comma
l_int|0x79
comma
l_int|0xF9
comma
l_int|0x05
comma
l_int|0x85
comma
l_int|0x45
comma
l_int|0xC5
comma
l_int|0x25
comma
l_int|0xA5
comma
l_int|0x65
comma
l_int|0xE5
comma
l_int|0x15
comma
l_int|0x95
comma
l_int|0x55
comma
l_int|0xD5
comma
l_int|0x35
comma
l_int|0xB5
comma
l_int|0x75
comma
l_int|0xF5
comma
l_int|0x0D
comma
l_int|0x8D
comma
l_int|0x4D
comma
l_int|0xCD
comma
l_int|0x2D
comma
l_int|0xAD
comma
l_int|0x6D
comma
l_int|0xED
comma
l_int|0x1D
comma
l_int|0x9D
comma
l_int|0x5D
comma
l_int|0xDD
comma
l_int|0x3D
comma
l_int|0xBD
comma
l_int|0x7D
comma
l_int|0xFD
comma
l_int|0x03
comma
l_int|0x83
comma
l_int|0x43
comma
l_int|0xC3
comma
l_int|0x23
comma
l_int|0xA3
comma
l_int|0x63
comma
l_int|0xE3
comma
l_int|0x13
comma
l_int|0x93
comma
l_int|0x53
comma
l_int|0xD3
comma
l_int|0x33
comma
l_int|0xB3
comma
l_int|0x73
comma
l_int|0xF3
comma
l_int|0x0B
comma
l_int|0x8B
comma
l_int|0x4B
comma
l_int|0xCB
comma
l_int|0x2B
comma
l_int|0xAB
comma
l_int|0x6B
comma
l_int|0xEB
comma
l_int|0x1B
comma
l_int|0x9B
comma
l_int|0x5B
comma
l_int|0xDB
comma
l_int|0x3B
comma
l_int|0xBB
comma
l_int|0x7B
comma
l_int|0xFB
comma
l_int|0x07
comma
l_int|0x87
comma
l_int|0x47
comma
l_int|0xC7
comma
l_int|0x27
comma
l_int|0xA7
comma
l_int|0x67
comma
l_int|0xE7
comma
l_int|0x17
comma
l_int|0x97
comma
l_int|0x57
comma
l_int|0xD7
comma
l_int|0x37
comma
l_int|0xB7
comma
l_int|0x77
comma
l_int|0xF7
comma
l_int|0x0F
comma
l_int|0x8F
comma
l_int|0x4F
comma
l_int|0xCF
comma
l_int|0x2F
comma
l_int|0xAF
comma
l_int|0x6F
comma
l_int|0xEF
comma
l_int|0x1F
comma
l_int|0x9F
comma
l_int|0x5F
comma
l_int|0xDF
comma
l_int|0x3F
comma
l_int|0xBF
comma
l_int|0x7F
comma
l_int|0xFF
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|HDLC_FAST_IDLE
DECL|enumerator|HDLC_GET_FLAG_B0
DECL|enumerator|HDLC_GETFLAG_B1A6
DECL|enumerator|HDLC_GETFLAG_B7
id|HDLC_FAST_IDLE
comma
id|HDLC_GET_FLAG_B0
comma
id|HDLC_GETFLAG_B1A6
comma
id|HDLC_GETFLAG_B7
comma
DECL|enumerator|HDLC_GET_DATA
DECL|enumerator|HDLC_FAST_FLAG
id|HDLC_GET_DATA
comma
id|HDLC_FAST_FLAG
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|HDLC_SEND_DATA
DECL|enumerator|HDLC_SEND_CRC1
DECL|enumerator|HDLC_SEND_FAST_FLAG
id|HDLC_SEND_DATA
comma
id|HDLC_SEND_CRC1
comma
id|HDLC_SEND_FAST_FLAG
comma
DECL|enumerator|HDLC_SEND_FIRST_FLAG
DECL|enumerator|HDLC_SEND_CRC2
DECL|enumerator|HDLC_SEND_CLOSING_FLAG
id|HDLC_SEND_FIRST_FLAG
comma
id|HDLC_SEND_CRC2
comma
id|HDLC_SEND_CLOSING_FLAG
comma
DECL|enumerator|HDLC_SEND_IDLE1
DECL|enumerator|HDLC_SEND_FAST_IDLE
DECL|enumerator|HDLC_SENDFLAG_B0
id|HDLC_SEND_IDLE1
comma
id|HDLC_SEND_FAST_IDLE
comma
id|HDLC_SENDFLAG_B0
comma
DECL|enumerator|HDLC_SENDFLAG_B1A6
DECL|enumerator|HDLC_SENDFLAG_B7
DECL|enumerator|STOPPED
id|HDLC_SENDFLAG_B1A6
comma
id|HDLC_SENDFLAG_B7
comma
id|STOPPED
)brace
suffix:semicolon
DECL|function|isdnhdlc_rcv_init
r_void
id|isdnhdlc_rcv_init
(paren
r_struct
id|isdnhdlc_vars
op_star
id|hdlc
comma
r_int
id|do_adapt56
)paren
(brace
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;ffbit_shift
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_GET_DATA
suffix:semicolon
id|hdlc-&gt;do_adapt56
op_assign
id|do_adapt56
suffix:semicolon
id|hdlc-&gt;dchannel
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;crc
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;cbin
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;shift_reg
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;ffvalue
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;dstpos
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|isdnhdlc_out_init
r_void
id|isdnhdlc_out_init
(paren
r_struct
id|isdnhdlc_vars
op_star
id|hdlc
comma
r_int
id|is_d_channel
comma
r_int
id|do_adapt56
)paren
(brace
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;ffbit_shift
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;do_closing
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;ffvalue
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_d_channel
)paren
(brace
id|hdlc-&gt;dchannel
op_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FIRST_FLAG
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;dchannel
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FAST_FLAG
suffix:semicolon
id|hdlc-&gt;ffvalue
op_assign
l_int|0x7e
suffix:semicolon
)brace
id|hdlc-&gt;cbin
op_assign
l_int|0x7e
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|do_adapt56
)paren
(brace
id|hdlc-&gt;do_adapt56
op_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SENDFLAG_B0
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;do_adapt56
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|8
suffix:semicolon
)brace
id|hdlc-&gt;shift_reg
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;  isdnhdlc_decode - decodes HDLC frames from a transparent bit stream.&n;&n;  The source buffer is scanned for valid HDLC frames looking for&n;  flags (01111110) to indicate the start of a frame. If the start of&n;  the frame is found, the bit stuffing is removed (0 after 5 1&squot;s).&n;  When a new flag is found, the complete frame has been received&n;  and the CRC is checked.&n;  If a valid frame is found, the function returns the frame length&n;  excluding the CRC with the bit HDLC_END_OF_FRAME set.&n;  If the beginning of a valid frame is found, the function returns&n;  the length.&n;  If a framing error is found (too many 1s and not a flag) the function&n;  returns the length with the bit HDLC_FRAMING_ERROR set.&n;  If a CRC error is found the function returns the length with the&n;  bit HDLC_CRC_ERROR set.&n;  If the frame length exceeds the destination buffer size, the function&n;  returns the length with the bit HDLC_LENGTH_ERROR set.&n;&n;  src - source buffer&n;  slen - source buffer length&n;  count - number of bytes removed (decoded) from the source buffer&n;  dst _ destination buffer&n;  dsize - destination buffer size&n;  returns - number of decoded bytes in the destination buffer and status&n;  flag.&n; */
DECL|function|isdnhdlc_decode
r_int
id|isdnhdlc_decode
(paren
r_struct
id|isdnhdlc_vars
op_star
id|hdlc
comma
r_const
r_int
r_char
op_star
id|src
comma
r_int
id|slen
comma
r_int
op_star
id|count
comma
r_int
r_char
op_star
id|dst
comma
r_int
id|dsize
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_static
r_const
r_int
r_char
id|fast_flag
(braket
)braket
op_assign
initialization_block
suffix:semicolon
r_static
r_const
r_int
r_char
id|fast_flag_value
(braket
)braket
op_assign
initialization_block
suffix:semicolon
r_static
r_const
r_int
r_char
id|fast_abort
(braket
)braket
op_assign
initialization_block
suffix:semicolon
op_star
id|count
op_assign
id|slen
suffix:semicolon
r_while
c_loop
(paren
id|slen
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;cbin
op_assign
op_star
id|src
op_increment
suffix:semicolon
id|slen
op_decrement
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;do_adapt56
)paren
(brace
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|hdlc-&gt;state
)paren
(brace
r_case
id|STOPPED
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|HDLC_FAST_IDLE
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_eq
l_int|0xff
)paren
(brace
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hdlc-&gt;state
op_assign
id|HDLC_GET_FLAG_B0
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDLC_GET_FLAG_B0
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hdlc-&gt;cbin
op_amp
l_int|0x80
)paren
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GETFLAG_B1A6
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;do_adapt56
)paren
(brace
r_if
c_cond
(paren
op_increment
id|hdlc-&gt;hdlc_bits1
op_ge
l_int|8
)paren
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|1
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_FAST_IDLE
suffix:semicolon
)brace
)brace
)brace
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDLC_GETFLAG_B1A6
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_amp
l_int|0x80
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
op_eq
l_int|6
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GETFLAG_B7
suffix:semicolon
)brace
)brace
r_else
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
)brace
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDLC_GETFLAG_B7
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_amp
l_int|0x80
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GET_FLAG_B0
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GET_DATA
suffix:semicolon
id|hdlc-&gt;crc
op_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;shift_reg
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
)brace
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDLC_GET_DATA
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_amp
l_int|0x80
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
)paren
(brace
r_case
l_int|6
suffix:colon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;data_received
)paren
(brace
singleline_comment|// bad frame
id|status
op_assign
op_minus
id|HDLC_FRAMING_ERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;do_adapt56
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_eq
id|fast_abort
(braket
id|hdlc-&gt;bit_shift
op_plus
l_int|1
)braket
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_FAST_IDLE
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GET_FLAG_B0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;shift_reg
op_or_assign
l_int|0x80
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
)paren
(brace
r_case
l_int|5
suffix:colon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;data_received
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;dstpos
OL
l_int|2
)paren
(brace
id|status
op_assign
op_minus
id|HDLC_FRAMING_ERROR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hdlc-&gt;crc
op_ne
l_int|0xf0b8
)paren
(brace
singleline_comment|// crc error
id|status
op_assign
op_minus
id|HDLC_CRC_ERROR
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// remove CRC
id|hdlc-&gt;dstpos
op_sub_assign
l_int|2
suffix:semicolon
singleline_comment|// good frame
id|status
op_assign
id|hdlc-&gt;dstpos
suffix:semicolon
)brace
)brace
id|hdlc-&gt;crc
op_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;shift_reg
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;do_adapt56
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_eq
id|fast_flag
(braket
id|hdlc-&gt;bit_shift
)braket
)paren
(brace
id|hdlc-&gt;ffvalue
op_assign
id|fast_flag_value
(braket
id|hdlc-&gt;bit_shift
)braket
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_FAST_FLAG
suffix:semicolon
id|hdlc-&gt;ffbit_shift
op_assign
id|hdlc-&gt;bit_shift
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GET_DATA
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GET_DATA
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
)paren
(brace
id|hdlc-&gt;dstpos
op_assign
l_int|0
suffix:semicolon
op_star
id|count
op_sub_assign
id|slen
suffix:semicolon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;data_bits
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;crc
op_assign
id|crc_ccitt_byte
c_func
(paren
id|hdlc-&gt;crc
comma
id|hdlc-&gt;shift_reg
)paren
suffix:semicolon
singleline_comment|// good byte received
r_if
c_cond
(paren
id|hdlc-&gt;dstpos
OL
id|dsize
)paren
(brace
id|dst
(braket
id|hdlc-&gt;dstpos
op_increment
)braket
op_assign
id|hdlc-&gt;shift_reg
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// frame too long
id|status
op_assign
op_minus
id|HDLC_LENGTH_ERROR
suffix:semicolon
id|hdlc-&gt;dstpos
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDLC_FAST_FLAG
suffix:colon
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_eq
id|hdlc-&gt;ffvalue
)paren
(brace
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hdlc-&gt;cbin
op_eq
l_int|0xff
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_FAST_IDLE
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hdlc-&gt;ffbit_shift
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_GETFLAG_B7
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;shift_reg
op_assign
id|fast_abort
(braket
id|hdlc-&gt;ffbit_shift
op_minus
l_int|1
)braket
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
id|hdlc-&gt;ffbit_shift
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
OL
l_int|0
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
)brace
id|hdlc-&gt;data_bits
op_assign
id|hdlc-&gt;ffbit_shift
op_minus
l_int|1
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_GET_DATA
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
op_star
id|count
op_sub_assign
id|slen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;  isdnhdlc_encode - encodes HDLC frames to a transparent bit stream.&n;&n;  The bit stream starts with a beginning flag (01111110). After&n;  that each byte is added to the bit stream with bit stuffing added&n;  (0 after 5 1&squot;s).&n;  When the last byte has been removed from the source buffer, the&n;  CRC (2 bytes is added) and the frame terminates with the ending flag.&n;  For the dchannel, the idle character (all 1&squot;s) is also added at the end.&n;  If this function is called with empty source buffer (slen=0), flags or&n;  idle character will be generated.&n;&n;  src - source buffer&n;  slen - source buffer length&n;  count - number of bytes removed (encoded) from source buffer&n;  dst _ destination buffer&n;  dsize - destination buffer size&n;  returns - number of encoded bytes in the destination buffer&n;*/
DECL|function|isdnhdlc_encode
r_int
id|isdnhdlc_encode
c_func
(paren
r_struct
id|isdnhdlc_vars
op_star
id|hdlc
comma
r_const
r_int
r_char
op_star
id|src
comma
r_int
r_int
id|slen
comma
r_int
op_star
id|count
comma
r_int
r_char
op_star
id|dst
comma
r_int
id|dsize
)paren
(brace
r_static
r_const
r_int
r_char
id|xfast_flag_value
(braket
)braket
op_assign
(brace
l_int|0x7e
comma
l_int|0x3f
comma
l_int|0x9f
comma
l_int|0xcf
comma
l_int|0xe7
comma
l_int|0xf3
comma
l_int|0xf9
comma
l_int|0xfc
comma
l_int|0x7e
)brace
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
op_star
id|count
op_assign
id|slen
suffix:semicolon
r_while
c_loop
(paren
id|dsize
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|slen
op_logical_and
op_logical_neg
id|hdlc-&gt;do_closing
)paren
(brace
id|hdlc-&gt;shift_reg
op_assign
op_star
id|src
op_increment
suffix:semicolon
id|slen
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|slen
op_eq
l_int|0
)paren
id|hdlc-&gt;do_closing
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* closing sequence, CRC + flag(s) */
id|hdlc-&gt;bit_shift
op_assign
l_int|8
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hdlc-&gt;state
op_eq
id|HDLC_SEND_DATA
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;data_received
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_CRC1
suffix:semicolon
id|hdlc-&gt;crc
op_xor_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|8
suffix:semicolon
id|hdlc-&gt;shift_reg
op_assign
id|hdlc-&gt;crc
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;do_adapt56
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FAST_FLAG
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SENDFLAG_B0
suffix:semicolon
)brace
)brace
)brace
)brace
r_switch
c_cond
(paren
id|hdlc-&gt;state
)paren
(brace
r_case
id|STOPPED
suffix:colon
r_while
c_loop
(paren
id|dsize
op_decrement
)paren
op_star
id|dst
op_increment
op_assign
l_int|0xff
suffix:semicolon
r_return
id|dsize
suffix:semicolon
r_case
id|HDLC_SEND_FAST_FLAG
suffix:colon
id|hdlc-&gt;do_closing
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|slen
op_eq
l_int|0
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|hdlc-&gt;ffvalue
suffix:semicolon
id|len
op_increment
suffix:semicolon
id|dsize
op_decrement
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;cbin
op_assign
id|hdlc-&gt;ffvalue
op_rshift
(paren
l_int|8
op_minus
id|hdlc-&gt;data_bits
)paren
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_DATA
suffix:semicolon
id|hdlc-&gt;crc
op_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SENDFLAG_B0
suffix:colon
id|hdlc-&gt;do_closing
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SENDFLAG_B1A6
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HDLC_SENDFLAG_B1A6
suffix:colon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|hdlc-&gt;hdlc_bits1
op_eq
l_int|6
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SENDFLAG_B7
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SENDFLAG_B7
suffix:colon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|slen
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SENDFLAG_B0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_DATA
suffix:semicolon
id|hdlc-&gt;crc
op_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_FIRST_FLAG
suffix:colon
id|hdlc-&gt;data_received
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;data_bits
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_DATA
suffix:semicolon
id|hdlc-&gt;crc
op_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;shift_reg
op_amp
l_int|0x01
)paren
(brace
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
)brace
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_DATA
suffix:semicolon
id|hdlc-&gt;crc
op_assign
l_int|0xffff
suffix:semicolon
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_DATA
suffix:colon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
op_eq
l_int|5
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;crc
op_assign
id|crc_ccitt_byte
c_func
(paren
id|hdlc-&gt;crc
comma
id|hdlc-&gt;shift_reg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;shift_reg
op_amp
l_int|0x01
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_increment
suffix:semicolon
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_CRC1
suffix:colon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
op_eq
l_int|5
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;shift_reg
op_amp
l_int|0x01
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_increment
suffix:semicolon
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;shift_reg
op_assign
(paren
id|hdlc-&gt;crc
op_rshift
l_int|8
)paren
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_CRC2
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|8
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_CRC2
suffix:colon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
op_eq
l_int|5
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;shift_reg
op_amp
l_int|0x01
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_increment
suffix:semicolon
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;shift_reg
op_assign
l_int|0x7e
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_CLOSING_FLAG
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|8
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_CLOSING_FLAG
suffix:colon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;hdlc_bits1
op_eq
l_int|5
)paren
(brace
id|hdlc-&gt;hdlc_bits1
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;shift_reg
op_amp
l_int|0x01
)paren
(brace
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
)brace
id|hdlc-&gt;shift_reg
op_rshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;ffvalue
op_assign
id|xfast_flag_value
(braket
id|hdlc-&gt;data_bits
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;dchannel
)paren
(brace
id|hdlc-&gt;ffvalue
op_assign
l_int|0x7e
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_IDLE1
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|8
op_minus
id|hdlc-&gt;data_bits
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FAST_IDLE
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|hdlc-&gt;do_adapt56
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FAST_FLAG
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SENDFLAG_B0
suffix:semicolon
id|hdlc-&gt;data_received
op_assign
l_int|0
suffix:semicolon
)brace
singleline_comment|// Finished with this frame, send flags
r_if
c_cond
(paren
id|dsize
OG
l_int|1
)paren
id|dsize
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_IDLE1
suffix:colon
id|hdlc-&gt;do_closing
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
id|hdlc-&gt;bit_shift
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|0
)paren
(brace
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FAST_IDLE
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HDLC_SEND_FAST_IDLE
suffix:colon
id|hdlc-&gt;do_closing
op_assign
l_int|0
suffix:semicolon
id|hdlc-&gt;cbin
op_assign
l_int|0xff
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;bit_shift
op_eq
l_int|8
)paren
(brace
id|hdlc-&gt;cbin
op_assign
l_int|0x7e
suffix:semicolon
id|hdlc-&gt;state
op_assign
id|HDLC_SEND_FIRST_FLAG
suffix:semicolon
)brace
r_else
(brace
op_star
id|dst
op_increment
op_assign
id|hdlc-&gt;cbin
suffix:semicolon
id|hdlc-&gt;bit_shift
op_assign
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|len
op_increment
suffix:semicolon
id|dsize
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdlc-&gt;do_adapt56
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;data_bits
op_eq
l_int|7
)paren
(brace
id|hdlc-&gt;cbin
op_lshift_assign
l_int|1
suffix:semicolon
id|hdlc-&gt;cbin
op_increment
suffix:semicolon
id|hdlc-&gt;data_bits
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|hdlc-&gt;data_bits
op_eq
l_int|8
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|hdlc-&gt;cbin
suffix:semicolon
id|hdlc-&gt;data_bits
op_assign
l_int|0
suffix:semicolon
id|len
op_increment
suffix:semicolon
id|dsize
op_decrement
suffix:semicolon
)brace
)brace
op_star
id|count
op_sub_assign
id|slen
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|isdnhdlc_bit_rev_tab
id|EXPORT_SYMBOL
c_func
(paren
id|isdnhdlc_bit_rev_tab
)paren
suffix:semicolon
DECL|variable|isdnhdlc_rcv_init
id|EXPORT_SYMBOL
c_func
(paren
id|isdnhdlc_rcv_init
)paren
suffix:semicolon
DECL|variable|isdnhdlc_decode
id|EXPORT_SYMBOL
c_func
(paren
id|isdnhdlc_decode
)paren
suffix:semicolon
DECL|variable|isdnhdlc_out_init
id|EXPORT_SYMBOL
c_func
(paren
id|isdnhdlc_out_init
)paren
suffix:semicolon
DECL|variable|isdnhdlc_encode
id|EXPORT_SYMBOL
c_func
(paren
id|isdnhdlc_encode
)paren
suffix:semicolon
eof
