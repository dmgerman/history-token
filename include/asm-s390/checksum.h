macro_line|#ifndef _S390_CHECKSUM_H
DECL|macro|_S390_CHECKSUM_H
mdefine_line|#define _S390_CHECKSUM_H
multiline_comment|/*&n; *  include/asm-s390/checksum.h&n; *    S390 fast network checksum routines&n; *    see also arch/S390/lib/checksum.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ulrich Hild        (first version)&n; *               Martin Schwidefsky (heavily optimized CKSM version)&n; *               D.J. Barrow        (third attempt) &n; */
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
multiline_comment|/*&n; * csum_partial as an inline function&n; */
r_extern
r_inline
r_int
r_int
DECL|function|csum_partial_inline
id|csum_partial_inline
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
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;    lr   2,%1&bslash;n&quot;
multiline_comment|/* address in gpr 2 */
l_string|&quot;    lr   3,%2&bslash;n&quot;
multiline_comment|/* length in gpr 3 */
l_string|&quot;0:  cksm %0,2&bslash;n&quot;
multiline_comment|/* do checksum on longs */
l_string|&quot;    jo   0b&bslash;n&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|buff
)paren
comma
l_string|&quot;d&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * the same as csum_partial, but copies from src while it&n; * checksums&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_extern
r_inline
r_int
r_int
DECL|function|csum_partial_copy
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
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_return
id|csum_partial_inline
c_func
(paren
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * the same as csum_partial_copy, but copies from user space.&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_extern
r_inline
r_int
r_int
DECL|function|csum_partial_copy_from_user
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
(brace
r_if
c_cond
(paren
id|copy_from_user
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
id|errp
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
id|dst
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_return
id|csum_partial
c_func
(paren
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
r_extern
r_inline
r_int
r_int
DECL|function|csum_partial_copy_nocheck
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
r_int
id|sum
)paren
(brace
id|memcpy
c_func
(paren
id|dst
comma
id|src
comma
id|len
)paren
suffix:semicolon
r_return
id|csum_partial_inline
c_func
(paren
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *      Fold a partial checksum without adding pseudo headers&n; */
macro_line|#if 1
r_int
r_int
id|csum_fold
c_func
(paren
r_int
r_int
id|sum
)paren
suffix:semicolon
macro_line|#else
r_extern
r_inline
r_int
r_int
DECL|function|csum_fold
id|csum_fold
c_func
(paren
r_int
r_int
id|sum
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;    sr   3,3&bslash;n&quot;
multiline_comment|/* %0 = H*65536 + L */
l_string|&quot;    lr   2,%0&bslash;n&quot;
multiline_comment|/* %0 = H L, R2/R3 = H L / 0 0 */
l_string|&quot;    srdl 2,16&bslash;n&quot;
multiline_comment|/* %0 = H L, R2/R3 = 0 H / L 0 */
l_string|&quot;    alr  2,3&bslash;n&quot;
multiline_comment|/* %0 = H L, R2/R3 = L H / L 0 */
l_string|&quot;    alr  %0,2&bslash;n&quot;
multiline_comment|/* %0 = H+L+C L+H */
l_string|&quot;    srl  %0,16&bslash;n&quot;
multiline_comment|/* %0 = H+L+C */
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|sum
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
op_complement
id|sum
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; */
r_extern
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
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;    sr   %0,%0&bslash;n&quot;
multiline_comment|/* set sum to zero */
l_string|&quot;    lr   2,%1&bslash;n&quot;
multiline_comment|/* address in gpr 2 */
l_string|&quot;    lr   3,%2&bslash;n&quot;
multiline_comment|/* length in gpr 3 */
l_string|&quot;0:  cksm %0,2&bslash;n&quot;
multiline_comment|/* do checksum on longs */
l_string|&quot;    jo   0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|iph
)paren
comma
l_string|&quot;d&quot;
(paren
id|ihl
op_star
l_int|4
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
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
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 32-bit checksum&n; */
r_extern
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
id|__volatile__
(paren
l_string|&quot;    sll   %3,16&bslash;n&quot;
l_string|&quot;    or    %3,%4&bslash;n&quot;
multiline_comment|/* newproto=proto&lt;&lt;16 in hiword, len in lowword */
l_string|&quot;    alr   %1,%2&bslash;n&quot;
multiline_comment|/* saddr+=daddr */
l_string|&quot;    brc   12,0f&bslash;n&quot;
l_string|&quot;    ahi   %1,1&bslash;n&quot;
multiline_comment|/* add carry */
l_string|&quot;0:  alr   %1,%3&bslash;n&quot;
multiline_comment|/* add saddr+=newproto */
l_string|&quot;    brc   12,1f&bslash;n&quot;
l_string|&quot;    ahi   %1,1&bslash;n&quot;
multiline_comment|/* add carry again */
l_string|&quot;1:  alr   %0,%1&bslash;n&quot;
multiline_comment|/* sum+=saddr */
l_string|&quot;    brc   12,2f&bslash;n&quot;
l_string|&quot;    ahi   %0,1&bslash;n&quot;
multiline_comment|/* add carry again */
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;d&quot;
(paren
id|daddr
)paren
comma
l_string|&quot;d&quot;
(paren
id|proto
)paren
comma
l_string|&quot;d&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
r_extern
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
macro_line|#endif /* _S390_CHECKSUM_H */
eof
