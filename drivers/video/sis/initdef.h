multiline_comment|/* $XFree86$ */
multiline_comment|/* $XdotOrg$ */
multiline_comment|/*&n; * Global definitions for init.c and init301.c&n; *&n; * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria&n; *&n; * If distributed as part of the Linux kernel, the following license terms&n; * apply:&n; *&n; * * This program is free software; you can redistribute it and/or modify&n; * * it under the terms of the GNU General Public License as published by&n; * * the Free Software Foundation; either version 2 of the named License,&n; * * or any later version.&n; * *&n; * * This program is distributed in the hope that it will be useful,&n; * * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * * GNU General Public License for more details.&n; * *&n; * * You should have received a copy of the GNU General Public License&n; * * along with this program; if not, write to the Free Software&n; * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; *&n; * Otherwise, the following license terms apply:&n; *&n; * * Redistribution and use in source and binary forms, with or without&n; * * modification, are permitted provided that the following conditions&n; * * are met:&n; * * 1) Redistributions of source code must retain the above copyright&n; * *    notice, this list of conditions and the following disclaimer.&n; * * 2) Redistributions in binary form must reproduce the above copyright&n; * *    notice, this list of conditions and the following disclaimer in the&n; * *    documentation and/or other materials provided with the distribution.&n; * * 3) The name of the author may not be used to endorse or promote products&n; * *    derived from this software without specific prior written permission.&n; * *&n; * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR&n; * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,&n; * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY&n; * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * Author: &t;Thomas Winischhofer &lt;thomas@winischhofer.net&gt;&n; *&n; */
macro_line|#ifndef _INITDEF_
DECL|macro|_INITDEF_
mdefine_line|#define _INITDEF_
DECL|macro|IS_SIS330
mdefine_line|#define IS_SIS330&t;&t;(HwInfo-&gt;jChipType == SIS_330)
DECL|macro|IS_SIS550
mdefine_line|#define IS_SIS550&t;&t;(HwInfo-&gt;jChipType == SIS_550)
DECL|macro|IS_SIS650
mdefine_line|#define IS_SIS650&t;&t;(HwInfo-&gt;jChipType == SIS_650)  /* All versions, incl 651, M65x */
DECL|macro|IS_SIS740
mdefine_line|#define IS_SIS740&t;&t;(HwInfo-&gt;jChipType == SIS_740)
DECL|macro|IS_SIS651
mdefine_line|#define IS_SIS651&t;        (SiS_Pr-&gt;SiS_SysFlags &amp; (SF_Is651 | SF_Is652))
DECL|macro|IS_SISM650
mdefine_line|#define IS_SISM650&t;        (SiS_Pr-&gt;SiS_SysFlags &amp; (SF_IsM650 | SF_IsM652 | SF_IsM653))
DECL|macro|IS_SIS65x
mdefine_line|#define IS_SIS65x               (IS_SIS651 || IS_SISM650)       /* Only special versions of 65x */
DECL|macro|IS_SIS661
mdefine_line|#define IS_SIS661&t;&t;(HwInfo-&gt;jChipType == SIS_661)
DECL|macro|IS_SIS741
mdefine_line|#define IS_SIS741&t;&t;(HwInfo-&gt;jChipType == SIS_741)
DECL|macro|IS_SIS660
mdefine_line|#define IS_SIS660&t;&t;(HwInfo-&gt;jChipType == SIS_660)
DECL|macro|IS_SIS760
mdefine_line|#define IS_SIS760&t;&t;(HwInfo-&gt;jChipType == SIS_760)
DECL|macro|IS_SIS661741660760
mdefine_line|#define IS_SIS661741660760&t;(IS_SIS661 || IS_SIS741 || IS_SIS660 || IS_SIS760)
DECL|macro|IS_SIS650740
mdefine_line|#define IS_SIS650740            ((HwInfo-&gt;jChipType &gt;= SIS_650) &amp;&amp; (HwInfo-&gt;jChipType &lt; SIS_330))
DECL|macro|IS_SIS550650740
mdefine_line|#define IS_SIS550650740         (IS_SIS550 || IS_SIS650740)
DECL|macro|IS_SIS650740660
mdefine_line|#define IS_SIS650740660         (IS_SIS650 || IS_SIS740 || IS_SIS661741660760)
DECL|macro|IS_SIS550650740660
mdefine_line|#define IS_SIS550650740660      (IS_SIS550 || IS_SIS650740660)
DECL|macro|SISGETROMW
mdefine_line|#define SISGETROMW(x)&t;&t;(ROMAddr[(x)] | (ROMAddr[(x)+1] &lt;&lt; 8))
multiline_comment|/* SiS_VBType */
DECL|macro|VB_SIS301
mdefine_line|#define VB_SIS301&t;      &t;0x0001
DECL|macro|VB_SIS301B
mdefine_line|#define VB_SIS301B        &t;0x0002
DECL|macro|VB_SIS302B
mdefine_line|#define VB_SIS302B        &t;0x0004
DECL|macro|VB_SIS301LV
mdefine_line|#define VB_SIS301LV     &t;0x0008
DECL|macro|VB_SIS302LV
mdefine_line|#define VB_SIS302LV     &t;0x0010
DECL|macro|VB_SIS302ELV
mdefine_line|#define VB_SIS302ELV&t;&t;0x0020
DECL|macro|VB_SIS301C
mdefine_line|#define VB_SIS301C              0x0040
DECL|macro|VB_UMC
mdefine_line|#define VB_UMC&t;&t;&t;0x4000
DECL|macro|VB_NoLCD
mdefine_line|#define VB_NoLCD        &t;0x8000
DECL|macro|VB_SIS301BLV302BLV
mdefine_line|#define VB_SIS301BLV302BLV      (VB_SIS301B|VB_SIS301C|VB_SIS302B|VB_SIS301LV|VB_SIS302LV|VB_SIS302ELV)
DECL|macro|VB_SIS301B302B
mdefine_line|#define VB_SIS301B302B          (VB_SIS301B|VB_SIS301C|VB_SIS302B)
DECL|macro|VB_SIS301LV302LV
mdefine_line|#define VB_SIS301LV302LV        (VB_SIS301LV|VB_SIS302LV|VB_SIS302ELV)
DECL|macro|VB_SISVB
mdefine_line|#define VB_SISVB&t;&t;(VB_SIS301 | VB_SIS301BLV302BLV)
DECL|macro|VB_SISTMDS
mdefine_line|#define VB_SISTMDS&t;&t;(VB_SIS301 | VB_SIS301B302B)
DECL|macro|VB_SISLVDS
mdefine_line|#define VB_SISLVDS&t;&t;VB_SIS301LV302LV
DECL|macro|VB_SISLCDA
mdefine_line|#define VB_SISLCDA&t;&t;(VB_SIS302B|VB_SIS301C|VB_SIS301LV|VB_SIS302LV|VB_SIS302ELV)
DECL|macro|VB_SISYPBPR
mdefine_line|#define VB_SISYPBPR&t;&t;(VB_SIS301C|VB_SIS301LV|VB_SIS302LV|VB_SIS302ELV)
DECL|macro|VB_SISHIVISION
mdefine_line|#define VB_SISHIVISION&t;&t;(VB_SIS301|VB_SIS301B|VB_SIS302B)
multiline_comment|/* VBInfo */
DECL|macro|SetSimuScanMode
mdefine_line|#define SetSimuScanMode         0x0001   /* CR 30 */
DECL|macro|SwitchCRT2
mdefine_line|#define SwitchCRT2              0x0002
DECL|macro|SetCRT2ToAVIDEO
mdefine_line|#define SetCRT2ToAVIDEO         0x0004
DECL|macro|SetCRT2ToSVIDEO
mdefine_line|#define SetCRT2ToSVIDEO         0x0008
DECL|macro|SetCRT2ToSCART
mdefine_line|#define SetCRT2ToSCART          0x0010
DECL|macro|SetCRT2ToLCD
mdefine_line|#define SetCRT2ToLCD            0x0020
DECL|macro|SetCRT2ToRAMDAC
mdefine_line|#define SetCRT2ToRAMDAC         0x0040
DECL|macro|SetCRT2ToHiVision
mdefine_line|#define SetCRT2ToHiVision       0x0080   &t;&t;/* for SiS bridge */
DECL|macro|SetCRT2ToCHYPbPr
mdefine_line|#define SetCRT2ToCHYPbPr       &t;SetCRT2ToHiVision&t;/* for Chrontel   */
DECL|macro|SetNTSCTV
mdefine_line|#define SetNTSCTV               0x0000   /* CR 31 */
DECL|macro|SetPALTV
mdefine_line|#define SetPALTV                0x0100   &t;&t;/* Deprecated here, now in TVMode */
DECL|macro|SetInSlaveMode
mdefine_line|#define SetInSlaveMode          0x0200
DECL|macro|SetNotSimuMode
mdefine_line|#define SetNotSimuMode          0x0400
DECL|macro|SetNotSimuTVMode
mdefine_line|#define SetNotSimuTVMode        SetNotSimuMode
DECL|macro|SetDispDevSwitch
mdefine_line|#define SetDispDevSwitch        0x0800
DECL|macro|SetCRT2ToYPbPr525750
mdefine_line|#define SetCRT2ToYPbPr525750    0x0800
DECL|macro|LoadDACFlag
mdefine_line|#define LoadDACFlag             0x1000
DECL|macro|DisableCRT2Display
mdefine_line|#define DisableCRT2Display      0x2000
DECL|macro|DriverMode
mdefine_line|#define DriverMode              0x4000
DECL|macro|HotKeySwitch
mdefine_line|#define HotKeySwitch            0x8000
DECL|macro|SetCRT2ToLCDA
mdefine_line|#define SetCRT2ToLCDA           0x8000
multiline_comment|/* v-- Needs change in sis_vga.c if changed (GPIO) --v */
DECL|macro|SetCRT2ToTV
mdefine_line|#define SetCRT2ToTV             (SetCRT2ToYPbPr525750|SetCRT2ToHiVision|SetCRT2ToSCART|SetCRT2ToSVIDEO|SetCRT2ToAVIDEO)
DECL|macro|SetCRT2ToTVNoYPbPrHiVision
mdefine_line|#define SetCRT2ToTVNoYPbPrHiVision (SetCRT2ToSCART | SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)
DECL|macro|SetCRT2ToTVNoHiVision
mdefine_line|#define SetCRT2ToTVNoHiVision  &t;(SetCRT2ToYPbPr525750 | SetCRT2ToSCART | SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)
multiline_comment|/* SiS_ModeType */
DECL|macro|ModeText
mdefine_line|#define ModeText                0x00
DECL|macro|ModeCGA
mdefine_line|#define ModeCGA                 0x01
DECL|macro|ModeEGA
mdefine_line|#define ModeEGA                 0x02
DECL|macro|ModeVGA
mdefine_line|#define ModeVGA                 0x03
DECL|macro|Mode15Bpp
mdefine_line|#define Mode15Bpp               0x04
DECL|macro|Mode16Bpp
mdefine_line|#define Mode16Bpp               0x05
DECL|macro|Mode24Bpp
mdefine_line|#define Mode24Bpp               0x06
DECL|macro|Mode32Bpp
mdefine_line|#define Mode32Bpp               0x07
DECL|macro|ModeTypeMask
mdefine_line|#define ModeTypeMask            0x07
DECL|macro|IsTextMode
mdefine_line|#define IsTextMode              0x07
DECL|macro|DACInfoFlag
mdefine_line|#define DACInfoFlag             0x0018
DECL|macro|MemoryInfoFlag
mdefine_line|#define MemoryInfoFlag          0x01E0
DECL|macro|MemorySizeShift
mdefine_line|#define MemorySizeShift         5
multiline_comment|/* modeflag */
DECL|macro|Charx8Dot
mdefine_line|#define Charx8Dot               0x0200
DECL|macro|LineCompareOff
mdefine_line|#define LineCompareOff          0x0400
DECL|macro|CRT2Mode
mdefine_line|#define CRT2Mode                0x0800
DECL|macro|HalfDCLK
mdefine_line|#define HalfDCLK                0x1000
DECL|macro|NoSupportSimuTV
mdefine_line|#define NoSupportSimuTV         0x2000
DECL|macro|NoSupportLCDScale
mdefine_line|#define NoSupportLCDScale&t;0x4000 /* SiS bridge: No scaling possible (no matter what panel) */
DECL|macro|DoubleScanMode
mdefine_line|#define DoubleScanMode          0x8000
multiline_comment|/* Infoflag */
DECL|macro|SupportTV
mdefine_line|#define SupportTV               0x0008
DECL|macro|SupportTV1024
mdefine_line|#define SupportTV1024           0x0800
DECL|macro|SupportCHTV
mdefine_line|#define SupportCHTV &t;&t;0x0800
DECL|macro|Support64048060Hz
mdefine_line|#define Support64048060Hz       0x0800  /* Special for 640x480 LCD */
DECL|macro|SupportHiVision
mdefine_line|#define SupportHiVision         0x0010
DECL|macro|SupportYPbPr750p
mdefine_line|#define SupportYPbPr750p        0x1000
DECL|macro|SupportLCD
mdefine_line|#define SupportLCD              0x0020
DECL|macro|SupportRAMDAC2
mdefine_line|#define SupportRAMDAC2          0x0040&t;/* All           (&lt;= 100Mhz) */
DECL|macro|SupportRAMDAC2_135
mdefine_line|#define SupportRAMDAC2_135      0x0100  /* All except DH (&lt;= 135Mhz) */
DECL|macro|SupportRAMDAC2_162
mdefine_line|#define SupportRAMDAC2_162      0x0200  /* B, C          (&lt;= 162Mhz) */
DECL|macro|SupportRAMDAC2_202
mdefine_line|#define SupportRAMDAC2_202      0x0400  /* C             (&lt;= 202Mhz) */
DECL|macro|InterlaceMode
mdefine_line|#define InterlaceMode           0x0080
DECL|macro|SyncPP
mdefine_line|#define SyncPP                  0x0000
DECL|macro|SyncPN
mdefine_line|#define SyncPN                  0x4000
DECL|macro|SyncNP
mdefine_line|#define SyncNP                  0x8000
DECL|macro|SyncNN
mdefine_line|#define SyncNN                  0xc000
multiline_comment|/* SetFlag */
DECL|macro|ProgrammingCRT2
mdefine_line|#define ProgrammingCRT2         0x0001
DECL|macro|LowModeTests
mdefine_line|#define LowModeTests&t;&t;0x0002
multiline_comment|/* #define TVSimuMode           0x0002 - deprecated */
multiline_comment|/* #define RPLLDIV2XO           0x0004 - deprecated */
DECL|macro|LCDVESATiming
mdefine_line|#define LCDVESATiming           0x0008
DECL|macro|EnableLVDSDDA
mdefine_line|#define EnableLVDSDDA           0x0010
DECL|macro|SetDispDevSwitchFlag
mdefine_line|#define SetDispDevSwitchFlag    0x0020
DECL|macro|CheckWinDos
mdefine_line|#define CheckWinDos             0x0040
DECL|macro|SetDOSMode
mdefine_line|#define SetDOSMode              0x0080
multiline_comment|/* TVMode flag */
DECL|macro|TVSetPAL
mdefine_line|#define TVSetPAL&t;&t;0x0001
DECL|macro|TVSetNTSCJ
mdefine_line|#define TVSetNTSCJ&t;&t;0x0002
DECL|macro|TVSetPALM
mdefine_line|#define TVSetPALM&t;&t;0x0004
DECL|macro|TVSetPALN
mdefine_line|#define TVSetPALN&t;&t;0x0008
DECL|macro|TVSetCHOverScan
mdefine_line|#define TVSetCHOverScan&t;&t;0x0010
DECL|macro|TVSetYPbPr525i
mdefine_line|#define TVSetYPbPr525i&t;&t;0x0020 /* new 0x10 */
DECL|macro|TVSetYPbPr525p
mdefine_line|#define TVSetYPbPr525p&t;&t;0x0040 /* new 0x20 */
DECL|macro|TVSetYPbPr750p
mdefine_line|#define TVSetYPbPr750p&t;&t;0x0080 /* new 0x40 */
DECL|macro|TVSetHiVision
mdefine_line|#define TVSetHiVision&t;&t;0x0100 /* new 0x80; = 1080i, software-wise identical */
DECL|macro|TVSetTVSimuMode
mdefine_line|#define TVSetTVSimuMode&t;&t;0x0200 /* new 0x200, prev. 0x800 */
DECL|macro|TVRPLLDIV2XO
mdefine_line|#define TVRPLLDIV2XO&t;&t;0x0400 /* prev 0x1000 */
DECL|macro|TVSetNTSC1024
mdefine_line|#define TVSetNTSC1024&t;&t;0x0800 /* new 0x100, prev. 0x2000 */
DECL|macro|TVAspect43
mdefine_line|#define TVAspect43&t;&t;0x2000
DECL|macro|TVAspect169
mdefine_line|#define TVAspect169&t;&t;0x4000
DECL|macro|TVAspect43LB
mdefine_line|#define TVAspect43LB&t;&t;0x8000
multiline_comment|/* YPbPr flag (&gt;=315, &lt;661; converted to TVMode) */
DECL|macro|YPbPr525p
mdefine_line|#define YPbPr525p               0x0001
DECL|macro|YPbPr750p
mdefine_line|#define YPbPr750p               0x0002
DECL|macro|YPbPr525i
mdefine_line|#define YPbPr525i               0x0004
DECL|macro|YPbPrHiVision
mdefine_line|#define YPbPrHiVision           0x0008
DECL|macro|YPbPrModeMask
mdefine_line|#define YPbPrModeMask           (YPbPr750p | YPbPr525p | YPbPr525i | YPbPrHiVision)
multiline_comment|/* SysFlags (to identify special versions) */
DECL|macro|SF_Is651
mdefine_line|#define SF_Is651                0x0001
DECL|macro|SF_IsM650
mdefine_line|#define SF_IsM650               0x0002
DECL|macro|SF_Is652
mdefine_line|#define SF_Is652&t;&t;0x0004
DECL|macro|SF_IsM652
mdefine_line|#define SF_IsM652&t;&t;0x0008
DECL|macro|SF_IsM653
mdefine_line|#define SF_IsM653&t;&t;0x0010
DECL|macro|SF_IsM661
mdefine_line|#define SF_IsM661&t;&t;0x0020
DECL|macro|SF_IsM741
mdefine_line|#define SF_IsM741&t;&t;0x0040
DECL|macro|SF_IsM760
mdefine_line|#define SF_IsM760&t;&t;0x0080
DECL|macro|SF_760LFB
mdefine_line|#define SF_760LFB&t;&t;0x8000  /* 760: We have LFB */
multiline_comment|/* CR32 (Newer 630, and 315 series)&n;&n;   [0]   VB connected with CVBS&n;   [1]   VB connected with SVHS&n;   [2]   VB connected with SCART&n;   [3]   VB connected with LCD&n;   [4]   VB connected with CRT2 (secondary VGA)&n;   [5]   CRT1 monitor is connected&n;   [6]   VB connected with Hi-Vision TV&n;   [7]   &lt;= 330: VB connected with DVI combo connector&n;         &gt;= 661: VB connected to YPbPr&n;*/
multiline_comment|/* CR35 (300 series only) */
DECL|macro|TVOverScan
mdefine_line|#define TVOverScan              0x10
DECL|macro|TVOverScanShift
mdefine_line|#define TVOverScanShift         4
multiline_comment|/* CR35 (661 series only)&n;&n;   [0]    1 = PAL, 0 = NTSC&n;   [1]    1 = NTSC-J (if D0 = 0)&n;   [2]    1 = PALM (if D0 = 1)&n;   [3]    1 = PALN (if D0 = 1)&n;   [4]    1 = Overscan (Chrontel only)&n;   [7:5]  (only if D2 in CR38 is set)&n;          000  525i&n; &t;  001  525p&n;&t;  010  750p&n;&t;  011  1080i (or HiVision on 301, 301B)&n;&n;   These bits are being translated to TVMode flag.&n;&n;*/
multiline_comment|/*&n;   CR37&n;&n;   [0]   Set 24/18 bit (0/1) RGB to LVDS/TMDS transmitter (set by BIOS)&n;   [3:1] External chip&n;         300 series:&n;&t;    001   SiS301 (never seen)&n;&t;    010   LVDS&n;&t;    011   LVDS + Tumpion Zurac&n;&t;    100   LVDS + Chrontel 7005&n;&t;    110   Chrontel 7005&n;&t;  315/330 series&n;&t;    001   SiS30x (never seen)&n;&t;    010   LVDS&n;&t;    011   LVDS + Chrontel 7019&n;&t;  660 series [2:1] only:&n;&t;     reserved (now in CR38)&n;&t;  All other combinations reserved&n;   [3]    661 only: Pass 1:1 data&n;   [4]    LVDS: 0: Panel Link expands / 1: Panel Link does not expand&n;          30x:  0: Bridge scales      / 1: Bridge does not scale = Panel scales (if possible)&n;   [5]    LCD polarity select&n;          0: VESA DMT Standard&n;&t;  1: EDID 2.x defined&n;   [6]    LCD horizontal polarity select&n;          0: High active&n;&t;  1: Low active&n;   [7]    LCD vertical polarity select&n;          0: High active&n;&t;  1: Low active&n;*/
multiline_comment|/* CR37: LCDInfo */
DECL|macro|LCDRGB18Bit
mdefine_line|#define LCDRGB18Bit           0x0001
DECL|macro|LCDNonExpanding
mdefine_line|#define LCDNonExpanding       0x0010
DECL|macro|LCDSync
mdefine_line|#define LCDSync               0x0020
DECL|macro|LCDPass11
mdefine_line|#define LCDPass11             0x0100   /* 0: center screen, 1: Pass 1:1 data */
DECL|macro|LCDDualLink
mdefine_line|#define LCDDualLink&t;      0x0200
DECL|macro|DontExpandLCD
mdefine_line|#define DontExpandLCD&t;      LCDNonExpanding
DECL|macro|LCDNonExpandingShift
mdefine_line|#define LCDNonExpandingShift       4
DECL|macro|DontExpandLCDShift
mdefine_line|#define DontExpandLCDShift    LCDNonExpandingShift
DECL|macro|LCDSyncBit
mdefine_line|#define LCDSyncBit            0x00e0
DECL|macro|LCDSyncShift
mdefine_line|#define LCDSyncShift               6
multiline_comment|/* CR38 (315 series) */
DECL|macro|EnableDualEdge
mdefine_line|#define EnableDualEdge &t;&t;0x01
DECL|macro|SetToLCDA
mdefine_line|#define SetToLCDA&t;&t;0x02   /* LCD channel A (301C/302B/30x(E)LV and 650+LVDS only) */
DECL|macro|EnableCHScart
mdefine_line|#define EnableCHScart           0x04   /* Scart on Ch7019 (unofficial definition - TW) */
DECL|macro|EnableCHYPbPr
mdefine_line|#define EnableCHYPbPr           0x08   /* YPbPr on Ch7019 (480i HDTV); only on 650/Ch7019 systems */
DECL|macro|EnableSiSYPbPr
mdefine_line|#define EnableSiSYPbPr          0x08   /* Enable YPbPr mode (30xLV/301C only) */
DECL|macro|EnableYPbPr525i
mdefine_line|#define EnableYPbPr525i         0x00   /* Enable 525i YPbPr mode (30xLV/301C only) (mask 0x30) */
DECL|macro|EnableYPbPr525p
mdefine_line|#define EnableYPbPr525p         0x10   /* Enable 525p YPbPr mode (30xLV/301C only) (mask 0x30) */
DECL|macro|EnableYPbPr750p
mdefine_line|#define EnableYPbPr750p         0x20   /* Enable 750p YPbPr mode (30xLV/301C only) (mask 0x30) */
DECL|macro|EnableYPbPr1080i
mdefine_line|#define EnableYPbPr1080i        0x30   /* Enable 1080i YPbPr mode (30xLV/301C only) (mask 0x30) */
DECL|macro|EnablePALM
mdefine_line|#define EnablePALM              0x40   /* 1 = Set PALM */
DECL|macro|EnablePALN
mdefine_line|#define EnablePALN              0x80   /* 1 = Set PALN */
DECL|macro|EnableNTSCJ
mdefine_line|#define EnableNTSCJ             EnablePALM  /* Not BIOS */
multiline_comment|/* CR38 (661 and later)&n;  D[7:5]  000 No VB&n;          001 301 series VB&n;&t;  010 LVDS&n;&t;  011 Chrontel 7019&n;&t;  100 Conexant&n;  D2      Enable YPbPr output (see CR35)&n;  D[1:0]  LCDA (like before)&n;*/
DECL|macro|EnablePALMN
mdefine_line|#define EnablePALMN             0x40   /* Romflag: 1 = Allow PALM/PALN */
multiline_comment|/* CR39 (650 only) */
DECL|macro|LCDPass1_1
mdefine_line|#define LCDPass1_1&t;&t;0x01   /* 0: center screen, 1: pass 1:1 data output  */
DECL|macro|Enable302LV_DualLink
mdefine_line|#define Enable302LV_DualLink    0x04   /* 302LV only; enable dual link */
multiline_comment|/* CR39 (661 and later)&n;   D[1:0] YPbPr Aspect Ratio&n;          00 4:3 letterbox&n;&t;  01 4:3&n;&t;  10 16:9&n;&t;  11 4:3&n;*/
multiline_comment|/* CR3B (651+301C)&n;   D[1:0] YPbPr Aspect Ratio&n;          ?&n;*/
multiline_comment|/* CR79 (315/330 series only; not 661 and later)&n;   [3-0] Notify driver&n;         0001 Mode Switch event (set by BIOS)&n;&t; 0010 Epansion On/Off event&n;&t; 0011 TV UnderScan/OverScan event&n;&t; 0100 Set Brightness event&n;&t; 0101 Set Contrast event&n;&t; 0110 Set Mute event&n;&t; 0111 Set Volume Up/Down event&n;   [4]   Enable Backlight Control by BIOS/driver &n;         (set by driver; set means that the BIOS should&n;&t; not touch the backlight registers because eg.&n;&t; the driver already switched off the backlight)&n;   [5]   PAL/NTSC (set by BIOS)&n;   [6]   Expansion On/Off (set by BIOS; copied to CR32[4])&n;   [7]   TV UnderScan/OverScan (set by BIOS)&n;*/
multiline_comment|/* LCDResInfo */
DECL|macro|Panel300_800x600
mdefine_line|#define Panel300_800x600        0x01&t;/* CR36 */
DECL|macro|Panel300_1024x768
mdefine_line|#define Panel300_1024x768       0x02
DECL|macro|Panel300_1280x1024
mdefine_line|#define Panel300_1280x1024      0x03
DECL|macro|Panel300_1280x960
mdefine_line|#define Panel300_1280x960       0x04
DECL|macro|Panel300_640x480
mdefine_line|#define Panel300_640x480        0x05
DECL|macro|Panel300_1024x600
mdefine_line|#define Panel300_1024x600       0x06
DECL|macro|Panel300_1152x768
mdefine_line|#define Panel300_1152x768       0x07
DECL|macro|Panel300_1280x768
mdefine_line|#define Panel300_1280x768       0x0a
DECL|macro|Panel300_320x480
mdefine_line|#define Panel300_320x480        0x0e &t;/* fstn - This is fake, can be any */
DECL|macro|Panel300_Custom
mdefine_line|#define Panel300_Custom&t;&t;0x0f
DECL|macro|Panel300_Barco1366
mdefine_line|#define Panel300_Barco1366      0x10
DECL|macro|Panel310_800x600
mdefine_line|#define Panel310_800x600        0x01
DECL|macro|Panel310_1024x768
mdefine_line|#define Panel310_1024x768       0x02
DECL|macro|Panel310_1280x1024
mdefine_line|#define Panel310_1280x1024      0x03
DECL|macro|Panel310_640x480
mdefine_line|#define Panel310_640x480        0x04
DECL|macro|Panel310_1024x600
mdefine_line|#define Panel310_1024x600       0x05
DECL|macro|Panel310_1152x864
mdefine_line|#define Panel310_1152x864       0x06
DECL|macro|Panel310_1280x960
mdefine_line|#define Panel310_1280x960       0x07
DECL|macro|Panel310_1152x768
mdefine_line|#define Panel310_1152x768       0x08&t;/* LVDS only */
DECL|macro|Panel310_1400x1050
mdefine_line|#define Panel310_1400x1050      0x09
DECL|macro|Panel310_1280x768
mdefine_line|#define Panel310_1280x768       0x0a
DECL|macro|Panel310_1600x1200
mdefine_line|#define Panel310_1600x1200      0x0b
DECL|macro|Panel310_640x480_2
mdefine_line|#define Panel310_640x480_2      0x0c
DECL|macro|Panel310_640x480_3
mdefine_line|#define Panel310_640x480_3      0x0d
DECL|macro|Panel310_320x480
mdefine_line|#define Panel310_320x480        0x0e    /* fstn - TW: This is fake, can be any */
DECL|macro|Panel310_Custom
mdefine_line|#define Panel310_Custom&t;&t;0x0f
DECL|macro|Panel661_800x600
mdefine_line|#define Panel661_800x600        0x01
DECL|macro|Panel661_1024x768
mdefine_line|#define Panel661_1024x768       0x02
DECL|macro|Panel661_1280x1024
mdefine_line|#define Panel661_1280x1024      0x03
DECL|macro|Panel661_640x480
mdefine_line|#define Panel661_640x480        0x04
DECL|macro|Panel661_1024x600
mdefine_line|#define Panel661_1024x600       0x05
DECL|macro|Panel661_1152x864
mdefine_line|#define Panel661_1152x864       0x06
DECL|macro|Panel661_1280x960
mdefine_line|#define Panel661_1280x960       0x07
DECL|macro|Panel661_1152x768
mdefine_line|#define Panel661_1152x768       0x08
DECL|macro|Panel661_1400x1050
mdefine_line|#define Panel661_1400x1050      0x09
DECL|macro|Panel661_1280x768
mdefine_line|#define Panel661_1280x768       0x0a
DECL|macro|Panel661_1600x1200
mdefine_line|#define Panel661_1600x1200      0x0b
DECL|macro|Panel661_1280x800
mdefine_line|#define Panel661_1280x800       0x0c
DECL|macro|Panel661_1680x1050
mdefine_line|#define Panel661_1680x1050      0x0d
DECL|macro|Panel661_1280x720
mdefine_line|#define Panel661_1280x720       0x0e
DECL|macro|Panel661_Custom
mdefine_line|#define Panel661_Custom&t;&t;0x0f
DECL|macro|Panel_800x600
mdefine_line|#define Panel_800x600           0x01&t;/* Unified values */
DECL|macro|Panel_1024x768
mdefine_line|#define Panel_1024x768          0x02    /* MUST match BIOS values from 0-e */
DECL|macro|Panel_1280x1024
mdefine_line|#define Panel_1280x1024         0x03
DECL|macro|Panel_640x480
mdefine_line|#define Panel_640x480           0x04
DECL|macro|Panel_1024x600
mdefine_line|#define Panel_1024x600          0x05
DECL|macro|Panel_1152x864
mdefine_line|#define Panel_1152x864          0x06
DECL|macro|Panel_1280x960
mdefine_line|#define Panel_1280x960          0x07
DECL|macro|Panel_1152x768
mdefine_line|#define Panel_1152x768          0x08&t;/* LVDS only */
DECL|macro|Panel_1400x1050
mdefine_line|#define Panel_1400x1050         0x09
DECL|macro|Panel_1280x768
mdefine_line|#define Panel_1280x768          0x0a    /* 30xB/C and LVDS only (BIOS: all) */
DECL|macro|Panel_1600x1200
mdefine_line|#define Panel_1600x1200         0x0b
DECL|macro|Panel_1280x800
mdefine_line|#define Panel_1280x800&t;&t;0x0c    /* 661etc (TMDS) */
DECL|macro|Panel_1680x1050
mdefine_line|#define Panel_1680x1050         0x0d    /* 661etc  */
DECL|macro|Panel_1280x720
mdefine_line|#define Panel_1280x720&t;&t;0x0e    /* 661etc  */
DECL|macro|Panel_Custom
mdefine_line|#define Panel_Custom&t;&t;0x0f&t;/* MUST BE 0x0f (for DVI DDC detection) */
DECL|macro|Panel_320x480
mdefine_line|#define Panel_320x480           0x10    /* SiS 550 fstn - TW: This is fake, can be any */
DECL|macro|Panel_Barco1366
mdefine_line|#define Panel_Barco1366         0x11
DECL|macro|Panel_848x480
mdefine_line|#define Panel_848x480&t;&t;0x12
DECL|macro|Panel_640x480_2
mdefine_line|#define Panel_640x480_2&t;&t;0x13    /* SiS 550 */
DECL|macro|Panel_640x480_3
mdefine_line|#define Panel_640x480_3&t;&t;0x14    /* SiS 550 */
DECL|macro|Panel_1280x768_2
mdefine_line|#define Panel_1280x768_2        0x15&t;/* 30xLV */
DECL|macro|Panel_1280x768_3
mdefine_line|#define Panel_1280x768_3        0x16    /* (unused) */
DECL|macro|Panel_1280x800_2
mdefine_line|#define Panel_1280x800_2&t;0x17    /* 30xLV */
multiline_comment|/* Index in ModeResInfo table */
DECL|macro|SIS_RI_320x200
mdefine_line|#define SIS_RI_320x200    0
DECL|macro|SIS_RI_320x240
mdefine_line|#define SIS_RI_320x240    1
DECL|macro|SIS_RI_320x400
mdefine_line|#define SIS_RI_320x400    2
DECL|macro|SIS_RI_400x300
mdefine_line|#define SIS_RI_400x300    3
DECL|macro|SIS_RI_512x384
mdefine_line|#define SIS_RI_512x384    4
DECL|macro|SIS_RI_640x400
mdefine_line|#define SIS_RI_640x400    5
DECL|macro|SIS_RI_640x480
mdefine_line|#define SIS_RI_640x480    6
DECL|macro|SIS_RI_800x600
mdefine_line|#define SIS_RI_800x600    7
DECL|macro|SIS_RI_1024x768
mdefine_line|#define SIS_RI_1024x768   8
DECL|macro|SIS_RI_1280x1024
mdefine_line|#define SIS_RI_1280x1024  9
DECL|macro|SIS_RI_1600x1200
mdefine_line|#define SIS_RI_1600x1200 10
DECL|macro|SIS_RI_1920x1440
mdefine_line|#define SIS_RI_1920x1440 11
DECL|macro|SIS_RI_2048x1536
mdefine_line|#define SIS_RI_2048x1536 12
DECL|macro|SIS_RI_720x480
mdefine_line|#define SIS_RI_720x480   13
DECL|macro|SIS_RI_720x576
mdefine_line|#define SIS_RI_720x576   14
DECL|macro|SIS_RI_1280x960
mdefine_line|#define SIS_RI_1280x960  15
DECL|macro|SIS_RI_800x480
mdefine_line|#define SIS_RI_800x480   16
DECL|macro|SIS_RI_1024x576
mdefine_line|#define SIS_RI_1024x576  17
DECL|macro|SIS_RI_1280x720
mdefine_line|#define SIS_RI_1280x720  18
DECL|macro|SIS_RI_856x480
mdefine_line|#define SIS_RI_856x480   19
DECL|macro|SIS_RI_1280x768
mdefine_line|#define SIS_RI_1280x768  20
DECL|macro|SIS_RI_1400x1050
mdefine_line|#define SIS_RI_1400x1050 21
DECL|macro|SIS_RI_1152x864
mdefine_line|#define SIS_RI_1152x864  22  /* Up to here SiS conforming */
DECL|macro|SIS_RI_848x480
mdefine_line|#define SIS_RI_848x480   23
DECL|macro|SIS_RI_1360x768
mdefine_line|#define SIS_RI_1360x768  24
DECL|macro|SIS_RI_1024x600
mdefine_line|#define SIS_RI_1024x600  25
DECL|macro|SIS_RI_1152x768
mdefine_line|#define SIS_RI_1152x768  26
DECL|macro|SIS_RI_768x576
mdefine_line|#define SIS_RI_768x576   27
DECL|macro|SIS_RI_1360x1024
mdefine_line|#define SIS_RI_1360x1024 28
DECL|macro|SIS_RI_1680x1050
mdefine_line|#define SIS_RI_1680x1050 29
DECL|macro|SIS_RI_1280x800
mdefine_line|#define SIS_RI_1280x800  30
DECL|macro|SIS_RI_1920x1080
mdefine_line|#define SIS_RI_1920x1080 31
DECL|macro|SIS_RI_960x540
mdefine_line|#define SIS_RI_960x540   32
DECL|macro|SIS_RI_960x600
mdefine_line|#define SIS_RI_960x600   33
multiline_comment|/* CR5F */
DECL|macro|IsM650
mdefine_line|#define IsM650                  0x80
multiline_comment|/* Timing data */
DECL|macro|NTSCHT
mdefine_line|#define NTSCHT                  1716
DECL|macro|NTSC2HT
mdefine_line|#define NTSC2HT                 1920
DECL|macro|NTSCVT
mdefine_line|#define NTSCVT                  525
DECL|macro|PALHT
mdefine_line|#define PALHT                   1728
DECL|macro|PALVT
mdefine_line|#define PALVT                   625
DECL|macro|StHiTVHT
mdefine_line|#define StHiTVHT                892
DECL|macro|StHiTVVT
mdefine_line|#define StHiTVVT                1126
DECL|macro|StHiTextTVHT
mdefine_line|#define StHiTextTVHT            1000
DECL|macro|StHiTextTVVT
mdefine_line|#define StHiTextTVVT            1126
DECL|macro|ExtHiTVHT
mdefine_line|#define ExtHiTVHT               2100
DECL|macro|ExtHiTVVT
mdefine_line|#define ExtHiTVVT               1125
multiline_comment|/* Indices in (VB)VCLKData tables */
DECL|macro|VCLK28
mdefine_line|#define VCLK28                  0x00   /* Index in VCLKData table (300 and 315) */
DECL|macro|VCLK40
mdefine_line|#define VCLK40                  0x04   /* Index in VCLKData table (300 and 315) */
DECL|macro|VCLK65_300
mdefine_line|#define VCLK65_300              0x09   /* Index in VCLKData table (300) */
DECL|macro|VCLK108_2_300
mdefine_line|#define VCLK108_2_300           0x14   /* Index in VCLKData table (300) */
DECL|macro|VCLK81_300
mdefine_line|#define VCLK81_300&t;&t;0x3f   /* Index in VCLKData table (300) */
DECL|macro|VCLK108_3_300
mdefine_line|#define VCLK108_3_300           0x42   /* Index in VCLKData table (300) */
DECL|macro|VCLK100_300
mdefine_line|#define VCLK100_300             0x43   /* Index in VCLKData table (300) */
DECL|macro|VCLK34_300
mdefine_line|#define VCLK34_300              0x3d   /* Index in VCLKData table (300) */
DECL|macro|VCLK_CUSTOM_300
mdefine_line|#define VCLK_CUSTOM_300&t;&t;0x47
DECL|macro|VCLK65_315
mdefine_line|#define VCLK65_315              0x0b   /* Index in (VB)VCLKData table (315) */
DECL|macro|VCLK108_2_315
mdefine_line|#define VCLK108_2_315           0x19   /* Index in (VB)VCLKData table (315) */
DECL|macro|VCLK81_315
mdefine_line|#define VCLK81_315&t;&t;0x5b   /* Index in (VB)VCLKData table (315) */
DECL|macro|VCLK162_315
mdefine_line|#define VCLK162_315             0x5e   /* Index in (VB)VCLKData table (315) */
DECL|macro|VCLK108_3_315
mdefine_line|#define VCLK108_3_315           0x45   /* Index in VBVCLKData table (315) */
DECL|macro|VCLK100_315
mdefine_line|#define VCLK100_315             0x46   /* Index in VBVCLKData table (315) */
DECL|macro|VCLK34_315
mdefine_line|#define VCLK34_315              0x55
DECL|macro|VCLK68_315
mdefine_line|#define VCLK68_315&t;&t;0x0d
DECL|macro|VCLK_1280x800_315_2
mdefine_line|#define VCLK_1280x800_315_2&t;0x5c   /* Index in VBVCLKData table (315) */
DECL|macro|VCLK121_315
mdefine_line|#define VCLK121_315&t;&t;0x5d   /* Index in VBVCLKData table (315) */
DECL|macro|VCLK_1280x720
mdefine_line|#define VCLK_1280x720&t;&t;0x5f
DECL|macro|VCLK_1280x768_2
mdefine_line|#define VCLK_1280x768_2&t;&t;0x60
DECL|macro|VCLK_1280x768_3
mdefine_line|#define VCLK_1280x768_3&t;&t;0x61   /* (unused?) */
DECL|macro|VCLK_CUSTOM_315
mdefine_line|#define VCLK_CUSTOM_315&t;&t;0x62
DECL|macro|VCLK_1280x720_2
mdefine_line|#define VCLK_1280x720_2&t;&t;0x63
DECL|macro|VCLK_720x480
mdefine_line|#define VCLK_720x480&t;&t;0x67
DECL|macro|VCLK_720x576
mdefine_line|#define VCLK_720x576&t;&t;0x68
DECL|macro|VCLK_768x576
mdefine_line|#define VCLK_768x576&t;&t;0x68
DECL|macro|VCLK_848x480
mdefine_line|#define VCLK_848x480&t;&t;0x65
DECL|macro|VCLK_856x480
mdefine_line|#define VCLK_856x480&t;&t;0x66
DECL|macro|VCLK_800x480
mdefine_line|#define VCLK_800x480&t;&t;0x65
DECL|macro|VCLK_1024x576
mdefine_line|#define VCLK_1024x576&t;&t;0x51
DECL|macro|VCLK_1152x864
mdefine_line|#define VCLK_1152x864&t;&t;0x64
DECL|macro|VCLK_1360x768
mdefine_line|#define VCLK_1360x768&t;&t;0x58
DECL|macro|VCLK_1280x800_315
mdefine_line|#define VCLK_1280x800_315&t;0x6c
DECL|macro|TVCLKBASE_300
mdefine_line|#define TVCLKBASE_300&t;&t;0x21   /* Indices on TV clocks in VCLKData table (300) */
DECL|macro|TVCLKBASE_315
mdefine_line|#define TVCLKBASE_315&t;        0x3a   /* Indices on TV clocks in (VB)VCLKData table (315) */
DECL|macro|TVVCLKDIV2
mdefine_line|#define TVVCLKDIV2              0x00   /* Index relative to TVCLKBASE */
DECL|macro|TVVCLK
mdefine_line|#define TVVCLK                  0x01   /* Index relative to TVCLKBASE */
DECL|macro|HiTVVCLKDIV2
mdefine_line|#define HiTVVCLKDIV2            0x02   /* Index relative to TVCLKBASE */
DECL|macro|HiTVVCLK
mdefine_line|#define HiTVVCLK                0x03   /* Index relative to TVCLKBASE */
DECL|macro|HiTVSimuVCLK
mdefine_line|#define HiTVSimuVCLK            0x04   /* Index relative to TVCLKBASE */
DECL|macro|HiTVTextVCLK
mdefine_line|#define HiTVTextVCLK            0x05   /* Index relative to TVCLKBASE */
DECL|macro|YPbPr750pVCLK
mdefine_line|#define YPbPr750pVCLK&t;&t;0x25   /* Index relative to TVCLKBASE; was 0x0f NOT relative */
multiline_comment|/* ------------------------------ */
DECL|macro|SetSCARTOutput
mdefine_line|#define SetSCARTOutput          0x01
DECL|macro|HotPlugFunction
mdefine_line|#define HotPlugFunction         0x08
DECL|macro|StStructSize
mdefine_line|#define StStructSize            0x06
DECL|macro|SIS_VIDEO_CAPTURE
mdefine_line|#define SIS_VIDEO_CAPTURE       0x00 - 0x30
DECL|macro|SIS_VIDEO_PLAYBACK
mdefine_line|#define SIS_VIDEO_PLAYBACK      0x02 - 0x30
DECL|macro|SIS_CRT2_PORT_04
mdefine_line|#define SIS_CRT2_PORT_04        0x04 - 0x30
DECL|macro|SIS_CRT2_PORT_10
mdefine_line|#define SIS_CRT2_PORT_10        0x10 - 0x30
DECL|macro|SIS_CRT2_PORT_12
mdefine_line|#define SIS_CRT2_PORT_12        0x12 - 0x30
DECL|macro|SIS_CRT2_PORT_14
mdefine_line|#define SIS_CRT2_PORT_14        0x14 - 0x30
DECL|macro|ADR_CRT2PtrData
mdefine_line|#define ADR_CRT2PtrData         0x20E
DECL|macro|offset_Zurac
mdefine_line|#define offset_Zurac            0x210   /* TW: Trumpion Zurac data pointer */
DECL|macro|ADR_LVDSDesPtrData
mdefine_line|#define ADR_LVDSDesPtrData      0x212
DECL|macro|ADR_LVDSCRT1DataPtr
mdefine_line|#define ADR_LVDSCRT1DataPtr     0x214
DECL|macro|ADR_CHTVVCLKPtr
mdefine_line|#define ADR_CHTVVCLKPtr         0x216
DECL|macro|ADR_CHTVRegDataPtr
mdefine_line|#define ADR_CHTVRegDataPtr      0x218
DECL|macro|LCDDataLen
mdefine_line|#define LCDDataLen              8
DECL|macro|HiTVDataLen
mdefine_line|#define HiTVDataLen             12
DECL|macro|TVDataLen
mdefine_line|#define TVDataLen               16
DECL|macro|LVDSDataLen
mdefine_line|#define LVDSDataLen             6
DECL|macro|LVDSDesDataLen
mdefine_line|#define LVDSDesDataLen          3
DECL|macro|ActiveNonExpanding
mdefine_line|#define ActiveNonExpanding      0x40
DECL|macro|ActiveNonExpandingShift
mdefine_line|#define ActiveNonExpandingShift 6
DECL|macro|ActivePAL
mdefine_line|#define ActivePAL               0x20
DECL|macro|ActivePALShift
mdefine_line|#define ActivePALShift          5
DECL|macro|ModeSwitchStatus
mdefine_line|#define ModeSwitchStatus        0x0F
DECL|macro|SoftTVType
mdefine_line|#define SoftTVType              0x40
DECL|macro|SoftSettingAddr
mdefine_line|#define SoftSettingAddr         0x52
DECL|macro|ModeSettingAddr
mdefine_line|#define ModeSettingAddr         0x53
DECL|macro|_PanelType00
mdefine_line|#define _PanelType00             0x00
DECL|macro|_PanelType01
mdefine_line|#define _PanelType01             0x08
DECL|macro|_PanelType02
mdefine_line|#define _PanelType02             0x10
DECL|macro|_PanelType03
mdefine_line|#define _PanelType03             0x18
DECL|macro|_PanelType04
mdefine_line|#define _PanelType04             0x20
DECL|macro|_PanelType05
mdefine_line|#define _PanelType05             0x28
DECL|macro|_PanelType06
mdefine_line|#define _PanelType06             0x30
DECL|macro|_PanelType07
mdefine_line|#define _PanelType07             0x38
DECL|macro|_PanelType08
mdefine_line|#define _PanelType08             0x40
DECL|macro|_PanelType09
mdefine_line|#define _PanelType09             0x48
DECL|macro|_PanelType0A
mdefine_line|#define _PanelType0A             0x50
DECL|macro|_PanelType0B
mdefine_line|#define _PanelType0B             0x58
DECL|macro|_PanelType0C
mdefine_line|#define _PanelType0C             0x60
DECL|macro|_PanelType0D
mdefine_line|#define _PanelType0D             0x68
DECL|macro|_PanelType0E
mdefine_line|#define _PanelType0E             0x70
DECL|macro|_PanelType0F
mdefine_line|#define _PanelType0F             0x78
DECL|macro|PRIMARY_VGA
mdefine_line|#define PRIMARY_VGA       &t;0     /* 1: SiS is primary vga 0:SiS is secondary vga */
DECL|macro|BIOSIDCodeAddr
mdefine_line|#define BIOSIDCodeAddr          0x235  /* Offsets to ptrs in BIOS image */
DECL|macro|OEMUtilIDCodeAddr
mdefine_line|#define OEMUtilIDCodeAddr       0x237
DECL|macro|VBModeIDTableAddr
mdefine_line|#define VBModeIDTableAddr       0x239
DECL|macro|OEMTVPtrAddr
mdefine_line|#define OEMTVPtrAddr            0x241
DECL|macro|PhaseTableAddr
mdefine_line|#define PhaseTableAddr          0x243
DECL|macro|NTSCFilterTableAddr
mdefine_line|#define NTSCFilterTableAddr     0x245
DECL|macro|PALFilterTableAddr
mdefine_line|#define PALFilterTableAddr      0x247
DECL|macro|OEMLCDPtr_1Addr
mdefine_line|#define OEMLCDPtr_1Addr         0x249
DECL|macro|OEMLCDPtr_2Addr
mdefine_line|#define OEMLCDPtr_2Addr         0x24B
DECL|macro|LCDHPosTable_1Addr
mdefine_line|#define LCDHPosTable_1Addr      0x24D
DECL|macro|LCDHPosTable_2Addr
mdefine_line|#define LCDHPosTable_2Addr      0x24F
DECL|macro|LCDVPosTable_1Addr
mdefine_line|#define LCDVPosTable_1Addr      0x251
DECL|macro|LCDVPosTable_2Addr
mdefine_line|#define LCDVPosTable_2Addr      0x253
DECL|macro|OEMLCDPIDTableAddr
mdefine_line|#define OEMLCDPIDTableAddr      0x255
DECL|macro|VBModeStructSize
mdefine_line|#define VBModeStructSize        5
DECL|macro|PhaseTableSize
mdefine_line|#define PhaseTableSize          4
DECL|macro|FilterTableSize
mdefine_line|#define FilterTableSize         4
DECL|macro|LCDHPosTableSize
mdefine_line|#define LCDHPosTableSize        7
DECL|macro|LCDVPosTableSize
mdefine_line|#define LCDVPosTableSize        5
DECL|macro|OEMLVDSPIDTableSize
mdefine_line|#define OEMLVDSPIDTableSize     4
DECL|macro|LVDSHPosTableSize
mdefine_line|#define LVDSHPosTableSize       4
DECL|macro|LVDSVPosTableSize
mdefine_line|#define LVDSVPosTableSize       6
DECL|macro|VB_ModeID
mdefine_line|#define VB_ModeID               0
DECL|macro|VB_TVTableIndex
mdefine_line|#define VB_TVTableIndex         1
DECL|macro|VB_LCDTableIndex
mdefine_line|#define VB_LCDTableIndex        2
DECL|macro|VB_LCDHIndex
mdefine_line|#define VB_LCDHIndex            3
DECL|macro|VB_LCDVIndex
mdefine_line|#define VB_LCDVIndex            4
DECL|macro|OEMLCDEnable
mdefine_line|#define OEMLCDEnable            0x0001
DECL|macro|OEMLCDDelayEnable
mdefine_line|#define OEMLCDDelayEnable       0x0002
DECL|macro|OEMLCDPOSEnable
mdefine_line|#define OEMLCDPOSEnable         0x0004
DECL|macro|OEMTVEnable
mdefine_line|#define OEMTVEnable             0x0100
DECL|macro|OEMTVDelayEnable
mdefine_line|#define OEMTVDelayEnable        0x0200
DECL|macro|OEMTVFlickerEnable
mdefine_line|#define OEMTVFlickerEnable      0x0400
DECL|macro|OEMTVPhaseEnable
mdefine_line|#define OEMTVPhaseEnable        0x0800
DECL|macro|OEMTVFilterEnable
mdefine_line|#define OEMTVFilterEnable       0x1000
DECL|macro|OEMLCDPanelIDSupport
mdefine_line|#define OEMLCDPanelIDSupport    0x0080
multiline_comment|/*&n;  =============================================================&n;   &t;&t;  for 315 series (old data layout)&n;  =============================================================&n;*/
DECL|macro|SoftDRAMType
mdefine_line|#define SoftDRAMType        0x80
DECL|macro|SoftSetting_OFFSET
mdefine_line|#define SoftSetting_OFFSET  0x52
DECL|macro|SR07_OFFSET
mdefine_line|#define SR07_OFFSET  0x7C
DECL|macro|SR15_OFFSET
mdefine_line|#define SR15_OFFSET  0x7D
DECL|macro|SR16_OFFSET
mdefine_line|#define SR16_OFFSET  0x81
DECL|macro|SR17_OFFSET
mdefine_line|#define SR17_OFFSET  0x85
DECL|macro|SR19_OFFSET
mdefine_line|#define SR19_OFFSET  0x8D
DECL|macro|SR1F_OFFSET
mdefine_line|#define SR1F_OFFSET  0x99
DECL|macro|SR21_OFFSET
mdefine_line|#define SR21_OFFSET  0x9A
DECL|macro|SR22_OFFSET
mdefine_line|#define SR22_OFFSET  0x9B
DECL|macro|SR23_OFFSET
mdefine_line|#define SR23_OFFSET  0x9C
DECL|macro|SR24_OFFSET
mdefine_line|#define SR24_OFFSET  0x9D
DECL|macro|SR25_OFFSET
mdefine_line|#define SR25_OFFSET  0x9E
DECL|macro|SR31_OFFSET
mdefine_line|#define SR31_OFFSET  0x9F
DECL|macro|SR32_OFFSET
mdefine_line|#define SR32_OFFSET  0xA0
DECL|macro|SR33_OFFSET
mdefine_line|#define SR33_OFFSET  0xA1
DECL|macro|CR40_OFFSET
mdefine_line|#define CR40_OFFSET  0xA2
DECL|macro|SR25_1_OFFSET
mdefine_line|#define SR25_1_OFFSET  0xF6
DECL|macro|CR49_OFFSET
mdefine_line|#define CR49_OFFSET  0xF7
DECL|macro|VB310Data_1_2_Offset
mdefine_line|#define VB310Data_1_2_Offset  0xB6
DECL|macro|VB310Data_4_D_Offset
mdefine_line|#define VB310Data_4_D_Offset  0xB7
DECL|macro|VB310Data_4_E_Offset
mdefine_line|#define VB310Data_4_E_Offset  0xB8
DECL|macro|VB310Data_4_10_Offset
mdefine_line|#define VB310Data_4_10_Offset 0xBB
DECL|macro|RGBSenseDataOffset
mdefine_line|#define RGBSenseDataOffset    0xBD
DECL|macro|YCSenseDataOffset
mdefine_line|#define YCSenseDataOffset     0xBF
DECL|macro|VideoSenseDataOffset
mdefine_line|#define VideoSenseDataOffset  0xC1
DECL|macro|OutputSelectOffset
mdefine_line|#define OutputSelectOffset    0xF3
DECL|macro|ECLK_MCLK_DISTANCE
mdefine_line|#define ECLK_MCLK_DISTANCE  0x14
DECL|macro|VBIOSTablePointerStart
mdefine_line|#define VBIOSTablePointerStart    0x100
DECL|macro|StandTablePtrOffset
mdefine_line|#define StandTablePtrOffset       VBIOSTablePointerStart+0x02
DECL|macro|EModeIDTablePtrOffset
mdefine_line|#define EModeIDTablePtrOffset     VBIOSTablePointerStart+0x04
DECL|macro|CRT1TablePtrOffset
mdefine_line|#define CRT1TablePtrOffset        VBIOSTablePointerStart+0x06
DECL|macro|ScreenOffsetPtrOffset
mdefine_line|#define ScreenOffsetPtrOffset     VBIOSTablePointerStart+0x08
DECL|macro|VCLKDataPtrOffset
mdefine_line|#define VCLKDataPtrOffset         VBIOSTablePointerStart+0x0A
DECL|macro|MCLKDataPtrOffset
mdefine_line|#define MCLKDataPtrOffset         VBIOSTablePointerStart+0x0E
DECL|macro|CRT2PtrDataPtrOffset
mdefine_line|#define CRT2PtrDataPtrOffset      VBIOSTablePointerStart+0x10
DECL|macro|TVAntiFlickPtrOffset
mdefine_line|#define TVAntiFlickPtrOffset      VBIOSTablePointerStart+0x12
DECL|macro|TVDelayPtr1Offset
mdefine_line|#define TVDelayPtr1Offset         VBIOSTablePointerStart+0x14
DECL|macro|TVPhaseIncrPtr1Offset
mdefine_line|#define TVPhaseIncrPtr1Offset     VBIOSTablePointerStart+0x16
DECL|macro|TVYFilterPtr1Offset
mdefine_line|#define TVYFilterPtr1Offset       VBIOSTablePointerStart+0x18
DECL|macro|LCDDelayPtr1Offset
mdefine_line|#define LCDDelayPtr1Offset        VBIOSTablePointerStart+0x20
DECL|macro|TVEdgePtr1Offset
mdefine_line|#define TVEdgePtr1Offset          VBIOSTablePointerStart+0x24
DECL|macro|CRT2Delay1Offset
mdefine_line|#define CRT2Delay1Offset          VBIOSTablePointerStart+0x28
macro_line|#endif
eof
