multiline_comment|/*&n; * $Id: nftl.h,v 1.16 2004/06/30 14:49:00 dbrown Exp $&n; *&n; * (C) 1999-2003 David Woodhouse &lt;dwmw2@infradead.org&gt;&n; */
macro_line|#ifndef __MTD_NFTL_H__
DECL|macro|__MTD_NFTL_H__
mdefine_line|#define __MTD_NFTL_H__
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/blktrans.h&gt;
macro_line|#include &lt;mtd/nftl-user.h&gt;
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
DECL|member|mbd
r_struct
id|mtd_blktrans_dev
id|mbd
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
DECL|member|oobinfo
r_struct
id|nand_oobinfo
id|oobinfo
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
mdefine_line|#define MAX_SECTORS_PER_UNIT 64
DECL|macro|NFTL_PARTN_BITS
mdefine_line|#define NFTL_PARTN_BITS 4
macro_line|#endif /* __MTD_NFTL_H__ */
eof
