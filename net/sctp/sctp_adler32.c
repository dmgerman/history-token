multiline_comment|/* SCTP kernel reference Implementation&n; * Copyright (c) 1999-2000 Cisco, Inc.&n; * Copyright (c) 1999-2001 Motorola, Inc.&n; * &n; * This file is part of the SCTP kernel reference Implementation&n; * &n; * $Header: /cvsroot/lksctp/lksctp/sctp_cvs/net/sctp/sctp_adler32.c,v 1.5 2002/06/13 16:03:38 jgrimm Exp $&n; * &n; * This file has direct heritage from the SCTP user-level reference &n; * implementation by R. Stewart, et al.  These functions implement the&n; * Adler-32 algorithm as specified by RFC 2960. &n; * &n; * The SCTP reference implementation is free software; &n; * you can redistribute it and/or modify it under the terms of &n; * the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * The SCTP reference implementation is distributed in the hope that it &n; * will be useful, but WITHOUT ANY WARRANTY; without even the implied&n; *                 ************************&n; * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; * See the GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA.  &n; * &n; * Please send any bug reports or fixes you make to the&n; * email address(es):&n; *    lksctp developers &lt;lksctp-developers@lists.sourceforge.net&gt;&n; * &n; * Or submit a bug report through the following website:&n; *    http://www.sf.net/projects/lksctp&n; *&n; * Written or modified by: &n; *    Randall Stewart &lt;rstewar1@email.mot.com&gt;&n; *    Ken Morneau     &lt;kmorneau@cisco.com&gt;&n; *    Qiaobing Xie    &lt;qxie1@email.mot.com&gt;&n; * &n; * Any bugs reported given to us we will try to fix... any fixes shared will&n; * be incorporated into the next SCTP release.&n; */
DECL|variable|cvs_id
r_static
r_char
op_star
id|cvs_id
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
op_assign
l_string|&quot;$Id: sctp_adler32.c,v 1.5 2002/06/13 16:03:38 jgrimm Exp $&quot;
suffix:semicolon
multiline_comment|/* This is an entry point for external calls&n; * Define this function in the header file. This is&n; * direct from rfc1950, ...&n; *&n; * The following C code computes the Adler-32 checksum of a data buffer.&n; * It is written for clarity, not for speed.  The sample code is in the&n; * ANSI C programming language. Non C users may find it easier to read&n; * with these hints:&n; *&n; *    &amp;      Bitwise AND operator.&n; *    &gt;&gt;     Bitwise right shift operator. When applied to an&n; *           unsigned quantity, as here, right shift inserts zero bit(s)&n; *           at the left.&n; *    &lt;&lt;     Bitwise left shift operator. Left shift inserts zero&n; *           bit(s) at the right.&n; *    ++     &quot;n++&quot; increments the variable n.&n; *    %      modulo operator: a % b is the remainder of a divided by b.&n; *&n; * Well, the above is a bit of a lie, I have optimized this a small&n; * tad, but I have commented the original lines below&n; */
macro_line|#include &lt;linux/types.h&gt; 
macro_line|#include &lt;net/sctp/sctp.h&gt;
DECL|macro|BASE
mdefine_line|#define BASE 65521 /* largest prime smaller than 65536 */
multiline_comment|/* Performance work as shown this pig to be the&n; * worst CPU wise guy. I have done what I could think&n; * of on my flight to Austrialia but I am sure some&n; * clever assembly could speed this up, but of&n; * course this would require the dreaded #ifdef&squot;s for&n; * architecture. If you can speed this up more, pass&n; * it back and we will incorporate it :-)&n; */
DECL|function|update_adler32
r_int
r_int
id|update_adler32
c_func
(paren
r_int
r_int
id|adler
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
id|__u32
id|s1
op_assign
id|adler
op_amp
l_int|0xffff
suffix:semicolon
id|__u32
id|s2
op_assign
(paren
id|adler
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|len
suffix:semicolon
id|n
op_increment
comma
id|buf
op_increment
)paren
(brace
multiline_comment|/* s1 = (s1 + buf[n]) % BASE */
multiline_comment|/* first we add */
id|s1
op_assign
(paren
id|s1
op_plus
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* Now if we need to, we do a mod by&n;&t;&t; * subtracting. It seems a bit faster&n;&t;&t; * since I really will only ever do&n;&t;&t; * one subtract at the MOST, since buf[n]&n;&t;&t; * is a max of 255.&n;&t;&t; */
r_if
c_cond
(paren
id|s1
op_ge
id|BASE
)paren
(brace
id|s1
op_sub_assign
id|BASE
suffix:semicolon
)brace
multiline_comment|/* s2 = (s2 + s1) % BASE */
multiline_comment|/* first we add */
id|s2
op_assign
(paren
id|s2
op_plus
id|s1
)paren
suffix:semicolon
multiline_comment|/* again, it is more efficent (it seems) to&n;&t;&t; * subtract since the most s2 will ever be&n;&t;&t; * is (BASE-1 + BASE-1) in the worse case.&n;&t;&t; * This would then be (2 * BASE) - 2, which&n;&t;&t; * will still only do one subtract. On Intel&n;&t;&t; * this is much better to do this way and&n;&t;&t; * avoid the divide. Have not -pg&squot;d on &n;&t;&t; * sparc.&n;&t;&t; */
r_if
c_cond
(paren
id|s2
op_ge
id|BASE
)paren
(brace
multiline_comment|/*      s2 %= BASE;*/
id|s2
op_sub_assign
id|BASE
suffix:semicolon
)brace
)brace
multiline_comment|/* Return the adler32 of the bytes buf[0..len-1] */
r_return
(paren
id|s2
op_lshift
l_int|16
)paren
op_plus
id|s1
suffix:semicolon
)brace
DECL|function|count_crc
id|__u32
id|count_crc
c_func
(paren
id|__u8
op_star
id|ptr
comma
id|__u16
id|count
)paren
(brace
multiline_comment|/*&n;&t; * Update a running Adler-32 checksum with the bytes&n;&t; * buf[0..len-1] and return the updated checksum. The Adler-32&n;&t; * checksum should be initialized to 1.&n;&t; */
id|__u32
id|adler
op_assign
l_int|1L
suffix:semicolon
id|__u32
id|zero
op_assign
l_int|0L
suffix:semicolon
multiline_comment|/* Calculate the CRC up to the checksum field. */
id|adler
op_assign
id|update_adler32
c_func
(paren
id|adler
comma
id|ptr
comma
r_sizeof
(paren
r_struct
id|sctphdr
)paren
op_minus
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
multiline_comment|/* Skip over the checksum field. */
id|adler
op_assign
id|update_adler32
c_func
(paren
id|adler
comma
op_amp
id|zero
comma
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
id|ptr
op_add_assign
r_sizeof
(paren
r_struct
id|sctphdr
)paren
suffix:semicolon
id|count
op_sub_assign
r_sizeof
(paren
r_struct
id|sctphdr
)paren
suffix:semicolon
multiline_comment|/* Calculate the rest of the Adler-32. */
id|adler
op_assign
id|update_adler32
c_func
(paren
id|adler
comma
id|ptr
comma
id|count
)paren
suffix:semicolon
r_return
id|adler
suffix:semicolon
)brace
eof
