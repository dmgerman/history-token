multiline_comment|/* zutil.h -- internal interface and configuration of the compression library&n; * Copyright (C) 1995-1998 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h&n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
multiline_comment|/* @(#) $Id: zutil.h,v 1.1 2000/01/01 03:32:23 davem Exp $ */
macro_line|#ifndef _Z_UTIL_H
DECL|macro|_Z_UTIL_H
mdefine_line|#define _Z_UTIL_H
macro_line|#include &lt;linux/zlib.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
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
DECL|typedef|check_func
r_typedef
id|uLong
(paren
op_star
id|check_func
)paren
(paren
id|uLong
id|check
comma
r_const
id|Byte
op_star
id|buf
comma
id|uInt
id|len
)paren
suffix:semicolon
multiline_comment|/* checksum functions */
DECL|macro|BASE
mdefine_line|#define BASE 65521L /* largest prime smaller than 65536 */
DECL|macro|NMAX
mdefine_line|#define NMAX 5552
multiline_comment|/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) &lt;= 2^32-1 */
DECL|macro|DO1
mdefine_line|#define DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
DECL|macro|DO2
mdefine_line|#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
DECL|macro|DO4
mdefine_line|#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
DECL|macro|DO8
mdefine_line|#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
DECL|macro|DO16
mdefine_line|#define DO16(buf)   DO8(buf,0); DO8(buf,8);
multiline_comment|/* ========================================================================= */
multiline_comment|/*&n;     Update a running Adler-32 checksum with the bytes buf[0..len-1] and&n;   return the updated checksum. If buf is NULL, this function returns&n;   the required initial value for the checksum.&n;   An Adler-32 checksum is almost as reliable as a CRC32 but can be computed&n;   much faster. Usage example:&n;&n;     uLong adler = adler32(0L, Z_NULL, 0);&n;&n;     while (read_buffer(buffer, length) != EOF) {&n;       adler = adler32(adler, buffer, length);&n;     }&n;     if (adler != original_adler) error();&n;*/
DECL|function|zlib_adler32
r_static
r_inline
id|uLong
id|zlib_adler32
c_func
(paren
id|uLong
id|adler
comma
r_const
id|Byte
op_star
id|buf
comma
id|uInt
id|len
)paren
(brace
r_int
r_int
id|s1
op_assign
id|adler
op_amp
l_int|0xffff
suffix:semicolon
r_int
r_int
id|s2
op_assign
(paren
id|adler
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_int
id|k
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
id|Z_NULL
)paren
r_return
l_int|1L
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
id|k
op_assign
id|len
OL
id|NMAX
ques
c_cond
id|len
suffix:colon
id|NMAX
suffix:semicolon
id|len
op_sub_assign
id|k
suffix:semicolon
r_while
c_loop
(paren
id|k
op_ge
l_int|16
)paren
(brace
id|DO16
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|16
suffix:semicolon
id|k
op_sub_assign
l_int|16
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
op_ne
l_int|0
)paren
r_do
(brace
id|s1
op_add_assign
op_star
id|buf
op_increment
suffix:semicolon
id|s2
op_add_assign
id|s1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|k
)paren
suffix:semicolon
id|s1
op_mod_assign
id|BASE
suffix:semicolon
id|s2
op_mod_assign
id|BASE
suffix:semicolon
)brace
r_return
(paren
id|s2
op_lshift
l_int|16
)paren
op_or
id|s1
suffix:semicolon
)brace
macro_line|#endif /* _Z_UTIL_H */
eof
