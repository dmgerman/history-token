multiline_comment|/*&n;  usb-midi.h  --  USB-MIDI driver&n;&n;  Copyright (C) 2001&n;      NAGANO Daisuke &lt;breeze.nagano@nifty.ne.jp&gt;&n;&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* ------------------------------------------------------------------------- */
macro_line|#ifndef _USB_MIDI_H_
DECL|macro|_USB_MIDI_H_
mdefine_line|#define _USB_MIDI_H_
macro_line|#ifndef USB_SUBCLASS_MIDISTREAMING
DECL|macro|USB_SUBCLASS_MIDISTREAMING
mdefine_line|#define USB_SUBCLASS_MIDISTREAMING&t;3
macro_line|#endif
DECL|macro|USB_DT_CS_DEVICE
mdefine_line|#define USB_DT_CS_DEVICE&t;&t;0x21
DECL|macro|USB_DT_CS_CONFIG
mdefine_line|#define USB_DT_CS_CONFIG&t;&t;0x22
DECL|macro|USB_DT_CS_STRING
mdefine_line|#define USB_DT_CS_STRING&t;&t;0x23
DECL|macro|USB_DT_CS_INTERFACE
mdefine_line|#define USB_DT_CS_INTERFACE&t;&t;0x24
DECL|macro|USB_DT_CS_ENDPOINT
mdefine_line|#define USB_DT_CS_ENDPOINT&t;&t;0x25
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* Roland MIDI Devices */
DECL|macro|USB_VENDOR_ID_ROLAND
mdefine_line|#define USB_VENDOR_ID_ROLAND&t;&t;0x0582
DECL|macro|USBMIDI_ROLAND_UA100G
mdefine_line|#define USBMIDI_ROLAND_UA100G&t;&t;0x0000
DECL|macro|USBMIDI_ROLAND_MPU64
mdefine_line|#define USBMIDI_ROLAND_MPU64&t;&t;0x0002
DECL|macro|USBMIDI_ROLAND_SC8850
mdefine_line|#define USBMIDI_ROLAND_SC8850&t;&t;0x0003
DECL|macro|USBMIDI_ROLAND_UM2
mdefine_line|#define USBMIDI_ROLAND_UM2&t;&t;0x0005
DECL|macro|USBMIDI_ROLAND_UM1
mdefine_line|#define USBMIDI_ROLAND_UM1&t;&t;0x0009
DECL|macro|USBMIDI_ROLAND_PC300
mdefine_line|#define USBMIDI_ROLAND_PC300&t;&t;0x0008
multiline_comment|/* YAMAHA MIDI Devices */
DECL|macro|USB_VENDOR_ID_YAMAHA
mdefine_line|#define USB_VENDOR_ID_YAMAHA&t;&t;0x0499
DECL|macro|USBMIDI_YAMAHA_MU1000
mdefine_line|#define USBMIDI_YAMAHA_MU1000&t;&t;0x1001
multiline_comment|/* Steinberg MIDI Devices */
DECL|macro|USB_VENDOR_ID_STEINBERG
mdefine_line|#define USB_VENDOR_ID_STEINBERG&t;&t;0x0763
DECL|macro|USBMIDI_STEINBERG_USB2MIDI
mdefine_line|#define USBMIDI_STEINBERG_USB2MIDI&t;0x1001
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* Supported devices */
DECL|struct|usb_midi_endpoint
r_struct
id|usb_midi_endpoint
(brace
DECL|member|endpoint
r_int
id|endpoint
suffix:semicolon
DECL|member|cableId
r_int
id|cableId
suffix:semicolon
multiline_comment|/* if bit-n == 1 then cableId-n is enabled (n: 0 - 15) */
)brace
suffix:semicolon
DECL|struct|usb_midi_device
r_struct
id|usb_midi_device
(brace
DECL|member|deviceName
r_char
op_star
id|deviceName
suffix:semicolon
DECL|member|idVendor
r_int
id|idVendor
suffix:semicolon
DECL|member|idProduct
r_int
id|idProduct
suffix:semicolon
DECL|member|interface
r_int
id|interface
suffix:semicolon
DECL|member|altSetting
r_int
id|altSetting
suffix:semicolon
multiline_comment|/* -1: auto detect */
DECL|member|in
r_struct
id|usb_midi_endpoint
id|in
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|out
r_struct
id|usb_midi_endpoint
id|out
(braket
l_int|15
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|usb_midi_devices
r_static
r_struct
id|usb_midi_device
id|usb_midi_devices
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* Roland UM-1 */
l_string|&quot;Roland UM-1&quot;
comma
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_UM1
comma
l_int|2
comma
op_minus
l_int|1
comma
(brace
(brace
l_int|0x81
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
(brace
(brace
l_int|0x01
comma
l_int|1
comma
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
)brace
comma
(brace
multiline_comment|/* Roland UM-2 */
l_string|&quot;Roland UM-2&quot;
comma
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_UM2
comma
l_int|2
comma
op_minus
l_int|1
comma
(brace
(brace
l_int|0x81
comma
l_int|3
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
(brace
(brace
l_int|0x01
comma
l_int|3
comma
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
)brace
comma
multiline_comment|/** Next entry courtesy research by Michael Minn &lt;michael@michaelminn.com&gt; **/
(brace
multiline_comment|/* Roland UA-100 */
l_string|&quot;Roland UA-100&quot;
comma
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_UA100G
comma
l_int|2
comma
op_minus
l_int|1
comma
(brace
(brace
l_int|0x82
comma
l_int|7
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/** cables 0,1 and 2 for SYSEX **/
(brace
(brace
l_int|0x02
comma
l_int|7
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
)brace
comma
multiline_comment|/** Next entry courtesy research by Michael Minn &lt;michael@michaelminn.com&gt; **/
(brace
multiline_comment|/* Roland SC8850 */
l_string|&quot;Roland SC8850&quot;
comma
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_SC8850
comma
l_int|2
comma
op_minus
l_int|1
comma
(brace
(brace
l_int|0x81
comma
l_int|15
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
multiline_comment|/** cables 0,1,2, and 3 **/
(brace
(brace
l_int|0x01
comma
l_int|15
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
)brace
comma
(brace
multiline_comment|/* YAMAHA MU1000 */
l_string|&quot;YAMAHA MU1000&quot;
comma
id|USB_VENDOR_ID_YAMAHA
comma
id|USBMIDI_YAMAHA_MU1000
comma
l_int|0
comma
op_minus
l_int|1
comma
(brace
(brace
l_int|0x81
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
(brace
(brace
l_int|0x01
comma
l_int|15
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
)brace
comma
(brace
multiline_comment|/* Roland PC-300 */
l_string|&quot;Roland PC-300&quot;
comma
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_PC300
comma
l_int|2
comma
op_minus
l_int|1
comma
(brace
(brace
l_int|0x81
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
(brace
(brace
l_int|0x01
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
comma
)brace
)brace
suffix:semicolon
DECL|macro|VENDOR_SPECIFIC_USB_MIDI_DEVICES
mdefine_line|#define VENDOR_SPECIFIC_USB_MIDI_DEVICES (sizeof(usb_midi_devices)/sizeof(struct usb_midi_device))
multiline_comment|/* for Hot-Plugging */
DECL|variable|usb_midi_ids
r_static
r_struct
id|usb_device_id
id|usb_midi_ids
(braket
)braket
op_assign
(brace
(brace
id|match_flags
suffix:colon
(paren
id|USB_DEVICE_ID_MATCH_INT_CLASS
op_or
id|USB_DEVICE_ID_MATCH_INT_SUBCLASS
)paren
comma
id|bInterfaceClass
suffix:colon
id|USB_CLASS_AUDIO
comma
id|bInterfaceSubClass
suffix:colon
id|USB_SUBCLASS_MIDISTREAMING
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_UM1
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_UM2
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_UA100G
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_PC300
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_ROLAND
comma
id|USBMIDI_ROLAND_SC8850
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_YAMAHA
comma
id|USBMIDI_YAMAHA_MU1000
)paren
)brace
comma
multiline_comment|/*&t;{ USB_DEVICE( USB_VENDOR_ID_STEINBERG, USBMIDI_STEINBERG_USB2MIDI ) },*/
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|usb_midi_ids
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------------- */
macro_line|#endif /* _USB_MIDI_H_ */
eof
