macro_line|#include &quot;sis.h&quot;
DECL|macro|PRIMARY_VGA
mdefine_line|#define PRIMARY_VGA&t;  1&t;
singleline_comment|//1: SiS is primary vga 0:SiS is secondary vga 
DECL|macro|ModeInfoFlag
mdefine_line|#define ModeInfoFlag      0x07
DECL|macro|MemoryInfoFlag
mdefine_line|#define MemoryInfoFlag    0x1E0
DECL|macro|MemorySizeShift
mdefine_line|#define MemorySizeShift   0x05
DECL|macro|ModeText
mdefine_line|#define ModeText          0x00
DECL|macro|ModeCGA
mdefine_line|#define ModeCGA           0x01
DECL|macro|ModeEGA
mdefine_line|#define ModeEGA           0x02
DECL|macro|ModeVGA
mdefine_line|#define ModeVGA           0x03
DECL|macro|Mode15Bpp
mdefine_line|#define Mode15Bpp         0x04
DECL|macro|Mode16Bpp
mdefine_line|#define Mode16Bpp         0x05
DECL|macro|Mode24Bpp
mdefine_line|#define Mode24Bpp         0x06
DECL|macro|Mode32Bpp
mdefine_line|#define Mode32Bpp         0x07
DECL|macro|CRT1Len
mdefine_line|#define CRT1Len           17
DECL|macro|DoubleScanMode
mdefine_line|#define DoubleScanMode    0x8000
DECL|macro|ADR_CRT2PtrData
mdefine_line|#define ADR_CRT2PtrData   0x20E 
singleline_comment|//address of CRT2PtrData in ROM image 
DECL|macro|offset_Zurac
mdefine_line|#define offset_Zurac      0x210
DECL|macro|ADR_LVDSDesPtrData
mdefine_line|#define ADR_LVDSDesPtrData      0x212
DECL|macro|ADR_LVDSCRT1DataPtr
mdefine_line|#define ADR_LVDSCRT1DataPtr     0x214
DECL|macro|SoftDRAMType
mdefine_line|#define SoftDRAMType      0x80  
singleline_comment|//5/19/2000,Mars,for soft setting dram type
DECL|macro|SoftSettingAddr
mdefine_line|#define SoftSettingAddr   0x52 
DECL|macro|ModeSettingAddr
mdefine_line|#define ModeSettingAddr   0x53
DECL|macro|InterlaceMode
mdefine_line|#define InterlaceMode     0x80
DECL|macro|HalfDCLK
mdefine_line|#define HalfDCLK          0x1000
DECL|macro|DACInfoFlag
mdefine_line|#define DACInfoFlag       0x18
DECL|macro|LineCompareOff
mdefine_line|#define LineCompareOff    0x400
DECL|macro|ActivePAL
mdefine_line|#define ActivePAL&t;  0x20
DECL|macro|ActivePALShift
mdefine_line|#define ActivePALShift&t;  5
DECL|macro|SelectCRT2Rate
mdefine_line|#define SelectCRT2Rate          0x4
DECL|macro|ProgrammingCRT2
mdefine_line|#define ProgrammingCRT2         0x1
DECL|macro|CRT2DisplayFlag
mdefine_line|#define CRT2DisplayFlag         0x2000
DECL|macro|SetCRT2ToRAMDAC
mdefine_line|#define SetCRT2ToRAMDAC         0x0040
DECL|macro|Charx8Dot
mdefine_line|#define Charx8Dot               0x0200
DECL|macro|LCDDataLen
mdefine_line|#define LCDDataLen              8
DECL|macro|SetCRT2ToLCD
mdefine_line|#define SetCRT2ToLCD            0x0020
DECL|macro|SetCRT2ToHiVisionTV
mdefine_line|#define SetCRT2ToHiVisionTV     0x0080
DECL|macro|HiTVDataLen
mdefine_line|#define HiTVDataLen             12
DECL|macro|TVDataLen
mdefine_line|#define TVDataLen               16
DECL|macro|SetPALTV
mdefine_line|#define SetPALTV                0x0100
DECL|macro|SetInSlaveMode
mdefine_line|#define SetInSlaveMode          0x0200
DECL|macro|SetCRT2ToTV
mdefine_line|#define SetCRT2ToTV             0x009C
DECL|macro|SetNotSimuTVMode
mdefine_line|#define SetNotSimuTVMode        0x0400
DECL|macro|SetSimuScanMode
mdefine_line|#define SetSimuScanMode         0x0001
DECL|macro|DriverMode
mdefine_line|#define DriverMode              0x4000
DECL|macro|CRT2Mode
mdefine_line|#define CRT2Mode                0x0800
singleline_comment|//#define ReIndexEnhLCD           4
DECL|macro|HalfDCLK
mdefine_line|#define HalfDCLK                0x1000
singleline_comment|//#define HiVisionTVHT            2100
singleline_comment|//#define HiVisionTVVT            2100
DECL|macro|NTSCHT
mdefine_line|#define NTSCHT                  1716
DECL|macro|NTSCVT
mdefine_line|#define NTSCVT                  525
DECL|macro|PALHT
mdefine_line|#define PALHT                   1728
DECL|macro|PALVT
mdefine_line|#define PALVT                   625
DECL|macro|VCLKStartFreq
mdefine_line|#define VCLKStartFreq           25      
singleline_comment|//Freq of first item in VCLKTable 
DECL|macro|SoftDramType
mdefine_line|#define SoftDramType            0x80
DECL|macro|VCLK65
mdefine_line|#define VCLK65                  0x09
DECL|macro|VCLK108_2
mdefine_line|#define VCLK108_2               0x14
singleline_comment|//#define LCDIs1280x1024Panel     0x04
singleline_comment|//#define HiVisionVCLK            0x22
DECL|macro|TVSimuMode
mdefine_line|#define TVSimuMode              0x02
DECL|macro|SetCRT2ToSVIDEO
mdefine_line|#define SetCRT2ToSVIDEO         0x08
singleline_comment|//#define LCDRGB18Bit             0x20
DECL|macro|LCDRGB18Bit
mdefine_line|#define LCDRGB18Bit             0x01
DECL|macro|Panel1280x1024
mdefine_line|#define Panel1280x1024          0x03
DECL|macro|Panel1024x768
mdefine_line|#define Panel1024x768           0x02
DECL|macro|Panel800x600
mdefine_line|#define Panel800x600            0x01
DECL|macro|RPLLDIV2XO
mdefine_line|#define RPLLDIV2XO              0x04 
DECL|macro|LoadDACFlag
mdefine_line|#define LoadDACFlag             0x1000
DECL|macro|AfterLockCRT2
mdefine_line|#define AfterLockCRT2           0x4000
DECL|macro|SupportRAMDAC2
mdefine_line|#define SupportRAMDAC2          0x0040
DECL|macro|SupportLCD
mdefine_line|#define SupportLCD              0x0020
singleline_comment|//#define Support1024x768LCD      0x0020
singleline_comment|//#define Support1280x1024LCD     0x0040
DECL|macro|SetCRT2ToAVIDEO
mdefine_line|#define SetCRT2ToAVIDEO         0x0004
DECL|macro|SetCRT2ToSCART
mdefine_line|#define SetCRT2ToSCART          0x0010
singleline_comment|//#define NoSupportSimuTV         0x0100
DECL|macro|NoSupportSimuTV
mdefine_line|#define NoSupportSimuTV         0x2000
DECL|macro|Ext2StructSize
mdefine_line|#define Ext2StructSize          5
DECL|macro|SupportTV
mdefine_line|#define SupportTV               0x0008
singleline_comment|//#define TVVCLKDIV2              0x020
singleline_comment|//#define TVVCLK                  0x021
DECL|macro|TVVCLKDIV2
mdefine_line|#define TVVCLKDIV2              0x021
DECL|macro|TVVCLK
mdefine_line|#define TVVCLK                  0x022
DECL|macro|SwitchToCRT2
mdefine_line|#define SwitchToCRT2            0x0002
DECL|macro|LCDVESATiming
mdefine_line|#define LCDVESATiming           0x08
DECL|macro|SetSCARTOutput
mdefine_line|#define SetSCARTOutput          0x01
DECL|macro|SCARTSense
mdefine_line|#define SCARTSense              0x04
DECL|macro|Monitor1Sense
mdefine_line|#define Monitor1Sense           0x20
DECL|macro|Monitor2Sense
mdefine_line|#define Monitor2Sense           0x10
DECL|macro|SVIDEOSense
mdefine_line|#define SVIDEOSense             0x02
DECL|macro|AVIDEOSense
mdefine_line|#define AVIDEOSense             0x01
DECL|macro|LCDSense
mdefine_line|#define LCDSense                0x08
DECL|macro|BoardTVType
mdefine_line|#define BoardTVType             0x02
DECL|macro|HotPlugFunction
mdefine_line|#define HotPlugFunction         0x08
DECL|macro|StStructSize
mdefine_line|#define StStructSize            0x06
DECL|macro|ExtChip301
mdefine_line|#define ExtChip301              0x02
DECL|macro|ExtChipLVDS
mdefine_line|#define ExtChipLVDS             0x04
DECL|macro|ExtChipTrumpion
mdefine_line|#define ExtChipTrumpion         0x06
DECL|macro|LCDNonExpanding
mdefine_line|#define LCDNonExpanding         0x10
DECL|macro|LCDNonExpandingShift
mdefine_line|#define LCDNonExpandingShift    4
DECL|macro|LVDSDataLen
mdefine_line|#define LVDSDataLen             6
DECL|macro|EnableLVDSDDA
mdefine_line|#define EnableLVDSDDA           0x10
DECL|macro|LCDSync
mdefine_line|#define LCDSync                 0x20
DECL|macro|SyncPP
mdefine_line|#define SyncPP                  0x0000
DECL|macro|LCDSyncBit
mdefine_line|#define LCDSyncBit              0xE0
DECL|macro|LVDSDesDataLen
mdefine_line|#define LVDSDesDataLen          3
DECL|macro|LVDSCRT1Len
mdefine_line|#define LVDSCRT1Len             15
DECL|macro|ActiveNonExpanding
mdefine_line|#define ActiveNonExpanding&t;0x40
DECL|macro|ActiveNonExpandingShift
mdefine_line|#define ActiveNonExpandingShift&t;6
DECL|macro|ModeSwitchStatus
mdefine_line|#define ModeSwitchStatus&t;0x0F
DECL|macro|SoftTVType
mdefine_line|#define SoftTVType&t;&t;0x40
DECL|macro|PanelType00
mdefine_line|#define PanelType00             0x00    
DECL|macro|PanelType01
mdefine_line|#define PanelType01             0x08
DECL|macro|PanelType02
mdefine_line|#define PanelType02             0x10
DECL|macro|PanelType03
mdefine_line|#define PanelType03             0x18
DECL|macro|PanelType04
mdefine_line|#define PanelType04             0x20
DECL|macro|PanelType05
mdefine_line|#define PanelType05             0x28
DECL|macro|PanelType06
mdefine_line|#define PanelType06             0x30
DECL|macro|PanelType07
mdefine_line|#define PanelType07             0x38
DECL|macro|PanelType08
mdefine_line|#define PanelType08             0x40
DECL|macro|PanelType09
mdefine_line|#define PanelType09             0x48
DECL|macro|PanelType0A
mdefine_line|#define PanelType0A             0x50
DECL|macro|PanelType0B
mdefine_line|#define PanelType0B             0x58
DECL|macro|PanelType0C
mdefine_line|#define PanelType0C             0x60
DECL|macro|PanelType0D
mdefine_line|#define PanelType0D             0x68
DECL|macro|PanelType0E
mdefine_line|#define PanelType0E             0x70
DECL|macro|PanelType0F
mdefine_line|#define PanelType0F             0x78
eof
