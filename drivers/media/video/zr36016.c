multiline_comment|/*&n; * Zoran ZR36016 basic configuration functions&n; *&n; * Copyright (C) 2001 Wolfgang Scherr &lt;scherr@net4you.at&gt;&n; *&n; * $Id: zr36016.c,v 1.1.2.14 2003/08/20 19:46:55 rbultje Exp $&n; *&n; * ------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * ------------------------------------------------------------------------&n; */
DECL|macro|ZR016_VERSION
mdefine_line|#define ZR016_VERSION &quot;v0.7&quot;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
multiline_comment|/* includes for structures and defines regarding video &n;   #include&lt;linux/videodev.h&gt; */
multiline_comment|/* I/O commands, error codes */
macro_line|#include&lt;asm/io.h&gt;
singleline_comment|//#include&lt;errno.h&gt;
multiline_comment|/* v4l  API */
macro_line|#include&lt;linux/videodev.h&gt;
multiline_comment|/* headerfile of this module */
macro_line|#include&quot;zr36016.h&quot;
multiline_comment|/* codec io API */
macro_line|#include&quot;videocodec.h&quot;
multiline_comment|/* it doesn&squot;t make sense to have more than 20 or so,&n;  just to prevent some unwanted loops */
DECL|macro|MAX_CODECS
mdefine_line|#define MAX_CODECS 20
multiline_comment|/* amount of chips attached via this driver */
DECL|variable|zr36016_codecs
r_static
r_int
id|zr36016_codecs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* debugging is available via module parameter */
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
l_string|&quot;Debug level (0-4)&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(num, format, args...) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (debug &gt;= num) &bslash;&n;&t;&t;&t;printk(format, ##args); &bslash;&n;&t;} while (0)
multiline_comment|/* =========================================================================&n;   Local hardware I/O functions:&n;&n;   read/write via codec layer (registers are located in the master device)&n;   ========================================================================= */
multiline_comment|/* read and write functions */
r_static
id|u8
DECL|function|zr36016_read
id|zr36016_read
(paren
r_struct
id|zr36016
op_star
id|ptr
comma
id|u16
id|reg
)paren
(brace
id|u8
id|value
op_assign
l_int|0
suffix:semicolon
singleline_comment|// just in case something is wrong...
r_if
c_cond
(paren
id|ptr-&gt;codec-&gt;master_data-&gt;readreg
)paren
id|value
op_assign
(paren
id|ptr-&gt;codec-&gt;master_data
op_member_access_from_pointer
id|readreg
c_func
(paren
id|ptr-&gt;codec
comma
id|reg
)paren
)paren
op_amp
l_int|0xFF
suffix:semicolon
r_else
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: invalid I/O setup, nothing read!&bslash;n&quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;%s: reading from 0x%04x: %02x&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|reg
comma
id|value
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
r_static
r_void
DECL|function|zr36016_write
id|zr36016_write
(paren
r_struct
id|zr36016
op_star
id|ptr
comma
id|u16
id|reg
comma
id|u8
id|value
)paren
(brace
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;%s: writing 0x%02x to 0x%04x&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|value
comma
id|reg
)paren
suffix:semicolon
singleline_comment|// just in case something is wrong...
r_if
c_cond
(paren
id|ptr-&gt;codec-&gt;master_data-&gt;writereg
)paren
(brace
id|ptr-&gt;codec-&gt;master_data
op_member_access_from_pointer
id|writereg
c_func
(paren
id|ptr-&gt;codec
comma
id|reg
comma
id|value
)paren
suffix:semicolon
)brace
r_else
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: invalid I/O setup, nothing written!&bslash;n&quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* indirect read and write functions */
multiline_comment|/* the 016 supports auto-addr-increment, but&n; * writing it all time cost not much and is safer... */
r_static
id|u8
DECL|function|zr36016_readi
id|zr36016_readi
(paren
r_struct
id|zr36016
op_star
id|ptr
comma
id|u16
id|reg
)paren
(brace
id|u8
id|value
op_assign
l_int|0
suffix:semicolon
singleline_comment|// just in case something is wrong...
r_if
c_cond
(paren
(paren
id|ptr-&gt;codec-&gt;master_data-&gt;writereg
)paren
op_logical_and
(paren
id|ptr-&gt;codec-&gt;master_data-&gt;readreg
)paren
)paren
(brace
id|ptr-&gt;codec-&gt;master_data
op_member_access_from_pointer
id|writereg
c_func
(paren
id|ptr-&gt;codec
comma
id|ZR016_IADDR
comma
id|reg
op_amp
l_int|0x0F
)paren
suffix:semicolon
singleline_comment|// ADDR
id|value
op_assign
(paren
id|ptr-&gt;codec-&gt;master_data
op_member_access_from_pointer
id|readreg
c_func
(paren
id|ptr-&gt;codec
comma
id|ZR016_IDATA
)paren
)paren
op_amp
l_int|0xFF
suffix:semicolon
singleline_comment|// DATA
)brace
r_else
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: invalid I/O setup, nothing read (i)!&bslash;n&quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;%s: reading indirect from 0x%04x: %02x&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|reg
comma
id|value
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
r_static
r_void
DECL|function|zr36016_writei
id|zr36016_writei
(paren
r_struct
id|zr36016
op_star
id|ptr
comma
id|u16
id|reg
comma
id|u8
id|value
)paren
(brace
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;%s: writing indirect 0x%02x to 0x%04x&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|value
comma
id|reg
)paren
suffix:semicolon
singleline_comment|// just in case something is wrong...
r_if
c_cond
(paren
id|ptr-&gt;codec-&gt;master_data-&gt;writereg
)paren
(brace
id|ptr-&gt;codec-&gt;master_data
op_member_access_from_pointer
id|writereg
c_func
(paren
id|ptr-&gt;codec
comma
id|ZR016_IADDR
comma
id|reg
op_amp
l_int|0x0F
)paren
suffix:semicolon
singleline_comment|// ADDR
id|ptr-&gt;codec-&gt;master_data
op_member_access_from_pointer
id|writereg
c_func
(paren
id|ptr-&gt;codec
comma
id|ZR016_IDATA
comma
id|value
op_amp
l_int|0x0FF
)paren
suffix:semicolon
singleline_comment|// DATA
)brace
r_else
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: invalid I/O setup, nothing written (i)!&bslash;n&quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* =========================================================================&n;   Local helper function:&n;&n;   version read&n;   ========================================================================= */
multiline_comment|/* version kept in datastructure */
r_static
id|u8
DECL|function|zr36016_read_version
id|zr36016_read_version
(paren
r_struct
id|zr36016
op_star
id|ptr
)paren
(brace
id|ptr-&gt;version
op_assign
id|zr36016_read
c_func
(paren
id|ptr
comma
l_int|0
)paren
op_rshift
l_int|4
suffix:semicolon
r_return
id|ptr-&gt;version
suffix:semicolon
)brace
multiline_comment|/* =========================================================================&n;   Local helper function:&n;&n;   basic test of &quot;connectivity&quot;, writes/reads to/from PAX-Lo register&n;   ========================================================================= */
r_static
r_int
DECL|function|zr36016_basic_test
id|zr36016_basic_test
(paren
r_struct
id|zr36016
op_star
id|ptr
)paren
(brace
r_if
c_cond
(paren
id|debug
)paren
(brace
r_int
id|i
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_LO
comma
l_int|0x55
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: registers: &quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|0x0b
suffix:semicolon
id|i
op_increment
)paren
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;%02x &quot;
comma
id|zr36016_readi
c_func
(paren
id|ptr
comma
id|i
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// for testing just write 0, then the default value to a register and read
singleline_comment|// it back in both cases 
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_LO
comma
l_int|0x00
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zr36016_readi
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_LO
)paren
op_ne
l_int|0x0
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: attach failed, can&squot;t connect to vfe processor!&bslash;n&quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_LO
comma
l_int|0x0d0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zr36016_readi
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_LO
)paren
op_ne
l_int|0x0d0
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: attach failed, can&squot;t connect to vfe processor!&bslash;n&quot;
comma
id|ptr-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
singleline_comment|// we allow version numbers from 0-3, should be enough, though
id|zr36016_read_version
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr-&gt;version
op_amp
l_int|0x0c
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;%s: attach failed, suspicious version %d found...&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|ptr-&gt;version
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* looks good! */
)brace
multiline_comment|/* =========================================================================&n;   Local helper function:&n;&n;   simple loop for pushing the init datasets - NO USE --&n;   ========================================================================= */
macro_line|#if 0
r_static
r_int
id|zr36016_pushit
(paren
r_struct
id|zr36016
op_star
id|ptr
comma
id|u16
id|startreg
comma
id|u16
id|len
comma
r_const
r_char
op_star
id|data
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_int|4
comma
l_string|&quot;%s: write data block to 0x%04x (len=%d)&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|startreg
comma
id|len
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|len
)paren
(brace
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|startreg
op_increment
comma
id|data
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* =========================================================================&n;   Basic datasets &amp; init:&n;&n;   //TODO//&n;   ========================================================================= */
singleline_comment|// needed offset values          PAL NTSC SECAM
DECL|variable|zr016_xoff
r_static
r_const
r_int
id|zr016_xoff
(braket
)braket
op_assign
(brace
l_int|20
comma
l_int|20
comma
l_int|20
)brace
suffix:semicolon
DECL|variable|zr016_yoff
r_static
r_const
r_int
id|zr016_yoff
(braket
)braket
op_assign
(brace
l_int|8
comma
l_int|9
comma
l_int|7
)brace
suffix:semicolon
r_static
r_void
DECL|function|zr36016_init
id|zr36016_init
(paren
r_struct
id|zr36016
op_star
id|ptr
)paren
(brace
singleline_comment|// stop any processing
id|zr36016_write
c_func
(paren
id|ptr
comma
id|ZR016_GOSTOP
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|// mode setup (yuv422 in and out, compression/expansuon due to mode)
id|zr36016_write
c_func
(paren
id|ptr
comma
id|ZR016_MODE
comma
id|ZR016_YUV422
op_or
id|ZR016_YUV422_YUV422
op_or
(paren
id|ptr-&gt;mode
op_eq
id|CODEC_DO_COMPRESSION
ques
c_cond
id|ZR016_COMPRESSION
suffix:colon
id|ZR016_EXPANSION
)paren
)paren
suffix:semicolon
singleline_comment|// misc setup
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_SETUP1
comma
(paren
id|ptr-&gt;xdec
ques
c_cond
(paren
id|ZR016_HRFL
op_or
id|ZR016_HORZ
)paren
suffix:colon
l_int|0
)paren
op_or
(paren
id|ptr-&gt;ydec
ques
c_cond
id|ZR016_VERT
suffix:colon
l_int|0
)paren
op_or
id|ZR016_CNTI
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_SETUP2
comma
id|ZR016_CCIR
)paren
suffix:semicolon
singleline_comment|// Window setup
singleline_comment|// (no extra offset for now, norm defines offset, default width height)
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_HI
comma
id|ptr-&gt;width
op_rshift
l_int|8
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAX_LO
comma
id|ptr-&gt;width
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAY_HI
comma
id|ptr-&gt;height
op_rshift
l_int|8
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_PAY_LO
comma
id|ptr-&gt;height
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_NAX_HI
comma
id|ptr-&gt;xoff
op_rshift
l_int|8
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_NAX_LO
comma
id|ptr-&gt;xoff
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_NAY_HI
comma
id|ptr-&gt;yoff
op_rshift
l_int|8
)paren
suffix:semicolon
id|zr36016_writei
c_func
(paren
id|ptr
comma
id|ZR016I_NAY_LO
comma
id|ptr-&gt;yoff
op_amp
l_int|0xFF
)paren
suffix:semicolon
multiline_comment|/* shall we continue now, please? */
id|zr36016_write
c_func
(paren
id|ptr
comma
id|ZR016_GOSTOP
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* =========================================================================&n;   CODEC API FUNCTIONS&n;&n;   this functions are accessed by the master via the API structure&n;   ========================================================================= */
multiline_comment|/* set compression/expansion mode and launches codec -&n;   this should be the last call from the master before starting processing */
r_static
r_int
DECL|function|zr36016_set_mode
id|zr36016_set_mode
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|mode
)paren
(brace
r_struct
id|zr36016
op_star
id|ptr
op_assign
(paren
r_struct
id|zr36016
op_star
)paren
id|codec-&gt;data
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;%s: set_mode %d call&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mode
op_ne
id|CODEC_DO_EXPANSION
)paren
op_logical_and
(paren
id|mode
op_ne
id|CODEC_DO_COMPRESSION
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ptr-&gt;mode
op_assign
id|mode
suffix:semicolon
id|zr36016_init
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* set picture size */
r_static
r_int
DECL|function|zr36016_set_video
id|zr36016_set_video
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_struct
id|tvnorm
op_star
id|norm
comma
r_struct
id|vfe_settings
op_star
id|cap
comma
r_struct
id|vfe_polarity
op_star
id|pol
)paren
(brace
r_struct
id|zr36016
op_star
id|ptr
op_assign
(paren
r_struct
id|zr36016
op_star
)paren
id|codec-&gt;data
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;%s: set_video %d.%d, %d/%d-%dx%d (0x%x) call&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|norm-&gt;HStart
comma
id|norm-&gt;VStart
comma
id|cap-&gt;x
comma
id|cap-&gt;y
comma
id|cap-&gt;width
comma
id|cap-&gt;height
comma
id|cap-&gt;decimation
)paren
suffix:semicolon
multiline_comment|/* if () return -EINVAL;&n;&t; * trust the master driver that it knows what it does - so&n;&t; * we allow invalid startx/y for now ... */
id|ptr-&gt;width
op_assign
id|cap-&gt;width
suffix:semicolon
id|ptr-&gt;height
op_assign
id|cap-&gt;height
suffix:semicolon
multiline_comment|/* (Ronald) This is ugly. zoran_device.c, line 387&n;&t; * already mentions what happens if HStart is even&n;&t; * (blue faces, etc., cr/cb inversed). There&squot;s probably&n;&t; * some good reason why HStart is 0 instead of 1, so I&squot;m&n;&t; * leaving it to this for now, but really... This can be&n;&t; * done a lot simpler */
id|ptr-&gt;xoff
op_assign
(paren
id|norm-&gt;HStart
ques
c_cond
id|norm-&gt;HStart
suffix:colon
l_int|1
)paren
op_plus
id|cap-&gt;x
suffix:semicolon
multiline_comment|/* Something to note here (I don&squot;t understand it), setting&n;&t; * VStart too high will cause the codec to &squot;not work&squot;. I&n;&t; * really don&squot;t get it. values of 16 (VStart) already break&n;&t; * it here. Just &squot;0&squot; seems to work. More testing needed! */
id|ptr-&gt;yoff
op_assign
id|norm-&gt;VStart
op_plus
id|cap-&gt;y
suffix:semicolon
multiline_comment|/* (Ronald) dzjeeh, can&squot;t this thing do hor_decimation = 4? */
id|ptr-&gt;xdec
op_assign
(paren
(paren
id|cap-&gt;decimation
op_amp
l_int|0xff
)paren
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|ptr-&gt;ydec
op_assign
(paren
(paren
(paren
id|cap-&gt;decimation
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* additional control functions */
r_static
r_int
DECL|function|zr36016_control
id|zr36016_control
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|type
comma
r_int
id|size
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|zr36016
op_star
id|ptr
op_assign
(paren
r_struct
id|zr36016
op_star
)paren
id|codec-&gt;data
suffix:semicolon
r_int
op_star
id|ival
op_assign
(paren
r_int
op_star
)paren
id|data
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;%s: control %d call with %d byte&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|type
comma
id|size
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|CODEC_G_STATUS
suffix:colon
multiline_comment|/* get last status - we don&squot;t know it ... */
r_if
c_cond
(paren
id|size
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ival
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CODEC_G_CODEC_MODE
suffix:colon
r_if
c_cond
(paren
id|size
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ival
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CODEC_S_CODEC_MODE
suffix:colon
r_if
c_cond
(paren
id|size
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ival
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* not needed, do nothing */
r_return
l_int|0
suffix:semicolon
r_case
id|CODEC_G_VFE
suffix:colon
r_case
id|CODEC_S_VFE
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|CODEC_S_MMAP
suffix:colon
multiline_comment|/* not available, give an error */
r_return
op_minus
id|ENXIO
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
multiline_comment|/* =========================================================================&n;   Exit and unregister function:&n;&n;   Deinitializes Zoran&squot;s JPEG processor&n;   ========================================================================= */
r_static
r_int
DECL|function|zr36016_unset
id|zr36016_unset
(paren
r_struct
id|videocodec
op_star
id|codec
)paren
(brace
r_struct
id|zr36016
op_star
id|ptr
op_assign
id|codec-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
(brace
multiline_comment|/* do wee need some codec deinit here, too ???? */
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;%s: finished codec #%d&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|ptr-&gt;num
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|codec-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|zr36016_codecs
op_decrement
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#else
id|module_put
c_func
(paren
id|THIS_MODULE
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* =========================================================================&n;   Setup and registry function:&n;&n;   Initializes Zoran&squot;s JPEG processor&n;&n;   Also sets pixel size, average code size, mode (compr./decompr.)&n;   (the given size is determined by the processor with the video interface)&n;   ========================================================================= */
r_static
r_int
DECL|function|zr36016_setup
id|zr36016_setup
(paren
r_struct
id|videocodec
op_star
id|codec
)paren
(brace
r_struct
id|zr36016
op_star
id|ptr
suffix:semicolon
r_int
id|res
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;zr36016: initializing VFE subsystem #%d.&bslash;n&quot;
comma
id|zr36016_codecs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zr36016_codecs
op_eq
id|MAX_CODECS
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;zr36016: Can&squot;t attach more codecs!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
singleline_comment|//mem structure init
id|codec-&gt;data
op_assign
id|ptr
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|zr36016
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|ptr
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;zr36016: Can&squot;t get enough memory!&bslash;n&quot;
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
id|ptr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|zr36016
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|ptr-&gt;name
comma
r_sizeof
(paren
id|ptr-&gt;name
)paren
comma
l_string|&quot;zr36016[%d]&quot;
comma
id|zr36016_codecs
)paren
suffix:semicolon
id|ptr-&gt;num
op_assign
id|zr36016_codecs
op_increment
suffix:semicolon
id|ptr-&gt;codec
op_assign
id|codec
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_ERR
l_string|&quot;zr36016: failed to increase module use count&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|zr36016_codecs
op_decrement
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif
singleline_comment|//testing
id|res
op_assign
id|zr36016_basic_test
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|zr36016_unset
c_func
(paren
id|codec
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
singleline_comment|//final setup
id|ptr-&gt;mode
op_assign
id|CODEC_DO_COMPRESSION
suffix:semicolon
id|ptr-&gt;width
op_assign
l_int|768
suffix:semicolon
id|ptr-&gt;height
op_assign
l_int|288
suffix:semicolon
id|ptr-&gt;xdec
op_assign
l_int|1
suffix:semicolon
id|ptr-&gt;ydec
op_assign
l_int|0
suffix:semicolon
id|zr36016_init
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
id|KERN_INFO
l_string|&quot;%s: codec v%d attached and running&bslash;n&quot;
comma
id|ptr-&gt;name
comma
id|ptr-&gt;version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|zr36016_codec
r_static
r_const
r_struct
id|videocodec
id|zr36016_codec
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;zr36016&quot;
comma
dot
id|magic
op_assign
l_int|0L
comma
singleline_comment|// magic not used
dot
id|flags
op_assign
id|CODEC_FLAG_HARDWARE
op_or
id|CODEC_FLAG_VFE
op_or
id|CODEC_FLAG_ENCODER
op_or
id|CODEC_FLAG_DECODER
comma
dot
id|type
op_assign
id|CODEC_TYPE_ZR36016
comma
dot
id|setup
op_assign
id|zr36016_setup
comma
singleline_comment|// functionality
dot
id|unset
op_assign
id|zr36016_unset
comma
dot
id|set_mode
op_assign
id|zr36016_set_mode
comma
dot
id|set_video
op_assign
id|zr36016_set_video
comma
dot
id|control
op_assign
id|zr36016_control
comma
singleline_comment|// others are not used
)brace
suffix:semicolon
multiline_comment|/* =========================================================================&n;   HOOK IN DRIVER AS KERNEL MODULE&n;   ========================================================================= */
r_static
r_int
id|__init
DECL|function|zr36016_init_module
id|zr36016_init_module
(paren
r_void
)paren
(brace
singleline_comment|//dprintk(1, &quot;ZR36016 driver %s&bslash;n&quot;,ZR016_VERSION);
id|zr36016_codecs
op_assign
l_int|0
suffix:semicolon
r_return
id|videocodec_register
c_func
(paren
op_amp
id|zr36016_codec
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|zr36016_cleanup_module
id|zr36016_cleanup_module
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|zr36016_codecs
)paren
(brace
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;zr36016: something&squot;s wrong - %d codecs left somehow.&bslash;n&quot;
comma
id|zr36016_codecs
)paren
suffix:semicolon
)brace
id|videocodec_unregister
c_func
(paren
op_amp
id|zr36016_codec
)paren
suffix:semicolon
)brace
DECL|variable|zr36016_init_module
id|module_init
c_func
(paren
id|zr36016_init_module
)paren
suffix:semicolon
DECL|variable|zr36016_cleanup_module
id|module_exit
c_func
(paren
id|zr36016_cleanup_module
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Wolfgang Scherr &lt;scherr@net4you.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver module for ZR36016 video frontends &quot;
id|ZR016_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
