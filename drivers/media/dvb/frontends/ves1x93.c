multiline_comment|/* &n;    Driver for VES1893 and VES1993 QPSK Frontends&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;    Copyright (C) 2001 Ronny Strutz &lt;3des@elitedvb.de&gt;&n;    Copyright (C) 2002 Dennis Noermann &lt;dennis.noermann@noernet.de&gt;&n;    Copyright (C) 2002-2003 Andreas Oberritter &lt;obi@linuxtv.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk&t;if (debug) printk
DECL|variable|board_type
r_static
r_int
id|board_type
op_assign
l_int|0
suffix:semicolon
DECL|macro|BOARD_SIEMENS_PCI
mdefine_line|#define BOARD_SIEMENS_PCI&t;0
DECL|macro|BOARD_NOKIA_DBOX2
mdefine_line|#define BOARD_NOKIA_DBOX2&t;1
DECL|macro|BOARD_SAGEM_DBOX2
mdefine_line|#define BOARD_SAGEM_DBOX2&t;2
DECL|variable|demod_type
r_static
r_int
id|demod_type
op_assign
l_int|0
suffix:semicolon
DECL|macro|DEMOD_VES1893
mdefine_line|#define DEMOD_VES1893&t;&t;0
DECL|macro|DEMOD_VES1993
mdefine_line|#define DEMOD_VES1993&t;&t;1
DECL|variable|ves1x93_info
r_static
r_struct
id|dvb_frontend_info
id|ves1x93_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VES1x93&quot;
comma
dot
id|type
op_assign
id|FE_QPSK
comma
dot
id|frequency_min
op_assign
l_int|950000
comma
dot
id|frequency_max
op_assign
l_int|2150000
comma
dot
id|frequency_stepsize
op_assign
l_int|250
comma
multiline_comment|/* kHz for QPSK frontends */
dot
id|frequency_tolerance
op_assign
l_int|29500
comma
dot
id|symbol_rate_min
op_assign
l_int|1000000
comma
dot
id|symbol_rate_max
op_assign
l_int|45000000
comma
multiline_comment|/*      .symbol_rate_tolerance&t;=&t;???,*/
dot
id|notifier_delay
op_assign
l_int|50
comma
multiline_comment|/* 1/20 s */
dot
id|caps
op_assign
id|FE_CAN_INVERSION_AUTO
op_or
id|FE_CAN_FEC_1_2
op_or
id|FE_CAN_FEC_2_3
op_or
id|FE_CAN_FEC_3_4
op_or
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_7_8
op_or
id|FE_CAN_FEC_AUTO
op_or
id|FE_CAN_QPSK
)brace
suffix:semicolon
multiline_comment|/**&n; * nokia dbox2 (ves1893) and sagem dbox2 (ves1993)&n; * need bit AGCR[PWMS] set to 1&n; */
DECL|variable|init_1893_tab
r_static
id|u8
id|init_1893_tab
(braket
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0xa4
comma
l_int|0x35
comma
l_int|0x80
comma
l_int|0x2a
comma
l_int|0x0b
comma
l_int|0x55
comma
l_int|0xc4
comma
l_int|0x09
comma
l_int|0x69
comma
l_int|0x00
comma
l_int|0x86
comma
l_int|0x4c
comma
l_int|0x28
comma
l_int|0x7f
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x81
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x21
comma
l_int|0xb0
comma
l_int|0x14
comma
l_int|0x00
comma
l_int|0xdc
comma
l_int|0x00
comma
l_int|0x81
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7f
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|init_1993_tab
r_static
id|u8
id|init_1993_tab
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x9c
comma
l_int|0x35
comma
l_int|0x80
comma
l_int|0x6a
comma
l_int|0x09
comma
l_int|0x72
comma
l_int|0x8c
comma
l_int|0x09
comma
l_int|0x6b
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x4c
comma
l_int|0x08
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x81
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x80
comma
l_int|0x40
comma
l_int|0x21
comma
l_int|0xb0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x81
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x80
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x0e
comma
l_int|0x80
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|init_1x93_tab
r_static
id|u8
op_star
id|init_1x93_tab
suffix:semicolon
DECL|variable|init_1893_wtab
r_static
id|u8
id|init_1893_wtab
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|init_1993_wtab
r_static
id|u8
id|init_1993_wtab
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|struct|ves1x93_state
r_struct
id|ves1x93_state
(brace
DECL|member|inversion
id|fe_spectral_inversion_t
id|inversion
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ves1x93_writereg
r_static
r_int
id|ves1x93_writereg
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|u8
id|buf
(braket
)braket
op_assign
(brace
l_int|0x00
comma
id|reg
comma
id|data
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
l_int|0x08
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|buf
comma
dot
id|len
op_assign
l_int|3
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c-&gt;xfer
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
comma
id|reg
comma
id|data
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_readreg
r_static
id|u8
id|ves1x93_readreg
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
id|reg
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|b0
(braket
)braket
op_assign
(brace
l_int|0x00
comma
id|reg
)brace
suffix:semicolon
id|u8
id|b1
(braket
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
)braket
op_assign
(brace
(brace
dot
id|addr
op_assign
l_int|0x08
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|b0
comma
dot
id|len
op_assign
l_int|2
)brace
comma
(brace
dot
id|addr
op_assign
l_int|0x08
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
id|b1
comma
dot
id|len
op_assign
l_int|1
)brace
)brace
suffix:semicolon
id|ret
op_assign
id|i2c-&gt;xfer
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|2
)paren
id|dprintk
c_func
(paren
l_string|&quot;%s: readreg error (ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_return
id|b1
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|tuner_write
r_static
r_int
id|tuner_write
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
op_star
id|data
comma
id|u8
id|len
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
l_int|0x61
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|data
comma
dot
id|len
op_assign
id|len
)brace
suffix:semicolon
id|ves1x93_writereg
c_func
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x11
)paren
suffix:semicolon
id|ret
op_assign
id|i2c-&gt;xfer
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
suffix:semicolon
id|ves1x93_writereg
c_func
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s: i/o error (ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_return
(paren
id|ret
op_ne
l_int|1
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *   set up the downconverter frequency divisor for a&n; *   reference clock comparision frequency of 125 kHz.&n; */
DECL|function|sp5659_set_tv_freq
r_static
r_int
id|sp5659_set_tv_freq
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|freq
comma
id|u8
id|pwr
)paren
(brace
id|u32
id|div
op_assign
(paren
id|freq
op_plus
l_int|479500
)paren
op_div
l_int|125
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
op_assign
(brace
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
comma
id|div
op_amp
l_int|0xff
comma
l_int|0x95
comma
(paren
id|pwr
op_lshift
l_int|5
)paren
op_or
l_int|0x30
)brace
suffix:semicolon
r_return
id|tuner_write
(paren
id|i2c
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
)brace
DECL|function|tsa5059_set_tv_freq
r_static
r_int
id|tsa5059_set_tv_freq
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|freq
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|freq
op_div_assign
l_int|1000
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|freq
op_rshift
l_int|8
)paren
op_amp
l_int|0x7F
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|freq
op_amp
l_int|0xFF
suffix:semicolon
id|ret
op_assign
id|tuner_write
c_func
(paren
id|i2c
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|tuner_set_tv_freq
r_static
r_int
id|tuner_set_tv_freq
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|freq
comma
id|u8
id|pwr
)paren
(brace
r_if
c_cond
(paren
(paren
id|demod_type
op_eq
id|DEMOD_VES1893
)paren
op_logical_and
(paren
id|board_type
op_eq
id|BOARD_SIEMENS_PCI
)paren
)paren
r_return
id|sp5659_set_tv_freq
(paren
id|i2c
comma
id|freq
comma
id|pwr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|demod_type
op_eq
id|DEMOD_VES1993
)paren
r_return
id|tsa5059_set_tv_freq
(paren
id|i2c
comma
id|freq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ves1x93_init
r_static
r_int
id|ves1x93_init
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|size
suffix:semicolon
id|u8
op_star
id|init_1x93_wtab
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: init chip&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|demod_type
)paren
(brace
r_case
id|DEMOD_VES1893
suffix:colon
id|init_1x93_tab
op_assign
id|init_1893_tab
suffix:semicolon
id|init_1x93_wtab
op_assign
id|init_1893_wtab
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|init_1893_tab
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_type
op_eq
id|BOARD_NOKIA_DBOX2
)paren
id|init_1x93_tab
(braket
l_int|0x05
)braket
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* invert PWM */
r_break
suffix:semicolon
r_case
id|DEMOD_VES1993
suffix:colon
id|init_1x93_tab
op_assign
id|init_1993_tab
suffix:semicolon
id|init_1x93_wtab
op_assign
id|init_1993_wtab
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|init_1993_tab
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_type
op_eq
id|BOARD_SAGEM_DBOX2
)paren
id|init_1x93_tab
(braket
l_int|0x05
)braket
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* invert PWM */
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|init_1x93_wtab
(braket
id|i
)braket
)paren
id|ves1x93_writereg
(paren
id|i2c
comma
id|i
comma
id|init_1x93_tab
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|demod_type
op_eq
id|DEMOD_VES1993
)paren
(brace
r_if
c_cond
(paren
id|board_type
op_eq
id|BOARD_NOKIA_DBOX2
)paren
id|tuner_write
c_func
(paren
id|i2c
comma
l_string|&quot;&bslash;x06&bslash;x5c&bslash;x83&bslash;x60&quot;
comma
l_int|4
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|board_type
op_eq
id|BOARD_SAGEM_DBOX2
)paren
id|tuner_write
c_func
(paren
id|i2c
comma
l_string|&quot;&bslash;x25&bslash;x70&bslash;x92&bslash;x40&quot;
comma
l_int|4
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_clr_bit
r_static
r_int
id|ves1x93_clr_bit
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0
comma
id|init_1x93_tab
(braket
l_int|0
)braket
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0
comma
id|init_1x93_tab
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|dvb_delay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_init_aquire
r_static
r_int
id|ves1x93_init_aquire
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|3
comma
l_int|0x00
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|3
comma
id|init_1x93_tab
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|dvb_delay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_set_inversion
r_static
r_int
id|ves1x93_set_inversion
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_spectral_inversion_t
id|inversion
)paren
(brace
id|u8
id|val
suffix:semicolon
multiline_comment|/*&n;&t; * inversion on/off are interchanged because i and q seem to&n;&t; * be swapped on the hardware&n;&t; */
r_switch
c_cond
(paren
id|inversion
)paren
(brace
r_case
id|INVERSION_OFF
suffix:colon
id|val
op_assign
l_int|0xc0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_ON
suffix:colon
id|val
op_assign
l_int|0x80
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_AUTO
suffix:colon
id|val
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
(paren
id|init_1x93_tab
(braket
l_int|0x0c
)braket
op_amp
l_int|0x3f
)paren
op_or
id|val
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_set_fec
r_static
r_int
id|ves1x93_set_fec
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_code_rate_t
id|fec
)paren
(brace
r_if
c_cond
(paren
id|fec
op_eq
id|FEC_AUTO
)paren
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x0d
comma
l_int|0x08
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fec
template_param
id|FEC_8_9
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x0d
comma
id|fec
op_minus
id|FEC_1_2
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_get_fec
r_static
id|fe_code_rate_t
id|ves1x93_get_fec
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_return
id|FEC_1_2
op_plus
(paren
(paren
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x0d
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_set_symbolrate
r_static
r_int
id|ves1x93_set_symbolrate
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|srate
)paren
(brace
id|u32
id|BDR
suffix:semicolon
id|u32
id|ratio
suffix:semicolon
id|u8
id|ADCONF
comma
id|FCONF
comma
id|FNR
suffix:semicolon
id|u32
id|BDRI
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|u32
id|XIN
comma
id|FIN
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: srate == %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
(paren
r_int
r_int
)paren
id|srate
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|board_type
)paren
(brace
r_case
id|BOARD_SIEMENS_PCI
suffix:colon
id|XIN
op_assign
l_int|90100000UL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOARD_NOKIA_DBOX2
suffix:colon
r_if
c_cond
(paren
id|demod_type
op_eq
id|DEMOD_VES1893
)paren
id|XIN
op_assign
l_int|91000000UL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|demod_type
op_eq
id|DEMOD_VES1993
)paren
id|XIN
op_assign
l_int|96000000UL
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOARD_SAGEM_DBOX2
suffix:colon
id|XIN
op_assign
l_int|92160000UL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srate
OG
id|XIN
op_div
l_int|2
)paren
id|srate
op_assign
id|XIN
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|srate
OL
l_int|500000
)paren
id|srate
op_assign
l_int|500000
suffix:semicolon
DECL|macro|MUL
mdefine_line|#define MUL (1UL&lt;&lt;26)
id|FIN
op_assign
(paren
id|XIN
op_plus
l_int|6000
)paren
op_rshift
l_int|4
suffix:semicolon
id|tmp
op_assign
id|srate
op_lshift
l_int|6
suffix:semicolon
id|ratio
op_assign
id|tmp
op_div
id|FIN
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|FIN
)paren
op_lshift
l_int|8
suffix:semicolon
id|ratio
op_assign
(paren
id|ratio
op_lshift
l_int|8
)paren
op_plus
id|tmp
op_div
id|FIN
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|FIN
)paren
op_lshift
l_int|8
suffix:semicolon
id|ratio
op_assign
(paren
id|ratio
op_lshift
l_int|8
)paren
op_plus
id|tmp
op_div
id|FIN
suffix:semicolon
id|FNR
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|3
)paren
id|FNR
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|11
)paren
op_div
l_int|50
)paren
id|FNR
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|6
)paren
id|FNR
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|9
)paren
id|FNR
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|12
)paren
id|FNR
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|11
)paren
op_div
l_int|200
)paren
id|FNR
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|24
)paren
id|FNR
op_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|27
)paren
op_div
l_int|1000
)paren
id|FNR
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|48
)paren
id|FNR
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|137
)paren
op_div
l_int|10000
)paren
id|FNR
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|FNR
op_eq
l_int|0xff
)paren
(brace
id|ADCONF
op_assign
l_int|0x89
suffix:semicolon
id|FCONF
op_assign
l_int|0x80
suffix:semicolon
id|FNR
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|ADCONF
op_assign
l_int|0x81
suffix:semicolon
id|FCONF
op_assign
l_int|0x88
op_or
(paren
id|FNR
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|FNR
op_amp
l_int|0x01
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
multiline_comment|/*FCONF  = 0x80 | ((FNR &amp; 0x01) &lt;&lt; 5) | (((FNR &gt; 1) &amp; 0x03) &lt;&lt; 3) | ((FNR &gt;&gt; 1) &amp; 0x07);*/
)brace
id|BDR
op_assign
(paren
(paren
(paren
id|ratio
op_lshift
(paren
id|FNR
op_rshift
l_int|1
)paren
)paren
op_rshift
l_int|4
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
id|BDRI
op_assign
(paren
(paren
(paren
id|FIN
op_lshift
l_int|8
)paren
op_div
(paren
(paren
id|srate
op_lshift
(paren
id|FNR
op_rshift
l_int|1
)paren
)paren
op_rshift
l_int|2
)paren
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;FNR= %d&bslash;n&quot;
comma
id|FNR
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;ratio= %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ratio
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BDR= %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|BDR
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BDRI= %02x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|BDRI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BDRI
OG
l_int|0xff
)paren
id|BDRI
op_assign
l_int|0xff
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x06
comma
l_int|0xff
op_amp
id|BDR
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x07
comma
l_int|0xff
op_amp
(paren
id|BDR
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x08
comma
l_int|0x0f
op_amp
(paren
id|BDR
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x09
comma
id|BDRI
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x20
comma
id|ADCONF
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x21
comma
id|FCONF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srate
OL
l_int|6000000
)paren
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x05
comma
id|init_1x93_tab
(braket
l_int|0x05
)braket
op_or
l_int|0x80
)paren
suffix:semicolon
r_else
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x05
comma
id|init_1x93_tab
(braket
l_int|0x05
)braket
op_amp
l_int|0x7f
)paren
suffix:semicolon
multiline_comment|/* ves1993 hates this, will lose lock */
r_if
c_cond
(paren
id|demod_type
op_ne
id|DEMOD_VES1993
)paren
id|ves1x93_clr_bit
(paren
id|i2c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_afc
r_static
r_int
id|ves1x93_afc
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|freq
comma
id|u32
id|srate
)paren
(brace
r_int
id|afc
suffix:semicolon
id|afc
op_assign
(paren
(paren
r_int
)paren
(paren
(paren
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x0a
)paren
op_lshift
l_int|1
)paren
op_amp
l_int|0xff
)paren
)paren
op_div
l_int|2
suffix:semicolon
id|afc
op_assign
(paren
id|afc
op_star
(paren
r_int
)paren
(paren
id|srate
op_div
l_int|1000
op_div
l_int|8
)paren
)paren
op_div
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|afc
)paren
(brace
id|freq
op_sub_assign
id|afc
suffix:semicolon
id|tuner_set_tv_freq
(paren
id|i2c
comma
id|freq
comma
l_int|0
)paren
suffix:semicolon
id|ves1x93_init_aquire
(paren
id|i2c
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_set_voltage
r_static
r_int
id|ves1x93_set_voltage
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_sec_voltage_t
id|voltage
)paren
(brace
r_switch
c_cond
(paren
id|voltage
)paren
(brace
r_case
id|SEC_VOLTAGE_13
suffix:colon
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x1f
comma
l_int|0x20
)paren
suffix:semicolon
r_case
id|SEC_VOLTAGE_18
suffix:colon
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x1f
comma
l_int|0x30
)paren
suffix:semicolon
r_case
id|SEC_VOLTAGE_OFF
suffix:colon
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x1f
comma
l_int|0x00
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|ves1x93_ioctl
r_static
r_int
id|ves1x93_ioctl
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
r_struct
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FE_GET_INFO
suffix:colon
id|memcpy
(paren
id|arg
comma
op_amp
id|ves1x93_info
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_info
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_READ_STATUS
suffix:colon
(brace
id|fe_status_t
op_star
id|status
op_assign
id|arg
suffix:semicolon
id|u8
id|sync
op_assign
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x0e
)paren
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sync
op_amp
l_int|1
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SIGNAL
suffix:semicolon
r_if
c_cond
(paren
id|sync
op_amp
l_int|2
)paren
op_star
id|status
op_or_assign
id|FE_HAS_CARRIER
suffix:semicolon
r_if
c_cond
(paren
id|sync
op_amp
l_int|4
)paren
op_star
id|status
op_or_assign
id|FE_HAS_VITERBI
suffix:semicolon
r_if
c_cond
(paren
id|sync
op_amp
l_int|8
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SYNC
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sync
op_amp
l_int|0x1f
)paren
op_eq
l_int|0x1f
)paren
op_star
id|status
op_or_assign
id|FE_HAS_LOCK
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_BER
suffix:colon
(brace
id|u32
op_star
id|ber
op_assign
(paren
id|u32
op_star
)paren
id|arg
suffix:semicolon
op_star
id|ber
op_assign
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x15
)paren
suffix:semicolon
op_star
id|ber
op_or_assign
(paren
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x16
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
op_star
id|ber
op_or_assign
(paren
(paren
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x17
)paren
op_amp
l_int|0x0F
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
op_star
id|ber
op_mul_assign
l_int|10
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
(brace
id|u8
id|signal
op_assign
op_complement
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x0b
)paren
suffix:semicolon
op_star
(paren
(paren
id|u16
op_star
)paren
id|arg
)paren
op_assign
(paren
id|signal
op_lshift
l_int|8
)paren
op_or
id|signal
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SNR
suffix:colon
(brace
id|u8
id|snr
op_assign
op_complement
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x1c
)paren
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|arg
op_assign
(paren
id|snr
op_lshift
l_int|8
)paren
op_or
id|snr
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_UNCORRECTED_BLOCKS
suffix:colon
(brace
op_star
(paren
id|u32
op_star
)paren
id|arg
op_assign
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x18
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|u32
op_star
)paren
id|arg
op_eq
l_int|0x7f
)paren
op_star
(paren
id|u32
op_star
)paren
id|arg
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* counter overflow... */
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x18
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* reset the counter */
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x18
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* dto. */
r_break
suffix:semicolon
)brace
r_case
id|FE_SET_FRONTEND
suffix:colon
(brace
r_struct
id|dvb_frontend_parameters
op_star
id|p
op_assign
id|arg
suffix:semicolon
id|tuner_set_tv_freq
(paren
id|i2c
comma
id|p-&gt;frequency
comma
l_int|0
)paren
suffix:semicolon
id|ves1x93_set_inversion
(paren
id|i2c
comma
id|p-&gt;inversion
)paren
suffix:semicolon
id|ves1x93_set_fec
(paren
id|i2c
comma
id|p-&gt;u.qpsk.fec_inner
)paren
suffix:semicolon
id|ves1x93_set_symbolrate
(paren
id|i2c
comma
id|p-&gt;u.qpsk.symbol_rate
)paren
suffix:semicolon
id|ves1x93_afc
(paren
id|i2c
comma
id|p-&gt;frequency
comma
id|p-&gt;u.qpsk.symbol_rate
)paren
suffix:semicolon
id|state-&gt;inversion
op_assign
id|p-&gt;inversion
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_GET_FRONTEND
suffix:colon
(brace
r_struct
id|dvb_frontend_parameters
op_star
id|p
op_assign
id|arg
suffix:semicolon
r_int
id|afc
suffix:semicolon
id|afc
op_assign
(paren
(paren
r_int
)paren
(paren
(paren
r_char
)paren
(paren
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x0a
)paren
op_lshift
l_int|1
)paren
)paren
)paren
op_div
l_int|2
suffix:semicolon
id|afc
op_assign
(paren
id|afc
op_star
(paren
r_int
)paren
(paren
id|p-&gt;u.qpsk.symbol_rate
op_div
l_int|1000
op_div
l_int|8
)paren
)paren
op_div
l_int|16
suffix:semicolon
id|p-&gt;frequency
op_sub_assign
id|afc
suffix:semicolon
multiline_comment|/*&n;&t;&t; * inversion indicator is only valid&n;&t;&t; * if auto inversion was used&n;&t;&t; */
r_if
c_cond
(paren
id|state-&gt;inversion
op_eq
id|INVERSION_AUTO
)paren
id|p-&gt;inversion
op_assign
(paren
id|ves1x93_readreg
(paren
id|i2c
comma
l_int|0x0f
)paren
op_amp
l_int|2
)paren
ques
c_cond
id|INVERSION_OFF
suffix:colon
id|INVERSION_ON
suffix:semicolon
id|p-&gt;u.qpsk.fec_inner
op_assign
id|ves1x93_get_fec
(paren
id|i2c
)paren
suffix:semicolon
multiline_comment|/*  XXX FIXME: timing offset !! */
r_break
suffix:semicolon
)brace
r_case
id|FE_SLEEP
suffix:colon
r_if
c_cond
(paren
id|board_type
op_eq
id|BOARD_SIEMENS_PCI
)paren
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x1f
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*  LNB power off  */
r_return
id|ves1x93_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x08
)paren
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_return
id|ves1x93_init
(paren
id|i2c
)paren
suffix:semicolon
r_case
id|FE_SET_TONE
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
multiline_comment|/* the ves1893 can generate the 22k */
multiline_comment|/* let&squot;s implement this when we have */
multiline_comment|/* a box that uses the 22K_0 pin... */
r_case
id|FE_SET_VOLTAGE
suffix:colon
r_return
id|ves1x93_set_voltage
(paren
id|i2c
comma
(paren
id|fe_sec_voltage_t
)paren
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_attach
r_static
r_int
id|ves1x93_attach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
op_star
id|data
)paren
(brace
id|u8
id|identity
op_assign
id|ves1x93_readreg
c_func
(paren
id|i2c
comma
l_int|0x1e
)paren
suffix:semicolon
r_struct
id|ves1x93_state
op_star
id|state
suffix:semicolon
r_switch
c_cond
(paren
id|identity
)paren
(brace
r_case
l_int|0xdc
suffix:colon
multiline_comment|/* VES1893A rev1 */
id|printk
c_func
(paren
l_string|&quot;ves1x93: Detected ves1893a rev1&bslash;n&quot;
)paren
suffix:semicolon
id|demod_type
op_assign
id|DEMOD_VES1893
suffix:semicolon
id|ves1x93_info.name
(braket
l_int|4
)braket
op_assign
l_char|&squot;8&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xdd
suffix:colon
multiline_comment|/* VES1893A rev2 */
id|printk
c_func
(paren
l_string|&quot;ves1x93: Detected ves1893a rev2&bslash;n&quot;
)paren
suffix:semicolon
id|demod_type
op_assign
id|DEMOD_VES1893
suffix:semicolon
id|ves1x93_info.name
(braket
l_int|4
)braket
op_assign
l_char|&squot;8&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xde
suffix:colon
multiline_comment|/* VES1993 */
id|printk
c_func
(paren
l_string|&quot;ves1x93: Detected ves1993&bslash;n&quot;
)paren
suffix:semicolon
id|demod_type
op_assign
id|DEMOD_VES1993
suffix:semicolon
id|ves1x93_info.name
(braket
l_int|4
)braket
op_assign
l_char|&squot;9&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;VES1x93 not found (identity %02x)&bslash;n&quot;
comma
id|identity
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ves1x93_state
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|state-&gt;inversion
op_assign
id|INVERSION_OFF
suffix:semicolon
op_star
id|data
op_assign
id|state
suffix:semicolon
r_return
id|dvb_register_frontend
(paren
id|ves1x93_ioctl
comma
id|i2c
comma
(paren
r_void
op_star
)paren
id|state
comma
op_amp
id|ves1x93_info
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_detach
r_static
r_void
id|ves1x93_detach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
id|data
)paren
(brace
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
id|dvb_unregister_frontend
(paren
id|ves1x93_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
DECL|function|init_ves1x93
r_static
r_int
id|__init
id|init_ves1x93
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|board_type
)paren
(brace
r_case
id|BOARD_NOKIA_DBOX2
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: NOKIA_DBOX2&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOARD_SAGEM_DBOX2
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: SAGEM_DBOX2&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BOARD_SIEMENS_PCI
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: SIEMENS_PCI&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|dvb_register_i2c_device
(paren
id|THIS_MODULE
comma
id|ves1x93_attach
comma
id|ves1x93_detach
)paren
suffix:semicolon
)brace
DECL|function|exit_ves1x93
r_static
r_void
id|__exit
id|exit_ves1x93
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
(paren
id|ves1x93_attach
)paren
suffix:semicolon
)brace
DECL|variable|init_ves1x93
id|module_init
c_func
(paren
id|init_ves1x93
)paren
suffix:semicolon
DECL|variable|exit_ves1x93
id|module_exit
c_func
(paren
id|exit_ves1x93
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;VES1x93 DVB-S Frontend&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|board_type
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
eof
