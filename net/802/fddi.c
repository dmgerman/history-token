multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;FDDI-type device handling.&n; *&n; * Version:&t;@(#)fddi.c&t;1.0.0&t;08/12/96&n; *&n; * Authors:&t;Lawrence V. Stefani, &lt;stefani@lkg.dec.com&gt;&n; *&n; *&t;&t;fddi.c is based on previous eth.c and tr.c work by&n; *&t;&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;&t;Mark Evans, &lt;evansmp@uhura.aston.ac.uk&gt;&n; *&t;&t;&t;Florian La Roche, &lt;rzsfl@rz.uni-sb.de&gt;&n; *&t;&t;&t;Alan Cox, &lt;gw4pts@gw4pts.ampr.org&gt;&n; * &n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Changes&n; *&t;&t;Alan Cox&t;&t;:&t;New arp/rebuild header&n; *&t;&t;Maciej W. Rozycki&t;:&t;IPv6 support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
multiline_comment|/*&n; * Create the FDDI MAC header for an arbitrary protocol layer&n; *&n; * saddr=NULL&t;means use device source address&n; * daddr=NULL&t;means leave destination address (eg unresolved arp)&n; */
DECL|function|fddi_header
r_int
id|fddi_header
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
(brace
r_int
id|hl
op_assign
id|FDDI_K_SNAP_HLEN
suffix:semicolon
r_struct
id|fddihdr
op_star
id|fddi
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|ETH_P_IP
op_logical_and
id|type
op_ne
id|ETH_P_IPV6
op_logical_and
id|type
op_ne
id|ETH_P_ARP
)paren
(brace
id|hl
op_assign
id|FDDI_K_8022_HLEN
op_minus
l_int|3
suffix:semicolon
)brace
id|fddi
op_assign
(paren
r_struct
id|fddihdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|hl
)paren
suffix:semicolon
id|fddi-&gt;fc
op_assign
id|FDDI_FC_K_ASYNC_LLC_DEF
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|ETH_P_IP
op_logical_or
id|type
op_eq
id|ETH_P_IPV6
op_logical_or
id|type
op_eq
id|ETH_P_ARP
)paren
(brace
id|fddi-&gt;hdr.llc_snap.dsap
op_assign
id|FDDI_EXTENDED_SAP
suffix:semicolon
id|fddi-&gt;hdr.llc_snap.ssap
op_assign
id|FDDI_EXTENDED_SAP
suffix:semicolon
id|fddi-&gt;hdr.llc_snap.ctrl
op_assign
id|FDDI_UI_CMD
suffix:semicolon
id|fddi-&gt;hdr.llc_snap.oui
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
id|fddi-&gt;hdr.llc_snap.oui
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|fddi-&gt;hdr.llc_snap.oui
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
id|fddi-&gt;hdr.llc_snap.ethertype
op_assign
id|htons
c_func
(paren
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the source and destination hardware addresses */
r_if
c_cond
(paren
id|saddr
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|fddi-&gt;saddr
comma
id|saddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|fddi-&gt;saddr
comma
id|dev-&gt;dev_addr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|daddr
op_ne
l_int|NULL
)paren
(brace
id|memcpy
c_func
(paren
id|fddi-&gt;daddr
comma
id|daddr
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_return
id|hl
suffix:semicolon
)brace
r_return
op_minus
id|hl
suffix:semicolon
)brace
multiline_comment|/*&n; * Rebuild the FDDI MAC header. This is called after an ARP&n; * (or in future other address resolution) has completed on&n; * this sk_buff.  We now let ARP fill in the other fields.&n; */
DECL|function|fddi_rebuild_header
r_int
id|fddi_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|fddihdr
op_star
id|fddi
op_assign
(paren
r_struct
id|fddihdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
macro_line|#ifdef CONFIG_INET
r_if
c_cond
(paren
id|fddi-&gt;hdr.llc_snap.ethertype
op_eq
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
multiline_comment|/* Try to get ARP to resolve the header and fill destination address */
r_return
id|arp_find
c_func
(paren
id|fddi-&gt;daddr
comma
id|skb
)paren
suffix:semicolon
r_else
macro_line|#endif&t;
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Don&squot;t know how to resolve type %02X addresses.&bslash;n&quot;
comma
id|skb-&gt;dev-&gt;name
comma
id|htons
c_func
(paren
id|fddi-&gt;hdr.llc_snap.ethertype
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Determine the packet&squot;s protocol ID and fill in skb fields.&n; * This routine is called before an incoming packet is passed&n; * up.  It&squot;s used to fill in specific skb fields and to set&n; * the proper pointer to the start of packet data (skb-&gt;data).&n; */
DECL|function|fddi_type_trans
r_int
r_int
id|fddi_type_trans
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
(brace
r_struct
id|fddihdr
op_star
id|fddi
op_assign
(paren
r_struct
id|fddihdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/*&n;&t; * Set mac.raw field to point to FC byte, set data field to point&n;&t; * to start of packet data.  Assume 802.2 SNAP frames for now.&n;&t; */
id|skb-&gt;mac.raw
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* point to frame control (FC) */
r_if
c_cond
(paren
id|fddi-&gt;hdr.llc_8022_1.dsap
op_eq
l_int|0xe0
)paren
(brace
id|skb_pull
c_func
(paren
id|skb
comma
id|FDDI_K_8022_HLEN
op_minus
l_int|3
)paren
suffix:semicolon
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_pull
c_func
(paren
id|skb
comma
id|FDDI_K_SNAP_HLEN
)paren
suffix:semicolon
multiline_comment|/* adjust for 21 byte header */
id|type
op_assign
id|fddi-&gt;hdr.llc_snap.ethertype
suffix:semicolon
)brace
multiline_comment|/* Set packet type based on destination address and flag settings */
r_if
c_cond
(paren
op_star
id|fddi-&gt;daddr
op_amp
l_int|0x01
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|fddi-&gt;daddr
comma
id|dev-&gt;broadcast
comma
id|FDDI_K_ALEN
)paren
op_eq
l_int|0
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_BROADCAST
suffix:semicolon
r_else
id|skb-&gt;pkt_type
op_assign
id|PACKET_MULTICAST
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|fddi-&gt;daddr
comma
id|dev-&gt;dev_addr
comma
id|FDDI_K_ALEN
)paren
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
)brace
multiline_comment|/* Assume 802.2 SNAP frames, for now */
r_return
id|type
suffix:semicolon
)brace
DECL|variable|fddi_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|fddi_type_trans
)paren
suffix:semicolon
eof
