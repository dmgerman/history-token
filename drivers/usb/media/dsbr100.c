multiline_comment|/* A driver for the D-Link DSB-R100 USB radio.  The R100 plugs&n; into both the USB and an analog audio input, so this thing&n; only deals with initialisation and frequency setting, the&n; audio data has to be handled by a sound driver.&n;&n; Major issue: I can&squot;t find out where the device reports the signal&n; strength, and indeed the windows software appearantly just looks&n; at the stereo indicator as well.  So, scanning will only find&n; stereo stations.  Sad, but I can&squot;t help it.&n;&n; Also, the windows program sends oodles of messages over to the&n; device, and I couldn&squot;t figure out their meaning.  My suspicion&n; is that they don&squot;t have any:-)&n;&n; You might find some interesting stuff about this module at&n; http://unimut.fsk.uni-heidelberg.de/unimut/demi/dsbr&n;&n; Copyright (c) 2000 Markus Demleitner &lt;msdemlei@tucana.harvard.edu&gt;&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2 of the License, or&n; (at your option) any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; if not, write to the Free Software&n; Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n;&n; History:&n;&n; Version 0.30:&n; &t;Markus: Updates for 2.5.x kernel and more ISO compiant source&n;&n; Version 0.25:&n;        PSL and Markus: Cleanup, radio now doesn&squot;t stop on device close&n;&n; Version 0.24:&n; &t;Markus: Hope I got these silly VIDEO_TUNER_LOW issues finally&n;&t;right.  Some minor cleanup, improved standalone compilation&n;&n; Version 0.23:&n; &t;Markus: Sign extension bug fixed by declaring transfer_buffer unsigned&n;&n; Version 0.22:&n; &t;Markus: Some (brown bag) cleanup in what VIDIOCSTUNER returns, &n;&t;thanks to Mike Cox for pointing the problem out.&n;&n; Version 0.21:&n; &t;Markus: Minor cleanup, warnings if something goes wrong, lame attempt&n;&t;to adhere to Documentation/CodingStyle&n;&n; Version 0.2: &n; &t;Brad Hards &lt;bradh@dynamite.com.au&gt;: Fixes to make it work as non-module&n;&t;Markus: Copyright clarification&n;&n; Version 0.01: Markus: initial release&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.25&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Markus Demleitner &lt;msdemlei@tucana.harvard.edu&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;D-Link DSB-R100 USB FM radio driver&quot;
DECL|macro|DSB100_VENDOR
mdefine_line|#define DSB100_VENDOR 0x04b4
DECL|macro|DSB100_PRODUCT
mdefine_line|#define DSB100_PRODUCT 0x1002
DECL|macro|TB_LEN
mdefine_line|#define TB_LEN 16
multiline_comment|/* Frequency limits in MHz -- these are European values.  For Japanese&n;devices, that would be 76 and 91.  */
DECL|macro|FREQ_MIN
mdefine_line|#define FREQ_MIN  87.5
DECL|macro|FREQ_MAX
mdefine_line|#define FREQ_MAX 108.0
DECL|macro|FREQ_MUL
mdefine_line|#define FREQ_MUL 16000
r_static
r_int
id|usb_dsbr100_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
suffix:semicolon
r_static
r_void
id|usb_dsbr100_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
r_static
r_int
id|usb_dsbr100_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|usb_dsbr100_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|usb_dsbr100_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|radio_nr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|transfer_buffer
r_int
r_char
id|transfer_buffer
(braket
id|TB_LEN
)braket
suffix:semicolon
DECL|member|curfreq
r_int
id|curfreq
suffix:semicolon
DECL|member|stereo
r_int
id|stereo
suffix:semicolon
DECL|typedef|usb_dsbr100
)brace
id|usb_dsbr100
suffix:semicolon
DECL|variable|usb_dsbr100_fops
r_static
r_struct
id|file_operations
id|usb_dsbr100_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|usb_dsbr100_open
comma
dot
id|release
op_assign
id|usb_dsbr100_close
comma
dot
id|ioctl
op_assign
id|usb_dsbr100_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
DECL|variable|usb_dsbr100_radio
r_static
r_struct
id|video_device
id|usb_dsbr100_radio
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
l_string|&quot;D-Link DSB-R 100&quot;
comma
dot
id|type
op_assign
id|VID_TYPE_TUNER
comma
dot
id|hardware
op_assign
id|VID_HARDWARE_AZTECH
comma
dot
id|fops
op_assign
op_amp
id|usb_dsbr100_fops
comma
)brace
suffix:semicolon
DECL|variable|users
r_static
r_int
id|users
op_assign
l_int|0
suffix:semicolon
DECL|variable|usb_dsbr100_table
r_static
r_struct
id|usb_device_id
id|usb_dsbr100_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|DSB100_VENDOR
comma
id|DSB100_PRODUCT
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|usb_dsbr100_table
)paren
suffix:semicolon
DECL|variable|usb_dsbr100_driver
r_static
r_struct
id|usb_driver
id|usb_dsbr100_driver
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
l_string|&quot;dsbr100&quot;
comma
dot
id|probe
op_assign
id|usb_dsbr100_probe
comma
dot
id|disconnect
op_assign
id|usb_dsbr100_disconnect
comma
dot
id|id_table
op_assign
id|usb_dsbr100_table
comma
)brace
suffix:semicolon
DECL|function|dsbr100_start
r_static
r_int
id|dsbr100_start
c_func
(paren
id|usb_dsbr100
op_star
id|radio
)paren
(brace
r_if
c_cond
(paren
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x00
comma
l_int|0xC7
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
op_logical_or
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x02
comma
l_int|0xC0
comma
l_int|0x01
comma
l_int|0x00
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|radio-&gt;transfer_buffer
)paren
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|dsbr100_stop
r_static
r_int
id|dsbr100_stop
c_func
(paren
id|usb_dsbr100
op_star
id|radio
)paren
(brace
r_if
c_cond
(paren
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x16
comma
l_int|0x1C
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
op_logical_or
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x02
comma
l_int|0xC0
comma
l_int|0x00
comma
l_int|0x00
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|radio-&gt;transfer_buffer
)paren
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|dsbr100_setfreq
r_static
r_int
id|dsbr100_setfreq
c_func
(paren
id|usb_dsbr100
op_star
id|radio
comma
r_int
id|freq
)paren
(brace
id|freq
op_assign
(paren
id|freq
op_div
l_int|16
op_star
l_int|80
)paren
op_div
l_int|1000
op_plus
l_int|856
suffix:semicolon
r_if
c_cond
(paren
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x01
comma
l_int|0xC0
comma
(paren
id|freq
op_rshift
l_int|8
)paren
op_amp
l_int|0x00ff
comma
id|freq
op_amp
l_int|0xff
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
op_logical_or
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x96
comma
l_int|0xB7
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
op_logical_or
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x00
comma
l_int|0x24
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
)paren
(brace
id|radio-&gt;stereo
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|radio-&gt;stereo
op_assign
op_logical_neg
(paren
(paren
id|radio-&gt;transfer_buffer
)paren
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
r_return
(paren
id|radio-&gt;transfer_buffer
)paren
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|dsbr100_getstat
r_static
r_void
id|dsbr100_getstat
c_func
(paren
id|usb_dsbr100
op_star
id|radio
)paren
(brace
r_if
c_cond
(paren
id|usb_control_msg
c_func
(paren
id|radio-&gt;dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|radio-&gt;dev
comma
l_int|0
)paren
comma
l_int|0x00
comma
l_int|0xC0
comma
l_int|0x00
comma
l_int|0x24
comma
id|radio-&gt;transfer_buffer
comma
l_int|8
comma
l_int|300
)paren
OL
l_int|0
)paren
id|radio-&gt;stereo
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|radio-&gt;stereo
op_assign
op_logical_neg
(paren
id|radio-&gt;transfer_buffer
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
)brace
DECL|function|usb_dsbr100_probe
r_static
r_int
id|usb_dsbr100_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
id|usb_dsbr100
op_star
id|radio
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|radio
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|usb_dsbr100
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
id|usb_dsbr100_radio.priv
op_assign
id|radio
suffix:semicolon
id|radio-&gt;dev
op_assign
id|interface_to_usbdev
(paren
id|intf
)paren
suffix:semicolon
id|radio-&gt;curfreq
op_assign
id|FREQ_MIN
op_star
id|FREQ_MUL
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
id|radio
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_dsbr100_disconnect
r_static
r_void
id|usb_dsbr100_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
id|usb_dsbr100
op_star
id|radio
op_assign
id|usb_get_intfdata
(paren
id|intf
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|radio
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|users
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|radio
)paren
suffix:semicolon
id|usb_dsbr100_radio.priv
op_assign
l_int|NULL
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_dsbr100_do_ioctl
r_static
r_int
id|usb_dsbr100_do_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
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
id|video_device
op_star
id|dev
op_assign
id|video_devdata
c_func
(paren
id|file
)paren
suffix:semicolon
id|usb_dsbr100
op_star
id|radio
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|radio
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOCGCAP
suffix:colon
(brace
r_struct
id|video_capability
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|v
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
id|v-&gt;type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v-&gt;channels
op_assign
l_int|1
suffix:semicolon
id|v-&gt;audios
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;D-Link R-100 USB FM Radio&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGTUNER
suffix:colon
(brace
r_struct
id|video_tuner
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|dsbr100_getstat
c_func
(paren
id|radio
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;tuner
)paren
(brace
multiline_comment|/* Only 1 tuner */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|v-&gt;rangelow
op_assign
id|FREQ_MIN
op_star
id|FREQ_MUL
suffix:semicolon
id|v-&gt;rangehigh
op_assign
id|FREQ_MAX
op_star
id|FREQ_MUL
suffix:semicolon
id|v-&gt;flags
op_assign
id|VIDEO_TUNER_LOW
suffix:semicolon
id|v-&gt;mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v-&gt;signal
op_assign
id|radio-&gt;stereo
op_star
l_int|0x7000
suffix:semicolon
multiline_comment|/* Don&squot;t know how to get signal strength */
id|v-&gt;flags
op_or_assign
id|VIDEO_TUNER_STEREO_ON
op_star
id|radio-&gt;stereo
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;DSB R-100&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSTUNER
suffix:colon
(brace
r_struct
id|video_tuner
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;tuner
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Only 1 tuner so no setting needed ! */
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGFREQ
suffix:colon
(brace
r_int
op_star
id|freq
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|radio-&gt;curfreq
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|freq
op_assign
id|radio-&gt;curfreq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSFREQ
suffix:colon
(brace
r_int
op_star
id|freq
op_assign
id|arg
suffix:semicolon
id|radio-&gt;curfreq
op_assign
op_star
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|dsbr100_setfreq
c_func
(paren
id|radio
comma
id|radio-&gt;curfreq
)paren
op_eq
op_minus
l_int|1
)paren
id|warn
c_func
(paren
l_string|&quot;Set frequency failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|v
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
id|v-&gt;flags
op_or_assign
id|VIDEO_AUDIO_MUTABLE
suffix:semicolon
id|v-&gt;mode
op_assign
id|VIDEO_SOUND_STEREO
suffix:semicolon
id|v-&gt;volume
op_assign
l_int|1
suffix:semicolon
id|v-&gt;step
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Radio&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;audio
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
(brace
r_if
c_cond
(paren
id|dsbr100_stop
c_func
(paren
id|radio
)paren
op_eq
op_minus
l_int|1
)paren
id|warn
c_func
(paren
l_string|&quot;Radio did not respond properly&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dsbr100_start
c_func
(paren
id|radio
)paren
op_eq
op_minus
l_int|1
)paren
id|warn
c_func
(paren
l_string|&quot;Radio did not respond properly&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|function|usb_dsbr100_ioctl
r_static
r_int
id|usb_dsbr100_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|video_usercopy
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|usb_dsbr100_do_ioctl
)paren
suffix:semicolon
)brace
DECL|function|usb_dsbr100_open
r_static
r_int
id|usb_dsbr100_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|video_device
op_star
id|dev
op_assign
id|video_devdata
c_func
(paren
id|file
)paren
suffix:semicolon
id|usb_dsbr100
op_star
id|radio
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|radio
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;Radio not initialised&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|users
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;Radio in use&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|users
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dsbr100_start
c_func
(paren
id|radio
)paren
OL
l_int|0
)paren
id|warn
c_func
(paren
l_string|&quot;Radio did not start up properly&quot;
)paren
suffix:semicolon
id|dsbr100_setfreq
c_func
(paren
id|radio
comma
id|radio-&gt;curfreq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_dsbr100_close
r_static
r_int
id|usb_dsbr100_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|video_device
op_star
id|dev
op_assign
id|video_devdata
c_func
(paren
id|file
)paren
suffix:semicolon
id|usb_dsbr100
op_star
id|radio
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|radio
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|users
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsbr100_init
r_static
r_int
id|__init
id|dsbr100_init
c_func
(paren
r_void
)paren
(brace
id|usb_dsbr100_radio.priv
op_assign
l_int|NULL
suffix:semicolon
id|usb_register
c_func
(paren
op_amp
id|usb_dsbr100_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|usb_dsbr100_radio
comma
id|VFL_TYPE_RADIO
comma
id|radio_nr
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;Couldn&squot;t register video device&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot;:&quot;
id|DRIVER_DESC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dsbr100_exit
r_static
r_void
id|__exit
id|dsbr100_exit
c_func
(paren
r_void
)paren
(brace
id|usb_dsbr100
op_star
id|radio
op_assign
id|usb_dsbr100_radio.priv
suffix:semicolon
r_if
c_cond
(paren
id|radio
)paren
id|dsbr100_stop
c_func
(paren
id|radio
)paren
suffix:semicolon
id|video_unregister_device
c_func
(paren
op_amp
id|usb_dsbr100_radio
)paren
suffix:semicolon
id|usb_deregister
c_func
(paren
op_amp
id|usb_dsbr100_driver
)paren
suffix:semicolon
)brace
DECL|variable|dsbr100_init
id|module_init
(paren
id|dsbr100_init
)paren
suffix:semicolon
DECL|variable|dsbr100_exit
id|module_exit
(paren
id|dsbr100_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
