macro_line|#ifndef __ASM_SH_CHECKSUM_H
DECL|macro|__ASM_SH_CHECKSUM_H
mdefine_line|#define __ASM_SH_CHECKSUM_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Kaz Kojima &amp; Niibe Yutaka&n; */
macro_line|#include &lt;linux/config.h&gt;
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
multiline_comment|/*&n; * the same as csum_partial, but copies from src while it&n; * checksums, and handles user-space pointer exceptions correctly, when needed.&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
id|asmlinkage
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
id|sum
comma
r_int
op_star
id|src_err_ptr
comma
r_int
op_star
id|dst_err_ptr
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Note: when you get a NULL pointer exception here this means someone&n; *&t;passed in an incorrect kernel address to one of these functions. &n; *&t;&n; *&t;If you use these functions directly please don&squot;t forget the &n; *&t;verify_area().&n; */
r_static
id|__inline__
DECL|function|csum_partial_copy_nocheck
r_int
r_int
id|csum_partial_copy_nocheck
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
(brace
r_return
id|csum_partial_copy_generic
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
id|__inline__
DECL|function|csum_partial_copy_from_user
r_int
r_int
id|csum_partial_copy_from_user
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
id|err_ptr
)paren
(brace
r_return
id|csum_partial_copy_generic
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
id|err_ptr
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the old (and unsafe) way of doing checksums, a warning message will be&n; * printed if they are used and an exeption occurs.&n; *&n; * these functions should go away after some time.&n; */
DECL|macro|csum_partial_copy_fromuser
mdefine_line|#define csum_partial_copy_fromuser csum_partial_copy
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
multiline_comment|/*&n; *&t;Fold a partial checksum&n; */
DECL|function|csum_fold
r_static
id|__inline__
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
id|__dummy
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;swap.w %0, %1&bslash;n&bslash;t&quot;
l_string|&quot;extu.w&t;%0, %0&bslash;n&bslash;t&quot;
l_string|&quot;extu.w&t;%1, %1&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;swap.w&t;%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;not&t;%0, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; *      i386 version by Jorge Cwik &lt;jorge@laser.satlink.net&gt;, adapted&n; *      for linux by * Arnt Gulbrandsen.&n; */
DECL|function|ip_fast_csum
r_static
id|__inline__
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
id|__dummy0
comma
id|__dummy1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov.l&t;@%1+, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@%1+, %3&bslash;n&bslash;t&quot;
l_string|&quot;add&t;#-2, %2&bslash;n&bslash;t&quot;
l_string|&quot;clrt&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;addc&t;%3, %0&bslash;n&bslash;t&quot;
l_string|&quot;movt&t;%4&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@%1+, %3&bslash;n&bslash;t&quot;
l_string|&quot;dt&t;%2&bslash;n&bslash;t&quot;
l_string|&quot;bf/s&t;1b&bslash;n&bslash;t&quot;
l_string|&quot; cmp/eq #1, %4&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%3, %0&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%2, %0&quot;
multiline_comment|/* Here %2 is 0, add carry-bit */
multiline_comment|/* Since the input registers which are loaded with iph and ihl&n;&t;   are modified, we must also specify them as outputs, or gcc&n;&t;   will assume they contain their original values. */
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy0
)paren
comma
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy1
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
l_string|&quot;t&quot;
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
id|__inline__
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
macro_line|#ifdef __LITTLE_ENDIAN__
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
id|__asm__
c_func
(paren
l_string|&quot;clrt&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%2, %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%3, %1&bslash;n&bslash;t&quot;
l_string|&quot;movt&t;%0&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|len_proto
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
l_string|&quot;1&quot;
(paren
id|len_proto
)paren
comma
l_string|&quot;0&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
DECL|function|csum_tcpudp_magic
r_static
id|__inline__
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
id|__inline__
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
macro_line|#ifdef CONFIG_IPV6
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
r_int
r_int
id|__dummy
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;clrt&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(0,%2), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(4,%2), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(8,%2), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(12,%2), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(0,%3), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(4,%3), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(8,%3), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l&t;@(12,%3), %1&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%4, %0&bslash;n&bslash;t&quot;
l_string|&quot;addc&t;%5, %0&bslash;n&bslash;t&quot;
l_string|&quot;movt&t;%1&bslash;n&bslash;t&quot;
l_string|&quot;add&t;%1, %0&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
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
suffix:colon
l_string|&quot;t&quot;
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
id|err_ptr
)paren
(brace
r_if
c_cond
(paren
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|dst
comma
id|len
)paren
)paren
r_return
id|csum_partial_copy_generic
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
comma
l_int|NULL
comma
id|err_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
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
multiline_comment|/* invalid checksum */
)brace
macro_line|#endif /* __ASM_SH_CHECKSUM_H */
eof
