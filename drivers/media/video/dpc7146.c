multiline_comment|/*&n;    dpc7146.c - v4l2 driver for the dpc7146 demonstration board&n;    &n;    Copyright (C) 2000-2003 Michael Hunold &lt;michael@mihu.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
DECL|macro|DEBUG_VARIABLE
mdefine_line|#define DEBUG_VARIABLE debug
macro_line|#include &lt;media/saa7146_vv.h&gt;
macro_line|#include &lt;linux/video_decoder.h&gt;&t;/* for saa7111a */
DECL|macro|I2C_SAA7111A
mdefine_line|#define I2C_SAA7111A            0x24
multiline_comment|/* All unused bytes are reserverd. */
DECL|macro|SAA711X_CHIP_VERSION
mdefine_line|#define SAA711X_CHIP_VERSION            0x00
DECL|macro|SAA711X_ANALOG_INPUT_CONTROL_1
mdefine_line|#define SAA711X_ANALOG_INPUT_CONTROL_1  0x02
DECL|macro|SAA711X_ANALOG_INPUT_CONTROL_2
mdefine_line|#define SAA711X_ANALOG_INPUT_CONTROL_2  0x03
DECL|macro|SAA711X_ANALOG_INPUT_CONTROL_3
mdefine_line|#define SAA711X_ANALOG_INPUT_CONTROL_3  0x04
DECL|macro|SAA711X_ANALOG_INPUT_CONTROL_4
mdefine_line|#define SAA711X_ANALOG_INPUT_CONTROL_4  0x05
DECL|macro|SAA711X_HORIZONTAL_SYNC_START
mdefine_line|#define SAA711X_HORIZONTAL_SYNC_START   0x06
DECL|macro|SAA711X_HORIZONTAL_SYNC_STOP
mdefine_line|#define SAA711X_HORIZONTAL_SYNC_STOP    0x07
DECL|macro|SAA711X_SYNC_CONTROL
mdefine_line|#define SAA711X_SYNC_CONTROL            0x08
DECL|macro|SAA711X_LUMINANCE_CONTROL
mdefine_line|#define SAA711X_LUMINANCE_CONTROL       0x09
DECL|macro|SAA711X_LUMINANCE_BRIGHTNESS
mdefine_line|#define SAA711X_LUMINANCE_BRIGHTNESS    0x0A
DECL|macro|SAA711X_LUMINANCE_CONTRAST
mdefine_line|#define SAA711X_LUMINANCE_CONTRAST      0x0B
DECL|macro|SAA711X_CHROMA_SATURATION
mdefine_line|#define SAA711X_CHROMA_SATURATION       0x0C
DECL|macro|SAA711X_CHROMA_HUE_CONTROL
mdefine_line|#define SAA711X_CHROMA_HUE_CONTROL      0x0D
DECL|macro|SAA711X_CHROMA_CONTROL
mdefine_line|#define SAA711X_CHROMA_CONTROL          0x0E
DECL|macro|SAA711X_FORMAT_DELAY_CONTROL
mdefine_line|#define SAA711X_FORMAT_DELAY_CONTROL    0x10
DECL|macro|SAA711X_OUTPUT_CONTROL_1
mdefine_line|#define SAA711X_OUTPUT_CONTROL_1        0x11
DECL|macro|SAA711X_OUTPUT_CONTROL_2
mdefine_line|#define SAA711X_OUTPUT_CONTROL_2        0x12
DECL|macro|SAA711X_OUTPUT_CONTROL_3
mdefine_line|#define SAA711X_OUTPUT_CONTROL_3        0x13
DECL|macro|SAA711X_V_GATE_1_START
mdefine_line|#define SAA711X_V_GATE_1_START          0x15
DECL|macro|SAA711X_V_GATE_1_STOP
mdefine_line|#define SAA711X_V_GATE_1_STOP           0x16
DECL|macro|SAA711X_V_GATE_1_MSB
mdefine_line|#define SAA711X_V_GATE_1_MSB            0x17
DECL|macro|SAA711X_TEXT_SLICER_STATUS
mdefine_line|#define SAA711X_TEXT_SLICER_STATUS      0x1A
DECL|macro|SAA711X_DECODED_BYTES_OF_TS_1
mdefine_line|#define SAA711X_DECODED_BYTES_OF_TS_1   0x1B
DECL|macro|SAA711X_DECODED_BYTES_OF_TS_2
mdefine_line|#define SAA711X_DECODED_BYTES_OF_TS_2   0x1C
DECL|macro|SAA711X_STATUS_BYTE
mdefine_line|#define SAA711X_STATUS_BYTE             0x1F
DECL|macro|DPC_BOARD_CAN_DO_VBI
mdefine_line|#define DPC_BOARD_CAN_DO_VBI(dev)   (dev-&gt;revision != 0) 
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
l_string|&quot;debug verbosity&quot;
)paren
suffix:semicolon
DECL|variable|dpc_num
r_static
r_int
id|dpc_num
op_assign
l_int|0
suffix:semicolon
DECL|macro|DPC_INPUTS
mdefine_line|#define DPC_INPUTS&t;2
DECL|variable|dpc_inputs
r_static
r_struct
id|v4l2_input
id|dpc_inputs
(braket
id|DPC_INPUTS
)braket
op_assign
(brace
(brace
l_int|0
comma
l_string|&quot;Port A&quot;
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
(brace
l_int|1
comma
l_string|&quot;Port B&quot;
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
DECL|macro|DPC_AUDIOS
mdefine_line|#define DPC_AUDIOS&t;0
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
id|VIDIOC_ENUMINPUT
comma
id|SAA7146_EXCLUSIVE
)brace
comma
(brace
id|VIDIOC_S_STD
comma
id|SAA7146_AFTER
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|struct|dpc
r_struct
id|dpc
(brace
DECL|member|video_dev
r_struct
id|video_device
op_star
id|video_dev
suffix:semicolon
DECL|member|vbi_dev
r_struct
id|video_device
op_star
id|vbi_dev
suffix:semicolon
DECL|member|i2c_adapter
r_struct
id|i2c_adapter
id|i2c_adapter
suffix:semicolon
DECL|member|saa7111a
r_struct
id|i2c_client
op_star
id|saa7111a
suffix:semicolon
DECL|member|cur_input
r_int
id|cur_input
suffix:semicolon
multiline_comment|/* current input */
)brace
suffix:semicolon
multiline_comment|/* fixme: add vbi stuff here */
DECL|function|dpc_probe
r_static
r_int
id|dpc_probe
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|dpc
op_star
id|dpc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_struct
id|list_head
op_star
id|item
suffix:semicolon
id|dpc
op_assign
(paren
r_struct
id|dpc
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dpc
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
id|dpc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dpc_v4l2.o: dpc_probe: not enough kernel memory.&bslash;n&quot;
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
id|dpc
comma
l_int|0x0
comma
r_sizeof
(paren
r_struct
id|dpc
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: enable i2c-port pins, video-port-pins&n;&t;   video port pins should be enabled here ?! */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
(paren
id|MASK_08
op_or
id|MASK_24
op_or
id|MASK_10
op_or
id|MASK_26
)paren
)paren
suffix:semicolon
id|dpc-&gt;i2c_adapter
op_assign
(paren
r_struct
id|i2c_adapter
)paren
(brace
dot
r_class
op_assign
id|I2C_CLASS_TV_ANALOG
comma
dot
id|name
op_assign
l_string|&quot;dpc7146&quot;
comma
)brace
suffix:semicolon
id|saa7146_i2c_adapter_prepare
c_func
(paren
id|dev
comma
op_amp
id|dpc-&gt;i2c_adapter
comma
id|SAA7146_I2C_BUS_BIT_RATE_480
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_add_adapter
c_func
(paren
op_amp
id|dpc-&gt;i2c_adapter
)paren
OL
l_int|0
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;cannot register i2c-device. skipping.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dpc
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* loop through all i2c-devices on the bus and look who is there */
id|list_for_each
c_func
(paren
id|item
comma
op_amp
id|dpc-&gt;i2c_adapter.clients
)paren
(brace
id|client
op_assign
id|list_entry
c_func
(paren
id|item
comma
r_struct
id|i2c_client
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|I2C_SAA7111A
op_eq
id|client-&gt;addr
)paren
(brace
id|dpc-&gt;saa7111a
op_assign
id|client
suffix:semicolon
)brace
)brace
multiline_comment|/* check if all devices are present */
r_if
c_cond
(paren
l_int|0
op_eq
id|dpc-&gt;saa7111a
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;dpc_v4l2.o: dpc_attach failed for this device.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|i2c_del_adapter
c_func
(paren
op_amp
id|dpc-&gt;i2c_adapter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dpc
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* all devices are present, probe was successful */
id|DEB_D
c_func
(paren
(paren
l_string|&quot;dpc_v4l2.o: dpc_probe succeeded for this device.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* we store the pointer in our private data field */
id|dev-&gt;ext_priv
op_assign
id|dpc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* bring hardware to a sane state. this has to be done, just in case someone&n;   wants to capture from this device before it has been properly initialized.&n;   the capture engine would badly fail, because no valid signal arrives on the&n;   saa7146, thus leading to timeouts and stuff. */
DECL|function|dpc_init_done
r_static
r_int
id|dpc_init_done
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|dpc
op_star
id|dpc
op_assign
(paren
r_struct
id|dpc
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;dpc_v4l2.o: dpc_init_done called.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* initialize the helper ics to useful values */
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x00
comma
l_int|0x11
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x02
comma
l_int|0xc0
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x03
comma
l_int|0x30
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x04
comma
l_int|0x00
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x05
comma
l_int|0x00
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x06
comma
l_int|0xde
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x07
comma
l_int|0xad
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x08
comma
l_int|0xa8
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x09
comma
l_int|0x00
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x0a
comma
l_int|0x80
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x0b
comma
l_int|0x47
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x0c
comma
l_int|0x40
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x0d
comma
l_int|0x00
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x0e
comma
l_int|0x03
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x10
comma
l_int|0xd0
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x11
comma
l_int|0x1c
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x12
comma
l_int|0xc1
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x13
comma
l_int|0x30
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|dpc-&gt;saa7111a
comma
l_int|0x1f
comma
l_int|0x81
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vv_data
r_static
r_struct
id|saa7146_ext_vv
id|vv_data
suffix:semicolon
multiline_comment|/* this function only gets called when the probing was successful */
DECL|function|dpc_attach
r_static
r_int
id|dpc_attach
c_func
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
id|dpc
op_star
id|dpc
op_assign
(paren
r_struct
id|dpc
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;dpc_v4l2.o: dpc_attach called.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* checking for i2c-devices can be omitted here, because we&n;&t;   already did this in &quot;dpc_vl42_probe&quot; */
id|saa7146_vv_init
c_func
(paren
id|dev
comma
op_amp
id|vv_data
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_register_device
c_func
(paren
op_amp
id|dpc-&gt;video_dev
comma
id|dev
comma
l_string|&quot;dpc&quot;
comma
id|VFL_TYPE_GRABBER
)paren
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;cannot register capture v4l2 device. skipping.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* initialization stuff (vbi) (only for revision &gt; 0 and for extensions which want it)*/
r_if
c_cond
(paren
l_int|0
op_ne
id|DPC_BOARD_CAN_DO_VBI
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_register_device
c_func
(paren
op_amp
id|dpc-&gt;vbi_dev
comma
id|dev
comma
l_string|&quot;dpc&quot;
comma
id|VFL_TYPE_VBI
)paren
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;cannot register vbi v4l2 device. skipping.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
id|i2c_use_client
c_func
(paren
id|dpc-&gt;saa7111a
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dpc: found &squot;dpc7146 demonstration board&squot;-%d.&bslash;n&quot;
comma
id|dpc_num
)paren
suffix:semicolon
id|dpc_num
op_increment
suffix:semicolon
multiline_comment|/* the rest */
id|dpc-&gt;cur_input
op_assign
l_int|0
suffix:semicolon
id|dpc_init_done
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dpc_detach
r_static
r_int
id|dpc_detach
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|dpc
op_star
id|dpc
op_assign
(paren
r_struct
id|dpc
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
id|i2c_release_client
c_func
(paren
id|dpc-&gt;saa7111a
)paren
suffix:semicolon
id|saa7146_unregister_device
c_func
(paren
op_amp
id|dpc-&gt;video_dev
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|DPC_BOARD_CAN_DO_VBI
c_func
(paren
id|dev
)paren
)paren
(brace
id|saa7146_unregister_device
c_func
(paren
op_amp
id|dpc-&gt;vbi_dev
comma
id|dev
)paren
suffix:semicolon
)brace
id|saa7146_vv_release
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dpc_num
op_decrement
suffix:semicolon
id|i2c_del_adapter
c_func
(paren
op_amp
id|dpc-&gt;i2c_adapter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dpc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef axa
DECL|function|dpc_vbi_bypass
r_int
id|dpc_vbi_bypass
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|dpc
op_star
id|dpc
op_assign
(paren
r_struct
id|dpc
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* switch bypass in saa7111a */
r_if
c_cond
(paren
l_int|0
op_ne
id|dpc-&gt;saa7111a-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|dpc-&gt;saa7111a
comma
id|SAA711X_VBI_BYPASS
comma
op_amp
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dpc_v4l2.o: VBI_BYPASS: could not address saa7111a.&bslash;n&quot;
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
macro_line|#endif
DECL|function|dpc_ioctl
r_static
r_int
id|dpc_ioctl
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
id|dpc
op_star
id|dpc
op_assign
(paren
r_struct
id|dpc
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
id|DPC_INPUTS
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
id|dpc_inputs
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
id|DEB_D
c_func
(paren
(paren
l_string|&quot;dpc_v4l2.o: v4l2_ioctl: VIDIOC_ENUMINPUT %d.&bslash;n&quot;
comma
id|i-&gt;index
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
id|dpc-&gt;cur_input
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;dpc_v4l2.o: VIDIOC_G_INPUT: %d&bslash;n&quot;
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
r_if
c_cond
(paren
id|input
OL
l_int|0
op_logical_or
id|input
op_ge
id|DPC_INPUTS
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dpc-&gt;cur_input
op_assign
id|input
suffix:semicolon
multiline_comment|/* fixme: switch input here, switch audio, too! */
singleline_comment|//&t;&t;saa7146_set_hps_source_and_sync(dev, input_port_selection[input].hps_source, input_port_selection[input].hps_sync);
id|printk
c_func
(paren
l_string|&quot;dpc_v4l2.o: VIDIOC_S_INPUT: fixme switch input.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;DEB_D((&quot;dpc_v4l2.o: v4l2_ioctl does not handle this ioctl.&bslash;n&quot;));&n;*/
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|std_callback
r_static
r_int
id|std_callback
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_standard
op_star
id|std
)paren
(brace
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
comma
(brace
dot
id|name
op_assign
l_string|&quot;SECAM&quot;
comma
dot
id|id
op_assign
id|V4L2_STD_SECAM
comma
dot
id|v_offset
op_assign
l_int|0x14
comma
dot
id|v_field
op_assign
l_int|288
comma
dot
id|h_offset
op_assign
l_int|0x14
comma
dot
id|h_pixels
op_assign
l_int|720
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
)brace
suffix:semicolon
DECL|variable|extension
r_static
r_struct
id|saa7146_extension
id|extension
suffix:semicolon
DECL|variable|dpc
r_static
r_struct
id|saa7146_pci_extension_data
id|dpc
op_assign
(brace
dot
id|ext_priv
op_assign
l_string|&quot;Multimedia eXtension Board&quot;
comma
dot
id|ext
op_assign
op_amp
id|extension
comma
)brace
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
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_PHILIPS
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_PHILIPS_SAA7146
comma
dot
id|subvendor
op_assign
l_int|0x0000
comma
dot
id|subdevice
op_assign
l_int|0x0000
comma
dot
id|driver_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|dpc
comma
)brace
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
id|DPC_INPUTS
comma
dot
id|capabilities
op_assign
id|V4L2_CAP_VBI_CAPTURE
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
id|std_callback
op_assign
op_amp
id|std_callback
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
id|dpc_ioctl
comma
)brace
suffix:semicolon
DECL|variable|extension
r_static
r_struct
id|saa7146_extension
id|extension
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dpc7146 demonstration board&quot;
comma
dot
id|flags
op_assign
id|SAA7146_USE_I2C_IRQ
comma
dot
id|pci_tbl
op_assign
op_amp
id|pci_tbl
(braket
l_int|0
)braket
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|probe
op_assign
id|dpc_probe
comma
dot
id|attach
op_assign
id|dpc_attach
comma
dot
id|detach
op_assign
id|dpc_detach
comma
dot
id|irq_mask
op_assign
l_int|0
comma
dot
id|irq_func
op_assign
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|dpc_init_module
r_static
r_int
id|__init
id|dpc_init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_register_extension
c_func
(paren
op_amp
id|extension
)paren
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;failed to register extension.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dpc_cleanup_module
r_static
r_void
id|__exit
id|dpc_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|saa7146_unregister_extension
c_func
(paren
op_amp
id|extension
)paren
suffix:semicolon
)brace
DECL|variable|dpc_init_module
id|module_init
c_func
(paren
id|dpc_init_module
)paren
suffix:semicolon
DECL|variable|dpc_cleanup_module
id|module_exit
c_func
(paren
id|dpc_cleanup_module
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;video4linux-2 driver for the &squot;dpc7146 demonstration board&squot;&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michael Hunold &lt;michael@mihu.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
