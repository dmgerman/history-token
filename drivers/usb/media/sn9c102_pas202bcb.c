multiline_comment|/***************************************************************************&n; * Plug-in for PAS202BCB image sensor connected to the SN9C10x PC Camera   *&n; * Controllers                                                             *&n; *                                                                         *&n; * Copyright (C) 2004 by Carlos Eduardo Medaglia Dyonisio                  *&n; *                       &lt;medaglia@undl.org.br&gt;                            *&n; *                       http://cadu.homelinux.com:8080/                   *&n; *                                                                         *&n; * DAC Magnitude, exposure and green gain controls added by                *&n; * Luca Risolia &lt;luca.risolia@studio.unibo.it&gt;                             *&n; *                                                                         *&n; * This program is free software; you can redistribute it and/or modify    *&n; * it under the terms of the GNU General Public License as published by    *&n; * the Free Software Foundation; either version 2 of the License, or       *&n; * (at your option) any later version.                                     *&n; *                                                                         *&n; * This program is distributed in the hope that it will be useful,         *&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of          *&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *&n; * GNU General Public License for more details.                            *&n; *                                                                         *&n; * You should have received a copy of the GNU General Public License       *&n; * along with this program; if not, write to the Free Software             *&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *&n; ***************************************************************************/
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;sn9c102_sensor.h&quot;
DECL|variable|pas202bcb
r_static
r_struct
id|sn9c102_sensor
id|pas202bcb
suffix:semicolon
DECL|function|pas202bcb_init
r_static
r_int
id|pas202bcb_init
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x00
comma
l_int|0x10
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x00
comma
l_int|0x11
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x00
comma
l_int|0x14
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x20
comma
l_int|0x17
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x30
comma
l_int|0x19
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x09
comma
l_int|0x18
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x02
comma
l_int|0x14
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x03
comma
l_int|0x40
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x0d
comma
l_int|0x2c
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x0e
comma
l_int|0x01
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x0f
comma
l_int|0xa9
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x10
comma
l_int|0x08
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x13
comma
l_int|0x63
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x15
comma
l_int|0x70
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x11
comma
l_int|0x01
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|400
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|pas202bcb_get_ctrl
r_static
r_int
id|pas202bcb_get_ctrl
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_struct
id|v4l2_control
op_star
id|ctrl
)paren
(brace
r_switch
c_cond
(paren
id|ctrl-&gt;id
)paren
(brace
r_case
id|V4L2_CID_EXPOSURE
suffix:colon
(brace
r_int
id|r1
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x04
)paren
comma
id|r2
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x05
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r1
OL
l_int|0
op_logical_or
id|r2
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ctrl-&gt;value
op_assign
(paren
id|r1
op_lshift
l_int|6
)paren
op_or
(paren
id|r2
op_amp
l_int|0x3f
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|V4L2_CID_RED_BALANCE
suffix:colon
r_if
c_cond
(paren
(paren
id|ctrl-&gt;value
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x09
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ctrl-&gt;value
op_and_assign
l_int|0x0f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|V4L2_CID_BLUE_BALANCE
suffix:colon
r_if
c_cond
(paren
(paren
id|ctrl-&gt;value
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x07
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ctrl-&gt;value
op_and_assign
l_int|0x0f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|V4L2_CID_GAIN
suffix:colon
r_if
c_cond
(paren
(paren
id|ctrl-&gt;value
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x10
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ctrl-&gt;value
op_and_assign
l_int|0x1f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SN9C102_V4L2_CID_GREEN_BALANCE
suffix:colon
r_if
c_cond
(paren
(paren
id|ctrl-&gt;value
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x08
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ctrl-&gt;value
op_and_assign
l_int|0x0f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SN9C102_V4L2_CID_DAC_MAGNITUDE
suffix:colon
r_if
c_cond
(paren
(paren
id|ctrl-&gt;value
op_assign
id|sn9c102_i2c_read
c_func
(paren
id|cam
comma
l_int|0x0c
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|pas202bcb_set_pix_format
r_static
r_int
id|pas202bcb_set_pix_format
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_const
r_struct
id|v4l2_pix_format
op_star
id|pix
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pix-&gt;pixelformat
op_eq
id|V4L2_PIX_FMT_SN9C10X
)paren
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x24
comma
l_int|0x17
)paren
suffix:semicolon
r_else
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x20
comma
l_int|0x17
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|pas202bcb_set_ctrl
r_static
r_int
id|pas202bcb_set_ctrl
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_const
r_struct
id|v4l2_control
op_star
id|ctrl
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|ctrl-&gt;id
)paren
(brace
r_case
id|V4L2_CID_EXPOSURE
suffix:colon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x04
comma
id|ctrl-&gt;value
op_rshift
l_int|6
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x05
comma
id|ctrl-&gt;value
op_amp
l_int|0x3f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|V4L2_CID_RED_BALANCE
suffix:colon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x09
comma
id|ctrl-&gt;value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|V4L2_CID_BLUE_BALANCE
suffix:colon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x07
comma
id|ctrl-&gt;value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|V4L2_CID_GAIN
suffix:colon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x10
comma
id|ctrl-&gt;value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SN9C102_V4L2_CID_GREEN_BALANCE
suffix:colon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x08
comma
id|ctrl-&gt;value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SN9C102_V4L2_CID_DAC_MAGNITUDE
suffix:colon
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x0c
comma
id|ctrl-&gt;value
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
id|err
op_add_assign
id|sn9c102_i2c_write
c_func
(paren
id|cam
comma
l_int|0x11
comma
l_int|0x01
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|pas202bcb_set_crop
r_static
r_int
id|pas202bcb_set_crop
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_const
r_struct
id|v4l2_rect
op_star
id|rect
)paren
(brace
r_struct
id|sn9c102_sensor
op_star
id|s
op_assign
op_amp
id|pas202bcb
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|u8
id|h_start
op_assign
(paren
id|u8
)paren
(paren
id|rect-&gt;left
op_minus
id|s-&gt;cropcap.bounds.left
)paren
op_plus
l_int|4
comma
id|v_start
op_assign
(paren
id|u8
)paren
(paren
id|rect-&gt;top
op_minus
id|s-&gt;cropcap.bounds.top
)paren
op_plus
l_int|3
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
id|h_start
comma
l_int|0x12
)paren
suffix:semicolon
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
id|v_start
comma
l_int|0x13
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|pas202bcb
r_static
r_struct
id|sn9c102_sensor
id|pas202bcb
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PAS202BCB&quot;
comma
dot
id|maintainer
op_assign
l_string|&quot;Carlos Eduardo Medaglia Dyonisio &quot;
l_string|&quot;&lt;medaglia@undl.org.br&gt;&quot;
comma
dot
id|sysfs_ops
op_assign
id|SN9C102_I2C_READ
op_or
id|SN9C102_I2C_WRITE
comma
dot
id|frequency
op_assign
id|SN9C102_I2C_400KHZ
op_or
id|SN9C102_I2C_100KHZ
comma
dot
id|interface
op_assign
id|SN9C102_I2C_2WIRES
comma
dot
id|i2c_slave_id
op_assign
l_int|0x40
comma
dot
id|init
op_assign
op_amp
id|pas202bcb_init
comma
dot
id|qctrl
op_assign
(brace
(brace
dot
id|id
op_assign
id|V4L2_CID_EXPOSURE
comma
dot
id|type
op_assign
id|V4L2_CTRL_TYPE_INTEGER
comma
dot
id|name
op_assign
l_string|&quot;exposure&quot;
comma
dot
id|minimum
op_assign
l_int|0x01e5
comma
dot
id|maximum
op_assign
l_int|0x3fff
comma
dot
id|step
op_assign
l_int|0x0001
comma
dot
id|default_value
op_assign
l_int|0x01e5
comma
dot
id|flags
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|id
op_assign
id|V4L2_CID_GAIN
comma
dot
id|type
op_assign
id|V4L2_CTRL_TYPE_INTEGER
comma
dot
id|name
op_assign
l_string|&quot;global gain&quot;
comma
dot
id|minimum
op_assign
l_int|0x00
comma
dot
id|maximum
op_assign
l_int|0x1f
comma
dot
id|step
op_assign
l_int|0x01
comma
dot
id|default_value
op_assign
l_int|0x0c
comma
dot
id|flags
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|id
op_assign
id|V4L2_CID_RED_BALANCE
comma
dot
id|type
op_assign
id|V4L2_CTRL_TYPE_INTEGER
comma
dot
id|name
op_assign
l_string|&quot;red balance&quot;
comma
dot
id|minimum
op_assign
l_int|0x00
comma
dot
id|maximum
op_assign
l_int|0x0f
comma
dot
id|step
op_assign
l_int|0x01
comma
dot
id|default_value
op_assign
l_int|0x01
comma
dot
id|flags
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|id
op_assign
id|V4L2_CID_BLUE_BALANCE
comma
dot
id|type
op_assign
id|V4L2_CTRL_TYPE_INTEGER
comma
dot
id|name
op_assign
l_string|&quot;blue balance&quot;
comma
dot
id|minimum
op_assign
l_int|0x00
comma
dot
id|maximum
op_assign
l_int|0x0f
comma
dot
id|step
op_assign
l_int|0x01
comma
dot
id|default_value
op_assign
l_int|0x05
comma
dot
id|flags
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|id
op_assign
id|SN9C102_V4L2_CID_GREEN_BALANCE
comma
dot
id|type
op_assign
id|V4L2_CTRL_TYPE_INTEGER
comma
dot
id|name
op_assign
l_string|&quot;green balance&quot;
comma
dot
id|minimum
op_assign
l_int|0x00
comma
dot
id|maximum
op_assign
l_int|0x0f
comma
dot
id|step
op_assign
l_int|0x01
comma
dot
id|default_value
op_assign
l_int|0x00
comma
dot
id|flags
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|id
op_assign
id|SN9C102_V4L2_CID_DAC_MAGNITUDE
comma
dot
id|type
op_assign
id|V4L2_CTRL_TYPE_INTEGER
comma
dot
id|name
op_assign
l_string|&quot;DAC magnitude&quot;
comma
dot
id|minimum
op_assign
l_int|0x00
comma
dot
id|maximum
op_assign
l_int|0xff
comma
dot
id|step
op_assign
l_int|0x01
comma
dot
id|default_value
op_assign
l_int|0x04
comma
dot
id|flags
op_assign
l_int|0
comma
)brace
comma
)brace
comma
dot
id|get_ctrl
op_assign
op_amp
id|pas202bcb_get_ctrl
comma
dot
id|set_ctrl
op_assign
op_amp
id|pas202bcb_set_ctrl
comma
dot
id|cropcap
op_assign
(brace
dot
id|bounds
op_assign
(brace
dot
id|left
op_assign
l_int|0
comma
dot
id|top
op_assign
l_int|0
comma
dot
id|width
op_assign
l_int|640
comma
dot
id|height
op_assign
l_int|480
comma
)brace
comma
dot
id|defrect
op_assign
(brace
dot
id|left
op_assign
l_int|0
comma
dot
id|top
op_assign
l_int|0
comma
dot
id|width
op_assign
l_int|640
comma
dot
id|height
op_assign
l_int|480
comma
)brace
comma
)brace
comma
dot
id|set_crop
op_assign
op_amp
id|pas202bcb_set_crop
comma
dot
id|pix_format
op_assign
(brace
dot
id|width
op_assign
l_int|640
comma
dot
id|height
op_assign
l_int|480
comma
dot
id|pixelformat
op_assign
id|V4L2_PIX_FMT_SBGGR8
comma
dot
id|priv
op_assign
l_int|8
comma
)brace
comma
dot
id|set_pix_format
op_assign
op_amp
id|pas202bcb_set_pix_format
)brace
suffix:semicolon
DECL|function|sn9c102_probe_pas202bcb
r_int
id|sn9c102_probe_pas202bcb
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
)paren
(brace
r_int
id|r0
op_assign
l_int|0
comma
id|r1
op_assign
l_int|0
comma
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *  Minimal initialization to enable the I2C communication&n;&t; *  NOTE: do NOT change the values!&n;&t; */
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x01
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* sensor power down */
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x40
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* sensor power on */
id|err
op_add_assign
id|sn9c102_write_reg
c_func
(paren
id|cam
comma
l_int|0x28
comma
l_int|0x17
)paren
suffix:semicolon
multiline_comment|/* sensor clock at 24 MHz */
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|r0
op_assign
id|sn9c102_i2c_try_read
c_func
(paren
id|cam
comma
op_amp
id|pas202bcb
comma
l_int|0x00
)paren
suffix:semicolon
id|r1
op_assign
id|sn9c102_i2c_try_read
c_func
(paren
id|cam
comma
op_amp
id|pas202bcb
comma
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r0
OL
l_int|0
op_logical_or
id|r1
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|pid
op_assign
(paren
id|r0
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|r1
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ne
l_int|0x017
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sn9c102_attach_sensor
c_func
(paren
id|cam
comma
op_amp
id|pas202bcb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
