multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/sis/initdef.h,v 1.4 2000/12/02 01:16:17 dawes Exp $ */
macro_line|#ifndef _INITDEF_
DECL|macro|_INITDEF_
mdefine_line|#define _INITDEF_
DECL|macro|SiS300
mdefine_line|#define SiS300                  0x0300
DECL|macro|SiS540
mdefine_line|#define SiS540                  0x5300
DECL|macro|SiS630
mdefine_line|#define SiS630                  0x6300
DECL|macro|SiS730
mdefine_line|#define SiS730                  0x6300
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
DECL|macro|VB_SIS30xLV
mdefine_line|#define VB_SIS30xLV&t;&t;VB_SIS301LV
DECL|macro|VB_SIS30xNEW
mdefine_line|#define VB_SIS30xNEW&t;&t;VB_SIS302LV
DECL|macro|VB_NoLCD
mdefine_line|#define VB_NoLCD        &t;0x8000
DECL|macro|VB_SIS301BLV302BLV
mdefine_line|#define VB_SIS301BLV302BLV      (VB_SIS301B|VB_SIS302B|VB_SIS301LV|VB_SIS302LV)
DECL|macro|VB_SIS301B302B
mdefine_line|#define VB_SIS301B302B          (VB_SIS301B|VB_SIS302B)
DECL|macro|VB_SIS301LV302LV
mdefine_line|#define VB_SIS301LV302LV        (VB_SIS301LV|VB_SIS302LV)
DECL|macro|IS_SIS650740
mdefine_line|#define IS_SIS650740            ((HwDeviceExtension-&gt;jChipType &gt;= SIS_650) &amp;&amp; (HwDeviceExtension-&gt;jChipType &lt; SIS_330))
DECL|macro|IS_SIS650
mdefine_line|#define IS_SIS650&t;&t;(HwDeviceExtension-&gt;jChipType == SIS_650)
DECL|macro|IS_SIS740
mdefine_line|#define IS_SIS740&t;&t;(HwDeviceExtension-&gt;jChipType == SIS_740)
DECL|macro|IS_SIS330
mdefine_line|#define IS_SIS330&t;&t;(HwDeviceExtension-&gt;jChipType == SIS_330)
DECL|macro|IS_SIS550
mdefine_line|#define IS_SIS550&t;&t;(HwDeviceExtension-&gt;jChipType == SIS_550)
DECL|macro|CRT1Len
mdefine_line|#define CRT1Len                 17
DECL|macro|LVDSCRT1Len
mdefine_line|#define LVDSCRT1Len             15
DECL|macro|CHTVRegDataLen
mdefine_line|#define CHTVRegDataLen          5
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
DECL|macro|ModeInfoFlag
mdefine_line|#define ModeInfoFlag            0x07
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
DECL|macro|DoubleScanMode
mdefine_line|#define DoubleScanMode          0x8000
multiline_comment|/* Infoflag */
DECL|macro|SupportAllCRT2
mdefine_line|#define SupportAllCRT2          0x0078
DECL|macro|SupportTV
mdefine_line|#define SupportTV               0x0008
DECL|macro|SupportHiVisionTV
mdefine_line|#define SupportHiVisionTV       0x0010
DECL|macro|SupportLCD
mdefine_line|#define SupportLCD              0x0020
DECL|macro|SupportRAMDAC2
mdefine_line|#define SupportRAMDAC2          0x0040  
DECL|macro|NoSupportTV
mdefine_line|#define NoSupportTV             0x0070
DECL|macro|NoSupportHiVisionTV
mdefine_line|#define NoSupportHiVisionTV     0x0060
DECL|macro|NoSupportLCD
mdefine_line|#define NoSupportLCD            0x0058
DECL|macro|SupportCHTV
mdefine_line|#define SupportCHTV &t;&t;0x0800
DECL|macro|SupportTV1024
mdefine_line|#define SupportTV1024           0x0800            
DECL|macro|InterlaceMode
mdefine_line|#define InterlaceMode           0x0080
DECL|macro|SupportHiVisionTV2
mdefine_line|#define SupportHiVisionTV2      0x1000
DECL|macro|SyncPP
mdefine_line|#define SyncPP                  0x0000
DECL|macro|SyncPN
mdefine_line|#define SyncPN                  0x4000
DECL|macro|SyncNP
mdefine_line|#define SyncNP                  0x8000
DECL|macro|SyncNN
mdefine_line|#define SyncNN                  0xc000
DECL|macro|ECLKindex0
mdefine_line|#define ECLKindex0              0x0000
DECL|macro|ECLKindex1
mdefine_line|#define ECLKindex1              0x0100
DECL|macro|ECLKindex2
mdefine_line|#define ECLKindex2              0x0200
DECL|macro|ECLKindex3
mdefine_line|#define ECLKindex3              0x0300
DECL|macro|ECLKindex4
mdefine_line|#define ECLKindex4              0x0400
multiline_comment|/* VBInfo */
DECL|macro|SetSimuScanMode
mdefine_line|#define SetSimuScanMode         0x0001   /* CR 30 */
DECL|macro|SwitchToCRT2
mdefine_line|#define SwitchToCRT2            0x0002
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
DECL|macro|SetCRT2ToHiVisionTV
mdefine_line|#define SetCRT2ToHiVisionTV     0x0080
DECL|macro|SetCRT2ToTV
mdefine_line|#define SetCRT2ToTV             0x009C   /* alias */
DECL|macro|SetNTSCTV
mdefine_line|#define SetNTSCTV               0x0000   /* CR 31 */
DECL|macro|SetPALTV
mdefine_line|#define SetPALTV                0x0100
DECL|macro|SetInSlaveMode
mdefine_line|#define SetInSlaveMode          0x0200
DECL|macro|SetNotSimuMode
mdefine_line|#define SetNotSimuMode          0x0400
DECL|macro|SetNotSimuTVMode
mdefine_line|#define SetNotSimuTVMode        0x0400
DECL|macro|SetDispDevSwitch
mdefine_line|#define SetDispDevSwitch        0x0800
DECL|macro|LoadDACFlag
mdefine_line|#define LoadDACFlag             0x1000
DECL|macro|SetCHTVOverScan
mdefine_line|#define SetCHTVOverScan  &t;0x1000  /* TW: Re-defined (from 0x8000) */
DECL|macro|DisableCRT2Display
mdefine_line|#define DisableCRT2Display      0x2000
DECL|macro|CRT2DisplayFlag
mdefine_line|#define CRT2DisplayFlag         0x2000
DECL|macro|DriverMode
mdefine_line|#define DriverMode              0x4000
DECL|macro|HotKeySwitch
mdefine_line|#define HotKeySwitch            0x8000  /* TW: ? */
DECL|macro|SetCRT2ToLCDA
mdefine_line|#define SetCRT2ToLCDA           0x8000
DECL|macro|PanelRGB18Bit
mdefine_line|#define PanelRGB18Bit           0x0100
DECL|macro|PanelRGB24Bit
mdefine_line|#define PanelRGB24Bit           0x0000
DECL|macro|TVOverScan
mdefine_line|#define TVOverScan              0x10    /* Bit in CR35 (300 series only) */
DECL|macro|TVOverScanShift
mdefine_line|#define TVOverScanShift         4
DECL|macro|ClearBufferFlag
mdefine_line|#define ClearBufferFlag         0x20
multiline_comment|/* CR32 (Newer 630, and 310/325 series)&n;&n;   [0]   VB connected with CVBS&n;   [1]   VB connected with SVHS&n;   [2]   VB connected with SCART&n;   [3]   VB connected with LCD&n;   [4]   VB connected with CRT2 (secondary VGA)&n;   [5]   CRT1 monitor is connected&n;   [6]   VB connected with Hi-Vision TV&n;   [7]   VB connected with DVI combo connector&n;&n;&n;   CR37&n;&n;   [0]   Set 24/18 bit (0/1) RGB to LVDS/TMDS transmitter (set by BIOS)&n;   [3:1] External chip&n;         300 series:&n;&t;    001   SiS301 (never seen)&n;&t;    010   LVDS&n;&t;    011   LVDS + Tumpion Zurac&n;&t;    100   LVDS + Chrontel 7005&n;&t;    110   Chrontel 7005&n;&t;  310/325 series&n;&t;    001   SiS30x (never seen)&n;&t;    010   LVDS&n;&t;    011   LVDS + Chrontel 7019&n;&t;  All other combinations reserved&n;   [4]    LVDS: 0: Panel Link expands / 1: Panel Link does not expand&n;          30x:  0: Bridge scales      / 1: Bridge does not scale = Panel scales (if possible)&n;   [5]    LCD polarity select&n;          0: VESA DMT Standard&n;&t;  1: EDID 2.x defined&n;   [6]    LCD horizontal polarity select&n;          0: High active&n;&t;  1: Low active&n;   [7]    LCD vertical polarity select&n;          0: High active&n;&t;  1: Low active&n;*/
multiline_comment|/* CR37: LCDInfo */
DECL|macro|LCDRGB18Bit
mdefine_line|#define LCDRGB18Bit           0x0001
DECL|macro|LCDNonExpanding
mdefine_line|#define LCDNonExpanding       0x0010
DECL|macro|DontExpandLCD
mdefine_line|#define DontExpandLCD&t;      LCDNonExpanding
DECL|macro|LCDNonExpandingShift
mdefine_line|#define LCDNonExpandingShift       4
DECL|macro|DontExpandLCDShift
mdefine_line|#define DontExpandLCDShift    LCDNonExpandingShift
DECL|macro|LCDSync
mdefine_line|#define LCDSync               0x0020
DECL|macro|LCDPass11
mdefine_line|#define LCDPass11             0x0100 
DECL|macro|LCDSyncBit
mdefine_line|#define LCDSyncBit            0x00e0
DECL|macro|LCDSyncShift
mdefine_line|#define LCDSyncShift               6
multiline_comment|/* CR38 (310/325 series) */
DECL|macro|EnableDualEdge
mdefine_line|#define EnableDualEdge &t;&t;0x01   
DECL|macro|SetToLCDA
mdefine_line|#define SetToLCDA&t;&t;0x02   /* LCD channel A (302B/LV and 650+LVDS only) */
DECL|macro|EnableSiSHiVision
mdefine_line|#define EnableSiSHiVision       0x04   /* HiVision (HDTV) on SiS bridge */
DECL|macro|EnableLVDSScart
mdefine_line|#define EnableLVDSScart         0x04   /* Scart on Ch7019 (unofficial definition - TW) */
DECL|macro|EnableLVDSHiVision
mdefine_line|#define EnableLVDSHiVision      0x08   /* YPbPr color format (480i HDTV); only on 650/Ch7019 systems */
DECL|macro|SiSHiVision1
mdefine_line|#define SiSHiVision1            0x10   /* See SetHiVision() */
DECL|macro|SiSHiVision2
mdefine_line|#define SiSHiVision2            0x20
DECL|macro|EnablePALM
mdefine_line|#define EnablePALM              0x40   /* 1 = Set PALM */
DECL|macro|EnablePALN
mdefine_line|#define EnablePALN              0x80   /* 1 = Set PALN */
DECL|macro|SetSCARTOutput
mdefine_line|#define SetSCARTOutput          0x01
DECL|macro|BoardTVType
mdefine_line|#define BoardTVType             0x02
DECL|macro|EnablePALMN
mdefine_line|#define EnablePALMN             0x40   /* Romflag: 1 = Allow PALM/PALN */
multiline_comment|/* CR39 (650) */
DECL|macro|LCDPass1_1
mdefine_line|#define LCDPass1_1&t;&t;0x01   /* LVDS only; set by driver to pass 1:1 data to LVDS output  */
DECL|macro|Enable302LV_DualLink
mdefine_line|#define Enable302LV_DualLink    0x04   /* 30xNEW (302LV) only; set by mode switching function */
multiline_comment|/* CR79 (310/325 series only)&n;   [3-0] Notify driver&n;         0001 Mode Switch event (set by BIOS)&n;&t; 0010 Epansion On/Off event&n;&t; 0011 TV UnderScan/OverScan event&n;&t; 0100 Set Brightness event&n;&t; 0101 Set Contrast event&n;&t; 0110 Set Mute event&n;&t; 0111 Set Volume Up/Down event&n;   [4]   Enable Backlight Control by BIOS/driver &n;         (set by driver; set means that the BIOS should&n;&t; not touch the backlight registers because eg.&n;&t; the driver already switched off the backlight)&n;   [5]   PAL/NTSC (set by BIOS)&n;   [6]   Expansion On/Off (set by BIOS; copied to CR32[4])&n;   [7]   TV UnderScan/OverScan (set by BIOS)&n;*/
multiline_comment|/* SetFlag */
DECL|macro|ProgrammingCRT2
mdefine_line|#define ProgrammingCRT2         0x01
DECL|macro|TVSimuMode
mdefine_line|#define TVSimuMode              0x02
DECL|macro|RPLLDIV2XO
mdefine_line|#define RPLLDIV2XO              0x04
DECL|macro|LCDVESATiming
mdefine_line|#define LCDVESATiming           0x08
DECL|macro|EnableLVDSDDA
mdefine_line|#define EnableLVDSDDA           0x10
DECL|macro|SetDispDevSwitchFlag
mdefine_line|#define SetDispDevSwitchFlag    0x20
DECL|macro|CheckWinDos
mdefine_line|#define CheckWinDos             0x40
DECL|macro|SetDOSMode
mdefine_line|#define SetDOSMode              0x80
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
DECL|macro|Panel300_320x480
mdefine_line|#define Panel300_320x480        0x08 &t;/* fstn - TW: This is fake, can be any */
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
mdefine_line|#define Panel310_1280x768       0x0a    /* LVDS only */
DECL|macro|Panel310_1600x1200
mdefine_line|#define Panel310_1600x1200      0x0b
DECL|macro|Panel310_320x480
mdefine_line|#define Panel310_320x480        0x0c    /* fstn - TW: This is fake, can be any */
DECL|macro|Panel_800x600
mdefine_line|#define Panel_800x600           0x01&t;/* Unified values */
DECL|macro|Panel_1024x768
mdefine_line|#define Panel_1024x768          0x02
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
mdefine_line|#define Panel_1280x768          0x0a    /* LVDS only */
DECL|macro|Panel_1600x1200
mdefine_line|#define Panel_1600x1200         0x0b
DECL|macro|Panel_320x480
mdefine_line|#define Panel_320x480           0x0c    /* fstn - TW: This is fake, can be any */
DECL|macro|ExtChipType
mdefine_line|#define ExtChipType             0x0e
DECL|macro|ExtChip301
mdefine_line|#define ExtChip301              0x02
DECL|macro|ExtChipLVDS
mdefine_line|#define ExtChipLVDS             0x04
DECL|macro|ExtChipTrumpion
mdefine_line|#define ExtChipTrumpion         0x06
DECL|macro|ExtChipCH7005
mdefine_line|#define ExtChipCH7005           0x08
DECL|macro|ExtChipMitacTV
mdefine_line|#define ExtChipMitacTV          0x0a    /* TW: Incorrect, 0x0a = Chrontel 7005 only */
DECL|macro|IsM650
mdefine_line|#define IsM650                  0x80   &t;/* TW: CR5F */
DECL|macro|LCDDataLen
mdefine_line|#define LCDDataLen              8
DECL|macro|HiTVDataLen
mdefine_line|#define HiTVDataLen             12
DECL|macro|TVDataLen
mdefine_line|#define TVDataLen               16
DECL|macro|SetPALTV
mdefine_line|#define SetPALTV                0x0100
DECL|macro|HalfDCLK
mdefine_line|#define HalfDCLK                0x1000  /* modeflag */
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
DECL|macro|VCLKStartFreq
mdefine_line|#define VCLKStartFreq           25
DECL|macro|SoftDramType
mdefine_line|#define SoftDramType            0x80
DECL|macro|VCLK40
mdefine_line|#define VCLK40                  0x04   /* Index in VCLKData array */
DECL|macro|VCLK65
mdefine_line|#define VCLK65                  0x09   /* Index in VCLKData array */
DECL|macro|VCLK108_2
mdefine_line|#define VCLK108_2               0x14   /* Index in VCLKData array */
DECL|macro|TVVCLKDIV2
mdefine_line|#define TVVCLKDIV2              0x21   /* Indices in (VB)VCLKData arrays */
DECL|macro|TVVCLK
mdefine_line|#define TVVCLK                  0x22
DECL|macro|HiTVVCLKDIV2
mdefine_line|#define HiTVVCLKDIV2            0x23
DECL|macro|HiTVVCLK
mdefine_line|#define HiTVVCLK                0x24
DECL|macro|HiTVSimuVCLK
mdefine_line|#define HiTVSimuVCLK            0x25
DECL|macro|HiTVTextVCLK
mdefine_line|#define HiTVTextVCLK            0x26
DECL|macro|LoadDACFlag
mdefine_line|#define LoadDACFlag             0x1000
DECL|macro|AfterLockCRT2
mdefine_line|#define AfterLockCRT2           0x4000
DECL|macro|SetCRT2ToAVIDEO
mdefine_line|#define SetCRT2ToAVIDEO         0x0004
DECL|macro|SetCRT2ToSCART
mdefine_line|#define SetCRT2ToSCART          0x0010
DECL|macro|Ext2StructSize
mdefine_line|#define Ext2StructSize          5
DECL|macro|SetSCARTOutput
mdefine_line|#define SetSCARTOutput          0x01
DECL|macro|AVIDEOSense
mdefine_line|#define AVIDEOSense             0x01
DECL|macro|SVIDEOSense
mdefine_line|#define SVIDEOSense             0x02
DECL|macro|SCARTSense
mdefine_line|#define SCARTSense              0x04
DECL|macro|LCDSense
mdefine_line|#define LCDSense                0x08
DECL|macro|Monitor1Sense
mdefine_line|#define Monitor1Sense           0x20
DECL|macro|Monitor2Sense
mdefine_line|#define Monitor2Sense           0x10
DECL|macro|HiTVSense
mdefine_line|#define HiTVSense               0x40
DECL|macro|BoardTVType
mdefine_line|#define BoardTVType             0x02
DECL|macro|HotPlugFunction
mdefine_line|#define HotPlugFunction         0x08
DECL|macro|StStructSize
mdefine_line|#define StStructSize            0x06
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
DECL|macro|LVDSDataLen
mdefine_line|#define LVDSDataLen             6
DECL|macro|EnableLVDSDDA
mdefine_line|#define EnableLVDSDDA           0x10
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
DECL|macro|SelectCRT1Rate
mdefine_line|#define SelectCRT1Rate          0x4
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
mdefine_line|#define BIOSIDCodeAddr          0x235  /* TW: Offsets to ptrs in BIOS image */
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
multiline_comment|/*&n;  =============================================================&n;   &t;&t;&t;for 310/325 series&n;  =============================================================&n;*/
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
