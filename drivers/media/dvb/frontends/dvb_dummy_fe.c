multiline_comment|/* &n; *  Driver for Dummy Frontend &n; *&n; *  Written by Emard &lt;emard@softhome.net&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.=&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
DECL|variable|sct
r_static
r_int
id|sct
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* depending on module parameter sct deliver different infos&n; */
r_static
DECL|variable|dvb_s_dummyfe_info
r_struct
id|dvb_frontend_info
id|dvb_s_dummyfe_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;DVB-S dummy frontend&quot;
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
multiline_comment|/*      .symbol_rate_tolerance &t;= ???,*/
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
r_static
DECL|variable|dvb_c_dummyfe_info
r_struct
id|dvb_frontend_info
id|dvb_c_dummyfe_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;DVB-C dummy frontend&quot;
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
macro_line|#if 0
dot
id|frequency_tolerance
op_assign
ques
c_cond
ques
c_cond
ques
c_cond
comma
dot
id|symbol_rate_tolerance
op_assign
ques
c_cond
ques
c_cond
ques
c_cond
comma
multiline_comment|/* ppm */
multiline_comment|/* == 8% (spec p. 5) */
dot
id|notifier_delay
op_assign
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
)brace
suffix:semicolon
DECL|variable|dvb_t_dummyfe_info
r_static
r_struct
id|dvb_frontend_info
id|dvb_t_dummyfe_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;DVB-T dummy frontend&quot;
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
multiline_comment|/*.frequency_tolerance = */
multiline_comment|/* FIXME: 12% of SR */
dot
id|symbol_rate_min
op_assign
l_int|0
comma
multiline_comment|/* FIXME */
dot
id|symbol_rate_max
op_assign
l_int|9360000
comma
multiline_comment|/* FIXME */
dot
id|symbol_rate_tolerance
op_assign
l_int|4000
comma
dot
id|notifier_delay
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
suffix:semicolon
DECL|function|frontend_info
r_struct
id|dvb_frontend_info
op_star
id|frontend_info
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|sct
)paren
(brace
r_case
l_int|2
suffix:colon
r_return
op_amp
id|dvb_t_dummyfe_info
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
op_amp
id|dvb_c_dummyfe_info
suffix:semicolon
r_case
l_int|0
suffix:colon
r_default
suffix:colon
r_return
op_amp
id|dvb_s_dummyfe_info
suffix:semicolon
)brace
)brace
r_static
DECL|function|dvbdummyfe_ioctl
r_int
id|dvbdummyfe_ioctl
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
id|frontend_info
c_func
(paren
)paren
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
l_int|0
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
l_int|0xff
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
l_int|0xf0
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
op_star
(paren
id|u32
op_star
)paren
id|arg
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SET_FRONTEND
suffix:colon
r_break
suffix:semicolon
r_case
id|FE_GET_FRONTEND
suffix:colon
r_break
suffix:semicolon
r_case
id|FE_SLEEP
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|FE_SET_TONE
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|FE_SET_VOLTAGE
suffix:colon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|dvbdummyfe_attach
r_int
id|dvbdummyfe_attach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dvb_register_frontend
(paren
id|dvbdummyfe_ioctl
comma
id|i2c
comma
l_int|NULL
comma
id|frontend_info
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|dvbdummyfe_detach
r_void
id|dvbdummyfe_detach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dvb_unregister_frontend
(paren
id|dvbdummyfe_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
r_static
DECL|function|init_dvbdummyfe
r_int
id|__init
id|init_dvbdummyfe
(paren
r_void
)paren
(brace
r_return
id|dvb_register_i2c_device
(paren
id|THIS_MODULE
comma
id|dvbdummyfe_attach
comma
id|dvbdummyfe_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|exit_dvbdummyfe
r_void
id|__exit
id|exit_dvbdummyfe
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
(paren
id|dvbdummyfe_attach
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|init_dvbdummyfe
id|module_init
c_func
(paren
id|init_dvbdummyfe
)paren
suffix:semicolon
DECL|variable|exit_dvbdummyfe
id|module_exit
c_func
(paren
id|exit_dvbdummyfe
)paren
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
id|MODULE_PARM
c_func
(paren
id|sct
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
eof
