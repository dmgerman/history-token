multiline_comment|/*&n; *    Support for OR51132 (pcHDTV HD-3000) - VSB/QAM&n; *&n; *    Copyright (C) 2005 Kirk Lapray &lt;kirk_lapray@bigfoot.com&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n;*/
macro_line|#ifndef OR51132_H
DECL|macro|OR51132_H
mdefine_line|#define OR51132_H
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;linux/dvb/frontend.h&gt;
DECL|struct|or51132_config
r_struct
id|or51132_config
(brace
multiline_comment|/* The demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
DECL|member|pll_address
id|u8
id|pll_address
suffix:semicolon
DECL|member|pll_desc
r_struct
id|dvb_pll_desc
op_star
id|pll_desc
suffix:semicolon
multiline_comment|/* Need to set device param for start_dma */
DECL|member|set_ts_params
r_int
(paren
op_star
id|set_ts_params
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|is_punctured
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|or51132_attach
c_func
(paren
r_const
r_struct
id|or51132_config
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
singleline_comment|// OR51132_H
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
