multiline_comment|/* Kernel module to match ROUTING parameters. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_rt.h&gt;
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv6 RT match&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andras Kis-Szabo &lt;kisza@sch.bme.hu&gt;&quot;
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|function|ipv6_ext_hdr
r_int
id|ipv6_ext_hdr
c_func
(paren
id|u8
id|nexthdr
)paren
(brace
r_return
(paren
(paren
id|nexthdr
op_eq
id|NEXTHDR_HOP
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_ROUTING
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_FRAGMENT
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_AUTH
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_ESP
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_NONE
)paren
op_logical_or
(paren
id|nexthdr
op_eq
id|NEXTHDR_DEST
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns 1 if the id is matched by the range, 0 otherwise */
r_static
r_inline
r_int
DECL|function|segsleft_match
id|segsleft_match
c_func
(paren
id|u_int32_t
id|min
comma
id|u_int32_t
id|max
comma
id|u_int32_t
id|id
comma
r_int
id|invert
)paren
(brace
r_int
id|r
op_assign
l_int|0
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;rt segsleft_match:%c 0x%x &lt;= 0x%x &lt;= 0x%x&quot;
comma
id|invert
ques
c_cond
l_char|&squot;!&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|min
comma
id|id
comma
id|max
)paren
suffix:semicolon
id|r
op_assign
(paren
id|id
op_ge
id|min
op_logical_and
id|id
op_le
id|max
)paren
op_xor
id|invert
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot; result %s&bslash;n&quot;
comma
id|r
ques
c_cond
l_string|&quot;PASS&quot;
suffix:colon
l_string|&quot;FAILED&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_int
DECL|function|match
id|match
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_const
r_void
op_star
id|matchinfo
comma
r_int
id|offset
comma
r_const
r_void
op_star
id|protohdr
comma
id|u_int16_t
id|datalen
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_struct
id|ipv6_rt_hdr
op_star
id|route
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|ip6t_rt
op_star
id|rtinfo
op_assign
id|matchinfo
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
id|u8
id|nexthdr
suffix:semicolon
r_int
r_int
id|ptr
suffix:semicolon
r_int
r_int
id|hdrlen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* type of the 1st exthdr */
id|nexthdr
op_assign
id|skb-&gt;nh.ipv6h-&gt;nexthdr
suffix:semicolon
multiline_comment|/* pointer to the 1st exthdr */
id|ptr
op_assign
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
suffix:semicolon
multiline_comment|/* available length */
id|len
op_assign
id|skb-&gt;len
op_minus
id|ptr
suffix:semicolon
id|temp
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ipv6_ext_hdr
c_func
(paren
id|nexthdr
)paren
)paren
(brace
r_struct
id|ipv6_opt_hdr
op_star
id|hdr
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ipv6_rt header iteration &bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Is there enough space for the next ext header? */
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|ipv6_opt_hdr
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No more exthdr -&gt; evaluate */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_NONE
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* ESP -&gt; evaluate */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_ESP
)paren
(brace
r_break
suffix:semicolon
)brace
id|hdr
op_assign
(paren
r_struct
id|ipv6_opt_hdr
op_star
)paren
id|skb-&gt;data
op_plus
id|ptr
suffix:semicolon
multiline_comment|/* Calculate the header length */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_FRAGMENT
)paren
(brace
id|hdrlen
op_assign
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_AUTH
)paren
id|hdrlen
op_assign
(paren
id|hdr-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
suffix:semicolon
r_else
id|hdrlen
op_assign
id|ipv6_optlen
c_func
(paren
id|hdr
)paren
suffix:semicolon
multiline_comment|/* ROUTING -&gt; evaluate */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_ROUTING
)paren
(brace
id|temp
op_or_assign
id|MASK_ROUTING
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* set the flag */
r_switch
c_cond
(paren
id|nexthdr
)paren
(brace
r_case
id|NEXTHDR_HOP
suffix:colon
r_case
id|NEXTHDR_ROUTING
suffix:colon
r_case
id|NEXTHDR_FRAGMENT
suffix:colon
r_case
id|NEXTHDR_AUTH
suffix:colon
r_case
id|NEXTHDR_DEST
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;ipv6_rt match: unknown nextheader %u&bslash;n&quot;
comma
id|nexthdr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|nexthdr
op_assign
id|hdr-&gt;nexthdr
suffix:semicolon
id|len
op_sub_assign
id|hdrlen
suffix:semicolon
id|ptr
op_add_assign
id|hdrlen
suffix:semicolon
r_if
c_cond
(paren
id|ptr
OG
id|skb-&gt;len
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipv6_rt: new pointer is too large! &bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* ROUTING header not found */
r_if
c_cond
(paren
id|temp
op_ne
id|MASK_ROUTING
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
(paren
r_int
)paren
r_sizeof
(paren
r_struct
id|ipv6_rt_hdr
)paren
)paren
(brace
op_star
id|hotdrop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
id|hdrlen
)paren
(brace
multiline_comment|/* Pcket smaller than its length field */
r_return
l_int|0
suffix:semicolon
)brace
id|route
op_assign
id|skb-&gt;data
op_plus
id|ptr
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IPv6 RT LEN %u %u &quot;
comma
id|hdrlen
comma
id|route-&gt;hdrlen
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;TYPE %04X &quot;
comma
id|route-&gt;type
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;SGS_LEFT %u %08X&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|route-&gt;segments_left
)paren
comma
id|ntohl
c_func
(paren
id|route-&gt;segments_left
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IPv6 RT segsleft %02X &quot;
comma
(paren
id|segsleft_match
c_func
(paren
id|rtinfo-&gt;segsleft
(braket
l_int|0
)braket
comma
id|rtinfo-&gt;segsleft
(braket
l_int|1
)braket
comma
id|ntohl
c_func
(paren
id|route-&gt;segments_left
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_SGS
)paren
)paren
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;type %02X %02X %02X &quot;
comma
id|rtinfo-&gt;rt_type
comma
id|route-&gt;type
comma
(paren
op_logical_neg
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_TYP
)paren
op_logical_or
(paren
(paren
id|rtinfo-&gt;rt_type
op_eq
id|route-&gt;type
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_TYP
)paren
)paren
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;len %02X %04X %02X &quot;
comma
id|rtinfo-&gt;hdrlen
comma
id|hdrlen
comma
(paren
op_logical_neg
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_LEN
)paren
op_logical_or
(paren
(paren
id|rtinfo-&gt;hdrlen
op_eq
id|hdrlen
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_LEN
)paren
)paren
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;res %02X %02X %02X &quot;
comma
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_RES
)paren
comma
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|bitmap
comma
op_logical_neg
(paren
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_RES
)paren
op_logical_and
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|bitmap
)paren
)paren
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|route
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|segsleft_match
c_func
(paren
id|rtinfo-&gt;segsleft
(braket
l_int|0
)braket
comma
id|rtinfo-&gt;segsleft
(braket
l_int|1
)braket
comma
id|ntohl
c_func
(paren
id|route-&gt;segments_left
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_SGS
)paren
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_LEN
)paren
op_logical_or
(paren
(paren
id|rtinfo-&gt;hdrlen
op_eq
id|hdrlen
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_LEN
)paren
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_TYP
)paren
op_logical_or
(paren
(paren
id|rtinfo-&gt;rt_type
op_eq
id|route-&gt;type
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_TYP
)paren
)paren
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_RES
)paren
op_logical_and
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|bitmap
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;#%d &quot;
comma
id|rtinfo-&gt;addrnr
)paren
suffix:semicolon
id|temp
op_assign
id|len
op_assign
id|ptr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_FST
)paren
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_FST_NSTRICT
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Not strict &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtinfo-&gt;addrnr
OG
(paren
r_int
r_int
)paren
(paren
(paren
id|hdrlen
op_minus
l_int|8
)paren
op_div
l_int|16
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;There isn&squot;t enough space&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;#%d &quot;
comma
id|rtinfo-&gt;addrnr
)paren
suffix:semicolon
id|ptr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|temp
op_assign
l_int|0
suffix:semicolon
id|temp
OL
(paren
r_int
r_int
)paren
(paren
(paren
id|hdrlen
op_minus
l_int|8
)paren
op_div
l_int|16
)paren
suffix:semicolon
id|temp
op_increment
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|u8
)paren
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|addr
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
op_eq
(paren
id|u8
)paren
(paren
id|rtinfo-&gt;addrs
(braket
id|ptr
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;%02X?%02X &quot;
comma
(paren
id|u8
)paren
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|addr
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
comma
(paren
id|u8
)paren
(paren
id|rtinfo-&gt;addrs
(braket
id|ptr
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
)paren
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|16
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_eq
l_int|16
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ptr=%d temp=%d;&bslash;n&quot;
comma
id|ptr
comma
id|temp
)paren
suffix:semicolon
id|ptr
op_increment
suffix:semicolon
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;%02X?%02X &quot;
comma
(paren
id|u8
)paren
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|addr
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
comma
(paren
id|u8
)paren
(paren
id|rtinfo-&gt;addrs
(braket
id|ptr
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;!ptr=%d temp=%d;&bslash;n&quot;
comma
id|ptr
comma
id|temp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptr
op_eq
id|rtinfo-&gt;addrnr
)paren
r_break
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;ptr=%d len=%d #%d&bslash;n&quot;
comma
id|ptr
comma
id|len
comma
id|rtinfo-&gt;addrnr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_eq
l_int|16
)paren
op_logical_and
(paren
id|ptr
op_eq
id|rtinfo-&gt;addrnr
)paren
)paren
r_return
id|ret
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Strict &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtinfo-&gt;addrnr
OG
(paren
r_int
r_int
)paren
(paren
(paren
id|hdrlen
op_minus
l_int|8
)paren
op_div
l_int|16
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;There isn&squot;t enough space&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;#%d &quot;
comma
id|rtinfo-&gt;addrnr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|temp
op_assign
l_int|0
suffix:semicolon
id|temp
OL
id|rtinfo-&gt;addrnr
suffix:semicolon
id|temp
op_increment
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|u8
)paren
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|addr
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
op_eq
(paren
id|u8
)paren
(paren
id|rtinfo-&gt;addrs
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;%02X?%02X &quot;
comma
(paren
id|u8
)paren
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|addr
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
comma
(paren
id|u8
)paren
(paren
id|rtinfo-&gt;addrs
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
)paren
suffix:semicolon
id|len
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|16
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_ne
l_int|16
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;%02X?%02X &quot;
comma
(paren
id|u8
)paren
(paren
(paren
(paren
r_struct
id|rt0_hdr
op_star
)paren
id|route
)paren
op_member_access_from_pointer
id|addr
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
comma
(paren
id|u8
)paren
(paren
id|rtinfo-&gt;addrs
(braket
id|temp
)braket
dot
id|s6_addr
(braket
id|len
)braket
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;!len=%d temp=%d;&bslash;n&quot;
comma
id|len
comma
id|temp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;temp=%d len=%d #%d&bslash;n&quot;
comma
id|temp
comma
id|len
comma
id|rtinfo-&gt;addrnr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_eq
l_int|16
)paren
op_logical_and
(paren
id|temp
op_eq
id|rtinfo-&gt;addrnr
)paren
op_logical_and
(paren
id|temp
op_eq
(paren
r_int
r_int
)paren
(paren
(paren
id|hdrlen
op_minus
l_int|8
)paren
op_div
l_int|16
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called when user tries to insert an entry of this type. */
r_static
r_int
DECL|function|checkentry
id|checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ip6t_ip6
op_star
id|ip
comma
r_void
op_star
id|matchinfo
comma
r_int
r_int
id|matchinfosize
comma
r_int
r_int
id|hook_mask
)paren
(brace
r_const
r_struct
id|ip6t_rt
op_star
id|rtinfo
op_assign
id|matchinfo
suffix:semicolon
r_if
c_cond
(paren
id|matchinfosize
op_ne
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_rt
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_rt: matchsize %u != %u&bslash;n&quot;
comma
id|matchinfosize
comma
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_rt
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rtinfo-&gt;invflags
op_amp
op_complement
id|IP6T_RT_INV_MASK
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_rt: unknown flags %X&bslash;n&quot;
comma
id|rtinfo-&gt;invflags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rtinfo-&gt;flags
op_amp
(paren
id|IP6T_RT_RES
op_or
id|IP6T_RT_FST_MASK
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|rtinfo-&gt;flags
op_amp
id|IP6T_RT_TYP
)paren
op_logical_or
(paren
id|rtinfo-&gt;rt_type
op_ne
l_int|0
)paren
op_logical_or
(paren
id|rtinfo-&gt;invflags
op_amp
id|IP6T_RT_INV_TYP
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;`--rt-type 0&squot; required before `--rt-0-*&squot;&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|rt_match
r_static
r_struct
id|ip6t_match
id|rt_match
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;rt&quot;
comma
op_amp
id|match
comma
op_amp
id|checkentry
comma
l_int|NULL
comma
id|THIS_MODULE
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_return
id|ip6t_register_match
c_func
(paren
op_amp
id|rt_match
)paren
suffix:semicolon
)brace
DECL|function|cleanup
r_static
r_void
id|__exit
id|cleanup
c_func
(paren
r_void
)paren
(brace
id|ip6t_unregister_match
c_func
(paren
op_amp
id|rt_match
)paren
suffix:semicolon
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|cleanup
id|module_exit
c_func
(paren
id|cleanup
)paren
suffix:semicolon
eof
