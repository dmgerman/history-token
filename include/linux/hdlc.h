multiline_comment|/*&n; * Generic HDLC support routines for Linux&n; *&n; * Copyright (C) 1999-2003 Krzysztof Halasa &lt;khc@pm.waw.pl&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; */
macro_line|#ifndef __HDLC_H
DECL|macro|__HDLC_H
mdefine_line|#define __HDLC_H
DECL|macro|GENERIC_HDLC_VERSION
mdefine_line|#define GENERIC_HDLC_VERSION 4&t;/* For synchronization with sethdlc utility */
DECL|macro|CLOCK_DEFAULT
mdefine_line|#define CLOCK_DEFAULT   0&t;/* Default setting */
DECL|macro|CLOCK_EXT
mdefine_line|#define CLOCK_EXT&t;1&t;/* External TX and RX clock - DTE */
DECL|macro|CLOCK_INT
mdefine_line|#define CLOCK_INT&t;2&t;/* Internal TX and RX clock - DCE */
DECL|macro|CLOCK_TXINT
mdefine_line|#define CLOCK_TXINT&t;3&t;/* Internal TX and external RX clock */
DECL|macro|CLOCK_TXFROMRX
mdefine_line|#define CLOCK_TXFROMRX&t;4&t;/* TX clock derived from external RX clock */
DECL|macro|ENCODING_DEFAULT
mdefine_line|#define ENCODING_DEFAULT&t;0 /* Default setting */
DECL|macro|ENCODING_NRZ
mdefine_line|#define ENCODING_NRZ&t;&t;1
DECL|macro|ENCODING_NRZI
mdefine_line|#define ENCODING_NRZI&t;&t;2
DECL|macro|ENCODING_FM_MARK
mdefine_line|#define ENCODING_FM_MARK&t;3
DECL|macro|ENCODING_FM_SPACE
mdefine_line|#define ENCODING_FM_SPACE&t;4
DECL|macro|ENCODING_MANCHESTER
mdefine_line|#define ENCODING_MANCHESTER&t;5
DECL|macro|PARITY_DEFAULT
mdefine_line|#define PARITY_DEFAULT&t;&t;0 /* Default setting */
DECL|macro|PARITY_NONE
mdefine_line|#define PARITY_NONE&t;&t;1 /* No parity */
DECL|macro|PARITY_CRC16_PR0
mdefine_line|#define PARITY_CRC16_PR0&t;2 /* CRC16, initial value 0x0000 */
DECL|macro|PARITY_CRC16_PR1
mdefine_line|#define PARITY_CRC16_PR1&t;3 /* CRC16, initial value 0xFFFF */
DECL|macro|PARITY_CRC16_PR0_CCITT
mdefine_line|#define PARITY_CRC16_PR0_CCITT&t;4 /* CRC16, initial 0x0000, ITU-T version */
DECL|macro|PARITY_CRC16_PR1_CCITT
mdefine_line|#define PARITY_CRC16_PR1_CCITT&t;5 /* CRC16, initial 0xFFFF, ITU-T version */
DECL|macro|PARITY_CRC32_PR0_CCITT
mdefine_line|#define PARITY_CRC32_PR0_CCITT&t;6 /* CRC32, initial value 0x00000000 */
DECL|macro|PARITY_CRC32_PR1_CCITT
mdefine_line|#define PARITY_CRC32_PR1_CCITT&t;7 /* CRC32, initial value 0xFFFFFFFF */
DECL|macro|LMI_DEFAULT
mdefine_line|#define LMI_DEFAULT&t;&t;0 /* Default setting */
DECL|macro|LMI_NONE
mdefine_line|#define LMI_NONE&t;&t;1 /* No LMI, all PVCs are static */
DECL|macro|LMI_ANSI
mdefine_line|#define LMI_ANSI&t;&t;2 /* ANSI Annex D */
DECL|macro|LMI_CCITT
mdefine_line|#define LMI_CCITT&t;&t;3 /* ITU-T Annex A */
DECL|macro|HDLC_MAX_MTU
mdefine_line|#define HDLC_MAX_MTU 1500&t;/* Ethernet 1500 bytes */
DECL|macro|HDLC_MAX_MRU
mdefine_line|#define HDLC_MAX_MRU (HDLC_MAX_MTU + 10 + 14 + 4) /* for ETH+VLAN over FR */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/syncppp.h&gt;
macro_line|#include &lt;linux/hdlc/ioctl.h&gt;
r_typedef
r_struct
(brace
multiline_comment|/* Used in Cisco and PPP mode */
DECL|member|address
id|u8
id|address
suffix:semicolon
DECL|member|control
id|u8
id|control
suffix:semicolon
DECL|member|protocol
id|u16
id|protocol
suffix:semicolon
DECL|typedef|hdlc_header
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|hdlc_header
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* code */
DECL|member|par1
id|u32
id|par1
suffix:semicolon
DECL|member|par2
id|u32
id|par2
suffix:semicolon
DECL|member|rel
id|u16
id|rel
suffix:semicolon
multiline_comment|/* reliability */
DECL|member|time
id|u32
id|time
suffix:semicolon
DECL|typedef|cisco_packet
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|cisco_packet
suffix:semicolon
DECL|macro|CISCO_PACKET_LEN
mdefine_line|#define&t;CISCO_PACKET_LEN&t;18
DECL|macro|CISCO_BIG_PACKET_LEN
mdefine_line|#define&t;CISCO_BIG_PACKET_LEN&t;20
DECL|struct|pvc_device_struct
r_typedef
r_struct
id|pvc_device_struct
(brace
DECL|member|master
r_struct
id|hdlc_device_struct
op_star
id|master
suffix:semicolon
DECL|member|main
r_struct
id|net_device
op_star
id|main
suffix:semicolon
DECL|member|ether
r_struct
id|net_device
op_star
id|ether
suffix:semicolon
multiline_comment|/* bridged Ethernet interface */
DECL|member|next
r_struct
id|pvc_device_struct
op_star
id|next
suffix:semicolon
multiline_comment|/* Sorted in ascending DLCI order */
DECL|member|dlci
r_int
id|dlci
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
r_struct
(brace
DECL|member|new
r_int
r_int
r_new
suffix:colon
l_int|1
suffix:semicolon
DECL|member|active
r_int
r_int
id|active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|exist
r_int
r_int
id|exist
suffix:colon
l_int|1
suffix:semicolon
DECL|member|deleted
r_int
r_int
id|deleted
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fecn
r_int
r_int
id|fecn
suffix:colon
l_int|1
suffix:semicolon
DECL|member|becn
r_int
r_int
id|becn
suffix:colon
l_int|1
suffix:semicolon
DECL|member|state
)brace
id|state
suffix:semicolon
DECL|typedef|pvc_device
)brace
id|pvc_device
suffix:semicolon
DECL|struct|hdlc_device_struct
r_typedef
r_struct
id|hdlc_device_struct
(brace
multiline_comment|/* To be initialized by hardware driver */
DECL|member|netdev
r_struct
id|net_device
id|netdev
suffix:semicolon
multiline_comment|/* master net device - must be first */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* used by HDLC layer to take control over HDLC device from hw driver*/
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|hdlc_device_struct
op_star
id|hdlc
comma
r_int
r_int
id|encoding
comma
r_int
r_int
id|parity
)paren
suffix:semicolon
multiline_comment|/* hardware driver must handle this instead of dev-&gt;hard_start_xmit */
DECL|member|xmit
r_int
(paren
op_star
id|xmit
)paren
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
multiline_comment|/* Things below are for HDLC layer internal use only */
r_struct
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|hdlc_device_struct
op_star
id|hdlc
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|hdlc_device_struct
op_star
id|hdlc
)paren
suffix:semicolon
multiline_comment|/* if open &amp; DCD */
DECL|member|start
r_void
(paren
op_star
id|start
)paren
(paren
r_struct
id|hdlc_device_struct
op_star
id|hdlc
)paren
suffix:semicolon
multiline_comment|/* if open &amp; !DCD */
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|hdlc_device_struct
op_star
id|hdlc
)paren
suffix:semicolon
DECL|member|detach
r_void
(paren
op_star
id|detach
)paren
(paren
r_struct
id|hdlc_device_struct
op_star
id|hdlc
)paren
suffix:semicolon
DECL|member|netif_rx
r_void
(paren
op_star
id|netif_rx
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|type_trans
r_int
r_int
(paren
op_star
id|type_trans
)paren
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
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* IF_PROTO_HDLC/CISCO/FR/etc. */
DECL|member|proto
)brace
id|proto
suffix:semicolon
DECL|member|carrier
r_int
id|carrier
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|state_lock
id|spinlock_t
id|state_lock
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|settings
id|fr_proto
id|settings
suffix:semicolon
DECL|member|first_pvc
id|pvc_device
op_star
id|first_pvc
suffix:semicolon
DECL|member|dce_pvc_count
r_int
id|dce_pvc_count
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|last_poll
r_int
id|last_poll
suffix:semicolon
DECL|member|reliable
r_int
id|reliable
suffix:semicolon
DECL|member|dce_changed
r_int
id|dce_changed
suffix:semicolon
DECL|member|request
r_int
id|request
suffix:semicolon
DECL|member|fullrep_sent
r_int
id|fullrep_sent
suffix:semicolon
DECL|member|last_errors
id|u32
id|last_errors
suffix:semicolon
multiline_comment|/* last errors bit list */
DECL|member|n391cnt
id|u8
id|n391cnt
suffix:semicolon
DECL|member|txseq
id|u8
id|txseq
suffix:semicolon
multiline_comment|/* TX sequence number */
DECL|member|rxseq
id|u8
id|rxseq
suffix:semicolon
multiline_comment|/* RX sequence number */
DECL|member|fr
)brace
id|fr
suffix:semicolon
r_struct
(brace
DECL|member|settings
id|cisco_proto
id|settings
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|last_poll
r_int
id|last_poll
suffix:semicolon
DECL|member|up
r_int
id|up
suffix:semicolon
DECL|member|txseq
id|u32
id|txseq
suffix:semicolon
multiline_comment|/* TX sequence number */
DECL|member|rxseq
id|u32
id|rxseq
suffix:semicolon
multiline_comment|/* RX sequence number */
DECL|member|cisco
)brace
id|cisco
suffix:semicolon
r_struct
(brace
DECL|member|settings
id|raw_hdlc_proto
id|settings
suffix:semicolon
DECL|member|raw_hdlc
)brace
id|raw_hdlc
suffix:semicolon
r_struct
(brace
DECL|member|pppdev
r_struct
id|ppp_device
id|pppdev
suffix:semicolon
DECL|member|syncppp_ptr
r_struct
id|ppp_device
op_star
id|syncppp_ptr
suffix:semicolon
DECL|member|old_change_mtu
r_int
(paren
op_star
id|old_change_mtu
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
suffix:semicolon
DECL|member|ppp
)brace
id|ppp
suffix:semicolon
DECL|member|state
)brace
id|state
suffix:semicolon
DECL|typedef|hdlc_device
)brace
id|hdlc_device
suffix:semicolon
r_int
id|hdlc_raw_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
suffix:semicolon
r_int
id|hdlc_raw_eth_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
suffix:semicolon
r_int
id|hdlc_cisco_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
suffix:semicolon
r_int
id|hdlc_ppp_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
suffix:semicolon
r_int
id|hdlc_fr_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
suffix:semicolon
r_int
id|hdlc_x25_ioctl
c_func
(paren
id|hdlc_device
op_star
id|hdlc
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
suffix:semicolon
multiline_comment|/* Exported from hdlc.o */
multiline_comment|/* Called by hardware driver when a user requests HDLC service */
r_int
id|hdlc_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Must be used by hardware driver on module startup/exit */
r_int
id|register_hdlc_device
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
suffix:semicolon
r_void
id|unregister_hdlc_device
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
suffix:semicolon
DECL|function|hdlc_to_dev
r_static
id|__inline__
r_struct
id|net_device
op_star
id|hdlc_to_dev
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_return
op_amp
id|hdlc-&gt;netdev
suffix:semicolon
)brace
DECL|function|dev_to_hdlc
r_static
id|__inline__
id|hdlc_device
op_star
id|dev_to_hdlc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|hdlc_device
op_star
)paren
id|dev
suffix:semicolon
)brace
DECL|function|dev_to_pvc
r_static
id|__inline__
id|pvc_device
op_star
id|dev_to_pvc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|pvc_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
)brace
DECL|function|hdlc_to_name
r_static
id|__inline__
r_const
r_char
op_star
id|hdlc_to_name
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_return
id|hdlc_to_dev
c_func
(paren
id|hdlc
)paren
op_member_access_from_pointer
id|name
suffix:semicolon
)brace
DECL|function|debug_frame
r_static
id|__inline__
r_void
id|debug_frame
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|skb-&gt;len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
l_int|100
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %02X&quot;
comma
id|skb-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Must be called by hardware driver when HDLC device is being opened */
r_int
id|hdlc_open
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
suffix:semicolon
multiline_comment|/* Must be called by hardware driver when HDLC device is being closed */
r_void
id|hdlc_close
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
suffix:semicolon
multiline_comment|/* Called by hardware driver when DCD line level changes */
r_void
id|hdlc_set_carrier
c_func
(paren
r_int
id|on
comma
id|hdlc_device
op_star
id|hdlc
)paren
suffix:semicolon
multiline_comment|/* May be used by hardware driver to gain control over HDLC device */
DECL|function|hdlc_proto_detach
r_static
id|__inline__
r_void
id|hdlc_proto_detach
c_func
(paren
id|hdlc_device
op_star
id|hdlc
)paren
(brace
r_if
c_cond
(paren
id|hdlc-&gt;proto.detach
)paren
id|hdlc-&gt;proto
dot
id|detach
c_func
(paren
id|hdlc
)paren
suffix:semicolon
id|hdlc-&gt;proto.detach
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|hdlc_type_trans
r_static
id|__inline__
r_int
r_int
id|hdlc_type_trans
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
id|hdlc_device
op_star
id|hdlc
op_assign
id|dev_to_hdlc
c_func
(paren
id|skb-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdlc-&gt;proto.type_trans
)paren
r_return
id|hdlc-&gt;proto
dot
id|type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
r_else
r_return
id|__constant_htons
c_func
(paren
id|ETH_P_HDLC
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL */
macro_line|#endif /* __HDLC_H */
eof
