multiline_comment|/* $Id: hysdn_pof.h,v 1.2 2000/11/13 22:51:47 kai Exp $&n;&n; * Linux driver for HYSDN cards, definitions used for handling pof-files.&n; * written by Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; *&n; * Copyright 1999  by Werner Cornelius (werner@titro.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/************************/
multiline_comment|/* POF specific defines */
multiline_comment|/************************/
DECL|macro|BOOT_BUF_SIZE
mdefine_line|#define BOOT_BUF_SIZE   0x1000&t;/* =4096, maybe moved to other h file */
DECL|macro|CRYPT_FEEDTERM
mdefine_line|#define CRYPT_FEEDTERM  0x8142
DECL|macro|CRYPT_STARTTERM
mdefine_line|#define CRYPT_STARTTERM 0x81a5
multiline_comment|/*  max. timeout time in seconds&n;&t;&t;&t;&t;     *  from end of booting to POF is ready&n;&t;&t;&t;&t;     */
DECL|macro|POF_READY_TIME_OUT_SEC
mdefine_line|#define POF_READY_TIME_OUT_SEC  10
multiline_comment|/**********************************/
multiline_comment|/* defines for 1.stage boot image */
multiline_comment|/**********************************/
multiline_comment|/*  the POF file record containing the boot loader image&n; *  has 2 pages a 16KB:&n; *  1. page contains the high 16-bit part of the 32-bit E1 words&n; *  2. page contains the low  16-bit part of the 32-bit E1 words&n; *&n; *  In each 16KB page we assume the start of the boot loader code&n; *  in the highest 2KB part (at offset 0x3800);&n; *  the rest (0x0000..0x37FF) is assumed to contain 0 bytes.&n; */
DECL|macro|POF_BOOT_LOADER_PAGE_SIZE
mdefine_line|#define POF_BOOT_LOADER_PAGE_SIZE   0x4000&t;/* =16384U */
DECL|macro|POF_BOOT_LOADER_TOTAL_SIZE
mdefine_line|#define POF_BOOT_LOADER_TOTAL_SIZE  (2U*POF_BOOT_LOADER_PAGE_SIZE)
DECL|macro|POF_BOOT_LOADER_CODE_SIZE
mdefine_line|#define POF_BOOT_LOADER_CODE_SIZE   0x0800&t;/* =2KB =2048U */
multiline_comment|/* offset in boot page, where loader code may start */
multiline_comment|/* =0x3800= 14336U */
DECL|macro|POF_BOOT_LOADER_OFF_IN_PAGE
mdefine_line|#define POF_BOOT_LOADER_OFF_IN_PAGE (POF_BOOT_LOADER_PAGE_SIZE-POF_BOOT_LOADER_CODE_SIZE)
multiline_comment|/*--------------------------------------POF file record structs------------*/
DECL|struct|PofFileHdr_tag
r_typedef
r_struct
id|PofFileHdr_tag
(brace
multiline_comment|/* Pof file header */
DECL|member|Magic
multiline_comment|/*00 */
id|ulong
id|Magic
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|N_PofRecs
multiline_comment|/*04 */
id|ulong
id|N_PofRecs
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*08 */
DECL|typedef|tPofFileHdr
)brace
id|tPofFileHdr
suffix:semicolon
DECL|struct|PofRecHdr_tag
r_typedef
r_struct
id|PofRecHdr_tag
(brace
multiline_comment|/* Pof record header */
DECL|member|PofRecId
multiline_comment|/*00 */
id|word
id|PofRecId
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|PofRecDataLen
multiline_comment|/*02 */
id|ulong
id|PofRecDataLen
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*06 */
DECL|typedef|tPofRecHdr
)brace
id|tPofRecHdr
suffix:semicolon
DECL|struct|PofTimeStamp_tag
r_typedef
r_struct
id|PofTimeStamp_tag
(brace
DECL|member|UnixTime
multiline_comment|/*00 */
id|ulong
id|UnixTime
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|DateTimeText
multiline_comment|/*04 */
id|uchar
id|DateTimeText
(braket
l_int|0x28
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* =40 */
multiline_comment|/*2C */
DECL|typedef|tPofTimeStamp
)brace
id|tPofTimeStamp
suffix:semicolon
multiline_comment|/* tPofFileHdr.Magic value: */
DECL|macro|TAGFILEMAGIC
mdefine_line|#define TAGFILEMAGIC 0x464F501AUL
multiline_comment|/* tPofRecHdr.PofRecId values: */
DECL|macro|TAG_ABSDATA
mdefine_line|#define TAG_ABSDATA  0x1000&t;/* abs. data */
DECL|macro|TAG_BOOTDTA
mdefine_line|#define TAG_BOOTDTA  0x1001&t;/* boot data */
DECL|macro|TAG_COMMENT
mdefine_line|#define TAG_COMMENT  0x0020
DECL|macro|TAG_SYSCALL
mdefine_line|#define TAG_SYSCALL  0x0021
DECL|macro|TAG_FLOWCTRL
mdefine_line|#define TAG_FLOWCTRL 0x0022
DECL|macro|TAG_TIMESTMP
mdefine_line|#define TAG_TIMESTMP 0x0010&t;/* date/time stamp of version */
DECL|macro|TAG_CABSDATA
mdefine_line|#define TAG_CABSDATA 0x1100&t;/* crypted abs. data */
DECL|macro|TAG_CBOOTDTA
mdefine_line|#define TAG_CBOOTDTA 0x1101&t;/* crypted boot data */
eof
