multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;IP/TCP/UDP checksumming routines&n; *&n; * Authors:&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Tom May, &lt;ftom@netcom.com&gt;&n; *&t;&t;Andreas Schwab, &lt;schwab@issan.informatik.uni-dortmund.de&gt;&n; *&t;&t;Lots of code moved from tcp.c and ip.c; see those files&n; *&t;&t;for more names.&n; *&n; * 03/02/96&t;Jes Sorensen, Andreas Schwab, Roman Hodek:&n; *&t;&t;Fixed some nasty bugs, causing some horrible crashes.&n; *&t;&t;A: At some points, the sum (%0) was used as&n; *&t;&t;length-counter instead of the length counter&n; *&t;&t;(%1). Thanks to Roman Hodek for pointing this out.&n; *&t;&t;B: GCC seems to mess up if one uses too many&n; *&t;&t;data-registers to hold input values and one tries to&n; *&t;&t;specify d0 and d1 as scratch registers. Letting gcc choose these&n; *      registers itself solves the problem.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* Revised by Kenneth Albanowski for m68knommu. Basic problem: unaligned access kills, so most&n;   of the assembly has to go. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
DECL|function|from32to16
r_static
r_inline
r_int
r_int
id|from32to16
c_func
(paren
r_int
r_int
id|x
)paren
(brace
multiline_comment|/* add up 16-bit and 16-bit for 16+c bit */
id|x
op_assign
(paren
id|x
op_amp
l_int|0xffff
)paren
op_plus
(paren
id|x
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* add up carry.. */
id|x
op_assign
(paren
id|x
op_amp
l_int|0xffff
)paren
op_plus
(paren
id|x
op_rshift
l_int|16
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|function|do_csum
r_static
r_int
r_int
id|do_csum
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
)paren
(brace
r_int
id|odd
comma
id|count
suffix:semicolon
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|odd
op_assign
l_int|1
op_amp
(paren
r_int
r_int
)paren
id|buff
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
(brace
id|result
op_assign
op_star
id|buff
suffix:semicolon
id|len
op_decrement
suffix:semicolon
id|buff
op_increment
suffix:semicolon
)brace
id|count
op_assign
id|len
op_rshift
l_int|1
suffix:semicolon
multiline_comment|/* nr of 16-bit words.. */
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
l_int|2
op_amp
(paren
r_int
r_int
)paren
id|buff
)paren
(brace
id|result
op_add_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|buff
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
id|buff
op_add_assign
l_int|2
suffix:semicolon
)brace
id|count
op_rshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* nr of 32-bit words.. */
r_if
c_cond
(paren
id|count
)paren
(brace
r_int
r_int
id|carry
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_int
r_int
id|w
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|buff
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|buff
op_add_assign
l_int|4
suffix:semicolon
id|result
op_add_assign
id|carry
suffix:semicolon
id|result
op_add_assign
id|w
suffix:semicolon
id|carry
op_assign
(paren
id|w
OG
id|result
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|result
op_add_assign
id|carry
suffix:semicolon
id|result
op_assign
(paren
id|result
op_amp
l_int|0xffff
)paren
op_plus
(paren
id|result
op_rshift
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_amp
l_int|2
)paren
(brace
id|result
op_add_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|buff
suffix:semicolon
id|buff
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
op_amp
l_int|1
)paren
id|result
op_add_assign
(paren
op_star
id|buff
op_lshift
l_int|8
)paren
suffix:semicolon
id|result
op_assign
id|from32to16
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|odd
)paren
id|result
op_assign
(paren
(paren
id|result
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|result
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; */
DECL|function|ip_fast_csum
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
op_complement
id|do_csum
c_func
(paren
id|iph
comma
id|ihl
op_star
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * computes the checksum of a memory block at buff, length len,&n; * and adds in &quot;sum&quot; (32-bit)&n; *&n; * returns a 32-bit number suitable for feeding into itself&n; * or csum_tcpudp_magic&n; *&n; * this function must be called with even lengths, except&n; * for the last fragment, which may be odd&n; *&n; * it&squot;s best to have buff aligned on a 32-bit boundary&n; */
DECL|function|csum_partial
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
(brace
r_int
r_int
id|result
op_assign
id|do_csum
c_func
(paren
id|buff
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* add in old sum, and carry.. */
id|result
op_add_assign
id|sum
suffix:semicolon
r_if
c_cond
(paren
id|sum
OG
id|result
)paren
id|result
op_add_assign
l_int|1
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|csum_partial
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial
)paren
suffix:semicolon
multiline_comment|/*&n; * this routine is used for miscellaneous IP-like checksums, mainly&n; * in icmp.c&n; */
DECL|function|ip_compute_csum
r_int
r_int
id|ip_compute_csum
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
)paren
(brace
r_return
op_complement
id|do_csum
c_func
(paren
id|buff
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * copy from fs while checksumming, otherwise like csum_partial&n; */
r_int
r_int
DECL|function|csum_partial_copy_from_user
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
id|csum_err
)paren
(brace
r_if
c_cond
(paren
id|csum_err
)paren
op_star
id|csum_err
op_assign
l_int|0
suffix:semicolon
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
multiline_comment|/*&n; * copy from ds while checksumming, otherwise like csum_partial&n; */
r_int
r_int
DECL|function|csum_partial_copy
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
eof
