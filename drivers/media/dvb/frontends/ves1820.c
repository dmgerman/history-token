multiline_comment|/* &n;    VES1820  - Single Chip Cable Channel Receiver driver module&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;ves1820.h&quot;
DECL|struct|ves1820_state
r_struct
id|ves1820_state
(brace
DECL|member|i2c
r_struct
id|i2c_adapter
op_star
id|i2c
suffix:semicolon
DECL|member|ops
r_struct
id|dvb_frontend_ops
id|ops
suffix:semicolon
multiline_comment|/* configuration settings */
DECL|member|config
r_const
r_struct
id|ves1820_config
op_star
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
multiline_comment|/* private demodulator data */
DECL|member|reg0
id|u8
id|reg0
suffix:semicolon
DECL|member|pwm
id|u8
id|pwm
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|verbose
r_static
r_int
id|verbose
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
l_int|0x93
comma
l_int|0x12
comma
l_int|0x12
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
l_int|0x20
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
c_func
(paren
r_struct
id|ves1820_state
op_star
id|state
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
id|state-&gt;config-&gt;demod_address
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
id|ret
suffix:semicolon
id|ret
op_assign
id|i2c_transfer
c_func
(paren
id|state-&gt;i2c
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
l_string|&quot;ves1820: %s(): writereg error (reg == 0x%02x,&quot;
l_string|&quot;val == 0x%02x, ret == %i)&bslash;n&quot;
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
id|msleep
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
c_func
(paren
r_struct
id|ves1820_state
op_star
id|state
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
id|state-&gt;config-&gt;demod_address
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
id|state-&gt;config-&gt;demod_address
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
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|i2c_transfer
c_func
(paren
id|state-&gt;i2c
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
id|printk
c_func
(paren
l_string|&quot;ves1820: %s(): readreg error (reg == 0x%02x,&quot;
l_string|&quot;ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reg
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
DECL|function|ves1820_setup_reg0
r_static
r_int
id|ves1820_setup_reg0
c_func
(paren
r_struct
id|ves1820_state
op_star
id|state
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
id|state-&gt;reg0
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;config-&gt;invert
)paren
id|reg0
op_or_assign
l_int|0x20
suffix:semicolon
r_else
id|reg0
op_and_assign
op_complement
l_int|0x20
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|INVERSION_OFF
op_eq
id|inversion
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;config-&gt;invert
)paren
id|reg0
op_and_assign
op_complement
l_int|0x20
suffix:semicolon
r_else
id|reg0
op_or_assign
l_int|0x20
suffix:semicolon
)brace
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
id|reg0
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
id|reg0
op_or
l_int|0x01
)paren
suffix:semicolon
id|state-&gt;reg0
op_assign
id|reg0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_set_symbolrate
r_static
r_int
id|ves1820_set_symbolrate
c_func
(paren
r_struct
id|ves1820_state
op_star
id|state
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
id|ratio
suffix:semicolon
id|u32
id|fin
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|u64
id|fptmp
suffix:semicolon
id|u64
id|fpxin
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OG
id|state-&gt;config-&gt;xin
op_div
l_int|2
)paren
id|symbolrate
op_assign
id|state-&gt;config-&gt;xin
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
id|state-&gt;config-&gt;xin
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
id|state-&gt;config-&gt;xin
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
id|state-&gt;config-&gt;xin
op_div
l_int|64
)paren
id|NDEC
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* yeuch! */
id|fpxin
op_assign
id|state-&gt;config-&gt;xin
op_star
l_int|10
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|123
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|1
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|160
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|0
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|246
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|1
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|320
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|0
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|492
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|1
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|640
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|0
suffix:semicolon
id|fptmp
op_assign
id|fpxin
suffix:semicolon
id|do_div
c_func
(paren
id|fptmp
comma
l_int|984
)paren
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OL
id|fptmp
)paren
suffix:semicolon
id|SFIL
op_assign
l_int|1
suffix:semicolon
id|fin
op_assign
id|state-&gt;config-&gt;xin
op_rshift
l_int|4
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
id|fin
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
id|fin
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
id|fin
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|fin
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
id|fin
op_div
l_int|2
)paren
op_div
id|fin
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
id|state-&gt;config-&gt;xin
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
c_func
(paren
id|state
comma
l_int|0x03
comma
id|NDEC
)paren
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x0a
comma
id|BDR
op_amp
l_int|0xff
)paren
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
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
c_func
(paren
id|state
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
c_func
(paren
id|state
comma
l_int|0x0d
comma
id|BDRI
)paren
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
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
DECL|function|ves1820_init
r_static
r_int
id|ves1820_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|val
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
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
(brace
id|val
op_assign
id|ves1820_inittab
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|2
)paren
op_logical_and
(paren
id|state-&gt;config-&gt;selagc
)paren
)paren
id|val
op_or_assign
l_int|0x08
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
comma
id|i
comma
id|val
)paren
suffix:semicolon
)brace
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x34
comma
id|state-&gt;pwm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;config-&gt;pll_init
)paren
id|state-&gt;config
op_member_access_from_pointer
id|pll_init
c_func
(paren
id|fe
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
c_func
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
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
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
id|state-&gt;config
op_member_access_from_pointer
id|pll_set
c_func
(paren
id|fe
comma
id|p
)paren
suffix:semicolon
id|ves1820_set_symbolrate
c_func
(paren
id|state
comma
id|p-&gt;u.qam.symbol_rate
)paren
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x34
comma
id|state-&gt;pwm
)paren
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
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
c_func
(paren
id|state
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
c_func
(paren
id|state
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
c_func
(paren
id|state
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
c_func
(paren
id|state
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
DECL|function|ves1820_read_status
r_static
r_int
id|ves1820_read_status
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_status_t
op_star
id|status
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
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
c_func
(paren
id|state
comma
l_int|0x11
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_read_ber
r_static
r_int
id|ves1820_read_ber
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
op_star
id|ber
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u32
id|_ber
op_assign
id|ves1820_readreg
c_func
(paren
id|state
comma
l_int|0x14
)paren
op_or
(paren
id|ves1820_readreg
c_func
(paren
id|state
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
id|state
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
id|ber
op_assign
l_int|10
op_star
id|_ber
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_read_signal_strength
r_static
r_int
id|ves1820_read_signal_strength
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
op_star
id|strength
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|gain
op_assign
id|ves1820_readreg
c_func
(paren
id|state
comma
l_int|0x17
)paren
suffix:semicolon
op_star
id|strength
op_assign
(paren
id|gain
op_lshift
l_int|8
)paren
op_or
id|gain
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_read_snr
r_static
r_int
id|ves1820_read_snr
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
op_star
id|snr
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|quality
op_assign
op_complement
id|ves1820_readreg
c_func
(paren
id|state
comma
l_int|0x18
)paren
suffix:semicolon
op_star
id|snr
op_assign
(paren
id|quality
op_lshift
l_int|8
)paren
op_or
id|quality
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_read_ucblocks
r_static
r_int
id|ves1820_read_ucblocks
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
op_star
id|ucblocks
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ucblocks
op_assign
id|ves1820_readreg
c_func
(paren
id|state
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
id|ucblocks
op_eq
l_int|0x7f
)paren
op_star
id|ucblocks
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* reset uncorrected block counter */
id|ves1820_writereg
c_func
(paren
id|state
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
c_func
(paren
id|state
comma
l_int|0x10
comma
id|ves1820_inittab
(braket
l_int|0x10
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_get_frontend
r_static
r_int
id|ves1820_get_frontend
c_func
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
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
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
c_func
(paren
id|state
comma
l_int|0x11
)paren
suffix:semicolon
id|afc
op_assign
id|ves1820_readreg
c_func
(paren
id|state
comma
l_int|0x19
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
multiline_comment|/* AFC only valid when carrier has been recovered */
id|printk
c_func
(paren
id|sync
op_amp
l_int|2
ques
c_cond
l_string|&quot;ves1820: AFC (%d) %dHz&bslash;n&quot;
suffix:colon
l_string|&quot;ves1820: [AFC (%d) %dHz]&bslash;n&quot;
comma
id|afc
comma
op_minus
(paren
(paren
id|s32
)paren
id|p-&gt;u.qam.symbol_rate
op_star
id|afc
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;config-&gt;invert
)paren
(brace
id|p-&gt;inversion
op_assign
(paren
id|state-&gt;reg0
op_amp
l_int|0x20
)paren
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;inversion
op_assign
(paren
op_logical_neg
(paren
id|state-&gt;reg0
op_amp
l_int|0x20
)paren
)paren
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
)brace
id|p-&gt;u.qam.modulation
op_assign
(paren
(paren
id|state-&gt;reg0
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
r_if
c_cond
(paren
id|sync
op_amp
l_int|2
)paren
id|p-&gt;frequency
op_sub_assign
(paren
(paren
id|s32
)paren
id|p-&gt;u.qam.symbol_rate
op_star
id|afc
)paren
op_rshift
l_int|10
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_sleep
r_static
r_int
id|ves1820_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x1b
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* pdown ADC */
id|ves1820_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* standby */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_get_tune_settings
r_static
r_int
id|ves1820_get_tune_settings
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_tune_settings
op_star
id|fesettings
)paren
(brace
id|fesettings-&gt;min_delay_ms
op_assign
l_int|200
suffix:semicolon
id|fesettings-&gt;step_size
op_assign
l_int|0
suffix:semicolon
id|fesettings-&gt;max_drift
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1820_release
r_static
r_void
id|ves1820_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
)brace
DECL|variable|ves1820_ops
r_static
r_struct
id|dvb_frontend_ops
id|ves1820_ops
suffix:semicolon
DECL|function|ves1820_attach
r_struct
id|dvb_frontend
op_star
id|ves1820_attach
c_func
(paren
r_const
r_struct
id|ves1820_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
comma
id|u8
id|pwm
)paren
(brace
r_struct
id|ves1820_state
op_star
id|state
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* allocate memory for the internal state */
id|state
op_assign
(paren
r_struct
id|ves1820_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ves1820_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* setup the state */
id|memcpy
c_func
(paren
op_amp
id|state-&gt;ops
comma
op_amp
id|ves1820_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
suffix:semicolon
id|state-&gt;reg0
op_assign
id|ves1820_inittab
(braket
l_int|0
)braket
suffix:semicolon
id|state-&gt;config
op_assign
id|config
suffix:semicolon
id|state-&gt;i2c
op_assign
id|i2c
suffix:semicolon
id|state-&gt;pwm
op_assign
id|pwm
suffix:semicolon
multiline_comment|/* check if the demod is there */
r_if
c_cond
(paren
(paren
id|ves1820_readreg
c_func
(paren
id|state
comma
l_int|0x1a
)paren
op_amp
l_int|0xf0
)paren
op_ne
l_int|0x70
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
l_string|&quot;ves1820: pwm=0x%02x&bslash;n&quot;
comma
id|state-&gt;pwm
)paren
suffix:semicolon
id|state-&gt;ops.info.symbol_rate_min
op_assign
(paren
id|state-&gt;config-&gt;xin
op_div
l_int|2
)paren
op_div
l_int|64
suffix:semicolon
multiline_comment|/* SACLK/64 == (XIN/2)/64 */
id|state-&gt;ops.info.symbol_rate_max
op_assign
(paren
id|state-&gt;config-&gt;xin
op_div
l_int|2
)paren
op_div
l_int|4
suffix:semicolon
multiline_comment|/* SACLK/4 */
multiline_comment|/* create dvb_frontend */
id|state-&gt;frontend.ops
op_assign
op_amp
id|state-&gt;ops
suffix:semicolon
id|state-&gt;frontend.demodulator_priv
op_assign
id|state
suffix:semicolon
r_return
op_amp
id|state-&gt;frontend
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|state
)paren
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|ves1820_ops
r_static
r_struct
id|dvb_frontend_ops
id|ves1820_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VLSI VES1820 DVB-C&quot;
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
)brace
comma
dot
id|release
op_assign
id|ves1820_release
comma
dot
id|init
op_assign
id|ves1820_init
comma
dot
id|sleep
op_assign
id|ves1820_sleep
comma
dot
id|set_frontend
op_assign
id|ves1820_set_parameters
comma
dot
id|get_frontend
op_assign
id|ves1820_get_frontend
comma
dot
id|get_tune_settings
op_assign
id|ves1820_get_tune_settings
comma
dot
id|read_status
op_assign
id|ves1820_read_status
comma
dot
id|read_ber
op_assign
id|ves1820_read_ber
comma
dot
id|read_signal_strength
op_assign
id|ves1820_read_signal_strength
comma
dot
id|read_snr
op_assign
id|ves1820_read_snr
comma
dot
id|read_ucblocks
op_assign
id|ves1820_read_ucblocks
comma
)brace
suffix:semicolon
id|module_param
c_func
(paren
id|verbose
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|verbose
comma
l_string|&quot;print AFC offset after tuning for debugging the PWM setting&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;VLSI VES1820 DVB-C Demodulator driver&quot;
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
DECL|variable|ves1820_attach
id|EXPORT_SYMBOL
c_func
(paren
id|ves1820_attach
)paren
suffix:semicolon
eof
