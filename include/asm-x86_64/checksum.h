macro_line|#ifndef _X86_64_CHECKSUM_H
DECL|macro|_X86_64_CHECKSUM_H
mdefine_line|#define _X86_64_CHECKSUM_H
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; *&t;By Jorge Cwik &lt;jorge@laser.satlink.net&gt;, adapted for linux by&n; *&t;Arnt Gulbrandsen.&n; */
DECL|function|ip_fast_csum
r_static
r_inline
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
(brace
r_int
r_int
id|sum
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&t;    movl (%1), %0&quot;
l_string|&quot;&bslash;n&t;    subl $4, %2&quot;
l_string|&quot;&bslash;n&t;    jbe 2f&quot;
l_string|&quot;&bslash;n&t;    addl 4(%1), %0&quot;
l_string|&quot;&bslash;n&t;    adcl 8(%1), %0&quot;
l_string|&quot;&bslash;n&t;    adcl 12(%1), %0&quot;
l_string|&quot;&bslash;n1:&t;    adcl 16(%1), %0&quot;
l_string|&quot;&bslash;n&t;    lea 4(%1), %1&quot;
l_string|&quot;&bslash;n&t;    decl %2&quot;
l_string|&quot;&bslash;n&t;    jne&t;1b&quot;
l_string|&quot;&bslash;n&t;    adcl $0, %0&quot;
l_string|&quot;&bslash;n&t;    movl %0, %2&quot;
l_string|&quot;&bslash;n&t;    shrl $16, %0&quot;
l_string|&quot;&bslash;n&t;    addw %w2, %w0&quot;
l_string|&quot;&bslash;n&t;    adcl $0, %0&quot;
l_string|&quot;&bslash;n&t;    notl %0&quot;
l_string|&quot;&bslash;n2:&quot;
multiline_comment|/* Since the input registers which are loaded with iph and ipl&n;&t;   are modified, we must also specify them as outputs, or gcc&n;&t;   will assume they contain their original values. */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|iph
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ihl
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|iph
)paren
comma
l_string|&quot;2&quot;
(paren
id|ihl
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Fold a partial checksum. Note this works on a 32bit unfolded checksum. Make sure&n; *&t;to not mix with 64bit checksums!&n; */
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
l_string|&quot;&bslash;n&t;&t;addl %1,%0&quot;
l_string|&quot;&bslash;n&t;&t;adcl $0xffff,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|sum
op_lshift
l_int|16
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
op_amp
l_int|0xffff0000
)paren
)paren
suffix:semicolon
r_return
(paren
op_complement
id|sum
)paren
op_rshift
l_int|16
suffix:semicolon
)brace
DECL|function|csum_tcpudp_nofold
r_static
r_inline
r_int
r_int
id|csum_tcpudp_nofold
c_func
(paren
r_int
id|saddr
comma
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
l_string|&quot;&bslash;n&t;addl %1, %0&quot;
l_string|&quot;&bslash;n&t;adcl %2, %0&quot;
l_string|&quot;&bslash;n&t;adcl %3, %0&quot;
l_string|&quot;&bslash;n&t;adcl $0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;g&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;g&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;g&quot;
(paren
(paren
id|ntohs
c_func
(paren
id|len
)paren
op_lshift
l_int|16
)paren
op_plus
id|proto
op_star
l_int|256
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
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
DECL|function|csum_tcpudp_magic
r_static
r_inline
r_int
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
r_int
id|sum
)paren
suffix:semicolon
multiline_comment|/*&n; * this is a new version of the above that records errors it finds in *errp,&n; * but continues and zeros the rest of the buffer.&n; */
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
r_int
id|sum
comma
r_int
op_star
id|errp
)paren
suffix:semicolon
r_int
r_int
id|csum_partial_copy_nocheck
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
)paren
suffix:semicolon
multiline_comment|/*&n; * this routine is used for miscellaneous IP-like checksums, mainly&n; * in icmp.c&n; */
r_extern
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
suffix:semicolon
DECL|macro|_HAVE_ARCH_IPV6_CSUM
mdefine_line|#define _HAVE_ARCH_IPV6_CSUM
DECL|function|csum_ipv6_magic
r_static
id|__inline__
r_int
r_int
r_int
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
id|__asm__
c_func
(paren
l_string|&quot;&bslash;n&t;&t;addl 0(%1), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 4(%1), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 8(%1), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 12(%1), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 0(%2), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 4(%2), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 8(%2), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl 12(%2), %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl %3, %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl %4, %0&quot;
l_string|&quot;&bslash;n&t;&t;adcl $0, %0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|htonl
c_func
(paren
id|len
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|htonl
c_func
(paren
id|proto
)paren
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
macro_line|#endif
eof
