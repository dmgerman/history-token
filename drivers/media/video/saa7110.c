multiline_comment|/*&n;    saa7110 - Philips SAA7110(A) video decoder driver&n;&n;    Copyright (C) 1998 Pauline Middelink &lt;middelin@polyware.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/i2c-old.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &quot;linux/video_decoder.h&quot;
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x...)&t;&t;&t;/* remove when no long debugging */
DECL|macro|SAA7110_MAX_INPUT
mdefine_line|#define SAA7110_MAX_INPUT&t;9&t;/* 6 CVBS, 3 SVHS */
DECL|macro|SAA7110_MAX_OUTPUT
mdefine_line|#define SAA7110_MAX_OUTPUT&t;0&t;/* its a decoder only */
DECL|macro|I2C_SAA7110
mdefine_line|#define&t;I2C_SAA7110&t;&t;0x9C&t;/* or 0x9E */
DECL|macro|I2C_DELAY
mdefine_line|#define&t;I2C_DELAY&t;&t;10&t;/* 10 us or 100khz */
DECL|struct|saa7110
r_struct
id|saa7110
(brace
DECL|member|bus
r_struct
id|i2c_bus
op_star
id|bus
suffix:semicolon
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|36
)braket
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
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* I2C support functions&t;&t;&t;&t;&t;&t;   */
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
DECL|function|saa7110_write
r_int
id|saa7110_write
c_func
(paren
r_struct
id|saa7110
op_star
id|decoder
comma
r_int
r_char
id|subaddr
comma
r_int
r_char
id|data
)paren
(brace
r_int
id|ack
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
id|decoder-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
id|subaddr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
id|data
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|decoder-&gt;reg
(braket
id|subaddr
)braket
op_assign
id|data
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
r_return
id|ack
suffix:semicolon
)brace
r_static
DECL|function|saa7110_write_block
r_int
id|saa7110_write_block
c_func
(paren
r_struct
id|saa7110
op_star
id|decoder
comma
r_int
r_const
r_char
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|subaddr
op_assign
op_star
id|data
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
id|decoder-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
op_star
id|data
comma
l_int|0
)paren
)paren
(brace
id|i2c_stop
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|decoder-&gt;reg
(braket
id|subaddr
op_increment
)braket
op_assign
op_star
id|data
op_increment
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|saa7110_read
r_int
id|saa7110_read
c_func
(paren
r_struct
id|saa7110
op_star
id|decoder
)paren
(brace
r_int
id|data
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
id|decoder-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|decoder-&gt;bus
comma
id|decoder-&gt;addr
op_or
l_int|1
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|data
op_assign
id|i2c_readbyte
c_func
(paren
id|decoder-&gt;bus
comma
l_int|1
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|decoder-&gt;bus
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* SAA7110 functions&t;&t;&t;&t;&t;&t;&t;   */
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
DECL|function|saa7110_selmux
r_int
id|saa7110_selmux
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
comma
r_int
id|chan
)paren
(brace
r_static
r_const
r_int
r_char
id|modes
(braket
l_int|9
)braket
(braket
l_int|8
)braket
op_assign
(brace
multiline_comment|/* mode 0 */
(brace
l_int|0x00
comma
l_int|0xD9
comma
l_int|0x17
comma
l_int|0x40
comma
l_int|0x03
comma
l_int|0x44
comma
l_int|0x75
comma
l_int|0x16
)brace
comma
multiline_comment|/* mode 1 */
(brace
l_int|0x00
comma
l_int|0xD8
comma
l_int|0x17
comma
l_int|0x40
comma
l_int|0x03
comma
l_int|0x44
comma
l_int|0x75
comma
l_int|0x16
)brace
comma
multiline_comment|/* mode 2 */
(brace
l_int|0x00
comma
l_int|0xBA
comma
l_int|0x07
comma
l_int|0x91
comma
l_int|0x03
comma
l_int|0x60
comma
l_int|0xB5
comma
l_int|0x05
)brace
comma
multiline_comment|/* mode 3 */
(brace
l_int|0x00
comma
l_int|0xB8
comma
l_int|0x07
comma
l_int|0x91
comma
l_int|0x03
comma
l_int|0x60
comma
l_int|0xB5
comma
l_int|0x05
)brace
comma
multiline_comment|/* mode 4 */
(brace
l_int|0x00
comma
l_int|0x7C
comma
l_int|0x07
comma
l_int|0xD2
comma
l_int|0x83
comma
l_int|0x60
comma
l_int|0xB5
comma
l_int|0x03
)brace
comma
multiline_comment|/* mode 5 */
(brace
l_int|0x00
comma
l_int|0x78
comma
l_int|0x07
comma
l_int|0xD2
comma
l_int|0x83
comma
l_int|0x60
comma
l_int|0xB5
comma
l_int|0x03
)brace
comma
multiline_comment|/* mode 6 */
(brace
l_int|0x80
comma
l_int|0x59
comma
l_int|0x17
comma
l_int|0x42
comma
l_int|0xA3
comma
l_int|0x44
comma
l_int|0x75
comma
l_int|0x12
)brace
comma
multiline_comment|/* mode 7 */
(brace
l_int|0x80
comma
l_int|0x9A
comma
l_int|0x17
comma
l_int|0xB1
comma
l_int|0x13
comma
l_int|0x60
comma
l_int|0xB5
comma
l_int|0x14
)brace
comma
multiline_comment|/* mode 8 */
(brace
l_int|0x80
comma
l_int|0x3C
comma
l_int|0x27
comma
l_int|0xC1
comma
l_int|0x23
comma
l_int|0x44
comma
l_int|0x75
comma
l_int|0x21
)brace
)brace
suffix:semicolon
r_struct
id|saa7110
op_star
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
r_const
r_int
r_char
op_star
id|ptr
op_assign
id|modes
(braket
id|chan
)braket
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x06
comma
id|ptr
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Luminance control&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x20
comma
id|ptr
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Analog Control #1&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x21
comma
id|ptr
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* Analog Control #2&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x22
comma
id|ptr
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* Mixer Control #1&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2C
comma
id|ptr
(braket
l_int|4
)braket
)paren
suffix:semicolon
multiline_comment|/* Mixer Control #2&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x30
comma
id|ptr
(braket
l_int|5
)braket
)paren
suffix:semicolon
multiline_comment|/* ADCs gain control&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x31
comma
id|ptr
(braket
l_int|6
)braket
)paren
suffix:semicolon
multiline_comment|/* Mixer Control #3&t;*/
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x21
comma
id|ptr
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* Analog Control #2&t;*/
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|determine_norm
r_int
id|determine_norm
c_func
(paren
r_struct
id|i2c_device
op_star
id|dev
)paren
(brace
r_struct
id|saa7110
op_star
id|decoder
op_assign
id|dev-&gt;data
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* mode changed, start automatic detection */
id|status
op_assign
id|saa7110_read
c_func
(paren
id|decoder
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x06
comma
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x20
)paren
(brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: norm=bw60&bslash;n&quot;
comma
id|dev-&gt;name
)paren
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2E
comma
l_int|0x81
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_NTSC
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: norm=bw50&bslash;n&quot;
comma
id|dev-&gt;name
)paren
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2E
comma
l_int|0x9A
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_PAL
suffix:semicolon
)brace
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x06
comma
l_int|0x00
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x20
)paren
(brace
multiline_comment|/* 60Hz */
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: norm=ntsc&bslash;n&quot;
comma
id|dev-&gt;name
)paren
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x06
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
l_int|0x2C
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2E
comma
l_int|0x81
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_NTSC
suffix:semicolon
)brace
multiline_comment|/* 50Hz -&gt; PAL/SECAM */
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x06
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2E
comma
l_int|0x9A
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
multiline_comment|/* pause 150 ms */
id|status
op_assign
id|saa7110_read
c_func
(paren
id|decoder
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x03
)paren
op_eq
l_int|0x01
)paren
(brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: norm=secam&bslash;n&quot;
comma
id|dev-&gt;name
)paren
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x07
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_SECAM
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: norm=pal&bslash;n&quot;
comma
id|dev-&gt;name
)paren
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_PAL
suffix:semicolon
)brace
r_static
DECL|function|saa7110_attach
r_int
id|saa7110_attach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_static
r_const
r_int
r_char
id|initseq
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0x4C
comma
l_int|0x3C
comma
l_int|0x0D
comma
l_int|0xEF
comma
l_int|0xBD
comma
l_int|0xF0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xF8
comma
l_int|0xF8
comma
l_int|0x60
comma
l_int|0x60
comma
l_int|0x00
comma
l_int|0x06
comma
l_int|0x18
comma
l_int|0x90
comma
l_int|0x00
comma
l_int|0x2C
comma
l_int|0x40
comma
l_int|0x46
comma
l_int|0x42
comma
l_int|0x1A
comma
l_int|0xFF
comma
l_int|0xDA
comma
l_int|0xF0
comma
l_int|0x8B
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xD9
comma
l_int|0x17
comma
l_int|0x40
comma
l_int|0x41
comma
l_int|0x80
comma
l_int|0x41
comma
l_int|0x80
comma
l_int|0x4F
comma
l_int|0xFE
comma
l_int|0x01
comma
l_int|0xCF
comma
l_int|0x0F
comma
l_int|0x03
comma
l_int|0x01
comma
l_int|0x81
comma
l_int|0x03
comma
l_int|0x40
comma
l_int|0x75
comma
l_int|0x01
comma
l_int|0x8C
comma
l_int|0x03
)brace
suffix:semicolon
r_struct
id|saa7110
op_star
id|decoder
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|device-&gt;data
op_assign
id|decoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|saa7110
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;data
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* clear our private data */
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
id|saa7110
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|device-&gt;name
comma
l_string|&quot;saa7110&quot;
)paren
suffix:semicolon
id|decoder-&gt;bus
op_assign
id|device-&gt;bus
suffix:semicolon
id|decoder-&gt;addr
op_assign
id|device-&gt;addr
suffix:semicolon
id|decoder-&gt;norm
op_assign
id|VIDEO_MODE_PAL
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
id|rv
op_assign
id|saa7110_write_block
c_func
(paren
id|decoder
comma
id|initseq
comma
r_sizeof
(paren
id|initseq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s_attach: init status %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|rv
)paren
suffix:semicolon
r_else
(brace
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x21
comma
l_int|0x16
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x04
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s_attach: chip version %x&bslash;n&quot;
comma
id|device-&gt;name
comma
id|saa7110_read
c_func
(paren
id|decoder
)paren
)paren
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x06
)paren
suffix:semicolon
)brace
multiline_comment|/* setup and implicit mode 0 select has been performed */
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|saa7110_detach
r_int
id|saa7110_detach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_struct
id|saa7110
op_star
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s_detach&bslash;n&quot;
comma
id|device-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* stop further output */
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0E
comma
l_int|0x00
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|device-&gt;data
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|saa7110_command
r_int
id|saa7110_command
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
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
id|saa7110
op_star
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
r_int
id|v
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DECODER_GET_CAPABILITIES
suffix:colon
(brace
r_struct
id|video_decoder_capability
op_star
id|dc
op_assign
id|arg
suffix:semicolon
id|dc-&gt;flags
op_assign
id|VIDEO_DECODER_PAL
op_or
id|VIDEO_DECODER_NTSC
op_or
id|VIDEO_DECODER_SECAM
op_or
id|VIDEO_DECODER_AUTO
op_or
id|VIDEO_DECODER_CCIR
suffix:semicolon
id|dc-&gt;inputs
op_assign
id|SAA7110_MAX_INPUT
suffix:semicolon
id|dc-&gt;outputs
op_assign
id|SAA7110_MAX_OUTPUT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_GET_STATUS
suffix:colon
(brace
r_struct
id|saa7110
op_star
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|i2c_read
c_func
(paren
id|device-&gt;bus
comma
id|device-&gt;addr
op_or
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x40
)paren
id|res
op_or_assign
id|DECODER_STATUS_GOOD
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x03
)paren
id|res
op_or_assign
id|DECODER_STATUS_COLOR
suffix:semicolon
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
r_case
id|VIDEO_MODE_SECAM
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_SECAM
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|res
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_NORM
suffix:colon
id|v
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;norm
op_ne
id|v
)paren
(brace
id|decoder-&gt;norm
op_assign
id|v
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x06
comma
l_int|0x00
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|v
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x06
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
l_int|0x2C
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x30
comma
l_int|0x81
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2A
comma
l_int|0xDF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x06
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2E
comma
l_int|0x9A
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_SECAM
suffix:colon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0D
comma
l_int|0x07
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x2E
comma
l_int|0x9A
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_AUTO
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|determine_norm
c_func
(paren
id|device
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_INPUT
suffix:colon
id|v
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v
id|SAA7110_MAX_INPUT
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;input
op_ne
id|v
)paren
(brace
id|decoder-&gt;input
op_assign
id|v
suffix:semicolon
id|saa7110_selmux
c_func
(paren
id|device
comma
id|v
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_OUTPUT
suffix:colon
id|v
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
multiline_comment|/* not much choice of outputs */
r_if
c_cond
(paren
id|v
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DECODER_ENABLE_OUTPUT
suffix:colon
id|v
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;enable
op_ne
id|v
)paren
(brace
id|decoder-&gt;enable
op_assign
id|v
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x0E
comma
id|v
ques
c_cond
l_int|0x18
suffix:colon
l_int|0x00
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|decoder-&gt;bright
op_ne
id|pic-&gt;brightness
)paren
(brace
multiline_comment|/* We want 0 to 255 we get 0-65535 */
id|decoder-&gt;bright
op_assign
id|pic-&gt;brightness
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x19
comma
id|decoder-&gt;bright
op_rshift
l_int|8
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
multiline_comment|/* We want 0 to 127 we get 0-65535 */
id|decoder-&gt;contrast
op_assign
id|pic-&gt;contrast
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x13
comma
id|decoder-&gt;contrast
op_rshift
l_int|9
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
multiline_comment|/* We want 0 to 127 we get 0-65535 */
id|decoder-&gt;sat
op_assign
id|pic-&gt;colour
suffix:semicolon
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x12
comma
id|decoder-&gt;sat
op_rshift
l_int|9
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
id|saa7110_write
c_func
(paren
id|decoder
comma
l_int|0x07
comma
(paren
id|decoder-&gt;hue
op_rshift
l_int|8
)paren
op_minus
l_int|128
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_DUMP
suffix:colon
r_for
c_loop
(paren
id|v
op_assign
l_int|0
suffix:semicolon
id|v
OL
l_int|34
suffix:semicolon
id|v
op_add_assign
l_int|16
)paren
(brace
r_int
id|j
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %03x&bslash;n&quot;
comma
id|device-&gt;name
comma
id|v
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
id|j
op_increment
)paren
(brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; %02x&quot;
comma
id|decoder-&gt;reg
(braket
id|v
op_plus
id|j
)braket
)paren
)paren
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;unknown saa7110_command??(%d)&bslash;n&quot;
comma
id|cmd
)paren
)paren
suffix:semicolon
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
DECL|variable|i2c_driver_saa7110
r_static
r_struct
id|i2c_driver
id|i2c_driver_saa7110
op_assign
(brace
l_string|&quot;saa7110&quot;
comma
multiline_comment|/* name */
id|I2C_DRIVERID_VIDEODECODER
comma
multiline_comment|/* in i2c.h */
id|I2C_SAA7110
comma
id|I2C_SAA7110
op_plus
l_int|1
comma
multiline_comment|/* Addr range */
id|saa7110_attach
comma
id|saa7110_detach
comma
id|saa7110_command
)brace
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|saa7110_init
r_static
r_int
id|saa7110_init
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_register_driver
c_func
(paren
op_amp
id|i2c_driver_saa7110
)paren
suffix:semicolon
)brace
DECL|function|saa7110_exit
r_static
r_void
id|saa7110_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_unregister_driver
c_func
(paren
op_amp
id|i2c_driver_saa7110
)paren
suffix:semicolon
)brace
DECL|variable|saa7110_init
id|module_init
c_func
(paren
id|saa7110_init
)paren
suffix:semicolon
DECL|variable|saa7110_exit
id|module_exit
c_func
(paren
id|saa7110_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
