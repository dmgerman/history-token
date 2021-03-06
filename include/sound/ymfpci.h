macro_line|#ifndef __SOUND_YMFPCI_H
DECL|macro|__SOUND_YMFPCI_H
mdefine_line|#define __SOUND_YMFPCI_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Definitions for Yahama YMF724/740/744/754 chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;pcm.h&quot;
macro_line|#include &quot;rawmidi.h&quot;
macro_line|#include &quot;ac97_codec.h&quot;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#ifndef PCI_VENDOR_ID_YAMAHA
DECL|macro|PCI_VENDOR_ID_YAMAHA
mdefine_line|#define PCI_VENDOR_ID_YAMAHA            0x1073
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_YAMAHA_724
DECL|macro|PCI_DEVICE_ID_YAMAHA_724
mdefine_line|#define PCI_DEVICE_ID_YAMAHA_724&t;0x0004
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_YAMAHA_724F
DECL|macro|PCI_DEVICE_ID_YAMAHA_724F
mdefine_line|#define PCI_DEVICE_ID_YAMAHA_724F&t;0x000d
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_YAMAHA_740
DECL|macro|PCI_DEVICE_ID_YAMAHA_740
mdefine_line|#define PCI_DEVICE_ID_YAMAHA_740&t;0x000a
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_YAMAHA_740C
DECL|macro|PCI_DEVICE_ID_YAMAHA_740C
mdefine_line|#define PCI_DEVICE_ID_YAMAHA_740C&t;0x000c
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_YAMAHA_744
DECL|macro|PCI_DEVICE_ID_YAMAHA_744
mdefine_line|#define PCI_DEVICE_ID_YAMAHA_744&t;0x0010
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_YAMAHA_754
DECL|macro|PCI_DEVICE_ID_YAMAHA_754
mdefine_line|#define PCI_DEVICE_ID_YAMAHA_754&t;0x0012
macro_line|#endif
multiline_comment|/*&n; *  Direct registers&n; */
DECL|macro|YMFREG
mdefine_line|#define YMFREG(chip, reg)&t;&t;(chip-&gt;port + YDSXGR_##reg)
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
DECL|macro|YDSXGR_ZVOUTVOL
mdefine_line|#define&t;YDSXGR_ZVOUTVOL&t;&t;&t;0x0088
DECL|macro|YDSXGR_ZVOUTVOLL
mdefine_line|#define&t;YDSXGR_ZVOUTVOLL&t;&t;0x0088
DECL|macro|YDSXGR_ZVOUTVOLR
mdefine_line|#define&t;YDSXGR_ZVOUTVOLR&t;&t;0x008A
DECL|macro|YDSXGR_SECADCOUTVOL
mdefine_line|#define&t;YDSXGR_SECADCOUTVOL&t;&t;0x008C
DECL|macro|YDSXGR_SECADCOUTVOLL
mdefine_line|#define&t;YDSXGR_SECADCOUTVOLL&t;&t;0x008C
DECL|macro|YDSXGR_SECADCOUTVOLR
mdefine_line|#define&t;YDSXGR_SECADCOUTVOLR&t;&t;0x008E
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
DECL|macro|YDSXGR_ZVLOOPVOL
mdefine_line|#define&t;YDSXGR_ZVLOOPVOL&t;&t;0x009C
DECL|macro|YDSXGR_ZVLOOPVOLL
mdefine_line|#define&t;YDSXGR_ZVLOOPVOLL&t;&t;0x009E
DECL|macro|YDSXGR_ZVLOOPVOLR
mdefine_line|#define&t;YDSXGR_ZVLOOPVOLR&t;&t;0x009E
DECL|macro|YDSXGR_SECADCLOOPVOL
mdefine_line|#define&t;YDSXGR_SECADCLOOPVOL&t;&t;0x00A0
DECL|macro|YDSXGR_SECADCLOOPVOLL
mdefine_line|#define&t;YDSXGR_SECADCLOOPVOLL&t;&t;0x00A0
DECL|macro|YDSXGR_SECADCLOOPVOLR
mdefine_line|#define&t;YDSXGR_SECADCLOOPVOLR&t;&t;0x00A2
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
DECL|macro|YDSXGR_SPDIFOUTVOL
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOL&t;&t;0x00B8
DECL|macro|YDSXGR_SPDIFOUTVOLL
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOLL&t;&t;0x00B8
DECL|macro|YDSXGR_SPDIFOUTVOLR
mdefine_line|#define&t;YDSXGR_SPDIFOUTVOLR&t;&t;0x00BA
DECL|macro|YDSXGR_SPDIFLOOPVOL
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOL&t;&t;0x00BC
DECL|macro|YDSXGR_SPDIFLOOPVOLL
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOLL&t;&t;0x00BC
DECL|macro|YDSXGR_SPDIFLOOPVOLR
mdefine_line|#define&t;YDSXGR_SPDIFLOOPVOLR&t;&t;0x00BE
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
DECL|macro|PCIR_DSXG_LEGACY
mdefine_line|#define PCIR_DSXG_LEGACY&t;&t;0x40
DECL|macro|PCIR_DSXG_ELEGACY
mdefine_line|#define PCIR_DSXG_ELEGACY&t;&t;0x42
DECL|macro|PCIR_DSXG_CTRL
mdefine_line|#define PCIR_DSXG_CTRL&t;&t;&t;0x48
DECL|macro|PCIR_DSXG_PWRCTRL1
mdefine_line|#define PCIR_DSXG_PWRCTRL1&t;&t;0x4a
DECL|macro|PCIR_DSXG_PWRCTRL2
mdefine_line|#define PCIR_DSXG_PWRCTRL2&t;&t;0x4e
DECL|macro|PCIR_DSXG_FMBASE
mdefine_line|#define PCIR_DSXG_FMBASE&t;&t;0x60
DECL|macro|PCIR_DSXG_SBBASE
mdefine_line|#define PCIR_DSXG_SBBASE&t;&t;0x62
DECL|macro|PCIR_DSXG_MPU401BASE
mdefine_line|#define PCIR_DSXG_MPU401BASE&t;&t;0x64
DECL|macro|PCIR_DSXG_JOYBASE
mdefine_line|#define PCIR_DSXG_JOYBASE&t;&t;0x66
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
DECL|macro|YMFPCI_LEGACY_SBEN
mdefine_line|#define YMFPCI_LEGACY_SBEN&t;(1 &lt;&lt; 0)&t;/* soundblaster enable */
DECL|macro|YMFPCI_LEGACY_FMEN
mdefine_line|#define YMFPCI_LEGACY_FMEN&t;(1 &lt;&lt; 1)&t;/* OPL3 enable */
DECL|macro|YMFPCI_LEGACY_JPEN
mdefine_line|#define YMFPCI_LEGACY_JPEN&t;(1 &lt;&lt; 2)&t;/* joystick enable */
DECL|macro|YMFPCI_LEGACY_MEN
mdefine_line|#define YMFPCI_LEGACY_MEN&t;(1 &lt;&lt; 3)&t;/* MPU401 enable */
DECL|macro|YMFPCI_LEGACY_MIEN
mdefine_line|#define YMFPCI_LEGACY_MIEN&t;(1 &lt;&lt; 4)&t;/* MPU RX irq enable */
DECL|macro|YMFPCI_LEGACY_IOBITS
mdefine_line|#define YMFPCI_LEGACY_IOBITS&t;(1 &lt;&lt; 5)&t;/* i/o bits range, 0 = 16bit, 1 =10bit */
DECL|macro|YMFPCI_LEGACY_SDMA
mdefine_line|#define YMFPCI_LEGACY_SDMA&t;(3 &lt;&lt; 6)&t;/* SB DMA select */
DECL|macro|YMFPCI_LEGACY_SBIRQ
mdefine_line|#define YMFPCI_LEGACY_SBIRQ&t;(7 &lt;&lt; 8)&t;/* SB IRQ select */
DECL|macro|YMFPCI_LEGACY_MPUIRQ
mdefine_line|#define YMFPCI_LEGACY_MPUIRQ&t;(7 &lt;&lt; 11)&t;/* MPU IRQ select */
DECL|macro|YMFPCI_LEGACY_SIEN
mdefine_line|#define YMFPCI_LEGACY_SIEN&t;(1 &lt;&lt; 14)&t;/* serialized IRQ */
DECL|macro|YMFPCI_LEGACY_LAD
mdefine_line|#define YMFPCI_LEGACY_LAD&t;(1 &lt;&lt; 15)&t;/* legacy audio disable */
DECL|macro|YMFPCI_LEGACY2_FMIO
mdefine_line|#define YMFPCI_LEGACY2_FMIO&t;(3 &lt;&lt; 0)&t;/* OPL3 i/o address (724/740) */
DECL|macro|YMFPCI_LEGACY2_SBIO
mdefine_line|#define YMFPCI_LEGACY2_SBIO&t;(3 &lt;&lt; 2)&t;/* SB i/o address (724/740) */
DECL|macro|YMFPCI_LEGACY2_MPUIO
mdefine_line|#define YMFPCI_LEGACY2_MPUIO&t;(3 &lt;&lt; 4)&t;/* MPU401 i/o address (724/740) */
DECL|macro|YMFPCI_LEGACY2_JSIO
mdefine_line|#define YMFPCI_LEGACY2_JSIO&t;(3 &lt;&lt; 6)&t;/* joystick i/o address (724/740) */
DECL|macro|YMFPCI_LEGACY2_MAIM
mdefine_line|#define YMFPCI_LEGACY2_MAIM&t;(1 &lt;&lt; 8)&t;/* MPU401 ack intr mask */
DECL|macro|YMFPCI_LEGACY2_SMOD
mdefine_line|#define YMFPCI_LEGACY2_SMOD&t;(3 &lt;&lt; 11)&t;/* SB DMA mode */
DECL|macro|YMFPCI_LEGACY2_SBVER
mdefine_line|#define YMFPCI_LEGACY2_SBVER&t;(3 &lt;&lt; 13)&t;/* SB version select */
DECL|macro|YMFPCI_LEGACY2_IMOD
mdefine_line|#define YMFPCI_LEGACY2_IMOD&t;(1 &lt;&lt; 15)&t;/* legacy IRQ mode */
multiline_comment|/* SIEN:IMOD 0:0 = legacy irq, 0:1 = INTA, 1:0 = serialized IRQ */
macro_line|#if defined(CONFIG_GAMEPORT) || (defined(MODULE) &amp;&amp; defined(CONFIG_GAMEPORT_MODULE))
DECL|macro|SUPPORT_JOYSTICK
mdefine_line|#define SUPPORT_JOYSTICK
macro_line|#endif
multiline_comment|/*&n; *&n; */
DECL|struct|_snd_ymfpci_playback_bank
r_typedef
r_struct
id|_snd_ymfpci_playback_bank
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
DECL|typedef|snd_ymfpci_playback_bank_t
)brace
id|snd_ymfpci_playback_bank_t
suffix:semicolon
DECL|struct|_snd_ymfpci_capture_bank
r_typedef
r_struct
id|_snd_ymfpci_capture_bank
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
DECL|member|num_of_loops
id|u32
id|num_of_loops
suffix:semicolon
multiline_comment|/* counter */
DECL|typedef|snd_ymfpci_capture_bank_t
)brace
id|snd_ymfpci_capture_bank_t
suffix:semicolon
DECL|struct|_snd_ymfpci_effect_bank
r_typedef
r_struct
id|_snd_ymfpci_effect_bank
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
DECL|typedef|snd_ymfpci_effect_bank_t
)brace
id|snd_ymfpci_effect_bank_t
suffix:semicolon
DECL|typedef|ymfpci_voice_t
r_typedef
r_struct
id|_snd_ymfpci_voice
id|ymfpci_voice_t
suffix:semicolon
DECL|typedef|ymfpci_pcm_t
r_typedef
r_struct
id|_snd_ymfpci_pcm
id|ymfpci_pcm_t
suffix:semicolon
DECL|typedef|ymfpci_t
r_typedef
r_struct
id|_snd_ymfpci
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
DECL|struct|_snd_ymfpci_voice
r_struct
id|_snd_ymfpci_voice
(brace
DECL|member|chip
id|ymfpci_t
op_star
id|chip
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|use
r_int
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
DECL|member|bank
id|snd_ymfpci_playback_bank_t
op_star
id|bank
suffix:semicolon
DECL|member|bank_addr
id|dma_addr_t
id|bank_addr
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
id|ymfpci_t
op_star
id|chip
comma
id|ymfpci_voice_t
op_star
id|voice
)paren
suffix:semicolon
DECL|member|ypcm
id|ymfpci_pcm_t
op_star
id|ypcm
suffix:semicolon
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
DECL|typedef|snd_ymfpci_pcm_type_t
)brace
id|snd_ymfpci_pcm_type_t
suffix:semicolon
DECL|struct|_snd_ymfpci_pcm
r_struct
id|_snd_ymfpci_pcm
(brace
DECL|member|chip
id|ymfpci_t
op_star
id|chip
suffix:semicolon
DECL|member|type
id|snd_ymfpci_pcm_type_t
id|type
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|voices
id|ymfpci_voice_t
op_star
id|voices
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* playback only */
DECL|member|running
r_int
r_int
id|running
suffix:colon
l_int|1
suffix:semicolon
DECL|member|output_front
r_int
r_int
id|output_front
suffix:colon
l_int|1
suffix:semicolon
DECL|member|output_rear
r_int
r_int
id|output_rear
suffix:colon
l_int|1
suffix:semicolon
DECL|member|period_size
id|u32
id|period_size
suffix:semicolon
multiline_comment|/* cached from runtime-&gt;period_size */
DECL|member|buffer_size
id|u32
id|buffer_size
suffix:semicolon
multiline_comment|/* cached from runtime-&gt;buffer_size */
DECL|member|period_pos
id|u32
id|period_pos
suffix:semicolon
DECL|member|last_pos
id|u32
id|last_pos
suffix:semicolon
DECL|member|capture_bank_number
id|u32
id|capture_bank_number
suffix:semicolon
DECL|member|shift
id|u32
id|shift
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_ymfpci
r_struct
id|_snd_ymfpci
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
multiline_comment|/* PCI device ID */
DECL|member|rev
r_int
r_int
id|rev
suffix:semicolon
multiline_comment|/* PCI revision */
DECL|member|reg_area_phys
r_int
r_int
id|reg_area_phys
suffix:semicolon
DECL|member|reg_area_virt
r_void
id|__iomem
op_star
id|reg_area_virt
suffix:semicolon
DECL|member|res_reg_area
r_struct
id|resource
op_star
id|res_reg_area
suffix:semicolon
DECL|member|fm_res
r_struct
id|resource
op_star
id|fm_res
suffix:semicolon
DECL|member|mpu_res
r_struct
id|resource
op_star
id|mpu_res
suffix:semicolon
DECL|member|old_legacy_ctrl
r_int
r_int
id|old_legacy_ctrl
suffix:semicolon
macro_line|#ifdef SUPPORT_JOYSTICK
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
macro_line|#endif
DECL|member|work_ptr
r_struct
id|snd_dma_buffer
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
DECL|member|bank_base_playback_addr
id|dma_addr_t
id|bank_base_playback_addr
suffix:semicolon
DECL|member|bank_base_capture_addr
id|dma_addr_t
id|bank_base_capture_addr
suffix:semicolon
DECL|member|bank_base_effect_addr
id|dma_addr_t
id|bank_base_effect_addr
suffix:semicolon
DECL|member|work_base_addr
id|dma_addr_t
id|work_base_addr
suffix:semicolon
DECL|member|ac3_tmp_base
r_struct
id|snd_dma_buffer
id|ac3_tmp_base
suffix:semicolon
DECL|member|ctrl_playback
id|u32
op_star
id|ctrl_playback
suffix:semicolon
DECL|member|bank_playback
id|snd_ymfpci_playback_bank_t
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
id|snd_ymfpci_capture_bank_t
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
id|snd_ymfpci_effect_bank_t
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
DECL|member|active_bank
id|u32
id|active_bank
suffix:semicolon
DECL|member|voices
id|ymfpci_voice_t
id|voices
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|ac97_bus
id|ac97_bus_t
op_star
id|ac97_bus
suffix:semicolon
DECL|member|ac97
id|ac97_t
op_star
id|ac97
suffix:semicolon
DECL|member|rawmidi
id|snd_rawmidi_t
op_star
id|rawmidi
suffix:semicolon
DECL|member|timer
id|snd_timer_t
op_star
id|timer
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
DECL|member|pcm2
id|snd_pcm_t
op_star
id|pcm2
suffix:semicolon
DECL|member|pcm_spdif
id|snd_pcm_t
op_star
id|pcm_spdif
suffix:semicolon
DECL|member|pcm_4ch
id|snd_pcm_t
op_star
id|pcm_4ch
suffix:semicolon
DECL|member|capture_substream
id|snd_pcm_substream_t
op_star
id|capture_substream
(braket
id|YDSXG_CAPTURE_VOICES
)braket
suffix:semicolon
DECL|member|effect_substream
id|snd_pcm_substream_t
op_star
id|effect_substream
(braket
id|YDSXG_EFFECT_VOICES
)braket
suffix:semicolon
DECL|member|ctl_vol_recsrc
id|snd_kcontrol_t
op_star
id|ctl_vol_recsrc
suffix:semicolon
DECL|member|ctl_vol_adcrec
id|snd_kcontrol_t
op_star
id|ctl_vol_adcrec
suffix:semicolon
DECL|member|ctl_vol_spdifrec
id|snd_kcontrol_t
op_star
id|ctl_vol_spdifrec
suffix:semicolon
DECL|member|spdif_bits
DECL|member|spdif_pcm_bits
r_int
r_int
id|spdif_bits
comma
id|spdif_pcm_bits
suffix:semicolon
DECL|member|spdif_pcm_ctl
id|snd_kcontrol_t
op_star
id|spdif_pcm_ctl
suffix:semicolon
DECL|member|mode_dup4ch
r_int
id|mode_dup4ch
suffix:semicolon
DECL|member|rear_opened
r_int
id|rear_opened
suffix:semicolon
DECL|member|spdif_opened
r_int
id|spdif_opened
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|voice_lock
id|spinlock_t
id|voice_lock
suffix:semicolon
DECL|member|interrupt_sleep
id|wait_queue_head_t
id|interrupt_sleep
suffix:semicolon
DECL|member|interrupt_sleep_count
id|atomic_t
id|interrupt_sleep_count
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|member|saved_regs
id|u32
op_star
id|saved_regs
suffix:semicolon
DECL|member|saved_ydsxgr_mode
id|u32
id|saved_ydsxgr_mode
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_int
id|snd_ymfpci_create
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
r_int
id|old_legacy_ctrl
comma
id|ymfpci_t
op_star
op_star
id|rcodec
)paren
suffix:semicolon
r_void
id|snd_ymfpci_free_gameport
c_func
(paren
id|ymfpci_t
op_star
id|chip
)paren
suffix:semicolon
r_int
id|snd_ymfpci_pcm
c_func
(paren
id|ymfpci_t
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
id|snd_ymfpci_pcm2
c_func
(paren
id|ymfpci_t
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
id|snd_ymfpci_pcm_spdif
c_func
(paren
id|ymfpci_t
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
id|snd_ymfpci_pcm_4ch
c_func
(paren
id|ymfpci_t
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
id|snd_ymfpci_mixer
c_func
(paren
id|ymfpci_t
op_star
id|chip
comma
r_int
id|rear_switch
)paren
suffix:semicolon
r_int
id|snd_ymfpci_timer
c_func
(paren
id|ymfpci_t
op_star
id|chip
comma
r_int
id|device
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_YMFPCI_H */
eof
