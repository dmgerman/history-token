multiline_comment|/*&t;&t;*/
multiline_comment|/*&n; * This file is derived from zlib.h and zconf.h from the zlib-0.95&n; * distribution by Jean-loup Gailly and Mark Adler, with some additions&n; * by Paul Mackerras to aid in implementing Deflate compression and&n; * decompression for PPP packets.&n; */
multiline_comment|/*&n; *  ==FILEVERSION 960122==&n; *&n; * This marker is used by the Linux installation script to determine&n; * whether an up-to-date version of this file is already installed.&n; */
multiline_comment|/* zlib.h -- interface of the &squot;zlib&squot; general purpose compression library&n;  version 0.95, Aug 16th, 1995.&n;&n;  Copyright (C) 1995 Jean-loup Gailly and Mark Adler&n;&n;  This software is provided &squot;as-is&squot;, without any express or implied&n;  warranty.  In no event will the authors be held liable for any damages&n;  arising from the use of this software.&n;&n;  Permission is granted to anyone to use this software for any purpose,&n;  including commercial applications, and to alter it and redistribute it&n;  freely, subject to the following restrictions:&n;&n;  1. The origin of this software must not be misrepresented; you must not&n;     claim that you wrote the original software. If you use this software&n;     in a product, an acknowledgment in the product documentation would be&n;     appreciated but is not required.&n;  2. Altered source versions must be plainly marked as such, and must not be&n;     misrepresented as being the original software.&n;  3. This notice may not be removed or altered from any source distribution.&n;&n;  Jean-loup Gailly        Mark Adler&n;  gzip@prep.ai.mit.edu    madler@alumni.caltech.edu&n; */
macro_line|#ifndef _ZLIB_H
DECL|macro|_ZLIB_H
mdefine_line|#define _ZLIB_H
multiline_comment|/* #include &quot;zconf.h&quot; */
multiline_comment|/* included directly here */
multiline_comment|/* zconf.h -- configuration of the zlib compression library&n; * Copyright (C) 1995 Jean-loup Gailly.&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* From: zconf.h,v 1.12 1995/05/03 17:27:12 jloup Exp */
multiline_comment|/*&n;     The library does not install any signal handler. It is recommended to&n;  add at least a handler for SIGSEGV when decompressing; the library checks&n;  the consistency of the input data whenever possible but may go nuts&n;  for some forms of corrupted input.&n; */
multiline_comment|/*&n; * Compile with -DMAXSEG_64K if the alloc function cannot allocate more&n; * than 64k bytes at a time (needed on systems with 16-bit int).&n; * Compile with -DUNALIGNED_OK if it is OK to access shorts or ints&n; * at addresses which are not a multiple of their size.&n; * Under DOS, -DFAR=far or -DFAR=__far may be needed.&n; */
macro_line|#ifndef STDC
macro_line|#  if defined(MSDOS) || defined(__STDC__) || defined(__cplusplus)
DECL|macro|STDC
macro_line|#    define STDC
macro_line|#  endif
macro_line|#endif
macro_line|#ifdef&t;__MWERKS__ /* Metrowerks CodeWarrior declares fileno() in unix.h */
macro_line|#  include &lt;unix.h&gt;
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
macro_line|#ifndef FAR
DECL|macro|FAR
macro_line|#  define FAR
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
DECL|typedef|Bytef
r_typedef
id|Byte
id|FAR
id|Bytef
suffix:semicolon
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
multiline_comment|/* end of original zconf.h */
DECL|macro|ZLIB_VERSION
mdefine_line|#define ZLIB_VERSION &quot;0.95P&quot;
multiline_comment|/* &n;     The &squot;zlib&squot; compression library provides in-memory compression and&n;  decompression functions, including integrity checks of the uncompressed&n;  data.  This version of the library supports only one compression method&n;  (deflation) but other algorithms may be added later and will have the same&n;  stream interface.&n;&n;     For compression the application must provide the output buffer and&n;  may optionally provide the input buffer for optimization. For decompression,&n;  the application must provide the input buffer and may optionally provide&n;  the output buffer for optimization.&n;&n;     Compression can be done in a single step if the buffers are large&n;  enough (for example if an input file is mmap&squot;ed), or can be done by&n;  repeated calls of the compression function.  In the latter case, the&n;  application must provide more input and/or consume the output&n;  (providing more output space) before each call.&n;*/
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
comma
id|uInt
id|nbytes
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
id|voidp
id|opaque
suffix:semicolon
multiline_comment|/* private data object passed to zalloc and zfree */
DECL|member|data_type
id|Byte
id|data_type
suffix:semicolon
multiline_comment|/* best guess about the data type: ascii or binary */
DECL|typedef|z_stream
)brace
id|z_stream
suffix:semicolon
multiline_comment|/*&n;   The application must update next_in and avail_in when avail_in has&n;   dropped to zero. It must update next_out and avail_out when avail_out&n;   has dropped to zero. The application must initialize zalloc, zfree and&n;   opaque before calling the init function. All other fields are set by the&n;   compression library and must not be updated by the application.&n;&n;   The opaque value provided by the application will be passed as the first&n;   parameter for calls of zalloc and zfree. This can be useful for custom&n;   memory management. The compression library attaches no meaning to the&n;   opaque value.&n;&n;   zalloc must return Z_NULL if there is not enough memory for the object.&n;   On 16-bit systems, the functions zalloc and zfree must be able to allocate&n;   exactly 65536 bytes, but will not be required to allocate more than this&n;   if the symbol MAXSEG_64K is defined (see zconf.h). WARNING: On MSDOS,&n;   pointers returned by zalloc for objects of exactly 65536 bytes *must*&n;   have their offset normalized to zero. The default allocation function&n;   provided by this library ensures this (see zutil.c). To reduce memory&n;   requirements and avoid any allocation of 64K objects, at the expense of&n;   compression ratio, compile the library with -DMAX_WBITS=14 (see zconf.h).&n;&n;   The fields total_in and total_out can be used for statistics or&n;   progress reports. After compression, total_in holds the total size of&n;   the uncompressed data and may be saved for use in the decompressor&n;   (particularly if the decompressor wants to decompress everything in&n;   a single step).&n;*/
multiline_comment|/* constants */
DECL|macro|Z_NO_FLUSH
mdefine_line|#define Z_NO_FLUSH      0
DECL|macro|Z_PARTIAL_FLUSH
mdefine_line|#define Z_PARTIAL_FLUSH 1
DECL|macro|Z_FULL_FLUSH
mdefine_line|#define Z_FULL_FLUSH    2
DECL|macro|Z_SYNC_FLUSH
mdefine_line|#define Z_SYNC_FLUSH    3 /* experimental: partial_flush + byte align */
DECL|macro|Z_FINISH
mdefine_line|#define Z_FINISH        4
DECL|macro|Z_PACKET_FLUSH
mdefine_line|#define Z_PACKET_FLUSH&t;5
multiline_comment|/* See deflate() below for the usage of these constants */
DECL|macro|Z_OK
mdefine_line|#define Z_OK            0
DECL|macro|Z_STREAM_END
mdefine_line|#define Z_STREAM_END    1
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
multiline_comment|/* error codes for the compression/decompression functions */
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
DECL|macro|Z_BINARY
mdefine_line|#define Z_BINARY   0
DECL|macro|Z_ASCII
mdefine_line|#define Z_ASCII    1
DECL|macro|Z_UNKNOWN
mdefine_line|#define Z_UNKNOWN  2
multiline_comment|/* Used to set the data_type field */
DECL|macro|Z_NULL
mdefine_line|#define Z_NULL  0  /* for initializing zalloc, zfree, opaque */
r_extern
r_char
op_star
id|zlib_version
suffix:semicolon
multiline_comment|/* The application can compare zlib_version and ZLIB_VERSION for consistency.&n;   If the first character differs, the library code actually used is&n;   not compatible with the zlib.h header file used by the application.&n; */
multiline_comment|/* basic functions */
r_extern
r_int
id|inflateInit
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
multiline_comment|/* &n;     Initializes the internal stream state for decompression. The fields&n;   zalloc and zfree must be initialized before by the caller.  If zalloc and&n;   zfree are set to Z_NULL, inflateInit updates them to use default allocation&n;   functions.&n;&n;     inflateInit returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory.  msg is set to null if there is no error message.&n;   inflateInit does not perform any decompression: this will be done by&n;   inflate().&n;*/
r_extern
r_int
id|inflate
id|OF
c_func
(paren
(paren
id|z_stream
op_star
id|strm
comma
r_int
id|flush
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;  Performs one or both of the following actions:&n;&n;  - Decompress more input starting at next_in and update next_in and avail_in&n;    accordingly. If not all input can be processed (because there is not&n;    enough room in the output buffer), next_in is updated and processing&n;    will resume at this point for the next call of inflate().&n;&n;  - Provide more output starting at next_out and update next_out and avail_out&n;    accordingly.  inflate() always provides as much output as possible&n;    (until there is no more input data or no more space in the output buffer).&n;&n;  Before the call of inflate(), the application should ensure that at least&n;  one of the actions is possible, by providing more input and/or consuming&n;  more output, and updating the next_* and avail_* values accordingly.&n;  The application can consume the uncompressed output when it wants, for&n;  example when the output buffer is full (avail_out == 0), or after each&n;  call of inflate().&n;&n;    If the parameter flush is set to Z_PARTIAL_FLUSH or Z_PACKET_FLUSH,&n;  inflate flushes as much output as possible to the output buffer. The&n;  flushing behavior of inflate is not specified for values of the flush&n;  parameter other than Z_PARTIAL_FLUSH, Z_PACKET_FLUSH or Z_FINISH, but the&n;  current implementation actually flushes as much output as possible&n;  anyway.  For Z_PACKET_FLUSH, inflate checks that once all the input data&n;  has been consumed, it is expecting to see the length field of a stored&n;  block; if not, it returns Z_DATA_ERROR.&n;&n;    inflate() should normally be called until it returns Z_STREAM_END or an&n;  error. However if all decompression is to be performed in a single step&n;  (a single call of inflate), the parameter flush should be set to&n;  Z_FINISH. In this case all pending input is processed and all pending&n;  output is flushed; avail_out must be large enough to hold all the&n;  uncompressed data. (The size of the uncompressed data may have been saved&n;  by the compressor for this purpose.) The next operation on this stream must&n;  be inflateEnd to deallocate the decompression state. The use of Z_FINISH&n;  is never required, but can be used to inform inflate that a faster routine&n;  may be used for the single inflate() call.&n;&n;    inflate() returns Z_OK if some progress has been made (more input&n;  processed or more output produced), Z_STREAM_END if the end of the&n;  compressed data has been reached and all uncompressed output has been&n;  produced, Z_DATA_ERROR if the input data was corrupted, Z_STREAM_ERROR if&n;  the stream structure was inconsistent (for example if next_in or next_out&n;  was NULL), Z_MEM_ERROR if there was not enough memory, Z_BUF_ERROR if no&n;  progress is possible or if there was not enough room in the output buffer&n;  when Z_FINISH is used. In the Z_DATA_ERROR case, the application may then&n;  call inflateSync to look for a good compression block.  */
r_extern
r_int
id|inflateEnd
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
multiline_comment|/*&n;     All dynamically allocated data structures for this stream are freed.&n;   This function discards any unprocessed input and does not flush any&n;   pending output.&n;&n;     inflateEnd returns Z_OK if success, Z_STREAM_ERROR if the stream state&n;   was inconsistent. In the error case, msg may be set but then points to a&n;   static string (which must not be deallocated).&n;*/
multiline_comment|/* advanced functions */
r_extern
r_int
id|inflateInit2
id|OF
c_func
(paren
(paren
id|z_stream
op_star
id|strm
comma
r_int
id|windowBits
)paren
)paren
suffix:semicolon
multiline_comment|/*   &n;     This is another version of inflateInit with more compression options. The&n;   fields next_out, zalloc and zfree must be initialized before by the caller.&n;&n;     The windowBits parameter is the base two logarithm of the maximum window&n;   size (the size of the history buffer).  It should be in the range 8..15 for&n;   this version of the library (the value 16 will be allowed soon). The&n;   default value is 15 if inflateInit is used instead. If a compressed stream&n;   with a larger window size is given as input, inflate() will return with&n;   the error code Z_DATA_ERROR instead of trying to allocate a larger window.&n;&n;     If next_out is not null, the library will use this buffer for the history&n;   buffer; the buffer must either be large enough to hold the entire output&n;   data, or have at least 1&lt;&lt;windowBits bytes.  If next_out is null, the&n;   library will allocate its own buffer (and leave next_out null). next_in&n;   need not be provided here but must be provided by the application for the&n;   next call of inflate().&n;&n;     If the history buffer is provided by the application, next_out must&n;   never be changed by the application since the decompressor maintains&n;   history information inside this buffer from call to call; the application&n;   can only reset next_out to the beginning of the history buffer when&n;   avail_out is zero and all output has been consumed.&n;&n;      inflateInit2 returns Z_OK if success, Z_MEM_ERROR if there was&n;   not enough memory, Z_STREAM_ERROR if a parameter is invalid (such as&n;   windowBits &lt; 8). msg is set to null if there is no error message.&n;   inflateInit2 does not perform any decompression: this will be done by&n;   inflate().&n;*/
r_extern
r_int
id|inflateSync
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
multiline_comment|/* &n;    Skips invalid compressed data until the special marker (see deflate()&n;  above) can be found, or until all available input is skipped. No output&n;  is provided.&n;&n;    inflateSync returns Z_OK if the special marker has been found, Z_BUF_ERROR&n;  if no more input was provided, Z_DATA_ERROR if no marker has been found,&n;  or Z_STREAM_ERROR if the stream structure was inconsistent. In the success&n;  case, the application may save the current current value of total_in which&n;  indicates where valid compressed data was found. In the error case, the&n;  application may repeatedly call inflateSync, providing more input each time,&n;  until success or end of the input data.&n;*/
r_extern
r_int
id|inflateReset
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
multiline_comment|/* checksum functions */
multiline_comment|/*&n;     This function is not related to compression but is exported&n;   anyway because it might be useful in applications using the&n;   compression library.&n;*/
r_extern
id|uLong
id|adler32
id|OF
c_func
(paren
(paren
id|uLong
id|adler
comma
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
macro_line|#ifndef _Z_UTIL_H
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
macro_line|#endif /* _ZLIB_H */
eof
