multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* adap-pcf.h i2c driver algorithms for PCF8584 adapters                     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-97 Simon G. Vogl&n;                   1998-99 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-algo-pcf.h,v 1.7 2000/02/27 23:02:45 frodo Exp $ */
macro_line|#ifndef I2C_ALGO_PCF_H
DECL|macro|I2C_ALGO_PCF_H
mdefine_line|#define I2C_ALGO_PCF_H 1
multiline_comment|/* --- Defines for pcf-adapters ---------------------------------------&t;*/
macro_line|#include &lt;linux/i2c.h&gt;
DECL|struct|i2c_algo_pcf_data
r_struct
id|i2c_algo_pcf_data
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private data for lolevel routines&t;*/
DECL|member|setpcf
r_void
(paren
op_star
id|setpcf
)paren
(paren
r_void
op_star
id|data
comma
r_int
id|ctl
comma
r_int
id|val
)paren
suffix:semicolon
DECL|member|getpcf
r_int
(paren
op_star
id|getpcf
)paren
(paren
r_void
op_star
id|data
comma
r_int
id|ctl
)paren
suffix:semicolon
DECL|member|getown
r_int
(paren
op_star
id|getown
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|getclock
r_int
(paren
op_star
id|getclock
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|waitforpin
r_void
(paren
op_star
id|waitforpin
)paren
(paren
r_void
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
DECL|macro|I2C_PCF_ADAP_MAX
mdefine_line|#define I2C_PCF_ADAP_MAX&t;16
r_int
id|i2c_pcf_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
r_int
id|i2c_pcf_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
macro_line|#endif /* I2C_ALGO_PCF_H */
eof
