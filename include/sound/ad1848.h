macro_line|#ifndef __SOUND_AD1848_H
DECL|macro|__SOUND_AD1848_H
mdefine_line|#define __SOUND_AD1848_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Definitions for AD1847/AD1848/CS4248 chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;control.h&quot;
macro_line|#include &quot;pcm.h&quot;
multiline_comment|/* IO ports */
DECL|macro|AD1848P
mdefine_line|#define AD1848P( codec, x ) ( (chip) -&gt; port + c_d_c_AD1848##x )
DECL|macro|c_d_c_AD1848REGSEL
mdefine_line|#define c_d_c_AD1848REGSEL&t;0
DECL|macro|c_d_c_AD1848REG
mdefine_line|#define c_d_c_AD1848REG&t;&t;1
DECL|macro|c_d_c_AD1848STATUS
mdefine_line|#define c_d_c_AD1848STATUS&t;2
DECL|macro|c_d_c_AD1848PIO
mdefine_line|#define c_d_c_AD1848PIO&t;&t;3
multiline_comment|/* codec registers */
DECL|macro|AD1848_LEFT_INPUT
mdefine_line|#define AD1848_LEFT_INPUT&t;0x00&t;/* left input control */
DECL|macro|AD1848_RIGHT_INPUT
mdefine_line|#define AD1848_RIGHT_INPUT&t;0x01&t;/* right input control */
DECL|macro|AD1848_AUX1_LEFT_INPUT
mdefine_line|#define AD1848_AUX1_LEFT_INPUT&t;0x02&t;/* left AUX1 input control */
DECL|macro|AD1848_AUX1_RIGHT_INPUT
mdefine_line|#define AD1848_AUX1_RIGHT_INPUT&t;0x03&t;/* right AUX1 input control */
DECL|macro|AD1848_AUX2_LEFT_INPUT
mdefine_line|#define AD1848_AUX2_LEFT_INPUT&t;0x04&t;/* left AUX2 input control */
DECL|macro|AD1848_AUX2_RIGHT_INPUT
mdefine_line|#define AD1848_AUX2_RIGHT_INPUT&t;0x05&t;/* right AUX2 input control */
DECL|macro|AD1848_LEFT_OUTPUT
mdefine_line|#define AD1848_LEFT_OUTPUT&t;0x06&t;/* left output control register */
DECL|macro|AD1848_RIGHT_OUTPUT
mdefine_line|#define AD1848_RIGHT_OUTPUT&t;0x07&t;/* right output control register */
DECL|macro|AD1848_DATA_FORMAT
mdefine_line|#define AD1848_DATA_FORMAT&t;0x08&t;/* clock and data format - playback/capture - bits 7-0 MCE */
DECL|macro|AD1848_IFACE_CTRL
mdefine_line|#define AD1848_IFACE_CTRL&t;0x09&t;/* interface control - bits 7-2 MCE */
DECL|macro|AD1848_PIN_CTRL
mdefine_line|#define AD1848_PIN_CTRL&t;&t;0x0a&t;/* pin control */
DECL|macro|AD1848_TEST_INIT
mdefine_line|#define AD1848_TEST_INIT&t;0x0b&t;/* test and initialization */
DECL|macro|AD1848_MISC_INFO
mdefine_line|#define AD1848_MISC_INFO&t;0x0c&t;/* miscellaneaous information */
DECL|macro|AD1848_LOOPBACK
mdefine_line|#define AD1848_LOOPBACK&t;&t;0x0d&t;/* loopback control */
DECL|macro|AD1848_DATA_UPR_CNT
mdefine_line|#define AD1848_DATA_UPR_CNT&t;0x0e&t;/* playback/capture upper base count */
DECL|macro|AD1848_DATA_LWR_CNT
mdefine_line|#define AD1848_DATA_LWR_CNT&t;0x0f&t;/* playback/capture lower base count */
multiline_comment|/* definitions for codec register select port - CODECP( REGSEL ) */
DECL|macro|AD1848_INIT
mdefine_line|#define AD1848_INIT&t;&t;0x80&t;/* CODEC is initializing */
DECL|macro|AD1848_MCE
mdefine_line|#define AD1848_MCE&t;&t;0x40&t;/* mode change enable */
DECL|macro|AD1848_TRD
mdefine_line|#define AD1848_TRD&t;&t;0x20&t;/* transfer request disable */
multiline_comment|/* definitions for codec status register - CODECP( STATUS ) */
DECL|macro|AD1848_GLOBALIRQ
mdefine_line|#define AD1848_GLOBALIRQ&t;0x01&t;/* IRQ is active */
multiline_comment|/* definitions for AD1848_LEFT_INPUT and AD1848_RIGHT_INPUT registers */
DECL|macro|AD1848_ENABLE_MIC_GAIN
mdefine_line|#define AD1848_ENABLE_MIC_GAIN&t;0x20
DECL|macro|AD1848_MIXS_LINE1
mdefine_line|#define AD1848_MIXS_LINE1&t;0x00
DECL|macro|AD1848_MIXS_AUX1
mdefine_line|#define AD1848_MIXS_AUX1&t;0x40
DECL|macro|AD1848_MIXS_LINE2
mdefine_line|#define AD1848_MIXS_LINE2&t;0x80
DECL|macro|AD1848_MIXS_ALL
mdefine_line|#define AD1848_MIXS_ALL&t;&t;0xc0
multiline_comment|/* definitions for clock and data format register - AD1848_PLAYBK_FORMAT */
DECL|macro|AD1848_LINEAR_8
mdefine_line|#define AD1848_LINEAR_8&t;&t;0x00&t;/* 8-bit unsigned data */
DECL|macro|AD1848_ALAW_8
mdefine_line|#define AD1848_ALAW_8&t;&t;0x60&t;/* 8-bit A-law companded */
DECL|macro|AD1848_ULAW_8
mdefine_line|#define AD1848_ULAW_8&t;&t;0x20&t;/* 8-bit U-law companded */
DECL|macro|AD1848_LINEAR_16
mdefine_line|#define AD1848_LINEAR_16&t;0x40&t;/* 16-bit twos complement data - little endian */
DECL|macro|AD1848_STEREO
mdefine_line|#define AD1848_STEREO&t;&t;0x10&t;/* stereo mode */
multiline_comment|/* bits 3-1 define frequency divisor */
DECL|macro|AD1848_XTAL1
mdefine_line|#define AD1848_XTAL1&t;&t;0x00&t;/* 24.576 crystal */
DECL|macro|AD1848_XTAL2
mdefine_line|#define AD1848_XTAL2&t;&t;0x01&t;/* 16.9344 crystal */
multiline_comment|/* definitions for interface control register - AD1848_IFACE_CTRL */
DECL|macro|AD1848_CAPTURE_PIO
mdefine_line|#define AD1848_CAPTURE_PIO&t;0x80&t;/* capture PIO enable */
DECL|macro|AD1848_PLAYBACK_PIO
mdefine_line|#define AD1848_PLAYBACK_PIO&t;0x40&t;/* playback PIO enable */
DECL|macro|AD1848_CALIB_MODE
mdefine_line|#define AD1848_CALIB_MODE&t;0x18&t;/* calibration mode bits */
DECL|macro|AD1848_AUTOCALIB
mdefine_line|#define AD1848_AUTOCALIB&t;0x08&t;/* auto calibrate */
DECL|macro|AD1848_SINGLE_DMA
mdefine_line|#define AD1848_SINGLE_DMA&t;0x04&t;/* use single DMA channel */
DECL|macro|AD1848_CAPTURE_ENABLE
mdefine_line|#define AD1848_CAPTURE_ENABLE&t;0x02&t;/* capture enable */
DECL|macro|AD1848_PLAYBACK_ENABLE
mdefine_line|#define AD1848_PLAYBACK_ENABLE&t;0x01&t;/* playback enable */
multiline_comment|/* definitions for pin control register - AD1848_PIN_CTRL */
DECL|macro|AD1848_IRQ_ENABLE
mdefine_line|#define AD1848_IRQ_ENABLE&t;0x02&t;/* enable IRQ */
DECL|macro|AD1848_XCTL1
mdefine_line|#define AD1848_XCTL1&t;&t;0x40&t;/* external control #1 */
DECL|macro|AD1848_XCTL0
mdefine_line|#define AD1848_XCTL0&t;&t;0x80&t;/* external control #0 */
multiline_comment|/* definitions for test and init register - AD1848_TEST_INIT */
DECL|macro|AD1848_CALIB_IN_PROGRESS
mdefine_line|#define AD1848_CALIB_IN_PROGRESS 0x20&t;/* auto calibrate in progress */
DECL|macro|AD1848_DMA_REQUEST
mdefine_line|#define AD1848_DMA_REQUEST&t;0x10&t;/* DMA request in progress */
multiline_comment|/* defines for codec.mode */
DECL|macro|AD1848_MODE_NONE
mdefine_line|#define AD1848_MODE_NONE&t;0x0000
DECL|macro|AD1848_MODE_PLAY
mdefine_line|#define AD1848_MODE_PLAY&t;0x0001
DECL|macro|AD1848_MODE_CAPTURE
mdefine_line|#define AD1848_MODE_CAPTURE&t;0x0002
DECL|macro|AD1848_MODE_TIMER
mdefine_line|#define AD1848_MODE_TIMER&t;0x0004
DECL|macro|AD1848_MODE_OPEN
mdefine_line|#define AD1848_MODE_OPEN&t;(AD1848_MODE_PLAY|AD1848_MODE_CAPTURE|AD1848_MODE_TIMER)
DECL|macro|AD1848_MODE_RUNNING
mdefine_line|#define AD1848_MODE_RUNNING&t;0x0010
multiline_comment|/* defines for codec.hardware */
DECL|macro|AD1848_HW_DETECT
mdefine_line|#define AD1848_HW_DETECT&t;0x0000&t;/* let AD1848 driver detect chip */
DECL|macro|AD1848_HW_AD1847
mdefine_line|#define AD1848_HW_AD1847&t;0x0001&t;/* AD1847 chip */
DECL|macro|AD1848_HW_AD1848
mdefine_line|#define AD1848_HW_AD1848&t;0x0002&t;/* AD1848 chip */
DECL|macro|AD1848_HW_CS4248
mdefine_line|#define AD1848_HW_CS4248&t;0x0003&t;/* CS4248 chip */
DECL|macro|AD1848_HW_CMI8330
mdefine_line|#define AD1848_HW_CMI8330&t;0x0004&t;/* CMI8330 chip */
DECL|struct|_snd_ad1848
r_struct
id|_snd_ad1848
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* i/o port */
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
multiline_comment|/* IRQ line */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* data DMA */
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
multiline_comment|/* see to AD1848_MODE_XXXX */
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
multiline_comment|/* see to AD1848_HW_XXXX */
DECL|member|single_dma
r_int
r_int
id|single_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* forced single DMA mode (GUS 16-bit daughter board) or dma1 == dma2 */
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
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|image
r_int
r_char
id|image
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* SGalaxy needs an access to extended registers */
DECL|member|mce_bit
r_int
id|mce_bit
suffix:semicolon
DECL|member|calibrate_mute
r_int
id|calibrate_mute
suffix:semicolon
DECL|member|dma_size
r_int
id|dma_size
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|open_mutex
r_struct
id|semaphore
id|open_mutex
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|ad1848_t
r_typedef
r_struct
id|_snd_ad1848
id|ad1848_t
suffix:semicolon
multiline_comment|/* exported functions */
r_void
id|snd_ad1848_out
c_func
(paren
id|ad1848_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|value
)paren
suffix:semicolon
r_void
id|snd_ad1848_dout
c_func
(paren
id|ad1848_t
op_star
id|chip
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|value
)paren
suffix:semicolon
r_int
r_char
id|snd_ad1848_in
c_func
(paren
id|ad1848_t
op_star
id|chip
comma
r_int
r_char
id|reg
)paren
suffix:semicolon
r_void
id|snd_ad1848_mce_up
c_func
(paren
id|ad1848_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|snd_ad1848_mce_down
c_func
(paren
id|ad1848_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_ad1848_create
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
id|dma
comma
r_int
r_int
id|hardware
comma
id|ad1848_t
op_star
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_ad1848_pcm
c_func
(paren
id|ad1848_t
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
id|snd_ad1848_mixer
c_func
(paren
id|ad1848_t
op_star
id|chip
)paren
suffix:semicolon
r_void
id|snd_ad1848_interrupt
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
DECL|macro|AD1848_SINGLE
mdefine_line|#define AD1848_SINGLE(xname, xindex, reg, shift, mask, invert) &bslash;&n;{ iface: SNDRV_CTL_ELEM_IFACE_MIXER, name: xname, index: xindex, &bslash;&n;  info: snd_ad1848_info_single, &bslash;&n;  get: snd_ad1848_get_single, put: snd_ad1848_put_single, &bslash;&n;  private_value: reg | (shift &lt;&lt; 8) | (mask &lt;&lt; 16) | (invert &lt;&lt; 24) }
r_int
id|snd_ad1848_info_single
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
id|snd_ad1848_get_single
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
id|snd_ad1848_put_single
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
DECL|macro|AD1848_DOUBLE
mdefine_line|#define AD1848_DOUBLE(xname, xindex, left_reg, right_reg, shift_left, shift_right, mask, invert) &bslash;&n;{ iface: SNDRV_CTL_ELEM_IFACE_MIXER, name: xname, index: xindex, &bslash;&n;  info: snd_ad1848_info_double, &bslash;&n;  get: snd_ad1848_get_double, put: snd_ad1848_put_double, &bslash;&n;  private_value: left_reg | (right_reg &lt;&lt; 8) | (shift_left &lt;&lt; 16) | (shift_right &lt;&lt; 19) | (mask &lt;&lt; 24) | (invert &lt;&lt; 22) }
r_int
id|snd_ad1848_info_double
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
id|snd_ad1848_get_double
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
id|snd_ad1848_put_double
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
id|snd_ad1848_debug
c_func
(paren
id|ad1848_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_AD1848_H */
eof
