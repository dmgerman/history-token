multiline_comment|/*&n; *  Advanced Linux Sound Architecture - ALSA - Driver&n; *  Copyright (c) 1994-2000 by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *                             Abramo Bagnara &lt;abramo@alsa-project.org&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_ASOUND_H
DECL|macro|__SOUND_ASOUND_H
mdefine_line|#define __SOUND_ASOUND_H
macro_line|#if defined(LINUX) || defined(__LINUX__) || defined(__linux__)
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#if  __LITTLE_ENDIAN == 1234
DECL|macro|SNDRV_LITTLE_ENDIAN
mdefine_line|#define SNDRV_LITTLE_ENDIAN
macro_line|#elif __BIG_ENDIAN == 4321
DECL|macro|SNDRV_BIG_ENDIAN
mdefine_line|#define SNDRV_BIG_ENDIAN
macro_line|#else
macro_line|#error &quot;Unsupported endian...&quot;
macro_line|#endif
macro_line|#else /* !__KERNEL__ */
macro_line|#include &lt;endian.h&gt;
macro_line|#if __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|SNDRV_LITTLE_ENDIAN
mdefine_line|#define SNDRV_LITTLE_ENDIAN
macro_line|#elif __BYTE_ORDER == __BIG_ENDIAN
DECL|macro|SNDRV_BIG_ENDIAN
mdefine_line|#define SNDRV_BIG_ENDIAN
macro_line|#else
macro_line|#error &quot;Unsupported endian...&quot;
macro_line|#endif
macro_line|#endif /* __KERNEL **/
macro_line|#endif /* LINUX */
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  protocol version&n; */
DECL|macro|SNDRV_PROTOCOL_VERSION
mdefine_line|#define SNDRV_PROTOCOL_VERSION(major, minor, subminor) (((major)&lt;&lt;16)|((minor)&lt;&lt;8)|(subminor))
DECL|macro|SNDRV_PROTOCOL_MAJOR
mdefine_line|#define SNDRV_PROTOCOL_MAJOR(version) (((version)&gt;&gt;16)&amp;0xffff)
DECL|macro|SNDRV_PROTOCOL_MINOR
mdefine_line|#define SNDRV_PROTOCOL_MINOR(version) (((version)&gt;&gt;8)&amp;0xff)
DECL|macro|SNDRV_PROTOCOL_MICRO
mdefine_line|#define SNDRV_PROTOCOL_MICRO(version) ((version)&amp;0xff)
DECL|macro|SNDRV_PROTOCOL_INCOMPATIBLE
mdefine_line|#define SNDRV_PROTOCOL_INCOMPATIBLE(kversion, uversion) &bslash;&n;&t;(SNDRV_PROTOCOL_MAJOR(kversion) != SNDRV_PROTOCOL_MAJOR(uversion) || &bslash;&n;&t; (SNDRV_PROTOCOL_MAJOR(kversion) == SNDRV_PROTOCOL_MAJOR(uversion) &amp;&amp; &bslash;&n;&t;   SNDRV_PROTOCOL_MINOR(kversion) != SNDRV_PROTOCOL_MINOR(uversion)))
multiline_comment|/****************************************************************************&n; *                                                                          *&n; *        Digital audio interface&t;&t;&t;&t;&t;    *&n; *                                                                          *&n; ****************************************************************************/
DECL|struct|sndrv_aes_iec958
r_struct
id|sndrv_aes_iec958
(brace
DECL|member|status
r_int
r_char
id|status
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* AES/IEC958 channel status bits */
DECL|member|subcode
r_int
r_char
id|subcode
(braket
l_int|147
)braket
suffix:semicolon
multiline_comment|/* AES/IEC958 subcode bits */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* nothing */
DECL|member|dig_subframe
r_int
r_char
id|dig_subframe
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* AES/IEC958 subframe bits */
)brace
suffix:semicolon
multiline_comment|/****************************************************************************&n; *                                                                          *&n; *      Section for driver hardware dependent interface - /dev/snd/hw?      *&n; *                                                                          *&n; ****************************************************************************/
DECL|macro|SNDRV_HWDEP_VERSION
mdefine_line|#define SNDRV_HWDEP_VERSION&t;&t;SNDRV_PROTOCOL_VERSION(1, 0, 0)
DECL|enum|sndrv_hwdep_iface
r_enum
id|sndrv_hwdep_iface
(brace
DECL|enumerator|SNDRV_HWDEP_IFACE_OPL2
id|SNDRV_HWDEP_IFACE_OPL2
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_HWDEP_IFACE_OPL3
id|SNDRV_HWDEP_IFACE_OPL3
comma
DECL|enumerator|SNDRV_HWDEP_IFACE_OPL4
id|SNDRV_HWDEP_IFACE_OPL4
comma
DECL|enumerator|SNDRV_HWDEP_IFACE_SB16CSP
id|SNDRV_HWDEP_IFACE_SB16CSP
comma
multiline_comment|/* Creative Signal Processor */
DECL|enumerator|SNDRV_HWDEP_IFACE_EMU10K1
id|SNDRV_HWDEP_IFACE_EMU10K1
comma
multiline_comment|/* FX8010 processor in EMU10K1 chip */
DECL|enumerator|SNDRV_HWDEP_IFACE_YSS225
id|SNDRV_HWDEP_IFACE_YSS225
comma
multiline_comment|/* Yamaha FX processor */
DECL|enumerator|SNDRV_HWDEP_IFACE_ICS2115
id|SNDRV_HWDEP_IFACE_ICS2115
comma
multiline_comment|/* Wavetable synth */
DECL|enumerator|SNDRV_HWDEP_IFACE_SSCAPE
id|SNDRV_HWDEP_IFACE_SSCAPE
comma
multiline_comment|/* Ensoniq SoundScape ISA card (MC68EC000) */
multiline_comment|/* Don&squot;t forget to change the following: */
DECL|enumerator|SNDRV_HWDEP_IFACE_LAST
id|SNDRV_HWDEP_IFACE_LAST
op_assign
id|SNDRV_HWDEP_IFACE_SSCAPE
comma
)brace
suffix:semicolon
DECL|struct|sndrv_hwdep_info
r_struct
id|sndrv_hwdep_info
(brace
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* WR: device number */
DECL|member|card
r_int
id|card
suffix:semicolon
multiline_comment|/* R: card number */
DECL|member|id
r_int
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* ID (user selectable) */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* hwdep name */
DECL|member|iface
r_enum
id|sndrv_hwdep_iface
id|iface
suffix:semicolon
multiline_comment|/* hwdep interface */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved for future */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_HWDEP_IOCTL_PVERSION
id|SNDRV_HWDEP_IOCTL_PVERSION
op_assign
id|_IOR
(paren
l_char|&squot;H&squot;
comma
l_int|0x00
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_HWDEP_IOCTL_INFO
id|SNDRV_HWDEP_IOCTL_INFO
op_assign
id|_IOR
(paren
l_char|&squot;H&squot;
comma
l_int|0x01
comma
r_struct
id|sndrv_hwdep_info
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *                                                                           *&n; *             Digital Audio (PCM) interface - /dev/snd/pcm??                *&n; *                                                                           *&n; *****************************************************************************/
DECL|macro|SNDRV_PCM_VERSION
mdefine_line|#define SNDRV_PCM_VERSION&t;&t;SNDRV_PROTOCOL_VERSION(2, 0, 3)
DECL|typedef|sndrv_pcm_uframes_t
r_typedef
r_int
r_int
id|sndrv_pcm_uframes_t
suffix:semicolon
DECL|typedef|sndrv_pcm_sframes_t
r_typedef
r_int
id|sndrv_pcm_sframes_t
suffix:semicolon
DECL|enum|sndrv_pcm_class
r_enum
id|sndrv_pcm_class
(brace
DECL|enumerator|SNDRV_PCM_CLASS_GENERIC
id|SNDRV_PCM_CLASS_GENERIC
op_assign
l_int|0
comma
multiline_comment|/* standard mono or stereo device */
DECL|enumerator|SNDRV_PCM_CLASS_MULTI
id|SNDRV_PCM_CLASS_MULTI
comma
multiline_comment|/* multichannel device */
DECL|enumerator|SNDRV_PCM_CLASS_MODEM
id|SNDRV_PCM_CLASS_MODEM
comma
multiline_comment|/* software modem class */
DECL|enumerator|SNDRV_PCM_CLASS_DIGITIZER
id|SNDRV_PCM_CLASS_DIGITIZER
comma
multiline_comment|/* digitizer class */
multiline_comment|/* Don&squot;t forget to change the following: */
DECL|enumerator|SNDRV_PCM_CLASS_LAST
id|SNDRV_PCM_CLASS_LAST
op_assign
id|SNDRV_PCM_CLASS_DIGITIZER
comma
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_subclass
r_enum
id|sndrv_pcm_subclass
(brace
DECL|enumerator|SNDRV_PCM_SUBCLASS_GENERIC_MIX
id|SNDRV_PCM_SUBCLASS_GENERIC_MIX
op_assign
l_int|0
comma
multiline_comment|/* mono or stereo subdevices are mixed together */
DECL|enumerator|SNDRV_PCM_SUBCLASS_MULTI_MIX
id|SNDRV_PCM_SUBCLASS_MULTI_MIX
comma
multiline_comment|/* multichannel subdevices are mixed together */
multiline_comment|/* Don&squot;t forget to change the following: */
DECL|enumerator|SNDRV_PCM_SUBCLASS_LAST
id|SNDRV_PCM_SUBCLASS_LAST
op_assign
id|SNDRV_PCM_SUBCLASS_MULTI_MIX
comma
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_stream
r_enum
id|sndrv_pcm_stream
(brace
DECL|enumerator|SNDRV_PCM_STREAM_PLAYBACK
id|SNDRV_PCM_STREAM_PLAYBACK
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_PCM_STREAM_CAPTURE
id|SNDRV_PCM_STREAM_CAPTURE
comma
DECL|enumerator|SNDRV_PCM_STREAM_LAST
id|SNDRV_PCM_STREAM_LAST
op_assign
id|SNDRV_PCM_STREAM_CAPTURE
comma
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_access
r_enum
id|sndrv_pcm_access
(brace
DECL|enumerator|SNDRV_PCM_ACCESS_MMAP_INTERLEAVED
id|SNDRV_PCM_ACCESS_MMAP_INTERLEAVED
op_assign
l_int|0
comma
multiline_comment|/* interleaved mmap */
DECL|enumerator|SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED
id|SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED
comma
multiline_comment|/* noninterleaved mmap */
DECL|enumerator|SNDRV_PCM_ACCESS_MMAP_COMPLEX
id|SNDRV_PCM_ACCESS_MMAP_COMPLEX
comma
multiline_comment|/* complex mmap */
DECL|enumerator|SNDRV_PCM_ACCESS_RW_INTERLEAVED
id|SNDRV_PCM_ACCESS_RW_INTERLEAVED
comma
multiline_comment|/* readi/writei */
DECL|enumerator|SNDRV_PCM_ACCESS_RW_NONINTERLEAVED
id|SNDRV_PCM_ACCESS_RW_NONINTERLEAVED
comma
multiline_comment|/* readn/writen */
DECL|enumerator|SNDRV_PCM_ACCESS_LAST
id|SNDRV_PCM_ACCESS_LAST
op_assign
id|SNDRV_PCM_ACCESS_RW_NONINTERLEAVED
comma
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_format
r_enum
id|sndrv_pcm_format
(brace
DECL|enumerator|SNDRV_PCM_FORMAT_S8
id|SNDRV_PCM_FORMAT_S8
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U8
id|SNDRV_PCM_FORMAT_U8
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S16_LE
id|SNDRV_PCM_FORMAT_S16_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S16_BE
id|SNDRV_PCM_FORMAT_S16_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U16_LE
id|SNDRV_PCM_FORMAT_U16_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U16_BE
id|SNDRV_PCM_FORMAT_U16_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S24_LE
id|SNDRV_PCM_FORMAT_S24_LE
comma
multiline_comment|/* low three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S24_BE
id|SNDRV_PCM_FORMAT_S24_BE
comma
multiline_comment|/* low three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U24_LE
id|SNDRV_PCM_FORMAT_U24_LE
comma
multiline_comment|/* low three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U24_BE
id|SNDRV_PCM_FORMAT_U24_BE
comma
multiline_comment|/* low three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S32_LE
id|SNDRV_PCM_FORMAT_S32_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S32_BE
id|SNDRV_PCM_FORMAT_S32_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U32_LE
id|SNDRV_PCM_FORMAT_U32_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U32_BE
id|SNDRV_PCM_FORMAT_U32_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT_LE
id|SNDRV_PCM_FORMAT_FLOAT_LE
comma
multiline_comment|/* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT_BE
id|SNDRV_PCM_FORMAT_FLOAT_BE
comma
multiline_comment|/* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT64_LE
id|SNDRV_PCM_FORMAT_FLOAT64_LE
comma
multiline_comment|/* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT64_BE
id|SNDRV_PCM_FORMAT_FLOAT64_BE
comma
multiline_comment|/* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
DECL|enumerator|SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
id|SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
comma
multiline_comment|/* IEC-958 subframe, Little Endian */
DECL|enumerator|SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
id|SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
comma
multiline_comment|/* IEC-958 subframe, Big Endian */
DECL|enumerator|SNDRV_PCM_FORMAT_MU_LAW
id|SNDRV_PCM_FORMAT_MU_LAW
comma
DECL|enumerator|SNDRV_PCM_FORMAT_A_LAW
id|SNDRV_PCM_FORMAT_A_LAW
comma
DECL|enumerator|SNDRV_PCM_FORMAT_IMA_ADPCM
id|SNDRV_PCM_FORMAT_IMA_ADPCM
comma
DECL|enumerator|SNDRV_PCM_FORMAT_MPEG
id|SNDRV_PCM_FORMAT_MPEG
comma
DECL|enumerator|SNDRV_PCM_FORMAT_GSM
id|SNDRV_PCM_FORMAT_GSM
comma
DECL|enumerator|SNDRV_PCM_FORMAT_SPECIAL
id|SNDRV_PCM_FORMAT_SPECIAL
op_assign
l_int|31
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S24_3LE
id|SNDRV_PCM_FORMAT_S24_3LE
op_assign
l_int|32
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S24_3BE
id|SNDRV_PCM_FORMAT_S24_3BE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U24_3LE
id|SNDRV_PCM_FORMAT_U24_3LE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U24_3BE
id|SNDRV_PCM_FORMAT_U24_3BE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S20_3LE
id|SNDRV_PCM_FORMAT_S20_3LE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S20_3BE
id|SNDRV_PCM_FORMAT_S20_3BE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U20_3LE
id|SNDRV_PCM_FORMAT_U20_3LE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U20_3BE
id|SNDRV_PCM_FORMAT_U20_3BE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S18_3LE
id|SNDRV_PCM_FORMAT_S18_3LE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_S18_3BE
id|SNDRV_PCM_FORMAT_S18_3BE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U18_3LE
id|SNDRV_PCM_FORMAT_U18_3LE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_U18_3BE
id|SNDRV_PCM_FORMAT_U18_3BE
comma
multiline_comment|/* in three bytes */
DECL|enumerator|SNDRV_PCM_FORMAT_LAST
id|SNDRV_PCM_FORMAT_LAST
op_assign
id|SNDRV_PCM_FORMAT_U18_3BE
comma
macro_line|#ifdef SNDRV_LITTLE_ENDIAN
DECL|enumerator|SNDRV_PCM_FORMAT_S16
id|SNDRV_PCM_FORMAT_S16
op_assign
id|SNDRV_PCM_FORMAT_S16_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U16
id|SNDRV_PCM_FORMAT_U16
op_assign
id|SNDRV_PCM_FORMAT_U16_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S24
id|SNDRV_PCM_FORMAT_S24
op_assign
id|SNDRV_PCM_FORMAT_S24_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U24
id|SNDRV_PCM_FORMAT_U24
op_assign
id|SNDRV_PCM_FORMAT_U24_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S32
id|SNDRV_PCM_FORMAT_S32
op_assign
id|SNDRV_PCM_FORMAT_S32_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U32
id|SNDRV_PCM_FORMAT_U32
op_assign
id|SNDRV_PCM_FORMAT_U32_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT
id|SNDRV_PCM_FORMAT_FLOAT
op_assign
id|SNDRV_PCM_FORMAT_FLOAT_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT64
id|SNDRV_PCM_FORMAT_FLOAT64
op_assign
id|SNDRV_PCM_FORMAT_FLOAT64_LE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_IEC958_SUBFRAME
id|SNDRV_PCM_FORMAT_IEC958_SUBFRAME
op_assign
id|SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
comma
macro_line|#endif
macro_line|#ifdef SNDRV_BIG_ENDIAN
DECL|enumerator|SNDRV_PCM_FORMAT_S16
id|SNDRV_PCM_FORMAT_S16
op_assign
id|SNDRV_PCM_FORMAT_S16_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U16
id|SNDRV_PCM_FORMAT_U16
op_assign
id|SNDRV_PCM_FORMAT_U16_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S24
id|SNDRV_PCM_FORMAT_S24
op_assign
id|SNDRV_PCM_FORMAT_S24_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U24
id|SNDRV_PCM_FORMAT_U24
op_assign
id|SNDRV_PCM_FORMAT_U24_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_S32
id|SNDRV_PCM_FORMAT_S32
op_assign
id|SNDRV_PCM_FORMAT_S32_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_U32
id|SNDRV_PCM_FORMAT_U32
op_assign
id|SNDRV_PCM_FORMAT_U32_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT
id|SNDRV_PCM_FORMAT_FLOAT
op_assign
id|SNDRV_PCM_FORMAT_FLOAT_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_FLOAT64
id|SNDRV_PCM_FORMAT_FLOAT64
op_assign
id|SNDRV_PCM_FORMAT_FLOAT64_BE
comma
DECL|enumerator|SNDRV_PCM_FORMAT_IEC958_SUBFRAME
id|SNDRV_PCM_FORMAT_IEC958_SUBFRAME
op_assign
id|SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_subformat
r_enum
id|sndrv_pcm_subformat
(brace
DECL|enumerator|SNDRV_PCM_SUBFORMAT_STD
id|SNDRV_PCM_SUBFORMAT_STD
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_PCM_SUBFORMAT_LAST
id|SNDRV_PCM_SUBFORMAT_LAST
op_assign
id|SNDRV_PCM_SUBFORMAT_STD
comma
)brace
suffix:semicolon
DECL|macro|SNDRV_PCM_INFO_MMAP
mdefine_line|#define SNDRV_PCM_INFO_MMAP&t;&t;0x00000001&t;/* hardware supports mmap */
DECL|macro|SNDRV_PCM_INFO_MMAP_VALID
mdefine_line|#define SNDRV_PCM_INFO_MMAP_VALID&t;0x00000002&t;/* period data are valid during transfer */
DECL|macro|SNDRV_PCM_INFO_DOUBLE
mdefine_line|#define SNDRV_PCM_INFO_DOUBLE&t;&t;0x00000004&t;/* Double buffering needed for PCM start/stop */
DECL|macro|SNDRV_PCM_INFO_BATCH
mdefine_line|#define SNDRV_PCM_INFO_BATCH&t;&t;0x00000010&t;/* double buffering */
DECL|macro|SNDRV_PCM_INFO_INTERLEAVED
mdefine_line|#define SNDRV_PCM_INFO_INTERLEAVED&t;0x00000100&t;/* channels are interleaved */
DECL|macro|SNDRV_PCM_INFO_NONINTERLEAVED
mdefine_line|#define SNDRV_PCM_INFO_NONINTERLEAVED&t;0x00000200&t;/* channels are not interleaved */
DECL|macro|SNDRV_PCM_INFO_COMPLEX
mdefine_line|#define SNDRV_PCM_INFO_COMPLEX&t;&t;0x00000400&t;/* complex frame organization (mmap only) */
DECL|macro|SNDRV_PCM_INFO_BLOCK_TRANSFER
mdefine_line|#define SNDRV_PCM_INFO_BLOCK_TRANSFER&t;0x00010000&t;/* hardware transfer block of samples */
DECL|macro|SNDRV_PCM_INFO_OVERRANGE
mdefine_line|#define SNDRV_PCM_INFO_OVERRANGE&t;0x00020000&t;/* hardware supports ADC (capture) overrange detection */
DECL|macro|SNDRV_PCM_INFO_RESUME
mdefine_line|#define SNDRV_PCM_INFO_RESUME&t;&t;0x00040000&t;/* hardware supports stream resume after suspend */
DECL|macro|SNDRV_PCM_INFO_PAUSE
mdefine_line|#define SNDRV_PCM_INFO_PAUSE&t;&t;0x00080000&t;/* pause ioctl is supported */
DECL|macro|SNDRV_PCM_INFO_HALF_DUPLEX
mdefine_line|#define SNDRV_PCM_INFO_HALF_DUPLEX&t;0x00100000&t;/* only half duplex */
DECL|macro|SNDRV_PCM_INFO_JOINT_DUPLEX
mdefine_line|#define SNDRV_PCM_INFO_JOINT_DUPLEX&t;0x00200000&t;/* playback and capture stream are somewhat correlated */
DECL|macro|SNDRV_PCM_INFO_SYNC_START
mdefine_line|#define SNDRV_PCM_INFO_SYNC_START&t;0x00400000&t;/* pcm support some kind of sync go */
DECL|enum|sndrv_pcm_state
r_enum
id|sndrv_pcm_state
(brace
DECL|enumerator|SNDRV_PCM_STATE_OPEN
id|SNDRV_PCM_STATE_OPEN
op_assign
l_int|0
comma
multiline_comment|/* stream is open */
DECL|enumerator|SNDRV_PCM_STATE_SETUP
id|SNDRV_PCM_STATE_SETUP
comma
multiline_comment|/* stream has a setup */
DECL|enumerator|SNDRV_PCM_STATE_PREPARED
id|SNDRV_PCM_STATE_PREPARED
comma
multiline_comment|/* stream is ready to start */
DECL|enumerator|SNDRV_PCM_STATE_RUNNING
id|SNDRV_PCM_STATE_RUNNING
comma
multiline_comment|/* stream is running */
DECL|enumerator|SNDRV_PCM_STATE_XRUN
id|SNDRV_PCM_STATE_XRUN
comma
multiline_comment|/* stream reached an xrun */
DECL|enumerator|SNDRV_PCM_STATE_DRAINING
id|SNDRV_PCM_STATE_DRAINING
comma
multiline_comment|/* stream is draining */
DECL|enumerator|SNDRV_PCM_STATE_PAUSED
id|SNDRV_PCM_STATE_PAUSED
comma
multiline_comment|/* stream is paused */
DECL|enumerator|SNDRV_PCM_STATE_SUSPENDED
id|SNDRV_PCM_STATE_SUSPENDED
comma
multiline_comment|/* hardware is suspended */
DECL|enumerator|SNDRV_PCM_STATE_LAST
id|SNDRV_PCM_STATE_LAST
op_assign
id|SNDRV_PCM_STATE_SUSPENDED
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_PCM_MMAP_OFFSET_DATA
id|SNDRV_PCM_MMAP_OFFSET_DATA
op_assign
l_int|0x00000000
comma
DECL|enumerator|SNDRV_PCM_MMAP_OFFSET_STATUS
id|SNDRV_PCM_MMAP_OFFSET_STATUS
op_assign
l_int|0x80000000
comma
DECL|enumerator|SNDRV_PCM_MMAP_OFFSET_CONTROL
id|SNDRV_PCM_MMAP_OFFSET_CONTROL
op_assign
l_int|0x81000000
comma
)brace
suffix:semicolon
DECL|union|sndrv_pcm_sync_id
r_union
id|sndrv_pcm_sync_id
(brace
DECL|member|id
r_int
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|id16
r_int
r_int
id|id16
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|id32
r_int
r_int
id|id32
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_info
r_struct
id|sndrv_pcm_info
(brace
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* RO/WR (control): device number */
DECL|member|subdevice
r_int
r_int
id|subdevice
suffix:semicolon
multiline_comment|/* RO/WR (control): subdevice number */
DECL|member|stream
r_enum
id|sndrv_pcm_stream
id|stream
suffix:semicolon
multiline_comment|/* RO/WR (control): stream number */
DECL|member|card
r_int
id|card
suffix:semicolon
multiline_comment|/* R: card number */
DECL|member|id
r_int
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* ID (user selectable) */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* name of this device */
DECL|member|subname
r_int
r_char
id|subname
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* subdevice name */
DECL|member|dev_class
r_enum
id|sndrv_pcm_class
id|dev_class
suffix:semicolon
multiline_comment|/* SNDRV_PCM_CLASS_* */
DECL|member|dev_subclass
r_enum
id|sndrv_pcm_subclass
id|dev_subclass
suffix:semicolon
multiline_comment|/* SNDRV_PCM_SUBCLASS_* */
DECL|member|subdevices_count
r_int
r_int
id|subdevices_count
suffix:semicolon
DECL|member|subdevices_avail
r_int
r_int
id|subdevices_avail
suffix:semicolon
DECL|member|sync
r_union
id|sndrv_pcm_sync_id
id|sync
suffix:semicolon
multiline_comment|/* hardware synchronization ID */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved for future... */
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_hw_param
r_enum
id|sndrv_pcm_hw_param
(brace
DECL|enumerator|SNDRV_PCM_HW_PARAM_ACCESS
id|SNDRV_PCM_HW_PARAM_ACCESS
op_assign
l_int|0
comma
multiline_comment|/* Access type */
DECL|enumerator|SNDRV_PCM_HW_PARAM_FIRST_MASK
id|SNDRV_PCM_HW_PARAM_FIRST_MASK
op_assign
id|SNDRV_PCM_HW_PARAM_ACCESS
comma
DECL|enumerator|SNDRV_PCM_HW_PARAM_FORMAT
id|SNDRV_PCM_HW_PARAM_FORMAT
comma
multiline_comment|/* Format */
DECL|enumerator|SNDRV_PCM_HW_PARAM_SUBFORMAT
id|SNDRV_PCM_HW_PARAM_SUBFORMAT
comma
multiline_comment|/* Subformat */
DECL|enumerator|SNDRV_PCM_HW_PARAM_LAST_MASK
id|SNDRV_PCM_HW_PARAM_LAST_MASK
op_assign
id|SNDRV_PCM_HW_PARAM_SUBFORMAT
comma
DECL|enumerator|SNDRV_PCM_HW_PARAM_SAMPLE_BITS
id|SNDRV_PCM_HW_PARAM_SAMPLE_BITS
op_assign
l_int|8
comma
multiline_comment|/* Bits per sample */
DECL|enumerator|SNDRV_PCM_HW_PARAM_FIRST_INTERVAL
id|SNDRV_PCM_HW_PARAM_FIRST_INTERVAL
op_assign
id|SNDRV_PCM_HW_PARAM_SAMPLE_BITS
comma
DECL|enumerator|SNDRV_PCM_HW_PARAM_FRAME_BITS
id|SNDRV_PCM_HW_PARAM_FRAME_BITS
comma
multiline_comment|/* Bits per frame */
DECL|enumerator|SNDRV_PCM_HW_PARAM_CHANNELS
id|SNDRV_PCM_HW_PARAM_CHANNELS
comma
multiline_comment|/* Channels */
DECL|enumerator|SNDRV_PCM_HW_PARAM_RATE
id|SNDRV_PCM_HW_PARAM_RATE
comma
multiline_comment|/* Approx rate */
DECL|enumerator|SNDRV_PCM_HW_PARAM_PERIOD_TIME
id|SNDRV_PCM_HW_PARAM_PERIOD_TIME
comma
multiline_comment|/* Approx distance between interrupts&n;&t;&t;&t;&t;&t;   in us */
DECL|enumerator|SNDRV_PCM_HW_PARAM_PERIOD_SIZE
id|SNDRV_PCM_HW_PARAM_PERIOD_SIZE
comma
multiline_comment|/* Approx frames between interrupts */
DECL|enumerator|SNDRV_PCM_HW_PARAM_PERIOD_BYTES
id|SNDRV_PCM_HW_PARAM_PERIOD_BYTES
comma
multiline_comment|/* Approx bytes between interrupts */
DECL|enumerator|SNDRV_PCM_HW_PARAM_PERIODS
id|SNDRV_PCM_HW_PARAM_PERIODS
comma
multiline_comment|/* Approx interrupts per buffer */
DECL|enumerator|SNDRV_PCM_HW_PARAM_BUFFER_TIME
id|SNDRV_PCM_HW_PARAM_BUFFER_TIME
comma
multiline_comment|/* Approx duration of buffer in us */
DECL|enumerator|SNDRV_PCM_HW_PARAM_BUFFER_SIZE
id|SNDRV_PCM_HW_PARAM_BUFFER_SIZE
comma
multiline_comment|/* Size of buffer in frames */
DECL|enumerator|SNDRV_PCM_HW_PARAM_BUFFER_BYTES
id|SNDRV_PCM_HW_PARAM_BUFFER_BYTES
comma
multiline_comment|/* Size of buffer in bytes */
DECL|enumerator|SNDRV_PCM_HW_PARAM_TICK_TIME
id|SNDRV_PCM_HW_PARAM_TICK_TIME
comma
multiline_comment|/* Approx tick duration in us */
DECL|enumerator|SNDRV_PCM_HW_PARAM_LAST_INTERVAL
id|SNDRV_PCM_HW_PARAM_LAST_INTERVAL
op_assign
id|SNDRV_PCM_HW_PARAM_TICK_TIME
)brace
suffix:semicolon
DECL|macro|SNDRV_PCM_HW_PARAMS_RUNTIME
mdefine_line|#define SNDRV_PCM_HW_PARAMS_RUNTIME&t;&t;(1&lt;&lt;0)
DECL|struct|sndrv_interval
r_struct
id|sndrv_interval
(brace
DECL|member|min
DECL|member|max
r_int
r_int
id|min
comma
id|max
suffix:semicolon
DECL|member|openmin
r_int
r_int
id|openmin
suffix:colon
l_int|1
comma
DECL|member|openmax
id|openmax
suffix:colon
l_int|1
comma
DECL|member|integer
id|integer
suffix:colon
l_int|1
comma
DECL|member|empty
id|empty
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNDRV_MASK_MAX
mdefine_line|#define SNDRV_MASK_MAX&t;256
DECL|struct|sndrv_mask
r_struct
id|sndrv_mask
(brace
DECL|member|bits
id|u_int32_t
id|bits
(braket
(paren
id|SNDRV_MASK_MAX
op_plus
l_int|31
)paren
op_div
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_hw_params
r_struct
id|sndrv_pcm_hw_params
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|masks
r_struct
id|sndrv_mask
id|masks
(braket
id|SNDRV_PCM_HW_PARAM_LAST_MASK
op_minus
id|SNDRV_PCM_HW_PARAM_FIRST_MASK
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|mres
r_struct
id|sndrv_mask
id|mres
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved masks */
DECL|member|intervals
r_struct
id|sndrv_interval
id|intervals
(braket
id|SNDRV_PCM_HW_PARAM_LAST_INTERVAL
op_minus
id|SNDRV_PCM_HW_PARAM_FIRST_INTERVAL
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|ires
r_struct
id|sndrv_interval
id|ires
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* reserved intervals */
DECL|member|rmask
r_int
r_int
id|rmask
suffix:semicolon
multiline_comment|/* W: requested masks */
DECL|member|cmask
r_int
r_int
id|cmask
suffix:semicolon
multiline_comment|/* R: changed masks */
DECL|member|info
r_int
r_int
id|info
suffix:semicolon
multiline_comment|/* R: Info flags for returned setup */
DECL|member|msbits
r_int
r_int
id|msbits
suffix:semicolon
multiline_comment|/* R: used most significant bits */
DECL|member|rate_num
r_int
r_int
id|rate_num
suffix:semicolon
multiline_comment|/* R: rate numerator */
DECL|member|rate_den
r_int
r_int
id|rate_den
suffix:semicolon
multiline_comment|/* R: rate denominator */
DECL|member|fifo_size
id|sndrv_pcm_uframes_t
id|fifo_size
suffix:semicolon
multiline_comment|/* R: chip FIFO size in frames */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved for future */
)brace
suffix:semicolon
DECL|enum|sndrv_pcm_tstamp
r_enum
id|sndrv_pcm_tstamp
(brace
DECL|enumerator|SNDRV_PCM_TSTAMP_NONE
id|SNDRV_PCM_TSTAMP_NONE
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_PCM_TSTAMP_MMAP
id|SNDRV_PCM_TSTAMP_MMAP
comma
DECL|enumerator|SNDRV_PCM_TSTAMP_LAST
id|SNDRV_PCM_TSTAMP_LAST
op_assign
id|SNDRV_PCM_TSTAMP_MMAP
comma
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_sw_params
r_struct
id|sndrv_pcm_sw_params
(brace
DECL|member|tstamp_mode
r_enum
id|sndrv_pcm_tstamp
id|tstamp_mode
suffix:semicolon
multiline_comment|/* timestamp mode */
DECL|member|period_step
r_int
r_int
id|period_step
suffix:semicolon
DECL|member|sleep_min
r_int
r_int
id|sleep_min
suffix:semicolon
multiline_comment|/* min ticks to sleep */
DECL|member|avail_min
id|sndrv_pcm_uframes_t
id|avail_min
suffix:semicolon
multiline_comment|/* min avail frames for wakeup */
DECL|member|xfer_align
id|sndrv_pcm_uframes_t
id|xfer_align
suffix:semicolon
multiline_comment|/* xfer size need to be a multiple */
DECL|member|start_threshold
id|sndrv_pcm_uframes_t
id|start_threshold
suffix:semicolon
multiline_comment|/* min hw_avail frames for automatic start */
DECL|member|stop_threshold
id|sndrv_pcm_uframes_t
id|stop_threshold
suffix:semicolon
multiline_comment|/* min avail frames for automatic stop */
DECL|member|silence_threshold
id|sndrv_pcm_uframes_t
id|silence_threshold
suffix:semicolon
multiline_comment|/* min distance from noise for silence filling */
DECL|member|silence_size
id|sndrv_pcm_uframes_t
id|silence_size
suffix:semicolon
multiline_comment|/* silence block size */
DECL|member|boundary
id|sndrv_pcm_uframes_t
id|boundary
suffix:semicolon
multiline_comment|/* pointers wrap point */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved for future */
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_channel_info
r_struct
id|sndrv_pcm_channel_info
(brace
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|offset
id|off_t
id|offset
suffix:semicolon
multiline_comment|/* mmap offset */
DECL|member|first
r_int
r_int
id|first
suffix:semicolon
multiline_comment|/* offset to first sample in bits */
DECL|member|step
r_int
r_int
id|step
suffix:semicolon
multiline_comment|/* samples distance in bits */
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_status
r_struct
id|sndrv_pcm_status
(brace
DECL|member|state
r_enum
id|sndrv_pcm_state
id|state
suffix:semicolon
multiline_comment|/* stream state */
DECL|member|trigger_tstamp
r_struct
id|timeval
id|trigger_tstamp
suffix:semicolon
multiline_comment|/* time when stream was started/stopped/paused */
DECL|member|tstamp
r_struct
id|timeval
id|tstamp
suffix:semicolon
multiline_comment|/* reference timestamp */
DECL|member|appl_ptr
id|sndrv_pcm_uframes_t
id|appl_ptr
suffix:semicolon
multiline_comment|/* appl ptr */
DECL|member|hw_ptr
id|sndrv_pcm_uframes_t
id|hw_ptr
suffix:semicolon
multiline_comment|/* hw ptr */
DECL|member|delay
id|sndrv_pcm_sframes_t
id|delay
suffix:semicolon
multiline_comment|/* current delay in frames */
DECL|member|avail
id|sndrv_pcm_uframes_t
id|avail
suffix:semicolon
multiline_comment|/* number of frames available */
DECL|member|avail_max
id|sndrv_pcm_uframes_t
id|avail_max
suffix:semicolon
multiline_comment|/* max frames available on hw since last status */
DECL|member|overrange
id|sndrv_pcm_uframes_t
id|overrange
suffix:semicolon
multiline_comment|/* count of ADC (capture) overrange detections from last status */
DECL|member|suspended_state
r_enum
id|sndrv_pcm_state
id|suspended_state
suffix:semicolon
multiline_comment|/* suspended stream state */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* must be filled with zero */
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_mmap_status
r_struct
id|sndrv_pcm_mmap_status
(brace
DECL|member|state
r_enum
id|sndrv_pcm_state
id|state
suffix:semicolon
multiline_comment|/* RO: state - SNDRV_PCM_STATE_XXXX */
DECL|member|pad1
r_int
id|pad1
suffix:semicolon
multiline_comment|/* Needed for 64 bit alignment */
DECL|member|hw_ptr
id|sndrv_pcm_uframes_t
id|hw_ptr
suffix:semicolon
multiline_comment|/* RO: hw ptr (0...boundary-1) */
DECL|member|tstamp
r_struct
id|timeval
id|tstamp
suffix:semicolon
multiline_comment|/* Timestamp */
DECL|member|suspended_state
r_enum
id|sndrv_pcm_state
id|suspended_state
suffix:semicolon
multiline_comment|/* RO: suspended stream state */
)brace
suffix:semicolon
DECL|struct|sndrv_pcm_mmap_control
r_struct
id|sndrv_pcm_mmap_control
(brace
DECL|member|appl_ptr
id|sndrv_pcm_uframes_t
id|appl_ptr
suffix:semicolon
multiline_comment|/* RW: appl ptr (0...boundary-1) */
DECL|member|avail_min
id|sndrv_pcm_uframes_t
id|avail_min
suffix:semicolon
multiline_comment|/* RW: min available frames for wakeup */
)brace
suffix:semicolon
DECL|struct|sndrv_xferi
r_struct
id|sndrv_xferi
(brace
DECL|member|result
id|sndrv_pcm_sframes_t
id|result
suffix:semicolon
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
DECL|member|frames
id|sndrv_pcm_uframes_t
id|frames
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_xfern
r_struct
id|sndrv_xfern
(brace
DECL|member|result
id|sndrv_pcm_sframes_t
id|result
suffix:semicolon
DECL|member|bufs
r_void
op_star
op_star
id|bufs
suffix:semicolon
DECL|member|frames
id|sndrv_pcm_uframes_t
id|frames
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_PCM_IOCTL_PVERSION
id|SNDRV_PCM_IOCTL_PVERSION
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x00
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_INFO
id|SNDRV_PCM_IOCTL_INFO
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x01
comma
r_struct
id|sndrv_pcm_info
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HW_REFINE
id|SNDRV_PCM_IOCTL_HW_REFINE
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_pcm_hw_params
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HW_PARAMS
id|SNDRV_PCM_IOCTL_HW_PARAMS
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x11
comma
r_struct
id|sndrv_pcm_hw_params
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HW_FREE
id|SNDRV_PCM_IOCTL_HW_FREE
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x12
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_SW_PARAMS
id|SNDRV_PCM_IOCTL_SW_PARAMS
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x13
comma
r_struct
id|sndrv_pcm_sw_params
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_STATUS
id|SNDRV_PCM_IOCTL_STATUS
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x20
comma
r_struct
id|sndrv_pcm_status
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_DELAY
id|SNDRV_PCM_IOCTL_DELAY
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x21
comma
id|sndrv_pcm_sframes_t
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_HWSYNC
id|SNDRV_PCM_IOCTL_HWSYNC
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x22
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_CHANNEL_INFO
id|SNDRV_PCM_IOCTL_CHANNEL_INFO
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x32
comma
r_struct
id|sndrv_pcm_channel_info
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_PREPARE
id|SNDRV_PCM_IOCTL_PREPARE
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x40
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_RESET
id|SNDRV_PCM_IOCTL_RESET
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x41
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_START
id|SNDRV_PCM_IOCTL_START
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x42
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_DROP
id|SNDRV_PCM_IOCTL_DROP
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x43
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_DRAIN
id|SNDRV_PCM_IOCTL_DRAIN
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x44
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_PAUSE
id|SNDRV_PCM_IOCTL_PAUSE
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x45
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_REWIND
id|SNDRV_PCM_IOCTL_REWIND
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x46
comma
id|sndrv_pcm_uframes_t
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_RESUME
id|SNDRV_PCM_IOCTL_RESUME
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x47
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_XRUN
id|SNDRV_PCM_IOCTL_XRUN
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x48
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_WRITEI_FRAMES
id|SNDRV_PCM_IOCTL_WRITEI_FRAMES
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x50
comma
r_struct
id|sndrv_xferi
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_READI_FRAMES
id|SNDRV_PCM_IOCTL_READI_FRAMES
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x51
comma
r_struct
id|sndrv_xferi
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_WRITEN_FRAMES
id|SNDRV_PCM_IOCTL_WRITEN_FRAMES
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x52
comma
r_struct
id|sndrv_xfern
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_READN_FRAMES
id|SNDRV_PCM_IOCTL_READN_FRAMES
op_assign
id|_IOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x53
comma
r_struct
id|sndrv_xfern
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_LINK
id|SNDRV_PCM_IOCTL_LINK
op_assign
id|_IOW
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x60
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_PCM_IOCTL_UNLINK
id|SNDRV_PCM_IOCTL_UNLINK
op_assign
id|_IO
c_func
(paren
l_char|&squot;A&squot;
comma
l_int|0x61
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* Trick to make alsa-lib/acinclude.m4 happy */
DECL|macro|SNDRV_PCM_IOCTL_REWIND
mdefine_line|#define SNDRV_PCM_IOCTL_REWIND SNDRV_PCM_IOCTL_REWIND
multiline_comment|/*****************************************************************************&n; *                                                                           *&n; *                            MIDI v1.0 interface                            *&n; *                                                                           *&n; *****************************************************************************/
multiline_comment|/*&n; *  Raw MIDI section - /dev/snd/midi??&n; */
DECL|macro|SNDRV_RAWMIDI_VERSION
mdefine_line|#define SNDRV_RAWMIDI_VERSION&t;&t;SNDRV_PROTOCOL_VERSION(2, 0, 0)
DECL|enum|sndrv_rawmidi_stream
r_enum
id|sndrv_rawmidi_stream
(brace
DECL|enumerator|SNDRV_RAWMIDI_STREAM_OUTPUT
id|SNDRV_RAWMIDI_STREAM_OUTPUT
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_RAWMIDI_STREAM_INPUT
id|SNDRV_RAWMIDI_STREAM_INPUT
comma
DECL|enumerator|SNDRV_RAWMIDI_STREAM_LAST
id|SNDRV_RAWMIDI_STREAM_LAST
op_assign
id|SNDRV_RAWMIDI_STREAM_INPUT
comma
)brace
suffix:semicolon
DECL|macro|SNDRV_RAWMIDI_INFO_OUTPUT
mdefine_line|#define SNDRV_RAWMIDI_INFO_OUTPUT&t;&t;0x00000001
DECL|macro|SNDRV_RAWMIDI_INFO_INPUT
mdefine_line|#define SNDRV_RAWMIDI_INFO_INPUT&t;&t;0x00000002
DECL|macro|SNDRV_RAWMIDI_INFO_DUPLEX
mdefine_line|#define SNDRV_RAWMIDI_INFO_DUPLEX&t;&t;0x00000004
DECL|struct|sndrv_rawmidi_info
r_struct
id|sndrv_rawmidi_info
(brace
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* RO/WR (control): device number */
DECL|member|subdevice
r_int
r_int
id|subdevice
suffix:semicolon
multiline_comment|/* RO/WR (control): subdevice number */
DECL|member|stream
r_enum
id|sndrv_rawmidi_stream
id|stream
suffix:semicolon
multiline_comment|/* WR: stream */
DECL|member|card
r_int
id|card
suffix:semicolon
multiline_comment|/* R: card number */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* SNDRV_RAWMIDI_INFO_XXXX */
DECL|member|id
r_int
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* ID (user selectable) */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* name of device */
DECL|member|subname
r_int
r_char
id|subname
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* name of active or selected subdevice */
DECL|member|subdevices_count
r_int
r_int
id|subdevices_count
suffix:semicolon
DECL|member|subdevices_avail
r_int
r_int
id|subdevices_avail
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
)brace
suffix:semicolon
DECL|struct|sndrv_rawmidi_params
r_struct
id|sndrv_rawmidi_params
(brace
DECL|member|stream
r_enum
id|sndrv_rawmidi_stream
id|stream
suffix:semicolon
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* queue size in bytes */
DECL|member|avail_min
r_int
id|avail_min
suffix:semicolon
multiline_comment|/* minimum avail bytes for wakeup */
DECL|member|no_active_sensing
r_int
r_int
id|no_active_sensing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* do not send active sensing byte in close() */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
)brace
suffix:semicolon
DECL|struct|sndrv_rawmidi_status
r_struct
id|sndrv_rawmidi_status
(brace
DECL|member|stream
r_enum
id|sndrv_rawmidi_stream
id|stream
suffix:semicolon
DECL|member|tstamp
r_struct
id|timeval
id|tstamp
suffix:semicolon
multiline_comment|/* Timestamp */
DECL|member|avail
r_int
id|avail
suffix:semicolon
multiline_comment|/* available bytes */
DECL|member|xruns
r_int
id|xruns
suffix:semicolon
multiline_comment|/* count of overruns since last status (in bytes) */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved for future use */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_RAWMIDI_IOCTL_PVERSION
id|SNDRV_RAWMIDI_IOCTL_PVERSION
op_assign
id|_IOR
c_func
(paren
l_char|&squot;W&squot;
comma
l_int|0x00
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_RAWMIDI_IOCTL_INFO
id|SNDRV_RAWMIDI_IOCTL_INFO
op_assign
id|_IOR
c_func
(paren
l_char|&squot;W&squot;
comma
l_int|0x01
comma
r_struct
id|sndrv_rawmidi_info
)paren
comma
DECL|enumerator|SNDRV_RAWMIDI_IOCTL_PARAMS
id|SNDRV_RAWMIDI_IOCTL_PARAMS
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;W&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_rawmidi_params
)paren
comma
DECL|enumerator|SNDRV_RAWMIDI_IOCTL_STATUS
id|SNDRV_RAWMIDI_IOCTL_STATUS
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;W&squot;
comma
l_int|0x20
comma
r_struct
id|sndrv_rawmidi_status
)paren
comma
DECL|enumerator|SNDRV_RAWMIDI_IOCTL_DROP
id|SNDRV_RAWMIDI_IOCTL_DROP
op_assign
id|_IOW
c_func
(paren
l_char|&squot;W&squot;
comma
l_int|0x30
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_RAWMIDI_IOCTL_DRAIN
id|SNDRV_RAWMIDI_IOCTL_DRAIN
op_assign
id|_IOW
c_func
(paren
l_char|&squot;W&squot;
comma
l_int|0x31
comma
r_int
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  Timer section - /dev/snd/timer&n; */
DECL|macro|SNDRV_TIMER_VERSION
mdefine_line|#define SNDRV_TIMER_VERSION&t;&t;SNDRV_PROTOCOL_VERSION(2, 0, 0)
DECL|enum|sndrv_timer_class
r_enum
id|sndrv_timer_class
(brace
DECL|enumerator|SNDRV_TIMER_CLASS_NONE
id|SNDRV_TIMER_CLASS_NONE
op_assign
op_minus
l_int|1
comma
DECL|enumerator|SNDRV_TIMER_CLASS_SLAVE
id|SNDRV_TIMER_CLASS_SLAVE
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_TIMER_CLASS_GLOBAL
id|SNDRV_TIMER_CLASS_GLOBAL
comma
DECL|enumerator|SNDRV_TIMER_CLASS_CARD
id|SNDRV_TIMER_CLASS_CARD
comma
DECL|enumerator|SNDRV_TIMER_CLASS_PCM
id|SNDRV_TIMER_CLASS_PCM
comma
DECL|enumerator|SNDRV_TIMER_CLASS_LAST
id|SNDRV_TIMER_CLASS_LAST
op_assign
id|SNDRV_TIMER_CLASS_PCM
comma
)brace
suffix:semicolon
multiline_comment|/* slave timer classes */
DECL|enum|sndrv_timer_slave_class
r_enum
id|sndrv_timer_slave_class
(brace
DECL|enumerator|SNDRV_TIMER_SCLASS_NONE
id|SNDRV_TIMER_SCLASS_NONE
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_TIMER_SCLASS_APPLICATION
id|SNDRV_TIMER_SCLASS_APPLICATION
comma
DECL|enumerator|SNDRV_TIMER_SCLASS_SEQUENCER
id|SNDRV_TIMER_SCLASS_SEQUENCER
comma
multiline_comment|/* alias */
DECL|enumerator|SNDRV_TIMER_SCLASS_OSS_SEQUENCER
id|SNDRV_TIMER_SCLASS_OSS_SEQUENCER
comma
multiline_comment|/* alias */
DECL|enumerator|SNDRV_TIMER_SCLASS_LAST
id|SNDRV_TIMER_SCLASS_LAST
op_assign
id|SNDRV_TIMER_SCLASS_OSS_SEQUENCER
comma
)brace
suffix:semicolon
multiline_comment|/* global timers (device member) */
DECL|macro|SNDRV_TIMER_GLOBAL_SYSTEM
mdefine_line|#define SNDRV_TIMER_GLOBAL_SYSTEM&t;0
DECL|macro|SNDRV_TIMER_GLOBAL_RTC
mdefine_line|#define SNDRV_TIMER_GLOBAL_RTC&t;&t;1
DECL|struct|sndrv_timer_id
r_struct
id|sndrv_timer_id
(brace
DECL|member|dev_class
r_enum
id|sndrv_timer_class
id|dev_class
suffix:semicolon
DECL|member|dev_sclass
r_enum
id|sndrv_timer_slave_class
id|dev_sclass
suffix:semicolon
DECL|member|card
r_int
id|card
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
DECL|member|subdevice
r_int
id|subdevice
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_timer_select
r_struct
id|sndrv_timer_select
(brace
DECL|member|id
r_struct
id|sndrv_timer_id
id|id
suffix:semicolon
multiline_comment|/* bind to timer ID */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
DECL|macro|SNDRV_TIMER_FLG_SLAVE
mdefine_line|#define SNDRV_TIMER_FLG_SLAVE&t;&t;(1&lt;&lt;0)&t;/* cannot be controlled */
DECL|struct|sndrv_timer_info
r_struct
id|sndrv_timer_info
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* timer flags - SNDRV_TIMER_FLG_* */
DECL|member|card
r_int
id|card
suffix:semicolon
multiline_comment|/* R: card number */
DECL|member|id
r_int
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* timer identificator */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* timer name */
DECL|member|ticks
r_int
r_int
id|ticks
suffix:semicolon
multiline_comment|/* maximum ticks */
DECL|member|resolution
r_int
r_int
id|resolution
suffix:semicolon
multiline_comment|/* average resolution */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
DECL|macro|SNDRV_TIMER_PSFLG_AUTO
mdefine_line|#define SNDRV_TIMER_PSFLG_AUTO&t;&t;(1&lt;&lt;0)&t;/* supports auto start */
DECL|struct|sndrv_timer_params
r_struct
id|sndrv_timer_params
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags - SNDRV_MIXER_PSFLG_* */
DECL|member|ticks
r_int
r_int
id|ticks
suffix:semicolon
multiline_comment|/* requested resolution in ticks */
DECL|member|queue_size
r_int
r_int
id|queue_size
suffix:semicolon
multiline_comment|/* total size of queue (32-1024) */
DECL|member|reserved0
r_int
r_int
id|reserved0
suffix:semicolon
multiline_comment|/* reserved, was: failure locations */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
DECL|struct|sndrv_timer_status
r_struct
id|sndrv_timer_status
(brace
DECL|member|tstamp
r_struct
id|timeval
id|tstamp
suffix:semicolon
multiline_comment|/* Timestamp */
DECL|member|resolution
r_int
r_int
id|resolution
suffix:semicolon
multiline_comment|/* current resolution */
DECL|member|lost
r_int
r_int
id|lost
suffix:semicolon
multiline_comment|/* counter of master tick lost */
DECL|member|overrun
r_int
r_int
id|overrun
suffix:semicolon
multiline_comment|/* count of read queue overruns */
DECL|member|queue
r_int
r_int
id|queue
suffix:semicolon
multiline_comment|/* used queue size */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_TIMER_IOCTL_PVERSION
id|SNDRV_TIMER_IOCTL_PVERSION
op_assign
id|_IOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x00
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_NEXT_DEVICE
id|SNDRV_TIMER_IOCTL_NEXT_DEVICE
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x01
comma
r_struct
id|sndrv_timer_id
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_SELECT
id|SNDRV_TIMER_IOCTL_SELECT
op_assign
id|_IOW
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_timer_select
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_INFO
id|SNDRV_TIMER_IOCTL_INFO
op_assign
id|_IOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x11
comma
r_struct
id|sndrv_timer_info
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_PARAMS
id|SNDRV_TIMER_IOCTL_PARAMS
op_assign
id|_IOW
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x12
comma
r_struct
id|sndrv_timer_params
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_STATUS
id|SNDRV_TIMER_IOCTL_STATUS
op_assign
id|_IOW
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x14
comma
r_struct
id|sndrv_timer_status
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_START
id|SNDRV_TIMER_IOCTL_START
op_assign
id|_IO
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x20
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_STOP
id|SNDRV_TIMER_IOCTL_STOP
op_assign
id|_IO
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x21
)paren
comma
DECL|enumerator|SNDRV_TIMER_IOCTL_CONTINUE
id|SNDRV_TIMER_IOCTL_CONTINUE
op_assign
id|_IO
c_func
(paren
l_char|&squot;T&squot;
comma
l_int|0x22
)paren
comma
)brace
suffix:semicolon
DECL|struct|sndrv_timer_read
r_struct
id|sndrv_timer_read
(brace
DECL|member|resolution
r_int
r_int
id|resolution
suffix:semicolon
DECL|member|ticks
r_int
r_int
id|ticks
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/****************************************************************************&n; *                                                                          *&n; *        Section for driver control interface - /dev/snd/control?          *&n; *                                                                          *&n; ****************************************************************************/
DECL|macro|SNDRV_CTL_VERSION
mdefine_line|#define SNDRV_CTL_VERSION&t;&t;SNDRV_PROTOCOL_VERSION(2, 0, 0)
DECL|struct|sndrv_ctl_card_info
r_struct
id|sndrv_ctl_card_info
(brace
DECL|member|card
r_int
id|card
suffix:semicolon
multiline_comment|/* card number */
DECL|member|pad
r_int
id|pad
suffix:semicolon
multiline_comment|/* reserved for future (was type) */
DECL|member|id
r_int
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* ID of card (user selectable) */
DECL|member|driver
r_int
r_char
id|driver
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Driver name */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Short name of soundcard */
DECL|member|longname
r_int
r_char
id|longname
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* name + info text about soundcard */
DECL|member|reserved_
r_int
r_char
id|reserved_
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved for future (was ID of mixer) */
DECL|member|mixername
r_int
r_char
id|mixername
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* visual mixer identification */
DECL|member|components
r_int
r_char
id|components
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* card components / fine identification, delimited with one space (AC97 etc..) */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|48
)braket
suffix:semicolon
multiline_comment|/* reserved for future */
)brace
suffix:semicolon
DECL|enum|sndrv_ctl_elem_type
r_enum
id|sndrv_ctl_elem_type
(brace
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_NONE
id|SNDRV_CTL_ELEM_TYPE_NONE
op_assign
l_int|0
comma
multiline_comment|/* invalid */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_BOOLEAN
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
comma
multiline_comment|/* boolean type */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_INTEGER
id|SNDRV_CTL_ELEM_TYPE_INTEGER
comma
multiline_comment|/* integer type */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_ENUMERATED
id|SNDRV_CTL_ELEM_TYPE_ENUMERATED
comma
multiline_comment|/* enumerated type */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_BYTES
id|SNDRV_CTL_ELEM_TYPE_BYTES
comma
multiline_comment|/* byte array */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_IEC958
id|SNDRV_CTL_ELEM_TYPE_IEC958
comma
multiline_comment|/* IEC958 (S/PDIF) setup */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_INTEGER64
id|SNDRV_CTL_ELEM_TYPE_INTEGER64
comma
multiline_comment|/* 64-bit integer type */
DECL|enumerator|SNDRV_CTL_ELEM_TYPE_LAST
id|SNDRV_CTL_ELEM_TYPE_LAST
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER64
comma
)brace
suffix:semicolon
DECL|enum|sndrv_ctl_elem_iface
r_enum
id|sndrv_ctl_elem_iface
(brace
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_CARD
id|SNDRV_CTL_ELEM_IFACE_CARD
op_assign
l_int|0
comma
multiline_comment|/* global control */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_HWDEP
id|SNDRV_CTL_ELEM_IFACE_HWDEP
comma
multiline_comment|/* hardware dependent device */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_MIXER
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
multiline_comment|/* virtual mixer device */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_PCM
id|SNDRV_CTL_ELEM_IFACE_PCM
comma
multiline_comment|/* PCM device */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_RAWMIDI
id|SNDRV_CTL_ELEM_IFACE_RAWMIDI
comma
multiline_comment|/* RawMidi device */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_TIMER
id|SNDRV_CTL_ELEM_IFACE_TIMER
comma
multiline_comment|/* timer device */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_SEQUENCER
id|SNDRV_CTL_ELEM_IFACE_SEQUENCER
comma
multiline_comment|/* sequencer client */
DECL|enumerator|SNDRV_CTL_ELEM_IFACE_LAST
id|SNDRV_CTL_ELEM_IFACE_LAST
op_assign
id|SNDRV_CTL_ELEM_IFACE_SEQUENCER
comma
)brace
suffix:semicolon
DECL|macro|SNDRV_CTL_ELEM_ACCESS_READ
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_READ&t;&t;(1&lt;&lt;0)
DECL|macro|SNDRV_CTL_ELEM_ACCESS_WRITE
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_WRITE&t;&t;(1&lt;&lt;1)
DECL|macro|SNDRV_CTL_ELEM_ACCESS_READWRITE
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_READWRITE&t;&t;(SNDRV_CTL_ELEM_ACCESS_READ|SNDRV_CTL_ELEM_ACCESS_WRITE)
DECL|macro|SNDRV_CTL_ELEM_ACCESS_VOLATILE
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_VOLATILE&t;&t;(1&lt;&lt;2)&t;/* control value may be changed without a notification */
DECL|macro|SNDRV_CTL_ELEM_ACCESS_INACTIVE
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_INACTIVE&t;&t;(1&lt;&lt;8)&t;/* control does actually nothing, but may be updated */
DECL|macro|SNDRV_CTL_ELEM_ACCESS_LOCK
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_LOCK&t;&t;(1&lt;&lt;9)&t;/* write lock */
DECL|macro|SNDRV_CTL_ELEM_ACCESS_OWNER
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_OWNER&t;&t;(1&lt;&lt;10)&t;/* write lock owner */
DECL|macro|SNDRV_CTL_ELEM_ACCESS_INDIRECT
mdefine_line|#define SNDRV_CTL_ELEM_ACCESS_INDIRECT&t;&t;(1&lt;&lt;31)&t;/* indirect access */
multiline_comment|/* for further details see the ACPI and PCI power management specification */
DECL|macro|SNDRV_CTL_POWER_D0
mdefine_line|#define SNDRV_CTL_POWER_D0&t;&t;0x0000&t;/* full On */
DECL|macro|SNDRV_CTL_POWER_D1
mdefine_line|#define SNDRV_CTL_POWER_D1&t;&t;0x0100&t;/* partial On */
DECL|macro|SNDRV_CTL_POWER_D2
mdefine_line|#define SNDRV_CTL_POWER_D2&t;&t;0x0200&t;/* partial On */
DECL|macro|SNDRV_CTL_POWER_D3
mdefine_line|#define SNDRV_CTL_POWER_D3&t;&t;0x0300&t;/* Off */
DECL|macro|SNDRV_CTL_POWER_D3hot
mdefine_line|#define SNDRV_CTL_POWER_D3hot&t;&t;(SNDRV_CTL_POWER_D3|0x0000)&t;/* Off, with power */
DECL|macro|SNDRV_CTL_POWER_D3cold
mdefine_line|#define SNDRV_CTL_POWER_D3cold&t;&t;(SNDRV_CTL_POWER_D3|0x0001)&t;/* Off, without power */
DECL|struct|sndrv_ctl_elem_id
r_struct
id|sndrv_ctl_elem_id
(brace
DECL|member|numid
r_int
r_int
id|numid
suffix:semicolon
multiline_comment|/* numeric identifier, zero = invalid */
DECL|member|iface
r_enum
id|sndrv_ctl_elem_iface
id|iface
suffix:semicolon
multiline_comment|/* interface identifier */
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* device/client number */
DECL|member|subdevice
r_int
r_int
id|subdevice
suffix:semicolon
multiline_comment|/* subdevice (substream) number */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|44
)braket
suffix:semicolon
multiline_comment|/* ASCII name of item */
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
multiline_comment|/* index of item */
)brace
suffix:semicolon
DECL|struct|sndrv_ctl_elem_list
r_struct
id|sndrv_ctl_elem_list
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* W: first element ID to get */
DECL|member|space
r_int
r_int
id|space
suffix:semicolon
multiline_comment|/* W: count of element IDs to get */
DECL|member|used
r_int
r_int
id|used
suffix:semicolon
multiline_comment|/* R: count of element IDs set */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* R: count of all elements */
DECL|member|pids
r_struct
id|sndrv_ctl_elem_id
op_star
id|pids
suffix:semicolon
multiline_comment|/* R: IDs */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|50
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_ctl_elem_info
r_struct
id|sndrv_ctl_elem_info
(brace
DECL|member|id
r_struct
id|sndrv_ctl_elem_id
id|id
suffix:semicolon
multiline_comment|/* W: element ID */
DECL|member|type
r_enum
id|sndrv_ctl_elem_type
id|type
suffix:semicolon
multiline_comment|/* R: value type - SNDRV_CTL_ELEM_TYPE_* */
DECL|member|access
r_int
r_int
id|access
suffix:semicolon
multiline_comment|/* R: value access (bitmask) - SNDRV_CTL_ELEM_ACCESS_* */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* count of values */
DECL|member|owner
id|pid_t
id|owner
suffix:semicolon
multiline_comment|/* owner&squot;s PID of this control */
r_union
(brace
r_struct
(brace
DECL|member|min
r_int
id|min
suffix:semicolon
multiline_comment|/* R: minimum value */
DECL|member|max
r_int
id|max
suffix:semicolon
multiline_comment|/* R: maximum value */
DECL|member|step
r_int
id|step
suffix:semicolon
multiline_comment|/* R: step (0 variable) */
DECL|member|integer
)brace
id|integer
suffix:semicolon
r_struct
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* R: minimum value */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* R: maximum value */
DECL|member|step
r_int
r_int
id|step
suffix:semicolon
multiline_comment|/* R: step (0 variable) */
DECL|member|integer64
)brace
id|integer64
suffix:semicolon
r_struct
(brace
DECL|member|items
r_int
r_int
id|items
suffix:semicolon
multiline_comment|/* R: number of items */
DECL|member|item
r_int
r_int
id|item
suffix:semicolon
multiline_comment|/* W: item number */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* R: value name */
DECL|member|enumerated
)brace
id|enumerated
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|value
)brace
id|value
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_ctl_elem_value
r_struct
id|sndrv_ctl_elem_value
(brace
DECL|member|id
r_struct
id|sndrv_ctl_elem_id
id|id
suffix:semicolon
multiline_comment|/* W: element ID */
DECL|member|indirect
r_int
r_int
id|indirect
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* W: use indirect pointer (xxx_ptr member) */
r_union
(brace
r_union
(brace
DECL|member|value
r_int
id|value
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|value_ptr
r_int
op_star
id|value_ptr
suffix:semicolon
DECL|member|integer
)brace
id|integer
suffix:semicolon
r_union
(brace
DECL|member|value
r_int
r_int
id|value
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|value_ptr
r_int
r_int
op_star
id|value_ptr
suffix:semicolon
DECL|member|integer64
)brace
id|integer64
suffix:semicolon
r_union
(brace
DECL|member|item
r_int
r_int
id|item
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|item_ptr
r_int
r_int
op_star
id|item_ptr
suffix:semicolon
DECL|member|enumerated
)brace
id|enumerated
suffix:semicolon
r_union
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|512
)braket
suffix:semicolon
DECL|member|data_ptr
r_int
r_char
op_star
id|data_ptr
suffix:semicolon
DECL|member|bytes
)brace
id|bytes
suffix:semicolon
DECL|member|iec958
r_struct
id|sndrv_aes_iec958
id|iec958
suffix:semicolon
DECL|member|value
)brace
id|value
suffix:semicolon
multiline_comment|/* RO */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_CTL_IOCTL_PVERSION
id|SNDRV_CTL_IOCTL_PVERSION
op_assign
id|_IOR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x00
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_CARD_INFO
id|SNDRV_CTL_IOCTL_CARD_INFO
op_assign
id|_IOR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x01
comma
r_struct
id|sndrv_ctl_card_info
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_LIST
id|SNDRV_CTL_IOCTL_ELEM_LIST
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_ctl_elem_list
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_INFO
id|SNDRV_CTL_IOCTL_ELEM_INFO
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x11
comma
r_struct
id|sndrv_ctl_elem_info
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_READ
id|SNDRV_CTL_IOCTL_ELEM_READ
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x12
comma
r_struct
id|sndrv_ctl_elem_value
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_WRITE
id|SNDRV_CTL_IOCTL_ELEM_WRITE
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x13
comma
r_struct
id|sndrv_ctl_elem_value
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_LOCK
id|SNDRV_CTL_IOCTL_ELEM_LOCK
op_assign
id|_IOW
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x14
comma
r_struct
id|sndrv_ctl_elem_id
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_UNLOCK
id|SNDRV_CTL_IOCTL_ELEM_UNLOCK
op_assign
id|_IOW
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x15
comma
r_struct
id|sndrv_ctl_elem_id
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS
id|SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x16
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE
id|SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x20
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_HWDEP_INFO
id|SNDRV_CTL_IOCTL_HWDEP_INFO
op_assign
id|_IOR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x21
comma
r_struct
id|sndrv_hwdep_info
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE
id|SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE
op_assign
id|_IOR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x30
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_PCM_INFO
id|SNDRV_CTL_IOCTL_PCM_INFO
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x31
comma
r_struct
id|sndrv_pcm_info
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE
id|SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE
op_assign
id|_IOW
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x32
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_RAWMIDI_NEXT_DEVICE
id|SNDRV_CTL_IOCTL_RAWMIDI_NEXT_DEVICE
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x40
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_RAWMIDI_INFO
id|SNDRV_CTL_IOCTL_RAWMIDI_INFO
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x41
comma
r_struct
id|sndrv_rawmidi_info
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_RAWMIDI_PREFER_SUBDEVICE
id|SNDRV_CTL_IOCTL_RAWMIDI_PREFER_SUBDEVICE
op_assign
id|_IOW
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x42
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_POWER
id|SNDRV_CTL_IOCTL_POWER
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0xd0
comma
r_int
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_POWER_STATE
id|SNDRV_CTL_IOCTL_POWER_STATE
op_assign
id|_IOR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0xd1
comma
r_int
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *  Read interface.&n; */
DECL|enum|sndrv_ctl_event_type
r_enum
id|sndrv_ctl_event_type
(brace
DECL|enumerator|SNDRV_CTL_EVENT_ELEM
id|SNDRV_CTL_EVENT_ELEM
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_CTL_EVENT_LAST
id|SNDRV_CTL_EVENT_LAST
op_assign
id|SNDRV_CTL_EVENT_ELEM
comma
)brace
suffix:semicolon
DECL|macro|SNDRV_CTL_EVENT_MASK_VALUE
mdefine_line|#define SNDRV_CTL_EVENT_MASK_VALUE&t;(1&lt;&lt;0)&t;/* element value was changed */
DECL|macro|SNDRV_CTL_EVENT_MASK_INFO
mdefine_line|#define SNDRV_CTL_EVENT_MASK_INFO&t;(1&lt;&lt;1)&t;/* element info was changed */
DECL|macro|SNDRV_CTL_EVENT_MASK_ADD
mdefine_line|#define SNDRV_CTL_EVENT_MASK_ADD&t;(1&lt;&lt;2)&t;/* element was added */
DECL|macro|SNDRV_CTL_EVENT_MASK_REMOVE
mdefine_line|#define SNDRV_CTL_EVENT_MASK_REMOVE&t;(~0U)&t;/* element was removed */
DECL|struct|sndrv_ctl_event
r_struct
id|sndrv_ctl_event
(brace
DECL|member|type
r_enum
id|sndrv_ctl_event_type
id|type
suffix:semicolon
multiline_comment|/* event type - SNDRV_CTL_EVENT_* */
r_union
(brace
r_struct
(brace
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|id
r_struct
id|sndrv_ctl_elem_id
id|id
suffix:semicolon
DECL|member|elem
)brace
id|elem
suffix:semicolon
DECL|member|data8
r_int
r_char
id|data8
(braket
l_int|60
)braket
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Control names&n; */
DECL|macro|SNDRV_CTL_NAME_NONE
mdefine_line|#define SNDRV_CTL_NAME_NONE&t;&t;&t;&t;&quot;&quot;
DECL|macro|SNDRV_CTL_NAME_PLAYBACK
mdefine_line|#define SNDRV_CTL_NAME_PLAYBACK&t;&t;&t;&t;&quot;Playback &quot;
DECL|macro|SNDRV_CTL_NAME_CAPTURE
mdefine_line|#define SNDRV_CTL_NAME_CAPTURE&t;&t;&t;&t;&quot;Capture &quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_NONE
mdefine_line|#define SNDRV_CTL_NAME_IEC958_NONE&t;&t;&t;&quot;&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_SWITCH
mdefine_line|#define SNDRV_CTL_NAME_IEC958_SWITCH&t;&t;&t;&quot;Switch&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_VOLUME
mdefine_line|#define SNDRV_CTL_NAME_IEC958_VOLUME&t;&t;&t;&quot;Volume&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_DEFAULT
mdefine_line|#define SNDRV_CTL_NAME_IEC958_DEFAULT&t;&t;&t;&quot;Default&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_MASK
mdefine_line|#define SNDRV_CTL_NAME_IEC958_MASK&t;&t;&t;&quot;Mask&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_CON_MASK
mdefine_line|#define SNDRV_CTL_NAME_IEC958_CON_MASK&t;&t;&t;&quot;Con Mask&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_PRO_MASK
mdefine_line|#define SNDRV_CTL_NAME_IEC958_PRO_MASK&t;&t;&t;&quot;Pro Mask&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958_PCM_STREAM
mdefine_line|#define SNDRV_CTL_NAME_IEC958_PCM_STREAM&t;&t;&quot;PCM Stream&quot;
DECL|macro|SNDRV_CTL_NAME_IEC958
mdefine_line|#define SNDRV_CTL_NAME_IEC958(expl,direction,what)&t;&quot;IEC958 &quot; expl SNDRV_CTL_NAME_##direction SNDRV_CTL_NAME_IEC958_##what
multiline_comment|/*&n; *&n; */
DECL|struct|sndrv_xferv
r_struct
id|sndrv_xferv
(brace
DECL|member|vector
r_const
r_struct
id|iovec
op_star
id|vector
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|SNDRV_IOCTL_READV
id|SNDRV_IOCTL_READV
op_assign
id|_IOW
c_func
(paren
l_char|&squot;K&squot;
comma
l_int|0x00
comma
r_struct
id|sndrv_xferv
)paren
comma
DECL|enumerator|SNDRV_IOCTL_WRITEV
id|SNDRV_IOCTL_WRITEV
op_assign
id|_IOW
c_func
(paren
l_char|&squot;K&squot;
comma
l_int|0x01
comma
r_struct
id|sndrv_xferv
)paren
comma
)brace
suffix:semicolon
macro_line|#endif /* __SOUND_ASOUND_H */
eof
