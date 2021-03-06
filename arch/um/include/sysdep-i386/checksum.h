multiline_comment|/* &n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_SYSDEP_CHECKSUM_H
DECL|macro|__UM_SYSDEP_CHECKSUM_H
mdefine_line|#define __UM_SYSDEP_CHECKSUM_H
macro_line|#include &quot;linux/in6.h&quot;
macro_line|#include &quot;linux/string.h&quot;
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
multiline_comment|/*&n; * the same as csum_partial, but copies from src while it&n; * checksums, and handles user-space pointer exceptions correctly, when needed.&n; *&n; * here even more important to align src and dst on a 32-bit (or even&n; * better 64-bit) boundary&n; */
r_int
r_int
id|csum_partial_copy_to
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
id|sum
comma
r_int
op_star
id|err_ptr
)paren
suffix:semicolon
r_int
r_int
id|csum_partial_copy_from
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
id|sum
comma
r_int
op_star
id|err_ptr
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Note: when you get a NULL pointer exception here this means someone&n; *&t;passed in an incorrect kernel address to one of these functions.&n; *&n; *&t;If you use these functions directly please don&squot;t forget the&n; *&t;access_ok().&n; */
r_static
id|__inline__
DECL|function|csum_partial_copy_nocheck
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
r_static
id|__inline__
DECL|function|csum_partial_copy_from_user
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
id|sum
comma
r_int
op_star
id|err_ptr
)paren
(brace
r_return
id|csum_partial_copy_from
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
id|err_ptr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the old (and unsafe) way of doing checksums, a warning message &n; * will be printed if they are used and an exception occurs.&n; *&n; * these functions should go away after some time.&n; */
DECL|macro|csum_partial_copy_fromuser
mdefine_line|#define csum_partial_copy_fromuser csum_partial_copy_from_user
r_int
r_int
id|csum_partial_copy
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
id|sum
)paren
suffix:semicolon
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
l_string|&quot;movl (%1), %0&t;;&bslash;n&quot;
l_string|&quot;subl $4, %2&t;;&bslash;n&quot;
l_string|&quot;jbe 2f&t;&t;;&bslash;n&quot;
l_string|&quot;addl 4(%1), %0&t;;&bslash;n&quot;
l_string|&quot;adcl 8(%1), %0&t;;&bslash;n&quot;
l_string|&quot;adcl 12(%1), %0&t;;&bslash;n&quot;
l_string|&quot;1:&t;    adcl 16(%1), %0&t;;&bslash;n&quot;
l_string|&quot;lea 4(%1), %1&t;;&bslash;n&quot;
l_string|&quot;decl %2&t;&t;;&bslash;n&quot;
l_string|&quot;jne 1b&t;&t;;&bslash;n&quot;
l_string|&quot;adcl $0, %0&t;;&bslash;n&quot;
l_string|&quot;movl %0, %2&t;;&bslash;n&quot;
l_string|&quot;shrl $16, %0&t;;&bslash;n&quot;
l_string|&quot;addw %w2, %w0&t;;&bslash;n&quot;
l_string|&quot;adcl $0, %0&t;;&bslash;n&quot;
l_string|&quot;notl %0&t;&t;;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;;&bslash;n&quot;
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
suffix:colon
l_string|&quot;memory&quot;
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
id|__asm__
c_func
(paren
l_string|&quot;addl %1, %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl $0xffff, %0&t;;&bslash;n&quot;
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
l_string|&quot;addl %1, %0&t;;&bslash;n&quot;
l_string|&quot;adcl %2, %0&t;;&bslash;n&quot;
l_string|&quot;adcl %3, %0&t;;&bslash;n&quot;
l_string|&quot;adcl $0, %0&t;;&bslash;n&quot;
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
l_string|&quot;addl 0(%1), %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl 4(%1), %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl 8(%1), %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl 12(%1), %0&t;;&bslash;n&quot;
l_string|&quot;adcl 0(%2), %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl 4(%2), %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl 8(%2), %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl 12(%2), %0&t;;&bslash;n&quot;
l_string|&quot;adcl %3, %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl %4, %0&t;&t;;&bslash;n&quot;
l_string|&quot;adcl $0, %0&t;&t;;&bslash;n&quot;
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
multiline_comment|/*&n; *&t;Copy and checksum to user&n; */
DECL|macro|HAVE_CSUM_COPY_USER
mdefine_line|#define HAVE_CSUM_COPY_USER
DECL|function|csum_and_copy_to_user
r_static
id|__inline__
r_int
r_int
id|csum_and_copy_to_user
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
id|csum_partial_copy_to
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
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
