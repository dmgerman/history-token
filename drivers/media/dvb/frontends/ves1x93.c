multiline_comment|/*&n;    Driver for VES1893 and VES1993 QPSK Demodulators&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;    Copyright (C) 2001 Ronny Strutz &lt;3des@elitedvb.de&gt;&n;    Copyright (C) 2002 Dennis Noermann &lt;dennis.noermann@noernet.de&gt;&n;    Copyright (C) 2002-2003 Andreas Oberritter &lt;obi@linuxtv.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;ves1x93.h&quot;
DECL|struct|ves1x93_state
r_struct
id|ves1x93_state
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
id|ves1x93_config
op_star
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
multiline_comment|/* previous uncorrected block counter */
DECL|member|inversion
id|fe_spectral_inversion_t
id|inversion
suffix:semicolon
DECL|member|init_1x93_tab
id|u8
op_star
id|init_1x93_tab
suffix:semicolon
DECL|member|init_1x93_wtab
id|u8
op_star
id|init_1x93_wtab
suffix:semicolon
DECL|member|tab_size
id|u8
id|tab_size
suffix:semicolon
DECL|member|demod_type
id|u8
id|demod_type
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
DECL|macro|DEMOD_VES1893
mdefine_line|#define DEMOD_VES1893&t;&t;0
DECL|macro|DEMOD_VES1993
mdefine_line|#define DEMOD_VES1993&t;&t;1
DECL|variable|init_1893_tab
r_static
id|u8
id|init_1893_tab
(braket
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0xa4
comma
l_int|0x35
comma
l_int|0x80
comma
l_int|0x2a
comma
l_int|0x0b
comma
l_int|0x55
comma
l_int|0xc4
comma
l_int|0x09
comma
l_int|0x69
comma
l_int|0x00
comma
l_int|0x86
comma
l_int|0x4c
comma
l_int|0x28
comma
l_int|0x7f
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x81
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
l_int|0x80
comma
l_int|0x00
comma
l_int|0x21
comma
l_int|0xb0
comma
l_int|0x14
comma
l_int|0x00
comma
l_int|0xdc
comma
l_int|0x00
comma
l_int|0x81
comma
l_int|0x80
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
l_int|0x55
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7f
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|init_1993_tab
r_static
id|u8
id|init_1993_tab
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x9c
comma
l_int|0x35
comma
l_int|0x80
comma
l_int|0x6a
comma
l_int|0x09
comma
l_int|0x72
comma
l_int|0x8c
comma
l_int|0x09
comma
l_int|0x6b
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x4c
comma
l_int|0x08
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x81
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
l_int|0x80
comma
l_int|0x40
comma
l_int|0x21
comma
l_int|0xb0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x81
comma
l_int|0x80
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
l_int|0x80
comma
l_int|0x80
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
l_int|0x55
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
l_int|0x03
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x0e
comma
l_int|0x80
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|init_1893_wtab
r_static
id|u8
id|init_1893_wtab
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|init_1993_wtab
r_static
id|u8
id|init_1993_wtab
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|function|ves1x93_writereg
r_static
r_int
id|ves1x93_writereg
(paren
r_struct
id|ves1x93_state
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
id|u8
id|buf
(braket
)braket
op_assign
(brace
l_int|0x00
comma
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
l_int|3
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
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
)paren
op_ne
l_int|1
)paren
(brace
id|dprintk
(paren
l_string|&quot;%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
comma
id|reg
comma
id|data
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_readreg
r_static
id|u8
id|ves1x93_readreg
(paren
r_struct
id|ves1x93_state
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
l_int|0x00
comma
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
l_int|2
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
id|ret
suffix:semicolon
r_return
id|b1
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|ves1x93_clr_bit
r_static
r_int
id|ves1x93_clr_bit
(paren
r_struct
id|ves1x93_state
op_star
id|state
)paren
(brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0
comma
id|state-&gt;init_1x93_tab
(braket
l_int|0
)braket
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0
comma
id|state-&gt;init_1x93_tab
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_set_inversion
r_static
r_int
id|ves1x93_set_inversion
(paren
r_struct
id|ves1x93_state
op_star
id|state
comma
id|fe_spectral_inversion_t
id|inversion
)paren
(brace
id|u8
id|val
suffix:semicolon
multiline_comment|/*&n;&t; * inversion on/off are interchanged because i and q seem to&n;&t; * be swapped on the hardware&n;&t; */
r_switch
c_cond
(paren
id|inversion
)paren
(brace
r_case
id|INVERSION_OFF
suffix:colon
id|val
op_assign
l_int|0xc0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_ON
suffix:colon
id|val
op_assign
l_int|0x80
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INVERSION_AUTO
suffix:colon
id|val
op_assign
l_int|0x00
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
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x0c
comma
(paren
id|state-&gt;init_1x93_tab
(braket
l_int|0x0c
)braket
op_amp
l_int|0x3f
)paren
op_or
id|val
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_set_fec
r_static
r_int
id|ves1x93_set_fec
(paren
r_struct
id|ves1x93_state
op_star
id|state
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
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x0d
comma
l_int|0x08
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fec
template_param
id|FEC_8_9
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x0d
comma
id|fec
op_minus
id|FEC_1_2
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_get_fec
r_static
id|fe_code_rate_t
id|ves1x93_get_fec
(paren
r_struct
id|ves1x93_state
op_star
id|state
)paren
(brace
r_return
id|FEC_1_2
op_plus
(paren
(paren
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x0d
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_set_symbolrate
r_static
r_int
id|ves1x93_set_symbolrate
(paren
r_struct
id|ves1x93_state
op_star
id|state
comma
id|u32
id|srate
)paren
(brace
id|u32
id|BDR
suffix:semicolon
id|u32
id|ratio
suffix:semicolon
id|u8
id|ADCONF
comma
id|FCONF
comma
id|FNR
comma
id|AGCR
suffix:semicolon
id|u32
id|BDRI
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|u32
id|FIN
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: srate == %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
(paren
r_int
r_int
)paren
id|srate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srate
OG
id|state-&gt;config-&gt;xin
op_div
l_int|2
)paren
id|srate
op_assign
id|state-&gt;config-&gt;xin
op_div
l_int|2
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
DECL|macro|MUL
mdefine_line|#define MUL (1UL&lt;&lt;26)
id|FIN
op_assign
(paren
id|state-&gt;config-&gt;xin
op_plus
l_int|6000
)paren
op_rshift
l_int|4
suffix:semicolon
id|tmp
op_assign
id|srate
op_lshift
l_int|6
suffix:semicolon
id|ratio
op_assign
id|tmp
op_div
id|FIN
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|FIN
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
id|FIN
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_mod
id|FIN
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
id|FIN
suffix:semicolon
id|FNR
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|3
)paren
id|FNR
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|11
)paren
op_div
l_int|50
)paren
id|FNR
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|6
)paren
id|FNR
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|9
)paren
id|FNR
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|12
)paren
id|FNR
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|11
)paren
op_div
l_int|200
)paren
id|FNR
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|24
)paren
id|FNR
op_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|27
)paren
op_div
l_int|1000
)paren
id|FNR
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
id|MUL
op_div
l_int|48
)paren
id|FNR
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|ratio
OL
(paren
id|MUL
op_star
l_int|137
)paren
op_div
l_int|10000
)paren
id|FNR
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|FNR
op_eq
l_int|0xff
)paren
(brace
id|ADCONF
op_assign
l_int|0x89
suffix:semicolon
id|FCONF
op_assign
l_int|0x80
suffix:semicolon
id|FNR
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|ADCONF
op_assign
l_int|0x81
suffix:semicolon
id|FCONF
op_assign
l_int|0x88
op_or
(paren
id|FNR
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|FNR
op_amp
l_int|0x01
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
multiline_comment|/*FCONF&t; = 0x80 | ((FNR &amp; 0x01) &lt;&lt; 5) | (((FNR &gt; 1) &amp; 0x03) &lt;&lt; 3) | ((FNR &gt;&gt; 1) &amp; 0x07);*/
)brace
id|BDR
op_assign
(paren
(paren
(paren
id|ratio
op_lshift
(paren
id|FNR
op_rshift
l_int|1
)paren
)paren
op_rshift
l_int|4
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
id|BDRI
op_assign
(paren
(paren
(paren
id|FIN
op_lshift
l_int|8
)paren
op_div
(paren
(paren
id|srate
op_lshift
(paren
id|FNR
op_rshift
l_int|1
)paren
)paren
op_rshift
l_int|2
)paren
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;FNR= %d&bslash;n&quot;
comma
id|FNR
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;ratio= %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ratio
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BDR= %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|BDR
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BDRI= %02x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|BDRI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BDRI
OG
l_int|0xff
)paren
id|BDRI
op_assign
l_int|0xff
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x06
comma
l_int|0xff
op_amp
id|BDR
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x07
comma
l_int|0xff
op_amp
(paren
id|BDR
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x08
comma
l_int|0x0f
op_amp
(paren
id|BDR
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x09
comma
id|BDRI
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x20
comma
id|ADCONF
)paren
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x21
comma
id|FCONF
)paren
suffix:semicolon
id|AGCR
op_assign
id|state-&gt;init_1x93_tab
(braket
l_int|0x05
)braket
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;config-&gt;invert_pwm
)paren
id|AGCR
op_or_assign
l_int|0x20
suffix:semicolon
r_if
c_cond
(paren
id|srate
OL
l_int|6000000
)paren
id|AGCR
op_or_assign
l_int|0x80
suffix:semicolon
r_else
id|AGCR
op_and_assign
op_complement
l_int|0x80
suffix:semicolon
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x05
comma
id|AGCR
)paren
suffix:semicolon
multiline_comment|/* ves1993 hates this, will lose lock */
r_if
c_cond
(paren
id|state-&gt;demod_type
op_ne
id|DEMOD_VES1993
)paren
id|ves1x93_clr_bit
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_init
r_static
r_int
id|ves1x93_init
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|val
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: init chip&bslash;n&quot;
comma
id|__FUNCTION__
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
id|state-&gt;tab_size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;init_1x93_wtab
(braket
id|i
)braket
)paren
(brace
id|val
op_assign
id|state-&gt;init_1x93_tab
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|state-&gt;config-&gt;invert_pwm
op_logical_and
(paren
id|i
op_eq
l_int|0x05
)paren
)paren
id|val
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* invert PWM */
id|ves1x93_writereg
(paren
id|state
comma
id|i
comma
id|val
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|state-&gt;config-&gt;pll_init
)paren
(brace
id|ves1x93_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x11
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
id|ves1x93_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_set_voltage
r_static
r_int
id|ves1x93_set_voltage
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
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
r_return
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x1f
comma
l_int|0x20
)paren
suffix:semicolon
r_case
id|SEC_VOLTAGE_18
suffix:colon
r_return
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x1f
comma
l_int|0x30
)paren
suffix:semicolon
r_case
id|SEC_VOLTAGE_OFF
suffix:colon
r_return
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x1f
comma
l_int|0x00
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
DECL|function|ves1x93_read_status
r_static
r_int
id|ves1x93_read_status
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|sync
op_assign
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x0e
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The ves1893 sometimes returns sync values that make no sense,&n;&t; * because, e.g., the SIGNAL bit is 0, while some of the higher&n;&t; * bits are 1 (and how can there be a CARRIER w/o a SIGNAL?).&n;&t; * Tests showed that the the VITERBI and SYNC bits are returned&n;&t; * reliably, while the SIGNAL and CARRIER bits ar sometimes wrong.&n;&t; * If such a case occurs, we read the value again, until we get a&n;&t; * valid value.&n;&t; */
r_int
id|maxtry
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* just for safety - let&squot;s not get stuck here */
r_while
c_loop
(paren
(paren
id|sync
op_amp
l_int|0x03
)paren
op_ne
l_int|0x03
op_logical_and
(paren
id|sync
op_amp
l_int|0x0c
)paren
op_logical_and
id|maxtry
op_decrement
)paren
(brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|sync
op_assign
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x0e
)paren
suffix:semicolon
)brace
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
l_int|1
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
l_int|2
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
l_int|4
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
l_int|8
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_read_ber
r_static
r_int
id|ves1x93_read_ber
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ber
op_assign
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x15
)paren
suffix:semicolon
op_star
id|ber
op_or_assign
(paren
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x16
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
op_star
id|ber
op_or_assign
(paren
(paren
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x17
)paren
op_amp
l_int|0x0F
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
op_star
id|ber
op_mul_assign
l_int|10
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_read_signal_strength
r_static
r_int
id|ves1x93_read_signal_strength
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|signal
op_assign
op_complement
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x0b
)paren
suffix:semicolon
op_star
id|strength
op_assign
(paren
id|signal
op_lshift
l_int|8
)paren
op_or
id|signal
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_read_snr
r_static
r_int
id|ves1x93_read_snr
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|_snr
op_assign
op_complement
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x1c
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
DECL|function|ves1x93_read_ucblocks
r_static
r_int
id|ves1x93_read_ucblocks
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
op_star
id|ucblocks
op_assign
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x18
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ucblocks
op_eq
l_int|0x7f
)paren
op_star
id|ucblocks
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* counter overflow... */
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x18
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* reset the counter */
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x18
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* dto. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_set_frontend
r_static
r_int
id|ves1x93_set_frontend
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
id|ves1x93_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x11
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
id|ves1x93_writereg
c_func
(paren
id|state
comma
l_int|0x00
comma
l_int|0x01
)paren
suffix:semicolon
id|ves1x93_set_inversion
(paren
id|state
comma
id|p-&gt;inversion
)paren
suffix:semicolon
id|ves1x93_set_fec
(paren
id|state
comma
id|p-&gt;u.qpsk.fec_inner
)paren
suffix:semicolon
id|ves1x93_set_symbolrate
(paren
id|state
comma
id|p-&gt;u.qpsk.symbol_rate
)paren
suffix:semicolon
id|state-&gt;inversion
op_assign
id|p-&gt;inversion
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_get_frontend
r_static
r_int
id|ves1x93_get_frontend
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
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_int
id|afc
suffix:semicolon
id|afc
op_assign
(paren
(paren
r_int
)paren
(paren
(paren
r_char
)paren
(paren
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x0a
)paren
op_lshift
l_int|1
)paren
)paren
)paren
op_div
l_int|2
suffix:semicolon
id|afc
op_assign
(paren
id|afc
op_star
(paren
r_int
)paren
(paren
id|p-&gt;u.qpsk.symbol_rate
op_div
l_int|1000
op_div
l_int|8
)paren
)paren
op_div
l_int|16
suffix:semicolon
id|p-&gt;frequency
op_sub_assign
id|afc
suffix:semicolon
multiline_comment|/*&n;&t; * inversion indicator is only valid&n;&t; * if auto inversion was used&n;&t; */
r_if
c_cond
(paren
id|state-&gt;inversion
op_eq
id|INVERSION_AUTO
)paren
id|p-&gt;inversion
op_assign
(paren
id|ves1x93_readreg
(paren
id|state
comma
l_int|0x0f
)paren
op_amp
l_int|2
)paren
ques
c_cond
id|INVERSION_OFF
suffix:colon
id|INVERSION_ON
suffix:semicolon
id|p-&gt;u.qpsk.fec_inner
op_assign
id|ves1x93_get_fec
(paren
id|state
)paren
suffix:semicolon
multiline_comment|/*  XXX FIXME: timing offset !! */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ves1x93_sleep
r_static
r_int
id|ves1x93_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|fe-&gt;demodulator_priv
suffix:semicolon
r_return
id|ves1x93_writereg
(paren
id|state
comma
l_int|0x00
comma
l_int|0x08
)paren
suffix:semicolon
)brace
DECL|function|ves1x93_release
r_static
r_void
id|ves1x93_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|ves1x93_state
op_star
id|state
op_assign
(paren
r_struct
id|ves1x93_state
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
DECL|variable|ves1x93_ops
r_static
r_struct
id|dvb_frontend_ops
id|ves1x93_ops
suffix:semicolon
DECL|function|ves1x93_attach
r_struct
id|dvb_frontend
op_star
id|ves1x93_attach
c_func
(paren
r_const
r_struct
id|ves1x93_config
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
id|ves1x93_state
op_star
id|state
op_assign
l_int|NULL
suffix:semicolon
id|u8
id|identity
suffix:semicolon
multiline_comment|/* allocate memory for the internal state */
id|state
op_assign
(paren
r_struct
id|ves1x93_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ves1x93_state
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
id|ves1x93_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
suffix:semicolon
id|state-&gt;inversion
op_assign
id|INVERSION_OFF
suffix:semicolon
multiline_comment|/* check if the demod is there + identify it */
id|identity
op_assign
id|ves1x93_readreg
c_func
(paren
id|state
comma
l_int|0x1e
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|identity
)paren
(brace
r_case
l_int|0xdc
suffix:colon
multiline_comment|/* VES1893A rev1 */
id|printk
c_func
(paren
l_string|&quot;ves1x93: Detected ves1893a rev1&bslash;n&quot;
)paren
suffix:semicolon
id|state-&gt;demod_type
op_assign
id|DEMOD_VES1893
suffix:semicolon
id|state-&gt;init_1x93_tab
op_assign
id|init_1893_tab
suffix:semicolon
id|state-&gt;init_1x93_wtab
op_assign
id|init_1893_wtab
suffix:semicolon
id|state-&gt;tab_size
op_assign
r_sizeof
(paren
id|init_1893_tab
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xdd
suffix:colon
multiline_comment|/* VES1893A rev2 */
id|printk
c_func
(paren
l_string|&quot;ves1x93: Detected ves1893a rev2&bslash;n&quot;
)paren
suffix:semicolon
id|state-&gt;demod_type
op_assign
id|DEMOD_VES1893
suffix:semicolon
id|state-&gt;init_1x93_tab
op_assign
id|init_1893_tab
suffix:semicolon
id|state-&gt;init_1x93_wtab
op_assign
id|init_1893_wtab
suffix:semicolon
id|state-&gt;tab_size
op_assign
r_sizeof
(paren
id|init_1893_tab
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xde
suffix:colon
multiline_comment|/* VES1993 */
id|printk
c_func
(paren
l_string|&quot;ves1x93: Detected ves1993&bslash;n&quot;
)paren
suffix:semicolon
id|state-&gt;demod_type
op_assign
id|DEMOD_VES1993
suffix:semicolon
id|state-&gt;init_1x93_tab
op_assign
id|init_1993_tab
suffix:semicolon
id|state-&gt;init_1x93_wtab
op_assign
id|init_1993_wtab
suffix:semicolon
id|state-&gt;tab_size
op_assign
r_sizeof
(paren
id|init_1993_tab
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
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
DECL|variable|ves1x93_ops
r_static
r_struct
id|dvb_frontend_ops
id|ves1x93_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VLSI VES1x93 DVB-S&quot;
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
multiline_comment|/*&t;.symbol_rate_tolerance&t;=&t;???,*/
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
id|ves1x93_release
comma
dot
id|init
op_assign
id|ves1x93_init
comma
dot
id|sleep
op_assign
id|ves1x93_sleep
comma
dot
id|set_frontend
op_assign
id|ves1x93_set_frontend
comma
dot
id|get_frontend
op_assign
id|ves1x93_get_frontend
comma
dot
id|read_status
op_assign
id|ves1x93_read_status
comma
dot
id|read_ber
op_assign
id|ves1x93_read_ber
comma
dot
id|read_signal_strength
op_assign
id|ves1x93_read_signal_strength
comma
dot
id|read_snr
op_assign
id|ves1x93_read_snr
comma
dot
id|read_ucblocks
op_assign
id|ves1x93_read_ucblocks
comma
dot
id|set_voltage
op_assign
id|ves1x93_set_voltage
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
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;VLSI VES1x93 DVB-S Demodulator driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ves1x93_attach
id|EXPORT_SYMBOL
c_func
(paren
id|ves1x93_attach
)paren
suffix:semicolon
eof
