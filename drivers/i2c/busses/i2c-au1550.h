multiline_comment|/*&n; * Copyright (C) 2004 Embedded Edge, LLC &lt;dan@embeddededge.com&gt;&n; * 2.6 port by Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef I2C_AU1550_H
DECL|macro|I2C_AU1550_H
mdefine_line|#define I2C_AU1550_H
DECL|struct|i2c_au1550_data
r_struct
id|i2c_au1550_data
(brace
DECL|member|psc_base
id|u32
id|psc_base
suffix:semicolon
DECL|member|xfer_timeout
r_int
id|xfer_timeout
suffix:semicolon
DECL|member|ack_timeout
r_int
id|ack_timeout
suffix:semicolon
)brace
suffix:semicolon
r_int
id|i2c_au1550_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
r_int
id|i2c_au1550_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
macro_line|#endif /* I2C_AU1550_H */
eof
