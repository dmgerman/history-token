multiline_comment|/*&n; * saa7110 - Philips SAA7110(A) video decoder driver&n; *&n; * Copyright (C) 1998 Pauline Middelink &lt;middelin@polyware.nl&gt;&n; *&n; * Copyright (C) 1999 Wolfgang Scherr &lt;scherr@net4you.net&gt;&n; * Copyright (C) 2000 Serguei Miridonov &lt;mirsev@cicese.mx&gt;&n; *    - some corrections for Pinnacle Systems Inc. DC10plus card.&n; *&n; * Changes by Ronald Bultje &lt;rbultje@ronald.bitfreak.net&gt;&n; *    - moved over to linux&gt;=2.4.x i2c protocol (1/1/2003)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Philips SAA7110 video decoder driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Pauline Middelink&quot;
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
macro_line|#include &lt;linux/videodev.h&gt;
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
DECL|macro|SAA7110_MAX_INPUT
mdefine_line|#define SAA7110_MAX_INPUT&t;9&t;/* 6 CVBS, 3 SVHS */
DECL|macro|SAA7110_MAX_OUTPUT
mdefine_line|#define SAA7110_MAX_OUTPUT&t;0&t;/* its a decoder only */
DECL|macro|I2C_SAA7110
mdefine_line|#define&t;I2C_SAA7110&t;&t;0x9C&t;/* or 0x9E */
DECL|struct|saa7110
r_struct
id|saa7110
(brace
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|54
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
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* I2C support functions&t;&t;&t;&t;&t;&t;   */
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_int
DECL|function|saa7110_write
id|saa7110_write
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
id|saa7110
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
r_int
DECL|function|saa7110_write_block
id|saa7110_write_block
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
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|len
op_decrement
suffix:semicolon
multiline_comment|/* the saa7110 has an autoincrement function, use it if&n;&t; * the adapter understands raw I2C */
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
r_struct
id|saa7110
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
l_int|54
)braket
suffix:semicolon
id|msg.len
op_assign
l_int|0
suffix:semicolon
id|msg.buf
op_assign
(paren
r_char
op_star
)paren
id|block_data
suffix:semicolon
id|msg.addr
op_assign
id|client-&gt;addr
suffix:semicolon
id|msg.flags
op_assign
id|client-&gt;flags
suffix:semicolon
r_while
c_loop
(paren
id|len
op_ge
l_int|1
)paren
(brace
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
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
op_ge
l_int|1
op_logical_and
id|msg.len
OL
l_int|54
)paren
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
op_star
id|data
op_increment
suffix:semicolon
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
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|len
op_decrement
op_ge
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|saa7110_write
c_func
(paren
id|client
comma
id|reg
op_increment
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
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|saa7110_read
id|saa7110_read
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
id|i2c_smbus_read_byte
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* SAA7110 functions&t;&t;&t;&t;&t;&t;&t;   */
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|macro|FRESP_06H_COMPST
mdefine_line|#define FRESP_06H_COMPST 0x03&t;
singleline_comment|//0x13
DECL|macro|FRESP_06H_SVIDEO
mdefine_line|#define FRESP_06H_SVIDEO 0x83&t;
singleline_comment|//0xC0
r_static
r_int
DECL|function|saa7110_selmux
id|saa7110_selmux
(paren
r_struct
id|i2c_client
op_star
id|client
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
id|FRESP_06H_COMPST
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
id|FRESP_06H_COMPST
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
id|FRESP_06H_COMPST
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
id|FRESP_06H_COMPST
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
id|FRESP_06H_COMPST
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
id|FRESP_06H_COMPST
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
id|FRESP_06H_SVIDEO
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
id|FRESP_06H_SVIDEO
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
id|FRESP_06H_SVIDEO
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
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
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
id|client
comma
l_int|0x06
comma
id|ptr
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Luminance control    */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x20
comma
id|ptr
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Analog Control #1    */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x21
comma
id|ptr
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* Analog Control #2    */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x22
comma
id|ptr
(braket
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* Mixer Control #1     */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x2C
comma
id|ptr
(braket
l_int|4
)braket
)paren
suffix:semicolon
multiline_comment|/* Mixer Control #2     */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x30
comma
id|ptr
(braket
l_int|5
)braket
)paren
suffix:semicolon
multiline_comment|/* ADCs gain control    */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x31
comma
id|ptr
(braket
l_int|6
)braket
)paren
suffix:semicolon
multiline_comment|/* Mixer Control #3     */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x21
comma
id|ptr
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* Analog Control #2    */
id|decoder-&gt;input
op_assign
id|chan
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|initseq
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
l_int|0xF2
comma
l_int|0x03
comma
l_int|0x00
comma
multiline_comment|/* 0x08 */
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
l_int|0x86
comma
l_int|0x18
comma
l_int|0x90
comma
multiline_comment|/* 0x10 */
l_int|0x00
comma
l_int|0x59
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
multiline_comment|/* 0x18 */
l_int|0xF2
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
multiline_comment|/* 0x20 */
l_int|0xD9
comma
l_int|0x16
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
multiline_comment|/* 0x28 */
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
l_int|0x03
comma
l_int|0x0C
comma
multiline_comment|/* 0x30 */
l_int|0x44
comma
l_int|0x71
comma
l_int|0x02
comma
l_int|0x8C
comma
l_int|0x02
)brace
suffix:semicolon
r_static
r_int
DECL|function|determine_norm
id|determine_norm
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|saa7110
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
id|status
suffix:semicolon
multiline_comment|/* mode changed, start automatic detection */
id|saa7110_write_block
c_func
(paren
id|client
comma
id|initseq
comma
r_sizeof
(paren
id|initseq
)paren
)paren
suffix:semicolon
id|saa7110_selmux
c_func
(paren
id|client
comma
id|decoder-&gt;input
)paren
suffix:semicolon
id|sleep_on_timeout
c_func
(paren
op_amp
id|decoder-&gt;wq
comma
id|HZ
op_div
l_int|4
)paren
suffix:semicolon
id|status
op_assign
id|saa7110_read
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x40
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status=0x%02x (no signal)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
)paren
suffix:semicolon
r_return
id|decoder-&gt;norm
suffix:semicolon
singleline_comment|// no change
)brace
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
id|client
comma
l_int|0x06
comma
l_int|0x83
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
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status=0x%02x (NTSC/no color)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client,0x2E,0x81);
r_return
id|VIDEO_MODE_NTSC
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status=0x%02x (PAL/no color)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client,0x2E,0x9A);
r_return
id|VIDEO_MODE_PAL
suffix:semicolon
)brace
singleline_comment|//saa7110_write(client,0x06,0x03);
r_if
c_cond
(paren
id|status
op_amp
l_int|0x20
)paren
(brace
multiline_comment|/* 60Hz */
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status=0x%02x (NTSC)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0D
comma
l_int|0x86
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0F
comma
l_int|0x50
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x11
comma
l_int|0x2C
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client,0x2E,0x81);
r_return
id|VIDEO_MODE_NTSC
suffix:semicolon
)brace
multiline_comment|/* 50Hz -&gt; PAL/SECAM */
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0D
comma
l_int|0x86
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0F
comma
l_int|0x10
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client,0x2E,0x9A);
id|sleep_on_timeout
c_func
(paren
op_amp
id|decoder-&gt;wq
comma
id|HZ
op_div
l_int|4
)paren
suffix:semicolon
id|status
op_assign
id|saa7110_read
c_func
(paren
id|client
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
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status=0x%02x (SECAM)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0D
comma
l_int|0x87
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_SECAM
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status=0x%02x (PAL)&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
)paren
suffix:semicolon
r_return
id|VIDEO_MODE_PAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|saa7110_command
id|saa7110_command
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
id|saa7110
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
id|v
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
singleline_comment|//saa7110_write_block(client, initseq, sizeof(initseq));
r_break
suffix:semicolon
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
id|saa7110_read
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
l_string|&quot;%s: status=0x%02x norm=%d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|status
comma
id|decoder-&gt;norm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
l_int|0x40
)paren
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
singleline_comment|//saa7110_write(client, 0x06, 0x03);
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
id|client
comma
l_int|0x0D
comma
l_int|0x86
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0F
comma
l_int|0x50
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x11
comma
l_int|0x2C
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client, 0x2E, 0x81);
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: switched to NTSC&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
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
id|client
comma
l_int|0x0D
comma
l_int|0x86
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0F
comma
l_int|0x10
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client, 0x2E, 0x9A);
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: switched to PAL&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
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
id|client
comma
l_int|0x0D
comma
l_int|0x87
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0F
comma
l_int|0x10
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client, 0x2E, 0x9A);
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: switched to SECAM&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_AUTO
suffix:colon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: TV standard detection...&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
suffix:semicolon
id|decoder-&gt;norm
op_assign
id|determine_norm
c_func
(paren
id|client
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|decoder-&gt;norm
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
template_param
id|SAA7110_MAX_INPUT
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: input=%d not available&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|v
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
id|decoder-&gt;input
op_ne
id|v
)paren
(brace
id|saa7110_selmux
c_func
(paren
id|client
comma
id|v
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: switched to input=%d&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
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
id|client
comma
l_int|0x0E
comma
id|v
ques
c_cond
l_int|0x18
suffix:colon
l_int|0x80
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: YUV %s&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|v
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
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
id|client
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
id|client
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
id|client
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
id|client
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
l_int|0x34
suffix:semicolon
id|v
op_add_assign
l_int|16
)paren
(brace
r_int
id|j
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: %03x&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|v
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
id|dprintk
c_func
(paren
l_int|1
comma
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
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;unknown saa7110_command??(%d)&bslash;n&quot;
comma
id|cmd
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
id|I2C_SAA7110
op_rshift
l_int|1
comma
(paren
id|I2C_SAA7110
op_rshift
l_int|1
)paren
op_plus
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
DECL|variable|i2c_driver_saa7110
r_static
r_struct
id|i2c_driver
id|i2c_driver_saa7110
suffix:semicolon
r_static
r_int
DECL|function|saa7110_detect_client
id|saa7110_detect_client
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
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_struct
id|saa7110
op_star
id|decoder
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;saa7110.c: detecting saa7110 client on address 0x%x&bslash;n&quot;
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
(paren
id|adapter
comma
id|I2C_FUNC_SMBUS_READ_BYTE
op_or
id|I2C_FUNC_SMBUS_WRITE_BYTE_DATA
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
id|i2c_driver_saa7110
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
l_string|&quot;saa7110&quot;
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
id|decoder
op_eq
l_int|0
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
id|saa7110
)paren
)paren
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
id|init_waitqueue_head
c_func
(paren
op_amp
id|decoder-&gt;wq
)paren
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|decoder
)paren
suffix:semicolon
id|rv
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
id|rv
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
id|rv
suffix:semicolon
)brace
id|rv
op_assign
id|saa7110_write_block
c_func
(paren
id|client
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
id|rv
)paren
suffix:semicolon
r_else
(brace
r_int
id|ver
comma
id|status
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x21
comma
l_int|0x10
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0e
comma
l_int|0x18
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0D
comma
l_int|0x04
)paren
suffix:semicolon
id|ver
op_assign
id|saa7110_read
c_func
(paren
id|client
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0D
comma
l_int|0x06
)paren
suffix:semicolon
singleline_comment|//mdelay(150);
id|status
op_assign
id|saa7110_read
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
l_string|&quot;%s_attach: SAA7110A version %x at 0x%02x, status=0x%02x&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|ver
comma
id|client-&gt;addr
op_lshift
l_int|1
comma
id|status
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0D
comma
l_int|0x86
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x0F
comma
l_int|0x10
)paren
suffix:semicolon
id|saa7110_write
c_func
(paren
id|client
comma
l_int|0x11
comma
l_int|0x59
)paren
suffix:semicolon
singleline_comment|//saa7110_write(client, 0x2E, 0x9A);
)brace
singleline_comment|//saa7110_selmux(client,0);
singleline_comment|//determine_norm(client);
multiline_comment|/* setup and implicit mode 0 select has been performed */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|saa7110_attach_adapter
id|saa7110_attach_adapter
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
l_string|&quot;saa7110.c: starting probe for adapter %s (0x%x)&bslash;n&quot;
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
id|saa7110_detect_client
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|saa7110_detach_client
id|saa7110_detach_client
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|saa7110
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
DECL|variable|i2c_driver_saa7110
r_static
r_struct
id|i2c_driver
id|i2c_driver_saa7110
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
l_string|&quot;saa7110&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_SAA7110
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|saa7110_attach_adapter
comma
dot
id|detach_client
op_assign
id|saa7110_detach_client
comma
dot
id|command
op_assign
id|saa7110_command
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|saa7110_init
id|saa7110_init
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|i2c_driver_saa7110
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|saa7110_exit
id|saa7110_exit
(paren
r_void
)paren
(brace
id|i2c_del_driver
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
eof
