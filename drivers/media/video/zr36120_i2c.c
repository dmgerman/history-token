multiline_comment|/*&n;    zr36120_i2c.c - Zoran 36120/36125 based framegrabbers&n;&n;    Copyright (C) 1998-1999 Pauline Middelink &lt;middelin@polyware.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/video_decoder.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;tuner.h&quot;
macro_line|#include &quot;zr36120.h&quot;
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* I2C functions&t;&t;&t;&t;&t;&t;&t;   */
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* software I2C functions */
DECL|macro|I2C_DELAY
mdefine_line|#define I2C_DELAY   10
DECL|function|i2c_setlines
r_static
r_void
id|i2c_setlines
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|ctrl
comma
r_int
id|data
)paren
(brace
r_struct
id|zoran
op_star
id|ztv
op_assign
(paren
r_struct
id|zoran
op_star
)paren
id|bus-&gt;data
suffix:semicolon
r_int
r_int
id|b
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|b
op_or_assign
id|ztv-&gt;card-&gt;swapi2c
ques
c_cond
id|ZORAN_I2C_SCL
suffix:colon
id|ZORAN_I2C_SDA
suffix:semicolon
r_if
c_cond
(paren
id|ctrl
)paren
id|b
op_or_assign
id|ztv-&gt;card-&gt;swapi2c
ques
c_cond
id|ZORAN_I2C_SDA
suffix:colon
id|ZORAN_I2C_SCL
suffix:semicolon
id|zrwrite
c_func
(paren
id|b
comma
id|ZORAN_I2C
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|I2C_DELAY
)paren
suffix:semicolon
)brace
DECL|function|i2c_getdataline
r_static
r_int
id|i2c_getdataline
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
)paren
(brace
r_struct
id|zoran
op_star
id|ztv
op_assign
(paren
r_struct
id|zoran
op_star
)paren
id|bus-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|ztv-&gt;card-&gt;swapi2c
)paren
r_return
id|zrread
c_func
(paren
id|ZORAN_I2C
)paren
op_amp
id|ZORAN_I2C_SCL
suffix:semicolon
r_return
id|zrread
c_func
(paren
id|ZORAN_I2C
)paren
op_amp
id|ZORAN_I2C_SDA
suffix:semicolon
)brace
r_static
DECL|function|attach_inform
r_void
id|attach_inform
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|id
)paren
(brace
r_struct
id|zoran
op_star
id|ztv
op_assign
(paren
r_struct
id|zoran
op_star
)paren
id|bus-&gt;data
suffix:semicolon
r_struct
id|video_decoder_capability
id|dc
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
id|I2C_DRIVERID_VIDEODECODER
suffix:colon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_INFO
l_string|&quot;decoder attached&bslash;n&quot;
comma
id|CARD
)paren
)paren
suffix:semicolon
multiline_comment|/* fetch the capabilites of the decoder */
id|rv
op_assign
id|i2c_control_device
c_func
(paren
op_amp
id|ztv-&gt;i2c
comma
id|I2C_DRIVERID_VIDEODECODER
comma
id|DECODER_GET_CAPABILITIES
comma
op_amp
id|dc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_DEBUG
l_string|&quot;decoder is not V4L aware!&bslash;n&quot;
comma
id|CARD
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_DEBUG
l_string|&quot;capabilities %d %d %d&bslash;n&quot;
comma
id|CARD
comma
id|dc.flags
comma
id|dc.inputs
comma
id|dc.outputs
)paren
)paren
suffix:semicolon
multiline_comment|/* Test if the decoder can de VBI transfers */
r_if
c_cond
(paren
id|dc.flags
op_amp
l_int|16
multiline_comment|/*VIDEO_DECODER_VBI*/
)paren
id|ztv-&gt;have_decoder
op_assign
l_int|2
suffix:semicolon
r_else
id|ztv-&gt;have_decoder
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_DRIVERID_TUNER
suffix:colon
id|ztv-&gt;have_tuner
op_assign
l_int|1
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_INFO
l_string|&quot;tuner attached&bslash;n&quot;
comma
id|CARD
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ztv-&gt;tuner_type
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_control_device
c_func
(paren
op_amp
id|ztv-&gt;i2c
comma
id|I2C_DRIVERID_TUNER
comma
id|TUNER_SET_TYPE
comma
op_amp
id|ztv-&gt;tuner_type
)paren
OL
l_int|0
)paren
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_INFO
l_string|&quot;attach_inform; tuner won&squot;t be set to type %d&bslash;n&quot;
comma
id|CARD
comma
id|ztv-&gt;tuner_type
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
id|CARD_INFO
l_string|&quot;attach_inform; unknown device id=%d&bslash;n&quot;
comma
id|CARD
comma
id|id
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
DECL|function|detach_inform
r_void
id|detach_inform
c_func
(paren
r_struct
id|i2c_bus
op_star
id|bus
comma
r_int
id|id
)paren
(brace
r_struct
id|zoran
op_star
id|ztv
op_assign
(paren
r_struct
id|zoran
op_star
)paren
id|bus-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
id|I2C_DRIVERID_VIDEODECODER
suffix:colon
id|ztv-&gt;have_decoder
op_assign
l_int|0
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_INFO
l_string|&quot;decoder detached&bslash;n&quot;
comma
id|CARD
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_DRIVERID_TUNER
suffix:colon
id|ztv-&gt;have_tuner
op_assign
l_int|0
suffix:semicolon
id|DEBUG
c_func
(paren
id|printk
c_func
(paren
id|CARD_INFO
l_string|&quot;tuner detached&bslash;n&quot;
comma
id|CARD
)paren
)paren
suffix:semicolon
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
id|CARD_INFO
l_string|&quot;detach_inform; unknown device id=%d&bslash;n&quot;
comma
id|CARD
comma
id|id
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|zoran_i2c_bus_template
r_struct
id|i2c_bus
id|zoran_i2c_bus_template
op_assign
(brace
l_string|&quot;ZR36120&quot;
comma
id|I2C_BUSID_ZORAN
comma
l_int|NULL
comma
id|SPIN_LOCK_UNLOCKED
comma
id|attach_inform
comma
id|detach_inform
comma
id|i2c_setlines
comma
id|i2c_getdataline
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
eof
