macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_CHECKSUM_H
DECL|macro|_PPC_CHECKSUM_H
mdefine_line|#define _PPC_CHECKSUM_H
multiline_comment|/*&n; * computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
r_extern
r_int
r_int
id|csum_partial
c_func
(paren
r_const
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
suffix:semicolon
multiline_comment|/*&n; * Computes the checksum of a memory block at src, length len,&n; * and adds in &quot;sum&quot; (32-bit), while copying the block to dst.&n; * If an access exception occurs on src or dst, it stores -EFAULT&n; * to *src_err or *dst_err respectively (if that pointer is not&n; * NULL), and, for an error on src, zeroes the rest of dst.&n; *&n; * Like csum_partial, this must be called with even lengths,&n; * except for the last fragment.&n; */
r_extern
r_int
r_int
id|csum_partial_copy_generic
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|sum
comma
r_int
op_star
id|src_err
comma
r_int
op_star
id|dst_err
)paren
suffix:semicolon
DECL|macro|csum_partial_copy_from_user
mdefine_line|#define csum_partial_copy_from_user(src, dst, len, sum, errp)&t;&bslash;&n;&t;csum_partial_copy_generic((__force void *)(src), (dst), (len), (sum), (errp), NULL)
multiline_comment|/* FIXME: this needs to be written to really do no check -- Cort */
DECL|macro|csum_partial_copy_nocheck
mdefine_line|#define csum_partial_copy_nocheck(src, dst, len, sum)&t;&bslash;&n;&t;csum_partial_copy_generic((src), (dst), (len), (sum), NULL, NULL)
multiline_comment|/*&n; * turns a 32-bit partial checksum (e.g. from csum_partial) into a&n; * 1&squot;s complement 16-bit checksum.&n; */
DECL|function|csum_fold
r_static
r_inline
r_int
r_int
id|csum_fold
c_func
(paren
r_int
r_int
id|sum
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* swap the two 16-bit halves of sum */
id|__asm__
c_func
(paren
l_string|&quot;rlwinm %0,%1,16,0,31&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sum
)paren
)paren
suffix:semicolon
multiline_comment|/* if there is a carry from adding the two 16-bit halves,&n;&t;   it will carry from the lower half into the upper half,&n;&t;   giving us the correct sum in the upper half. */
id|sum
op_assign
op_complement
(paren
id|sum
op_plus
id|tmp
)paren
op_rshift
l_int|16
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine is used for miscellaneous IP-like checksums, mainly&n; * in icmp.c&n; */
DECL|function|ip_compute_csum
r_static
r_inline
r_int
r_int
id|ip_compute_csum
c_func
(paren
r_int
r_char
op_star
id|buff
comma
r_int
id|len
)paren
(brace
r_return
id|csum_fold
c_func
(paren
id|csum_partial
c_func
(paren
id|buff
comma
id|len
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME: I swiped this one from the sparc and made minor modifications.&n; * It may not be correct.  -- Cort&n; */
DECL|function|csum_tcpudp_nofold
r_static
r_inline
r_int
r_int
id|csum_tcpudp_nofold
c_func
(paren
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|proto
comma
r_int
r_int
id|sum
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;&t;addc %0,%0,%1 &bslash;n&bslash;&n;&t;adde %0,%0,%2 &bslash;n&bslash;&n;&t;adde %0,%0,%3 &bslash;n&bslash;&n;&t;addze %0,%0 &bslash;n&bslash;&n;&t;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;r&quot;
(paren
(paren
id|proto
op_lshift
l_int|16
)paren
op_plus
id|len
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a version of ip_compute_csum() optimized for IP headers,&n; * which always checksum on 4 octet boundaries.  ihl is the number&n; * of 32-bit words and is always &gt;= 5.&n; */
r_extern
r_int
r_int
id|ip_fast_csum
c_func
(paren
r_int
r_char
op_star
id|iph
comma
r_int
r_int
id|ihl
)paren
suffix:semicolon
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
r_extern
r_int
r_int
id|csum_tcpudp_magic
c_func
(paren
r_int
r_int
id|saddr
comma
r_int
r_int
id|daddr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|proto
comma
r_int
r_int
id|sum
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
