multiline_comment|/*&n; * eth1394.h -- Ethernet driver for Linux IEEE-1394 Subsystem&n; *&n; * Copyright (C) 2000 Bonin Franck &lt;boninf@free.fr&gt;&n; *           (C) 2001 Ben Collins &lt;bcollins@debian.org&gt;&n; *&n; * Mainly based on work by Emanuel Pirker and Andreas E. Bombe&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef __ETH1394_H
DECL|macro|__ETH1394_H
mdefine_line|#define __ETH1394_H
macro_line|#include &quot;ieee1394.h&quot;
multiline_comment|/* Register for incoming packets. This is 4096 bytes, which supports up to&n; * S3200 (per Table 16-3 of IEEE 1394b-2002). */
DECL|macro|ETHER1394_REGION_ADDR_LEN
mdefine_line|#define ETHER1394_REGION_ADDR_LEN&t;4096
DECL|macro|ETHER1394_REGION_ADDR
mdefine_line|#define ETHER1394_REGION_ADDR&t;&t;0xfffff0200000ULL
DECL|macro|ETHER1394_REGION_ADDR_END
mdefine_line|#define ETHER1394_REGION_ADDR_END&t;(ETHER1394_REGION_ADDR + ETHER1394_REGION_ADDR_LEN)
multiline_comment|/* GASP identifier numbers for IPv4 over IEEE 1394 */
DECL|macro|ETHER1394_GASP_SPECIFIER_ID
mdefine_line|#define ETHER1394_GASP_SPECIFIER_ID&t;0x00005E
DECL|macro|ETHER1394_GASP_SPECIFIER_ID_HI
mdefine_line|#define ETHER1394_GASP_SPECIFIER_ID_HI&t;((ETHER1394_GASP_SPECIFIER_ID &gt;&gt; 8) &amp; 0xffff)
DECL|macro|ETHER1394_GASP_SPECIFIER_ID_LO
mdefine_line|#define ETHER1394_GASP_SPECIFIER_ID_LO&t;(ETHER1394_GASP_SPECIFIER_ID &amp; 0xff)
DECL|macro|ETHER1394_GASP_VERSION
mdefine_line|#define ETHER1394_GASP_VERSION&t;&t;1
DECL|macro|ETHER1394_GASP_OVERHEAD
mdefine_line|#define ETHER1394_GASP_OVERHEAD (2 * sizeof(quadlet_t))  /* GASP header overhead */
multiline_comment|/* Node set == 64 */
DECL|macro|NODE_SET
mdefine_line|#define NODE_SET&t;&t;&t;(ALL_NODES + 1)
DECL|enum|eth1394_bc_states
DECL|enumerator|ETHER1394_BC_CLOSED
DECL|enumerator|ETHER1394_BC_OPENED
r_enum
id|eth1394_bc_states
(brace
id|ETHER1394_BC_CLOSED
comma
id|ETHER1394_BC_OPENED
comma
DECL|enumerator|ETHER1394_BC_CHECK
id|ETHER1394_BC_CHECK
)brace
suffix:semicolon
DECL|struct|pdg_list
r_struct
id|pdg_list
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* partial datagram list per node */
DECL|member|sz
r_int
r_int
id|sz
suffix:semicolon
multiline_comment|/* partial datagram list size per node&t;*/
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* partial datagram lock&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* Private structure for our ethernet driver */
DECL|struct|eth1394_priv
r_struct
id|eth1394_priv
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* Device stats&t;&t;&t; */
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
multiline_comment|/* The card for this dev&t; */
DECL|member|maxpayload
id|u16
id|maxpayload
(braket
id|NODE_SET
)braket
suffix:semicolon
multiline_comment|/* Max payload per node&t;&t; */
DECL|member|sspd
r_int
r_char
id|sspd
(braket
id|NODE_SET
)braket
suffix:semicolon
multiline_comment|/* Max speed per node&t;&t; */
DECL|member|fifo
id|u64
id|fifo
(braket
id|ALL_NODES
)braket
suffix:semicolon
multiline_comment|/* FIFO offset per node&t;&t; */
DECL|member|eui
id|u64
id|eui
(braket
id|ALL_NODES
)braket
suffix:semicolon
multiline_comment|/* EUI-64 per node&t;&t; */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Private lock&t;&t;&t; */
DECL|member|broadcast_channel
r_int
id|broadcast_channel
suffix:semicolon
multiline_comment|/* Async stream Broadcast Channel */
DECL|member|bc_state
r_enum
id|eth1394_bc_states
id|bc_state
suffix:semicolon
multiline_comment|/* broadcast channel state&t; */
DECL|member|iso
r_struct
id|hpsb_iso
op_star
id|iso
suffix:semicolon
multiline_comment|/* Async stream recv handle&t; */
DECL|member|pdg
r_struct
id|pdg_list
id|pdg
(braket
id|ALL_NODES
)braket
suffix:semicolon
multiline_comment|/* partial RX datagram lists     */
DECL|member|dgl
r_int
id|dgl
(braket
id|NODE_SET
)braket
suffix:semicolon
multiline_comment|/* Outgoing datagram label per node */
)brace
suffix:semicolon
DECL|struct|host_info
r_struct
id|host_info
(brace
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Define a fake hardware header format for the networking core.  Note that&n; * header size cannot exceed 16 bytes as that is the size of the header cache.&n; * Also, we do not need the source address in the header so we omit it and&n; * keep the header to under 16 bytes */
DECL|macro|ETH1394_ALEN
mdefine_line|#define ETH1394_ALEN (8)
DECL|macro|ETH1394_HLEN
mdefine_line|#define ETH1394_HLEN (10)
DECL|struct|eth1394hdr
r_struct
id|eth1394hdr
(brace
DECL|member|h_dest
r_int
r_char
id|h_dest
(braket
id|ETH1394_ALEN
)braket
suffix:semicolon
multiline_comment|/* destination eth1394 addr&t;*/
DECL|member|h_proto
r_int
r_int
id|h_proto
suffix:semicolon
multiline_comment|/* packet type ID field&t;*/
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|enumerator|ETH1394_GASP
DECL|enumerator|ETH1394_WRREQ
DECL|typedef|eth1394_tx_type
r_typedef
r_enum
(brace
id|ETH1394_GASP
comma
id|ETH1394_WRREQ
)brace
id|eth1394_tx_type
suffix:semicolon
multiline_comment|/* IP1394 headers */
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* Unfragmented */
macro_line|#if defined __BIG_ENDIAN_BITFIELD
DECL|struct|eth1394_uf_hdr
r_struct
id|eth1394_uf_hdr
(brace
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|res
id|u16
id|res
suffix:colon
l_int|14
suffix:semicolon
DECL|member|ether_type
id|u16
id|ether_type
suffix:semicolon
multiline_comment|/* Ethernet packet type */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#elif defined __LITTLE_ENDIAN_BITFIELD
DECL|struct|eth1394_uf_hdr
r_struct
id|eth1394_uf_hdr
(brace
DECL|member|res
id|u16
id|res
suffix:colon
l_int|14
suffix:semicolon
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ether_type
id|u16
id|ether_type
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#error Unknown bit field type
macro_line|#endif
multiline_comment|/* First fragment */
macro_line|#if defined __BIG_ENDIAN_BITFIELD
DECL|struct|eth1394_ff_hdr
r_struct
id|eth1394_ff_hdr
(brace
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|res1
id|u16
id|res1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|dg_size
id|u16
id|dg_size
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Datagram size */
DECL|member|ether_type
id|u16
id|ether_type
suffix:semicolon
multiline_comment|/* Ethernet packet type */
DECL|member|dgl
id|u16
id|dgl
suffix:semicolon
multiline_comment|/* Datagram label */
DECL|member|res2
id|u16
id|res2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#elif defined __LITTLE_ENDIAN_BITFIELD
DECL|struct|eth1394_ff_hdr
r_struct
id|eth1394_ff_hdr
(brace
DECL|member|dg_size
id|u16
id|dg_size
suffix:colon
l_int|12
suffix:semicolon
DECL|member|res1
id|u16
id|res1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ether_type
id|u16
id|ether_type
suffix:semicolon
DECL|member|dgl
id|u16
id|dgl
suffix:semicolon
DECL|member|res2
id|u16
id|res2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#error Unknown bit field type
macro_line|#endif
multiline_comment|/* XXX: Subsequent fragments, including last */
macro_line|#if defined __BIG_ENDIAN_BITFIELD
DECL|struct|eth1394_sf_hdr
r_struct
id|eth1394_sf_hdr
(brace
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|res1
id|u16
id|res1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|dg_size
id|u16
id|dg_size
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Datagram size */
DECL|member|res2
id|u16
id|res2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fg_off
id|u16
id|fg_off
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Fragment offset */
DECL|member|dgl
id|u16
id|dgl
suffix:semicolon
multiline_comment|/* Datagram label */
DECL|member|res3
id|u16
id|res3
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#elif defined __LITTLE_ENDIAN_BITFIELD
DECL|struct|eth1394_sf_hdr
r_struct
id|eth1394_sf_hdr
(brace
DECL|member|dg_size
id|u16
id|dg_size
suffix:colon
l_int|12
suffix:semicolon
DECL|member|res1
id|u16
id|res1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|fg_off
id|u16
id|fg_off
suffix:colon
l_int|12
suffix:semicolon
DECL|member|res2
id|u16
id|res2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|dgl
id|u16
id|dgl
suffix:semicolon
DECL|member|res3
id|u16
id|res3
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#error Unknown bit field type
macro_line|#endif
macro_line|#if defined __BIG_ENDIAN_BITFIELD
DECL|struct|eth1394_common_hdr
r_struct
id|eth1394_common_hdr
(brace
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pad1
id|u16
id|pad1
suffix:colon
l_int|14
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#elif defined __LITTLE_ENDIAN_BITFIELD
DECL|struct|eth1394_common_hdr
r_struct
id|eth1394_common_hdr
(brace
DECL|member|pad1
id|u16
id|pad1
suffix:colon
l_int|14
suffix:semicolon
DECL|member|lf
id|u16
id|lf
suffix:colon
l_int|2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#error Unknown bit field type
macro_line|#endif
DECL|struct|eth1394_hdr_words
r_struct
id|eth1394_hdr_words
(brace
DECL|member|word1
id|u16
id|word1
suffix:semicolon
DECL|member|word2
id|u16
id|word2
suffix:semicolon
DECL|member|word3
id|u16
id|word3
suffix:semicolon
DECL|member|word4
id|u16
id|word4
suffix:semicolon
)brace
suffix:semicolon
DECL|union|eth1394_hdr
r_union
id|eth1394_hdr
(brace
DECL|member|common
r_struct
id|eth1394_common_hdr
id|common
suffix:semicolon
DECL|member|uf
r_struct
id|eth1394_uf_hdr
id|uf
suffix:semicolon
DECL|member|ff
r_struct
id|eth1394_ff_hdr
id|ff
suffix:semicolon
DECL|member|sf
r_struct
id|eth1394_sf_hdr
id|sf
suffix:semicolon
DECL|member|words
r_struct
id|eth1394_hdr_words
id|words
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* End of IP1394 headers */
multiline_comment|/* Fragment types */
DECL|macro|ETH1394_HDR_LF_UF
mdefine_line|#define ETH1394_HDR_LF_UF&t;0&t;/* unfragmented&t;&t;*/
DECL|macro|ETH1394_HDR_LF_FF
mdefine_line|#define ETH1394_HDR_LF_FF&t;1&t;/* first fragment&t;*/
DECL|macro|ETH1394_HDR_LF_LF
mdefine_line|#define ETH1394_HDR_LF_LF&t;2&t;/* last fragment&t;*/
DECL|macro|ETH1394_HDR_LF_IF
mdefine_line|#define ETH1394_HDR_LF_IF&t;3&t;/* interior fragment&t;*/
DECL|macro|IP1394_HW_ADDR_LEN
mdefine_line|#define IP1394_HW_ADDR_LEN&t;16&t;/* As per RFC&t;&t;*/
multiline_comment|/* Our arp packet (ARPHRD_IEEE1394) */
DECL|struct|eth1394_arp
r_struct
id|eth1394_arp
(brace
DECL|member|hw_type
id|u16
id|hw_type
suffix:semicolon
multiline_comment|/* 0x0018&t;*/
DECL|member|proto_type
id|u16
id|proto_type
suffix:semicolon
multiline_comment|/* 0x0806&t;*/
DECL|member|hw_addr_len
id|u8
id|hw_addr_len
suffix:semicolon
multiline_comment|/* 16 &t;&t;*/
DECL|member|ip_addr_len
id|u8
id|ip_addr_len
suffix:semicolon
multiline_comment|/* 4&t;&t;*/
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
multiline_comment|/* ARP Opcode&t;*/
multiline_comment|/* Above is exactly the same format as struct arphdr */
DECL|member|s_uniq_id
id|u64
id|s_uniq_id
suffix:semicolon
multiline_comment|/* Sender&squot;s 64bit EUI&t;&t;&t;*/
DECL|member|max_rec
id|u8
id|max_rec
suffix:semicolon
multiline_comment|/* Sender&squot;s max packet size&t;&t;*/
DECL|member|sspd
id|u8
id|sspd
suffix:semicolon
multiline_comment|/* Sender&squot;s max speed&t;&t;&t;*/
DECL|member|fifo_hi
id|u16
id|fifo_hi
suffix:semicolon
multiline_comment|/* hi 16bits of sender&squot;s FIFO addr&t;*/
DECL|member|fifo_lo
id|u32
id|fifo_lo
suffix:semicolon
multiline_comment|/* lo 32bits of sender&squot;s FIFO addr&t;*/
DECL|member|sip
id|u32
id|sip
suffix:semicolon
multiline_comment|/* Sender&squot;s IP Address&t;&t;&t;*/
DECL|member|tip
id|u32
id|tip
suffix:semicolon
multiline_comment|/* IP Address of requested hw addr&t;*/
)brace
suffix:semicolon
multiline_comment|/* Network timeout */
DECL|macro|ETHER1394_TIMEOUT
mdefine_line|#define ETHER1394_TIMEOUT&t;100000
multiline_comment|/* This is our task struct. It&squot;s used for the packet complete callback.  */
DECL|struct|packet_task
r_struct
id|packet_task
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|outstanding_pkts
r_int
id|outstanding_pkts
suffix:semicolon
DECL|member|tx_type
id|eth1394_tx_type
id|tx_type
suffix:semicolon
DECL|member|max_payload
r_int
id|max_payload
suffix:semicolon
DECL|member|packet
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
DECL|member|priv
r_struct
id|eth1394_priv
op_star
id|priv
suffix:semicolon
DECL|member|hdr
r_union
id|eth1394_hdr
id|hdr
suffix:semicolon
DECL|member|addr
id|u64
id|addr
suffix:semicolon
DECL|member|dest_node
id|u16
id|dest_node
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ETH1394_H */
eof
