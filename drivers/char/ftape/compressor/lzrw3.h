macro_line|#ifndef _LZRW3_H
DECL|macro|_LZRW3_H
mdefine_line|#define _LZRW3_H
multiline_comment|/*&n; * $Source: /homes/cvs/ftape-stacked/ftape/compressor/lzrw3.h,v $&n; * $Revision: 1.1 $&n; * $Date: 1997/10/05 19:12:30 $&n; *&n; *  include files for lzrw3. Only slighty modified from the original&n; *  version. Assembles the three include files compress.h, port.h and&n; *  fastcopy.h from the original lzrw3 package.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/*                                 COMPRESS.H                                 */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/* Author : Ross Williams.                                                    */
multiline_comment|/* Date   : December 1989.                                                    */
multiline_comment|/*                                                                            */
multiline_comment|/* This header file defines the interface to a set of functions called        */
multiline_comment|/* &squot;compress&squot;, each member of which implements a particular data compression  */
multiline_comment|/* algorithm.                                                                 */
multiline_comment|/*                                                                            */
multiline_comment|/* Normally in C programming, for each .H file, there is a corresponding .C   */
multiline_comment|/* file that implements the functions promised in the .H file.                */
multiline_comment|/* Here, there are many .C files corresponding to this header file.           */
multiline_comment|/* Each comforming implementation file contains a single function             */
multiline_comment|/* called &squot;compress&squot; that implements a single data compression                */
multiline_comment|/* algorithm that conforms with the interface specified in this header file.  */
multiline_comment|/* Only one algorithm can be linked in at a time in this organization.        */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/*                    DEFINITION OF FUNCTION COMPRESS                         */
multiline_comment|/*                    ===============================                         */
multiline_comment|/*                                                                            */
multiline_comment|/* Summary of Function Compress                                               */
multiline_comment|/* ----------------------------                                               */
multiline_comment|/* The action that &squot;compress&squot; takes depends on its first argument called      */
multiline_comment|/* &squot;action&squot;.  The function provides three actions:                            */
multiline_comment|/*                                                                            */
multiline_comment|/*    - Return information about the algorithm.                               */
multiline_comment|/*    - Compress   a block of memory.                                         */
multiline_comment|/*    - Decompress a block of memory.                                         */
multiline_comment|/*                                                                            */
multiline_comment|/* Parameters                                                                 */
multiline_comment|/* ----------                                                                 */
multiline_comment|/* See the formal C definition later for a description of the parameters.     */
multiline_comment|/*                                                                            */
multiline_comment|/* Constants                                                                  */
multiline_comment|/* ---------                                                                  */
multiline_comment|/* COMPRESS_OVERRUN: The constant COMPRESS_OVERRUN defines by how many bytes  */
multiline_comment|/* an algorithm is allowed to expand a block during a compression operation.  */
multiline_comment|/*                                                                            */
multiline_comment|/* Although compression algorithms usually compress data, there will always   */
multiline_comment|/* be data that a given compressor will expand (this can be proven).          */
multiline_comment|/* Fortunately, the degree of expansion can be limited to a single bit, by    */
multiline_comment|/* copying over the input data if the data gets bigger during compression.    */
multiline_comment|/* To allow for this possibility, the first bit of a compressed               */
multiline_comment|/* representation can be used as a flag indicating whether the                */
multiline_comment|/* input data was copied over, or truly compressed. In practice, the first    */
multiline_comment|/* byte would be used to store this bit so as to maintain byte alignment.     */
multiline_comment|/*                                                                            */
multiline_comment|/* Unfortunately, in general, the only way to tell if an algorithm will       */
multiline_comment|/* expand a particular block of data is to run the algorithm on the data.     */
multiline_comment|/* If the algorithm does not continuously monitor how many output bytes it    */
multiline_comment|/* has written, it might write an output block far larger than the input      */
multiline_comment|/* block before realizing that it has done so.                                */
multiline_comment|/* On the other hand, continuous checks on output length are inefficient.     */
multiline_comment|/*                                                                            */
multiline_comment|/* To cater for all these problems, this interface definition:                */
multiline_comment|/* &gt; Allows a compression algorithm to return an output block that is up to   */
multiline_comment|/*   COMPRESS_OVERRUN bytes longer than the input block.                      */
multiline_comment|/* &gt; Allows a compression algorithm to write up to COMPRESS_OVERRUN bytes     */
multiline_comment|/*   more than the length of the input block to the memory of the output      */
multiline_comment|/*   block regardless of the length of the output block eventually returned.  */
multiline_comment|/*   This allows an algorithm to overrun the length of the input block in the */
multiline_comment|/*   output block by up to COMPRESS_OVERRUN bytes between expansion checks.   */
multiline_comment|/*                                                                            */
multiline_comment|/* The problem does not arise for decompression.                              */
multiline_comment|/*                                                                            */
multiline_comment|/* Identity Action                                                            */
multiline_comment|/* ---------------                                                            */
multiline_comment|/* &gt; action must be COMPRESS_ACTION_IDENTITY.                                 */
multiline_comment|/* &gt; p_dst_len must point to a longword to receive a longword address.        */
multiline_comment|/* &gt; The value of the other parameters does not matter.                       */
multiline_comment|/* &gt; After execution, the longword that p_dst_len points to will be a pointer */
multiline_comment|/*   to a structure of type compress_identity.                                */
multiline_comment|/*   Thus, for example, after the call, (*p_dst_len)-&gt;memory will return the  */
multiline_comment|/*   number of bytes of working memory that the algorithm requires to run.    */
multiline_comment|/* &gt; The values of the identity structure returned are fixed constant         */
multiline_comment|/*   attributes of the algorithm and must not vary from call to call.         */
multiline_comment|/*                                                                            */
multiline_comment|/* Common Requirements for Compression and Decompression Actions              */
multiline_comment|/* -------------------------------------------------------------              */
multiline_comment|/* &gt; wrk_mem must point to an unused block of memory of a length specified in */
multiline_comment|/*   the algorithm&squot;s identity block. The identity block can be obtained by    */
multiline_comment|/*   making a separate call to compress, specifying the identity action.      */
multiline_comment|/* &gt; The INPUT BLOCK is defined to be Memory[src_addr,src_addr+src_len-1].    */
multiline_comment|/* &gt; dst_len will be used to denote *p_dst_len.                               */
multiline_comment|/* &gt; dst_len is not read by compress, only written.                           */
multiline_comment|/* &gt; The value of dst_len is defined only upon termination.                   */
multiline_comment|/* &gt; The OUTPUT BLOCK is defined to be Memory[dst_addr,dst_addr+dst_len-1].   */
multiline_comment|/*                                                                            */
multiline_comment|/* Compression Action                                                         */
multiline_comment|/* ------------------                                                         */
multiline_comment|/* &gt; action must be COMPRESS_ACTION_COMPRESS.                                 */
multiline_comment|/* &gt; src_len must be in the range [0,COMPRESS_MAX_ORG].                       */
multiline_comment|/* &gt; The OUTPUT ZONE is defined to be                                         */
multiline_comment|/*      Memory[dst_addr,dst_addr+src_len-1+COMPRESS_OVERRUN].                 */
multiline_comment|/* &gt; The function can modify any part of the output zone regardless of the    */
multiline_comment|/*   final length of the output block.                                        */
multiline_comment|/* &gt; The input block and the output zone must not overlap.                    */
multiline_comment|/* &gt; dst_len will be in the range [0,src_len+COMPRESS_OVERRUN].               */
multiline_comment|/* &gt; dst_len will be in the range [0,COMPRESS_MAX_COM] (from prev fact).      */
multiline_comment|/* &gt; The output block will consist of a representation of the input block.    */
multiline_comment|/*                                                                            */
multiline_comment|/* Decompression Action                                                       */
multiline_comment|/* --------------------                                                       */
multiline_comment|/* &gt; action must be COMPRESS_ACTION_DECOMPRESS.                               */
multiline_comment|/* &gt; The input block must be the result of an earlier compression operation.  */
multiline_comment|/* &gt; If the previous fact is true, the following facts must also be true:     */
multiline_comment|/*   &gt; src_len will be in the range [0,COMPRESS_MAX_COM].                     */
multiline_comment|/*   &gt; dst_len will be in the range [0,COMPRESS_MAX_ORG].                     */
multiline_comment|/* &gt; The input and output blocks must not overlap.                            */
multiline_comment|/* &gt; Only the output block is modified.                                       */
multiline_comment|/* &gt; Upon termination, the output block will consist of the bytes contained   */
multiline_comment|/*   in the input block passed to the earlier compression operation.          */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/*                                    PORT.H                                  */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
multiline_comment|/*                                                                            */
multiline_comment|/* This module contains macro definitions and types that are likely to        */
multiline_comment|/* change between computers.                                                  */
multiline_comment|/*                                                                            */
multiline_comment|/******************************************************************************/
macro_line|#ifndef DONE_PORT       /* Only do this if not previously done.               */
macro_line|#ifdef THINK_C
DECL|macro|UBYTE
mdefine_line|#define UBYTE unsigned char      /* Unsigned byte                       */
DECL|macro|UWORD
mdefine_line|#define UWORD unsigned int       /* Unsigned word (2 bytes)             */
DECL|macro|ULONG
mdefine_line|#define ULONG unsigned long      /* Unsigned word (4 bytes)             */
DECL|macro|BOOL
mdefine_line|#define BOOL  unsigned char      /* Boolean                             */
DECL|macro|FOPEN_BINARY_READ
mdefine_line|#define FOPEN_BINARY_READ  &quot;rb&quot;  /* Mode string for binary reading.     */
DECL|macro|FOPEN_BINARY_WRITE
mdefine_line|#define FOPEN_BINARY_WRITE &quot;wb&quot;  /* Mode string for binary writing.     */
DECL|macro|FOPEN_TEXT_APPEND
mdefine_line|#define FOPEN_TEXT_APPEND  &quot;a&quot;   /* Mode string for text appending.     */
DECL|macro|REAL
mdefine_line|#define REAL double              /* USed for floating point stuff.      */
macro_line|#endif
macro_line|#if defined(LINUX) || defined(linux)
DECL|macro|UBYTE
mdefine_line|#define UBYTE __u8               /* Unsigned byte                       */
DECL|macro|UWORD
mdefine_line|#define UWORD __u16              /* Unsigned word (2 bytes)             */
DECL|macro|ULONG
mdefine_line|#define ULONG __u32              /* Unsigned word (4 bytes)             */
DECL|macro|LONG
mdefine_line|#define LONG  __s32              /* Signed   word (4 bytes)             */
DECL|macro|BOOL
mdefine_line|#define BOOL  is not used here   /* Boolean                             */
DECL|macro|FOPEN_BINARY_READ
mdefine_line|#define FOPEN_BINARY_READ  not used  /* Mode string for binary reading. */
DECL|macro|FOPEN_BINARY_WRITE
mdefine_line|#define FOPEN_BINARY_WRITE not used  /* Mode string for binary writing. */
DECL|macro|FOPEN_TEXT_APPEND
mdefine_line|#define FOPEN_TEXT_APPEND  not used  /* Mode string for text appending. */
DECL|macro|REAL
mdefine_line|#define REAL not used                /* USed for floating point stuff.  */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#endif
DECL|macro|DONE_PORT
mdefine_line|#define DONE_PORT                   /* Don&squot;t do all this again.            */
DECL|macro|MALLOC_FAIL
mdefine_line|#define MALLOC_FAIL NULL            /* Failure status from malloc()        */
DECL|macro|LOCAL
mdefine_line|#define LOCAL static                /* For non-exported routines.          */
DECL|macro|EXPORT
mdefine_line|#define EXPORT                      /* Signals exported function.          */
DECL|macro|then
mdefine_line|#define then                        /* Useful for aligning ifs.            */
macro_line|#endif
multiline_comment|/******************************************************************************/
multiline_comment|/*                              End of PORT.H                                 */
multiline_comment|/******************************************************************************/
DECL|macro|COMPRESS_ACTION_IDENTITY
mdefine_line|#define COMPRESS_ACTION_IDENTITY   0
DECL|macro|COMPRESS_ACTION_COMPRESS
mdefine_line|#define COMPRESS_ACTION_COMPRESS   1
DECL|macro|COMPRESS_ACTION_DECOMPRESS
mdefine_line|#define COMPRESS_ACTION_DECOMPRESS 2
DECL|macro|COMPRESS_OVERRUN
mdefine_line|#define COMPRESS_OVERRUN 1024
DECL|macro|COMPRESS_MAX_COM
mdefine_line|#define COMPRESS_MAX_COM 0x70000000
DECL|macro|COMPRESS_MAX_ORG
mdefine_line|#define COMPRESS_MAX_ORG (COMPRESS_MAX_COM-COMPRESS_OVERRUN)
DECL|macro|COMPRESS_MAX_STRLEN
mdefine_line|#define COMPRESS_MAX_STRLEN 255
multiline_comment|/* The following structure provides information about the algorithm.         */
multiline_comment|/* &gt; The top bit of id must be zero. The remaining bits must be chosen by    */
multiline_comment|/*   the author of the algorithm by tossing a coin 31 times.                 */
multiline_comment|/* &gt; The amount of memory requested by the algorithm is specified in bytes   */
multiline_comment|/*   and must be in the range [0,0x70000000].                                */
multiline_comment|/* &gt; All strings s must be such that strlen(s)&lt;=COMPRESS_MAX_STRLEN.         */
DECL|struct|compress_identity
r_struct
id|compress_identity
(brace
DECL|member|id
id|ULONG
id|id
suffix:semicolon
multiline_comment|/* Identifying number of algorithm.            */
DECL|member|memory
id|ULONG
id|memory
suffix:semicolon
multiline_comment|/* Number of bytes of working memory required. */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Name of algorithm.                          */
DECL|member|version
r_char
op_star
id|version
suffix:semicolon
multiline_comment|/* Version number.                             */
DECL|member|date
r_char
op_star
id|date
suffix:semicolon
multiline_comment|/* Date of release of this version.            */
DECL|member|copyright
r_char
op_star
id|copyright
suffix:semicolon
multiline_comment|/* Copyright message.                          */
DECL|member|author
r_char
op_star
id|author
suffix:semicolon
multiline_comment|/* Author of algorithm.                        */
DECL|member|affiliation
r_char
op_star
id|affiliation
suffix:semicolon
multiline_comment|/* Affiliation of author.                      */
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
multiline_comment|/* Where the algorithm can be obtained.        */
)brace
suffix:semicolon
r_void
id|lzrw3_compress
c_func
(paren
multiline_comment|/* Single function interface to compression algorithm. */
id|UWORD
id|action
comma
multiline_comment|/* Action to be performed.                             */
id|UBYTE
op_star
id|wrk_mem
comma
multiline_comment|/* Working memory temporarily given to routine to use. */
id|UBYTE
op_star
id|src_adr
comma
multiline_comment|/* Address of input  data.                             */
id|LONG
id|src_len
comma
multiline_comment|/* Length  of input  data.                             */
id|UBYTE
op_star
id|dst_adr
comma
multiline_comment|/* Address of output data.                             */
r_void
op_star
id|p_dst_len
multiline_comment|/* Pointer to a longword where routine will write:     */
multiline_comment|/*    If action=..IDENTITY   =&gt; Adr of id structure.   */
multiline_comment|/*    If action=..COMPRESS   =&gt; Length of output data. */
multiline_comment|/*    If action=..DECOMPRESS =&gt; Length of output data. */
)paren
suffix:semicolon
multiline_comment|/******************************************************************************/
multiline_comment|/*                             End of COMPRESS.H                              */
multiline_comment|/******************************************************************************/
multiline_comment|/******************************************************************************/
multiline_comment|/*                                  fast_copy.h                               */
multiline_comment|/******************************************************************************/
multiline_comment|/* This function copies a block of memory very quickly.                       */
multiline_comment|/* The exact speed depends on the relative alignment of the blocks of memory. */
multiline_comment|/* PRE  : 0&lt;=src_len&lt;=(2^32)-1 .                                              */
multiline_comment|/* PRE  : Source and destination blocks must not overlap.                     */
multiline_comment|/* POST : MEM[dst_adr,dst_adr+src_len-1]=MEM[src_adr,src_adr+src_len-1].      */
multiline_comment|/* POST : MEM[dst_adr,dst_adr+src_len-1] is the only memory changed.          */
DECL|macro|fast_copy
mdefine_line|#define fast_copy(src,dst,len) memcpy(dst,src,len)
multiline_comment|/******************************************************************************/
multiline_comment|/*                               End of fast_copy.h                           */
multiline_comment|/******************************************************************************/
macro_line|#endif
eof
