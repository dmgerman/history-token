macro_line|#ifndef __SOUND_ASOUNDEF_H
DECL|macro|__SOUND_ASOUNDEF_H
mdefine_line|#define __SOUND_ASOUNDEF_H
multiline_comment|/*&n; *  Advanced Linux Sound Architecture - ALSA - Driver&n; *  Copyright (c) 1994-2000 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/****************************************************************************&n; *                                                                          *&n; *        Digital audio interface&t;&t;&t;&t;&t;    *&n; *                                                                          *&n; ****************************************************************************/
multiline_comment|/* AES/IEC958 channel status bits */
DECL|macro|IEC958_AES0_PROFESSIONAL
mdefine_line|#define IEC958_AES0_PROFESSIONAL&t;(1&lt;&lt;0)&t;/* 0 = consumer, 1 = professional */
DECL|macro|IEC958_AES0_NONAUDIO
mdefine_line|#define IEC958_AES0_NONAUDIO&t;&t;(1&lt;&lt;1)&t;/* 0 = audio, 1 = non-audio */
DECL|macro|IEC958_AES0_PRO_EMPHASIS
mdefine_line|#define IEC958_AES0_PRO_EMPHASIS&t;(7&lt;&lt;2)&t;/* mask - emphasis */
DECL|macro|IEC958_AES0_PRO_EMPHASIS_NOTID
mdefine_line|#define IEC958_AES0_PRO_EMPHASIS_NOTID&t;(0&lt;&lt;2)&t;/* emphasis not indicated */
DECL|macro|IEC958_AES0_PRO_EMPHASIS_NONE
mdefine_line|#define IEC958_AES0_PRO_EMPHASIS_NONE&t;(1&lt;&lt;2)&t;/* none emphasis */
DECL|macro|IEC958_AES0_PRO_EMPHASIS_5015
mdefine_line|#define IEC958_AES0_PRO_EMPHASIS_5015&t;(3&lt;&lt;2)&t;/* 50/15us emphasis */
DECL|macro|IEC958_AES0_PRO_EMPHASIS_CCITT
mdefine_line|#define IEC958_AES0_PRO_EMPHASIS_CCITT&t;(7&lt;&lt;2)&t;/* CCITT J.17 emphasis */
DECL|macro|IEC958_AES0_PRO_FREQ_UNLOCKED
mdefine_line|#define IEC958_AES0_PRO_FREQ_UNLOCKED&t;(1&lt;&lt;5)&t;/* source sample frequency: 0 = locked, 1 = unlocked */
DECL|macro|IEC958_AES0_PRO_FS
mdefine_line|#define IEC958_AES0_PRO_FS&t;&t;(3&lt;&lt;6)&t;/* mask - sample frequency */
DECL|macro|IEC958_AES0_PRO_FS_NOTID
mdefine_line|#define IEC958_AES0_PRO_FS_NOTID&t;(0&lt;&lt;6)&t;/* fs not indicated */
DECL|macro|IEC958_AES0_PRO_FS_44100
mdefine_line|#define IEC958_AES0_PRO_FS_44100&t;(1&lt;&lt;6)&t;/* 44.1kHz */
DECL|macro|IEC958_AES0_PRO_FS_48000
mdefine_line|#define IEC958_AES0_PRO_FS_48000&t;(2&lt;&lt;6)&t;/* 48kHz */
DECL|macro|IEC958_AES0_PRO_FS_32000
mdefine_line|#define IEC958_AES0_PRO_FS_32000&t;(3&lt;&lt;6)&t;/* 32kHz */
DECL|macro|IEC958_AES0_CON_NOT_COPYRIGHT
mdefine_line|#define IEC958_AES0_CON_NOT_COPYRIGHT&t;(1&lt;&lt;2)&t;/* 0 = copyright, 1 = not copyright */
DECL|macro|IEC958_AES0_CON_EMPHASIS
mdefine_line|#define IEC958_AES0_CON_EMPHASIS&t;(7&lt;&lt;3)&t;/* mask - emphasis */
DECL|macro|IEC958_AES0_CON_EMPHASIS_NONE
mdefine_line|#define IEC958_AES0_CON_EMPHASIS_NONE&t;(0&lt;&lt;3)&t;/* none emphasis */
DECL|macro|IEC958_AES0_CON_EMPHASIS_5015
mdefine_line|#define IEC958_AES0_CON_EMPHASIS_5015&t;(1&lt;&lt;3)&t;/* 50/15us emphasis */
DECL|macro|IEC958_AES0_CON_MODE
mdefine_line|#define IEC958_AES0_CON_MODE&t;&t;(3&lt;&lt;6)&t;/* mask - mode */
DECL|macro|IEC958_AES1_PRO_MODE
mdefine_line|#define IEC958_AES1_PRO_MODE&t;&t;(15&lt;&lt;0)&t;/* mask - channel mode */
DECL|macro|IEC958_AES1_PRO_MODE_NOTID
mdefine_line|#define IEC958_AES1_PRO_MODE_NOTID&t;(0&lt;&lt;0)&t;/* not indicated */
DECL|macro|IEC958_AES1_PRO_MODE_STEREOPHONIC
mdefine_line|#define IEC958_AES1_PRO_MODE_STEREOPHONIC (2&lt;&lt;0) /* stereophonic - ch A is left */
DECL|macro|IEC958_AES1_PRO_MODE_SINGLE
mdefine_line|#define IEC958_AES1_PRO_MODE_SINGLE&t;(4&lt;&lt;0)&t;/* single channel */
DECL|macro|IEC958_AES1_PRO_MODE_TWO
mdefine_line|#define IEC958_AES1_PRO_MODE_TWO&t;(8&lt;&lt;0)&t;/* two channels */
DECL|macro|IEC958_AES1_PRO_MODE_PRIMARY
mdefine_line|#define IEC958_AES1_PRO_MODE_PRIMARY&t;(12&lt;&lt;0)&t;/* primary/secondary */
DECL|macro|IEC958_AES1_PRO_MODE_BYTE3
mdefine_line|#define IEC958_AES1_PRO_MODE_BYTE3&t;(15&lt;&lt;0)&t;/* vector to byte 3 */
DECL|macro|IEC958_AES1_PRO_USERBITS
mdefine_line|#define IEC958_AES1_PRO_USERBITS&t;(15&lt;&lt;4)&t;/* mask - user bits */
DECL|macro|IEC958_AES1_PRO_USERBITS_NOTID
mdefine_line|#define IEC958_AES1_PRO_USERBITS_NOTID&t;(0&lt;&lt;4)&t;/* not indicated */
DECL|macro|IEC958_AES1_PRO_USERBITS_192
mdefine_line|#define IEC958_AES1_PRO_USERBITS_192&t;(8&lt;&lt;4)&t;/* 192-bit structure */
DECL|macro|IEC958_AES1_PRO_USERBITS_UDEF
mdefine_line|#define IEC958_AES1_PRO_USERBITS_UDEF&t;(12&lt;&lt;4)&t;/* user defined application */
DECL|macro|IEC958_AES1_CON_CATEGORY
mdefine_line|#define IEC958_AES1_CON_CATEGORY&t;0x7f
DECL|macro|IEC958_AES1_CON_GENERAL
mdefine_line|#define IEC958_AES1_CON_GENERAL&t;&t;0x00
DECL|macro|IEC958_AES1_CON_EXPERIMENTAL
mdefine_line|#define IEC958_AES1_CON_EXPERIMENTAL&t;0x40
DECL|macro|IEC958_AES1_CON_SOLIDMEM_MASK
mdefine_line|#define IEC958_AES1_CON_SOLIDMEM_MASK&t;0x0f
DECL|macro|IEC958_AES1_CON_SOLIDMEM_ID
mdefine_line|#define IEC958_AES1_CON_SOLIDMEM_ID&t;0x08
DECL|macro|IEC958_AES1_CON_BROADCAST1_MASK
mdefine_line|#define IEC958_AES1_CON_BROADCAST1_MASK 0x07
DECL|macro|IEC958_AES1_CON_BROADCAST1_ID
mdefine_line|#define IEC958_AES1_CON_BROADCAST1_ID&t;0x04
DECL|macro|IEC958_AES1_CON_DIGDIGCONV_MASK
mdefine_line|#define IEC958_AES1_CON_DIGDIGCONV_MASK 0x07
DECL|macro|IEC958_AES1_CON_DIGDIGCONV_ID
mdefine_line|#define IEC958_AES1_CON_DIGDIGCONV_ID&t;0x02
DECL|macro|IEC958_AES1_CON_ADC_COPYRIGHT_MASK
mdefine_line|#define IEC958_AES1_CON_ADC_COPYRIGHT_MASK 0x1f
DECL|macro|IEC958_AES1_CON_ADC_COPYRIGHT_ID
mdefine_line|#define IEC958_AES1_CON_ADC_COPYRIGHT_ID 0x06
DECL|macro|IEC958_AES1_CON_ADC_MASK
mdefine_line|#define IEC958_AES1_CON_ADC_MASK&t;0x1f
DECL|macro|IEC958_AES1_CON_ADC_ID
mdefine_line|#define IEC958_AES1_CON_ADC_ID&t;&t;0x16
DECL|macro|IEC958_AES1_CON_BROADCAST2_MASK
mdefine_line|#define IEC958_AES1_CON_BROADCAST2_MASK 0x0f
DECL|macro|IEC958_AES1_CON_BROADCAST2_ID
mdefine_line|#define IEC958_AES1_CON_BROADCAST2_ID&t;0x0e
DECL|macro|IEC958_AES1_CON_LASEROPT_MASK
mdefine_line|#define IEC958_AES1_CON_LASEROPT_MASK&t;0x07
DECL|macro|IEC958_AES1_CON_LASEROPT_ID
mdefine_line|#define IEC958_AES1_CON_LASEROPT_ID&t;0x01
DECL|macro|IEC958_AES1_CON_MUSICAL_MASK
mdefine_line|#define IEC958_AES1_CON_MUSICAL_MASK&t;0x07
DECL|macro|IEC958_AES1_CON_MUSICAL_ID
mdefine_line|#define IEC958_AES1_CON_MUSICAL_ID&t;0x05
DECL|macro|IEC958_AES1_CON_MAGNETIC_MASK
mdefine_line|#define IEC958_AES1_CON_MAGNETIC_MASK&t;0x07
DECL|macro|IEC958_AES1_CON_MAGNETIC_ID
mdefine_line|#define IEC958_AES1_CON_MAGNETIC_ID&t;0x03
DECL|macro|IEC958_AES1_CON_IEC908_CD
mdefine_line|#define IEC958_AES1_CON_IEC908_CD&t;(IEC958_AES1_CON_LASEROPT_ID|0x00)
DECL|macro|IEC958_AES1_CON_NON_IEC908_CD
mdefine_line|#define IEC958_AES1_CON_NON_IEC908_CD&t;(IEC958_AES1_CON_LASEROPT_ID|0x08)
DECL|macro|IEC958_AES1_CON_PCM_CODER
mdefine_line|#define IEC958_AES1_CON_PCM_CODER&t;(IEC958_AES1_CON_DIGDIGCONV_ID|0x00)
DECL|macro|IEC958_AES1_CON_SAMPLER
mdefine_line|#define IEC958_AES1_CON_SAMPLER&t;&t;(IEC958_AES1_CON_DIGDIGCONV_ID|0x20)
DECL|macro|IEC958_AES1_CON_MIXER
mdefine_line|#define IEC958_AES1_CON_MIXER&t;&t;(IEC958_AES1_CON_DIGDIGCONV_ID|0x10)
DECL|macro|IEC958_AES1_CON_RATE_CONVERTER
mdefine_line|#define IEC958_AES1_CON_RATE_CONVERTER&t;(IEC958_AES1_CON_DIGDIGCONV_ID|0x18)
DECL|macro|IEC958_AES1_CON_SYNTHESIZER
mdefine_line|#define IEC958_AES1_CON_SYNTHESIZER&t;(IEC958_AES1_CON_MUSICAL_ID|0x00)
DECL|macro|IEC958_AES1_CON_MICROPHONE
mdefine_line|#define IEC958_AES1_CON_MICROPHONE&t;(IEC958_AES1_CON_MUSICAL_ID|0x08)
DECL|macro|IEC958_AES1_CON_DAT
mdefine_line|#define IEC958_AES1_CON_DAT&t;&t;(IEC958_AES1_CON_MAGNETIC_ID|0x00)
DECL|macro|IEC958_AES1_CON_VCR
mdefine_line|#define IEC958_AES1_CON_VCR&t;&t;(IEC958_AES1_CON_MAGNETIC_ID|0x08)
DECL|macro|IEC958_AES1_CON_ORIGINAL
mdefine_line|#define IEC958_AES1_CON_ORIGINAL&t;(1&lt;&lt;7)&t;/* this bits depends on the category code */
DECL|macro|IEC958_AES2_PRO_SBITS
mdefine_line|#define IEC958_AES2_PRO_SBITS&t;&t;(7&lt;&lt;0)&t;/* mask - sample bits */
DECL|macro|IEC958_AES2_PRO_SBITS_20
mdefine_line|#define IEC958_AES2_PRO_SBITS_20&t;(2&lt;&lt;0)&t;/* 20-bit - coordination */
DECL|macro|IEC958_AES2_PRO_SBITS_24
mdefine_line|#define IEC958_AES2_PRO_SBITS_24&t;(4&lt;&lt;0)&t;/* 24-bit - main audio */
DECL|macro|IEC958_AES2_PRO_SBITS_UDEF
mdefine_line|#define IEC958_AES2_PRO_SBITS_UDEF&t;(6&lt;&lt;0)&t;/* user defined application */
DECL|macro|IEC958_AES2_PRO_WORDLEN
mdefine_line|#define IEC958_AES2_PRO_WORDLEN&t;&t;(7&lt;&lt;3)&t;/* mask - source word length */
DECL|macro|IEC958_AES2_PRO_WORDLEN_NOTID
mdefine_line|#define IEC958_AES2_PRO_WORDLEN_NOTID&t;(0&lt;&lt;3)&t;/* not indicated */
DECL|macro|IEC958_AES2_PRO_WORDLEN_22_18
mdefine_line|#define IEC958_AES2_PRO_WORDLEN_22_18&t;(2&lt;&lt;3)&t;/* 22-bit or 18-bit */
DECL|macro|IEC958_AES2_PRO_WORDLEN_23_19
mdefine_line|#define IEC958_AES2_PRO_WORDLEN_23_19&t;(4&lt;&lt;3)&t;/* 23-bit or 19-bit */
DECL|macro|IEC958_AES2_PRO_WORDLEN_24_20
mdefine_line|#define IEC958_AES2_PRO_WORDLEN_24_20&t;(5&lt;&lt;3)&t;/* 24-bit or 20-bit */
DECL|macro|IEC958_AES2_PRO_WORDLEN_20_16
mdefine_line|#define IEC958_AES2_PRO_WORDLEN_20_16&t;(6&lt;&lt;3)&t;/* 20-bit or 16-bit */
DECL|macro|IEC958_AES2_CON_SOURCE
mdefine_line|#define IEC958_AES2_CON_SOURCE&t;&t;(15&lt;&lt;0)&t;/* mask - source number */
DECL|macro|IEC958_AES2_CON_SOURCE_UNSPEC
mdefine_line|#define IEC958_AES2_CON_SOURCE_UNSPEC&t;(0&lt;&lt;0)&t;/* unspecified */
DECL|macro|IEC958_AES2_CON_CHANNEL
mdefine_line|#define IEC958_AES2_CON_CHANNEL&t;&t;(15&lt;&lt;4)&t;/* mask - channel number */
DECL|macro|IEC958_AES2_CON_CHANNEL_UNSPEC
mdefine_line|#define IEC958_AES2_CON_CHANNEL_UNSPEC&t;(0&lt;&lt;4)&t;/* unspecified */
DECL|macro|IEC958_AES3_CON_FS
mdefine_line|#define IEC958_AES3_CON_FS&t;&t;(15&lt;&lt;0)&t;/* mask - sample frequency */
DECL|macro|IEC958_AES3_CON_FS_44100
mdefine_line|#define IEC958_AES3_CON_FS_44100&t;(0&lt;&lt;0)&t;/* 44.1kHz */
DECL|macro|IEC958_AES3_CON_FS_48000
mdefine_line|#define IEC958_AES3_CON_FS_48000&t;(2&lt;&lt;0)&t;/* 48kHz */
DECL|macro|IEC958_AES3_CON_FS_32000
mdefine_line|#define IEC958_AES3_CON_FS_32000&t;(3&lt;&lt;0)&t;/* 32kHz */
DECL|macro|IEC958_AES3_CON_CLOCK
mdefine_line|#define IEC958_AES3_CON_CLOCK&t;&t;(3&lt;&lt;4)&t;/* mask - clock accuracy */
DECL|macro|IEC958_AES3_CON_CLOCK_1000PPM
mdefine_line|#define IEC958_AES3_CON_CLOCK_1000PPM&t;(0&lt;&lt;4)&t;/* 1000 ppm */
DECL|macro|IEC958_AES3_CON_CLOCK_50PPM
mdefine_line|#define IEC958_AES3_CON_CLOCK_50PPM&t;(1&lt;&lt;4)&t;/* 50 ppm */
DECL|macro|IEC958_AES3_CON_CLOCK_VARIABLE
mdefine_line|#define IEC958_AES3_CON_CLOCK_VARIABLE&t;(2&lt;&lt;4)&t;/* variable pitch */
multiline_comment|/*****************************************************************************&n; *                                                                           *&n; *                            MIDI v1.0 interface                            *&n; *                                                                           *&n; *****************************************************************************/
DECL|macro|MIDI_CHANNELS
mdefine_line|#define MIDI_CHANNELS&t;&t;&t;16
DECL|macro|MIDI_GM_DRUM_CHANNEL
mdefine_line|#define MIDI_GM_DRUM_CHANNEL&t;&t;(10-1)
multiline_comment|/*&n; *  MIDI commands&n; */
DECL|macro|MIDI_CMD_NOTE_OFF
mdefine_line|#define MIDI_CMD_NOTE_OFF&t;&t;0x80
DECL|macro|MIDI_CMD_NOTE_ON
mdefine_line|#define MIDI_CMD_NOTE_ON&t;&t;0x90
DECL|macro|MIDI_CMD_NOTE_PRESSURE
mdefine_line|#define MIDI_CMD_NOTE_PRESSURE&t;&t;0xa0
DECL|macro|MIDI_CMD_CONTROL
mdefine_line|#define MIDI_CMD_CONTROL&t;&t;0xb0
DECL|macro|MIDI_CMD_PGM_CHANGE
mdefine_line|#define MIDI_CMD_PGM_CHANGE&t;&t;0xc0
DECL|macro|MIDI_CMD_CHANNEL_PRESSURE
mdefine_line|#define MIDI_CMD_CHANNEL_PRESSURE&t;0xd0
DECL|macro|MIDI_CMD_BENDER
mdefine_line|#define MIDI_CMD_BENDER&t;&t;&t;0xe0
DECL|macro|MIDI_CMD_COMMON_SYSEX
mdefine_line|#define MIDI_CMD_COMMON_SYSEX&t;&t;0xf0
DECL|macro|MIDI_CMD_COMMON_MTC_QUARTER
mdefine_line|#define MIDI_CMD_COMMON_MTC_QUARTER&t;0xf1
DECL|macro|MIDI_CMD_COMMON_SONG_POS
mdefine_line|#define MIDI_CMD_COMMON_SONG_POS&t;0xf2
DECL|macro|MIDI_CMD_COMMON_SONG_SELECT
mdefine_line|#define MIDI_CMD_COMMON_SONG_SELECT&t;0xf3
DECL|macro|MIDI_CMD_COMMON_TUNE_REQUEST
mdefine_line|#define MIDI_CMD_COMMON_TUNE_REQUEST&t;0xf6
DECL|macro|MIDI_CMD_COMMON_SYSEX_END
mdefine_line|#define MIDI_CMD_COMMON_SYSEX_END&t;0xf7
DECL|macro|MIDI_CMD_COMMON_CLOCK
mdefine_line|#define MIDI_CMD_COMMON_CLOCK&t;&t;0xf8
DECL|macro|MIDI_CMD_COMMON_START
mdefine_line|#define MIDI_CMD_COMMON_START&t;&t;0xfa
DECL|macro|MIDI_CMD_COMMON_CONTINUE
mdefine_line|#define MIDI_CMD_COMMON_CONTINUE&t;0xfb
DECL|macro|MIDI_CMD_COMMON_STOP
mdefine_line|#define MIDI_CMD_COMMON_STOP&t;&t;0xfc
DECL|macro|MIDI_CMD_COMMON_SENSING
mdefine_line|#define MIDI_CMD_COMMON_SENSING&t;&t;0xfe
DECL|macro|MIDI_CMD_COMMON_RESET
mdefine_line|#define MIDI_CMD_COMMON_RESET&t;&t;0xff
multiline_comment|/*&n; *  MIDI controllers&n; */
DECL|macro|MIDI_CTL_MSB_BANK
mdefine_line|#define MIDI_CTL_MSB_BANK&t;&t;0x00
DECL|macro|MIDI_CTL_MSB_MODWHEEL
mdefine_line|#define MIDI_CTL_MSB_MODWHEEL         &t;0x01
DECL|macro|MIDI_CTL_MSB_BREATH
mdefine_line|#define MIDI_CTL_MSB_BREATH           &t;0x02
DECL|macro|MIDI_CTL_MSB_FOOT
mdefine_line|#define MIDI_CTL_MSB_FOOT             &t;0x04
DECL|macro|MIDI_CTL_MSB_PORTNAMENTO_TIME
mdefine_line|#define MIDI_CTL_MSB_PORTNAMENTO_TIME &t;0x05
DECL|macro|MIDI_CTL_MSB_DATA_ENTRY
mdefine_line|#define MIDI_CTL_MSB_DATA_ENTRY&t;&t;0x06
DECL|macro|MIDI_CTL_MSB_MAIN_VOLUME
mdefine_line|#define MIDI_CTL_MSB_MAIN_VOLUME      &t;0x07
DECL|macro|MIDI_CTL_MSB_BALANCE
mdefine_line|#define MIDI_CTL_MSB_BALANCE          &t;0x08
DECL|macro|MIDI_CTL_MSB_PAN
mdefine_line|#define MIDI_CTL_MSB_PAN              &t;0x0a
DECL|macro|MIDI_CTL_MSB_EXPRESSION
mdefine_line|#define MIDI_CTL_MSB_EXPRESSION       &t;0x0b
DECL|macro|MIDI_CTL_MSB_EFFECT1
mdefine_line|#define MIDI_CTL_MSB_EFFECT1&t;&t;0x0c
DECL|macro|MIDI_CTL_MSB_EFFECT2
mdefine_line|#define MIDI_CTL_MSB_EFFECT2&t;&t;0x0d
DECL|macro|MIDI_CTL_MSB_GENERAL_PURPOSE1
mdefine_line|#define MIDI_CTL_MSB_GENERAL_PURPOSE1 &t;0x10
DECL|macro|MIDI_CTL_MSB_GENERAL_PURPOSE2
mdefine_line|#define MIDI_CTL_MSB_GENERAL_PURPOSE2 &t;0x11
DECL|macro|MIDI_CTL_MSB_GENERAL_PURPOSE3
mdefine_line|#define MIDI_CTL_MSB_GENERAL_PURPOSE3 &t;0x12
DECL|macro|MIDI_CTL_MSB_GENERAL_PURPOSE4
mdefine_line|#define MIDI_CTL_MSB_GENERAL_PURPOSE4 &t;0x13
DECL|macro|MIDI_CTL_LSB_BANK
mdefine_line|#define MIDI_CTL_LSB_BANK&t;&t;0x20
DECL|macro|MIDI_CTL_LSB_MODWHEEL
mdefine_line|#define MIDI_CTL_LSB_MODWHEEL        &t;0x21
DECL|macro|MIDI_CTL_LSB_BREATH
mdefine_line|#define MIDI_CTL_LSB_BREATH           &t;0x22
DECL|macro|MIDI_CTL_LSB_FOOT
mdefine_line|#define MIDI_CTL_LSB_FOOT             &t;0x24
DECL|macro|MIDI_CTL_LSB_PORTNAMENTO_TIME
mdefine_line|#define MIDI_CTL_LSB_PORTNAMENTO_TIME &t;0x25
DECL|macro|MIDI_CTL_LSB_DATA_ENTRY
mdefine_line|#define MIDI_CTL_LSB_DATA_ENTRY&t;&t;0x26
DECL|macro|MIDI_CTL_LSB_MAIN_VOLUME
mdefine_line|#define MIDI_CTL_LSB_MAIN_VOLUME      &t;0x27
DECL|macro|MIDI_CTL_LSB_BALANCE
mdefine_line|#define MIDI_CTL_LSB_BALANCE          &t;0x28
DECL|macro|MIDI_CTL_LSB_PAN
mdefine_line|#define MIDI_CTL_LSB_PAN              &t;0x2a
DECL|macro|MIDI_CTL_LSB_EXPRESSION
mdefine_line|#define MIDI_CTL_LSB_EXPRESSION       &t;0x2b
DECL|macro|MIDI_CTL_LSB_EFFECT1
mdefine_line|#define MIDI_CTL_LSB_EFFECT1&t;&t;0x2c
DECL|macro|MIDI_CTL_LSB_EFFECT2
mdefine_line|#define MIDI_CTL_LSB_EFFECT2&t;&t;0x2d
DECL|macro|MIDI_CTL_LSB_GENERAL_PURPOSE1
mdefine_line|#define MIDI_CTL_LSB_GENERAL_PURPOSE1 &t;0x30
DECL|macro|MIDI_CTL_LSB_GENERAL_PURPOSE2
mdefine_line|#define MIDI_CTL_LSB_GENERAL_PURPOSE2 &t;0x31
DECL|macro|MIDI_CTL_LSB_GENERAL_PURPOSE3
mdefine_line|#define MIDI_CTL_LSB_GENERAL_PURPOSE3 &t;0x32
DECL|macro|MIDI_CTL_LSB_GENERAL_PURPOSE4
mdefine_line|#define MIDI_CTL_LSB_GENERAL_PURPOSE4 &t;0x33
DECL|macro|MIDI_CTL_SUSTAIN
mdefine_line|#define MIDI_CTL_SUSTAIN              &t;0x40
DECL|macro|MIDI_CTL_PORTAMENTO
mdefine_line|#define MIDI_CTL_PORTAMENTO           &t;0x41
DECL|macro|MIDI_CTL_SUSTENUTO
mdefine_line|#define MIDI_CTL_SUSTENUTO            &t;0x42
DECL|macro|MIDI_CTL_SOFT_PEDAL
mdefine_line|#define MIDI_CTL_SOFT_PEDAL           &t;0x43
DECL|macro|MIDI_CTL_LEGATO_FOOTSWITCH
mdefine_line|#define MIDI_CTL_LEGATO_FOOTSWITCH&t;0x44
DECL|macro|MIDI_CTL_HOLD2
mdefine_line|#define MIDI_CTL_HOLD2                &t;0x45
DECL|macro|MIDI_CTL_SC1_SOUND_VARIATION
mdefine_line|#define MIDI_CTL_SC1_SOUND_VARIATION&t;0x46
DECL|macro|MIDI_CTL_SC2_TIMBRE
mdefine_line|#define MIDI_CTL_SC2_TIMBRE&t;&t;0x47
DECL|macro|MIDI_CTL_SC3_RELEASE_TIME
mdefine_line|#define MIDI_CTL_SC3_RELEASE_TIME&t;0x48
DECL|macro|MIDI_CTL_SC4_ATTACK_TIME
mdefine_line|#define MIDI_CTL_SC4_ATTACK_TIME&t;0x49
DECL|macro|MIDI_CTL_SC5_BRIGHTNESS
mdefine_line|#define MIDI_CTL_SC5_BRIGHTNESS&t;&t;0x4a
DECL|macro|MIDI_CTL_SC6
mdefine_line|#define MIDI_CTL_SC6&t;&t;&t;0x4b
DECL|macro|MIDI_CTL_SC7
mdefine_line|#define MIDI_CTL_SC7&t;&t;&t;0x4c
DECL|macro|MIDI_CTL_SC8
mdefine_line|#define MIDI_CTL_SC8&t;&t;&t;0x4d
DECL|macro|MIDI_CTL_SC9
mdefine_line|#define MIDI_CTL_SC9&t;&t;&t;0x4e
DECL|macro|MIDI_CTL_SC10
mdefine_line|#define MIDI_CTL_SC10&t;&t;&t;0x4f
DECL|macro|MIDI_CTL_GENERAL_PURPOSE5
mdefine_line|#define MIDI_CTL_GENERAL_PURPOSE5     &t;0x50
DECL|macro|MIDI_CTL_GENERAL_PURPOSE6
mdefine_line|#define MIDI_CTL_GENERAL_PURPOSE6     &t;0x51
DECL|macro|MIDI_CTL_GENERAL_PURPOSE7
mdefine_line|#define MIDI_CTL_GENERAL_PURPOSE7     &t;0x52
DECL|macro|MIDI_CTL_GENERAL_PURPOSE8
mdefine_line|#define MIDI_CTL_GENERAL_PURPOSE8     &t;0x53
DECL|macro|MIDI_CTL_PORNAMENTO_CONTROL
mdefine_line|#define MIDI_CTL_PORNAMENTO_CONTROL&t;0x54
DECL|macro|MIDI_CTL_E1_REVERB_DEPTH
mdefine_line|#define MIDI_CTL_E1_REVERB_DEPTH&t;0x5b
DECL|macro|MIDI_CTL_E2_TREMOLO_DEPTH
mdefine_line|#define MIDI_CTL_E2_TREMOLO_DEPTH&t;0x5c
DECL|macro|MIDI_CTL_E3_CHORUS_DEPTH
mdefine_line|#define MIDI_CTL_E3_CHORUS_DEPTH&t;0x5d
DECL|macro|MIDI_CTL_E4_DETUNE_DEPTH
mdefine_line|#define MIDI_CTL_E4_DETUNE_DEPTH&t;0x5e
DECL|macro|MIDI_CTL_E5_PHASER_DEPTH
mdefine_line|#define MIDI_CTL_E5_PHASER_DEPTH&t;0x5f
DECL|macro|MIDI_CTL_DATA_INCREMENT
mdefine_line|#define MIDI_CTL_DATA_INCREMENT       &t;0x60
DECL|macro|MIDI_CTL_DATA_DECREMENT
mdefine_line|#define MIDI_CTL_DATA_DECREMENT       &t;0x61
DECL|macro|MIDI_CTL_NONREG_PARM_NUM_LSB
mdefine_line|#define MIDI_CTL_NONREG_PARM_NUM_LSB  &t;0x62
DECL|macro|MIDI_CTL_NONREG_PARM_NUM_MSB
mdefine_line|#define MIDI_CTL_NONREG_PARM_NUM_MSB  &t;0x63
DECL|macro|MIDI_CTL_REGIST_PARM_NUM_LSB
mdefine_line|#define MIDI_CTL_REGIST_PARM_NUM_LSB  &t;0x64
DECL|macro|MIDI_CTL_REGIST_PARM_NUM_MSB
mdefine_line|#define MIDI_CTL_REGIST_PARM_NUM_MSB&t;0x65
DECL|macro|MIDI_CTL_ALL_SOUNDS_OFF
mdefine_line|#define MIDI_CTL_ALL_SOUNDS_OFF&t;&t;0x78
DECL|macro|MIDI_CTL_RESET_CONTROLLERS
mdefine_line|#define MIDI_CTL_RESET_CONTROLLERS&t;0x79
DECL|macro|MIDI_CTL_LOCAL_CONTROL_SWITCH
mdefine_line|#define MIDI_CTL_LOCAL_CONTROL_SWITCH&t;0x7a
DECL|macro|MIDI_CTL_ALL_NOTES_OFF
mdefine_line|#define MIDI_CTL_ALL_NOTES_OFF&t;&t;0x7b
DECL|macro|MIDI_CTL_OMNI_OFF
mdefine_line|#define MIDI_CTL_OMNI_OFF&t;&t;0x7c
DECL|macro|MIDI_CTL_OMNI_ON
mdefine_line|#define MIDI_CTL_OMNI_ON&t;&t;0x7d
DECL|macro|MIDI_CTL_MONO1
mdefine_line|#define MIDI_CTL_MONO1&t;&t;&t;0x7e
DECL|macro|MIDI_CTL_MONO2
mdefine_line|#define MIDI_CTL_MONO2&t;&t;&t;0x7f
macro_line|#endif /* __SOUND_ASOUNDEF_H */
eof
