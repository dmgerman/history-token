multiline_comment|/*&n; * include/linux/sunrpc/xdr.h&n; *&n; * Copyright (C) 1995-1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _SUNRPC_XDR_H_
DECL|macro|_SUNRPC_XDR_H_
mdefine_line|#define _SUNRPC_XDR_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*&n; * Buffer adjustment&n; */
DECL|macro|XDR_QUADLEN
mdefine_line|#define XDR_QUADLEN(l)&t;&t;(((l) + 3) &gt;&gt; 2)
multiline_comment|/*&n; * Generic opaque `network object.&squot; At the kernel level, this type&n; * is used only by lockd.&n; */
DECL|macro|XDR_MAX_NETOBJ
mdefine_line|#define XDR_MAX_NETOBJ&t;&t;1024
DECL|struct|xdr_netobj
r_struct
id|xdr_netobj
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the generic XDR function. rqstp is either a rpc_rqst (client&n; * side) or svc_rqst pointer (server side).&n; * Encode functions always assume there&squot;s enough room in the buffer.&n; */
DECL|typedef|kxdrproc_t
r_typedef
r_int
(paren
op_star
id|kxdrproc_t
)paren
(paren
r_void
op_star
id|rqstp
comma
id|u32
op_star
id|data
comma
r_void
op_star
id|obj
)paren
suffix:semicolon
multiline_comment|/*&n; * Basic structure for transmission/reception of a client XDR message.&n; * Features a header (for a linear buffer containing RPC headers&n; * and the data payload for short messages), and then an array of&n; * pages.&n; * The tail iovec allows you to append data after the page array. Its&n; * main interest is for appending padding to the pages in order to&n; * satisfy the int_32-alignment requirements in RFC1832.&n; *&n; * For the future, we might want to string several of these together&n; * in a list if anybody wants to make use of NFSv4 COMPOUND&n; * operations and/or has a need for scatter/gather involving pages.&n; */
DECL|struct|xdr_buf
r_struct
id|xdr_buf
(brace
DECL|member|head
r_struct
id|iovec
id|head
(braket
l_int|1
)braket
comma
multiline_comment|/* RPC header + non-page data */
DECL|member|tail
id|tail
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Appended after page data */
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
multiline_comment|/* Array of contiguous pages */
DECL|member|page_base
r_int
r_int
id|page_base
comma
multiline_comment|/* Start of page data */
DECL|member|page_len
id|page_len
suffix:semicolon
multiline_comment|/* Length of page data */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Total length of data */
)brace
suffix:semicolon
multiline_comment|/*&n; * pre-xdr&squot;ed macros.&n; */
DECL|macro|xdr_zero
mdefine_line|#define&t;xdr_zero&t;__constant_htonl(0)
DECL|macro|xdr_one
mdefine_line|#define&t;xdr_one&t;&t;__constant_htonl(1)
DECL|macro|xdr_two
mdefine_line|#define&t;xdr_two&t;&t;__constant_htonl(2)
DECL|macro|rpc_success
mdefine_line|#define&t;rpc_success&t;&t;__constant_htonl(RPC_SUCCESS)
DECL|macro|rpc_prog_unavail
mdefine_line|#define&t;rpc_prog_unavail&t;__constant_htonl(RPC_PROG_UNAVAIL)
DECL|macro|rpc_prog_mismatch
mdefine_line|#define&t;rpc_prog_mismatch&t;__constant_htonl(RPC_PROG_MISMATCH)
DECL|macro|rpc_proc_unavail
mdefine_line|#define&t;rpc_proc_unavail&t;__constant_htonl(RPC_PROC_UNAVAIL)
DECL|macro|rpc_garbage_args
mdefine_line|#define&t;rpc_garbage_args&t;__constant_htonl(RPC_GARBAGE_ARGS)
DECL|macro|rpc_system_err
mdefine_line|#define&t;rpc_system_err&t;&t;__constant_htonl(RPC_SYSTEM_ERR)
DECL|macro|rpc_auth_ok
mdefine_line|#define&t;rpc_auth_ok&t;&t;__constant_htonl(RPC_AUTH_OK)
DECL|macro|rpc_autherr_badcred
mdefine_line|#define&t;rpc_autherr_badcred&t;__constant_htonl(RPC_AUTH_BADCRED)
DECL|macro|rpc_autherr_rejectedcred
mdefine_line|#define&t;rpc_autherr_rejectedcred __constant_htonl(RPC_AUTH_REJECTEDCRED)
DECL|macro|rpc_autherr_badverf
mdefine_line|#define&t;rpc_autherr_badverf&t;__constant_htonl(RPC_AUTH_BADVERF)
DECL|macro|rpc_autherr_rejectedverf
mdefine_line|#define&t;rpc_autherr_rejectedverf __constant_htonl(RPC_AUTH_REJECTEDVERF)
DECL|macro|rpc_autherr_tooweak
mdefine_line|#define&t;rpc_autherr_tooweak&t;__constant_htonl(RPC_AUTH_TOOWEAK)
multiline_comment|/*&n; * Miscellaneous XDR helper functions&n; */
id|u32
op_star
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
id|s
comma
r_int
r_int
id|len
)paren
suffix:semicolon
id|u32
op_star
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
id|s
)paren
suffix:semicolon
id|u32
op_star
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
suffix:semicolon
id|u32
op_star
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
suffix:semicolon
id|u32
op_star
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
)paren
suffix:semicolon
id|u32
op_star
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
)paren
suffix:semicolon
id|u32
op_star
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
suffix:semicolon
r_void
id|xdr_encode_pages
c_func
(paren
r_struct
id|xdr_buf
op_star
comma
r_struct
id|page
op_star
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|xdr_inline_pages
c_func
(paren
r_struct
id|xdr_buf
op_star
comma
r_int
r_int
comma
r_struct
id|page
op_star
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Decode 64bit quantities (NFSv3 support)&n; */
r_static
r_inline
id|u32
op_star
DECL|function|xdr_encode_hyper
id|xdr_encode_hyper
c_func
(paren
id|u32
op_star
id|p
comma
id|__u64
id|val
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|val
op_rshift
l_int|32
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|val
op_amp
l_int|0xFFFFFFFF
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_hyper
id|xdr_decode_hyper
c_func
(paren
id|u32
op_star
id|p
comma
id|__u64
op_star
id|valp
)paren
(brace
op_star
id|valp
op_assign
(paren
(paren
id|__u64
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_lshift
l_int|32
suffix:semicolon
op_star
id|valp
op_or_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust iovec to reflect end of xdr&squot;ed data (RPC client XDR)&n; */
r_static
r_inline
r_int
DECL|function|xdr_adjust_iovec
id|xdr_adjust_iovec
c_func
(paren
r_struct
id|iovec
op_star
id|iov
comma
id|u32
op_star
id|p
)paren
(brace
r_return
id|iov-&gt;iov_len
op_assign
(paren
(paren
id|u8
op_star
)paren
id|p
op_minus
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
)paren
suffix:semicolon
)brace
r_void
id|xdr_shift_iovec
c_func
(paren
r_struct
id|iovec
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Maximum number of iov&squot;s we use.&n; */
DECL|macro|MAX_IOVEC
mdefine_line|#define MAX_IOVEC&t;(12)
multiline_comment|/*&n; * XDR buffer helper functions&n; */
r_extern
r_int
id|xdr_kmap
c_func
(paren
r_struct
id|iovec
op_star
comma
r_struct
id|xdr_buf
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xdr_kunmap
c_func
(paren
r_struct
id|xdr_buf
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|xdr_shift_buf
c_func
(paren
r_struct
id|xdr_buf
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Helper structure for copying from an sk_buff.&n; */
r_typedef
r_struct
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|csum
r_int
r_int
id|csum
suffix:semicolon
DECL|typedef|skb_reader_t
)brace
id|skb_reader_t
suffix:semicolon
DECL|typedef|skb_read_actor_t
r_typedef
r_int
(paren
op_star
id|skb_read_actor_t
)paren
(paren
id|skb_reader_t
op_star
id|desc
comma
r_void
op_star
id|to
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|xdr_partial_copy_from_skb
c_func
(paren
r_struct
id|xdr_buf
op_star
comma
r_int
r_int
comma
id|skb_reader_t
op_star
comma
id|skb_read_actor_t
)paren
suffix:semicolon
multiline_comment|/*&n; * Provide some simple tools for XDR buffer overflow-checking etc.&n; */
DECL|struct|xdr_stream
r_struct
id|xdr_stream
(brace
DECL|member|p
r_uint32
op_star
id|p
suffix:semicolon
multiline_comment|/* start of available buffer */
DECL|member|buf
r_struct
id|xdr_buf
op_star
id|buf
suffix:semicolon
multiline_comment|/* XDR buffer to read/write */
DECL|member|end
r_uint32
op_star
id|end
suffix:semicolon
multiline_comment|/* end of available buffer space */
DECL|member|iov
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
multiline_comment|/* pointer to the current iovec */
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize an xdr_stream for encoding data.&n; *&n; * Note: at the moment the RPC client only passes the length of our&n; *&t; scratch buffer in the xdr_buf&squot;s header iovec. Previously this&n; *&t; meant we needed to call xdr_adjust_iovec() after encoding the&n; *&t; data. With the new scheme, the xdr_stream manages the details&n; *&t; of the buffer length, and takes care of adjusting the iovec&n; *&t; length for us.&n; */
r_static
r_inline
r_void
DECL|function|xdr_init_encode
id|xdr_init_encode
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_struct
id|xdr_buf
op_star
id|buf
comma
r_uint32
op_star
id|p
)paren
(brace
r_struct
id|iovec
op_star
id|iov
op_assign
id|buf-&gt;head
suffix:semicolon
id|xdr-&gt;buf
op_assign
id|buf
suffix:semicolon
id|xdr-&gt;iov
op_assign
id|iov
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
id|buf-&gt;len
op_assign
id|iov-&gt;iov_len
op_assign
(paren
r_char
op_star
)paren
id|p
op_minus
(paren
r_char
op_star
)paren
id|iov-&gt;iov_base
suffix:semicolon
id|xdr-&gt;p
op_assign
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Check that we have enough buffer space to encode &squot;nbytes&squot; more&n; * bytes of data. If so, update the total xdr_buf length, and&n; * adjust the length of the current iovec.&n; */
r_static
r_inline
r_uint32
op_star
DECL|function|xdr_reserve_space
id|xdr_reserve_space
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_int
id|nbytes
)paren
(brace
r_uint32
op_star
id|p
op_assign
id|xdr-&gt;p
suffix:semicolon
r_uint32
op_star
id|q
suffix:semicolon
multiline_comment|/* align nbytes on the next 32-bit boundary */
id|nbytes
op_add_assign
l_int|3
suffix:semicolon
id|nbytes
op_and_assign
op_complement
l_int|3
suffix:semicolon
id|q
op_assign
id|p
op_plus
(paren
id|nbytes
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|q
OG
id|xdr-&gt;end
op_logical_or
id|q
OL
id|p
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|xdr-&gt;p
op_assign
id|q
suffix:semicolon
id|xdr-&gt;iov-&gt;iov_len
op_add_assign
id|nbytes
suffix:semicolon
id|xdr-&gt;buf-&gt;len
op_add_assign
id|nbytes
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
r_extern
r_void
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
suffix:semicolon
r_extern
r_void
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
suffix:semicolon
multiline_comment|/*&n; * Initialize an xdr_stream for decoding data.&n; */
r_static
r_inline
r_void
DECL|function|xdr_init_decode
id|xdr_init_decode
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_struct
id|xdr_buf
op_star
id|buf
comma
r_uint32
op_star
id|p
)paren
(brace
r_struct
id|iovec
op_star
id|iov
op_assign
id|buf-&gt;head
suffix:semicolon
id|xdr-&gt;buf
op_assign
id|buf
suffix:semicolon
id|xdr-&gt;iov
op_assign
id|iov
suffix:semicolon
id|xdr-&gt;p
op_assign
id|p
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
multiline_comment|/*&n; * Check if the input buffer is long enough to enable us to decode&n; * &squot;nbytes&squot; more bytes of data starting at the current position.&n; * If so return the current pointer, then update the current&n; * position.&n; */
r_static
r_inline
r_uint32
op_star
DECL|function|xdr_inline_decode
id|xdr_inline_decode
c_func
(paren
r_struct
id|xdr_stream
op_star
id|xdr
comma
r_int
id|nbytes
)paren
(brace
r_uint32
op_star
id|p
op_assign
id|xdr-&gt;p
suffix:semicolon
r_uint32
op_star
id|q
op_assign
id|p
op_plus
id|XDR_QUADLEN
c_func
(paren
id|nbytes
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|q
OG
id|xdr-&gt;end
op_logical_or
id|q
OL
id|p
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|xdr-&gt;p
op_assign
id|q
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SUNRPC_XDR_H_ */
eof
