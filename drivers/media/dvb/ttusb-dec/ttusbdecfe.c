multiline_comment|/*&n; * TTUSB DEC Frontend Driver&n; *&n; * Copyright (C) 2003-2004 Alex Woods &lt;linux-dvb@giblets.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;ttusbdecfe.h&quot;
DECL|macro|LOF_HI
mdefine_line|#define LOF_HI&t;&t;&t;10600000
DECL|macro|LOF_LO
mdefine_line|#define LOF_LO&t;&t;&t;9750000
DECL|struct|ttusbdecfe_state
r_struct
id|ttusbdecfe_state
(brace
DECL|member|ops
r_struct
id|dvb_frontend_ops
id|ops
suffix:semicolon
multiline_comment|/* configuration settings */
DECL|member|config
r_const
r_struct
id|ttusbdecfe_config
op_star
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
DECL|member|hi_band
id|u8
id|hi_band
suffix:semicolon
DECL|member|voltage
id|u8
id|voltage
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ttusbdecfe_read_status
r_static
r_int
id|ttusbdecfe_read_status
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
id|FE_HAS_VITERBI
op_or
id|FE_HAS_SYNC
op_or
id|FE_HAS_CARRIER
op_or
id|FE_HAS_LOCK
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttusbdecfe_dvbt_set_frontend
r_static
r_int
id|ttusbdecfe_dvbt_set_frontend
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
id|ttusbdecfe_state
op_star
id|state
op_assign
(paren
r_struct
id|ttusbdecfe_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|b
(braket
)braket
op_assign
(brace
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
l_int|0xff
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xff
)brace
suffix:semicolon
id|u32
id|freq
op_assign
id|htonl
c_func
(paren
id|p-&gt;frequency
op_div
l_int|1000
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|4
)braket
comma
op_amp
id|freq
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|send_command
c_func
(paren
id|fe
comma
l_int|0x71
comma
r_sizeof
(paren
id|b
)paren
comma
id|b
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttusbdecfe_dvbs_set_frontend
r_static
r_int
id|ttusbdecfe_dvbs_set_frontend
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
id|ttusbdecfe_state
op_star
id|state
op_assign
(paren
r_struct
id|ttusbdecfe_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|b
(braket
)braket
op_assign
(brace
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
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
id|u32
id|freq
suffix:semicolon
id|u32
id|sym_rate
suffix:semicolon
id|u32
id|band
suffix:semicolon
id|u32
id|lnb_voltage
suffix:semicolon
id|freq
op_assign
id|htonl
c_func
(paren
id|p-&gt;frequency
op_plus
(paren
id|state-&gt;hi_band
ques
c_cond
id|LOF_HI
suffix:colon
id|LOF_LO
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|4
)braket
comma
op_amp
id|freq
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|sym_rate
op_assign
id|htonl
c_func
(paren
id|p-&gt;u.qam.symbol_rate
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|12
)braket
comma
op_amp
id|sym_rate
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|band
op_assign
id|htonl
c_func
(paren
id|state-&gt;hi_band
ques
c_cond
id|LOF_HI
suffix:colon
id|LOF_LO
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|24
)braket
comma
op_amp
id|band
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|lnb_voltage
op_assign
id|htonl
c_func
(paren
id|state-&gt;voltage
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|28
)braket
comma
op_amp
id|lnb_voltage
comma
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|send_command
c_func
(paren
id|fe
comma
l_int|0x71
comma
r_sizeof
(paren
id|b
)paren
comma
id|b
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttusbdecfe_dvbs_diseqc_send_master_cmd
r_static
r_int
id|ttusbdecfe_dvbs_diseqc_send_master_cmd
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_diseqc_master_cmd
op_star
id|cmd
)paren
(brace
r_struct
id|ttusbdecfe_state
op_star
id|state
op_assign
(paren
r_struct
id|ttusbdecfe_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|b
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0xff
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
)brace
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|b
(braket
l_int|4
)braket
comma
id|cmd-&gt;msg
comma
id|cmd-&gt;msg_len
)paren
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|send_command
c_func
(paren
id|fe
comma
l_int|0x72
comma
r_sizeof
(paren
id|b
)paren
op_minus
(paren
l_int|6
op_minus
id|cmd-&gt;msg_len
)paren
comma
id|b
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttusbdecfe_dvbs_set_tone
r_static
r_int
id|ttusbdecfe_dvbs_set_tone
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
r_struct
id|ttusbdecfe_state
op_star
id|state
op_assign
(paren
r_struct
id|ttusbdecfe_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|state-&gt;hi_band
op_assign
(paren
id|SEC_TONE_ON
op_eq
id|tone
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ttusbdecfe_dvbs_set_voltage
r_static
r_int
id|ttusbdecfe_dvbs_set_voltage
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
r_struct
id|ttusbdecfe_state
op_star
id|state
op_assign
(paren
r_struct
id|ttusbdecfe_state
op_star
)paren
id|fe-&gt;demodulator_priv
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
id|state-&gt;voltage
op_assign
l_int|13
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEC_VOLTAGE_18
suffix:colon
id|state-&gt;voltage
op_assign
l_int|18
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
DECL|function|ttusbdecfe_release
r_static
r_void
id|ttusbdecfe_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ttusbdecfe_state
op_star
id|state
op_assign
(paren
r_struct
id|ttusbdecfe_state
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
DECL|variable|ttusbdecfe_dvbt_ops
r_static
r_struct
id|dvb_frontend_ops
id|ttusbdecfe_dvbt_ops
suffix:semicolon
DECL|function|ttusbdecfe_dvbt_attach
r_struct
id|dvb_frontend
op_star
id|ttusbdecfe_dvbt_attach
c_func
(paren
r_const
r_struct
id|ttusbdecfe_config
op_star
id|config
)paren
(brace
r_struct
id|ttusbdecfe_state
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
id|ttusbdecfe_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ttusbdecfe_state
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
id|memcpy
c_func
(paren
op_amp
id|state-&gt;ops
comma
op_amp
id|ttusbdecfe_dvbt_ops
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
DECL|variable|ttusbdecfe_dvbs_ops
r_static
r_struct
id|dvb_frontend_ops
id|ttusbdecfe_dvbs_ops
suffix:semicolon
DECL|function|ttusbdecfe_dvbs_attach
r_struct
id|dvb_frontend
op_star
id|ttusbdecfe_dvbs_attach
c_func
(paren
r_const
r_struct
id|ttusbdecfe_config
op_star
id|config
)paren
(brace
r_struct
id|ttusbdecfe_state
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
id|ttusbdecfe_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ttusbdecfe_state
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
id|state-&gt;voltage
op_assign
l_int|0
suffix:semicolon
id|state-&gt;hi_band
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|state-&gt;ops
comma
op_amp
id|ttusbdecfe_dvbs_ops
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
DECL|variable|ttusbdecfe_dvbt_ops
r_static
r_struct
id|dvb_frontend_ops
id|ttusbdecfe_dvbt_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;TechnoTrend/Hauppauge DEC2000-t Frontend&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
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
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_7_8
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
id|ttusbdecfe_release
comma
dot
id|set_frontend
op_assign
id|ttusbdecfe_dvbt_set_frontend
comma
dot
id|read_status
op_assign
id|ttusbdecfe_read_status
comma
)brace
suffix:semicolon
DECL|variable|ttusbdecfe_dvbs_ops
r_static
r_struct
id|dvb_frontend_ops
id|ttusbdecfe_dvbs_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;TechnoTrend/Hauppauge DEC3000-s Frontend&quot;
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
l_int|125
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
id|ttusbdecfe_release
comma
dot
id|set_frontend
op_assign
id|ttusbdecfe_dvbs_set_frontend
comma
dot
id|read_status
op_assign
id|ttusbdecfe_read_status
comma
dot
id|diseqc_send_master_cmd
op_assign
id|ttusbdecfe_dvbs_diseqc_send_master_cmd
comma
dot
id|set_voltage
op_assign
id|ttusbdecfe_dvbs_set_voltage
comma
dot
id|set_tone
op_assign
id|ttusbdecfe_dvbs_set_tone
comma
)brace
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;TTUSB DEC DVB-T/S Demodulator driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alex Woods/Andrew de Quincey&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ttusbdecfe_dvbt_attach
id|EXPORT_SYMBOL
c_func
(paren
id|ttusbdecfe_dvbt_attach
)paren
suffix:semicolon
DECL|variable|ttusbdecfe_dvbs_attach
id|EXPORT_SYMBOL
c_func
(paren
id|ttusbdecfe_dvbs_attach
)paren
suffix:semicolon
eof
