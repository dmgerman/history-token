macro_line|#ifndef __SOUND_AC97_CODEC_H
DECL|macro|__SOUND_AC97_CODEC_H
mdefine_line|#define __SOUND_AC97_CODEC_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.1&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;control.h&quot;
macro_line|#include &quot;info.h&quot;
multiline_comment|/*&n; *  AC&squot;97 codec registers&n; */
DECL|macro|AC97_RESET
mdefine_line|#define AC97_RESET&t;&t;0x00&t;/* Reset */
DECL|macro|AC97_MASTER
mdefine_line|#define AC97_MASTER&t;&t;0x02&t;/* Master Volume */
DECL|macro|AC97_HEADPHONE
mdefine_line|#define AC97_HEADPHONE&t;&t;0x04&t;/* Headphone Volume (optional) */
DECL|macro|AC97_MASTER_MONO
mdefine_line|#define AC97_MASTER_MONO&t;0x06&t;/* Master Volume Mono (optional) */
DECL|macro|AC97_MASTER_TONE
mdefine_line|#define AC97_MASTER_TONE&t;0x08&t;/* Master Tone (Bass &amp; Treble) (optional) */
DECL|macro|AC97_PC_BEEP
mdefine_line|#define AC97_PC_BEEP&t;&t;0x0a&t;/* PC Beep Volume (optinal) */
DECL|macro|AC97_PHONE
mdefine_line|#define AC97_PHONE&t;&t;0x0c&t;/* Phone Volume (optional) */
DECL|macro|AC97_MIC
mdefine_line|#define AC97_MIC&t;&t;0x0e&t;/* MIC Volume */
DECL|macro|AC97_LINE
mdefine_line|#define AC97_LINE&t;&t;0x10&t;/* Line In Volume */
DECL|macro|AC97_CD
mdefine_line|#define AC97_CD&t;&t;&t;0x12&t;/* CD Volume */
DECL|macro|AC97_VIDEO
mdefine_line|#define AC97_VIDEO&t;&t;0x14&t;/* Video Volume (optional) */
DECL|macro|AC97_AUX
mdefine_line|#define AC97_AUX&t;&t;0x16&t;/* AUX Volume (optional) */
DECL|macro|AC97_PCM
mdefine_line|#define AC97_PCM&t;&t;0x18&t;/* PCM Volume */
DECL|macro|AC97_REC_SEL
mdefine_line|#define AC97_REC_SEL&t;&t;0x1a&t;/* Record Select */
DECL|macro|AC97_REC_GAIN
mdefine_line|#define AC97_REC_GAIN&t;&t;0x1c&t;/* Record Gain */
DECL|macro|AC97_REC_GAIN_MIC
mdefine_line|#define AC97_REC_GAIN_MIC&t;0x1e&t;/* Record Gain MIC (optional) */
DECL|macro|AC97_GENERAL_PURPOSE
mdefine_line|#define AC97_GENERAL_PURPOSE&t;0x20&t;/* General Purpose (optional) */
DECL|macro|AC97_3D_CONTROL
mdefine_line|#define AC97_3D_CONTROL&t;&t;0x22&t;/* 3D Control (optional) */
DECL|macro|AC97_RESERVED
mdefine_line|#define AC97_RESERVED&t;&t;0x24&t;/* Reserved */
DECL|macro|AC97_POWERDOWN
mdefine_line|#define AC97_POWERDOWN&t;&t;0x26&t;/* Powerdown control / status */
multiline_comment|/* range 0x28-0x3a - AUDIO AC&squot;97 2.0 extensions */
DECL|macro|AC97_EXTENDED_ID
mdefine_line|#define AC97_EXTENDED_ID&t;0x28&t;/* Extended Audio ID */
DECL|macro|AC97_EXTENDED_STATUS
mdefine_line|#define AC97_EXTENDED_STATUS&t;0x2a&t;/* Extended Audio Status */
DECL|macro|AC97_PCM_FRONT_DAC_RATE
mdefine_line|#define AC97_PCM_FRONT_DAC_RATE 0x2c&t;/* PCM Front DAC Rate */
DECL|macro|AC97_PCM_SURR_DAC_RATE
mdefine_line|#define AC97_PCM_SURR_DAC_RATE&t;0x2e&t;/* PCM Surround DAC Rate */
DECL|macro|AC97_PCM_LFE_DAC_RATE
mdefine_line|#define AC97_PCM_LFE_DAC_RATE&t;0x30&t;/* PCM LFE DAC Rate */
DECL|macro|AC97_PCM_LR_ADC_RATE
mdefine_line|#define AC97_PCM_LR_ADC_RATE&t;0x32&t;/* PCM LR DAC Rate */
DECL|macro|AC97_PCM_MIC_ADC_RATE
mdefine_line|#define AC97_PCM_MIC_ADC_RATE&t;0x34&t;/* PCM MIC ADC Rate */
DECL|macro|AC97_CENTER_LFE_MASTER
mdefine_line|#define AC97_CENTER_LFE_MASTER&t;0x36&t;/* Center + LFE Master Volume */
DECL|macro|AC97_SURROUND_MASTER
mdefine_line|#define AC97_SURROUND_MASTER&t;0x38&t;/* Surround (Rear) Master Volume */
DECL|macro|AC97_SPDIF
mdefine_line|#define AC97_SPDIF&t;&t;0x3a&t;/* S/PDIF control */
multiline_comment|/* range 0x3c-0x58 - MODEM */
multiline_comment|/* range 0x5a-0x7b - Vendor Specific */
DECL|macro|AC97_VENDOR_ID1
mdefine_line|#define AC97_VENDOR_ID1&t;&t;0x7c&t;/* Vendor ID1 */
DECL|macro|AC97_VENDOR_ID2
mdefine_line|#define AC97_VENDOR_ID2&t;&t;0x7e&t;/* Vendor ID2 / revision */
multiline_comment|/* extended audio status and control bit defines */
DECL|macro|AC97_EA_VRA
mdefine_line|#define AC97_EA_VRA&t;&t;0x0001&t;/* Variable bit rate enable bit */
DECL|macro|AC97_EA_DRA
mdefine_line|#define AC97_EA_DRA&t;&t;0x0002&t;/* Double-rate audio enable bit */
DECL|macro|AC97_EA_SPDIF
mdefine_line|#define AC97_EA_SPDIF&t;&t;0x0004&t;/* S/PDIF Enable bit */
DECL|macro|AC97_EA_VRM
mdefine_line|#define AC97_EA_VRM&t;&t;0x0008&t;/* Variable bit rate for MIC enable bit */
DECL|macro|AC97_EA_CDAC
mdefine_line|#define AC97_EA_CDAC&t;&t;0x0040&t;/* PCM Center DAC is ready (Read only) */
DECL|macro|AC97_EA_SDAC
mdefine_line|#define AC97_EA_SDAC&t;&t;0x0040&t;/* PCM Surround DACs are ready (Read only) */
DECL|macro|AC97_EA_LDAC
mdefine_line|#define AC97_EA_LDAC&t;&t;0x0080&t;/* PCM LFE DAC is ready (Read only) */
DECL|macro|AC97_EA_MDAC
mdefine_line|#define AC97_EA_MDAC&t;&t;0x0100&t;/* MIC ADC is ready (Read only) */
DECL|macro|AC97_EA_SPCV
mdefine_line|#define AC97_EA_SPCV&t;&t;0x0400&t;/* S/PDIF configuration valid (Read only) */
DECL|macro|AC97_EA_PRI
mdefine_line|#define AC97_EA_PRI&t;&t;0x0800&t;/* Turns the PCM Center DAC off */
DECL|macro|AC97_EA_PRJ
mdefine_line|#define AC97_EA_PRJ&t;&t;0x1000&t;/* Turns the PCM Surround DACs off */
DECL|macro|AC97_EA_PRK
mdefine_line|#define AC97_EA_PRK&t;&t;0x2000&t;/* Turns the PCM LFE DAC off */
DECL|macro|AC97_EA_PRL
mdefine_line|#define AC97_EA_PRL&t;&t;0x4000&t;/* Turns the MIC ADC off */
DECL|macro|AC97_EA_SLOT_MASK
mdefine_line|#define AC97_EA_SLOT_MASK&t;0xffcf&t;/* Mask for slot assignment bits */
DECL|macro|AC97_EA_SPSA_3_4
mdefine_line|#define AC97_EA_SPSA_3_4&t;0x0000&t;/* Slot assigned to 3 &amp; 4 */
DECL|macro|AC97_EA_SPSA_7_8
mdefine_line|#define AC97_EA_SPSA_7_8&t;0x0010&t;/* Slot assigned to 7 &amp; 8 */
DECL|macro|AC97_EA_SPSA_6_9
mdefine_line|#define AC97_EA_SPSA_6_9&t;0x0020&t;/* Slot assigned to 6 &amp; 9 */
DECL|macro|AC97_EA_SPSA_10_11
mdefine_line|#define AC97_EA_SPSA_10_11&t;0x0030&t;/* Slot assigned to 10 &amp; 11 */
multiline_comment|/* S/PDIF control bit defines */
DECL|macro|AC97_SC_PRO
mdefine_line|#define AC97_SC_PRO&t;&t;0x0001&t;/* Professional status */
DECL|macro|AC97_SC_NAUDIO
mdefine_line|#define AC97_SC_NAUDIO&t;&t;0x0002&t;/* Non audio stream */
DECL|macro|AC97_SC_COPY
mdefine_line|#define AC97_SC_COPY&t;&t;0x0004&t;/* Copyright status */
DECL|macro|AC97_SC_PRE
mdefine_line|#define AC97_SC_PRE&t;&t;0x0008&t;/* Preemphasis status */
DECL|macro|AC97_SC_CC_MASK
mdefine_line|#define AC97_SC_CC_MASK&t;&t;0x07f0&t;/* Category Code mask */
DECL|macro|AC97_SC_L
mdefine_line|#define AC97_SC_L&t;&t;0x0800&t;/* Generation Level status */
DECL|macro|AC97_SC_SPSR_MASK
mdefine_line|#define AC97_SC_SPSR_MASK&t;0xcfff&t;/* S/PDIF Sample Rate bits */
DECL|macro|AC97_SC_SPSR_44K
mdefine_line|#define AC97_SC_SPSR_44K&t;0x0000&t;/* Use 44.1kHz Sample rate */
DECL|macro|AC97_SC_SPSR_48K
mdefine_line|#define AC97_SC_SPSR_48K&t;0x2000&t;/* Use 48kHz Sample rate */
DECL|macro|AC97_SC_SPSR_32K
mdefine_line|#define AC97_SC_SPSR_32K&t;0x3000&t;/* Use 32kHz Sample rate */
DECL|macro|AC97_SC_DRS
mdefine_line|#define AC97_SC_DRS&t;&t;0x4000&t;/* Double Rate S/PDIF */
DECL|macro|AC97_SC_V
mdefine_line|#define AC97_SC_V&t;&t;0x8000&t;/* Validity status */
multiline_comment|/* specific - SigmaTel */
DECL|macro|AC97_SIGMATEL_ANALOG
mdefine_line|#define AC97_SIGMATEL_ANALOG&t;0x6c&t;/* Analog Special */
DECL|macro|AC97_SIGMATEL_DAC2INVERT
mdefine_line|#define AC97_SIGMATEL_DAC2INVERT 0x6e
DECL|macro|AC97_SIGMATEL_BIAS1
mdefine_line|#define AC97_SIGMATEL_BIAS1&t;0x70
DECL|macro|AC97_SIGMATEL_BIAS2
mdefine_line|#define AC97_SIGMATEL_BIAS2&t;0x72
DECL|macro|AC97_SIGMATEL_MULTICHN
mdefine_line|#define AC97_SIGMATEL_MULTICHN&t;0x74&t;/* Multi-Channel programming */
DECL|macro|AC97_SIGMATEL_CIC1
mdefine_line|#define AC97_SIGMATEL_CIC1&t;0x76
DECL|macro|AC97_SIGMATEL_CIC2
mdefine_line|#define AC97_SIGMATEL_CIC2&t;0x78
multiline_comment|/* specific - Analog Devices */
DECL|macro|AC97_AD_TEST
mdefine_line|#define AC97_AD_TEST&t;&t;0x5a&t;/* test register */
DECL|macro|AC97_AD_CODEC_CFG
mdefine_line|#define AC97_AD_CODEC_CFG&t;0x70&t;/* codec configuration */
DECL|macro|AC97_AD_JACK_SPDIF
mdefine_line|#define AC97_AD_JACK_SPDIF&t;0x72&t;/* Jack Sense &amp; S/PDIF */
DECL|macro|AC97_AD_SERIAL_CFG
mdefine_line|#define AC97_AD_SERIAL_CFG&t;0x74&t;/* Serial Configuration */
DECL|macro|AC97_AD_MISC
mdefine_line|#define AC97_AD_MISC&t;&t;0x76&t;/* Misc Control Bits */
multiline_comment|/* specific - Cirrus Logic */
DECL|macro|AC97_CSR_ACMODE
mdefine_line|#define AC97_CSR_ACMODE&t;&t;0x5e&t;/* AC Mode Register */
DECL|macro|AC97_CSR_MISC_CRYSTAL
mdefine_line|#define AC97_CSR_MISC_CRYSTAL&t;0x60&t;/* Misc Crystal Control */
DECL|macro|AC97_CSR_SPDIF
mdefine_line|#define AC97_CSR_SPDIF&t;&t;0x68&t;/* S/PDIF Register */
DECL|macro|AC97_CSR_SERIAL
mdefine_line|#define AC97_CSR_SERIAL&t;&t;0x6a&t;/* Serial Port Control */
DECL|macro|AC97_CSR_SPECF_ADDR
mdefine_line|#define AC97_CSR_SPECF_ADDR&t;0x6c&t;/* Special Feature Address */
DECL|macro|AC97_CSR_SPECF_DATA
mdefine_line|#define AC97_CSR_SPECF_DATA&t;0x6e&t;/* Special Feature Data */
DECL|macro|AC97_CSR_BDI_STATUS
mdefine_line|#define AC97_CSR_BDI_STATUS&t;0x7a&t;/* BDI Status */
multiline_comment|/* ac97-&gt;scaps */
DECL|macro|AC97_SCAP_SURROUND_DAC
mdefine_line|#define AC97_SCAP_SURROUND_DAC&t;(1&lt;&lt;0)&t;/* surround L&amp;R DACs are present */
DECL|macro|AC97_SCAP_CENTER_LFE_DAC
mdefine_line|#define AC97_SCAP_CENTER_LFE_DAC (1&lt;&lt;1)&t;/* center and LFE DACs are present */
multiline_comment|/* ac97-&gt;flags */
DECL|macro|AC97_HAS_PC_BEEP
mdefine_line|#define AC97_HAS_PC_BEEP&t;(1&lt;&lt;0)&t;/* force PC Speaker usage */
DECL|macro|AC97_AD_MULTI
mdefine_line|#define AC97_AD_MULTI&t;&t;(1&lt;&lt;1)&t;/* Analog Devices - multi codecs */
DECL|macro|AC97_CS_SPDIF
mdefine_line|#define AC97_CS_SPDIF&t;&t;(1&lt;&lt;2)&t;/* Cirrus Logic uses funky SPDIF */
multiline_comment|/*&n;&n; */
DECL|typedef|ac97_t
r_typedef
r_struct
id|_snd_ac97
id|ac97_t
suffix:semicolon
DECL|struct|_snd_ac97
r_struct
id|_snd_ac97
(brace
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|member|read
r_int
r_int
(paren
op_star
id|read
)paren
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
)paren
suffix:semicolon
DECL|member|wait
r_void
(paren
op_star
id|wait
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
DECL|member|proc_regs_entry
id|snd_info_entry_t
op_star
id|proc_regs_entry
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
multiline_comment|/* --- */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
multiline_comment|/* number of codec: 0 = primary, 1 = secondary */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* physical address of codec [0-3] */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* identification of codec */
DECL|member|caps
r_int
r_int
id|caps
suffix:semicolon
multiline_comment|/* capabilities (register 0) */
DECL|member|ext_id
r_int
r_int
id|ext_id
suffix:semicolon
multiline_comment|/* extended feature identification (register 28) */
DECL|member|scaps
r_int
r_int
id|scaps
suffix:semicolon
multiline_comment|/* driver capabilities */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* specific code */
DECL|member|clock
r_int
r_int
id|clock
suffix:semicolon
multiline_comment|/* AC&squot;97 clock (usually 48000Hz) */
DECL|member|rates_front_dac
r_int
r_int
id|rates_front_dac
suffix:semicolon
DECL|member|rates_surr_dac
r_int
r_int
id|rates_surr_dac
suffix:semicolon
DECL|member|rates_lfe_dac
r_int
r_int
id|rates_lfe_dac
suffix:semicolon
DECL|member|rates_adc
r_int
r_int
id|rates_adc
suffix:semicolon
DECL|member|rates_mic_adc
r_int
r_int
id|rates_mic_adc
suffix:semicolon
DECL|member|spdif_status
r_int
r_int
id|spdif_status
suffix:semicolon
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|0x80
)braket
suffix:semicolon
multiline_comment|/* register cache */
id|bitmap_member
c_func
(paren
id|reg_accessed
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* bit flags */
r_union
(brace
multiline_comment|/* vendor specific code */
r_struct
(brace
DECL|member|unchained
r_int
r_int
id|unchained
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// 0 = C34, 1 = C79, 2 = C69
DECL|member|chained
r_int
r_int
id|chained
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// 0 = C34, 1 = C79, 2 = C69
DECL|member|id
r_int
r_int
id|id
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// codec IDs (lower 16-bit word)
DECL|member|pcmreg
r_int
r_int
id|pcmreg
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// PCM registers
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|member|ad18xx
)brace
id|ad18xx
suffix:semicolon
DECL|member|spec
)brace
id|spec
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_ac97_mixer
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|ac97_t
op_star
id|_ac97
comma
id|ac97_t
op_star
op_star
id|rac97
)paren
suffix:semicolon
r_void
id|snd_ac97_write
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_int
r_int
id|snd_ac97_read
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
)paren
suffix:semicolon
r_void
id|snd_ac97_write_cache
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_int
id|snd_ac97_update
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_int
id|snd_ac97_update_bits
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_int
id|snd_ac97_set_rate
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
id|reg
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_void
id|snd_ac97_suspend
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
r_void
id|snd_ac97_resume
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_AC97_CODEC_H */
eof
