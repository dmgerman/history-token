multiline_comment|/*&n; *&t;inftl.h -- defines to support the Inverse NAND Flash Translation Layer&n; *&n; *&t;(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)&n; *&n; *&t;$Id: inftl.h,v 1.6 2004/06/30 14:49:00 dbrown Exp $&n; */
macro_line|#ifndef __MTD_INFTL_H__
DECL|macro|__MTD_INFTL_H__
mdefine_line|#define __MTD_INFTL_H__
macro_line|#ifndef __KERNEL__
macro_line|#error This is a kernel header. Perhaps include nftl-user.h instead?
macro_line|#endif
macro_line|#include &lt;linux/mtd/blktrans.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/nftl.h&gt;
macro_line|#include &lt;mtd/inftl-user.h&gt;
macro_line|#ifndef INFTL_MAJOR
DECL|macro|INFTL_MAJOR
mdefine_line|#define INFTL_MAJOR 94
macro_line|#endif
DECL|macro|INFTL_PARTN_BITS
mdefine_line|#define INFTL_PARTN_BITS 4
macro_line|#ifdef __KERNEL__
DECL|struct|INFTLrecord
r_struct
id|INFTLrecord
(brace
DECL|member|mbd
r_struct
id|mtd_blktrans_dev
id|mbd
suffix:semicolon
DECL|member|MediaUnit
id|__u16
id|MediaUnit
suffix:semicolon
DECL|member|EraseSize
id|__u32
id|EraseSize
suffix:semicolon
DECL|member|MediaHdr
r_struct
id|INFTLMediaHeader
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
DECL|member|firstEUN
id|__u16
id|firstEUN
suffix:semicolon
DECL|member|lastEUN
id|__u16
id|lastEUN
suffix:semicolon
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
DECL|member|PUtable
id|__u16
op_star
id|PUtable
suffix:semicolon
multiline_comment|/* Physical Unit Table  */
DECL|member|VUtable
id|__u16
op_star
id|VUtable
suffix:semicolon
multiline_comment|/* Virtual Unit Table */
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
id|INFTL_mount
c_func
(paren
r_struct
id|INFTLrecord
op_star
id|s
)paren
suffix:semicolon
r_int
id|INFTL_formatblock
c_func
(paren
r_struct
id|INFTLrecord
op_star
id|s
comma
r_int
id|block
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __MTD_INFTL_H__ */
eof
