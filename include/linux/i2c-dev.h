multiline_comment|/*&n;    i2c-dev.h - i2c-bus driver, char device interface&n;&n;    Copyright (C) 1995-97 Simon G. Vogl&n;    Copyright (C) 1998-99 Frodo Looijaard &lt;frodol@dds.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* $Id: i2c-dev.h,v 1.11 2002/07/07 15:42:47 mds Exp $ */
macro_line|#ifndef I2C_DEV_H
DECL|macro|I2C_DEV_H
mdefine_line|#define I2C_DEV_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
multiline_comment|/* Some IOCTL commands are defined in &lt;linux/i2c.h&gt; */
multiline_comment|/* Note: 10-bit addresses are NOT supported! */
multiline_comment|/* This is the structure as used in the I2C_SMBUS ioctl call */
DECL|struct|i2c_smbus_ioctl_data
r_struct
id|i2c_smbus_ioctl_data
(brace
DECL|member|read_write
r_char
id|read_write
suffix:semicolon
DECL|member|command
id|__u8
id|command
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|data
r_union
id|i2c_smbus_data
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
op_star
id|msgs
suffix:semicolon
multiline_comment|/* pointers to i2c_msgs */
DECL|member|nmsgs
r_int
id|nmsgs
suffix:semicolon
multiline_comment|/* number of i2c_msgs */
)brace
suffix:semicolon
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;sys/ioctl.h&gt;
DECL|function|i2c_smbus_access
r_static
r_inline
id|__s32
id|i2c_smbus_access
c_func
(paren
r_int
id|file
comma
r_char
id|read_write
comma
id|__u8
id|command
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
(brace
r_struct
id|i2c_smbus_ioctl_data
id|args
suffix:semicolon
id|args.read_write
op_assign
id|read_write
suffix:semicolon
id|args.command
op_assign
id|command
suffix:semicolon
id|args.size
op_assign
id|size
suffix:semicolon
id|args.data
op_assign
id|data
suffix:semicolon
r_return
id|ioctl
c_func
(paren
id|file
comma
id|I2C_SMBUS
comma
op_amp
id|args
)paren
suffix:semicolon
)brace
DECL|function|i2c_smbus_write_quick
r_static
r_inline
id|__s32
id|i2c_smbus_write_quick
c_func
(paren
r_int
id|file
comma
id|__u8
id|value
)paren
(brace
r_return
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|value
comma
l_int|0
comma
id|I2C_SMBUS_QUICK
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|i2c_smbus_read_byte
r_static
r_inline
id|__s32
id|i2c_smbus_read_byte
c_func
(paren
r_int
id|file
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_READ
comma
l_int|0
comma
id|I2C_SMBUS_BYTE
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0x0FF
op_amp
id|data.byte
suffix:semicolon
)brace
DECL|function|i2c_smbus_write_byte
r_static
r_inline
id|__s32
id|i2c_smbus_write_byte
c_func
(paren
r_int
id|file
comma
id|__u8
id|value
)paren
(brace
r_return
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|value
comma
id|I2C_SMBUS_BYTE
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|i2c_smbus_read_byte_data
r_static
r_inline
id|__s32
id|i2c_smbus_read_byte_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_READ
comma
id|command
comma
id|I2C_SMBUS_BYTE_DATA
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0x0FF
op_amp
id|data.byte
suffix:semicolon
)brace
DECL|function|i2c_smbus_write_byte_data
r_static
r_inline
id|__s32
id|i2c_smbus_write_byte_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u8
id|value
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
id|data.byte
op_assign
id|value
suffix:semicolon
r_return
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|command
comma
id|I2C_SMBUS_BYTE_DATA
comma
op_amp
id|data
)paren
suffix:semicolon
)brace
DECL|function|i2c_smbus_read_word_data
r_static
r_inline
id|__s32
id|i2c_smbus_read_word_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_READ
comma
id|command
comma
id|I2C_SMBUS_WORD_DATA
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0x0FFFF
op_amp
id|data.word
suffix:semicolon
)brace
DECL|function|i2c_smbus_write_word_data
r_static
r_inline
id|__s32
id|i2c_smbus_write_word_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u16
id|value
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
id|data.word
op_assign
id|value
suffix:semicolon
r_return
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|command
comma
id|I2C_SMBUS_WORD_DATA
comma
op_amp
id|data
)paren
suffix:semicolon
)brace
DECL|function|i2c_smbus_process_call
r_static
r_inline
id|__s32
id|i2c_smbus_process_call
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u16
id|value
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
id|data.word
op_assign
id|value
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|command
comma
id|I2C_SMBUS_PROC_CALL
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0x0FFFF
op_amp
id|data.word
suffix:semicolon
)brace
multiline_comment|/* Returns the number of read bytes */
DECL|function|i2c_smbus_read_block_data
r_static
r_inline
id|__s32
id|i2c_smbus_read_block_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u8
op_star
id|values
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_READ
comma
id|command
comma
id|I2C_SMBUS_BLOCK_DATA
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|data.block
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
id|values
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|data.block
(braket
id|i
)braket
suffix:semicolon
r_return
id|data.block
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
DECL|function|i2c_smbus_write_block_data
r_static
r_inline
id|__s32
id|i2c_smbus_write_block_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u8
id|length
comma
id|__u8
op_star
id|values
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|32
)paren
id|length
op_assign
l_int|32
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|length
suffix:semicolon
id|i
op_increment
)paren
id|data.block
(braket
id|i
)braket
op_assign
id|values
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|data.block
(braket
l_int|0
)braket
op_assign
id|length
suffix:semicolon
r_return
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|command
comma
id|I2C_SMBUS_BLOCK_DATA
comma
op_amp
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the number of read bytes */
DECL|function|i2c_smbus_read_i2c_block_data
r_static
r_inline
id|__s32
id|i2c_smbus_read_i2c_block_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u8
op_star
id|values
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_READ
comma
id|command
comma
id|I2C_SMBUS_I2C_BLOCK_DATA
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|data.block
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
id|values
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|data.block
(braket
id|i
)braket
suffix:semicolon
r_return
id|data.block
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
DECL|function|i2c_smbus_write_i2c_block_data
r_static
r_inline
id|__s32
id|i2c_smbus_write_i2c_block_data
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u8
id|length
comma
id|__u8
op_star
id|values
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|32
)paren
id|length
op_assign
l_int|32
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|length
suffix:semicolon
id|i
op_increment
)paren
id|data.block
(braket
id|i
)braket
op_assign
id|values
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|data.block
(braket
l_int|0
)braket
op_assign
id|length
suffix:semicolon
r_return
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|command
comma
id|I2C_SMBUS_I2C_BLOCK_DATA
comma
op_amp
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the number of read bytes */
DECL|function|i2c_smbus_block_process_call
r_static
r_inline
id|__s32
id|i2c_smbus_block_process_call
c_func
(paren
r_int
id|file
comma
id|__u8
id|command
comma
id|__u8
id|length
comma
id|__u8
op_star
id|values
)paren
(brace
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|32
)paren
id|length
op_assign
l_int|32
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|length
suffix:semicolon
id|i
op_increment
)paren
id|data.block
(braket
id|i
)braket
op_assign
id|values
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|data.block
(braket
l_int|0
)braket
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_access
c_func
(paren
id|file
comma
id|I2C_SMBUS_WRITE
comma
id|command
comma
id|I2C_SMBUS_BLOCK_PROC_CALL
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|data.block
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
id|values
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|data.block
(braket
id|i
)braket
suffix:semicolon
r_return
id|data.block
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
macro_line|#endif /* ndef __KERNEL__ */
macro_line|#endif
eof
