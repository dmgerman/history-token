multiline_comment|/* zconf.h -- configuration of the zlib compression library&n; * Copyright (C) 1995-1998 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* @(#) $Id$ */
macro_line|#ifndef _ZCONF_H
DECL|macro|_ZCONF_H
mdefine_line|#define _ZCONF_H
multiline_comment|/* The memory requirements for deflate are (in bytes):&n;            (1 &lt;&lt; (windowBits+2)) +  (1 &lt;&lt; (memLevel+9))&n; that is: 128K for windowBits=15  +  128K for memLevel = 8  (default values)&n; plus a few kilobytes for small objects. For example, if you want to reduce&n; the default memory requirements from 256K to 128K, compile with&n;     make CFLAGS=&quot;-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7&quot;&n; Of course this will generally degrade compression (there&squot;s no free lunch).&n;&n;   The memory requirements for inflate are (in bytes) 1 &lt;&lt; windowBits&n; that is, 32K for windowBits=15 (default value) plus a few kilobytes&n; for small objects.&n;*/
multiline_comment|/* Maximum value for memLevel in deflateInit2 */
macro_line|#ifndef MAX_MEM_LEVEL
DECL|macro|MAX_MEM_LEVEL
macro_line|#  define MAX_MEM_LEVEL 9
macro_line|#endif
multiline_comment|/* Maximum value for windowBits in deflateInit2 and inflateInit2.&n; * WARNING: reducing MAX_WBITS makes minigzip unable to extract .gz files&n; * created by gzip. (Files created by minigzip can still be extracted by&n; * gzip.)&n; */
macro_line|#ifndef MAX_WBITS
DECL|macro|MAX_WBITS
macro_line|#  define MAX_WBITS   15 /* 32K LZ77 window */
macro_line|#endif
multiline_comment|/* Type declarations */
DECL|typedef|Byte
r_typedef
r_int
r_char
id|Byte
suffix:semicolon
multiline_comment|/* 8 bits */
DECL|typedef|uInt
r_typedef
r_int
r_int
id|uInt
suffix:semicolon
multiline_comment|/* 16 bits or more */
DECL|typedef|uLong
r_typedef
r_int
r_int
id|uLong
suffix:semicolon
multiline_comment|/* 32 bits or more */
DECL|typedef|voidp
r_typedef
r_void
op_star
id|voidp
suffix:semicolon
macro_line|#endif /* _ZCONF_H */
eof
