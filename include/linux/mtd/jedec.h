multiline_comment|/* JEDEC Flash Interface.&n; * This is an older type of interface for self programming flash. It is &n; * commonly use in older AMD chips and is obsolete compared with CFI.&n; * It is called JEDEC because the JEDEC association distributes the ID codes&n; * for the chips.&n; *&n; * See the AMD flash databook for information on how to operate the interface.&n; *&n; * $Id: jedec.h,v 1.1 2000/07/04 07:21:51 jgg Exp $&n; */
macro_line|#ifndef __LINUX_MTD_JEDEC_H__
DECL|macro|__LINUX_MTD_JEDEC_H__
mdefine_line|#define __LINUX_MTD_JEDEC_H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
DECL|macro|MAX_JEDEC_CHIPS
mdefine_line|#define MAX_JEDEC_CHIPS 16
singleline_comment|// Listing of all supported chips and their information
DECL|struct|JEDECTable
r_struct
id|JEDECTable
(brace
DECL|member|jedec
id|__u16
id|jedec
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|sectorsize
r_int
r_int
id|sectorsize
suffix:semicolon
DECL|member|capabilities
id|__u32
id|capabilities
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// JEDEC being 0 is the end of the chip array
DECL|struct|jedec_flash_chip
r_struct
id|jedec_flash_chip
(brace
DECL|member|jedec
id|__u16
id|jedec
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|sectorsize
r_int
r_int
id|sectorsize
suffix:semicolon
singleline_comment|// *(__u8*)(base + (adder &lt;&lt; addrshift)) = data &lt;&lt; datashift
singleline_comment|// Address size = size &lt;&lt; addrshift
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
singleline_comment|// Byte 0 of the flash, will be unaligned
DECL|member|datashift
r_int
r_int
id|datashift
suffix:semicolon
singleline_comment|// Useful for 32bit/16bit accesses
DECL|member|addrshift
r_int
r_int
id|addrshift
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
singleline_comment|// linerized start. base==offset for unbanked, uninterleaved flash
DECL|member|capabilities
id|__u32
id|capabilities
suffix:semicolon
singleline_comment|// These markers are filled in by the flash_chip_scan function
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|jedec_private
r_struct
id|jedec_private
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
singleline_comment|// Total size of all the devices
multiline_comment|/* Bank handling. If sum(bank_fill) == size then this is linear flash.&n;      Otherwise the mapping has holes in it. bank_fill may be used to&n;      find the holes, but in the common symetric case &n;      bank_fill[0] == bank_fill[*], thus addresses may be computed &n;      mathmatically. bank_fill must be powers of two */
DECL|member|is_banked
r_int
id|is_banked
suffix:semicolon
DECL|member|bank_fill
r_int
r_int
id|bank_fill
(braket
id|MAX_JEDEC_CHIPS
)braket
suffix:semicolon
DECL|member|chips
r_struct
id|jedec_flash_chip
id|chips
(braket
id|MAX_JEDEC_CHIPS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|JEDECTable
op_star
id|jedec_idtoinf
c_func
(paren
id|__u8
id|mfr
comma
id|__u8
id|id
)paren
suffix:semicolon
macro_line|#endif
eof
