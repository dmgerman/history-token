multiline_comment|/*&n; *  linux/net/sunrpc/gss_krb5_seqnum.c&n; *&n; *  Adapted from MIT Kerberos 5-1.2.1 lib/gssapi/krb5/util_seqnum.c&n; *&n; *  Copyright (c) 2000 The Regents of the University of Michigan.&n; *  All rights reserved.&n; *&n; *  Andy Adamson   &lt;andros@umich.edu&gt;&n; */
multiline_comment|/*&n; * Copyright 1993 by OpenVision Technologies, Inc.&n; * &n; * Permission to use, copy, modify, distribute, and sell this software&n; * and its documentation for any purpose is hereby granted without fee,&n; * provided that the above copyright notice appears in all copies and&n; * that both that copyright notice and this permission notice appear in&n; * supporting documentation, and that the name of OpenVision not be used&n; * in advertising or publicity pertaining to distribution of the software&n; * without specific, written prior permission. OpenVision makes no&n; * representations about the suitability of this software for any&n; * purpose.  It is provided &quot;as is&quot; without express or implied warranty.&n; * &n; * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,&n; * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO&n; * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INDIRECT OR&n; * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF&n; * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR&n; * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR&n; * PERFORMANCE OF THIS SOFTWARE.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sunrpc/gss_krb5.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY        RPCDBG_AUTH
macro_line|#endif
id|s32
DECL|function|krb5_make_seq_num
id|krb5_make_seq_num
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|key
comma
r_int
id|direction
comma
id|s32
id|seqnum
comma
r_int
r_char
op_star
id|cksum
comma
r_int
r_char
op_star
id|buf
)paren
(brace
r_int
r_char
id|plain
(braket
l_int|8
)braket
suffix:semicolon
id|plain
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|seqnum
op_amp
l_int|0xff
)paren
suffix:semicolon
id|plain
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
id|seqnum
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|plain
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
id|seqnum
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|plain
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
id|seqnum
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|plain
(braket
l_int|4
)braket
op_assign
id|direction
suffix:semicolon
id|plain
(braket
l_int|5
)braket
op_assign
id|direction
suffix:semicolon
id|plain
(braket
l_int|6
)braket
op_assign
id|direction
suffix:semicolon
id|plain
(braket
l_int|7
)braket
op_assign
id|direction
suffix:semicolon
r_return
id|krb5_encrypt
c_func
(paren
id|key
comma
id|cksum
comma
id|plain
comma
id|buf
comma
l_int|8
)paren
suffix:semicolon
)brace
id|s32
DECL|function|krb5_get_seq_num
id|krb5_get_seq_num
c_func
(paren
r_struct
id|crypto_tfm
op_star
id|key
comma
r_int
r_char
op_star
id|cksum
comma
r_int
r_char
op_star
id|buf
comma
r_int
op_star
id|direction
comma
id|s32
op_star
id|seqnum
)paren
(brace
id|s32
id|code
suffix:semicolon
r_int
r_char
id|plain
(braket
l_int|8
)braket
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      krb5_get_seq_num:&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|code
op_assign
id|krb5_decrypt
c_func
(paren
id|key
comma
id|cksum
comma
id|buf
comma
id|plain
comma
l_int|8
)paren
)paren
)paren
r_return
id|code
suffix:semicolon
r_if
c_cond
(paren
(paren
id|plain
(braket
l_int|4
)braket
op_ne
id|plain
(braket
l_int|5
)braket
)paren
op_logical_or
(paren
id|plain
(braket
l_int|4
)braket
op_ne
id|plain
(braket
l_int|6
)braket
)paren
op_logical_or
(paren
id|plain
(braket
l_int|4
)braket
op_ne
id|plain
(braket
l_int|7
)braket
)paren
)paren
r_return
(paren
id|s32
)paren
id|KG_BAD_SEQ
suffix:semicolon
op_star
id|direction
op_assign
id|plain
(braket
l_int|4
)braket
suffix:semicolon
op_star
id|seqnum
op_assign
(paren
(paren
id|plain
(braket
l_int|0
)braket
)paren
op_or
(paren
id|plain
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|plain
(braket
l_int|2
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|plain
(braket
l_int|3
)braket
op_lshift
l_int|24
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
