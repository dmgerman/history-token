multiline_comment|/* inflate.c -- zlib interface to inflate modules&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/zutil.h&gt;
macro_line|#include &quot;infblock.h&quot;
macro_line|#include &quot;infutil.h&quot;
DECL|function|zlib_inflate_workspacesize
r_int
id|ZEXPORT
id|zlib_inflate_workspacesize
c_func
(paren
r_void
)paren
(brace
r_return
r_sizeof
(paren
r_struct
id|inflate_workspace
)paren
suffix:semicolon
)brace
DECL|function|zlib_inflateReset
r_int
id|ZEXPORT
id|zlib_inflateReset
c_func
(paren
id|z
)paren
id|z_streamp
id|z
suffix:semicolon
(brace
r_if
c_cond
(paren
id|z
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;state
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;workspace
op_eq
id|Z_NULL
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
id|z-&gt;total_in
op_assign
id|z-&gt;total_out
op_assign
l_int|0
suffix:semicolon
id|z-&gt;msg
op_assign
id|Z_NULL
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|z-&gt;state-&gt;nowrap
ques
c_cond
id|BLOCKS
suffix:colon
id|METHOD
suffix:semicolon
id|zlib_inflate_blocks_reset
c_func
(paren
id|z-&gt;state-&gt;blocks
comma
id|z
comma
id|Z_NULL
)paren
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
DECL|function|zlib_inflateEnd
r_int
id|ZEXPORT
id|zlib_inflateEnd
c_func
(paren
id|z
)paren
id|z_streamp
id|z
suffix:semicolon
(brace
r_if
c_cond
(paren
id|z
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;state
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;workspace
op_eq
id|Z_NULL
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;state-&gt;blocks
op_ne
id|Z_NULL
)paren
id|zlib_inflate_blocks_free
c_func
(paren
id|z-&gt;state-&gt;blocks
comma
id|z
)paren
suffix:semicolon
id|z-&gt;state
op_assign
id|Z_NULL
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
DECL|function|zlib_inflateInit2_
r_int
id|ZEXPORT
id|zlib_inflateInit2_
c_func
(paren
id|z
comma
id|w
comma
id|version
comma
id|stream_size
)paren
id|z_streamp
id|z
suffix:semicolon
r_int
id|w
suffix:semicolon
r_const
r_char
op_star
id|version
suffix:semicolon
r_int
id|stream_size
suffix:semicolon
(brace
r_if
c_cond
(paren
id|version
op_eq
id|Z_NULL
op_logical_or
id|version
(braket
l_int|0
)braket
op_ne
id|ZLIB_VERSION
(braket
l_int|0
)braket
op_logical_or
id|stream_size
op_ne
r_sizeof
(paren
id|z_stream
)paren
op_logical_or
id|z-&gt;workspace
op_eq
id|Z_NULL
)paren
r_return
id|Z_VERSION_ERROR
suffix:semicolon
multiline_comment|/* initialize state */
r_if
c_cond
(paren
id|z
op_eq
id|Z_NULL
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
id|z-&gt;msg
op_assign
id|Z_NULL
suffix:semicolon
id|z-&gt;state
op_assign
op_amp
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|internal_state
suffix:semicolon
id|z-&gt;state-&gt;blocks
op_assign
id|Z_NULL
suffix:semicolon
multiline_comment|/* handle undocumented nowrap option (no zlib header or check) */
id|z-&gt;state-&gt;nowrap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|w
OL
l_int|0
)paren
(brace
id|w
op_assign
op_minus
id|w
suffix:semicolon
id|z-&gt;state-&gt;nowrap
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* set window size */
r_if
c_cond
(paren
id|w
template_param
l_int|15
)paren
(brace
id|zlib_inflateEnd
c_func
(paren
id|z
)paren
suffix:semicolon
r_return
id|Z_STREAM_ERROR
suffix:semicolon
)brace
id|z-&gt;state-&gt;wbits
op_assign
(paren
id|uInt
)paren
id|w
suffix:semicolon
multiline_comment|/* create inflate_blocks state */
r_if
c_cond
(paren
(paren
id|z-&gt;state-&gt;blocks
op_assign
id|zlib_inflate_blocks_new
c_func
(paren
id|z
comma
id|z-&gt;state-&gt;nowrap
ques
c_cond
id|Z_NULL
suffix:colon
id|zlib_adler32
comma
(paren
id|uInt
)paren
l_int|1
op_lshift
id|w
)paren
)paren
op_eq
id|Z_NULL
)paren
(brace
id|zlib_inflateEnd
c_func
(paren
id|z
)paren
suffix:semicolon
r_return
id|Z_MEM_ERROR
suffix:semicolon
)brace
multiline_comment|/* reset state */
id|zlib_inflateReset
c_func
(paren
id|z
)paren
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
multiline_comment|/*&n; * At the end of a Deflate-compressed PPP packet, we expect to have seen&n; * a `stored&squot; block type value but not the (zero) length bytes.&n; */
DECL|function|zlib_inflate_packet_flush
r_static
r_int
id|zlib_inflate_packet_flush
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;mode
op_ne
id|LENS
)paren
r_return
id|Z_DATA_ERROR
suffix:semicolon
id|s-&gt;mode
op_assign
id|TYPE
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
DECL|function|zlib_inflateInit_
r_int
id|ZEXPORT
id|zlib_inflateInit_
c_func
(paren
id|z
comma
id|version
comma
id|stream_size
)paren
id|z_streamp
id|z
suffix:semicolon
r_const
r_char
op_star
id|version
suffix:semicolon
r_int
id|stream_size
suffix:semicolon
(brace
r_return
id|zlib_inflateInit2_
c_func
(paren
id|z
comma
id|DEF_WBITS
comma
id|version
comma
id|stream_size
)paren
suffix:semicolon
)brace
DECL|macro|NEEDBYTE
macro_line|#undef NEEDBYTE
DECL|macro|NEXTBYTE
macro_line|#undef NEXTBYTE
DECL|macro|NEEDBYTE
mdefine_line|#define NEEDBYTE {if(z-&gt;avail_in==0)goto empty;r=trv;}
DECL|macro|NEXTBYTE
mdefine_line|#define NEXTBYTE (z-&gt;avail_in--,z-&gt;total_in++,*z-&gt;next_in++)
DECL|function|zlib_inflate
r_int
id|ZEXPORT
id|zlib_inflate
c_func
(paren
id|z
comma
id|f
)paren
id|z_streamp
id|z
suffix:semicolon
r_int
id|f
suffix:semicolon
(brace
r_int
id|r
comma
id|trv
suffix:semicolon
id|uInt
id|b
suffix:semicolon
r_if
c_cond
(paren
id|z
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;state
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;next_in
op_eq
id|Z_NULL
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
id|trv
op_assign
id|f
op_eq
id|Z_FINISH
ques
c_cond
id|Z_BUF_ERROR
suffix:colon
id|Z_OK
suffix:semicolon
id|r
op_assign
id|Z_BUF_ERROR
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
r_switch
c_cond
(paren
id|z-&gt;state-&gt;mode
)paren
(brace
r_case
id|METHOD
suffix:colon
id|NEEDBYTE
r_if
c_cond
(paren
(paren
(paren
id|z-&gt;state-&gt;sub.method
op_assign
id|NEXTBYTE
)paren
op_amp
l_int|0xf
)paren
op_ne
id|Z_DEFLATED
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;unknown compression method&quot;
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* can&squot;t try inflateSync */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|z-&gt;state-&gt;sub.method
op_rshift
l_int|4
)paren
op_plus
l_int|8
OG
id|z-&gt;state-&gt;wbits
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;invalid window size&quot;
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* can&squot;t try inflateSync */
r_break
suffix:semicolon
)brace
id|z-&gt;state-&gt;mode
op_assign
id|FLAG
suffix:semicolon
r_case
id|FLAG
suffix:colon
id|NEEDBYTE
id|b
op_assign
id|NEXTBYTE
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|z-&gt;state-&gt;sub.method
op_lshift
l_int|8
)paren
op_plus
id|b
)paren
op_mod
l_int|31
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;incorrect header check&quot;
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* can&squot;t try inflateSync */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|b
op_amp
id|PRESET_DICT
)paren
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|BLOCKS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|z-&gt;state-&gt;mode
op_assign
id|DICT4
suffix:semicolon
r_case
id|DICT4
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_assign
(paren
id|uLong
)paren
id|NEXTBYTE
op_lshift
l_int|24
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|DICT3
suffix:semicolon
r_case
id|DICT3
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_add_assign
(paren
id|uLong
)paren
id|NEXTBYTE
op_lshift
l_int|16
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|DICT2
suffix:semicolon
r_case
id|DICT2
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_add_assign
(paren
id|uLong
)paren
id|NEXTBYTE
op_lshift
l_int|8
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|DICT1
suffix:semicolon
r_case
id|DICT1
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_add_assign
(paren
id|uLong
)paren
id|NEXTBYTE
suffix:semicolon
id|z-&gt;adler
op_assign
id|z-&gt;state-&gt;sub.check.need
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|DICT0
suffix:semicolon
r_return
id|Z_NEED_DICT
suffix:semicolon
r_case
id|DICT0
suffix:colon
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;need dictionary&quot;
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* can try inflateSync */
r_return
id|Z_STREAM_ERROR
suffix:semicolon
r_case
id|BLOCKS
suffix:colon
id|r
op_assign
id|zlib_inflate_blocks
c_func
(paren
id|z-&gt;state-&gt;blocks
comma
id|z
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
id|Z_PACKET_FLUSH
op_logical_and
id|z-&gt;avail_in
op_eq
l_int|0
op_logical_and
id|z-&gt;avail_out
op_ne
l_int|0
)paren
id|r
op_assign
id|zlib_inflate_packet_flush
c_func
(paren
id|z-&gt;state-&gt;blocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
id|Z_DATA_ERROR
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* can try inflateSync */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r
op_eq
id|Z_OK
)paren
id|r
op_assign
id|trv
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_STREAM_END
)paren
r_return
id|r
suffix:semicolon
id|r
op_assign
id|trv
suffix:semicolon
id|zlib_inflate_blocks_reset
c_func
(paren
id|z-&gt;state-&gt;blocks
comma
id|z
comma
op_amp
id|z-&gt;state-&gt;sub.check.was
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;state-&gt;nowrap
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_DONE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|z-&gt;state-&gt;mode
op_assign
id|CHECK4
suffix:semicolon
r_case
id|CHECK4
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_assign
(paren
id|uLong
)paren
id|NEXTBYTE
op_lshift
l_int|24
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|CHECK3
suffix:semicolon
r_case
id|CHECK3
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_add_assign
(paren
id|uLong
)paren
id|NEXTBYTE
op_lshift
l_int|16
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|CHECK2
suffix:semicolon
r_case
id|CHECK2
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_add_assign
(paren
id|uLong
)paren
id|NEXTBYTE
op_lshift
l_int|8
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|CHECK1
suffix:semicolon
r_case
id|CHECK1
suffix:colon
id|NEEDBYTE
id|z-&gt;state-&gt;sub.check.need
op_add_assign
(paren
id|uLong
)paren
id|NEXTBYTE
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;state-&gt;sub.check.was
op_ne
id|z-&gt;state-&gt;sub.check.need
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;incorrect data check&quot;
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* can&squot;t try inflateSync */
r_break
suffix:semicolon
)brace
id|z-&gt;state-&gt;mode
op_assign
id|I_DONE
suffix:semicolon
r_case
id|I_DONE
suffix:colon
r_return
id|Z_STREAM_END
suffix:semicolon
r_case
id|I_BAD
suffix:colon
r_return
id|Z_DATA_ERROR
suffix:semicolon
r_default
suffix:colon
r_return
id|Z_STREAM_ERROR
suffix:semicolon
)brace
id|empty
suffix:colon
r_if
c_cond
(paren
id|f
op_ne
id|Z_PACKET_FLUSH
)paren
r_return
id|r
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;need more for packet flush&quot;
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* can try inflateSync */
r_return
id|Z_DATA_ERROR
suffix:semicolon
)brace
DECL|function|zlib_inflateSync
r_int
id|ZEXPORT
id|zlib_inflateSync
c_func
(paren
id|z
)paren
id|z_streamp
id|z
suffix:semicolon
(brace
id|uInt
id|n
suffix:semicolon
multiline_comment|/* number of bytes to look at */
id|Bytef
op_star
id|p
suffix:semicolon
multiline_comment|/* pointer to bytes */
id|uInt
id|m
suffix:semicolon
multiline_comment|/* number of marker bytes found in a row */
id|uLong
id|r
comma
id|w
suffix:semicolon
multiline_comment|/* temporaries to save total_in and total_out */
multiline_comment|/* set up */
r_if
c_cond
(paren
id|z
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;state
op_eq
id|Z_NULL
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|z-&gt;state-&gt;mode
op_ne
id|I_BAD
)paren
(brace
id|z-&gt;state-&gt;mode
op_assign
id|I_BAD
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|n
op_assign
id|z-&gt;avail_in
)paren
op_eq
l_int|0
)paren
r_return
id|Z_BUF_ERROR
suffix:semicolon
id|p
op_assign
id|z-&gt;next_in
suffix:semicolon
id|m
op_assign
id|z-&gt;state-&gt;sub.marker
suffix:semicolon
multiline_comment|/* search */
r_while
c_loop
(paren
id|n
op_logical_and
id|m
OL
l_int|4
)paren
(brace
r_static
r_const
id|Byte
id|mark
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
id|mark
(braket
id|m
)braket
)paren
id|m
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|p
)paren
id|m
op_assign
l_int|0
suffix:semicolon
r_else
id|m
op_assign
l_int|4
op_minus
id|m
suffix:semicolon
id|p
op_increment
comma
id|n
op_decrement
suffix:semicolon
)brace
multiline_comment|/* restore */
id|z-&gt;total_in
op_add_assign
id|p
op_minus
id|z-&gt;next_in
suffix:semicolon
id|z-&gt;next_in
op_assign
id|p
suffix:semicolon
id|z-&gt;avail_in
op_assign
id|n
suffix:semicolon
id|z-&gt;state-&gt;sub.marker
op_assign
id|m
suffix:semicolon
multiline_comment|/* return no joy or set up to restart on a new block */
r_if
c_cond
(paren
id|m
op_ne
l_int|4
)paren
r_return
id|Z_DATA_ERROR
suffix:semicolon
id|r
op_assign
id|z-&gt;total_in
suffix:semicolon
id|w
op_assign
id|z-&gt;total_out
suffix:semicolon
id|zlib_inflateReset
c_func
(paren
id|z
)paren
suffix:semicolon
id|z-&gt;total_in
op_assign
id|r
suffix:semicolon
id|z-&gt;total_out
op_assign
id|w
suffix:semicolon
id|z-&gt;state-&gt;mode
op_assign
id|BLOCKS
suffix:semicolon
r_return
id|Z_OK
suffix:semicolon
)brace
multiline_comment|/* Returns true if inflate is currently at the end of a block generated&n; * by Z_SYNC_FLUSH or Z_FULL_FLUSH. This function is used by one PPP&n; * implementation to provide an additional safety check. PPP uses Z_SYNC_FLUSH&n; * but removes the length bytes of the resulting empty stored block. When&n; * decompressing, PPP checks that at the end of input packet, inflate is&n; * waiting for these length bytes.&n; */
DECL|function|zlib_inflateSyncPoint
r_int
id|ZEXPORT
id|zlib_inflateSyncPoint
c_func
(paren
id|z
)paren
id|z_streamp
id|z
suffix:semicolon
(brace
r_if
c_cond
(paren
id|z
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;state
op_eq
id|Z_NULL
op_logical_or
id|z-&gt;state-&gt;blocks
op_eq
id|Z_NULL
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
r_return
id|zlib_inflate_blocks_sync_point
c_func
(paren
id|z-&gt;state-&gt;blocks
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This subroutine adds the data at next_in/avail_in to the output history&n; * without performing any output.  The output buffer must be &quot;caught up&quot;;&n; * i.e. no pending output (hence s-&gt;read equals s-&gt;write), and the state must&n; * be BLOCKS (i.e. we should be willing to see the start of a series of&n; * BLOCKS).  On exit, the output will also be caught up, and the checksum&n; * will have been updated if need be.&n; */
DECL|function|zlib_inflate_addhistory
r_static
r_int
id|zlib_inflate_addhistory
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
comma
id|z_stream
op_star
id|z
)paren
(brace
id|uLong
id|b
suffix:semicolon
multiline_comment|/* bit buffer */
multiline_comment|/* NOT USED HERE */
id|uInt
id|k
suffix:semicolon
multiline_comment|/* bits in bit buffer */
multiline_comment|/* NOT USED HERE */
id|uInt
id|t
suffix:semicolon
multiline_comment|/* temporary storage */
id|Bytef
op_star
id|p
suffix:semicolon
multiline_comment|/* input data pointer */
id|uInt
id|n
suffix:semicolon
multiline_comment|/* bytes available there */
id|Bytef
op_star
id|q
suffix:semicolon
multiline_comment|/* output window write pointer */
id|uInt
id|m
suffix:semicolon
multiline_comment|/* bytes to end of window or read pointer */
r_if
c_cond
(paren
id|s-&gt;read
op_ne
id|s-&gt;write
)paren
r_return
id|Z_STREAM_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;mode
op_ne
id|TYPE
)paren
r_return
id|Z_DATA_ERROR
suffix:semicolon
multiline_comment|/* we&squot;re ready to rock */
id|LOAD
multiline_comment|/* while there is input ready, copy to output buffer, moving&n;     * pointers as needed.&n;     */
r_while
c_loop
(paren
id|n
)paren
(brace
id|t
op_assign
id|n
suffix:semicolon
multiline_comment|/* how many to do */
multiline_comment|/* is there room until end of buffer? */
r_if
c_cond
(paren
id|t
OG
id|m
)paren
id|t
op_assign
id|m
suffix:semicolon
multiline_comment|/* update check information */
r_if
c_cond
(paren
id|s-&gt;checkfn
op_ne
id|Z_NULL
)paren
id|s-&gt;check
op_assign
(paren
op_star
id|s-&gt;checkfn
)paren
(paren
id|s-&gt;check
comma
id|q
comma
id|t
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|q
comma
id|p
comma
id|t
)paren
suffix:semicolon
id|q
op_add_assign
id|t
suffix:semicolon
id|p
op_add_assign
id|t
suffix:semicolon
id|n
op_sub_assign
id|t
suffix:semicolon
id|z-&gt;total_out
op_add_assign
id|t
suffix:semicolon
id|s-&gt;read
op_assign
id|q
suffix:semicolon
multiline_comment|/* drag read pointer forward */
multiline_comment|/*      WWRAP  */
multiline_comment|/* expand WWRAP macro by hand to handle s-&gt;read */
r_if
c_cond
(paren
id|q
op_eq
id|s-&gt;end
)paren
(brace
id|s-&gt;read
op_assign
id|q
op_assign
id|s-&gt;window
suffix:semicolon
id|m
op_assign
id|WAVAIL
suffix:semicolon
)brace
)brace
id|UPDATE
r_return
id|Z_OK
suffix:semicolon
)brace
multiline_comment|/*&n; * This subroutine adds the data at next_in/avail_in to the output history&n; * without performing any output.  The output buffer must be &quot;caught up&quot;;&n; * i.e. no pending output (hence s-&gt;read equals s-&gt;write), and the state must&n; * be BLOCKS (i.e. we should be willing to see the start of a series of&n; * BLOCKS).  On exit, the output will also be caught up, and the checksum&n; * will have been updated if need be.&n; */
DECL|function|zlib_inflateIncomp
r_int
id|ZEXPORT
id|zlib_inflateIncomp
c_func
(paren
id|z
)paren
id|z_stream
op_star
id|z
suffix:semicolon
(brace
r_if
c_cond
(paren
id|z-&gt;state-&gt;mode
op_ne
id|BLOCKS
)paren
r_return
id|Z_DATA_ERROR
suffix:semicolon
r_return
id|zlib_inflate_addhistory
c_func
(paren
id|z-&gt;state-&gt;blocks
comma
id|z
)paren
suffix:semicolon
)brace
eof
