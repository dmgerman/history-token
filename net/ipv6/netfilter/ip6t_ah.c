multiline_comment|/* Kernel module to match AH parameters. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_ah.h&gt;
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
l_string|&quot;IPv6 AH match&quot;
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
DECL|struct|ahhdr
r_struct
id|ahhdr
(brace
DECL|member|nexthdr
id|__u8
id|nexthdr
suffix:semicolon
DECL|member|hdrlen
id|__u8
id|hdrlen
suffix:semicolon
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* Returns 1 if the spi is matched by the range, 0 otherwise */
r_static
r_inline
r_int
DECL|function|spi_match
id|spi_match
c_func
(paren
id|u_int32_t
id|min
comma
id|u_int32_t
id|max
comma
id|u_int32_t
id|spi
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
l_string|&quot;ah spi_match:%c 0x%x &lt;= 0x%x &lt;= 0x%x&quot;
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
id|spi
comma
id|max
)paren
suffix:semicolon
id|r
op_assign
(paren
id|spi
op_ge
id|min
op_logical_and
id|spi
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
l_string|&quot;PASS&bslash;n&quot;
suffix:colon
l_string|&quot;FAILED&bslash;n&quot;
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
id|ahhdr
op_star
id|ah
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|ip6t_ah
op_star
id|ahinfo
op_assign
id|matchinfo
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
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
multiline_comment|/*DEBUGP(&quot;IPv6 AH entered&bslash;n&quot;);*/
multiline_comment|/* if (opt-&gt;auth == 0) return 0;&n;       * It does not filled on output */
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
l_string|&quot;ipv6_ah header iteration &bslash;n&quot;
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
multiline_comment|/* AH -&gt; evaluate */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_AUTH
)paren
(brace
id|temp
op_or_assign
id|MASK_AH
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
l_string|&quot;ipv6_ah match: unknown nextheader %u&bslash;n&quot;
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
l_string|&quot;ipv6_ah: new pointer too large! &bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* AH header not found */
r_if
c_cond
(paren
id|temp
op_ne
id|MASK_AH
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
id|ahhdr
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
id|ah
op_assign
id|skb-&gt;data
op_plus
id|ptr
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IPv6 AH LEN %u %u &quot;
comma
id|hdrlen
comma
id|ah-&gt;hdrlen
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;RES %04X &quot;
comma
id|ah-&gt;reserved
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;SPI %u %08X&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IPv6 AH spi %02X &quot;
comma
(paren
id|spi_match
c_func
(paren
id|ahinfo-&gt;spis
(braket
l_int|0
)braket
comma
id|ahinfo-&gt;spis
(braket
l_int|1
)braket
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|ahinfo-&gt;invflags
op_amp
id|IP6T_AH_INV_SPI
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
id|ahinfo-&gt;hdrlen
comma
id|hdrlen
comma
(paren
op_logical_neg
id|ahinfo-&gt;hdrlen
op_logical_or
(paren
id|ahinfo-&gt;hdrlen
op_eq
id|hdrlen
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|ahinfo-&gt;invflags
op_amp
id|IP6T_AH_INV_LEN
)paren
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;res %02X %04X %02X&bslash;n&quot;
comma
id|ahinfo-&gt;hdrres
comma
id|ah-&gt;reserved
comma
op_logical_neg
(paren
id|ahinfo-&gt;hdrres
op_logical_and
id|ah-&gt;reserved
)paren
)paren
suffix:semicolon
r_return
(paren
id|ah
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|spi_match
c_func
(paren
id|ahinfo-&gt;spis
(braket
l_int|0
)braket
comma
id|ahinfo-&gt;spis
(braket
l_int|1
)braket
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|ahinfo-&gt;invflags
op_amp
id|IP6T_AH_INV_SPI
)paren
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|ahinfo-&gt;hdrlen
op_logical_or
(paren
id|ahinfo-&gt;hdrlen
op_eq
id|hdrlen
)paren
op_xor
op_logical_neg
op_logical_neg
(paren
id|ahinfo-&gt;invflags
op_amp
id|IP6T_AH_INV_LEN
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|ahinfo-&gt;hdrres
op_logical_and
id|ah-&gt;reserved
)paren
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
id|ip6t_ah
op_star
id|ahinfo
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
id|ip6t_ah
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_ah: matchsize %u != %u&bslash;n&quot;
comma
id|matchinfosize
comma
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_ah
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
id|ahinfo-&gt;invflags
op_amp
op_complement
id|IP6T_AH_INV_MASK
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_ah: unknown flags %X&bslash;n&quot;
comma
id|ahinfo-&gt;invflags
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
DECL|variable|ah_match
r_static
r_struct
id|ip6t_match
id|ah_match
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
)brace
comma
l_string|&quot;ah&quot;
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
id|ah_match
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
id|ah_match
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
