multiline_comment|/* &n; * vpx3220a, vpx3216b &amp; vpx3214c video decoder driver version 0.0.1&n; *&n; * Copyright (C) 2001 Laurent Pinchart &lt;lpinchart@freegates.be&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/byteorder/swab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-dev.h&gt;
DECL|macro|I2C_NAME
mdefine_line|#define I2C_NAME(x) (x)-&gt;dev.name
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/video_decoder.h&gt;
DECL|macro|I2C_VPX3220
mdefine_line|#define I2C_VPX3220        0x86
DECL|macro|VPX3220_DEBUG
mdefine_line|#define VPX3220_DEBUG&t;KERN_DEBUG &quot;vpx3220: &quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
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
DECL|macro|VPX_TIMEOUT_COUNT
mdefine_line|#define VPX_TIMEOUT_COUNT  10
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|struct|vpx3220
r_struct
id|vpx3220
(brace
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|255
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
DECL|variable|inputs
r_static
r_char
op_star
id|inputs
(braket
)braket
op_assign
(brace
l_string|&quot;internal&quot;
comma
l_string|&quot;composite&quot;
comma
l_string|&quot;svideo&quot;
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_inline
r_int
DECL|function|vpx3220_write
id|vpx3220_write
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
id|vpx3220
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
DECL|function|vpx3220_read
id|vpx3220_read
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
DECL|function|vpx3220_fp_status
id|vpx3220_fp_status
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VPX_TIMEOUT_COUNT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|vpx3220_read
c_func
(paren
id|client
comma
l_int|0x29
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
l_int|4
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|vpx3220_fp_write
id|vpx3220_fp_write
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|fpaddr
comma
id|u16
id|data
)paren
(brace
multiline_comment|/* Write the 16-bit address to the FPWR register */
r_if
c_cond
(paren
id|i2c_smbus_write_word_data
c_func
(paren
id|client
comma
l_int|0x27
comma
id|swab16
c_func
(paren
id|fpaddr
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|VPX3220_DEBUG
l_string|&quot;%s: failed&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vpx3220_fp_status
c_func
(paren
id|client
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Write the 16-bit data to the FPDAT register */
r_if
c_cond
(paren
id|i2c_smbus_write_word_data
c_func
(paren
id|client
comma
l_int|0x28
comma
id|swab16
c_func
(paren
id|data
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|VPX3220_DEBUG
l_string|&quot;%s: failed&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|u16
DECL|function|vpx3220_fp_read
id|vpx3220_fp_read
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u16
id|fpaddr
)paren
(brace
id|s16
id|data
suffix:semicolon
multiline_comment|/* Write the 16-bit address to the FPRD register */
r_if
c_cond
(paren
id|i2c_smbus_write_word_data
c_func
(paren
id|client
comma
l_int|0x26
comma
id|swab16
c_func
(paren
id|fpaddr
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|VPX3220_DEBUG
l_string|&quot;%s: failed&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vpx3220_fp_status
c_func
(paren
id|client
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Read the 16-bit data from the FPDAT register */
id|data
op_assign
id|i2c_smbus_read_word_data
c_func
(paren
id|client
comma
l_int|0x28
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
op_minus
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|VPX3220_DEBUG
l_string|&quot;%s: failed&bslash;n&quot;
comma
id|__func__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|swab16
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|vpx3220_write_block
id|vpx3220_write_block
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
id|u8
id|reg
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
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
id|vpx3220_write
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
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|vpx3220_write_fp_block
id|vpx3220_write_fp_block
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_const
id|u16
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
id|u8
id|reg
suffix:semicolon
r_int
id|ret
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
id|reg
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|ret
op_or_assign
id|vpx3220_fp_write
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
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|init_ntsc
r_static
r_const
r_int
r_int
id|init_ntsc
(braket
)braket
op_assign
(brace
l_int|0x1c
comma
l_int|0x00
comma
multiline_comment|/* NTSC tint angle */
l_int|0x88
comma
l_int|17
comma
multiline_comment|/* Window 1 vertical */
l_int|0x89
comma
l_int|240
comma
multiline_comment|/* Vertical lines in */
l_int|0x8a
comma
l_int|240
comma
multiline_comment|/* Vertical lines out */
l_int|0x8b
comma
l_int|000
comma
multiline_comment|/* Horizontal begin */
l_int|0x8c
comma
l_int|640
comma
multiline_comment|/* Horizontal length */
l_int|0x8d
comma
l_int|640
comma
multiline_comment|/* Number of pixels */
l_int|0x8f
comma
l_int|0xc00
comma
multiline_comment|/* Disable window 2 */
l_int|0xf0
comma
l_int|0x173
comma
multiline_comment|/* 13.5 MHz transport, Forced&n;&t;&t;&t;&t; * mode, latch windows */
l_int|0xf2
comma
l_int|0x13
comma
multiline_comment|/* NTSC M, composite input */
l_int|0xe7
comma
l_int|0x1e1
comma
multiline_comment|/* Enable vertical standard&n;&t;&t;&t;&t; * locking @ 240 lines */
)brace
suffix:semicolon
DECL|variable|init_pal
r_static
r_const
r_int
r_int
id|init_pal
(braket
)braket
op_assign
(brace
l_int|0x88
comma
l_int|23
comma
multiline_comment|/* Window 1 vertical begin */
l_int|0x89
comma
l_int|288
op_plus
l_int|16
comma
multiline_comment|/* Vertical lines in (16 lines&n;&t;&t;&t;&t; * skipped by the VFE) */
l_int|0x8a
comma
l_int|288
op_plus
l_int|16
comma
multiline_comment|/* Vertical lines out (16 lines&n;&t;&t;&t;&t; * skipped by the VFE) */
l_int|0x8b
comma
l_int|16
comma
multiline_comment|/* Horizontal begin */
l_int|0x8c
comma
l_int|768
comma
multiline_comment|/* Horizontal length */
l_int|0x8d
comma
l_int|784
comma
multiline_comment|/* Number of pixels&n;&t;&t;&t;&t; * Must be &gt;= Horizontal begin + Horizontal length */
l_int|0x8f
comma
l_int|0xc00
comma
multiline_comment|/* Disable window 2 */
l_int|0xf0
comma
l_int|0x177
comma
multiline_comment|/* 13.5 MHz transport, Forced&n;&t;&t;&t;&t; * mode, latch windows */
l_int|0xf2
comma
l_int|0x3d1
comma
multiline_comment|/* PAL B,G,H,I, composite input */
l_int|0xe7
comma
l_int|0x261
comma
multiline_comment|/* PAL/SECAM set to 288 + 16 lines &n;&t;&t;&t;&t; * change to 0x241 for 288 lines */
)brace
suffix:semicolon
DECL|variable|init_secam
r_static
r_const
r_int
r_int
id|init_secam
(braket
)braket
op_assign
(brace
l_int|0x88
comma
l_int|23
op_minus
l_int|16
comma
multiline_comment|/* Window 1 vertical begin */
l_int|0x89
comma
l_int|288
op_plus
l_int|16
comma
multiline_comment|/* Vertical lines in (16 lines&n;&t;&t;&t;&t; * skipped by the VFE) */
l_int|0x8a
comma
l_int|288
op_plus
l_int|16
comma
multiline_comment|/* Vertical lines out (16 lines&n;&t;&t;&t;&t; * skipped by the VFE) */
l_int|0x8b
comma
l_int|16
comma
multiline_comment|/* Horizontal begin */
l_int|0x8c
comma
l_int|768
comma
multiline_comment|/* Horizontal length */
l_int|0x8d
comma
l_int|784
comma
multiline_comment|/* Number of pixels&n;&t;&t;&t;&t; * Must be &gt;= Horizontal begin + Horizontal length */
l_int|0x8f
comma
l_int|0xc00
comma
multiline_comment|/* Disable window 2 */
l_int|0xf0
comma
l_int|0x177
comma
multiline_comment|/* 13.5 MHz transport, Forced&n;&t;&t;&t;&t; * mode, latch windows */
l_int|0xf2
comma
l_int|0x3d5
comma
multiline_comment|/* SECAM, composite input */
l_int|0xe7
comma
l_int|0x261
comma
multiline_comment|/* PAL/SECAM set to 288 + 16 lines &n;&t;&t;&t;&t; * change to 0x241 for 288 lines */
)brace
suffix:semicolon
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
l_int|0xf2
comma
l_int|0x00
comma
multiline_comment|/* Disable all outputs */
l_int|0x33
comma
l_int|0x0d
comma
multiline_comment|/* Luma : VIN2, Chroma : CIN&n;&t;&t;&t;&t; * (clamp off) */
l_int|0xd8
comma
l_int|0xa8
comma
multiline_comment|/* HREF/VREF active high, VREF&n;&t;&t;&t;&t; * pulse = 2, Odd/Even flag */
l_int|0x20
comma
l_int|0x03
comma
multiline_comment|/* IF compensation 0dB/oct */
l_int|0xe0
comma
l_int|0xff
comma
multiline_comment|/* Open up all comparators */
l_int|0xe1
comma
l_int|0x00
comma
l_int|0xe2
comma
l_int|0x7f
comma
l_int|0xe3
comma
l_int|0x80
comma
l_int|0xe4
comma
l_int|0x7f
comma
l_int|0xe5
comma
l_int|0x80
comma
l_int|0xe6
comma
l_int|0x00
comma
multiline_comment|/* Brightness set to 0 */
l_int|0xe7
comma
l_int|0xe0
comma
multiline_comment|/* Contrast to 1.0, noise shaping&n;&t;&t;&t;&t; * 10 to 8 2-bit error diffusion */
l_int|0xe8
comma
l_int|0xf8
comma
multiline_comment|/* YUV422, CbCr binary offset,&n;&t;&t;&t;&t; * ... (p.32) */
l_int|0xea
comma
l_int|0x18
comma
multiline_comment|/* LLC2 connected, output FIFO&n;&t;&t;&t;&t; * reset with VACTintern */
l_int|0xf0
comma
l_int|0x8a
comma
multiline_comment|/* Half full level to 10, bus&n;&t;&t;&t;&t; * shuffler [7:0, 23:16, 15:8] */
l_int|0xf1
comma
l_int|0x18
comma
multiline_comment|/* Single clock, sync mode, no&n;&t;&t;&t;&t; * FE delay, no HLEN counter */
l_int|0xf8
comma
l_int|0x12
comma
multiline_comment|/* Port A, PIXCLK, HF# &amp; FE#&n;&t;&t;&t;&t; * strength to 2 */
l_int|0xf9
comma
l_int|0x24
comma
multiline_comment|/* Port B, HREF, VREF, PREF &amp;&n;&t;&t;&t;&t; * ALPHA strength to 4 */
)brace
suffix:semicolon
DECL|variable|init_fp
r_static
r_const
r_int
r_int
id|init_fp
(braket
)braket
op_assign
(brace
l_int|0x59
comma
l_int|0
comma
l_int|0xa0
comma
l_int|2070
comma
multiline_comment|/* ACC reference */
l_int|0xa3
comma
l_int|0
comma
l_int|0xa4
comma
l_int|0
comma
l_int|0xa8
comma
l_int|30
comma
l_int|0xb2
comma
l_int|768
comma
l_int|0xbe
comma
l_int|27
comma
l_int|0x58
comma
l_int|0
comma
l_int|0x26
comma
l_int|0
comma
l_int|0x4b
comma
l_int|0x298
comma
multiline_comment|/* PLL gain */
)brace
suffix:semicolon
r_static
r_void
DECL|function|vpx3220_dump_i2c
id|vpx3220_dump_i2c
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
id|len
op_assign
r_sizeof
(paren
id|init_common
)paren
suffix:semicolon
r_const
r_int
r_char
op_star
id|data
op_assign
id|init_common
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_DEBUG
l_string|&quot;vpx3216b i2c reg 0x%02x data 0x%02x&bslash;n&quot;
comma
op_star
id|data
comma
id|vpx3220_read
c_func
(paren
id|client
comma
op_star
id|data
)paren
)paren
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|vpx3220_command
id|vpx3220_command
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
id|vpx3220
op_star
id|decoder
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
(brace
id|vpx3220_write_block
c_func
(paren
id|client
comma
id|init_common
comma
r_sizeof
(paren
id|init_common
)paren
)paren
suffix:semicolon
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_fp
comma
r_sizeof
(paren
id|init_fp
)paren
op_rshift
l_int|1
)paren
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
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_ntsc
comma
r_sizeof
(paren
id|init_ntsc
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_SECAM
suffix:colon
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_secam
comma
r_sizeof
(paren
id|init_secam
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_DUMP
suffix:colon
(brace
id|vpx3220_dump_i2c
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
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
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_DEBUG
l_string|&quot;%s: DECODER_GET_CAPABILITIES&bslash;n&quot;
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
id|cap-&gt;inputs
op_assign
l_int|3
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
id|res
op_assign
l_int|0
comma
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: DECODER_GET_STATUS&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
suffix:semicolon
id|status
op_assign
id|vpx3220_fp_read
c_func
(paren
id|client
comma
l_int|0x0f3
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: status: 0x%04x&bslash;n&quot;
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
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
(brace
id|res
op_or_assign
id|DECODER_STATUS_GOOD
op_or
id|DECODER_STATUS_COLOR
suffix:semicolon
r_switch
c_cond
(paren
id|status
op_amp
l_int|0x18
)paren
(brace
r_case
l_int|0x00
suffix:colon
r_case
l_int|0x10
suffix:colon
r_case
l_int|0x14
suffix:colon
r_case
l_int|0x18
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_PAL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_SECAM
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
r_case
l_int|0x0c
suffix:colon
r_case
l_int|0x1c
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_NTSC
suffix:semicolon
r_break
suffix:semicolon
)brace
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
(brace
r_int
op_star
id|iarg
op_assign
id|arg
comma
id|data
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_DEBUG
l_string|&quot;%s: DECODER_SET_NORM %d&bslash;n&quot;
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
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_ntsc
comma
r_sizeof
(paren
id|init_ntsc
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: norm switched to NTSC&bslash;n&quot;
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
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: norm switched to PAL&bslash;n&quot;
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
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_secam
comma
r_sizeof
(paren
id|init_secam
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: norm switched to SECAM&bslash;n&quot;
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
multiline_comment|/* FIXME This is only preliminary support */
id|data
op_assign
id|vpx3220_fp_read
c_func
(paren
id|client
comma
l_int|0xf2
)paren
op_amp
l_int|0x20
suffix:semicolon
id|vpx3220_fp_write
c_func
(paren
id|client
comma
l_int|0xf2
comma
l_int|0x00c0
op_or
id|data
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: norm switched to Auto&bslash;n&quot;
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
r_default
suffix:colon
r_return
op_minus
id|EINVAL
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
comma
id|data
suffix:semicolon
multiline_comment|/* RJ:  *iarg = 0: ST8 (PCTV) input&n;&t;&t; *iarg = 1: COMPOSITE  input&n;&t;&t; *iarg = 2: SVHS       input  */
r_const
r_int
id|input
(braket
l_int|3
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0x0c
comma
l_int|0
)brace
comma
(brace
l_int|0x0d
comma
l_int|0
)brace
comma
(brace
l_int|0x0e
comma
l_int|1
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
op_star
id|iarg
template_param
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: input switched to %s&bslash;n&quot;
comma
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
id|inputs
(braket
op_star
id|iarg
)braket
)paren
suffix:semicolon
id|vpx3220_write
c_func
(paren
id|client
comma
l_int|0x33
comma
id|input
(braket
op_star
id|iarg
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|data
op_assign
id|vpx3220_fp_read
c_func
(paren
id|client
comma
l_int|0xf2
)paren
op_amp
op_complement
(paren
l_int|0x0020
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
OL
l_int|0
)paren
r_return
id|data
suffix:semicolon
multiline_comment|/* 0x0010 is required to latch the setting */
id|vpx3220_fp_write
c_func
(paren
id|client
comma
l_int|0xf2
comma
id|data
op_or
(paren
id|input
(braket
op_star
id|iarg
)braket
(braket
l_int|1
)braket
op_lshift
l_int|5
)paren
op_or
l_int|0x0010
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
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
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_DEBUG
l_string|&quot;%s: DECODER_ENABLE_OUTPUT %d&bslash;n&quot;
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
id|vpx3220_write
c_func
(paren
id|client
comma
l_int|0xf2
comma
(paren
op_star
id|iarg
ques
c_cond
l_int|0x1b
suffix:colon
l_int|0x00
)paren
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
multiline_comment|/* We want -128 to 128 we get 0-65535 */
id|decoder-&gt;bright
op_assign
id|pic-&gt;brightness
suffix:semicolon
id|vpx3220_write
c_func
(paren
id|client
comma
l_int|0xe6
comma
(paren
id|decoder-&gt;bright
op_minus
l_int|32768
)paren
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
multiline_comment|/* We want 0 to 64 we get 0-65535 */
multiline_comment|/* Bit 7 and 8 is for noise shaping */
id|decoder-&gt;contrast
op_assign
id|pic-&gt;contrast
suffix:semicolon
id|vpx3220_write
c_func
(paren
id|client
comma
l_int|0xe7
comma
(paren
id|decoder-&gt;contrast
op_rshift
l_int|10
)paren
op_plus
l_int|192
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
multiline_comment|/* We want 0 to 4096 we get 0-65535 */
id|decoder-&gt;sat
op_assign
id|pic-&gt;colour
suffix:semicolon
id|vpx3220_fp_write
c_func
(paren
id|client
comma
l_int|0xa0
comma
id|decoder-&gt;sat
op_rshift
l_int|4
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
multiline_comment|/* We want -512 to 512 we get 0-65535 */
id|decoder-&gt;hue
op_assign
id|pic-&gt;hue
suffix:semicolon
id|vpx3220_fp_write
c_func
(paren
id|client
comma
l_int|0x1c
comma
(paren
(paren
id|decoder-&gt;hue
op_minus
l_int|32768
)paren
op_rshift
l_int|6
)paren
op_amp
l_int|0xFFF
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
r_static
r_int
DECL|function|vpx3220_init_client
id|vpx3220_init_client
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
id|vpx3220_write_block
c_func
(paren
id|client
comma
id|init_common
comma
r_sizeof
(paren
id|init_common
)paren
)paren
suffix:semicolon
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_fp
comma
r_sizeof
(paren
id|init_fp
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Default to PAL */
id|vpx3220_write_fp_block
c_func
(paren
id|client
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* -----------------------------------------------------------------------&n; * Client managment code&n; */
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
id|I2C_VPX3220
op_rshift
l_int|1
comma
(paren
id|I2C_VPX3220
op_rshift
l_int|1
)paren
op_plus
l_int|4
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
DECL|variable|vpx3220_i2c_id
r_static
r_int
id|vpx3220_i2c_id
op_assign
l_int|0
suffix:semicolon
DECL|variable|vpx3220_i2c_driver
r_static
r_struct
id|i2c_driver
id|vpx3220_i2c_driver
suffix:semicolon
r_static
r_int
DECL|function|vpx3220_detach_client
id|vpx3220_detach_client
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|vpx3220
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
r_static
r_int
DECL|function|vpx3220_detect_client
id|vpx3220_detect_client
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
id|err
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_struct
id|vpx3220
op_star
id|decoder
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|VPX3220_DEBUG
l_string|&quot;%s&bslash;n&quot;
comma
id|__func__
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
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
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
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
id|vpx3220_i2c_driver
suffix:semicolon
id|client-&gt;flags
op_assign
id|I2C_CLIENT_ALLOW_USE
suffix:semicolon
id|client-&gt;id
op_assign
id|vpx3220_i2c_id
op_increment
suffix:semicolon
multiline_comment|/* Check for manufacture ID and part number */
r_if
c_cond
(paren
id|kind
OL
l_int|0
)paren
(brace
id|u8
id|id
suffix:semicolon
id|u16
id|pn
suffix:semicolon
id|id
op_assign
id|vpx3220_read
c_func
(paren
id|client
comma
l_int|0x00
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_ne
l_int|0xec
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;vpx3220_attach: Wrong manufacturer ID (0x%02x)&bslash;n&quot;
comma
id|id
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
id|pn
op_assign
(paren
id|vpx3220_read
c_func
(paren
id|client
comma
l_int|0x02
)paren
op_lshift
l_int|8
)paren
op_plus
id|vpx3220_read
c_func
(paren
id|client
comma
l_int|0x01
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pn
)paren
(brace
r_case
l_int|0x4680
suffix:colon
id|snprintf
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
r_sizeof
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
op_minus
l_int|1
comma
l_string|&quot;vpx3220a[%d]&quot;
comma
id|client-&gt;id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4260
suffix:colon
id|snprintf
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
r_sizeof
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
op_minus
l_int|1
comma
l_string|&quot;vpx3216b[%d]&quot;
comma
id|client-&gt;id
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4280
suffix:colon
id|snprintf
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
r_sizeof
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
op_minus
l_int|1
comma
l_string|&quot;vpx3214c[%d]&quot;
comma
id|client-&gt;id
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
id|KERN_INFO
l_string|&quot;%s: Wrong part number (0x%04x)&bslash;n&quot;
comma
id|__func__
comma
id|pn
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
)brace
r_else
(brace
id|snprintf
c_func
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
comma
r_sizeof
(paren
id|I2C_NAME
c_func
(paren
id|client
)paren
)paren
op_minus
l_int|1
comma
l_string|&quot;forced vpx32xx[%d]&quot;
comma
id|client-&gt;id
)paren
suffix:semicolon
)brace
id|decoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vpx3220
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
id|vpx3220
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
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|decoder
)paren
suffix:semicolon
id|err
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
id|err
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
id|err
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: vpx32xx client found at address 0x%02x&bslash;n&quot;
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
id|vpx3220_init_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|vpx3220_attach_adapter
id|vpx3220_attach_adapter
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|i2c_probe
c_func
(paren
id|adapter
comma
op_amp
id|addr_data
comma
op_amp
id|vpx3220_detect_client
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|VPX3220_DEBUG
l_string|&quot;%s: i2c_probe returned %d&bslash;n&quot;
comma
id|__func__
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* -----------------------------------------------------------------------&n; * Driver initialization and cleanup code&n; */
DECL|variable|vpx3220_i2c_driver
r_static
r_struct
id|i2c_driver
id|vpx3220_i2c_driver
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
l_string|&quot;vpx3220&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_VPX3220
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|vpx3220_attach_adapter
comma
dot
id|detach_client
op_assign
id|vpx3220_detach_client
comma
dot
id|command
op_assign
id|vpx3220_command
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|vpx3220_init
id|vpx3220_init
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|vpx3220_i2c_driver
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|vpx3220_cleanup
id|vpx3220_cleanup
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|vpx3220_i2c_driver
)paren
suffix:semicolon
)brace
DECL|variable|vpx3220_init
id|module_init
c_func
(paren
id|vpx3220_init
)paren
suffix:semicolon
DECL|variable|vpx3220_cleanup
id|module_exit
c_func
(paren
id|vpx3220_cleanup
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;vpx3220a/vpx3216b/vpx3214c video encoder driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Laurent Pinchart&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
