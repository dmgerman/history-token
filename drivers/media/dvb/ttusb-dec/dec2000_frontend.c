multiline_comment|/*&n; * TTUSB DEC-2000-t Frontend&n; *&n; * Copyright (C) 2003 Alex Woods &lt;linux-dvb@giblets.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk&t;if (debug) printk
DECL|variable|dec2000_frontend_info
r_static
r_struct
id|dvb_frontend_info
id|dec2000_frontend_info
op_assign
(brace
id|name
suffix:colon
l_string|&quot;TechnoTrend/Hauppauge DEC-2000-t Frontend&quot;
comma
id|type
suffix:colon
id|FE_OFDM
comma
id|frequency_min
suffix:colon
l_int|51000000
comma
id|frequency_max
suffix:colon
l_int|858000000
comma
id|frequency_stepsize
suffix:colon
l_int|62500
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
DECL|function|dec2000_frontend_ioctl
r_static
r_int
id|dec2000_frontend_ioctl
c_func
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
id|dprintk
c_func
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
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_GET_INFO&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|arg
comma
op_amp
id|dec2000_frontend_info
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
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_READ_STATUS&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
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
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_READ_BER&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
op_star
id|ber
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_READ_SIGNAL_STRENGTH&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
op_star
(paren
id|s32
op_star
)paren
id|arg
op_assign
l_int|0xFF
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SNR
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_READ_SNR&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
op_star
(paren
id|s32
op_star
)paren
id|arg
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_READ_UNCORRECTED_BLOCKS
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_READ_UNCORRECTED_BLOCKS&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|arg
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SET_FRONTEND
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
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
id|addr
suffix:colon
l_int|0x71
comma
id|flags
suffix:colon
l_int|0
comma
id|len
suffix:colon
l_int|20
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_SET_FRONTEND&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;            frequency-&gt;%d&bslash;n&quot;
comma
id|p-&gt;frequency
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;            symbol_rate-&gt;%d&bslash;n&quot;
comma
id|p-&gt;u.qam.symbol_rate
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;            inversion-&gt;%d&bslash;n&quot;
comma
id|p-&gt;inversion
)paren
suffix:semicolon
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
r_int
)paren
)paren
suffix:semicolon
id|msg.buf
op_assign
id|b
suffix:semicolon
id|fe-&gt;i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|fe-&gt;i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_GET_FRONTEND
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_GET_FRONTEND&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SLEEP
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_SLEEP&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_INIT&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: FE_RESET&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;%s: unknown IOCTL (0x%X)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dec2000_frontend_attach
r_static
r_int
id|dec2000_frontend_attach
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dvb_register_frontend
c_func
(paren
id|dec2000_frontend_ioctl
comma
id|i2c
comma
l_int|NULL
comma
op_amp
id|dec2000_frontend_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dec2000_frontend_detach
r_static
r_void
id|dec2000_frontend_detach
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dvb_unregister_frontend
c_func
(paren
id|dec2000_frontend_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
DECL|function|dec2000_frontend_init
r_static
r_int
id|__init
id|dec2000_frontend_init
c_func
(paren
r_void
)paren
(brace
r_return
id|dvb_register_i2c_device
c_func
(paren
id|THIS_MODULE
comma
id|dec2000_frontend_attach
comma
id|dec2000_frontend_detach
)paren
suffix:semicolon
)brace
DECL|function|dec2000_frontend_exit
r_static
r_void
id|__exit
id|dec2000_frontend_exit
c_func
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
c_func
(paren
id|dec2000_frontend_attach
)paren
suffix:semicolon
)brace
DECL|variable|dec2000_frontend_init
id|module_init
c_func
(paren
id|dec2000_frontend_init
)paren
suffix:semicolon
DECL|variable|dec2000_frontend_exit
id|module_exit
c_func
(paren
id|dec2000_frontend_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;TechnoTrend/Hauppauge DEC-2000-t Frontend&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alex Woods &lt;linux-dvb@giblets.org&quot;
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
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debug level&quot;
)paren
suffix:semicolon
eof
