macro_line|#ifndef __BEN_VLAN_802_1Q_INC__
DECL|macro|__BEN_VLAN_802_1Q_INC__
mdefine_line|#define __BEN_VLAN_802_1Q_INC__
macro_line|#include &lt;linux/if_vlan.h&gt;
multiline_comment|/*  Uncomment this if you want debug traces to be shown. */
multiline_comment|/* #define VLAN_DEBUG */
DECL|macro|VLAN_ERR
mdefine_line|#define VLAN_ERR KERN_ERR
DECL|macro|VLAN_INF
mdefine_line|#define VLAN_INF KERN_ALERT
DECL|macro|VLAN_DBG
mdefine_line|#define VLAN_DBG KERN_ALERT /* change these... to debug, having a hard time&n;                             * changing the log level at run-time..for some reason.&n;                             */
multiline_comment|/*&n;&n;These I use for memory debugging.  I feared a leak at one time, but&n;I never found it..and the problem seems to have dissappeared.  Still,&n;I&squot;ll bet they might prove useful again... --Ben&n;&n;&n;#define VLAN_MEM_DBG(x, y, z) printk(VLAN_DBG __FUNCTION__ &quot;:  &quot;  x, y, z);&n;#define VLAN_FMEM_DBG(x, y) printk(VLAN_DBG __FUNCTION__  &quot;:  &quot; x, y);&n;*/
multiline_comment|/* This way they don&squot;t do anything! */
DECL|macro|VLAN_MEM_DBG
mdefine_line|#define VLAN_MEM_DBG(x, y, z) 
DECL|macro|VLAN_FMEM_DBG
mdefine_line|#define VLAN_FMEM_DBG(x, y)
r_extern
r_int
r_int
id|vlan_name_type
suffix:semicolon
DECL|macro|VLAN_GRP_HASH_SHIFT
mdefine_line|#define VLAN_GRP_HASH_SHIFT&t;5
DECL|macro|VLAN_GRP_HASH_SIZE
mdefine_line|#define VLAN_GRP_HASH_SIZE&t;(1 &lt;&lt; VLAN_GRP_HASH_SHIFT)
DECL|macro|VLAN_GRP_HASH_MASK
mdefine_line|#define VLAN_GRP_HASH_MASK&t;(VLAN_GRP_HASH_SIZE - 1)
r_extern
r_struct
id|vlan_group
op_star
id|vlan_group_hash
(braket
id|VLAN_GRP_HASH_SIZE
)braket
suffix:semicolon
r_extern
id|spinlock_t
id|vlan_group_lock
suffix:semicolon
multiline_comment|/*  Find a VLAN device by the MAC address of its Ethernet device, and&n; *  it&squot;s VLAN ID.  The default configuration is to have VLAN&squot;s scope&n; *  to be box-wide, so the MAC will be ignored.  The mac will only be&n; *  looked at if we are configured to have a separate set of VLANs per&n; *  each MAC addressable interface.  Note that this latter option does&n; *  NOT follow the spec for VLANs, but may be useful for doing very&n; *  large quantities of VLAN MUX/DEMUX onto FrameRelay or ATM PVCs.&n; *&n; *  Must be invoked with vlan_group_lock held and that lock MUST NOT&n; *  be dropped until a reference is obtained on the returned device.&n; *  You may drop the lock earlier if you are running under the RTNL&n; *  semaphore, however.&n; */
r_struct
id|net_device
op_star
id|__find_vlan_dev
c_func
(paren
r_struct
id|net_device
op_star
id|real_dev
comma
r_int
r_int
id|VID
)paren
suffix:semicolon
multiline_comment|/* vlan.c */
multiline_comment|/* found in vlan_dev.c */
r_int
id|vlan_dev_rebuild_header
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|vlan_skb_recv
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
r_struct
id|packet_type
op_star
id|ptype
)paren
suffix:semicolon
r_int
id|vlan_dev_hard_header
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
r_int
id|vlan_dev_hard_start_xmit
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
r_int
id|vlan_dev_hwaccel_hard_start_xmit
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
r_int
id|vlan_dev_change_mtu
c_func
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
r_int
id|vlan_dev_set_mac_address
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
r_int
id|vlan_dev_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|vlan_dev_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|vlan_dev_set_ingress_priority
c_func
(paren
r_char
op_star
id|dev_name
comma
id|__u32
id|skb_prio
comma
r_int
id|vlan_prio
)paren
suffix:semicolon
r_int
id|vlan_dev_set_egress_priority
c_func
(paren
r_char
op_star
id|dev_name
comma
id|__u32
id|skb_prio
comma
r_int
id|vlan_prio
)paren
suffix:semicolon
r_int
id|vlan_dev_set_vlan_flag
c_func
(paren
r_char
op_star
id|dev_name
comma
id|__u32
id|flag
comma
r_int
id|flag_val
)paren
suffix:semicolon
r_void
id|vlan_dev_set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|vlan_dev
)paren
suffix:semicolon
macro_line|#endif /* !(__BEN_VLAN_802_1Q_INC__) */
eof
