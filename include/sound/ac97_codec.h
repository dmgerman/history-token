macro_line|#ifndef __SOUND_AC97_CODEC_H
DECL|macro|__SOUND_AC97_CODEC_H
mdefine_line|#define __SOUND_AC97_CODEC_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.1&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &quot;pcm.h&quot;
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
DECL|macro|AC97_INT_PAGING
mdefine_line|#define AC97_INT_PAGING&t;&t;0x24&t;/* Audio Interrupt &amp; Paging (AC&squot;97 2.3) */
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
multiline_comment|/* range 0x60-0x6f (page 1) - extended codec registers */
DECL|macro|AC97_CODEC_CLASS_REV
mdefine_line|#define AC97_CODEC_CLASS_REV&t;0x60&t;/* Codec Class/Revision */
DECL|macro|AC97_PCI_SVID
mdefine_line|#define AC97_PCI_SVID&t;&t;0x62&t;/* PCI Subsystem Vendor ID */
DECL|macro|AC97_PCI_SID
mdefine_line|#define AC97_PCI_SID&t;&t;0x64&t;/* PCI Subsystem ID */
DECL|macro|AC97_FUNC_SELECT
mdefine_line|#define AC97_FUNC_SELECT&t;0x66&t;/* Function Select */
DECL|macro|AC97_FUNC_INFO
mdefine_line|#define AC97_FUNC_INFO&t;&t;0x68&t;/* Function Information */
DECL|macro|AC97_SENSE_INFO
mdefine_line|#define AC97_SENSE_INFO&t;&t;0x6a&t;/* Sense Details */
multiline_comment|/* slot allocation */
DECL|macro|AC97_SLOT_TAG
mdefine_line|#define AC97_SLOT_TAG&t;&t;0
DECL|macro|AC97_SLOT_CMD_ADDR
mdefine_line|#define AC97_SLOT_CMD_ADDR&t;1
DECL|macro|AC97_SLOT_CMD_DATA
mdefine_line|#define AC97_SLOT_CMD_DATA&t;2
DECL|macro|AC97_SLOT_PCM_LEFT
mdefine_line|#define AC97_SLOT_PCM_LEFT&t;3
DECL|macro|AC97_SLOT_PCM_RIGHT
mdefine_line|#define AC97_SLOT_PCM_RIGHT&t;4
DECL|macro|AC97_SLOT_MODEM_LINE1
mdefine_line|#define AC97_SLOT_MODEM_LINE1&t;5
DECL|macro|AC97_SLOT_PCM_CENTER
mdefine_line|#define AC97_SLOT_PCM_CENTER&t;6
DECL|macro|AC97_SLOT_MIC
mdefine_line|#define AC97_SLOT_MIC&t;&t;6&t;/* input */
DECL|macro|AC97_SLOT_SPDIF_LEFT1
mdefine_line|#define AC97_SLOT_SPDIF_LEFT1&t;6
DECL|macro|AC97_SLOT_PCM_SLEFT
mdefine_line|#define AC97_SLOT_PCM_SLEFT&t;7&t;/* surround left */
DECL|macro|AC97_SLOT_PCM_LEFT_0
mdefine_line|#define AC97_SLOT_PCM_LEFT_0&t;7&t;/* double rate operation */
DECL|macro|AC97_SLOT_SPDIF_LEFT
mdefine_line|#define AC97_SLOT_SPDIF_LEFT&t;7
DECL|macro|AC97_SLOT_PCM_SRIGHT
mdefine_line|#define AC97_SLOT_PCM_SRIGHT&t;8&t;/* surround right */
DECL|macro|AC97_SLOT_PCM_RIGHT_0
mdefine_line|#define AC97_SLOT_PCM_RIGHT_0&t;8&t;/* double rate operation */
DECL|macro|AC97_SLOT_SPDIF_RIGHT
mdefine_line|#define AC97_SLOT_SPDIF_RIGHT&t;8
DECL|macro|AC97_SLOT_LFE
mdefine_line|#define AC97_SLOT_LFE&t;&t;9
DECL|macro|AC97_SLOT_SPDIF_RIGHT1
mdefine_line|#define AC97_SLOT_SPDIF_RIGHT1&t;9
DECL|macro|AC97_SLOT_MODEM_LINE2
mdefine_line|#define AC97_SLOT_MODEM_LINE2&t;10
DECL|macro|AC97_SLOT_PCM_LEFT_1
mdefine_line|#define AC97_SLOT_PCM_LEFT_1&t;10&t;/* double rate operation */
DECL|macro|AC97_SLOT_SPDIF_LEFT2
mdefine_line|#define AC97_SLOT_SPDIF_LEFT2&t;10
DECL|macro|AC97_SLOT_HANDSET
mdefine_line|#define AC97_SLOT_HANDSET&t;11&t;/* output */
DECL|macro|AC97_SLOT_PCM_RIGHT_1
mdefine_line|#define AC97_SLOT_PCM_RIGHT_1&t;11&t;/* double rate operation */
DECL|macro|AC97_SLOT_SPDIF_RIGHT2
mdefine_line|#define AC97_SLOT_SPDIF_RIGHT2&t;11
DECL|macro|AC97_SLOT_MODEM_GPIO
mdefine_line|#define AC97_SLOT_MODEM_GPIO&t;12&t;/* modem GPIO */
DECL|macro|AC97_SLOT_PCM_CENTER_1
mdefine_line|#define AC97_SLOT_PCM_CENTER_1&t;12&t;/* double rate operation */
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
multiline_comment|/* general purpose */
DECL|macro|AC97_GP_DRSS_MASK
mdefine_line|#define AC97_GP_DRSS_MASK&t;0x0c00&t;/* double rate slot select */
DECL|macro|AC97_GP_DRSS_1011
mdefine_line|#define AC97_GP_DRSS_1011&t;0x0000&t;/* LR(C) 10+11(+12) */
DECL|macro|AC97_GP_DRSS_78
mdefine_line|#define AC97_GP_DRSS_78&t;&t;0x0400&t;/* LR 7+8 */
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
DECL|macro|AC97_EI_REV_23
mdefine_line|#define AC97_EI_REV_23&t;&t;0x0800&t;/* AC&squot;97 revision 2.3 */
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
multiline_comment|/* Interrupt and Paging bit defines (AC&squot;97 2.3) */
DECL|macro|AC97_PAGE_MASK
mdefine_line|#define AC97_PAGE_MASK&t;&t;0x000f&t;/* Page Selector */
DECL|macro|AC97_PAGE_VENDOR
mdefine_line|#define AC97_PAGE_VENDOR&t;0&t;/* Vendor-specific registers */
DECL|macro|AC97_PAGE_1
mdefine_line|#define AC97_PAGE_1&t;&t;1&t;/* Extended Codec Registers page 1 */
DECL|macro|AC97_INT_ENABLE
mdefine_line|#define AC97_INT_ENABLE&t;&t;0x0800&t;/* Interrupt Enable */
DECL|macro|AC97_INT_SENSE
mdefine_line|#define AC97_INT_SENSE&t;&t;0x1000&t;/* Sense Cycle */
DECL|macro|AC97_INT_CAUSE_SENSE
mdefine_line|#define AC97_INT_CAUSE_SENSE&t;0x2000&t;/* Sense Cycle Completed (RO) */
DECL|macro|AC97_INT_CAUSE_GPIO
mdefine_line|#define AC97_INT_CAUSE_GPIO&t;0x4000&t;/* GPIO bits changed (RO) */
DECL|macro|AC97_INT_STATUS
mdefine_line|#define AC97_INT_STATUS&t;&t;0x8000&t;/* Interrupt Status */
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
multiline_comment|/* modem gpio status defines */
DECL|macro|AC97_GPIO_LINE1_OH
mdefine_line|#define AC97_GPIO_LINE1_OH      0x0001  /* Off Hook Line1 */
DECL|macro|AC97_GPIO_LINE1_RI
mdefine_line|#define AC97_GPIO_LINE1_RI      0x0002  /* Ring Detect Line1 */
DECL|macro|AC97_GPIO_LINE1_CID
mdefine_line|#define AC97_GPIO_LINE1_CID     0x0004  /* Caller ID path enable Line1 */
DECL|macro|AC97_GPIO_LINE1_LCS
mdefine_line|#define AC97_GPIO_LINE1_LCS     0x0008  /* Loop Current Sense Line1 */
DECL|macro|AC97_GPIO_LINE1_PULSE
mdefine_line|#define AC97_GPIO_LINE1_PULSE   0x0010  /* Opt./ Pulse Dial Line1 (out) */
DECL|macro|AC97_GPIO_LINE1_HL1R
mdefine_line|#define AC97_GPIO_LINE1_HL1R    0x0020  /* Opt./ Handset to Line1 relay control (out) */
DECL|macro|AC97_GPIO_LINE1_HOHD
mdefine_line|#define AC97_GPIO_LINE1_HOHD    0x0040  /* Opt./ Handset off hook detect Line1 (in) */
DECL|macro|AC97_GPIO_LINE12_AC
mdefine_line|#define AC97_GPIO_LINE12_AC     0x0080  /* Opt./ Int.bit 1 / Line1/2 AC (out) */
DECL|macro|AC97_GPIO_LINE12_DC
mdefine_line|#define AC97_GPIO_LINE12_DC     0x0100  /* Opt./ Int.bit 2 / Line1/2 DC (out) */
DECL|macro|AC97_GPIO_LINE12_RS
mdefine_line|#define AC97_GPIO_LINE12_RS     0x0200  /* Opt./ Int.bit 3 / Line1/2 RS (out) */
DECL|macro|AC97_GPIO_LINE2_OH
mdefine_line|#define AC97_GPIO_LINE2_OH      0x0400  /* Off Hook Line2 */
DECL|macro|AC97_GPIO_LINE2_RI
mdefine_line|#define AC97_GPIO_LINE2_RI      0x0800  /* Ring Detect Line2 */
DECL|macro|AC97_GPIO_LINE2_CID
mdefine_line|#define AC97_GPIO_LINE2_CID     0x1000  /* Caller ID path enable Line2 */
DECL|macro|AC97_GPIO_LINE2_LCS
mdefine_line|#define AC97_GPIO_LINE2_LCS     0x2000  /* Loop Current Sense Line2 */
DECL|macro|AC97_GPIO_LINE2_PULSE
mdefine_line|#define AC97_GPIO_LINE2_PULSE   0x4000  /* Opt./ Pulse Dial Line2 (out) */
DECL|macro|AC97_GPIO_LINE2_HL1R
mdefine_line|#define AC97_GPIO_LINE2_HL1R    0x8000  /* Opt./ Handset to Line2 relay control (out) */
multiline_comment|/* specific - SigmaTel */
DECL|macro|AC97_SIGMATEL_OUTSEL
mdefine_line|#define AC97_SIGMATEL_OUTSEL&t;0x64&t;/* Output Select, STAC9758 */
DECL|macro|AC97_SIGMATEL_INSEL
mdefine_line|#define AC97_SIGMATEL_INSEL&t;0x66&t;/* Input Select, STAC9758 */
DECL|macro|AC97_SIGMATEL_IOMISC
mdefine_line|#define AC97_SIGMATEL_IOMISC&t;0x68&t;/* STAC9758 */
DECL|macro|AC97_SIGMATEL_ANALOG
mdefine_line|#define AC97_SIGMATEL_ANALOG&t;0x6c&t;/* Analog Special */
DECL|macro|AC97_SIGMATEL_DAC2INVERT
mdefine_line|#define AC97_SIGMATEL_DAC2INVERT 0x6e
DECL|macro|AC97_SIGMATEL_BIAS1
mdefine_line|#define AC97_SIGMATEL_BIAS1&t;0x70
DECL|macro|AC97_SIGMATEL_BIAS2
mdefine_line|#define AC97_SIGMATEL_BIAS2&t;0x72
DECL|macro|AC97_SIGMATEL_VARIOUS
mdefine_line|#define AC97_SIGMATEL_VARIOUS&t;0x72&t;/* STAC9758 */
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
DECL|macro|AC97_ALC650_SPDIF_INPUT_STATUS1
mdefine_line|#define AC97_ALC650_SPDIF_INPUT_STATUS1&t;0x60
multiline_comment|/* S/PDIF input status 1 bit defines */
DECL|macro|AC97_ALC650_PRO
mdefine_line|#define AC97_ALC650_PRO             0x0001  /* Professional status */
DECL|macro|AC97_ALC650_NAUDIO
mdefine_line|#define AC97_ALC650_NAUDIO          0x0002  /* Non audio stream */
DECL|macro|AC97_ALC650_COPY
mdefine_line|#define AC97_ALC650_COPY            0x0004  /* Copyright status */
DECL|macro|AC97_ALC650_PRE
mdefine_line|#define AC97_ALC650_PRE             0x0038  /* Preemphasis status */
DECL|macro|AC97_ALC650_PRE_SHIFT
mdefine_line|#define AC97_ALC650_PRE_SHIFT       3
DECL|macro|AC97_ALC650_MODE
mdefine_line|#define AC97_ALC650_MODE            0x00C0  /* Preemphasis status */
DECL|macro|AC97_ALC650_MODE_SHIFT
mdefine_line|#define AC97_ALC650_MODE_SHIFT      6
DECL|macro|AC97_ALC650_CC_MASK
mdefine_line|#define AC97_ALC650_CC_MASK         0x7f00  /* Category Code mask */
DECL|macro|AC97_ALC650_CC_SHIFT
mdefine_line|#define AC97_ALC650_CC_SHIFT        8
DECL|macro|AC97_ALC650_L
mdefine_line|#define AC97_ALC650_L               0x8000  /* Generation Level status */
DECL|macro|AC97_ALC650_SPDIF_INPUT_STATUS2
mdefine_line|#define AC97_ALC650_SPDIF_INPUT_STATUS2&t;0x62
multiline_comment|/* S/PDIF input status 2 bit defines */
DECL|macro|AC97_ALC650_SOUCE_MASK
mdefine_line|#define AC97_ALC650_SOUCE_MASK      0x000f  /* Source number */
DECL|macro|AC97_ALC650_CHANNEL_MASK
mdefine_line|#define AC97_ALC650_CHANNEL_MASK    0x00f0  /* Channel number */
DECL|macro|AC97_ALC650_CHANNEL_SHIFT
mdefine_line|#define AC97_ALC650_CHANNEL_SHIFT   4 
DECL|macro|AC97_ALC650_SPSR_MASK
mdefine_line|#define AC97_ALC650_SPSR_MASK       0x0f00  /* S/PDIF Sample Rate bits */
DECL|macro|AC97_ALC650_SPSR_SHIFT
mdefine_line|#define AC97_ALC650_SPSR_SHIFT      8
DECL|macro|AC97_ALC650_SPSR_44K
mdefine_line|#define AC97_ALC650_SPSR_44K        0x0000  /* Use 44.1kHz Sample rate */
DECL|macro|AC97_ALC650_SPSR_48K
mdefine_line|#define AC97_ALC650_SPSR_48K        0x0200  /* Use 48kHz Sample rate */
DECL|macro|AC97_ALC650_SPSR_32K
mdefine_line|#define AC97_ALC650_SPSR_32K        0x0300  /* Use 32kHz Sample rate */
DECL|macro|AC97_ALC650_CLOCK_ACCURACY
mdefine_line|#define AC97_ALC650_CLOCK_ACCURACY  0x3000  /* Clock accuracy */
DECL|macro|AC97_ALC650_CLOCK_SHIFT
mdefine_line|#define AC97_ALC650_CLOCK_SHIFT     12
DECL|macro|AC97_ALC650_CLOCK_LOCK
mdefine_line|#define AC97_ALC650_CLOCK_LOCK      0x4000  /* Clock locked status */
DECL|macro|AC97_ALC650_V
mdefine_line|#define AC97_ALC650_V               0x8000  /* Validity status */
DECL|macro|AC97_ALC650_SURR_DAC_VOL
mdefine_line|#define AC97_ALC650_SURR_DAC_VOL&t;0x64
DECL|macro|AC97_ALC650_LFE_DAC_VOL
mdefine_line|#define AC97_ALC650_LFE_DAC_VOL&t;&t;0x66
DECL|macro|AC97_ALC650_UNKNOWN1
mdefine_line|#define AC97_ALC650_UNKNOWN1&t;&t;0x68
DECL|macro|AC97_ALC650_MULTICH
mdefine_line|#define AC97_ALC650_MULTICH&t;&t;0x6a
DECL|macro|AC97_ALC650_UNKNOWN2
mdefine_line|#define AC97_ALC650_UNKNOWN2&t;&t;0x6c
DECL|macro|AC97_ALC650_REVISION
mdefine_line|#define AC97_ALC650_REVISION&t;&t;0x6e
DECL|macro|AC97_ALC650_UNKNOWN3
mdefine_line|#define AC97_ALC650_UNKNOWN3&t;&t;0x70
DECL|macro|AC97_ALC650_UNKNOWN4
mdefine_line|#define AC97_ALC650_UNKNOWN4&t;&t;0x72
DECL|macro|AC97_ALC650_MISC
mdefine_line|#define AC97_ALC650_MISC&t;&t;0x74
DECL|macro|AC97_ALC650_GPIO_SETUP
mdefine_line|#define AC97_ALC650_GPIO_SETUP&t;&t;0x76
DECL|macro|AC97_ALC650_GPIO_STATUS
mdefine_line|#define AC97_ALC650_GPIO_STATUS&t;&t;0x78
DECL|macro|AC97_ALC650_CLOCK
mdefine_line|#define AC97_ALC650_CLOCK&t;&t;0x7a
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
mdefine_line|#define AC97_SCAP_AUDIO&t;&t;(1&lt;&lt;0)&t;/* audio codec 97 */
DECL|macro|AC97_SCAP_MODEM
mdefine_line|#define AC97_SCAP_MODEM&t;&t;(1&lt;&lt;1)&t;/* modem codec 97 */
DECL|macro|AC97_SCAP_SURROUND_DAC
mdefine_line|#define AC97_SCAP_SURROUND_DAC&t;(1&lt;&lt;2)&t;/* surround L&amp;R DACs are present */
DECL|macro|AC97_SCAP_CENTER_LFE_DAC
mdefine_line|#define AC97_SCAP_CENTER_LFE_DAC (1&lt;&lt;3)&t;/* center and LFE DACs are present */
DECL|macro|AC97_SCAP_SKIP_AUDIO
mdefine_line|#define AC97_SCAP_SKIP_AUDIO&t;(1&lt;&lt;4)&t;/* skip audio part of codec */
DECL|macro|AC97_SCAP_SKIP_MODEM
mdefine_line|#define AC97_SCAP_SKIP_MODEM&t;(1&lt;&lt;5)&t;/* skip modem part of codec */
DECL|macro|AC97_SCAP_INDEP_SDIN
mdefine_line|#define AC97_SCAP_INDEP_SDIN&t;(1&lt;&lt;6)&t;/* independent SDIN */
DECL|macro|AC97_SCAP_INV_EAPD
mdefine_line|#define AC97_SCAP_INV_EAPD&t;(1&lt;&lt;7)&t;/* inverted EAPD */
DECL|macro|AC97_SCAP_DETECT_BY_VENDOR
mdefine_line|#define AC97_SCAP_DETECT_BY_VENDOR (1&lt;&lt;8) /* use vendor registers for read tests */
multiline_comment|/* ac97-&gt;flags */
DECL|macro|AC97_HAS_PC_BEEP
mdefine_line|#define AC97_HAS_PC_BEEP&t;(1&lt;&lt;0)&t;/* force PC Speaker usage */
DECL|macro|AC97_AD_MULTI
mdefine_line|#define AC97_AD_MULTI&t;&t;(1&lt;&lt;1)&t;/* Analog Devices - multi codecs */
DECL|macro|AC97_CS_SPDIF
mdefine_line|#define AC97_CS_SPDIF&t;&t;(1&lt;&lt;2)&t;/* Cirrus Logic uses funky SPDIF */
DECL|macro|AC97_CX_SPDIF
mdefine_line|#define AC97_CX_SPDIF&t;&t;(1&lt;&lt;3)&t;/* Conexant&squot;s spdif interface */
DECL|macro|AC97_STEREO_MUTES
mdefine_line|#define AC97_STEREO_MUTES&t;(1&lt;&lt;4)&t;/* has stereo mute bits */
DECL|macro|AC97_DOUBLE_RATE
mdefine_line|#define AC97_DOUBLE_RATE&t;(1&lt;&lt;5)&t;/* supports double rate playback */
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
multiline_comment|/* shared controllers */
r_enum
(brace
DECL|enumerator|AC97_SHARED_TYPE_NONE
id|AC97_SHARED_TYPE_NONE
comma
DECL|enumerator|AC97_SHARED_TYPE_ICH
id|AC97_SHARED_TYPE_ICH
comma
DECL|enumerator|AC97_SHARED_TYPE_ATIIXP
id|AC97_SHARED_TYPE_ATIIXP
comma
DECL|enumerator|AC97_SHARED_TYPE_VIA
id|AC97_SHARED_TYPE_VIA
comma
DECL|enumerator|AC97_SHARED_TYPES
id|AC97_SHARED_TYPES
)brace
suffix:semicolon
multiline_comment|/*&n; *&n; */
DECL|typedef|ac97_bus_t
r_typedef
r_struct
id|_snd_ac97_bus
id|ac97_bus_t
suffix:semicolon
DECL|typedef|ac97_bus_ops_t
r_typedef
r_struct
id|_snd_ac97_bus_ops
id|ac97_bus_ops_t
suffix:semicolon
DECL|typedef|ac97_template_t
r_typedef
r_struct
id|_snd_ac97_template
id|ac97_template_t
suffix:semicolon
DECL|typedef|ac97_t
r_typedef
r_struct
id|_snd_ac97
id|ac97_t
suffix:semicolon
DECL|enum|ac97_pcm_cfg
r_enum
id|ac97_pcm_cfg
(brace
DECL|enumerator|AC97_PCM_CFG_FRONT
id|AC97_PCM_CFG_FRONT
op_assign
l_int|2
comma
DECL|enumerator|AC97_PCM_CFG_REAR
id|AC97_PCM_CFG_REAR
op_assign
l_int|10
comma
multiline_comment|/* alias surround */
DECL|enumerator|AC97_PCM_CFG_LFE
id|AC97_PCM_CFG_LFE
op_assign
l_int|11
comma
multiline_comment|/* center + lfe */
DECL|enumerator|AC97_PCM_CFG_40
id|AC97_PCM_CFG_40
op_assign
l_int|4
comma
multiline_comment|/* front + rear */
DECL|enumerator|AC97_PCM_CFG_51
id|AC97_PCM_CFG_51
op_assign
l_int|6
comma
multiline_comment|/* front + rear + center/lfe */
DECL|enumerator|AC97_PCM_CFG_SPDIF
id|AC97_PCM_CFG_SPDIF
op_assign
l_int|20
)brace
suffix:semicolon
multiline_comment|/* PCM allocation */
DECL|struct|ac97_pcm
r_struct
id|ac97_pcm
(brace
DECL|member|bus
id|ac97_bus_t
op_star
id|bus
suffix:semicolon
DECL|member|stream
r_int
r_int
id|stream
suffix:colon
l_int|1
comma
multiline_comment|/* stream type: 1 = capture */
DECL|member|exclusive
id|exclusive
suffix:colon
l_int|1
comma
multiline_comment|/* exclusive mode, don&squot;t override with other pcms */
DECL|member|copy_flag
id|copy_flag
suffix:colon
l_int|1
comma
multiline_comment|/* lowlevel driver must fill all entries */
DECL|member|spdif
id|spdif
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* spdif pcm */
DECL|member|aslots
r_int
r_int
id|aslots
suffix:semicolon
multiline_comment|/* active slots */
DECL|member|rates
r_int
r_int
id|rates
suffix:semicolon
multiline_comment|/* available rates */
r_struct
(brace
DECL|member|slots
r_int
r_int
id|slots
suffix:semicolon
multiline_comment|/* driver input: requested AC97 slot numbers */
DECL|member|rslots
r_int
r_int
id|rslots
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* allocated slots per codecs */
DECL|member|rate_table
r_int
r_char
id|rate_table
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|codec
id|ac97_t
op_star
id|codec
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* allocated codecs */
DECL|member|r
)brace
id|r
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0 = standard rates, 1 = double rates */
DECL|member|private_value
r_int
r_int
id|private_value
suffix:semicolon
multiline_comment|/* used by the hardware driver */
)brace
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
macro_line|#ifdef CONFIG_PM
DECL|member|resume
r_void
(paren
op_star
id|resume
)paren
(paren
id|ac97_t
op_star
id|ac97
)paren
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|_snd_ac97_bus_ops
r_struct
id|_snd_ac97_bus_ops
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
)brace
suffix:semicolon
DECL|struct|_snd_ac97_bus
r_struct
id|_snd_ac97_bus
(brace
multiline_comment|/* -- lowlevel (hardware) driver specific -- */
DECL|member|ops
id|ac97_bus_ops_t
op_star
id|ops
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
id|ac97_bus_t
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* --- */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
multiline_comment|/* bus number */
DECL|member|no_vra
r_int
r_int
id|no_vra
suffix:colon
l_int|1
comma
multiline_comment|/* bridge doesn&squot;t support VRA */
DECL|member|dra
id|dra
suffix:colon
l_int|1
comma
multiline_comment|/* bridge supports double rate */
DECL|member|isdin
id|isdin
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* independent SDIN */
DECL|member|clock
r_int
r_int
id|clock
suffix:semicolon
multiline_comment|/* AC&squot;97 base clock (usually 48000Hz) */
DECL|member|bus_lock
id|spinlock_t
id|bus_lock
suffix:semicolon
multiline_comment|/* used mainly for slot allocation */
DECL|member|used_slots
r_int
r_int
id|used_slots
(braket
l_int|2
)braket
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* actually used PCM slots */
DECL|member|pcms_count
r_int
r_int
id|pcms_count
suffix:semicolon
multiline_comment|/* count of PCMs */
DECL|member|pcms
r_struct
id|ac97_pcm
op_star
id|pcms
suffix:semicolon
DECL|member|shared_type
r_int
r_int
id|shared_type
suffix:semicolon
multiline_comment|/* type of shared controller betwen audio and modem */
DECL|member|codec
id|ac97_t
op_star
id|codec
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|proc
id|snd_info_entry_t
op_star
id|proc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_ac97_template
r_struct
id|_snd_ac97_template
(brace
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
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
multiline_comment|/* assigned PCI device - used for quirks */
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
DECL|member|scaps
r_int
r_int
id|scaps
suffix:semicolon
multiline_comment|/* driver capabilities */
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
)brace
suffix:semicolon
DECL|struct|_snd_ac97
r_struct
id|_snd_ac97
(brace
multiline_comment|/* -- lowlevel (hardware) driver specific -- */
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
DECL|member|bus
id|ac97_bus_t
op_star
id|bus
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
multiline_comment|/* assigned PCI device - used for quirks */
DECL|member|proc
id|snd_info_entry_t
op_star
id|proc
suffix:semicolon
DECL|member|proc_regs
id|snd_info_entry_t
op_star
id|proc_regs
suffix:semicolon
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
DECL|member|reg_mutex
r_struct
id|semaphore
id|reg_mutex
suffix:semicolon
DECL|member|page_mutex
r_struct
id|semaphore
id|page_mutex
suffix:semicolon
multiline_comment|/* mutex for AD18xx multi-codecs and paging (2.3) */
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
op_ge
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
DECL|function|ac97_can_spdif
r_static
r_inline
r_int
id|ac97_can_spdif
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
id|AC97_EI_SPDIF
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/* functions */
r_int
id|snd_ac97_bus
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|num
comma
id|ac97_bus_ops_t
op_star
id|ops
comma
r_void
op_star
id|private_data
comma
id|ac97_bus_t
op_star
op_star
id|rbus
)paren
suffix:semicolon
multiline_comment|/* create new AC97 bus */
r_int
id|snd_ac97_mixer
c_func
(paren
id|ac97_bus_t
op_star
id|bus
comma
id|ac97_template_t
op_star
r_template
comma
id|ac97_t
op_star
op_star
id|rac97
)paren
suffix:semicolon
multiline_comment|/* create mixer controls */
r_const
r_char
op_star
id|snd_ac97_get_short_name
c_func
(paren
id|ac97_t
op_star
id|ac97
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
multiline_comment|/* quirk types */
r_enum
(brace
DECL|enumerator|AC97_TUNE_DEFAULT
id|AC97_TUNE_DEFAULT
op_assign
op_minus
l_int|1
comma
multiline_comment|/* use default from quirk list (not valid in list) */
DECL|enumerator|AC97_TUNE_NONE
id|AC97_TUNE_NONE
op_assign
l_int|0
comma
multiline_comment|/* nothing extra to do */
DECL|enumerator|AC97_TUNE_HP_ONLY
id|AC97_TUNE_HP_ONLY
comma
multiline_comment|/* headphone (true line-out) control as master only */
DECL|enumerator|AC97_TUNE_SWAP_HP
id|AC97_TUNE_SWAP_HP
comma
multiline_comment|/* swap headphone and master controls */
DECL|enumerator|AC97_TUNE_SWAP_SURROUND
id|AC97_TUNE_SWAP_SURROUND
comma
multiline_comment|/* swap master and surround controls */
DECL|enumerator|AC97_TUNE_AD_SHARING
id|AC97_TUNE_AD_SHARING
comma
multiline_comment|/* for AD1985, turn on OMS bit and use headphone */
DECL|enumerator|AC97_TUNE_ALC_JACK
id|AC97_TUNE_ALC_JACK
comma
multiline_comment|/* for Realtek, enable JACK detection */
DECL|enumerator|AC97_TUNE_INV_EAPD
id|AC97_TUNE_INV_EAPD
comma
multiline_comment|/* inverted EAPD implementation */
DECL|enumerator|AC97_TUNE_MUTE_LED
id|AC97_TUNE_MUTE_LED
comma
multiline_comment|/* EAPD bit works as mute LED */
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
multiline_comment|/* PCI vendor id */
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* PCI device id */
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
multiline_comment|/* device id bit mask, 0 = accept all */
DECL|member|codec_id
r_int
r_int
id|codec_id
suffix:semicolon
multiline_comment|/* codec id (if any), 0 = accept all */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name shown as info */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* quirk type above */
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
comma
r_const
r_char
op_star
id|override
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
r_int
id|snd_ac97_pcm_assign
c_func
(paren
id|ac97_bus_t
op_star
id|ac97
comma
r_int
r_int
id|pcms_count
comma
r_const
r_struct
id|ac97_pcm
op_star
id|pcms
)paren
suffix:semicolon
r_int
id|snd_ac97_pcm_open
c_func
(paren
r_struct
id|ac97_pcm
op_star
id|pcm
comma
r_int
r_int
id|rate
comma
r_enum
id|ac97_pcm_cfg
id|cfg
comma
r_int
r_int
id|slots
)paren
suffix:semicolon
r_int
id|snd_ac97_pcm_close
c_func
(paren
r_struct
id|ac97_pcm
op_star
id|pcm
)paren
suffix:semicolon
r_int
id|snd_ac97_pcm_double_rate_rules
c_func
(paren
id|snd_pcm_runtime_t
op_star
id|runtime
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_AC97_CODEC_H */
eof
