multiline_comment|/*&n; * $Id: mtd-abi.h,v 1.7 2004/11/23 15:37:32 gleixner Exp $&n; *&n; * Portions of MTD ABI definition which are shared by kernel and user space &n; */
macro_line|#ifndef __MTD_ABI_H__
DECL|macro|__MTD_ABI_H__
mdefine_line|#define __MTD_ABI_H__
macro_line|#ifndef __KERNEL__ /* Urgh. The whole point of splitting this out into&n;&t;&t;    separate files was to avoid #ifdef __KERNEL__ */
DECL|macro|__user
mdefine_line|#define __user
macro_line|#endif
DECL|struct|erase_info_user
r_struct
id|erase_info_user
(brace
DECL|member|start
r_uint32
id|start
suffix:semicolon
DECL|member|length
r_uint32
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtd_oob_buf
r_struct
id|mtd_oob_buf
(brace
DECL|member|start
r_uint32
id|start
suffix:semicolon
DECL|member|length
r_uint32
id|length
suffix:semicolon
DECL|member|ptr
r_int
r_char
id|__user
op_star
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MTD_ABSENT
mdefine_line|#define MTD_ABSENT&t;&t;0
DECL|macro|MTD_RAM
mdefine_line|#define MTD_RAM&t;&t;&t;1
DECL|macro|MTD_ROM
mdefine_line|#define MTD_ROM&t;&t;&t;2
DECL|macro|MTD_NORFLASH
mdefine_line|#define MTD_NORFLASH&t;&t;3
DECL|macro|MTD_NANDFLASH
mdefine_line|#define MTD_NANDFLASH&t;&t;4
DECL|macro|MTD_PEROM
mdefine_line|#define MTD_PEROM&t;&t;5
DECL|macro|MTD_OTHER
mdefine_line|#define MTD_OTHER&t;&t;14
DECL|macro|MTD_UNKNOWN
mdefine_line|#define MTD_UNKNOWN&t;&t;15
DECL|macro|MTD_CLEAR_BITS
mdefine_line|#define MTD_CLEAR_BITS&t;&t;1       
singleline_comment|// Bits can be cleared (flash)
DECL|macro|MTD_SET_BITS
mdefine_line|#define MTD_SET_BITS&t;&t;2       
singleline_comment|// Bits can be set
DECL|macro|MTD_ERASEABLE
mdefine_line|#define MTD_ERASEABLE&t;&t;4       
singleline_comment|// Has an erase function
DECL|macro|MTD_WRITEB_WRITEABLE
mdefine_line|#define MTD_WRITEB_WRITEABLE&t;8       
singleline_comment|// Direct IO is possible
DECL|macro|MTD_VOLATILE
mdefine_line|#define MTD_VOLATILE&t;&t;16      
singleline_comment|// Set for RAMs
DECL|macro|MTD_XIP
mdefine_line|#define MTD_XIP&t;&t;&t;32&t;
singleline_comment|// eXecute-In-Place possible
DECL|macro|MTD_OOB
mdefine_line|#define MTD_OOB&t;&t;&t;64&t;
singleline_comment|// Out-of-band data (NAND flash)
DECL|macro|MTD_ECC
mdefine_line|#define MTD_ECC&t;&t;&t;128&t;
singleline_comment|// Device capable of automatic ECC
DECL|macro|MTD_NO_VIRTBLOCKS
mdefine_line|#define MTD_NO_VIRTBLOCKS&t;256&t;
singleline_comment|// Virtual blocks not allowed
singleline_comment|// Some common devices / combinations of capabilities
DECL|macro|MTD_CAP_ROM
mdefine_line|#define MTD_CAP_ROM&t;&t;0
DECL|macro|MTD_CAP_RAM
mdefine_line|#define MTD_CAP_RAM&t;&t;(MTD_CLEAR_BITS|MTD_SET_BITS|MTD_WRITEB_WRITEABLE)
DECL|macro|MTD_CAP_NORFLASH
mdefine_line|#define MTD_CAP_NORFLASH        (MTD_CLEAR_BITS|MTD_ERASEABLE)
DECL|macro|MTD_CAP_NANDFLASH
mdefine_line|#define MTD_CAP_NANDFLASH       (MTD_CLEAR_BITS|MTD_ERASEABLE|MTD_OOB)
DECL|macro|MTD_WRITEABLE
mdefine_line|#define MTD_WRITEABLE&t;&t;(MTD_CLEAR_BITS|MTD_SET_BITS)
singleline_comment|// Types of automatic ECC/Checksum available
DECL|macro|MTD_ECC_NONE
mdefine_line|#define MTD_ECC_NONE&t;&t;0 &t;
singleline_comment|// No automatic ECC available
DECL|macro|MTD_ECC_RS_DiskOnChip
mdefine_line|#define MTD_ECC_RS_DiskOnChip&t;1&t;
singleline_comment|// Automatic ECC on DiskOnChip
DECL|macro|MTD_ECC_SW
mdefine_line|#define MTD_ECC_SW&t;&t;2&t;
singleline_comment|// SW ECC for Toshiba &amp; Samsung devices
multiline_comment|/* ECC byte placement */
DECL|macro|MTD_NANDECC_OFF
mdefine_line|#define MTD_NANDECC_OFF&t;&t;0&t;
singleline_comment|// Switch off ECC (Not recommended)
DECL|macro|MTD_NANDECC_PLACE
mdefine_line|#define MTD_NANDECC_PLACE&t;1&t;
singleline_comment|// Use the given placement in the structure (YAFFS1 legacy mode)
DECL|macro|MTD_NANDECC_AUTOPLACE
mdefine_line|#define MTD_NANDECC_AUTOPLACE&t;2&t;
singleline_comment|// Use the default placement scheme
DECL|macro|MTD_NANDECC_PLACEONLY
mdefine_line|#define MTD_NANDECC_PLACEONLY&t;3&t;
singleline_comment|// Use the given placement in the structure (Do not store ecc result on read)
DECL|struct|mtd_info_user
r_struct
id|mtd_info_user
(brace
DECL|member|type
r_uint8
id|type
suffix:semicolon
DECL|member|flags
r_uint32
id|flags
suffix:semicolon
DECL|member|size
r_uint32
id|size
suffix:semicolon
singleline_comment|// Total size of the MTD
DECL|member|erasesize
r_uint32
id|erasesize
suffix:semicolon
DECL|member|oobblock
r_uint32
id|oobblock
suffix:semicolon
singleline_comment|// Size of OOB blocks (e.g. 512)
DECL|member|oobsize
r_uint32
id|oobsize
suffix:semicolon
singleline_comment|// Amount of OOB data per block (e.g. 16)
DECL|member|ecctype
r_uint32
id|ecctype
suffix:semicolon
DECL|member|eccsize
r_uint32
id|eccsize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|region_info_user
r_struct
id|region_info_user
(brace
DECL|member|offset
r_uint32
id|offset
suffix:semicolon
multiline_comment|/* At which this region starts, &n;&t;&t;&t;&t;&t; * from the beginning of the MTD */
DECL|member|erasesize
r_uint32
id|erasesize
suffix:semicolon
multiline_comment|/* For this region */
DECL|member|numblocks
r_uint32
id|numblocks
suffix:semicolon
multiline_comment|/* Number of blocks in this region */
DECL|member|regionindex
r_uint32
id|regionindex
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MEMGETINFO
mdefine_line|#define MEMGETINFO              _IOR(&squot;M&squot;, 1, struct mtd_info_user)
DECL|macro|MEMERASE
mdefine_line|#define MEMERASE                _IOW(&squot;M&squot;, 2, struct erase_info_user)
DECL|macro|MEMWRITEOOB
mdefine_line|#define MEMWRITEOOB             _IOWR(&squot;M&squot;, 3, struct mtd_oob_buf)
DECL|macro|MEMREADOOB
mdefine_line|#define MEMREADOOB              _IOWR(&squot;M&squot;, 4, struct mtd_oob_buf)
DECL|macro|MEMLOCK
mdefine_line|#define MEMLOCK                 _IOW(&squot;M&squot;, 5, struct erase_info_user)
DECL|macro|MEMUNLOCK
mdefine_line|#define MEMUNLOCK               _IOW(&squot;M&squot;, 6, struct erase_info_user)
DECL|macro|MEMGETREGIONCOUNT
mdefine_line|#define MEMGETREGIONCOUNT&t;_IOR(&squot;M&squot;, 7, int)
DECL|macro|MEMGETREGIONINFO
mdefine_line|#define MEMGETREGIONINFO&t;_IOWR(&squot;M&squot;, 8, struct region_info_user)
DECL|macro|MEMSETOOBSEL
mdefine_line|#define MEMSETOOBSEL&t;&t;_IOW(&squot;M&squot;, 9, struct nand_oobinfo)
DECL|macro|MEMGETOOBSEL
mdefine_line|#define MEMGETOOBSEL&t;&t;_IOR(&squot;M&squot;, 10, struct nand_oobinfo)
DECL|macro|MEMGETBADBLOCK
mdefine_line|#define MEMGETBADBLOCK&t;&t;_IOW(&squot;M&squot;, 11, loff_t)
DECL|macro|MEMSETBADBLOCK
mdefine_line|#define MEMSETBADBLOCK&t;&t;_IOW(&squot;M&squot;, 12, loff_t)
DECL|struct|nand_oobinfo
r_struct
id|nand_oobinfo
(brace
DECL|member|useecc
r_uint32
id|useecc
suffix:semicolon
DECL|member|eccbytes
r_uint32
id|eccbytes
suffix:semicolon
DECL|member|oobfree
r_uint32
id|oobfree
(braket
l_int|8
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|eccpos
r_uint32
id|eccpos
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __MTD_ABI_H__ */
eof
