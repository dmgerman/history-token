multiline_comment|/*&n;    VES1820  - Single Chip Cable Channel Receiver driver module&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef VES1820_H
DECL|macro|VES1820_H
mdefine_line|#define VES1820_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
DECL|macro|VES1820_SELAGC_PWM
mdefine_line|#define VES1820_SELAGC_PWM 0
DECL|macro|VES1820_SELAGC_SIGNAMPERR
mdefine_line|#define VES1820_SELAGC_SIGNAMPERR 1
DECL|struct|ves1820_config
r_struct
id|ves1820_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* value of XIN to use */
DECL|member|xin
id|u32
id|xin
suffix:semicolon
multiline_comment|/* does inversion need inverted? */
DECL|member|invert
id|u8
id|invert
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SELAGC control */
DECL|member|selagc
id|u8
id|selagc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PLL maintenance */
DECL|member|pll_init
r_int
(paren
op_star
id|pll_init
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
DECL|member|pll_set
r_int
(paren
op_star
id|pll_set
)paren
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
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|ves1820_attach
c_func
(paren
r_const
r_struct
id|ves1820_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
comma
id|u8
id|pwm
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// VES1820_H
eof
