multiline_comment|/*&n;    hexium_orion.c - v4l2 driver for the Hexium Orion frame grabber cards&n;&n;    Visit http://www.mihu.de/linux/saa7146/ and follow the link&n;    to &quot;hexium&quot; for further details about this card.&n;    &n;    Copyright (C) 2003 Michael Hunold &lt;michael@mihu.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
DECL|macro|DEBUG_VARIABLE
mdefine_line|#define DEBUG_VARIABLE debug
macro_line|#include &lt;media/saa7146_vv.h&gt;
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
l_string|&quot;debug verbosity&quot;
)paren
suffix:semicolon
multiline_comment|/* global variables */
DECL|variable|hexium_num
r_int
id|hexium_num
op_assign
l_int|0
suffix:semicolon
macro_line|#include &quot;hexium_orion.h&quot;
multiline_comment|/* this is only called for old HV-PCI6/Orion cards&n;   without eeprom */
DECL|function|hexium_probe
r_static
r_int
id|hexium_probe
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|hexium
op_star
id|hexium
op_assign
l_int|0
suffix:semicolon
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* there are no hexium orion cards with revision 0 saa7146s */
r_if
c_cond
(paren
l_int|0
op_eq
id|dev-&gt;revision
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|hexium
op_assign
(paren
r_struct
id|hexium
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hexium
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
id|hexium
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hexium_orion.o: hexium_probe: not enough kernel memory.&bslash;n&quot;
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
id|hexium
comma
l_int|0x0
comma
r_sizeof
(paren
r_struct
id|hexium
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
id|saa7146_write
c_func
(paren
id|dev
comma
id|DD1_INIT
comma
l_int|0x02000200
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|DD1_STREAM_B
comma
l_int|0x00000000
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_09
op_or
id|MASK_25
op_or
id|MASK_10
op_or
id|MASK_26
)paren
)paren
suffix:semicolon
id|saa7146_i2c_adapter_prepare
c_func
(paren
id|dev
comma
op_amp
id|hexium-&gt;i2c_adapter
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
id|hexium-&gt;i2c_adapter
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
id|hexium
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* set SAA7110 control GPIO 0 */
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
multiline_comment|/*  set HWControl GPIO number 2 */
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|2
comma
id|SAA7146_GPIO_OUTHI
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* detect newer Hexium Orion cards by subsystem ids */
r_if
c_cond
(paren
l_int|0x17c8
op_eq
id|dev-&gt;pci-&gt;subsystem_vendor
op_logical_and
l_int|0x0101
op_eq
id|dev-&gt;pci-&gt;subsystem_device
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hexium_orion.o: device is a Hexium Orion w/ 1 SVHS + 3 BNC inputs.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* we store the pointer in our private data field */
(paren
r_struct
id|hexium
op_star
)paren
id|dev-&gt;ext_priv
op_assign
id|hexium
suffix:semicolon
id|hexium-&gt;type
op_assign
id|HEXIUM_ORION_1SVHS_3BNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0x17c8
op_eq
id|dev-&gt;pci-&gt;subsystem_vendor
op_logical_and
l_int|0x2101
op_eq
id|dev-&gt;pci-&gt;subsystem_device
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hexium_orion.o: device is a Hexium Orion w/ 4 BNC inputs.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* we store the pointer in our private data field */
(paren
r_struct
id|hexium
op_star
)paren
id|dev-&gt;ext_priv
op_assign
id|hexium
suffix:semicolon
id|hexium-&gt;type
op_assign
id|HEXIUM_ORION_4BNC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check if this is an old hexium Orion card by looking at &n;&t;   a saa7110 at address 0x4e */
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|err
op_assign
id|i2c_smbus_xfer
c_func
(paren
op_amp
id|hexium-&gt;i2c_adapter
comma
l_int|0x4e
comma
l_int|0
comma
id|I2C_SMBUS_READ
comma
l_int|0x00
comma
id|I2C_SMBUS_BYTE_DATA
comma
op_amp
id|data
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hexium_orion.o: device is a Hexium HV-PCI6/Orion (old).&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* we store the pointer in our private data field */
(paren
r_struct
id|hexium
op_star
)paren
id|dev-&gt;ext_priv
op_assign
id|hexium
suffix:semicolon
id|hexium-&gt;type
op_assign
id|HEXIUM_HV_PCI6_ORION
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|hexium-&gt;i2c_adapter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hexium
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* bring hardware to a sane state. this has to be done, just in case someone&n;   wants to capture from this device before it has been properly initialized.&n;   the capture engine would badly fail, because no valid signal arrives on the&n;   saa7146, thus leading to timeouts and stuff. */
DECL|function|hexium_init_done
r_static
r_int
id|hexium_init_done
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|hexium
op_star
id|hexium
op_assign
(paren
r_struct
id|hexium
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
r_union
id|i2c_smbus_data
id|data
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;hexium_init_done called.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* initialize the helper ics to useful values */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|hexium_saa7110
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data.byte
op_assign
id|hexium_saa7110
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|i2c_smbus_xfer
c_func
(paren
op_amp
id|hexium-&gt;i2c_adapter
comma
l_int|0x4e
comma
l_int|0
comma
id|I2C_SMBUS_WRITE
comma
id|i
comma
id|I2C_SMBUS_BYTE_DATA
comma
op_amp
id|data
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hexium_orion: failed for address 0x%02x&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
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
DECL|function|hexium_attach
r_static
r_int
id|hexium_attach
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
id|hexium
op_star
id|hexium
op_assign
(paren
r_struct
id|hexium
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;.&bslash;n&quot;
)paren
)paren
suffix:semicolon
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
id|hexium-&gt;video_dev
comma
id|dev
comma
l_string|&quot;hexium&quot;
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
id|printk
c_func
(paren
l_string|&quot;hexium_orion.o: found &squot;hexium orion&squot; frame grabber-%d.&bslash;n&quot;
comma
id|hexium_num
)paren
suffix:semicolon
id|hexium_num
op_increment
suffix:semicolon
multiline_comment|/* the rest */
id|hexium-&gt;cur_input
op_assign
l_int|0
suffix:semicolon
id|hexium_init_done
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hexium_detach
r_static
r_int
id|hexium_detach
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|hexium
op_star
id|hexium
op_assign
(paren
r_struct
id|hexium
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
id|saa7146_unregister_device
c_func
(paren
op_amp
id|hexium-&gt;video_dev
comma
id|dev
)paren
suffix:semicolon
id|saa7146_vv_release
c_func
(paren
id|dev
)paren
suffix:semicolon
id|hexium_num
op_decrement
suffix:semicolon
id|i2c_del_adapter
c_func
(paren
op_amp
id|hexium-&gt;i2c_adapter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hexium
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hexium_ioctl
r_static
r_int
id|hexium_ioctl
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
id|hexium
op_star
id|hexium
op_assign
(paren
r_struct
id|hexium
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
id|HEXIUM_INPUTS
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
id|hexium_inputs
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
l_string|&quot;v4l2_ioctl: VIDIOC_ENUMINPUT %d.&bslash;n&quot;
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
id|hexium-&gt;cur_input
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;VIDIOC_G_INPUT: %d&bslash;n&quot;
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
id|HEXIUM_INPUTS
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|hexium-&gt;cur_input
op_assign
id|input
suffix:semicolon
multiline_comment|/* fixme: switch input here, switch audio, too! */
singleline_comment|//              saa7146_set_hps_source_and_sync(dev, input_port_selection[input].hps_source, input_port_selection[input].hps_sync);
id|printk
c_func
(paren
l_string|&quot;hexium_orion.o: VIDIOC_S_INPUT: fixme switch input.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;DEB_D((&quot;v4l2_ioctl does not handle this ioctl.&bslash;n&quot;));&n;*/
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
DECL|variable|extension
r_static
r_struct
id|saa7146_extension
id|extension
suffix:semicolon
DECL|variable|hexium_hv_pci6
r_static
r_struct
id|saa7146_pci_extension_data
id|hexium_hv_pci6
op_assign
(brace
dot
id|ext_priv
op_assign
l_string|&quot;Hexium HV-PCI6 / Orion&quot;
comma
dot
id|ext
op_assign
op_amp
id|extension
comma
)brace
suffix:semicolon
DECL|variable|hexium_orion_1svhs_3bnc
r_static
r_struct
id|saa7146_pci_extension_data
id|hexium_orion_1svhs_3bnc
op_assign
(brace
dot
id|ext_priv
op_assign
l_string|&quot;Hexium HV-PCI6 / Orion (1 SVHS/3 BNC)&quot;
comma
dot
id|ext
op_assign
op_amp
id|extension
comma
)brace
suffix:semicolon
DECL|variable|hexium_orion_4bnc
r_static
r_struct
id|saa7146_pci_extension_data
id|hexium_orion_4bnc
op_assign
(brace
dot
id|ext_priv
op_assign
l_string|&quot;Hexium HV-PCI6 / Orion (4 BNC)&quot;
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
id|hexium_hv_pci6
comma
)brace
comma
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
l_int|0x17c8
comma
dot
id|subdevice
op_assign
l_int|0x0101
comma
dot
id|driver_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|hexium_orion_1svhs_3bnc
comma
)brace
comma
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
l_int|0x17c8
comma
dot
id|subdevice
op_assign
l_int|0x2101
comma
dot
id|driver_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|hexium_orion_4bnc
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
id|HEXIUM_INPUTS
comma
dot
id|capabilities
op_assign
l_int|0
comma
dot
id|stds
op_assign
op_amp
id|hexium_standards
(braket
l_int|0
)braket
comma
dot
id|num_stds
op_assign
r_sizeof
(paren
id|hexium_standards
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
id|hexium_ioctl
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
l_string|&quot;hexium HV-PCI6/Orion&quot;
comma
dot
id|flags
op_assign
l_int|0
comma
singleline_comment|// SAA7146_USE_I2C_IRQ,
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
id|hexium_probe
comma
dot
id|attach
op_assign
id|hexium_attach
comma
dot
id|detach
op_assign
id|hexium_detach
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
DECL|function|hexium_init_module
r_int
id|__init
id|hexium_init_module
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
DECL|function|hexium_cleanup_module
r_void
id|__exit
id|hexium_cleanup_module
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
DECL|variable|hexium_init_module
id|module_init
c_func
(paren
id|hexium_init_module
)paren
suffix:semicolon
DECL|variable|hexium_cleanup_module
id|module_exit
c_func
(paren
id|hexium_cleanup_module
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;video4linux-2 driver for Hexium Orion frame grabber cards&quot;
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
