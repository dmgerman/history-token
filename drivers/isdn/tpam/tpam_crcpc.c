multiline_comment|/* $Id: tpam_crcpc.c,v 1.1.2.2 2001/09/23 22:25:03 kai Exp $&n; *&n; * Turbo PAM ISDN driver for Linux. (Kernel Driver - CRC encoding)&n; *&n; * Copyright 1998-2000 AUVERTECH T&#xfffd;l&#xfffd;com&n; * Copyright 2001 Stelian Pop &lt;stelian.pop@fr.alcove.com&gt;, Alc&#xfffd;ve&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * For all support questions please contact: &lt;support@auvertech.fr&gt;&n; *&n; */
multiline_comment|/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++&n;&n;Module Name:&n;&n;    crcpc.c&n;&n;Abstract:&n;&n;    Modem HDLC coding&n;    Software HDLC coding / decoding&n;&n;Revision History:&n;&n;---------------------------------------------------------------------------*/
macro_line|#include &quot;tpam.h&quot;
DECL|macro|HDLC_CTRL_CHAR_CMPL_MASK
mdefine_line|#define  HDLC_CTRL_CHAR_CMPL_MASK&t;0x20&t;/* HDLC control character complement mask */
DECL|macro|HDLC_FLAG
mdefine_line|#define  HDLC_FLAG&t;&t;&t;0x7E&t;/* HDLC flag */
DECL|macro|HDLC_CTRL_ESC
mdefine_line|#define  HDLC_CTRL_ESC&t;&t;&t;0x7D&t;/* HDLC control escapr character */
DECL|macro|HDLC_LIKE_FCS_INIT_VAL
mdefine_line|#define  HDLC_LIKE_FCS_INIT_VAL&t;&t;0xFFFF&t;/* FCS initial value (0xFFFF for new equipment or 0) */
DECL|macro|HDLC_FCS_OK
mdefine_line|#define  HDLC_FCS_OK&t;&t;&t;0xF0B8&t;/* This value is the only valid value of FCS */
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
DECL|macro|FALSE
mdefine_line|#define FALSE&t;0
DECL|variable|t_ap_hdlc_like_fcs
r_static
id|u16
id|t_ap_hdlc_like_fcs
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x1189
comma
l_int|0x2312
comma
l_int|0x329b
comma
l_int|0x4624
comma
l_int|0x57ad
comma
l_int|0x6536
comma
l_int|0x74bf
comma
l_int|0x8c48
comma
l_int|0x9dc1
comma
l_int|0xaf5a
comma
l_int|0xbed3
comma
l_int|0xca6c
comma
l_int|0xdbe5
comma
l_int|0xe97e
comma
l_int|0xf8f7
comma
l_int|0x1081
comma
l_int|0x0108
comma
l_int|0x3393
comma
l_int|0x221a
comma
l_int|0x56a5
comma
l_int|0x472c
comma
l_int|0x75b7
comma
l_int|0x643e
comma
l_int|0x9cc9
comma
l_int|0x8d40
comma
l_int|0xbfdb
comma
l_int|0xae52
comma
l_int|0xdaed
comma
l_int|0xcb64
comma
l_int|0xf9ff
comma
l_int|0xe876
comma
l_int|0x2102
comma
l_int|0x308b
comma
l_int|0x0210
comma
l_int|0x1399
comma
l_int|0x6726
comma
l_int|0x76af
comma
l_int|0x4434
comma
l_int|0x55bd
comma
l_int|0xad4a
comma
l_int|0xbcc3
comma
l_int|0x8e58
comma
l_int|0x9fd1
comma
l_int|0xeb6e
comma
l_int|0xfae7
comma
l_int|0xc87c
comma
l_int|0xd9f5
comma
l_int|0x3183
comma
l_int|0x200a
comma
l_int|0x1291
comma
l_int|0x0318
comma
l_int|0x77a7
comma
l_int|0x662e
comma
l_int|0x54b5
comma
l_int|0x453c
comma
l_int|0xbdcb
comma
l_int|0xac42
comma
l_int|0x9ed9
comma
l_int|0x8f50
comma
l_int|0xfbef
comma
l_int|0xea66
comma
l_int|0xd8fd
comma
l_int|0xc974
comma
l_int|0x4204
comma
l_int|0x538d
comma
l_int|0x6116
comma
l_int|0x709f
comma
l_int|0x0420
comma
l_int|0x15a9
comma
l_int|0x2732
comma
l_int|0x36bb
comma
l_int|0xce4c
comma
l_int|0xdfc5
comma
l_int|0xed5e
comma
l_int|0xfcd7
comma
l_int|0x8868
comma
l_int|0x99e1
comma
l_int|0xab7a
comma
l_int|0xbaf3
comma
l_int|0x5285
comma
l_int|0x430c
comma
l_int|0x7197
comma
l_int|0x601e
comma
l_int|0x14a1
comma
l_int|0x0528
comma
l_int|0x37b3
comma
l_int|0x263a
comma
l_int|0xdecd
comma
l_int|0xcf44
comma
l_int|0xfddf
comma
l_int|0xec56
comma
l_int|0x98e9
comma
l_int|0x8960
comma
l_int|0xbbfb
comma
l_int|0xaa72
comma
l_int|0x6306
comma
l_int|0x728f
comma
l_int|0x4014
comma
l_int|0x519d
comma
l_int|0x2522
comma
l_int|0x34ab
comma
l_int|0x0630
comma
l_int|0x17b9
comma
l_int|0xef4e
comma
l_int|0xfec7
comma
l_int|0xcc5c
comma
l_int|0xddd5
comma
l_int|0xa96a
comma
l_int|0xb8e3
comma
l_int|0x8a78
comma
l_int|0x9bf1
comma
l_int|0x7387
comma
l_int|0x620e
comma
l_int|0x5095
comma
l_int|0x411c
comma
l_int|0x35a3
comma
l_int|0x242a
comma
l_int|0x16b1
comma
l_int|0x0738
comma
l_int|0xffcf
comma
l_int|0xee46
comma
l_int|0xdcdd
comma
l_int|0xcd54
comma
l_int|0xb9eb
comma
l_int|0xa862
comma
l_int|0x9af9
comma
l_int|0x8b70
comma
l_int|0x8408
comma
l_int|0x9581
comma
l_int|0xa71a
comma
l_int|0xb693
comma
l_int|0xc22c
comma
l_int|0xd3a5
comma
l_int|0xe13e
comma
l_int|0xf0b7
comma
l_int|0x0840
comma
l_int|0x19c9
comma
l_int|0x2b52
comma
l_int|0x3adb
comma
l_int|0x4e64
comma
l_int|0x5fed
comma
l_int|0x6d76
comma
l_int|0x7cff
comma
l_int|0x9489
comma
l_int|0x8500
comma
l_int|0xb79b
comma
l_int|0xa612
comma
l_int|0xd2ad
comma
l_int|0xc324
comma
l_int|0xf1bf
comma
l_int|0xe036
comma
l_int|0x18c1
comma
l_int|0x0948
comma
l_int|0x3bd3
comma
l_int|0x2a5a
comma
l_int|0x5ee5
comma
l_int|0x4f6c
comma
l_int|0x7df7
comma
l_int|0x6c7e
comma
l_int|0xa50a
comma
l_int|0xb483
comma
l_int|0x8618
comma
l_int|0x9791
comma
l_int|0xe32e
comma
l_int|0xf2a7
comma
l_int|0xc03c
comma
l_int|0xd1b5
comma
l_int|0x2942
comma
l_int|0x38cb
comma
l_int|0x0a50
comma
l_int|0x1bd9
comma
l_int|0x6f66
comma
l_int|0x7eef
comma
l_int|0x4c74
comma
l_int|0x5dfd
comma
l_int|0xb58b
comma
l_int|0xa402
comma
l_int|0x9699
comma
l_int|0x8710
comma
l_int|0xf3af
comma
l_int|0xe226
comma
l_int|0xd0bd
comma
l_int|0xc134
comma
l_int|0x39c3
comma
l_int|0x284a
comma
l_int|0x1ad1
comma
l_int|0x0b58
comma
l_int|0x7fe7
comma
l_int|0x6e6e
comma
l_int|0x5cf5
comma
l_int|0x4d7c
comma
l_int|0xc60c
comma
l_int|0xd785
comma
l_int|0xe51e
comma
l_int|0xf497
comma
l_int|0x8028
comma
l_int|0x91a1
comma
l_int|0xa33a
comma
l_int|0xb2b3
comma
l_int|0x4a44
comma
l_int|0x5bcd
comma
l_int|0x6956
comma
l_int|0x78df
comma
l_int|0x0c60
comma
l_int|0x1de9
comma
l_int|0x2f72
comma
l_int|0x3efb
comma
l_int|0xd68d
comma
l_int|0xc704
comma
l_int|0xf59f
comma
l_int|0xe416
comma
l_int|0x90a9
comma
l_int|0x8120
comma
l_int|0xb3bb
comma
l_int|0xa232
comma
l_int|0x5ac5
comma
l_int|0x4b4c
comma
l_int|0x79d7
comma
l_int|0x685e
comma
l_int|0x1ce1
comma
l_int|0x0d68
comma
l_int|0x3ff3
comma
l_int|0x2e7a
comma
l_int|0xe70e
comma
l_int|0xf687
comma
l_int|0xc41c
comma
l_int|0xd595
comma
l_int|0xa12a
comma
l_int|0xb0a3
comma
l_int|0x8238
comma
l_int|0x93b1
comma
l_int|0x6b46
comma
l_int|0x7acf
comma
l_int|0x4854
comma
l_int|0x59dd
comma
l_int|0x2d62
comma
l_int|0x3ceb
comma
l_int|0x0e70
comma
l_int|0x1ff9
comma
l_int|0xf78f
comma
l_int|0xe606
comma
l_int|0xd49d
comma
l_int|0xc514
comma
l_int|0xb1ab
comma
l_int|0xa022
comma
l_int|0x92b9
comma
l_int|0x8330
comma
l_int|0x7bc7
comma
l_int|0x6a4e
comma
l_int|0x58d5
comma
l_int|0x495c
comma
l_int|0x3de3
comma
l_int|0x2c6a
comma
l_int|0x1ef1
comma
l_int|0x0f78
)brace
suffix:semicolon
DECL|variable|ap_t_ctrl_char_complemented
r_static
id|u8
id|ap_t_ctrl_char_complemented
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* list of characters to complement */
DECL|function|ap_hdlc_like_ctrl_char_list
r_static
r_void
id|ap_hdlc_like_ctrl_char_list
(paren
id|u32
id|ctrl_char
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|256
suffix:semicolon
op_increment
id|i
)paren
id|ap_t_ctrl_char_complemented
(braket
id|i
)braket
op_assign
id|FALSE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
(paren
id|ctrl_char
op_rshift
id|i
)paren
op_amp
l_int|0x0001
)paren
id|ap_t_ctrl_char_complemented
(braket
id|i
)braket
op_assign
id|TRUE
suffix:semicolon
id|ap_t_ctrl_char_complemented
(braket
id|HDLC_FLAG
)braket
op_assign
id|TRUE
suffix:semicolon
id|ap_t_ctrl_char_complemented
(braket
id|HDLC_CTRL_ESC
)braket
op_assign
id|TRUE
suffix:semicolon
)brace
DECL|function|init_CRC
r_void
id|init_CRC
c_func
(paren
)paren
(brace
id|ap_hdlc_like_ctrl_char_list
c_func
(paren
l_int|0xffffffff
)paren
suffix:semicolon
)brace
DECL|function|hdlc_encode_modem
r_void
id|hdlc_encode_modem
c_func
(paren
id|u8
op_star
id|buffer_in
comma
id|u32
id|lng_in
comma
id|u8
op_star
id|buffer_out
comma
id|u32
op_star
id|lng_out
)paren
(brace
id|u16
id|fcs
suffix:semicolon
r_register
id|u8
id|data
suffix:semicolon
r_register
id|u8
op_star
id|p_data_out
op_assign
id|buffer_out
suffix:semicolon
id|fcs
op_assign
id|HDLC_LIKE_FCS_INIT_VAL
suffix:semicolon
multiline_comment|/*&n;&t; *   Insert HDLC flag at the beginning of the frame&n;&t; */
op_star
id|p_data_out
op_increment
op_assign
id|HDLC_FLAG
suffix:semicolon
DECL|macro|ESCAPE_CHAR
mdefine_line|#define ESCAPE_CHAR(data_out, data) &bslash;&n;&t;if (ap_t_ctrl_char_complemented[data]) { &bslash;&n;&t;&t;*data_out++ = HDLC_CTRL_ESC; &bslash;&n;&t;&t;*data_out++ = data ^ 0x20; &bslash;&n;&t;} &bslash;&n;&t;else &bslash;&n;&t;&t;*data_out++ = data;
r_while
c_loop
(paren
id|lng_in
op_decrement
)paren
(brace
id|data
op_assign
op_star
id|buffer_in
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; *   FCS calculation&n;&t;&t; */
id|fcs
op_assign
(paren
id|fcs
op_rshift
l_int|8
)paren
op_xor
id|t_ap_hdlc_like_fcs
(braket
(paren
(paren
id|u8
)paren
(paren
id|fcs
op_xor
id|data
)paren
)paren
op_amp
l_int|0xff
)braket
suffix:semicolon
id|ESCAPE_CHAR
c_func
(paren
id|p_data_out
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Add FCS and closing flag&n;&t; */
id|fcs
op_xor_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// Complement
id|data
op_assign
(paren
id|u8
)paren
(paren
id|fcs
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|ESCAPE_CHAR
c_func
(paren
id|p_data_out
comma
id|data
)paren
suffix:semicolon
id|data
op_assign
(paren
id|u8
)paren
(paren
(paren
id|fcs
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|ESCAPE_CHAR
c_func
(paren
id|p_data_out
comma
id|data
)paren
suffix:semicolon
DECL|macro|ESCAPE_CHAR
macro_line|#undef ESCAPE_CHAR
op_star
id|p_data_out
op_increment
op_assign
id|HDLC_FLAG
suffix:semicolon
op_star
id|lng_out
op_assign
(paren
id|u32
)paren
(paren
id|p_data_out
op_minus
id|buffer_out
)paren
suffix:semicolon
)brace
DECL|function|hdlc_no_accm_encode
r_void
id|hdlc_no_accm_encode
c_func
(paren
id|u8
op_star
id|buffer_in
comma
id|u32
id|lng_in
comma
id|u8
op_star
id|buffer_out
comma
id|u32
op_star
id|lng_out
)paren
(brace
id|u16
id|fcs
suffix:semicolon
r_register
id|u8
id|data
suffix:semicolon
r_register
id|u8
op_star
id|p_data_out
op_assign
id|buffer_out
suffix:semicolon
multiline_comment|/*&n;&t; *   Insert HDLC flag at the beginning of the frame&n;&t; */
id|fcs
op_assign
id|HDLC_LIKE_FCS_INIT_VAL
suffix:semicolon
r_while
c_loop
(paren
id|lng_in
op_decrement
)paren
(brace
id|data
op_assign
op_star
id|buffer_in
op_increment
suffix:semicolon
multiline_comment|/* calculate FCS */
id|fcs
op_assign
(paren
id|fcs
op_rshift
l_int|8
)paren
op_xor
id|t_ap_hdlc_like_fcs
(braket
(paren
(paren
id|u8
)paren
(paren
id|fcs
op_xor
id|data
)paren
)paren
op_amp
l_int|0xff
)braket
suffix:semicolon
op_star
id|p_data_out
op_increment
op_assign
id|data
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Add FCS and closing flag&n;&t; */
id|fcs
op_xor_assign
l_int|0xFFFF
suffix:semicolon
singleline_comment|// Complement
id|data
op_assign
(paren
id|u8
)paren
(paren
id|fcs
)paren
suffix:semicolon
op_star
id|p_data_out
op_increment
op_assign
id|data
suffix:semicolon
id|data
op_assign
(paren
id|u8
)paren
(paren
(paren
id|fcs
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
singleline_comment|// revense MSB / LSB
op_star
id|p_data_out
op_increment
op_assign
id|data
suffix:semicolon
op_star
id|lng_out
op_assign
(paren
id|u32
)paren
(paren
id|p_data_out
op_minus
id|buffer_out
)paren
suffix:semicolon
)brace
DECL|function|hdlc_no_accm_decode
id|u32
id|hdlc_no_accm_decode
c_func
(paren
id|u8
op_star
id|buffer_in
comma
id|u32
id|lng_in
)paren
(brace
id|u16
id|fcs
suffix:semicolon
id|u32
id|lng
op_assign
id|lng_in
suffix:semicolon
r_register
id|u8
id|data
suffix:semicolon
multiline_comment|/*&n;&t; *   Insert HDLC flag at the beginning of the frame&n;&t; */
id|fcs
op_assign
id|HDLC_LIKE_FCS_INIT_VAL
suffix:semicolon
r_while
c_loop
(paren
id|lng_in
op_decrement
)paren
(brace
id|data
op_assign
op_star
id|buffer_in
op_increment
suffix:semicolon
multiline_comment|/* calculate FCS */
id|fcs
op_assign
(paren
id|fcs
op_rshift
l_int|8
)paren
op_xor
id|t_ap_hdlc_like_fcs
(braket
(paren
(paren
id|u8
)paren
(paren
id|fcs
op_xor
id|data
)paren
)paren
op_amp
l_int|0xff
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fcs
op_eq
id|HDLC_FCS_OK
)paren
r_return
(paren
id|lng
op_minus
l_int|2
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
eof
