multiline_comment|/*&n; * Copyright (C) 2001,2002,2003 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef I2C_ALGO_SIBYTE_H
DECL|macro|I2C_ALGO_SIBYTE_H
mdefine_line|#define I2C_ALGO_SIBYTE_H 1
macro_line|#include &lt;linux/i2c.h&gt;
DECL|struct|i2c_algo_sibyte_data
r_struct
id|i2c_algo_sibyte_data
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private data */
DECL|member|bus
r_int
id|bus
suffix:semicolon
multiline_comment|/* which bus */
DECL|member|reg_base
r_void
op_star
id|reg_base
suffix:semicolon
multiline_comment|/* CSR base */
)brace
suffix:semicolon
r_int
id|i2c_sibyte_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
comma
r_int
id|speed
)paren
suffix:semicolon
r_int
id|i2c_sibyte_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
macro_line|#endif /* I2C_ALGO_SIBYTE_H */
eof
