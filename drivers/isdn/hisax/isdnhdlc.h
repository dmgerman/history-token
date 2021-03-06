multiline_comment|/*&n; * isdnhdlc.h  --  General purpose ISDN HDLC decoder.&n; *&n; * Implementation of a HDLC decoder/encoder in software.&n; * Neccessary because some ISDN devices don&squot;t have HDLC&n; * controllers. Also included: a bit reversal table.&n; *&n; *Copyright (C) 2002    Wolfgang M&#xfffd;es      &lt;wolfgang@iksw-muees.de&gt;&n; *&t;&t;2001 &t;Frode Isaksen      &lt;fisaksen@bewan.com&gt;&n; *              2001 &t;Kai Germaschewski  &lt;kai.germaschewski@gmx.de&gt;&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ISDNHDLC_H__
DECL|macro|__ISDNHDLC_H__
mdefine_line|#define __ISDNHDLC_H__
DECL|struct|isdnhdlc_vars
r_struct
id|isdnhdlc_vars
(brace
DECL|member|bit_shift
r_int
id|bit_shift
suffix:semicolon
DECL|member|hdlc_bits1
r_int
id|hdlc_bits1
suffix:semicolon
DECL|member|data_bits
r_int
id|data_bits
suffix:semicolon
DECL|member|ffbit_shift
r_int
id|ffbit_shift
suffix:semicolon
singleline_comment|// encoding only
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|dstpos
r_int
id|dstpos
suffix:semicolon
DECL|member|crc
r_int
r_int
id|crc
suffix:semicolon
DECL|member|cbin
r_int
r_char
id|cbin
suffix:semicolon
DECL|member|shift_reg
r_int
r_char
id|shift_reg
suffix:semicolon
DECL|member|ffvalue
r_int
r_char
id|ffvalue
suffix:semicolon
DECL|member|data_received
r_int
id|data_received
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// set if transferring data
DECL|member|dchannel
r_int
id|dchannel
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// set if D channel (send idle instead of flags)
DECL|member|do_adapt56
r_int
id|do_adapt56
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// set if 56K adaptation
DECL|member|do_closing
r_int
id|do_closing
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// set if in closing phase (need to send CRC + flag
)brace
suffix:semicolon
multiline_comment|/*&n;  The return value from isdnhdlc_decode is&n;  the frame length, 0 if no complete frame was decoded,&n;  or a negative error number&n;*/
DECL|macro|HDLC_FRAMING_ERROR
mdefine_line|#define HDLC_FRAMING_ERROR     1
DECL|macro|HDLC_CRC_ERROR
mdefine_line|#define HDLC_CRC_ERROR         2
DECL|macro|HDLC_LENGTH_ERROR
mdefine_line|#define HDLC_LENGTH_ERROR      3
r_extern
r_const
r_int
r_char
id|isdnhdlc_bit_rev_tab
(braket
l_int|256
)braket
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|isdnhdlc_encode
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
suffix:semicolon
macro_line|#endif /* __ISDNHDLC_H__ */
eof
