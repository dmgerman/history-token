DECL|macro|DEBUGLEVEL
mdefine_line|#define DEBUGLEVEL 0
multiline_comment|/* &n;    adv7175 - adv7175a video encoder driver version 0.0.3&n;&n;    Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;    Copyright (C) 1999 Wolfgang Scherr &lt;scherr@net4you.net&gt;&n;    Copyright (C) 2000 Serguei Miridonov &lt;mirsev@cicese.mx&gt;&n;       - some corrections for Pinnacle Systems Inc. DC10plus card.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/i2c-old.h&gt;
macro_line|#include &lt;linux/video_encoder.h&gt;
macro_line|#if (DEBUGLEVEL &gt; 0)
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x...)  x&t;&t;/* Debug driver */
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x...)
macro_line|#endif
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|struct|adv7175
r_struct
id|adv7175
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
l_int|128
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
DECL|macro|I2C_ADV7175
mdefine_line|#define   I2C_ADV7175        0xd4
DECL|macro|I2C_ADV7176
mdefine_line|#define   I2C_ADV7176        0x54
DECL|variable|adv7175_name
r_static
r_char
id|adv7175_name
(braket
)braket
op_assign
l_string|&quot;adv7175&quot;
suffix:semicolon
DECL|variable|adv7176_name
r_static
r_char
id|adv7176_name
(braket
)braket
op_assign
l_string|&quot;adv7176&quot;
suffix:semicolon
DECL|variable|unknown_name
r_static
r_char
id|unknown_name
(braket
)braket
op_assign
l_string|&quot;UNKNOWN&quot;
suffix:semicolon
macro_line|#if (DEBUGLEVEL &gt; 0)
DECL|variable|inputs
r_static
r_char
op_star
id|inputs
(braket
)braket
op_assign
(brace
l_string|&quot;pass_through&quot;
comma
l_string|&quot;play_back&quot;
comma
l_string|&quot;color_bar&quot;
)brace
suffix:semicolon
DECL|variable|norms
r_static
r_char
op_star
id|norms
(braket
)braket
op_assign
(brace
l_string|&quot;PAL&quot;
comma
l_string|&quot;NTSC&quot;
comma
l_string|&quot;SECAM-&gt;PAL (may not work!)&quot;
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|I2C_DELAY
mdefine_line|#define I2C_DELAY   10
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|adv7175_write
r_static
r_int
id|adv7175_write
c_func
(paren
r_struct
id|adv7175
op_star
id|dev
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
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
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
id|dev-&gt;bus
comma
id|data
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
id|data
suffix:semicolon
id|i2c_stop
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
r_return
id|ack
suffix:semicolon
)brace
DECL|function|adv7175_read
r_static
r_int
r_char
id|adv7175_read
c_func
(paren
r_struct
id|adv7175
op_star
id|dev
comma
r_int
r_char
id|subaddr
)paren
(brace
r_int
r_char
id|data
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|subaddr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
op_plus
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
id|dev-&gt;bus
comma
l_int|1
)paren
suffix:semicolon
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
id|data
suffix:semicolon
id|i2c_stop
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|adv7175_write_block
r_static
r_int
id|adv7175_write_block
c_func
(paren
r_struct
id|adv7175
op_star
id|dev
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
id|ack
op_assign
l_int|0
suffix:semicolon
r_int
id|subaddr
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
id|LOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
(paren
id|subaddr
op_assign
op_star
id|data
op_increment
)paren
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
(paren
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
op_star
id|data
op_increment
)paren
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
op_logical_and
op_star
id|data
op_eq
op_increment
id|subaddr
)paren
(brace
id|data
op_increment
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
(paren
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
op_star
id|data
op_increment
)paren
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
)brace
r_return
id|ack
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
singleline_comment|// Output filter:  S-Video  Composite
DECL|macro|MR050
mdefine_line|#define MR050       0x11&t;
singleline_comment|//0x09
DECL|macro|MR060
mdefine_line|#define MR060       0x14&t;
singleline_comment|//0x0c
singleline_comment|//---------------------------------------------------------------------------
DECL|macro|TR0MODE
mdefine_line|#define TR0MODE     0x46
DECL|macro|TR0RST
mdefine_line|#define TR0RST&t;    0x80
DECL|macro|TR1CAPT
mdefine_line|#define TR1CAPT&t;    0x80
DECL|macro|TR1PLAY
mdefine_line|#define TR1PLAY&t;    0x00
DECL|variable|init_common
r_static
r_const
r_int
r_char
id|init_common
(braket
)braket
op_assign
(brace
l_int|0x00
comma
id|MR050
comma
multiline_comment|/* MR0, PAL enabled */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* MR1 */
l_int|0x02
comma
l_int|0x0c
comma
multiline_comment|/* subc. freq. */
l_int|0x03
comma
l_int|0x8c
comma
multiline_comment|/* subc. freq. */
l_int|0x04
comma
l_int|0x79
comma
multiline_comment|/* subc. freq. */
l_int|0x05
comma
l_int|0x26
comma
multiline_comment|/* subc. freq. */
l_int|0x06
comma
l_int|0x40
comma
multiline_comment|/* subc. phase */
l_int|0x07
comma
id|TR0MODE
comma
multiline_comment|/* TR0, 16bit */
l_int|0x08
comma
l_int|0x21
comma
multiline_comment|/*  */
l_int|0x09
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x0a
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x0b
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x0c
comma
id|TR1CAPT
comma
multiline_comment|/* TR1 */
l_int|0x0d
comma
l_int|0x4f
comma
multiline_comment|/* MR2 */
l_int|0x0e
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x0f
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x10
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x11
comma
l_int|0x00
comma
multiline_comment|/*  */
l_int|0x12
comma
l_int|0x00
comma
multiline_comment|/* MR3 */
l_int|0x24
comma
l_int|0x00
comma
multiline_comment|/*  */
)brace
suffix:semicolon
DECL|variable|init_pal
r_static
r_const
r_int
r_char
id|init_pal
(braket
)braket
op_assign
(brace
l_int|0x00
comma
id|MR050
comma
multiline_comment|/* MR0, PAL enabled */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* MR1 */
l_int|0x02
comma
l_int|0x0c
comma
multiline_comment|/* subc. freq. */
l_int|0x03
comma
l_int|0x8c
comma
multiline_comment|/* subc. freq. */
l_int|0x04
comma
l_int|0x79
comma
multiline_comment|/* subc. freq. */
l_int|0x05
comma
l_int|0x26
comma
multiline_comment|/* subc. freq. */
l_int|0x06
comma
l_int|0x40
comma
multiline_comment|/* subc. phase */
)brace
suffix:semicolon
DECL|variable|init_ntsc
r_static
r_const
r_int
r_char
id|init_ntsc
(braket
)braket
op_assign
(brace
l_int|0x00
comma
id|MR060
comma
multiline_comment|/* MR0, NTSC enabled */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* MR1 */
l_int|0x02
comma
l_int|0x55
comma
multiline_comment|/* subc. freq. */
l_int|0x03
comma
l_int|0x55
comma
multiline_comment|/* subc. freq. */
l_int|0x04
comma
l_int|0x55
comma
multiline_comment|/* subc. freq. */
l_int|0x05
comma
l_int|0x25
comma
multiline_comment|/* subc. freq. */
l_int|0x06
comma
l_int|0x1a
comma
multiline_comment|/* subc. phase */
)brace
suffix:semicolon
DECL|function|adv7175_attach
r_static
r_int
id|adv7175_attach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|adv7175
op_star
id|encoder
suffix:semicolon
r_char
op_star
id|dname
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|device-&gt;data
op_assign
id|encoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|adv7175
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
id|MOD_DEC_USE_COUNT
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
id|adv7175
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|device-&gt;addr
op_eq
id|I2C_ADV7175
)paren
op_logical_or
(paren
id|device-&gt;addr
op_eq
(paren
id|I2C_ADV7175
op_plus
l_int|2
)paren
)paren
)paren
(brace
id|dname
op_assign
id|adv7175_name
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|device-&gt;addr
op_eq
id|I2C_ADV7176
)paren
op_logical_or
(paren
id|device-&gt;addr
op_eq
(paren
id|I2C_ADV7176
op_plus
l_int|2
)paren
)paren
)paren
(brace
id|dname
op_assign
id|adv7176_name
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// We should never get here!!!
id|dname
op_assign
id|unknown_name
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|device-&gt;name
comma
id|dname
)paren
suffix:semicolon
id|encoder-&gt;bus
op_assign
id|device-&gt;bus
suffix:semicolon
id|encoder-&gt;addr
op_assign
id|device-&gt;addr
suffix:semicolon
id|encoder-&gt;norm
op_assign
id|VIDEO_MODE_PAL
suffix:semicolon
id|encoder-&gt;input
op_assign
l_int|0
suffix:semicolon
id|encoder-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|i
op_assign
id|adv7175_write_block
c_func
(paren
id|encoder
comma
id|init_common
comma
r_sizeof
(paren
id|init_common
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|0
)paren
(brace
id|i
op_assign
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|i
op_assign
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
id|i
op_assign
id|adv7175_read
c_func
(paren
id|encoder
comma
l_int|0x12
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s_attach: %s rev. %d at 0x%02x&bslash;n&quot;
comma
id|device-&gt;name
comma
id|dname
comma
id|i
op_amp
l_int|1
comma
id|device-&gt;addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s_attach: init error %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adv7175_detach
r_static
r_int
id|adv7175_detach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
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
DECL|function|adv7175_command
r_static
r_int
id|adv7175_command
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
id|adv7175
op_star
id|encoder
op_assign
id|device-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
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
id|cap-&gt;flags
op_assign
id|VIDEO_ENCODER_PAL
op_or
id|VIDEO_ENCODER_NTSC
singleline_comment|// | VIDEO_ENCODER_SECAM
singleline_comment|// | VIDEO_ENCODER_CCIR
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
id|iarg
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
id|encoder-&gt;norm
op_ne
id|iarg
)paren
(brace
r_switch
c_cond
(paren
id|iarg
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|adv7175_write_block
c_func
(paren
id|encoder
comma
id|init_ntsc
comma
r_sizeof
(paren
id|init_ntsc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|encoder-&gt;input
op_eq
l_int|0
)paren
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x4f
)paren
suffix:semicolon
singleline_comment|// Enable genlock
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|adv7175_write_block
c_func
(paren
id|encoder
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|encoder-&gt;input
op_eq
l_int|0
)paren
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x4f
)paren
suffix:semicolon
singleline_comment|// Enable genlock
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_SECAM
suffix:colon
singleline_comment|// WARNING! ADV7176 does not support SECAM.
singleline_comment|// This is an attempt to convert SECAM-&gt;PAL (typically
singleline_comment|// it does not work due to genlock: when decoder
singleline_comment|// is in SECAM and encoder in in PAL the subcarrier
singleline_comment|// can not be syncronized with horizontal frequency)
id|adv7175_write_block
c_func
(paren
id|encoder
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|encoder-&gt;input
op_eq
l_int|0
)paren
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x49
)paren
suffix:semicolon
singleline_comment|// Disable genlock
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: illegal norm: %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|iarg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: switched to %s&bslash;n&quot;
comma
id|device-&gt;name
comma
id|norms
(braket
id|iarg
)braket
)paren
)paren
suffix:semicolon
id|encoder-&gt;norm
op_assign
id|iarg
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_INPUT
suffix:colon
(brace
r_int
id|iarg
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
multiline_comment|/* RJ: *iarg = 0: input is from SAA7110&n;&t;&t;&t;   *iarg = 1: input is from ZR36060&n;&t;&t;&t;   *iarg = 2: color bar */
r_if
c_cond
(paren
id|encoder-&gt;input
op_ne
id|iarg
)paren
(brace
r_switch
c_cond
(paren
id|iarg
)paren
(brace
r_case
l_int|0
suffix:colon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x01
comma
l_int|0x00
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0c
comma
id|TR1CAPT
)paren
suffix:semicolon
multiline_comment|/* TR1 */
r_if
c_cond
(paren
id|encoder-&gt;norm
op_eq
id|VIDEO_MODE_SECAM
)paren
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x49
)paren
suffix:semicolon
singleline_comment|// Disable genlock
r_else
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x4f
)paren
suffix:semicolon
singleline_comment|// Enable genlock
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
singleline_comment|//udelay(10);
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x01
comma
l_int|0x00
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0c
comma
id|TR1PLAY
)paren
suffix:semicolon
multiline_comment|/* TR1 */
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x49
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
singleline_comment|//udelay(10);
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x01
comma
l_int|0x80
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x0d
comma
l_int|0x49
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
op_or
id|TR0RST
)paren
suffix:semicolon
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x07
comma
id|TR0MODE
)paren
suffix:semicolon
singleline_comment|//udelay(10);
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: illegal input: %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|iarg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: switched to %s&bslash;n&quot;
comma
id|device-&gt;name
comma
id|inputs
(braket
id|iarg
)braket
)paren
)paren
suffix:semicolon
id|encoder-&gt;input
op_assign
id|iarg
suffix:semicolon
)brace
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
id|adv7175_write
c_func
(paren
id|encoder
comma
l_int|0x61
comma
(paren
id|encoder
op_member_access_from_pointer
id|reg
(braket
l_int|0x61
)braket
op_amp
l_int|0xbf
)paren
op_or
(paren
id|encoder
op_member_access_from_pointer
id|enable
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x40
)paren
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
DECL|variable|i2c_driver_adv7175
r_static
r_struct
id|i2c_driver
id|i2c_driver_adv7175
op_assign
(brace
l_string|&quot;adv7175&quot;
comma
multiline_comment|/* name */
id|I2C_DRIVERID_VIDEOENCODER
comma
multiline_comment|/* ID */
id|I2C_ADV7175
comma
id|I2C_ADV7175
op_plus
l_int|3
comma
id|adv7175_attach
comma
id|adv7175_detach
comma
id|adv7175_command
)brace
suffix:semicolon
DECL|variable|i2c_driver_adv7176
r_static
r_struct
id|i2c_driver
id|i2c_driver_adv7176
op_assign
(brace
l_string|&quot;adv7175&quot;
comma
multiline_comment|/* name */
id|I2C_DRIVERID_VIDEOENCODER
comma
multiline_comment|/* ID */
id|I2C_ADV7176
comma
id|I2C_ADV7176
op_plus
l_int|3
comma
id|adv7175_attach
comma
id|adv7175_detach
comma
id|adv7175_command
)brace
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|adv7175_init
r_static
r_int
id|adv7175_init
c_func
(paren
r_void
)paren
(brace
r_int
id|res_adv7175
op_assign
l_int|0
comma
id|res_adv7176
op_assign
l_int|0
suffix:semicolon
id|res_adv7175
op_assign
id|i2c_register_driver
c_func
(paren
op_amp
id|i2c_driver_adv7175
)paren
suffix:semicolon
id|res_adv7176
op_assign
id|i2c_register_driver
c_func
(paren
op_amp
id|i2c_driver_adv7176
)paren
suffix:semicolon
r_return
(paren
id|res_adv7175
op_or
id|res_adv7176
)paren
suffix:semicolon
singleline_comment|// Any idea how to make it better?
)brace
DECL|function|adv7175_exit
r_static
r_void
id|adv7175_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_unregister_driver
c_func
(paren
op_amp
id|i2c_driver_adv7176
)paren
suffix:semicolon
id|i2c_unregister_driver
c_func
(paren
op_amp
id|i2c_driver_adv7175
)paren
suffix:semicolon
)brace
DECL|variable|adv7175_init
id|module_init
c_func
(paren
id|adv7175_init
)paren
suffix:semicolon
DECL|variable|adv7175_exit
id|module_exit
c_func
(paren
id|adv7175_exit
)paren
suffix:semicolon
eof
