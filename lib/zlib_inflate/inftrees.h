multiline_comment|/* inftrees.h -- header to use inftrees.c&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
multiline_comment|/* Huffman code lookup table entry--this entry is four bytes for machines&n;   that have 16-bit pointers (e.g. PC&squot;s in the small or medium model). */
macro_line|#ifndef _INFTREES_H
DECL|macro|_INFTREES_H
mdefine_line|#define _INFTREES_H
DECL|typedef|inflate_huft
r_typedef
r_struct
id|inflate_huft_s
id|FAR
id|inflate_huft
suffix:semicolon
DECL|struct|inflate_huft_s
r_struct
id|inflate_huft_s
(brace
r_union
(brace
r_struct
(brace
DECL|member|Exop
id|Byte
id|Exop
suffix:semicolon
multiline_comment|/* number of extra bits or operation */
DECL|member|Bits
id|Byte
id|Bits
suffix:semicolon
multiline_comment|/* number of bits in this code or subcode */
DECL|member|what
)brace
id|what
suffix:semicolon
DECL|member|pad
id|uInt
id|pad
suffix:semicolon
multiline_comment|/* pad structure to a power of 2 (4 bytes for */
DECL|member|word
)brace
id|word
suffix:semicolon
multiline_comment|/*  16-bit, 8 bytes for 32-bit int&squot;s) */
DECL|member|base
id|uInt
id|base
suffix:semicolon
multiline_comment|/* literal, length base, distance base,&n;                           or table offset */
)brace
suffix:semicolon
multiline_comment|/* Maximum size of dynamic tree.  The maximum found in a long but non-&n;   exhaustive search was 1004 huft structures (850 for length/literals&n;   and 154 for distances, the latter actually the result of an&n;   exhaustive search).  The actual maximum is not known, but the&n;   value below is more than safe. */
DECL|macro|MANY
mdefine_line|#define MANY 1440
r_extern
r_int
id|zlib_inflate_trees_bits
id|OF
c_func
(paren
(paren
id|uIntf
op_star
comma
multiline_comment|/* 19 code lengths */
id|uIntf
op_star
comma
multiline_comment|/* bits tree desired/actual depth */
id|inflate_huft
op_star
id|FAR
op_star
comma
multiline_comment|/* bits tree result */
id|inflate_huft
op_star
comma
multiline_comment|/* space for trees */
id|z_streamp
)paren
)paren
suffix:semicolon
multiline_comment|/* for messages */
r_extern
r_int
id|zlib_inflate_trees_dynamic
id|OF
c_func
(paren
(paren
id|uInt
comma
multiline_comment|/* number of literal/length codes */
id|uInt
comma
multiline_comment|/* number of distance codes */
id|uIntf
op_star
comma
multiline_comment|/* that many (total) code lengths */
id|uIntf
op_star
comma
multiline_comment|/* literal desired/actual bit depth */
id|uIntf
op_star
comma
multiline_comment|/* distance desired/actual bit depth */
id|inflate_huft
op_star
id|FAR
op_star
comma
multiline_comment|/* literal/length tree result */
id|inflate_huft
op_star
id|FAR
op_star
comma
multiline_comment|/* distance tree result */
id|inflate_huft
op_star
comma
multiline_comment|/* space for trees */
id|z_streamp
)paren
)paren
suffix:semicolon
multiline_comment|/* for messages */
r_extern
r_int
id|zlib_inflate_trees_fixed
id|OF
c_func
(paren
(paren
id|uIntf
op_star
comma
multiline_comment|/* literal desired/actual bit depth */
id|uIntf
op_star
comma
multiline_comment|/* distance desired/actual bit depth */
id|inflate_huft
op_star
id|FAR
op_star
comma
multiline_comment|/* literal/length tree result */
id|inflate_huft
op_star
id|FAR
op_star
comma
multiline_comment|/* distance tree result */
id|z_streamp
)paren
)paren
suffix:semicolon
multiline_comment|/* for memory allocation */
macro_line|#endif /* _INFTREES_H */
eof
