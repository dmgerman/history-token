multiline_comment|/* &n;    Driver for Grundig 29504-491, a Philips TDA8083 based QPSK Frontend&n;&n;    Copyright (C) 2001 Convergence Integrated Media GmbH&n;&n;    written by Ralph Metzler &lt;ralph@convergence.de&gt;&n;&n;    adoption to the new DVB frontend API and diagnostic ioctl&squot;s&n;    by Holger Waechtler &lt;holger@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
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
r_static
DECL|variable|grundig_29504_491_info
r_struct
id|dvb_frontend_info
id|grundig_29504_491_info
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Grundig 29504-491, (TDA8083 based)&quot;
comma
id|type
suffix:colon
id|FE_QPSK
comma
id|frequency_min
suffix:colon
l_int|950000
comma
multiline_comment|/* FIXME: guessed! */
id|frequency_max
suffix:colon
l_int|1400000
comma
multiline_comment|/* FIXME: guessed! */
id|frequency_stepsize
suffix:colon
l_int|125
comma
multiline_comment|/* kHz for QPSK frontends */
multiline_comment|/*      frequency_tolerance: ???,*/
id|symbol_rate_min
suffix:colon
l_int|1000000
comma
multiline_comment|/* FIXME: guessed! */
id|symbol_rate_max
suffix:colon
l_int|45000000
comma
multiline_comment|/* FIXME: guessed! */
multiline_comment|/*      symbol_rate_tolerance: ???,*/
id|notifier_delay
suffix:colon
l_int|0
comma
id|caps
suffix:colon
id|FE_CAN_INVERSION_AUTO
op_or
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
id|FE_CAN_QPSK
op_or
id|FE_CAN_MUTE_TS
)brace
suffix:semicolon
r_static
DECL|variable|tda8083_init_tab
id|u8
id|tda8083_init_tab
(braket
)braket
op_assign
(brace
l_int|0x04
comma
l_int|0x00
comma
l_int|0x4a
comma
l_int|0x79
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0xff
comma
l_int|0xea
comma
l_int|0x48
comma
l_int|0x42
comma
l_int|0x79
comma
l_int|0x60
comma
l_int|0x70
comma
l_int|0x52
comma
l_int|0x9a
comma
l_int|0x10
comma
l_int|0x0e
comma
l_int|0x10
comma
l_int|0xf2
comma
l_int|0xa7
comma
l_int|0x93
comma
l_int|0x0b
comma
l_int|0x05
comma
l_int|0xc8
comma
l_int|0x9d
comma
l_int|0x00
comma
l_int|0x42
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x60
comma
l_int|0x40
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x75
comma
l_int|0x00
comma
l_int|0xe0
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
r_static
DECL|function|tda8083_writereg
r_int
id|tda8083_writereg
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
(paren
l_string|&quot;%s: writereg error (reg %02x, ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reg
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
DECL|function|tda8083_readregs
r_int
id|tda8083_readregs
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
(paren
l_string|&quot;%s: readreg error (reg %02x, ret == %i)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|reg1
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
r_inline
DECL|function|tda8083_readreg
id|u8
id|tda8083_readreg
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
id|u8
id|val
suffix:semicolon
id|tda8083_readregs
(paren
id|i2c
comma
id|reg
comma
op_amp
id|val
comma
l_int|1
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
DECL|function|tsa5522_write
r_int
id|tsa5522_write
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
multiline_comment|/**&n; *   set up the downconverter frequency divisor for a&n; *   reference clock comparision frequency of 125 kHz.&n; */
r_static
DECL|function|tsa5522_set_tv_freq
r_int
id|tsa5522_set_tv_freq
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|freq
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
l_int|0x8e
comma
l_int|0x00
)brace
suffix:semicolon
r_return
id|tsa5522_write
(paren
id|i2c
comma
id|buf
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tda8083_init
id|tda8083_init
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
l_string|&quot;%s: init TDA8083&bslash;n&quot;
comma
id|__FILE__
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
l_int|44
suffix:semicolon
id|i
op_increment
)paren
id|tda8083_writereg
(paren
id|i2c
comma
id|i
comma
id|tda8083_init_tab
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|tda8083_set_inversion
id|tda8083_set_inversion
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_spectral_inversion_t
id|inversion
)paren
(brace
multiline_comment|/*  XXX FIXME: implement other modes than FEC_AUTO */
r_if
c_cond
(paren
id|inversion
op_eq
id|INVERSION_AUTO
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|tda8083_set_fec
id|tda8083_set_fec
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
r_if
c_cond
(paren
id|fec
op_eq
id|FEC_AUTO
)paren
r_return
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x07
comma
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fec
op_ge
id|FEC_1_2
op_logical_and
id|fec
op_le
id|FEC_8_9
)paren
r_return
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x07
comma
l_int|1
op_lshift
(paren
id|FEC_8_9
op_minus
id|fec
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
DECL|function|tda8083_get_fec
id|fe_code_rate_t
id|tda8083_get_fec
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|u8
id|index
suffix:semicolon
r_static
id|fe_code_rate_t
id|fec_tab
(braket
)braket
op_assign
(brace
id|FEC_8_9
comma
id|FEC_1_2
comma
id|FEC_2_3
comma
id|FEC_3_4
comma
id|FEC_4_5
comma
id|FEC_5_6
comma
id|FEC_6_7
comma
id|FEC_7_8
)brace
suffix:semicolon
id|index
op_assign
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x0e
)paren
op_amp
l_int|0x3
suffix:semicolon
r_if
c_cond
(paren
id|index
OG
l_int|7
)paren
r_return
id|FEC_NONE
suffix:semicolon
r_return
id|fec_tab
(braket
id|index
)braket
suffix:semicolon
)brace
r_static
DECL|function|tda8083_set_symbolrate
r_int
id|tda8083_set_symbolrate
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
id|filter
suffix:semicolon
r_if
c_cond
(paren
id|srate
OG
l_int|32000000
)paren
id|srate
op_assign
l_int|32000000
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
id|filter
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|srate
OL
l_int|24000000
)paren
id|filter
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|srate
OL
l_int|16000000
)paren
id|filter
op_assign
l_int|3
suffix:semicolon
id|tmp
op_assign
l_int|31250
op_lshift
l_int|16
suffix:semicolon
id|ratio
op_assign
id|tmp
op_div
id|srate
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|srate
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
id|srate
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|srate
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
id|srate
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tda8083: ratio == %08x&bslash;n&quot;
comma
id|ratio
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x05
comma
id|filter
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x02
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
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x03
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
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x04
comma
(paren
id|ratio
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
DECL|function|tda8083_wait_diseqc_fifo
r_void
id|tda8083_wait_diseqc_fifo
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
r_while
c_loop
(paren
id|jiffies
op_minus
id|start
OL
id|timeout
op_logical_and
op_logical_neg
(paren
id|tda8083_readreg
c_func
(paren
id|i2c
comma
l_int|0x02
)paren
op_amp
l_int|0x80
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
(paren
l_int|5
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
r_static
DECL|function|tda8083_send_diseqc_msg
r_int
id|tda8083_send_diseqc_msg
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
r_int
id|i
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x29
comma
(paren
id|m-&gt;msg_len
op_minus
l_int|3
)paren
op_or
(paren
l_int|1
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/* enable */
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
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x23
op_plus
id|i
comma
id|m-&gt;msg
(braket
id|i
)braket
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x29
comma
(paren
id|m-&gt;msg_len
op_minus
l_int|3
)paren
op_or
(paren
l_int|3
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/* send!! */
id|tda8083_wait_diseqc_fifo
(paren
id|i2c
comma
l_int|100
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|tda8083_send_diseqc_burst
r_int
id|tda8083_send_diseqc_burst
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
r_switch
c_cond
(paren
id|burst
)paren
(brace
r_case
id|SEC_MINI_A
suffix:colon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x29
comma
(paren
l_int|5
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/* send burst A */
r_break
suffix:semicolon
r_case
id|SEC_MINI_B
suffix:colon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x29
comma
(paren
l_int|7
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
multiline_comment|/* send B */
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
id|tda8083_wait_diseqc_fifo
(paren
id|i2c
comma
l_int|100
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|tda8083_set_tone
r_int
id|tda8083_set_tone
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
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x26
comma
l_int|0xf1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tone
)paren
(brace
r_case
id|SEC_TONE_OFF
suffix:colon
r_return
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x29
comma
l_int|0x00
)paren
suffix:semicolon
r_case
id|SEC_TONE_ON
suffix:colon
r_return
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x29
comma
l_int|0x80
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
DECL|function|tda8083_set_voltage
r_int
id|tda8083_set_voltage
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
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x20
comma
l_int|0x00
)paren
suffix:semicolon
r_case
id|SEC_VOLTAGE_18
suffix:colon
r_return
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x20
comma
l_int|0x11
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
DECL|function|grundig_29504_491_ioctl
r_int
id|grundig_29504_491_ioctl
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
id|grundig_29504_491_info
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
op_complement
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x01
)paren
suffix:semicolon
id|u8
id|sync
op_assign
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x02
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
l_int|0x01
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
l_int|0x02
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
(paren
id|sync
op_amp
l_int|0x1f
)paren
op_eq
l_int|0x1f
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
l_int|0
suffix:semicolon
multiline_comment|/*   XXX FIXME: implement me!!! */
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
(brace
id|u8
id|signal
op_assign
op_complement
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x01
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
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x08
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
(paren
id|u32
op_star
)paren
id|arg
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*   XXX FIXME: implement me!!! */
r_return
op_minus
id|EOPNOTSUPP
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
id|arg
suffix:semicolon
id|tsa5522_set_tv_freq
(paren
id|i2c
comma
id|p-&gt;frequency
)paren
suffix:semicolon
id|tda8083_set_inversion
(paren
id|i2c
comma
id|p-&gt;inversion
)paren
suffix:semicolon
id|tda8083_set_fec
(paren
id|i2c
comma
id|p-&gt;u.qpsk.fec_inner
)paren
suffix:semicolon
id|tda8083_set_symbolrate
(paren
id|i2c
comma
id|p-&gt;u.qpsk.symbol_rate
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
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
multiline_comment|/*  FIXME: get symbolrate &amp; frequency offset...*/
multiline_comment|/*p-&gt;frequency = ???;*/
id|p-&gt;inversion
op_assign
(paren
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x0e
)paren
op_amp
l_int|0x80
)paren
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
id|p-&gt;u.qpsk.fec_inner
op_assign
id|tda8083_get_fec
(paren
id|i2c
)paren
suffix:semicolon
multiline_comment|/*p-&gt;u.qpsk.symbol_rate = tda8083_get_symbolrate (i2c);*/
r_break
suffix:semicolon
)brace
r_case
id|FE_SLEEP
suffix:colon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x02
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
id|tda8083_init
(paren
id|i2c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_DISEQC_SEND_MASTER_CMD
suffix:colon
r_return
id|tda8083_send_diseqc_msg
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_DISEQC_SEND_BURST
suffix:colon
id|tda8083_send_diseqc_burst
(paren
id|i2c
comma
(paren
id|fe_sec_mini_cmd_t
)paren
id|arg
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SET_TONE
suffix:colon
id|tda8083_set_tone
(paren
id|i2c
comma
(paren
id|fe_sec_tone_mode_t
)paren
id|arg
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SET_VOLTAGE
suffix:colon
id|tda8083_set_voltage
(paren
id|i2c
comma
(paren
id|fe_sec_voltage_t
)paren
id|arg
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x3c
)paren
suffix:semicolon
id|tda8083_writereg
(paren
id|i2c
comma
l_int|0x00
comma
l_int|0x04
)paren
suffix:semicolon
r_break
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
DECL|function|tda8083_attach
r_int
id|tda8083_attach
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
id|tda8083_readreg
(paren
id|i2c
comma
l_int|0x00
)paren
)paren
op_ne
l_int|0x05
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dvb_register_frontend
(paren
id|grundig_29504_491_ioctl
comma
id|i2c
comma
l_int|NULL
comma
op_amp
id|grundig_29504_491_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|tda8083_detach
r_void
id|tda8083_detach
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dvb_unregister_frontend
(paren
id|grundig_29504_491_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
r_static
DECL|function|init_tda8083
r_int
id|__init
id|init_tda8083
(paren
r_void
)paren
(brace
r_return
id|dvb_register_i2c_device
(paren
id|THIS_MODULE
comma
id|tda8083_attach
comma
id|tda8083_detach
)paren
suffix:semicolon
)brace
r_static
DECL|function|exit_tda8083
r_void
id|__exit
id|exit_tda8083
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
(paren
id|tda8083_attach
)paren
suffix:semicolon
)brace
DECL|variable|init_tda8083
id|module_init
c_func
(paren
id|init_tda8083
)paren
suffix:semicolon
DECL|variable|exit_tda8083
id|module_exit
c_func
(paren
id|exit_tda8083
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
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Grundig 29504-491 DVB frontend driver&quot;
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
