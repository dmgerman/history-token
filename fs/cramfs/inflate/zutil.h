multiline_comment|/* zutil.h -- internal interface and configuration of the compression library&n; * Copyright (C) 1995-1998 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h&n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
multiline_comment|/* @(#) $Id: zutil.h,v 1.1 2000/01/01 03:32:23 davem Exp $ */
macro_line|#ifndef _Z_UTIL_H
DECL|macro|_Z_UTIL_H
mdefine_line|#define _Z_UTIL_H
macro_line|#include &quot;zlib.h&quot;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifndef local
DECL|macro|local
macro_line|#  define local static
macro_line|#endif
multiline_comment|/* compile with -Dlocal if your debugger can&squot;t find static symbols */
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|uchf
r_typedef
id|uch
id|FAR
id|uchf
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
suffix:semicolon
DECL|typedef|ushf
r_typedef
id|ush
id|FAR
id|ushf
suffix:semicolon
DECL|typedef|ulg
r_typedef
r_int
r_int
id|ulg
suffix:semicolon
multiline_comment|/* common constants */
macro_line|#ifndef DEF_WBITS
DECL|macro|DEF_WBITS
macro_line|#  define DEF_WBITS MAX_WBITS
macro_line|#endif
multiline_comment|/* default windowBits for decompression. MAX_WBITS is for compression only */
macro_line|#if MAX_MEM_LEVEL &gt;= 8
DECL|macro|DEF_MEM_LEVEL
macro_line|#  define DEF_MEM_LEVEL 8
macro_line|#else
DECL|macro|DEF_MEM_LEVEL
macro_line|#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
macro_line|#endif
multiline_comment|/* default memLevel */
DECL|macro|STORED_BLOCK
mdefine_line|#define STORED_BLOCK 0
DECL|macro|STATIC_TREES
mdefine_line|#define STATIC_TREES 1
DECL|macro|DYN_TREES
mdefine_line|#define DYN_TREES    2
multiline_comment|/* The three kinds of block type */
DECL|macro|MIN_MATCH
mdefine_line|#define MIN_MATCH  3
DECL|macro|MAX_MATCH
mdefine_line|#define MAX_MATCH  258
multiline_comment|/* The minimum and maximum match lengths */
DECL|macro|PRESET_DICT
mdefine_line|#define PRESET_DICT 0x20 /* preset dictionary flag in zlib header */
multiline_comment|/* target dependencies */
multiline_comment|/* Common defaults */
macro_line|#ifndef OS_CODE
DECL|macro|OS_CODE
macro_line|#  define OS_CODE  0x03  /* assume Unix */
macro_line|#endif
multiline_comment|/* functions */
DECL|typedef|OF
r_typedef
id|uLong
(paren
id|ZEXPORT
op_star
id|check_func
)paren
id|OF
c_func
(paren
(paren
id|uLong
id|check
comma
r_const
id|Bytef
op_star
id|buf
comma
id|uInt
id|len
)paren
)paren
suffix:semicolon
macro_line|#endif /* _Z_UTIL_H */
eof
