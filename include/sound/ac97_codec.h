macro_line|#ifndef __SOUND_AC97_CODEC_H
DECL|macro|__SOUND_AC97_CODEC_H
mdefine_line|#define __SOUND_AC97_CODEC_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.1&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/bitops.h&gt;
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
mdefine_line|#define AC97_EXTENDED_STATUS&t;0x2a&t;/* Extended Audio Status and Control */
DECL|macro|AC97_PCM_FRONT_DAC_RATE
mdefine_line|#define AC97_PCM_FRONT_DAC_RATE 0x2c&t;/* PCM Front DAC Rate */
DECL|macro|AC97_PCM_SURR_DAC_RATE
mdefine_line|#define AC97_PCM_SURR_DAC_RATE&t;0x2e&t;/* PCM Surround DAC Rate */
DECL|macro|AC97_PCM_LFE_DAC_RATE
mdefine_line|#define AC97_PCM_LFE_DAC_RATE&t;0x30&t;/* PCM LFE DAC Rate */
DECL|macro|AC97_PCM_LR_ADC_RATE
mdefine_line|#define AC97_PCM_LR_ADC_RATE&t;0x32&t;/* PCM LR ADC Rate */
DECL|macro|AC97_PCM_MIC_ADC_RATE
mdefine_line|#define AC97_PCM_MIC_ADC_RATE&t;0x34&t;/* PCM MIC ADC Rate */
DECL|macro|AC97_CENTER_LFE_MASTER
mdefine_line|#define AC97_CENTER_LFE_MASTER&t;0x36&t;/* Center + LFE Master Volume */
DECL|macro|AC97_SURROUND_MASTER
mdefine_line|#define AC97_SURROUND_MASTER&t;0x38&t;/* Surround (Rear) Master Volume */
DECL|macro|AC97_SPDIF
mdefine_line|#define AC97_SPDIF&t;&t;0x3a&t;/* S/PDIF control */
multiline_comment|/* range 0x3c-0x58 - MODEM */
DECL|macro|AC97_EXTENDED_MID
mdefine_line|#define AC97_EXTENDED_MID&t;0x3c&t;/* Extended Modem ID */
DECL|macro|AC97_EXTENDED_MSTATUS
mdefine_line|#define AC97_EXTENDED_MSTATUS&t;0x3e&t;/* Extended Modem Status and Control */
DECL|macro|AC97_LINE1_RATE
mdefine_line|#define AC97_LINE1_RATE&t;&t;0x40&t;/* Line1 DAC/ADC Rate */
DECL|macro|AC97_LINE2_RATE
mdefine_line|#define AC97_LINE2_RATE&t;&t;0x42&t;/* Line2 DAC/ADC Rate */
DECL|macro|AC97_HANDSET_RATE
mdefine_line|#define AC97_HANDSET_RATE&t;0x44&t;/* Handset DAC/ADC Rate */
DECL|macro|AC97_LINE1_LEVEL
mdefine_line|#define AC97_LINE1_LEVEL&t;0x46&t;/* Line1 DAC/ADC Level */
DECL|macro|AC97_LINE2_LEVEL
mdefine_line|#define AC97_LINE2_LEVEL&t;0x48&t;/* Line2 DAC/ADC Level */
DECL|macro|AC97_HANDSET_LEVEL
mdefine_line|#define AC97_HANDSET_LEVEL&t;0x4a&t;/* Handset DAC/ADC Level */
DECL|macro|AC97_GPIO_CFG
mdefine_line|#define AC97_GPIO_CFG&t;&t;0x4c&t;/* GPIO Configuration */
DECL|macro|AC97_GPIO_POLARITY
mdefine_line|#define AC97_GPIO_POLARITY&t;0x4e&t;/* GPIO Pin Polarity/Type, 0=low, 1=high active */
DECL|macro|AC97_GPIO_STICKY
mdefine_line|#define AC97_GPIO_STICKY&t;0x50&t;/* GPIO Pin Sticky, 0=not, 1=sticky */
DECL|macro|AC97_GPIO_WAKEUP
mdefine_line|#define AC97_GPIO_WAKEUP&t;0x52&t;/* GPIO Pin Wakeup, 0=no int, 1=yes int */
DECL|macro|AC97_GPIO_STATUS
mdefine_line|#define AC97_GPIO_STATUS&t;0x54&t;/* GPIO Pin Status, slot 12 */
DECL|macro|AC97_MISC_AFE
mdefine_line|#define AC97_MISC_AFE&t;&t;0x56&t;/* Miscellaneous Modem AFE Status and Control */
multiline_comment|/* range 0x5a-0x7b - Vendor Specific */
DECL|macro|AC97_VENDOR_ID1
mdefine_line|#define AC97_VENDOR_ID1&t;&t;0x7c&t;/* Vendor ID1 */
DECL|macro|AC97_VENDOR_ID2
mdefine_line|#define AC97_VENDOR_ID2&t;&t;0x7e&t;/* Vendor ID2 / revision */
multiline_comment|/* basic capabilities (reset register) */
DECL|macro|AC97_BC_DEDICATED_MIC
mdefine_line|#define AC97_BC_DEDICATED_MIC&t;0x0001&t;/* Dedicated Mic PCM In Channel */
DECL|macro|AC97_BC_RESERVED1
mdefine_line|#define AC97_BC_RESERVED1&t;0x0002&t;/* Reserved (was Modem Line Codec support) */
DECL|macro|AC97_BC_BASS_TREBLE
mdefine_line|#define AC97_BC_BASS_TREBLE&t;0x0004&t;/* Bass &amp; Treble Control */
DECL|macro|AC97_BC_SIM_STEREO
mdefine_line|#define AC97_BC_SIM_STEREO&t;0x0008&t;/* Simulated stereo */
DECL|macro|AC97_BC_HEADPHONE
mdefine_line|#define AC97_BC_HEADPHONE&t;0x0010&t;/* Headphone Out Support */
DECL|macro|AC97_BC_LOUDNESS
mdefine_line|#define AC97_BC_LOUDNESS&t;0x0020&t;/* Loudness (bass boost) Support */
DECL|macro|AC97_BC_16BIT_DAC
mdefine_line|#define AC97_BC_16BIT_DAC&t;0x0000&t;/* 16-bit DAC resolution */
DECL|macro|AC97_BC_18BIT_DAC
mdefine_line|#define AC97_BC_18BIT_DAC&t;0x0040&t;/* 18-bit DAC resolution */
DECL|macro|AC97_BC_20BIT_DAC
mdefine_line|#define AC97_BC_20BIT_DAC&t;0x0080&t;/* 20-bit DAC resolution */
DECL|macro|AC97_BC_DAC_MASK
mdefine_line|#define AC97_BC_DAC_MASK&t;0x00c0
DECL|macro|AC97_BC_16BIT_ADC
mdefine_line|#define AC97_BC_16BIT_ADC&t;0x0000&t;/* 16-bit ADC resolution */
DECL|macro|AC97_BC_18BIT_ADC
mdefine_line|#define AC97_BC_18BIT_ADC&t;0x0100&t;/* 18-bit ADC resolution */
DECL|macro|AC97_BC_20BIT_ADC
mdefine_line|#define AC97_BC_20BIT_ADC&t;0x0200&t;/* 20-bit ADC resolution */
DECL|macro|AC97_BC_ADC_MASK
mdefine_line|#define AC97_BC_ADC_MASK&t;0x0300
multiline_comment|/* extended audio ID bit defines */
DECL|macro|AC97_EI_VRA
mdefine_line|#define AC97_EI_VRA&t;&t;0x0001&t;/* Variable bit rate supported */
DECL|macro|AC97_EI_DRA
mdefine_line|#define AC97_EI_DRA&t;&t;0x0002&t;/* Double rate supported */
DECL|macro|AC97_EI_SPDIF
mdefine_line|#define AC97_EI_SPDIF&t;&t;0x0004&t;/* S/PDIF out supported */
DECL|macro|AC97_EI_VRM
mdefine_line|#define AC97_EI_VRM&t;&t;0x0008&t;/* Variable bit rate supported for MIC */
DECL|macro|AC97_EI_DACS_SLOT_MASK
mdefine_line|#define AC97_EI_DACS_SLOT_MASK&t;0x0030&t;/* DACs slot assignment */
DECL|macro|AC97_EI_DACS_SLOT_SHIFT
mdefine_line|#define AC97_EI_DACS_SLOT_SHIFT&t;4
DECL|macro|AC97_EI_CDAC
mdefine_line|#define AC97_EI_CDAC&t;&t;0x0040&t;/* PCM Center DAC available */
DECL|macro|AC97_EI_SDAC
mdefine_line|#define AC97_EI_SDAC&t;&t;0x0080&t;/* PCM Surround DACs available */
DECL|macro|AC97_EI_LDAC
mdefine_line|#define AC97_EI_LDAC&t;&t;0x0100&t;/* PCM LFE DAC available */
DECL|macro|AC97_EI_AMAP
mdefine_line|#define AC97_EI_AMAP&t;&t;0x0200&t;/* indicates optional slot/DAC mapping based on codec ID */
DECL|macro|AC97_EI_REV_MASK
mdefine_line|#define AC97_EI_REV_MASK&t;0x0c00&t;/* AC&squot;97 revision mask */
DECL|macro|AC97_EI_REV_22
mdefine_line|#define AC97_EI_REV_22&t;&t;0x0400&t;/* AC&squot;97 revision 2.2 */
DECL|macro|AC97_EI_REV_SHIFT
mdefine_line|#define AC97_EI_REV_SHIFT&t;10
DECL|macro|AC97_EI_ADDR_MASK
mdefine_line|#define AC97_EI_ADDR_MASK&t;0xc000&t;/* physical codec ID (address) */
DECL|macro|AC97_EI_ADDR_SHIFT
mdefine_line|#define AC97_EI_ADDR_SHIFT&t;14
multiline_comment|/* extended audio status and control bit defines */
DECL|macro|AC97_EA_VRA
mdefine_line|#define AC97_EA_VRA&t;&t;0x0001&t;/* Variable bit rate enable bit */
DECL|macro|AC97_EA_DRA
mdefine_line|#define AC97_EA_DRA&t;&t;0x0002&t;/* Double-rate audio enable bit */
DECL|macro|AC97_EA_SPDIF
mdefine_line|#define AC97_EA_SPDIF&t;&t;0x0004&t;/* S/PDIF out enable bit */
DECL|macro|AC97_EA_VRM
mdefine_line|#define AC97_EA_VRM&t;&t;0x0008&t;/* Variable bit rate for MIC enable bit */
DECL|macro|AC97_EA_SPSA_SLOT_MASK
mdefine_line|#define AC97_EA_SPSA_SLOT_MASK&t;0x0030&t;/* Mask for slot assignment bits */
DECL|macro|AC97_EA_SPSA_SLOT_SHIFT
mdefine_line|#define AC97_EA_SPSA_SLOT_SHIFT 4
DECL|macro|AC97_EA_SPSA_3_4
mdefine_line|#define AC97_EA_SPSA_3_4&t;0x0000&t;/* Slot assigned to 3 &amp; 4 */
DECL|macro|AC97_EA_SPSA_7_8
mdefine_line|#define AC97_EA_SPSA_7_8&t;0x0010&t;/* Slot assigned to 7 &amp; 8 */
DECL|macro|AC97_EA_SPSA_6_9
mdefine_line|#define AC97_EA_SPSA_6_9&t;0x0020&t;/* Slot assigned to 6 &amp; 9 */
DECL|macro|AC97_EA_SPSA_10_11
mdefine_line|#define AC97_EA_SPSA_10_11&t;0x0030&t;/* Slot assigned to 10 &amp; 11 */
DECL|macro|AC97_EA_CDAC
mdefine_line|#define AC97_EA_CDAC&t;&t;0x0040&t;/* PCM Center DAC is ready (Read only) */
DECL|macro|AC97_EA_SDAC
mdefine_line|#define AC97_EA_SDAC&t;&t;0x0080&t;/* PCM Surround DACs are ready (Read only) */
DECL|macro|AC97_EA_LDAC
mdefine_line|#define AC97_EA_LDAC&t;&t;0x0100&t;/* PCM LFE DAC is ready (Read only) */
DECL|macro|AC97_EA_MDAC
mdefine_line|#define AC97_EA_MDAC&t;&t;0x0200&t;/* MIC ADC is ready (Read only) */
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
DECL|macro|AC97_SC_CC_SHIFT
mdefine_line|#define AC97_SC_CC_SHIFT&t;4
DECL|macro|AC97_SC_L
mdefine_line|#define AC97_SC_L&t;&t;0x0800&t;/* Generation Level status */
DECL|macro|AC97_SC_SPSR_MASK
mdefine_line|#define AC97_SC_SPSR_MASK&t;0x3000&t;/* S/PDIF Sample Rate bits */
DECL|macro|AC97_SC_SPSR_SHIFT
mdefine_line|#define AC97_SC_SPSR_SHIFT&t;12
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
multiline_comment|/* extended modem ID bit defines */
DECL|macro|AC97_MEI_LINE1
mdefine_line|#define AC97_MEI_LINE1&t;&t;0x0001&t;/* Line1 present */
DECL|macro|AC97_MEI_LINE2
mdefine_line|#define AC97_MEI_LINE2&t;&t;0x0002&t;/* Line2 present */
DECL|macro|AC97_MEI_HANDSET
mdefine_line|#define AC97_MEI_HANDSET&t;0x0004&t;/* Handset present */
DECL|macro|AC97_MEI_CID1
mdefine_line|#define AC97_MEI_CID1&t;&t;0x0008&t;/* caller ID decode for Line1 is supported */
DECL|macro|AC97_MEI_CID2
mdefine_line|#define AC97_MEI_CID2&t;&t;0x0010&t;/* caller ID decode for Line2 is supported */
DECL|macro|AC97_MEI_ADDR_MASK
mdefine_line|#define AC97_MEI_ADDR_MASK&t;0xc000&t;/* physical codec ID (address) */
DECL|macro|AC97_MEI_ADDR_SHIFT
mdefine_line|#define AC97_MEI_ADDR_SHIFT&t;14
multiline_comment|/* extended modem status and control bit defines */
DECL|macro|AC97_MEA_GPIO
mdefine_line|#define AC97_MEA_GPIO&t;&t;0x0001&t;/* GPIO is ready (ro) */
DECL|macro|AC97_MEA_MREF
mdefine_line|#define AC97_MEA_MREF&t;&t;0x0002&t;/* Vref is up to nominal level (ro) */
DECL|macro|AC97_MEA_ADC1
mdefine_line|#define AC97_MEA_ADC1&t;&t;0x0004&t;/* ADC1 operational (ro) */
DECL|macro|AC97_MEA_DAC1
mdefine_line|#define AC97_MEA_DAC1&t;&t;0x0008&t;/* DAC1 operational (ro) */
DECL|macro|AC97_MEA_ADC2
mdefine_line|#define AC97_MEA_ADC2&t;&t;0x0010&t;/* ADC2 operational (ro) */
DECL|macro|AC97_MEA_DAC2
mdefine_line|#define AC97_MEA_DAC2&t;&t;0x0020&t;/* DAC2 operational (ro) */
DECL|macro|AC97_MEA_HADC
mdefine_line|#define AC97_MEA_HADC&t;&t;0x0040&t;/* HADC operational (ro) */
DECL|macro|AC97_MEA_HDAC
mdefine_line|#define AC97_MEA_HDAC&t;&t;0x0080&t;/* HDAC operational (ro) */
DECL|macro|AC97_MEA_PRA
mdefine_line|#define AC97_MEA_PRA&t;&t;0x0100&t;/* GPIO power down (high) */
DECL|macro|AC97_MEA_PRB
mdefine_line|#define AC97_MEA_PRB&t;&t;0x0200&t;/* reserved */
DECL|macro|AC97_MEA_PRC
mdefine_line|#define AC97_MEA_PRC&t;&t;0x0400&t;/* ADC1 power down (high) */
DECL|macro|AC97_MEA_PRD
mdefine_line|#define AC97_MEA_PRD&t;&t;0x0800&t;/* DAC1 power down (high) */
DECL|macro|AC97_MEA_PRE
mdefine_line|#define AC97_MEA_PRE&t;&t;0x1000&t;/* ADC2 power down (high) */
DECL|macro|AC97_MEA_PRF
mdefine_line|#define AC97_MEA_PRF&t;&t;0x2000&t;/* DAC2 power down (high) */
DECL|macro|AC97_MEA_PRG
mdefine_line|#define AC97_MEA_PRG&t;&t;0x4000&t;/* HADC power down (high) */
DECL|macro|AC97_MEA_PRH
mdefine_line|#define AC97_MEA_PRH&t;&t;0x8000&t;/* HDAC power down (high) */
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
multiline_comment|/* specific - Conexant */
DECL|macro|AC97_CXR_AUDIO_MISC
mdefine_line|#define AC97_CXR_AUDIO_MISC&t;0x5c
DECL|macro|AC97_CXR_SPDIFEN
mdefine_line|#define AC97_CXR_SPDIFEN&t;(1&lt;&lt;3)
DECL|macro|AC97_CXR_COPYRGT
mdefine_line|#define AC97_CXR_COPYRGT&t;(1&lt;&lt;2)
DECL|macro|AC97_CXR_SPDIF_MASK
mdefine_line|#define AC97_CXR_SPDIF_MASK&t;(3&lt;&lt;0)
DECL|macro|AC97_CXR_SPDIF_PCM
mdefine_line|#define AC97_CXR_SPDIF_PCM&t;0x0
DECL|macro|AC97_CXR_SPDIF_AC3
mdefine_line|#define AC97_CXR_SPDIF_AC3&t;0x2
multiline_comment|/* specific - ALC */
DECL|macro|AC97_ALC650_SURR_DAC_VOL
mdefine_line|#define AC97_ALC650_SURR_DAC_VOL&t;0x64
DECL|macro|AC97_ALC650_LFE_DAC_VOL
mdefine_line|#define AC97_ALC650_LFE_DAC_VOL&t;&t;0x66
DECL|macro|AC97_ALC650_MULTICH
mdefine_line|#define AC97_ALC650_MULTICH&t;0x6a
DECL|macro|AC97_ALC650_CLOCK
mdefine_line|#define AC97_ALC650_CLOCK&t;0x7a
multiline_comment|/* specific - Yamaha YMF753 */
DECL|macro|AC97_YMF753_DIT_CTRL2
mdefine_line|#define AC97_YMF753_DIT_CTRL2&t;0x66&t;/* DIT Control 2 */
DECL|macro|AC97_YMF753_3D_MODE_SEL
mdefine_line|#define AC97_YMF753_3D_MODE_SEL&t;0x68&t;/* 3D Mode Select */
multiline_comment|/* specific - C-Media */
DECL|macro|AC97_CM9738_VENDOR_CTRL
mdefine_line|#define AC97_CM9738_VENDOR_CTRL&t;0x5a
DECL|macro|AC97_CM9739_MULTI_CHAN
mdefine_line|#define AC97_CM9739_MULTI_CHAN&t;0x64
DECL|macro|AC97_CM9739_SPDIF_IN_STATUS
mdefine_line|#define AC97_CM9739_SPDIF_IN_STATUS&t;0x68 /* 32bit */
DECL|macro|AC97_CM9739_SPDIF_CTRL
mdefine_line|#define AC97_CM9739_SPDIF_CTRL&t;0x6c
multiline_comment|/* specific - wolfson */
DECL|macro|AC97_WM97XX_FMIXER_VOL
mdefine_line|#define AC97_WM97XX_FMIXER_VOL  0x72
DECL|macro|AC97_WM9704_RMIXER_VOL
mdefine_line|#define AC97_WM9704_RMIXER_VOL  0x74
DECL|macro|AC97_WM9704_TEST
mdefine_line|#define AC97_WM9704_TEST        0x5a
DECL|macro|AC97_WM9704_RPCM_VOL
mdefine_line|#define AC97_WM9704_RPCM_VOL    0x70
DECL|macro|AC97_WM9711_OUT3VOL
mdefine_line|#define AC97_WM9711_OUT3VOL     0x16
multiline_comment|/* ac97-&gt;scaps */
DECL|macro|AC97_SCAP_AUDIO
mdefine_line|#define AC97_SCAP_AUDIO&t;&t;(1&lt;&lt;0)&t;/* audio AC&squot;97 codec */
DECL|macro|AC97_SCAP_MODEM
mdefine_line|#define AC97_SCAP_MODEM&t;&t;(1&lt;&lt;1)&t;/* modem AC&squot;97 codec */
DECL|macro|AC97_SCAP_SURROUND_DAC
mdefine_line|#define AC97_SCAP_SURROUND_DAC&t;(1&lt;&lt;2)&t;/* surround L&amp;R DACs are present */
DECL|macro|AC97_SCAP_CENTER_LFE_DAC
mdefine_line|#define AC97_SCAP_CENTER_LFE_DAC (1&lt;&lt;3)&t;/* center and LFE DACs are present */
multiline_comment|/* ac97-&gt;flags */
DECL|macro|AC97_HAS_PC_BEEP
mdefine_line|#define AC97_HAS_PC_BEEP&t;(1&lt;&lt;0)&t;/* force PC Speaker usage */
DECL|macro|AC97_AD_MULTI
mdefine_line|#define AC97_AD_MULTI&t;&t;(1&lt;&lt;1)&t;/* Analog Devices - multi codecs */
DECL|macro|AC97_CS_SPDIF
mdefine_line|#define AC97_CS_SPDIF&t;&t;(1&lt;&lt;2)&t;/* Cirrus Logic uses funky SPDIF */
DECL|macro|AC97_CX_SPDIF
mdefine_line|#define AC97_CX_SPDIF&t;&t;(1&lt;&lt;3)&t;/* Conexant&squot;s spdif interface */
multiline_comment|/* rates indexes */
DECL|macro|AC97_RATES_FRONT_DAC
mdefine_line|#define AC97_RATES_FRONT_DAC&t;0
DECL|macro|AC97_RATES_SURR_DAC
mdefine_line|#define AC97_RATES_SURR_DAC&t;1
DECL|macro|AC97_RATES_LFE_DAC
mdefine_line|#define AC97_RATES_LFE_DAC&t;2
DECL|macro|AC97_RATES_ADC
mdefine_line|#define AC97_RATES_ADC&t;&t;3
DECL|macro|AC97_RATES_MIC_ADC
mdefine_line|#define AC97_RATES_MIC_ADC&t;4
DECL|macro|AC97_RATES_SPDIF
mdefine_line|#define AC97_RATES_SPDIF&t;5
multiline_comment|/*&n; *&n; */
DECL|typedef|ac97_t
r_typedef
r_struct
id|_snd_ac97
id|ac97_t
suffix:semicolon
DECL|struct|snd_ac97_build_ops
r_struct
id|snd_ac97_build_ops
(brace
DECL|member|build_3d
r_int
(paren
op_star
id|build_3d
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
DECL|member|build_specific
r_int
(paren
op_star
id|build_specific
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
DECL|member|build_spdif
r_int
(paren
op_star
id|build_spdif
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
DECL|member|build_post_spdif
r_int
(paren
op_star
id|build_post_spdif
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_ac97
r_struct
id|_snd_ac97
(brace
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
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
DECL|member|build_ops
r_struct
id|snd_ac97_build_ops
op_star
id|build_ops
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
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
multiline_comment|/* assigned PCI device - used for quirks */
DECL|member|subsystem_vendor
r_int
r_int
id|subsystem_vendor
suffix:semicolon
DECL|member|subsystem_device
r_int
r_int
id|subsystem_device
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
DECL|member|ext_mid
r_int
r_int
id|ext_mid
suffix:semicolon
multiline_comment|/* extended modem ID (register 3C) */
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
DECL|member|rates
r_int
r_int
id|rates
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* see AC97_RATES_* defines */
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
DECL|member|limited_regs
r_int
r_int
id|limited_regs
suffix:semicolon
multiline_comment|/* allow limited registers only */
id|DECLARE_BITMAP
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
DECL|member|codec_cfg
r_int
r_int
id|codec_cfg
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// CODEC_CFG bits
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|member|ad18xx
)brace
id|ad18xx
suffix:semicolon
DECL|member|dev_flags
r_int
r_int
id|dev_flags
suffix:semicolon
multiline_comment|/* device specific */
DECL|member|spec
)brace
id|spec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* conditions */
DECL|function|ac97_is_audio
r_static
r_inline
r_int
id|ac97_is_audio
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_return
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_AUDIO
)paren
suffix:semicolon
)brace
DECL|function|ac97_is_modem
r_static
r_inline
r_int
id|ac97_is_modem
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_return
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_MODEM
)paren
suffix:semicolon
)brace
DECL|function|ac97_is_rev22
r_static
r_inline
r_int
id|ac97_is_rev22
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_return
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_REV_MASK
)paren
op_eq
id|AC97_EI_REV_22
suffix:semicolon
)brace
DECL|function|ac97_can_amap
r_static
r_inline
r_int
id|ac97_can_amap
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_return
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_AMAP
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* functions */
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
multiline_comment|/* create mixer controls */
r_int
id|snd_ac97_modem
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
multiline_comment|/* create modem controls */
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
DECL|enumerator|AC97_TUNE_HP_ONLY
DECL|enumerator|AC97_TUNE_SWAP_HP
DECL|enumerator|AC97_TUNE_SWAP_SURROUND
r_enum
(brace
id|AC97_TUNE_HP_ONLY
comma
id|AC97_TUNE_SWAP_HP
comma
id|AC97_TUNE_SWAP_SURROUND
)brace
suffix:semicolon
DECL|struct|ac97_quirk
r_struct
id|ac97_quirk
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_ac97_tune_hardware
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_struct
id|ac97_quirk
op_star
id|quirk
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_AC97_CODEC_H */
eof
