multiline_comment|/* &n; * bt856 - BT856A Digital Video Encoder (Rockwell Part)&n; *&n; * Copyright (C) 1999 Mike Bernson &lt;mike@mlb.org&gt;&n; * Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n; *&n; * Modifications for LML33/DC10plus unified driver&n; * Copyright (C) 2000 Serguei Miridonov &lt;mirsev@cicese.mx&gt;&n; *&n; * This code was modify/ported from the saa7111 driver written&n; * by Dave Perks.&n; *&n; * Changes by Ronald Bultje &lt;rbultje@ronald.bitfreak.net&gt;&n; *   - moved over to linux&gt;=2.4.x i2c protocol (9/9/2002)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Brooktree-856A video encoder driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mike Bernson &amp; Dave Perks&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-dev.h&gt;
DECL|macro|I2C_NAME
mdefine_line|#define I2C_NAME(s) (s)-&gt;name
macro_line|#include &lt;linux/video_encoder.h&gt;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debug level (0-1)&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(num, format, args...) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (debug &gt;= num) &bslash;&n;&t;&t;&t;printk(format, ##args); &bslash;&n;&t;} while (0)
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|macro|REG_OFFSET
mdefine_line|#define REG_OFFSET  0xCE
DECL|struct|bt856
r_struct
id|bt856
(brace
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|norm
r_int
id|norm
suffix:semicolon
DECL|member|enable
r_int
id|enable
suffix:semicolon
DECL|member|bright
r_int
id|bright
suffix:semicolon
DECL|member|contrast
r_int
id|contrast
suffix:semicolon
DECL|member|hue
r_int
id|hue
suffix:semicolon
DECL|member|sat
r_int
id|sat
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|I2C_BT856
mdefine_line|#define   I2C_BT856        0x88
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_inline
r_int
DECL|function|bt856_write
id|bt856_write
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
comma
id|u8
id|value
)paren
(brace
r_struct
id|bt856
op_star
id|encoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|encoder-&gt;reg
(braket
id|reg
op_minus
id|REG_OFFSET
)braket
op_assign
id|value
suffix:semicolon
r_return
id|i2c_smbus_write_byte_data
c_func
(paren
id|client
comma
id|reg
comma
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|bt856_setbit
id|bt856_setbit
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
comma
id|u8
id|bit
comma
id|u8
id|value
)paren
(brace
r_struct
id|bt856
op_star
id|encoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
id|bt856_write
c_func
(paren
id|client
comma
id|reg
comma
(paren
id|encoder
op_member_access_from_pointer
id|reg
(braket
id|reg
op_minus
id|REG_OFFSET
)braket
op_amp
op_complement
(paren
l_int|1
op_lshift
id|bit
)paren
)paren
op_or
(paren
id|value
ques
c_cond
(paren
l_int|1
op_lshift
id|bit
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|bt856_dump
id|bt856_dump
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|bt856
op_star
id|encoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: register dump:&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0xd6
suffix:semicolon
id|i
op_le
l_int|0xde
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|encoder-&gt;reg
(braket
id|i
op_minus
id|REG_OFFSET
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_int
DECL|function|bt856_command
id|bt856_command
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|bt856
op_star
id|encoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* This is just for testing!!! */
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;bt856: init&bslash;n&quot;
)paren
suffix:semicolon
id|bt856_write
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|0x18
)paren
suffix:semicolon
id|bt856_write
c_func
(paren
id|client
comma
l_int|0xda
comma
l_int|0
)paren
suffix:semicolon
id|bt856_write
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|//bt856_setbit(client, 0xdc, 6, 0);
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|4
comma
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|encoder-&gt;norm
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|2
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|2
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
op_ne
l_int|0
)paren
id|bt856_dump
c_func
(paren
id|client
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ENCODER_GET_CAPABILITIES
suffix:colon
(brace
r_struct
id|video_encoder_capability
op_star
id|cap
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: get capabilities&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
suffix:semicolon
id|cap-&gt;flags
op_assign
id|VIDEO_ENCODER_PAL
op_or
id|VIDEO_ENCODER_NTSC
op_or
id|VIDEO_ENCODER_CCIR
suffix:semicolon
id|cap-&gt;inputs
op_assign
l_int|2
suffix:semicolon
id|cap-&gt;outputs
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_NORM
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: set norm %d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
op_star
id|iarg
)paren
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|iarg
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|2
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|2
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xda
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|//bt856_setbit(client, 0xda, 0, 1);
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|encoder-&gt;norm
op_assign
op_star
id|iarg
suffix:semicolon
r_if
c_cond
(paren
id|debug
op_ne
l_int|0
)paren
id|bt856_dump
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_INPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: set input %d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
op_star
id|iarg
)paren
suffix:semicolon
multiline_comment|/* We only have video bus.&n;&t;&t; * iarg = 0: input is from bt819&n;&t;&t; * iarg = 1: input is from ZR36060 */
r_switch
c_cond
(paren
op_star
id|iarg
)paren
(brace
r_case
l_int|0
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|6
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|6
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
singleline_comment|// Color bar
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|4
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debug
op_ne
l_int|0
)paren
id|bt856_dump
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_OUTPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: set output %d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
op_star
id|iarg
)paren
suffix:semicolon
multiline_comment|/* not much choice of outputs */
r_if
c_cond
(paren
op_star
id|iarg
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_ENABLE_OUTPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
id|encoder-&gt;enable
op_assign
op_logical_neg
op_logical_neg
op_star
id|iarg
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: enable output %d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|encoder-&gt;enable
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/*&n; * Generic i2c probe&n; * concerning the addresses: i2c wants 7 bit (without the r/w bit), so &squot;&gt;&gt;1&squot;&n; */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
id|I2C_BT856
op_rshift
l_int|1
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|normal_i2c_range
r_static
r_int
r_int
id|normal_i2c_range
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|probe
r_static
r_int
r_int
id|probe
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|probe_range
r_static
r_int
r_int
id|probe_range
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|ignore
r_static
r_int
r_int
id|ignore
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|ignore_range
r_static
r_int
r_int
id|ignore_range
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|force
r_static
r_int
r_int
id|force
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|addr_data
r_static
r_struct
id|i2c_client_address_data
id|addr_data
op_assign
(brace
dot
id|normal_i2c
op_assign
id|normal_i2c
comma
dot
id|normal_i2c_range
op_assign
id|normal_i2c_range
comma
dot
id|probe
op_assign
id|probe
comma
dot
id|probe_range
op_assign
id|probe_range
comma
dot
id|ignore
op_assign
id|ignore
comma
dot
id|ignore_range
op_assign
id|ignore_range
comma
dot
id|force
op_assign
id|force
)brace
suffix:semicolon
DECL|variable|i2c_driver_bt856
r_static
r_struct
id|i2c_driver
id|i2c_driver_bt856
suffix:semicolon
r_static
r_int
DECL|function|bt856_detect_client
id|bt856_detect_client
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|address
comma
r_int
id|kind
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_struct
id|bt856
op_star
id|encoder
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;bt856.c: detecting bt856 client on address 0x%x&bslash;n&quot;
comma
id|address
op_lshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Check if the adapter supports the needed features */
r_if
c_cond
(paren
op_logical_neg
id|i2c_check_functionality
c_func
(paren
id|adapter
comma
id|I2C_FUNC_SMBUS_BYTE_DATA
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|client
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|client
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|client-&gt;addr
op_assign
id|address
suffix:semicolon
id|client-&gt;adapter
op_assign
id|adapter
suffix:semicolon
id|client-&gt;driver
op_assign
op_amp
id|i2c_driver_bt856
suffix:semicolon
id|client-&gt;flags
op_assign
id|I2C_CLIENT_ALLOW_USE
suffix:semicolon
id|strlcpy
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
l_string|&quot;bt856&quot;
comma
r_sizeof
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
)paren
suffix:semicolon
id|encoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|bt856
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|encoder
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|encoder
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|bt856
)paren
)paren
suffix:semicolon
id|encoder-&gt;norm
op_assign
id|VIDEO_MODE_NTSC
suffix:semicolon
id|encoder-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|encoder
)paren
suffix:semicolon
id|i
op_assign
id|i2c_attach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|encoder
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|bt856_write
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|0x18
)paren
suffix:semicolon
id|bt856_write
c_func
(paren
id|client
comma
l_int|0xda
comma
l_int|0
)paren
suffix:semicolon
id|bt856_write
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
singleline_comment|//bt856_setbit(client, 0xdc, 6, 0);
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|4
comma
l_int|1
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|encoder-&gt;norm
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|2
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|2
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xdc
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|bt856_setbit
c_func
(paren
id|client
comma
l_int|0xde
comma
l_int|3
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
op_ne
l_int|0
)paren
id|bt856_dump
c_func
(paren
id|client
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s_attach: at address 0x%x&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|client-&gt;addr
op_lshift
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|bt856_attach_adapter
id|bt856_attach_adapter
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;bt856.c: starting probe for adapter %s (0x%x)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|adapter
)paren
comma
id|adapter-&gt;id
)paren
suffix:semicolon
r_return
id|i2c_probe
c_func
(paren
id|adapter
comma
op_amp
id|addr_data
comma
op_amp
id|bt856_detect_client
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|bt856_detach_client
id|bt856_detach_client
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|bt856
op_star
id|encoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|encoder
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|variable|i2c_driver_bt856
r_static
r_struct
id|i2c_driver
id|i2c_driver_bt856
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;bt856&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_BT856
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|bt856_attach_adapter
comma
dot
id|detach_client
op_assign
id|bt856_detach_client
comma
dot
id|command
op_assign
id|bt856_command
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|bt856_init
id|bt856_init
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|i2c_driver_bt856
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|bt856_exit
id|bt856_exit
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|i2c_driver_bt856
)paren
suffix:semicolon
)brace
DECL|variable|bt856_init
id|module_init
c_func
(paren
id|bt856_init
)paren
suffix:semicolon
DECL|variable|bt856_exit
id|module_exit
c_func
(paren
id|bt856_exit
)paren
suffix:semicolon
eof
