multiline_comment|/*&n;    Driver for STV0297 demodulator&n;&n;    Copyright (C) 2003-2004 Dennis Noermann &lt;dennis.noermann@noernet.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef STV0297_H
DECL|macro|STV0297_H
mdefine_line|#define STV0297_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
DECL|struct|stv0297_config
r_struct
id|stv0297_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
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
id|stv0297_attach
c_func
(paren
r_const
r_struct
id|stv0297_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
comma
r_int
id|pwm
)paren
suffix:semicolon
r_extern
r_int
id|stv0297_enable_plli2c
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// STV0297_H
eof
