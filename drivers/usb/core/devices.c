multiline_comment|/*&n; * devices.c&n; * (C) Copyright 1999 Randy Dunlap.&n; * (C) Copyright 1999,2000 Thomas Sailer &lt;sailer@ife.ee.ethz.ch&gt;. (proc file per device)&n; * (C) Copyright 1999 Deti Fliegl (new USB architecture)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; *************************************************************&n; *&n; * &lt;mountpoint&gt;/devices contains USB topology, device, config, class,&n; * interface, &amp; endpoint data.&n; *&n; * I considered using /proc/bus/usb/devices/device# for each device&n; * as it is attached or detached, but I didn&squot;t like this for some&n; * reason -- maybe it&squot;s just too deep of a directory structure.&n; * I also don&squot;t like looking in multiple places to gather and view&n; * the data.  Having only one file for ./devices also prevents race&n; * conditions that could arise if a program was reading device info&n; * for devices that are being removed (unplugged).  (That is, the&n; * program may find a directory for devnum_12 then try to open it,&n; * but it was just unplugged, so the directory is now deleted.&n; * But programs would just have to be prepared for situations like&n; * this in any plug-and-play environment.)&n; *&n; * 1999-12-16: Thomas Sailer &lt;sailer@ife.ee.ethz.ch&gt;&n; *   Converted the whole proc stuff to real&n; *   read methods. Now not the whole device list needs to fit&n; *   into one page, only the device list for one bus.&n; *   Added a poll method to /proc/bus/usb/devices, to wake&n; *   up an eventual usbd&n; * 2000-01-04: Thomas Sailer &lt;sailer@ife.ee.ethz.ch&gt;&n; *   Turned into its own filesystem&n; * 2000-07-05: Ashley Montanaro &lt;ashley@compsoc.man.ac.uk&gt;&n; *   Converted file reading routine to dump to buffer once&n; *   per device, not per bus&n; *&n; * $Id: devices.c,v 1.5 2000/01/11 13:58:21 tom Exp $&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/usbdevice_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;hcd.h&quot;
DECL|macro|MAX_TOPO_LEVEL
mdefine_line|#define MAX_TOPO_LEVEL&t;&t;6
multiline_comment|/* Define ALLOW_SERIAL_NUMBER if you want to see the serial number of devices */
DECL|macro|ALLOW_SERIAL_NUMBER
mdefine_line|#define ALLOW_SERIAL_NUMBER
DECL|variable|format_topo
r_static
r_char
op_star
id|format_topo
op_assign
multiline_comment|/* T:  Bus=dd Lev=dd Prnt=dd Port=dd Cnt=dd Dev#=ddd Spd=ddd MxCh=dd */
l_string|&quot;T:  Bus=%2.2d Lev=%2.2d Prnt=%2.2d Port=%2.2d Cnt=%2.2d Dev#=%3d Spd=%3s MxCh=%2d&bslash;n&quot;
suffix:semicolon
DECL|variable|format_string_manufacturer
r_static
r_char
op_star
id|format_string_manufacturer
op_assign
multiline_comment|/* S:  Manufacturer=xxxx */
l_string|&quot;S:  Manufacturer=%.100s&bslash;n&quot;
suffix:semicolon
DECL|variable|format_string_product
r_static
r_char
op_star
id|format_string_product
op_assign
multiline_comment|/* S:  Product=xxxx */
l_string|&quot;S:  Product=%.100s&bslash;n&quot;
suffix:semicolon
macro_line|#ifdef ALLOW_SERIAL_NUMBER
DECL|variable|format_string_serialnumber
r_static
r_char
op_star
id|format_string_serialnumber
op_assign
multiline_comment|/* S:  SerialNumber=xxxx */
l_string|&quot;S:  SerialNumber=%.100s&bslash;n&quot;
suffix:semicolon
macro_line|#endif
DECL|variable|format_bandwidth
r_static
r_char
op_star
id|format_bandwidth
op_assign
multiline_comment|/* B:  Alloc=ddd/ddd us (xx%), #Int=ddd, #Iso=ddd */
l_string|&quot;B:  Alloc=%3d/%3d us (%2d%%), #Int=%3d, #Iso=%3d&bslash;n&quot;
suffix:semicolon
DECL|variable|format_device1
r_static
r_char
op_star
id|format_device1
op_assign
multiline_comment|/* D:  Ver=xx.xx Cls=xx(sssss) Sub=xx Prot=xx MxPS=dd #Cfgs=dd */
l_string|&quot;D:  Ver=%2x.%02x Cls=%02x(%-5s) Sub=%02x Prot=%02x MxPS=%2d #Cfgs=%3d&bslash;n&quot;
suffix:semicolon
DECL|variable|format_device2
r_static
r_char
op_star
id|format_device2
op_assign
multiline_comment|/* P:  Vendor=xxxx ProdID=xxxx Rev=xx.xx */
l_string|&quot;P:  Vendor=%04x ProdID=%04x Rev=%2x.%02x&bslash;n&quot;
suffix:semicolon
DECL|variable|format_config
r_static
r_char
op_star
id|format_config
op_assign
multiline_comment|/* C:  #Ifs=dd Cfg#=dd Atr=xx MPwr=dddmA */
l_string|&quot;C:%c #Ifs=%2d Cfg#=%2d Atr=%02x MxPwr=%3dmA&bslash;n&quot;
suffix:semicolon
DECL|variable|format_iface
r_static
r_char
op_star
id|format_iface
op_assign
multiline_comment|/* I:  If#=dd Alt=dd #EPs=dd Cls=xx(sssss) Sub=xx Prot=xx Driver=xxxx*/
l_string|&quot;I:  If#=%2d Alt=%2d #EPs=%2d Cls=%02x(%-5s) Sub=%02x Prot=%02x Driver=%s&bslash;n&quot;
suffix:semicolon
DECL|variable|format_endpt
r_static
r_char
op_star
id|format_endpt
op_assign
multiline_comment|/* E:  Ad=xx(s) Atr=xx(ssss) MxPS=dddd Ivl=D?s */
l_string|&quot;E:  Ad=%02x(%c) Atr=%02x(%-4s) MxPS=%4d Ivl=%d%cs&bslash;n&quot;
suffix:semicolon
multiline_comment|/*&n; * Need access to the driver and USB bus lists.&n; * extern struct list_head usb_driver_list;&n; * extern struct list_head usb_bus_list;&n; * However, these will come from functions that return ptrs to each of them.&n; */
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|deviceconndiscwq
)paren
suffix:semicolon
DECL|variable|conndiscevcnt
r_static
r_int
r_int
id|conndiscevcnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this struct stores the poll state for &lt;mountpoint&gt;/devices pollers */
DECL|struct|usb_device_status
r_struct
id|usb_device_status
(brace
DECL|member|lastev
r_int
r_int
id|lastev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|class_info
r_struct
id|class_info
(brace
DECL|member|class
r_int
r_class
suffix:semicolon
DECL|member|class_name
r_char
op_star
id|class_name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|clas_info
r_static
r_const
r_struct
id|class_info
id|clas_info
(braket
)braket
op_assign
(brace
multiline_comment|/* max. 5 chars. per name string */
(brace
id|USB_CLASS_PER_INTERFACE
comma
l_string|&quot;&gt;ifc&quot;
)brace
comma
(brace
id|USB_CLASS_AUDIO
comma
l_string|&quot;audio&quot;
)brace
comma
(brace
id|USB_CLASS_COMM
comma
l_string|&quot;comm.&quot;
)brace
comma
(brace
id|USB_CLASS_HID
comma
l_string|&quot;HID&quot;
)brace
comma
(brace
id|USB_CLASS_HUB
comma
l_string|&quot;hub&quot;
)brace
comma
(brace
id|USB_CLASS_PHYSICAL
comma
l_string|&quot;PID&quot;
)brace
comma
(brace
id|USB_CLASS_PRINTER
comma
l_string|&quot;print&quot;
)brace
comma
(brace
id|USB_CLASS_MASS_STORAGE
comma
l_string|&quot;stor.&quot;
)brace
comma
(brace
id|USB_CLASS_CDC_DATA
comma
l_string|&quot;data&quot;
)brace
comma
(brace
id|USB_CLASS_APP_SPEC
comma
l_string|&quot;app.&quot;
)brace
comma
(brace
id|USB_CLASS_VENDOR_SPEC
comma
l_string|&quot;vend.&quot;
)brace
comma
(brace
id|USB_CLASS_STILL_IMAGE
comma
l_string|&quot;still&quot;
)brace
comma
(brace
id|USB_CLASS_CSCID
comma
l_string|&quot;scard&quot;
)brace
comma
(brace
id|USB_CLASS_CONTENT_SEC
comma
l_string|&quot;c-sec&quot;
)brace
comma
(brace
op_minus
l_int|1
comma
l_string|&quot;unk.&quot;
)brace
multiline_comment|/* leave as last */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************/
DECL|function|usbdevfs_conn_disc_event
r_void
id|usbdevfs_conn_disc_event
c_func
(paren
r_void
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|deviceconndiscwq
)paren
suffix:semicolon
id|conndiscevcnt
op_increment
suffix:semicolon
)brace
DECL|function|class_decode
r_static
r_const
r_char
op_star
id|class_decode
c_func
(paren
r_const
r_int
r_class
)paren
(brace
r_int
id|ix
suffix:semicolon
r_for
c_loop
(paren
id|ix
op_assign
l_int|0
suffix:semicolon
id|clas_info
(braket
id|ix
)braket
dot
r_class
op_ne
op_minus
l_int|1
suffix:semicolon
id|ix
op_increment
)paren
r_if
c_cond
(paren
id|clas_info
(braket
id|ix
)braket
dot
r_class
op_eq
r_class
)paren
r_break
suffix:semicolon
r_return
(paren
id|clas_info
(braket
id|ix
)braket
dot
id|class_name
)paren
suffix:semicolon
)brace
DECL|function|usb_dump_endpoint_descriptor
r_static
r_char
op_star
id|usb_dump_endpoint_descriptor
(paren
r_int
id|speed
comma
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_endpoint_descriptor
op_star
id|desc
)paren
(brace
r_char
id|dir
comma
id|unit
comma
op_star
id|type
suffix:semicolon
r_int
id|interval
comma
id|in
comma
id|bandwidth
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|in
op_assign
(paren
id|desc-&gt;bEndpointAddress
op_amp
id|USB_DIR_IN
)paren
suffix:semicolon
id|dir
op_assign
id|in
ques
c_cond
l_char|&squot;I&squot;
suffix:colon
l_char|&squot;O&squot;
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_eq
id|USB_SPEED_HIGH
)paren
(brace
r_switch
c_cond
(paren
id|desc-&gt;wMaxPacketSize
op_amp
(paren
l_int|0x03
op_lshift
l_int|11
)paren
)paren
(brace
r_case
l_int|1
op_lshift
l_int|11
suffix:colon
id|bandwidth
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
op_lshift
l_int|11
suffix:colon
id|bandwidth
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* this isn&squot;t checking for illegal values */
r_switch
c_cond
(paren
id|desc-&gt;bmAttributes
op_amp
id|USB_ENDPOINT_XFERTYPE_MASK
)paren
(brace
r_case
id|USB_ENDPOINT_XFER_CONTROL
suffix:colon
id|type
op_assign
l_string|&quot;Ctrl&quot;
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_eq
id|USB_SPEED_HIGH
)paren
multiline_comment|/* uframes per NAK */
id|interval
op_assign
id|desc-&gt;bInterval
suffix:semicolon
r_else
id|interval
op_assign
l_int|0
suffix:semicolon
id|dir
op_assign
l_char|&squot;B&squot;
suffix:semicolon
multiline_comment|/* ctrl is bidirectional */
r_break
suffix:semicolon
r_case
id|USB_ENDPOINT_XFER_ISOC
suffix:colon
id|type
op_assign
l_string|&quot;Isoc&quot;
suffix:semicolon
id|interval
op_assign
l_int|1
op_lshift
(paren
id|desc-&gt;bInterval
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_ENDPOINT_XFER_BULK
suffix:colon
id|type
op_assign
l_string|&quot;Bulk&quot;
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_eq
id|USB_SPEED_HIGH
op_logical_and
op_logical_neg
id|in
)paren
multiline_comment|/* uframes per NAK */
id|interval
op_assign
id|desc-&gt;bInterval
suffix:semicolon
r_else
id|interval
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_ENDPOINT_XFER_INT
suffix:colon
id|type
op_assign
l_string|&quot;Int.&quot;
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_eq
id|USB_SPEED_HIGH
)paren
(brace
id|interval
op_assign
l_int|1
op_lshift
(paren
id|desc-&gt;bInterval
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|interval
op_assign
id|desc-&gt;bInterval
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* &quot;can&squot;t happen&quot; */
r_return
id|start
suffix:semicolon
)brace
id|interval
op_mul_assign
(paren
id|speed
op_eq
id|USB_SPEED_HIGH
)paren
ques
c_cond
l_int|125
suffix:colon
l_int|1000
suffix:semicolon
r_if
c_cond
(paren
id|interval
op_mod
l_int|1000
)paren
id|unit
op_assign
l_char|&squot;u&squot;
suffix:semicolon
r_else
(brace
id|unit
op_assign
l_char|&squot;m&squot;
suffix:semicolon
id|interval
op_div_assign
l_int|1000
suffix:semicolon
)brace
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_endpt
comma
id|desc-&gt;bEndpointAddress
comma
id|dir
comma
id|desc-&gt;bmAttributes
comma
id|type
comma
(paren
id|desc-&gt;wMaxPacketSize
op_amp
l_int|0x07ff
)paren
op_star
id|bandwidth
comma
id|interval
comma
id|unit
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
DECL|function|usb_dump_interface_descriptor
r_static
r_char
op_star
id|usb_dump_interface_descriptor
c_func
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_interface
op_star
id|iface
comma
r_int
id|setno
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|desc
op_assign
op_amp
id|iface-&gt;altsetting
(braket
id|setno
)braket
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_iface
comma
id|desc-&gt;bInterfaceNumber
comma
id|desc-&gt;bAlternateSetting
comma
id|desc-&gt;bNumEndpoints
comma
id|desc-&gt;bInterfaceClass
comma
id|class_decode
c_func
(paren
id|desc-&gt;bInterfaceClass
)paren
comma
id|desc-&gt;bInterfaceSubClass
comma
id|desc-&gt;bInterfaceProtocol
comma
id|iface-&gt;driver
ques
c_cond
id|iface-&gt;driver-&gt;name
suffix:colon
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
DECL|function|usb_dump_interface
r_static
r_char
op_star
id|usb_dump_interface
c_func
(paren
r_int
id|speed
comma
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_interface
op_star
id|iface
comma
r_int
id|setno
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|desc
op_assign
op_amp
id|iface-&gt;altsetting
(braket
id|setno
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|start
op_assign
id|usb_dump_interface_descriptor
c_func
(paren
id|start
comma
id|end
comma
id|iface
comma
id|setno
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
OL
id|desc-&gt;bNumEndpoints
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|usb_dump_endpoint_descriptor
c_func
(paren
id|speed
comma
id|start
comma
id|end
comma
id|desc-&gt;endpoint
op_plus
id|i
)paren
suffix:semicolon
)brace
r_return
id|start
suffix:semicolon
)brace
multiline_comment|/* TBD:&n; * 0. TBDs&n; * 1. marking active config and ifaces (code lists all, but should mark&n; *    which ones are active, if any)&n; * 2. add &lt;halted&gt; status to each endpoint line&n; */
DECL|function|usb_dump_config_descriptor
r_static
r_char
op_star
id|usb_dump_config_descriptor
c_func
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_config_descriptor
op_star
id|desc
comma
r_int
id|active
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_config
comma
id|active
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
comma
multiline_comment|/* mark active/actual/current cfg. */
id|desc-&gt;bNumInterfaces
comma
id|desc-&gt;bConfigurationValue
comma
id|desc-&gt;bmAttributes
comma
id|desc-&gt;MaxPower
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
DECL|function|usb_dump_config
r_static
r_char
op_star
id|usb_dump_config
(paren
r_int
id|speed
comma
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_config_descriptor
op_star
id|config
comma
r_int
id|active
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|usb_interface
op_star
id|interface
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|config
)paren
multiline_comment|/* getting these some in 2.3.7; none in 2.3.6 */
r_return
id|start
op_plus
id|sprintf
c_func
(paren
id|start
comma
l_string|&quot;(null Cfg. desc.)&bslash;n&quot;
)paren
suffix:semicolon
id|start
op_assign
id|usb_dump_config_descriptor
c_func
(paren
id|start
comma
id|end
comma
id|config
comma
id|active
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
OL
id|config-&gt;bNumInterfaces
suffix:semicolon
id|i
op_increment
)paren
(brace
id|interface
op_assign
id|config-&gt;interface
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interface
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|interface-&gt;num_altsetting
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|usb_dump_interface
c_func
(paren
id|speed
comma
id|start
comma
id|end
comma
id|interface
comma
id|j
)paren
suffix:semicolon
)brace
)brace
r_return
id|start
suffix:semicolon
)brace
multiline_comment|/*&n; * Dump the different USB descriptors.&n; */
DECL|function|usb_dump_device_descriptor
r_static
r_char
op_star
id|usb_dump_device_descriptor
c_func
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_device_descriptor
op_star
id|desc
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_add_assign
id|sprintf
(paren
id|start
comma
id|format_device1
comma
id|desc-&gt;bcdUSB
op_rshift
l_int|8
comma
id|desc-&gt;bcdUSB
op_amp
l_int|0xff
comma
id|desc-&gt;bDeviceClass
comma
id|class_decode
(paren
id|desc-&gt;bDeviceClass
)paren
comma
id|desc-&gt;bDeviceSubClass
comma
id|desc-&gt;bDeviceProtocol
comma
id|desc-&gt;bMaxPacketSize0
comma
id|desc-&gt;bNumConfigurations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_device2
comma
id|desc-&gt;idVendor
comma
id|desc-&gt;idProduct
comma
id|desc-&gt;bcdDevice
op_rshift
l_int|8
comma
id|desc-&gt;bcdDevice
op_amp
l_int|0xff
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
multiline_comment|/*&n; * Dump the different strings that this device holds.&n; */
DECL|function|usb_dump_device_strings
r_static
r_char
op_star
id|usb_dump_device_strings
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
l_int|128
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
id|start
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;descriptor.iManufacturer
)paren
(brace
r_if
c_cond
(paren
id|usb_string
c_func
(paren
id|dev
comma
id|dev-&gt;descriptor.iManufacturer
comma
id|buf
comma
l_int|128
)paren
OG
l_int|0
)paren
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_string_manufacturer
comma
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;descriptor.iProduct
)paren
(brace
r_if
c_cond
(paren
id|usb_string
c_func
(paren
id|dev
comma
id|dev-&gt;descriptor.iProduct
comma
id|buf
comma
l_int|128
)paren
OG
l_int|0
)paren
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_string_product
comma
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_goto
id|out
suffix:semicolon
macro_line|#ifdef ALLOW_SERIAL_NUMBER
r_if
c_cond
(paren
id|dev-&gt;descriptor.iSerialNumber
)paren
(brace
r_if
c_cond
(paren
id|usb_string
c_func
(paren
id|dev
comma
id|dev-&gt;descriptor.iSerialNumber
comma
id|buf
comma
l_int|128
)paren
OG
l_int|0
)paren
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
id|format_string_serialnumber
comma
id|buf
)paren
suffix:semicolon
)brace
macro_line|#endif
id|out
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
DECL|function|usb_dump_desc
r_static
r_char
op_star
id|usb_dump_desc
c_func
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|usb_dump_device_descriptor
c_func
(paren
id|start
comma
id|end
comma
op_amp
id|dev-&gt;descriptor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|usb_dump_device_strings
(paren
id|start
comma
id|end
comma
id|dev
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
OL
id|dev-&gt;descriptor.bNumConfigurations
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_assign
id|usb_dump_config
c_func
(paren
id|dev-&gt;speed
comma
id|start
comma
id|end
comma
id|dev-&gt;config
op_plus
id|i
comma
multiline_comment|/* active ? */
(paren
id|dev-&gt;config
op_plus
id|i
)paren
op_eq
id|dev-&gt;actconfig
)paren
suffix:semicolon
)brace
r_return
id|start
suffix:semicolon
)brace
macro_line|#ifdef PROC_EXTRA /* TBD: may want to add this code later */
DECL|function|usb_dump_hub_descriptor
r_static
r_char
op_star
id|usb_dump_hub_descriptor
c_func
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_hub_descriptor
op_star
id|desc
)paren
(brace
r_int
id|leng
op_assign
id|USB_DT_HUB_NONVAR_SIZE
suffix:semicolon
r_int
r_char
op_star
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|desc
suffix:semicolon
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
l_string|&quot;Interface:&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|leng
op_logical_and
id|start
op_le
id|end
)paren
(brace
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
l_string|&quot; %02x&quot;
comma
op_star
id|ptr
)paren
suffix:semicolon
id|ptr
op_increment
suffix:semicolon
id|leng
op_decrement
suffix:semicolon
)brace
op_star
id|start
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
DECL|function|usb_dump_string
r_static
r_char
op_star
id|usb_dump_string
c_func
(paren
r_char
op_star
id|start
comma
r_char
op_star
id|end
comma
r_const
r_struct
id|usb_device
op_star
id|dev
comma
r_char
op_star
id|id
comma
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|start
OG
id|end
)paren
r_return
id|start
suffix:semicolon
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
l_string|&quot;Interface:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
op_le
id|dev-&gt;maxstring
op_logical_and
id|dev-&gt;stringindex
op_logical_and
id|dev-&gt;stringindex
(braket
id|index
)braket
)paren
id|start
op_add_assign
id|sprintf
c_func
(paren
id|start
comma
l_string|&quot;%s: %.100s &quot;
comma
id|id
comma
id|dev-&gt;stringindex
(braket
id|index
)braket
)paren
suffix:semicolon
r_return
id|start
suffix:semicolon
)brace
macro_line|#endif /* PROC_EXTRA */
multiline_comment|/*****************************************************************/
multiline_comment|/* This is a recursive function. Parameters:&n; * buffer - the user-space buffer to write data into&n; * nbytes - the maximum number of bytes to write&n; * skip_bytes - the number of bytes to skip before writing anything&n; * file_offset - the offset into the devices file on completion&n; */
DECL|function|usb_device_dump
r_static
id|ssize_t
id|usb_device_dump
c_func
(paren
r_char
op_star
op_star
id|buffer
comma
r_int
op_star
id|nbytes
comma
id|loff_t
op_star
id|skip_bytes
comma
id|loff_t
op_star
id|file_offset
comma
r_struct
id|usb_device
op_star
id|usbdev
comma
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|level
comma
r_int
id|index
comma
r_int
id|count
)paren
(brace
r_int
id|chix
suffix:semicolon
r_int
id|ret
comma
id|cnt
op_assign
l_int|0
suffix:semicolon
r_int
id|parent_devnum
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|pages_start
comma
op_star
id|data_end
comma
op_star
id|speed
suffix:semicolon
r_int
r_int
id|length
suffix:semicolon
id|ssize_t
id|total_written
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t bother with anything else if we&squot;re not writing any data */
r_if
c_cond
(paren
op_star
id|nbytes
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|level
OG
id|MAX_TOPO_LEVEL
)paren
r_return
id|total_written
suffix:semicolon
multiline_comment|/* allocate 2^1 pages = 8K (on i386); should be more than enough for one device */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pages_start
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|1
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|usbdev-&gt;parent
op_logical_and
id|usbdev-&gt;parent-&gt;devnum
op_ne
op_minus
l_int|1
)paren
id|parent_devnum
op_assign
id|usbdev-&gt;parent-&gt;devnum
suffix:semicolon
multiline_comment|/*&n;&t; * So the root hub&squot;s parent is 0 and any device that is&n;&t; * plugged into the root hub has a parent of 0.&n;&t; */
r_switch
c_cond
(paren
id|usbdev-&gt;speed
)paren
(brace
r_case
id|USB_SPEED_LOW
suffix:colon
id|speed
op_assign
l_string|&quot;1.5&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_UNKNOWN
suffix:colon
multiline_comment|/* usb 1.1 root hub code */
r_case
id|USB_SPEED_FULL
suffix:colon
id|speed
op_assign
l_string|&quot;12 &quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USB_SPEED_HIGH
suffix:colon
id|speed
op_assign
l_string|&quot;480&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|speed
op_assign
l_string|&quot;?? &quot;
suffix:semicolon
)brace
id|data_end
op_assign
id|pages_start
op_plus
id|sprintf
c_func
(paren
id|pages_start
comma
id|format_topo
comma
id|bus-&gt;busnum
comma
id|level
comma
id|parent_devnum
comma
id|index
comma
id|count
comma
id|usbdev-&gt;devnum
comma
id|speed
comma
id|usbdev-&gt;maxchild
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * level = topology-tier level;&n;&t; * parent_devnum = parent device number;&n;&t; * index = parent&squot;s connector number;&n;&t; * count = device count at this level&n;&t; */
multiline_comment|/* If this is the root hub, display the bandwidth information */
r_if
c_cond
(paren
id|level
op_eq
l_int|0
)paren
(brace
r_int
id|max
suffix:semicolon
multiline_comment|/* high speed reserves 80%, full/low reserves 90% */
r_if
c_cond
(paren
id|usbdev-&gt;speed
op_eq
id|USB_SPEED_HIGH
)paren
id|max
op_assign
l_int|800
suffix:semicolon
r_else
id|max
op_assign
id|FRAME_TIME_MAX_USECS_ALLOC
suffix:semicolon
multiline_comment|/* report &quot;average&quot; periodic allocation over a microsecond.&n;&t;&t; * the schedules are actually bursty, HCDs need to deal with&n;&t;&t; * that and just compute/report this average.&n;&t;&t; */
id|data_end
op_add_assign
id|sprintf
c_func
(paren
id|data_end
comma
id|format_bandwidth
comma
id|bus-&gt;bandwidth_allocated
comma
id|max
comma
(paren
l_int|100
op_star
id|bus-&gt;bandwidth_allocated
op_plus
id|max
op_div
l_int|2
)paren
op_div
id|max
comma
id|bus-&gt;bandwidth_int_reqs
comma
id|bus-&gt;bandwidth_isoc_reqs
)paren
suffix:semicolon
)brace
id|data_end
op_assign
id|usb_dump_desc
c_func
(paren
id|data_end
comma
id|pages_start
op_plus
(paren
l_int|2
op_star
id|PAGE_SIZE
)paren
op_minus
l_int|256
comma
id|usbdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data_end
OG
(paren
id|pages_start
op_plus
(paren
l_int|2
op_star
id|PAGE_SIZE
)paren
op_minus
l_int|256
)paren
)paren
id|data_end
op_add_assign
id|sprintf
c_func
(paren
id|data_end
comma
l_string|&quot;(truncated)&bslash;n&quot;
)paren
suffix:semicolon
id|length
op_assign
id|data_end
op_minus
id|pages_start
suffix:semicolon
multiline_comment|/* if we can start copying some data to the user */
r_if
c_cond
(paren
id|length
OG
op_star
id|skip_bytes
)paren
(brace
id|length
op_sub_assign
op_star
id|skip_bytes
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
op_star
id|nbytes
)paren
id|length
op_assign
op_star
id|nbytes
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_star
id|buffer
comma
id|pages_start
op_plus
op_star
id|skip_bytes
comma
id|length
)paren
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pages_start
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|total_written
op_eq
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|total_written
suffix:semicolon
)brace
op_star
id|nbytes
op_sub_assign
id|length
suffix:semicolon
op_star
id|file_offset
op_add_assign
id|length
suffix:semicolon
id|total_written
op_add_assign
id|length
suffix:semicolon
op_star
id|buffer
op_add_assign
id|length
suffix:semicolon
op_star
id|skip_bytes
op_assign
l_int|0
suffix:semicolon
)brace
r_else
op_star
id|skip_bytes
op_sub_assign
id|length
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pages_start
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Now look at all of this device&squot;s children. */
r_for
c_loop
(paren
id|chix
op_assign
l_int|0
suffix:semicolon
id|chix
OL
id|usbdev-&gt;maxchild
suffix:semicolon
id|chix
op_increment
)paren
(brace
r_if
c_cond
(paren
id|usbdev-&gt;children
(braket
id|chix
)braket
)paren
(brace
id|ret
op_assign
id|usb_device_dump
c_func
(paren
id|buffer
comma
id|nbytes
comma
id|skip_bytes
comma
id|file_offset
comma
id|usbdev-&gt;children
(braket
id|chix
)braket
comma
id|bus
comma
id|level
op_plus
l_int|1
comma
id|chix
comma
op_increment
id|cnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|EFAULT
)paren
r_return
id|total_written
suffix:semicolon
id|total_written
op_add_assign
id|ret
suffix:semicolon
)brace
)brace
r_return
id|total_written
suffix:semicolon
)brace
DECL|function|usb_device_read
r_static
id|ssize_t
id|usb_device_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|list_head
op_star
id|buslist
suffix:semicolon
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
id|ssize_t
id|ret
comma
id|total_written
op_assign
l_int|0
suffix:semicolon
id|loff_t
id|skip_bytes
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|nbytes
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* enumerate busses */
id|down
(paren
op_amp
id|usb_bus_list_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|buslist
op_assign
id|usb_bus_list.next
suffix:semicolon
id|buslist
op_ne
op_amp
id|usb_bus_list
suffix:semicolon
id|buslist
op_assign
id|buslist-&gt;next
)paren
(brace
multiline_comment|/* print devices for this bus */
id|bus
op_assign
id|list_entry
c_func
(paren
id|buslist
comma
r_struct
id|usb_bus
comma
id|bus_list
)paren
suffix:semicolon
multiline_comment|/* recurse through all children of the root hub */
id|ret
op_assign
id|usb_device_dump
c_func
(paren
op_amp
id|buf
comma
op_amp
id|nbytes
comma
op_amp
id|skip_bytes
comma
id|ppos
comma
id|bus-&gt;root_hub
comma
id|bus
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|total_written
op_add_assign
id|ret
suffix:semicolon
)brace
id|up
(paren
op_amp
id|usb_bus_list_lock
)paren
suffix:semicolon
r_return
id|total_written
suffix:semicolon
)brace
multiline_comment|/* Kernel lock for &quot;lastev&quot; protection */
DECL|function|usb_device_poll
r_static
r_int
r_int
id|usb_device_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_struct
id|usb_device_status
op_star
id|st
op_assign
(paren
r_struct
id|usb_device_status
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|st
)paren
(brace
id|st
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_device_status
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|st
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|POLLIN
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * need to prevent the module from being unloaded, since&n;&t;&t; * proc_unregister does not call the release method and&n;&t;&t; * we would have a memory leak&n;&t;&t; */
id|st-&gt;lastev
op_assign
id|conndiscevcnt
suffix:semicolon
id|file-&gt;private_data
op_assign
id|st
suffix:semicolon
id|mask
op_assign
id|POLLIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|deviceconndiscwq
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;lastev
op_ne
id|conndiscevcnt
)paren
id|mask
op_or_assign
id|POLLIN
suffix:semicolon
id|st-&gt;lastev
op_assign
id|conndiscevcnt
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|usb_device_open
r_static
r_int
id|usb_device_open
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
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_device_release
r_static
r_int
id|usb_device_release
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
r_if
c_cond
(paren
id|file-&gt;private_data
)paren
(brace
id|kfree
c_func
(paren
id|file-&gt;private_data
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_device_lseek
r_static
id|loff_t
id|usb_device_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
id|loff_t
id|ret
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|usbdevfs_devices_fops
r_struct
id|file_operations
id|usbdevfs_devices_fops
op_assign
(brace
id|llseek
suffix:colon
id|usb_device_lseek
comma
id|read
suffix:colon
id|usb_device_read
comma
id|poll
suffix:colon
id|usb_device_poll
comma
id|open
suffix:colon
id|usb_device_open
comma
id|release
suffix:colon
id|usb_device_release
comma
)brace
suffix:semicolon
eof