macro_line|#ifndef __SOUND_ES1688_H
DECL|macro|__SOUND_ES1688_H
mdefine_line|#define __SOUND_ES1688_H
multiline_comment|/*&n; *  Header file for ES488/ES1688&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;control.h&quot;
macro_line|#include &quot;pcm.h&quot;
DECL|macro|ES1688_HW_AUTO
mdefine_line|#define ES1688_HW_AUTO&t;&t;0x0000
DECL|macro|ES1688_HW_688
mdefine_line|#define ES1688_HW_688&t;&t;0x0001
DECL|macro|ES1688_HW_1688
mdefine_line|#define ES1688_HW_1688&t;&t;0x0002
DECL|struct|_snd_es1688
r_struct
id|_snd_es1688
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* port of ESS chip */
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|mpu_port
r_int
r_int
id|mpu_port
suffix:semicolon
multiline_comment|/* MPU-401 port of ESS chip */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ number of ESS chip */
DECL|member|mpu_irq
r_int
id|mpu_irq
suffix:semicolon
multiline_comment|/* MPU IRQ */
DECL|member|dma8
r_int
id|dma8
suffix:semicolon
multiline_comment|/* 8-bit DMA */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* version of ESS chip */
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
multiline_comment|/* see to ES1688_HW_XXXX */
DECL|member|trigger_value
r_int
r_int
id|trigger_value
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|dma_size
r_int
r_int
id|dma_size
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
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|mixer_lock
id|spinlock_t
id|mixer_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|es1688_t
r_typedef
r_struct
id|_snd_es1688
id|es1688_t
suffix:semicolon
multiline_comment|/* I/O ports */
DECL|macro|ES1688P
mdefine_line|#define ES1688P(codec, x) ((codec)-&gt;port + e_s_s_ESS1688##x)
DECL|macro|e_s_s_ESS1688RESET
mdefine_line|#define e_s_s_ESS1688RESET&t;0x6
DECL|macro|e_s_s_ESS1688READ
mdefine_line|#define e_s_s_ESS1688READ&t;0xa
DECL|macro|e_s_s_ESS1688WRITE
mdefine_line|#define e_s_s_ESS1688WRITE&t;0xc
DECL|macro|e_s_s_ESS1688COMMAND
mdefine_line|#define e_s_s_ESS1688COMMAND&t;0xc
DECL|macro|e_s_s_ESS1688STATUS
mdefine_line|#define e_s_s_ESS1688STATUS&t;0xc
DECL|macro|e_s_s_ESS1688DATA_AVAIL
mdefine_line|#define e_s_s_ESS1688DATA_AVAIL&t;0xe
DECL|macro|e_s_s_ESS1688DATA_AVAIL_16
mdefine_line|#define e_s_s_ESS1688DATA_AVAIL_16 0xf
DECL|macro|e_s_s_ESS1688MIXER_ADDR
mdefine_line|#define e_s_s_ESS1688MIXER_ADDR&t;0x4
DECL|macro|e_s_s_ESS1688MIXER_DATA
mdefine_line|#define e_s_s_ESS1688MIXER_DATA&t;0x5
DECL|macro|e_s_s_ESS1688OPL3_LEFT
mdefine_line|#define e_s_s_ESS1688OPL3_LEFT&t;0x0
DECL|macro|e_s_s_ESS1688OPL3_RIGHT
mdefine_line|#define e_s_s_ESS1688OPL3_RIGHT&t;0x2
DECL|macro|e_s_s_ESS1688OPL3_BOTH
mdefine_line|#define e_s_s_ESS1688OPL3_BOTH&t;0x8
DECL|macro|e_s_s_ESS1688ENABLE0
mdefine_line|#define e_s_s_ESS1688ENABLE0&t;0x0
DECL|macro|e_s_s_ESS1688ENABLE1
mdefine_line|#define e_s_s_ESS1688ENABLE1&t;0x9
DECL|macro|e_s_s_ESS1688ENABLE2
mdefine_line|#define e_s_s_ESS1688ENABLE2&t;0xb
DECL|macro|e_s_s_ESS1688INIT1
mdefine_line|#define e_s_s_ESS1688INIT1&t;0x7
DECL|macro|ES1688_DSP_CMD_DMAOFF
mdefine_line|#define ES1688_DSP_CMD_DMAOFF&t;0xd0
DECL|macro|ES1688_DSP_CMD_SPKON
mdefine_line|#define ES1688_DSP_CMD_SPKON&t;0xd1
DECL|macro|ES1688_DSP_CMD_SPKOFF
mdefine_line|#define ES1688_DSP_CMD_SPKOFF&t;0xd3
DECL|macro|ES1688_DSP_CMD_DMAON
mdefine_line|#define ES1688_DSP_CMD_DMAON&t;0xd4
DECL|macro|ES1688_PCM_DEV
mdefine_line|#define ES1688_PCM_DEV&t;&t;0x14
DECL|macro|ES1688_MIC_DEV
mdefine_line|#define ES1688_MIC_DEV&t;&t;0x1a
DECL|macro|ES1688_REC_DEV
mdefine_line|#define ES1688_REC_DEV&t;&t;0x1c
DECL|macro|ES1688_MASTER_DEV
mdefine_line|#define ES1688_MASTER_DEV&t;0x32
DECL|macro|ES1688_FM_DEV
mdefine_line|#define ES1688_FM_DEV&t;&t;0x36
DECL|macro|ES1688_CD_DEV
mdefine_line|#define ES1688_CD_DEV&t;&t;0x38
DECL|macro|ES1688_AUX_DEV
mdefine_line|#define ES1688_AUX_DEV&t;&t;0x3a
DECL|macro|ES1688_SPEAKER_DEV
mdefine_line|#define ES1688_SPEAKER_DEV&t;0x3c
DECL|macro|ES1688_LINE_DEV
mdefine_line|#define ES1688_LINE_DEV&t;&t;0x3e
DECL|macro|ES1688_RECLEV_DEV
mdefine_line|#define ES1688_RECLEV_DEV&t;0xb4
DECL|macro|ES1688_MIXS_MASK
mdefine_line|#define ES1688_MIXS_MASK&t;0x17
DECL|macro|ES1688_MIXS_MIC
mdefine_line|#define ES1688_MIXS_MIC&t;&t;0x00
DECL|macro|ES1688_MIXS_MIC_MASTER
mdefine_line|#define ES1688_MIXS_MIC_MASTER&t;0x01
DECL|macro|ES1688_MIXS_CD
mdefine_line|#define ES1688_MIXS_CD&t;&t;0x02
DECL|macro|ES1688_MIXS_AOUT
mdefine_line|#define ES1688_MIXS_AOUT&t;0x03
DECL|macro|ES1688_MIXS_MIC1
mdefine_line|#define ES1688_MIXS_MIC1&t;0x04
DECL|macro|ES1688_MIXS_REC_MIX
mdefine_line|#define ES1688_MIXS_REC_MIX&t;0x05
DECL|macro|ES1688_MIXS_LINE
mdefine_line|#define ES1688_MIXS_LINE&t;0x06
DECL|macro|ES1688_MIXS_MASTER
mdefine_line|#define ES1688_MIXS_MASTER&t;0x07
DECL|macro|ES1688_MIXS_MUTE
mdefine_line|#define ES1688_MIXS_MUTE&t;0x10
multiline_comment|/*&n;&n; */
r_void
id|snd_es1688_mixer_write
c_func
(paren
id|es1688_t
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
id|snd_es1688_mixer_read
c_func
(paren
id|es1688_t
op_star
id|chip
comma
r_int
r_char
id|reg
)paren
suffix:semicolon
r_void
id|snd_es1688_interrupt
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
id|snd_es1688_create
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
id|mpu_port
comma
r_int
id|irq
comma
r_int
id|mpu_irq
comma
r_int
id|dma8
comma
r_int
r_int
id|hardware
comma
id|es1688_t
op_star
op_star
id|rchip
)paren
suffix:semicolon
r_int
id|snd_es1688_pcm
c_func
(paren
id|es1688_t
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
id|snd_es1688_mixer
c_func
(paren
id|es1688_t
op_star
id|chip
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_ES1688_H */
eof
