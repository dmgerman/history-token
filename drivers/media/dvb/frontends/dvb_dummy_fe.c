multiline_comment|/*&n; *  Driver for Dummy Frontend&n; *&n; *  Written by Emard &lt;emard@softhome.net&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.=&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_dummy_fe.h&quot;
DECL|struct|dvb_dummy_fe_state
r_struct
id|dvb_dummy_fe_state
(brace
DECL|member|ops
r_struct
id|dvb_frontend_ops
id|ops
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dvb_dummy_fe_read_status
r_static
r_int
id|dvb_dummy_fe_read_status
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
op_star
id|status
op_assign
id|FE_HAS_SIGNAL
op_or
id|FE_HAS_CARRIER
op_or
id|FE_HAS_VITERBI
op_or
id|FE_HAS_SYNC
op_or
id|FE_HAS_LOCK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_read_ber
r_static
r_int
id|dvb_dummy_fe_read_ber
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
op_star
id|ber
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_read_signal_strength
r_static
r_int
id|dvb_dummy_fe_read_signal_strength
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
op_star
id|strength
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_read_snr
r_static
r_int
id|dvb_dummy_fe_read_snr
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
op_star
id|snr
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_read_ucblocks
r_static
r_int
id|dvb_dummy_fe_read_ucblocks
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
op_star
id|ucblocks
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_get_frontend
r_static
r_int
id|dvb_dummy_fe_get_frontend
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_set_frontend
r_static
r_int
id|dvb_dummy_fe_set_frontend
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_sleep
r_static
r_int
id|dvb_dummy_fe_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_init
r_static
r_int
id|dvb_dummy_fe_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_set_tone
r_static
r_int
id|dvb_dummy_fe_set_tone
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_sec_tone_mode_t
id|tone
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_set_voltage
r_static
r_int
id|dvb_dummy_fe_set_voltage
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_sec_voltage_t
id|voltage
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dvb_dummy_fe_release
r_static
r_void
id|dvb_dummy_fe_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|dvb_dummy_fe_state
op_star
id|state
op_assign
(paren
r_struct
id|dvb_dummy_fe_state
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
DECL|variable|dvb_dummy_fe_ofdm_ops
r_static
r_struct
id|dvb_frontend_ops
id|dvb_dummy_fe_ofdm_ops
suffix:semicolon
DECL|function|dvb_dummy_fe_ofdm_attach
r_struct
id|dvb_frontend
op_star
id|dvb_dummy_fe_ofdm_attach
c_func
(paren
r_void
)paren
(brace
r_struct
id|dvb_dummy_fe_state
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
id|dvb_dummy_fe_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_dummy_fe_state
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
id|dvb_dummy_fe_ofdm_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
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
DECL|variable|dvb_dummy_fe_qpsk_ops
r_static
r_struct
id|dvb_frontend_ops
id|dvb_dummy_fe_qpsk_ops
suffix:semicolon
DECL|function|dvb_dummy_fe_qpsk_attach
r_struct
id|dvb_frontend
op_star
id|dvb_dummy_fe_qpsk_attach
c_func
(paren
)paren
(brace
r_struct
id|dvb_dummy_fe_state
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
id|dvb_dummy_fe_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_dummy_fe_state
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
id|dvb_dummy_fe_qpsk_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
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
DECL|variable|dvb_dummy_fe_qam_ops
r_static
r_struct
id|dvb_frontend_ops
id|dvb_dummy_fe_qam_ops
suffix:semicolon
DECL|function|dvb_dummy_fe_qam_attach
r_struct
id|dvb_frontend
op_star
id|dvb_dummy_fe_qam_attach
c_func
(paren
)paren
(brace
r_struct
id|dvb_dummy_fe_state
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
id|dvb_dummy_fe_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dvb_dummy_fe_state
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
id|dvb_dummy_fe_qam_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
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
DECL|variable|dvb_dummy_fe_ofdm_ops
r_static
r_struct
id|dvb_frontend_ops
id|dvb_dummy_fe_ofdm_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Dummy DVB-T&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
comma
dot
id|frequency_min
op_assign
l_int|0
comma
dot
id|frequency_max
op_assign
l_int|863250000
comma
dot
id|frequency_stepsize
op_assign
l_int|62500
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
id|FE_CAN_FEC_4_5
op_or
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_6_7
op_or
id|FE_CAN_FEC_7_8
op_or
id|FE_CAN_FEC_8_9
op_or
id|FE_CAN_FEC_AUTO
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
comma
)brace
comma
dot
id|release
op_assign
id|dvb_dummy_fe_release
comma
dot
id|init
op_assign
id|dvb_dummy_fe_init
comma
dot
id|sleep
op_assign
id|dvb_dummy_fe_sleep
comma
dot
id|set_frontend
op_assign
id|dvb_dummy_fe_set_frontend
comma
dot
id|get_frontend
op_assign
id|dvb_dummy_fe_get_frontend
comma
dot
id|read_status
op_assign
id|dvb_dummy_fe_read_status
comma
dot
id|read_ber
op_assign
id|dvb_dummy_fe_read_ber
comma
dot
id|read_signal_strength
op_assign
id|dvb_dummy_fe_read_signal_strength
comma
dot
id|read_snr
op_assign
id|dvb_dummy_fe_read_snr
comma
dot
id|read_ucblocks
op_assign
id|dvb_dummy_fe_read_ucblocks
comma
)brace
suffix:semicolon
DECL|variable|dvb_dummy_fe_qam_ops
r_static
r_struct
id|dvb_frontend_ops
id|dvb_dummy_fe_qam_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Dummy DVB-C&quot;
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
l_int|57840000
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
l_int|57840000
op_div
l_int|2
)paren
op_div
l_int|4
comma
multiline_comment|/* SACLK/4 */
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
)brace
comma
dot
id|release
op_assign
id|dvb_dummy_fe_release
comma
dot
id|init
op_assign
id|dvb_dummy_fe_init
comma
dot
id|sleep
op_assign
id|dvb_dummy_fe_sleep
comma
dot
id|set_frontend
op_assign
id|dvb_dummy_fe_set_frontend
comma
dot
id|get_frontend
op_assign
id|dvb_dummy_fe_get_frontend
comma
dot
id|read_status
op_assign
id|dvb_dummy_fe_read_status
comma
dot
id|read_ber
op_assign
id|dvb_dummy_fe_read_ber
comma
dot
id|read_signal_strength
op_assign
id|dvb_dummy_fe_read_signal_strength
comma
dot
id|read_snr
op_assign
id|dvb_dummy_fe_read_snr
comma
dot
id|read_ucblocks
op_assign
id|dvb_dummy_fe_read_ucblocks
comma
)brace
suffix:semicolon
DECL|variable|dvb_dummy_fe_qpsk_ops
r_static
r_struct
id|dvb_frontend_ops
id|dvb_dummy_fe_qpsk_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Dummy DVB-S&quot;
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
comma
dot
id|release
op_assign
id|dvb_dummy_fe_release
comma
dot
id|init
op_assign
id|dvb_dummy_fe_init
comma
dot
id|sleep
op_assign
id|dvb_dummy_fe_sleep
comma
dot
id|set_frontend
op_assign
id|dvb_dummy_fe_set_frontend
comma
dot
id|get_frontend
op_assign
id|dvb_dummy_fe_get_frontend
comma
dot
id|read_status
op_assign
id|dvb_dummy_fe_read_status
comma
dot
id|read_ber
op_assign
id|dvb_dummy_fe_read_ber
comma
dot
id|read_signal_strength
op_assign
id|dvb_dummy_fe_read_signal_strength
comma
dot
id|read_snr
op_assign
id|dvb_dummy_fe_read_snr
comma
dot
id|read_ucblocks
op_assign
id|dvb_dummy_fe_read_ucblocks
comma
dot
id|set_voltage
op_assign
id|dvb_dummy_fe_set_voltage
comma
dot
id|set_tone
op_assign
id|dvb_dummy_fe_set_tone
comma
)brace
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;DVB DUMMY Frontend&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Emard&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|dvb_dummy_fe_ofdm_attach
id|EXPORT_SYMBOL
c_func
(paren
id|dvb_dummy_fe_ofdm_attach
)paren
suffix:semicolon
DECL|variable|dvb_dummy_fe_qam_attach
id|EXPORT_SYMBOL
c_func
(paren
id|dvb_dummy_fe_qam_attach
)paren
suffix:semicolon
DECL|variable|dvb_dummy_fe_qpsk_attach
id|EXPORT_SYMBOL
c_func
(paren
id|dvb_dummy_fe_qpsk_attach
)paren
suffix:semicolon
eof
