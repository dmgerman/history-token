multiline_comment|/* &n; * Linux driver for Disk-On-Chip devices&n; *&n; * Copyright (C) 1999 Machine Vision Holdings, Inc.   &n; * Copyright (C) 2001-2003 David Woodhouse &lt;dwmw2@infradead.org&gt;&n; * Copyright (C) 2002-2003 Greg Ungerer &lt;gerg@snapgear.com&gt;&n; * Copyright (C) 2002-2003 SnapGear Inc&n; *&n; * $Id: doc2000.h,v 1.24 2005/01/05 12:40:38 dwmw2 Exp $ &n; *&n; * Released under GPL&n; */
macro_line|#ifndef __MTD_DOC2000_H__
DECL|macro|__MTD_DOC2000_H__
mdefine_line|#define __MTD_DOC2000_H__
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|macro|DoC_Sig1
mdefine_line|#define DoC_Sig1 0
DECL|macro|DoC_Sig2
mdefine_line|#define DoC_Sig2 1
DECL|macro|DoC_ChipID
mdefine_line|#define DoC_ChipID&t;&t;0x1000
DECL|macro|DoC_DOCStatus
mdefine_line|#define DoC_DOCStatus&t;&t;0x1001
DECL|macro|DoC_DOCControl
mdefine_line|#define DoC_DOCControl&t;&t;0x1002
DECL|macro|DoC_FloorSelect
mdefine_line|#define DoC_FloorSelect&t;&t;0x1003
DECL|macro|DoC_CDSNControl
mdefine_line|#define DoC_CDSNControl&t;&t;0x1004
DECL|macro|DoC_CDSNDeviceSelect
mdefine_line|#define DoC_CDSNDeviceSelect &t;0x1005
DECL|macro|DoC_ECCConf
mdefine_line|#define DoC_ECCConf &t;&t;0x1006
DECL|macro|DoC_2k_ECCStatus
mdefine_line|#define DoC_2k_ECCStatus&t;0x1007
DECL|macro|DoC_CDSNSlowIO
mdefine_line|#define DoC_CDSNSlowIO&t;&t;0x100d
DECL|macro|DoC_ECCSyndrome0
mdefine_line|#define DoC_ECCSyndrome0&t;0x1010
DECL|macro|DoC_ECCSyndrome1
mdefine_line|#define DoC_ECCSyndrome1&t;0x1011
DECL|macro|DoC_ECCSyndrome2
mdefine_line|#define DoC_ECCSyndrome2&t;0x1012
DECL|macro|DoC_ECCSyndrome3
mdefine_line|#define DoC_ECCSyndrome3&t;0x1013
DECL|macro|DoC_ECCSyndrome4
mdefine_line|#define DoC_ECCSyndrome4&t;0x1014
DECL|macro|DoC_ECCSyndrome5
mdefine_line|#define DoC_ECCSyndrome5&t;0x1015
DECL|macro|DoC_AliasResolution
mdefine_line|#define DoC_AliasResolution &t;0x101b
DECL|macro|DoC_ConfigInput
mdefine_line|#define DoC_ConfigInput&t;&t;0x101c
DECL|macro|DoC_ReadPipeInit
mdefine_line|#define DoC_ReadPipeInit &t;0x101d
DECL|macro|DoC_WritePipeTerm
mdefine_line|#define DoC_WritePipeTerm &t;0x101e
DECL|macro|DoC_LastDataRead
mdefine_line|#define DoC_LastDataRead &t;0x101f
DECL|macro|DoC_NOP
mdefine_line|#define DoC_NOP &t;&t;0x1020
DECL|macro|DoC_Mil_CDSN_IO
mdefine_line|#define DoC_Mil_CDSN_IO &t;0x0800
DECL|macro|DoC_2k_CDSN_IO
mdefine_line|#define DoC_2k_CDSN_IO &t;&t;0x1800
DECL|macro|DoC_Mplus_NOP
mdefine_line|#define DoC_Mplus_NOP&t;&t;&t;0x1002
DECL|macro|DoC_Mplus_AliasResolution
mdefine_line|#define DoC_Mplus_AliasResolution&t;0x1004
DECL|macro|DoC_Mplus_DOCControl
mdefine_line|#define DoC_Mplus_DOCControl&t;&t;0x1006
DECL|macro|DoC_Mplus_AccessStatus
mdefine_line|#define DoC_Mplus_AccessStatus&t;&t;0x1008
DECL|macro|DoC_Mplus_DeviceSelect
mdefine_line|#define DoC_Mplus_DeviceSelect&t;&t;0x1008
DECL|macro|DoC_Mplus_Configuration
mdefine_line|#define DoC_Mplus_Configuration&t;&t;0x100a
DECL|macro|DoC_Mplus_OutputControl
mdefine_line|#define DoC_Mplus_OutputControl&t;&t;0x100c
DECL|macro|DoC_Mplus_FlashControl
mdefine_line|#define DoC_Mplus_FlashControl&t;&t;0x1020
DECL|macro|DoC_Mplus_FlashSelect
mdefine_line|#define DoC_Mplus_FlashSelect &t;&t;0x1022
DECL|macro|DoC_Mplus_FlashCmd
mdefine_line|#define DoC_Mplus_FlashCmd&t;&t;0x1024
DECL|macro|DoC_Mplus_FlashAddress
mdefine_line|#define DoC_Mplus_FlashAddress&t;&t;0x1026
DECL|macro|DoC_Mplus_FlashData0
mdefine_line|#define DoC_Mplus_FlashData0&t;&t;0x1028
DECL|macro|DoC_Mplus_FlashData1
mdefine_line|#define DoC_Mplus_FlashData1&t;&t;0x1029
DECL|macro|DoC_Mplus_ReadPipeInit
mdefine_line|#define DoC_Mplus_ReadPipeInit&t;&t;0x102a
DECL|macro|DoC_Mplus_LastDataRead
mdefine_line|#define DoC_Mplus_LastDataRead&t;&t;0x102c
DECL|macro|DoC_Mplus_LastDataRead1
mdefine_line|#define DoC_Mplus_LastDataRead1&t;&t;0x102d
DECL|macro|DoC_Mplus_WritePipeTerm
mdefine_line|#define DoC_Mplus_WritePipeTerm &t;0x102e
DECL|macro|DoC_Mplus_ECCSyndrome0
mdefine_line|#define DoC_Mplus_ECCSyndrome0&t;&t;0x1040
DECL|macro|DoC_Mplus_ECCSyndrome1
mdefine_line|#define DoC_Mplus_ECCSyndrome1&t;&t;0x1041
DECL|macro|DoC_Mplus_ECCSyndrome2
mdefine_line|#define DoC_Mplus_ECCSyndrome2&t;&t;0x1042
DECL|macro|DoC_Mplus_ECCSyndrome3
mdefine_line|#define DoC_Mplus_ECCSyndrome3&t;&t;0x1043
DECL|macro|DoC_Mplus_ECCSyndrome4
mdefine_line|#define DoC_Mplus_ECCSyndrome4&t;&t;0x1044
DECL|macro|DoC_Mplus_ECCSyndrome5
mdefine_line|#define DoC_Mplus_ECCSyndrome5&t;&t;0x1045
DECL|macro|DoC_Mplus_ECCConf
mdefine_line|#define DoC_Mplus_ECCConf &t;&t;0x1046
DECL|macro|DoC_Mplus_Toggle
mdefine_line|#define DoC_Mplus_Toggle&t;&t;0x1046
DECL|macro|DoC_Mplus_DownloadStatus
mdefine_line|#define DoC_Mplus_DownloadStatus&t;0x1074
DECL|macro|DoC_Mplus_CtrlConfirm
mdefine_line|#define DoC_Mplus_CtrlConfirm&t;&t;0x1076
DECL|macro|DoC_Mplus_Power
mdefine_line|#define DoC_Mplus_Power&t;&t;&t;0x1fff
multiline_comment|/* How to access the device? &n; * On ARM, it&squot;ll be mmap&squot;d directly with 32-bit wide accesses. &n; * On PPC, it&squot;s mmap&squot;d and 16-bit wide.&n; * Others use readb/writeb &n; */
macro_line|#if defined(__arm__)
DECL|macro|ReadDOC_
mdefine_line|#define ReadDOC_(adr, reg)      ((unsigned char)(*(volatile __u32 *)(((unsigned long)adr)+((reg)&lt;&lt;2))))
DECL|macro|WriteDOC_
mdefine_line|#define WriteDOC_(d, adr, reg)  do{ *(volatile __u32 *)(((unsigned long)adr)+((reg)&lt;&lt;2)) = (__u32)d; wmb();} while(0)
DECL|macro|DOC_IOREMAP_LEN
mdefine_line|#define DOC_IOREMAP_LEN 0x8000
macro_line|#elif defined(__ppc__)
DECL|macro|ReadDOC_
mdefine_line|#define ReadDOC_(adr, reg)      ((unsigned char)(*(volatile __u16 *)(((unsigned long)adr)+((reg)&lt;&lt;1))))
DECL|macro|WriteDOC_
mdefine_line|#define WriteDOC_(d, adr, reg)  do{ *(volatile __u16 *)(((unsigned long)adr)+((reg)&lt;&lt;1)) = (__u16)d; wmb();} while(0)
DECL|macro|DOC_IOREMAP_LEN
mdefine_line|#define DOC_IOREMAP_LEN 0x4000
macro_line|#else
DECL|macro|ReadDOC_
mdefine_line|#define ReadDOC_(adr, reg)      readb((void __iomem *)(adr) + (reg))
DECL|macro|WriteDOC_
mdefine_line|#define WriteDOC_(d, adr, reg)  writeb(d, (void __iomem *)(adr) + (reg))
DECL|macro|DOC_IOREMAP_LEN
mdefine_line|#define DOC_IOREMAP_LEN 0x2000
macro_line|#endif
macro_line|#if defined(__i386__) || defined(__x86_64__)
DECL|macro|USE_MEMCPY
mdefine_line|#define USE_MEMCPY
macro_line|#endif
multiline_comment|/* These are provided to directly use the DoC_xxx defines */
DECL|macro|ReadDOC
mdefine_line|#define ReadDOC(adr, reg)      ReadDOC_(adr,DoC_##reg)
DECL|macro|WriteDOC
mdefine_line|#define WriteDOC(d, adr, reg)  WriteDOC_(d,adr,DoC_##reg)
DECL|macro|DOC_MODE_RESET
mdefine_line|#define DOC_MODE_RESET &t;&t;0
DECL|macro|DOC_MODE_NORMAL
mdefine_line|#define DOC_MODE_NORMAL &t;1
DECL|macro|DOC_MODE_RESERVED1
mdefine_line|#define DOC_MODE_RESERVED1 &t;2
DECL|macro|DOC_MODE_RESERVED2
mdefine_line|#define DOC_MODE_RESERVED2 &t;3
DECL|macro|DOC_MODE_CLR_ERR
mdefine_line|#define DOC_MODE_CLR_ERR &t;0x80
DECL|macro|DOC_MODE_RST_LAT
mdefine_line|#define&t;DOC_MODE_RST_LAT&t;0x10
DECL|macro|DOC_MODE_BDECT
mdefine_line|#define&t;DOC_MODE_BDECT&t;&t;0x08
DECL|macro|DOC_MODE_MDWREN
mdefine_line|#define DOC_MODE_MDWREN &t;0x04
DECL|macro|DOC_ChipID_Doc2k
mdefine_line|#define DOC_ChipID_Doc2k &t;0x20
DECL|macro|DOC_ChipID_Doc2kTSOP
mdefine_line|#define DOC_ChipID_Doc2kTSOP &t;0x21&t;/* internal number for MTD */
DECL|macro|DOC_ChipID_DocMil
mdefine_line|#define DOC_ChipID_DocMil &t;0x30
DECL|macro|DOC_ChipID_DocMilPlus32
mdefine_line|#define DOC_ChipID_DocMilPlus32&t;0x40
DECL|macro|DOC_ChipID_DocMilPlus16
mdefine_line|#define DOC_ChipID_DocMilPlus16&t;0x41
DECL|macro|CDSN_CTRL_FR_B
mdefine_line|#define CDSN_CTRL_FR_B &t;&t;0x80
DECL|macro|CDSN_CTRL_FR_B0
mdefine_line|#define CDSN_CTRL_FR_B0&t;&t;0x40
DECL|macro|CDSN_CTRL_FR_B1
mdefine_line|#define CDSN_CTRL_FR_B1&t;&t;0x80
DECL|macro|CDSN_CTRL_ECC_IO
mdefine_line|#define CDSN_CTRL_ECC_IO &t;0x20
DECL|macro|CDSN_CTRL_FLASH_IO
mdefine_line|#define CDSN_CTRL_FLASH_IO &t;0x10
DECL|macro|CDSN_CTRL_WP
mdefine_line|#define CDSN_CTRL_WP &t;&t;0x08
DECL|macro|CDSN_CTRL_ALE
mdefine_line|#define CDSN_CTRL_ALE &t;&t;0x04
DECL|macro|CDSN_CTRL_CLE
mdefine_line|#define CDSN_CTRL_CLE &t;&t;0x02
DECL|macro|CDSN_CTRL_CE
mdefine_line|#define CDSN_CTRL_CE &t;&t;0x01
DECL|macro|DOC_ECC_RESET
mdefine_line|#define DOC_ECC_RESET &t;&t;0
DECL|macro|DOC_ECC_ERROR
mdefine_line|#define DOC_ECC_ERROR &t;&t;0x80
DECL|macro|DOC_ECC_RW
mdefine_line|#define DOC_ECC_RW &t;&t;0x20
DECL|macro|DOC_ECC__EN
mdefine_line|#define DOC_ECC__EN &t;&t;0x08
DECL|macro|DOC_TOGGLE_BIT
mdefine_line|#define DOC_TOGGLE_BIT &t;&t;0x04
DECL|macro|DOC_ECC_RESV
mdefine_line|#define DOC_ECC_RESV &t;&t;0x02
DECL|macro|DOC_ECC_IGNORE
mdefine_line|#define DOC_ECC_IGNORE&t;&t;0x01
DECL|macro|DOC_FLASH_CE
mdefine_line|#define DOC_FLASH_CE&t;&t;0x80
DECL|macro|DOC_FLASH_WP
mdefine_line|#define DOC_FLASH_WP&t;&t;0x40
DECL|macro|DOC_FLASH_BANK
mdefine_line|#define DOC_FLASH_BANK&t;&t;0x02
multiline_comment|/* We have to also set the reserved bit 1 for enable */
DECL|macro|DOC_ECC_EN
mdefine_line|#define DOC_ECC_EN (DOC_ECC__EN | DOC_ECC_RESV)
DECL|macro|DOC_ECC_DIS
mdefine_line|#define DOC_ECC_DIS (DOC_ECC_RESV)
DECL|struct|Nand
r_struct
id|Nand
(brace
DECL|member|floor
DECL|member|chip
r_char
id|floor
comma
id|chip
suffix:semicolon
DECL|member|curadr
r_int
r_int
id|curadr
suffix:semicolon
DECL|member|curmode
r_int
r_char
id|curmode
suffix:semicolon
multiline_comment|/* Also some erase/write/pipeline info when we get that far */
)brace
suffix:semicolon
DECL|macro|MAX_FLOORS
mdefine_line|#define MAX_FLOORS 4
DECL|macro|MAX_CHIPS
mdefine_line|#define MAX_CHIPS 4
DECL|macro|MAX_FLOORS_MIL
mdefine_line|#define MAX_FLOORS_MIL 1
DECL|macro|MAX_CHIPS_MIL
mdefine_line|#define MAX_CHIPS_MIL 1
DECL|macro|MAX_FLOORS_MPLUS
mdefine_line|#define MAX_FLOORS_MPLUS 2
DECL|macro|MAX_CHIPS_MPLUS
mdefine_line|#define MAX_CHIPS_MPLUS 1
DECL|macro|ADDR_COLUMN
mdefine_line|#define ADDR_COLUMN 1
DECL|macro|ADDR_PAGE
mdefine_line|#define ADDR_PAGE 2
DECL|macro|ADDR_COLUMN_PAGE
mdefine_line|#define ADDR_COLUMN_PAGE 3
DECL|struct|DiskOnChip
r_struct
id|DiskOnChip
(brace
DECL|member|physadr
r_int
r_int
id|physadr
suffix:semicolon
DECL|member|virtadr
r_void
id|__iomem
op_star
id|virtadr
suffix:semicolon
DECL|member|totlen
r_int
r_int
id|totlen
suffix:semicolon
DECL|member|ChipID
r_int
r_char
id|ChipID
suffix:semicolon
multiline_comment|/* Type of DiskOnChip */
DECL|member|ioreg
r_int
id|ioreg
suffix:semicolon
DECL|member|mfr
r_int
r_int
id|mfr
suffix:semicolon
multiline_comment|/* Flash IDs - only one type of flash per device */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|chipshift
r_int
id|chipshift
suffix:semicolon
DECL|member|page256
r_char
id|page256
suffix:semicolon
DECL|member|pageadrlen
r_char
id|pageadrlen
suffix:semicolon
DECL|member|interleave
r_char
id|interleave
suffix:semicolon
multiline_comment|/* Internal interleaving - Millennium Plus style */
DECL|member|erasesize
r_int
r_int
id|erasesize
suffix:semicolon
DECL|member|curfloor
r_int
id|curfloor
suffix:semicolon
DECL|member|curchip
r_int
id|curchip
suffix:semicolon
DECL|member|numchips
r_int
id|numchips
suffix:semicolon
DECL|member|chips
r_struct
id|Nand
op_star
id|chips
suffix:semicolon
DECL|member|nextdoc
r_struct
id|mtd_info
op_star
id|nextdoc
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_int
id|doc_decode_ecc
c_func
(paren
r_int
r_char
id|sector
(braket
l_int|512
)braket
comma
r_int
r_char
id|ecc1
(braket
l_int|6
)braket
)paren
suffix:semicolon
macro_line|#endif /* __MTD_DOC2000_H__ */
eof
