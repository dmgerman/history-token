multiline_comment|/*&n; * budget-av.c: driver for the SAA7146 based Budget DVB cards&n; *              with analog video in &n; *&n; * Compiled from various sources by Michael Hunold &lt;michael@mihu.de&gt; &n; *&n; * Copyright (C) 2002 Ralph Metzler &lt;rjkm@metzlerbros.de&gt;&n; *&n; * Copyright (C) 1999-2002 Ralph  Metzler &n; *                       &amp; Marcus Metzler for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; *&n; * the project&squot;s page is at http://www.linuxtv.org/dvb/&n; */
macro_line|#include &lt;media/saa7146_vv.h&gt;
macro_line|#include &quot;budget.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|struct|budget_av
r_struct
id|budget_av
(brace
DECL|member|budget
r_struct
id|budget
id|budget
suffix:semicolon
DECL|member|vd
r_struct
id|video_device
id|vd
suffix:semicolon
DECL|member|cur_input
r_int
id|cur_input
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****************************************************************************&n; * INITIALIZATION&n; ****************************************************************************/
DECL|function|i2c_readreg
r_static
id|u8
id|i2c_readreg
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
id|id
comma
id|u8
id|reg
)paren
(brace
id|u8
id|mm1
(braket
)braket
op_assign
(brace
l_int|0x00
)brace
suffix:semicolon
id|u8
id|mm2
(braket
)braket
op_assign
(brace
l_int|0x00
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
(braket
l_int|2
)braket
suffix:semicolon
id|msgs
(braket
l_int|0
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|msgs
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|I2C_M_RD
suffix:semicolon
id|msgs
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|msgs
(braket
l_int|1
)braket
dot
id|addr
op_assign
id|id
op_div
l_int|2
suffix:semicolon
id|mm1
(braket
l_int|0
)braket
op_assign
id|reg
suffix:semicolon
id|msgs
(braket
l_int|0
)braket
dot
id|len
op_assign
l_int|1
suffix:semicolon
id|msgs
(braket
l_int|1
)braket
dot
id|len
op_assign
l_int|1
suffix:semicolon
id|msgs
(braket
l_int|0
)braket
dot
id|buf
op_assign
id|mm1
suffix:semicolon
id|msgs
(braket
l_int|1
)braket
dot
id|buf
op_assign
id|mm2
suffix:semicolon
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
id|msgs
comma
l_int|2
)paren
suffix:semicolon
r_return
id|mm2
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|i2c_writereg
r_static
r_int
id|i2c_writereg
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u8
id|id
comma
id|u8
id|reg
comma
id|u8
id|val
)paren
(brace
id|u8
id|msg
(braket
l_int|2
)braket
op_assign
initialization_block
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
suffix:semicolon
id|msgs.flags
op_assign
l_int|0
suffix:semicolon
id|msgs.addr
op_assign
id|id
op_div
l_int|2
suffix:semicolon
id|msgs.len
op_assign
l_int|2
suffix:semicolon
id|msgs.buf
op_assign
id|msg
suffix:semicolon
r_return
id|i2c-&gt;xfer
(paren
id|i2c
comma
op_amp
id|msgs
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|saa7113_tab
r_static
r_const
id|u8
id|saa7113_tab
(braket
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x08
comma
l_int|0x02
comma
l_int|0xc0
comma
l_int|0x03
comma
l_int|0x33
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x05
comma
l_int|0x00
comma
l_int|0x06
comma
l_int|0xeb
comma
l_int|0x07
comma
l_int|0xe0
comma
l_int|0x08
comma
l_int|0x28
comma
l_int|0x09
comma
l_int|0x00
comma
l_int|0x0a
comma
l_int|0x80
comma
l_int|0x0b
comma
l_int|0x47
comma
l_int|0x0c
comma
l_int|0x40
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x0e
comma
l_int|0x01
comma
l_int|0x0f
comma
l_int|0x44
comma
l_int|0x10
comma
l_int|0x08
comma
l_int|0x11
comma
l_int|0x0c
comma
l_int|0x12
comma
l_int|0x7b
comma
l_int|0x13
comma
l_int|0x00
comma
l_int|0x15
comma
l_int|0x00
comma
l_int|0x16
comma
l_int|0x00
comma
l_int|0x17
comma
l_int|0x00
comma
l_int|0x57
comma
l_int|0xff
comma
l_int|0x40
comma
l_int|0x82
comma
l_int|0x58
comma
l_int|0x00
comma
l_int|0x59
comma
l_int|0x54
comma
l_int|0x5a
comma
l_int|0x07
comma
l_int|0x5b
comma
l_int|0x83
comma
l_int|0x5e
comma
l_int|0x00
comma
l_int|0xff
)brace
suffix:semicolon
DECL|function|saa7113_init
r_static
r_int
id|saa7113_init
(paren
r_struct
id|budget_av
op_star
id|budget_av
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
op_amp
id|budget_av-&gt;budget
suffix:semicolon
r_const
id|u8
op_star
id|data
op_assign
id|saa7113_tab
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writereg
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
l_int|0x01
comma
l_int|0x08
)paren
op_ne
l_int|1
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;saa7113: not found on KNC card&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|INFO
c_func
(paren
(paren
l_string|&quot;saa7113: detected and initializing&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|data
op_ne
l_int|0xff
)paren
(brace
id|i2c_writereg
c_func
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
op_star
id|data
comma
op_star
(paren
id|data
op_plus
l_int|1
)paren
)paren
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
)brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;saa7113: status=%02x&bslash;n&quot;
comma
id|i2c_readreg
c_func
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
l_int|0x1f
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7113_setinput
r_static
r_int
id|saa7113_setinput
(paren
r_struct
id|budget_av
op_star
id|budget_av
comma
r_int
id|input
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
op_amp
id|budget_av-&gt;budget
suffix:semicolon
r_if
c_cond
(paren
id|input
op_eq
l_int|1
)paren
(brace
id|i2c_writereg
c_func
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
l_int|0x02
comma
l_int|0xc7
)paren
suffix:semicolon
id|i2c_writereg
c_func
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
l_int|0x09
comma
l_int|0x80
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|input
op_eq
l_int|0
)paren
(brace
id|i2c_writereg
c_func
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
l_int|0x02
comma
l_int|0xc0
)paren
suffix:semicolon
id|i2c_writereg
c_func
(paren
id|budget-&gt;i2c_bus
comma
l_int|0x4a
comma
l_int|0x09
comma
l_int|0x00
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
id|budget_av-&gt;cur_input
op_assign
id|input
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_av_detach
r_static
r_int
id|budget_av_detach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|budget_av
op_star
id|budget_av
op_assign
(paren
r_struct
id|budget_av
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
r_int
id|err
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev: %p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|0
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
id|dvb_delay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|saa7146_unregister_device
(paren
op_amp
id|budget_av-&gt;vd
comma
id|dev
)paren
suffix:semicolon
id|err
op_assign
id|ttpci_budget_deinit
(paren
op_amp
id|budget_av-&gt;budget
)paren
suffix:semicolon
id|kfree
(paren
id|budget_av
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|vv_data
r_static
r_struct
id|saa7146_ext_vv
id|vv_data
suffix:semicolon
DECL|function|budget_av_attach
r_static
r_int
id|budget_av_attach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_pci_extension_data
op_star
id|info
)paren
(brace
r_struct
id|budget_av
op_star
id|budget_av
suffix:semicolon
r_struct
id|budget_info
op_star
id|bi
op_assign
id|info-&gt;ext_priv
suffix:semicolon
r_int
id|err
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev: %p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bi-&gt;type
op_ne
id|BUDGET_KNC1
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|budget_av
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|budget_av
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|budget_av
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|budget_av
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ttpci_budget_init
c_func
(paren
op_amp
id|budget_av-&gt;budget
comma
id|dev
comma
id|info
)paren
)paren
)paren
(brace
id|kfree
c_func
(paren
id|budget_av
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|dev-&gt;ext_priv
op_assign
id|budget_av
suffix:semicolon
multiline_comment|/* knc1 initialization */
id|saa7146_write
c_func
(paren
id|dev
comma
id|DD1_STREAM_B
comma
l_int|0x04000000
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|DD1_INIT
comma
l_int|0x07000600
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
id|MASK_09
op_or
id|MASK_25
op_or
id|MASK_10
op_or
id|MASK_26
)paren
suffix:semicolon
singleline_comment|//test_knc_ci(av7110);
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|0
comma
id|SAA7146_GPIO_OUTHI
)paren
suffix:semicolon
id|dvb_delay
c_func
(paren
l_int|500
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|saa7113_init
(paren
id|budget_av
)paren
)paren
)paren
(brace
multiline_comment|/* fixme: proper cleanup here */
id|ERR
c_func
(paren
(paren
l_string|&quot;cannot init saa7113.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_vv_init
c_func
(paren
id|dev
comma
op_amp
id|vv_data
)paren
)paren
(brace
multiline_comment|/* fixme: proper cleanup here */
id|ERR
c_func
(paren
(paren
l_string|&quot;cannot init vv subsystem.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|saa7146_register_device
c_func
(paren
op_amp
id|budget_av-&gt;vd
comma
id|dev
comma
l_string|&quot;knc1&quot;
comma
id|VFL_TYPE_GRABBER
)paren
)paren
)paren
(brace
multiline_comment|/* fixme: proper cleanup here */
id|ERR
c_func
(paren
(paren
l_string|&quot;cannot register capture v4l2 device.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* beware: this modifies dev-&gt;vv ... */
id|saa7146_set_hps_source_and_sync
c_func
(paren
id|dev
comma
id|SAA7146_HPS_SOURCE_PORT_A
comma
id|SAA7146_HPS_SYNC_PORT_A
)paren
suffix:semicolon
id|saa7113_setinput
(paren
id|budget_av
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* what is this? since we don&squot;t support open()/close()&n;&t;   notifications, we simply put this into the release handler... */
multiline_comment|/*&n;&t;saa7146_setgpio(dev, 0, SAA7146_GPIO_OUTLO);&n;&t;set_current_state(TASK_INTERRUPTIBLE);&n;&t;schedule_timeout (20);&n;*/
multiline_comment|/* fixme: find some sane values here... */
id|saa7146_write
c_func
(paren
id|dev
comma
id|PCI_BT_V1
comma
l_int|0x1c00101f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|KNC1_INPUTS
mdefine_line|#define KNC1_INPUTS 2
DECL|variable|knc1_inputs
r_static
r_struct
id|v4l2_input
id|knc1_inputs
(braket
id|KNC1_INPUTS
)braket
op_assign
(brace
(brace
l_int|0
comma
l_string|&quot;Composite&quot;
comma
id|V4L2_INPUT_TYPE_TUNER
comma
l_int|1
comma
l_int|0
comma
id|V4L2_STD_PAL_BG
op_or
id|V4L2_STD_NTSC_M
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_string|&quot;S-Video&quot;
comma
id|V4L2_INPUT_TYPE_CAMERA
comma
l_int|2
comma
l_int|0
comma
id|V4L2_STD_PAL_BG
op_or
id|V4L2_STD_NTSC_M
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|ioctls
r_static
r_struct
id|saa7146_extension_ioctls
id|ioctls
(braket
)braket
op_assign
(brace
(brace
id|VIDIOC_ENUMINPUT
comma
id|SAA7146_EXCLUSIVE
)brace
comma
(brace
id|VIDIOC_G_INPUT
comma
id|SAA7146_EXCLUSIVE
)brace
comma
(brace
id|VIDIOC_S_INPUT
comma
id|SAA7146_EXCLUSIVE
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|av_ioctl
r_static
r_int
id|av_ioctl
c_func
(paren
r_struct
id|saa7146_fh
op_star
id|fh
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
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_struct
id|budget_av
op_star
id|budget_av
op_assign
(paren
r_struct
id|budget_av
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
multiline_comment|/*&n;&t;struct saa7146_vv *vv = dev-&gt;vv_data; &n;*/
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOC_ENUMINPUT
suffix:colon
(brace
r_struct
id|v4l2_input
op_star
id|i
op_assign
id|arg
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;VIDIOC_ENUMINPUT %d.&bslash;n&quot;
comma
id|i-&gt;index
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;index
OL
l_int|0
op_logical_or
id|i-&gt;index
op_ge
id|KNC1_INPUTS
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|i
comma
op_amp
id|knc1_inputs
(braket
id|i-&gt;index
)braket
comma
r_sizeof
(paren
r_struct
id|v4l2_input
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_G_INPUT
suffix:colon
(brace
r_int
op_star
id|input
op_assign
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
op_star
id|input
op_assign
id|budget_av-&gt;cur_input
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;VIDIOC_G_INPUT %d.&bslash;n&quot;
comma
op_star
id|input
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_S_INPUT
suffix:colon
(brace
r_int
id|input
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;VIDIOC_S_INPUT %d.&bslash;n&quot;
comma
id|input
)paren
)paren
suffix:semicolon
r_return
id|saa7113_setinput
(paren
id|budget_av
comma
id|input
)paren
suffix:semicolon
)brace
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;DEB2(printk(&quot;does not handle this ioctl.&bslash;n&quot;));&n;*/
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|standard
r_static
r_struct
id|saa7146_standard
id|standard
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;PAL&quot;
comma
dot
id|id
op_assign
id|V4L2_STD_PAL
comma
dot
id|v_offset
op_assign
l_int|0x17
comma
dot
id|v_field
op_assign
l_int|288
comma
dot
id|v_calc
op_assign
l_int|576
comma
dot
id|h_offset
op_assign
l_int|0x14
comma
dot
id|h_pixels
op_assign
l_int|680
comma
dot
id|h_calc
op_assign
l_int|680
op_plus
l_int|1
comma
dot
id|v_max_out
op_assign
l_int|576
comma
dot
id|h_max_out
op_assign
l_int|768
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;NTSC&quot;
comma
dot
id|id
op_assign
id|V4L2_STD_NTSC
comma
dot
id|v_offset
op_assign
l_int|0x16
comma
dot
id|v_field
op_assign
l_int|240
comma
dot
id|v_calc
op_assign
l_int|480
comma
dot
id|h_offset
op_assign
l_int|0x06
comma
dot
id|h_pixels
op_assign
l_int|708
comma
dot
id|h_calc
op_assign
l_int|708
op_plus
l_int|1
comma
dot
id|v_max_out
op_assign
l_int|480
comma
dot
id|h_max_out
op_assign
l_int|640
comma
)brace
)brace
suffix:semicolon
DECL|variable|vv_data
r_static
r_struct
id|saa7146_ext_vv
id|vv_data
op_assign
(brace
dot
id|inputs
op_assign
l_int|2
comma
dot
id|capabilities
op_assign
l_int|0
comma
singleline_comment|// perhaps later: V4L2_CAP_VBI_CAPTURE, but that need tweaking with the saa7113
dot
id|flags
op_assign
l_int|0
comma
dot
id|stds
op_assign
op_amp
id|standard
(braket
l_int|0
)braket
comma
dot
id|num_stds
op_assign
r_sizeof
(paren
id|standard
)paren
op_div
r_sizeof
(paren
r_struct
id|saa7146_standard
)paren
comma
dot
id|ioctls
op_assign
op_amp
id|ioctls
(braket
l_int|0
)braket
comma
dot
id|ioctl
op_assign
id|av_ioctl
comma
)brace
suffix:semicolon
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|knc1
comma
l_string|&quot;KNC1 DVB-S&quot;
comma
id|BUDGET_KNC1
)paren
suffix:semicolon
DECL|variable|pci_tbl
r_static
r_struct
id|pci_device_id
id|pci_tbl
(braket
)braket
op_assign
(brace
id|MAKE_EXTENSION_PCI
c_func
(paren
id|knc1
comma
l_int|0x1131
comma
l_int|0x4f56
)paren
comma
(brace
dot
id|vendor
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|pci_tbl
)paren
suffix:semicolon
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;budget dvb /w video in&bslash;0&quot;
comma
dot
id|pci_tbl
op_assign
id|pci_tbl
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|attach
op_assign
id|budget_av_attach
comma
dot
id|detach
op_assign
id|budget_av_detach
comma
dot
id|irq_mask
op_assign
id|MASK_10
comma
dot
id|irq_func
op_assign
id|ttpci_budget_irq10_handler
comma
)brace
suffix:semicolon
DECL|function|budget_av_init
r_static
r_int
id|__init
id|budget_av_init
c_func
(paren
r_void
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|saa7146_register_extension
c_func
(paren
op_amp
id|budget_extension
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_av_exit
r_static
r_void
id|__exit
id|budget_av_exit
c_func
(paren
r_void
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|saa7146_unregister_extension
c_func
(paren
op_amp
id|budget_extension
)paren
suffix:semicolon
)brace
DECL|variable|budget_av_init
id|module_init
c_func
(paren
id|budget_av_init
)paren
suffix:semicolon
DECL|variable|budget_av_exit
id|module_exit
c_func
(paren
id|budget_av_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler, Marcus Metzler, Michael Hunold, others&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;driver for the SAA7146 based so-called &quot;
l_string|&quot;budget PCI DVB w/ analog input (e.g. the KNC cards)&quot;
)paren
suffix:semicolon
eof
