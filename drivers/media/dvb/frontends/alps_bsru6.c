multiline_comment|/* &n;    Alps BSRU6 DVB QPSK frontend driver&n;&n;    Copyright (C) 2001-2002 Convergence Integrated Media GmbH&n;&t;&lt;ralph@convergence.de&gt;, &lt;holger@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
DECL|macro|M_CLK
mdefine_line|#define M_CLK (88000000UL)
multiline_comment|/* M=21, K=0, P=0, f_VCO = 4MHz*4*(M+1)/(K+1) = 352 MHz */
r_static
DECL|variable|bsru6_info
r_struct
id|dvb_frontend_info
id|bsru6_info
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Alps BSRU6&quot;
comma
id|type
suffix:colon
id|FE_QPSK
comma
id|frequency_min
suffix:colon
l_int|950000
comma
id|frequency_max
suffix:colon
l_int|2150000
comma
id|frequency_stepsize
suffix:colon
l_int|125
comma
multiline_comment|/* kHz for QPSK frontends */
id|frequency_tolerance
suffix:colon
id|M_CLK
op_div
l_int|2000
comma
id|symbol_rate_min
suffix:colon
l_int|1000000
comma
id|symbol_rate_max
suffix:colon
l_int|45000000
comma
id|symbol_rate_tolerance
suffix:colon
l_int|500
comma
multiline_comment|/* ppm */
id|notifier_delay
suffix:colon
l_int|0
comma
id|caps
suffix:colon
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
r_static
DECL|variable|init_tab
id|u8
id|init_tab
(braket
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x15
comma
singleline_comment|// M: 0x15 DIRCLK: 0 K:0
l_int|0x02
comma
l_int|0x30
comma
singleline_comment|// P: 0  SERCLK: 0 VCO:ON  STDBY:0
l_int|0x03
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x7d
comma
singleline_comment|// F22FR, F22=22kHz
l_int|0x05
comma
l_int|0x35
comma
singleline_comment|// SDAT:0 SCLT:0 I2CT:1
l_int|0x06
comma
l_int|0x00
comma
singleline_comment|// DAC mode and MSB 
l_int|0x07
comma
l_int|0x00
comma
singleline_comment|// DAC LSB
l_int|0x08
comma
l_int|0x43
comma
singleline_comment|// DiSEqC
l_int|0x09
comma
l_int|0x00
comma
l_int|0x0a
comma
l_int|0x42
comma
l_int|0x0c
comma
l_int|0x51
comma
singleline_comment|// QPSK reverse:1  Nyquist:0 OP0 val:1 OP0 con:1 OP1 val:1 OP1 con:1 
l_int|0x0d
comma
l_int|0x82
comma
l_int|0x0e
comma
l_int|0x23
comma
l_int|0x0f
comma
l_int|0x52
comma
l_int|0x10
comma
l_int|0x3d
comma
singleline_comment|// AGC2
l_int|0x11
comma
l_int|0x84
comma
l_int|0x12
comma
l_int|0xb5
comma
singleline_comment|// Lock detect: -64  Carrier freq detect:on
l_int|0x13
comma
l_int|0xb6
comma
singleline_comment|// alpha_car b:4 a:0  noise est:256ks  derot:on 
l_int|0x14
comma
l_int|0x93
comma
singleline_comment|// beat carc:0 d:0 e:0xf  phase detect algo: 1
l_int|0x15
comma
l_int|0xc9
comma
singleline_comment|// lock detector threshold
l_int|0x16
comma
l_int|0x1d
comma
l_int|0x17
comma
l_int|0x0
comma
l_int|0x18
comma
l_int|0x14
comma
l_int|0x19
comma
l_int|0xf2
comma
l_int|0x1a
comma
l_int|0x11
comma
l_int|0x1b
comma
l_int|0x9c
comma
l_int|0x1c
comma
l_int|0x0
comma
l_int|0x1d
comma
l_int|0x0
comma
l_int|0x1e
comma
l_int|0xb
comma
l_int|0x22
comma
l_int|0x00
comma
l_int|0x23
comma
l_int|0x00
comma
l_int|0x24
comma
l_int|0xff
comma
l_int|0x25
comma
l_int|0xff
comma
l_int|0x26
comma
l_int|0xff
comma
l_int|0x28
comma
l_int|0x00
comma
singleline_comment|// out imp: normal  out type: parallel FEC mode:0 
l_int|0x29
comma
l_int|0x1e
comma
singleline_comment|// 1/2 threshold
l_int|0x2a
comma
l_int|0x14
comma
singleline_comment|// 2/3 threshold
l_int|0x2b
comma
l_int|0x0f
comma
singleline_comment|// 3/4 threshold
l_int|0x2c
comma
l_int|0x09
comma
singleline_comment|// 5/6 threshold
l_int|0x2d
comma
l_int|0x05
comma
singleline_comment|// 7/8 threshold
l_int|0x2e
comma
l_int|0x01
comma
l_int|0x31
comma
l_int|0x1f
comma
singleline_comment|// test all FECs 
l_int|0x32
comma
l_int|0x19
comma
singleline_comment|// viterbi and synchro search
l_int|0x33
comma
l_int|0xfc
comma
singleline_comment|// rs control
l_int|0x34
comma
l_int|0x93
comma
singleline_comment|// error control
l_int|0x0b
comma
l_int|0x00
comma
l_int|0x27
comma
l_int|0x00
comma
l_int|0x2f
comma
l_int|0x00
comma
l_int|0x30
comma
l_int|0x00
comma
l_int|0x35
comma
l_int|0x00
comma
l_int|0x36
comma
l_int|0x00
comma
l_int|0x37
comma
l_int|0x00
comma
l_int|0x38
comma
l_int|0x00
comma
l_int|0x39
comma
l_int|0x00
comma
l_int|0x3a
comma
l_int|0x00
comma
l_int|0x3b
comma
l_int|0x00
comma
l_int|0x3c
comma
l_int|0x00
comma
l_int|0x3d
comma
l_int|0x00
comma
l_int|0x3e
comma
l_int|0x00
comma
l_int|0x3f
comma
l_int|0x00
comma
l_int|0x40
comma
l_int|0x00
comma
l_int|0x41
comma
l_int|0x00
comma
l_int|0x42
comma
l_int|0x00
comma
l_int|0x43
comma
l_int|0x00
comma
l_int|0x44
comma
l_int|0x00
comma
l_int|0x45
comma
l_int|0x00
comma
l_int|0x46
comma
l_int|0x00
comma
l_int|0x47
comma
l_int|0x00
comma
l_int|0x48
comma
l_int|0x00
comma
l_int|0x49
comma
l_int|0x00
comma
l_int|0x4a
comma
l_int|0x00
comma
l_int|0x4b
comma
l_int|0x00
comma
l_int|0x4c
comma
l_int|0x00
comma
l_int|0x4d
comma
l_int|0x00
comma
l_int|0x4e
comma
l_int|0x00
comma
l_int|0x4f
comma
l_int|0x00
)brace
suffix:semicolon
r_static
DECL|function|stv0299_writereg
r_int
id|stv0299_writereg
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
l_int|0x68
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
l_int|2
)brace
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
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
l_string|&quot;%s: writereg error (reg == 0x%02x, val == 0x%02x, ret == %i)&bslash;n&quot;
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
r_static
DECL|function|stv0299_readreg
id|u8
id|stv0299_readreg
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
l_int|0x68
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
l_int|0x68
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
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
DECL|function|stv0299_readregs
r_int
id|stv0299_readregs
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
id|reg1
comma
id|u8
op_star
id|b
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
(braket
)braket
op_assign
(brace
(brace
id|addr
suffix:colon
l_int|0x68
comma
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
op_amp
id|reg1
comma
id|len
suffix:colon
l_int|1
)brace
comma
(brace
id|addr
suffix:colon
l_int|0x68
comma
id|flags
suffix:colon
id|I2C_M_RD
comma
id|buf
suffix:colon
id|b
comma
id|len
suffix:colon
id|len
)brace
)brace
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
id|ret
op_eq
l_int|2
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_static
DECL|function|tsa5059_write
r_int
id|tsa5059_write
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
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
id|u8
id|rpt1
(braket
)braket
op_assign
(brace
l_int|0x05
comma
l_int|0xb5
)brace
suffix:semicolon
multiline_comment|/*  enable i2c repeater on stv0299  */
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
l_int|0x68
comma
id|flags
suffix:colon
l_int|0
comma
id|buf
suffix:colon
id|rpt1
comma
id|len
suffix:colon
l_int|2
)brace
comma
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
id|data
comma
id|len
suffix:colon
l_int|4
)brace
)brace
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
l_int|2
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *   set up the downconverter frequency divisor for a &n; *   reference clock comparision frequency of 125 kHz.&n; */
r_static
DECL|function|tsa5059_set_tv_freq
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
comma
id|u8
id|pwr
)paren
(brace
id|u32
id|div
op_assign
id|freq
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
l_int|0x84
comma
(paren
id|pwr
op_lshift
l_int|5
)paren
op_or
l_int|0x20
)brace
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|tsa5059_write
(paren
id|i2c
comma
id|buf
)paren
suffix:semicolon
)brace
r_static
DECL|function|stv0299_init
r_int
id|stv0299_init
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
id|dprintk
c_func
(paren
l_string|&quot;stv0299: init chip&bslash;n&quot;
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
r_sizeof
(paren
id|init_tab
)paren
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|stv0299_writereg
(paren
id|i2c
comma
id|init_tab
(braket
id|i
)braket
comma
id|init_tab
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|stv0299_set_inversion
r_int
id|stv0299_set_inversion
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_int
id|inversion
)paren
(brace
id|u8
id|val
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|inversion
)paren
(brace
r_case
id|INVERSION_AUTO
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|INVERSION_OFF
suffix:colon
id|val
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x0c
)paren
suffix:semicolon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
id|val
op_or
l_int|0x01
)paren
suffix:semicolon
r_case
id|INVERSION_ON
suffix:colon
id|val
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x0c
)paren
suffix:semicolon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
id|val
op_amp
l_int|0xfe
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
r_static
DECL|function|stv0299_set_FEC
r_int
id|stv0299_set_FEC
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
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|fec
)paren
(brace
r_case
id|FEC_AUTO
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x31
comma
l_int|0x1f
)paren
suffix:semicolon
r_case
id|FEC_1_2
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x31
comma
l_int|0x01
)paren
suffix:semicolon
r_case
id|FEC_2_3
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x31
comma
l_int|0x02
)paren
suffix:semicolon
r_case
id|FEC_3_4
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x31
comma
l_int|0x04
)paren
suffix:semicolon
r_case
id|FEC_5_6
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x31
comma
l_int|0x08
)paren
suffix:semicolon
r_case
id|FEC_7_8
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x31
comma
l_int|0x10
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
r_static
DECL|function|stv0299_get_FEC
id|fe_code_rate_t
id|stv0299_get_FEC
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_static
id|fe_code_rate_t
id|fec_tab
(braket
)braket
op_assign
(brace
id|FEC_2_3
comma
id|FEC_3_4
comma
id|FEC_5_6
comma
id|FEC_7_8
comma
id|FEC_1_2
)brace
suffix:semicolon
id|u8
id|index
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|index
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x1b
)paren
suffix:semicolon
id|index
op_and_assign
l_int|0x7
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
l_int|4
)paren
r_return
id|FEC_AUTO
suffix:semicolon
r_return
id|fec_tab
(braket
id|index
)braket
suffix:semicolon
)brace
r_static
DECL|function|stv0299_wait_diseqc_fifo
r_int
id|stv0299_wait_diseqc_fifo
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_int
id|timeout
)paren
(brace
r_int
r_int
id|start
op_assign
id|jiffies
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_while
c_loop
(paren
id|stv0299_readreg
c_func
(paren
id|i2c
comma
l_int|0x0a
)paren
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_minus
id|start
OG
id|timeout
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s: timeout!!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
(paren
l_int|1
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|stv0299_wait_diseqc_idle
r_int
id|stv0299_wait_diseqc_idle
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_int
id|timeout
)paren
(brace
r_int
r_int
id|start
op_assign
id|jiffies
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|stv0299_readreg
c_func
(paren
id|i2c
comma
l_int|0x0a
)paren
op_amp
l_int|3
)paren
op_ne
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_minus
id|start
OG
id|timeout
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s: timeout!!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
(paren
l_int|1
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|stv0299_send_diseqc_msg
r_int
id|stv0299_send_diseqc_msg
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_struct
id|dvb_diseqc_master_cmd
op_star
id|m
)paren
(brace
id|u8
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|val
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x08
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x08
comma
(paren
id|val
op_amp
op_complement
l_int|0x7
)paren
op_or
l_int|0x6
)paren
)paren
multiline_comment|/* DiSEqC mode */
r_return
op_minus
id|EREMOTEIO
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
id|m-&gt;msg_len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|stv0299_wait_diseqc_fifo
(paren
id|i2c
comma
l_int|100
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x09
comma
id|m-&gt;msg
(braket
id|i
)braket
)paren
)paren
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
multiline_comment|/* Shouldn&squot;t we wait for idle state (FE=1, FF=0) here to &n;&t;   make certain all bytes have been sent ? &n;&t;   Hmm, actually we should do that before all mode changes too ...&n;&t;   if (stv0299_wait_diseqc_idle (i2c, 100) &lt; 0) */
r_if
c_cond
(paren
id|stv0299_wait_diseqc_fifo
(paren
id|i2c
comma
l_int|100
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|stv0299_send_diseqc_burst
r_int
id|stv0299_send_diseqc_burst
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_sec_mini_cmd_t
id|burst
)paren
(brace
id|u8
id|val
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|val
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x08
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_wait_diseqc_fifo
(paren
id|i2c
comma
l_int|100
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x08
comma
(paren
id|val
op_amp
op_complement
l_int|0x7
)paren
op_or
l_int|0x2
)paren
)paren
multiline_comment|/* burst mode */
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x09
comma
id|burst
op_eq
id|SEC_MINI_A
ques
c_cond
l_int|0x00
suffix:colon
l_int|0xff
)paren
)paren
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_wait_diseqc_fifo
(paren
id|i2c
comma
l_int|100
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
r_if
c_cond
(paren
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x08
comma
id|val
)paren
)paren
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|stv0299_set_tone
r_int
id|stv0299_set_tone
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_sec_tone_mode_t
id|tone
)paren
(brace
id|u8
id|val
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|val
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x08
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tone
)paren
(brace
r_case
id|SEC_TONE_ON
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x08
comma
id|val
op_or
l_int|0x3
)paren
suffix:semicolon
r_case
id|SEC_TONE_OFF
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x08
comma
(paren
id|val
op_amp
op_complement
l_int|0x3
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
)brace
r_static
DECL|function|stv0299_set_voltage
r_int
id|stv0299_set_voltage
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
id|u8
id|val
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|val
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x0c
)paren
suffix:semicolon
id|val
op_and_assign
l_int|0x0f
suffix:semicolon
id|val
op_or_assign
l_int|0x40
suffix:semicolon
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
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
id|val
)paren
suffix:semicolon
r_case
id|SEC_VOLTAGE_18
suffix:colon
r_return
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
id|val
op_or
l_int|0x10
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
)brace
r_static
DECL|function|stv0299_set_symbolrate
r_int
id|stv0299_set_symbolrate
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
id|ratio
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|u8
id|aclk
op_assign
l_int|0xb4
comma
id|bclk
op_assign
l_int|0x51
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srate
OG
id|M_CLK
)paren
id|srate
op_assign
id|M_CLK
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
r_if
c_cond
(paren
id|srate
OL
l_int|30000000
)paren
(brace
id|aclk
op_assign
l_int|0xb6
suffix:semicolon
id|bclk
op_assign
l_int|0x53
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srate
OL
l_int|14000000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x53
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srate
OL
l_int|7000000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x4f
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srate
OL
l_int|3000000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x4b
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srate
OL
l_int|1500000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x47
suffix:semicolon
)brace
DECL|macro|FIN
mdefine_line|#define FIN (M_CLK &gt;&gt; 4)
id|tmp
op_assign
id|srate
op_lshift
l_int|4
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
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x13
comma
id|aclk
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x14
comma
id|bclk
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x1f
comma
(paren
id|ratio
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x20
comma
(paren
id|ratio
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x21
comma
(paren
id|ratio
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|stv0299_get_symbolrate
r_int
id|stv0299_get_symbolrate
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|u32
id|Mclk
op_assign
id|M_CLK
op_div
l_int|4096L
suffix:semicolon
id|u32
id|srate
suffix:semicolon
id|s32
id|offset
suffix:semicolon
id|u8
id|sfr
(braket
l_int|3
)braket
suffix:semicolon
id|s8
id|rtf
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|stv0299_readregs
(paren
id|i2c
comma
l_int|0x1f
comma
id|sfr
comma
l_int|3
)paren
suffix:semicolon
id|stv0299_readregs
(paren
id|i2c
comma
l_int|0x1a
comma
op_amp
id|rtf
comma
l_int|1
)paren
suffix:semicolon
id|srate
op_assign
(paren
id|sfr
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|sfr
(braket
l_int|1
)braket
suffix:semicolon
id|srate
op_mul_assign
id|Mclk
suffix:semicolon
id|srate
op_div_assign
l_int|16
suffix:semicolon
id|srate
op_add_assign
(paren
id|sfr
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_star
id|Mclk
op_div
l_int|256
suffix:semicolon
id|offset
op_assign
(paren
id|s32
)paren
id|rtf
op_star
(paren
id|srate
op_div
l_int|4096L
)paren
suffix:semicolon
id|offset
op_div_assign
l_int|128
suffix:semicolon
id|srate
op_add_assign
id|offset
suffix:semicolon
id|srate
op_add_assign
l_int|1000
suffix:semicolon
id|srate
op_div_assign
l_int|2000
suffix:semicolon
id|srate
op_mul_assign
l_int|2000
suffix:semicolon
r_return
id|srate
suffix:semicolon
)brace
r_static
DECL|function|bsru6_ioctl
r_int
id|bsru6_ioctl
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
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
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
id|bsru6_info
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
id|u8
id|signal
op_assign
l_int|0xff
op_minus
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x18
)paren
suffix:semicolon
id|u8
id|sync
op_assign
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x1b
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
id|signal
OG
l_int|10
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
l_int|0x80
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
l_int|0x10
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
l_int|0x08
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
l_int|0x98
)paren
op_eq
l_int|0x98
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
(paren
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x1d
)paren
op_lshift
l_int|8
)paren
op_or
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x1e
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
(brace
id|s32
id|signal
op_assign
l_int|0xffff
op_minus
(paren
(paren
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x18
)paren
op_lshift
l_int|8
)paren
op_or
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x19
)paren
)paren
suffix:semicolon
id|signal
op_assign
id|signal
op_star
l_int|5
op_div
l_int|4
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
OG
l_int|0xffff
)paren
ques
c_cond
l_int|0xffff
suffix:colon
(paren
id|signal
OL
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
id|signal
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SNR
suffix:colon
(brace
id|s32
id|snr
op_assign
l_int|0xffff
op_minus
(paren
(paren
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x24
)paren
op_lshift
l_int|8
)paren
op_or
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x25
)paren
)paren
suffix:semicolon
id|snr
op_assign
l_int|3
op_star
(paren
id|snr
op_minus
l_int|0xa100
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
id|snr
OG
l_int|0xffff
)paren
ques
c_cond
l_int|0xffff
suffix:colon
(paren
id|snr
OL
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
id|snr
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
l_int|0
suffix:semicolon
multiline_comment|/* the stv0299 can&squot;t measure BER and */
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
multiline_comment|/* errors at the same time.... */
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
id|tsa5059_set_tv_freq
(paren
id|i2c
comma
id|p-&gt;frequency
comma
l_int|3
)paren
suffix:semicolon
id|stv0299_set_inversion
(paren
id|i2c
comma
id|p-&gt;inversion
)paren
suffix:semicolon
id|stv0299_set_FEC
(paren
id|i2c
comma
id|p-&gt;u.qpsk.fec_inner
)paren
suffix:semicolon
id|stv0299_set_symbolrate
(paren
id|i2c
comma
id|p-&gt;u.qpsk.symbol_rate
)paren
suffix:semicolon
id|tsa5059_set_tv_freq
(paren
id|i2c
comma
id|p-&gt;frequency
comma
l_int|0
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x22
comma
l_int|0x00
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x23
comma
l_int|0x00
)paren
suffix:semicolon
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x23
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x12
comma
l_int|0xb9
)paren
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
id|s32
id|derot_freq
suffix:semicolon
id|derot_freq
op_assign
(paren
id|s32
)paren
(paren
id|s16
)paren
(paren
(paren
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x22
)paren
op_lshift
l_int|8
)paren
op_or
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x23
)paren
)paren
suffix:semicolon
id|derot_freq
op_mul_assign
(paren
id|M_CLK
op_rshift
l_int|16
)paren
suffix:semicolon
id|derot_freq
op_add_assign
l_int|500
suffix:semicolon
id|derot_freq
op_div_assign
l_int|1000
suffix:semicolon
id|p-&gt;frequency
op_add_assign
id|derot_freq
suffix:semicolon
id|p-&gt;inversion
op_assign
(paren
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x0c
)paren
op_amp
l_int|1
)paren
ques
c_cond
id|INVERSION_OFF
suffix:colon
id|INVERSION_ON
suffix:semicolon
id|p-&gt;u.qpsk.fec_inner
op_assign
id|stv0299_get_FEC
(paren
id|i2c
)paren
suffix:semicolon
id|p-&gt;u.qpsk.symbol_rate
op_assign
id|stv0299_get_symbolrate
(paren
id|i2c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_SLEEP
suffix:colon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*  LNB power off! */
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x02
comma
l_int|0x80
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_return
id|stv0299_init
(paren
id|i2c
)paren
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x22
comma
l_int|0x00
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x23
comma
l_int|0x00
)paren
suffix:semicolon
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x23
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|i2c
comma
l_int|0x12
comma
l_int|0xb9
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_DISEQC_SEND_MASTER_CMD
suffix:colon
r_return
id|stv0299_send_diseqc_msg
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_DISEQC_SEND_BURST
suffix:colon
r_return
id|stv0299_send_diseqc_burst
(paren
id|i2c
comma
(paren
id|fe_sec_mini_cmd_t
)paren
id|arg
)paren
suffix:semicolon
r_case
id|FE_SET_TONE
suffix:colon
r_return
id|stv0299_set_tone
(paren
id|i2c
comma
(paren
id|fe_sec_tone_mode_t
)paren
id|arg
)paren
suffix:semicolon
r_case
id|FE_SET_VOLTAGE
suffix:colon
r_return
id|stv0299_set_voltage
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
r_static
DECL|function|bsru6_attach
r_int
id|bsru6_attach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stv0299_readreg
(paren
id|i2c
comma
l_int|0x00
)paren
)paren
op_ne
l_int|0xa1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dvb_register_frontend
(paren
id|bsru6_ioctl
comma
id|i2c
comma
l_int|NULL
comma
op_amp
id|bsru6_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|bsru6_detach
r_void
id|bsru6_detach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dvb_unregister_frontend
(paren
id|bsru6_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
r_static
DECL|function|init_bsru6
r_int
id|__init
id|init_bsru6
(paren
r_void
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
id|dvb_register_i2c_device
(paren
id|THIS_MODULE
comma
id|bsru6_attach
comma
id|bsru6_detach
)paren
suffix:semicolon
)brace
r_static
DECL|function|exit_bsru6
r_void
id|__exit
id|exit_bsru6
(paren
r_void
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dvb_unregister_i2c_device
(paren
id|bsru6_attach
)paren
suffix:semicolon
)brace
DECL|variable|init_bsru6
id|module_init
(paren
id|init_bsru6
)paren
suffix:semicolon
DECL|variable|exit_bsru6
id|module_exit
(paren
id|exit_bsru6
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
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;enable verbose debug messages&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;BSRU6 DVB Frontend driver&quot;
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
