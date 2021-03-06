multiline_comment|/*&n; * b2c2-common.c - common methods for the B2C2/Technisat SkyStar2 PCI DVB card and&n; *                 for the B2C2/Technisat Sky/Cable/AirStar USB devices&n; *                 based on the FlexCopII/FlexCopIII by B2C2, Inc.&n; *&n; * Copyright (C) 2003  Vadim Catana, skystar@moldova.cc&n; *&n; * FIX: DISEQC Tone Burst in flexcop_diseqc_ioctl()&n; * FIX: FULL soft DiSEqC for skystar2 (FlexCopII rev 130) VP310 equipped&n; *     Vincenzo Di Massa, hawk.it at tiscalinet.it&n; *&n; * Converted to Linux coding style&n; * Misc reorganization, polishing, restyling&n; *     Roberto Ragusa, r.ragusa at libero.it&n; *&n; * Added hardware filtering support,&n; *     Niklas Peinecke, peinecke at gdv.uni-hannover.de&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#include &quot;stv0299.h&quot;
macro_line|#include &quot;mt352.h&quot;
macro_line|#include &quot;mt312.h&quot;
DECL|function|samsung_tbmu24112_set_symbol_rate
r_static
r_int
id|samsung_tbmu24112_set_symbol_rate
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
DECL|function|samsung_tbmu24112_pll_set
r_static
r_int
id|samsung_tbmu24112_pll_set
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
id|u8
id|buf
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
singleline_comment|//&t;struct adapter* adapter = (struct adapter*) fe-&gt;dvb-&gt;priv;
id|div
op_assign
id|params-&gt;frequency
op_div
l_int|125
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
l_int|0x84
suffix:semicolon
singleline_comment|// 0xC4
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x08
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|1500000
)paren
id|buf
(braket
l_int|3
)braket
op_or_assign
l_int|0x10
suffix:semicolon
singleline_comment|//&t;if (i2c_transfer (&amp;adapter-&gt;i2c_adap, &amp;msg, 1) != 1) return -EIO;
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|samsung_tbmu24112_inittab
r_static
id|u8
id|samsung_tbmu24112_inittab
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
l_int|0x30
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x7D
comma
l_int|0x05
comma
l_int|0x35
comma
l_int|0x06
comma
l_int|0x02
comma
l_int|0x07
comma
l_int|0x00
comma
l_int|0x08
comma
l_int|0xC3
comma
l_int|0x0C
comma
l_int|0x00
comma
l_int|0x0D
comma
l_int|0x81
comma
l_int|0x0E
comma
l_int|0x23
comma
l_int|0x0F
comma
l_int|0x12
comma
l_int|0x10
comma
l_int|0x7E
comma
l_int|0x11
comma
l_int|0x84
comma
l_int|0x12
comma
l_int|0xB9
comma
l_int|0x13
comma
l_int|0x88
comma
l_int|0x14
comma
l_int|0x89
comma
l_int|0x15
comma
l_int|0xC9
comma
l_int|0x16
comma
l_int|0x00
comma
l_int|0x17
comma
l_int|0x5C
comma
l_int|0x18
comma
l_int|0x00
comma
l_int|0x19
comma
l_int|0x00
comma
l_int|0x1A
comma
l_int|0x00
comma
l_int|0x1C
comma
l_int|0x00
comma
l_int|0x1D
comma
l_int|0x00
comma
l_int|0x1E
comma
l_int|0x00
comma
l_int|0x1F
comma
l_int|0x3A
comma
l_int|0x20
comma
l_int|0x2E
comma
l_int|0x21
comma
l_int|0x80
comma
l_int|0x22
comma
l_int|0xFF
comma
l_int|0x23
comma
l_int|0xC1
comma
l_int|0x28
comma
l_int|0x00
comma
l_int|0x29
comma
l_int|0x1E
comma
l_int|0x2A
comma
l_int|0x14
comma
l_int|0x2B
comma
l_int|0x0F
comma
l_int|0x2C
comma
l_int|0x09
comma
l_int|0x2D
comma
l_int|0x05
comma
l_int|0x31
comma
l_int|0x1F
comma
l_int|0x32
comma
l_int|0x19
comma
l_int|0x33
comma
l_int|0xFE
comma
l_int|0x34
comma
l_int|0x93
comma
l_int|0xff
comma
l_int|0xff
comma
)brace
suffix:semicolon
DECL|variable|samsung_tbmu24112_config
r_static
r_struct
id|stv0299_config
id|samsung_tbmu24112_config
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
id|samsung_tbmu24112_inittab
comma
dot
id|mclk
op_assign
l_int|88000000UL
comma
dot
id|invert
op_assign
l_int|0
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
id|STV0229_LOCKOUTPUT_LK
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
id|samsung_tbmu24112_set_symbol_rate
comma
dot
id|pll_set
op_assign
id|samsung_tbmu24112_pll_set
comma
)brace
suffix:semicolon
DECL|function|samsung_tdtc9251dh0_demod_init
r_static
r_int
id|samsung_tdtc9251dh0_demod_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_static
id|u8
id|mt352_clock_config
(braket
)braket
op_assign
(brace
l_int|0x89
comma
l_int|0x10
comma
l_int|0x2d
)brace
suffix:semicolon
r_static
id|u8
id|mt352_reset
(braket
)braket
op_assign
(brace
l_int|0x50
comma
l_int|0x80
)brace
suffix:semicolon
r_static
id|u8
id|mt352_adc_ctl_1_cfg
(braket
)braket
op_assign
(brace
l_int|0x8E
comma
l_int|0x40
)brace
suffix:semicolon
r_static
id|u8
id|mt352_agc_cfg
(braket
)braket
op_assign
(brace
l_int|0x67
comma
l_int|0x28
comma
l_int|0xa1
)brace
suffix:semicolon
r_static
id|u8
id|mt352_capt_range_cfg
(braket
)braket
op_assign
(brace
l_int|0x75
comma
l_int|0x32
)brace
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_clock_config
comma
r_sizeof
(paren
id|mt352_clock_config
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_reset
comma
r_sizeof
(paren
id|mt352_reset
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_adc_ctl_1_cfg
comma
r_sizeof
(paren
id|mt352_adc_ctl_1_cfg
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_agc_cfg
comma
r_sizeof
(paren
id|mt352_agc_cfg
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_capt_range_cfg
comma
r_sizeof
(paren
id|mt352_capt_range_cfg
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|samsung_tdtc9251dh0_pll_set
r_static
r_int
id|samsung_tdtc9251dh0_pll_set
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
comma
id|u8
op_star
id|pllbuf
)paren
(brace
id|u32
id|div
suffix:semicolon
r_int
r_char
id|bs
op_assign
l_int|0
suffix:semicolon
DECL|macro|IF_FREQUENCYx6
mdefine_line|#define IF_FREQUENCYx6 217    /* 6 * 36.16666666667MHz */
id|div
op_assign
(paren
(paren
(paren
id|params-&gt;frequency
op_plus
l_int|83333
)paren
op_star
l_int|3
)paren
op_div
l_int|500000
)paren
op_plus
id|IF_FREQUENCYx6
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
op_ge
l_int|48000000
op_logical_and
id|params-&gt;frequency
op_le
l_int|154000000
)paren
id|bs
op_assign
l_int|0x09
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
op_ge
l_int|161000000
op_logical_and
id|params-&gt;frequency
op_le
l_int|439000000
)paren
id|bs
op_assign
l_int|0x0a
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
op_ge
l_int|447000000
op_logical_and
id|params-&gt;frequency
op_le
l_int|863000000
)paren
id|bs
op_assign
l_int|0x08
suffix:semicolon
id|pllbuf
(braket
l_int|0
)braket
op_assign
l_int|0xc2
suffix:semicolon
singleline_comment|// Note: non-linux standard PLL i2c address
id|pllbuf
(braket
l_int|1
)braket
op_assign
id|div
op_rshift
l_int|8
suffix:semicolon
id|pllbuf
(braket
l_int|2
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|pllbuf
(braket
l_int|3
)braket
op_assign
l_int|0xcc
suffix:semicolon
id|pllbuf
(braket
l_int|4
)braket
op_assign
id|bs
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|samsung_tdtc9251dh0_config
r_static
r_struct
id|mt352_config
id|samsung_tdtc9251dh0_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x0f
comma
dot
id|demod_init
op_assign
id|samsung_tdtc9251dh0_demod_init
comma
dot
id|pll_set
op_assign
id|samsung_tdtc9251dh0_pll_set
comma
)brace
suffix:semicolon
DECL|function|skystar23_samsung_tbdu18132_pll_set
r_static
r_int
id|skystar23_samsung_tbdu18132_pll_set
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
id|u8
id|buf
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
singleline_comment|//&t;struct adapter* adapter = (struct adapter*) fe-&gt;dvb-&gt;priv;
id|div
op_assign
(paren
id|params-&gt;frequency
op_plus
(paren
l_int|125
op_div
l_int|2
)paren
)paren
op_div
l_int|125
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
(paren
id|div
op_rshift
l_int|0
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x84
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
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x80
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;frequency
OL
l_int|1550000
)paren
id|buf
(braket
l_int|3
)braket
op_or_assign
l_int|0x02
suffix:semicolon
singleline_comment|//if (i2c_transfer (&amp;adapter-&gt;i2c_adap, &amp;msg, 1) != 1) return -EIO;
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|skystar23_samsung_tbdu18132_config
r_static
r_struct
id|mt312_config
id|skystar23_samsung_tbdu18132_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x0e
comma
dot
id|pll_set
op_assign
id|skystar23_samsung_tbdu18132_pll_set
comma
)brace
suffix:semicolon
eof
