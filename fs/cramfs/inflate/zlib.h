multiline_comment|/* zlib.h -- interface of the &squot;zlib&squot; general purpose compression library&n;  version 1.1.3, July 9th, 1998&n;&n;  Copyright (C) 1995-1998 Jean-loup Gailly and Mark Adler&n;&n;  This software is provided &squot;as-is&squot;, without any express or implied&n;  warranty.  In no event will the authors be held liable for any damages&n;  arising from the use of this software.&n;&n;  Permission is granted to anyone to use this software for any purpose,&n;  including commercial applications, and to alter it and redistribute it&n;  freely, subject to the following restrictions:&n;&n;  1. The origin of this software must not be misrepresented; you must not&n;     claim that you wrote the original software. If you use this software&n;     in a product, an acknowledgment in the product documentation would be&n;     appreciated but is not required.&n;  2. Altered source versions must be plainly marked as such, and must not be&n;     misrepresented as being the original software.&n;  3. This notice may not be removed or altered from any source distribution.&n;&n;  Jean-loup Gailly        Mark Adler&n;  jloup@gzip.org          madler@alumni.caltech.edu&n;&n;&n;  The data format used by the zlib library is described by RFCs (Request for&n;  Comments) 1950 to 1952 in the files ftp://ds.internic.net/rfc/rfc1950.txt&n;  (zlib format), rfc1951.txt (deflate format) and rfc1952.txt (gzip format).&n;*/
macro_line|#ifndef _ZLIB_H
DECL|macro|_ZLIB_H
mdefine_line|#define _ZLIB_H
macro_line|#include &quot;zconf.h&quot;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
DECL|macro|ZLIB_VERSION
mdefine_line|#define ZLIB_VERSION &quot;1.1.3&quot;
multiline_comment|/* &n;     The &squot;zlib&squot; compression library provides in-memory compression and&n;  decompression functions, including integrity checks of the uncompressed&n;  data.  This version of the library supports only one compression method&n;  (deflation) but other algorithms will be added later and will have the same&n;  stream interface.&n;&n;     Compression can be done in a single step if the buffers are large&n;  enough (for example if an input file is mmap&squot;ed), or can be done by&n;  repeated calls of the compression function.  In the latter case, the&n;  application must provide more input and/or consume the output&n;  (providing more output space) before each call.&n;&n;     The library also supports reading and writing files in gzip (.gz) format&n;  with an interface similar to that of stdio.&n;&n;     The library does not install any signal handler. The decoder checks&n;  the consistency of the compressed data, so the library should never&n;  crash even in case of corrupted input.&n;*/
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
DECL|member|nozalloc
id|alloc_func
id|nozalloc
suffix:semicolon
multiline_comment|/* used to allocate the internal state */
DECL|member|nozfree
id|free_func
id|nozfree
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
multiline_comment|/*&n;   The application must update next_in and avail_in when avail_in has&n;   dropped to zero. It must update next_out and avail_out when avail_out&n;   has dropped to zero. The application must initialize zalloc, zfree and&n;   opaque before calling the init function. All other fields are set by the&n;   compression library and must not be updated by the application.&n;&n;   The opaque value provided by the application will be passed as the first&n;   parameter for calls of zalloc and zfree. This can be useful for custom&n;   memory management. The compression library attaches no meaning to the&n;   opaque value.&n;&n;   zalloc must return Z_NULL if there is not enough memory for the object.&n;   If zlib is used in a multi-threaded application, zalloc and zfree must be&n;   thread safe.&n;&n;   On 16-bit systems, the functions zalloc and zfree must be able to allocate&n;   exactly 65536 bytes, but will not be required to allocate more than this&n;   if the symbol MAXSEG_64K is defined (see zconf.h). WARNING: On MSDOS,&n;   pointers returned by zalloc for objects of exactly 65536 bytes *must*&n;   have their offset normalized to zero. The default allocation function&n;   provided by this library ensures this (see zutil.c). To reduce memory&n;   requirements and avoid any allocation of 64K objects, at the expense of&n;   compression ratio, compile the library with -DMAX_WBITS=14 (see zconf.h).&n;&n;   The fields total_in and total_out can be used for statistics or&n;   progress reports. After compression, total_in holds the total size of&n;   the uncompressed data and may be saved for use in the decompressor&n;   (particularly if the decompressor wants to decompress everything in&n;   a single step).&n;*/
multiline_comment|/* constants */
DECL|macro|Z_NO_FLUSH
mdefine_line|#define Z_NO_FLUSH      0
DECL|macro|Z_PARTIAL_FLUSH
mdefine_line|#define Z_PARTIAL_FLUSH 1 /* will be removed, use Z_SYNC_FLUSH instead */
DECL|macro|Z_SYNC_FLUSH
mdefine_line|#define Z_SYNC_FLUSH    2
DECL|macro|Z_FULL_FLUSH
mdefine_line|#define Z_FULL_FLUSH    3
DECL|macro|Z_FINISH
mdefine_line|#define Z_FINISH        4
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
id|ZEXTERN
r_const
r_char
op_star
id|ZEXPORT
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
multiline_comment|/* &n;ZEXTERN int ZEXPORT deflateInit OF((z_streamp strm, int level));&n;&n;     Initializes the internal stream state for compression. The fields&n;   zalloc, zfree and opaque must be initialized before by the caller.&n;   If zalloc and zfree are set to Z_NULL, deflateInit updates them to&n;   use default allocation functions.&n;&n;     The compression level must be Z_DEFAULT_COMPRESSION, or between 0 and 9:&n;   1 gives best speed, 9 gives best compression, 0 gives no compression at&n;   all (the input data is simply copied a block at a time).&n;   Z_DEFAULT_COMPRESSION requests a default compromise between speed and&n;   compression (currently equivalent to level 6).&n;&n;     deflateInit returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_STREAM_ERROR if level is not a valid compression level,&n;   Z_VERSION_ERROR if the zlib library version (zlib_version) is incompatible&n;   with the version assumed by the caller (ZLIB_VERSION).&n;   msg is set to null if there is no error message.  deflateInit does not&n;   perform any compression: this will be done by deflate().&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
multiline_comment|/*&n;    deflate compresses as much data as possible, and stops when the input&n;  buffer becomes empty or the output buffer becomes full. It may introduce some&n;  output latency (reading input without producing any output) except when&n;  forced to flush.&n;&n;    The detailed semantics are as follows. deflate performs one or both of the&n;  following actions:&n;&n;  - Compress more input starting at next_in and update next_in and avail_in&n;    accordingly. If not all input can be processed (because there is not&n;    enough room in the output buffer), next_in and avail_in are updated and&n;    processing will resume at this point for the next call of deflate().&n;&n;  - Provide more output starting at next_out and update next_out and avail_out&n;    accordingly. This action is forced if the parameter flush is non zero.&n;    Forcing flush frequently degrades the compression ratio, so this parameter&n;    should be set only when necessary (in interactive applications).&n;    Some output may be provided even if flush is not set.&n;&n;  Before the call of deflate(), the application should ensure that at least&n;  one of the actions is possible, by providing more input and/or consuming&n;  more output, and updating avail_in or avail_out accordingly; avail_out&n;  should never be zero before the call. The application can consume the&n;  compressed output when it wants, for example when the output buffer is full&n;  (avail_out == 0), or after each call of deflate(). If deflate returns Z_OK&n;  and with zero avail_out, it must be called again after making room in the&n;  output buffer because there might be more output pending.&n;&n;    If the parameter flush is set to Z_SYNC_FLUSH, all pending output is&n;  flushed to the output buffer and the output is aligned on a byte boundary, so&n;  that the decompressor can get all input data available so far. (In particular&n;  avail_in is zero after the call if enough output space has been provided&n;  before the call.)  Flushing may degrade compression for some compression&n;  algorithms and so it should be used only when necessary.&n;&n;    If flush is set to Z_FULL_FLUSH, all output is flushed as with&n;  Z_SYNC_FLUSH, and the compression state is reset so that decompression can&n;  restart from this point if previous compressed data has been damaged or if&n;  random access is desired. Using Z_FULL_FLUSH too often can seriously degrade&n;  the compression.&n;&n;    If deflate returns with avail_out == 0, this function must be called again&n;  with the same value of the flush parameter and more output space (updated&n;  avail_out), until the flush is complete (deflate returns with non-zero&n;  avail_out).&n;&n;    If the parameter flush is set to Z_FINISH, pending input is processed,&n;  pending output is flushed and deflate returns with Z_STREAM_END if there&n;  was enough output space; if deflate returns with Z_OK, this function must be&n;  called again with Z_FINISH and more output space (updated avail_out) but no&n;  more input data, until it returns with Z_STREAM_END or an error. After&n;  deflate has returned Z_STREAM_END, the only possible operations on the&n;  stream are deflateReset or deflateEnd.&n;  &n;    Z_FINISH can be used immediately after deflateInit if all the compression&n;  is to be done in a single step. In this case, avail_out must be at least&n;  0.1% larger than avail_in plus 12 bytes.  If deflate does not return&n;  Z_STREAM_END, then it must be called again as described above.&n;&n;    deflate() sets strm-&gt;adler to the adler32 checksum of all input read&n;  so far (that is, total_in bytes).&n;&n;    deflate() may update data_type if it can make a good guess about&n;  the input data type (Z_ASCII or Z_BINARY). In doubt, the data is considered&n;  binary. This field is only for information purposes and does not affect&n;  the compression algorithm in any manner.&n;&n;    deflate() returns Z_OK if some progress has been made (more input&n;  processed or more output produced), Z_STREAM_END if all input has been&n;  consumed and all output has been produced (only when flush is set to&n;  Z_FINISH), Z_STREAM_ERROR if the stream state was inconsistent (for example&n;  if next_in or next_out was NULL), Z_BUF_ERROR if no progress is possible&n;  (for example avail_in or avail_out was zero).&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
multiline_comment|/* &n;ZEXTERN int ZEXPORT cramfs_inflateInit OF((z_streamp strm));&n;&n;     Initializes the internal stream state for decompression. The fields&n;   next_in, avail_in, zalloc, zfree and opaque must be initialized before by&n;   the caller. If next_in is not Z_NULL and avail_in is large enough (the exact&n;   value depends on the compression method), inflateInit determines the&n;   compression method from the zlib header and allocates all data structures&n;   accordingly; otherwise the allocation will be deferred to the first call of&n;   inflate.  If zalloc and zfree are set to Z_NULL, inflateInit updates them to&n;   use default allocation functions.&n;&n;     inflateInit returns Z_OK if success, Z_MEM_ERROR if there was not enough&n;   memory, Z_VERSION_ERROR if the zlib library version is incompatible with the&n;   version assumed by the caller.  msg is set to null if there is no error&n;   message. inflateInit does not perform any decompression apart from reading&n;   the zlib header if present: this will be done by inflate().  (So next_in and&n;   avail_in may be modified, but next_out and avail_out are unchanged.)&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflate
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
multiline_comment|/*&n;    inflate decompresses as much data as possible, and stops when the input&n;  buffer becomes empty or the output buffer becomes full. It may some&n;  introduce some output latency (reading input without producing any output)&n;  except when forced to flush.&n;&n;  The detailed semantics are as follows. inflate performs one or both of the&n;  following actions:&n;&n;  - Decompress more input starting at next_in and update next_in and avail_in&n;    accordingly. If not all input can be processed (because there is not&n;    enough room in the output buffer), next_in is updated and processing&n;    will resume at this point for the next call of inflate().&n;&n;  - Provide more output starting at next_out and update next_out and avail_out&n;    accordingly.  inflate() provides as much output as possible, until there&n;    is no more input data or no more space in the output buffer (see below&n;    about the flush parameter).&n;&n;  Before the call of inflate(), the application should ensure that at least&n;  one of the actions is possible, by providing more input and/or consuming&n;  more output, and updating the next_* and avail_* values accordingly.&n;  The application can consume the uncompressed output when it wants, for&n;  example when the output buffer is full (avail_out == 0), or after each&n;  call of inflate(). If inflate returns Z_OK and with zero avail_out, it&n;  must be called again after making room in the output buffer because there&n;  might be more output pending.&n;&n;    If the parameter flush is set to Z_SYNC_FLUSH, inflate flushes as much&n;  output as possible to the output buffer. The flushing behavior of inflate is&n;  not specified for values of the flush parameter other than Z_SYNC_FLUSH&n;  and Z_FINISH, but the current implementation actually flushes as much output&n;  as possible anyway.&n;&n;    inflate() should normally be called until it returns Z_STREAM_END or an&n;  error. However if all decompression is to be performed in a single step&n;  (a single call of inflate), the parameter flush should be set to&n;  Z_FINISH. In this case all pending input is processed and all pending&n;  output is flushed; avail_out must be large enough to hold all the&n;  uncompressed data. (The size of the uncompressed data may have been saved&n;  by the compressor for this purpose.) The next operation on this stream must&n;  be inflateEnd to deallocate the decompression state. The use of Z_FINISH&n;  is never required, but can be used to inform inflate that a faster routine&n;  may be used for the single inflate() call.&n;&n;     If a preset dictionary is needed at this point (see inflateSetDictionary&n;  below), inflate sets strm-adler to the adler32 checksum of the&n;  dictionary chosen by the compressor and returns Z_NEED_DICT; otherwise &n;  it sets strm-&gt;adler to the adler32 checksum of all output produced&n;  so far (that is, total_out bytes) and returns Z_OK, Z_STREAM_END or&n;  an error code as described below. At the end of the stream, inflate()&n;  checks that its computed adler32 checksum is equal to that saved by the&n;  compressor and returns Z_STREAM_END only if the checksum is correct.&n;&n;    inflate() returns Z_OK if some progress has been made (more input processed&n;  or more output produced), Z_STREAM_END if the end of the compressed data has&n;  been reached and all uncompressed output has been produced, Z_NEED_DICT if a&n;  preset dictionary is needed at this point, Z_DATA_ERROR if the input data was&n;  corrupted (input stream not conforming to the zlib format or incorrect&n;  adler32 checksum), Z_STREAM_ERROR if the stream structure was inconsistent&n;  (for example if next_in or next_out was NULL), Z_MEM_ERROR if there was not&n;  enough memory, Z_BUF_ERROR if no progress is possible or if there was not&n;  enough room in the output buffer when Z_FINISH is used. In the Z_DATA_ERROR&n;  case, the application may then call inflateSync to look for a good&n;  compression block.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflateEnd
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
multiline_comment|/*   &n;ZEXTERN int ZEXPORT deflateInit2 OF((z_streamp strm,&n;                                     int  level,&n;                                     int  method,&n;                                     int  windowBits,&n;                                     int  memLevel,&n;                                     int  strategy));&n;&n;     This is another version of deflateInit with more compression options. The&n;   fields next_in, zalloc, zfree and opaque must be initialized before by&n;   the caller.&n;&n;     The method parameter is the compression method. It must be Z_DEFLATED in&n;   this version of the library.&n;&n;     The windowBits parameter is the base two logarithm of the window size&n;   (the size of the history buffer).  It should be in the range 8..15 for this&n;   version of the library. Larger values of this parameter result in better&n;   compression at the expense of memory usage. The default value is 15 if&n;   deflateInit is used instead.&n;&n;     The memLevel parameter specifies how much memory should be allocated&n;   for the internal compression state. memLevel=1 uses minimum memory but&n;   is slow and reduces compression ratio; memLevel=9 uses maximum memory&n;   for optimal speed. The default value is 8. See zconf.h for total memory&n;   usage as a function of windowBits and memLevel.&n;&n;     The strategy parameter is used to tune the compression algorithm. Use the&n;   value Z_DEFAULT_STRATEGY for normal data, Z_FILTERED for data produced by a&n;   filter (or predictor), or Z_HUFFMAN_ONLY to force Huffman encoding only (no&n;   string match).  Filtered data consists mostly of small values with a&n;   somewhat random distribution. In this case, the compression algorithm is&n;   tuned to compress them better. The effect of Z_FILTERED is to force more&n;   Huffman coding and less string matching; it is somewhat intermediate&n;   between Z_DEFAULT and Z_HUFFMAN_ONLY. The strategy parameter only affects&n;   the compression ratio but not the correctness of the compressed output even&n;   if it is not set appropriately.&n;&n;      deflateInit2 returns Z_OK if success, Z_MEM_ERROR if there was not enough&n;   memory, Z_STREAM_ERROR if a parameter is invalid (such as an invalid&n;   method). msg is set to null if there is no error message.  deflateInit2 does&n;   not perform any compression: this will be done by deflate().&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
multiline_comment|/*&n;     Initializes the compression dictionary from the given byte sequence&n;   without producing any compressed output. This function must be called&n;   immediately after deflateInit, deflateInit2 or deflateReset, before any&n;   call of deflate. The compressor and decompressor must use exactly the same&n;   dictionary (see inflateSetDictionary).&n;&n;     The dictionary should consist of strings (byte sequences) that are likely&n;   to be encountered later in the data to be compressed, with the most commonly&n;   used strings preferably put towards the end of the dictionary. Using a&n;   dictionary is most useful when the data to be compressed is short and can be&n;   predicted with good accuracy; the data can then be compressed better than&n;   with the default empty dictionary.&n;&n;     Depending on the size of the compression data structures selected by&n;   deflateInit or deflateInit2, a part of the dictionary may in effect be&n;   discarded, for example if the dictionary is larger than the window size in&n;   deflate or deflate2. Thus the strings most likely to be useful should be&n;   put at the end of the dictionary, not at the front.&n;&n;     Upon return of this function, strm-&gt;adler is set to the Adler32 value&n;   of the dictionary; the decompressor may later use this value to determine&n;   which dictionary has been used by the compressor. (The Adler32 value&n;   applies to the whole dictionary even if only a subset of the dictionary is&n;   actually used by the compressor.)&n;&n;     deflateSetDictionary returns Z_OK if success, or Z_STREAM_ERROR if a&n;   parameter is invalid (such as NULL dictionary) or the stream state is&n;   inconsistent (for example if deflate has already been called for this stream&n;   or if the compression method is bsort). deflateSetDictionary does not&n;   perform any compression: this will be done by deflate().&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
multiline_comment|/*&n;     Sets the destination stream as a complete copy of the source stream.&n;&n;     This function can be useful when several compression strategies will be&n;   tried, for example when there are several ways of pre-processing the input&n;   data with a filter. The streams that will be discarded should then be freed&n;   by calling deflateEnd.  Note that deflateCopy duplicates the internal&n;   compression state which can be quite large, so this strategy is slow and&n;   can consume lots of memory.&n;&n;     deflateCopy returns Z_OK if success, Z_MEM_ERROR if there was not&n;   enough memory, Z_STREAM_ERROR if the source stream state was inconsistent&n;   (such as zalloc being NULL). msg is left unchanged in both source and&n;   destination.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
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
multiline_comment|/*&n;     Dynamically update the compression level and compression strategy.  The&n;   interpretation of level and strategy is as in deflateInit2.  This can be&n;   used to switch between compression and straight copy of the input data, or&n;   to switch to a different kind of input data requiring a different&n;   strategy. If the compression level is changed, the input available so far&n;   is compressed with the old level (and may be flushed); the new level will&n;   take effect only at the next call of deflate().&n;&n;     Before the call of deflateParams, the stream state must be set as for&n;   a call of deflate(), since the currently available input may have to&n;   be compressed and flushed. In particular, strm-&gt;avail_out must be non-zero.&n;&n;     deflateParams returns Z_OK if success, Z_STREAM_ERROR if the source&n;   stream state was inconsistent or if a parameter was invalid, Z_BUF_ERROR&n;   if strm-&gt;avail_out was zero.&n;*/
multiline_comment|/*   &n;ZEXTERN int ZEXPORT inflateInit2 OF((z_streamp strm,&n;                                     int  windowBits));&n;&n;     This is another version of inflateInit with an extra parameter. The&n;   fields next_in, avail_in, zalloc, zfree and opaque must be initialized&n;   before by the caller.&n;&n;     The windowBits parameter is the base two logarithm of the maximum window&n;   size (the size of the history buffer).  It should be in the range 8..15 for&n;   this version of the library. The default value is 15 if inflateInit is used&n;   instead. If a compressed stream with a larger window size is given as&n;   input, inflate() will return with the error code Z_DATA_ERROR instead of&n;   trying to allocate a larger window.&n;&n;      inflateInit2 returns Z_OK if success, Z_MEM_ERROR if there was not enough&n;   memory, Z_STREAM_ERROR if a parameter is invalid (such as a negative&n;   memLevel). msg is set to null if there is no error message.  inflateInit2&n;   does not perform any decompression apart from reading the zlib header if&n;   present: this will be done by inflate(). (So next_in and avail_in may be&n;   modified, but next_out and avail_out are unchanged.)&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
multiline_comment|/*&n;     Initializes the decompression dictionary from the given uncompressed byte&n;   sequence. This function must be called immediately after a call of inflate&n;   if this call returned Z_NEED_DICT. The dictionary chosen by the compressor&n;   can be determined from the Adler32 value returned by this call of&n;   inflate. The compressor and decompressor must use exactly the same&n;   dictionary (see deflateSetDictionary).&n;&n;     inflateSetDictionary returns Z_OK if success, Z_STREAM_ERROR if a&n;   parameter is invalid (such as NULL dictionary) or the stream state is&n;   inconsistent, Z_DATA_ERROR if the given dictionary doesn&squot;t match the&n;   expected one (incorrect Adler32 value). inflateSetDictionary does not&n;   perform any decompression: this will be done by subsequent calls of&n;   inflate().&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflateSync
id|OF
c_func
(paren
(paren
id|z_streamp
id|strm
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;    Skips invalid compressed data until a full flush point (see above the&n;  description of deflate with Z_FULL_FLUSH) can be found, or until all&n;  available input is skipped. No output is provided.&n;&n;    inflateSync returns Z_OK if a full flush point has been found, Z_BUF_ERROR&n;  if no more input was provided, Z_DATA_ERROR if no flush point has been found,&n;  or Z_STREAM_ERROR if the stream structure was inconsistent. In the success&n;  case, the application may save the current current value of total_in which&n;  indicates where valid compressed data was found. In the error case, the&n;  application may repeatedly call inflateSync, providing more input each time,&n;  until success or end of the input data.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflateReset
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
multiline_comment|/* utility functions */
multiline_comment|/*&n;     The following utility functions are implemented on top of the&n;   basic stream-oriented functions. To simplify the interface, some&n;   default options are assumed (compression level and memory usage,&n;   standard memory allocation functions). The source code of these&n;   utility functions can easily be modified if you need special options.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
id|compress2
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
comma
r_int
id|level
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Compresses the source buffer into the destination buffer. The level&n;   parameter has the same meaning as in deflateInit.  sourceLen is the byte&n;   length of the source buffer. Upon entry, destLen is the total size of the&n;   destination buffer, which must be at least 0.1% larger than sourceLen plus&n;   12 bytes. Upon exit, destLen is the actual size of the compressed buffer.&n;&n;     compress2 returns Z_OK if success, Z_MEM_ERROR if there was not enough&n;   memory, Z_BUF_ERROR if there was not enough room in the output buffer,&n;   Z_STREAM_ERROR if the level parameter is invalid.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
id|gzFile
id|ZEXPORT
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
multiline_comment|/*&n;     Opens a gzip (.gz) file for reading or writing. The mode parameter&n;   is as in fopen (&quot;rb&quot; or &quot;wb&quot;) but can also include a compression level&n;   (&quot;wb9&quot;) or a strategy: &squot;f&squot; for filtered data as in &quot;wb6f&quot;, &squot;h&squot; for&n;   Huffman only compression as in &quot;wb1h&quot;. (See the description&n;   of deflateInit2 for more information about the strategy parameter.)&n;&n;     gzopen can be used to read a file which is not in gzip format; in this&n;   case gzread will directly read from the file without decompression.&n;&n;     gzopen returns NULL if the file could not be opened or if there was&n;   insufficient memory to allocate the (de)compression state; errno&n;   can be checked to distinguish the two cases (if errno is zero, the&n;   zlib error is Z_MEM_ERROR).  */
id|ZEXTERN
id|gzFile
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
id|gzsetparams
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_int
id|level
comma
r_int
id|strategy
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Dynamically update the compression level or strategy. See the description&n;   of deflateInit2 for the meaning of these parameters.&n;     gzsetparams returns Z_OK if success, or Z_STREAM_ERROR if the file was not&n;   opened for writing.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORTVA
id|gzprintf
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_const
r_char
op_star
id|format
comma
dot
dot
dot
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Converts, formats, and writes the args to the compressed file under&n;   control of the format string, as in fprintf. gzprintf returns the number of&n;   uncompressed bytes actually written (0 in case of error).&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|gzputs
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_const
r_char
op_star
id|s
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;      Writes the given null-terminated string to the compressed file, excluding&n;   the terminating null character.&n;      gzputs returns the number of characters written, or -1 in case of error.&n;*/
id|ZEXTERN
r_char
op_star
id|ZEXPORT
id|gzgets
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;      Reads bytes from the compressed file until len-1 characters are read, or&n;   a newline character is read and transferred to buf, or an end-of-file&n;   condition is encountered.  The string is then terminated with a null&n;   character.&n;      gzgets returns buf, or Z_NULL in case of error.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|gzputc
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
r_int
id|c
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;      Writes c, converted to an unsigned char, into the compressed file.&n;   gzputc returns the value that was written, or -1 in case of error.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|gzgetc
id|OF
c_func
(paren
(paren
id|gzFile
id|file
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;      Reads one byte from the compressed file. gzgetc returns this byte&n;   or -1 in case of end of file or error.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
id|z_off_t
id|ZEXPORT
id|gzseek
id|OF
c_func
(paren
(paren
id|gzFile
id|file
comma
id|z_off_t
id|offset
comma
r_int
id|whence
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;      Sets the starting position for the next gzread or gzwrite on the&n;   given compressed file. The offset represents a number of bytes in the&n;   uncompressed data stream. The whence parameter is defined as in lseek(2);&n;   the value SEEK_END is not supported.&n;     If the file is opened for reading, this function is emulated but can be&n;   extremely slow. If the file is opened for writing, only forward seeks are&n;   supported; gzseek then compresses a sequence of zeroes up to the new&n;   starting position.&n;&n;      gzseek returns the resulting offset location as measured in bytes from&n;   the beginning of the uncompressed stream, or -1 in case of error, in&n;   particular if the file is opened for writing and the new starting position&n;   would be before the current position.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|gzrewind
id|OF
c_func
(paren
(paren
id|gzFile
id|file
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Rewinds the given file. This function is supported only for reading.&n;&n;   gzrewind(file) is equivalent to (int)gzseek(file, 0L, SEEK_SET)&n;*/
id|ZEXTERN
id|z_off_t
id|ZEXPORT
id|gztell
id|OF
c_func
(paren
(paren
id|gzFile
id|file
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Returns the starting position for the next gzread or gzwrite on the&n;   given compressed file. This position represents a number of bytes in the&n;   uncompressed data stream.&n;&n;   gztell(file) is equivalent to gzseek(file, 0L, SEEK_CUR)&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
id|gzeof
id|OF
c_func
(paren
(paren
id|gzFile
id|file
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;     Returns 1 when EOF has previously been detected reading the given&n;   input stream, otherwise zero.&n;*/
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_const
r_char
op_star
id|ZEXPORT
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
id|ZEXTERN
id|uLong
id|ZEXPORT
id|cramfs_adler32
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
id|ZEXTERN
id|uLong
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflateInit_
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
id|ZEXTERN
r_int
id|ZEXPORT
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
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflateInit2_
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
DECL|macro|cramfs_inflateInit
mdefine_line|#define cramfs_inflateInit(strm) &bslash;&n;        cramfs_inflateInit_((strm),                ZLIB_VERSION, sizeof(z_stream))
DECL|macro|deflateInit2
mdefine_line|#define deflateInit2(strm, level, method, windowBits, memLevel, strategy) &bslash;&n;        deflateInit2_((strm),(level),(method),(windowBits),(memLevel),&bslash;&n;                      (strategy),           ZLIB_VERSION, sizeof(z_stream))
DECL|macro|inflateInit2
mdefine_line|#define inflateInit2(strm, windowBits) &bslash;&n;        cramfs_inflateInit2_((strm), (windowBits), ZLIB_VERSION, sizeof(z_stream))
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
id|ZEXTERN
r_const
r_char
op_star
id|ZEXPORT
id|zError
id|OF
c_func
(paren
(paren
r_int
id|err
)paren
)paren
suffix:semicolon
id|ZEXTERN
r_int
id|ZEXPORT
id|cramfs_inflateSyncPoint
id|OF
c_func
(paren
(paren
id|z_streamp
id|z
)paren
)paren
suffix:semicolon
id|ZEXTERN
r_const
id|uLongf
op_star
id|ZEXPORT
id|get_crc_table
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* _ZLIB_H */
eof
