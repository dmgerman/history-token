multiline_comment|/* Defines for NAND Flash Translation Layer  */
multiline_comment|/* (c) 1999 Machine Vision Holdings, Inc.    */
multiline_comment|/* Author: David Woodhouse &lt;dwmw2@mvhi.com&gt;  */
multiline_comment|/* $Id: nftl.h,v 1.9 2000/11/07 05:48:49 ollie Exp $ */
macro_line|#ifndef __MTD_NFTL_H__
DECL|macro|__MTD_NFTL_H__
mdefine_line|#define __MTD_NFTL_H__
macro_line|#ifndef __BOOT__
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#endif
multiline_comment|/* Block Control Information */
DECL|struct|nftl_bci
r_struct
id|nftl_bci
(brace
DECL|member|ECCSig
r_int
r_char
id|ECCSig
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|Status
id|__u8
id|Status
suffix:semicolon
DECL|member|Status1
id|__u8
id|Status1
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Unit Control Information */
DECL|struct|nftl_uci0
r_struct
id|nftl_uci0
(brace
DECL|member|VirtUnitNum
id|__u16
id|VirtUnitNum
suffix:semicolon
DECL|member|ReplUnitNum
id|__u16
id|ReplUnitNum
suffix:semicolon
DECL|member|SpareVirtUnitNum
id|__u16
id|SpareVirtUnitNum
suffix:semicolon
DECL|member|SpareReplUnitNum
id|__u16
id|SpareReplUnitNum
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|nftl_uci1
r_struct
id|nftl_uci1
(brace
DECL|member|WearInfo
id|__u32
id|WearInfo
suffix:semicolon
DECL|member|EraseMark
id|__u16
id|EraseMark
suffix:semicolon
DECL|member|EraseMark1
id|__u16
id|EraseMark1
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|nftl_uci2
r_struct
id|nftl_uci2
(brace
DECL|member|FoldMark
id|__u16
id|FoldMark
suffix:semicolon
DECL|member|FoldMark1
id|__u16
id|FoldMark1
suffix:semicolon
DECL|member|unused
id|__u32
id|unused
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|union|nftl_uci
r_union
id|nftl_uci
(brace
DECL|member|a
r_struct
id|nftl_uci0
id|a
suffix:semicolon
DECL|member|b
r_struct
id|nftl_uci1
id|b
suffix:semicolon
DECL|member|c
r_struct
id|nftl_uci2
id|c
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nftl_oob
r_struct
id|nftl_oob
(brace
DECL|member|b
r_struct
id|nftl_bci
id|b
suffix:semicolon
DECL|member|u
r_union
id|nftl_uci
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* NFTL Media Header */
DECL|struct|NFTLMediaHeader
r_struct
id|NFTLMediaHeader
(brace
DECL|member|DataOrgID
r_char
id|DataOrgID
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|NumEraseUnits
id|__u16
id|NumEraseUnits
suffix:semicolon
DECL|member|FirstPhysicalEUN
id|__u16
id|FirstPhysicalEUN
suffix:semicolon
DECL|member|FormattedSize
id|__u32
id|FormattedSize
suffix:semicolon
DECL|member|UnitSizeFactor
r_int
r_char
id|UnitSizeFactor
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|MAX_ERASE_ZONES
mdefine_line|#define MAX_ERASE_ZONES (8192 - 512)
DECL|macro|ERASE_MARK
mdefine_line|#define ERASE_MARK 0x3c69
DECL|macro|SECTOR_FREE
mdefine_line|#define SECTOR_FREE 0xff
DECL|macro|SECTOR_USED
mdefine_line|#define SECTOR_USED 0x55
DECL|macro|SECTOR_IGNORE
mdefine_line|#define SECTOR_IGNORE 0x11
DECL|macro|SECTOR_DELETED
mdefine_line|#define SECTOR_DELETED 0x00
DECL|macro|FOLD_MARK_IN_PROGRESS
mdefine_line|#define FOLD_MARK_IN_PROGRESS 0x5555
DECL|macro|ZONE_GOOD
mdefine_line|#define ZONE_GOOD 0xff
DECL|macro|ZONE_BAD_ORIGINAL
mdefine_line|#define ZONE_BAD_ORIGINAL 0
DECL|macro|ZONE_BAD_MARKED
mdefine_line|#define ZONE_BAD_MARKED 7
macro_line|#ifdef __KERNEL__
multiline_comment|/* these info are used in ReplUnitTable */
DECL|macro|BLOCK_NIL
mdefine_line|#define BLOCK_NIL          0xffff /* last block of a chain */
DECL|macro|BLOCK_FREE
mdefine_line|#define BLOCK_FREE         0xfffe /* free block */
DECL|macro|BLOCK_NOTEXPLORED
mdefine_line|#define BLOCK_NOTEXPLORED  0xfffd /* non explored block, only used during mounting */
DECL|macro|BLOCK_RESERVED
mdefine_line|#define BLOCK_RESERVED     0xfffc /* bios block or bad block */
DECL|struct|NFTLrecord
r_struct
id|NFTLrecord
(brace
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|member|MediaUnit
DECL|member|SpareMediaUnit
id|__u16
id|MediaUnit
comma
id|SpareMediaUnit
suffix:semicolon
DECL|member|EraseSize
id|__u32
id|EraseSize
suffix:semicolon
DECL|member|MediaHdr
r_struct
id|NFTLMediaHeader
id|MediaHdr
suffix:semicolon
DECL|member|usecount
r_int
id|usecount
suffix:semicolon
DECL|member|heads
r_int
r_char
id|heads
suffix:semicolon
DECL|member|sectors
r_int
r_char
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
r_int
id|cylinders
suffix:semicolon
DECL|member|numvunits
id|__u16
id|numvunits
suffix:semicolon
DECL|member|lastEUN
id|__u16
id|lastEUN
suffix:semicolon
multiline_comment|/* should be suppressed */
DECL|member|numfreeEUNs
id|__u16
id|numfreeEUNs
suffix:semicolon
DECL|member|LastFreeEUN
id|__u16
id|LastFreeEUN
suffix:semicolon
multiline_comment|/* To speed up finding a free EUN */
DECL|member|nr_sects
id|__u32
r_int
id|nr_sects
suffix:semicolon
DECL|member|head
DECL|member|sect
DECL|member|cyl
r_int
id|head
comma
id|sect
comma
id|cyl
suffix:semicolon
DECL|member|EUNtable
id|__u16
op_star
id|EUNtable
suffix:semicolon
multiline_comment|/* [numvunits]: First EUN for each virtual unit  */
DECL|member|ReplUnitTable
id|__u16
op_star
id|ReplUnitTable
suffix:semicolon
multiline_comment|/* [numEUNs]: ReplUnitNumber for each */
DECL|member|nb_blocks
r_int
r_int
id|nb_blocks
suffix:semicolon
multiline_comment|/* number of physical blocks */
DECL|member|nb_boot_blocks
r_int
r_int
id|nb_boot_blocks
suffix:semicolon
multiline_comment|/* number of blocks used by the bios */
DECL|member|instr
r_struct
id|erase_info
id|instr
suffix:semicolon
)brace
suffix:semicolon
r_int
id|NFTL_mount
c_func
(paren
r_struct
id|NFTLrecord
op_star
id|s
)paren
suffix:semicolon
r_int
id|NFTL_formatblock
c_func
(paren
r_struct
id|NFTLrecord
op_star
id|s
comma
r_int
id|block
)paren
suffix:semicolon
macro_line|#ifndef NFTL_MAJOR
DECL|macro|NFTL_MAJOR
mdefine_line|#define NFTL_MAJOR 93
macro_line|#endif
DECL|macro|MAX_NFTLS
mdefine_line|#define MAX_NFTLS 16
DECL|macro|MAX_SECTORS_PER_UNIT
mdefine_line|#define MAX_SECTORS_PER_UNIT 32
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __MTD_NFTL_H__ */
eof
