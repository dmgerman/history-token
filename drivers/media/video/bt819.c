multiline_comment|/* &n; *  bt819 - BT819A VideoStream Decoder (Rockwell Part)&n; *&n; * Copyright (C) 1999 Mike Bernson &lt;mike@mlb.org&gt;&n; * Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n; *&n; * Modifications for LML33/DC10plus unified driver&n; * Copyright (C) 2000 Serguei Miridonov &lt;mirsev@cicese.mx&gt;&n; *  &n; * Changes by Ronald Bultje &lt;rbultje@ronald.bitfreak.net&gt;&n; *    - moved over to linux&gt;=2.4.x i2c protocol (9/9/2002)&n; *&n; * This code was modify/ported from the saa7111 driver written&n; * by Dave Perks.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
l_string|&quot;Brooktree-819 video decoder driver&quot;
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
macro_line|#include &lt;linux/video_decoder.h&gt;
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
DECL|struct|bt819
r_struct
id|bt819
(brace
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
DECL|member|norm
r_int
id|norm
suffix:semicolon
DECL|member|input
r_int
id|input
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
DECL|struct|timing
r_struct
id|timing
(brace
DECL|member|hactive
r_int
id|hactive
suffix:semicolon
DECL|member|hdelay
r_int
id|hdelay
suffix:semicolon
DECL|member|vactive
r_int
id|vactive
suffix:semicolon
DECL|member|vdelay
r_int
id|vdelay
suffix:semicolon
DECL|member|hscale
r_int
id|hscale
suffix:semicolon
DECL|member|vscale
r_int
id|vscale
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for values, see the bt819 datasheet */
DECL|variable|timing_data
r_static
r_struct
id|timing
id|timing_data
(braket
)braket
op_assign
(brace
(brace
l_int|864
op_minus
l_int|24
comma
l_int|20
comma
l_int|625
op_minus
l_int|2
comma
l_int|1
comma
l_int|0x0504
comma
l_int|0x0000
)brace
comma
(brace
l_int|858
op_minus
l_int|24
comma
l_int|20
comma
l_int|525
op_minus
l_int|2
comma
l_int|1
comma
l_int|0x00f8
comma
l_int|0x0000
)brace
comma
)brace
suffix:semicolon
DECL|macro|I2C_BT819
mdefine_line|#define   I2C_BT819        0x8a
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_inline
r_int
DECL|function|bt819_write
id|bt819_write
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
id|bt819
op_star
id|decoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|decoder-&gt;reg
(braket
id|reg
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
DECL|function|bt819_setbit
id|bt819_setbit
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
id|bt819
op_star
id|decoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
id|bt819_write
c_func
(paren
id|client
comma
id|reg
comma
(paren
id|decoder
op_member_access_from_pointer
id|reg
(braket
id|reg
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
r_int
DECL|function|bt819_write_block
id|bt819_write_block
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_const
id|u8
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
id|u8
id|reg
suffix:semicolon
multiline_comment|/* the bt819 has an autoincrement function, use it if&n;&t; * the adapter understands raw I2C */
r_if
c_cond
(paren
id|i2c_check_functionality
c_func
(paren
id|client-&gt;adapter
comma
id|I2C_FUNC_I2C
)paren
)paren
(brace
multiline_comment|/* do raw I2C, not smbus compatible */
r_struct
id|bt819
op_star
id|decoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_struct
id|i2c_msg
id|msg
suffix:semicolon
id|u8
id|block_data
(braket
l_int|32
)braket
suffix:semicolon
id|msg.addr
op_assign
id|client-&gt;addr
suffix:semicolon
id|msg.flags
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
l_int|2
)paren
(brace
id|msg.buf
op_assign
(paren
r_char
op_star
)paren
id|block_data
suffix:semicolon
id|msg.len
op_assign
l_int|0
suffix:semicolon
id|block_data
(braket
id|msg.len
op_increment
)braket
op_assign
id|reg
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_do
(brace
id|block_data
(braket
id|msg.len
op_increment
)braket
op_assign
id|decoder-&gt;reg
(braket
id|reg
op_increment
)braket
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
op_ge
l_int|2
op_logical_and
id|data
(braket
l_int|0
)braket
op_eq
id|reg
op_logical_and
id|msg.len
OL
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c_transfer
c_func
(paren
id|client-&gt;adapter
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* do some slow I2C emulation kind of thing */
r_while
c_loop
(paren
id|len
op_ge
l_int|2
)paren
(brace
id|reg
op_assign
op_star
id|data
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|bt819_write
c_func
(paren
id|client
comma
id|reg
comma
op_star
id|data
op_increment
)paren
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|bt819_read
id|bt819_read
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|reg
)paren
(brace
r_return
id|i2c_smbus_read_byte_data
c_func
(paren
id|client
comma
id|reg
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|bt819_init
id|bt819_init
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|bt819
op_star
id|decoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_static
r_int
r_char
id|init
(braket
)braket
op_assign
(brace
singleline_comment|//0x1f, 0x00,     /* Reset */
l_int|0x01
comma
l_int|0x59
comma
multiline_comment|/* 0x01 input format */
l_int|0x02
comma
l_int|0x00
comma
multiline_comment|/* 0x02 temporal decimation */
l_int|0x03
comma
l_int|0x12
comma
multiline_comment|/* 0x03 Cropping msb */
l_int|0x04
comma
l_int|0x16
comma
multiline_comment|/* 0x04 Vertical Delay, lsb */
l_int|0x05
comma
l_int|0xe0
comma
multiline_comment|/* 0x05 Vertical Active lsb */
l_int|0x06
comma
l_int|0x80
comma
multiline_comment|/* 0x06 Horizontal Delay lsb */
l_int|0x07
comma
l_int|0xd0
comma
multiline_comment|/* 0x07 Horizontal Active lsb */
l_int|0x08
comma
l_int|0x00
comma
multiline_comment|/* 0x08 Horizontal Scaling msb */
l_int|0x09
comma
l_int|0xf8
comma
multiline_comment|/* 0x09 Horizontal Scaling lsb */
l_int|0x0a
comma
l_int|0x00
comma
multiline_comment|/* 0x0a Brightness control */
l_int|0x0b
comma
l_int|0x30
comma
multiline_comment|/* 0x0b Miscellaneous control */
l_int|0x0c
comma
l_int|0xd8
comma
multiline_comment|/* 0x0c Luma Gain lsb */
l_int|0x0d
comma
l_int|0xfe
comma
multiline_comment|/* 0x0d Chroma Gain (U) lsb */
l_int|0x0e
comma
l_int|0xb4
comma
multiline_comment|/* 0x0e Chroma Gain (V) msb */
l_int|0x0f
comma
l_int|0x00
comma
multiline_comment|/* 0x0f Hue control */
l_int|0x12
comma
l_int|0x04
comma
multiline_comment|/* 0x12 Output Format */
l_int|0x13
comma
l_int|0x20
comma
multiline_comment|/* 0x13 Vertial Scaling msb 0x00&n;&t;&t;&t;&t;&t;   chroma comb OFF, line drop scaling, interlace scaling&n;&t;&t;&t;&t;&t;   BUG? Why does turning the chroma comb on fuck up color?&n;&t;&t;&t;&t;&t;   Bug in the bt819 stepping on my board?&n;&t;&t;&t;&t;&t;*/
l_int|0x14
comma
l_int|0x00
comma
multiline_comment|/* 0x14 Vertial Scaling lsb */
l_int|0x16
comma
l_int|0x07
comma
multiline_comment|/* 0x16 Video Timing Polarity &n;&t;&t;&t;&t;&t;   ACTIVE=active low&n;&t;&t;&t;&t;&t;   FIELD: high=odd, &n;&t;&t;&t;&t;&t;   vreset=active high,&n;&t;&t;&t;&t;&t;   hreset=active high */
l_int|0x18
comma
l_int|0x68
comma
multiline_comment|/* 0x18 AGC Delay */
l_int|0x19
comma
l_int|0x5d
comma
multiline_comment|/* 0x19 Burst Gate Delay */
l_int|0x1a
comma
l_int|0x80
comma
multiline_comment|/* 0x1a ADC Interface */
)brace
suffix:semicolon
r_struct
id|timing
op_star
id|timing
op_assign
op_amp
id|timing_data
(braket
id|decoder-&gt;norm
)braket
suffix:semicolon
id|init
(braket
l_int|0x03
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
(paren
(paren
(paren
id|timing-&gt;vdelay
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|6
)paren
op_or
(paren
(paren
(paren
id|timing
op_member_access_from_pointer
id|vactive
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
(paren
id|timing-&gt;hdelay
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|timing
op_member_access_from_pointer
id|hactive
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
suffix:semicolon
id|init
(braket
l_int|0x04
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
id|timing-&gt;vdelay
op_amp
l_int|0xff
suffix:semicolon
id|init
(braket
l_int|0x05
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
id|timing-&gt;vactive
op_amp
l_int|0xff
suffix:semicolon
id|init
(braket
l_int|0x06
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
id|timing-&gt;hdelay
op_amp
l_int|0xff
suffix:semicolon
id|init
(braket
l_int|0x07
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
id|timing-&gt;hactive
op_amp
l_int|0xff
suffix:semicolon
id|init
(braket
l_int|0x08
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
id|timing-&gt;hscale
op_rshift
l_int|8
suffix:semicolon
id|init
(braket
l_int|0x09
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
id|timing-&gt;hscale
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* 0x15 in array is address 0x19 */
id|init
(braket
l_int|0x15
op_star
l_int|2
op_minus
l_int|1
)braket
op_assign
(paren
id|decoder-&gt;norm
op_eq
l_int|0
)paren
ques
c_cond
l_int|115
suffix:colon
l_int|93
suffix:semicolon
multiline_comment|/* Chroma burst delay */
multiline_comment|/* reset */
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x1f
comma
l_int|0x00
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* init */
r_return
id|bt819_write_block
c_func
(paren
id|client
comma
id|init
comma
r_sizeof
(paren
id|init
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_int
DECL|function|bt819_command
id|bt819_command
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
r_int
id|temp
suffix:semicolon
r_struct
id|bt819
op_star
id|decoder
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|decoder-&gt;initialized
)paren
(brace
singleline_comment|// First call to bt819_init could be
id|bt819_init
c_func
(paren
id|client
)paren
suffix:semicolon
singleline_comment|// without #FRST = 0
id|decoder-&gt;initialized
op_assign
l_int|1
suffix:semicolon
)brace
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
id|bt819_init
c_func
(paren
id|client
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DECODER_GET_CAPABILITIES
suffix:colon
(brace
r_struct
id|video_decoder_capability
op_star
id|cap
op_assign
id|arg
suffix:semicolon
id|cap-&gt;flags
op_assign
id|VIDEO_DECODER_PAL
op_or
id|VIDEO_DECODER_NTSC
op_or
id|VIDEO_DECODER_AUTO
op_or
id|VIDEO_DECODER_CCIR
suffix:semicolon
id|cap-&gt;inputs
op_assign
l_int|8
suffix:semicolon
id|cap-&gt;outputs
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_GET_STATUS
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|res
suffix:semicolon
id|status
op_assign
id|bt819_read
c_func
(paren
id|client
comma
l_int|0x00
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x80
)paren
)paren
(brace
id|res
op_or_assign
id|DECODER_STATUS_GOOD
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|decoder-&gt;norm
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_NTSC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_PAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_case
id|VIDEO_MODE_AUTO
suffix:colon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x10
)paren
)paren
(brace
id|res
op_or_assign
id|DECODER_STATUS_PAL
suffix:semicolon
)brace
r_else
(brace
id|res
op_or_assign
id|DECODER_STATUS_NTSC
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|res
op_or_assign
id|DECODER_STATUS_COLOR
suffix:semicolon
op_star
id|iarg
op_assign
id|res
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: get status %x&bslash;n&quot;
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
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_NORM
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_struct
id|timing
op_star
id|timing
op_assign
l_int|NULL
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: set norm %x&bslash;n&quot;
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
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|5
comma
l_int|0
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x18
comma
l_int|0x68
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x19
comma
l_int|0x5d
)paren
suffix:semicolon
singleline_comment|//bt819_setbit(client, 0x1a,  5, 1);
id|timing
op_assign
op_amp
id|timing_data
(braket
id|VIDEO_MODE_NTSC
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|5
comma
l_int|1
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x18
comma
l_int|0x7f
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x19
comma
l_int|0x72
)paren
suffix:semicolon
singleline_comment|//bt819_setbit(client, 0x1a,  5, 0);
id|timing
op_assign
op_amp
id|timing_data
(braket
id|VIDEO_MODE_PAL
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_AUTO
suffix:colon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x01
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: unsupported norm %d&bslash;n&quot;
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timing
)paren
(brace
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x03
comma
(paren
(paren
(paren
id|timing-&gt;vdelay
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|6
)paren
op_or
(paren
(paren
(paren
id|timing-&gt;vactive
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
(paren
id|timing-&gt;hdelay
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|timing-&gt;hactive
op_rshift
l_int|8
)paren
op_amp
l_int|0x03
)paren
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x04
comma
id|timing-&gt;vdelay
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x05
comma
id|timing-&gt;vactive
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x06
comma
id|timing-&gt;hdelay
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x07
comma
id|timing-&gt;hactive
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x08
comma
(paren
id|timing-&gt;hscale
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x09
comma
id|timing-&gt;hscale
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
id|decoder-&gt;norm
op_assign
op_star
id|iarg
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_INPUT
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
l_string|&quot;%s: set input %x&bslash;n&quot;
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
r_if
c_cond
(paren
op_star
id|iarg
template_param
l_int|7
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;input
op_ne
op_star
id|iarg
)paren
(brace
id|decoder-&gt;input
op_assign
op_star
id|iarg
suffix:semicolon
multiline_comment|/* select mode */
r_if
c_cond
(paren
id|decoder-&gt;input
op_eq
l_int|0
)paren
(brace
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x0b
comma
l_int|6
comma
l_int|0
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x1a
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x0b
comma
l_int|6
comma
l_int|1
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x1a
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_OUTPUT
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
l_string|&quot;%s: set output %x&bslash;n&quot;
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
id|DECODER_ENABLE_OUTPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_int
id|enable
op_assign
(paren
op_star
id|iarg
op_ne
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: enable output %x&bslash;n&quot;
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
r_if
c_cond
(paren
id|decoder-&gt;enable
op_ne
id|enable
)paren
(brace
id|decoder-&gt;enable
op_assign
id|enable
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;enable
)paren
(brace
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x16
comma
l_int|7
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x16
comma
l_int|7
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_PICTURE
suffix:colon
(brace
r_struct
id|video_picture
op_star
id|pic
op_assign
id|arg
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: set picture brightness %d contrast %d colour %d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|pic-&gt;brightness
comma
id|pic-&gt;contrast
comma
id|pic-&gt;colour
)paren
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;bright
op_ne
id|pic-&gt;brightness
)paren
(brace
multiline_comment|/* We want -128 to 127 we get 0-65535 */
id|decoder-&gt;bright
op_assign
id|pic-&gt;brightness
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x0a
comma
(paren
id|decoder-&gt;bright
op_rshift
l_int|8
)paren
op_minus
l_int|128
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;contrast
op_ne
id|pic-&gt;contrast
)paren
(brace
multiline_comment|/* We want 0 to 511 we get 0-65535 */
id|decoder-&gt;contrast
op_assign
id|pic-&gt;contrast
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x0c
comma
(paren
id|decoder-&gt;contrast
op_rshift
l_int|7
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x0b
comma
l_int|2
comma
(paren
(paren
id|decoder-&gt;contrast
op_rshift
l_int|15
)paren
op_amp
l_int|0x01
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;sat
op_ne
id|pic-&gt;colour
)paren
(brace
multiline_comment|/* We want 0 to 511 we get 0-65535 */
id|decoder-&gt;sat
op_assign
id|pic-&gt;colour
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x0d
comma
(paren
id|decoder-&gt;sat
op_rshift
l_int|7
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x0b
comma
l_int|1
comma
(paren
(paren
id|decoder-&gt;sat
op_rshift
l_int|15
)paren
op_amp
l_int|0x01
)paren
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|decoder-&gt;sat
op_star
l_int|201
)paren
op_div
l_int|237
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x0e
comma
(paren
id|temp
op_rshift
l_int|7
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|bt819_setbit
c_func
(paren
id|client
comma
l_int|0x0b
comma
l_int|0
comma
(paren
id|temp
op_rshift
l_int|15
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;hue
op_ne
id|pic-&gt;hue
)paren
(brace
multiline_comment|/* We want -128 to 127 we get 0-65535 */
id|decoder-&gt;hue
op_assign
id|pic-&gt;hue
suffix:semicolon
id|bt819_write
c_func
(paren
id|client
comma
l_int|0x0f
comma
l_int|128
op_minus
(paren
id|decoder-&gt;hue
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
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
id|I2C_BT819
op_rshift
l_int|1
comma
id|I2C_CLIENT_END
comma
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
DECL|variable|i2c_driver_bt819
r_static
r_struct
id|i2c_driver
id|i2c_driver_bt819
suffix:semicolon
r_static
r_int
DECL|function|bt819_detect_client
id|bt819_detect_client
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
comma
id|id
suffix:semicolon
r_struct
id|bt819
op_star
id|decoder
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;saa7111.c: detecting bt819 client on address 0x%x&bslash;n&quot;
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
id|i2c_driver_bt819
suffix:semicolon
id|client-&gt;flags
op_assign
id|I2C_CLIENT_ALLOW_USE
suffix:semicolon
id|decoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|bt819
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|decoder
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
id|decoder
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|bt819
)paren
)paren
suffix:semicolon
id|decoder-&gt;norm
op_assign
id|VIDEO_MODE_NTSC
suffix:semicolon
id|decoder-&gt;input
op_assign
l_int|0
suffix:semicolon
id|decoder-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|decoder-&gt;bright
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;contrast
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;hue
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;sat
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;initialized
op_assign
l_int|0
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|decoder
)paren
suffix:semicolon
id|id
op_assign
id|bt819_read
c_func
(paren
id|client
comma
l_int|0x17
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|id
op_amp
l_int|0xf0
)paren
(brace
r_case
l_int|0x70
suffix:colon
id|strlcpy
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
l_string|&quot;bt819a&quot;
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
r_break
suffix:semicolon
r_case
l_int|0x60
suffix:colon
id|strlcpy
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
l_string|&quot;bt817a&quot;
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
r_break
suffix:semicolon
r_case
l_int|0x20
suffix:colon
id|strlcpy
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
l_string|&quot;bt815a&quot;
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
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;bt819: unknown chip version 0x%x (ver 0x%x)&bslash;n&quot;
comma
id|id
op_amp
l_int|0xf0
comma
id|id
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|decoder
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
id|decoder
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|i
op_assign
id|bt819_init
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s_attach: init status %d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s_attach: chip version 0x%x at address 0x%x&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|id
op_amp
l_int|0x0f
comma
id|client-&gt;addr
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|bt819_attach_adapter
id|bt819_attach_adapter
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
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
id|bt819_detect_client
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|bt819_detach_client
id|bt819_detach_client
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|bt819
op_star
id|decoder
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
id|decoder
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
DECL|variable|i2c_driver_bt819
r_static
r_struct
id|i2c_driver
id|i2c_driver_bt819
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
l_string|&quot;bt819&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_BT819
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|bt819_attach_adapter
comma
dot
id|detach_client
op_assign
id|bt819_detach_client
comma
dot
id|command
op_assign
id|bt819_command
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|bt819_init_module
id|bt819_init_module
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|i2c_driver_bt819
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|bt819_exit
id|bt819_exit
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|i2c_driver_bt819
)paren
suffix:semicolon
)brace
DECL|variable|bt819_init_module
id|module_init
c_func
(paren
id|bt819_init_module
)paren
suffix:semicolon
DECL|variable|bt819_exit
id|module_exit
c_func
(paren
id|bt819_exit
)paren
suffix:semicolon
eof
