multiline_comment|/*&n; * VLAN&t;&t;An implementation of 802.1Q VLAN tagging.&n; *&n; * Authors:&t;Ben Greear &lt;greearb@candelatech.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#ifndef _LINUX_IF_VLAN_H_
DECL|macro|_LINUX_IF_VLAN_H_
mdefine_line|#define _LINUX_IF_VLAN_H_
macro_line|#ifdef __KERNEL__
multiline_comment|/* externally defined structs */
r_struct
id|vlan_group
suffix:semicolon
r_struct
id|net_device
suffix:semicolon
r_struct
id|sk_buff
suffix:semicolon
r_struct
id|packet_type
suffix:semicolon
r_struct
id|vlan_collection
suffix:semicolon
r_struct
id|vlan_dev_info
suffix:semicolon
macro_line|#include &lt;linux/proc_fs.h&gt; /* for proc_dir_entry */
macro_line|#include &lt;linux/netdevice.h&gt;
DECL|macro|VLAN_HLEN
mdefine_line|#define VLAN_HLEN&t;4&t;&t;/* The additional bytes (on top of the Ethernet header)&n;&t;&t;&t;&t;&t; * that VLAN requires.&n;&t;&t;&t;&t;&t; */
DECL|macro|VLAN_ETH_ALEN
mdefine_line|#define VLAN_ETH_ALEN&t;6&t;&t;/* Octets in one ethernet addr&t; */
DECL|macro|VLAN_ETH_HLEN
mdefine_line|#define VLAN_ETH_HLEN&t;18&t;&t;/* Total octets in header.&t; */
DECL|macro|VLAN_ETH_ZLEN
mdefine_line|#define VLAN_ETH_ZLEN&t;64&t;&t;/* Min. octets in frame sans FCS */
multiline_comment|/*&n; * According to 802.3ac, the packet can be 4 bytes longer. --Klika Jan&n; */
DECL|macro|VLAN_ETH_DATA_LEN
mdefine_line|#define VLAN_ETH_DATA_LEN&t;1500&t;/* Max. octets in payload&t; */
DECL|macro|VLAN_ETH_FRAME_LEN
mdefine_line|#define VLAN_ETH_FRAME_LEN&t;1518&t;/* Max. octets in frame sans FCS */
DECL|struct|vlan_ethhdr
r_struct
id|vlan_ethhdr
(brace
DECL|member|h_dest
r_int
r_char
id|h_dest
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* destination eth addr&t;*/
DECL|member|h_source
r_int
r_char
id|h_source
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* source ether addr&t;*/
DECL|member|h_vlan_proto
r_int
r_int
id|h_vlan_proto
suffix:semicolon
multiline_comment|/* Should always be 0x8100 */
DECL|member|h_vlan_TCI
r_int
r_int
id|h_vlan_TCI
suffix:semicolon
multiline_comment|/* Encapsulates priority and VLAN ID */
DECL|member|h_vlan_encapsulated_proto
r_int
r_int
id|h_vlan_encapsulated_proto
suffix:semicolon
multiline_comment|/* packet type ID field (or len) */
)brace
suffix:semicolon
DECL|struct|vlan_hdr
r_struct
id|vlan_hdr
(brace
DECL|member|h_vlan_TCI
r_int
r_int
id|h_vlan_TCI
suffix:semicolon
multiline_comment|/* Encapsulates priority and VLAN ID */
DECL|member|h_vlan_encapsulated_proto
r_int
r_int
id|h_vlan_encapsulated_proto
suffix:semicolon
multiline_comment|/* packet type ID field (or len) */
)brace
suffix:semicolon
DECL|macro|VLAN_VID_MASK
mdefine_line|#define VLAN_VID_MASK&t;0xfff
multiline_comment|/* found in af_inet.c */
r_extern
r_int
(paren
op_star
id|vlan_ioctl_hook
)paren
(paren
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|macro|VLAN_NAME
mdefine_line|#define VLAN_NAME &quot;vlan&quot;
multiline_comment|/* if this changes, algorithm will have to be reworked because this&n; * depends on completely exhausting the VLAN identifier space.  Thus&n; * it gives constant time look-up, but in many cases it wastes memory.&n; */
DECL|macro|VLAN_GROUP_ARRAY_LEN
mdefine_line|#define VLAN_GROUP_ARRAY_LEN 4096
DECL|struct|vlan_group
r_struct
id|vlan_group
(brace
DECL|member|real_dev_ifindex
r_int
id|real_dev_ifindex
suffix:semicolon
multiline_comment|/* The ifindex of the ethernet(like) device the vlan is attached to. */
DECL|member|vlan_devices
r_struct
id|net_device
op_star
id|vlan_devices
(braket
id|VLAN_GROUP_ARRAY_LEN
)braket
suffix:semicolon
DECL|member|next
r_struct
id|vlan_group
op_star
id|next
suffix:semicolon
multiline_comment|/* the next in the list */
)brace
suffix:semicolon
DECL|struct|vlan_priority_tci_mapping
r_struct
id|vlan_priority_tci_mapping
(brace
DECL|member|priority
r_int
r_int
id|priority
suffix:semicolon
DECL|member|vlan_qos
r_int
r_int
id|vlan_qos
suffix:semicolon
multiline_comment|/* This should be shifted when first set, so we only do it&n;&t;&t;&t;&t;  * at provisioning time.&n;&t;&t;&t;&t;  * ((skb-&gt;priority &lt;&lt; 13) &amp; 0xE000)&n;&t;&t;&t;&t;  */
DECL|member|next
r_struct
id|vlan_priority_tci_mapping
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Holds information that makes sense if this device is a VLAN device. */
DECL|struct|vlan_dev_info
r_struct
id|vlan_dev_info
(brace
multiline_comment|/** This will be the mapping that correlates skb-&gt;priority to&n;&t; * 3 bits of VLAN QOS tags...&n;&t; */
DECL|member|ingress_priority_map
r_int
r_int
id|ingress_priority_map
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|egress_priority_map
r_struct
id|vlan_priority_tci_mapping
op_star
id|egress_priority_map
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* hash table */
DECL|member|vlan_id
r_int
r_int
id|vlan_id
suffix:semicolon
multiline_comment|/*  The VLAN Identifier for this interface. */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* (1 &lt;&lt; 0) re_order_header   This option will cause the&n;                                        *   VLAN code to move around the ethernet header on&n;                                        *   ingress to make the skb look **exactly** like it&n;                                        *   came in from an ethernet port.  This destroys some of&n;                                        *   the VLAN information in the skb, but it fixes programs&n;                                        *   like DHCP that use packet-filtering and don&squot;t understand&n;                                        *   802.1Q&n;                                        */
DECL|member|old_mc_list
r_struct
id|dev_mc_list
op_star
id|old_mc_list
suffix:semicolon
multiline_comment|/* old multi-cast list for the VLAN interface..&n;                                           * we save this so we can tell what changes were&n;                                           * made, in order to feed the right changes down&n;                                           * to the real hardware...&n;                                           */
DECL|member|old_allmulti
r_int
id|old_allmulti
suffix:semicolon
multiline_comment|/* similar to above. */
DECL|member|old_promiscuity
r_int
id|old_promiscuity
suffix:semicolon
multiline_comment|/* similar to above. */
DECL|member|real_dev
r_struct
id|net_device
op_star
id|real_dev
suffix:semicolon
multiline_comment|/* the underlying device/interface */
DECL|member|dent
r_struct
id|proc_dir_entry
op_star
id|dent
suffix:semicolon
multiline_comment|/* Holds the proc data */
DECL|member|cnt_inc_headroom_on_tx
r_int
r_int
id|cnt_inc_headroom_on_tx
suffix:semicolon
multiline_comment|/* How many times did we have to grow the skb on TX. */
DECL|member|cnt_encap_on_xmit
r_int
r_int
id|cnt_encap_on_xmit
suffix:semicolon
multiline_comment|/* How many times did we have to encapsulate the skb on TX. */
DECL|member|dev_stats
r_struct
id|net_device_stats
id|dev_stats
suffix:semicolon
multiline_comment|/* Device stats (rx-bytes, tx-pkts, etc...) */
)brace
suffix:semicolon
DECL|macro|VLAN_DEV_INFO
mdefine_line|#define VLAN_DEV_INFO(x) ((struct vlan_dev_info *)(x-&gt;priv))
multiline_comment|/* inline functions */
DECL|function|vlan_dev_get_stats
r_static
r_inline
r_struct
id|net_device_stats
op_star
id|vlan_dev_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
op_amp
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|dev_stats
)paren
suffix:semicolon
)brace
DECL|function|vlan_get_ingress_priority
r_static
r_inline
id|__u32
id|vlan_get_ingress_priority
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|vlan_tag
)paren
(brace
r_struct
id|vlan_dev_info
op_star
id|vip
op_assign
id|VLAN_DEV_INFO
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|vip-&gt;ingress_priority_map
(braket
(paren
id|vlan_tag
op_rshift
l_int|13
)paren
op_amp
l_int|0x7
)braket
suffix:semicolon
)brace
multiline_comment|/* VLAN tx hw acceleration helpers. */
DECL|struct|vlan_skb_tx_cookie
r_struct
id|vlan_skb_tx_cookie
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|vlan_tag
id|u32
id|vlan_tag
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VLAN_TX_COOKIE_MAGIC
mdefine_line|#define VLAN_TX_COOKIE_MAGIC&t;0x564c414e&t;/* &quot;VLAN&quot; in ascii. */
DECL|macro|VLAN_TX_SKB_CB
mdefine_line|#define VLAN_TX_SKB_CB(__skb)&t;((struct vlan_skb_tx_cookie *)&amp;((__skb)-&gt;cb[0]))
DECL|macro|vlan_tx_tag_present
mdefine_line|#define vlan_tx_tag_present(__skb) &bslash;&n;&t;(VLAN_TX_SKB_CB(__skb)-&gt;magic == VLAN_TX_COOKIE_MAGIC)
DECL|macro|vlan_tx_tag_get
mdefine_line|#define vlan_tx_tag_get(__skb)&t;(VLAN_TX_SKB_CB(__skb)-&gt;vlan_tag)
multiline_comment|/* VLAN rx hw acceleration helper.  This acts like netif_rx().  */
DECL|function|vlan_hwaccel_rx
r_static
r_inline
r_int
id|vlan_hwaccel_rx
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|vlan_group
op_star
id|grp
comma
r_int
r_int
id|vlan_tag
)paren
(brace
r_struct
id|net_device_stats
op_star
id|stats
suffix:semicolon
id|skb-&gt;dev
op_assign
id|grp-&gt;vlan_devices
(braket
id|vlan_tag
op_amp
id|VLAN_VID_MASK
)braket
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;dev
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* Not NET_RX_DROP, this is not being dropped&n;&t;&t; * due to congestion.&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
id|skb-&gt;dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
id|stats
op_assign
id|vlan_dev_get_stats
c_func
(paren
id|skb-&gt;dev
)paren
suffix:semicolon
id|stats-&gt;rx_packets
op_increment
suffix:semicolon
id|stats-&gt;rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb-&gt;priority
op_assign
id|vlan_get_ingress_priority
c_func
(paren
id|skb-&gt;dev
comma
id|vlan_tag
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;pkt_type
)paren
(brace
r_case
id|PACKET_BROADCAST
suffix:colon
r_break
suffix:semicolon
r_case
id|PACKET_MULTICAST
suffix:colon
id|stats-&gt;multicast
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PACKET_OTHERHOST
suffix:colon
multiline_comment|/* Our lower layer thinks this is not local, let&squot;s make sure.&n;&t;&t; * This allows the VLAN to have a different MAC than the underlying&n;&t;&t; * device, and still route correctly.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|skb-&gt;mac.ethernet-&gt;h_dest
comma
id|skb-&gt;dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
)paren
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* VLAN IOCTLs are found in sockios.h */
multiline_comment|/* Passed in vlan_ioctl_args structure to determine behaviour. */
DECL|enum|vlan_ioctl_cmds
r_enum
id|vlan_ioctl_cmds
(brace
DECL|enumerator|ADD_VLAN_CMD
id|ADD_VLAN_CMD
comma
DECL|enumerator|DEL_VLAN_CMD
id|DEL_VLAN_CMD
comma
DECL|enumerator|SET_VLAN_INGRESS_PRIORITY_CMD
id|SET_VLAN_INGRESS_PRIORITY_CMD
comma
DECL|enumerator|SET_VLAN_EGRESS_PRIORITY_CMD
id|SET_VLAN_EGRESS_PRIORITY_CMD
comma
DECL|enumerator|GET_VLAN_INGRESS_PRIORITY_CMD
id|GET_VLAN_INGRESS_PRIORITY_CMD
comma
DECL|enumerator|GET_VLAN_EGRESS_PRIORITY_CMD
id|GET_VLAN_EGRESS_PRIORITY_CMD
comma
DECL|enumerator|SET_VLAN_NAME_TYPE_CMD
id|SET_VLAN_NAME_TYPE_CMD
comma
DECL|enumerator|SET_VLAN_FLAG_CMD
id|SET_VLAN_FLAG_CMD
)brace
suffix:semicolon
DECL|enum|vlan_name_types
r_enum
id|vlan_name_types
(brace
DECL|enumerator|VLAN_NAME_TYPE_PLUS_VID
id|VLAN_NAME_TYPE_PLUS_VID
comma
multiline_comment|/* Name will look like:  vlan0005 */
DECL|enumerator|VLAN_NAME_TYPE_RAW_PLUS_VID
id|VLAN_NAME_TYPE_RAW_PLUS_VID
comma
multiline_comment|/* name will look like:  eth1.0005 */
DECL|enumerator|VLAN_NAME_TYPE_PLUS_VID_NO_PAD
id|VLAN_NAME_TYPE_PLUS_VID_NO_PAD
comma
multiline_comment|/* Name will look like:  vlan5 */
DECL|enumerator|VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD
id|VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD
comma
multiline_comment|/* Name will look like:  eth0.5 */
DECL|enumerator|VLAN_NAME_TYPE_HIGHEST
id|VLAN_NAME_TYPE_HIGHEST
)brace
suffix:semicolon
DECL|struct|vlan_ioctl_args
r_struct
id|vlan_ioctl_args
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
multiline_comment|/* Should be one of the vlan_ioctl_cmds enum above. */
DECL|member|device1
r_char
id|device1
(braket
l_int|24
)braket
suffix:semicolon
r_union
(brace
DECL|member|device2
r_char
id|device2
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|VID
r_int
id|VID
suffix:semicolon
DECL|member|skb_priority
r_int
r_int
id|skb_priority
suffix:semicolon
DECL|member|name_type
r_int
r_int
id|name_type
suffix:semicolon
DECL|member|bind_type
r_int
r_int
id|bind_type
suffix:semicolon
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
multiline_comment|/* Matches vlan_dev_info flags */
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|vlan_qos
r_int
id|vlan_qos
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(_LINUX_IF_VLAN_H_) */
eof
