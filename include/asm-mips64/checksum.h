multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 1998, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) 2001 Thiemo Seufer.&n; */
macro_line|#ifndef _ASM_CHECKSUM_H
DECL|macro|_ASM_CHECKSUM_H
mdefine_line|#define _ASM_CHECKSUM_H
macro_line|#include &lt;asm/uaccess.h&gt;
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
multiline_comment|/*&n; * this is a new version of the above that records errors it finds in *errp,&n; * but continues and zeros the rest of the buffer.&n; */
DECL|macro|csum_partial_copy_nocheck
mdefine_line|#define csum_partial_copy_nocheck csum_partial_copy
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
multiline_comment|/*&n; * Copy and checksum to user&n; */
DECL|macro|HAVE_CSUM_COPY_USER
mdefine_line|#define HAVE_CSUM_COPY_USER
DECL|function|csum_and_copy_to_user
r_extern
r_inline
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
multiline_comment|/*&n; * the same as csum_partial, but copies from user space (but on MIPS&n; * we have just one address space, so this is identical to the above)&n; *&n; * this is obsolete and will go away.&n; */
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
r_int
id|sum
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Fold a partial checksum without adding pseudo headers&n; */
DECL|function|csum_fold
r_static
r_inline
r_int
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
l_string|&quot;.set&bslash;tnoat&bslash;t&bslash;t&bslash;t# csum_fold&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$1,%0,16&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0,$1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1,%0,$1&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t%0,%0,16&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0,$1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t%0,0xffff&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&quot;
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
l_string|&quot;$1&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
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
r_int
r_int
id|dummy
suffix:semicolon
multiline_comment|/*&n;&t; * This is for 32-bit processors ...  but works just fine for 64-bit&n;&t; * processors for now ...  XXX&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# ip_fast_csum&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%0, (%1)&bslash;n&bslash;t&quot;
l_string|&quot;subu&bslash;t%2, 4&bslash;n&bslash;t&quot;
l_string|&quot;dsll&bslash;t%2, 2&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%3, 4(%1)&bslash;n&bslash;t&quot;
l_string|&quot;daddu&bslash;t%2, %1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%3, 8(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%3, 12(%1)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&quot;
l_string|&quot;1:&bslash;tlw&bslash;t%3, 16(%1)&bslash;n&bslash;t&quot;
l_string|&quot;daddiu&bslash;t%1, 4&bslash;n&quot;
l_string|&quot;addu&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, %3&bslash;n&bslash;t&quot;
l_string|&quot;bne&bslash;t%2, %1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; addu&bslash;t%0, $1&bslash;n&quot;
l_string|&quot;2:&bslash;t.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|iph
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|ihl
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
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
l_string|&quot;$1&quot;
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
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
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
l_string|&quot;.set&bslash;tnoat&bslash;t&bslash;t&bslash;t# csum_tcpudp_nofold&bslash;n&bslash;t&quot;
l_string|&quot;daddu&bslash;t%0, %2&bslash;n&bslash;t&quot;
l_string|&quot;daddu&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;daddu&bslash;t%0, %4&bslash;n&bslash;t&quot;
l_string|&quot;dsll32&bslash;t$1, %0, 0&bslash;n&bslash;t&quot;
l_string|&quot;daddu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;dsrl32&bslash;t%0, %0, 0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|saddr
)paren
comma
macro_line|#ifdef __MIPSEL__
l_string|&quot;r&quot;
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
macro_line|#else
l_string|&quot;r&quot;
(paren
(paren
(paren
id|proto
)paren
op_lshift
l_int|16
)paren
op_plus
id|len
)paren
comma
macro_line|#endif
l_string|&quot;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;$1&quot;
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
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# csum_ipv6_magic&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %5&bslash;t&bslash;t&bslash;t# proto (long in network byte order)&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, %5&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %6&bslash;t&bslash;t&bslash;t# csum&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, %6&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 0(%2)&bslash;t&bslash;t&bslash;t# four words source address&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 4(%2)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 8(%2)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 12(%2)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 0(%3)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 4(%3)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 8(%3)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t%1, 12(%3)&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, $1&bslash;n&bslash;t&quot;
l_string|&quot;addu&bslash;t%0, %1&bslash;n&bslash;t&quot;
l_string|&quot;sltu&bslash;t$1, %0, $1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
(paren
id|proto
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
l_string|&quot;0&quot;
(paren
id|htonl
c_func
(paren
id|len
)paren
)paren
comma
l_string|&quot;1&quot;
(paren
id|htonl
c_func
(paren
id|proto
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;$1&quot;
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
macro_line|#endif /* _ASM_CHECKSUM_H */
eof
