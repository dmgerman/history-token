multiline_comment|/* TODO: csum_tcpudp_magic could be speeded up, and csum_fold as well */
macro_line|#ifndef _CRIS_CHECKSUM_H
DECL|macro|_CRIS_CHECKSUM_H
mdefine_line|#define _CRIS_CHECKSUM_H
macro_line|#include &lt;asm/arch/checksum.h&gt;
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
multiline_comment|/*&n; *&t;Fold a partial checksum into a word&n; */
DECL|function|csum_fold
r_extern
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
multiline_comment|/* the while loop is unnecessary really, it&squot;s always enough with two&n;&t;   iterations */
r_while
c_loop
(paren
id|sum
op_rshift
l_int|16
)paren
(brace
id|sum
op_assign
(paren
id|sum
op_amp
l_int|0xffff
)paren
op_plus
(paren
id|sum
op_rshift
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/* add in end-around carry */
r_return
op_complement
id|sum
suffix:semicolon
)brace
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
r_int
id|sum
comma
r_int
op_star
id|errptr
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; */
DECL|function|ip_fast_csum
r_extern
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
r_return
id|csum_fold
c_func
(paren
id|csum_partial
c_func
(paren
id|iph
comma
id|ihl
op_star
l_int|4
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * computes the checksum of the TCP/UDP pseudo-header&n; * returns a 16-bit checksum, already complemented&n; */
DECL|function|csum_tcpudp_magic
r_extern
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
r_extern
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
macro_line|#endif
eof
