macro_line|#ifndef __YMFPCI_H
DECL|macro|__YMFPCI_H
mdefine_line|#define __YMFPCI_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Definitions for Yahama YMF724/740/744/754 chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *  Direct registers&n; */
multiline_comment|/* #define YMFREG(codec, reg)&t;&t;(codec-&gt;port + YDSXGR_##reg) */
DECL|macro|YDSXGR_INTFLAG
mdefine_line|#define&t;YDSXGR_INTFLAG&t;&t;&t;0x0004
DECL|macro|YDSXGR_ACTIVITY
mdefine_line|#define&t;YDSXGR_ACTIVITY&t;&t;&t;0x0006
DECL|macro|YDSXGR_GLOBALCTRL
mdefine_line|#define&t;YDSXGR_GLOBALCTRL&t;&t;0x0008
DECL|macro|YDSXGR_ZVCTRL
mdefine_line|#define&t;YDSXGR_ZVCTRL&t;&t;&t;0x000A
DECL|macro|YDSXGR_TIMERCTRL
mdefine_line|#define&t;YDSXGR_TIMERCTRL&t;&t;0x0010
DECL|macro|YDSXGR_TIMERCTRL_TEN
mdefine_line|#define&t;YDSXGR_TIMERCTRL_TEN&t;&t; 0x0001
DECL|macro|YDSXGR_TIMERCTRL_TIEN
mdefine_line|#define&t;YDSXGR_TIMERCTRL_TIEN&t;&t; 0x0002
DECL|macro|YDSXGR_TIMERCOUNT
mdefine_line|#define&t;YDSXGR_TIMERCOUNT&t;&t;0x0012
DECL|macro|YDSXGR_SPDIFOUTCTRL
mdefine_line|#define&t;YDSXGR_SPDIFOUTCTRL&t;&t;0x0018
DECL|macro|YDSXGR_SPDIFOUTSTATUS
mdefine_line|#define&t;YDSXGR_SPDIFOUTSTATUS&t;&t;0x001C
DECL|macro|YDSXGR_EEPROMCTRL
mdefine_line|#define&t;YDSXGR_EEPROMCTRL&t;&t;0x0020
DECL|macro|YDSXGR_SPDIFINCTRL
mdefine_line|#define&t;YDSXGR_SPDIFINCTRL&t;&t;0x0034
DECL|macro|YDSXGR_SPDIFINSTATUS
mdefine_line|#define&t;YDSXGR_SPDIFINSTATUS&t;&t;0x0038
DECL|macro|YDSXGR_DSPPROGRAMDL
mdefine_line|#define&t;YDSXGR_DSPPROGRAMDL&t;&t;0x0048
DECL|macro|YDSXGR_DLCNTRL
mdefine_line|#define&t;YDSXGR_DLCNTRL&t;&t;&t;0x004C
DECL|macro|YDSXGR_GPIOININTFLAG
mdefine_line|#define&t;YDSXGR_GPIOININTFLAG&t;&t;0x0050
DECL|macro|YDSXGR_GPIOININTENABLE
mdefine_line|#define&t;YDSXGR_GPIOININTENABLE&t;&t;0x0052
DECL|macro|YDSXGR_GPIOINSTATUS
mdefine_line|#define&t;YDSXGR_GPIOINSTATUS&t;&t;0x0054
DECL|macro|YDSXGR_GPIOOUTCTRL
mdefine_line|#define&t;YDSXGR_GPIOOUTCTRL&t;&t;0x0056
DECL|macro|YDSXGR_GPIOFUNCENABLE
mdefine_line|#define&t;YDSXGR_GPIOFUNCENABLE&t;&t;0x0058
DECL|macro|YDSXGR_GPIOTYPECONFIG
mdefine_line|#define&t;YDSXGR_GPIOTYPECONFIG&t;&t;0x005A
DECL|macro|YDSXGR_AC97CMDDATA
mdefine_line|#define&t;YDSXGR_AC97CMDDATA&t;&t;0x0060
DECL|macro|YDSXGR_AC97CMDADR
mdefine_line|#define&t;YDSXGR_AC97CMDADR&t;&t;0x0062
DECL|macro|YDSXGR_PRISTATUSDATA
mdefine_line|#define&t;YDSXGR_PRISTATUSDATA&t;&t;0x0064
DECL|macro|YDSXGR_PRISTATUSADR
mdefine_line|#define&t;YDSXGR_PRISTATUSADR&t;&t;0x0066
DECL|macro|YDSXGR_SECSTATUSDATA
mdefine_line|#define&t;YDSXGR_SECSTATUSDATA&t;&t;0x0068
DECL|macro|YDSXGR_SECSTATUSADR
mdefine_line|#define&t;YDSXGR_SECSTATUSADR&t;&t;0x006A
DECL|macro|YDSXGR_SECCONFIG
mdefine_line|#define&t;YDSXGR_SECCONFIG&t;&t;0x0070
DECL|macro|YDSXGR_LEGACYOUTVOL
mdefine_line|#define&t;YDSXGR_LEGACYOUTVOL&t;&t;0x0080
DECL|macro|YDSXGR_LEGACYOUTVOLL
mdefine_line|#define&t;YDSXGR_LEGACYOUTVOLL&t;&t;0x0080
DECL|macro|YDSXGR_LEGACYOUTVOLR
mdefine_line|#define&t;YDSXGR_LEGACYOUTVOLR&t;&t;0x0082
DECL|macro|YDSXGR_NATIVEDACOUTVOL
mdefine_line|#define&t;YDSXGR_NATIVEDACOUTVOL&t;&t;0x0084
DECL|macro|YDSXGR_NATIVEDACOUTVOLL
mdefine_line|#define&t;YDSXGR_NATIVEDACOUTVOLL&t;&t;0x0084
DECL|macro|YDSXGR_NATIVEDACOUTVOLR
mdefine_line|#define&t;YDSXGR_NATIVEDACOUTVOLR&t;&t;0x0086
DECL|macro|YDSXGR_SPDIFOUTVOL
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOL&t;&t;0x0088
DECL|macro|YDSXGR_SPDIFOUTVOLL
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOLL&t;&t;0x0088
DECL|macro|YDSXGR_SPDIFOUTVOLR
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOLR&t;&t;0x008A
DECL|macro|YDSXGR_AC3OUTVOL
mdefine_line|#define&t;YDSXGR_AC3OUTVOL&t;&t;0x008C
DECL|macro|YDSXGR_AC3OUTVOLL
mdefine_line|#define&t;YDSXGR_AC3OUTVOLL&t;&t;0x008C
DECL|macro|YDSXGR_AC3OUTVOLR
mdefine_line|#define&t;YDSXGR_AC3OUTVOLR&t;&t;0x008E
DECL|macro|YDSXGR_PRIADCOUTVOL
mdefine_line|#define&t;YDSXGR_PRIADCOUTVOL&t;&t;0x0090
DECL|macro|YDSXGR_PRIADCOUTVOLL
mdefine_line|#define&t;YDSXGR_PRIADCOUTVOLL&t;&t;0x0090
DECL|macro|YDSXGR_PRIADCOUTVOLR
mdefine_line|#define&t;YDSXGR_PRIADCOUTVOLR&t;&t;0x0092
DECL|macro|YDSXGR_LEGACYLOOPVOL
mdefine_line|#define&t;YDSXGR_LEGACYLOOPVOL&t;&t;0x0094
DECL|macro|YDSXGR_LEGACYLOOPVOLL
mdefine_line|#define&t;YDSXGR_LEGACYLOOPVOLL&t;&t;0x0094
DECL|macro|YDSXGR_LEGACYLOOPVOLR
mdefine_line|#define&t;YDSXGR_LEGACYLOOPVOLR&t;&t;0x0096
DECL|macro|YDSXGR_NATIVEDACLOOPVOL
mdefine_line|#define&t;YDSXGR_NATIVEDACLOOPVOL&t;&t;0x0098
DECL|macro|YDSXGR_NATIVEDACLOOPVOLL
mdefine_line|#define&t;YDSXGR_NATIVEDACLOOPVOLL&t;0x0098
DECL|macro|YDSXGR_NATIVEDACLOOPVOLR
mdefine_line|#define&t;YDSXGR_NATIVEDACLOOPVOLR&t;0x009A
DECL|macro|YDSXGR_SPDIFLOOPVOL
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOL&t;&t;0x009C
DECL|macro|YDSXGR_SPDIFLOOPVOLL
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOLL&t;&t;0x009E
DECL|macro|YDSXGR_SPDIFLOOPVOLR
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOLR&t;&t;0x009E
DECL|macro|YDSXGR_AC3LOOPVOL
mdefine_line|#define&t;YDSXGR_AC3LOOPVOL&t;&t;0x00A0
DECL|macro|YDSXGR_AC3LOOPVOLL
mdefine_line|#define&t;YDSXGR_AC3LOOPVOLL&t;&t;0x00A0
DECL|macro|YDSXGR_AC3LOOPVOLR
mdefine_line|#define&t;YDSXGR_AC3LOOPVOLR&t;&t;0x00A2
DECL|macro|YDSXGR_PRIADCLOOPVOL
mdefine_line|#define&t;YDSXGR_PRIADCLOOPVOL&t;&t;0x00A4
DECL|macro|YDSXGR_PRIADCLOOPVOLL
mdefine_line|#define&t;YDSXGR_PRIADCLOOPVOLL&t;&t;0x00A4
DECL|macro|YDSXGR_PRIADCLOOPVOLR
mdefine_line|#define&t;YDSXGR_PRIADCLOOPVOLR&t;&t;0x00A6
DECL|macro|YDSXGR_NATIVEADCINVOL
mdefine_line|#define&t;YDSXGR_NATIVEADCINVOL&t;&t;0x00A8
DECL|macro|YDSXGR_NATIVEADCINVOLL
mdefine_line|#define&t;YDSXGR_NATIVEADCINVOLL&t;&t;0x00A8
DECL|macro|YDSXGR_NATIVEADCINVOLR
mdefine_line|#define&t;YDSXGR_NATIVEADCINVOLR&t;&t;0x00AA
DECL|macro|YDSXGR_NATIVEDACINVOL
mdefine_line|#define&t;YDSXGR_NATIVEDACINVOL&t;&t;0x00AC
DECL|macro|YDSXGR_NATIVEDACINVOLL
mdefine_line|#define&t;YDSXGR_NATIVEDACINVOLL&t;&t;0x00AC
DECL|macro|YDSXGR_NATIVEDACINVOLR
mdefine_line|#define&t;YDSXGR_NATIVEDACINVOLR&t;&t;0x00AE
DECL|macro|YDSXGR_BUF441OUTVOL
mdefine_line|#define&t;YDSXGR_BUF441OUTVOL&t;&t;0x00B0
DECL|macro|YDSXGR_BUF441OUTVOLL
mdefine_line|#define&t;YDSXGR_BUF441OUTVOLL&t;&t;0x00B0
DECL|macro|YDSXGR_BUF441OUTVOLR
mdefine_line|#define&t;YDSXGR_BUF441OUTVOLR&t;&t;0x00B2
DECL|macro|YDSXGR_BUF441LOOPVOL
mdefine_line|#define&t;YDSXGR_BUF441LOOPVOL&t;&t;0x00B4
DECL|macro|YDSXGR_BUF441LOOPVOLL
mdefine_line|#define&t;YDSXGR_BUF441LOOPVOLL&t;&t;0x00B4
DECL|macro|YDSXGR_BUF441LOOPVOLR
mdefine_line|#define&t;YDSXGR_BUF441LOOPVOLR&t;&t;0x00B6
DECL|macro|YDSXGR_SPDIFOUTVOL2
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOL2&t;&t;0x00B8
DECL|macro|YDSXGR_SPDIFOUTVOL2L
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOL2L&t;&t;0x00B8
DECL|macro|YDSXGR_SPDIFOUTVOL2R
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOL2R&t;&t;0x00BA
DECL|macro|YDSXGR_SPDIFLOOPVOL2
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOL2&t;&t;0x00BC
DECL|macro|YDSXGR_SPDIFLOOPVOL2L
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOL2L&t;&t;0x00BC
DECL|macro|YDSXGR_SPDIFLOOPVOL2R
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOL2R&t;&t;0x00BE
DECL|macro|YDSXGR_ADCSLOTSR
mdefine_line|#define&t;YDSXGR_ADCSLOTSR&t;&t;0x00C0
DECL|macro|YDSXGR_RECSLOTSR
mdefine_line|#define&t;YDSXGR_RECSLOTSR&t;&t;0x00C4
DECL|macro|YDSXGR_ADCFORMAT
mdefine_line|#define&t;YDSXGR_ADCFORMAT&t;&t;0x00C8
DECL|macro|YDSXGR_RECFORMAT
mdefine_line|#define&t;YDSXGR_RECFORMAT&t;&t;0x00CC
DECL|macro|YDSXGR_P44SLOTSR
mdefine_line|#define&t;YDSXGR_P44SLOTSR&t;&t;0x00D0
DECL|macro|YDSXGR_STATUS
mdefine_line|#define&t;YDSXGR_STATUS&t;&t;&t;0x0100
DECL|macro|YDSXGR_CTRLSELECT
mdefine_line|#define&t;YDSXGR_CTRLSELECT&t;&t;0x0104
DECL|macro|YDSXGR_MODE
mdefine_line|#define&t;YDSXGR_MODE&t;&t;&t;0x0108
DECL|macro|YDSXGR_SAMPLECOUNT
mdefine_line|#define&t;YDSXGR_SAMPLECOUNT&t;&t;0x010C
DECL|macro|YDSXGR_NUMOFSAMPLES
mdefine_line|#define&t;YDSXGR_NUMOFSAMPLES&t;&t;0x0110
DECL|macro|YDSXGR_CONFIG
mdefine_line|#define&t;YDSXGR_CONFIG&t;&t;&t;0x0114
DECL|macro|YDSXGR_PLAYCTRLSIZE
mdefine_line|#define&t;YDSXGR_PLAYCTRLSIZE&t;&t;0x0140
DECL|macro|YDSXGR_RECCTRLSIZE
mdefine_line|#define&t;YDSXGR_RECCTRLSIZE&t;&t;0x0144
DECL|macro|YDSXGR_EFFCTRLSIZE
mdefine_line|#define&t;YDSXGR_EFFCTRLSIZE&t;&t;0x0148
DECL|macro|YDSXGR_WORKSIZE
mdefine_line|#define&t;YDSXGR_WORKSIZE&t;&t;&t;0x014C
DECL|macro|YDSXGR_MAPOFREC
mdefine_line|#define&t;YDSXGR_MAPOFREC&t;&t;&t;0x0150
DECL|macro|YDSXGR_MAPOFEFFECT
mdefine_line|#define&t;YDSXGR_MAPOFEFFECT&t;&t;0x0154
DECL|macro|YDSXGR_PLAYCTRLBASE
mdefine_line|#define&t;YDSXGR_PLAYCTRLBASE&t;&t;0x0158
DECL|macro|YDSXGR_RECCTRLBASE
mdefine_line|#define&t;YDSXGR_RECCTRLBASE&t;&t;0x015C
DECL|macro|YDSXGR_EFFCTRLBASE
mdefine_line|#define&t;YDSXGR_EFFCTRLBASE&t;&t;0x0160
DECL|macro|YDSXGR_WORKBASE
mdefine_line|#define&t;YDSXGR_WORKBASE&t;&t;&t;0x0164
DECL|macro|YDSXGR_DSPINSTRAM
mdefine_line|#define&t;YDSXGR_DSPINSTRAM&t;&t;0x1000
DECL|macro|YDSXGR_CTRLINSTRAM
mdefine_line|#define&t;YDSXGR_CTRLINSTRAM&t;&t;0x4000
DECL|macro|YDSXG_AC97READCMD
mdefine_line|#define YDSXG_AC97READCMD&t;&t;0x8000
DECL|macro|YDSXG_AC97WRITECMD
mdefine_line|#define YDSXG_AC97WRITECMD&t;&t;0x0000
DECL|macro|PCIR_LEGCTRL
mdefine_line|#define PCIR_LEGCTRL&t;&t;&t;0x40
DECL|macro|PCIR_ELEGCTRL
mdefine_line|#define PCIR_ELEGCTRL&t;&t;&t;0x42
DECL|macro|PCIR_DSXGCTRL
mdefine_line|#define PCIR_DSXGCTRL&t;&t;&t;0x48
DECL|macro|PCIR_DSXPWRCTRL1
mdefine_line|#define PCIR_DSXPWRCTRL1&t;&t;0x4a
DECL|macro|PCIR_DSXPWRCTRL2
mdefine_line|#define PCIR_DSXPWRCTRL2&t;&t;0x4e
DECL|macro|PCIR_OPLADR
mdefine_line|#define PCIR_OPLADR&t;&t;&t;0x60
DECL|macro|PCIR_SBADR
mdefine_line|#define PCIR_SBADR&t;&t;&t;0x62
DECL|macro|PCIR_MPUADR
mdefine_line|#define PCIR_MPUADR&t;&t;&t;0x64
DECL|macro|YDSXG_DSPLENGTH
mdefine_line|#define YDSXG_DSPLENGTH&t;&t;&t;0x0080
DECL|macro|YDSXG_CTRLLENGTH
mdefine_line|#define YDSXG_CTRLLENGTH&t;&t;0x3000
DECL|macro|YDSXG_DEFAULT_WORK_SIZE
mdefine_line|#define YDSXG_DEFAULT_WORK_SIZE&t;&t;0x0400
DECL|macro|YDSXG_PLAYBACK_VOICES
mdefine_line|#define YDSXG_PLAYBACK_VOICES&t;&t;64
DECL|macro|YDSXG_CAPTURE_VOICES
mdefine_line|#define YDSXG_CAPTURE_VOICES&t;&t;2
DECL|macro|YDSXG_EFFECT_VOICES
mdefine_line|#define YDSXG_EFFECT_VOICES&t;&t;5
multiline_comment|/* maxinum number of AC97 codecs connected, AC97 2.0 defined 4 */
DECL|macro|NR_AC97
mdefine_line|#define NR_AC97&t;&t;2
DECL|macro|YMF_SAMPF
mdefine_line|#define YMF_SAMPF&t;&t;&t;256&t;/* Samples per frame @48000 */
multiline_comment|/*&n; * The slot/voice control bank (2 of these per voice)&n; */
DECL|struct|stru_ymfpci_playback_bank
r_typedef
r_struct
id|stru_ymfpci_playback_bank
(brace
DECL|member|format
id|u32
id|format
suffix:semicolon
DECL|member|loop_default
id|u32
id|loop_default
suffix:semicolon
DECL|member|base
id|u32
id|base
suffix:semicolon
multiline_comment|/* 32-bit address */
DECL|member|loop_start
id|u32
id|loop_start
suffix:semicolon
multiline_comment|/* 32-bit offset */
DECL|member|loop_end
id|u32
id|loop_end
suffix:semicolon
multiline_comment|/* 32-bit offset */
DECL|member|loop_frac
id|u32
id|loop_frac
suffix:semicolon
multiline_comment|/* 8-bit fraction - loop_start */
DECL|member|delta_end
id|u32
id|delta_end
suffix:semicolon
multiline_comment|/* pitch delta end */
DECL|member|lpfK_end
id|u32
id|lpfK_end
suffix:semicolon
DECL|member|eg_gain_end
id|u32
id|eg_gain_end
suffix:semicolon
DECL|member|left_gain_end
id|u32
id|left_gain_end
suffix:semicolon
DECL|member|right_gain_end
id|u32
id|right_gain_end
suffix:semicolon
DECL|member|eff1_gain_end
id|u32
id|eff1_gain_end
suffix:semicolon
DECL|member|eff2_gain_end
id|u32
id|eff2_gain_end
suffix:semicolon
DECL|member|eff3_gain_end
id|u32
id|eff3_gain_end
suffix:semicolon
DECL|member|lpfQ
id|u32
id|lpfQ
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* P3: Always 0 for some reason. */
DECL|member|num_of_frames
id|u32
id|num_of_frames
suffix:semicolon
DECL|member|loop_count
id|u32
id|loop_count
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* P3: J. reads this to know where chip is. */
DECL|member|start_frac
id|u32
id|start_frac
suffix:semicolon
DECL|member|delta
id|u32
id|delta
suffix:semicolon
DECL|member|lpfK
id|u32
id|lpfK
suffix:semicolon
DECL|member|eg_gain
id|u32
id|eg_gain
suffix:semicolon
DECL|member|left_gain
id|u32
id|left_gain
suffix:semicolon
DECL|member|right_gain
id|u32
id|right_gain
suffix:semicolon
DECL|member|eff1_gain
id|u32
id|eff1_gain
suffix:semicolon
DECL|member|eff2_gain
id|u32
id|eff2_gain
suffix:semicolon
DECL|member|eff3_gain
id|u32
id|eff3_gain
suffix:semicolon
DECL|member|lpfD1
id|u32
id|lpfD1
suffix:semicolon
DECL|member|lpfD2
id|u32
id|lpfD2
suffix:semicolon
DECL|typedef|ymfpci_playback_bank_t
)brace
id|ymfpci_playback_bank_t
suffix:semicolon
DECL|struct|stru_ymfpci_capture_bank
r_typedef
r_struct
id|stru_ymfpci_capture_bank
(brace
DECL|member|base
id|u32
id|base
suffix:semicolon
multiline_comment|/* 32-bit address (aligned at 4) */
DECL|member|loop_end
id|u32
id|loop_end
suffix:semicolon
multiline_comment|/* size in BYTES (aligned at 4) */
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* 32-bit offset */
DECL|member|num_of_loops
id|u32
id|num_of_loops
suffix:semicolon
multiline_comment|/* counter */
DECL|typedef|ymfpci_capture_bank_t
)brace
id|ymfpci_capture_bank_t
suffix:semicolon
DECL|struct|stru_ymfpci_effect_bank
r_typedef
r_struct
id|stru_ymfpci_effect_bank
(brace
DECL|member|base
id|u32
id|base
suffix:semicolon
multiline_comment|/* 32-bit address */
DECL|member|loop_end
id|u32
id|loop_end
suffix:semicolon
multiline_comment|/* 32-bit offset */
DECL|member|start
id|u32
id|start
suffix:semicolon
multiline_comment|/* 32-bit offset */
DECL|member|temp
id|u32
id|temp
suffix:semicolon
DECL|typedef|ymfpci_effect_bank_t
)brace
id|ymfpci_effect_bank_t
suffix:semicolon
DECL|typedef|ymfpci_voice_t
r_typedef
r_struct
id|ymf_voice
id|ymfpci_voice_t
suffix:semicolon
multiline_comment|/*&n; * Throughout the code Yaroslav names YMF unit pointer &quot;codec&quot;&n; * even though it does not correspond to any codec. Must be historic.&n; * We replace it with &quot;unit&quot; over time.&n; * AC97 parts use &quot;codec&quot; to denote a codec, naturally.&n; */
DECL|typedef|ymfpci_t
r_typedef
r_struct
id|ymf_unit
id|ymfpci_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|YMFPCI_PCM
id|YMFPCI_PCM
comma
DECL|enumerator|YMFPCI_SYNTH
id|YMFPCI_SYNTH
comma
DECL|enumerator|YMFPCI_MIDI
id|YMFPCI_MIDI
DECL|typedef|ymfpci_voice_type_t
)brace
id|ymfpci_voice_type_t
suffix:semicolon
DECL|struct|ymf_voice
r_struct
id|ymf_voice
(brace
singleline_comment|// ymfpci_t *codec;
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|use
DECL|member|pcm
DECL|member|synth
DECL|member|midi
r_char
id|use
comma
id|pcm
comma
id|synth
comma
id|midi
suffix:semicolon
singleline_comment|// bool
DECL|member|bank
id|ymfpci_playback_bank_t
op_star
id|bank
suffix:semicolon
DECL|member|ypcm
r_struct
id|ymf_pcm
op_star
id|ypcm
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ymf_capture
r_struct
id|ymf_capture
(brace
singleline_comment|// struct ymf_unit *unit;
DECL|member|use
r_int
id|use
suffix:semicolon
DECL|member|bank
id|ymfpci_capture_bank_t
op_star
id|bank
suffix:semicolon
DECL|member|ypcm
r_struct
id|ymf_pcm
op_star
id|ypcm
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ymf_unit
r_struct
id|ymf_unit
(brace
DECL|member|rev
id|u8
id|rev
suffix:semicolon
multiline_comment|/* PCI revision */
DECL|member|reg_area_virt
r_void
op_star
id|reg_area_virt
suffix:semicolon
DECL|member|work_ptr
r_void
op_star
id|work_ptr
suffix:semicolon
DECL|member|bank_size_playback
r_int
r_int
id|bank_size_playback
suffix:semicolon
DECL|member|bank_size_capture
r_int
r_int
id|bank_size_capture
suffix:semicolon
DECL|member|bank_size_effect
r_int
r_int
id|bank_size_effect
suffix:semicolon
DECL|member|work_size
r_int
r_int
id|work_size
suffix:semicolon
DECL|member|bank_base_playback
r_void
op_star
id|bank_base_playback
suffix:semicolon
DECL|member|bank_base_capture
r_void
op_star
id|bank_base_capture
suffix:semicolon
DECL|member|bank_base_effect
r_void
op_star
id|bank_base_effect
suffix:semicolon
DECL|member|work_base
r_void
op_star
id|work_base
suffix:semicolon
DECL|member|ctrl_playback
id|u32
op_star
id|ctrl_playback
suffix:semicolon
DECL|member|bank_playback
id|ymfpci_playback_bank_t
op_star
id|bank_playback
(braket
id|YDSXG_PLAYBACK_VOICES
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bank_capture
id|ymfpci_capture_bank_t
op_star
id|bank_capture
(braket
id|YDSXG_CAPTURE_VOICES
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bank_effect
id|ymfpci_effect_bank_t
op_star
id|bank_effect
(braket
id|YDSXG_EFFECT_VOICES
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|start_count
r_int
id|start_count
suffix:semicolon
DECL|member|suspended
r_int
id|suspended
suffix:semicolon
DECL|member|active_bank
id|u32
id|active_bank
suffix:semicolon
DECL|member|voices
r_struct
id|ymf_voice
id|voices
(braket
id|YDSXG_PLAYBACK_VOICES
)braket
suffix:semicolon
DECL|member|capture
r_struct
id|ymf_capture
id|capture
(braket
id|YDSXG_CAPTURE_VOICES
)braket
suffix:semicolon
DECL|member|ac97_codec
r_struct
id|ac97_codec
op_star
id|ac97_codec
(braket
id|NR_AC97
)braket
suffix:semicolon
DECL|member|ac97_features
id|u16
id|ac97_features
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
macro_line|#ifdef CONFIG_SOUND_YMFPCI_LEGACY
multiline_comment|/* legacy hardware resources */
DECL|member|iosynth
DECL|member|iomidi
r_int
r_int
id|iosynth
comma
id|iomidi
suffix:semicolon
DECL|member|opl3_data
DECL|member|mpu_data
r_struct
id|address_info
id|opl3_data
comma
id|mpu_data
suffix:semicolon
macro_line|#endif
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|voice_lock
id|spinlock_t
id|voice_lock
suffix:semicolon
multiline_comment|/* soundcore stuff */
DECL|member|dev_audio
r_int
id|dev_audio
suffix:semicolon
DECL|member|open_sem
r_struct
id|semaphore
id|open_sem
suffix:semicolon
DECL|member|ymf_devs
r_struct
id|list_head
id|ymf_devs
suffix:semicolon
DECL|member|states
r_struct
id|list_head
id|states
suffix:semicolon
multiline_comment|/* List of states for this unit */
)brace
suffix:semicolon
DECL|struct|ymf_dmabuf
r_struct
id|ymf_dmabuf
(brace
multiline_comment|/* OSS buffer management stuff */
DECL|member|rawbuf
r_void
op_star
id|rawbuf
suffix:semicolon
DECL|member|buforder
r_int
id|buforder
suffix:semicolon
DECL|member|numfrag
r_int
id|numfrag
suffix:semicolon
DECL|member|fragshift
r_int
id|fragshift
suffix:semicolon
multiline_comment|/* our buffer acts like a circular ring */
DECL|member|hwptr
r_int
id|hwptr
suffix:semicolon
multiline_comment|/* where dma last started */
DECL|member|swptr
r_int
id|swptr
suffix:semicolon
multiline_comment|/* where driver last clear/filled */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* fill count */
DECL|member|total_bytes
r_int
id|total_bytes
suffix:semicolon
multiline_comment|/* total bytes dmaed by hardware */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* put process on wait queue when no more space in buffer */
multiline_comment|/* redundant, but makes calculations easier */
DECL|member|fragsize
r_int
id|fragsize
suffix:semicolon
DECL|member|dmasize
r_int
id|dmasize
suffix:semicolon
multiline_comment|/* Total rawbuf[] size */
multiline_comment|/* OSS stuff */
DECL|member|mapped
r_int
id|mapped
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ready
r_int
id|ready
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ossfragshift
r_int
id|ossfragshift
suffix:semicolon
DECL|member|ossmaxfrags
r_int
id|ossmaxfrags
suffix:semicolon
DECL|member|subdivision
r_int
id|subdivision
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ymf_pcm_format
r_struct
id|ymf_pcm_format
(brace
DECL|member|format
r_int
id|format
suffix:semicolon
multiline_comment|/* OSS format */
DECL|member|rate
r_int
id|rate
suffix:semicolon
multiline_comment|/* rate in Hz */
DECL|member|voices
r_int
id|voices
suffix:semicolon
multiline_comment|/* number of voices */
DECL|member|shift
r_int
id|shift
suffix:semicolon
multiline_comment|/* redundant, computed from the above */
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|PLAYBACK_VOICE
id|PLAYBACK_VOICE
comma
DECL|enumerator|CAPTURE_REC
id|CAPTURE_REC
comma
DECL|enumerator|CAPTURE_AC97
id|CAPTURE_AC97
comma
DECL|enumerator|EFFECT_DRY_LEFT
id|EFFECT_DRY_LEFT
comma
DECL|enumerator|EFFECT_DRY_RIGHT
id|EFFECT_DRY_RIGHT
comma
DECL|enumerator|EFFECT_EFF1
id|EFFECT_EFF1
comma
DECL|enumerator|EFFECT_EFF2
id|EFFECT_EFF2
comma
DECL|enumerator|EFFECT_EFF3
id|EFFECT_EFF3
DECL|typedef|ymfpci_pcm_type_t
)brace
id|ymfpci_pcm_type_t
suffix:semicolon
multiline_comment|/* This is variant record, but we hate unions. Little waste on pointers []. */
DECL|struct|ymf_pcm
r_struct
id|ymf_pcm
(brace
DECL|member|type
id|ymfpci_pcm_type_t
id|type
suffix:semicolon
DECL|member|state
r_struct
id|ymf_state
op_star
id|state
suffix:semicolon
DECL|member|voices
id|ymfpci_voice_t
op_star
id|voices
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|capture_bank_number
r_int
id|capture_bank_number
suffix:semicolon
DECL|member|dmabuf
r_struct
id|ymf_dmabuf
id|dmabuf
suffix:semicolon
DECL|member|running
r_int
id|running
suffix:semicolon
DECL|member|spdif
r_int
id|spdif
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * &quot;Software&quot; or virtual channel, an instance of opened /dev/dsp.&n; * It may have two physical channels (pcms) for duplex operations.&n; */
DECL|struct|ymf_state
r_struct
id|ymf_state
(brace
DECL|member|chain
r_struct
id|list_head
id|chain
suffix:semicolon
DECL|member|unit
r_struct
id|ymf_unit
op_star
id|unit
suffix:semicolon
multiline_comment|/* backpointer */
DECL|member|rpcm
DECL|member|wpcm
r_struct
id|ymf_pcm
id|rpcm
comma
id|wpcm
suffix:semicolon
DECL|member|format
r_struct
id|ymf_pcm_format
id|format
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __YMFPCI_H */
eof
