multiline_comment|/*&n;    Driver for Spase SP8870 demodulator&n;&n;    Copyright (C) 1999 Juergen Peitz&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#ifndef SP8870_H
DECL|macro|SP8870_H
mdefine_line|#define SP8870_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
DECL|struct|sp8870_config
r_struct
id|sp8870_config
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
multiline_comment|/* request firmware for device */
DECL|member|request_firmware
r_int
(paren
op_star
id|request_firmware
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_const
r_struct
id|firmware
op_star
op_star
id|fw
comma
r_char
op_star
id|name
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|sp8870_attach
c_func
(paren
r_const
r_struct
id|sp8870_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// SP8870_H
eof
