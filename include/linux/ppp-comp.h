multiline_comment|/*&n; * ppp-comp.h - Definitions for doing PPP packet compression.&n; *&n; * Copyright (c) 1994 The Australian National University.&n; * All rights reserved.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied. The Australian National University&n; * makes no representations about the suitability of this software for&n; * any purpose.&n; *&n; * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY&n; * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES&n; * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF&n; * THE AUSTRALIAN NATIONAL UNIVERSITY HAVE BEEN ADVISED OF THE POSSIBILITY&n; * OF SUCH DAMAGE.&n; *&n; * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO&n; * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,&n; * OR MODIFICATIONS.&n; *&n; * $Id: ppp-comp.h,v 1.6 1997/11/27 06:04:44 paulus Exp $&n; */
multiline_comment|/*&n; *  ==FILEVERSION 980319==&n; *&n; *  NOTE TO MAINTAINERS:&n; *     If you modify this file at all, please set the above date.&n; *     ppp-comp.h is shipped with a PPP distribution as well as with the kernel;&n; *     if everyone increases the FILEVERSION number above, then scripts&n; *     can do the right thing when deciding whether to install a new ppp-comp.h&n; *     file.  Don&squot;t change the format of that line otherwise, so the&n; *     installation script can recognize it.&n; */
macro_line|#ifndef _NET_PPP_COMP_H
DECL|macro|_NET_PPP_COMP_H
mdefine_line|#define _NET_PPP_COMP_H
multiline_comment|/*&n; * The following symbols control whether we include code for&n; * various compression methods.&n; */
macro_line|#ifndef DO_BSD_COMPRESS
DECL|macro|DO_BSD_COMPRESS
mdefine_line|#define DO_BSD_COMPRESS&t;1&t;/* by default, include BSD-Compress */
macro_line|#endif
macro_line|#ifndef DO_DEFLATE
DECL|macro|DO_DEFLATE
mdefine_line|#define DO_DEFLATE&t;1&t;/* by default, include Deflate */
macro_line|#endif
DECL|macro|DO_PREDICTOR_1
mdefine_line|#define DO_PREDICTOR_1&t;0
DECL|macro|DO_PREDICTOR_2
mdefine_line|#define DO_PREDICTOR_2&t;0
multiline_comment|/*&n; * Structure giving methods for compression/decompression.&n; */
DECL|struct|compressor
r_struct
id|compressor
(brace
DECL|member|compress_proto
r_int
id|compress_proto
suffix:semicolon
multiline_comment|/* CCP compression protocol number */
multiline_comment|/* Allocate space for a compressor (transmit side) */
DECL|member|comp_alloc
r_void
op_star
(paren
op_star
id|comp_alloc
)paren
(paren
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
)paren
suffix:semicolon
multiline_comment|/* Free space used by a compressor */
DECL|member|comp_free
r_void
(paren
op_star
id|comp_free
)paren
(paren
r_void
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/* Initialize a compressor */
DECL|member|comp_init
r_int
(paren
op_star
id|comp_init
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
comma
r_int
id|unit
comma
r_int
id|opthdr
comma
r_int
id|debug
)paren
suffix:semicolon
multiline_comment|/* Reset a compressor */
DECL|member|comp_reset
r_void
(paren
op_star
id|comp_reset
)paren
(paren
r_void
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/* Compress a packet */
DECL|member|compress
r_int
(paren
op_star
id|compress
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|rptr
comma
r_int
r_char
op_star
id|obuf
comma
r_int
id|isize
comma
r_int
id|osize
)paren
suffix:semicolon
multiline_comment|/* Return compression statistics */
DECL|member|comp_stat
r_void
(paren
op_star
id|comp_stat
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|compstat
op_star
id|stats
)paren
suffix:semicolon
multiline_comment|/* Allocate space for a decompressor (receive side) */
DECL|member|decomp_alloc
r_void
op_star
(paren
op_star
id|decomp_alloc
)paren
(paren
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
)paren
suffix:semicolon
multiline_comment|/* Free space used by a decompressor */
DECL|member|decomp_free
r_void
(paren
op_star
id|decomp_free
)paren
(paren
r_void
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/* Initialize a decompressor */
DECL|member|decomp_init
r_int
(paren
op_star
id|decomp_init
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
comma
r_int
id|unit
comma
r_int
id|opthdr
comma
r_int
id|mru
comma
r_int
id|debug
)paren
suffix:semicolon
multiline_comment|/* Reset a decompressor */
DECL|member|decomp_reset
r_void
(paren
op_star
id|decomp_reset
)paren
(paren
r_void
op_star
id|state
)paren
suffix:semicolon
multiline_comment|/* Decompress a packet. */
DECL|member|decompress
r_int
(paren
op_star
id|decompress
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|ibuf
comma
r_int
id|isize
comma
r_int
r_char
op_star
id|obuf
comma
r_int
id|osize
)paren
suffix:semicolon
multiline_comment|/* Update state for an incompressible packet received */
DECL|member|incomp
r_void
(paren
op_star
id|incomp
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|ibuf
comma
r_int
id|icnt
)paren
suffix:semicolon
multiline_comment|/* Return decompression statistics */
DECL|member|decomp_stat
r_void
(paren
op_star
id|decomp_stat
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|compstat
op_star
id|stats
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The return value from decompress routine is the length of the&n; * decompressed packet if successful, otherwise DECOMP_ERROR&n; * or DECOMP_FATALERROR if an error occurred.&n; * &n; * We need to make this distinction so that we can disable certain&n; * useful functionality, namely sending a CCP reset-request as a result&n; * of an error detected after decompression.  This is to avoid infringing&n; * a patent held by Motorola.&n; * Don&squot;t you just lurve software patents.&n; */
DECL|macro|DECOMP_ERROR
mdefine_line|#define DECOMP_ERROR&t;&t;-1&t;/* error detected before decomp. */
DECL|macro|DECOMP_FATALERROR
mdefine_line|#define DECOMP_FATALERROR&t;-2&t;/* error detected after decomp. */
multiline_comment|/*&n; * CCP codes.&n; */
DECL|macro|CCP_CONFREQ
mdefine_line|#define CCP_CONFREQ&t;1
DECL|macro|CCP_CONFACK
mdefine_line|#define CCP_CONFACK&t;2
DECL|macro|CCP_TERMREQ
mdefine_line|#define CCP_TERMREQ&t;5
DECL|macro|CCP_TERMACK
mdefine_line|#define CCP_TERMACK&t;6
DECL|macro|CCP_RESETREQ
mdefine_line|#define CCP_RESETREQ&t;14
DECL|macro|CCP_RESETACK
mdefine_line|#define CCP_RESETACK&t;15
multiline_comment|/*&n; * Max # bytes for a CCP option&n; */
DECL|macro|CCP_MAX_OPTION_LENGTH
mdefine_line|#define CCP_MAX_OPTION_LENGTH&t;32
multiline_comment|/*&n; * Parts of a CCP packet.&n; */
DECL|macro|CCP_CODE
mdefine_line|#define CCP_CODE(dp)&t;&t;((dp)[0])
DECL|macro|CCP_ID
mdefine_line|#define CCP_ID(dp)&t;&t;((dp)[1])
DECL|macro|CCP_LENGTH
mdefine_line|#define CCP_LENGTH(dp)&t;&t;(((dp)[2] &lt;&lt; 8) + (dp)[3])
DECL|macro|CCP_HDRLEN
mdefine_line|#define CCP_HDRLEN&t;&t;4
DECL|macro|CCP_OPT_CODE
mdefine_line|#define CCP_OPT_CODE(dp)&t;((dp)[0])
DECL|macro|CCP_OPT_LENGTH
mdefine_line|#define CCP_OPT_LENGTH(dp)&t;((dp)[1])
DECL|macro|CCP_OPT_MINLEN
mdefine_line|#define CCP_OPT_MINLEN&t;&t;2
multiline_comment|/*&n; * Definitions for BSD-Compress.&n; */
DECL|macro|CI_BSD_COMPRESS
mdefine_line|#define CI_BSD_COMPRESS&t;&t;21&t;/* config. option for BSD-Compress */
DECL|macro|CILEN_BSD_COMPRESS
mdefine_line|#define CILEN_BSD_COMPRESS&t;3&t;/* length of config. option */
multiline_comment|/* Macros for handling the 3rd byte of the BSD-Compress config option. */
DECL|macro|BSD_NBITS
mdefine_line|#define BSD_NBITS(x)&t;&t;((x) &amp; 0x1F)&t;/* number of bits requested */
DECL|macro|BSD_VERSION
mdefine_line|#define BSD_VERSION(x)&t;&t;((x) &gt;&gt; 5)&t;/* version of option format */
DECL|macro|BSD_CURRENT_VERSION
mdefine_line|#define BSD_CURRENT_VERSION&t;1&t;&t;/* current version number */
DECL|macro|BSD_MAKE_OPT
mdefine_line|#define BSD_MAKE_OPT(v, n)&t;(((v) &lt;&lt; 5) | (n))
DECL|macro|BSD_MIN_BITS
mdefine_line|#define BSD_MIN_BITS&t;&t;9&t;/* smallest code size supported */
DECL|macro|BSD_MAX_BITS
mdefine_line|#define BSD_MAX_BITS&t;&t;15&t;/* largest code size supported */
multiline_comment|/*&n; * Definitions for Deflate.&n; */
DECL|macro|CI_DEFLATE
mdefine_line|#define CI_DEFLATE&t;&t;26&t;/* config option for Deflate */
DECL|macro|CI_DEFLATE_DRAFT
mdefine_line|#define CI_DEFLATE_DRAFT&t;24&t;/* value used in original draft RFC */
DECL|macro|CILEN_DEFLATE
mdefine_line|#define CILEN_DEFLATE&t;&t;4&t;/* length of its config option */
DECL|macro|DEFLATE_MIN_SIZE
mdefine_line|#define DEFLATE_MIN_SIZE&t;8
DECL|macro|DEFLATE_MAX_SIZE
mdefine_line|#define DEFLATE_MAX_SIZE&t;15
DECL|macro|DEFLATE_METHOD_VAL
mdefine_line|#define DEFLATE_METHOD_VAL&t;8
DECL|macro|DEFLATE_SIZE
mdefine_line|#define DEFLATE_SIZE(x)&t;&t;(((x) &gt;&gt; 4) + DEFLATE_MIN_SIZE)
DECL|macro|DEFLATE_METHOD
mdefine_line|#define DEFLATE_METHOD(x)&t;((x) &amp; 0x0F)
DECL|macro|DEFLATE_MAKE_OPT
mdefine_line|#define DEFLATE_MAKE_OPT(w)&t;((((w) - DEFLATE_MIN_SIZE) &lt;&lt; 4) &bslash;&n;&t;&t;&t;&t; + DEFLATE_METHOD_VAL)
DECL|macro|DEFLATE_CHK_SEQUENCE
mdefine_line|#define DEFLATE_CHK_SEQUENCE&t;0
multiline_comment|/*&n; * Definitions for other, as yet unsupported, compression methods.&n; */
DECL|macro|CI_PREDICTOR_1
mdefine_line|#define CI_PREDICTOR_1&t;&t;1&t;/* config option for Predictor-1 */
DECL|macro|CILEN_PREDICTOR_1
mdefine_line|#define CILEN_PREDICTOR_1&t;2&t;/* length of its config option */
DECL|macro|CI_PREDICTOR_2
mdefine_line|#define CI_PREDICTOR_2&t;&t;2&t;/* config option for Predictor-2 */
DECL|macro|CILEN_PREDICTOR_2
mdefine_line|#define CILEN_PREDICTOR_2&t;2&t;/* length of its config option */
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|ppp_register_compressor
c_func
(paren
r_struct
id|compressor
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ppp_unregister_compressor
c_func
(paren
r_struct
id|compressor
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _NET_PPP_COMP_H */
eof
