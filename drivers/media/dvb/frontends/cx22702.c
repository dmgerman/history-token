multiline_comment|/*&n;    Conexant 22702 DVB OFDM demodulator driver&n;&n;    based on:&n;        Alps TDMB7 DVB OFDM demodulator driver&n;&n;    Copyright (C) 2001-2002 Convergence Integrated Media GmbH&n;&t;  Holger Waechtler &lt;holger@convergence.de&gt;&n;&n;    Copyright (C) 2004 Steven Toth &lt;steve@toth.demon.co.uk&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;cx22702.h&quot;
DECL|struct|cx22702_state
r_struct
id|cx22702_state
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
id|cx22702_config
op_star
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
multiline_comment|/* previous uncorrected block counter */
DECL|member|prevUCBlocks
id|u8
id|prevUCBlocks
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk&t;if (debug) printk
multiline_comment|/* Register values to initialise the demod */
DECL|variable|init_tab
r_static
id|u8
id|init_tab
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* Stop aquisition */
l_int|0x0B
comma
l_int|0x06
comma
l_int|0x09
comma
l_int|0x01
comma
l_int|0x0D
comma
l_int|0x41
comma
l_int|0x16
comma
l_int|0x32
comma
l_int|0x20
comma
l_int|0x0A
comma
l_int|0x21
comma
l_int|0x17
comma
l_int|0x24
comma
l_int|0x3e
comma
l_int|0x26
comma
l_int|0xff
comma
l_int|0x27
comma
l_int|0x10
comma
l_int|0x28
comma
l_int|0x00
comma
l_int|0x29
comma
l_int|0x00
comma
l_int|0x2a
comma
l_int|0x10
comma
l_int|0x2b
comma
l_int|0x00
comma
l_int|0x2c
comma
l_int|0x10
comma
l_int|0x2d
comma
l_int|0x00
comma
l_int|0x48
comma
l_int|0xd4
comma
l_int|0x49
comma
l_int|0x56
comma
l_int|0x6b
comma
l_int|0x1e
comma
l_int|0xc8
comma
l_int|0x02
comma
l_int|0xf8
comma
l_int|0x02
comma
l_int|0xf9
comma
l_int|0x00
comma
l_int|0xfa
comma
l_int|0x00
comma
l_int|0xfb
comma
l_int|0x00
comma
l_int|0xfc
comma
l_int|0x00
comma
l_int|0xfd
comma
l_int|0x00
comma
)brace
suffix:semicolon
DECL|function|cx22702_writereg
r_static
r_int
id|cx22702_writereg
(paren
r_struct
id|cx22702_state
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
l_int|2
)brace
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
DECL|function|cx22702_readreg
r_static
id|u8
id|cx22702_readreg
(paren
r_struct
id|cx22702_state
op_star
id|state
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
l_int|1
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
DECL|function|cx22702_set_inversion
r_static
r_int
id|cx22702_set_inversion
(paren
r_struct
id|cx22702_state
op_star
id|state
comma
r_int
id|inversion
)paren
(brace
id|u8
id|val
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
id|INVERSION_ON
suffix:colon
id|val
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x0C
)paren
suffix:semicolon
r_return
id|cx22702_writereg
(paren
id|state
comma
l_int|0x0C
comma
id|val
op_or
l_int|0x01
)paren
suffix:semicolon
r_case
id|INVERSION_OFF
suffix:colon
id|val
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x0C
)paren
suffix:semicolon
r_return
id|cx22702_writereg
(paren
id|state
comma
l_int|0x0C
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
multiline_comment|/* Retrieve the demod settings */
DECL|function|cx22702_get_tps
r_static
r_int
id|cx22702_get_tps
(paren
r_struct
id|cx22702_state
op_star
id|state
comma
r_struct
id|dvb_ofdm_parameters
op_star
id|p
)paren
(brace
id|u8
id|val
suffix:semicolon
multiline_comment|/* Make sure the TPS regs are valid */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0A
)paren
op_amp
l_int|0x20
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|val
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x01
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|val
op_amp
l_int|0x18
)paren
op_rshift
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|p-&gt;constellation
op_assign
id|QPSK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;constellation
op_assign
id|QAM_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p-&gt;constellation
op_assign
id|QAM_64
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|val
op_amp
l_int|0x07
)paren
(brace
r_case
l_int|0
suffix:colon
id|p-&gt;hierarchy_information
op_assign
id|HIERARCHY_NONE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;hierarchy_information
op_assign
id|HIERARCHY_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p-&gt;hierarchy_information
op_assign
id|HIERARCHY_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p-&gt;hierarchy_information
op_assign
id|HIERARCHY_4
suffix:semicolon
r_break
suffix:semicolon
)brace
id|val
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x02
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|val
op_amp
l_int|0x38
)paren
op_rshift
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|p-&gt;code_rate_HP
op_assign
id|FEC_1_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;code_rate_HP
op_assign
id|FEC_2_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p-&gt;code_rate_HP
op_assign
id|FEC_3_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p-&gt;code_rate_HP
op_assign
id|FEC_5_6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|p-&gt;code_rate_HP
op_assign
id|FEC_7_8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|val
op_amp
l_int|0x07
)paren
(brace
r_case
l_int|0
suffix:colon
id|p-&gt;code_rate_LP
op_assign
id|FEC_1_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;code_rate_LP
op_assign
id|FEC_2_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p-&gt;code_rate_LP
op_assign
id|FEC_3_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p-&gt;code_rate_LP
op_assign
id|FEC_5_6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|p-&gt;code_rate_LP
op_assign
id|FEC_7_8
suffix:semicolon
r_break
suffix:semicolon
)brace
id|val
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x03
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|val
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)paren
(brace
r_case
l_int|0
suffix:colon
id|p-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|val
op_amp
l_int|0x03
)paren
(brace
r_case
l_int|0
suffix:colon
id|p-&gt;transmission_mode
op_assign
id|TRANSMISSION_MODE_2K
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p-&gt;transmission_mode
op_assign
id|TRANSMISSION_MODE_8K
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
DECL|function|cx22702_set_tps
r_static
r_int
id|cx22702_set_tps
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
id|u8
id|val
suffix:semicolon
r_struct
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
multiline_comment|/* set PLL */
id|cx22702_writereg
(paren
id|state
comma
l_int|0x0D
comma
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0D
)paren
op_amp
l_int|0xfe
)paren
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
id|cx22702_writereg
(paren
id|state
comma
l_int|0x0D
comma
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0D
)paren
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* set inversion */
id|cx22702_set_inversion
(paren
id|state
comma
id|p-&gt;inversion
)paren
suffix:semicolon
multiline_comment|/* set bandwidth */
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.bandwidth
)paren
(brace
r_case
id|BANDWIDTH_6_MHZ
suffix:colon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0C
comma
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0C
)paren
op_amp
l_int|0xcf
)paren
op_or
l_int|0x20
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BANDWIDTH_7_MHZ
suffix:colon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0C
comma
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0C
)paren
op_amp
l_int|0xcf
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BANDWIDTH_8_MHZ
suffix:colon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0C
comma
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0C
)paren
op_amp
l_int|0xcf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid bandwidth&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|p-&gt;u.ofdm.code_rate_LP
op_assign
id|FEC_AUTO
suffix:semicolon
singleline_comment|//temp hack as manual not working
multiline_comment|/* use auto configuration? */
r_if
c_cond
(paren
(paren
id|p-&gt;u.ofdm.hierarchy_information
op_eq
id|HIERARCHY_AUTO
)paren
op_logical_or
(paren
id|p-&gt;u.ofdm.constellation
op_eq
id|QAM_AUTO
)paren
op_logical_or
(paren
id|p-&gt;u.ofdm.code_rate_HP
op_eq
id|FEC_AUTO
)paren
op_logical_or
(paren
id|p-&gt;u.ofdm.code_rate_LP
op_eq
id|FEC_AUTO
)paren
op_logical_or
(paren
id|p-&gt;u.ofdm.guard_interval
op_eq
id|GUARD_INTERVAL_AUTO
)paren
op_logical_or
(paren
id|p-&gt;u.ofdm.transmission_mode
op_eq
id|TRANSMISSION_MODE_AUTO
)paren
)paren
(brace
multiline_comment|/* TPS Source - use hardware driven values */
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x06
comma
l_int|0x10
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x07
comma
l_int|0x9
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x08
comma
l_int|0xC1
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0B
comma
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0B
)paren
op_amp
l_int|0xfc
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0C
comma
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0C
)paren
op_amp
l_int|0xBF
)paren
op_or
l_int|0x40
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Begin aquisition */
id|printk
c_func
(paren
l_string|&quot;%s: Autodetecting&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* manually programmed values */
id|val
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.constellation
)paren
(brace
r_case
id|QPSK
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xe7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_16
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xe7
)paren
op_or
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_64
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xe7
)paren
op_or
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid constellation&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.hierarchy_information
)paren
(brace
r_case
id|HIERARCHY_NONE
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_1
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_2
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_4
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid hierarchy&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cx22702_writereg
(paren
id|state
comma
l_int|0x06
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.code_rate_HP
)paren
(brace
r_case
id|FEC_NONE
suffix:colon
r_case
id|FEC_1_2
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xc7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_2_3
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xc7
)paren
op_or
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_3_4
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xc7
)paren
op_or
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_5_6
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xc7
)paren
op_or
l_int|0x18
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_7_8
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xc7
)paren
op_or
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid code_rate_HP&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.code_rate_LP
)paren
(brace
r_case
id|FEC_NONE
suffix:colon
r_case
id|FEC_1_2
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_2_3
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_3_4
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_5_6
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_7_8
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf8
)paren
op_or
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid code_rate_LP&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cx22702_writereg
(paren
id|state
comma
l_int|0x07
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.guard_interval
)paren
(brace
r_case
id|GUARD_INTERVAL_1_32
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GUARD_INTERVAL_1_16
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf3
)paren
op_or
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GUARD_INTERVAL_1_8
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf3
)paren
op_or
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GUARD_INTERVAL_1_4
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xf3
)paren
op_or
l_int|0x0c
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid guard_interval&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p-&gt;u.ofdm.transmission_mode
)paren
(brace
r_case
id|TRANSMISSION_MODE_2K
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xfc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRANSMISSION_MODE_8K
suffix:colon
id|val
op_assign
(paren
id|val
op_amp
l_int|0xfc
)paren
op_or
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: invalid transmission_mode&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x08
comma
id|val
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0B
comma
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0B
)paren
op_amp
l_int|0xfc
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x0C
comma
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0C
)paren
op_amp
l_int|0xBF
)paren
op_or
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* Begin channel aquisition */
id|cx22702_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset the demod hardware and reset all of the configuration registers&n;   to a default state. */
DECL|function|cx22702_init
r_static
r_int
id|cx22702_init
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
r_struct
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|cx22702_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x02
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|10
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
id|cx22702_writereg
(paren
id|state
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
multiline_comment|/* init PLL */
r_if
c_cond
(paren
id|state-&gt;config-&gt;pll_init
)paren
(brace
id|cx22702_writereg
(paren
id|state
comma
l_int|0x0D
comma
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0D
)paren
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|pll_init
c_func
(paren
id|fe
)paren
suffix:semicolon
id|cx22702_writereg
(paren
id|state
comma
l_int|0x0D
comma
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x0D
)paren
op_or
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22702_read_status
r_static
r_int
id|cx22702_read_status
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
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|reg0A
suffix:semicolon
id|u8
id|reg23
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
id|reg0A
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x0A
)paren
suffix:semicolon
id|reg23
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x23
)paren
suffix:semicolon
id|dprintk
(paren
l_string|&quot;%s: status demod=0x%02x agc=0x%02x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reg0A
comma
id|reg23
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg0A
op_amp
l_int|0x10
)paren
(brace
op_star
id|status
op_or_assign
id|FE_HAS_LOCK
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_VITERBI
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_SYNC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg0A
op_amp
l_int|0x20
)paren
(brace
op_star
id|status
op_or_assign
id|FE_HAS_CARRIER
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reg23
OL
l_int|0xf0
)paren
(brace
op_star
id|status
op_or_assign
id|FE_HAS_SIGNAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22702_read_ber
r_static
r_int
id|cx22702_read_ber
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
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_if
c_cond
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xE4
)paren
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* Realtime statistics */
op_star
id|ber
op_assign
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDE
)paren
op_amp
l_int|0x7F
)paren
op_lshift
l_int|7
op_or
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDF
)paren
op_amp
l_int|0x7F
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Averagtine statistics */
op_star
id|ber
op_assign
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDE
)paren
op_amp
l_int|0x7F
)paren
op_lshift
l_int|7
op_or
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDF
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22702_read_signal_strength
r_static
r_int
id|cx22702_read_signal_strength
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
op_star
id|signal_strength
)paren
(brace
r_struct
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|signal_strength
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x23
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22702_read_snr
r_static
r_int
id|cx22702_read_snr
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
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u16
id|rs_ber
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xE4
)paren
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* Realtime statistics */
id|rs_ber
op_assign
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDE
)paren
op_amp
l_int|0x7F
)paren
op_lshift
l_int|7
op_or
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDF
)paren
op_amp
l_int|0x7F
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Averagine statistics */
id|rs_ber
op_assign
(paren
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDE
)paren
op_amp
l_int|0x7F
)paren
op_lshift
l_int|8
op_or
id|cx22702_readreg
(paren
id|state
comma
l_int|0xDF
)paren
suffix:semicolon
)brace
op_star
id|snr
op_assign
op_complement
id|rs_ber
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22702_read_ucblocks
r_static
r_int
id|cx22702_read_ucblocks
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
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|_ucblocks
suffix:semicolon
multiline_comment|/* RS Uncorrectable Packet Count then reset */
id|_ucblocks
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0xE3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;prevUCBlocks
OL
id|_ucblocks
)paren
op_star
id|ucblocks
op_assign
(paren
id|_ucblocks
op_minus
id|state-&gt;prevUCBlocks
)paren
suffix:semicolon
r_else
op_star
id|ucblocks
op_assign
id|state-&gt;prevUCBlocks
op_minus
id|_ucblocks
suffix:semicolon
id|state-&gt;prevUCBlocks
op_assign
id|_ucblocks
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22702_get_frontend
r_static
r_int
id|cx22702_get_frontend
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
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|reg0C
op_assign
id|cx22702_readreg
(paren
id|state
comma
l_int|0x0C
)paren
suffix:semicolon
id|p-&gt;inversion
op_assign
id|reg0C
op_amp
l_int|0x1
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
r_return
id|cx22702_get_tps
(paren
id|state
comma
op_amp
id|p-&gt;u.ofdm
)paren
suffix:semicolon
)brace
DECL|function|cx22702_release
r_static
r_void
id|cx22702_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|cx22702_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22702_state
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
DECL|variable|cx22702_ops
r_static
r_struct
id|dvb_frontend_ops
id|cx22702_ops
suffix:semicolon
DECL|function|cx22702_attach
r_struct
id|dvb_frontend
op_star
id|cx22702_attach
c_func
(paren
r_const
r_struct
id|cx22702_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
r_struct
id|cx22702_state
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
id|cx22702_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cx22702_state
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
id|state-&gt;config
op_assign
id|config
suffix:semicolon
id|state-&gt;i2c
op_assign
id|i2c
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|state-&gt;ops
comma
op_amp
id|cx22702_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
suffix:semicolon
id|state-&gt;prevUCBlocks
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* check if the demod is there */
r_if
c_cond
(paren
id|cx22702_readreg
c_func
(paren
id|state
comma
l_int|0x1f
)paren
op_ne
l_int|0x3
)paren
r_goto
id|error
suffix:semicolon
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
DECL|variable|cx22702_ops
r_static
r_struct
id|dvb_frontend_ops
id|cx22702_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Conexant CX22702 DVB-T&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
comma
dot
id|frequency_min
op_assign
l_int|177000000
comma
dot
id|frequency_max
op_assign
l_int|858000000
comma
dot
id|frequency_stepsize
op_assign
l_int|166666
comma
dot
id|caps
op_assign
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
op_or
id|FE_CAN_QAM_16
op_or
id|FE_CAN_QAM_64
op_or
id|FE_CAN_QAM_AUTO
op_or
id|FE_CAN_HIERARCHY_AUTO
op_or
id|FE_CAN_GUARD_INTERVAL_AUTO
op_or
id|FE_CAN_TRANSMISSION_MODE_AUTO
op_or
id|FE_CAN_RECOVER
)brace
comma
dot
id|release
op_assign
id|cx22702_release
comma
dot
id|init
op_assign
id|cx22702_init
comma
dot
id|set_frontend
op_assign
id|cx22702_set_tps
comma
dot
id|get_frontend
op_assign
id|cx22702_get_frontend
comma
dot
id|read_status
op_assign
id|cx22702_read_status
comma
dot
id|read_ber
op_assign
id|cx22702_read_ber
comma
dot
id|read_signal_strength
op_assign
id|cx22702_read_signal_strength
comma
dot
id|read_snr
op_assign
id|cx22702_read_snr
comma
dot
id|read_ucblocks
op_assign
id|cx22702_read_ucblocks
comma
)brace
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Enable verbose debug messages&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Conexant CX22702 DVB-T Demodulator driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Steven Toth&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cx22702_attach
id|EXPORT_SYMBOL
c_func
(paren
id|cx22702_attach
)paren
suffix:semicolon
eof
