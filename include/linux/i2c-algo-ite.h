multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-algo-ite.h i2c driver algorithms for ITE IIC adapters                 */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-97 Simon G. Vogl&n;                   1998-99 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* Modifications by MontaVista Software, 2001&n;   Changes made to support the ITE IIC peripheral */
macro_line|#ifndef I2C_ALGO_ITE_H
DECL|macro|I2C_ALGO_ITE_H
mdefine_line|#define I2C_ALGO_ITE_H 1
macro_line|#include &lt;linux/i2c.h&gt;
multiline_comment|/* Example of a sequential read request:&n;&t;struct i2c_iic_msg s_msg; &n;&n;&t;s_msg.addr=device_address;&n;&t;s_msg.len=length;&n;&t;s_msg.buf=buffer;&n;&t;s_msg.waddr=word_address;&n;&t;ioctl(file,I2C_SREAD, &amp;s_msg);&n; */
DECL|macro|I2C_SREAD
mdefine_line|#define I2C_SREAD&t;0x780&t;/* SREAD ioctl command */
DECL|struct|i2c_iic_msg
r_struct
id|i2c_iic_msg
(brace
DECL|member|addr
id|__u16
id|addr
suffix:semicolon
multiline_comment|/* device address */
DECL|member|waddr
id|__u16
id|waddr
suffix:semicolon
multiline_comment|/* word address */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* msg length */
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* pointer to msg data */
)brace
suffix:semicolon
DECL|struct|i2c_algo_iic_data
r_struct
id|i2c_algo_iic_data
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private data for lolevel routines&t;*/
DECL|member|setiic
r_void
(paren
op_star
id|setiic
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
DECL|member|getiic
r_int
(paren
op_star
id|getiic
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
r_int
id|i2c_iic_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
r_int
id|i2c_iic_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
macro_line|#endif /* I2C_ALGO_ITE_H */
eof
