macro_line|#ifndef __SOUND_AD1816A_H
DECL|macro|__SOUND_AD1816A_H
mdefine_line|#define __SOUND_AD1816A_H
multiline_comment|/*&n;    ad1816a.h - definitions for ADI SoundPort AD1816A chip.&n;    Copyright (C) 1999-2000 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;*/
macro_line|#include &quot;control.h&quot;
macro_line|#include &quot;pcm.h&quot;
macro_line|#include &quot;timer.h&quot;
DECL|macro|AD1816A_REG
mdefine_line|#define AD1816A_REG(r)&t;&t;&t;(chip-&gt;port + r)
DECL|macro|AD1816A_CHIP_STATUS
mdefine_line|#define AD1816A_CHIP_STATUS&t;&t;0x00
DECL|macro|AD1816A_INDIR_ADDR
mdefine_line|#define AD1816A_INDIR_ADDR&t;&t;0x00
DECL|macro|AD1816A_INTERRUPT_STATUS
mdefine_line|#define AD1816A_INTERRUPT_STATUS&t;0x01
DECL|macro|AD1816A_INDIR_DATA_LOW
mdefine_line|#define AD1816A_INDIR_DATA_LOW&t;&t;0x02
DECL|macro|AD1816A_INDIR_DATA_HIGH
mdefine_line|#define AD1816A_INDIR_DATA_HIGH&t;&t;0x03
DECL|macro|AD1816A_PIO_DEBUG
mdefine_line|#define AD1816A_PIO_DEBUG&t;&t;0x04
DECL|macro|AD1816A_PIO_STATUS
mdefine_line|#define AD1816A_PIO_STATUS&t;&t;0x05
DECL|macro|AD1816A_PIO_DATA
mdefine_line|#define AD1816A_PIO_DATA&t;&t;0x06
DECL|macro|AD1816A_RESERVED_7
mdefine_line|#define AD1816A_RESERVED_7&t;&t;0x07
DECL|macro|AD1816A_PLAYBACK_CONFIG
mdefine_line|#define AD1816A_PLAYBACK_CONFIG&t;&t;0x08
DECL|macro|AD1816A_CAPTURE_CONFIG
mdefine_line|#define AD1816A_CAPTURE_CONFIG&t;&t;0x09
DECL|macro|AD1816A_RESERVED_10
mdefine_line|#define AD1816A_RESERVED_10&t;&t;0x0a
DECL|macro|AD1816A_RESERVED_11
mdefine_line|#define AD1816A_RESERVED_11&t;&t;0x0b
DECL|macro|AD1816A_JOYSTICK_RAW_DATA
mdefine_line|#define AD1816A_JOYSTICK_RAW_DATA&t;0x0c
DECL|macro|AD1816A_JOYSTICK_CTRL
mdefine_line|#define AD1816A_JOYSTICK_CTRL&t;&t;0x0d
DECL|macro|AD1816A_JOY_POS_DATA_LOW
mdefine_line|#define AD1816A_JOY_POS_DATA_LOW&t;0x0e
DECL|macro|AD1816A_JOY_POS_DATA_HIGH
mdefine_line|#define AD1816A_JOY_POS_DATA_HIGH&t;0x0f
DECL|macro|AD1816A_LOW_BYTE_TMP
mdefine_line|#define AD1816A_LOW_BYTE_TMP&t;&t;0x00
DECL|macro|AD1816A_INTERRUPT_ENABLE
mdefine_line|#define AD1816A_INTERRUPT_ENABLE&t;0x01
DECL|macro|AD1816A_EXTERNAL_CTRL
mdefine_line|#define AD1816A_EXTERNAL_CTRL&t;&t;0x01
DECL|macro|AD1816A_PLAYBACK_SAMPLE_RATE
mdefine_line|#define AD1816A_PLAYBACK_SAMPLE_RATE&t;0x02
DECL|macro|AD1816A_CAPTURE_SAMPLE_RATE
mdefine_line|#define AD1816A_CAPTURE_SAMPLE_RATE&t;0x03
DECL|macro|AD1816A_VOICE_ATT
mdefine_line|#define AD1816A_VOICE_ATT&t;&t;0x04
DECL|macro|AD1816A_FM_ATT
mdefine_line|#define AD1816A_FM_ATT&t;&t;&t;0x05
DECL|macro|AD1816A_I2S_1_ATT
mdefine_line|#define AD1816A_I2S_1_ATT&t;&t;0x06
DECL|macro|AD1816A_I2S_0_ATT
mdefine_line|#define AD1816A_I2S_0_ATT&t;&t;0x07
DECL|macro|AD1816A_PLAYBACK_BASE_COUNT
mdefine_line|#define AD1816A_PLAYBACK_BASE_COUNT&t;0x08
DECL|macro|AD1816A_PLAYBACK_CURR_COUNT
mdefine_line|#define AD1816A_PLAYBACK_CURR_COUNT&t;0x09
DECL|macro|AD1816A_CAPTURE_BASE_COUNT
mdefine_line|#define AD1816A_CAPTURE_BASE_COUNT&t;0x0a
DECL|macro|AD1816A_CAPTURE_CURR_COUNT
mdefine_line|#define AD1816A_CAPTURE_CURR_COUNT&t;0x0b
DECL|macro|AD1816A_TIMER_BASE_COUNT
mdefine_line|#define AD1816A_TIMER_BASE_COUNT&t;0x0c
DECL|macro|AD1816A_TIMER_CURR_COUNT
mdefine_line|#define AD1816A_TIMER_CURR_COUNT&t;0x0d
DECL|macro|AD1816A_MASTER_ATT
mdefine_line|#define AD1816A_MASTER_ATT&t;&t;0x0e
DECL|macro|AD1816A_CD_GAIN_ATT
mdefine_line|#define AD1816A_CD_GAIN_ATT&t;&t;0x0f
DECL|macro|AD1816A_SYNTH_GAIN_ATT
mdefine_line|#define AD1816A_SYNTH_GAIN_ATT&t;&t;0x10
DECL|macro|AD1816A_VID_GAIN_ATT
mdefine_line|#define AD1816A_VID_GAIN_ATT&t;&t;0x11
DECL|macro|AD1816A_LINE_GAIN_ATT
mdefine_line|#define AD1816A_LINE_GAIN_ATT&t;&t;0x12
DECL|macro|AD1816A_MIC_GAIN_ATT
mdefine_line|#define AD1816A_MIC_GAIN_ATT&t;&t;0x13
DECL|macro|AD1816A_PHONE_IN_GAIN_ATT
mdefine_line|#define AD1816A_PHONE_IN_GAIN_ATT&t;0x13
DECL|macro|AD1816A_ADC_SOURCE_SEL
mdefine_line|#define AD1816A_ADC_SOURCE_SEL&t;&t;0x14
DECL|macro|AD1816A_ADC_PGA
mdefine_line|#define AD1816A_ADC_PGA&t;&t;&t;0x14
DECL|macro|AD1816A_CHIP_CONFIG
mdefine_line|#define AD1816A_CHIP_CONFIG&t;&t;0x20
DECL|macro|AD1816A_DSP_CONFIG
mdefine_line|#define AD1816A_DSP_CONFIG&t;&t;0x21
DECL|macro|AD1816A_FM_SAMPLE_RATE
mdefine_line|#define AD1816A_FM_SAMPLE_RATE&t;&t;0x22
DECL|macro|AD1816A_I2S_1_SAMPLE_RATE
mdefine_line|#define AD1816A_I2S_1_SAMPLE_RATE&t;0x23
DECL|macro|AD1816A_I2S_0_SAMPLE_RATE
mdefine_line|#define AD1816A_I2S_0_SAMPLE_RATE&t;0x24
DECL|macro|AD1816A_RESERVED_37
mdefine_line|#define AD1816A_RESERVED_37&t;&t;0x25
DECL|macro|AD1816A_PROGRAM_CLOCK_RATE
mdefine_line|#define AD1816A_PROGRAM_CLOCK_RATE&t;0x26
DECL|macro|AD1816A_3D_PHAT_CTRL
mdefine_line|#define AD1816A_3D_PHAT_CTRL&t;&t;0x27
DECL|macro|AD1816A_PHONE_OUT_ATT
mdefine_line|#define AD1816A_PHONE_OUT_ATT&t;&t;0x27
DECL|macro|AD1816A_RESERVED_40
mdefine_line|#define AD1816A_RESERVED_40&t;&t;0x28
DECL|macro|AD1816A_HW_VOL_BUT
mdefine_line|#define AD1816A_HW_VOL_BUT&t;&t;0x29
DECL|macro|AD1816A_DSP_MAILBOX_0
mdefine_line|#define AD1816A_DSP_MAILBOX_0&t;&t;0x2a
DECL|macro|AD1816A_DSP_MAILBOX_1
mdefine_line|#define AD1816A_DSP_MAILBOX_1&t;&t;0x2b
DECL|macro|AD1816A_POWERDOWN_CTRL
mdefine_line|#define AD1816A_POWERDOWN_CTRL&t;&t;0x2c
DECL|macro|AD1816A_TIMER_CTRL
mdefine_line|#define AD1816A_TIMER_CTRL&t;&t;0x2c
DECL|macro|AD1816A_VERSION_ID
mdefine_line|#define AD1816A_VERSION_ID&t;&t;0x2d
DECL|macro|AD1816A_RESERVED_46
mdefine_line|#define AD1816A_RESERVED_46&t;&t;0x2e
DECL|macro|AD1816A_READY
mdefine_line|#define AD1816A_READY&t;&t;&t;0x80
DECL|macro|AD1816A_PLAYBACK_IRQ_PENDING
mdefine_line|#define AD1816A_PLAYBACK_IRQ_PENDING&t;0x80
DECL|macro|AD1816A_CAPTURE_IRQ_PENDING
mdefine_line|#define AD1816A_CAPTURE_IRQ_PENDING&t;0x40
DECL|macro|AD1816A_TIMER_IRQ_PENDING
mdefine_line|#define AD1816A_TIMER_IRQ_PENDING&t;0x20
DECL|macro|AD1816A_PLAYBACK_ENABLE
mdefine_line|#define AD1816A_PLAYBACK_ENABLE&t;&t;0x01
DECL|macro|AD1816A_PLAYBACK_PIO
mdefine_line|#define AD1816A_PLAYBACK_PIO&t;&t;0x02
DECL|macro|AD1816A_CAPTURE_ENABLE
mdefine_line|#define AD1816A_CAPTURE_ENABLE&t;&t;0x01
DECL|macro|AD1816A_CAPTURE_PIO
mdefine_line|#define AD1816A_CAPTURE_PIO&t;&t;0x02
DECL|macro|AD1816A_FMT_LINEAR_8
mdefine_line|#define AD1816A_FMT_LINEAR_8&t;&t;0x00
DECL|macro|AD1816A_FMT_ULAW_8
mdefine_line|#define AD1816A_FMT_ULAW_8&t;&t;0x08
DECL|macro|AD1816A_FMT_LINEAR_16_LIT
mdefine_line|#define AD1816A_FMT_LINEAR_16_LIT&t;0x10
DECL|macro|AD1816A_FMT_ALAW_8
mdefine_line|#define AD1816A_FMT_ALAW_8&t;&t;0x18
DECL|macro|AD1816A_FMT_LINEAR_16_BIG
mdefine_line|#define AD1816A_FMT_LINEAR_16_BIG&t;0x30
DECL|macro|AD1816A_FMT_ALL
mdefine_line|#define AD1816A_FMT_ALL&t;&t;&t;0x38
DECL|macro|AD1816A_FMT_STEREO
mdefine_line|#define AD1816A_FMT_STEREO&t;&t;0x04
DECL|macro|AD1816A_PLAYBACK_IRQ_ENABLE
mdefine_line|#define AD1816A_PLAYBACK_IRQ_ENABLE&t;0x8000
DECL|macro|AD1816A_CAPTURE_IRQ_ENABLE
mdefine_line|#define AD1816A_CAPTURE_IRQ_ENABLE&t;0x4000
DECL|macro|AD1816A_TIMER_IRQ_ENABLE
mdefine_line|#define AD1816A_TIMER_IRQ_ENABLE&t;0x2000
DECL|macro|AD1816A_TIMER_ENABLE
mdefine_line|#define AD1816A_TIMER_ENABLE&t;&t;0x0080
DECL|macro|AD1816A_SRC_LINE
mdefine_line|#define AD1816A_SRC_LINE&t;&t;0x00
DECL|macro|AD1816A_SRC_OUT
mdefine_line|#define AD1816A_SRC_OUT&t;&t;&t;0x10
DECL|macro|AD1816A_SRC_CD
mdefine_line|#define AD1816A_SRC_CD&t;&t;&t;0x20
DECL|macro|AD1816A_SRC_SYNTH
mdefine_line|#define AD1816A_SRC_SYNTH&t;&t;0x30
DECL|macro|AD1816A_SRC_VIDEO
mdefine_line|#define AD1816A_SRC_VIDEO&t;&t;0x40
DECL|macro|AD1816A_SRC_MIC
mdefine_line|#define AD1816A_SRC_MIC&t;&t;&t;0x50
DECL|macro|AD1816A_SRC_MONO
mdefine_line|#define AD1816A_SRC_MONO&t;&t;0x50
DECL|macro|AD1816A_SRC_PHONE_IN
mdefine_line|#define AD1816A_SRC_PHONE_IN&t;&t;0x60
DECL|macro|AD1816A_SRC_MASK
mdefine_line|#define AD1816A_SRC_MASK&t;&t;0x70
DECL|macro|AD1816A_CAPTURE_NOT_EQUAL
mdefine_line|#define AD1816A_CAPTURE_NOT_EQUAL&t;0x1000
DECL|macro|AD1816A_WSS_ENABLE
mdefine_line|#define AD1816A_WSS_ENABLE&t;&t;0x8000
DECL|typedef|ad1816a_t
r_typedef
r_struct
id|_snd_ad1816a
id|ad1816a_t
suffix:semicolon
DECL|struct|_snd_ad1816a
r_struct
id|_snd_ad1816a
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dma1
r_int
id|dma1
suffix:semicolon
DECL|member|dma2
r_int
id|dma2
suffix:semicolon
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
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
DECL|member|p_dma_size
r_int
r_int
id|p_dma_size
suffix:semicolon
DECL|member|c_dma_size
r_int
r_int
id|c_dma_size
suffix:semicolon
DECL|member|timer
id|snd_timer_t
op_star
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AD1816A_HW_AUTO
mdefine_line|#define AD1816A_HW_AUTO&t;&t;0
DECL|macro|AD1816A_HW_AD1816A
mdefine_line|#define AD1816A_HW_AD1816A&t;1
DECL|macro|AD1816A_HW_AD1815
mdefine_line|#define AD1816A_HW_AD1815&t;2
DECL|macro|AD1816A_HW_AD18MAX10
mdefine_line|#define AD1816A_HW_AD18MAX10&t;3
DECL|macro|AD1816A_MODE_PLAYBACK
mdefine_line|#define AD1816A_MODE_PLAYBACK&t;0x01
DECL|macro|AD1816A_MODE_CAPTURE
mdefine_line|#define AD1816A_MODE_CAPTURE&t;0x02
DECL|macro|AD1816A_MODE_TIMER
mdefine_line|#define AD1816A_MODE_TIMER&t;0x04
DECL|macro|AD1816A_MODE_OPEN
mdefine_line|#define AD1816A_MODE_OPEN&t;(AD1816A_MODE_PLAYBACK |&t;&bslash;&n;&t;&t;&t;&t;AD1816A_MODE_CAPTURE |&t;&t;&bslash;&n;&t;&t;&t;&t;AD1816A_MODE_TIMER)
r_extern
r_int
id|snd_ad1816a_create
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
r_int
id|dma1
comma
r_int
id|dma2
comma
id|ad1816a_t
op_star
op_star
id|chip
)paren
suffix:semicolon
r_extern
r_int
id|snd_ad1816a_pcm
c_func
(paren
id|ad1816a_t
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
r_extern
r_int
id|snd_ad1816a_mixer
c_func
(paren
id|ad1816a_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#endif&t;/* __SOUND_AD1816A_H */
eof
