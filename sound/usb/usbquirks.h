multiline_comment|/*&n; * ALSA USB Audio Driver&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;,&n; *                       Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; *&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/*&n; * The contents of this file are part of the driver&squot;s id_table.&n; *&n; * In a perfect world, this file would be empty.&n; */
DECL|macro|USB_DEVICE_VENDOR_SPEC
mdefine_line|#define USB_DEVICE_VENDOR_SPEC(vend, prod) &bslash;&n;&t;.match_flags = USB_DEVICE_ID_MATCH_VENDOR | &bslash;&n;&t;&t;       USB_DEVICE_ID_MATCH_PRODUCT | &bslash;&n;&t;&t;       USB_DEVICE_ID_MATCH_INT_CLASS, &bslash;&n;&t;.idVendor = vend, &bslash;&n;&t;.idProduct = prod, &bslash;&n;&t;.bInterfaceClass = USB_CLASS_VENDOR_SPEC
multiline_comment|/* Yamaha devices */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1000
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UX256&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1001
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MU1000&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1002
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MU2000&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1003
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MU500&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0499
comma
l_int|0x1004
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UW500&quot;
comma
dot
id|ifnum
op_assign
l_int|3
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1005
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MOTIF6&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1006
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MOTIF7&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1007
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MOTIF8&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1008
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UX96&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1009
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UX16&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0499
comma
l_int|0x100a
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;EOS BX&quot;
comma
dot
id|ifnum
op_assign
l_int|3
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x100e
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;S08&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x100f
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;CLP-150&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0499
comma
l_int|0x1010
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Yamaha&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;CLP-170&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_YAMAHA
)brace
)brace
comma
multiline_comment|/*&n; * Once upon a time people thought, &quot;Wouldn&squot;t it be nice if there was a&n; * standard for USB MIDI devices, so that device drivers would not be forced&n; * to know about the quirks of specific devices?&quot;  So Roland went ahead and&n; * wrote the USB Device Class Definition for MIDI Devices, and the USB-IF&n; * endorsed it, and now everybody designing USB MIDI devices does so in&n; * agreement with this standard (or at least tries to).&n; *&n; * And if you prefer a happy end, you can imagine that Roland devices set a&n; * good example. Instead of being completely fucked up due to the lack of&n; * class-specific descriptors.&n; */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0000
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UA-100&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_ROLAND_UA100
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0002
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UM-4&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x000f
comma
dot
id|in_cables
op_assign
l_int|0x000f
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0003
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SC-8850&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x003f
comma
dot
id|in_cables
op_assign
l_int|0x003f
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0004
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;U-8&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0003
comma
dot
id|in_cables
op_assign
l_int|0x0003
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0005
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UM-2&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0003
comma
dot
id|in_cables
op_assign
l_int|0x0003
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0007
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SC-8820&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0013
comma
dot
id|in_cables
op_assign
l_int|0x0013
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0008
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;PC-300&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0001
comma
dot
id|in_cables
op_assign
l_int|0x0001
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0009
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UM-1&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0001
comma
dot
id|in_cables
op_assign
l_int|0x0001
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x000b
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SK-500&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0013
comma
dot
id|in_cables
op_assign
l_int|0x0013
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x000c
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SC-D70&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0007
comma
dot
id|in_cables
op_assign
l_int|0x0007
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0012
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;Roland&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;XV-5050&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0001
comma
dot
id|in_cables
op_assign
l_int|0x0001
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0014
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UM-880&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x01ff
comma
dot
id|in_cables
op_assign
l_int|0x01ff
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0016
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SD-90&quot;
comma
dot
id|ifnum
op_assign
l_int|2
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x000f
comma
dot
id|in_cables
op_assign
l_int|0x000f
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0023
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UM-550&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x003f
comma
dot
id|in_cables
op_assign
l_int|0x003f
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0582
comma
l_int|0x0025
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UA-20&quot;
comma
dot
id|ifnum
op_assign
l_int|3
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0001
comma
dot
id|in_cables
op_assign
l_int|0x0001
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0027
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SD-20&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0003
comma
dot
id|in_cables
op_assign
l_int|0x0007
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0582
comma
l_int|0x0029
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;SD-80&quot;
comma
dot
id|ifnum
op_assign
l_int|0
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x000f
comma
dot
id|in_cables
op_assign
l_int|0x000f
)brace
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0582
comma
l_int|0x002b
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;EDIROL&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;UA-700&quot;
comma
dot
id|ifnum
op_assign
l_int|3
comma
dot
id|type
op_assign
id|QUIRK_MIDI_FIXED_ENDPOINT
comma
dot
id|data
op_assign
op_amp
(paren
r_const
id|snd_usb_midi_endpoint_info_t
)paren
(brace
dot
id|epnum
op_assign
op_minus
l_int|1
comma
dot
id|out_cables
op_assign
l_int|0x0003
comma
dot
id|in_cables
op_assign
l_int|0x0003
)brace
)brace
)brace
comma
multiline_comment|/* Midiman/M-Audio devices */
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x1002
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MidiSport 2x2&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|2
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x1011
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MidiSport 1x1&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x1015
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;Keystation&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x1021
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MidiSport 4x4&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|4
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x1033
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;MidiSport 8x8&quot;
comma
dot
id|ifnum
op_assign
id|QUIRK_ANY_INTERFACE
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|9
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x2001
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;Quattro&quot;
comma
dot
id|ifnum
op_assign
l_int|9
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
)brace
)brace
comma
(brace
id|USB_DEVICE_VENDOR_SPEC
c_func
(paren
l_int|0x0763
comma
l_int|0x2003
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
r_const
id|snd_usb_audio_quirk_t
)paren
(brace
dot
id|vendor_name
op_assign
l_string|&quot;M-Audio&quot;
comma
dot
id|product_name
op_assign
l_string|&quot;AudioPhile&quot;
comma
dot
id|ifnum
op_assign
l_int|9
comma
dot
id|type
op_assign
id|QUIRK_MIDI_MIDIMAN
comma
dot
id|data
op_assign
(paren
r_void
op_star
)paren
l_int|1
)brace
)brace
comma
DECL|macro|USB_DEVICE_VENDOR_SPEC
macro_line|#undef USB_DEVICE_VENDOR_SPEC
eof
