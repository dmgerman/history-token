multiline_comment|/*&n; * budget.c: driver for the SAA7146 based Budget DVB cards&n; *&n; * Compiled from various sources by Michael Hunold &lt;michael@mihu.de&gt;&n; *&n; * Copyright (C) 2002 Ralph Metzler &lt;rjkm@metzlerbros.de&gt;&n; *&n; * Copyright (C) 1999-2002 Ralph  Metzler&n; *                       &amp; Marcus Metzler for convergence integrated media GmbH&n; *&n; * 26feb2004 Support for FS Activy Card (Grundig tuner) by&n; *           Michael Dreher &lt;michael@5dot1.de&gt;,&n; *           Oliver Endriss &lt;o.endriss@gmx.de&gt; and&n; *           Andreas &squot;randy&squot; Weinberger&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; *&n; *&n; * the project&squot;s page is at http://www.linuxtv.org/dvb/&n; */
macro_line|#include &quot;budget.h&quot;
macro_line|#include &quot;stv0299.h&quot;
macro_line|#include &quot;ves1x93.h&quot;
macro_line|#include &quot;ves1820.h&quot;
macro_line|#include &quot;l64781.h&quot;
macro_line|#include &quot;tda8083.h&quot;
DECL|function|Set22K
r_static
r_void
id|Set22K
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|state
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
(paren
id|state
ques
c_cond
id|SAA7146_GPIO_OUTHI
suffix:colon
id|SAA7146_GPIO_OUTLO
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Diseqc functions only for TT Budget card */
multiline_comment|/* taken from the Skyvision DVB driver by&n;   Ralph Metzler &lt;rjkm@metzlerbros.de&gt; */
DECL|function|DiseqcSendBit
r_static
r_void
id|DiseqcSendBit
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|data
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTHI
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|data
ques
c_cond
l_int|500
suffix:colon
l_int|1000
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|data
ques
c_cond
l_int|1000
suffix:colon
l_int|500
)paren
suffix:semicolon
)brace
DECL|function|DiseqcSendByte
r_static
r_void
id|DiseqcSendByte
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|data
)paren
(brace
r_int
id|i
comma
id|par
op_assign
l_int|1
comma
id|d
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|d
op_assign
(paren
id|data
op_rshift
id|i
)paren
op_amp
l_int|1
suffix:semicolon
id|par
op_xor_assign
id|d
suffix:semicolon
id|DiseqcSendBit
c_func
(paren
id|budget
comma
id|d
)paren
suffix:semicolon
)brace
id|DiseqcSendBit
c_func
(paren
id|budget
comma
id|par
)paren
suffix:semicolon
)brace
DECL|function|SendDiSEqCMsg
r_static
r_int
id|SendDiSEqCMsg
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|len
comma
id|u8
op_star
id|msg
comma
r_int
r_int
id|burst
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|16
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
id|len
suffix:semicolon
id|i
op_increment
)paren
id|DiseqcSendByte
c_func
(paren
id|budget
comma
id|msg
(braket
id|i
)braket
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|burst
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|burst
)paren
id|DiseqcSendByte
c_func
(paren
id|budget
comma
l_int|0xff
)paren
suffix:semicolon
r_else
(brace
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTHI
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|12500
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *   Routines for the Fujitsu Siemens Activy budget card&n; *   22 kHz tone and DiSEqC are handled by the frontend.&n; *   Voltage must be set here.&n; */
DECL|function|SetVoltage_Activy
r_static
r_int
id|SetVoltage_Activy
(paren
r_struct
id|budget
op_star
id|budget
comma
id|fe_sec_voltage_t
id|voltage
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
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
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|2
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEC_VOLTAGE_18
suffix:colon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|2
comma
id|SAA7146_GPIO_OUTHI
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|siemens_budget_set_voltage
r_static
r_int
id|siemens_budget_set_voltage
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
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
r_return
id|SetVoltage_Activy
(paren
id|budget
comma
id|voltage
)paren
suffix:semicolon
)brace
DECL|function|budget_set_tone
r_static
r_int
id|budget_set_tone
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
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|tone
)paren
(brace
r_case
id|SEC_TONE_ON
suffix:colon
id|Set22K
(paren
id|budget
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEC_TONE_OFF
suffix:colon
id|Set22K
(paren
id|budget
comma
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_diseqc_send_master_cmd
r_static
r_int
id|budget_diseqc_send_master_cmd
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
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|SendDiSEqCMsg
(paren
id|budget
comma
id|cmd-&gt;msg_len
comma
id|cmd-&gt;msg
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_diseqc_send_burst
r_static
r_int
id|budget_diseqc_send_burst
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_sec_mini_cmd_t
id|minicmd
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|SendDiSEqCMsg
(paren
id|budget
comma
l_int|0
comma
l_int|NULL
comma
id|minicmd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alps_bsrv2_pll_set
r_static
r_int
id|alps_bsrv2_pll_set
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
id|params
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|pwr
op_assign
l_int|0
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
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
id|buf
comma
dot
id|len
op_assign
r_sizeof
(paren
id|buf
)paren
)brace
suffix:semicolon
id|u32
id|div
op_assign
(paren
id|params-&gt;frequency
op_plus
l_int|479500
)paren
op_div
l_int|125
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
OG
l_int|2000000
)paren
id|pwr
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OG
l_int|1800000
)paren
id|pwr
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OG
l_int|1600000
)paren
id|pwr
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OG
l_int|1200000
)paren
id|pwr
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
op_ge
l_int|1100000
)paren
id|pwr
op_assign
l_int|1
suffix:semicolon
r_else
id|pwr
op_assign
l_int|2
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
op_amp
l_int|0x18000
)paren
op_rshift
l_int|10
)paren
op_or
l_int|0x95
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
(paren
id|pwr
op_lshift
l_int|6
)paren
op_or
l_int|0x30
suffix:semicolon
singleline_comment|// NOTE: since we&squot;re using a prescaler of 2, we set the
singleline_comment|// divisor frequency to 62.5kHz and divide by 125 above
r_if
c_cond
(paren
id|i2c_transfer
(paren
op_amp
id|budget-&gt;i2c_adap
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|alps_bsrv2_config
r_static
r_struct
id|ves1x93_config
id|alps_bsrv2_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x08
comma
dot
id|xin
op_assign
l_int|90100000UL
comma
dot
id|invert_pwm
op_assign
l_int|0
comma
dot
id|pll_set
op_assign
id|alps_bsrv2_pll_set
comma
)brace
suffix:semicolon
DECL|variable|alps_bsru6_inittab
r_static
id|u8
id|alps_bsru6_inittab
(braket
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x15
comma
l_int|0x02
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x7d
comma
multiline_comment|/* F22FR = 0x7d, F22 = f_VCO / 128 / 0x7d = 22 kHz */
l_int|0x05
comma
l_int|0x35
comma
multiline_comment|/* I2CT = 0, SCLT = 1, SDAT = 1 */
l_int|0x06
comma
l_int|0x40
comma
multiline_comment|/* DAC not used, set to high impendance mode */
l_int|0x07
comma
l_int|0x00
comma
multiline_comment|/* DAC LSB */
l_int|0x08
comma
l_int|0x40
comma
multiline_comment|/* DiSEqC off, LNB power on OP2/LOCK pin on */
l_int|0x09
comma
l_int|0x00
comma
multiline_comment|/* FIFO */
l_int|0x0c
comma
l_int|0x51
comma
multiline_comment|/* OP1 ctl = Normal, OP1 val = 1 (LNB Power ON) */
l_int|0x0d
comma
l_int|0x82
comma
multiline_comment|/* DC offset compensation = ON, beta_agc1 = 2 */
l_int|0x0e
comma
l_int|0x23
comma
multiline_comment|/* alpha_tmg = 2, beta_tmg = 3 */
l_int|0x10
comma
l_int|0x3f
comma
singleline_comment|// AGC2  0x3d
l_int|0x11
comma
l_int|0x84
comma
l_int|0x12
comma
l_int|0xb5
comma
singleline_comment|// Lock detect: -64  Carrier freq detect:on
l_int|0x15
comma
l_int|0xc9
comma
singleline_comment|// lock detector threshold
l_int|0x16
comma
l_int|0x00
comma
l_int|0x17
comma
l_int|0x00
comma
l_int|0x18
comma
l_int|0x00
comma
l_int|0x19
comma
l_int|0x00
comma
l_int|0x1a
comma
l_int|0x00
comma
l_int|0x1f
comma
l_int|0x50
comma
l_int|0x20
comma
l_int|0x00
comma
l_int|0x21
comma
l_int|0x00
comma
l_int|0x22
comma
l_int|0x00
comma
l_int|0x23
comma
l_int|0x00
comma
l_int|0x28
comma
l_int|0x00
comma
singleline_comment|// out imp: normal  out type: parallel FEC mode:0
l_int|0x29
comma
l_int|0x1e
comma
singleline_comment|// 1/2 threshold
l_int|0x2a
comma
l_int|0x14
comma
singleline_comment|// 2/3 threshold
l_int|0x2b
comma
l_int|0x0f
comma
singleline_comment|// 3/4 threshold
l_int|0x2c
comma
l_int|0x09
comma
singleline_comment|// 5/6 threshold
l_int|0x2d
comma
l_int|0x05
comma
singleline_comment|// 7/8 threshold
l_int|0x2e
comma
l_int|0x01
comma
l_int|0x31
comma
l_int|0x1f
comma
singleline_comment|// test all FECs
l_int|0x32
comma
l_int|0x19
comma
singleline_comment|// viterbi and synchro search
l_int|0x33
comma
l_int|0xfc
comma
singleline_comment|// rs control
l_int|0x34
comma
l_int|0x93
comma
singleline_comment|// error control
l_int|0x0f
comma
l_int|0x52
comma
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
DECL|function|alps_bsru6_set_symbol_rate
r_static
r_int
id|alps_bsru6_set_symbol_rate
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
id|srate
comma
id|u32
id|ratio
)paren
(brace
id|u8
id|aclk
op_assign
l_int|0
suffix:semicolon
id|u8
id|bclk
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|srate
OL
l_int|1500000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x47
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|srate
OL
l_int|3000000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x4b
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|srate
OL
l_int|7000000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x4f
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|srate
OL
l_int|14000000
)paren
(brace
id|aclk
op_assign
l_int|0xb7
suffix:semicolon
id|bclk
op_assign
l_int|0x53
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|srate
OL
l_int|30000000
)paren
(brace
id|aclk
op_assign
l_int|0xb6
suffix:semicolon
id|bclk
op_assign
l_int|0x53
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|srate
OL
l_int|45000000
)paren
(brace
id|aclk
op_assign
l_int|0xb4
suffix:semicolon
id|bclk
op_assign
l_int|0x51
suffix:semicolon
)brace
id|stv0299_writereg
(paren
id|fe
comma
l_int|0x13
comma
id|aclk
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|fe
comma
l_int|0x14
comma
id|bclk
)paren
suffix:semicolon
id|stv0299_writereg
(paren
id|fe
comma
l_int|0x1f
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
id|stv0299_writereg
(paren
id|fe
comma
l_int|0x20
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
id|stv0299_writereg
(paren
id|fe
comma
l_int|0x21
comma
(paren
id|ratio
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alps_bsru6_pll_set
r_static
r_int
id|alps_bsru6_pll_set
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
id|params
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|data
(braket
l_int|4
)braket
suffix:semicolon
id|u32
id|div
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
r_sizeof
(paren
id|data
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|params-&gt;frequency
OL
l_int|950000
)paren
op_logical_or
(paren
id|params-&gt;frequency
OG
l_int|2150000
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|div
op_assign
(paren
id|params-&gt;frequency
op_plus
(paren
l_int|125
op_minus
l_int|1
)paren
)paren
op_div
l_int|125
suffix:semicolon
singleline_comment|// round correctly
id|data
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
id|data
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|data
(braket
l_int|2
)braket
op_assign
l_int|0x80
op_or
(paren
(paren
id|div
op_amp
l_int|0x18000
)paren
op_rshift
l_int|10
)paren
op_or
l_int|4
suffix:semicolon
id|data
(braket
l_int|3
)braket
op_assign
l_int|0xC4
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
OG
l_int|1530000
)paren
id|data
(braket
l_int|3
)braket
op_assign
l_int|0xc0
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
(paren
op_amp
id|budget-&gt;i2c_adap
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|alps_bsru6_config
r_static
r_struct
id|stv0299_config
id|alps_bsru6_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x68
comma
dot
id|inittab
op_assign
id|alps_bsru6_inittab
comma
dot
id|mclk
op_assign
l_int|88000000UL
comma
dot
id|invert
op_assign
l_int|1
comma
dot
id|enhanced_tuning
op_assign
l_int|0
comma
dot
id|skip_reinit
op_assign
l_int|0
comma
dot
id|lock_output
op_assign
id|STV0229_LOCKOUTPUT_1
comma
dot
id|volt13_op0_op1
op_assign
id|STV0299_VOLT13_OP1
comma
dot
id|min_delay_ms
op_assign
l_int|100
comma
dot
id|set_symbol_rate
op_assign
id|alps_bsru6_set_symbol_rate
comma
dot
id|pll_set
op_assign
id|alps_bsru6_pll_set
comma
)brace
suffix:semicolon
DECL|function|alps_tdbe2_pll_set
r_static
r_int
id|alps_tdbe2_pll_set
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
id|params
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u32
id|div
suffix:semicolon
id|u8
id|data
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
l_int|0x62
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
r_sizeof
(paren
id|data
)paren
)brace
suffix:semicolon
id|div
op_assign
(paren
id|params-&gt;frequency
op_plus
l_int|35937500
op_plus
l_int|31250
)paren
op_div
l_int|62500
suffix:semicolon
id|data
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
id|data
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|data
(braket
l_int|2
)braket
op_assign
l_int|0x85
op_or
(paren
(paren
id|div
op_rshift
l_int|10
)paren
op_amp
l_int|0x60
)paren
suffix:semicolon
id|data
(braket
l_int|3
)braket
op_assign
(paren
id|params-&gt;frequency
OL
l_int|174000000
ques
c_cond
l_int|0x88
suffix:colon
id|params-&gt;frequency
OL
l_int|470000000
ques
c_cond
l_int|0x84
suffix:colon
l_int|0x81
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
(paren
op_amp
id|budget-&gt;i2c_adap
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|alps_tdbe2_config
r_static
r_struct
id|ves1820_config
id|alps_tdbe2_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x09
comma
dot
id|xin
op_assign
l_int|57840000UL
comma
dot
id|invert
op_assign
l_int|1
comma
dot
id|selagc
op_assign
id|VES1820_SELAGC_SIGNAMPERR
comma
dot
id|pll_set
op_assign
id|alps_tdbe2_pll_set
comma
)brace
suffix:semicolon
DECL|function|grundig_29504_401_pll_set
r_static
r_int
id|grundig_29504_401_pll_set
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
id|params
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u32
id|div
suffix:semicolon
id|u8
id|cfg
comma
id|cpump
comma
id|band_select
suffix:semicolon
id|u8
id|data
(braket
l_int|4
)braket
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
r_sizeof
(paren
id|data
)paren
)brace
suffix:semicolon
id|div
op_assign
(paren
l_int|36125000
op_plus
id|params-&gt;frequency
)paren
op_div
l_int|166666
suffix:semicolon
id|cfg
op_assign
l_int|0x88
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|175000000
)paren
id|cpump
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|390000000
)paren
id|cpump
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|470000000
)paren
id|cpump
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|750000000
)paren
id|cpump
op_assign
l_int|1
suffix:semicolon
r_else
id|cpump
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|175000000
)paren
id|band_select
op_assign
l_int|0x0e
suffix:semicolon
r_else
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|470000000
)paren
id|band_select
op_assign
l_int|0x05
suffix:semicolon
r_else
id|band_select
op_assign
l_int|0x03
suffix:semicolon
id|data
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
id|data
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|data
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
id|data
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
r_if
c_cond
(paren
id|i2c_transfer
(paren
op_amp
id|budget-&gt;i2c_adap
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|grundig_29504_401_config
r_static
r_struct
id|l64781_config
id|grundig_29504_401_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x55
comma
dot
id|pll_set
op_assign
id|grundig_29504_401_pll_set
comma
)brace
suffix:semicolon
DECL|function|grundig_29504_451_pll_set
r_static
r_int
id|grundig_29504_451_pll_set
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
id|params
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u32
id|div
suffix:semicolon
id|u8
id|data
(braket
l_int|4
)braket
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
r_sizeof
(paren
id|data
)paren
)brace
suffix:semicolon
id|div
op_assign
id|params-&gt;frequency
op_div
l_int|125
suffix:semicolon
id|data
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
id|data
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|data
(braket
l_int|2
)braket
op_assign
l_int|0x8e
suffix:semicolon
id|data
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
(paren
op_amp
id|budget-&gt;i2c_adap
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|grundig_29504_451_config
r_static
r_struct
id|tda8083_config
id|grundig_29504_451_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x68
comma
dot
id|pll_set
op_assign
id|grundig_29504_451_pll_set
comma
)brace
suffix:semicolon
DECL|function|read_pwm
r_static
id|u8
id|read_pwm
c_func
(paren
r_struct
id|budget
op_star
id|budget
)paren
(brace
id|u8
id|b
op_assign
l_int|0xff
suffix:semicolon
id|u8
id|pwm
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
l_int|0x50
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
op_amp
id|b
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
l_int|0x50
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
op_amp
id|pwm
comma
dot
id|len
op_assign
l_int|1
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i2c_transfer
c_func
(paren
op_amp
id|budget-&gt;i2c_adap
comma
id|msg
comma
l_int|2
)paren
op_ne
l_int|2
)paren
op_logical_or
(paren
id|pwm
op_eq
l_int|0xff
)paren
)paren
id|pwm
op_assign
l_int|0x48
suffix:semicolon
r_return
id|pwm
suffix:semicolon
)brace
DECL|function|frontend_init
r_static
r_void
id|frontend_init
c_func
(paren
r_struct
id|budget
op_star
id|budget
)paren
(brace
r_switch
c_cond
(paren
id|budget-&gt;dev-&gt;pci-&gt;subsystem_device
)paren
(brace
r_case
l_int|0x1003
suffix:colon
singleline_comment|// Hauppauge/TT Nova budget (stv0299/ALPS BSRU6(tsa5059) OR ves1893/ALPS BSRV2(sp5659))
r_case
l_int|0x1013
suffix:colon
singleline_comment|// try the ALPS BSRV2 first of all
id|budget-&gt;dvb_frontend
op_assign
id|ves1x93_attach
c_func
(paren
op_amp
id|alps_bsrv2_config
comma
op_amp
id|budget-&gt;i2c_adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
(brace
id|budget-&gt;dvb_frontend-&gt;ops-&gt;diseqc_send_master_cmd
op_assign
id|budget_diseqc_send_master_cmd
suffix:semicolon
id|budget-&gt;dvb_frontend-&gt;ops-&gt;diseqc_send_burst
op_assign
id|budget_diseqc_send_burst
suffix:semicolon
id|budget-&gt;dvb_frontend-&gt;ops-&gt;set_tone
op_assign
id|budget_set_tone
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|// try the ALPS BSRU6 now
id|budget-&gt;dvb_frontend
op_assign
id|stv0299_attach
c_func
(paren
op_amp
id|alps_bsru6_config
comma
op_amp
id|budget-&gt;i2c_adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
(brace
id|budget-&gt;dvb_frontend-&gt;ops-&gt;diseqc_send_master_cmd
op_assign
id|budget_diseqc_send_master_cmd
suffix:semicolon
id|budget-&gt;dvb_frontend-&gt;ops-&gt;diseqc_send_burst
op_assign
id|budget_diseqc_send_burst
suffix:semicolon
id|budget-&gt;dvb_frontend-&gt;ops-&gt;set_tone
op_assign
id|budget_set_tone
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x1004
suffix:colon
singleline_comment|// Hauppauge/TT DVB-C budget (ves1820/ALPS TDBE2(sp5659))
id|budget-&gt;dvb_frontend
op_assign
id|ves1820_attach
c_func
(paren
op_amp
id|alps_tdbe2_config
comma
op_amp
id|budget-&gt;i2c_adap
comma
id|read_pwm
c_func
(paren
id|budget
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
r_break
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1005
suffix:colon
singleline_comment|// Hauppauge/TT Nova-T budget (L64781/Grundig 29504-401(tsa5060))
id|budget-&gt;dvb_frontend
op_assign
id|l64781_attach
c_func
(paren
op_amp
id|grundig_29504_401_config
comma
op_amp
id|budget-&gt;i2c_adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
r_break
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4f60
suffix:colon
singleline_comment|// Fujitsu Siemens Activy Budget-S PCI rev AL (stv0299/ALPS BSRU6(tsa5059))
id|budget-&gt;dvb_frontend
op_assign
id|stv0299_attach
c_func
(paren
op_amp
id|alps_bsru6_config
comma
op_amp
id|budget-&gt;i2c_adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
(brace
id|budget-&gt;dvb_frontend-&gt;ops-&gt;set_voltage
op_assign
id|siemens_budget_set_voltage
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x4f61
suffix:colon
singleline_comment|// Fujitsu Siemens Activy Budget-S PCI rev GR (tda8083/Grundig 29504-451(tsa5522))
id|budget-&gt;dvb_frontend
op_assign
id|tda8083_attach
c_func
(paren
op_amp
id|grundig_29504_451_config
comma
op_amp
id|budget-&gt;i2c_adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
(brace
id|budget-&gt;dvb_frontend-&gt;ops-&gt;set_voltage
op_assign
id|siemens_budget_set_voltage
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;budget: A frontend driver was not found for device %04x/%04x subsystem %04x/%04x&bslash;n&quot;
comma
id|budget-&gt;dev-&gt;pci-&gt;vendor
comma
id|budget-&gt;dev-&gt;pci-&gt;device
comma
id|budget-&gt;dev-&gt;pci-&gt;subsystem_vendor
comma
id|budget-&gt;dev-&gt;pci-&gt;subsystem_device
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dvb_register_frontend
c_func
(paren
id|budget-&gt;dvb_adapter
comma
id|budget-&gt;dvb_frontend
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;budget: Frontend registration failed!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend-&gt;ops-&gt;release
)paren
id|budget-&gt;dvb_frontend-&gt;ops
op_member_access_from_pointer
id|release
c_func
(paren
id|budget-&gt;dvb_frontend
)paren
suffix:semicolon
id|budget-&gt;dvb_frontend
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
DECL|function|budget_attach
r_static
r_int
id|budget_attach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_pci_extension_data
op_star
id|info
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|budget
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|budget
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|budget
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;dev:%p, info:%p, budget:%p&bslash;n&quot;
comma
id|dev
comma
id|info
comma
id|budget
)paren
suffix:semicolon
id|dev-&gt;ext_priv
op_assign
id|budget
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ttpci_budget_init
(paren
id|budget
comma
id|dev
comma
id|info
comma
id|THIS_MODULE
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;==&gt; failed&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
(paren
id|budget
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|budget-&gt;dvb_adapter-&gt;priv
op_assign
id|budget
suffix:semicolon
id|frontend_init
c_func
(paren
id|budget
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_detach
r_static
r_int
id|budget_detach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|budget-&gt;dvb_frontend
)paren
id|dvb_unregister_frontend
c_func
(paren
id|budget-&gt;dvb_frontend
)paren
suffix:semicolon
id|err
op_assign
id|ttpci_budget_deinit
(paren
id|budget
)paren
suffix:semicolon
id|kfree
(paren
id|budget
)paren
suffix:semicolon
id|dev-&gt;ext_priv
op_assign
l_int|NULL
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|ttbs
comma
l_string|&quot;TT-Budget/WinTV-NOVA-S  PCI&quot;
comma
id|BUDGET_TT
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|ttbc
comma
l_string|&quot;TT-Budget/WinTV-NOVA-C  PCI&quot;
comma
id|BUDGET_TT
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|ttbt
comma
l_string|&quot;TT-Budget/WinTV-NOVA-T  PCI&quot;
comma
id|BUDGET_TT
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|satel
comma
l_string|&quot;SATELCO Multimedia PCI&quot;
comma
id|BUDGET_TT_HW_DISEQC
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|fsacs0
comma
l_string|&quot;Fujitsu Siemens Activy Budget-S PCI (rev GR/grundig frontend)&quot;
comma
id|BUDGET_FS_ACTIVY
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|fsacs1
comma
l_string|&quot;Fujitsu Siemens Activy Budget-S PCI (rev AL/alps frontend)&quot;
comma
id|BUDGET_FS_ACTIVY
)paren
suffix:semicolon
DECL|variable|pci_tbl
r_static
r_struct
id|pci_device_id
id|pci_tbl
(braket
)braket
op_assign
(brace
id|MAKE_EXTENSION_PCI
c_func
(paren
id|ttbs
comma
l_int|0x13c2
comma
l_int|0x1003
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|ttbc
comma
l_int|0x13c2
comma
l_int|0x1004
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|ttbt
comma
l_int|0x13c2
comma
l_int|0x1005
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|satel
comma
l_int|0x13c2
comma
l_int|0x1013
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|fsacs1
comma
l_int|0x1131
comma
l_int|0x4f60
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|fsacs0
comma
l_int|0x1131
comma
l_int|0x4f61
)paren
comma
(brace
dot
id|vendor
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|pci_tbl
)paren
suffix:semicolon
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;budget dvb&bslash;0&quot;
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|pci_tbl
op_assign
id|pci_tbl
comma
dot
id|attach
op_assign
id|budget_attach
comma
dot
id|detach
op_assign
id|budget_detach
comma
dot
id|irq_mask
op_assign
id|MASK_10
comma
dot
id|irq_func
op_assign
id|ttpci_budget_irq10_handler
comma
)brace
suffix:semicolon
DECL|function|budget_init
r_static
r_int
id|__init
id|budget_init
c_func
(paren
r_void
)paren
(brace
r_return
id|saa7146_register_extension
c_func
(paren
op_amp
id|budget_extension
)paren
suffix:semicolon
)brace
DECL|function|budget_exit
r_static
r_void
id|__exit
id|budget_exit
c_func
(paren
r_void
)paren
(brace
id|saa7146_unregister_extension
c_func
(paren
op_amp
id|budget_extension
)paren
suffix:semicolon
)brace
DECL|variable|budget_init
id|module_init
c_func
(paren
id|budget_init
)paren
suffix:semicolon
DECL|variable|budget_exit
id|module_exit
c_func
(paren
id|budget_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler, Marcus Metzler, Michael Hunold, others&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;driver for the SAA7146 based so-called &quot;
l_string|&quot;budget PCI DVB cards by Siemens, Technotrend, Hauppauge&quot;
)paren
suffix:semicolon
eof
