multiline_comment|/*&n; * Driver for ST5481 USB ISDN modem&n; *&n; * Author       Frode Isaksen&n; * Copyright    2001 by Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 by Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/crc-ccitt.h&gt;
macro_line|#include &quot;st5481_hdlc.h&quot;
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
r_void
DECL|function|hdlc_rcv_init
id|hdlc_rcv_init
c_func
(paren
r_struct
id|hdlc_vars
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
r_void
DECL|function|hdlc_out_init
id|hdlc_out_init
c_func
(paren
r_struct
id|hdlc_vars
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
multiline_comment|/*&n;  hdlc_decode - decodes HDLC frames from a transparent bit stream.&n;&n;  The source buffer is scanned for valid HDLC frames looking for&n;  flags (01111110) to indicate the start of a frame. If the start of&n;  the frame is found, the bit stuffing is removed (0 after 5 1&squot;s).&n;  When a new flag is found, the complete frame has been received&n;  and the CRC is checked.&n;  If a valid frame is found, the function returns the frame length &n;  excluding the CRC with the bit HDLC_END_OF_FRAME set.&n;  If the beginning of a valid frame is found, the function returns&n;  the length. &n;  If a framing error is found (too many 1s and not a flag) the function &n;  returns the length with the bit HDLC_FRAMING_ERROR set.&n;  If a CRC error is found the function returns the length with the&n;  bit HDLC_CRC_ERROR set.&n;  If the frame length exceeds the destination buffer size, the function&n;  returns the length with the bit HDLC_LENGTH_ERROR set.&n;&n;  src - source buffer&n;  slen - source buffer length&n;  count - number of bytes removed (decoded) from the source buffer&n;  dst _ destination buffer&n;  dsize - destination buffer size&n;  returns - number of decoded bytes in the destination buffer and status&n;  flag.&n; */
DECL|function|hdlc_decode
r_int
id|hdlc_decode
c_func
(paren
r_struct
id|hdlc_vars
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
id|dsize
op_decrement
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
multiline_comment|/*&n;  hdlc_encode - encodes HDLC frames to a transparent bit stream.&n;&n;  The bit stream starts with a beginning flag (01111110). After&n;  that each byte is added to the bit stream with bit stuffing added&n;  (0 after 5 1&squot;s).&n;  When the last byte has been removed from the source buffer, the&n;  CRC (2 bytes is added) and the frame terminates with the ending flag.&n;  For the dchannel, the idle character (all 1&squot;s) is also added at the end.&n;  If this function is called with empty source buffer (slen=0), flags or&n;  idle character will be generated.&n; &n;  src - source buffer&n;  slen - source buffer length&n;  count - number of bytes removed (encoded) from source buffer&n;  dst _ destination buffer&n;  dsize - destination buffer size&n;  returns - number of encoded bytes in the destination buffer&n;*/
DECL|function|hdlc_encode
r_int
id|hdlc_encode
c_func
(paren
r_struct
id|hdlc_vars
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
eof
