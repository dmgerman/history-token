macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_M32R_CHECKSUM_H
DECL|macro|_ASM_M32R_CHECKSUM_H
mdefine_line|#define _ASM_M32R_CHECKSUM_H
multiline_comment|/*&n; * include/asm-m32r/checksum.h&n; *&n; * IP/TCP/UDP checksum routines&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Some code taken from mips and parisc architecture.&n; *&n; *    Copyright (C) 2001, 2002  Hiroyuki Kondo, Hirokazu Takata&n; *    Copyright (C) 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;linux/in6.h&gt;
multiline_comment|/*&n; * computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
id|asmlinkage
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
)paren
suffix:semicolon
multiline_comment|/*&n; * This is a new version of the above that records errors it finds in *errp,&n; * but continues and zeros thre rest of the buffer.&n; */
r_extern
r_int
r_int
id|csum_partial_copy_from_user
c_func
(paren
r_const
r_int
r_char
id|__user
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
id|err_ptr
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
r_int
r_int
id|tmpreg
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;&t;sll3&t;%1, %0, #16 &bslash;n&quot;
l_string|&quot;&t;cmp&t;%0, %0 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %1 &bslash;n&quot;
l_string|&quot;&t;ldi&t;%1, #0 &bslash;n&quot;
l_string|&quot;&t;srli&t;%0, #16 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %1 &bslash;n&quot;
l_string|&quot;&t;xor3&t;%0, %0, #0x0000ffff &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;cbit&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a version of ip_compute_csum() optimized for IP headers,&n; * which always checksum on 4 octet boundaries.&n; */
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
comma
id|tmpreg0
comma
id|tmpreg1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;ld&t;%0, @%1+ &bslash;n&quot;
l_string|&quot;&t;addi&t;%2, #-4 &bslash;n&quot;
l_string|&quot;#&t;bgez&t;%2, 2f &bslash;n&quot;
l_string|&quot;&t;cmp&t;%0, %0 &bslash;n&quot;
l_string|&quot;&t;ld&t;%3, @%1+ &bslash;n&quot;
l_string|&quot;&t;ld&t;%4, @%1+ &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %3 &bslash;n&quot;
l_string|&quot;&t;ld&t;%3, @%1+ &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %4 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %3 &bslash;n&quot;
l_string|&quot;&t;.fillinsn&bslash;n&quot;
l_string|&quot;1: &bslash;n&quot;
l_string|&quot;&t;ld&t;%4, @%1+ &bslash;n&quot;
l_string|&quot;&t;addi&t;%2, #-1 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %4 &bslash;n&quot;
l_string|&quot;&t;bgtz&t;%2, 1b &bslash;n&quot;
l_string|&quot;&bslash;n&quot;
l_string|&quot;&t;ldi&t;%3, #0 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %3 &bslash;n&quot;
l_string|&quot;&t;.fillinsn&bslash;n&quot;
l_string|&quot;2: &bslash;n&quot;
multiline_comment|/* Since the input registers which are loaded with iph and ipl&n;&t;   are modified, we must also specify them as outputs, or gcc&n;&t;   will assume they contain their original values. */
suffix:colon
l_string|&quot;=&amp;r&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg1
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
l_string|&quot;cbit&quot;
comma
l_string|&quot;memory&quot;
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
macro_line|#if defined(__LITTLE_ENDIAN)
r_int
r_int
id|len_proto
op_assign
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
suffix:semicolon
macro_line|#else
r_int
r_int
id|len_proto
op_assign
(paren
id|proto
op_lshift
l_int|16
)paren
op_plus
id|len
suffix:semicolon
macro_line|#endif
r_int
r_int
id|tmpreg
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;&t;cmp&t;%0, %0 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %2 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %3 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %4 &bslash;n&quot;
l_string|&quot;&t;ldi&t;%1, #0 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %1 &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg
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
id|len_proto
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;cbit&quot;
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
DECL|function|csum_ipv6_magic
r_static
r_inline
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
r_int
r_int
id|tmpreg0
comma
id|tmpreg1
comma
id|tmpreg2
comma
id|tmpreg3
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;&t;ld&t;%1, @(%5) &bslash;n&quot;
l_string|&quot;&t;ld&t;%2, @(4,%5) &bslash;n&quot;
l_string|&quot;&t;ld&t;%3, @(8,%5) &bslash;n&quot;
l_string|&quot;&t;ld&t;%4, @(12,%5) &bslash;n&quot;
l_string|&quot;&t;add&t;%0, %1 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %2 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %3 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %4 &bslash;n&quot;
l_string|&quot;&t;ld&t;%1, @(%6) &bslash;n&quot;
l_string|&quot;&t;ld&t;%2, @(4,%6) &bslash;n&quot;
l_string|&quot;&t;ld&t;%3, @(8,%6) &bslash;n&quot;
l_string|&quot;&t;ld&t;%4, @(12,%6) &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %1 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %2 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %3 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %4 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %7 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %8 &bslash;n&quot;
l_string|&quot;&t;ldi&t;%1, #0 &bslash;n&quot;
l_string|&quot;&t;addx&t;%0, %1 &bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg2
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg3
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
(paren
id|__u32
)paren
(paren
id|len
)paren
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
suffix:colon
l_string|&quot;cbit&quot;
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
macro_line|#endif /* _ASM_M32R_CHECKSUM_H */
macro_line|#endif /* __KERNEL__ */
eof
