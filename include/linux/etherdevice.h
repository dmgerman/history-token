multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  NET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Ethernet handlers.&n; *&n; * Version:&t;@(#)eth.h&t;1.0.4&t;05/13/93&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;Relocated to include/linux where it belongs by Alan Cox &n; *&t;&t;&t;&t;&t;&t;&t;&lt;gw4pts@gw4pts.ampr.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;WARNING: This move may well be temporary. This file will get merged with others RSN.&n; *&n; */
macro_line|#ifndef _LINUX_ETHERDEVICE_H
DECL|macro|_LINUX_ETHERDEVICE_H
mdefine_line|#define _LINUX_ETHERDEVICE_H
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|eth_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_void
op_star
id|daddr
comma
r_void
op_star
id|saddr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|eth_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
r_int
id|eth_type_trans
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|eth_header_cache_update
c_func
(paren
r_struct
id|hh_cache
op_star
id|hh
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_char
op_star
id|haddr
)paren
suffix:semicolon
r_extern
r_int
id|eth_header_cache
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|hh_cache
op_star
id|hh
)paren
suffix:semicolon
r_extern
r_int
id|eth_header_parse
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|haddr
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|__init_etherdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_priv
)paren
suffix:semicolon
DECL|function|init_etherdev
r_static
r_inline
r_struct
id|net_device
op_star
id|init_etherdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_priv
)paren
(brace
r_return
id|__init_etherdev
c_func
(paren
id|dev
comma
id|sizeof_priv
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|net_device
op_star
id|alloc_etherdev
c_func
(paren
r_int
id|sizeof_priv
)paren
suffix:semicolon
DECL|function|eth_copy_and_sum
r_static
r_inline
r_void
id|eth_copy_and_sum
(paren
r_struct
id|sk_buff
op_star
id|dest
comma
r_int
r_char
op_star
id|src
comma
r_int
id|len
comma
r_int
id|base
)paren
(brace
id|memcpy
(paren
id|dest-&gt;data
comma
id|src
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * is_valid_ether_addr - Determine if the given Ethernet address is valid&n; * @addr: Pointer to a six-byte array containing the Ethernet address&n; *&n; * Check that the Ethernet address (MAC) is not 00:00:00:00:00:00, is not&n; * a multicast address, and is not FF:FF:FF:FF:FF:FF.  The multicast&n; * and FF:FF:... tests are combined into the single test &quot;!(addr[0]&amp;1)&quot;.&n; *&n; * Return true if the address is valid.&n; */
DECL|function|is_valid_ether_addr
r_static
r_inline
r_int
id|is_valid_ether_addr
c_func
(paren
id|u8
op_star
id|addr
)paren
(brace
r_const
r_char
id|zaddr
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
r_return
op_logical_neg
(paren
id|addr
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
op_logical_and
id|memcmp
c_func
(paren
id|addr
comma
id|zaddr
comma
l_int|6
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif&t;/* _LINUX_ETHERDEVICE_H */
eof
