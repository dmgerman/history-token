macro_line|#ifndef _M68K_CHECKSUM_H
DECL|macro|_M68K_CHECKSUM_H
mdefine_line|#define _M68K_CHECKSUM_H
multiline_comment|/*&n; * computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
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
multiline_comment|/*&n; * the same as csum_partial, but copies from src while it&n; * checksums&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_int
r_int
id|csum_partial_copy
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
id|sum
)paren
suffix:semicolon
multiline_comment|/*&n; * the same as csum_partial_copy, but copies from user space.&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_extern
r_int
r_int
id|csum_partial_copy_from_user
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
id|sum
comma
r_int
op_star
id|csum_err
)paren
suffix:semicolon
DECL|macro|csum_partial_copy_nocheck
mdefine_line|#define csum_partial_copy_nocheck(src, dst, len, sum)&t;&bslash;&n;&t;csum_partial_copy((src), (dst), (len), (sum))
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; */
r_static
r_inline
r_int
r_int
DECL|function|ip_fast_csum
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
(brace
r_int
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
id|__asm__
(paren
l_string|&quot;subqw #1,%2&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;movel %1@+,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;addxl %/d0,%0&bslash;n&bslash;t&quot;
l_string|&quot;dbra  %2,1b&bslash;n&bslash;t&quot;
l_string|&quot;movel %0,%/d0&bslash;n&bslash;t&quot;
l_string|&quot;swap  %/d0&bslash;n&bslash;t&quot;
l_string|&quot;addxw %/d0,%0&bslash;n&bslash;t&quot;
l_string|&quot;clrw  %/d0&bslash;n&bslash;t&quot;
l_string|&quot;addxw %/d0,%0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=a&quot;
(paren
id|iph
)paren
comma
l_string|&quot;=d&quot;
(paren
id|ihl
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|iph
)paren
comma
l_string|&quot;2&quot;
(paren
id|ihl
)paren
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
r_return
op_complement
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Fold a partial checksum&n; */
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
op_assign
id|sum
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;swap %1&bslash;n&bslash;t&quot;
l_string|&quot;addw %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;clrw %1&bslash;n&bslash;t&quot;
l_string|&quot;addxw %1, %0&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|sum
)paren
)paren
suffix:semicolon
r_return
op_complement
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
r_static
r_inline
r_int
r_int
DECL|function|csum_tcpudp_nofold
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
(paren
l_string|&quot;addl  %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;clrl %1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|saddr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;1&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;d&quot;
(paren
id|len
op_plus
id|proto
)paren
comma
l_string|&quot;d&quot;
(paren
id|sum
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
r_int
DECL|function|csum_tcpudp_magic
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
(brace
r_return
id|csum_fold
c_func
(paren
id|csum_tcpudp_nofold
c_func
(paren
id|saddr
comma
id|daddr
comma
id|len
comma
id|proto
comma
id|sum
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * this routine is used for miscellaneous IP-like checksums, mainly&n; * in icmp.c&n; */
r_static
r_inline
r_int
r_int
DECL|function|ip_compute_csum
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
DECL|macro|_HAVE_ARCH_IPV6_CSUM
mdefine_line|#define _HAVE_ARCH_IPV6_CSUM
r_static
id|__inline__
r_int
r_int
r_int
DECL|function|csum_ipv6_magic
id|csum_ipv6_magic
c_func
(paren
r_struct
id|in6_addr
op_star
id|saddr
comma
r_struct
id|in6_addr
op_star
id|daddr
comma
id|__u32
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
r_register
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;addl %2@,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@(4),%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@(8),%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@(12),%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %3@,%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %3@(4),%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %3@(8),%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %3@(12),%1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;clrl %1&bslash;n&bslash;t&quot;
l_string|&quot;addxl %1,%0&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;a&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;d&quot;
(paren
id|len
op_plus
id|proto
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
)paren
)paren
suffix:semicolon
r_return
id|csum_fold
c_func
(paren
id|sum
)paren
suffix:semicolon
)brace
macro_line|#endif /* _M68K_CHECKSUM_H */
eof
