multiline_comment|/* infcodes.c -- process literals and length/distance pairs&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
macro_line|#include &lt;linux/zutil.h&gt;
macro_line|#include &quot;inftrees.h&quot;
macro_line|#include &quot;infblock.h&quot;
macro_line|#include &quot;infcodes.h&quot;
macro_line|#include &quot;infutil.h&quot;
macro_line|#include &quot;inffast.h&quot;
multiline_comment|/* simplify the use of the inflate_huft type with some defines */
DECL|macro|exop
mdefine_line|#define exop word.what.Exop
DECL|macro|bits
mdefine_line|#define bits word.what.Bits
DECL|function|zlib_inflate_codes_new
id|inflate_codes_statef
op_star
id|zlib_inflate_codes_new
c_func
(paren
id|bl
comma
id|bd
comma
id|tl
comma
id|td
comma
id|z
)paren
id|uInt
id|bl
comma
id|bd
suffix:semicolon
id|inflate_huft
op_star
id|tl
suffix:semicolon
id|inflate_huft
op_star
id|td
suffix:semicolon
multiline_comment|/* need separate declaration for Borland C++ */
id|z_streamp
id|z
suffix:semicolon
(brace
id|inflate_codes_statef
op_star
id|c
suffix:semicolon
id|c
op_assign
op_amp
id|WS
c_func
(paren
id|z
)paren
op_member_access_from_pointer
id|working_state
suffix:semicolon
(brace
id|c-&gt;mode
op_assign
id|START
suffix:semicolon
id|c-&gt;lbits
op_assign
(paren
id|Byte
)paren
id|bl
suffix:semicolon
id|c-&gt;dbits
op_assign
(paren
id|Byte
)paren
id|bd
suffix:semicolon
id|c-&gt;ltree
op_assign
id|tl
suffix:semicolon
id|c-&gt;dtree
op_assign
id|td
suffix:semicolon
)brace
r_return
id|c
suffix:semicolon
)brace
DECL|function|zlib_inflate_codes
r_int
id|zlib_inflate_codes
c_func
(paren
id|s
comma
id|z
comma
id|r
)paren
id|inflate_blocks_statef
op_star
id|s
suffix:semicolon
id|z_streamp
id|z
suffix:semicolon
r_int
id|r
suffix:semicolon
(brace
id|uInt
id|j
suffix:semicolon
multiline_comment|/* temporary storage */
id|inflate_huft
op_star
id|t
suffix:semicolon
multiline_comment|/* temporary pointer */
id|uInt
id|e
suffix:semicolon
multiline_comment|/* extra bits or operation */
id|uLong
id|b
suffix:semicolon
multiline_comment|/* bit buffer */
id|uInt
id|k
suffix:semicolon
multiline_comment|/* bits in bit buffer */
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
id|Bytef
op_star
id|f
suffix:semicolon
multiline_comment|/* pointer to copy strings from */
id|inflate_codes_statef
op_star
id|c
op_assign
id|s-&gt;sub.decode.codes
suffix:semicolon
multiline_comment|/* codes state */
multiline_comment|/* copy input/output information to locals (UPDATE macro restores) */
id|LOAD
multiline_comment|/* process input and output based on current state */
r_while
c_loop
(paren
l_int|1
)paren
r_switch
c_cond
(paren
id|c-&gt;mode
)paren
(brace
multiline_comment|/* waiting for &quot;i:&quot;=input, &quot;o:&quot;=output, &quot;x:&quot;=nothing */
r_case
id|START
suffix:colon
multiline_comment|/* x: set up for LEN */
macro_line|#ifndef SLOW
r_if
c_cond
(paren
id|m
op_ge
l_int|258
op_logical_and
id|n
op_ge
l_int|10
)paren
(brace
id|UPDATE
id|r
op_assign
id|zlib_inflate_fast
c_func
(paren
id|c-&gt;lbits
comma
id|c-&gt;dbits
comma
id|c-&gt;ltree
comma
id|c-&gt;dtree
comma
id|s
comma
id|z
)paren
suffix:semicolon
id|LOAD
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
id|c-&gt;mode
op_assign
id|r
op_eq
id|Z_STREAM_END
ques
c_cond
id|WASH
suffix:colon
id|BADCODE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif /* !SLOW */
id|c-&gt;sub.code.need
op_assign
id|c-&gt;lbits
suffix:semicolon
id|c-&gt;sub.code.tree
op_assign
id|c-&gt;ltree
suffix:semicolon
id|c-&gt;mode
op_assign
id|LEN
suffix:semicolon
r_case
id|LEN
suffix:colon
multiline_comment|/* i: get length/literal/eob next */
id|j
op_assign
id|c-&gt;sub.code.need
suffix:semicolon
id|NEEDBITS
c_func
(paren
id|j
)paren
id|t
op_assign
id|c-&gt;sub.code.tree
op_plus
(paren
(paren
id|uInt
)paren
id|b
op_amp
id|zlib_inflate_mask
(braket
id|j
)braket
)paren
suffix:semicolon
id|DUMPBITS
c_func
(paren
id|t-&gt;bits
)paren
id|e
op_assign
(paren
id|uInt
)paren
(paren
id|t-&gt;exop
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
op_eq
l_int|0
)paren
multiline_comment|/* literal */
(brace
id|c-&gt;sub.lit
op_assign
id|t-&gt;base
suffix:semicolon
id|c-&gt;mode
op_assign
id|LIT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|e
op_amp
l_int|16
)paren
multiline_comment|/* length */
(brace
id|c-&gt;sub.copy.get
op_assign
id|e
op_amp
l_int|15
suffix:semicolon
id|c-&gt;len
op_assign
id|t-&gt;base
suffix:semicolon
id|c-&gt;mode
op_assign
id|LENEXT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|e
op_amp
l_int|64
)paren
op_eq
l_int|0
)paren
multiline_comment|/* next table */
(brace
id|c-&gt;sub.code.need
op_assign
id|e
suffix:semicolon
id|c-&gt;sub.code.tree
op_assign
id|t
op_plus
id|t-&gt;base
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|e
op_amp
l_int|32
)paren
multiline_comment|/* end of block */
(brace
id|c-&gt;mode
op_assign
id|WASH
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c-&gt;mode
op_assign
id|BADCODE
suffix:semicolon
multiline_comment|/* invalid code */
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;invalid literal/length code&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
r_case
id|LENEXT
suffix:colon
multiline_comment|/* i: getting length extra (have base) */
id|j
op_assign
id|c-&gt;sub.copy.get
suffix:semicolon
id|NEEDBITS
c_func
(paren
id|j
)paren
id|c-&gt;len
op_add_assign
(paren
id|uInt
)paren
id|b
op_amp
id|zlib_inflate_mask
(braket
id|j
)braket
suffix:semicolon
id|DUMPBITS
c_func
(paren
id|j
)paren
id|c-&gt;sub.code.need
op_assign
id|c-&gt;dbits
suffix:semicolon
id|c-&gt;sub.code.tree
op_assign
id|c-&gt;dtree
suffix:semicolon
id|c-&gt;mode
op_assign
id|DIST
suffix:semicolon
r_case
id|DIST
suffix:colon
multiline_comment|/* i: get distance next */
id|j
op_assign
id|c-&gt;sub.code.need
suffix:semicolon
id|NEEDBITS
c_func
(paren
id|j
)paren
id|t
op_assign
id|c-&gt;sub.code.tree
op_plus
(paren
(paren
id|uInt
)paren
id|b
op_amp
id|zlib_inflate_mask
(braket
id|j
)braket
)paren
suffix:semicolon
id|DUMPBITS
c_func
(paren
id|t-&gt;bits
)paren
id|e
op_assign
(paren
id|uInt
)paren
(paren
id|t-&gt;exop
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
op_amp
l_int|16
)paren
multiline_comment|/* distance */
(brace
id|c-&gt;sub.copy.get
op_assign
id|e
op_amp
l_int|15
suffix:semicolon
id|c-&gt;sub.copy.dist
op_assign
id|t-&gt;base
suffix:semicolon
id|c-&gt;mode
op_assign
id|DISTEXT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|e
op_amp
l_int|64
)paren
op_eq
l_int|0
)paren
multiline_comment|/* next table */
(brace
id|c-&gt;sub.code.need
op_assign
id|e
suffix:semicolon
id|c-&gt;sub.code.tree
op_assign
id|t
op_plus
id|t-&gt;base
suffix:semicolon
r_break
suffix:semicolon
)brace
id|c-&gt;mode
op_assign
id|BADCODE
suffix:semicolon
multiline_comment|/* invalid code */
id|z-&gt;msg
op_assign
(paren
r_char
op_star
)paren
l_string|&quot;invalid distance code&quot;
suffix:semicolon
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
r_case
id|DISTEXT
suffix:colon
multiline_comment|/* i: getting distance extra */
id|j
op_assign
id|c-&gt;sub.copy.get
suffix:semicolon
id|NEEDBITS
c_func
(paren
id|j
)paren
id|c-&gt;sub.copy.dist
op_add_assign
(paren
id|uInt
)paren
id|b
op_amp
id|zlib_inflate_mask
(braket
id|j
)braket
suffix:semicolon
id|DUMPBITS
c_func
(paren
id|j
)paren
id|c-&gt;mode
op_assign
id|COPY
suffix:semicolon
r_case
id|COPY
suffix:colon
multiline_comment|/* o: copying bytes in window, waiting for space */
macro_line|#ifndef __TURBOC__ /* Turbo C bug for following expression */
id|f
op_assign
(paren
id|uInt
)paren
(paren
id|q
op_minus
id|s-&gt;window
)paren
OL
id|c-&gt;sub.copy.dist
ques
c_cond
id|s-&gt;end
op_minus
(paren
id|c-&gt;sub.copy.dist
op_minus
(paren
id|q
op_minus
id|s-&gt;window
)paren
)paren
suffix:colon
id|q
op_minus
id|c-&gt;sub.copy.dist
suffix:semicolon
macro_line|#else
id|f
op_assign
id|q
op_minus
id|c-&gt;sub.copy.dist
suffix:semicolon
r_if
c_cond
(paren
(paren
id|uInt
)paren
(paren
id|q
op_minus
id|s-&gt;window
)paren
OL
id|c-&gt;sub.copy.dist
)paren
id|f
op_assign
id|s-&gt;end
op_minus
(paren
id|c-&gt;sub.copy.dist
op_minus
(paren
id|uInt
)paren
(paren
id|q
op_minus
id|s-&gt;window
)paren
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|c-&gt;len
)paren
(brace
id|NEEDOUT
id|OUTBYTE
c_func
(paren
op_star
id|f
op_increment
)paren
r_if
c_cond
(paren
id|f
op_eq
id|s-&gt;end
)paren
id|f
op_assign
id|s-&gt;window
suffix:semicolon
id|c-&gt;len
op_decrement
suffix:semicolon
)brace
id|c-&gt;mode
op_assign
id|START
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LIT
suffix:colon
multiline_comment|/* o: got literal, waiting for output space */
id|NEEDOUT
id|OUTBYTE
c_func
(paren
id|c-&gt;sub.lit
)paren
id|c-&gt;mode
op_assign
id|START
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WASH
suffix:colon
multiline_comment|/* o: got eob, possibly more output */
r_if
c_cond
(paren
id|k
OG
l_int|7
)paren
multiline_comment|/* return unused byte, if any */
(brace
id|k
op_sub_assign
l_int|8
suffix:semicolon
id|n
op_increment
suffix:semicolon
id|p
op_decrement
suffix:semicolon
multiline_comment|/* can always return one */
)brace
id|FLUSH
r_if
c_cond
(paren
id|s-&gt;read
op_ne
id|s-&gt;write
)paren
id|LEAVE
id|c-&gt;mode
op_assign
id|END
suffix:semicolon
r_case
id|END
suffix:colon
id|r
op_assign
id|Z_STREAM_END
suffix:semicolon
id|LEAVE
r_case
id|BADCODE
suffix:colon
multiline_comment|/* x: got error */
id|r
op_assign
id|Z_DATA_ERROR
suffix:semicolon
id|LEAVE
r_default
suffix:colon
id|r
op_assign
id|Z_STREAM_ERROR
suffix:semicolon
id|LEAVE
)brace
macro_line|#ifdef NEED_DUMMY_RETURN
r_return
id|Z_STREAM_ERROR
suffix:semicolon
multiline_comment|/* Some dumb compilers complain without this */
macro_line|#endif
)brace
DECL|function|zlib_inflate_codes_free
r_void
id|zlib_inflate_codes_free
c_func
(paren
id|c
comma
id|z
)paren
id|inflate_codes_statef
op_star
id|c
suffix:semicolon
id|z_streamp
id|z
suffix:semicolon
(brace
)brace
eof
