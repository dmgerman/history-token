macro_line|#ifndef _H8300_CHECKSUM_H
DECL|macro|_H8300_CHECKSUM_H
mdefine_line|#define _H8300_CHECKSUM_H
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
id|__asm__
c_func
(paren
l_string|&quot;mov.l %0,er0&bslash;n&bslash;t&quot;
l_string|&quot;add.w e0,r0&bslash;n&bslash;t&quot;
l_string|&quot;xor.w e0,e0&bslash;n&bslash;t&quot;
l_string|&quot;rotxl.w e0&bslash;n&bslash;t&quot;
l_string|&quot;add.w e0,r0&bslash;n&bslash;t&quot;
l_string|&quot;sub.w e0,e0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l er0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;er0&quot;
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
l_string|&quot;sub.l er0,er0&bslash;n&bslash;t&quot;
l_string|&quot;add.l %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;addx&t;#0,r0l&bslash;n&bslash;t&quot;
l_string|&quot;add.l&t;%3,%0&bslash;n&bslash;t&quot;
l_string|&quot;addx&t;#0,r0l&bslash;n&bslash;t&quot;
l_string|&quot;add.l %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;addx&t;#0,r0l&bslash;n&bslash;t&quot;
l_string|&quot;add.l&t;er0,%0&bslash;n&bslash;t&quot;
l_string|&quot;bcc&t;1f&bslash;n&bslash;t&quot;
l_string|&quot;inc.l&t;#1,%0&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
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
id|len
op_plus
id|proto
)paren
suffix:colon
l_string|&quot;er0&quot;
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
r_extern
r_int
r_int
id|ip_compute_csum
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
)paren
suffix:semicolon
macro_line|#endif /* _H8300_CHECKSUM_H */
eof
