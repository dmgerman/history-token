multiline_comment|/*&n;    i2c-dev.h - i2c-bus driver, char device interface&n;&n;    Copyright (C) 1995-97 Simon G. Vogl&n;    Copyright (C) 1998-99 Frodo Looijaard &lt;frodol@dds.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* $Id: i2c-dev.h,v 1.13 2003/01/21 08:08:16 kmalkki Exp $ */
macro_line|#ifndef _LINUX_I2C_DEV_H
DECL|macro|_LINUX_I2C_DEV_H
mdefine_line|#define _LINUX_I2C_DEV_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Some IOCTL commands are defined in &lt;linux/i2c.h&gt; */
multiline_comment|/* Note: 10-bit addresses are NOT supported! */
multiline_comment|/* This is the structure as used in the I2C_SMBUS ioctl call */
DECL|struct|i2c_smbus_ioctl_data
r_struct
id|i2c_smbus_ioctl_data
(brace
DECL|member|read_write
id|__u8
id|read_write
suffix:semicolon
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|data
r_union
id|i2c_smbus_data
id|__user
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is the structure as used in the I2C_RDWR ioctl call */
DECL|struct|i2c_rdwr_ioctl_data
r_struct
id|i2c_rdwr_ioctl_data
(brace
DECL|member|msgs
r_struct
id|i2c_msg
id|__user
op_star
id|msgs
suffix:semicolon
multiline_comment|/* pointers to i2c_msgs */
DECL|member|nmsgs
id|__u32
id|nmsgs
suffix:semicolon
multiline_comment|/* number of i2c_msgs */
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_I2C_DEV_H */
eof
