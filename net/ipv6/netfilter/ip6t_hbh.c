multiline_comment|/* Kernel module to match Hop-by-Hop and Destination parameters. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_opts.h&gt;
DECL|macro|LOW
mdefine_line|#define LOW(n)&t;&t;(n &amp; 0x00FF)
DECL|macro|HOPBYHOP
mdefine_line|#define HOPBYHOP&t;1
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#if HOPBYHOP
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv6 HbH match&quot;
)paren
suffix:semicolon
macro_line|#else
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv6 DST match&quot;
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/*&n; * (Type &amp; 0xC0) &gt;&gt; 6&n; * &t;0&t;-&gt; ignorable&n; * &t;1&t;-&gt; must drop the packet&n; * &t;2&t;-&gt; send ICMP PARM PROB regardless and drop packet&n; * &t;3&t;-&gt; Send ICMP if not a multicast address and drop packet&n; *  (Type &amp; 0x20) &gt;&gt; 5&n; *  &t;0&t;-&gt; invariant&n; *  &t;1&t;-&gt; can change the routing&n; *  (Type &amp; 0x1F) Type&n; *      0&t;-&gt; PAD0 (only 1 byte!)&n; *      1&t;-&gt; PAD1 LENGTH info (total length = length + 2)&n; *      C0 | 2&t;-&gt; JUMBO 4 x x x x ( xxxx &gt; 64k )&n; *      5&t;-&gt; RTALERT 2 x x&n; */
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
id|ipv6_opt_hdr
op_star
id|optsh
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|ip6t_opts
op_star
id|optinfo
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
id|u_int16_t
op_star
id|optdesc
op_assign
l_int|NULL
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
l_string|&quot;ipv6_opts header iteration &bslash;n&quot;
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
r_void
op_star
)paren
(paren
id|skb-&gt;data
)paren
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
multiline_comment|/* OPTS -&gt; evaluate */
macro_line|#if HOPBYHOP
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_HOP
)paren
(brace
id|temp
op_or_assign
id|MASK_HOPOPTS
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_DEST
)paren
(brace
id|temp
op_or_assign
id|MASK_DSTOPTS
suffix:semicolon
macro_line|#endif
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
l_string|&quot;ipv6_opts match: unknown nextheader %u&bslash;n&quot;
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
l_string|&quot;ipv6_opts: new pointer is too large! &bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* OPTIONS header not found */
macro_line|#if HOPBYHOP
r_if
c_cond
(paren
id|temp
op_ne
id|MASK_HOPOPTS
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|temp
op_ne
id|MASK_DSTOPTS
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Packet smaller than it&squot;s length field */
r_return
l_int|0
suffix:semicolon
)brace
id|optsh
op_assign
(paren
r_void
op_star
)paren
(paren
id|skb-&gt;data
)paren
op_plus
id|ptr
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IPv6 OPTS LEN %u %u &quot;
comma
id|hdrlen
comma
id|optsh-&gt;hdrlen
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;len %02X %04X %02X &quot;
comma
id|optinfo-&gt;hdrlen
comma
id|hdrlen
comma
(paren
op_logical_neg
(paren
id|optinfo-&gt;flags
op_amp
id|IP6T_OPTS_LEN
)paren
op_logical_or
(paren
(paren
id|optinfo-&gt;hdrlen
op_eq
id|hdrlen
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|optinfo-&gt;invflags
op_amp
id|IP6T_OPTS_INV_LEN
)paren
)paren
)paren
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|optsh
op_ne
l_int|NULL
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|optinfo-&gt;flags
op_amp
id|IP6T_OPTS_LEN
)paren
op_logical_or
(paren
(paren
id|optinfo-&gt;hdrlen
op_eq
id|hdrlen
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|optinfo-&gt;invflags
op_amp
id|IP6T_OPTS_INV_LEN
)paren
)paren
)paren
suffix:semicolon
id|temp
op_assign
id|len
op_assign
l_int|0
suffix:semicolon
id|ptr
op_add_assign
l_int|2
suffix:semicolon
id|hdrlen
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|optinfo-&gt;flags
op_amp
id|IP6T_OPTS_OPTS
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
id|optinfo-&gt;flags
op_amp
id|IP6T_OPTS_NSTRICT
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Not strict - not implemented&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Strict &quot;
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;#%d &quot;
comma
id|optinfo-&gt;optsnr
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
id|optinfo-&gt;optsnr
suffix:semicolon
id|temp
op_increment
)paren
(brace
id|optdesc
op_assign
(paren
r_void
op_star
)paren
(paren
id|skb-&gt;data
)paren
op_plus
id|ptr
suffix:semicolon
multiline_comment|/* Type check */
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
op_star
id|optdesc
op_ne
(paren
id|optinfo-&gt;opts
(braket
id|temp
)braket
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Tbad %02X %02X&bslash;n&quot;
comma
(paren
r_int
r_char
)paren
op_star
id|optdesc
comma
(paren
id|optinfo-&gt;opts
(braket
id|temp
)braket
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
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
l_string|&quot;Tok &quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Length check */
r_if
c_cond
(paren
(paren
(paren
id|optinfo-&gt;opts
(braket
id|temp
)braket
op_amp
l_int|0x00FF
)paren
op_ne
l_int|0xFF
)paren
op_logical_and
(paren
r_int
r_char
)paren
op_star
id|optdesc
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ntohs
c_func
(paren
(paren
id|u16
)paren
op_star
id|optdesc
)paren
op_ne
id|optinfo-&gt;opts
(braket
id|temp
)braket
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Lbad %02X %04X %04X&bslash;n&quot;
comma
(paren
r_int
r_char
)paren
op_star
id|optdesc
comma
id|ntohs
c_func
(paren
(paren
id|u16
)paren
op_star
id|optdesc
)paren
comma
id|optinfo-&gt;opts
(braket
id|temp
)braket
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
l_string|&quot;Lok &quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Step to the next */
r_if
c_cond
(paren
(paren
r_int
r_char
)paren
op_star
id|optdesc
op_eq
l_int|0
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;PAD0 &bslash;n&quot;
)paren
suffix:semicolon
id|ptr
op_increment
suffix:semicolon
id|hdrlen
op_decrement
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_add_assign
id|LOW
c_func
(paren
id|ntohs
c_func
(paren
op_star
id|optdesc
)paren
)paren
suffix:semicolon
id|hdrlen
op_sub_assign
id|LOW
c_func
(paren
id|ntohs
c_func
(paren
op_star
id|optdesc
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;len%04X &bslash;n&quot;
comma
id|LOW
c_func
(paren
id|ntohs
c_func
(paren
op_star
id|optdesc
)paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptr
OG
id|skb-&gt;len
op_logical_or
(paren
op_logical_neg
id|hdrlen
op_logical_and
(paren
id|temp
op_ne
id|optinfo-&gt;optsnr
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;new pointer is too large! &bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|temp
op_eq
id|optinfo-&gt;optsnr
)paren
r_return
id|ret
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
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
id|ip6t_opts
op_star
id|optsinfo
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
id|ip6t_opts
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_opts: matchsize %u != %u&bslash;n&quot;
comma
id|matchinfosize
comma
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_opts
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
id|optsinfo-&gt;invflags
op_amp
op_complement
id|IP6T_OPTS_INV_MASK
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_opts: unknown flags %X&bslash;n&quot;
comma
id|optsinfo-&gt;invflags
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
DECL|variable|opts_match
r_static
r_struct
id|ip6t_match
id|opts_match
op_assign
(brace
macro_line|#if HOPBYHOP
dot
id|name
op_assign
l_string|&quot;hbh&quot;
comma
macro_line|#else
dot
id|name
op_assign
l_string|&quot;dst&quot;
comma
macro_line|#endif
dot
id|match
op_assign
op_amp
id|match
comma
dot
id|checkentry
op_assign
op_amp
id|checkentry
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
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
id|opts_match
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
id|opts_match
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
