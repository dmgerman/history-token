multiline_comment|/*&n;    Conexant cx22700 DVB OFDM demodulator driver&n;&n;    Copyright (C) 2001-2002 Convergence Integrated Media GmbH&n;&t;Holger Waechtler &lt;holger@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;cx22700.h&quot;
DECL|struct|cx22700_state
r_struct
id|cx22700_state
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
DECL|member|config
r_const
r_struct
id|cx22700_config
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
mdefine_line|#define dprintk(args...) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (debug) printk(KERN_DEBUG &quot;cx22700: &quot; args); &bslash;&n;&t;} while (0)
DECL|variable|init_tab
r_static
id|u8
id|init_tab
(braket
)braket
op_assign
(brace
l_int|0x04
comma
l_int|0x10
comma
l_int|0x05
comma
l_int|0x09
comma
l_int|0x06
comma
l_int|0x00
comma
l_int|0x08
comma
l_int|0x04
comma
l_int|0x09
comma
l_int|0x00
comma
l_int|0x0a
comma
l_int|0x01
comma
l_int|0x15
comma
l_int|0x40
comma
l_int|0x16
comma
l_int|0x10
comma
l_int|0x17
comma
l_int|0x87
comma
l_int|0x18
comma
l_int|0x17
comma
l_int|0x1a
comma
l_int|0x10
comma
l_int|0x25
comma
l_int|0x04
comma
l_int|0x2e
comma
l_int|0x00
comma
l_int|0x39
comma
l_int|0x00
comma
l_int|0x3a
comma
l_int|0x04
comma
l_int|0x45
comma
l_int|0x08
comma
l_int|0x46
comma
l_int|0x02
comma
l_int|0x47
comma
l_int|0x05
comma
)brace
suffix:semicolon
DECL|function|cx22700_writereg
r_static
r_int
id|cx22700_writereg
(paren
r_struct
id|cx22700_state
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
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ret
op_assign
id|i2c_transfer
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
DECL|function|cx22700_readreg
r_static
r_int
id|cx22700_readreg
(paren
r_struct
id|cx22700_state
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
id|dprintk
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|ret
op_assign
id|i2c_transfer
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
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|b1
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|cx22700_set_inversion
r_static
r_int
id|cx22700_set_inversion
(paren
r_struct
id|cx22700_state
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
id|INVERSION_ON
suffix:colon
id|val
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x09
)paren
suffix:semicolon
r_return
id|cx22700_writereg
(paren
id|state
comma
l_int|0x09
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
id|cx22700_readreg
(paren
id|state
comma
l_int|0x09
)paren
suffix:semicolon
r_return
id|cx22700_writereg
(paren
id|state
comma
l_int|0x09
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
DECL|function|cx22700_set_tps
r_static
r_int
id|cx22700_set_tps
(paren
r_struct
id|cx22700_state
op_star
id|state
comma
r_struct
id|dvb_ofdm_parameters
op_star
id|p
)paren
(brace
r_static
r_const
id|u8
id|qam_tab
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|2
)brace
suffix:semicolon
r_static
r_const
id|u8
id|fec_tab
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|3
comma
l_int|4
)brace
suffix:semicolon
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
r_if
c_cond
(paren
id|p-&gt;code_rate_HP
template_param
id|FEC_7_8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;code_rate_LP
template_param
id|FEC_7_8
)paren
r_if
c_cond
(paren
id|p-&gt;code_rate_HP
op_eq
id|FEC_4_5
op_logical_or
id|p-&gt;code_rate_LP
op_eq
id|FEC_4_5
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;guard_interval
template_param
id|GUARD_INTERVAL_1_4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;transmission_mode
op_ne
id|TRANSMISSION_MODE_2K
op_logical_and
id|p-&gt;transmission_mode
op_ne
id|TRANSMISSION_MODE_8K
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;constellation
op_ne
id|QPSK
op_logical_and
id|p-&gt;constellation
op_ne
id|QAM_16
op_logical_and
id|p-&gt;constellation
op_ne
id|QAM_64
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;hierarchy_information
template_param
id|HIERARCHY_4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bandwidth
template_param
id|BANDWIDTH_6_MHZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bandwidth
op_eq
id|BANDWIDTH_7_MHZ
)paren
id|cx22700_writereg
(paren
id|state
comma
l_int|0x09
comma
id|cx22700_readreg
(paren
id|state
comma
l_int|0x09
op_or
l_int|0x10
)paren
)paren
suffix:semicolon
r_else
id|cx22700_writereg
(paren
id|state
comma
l_int|0x09
comma
id|cx22700_readreg
(paren
id|state
comma
l_int|0x09
op_amp
op_complement
l_int|0x10
)paren
)paren
suffix:semicolon
id|val
op_assign
id|qam_tab
(braket
id|p-&gt;constellation
op_minus
id|QPSK
)braket
suffix:semicolon
id|val
op_or_assign
id|p-&gt;hierarchy_information
op_minus
id|HIERARCHY_NONE
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x04
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
id|fec_tab
(braket
id|p-&gt;code_rate_HP
op_minus
id|FEC_1_2
)braket
op_lshift
l_int|3
suffix:semicolon
id|val
op_or_assign
id|fec_tab
(braket
id|p-&gt;code_rate_LP
op_minus
id|FEC_1_2
)braket
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x05
comma
id|val
)paren
suffix:semicolon
id|val
op_assign
(paren
id|p-&gt;guard_interval
op_minus
id|GUARD_INTERVAL_1_32
)paren
op_lshift
l_int|2
suffix:semicolon
id|val
op_or_assign
id|p-&gt;transmission_mode
op_minus
id|TRANSMISSION_MODE_2K
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x06
comma
id|val
)paren
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x08
comma
l_int|0x04
op_or
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* use user tps parameters */
id|cx22700_writereg
(paren
id|state
comma
l_int|0x08
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* restart aquisition */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_get_tps
r_static
r_int
id|cx22700_get_tps
(paren
r_struct
id|cx22700_state
op_star
id|state
comma
r_struct
id|dvb_ofdm_parameters
op_star
id|p
)paren
(brace
r_static
r_const
id|fe_modulation_t
id|qam_tab
(braket
l_int|3
)braket
op_assign
(brace
id|QPSK
comma
id|QAM_16
comma
id|QAM_64
)brace
suffix:semicolon
r_static
r_const
id|fe_code_rate_t
id|fec_tab
(braket
l_int|5
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
)brace
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|cx22700_readreg
c_func
(paren
id|state
comma
l_int|0x07
)paren
op_amp
l_int|0x20
)paren
)paren
multiline_comment|/*  tps valid? */
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|val
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
l_int|0x7
)paren
OG
l_int|4
)paren
id|p-&gt;hierarchy_information
op_assign
id|HIERARCHY_AUTO
suffix:semicolon
r_else
id|p-&gt;hierarchy_information
op_assign
id|HIERARCHY_NONE
op_plus
(paren
id|val
op_amp
l_int|0x7
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|val
op_rshift
l_int|3
)paren
op_amp
l_int|0x3
)paren
OG
l_int|2
)paren
id|p-&gt;constellation
op_assign
id|QAM_AUTO
suffix:semicolon
r_else
id|p-&gt;constellation
op_assign
id|qam_tab
(braket
(paren
id|val
op_rshift
l_int|3
)paren
op_amp
l_int|0x3
)braket
suffix:semicolon
id|val
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x02
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|val
op_rshift
l_int|3
)paren
op_amp
l_int|0x07
)paren
OG
l_int|4
)paren
id|p-&gt;code_rate_HP
op_assign
id|FEC_AUTO
suffix:semicolon
r_else
id|p-&gt;code_rate_HP
op_assign
id|fec_tab
(braket
(paren
id|val
op_rshift
l_int|3
)paren
op_amp
l_int|0x07
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
l_int|0x07
)paren
OG
l_int|4
)paren
id|p-&gt;code_rate_LP
op_assign
id|FEC_AUTO
suffix:semicolon
r_else
id|p-&gt;code_rate_LP
op_assign
id|fec_tab
(braket
id|val
op_amp
l_int|0x07
)braket
suffix:semicolon
id|val
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x03
)paren
suffix:semicolon
id|p-&gt;guard_interval
op_assign
id|GUARD_INTERVAL_1_32
op_plus
(paren
(paren
id|val
op_rshift
l_int|6
)paren
op_amp
l_int|0x3
)paren
suffix:semicolon
id|p-&gt;transmission_mode
op_assign
id|TRANSMISSION_MODE_2K
op_plus
(paren
(paren
id|val
op_rshift
l_int|5
)paren
op_amp
l_int|0x1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_init
r_static
r_int
id|cx22700_init
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;cx22700_init: init chip&bslash;n&quot;
)paren
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/*  soft reset */
id|cx22700_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x00
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
id|cx22700_writereg
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
id|cx22700_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;config-&gt;pll_init
)paren
(brace
id|cx22700_writereg
(paren
id|state
comma
l_int|0x0a
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* open i2c bus switch */
id|state-&gt;config
op_member_access_from_pointer
id|pll_init
c_func
(paren
id|fe
)paren
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x0a
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* close i2c bus switch */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_read_status
r_static
r_int
id|cx22700_read_status
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u16
id|rs_ber
op_assign
(paren
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0d
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0e
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|u8
id|sync
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x07
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
id|rs_ber
OL
l_int|0xff00
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
l_int|0x20
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
l_int|0x10
)paren
op_star
id|status
op_or_assign
id|FE_HAS_SYNC
suffix:semicolon
r_if
c_cond
(paren
op_star
id|status
op_eq
l_int|0x0f
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
DECL|function|cx22700_read_ber
r_static
r_int
id|cx22700_read_ber
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ber
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0c
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x0c
comma
l_int|0x00
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_read_signal_strength
r_static
r_int
id|cx22700_read_signal_strength
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u16
id|rs_ber
op_assign
(paren
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0d
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0e
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
op_star
id|signal_strength
op_assign
op_complement
id|rs_ber
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_read_snr
r_static
r_int
id|cx22700_read_snr
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u16
id|rs_ber
op_assign
(paren
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0d
)paren
op_lshift
l_int|9
)paren
op_or
(paren
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0e
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
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
DECL|function|cx22700_read_ucblocks
r_static
r_int
id|cx22700_read_ucblocks
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ucblocks
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x0f
)paren
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x0f
comma
l_int|0x00
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_set_frontend
r_static
r_int
id|cx22700_set_frontend
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* XXX CHECKME: soft reset*/
id|cx22700_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x00
)paren
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x0a
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* open i2c bus switch */
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
id|cx22700_writereg
(paren
id|state
comma
l_int|0x0a
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* close i2c bus switch */
id|cx22700_set_inversion
(paren
id|state
comma
id|p-&gt;inversion
)paren
suffix:semicolon
id|cx22700_set_tps
(paren
id|state
comma
op_amp
id|p-&gt;u.ofdm
)paren
suffix:semicolon
id|cx22700_writereg
(paren
id|state
comma
l_int|0x37
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* PAL loop filter off */
id|cx22700_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* restart acquire */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_get_frontend
r_static
r_int
id|cx22700_get_frontend
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
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|reg09
op_assign
id|cx22700_readreg
(paren
id|state
comma
l_int|0x09
)paren
suffix:semicolon
id|p-&gt;inversion
op_assign
id|reg09
op_amp
l_int|0x1
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
r_return
id|cx22700_get_tps
(paren
id|state
comma
op_amp
id|p-&gt;u.ofdm
)paren
suffix:semicolon
)brace
DECL|function|cx22700_get_tune_settings
r_static
r_int
id|cx22700_get_tune_settings
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
l_int|150
suffix:semicolon
id|fesettings-&gt;step_size
op_assign
l_int|166667
suffix:semicolon
id|fesettings-&gt;max_drift
op_assign
l_int|166667
op_star
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx22700_release
r_static
r_void
id|cx22700_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|cx22700_state
op_star
id|state
op_assign
(paren
r_struct
id|cx22700_state
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
DECL|variable|cx22700_ops
r_static
r_struct
id|dvb_frontend_ops
id|cx22700_ops
suffix:semicolon
DECL|function|cx22700_attach
r_struct
id|dvb_frontend
op_star
id|cx22700_attach
c_func
(paren
r_const
r_struct
id|cx22700_config
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
id|cx22700_state
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
id|cx22700_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cx22700_state
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
id|cx22700_ops
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
id|cx22700_readreg
c_func
(paren
id|state
comma
l_int|0x07
)paren
OL
l_int|0
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
DECL|variable|cx22700_ops
r_static
r_struct
id|dvb_frontend_ops
id|cx22700_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Conexant CX22700 DVB-T&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
comma
dot
id|frequency_min
op_assign
l_int|470000000
comma
dot
id|frequency_max
op_assign
l_int|860000000
comma
dot
id|frequency_stepsize
op_assign
l_int|166667
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
id|FE_CAN_RECOVER
)brace
comma
dot
id|release
op_assign
id|cx22700_release
comma
dot
id|init
op_assign
id|cx22700_init
comma
dot
id|set_frontend
op_assign
id|cx22700_set_frontend
comma
dot
id|get_frontend
op_assign
id|cx22700_get_frontend
comma
dot
id|get_tune_settings
op_assign
id|cx22700_get_tune_settings
comma
dot
id|read_status
op_assign
id|cx22700_read_status
comma
dot
id|read_ber
op_assign
id|cx22700_read_ber
comma
dot
id|read_signal_strength
op_assign
id|cx22700_read_signal_strength
comma
dot
id|read_snr
op_assign
id|cx22700_read_snr
comma
dot
id|read_ucblocks
op_assign
id|cx22700_read_ucblocks
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
l_string|&quot;Conexant CX22700 DVB-T Demodulator driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Holger Waechtler&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cx22700_attach
id|EXPORT_SYMBOL
c_func
(paren
id|cx22700_attach
)paren
suffix:semicolon
eof
