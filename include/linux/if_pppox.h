multiline_comment|/***************************************************************************&n; * Linux PPP over X - Generic PPP transport layer sockets&n; * Linux PPP over Ethernet (PPPoE) Socket Implementation (RFC 2516) &n; *&n; * This file supplies definitions required by the PPP over Ethernet driver&n; * (pppox.c).  All version information wrt this file is located in pppox.c&n; *&n; * License:&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#ifndef __LINUX_IF_PPPOX_H
DECL|macro|__LINUX_IF_PPPOX_H
mdefine_line|#define __LINUX_IF_PPPOX_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifdef  __KERNEL__
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/ppp_channel.h&gt;
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* For user-space programs to pick up these definitions&n; * which they wouldn&squot;t get otherwise without defining __KERNEL__&n; */
macro_line|#ifndef AF_PPPOX
DECL|macro|AF_PPPOX
mdefine_line|#define AF_PPPOX&t;24
DECL|macro|PF_PPPOX
mdefine_line|#define PF_PPPOX&t;AF_PPPOX
macro_line|#endif /* !(AF_PPPOX) */
multiline_comment|/************************************************************************ &n; * PPPoE addressing definition &n; */
DECL|typedef|sid_t
r_typedef
id|__u16
id|sid_t
suffix:semicolon
DECL|struct|pppoe_addr
r_struct
id|pppoe_addr
(brace
DECL|member|sid
id|sid_t
id|sid
suffix:semicolon
multiline_comment|/* Session identifier */
DECL|member|remote
r_int
r_char
id|remote
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* Remote address */
DECL|member|dev
r_char
id|dev
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Local device to use */
)brace
suffix:semicolon
multiline_comment|/************************************************************************ &n; * Protocols supported by AF_PPPOX &n; */
DECL|macro|PX_PROTO_OE
mdefine_line|#define PX_PROTO_OE    0 /* Currently just PPPoE */
DECL|macro|PX_MAX_PROTO
mdefine_line|#define PX_MAX_PROTO   1&t;
DECL|struct|sockaddr_pppox
r_struct
id|sockaddr_pppox
(brace
DECL|member|sa_family
id|sa_family_t
id|sa_family
suffix:semicolon
multiline_comment|/* address family, AF_PPPOX */
DECL|member|sa_protocol
r_int
r_int
id|sa_protocol
suffix:semicolon
multiline_comment|/* protocol identifier */
(def_block
r_union
(brace
DECL|member|pppoe
r_struct
id|pppoe_addr
id|pppoe
suffix:semicolon
DECL|member|sa_addr
)brace
)def_block
id|sa_addr
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *&n; * ioctl interface for defining forwarding of connections&n; *&n; ********************************************************************/
DECL|macro|PPPOEIOCSFWD
mdefine_line|#define PPPOEIOCSFWD&t;_IOW(0xB1 ,0, sizeof(struct sockaddr_pppox))
DECL|macro|PPPOEIOCDFWD
mdefine_line|#define PPPOEIOCDFWD&t;_IO(0xB1 ,1)
multiline_comment|/*#define PPPOEIOCGFWD&t;_IOWR(0xB1,2, sizeof(struct sockaddr_pppox))*/
multiline_comment|/* Codes to identify message types */
DECL|macro|PADI_CODE
mdefine_line|#define PADI_CODE&t;0x09
DECL|macro|PADO_CODE
mdefine_line|#define PADO_CODE&t;0x07
DECL|macro|PADR_CODE
mdefine_line|#define PADR_CODE&t;0x19
DECL|macro|PADS_CODE
mdefine_line|#define PADS_CODE&t;0x65
DECL|macro|PADT_CODE
mdefine_line|#define PADT_CODE&t;0xa7
DECL|struct|pppoe_tag
r_struct
id|pppoe_tag
(brace
DECL|member|tag_type
id|__u16
id|tag_type
suffix:semicolon
DECL|member|tag_len
id|__u16
id|tag_len
suffix:semicolon
DECL|member|tag_data
r_char
id|tag_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Tag identifiers */
DECL|macro|PTT_EOL
mdefine_line|#define PTT_EOL&t;&t;__constant_htons(0x0000)
DECL|macro|PTT_SRV_NAME
mdefine_line|#define PTT_SRV_NAME&t;__constant_htons(0x0101)
DECL|macro|PTT_AC_NAME
mdefine_line|#define PTT_AC_NAME&t;__constant_htons(0x0102)
DECL|macro|PTT_HOST_UNIQ
mdefine_line|#define PTT_HOST_UNIQ&t;__constant_htons(0x0103)
DECL|macro|PTT_AC_COOKIE
mdefine_line|#define PTT_AC_COOKIE&t;__constant_htons(0x0104)
DECL|macro|PTT_VENDOR
mdefine_line|#define PTT_VENDOR &t;__constant_htons(0x0105)
DECL|macro|PTT_RELAY_SID
mdefine_line|#define PTT_RELAY_SID&t;__constant_htons(0x0110)
DECL|macro|PTT_SRV_ERR
mdefine_line|#define PTT_SRV_ERR     __constant_htons(0x0201)
DECL|macro|PTT_SYS_ERR
mdefine_line|#define PTT_SYS_ERR  &t;__constant_htons(0x0202)
DECL|macro|PTT_GEN_ERR
mdefine_line|#define PTT_GEN_ERR  &t;__constant_htons(0x0203)
DECL|struct|pppoe_hdr
r_struct
id|pppoe_hdr
(brace
macro_line|#if defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|ver
id|__u8
id|ver
suffix:colon
l_int|4
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__BIG_ENDIAN_BITFIELD)
id|__u8
id|type
suffix:colon
l_int|4
suffix:semicolon
id|__u8
id|ver
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error&t;&quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|sid
id|__u16
id|sid
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|tag
r_struct
id|pppoe_tag
id|tag
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|pppoe_opt
r_struct
id|pppoe_opt
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* device associated with socket*/
DECL|member|pa
r_struct
id|pppoe_addr
id|pa
suffix:semicolon
multiline_comment|/* what this socket is bound to*/
DECL|member|relay
r_struct
id|sockaddr_pppox
id|relay
suffix:semicolon
multiline_comment|/* what socket data will be&n;&t;&t;&t;&t;&t;     relayed to (PPPoE relaying) */
)brace
suffix:semicolon
DECL|struct|pppox_opt
r_struct
id|pppox_opt
(brace
DECL|member|chan
r_struct
id|ppp_channel
id|chan
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|next
r_struct
id|pppox_opt
op_star
id|next
suffix:semicolon
multiline_comment|/* for hash table */
r_union
(brace
DECL|member|pppoe
r_struct
id|pppoe_opt
id|pppoe
suffix:semicolon
DECL|member|proto
)brace
id|proto
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|pppoe_dev
mdefine_line|#define pppoe_dev&t;proto.pppoe.dev
DECL|macro|pppoe_pa
mdefine_line|#define pppoe_pa&t;proto.pppoe.pa
DECL|macro|pppoe_relay
mdefine_line|#define pppoe_relay&t;proto.pppoe.relay
DECL|macro|pppox_sk
mdefine_line|#define pppox_sk(__sk) ((struct pppox_opt *)(__sk)-&gt;protinfo)
DECL|struct|pppox_proto
r_struct
id|pppox_proto
(brace
DECL|member|create
r_int
(paren
op_star
id|create
)paren
(paren
r_struct
id|socket
op_star
id|sock
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_pppox_proto
c_func
(paren
r_int
id|proto_num
comma
r_struct
id|pppox_proto
op_star
id|pp
)paren
suffix:semicolon
r_extern
r_void
id|unregister_pppox_proto
c_func
(paren
r_int
id|proto_num
)paren
suffix:semicolon
r_extern
r_void
id|pppox_unbind_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
multiline_comment|/* delete ppp-channel binding */
r_extern
r_int
id|pppox_channel_ioctl
c_func
(paren
r_struct
id|ppp_channel
op_star
id|pc
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* PPPoE socket states */
r_enum
(brace
DECL|enumerator|PPPOX_NONE
id|PPPOX_NONE
op_assign
l_int|0
comma
multiline_comment|/* initial state */
DECL|enumerator|PPPOX_CONNECTED
id|PPPOX_CONNECTED
op_assign
l_int|1
comma
multiline_comment|/* connection established ==TCP_ESTABLISHED */
DECL|enumerator|PPPOX_BOUND
id|PPPOX_BOUND
op_assign
l_int|2
comma
multiline_comment|/* bound to ppp device */
DECL|enumerator|PPPOX_RELAY
id|PPPOX_RELAY
op_assign
l_int|4
comma
multiline_comment|/* forwarding is enabled */
DECL|enumerator|PPPOX_DEAD
id|PPPOX_DEAD
op_assign
l_int|8
)brace
suffix:semicolon
r_extern
r_struct
id|ppp_channel_ops
id|pppoe_chan_ops
suffix:semicolon
r_extern
r_int
id|pppox_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|np
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(__LINUX_IF_PPPOX_H) */
eof
