macro_line|#ifndef _ZFTAPE_COMPRESS_H
DECL|macro|_ZFTAPE_COMPRESS_H
mdefine_line|#define _ZFTAPE_COMPRESS_H
multiline_comment|/*&n; *      Copyright (c) 1994-1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or&n; modify it under the terms of the GNU General Public License as&n; published by the Free Software Foundation; either version 2, or (at&n; your option) any later version.&n; &n; This program is distributed in the hope that it will be useful, but&n; WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; General Public License for more details.&n; &n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,&n; USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/compressor/zftape-compress.h,v $&n; * $Revision: 1.1 $&n; * $Date: 1997/10/05 19:12:32 $&n; *&n; * This file contains macros and definitions for zftape&squot;s&n; * builtin compression code.&n; *&n; */
macro_line|#include &quot;../zftape/zftape-buffers.h&quot;
macro_line|#include &quot;../zftape/zftape-vtbl.h&quot;
macro_line|#include &quot;../compressor/lzrw3.h&quot;
multiline_comment|/* CMPR_WRK_MEM_SIZE gives the size of the compression wrk_mem */
multiline_comment|/* I got these out of lzrw3.c */
DECL|macro|U
mdefine_line|#define U(X)            ((__u32) X)
DECL|macro|SIZE_P_BYTE
mdefine_line|#define SIZE_P_BYTE     (U(sizeof(__u8 *)))
DECL|macro|ALIGNMENT_FUDGE
mdefine_line|#define ALIGNMENT_FUDGE (U(16))
DECL|macro|CMPR_WRK_MEM_SIZE
mdefine_line|#define CMPR_WRK_MEM_SIZE (U(4096)*(SIZE_P_BYTE) + ALIGNMENT_FUDGE)
multiline_comment|/* the maximum number of bytes the size of the &quot;compressed&quot; data can&n; * exceed the uncompressed data. As it is quite useless to compress&n; * data twice it is sometimes the case that it is more efficient to&n; * copy a block of data but to feed it to the &quot;compression&quot;&n; * algorithm. In this case there are some flag bytes or the like&n; * proceding the &quot;compressed&quot; data.  THAT MUST NOT BE THE CASE for the&n; * algorithm we use for this driver. Instead, the high bit 15 of&n; * compressed_size:&n; *&n; * compressed_size = ftape_compress()&n; *&n; * must be set in such a case.&n; *&n; * Nevertheless, it might also be as for lzrw3 that there is an&n; * &quot;intermediate&quot; overrun that exceeds the amount of the compressed&n; * data that is actually produced. During the algorithm we need in the&n; * worst case MAX_CMP_GROUP bytes more than the input-size.&n; */
DECL|macro|MAX_CMP_GROUP
mdefine_line|#define MAX_CMP_GROUP (2+16*2) /* from lzrw3.c */
DECL|macro|CMPR_OVERRUN
mdefine_line|#define CMPR_OVERRUN      MAX_CMP_GROUP /* during compression */
multiline_comment|/****************************************************/
DECL|macro|CMPR_BUFFER_SIZE
mdefine_line|#define     CMPR_BUFFER_SIZE (MAX_BLOCK_SIZE + CMPR_OVERRUN)
multiline_comment|/* the compression map stores the byte offset compressed blocks within&n; * the current volume for catridges with format code 2,3 and 5&n; * (and old versions of zftape) and the offset measured in kilobytes for&n; * format code 4 and 6. This gives us a possible max. size of a &n; * compressed volume of 1024*4GIG which should be enough.&n; */
DECL|typedef|CmprMap
r_typedef
id|__u32
id|CmprMap
suffix:semicolon
multiline_comment|/* globals &n; */
multiline_comment|/* exported functions&n; */
macro_line|#endif /* _ZFTAPE_COMPRESS_H */
eof
