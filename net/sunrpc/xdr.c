multiline_comment|/*&n; * linux/net/sunrpc/xdr.c&n; *&n; * Generic XDR support.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
multiline_comment|/*&n; * XDR functions for basic NFS types&n; */
id|u32
op_star
DECL|function|xdr_encode_netobj
id|xdr_encode_netobj
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_struct
id|xdr_netobj
op_star
id|obj
)paren
(brace
r_int
r_int
id|quadlen
op_assign
id|XDR_QUADLEN
c_func
(paren
id|obj-&gt;len
)paren
suffix:semicolon
id|p
(braket
id|quadlen
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* zero trailing bytes */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|obj-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|obj-&gt;data
comma
id|obj-&gt;len
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|obj-&gt;len
)paren
suffix:semicolon
)brace
id|u32
op_star
DECL|function|xdr_decode_netobj_fixed
id|xdr_decode_netobj_fixed
c_func
(paren
id|u32
op_star
id|p
comma
r_void
op_star
id|obj
comma
r_int
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
op_ne
id|len
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|obj
comma
id|p
comma
id|len
)paren
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
id|u32
op_star
DECL|function|xdr_decode_netobj
id|xdr_decode_netobj
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|xdr_netobj
op_star
id|obj
)paren
(brace
r_int
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
OG
id|XDR_MAX_NETOBJ
)paren
r_return
l_int|NULL
suffix:semicolon
id|obj-&gt;len
op_assign
id|len
suffix:semicolon
id|obj-&gt;data
op_assign
(paren
id|u8
op_star
)paren
id|p
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
id|u32
op_star
DECL|function|xdr_encode_array
id|xdr_encode_array
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_char
op_star
id|array
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|quadlen
op_assign
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
id|p
(braket
id|quadlen
)braket
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|array
comma
id|len
)paren
suffix:semicolon
r_return
id|p
op_plus
id|quadlen
suffix:semicolon
)brace
id|u32
op_star
DECL|function|xdr_encode_string
id|xdr_encode_string
c_func
(paren
id|u32
op_star
id|p
comma
r_const
r_char
op_star
id|string
)paren
(brace
r_return
id|xdr_encode_array
c_func
(paren
id|p
comma
id|string
comma
id|strlen
c_func
(paren
id|string
)paren
)paren
suffix:semicolon
)brace
id|u32
op_star
DECL|function|xdr_decode_string
id|xdr_decode_string
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|sp
comma
r_int
op_star
id|lenp
comma
r_int
id|maxlen
)paren
(brace
r_int
r_int
id|len
suffix:semicolon
r_char
op_star
id|string
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
OG
id|maxlen
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|lenp
)paren
op_star
id|lenp
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_mod
l_int|4
)paren
op_ne
l_int|0
)paren
(brace
id|string
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
)brace
r_else
(brace
id|string
op_assign
(paren
r_char
op_star
)paren
(paren
id|p
op_minus
l_int|1
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|string
comma
id|p
comma
id|len
)paren
suffix:semicolon
)brace
id|string
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|sp
op_assign
id|string
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
id|u32
op_star
DECL|function|xdr_decode_string_inplace
id|xdr_decode_string_inplace
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|sp
comma
r_int
op_star
id|lenp
comma
r_int
id|maxlen
)paren
(brace
r_int
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
OG
id|maxlen
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|lenp
op_assign
id|len
suffix:semicolon
op_star
id|sp
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
r_return
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
r_void
DECL|function|xdr_encode_pages
id|xdr_encode_pages
c_func
(paren
r_struct
id|xdr_buf
op_star
id|xdr
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
r_int
id|base
comma
r_int
r_int
id|len
)paren
(brace
id|xdr-&gt;pages
op_assign
id|pages
suffix:semicolon
id|xdr-&gt;page_base
op_assign
id|base
suffix:semicolon
id|xdr-&gt;page_len
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
l_int|3
)paren
(brace
r_struct
id|iovec
op_star
id|iov
op_assign
id|xdr-&gt;tail
suffix:semicolon
r_int
r_int
id|pad
op_assign
l_int|4
op_minus
(paren
id|len
op_amp
l_int|3
)paren
suffix:semicolon
id|iov-&gt;iov_base
op_assign
(paren
r_void
op_star
)paren
l_string|&quot;&bslash;0&bslash;0&bslash;0&quot;
suffix:semicolon
id|iov-&gt;iov_len
op_assign
id|pad
suffix:semicolon
id|len
op_add_assign
id|pad
suffix:semicolon
)brace
id|xdr-&gt;len
op_add_assign
id|len
suffix:semicolon
)brace
r_void
DECL|function|xdr_inline_pages
id|xdr_inline_pages
c_func
(paren
r_struct
id|xdr_buf
op_star
id|xdr
comma
r_int
r_int
id|offset
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
r_int
id|base
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|iovec
op_star
id|head
op_assign
id|xdr-&gt;head
suffix:semicolon
r_struct
id|iovec
op_star
id|tail
op_assign
id|xdr-&gt;tail
suffix:semicolon
r_char
op_star
id|buf
op_assign
(paren
r_char
op_star
)paren
id|head-&gt;iov_base
suffix:semicolon
r_int
r_int
id|buflen
op_assign
id|head-&gt;iov_len
suffix:semicolon
id|head-&gt;iov_len
op_assign
id|offset
suffix:semicolon
id|xdr-&gt;pages
op_assign
id|pages
suffix:semicolon
id|xdr-&gt;page_base
op_assign
id|base
suffix:semicolon
id|xdr-&gt;page_len
op_assign
id|len
suffix:semicolon
id|tail-&gt;iov_base
op_assign
id|buf
op_plus
id|offset
suffix:semicolon
id|tail-&gt;iov_len
op_assign
id|buflen
op_minus
id|offset
suffix:semicolon
id|xdr-&gt;len
op_add_assign
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Realign the iovec if the server missed out some reply elements&n; * (such as post-op attributes,...)&n; * Note: This is a simple implementation that assumes that&n; *            len &lt;= iov-&gt;iov_len !!!&n; *       The RPC header (assumed to be the 1st element in the iov array)&n; *            is not shifted.&n; */
DECL|function|xdr_shift_iovec
r_void
id|xdr_shift_iovec
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
r_int
id|nr
comma
r_int
id|len
)paren
(brace
r_struct
id|iovec
op_star
id|pvec
suffix:semicolon
r_for
c_loop
(paren
id|pvec
op_assign
id|iov
op_plus
id|nr
op_minus
l_int|1
suffix:semicolon
id|nr
OG
l_int|1
suffix:semicolon
id|nr
op_decrement
comma
id|pvec
op_decrement
)paren
(brace
r_struct
id|iovec
op_star
id|svec
op_assign
id|pvec
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|pvec-&gt;iov_len
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;RPC: Urk! Large shift of short iovec.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memmove
c_func
(paren
(paren
r_char
op_star
)paren
id|pvec-&gt;iov_base
op_plus
id|len
comma
id|pvec-&gt;iov_base
comma
id|pvec-&gt;iov_len
op_minus
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|svec-&gt;iov_len
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;RPC: Urk! Large shift of short iovec.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|pvec-&gt;iov_base
comma
(paren
r_char
op_star
)paren
id|svec-&gt;iov_base
op_plus
id|svec-&gt;iov_len
op_minus
id|len
comma
id|len
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Map a struct xdr_buf into an iovec array.&n; */
DECL|function|xdr_kmap
r_int
id|xdr_kmap
c_func
(paren
r_struct
id|iovec
op_star
id|iov_base
comma
r_struct
id|xdr_buf
op_star
id|xdr
comma
r_int
id|base
)paren
(brace
r_struct
id|iovec
op_star
id|iov
op_assign
id|iov_base
suffix:semicolon
r_struct
id|page
op_star
op_star
id|ppage
op_assign
id|xdr-&gt;pages
suffix:semicolon
r_int
r_int
id|len
comma
id|pglen
op_assign
id|xdr-&gt;page_len
suffix:semicolon
id|len
op_assign
id|xdr-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
r_if
c_cond
(paren
id|base
OL
id|len
)paren
(brace
id|iov-&gt;iov_len
op_assign
id|len
op_minus
id|base
suffix:semicolon
id|iov-&gt;iov_base
op_assign
(paren
r_char
op_star
)paren
id|xdr-&gt;head
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|base
suffix:semicolon
id|iov
op_increment
suffix:semicolon
id|base
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|base
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pglen
op_eq
l_int|0
)paren
r_goto
id|map_tail
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ge
id|pglen
)paren
(brace
id|base
op_sub_assign
id|pglen
suffix:semicolon
r_goto
id|map_tail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_logical_or
id|xdr-&gt;page_base
)paren
(brace
id|pglen
op_sub_assign
id|base
suffix:semicolon
id|base
op_add_assign
id|xdr-&gt;page_base
suffix:semicolon
id|ppage
op_add_assign
id|base
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|base
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
)brace
r_do
(brace
id|len
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|iov-&gt;iov_base
op_assign
id|kmap
c_func
(paren
op_star
id|ppage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
(brace
id|iov-&gt;iov_base
op_add_assign
id|base
suffix:semicolon
id|len
op_sub_assign
id|base
suffix:semicolon
id|base
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pglen
OL
id|len
)paren
id|len
op_assign
id|pglen
suffix:semicolon
id|iov-&gt;iov_len
op_assign
id|len
suffix:semicolon
id|iov
op_increment
suffix:semicolon
id|ppage
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|pglen
op_sub_assign
id|len
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|map_tail
suffix:colon
r_if
c_cond
(paren
id|xdr-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_len
)paren
(brace
id|iov-&gt;iov_len
op_assign
id|xdr-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_len
op_minus
id|base
suffix:semicolon
id|iov-&gt;iov_base
op_assign
(paren
r_char
op_star
)paren
id|xdr-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|base
suffix:semicolon
id|iov
op_increment
suffix:semicolon
)brace
r_return
(paren
id|iov
op_minus
id|iov_base
)paren
suffix:semicolon
)brace
DECL|function|xdr_kunmap
r_void
id|xdr_kunmap
c_func
(paren
r_struct
id|xdr_buf
op_star
id|xdr
comma
r_int
id|base
)paren
(brace
r_struct
id|page
op_star
op_star
id|ppage
op_assign
id|xdr-&gt;pages
suffix:semicolon
r_int
r_int
id|pglen
op_assign
id|xdr-&gt;page_len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pglen
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|base
OG
id|xdr-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
)paren
id|base
op_sub_assign
id|xdr-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
r_else
id|base
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ge
id|pglen
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|base
op_logical_or
id|xdr-&gt;page_base
)paren
(brace
id|pglen
op_sub_assign
id|base
suffix:semicolon
id|base
op_add_assign
id|xdr-&gt;page_base
suffix:semicolon
id|ppage
op_add_assign
id|base
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
multiline_comment|/* Note: The offset means that the length of the first&n;&t;&t; * page is really (PAGE_CACHE_SIZE - (base &amp; ~PAGE_CACHE_MASK)).&n;&t;&t; * In order to avoid an extra test inside the loop,&n;&t;&t; * we bump pglen here, and just subtract PAGE_CACHE_SIZE... */
id|pglen
op_add_assign
id|base
op_amp
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|flush_dcache_page
c_func
(paren
op_star
id|ppage
)paren
suffix:semicolon
id|kunmap
c_func
(paren
op_star
id|ppage
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pglen
op_le
id|PAGE_CACHE_SIZE
)paren
r_break
suffix:semicolon
id|pglen
op_sub_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|ppage
op_increment
suffix:semicolon
)brace
)brace
r_void
DECL|function|xdr_partial_copy_from_skb
id|xdr_partial_copy_from_skb
c_func
(paren
r_struct
id|xdr_buf
op_star
id|xdr
comma
r_int
r_int
id|base
comma
id|skb_reader_t
op_star
id|desc
comma
id|skb_read_actor_t
id|copy_actor
)paren
(brace
r_struct
id|page
op_star
op_star
id|ppage
op_assign
id|xdr-&gt;pages
suffix:semicolon
r_int
r_int
id|len
comma
id|pglen
op_assign
id|xdr-&gt;page_len
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|len
op_assign
id|xdr-&gt;head
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
r_if
c_cond
(paren
id|base
OL
id|len
)paren
(brace
id|len
op_sub_assign
id|base
suffix:semicolon
id|ret
op_assign
id|copy_actor
c_func
(paren
id|desc
comma
(paren
r_char
op_star
)paren
id|xdr-&gt;head
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|len
op_logical_or
op_logical_neg
id|desc-&gt;count
)paren
r_return
suffix:semicolon
id|base
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|base
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pglen
op_eq
l_int|0
)paren
r_goto
id|copy_tail
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ge
id|pglen
)paren
(brace
id|base
op_sub_assign
id|pglen
suffix:semicolon
r_goto
id|copy_tail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|base
op_logical_or
id|xdr-&gt;page_base
)paren
(brace
id|pglen
op_sub_assign
id|base
suffix:semicolon
id|base
op_add_assign
id|xdr-&gt;page_base
suffix:semicolon
id|ppage
op_add_assign
id|base
op_rshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|base
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
)brace
r_do
(brace
r_char
op_star
id|kaddr
suffix:semicolon
id|len
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|kaddr
op_assign
id|kmap_atomic
c_func
(paren
op_star
id|ppage
comma
id|KM_SKB_SUNRPC_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
)paren
(brace
id|len
op_sub_assign
id|base
suffix:semicolon
r_if
c_cond
(paren
id|pglen
OL
id|len
)paren
id|len
op_assign
id|pglen
suffix:semicolon
id|ret
op_assign
id|copy_actor
c_func
(paren
id|desc
comma
id|kaddr
op_plus
id|base
comma
id|len
)paren
suffix:semicolon
id|base
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pglen
OL
id|len
)paren
id|len
op_assign
id|pglen
suffix:semicolon
id|ret
op_assign
id|copy_actor
c_func
(paren
id|desc
comma
id|kaddr
comma
id|len
)paren
suffix:semicolon
)brace
id|flush_dcache_page
c_func
(paren
op_star
id|ppage
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|kaddr
comma
id|KM_SKB_SUNRPC_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|len
op_logical_or
op_logical_neg
id|desc-&gt;count
)paren
r_return
suffix:semicolon
id|ppage
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|pglen
op_sub_assign
id|len
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|copy_tail
suffix:colon
id|len
op_assign
id|xdr-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
id|copy_actor
c_func
(paren
id|desc
comma
(paren
r_char
op_star
)paren
id|xdr-&gt;tail
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|base
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Helper routines for doing &squot;memmove&squot; like operations on a struct xdr_buf&n; *&n; * _shift_data_right_pages&n; * @pages: vector of pages containing both the source and dest memory area.&n; * @pgto_base: page vector address of destination&n; * @pgfrom_base: page vector address of source&n; * @len: number of bytes to copy&n; *&n; * Note: the addresses pgto_base and pgfrom_base are both calculated in&n; *       the same way:&n; *            if a memory area starts at byte &squot;base&squot; in page &squot;pages[i]&squot;,&n; *            then its address is given as (i &lt;&lt; PAGE_CACHE_SHIFT) + base&n; * Also note: pgfrom_base must be &lt; pgto_base, but the memory areas&n; * &t;they point to may overlap.&n; */
r_static
r_void
DECL|function|_shift_data_right_pages
id|_shift_data_right_pages
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|pgto_base
comma
r_int
id|pgfrom_base
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
op_star
id|pgfrom
comma
op_star
op_star
id|pgto
suffix:semicolon
r_char
op_star
id|vfrom
comma
op_star
id|vto
suffix:semicolon
r_int
id|copy
suffix:semicolon
id|BUG_ON
c_func
(paren
id|pgto_base
op_le
id|pgfrom_base
)paren
suffix:semicolon
id|pgto_base
op_add_assign
id|len
suffix:semicolon
id|pgfrom_base
op_add_assign
id|len
suffix:semicolon
id|pgto
op_assign
id|pages
op_plus
(paren
id|pgto_base
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|pgfrom
op_assign
id|pages
op_plus
(paren
id|pgfrom_base
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|pgto_base
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
id|pgfrom_base
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_do
(brace
multiline_comment|/* Are any pointers crossing a page boundary? */
r_if
c_cond
(paren
id|pgto_base
op_eq
l_int|0
)paren
(brace
id|pgto_base
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|pgto
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pgfrom_base
op_eq
l_int|0
)paren
(brace
id|pgfrom_base
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|pgfrom
op_decrement
suffix:semicolon
)brace
id|copy
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|pgto_base
)paren
id|copy
op_assign
id|pgto_base
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|pgfrom_base
)paren
id|copy
op_assign
id|pgfrom_base
suffix:semicolon
id|pgto_base
op_sub_assign
id|copy
suffix:semicolon
id|pgfrom_base
op_sub_assign
id|copy
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
op_star
id|pgto
comma
id|KM_USER0
)paren
suffix:semicolon
id|vfrom
op_assign
id|kmap_atomic
c_func
(paren
op_star
id|pgfrom
comma
id|KM_USER1
)paren
suffix:semicolon
id|memmove
c_func
(paren
id|vto
op_plus
id|pgto_base
comma
id|vfrom
op_plus
id|pgfrom_base
comma
id|copy
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vfrom
comma
id|KM_USER1
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vto
comma
id|KM_USER0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * _copy_to_pages&n; * @pages: array of pages&n; * @pgbase: page vector address of destination&n; * @p: pointer to source data&n; * @len: length&n; *&n; * Copies data from an arbitrary memory location into an array of pages&n; * The copy is assumed to be non-overlapping.&n; */
r_static
r_void
DECL|function|_copy_to_pages
id|_copy_to_pages
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|pgbase
comma
r_const
r_char
op_star
id|p
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
op_star
id|pgto
suffix:semicolon
r_char
op_star
id|vto
suffix:semicolon
r_int
id|copy
suffix:semicolon
id|pgto
op_assign
id|pages
op_plus
(paren
id|pgbase
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|pgbase
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_do
(brace
id|copy
op_assign
id|PAGE_CACHE_SIZE
op_minus
id|pgbase
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|vto
op_assign
id|kmap_atomic
c_func
(paren
op_star
id|pgto
comma
id|KM_USER0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|vto
op_plus
id|pgbase
comma
id|p
comma
id|copy
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vto
comma
id|KM_USER0
)paren
suffix:semicolon
id|pgbase
op_add_assign
id|copy
suffix:semicolon
r_if
c_cond
(paren
id|pgbase
op_eq
id|PAGE_CACHE_SIZE
)paren
(brace
id|pgbase
op_assign
l_int|0
suffix:semicolon
id|pgto
op_increment
suffix:semicolon
)brace
id|p
op_add_assign
id|copy
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * _copy_from_pages&n; * @p: pointer to destination&n; * @pages: array of pages&n; * @pgbase: offset of source data&n; * @len: length&n; *&n; * Copies data into an arbitrary memory location from an array of pages&n; * The copy is assumed to be non-overlapping.&n; */
r_static
r_void
DECL|function|_copy_from_pages
id|_copy_from_pages
c_func
(paren
r_char
op_star
id|p
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|pgbase
comma
r_int
id|len
)paren
(brace
r_struct
id|page
op_star
op_star
id|pgfrom
suffix:semicolon
r_char
op_star
id|vfrom
suffix:semicolon
r_int
id|copy
suffix:semicolon
id|pgfrom
op_assign
id|pages
op_plus
(paren
id|pgbase
op_rshift
id|PAGE_CACHE_SHIFT
)paren
suffix:semicolon
id|pgbase
op_and_assign
op_complement
id|PAGE_CACHE_MASK
suffix:semicolon
r_do
(brace
id|copy
op_assign
id|PAGE_CACHE_SIZE
op_minus
id|pgbase
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|vfrom
op_assign
id|kmap_atomic
c_func
(paren
op_star
id|pgfrom
comma
id|KM_USER0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|vfrom
op_plus
id|pgbase
comma
id|copy
)paren
suffix:semicolon
id|kunmap_atomic
c_func
(paren
id|vfrom
comma
id|KM_USER0
)paren
suffix:semicolon
id|pgbase
op_add_assign
id|copy
suffix:semicolon
r_if
c_cond
(paren
id|pgbase
op_eq
id|PAGE_CACHE_SIZE
)paren
(brace
id|pgbase
op_assign
l_int|0
suffix:semicolon
id|pgfrom
op_increment
suffix:semicolon
)brace
id|p
op_add_assign
id|copy
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * xdr_shrink_bufhead&n; * @buf: xdr_buf&n; * @len: bytes to remove from buf-&gt;head[0]&n; *&n; * Shrinks XDR buffer&squot;s header iovec buf-&gt;head[0] by &n; * &squot;len&squot; bytes. The extra data is not lost, but is instead&n; * moved into the inlined pages and/or the tail.&n; */
r_void
DECL|function|xdr_shrink_bufhead
id|xdr_shrink_bufhead
c_func
(paren
r_struct
id|xdr_buf
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|iovec
op_star
id|head
comma
op_star
id|tail
suffix:semicolon
r_int
id|copy
comma
id|offs
suffix:semicolon
r_int
r_int
id|pglen
op_assign
id|buf-&gt;page_len
suffix:semicolon
id|tail
op_assign
id|buf-&gt;tail
suffix:semicolon
id|head
op_assign
id|buf-&gt;head
suffix:semicolon
id|BUG_ON
(paren
id|len
OG
id|head-&gt;iov_len
)paren
suffix:semicolon
multiline_comment|/* Shift the tail first */
r_if
c_cond
(paren
id|tail-&gt;iov_len
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tail-&gt;iov_len
OG
id|len
)paren
(brace
id|copy
op_assign
id|tail-&gt;iov_len
op_minus
id|len
suffix:semicolon
id|memmove
c_func
(paren
(paren
r_char
op_star
)paren
id|tail-&gt;iov_base
op_plus
id|len
comma
id|tail-&gt;iov_base
comma
id|copy
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy from the inlined pages into the tail */
id|copy
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|pglen
)paren
id|copy
op_assign
id|pglen
suffix:semicolon
id|offs
op_assign
id|len
op_minus
id|copy
suffix:semicolon
r_if
c_cond
(paren
id|offs
op_ge
id|tail-&gt;iov_len
)paren
id|copy
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|copy
OG
id|tail-&gt;iov_len
op_minus
id|offs
)paren
id|copy
op_assign
id|tail-&gt;iov_len
op_minus
id|offs
suffix:semicolon
r_if
c_cond
(paren
id|copy
op_ne
l_int|0
)paren
id|_copy_from_pages
c_func
(paren
(paren
r_char
op_star
)paren
id|tail-&gt;iov_base
op_plus
id|offs
comma
id|buf-&gt;pages
comma
id|buf-&gt;page_base
op_plus
id|pglen
op_plus
id|offs
op_minus
id|len
comma
id|copy
)paren
suffix:semicolon
multiline_comment|/* Do we also need to copy data from the head into the tail ? */
r_if
c_cond
(paren
id|len
OG
id|pglen
)paren
(brace
id|offs
op_assign
id|copy
op_assign
id|len
op_minus
id|pglen
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|tail-&gt;iov_len
)paren
id|copy
op_assign
id|tail-&gt;iov_len
suffix:semicolon
id|memcpy
c_func
(paren
id|tail-&gt;iov_base
comma
(paren
r_char
op_star
)paren
id|head-&gt;iov_base
op_plus
id|head-&gt;iov_len
op_minus
id|offs
comma
id|copy
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Now handle pages */
r_if
c_cond
(paren
id|pglen
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|pglen
OG
id|len
)paren
id|_shift_data_right_pages
c_func
(paren
id|buf-&gt;pages
comma
id|buf-&gt;page_base
op_plus
id|len
comma
id|buf-&gt;page_base
comma
id|pglen
op_minus
id|len
)paren
suffix:semicolon
id|copy
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|pglen
)paren
id|copy
op_assign
id|pglen
suffix:semicolon
id|_copy_to_pages
c_func
(paren
id|buf-&gt;pages
comma
id|buf-&gt;page_base
comma
(paren
r_char
op_star
)paren
id|head-&gt;iov_base
op_plus
id|head-&gt;iov_len
op_minus
id|len
comma
id|copy
)paren
suffix:semicolon
)brace
id|head-&gt;iov_len
op_sub_assign
id|len
suffix:semicolon
id|buf-&gt;len
op_sub_assign
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * xdr_shrink_pagelen&n; * @buf: xdr_buf&n; * @len: bytes to remove from buf-&gt;pages&n; *&n; * Shrinks XDR buffer&squot;s page array buf-&gt;pages by &n; * &squot;len&squot; bytes. The extra data is not lost, but is instead&n; * moved into the tail.&n; */
r_void
DECL|function|xdr_shrink_pagelen
id|xdr_shrink_pagelen
c_func
(paren
r_struct
id|xdr_buf
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|iovec
op_star
id|tail
suffix:semicolon
r_int
id|copy
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
r_int
id|pglen
op_assign
id|buf-&gt;page_len
suffix:semicolon
id|tail
op_assign
id|buf-&gt;tail
suffix:semicolon
id|BUG_ON
(paren
id|len
OG
id|pglen
)paren
suffix:semicolon
multiline_comment|/* Shift the tail first */
r_if
c_cond
(paren
id|tail-&gt;iov_len
op_ne
l_int|0
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|tail-&gt;iov_base
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|tail-&gt;iov_len
OG
id|len
)paren
(brace
id|copy
op_assign
id|tail-&gt;iov_len
op_minus
id|len
suffix:semicolon
id|memmove
c_func
(paren
id|p
comma
id|tail-&gt;iov_base
comma
id|copy
)paren
suffix:semicolon
)brace
r_else
id|buf-&gt;len
op_sub_assign
id|len
suffix:semicolon
multiline_comment|/* Copy from the inlined pages into the tail */
id|copy
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|tail-&gt;iov_len
)paren
id|copy
op_assign
id|tail-&gt;iov_len
suffix:semicolon
id|_copy_from_pages
c_func
(paren
(paren
r_char
op_star
)paren
id|tail-&gt;iov_base
comma
id|buf-&gt;pages
comma
id|buf-&gt;page_base
op_plus
id|pglen
op_minus
id|len
comma
id|copy
)paren
suffix:semicolon
)brace
id|buf-&gt;page_len
op_sub_assign
id|len
suffix:semicolon
id|buf-&gt;len
op_sub_assign
id|len
suffix:semicolon
)brace
r_void
DECL|function|xdr_shift_buf
id|xdr_shift_buf
c_func
(paren
r_struct
id|xdr_buf
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|xdr_shrink_bufhead
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
r_void
DECL|function|xdr_write_pages
id|xdr_write_pages
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
r_int
id|base
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|xdr_buf
op_star
id|buf
op_assign
id|xdr-&gt;buf
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
op_assign
id|buf-&gt;tail
suffix:semicolon
id|buf-&gt;pages
op_assign
id|pages
suffix:semicolon
id|buf-&gt;page_base
op_assign
id|base
suffix:semicolon
id|buf-&gt;page_len
op_assign
id|len
suffix:semicolon
id|iov-&gt;iov_base
op_assign
(paren
r_char
op_star
)paren
id|xdr-&gt;p
suffix:semicolon
id|iov-&gt;iov_len
op_assign
l_int|0
suffix:semicolon
id|xdr-&gt;iov
op_assign
id|iov
suffix:semicolon
r_if
c_cond
(paren
id|len
op_amp
l_int|3
)paren
(brace
r_int
r_int
id|pad
op_assign
l_int|4
op_minus
(paren
id|len
op_amp
l_int|3
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|xdr-&gt;p
op_ge
id|xdr-&gt;end
)paren
suffix:semicolon
id|iov-&gt;iov_base
op_assign
(paren
r_char
op_star
)paren
id|xdr-&gt;p
op_plus
(paren
id|len
op_amp
l_int|3
)paren
suffix:semicolon
id|iov-&gt;iov_len
op_add_assign
id|pad
suffix:semicolon
id|len
op_add_assign
id|pad
suffix:semicolon
op_star
id|xdr-&gt;p
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
id|buf-&gt;len
op_add_assign
id|len
suffix:semicolon
)brace
r_void
DECL|function|xdr_read_pages
id|xdr_read_pages
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|xdr_buf
op_star
id|buf
op_assign
id|xdr-&gt;buf
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
id|ssize_t
id|shift
suffix:semicolon
multiline_comment|/* Realign pages to current pointer position */
id|iov
op_assign
id|buf-&gt;head
suffix:semicolon
id|shift
op_assign
id|iov-&gt;iov_len
op_plus
(paren
r_char
op_star
)paren
id|iov-&gt;iov_base
op_minus
(paren
r_char
op_star
)paren
id|xdr-&gt;p
suffix:semicolon
r_if
c_cond
(paren
id|shift
OG
l_int|0
)paren
id|xdr_shrink_bufhead
c_func
(paren
id|buf
comma
id|shift
)paren
suffix:semicolon
multiline_comment|/* Truncate page data and move it into the tail */
id|len
op_assign
id|XDR_QUADLEN
c_func
(paren
id|len
)paren
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;page_len
OG
id|len
)paren
id|xdr_shrink_pagelen
c_func
(paren
id|buf
comma
id|buf-&gt;page_len
op_minus
id|len
)paren
suffix:semicolon
id|xdr-&gt;iov
op_assign
id|iov
op_assign
id|buf-&gt;tail
suffix:semicolon
id|xdr-&gt;p
op_assign
(paren
r_uint32
op_star
)paren
id|iov-&gt;iov_base
suffix:semicolon
id|xdr-&gt;end
op_assign
(paren
r_uint32
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|iov-&gt;iov_base
op_plus
id|iov-&gt;iov_len
)paren
suffix:semicolon
)brace
eof
