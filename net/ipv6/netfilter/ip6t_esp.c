multiline_comment|/* Kernel module to match ESP parameters. */
multiline_comment|/* (C) 2001-2002 Andras Kis-Szabo &lt;kisza@sch.bme.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv6/ip6t_esp.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IPv6 ESP match&quot;
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
l_string|&quot;esp spi_match:%c 0x%x &lt;= 0x%x &lt;= 0x%x&quot;
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
r_int
r_int
id|protoff
comma
r_int
op_star
id|hotdrop
)paren
(brace
r_struct
id|ip_esp_hdr
id|_esp
comma
op_star
id|eh
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|ip6t_esp
op_star
id|espinfo
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
multiline_comment|/* Make sure this isn&squot;t an evil packet */
multiline_comment|/*DEBUGP(&quot;ipv6_esp entered &bslash;n&quot;);*/
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
id|ip6t_ext_hdr
c_func
(paren
id|nexthdr
)paren
)paren
(brace
r_struct
id|ipv6_opt_hdr
id|_hdr
comma
op_star
id|hp
suffix:semicolon
r_int
id|hdrlen
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ipv6_esp header iteration &bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Is there enough space for the next ext header? */
r_if
c_cond
(paren
id|len
OL
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
r_break
suffix:semicolon
multiline_comment|/* ESP -&gt; evaluate */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_ESP
)paren
(brace
id|temp
op_or_assign
id|MASK_ESP
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hp
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_hdr
)paren
comma
op_amp
id|_hdr
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|hp
op_eq
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Calculate the header length */
r_if
c_cond
(paren
id|nexthdr
op_eq
id|NEXTHDR_FRAGMENT
)paren
id|hdrlen
op_assign
l_int|8
suffix:semicolon
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
id|hp-&gt;hdrlen
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
id|hp
)paren
suffix:semicolon
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
l_string|&quot;ipv6_esp match: unknown nextheader %u&bslash;n&quot;
comma
id|nexthdr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|nexthdr
op_assign
id|hp-&gt;nexthdr
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
l_string|&quot;ipv6_esp: new pointer too large! &bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* ESP header not found */
r_if
c_cond
(paren
id|temp
op_ne
id|MASK_ESP
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
r_sizeof
(paren
r_struct
id|ip_esp_hdr
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
id|eh
op_assign
id|skb_header_pointer
c_func
(paren
id|skb
comma
id|ptr
comma
r_sizeof
(paren
id|_esp
)paren
comma
op_amp
id|_esp
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|eh
op_eq
l_int|NULL
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;IPv6 ESP SPI %u %08X&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|eh-&gt;spi
)paren
comma
id|ntohl
c_func
(paren
id|eh-&gt;spi
)paren
)paren
suffix:semicolon
r_return
(paren
id|eh
op_ne
l_int|NULL
)paren
op_logical_and
id|spi_match
c_func
(paren
id|espinfo-&gt;spis
(braket
l_int|0
)braket
comma
id|espinfo-&gt;spis
(braket
l_int|1
)braket
comma
id|ntohl
c_func
(paren
id|eh-&gt;spi
)paren
comma
op_logical_neg
op_logical_neg
(paren
id|espinfo-&gt;invflags
op_amp
id|IP6T_ESP_INV_SPI
)paren
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
id|ip6t_esp
op_star
id|espinfo
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
id|ip6t_esp
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_esp: matchsize %u != %u&bslash;n&quot;
comma
id|matchinfosize
comma
id|IP6T_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ip6t_esp
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
id|espinfo-&gt;invflags
op_amp
op_complement
id|IP6T_ESP_INV_MASK
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip6t_esp: unknown flags %X&bslash;n&quot;
comma
id|espinfo-&gt;invflags
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
DECL|variable|esp_match
r_static
r_struct
id|ip6t_match
id|esp_match
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;esp&quot;
comma
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
id|esp_match
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
id|esp_match
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
