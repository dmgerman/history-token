multiline_comment|/* &n;    bt819 - BT819A VideoStream Decoder (Rockwell Part)&n;&n;    Copyright (C) 1999 Mike Bernson &lt;mike@mlb.org&gt;&n;    Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;    Modifications for LML33/DC10plus unified driver&n;    Copyright (C) 2000 Serguei Miridonov &lt;mirsev@cicese.mx&gt;&n;    &n;    This code was modify/ported from the saa7111 driver written&n;    by Dave Perks.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/i2c-old.h&gt;
macro_line|#include &lt;linux/video_decoder.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)       x&t;/* Debug driver */
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|struct|bt819
r_struct
id|bt819
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
DECL|variable|timing_data
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
l_int|2
comma
l_int|623
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
l_int|2
comma
l_int|523
comma
l_int|1
comma
l_int|0x00f8
comma
l_int|0x0000
)brace
comma
singleline_comment|//      { 858-68, 64, 523, 1, 0x00f8, 0x0000 },
)brace
suffix:semicolon
DECL|macro|I2C_BT819
mdefine_line|#define   I2C_BT819        0x8a
DECL|macro|I2C_DELAY
mdefine_line|#define   I2C_DELAY   10
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|bt819_write
r_static
r_int
id|bt819_write
c_func
(paren
r_struct
id|bt819
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
DECL|function|bt819_setbit
r_static
r_int
id|bt819_setbit
c_func
(paren
r_struct
id|bt819
op_star
id|dev
comma
r_int
id|subaddr
comma
r_int
id|bit
comma
r_int
id|data
)paren
(brace
r_return
id|bt819_write
c_func
(paren
id|dev
comma
id|subaddr
comma
(paren
id|dev-&gt;reg
(braket
id|subaddr
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
id|data
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
DECL|function|bt819_write_block
r_static
r_int
id|bt819_write_block
c_func
(paren
r_struct
id|bt819
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
suffix:semicolon
r_int
id|subaddr
suffix:semicolon
id|ack
op_assign
l_int|0
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
DECL|function|bt819_read
r_static
r_int
id|bt819_read
c_func
(paren
r_struct
id|bt819
op_star
id|dev
comma
r_int
r_char
id|subaddr
)paren
(brace
r_int
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
id|dev-&gt;bus
comma
l_int|1
)paren
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
DECL|function|bt819_init
r_static
r_int
id|bt819_init
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_struct
id|bt819
op_star
id|decoder
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
multiline_comment|/* 0x13 Vertial Scaling msb 0x60, */
l_int|0x14
comma
l_int|0x00
comma
multiline_comment|/* 0x14 Vertial Scaling lsb */
l_int|0x16
comma
l_int|0x04
comma
multiline_comment|/* 0x16 Video Timing Polarity 0x02, */
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
suffix:semicolon
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
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
l_int|3
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
suffix:semicolon
id|init
(braket
l_int|4
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
l_int|5
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
l_int|6
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
l_int|7
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
l_int|8
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
l_int|9
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
id|bt819_write
c_func
(paren
id|decoder
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
r_return
id|bt819_write_block
c_func
(paren
id|decoder
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
DECL|function|bt819_attach
r_static
r_int
id|bt819_attach
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
id|bt819
op_star
id|decoder
suffix:semicolon
id|MOD_INC_USE_COUNT
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
id|strcpy
c_func
(paren
id|device-&gt;name
comma
l_string|&quot;bt819&quot;
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
id|i
op_assign
id|bt819_init
c_func
(paren
id|device
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bt819_attach: init status %d&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: bt819_attach: chip version %x&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
id|bt819_read
c_func
(paren
id|decoder
comma
l_int|0x17
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bt819_detach
r_static
r_int
id|bt819_detach
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
DECL|function|bt819_command
r_static
r_int
id|bt819_command
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
r_int
id|temp
suffix:semicolon
r_struct
id|bt819
op_star
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
singleline_comment|//return 0;
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
id|device
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
id|decoder
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
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s-bt819: get status %x&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
op_star
id|iarg
)paren
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
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s-bt819: set norm %x&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
op_star
id|iarg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|iarg
op_eq
id|VIDEO_MODE_NTSC
)paren
(brace
id|bt819_setbit
c_func
(paren
id|decoder
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
id|decoder
comma
l_int|0x01
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|decoder
comma
l_int|0x18
comma
l_int|0x68
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|decoder
comma
l_int|0x19
comma
l_int|0x5d
)paren
suffix:semicolon
singleline_comment|//bt819_setbit(decoder, 0x1a,  5, 1);
id|timing
op_assign
op_amp
id|timing_data
(braket
id|VIDEO_MODE_NTSC
)braket
suffix:semicolon
)brace
r_else
(brace
id|bt819_setbit
c_func
(paren
id|decoder
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
id|decoder
comma
l_int|0x01
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|decoder
comma
l_int|0x18
comma
l_int|0x7f
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|decoder
comma
l_int|0x19
comma
l_int|0x72
)paren
suffix:semicolon
singleline_comment|//bt819_setbit(decoder, 0x1a,  5, 0);
id|timing
op_assign
op_amp
id|timing_data
(braket
id|VIDEO_MODE_PAL
)braket
suffix:semicolon
)brace
id|bt819_write
c_func
(paren
id|decoder
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
id|timing
op_member_access_from_pointer
id|hdelay
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
id|decoder
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
id|decoder
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
id|decoder
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
id|decoder
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
id|decoder
comma
l_int|0x08
comma
id|timing-&gt;hscale
op_rshift
l_int|8
)paren
suffix:semicolon
id|bt819_write
c_func
(paren
id|decoder
comma
l_int|0x09
comma
id|timing-&gt;hscale
op_amp
l_int|0xff
)paren
suffix:semicolon
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
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s-bt819: set input %x&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
op_star
id|iarg
)paren
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
id|decoder
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
id|decoder
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
id|decoder
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
id|decoder
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
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s-bt819: set output %x&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
op_star
id|iarg
)paren
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
id|DEBUG
c_func
(paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s-bt819: enable output %x&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
op_star
id|iarg
)paren
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
id|decoder
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
id|decoder
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
id|DEBUG
c_func
(paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s-bt819: set picture brightness %d contrast %d colour %d&bslash;n&quot;
comma
id|decoder-&gt;bus-&gt;name
comma
id|pic-&gt;brightness
comma
id|pic-&gt;contrast
comma
id|pic-&gt;colour
)paren
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
id|decoder
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
id|decoder
comma
l_int|0x0c
comma
(paren
id|decoder
op_member_access_from_pointer
id|contrast
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
id|decoder
comma
l_int|0x0b
comma
l_int|2
comma
(paren
(paren
id|decoder
op_member_access_from_pointer
id|contrast
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
id|decoder
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
id|decoder
comma
l_int|0x0b
comma
l_int|1
comma
(paren
(paren
id|decoder
op_member_access_from_pointer
id|sat
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
id|decoder
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
id|decoder
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
id|decoder
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
DECL|variable|i2c_driver_bt819
r_static
r_struct
id|i2c_driver
id|i2c_driver_bt819
op_assign
(brace
l_string|&quot;bt819&quot;
comma
multiline_comment|/* name */
id|I2C_DRIVERID_VIDEODECODER
comma
multiline_comment|/* ID */
id|I2C_BT819
comma
id|I2C_BT819
op_plus
l_int|1
comma
id|bt819_attach
comma
id|bt819_detach
comma
id|bt819_command
)brace
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|bt819_setup
r_static
r_int
id|bt819_setup
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
id|i2c_driver_bt819
)paren
suffix:semicolon
)brace
DECL|function|bt819_exit
r_static
r_void
id|bt819_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_unregister_driver
c_func
(paren
op_amp
id|i2c_driver_bt819
)paren
suffix:semicolon
)brace
DECL|variable|bt819_setup
id|module_init
c_func
(paren
id|bt819_setup
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
