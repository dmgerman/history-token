macro_line|#ifndef __SOUND_CS4231_H
DECL|macro|__SOUND_CS4231_H
mdefine_line|#define __SOUND_CS4231_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Definitions for CS4231 &amp; InterWave chips &amp; compatible chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;control.h&quot;
macro_line|#include &quot;pcm.h&quot;
macro_line|#include &quot;timer.h&quot;
multiline_comment|/* IO ports */
DECL|macro|CS4231P
mdefine_line|#define CS4231P(chip, x)&t;((chip)-&gt;port + c_d_c_CS4231##x)
DECL|macro|c_d_c_CS4231REGSEL
mdefine_line|#define c_d_c_CS4231REGSEL&t;0
DECL|macro|c_d_c_CS4231REG
mdefine_line|#define c_d_c_CS4231REG&t;&t;1
DECL|macro|c_d_c_CS4231STATUS
mdefine_line|#define c_d_c_CS4231STATUS&t;2
DECL|macro|c_d_c_CS4231PIO
mdefine_line|#define c_d_c_CS4231PIO&t;&t;3
multiline_comment|/* codec registers */
DECL|macro|CS4231_LEFT_INPUT
mdefine_line|#define CS4231_LEFT_INPUT&t;0x00&t;/* left input control */
DECL|macro|CS4231_RIGHT_INPUT
mdefine_line|#define CS4231_RIGHT_INPUT&t;0x01&t;/* right input control */
DECL|macro|CS4231_AUX1_LEFT_INPUT
mdefine_line|#define CS4231_AUX1_LEFT_INPUT&t;0x02&t;/* left AUX1 input control */
DECL|macro|CS4231_AUX1_RIGHT_INPUT
mdefine_line|#define CS4231_AUX1_RIGHT_INPUT&t;0x03&t;/* right AUX1 input control */
DECL|macro|CS4231_AUX2_LEFT_INPUT
mdefine_line|#define CS4231_AUX2_LEFT_INPUT&t;0x04&t;/* left AUX2 input control */
DECL|macro|CS4231_AUX2_RIGHT_INPUT
mdefine_line|#define CS4231_AUX2_RIGHT_INPUT&t;0x05&t;/* right AUX2 input control */
DECL|macro|CS4231_LEFT_OUTPUT
mdefine_line|#define CS4231_LEFT_OUTPUT&t;0x06&t;/* left output control register */
DECL|macro|CS4231_RIGHT_OUTPUT
mdefine_line|#define CS4231_RIGHT_OUTPUT&t;0x07&t;/* right output control register */
DECL|macro|CS4231_PLAYBK_FORMAT
mdefine_line|#define CS4231_PLAYBK_FORMAT&t;0x08&t;/* clock and data format - playback - bits 7-0 MCE */
DECL|macro|CS4231_IFACE_CTRL
mdefine_line|#define CS4231_IFACE_CTRL&t;0x09&t;/* interface control - bits 7-2 MCE */
DECL|macro|CS4231_PIN_CTRL
mdefine_line|#define CS4231_PIN_CTRL&t;&t;0x0a&t;/* pin control */
DECL|macro|CS4231_TEST_INIT
mdefine_line|#define CS4231_TEST_INIT&t;0x0b&t;/* test and initialization */
DECL|macro|CS4231_MISC_INFO
mdefine_line|#define CS4231_MISC_INFO&t;0x0c&t;/* miscellaneaous information */
DECL|macro|CS4231_LOOPBACK
mdefine_line|#define CS4231_LOOPBACK&t;&t;0x0d&t;/* loopback control */
DECL|macro|CS4231_PLY_UPR_CNT
mdefine_line|#define CS4231_PLY_UPR_CNT&t;0x0e&t;/* playback upper base count */
DECL|macro|CS4231_PLY_LWR_CNT
mdefine_line|#define CS4231_PLY_LWR_CNT&t;0x0f&t;/* playback lower base count */
DECL|macro|CS4231_ALT_FEATURE_1
mdefine_line|#define CS4231_ALT_FEATURE_1&t;0x10&t;/* alternate #1 feature enable */
DECL|macro|CS4231_ALT_FEATURE_2
mdefine_line|#define CS4231_ALT_FEATURE_2&t;0x11&t;/* alternate #2 feature enable */
DECL|macro|CS4231_LEFT_LINE_IN
mdefine_line|#define CS4231_LEFT_LINE_IN&t;0x12&t;/* left line input control */
DECL|macro|CS4231_RIGHT_LINE_IN
mdefine_line|#define CS4231_RIGHT_LINE_IN&t;0x13&t;/* right line input control */
DECL|macro|CS4231_TIMER_LOW
mdefine_line|#define CS4231_TIMER_LOW&t;0x14&t;/* timer low byte */
DECL|macro|CS4231_TIMER_HIGH
mdefine_line|#define CS4231_TIMER_HIGH&t;0x15&t;/* timer high byte */
DECL|macro|CS4231_LEFT_MIC_INPUT
mdefine_line|#define CS4231_LEFT_MIC_INPUT&t;0x16&t;/* left MIC input control register (InterWave only) */
DECL|macro|CS4231_RIGHT_MIC_INPUT
mdefine_line|#define CS4231_RIGHT_MIC_INPUT&t;0x17&t;/* right MIC input control register (InterWave only) */
DECL|macro|CS4236_EXT_REG
mdefine_line|#define CS4236_EXT_REG&t;&t;0x17&t;/* extended register access */
DECL|macro|CS4231_IRQ_STATUS
mdefine_line|#define CS4231_IRQ_STATUS&t;0x18&t;/* irq status register */
DECL|macro|CS4231_LINE_LEFT_OUTPUT
mdefine_line|#define CS4231_LINE_LEFT_OUTPUT&t;0x19&t;/* left line output control register (InterWave only) */
DECL|macro|CS4231_VERSION
mdefine_line|#define CS4231_VERSION&t;&t;0x19&t;/* CS4231(A) - version values */
DECL|macro|CS4231_MONO_CTRL
mdefine_line|#define CS4231_MONO_CTRL&t;0x1a&t;/* mono input/output control */
DECL|macro|CS4231_LINE_RIGHT_OUTPUT
mdefine_line|#define CS4231_LINE_RIGHT_OUTPUT 0x1b&t;/* right line output control register (InterWave only) */
DECL|macro|CS4235_LEFT_MASTER
mdefine_line|#define CS4235_LEFT_MASTER&t;0x1b&t;/* left master output control */
DECL|macro|CS4231_REC_FORMAT
mdefine_line|#define CS4231_REC_FORMAT&t;0x1c&t;/* clock and data format - record - bits 7-0 MCE */
DECL|macro|CS4231_PLY_VAR_FREQ
mdefine_line|#define CS4231_PLY_VAR_FREQ&t;0x1d&t;/* playback variable frequency */
DECL|macro|CS4235_RIGHT_MASTER
mdefine_line|#define CS4235_RIGHT_MASTER&t;0x1d&t;/* right master output control */
DECL|macro|CS4231_REC_UPR_CNT
mdefine_line|#define CS4231_REC_UPR_CNT&t;0x1e&t;/* record upper count */
DECL|macro|CS4231_REC_LWR_CNT
mdefine_line|#define CS4231_REC_LWR_CNT&t;0x1f&t;/* record lower count */
multiline_comment|/* definitions for codec register select port - CODECP( REGSEL ) */
DECL|macro|CS4231_INIT
mdefine_line|#define CS4231_INIT&t;&t;0x80&t;/* CODEC is initializing */
DECL|macro|CS4231_MCE
mdefine_line|#define CS4231_MCE&t;&t;0x40&t;/* mode change enable */
DECL|macro|CS4231_TRD
mdefine_line|#define CS4231_TRD&t;&t;0x20&t;/* transfer request disable */
multiline_comment|/* definitions for codec status register - CODECP( STATUS ) */
DECL|macro|CS4231_GLOBALIRQ
mdefine_line|#define CS4231_GLOBALIRQ&t;0x01&t;/* IRQ is active */
multiline_comment|/* definitions for codec irq status */
DECL|macro|CS4231_PLAYBACK_IRQ
mdefine_line|#define CS4231_PLAYBACK_IRQ&t;0x10
DECL|macro|CS4231_RECORD_IRQ
mdefine_line|#define CS4231_RECORD_IRQ&t;0x20
DECL|macro|CS4231_TIMER_IRQ
mdefine_line|#define CS4231_TIMER_IRQ&t;0x40
DECL|macro|CS4231_ALL_IRQS
mdefine_line|#define CS4231_ALL_IRQS&t;&t;0x70
DECL|macro|CS4231_REC_UNDERRUN
mdefine_line|#define CS4231_REC_UNDERRUN&t;0x08
DECL|macro|CS4231_REC_OVERRUN
mdefine_line|#define CS4231_REC_OVERRUN&t;0x04
DECL|macro|CS4231_PLY_OVERRUN
mdefine_line|#define CS4231_PLY_OVERRUN&t;0x02
DECL|macro|CS4231_PLY_UNDERRUN
mdefine_line|#define CS4231_PLY_UNDERRUN&t;0x01
multiline_comment|/* definitions for CS4231_LEFT_INPUT and CS4231_RIGHT_INPUT registers */
DECL|macro|CS4231_ENABLE_MIC_GAIN
mdefine_line|#define CS4231_ENABLE_MIC_GAIN&t;0x20
DECL|macro|CS4231_MIXS_LINE
mdefine_line|#define CS4231_MIXS_LINE&t;0x00
DECL|macro|CS4231_MIXS_AUX1
mdefine_line|#define CS4231_MIXS_AUX1&t;0x40
DECL|macro|CS4231_MIXS_MIC
mdefine_line|#define CS4231_MIXS_MIC&t;&t;0x80
DECL|macro|CS4231_MIXS_ALL
mdefine_line|#define CS4231_MIXS_ALL&t;&t;0xc0
multiline_comment|/* definitions for clock and data format register - CS4231_PLAYBK_FORMAT */
DECL|macro|CS4231_LINEAR_8
mdefine_line|#define CS4231_LINEAR_8&t;&t;0x00&t;/* 8-bit unsigned data */
DECL|macro|CS4231_ALAW_8
mdefine_line|#define CS4231_ALAW_8&t;&t;0x60&t;/* 8-bit A-law companded */
DECL|macro|CS4231_ULAW_8
mdefine_line|#define CS4231_ULAW_8&t;&t;0x20&t;/* 8-bit U-law companded */
DECL|macro|CS4231_LINEAR_16
mdefine_line|#define CS4231_LINEAR_16&t;0x40&t;/* 16-bit twos complement data - little endian */
DECL|macro|CS4231_LINEAR_16_BIG
mdefine_line|#define CS4231_LINEAR_16_BIG&t;0xc0&t;/* 16-bit twos complement data - big endian */
DECL|macro|CS4231_ADPCM_16
mdefine_line|#define CS4231_ADPCM_16&t;&t;0xa0&t;/* 16-bit ADPCM */
DECL|macro|CS4231_STEREO
mdefine_line|#define CS4231_STEREO&t;&t;0x10&t;/* stereo mode */
multiline_comment|/* bits 3-1 define frequency divisor */
DECL|macro|CS4231_XTAL1
mdefine_line|#define CS4231_XTAL1&t;&t;0x00&t;/* 24.576 crystal */
DECL|macro|CS4231_XTAL2
mdefine_line|#define CS4231_XTAL2&t;&t;0x01&t;/* 16.9344 crystal */
multiline_comment|/* definitions for interface control register - CS4231_IFACE_CTRL */
DECL|macro|CS4231_RECORD_PIO
mdefine_line|#define CS4231_RECORD_PIO&t;0x80&t;/* record PIO enable */
DECL|macro|CS4231_PLAYBACK_PIO
mdefine_line|#define CS4231_PLAYBACK_PIO&t;0x40&t;/* playback PIO enable */
DECL|macro|CS4231_CALIB_MODE
mdefine_line|#define CS4231_CALIB_MODE&t;0x18&t;/* calibration mode bits */
DECL|macro|CS4231_AUTOCALIB
mdefine_line|#define CS4231_AUTOCALIB&t;0x08&t;/* auto calibrate */
DECL|macro|CS4231_SINGLE_DMA
mdefine_line|#define CS4231_SINGLE_DMA&t;0x04&t;/* use single DMA channel */
DECL|macro|CS4231_RECORD_ENABLE
mdefine_line|#define CS4231_RECORD_ENABLE&t;0x02&t;/* record enable */
DECL|macro|CS4231_PLAYBACK_ENABLE
mdefine_line|#define CS4231_PLAYBACK_ENABLE&t;0x01&t;/* playback enable */
multiline_comment|/* definitions for pin control register - CS4231_PIN_CTRL */
DECL|macro|CS4231_IRQ_ENABLE
mdefine_line|#define CS4231_IRQ_ENABLE&t;0x02&t;/* enable IRQ */
DECL|macro|CS4231_XCTL1
mdefine_line|#define CS4231_XCTL1&t;&t;0x40&t;/* external control #1 */
DECL|macro|CS4231_XCTL0
mdefine_line|#define CS4231_XCTL0&t;&t;0x80&t;/* external control #0 */
multiline_comment|/* definitions for test and init register - CS4231_TEST_INIT */
DECL|macro|CS4231_CALIB_IN_PROGRESS
mdefine_line|#define CS4231_CALIB_IN_PROGRESS 0x20&t;/* auto calibrate in progress */
DECL|macro|CS4231_DMA_REQUEST
mdefine_line|#define CS4231_DMA_REQUEST&t;0x10&t;/* DMA request in progress */
multiline_comment|/* definitions for misc control register - CS4231_MISC_INFO */
DECL|macro|CS4231_MODE2
mdefine_line|#define CS4231_MODE2&t;&t;0x40&t;/* MODE 2 */
DECL|macro|CS4231_IW_MODE3
mdefine_line|#define CS4231_IW_MODE3&t;&t;0x6c&t;/* MODE 3 - InterWave enhanced mode */
DECL|macro|CS4231_4236_MODE3
mdefine_line|#define CS4231_4236_MODE3&t;0xe0&t;/* MODE 3 - CS4236+ enhanced mode */
multiline_comment|/* definitions for alternate feature 1 register - CS4231_ALT_FEATURE_1 */
DECL|macro|CS4231_DACZ
mdefine_line|#define&t;CS4231_DACZ&t;&t;0x01&t;/* zero DAC when underrun */
DECL|macro|CS4231_TIMER_ENABLE
mdefine_line|#define CS4231_TIMER_ENABLE&t;0x40&t;/* codec timer enable */
DECL|macro|CS4231_OLB
mdefine_line|#define CS4231_OLB&t;&t;0x80&t;/* output level bit */
multiline_comment|/* definitions for Extended Registers - CS4236+ */
DECL|macro|CS4236_REG
mdefine_line|#define CS4236_REG(i23val)&t;(((i23val &lt;&lt; 2) &amp; 0x10) | ((i23val &gt;&gt; 4) &amp; 0x0f))
DECL|macro|CS4236_I23VAL
mdefine_line|#define CS4236_I23VAL(reg)&t;((((reg)&amp;0xf) &lt;&lt; 4) | (((reg)&amp;0x10) &gt;&gt; 2) | 0x8)
DECL|macro|CS4236_LEFT_LINE
mdefine_line|#define CS4236_LEFT_LINE&t;0x08&t;/* left LINE alternate volume */
DECL|macro|CS4236_RIGHT_LINE
mdefine_line|#define CS4236_RIGHT_LINE&t;0x18&t;/* right LINE alternate volume */
DECL|macro|CS4236_LEFT_MIC
mdefine_line|#define CS4236_LEFT_MIC&t;&t;0x28&t;/* left MIC volume */
DECL|macro|CS4236_RIGHT_MIC
mdefine_line|#define CS4236_RIGHT_MIC&t;0x38&t;/* right MIC volume */
DECL|macro|CS4236_LEFT_MIX_CTRL
mdefine_line|#define CS4236_LEFT_MIX_CTRL&t;0x48&t;/* synthesis and left input mixer control */
DECL|macro|CS4236_RIGHT_MIX_CTRL
mdefine_line|#define CS4236_RIGHT_MIX_CTRL&t;0x58&t;/* right input mixer control */
DECL|macro|CS4236_LEFT_FM
mdefine_line|#define CS4236_LEFT_FM&t;&t;0x68&t;/* left FM volume */
DECL|macro|CS4236_RIGHT_FM
mdefine_line|#define CS4236_RIGHT_FM&t;&t;0x78&t;/* right FM volume */
DECL|macro|CS4236_LEFT_DSP
mdefine_line|#define CS4236_LEFT_DSP&t;&t;0x88&t;/* left DSP serial port volume */
DECL|macro|CS4236_RIGHT_DSP
mdefine_line|#define CS4236_RIGHT_DSP&t;0x98&t;/* right DSP serial port volume */
DECL|macro|CS4236_RIGHT_LOOPBACK
mdefine_line|#define CS4236_RIGHT_LOOPBACK&t;0xa8&t;/* right loopback monitor volume */
DECL|macro|CS4236_DAC_MUTE
mdefine_line|#define CS4236_DAC_MUTE&t;&t;0xb8&t;/* DAC mute and IFSE enable */
DECL|macro|CS4236_ADC_RATE
mdefine_line|#define CS4236_ADC_RATE&t;&t;0xc8&t;/* indenpendent ADC sample frequency */
DECL|macro|CS4236_DAC_RATE
mdefine_line|#define CS4236_DAC_RATE&t;&t;0xd8&t;/* indenpendent DAC sample frequency */
DECL|macro|CS4236_LEFT_MASTER
mdefine_line|#define CS4236_LEFT_MASTER&t;0xe8&t;/* left master digital audio volume */
DECL|macro|CS4236_RIGHT_MASTER
mdefine_line|#define CS4236_RIGHT_MASTER&t;0xf8&t;/* right master digital audio volume */
DECL|macro|CS4236_LEFT_WAVE
mdefine_line|#define CS4236_LEFT_WAVE&t;0x0c&t;/* left wavetable serial port volume */
DECL|macro|CS4236_RIGHT_WAVE
mdefine_line|#define CS4236_RIGHT_WAVE&t;0x1c&t;/* right wavetable serial port volume */
DECL|macro|CS4236_VERSION
mdefine_line|#define CS4236_VERSION&t;&t;0x9c&t;/* chip version and ID */
multiline_comment|/* defines for codec.mode */
DECL|macro|CS4231_MODE_NONE
mdefine_line|#define CS4231_MODE_NONE&t;0x0000
DECL|macro|CS4231_MODE_PLAY
mdefine_line|#define CS4231_MODE_PLAY&t;0x0001
DECL|macro|CS4231_MODE_RECORD
mdefine_line|#define CS4231_MODE_RECORD&t;0x0002
DECL|macro|CS4231_MODE_TIMER
mdefine_line|#define CS4231_MODE_TIMER&t;0x0004
DECL|macro|CS4231_MODE_OPEN
mdefine_line|#define CS4231_MODE_OPEN&t;(CS4231_MODE_PLAY|CS4231_MODE_RECORD|CS4231_MODE_TIMER)
multiline_comment|/* defines for codec.hardware */
DECL|macro|CS4231_HW_DETECT
mdefine_line|#define CS4231_HW_DETECT        0x0000&t;/* let CS4231 driver detect chip */
DECL|macro|CS4231_HW_DETECT3
mdefine_line|#define CS4231_HW_DETECT3&t;0x0001&t;/* allow mode 3 */
DECL|macro|CS4231_HW_TYPE_MASK
mdefine_line|#define CS4231_HW_TYPE_MASK&t;0xff00&t;/* type mask */
DECL|macro|CS4231_HW_CS4231_MASK
mdefine_line|#define CS4231_HW_CS4231_MASK   0x0100&t;/* CS4231 serie */
DECL|macro|CS4231_HW_CS4231
mdefine_line|#define CS4231_HW_CS4231        0x0100&t;/* CS4231 chip */
DECL|macro|CS4231_HW_CS4231A
mdefine_line|#define CS4231_HW_CS4231A       0x0101&t;/* CS4231A chip */
DECL|macro|CS4231_HW_CS4232_MASK
mdefine_line|#define CS4231_HW_CS4232_MASK   0x0200&t;/* CS4232 serie (has control ports) */
DECL|macro|CS4231_HW_CS4232
mdefine_line|#define CS4231_HW_CS4232        0x0200&t;/* CS4232 */
DECL|macro|CS4231_HW_CS4232A
mdefine_line|#define CS4231_HW_CS4232A       0x0201&t;/* CS4232A */
DECL|macro|CS4231_HW_CS4236
mdefine_line|#define CS4231_HW_CS4236&t;0x0202&t;/* CS4236 */
DECL|macro|CS4231_HW_CS4236B_MASK
mdefine_line|#define CS4231_HW_CS4236B_MASK&t;0x0400&t;/* CS4236B serie (has extended control regs) */
DECL|macro|CS4231_HW_CS4235
mdefine_line|#define CS4231_HW_CS4235&t;0x0400&t;/* CS4235 - Crystal Clear (tm) stereo enhancement */
DECL|macro|CS4231_HW_CS4236B
mdefine_line|#define CS4231_HW_CS4236B       0x0401&t;/* CS4236B */
DECL|macro|CS4231_HW_CS4237B
mdefine_line|#define CS4231_HW_CS4237B       0x0402&t;/* CS4237B - SRS 3D */
DECL|macro|CS4231_HW_CS4238B
mdefine_line|#define CS4231_HW_CS4238B&t;0x0403&t;/* CS4238B - QSOUND 3D */
DECL|macro|CS4231_HW_CS4239
mdefine_line|#define CS4231_HW_CS4239&t;0x0404&t;/* CS4239 - Crystal Clear (tm) stereo enhancement */
multiline_comment|/* compatible, but clones */
DECL|macro|CS4231_HW_INTERWAVE
mdefine_line|#define CS4231_HW_INTERWAVE     0x1000&t;/* InterWave chip */
DECL|macro|CS4231_HW_OPL3SA2
mdefine_line|#define CS4231_HW_OPL3SA2       0x1001&t;/* OPL3-SA2 chip */
multiline_comment|/* defines for codec.hwshare */
DECL|macro|CS4231_HWSHARE_IRQ
mdefine_line|#define CS4231_HWSHARE_IRQ&t;(1&lt;&lt;0)
DECL|macro|CS4231_HWSHARE_DMA1
mdefine_line|#define CS4231_HWSHARE_DMA1&t;(1&lt;&lt;1)
DECL|macro|CS4231_HWSHARE_DMA2
mdefine_line|#define CS4231_HWSHARE_DMA2&t;(1&lt;&lt;2)
DECL|typedef|cs4231_t
r_typedef
r_struct
id|_snd_cs4231
id|cs4231_t
suffix:semicolon
DECL|struct|_snd_cs4231
r_struct
id|_snd_cs4231
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* base i/o port */
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|cport
r_int
r_int
id|cport
suffix:semicolon
multiline_comment|/* control base i/o port (CS4236) */
DECL|member|res_cport
r_struct
id|resource
op_star
id|res_cport
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ line */
DECL|member|dma1
r_int
id|dma1
suffix:semicolon
multiline_comment|/* playback DMA */
DECL|member|dma2
r_int
id|dma2
suffix:semicolon
multiline_comment|/* record DMA */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* version of CODEC chip */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* see to CS4231_MODE_XXXX */
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
multiline_comment|/* see to CS4231_HW_XXXX */
DECL|member|hwshare
r_int
r_int
id|hwshare
suffix:semicolon
multiline_comment|/* shared resources */
DECL|member|single_dma
r_int
r_int
id|single_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* forced single DMA mode (GUS 16-bit daughter board) or dma1 == dma2 */
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
DECL|member|timer
id|snd_timer_t
op_star
id|timer
suffix:semicolon
DECL|member|image
r_int
r_char
id|image
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* registers image */
DECL|member|eimage
r_int
r_char
id|eimage
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* extended registers image */
DECL|member|cimage
r_int
r_char
id|cimage
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* control registers image */
DECL|member|mce_bit
r_int
id|mce_bit
suffix:semicolon
DECL|member|calibrate_mute
r_int
id|calibrate_mute
suffix:semicolon
DECL|member|sw_3d_bit
r_int
id|sw_3d_bit
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
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|mce_mutex
r_struct
id|semaphore
id|mce_mutex
suffix:semicolon
DECL|member|open_mutex
r_struct
id|semaphore
id|open_mutex
suffix:semicolon
DECL|member|rate_constraint
r_int
(paren
op_star
id|rate_constraint
)paren
(paren
id|snd_pcm_runtime_t
op_star
id|runtime
)paren
suffix:semicolon
DECL|member|set_playback_format
r_void
(paren
op_star
id|set_playback_format
)paren
(paren
id|cs4231_t
op_star
id|chip
comma
id|snd_pcm_hw_params_t
op_star
id|hw_params
comma
r_int
r_char
id|pdfr
)paren
suffix:semicolon
DECL|member|set_capture_format
r_void
(paren
op_star
id|set_capture_format
)paren
(paren
id|cs4231_t
op_star
id|chip
comma
id|snd_pcm_hw_params_t
op_star
id|hw_params
comma
r_int
r_char
id|cdfr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|member|pm_dev
r_struct
id|pm_dev
op_star
id|pm_dev
suffix:semicolon
DECL|member|suspend
r_void
(paren
op_star
id|suspend
)paren
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#endif
DECL|member|dma_private_data
r_void
op_star
id|dma_private_data
suffix:semicolon
DECL|member|claim_dma
r_int
(paren
op_star
id|claim_dma
)paren
(paren
id|cs4231_t
op_star
id|chip
comma
r_void
op_star
id|dma_private_data
comma
r_int
id|dma
)paren
suffix:semicolon
DECL|member|release_dma
r_int
(paren
op_star
id|release_dma
)paren
(paren
id|cs4231_t
op_star
id|chip
comma
r_void
op_star
id|dma_private_data
comma
r_int
id|dma
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* exported functions */
r_void
id|snd_cs4231_out
c_func
(paren
id|cs4231_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
r_char
id|snd_cs4231_in
c_func
(paren
id|cs4231_t
op_star
id|chip
comma
r_int
r_char
id|reg
)paren
suffix:semicolon
r_void
id|snd_cs4231_outm
c_func
(paren
id|cs4231_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_void
id|snd_cs4236_ext_out
c_func
(paren
id|cs4231_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
r_char
id|snd_cs4236_ext_in
c_func
(paren
id|cs4231_t
op_star
id|chip
comma
r_int
r_char
id|reg
)paren
suffix:semicolon
r_void
id|snd_cs4231_mce_up
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|snd_cs4231_mce_down
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|snd_cs4231_interrupt
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
r_const
r_char
op_star
id|snd_cs4231_chip_id
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_cs4231_create
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
r_int
id|cport
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
r_int
r_int
id|hardware
comma
r_int
r_int
id|hwshare
comma
id|cs4231_t
op_star
op_star
id|rchip
)paren
suffix:semicolon
r_int
id|snd_cs4231_pcm
c_func
(paren
id|cs4231_t
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
id|snd_cs4231_timer
c_func
(paren
id|cs4231_t
op_star
id|chip
comma
r_int
id|device
comma
id|snd_timer_t
op_star
op_star
id|rtimer
)paren
suffix:semicolon
r_int
id|snd_cs4231_mixer
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_cs4236_create
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
r_int
id|cport
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
r_int
r_int
id|hardware
comma
r_int
r_int
id|hwshare
comma
id|cs4231_t
op_star
op_star
id|rchip
)paren
suffix:semicolon
r_int
id|snd_cs4236_pcm
c_func
(paren
id|cs4231_t
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
id|snd_cs4236_mixer
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
multiline_comment|/*&n; *  mixer library&n; */
DECL|macro|CS4231_SINGLE
mdefine_line|#define CS4231_SINGLE(xname, xindex, reg, shift, mask, invert) &bslash;&n;{ iface: SNDRV_CTL_ELEM_IFACE_MIXER, name: xname, index: xindex, &bslash;&n;  info: snd_cs4231_info_single, &bslash;&n;  get: snd_cs4231_get_single, put: snd_cs4231_put_single, &bslash;&n;  private_value: reg | (shift &lt;&lt; 8) | (mask &lt;&lt; 16) | (invert &lt;&lt; 24) }
r_int
id|snd_cs4231_info_single
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
suffix:semicolon
r_int
id|snd_cs4231_get_single
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
r_int
id|snd_cs4231_put_single
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|macro|CS4231_DOUBLE
mdefine_line|#define CS4231_DOUBLE(xname, xindex, left_reg, right_reg, shift_left, shift_right, mask, invert) &bslash;&n;{ iface: SNDRV_CTL_ELEM_IFACE_MIXER, name: xname, index: xindex, &bslash;&n;  info: snd_cs4231_info_double, &bslash;&n;  get: snd_cs4231_get_double, put: snd_cs4231_put_double, &bslash;&n;  private_value: left_reg | (right_reg &lt;&lt; 8) | (shift_left &lt;&lt; 16) | (shift_right &lt;&lt; 19) | (mask &lt;&lt; 24) | (invert &lt;&lt; 22) }
r_int
id|snd_cs4231_info_double
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
suffix:semicolon
r_int
id|snd_cs4231_get_double
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
r_int
id|snd_cs4231_put_double
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
r_void
id|snd_cs4231_debug
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_CS4231_H */
eof
