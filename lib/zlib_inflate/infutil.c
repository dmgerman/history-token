multiline_comment|/* inflate_util.c -- data and routines common to blocks and codes&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
macro_line|#include &lt;linux/zutil.h&gt;
macro_line|#include &quot;infblock.h&quot;
macro_line|#include &quot;inftrees.h&quot;
macro_line|#include &quot;infcodes.h&quot;
macro_line|#include &quot;infutil.h&quot;
r_struct
id|inflate_codes_state
suffix:semicolon
multiline_comment|/* And&squot;ing with mask[n] masks the lower n bits */
DECL|variable|zlib_inflate_mask
id|uInt
id|zlib_inflate_mask
(braket
l_int|17
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0001
comma
l_int|0x0003
comma
l_int|0x0007
comma
l_int|0x000f
comma
l_int|0x001f
comma
l_int|0x003f
comma
l_int|0x007f
comma
l_int|0x00ff
comma
l_int|0x01ff
comma
l_int|0x03ff
comma
l_int|0x07ff
comma
l_int|0x0fff
comma
l_int|0x1fff
comma
l_int|0x3fff
comma
l_int|0x7fff
comma
l_int|0xffff
)brace
suffix:semicolon
multiline_comment|/* copy as much as possible from the sliding window to the output area */
DECL|function|zlib_inflate_flush
r_int
id|zlib_inflate_flush
c_func
(paren
id|inflate_blocks_statef
op_star
id|s
comma
id|z_streamp
id|z
comma
r_int
id|r
)paren
(brace
id|uInt
id|n
suffix:semicolon
id|Byte
op_star
id|p
suffix:semicolon
id|Byte
op_star
id|q
suffix:semicolon
multiline_comment|/* local copies of source and destination pointers */
id|p
op_assign
id|z-&gt;next_out
suffix:semicolon
id|q
op_assign
id|s-&gt;read
suffix:semicolon
multiline_comment|/* compute number of bytes to copy as far as end of window */
id|n
op_assign
(paren
id|uInt
)paren
(paren
(paren
id|q
op_le
id|s-&gt;write
ques
c_cond
id|s-&gt;write
suffix:colon
id|s-&gt;end
)paren
op_minus
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|z-&gt;avail_out
)paren
id|n
op_assign
id|z-&gt;avail_out
suffix:semicolon
r_if
c_cond
(paren
id|n
op_logical_and
id|r
op_eq
id|Z_BUF_ERROR
)paren
id|r
op_assign
id|Z_OK
suffix:semicolon
multiline_comment|/* update counters */
id|z-&gt;avail_out
op_sub_assign
id|n
suffix:semicolon
id|z-&gt;total_out
op_add_assign
id|n
suffix:semicolon
multiline_comment|/* update check information */
r_if
c_cond
(paren
id|s-&gt;checkfn
op_ne
id|Z_NULL
)paren
id|z-&gt;adler
op_assign
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
id|n
)paren
suffix:semicolon
multiline_comment|/* copy as far as end of window */
id|memcpy
c_func
(paren
id|p
comma
id|q
comma
id|n
)paren
suffix:semicolon
id|p
op_add_assign
id|n
suffix:semicolon
id|q
op_add_assign
id|n
suffix:semicolon
multiline_comment|/* see if more to copy at beginning of window */
r_if
c_cond
(paren
id|q
op_eq
id|s-&gt;end
)paren
(brace
multiline_comment|/* wrap pointers */
id|q
op_assign
id|s-&gt;window
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;write
op_eq
id|s-&gt;end
)paren
id|s-&gt;write
op_assign
id|s-&gt;window
suffix:semicolon
multiline_comment|/* compute bytes to copy */
id|n
op_assign
(paren
id|uInt
)paren
(paren
id|s-&gt;write
op_minus
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|z-&gt;avail_out
)paren
id|n
op_assign
id|z-&gt;avail_out
suffix:semicolon
r_if
c_cond
(paren
id|n
op_logical_and
id|r
op_eq
id|Z_BUF_ERROR
)paren
id|r
op_assign
id|Z_OK
suffix:semicolon
multiline_comment|/* update counters */
id|z-&gt;avail_out
op_sub_assign
id|n
suffix:semicolon
id|z-&gt;total_out
op_add_assign
id|n
suffix:semicolon
multiline_comment|/* update check information */
r_if
c_cond
(paren
id|s-&gt;checkfn
op_ne
id|Z_NULL
)paren
id|z-&gt;adler
op_assign
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
id|n
)paren
suffix:semicolon
multiline_comment|/* copy */
id|memcpy
c_func
(paren
id|p
comma
id|q
comma
id|n
)paren
suffix:semicolon
id|p
op_add_assign
id|n
suffix:semicolon
id|q
op_add_assign
id|n
suffix:semicolon
)brace
multiline_comment|/* update pointers */
id|z-&gt;next_out
op_assign
id|p
suffix:semicolon
id|s-&gt;read
op_assign
id|q
suffix:semicolon
multiline_comment|/* done */
r_return
id|r
suffix:semicolon
)brace
eof
