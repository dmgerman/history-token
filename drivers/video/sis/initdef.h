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
DECL|macro|VB_SIS301
mdefine_line|#define VB_SIS301&t;&t;0x0001&t;/*301b */
DECL|macro|VB_SIS301B
mdefine_line|#define VB_SIS301B&t;&t;0x0002
DECL|macro|VB_SIS302B
mdefine_line|#define VB_SIS302B&t;&t;0x0004
DECL|macro|VB_NoLCD
mdefine_line|#define  VB_NoLCD&t;&t;0x8000
multiline_comment|/*end 301b*/
DECL|macro|CRT1Len
mdefine_line|#define CRT1Len                 17
DECL|macro|LVDSCRT1Len
mdefine_line|#define LVDSCRT1Len             15
DECL|macro|CHTVRegDataLen
mdefine_line|#define CHTVRegDataLen          5
DECL|macro|ModeInfoFlag
mdefine_line|#define ModeInfoFlag            0x07
DECL|macro|IsTextMode
mdefine_line|#define IsTextMode              0x07
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
DECL|macro|DACInfoFlag
mdefine_line|#define DACInfoFlag             0x18
DECL|macro|MemoryInfoFlag
mdefine_line|#define MemoryInfoFlag          0x1E0
DECL|macro|MemorySizeShift
mdefine_line|#define MemorySizeShift         0x05
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
mdefine_line|#define SupportTV1024           0x0800&t;/*301b */
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
DECL|macro|SetSimuScanMode
mdefine_line|#define SetSimuScanMode         0x0001
DECL|macro|SwitchToCRT2
mdefine_line|#define SwitchToCRT2            0x0002
DECL|macro|SetCRT2ToTV
mdefine_line|#define SetCRT2ToTV             0x009C
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
DECL|macro|SetNTSCTV
mdefine_line|#define SetNTSCTV               0x0000
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
DECL|macro|DisableCRT2Display
mdefine_line|#define DisableCRT2Display      0x2000
DECL|macro|DriverMode
mdefine_line|#define DriverMode              0x4000
DECL|macro|HotKeySwitch
mdefine_line|#define HotKeySwitch            0x8000
DECL|macro|SetCHTVOverScan
mdefine_line|#define SetCHTVOverScan  &t;0x8000
DECL|macro|SetCRT2ToLCDA
mdefine_line|#define SetCRT2ToLCDA&t;&t;0x8000&t;/*301b */
DECL|macro|PanelRGB18Bit
mdefine_line|#define PanelRGB18Bit           0x0100
DECL|macro|PanelRGB24Bit
mdefine_line|#define PanelRGB24Bit           0x0000
DECL|macro|TVOverScan
mdefine_line|#define TVOverScan              0x10
DECL|macro|TVOverScanShift
mdefine_line|#define TVOverScanShift         4
DECL|macro|ClearBufferFlag
mdefine_line|#define ClearBufferFlag         0x20
DECL|macro|EnableDualEdge
mdefine_line|#define EnableDualEdge &t;&t;0x01&t;/*301b */
DECL|macro|SetToLCDA
mdefine_line|#define SetToLCDA&t;&t;0x02
DECL|macro|SetSCARTOutput
mdefine_line|#define SetSCARTOutput          0x01
DECL|macro|BoardTVType
mdefine_line|#define BoardTVType             0x02
DECL|macro|EnablePALMN
mdefine_line|#define  EnablePALMN&t;&t;0x40
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
DECL|macro|SetJDOSMode
mdefine_line|#define SetJDOSMode             0x80
DECL|macro|Panel800x600
mdefine_line|#define Panel800x600            0x01
DECL|macro|Panel1024x768
mdefine_line|#define Panel1024x768           0x02
DECL|macro|Panel1280x1024
mdefine_line|#define Panel1280x1024          0x03
DECL|macro|Panel1280x960
mdefine_line|#define Panel1280x960           0x04
DECL|macro|Panel640x480
mdefine_line|#define Panel640x480            0x05
DECL|macro|Panel1600x1200
mdefine_line|#define Panel1600x1200          0x06&t;/*301b */
DECL|macro|LCDRGB18Bit
mdefine_line|#define LCDRGB18Bit             0x01
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
mdefine_line|#define ExtChipMitacTV          0x0a
DECL|macro|LCDNonExpanding
mdefine_line|#define LCDNonExpanding         0x10
DECL|macro|LCDNonExpandingShift
mdefine_line|#define LCDNonExpandingShift    4
DECL|macro|LCDSync
mdefine_line|#define LCDSync                 0x20
DECL|macro|LCDSyncBit
mdefine_line|#define LCDSyncBit              0xe0
DECL|macro|LCDSyncShift
mdefine_line|#define LCDSyncShift            6
DECL|macro|DDC2DelayTime
mdefine_line|#define DDC2DelayTime           300
DECL|macro|CRT2DisplayFlag
mdefine_line|#define CRT2DisplayFlag         0x2000
DECL|macro|LCDDataLen
mdefine_line|#define LCDDataLen              8
DECL|macro|HiTVDataLen
mdefine_line|#define HiTVDataLen             12
DECL|macro|TVDataLen
mdefine_line|#define TVDataLen               16
DECL|macro|SetPALTV
mdefine_line|#define SetPALTV                0x0100
DECL|macro|HalfDCLK
mdefine_line|#define HalfDCLK                0x1000
DECL|macro|NTSCHT
mdefine_line|#define NTSCHT                  1716
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
mdefine_line|#define VCLK40                  0x04
DECL|macro|VCLK65
mdefine_line|#define VCLK65                  0x09
DECL|macro|VCLK108_2
mdefine_line|#define VCLK108_2               0x14
DECL|macro|LCDRGB18Bit
mdefine_line|#define LCDRGB18Bit             0x01
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
DECL|macro|TVVCLKDIV2
mdefine_line|#define TVVCLKDIV2              0x021
DECL|macro|TVVCLK
mdefine_line|#define TVVCLK                  0x022
DECL|macro|HiTVVCLKDIV2
mdefine_line|#define HiTVVCLKDIV2            0x023
DECL|macro|HiTVVCLK
mdefine_line|#define HiTVVCLK                0x024
DECL|macro|HiTVSimuVCLK
mdefine_line|#define HiTVSimuVCLK            0x025
DECL|macro|HiTVTextVCLK
mdefine_line|#define HiTVTextVCLK            0x026
DECL|macro|SwitchToCRT2
mdefine_line|#define SwitchToCRT2            0x0002
DECL|macro|LCDVESATiming
mdefine_line|#define LCDVESATiming           0x08
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
mdefine_line|#define SIS_CRT2_PORT_04        0x04 - 0x030
DECL|macro|SIS_CRT2_PORT_10
mdefine_line|#define SIS_CRT2_PORT_10        0x10 - 0x30
DECL|macro|SIS_CRT2_PORT_12
mdefine_line|#define SIS_CRT2_PORT_12        0x12 - 0x30
DECL|macro|SIS_CRT2_PORT_14
mdefine_line|#define SIS_CRT2_PORT_14        0x14 - 0x30
DECL|macro|LCDNonExpanding
mdefine_line|#define LCDNonExpanding         0x10
DECL|macro|ADR_CRT2PtrData
mdefine_line|#define ADR_CRT2PtrData         0x20E
DECL|macro|offset_Zurac
mdefine_line|#define offset_Zurac            0x210
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
mdefine_line|#define _PanelType00            0x00
DECL|macro|_PanelType01
mdefine_line|#define _PanelType01            0x08
DECL|macro|_PanelType02
mdefine_line|#define _PanelType02            0x10
DECL|macro|_PanelType03
mdefine_line|#define _PanelType03            0x18
DECL|macro|_PanelType04
mdefine_line|#define _PanelType04            0x20
DECL|macro|_PanelType05
mdefine_line|#define _PanelType05            0x28
DECL|macro|_PanelType06
mdefine_line|#define _PanelType06            0x30
DECL|macro|_PanelType07
mdefine_line|#define _PanelType07            0x38
DECL|macro|_PanelType08
mdefine_line|#define _PanelType08            0x40
DECL|macro|_PanelType09
mdefine_line|#define _PanelType09            0x48
DECL|macro|_PanelType0A
mdefine_line|#define _PanelType0A            0x50
DECL|macro|_PanelType0B
mdefine_line|#define _PanelType0B            0x58
DECL|macro|_PanelType0C
mdefine_line|#define _PanelType0C            0x60
DECL|macro|_PanelType0D
mdefine_line|#define _PanelType0D            0x68
DECL|macro|_PanelType0E
mdefine_line|#define _PanelType0E            0x70
DECL|macro|_PanelType0F
mdefine_line|#define _PanelType0F            0x78
DECL|macro|PRIMARY_VGA
mdefine_line|#define PRIMARY_VGA&t;&t;0&t;/* 1: SiS is primary vga 0:SiS is secondary vga */
DECL|macro|BIOSIDCodeAddr
mdefine_line|#define BIOSIDCodeAddr          0x235
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
multiline_comment|/* =============================================================&n;   for 310&n;============================================================== */
DECL|macro|SoftDRAMType
mdefine_line|#define SoftDRAMType      &t;0x80
DECL|macro|SoftSetting_OFFSET
mdefine_line|#define SoftSetting_OFFSET&t;0x52
DECL|macro|SR07_OFFSET
mdefine_line|#define SR07_OFFSET&t;&t;0x7C
DECL|macro|SR15_OFFSET
mdefine_line|#define SR15_OFFSET&t;&t;0x7D
DECL|macro|SR16_OFFSET
mdefine_line|#define SR16_OFFSET&t;&t;0x81
DECL|macro|SR17_OFFSET
mdefine_line|#define SR17_OFFSET&t;&t;0x85
DECL|macro|SR19_OFFSET
mdefine_line|#define SR19_OFFSET&t;&t;0x8D
DECL|macro|SR1F_OFFSET
mdefine_line|#define SR1F_OFFSET&t;&t;0x99
DECL|macro|SR21_OFFSET
mdefine_line|#define SR21_OFFSET&t;&t;0x9A
DECL|macro|SR22_OFFSET
mdefine_line|#define SR22_OFFSET&t;&t;0x9B
DECL|macro|SR23_OFFSET
mdefine_line|#define SR23_OFFSET&t;&t;0x9C
DECL|macro|SR24_OFFSET
mdefine_line|#define SR24_OFFSET&t;&t;0x9D
DECL|macro|SR25_OFFSET
mdefine_line|#define SR25_OFFSET&t;&t;0x9E
DECL|macro|SR31_OFFSET
mdefine_line|#define SR31_OFFSET&t;&t;0x9F
DECL|macro|SR32_OFFSET
mdefine_line|#define SR32_OFFSET&t;&t;0xA0
DECL|macro|SR33_OFFSET
mdefine_line|#define SR33_OFFSET&t;&t;0xA1
DECL|macro|CR40_OFFSET
mdefine_line|#define CR40_OFFSET&t;&t;0xA2
DECL|macro|SR25_1_OFFSET
mdefine_line|#define SR25_1_OFFSET&t;&t;0xF6
DECL|macro|CR49_OFFSET
mdefine_line|#define CR49_OFFSET&t;&t;0xF7
DECL|macro|VB310Data_1_2_Offset
mdefine_line|#define VB310Data_1_2_Offset&t;0xB6
DECL|macro|VB310Data_4_D_Offset
mdefine_line|#define VB310Data_4_D_Offset&t;0xB7
DECL|macro|VB310Data_4_E_Offset
mdefine_line|#define VB310Data_4_E_Offset&t;0xB8
DECL|macro|VB310Data_4_10_Offset
mdefine_line|#define VB310Data_4_10_Offset&t;0xBB
DECL|macro|RGBSenseDataOffset
mdefine_line|#define RGBSenseDataOffset&t;0xBD
DECL|macro|YCSenseDataOffset
mdefine_line|#define YCSenseDataOffset&t;0xBF
DECL|macro|VideoSenseDataOffset
mdefine_line|#define VideoSenseDataOffset&t;0xC1
DECL|macro|OutputSelectOffset
mdefine_line|#define OutputSelectOffset&t;0xF3
DECL|macro|ECLK_MCLK_DISTANCE
mdefine_line|#define ECLK_MCLK_DISTANCE&t;0x14
DECL|macro|VBIOSTablePointerStart
mdefine_line|#define VBIOSTablePointerStart&t;0x100
DECL|macro|StandTablePtrOffset
mdefine_line|#define StandTablePtrOffset&t;VBIOSTablePointerStart+0x02
DECL|macro|EModeIDTablePtrOffset
mdefine_line|#define EModeIDTablePtrOffset&t;VBIOSTablePointerStart+0x04
DECL|macro|CRT1TablePtrOffset
mdefine_line|#define CRT1TablePtrOffset&t;VBIOSTablePointerStart+0x06
DECL|macro|ScreenOffsetPtrOffset
mdefine_line|#define ScreenOffsetPtrOffset&t;VBIOSTablePointerStart+0x08
DECL|macro|VCLKDataPtrOffset
mdefine_line|#define VCLKDataPtrOffset&t;VBIOSTablePointerStart+0x0A
DECL|macro|MCLKDataPtrOffset
mdefine_line|#define MCLKDataPtrOffset&t;VBIOSTablePointerStart+0x0E
DECL|macro|CRT2PtrDataPtrOffset
mdefine_line|#define CRT2PtrDataPtrOffset&t;VBIOSTablePointerStart+0x10
DECL|macro|TVAntiFlickPtrOffset
mdefine_line|#define TVAntiFlickPtrOffset&t;VBIOSTablePointerStart+0x12
DECL|macro|TVDelayPtr1Offset
mdefine_line|#define TVDelayPtr1Offset&t;VBIOSTablePointerStart+0x14
DECL|macro|TVPhaseIncrPtr1Offset
mdefine_line|#define TVPhaseIncrPtr1Offset&t;VBIOSTablePointerStart+0x16
DECL|macro|TVYFilterPtr1Offset
mdefine_line|#define TVYFilterPtr1Offset&t;VBIOSTablePointerStart+0x18
DECL|macro|LCDDelayPtr1Offset
mdefine_line|#define LCDDelayPtr1Offset&t;VBIOSTablePointerStart+0x20
DECL|macro|TVEdgePtr1Offset
mdefine_line|#define TVEdgePtr1Offset&t;VBIOSTablePointerStart+0x24
DECL|macro|CRT2Delay1Offset
mdefine_line|#define CRT2Delay1Offset&t;VBIOSTablePointerStart+0x28
macro_line|#endif
eof
