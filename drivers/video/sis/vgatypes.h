macro_line|#ifndef _VGATYPES_
DECL|macro|_VGATYPES_
mdefine_line|#define _VGATYPES_
macro_line|#ifndef TC
DECL|macro|far
mdefine_line|#define far
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE   0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE    1
macro_line|#endif
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL    0
macro_line|#endif
macro_line|#ifndef CHAR
DECL|typedef|CHAR
r_typedef
r_char
id|CHAR
suffix:semicolon
macro_line|#endif
macro_line|#ifndef SHORT
DECL|typedef|SHORT
r_typedef
r_int
id|SHORT
suffix:semicolon
macro_line|#endif
macro_line|#ifndef LONG
DECL|typedef|LONG
r_typedef
r_int
id|LONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef UCHAR
DECL|typedef|UCHAR
r_typedef
r_int
r_char
id|UCHAR
suffix:semicolon
macro_line|#endif
macro_line|#ifndef USHORT
DECL|typedef|USHORT
r_typedef
r_int
r_int
id|USHORT
suffix:semicolon
macro_line|#endif
macro_line|#ifndef ULONG
DECL|typedef|ULONG
r_typedef
r_int
r_int
id|ULONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PUCHAR
DECL|typedef|PUCHAR
r_typedef
id|UCHAR
id|far
op_star
id|PUCHAR
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PUSHORT
DECL|typedef|PUSHORT
r_typedef
id|USHORT
id|far
op_star
id|PUSHORT
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PULONG
DECL|typedef|PULONG
r_typedef
id|ULONG
id|far
op_star
id|PULONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PVOID
DECL|typedef|PVOID
r_typedef
r_void
id|far
op_star
id|PVOID
suffix:semicolon
macro_line|#endif
macro_line|#ifndef VOID
DECL|typedef|VOID
r_typedef
r_void
id|VOID
suffix:semicolon
macro_line|#endif
macro_line|#ifndef BOOLEAN
DECL|typedef|BOOLEAN
r_typedef
id|UCHAR
id|BOOLEAN
suffix:semicolon
macro_line|#endif
macro_line|#ifndef WINCE_HEADER
macro_line|#ifndef bool
DECL|typedef|bool
r_typedef
id|UCHAR
r_bool
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* WINCE_HEADER */
macro_line|#ifndef VBIOS_VER_MAX_LENGTH
DECL|macro|VBIOS_VER_MAX_LENGTH
mdefine_line|#define VBIOS_VER_MAX_LENGTH         4
macro_line|#endif
macro_line|#ifndef WIN2000
macro_line|#ifndef SIS_VB_CHIP_TYPE
DECL|enum|_SIS_VB_CHIP_TYPE
r_typedef
r_enum
id|_SIS_VB_CHIP_TYPE
(brace
DECL|enumerator|VB_CHIP_Legacy
id|VB_CHIP_Legacy
op_assign
l_int|0
comma
DECL|enumerator|VB_CHIP_301
id|VB_CHIP_301
comma
DECL|enumerator|VB_CHIP_301B
id|VB_CHIP_301B
comma
DECL|enumerator|VB_CHIP_301BLCD
id|VB_CHIP_301BLCD
comma
DECL|enumerator|VB_CHIP_301BTV
id|VB_CHIP_301BTV
comma
DECL|enumerator|VB_CHIP_302
id|VB_CHIP_302
comma
DECL|enumerator|VB_CHIP_302B
id|VB_CHIP_302B
comma
DECL|enumerator|VB_CHIP_302BLCD
id|VB_CHIP_302BLCD
comma
DECL|enumerator|VB_CHIP_302BTV
id|VB_CHIP_302BTV
comma
DECL|enumerator|VB_CHIP_303
id|VB_CHIP_303
comma
DECL|enumerator|VB_CHIP_UNKNOWN
id|VB_CHIP_UNKNOWN
comma
multiline_comment|/* other video bridge or no video bridge */
DECL|enumerator|MAX_VB_CHIP
id|MAX_VB_CHIP
DECL|typedef|SIS_VB_CHIP_TYPE
)brace
id|SIS_VB_CHIP_TYPE
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifndef WIN2000
macro_line|#ifndef SIS_LCD_TYPE
DECL|enum|_SIS_LCD_TYPE
r_typedef
r_enum
id|_SIS_LCD_TYPE
(brace
DECL|enumerator|LCD_INVALID
id|LCD_INVALID
op_assign
l_int|0
comma
DECL|enumerator|LCD_800x600
id|LCD_800x600
comma
DECL|enumerator|LCD_1024x768
id|LCD_1024x768
comma
DECL|enumerator|LCD_1280x1024
id|LCD_1280x1024
comma
DECL|enumerator|LCD_1280x960
id|LCD_1280x960
comma
DECL|enumerator|LCD_640x480
id|LCD_640x480
comma
DECL|enumerator|LCD_1600x1200
id|LCD_1600x1200
comma
DECL|enumerator|LCD_1920x1440
id|LCD_1920x1440
comma
DECL|enumerator|LCD_2048x1536
id|LCD_2048x1536
comma
DECL|enumerator|LCD_UNKNOWN
id|LCD_UNKNOWN
DECL|typedef|SIS_LCD_TYPE
)brace
id|SIS_LCD_TYPE
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifndef WIN2000&t;&t;&t;/* mark by Paul ,Move definition to sisv.h */
macro_line|#ifndef PSIS_DSReg
DECL|struct|_SIS_DSReg
r_typedef
r_struct
id|_SIS_DSReg
(brace
DECL|member|jIdx
id|UCHAR
id|jIdx
suffix:semicolon
DECL|member|jVal
id|UCHAR
id|jVal
suffix:semicolon
DECL|typedef|SIS_DSReg
DECL|typedef|PSIS_DSReg
)brace
id|SIS_DSReg
comma
op_star
id|PSIS_DSReg
suffix:semicolon
macro_line|#endif
macro_line|#ifndef SIS_HW_DEVICE_INFO
DECL|typedef|SIS_HW_DEVICE_INFO
DECL|typedef|PSIS_HW_DEVICE_INFO
r_typedef
r_struct
id|_SIS_HW_DEVICE_INFO
id|SIS_HW_DEVICE_INFO
comma
op_star
id|PSIS_HW_DEVICE_INFO
suffix:semicolon
DECL|typedef|PSIS_QUERYSPACE
r_typedef
id|BOOLEAN
(paren
op_star
id|PSIS_QUERYSPACE
)paren
(paren
id|PSIS_HW_DEVICE_INFO
comma
id|ULONG
comma
id|ULONG
comma
id|ULONG
op_star
)paren
suffix:semicolon
DECL|struct|_SIS_HW_DEVICE_INFO
r_struct
id|_SIS_HW_DEVICE_INFO
(brace
DECL|member|pDevice
id|PVOID
id|pDevice
suffix:semicolon
multiline_comment|/* The pointer to the physical device data structure &n;&t;&t;&t;&t;   in each OS or NULL for unused. */
DECL|member|pjVirtualRomBase
id|UCHAR
op_star
id|pjVirtualRomBase
suffix:semicolon
multiline_comment|/* Only for NT, NULL for WinCE &amp; Linux. */
multiline_comment|/* base virtual address of VBIOS ROM Space */
multiline_comment|/* or base virtual address of ROM image file. */
multiline_comment|/* if NULL, then read from pjROMImage; */
multiline_comment|/* Note:ROM image file is the file of VBIOS ROM */
DECL|member|pjCustomizedROMImage
id|UCHAR
op_star
id|pjCustomizedROMImage
suffix:semicolon
multiline_comment|/* base virtual address of ROM image file. */
multiline_comment|/* wincE:ROM image file is the file for OEM */
multiline_comment|/*       customized table */
multiline_comment|/* Linux: not used */
multiline_comment|/* NT   : not used  */
multiline_comment|/* Note : pjCustomizedROMImage=NULL if no ROM image file */
DECL|member|pjVideoMemoryAddress
id|UCHAR
op_star
id|pjVideoMemoryAddress
suffix:semicolon
multiline_comment|/* base virtual memory address */
multiline_comment|/* of Linear VGA memory */
DECL|member|ulVideoMemorySize
id|ULONG
id|ulVideoMemorySize
suffix:semicolon
multiline_comment|/* size, in bytes, of the memory on the board */
DECL|member|ulIOAddress
id|ULONG
id|ulIOAddress
suffix:semicolon
multiline_comment|/* base I/O address of VGA ports (0x3B0) */
DECL|member|jChipType
id|UCHAR
id|jChipType
suffix:semicolon
multiline_comment|/* Used to Identify SiS Graphics Chip */
multiline_comment|/* defined in the data structure type  */
multiline_comment|/* &quot;SIS_CHIP_TYPE&quot; */
DECL|member|jChipRevision
id|UCHAR
id|jChipRevision
suffix:semicolon
multiline_comment|/* Used to Identify SiS Graphics Chip Revision */
DECL|member|ujVBChipID
id|UCHAR
id|ujVBChipID
suffix:semicolon
multiline_comment|/* the ID of video bridge */
multiline_comment|/* defined in the data structure type */
multiline_comment|/* &quot;SIS_VB_CHIP_TYPE&quot; */
DECL|member|usExternalChip
id|USHORT
id|usExternalChip
suffix:semicolon
multiline_comment|/* NO VB or other video bridge(not  */
multiline_comment|/* SiS video bridge) */
multiline_comment|/* if ujVBChipID = VB_CHIP_UNKNOWN, */
multiline_comment|/* then bit0=1 : LVDS,bit1=1 : trumpion, */
multiline_comment|/* bit2=1 : CH7005 &amp; no video bridge if */
multiline_comment|/* usExternalChip = 0. */
multiline_comment|/* Note: CR37[3:1]: */
multiline_comment|/*             001:SiS 301 */
multiline_comment|/*             010:LVDS */
multiline_comment|/*             011:Trumpion LVDS Scaling Chip */
multiline_comment|/*             100:LVDS(LCD-out)+Chrontel 7005 */
multiline_comment|/*             101:Single Chrontel 7005 */
DECL|member|ulCRT2LCDType
id|ULONG
id|ulCRT2LCDType
suffix:semicolon
multiline_comment|/* defined in the data structure type */
multiline_comment|/* &quot;SIS_LCD_TYPE&quot; */
DECL|member|bIntegratedMMEnabled
id|BOOLEAN
id|bIntegratedMMEnabled
suffix:semicolon
multiline_comment|/* supporting integration MM enable */
DECL|member|bSkipDramSizing
id|BOOLEAN
id|bSkipDramSizing
suffix:semicolon
multiline_comment|/* True: Skip video memory sizing. */
DECL|member|pSR
id|PSIS_DSReg
id|pSR
suffix:semicolon
multiline_comment|/* restore SR registers in initial function. */
multiline_comment|/* end data :(idx, val) =  (FF, FF). */
multiline_comment|/* Note : restore SR registers if  */
multiline_comment|/* bSkipDramSizing = TRUE */
DECL|member|pCR
id|PSIS_DSReg
id|pCR
suffix:semicolon
multiline_comment|/* restore CR registers in initial function. */
multiline_comment|/* end data :(idx, val) =  (FF, FF) */
multiline_comment|/* Note : restore cR registers if  */
multiline_comment|/* bSkipDramSizing = TRUE */
DECL|member|pQueryVGAConfigSpace
id|PSIS_QUERYSPACE
id|pQueryVGAConfigSpace
suffix:semicolon
multiline_comment|/* Get/Set VGA Configuration  */
multiline_comment|/* space */
DECL|member|pQueryNorthBridgeSpace
id|PSIS_QUERYSPACE
id|pQueryNorthBridgeSpace
suffix:semicolon
multiline_comment|/* Get/Set North Bridge  */
multiline_comment|/* space  */
DECL|member|szVBIOSVer
id|UCHAR
id|szVBIOSVer
(braket
id|VBIOS_VER_MAX_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/*~ mark by Paul ,Move definition to sisv.h */
macro_line|#ifndef WIN2000
macro_line|#ifndef WINCE_HEADER
macro_line|#ifndef BUS_DATA_TYPE
DECL|enum|_BUS_DATA_TYPE
r_typedef
r_enum
id|_BUS_DATA_TYPE
(brace
DECL|enumerator|ConfigurationSpaceUndefined
id|ConfigurationSpaceUndefined
op_assign
op_minus
l_int|1
comma
DECL|enumerator|Cmos
id|Cmos
comma
DECL|enumerator|EisaConfiguration
id|EisaConfiguration
comma
DECL|enumerator|Pos
id|Pos
comma
DECL|enumerator|CbusConfiguration
id|CbusConfiguration
comma
DECL|enumerator|PCIConfiguration
id|PCIConfiguration
comma
DECL|enumerator|VMEConfiguration
id|VMEConfiguration
comma
DECL|enumerator|NuBusConfiguration
id|NuBusConfiguration
comma
DECL|enumerator|PCMCIAConfiguration
id|PCMCIAConfiguration
comma
DECL|enumerator|MPIConfiguration
id|MPIConfiguration
comma
DECL|enumerator|MPSAConfiguration
id|MPSAConfiguration
comma
DECL|enumerator|PNPISAConfiguration
id|PNPISAConfiguration
comma
DECL|enumerator|MaximumBusDataType
id|MaximumBusDataType
DECL|typedef|BUS_DATA_TYPE
DECL|typedef|PBUS_DATA_TYPE
)brace
id|BUS_DATA_TYPE
comma
op_star
id|PBUS_DATA_TYPE
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* WINCE_HEADER */
macro_line|#ifndef PCI_TYPE0_ADDRESSES
DECL|macro|PCI_TYPE0_ADDRESSES
mdefine_line|#define PCI_TYPE0_ADDRESSES             6
macro_line|#endif
macro_line|#ifndef PCI_TYPE1_ADDRESSES
DECL|macro|PCI_TYPE1_ADDRESSES
mdefine_line|#define PCI_TYPE1_ADDRESSES             2
macro_line|#endif
macro_line|#ifndef WINCE_HEADER
macro_line|#ifndef PCI_COMMON_CONFIG
DECL|struct|_PCI_COMMON_CONFIG
r_typedef
r_struct
id|_PCI_COMMON_CONFIG
(brace
DECL|member|VendorID
id|USHORT
id|VendorID
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|DeviceID
id|USHORT
id|DeviceID
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|Command
id|USHORT
id|Command
suffix:semicolon
multiline_comment|/* Device control       */
DECL|member|Status
id|USHORT
id|Status
suffix:semicolon
DECL|member|RevisionID
id|UCHAR
id|RevisionID
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|ProgIf
id|UCHAR
id|ProgIf
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|SubClass
id|UCHAR
id|SubClass
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|BaseClass
id|UCHAR
id|BaseClass
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|CacheLineSize
id|UCHAR
id|CacheLineSize
suffix:semicolon
multiline_comment|/* (ro+)                */
DECL|member|LatencyTimer
id|UCHAR
id|LatencyTimer
suffix:semicolon
multiline_comment|/* (ro+)                */
DECL|member|HeaderType
id|UCHAR
id|HeaderType
suffix:semicolon
multiline_comment|/* (ro)                 */
DECL|member|BIST
id|UCHAR
id|BIST
suffix:semicolon
multiline_comment|/* Built in self test   */
r_union
(brace
DECL|struct|_PCI_HEADER_TYPE_0
r_struct
id|_PCI_HEADER_TYPE_0
(brace
DECL|member|BaseAddresses
id|ULONG
id|BaseAddresses
(braket
id|PCI_TYPE0_ADDRESSES
)braket
suffix:semicolon
DECL|member|CIS
id|ULONG
id|CIS
suffix:semicolon
DECL|member|SubVendorID
id|USHORT
id|SubVendorID
suffix:semicolon
DECL|member|SubSystemID
id|USHORT
id|SubSystemID
suffix:semicolon
DECL|member|ROMBaseAddress
id|ULONG
id|ROMBaseAddress
suffix:semicolon
DECL|member|Reserved2
id|ULONG
id|Reserved2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|InterruptLine
id|UCHAR
id|InterruptLine
suffix:semicolon
multiline_comment|/*                    */
DECL|member|InterruptPin
id|UCHAR
id|InterruptPin
suffix:semicolon
multiline_comment|/* (ro)               */
DECL|member|MinimumGrant
id|UCHAR
id|MinimumGrant
suffix:semicolon
multiline_comment|/* (ro)               */
DECL|member|MaximumLatency
id|UCHAR
id|MaximumLatency
suffix:semicolon
multiline_comment|/* (ro)               */
DECL|member|type0
)brace
id|type0
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|DeviceSpecific
id|UCHAR
id|DeviceSpecific
(braket
l_int|192
)braket
suffix:semicolon
DECL|typedef|PCI_COMMON_CONFIG
DECL|typedef|PPCI_COMMON_CONFIG
)brace
id|PCI_COMMON_CONFIG
comma
op_star
id|PPCI_COMMON_CONFIG
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* WINCE_HEADER */
macro_line|#ifndef FIELD_OFFSET
DECL|macro|FIELD_OFFSET
mdefine_line|#define FIELD_OFFSET(type, field)    ((LONG)&amp;(((type *)0)-&gt;field))
macro_line|#endif
macro_line|#ifndef PCI_COMMON_HDR_LENGTH
DECL|macro|PCI_COMMON_HDR_LENGTH
mdefine_line|#define PCI_COMMON_HDR_LENGTH (FIELD_OFFSET (PCI_COMMON_CONFIG, DeviceSpecific))
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
