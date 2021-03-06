macro_line|#ifndef _X86_64_CHECKSUM_H
DECL|macro|_X86_64_CHECKSUM_H
mdefine_line|#define _X86_64_CHECKSUM_H
multiline_comment|/* &n; * Checksums for x86-64 &n; * Copyright 2002 by Andi Kleen, SuSE Labs &n; * with some code from asm-i386/checksum.h&n; */
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/** &n; * csum_fold - Fold and invert a 32bit checksum.&n; * sum: 32bit unfolded sum&n; * &n; * Fold a 32bit running checksum to 16bit and invert it. This is usually&n; * the last step before putting a checksum into a packet.&n; * Make sure not to mix with 64bit checksums.&n; */
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
l_string|&quot;  addl %1,%0&bslash;n&quot;
l_string|&quot;  adcl $0xffff,%0&quot;
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
multiline_comment|/*&n; *&t;This is a version of ip_compute_csum() optimized for IP headers,&n; *&t;which always checksum on 4 octet boundaries.&n; *&n; *&t;By Jorge Cwik &lt;jorge@laser.satlink.net&gt;, adapted for linux by&n; *&t;Arnt Gulbrandsen.&n; */
multiline_comment|/**&n; * ip_fast_csum - Compute the IPv4 header checksum efficiently.&n; * iph: ipv4 header&n; * ihl: length of header / 4&n; */
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
id|asm
c_func
(paren
l_string|&quot;  movl (%1), %0&bslash;n&quot;
l_string|&quot;  subl $4, %2&bslash;n&quot;
l_string|&quot;  jbe 2f&bslash;n&quot;
l_string|&quot;  addl 4(%1), %0&bslash;n&quot;
l_string|&quot;  adcl 8(%1), %0&bslash;n&quot;
l_string|&quot;  adcl 12(%1), %0&bslash;n&quot;
l_string|&quot;1: adcl 16(%1), %0&bslash;n&quot;
l_string|&quot;  lea 4(%1), %1&bslash;n&quot;
l_string|&quot;  decl %2&bslash;n&quot;
l_string|&quot;  jne&t;1b&bslash;n&quot;
l_string|&quot;  adcl $0, %0&bslash;n&quot;
l_string|&quot;  movl %0, %2&bslash;n&quot;
l_string|&quot;  shrl $16, %0&bslash;n&quot;
l_string|&quot;  addw %w2, %w0&bslash;n&quot;
l_string|&quot;  adcl $0, %0&bslash;n&quot;
l_string|&quot;  notl %0&bslash;n&quot;
l_string|&quot;2:&quot;
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
multiline_comment|/** &n; * csum_tcpup_nofold - Compute an IPv4 pseudo header checksum.&n; * @saddr: source address&n; * @daddr: destination address&n; * @len: length of packet&n; * @proto: ip protocol of packet&n; * @sum: initial sum to be added in (32bit unfolded) &n; * &n; * Returns the pseudo header checksum the input data. Result is &n; * 32bit unfolded.&n; */
r_static
r_inline
r_int
r_int
DECL|function|csum_tcpudp_nofold
id|csum_tcpudp_nofold
c_func
(paren
r_int
id|saddr
comma
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
id|asm
c_func
(paren
l_string|&quot;  addl %1, %0&bslash;n&quot;
l_string|&quot;  adcl %2, %0&bslash;n&quot;
l_string|&quot;  adcl %3, %0&bslash;n&quot;
l_string|&quot;  adcl $0, %0&bslash;n&quot;
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
multiline_comment|/** &n; * csum_tcpup_magic - Compute an IPv4 pseudo header checksum.&n; * @saddr: source address&n; * @daddr: destination address&n; * @len: length of packet&n; * @proto: ip protocol of packet&n; * @sum: initial sum to be added in (32bit unfolded) &n; * &n; * Returns the 16bit pseudo header checksum the input data already&n; * complemented and ready to be filled in.&n; */
r_static
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
multiline_comment|/** &n; * csum_partial - Compute an internet checksum.&n; * @buff: buffer to be checksummed&n; * @len: length of buffer.&n; * @sum: initial sum to be added in (32bit unfolded)&n; *&n; * Returns the 32bit unfolded internet checksum of the buffer.&n; * Before filling it in it needs to be csum_fold()&squot;ed.&n; * buff should be aligned to a 64bit boundary if possible.&n; */
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
DECL|macro|_HAVE_ARCH_COPY_AND_CSUM_FROM_USER
mdefine_line|#define  _HAVE_ARCH_COPY_AND_CSUM_FROM_USER 1
DECL|macro|HAVE_CSUM_COPY_USER
mdefine_line|#define HAVE_CSUM_COPY_USER 1
multiline_comment|/* Do not call this directly. Use the wrappers below */
r_extern
r_int
r_int
id|csum_partial_copy_generic
c_func
(paren
r_const
r_int
r_char
op_star
id|src
comma
r_const
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
id|src_err_ptr
comma
r_int
op_star
id|dst_err_ptr
)paren
suffix:semicolon
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
id|isum
comma
r_int
op_star
id|errp
)paren
suffix:semicolon
r_extern
r_int
r_int
id|csum_partial_copy_to_user
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
id|__user
op_star
id|dst
comma
r_int
id|len
comma
r_int
r_int
id|isum
comma
r_int
op_star
id|errp
)paren
suffix:semicolon
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
multiline_comment|/* Old names. To be removed. */
DECL|macro|csum_and_copy_to_user
mdefine_line|#define csum_and_copy_to_user csum_partial_copy_to_user
DECL|macro|csum_and_copy_from_user
mdefine_line|#define csum_and_copy_from_user csum_partial_copy_from_user
multiline_comment|/** &n; * ip_compute_csum - Compute an 16bit IP checksum.&n; * @buff: buffer address.&n; * @len: length of buffer.&n; *&n; * Returns the 16bit folded/inverted checksum of the passed buffer.&n; * Ready to fill in.&n; */
r_extern
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
suffix:semicolon
multiline_comment|/**&n; * csum_ipv6_magic - Compute checksum of an IPv6 pseudo header.&n; * @saddr: source address&n; * @daddr: destination address&n; * @len: length of packet&n; * @proto: protocol of packet&n; * @sum: initial sum (32bit unfolded) to be added in&n; *&n; * Computes an IPv6 pseudo header checksum. This sum is added the checksum &n; * into UDP/TCP packets and contains some link layer information.&n; * Returns the unfolded 32bit checksum.&n; */
r_struct
id|in6_addr
suffix:semicolon
DECL|macro|_HAVE_ARCH_IPV6_CSUM
mdefine_line|#define _HAVE_ARCH_IPV6_CSUM 1
r_extern
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
suffix:semicolon
DECL|function|add32_with_carry
r_static
r_inline
r_int
id|add32_with_carry
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
id|asm
c_func
(paren
l_string|&quot;addl %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;adcl $0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|a
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|a
)paren
comma
l_string|&quot;r&quot;
(paren
id|b
)paren
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
macro_line|#endif
eof
