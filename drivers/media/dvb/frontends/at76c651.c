multiline_comment|/*&n; * at76c651.c&n; * &n; * Atmel DVB-C Frontend Driver (at76c651/dat7021)&n; *&n; * Copyright (C) 2001 fnbrd &lt;fnbrd@gmx.de&gt;&n; *             &amp; 2002 Andreas Oberritter &lt;obi@linuxtv.org&gt;&n; *             &amp; 2003 Wolfram Joost &lt;dbox2@frokaschwei.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#if defined(__powerpc__)
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#endif
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dvb_i2c.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|at76c651_qam
r_static
id|u8
id|at76c651_qam
suffix:semicolon
DECL|variable|at76c651_revision
r_static
id|u8
id|at76c651_revision
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk&t;if (debug) printk
multiline_comment|/*&n; * DAT7021&n; * -------&n; * Input Frequency Range (RF): 48.25 MHz to 863.25 MHz&n; * Band Width: 8 MHz&n; * Level Input (Range for Digital Signals): -61 dBm to -41 dBm&n; * Output Frequency (IF): 36 MHz&n; *&n; * (see http://www.atmel.com/atmel/acrobat/doc1320.pdf)&n; */
DECL|variable|at76c651_info
r_static
r_struct
id|dvb_frontend_info
id|at76c651_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Atmel AT76C651(B) with DAT7021&quot;
comma
dot
id|type
op_assign
id|FE_QAM
comma
dot
id|frequency_min
op_assign
l_int|48250000
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
id|FE_CAN_QAM_16
op_or
id|FE_CAN_QAM_32
op_or
id|FE_CAN_QAM_64
op_or
id|FE_CAN_QAM_128
op_or
id|FE_CAN_QAM_256
multiline_comment|/* | FE_CAN_QAM_512 | FE_CAN_QAM_1024 */
op_or
id|FE_CAN_RECOVER
op_or
id|FE_CAN_CLEAN_SETUP
op_or
id|FE_CAN_MUTE_TS
)brace
suffix:semicolon
macro_line|#if ! defined(__powerpc__)
DECL|function|__ilog2
r_static
id|__inline__
r_int
id|__ilog2
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|x
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|x
op_rshift_assign
l_int|1
suffix:semicolon
r_return
id|i
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|at76c651_writereg
r_static
r_int
id|at76c651_writereg
c_func
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
dot
id|addr
op_assign
l_int|0x1a
op_rshift
l_int|1
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
id|i2c
op_member_access_from_pointer
id|xfer
c_func
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
l_string|&quot;%s: writereg error &quot;
l_string|&quot;(reg == 0x%02x, val == 0x%02x, ret == %i)&bslash;n&quot;
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
id|dvb_delay
c_func
(paren
l_int|10
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
id|EREMOTEIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_readreg
r_static
id|u8
id|at76c651_readreg
c_func
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
dot
id|addr
op_assign
l_int|0x1a
op_rshift
l_int|1
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
l_int|0x1a
op_rshift
l_int|1
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
id|i2c
op_member_access_from_pointer
id|xfer
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
DECL|function|at76c651_reset
r_static
r_int
id|at76c651_reset
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_return
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x07
comma
l_int|0x01
)paren
suffix:semicolon
)brace
DECL|function|at76c651_disable_interrupts
r_static
r_int
id|at76c651_disable_interrupts
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_return
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x0b
comma
l_int|0x00
)paren
suffix:semicolon
)brace
DECL|function|at76c651_set_auto_config
r_static
r_int
id|at76c651_set_auto_config
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
multiline_comment|/*&n;&t; * Autoconfig&n;&t; */
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x06
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Performance optimizations, should be done after autoconfig&n;&t; */
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x10
comma
l_int|0x06
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x11
comma
(paren
(paren
id|at76c651_qam
op_eq
l_int|5
)paren
op_logical_or
(paren
id|at76c651_qam
op_eq
l_int|7
)paren
)paren
ques
c_cond
l_int|0x12
suffix:colon
l_int|0x10
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x15
comma
l_int|0x28
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x20
comma
l_int|0x09
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x24
comma
(paren
(paren
id|at76c651_qam
op_eq
l_int|5
)paren
op_logical_or
(paren
id|at76c651_qam
op_eq
l_int|7
)paren
)paren
ques
c_cond
l_int|0xC0
suffix:colon
l_int|0x90
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x30
comma
l_int|0x90
)paren
suffix:semicolon
r_if
c_cond
(paren
id|at76c651_qam
op_eq
l_int|5
)paren
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x35
comma
l_int|0x2A
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize A/D-converter&n;&t; */
r_if
c_cond
(paren
id|at76c651_revision
op_eq
l_int|0x11
)paren
(brace
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x2E
comma
l_int|0x38
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x2F
comma
l_int|0x13
)paren
suffix:semicolon
)brace
id|at76c651_disable_interrupts
c_func
(paren
id|i2c
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Restart operation&n;&t; */
id|at76c651_reset
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_set_bbfreq
r_static
r_int
id|at76c651_set_bbfreq
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x04
comma
l_int|0x3f
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x05
comma
l_int|0xee
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_switch_tuner_i2c
r_static
r_int
id|at76c651_switch_tuner_i2c
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
id|enable
)paren
(brace
r_if
c_cond
(paren
id|enable
)paren
r_return
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x0c
comma
l_int|0xc2
op_or
l_int|0x01
)paren
suffix:semicolon
r_else
r_return
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x0c
comma
l_int|0xc2
)paren
suffix:semicolon
)brace
DECL|function|dat7021_write
r_static
r_int
id|dat7021_write
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|tw
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
l_int|0xc2
op_rshift
l_int|1
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|tw
comma
dot
id|len
op_assign
r_sizeof
(paren
id|tw
)paren
)brace
suffix:semicolon
macro_line|#ifdef __LITTLE_ENDIAN
id|tw
op_assign
id|__cpu_to_be32
c_func
(paren
id|tw
)paren
suffix:semicolon
macro_line|#endif
id|at76c651_switch_tuner_i2c
c_func
(paren
id|i2c
comma
l_int|1
)paren
suffix:semicolon
id|ret
op_assign
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
suffix:semicolon
id|at76c651_switch_tuner_i2c
c_func
(paren
id|i2c
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|4
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|at76c651_reset
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dat7021_set_tv_freq
r_static
r_int
id|dat7021_set_tv_freq
c_func
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
id|dw
suffix:semicolon
id|freq
op_div_assign
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
(paren
id|freq
OL
l_int|48250
)paren
op_logical_or
(paren
id|freq
OG
l_int|863250
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * formula: dw=0x17e28e06+(freq-346000UL)/8000UL*0x800000&n;&t; *      or: dw=0x4E28E06+(freq-42000) / 125 * 0x20000&n;&t; */
id|dw
op_assign
(paren
id|freq
op_minus
l_int|42000
)paren
op_star
l_int|4096
suffix:semicolon
id|dw
op_assign
id|dw
op_div
l_int|125
suffix:semicolon
id|dw
op_assign
id|dw
op_star
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|freq
OG
l_int|394000
)paren
id|dw
op_add_assign
l_int|0x4E28E85
suffix:semicolon
r_else
id|dw
op_add_assign
l_int|0x4E28E06
suffix:semicolon
r_return
id|dat7021_write
c_func
(paren
id|i2c
comma
id|dw
)paren
suffix:semicolon
)brace
DECL|function|at76c651_set_symbolrate
r_static
r_int
id|at76c651_set_symbolrate
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|symbolrate
)paren
(brace
id|u8
id|exponent
suffix:semicolon
id|u32
id|mantissa
suffix:semicolon
r_if
c_cond
(paren
id|symbolrate
OG
l_int|9360000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * FREF = 57800 kHz&n;&t; * exponent = 10 + floor ( log2 ( symbolrate / FREF ) )&n;&t; * mantissa = ( symbolrate / FREF) * ( 1 &lt;&lt; ( 30 - exponent ) )&n;&t; */
id|exponent
op_assign
id|__ilog2
c_func
(paren
(paren
id|symbolrate
op_lshift
l_int|4
)paren
op_div
l_int|903125
)paren
suffix:semicolon
id|mantissa
op_assign
(paren
(paren
id|symbolrate
op_div
l_int|3125
)paren
op_star
(paren
l_int|1
op_lshift
(paren
l_int|24
op_minus
id|exponent
)paren
)paren
)paren
op_div
l_int|289
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x00
comma
id|mantissa
op_rshift
l_int|13
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x01
comma
id|mantissa
op_rshift
l_int|5
)paren
suffix:semicolon
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x02
comma
(paren
id|mantissa
op_lshift
l_int|3
)paren
op_or
id|exponent
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_set_qam
r_static
r_int
id|at76c651_set_qam
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_modulation_t
id|qam
)paren
(brace
r_switch
c_cond
(paren
id|qam
)paren
(brace
r_case
id|QPSK
suffix:colon
id|at76c651_qam
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_16
suffix:colon
id|at76c651_qam
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_32
suffix:colon
id|at76c651_qam
op_assign
l_int|0x05
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_64
suffix:colon
id|at76c651_qam
op_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_128
suffix:colon
id|at76c651_qam
op_assign
l_int|0x07
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_256
suffix:colon
id|at76c651_qam
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
id|QAM_512
suffix:colon
id|at76c651_qam
op_assign
l_int|0x09
suffix:semicolon
r_break
suffix:semicolon
r_case
id|QAM_1024
suffix:colon
id|at76c651_qam
op_assign
l_int|0x0A
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x03
comma
id|at76c651_qam
)paren
suffix:semicolon
)brace
DECL|function|at76c651_set_inversion
r_static
r_int
id|at76c651_set_inversion
c_func
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
id|u8
id|feciqinv
op_assign
id|at76c651_readreg
c_func
(paren
id|i2c
comma
l_int|0x60
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|inversion
)paren
(brace
r_case
id|INVERSION_OFF
suffix:colon
id|feciqinv
op_or_assign
l_int|0x02
suffix:semicolon
id|feciqinv
op_and_assign
l_int|0xFE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_ON
suffix:colon
id|feciqinv
op_or_assign
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_AUTO
suffix:colon
id|feciqinv
op_and_assign
l_int|0xFC
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
id|at76c651_writereg
c_func
(paren
id|i2c
comma
l_int|0x60
comma
id|feciqinv
)paren
suffix:semicolon
)brace
DECL|function|at76c651_set_parameters
r_static
r_int
id|at76c651_set_parameters
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_struct
id|dvb_frontend_parameters
op_star
id|p
)paren
(brace
id|dat7021_set_tv_freq
c_func
(paren
id|i2c
comma
id|p-&gt;frequency
)paren
suffix:semicolon
id|at76c651_set_symbolrate
c_func
(paren
id|i2c
comma
id|p-&gt;u.qam.symbol_rate
)paren
suffix:semicolon
id|at76c651_set_inversion
c_func
(paren
id|i2c
comma
id|p-&gt;inversion
)paren
suffix:semicolon
id|at76c651_set_auto_config
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_set_defaults
r_static
r_int
id|at76c651_set_defaults
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|at76c651_set_symbolrate
c_func
(paren
id|i2c
comma
l_int|6900000
)paren
suffix:semicolon
id|at76c651_set_qam
c_func
(paren
id|i2c
comma
id|QAM_64
)paren
suffix:semicolon
id|at76c651_set_bbfreq
c_func
(paren
id|i2c
)paren
suffix:semicolon
id|at76c651_set_auto_config
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_ioctl
r_static
r_int
id|at76c651_ioctl
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
c_func
(paren
id|arg
comma
op_amp
id|at76c651_info
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
id|sync
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Bits: FEC, CAR, EQU, TIM, AGC2, AGC1, ADC, PLL (PLL=0) &n;&t;&t;&t; */
id|sync
op_assign
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x80
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
id|sync
op_amp
(paren
l_int|0x04
op_or
l_int|0x10
)paren
)paren
multiline_comment|/* AGC1 || TIM */
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
l_int|0x10
)paren
multiline_comment|/* TIM */
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
l_int|0x80
)paren
multiline_comment|/* FEC */
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
multiline_comment|/* CAR */
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
l_int|0xF0
)paren
op_eq
l_int|0xF0
)paren
multiline_comment|/* TIM &amp;&amp; EQU &amp;&amp; CAR &amp;&amp; FEC */
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
(paren
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x81
)paren
op_amp
l_int|0x0F
)paren
op_lshift
l_int|16
suffix:semicolon
op_star
id|ber
op_or_assign
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x82
)paren
op_lshift
l_int|8
suffix:semicolon
op_star
id|ber
op_or_assign
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x83
)paren
suffix:semicolon
op_star
id|ber
op_mul_assign
l_int|10
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
op_complement
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x91
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
op_star
(paren
id|u16
op_star
)paren
id|arg
op_assign
l_int|0xFFFF
op_minus
(paren
(paren
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x8F
)paren
op_lshift
l_int|8
)paren
op_or
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x90
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
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
id|at76c651_readreg
c_func
(paren
id|fe-&gt;i2c
comma
l_int|0x82
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_SET_FRONTEND
suffix:colon
r_return
id|at76c651_set_parameters
c_func
(paren
id|fe-&gt;i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_GET_FRONTEND
suffix:colon
r_break
suffix:semicolon
r_case
id|FE_SLEEP
suffix:colon
r_break
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_return
id|at76c651_set_defaults
c_func
(paren
id|fe-&gt;i2c
)paren
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
r_return
id|at76c651_reset
c_func
(paren
id|fe-&gt;i2c
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|at76c651_attach
r_static
r_int
id|at76c651_attach
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
(paren
id|at76c651_readreg
c_func
(paren
id|i2c
comma
l_int|0x0E
)paren
op_ne
l_int|0x65
)paren
op_logical_or
(paren
(paren
(paren
id|at76c651_revision
op_assign
id|at76c651_readreg
c_func
(paren
id|i2c
comma
l_int|0x0F
)paren
)paren
op_amp
l_int|0xFE
)paren
op_ne
l_int|0x10
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;no AT76C651(B) found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|at76c651_revision
op_eq
l_int|0x10
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;AT76C651A found&bslash;n&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|at76c651_info.name
comma
l_string|&quot;Atmel AT76C651A with DAT7021&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|at76c651_info.name
comma
l_string|&quot;Atmel AT76C651B with DAT7021&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;AT76C651B found&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|at76c651_set_defaults
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_return
id|dvb_register_frontend
c_func
(paren
id|at76c651_ioctl
comma
id|i2c
comma
l_int|NULL
comma
op_amp
id|at76c651_info
)paren
suffix:semicolon
)brace
DECL|function|at76c651_detach
r_static
r_void
id|at76c651_detach
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_void
op_star
id|data
)paren
(brace
id|dvb_unregister_frontend
c_func
(paren
id|at76c651_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
DECL|function|at76c651_init
r_static
r_int
id|__init
id|at76c651_init
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
id|at76c651_attach
comma
id|at76c651_detach
)paren
suffix:semicolon
)brace
DECL|function|at76c651_exit
r_static
r_void
id|__exit
id|at76c651_exit
c_func
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
c_func
(paren
id|at76c651_attach
)paren
suffix:semicolon
)brace
DECL|variable|at76c651_init
id|module_init
c_func
(paren
id|at76c651_init
)paren
suffix:semicolon
DECL|variable|at76c651_exit
id|module_exit
c_func
(paren
id|at76c651_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;at76c651/dat7021 dvb-c frontend driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andreas Oberritter &lt;obi@linuxtv.org&gt;&quot;
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
eof
