macro_line|#ifndef __SOUND_SB_H
DECL|macro|__SOUND_SB_H
mdefine_line|#define __SOUND_SB_H
multiline_comment|/*&n; *  Header file for SoundBlaster cards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;pcm.h&quot;
macro_line|#include &quot;rawmidi.h&quot;
macro_line|#include &lt;asm/io.h&gt;
DECL|enum|sb_hw_type
r_enum
id|sb_hw_type
(brace
DECL|enumerator|SB_HW_AUTO
id|SB_HW_AUTO
comma
DECL|enumerator|SB_HW_10
id|SB_HW_10
comma
DECL|enumerator|SB_HW_20
id|SB_HW_20
comma
DECL|enumerator|SB_HW_201
id|SB_HW_201
comma
DECL|enumerator|SB_HW_PRO
id|SB_HW_PRO
comma
DECL|enumerator|SB_HW_16
id|SB_HW_16
comma
DECL|enumerator|SB_HW_16CSP
id|SB_HW_16CSP
comma
multiline_comment|/* SB16 with CSP chip */
DECL|enumerator|SB_HW_ALS100
id|SB_HW_ALS100
comma
multiline_comment|/* Avance Logic ALS100 chip */
DECL|enumerator|SB_HW_ALS4000
id|SB_HW_ALS4000
comma
multiline_comment|/* Avance Logic ALS4000 chip */
)brace
suffix:semicolon
DECL|macro|SB_OPEN_PCM
mdefine_line|#define SB_OPEN_PCM&t;&t;0x01
DECL|macro|SB_OPEN_MIDI_INPUT
mdefine_line|#define SB_OPEN_MIDI_INPUT&t;0x02
DECL|macro|SB_OPEN_MIDI_OUTPUT
mdefine_line|#define SB_OPEN_MIDI_OUTPUT&t;0x04
DECL|macro|SB_OPEN_MIDI_TRIGGER
mdefine_line|#define SB_OPEN_MIDI_TRIGGER&t;0x08
DECL|macro|SB_MODE_HALT
mdefine_line|#define SB_MODE_HALT&t;&t;0x00
DECL|macro|SB_MODE_PLAYBACK_8
mdefine_line|#define SB_MODE_PLAYBACK_8&t;0x01
DECL|macro|SB_MODE_PLAYBACK_16
mdefine_line|#define SB_MODE_PLAYBACK_16&t;0x02
DECL|macro|SB_MODE_PLAYBACK
mdefine_line|#define SB_MODE_PLAYBACK&t;(SB_MODE_PLAYBACK_8 | SB_MODE_PLAYBACK_16)
DECL|macro|SB_MODE_CAPTURE_8
mdefine_line|#define SB_MODE_CAPTURE_8&t;0x04
DECL|macro|SB_MODE_CAPTURE_16
mdefine_line|#define SB_MODE_CAPTURE_16&t;0x08
DECL|macro|SB_MODE_CAPTURE
mdefine_line|#define SB_MODE_CAPTURE&t;&t;(SB_MODE_CAPTURE_8 | SB_MODE_CAPTURE_16)
DECL|macro|SB_RATE_LOCK_PLAYBACK
mdefine_line|#define SB_RATE_LOCK_PLAYBACK&t;0x10
DECL|macro|SB_RATE_LOCK_CAPTURE
mdefine_line|#define SB_RATE_LOCK_CAPTURE&t;0x20
DECL|macro|SB_RATE_LOCK
mdefine_line|#define SB_RATE_LOCK&t;&t;(SB_RATE_LOCK_PLAYBACK | SB_RATE_LOCK_CAPTURE)
DECL|macro|SB_MPU_INPUT
mdefine_line|#define SB_MPU_INPUT&t;&t;1
DECL|struct|_snd_sb
r_struct
id|_snd_sb
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* base port of DSP chip */
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|alt_port
r_int
r_int
id|alt_port
suffix:semicolon
multiline_comment|/* alternate port (ALS4000) */
DECL|member|res_alt_port
r_struct
id|resource
op_star
id|res_alt_port
suffix:semicolon
DECL|member|mpu_port
r_int
r_int
id|mpu_port
suffix:semicolon
multiline_comment|/* MPU port for SB DSP 4.0+ */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ number of DSP chip */
DECL|member|dma8
r_int
id|dma8
suffix:semicolon
multiline_comment|/* 8-bit DMA */
DECL|member|dma16
r_int
id|dma16
suffix:semicolon
multiline_comment|/* 16-bit DMA */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* version of DSP chip */
DECL|member|hardware
r_enum
id|sb_hw_type
id|hardware
suffix:semicolon
multiline_comment|/* see to SB_HW_XXXX */
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
multiline_comment|/* ALS4000 */
DECL|member|open
r_int
r_int
id|open
suffix:semicolon
multiline_comment|/* see to SB_OPEN_XXXX for sb8 */
multiline_comment|/* also SNDRV_SB_CSP_MODE_XXX for sb16_csp */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* current mode of stream */
DECL|member|force_mode16
r_int
r_int
id|force_mode16
suffix:semicolon
multiline_comment|/* force 16-bit mode of streams */
DECL|member|locked_rate
r_int
r_int
id|locked_rate
suffix:semicolon
multiline_comment|/* sb16 duplex */
DECL|member|playback_format
r_int
r_int
id|playback_format
suffix:semicolon
DECL|member|capture_format
r_int
r_int
id|capture_format
suffix:semicolon
DECL|member|midi_timer
r_struct
id|timer_list
id|midi_timer
suffix:semicolon
DECL|member|p_dma_size
r_int
r_int
id|p_dma_size
suffix:semicolon
DECL|member|p_period_size
r_int
r_int
id|p_period_size
suffix:semicolon
DECL|member|c_dma_size
r_int
r_int
id|c_dma_size
suffix:semicolon
DECL|member|c_period_size
r_int
r_int
id|c_period_size
suffix:semicolon
DECL|member|mixer_lock
id|spinlock_t
id|mixer_lock
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|csp
r_void
op_star
id|csp
suffix:semicolon
multiline_comment|/* used only when CONFIG_SND_SB16_CSP is set */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|playback_substream
id|snd_pcm_substream_t
op_star
id|playback_substream
suffix:semicolon
DECL|member|capture_substream
id|snd_pcm_substream_t
op_star
id|capture_substream
suffix:semicolon
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
DECL|member|midi_substream_input
id|snd_rawmidi_substream_t
op_star
id|midi_substream_input
suffix:semicolon
DECL|member|midi_substream_output
id|snd_rawmidi_substream_t
op_star
id|midi_substream_output
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|open_lock
id|spinlock_t
id|open_lock
suffix:semicolon
DECL|member|midi_input_lock
id|spinlock_t
id|midi_input_lock
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|sb_t
r_typedef
r_struct
id|_snd_sb
id|sb_t
suffix:semicolon
multiline_comment|/* I/O ports */
DECL|macro|SBP
mdefine_line|#define SBP(chip, x)&t;&t;((chip)-&gt;port + s_b_SB_##x)
DECL|macro|SBP1
mdefine_line|#define SBP1(port, x)&t;&t;((port) + s_b_SB_##x)
DECL|macro|s_b_SB_RESET
mdefine_line|#define s_b_SB_RESET&t;&t;0x6
DECL|macro|s_b_SB_READ
mdefine_line|#define s_b_SB_READ&t;&t;0xa
DECL|macro|s_b_SB_WRITE
mdefine_line|#define s_b_SB_WRITE&t;&t;0xc
DECL|macro|s_b_SB_COMMAND
mdefine_line|#define s_b_SB_COMMAND&t;&t;0xc
DECL|macro|s_b_SB_STATUS
mdefine_line|#define s_b_SB_STATUS&t;&t;0xc
DECL|macro|s_b_SB_DATA_AVAIL
mdefine_line|#define s_b_SB_DATA_AVAIL&t;0xe
DECL|macro|s_b_SB_DATA_AVAIL_16
mdefine_line|#define s_b_SB_DATA_AVAIL_16 &t;0xf
DECL|macro|s_b_SB_MIXER_ADDR
mdefine_line|#define s_b_SB_MIXER_ADDR&t;0x4
DECL|macro|s_b_SB_MIXER_DATA
mdefine_line|#define s_b_SB_MIXER_DATA&t;0x5
DECL|macro|s_b_SB_OPL3_LEFT
mdefine_line|#define s_b_SB_OPL3_LEFT&t;0x0
DECL|macro|s_b_SB_OPL3_RIGHT
mdefine_line|#define s_b_SB_OPL3_RIGHT&t;0x2
DECL|macro|s_b_SB_OPL3_BOTH
mdefine_line|#define s_b_SB_OPL3_BOTH&t;0x8
DECL|macro|SB_DSP_OUTPUT
mdefine_line|#define SB_DSP_OUTPUT&t;&t;0x14
DECL|macro|SB_DSP_INPUT
mdefine_line|#define SB_DSP_INPUT&t;&t;0x24
DECL|macro|SB_DSP_BLOCK_SIZE
mdefine_line|#define SB_DSP_BLOCK_SIZE&t;0x48
DECL|macro|SB_DSP_HI_OUTPUT
mdefine_line|#define SB_DSP_HI_OUTPUT&t;0x91
DECL|macro|SB_DSP_HI_INPUT
mdefine_line|#define SB_DSP_HI_INPUT&t;&t;0x99
DECL|macro|SB_DSP_LO_OUTPUT_AUTO
mdefine_line|#define SB_DSP_LO_OUTPUT_AUTO&t;0x1c
DECL|macro|SB_DSP_LO_INPUT_AUTO
mdefine_line|#define SB_DSP_LO_INPUT_AUTO&t;0x2c
DECL|macro|SB_DSP_HI_OUTPUT_AUTO
mdefine_line|#define SB_DSP_HI_OUTPUT_AUTO&t;0x90
DECL|macro|SB_DSP_HI_INPUT_AUTO
mdefine_line|#define SB_DSP_HI_INPUT_AUTO&t;0x98
DECL|macro|SB_DSP_IMMED_INT
mdefine_line|#define SB_DSP_IMMED_INT&t;0xf2
DECL|macro|SB_DSP_GET_VERSION
mdefine_line|#define SB_DSP_GET_VERSION&t;0xe1
DECL|macro|SB_DSP_SPEAKER_ON
mdefine_line|#define SB_DSP_SPEAKER_ON&t;0xd1
DECL|macro|SB_DSP_SPEAKER_OFF
mdefine_line|#define SB_DSP_SPEAKER_OFF&t;0xd3
DECL|macro|SB_DSP_DMA8_OFF
mdefine_line|#define SB_DSP_DMA8_OFF&t;&t;0xd0
DECL|macro|SB_DSP_DMA8_ON
mdefine_line|#define SB_DSP_DMA8_ON&t;&t;0xd4
DECL|macro|SB_DSP_DMA8_EXIT
mdefine_line|#define SB_DSP_DMA8_EXIT&t;0xda
DECL|macro|SB_DSP_DMA16_OFF
mdefine_line|#define SB_DSP_DMA16_OFF&t;0xd5
DECL|macro|SB_DSP_DMA16_ON
mdefine_line|#define SB_DSP_DMA16_ON&t;&t;0xd6
DECL|macro|SB_DSP_DMA16_EXIT
mdefine_line|#define SB_DSP_DMA16_EXIT&t;0xd9
DECL|macro|SB_DSP_SAMPLE_RATE
mdefine_line|#define SB_DSP_SAMPLE_RATE&t;0x40
DECL|macro|SB_DSP_SAMPLE_RATE_OUT
mdefine_line|#define SB_DSP_SAMPLE_RATE_OUT&t;0x41
DECL|macro|SB_DSP_SAMPLE_RATE_IN
mdefine_line|#define SB_DSP_SAMPLE_RATE_IN&t;0x42
DECL|macro|SB_DSP_MONO_8BIT
mdefine_line|#define SB_DSP_MONO_8BIT&t;0xa0
DECL|macro|SB_DSP_MONO_16BIT
mdefine_line|#define SB_DSP_MONO_16BIT&t;0xa4
DECL|macro|SB_DSP_STEREO_8BIT
mdefine_line|#define SB_DSP_STEREO_8BIT&t;0xa8
DECL|macro|SB_DSP_STEREO_16BIT
mdefine_line|#define SB_DSP_STEREO_16BIT&t;0xac
DECL|macro|SB_DSP_MIDI_INPUT_IRQ
mdefine_line|#define SB_DSP_MIDI_INPUT_IRQ&t;0x31
DECL|macro|SB_DSP_MIDI_OUTPUT
mdefine_line|#define SB_DSP_MIDI_OUTPUT&t;0x38
DECL|macro|SB_DSP4_OUT8_AI
mdefine_line|#define SB_DSP4_OUT8_AI&t;&t;0xc6
DECL|macro|SB_DSP4_IN8_AI
mdefine_line|#define SB_DSP4_IN8_AI&t;&t;0xce
DECL|macro|SB_DSP4_OUT16_AI
mdefine_line|#define SB_DSP4_OUT16_AI&t;0xb6
DECL|macro|SB_DSP4_IN16_AI
mdefine_line|#define SB_DSP4_IN16_AI&t;&t;0xbe
DECL|macro|SB_DSP4_MODE_UNS_MONO
mdefine_line|#define SB_DSP4_MODE_UNS_MONO&t;0x00
DECL|macro|SB_DSP4_MODE_SIGN_MONO
mdefine_line|#define SB_DSP4_MODE_SIGN_MONO&t;0x10
DECL|macro|SB_DSP4_MODE_UNS_STEREO
mdefine_line|#define SB_DSP4_MODE_UNS_STEREO&t;0x20
DECL|macro|SB_DSP4_MODE_SIGN_STEREO
mdefine_line|#define SB_DSP4_MODE_SIGN_STEREO 0x30
DECL|macro|SB_DSP4_OUTPUT
mdefine_line|#define SB_DSP4_OUTPUT&t;&t;0x3c
DECL|macro|SB_DSP4_INPUT_LEFT
mdefine_line|#define SB_DSP4_INPUT_LEFT&t;0x3d
DECL|macro|SB_DSP4_INPUT_RIGHT
mdefine_line|#define SB_DSP4_INPUT_RIGHT&t;0x3e
multiline_comment|/* registers for SB 2.0 mixer */
DECL|macro|SB_DSP20_MASTER_DEV
mdefine_line|#define SB_DSP20_MASTER_DEV&t;0x02
DECL|macro|SB_DSP20_PCM_DEV
mdefine_line|#define SB_DSP20_PCM_DEV&t;0x0A
DECL|macro|SB_DSP20_CD_DEV
mdefine_line|#define SB_DSP20_CD_DEV&t;&t;0x08
DECL|macro|SB_DSP20_FM_DEV
mdefine_line|#define SB_DSP20_FM_DEV&t;&t;0x06
multiline_comment|/* registers for SB PRO mixer */
DECL|macro|SB_DSP_MASTER_DEV
mdefine_line|#define SB_DSP_MASTER_DEV&t;0x22
DECL|macro|SB_DSP_PCM_DEV
mdefine_line|#define SB_DSP_PCM_DEV&t;&t;0x04
DECL|macro|SB_DSP_LINE_DEV
mdefine_line|#define SB_DSP_LINE_DEV&t;&t;0x2e
DECL|macro|SB_DSP_CD_DEV
mdefine_line|#define SB_DSP_CD_DEV&t;&t;0x28
DECL|macro|SB_DSP_FM_DEV
mdefine_line|#define SB_DSP_FM_DEV&t;&t;0x26
DECL|macro|SB_DSP_MIC_DEV
mdefine_line|#define SB_DSP_MIC_DEV&t;&t;0x0a
DECL|macro|SB_DSP_CAPTURE_SOURCE
mdefine_line|#define SB_DSP_CAPTURE_SOURCE&t;0x0c
DECL|macro|SB_DSP_CAPTURE_FILT
mdefine_line|#define SB_DSP_CAPTURE_FILT&t;0x0c
DECL|macro|SB_DSP_PLAYBACK_FILT
mdefine_line|#define SB_DSP_PLAYBACK_FILT&t;0x0e
DECL|macro|SB_DSP_STEREO_SW
mdefine_line|#define SB_DSP_STEREO_SW&t;0x0e
DECL|macro|SB_DSP_MIXS_MIC0
mdefine_line|#define SB_DSP_MIXS_MIC0&t;0x00&t;/* same as MIC */
DECL|macro|SB_DSP_MIXS_CD
mdefine_line|#define SB_DSP_MIXS_CD&t;&t;0x01
DECL|macro|SB_DSP_MIXS_MIC
mdefine_line|#define SB_DSP_MIXS_MIC&t;&t;0x02
DECL|macro|SB_DSP_MIXS_LINE
mdefine_line|#define SB_DSP_MIXS_LINE&t;0x03
multiline_comment|/* registers (only for left channel) for SB 16 mixer */
DECL|macro|SB_DSP4_MASTER_DEV
mdefine_line|#define SB_DSP4_MASTER_DEV&t;0x30
DECL|macro|SB_DSP4_BASS_DEV
mdefine_line|#define SB_DSP4_BASS_DEV&t;0x46
DECL|macro|SB_DSP4_TREBLE_DEV
mdefine_line|#define SB_DSP4_TREBLE_DEV&t;0x44
DECL|macro|SB_DSP4_SYNTH_DEV
mdefine_line|#define SB_DSP4_SYNTH_DEV&t;0x34
DECL|macro|SB_DSP4_PCM_DEV
mdefine_line|#define SB_DSP4_PCM_DEV&t;&t;0x32
DECL|macro|SB_DSP4_SPEAKER_DEV
mdefine_line|#define SB_DSP4_SPEAKER_DEV&t;0x3b
DECL|macro|SB_DSP4_LINE_DEV
mdefine_line|#define SB_DSP4_LINE_DEV&t;0x38
DECL|macro|SB_DSP4_MIC_DEV
mdefine_line|#define SB_DSP4_MIC_DEV&t;&t;0x3a
DECL|macro|SB_DSP4_OUTPUT_SW
mdefine_line|#define SB_DSP4_OUTPUT_SW&t;0x3c
DECL|macro|SB_DSP4_CD_DEV
mdefine_line|#define SB_DSP4_CD_DEV&t;&t;0x36
DECL|macro|SB_DSP4_IGAIN_DEV
mdefine_line|#define SB_DSP4_IGAIN_DEV&t;0x3f
DECL|macro|SB_DSP4_OGAIN_DEV
mdefine_line|#define SB_DSP4_OGAIN_DEV&t;0x41
DECL|macro|SB_DSP4_MIC_AGC
mdefine_line|#define SB_DSP4_MIC_AGC&t;&t;0x43
multiline_comment|/* additional registers for SB 16 mixer */
DECL|macro|SB_DSP4_IRQSETUP
mdefine_line|#define SB_DSP4_IRQSETUP&t;0x80
DECL|macro|SB_DSP4_DMASETUP
mdefine_line|#define SB_DSP4_DMASETUP&t;0x81
DECL|macro|SB_DSP4_IRQSTATUS
mdefine_line|#define SB_DSP4_IRQSTATUS&t;0x82
DECL|macro|SB_DSP4_MPUSETUP
mdefine_line|#define SB_DSP4_MPUSETUP&t;0x84
DECL|macro|SB_DSP4_3DSE
mdefine_line|#define SB_DSP4_3DSE&t;&t;0x90
multiline_comment|/* IRQ setting bitmap */
DECL|macro|SB_IRQSETUP_IRQ9
mdefine_line|#define SB_IRQSETUP_IRQ9&t;0x01
DECL|macro|SB_IRQSETUP_IRQ5
mdefine_line|#define SB_IRQSETUP_IRQ5&t;0x02
DECL|macro|SB_IRQSETUP_IRQ7
mdefine_line|#define SB_IRQSETUP_IRQ7&t;0x04
DECL|macro|SB_IRQSETUP_IRQ10
mdefine_line|#define SB_IRQSETUP_IRQ10&t;0x08
multiline_comment|/* IRQ types */
DECL|macro|SB_IRQTYPE_8BIT
mdefine_line|#define SB_IRQTYPE_8BIT&t;&t;0x01
DECL|macro|SB_IRQTYPE_16BIT
mdefine_line|#define SB_IRQTYPE_16BIT&t;0x02
DECL|macro|SB_IRQTYPE_MPUIN
mdefine_line|#define SB_IRQTYPE_MPUIN&t;0x04
multiline_comment|/* DMA setting bitmap */
DECL|macro|SB_DMASETUP_DMA0
mdefine_line|#define SB_DMASETUP_DMA0&t;0x01
DECL|macro|SB_DMASETUP_DMA1
mdefine_line|#define SB_DMASETUP_DMA1&t;0x02
DECL|macro|SB_DMASETUP_DMA3
mdefine_line|#define SB_DMASETUP_DMA3&t;0x08
DECL|macro|SB_DMASETUP_DMA5
mdefine_line|#define SB_DMASETUP_DMA5&t;0x20
DECL|macro|SB_DMASETUP_DMA6
mdefine_line|#define SB_DMASETUP_DMA6&t;0x40
DECL|macro|SB_DMASETUP_DMA7
mdefine_line|#define SB_DMASETUP_DMA7&t;0x80
multiline_comment|/*&n; *&n; */
DECL|function|snd_sb_ack_8bit
r_static
r_inline
r_void
id|snd_sb_ack_8bit
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|DATA_AVAIL
)paren
)paren
suffix:semicolon
)brace
DECL|function|snd_sb_ack_16bit
r_static
r_inline
r_void
id|snd_sb_ack_16bit
c_func
(paren
id|sb_t
op_star
id|chip
)paren
(brace
id|inb
c_func
(paren
id|SBP
c_func
(paren
id|chip
comma
id|DATA_AVAIL_16
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* sb_common.c */
r_int
id|snd_sbdsp_command
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
id|snd_sbdsp_get_byte
c_func
(paren
id|sb_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_sbdsp_reset
c_func
(paren
id|sb_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_sbdsp_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|port
comma
r_int
id|irq
comma
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|dma8
comma
r_int
id|dma16
comma
r_int
r_int
id|hardware
comma
id|sb_t
op_star
op_star
id|r_chip
)paren
suffix:semicolon
multiline_comment|/* sb_mixer.c */
r_void
id|snd_sbmixer_write
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|data
)paren
suffix:semicolon
r_int
r_char
id|snd_sbmixer_read
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
r_char
id|reg
)paren
suffix:semicolon
r_int
id|snd_sbmixer_new
c_func
(paren
id|sb_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/* sb8_init.c */
r_int
id|snd_sb8dsp_pcm
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
suffix:semicolon
multiline_comment|/* sb8.c */
r_void
id|snd_sb8dsp_interrupt
c_func
(paren
id|sb_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_sb8_playback_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_sb8_capture_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_sb8_playback_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_sb8_capture_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
multiline_comment|/* midi8.c */
r_void
id|snd_sb8dsp_midi_interrupt
c_func
(paren
id|sb_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_sb8dsp_midi
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
id|device
comma
id|snd_rawmidi_t
op_star
op_star
id|rrawmidi
)paren
suffix:semicolon
multiline_comment|/* sb16_init.c */
r_int
id|snd_sb16dsp_pcm
c_func
(paren
id|sb_t
op_star
id|chip
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
suffix:semicolon
r_int
id|snd_sb16dsp_configure
c_func
(paren
id|sb_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/* sb16.c */
r_void
id|snd_sb16dsp_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
id|snd_sb16_playback_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_sb16_capture_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_sb16_playback_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_sb16_capture_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_SB_H */
eof
