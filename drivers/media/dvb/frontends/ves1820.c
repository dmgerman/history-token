multiline_comment|/* &n;    VES1820  - Single Chip Cable Channel Receiver driver module&n;               used on the the Siemens DVB-C cards&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;compat.h&quot;
macro_line|#include &quot;dvb_frontend.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk&t;if (debug) printk
multiline_comment|/**&n; *  since we need only a few bits to store internal state we don&squot;t allocate&n; *  extra memory but use frontend-&gt;data as bitfield&n; */
DECL|macro|SET_PWM
mdefine_line|#define SET_PWM(frontend,pwm) do { &t;&t;&bslash;&n;&t;(int) frontend-&gt;data &amp;= ~0xff; &t;&t;&bslash;&n;&t;(int) frontend-&gt;data |= pwm; &t;&t;&bslash;&n;} while (0)
DECL|macro|SET_REG0
mdefine_line|#define SET_REG0(frontend,reg0) do {&t;&t;&bslash;&n;&t;(int) frontend-&gt;data &amp;= ~(0xff &lt;&lt; 8); &t;&bslash;&n;&t;(int) frontend-&gt;data |= reg0 &lt;&lt; 8; &t;&bslash;&n;} while (0)
DECL|macro|SET_TUNER
mdefine_line|#define SET_TUNER(frontend,type) do {&t;&t;&bslash;&n;&t;(int) frontend-&gt;data &amp;= ~(0xff &lt;&lt; 16); &t;&bslash;&n;&t;(int) frontend-&gt;data |= type &lt;&lt; 16;&t;&bslash;&n;} while (0)
DECL|macro|GET_PWM
mdefine_line|#define GET_PWM(frontend) ((u8) ((int) frontend-&gt;data &amp; 0xff))
DECL|macro|GET_REG0
mdefine_line|#define GET_REG0(frontend) ((u8) (((int) frontend-&gt;data &gt;&gt; 8) &amp; 0xff))
DECL|macro|GET_TUNER
mdefine_line|#define GET_TUNER(frontend) ((u8) (((int) frontend-&gt;data &gt;&gt; 16) &amp; 0xff))
r_static
DECL|variable|ves1820_info
r_struct
id|dvb_frontend_info
id|ves1820_info
op_assign
(brace
id|name
suffix:colon
l_string|&quot;VES1820/Grundig tuner as used on the Siemens DVB-C card&quot;
comma
id|type
suffix:colon
id|FE_QAM
comma
id|frequency_stepsize
suffix:colon
l_int|62500
comma
id|frequency_min
suffix:colon
l_int|51000000
comma
id|frequency_max
suffix:colon
l_int|858000000
comma
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
id|symbol_rate_min
suffix:colon
ques
c_cond
ques
c_cond
ques
c_cond
comma
id|symbol_rate_max
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
id|caps
suffix:colon
id|FE_CAN_QAM_16
op_or
id|FE_CAN_QAM_32
op_or
id|FE_CAN_QAM_64
op_or
id|FE_CAN_QAM_128
op_or
id|FE_CAN_QAM_256
)brace
suffix:semicolon
r_static
DECL|variable|ves1820_inittab
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
r_static
DECL|function|ves1820_writereg
r_int
id|ves1820_writereg
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
r_int
id|ret
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
l_int|0x09
comma
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
id|buf
comma
id|len
suffix:colon
l_int|3
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
id|mdelay
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
r_static
DECL|function|ves1820_readreg
id|u8
id|ves1820_readreg
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
id|addr
suffix:colon
l_int|0x09
comma
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
id|b0
comma
id|len
suffix:colon
l_int|2
)brace
comma
(brace
id|addr
suffix:colon
l_int|0x09
comma
id|flags
suffix:colon
id|I2C_M_RD
comma
id|buf
suffix:colon
id|b1
comma
id|len
suffix:colon
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
r_static
DECL|function|tuner_write
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
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
id|data
comma
id|len
suffix:colon
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
r_static
DECL|function|tuner_set_tv_freq
r_int
id|tuner_set_tv_freq
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
id|u32
id|freq
)paren
(brace
id|u32
id|div
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
id|frontend
)paren
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
id|div
op_assign
(paren
id|freq
op_plus
l_int|36250000
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
id|frontend-&gt;i2c
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
r_static
DECL|function|probe_tuner
r_int
id|probe_tuner
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|frontend-&gt;i2c
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
id|addr
suffix:colon
l_int|0x61
comma
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
l_int|NULL
comma
id|len
suffix:colon
l_int|0
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
op_amp
id|msg
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
id|SET_TUNER
c_func
(paren
id|frontend
comma
l_int|0
)paren
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
(brace
id|SET_TUNER
c_func
(paren
id|frontend
comma
l_int|1
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: setup for tuner sp5659c&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_init
r_int
id|ves1820_init
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|frontend-&gt;i2c
suffix:semicolon
id|u8
id|b0
(braket
)braket
op_assign
(brace
l_int|0xff
)brace
suffix:semicolon
id|u8
id|pwm
suffix:semicolon
r_int
id|i
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
l_int|0x28
comma
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
id|b0
comma
id|len
suffix:colon
l_int|1
)brace
comma
(brace
id|addr
suffix:colon
l_int|0x28
comma
id|flags
suffix:colon
id|I2C_M_RD
comma
id|buf
suffix:colon
op_amp
id|pwm
comma
id|len
suffix:colon
l_int|1
)brace
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;VES1820: init chip&bslash;n&quot;
)paren
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
id|ves1820_writereg
(paren
id|i2c
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
id|i2c
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
id|i2c
comma
l_int|0x34
comma
id|pwm
)paren
suffix:semicolon
(paren
r_int
)paren
id|frontend-&gt;data
op_assign
l_int|0
suffix:semicolon
id|SET_PWM
c_func
(paren
id|frontend
comma
id|pwm
)paren
suffix:semicolon
id|probe_tuner
(paren
id|frontend
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_setup_reg0
r_int
id|ves1820_setup_reg0
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
id|u8
id|real_qam
comma
id|fe_spectral_inversion_t
id|inversion
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|frontend-&gt;i2c
suffix:semicolon
id|u8
id|reg0
op_assign
(paren
id|ves1820_inittab
(braket
l_int|0
)braket
op_amp
l_int|0xe3
)paren
op_or
(paren
id|real_qam
op_lshift
l_int|2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|inversion
)paren
(brace
r_case
id|INVERSION_OFF
suffix:colon
multiline_comment|/* XXX FIXME: reversed?? p. 25  */
id|reg0
op_or_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_ON
suffix:colon
id|reg0
op_and_assign
l_int|0xdf
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
id|SET_REG0
c_func
(paren
id|frontend
comma
id|reg0
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
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
id|i2c
comma
l_int|0x00
comma
id|reg0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_reset
r_int
id|ves1820_reset
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|frontend-&gt;i2c
suffix:semicolon
id|u8
id|reg0
op_assign
id|GET_REG0
c_func
(paren
id|frontend
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
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
id|i2c
comma
l_int|0x00
comma
id|reg0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_reset_uncorrected_block_counter
r_void
id|ves1820_reset_uncorrected_block_counter
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|ves1820_writereg
(paren
id|i2c
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
id|i2c
comma
l_int|0x10
comma
id|ves1820_inittab
(braket
l_int|0x10
)braket
)paren
suffix:semicolon
)brace
r_static
DECL|function|ves1820_set_symbolrate
r_int
id|ves1820_set_symbolrate
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
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
DECL|macro|XIN
mdefine_line|#define XIN 57840000UL
DECL|macro|FIN
mdefine_line|#define FIN (57840000UL&gt;&gt;4)
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
id|i2c
comma
l_int|0x03
comma
id|NDEC
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
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
id|i2c
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
id|i2c
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
id|i2c
comma
l_int|0x0d
comma
id|BDRI
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
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
r_static
DECL|function|ves1820_reset_pwm
r_void
id|ves1820_reset_pwm
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
)paren
(brace
id|u8
id|pwm
op_assign
id|GET_PWM
c_func
(paren
id|frontend
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|frontend-&gt;i2c
comma
l_int|0x34
comma
id|pwm
)paren
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|QAM_Mode
id|fe_modulation_t
id|QAM_Mode
suffix:semicolon
DECL|member|NoOfSym
r_int
id|NoOfSym
suffix:semicolon
DECL|member|Reg1
id|u8
id|Reg1
suffix:semicolon
DECL|member|Reg5
id|u8
id|Reg5
suffix:semicolon
DECL|member|Reg8
id|u8
id|Reg8
suffix:semicolon
DECL|member|Reg9
id|u8
id|Reg9
suffix:semicolon
DECL|typedef|QAM_SETTING
)brace
id|QAM_SETTING
suffix:semicolon
DECL|variable|QAM_Values
id|QAM_SETTING
id|QAM_Values
(braket
)braket
op_assign
(brace
(brace
id|QAM_16
comma
l_int|16
comma
l_int|140
comma
l_int|164
comma
l_int|162
comma
l_int|145
)brace
comma
(brace
id|QAM_32
comma
l_int|32
comma
l_int|140
comma
l_int|120
comma
l_int|116
comma
l_int|150
)brace
comma
(brace
id|QAM_64
comma
l_int|64
comma
l_int|106
comma
l_int|70
comma
l_int|67
comma
l_int|106
)brace
comma
(brace
id|QAM_128
comma
l_int|128
comma
l_int|120
comma
l_int|54
comma
l_int|52
comma
l_int|126
)brace
comma
(brace
id|QAM_256
comma
l_int|256
comma
l_int|92
comma
l_int|38
comma
l_int|35
comma
l_int|107
)brace
)brace
suffix:semicolon
r_static
DECL|function|ves1820_set_parameters
r_int
id|ves1820_set_parameters
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
comma
r_struct
id|dvb_frontend_parameters
op_star
id|p
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|frontend-&gt;i2c
suffix:semicolon
r_int
id|real_qam
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.qam.modulation
)paren
(brace
r_case
id|QAM_16
suffix:colon
id|real_qam
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_32
suffix:colon
id|real_qam
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_64
suffix:colon
id|real_qam
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_128
suffix:colon
id|real_qam
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_256
suffix:colon
id|real_qam
op_assign
l_int|4
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
id|tuner_set_tv_freq
(paren
id|frontend
comma
id|p-&gt;frequency
)paren
suffix:semicolon
id|ves1820_set_symbolrate
(paren
id|i2c
comma
id|p-&gt;u.qam.symbol_rate
)paren
suffix:semicolon
id|ves1820_reset_pwm
(paren
id|frontend
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
comma
l_int|0x01
comma
id|QAM_Values
(braket
id|real_qam
)braket
dot
id|Reg1
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
comma
l_int|0x05
comma
id|QAM_Values
(braket
id|real_qam
)braket
dot
id|Reg5
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
comma
l_int|0x08
comma
id|QAM_Values
(braket
id|real_qam
)braket
dot
id|Reg8
)paren
suffix:semicolon
id|ves1820_writereg
(paren
id|i2c
comma
l_int|0x09
comma
id|QAM_Values
(braket
id|real_qam
)braket
dot
id|Reg9
)paren
suffix:semicolon
id|ves1820_setup_reg0
(paren
id|frontend
comma
id|real_qam
comma
id|p-&gt;inversion
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_ioctl
r_int
id|ves1820_ioctl
(paren
r_struct
id|dvb_frontend
op_star
id|frontend
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
id|frontend-&gt;i2c
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
c_func
(paren
id|frontend-&gt;i2c
comma
l_int|0x14
)paren
op_or
(paren
id|ves1820_readreg
c_func
(paren
id|frontend-&gt;i2c
comma
l_int|0x15
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|ves1820_readreg
c_func
(paren
id|frontend-&gt;i2c
comma
l_int|0x16
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* XXX FIXME: scale!!*/
r_break
suffix:semicolon
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
id|frontend-&gt;i2c
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
id|frontend-&gt;i2c
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
id|frontend-&gt;i2c
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
id|ves1820_reset_uncorrected_block_counter
(paren
id|frontend-&gt;i2c
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
id|frontend
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_GET_FRONTEND
suffix:colon
multiline_comment|/*  XXX FIXME: implement! */
multiline_comment|/*&n;                struct frontend *front = (struct frontend *)arg;&n;                &n;                front-&gt;afc=(int)((char)(readreg(client,0x19)));&n;                front-&gt;afc=(front-&gt;afc*(int)(front-&gt;param.u.qam.SymbolRate/8))/128;&n;*/
r_break
suffix:semicolon
r_case
id|FE_SLEEP
suffix:colon
id|ves1820_writereg
(paren
id|frontend-&gt;i2c
comma
l_int|0x1b
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* pdown ADC */
id|ves1820_writereg
(paren
id|frontend-&gt;i2c
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
id|frontend
)paren
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
id|ves1820_reset
(paren
id|frontend
)paren
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
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_attach
r_int
id|ves1820_attach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_if
c_cond
(paren
(paren
id|ves1820_readreg
(paren
id|i2c
comma
l_int|0x1a
)paren
op_amp
l_int|0xf0
)paren
op_ne
l_int|0x70
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dvb_register_frontend
(paren
id|ves1820_ioctl
comma
id|i2c
comma
l_int|NULL
comma
op_amp
id|ves1820_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|ves1820_detach
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
r_static
DECL|function|init_ves1820
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
r_static
DECL|function|exit_ves1820
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
l_string|&quot;&quot;
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
eof
