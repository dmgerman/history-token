multiline_comment|/*&t;$Id: zlib.h,v 1.2 1997/12/23 10:47:44 paulus Exp $&t;*/
multiline_comment|/*&n; * This file is derived from zlib.h and zconf.h from the zlib-1.0.4&n; * distribution by Jean-loup Gailly and Mark Adler, with some additions&n; * by Paul Mackerras to aid in implementing Deflate compression and&n; * decompression for PPP packets.&n; */
multiline_comment|/*&n; *  ==FILEVERSION 971127==&n; *&n; * This marker is used by the Linux installation script to determine&n; * whether an up-to-date version of this file is already installed.&n; */
multiline_comment|/* +++ zlib.h */
multiline_comment|/* zlib.h -- interface of the &squot;zlib&squot; general purpose compression library&n;  version 1.0.4, Jul 24th, 1996.&n;&n;  Copyright (C) 1995-1996 Jean-loup Gailly and Mark Adler&n;&n;  This software is provided &squot;as-is&squot;, without any express or implied&n;  warranty.  In no event will the authors be held liable for any damages&n;  arising from the use of this software.&n;&n;  Permission is granted to anyone to use this software for any purpose,&n;  including commercial applications, and to alter it and redistribute it&n;  freely, subject to the following restrictions:&n;&n;  1. The origin of this software must not be misrepresented; you must not&n;     claim that you wrote the original software. If you use this software&n;     in a product, an acknowledgment in the product documentation would be&n;     appreciated but is not required.&n;  2. Altered source versions must be plainly marked as such, and must not be&n;     misrepresented as being the original software.&n;  3. This notice may not be removed or altered from any source distribution.&n;&n;  Jean-loup Gailly        Mark Adler&n;  gzip@prep.ai.mit.edu    madler@alumni.caltech.edu&n;&n;&n;  The data format used by the zlib library is described by RFCs (Request for&n;  Comments) 1950 to 1952 in the files ftp://ds.internic.net/rfc/rfc1950.txt&n;  (zlib format), rfc1951.txt (deflate format) and rfc1952.txt (gzip format).&n;*/
macro_line|#ifndef _ZLIB_H
DECL|macro|_ZLIB_H
mdefine_line|#define _ZLIB_H
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/* +++ zconf.h */
multiline_comment|/* zconf.h -- configuration of the zlib compression library&n; * Copyright (C) 1995-1996 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* From: zconf.h,v 1.20 1996/07/02 15:09:28 me Exp $ */
macro_line|#ifndef _ZCONF_H
DECL|macro|_ZCONF_H
mdefine_line|#define _ZCONF_H
multiline_comment|/*&n; * If you *really* need a unique prefix for all types and library functions,&n; * compile with -DZ_PREFIX. The &quot;standard&quot; zlib should be compiled without it.&n; */
macro_line|#ifdef Z_PREFIX
DECL|macro|deflateInit_
macro_line|#  define deflateInit_&t;z_deflateInit_
DECL|macro|deflate
macro_line|#  define deflate&t;z_deflate
DECL|macro|deflateEnd
macro_line|#  define deflateEnd&t;z_deflateEnd
DECL|macro|inflateInit_
macro_line|#  define inflateInit_ &t;z_inflateInit_
DECL|macro|inflate
macro_line|#  define inflate&t;z_inflate
DECL|macro|inflateEnd
macro_line|#  define inflateEnd&t;z_inflateEnd
DECL|macro|deflateInit2_
macro_line|#  define deflateInit2_&t;z_deflateInit2_
DECL|macro|deflateSetDictionary
macro_line|#  define deflateSetDictionary z_deflateSetDictionary
DECL|macro|deflateCopy
macro_line|#  define deflateCopy&t;z_deflateCopy
DECL|macro|deflateReset
macro_line|#  define deflateReset&t;z_deflateReset
DECL|macro|deflateParams
macro_line|#  define deflateParams&t;z_deflateParams
DECL|macro|inflateInit2_
macro_line|#  define inflateInit2_&t;z_inflateInit2_
DECL|macro|inflateSetDictionary
macro_line|#  define inflateSetDictionary z_inflateSetDictionary
DECL|macro|inflateSync
macro_line|#  define inflateSync&t;z_inflateSync
DECL|macro|inflateReset
macro_line|#  define inflateReset&t;z_inflateReset
DECL|macro|compress
macro_line|#  define compress&t;z_compress
DECL|macro|uncompress
macro_line|#  define uncompress&t;z_uncompress
DECL|macro|adler32
macro_line|#  define adler32&t;z_adler32
DECL|macro|crc32
macro_line|#  define crc32&t;&t;z_crc32
DECL|macro|get_crc_table
macro_line|#  define get_crc_table z_get_crc_table
DECL|macro|Byte
macro_line|#  define Byte&t;&t;z_Byte
DECL|macro|uInt
macro_line|#  define uInt&t;&t;z_uInt
DECL|macro|uLong
macro_line|#  define uLong&t;&t;z_uLong
DECL|macro|Bytef
macro_line|#  define Bytef&t;        z_Bytef
DECL|macro|charf
macro_line|#  define charf&t;&t;z_charf
DECL|macro|intf
macro_line|#  define intf&t;&t;z_intf
DECL|macro|uIntf
macro_line|#  define uIntf&t;&t;z_uIntf
DECL|macro|uLongf
macro_line|#  define uLongf&t;z_uLongf
DECL|macro|voidpf
macro_line|#  define voidpf&t;z_voidpf
DECL|macro|voidp
macro_line|#  define voidp&t;&t;z_voidp
macro_line|#endif
macro_line|#if (defined(_WIN32) || defined(__WIN32__)) &amp;&amp; !defined(WIN32)
DECL|macro|WIN32
macro_line|#  define WIN32
macro_line|#endif
macro_line|#if defined(__GNUC__) || defined(WIN32) || defined(__386__) || defined(i386)
macro_line|#  ifndef __32BIT__
DECL|macro|__32BIT__
macro_line|#    define __32BIT__
macro_line|#  endif
macro_line|#endif
macro_line|#if defined(__MSDOS__) &amp;&amp; !defined(MSDOS)
DECL|macro|MSDOS
macro_line|#  define MSDOS
macro_line|#endif
multiline_comment|/*&n; * Compile with -DMAXSEG_64K if the alloc function cannot allocate more&n; * than 64k bytes at a time (needed on systems with 16-bit int).&n; */
macro_line|#if defined(MSDOS) &amp;&amp; !defined(__32BIT__)
DECL|macro|MAXSEG_64K
macro_line|#  define MAXSEG_64K
macro_line|#endif
macro_line|#ifdef MSDOS
DECL|macro|UNALIGNED_OK
macro_line|#  define UNALIGNED_OK
macro_line|#endif
macro_line|#if (defined(MSDOS) || defined(_WINDOWS) || defined(WIN32))  &amp;&amp; !defined(STDC)
DECL|macro|STDC
macro_line|#  define STDC
macro_line|#endif
macro_line|#if (defined(__STDC__) || defined(__cplusplus)) &amp;&amp; !defined(STDC)
DECL|macro|STDC
macro_line|#  define STDC
macro_line|#endif
macro_line|#ifndef STDC
macro_line|#  ifndef const /* cannot use !defined(STDC) &amp;&amp; !defined(const) on Mac */
DECL|macro|const
macro_line|#    define const
macro_line|#  endif
macro_line|#endif
multiline_comment|/* Some Mac compilers merge all .h files incorrectly: */
macro_line|#if defined(__MWERKS__) || defined(applec) ||defined(THINK_C) ||defined(__SC__)
DECL|macro|NO_DUMMY_DECL
macro_line|#  define NO_DUMMY_DECL
macro_line|#endif
multiline_comment|/* Maximum value for memLevel in deflateInit2 */
macro_line|#ifndef MAX_MEM_LEVEL
macro_line|#  ifdef MAXSEG_64K
DECL|macro|MAX_MEM_LEVEL
macro_line|#    define MAX_MEM_LEVEL 8
macro_line|#  else
DECL|macro|MAX_MEM_LEVEL
macro_line|#    define MAX_MEM_LEVEL 9
macro_line|#  endif
macro_line|#endif
multiline_comment|/* Maximum value for windowBits in deflateInit2 and inflateInit2 */
macro_line|#ifndef MAX_WBITS
DECL|macro|MAX_WBITS
macro_line|#  define MAX_WBITS   15 /* 32K LZ77 window */
macro_line|#endif
multiline_comment|/* The memory requirements for deflate are (in bytes):&n;            1 &lt;&lt; (windowBits+2)   +  1 &lt;&lt; (memLevel+9)&n; that is: 128K for windowBits=15  +  128K for memLevel = 8  (default values)&n; plus a few kilobytes for small objects. For example, if you want to reduce&n; the default memory requirements from 256K to 128K, compile with&n;     make CFLAGS=&quot;-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7&quot;&n; Of course this will generally degrade compression (there&squot;s no free lunch).&n;&n;   The memory requirements for inflate are (in bytes) 1 &lt;&lt; windowBits&n; that is, 32K for windowBits=15 (default value) plus a few kilobytes&n; for small objects.&n;*/
multiline_comment|/* Type declarations */
macro_line|#ifndef OF /* function prototypes */
macro_line|#  ifdef STDC
DECL|macro|OF
macro_line|#    define OF(args)  args
macro_line|#  else
DECL|macro|OF
macro_line|#    define OF(args)  ()
macro_line|#  endif
macro_line|#endif
multiline_comment|/* The following definitions for FAR are needed only for MSDOS mixed&n; * model programming (small or medium model with some far allocations).&n; * This was tested only with MSC; for other MSDOS compilers you may have&n; * to define NO_MEMCPY in zutil.h.  If you don&squot;t need the mixed model,&n; * just define FAR to be empty.&n; */
macro_line|#if (defined(M_I86SM) || defined(M_I86MM)) &amp;&amp; !defined(__32BIT__)
multiline_comment|/* MSC small or medium model */
DECL|macro|SMALL_MEDIUM
macro_line|#  define SMALL_MEDIUM
macro_line|#  ifdef _MSC_VER
DECL|macro|FAR
macro_line|#    define FAR __far
macro_line|#  else
DECL|macro|FAR
macro_line|#    define FAR far
macro_line|#  endif
macro_line|#endif
macro_line|#if defined(__BORLANDC__) &amp;&amp; (defined(__SMALL__) || defined(__MEDIUM__))
macro_line|#  ifndef __32BIT__
DECL|macro|SMALL_MEDIUM
macro_line|#    define SMALL_MEDIUM
DECL|macro|FAR
macro_line|#    define FAR __far
macro_line|#  endif
macro_line|#endif
macro_line|#ifndef FAR
DECL|macro|FAR
macro_line|#   define FAR
macro_line|#endif
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
macro_line|#if defined(__BORLANDC__) &amp;&amp; defined(SMALL_MEDIUM)
multiline_comment|/* Borland C/C++ ignores FAR inside typedef */
DECL|macro|Bytef
macro_line|#  define Bytef Byte FAR
macro_line|#else
DECL|typedef|Bytef
r_typedef
id|Byte
id|FAR
id|Bytef
suffix:semicolon
macro_line|#endif
DECL|typedef|charf
r_typedef
r_char
id|FAR
id|charf
suffix:semicolon
DECL|typedef|intf
r_typedef
r_int
id|FAR
id|intf
suffix:semicolon
DECL|typedef|uIntf
r_typedef
id|uInt
id|FAR
id|uIntf
suffix:semicolon
DECL|typedef|uLongf
r_typedef
id|uLong
id|FAR
id|uLongf
suffix:semicolon
macro_line|#ifdef STDC
DECL|typedef|voidpf
r_typedef
r_void
id|FAR
op_star
id|voidpf
suffix:semicolon
DECL|typedef|voidp
r_typedef
r_void
op_star
id|voidp
suffix:semicolon
macro_line|#else
DECL|typedef|voidpf
r_typedef
id|Byte
id|FAR
op_star
id|voidpf
suffix:semicolon
DECL|typedef|voidp
r_typedef
id|Byte
op_star
id|voidp
suffix:semicolon
macro_line|#endif
multiline_comment|/* Compile with -DZLIB_DLL for Windows DLL support */
macro_line|#if (defined(_WINDOWS) || defined(WINDOWS)) &amp;&amp; defined(ZLIB_DLL)
macro_line|#  include &lt;windows.h&gt;
DECL|macro|EXPORT
macro_line|#  define EXPORT  WINAPI
macro_line|#else
DECL|macro|EXPORT
macro_line|#  define EXPORT
macro_line|#endif
macro_line|#endif /* _ZCONF_H */
multiline_comment|/* --- zconf.h */
DECL|macro|ZLIB_VERSION
mdefine_line|#define ZLIB_VERSION &quot;1.0.4P&quot;
multiline_comment|/* &n;     The &squot;zlib&squot; compression library provides in-memory compression and&n;  decompression functions, including integrity checks of the uncompressed&n;  data.  This version of the library supports only one compression method&n;  (deflation) but other algorithms may be added later and will have the same&n;  stream interface.&n;&n;     For compression the application must provide the output buffer and&n;  may optionally provide the input buffer for optimization. For decompression,&n;  the application must provide the input buffer and may optionally provide&n;  the output buffer for optimization.&n;&n;     Compression can be done in a single step if the buffers are large&n;  enough (for example if an input file is mmap&squot;ed), or can be done by&n;  repeated calls of the compression function.  In the latter case, the&n;  application must provide more input and/or consume the output&n;  (providing more output space) before each call.&n;&n;     The library does not install any signal handler. It is recommended to&n;  add at least a handler for SIGSEGV when decompressing; the library checks&n;  the consistency of the input data whenever possible but may go nuts&n;  for some forms of corrupted input.&n;*/
DECL|typedef|alloc_func
r_typedef
id|voidpf
(paren
op_star
id|alloc_func
)paren
id|OF
c_func
(paren
(paren
id|voidpf
id|opaque
comma
id|uInt
id|items
comma
id|uInt
id|size
)paren
)paren
suffix:semicolon
DECL|typedef|free_func
r_typedef
r_void
(paren
op_star
id|free_func
)paren
id|OF
c_func
(paren
(paren
id|voidpf
id|opaque
comma
id|voidpf
id|address
)paren
)paren
suffix:semicolon
r_struct
id|internal_state
suffix:semicolon
DECL|struct|z_stream_s
r_typedef
r_struct
id|z_stream_s
(brace
DECL|member|next_in
id|Bytef
op_star
id|next_in
suffix:semicolon
multiline_comment|/* next input byte */
DECL|member|avail_in
id|uInt
id|avail_in
suffix:semicolon
multiline_comment|/* number of bytes available at next_in */
DECL|member|total_in
id|uLong
id|total_in
suffix:semicolon
multiline_comment|/* total nb of input bytes read so far */
DECL|member|next_out
id|Bytef
op_star
id|next_out
suffix:semicolon
multiline_comment|/* next output byte should be put there */
DECL|member|avail_out
id|uInt
id|avail_out
suffix:semicolon
multiline_comment|/* remaining free space at next_out */
DECL|member|total_out
id|uLong
id|total_out
suffix:semicolon
multiline_comment|/* total nb of bytes output so far */
DECL|member|msg
r_char
op_star
id|msg
suffix:semicolon
multiline_comment|/* last error message, NULL if no error */
DECL|member|state
r_struct
id|internal_state
id|FAR
op_star
id|state
suffix:semicolon
multiline_comment|/* not visible by applications */
DECL|member|zalloc
id|alloc_func
id|zalloc
suffix:semicolon
multiline_comment|/* used to allocate the internal state */
DECL|member|zfree
id|free_func
id|zfree
suffix:semicolon
multiline_comment|/* used to free the internal state */
DECL|member|opaque
id|voidpf
id|opaque
suffix:semicolon
multiline_comment|/* private data object passed to zalloc and zfree */
DECL|member|data_type
r_int
id|data_type
suffix:semicolon
multiline_comment|/* best guess about the data type: ascii or binary */
DECL|member|adler
id|uLong
id|adler
suffix:semicolon
multiline_comment|/* adler32 value of the uncompressed data */
DECL|member|reserved
id|uLong
id|reserved
suffix:semicolon
multiline_comment|/* reserved for future use */
DECL|typedef|z_stream
)brace
id|z_stream
suffix:semicolon
DECL|typedef|z_streamp
r_typedef
id|z_stream
id|FAR
op_star
id|z_streamp
suffix:semicolon
multiline_comment|/*&n;   The application must update next_in and avail_in when avail_in has&n;   dropped to zero. It must update next_out and avail_out when avail_out&n;   has dropped to zero. The application must initialize zalloc, zfree and&n;   opaque before calling the init function. All other fields are set by the&n;   compression library and must not be updated by the application.&n;&n;   The opaque value provided by the application will be passed as the first&n;   parameter for calls of zalloc and zfree. This can be useful for custom&n;   memory management. The compression library attaches no meaning to the&n;   opaque value.&n;&n;   zalloc must return Z_NULL if there is not enough memory for the object.&n;   On 16-bit systems, the functions zalloc and zfree must be able to allocate&n;   exactly 65536 bytes, but will not be required to allocate more than this&n;   if the symbol MAXSEG_64K is defined (see zconf.h). WARNING: On MSDOS,&n;   pointers returned by zalloc for objects of exactly 65536 bytes *must*&n;   have their offset normalized to zero. The default allocation function&n;   provided by this library ensures this (see zutil.c). To reduce memory&n;   requirements and avoid any allocation of 64K objects, at the expense of&n;   compression ratio, compile the library with -DMAX_WBITS=14 (see zconf.h).&n;&n;   The fields total_in and total_out can be used for statistics or&n;   progress reports. After compression, total_in holds the total size of&n;   the uncompressed data and may be saved for use in the decompressor&n;   (particularly if the decompressor wants to decompress everything in&n;   a single step).&n;*/
multiline_comment|/* constants */
DECL|macro|Z_NO_FLUSH
mdefine_line|#define Z_NO_FLUSH      0
DECL|macro|Z_PARTIAL_FLUSH
mdefine_line|#define Z_PARTIAL_FLUSH 1
DECL|macro|Z_PACKET_FLUSH
mdefine_line|#define Z_PACKET_FLUSH&t;2
DECL|macro|Z_SYNC_FLUSH
mdefine_line|#define Z_SYNC_FLUSH    3
DECL|macro|Z_FULL_FLUSH
mdefine_line|#define Z_FULL_FLUSH    4
DECL|macro|Z_FINISH
mdefine_line|#define Z_FINISH        5
multiline_comment|/* Allowed flush values; see deflate() below for details */
DECL|macro|Z_OK
mdefine_line|#define Z_OK            0
DECL|macro|Z_STREAM_END
mdefine_line|#define Z_STREAM_END    1
DECL|macro|Z_NEED_DICT
mdefine_line|#define Z_NEED_DICT     2
DECL|macro|Z_ERRNO
mdefine_line|#define Z_ERRNO        (-1)
DECL|macro|Z_STREAM_ERROR
mdefine_line|#define Z_STREAM_ERROR (-2)
DECL|macro|Z_DATA_ERROR
mdefine_line|#define Z_DATA_ERROR   (-3)
DECL|macro|Z_MEM_ERROR
mdefine_line|#define Z_MEM_ERROR    (-4)
DECL|macro|Z_BUF_ERROR
mdefine_line|#define Z_BUF_ERROR    (-5)
DECL|macro|Z_VERSION_ERROR
mdefine_line|#define Z_VERSION_ERROR (-6)
multiline_comment|/* Return codes for the compression/decompression functions. Negative&n; * values are errors, positive values are used for special but normal events.&n; */
DECL|macro|Z_NO_COMPRESSION
mdefine_line|#define Z_NO_COMPRESSION         0
DECL|macro|Z_BEST_SPEED
mdefine_line|#define Z_BEST_SPEED             1
DECL|macro|Z_BEST_COMPRESSION
mdefine_line|#define Z_BEST_COMPRESSION       9
DECL|macro|Z_DEFAULT_COMPRESSION
mdefine_line|#define Z_DEFAULT_COMPRESSION  (-1)
multiline_comment|/* compression levels */
DECL|macro|Z_FILTERED
mdefine_line|#define Z_FILTERED            1
DECL|macro|Z_HUFFMAN_ONLY
mdefine_line|#define Z_HUFFMAN_ONLY        2
DECL|macro|Z_DEFAULT_STRATEGY
mdefine_line|#define Z_DEFAULT_STRATEGY    0
multiline_comment|/* compression strategy; see deflateInit2() below for details */
DECL|macro|Z_BINARY
mdefine_line|#define Z_BINARY   0
DECL|macro|Z_ASCII
mdefine_line|#define Z_ASCII    1
DECL|macro|Z_UNKNOWN
mdefine_line|#define Z_UNKNOWN  2
multiline_comment|/* Possible values of the data_type field */
DECL|macro|Z_DEFLATED
mdefine_line|#define Z_DEFLATED   8
multiline_comment|/* The deflate compression method (the only one supported in this version) */
DECL|macro|Z_NULL
mdefine_line|#define Z_NULL  0  /* for initializing zalloc, zfree, opaque */
DECL|macro|zlib_version
mdefine_line|#define zlib_version zlibVersion()
multiline_comment|/* for compatibility with versions &lt; 1.0.2 */
multiline_comment|/* basic functions */
r_extern
r_const
r_char
op_star
id|EXPORT
id|zlibVersion
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
multiline_comment|/* The application can compare zlibVersion and ZLIB_VERSION for consistency.&n;   If the first character differs, the library code actually used is&n;   not compatible with the zlib.h header file used by the application.&n;   This check is automatically made by deflateInit and inflateInit.&n; */
multiline_comment|/* &n;extern int EXPORT deflateInit OF((z_streamp strm, int level));&n;&n;     Initializes the internal stream state for compression. The fields&n;   zalloc, zfree and opaque must be initialized before by the caller.&n;   If zalloc and zfree are set to Z_NULL, deflateInit updates them to&n;   use default allocation functions.&n;&n;     The compression level must be Z_DEFAULT_COMPRESSION, or between 0 and 9:&n;   1 gives best speed, 9 gives best compression, 0 gives no compression at&n;   all (the input data is simply copied a block at a time).&n;   Z_DEFAULT_COMPRESSION requests a default compromise between speed and&n;   compression (currently equivalent to level 6).&n;&n;     deflateInit returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_STREAM_ERROR if level is not a valid compression level,&n;   Z_VERSION_ERROR if the zlib library version (zlib_version) is incompatible&n;   with the version assumed by the caller (ZLIB_VERSION).&n;   msg is set to null if there is no error message.  deflateInit does not&n;   perform any compression: this will be done by deflate().&n;*/
r_extern
r_int
id|EXPORT
id|deflate
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_int
id|flush
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;  Performs one or both of the following actions:&n;&n;  - Compress more input starting at next_in and update next_in and avail_in&n;    accordingly. If not all input can be processed (because there is not&n;    enough room in the output buffer), next_in and avail_in are updated and&n;    processing will resume at this point for the next call of deflate().&n;&n;  - Provide more output starting at next_out and update next_out and avail_out&n;    accordingly. This action is forced if the parameter flush is non zero.&n;    Forcing flush frequently degrades the compression ratio, so this parameter&n;    should be set only when necessary (in interactive applications).&n;    Some output may be provided even if flush is not set.&n;&n;  Before the call of deflate(), the application should ensure that at least&n;  one of the actions is possible, by providing more input and/or consuming&n;  more output, and updating avail_in or avail_out accordingly; avail_out&n;  should never be zero before the call. The application can consume the&n;  compressed output when it wants, for example when the output buffer is full&n;  (avail_out == 0), or after each call of deflate(). If deflate returns Z_OK&n;  and with zero avail_out, it must be called again after making room in the&n;  output buffer because there might be more output pending.&n;&n;    If the parameter flush is set to Z_PARTIAL_FLUSH, the current compression&n;  block is terminated and flushed to the output buffer so that the&n;  decompressor can get all input data available so far. For method 9, a future&n;  variant on method 8, the current block will be flushed but not terminated.&n;  Z_SYNC_FLUSH has the same effect as partial flush except that the compressed&n;  output is byte aligned (the compressor can clear its internal bit buffer)&n;  and the current block is always terminated; this can be useful if the&n;  compressor has to be restarted from scratch after an interruption (in which&n;  case the internal state of the compressor may be lost).&n;    If flush is set to Z_FULL_FLUSH, the compression block is terminated, a&n;  special marker is output and the compression dictionary is discarded; this&n;  is useful to allow the decompressor to synchronize if one compressed block&n;  has been damaged (see inflateSync below).  Flushing degrades compression and&n;  so should be used only when necessary.  Using Z_FULL_FLUSH too often can&n;  seriously degrade the compression. If deflate returns with avail_out == 0,&n;  this function must be called again with the same value of the flush&n;  parameter and more output space (updated avail_out), until the flush is&n;  complete (deflate returns with non-zero avail_out).&n;&n;    If the parameter flush is set to Z_PACKET_FLUSH, the compression&n;  block is terminated, and a zero-length stored block is output,&n;  omitting the length bytes (the effect of this is that the 3-bit type&n;  code 000 for a stored block is output, and the output is then&n;  byte-aligned).  This is designed for use at the end of a PPP packet.&n;&n;    If the parameter flush is set to Z_FINISH, pending input is processed,&n;  pending output is flushed and deflate returns with Z_STREAM_END if there&n;  was enough output space; if deflate returns with Z_OK, this function must be&n;  called again with Z_FINISH and more output space (updated avail_out) but no&n;  more input data, until it returns with Z_STREAM_END or an error. After&n;  deflate has returned Z_STREAM_END, the only possible operations on the&n;  stream are deflateReset or deflateEnd.&n;  &n;    Z_FINISH can be used immediately after deflateInit if all the compression&n;  is to be done in a single step. In this case, avail_out must be at least&n;  0.1% larger than avail_in plus 12 bytes.  If deflate does not return&n;  Z_STREAM_END, then it must be called again as described above.&n;&n;    deflate() may update data_type if it can make a good guess about&n;  the input data type (Z_ASCII or Z_BINARY). In doubt, the data is considered&n;  binary. This field is only for information purposes and does not affect&n;  the compression algorithm in any manner.&n;&n;    deflate() returns Z_OK if some progress has been made (more input&n;  processed or more output produced), Z_STREAM_END if all input has been&n;  consumed and all output has been produced (only when flush is set to&n;  Z_FINISH), Z_STREAM_ERROR if the stream state was inconsistent (for example&n;  if next_in or next_out was NULL), Z_BUF_ERROR if no progress is possible.&n;*/
r_extern
r_int
id|EXPORT
id|deflateEnd
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     All dynamically allocated data structures for this stream are freed.&n;   This function discards any unprocessed input and does not flush any&n;   pending output.&n;&n;     deflateEnd returns Z_OK if success, Z_STREAM_ERROR if the&n;   stream state was inconsistent, Z_DATA_ERROR if the stream was freed&n;   prematurely (some input or output was discarded). In the error case,&n;   msg may be set but then points to a static string (which must not be&n;   deallocated).&n;*/
multiline_comment|/* &n;extern int EXPORT inflateInit OF((z_streamp strm));&n;&n;     Initializes the internal stream state for decompression. The fields&n;   zalloc, zfree and opaque must be initialized before by the caller.  If&n;   zalloc and zfree are set to Z_NULL, inflateInit updates them to use default&n;   allocation functions.&n;&n;     inflateInit returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_VERSION_ERROR if the zlib library version is incompatible&n;   with the version assumed by the caller.  msg is set to null if there is no&n;   error message. inflateInit does not perform any decompression: this will be&n;   done by inflate().&n;*/
r_extern
r_int
id|EXPORT
id|inflate
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_int
id|flush
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;  Performs one or both of the following actions:&n;&n;  - Decompress more input starting at next_in and update next_in and avail_in&n;    accordingly. If not all input can be processed (because there is not&n;    enough room in the output buffer), next_in is updated and processing&n;    will resume at this point for the next call of inflate().&n;&n;  - Provide more output starting at next_out and update next_out and avail_out&n;    accordingly.  inflate() provides as much output as possible, until there&n;    is no more input data or no more space in the output buffer (see below&n;    about the flush parameter).&n;&n;  Before the call of inflate(), the application should ensure that at least&n;  one of the actions is possible, by providing more input and/or consuming&n;  more output, and updating the next_* and avail_* values accordingly.&n;  The application can consume the uncompressed output when it wants, for&n;  example when the output buffer is full (avail_out == 0), or after each&n;  call of inflate(). If inflate returns Z_OK and with zero avail_out, it&n;  must be called again after making room in the output buffer because there&n;  might be more output pending.&n;&n;    If the parameter flush is set to Z_PARTIAL_FLUSH or Z_PACKET_FLUSH,&n;  inflate flushes as much output as possible to the output buffer. The&n;  flushing behavior of inflate is not specified for values of the flush&n;  parameter other than Z_PARTIAL_FLUSH, Z_PACKET_FLUSH or Z_FINISH, but the&n;  current implementation actually flushes as much output as possible&n;  anyway.  For Z_PACKET_FLUSH, inflate checks that once all the input data&n;  has been consumed, it is expecting to see the length field of a stored&n;  block; if not, it returns Z_DATA_ERROR.&n;&n;    inflate() should normally be called until it returns Z_STREAM_END or an&n;  error. However if all decompression is to be performed in a single step&n;  (a single call of inflate), the parameter flush should be set to&n;  Z_FINISH. In this case all pending input is processed and all pending&n;  output is flushed; avail_out must be large enough to hold all the&n;  uncompressed data. (The size of the uncompressed data may have been saved&n;  by the compressor for this purpose.) The next operation on this stream must&n;  be inflateEnd to deallocate the decompression state. The use of Z_FINISH&n;  is never required, but can be used to inform inflate that a faster routine&n;  may be used for the single inflate() call.&n;&n;    inflate() returns Z_OK if some progress has been made (more input&n;  processed or more output produced), Z_STREAM_END if the end of the&n;  compressed data has been reached and all uncompressed output has been&n;  produced, Z_NEED_DICT if a preset dictionary is needed at this point (see&n;  inflateSetDictionary below), Z_DATA_ERROR if the input data was corrupted,&n;  Z_STREAM_ERROR if the stream structure was inconsistent (for example if&n;  next_in or next_out was NULL), Z_MEM_ERROR if there was not enough memory,&n;  Z_BUF_ERROR if no progress is possible or if there was not enough room in&n;  the output buffer when Z_FINISH is used. In the Z_DATA_ERROR case, the&n;  application may then call inflateSync to look for a good compression block.&n;  In the Z_NEED_DICT case, strm-&gt;adler is set to the Adler32 value of the&n;  dictionary chosen by the compressor.&n;*/
r_extern
r_int
id|EXPORT
id|inflateEnd
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     All dynamically allocated data structures for this stream are freed.&n;   This function discards any unprocessed input and does not flush any&n;   pending output.&n;&n;     inflateEnd returns Z_OK if success, Z_STREAM_ERROR if the stream state&n;   was inconsistent. In the error case, msg may be set but then points to a&n;   static string (which must not be deallocated).&n;*/
multiline_comment|/* Advanced functions */
multiline_comment|/*&n;    The following functions are needed only in some special applications.&n;*/
multiline_comment|/*   &n;extern int EXPORT deflateInit2 OF((z_streamp strm,&n;                                   int  level,&n;                                   int  method,&n;                                   int  windowBits,&n;                                   int  memLevel,&n;                                   int  strategy));&n;&n;     This is another version of deflateInit with more compression options. The&n;   fields next_in, zalloc, zfree and opaque must be initialized before by&n;   the caller.&n;&n;     The method parameter is the compression method. It must be Z_DEFLATED in&n;   this version of the library. (Method 9 will allow a 64K history buffer and&n;   partial block flushes.)&n;&n;     The windowBits parameter is the base two logarithm of the window size&n;   (the size of the history buffer).  It should be in the range 8..15 for this&n;   version of the library (the value 16 will be allowed for method 9). Larger&n;   values of this parameter result in better compression at the expense of&n;   memory usage. The default value is 15 if deflateInit is used instead.&n;&n;     The memLevel parameter specifies how much memory should be allocated&n;   for the internal compression state. memLevel=1 uses minimum memory but&n;   is slow and reduces compression ratio; memLevel=9 uses maximum memory&n;   for optimal speed. The default value is 8. See zconf.h for total memory&n;   usage as a function of windowBits and memLevel.&n;&n;     The strategy parameter is used to tune the compression algorithm. Use the&n;   value Z_DEFAULT_STRATEGY for normal data, Z_FILTERED for data produced by a&n;   filter (or predictor), or Z_HUFFMAN_ONLY to force Huffman encoding only (no&n;   string match).  Filtered data consists mostly of small values with a&n;   somewhat random distribution. In this case, the compression algorithm is&n;   tuned to compress them better. The effect of Z_FILTERED is to force more&n;   Huffman coding and less string matching; it is somewhat intermediate&n;   between Z_DEFAULT and Z_HUFFMAN_ONLY. The strategy parameter only affects&n;   the compression ratio but not the correctness of the compressed output even&n;   if it is not set appropriately.&n;&n;     If next_in is not null, the library will use this buffer to hold also&n;   some history information; the buffer must either hold the entire input&n;   data, or have at least 1&lt;&lt;(windowBits+1) bytes and be writable. If next_in&n;   is null, the library will allocate its own history buffer (and leave next_in&n;   null). next_out need not be provided here but must be provided by the&n;   application for the next call of deflate().&n;&n;     If the history buffer is provided by the application, next_in must&n;   must never be changed by the application since the compressor maintains&n;   information inside this buffer from call to call; the application&n;   must provide more input only by increasing avail_in. next_in is always&n;   reset by the library in this case.&n;&n;      deflateInit2 returns Z_OK if success, Z_MEM_ERROR if there was&n;   not enough memory, Z_STREAM_ERROR if a parameter is invalid (such as&n;   an invalid method). msg is set to null if there is no error message.&n;   deflateInit2 does not perform any compression: this will be done by&n;   deflate(). &n;*/
r_extern
r_int
id|EXPORT
id|deflateSetDictionary
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_const
id|Bytef
op_star
id|dictionary
comma
id|uInt
id|dictLength
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Initializes the compression dictionary (history buffer) from the given&n;   byte sequence without producing any compressed output. This function must&n;   be called immediately after deflateInit or deflateInit2, before any call&n;   of deflate. The compressor and decompressor must use exactly the same&n;   dictionary (see inflateSetDictionary).&n;     The dictionary should consist of strings (byte sequences) that are likely&n;   to be encountered later in the data to be compressed, with the most commonly&n;   used strings preferably put towards the end of the dictionary. Using a&n;   dictionary is most useful when the data to be compressed is short and&n;   can be predicted with good accuracy; the data can then be compressed better&n;   than with the default empty dictionary. In this version of the library,&n;   only the last 32K bytes of the dictionary are used.&n;     Upon return of this function, strm-&gt;adler is set to the Adler32 value&n;   of the dictionary; the decompressor may later use this value to determine&n;   which dictionary has been used by the compressor. (The Adler32 value&n;   applies to the whole dictionary even if only a subset of the dictionary is&n;   actually used by the compressor.)&n;&n;     deflateSetDictionary returns Z_OK if success, or Z_STREAM_ERROR if a&n;   parameter is invalid (such as NULL dictionary) or the stream state&n;   is inconsistent (for example if deflate has already been called for this&n;   stream). deflateSetDictionary does not perform any compression: this will&n;   be done by deflate(). &n;*/
r_extern
r_int
id|EXPORT
id|deflateCopy
id|OF
c_func
(paren
(paren
id|z_streamp
id|dest
comma
id|z_streamp
id|source
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Sets the destination stream as a complete copy of the source stream.  If&n;   the source stream is using an application-supplied history buffer, a new&n;   buffer is allocated for the destination stream.  The compressed output&n;   buffer is always application-supplied. It&squot;s the responsibility of the&n;   application to provide the correct values of next_out and avail_out for the&n;   next call of deflate.&n;&n;     This function can be useful when several compression strategies will be&n;   tried, for example when there are several ways of pre-processing the input&n;   data with a filter. The streams that will be discarded should then be freed&n;   by calling deflateEnd.  Note that deflateCopy duplicates the internal&n;   compression state which can be quite large, so this strategy is slow and&n;   can consume lots of memory.&n;&n;     deflateCopy returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_STREAM_ERROR if the source stream state was inconsistent&n;   (such as zalloc being NULL). msg is left unchanged in both source and&n;   destination.&n;*/
r_extern
r_int
id|EXPORT
id|deflateReset
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     This function is equivalent to deflateEnd followed by deflateInit,&n;   but does not free and reallocate all the internal compression state.&n;   The stream will keep the same compression level and any other attributes&n;   that may have been set by deflateInit2.&n;&n;      deflateReset returns Z_OK if success, or Z_STREAM_ERROR if the source&n;   stream state was inconsistent (such as zalloc or state being NULL).&n;*/
r_extern
r_int
id|EXPORT
id|deflateParams
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_int
id|level
comma
r_int
id|strategy
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Dynamically update the compression level and compression strategy.&n;   This can be used to switch between compression and straight copy of&n;   the input data, or to switch to a different kind of input data requiring&n;   a different strategy. If the compression level is changed, the input&n;   available so far is compressed with the old level (and may be flushed);&n;   the new level will take effect only at the next call of deflate().&n;&n;     Before the call of deflateParams, the stream state must be set as for&n;   a call of deflate(), since the currently available input may have to&n;   be compressed and flushed. In particular, strm-&gt;avail_out must be non-zero.&n;&n;     deflateParams returns Z_OK if success, Z_STREAM_ERROR if the source&n;   stream state was inconsistent or if a parameter was invalid, Z_BUF_ERROR&n;   if strm-&gt;avail_out was zero.&n;*/
r_extern
r_int
id|EXPORT
id|deflateOutputPending
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Returns the number of bytes of output which are immediately&n;   available from the compressor (i.e. without any further input&n;   or flush).&n;*/
multiline_comment|/*   &n;extern int EXPORT inflateInit2 OF((z_streamp strm,&n;                                   int  windowBits));&n;&n;     This is another version of inflateInit with more compression options. The&n;   fields next_out, zalloc, zfree and opaque must be initialized before by&n;   the caller.&n;&n;     The windowBits parameter is the base two logarithm of the maximum window&n;   size (the size of the history buffer).  It should be in the range 8..15 for&n;   this version of the library (the value 16 will be allowed soon). The&n;   default value is 15 if inflateInit is used instead. If a compressed stream&n;   with a larger window size is given as input, inflate() will return with&n;   the error code Z_DATA_ERROR instead of trying to allocate a larger window.&n;&n;     If next_out is not null, the library will use this buffer for the history&n;   buffer; the buffer must either be large enough to hold the entire output&n;   data, or have at least 1&lt;&lt;windowBits bytes.  If next_out is null, the&n;   library will allocate its own buffer (and leave next_out null). next_in&n;   need not be provided here but must be provided by the application for the&n;   next call of inflate().&n;&n;     If the history buffer is provided by the application, next_out must&n;   never be changed by the application since the decompressor maintains&n;   history information inside this buffer from call to call; the application&n;   can only reset next_out to the beginning of the history buffer when&n;   avail_out is zero and all output has been consumed.&n;&n;      inflateInit2 returns Z_OK if success, Z_MEM_ERROR if there was&n;   not enough memory, Z_STREAM_ERROR if a parameter is invalid (such as&n;   windowBits &lt; 8). msg is set to null if there is no error message.&n;   inflateInit2 does not perform any decompression: this will be done by&n;   inflate().&n;*/
r_extern
r_int
id|EXPORT
id|inflateSetDictionary
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_const
id|Bytef
op_star
id|dictionary
comma
id|uInt
id|dictLength
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Initializes the decompression dictionary (history buffer) from the given&n;   uncompressed byte sequence. This function must be called immediately after&n;   a call of inflate if this call returned Z_NEED_DICT. The dictionary chosen&n;   by the compressor can be determined from the Adler32 value returned by this&n;   call of inflate. The compressor and decompressor must use exactly the same&n;   dictionary (see deflateSetDictionary).&n;&n;     inflateSetDictionary returns Z_OK if success, Z_STREAM_ERROR if a&n;   parameter is invalid (such as NULL dictionary) or the stream state is&n;   inconsistent, Z_DATA_ERROR if the given dictionary doesn&squot;t match the&n;   expected one (incorrect Adler32 value). inflateSetDictionary does not&n;   perform any decompression: this will be done by subsequent calls of&n;   inflate().&n;*/
r_extern
r_int
id|EXPORT
id|inflateSync
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;    Skips invalid compressed data until the special marker (see deflate()&n;  above) can be found, or until all available input is skipped. No output&n;  is provided.&n;&n;    inflateSync returns Z_OK if the special marker has been found, Z_BUF_ERROR&n;  if no more input was provided, Z_DATA_ERROR if no marker has been found,&n;  or Z_STREAM_ERROR if the stream structure was inconsistent. In the success&n;  case, the application may save the current current value of total_in which&n;  indicates where valid compressed data was found. In the error case, the&n;  application may repeatedly call inflateSync, providing more input each time,&n;  until success or end of the input data.&n;*/
r_extern
r_int
id|EXPORT
id|inflateReset
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     This function is equivalent to inflateEnd followed by inflateInit,&n;   but does not free and reallocate all the internal decompression state.&n;   The stream will keep attributes that may have been set by inflateInit2.&n;&n;      inflateReset returns Z_OK if success, or Z_STREAM_ERROR if the source&n;   stream state was inconsistent (such as zalloc or state being NULL).&n;*/
r_extern
r_int
id|inflateIncomp
id|OF
c_func
(paren
(paren
id|z_stream
op_star
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     This function adds the data at next_in (avail_in bytes) to the output&n;   history without performing any output.  There must be no pending output,&n;   and the decompressor must be expecting to see the start of a block.&n;   Calling this function is equivalent to decompressing a stored block&n;   containing the data at next_in (except that the data is not output).&n;*/
multiline_comment|/* utility functions */
multiline_comment|/*&n;     The following utility functions are implemented on top of the&n;   basic stream-oriented functions. To simplify the interface, some&n;   default options are assumed (compression level, window size,&n;   standard memory allocation functions). The source code of these&n;   utility functions can easily be modified if you need special options.&n;*/
r_extern
r_int
id|EXPORT
id|compress
id|OF
c_func
(paren
(paren
id|Bytef
op_star
id|dest
comma
id|uLongf
op_star
id|destLen
comma
r_const
id|Bytef
op_star
id|source
comma
id|uLong
id|sourceLen
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Compresses the source buffer into the destination buffer.  sourceLen is&n;   the byte length of the source buffer. Upon entry, destLen is the total&n;   size of the destination buffer, which must be at least 0.1% larger than&n;   sourceLen plus 12 bytes. Upon exit, destLen is the actual size of the&n;   compressed buffer.&n;     This function can be used to compress a whole file at once if the&n;   input file is mmap&squot;ed.&n;     compress returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_BUF_ERROR if there was not enough room in the output&n;   buffer.&n;*/
r_extern
r_int
id|EXPORT
id|uncompress
id|OF
c_func
(paren
(paren
id|Bytef
op_star
id|dest
comma
id|uLongf
op_star
id|destLen
comma
r_const
id|Bytef
op_star
id|source
comma
id|uLong
id|sourceLen
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Decompresses the source buffer into the destination buffer.  sourceLen is&n;   the byte length of the source buffer. Upon entry, destLen is the total&n;   size of the destination buffer, which must be large enough to hold the&n;   entire uncompressed data. (The size of the uncompressed data must have&n;   been saved previously by the compressor and transmitted to the decompressor&n;   by some mechanism outside the scope of this compression library.)&n;   Upon exit, destLen is the actual size of the compressed buffer.&n;     This function can be used to decompress a whole file at once if the&n;   input file is mmap&squot;ed.&n;&n;     uncompress returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_BUF_ERROR if there was not enough room in the output&n;   buffer, or Z_DATA_ERROR if the input data was corrupted.&n;*/
DECL|typedef|gzFile
r_typedef
id|voidp
id|gzFile
suffix:semicolon
r_extern
id|gzFile
id|EXPORT
id|gzopen
id|OF
c_func
(paren
(paren
r_const
r_char
op_star
id|path
comma
r_const
r_char
op_star
id|mode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Opens a gzip (.gz) file for reading or writing. The mode parameter&n;   is as in fopen (&quot;rb&quot; or &quot;wb&quot;) but can also include a compression level&n;   (&quot;wb9&quot;).  gzopen can be used to read a file which is not in gzip format;&n;   in this case gzread will directly read from the file without decompression.&n;     gzopen returns NULL if the file could not be opened or if there was&n;   insufficient memory to allocate the (de)compression state; errno&n;   can be checked to distinguish the two cases (if errno is zero, the&n;   zlib error is Z_MEM_ERROR).&n;*/
r_extern
id|gzFile
id|EXPORT
id|gzdopen
id|OF
c_func
(paren
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|mode
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     gzdopen() associates a gzFile with the file descriptor fd.  File&n;   descriptors are obtained from calls like open, dup, creat, pipe or&n;   fileno (in the file has been previously opened with fopen).&n;   The mode parameter is as in gzopen.&n;     The next call of gzclose on the returned gzFile will also close the&n;   file descriptor fd, just like fclose(fdopen(fd), mode) closes the file&n;   descriptor fd. If you want to keep fd open, use gzdopen(dup(fd), mode).&n;     gzdopen returns NULL if there was insufficient memory to allocate&n;   the (de)compression state.&n;*/
r_extern
r_int
id|EXPORT
id|gzread
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
id|voidp
id|buf
comma
r_int
id|len
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Reads the given number of uncompressed bytes from the compressed file.&n;   If the input file was not in gzip format, gzread copies the given number&n;   of bytes into the buffer.&n;     gzread returns the number of uncompressed bytes actually read (0 for&n;   end of file, -1 for error). */
r_extern
r_int
id|EXPORT
id|gzwrite
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_const
id|voidp
id|buf
comma
r_int
id|len
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Writes the given number of uncompressed bytes into the compressed file.&n;   gzwrite returns the number of uncompressed bytes actually written&n;   (0 in case of error).&n;*/
r_extern
r_int
id|EXPORT
id|gzflush
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_int
id|flush
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Flushes all pending output into the compressed file. The parameter&n;   flush is as in the deflate() function. The return value is the zlib&n;   error number (see function gzerror below). gzflush returns Z_OK if&n;   the flush parameter is Z_FINISH and all output could be flushed.&n;     gzflush should be called only when strictly necessary because it can&n;   degrade compression.&n;*/
r_extern
r_int
id|EXPORT
id|gzclose
id|OF
c_func
(paren
(paren
id|gzFile
id|file
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Flushes all pending output if necessary, closes the compressed file&n;   and deallocates all the (de)compression state. The return value is the zlib&n;   error number (see function gzerror below).&n;*/
r_extern
r_const
r_char
op_star
id|EXPORT
id|gzerror
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_int
op_star
id|errnum
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Returns the error message for the last error which occurred on the&n;   given compressed file. errnum is set to zlib error number. If an&n;   error occurred in the file system and not in the compression library,&n;   errnum is set to Z_ERRNO and the application may consult errno&n;   to get the exact error code.&n;*/
multiline_comment|/* checksum functions */
multiline_comment|/*&n;     These functions are not related to compression but are exported&n;   anyway because they might be useful in applications using the&n;   compression library.&n;*/
r_extern
id|uLong
id|EXPORT
id|adler32
id|OF
c_func
(paren
(paren
id|uLong
id|adler
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
multiline_comment|/*&n;     Update a running Adler-32 checksum with the bytes buf[0..len-1] and&n;   return the updated checksum. If buf is NULL, this function returns&n;   the required initial value for the checksum.&n;   An Adler-32 checksum is almost as reliable as a CRC32 but can be computed&n;   much faster. Usage example:&n;&n;     uLong adler = adler32(0L, Z_NULL, 0);&n;&n;     while (read_buffer(buffer, length) != EOF) {&n;       adler = adler32(adler, buffer, length);&n;     }&n;     if (adler != original_adler) error();&n;*/
r_extern
id|uLong
id|EXPORT
id|crc32
id|OF
c_func
(paren
(paren
id|uLong
id|crc
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
multiline_comment|/*&n;     Update a running crc with the bytes buf[0..len-1] and return the updated&n;   crc. If buf is NULL, this function returns the required initial value&n;   for the crc. Pre- and post-conditioning (one&squot;s complement) is performed&n;   within this function so it shouldn&squot;t be done by the application.&n;   Usage example:&n;&n;     uLong crc = crc32(0L, Z_NULL, 0);&n;&n;     while (read_buffer(buffer, length) != EOF) {&n;       crc = crc32(crc, buffer, length);&n;     }&n;     if (crc != original_crc) error();&n;*/
multiline_comment|/* various hacks, don&squot;t look :) */
multiline_comment|/* deflateInit and inflateInit are macros to allow checking the zlib version&n; * and the compiler&squot;s view of z_stream:&n; */
r_extern
r_int
id|EXPORT
id|deflateInit_
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_int
id|level
comma
r_const
r_char
op_star
id|version
comma
r_int
id|stream_size
)paren
)paren
suffix:semicolon
r_extern
r_int
id|EXPORT
id|inflateInit_
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_const
r_char
op_star
id|version
comma
r_int
id|stream_size
)paren
)paren
suffix:semicolon
r_extern
r_int
id|EXPORT
id|deflateInit2_
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_int
id|level
comma
r_int
id|method
comma
r_int
id|windowBits
comma
r_int
id|memLevel
comma
r_int
id|strategy
comma
r_const
r_char
op_star
id|version
comma
r_int
id|stream_size
)paren
)paren
suffix:semicolon
r_extern
r_int
id|EXPORT
id|inflateInit2_
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
comma
r_int
id|windowBits
comma
r_const
r_char
op_star
id|version
comma
r_int
id|stream_size
)paren
)paren
suffix:semicolon
DECL|macro|deflateInit
mdefine_line|#define deflateInit(strm, level) &bslash;&n;        deflateInit_((strm), (level),       ZLIB_VERSION, sizeof(z_stream))
DECL|macro|inflateInit
mdefine_line|#define inflateInit(strm) &bslash;&n;        inflateInit_((strm),                ZLIB_VERSION, sizeof(z_stream))
DECL|macro|deflateInit2
mdefine_line|#define deflateInit2(strm, level, method, windowBits, memLevel, strategy) &bslash;&n;        deflateInit2_((strm),(level),(method),(windowBits),(memLevel),&bslash;&n;&t;&t;      (strategy),           ZLIB_VERSION, sizeof(z_stream))
DECL|macro|inflateInit2
mdefine_line|#define inflateInit2(strm, windowBits) &bslash;&n;        inflateInit2_((strm), (windowBits), ZLIB_VERSION, sizeof(z_stream))
macro_line|#if !defined(_Z_UTIL_H) &amp;&amp; !defined(NO_DUMMY_DECL)
DECL|struct|internal_state
DECL|member|dummy
r_struct
id|internal_state
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hack for buggy compilers */
macro_line|#endif
id|uLongf
op_star
id|get_crc_table
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
multiline_comment|/* can be used by asm versions of crc32() */
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* _ZLIB_H */
multiline_comment|/* --- zlib.h */
eof
