multiline_comment|/*&n;    Frontend-driver for TwinHan DST Frontend&n;&n;    Copyright (C) 2003 Jamie Honan&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#ifndef DST_H
DECL|macro|DST_H
mdefine_line|#define DST_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;bt878.h&quot;
DECL|struct|dst_config
r_struct
id|dst_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|dst_attach
c_func
(paren
r_const
r_struct
id|dst_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
comma
r_struct
id|bt878
op_star
id|bt
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DST_H
eof
