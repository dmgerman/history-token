multiline_comment|/* &n;    driver for Grundig 29504-401 DVB-T Frontends based on&n;    LSI L64781 COFDM demodulator as used in Technotrend DVB-T cards&n;&n;    Copyright (C) 2001 Holger Waechtler &lt;holger@convergence.de&gt;&n;                       for Convergence Integrated Media GmbH&n;                       Marko Kohtala &lt;marko.kohtala@luukku.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
DECL|macro|FRONTEND_NAME
mdefine_line|#define FRONTEND_NAME &quot;dvbfe_l64781&quot;
DECL|macro|dprintk
mdefine_line|#define dprintk(args...) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (debug) printk(KERN_DEBUG FRONTEND_NAME &quot;: &quot; args); &bslash;&n;&t;} while (0)
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|variable|old_set_tv_freq
r_static
r_int
id|old_set_tv_freq
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
id|module_param
c_func
(paren
id|old_set_tv_freq
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|old_set_tv_freq
comma
l_string|&quot;Use old tsa5060_set_tv_freq calculations.&quot;
)paren
suffix:semicolon
DECL|struct|l64781_state
r_struct
id|l64781_state
(brace
DECL|member|first
r_int
id|first
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i2c
r_struct
id|i2c_adapter
op_star
id|i2c
suffix:semicolon
DECL|member|dvb
r_struct
id|dvb_adapter
op_star
id|dvb
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|l64781_info
r_struct
id|dvb_frontend_info
id|l64781_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Grundig 29504-401 (LSI L64781 Based)&quot;
comma
dot
id|type
op_assign
id|FE_OFDM
comma
multiline_comment|/*&t;.frequency_min = ???,*/
multiline_comment|/*&t;.frequency_max = ???,*/
dot
id|frequency_stepsize
op_assign
l_int|166666
comma
multiline_comment|/*      .frequency_tolerance = ???,*/
multiline_comment|/*      .symbol_rate_tolerance = ???,*/
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
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_7_8
op_or
id|FE_CAN_QPSK
op_or
id|FE_CAN_QAM_16
op_or
id|FE_CAN_QAM_64
op_or
id|FE_CAN_MUTE_TS
)brace
suffix:semicolon
DECL|function|l64781_writereg
r_static
r_int
id|l64781_writereg
(paren
r_struct
id|i2c_adapter
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
dot
id|addr
op_assign
l_int|0x55
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
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c_transfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
id|dprintk
(paren
l_string|&quot;%s: write_reg error (reg == %02x) = %02x!&bslash;n&quot;
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
DECL|function|l64781_readreg
r_static
id|u8
id|l64781_readreg
(paren
r_struct
id|i2c_adapter
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
dot
id|addr
op_assign
l_int|0x55
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
l_int|0x55
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
DECL|function|tsa5060_write
r_static
r_int
id|tsa5060_write
(paren
r_struct
id|i2c_adapter
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
dot
id|addr
op_assign
l_int|0x61
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|data
comma
dot
id|len
op_assign
l_int|4
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c_transfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
id|dprintk
(paren
l_string|&quot;%s: write_reg error == %02x!&bslash;n&quot;
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
multiline_comment|/**&n; *   set up the downconverter frequency divisor for a&n; *   reference clock comparision frequency of 166666 Hz.&n; *   frequency offset is 36125000 Hz.&n; */
DECL|function|tsa5060_set_tv_freq
r_static
r_int
id|tsa5060_set_tv_freq
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
comma
id|u32
id|freq
)paren
(brace
id|u32
id|div
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
id|u8
id|cfg
comma
id|cpump
comma
id|band_select
suffix:semicolon
r_if
c_cond
(paren
id|old_set_tv_freq
)paren
id|div
op_assign
(paren
l_int|36000000
op_plus
id|freq
)paren
op_div
l_int|166666
suffix:semicolon
r_else
id|div
op_assign
(paren
l_int|36125000
op_plus
id|freq
)paren
op_div
l_int|166666
suffix:semicolon
id|cfg
op_assign
l_int|0x88
suffix:semicolon
id|cpump
op_assign
id|freq
OL
l_int|175000000
ques
c_cond
l_int|2
suffix:colon
id|freq
OL
l_int|390000000
ques
c_cond
l_int|1
suffix:colon
id|freq
OL
l_int|470000000
ques
c_cond
l_int|2
suffix:colon
id|freq
OL
l_int|750000000
ques
c_cond
l_int|1
suffix:colon
l_int|3
suffix:semicolon
id|band_select
op_assign
id|freq
OL
l_int|175000000
ques
c_cond
l_int|0x0e
suffix:colon
id|freq
OL
l_int|470000000
ques
c_cond
l_int|0x05
suffix:colon
l_int|0x03
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
(paren
(paren
id|div
op_rshift
l_int|10
)paren
op_amp
l_int|0x60
)paren
op_or
id|cfg
suffix:semicolon
r_if
c_cond
(paren
id|old_set_tv_freq
)paren
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0xc0
suffix:semicolon
r_else
id|buf
(braket
l_int|3
)braket
op_assign
(paren
id|cpump
op_lshift
l_int|6
)paren
op_or
id|band_select
suffix:semicolon
r_return
id|tsa5060_write
(paren
id|i2c
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|apply_tps
r_static
r_void
id|apply_tps
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x2a
comma
l_int|0x00
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x2a
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* This here is a little bit questionable because it enables&n;&t;   the automatic update of TPS registers. I think we&squot;d need to&n;&t;   handle the IRQ from FE to update some other registers as&n;&t;   well, or at least implement some magic to tuning to correct&n;&t;   to the TPS received from transmission. */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x2a
comma
l_int|0x02
)paren
suffix:semicolon
)brace
DECL|function|reset_afc
r_static
r_void
id|reset_afc
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
multiline_comment|/* Set AFC stall for the AFC_INIT_FRQ setting, TIM_STALL for&n;&t;   timing offset */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x07
comma
l_int|0x9e
)paren
suffix:semicolon
multiline_comment|/* stall AFC */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x08
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* AFC INIT FREQ */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x09
comma
l_int|0
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x0a
comma
l_int|0
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x07
comma
l_int|0x8e
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x0e
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* AGC gain to zero in beginning */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x11
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* stall TIM */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x10
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* TIM_OFFSET_LSB */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x12
comma
l_int|0
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x13
comma
l_int|0
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x11
comma
l_int|0x00
)paren
suffix:semicolon
)brace
DECL|function|apply_frontend_param
r_static
r_int
id|apply_frontend_param
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
comma
r_struct
id|dvb_frontend_parameters
op_star
id|param
)paren
(brace
multiline_comment|/* The coderates for FEC_NONE, FEC_4_5 and FEC_FEC_6_7 are arbitrary */
r_static
r_const
id|u8
id|fec_tab
(braket
)braket
op_assign
(brace
l_int|7
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|9
comma
l_int|3
comma
l_int|10
comma
l_int|4
)brace
suffix:semicolon
multiline_comment|/* QPSK, QAM_16, QAM_64 */
r_static
r_const
id|u8
id|qam_tab
(braket
)braket
op_assign
(brace
l_int|2
comma
l_int|4
comma
l_int|0
comma
l_int|6
)brace
suffix:semicolon
r_static
r_const
id|u8
id|bw_tab
(braket
)braket
op_assign
(brace
l_int|8
comma
l_int|7
comma
l_int|6
)brace
suffix:semicolon
multiline_comment|/* 8Mhz, 7MHz, 6MHz */
r_static
r_const
id|u8
id|guard_tab
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|4
comma
l_int|8
)brace
suffix:semicolon
multiline_comment|/* The Grundig 29504-401.04 Tuner comes with 18.432MHz crystal. */
r_static
r_const
id|u32
id|ppm
op_assign
l_int|8000
suffix:semicolon
r_struct
id|dvb_ofdm_parameters
op_star
id|p
op_assign
op_amp
id|param-&gt;u.ofdm
suffix:semicolon
id|u32
id|ddfs_offset_fixed
suffix:semicolon
multiline_comment|/*&t;u32 ddfs_offset_variable = 0x6000-((1000000UL+ppm)/ */
multiline_comment|/*&t;&t;&t;bw_tab[p-&gt;bandWidth]&lt;&lt;10)/15625; */
id|u32
id|init_freq
suffix:semicolon
id|u32
id|spi_bias
suffix:semicolon
id|u8
id|val0x04
suffix:semicolon
id|u8
id|val0x05
suffix:semicolon
id|u8
id|val0x06
suffix:semicolon
r_int
id|bw
op_assign
id|p-&gt;bandwidth
op_minus
id|BANDWIDTH_8_MHZ
suffix:semicolon
r_if
c_cond
(paren
id|param-&gt;inversion
op_ne
id|INVERSION_ON
op_logical_and
id|param-&gt;inversion
op_ne
id|INVERSION_OFF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|bw
template_param
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;code_rate_HP
op_ne
id|FEC_1_2
op_logical_and
id|p-&gt;code_rate_HP
op_ne
id|FEC_2_3
op_logical_and
id|p-&gt;code_rate_HP
op_ne
id|FEC_3_4
op_logical_and
id|p-&gt;code_rate_HP
op_ne
id|FEC_5_6
op_logical_and
id|p-&gt;code_rate_HP
op_ne
id|FEC_7_8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;hierarchy_information
op_ne
id|HIERARCHY_NONE
op_logical_and
(paren
id|p-&gt;code_rate_LP
op_ne
id|FEC_1_2
op_logical_and
id|p-&gt;code_rate_LP
op_ne
id|FEC_2_3
op_logical_and
id|p-&gt;code_rate_LP
op_ne
id|FEC_3_4
op_logical_and
id|p-&gt;code_rate_LP
op_ne
id|FEC_5_6
op_logical_and
id|p-&gt;code_rate_LP
op_ne
id|FEC_7_8
)paren
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
id|p-&gt;hierarchy_information
template_param
id|HIERARCHY_4
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ddfs_offset_fixed
op_assign
l_int|0x4000
op_minus
(paren
id|ppm
op_lshift
l_int|16
)paren
op_div
id|bw_tab
(braket
id|p-&gt;bandwidth
)braket
op_div
l_int|1000000
suffix:semicolon
multiline_comment|/* This works up to 20000 ppm, it overflows if too large ppm! */
id|init_freq
op_assign
(paren
(paren
(paren
l_int|8UL
op_lshift
l_int|25
)paren
op_plus
(paren
l_int|8UL
op_lshift
l_int|19
)paren
op_div
l_int|25
op_star
id|ppm
op_div
(paren
l_int|15625
op_div
l_int|25
)paren
)paren
op_div
id|bw_tab
(braket
id|p-&gt;bandwidth
)braket
op_amp
l_int|0xFFFFFF
)paren
suffix:semicolon
multiline_comment|/* SPI bias calculation is slightly modified to fit in 32bit */
multiline_comment|/* will work for high ppm only... */
id|spi_bias
op_assign
l_int|378
op_star
(paren
l_int|1
op_lshift
l_int|10
)paren
suffix:semicolon
id|spi_bias
op_mul_assign
l_int|16
suffix:semicolon
id|spi_bias
op_mul_assign
id|bw_tab
(braket
id|p-&gt;bandwidth
)braket
suffix:semicolon
id|spi_bias
op_mul_assign
id|qam_tab
(braket
id|p-&gt;constellation
)braket
suffix:semicolon
id|spi_bias
op_div_assign
id|p-&gt;code_rate_HP
op_plus
l_int|1
suffix:semicolon
id|spi_bias
op_div_assign
(paren
id|guard_tab
(braket
id|p-&gt;guard_interval
)braket
op_plus
l_int|32
)paren
suffix:semicolon
id|spi_bias
op_mul_assign
l_int|1000ULL
suffix:semicolon
id|spi_bias
op_div_assign
l_int|1000ULL
op_plus
id|ppm
op_div
l_int|1000
suffix:semicolon
id|spi_bias
op_mul_assign
id|p-&gt;code_rate_HP
suffix:semicolon
id|val0x04
op_assign
(paren
id|p-&gt;transmission_mode
op_lshift
l_int|2
)paren
op_or
id|p-&gt;guard_interval
suffix:semicolon
id|val0x05
op_assign
id|fec_tab
(braket
id|p-&gt;code_rate_HP
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;hierarchy_information
op_ne
id|HIERARCHY_NONE
)paren
id|val0x05
op_or_assign
(paren
id|p-&gt;code_rate_LP
op_minus
id|FEC_1_2
)paren
op_lshift
l_int|3
suffix:semicolon
id|val0x06
op_assign
(paren
id|p-&gt;hierarchy_information
op_lshift
l_int|2
)paren
op_or
id|p-&gt;constellation
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x04
comma
id|val0x04
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x05
comma
id|val0x05
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x06
comma
id|val0x06
)paren
suffix:semicolon
id|reset_afc
(paren
id|i2c
)paren
suffix:semicolon
multiline_comment|/* Technical manual section 2.6.1, TIM_IIR_GAIN optimal values */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x15
comma
id|p-&gt;transmission_mode
op_eq
id|TRANSMISSION_MODE_2K
ques
c_cond
l_int|1
suffix:colon
l_int|3
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x16
comma
id|init_freq
op_amp
l_int|0xff
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x17
comma
(paren
id|init_freq
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x18
comma
(paren
id|init_freq
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x1b
comma
id|spi_bias
op_amp
l_int|0xff
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x1c
comma
(paren
id|spi_bias
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x1d
comma
(paren
(paren
id|spi_bias
op_rshift
l_int|16
)paren
op_amp
l_int|0x7f
)paren
op_or
(paren
id|param-&gt;inversion
op_eq
id|INVERSION_ON
ques
c_cond
l_int|0x80
suffix:colon
l_int|0x00
)paren
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x22
comma
id|ddfs_offset_fixed
op_amp
l_int|0xff
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x23
comma
(paren
id|ddfs_offset_fixed
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*  clear interrupt registers... */
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/*  dto. */
id|apply_tps
(paren
id|i2c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|reset_and_configure
r_static
r_int
id|reset_and_configure
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
id|u8
id|buf
(braket
)braket
op_assign
(brace
l_int|0x06
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
l_int|0x00
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
l_int|1
)brace
suffix:semicolon
r_return
(paren
id|i2c_transfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|get_frontend
r_static
r_int
id|get_frontend
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
comma
r_struct
id|dvb_frontend_parameters
op_star
id|param
)paren
(brace
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|l64781_readreg
c_func
(paren
id|i2c
comma
l_int|0x04
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tmp
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|param-&gt;u.ofdm.guard_interval
op_assign
id|GUARD_INTERVAL_1_32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|param-&gt;u.ofdm.guard_interval
op_assign
id|GUARD_INTERVAL_1_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|param-&gt;u.ofdm.guard_interval
op_assign
id|GUARD_INTERVAL_1_8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|param-&gt;u.ofdm.guard_interval
op_assign
id|GUARD_INTERVAL_1_4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|tmp
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
id|param-&gt;u.ofdm.transmission_mode
op_assign
id|TRANSMISSION_MODE_2K
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|param-&gt;u.ofdm.transmission_mode
op_assign
id|TRANSMISSION_MODE_8K
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unexpected value for transmission_mode&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|l64781_readreg
c_func
(paren
id|i2c
comma
l_int|0x05
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tmp
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|param-&gt;u.ofdm.code_rate_HP
op_assign
id|FEC_1_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|param-&gt;u.ofdm.code_rate_HP
op_assign
id|FEC_2_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|param-&gt;u.ofdm.code_rate_HP
op_assign
id|FEC_3_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|param-&gt;u.ofdm.code_rate_HP
op_assign
id|FEC_5_6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|param-&gt;u.ofdm.code_rate_HP
op_assign
id|FEC_7_8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unexpected value for code_rate_HP&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|tmp
op_rshift
l_int|3
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|param-&gt;u.ofdm.code_rate_LP
op_assign
id|FEC_1_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|param-&gt;u.ofdm.code_rate_LP
op_assign
id|FEC_2_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|param-&gt;u.ofdm.code_rate_LP
op_assign
id|FEC_3_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|param-&gt;u.ofdm.code_rate_LP
op_assign
id|FEC_5_6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|param-&gt;u.ofdm.code_rate_LP
op_assign
id|FEC_7_8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unexpected value for code_rate_LP&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|l64781_readreg
c_func
(paren
id|i2c
comma
l_int|0x06
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|tmp
op_amp
l_int|3
)paren
(brace
r_case
l_int|0
suffix:colon
id|param-&gt;u.ofdm.constellation
op_assign
id|QPSK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|param-&gt;u.ofdm.constellation
op_assign
id|QAM_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|param-&gt;u.ofdm.constellation
op_assign
id|QAM_64
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unexpected value for constellation&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|tmp
op_rshift
l_int|2
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|param-&gt;u.ofdm.hierarchy_information
op_assign
id|HIERARCHY_NONE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|param-&gt;u.ofdm.hierarchy_information
op_assign
id|HIERARCHY_1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|param-&gt;u.ofdm.hierarchy_information
op_assign
id|HIERARCHY_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|param-&gt;u.ofdm.hierarchy_information
op_assign
id|HIERARCHY_4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unexpected value for hierarchy&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x1d
)paren
suffix:semicolon
id|param-&gt;inversion
op_assign
(paren
id|tmp
op_amp
l_int|0x80
)paren
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
id|tmp
op_assign
(paren
r_int
)paren
(paren
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x08
)paren
op_or
(paren
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x09
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x0a
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|param-&gt;frequency
op_add_assign
id|tmp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init
r_static
r_int
id|init
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
id|reset_and_configure
(paren
id|i2c
)paren
suffix:semicolon
multiline_comment|/* Power up */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x3e
comma
l_int|0xa5
)paren
suffix:semicolon
multiline_comment|/* Reset hard */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x2a
comma
l_int|0x04
)paren
suffix:semicolon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x2a
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Set tuner specific things */
multiline_comment|/* AFC_POL, set also in reset_afc */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x07
comma
l_int|0x8e
)paren
suffix:semicolon
multiline_comment|/* Use internal ADC */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x0b
comma
l_int|0x81
)paren
suffix:semicolon
multiline_comment|/* AGC loop gain, and polarity is positive */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x0c
comma
l_int|0x84
)paren
suffix:semicolon
multiline_comment|/* Internal ADC outputs two&squot;s complement */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x0d
comma
l_int|0x8c
)paren
suffix:semicolon
multiline_comment|/* With ppm=8000, it seems the DTR_SENSITIVITY will result in&n;           value of 2 with all possible bandwidths and guard&n;           intervals, which is the initial value anyway. */
multiline_comment|/*l64781_writereg (i2c, 0x19, 0x92);*/
multiline_comment|/* Everything is two&squot;s complement, soft bit and CSI_OUT too */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x1e
comma
l_int|0x09
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|l64781_ioctl
r_int
id|l64781_ioctl
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
id|l64781_state
op_star
id|state
op_assign
id|fe-&gt;data
suffix:semicolon
r_struct
id|i2c_adapter
op_star
id|i2c
op_assign
id|state-&gt;i2c
suffix:semicolon
r_int
id|res
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
id|l64781_info
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
r_int
id|sync
op_assign
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x32
)paren
suffix:semicolon
r_int
id|gain
op_assign
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x0e
)paren
suffix:semicolon
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*  clear interrupt registers... */
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/*  dto. */
op_star
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|gain
OG
l_int|5
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
l_int|0x02
)paren
multiline_comment|/* VCXO locked, this criteria should be ok */
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
l_int|0x20
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
l_int|0x40
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
op_eq
l_int|0x7f
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
(brace
multiline_comment|/*   XXX FIXME: set up counting period (reg 0x26...0x28)&n;&t;&t; */
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
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x39
)paren
op_or
(paren
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x3a
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
(brace
id|u8
id|gain
op_assign
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x0e
)paren
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|arg
op_assign
(paren
id|gain
op_lshift
l_int|8
)paren
op_or
id|gain
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_SNR
suffix:colon
(brace
id|u16
op_star
id|snr
op_assign
(paren
id|u16
op_star
)paren
id|arg
suffix:semicolon
id|u8
id|avg_quality
op_assign
l_int|0xff
op_minus
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x33
)paren
suffix:semicolon
op_star
id|snr
op_assign
(paren
id|avg_quality
op_lshift
l_int|8
)paren
op_or
id|avg_quality
suffix:semicolon
multiline_comment|/* not exact, but...*/
r_break
suffix:semicolon
)brace
r_case
id|FE_READ_UNCORRECTED_BLOCKS
suffix:colon
(brace
id|u32
op_star
id|ub
op_assign
(paren
id|u32
op_star
)paren
id|arg
suffix:semicolon
op_star
id|ub
op_assign
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x37
)paren
op_or
(paren
id|l64781_readreg
(paren
id|i2c
comma
l_int|0x38
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|tsa5060_set_tv_freq
(paren
id|i2c
comma
id|p-&gt;frequency
)paren
suffix:semicolon
r_return
id|apply_frontend_param
(paren
id|i2c
comma
id|p
)paren
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
r_return
id|get_frontend
c_func
(paren
id|i2c
comma
id|p
)paren
suffix:semicolon
)brace
r_case
id|FE_SLEEP
suffix:colon
multiline_comment|/* Power down */
r_return
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x3e
comma
l_int|0x5a
)paren
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
id|res
op_assign
id|init
(paren
id|i2c
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_eq
l_int|0
)paren
op_logical_and
(paren
id|state-&gt;first
)paren
)paren
(brace
id|state-&gt;first
op_assign
l_int|0
suffix:semicolon
id|msleep
c_func
(paren
l_int|200
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
r_case
id|FE_GET_TUNE_SETTINGS
suffix:colon
(brace
r_struct
id|dvb_frontend_tune_settings
op_star
id|fesettings
op_assign
(paren
r_struct
id|dvb_frontend_tune_settings
op_star
)paren
id|arg
suffix:semicolon
id|fesettings-&gt;min_delay_ms
op_assign
l_int|200
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
r_default
suffix:colon
id|dprintk
(paren
l_string|&quot;%s: unknown command !!!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|l64781_probe
r_static
r_int
id|l64781_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
id|u8
id|reg0x3e
suffix:semicolon
id|u8
id|b0
(braket
)braket
op_assign
(brace
l_int|0x1a
)brace
suffix:semicolon
id|u8
id|b1
(braket
)braket
op_assign
(brace
l_int|0x00
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
l_int|0x55
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
l_int|0x55
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
multiline_comment|/**&n;&t; *  the L64781 won&squot;t show up before we send the reset_and_configure()&n;&t; *  broadcast. If nothing responds there is no L64781 on the bus...&n;&t; */
r_if
c_cond
(paren
id|reset_and_configure
c_func
(paren
id|i2c
)paren
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;No response to reset and configure broadcast...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* The chip always responds to reads */
r_if
c_cond
(paren
id|i2c_transfer
c_func
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
op_ne
l_int|2
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;No response to read on I2C bus&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Save current register contents for bailout */
id|reg0x3e
op_assign
id|l64781_readreg
c_func
(paren
id|i2c
comma
l_int|0x3e
)paren
suffix:semicolon
multiline_comment|/* Reading the POWER_DOWN register always returns 0 */
r_if
c_cond
(paren
id|reg0x3e
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;Device doesn&squot;t look like L64781&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Turn the chip off */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x3e
comma
l_int|0x5a
)paren
suffix:semicolon
multiline_comment|/* Responds to all reads with 0 */
r_if
c_cond
(paren
id|l64781_readreg
c_func
(paren
id|i2c
comma
l_int|0x1a
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;Read 1 returned unexpcted value&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Turn the chip on */
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x3e
comma
l_int|0xa5
)paren
suffix:semicolon
multiline_comment|/* Responds with register default value */
r_if
c_cond
(paren
id|l64781_readreg
c_func
(paren
id|i2c
comma
l_int|0x1a
)paren
op_ne
l_int|0xa1
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;Read 2 returned unexpcted value&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|l64781_writereg
(paren
id|i2c
comma
l_int|0x3e
comma
id|reg0x3e
)paren
suffix:semicolon
multiline_comment|/* restore reg 0x3e */
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
suffix:semicolon
DECL|function|l64781_attach_adapter
r_static
r_int
id|l64781_attach_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_struct
id|l64781_state
op_star
id|state
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Trying to attach to adapter 0x%x:%s.&bslash;n&quot;
comma
id|adapter-&gt;id
comma
id|adapter-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|l64781_probe
c_func
(paren
id|adapter
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|l64781_state
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|state
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|l64781_state
)paren
)paren
suffix:semicolon
id|state-&gt;i2c
op_assign
id|adapter
suffix:semicolon
id|state-&gt;first
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|client
comma
op_amp
id|client_template
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|client-&gt;addr
op_assign
l_int|0
suffix:semicolon
singleline_comment|//XXX
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c_attach_client
c_func
(paren
id|client
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|state-&gt;dvb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|dvb_register_frontend
c_func
(paren
id|l64781_ioctl
comma
id|state-&gt;dvb
comma
id|state
comma
op_amp
id|l64781_info
comma
id|THIS_MODULE
)paren
)paren
)paren
(brace
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|l64781_detach_client
r_static
r_int
id|l64781_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|l64781_state
op_star
id|state
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|dvb_unregister_frontend
c_func
(paren
id|l64781_ioctl
comma
id|state-&gt;dvb
)paren
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|state-&gt;dvb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|l64781_command
r_static
r_int
id|l64781_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
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
id|l64781_state
op_star
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
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
id|FE_REGISTER
suffix:colon
(brace
id|data-&gt;dvb
op_assign
id|arg
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_UNREGISTER
suffix:colon
(brace
id|data-&gt;dvb
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
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
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
id|FRONTEND_NAME
comma
dot
id|id
op_assign
id|I2C_DRIVERID_DVBFE_L64781
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|l64781_attach_adapter
comma
dot
id|detach_client
op_assign
id|l64781_detach_client
comma
dot
id|command
op_assign
id|l64781_command
comma
)brace
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
op_assign
(brace
dot
id|name
op_assign
id|FRONTEND_NAME
comma
dot
id|flags
op_assign
id|I2C_CLIENT_ALLOW_USE
comma
dot
id|driver
op_assign
op_amp
id|driver
comma
)brace
suffix:semicolon
DECL|function|init_l64781
r_static
r_int
id|__init
id|init_l64781
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|exit_l64781
r_static
r_void
id|__exit
id|exit_l64781
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|i2c_del_driver
c_func
(paren
op_amp
id|driver
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;l64781: driver deregistration failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|init_l64781
id|module_init
c_func
(paren
id|init_l64781
)paren
suffix:semicolon
DECL|variable|exit_l64781
id|module_exit
c_func
(paren
id|exit_l64781
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Grundig 29504-401 DVB-T Frontend (LSI L64781 Based)&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Holger Waechtler, Marko Kohtala&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
