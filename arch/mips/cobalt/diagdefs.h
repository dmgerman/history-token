multiline_comment|/*&n; * Filename: diagdefs.h&n; * &n; * Description: Some general definitions used by the diagnostics &n; * &n; * Author(s): Timothy Stonis&n; * &n; * Copyright 1997, Cobalt Microserver, Inc.&n; */
DECL|macro|KSEG0_Base
mdefine_line|#define KSEG0_Base&t;&t;0x80000000
DECL|macro|KSEG1_Base
mdefine_line|#define KSEG1_Base&t;&t;0xA0000000
singleline_comment|// Some useful Galileo registers/base addresses (boot time kseg1 mapping) 
DECL|macro|kGal_InternalBase
mdefine_line|#define kGal_InternalBase&t;( 0x14000000 | KSEG1_Base ) 
DECL|macro|kGal_DevBank0Base
mdefine_line|#define kGal_DevBank0Base&t;( 0x1C000000 | KSEG1_Base )
DECL|macro|kGal_DevBank1Base
mdefine_line|#define kGal_DevBank1Base &t;( 0x1C800000 | KSEG1_Base )
DECL|macro|kGal_RAS10Lo
mdefine_line|#define kGal_RAS10Lo&t;&t;0x008
DECL|macro|kGal_RAS10Hi
mdefine_line|#define kGal_RAS10Hi&t;&t;0x010
DECL|macro|kGal_RAS32Lo
mdefine_line|#define kGal_RAS32Lo&t;&t;0x018
DECL|macro|kGal_RAS32Hi
mdefine_line|#define kGal_RAS32Hi&t;&t;0x020
DECL|macro|kGal_PCIIOLo
mdefine_line|#define kGal_PCIIOLo&t;&t;0x048
DECL|macro|kGal_PCIIOHi
mdefine_line|#define kGal_PCIIOHi&t;&t;0x050
DECL|macro|kGal_RAS10LoCfg
mdefine_line|#define kGal_RAS10LoCfg&t;&t;0x000
DECL|macro|kGal_RAS10HiCfg
mdefine_line|#define kGal_RAS10HiCfg&t;&t;0x03
DECL|macro|kGal_RAS32LoCfg
mdefine_line|#define kGal_RAS32LoCfg&t;&t;0x004
DECL|macro|kGal_RAS32HiCfg
mdefine_line|#define kGal_RAS32HiCfg&t;&t;0x07
DECL|macro|kGal_PCIIOLoCfg
mdefine_line|#define kGal_PCIIOLoCfg&t;&t;0x000
DECL|macro|kGal_PCIIOHiCfg
mdefine_line|#define kGal_PCIIOHiCfg&t;&t;0x0F
DECL|macro|kGal_DevBank0PReg
mdefine_line|#define kGal_DevBank0PReg&t;0x45C
DECL|macro|kGal_DevBank1PReg
mdefine_line|#define kGal_DevBank1PReg&t;0x460
DECL|macro|kGal_DevBank2PReg
mdefine_line|#define kGal_DevBank2PReg&t;0x464
DECL|macro|kGal_DevBank3PReg
mdefine_line|#define kGal_DevBank3PReg&t;0x468
DECL|macro|kGal_DevBankBPReg
mdefine_line|#define kGal_DevBankBPReg&t;0x46C
DECL|macro|kGal_DRAMCReg
mdefine_line|#define kGal_DRAMCReg&t;&t;0x448
DECL|macro|kGal_DRAM0PReg
mdefine_line|#define kGal_DRAM0PReg&t;&t;0x44C
DECL|macro|kGal_DRAM1PReg
mdefine_line|#define kGal_DRAM1PReg&t;&t;0x450
DECL|macro|kGal_DRAM2PReg
mdefine_line|#define kGal_DRAM2PReg&t;&t;0x454
DECL|macro|kGal_DRAM3PReg
mdefine_line|#define kGal_DRAM3PReg&t;&t;0x458
DECL|macro|kGal_ConfigAddr
mdefine_line|#define kGal_ConfigAddr&t;&t;0xCF8
DECL|macro|kGal_ConfigData
mdefine_line|#define kGal_ConfigData&t;&t;0xCFC
DECL|macro|kGal_PCICfgEn
mdefine_line|#define kGal_PCICfgEn&t;&t;0x1F 
singleline_comment|// Generate config cycle 
DECL|macro|kGal_DevNum
mdefine_line|#define kGal_DevNum&t;&t;0x00 
singleline_comment|// Technically 0x06, but 0 works too
DECL|macro|kGal_MasMemEn
mdefine_line|#define kGal_MasMemEn&t;&t;0x06
DECL|macro|kGal_Latency
mdefine_line|#define kGal_Latency&t;&t;0x700
DECL|macro|kGal_RAS01StartReg
mdefine_line|#define kGal_RAS01StartReg&t;0x10
DECL|macro|kGal_RAS23StartReg
mdefine_line|#define kGal_RAS23StartReg&t;0x14
DECL|macro|kGal_RAS01SizeReg
mdefine_line|#define kGal_RAS01SizeReg&t;0x0C08
DECL|macro|kGal_RAS23SizeReg
mdefine_line|#define kGal_RAS23SizeReg&t;0x0C0C
DECL|macro|kGal_RAS01Start
mdefine_line|#define kGal_RAS01Start&t;&t;0x000
DECL|macro|kGal_RAS23Start
mdefine_line|#define kGal_RAS23Start&t;&t;0x00800000
DECL|macro|kGal_RAS01Size
mdefine_line|#define kGal_RAS01Size&t;&t;0x007FFFFF
DECL|macro|kGal_RAS23Size
mdefine_line|#define kGal_RAS23Size&t;&t;0x007FFFFF
singleline_comment|// Paramter information for devices, DRAM, etc
DECL|macro|kGal_DevBank0Cfg
mdefine_line|#define&t;kGal_DevBank0Cfg&t;0x1446DB33
DECL|macro|kGal_DevBank1Cfg
mdefine_line|#define&t;kGal_DevBank1Cfg&t;0x144FE667
DECL|macro|kGal_DevBankBCfg
mdefine_line|#define&t;kGal_DevBankBCfg&t;0x1446DC43
DECL|macro|kGal_DRAMConfig
mdefine_line|#define&t;kGal_DRAMConfig&t;&t;0x00000300
DECL|macro|kGal_DRAM0Config
mdefine_line|#define&t;kGal_DRAM0Config&t;0x00000010
DECL|macro|kGal_DRAM1Config
mdefine_line|#define&t;kGal_DRAM1Config&t;0x00000010
DECL|macro|kGal_DRAM2Config
mdefine_line|#define&t;kGal_DRAM2Config&t;0x00000010
DECL|macro|kGal_DRAM3Config
mdefine_line|#define&t;kGal_DRAM3Config&t;0x00000010
DECL|macro|kGal_DRAM0Hi
mdefine_line|#define&t;kGal_DRAM0Hi&t;&t;0x00000003
DECL|macro|kGal_DRAM0Lo
mdefine_line|#define&t;kGal_DRAM0Lo&t;&t;0x00000000
DECL|macro|kGal_DRAM1Hi
mdefine_line|#define&t;kGal_DRAM1Hi&t;&t;0x00000007
DECL|macro|kGal_DRAM1Lo
mdefine_line|#define&t;kGal_DRAM1Lo&t;&t;0x00000004
DECL|macro|kGal_DRAM2Hi
mdefine_line|#define&t;kGal_DRAM2Hi&t;&t;0x0000000B
DECL|macro|kGal_DRAM2Lo
mdefine_line|#define&t;kGal_DRAM2Lo&t;&t;0x00000008
DECL|macro|kGal_DRAM3Hi
mdefine_line|#define&t;kGal_DRAM3Hi&t;&t;0x0000000F
DECL|macro|kGal_DRAM3Lo
mdefine_line|#define&t;kGal_DRAM3Lo&t;&t;0x0000000C
DECL|macro|kGal_RAS0Lo
mdefine_line|#define kGal_RAS0Lo&t;&t;0x400
DECL|macro|kGal_RAS0Hi
mdefine_line|#define kGal_RAS0Hi&t;&t;0x404
DECL|macro|kGal_RAS1Lo
mdefine_line|#define kGal_RAS1Lo&t;&t;0x408
DECL|macro|kGal_RAS1Hi
mdefine_line|#define kGal_RAS1Hi&t;&t;0x40C
DECL|macro|kGal_RAS2Lo
mdefine_line|#define kGal_RAS2Lo&t;&t;0x410
DECL|macro|kGal_RAS2Hi
mdefine_line|#define kGal_RAS2Hi&t;&t;0x414
DECL|macro|kGal_RAS3Lo
mdefine_line|#define kGal_RAS3Lo&t;&t;0x418
DECL|macro|kGal_RAS3Hi
mdefine_line|#define kGal_RAS3Hi&t;&t;0x41C
singleline_comment|// Feedback LED indicators during setup code (reset.S, main.c) 
DECL|macro|kLED_AllOn
mdefine_line|#define kLED_AllOn&t;0x0F
DECL|macro|kLED_FlashTest
mdefine_line|#define kLED_FlashTest&t;0x01
DECL|macro|kLED_MemTest
mdefine_line|#define kLED_MemTest&t;0x02
DECL|macro|kLED_SCCTest
mdefine_line|#define kLED_SCCTest&t;0x03
DECL|macro|kLED_GalPCI
mdefine_line|#define kLED_GalPCI&t;0x04
DECL|macro|kLED_EnetTest
mdefine_line|#define kLED_EnetTest&t;0x05
DECL|macro|kLED_SCSITest
mdefine_line|#define kLED_SCSITest&t;0x06
DECL|macro|kLED_IOCTest
mdefine_line|#define kLED_IOCTest&t;0x07
DECL|macro|kLED_Quickdone
mdefine_line|#define kLED_Quickdone&t;0x0A
DECL|macro|kLED_Exception
mdefine_line|#define kLED_Exception&t;0x0B
DECL|macro|kLED_ProcInit
mdefine_line|#define kLED_ProcInit&t;0x0E
DECL|macro|kLED_AllOff
mdefine_line|#define kLED_AllOff&t;0x00
DECL|macro|kLEDBase
mdefine_line|#define kLEDBase&t;kGal_DevBank0Base
singleline_comment|// Some memory related constants 
DECL|macro|kRAM_Start
mdefine_line|#define kRAM_Start&t;(0x00000000 | KSEG0_Base)
DECL|macro|kTestPat1
mdefine_line|#define&t;kTestPat1&t;0xA5A5A5A5
DECL|macro|kTestPat2
mdefine_line|#define kTestPat2&t;0x5A5A5A5A
DECL|macro|k1Meg_kseg1
mdefine_line|#define k1Meg_kseg1 &t;(0x00100000 | KSEG0_Base)
DECL|macro|k2Meg_kseg1
mdefine_line|#define k2Meg_kseg1  &t;(0x00200000 | KSEG0_Base)
DECL|macro|k4Meg_kseg1
mdefine_line|#define k4Meg_kseg1  &t;(0x00400000 | KSEG0_Base)
DECL|macro|k8Meg_kseg1
mdefine_line|#define k8Meg_kseg1  &t;(0x00800000 | KSEG0_Base)
DECL|macro|k16Meg_kseg1
mdefine_line|#define k16Meg_kseg1  &t;(0x01000000 | KSEG0_Base)
DECL|macro|kInit_SP
mdefine_line|#define kInit_SP&t;k4Meg_kseg1 - 0x100
DECL|macro|kVectorBase
mdefine_line|#define kVectorBase&t;0x200&t;
DECL|macro|kDebugVectors
mdefine_line|#define kDebugVectors&t;0x400
DECL|macro|kMallocCheese
mdefine_line|#define kMallocCheese&t;0x80E00000
DECL|macro|kDecompAddr
mdefine_line|#define kDecompAddr&t;0x80700000
DECL|macro|kCompAddr
mdefine_line|#define kCompAddr&t;0x80500000
singleline_comment|// Ethernet definitions
DECL|macro|kEnet_VIOBase
mdefine_line|#define&t;kEnet_VIOBase&t;( 0x12100000 | KSEG1_Base )
DECL|macro|kEnet_PIOBase
mdefine_line|#define&t;kEnet_PIOBase&t;0x12100000
DECL|macro|kEnet_CSCfg
mdefine_line|#define&t;kEnet_CSCfg&t;0x46
DECL|macro|kEnet_DevNum
mdefine_line|#define kEnet_DevNum&t;0x07
DECL|macro|kEnet_CSR3
mdefine_line|#define kEnet_CSR3&t;0x18
DECL|macro|kEnet_CSR15
mdefine_line|#define kEnet_CSR15&t;0x78
DECL|macro|kEnet_GEPOut
mdefine_line|#define kEnet_GEPOut&t;0x080f0000
DECL|macro|kEnet_GEPOn
mdefine_line|#define kEnet_GEPOn&t;0x000f0000
singleline_comment|// SCSI definitions
DECL|macro|kSCSI_VIOBase
mdefine_line|#define&t;kSCSI_VIOBase&t;( 0x12200000 | KSEG1_Base )
DECL|macro|kSCSI_PIOBase
mdefine_line|#define&t;kSCSI_PIOBase&t;0x12200000 
DECL|macro|kSCSI_CSCfg
mdefine_line|#define&t;kSCSI_CSCfg&t;0x46 
DECL|macro|kSCSI_DevNum
mdefine_line|#define kSCSI_DevNum&t;0x08
DECL|macro|kSCSI_GPCNTL
mdefine_line|#define kSCSI_GPCNTL&t;0x47
DECL|macro|kSCSI_GPREG
mdefine_line|#define kSCSI_GPREG&t;0x07
DECL|macro|kSCSI_SCRTCHA
mdefine_line|#define kSCSI_SCRTCHA&t;0x34
DECL|macro|kSCSI_GPIOOut
mdefine_line|#define kSCSI_GPIOOut&t;0x0C
DECL|macro|kSCSI_LEDsOn
mdefine_line|#define kSCSI_LEDsOn&t;0x00
singleline_comment|// I/O Controller definitions
DECL|macro|kIOC_VIOBase
mdefine_line|#define kIOC_VIOBase&t;( 0x10000000 | KSEG1_Base )
DECL|macro|kIOC_RIOBase
mdefine_line|#define kIOC_RIOBase&t;0x10000000 
DECL|macro|kIOC_DevNum
mdefine_line|#define kIOC_DevNum&t;0x09
DECL|macro|kIOC_ISAFunc
mdefine_line|#define kIOC_ISAFunc&t;0x00
DECL|macro|kIOC_IDEFunc
mdefine_line|#define kIOC_IDEFunc&t;0x01
DECL|macro|kIOC_USBFunc
mdefine_line|#define kIOC_USBFunc&t;0x02
DECL|macro|kIOC_MiscC0
mdefine_line|#define kIOC_MiscC0&t;0x44
DECL|macro|kIOC_IDEEnable
mdefine_line|#define kIOC_IDEEnable&t;0x40
DECL|macro|kIOC_PCIIDEOn
mdefine_line|#define kIOC_PCIIDEOn &t;0x02800085
DECL|macro|kIOC_PriIDEOn
mdefine_line|#define kIOC_PriIDEOn&t;0x0A
singleline_comment|// Some PCI Definitions
DECL|macro|kPCI_StatCmd
mdefine_line|#define&t;kPCI_StatCmd&t;0x04
DECL|macro|kPCI_LatCache
mdefine_line|#define&t;kPCI_LatCache&t;0x0C
DECL|macro|kPCI_CBIO
mdefine_line|#define&t;kPCI_CBIO&t;0x10
DECL|macro|kPCI_CBMEM
mdefine_line|#define&t;kPCI_CBMEM&t;0x14
singleline_comment|// Random constants
DECL|macro|kBogoSec
mdefine_line|#define kBogoSec&t;0x0003F940
DECL|macro|kSCCDelay
mdefine_line|#define kSCCDelay&t;0x00000001
eof
