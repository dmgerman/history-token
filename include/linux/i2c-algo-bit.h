multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-algo-bit.h i2c driver algorithms for bit-shift adapters               */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-99 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-algo-bit.h,v 1.7 1999/12/21 23:45:58 frodo Exp $ */
macro_line|#ifndef I2C_ALGO_BIT_H
DECL|macro|I2C_ALGO_BIT_H
mdefine_line|#define I2C_ALGO_BIT_H 1
macro_line|#include &lt;linux/i2c.h&gt;
multiline_comment|/* --- Defines for bit-adapters ---------------------------------------&t;*/
multiline_comment|/*&n; * This struct contains the hw-dependent functions of bit-style adapters to &n; * manipulate the line states, and to init any hw-specific features. This is&n; * only used if you have more than one hw-type of adapter running. &n; */
DECL|struct|i2c_algo_bit_data
r_struct
id|i2c_algo_bit_data
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private data for lowlevel routines */
DECL|member|setsda
r_void
(paren
op_star
id|setsda
)paren
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
suffix:semicolon
DECL|member|setscl
r_void
(paren
op_star
id|setscl
)paren
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
suffix:semicolon
DECL|member|getsda
r_int
(paren
op_star
id|getsda
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|getscl
r_int
(paren
op_star
id|getscl
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* local settings */
DECL|member|udelay
r_int
id|udelay
suffix:semicolon
DECL|member|mdelay
r_int
id|mdelay
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|I2C_BIT_ADAP_MAX
mdefine_line|#define I2C_BIT_ADAP_MAX&t;16
r_int
id|i2c_bit_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
r_int
id|i2c_bit_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
macro_line|#endif /* I2C_ALGO_BIT_H */
eof
