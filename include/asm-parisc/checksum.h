macro_line|#ifndef _PARISC_CHECKSUM_H
DECL|macro|_PARISC_CHECKSUM_H
mdefine_line|#define _PARISC_CHECKSUM_H
macro_line|#include &lt;linux/in6.h&gt;
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
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * The same as csum_partial, but copies from src while it checksums.&n; *&n; * Here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_extern
r_int
r_int
id|csum_partial_copy_nocheck
c_func
(paren
r_const
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * this is a new version of the above that records errors it finds in *errp,&n; * but continues and zeros the rest of the buffer.&n; */
r_extern
r_int
r_int
id|csum_partial_copy_from_user
c_func
(paren
r_const
r_int
r_char
op_star
id|src
comma
r_int
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
multiline_comment|/*&n; *&t;Optimized for IP headers, which always checksum on 4 octet boundaries.&n; *&n; *&t;Written by Randolph Chung &lt;tausq@debian.org&gt;, and then mucked with by&n; *&t;LaMont Jones &lt;lamont@debian.org&gt;&n; */
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
(paren
l_string|&quot;&t;ldws,ma&t;&t;4(%1), %0&bslash;n&quot;
l_string|&quot;&t;addib,&lt;=&t;-4, %2, 2f&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;ldws&t;&t;4(%1), %%r20&bslash;n&quot;
l_string|&quot;&t;ldws&t;&t;8(%1), %%r21&bslash;n&quot;
l_string|&quot;&t;add&t;&t;%0, %%r20, %0&bslash;n&quot;
l_string|&quot;&t;ldws,ma&t;&t;12(%1), %%r19&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%0, %%r21, %0&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%0, %%r19, %0&bslash;n&quot;
l_string|&quot;1:&t;ldws,ma&t;&t;4(%1), %%r19&bslash;n&quot;
l_string|&quot;&t;addib,&lt;&t;&t;0, %2, 1b&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%0, %%r19, %0&bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;extru&t;&t;%0, 31, 16, %%r20&bslash;n&quot;
l_string|&quot;&t;extru&t;&t;%0, 15, 16, %%r21&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%%r20, %%r21, %0&bslash;n&quot;
l_string|&quot;&t;extru&t;&t;%0, 15, 16, %%r21&bslash;n&quot;
l_string|&quot;&t;add&t;&t;%0, %%r21, %0&bslash;n&quot;
l_string|&quot;&t;subi&t;&t;-1, %0, %0&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
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
suffix:colon
l_string|&quot;r19&quot;
comma
l_string|&quot;r20&quot;
comma
l_string|&quot;r21&quot;
)paren
suffix:semicolon
r_return
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
multiline_comment|/* add the swapped two 16-bit halves of sum,&n;&t;   a possible carry from adding the two 16-bit halves,&n;&t;   will carry from the lower half into the upper half,&n;&t;   giving us the correct sum in the upper half. */
id|sum
op_add_assign
(paren
id|sum
op_lshift
l_int|16
)paren
op_plus
(paren
id|sum
op_rshift
l_int|16
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
l_string|&quot;&t;add  %1, %0, %0&bslash;n&quot;
l_string|&quot;&t;addc %2, %0, %0&bslash;n&quot;
l_string|&quot;&t;addc %3, %0, %0&bslash;n&quot;
l_string|&quot;&t;addc %%r0, %0, %0&bslash;n&quot;
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
id|buf
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
id|buf
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
id|__u16
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
id|__volatile__
(paren
macro_line|#if BITS_PER_LONG &gt; 32
multiline_comment|/*&n;&t;** We can execute two loads and two adds per cycle on PA 8000.&n;&t;** But add insn&squot;s get serialized waiting for the carry bit.&n;&t;** Try to keep 4 registers with &quot;live&quot; values ahead of the ALU.&n;&t;*/
l_string|&quot;&t;ldd,ma&t;&t;8(%1), %%r19&bslash;n&quot;
multiline_comment|/* get 1st saddr word */
l_string|&quot;&t;ldd,ma&t;&t;8(%2), %%r20&bslash;n&quot;
multiline_comment|/* get 1st daddr word */
l_string|&quot;&t;add&t;&t;%8, %3, %3&bslash;n&quot;
multiline_comment|/* add 16-bit proto + len */
l_string|&quot;&t;add&t;&t;%%r19, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldd,ma&t;&t;8(%1), %%r21&bslash;n&quot;
multiline_comment|/* 2cd saddr */
l_string|&quot;&t;ldd,ma&t;&t;8(%2), %%r22&bslash;n&quot;
multiline_comment|/* 2cd daddr */
l_string|&quot;&t;add,dc&t;&t;%%r20, %0, %0&bslash;n&quot;
l_string|&quot;&t;add,dc&t;&t;%%r21, %0, %0&bslash;n&quot;
l_string|&quot;&t;add,dc&t;&t;%%r22, %0, %0&bslash;n&quot;
l_string|&quot;&t;add,dc&t;&t;%3, %0, %0&bslash;n&quot;
multiline_comment|/* fold in proto+len | carry bit */
l_string|&quot;&t;extrd,u&t;&t;%0, 31, 32, %%r19&bslash;n&quot;
multiline_comment|/* copy upper half down */
l_string|&quot;&t;depdi&t;&t;0, 31, 32, %0&bslash;n&quot;
multiline_comment|/* clear upper half */
l_string|&quot;&t;add&t;&t;%%r19, %0, %0&bslash;n&quot;
multiline_comment|/* fold into 32-bits */
l_string|&quot;&t;addc&t;&t;0, %0, %0&bslash;n&quot;
multiline_comment|/* add carry */
macro_line|#else
multiline_comment|/*&n;&t;** For PA 1.x, the insn order doesn&squot;t matter as much.&n;&t;** Insn stream is serialized on the carry bit here too.&n;&t;** result from the previous operation (eg r0 + x)&n;&t;*/
l_string|&quot;&t;ldw,ma&t;&t;4(%1), %%r19&bslash;n&quot;
multiline_comment|/* get 1st saddr word */
l_string|&quot;&t;ldw,ma&t;&t;4(%2), %%r20&bslash;n&quot;
multiline_comment|/* get 1st daddr word */
l_string|&quot;&t;add&t;&t;%8, %3, %3&bslash;n&quot;
multiline_comment|/* add 16-bit proto + len */
l_string|&quot;&t;add&t;&t;%%r19, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldw,ma&t;&t;4(%1), %%r21&bslash;n&quot;
multiline_comment|/* 2cd saddr */
l_string|&quot;&t;addc&t;&t;%%r20, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldw,ma&t;&t;4(%2), %%r22&bslash;n&quot;
multiline_comment|/* 2cd daddr */
l_string|&quot;&t;addc&t;&t;%%r21, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldw,ma&t;&t;4(%1), %%r19&bslash;n&quot;
multiline_comment|/* 3rd saddr */
l_string|&quot;&t;addc&t;&t;%%r22, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldw,ma&t;&t;4(%2), %%r20&bslash;n&quot;
multiline_comment|/* 3rd daddr */
l_string|&quot;&t;addc&t;&t;%%r19, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldw,ma&t;&t;4(%1), %%r21&bslash;n&quot;
multiline_comment|/* 4th saddr */
l_string|&quot;&t;addc&t;&t;%%r20, %0, %0&bslash;n&quot;
l_string|&quot;&t;ldw,ma&t;&t;4(%2), %%r22&bslash;n&quot;
multiline_comment|/* 4th daddr */
l_string|&quot;&t;addc&t;&t;%%r21, %0, %0&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%%r22, %0, %0&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%3, %0, %0&bslash;n&quot;
multiline_comment|/* fold in proto+len, catch carry */
macro_line|#endif
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;2&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;3&quot;
(paren
id|len
)paren
comma
l_string|&quot;r&quot;
(paren
id|proto
)paren
suffix:colon
l_string|&quot;r19&quot;
comma
l_string|&quot;r20&quot;
comma
l_string|&quot;r21&quot;
comma
l_string|&quot;r22&quot;
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
multiline_comment|/* &n; *&t;Copy and checksum to user&n; */
DECL|macro|HAVE_CSUM_COPY_USER
mdefine_line|#define HAVE_CSUM_COPY_USER
DECL|function|csum_and_copy_to_user
r_static
id|__inline__
r_int
r_int
id|csum_and_copy_to_user
(paren
r_const
r_int
r_char
op_star
id|src
comma
r_int
r_char
id|__user
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
id|err_ptr
)paren
(brace
multiline_comment|/* code stolen from include/asm-mips64 */
id|sum
op_assign
id|csum_partial
c_func
(paren
id|src
comma
id|len
comma
id|sum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
)paren
(brace
op_star
id|err_ptr
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|sum
suffix:semicolon
)brace
macro_line|#endif
eof
