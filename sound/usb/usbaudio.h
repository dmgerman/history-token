macro_line|#ifndef __USBAUDIO_H
DECL|macro|__USBAUDIO_H
mdefine_line|#define __USBAUDIO_H
multiline_comment|/*&n; *   (Tentative) USB Audio Driver for ALSA&n; *&n; *   Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/*&n; */
DECL|macro|USB_SUBCLASS_AUDIO_CONTROL
mdefine_line|#define USB_SUBCLASS_AUDIO_CONTROL&t;0x01
DECL|macro|USB_SUBCLASS_AUDIO_STREAMING
mdefine_line|#define USB_SUBCLASS_AUDIO_STREAMING&t;0x02
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
)brace
suffix:semicolon
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
comma
r_int
id|iface
comma
r_int
id|altsetting
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
comma
r_int
id|iface
comma
r_int
id|altsetting
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
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
suffix:semicolon
macro_line|#endif /* __USBAUDIO_H */
eof
