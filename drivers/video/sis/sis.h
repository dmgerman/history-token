macro_line|#ifndef _SISFB_LOCAL
DECL|macro|_SISFB_LOCAL
mdefine_line|#define _SISFB_LOCAL
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|NOBIOS
macro_line|#undef NOBIOS
DECL|macro|CONFIG_FB_SIS_LINUXBIOS
macro_line|#undef CONFIG_FB_SIS_LINUXBIOS
macro_line|#ifdef NOBIOS
DECL|macro|CONFIG_FB_SIS_LINUXBIOS
macro_line|#undef CONFIG_FB_SIS_LINUXBIOS
macro_line|#endif
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|NO_ERROR
mdefine_line|#define NO_ERROR 0
multiline_comment|/* Data type conversion */
DECL|macro|UCHAR
mdefine_line|#define UCHAR   unsigned char
DECL|macro|USHORT
mdefine_line|#define USHORT  unsigned short
DECL|macro|ULONG
mdefine_line|#define ULONG   unsigned long
DECL|macro|SHORT
mdefine_line|#define SHORT   short
DECL|macro|BOOLEAN
mdefine_line|#define BOOLEAN int
DECL|macro|VOID
mdefine_line|#define VOID void
DECL|macro|IND_SIS_CRT2_PORT_04
mdefine_line|#define IND_SIS_CRT2_PORT_04        0x04 - 0x30
DECL|macro|IND_SIS_CRT2_PORT_10
mdefine_line|#define IND_SIS_CRT2_PORT_10        0x10 - 0x30
DECL|macro|IND_SIS_CRT2_PORT_12
mdefine_line|#define IND_SIS_CRT2_PORT_12        0x12 - 0x30
DECL|macro|IND_SIS_CRT2_PORT_14
mdefine_line|#define IND_SIS_CRT2_PORT_14        0x14 - 0x30
DECL|macro|ClearALLBuffer
mdefine_line|#define ClearALLBuffer(x)  ClearBuffer(x)
multiline_comment|/* Data struct for setmode codes */
DECL|enum|_CHIP_TYPE
r_typedef
r_enum
id|_CHIP_TYPE
(brace
DECL|enumerator|SIS_GENERIC
id|SIS_GENERIC
op_assign
l_int|0
comma
DECL|enumerator|SIS_Glamour
id|SIS_Glamour
comma
singleline_comment|//300
DECL|enumerator|SIS_Trojan
id|SIS_Trojan
comma
singleline_comment|//630
DECL|enumerator|SIS_Spartan
id|SIS_Spartan
comma
singleline_comment|//540
DECL|enumerator|SIS_730
id|SIS_730
comma
DECL|enumerator|MAX_SIS_CHIP
id|MAX_SIS_CHIP
DECL|typedef|CHIP_TYPE
)brace
id|CHIP_TYPE
suffix:semicolon
DECL|enum|_LCD_TYPE
r_typedef
r_enum
id|_LCD_TYPE
(brace
DECL|enumerator|LCD1024
id|LCD1024
op_assign
l_int|1
comma
DECL|enumerator|LCD1280
id|LCD1280
comma
DECL|enumerator|LCD2048
id|LCD2048
comma
DECL|enumerator|LCD1920
id|LCD1920
comma
DECL|enumerator|LCD1600
id|LCD1600
comma
DECL|enumerator|LCD800
id|LCD800
comma
DECL|enumerator|LCD640
id|LCD640
DECL|typedef|LCD_TYPE
)brace
id|LCD_TYPE
suffix:semicolon
DECL|struct|_HW_DEVICE_EXTENSION
r_typedef
r_struct
id|_HW_DEVICE_EXTENSION
(brace
DECL|member|VirtualRomBase
r_int
r_int
id|VirtualRomBase
suffix:semicolon
DECL|member|VirtualVideoMemoryAddress
r_char
op_star
id|VirtualVideoMemoryAddress
suffix:semicolon
DECL|member|IOAddress
r_int
r_int
id|IOAddress
suffix:semicolon
DECL|member|jChipID
id|CHIP_TYPE
id|jChipID
suffix:semicolon
DECL|member|bIntegratedMMEnabled
r_int
id|bIntegratedMMEnabled
suffix:semicolon
DECL|member|usLCDType
id|LCD_TYPE
id|usLCDType
suffix:semicolon
DECL|member|revision_id
id|u8
id|revision_id
suffix:semicolon
DECL|member|uVBChipID
id|u8
id|uVBChipID
suffix:semicolon
DECL|typedef|HW_DEVICE_EXTENSION
DECL|typedef|PHW_DEVICE_EXTENSION
)brace
id|HW_DEVICE_EXTENSION
comma
op_star
id|PHW_DEVICE_EXTENSION
suffix:semicolon
macro_line|#endif
eof
