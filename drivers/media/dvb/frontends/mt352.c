multiline_comment|/*&n; *  Driver for Zarlink DVB-T MT352 demodulator&n; *&n; *  Written by Holger Waechtler &lt;holger@qanu.de&gt;&n; *&t; and Daniel Mack &lt;daniel@qanu.de&gt;&n; *&n; *  AVerMedia AVerTV DVB-T 771 support by&n; *       Wolfram Joost &lt;dbox2@frokaschwei.de&gt;&n; *&n; *  Support for Samsung TDTC9251DH01C(M) tuner&n; *  Copyright (C) 2004 Antonio Mancuso &lt;antonio.mancuso@digitaltelevision.it&gt;&n; *                     Amauri  Celani  &lt;acelani@essegi.net&gt;&n; *&n; *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Lite support by&n; *       Christopher Pascoe &lt;c.pascoe@itee.uq.edu.au&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.=&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;mt352_priv.h&quot;
macro_line|#include &quot;mt352.h&quot;
DECL|struct|mt352_state
r_struct
id|mt352_state
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
id|mt352_config
op_star
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(args...) &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (debug) printk(KERN_DEBUG &quot;mt352: &quot; args); &bslash;&n;} while (0)
DECL|function|mt352_single_write
r_static
r_int
id|mt352_single_write
c_func
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
id|val
)paren
(brace
r_struct
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|buf
(braket
l_int|2
)braket
op_assign
(brace
id|reg
comma
id|val
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
r_int
id|err
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
id|err
op_ne
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;mt352_write() to reg %x failed (err = %d)!&bslash;n&quot;
comma
id|reg
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_write
r_int
id|mt352_write
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
op_star
id|ibuf
comma
r_int
id|ilen
)paren
(brace
r_int
id|err
comma
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
id|ilen
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|mt352_single_write
c_func
(paren
id|fe
comma
id|ibuf
(braket
l_int|0
)braket
op_plus
id|i
comma
id|ibuf
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_read_register
r_static
id|u8
id|mt352_read_register
c_func
(paren
r_struct
id|mt352_state
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
DECL|function|mt352_read
id|u8
id|mt352_read
c_func
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
r_return
id|mt352_read_register
c_func
(paren
id|fe-&gt;demodulator_priv
comma
id|reg
)paren
suffix:semicolon
)brace
DECL|function|mt352_sleep
r_static
r_int
id|mt352_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_static
id|u8
id|mt352_softdown
(braket
)braket
op_assign
(brace
id|CLOCK_CTL
comma
l_int|0x20
comma
l_int|0x08
)brace
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_softdown
comma
r_sizeof
(paren
id|mt352_softdown
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_set_parameters
r_static
r_int
id|mt352_set_parameters
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
id|param
)paren
(brace
r_struct
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|14
)braket
suffix:semicolon
r_int
r_int
id|tps
op_assign
l_int|0
suffix:semicolon
r_struct
id|dvb_ofdm_parameters
op_star
id|op
op_assign
op_amp
id|param-&gt;u.ofdm
suffix:semicolon
r_int
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|op-&gt;code_rate_HP
)paren
(brace
r_case
id|FEC_2_3
suffix:colon
id|tps
op_or_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_3_4
suffix:colon
id|tps
op_or_assign
(paren
l_int|2
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_5_6
suffix:colon
id|tps
op_or_assign
(paren
l_int|3
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_7_8
suffix:colon
id|tps
op_or_assign
(paren
l_int|4
op_lshift
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_1_2
suffix:colon
r_case
id|FEC_AUTO
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|op-&gt;code_rate_LP
)paren
(brace
r_case
id|FEC_2_3
suffix:colon
id|tps
op_or_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_3_4
suffix:colon
id|tps
op_or_assign
(paren
l_int|2
op_lshift
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_5_6
suffix:colon
id|tps
op_or_assign
(paren
l_int|3
op_lshift
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_7_8
suffix:colon
id|tps
op_or_assign
(paren
l_int|4
op_lshift
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FEC_1_2
suffix:colon
r_case
id|FEC_AUTO
suffix:colon
r_break
suffix:semicolon
r_case
id|FEC_NONE
suffix:colon
r_if
c_cond
(paren
id|op-&gt;hierarchy_information
op_eq
id|HIERARCHY_AUTO
op_logical_or
id|op-&gt;hierarchy_information
op_eq
id|HIERARCHY_NONE
)paren
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|op-&gt;constellation
)paren
(brace
r_case
id|QPSK
suffix:colon
r_break
suffix:semicolon
r_case
id|QAM_AUTO
suffix:colon
r_case
id|QAM_16
suffix:colon
id|tps
op_or_assign
(paren
l_int|1
op_lshift
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_64
suffix:colon
id|tps
op_or_assign
(paren
l_int|2
op_lshift
l_int|13
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
r_switch
c_cond
(paren
id|op-&gt;transmission_mode
)paren
(brace
r_case
id|TRANSMISSION_MODE_2K
suffix:colon
r_case
id|TRANSMISSION_MODE_AUTO
suffix:colon
r_break
suffix:semicolon
r_case
id|TRANSMISSION_MODE_8K
suffix:colon
id|tps
op_or_assign
(paren
l_int|1
op_lshift
l_int|0
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
r_switch
c_cond
(paren
id|op-&gt;guard_interval
)paren
(brace
r_case
id|GUARD_INTERVAL_1_32
suffix:colon
r_case
id|GUARD_INTERVAL_AUTO
suffix:colon
r_break
suffix:semicolon
r_case
id|GUARD_INTERVAL_1_16
suffix:colon
id|tps
op_or_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GUARD_INTERVAL_1_8
suffix:colon
id|tps
op_or_assign
(paren
l_int|2
op_lshift
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GUARD_INTERVAL_1_4
suffix:colon
id|tps
op_or_assign
(paren
l_int|3
op_lshift
l_int|2
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
r_switch
c_cond
(paren
id|op-&gt;hierarchy_information
)paren
(brace
r_case
id|HIERARCHY_AUTO
suffix:colon
r_case
id|HIERARCHY_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|HIERARCHY_1
suffix:colon
id|tps
op_or_assign
(paren
l_int|1
op_lshift
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_2
suffix:colon
id|tps
op_or_assign
(paren
l_int|2
op_lshift
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HIERARCHY_4
suffix:colon
id|tps
op_or_assign
(paren
l_int|3
op_lshift
l_int|10
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
id|buf
(braket
l_int|0
)braket
op_assign
id|TPS_GIVEN_1
suffix:semicolon
multiline_comment|/* TPS_GIVEN_1 and following registers */
id|buf
(braket
l_int|1
)braket
op_assign
id|msb
c_func
(paren
id|tps
)paren
suffix:semicolon
multiline_comment|/* TPS_GIVEN_(1|0) */
id|buf
(braket
l_int|2
)braket
op_assign
id|lsb
c_func
(paren
id|tps
)paren
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x50
suffix:semicolon
multiline_comment|/**&n;&t; *  these settings assume 20.48MHz f_ADC, for other tuners you might&n;&t; *  need other values. See p. 33 in the MT352 Design Manual.&n;&t; */
r_if
c_cond
(paren
id|op-&gt;bandwidth
op_eq
id|BANDWIDTH_8_MHZ
)paren
(brace
id|buf
(braket
l_int|4
)braket
op_assign
l_int|0x72
suffix:semicolon
multiline_comment|/* TRL_NOMINAL_RATE_(1|0) */
id|buf
(braket
l_int|5
)braket
op_assign
l_int|0x49
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|op-&gt;bandwidth
op_eq
id|BANDWIDTH_7_MHZ
)paren
(brace
id|buf
(braket
l_int|4
)braket
op_assign
l_int|0x64
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
l_int|0x00
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 6MHz */
id|buf
(braket
l_int|4
)braket
op_assign
l_int|0x55
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
l_int|0xb7
suffix:semicolon
)brace
id|buf
(braket
l_int|6
)braket
op_assign
l_int|0x31
suffix:semicolon
multiline_comment|/* INPUT_FREQ_(1|0), 20.48MHz clock, 36.166667MHz IF */
id|buf
(braket
l_int|7
)braket
op_assign
l_int|0x05
suffix:semicolon
multiline_comment|/* see MT352 Design Manual page 32 for details */
id|state-&gt;config
op_member_access_from_pointer
id|pll_set
c_func
(paren
id|fe
comma
id|param
comma
id|buf
op_plus
l_int|8
)paren
suffix:semicolon
id|buf
(braket
l_int|13
)braket
op_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* TUNER_GO!! */
multiline_comment|/* Only send the tuning request if the tuner doesn&squot;t have the requested&n;&t; * parameters already set.  Enhances tuning time and prevents stream&n;&t; * breakup when retuning the same transponder. */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|13
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
op_ne
id|mt352_read_register
c_func
(paren
id|state
comma
id|i
op_plus
l_int|0x50
)paren
)paren
(brace
id|mt352_write
c_func
(paren
id|fe
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_get_parameters
r_static
r_int
id|mt352_get_parameters
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
id|param
)paren
(brace
r_struct
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u16
id|tps
suffix:semicolon
id|u16
id|div
suffix:semicolon
id|u8
id|trl
suffix:semicolon
r_struct
id|dvb_ofdm_parameters
op_star
id|op
op_assign
op_amp
id|param-&gt;u.ofdm
suffix:semicolon
r_static
r_const
id|u8
id|tps_fec_to_api
(braket
l_int|8
)braket
op_assign
(brace
id|FEC_1_2
comma
id|FEC_2_3
comma
id|FEC_3_4
comma
id|FEC_5_6
comma
id|FEC_7_8
comma
id|FEC_AUTO
comma
id|FEC_AUTO
comma
id|FEC_AUTO
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
l_int|0x00
)paren
op_amp
l_int|0xC0
)paren
op_ne
l_int|0xC0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Use TPS_RECEIVED-registers, not the TPS_CURRENT-registers because&n;&t; * the mt352 sometimes works with the wrong parameters&n;&t; */
id|tps
op_assign
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
id|TPS_RECEIVED_1
)paren
op_lshift
l_int|8
)paren
op_or
id|mt352_read_register
c_func
(paren
id|state
comma
id|TPS_RECEIVED_0
)paren
suffix:semicolon
id|div
op_assign
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
id|CHAN_START_1
)paren
op_lshift
l_int|8
)paren
op_or
id|mt352_read_register
c_func
(paren
id|state
comma
id|CHAN_START_0
)paren
suffix:semicolon
id|trl
op_assign
id|mt352_read_register
c_func
(paren
id|state
comma
id|TRL_NOMINAL_RATE_1
)paren
suffix:semicolon
id|op-&gt;code_rate_HP
op_assign
id|tps_fec_to_api
(braket
(paren
id|tps
op_rshift
l_int|7
)paren
op_amp
l_int|7
)braket
suffix:semicolon
id|op-&gt;code_rate_LP
op_assign
id|tps_fec_to_api
(braket
(paren
id|tps
op_rshift
l_int|4
)paren
op_amp
l_int|7
)braket
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|tps
op_rshift
l_int|13
)paren
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|op-&gt;constellation
op_assign
id|QPSK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|op-&gt;constellation
op_assign
id|QAM_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|op-&gt;constellation
op_assign
id|QAM_64
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|op-&gt;constellation
op_assign
id|QAM_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|op-&gt;transmission_mode
op_assign
(paren
id|tps
op_amp
l_int|0x01
)paren
ques
c_cond
id|TRANSMISSION_MODE_8K
suffix:colon
id|TRANSMISSION_MODE_2K
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|tps
op_rshift
l_int|2
)paren
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|op-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|op-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|op-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|op-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|op-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|tps
op_rshift
l_int|10
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|op-&gt;hierarchy_information
op_assign
id|HIERARCHY_NONE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|op-&gt;hierarchy_information
op_assign
id|HIERARCHY_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|op-&gt;hierarchy_information
op_assign
id|HIERARCHY_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|op-&gt;hierarchy_information
op_assign
id|HIERARCHY_4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|op-&gt;hierarchy_information
op_assign
id|HIERARCHY_AUTO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|param-&gt;frequency
op_assign
(paren
l_int|500
op_star
(paren
id|div
op_minus
id|IF_FREQUENCYx6
)paren
)paren
op_div
l_int|3
op_star
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|trl
op_eq
l_int|0x72
)paren
(brace
id|op-&gt;bandwidth
op_assign
id|BANDWIDTH_8_MHZ
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|trl
op_eq
l_int|0x64
)paren
(brace
id|op-&gt;bandwidth
op_assign
id|BANDWIDTH_7_MHZ
suffix:semicolon
)brace
r_else
(brace
id|op-&gt;bandwidth
op_assign
id|BANDWIDTH_6_MHZ
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
id|STATUS_2
)paren
op_amp
l_int|0x02
)paren
id|param-&gt;inversion
op_assign
id|INVERSION_OFF
suffix:semicolon
r_else
id|param-&gt;inversion
op_assign
id|INVERSION_ON
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_read_status
r_static
r_int
id|mt352_read_status
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
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|r
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
id|r
op_assign
id|mt352_read_register
(paren
id|state
comma
id|STATUS_0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_amp
(paren
l_int|1
op_lshift
l_int|4
)paren
)paren
op_star
id|status
op_assign
id|FE_HAS_CARRIER
suffix:semicolon
r_if
c_cond
(paren
id|r
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
op_star
id|status
op_or_assign
id|FE_HAS_VITERBI
suffix:semicolon
r_if
c_cond
(paren
id|r
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
op_star
id|status
op_or_assign
id|FE_HAS_LOCK
suffix:semicolon
id|r
op_assign
id|mt352_read_register
(paren
id|state
comma
id|STATUS_1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_amp
(paren
l_int|1
op_lshift
l_int|1
)paren
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SYNC
suffix:semicolon
id|r
op_assign
id|mt352_read_register
(paren
id|state
comma
id|STATUS_3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_amp
(paren
l_int|1
op_lshift
l_int|6
)paren
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SIGNAL
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|status
op_amp
(paren
id|FE_HAS_CARRIER
op_or
id|FE_HAS_VITERBI
op_or
id|FE_HAS_SYNC
)paren
)paren
op_ne
(paren
id|FE_HAS_CARRIER
op_or
id|FE_HAS_VITERBI
op_or
id|FE_HAS_SYNC
)paren
)paren
op_star
id|status
op_and_assign
op_complement
id|FE_HAS_LOCK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_read_ber
r_static
r_int
id|mt352_read_ber
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
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ber
op_assign
(paren
id|mt352_read_register
(paren
id|state
comma
id|RS_ERR_CNT_2
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|mt352_read_register
(paren
id|state
comma
id|RS_ERR_CNT_1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|mt352_read_register
(paren
id|state
comma
id|RS_ERR_CNT_0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_read_signal_strength
r_static
r_int
id|mt352_read_signal_strength
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
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u16
id|signal
op_assign
(paren
id|mt352_read_register
(paren
id|state
comma
id|AGC_GAIN_3
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|mt352_read_register
(paren
id|state
comma
id|AGC_GAIN_2
)paren
)paren
suffix:semicolon
op_star
id|strength
op_assign
op_complement
id|signal
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_read_snr
r_static
r_int
id|mt352_read_snr
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
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|_snr
op_assign
id|mt352_read_register
(paren
id|state
comma
id|SNR
)paren
suffix:semicolon
op_star
id|snr
op_assign
(paren
id|_snr
op_lshift
l_int|8
)paren
op_or
id|_snr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_read_ucblocks
r_static
r_int
id|mt352_read_ucblocks
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
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ucblocks
op_assign
(paren
id|mt352_read_register
(paren
id|state
comma
id|RS_UBC_1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|mt352_read_register
(paren
id|state
comma
id|RS_UBC_0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_get_tune_settings
r_static
r_int
id|mt352_get_tune_settings
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
id|fe_tune_settings
)paren
(brace
id|fe_tune_settings-&gt;min_delay_ms
op_assign
l_int|800
suffix:semicolon
id|fe_tune_settings-&gt;step_size
op_assign
l_int|0
suffix:semicolon
id|fe_tune_settings-&gt;max_drift
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_init
r_static
r_int
id|mt352_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_static
id|u8
id|mt352_reset_attach
(braket
)braket
op_assign
(brace
id|RESET
comma
l_int|0xC0
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
id|CLOCK_CTL
)paren
op_amp
l_int|0x10
)paren
op_eq
l_int|0
op_logical_or
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
id|CONFIG
)paren
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Do a &quot;hard&quot; reset */
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_reset_attach
comma
r_sizeof
(paren
id|mt352_reset_attach
)paren
)paren
suffix:semicolon
r_return
id|state-&gt;config
op_member_access_from_pointer
id|demod_init
c_func
(paren
id|fe
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt352_release
r_static
r_void
id|mt352_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|mt352_state
op_star
id|state
op_assign
(paren
r_struct
id|mt352_state
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
DECL|variable|mt352_ops
r_static
r_struct
id|dvb_frontend_ops
id|mt352_ops
suffix:semicolon
DECL|function|mt352_attach
r_struct
id|dvb_frontend
op_star
id|mt352_attach
c_func
(paren
r_const
r_struct
id|mt352_config
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
id|mt352_state
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
id|mt352_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mt352_state
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
id|mt352_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
suffix:semicolon
multiline_comment|/* check if the demod is there */
r_if
c_cond
(paren
id|mt352_read_register
c_func
(paren
id|state
comma
id|CHIP_ID
)paren
op_ne
id|ID_MT352
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
DECL|variable|mt352_ops
r_static
r_struct
id|dvb_frontend_ops
id|mt352_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Zarlink MT352 DVB-T&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
comma
dot
id|frequency_min
op_assign
l_int|174000000
comma
dot
id|frequency_max
op_assign
l_int|862000000
comma
dot
id|frequency_stepsize
op_assign
l_int|166667
comma
dot
id|frequency_tolerance
op_assign
l_int|0
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
id|FE_CAN_TRANSMISSION_MODE_AUTO
op_or
id|FE_CAN_GUARD_INTERVAL_AUTO
op_or
id|FE_CAN_HIERARCHY_AUTO
op_or
id|FE_CAN_RECOVER
op_or
id|FE_CAN_MUTE_TS
)brace
comma
dot
id|release
op_assign
id|mt352_release
comma
dot
id|init
op_assign
id|mt352_init
comma
dot
id|sleep
op_assign
id|mt352_sleep
comma
dot
id|set_frontend
op_assign
id|mt352_set_parameters
comma
dot
id|get_frontend
op_assign
id|mt352_get_parameters
comma
dot
id|get_tune_settings
op_assign
id|mt352_get_tune_settings
comma
dot
id|read_status
op_assign
id|mt352_read_status
comma
dot
id|read_ber
op_assign
id|mt352_read_ber
comma
dot
id|read_signal_strength
op_assign
id|mt352_read_signal_strength
comma
dot
id|read_snr
op_assign
id|mt352_read_snr
comma
dot
id|read_ucblocks
op_assign
id|mt352_read_ucblocks
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
l_string|&quot;Turn on/off frontend debugging (default:off).&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Zarlink MT352 DVB-T Demodulator driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Holger Waechtler, Daniel Mack, Antonio Mancuso&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|mt352_attach
id|EXPORT_SYMBOL
c_func
(paren
id|mt352_attach
)paren
suffix:semicolon
DECL|variable|mt352_write
id|EXPORT_SYMBOL
c_func
(paren
id|mt352_write
)paren
suffix:semicolon
DECL|variable|mt352_read
id|EXPORT_SYMBOL
c_func
(paren
id|mt352_read
)paren
suffix:semicolon
eof
