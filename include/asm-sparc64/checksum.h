multiline_comment|/* $Id: checksum.h,v 1.17 2001/04/24 01:09:12 davem Exp $ */
macro_line|#ifndef __SPARC64_CHECKSUM_H
DECL|macro|__SPARC64_CHECKSUM_H
mdefine_line|#define __SPARC64_CHECKSUM_H
multiline_comment|/*  checksum.h:  IP/UDP/TCP checksum routines on the V9.&n; *&n; *  Copyright(C) 1995 Linus Torvalds&n; *  Copyright(C) 1995 Miguel de Icaza&n; *  Copyright(C) 1996 David S. Miller&n; *  Copyright(C) 1996 Eddie C. Dost&n; *  Copyright(C) 1997 Jakub Jelinek&n; *&n; * derived from:&n; *&t;Alpha checksum c-code&n; *      ix86 inline assembly&n; *      RFC1071 Computing the Internet Checksum&n; */
macro_line|#include &lt;asm/uaccess.h&gt; 
multiline_comment|/* computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
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
multiline_comment|/* the same as csum_partial, but copies from user space while it&n; * checksums&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_extern
r_int
r_int
id|csum_partial_copy_sparc64
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
r_extern
id|__inline__
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
r_int
id|ret
suffix:semicolon
r_int
r_char
id|cur_ds
op_assign
id|current-&gt;thread.current_ds.seg
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;wr %%g0, %0, %%asi&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_P
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|csum_partial_copy_sparc64
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;wr %%g0, %0, %%asi&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|cur_ds
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
id|__inline__
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
id|err
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stx&t;%0, [%%sp + 0x7ff + 128]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|err
)paren
)paren
suffix:semicolon
r_return
id|csum_partial_copy_sparc64
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Copy and checksum to user&n; */
DECL|macro|HAVE_CSUM_COPY_USER
mdefine_line|#define HAVE_CSUM_COPY_USER
r_extern
r_int
r_int
id|csum_partial_copy_user_sparc64
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
r_extern
id|__inline__
r_int
r_int
DECL|function|csum_and_copy_to_user
id|csum_and_copy_to_user
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
id|err
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stx&t;%0, [%%sp + 0x7ff + 128]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|err
)paren
)paren
suffix:semicolon
r_return
id|csum_partial_copy_user_sparc64
c_func
(paren
id|src
comma
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
)brace
multiline_comment|/* ihl is always 5 or greater, almost always is 5, and iph is word aligned&n; * the majority of the time.&n; */
DECL|function|ip_fast_csum
r_extern
id|__inline__
r_int
r_int
id|ip_fast_csum
c_func
(paren
id|__const__
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
multiline_comment|/* Note: We must read %2 before we touch %0 for the first time,&n;&t; *       because GCC can legitimately use the same register for&n;&t; *       both operands.&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;sub&t;&t;%2, 4, %%g7&t;&t;! IEU0&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x00], %0&t;&t;! Load&t;Group&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x04], %%g2&t;! Load&t;Group&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x08], %%g3&t;! Load&t;Group&bslash;n&quot;
l_string|&quot;&t;addcc&t;&t;%%g2, %0, %0&t;&t;! IEU1&t;1 Load Bubble + Group&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x0c], %%g2&t;! Load&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g3, %0, %0&t;&t;! Sngle&t;Group no Bubble&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x10], %%g3&t;! Load&t;Group&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g2, %0, %0&t;&t;! Sngle&t;Group no Bubble&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%0, %%g0, %0&t;&t;! Sngle Group&bslash;n&quot;
l_string|&quot;1:&t;addcc&t;&t;%%g3, %0, %0&t;&t;! IEU1&t;Group no Bubble&bslash;n&quot;
l_string|&quot;&t;add&t;&t;%1, 4, %1&t;&t;! IEU0&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%0, %%g0, %0&t;&t;! Sngle Group no Bubble&bslash;n&quot;
l_string|&quot;&t;subcc&t;&t;%%g7, 1, %%g7&t;&t;! IEU1&t;Group&bslash;n&quot;
l_string|&quot;&t;be,a,pt&t;&t;%%icc, 2f&t;&t;! CTI&bslash;n&quot;
l_string|&quot;&t; sll&t;&t;%0, 16, %%g2&t;&t;! IEU0&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x10], %%g3&t;! Load&t;Group&bslash;n&quot;
l_string|&quot;&t;ba,pt&t;&t;%%xcc, 1b&t;&t;! CTI&bslash;n&quot;
l_string|&quot;&t; nop&t;&t;&t;&t;&t;! IEU0&bslash;n&quot;
l_string|&quot;2:&t;addcc&t;&t;%0, %%g2, %%g2&t;&t;! IEU1&t;Group&bslash;n&quot;
l_string|&quot;&t;srl&t;&t;%%g2, 16, %0&t;&t;! IEU0&t;Group regdep&t;XXX Scheisse!&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%0, %%g0, %0&t;&t;! Sngle&t;Group&bslash;n&quot;
l_string|&quot;&t;xnor&t;&t;%%g0, %0, %0&t;&t;! IEU0&t;Group&bslash;n&quot;
l_string|&quot;&t;srl&t;&t;%0, 0, %0&t;&t;! IEU0&t;Group&t;&t;XXX Scheisse!&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|iph
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ihl
)paren
comma
l_string|&quot;1&quot;
(paren
id|iph
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/* Fold a partial checksum without adding pseudo headers. */
DECL|function|csum_fold
r_extern
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
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;addcc&t;&t;%0, %1, %1&bslash;n&quot;
l_string|&quot;&t;srl&t;&t;%1, 16, %1&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%1, %%g0, %1&bslash;n&quot;
l_string|&quot;&t;xnor&t;&t;%%g0, %1, %0&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=r&quot;
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
op_lshift
l_int|16
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
id|sum
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
DECL|function|csum_tcpudp_nofold
r_extern
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;addcc&t;&t;%1, %0, %0&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%2, %0, %0&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%3, %0, %0&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;%0, %%g0, %0&bslash;n&quot;
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
suffix:colon
l_string|&quot;r&quot;
(paren
id|daddr
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
comma
l_string|&quot;1&quot;
(paren
id|saddr
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
id|__volatile__
(paren
l_string|&quot;&t;addcc&t;&t;%3, %4, %%g7&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%5, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%2 + 0x0c], %%g2&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%2 + 0x08], %%g3&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g2, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%2 + 0x04], %%g2&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g3, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%2 + 0x00], %%g3&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g2, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x0c], %%g2&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g3, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x08], %%g3&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g2, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x04], %%g2&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g3, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;lduw&t;&t;[%1 + 0x00], %%g3&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g2, %%g7, %%g7&bslash;n&quot;
l_string|&quot;&t;addccc&t;&t;%%g3, %%g7, %0&bslash;n&quot;
l_string|&quot;&t;addc&t;&t;0, %0, %0&bslash;n&quot;
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
l_string|&quot;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;cc&quot;
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
multiline_comment|/* this routine is used for miscellaneous IP-like checksums, mainly in icmp.c */
DECL|function|ip_compute_csum
r_extern
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
macro_line|#endif /* !(__SPARC64_CHECKSUM_H) */
eof
