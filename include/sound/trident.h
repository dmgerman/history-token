macro_line|#ifndef __SOUND_TRIDENT_H
DECL|macro|__SOUND_TRIDENT_H
mdefine_line|#define __SOUND_TRIDENT_H
multiline_comment|/*&n; *  audio@tridentmicro.com&n; *  Fri Feb 19 15:55:28 MST 1999&n; *  Definitions for Trident 4DWave DX/NX chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;pcm.h&quot;
macro_line|#include &quot;mpu401.h&quot;
macro_line|#include &quot;ac97_codec.h&quot;
macro_line|#include &quot;seq_midi_emul.h&quot;
macro_line|#include &quot;seq_device.h&quot;
macro_line|#include &quot;util_mem.h&quot;
singleline_comment|//#include &quot;ainstr_iw.h&quot;
singleline_comment|//#include &quot;ainstr_gf1.h&quot;
macro_line|#include &quot;ainstr_simple.h&quot;
macro_line|#ifndef PCI_VENDOR_ID_TRIDENT
DECL|macro|PCI_VENDOR_ID_TRIDENT
mdefine_line|#define PCI_VENDOR_ID_TRIDENT&t;&t;0x1023
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TRIDENT_4DWAVE_DX 
DECL|macro|PCI_DEVICE_ID_TRIDENT_4DWAVE_DX
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_4DWAVE_DX&t;0x2000
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TRIDENT_4DWAVE_NX 
DECL|macro|PCI_DEVICE_ID_TRIDENT_4DWAVE_NX
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_4DWAVE_NX&t;0x2001
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_SI
DECL|macro|PCI_VENDOR_ID_SI
mdefine_line|#define PCI_VENDOR_ID_SI&t;&t;0x1039
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_7018
DECL|macro|PCI_DEVICE_ID_SI_7018
mdefine_line|#define PCI_DEVICE_ID_SI_7018&t;&t;0x7018
macro_line|#endif
DECL|macro|TRIDENT_DEVICE_ID_DX
mdefine_line|#define TRIDENT_DEVICE_ID_DX&t;&t;((PCI_VENDOR_ID_TRIDENT&lt;&lt;16)|PCI_DEVICE_ID_TRIDENT_4DWAVE_DX)
DECL|macro|TRIDENT_DEVICE_ID_NX
mdefine_line|#define TRIDENT_DEVICE_ID_NX&t;&t;((PCI_VENDOR_ID_TRIDENT&lt;&lt;16)|PCI_DEVICE_ID_TRIDENT_4DWAVE_NX)
DECL|macro|TRIDENT_DEVICE_ID_SI7018
mdefine_line|#define TRIDENT_DEVICE_ID_SI7018&t;((PCI_VENDOR_ID_SI&lt;&lt;16)|PCI_DEVICE_ID_SI_7018)
multiline_comment|/* Trident chipsets have 1GB memory limit */
macro_line|#ifdef __alpha__
DECL|macro|TRIDENT_DMA_TYPE
mdefine_line|#define TRIDENT_DMA_TYPE        SNDRV_DMA_TYPE_PCI_16MB
DECL|macro|TRIDENT_GFP_FLAGS
mdefine_line|#define TRIDENT_GFP_FLAGS&t;GFP_DMA
macro_line|#else
DECL|macro|TRIDENT_DMA_TYPE
mdefine_line|#define TRIDENT_DMA_TYPE        SNDRV_DMA_TYPE_PCI
macro_line|#if defined(__i386__) &amp;&amp; !defined(CONFIG_1GB)
DECL|macro|TRIDENT_GFP_FLAGS
mdefine_line|#define TRIDENT_GFP_FLAGS&t;GFP_DMA
macro_line|#else
DECL|macro|TRIDENT_GFP_FLAGS
mdefine_line|#define TRIDENT_GFP_FLAGS&t;0
macro_line|#endif
macro_line|#endif
DECL|macro|SNDRV_SEQ_DEV_ID_TRIDENT
mdefine_line|#define SNDRV_SEQ_DEV_ID_TRIDENT&t;&t;&t;&quot;trident-synth&quot;
DECL|macro|SNDRV_TRIDENT_VOICE_TYPE_PCM
mdefine_line|#define SNDRV_TRIDENT_VOICE_TYPE_PCM&t;&t;0
DECL|macro|SNDRV_TRIDENT_VOICE_TYPE_SYNTH
mdefine_line|#define SNDRV_TRIDENT_VOICE_TYPE_SYNTH&t;&t;1
DECL|macro|SNDRV_TRIDENT_VOICE_TYPE_MIDI
mdefine_line|#define SNDRV_TRIDENT_VOICE_TYPE_MIDI&t;&t;2
DECL|macro|SNDRV_TRIDENT_VFLG_RUNNING
mdefine_line|#define SNDRV_TRIDENT_VFLG_RUNNING&t;&t;(1&lt;&lt;0)
multiline_comment|/* TLB code constants */
DECL|macro|SNDRV_TRIDENT_PAGE_SIZE
mdefine_line|#define SNDRV_TRIDENT_PAGE_SIZE&t;&t;&t;4096
DECL|macro|SNDRV_TRIDENT_PAGE_SHIFT
mdefine_line|#define SNDRV_TRIDENT_PAGE_SHIFT&t;&t;&t;12
DECL|macro|SNDRV_TRIDENT_PAGE_MASK
mdefine_line|#define SNDRV_TRIDENT_PAGE_MASK&t;&t;&t;((1&lt;&lt;SNDRV_TRIDENT_PAGE_SHIFT)-1)
DECL|macro|SNDRV_TRIDENT_MAX_PAGES
mdefine_line|#define SNDRV_TRIDENT_MAX_PAGES&t;&t;&t;4096
multiline_comment|/*&n; * Direct registers&n; */
DECL|macro|TRID_REG
mdefine_line|#define TRID_REG(trident, x) ((trident)-&gt;port + (x))
DECL|macro|ID_4DWAVE_DX
mdefine_line|#define ID_4DWAVE_DX        0x2000
DECL|macro|ID_4DWAVE_NX
mdefine_line|#define ID_4DWAVE_NX        0x2001
multiline_comment|/* Bank definitions */
DECL|macro|T4D_BANK_A
mdefine_line|#define T4D_BANK_A&t;0
DECL|macro|T4D_BANK_B
mdefine_line|#define T4D_BANK_B&t;1
DECL|macro|T4D_NUM_BANKS
mdefine_line|#define T4D_NUM_BANKS&t;2
multiline_comment|/* Register definitions */
multiline_comment|/* Global registers */
DECL|enum|global_control_bits
r_enum
id|global_control_bits
(brace
DECL|enumerator|CHANNEL_IDX
DECL|enumerator|OVERRUN_IE
id|CHANNEL_IDX
op_assign
l_int|0x0000003f
comma
id|OVERRUN_IE
op_assign
l_int|0x00000400
comma
DECL|enumerator|UNDERRUN_IE
DECL|enumerator|ENDLP_IE
id|UNDERRUN_IE
op_assign
l_int|0x00000800
comma
id|ENDLP_IE
op_assign
l_int|0x00001000
comma
DECL|enumerator|MIDLP_IE
DECL|enumerator|ETOG_IE
id|MIDLP_IE
op_assign
l_int|0x00002000
comma
id|ETOG_IE
op_assign
l_int|0x00004000
comma
DECL|enumerator|EDROP_IE
DECL|enumerator|BANK_B_EN
id|EDROP_IE
op_assign
l_int|0x00008000
comma
id|BANK_B_EN
op_assign
l_int|0x00010000
)brace
suffix:semicolon
DECL|enum|miscint_bits
r_enum
id|miscint_bits
(brace
DECL|enumerator|PB_UNDERRUN_IRQ
DECL|enumerator|REC_OVERRUN_IRQ
id|PB_UNDERRUN_IRQ
op_assign
l_int|0x00000001
comma
id|REC_OVERRUN_IRQ
op_assign
l_int|0x00000002
comma
DECL|enumerator|SB_IRQ
DECL|enumerator|MPU401_IRQ
id|SB_IRQ
op_assign
l_int|0x00000004
comma
id|MPU401_IRQ
op_assign
l_int|0x00000008
comma
DECL|enumerator|OPL3_IRQ
DECL|enumerator|ADDRESS_IRQ
id|OPL3_IRQ
op_assign
l_int|0x00000010
comma
id|ADDRESS_IRQ
op_assign
l_int|0x00000020
comma
DECL|enumerator|ENVELOPE_IRQ
DECL|enumerator|PB_UNDERRUN
id|ENVELOPE_IRQ
op_assign
l_int|0x00000040
comma
id|PB_UNDERRUN
op_assign
l_int|0x00000100
comma
DECL|enumerator|REC_OVERRUN
DECL|enumerator|MIXER_UNDERFLOW
id|REC_OVERRUN
op_assign
l_int|0x00000200
comma
id|MIXER_UNDERFLOW
op_assign
l_int|0x00000400
comma
DECL|enumerator|MIXER_OVERFLOW
DECL|enumerator|NX_SB_IRQ_DISABLE
id|MIXER_OVERFLOW
op_assign
l_int|0x00000800
comma
id|NX_SB_IRQ_DISABLE
op_assign
l_int|0x00001000
comma
DECL|enumerator|ST_TARGET_REACHED
id|ST_TARGET_REACHED
op_assign
l_int|0x00008000
comma
DECL|enumerator|PB_24K_MODE
DECL|enumerator|ST_IRQ_EN
id|PB_24K_MODE
op_assign
l_int|0x00010000
comma
id|ST_IRQ_EN
op_assign
l_int|0x00800000
comma
DECL|enumerator|ACGPIO_IRQ
id|ACGPIO_IRQ
op_assign
l_int|0x01000000
)brace
suffix:semicolon
multiline_comment|/* T2 legacy dma control registers. */
DECL|macro|LEGACY_DMAR0
mdefine_line|#define LEGACY_DMAR0                0x00  
singleline_comment|// ADR0
DECL|macro|LEGACY_DMAR4
mdefine_line|#define LEGACY_DMAR4                0x04  
singleline_comment|// CNT0
DECL|macro|LEGACY_DMAR6
mdefine_line|#define LEGACY_DMAR6&t;&t;    0x06  
singleline_comment|// CNT0 - High bits
DECL|macro|LEGACY_DMAR11
mdefine_line|#define LEGACY_DMAR11               0x0b  
singleline_comment|// MOD 
DECL|macro|LEGACY_DMAR15
mdefine_line|#define LEGACY_DMAR15               0x0f  
singleline_comment|// MMR 
DECL|macro|T4D_START_A
mdefine_line|#define T4D_START_A&t;&t;     0x80
DECL|macro|T4D_STOP_A
mdefine_line|#define T4D_STOP_A&t;&t;     0x84
DECL|macro|T4D_DLY_A
mdefine_line|#define T4D_DLY_A&t;&t;     0x88
DECL|macro|T4D_SIGN_CSO_A
mdefine_line|#define T4D_SIGN_CSO_A&t;&t;     0x8c
DECL|macro|T4D_CSPF_A
mdefine_line|#define T4D_CSPF_A&t;&t;     0x90
DECL|macro|T4D_CSPF_B
mdefine_line|#define T4D_CSPF_B&t;&t;     0xbc
DECL|macro|T4D_CEBC_A
mdefine_line|#define T4D_CEBC_A&t;&t;     0x94
DECL|macro|T4D_AINT_A
mdefine_line|#define T4D_AINT_A&t;&t;     0x98
DECL|macro|T4D_AINTEN_A
mdefine_line|#define T4D_AINTEN_A&t;&t;     0x9c
DECL|macro|T4D_LFO_GC_CIR
mdefine_line|#define T4D_LFO_GC_CIR               0xa0
DECL|macro|T4D_MUSICVOL_WAVEVOL
mdefine_line|#define T4D_MUSICVOL_WAVEVOL         0xa8
DECL|macro|T4D_SBDELTA_DELTA_R
mdefine_line|#define T4D_SBDELTA_DELTA_R          0xac
DECL|macro|T4D_MISCINT
mdefine_line|#define T4D_MISCINT                  0xb0
DECL|macro|T4D_START_B
mdefine_line|#define T4D_START_B                  0xb4
DECL|macro|T4D_STOP_B
mdefine_line|#define T4D_STOP_B                   0xb8
DECL|macro|T4D_SBBL_SBCL
mdefine_line|#define T4D_SBBL_SBCL                0xc0
DECL|macro|T4D_SBCTRL_SBE2R_SBDD
mdefine_line|#define T4D_SBCTRL_SBE2R_SBDD        0xc4
DECL|macro|T4D_STIMER
mdefine_line|#define T4D_STIMER&t;&t;     0xc8
DECL|macro|T4D_AINT_B
mdefine_line|#define T4D_AINT_B                   0xd8
DECL|macro|T4D_AINTEN_B
mdefine_line|#define T4D_AINTEN_B                 0xdc
DECL|macro|T4D_RCI
mdefine_line|#define T4D_RCI                      0x70
multiline_comment|/* MPU-401 UART */
DECL|macro|T4D_MPU401_BASE
mdefine_line|#define T4D_MPU401_BASE             0x20
DECL|macro|T4D_MPUR0
mdefine_line|#define T4D_MPUR0                   0x20
DECL|macro|T4D_MPUR1
mdefine_line|#define T4D_MPUR1                   0x21
DECL|macro|T4D_MPUR2
mdefine_line|#define T4D_MPUR2                   0x22
DECL|macro|T4D_MPUR3
mdefine_line|#define T4D_MPUR3                   0x23
multiline_comment|/* S/PDIF Registers */
DECL|macro|NX_SPCTRL_SPCSO
mdefine_line|#define NX_SPCTRL_SPCSO             0x24
DECL|macro|NX_SPLBA
mdefine_line|#define NX_SPLBA                    0x28
DECL|macro|NX_SPESO
mdefine_line|#define NX_SPESO                    0x2c
DECL|macro|NX_SPCSTATUS
mdefine_line|#define NX_SPCSTATUS                0x64
multiline_comment|/* NX Specific Registers */
DECL|macro|NX_TLBC
mdefine_line|#define NX_TLBC                     0x6c
multiline_comment|/* Channel Registers */
DECL|macro|CH_START
mdefine_line|#define CH_START&t;&t;    0xe0
DECL|macro|CH_DX_CSO_ALPHA_FMS
mdefine_line|#define CH_DX_CSO_ALPHA_FMS         0xe0
DECL|macro|CH_DX_ESO_DELTA
mdefine_line|#define CH_DX_ESO_DELTA             0xe8
DECL|macro|CH_DX_FMC_RVOL_CVOL
mdefine_line|#define CH_DX_FMC_RVOL_CVOL         0xec
DECL|macro|CH_NX_DELTA_CSO
mdefine_line|#define CH_NX_DELTA_CSO             0xe0
DECL|macro|CH_NX_DELTA_ESO
mdefine_line|#define CH_NX_DELTA_ESO             0xe8
DECL|macro|CH_NX_ALPHA_FMS_FMC_RVOL_CVOL
mdefine_line|#define CH_NX_ALPHA_FMS_FMC_RVOL_CVOL 0xec
DECL|macro|CH_LBA
mdefine_line|#define CH_LBA                      0xe4
DECL|macro|CH_GVSEL_PAN_VOL_CTRL_EC
mdefine_line|#define CH_GVSEL_PAN_VOL_CTRL_EC    0xf0
DECL|macro|CH_EBUF1
mdefine_line|#define CH_EBUF1                    0xf4
DECL|macro|CH_EBUF2
mdefine_line|#define CH_EBUF2                    0xf8
multiline_comment|/* AC-97 Registers */
DECL|macro|DX_ACR0_AC97_W
mdefine_line|#define DX_ACR0_AC97_W              0x40
DECL|macro|DX_ACR1_AC97_R
mdefine_line|#define DX_ACR1_AC97_R              0x44
DECL|macro|DX_ACR2_AC97_COM_STAT
mdefine_line|#define DX_ACR2_AC97_COM_STAT       0x48
DECL|macro|NX_ACR0_AC97_COM_STAT
mdefine_line|#define NX_ACR0_AC97_COM_STAT       0x40
DECL|macro|NX_ACR1_AC97_W
mdefine_line|#define NX_ACR1_AC97_W              0x44
DECL|macro|NX_ACR2_AC97_R_PRIMARY
mdefine_line|#define NX_ACR2_AC97_R_PRIMARY      0x48
DECL|macro|NX_ACR3_AC97_R_SECONDARY
mdefine_line|#define NX_ACR3_AC97_R_SECONDARY    0x4c
DECL|macro|SI_AC97_WRITE
mdefine_line|#define SI_AC97_WRITE&t;&t;    0x40
DECL|macro|SI_AC97_READ
mdefine_line|#define SI_AC97_READ&t;&t;    0x44
DECL|macro|SI_SERIAL_INTF_CTRL
mdefine_line|#define SI_SERIAL_INTF_CTRL&t;    0x48
DECL|macro|SI_AC97_GPIO
mdefine_line|#define SI_AC97_GPIO&t;&t;    0x4c
DECL|macro|SI_ASR0
mdefine_line|#define SI_ASR0&t;&t;&t;    0x50
DECL|macro|SI_SPDIF_CS
mdefine_line|#define SI_SPDIF_CS&t;&t;    0x70
DECL|macro|SI_GPIO
mdefine_line|#define SI_GPIO&t;&t;&t;    0x7c
DECL|enum|trident_nx_ac97_bits
r_enum
id|trident_nx_ac97_bits
(brace
multiline_comment|/* ACR1-3 */
DECL|enumerator|NX_AC97_BUSY_WRITE
id|NX_AC97_BUSY_WRITE
op_assign
l_int|0x0800
comma
DECL|enumerator|NX_AC97_BUSY_READ
id|NX_AC97_BUSY_READ
op_assign
l_int|0x0800
comma
DECL|enumerator|NX_AC97_BUSY_DATA
id|NX_AC97_BUSY_DATA
op_assign
l_int|0x0400
comma
DECL|enumerator|NX_AC97_WRITE_SECONDARY
id|NX_AC97_WRITE_SECONDARY
op_assign
l_int|0x0100
comma
multiline_comment|/* ACR0 */
DECL|enumerator|NX_AC97_SECONDARY_READY
id|NX_AC97_SECONDARY_READY
op_assign
l_int|0x0040
comma
DECL|enumerator|NX_AC97_SECONDARY_RECORD
id|NX_AC97_SECONDARY_RECORD
op_assign
l_int|0x0020
comma
DECL|enumerator|NX_AC97_SURROUND_OUTPUT
id|NX_AC97_SURROUND_OUTPUT
op_assign
l_int|0x0010
comma
DECL|enumerator|NX_AC97_PRIMARY_READY
id|NX_AC97_PRIMARY_READY
op_assign
l_int|0x0008
comma
DECL|enumerator|NX_AC97_PRIMARY_RECORD
id|NX_AC97_PRIMARY_RECORD
op_assign
l_int|0x0004
comma
DECL|enumerator|NX_AC97_PCM_OUTPUT
id|NX_AC97_PCM_OUTPUT
op_assign
l_int|0x0002
comma
DECL|enumerator|NX_AC97_WARM_RESET
id|NX_AC97_WARM_RESET
op_assign
l_int|0x0001
)brace
suffix:semicolon
DECL|enum|trident_dx_ac97_bits
r_enum
id|trident_dx_ac97_bits
(brace
DECL|enumerator|DX_AC97_BUSY_WRITE
id|DX_AC97_BUSY_WRITE
op_assign
l_int|0x8000
comma
DECL|enumerator|DX_AC97_BUSY_READ
id|DX_AC97_BUSY_READ
op_assign
l_int|0x8000
comma
DECL|enumerator|DX_AC97_READY
id|DX_AC97_READY
op_assign
l_int|0x0010
comma
DECL|enumerator|DX_AC97_RECORD
id|DX_AC97_RECORD
op_assign
l_int|0x0008
comma
DECL|enumerator|DX_AC97_PLAYBACK
id|DX_AC97_PLAYBACK
op_assign
l_int|0x0002
)brace
suffix:semicolon
DECL|enum|sis7018_ac97_bits
r_enum
id|sis7018_ac97_bits
(brace
DECL|enumerator|SI_AC97_BUSY_WRITE
id|SI_AC97_BUSY_WRITE
op_assign
l_int|0x00008000
comma
DECL|enumerator|SI_AC97_AUDIO_BUSY
id|SI_AC97_AUDIO_BUSY
op_assign
l_int|0x00004000
comma
DECL|enumerator|SI_AC97_MODEM_BUSY
id|SI_AC97_MODEM_BUSY
op_assign
l_int|0x00002000
comma
DECL|enumerator|SI_AC97_BUSY_READ
id|SI_AC97_BUSY_READ
op_assign
l_int|0x00008000
comma
DECL|enumerator|SI_AC97_SECONDARY
id|SI_AC97_SECONDARY
op_assign
l_int|0x00000080
comma
)brace
suffix:semicolon
DECL|enum|serial_intf_ctrl_bits
r_enum
id|serial_intf_ctrl_bits
(brace
DECL|enumerator|WARM_RESET
id|WARM_RESET
op_assign
l_int|0x00000001
comma
DECL|enumerator|COLD_RESET
id|COLD_RESET
op_assign
l_int|0x00000002
comma
DECL|enumerator|I2S_CLOCK
id|I2S_CLOCK
op_assign
l_int|0x00000004
comma
DECL|enumerator|PCM_SEC_AC97
id|PCM_SEC_AC97
op_assign
l_int|0x00000008
comma
DECL|enumerator|AC97_DBL_RATE
id|AC97_DBL_RATE
op_assign
l_int|0x00000010
comma
DECL|enumerator|SPDIF_EN
id|SPDIF_EN
op_assign
l_int|0x00000020
comma
DECL|enumerator|I2S_OUTPUT_EN
id|I2S_OUTPUT_EN
op_assign
l_int|0x00000040
comma
DECL|enumerator|I2S_INPUT_EN
id|I2S_INPUT_EN
op_assign
l_int|0x00000080
comma
DECL|enumerator|PCMIN
id|PCMIN
op_assign
l_int|0x00000100
comma
DECL|enumerator|LINE1IN
id|LINE1IN
op_assign
l_int|0x00000200
comma
DECL|enumerator|MICIN
id|MICIN
op_assign
l_int|0x00000400
comma
DECL|enumerator|LINE2IN
id|LINE2IN
op_assign
l_int|0x00000800
comma
DECL|enumerator|HEAD_SET_IN
id|HEAD_SET_IN
op_assign
l_int|0x00001000
comma
DECL|enumerator|GPIOIN
id|GPIOIN
op_assign
l_int|0x00002000
comma
multiline_comment|/* 7018 spec says id = 01 but the demo board routed to 10&n;&t;   SECONDARY_ID= 0x00004000, */
DECL|enumerator|SECONDARY_ID
id|SECONDARY_ID
op_assign
l_int|0x00004000
comma
DECL|enumerator|PCMOUT
id|PCMOUT
op_assign
l_int|0x00010000
comma
DECL|enumerator|SURROUT
id|SURROUT
op_assign
l_int|0x00020000
comma
DECL|enumerator|CENTEROUT
id|CENTEROUT
op_assign
l_int|0x00040000
comma
DECL|enumerator|LFEOUT
id|LFEOUT
op_assign
l_int|0x00080000
comma
DECL|enumerator|LINE1OUT
id|LINE1OUT
op_assign
l_int|0x00100000
comma
DECL|enumerator|LINE2OUT
id|LINE2OUT
op_assign
l_int|0x00200000
comma
DECL|enumerator|GPIOOUT
id|GPIOOUT
op_assign
l_int|0x00400000
comma
DECL|enumerator|SI_AC97_PRIMARY_READY
id|SI_AC97_PRIMARY_READY
op_assign
l_int|0x01000000
comma
DECL|enumerator|SI_AC97_SECONDARY_READY
id|SI_AC97_SECONDARY_READY
op_assign
l_int|0x02000000
comma
DECL|enumerator|SI_AC97_POWERDOWN
id|SI_AC97_POWERDOWN
op_assign
l_int|0x04000000
comma
)brace
suffix:semicolon
multiline_comment|/* PCM defaults */
DECL|macro|T4D_DEFAULT_PCM_VOL
mdefine_line|#define T4D_DEFAULT_PCM_VOL&t;10&t;/* 0 - 255 */
DECL|macro|T4D_DEFAULT_PCM_PAN
mdefine_line|#define T4D_DEFAULT_PCM_PAN&t;0&t;/* 0 - 127 */
DECL|macro|T4D_DEFAULT_PCM_RVOL
mdefine_line|#define T4D_DEFAULT_PCM_RVOL&t;127&t;/* 0 - 127 */
DECL|macro|T4D_DEFAULT_PCM_CVOL
mdefine_line|#define T4D_DEFAULT_PCM_CVOL&t;127&t;/* 0 - 127 */
DECL|typedef|trident_t
r_typedef
r_struct
id|_snd_trident
id|trident_t
suffix:semicolon
DECL|typedef|snd_trident_voice_t
r_typedef
r_struct
id|_snd_trident_voice
id|snd_trident_voice_t
suffix:semicolon
DECL|typedef|snd_trident_pcm_mixer_t
r_typedef
r_struct
id|_snd_trident_pcm_mixer
id|snd_trident_pcm_mixer_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|sample_start
r_void
(paren
op_star
id|sample_start
)paren
(paren
id|trident_t
op_star
id|gus
comma
id|snd_trident_voice_t
op_star
id|voice
comma
id|snd_seq_position_t
id|position
)paren
suffix:semicolon
DECL|member|sample_stop
r_void
(paren
op_star
id|sample_stop
)paren
(paren
id|trident_t
op_star
id|gus
comma
id|snd_trident_voice_t
op_star
id|voice
comma
id|snd_seq_stop_mode_t
id|mode
)paren
suffix:semicolon
DECL|member|sample_freq
r_void
(paren
op_star
id|sample_freq
)paren
(paren
id|trident_t
op_star
id|gus
comma
id|snd_trident_voice_t
op_star
id|voice
comma
id|snd_seq_frequency_t
id|freq
)paren
suffix:semicolon
DECL|member|sample_volume
r_void
(paren
op_star
id|sample_volume
)paren
(paren
id|trident_t
op_star
id|gus
comma
id|snd_trident_voice_t
op_star
id|voice
comma
id|snd_seq_ev_volume_t
op_star
id|volume
)paren
suffix:semicolon
DECL|member|sample_loop
r_void
(paren
op_star
id|sample_loop
)paren
(paren
id|trident_t
op_star
id|card
comma
id|snd_trident_voice_t
op_star
id|voice
comma
id|snd_seq_ev_loop_t
op_star
id|loop
)paren
suffix:semicolon
DECL|member|sample_pos
r_void
(paren
op_star
id|sample_pos
)paren
(paren
id|trident_t
op_star
id|card
comma
id|snd_trident_voice_t
op_star
id|voice
comma
id|snd_seq_position_t
id|position
)paren
suffix:semicolon
DECL|member|sample_private1
r_void
(paren
op_star
id|sample_private1
)paren
(paren
id|trident_t
op_star
id|card
comma
id|snd_trident_voice_t
op_star
id|voice
comma
r_int
r_char
op_star
id|data
)paren
suffix:semicolon
DECL|typedef|snd_trident_sample_ops_t
)brace
id|snd_trident_sample_ops_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|chset
id|snd_midi_channel_set_t
op_star
id|chset
suffix:semicolon
DECL|member|trident
id|trident_t
op_star
id|trident
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* operation mode */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* sequencer client number */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* sequencer port number */
DECL|member|midi_has_voices
r_int
id|midi_has_voices
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|snd_trident_port_t
)brace
id|snd_trident_port_t
suffix:semicolon
DECL|struct|snd_trident_memblk_arg
r_typedef
r_struct
id|snd_trident_memblk_arg
(brace
DECL|member|first_page
DECL|member|last_page
r_int
id|first_page
comma
id|last_page
suffix:semicolon
DECL|typedef|snd_trident_memblk_arg_t
)brace
id|snd_trident_memblk_arg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|entries
r_int
r_int
op_star
id|entries
suffix:semicolon
multiline_comment|/* 16k-aligned TLB table */
DECL|member|entries_dmaaddr
id|dma_addr_t
id|entries_dmaaddr
suffix:semicolon
multiline_comment|/* 16k-aligned PCI address to TLB table */
DECL|member|shadow_entries
r_int
r_int
op_star
id|shadow_entries
suffix:semicolon
multiline_comment|/* shadow entries with virtual addresses */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* pointer for table calloc */
DECL|member|buffer_dmaaddr
id|dma_addr_t
id|buffer_dmaaddr
suffix:semicolon
multiline_comment|/* not accessible PCI BUS physical address */
DECL|member|memhdr
id|snd_util_memhdr_t
op_star
id|memhdr
suffix:semicolon
multiline_comment|/* page allocation list */
DECL|member|silent_page
r_void
op_star
id|silent_page
suffix:semicolon
multiline_comment|/* silent page */
DECL|member|silent_page_dmaaddr
id|dma_addr_t
id|silent_page_dmaaddr
suffix:semicolon
multiline_comment|/* not accessible PCI BUS physical address */
DECL|typedef|snd_trident_tlb_t
)brace
id|snd_trident_tlb_t
suffix:semicolon
DECL|struct|_snd_trident_voice
r_struct
id|_snd_trident_voice
(brace
DECL|member|number
r_int
r_int
id|number
suffix:semicolon
DECL|member|use
r_int
id|use
suffix:colon
l_int|1
comma
DECL|member|pcm
id|pcm
suffix:colon
l_int|1
comma
DECL|member|synth
id|synth
suffix:colon
l_int|1
comma
DECL|member|midi
id|midi
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|client
r_int
r_char
id|client
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
DECL|member|index
r_int
r_char
id|index
suffix:semicolon
DECL|member|instr
id|snd_seq_instr_t
id|instr
suffix:semicolon
DECL|member|sample_ops
id|snd_trident_sample_ops_t
op_star
id|sample_ops
suffix:semicolon
multiline_comment|/* channel parameters */
DECL|member|CSO
r_int
r_int
id|CSO
suffix:semicolon
multiline_comment|/* 24 bits (16 on DX) */
DECL|member|ESO
r_int
r_int
id|ESO
suffix:semicolon
multiline_comment|/* 24 bits (16 on DX) */
DECL|member|LBA
r_int
r_int
id|LBA
suffix:semicolon
multiline_comment|/* 30 bits */
DECL|member|EC
r_int
r_int
id|EC
suffix:semicolon
multiline_comment|/* 12 bits */
DECL|member|Alpha
r_int
r_int
id|Alpha
suffix:semicolon
multiline_comment|/* 12 bits */
DECL|member|Delta
r_int
r_int
id|Delta
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|Attribute
r_int
r_int
id|Attribute
suffix:semicolon
multiline_comment|/* 16 bits - SiS 7018 */
DECL|member|Vol
r_int
r_int
id|Vol
suffix:semicolon
multiline_comment|/* 12 bits (6.6) */
DECL|member|Pan
r_int
r_char
id|Pan
suffix:semicolon
multiline_comment|/* 7 bits (1.4.2) */
DECL|member|GVSel
r_int
r_char
id|GVSel
suffix:semicolon
multiline_comment|/* 1 bit */
DECL|member|RVol
r_int
r_char
id|RVol
suffix:semicolon
multiline_comment|/* 7 bits (5.2) */
DECL|member|CVol
r_int
r_char
id|CVol
suffix:semicolon
multiline_comment|/* 7 bits (5.2) */
DECL|member|FMC
r_int
r_char
id|FMC
suffix:semicolon
multiline_comment|/* 2 bits */
DECL|member|CTRL
r_int
r_char
id|CTRL
suffix:semicolon
multiline_comment|/* 4 bits */
DECL|member|FMS
r_int
r_char
id|FMS
suffix:semicolon
multiline_comment|/* 4 bits */
DECL|member|LFO
r_int
r_char
id|LFO
suffix:semicolon
multiline_comment|/* 8 bits */
DECL|member|negCSO
r_int
r_int
id|negCSO
suffix:semicolon
multiline_comment|/* nonzero - use negative CSO */
DECL|member|memblk
id|snd_util_memblk_t
op_star
id|memblk
suffix:semicolon
multiline_comment|/* memory block if TLB enabled */
multiline_comment|/* PCM data */
DECL|member|trident
id|trident_t
op_star
id|trident
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|extra
id|snd_trident_voice_t
op_star
id|extra
suffix:semicolon
multiline_comment|/* extra PCM voice (acts as interrupt generator) */
DECL|member|running
r_int
id|running
suffix:colon
l_int|1
comma
DECL|member|capture
id|capture
suffix:colon
l_int|1
comma
DECL|member|spdif
id|spdif
suffix:colon
l_int|1
comma
DECL|member|foldback
id|foldback
suffix:colon
l_int|1
suffix:semicolon
DECL|member|foldback_chan
r_int
id|foldback_chan
suffix:semicolon
multiline_comment|/* foldback subdevice number */
DECL|member|stimer
r_int
r_int
id|stimer
suffix:semicolon
multiline_comment|/* global sample timer (to detect spurious interrupts) */
DECL|member|spurious_threshold
r_int
r_int
id|spurious_threshold
suffix:semicolon
multiline_comment|/* spurious threshold */
multiline_comment|/* --- */
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
id|snd_trident_voice_t
op_star
id|voice
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_4dwave
r_struct
id|_snd_4dwave
(brace
DECL|member|seq_client
r_int
id|seq_client
suffix:semicolon
DECL|member|seq_ports
id|snd_trident_port_t
id|seq_ports
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|simple_ops
id|snd_simple_ops_t
id|simple_ops
suffix:semicolon
DECL|member|ilist
id|snd_seq_kinstr_list_t
op_star
id|ilist
suffix:semicolon
DECL|member|voices
id|snd_trident_voice_t
id|voices
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|ChanSynthCount
r_int
id|ChanSynthCount
suffix:semicolon
multiline_comment|/* number of allocated synth channels */
DECL|member|max_size
r_int
id|max_size
suffix:semicolon
multiline_comment|/* maximum synth memory size in bytes */
DECL|member|current_size
r_int
id|current_size
suffix:semicolon
multiline_comment|/* current allocated synth mem in bytes */
)brace
suffix:semicolon
DECL|struct|_snd_trident_pcm_mixer
r_struct
id|_snd_trident_pcm_mixer
(brace
DECL|member|voice
id|snd_trident_voice_t
op_star
id|voice
suffix:semicolon
multiline_comment|/* active voice */
DECL|member|vol
r_int
r_int
id|vol
suffix:semicolon
multiline_comment|/* front volume */
DECL|member|pan
r_int
r_char
id|pan
suffix:semicolon
multiline_comment|/* pan control */
DECL|member|rvol
r_int
r_char
id|rvol
suffix:semicolon
multiline_comment|/* rear volume */
DECL|member|cvol
r_int
r_char
id|cvol
suffix:semicolon
multiline_comment|/* center volume */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
DECL|member|ctl_vol
id|snd_kcontrol_t
op_star
id|ctl_vol
suffix:semicolon
multiline_comment|/* front volume */
DECL|member|ctl_pan
id|snd_kcontrol_t
op_star
id|ctl_pan
suffix:semicolon
multiline_comment|/* pan */
DECL|member|ctl_rvol
id|snd_kcontrol_t
op_star
id|ctl_rvol
suffix:semicolon
multiline_comment|/* rear volume */
DECL|member|ctl_cvol
id|snd_kcontrol_t
op_star
id|ctl_cvol
suffix:semicolon
multiline_comment|/* center volume */
)brace
suffix:semicolon
DECL|struct|_snd_trident
r_struct
id|_snd_trident
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* device ID */
DECL|member|bDMAStart
r_int
r_char
id|bDMAStart
suffix:semicolon
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
DECL|member|midi_port
r_int
r_int
id|midi_port
suffix:semicolon
DECL|member|spurious_irq_count
r_int
r_int
id|spurious_irq_count
suffix:semicolon
DECL|member|spurious_irq_max_delta
r_int
r_int
id|spurious_irq_max_delta
suffix:semicolon
DECL|member|tlb
id|snd_trident_tlb_t
id|tlb
suffix:semicolon
multiline_comment|/* TLB entries for NX cards */
DECL|member|spdif_ctrl
r_int
r_char
id|spdif_ctrl
suffix:semicolon
DECL|member|spdif_pcm_ctrl
r_int
r_char
id|spdif_pcm_ctrl
suffix:semicolon
DECL|member|spdif_bits
r_int
r_int
id|spdif_bits
suffix:semicolon
DECL|member|spdif_pcm_bits
r_int
r_int
id|spdif_pcm_bits
suffix:semicolon
DECL|member|spdif_pcm_ctl
id|snd_kcontrol_t
op_star
id|spdif_pcm_ctl
suffix:semicolon
multiline_comment|/* S/PDIF settings */
DECL|member|ac97_ctrl
r_int
r_int
id|ac97_ctrl
suffix:semicolon
DECL|member|ChanMap
r_int
r_int
id|ChanMap
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* allocation map for hardware channels */
DECL|member|ChanPCM
r_int
id|ChanPCM
suffix:semicolon
multiline_comment|/* max number of PCM channels */
DECL|member|ChanPCMcnt
r_int
id|ChanPCMcnt
suffix:semicolon
multiline_comment|/* actual number of PCM channels */
DECL|member|synth
r_struct
id|_snd_4dwave
id|synth
suffix:semicolon
multiline_comment|/* synth specific variables */
DECL|member|event_lock
id|spinlock_t
id|event_lock
suffix:semicolon
DECL|member|voice_alloc
id|spinlock_t
id|voice_alloc
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
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
multiline_comment|/* ADC/DAC PCM */
DECL|member|foldback
id|snd_pcm_t
op_star
id|foldback
suffix:semicolon
multiline_comment|/* Foldback PCM */
DECL|member|spdif
id|snd_pcm_t
op_star
id|spdif
suffix:semicolon
multiline_comment|/* SPDIF PCM */
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
DECL|member|seq_dev
id|snd_seq_device_t
op_star
id|seq_dev
suffix:semicolon
DECL|member|ac97
id|ac97_t
op_star
id|ac97
suffix:semicolon
DECL|member|musicvol_wavevol
r_int
r_int
id|musicvol_wavevol
suffix:semicolon
DECL|member|pcm_mixer
id|snd_trident_pcm_mixer_t
id|pcm_mixer
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_trident_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|pcm_streams
comma
r_int
id|pcm_spdif_device
comma
r_int
id|max_wavetable_size
comma
id|trident_t
op_star
op_star
id|rtrident
)paren
suffix:semicolon
r_int
id|snd_trident_free
c_func
(paren
id|trident_t
op_star
id|trident
)paren
suffix:semicolon
r_int
id|snd_trident_pcm
c_func
(paren
id|trident_t
op_star
id|trident
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
id|snd_trident_foldback_pcm
c_func
(paren
id|trident_t
op_star
id|trident
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
id|snd_trident_spdif_pcm
c_func
(paren
id|trident_t
op_star
id|trident
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
id|snd_trident_attach_synthesizer
c_func
(paren
id|trident_t
op_star
id|trident
)paren
suffix:semicolon
r_int
id|snd_trident_detach_synthesizer
c_func
(paren
id|trident_t
op_star
id|trident
)paren
suffix:semicolon
id|snd_trident_voice_t
op_star
id|snd_trident_alloc_voice
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
id|type
comma
r_int
id|client
comma
r_int
id|port
)paren
suffix:semicolon
r_void
id|snd_trident_free_voice
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_trident_voice_t
op_star
id|voice
)paren
suffix:semicolon
r_void
id|snd_trident_start_voice
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
r_int
id|voice
)paren
suffix:semicolon
r_void
id|snd_trident_stop_voice
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
r_int
id|voice
)paren
suffix:semicolon
r_void
id|snd_trident_write_voice_regs
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_trident_voice_t
op_star
id|voice
)paren
suffix:semicolon
r_void
id|snd_trident_clear_voices
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
r_int
id|v_min
comma
r_int
r_int
id|v_max
)paren
suffix:semicolon
multiline_comment|/* TLB memory allocation */
id|snd_util_memblk_t
op_star
id|snd_trident_alloc_pages
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_void
op_star
id|pages
comma
id|dma_addr_t
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_trident_free_pages
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
id|snd_util_memblk_t
op_star
id|snd_trident_synth_alloc
c_func
(paren
id|trident_t
op_star
id|trident
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_trident_synth_free
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
r_int
id|snd_trident_synth_bzero
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
id|offset
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_trident_synth_copy_from_user
c_func
(paren
id|trident_t
op_star
id|trident
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|data
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Power Management */
macro_line|#ifdef CONFIG_PM
r_void
id|snd_trident_suspend
c_func
(paren
id|trident_t
op_star
id|trident
)paren
suffix:semicolon
r_void
id|snd_trident_resume
c_func
(paren
id|trident_t
op_star
id|trident
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SOUND_TRIDENT_H */
eof
