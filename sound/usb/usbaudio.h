macro_line|#ifndef __USBAUDIO_H
DECL|macro|__USBAUDIO_H
mdefine_line|#define __USBAUDIO_H
multiline_comment|/*&n; *   (Tentative) USB Audio Driver for ALSA&n; *&n; *   Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/*&n; */
DECL|macro|USB_SUBCLASS_AUDIO_CONTROL
mdefine_line|#define USB_SUBCLASS_AUDIO_CONTROL&t;0x01
DECL|macro|USB_SUBCLASS_AUDIO_STREAMING
mdefine_line|#define USB_SUBCLASS_AUDIO_STREAMING&t;0x02
DECL|macro|USB_SUBCLASS_MIDI_STREAMING
mdefine_line|#define USB_SUBCLASS_MIDI_STREAMING&t;0x03
DECL|macro|USB_SUBCLASS_VENDOR_SPEC
mdefine_line|#define USB_SUBCLASS_VENDOR_SPEC&t;0xff
DECL|macro|USB_DT_CS_DEVICE
mdefine_line|#define USB_DT_CS_DEVICE                0x21
DECL|macro|USB_DT_CS_CONFIG
mdefine_line|#define USB_DT_CS_CONFIG                0x22
DECL|macro|USB_DT_CS_STRING
mdefine_line|#define USB_DT_CS_STRING                0x23
DECL|macro|USB_DT_CS_INTERFACE
mdefine_line|#define USB_DT_CS_INTERFACE             0x24
DECL|macro|USB_DT_CS_ENDPOINT
mdefine_line|#define USB_DT_CS_ENDPOINT              0x25
DECL|macro|CS_AUDIO_UNDEFINED
mdefine_line|#define CS_AUDIO_UNDEFINED&t;&t;0x20
DECL|macro|CS_AUDIO_DEVICE
mdefine_line|#define CS_AUDIO_DEVICE&t;&t;&t;0x21
DECL|macro|CS_AUDIO_CONFIGURATION
mdefine_line|#define CS_AUDIO_CONFIGURATION&t;&t;0x22
DECL|macro|CS_AUDIO_STRING
mdefine_line|#define CS_AUDIO_STRING&t;&t;&t;0x23
DECL|macro|CS_AUDIO_INTERFACE
mdefine_line|#define CS_AUDIO_INTERFACE&t;&t;0x24
DECL|macro|CS_AUDIO_ENDPOINT
mdefine_line|#define CS_AUDIO_ENDPOINT&t;&t;0x25
DECL|macro|HEADER
mdefine_line|#define HEADER&t;&t;&t;&t;0x01
DECL|macro|INPUT_TERMINAL
mdefine_line|#define INPUT_TERMINAL&t;&t;&t;0x02
DECL|macro|OUTPUT_TERMINAL
mdefine_line|#define OUTPUT_TERMINAL&t;&t;&t;0x03
DECL|macro|MIXER_UNIT
mdefine_line|#define MIXER_UNIT&t;&t;&t;0x04
DECL|macro|SELECTOR_UNIT
mdefine_line|#define SELECTOR_UNIT&t;&t;&t;0x05
DECL|macro|FEATURE_UNIT
mdefine_line|#define FEATURE_UNIT&t;&t;&t;0x06
DECL|macro|PROCESSING_UNIT
mdefine_line|#define PROCESSING_UNIT&t;&t;&t;0x07
DECL|macro|EXTENSION_UNIT
mdefine_line|#define EXTENSION_UNIT&t;&t;&t;0x08
DECL|macro|AS_GENERAL
mdefine_line|#define AS_GENERAL&t;&t;&t;0x01
DECL|macro|FORMAT_TYPE
mdefine_line|#define FORMAT_TYPE&t;&t;&t;0x02
DECL|macro|FORMAT_SPECIFIC
mdefine_line|#define FORMAT_SPECIFIC&t;&t;&t;0x03
DECL|macro|EP_GENERAL
mdefine_line|#define EP_GENERAL&t;&t;&t;0x01
DECL|macro|MS_GENERAL
mdefine_line|#define MS_GENERAL&t;&t;&t;0x01
DECL|macro|MIDI_IN_JACK
mdefine_line|#define MIDI_IN_JACK&t;&t;&t;0x02
DECL|macro|MIDI_OUT_JACK
mdefine_line|#define MIDI_OUT_JACK&t;&t;&t;0x03
multiline_comment|/* endpoint attributes */
DECL|macro|EP_ATTR_MASK
mdefine_line|#define EP_ATTR_MASK&t;&t;&t;0x0c
DECL|macro|EP_ATTR_ASYNC
mdefine_line|#define EP_ATTR_ASYNC&t;&t;&t;0x04
DECL|macro|EP_ATTR_ADAPTIVE
mdefine_line|#define EP_ATTR_ADAPTIVE&t;&t;0x08
DECL|macro|EP_ATTR_SYNC
mdefine_line|#define EP_ATTR_SYNC&t;&t;&t;0x0c
multiline_comment|/* cs endpoint attributes */
DECL|macro|EP_CS_ATTR_SAMPLE_RATE
mdefine_line|#define EP_CS_ATTR_SAMPLE_RATE&t;&t;0x01
DECL|macro|EP_CS_ATTR_PITCH_CONTROL
mdefine_line|#define EP_CS_ATTR_PITCH_CONTROL&t;0x02
DECL|macro|EP_CS_ATTR_FILL_MAX
mdefine_line|#define EP_CS_ATTR_FILL_MAX&t;&t;0x80
multiline_comment|/* Audio Class specific Request Codes */
DECL|macro|SET_CUR
mdefine_line|#define SET_CUR    0x01
DECL|macro|GET_CUR
mdefine_line|#define GET_CUR    0x81
DECL|macro|SET_MIN
mdefine_line|#define SET_MIN    0x02
DECL|macro|GET_MIN
mdefine_line|#define GET_MIN    0x82
DECL|macro|SET_MAX
mdefine_line|#define SET_MAX    0x03
DECL|macro|GET_MAX
mdefine_line|#define GET_MAX    0x83
DECL|macro|SET_RES
mdefine_line|#define SET_RES    0x04
DECL|macro|GET_RES
mdefine_line|#define GET_RES    0x84
DECL|macro|SET_MEM
mdefine_line|#define SET_MEM    0x05
DECL|macro|GET_MEM
mdefine_line|#define GET_MEM    0x85
DECL|macro|GET_STAT
mdefine_line|#define GET_STAT   0xff
multiline_comment|/* Terminal Control Selectors */
DECL|macro|COPY_PROTECT_CONTROL
mdefine_line|#define COPY_PROTECT_CONTROL       0x01
multiline_comment|/* Endpoint Control Selectors */
DECL|macro|SAMPLING_FREQ_CONTROL
mdefine_line|#define SAMPLING_FREQ_CONTROL      0x01
DECL|macro|PITCH_CONTROL
mdefine_line|#define PITCH_CONTROL              0x02
multiline_comment|/* Format Types */
DECL|macro|USB_FORMAT_TYPE_I
mdefine_line|#define USB_FORMAT_TYPE_I&t;0x01
DECL|macro|USB_FORMAT_TYPE_II
mdefine_line|#define USB_FORMAT_TYPE_II&t;0x02
DECL|macro|USB_FORMAT_TYPE_III
mdefine_line|#define USB_FORMAT_TYPE_III&t;0x03
multiline_comment|/* type I */
DECL|macro|USB_AUDIO_FORMAT_PCM
mdefine_line|#define USB_AUDIO_FORMAT_PCM&t;0x01
DECL|macro|USB_AUDIO_FORMAT_PCM8
mdefine_line|#define USB_AUDIO_FORMAT_PCM8&t;0x02
DECL|macro|USB_AUDIO_FORMAT_IEEE_FLOAT
mdefine_line|#define USB_AUDIO_FORMAT_IEEE_FLOAT&t;0x03
DECL|macro|USB_AUDIO_FORMAT_ALAW
mdefine_line|#define USB_AUDIO_FORMAT_ALAW&t;0x04
DECL|macro|USB_AUDIO_FORMAT_MU_LAW
mdefine_line|#define USB_AUDIO_FORMAT_MU_LAW&t;0x05
multiline_comment|/* type II */
DECL|macro|USB_AUDIO_FORMAT_MPEG
mdefine_line|#define USB_AUDIO_FORMAT_MPEG&t;0x1001
DECL|macro|USB_AUDIO_FORMAT_AC3
mdefine_line|#define USB_AUDIO_FORMAT_AC3&t;0x1002
multiline_comment|/* type III */
DECL|macro|USB_AUDIO_FORMAT_IEC1937_AC3
mdefine_line|#define USB_AUDIO_FORMAT_IEC1937_AC3&t;0x2001
DECL|macro|USB_AUDIO_FORMAT_IEC1937_MPEG1_LAYER1
mdefine_line|#define USB_AUDIO_FORMAT_IEC1937_MPEG1_LAYER1&t;0x2002
DECL|macro|USB_AUDIO_FORMAT_IEC1937_MPEG2_NOEXT
mdefine_line|#define USB_AUDIO_FORMAT_IEC1937_MPEG2_NOEXT&t;0x2003
DECL|macro|USB_AUDIO_FORMAT_IEC1937_MPEG2_EXT
mdefine_line|#define USB_AUDIO_FORMAT_IEC1937_MPEG2_EXT&t;0x2004
DECL|macro|USB_AUDIO_FORMAT_IEC1937_MPEG2_LAYER1_LS
mdefine_line|#define USB_AUDIO_FORMAT_IEC1937_MPEG2_LAYER1_LS&t;0x2005
DECL|macro|USB_AUDIO_FORMAT_IEC1937_MPEG2_LAYER23_LS
mdefine_line|#define USB_AUDIO_FORMAT_IEC1937_MPEG2_LAYER23_LS&t;0x2006
multiline_comment|/* maximum number of endpoints per interface */
DECL|macro|MIDI_MAX_ENDPOINTS
mdefine_line|#define MIDI_MAX_ENDPOINTS 2
multiline_comment|/*&n; */
DECL|typedef|snd_usb_audio_t
r_typedef
r_struct
id|snd_usb_audio
id|snd_usb_audio_t
suffix:semicolon
DECL|struct|snd_usb_audio
r_struct
id|snd_usb_audio
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
DECL|member|num_interfaces
r_int
id|num_interfaces
suffix:semicolon
DECL|member|pcm_list
r_struct
id|list_head
id|pcm_list
suffix:semicolon
multiline_comment|/* list of pcm streams */
DECL|member|pcm_devs
r_int
id|pcm_devs
suffix:semicolon
DECL|member|midi_list
r_struct
id|list_head
id|midi_list
suffix:semicolon
multiline_comment|/* list of midi interfaces */
DECL|member|next_midi_device
r_int
id|next_midi_device
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Information about devices with broken descriptors&n; */
DECL|macro|QUIRK_ANY_INTERFACE
mdefine_line|#define QUIRK_ANY_INTERFACE -1
DECL|macro|QUIRK_MIDI_FIXED_ENDPOINT
mdefine_line|#define QUIRK_MIDI_FIXED_ENDPOINT&t;0
DECL|macro|QUIRK_MIDI_YAMAHA
mdefine_line|#define QUIRK_MIDI_YAMAHA&t;&t;1
DECL|macro|QUIRK_MIDI_MIDIMAN
mdefine_line|#define QUIRK_MIDI_MIDIMAN&t;&t;2
DECL|macro|QUIRK_COMPOSITE
mdefine_line|#define QUIRK_COMPOSITE&t;&t;&t;3
DECL|macro|QUIRK_AUDIO_FIXED_ENDPOINT
mdefine_line|#define QUIRK_AUDIO_FIXED_ENDPOINT&t;4
DECL|macro|QUIRK_AUDIO_STANDARD_INTERFACE
mdefine_line|#define QUIRK_AUDIO_STANDARD_INTERFACE&t;5
DECL|macro|QUIRK_MIDI_STANDARD_INTERFACE
mdefine_line|#define QUIRK_MIDI_STANDARD_INTERFACE&t;6
DECL|typedef|snd_usb_audio_quirk_t
r_typedef
r_struct
id|snd_usb_audio_quirk
id|snd_usb_audio_quirk_t
suffix:semicolon
DECL|typedef|snd_usb_midi_endpoint_info_t
r_typedef
r_struct
id|snd_usb_midi_endpoint_info
id|snd_usb_midi_endpoint_info_t
suffix:semicolon
DECL|struct|snd_usb_audio_quirk
r_struct
id|snd_usb_audio_quirk
(brace
DECL|member|vendor_name
r_const
r_char
op_star
id|vendor_name
suffix:semicolon
DECL|member|product_name
r_const
r_char
op_star
id|product_name
suffix:semicolon
DECL|member|ifnum
r_int16
id|ifnum
suffix:semicolon
DECL|member|type
r_int16
id|type
suffix:semicolon
DECL|member|data
r_const
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* data for QUIRK_MIDI_FIXED_ENDPOINT */
DECL|struct|snd_usb_midi_endpoint_info
r_struct
id|snd_usb_midi_endpoint_info
(brace
DECL|member|out_ep
DECL|member|in_ep
r_int8
id|out_ep
comma
id|in_ep
suffix:semicolon
multiline_comment|/* ep number, 0 autodetect */
DECL|member|out_cables
r_uint16
id|out_cables
suffix:semicolon
multiline_comment|/* bitmask */
DECL|member|in_cables
r_uint16
id|in_cables
suffix:semicolon
multiline_comment|/* bitmask */
)brace
suffix:semicolon
multiline_comment|/* for QUIRK_MIDI_YAMAHA, data is NULL */
multiline_comment|/* for QUIRK_MIDI_MIDIMAN, data points to a snd_usb_midi_endpoint_info&n; * structure (out_cables and in_cables only) */
multiline_comment|/* for QUIRK_COMPOSITE, data points to an array of snd_usb_audio_quirk&n; * structures, terminated with .ifnum = -1 */
multiline_comment|/* for QUIRK_AUDIO_FIXED_ENDPOINT, data points to an audioformat structure */
multiline_comment|/* for QUIRK_AUDIO/MIDI_STANDARD_INTERFACE, data is NULL */
multiline_comment|/*&n; */
DECL|macro|combine_word
mdefine_line|#define combine_word(s)    ((*s) | ((unsigned int)(s)[1] &lt;&lt; 8))
DECL|macro|combine_triple
mdefine_line|#define combine_triple(s)  (combine_word(s) | ((unsigned int)(s)[2] &lt;&lt; 16))
DECL|macro|combine_quad
mdefine_line|#define combine_quad(s)    (combine_triple(s) | ((unsigned int)(s)[3] &lt;&lt; 24))
r_int
r_int
id|snd_usb_combine_bytes
c_func
(paren
r_int
r_char
op_star
id|bytes
comma
r_int
id|size
)paren
suffix:semicolon
r_void
op_star
id|snd_usb_find_desc
c_func
(paren
r_void
op_star
id|descstart
comma
r_int
id|desclen
comma
r_void
op_star
id|after
comma
id|u8
id|dtype
)paren
suffix:semicolon
r_void
op_star
id|snd_usb_find_csint_desc
c_func
(paren
r_void
op_star
id|descstart
comma
r_int
id|desclen
comma
r_void
op_star
id|after
comma
id|u8
id|dsubtype
)paren
suffix:semicolon
r_int
id|snd_usb_create_mixer
c_func
(paren
id|snd_usb_audio_t
op_star
id|chip
comma
r_int
id|ctrlif
)paren
suffix:semicolon
r_int
id|snd_usb_create_midi_interface
c_func
(paren
id|snd_usb_audio_t
op_star
id|chip
comma
r_struct
id|usb_interface
op_star
id|iface
comma
r_const
id|snd_usb_audio_quirk_t
op_star
id|quirk
)paren
suffix:semicolon
r_void
id|snd_usbmidi_disconnect
c_func
(paren
r_struct
id|list_head
op_star
id|p
comma
r_struct
id|usb_driver
op_star
id|driver
)paren
suffix:semicolon
multiline_comment|/*&n; * retrieve usb_interface descriptor from the host interface&n; * (conditional for compatibility with the older API)&n; */
macro_line|#ifndef get_iface_desc
DECL|macro|get_iface_desc
mdefine_line|#define get_iface_desc(iface)&t;(&amp;iface-&gt;desc)
DECL|macro|get_endpoint
mdefine_line|#define get_endpoint(alt,ep)&t;(&amp;(alt)-&gt;endpoint[ep].desc)
DECL|macro|get_ep_desc
mdefine_line|#define get_ep_desc(ep)&t;&t;(&amp;(ep)-&gt;desc)
DECL|macro|get_cfg_desc
mdefine_line|#define get_cfg_desc(cfg)&t;(&amp;(cfg)-&gt;desc)
macro_line|#endif
macro_line|#ifndef usb_pipe_needs_resubmit
DECL|macro|usb_pipe_needs_resubmit
mdefine_line|#define usb_pipe_needs_resubmit(pipe) 1
macro_line|#endif
macro_line|#ifndef snd_usb_complete_callback
DECL|macro|snd_usb_complete_callback
mdefine_line|#define snd_usb_complete_callback(x) (x)
macro_line|#endif
macro_line|#endif /* __USBAUDIO_H */
eof
