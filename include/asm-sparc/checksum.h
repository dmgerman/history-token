multiline_comment|/* $Id: checksum.h,v 1.33 2002/02/01 22:01:05 davem Exp $ */
macro_line|#ifndef __SPARC_CHECKSUM_H
DECL|macro|__SPARC_CHECKSUM_H
mdefine_line|#define __SPARC_CHECKSUM_H
multiline_comment|/*  checksum.h:  IP/UDP/TCP checksum routines on the Sparc.&n; *&n; *  Copyright(C) 1995 Linus Torvalds&n; *  Copyright(C) 1995 Miguel de Icaza&n; *  Copyright(C) 1996 David S. Miller&n; *  Copyright(C) 1996 Eddie C. Dost&n; *  Copyright(C) 1997 Jakub Jelinek&n; *&n; * derived from:&n; *&t;Alpha checksum c-code&n; *      ix86 inline assembly&n; *      RFC1071 Computing the Internet Checksum&n; */
macro_line|#include &lt;linux/in6.h&gt;
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
multiline_comment|/* the same as csum_partial, but copies from fs:src while it&n; * checksums&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_extern
r_int
r_int
id|__csum_partial_copy_sparc_generic
(paren
r_const
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_static
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
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;o0&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_register
r_char
op_star
id|d
id|asm
c_func
(paren
l_string|&quot;o1&quot;
)paren
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|l
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
op_assign
id|len
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;call __csum_partial_copy_sparc_generic&bslash;n&bslash;t&quot;
l_string|&quot; mov %6, %%g7&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|d
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|l
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;1&quot;
(paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
id|l
)paren
comma
l_string|&quot;r&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
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
id|err
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_READ
comma
id|src
comma
id|len
)paren
)paren
(brace
op_star
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|memset
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
r_else
(brace
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;o0&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_register
r_char
op_star
id|d
id|asm
c_func
(paren
l_string|&quot;o1&quot;
)paren
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|l
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
op_assign
id|len
suffix:semicolon
r_register
r_int
r_int
id|s
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
op_assign
id|sum
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;
l_string|&quot;.align 4&bslash;n&bslash;t&quot;
l_string|&quot;.word 1f,2&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;call __csum_partial_copy_sparc_generic&bslash;n&bslash;t&quot;
l_string|&quot; st %8, [%%sp + 64]&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|d
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|l
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;1&quot;
(paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
id|l
)paren
comma
l_string|&quot;3&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_static
r_inline
r_int
r_int
DECL|function|csum_partial_copy_to_user
id|csum_partial_copy_to_user
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
id|__user
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
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_WRITE
comma
id|dst
comma
id|len
)paren
)paren
(brace
op_star
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
r_else
(brace
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;o0&quot;
)paren
op_assign
(paren
r_int
r_int
)paren
id|src
suffix:semicolon
r_register
r_char
op_star
id|d
id|asm
c_func
(paren
l_string|&quot;o1&quot;
)paren
op_assign
id|dst
suffix:semicolon
r_register
r_int
id|l
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
op_assign
id|len
suffix:semicolon
r_register
r_int
r_int
id|s
id|asm
c_func
(paren
l_string|&quot;g7&quot;
)paren
op_assign
id|sum
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;.section __ex_table,#alloc&bslash;n&bslash;t&quot;
l_string|&quot;.align 4&bslash;n&bslash;t&quot;
l_string|&quot;.word 1f,1&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;call __csum_partial_copy_sparc_generic&bslash;n&bslash;t&quot;
l_string|&quot; st %8, [%%sp + 64]&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|d
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|l
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|s
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;1&quot;
(paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
id|l
)paren
comma
l_string|&quot;3&quot;
(paren
id|s
)paren
comma
l_string|&quot;r&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;o2&quot;
comma
l_string|&quot;o3&quot;
comma
l_string|&quot;o4&quot;
comma
l_string|&quot;o5&quot;
comma
l_string|&quot;o7&quot;
comma
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g5&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
DECL|macro|HAVE_CSUM_COPY_USER
mdefine_line|#define HAVE_CSUM_COPY_USER
DECL|macro|csum_and_copy_to_user
mdefine_line|#define csum_and_copy_to_user csum_partial_copy_to_user
multiline_comment|/* ihl is always 5 or greater, almost always is 5, and iph is word aligned&n; * the majority of the time.&n; */
DECL|function|ip_fast_csum
r_static
r_inline
r_int
r_int
id|ip_fast_csum
c_func
(paren
r_const
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
l_string|&quot;sub&bslash;t%2, 4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x00], %0&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x04], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x08], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addcc&bslash;t%%g2, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%%g3, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x0c], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x10], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%%g2, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&quot;
l_string|&quot;1:&bslash;taddcc&bslash;t%%g3, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;add&bslash;t%1, 4, %1&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;subcc&bslash;t%%g4, 1, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;be,a&bslash;t2f&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t%0, 16, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;b&bslash;t1b&bslash;n&bslash;t&quot;
l_string|&quot;ld&bslash;t[%1 + 0x10], %%g3&bslash;n&quot;
l_string|&quot;2:&bslash;taddcc&bslash;t%0, %%g2, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t%%g2, 16, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
l_string|&quot;xnor&bslash;t%%g0, %0, %0&quot;
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
l_string|&quot;g4&quot;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;addcc&bslash;t%0, %1, %1&bslash;n&bslash;t&quot;
l_string|&quot;srl&bslash;t%1, 16, %1&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%1, %%g0, %1&bslash;n&bslash;t&quot;
l_string|&quot;xnor&bslash;t%%g0, %1, %0&quot;
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
id|sum
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
id|__volatile__
c_func
(paren
l_string|&quot;addcc&bslash;t%1, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%2, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&bslash;t%3, %0, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&bslash;t%0, %%g0, %0&bslash;n&bslash;t&quot;
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
id|__volatile__
(paren
l_string|&quot;addcc&t;%3, %4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%5, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%2 + 0x0c], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%2 + 0x08], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g2, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%2 + 0x04], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g3, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%2 + 0x00], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g2, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%1 + 0x0c], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g3, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%1 + 0x08], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g2, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%1 + 0x04], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g3, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;ld&t;[%1 + 0x00], %%g3&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g2, %%g4, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;addxcc&t;%%g3, %%g4, %0&bslash;n&bslash;t&quot;
l_string|&quot;addx&t;0, %0, %0&bslash;n&quot;
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
l_string|&quot;g4&quot;
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
macro_line|#endif /* !(__SPARC_CHECKSUM_H) */
eof
