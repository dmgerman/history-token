multiline_comment|/*&n; * INET&t;&t;802.1Q VLAN&n; *&t;&t;Ethernet-type device handling.&n; *&n; * Authors:&t;Ben Greear &lt;greearb@candelatech.com&gt;&n; *              Please send support related email to: vlan@scry.wanfear.com&n; *              VLAN Home Page: http://www.candelatech.com/~greear/vlan.html&n; * &n; * Fixes:&n; *              Fix for packet capture - Nick Eggleston &lt;nick@dccinc.com&gt;;&n; *&t;&t;Add HW acceleration hooks - David S. Miller &lt;davem@redhat.com&gt;;&n; *&t;&t;Correct all the locking - David S. Miller &lt;davem@redhat.com&gt;;&n; *&t;&t;Use hash table for VLAN groups - David S. Miller &lt;davem@redhat.com&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/uaccess.h&gt; /* for copy_from_user */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/p8022.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/if_vlan.h&gt;
macro_line|#include &quot;vlan.h&quot;
macro_line|#include &quot;vlanproc.h&quot;
multiline_comment|/* Global VLAN variables */
multiline_comment|/* Our listing of VLAN group(s) */
DECL|variable|vlan_group_hash
r_struct
id|vlan_group
op_star
id|vlan_group_hash
(braket
id|VLAN_GRP_HASH_SIZE
)braket
suffix:semicolon
DECL|variable|vlan_group_lock
id|spinlock_t
id|vlan_group_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|vlan_grp_hashfn
mdefine_line|#define vlan_grp_hashfn(IDX)&t;((((IDX) &gt;&gt; VLAN_GRP_HASH_SHIFT) ^ (IDX)) &amp; VLAN_GRP_HASH_MASK)
DECL|variable|vlan_fullname
r_static
r_char
id|vlan_fullname
(braket
)braket
op_assign
l_string|&quot;802.1Q VLAN Support&quot;
suffix:semicolon
DECL|variable|vlan_version
r_static
r_int
r_int
id|vlan_version
op_assign
l_int|1
suffix:semicolon
DECL|variable|vlan_release
r_static
r_int
r_int
id|vlan_release
op_assign
l_int|7
suffix:semicolon
DECL|variable|vlan_copyright
r_static
r_char
id|vlan_copyright
(braket
)braket
op_assign
l_string|&quot;Ben Greear &lt;greearb@candelatech.com&gt;&quot;
suffix:semicolon
DECL|variable|vlan_buggyright
r_static
r_char
id|vlan_buggyright
(braket
)braket
op_assign
l_string|&quot;David S. Miller &lt;davem@redhat.com&gt;&quot;
suffix:semicolon
r_static
r_int
id|vlan_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|variable|vlan_notifier_block
r_struct
id|notifier_block
id|vlan_notifier_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|vlan_device_event
comma
)brace
suffix:semicolon
multiline_comment|/* These may be changed at run-time through IOCTLs */
multiline_comment|/* Determines interface naming scheme. */
DECL|variable|vlan_name_type
r_int
r_int
id|vlan_name_type
op_assign
id|VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD
suffix:semicolon
multiline_comment|/* DO reorder the header by default */
DECL|variable|vlan_default_dev_flags
r_int
r_int
id|vlan_default_dev_flags
op_assign
l_int|1
suffix:semicolon
DECL|variable|vlan_packet_type
r_static
r_struct
id|packet_type
id|vlan_packet_type
op_assign
(brace
dot
id|type
op_assign
id|__constant_htons
c_func
(paren
id|ETH_P_8021Q
)paren
comma
dot
id|dev
op_assign
l_int|NULL
comma
dot
id|func
op_assign
id|vlan_skb_recv
comma
multiline_comment|/* VLAN receive method */
dot
id|data
op_assign
(paren
r_void
op_star
)paren
(paren
op_minus
l_int|1
)paren
comma
multiline_comment|/* Set here &squot;(void *)1&squot; when this code can SHARE SKBs */
dot
id|next
op_assign
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* End of global variables definitions. */
multiline_comment|/*&n; * Function vlan_proto_init (pro)&n; *&n; *    Initialize VLAN protocol layer, &n; *&n; */
DECL|function|vlan_proto_init
r_static
r_int
id|__init
id|vlan_proto_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
id|VLAN_INF
l_string|&quot;%s v%u.%u %s&bslash;n&quot;
comma
id|vlan_fullname
comma
id|vlan_version
comma
id|vlan_release
comma
id|vlan_copyright
)paren
suffix:semicolon
id|printk
c_func
(paren
id|VLAN_INF
l_string|&quot;All bugs added by %s&bslash;n&quot;
comma
id|vlan_buggyright
)paren
suffix:semicolon
multiline_comment|/* proc file system initialization */
id|err
op_assign
id|vlan_proc_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s %s: can&squot;t create entry in proc filesystem!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|VLAN_NAME
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dev_add_pack
c_func
(paren
op_amp
id|vlan_packet_type
)paren
suffix:semicolon
multiline_comment|/* Register us to receive netdevice events */
id|register_netdevice_notifier
c_func
(paren
op_amp
id|vlan_notifier_block
)paren
suffix:semicolon
id|vlan_ioctl_hook
op_assign
id|vlan_ioctl_handler
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *     Module &squot;remove&squot; entry point.&n; *     o delete /proc/net/router directory and static entries.&n; */
DECL|function|vlan_cleanup_module
r_static
r_void
id|__exit
id|vlan_cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* This table must be empty if there are no module&n;&t; * references left.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VLAN_GRP_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|vlan_group_hash
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Un-register us from receiving netdevice events */
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|vlan_notifier_block
)paren
suffix:semicolon
id|dev_remove_pack
c_func
(paren
op_amp
id|vlan_packet_type
)paren
suffix:semicolon
id|vlan_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
id|vlan_ioctl_hook
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|vlan_proto_init
id|module_init
c_func
(paren
id|vlan_proto_init
)paren
suffix:semicolon
DECL|variable|vlan_cleanup_module
id|module_exit
c_func
(paren
id|vlan_cleanup_module
)paren
suffix:semicolon
multiline_comment|/* Must be invoked with vlan_group_lock held. */
DECL|function|__vlan_find_group
r_static
r_struct
id|vlan_group
op_star
id|__vlan_find_group
c_func
(paren
r_int
id|real_dev_ifindex
)paren
(brace
r_struct
id|vlan_group
op_star
id|grp
suffix:semicolon
r_for
c_loop
(paren
id|grp
op_assign
id|vlan_group_hash
(braket
id|vlan_grp_hashfn
c_func
(paren
id|real_dev_ifindex
)paren
)braket
suffix:semicolon
id|grp
op_ne
l_int|NULL
suffix:semicolon
id|grp
op_assign
id|grp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|grp-&gt;real_dev_ifindex
op_eq
id|real_dev_ifindex
)paren
r_break
suffix:semicolon
)brace
r_return
id|grp
suffix:semicolon
)brace
multiline_comment|/* Must hold vlan_group_lock. */
DECL|function|__grp_hash
r_static
r_void
id|__grp_hash
c_func
(paren
r_struct
id|vlan_group
op_star
id|grp
)paren
(brace
r_struct
id|vlan_group
op_star
op_star
id|head
suffix:semicolon
id|head
op_assign
op_amp
id|vlan_group_hash
(braket
id|vlan_grp_hashfn
c_func
(paren
id|grp-&gt;real_dev_ifindex
)paren
)braket
suffix:semicolon
id|grp-&gt;next
op_assign
op_star
id|head
suffix:semicolon
op_star
id|head
op_assign
id|grp
suffix:semicolon
)brace
multiline_comment|/* Must hold vlan_group_lock. */
DECL|function|__grp_unhash
r_static
r_void
id|__grp_unhash
c_func
(paren
r_struct
id|vlan_group
op_star
id|grp
)paren
(brace
r_struct
id|vlan_group
op_star
id|next
comma
op_star
op_star
id|pprev
suffix:semicolon
id|pprev
op_assign
op_amp
id|vlan_group_hash
(braket
id|vlan_grp_hashfn
c_func
(paren
id|grp-&gt;real_dev_ifindex
)paren
)braket
suffix:semicolon
id|next
op_assign
op_star
id|pprev
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
id|grp
)paren
(brace
id|pprev
op_assign
op_amp
id|next-&gt;next
suffix:semicolon
id|next
op_assign
op_star
id|pprev
suffix:semicolon
)brace
op_star
id|pprev
op_assign
id|grp-&gt;next
suffix:semicolon
)brace
multiline_comment|/*  Find the protocol handler.  Assumes VID &lt; VLAN_VID_MASK.&n; *&n; * Must be invoked with vlan_group_lock held.&n; */
DECL|function|__find_vlan_dev
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
(brace
r_struct
id|vlan_group
op_star
id|grp
op_assign
id|__vlan_find_group
c_func
(paren
id|real_dev-&gt;ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|grp
)paren
r_return
id|grp-&gt;vlan_devices
(braket
id|VID
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* This returns 0 if everything went fine.&n; * It will return 1 if the group was killed as a result.&n; * A negative return indicates failure.&n; *&n; * The RTNL lock must be held.&n; */
DECL|function|unregister_vlan_dev
r_static
r_int
id|unregister_vlan_dev
c_func
(paren
r_struct
id|net_device
op_star
id|real_dev
comma
r_int
r_int
id|vlan_id
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|real_dev_ifindex
op_assign
id|real_dev-&gt;ifindex
suffix:semicolon
r_struct
id|vlan_group
op_star
id|grp
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: VID: %i&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|vlan_id
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|vlan_id
op_ge
id|VLAN_VID_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|grp
op_assign
id|__vlan_find_group
c_func
(paren
id|real_dev_ifindex
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|grp
)paren
(brace
id|dev
op_assign
id|grp-&gt;vlan_devices
(braket
id|vlan_id
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
multiline_comment|/* Remove proc entry */
id|vlan_proc_rem_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Take it out of our own structures, but be sure to&n;&t;&t;&t; * interlock with HW accelerating devices or SW vlan&n;&t;&t;&t; * input packet processing.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|real_dev-&gt;features
op_amp
(paren
id|NETIF_F_HW_VLAN_RX
op_or
id|NETIF_F_HW_VLAN_FILTER
)paren
)paren
(brace
id|real_dev
op_member_access_from_pointer
id|vlan_rx_kill_vid
c_func
(paren
id|real_dev
comma
id|vlan_id
)paren
suffix:semicolon
)brace
id|br_write_lock
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|grp-&gt;vlan_devices
(braket
id|vlan_id
)braket
op_assign
l_int|NULL
suffix:semicolon
id|br_write_unlock
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
multiline_comment|/* Caller unregisters (and if necessary, puts)&n;&t;&t;&t; * VLAN device, but we get rid of the reference to&n;&t;&t;&t; * real_dev here.&n;&t;&t;&t; */
id|dev_put
c_func
(paren
id|real_dev
)paren
suffix:semicolon
multiline_comment|/* If the group is now empty, kill off the&n;&t;&t;&t; * group.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VLAN_VID_MASK
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|grp-&gt;vlan_devices
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|VLAN_VID_MASK
)paren
(brace
r_if
c_cond
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_RX
)paren
id|real_dev
op_member_access_from_pointer
id|vlan_rx_register
c_func
(paren
id|real_dev
comma
l_int|NULL
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|__grp_unhash
c_func
(paren
id|grp
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|unregister_vlan_device
r_static
r_int
id|unregister_vlan_device
c_func
(paren
r_const
r_char
op_star
id|vlan_IF_name
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|dev
op_assign
id|dev_get_by_name
c_func
(paren
id|vlan_IF_name
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;priv_flags
op_amp
id|IFF_802_1Q_VLAN
)paren
(brace
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|unregister_vlan_dev
c_func
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|real_dev
comma
id|VLAN_DEV_INFO
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|vlan_id
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|1
)paren
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|VLAN_ERR
l_string|&quot;%s: ERROR:&t;Tried to remove a non-vlan device &quot;
l_string|&quot;with VLAN code, name: %s  priv_flags: %hX&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev-&gt;name
comma
id|dev-&gt;priv_flags
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
r_else
(brace
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: WARNING: Could not find dev.&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
macro_line|#endif
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*  Attach a VLAN device to a mac address (ie Ethernet Card).&n; *  Returns the device that was created, or NULL if there was&n; *  an error of some kind.&n; */
DECL|function|register_vlan_device
r_static
r_struct
id|net_device
op_star
id|register_vlan_device
c_func
(paren
r_const
r_char
op_star
id|eth_IF_name
comma
r_int
r_int
id|VLAN_ID
)paren
(brace
r_struct
id|vlan_group
op_star
id|grp
suffix:semicolon
r_struct
id|net_device
op_star
id|new_dev
suffix:semicolon
r_struct
id|net_device
op_star
id|real_dev
suffix:semicolon
multiline_comment|/* the ethernet device */
r_int
id|malloc_size
op_assign
l_int|0
suffix:semicolon
r_int
id|r
suffix:semicolon
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: if_name -:%s:-&t;vid: %i&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|eth_IF_name
comma
id|VLAN_ID
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|VLAN_ID
op_ge
id|VLAN_VID_MASK
)paren
r_goto
id|out_ret_null
suffix:semicolon
multiline_comment|/* find the device relating to eth_IF_name. */
id|real_dev
op_assign
id|dev_get_by_name
c_func
(paren
id|eth_IF_name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|real_dev
)paren
r_goto
id|out_ret_null
suffix:semicolon
r_if
c_cond
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_VLAN_CHALLENGED
)paren
(brace
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: VLANs not supported on %s.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|real_dev-&gt;name
)paren
suffix:semicolon
r_goto
id|out_put_dev
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_RX
)paren
op_logical_and
(paren
id|real_dev-&gt;vlan_rx_register
op_eq
l_int|NULL
op_logical_or
id|real_dev-&gt;vlan_rx_kill_vid
op_eq
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: Device %s has buggy VLAN hw accel.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|real_dev-&gt;name
)paren
suffix:semicolon
r_goto
id|out_put_dev
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_FILTER
)paren
op_logical_and
(paren
id|real_dev-&gt;vlan_rx_add_vid
op_eq
l_int|NULL
op_logical_or
id|real_dev-&gt;vlan_rx_kill_vid
op_eq
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: Device %s has buggy VLAN hw accel.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|real_dev-&gt;name
)paren
suffix:semicolon
r_goto
id|out_put_dev
suffix:semicolon
)brace
multiline_comment|/* From this point on, all the data structures must remain&n;&t; * consistent.&n;&t; */
id|rtnl_lock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* The real device must be up and operating in order to&n;&t; * assosciate a VLAN device with it.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|real_dev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|r
op_assign
(paren
id|__find_vlan_dev
c_func
(paren
id|real_dev
comma
id|VLAN_ID
)paren
op_ne
l_int|NULL
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
multiline_comment|/* was already registered. */
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: ALREADY had VLAN registered&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
id|malloc_size
op_assign
(paren
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
id|new_dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|kmalloc
c_func
(paren
id|malloc_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|VLAN_MEM_DBG
c_func
(paren
l_string|&quot;net_device malloc, addr: %p  size: %i&bslash;n&quot;
comma
id|new_dev
comma
id|malloc_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_dev
op_eq
l_int|NULL
)paren
r_goto
id|out_unlock
suffix:semicolon
id|memset
c_func
(paren
id|new_dev
comma
l_int|0
comma
id|malloc_size
)paren
suffix:semicolon
multiline_comment|/* Set us up to have no queue, as the underlying Hardware device&n;&t; * can do all the queueing we could want.&n;&t; */
id|new_dev-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Gotta set up the fields for the device. */
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;About to allocate name, vlan_name_type: %i&bslash;n&quot;
comma
id|vlan_name_type
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|vlan_name_type
)paren
(brace
r_case
id|VLAN_NAME_TYPE_RAW_PLUS_VID
suffix:colon
multiline_comment|/* name will look like:&t; eth1.0005 */
id|sprintf
c_func
(paren
id|new_dev-&gt;name
comma
l_string|&quot;%s.%.4i&quot;
comma
id|real_dev-&gt;name
comma
id|VLAN_ID
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VLAN_NAME_TYPE_PLUS_VID_NO_PAD
suffix:colon
multiline_comment|/* Put our vlan.VID in the name.&n;&t;&t; * Name will look like:&t; vlan5&n;&t;&t; */
id|sprintf
c_func
(paren
id|new_dev-&gt;name
comma
l_string|&quot;vlan%i&quot;
comma
id|VLAN_ID
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD
suffix:colon
multiline_comment|/* Put our vlan.VID in the name.&n;&t;&t; * Name will look like:&t; eth0.5&n;&t;&t; */
id|sprintf
c_func
(paren
id|new_dev-&gt;name
comma
l_string|&quot;%s.%i&quot;
comma
id|real_dev-&gt;name
comma
id|VLAN_ID
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VLAN_NAME_TYPE_PLUS_VID
suffix:colon
multiline_comment|/* Put our vlan.VID in the name.&n;&t;&t; * Name will look like:&t; vlan0005&n;&t;&t; */
r_default
suffix:colon
id|sprintf
c_func
(paren
id|new_dev-&gt;name
comma
l_string|&quot;vlan%.4i&quot;
comma
id|VLAN_ID
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;Allocated new name -:%s:-&bslash;n&quot;
comma
id|new_dev-&gt;name
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* set up method calls */
id|new_dev-&gt;init
op_assign
id|vlan_dev_init
suffix:semicolon
id|new_dev-&gt;destructor
op_assign
id|vlan_dev_destruct
suffix:semicolon
id|new_dev-&gt;features
op_or_assign
id|NETIF_F_DYNALLOC
suffix:semicolon
multiline_comment|/* new_dev-&gt;ifindex = 0;  it will be set when added to&n;&t; * the global list.&n;&t; * iflink is set as well.&n;&t; */
id|new_dev-&gt;get_stats
op_assign
id|vlan_dev_get_stats
suffix:semicolon
multiline_comment|/* IFF_BROADCAST|IFF_MULTICAST; ??? */
id|new_dev-&gt;flags
op_assign
id|real_dev-&gt;flags
suffix:semicolon
id|new_dev-&gt;flags
op_and_assign
op_complement
id|IFF_UP
suffix:semicolon
multiline_comment|/* Make this thing known as a VLAN device */
id|new_dev-&gt;priv_flags
op_or_assign
id|IFF_802_1Q_VLAN
suffix:semicolon
multiline_comment|/* need 4 bytes for extra VLAN header info,&n;&t; * hope the underlying device can handle it.&n;&t; */
id|new_dev-&gt;mtu
op_assign
id|real_dev-&gt;mtu
suffix:semicolon
id|new_dev-&gt;change_mtu
op_assign
id|vlan_dev_change_mtu
suffix:semicolon
multiline_comment|/* TODO: maybe just assign it to be ETHERNET? */
id|new_dev-&gt;type
op_assign
id|real_dev-&gt;type
suffix:semicolon
id|new_dev-&gt;hard_header_len
op_assign
id|real_dev-&gt;hard_header_len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_TX
)paren
)paren
(brace
multiline_comment|/* Regular ethernet + 4 bytes (18 total). */
id|new_dev-&gt;hard_header_len
op_add_assign
id|VLAN_HLEN
suffix:semicolon
)brace
id|new_dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vlan_dev_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|VLAN_MEM_DBG
c_func
(paren
l_string|&quot;new_dev-&gt;priv malloc, addr: %p  size: %i&bslash;n&quot;
comma
id|new_dev-&gt;priv
comma
r_sizeof
(paren
r_struct
id|vlan_dev_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_dev-&gt;priv
op_eq
l_int|NULL
)paren
r_goto
id|out_free_newdev
suffix:semicolon
id|memset
c_func
(paren
id|new_dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vlan_dev_info
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|new_dev-&gt;broadcast
comma
id|real_dev-&gt;broadcast
comma
id|real_dev-&gt;addr_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|new_dev-&gt;dev_addr
comma
id|real_dev-&gt;dev_addr
comma
id|real_dev-&gt;addr_len
)paren
suffix:semicolon
id|new_dev-&gt;addr_len
op_assign
id|real_dev-&gt;addr_len
suffix:semicolon
id|new_dev-&gt;open
op_assign
id|vlan_dev_open
suffix:semicolon
id|new_dev-&gt;stop
op_assign
id|vlan_dev_stop
suffix:semicolon
r_if
c_cond
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_TX
)paren
(brace
id|new_dev-&gt;hard_header
op_assign
id|real_dev-&gt;hard_header
suffix:semicolon
id|new_dev-&gt;hard_start_xmit
op_assign
id|vlan_dev_hwaccel_hard_start_xmit
suffix:semicolon
id|new_dev-&gt;rebuild_header
op_assign
id|real_dev-&gt;rebuild_header
suffix:semicolon
)brace
r_else
(brace
id|new_dev-&gt;hard_header
op_assign
id|vlan_dev_hard_header
suffix:semicolon
id|new_dev-&gt;hard_start_xmit
op_assign
id|vlan_dev_hard_start_xmit
suffix:semicolon
id|new_dev-&gt;rebuild_header
op_assign
id|vlan_dev_rebuild_header
suffix:semicolon
)brace
id|new_dev-&gt;hard_header_parse
op_assign
id|real_dev-&gt;hard_header_parse
suffix:semicolon
id|new_dev-&gt;set_mac_address
op_assign
id|vlan_dev_set_mac_address
suffix:semicolon
id|new_dev-&gt;set_multicast_list
op_assign
id|vlan_dev_set_multicast_list
suffix:semicolon
id|VLAN_DEV_INFO
c_func
(paren
id|new_dev
)paren
op_member_access_from_pointer
id|vlan_id
op_assign
id|VLAN_ID
suffix:semicolon
multiline_comment|/* 1 through VLAN_VID_MASK */
id|VLAN_DEV_INFO
c_func
(paren
id|new_dev
)paren
op_member_access_from_pointer
id|real_dev
op_assign
id|real_dev
suffix:semicolon
id|VLAN_DEV_INFO
c_func
(paren
id|new_dev
)paren
op_member_access_from_pointer
id|dent
op_assign
l_int|NULL
suffix:semicolon
id|VLAN_DEV_INFO
c_func
(paren
id|new_dev
)paren
op_member_access_from_pointer
id|flags
op_assign
id|vlan_default_dev_flags
suffix:semicolon
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;About to go find the group for idx: %i&bslash;n&quot;
comma
id|real_dev-&gt;ifindex
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* So, got the sucker initialized, now lets place&n;&t; * it into our local structure.&n;&t; */
id|spin_lock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|grp
op_assign
id|__vlan_find_group
c_func
(paren
id|real_dev-&gt;ifindex
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
multiline_comment|/* Note, we are running under the RTNL semaphore&n;&t; * so it cannot &quot;appear&quot; on us.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|grp
)paren
(brace
multiline_comment|/* need to add a new group */
id|grp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|vlan_group
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|grp
)paren
r_goto
id|out_free_newdev_priv
suffix:semicolon
multiline_comment|/* printk(KERN_ALERT &quot;VLAN REGISTER:  Allocated new group.&bslash;n&quot;); */
id|memset
c_func
(paren
id|grp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vlan_group
)paren
)paren
suffix:semicolon
id|grp-&gt;real_dev_ifindex
op_assign
id|real_dev-&gt;ifindex
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|__grp_hash
c_func
(paren
id|grp
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_RX
)paren
id|real_dev
op_member_access_from_pointer
id|vlan_rx_register
c_func
(paren
id|real_dev
comma
id|grp
)paren
suffix:semicolon
)brace
id|grp-&gt;vlan_devices
(braket
id|VLAN_ID
)braket
op_assign
id|new_dev
suffix:semicolon
id|vlan_proc_add_dev
c_func
(paren
id|new_dev
)paren
suffix:semicolon
multiline_comment|/* create it&squot;s proc entry */
r_if
c_cond
(paren
id|real_dev-&gt;features
op_amp
id|NETIF_F_HW_VLAN_FILTER
)paren
id|real_dev
op_member_access_from_pointer
id|vlan_rx_add_vid
c_func
(paren
id|real_dev
comma
id|VLAN_ID
)paren
suffix:semicolon
id|register_netdevice
c_func
(paren
id|new_dev
)paren
suffix:semicolon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTE:  We have a reference to the real device,&n;&t; * so hold on to the reference.&n;&t; */
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* Add was a success!! */
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;Allocated new device successfully, returning.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|new_dev
suffix:semicolon
id|out_free_newdev_priv
suffix:colon
id|kfree
c_func
(paren
id|new_dev-&gt;priv
)paren
suffix:semicolon
id|out_free_newdev
suffix:colon
id|kfree
c_func
(paren
id|new_dev
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|rtnl_unlock
c_func
(paren
)paren
suffix:semicolon
id|out_put_dev
suffix:colon
id|dev_put
c_func
(paren
id|real_dev
)paren
suffix:semicolon
id|out_ret_null
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|vlan_device_event
r_static
r_int
id|vlan_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|unused
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
(paren
id|ptr
)paren
suffix:semicolon
r_struct
id|vlan_group
op_star
id|grp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|flgs
suffix:semicolon
r_struct
id|net_device
op_star
id|vlandev
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
id|grp
op_assign
id|__vlan_find_group
c_func
(paren
id|dev-&gt;ifindex
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|vlan_group_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|grp
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* It is OK that we do not hold the group lock right now,&n;&t; * as we run under the RTNL lock.&n;&t; */
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_CHANGEADDR
suffix:colon
r_case
id|NETDEV_GOING_DOWN
suffix:colon
multiline_comment|/* Ignore for now */
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
multiline_comment|/* Put all VLANs for this dev in the down state too.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VLAN_GROUP_ARRAY_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vlandev
op_assign
id|grp-&gt;vlan_devices
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vlandev
)paren
r_continue
suffix:semicolon
id|flgs
op_assign
id|vlandev-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flgs
op_amp
id|IFF_UP
)paren
)paren
r_continue
suffix:semicolon
id|dev_change_flags
c_func
(paren
id|vlandev
comma
id|flgs
op_amp
op_complement
id|IFF_UP
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UP
suffix:colon
multiline_comment|/* Put all VLANs for this dev in the up state too.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VLAN_GROUP_ARRAY_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vlandev
op_assign
id|grp-&gt;vlan_devices
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vlandev
)paren
r_continue
suffix:semicolon
id|flgs
op_assign
id|vlandev-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
id|flgs
op_amp
id|IFF_UP
)paren
r_continue
suffix:semicolon
id|dev_change_flags
c_func
(paren
id|vlandev
comma
id|flgs
op_or
id|IFF_UP
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UNREGISTER
suffix:colon
multiline_comment|/* Delete all VLANs for this dev. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|VLAN_GROUP_ARRAY_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|ret
suffix:semicolon
id|vlandev
op_assign
id|grp-&gt;vlan_devices
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vlandev
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|unregister_vlan_dev
c_func
(paren
id|dev
comma
id|VLAN_DEV_INFO
c_func
(paren
id|vlandev
)paren
op_member_access_from_pointer
id|vlan_id
)paren
suffix:semicolon
id|unregister_netdevice
c_func
(paren
id|vlandev
)paren
suffix:semicolon
multiline_comment|/* Group was destroyed? */
r_if
c_cond
(paren
id|ret
op_eq
l_int|1
)paren
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
suffix:semicolon
id|out
suffix:colon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;VLAN IOCTL handler.&n; *&t;o execute requested action or pass command to the device driver&n; *   arg is really a void* to a vlan_ioctl_args structure.&n; */
DECL|function|vlan_ioctl_handler
r_int
id|vlan_ioctl_handler
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|vlan_ioctl_args
id|args
suffix:semicolon
multiline_comment|/* everything here needs root permissions, except aguably the&n;&t; * hack ioctls for sending packets.  However, I know _I_ don&squot;t&n;&t; * want users running that on my network! --BLG&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|args
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|vlan_ioctl_args
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Null terminate this sucker, just in case. */
id|args.device1
(braket
l_int|23
)braket
op_assign
l_int|0
suffix:semicolon
id|args.u.device2
(braket
l_int|23
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: args.cmd: %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|args.cmd
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|args.cmd
)paren
(brace
r_case
id|SET_VLAN_INGRESS_PRIORITY_CMD
suffix:colon
id|err
op_assign
id|vlan_dev_set_ingress_priority
c_func
(paren
id|args.device1
comma
id|args.u.skb_priority
comma
id|args.vlan_qos
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SET_VLAN_EGRESS_PRIORITY_CMD
suffix:colon
id|err
op_assign
id|vlan_dev_set_egress_priority
c_func
(paren
id|args.device1
comma
id|args.u.skb_priority
comma
id|args.vlan_qos
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SET_VLAN_FLAG_CMD
suffix:colon
id|err
op_assign
id|vlan_dev_set_vlan_flag
c_func
(paren
id|args.device1
comma
id|args.u.flag
comma
id|args.vlan_qos
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SET_VLAN_NAME_TYPE_CMD
suffix:colon
r_if
c_cond
(paren
(paren
id|args.u.name_type
op_ge
l_int|0
)paren
op_logical_and
(paren
id|args.u.name_type
OL
id|VLAN_NAME_TYPE_HIGHEST
)paren
)paren
(brace
id|vlan_name_type
op_assign
id|args.u.name_type
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* TODO:  Figure out how to pass info back...&n;&t;&t;   case GET_VLAN_INGRESS_PRIORITY_IOCTL:&n;&t;&t;   err = vlan_dev_get_ingress_priority(args);&n;&t;&t;   break;&n;&n;&t;&t;   case GET_VLAN_EGRESS_PRIORITY_IOCTL:&n;&t;&t;   err = vlan_dev_get_egress_priority(args);&n;&t;&t;   break;&n;&t;&t;*/
r_case
id|ADD_VLAN_CMD
suffix:colon
multiline_comment|/* we have been given the name of the Ethernet Device we want to&n;&t;&t; * talk to:  args.dev1&t; We also have the&n;&t;&t; * VLAN ID:  args.u.VID&n;&t;&t; */
r_if
c_cond
(paren
id|register_vlan_device
c_func
(paren
id|args.device1
comma
id|args.u.VID
)paren
)paren
(brace
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DEL_VLAN_CMD
suffix:colon
multiline_comment|/* Here, the args.dev1 is the actual VLAN we want&n;&t;&t; * to get rid of.&n;&t;&t; */
id|err
op_assign
id|unregister_vlan_device
c_func
(paren
id|args.device1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* pass on to underlying device instead?? */
id|printk
c_func
(paren
id|VLAN_DBG
l_string|&quot;%s: Unknown VLAN CMD: %x &bslash;n&quot;
comma
id|__FUNCTION__
comma
id|args.cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
