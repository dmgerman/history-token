macro_line|#ifndef TRIDENTFB_DEBUG
DECL|macro|TRIDENTFB_DEBUG
mdefine_line|#define TRIDENTFB_DEBUG 0
macro_line|#endif
macro_line|#if TRIDENTFB_DEBUG
DECL|macro|debug
mdefine_line|#define debug(f,a...)&t;printk(&quot;%s:&quot; f,  __FUNCTION__ , ## a)
macro_line|#else
DECL|macro|debug
mdefine_line|#define debug(f,a...)
macro_line|#endif
DECL|macro|output
mdefine_line|#define output(f, a...) printk(&quot;tridentfb: &quot; f, ## a)
DECL|macro|Kb
mdefine_line|#define Kb&t;(1024)
DECL|macro|Mb
mdefine_line|#define Mb&t;(Kb*Kb)
multiline_comment|/* PCI IDS of supported cards temporarily here */
DECL|macro|CYBER9320
mdefine_line|#define CYBER9320&t;0x9320
DECL|macro|CYBER9388
mdefine_line|#define CYBER9388&t;0x9388
DECL|macro|CYBER9397
mdefine_line|#define CYBER9397&t;0x9397
DECL|macro|CYBER9397DVD
mdefine_line|#define CYBER9397DVD&t;0x939A
DECL|macro|CYBER9520
mdefine_line|#define CYBER9520&t;0x9520
DECL|macro|CYBER9525DVD
mdefine_line|#define CYBER9525DVD&t;0x9525
DECL|macro|IMAGE975
mdefine_line|#define IMAGE975&t;0x9750
DECL|macro|IMAGE985
mdefine_line|#define IMAGE985&t;0x9850
DECL|macro|BLADE3D
mdefine_line|#define BLADE3D&t;&t;0x9880
DECL|macro|CYBERBLADEE4
mdefine_line|#define CYBERBLADEE4&t;0x9540
DECL|macro|CYBERBLADEi7
mdefine_line|#define CYBERBLADEi7&t;0x8400
DECL|macro|CYBERBLADEi7D
mdefine_line|#define CYBERBLADEi7D&t;0x8420
DECL|macro|CYBERBLADEi1
mdefine_line|#define CYBERBLADEi1&t;0x8500
DECL|macro|CYBERBLADEi1D
mdefine_line|#define CYBERBLADEi1D&t;0x8520
DECL|macro|CYBERBLADEAi1
mdefine_line|#define CYBERBLADEAi1&t;0x8600
DECL|macro|CYBERBLADEAi1D
mdefine_line|#define CYBERBLADEAi1D&t;0x8620
DECL|macro|CYBERBLADEXPAi1
mdefine_line|#define CYBERBLADEXPAi1 0x8820
DECL|macro|CYBERBLADEXPm8
mdefine_line|#define CYBERBLADEXPm8  0x9910
DECL|macro|CYBERBLADEXPm16
mdefine_line|#define CYBERBLADEXPm16 0x9930
multiline_comment|/* acceleration families */
DECL|macro|IMAGE
mdefine_line|#define IMAGE&t;0
DECL|macro|BLADE
mdefine_line|#define BLADE&t;1
DECL|macro|XP
mdefine_line|#define XP&t;2
DECL|macro|is_image
mdefine_line|#define is_image()&t;(family == IMAGE)
DECL|macro|is_blade
mdefine_line|#define is_blade()&t;(family == BLADE)
DECL|macro|is_xp
mdefine_line|#define is_xp()&t;&t;(family == XP)
multiline_comment|/* these defines are for &squot;lcd&squot; variable */
DECL|macro|LCD_STRETCH
mdefine_line|#define LCD_STRETCH&t;0
DECL|macro|LCD_CENTER
mdefine_line|#define LCD_CENTER&t;1
DECL|macro|LCD_BIOS
mdefine_line|#define LCD_BIOS&t;2
multiline_comment|/* display types */
DECL|macro|DISPLAY_CRT
mdefine_line|#define DISPLAY_CRT&t;0
DECL|macro|DISPLAY_FP
mdefine_line|#define DISPLAY_FP&t;1
DECL|macro|flatpanel
mdefine_line|#define flatpanel (displaytype == DISPLAY_FP)
multiline_comment|/* these are for defaultaccel variable */
DECL|macro|ACCEL
mdefine_line|#define ACCEL&t;1
DECL|macro|NOACCEL
mdefine_line|#define NOACCEL&t;0
DECL|macro|TRIDENT_IOSIZE
mdefine_line|#define TRIDENT_IOSIZE&t;0x20000
DECL|macro|NTSC
mdefine_line|#define NTSC 14.31818
DECL|macro|PAL
mdefine_line|#define PAL  17.73448
multiline_comment|/* General Registers */
DECL|macro|SPR
mdefine_line|#define SPR&t;0x1F&t;&t;/* Software Programming Register (videoram) */
multiline_comment|/* 3C4 */
DECL|macro|RevisionID
mdefine_line|#define RevisionID 0x09
DECL|macro|OldOrNew
mdefine_line|#define OldOrNew 0x0B
DECL|macro|ConfPort1
mdefine_line|#define ConfPort1 0x0C
DECL|macro|ConfPort2
mdefine_line|#define ConfPort2 0x0C
DECL|macro|NewMode2
mdefine_line|#define NewMode2 0x0D
DECL|macro|NewMode1
mdefine_line|#define NewMode1 0x0E
DECL|macro|Protection
mdefine_line|#define Protection 0x11
DECL|macro|MCLKLow
mdefine_line|#define MCLKLow 0x16
DECL|macro|MCLKHigh
mdefine_line|#define MCLKHigh 0x17
DECL|macro|ClockLow
mdefine_line|#define ClockLow 0x18
DECL|macro|ClockHigh
mdefine_line|#define ClockHigh 0x19
DECL|macro|SSetup
mdefine_line|#define SSetup 0x20
DECL|macro|SKey
mdefine_line|#define SKey 0x37
DECL|macro|SPKey
mdefine_line|#define SPKey 0x57
multiline_comment|/* 0x3x4 */
DECL|macro|CRTHTotal
mdefine_line|#define CRTHTotal&t;0x00
DECL|macro|CRTHDispEnd
mdefine_line|#define CRTHDispEnd&t;0x01
DECL|macro|CRTHBlankStart
mdefine_line|#define CRTHBlankStart&t;0x02
DECL|macro|CRTHBlankEnd
mdefine_line|#define CRTHBlankEnd&t;0x03
DECL|macro|CRTHSyncStart
mdefine_line|#define CRTHSyncStart&t;0x04
DECL|macro|CRTHSyncEnd
mdefine_line|#define CRTHSyncEnd&t;0x05
DECL|macro|CRTVTotal
mdefine_line|#define CRTVTotal&t;0x06
DECL|macro|CRTVDispEnd
mdefine_line|#define CRTVDispEnd&t;0x12
DECL|macro|CRTVBlankStart
mdefine_line|#define CRTVBlankStart&t;0x15
DECL|macro|CRTVBlankEnd
mdefine_line|#define CRTVBlankEnd&t;0x16
DECL|macro|CRTVSyncStart
mdefine_line|#define CRTVSyncStart&t;0x10
DECL|macro|CRTVSyncEnd
mdefine_line|#define CRTVSyncEnd&t;0x11
DECL|macro|CRTOverflow
mdefine_line|#define CRTOverflow&t;0x07
DECL|macro|CRTPRowScan
mdefine_line|#define CRTPRowScan&t;0x08
DECL|macro|CRTMaxScanLine
mdefine_line|#define CRTMaxScanLine&t;0x09
DECL|macro|CRTModeControl
mdefine_line|#define CRTModeControl&t;0x17
DECL|macro|CRTLineCompare
mdefine_line|#define CRTLineCompare&t;0x18
multiline_comment|/* 3x4 */
DECL|macro|StartAddrHigh
mdefine_line|#define StartAddrHigh 0x0C
DECL|macro|StartAddrLow
mdefine_line|#define StartAddrLow 0x0D
DECL|macro|Offset
mdefine_line|#define Offset 0x13
DECL|macro|Underline
mdefine_line|#define Underline 0x14
DECL|macro|CRTCMode
mdefine_line|#define CRTCMode 0x17
DECL|macro|CRTCModuleTest
mdefine_line|#define CRTCModuleTest 0x1E
DECL|macro|FIFOControl
mdefine_line|#define FIFOControl 0x20
DECL|macro|LinearAddReg
mdefine_line|#define LinearAddReg 0x21
DECL|macro|DRAMTiming
mdefine_line|#define DRAMTiming 0x23
DECL|macro|New32
mdefine_line|#define New32 0x23
DECL|macro|RAMDACTiming
mdefine_line|#define RAMDACTiming 0x25
DECL|macro|CRTHiOrd
mdefine_line|#define CRTHiOrd 0x27
DECL|macro|AddColReg
mdefine_line|#define AddColReg 0x29
DECL|macro|InterfaceSel
mdefine_line|#define InterfaceSel 0x2A
DECL|macro|HorizOverflow
mdefine_line|#define HorizOverflow 0x2B
DECL|macro|GETest
mdefine_line|#define GETest 0x2D
DECL|macro|Performance
mdefine_line|#define Performance 0x2F
DECL|macro|GraphEngReg
mdefine_line|#define GraphEngReg 0x36
DECL|macro|I2C
mdefine_line|#define I2C 0x37
DECL|macro|PixelBusReg
mdefine_line|#define PixelBusReg 0x38
DECL|macro|PCIReg
mdefine_line|#define PCIReg 0x39
DECL|macro|DRAMControl
mdefine_line|#define DRAMControl 0x3A
DECL|macro|MiscContReg
mdefine_line|#define MiscContReg 0x3C
DECL|macro|CursorXLow
mdefine_line|#define CursorXLow 0x40
DECL|macro|CursorXHigh
mdefine_line|#define CursorXHigh 0x41
DECL|macro|CursorYLow
mdefine_line|#define CursorYLow 0x42
DECL|macro|CursorYHigh
mdefine_line|#define CursorYHigh 0x43
DECL|macro|CursorLocLow
mdefine_line|#define CursorLocLow 0x44
DECL|macro|CursorLocHigh
mdefine_line|#define CursorLocHigh 0x45
DECL|macro|CursorXOffset
mdefine_line|#define CursorXOffset 0x46
DECL|macro|CursorYOffset
mdefine_line|#define CursorYOffset 0x47
DECL|macro|CursorFG1
mdefine_line|#define CursorFG1 0x48
DECL|macro|CursorFG2
mdefine_line|#define CursorFG2 0x49
DECL|macro|CursorFG3
mdefine_line|#define CursorFG3 0x4A
DECL|macro|CursorFG4
mdefine_line|#define CursorFG4 0x4B
DECL|macro|CursorBG1
mdefine_line|#define CursorBG1 0x4C
DECL|macro|CursorBG2
mdefine_line|#define CursorBG2 0x4D
DECL|macro|CursorBG3
mdefine_line|#define CursorBG3 0x4E
DECL|macro|CursorBG4
mdefine_line|#define CursorBG4 0x4F
DECL|macro|CursorControl
mdefine_line|#define CursorControl 0x50
DECL|macro|PCIRetry
mdefine_line|#define PCIRetry 0x55
DECL|macro|PreEndControl
mdefine_line|#define PreEndControl 0x56
DECL|macro|PreEndFetch
mdefine_line|#define PreEndFetch 0x57
DECL|macro|PCIMaster
mdefine_line|#define PCIMaster 0x60
DECL|macro|Enhancement0
mdefine_line|#define Enhancement0 0x62
DECL|macro|NewEDO
mdefine_line|#define NewEDO 0x64
DECL|macro|TVinterface
mdefine_line|#define TVinterface 0xC0
DECL|macro|TVMode
mdefine_line|#define TVMode 0xC1
DECL|macro|ClockControl
mdefine_line|#define ClockControl 0xCF
multiline_comment|/* 3CE */
DECL|macro|MiscExtFunc
mdefine_line|#define MiscExtFunc 0x0F
DECL|macro|PowerStatus
mdefine_line|#define PowerStatus 0x23
DECL|macro|MiscIntContReg
mdefine_line|#define MiscIntContReg 0x2F
DECL|macro|CyberControl
mdefine_line|#define CyberControl 0x30
DECL|macro|CyberEnhance
mdefine_line|#define CyberEnhance 0x31
DECL|macro|FPConfig
mdefine_line|#define FPConfig     0x33
DECL|macro|VertStretch
mdefine_line|#define VertStretch  0x52
DECL|macro|HorStretch
mdefine_line|#define HorStretch   0x53
DECL|macro|BiosMode
mdefine_line|#define BiosMode     0x5c
DECL|macro|BiosReg
mdefine_line|#define BiosReg      0x5d
eof
