multiline_comment|/*&n; * INET&t;&t;802.1Q VLAN&n; *&t;&t;Ethernet-type device handling.&n; *&n; * Authors:&t;Ben Greear &lt;greearb@candelatech.com&gt;&n; *              Please send support related email to: vlan@scry.wanfear.com&n; *              VLAN Home Page: http://www.candelatech.com/~greear/vlan.html&n; * &n; * Fixes:&n; *              Fix for packet capture - Nick Eggleston &lt;nick@dccinc.com&gt;;&n; *&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
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
DECL|variable|p802_1Q_vlan_list
r_struct
id|vlan_group
op_star
id|p802_1Q_vlan_list
suffix:semicolon
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
l_int|6
suffix:semicolon
DECL|variable|vlan_copyright
r_static
r_char
id|vlan_copyright
(braket
)braket
op_assign
l_string|&quot; Ben Greear &lt;greearb@candelatech.com&gt;&quot;
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
id|notifier_call
suffix:colon
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
multiline_comment|/* Counter for how many NON-VLAN protos we&squot;ve received on a VLAN. */
DECL|variable|vlan_bad_proto_recvd
r_int
r_int
id|vlan_bad_proto_recvd
op_assign
l_int|0
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
id|type
suffix:colon
id|__constant_htons
c_func
(paren
id|ETH_P_8021Q
)paren
comma
id|dev
suffix:colon
l_int|NULL
comma
id|func
suffix:colon
id|vlan_skb_recv
comma
multiline_comment|/* VLAN receive method */
id|data
suffix:colon
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
id|next
suffix:colon
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
id|__FUNCTION__
l_string|&quot;%s: can&squot;t create entry in proc filesystem!&bslash;n&quot;
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
id|printk
c_func
(paren
id|VLAN_INF
l_string|&quot;%s Initialization complete.&bslash;n&quot;
comma
id|VLAN_NAME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Cleanup of groups before exit&n; */
DECL|function|vlan_group_cleanup
r_static
r_void
id|vlan_group_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|vlan_group
op_star
id|grp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|vlan_group
op_star
id|nextgroup
suffix:semicolon
r_for
c_loop
(paren
id|grp
op_assign
id|p802_1Q_vlan_list
suffix:semicolon
(paren
id|grp
op_ne
l_int|NULL
)paren
suffix:semicolon
)paren
(brace
id|nextgroup
op_assign
id|grp-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|grp
)paren
suffix:semicolon
id|grp
op_assign
id|nextgroup
suffix:semicolon
)brace
id|p802_1Q_vlan_list
op_assign
l_int|NULL
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
id|vlan_group_cleanup
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
multiline_comment|/**  Will search linearly for now, based on device index.  Could&n; * hash, or directly link, this some day. --Ben&n; * TODO:  Potential performance issue here.  Linear search where N is&n; *        the number of &squot;real&squot; devices used by VLANs.&n; */
DECL|function|vlan_find_group
r_struct
id|vlan_group
op_star
id|vlan_find_group
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
op_assign
l_int|NULL
suffix:semicolon
id|br_read_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_for
c_loop
(paren
id|grp
op_assign
id|p802_1Q_vlan_list
suffix:semicolon
(paren
(paren
id|grp
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|grp-&gt;real_dev_ifindex
op_ne
id|real_dev_ifindex
)paren
)paren
suffix:semicolon
id|grp
op_assign
id|grp-&gt;next
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|br_read_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
r_return
id|grp
suffix:semicolon
)brace
multiline_comment|/*  Find the protocol handler.  Assumes VID &lt; 0xFFF.&n; */
DECL|function|find_802_1Q_vlan_dev
r_struct
id|net_device
op_star
id|find_802_1Q_vlan_dev
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
id|vlan_find_group
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
multiline_comment|/** This method will explicitly do a dev_put on the device if do_dev_put&n; * is TRUE.  This gets around a difficulty with reference counting, and&n; * the unregister-by-name (below).  If do_locks is true, it will grab&n; * a lock before un-registering.  If do_locks is false, it is assumed that&n; * the lock has already been grabbed externally...  --Ben&n; */
DECL|function|unregister_802_1Q_vlan_dev
r_int
id|unregister_802_1Q_vlan_dev
c_func
(paren
r_int
id|real_dev_ifindex
comma
r_int
r_int
id|vlan_id
comma
r_int
id|do_dev_put
comma
r_int
id|do_locks
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|vlan_group
op_star
id|grp
suffix:semicolon
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
id|__FUNCTION__
l_string|&quot;: VID: %i&bslash;n&quot;
comma
id|vlan_id
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* sanity check */
r_if
c_cond
(paren
(paren
id|vlan_id
op_ge
l_int|0xFFF
)paren
op_logical_or
(paren
id|vlan_id
op_le
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|grp
op_assign
id|vlan_find_group
c_func
(paren
id|real_dev_ifindex
)paren
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
multiline_comment|/* Take it out of our own structures */
id|grp-&gt;vlan_devices
(braket
id|vlan_id
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Take it out of the global list of devices.&n;&t;&t;&t; *  NOTE:  This deletes dev, don&squot;t access it again!!&n;&t;&t;&t; */
r_if
c_cond
(paren
id|do_dev_put
)paren
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* TODO:  Please review this code. */
r_if
c_cond
(paren
id|do_locks
)paren
(brace
id|rtnl_lock
c_func
(paren
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
)brace
r_else
(brace
id|unregister_netdevice
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_802_1Q_vlan_device
r_int
id|unregister_802_1Q_vlan_device
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
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
id|__FUNCTION__
l_string|&quot;: unregister VLAN by name, name -:%s:-&bslash;n&quot;
comma
id|vlan_IF_name
)paren
suffix:semicolon
macro_line|#endif
id|dev
op_assign
id|dev_get_by_name
c_func
(paren
id|vlan_IF_name
)paren
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
r_return
id|unregister_802_1Q_vlan_dev
c_func
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|real_dev-&gt;ifindex
comma
(paren
r_int
r_int
)paren
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|dev
)paren
op_member_access_from_pointer
id|vlan_id
)paren
comma
l_int|1
multiline_comment|/* do dev_put */
comma
l_int|1
multiline_comment|/* do locking */
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|VLAN_ERR
id|__FUNCTION__
l_string|&quot;: ERROR:&t;Tried to remove a non-vlan device &quot;
l_string|&quot;with VLAN code, name: %s  priv_flags: %hX&bslash;n&quot;
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
r_return
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
id|__FUNCTION__
l_string|&quot;: WARNING: Could not find dev.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*  Attach a VLAN device to a mac address (ie Ethernet Card).&n; *  Returns the device that was created, or NULL if there was&n; *  an error of some kind.&n; */
DECL|function|register_802_1Q_vlan_device
r_struct
id|net_device
op_star
id|register_802_1Q_vlan_device
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
macro_line|#ifdef VLAN_DEBUG
id|printk
c_func
(paren
id|VLAN_DBG
id|__FUNCTION__
l_string|&quot;: if_name -:%s:-&t;vid: %i&bslash;n&quot;
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
l_int|0xfff
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
multiline_comment|/* TODO:  Make sure this device can really handle having a VLAN attached&n;&t; * to it...&n;&t; */
r_if
c_cond
(paren
id|find_802_1Q_vlan_dev
c_func
(paren
id|real_dev
comma
id|VLAN_ID
)paren
)paren
(brace
multiline_comment|/* was already registered. */
id|printk
c_func
(paren
id|VLAN_DBG
id|__FUNCTION__
l_string|&quot;: ALREADY had VLAN registered&bslash;n&quot;
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|real_dev
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|out_put_dev
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
multiline_comment|/* set us up to not use a Qdisc, as the underlying Hardware device&n;&t; * can do all the queueing we could want.&n;&t; */
multiline_comment|/* new_dev-&gt;qdisc_sleeping = &amp;noqueue_qdisc;   Not needed it seems. */
id|new_dev-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This should effectively give us no queue. */
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
multiline_comment|/* Regular ethernet + 4 bytes (18 total). */
id|new_dev-&gt;hard_header_len
op_assign
id|VLAN_HLEN
op_plus
id|real_dev-&gt;hard_header_len
suffix:semicolon
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
(brace
id|kfree
c_func
(paren
id|new_dev
)paren
suffix:semicolon
r_goto
id|out_put_dev
suffix:semicolon
)brace
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
multiline_comment|/* 1 through 0xFFF */
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
id|grp
op_assign
id|vlan_find_group
c_func
(paren
id|real_dev-&gt;ifindex
)paren
suffix:semicolon
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
id|VLAN_MEM_DBG
c_func
(paren
l_string|&quot;grp malloc, addr: %p  size: %i&bslash;n&quot;
comma
id|grp
comma
r_sizeof
(paren
r_struct
id|vlan_group
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|grp
)paren
(brace
id|kfree
c_func
(paren
id|new_dev-&gt;priv
)paren
suffix:semicolon
id|VLAN_FMEM_DBG
c_func
(paren
l_string|&quot;new_dev-&gt;priv free, addr: %p&bslash;n&quot;
comma
id|new_dev-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|new_dev
)paren
suffix:semicolon
id|VLAN_FMEM_DBG
c_func
(paren
l_string|&quot;new_dev free, addr: %p&bslash;n&quot;
comma
id|new_dev
)paren
suffix:semicolon
r_goto
id|out_put_dev
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;VLAN REGISTER:  Allocated new group.&bslash;n&quot;
)paren
suffix:semicolon
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
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|grp-&gt;next
op_assign
id|p802_1Q_vlan_list
suffix:semicolon
id|p802_1Q_vlan_list
op_assign
id|grp
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
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
multiline_comment|/* TODO: Please check this: RTNL   --Ben */
id|rtnl_lock
c_func
(paren
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
op_assign
l_int|0
suffix:semicolon
r_struct
id|net_device
op_star
id|vlandev
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|NETDEV_CHANGEADDR
suffix:colon
multiline_comment|/* Ignore for now */
r_break
suffix:semicolon
r_case
id|NETDEV_GOING_DOWN
suffix:colon
multiline_comment|/* Ignore for now */
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
multiline_comment|/* TODO:  Please review this code. */
multiline_comment|/* put all related VLANs in the down state too. */
r_for
c_loop
(paren
id|grp
op_assign
id|p802_1Q_vlan_list
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
r_int
id|flgs
op_assign
l_int|0
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
op_logical_or
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|vlandev
)paren
op_member_access_from_pointer
id|real_dev
op_ne
id|dev
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|vlandev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
)paren
r_continue
suffix:semicolon
id|flgs
op_assign
id|vlandev-&gt;flags
suffix:semicolon
id|flgs
op_and_assign
op_complement
id|IFF_UP
suffix:semicolon
id|dev_change_flags
c_func
(paren
id|vlandev
comma
id|flgs
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UP
suffix:colon
multiline_comment|/* TODO:  Please review this code. */
multiline_comment|/* put all related VLANs in the down state too. */
r_for
c_loop
(paren
id|grp
op_assign
id|p802_1Q_vlan_list
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
r_int
id|flgs
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
op_logical_or
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|vlandev
)paren
op_member_access_from_pointer
id|real_dev
op_ne
id|dev
)paren
op_logical_or
(paren
id|vlandev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
r_continue
suffix:semicolon
id|flgs
op_assign
id|vlandev-&gt;flags
suffix:semicolon
id|flgs
op_or_assign
id|IFF_UP
suffix:semicolon
id|dev_change_flags
c_func
(paren
id|vlandev
comma
id|flgs
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UNREGISTER
suffix:colon
multiline_comment|/* TODO:  Please review this code. */
multiline_comment|/* delete all related VLANs. */
r_for
c_loop
(paren
id|grp
op_assign
id|p802_1Q_vlan_list
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
op_logical_or
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|vlandev
)paren
op_member_access_from_pointer
id|real_dev
op_ne
id|dev
)paren
)paren
r_continue
suffix:semicolon
id|unregister_802_1Q_vlan_dev
c_func
(paren
id|VLAN_DEV_INFO
c_func
(paren
id|vlandev
)paren
op_member_access_from_pointer
id|real_dev-&gt;ifindex
comma
id|VLAN_DEV_INFO
c_func
(paren
id|vlandev
)paren
op_member_access_from_pointer
id|vlan_id
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|vlandev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
suffix:semicolon
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
id|__FUNCTION__
l_string|&quot;: args.cmd: %x&bslash;n&quot;
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
id|register_802_1Q_vlan_device
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
id|unregister_802_1Q_vlan_device
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
id|__FUNCTION__
l_string|&quot;: Unknown VLAN CMD: %x &bslash;n&quot;
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
eof
