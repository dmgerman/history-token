multiline_comment|/* &n;    VES1820  - Single Chip Cable Channel Receiver driver module&n;               used on the the Siemens DVB-C cards&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
macro_line|#if 0
mdefine_line|#define dprintk(x...) printk(x)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(x...)
macro_line|#endif
multiline_comment|/**&n; *  since we need only a few bits to store internal state we don&squot;t allocate&n; *  extra memory but use frontend-&gt;data as bitfield&n; */
DECL|macro|SET_PWM
mdefine_line|#define SET_PWM(data,pwm) do { &t;&t;&bslash;&n;&t;(long) data &amp;= ~0xff; &t;&t;&bslash;&n;&t;(long) data |= pwm; &t;&t;&bslash;&n;} while (0)
DECL|macro|SET_REG0
mdefine_line|#define SET_REG0(data,reg0) do {&t;&bslash;&n;&t;(long) data &amp;= ~(0xff &lt;&lt; 8); &t;&bslash;&n;&t;(long) data |= reg0 &lt;&lt; 8; &t;&bslash;&n;} while (0)
DECL|macro|SET_TUNER
mdefine_line|#define SET_TUNER(data,type) do {&t;&bslash;&n;&t;(long) data &amp;= ~(0xff &lt;&lt; 16); &t;&bslash;&n;&t;(long) data |= type &lt;&lt; 16;&t;&bslash;&n;} while (0)
DECL|macro|SET_DEMOD_ADDR
mdefine_line|#define SET_DEMOD_ADDR(data,type) do {&t;&bslash;&n;&t;(long) data &amp;= ~(0xff &lt;&lt; 24); &t;&bslash;&n;&t;(long) data |= type &lt;&lt; 24;&t;&bslash;&n;} while (0)
DECL|macro|GET_PWM
mdefine_line|#define GET_PWM(data) ((u8) ((long) data &amp; 0xff))
DECL|macro|GET_REG0
mdefine_line|#define GET_REG0(data) ((u8) (((long) data &gt;&gt; 8) &amp; 0xff))
DECL|macro|GET_TUNER
mdefine_line|#define GET_TUNER(data) ((u8) (((long) data &gt;&gt; 16) &amp; 0xff))
DECL|macro|GET_DEMOD_ADDR
mdefine_line|#define GET_DEMOD_ADDR(data) ((u8) (((long) data &gt;&gt; 24) &amp; 0xff))
DECL|macro|XIN
mdefine_line|#define XIN 57840000UL
DECL|macro|FIN
mdefine_line|#define FIN (XIN &gt;&gt; 4)
DECL|variable|ves1820_info
r_static
r_struct
id|dvb_frontend_info
id|ves1820_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VES1820 based DVB-C frontend&quot;
comma
dot
id|type
op_assign
id|FE_QAM
comma
dot
id|frequency_stepsize
op_assign
l_int|62500
comma
dot
id|frequency_min
op_assign
l_int|51000000
comma
dot
id|frequency_max
op_assign
l_int|858000000
comma
dot
id|symbol_rate_min
op_assign
(paren
id|XIN
op_div
l_int|2
)paren
op_div
l_int|64
comma
multiline_comment|/* SACLK/64 == (XIN/2)/64 */
dot
id|symbol_rate_max
op_assign
(paren
id|XIN
op_div
l_int|2
)paren
op_div
l_int|4
comma
multiline_comment|/* SACLK/4 */
macro_line|#if 0
id|frequency_tolerance
suffix:colon
ques
c_cond
ques
c_cond
ques
c_cond
comma
id|symbol_rate_tolerance
suffix:colon
ques
c_cond
ques
c_cond
ques
c_cond
comma
multiline_comment|/* ppm */
multiline_comment|/* == 8% (spec p. 5) */
id|notifier_delay
suffix:colon
ques
c_cond
comma
macro_line|#endif
dot
id|caps
op_assign
id|FE_CAN_QAM_16
op_or
id|FE_CAN_QAM_32
op_or
id|FE_CAN_QAM_64
op_or
id|FE_CAN_QAM_128
op_or
id|FE_CAN_QAM_256
op_or
id|FE_CAN_FEC_AUTO
op_or
id|FE_CAN_INVERSION_AUTO
op_or
id|FE_CAN_CLEAN_SETUP
op_or
id|FE_CAN_RECOVER
)brace
suffix:semicolon
DECL|variable|ves1820_inittab
r_static
id|u8
id|ves1820_inittab
(braket
)braket
op_assign
(brace
l_int|0x69
comma
l_int|0x6A
comma
l_int|0x9B
comma
l_int|0x0A
comma
l_int|0x52
comma
l_int|0x46
comma
l_int|0x26
comma
l_int|0x1A
comma
l_int|0x43
comma
l_int|0x6A
comma
l_int|0xAA
comma
l_int|0xAA
comma
l_int|0x1E
comma
l_int|0x85
comma
l_int|0x43
comma
l_int|0x28
comma
l_int|0xE0
comma
l_int|0x00
comma
l_int|0xA1
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
l_int|0x01
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x02
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
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x40
)brace
suffix:semicolon
DECL|function|ves1820_writereg
r_static
r_int
id|ves1820_writereg
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|u8
id|addr
op_assign
id|GET_DEMOD_ADDR
c_func
(paren
id|fe-&gt;data
)paren
suffix:semicolon
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
id|addr
suffix:colon
id|addr
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
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
r_int
id|ret
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
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
id|dprintk
c_func
(paren
l_string|&quot;%s: writereg error &quot;
l_string|&quot;(reg == 0x%02x, val == 0x%02x, ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reg
comma
id|data
comma
id|ret
)paren
suffix:semicolon
id|dvb_delay
c_func
(paren
l_int|10
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
id|EREMOTEIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_readreg
r_static
id|u8
id|ves1820_readreg
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|reg
)paren
(brace
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
id|u8
id|addr
op_assign
id|GET_DEMOD_ADDR
c_func
(paren
id|fe-&gt;data
)paren
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
)braket
op_assign
(brace
(brace
id|addr
suffix:colon
id|addr
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
id|addr
suffix:colon
id|addr
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
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
r_int
id|ret
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
id|addr
comma
id|u8
id|data
(braket
l_int|4
)braket
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
id|addr
suffix:colon
id|addr
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
l_int|4
)brace
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
id|EREMOTEIO
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *   set up the downconverter frequency divisor for a&n; *   reference clock comparision frequency of 62.5 kHz.&n; */
DECL|function|tuner_set_tv_freq
r_static
r_int
id|tuner_set_tv_freq
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
id|freq
)paren
(brace
id|u32
id|div
comma
id|ifreq
suffix:semicolon
r_static
id|u8
id|addr
(braket
)braket
op_assign
(brace
l_int|0x61
comma
l_int|0x62
)brace
suffix:semicolon
r_static
id|u8
id|byte3
(braket
)braket
op_assign
(brace
l_int|0x8e
comma
l_int|0x85
)brace
suffix:semicolon
r_int
id|tuner_type
op_assign
id|GET_TUNER
c_func
(paren
id|fe-&gt;data
)paren
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tuner_type
op_eq
l_int|0xff
)paren
multiline_comment|/*  PLL not reachable over i2c ...  */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strstr
(paren
id|fe-&gt;i2c-&gt;adapter-&gt;name
comma
l_string|&quot;Technotrend&quot;
)paren
)paren
id|ifreq
op_assign
l_int|35937500
suffix:semicolon
r_else
id|ifreq
op_assign
l_int|36125000
suffix:semicolon
id|div
op_assign
(paren
id|freq
op_plus
id|ifreq
op_plus
l_int|31250
)paren
op_div
l_int|62500
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|byte3
(braket
id|tuner_type
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tuner_type
op_eq
l_int|1
)paren
(brace
id|buf
(braket
l_int|2
)braket
op_or_assign
(paren
id|div
op_rshift
l_int|10
)paren
op_amp
l_int|0x60
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
(paren
id|freq
OL
l_int|174000000
ques
c_cond
l_int|0x88
suffix:colon
id|freq
OL
l_int|470000000
ques
c_cond
l_int|0x84
suffix:colon
l_int|0x81
)paren
suffix:semicolon
)brace
r_else
(brace
id|buf
(braket
l_int|3
)braket
op_assign
(paren
id|freq
OL
l_int|174000000
ques
c_cond
l_int|0xa1
suffix:colon
id|freq
OL
l_int|454000000
ques
c_cond
l_int|0x92
suffix:colon
l_int|0x34
)paren
suffix:semicolon
)brace
r_return
id|tuner_write
(paren
id|fe-&gt;i2c
comma
id|addr
(braket
id|tuner_type
)braket
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|ves1820_setup_reg0
r_static
r_int
id|ves1820_setup_reg0
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|reg0
comma
id|fe_spectral_inversion_t
id|inversion
)paren
(brace
id|reg0
op_or_assign
id|GET_REG0
c_func
(paren
id|fe-&gt;data
)paren
op_amp
l_int|0x62
suffix:semicolon
r_if
c_cond
(paren
id|INVERSION_ON
op_eq
id|inversion
)paren
id|reg0
op_and_assign
op_complement
l_int|0x20
suffix:semicolon
r_else
r_if
c_cond
(paren
id|INVERSION_OFF
op_eq
id|inversion
)paren
id|reg0
op_or_assign
l_int|0x20
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x00
comma
id|reg0
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x00
comma
id|reg0
op_or
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/**&n;&t; *  check lock and toggle inversion bit if required...&n;&t; */
r_if
c_cond
(paren
id|INVERSION_AUTO
op_eq
id|inversion
op_logical_and
op_logical_neg
(paren
id|ves1820_readreg
(paren
id|fe
comma
l_int|0x11
)paren
op_amp
l_int|0x08
)paren
)paren
(brace
id|dvb_delay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ves1820_readreg
(paren
id|fe
comma
l_int|0x11
)paren
op_amp
l_int|0x08
)paren
)paren
(brace
id|reg0
op_xor_assign
l_int|0x20
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x00
comma
id|reg0
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x00
comma
id|reg0
op_or
l_int|0x01
)paren
suffix:semicolon
)brace
)brace
id|SET_REG0
c_func
(paren
id|fe-&gt;data
comma
id|reg0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_init
r_static
r_int
id|ves1820_init
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;VES1820: init chip&bslash;n&quot;
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0
comma
l_int|0
)paren
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
l_int|53
suffix:semicolon
id|i
op_increment
)paren
id|ves1820_writereg
(paren
id|fe
comma
id|i
comma
id|ves1820_inittab
(braket
id|i
)braket
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x34
comma
id|GET_PWM
c_func
(paren
id|fe-&gt;data
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_set_symbolrate
r_static
r_int
id|ves1820_set_symbolrate
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
id|symbolrate
)paren
(brace
id|s32
id|BDR
suffix:semicolon
id|s32
id|BDRI
suffix:semicolon
id|s16
id|SFIL
op_assign
l_int|0
suffix:semicolon
id|u16
id|NDEC
op_assign
l_int|0
suffix:semicolon
id|u32
id|tmp
comma
id|ratio
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OG
id|XIN
op_div
l_int|2
)paren
id|symbolrate
op_assign
id|XIN
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
l_int|500000
)paren
id|symbolrate
op_assign
l_int|500000
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|XIN
op_div
l_int|16
)paren
id|NDEC
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|XIN
op_div
l_int|32
)paren
id|NDEC
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|XIN
op_div
l_int|64
)paren
id|NDEC
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_float|12.3
)paren
)paren
id|SFIL
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_int|16
)paren
)paren
id|SFIL
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_float|24.6
)paren
)paren
id|SFIL
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_int|32
)paren
)paren
id|SFIL
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_float|49.2
)paren
)paren
id|SFIL
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_int|64
)paren
)paren
id|SFIL
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
(paren
id|u32
)paren
(paren
id|XIN
op_div
l_float|98.4
)paren
)paren
id|SFIL
op_assign
l_int|1
suffix:semicolon
id|symbolrate
op_lshift_assign
id|NDEC
suffix:semicolon
id|ratio
op_assign
(paren
id|symbolrate
op_lshift
l_int|4
)paren
op_div
id|FIN
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|symbolrate
op_lshift
l_int|4
)paren
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
(paren
id|tmp
op_plus
id|FIN
op_div
l_int|2
)paren
op_div
id|FIN
suffix:semicolon
id|BDR
op_assign
id|ratio
suffix:semicolon
id|BDRI
op_assign
(paren
(paren
(paren
id|XIN
op_lshift
l_int|5
)paren
op_div
id|symbolrate
)paren
op_plus
l_int|1
)paren
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|BDRI
OG
l_int|0xFF
)paren
id|BDRI
op_assign
l_int|0xFF
suffix:semicolon
id|SFIL
op_assign
(paren
id|SFIL
op_lshift
l_int|4
)paren
op_or
id|ves1820_inittab
(braket
l_int|0x0E
)braket
suffix:semicolon
id|NDEC
op_assign
(paren
id|NDEC
op_lshift
l_int|6
)paren
op_or
id|ves1820_inittab
(braket
l_int|0x03
)braket
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x03
comma
id|NDEC
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x0a
comma
id|BDR
op_amp
l_int|0xff
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x0b
comma
(paren
id|BDR
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x0c
comma
(paren
id|BDR
op_rshift
l_int|16
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x0d
comma
id|BDRI
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x0e
comma
id|SFIL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_set_parameters
r_static
r_int
id|ves1820_set_parameters
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|p
)paren
(brace
r_static
r_const
id|u8
id|reg0x00
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x04
comma
l_int|0x08
comma
l_int|0x0c
comma
l_int|0x10
)brace
suffix:semicolon
r_static
r_const
id|u8
id|reg0x01
(braket
)braket
op_assign
(brace
l_int|140
comma
l_int|140
comma
l_int|106
comma
l_int|100
comma
l_int|92
)brace
suffix:semicolon
r_static
r_const
id|u8
id|reg0x05
(braket
)braket
op_assign
(brace
l_int|135
comma
l_int|100
comma
l_int|70
comma
l_int|54
comma
l_int|38
)brace
suffix:semicolon
r_static
r_const
id|u8
id|reg0x08
(braket
)braket
op_assign
(brace
l_int|162
comma
l_int|116
comma
l_int|67
comma
l_int|52
comma
l_int|35
)brace
suffix:semicolon
r_static
r_const
id|u8
id|reg0x09
(braket
)braket
op_assign
(brace
l_int|145
comma
l_int|150
comma
l_int|106
comma
l_int|126
comma
l_int|107
)brace
suffix:semicolon
r_int
id|real_qam
op_assign
id|p-&gt;u.qam.modulation
op_minus
id|QAM_16
suffix:semicolon
r_if
c_cond
(paren
id|real_qam
template_param
l_int|4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tuner_set_tv_freq
(paren
id|fe
comma
id|p-&gt;frequency
)paren
suffix:semicolon
id|ves1820_set_symbolrate
(paren
id|fe
comma
id|p-&gt;u.qam.symbol_rate
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x34
comma
id|GET_PWM
c_func
(paren
id|fe-&gt;data
)paren
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x01
comma
id|reg0x01
(braket
id|real_qam
)braket
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x05
comma
id|reg0x05
(braket
id|real_qam
)braket
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x08
comma
id|reg0x08
(braket
id|real_qam
)braket
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x09
comma
id|reg0x09
(braket
id|real_qam
)braket
)paren
suffix:semicolon
id|ves1820_setup_reg0
(paren
id|fe
comma
id|reg0x00
(braket
id|real_qam
)braket
comma
id|p-&gt;inversion
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_ioctl
r_static
r_int
id|ves1820_ioctl
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
id|ves1820_info
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
(paren
id|fe_status_t
op_star
)paren
id|arg
suffix:semicolon
r_int
id|sync
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
id|sync
op_assign
id|ves1820_readreg
(paren
id|fe
comma
l_int|0x11
)paren
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
l_int|2
)paren
multiline_comment|/* XXX FIXME! */
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
l_int|4
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SYNC
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
id|ber
op_assign
id|ves1820_readreg
c_func
(paren
id|fe
comma
l_int|0x14
)paren
op_or
(paren
id|ves1820_readreg
c_func
(paren
id|fe
comma
l_int|0x15
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|ves1820_readreg
c_func
(paren
id|fe
comma
l_int|0x16
)paren
op_amp
l_int|0x0f
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|arg
)paren
op_assign
l_int|10
op_star
id|ber
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
(brace
id|u8
id|gain
op_assign
id|ves1820_readreg
c_func
(paren
id|fe
comma
l_int|0x17
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
id|gain
op_lshift
l_int|8
)paren
op_or
id|gain
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SNR
suffix:colon
(brace
id|u8
id|quality
op_assign
op_complement
id|ves1820_readreg
c_func
(paren
id|fe
comma
l_int|0x18
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
id|quality
op_lshift
l_int|8
)paren
op_or
id|quality
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_UNCORRECTED_BLOCKS
suffix:colon
op_star
(paren
(paren
id|u32
op_star
)paren
id|arg
)paren
op_assign
id|ves1820_readreg
(paren
id|fe
comma
l_int|0x13
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|arg
)paren
op_eq
l_int|0x7f
)paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|arg
)paren
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* reset uncorrected block counter */
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x10
comma
id|ves1820_inittab
(braket
l_int|0x10
)braket
op_amp
l_int|0xdf
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x10
comma
id|ves1820_inittab
(braket
l_int|0x10
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SET_FRONTEND
suffix:colon
r_return
id|ves1820_set_parameters
(paren
id|fe
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_GET_FRONTEND
suffix:colon
(brace
r_struct
id|dvb_frontend_parameters
op_star
id|p
op_assign
(paren
r_struct
id|dvb_frontend_parameters
op_star
)paren
id|arg
suffix:semicolon
id|u8
id|reg0
op_assign
id|GET_REG0
c_func
(paren
id|fe-&gt;data
)paren
suffix:semicolon
r_int
id|sync
suffix:semicolon
id|s8
id|afc
op_assign
l_int|0
suffix:semicolon
id|sync
op_assign
id|ves1820_readreg
(paren
id|fe
comma
l_int|0x11
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sync
op_amp
l_int|2
)paren
multiline_comment|/* AFC only valid when carrier has been recovered */
id|afc
op_assign
id|ves1820_readreg
c_func
(paren
id|fe
comma
l_int|0x19
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: AFC (%d) %dHz&bslash;n&quot;
comma
id|__FILE__
comma
id|afc
comma
op_minus
(paren
(paren
id|s32
)paren
(paren
id|p-&gt;u.qam.symbol_rate
op_rshift
l_int|3
)paren
op_star
id|afc
op_rshift
l_int|7
)paren
)paren
suffix:semicolon
id|p-&gt;inversion
op_assign
id|reg0
op_amp
l_int|0x20
ques
c_cond
id|INVERSION_OFF
suffix:colon
id|INVERSION_ON
suffix:semicolon
id|p-&gt;u.qam.modulation
op_assign
(paren
(paren
id|reg0
op_rshift
l_int|2
)paren
op_amp
l_int|7
)paren
op_plus
id|QAM_16
suffix:semicolon
id|p-&gt;u.qam.fec_inner
op_assign
id|FEC_NONE
suffix:semicolon
id|p-&gt;frequency
op_assign
(paren
(paren
id|p-&gt;frequency
op_plus
l_int|31250
)paren
op_div
l_int|62500
)paren
op_star
l_int|62500
suffix:semicolon
singleline_comment|// To prevent overflow, shift symbol rate first a
singleline_comment|// couple of bits.
id|p-&gt;frequency
op_sub_assign
(paren
id|s32
)paren
(paren
id|p-&gt;u.qam.symbol_rate
op_rshift
l_int|3
)paren
op_star
id|afc
op_rshift
l_int|7
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_SLEEP
suffix:colon
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x1b
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* pdown ADC */
id|ves1820_writereg
(paren
id|fe
comma
l_int|0x00
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* standby */
r_break
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_return
id|ves1820_init
(paren
id|fe
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_tuner
r_static
r_int
id|probe_tuner
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_static
r_const
r_struct
id|i2c_msg
id|msg1
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
l_int|NULL
comma
dot
id|len
op_assign
l_int|0
)brace
suffix:semicolon
r_static
r_const
r_struct
id|i2c_msg
id|msg2
op_assign
(brace
dot
id|addr
op_assign
l_int|0x62
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
l_int|NULL
comma
dot
id|len
op_assign
l_int|0
)brace
suffix:semicolon
r_int
id|type
suffix:semicolon
r_if
c_cond
(paren
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
op_amp
id|msg1
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|type
op_assign
l_int|0
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: setup for tuner spXXXX&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
op_amp
id|msg2
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|type
op_assign
l_int|1
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: setup for tuner sp5659c&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
)brace
r_else
(brace
id|type
op_assign
op_minus
l_int|1
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: unknown PLL, &quot;
l_string|&quot;please report to &lt;linuxdvb@linuxtv.org&gt;!!&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
)brace
r_return
id|type
suffix:semicolon
)brace
DECL|function|read_pwm
r_static
id|u8
id|read_pwm
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|u8
id|b
op_assign
l_int|0xff
suffix:semicolon
id|u8
id|pwm
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
l_int|0x50
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
op_amp
id|b
comma
dot
id|len
op_assign
l_int|1
)brace
comma
(brace
dot
id|addr
op_assign
l_int|0x50
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
op_amp
id|pwm
comma
dot
id|len
op_assign
l_int|1
)brace
)brace
suffix:semicolon
id|i2c-&gt;xfer
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;VES1820: pwm=%02x&bslash;n&quot;
comma
id|pwm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pwm
op_eq
l_int|0xff
)paren
id|pwm
op_assign
l_int|0x48
suffix:semicolon
r_return
id|pwm
suffix:semicolon
)brace
DECL|function|probe_demod_addr
r_static
r_int
id|probe_demod_addr
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|u8
id|b
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x1a
)brace
suffix:semicolon
id|u8
id|id
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
id|b
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
op_amp
id|id
comma
dot
id|len
op_assign
l_int|1
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
op_eq
l_int|2
op_logical_and
(paren
id|id
op_amp
l_int|0xf0
)paren
op_eq
l_int|0x70
)paren
r_return
id|msg
(braket
l_int|0
)braket
dot
id|addr
suffix:semicolon
id|msg
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|msg
(braket
l_int|1
)braket
dot
id|addr
op_assign
l_int|0x09
suffix:semicolon
r_if
c_cond
(paren
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
op_eq
l_int|2
op_logical_and
(paren
id|id
op_amp
l_int|0xf0
)paren
op_eq
l_int|0x70
)paren
r_return
id|msg
(braket
l_int|0
)braket
dot
id|addr
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ves1820_attach
r_static
r_int
id|ves1820_attach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_void
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
r_int
id|demod_addr
suffix:semicolon
r_int
id|tuner_type
suffix:semicolon
r_if
c_cond
(paren
(paren
id|demod_addr
op_assign
id|probe_demod_addr
c_func
(paren
id|i2c
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tuner_type
op_assign
id|probe_tuner
c_func
(paren
id|i2c
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|SET_PWM
c_func
(paren
id|data
comma
id|read_pwm
c_func
(paren
id|i2c
)paren
)paren
suffix:semicolon
id|SET_REG0
c_func
(paren
id|data
comma
id|ves1820_inittab
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|SET_TUNER
c_func
(paren
id|data
comma
id|tuner_type
)paren
suffix:semicolon
id|SET_DEMOD_ADDR
c_func
(paren
id|data
comma
id|demod_addr
)paren
suffix:semicolon
id|dvb_register_frontend
(paren
id|ves1820_ioctl
comma
id|i2c
comma
id|data
comma
op_amp
id|ves1820_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_detach
r_static
r_void
id|ves1820_detach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dvb_unregister_frontend
(paren
id|ves1820_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
DECL|function|init_ves1820
r_static
r_int
id|__init
id|init_ves1820
(paren
r_void
)paren
(brace
r_return
id|dvb_register_i2c_device
(paren
id|THIS_MODULE
comma
id|ves1820_attach
comma
id|ves1820_detach
)paren
suffix:semicolon
)brace
DECL|function|exit_ves1820
r_static
r_void
id|__exit
id|exit_ves1820
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
(paren
id|ves1820_attach
)paren
suffix:semicolon
)brace
DECL|variable|init_ves1820
id|module_init
c_func
(paren
id|init_ves1820
)paren
suffix:semicolon
DECL|variable|exit_ves1820
id|module_exit
c_func
(paren
id|exit_ves1820
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;VES1820 DVB-C frontend driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler, Holger Waechtler&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
