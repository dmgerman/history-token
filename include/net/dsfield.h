multiline_comment|/* include/net/dsfield.h - Manipulation of the Differentiated Services field */
multiline_comment|/* Written 1998-2000 by Werner Almesberger, EPFL ICA */
macro_line|#ifndef __NET_DSFIELD_H
DECL|macro|__NET_DSFIELD_H
mdefine_line|#define __NET_DSFIELD_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|function|ipv4_get_dsfield
r_static
r_inline
id|__u8
id|ipv4_get_dsfield
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
r_return
id|iph-&gt;tos
suffix:semicolon
)brace
DECL|function|ipv6_get_dsfield
r_static
r_inline
id|__u8
id|ipv6_get_dsfield
c_func
(paren
r_struct
id|ipv6hdr
op_star
id|ipv6h
)paren
(brace
r_return
id|ntohs
c_func
(paren
op_star
(paren
id|__u16
op_star
)paren
id|ipv6h
)paren
op_rshift
l_int|4
suffix:semicolon
)brace
DECL|function|ipv4_change_dsfield
r_static
r_inline
r_void
id|ipv4_change_dsfield
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
id|__u8
id|mask
comma
id|__u8
id|value
)paren
(brace
id|__u32
id|check
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;check
)paren
suffix:semicolon
id|__u8
id|dsfield
suffix:semicolon
id|dsfield
op_assign
(paren
id|iph-&gt;tos
op_amp
id|mask
)paren
op_or
id|value
suffix:semicolon
id|check
op_add_assign
id|iph-&gt;tos
suffix:semicolon
r_if
c_cond
(paren
(paren
id|check
op_plus
l_int|1
)paren
op_rshift
l_int|16
)paren
id|check
op_assign
(paren
id|check
op_plus
l_int|1
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|check
op_sub_assign
id|dsfield
suffix:semicolon
id|check
op_add_assign
id|check
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* adjust carry */
id|iph-&gt;check
op_assign
id|htons
c_func
(paren
id|check
)paren
suffix:semicolon
id|iph-&gt;tos
op_assign
id|dsfield
suffix:semicolon
)brace
DECL|function|ipv6_change_dsfield
r_static
r_inline
r_void
id|ipv6_change_dsfield
c_func
(paren
r_struct
id|ipv6hdr
op_star
id|ipv6h
comma
id|__u8
id|mask
comma
id|__u8
id|value
)paren
(brace
id|__u16
id|tmp
suffix:semicolon
id|tmp
op_assign
id|ntohs
c_func
(paren
op_star
(paren
id|__u16
op_star
)paren
id|ipv6h
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_amp
(paren
(paren
id|mask
op_lshift
l_int|4
)paren
op_or
l_int|0xf00f
)paren
)paren
op_or
(paren
id|value
op_lshift
l_int|4
)paren
suffix:semicolon
op_star
(paren
id|__u16
op_star
)paren
id|ipv6h
op_assign
id|htons
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
