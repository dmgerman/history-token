multiline_comment|/*&n; * Bond several ethernet interfaces into a Cisco, running &squot;Etherchannel&squot;.&n; *&n; * Portions are (c) Copyright 1995 Simon &quot;Guru Aleph-Null&quot; Janes&n; * NCM: Network and Communications Management, Inc.&n; *&n; * BUT, I&squot;m the one who modified it for ethernet, so:&n; * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov&n; *&n; *&t;This software may be used and distributed according to the terms&n; *&t;of the GNU Public License, incorporated herein by reference.&n; * &n; *&n; * 2003/03/18 - Amir Noam &lt;amir.noam at intel dot com&gt;,&n; *&t;&t;Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Added support for IEEE 802.3ad Dynamic link aggregation mode.&n; *&n; * 2003/05/01 - Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Amir Noam &lt;amir.noam at intel dot com&gt;&n; *&t;- Code beautification and style changes (mainly in comments).&n; *&n; * 2003/05/01 - Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Added support for Transmit load balancing mode.&n; */
macro_line|#ifndef _LINUX_BONDING_H
DECL|macro|_LINUX_BONDING_H
mdefine_line|#define _LINUX_BONDING_H
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;bond_3ad.h&quot;
macro_line|#include &quot;bond_alb.h&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;2.4.1&quot;
DECL|macro|DRV_RELDATE
mdefine_line|#define DRV_RELDATE&t;&quot;September 15, 2003&quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;bonding&quot;
DECL|macro|DRV_DESCRIPTION
mdefine_line|#define DRV_DESCRIPTION&t;&quot;Ethernet Channel Bonding Driver&quot;
macro_line|#ifdef BONDING_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, args...) &bslash;&n;&t;printk(KERN_DEBUG     &bslash;&n;&t;       DRV_NAME &quot;: %s() %d: &quot; fmt, __FUNCTION__, __LINE__ , ## args )
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, args...)
macro_line|#endif /* BONDING_DEBUG */
DECL|macro|IS_UP
mdefine_line|#define IS_UP(dev)  ((((dev)-&gt;flags &amp; (IFF_UP)) == (IFF_UP)) &amp;&amp; &bslash;&n;&t;&t;     (netif_running(dev) &amp;&amp; netif_carrier_ok(dev)))
multiline_comment|/* Checks whether the dev is ready for transmit. We do not check netif_running&n; * since a device can be stopped by the driver for short periods of time for&n; * maintainance. dev_queue_xmit() handles this by queing the packet until the&n; * the dev is running again. Keeping packets ordering requires sticking the&n; * same dev as much as possible&n; */
DECL|macro|SLAVE_IS_OK
mdefine_line|#define SLAVE_IS_OK(slave) &bslash;&n;&t;&t;     ((((slave)-&gt;dev-&gt;flags &amp; (IFF_UP)) == (IFF_UP)) &amp;&amp; &bslash;&n;&t;&t;     netif_carrier_ok((slave)-&gt;dev) &amp;&amp; &bslash;&n;&t;&t;     ((slave)-&gt;link == BOND_LINK_UP) &amp;&amp; &bslash;&n;&t;&t;     ((slave)-&gt;state == BOND_STATE_ACTIVE))
DECL|struct|slave
r_typedef
r_struct
id|slave
(brace
DECL|member|next
r_struct
id|slave
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|slave
op_star
id|prev
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|delay
r_int
id|delay
suffix:semicolon
DECL|member|jiffies
r_int
r_int
id|jiffies
suffix:semicolon
DECL|member|link
r_char
id|link
suffix:semicolon
multiline_comment|/* one of BOND_LINK_XXXX */
DECL|member|state
r_char
id|state
suffix:semicolon
multiline_comment|/* one of BOND_STATE_XXXX */
DECL|member|original_flags
r_int
r_int
id|original_flags
suffix:semicolon
DECL|member|link_failure_count
id|u32
id|link_failure_count
suffix:semicolon
DECL|member|speed
id|u16
id|speed
suffix:semicolon
DECL|member|duplex
id|u8
id|duplex
suffix:semicolon
DECL|member|perm_hwaddr
id|u8
id|perm_hwaddr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|ad_info
r_struct
id|ad_slave_info
id|ad_info
suffix:semicolon
multiline_comment|/* HUGE - better to dynamically alloc */
DECL|member|tlb_info
r_struct
id|tlb_slave_info
id|tlb_info
suffix:semicolon
DECL|typedef|slave_t
)brace
id|slave_t
suffix:semicolon
multiline_comment|/*&n; * Here are the locking policies for the two bonding locks:&n; *&n; * 1) Get bond-&gt;lock when reading/writing slave list.&n; * 2) Get bond-&gt;ptrlock when reading/writing bond-&gt;current_slave.&n; *    (It is unnecessary when the write-lock is put with bond-&gt;lock.)&n; * 3) When we lock with bond-&gt;ptrlock, we must lock with bond-&gt;lock&n; *    beforehand.&n; */
DECL|struct|bonding
r_typedef
r_struct
id|bonding
(brace
DECL|member|next
id|slave_t
op_star
id|next
suffix:semicolon
DECL|member|prev
id|slave_t
op_star
id|prev
suffix:semicolon
DECL|member|current_slave
id|slave_t
op_star
id|current_slave
suffix:semicolon
DECL|member|primary_slave
id|slave_t
op_star
id|primary_slave
suffix:semicolon
DECL|member|current_arp_slave
id|slave_t
op_star
id|current_arp_slave
suffix:semicolon
DECL|member|slave_cnt
id|__s32
id|slave_cnt
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|ptrlock
id|rwlock_t
id|ptrlock
suffix:semicolon
DECL|member|mii_timer
r_struct
id|timer_list
id|mii_timer
suffix:semicolon
DECL|member|arp_timer
r_struct
id|timer_list
id|arp_timer
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|bond_proc_file
r_struct
id|proc_dir_entry
op_star
id|bond_proc_file
suffix:semicolon
DECL|member|procdir_name
r_char
id|procdir_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
DECL|member|bond_list
r_struct
id|list_head
id|bond_list
suffix:semicolon
DECL|member|device
r_struct
id|net_device
op_star
id|device
suffix:semicolon
DECL|member|mc_list
r_struct
id|dev_mc_list
op_star
id|mc_list
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ad_info
r_struct
id|ad_bond_info
id|ad_info
suffix:semicolon
DECL|member|alb_info
r_struct
id|alb_bond_info
id|alb_info
suffix:semicolon
DECL|typedef|bonding_t
)brace
id|bonding_t
suffix:semicolon
multiline_comment|/* Forward declarations */
r_void
id|bond_set_slave_active_flags
c_func
(paren
id|slave_t
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_set_slave_inactive_flags
c_func
(paren
id|slave_t
op_star
id|slave
)paren
suffix:semicolon
multiline_comment|/**&n; * These functions can be used for iterating the slave list&n; * (which is circular)&n; * Caller must hold bond lock for read&n; */
r_extern
r_inline
r_struct
id|slave
op_star
DECL|function|bond_get_first_slave
id|bond_get_first_slave
c_func
(paren
r_struct
id|bonding
op_star
id|bond
)paren
(brace
multiline_comment|/* if there are no slaves return NULL */
r_if
c_cond
(paren
id|bond-&gt;next
op_eq
(paren
id|slave_t
op_star
)paren
id|bond
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|bond-&gt;next
suffix:semicolon
)brace
multiline_comment|/**&n; * Caller must hold bond lock for read&n; */
r_extern
r_inline
r_struct
id|slave
op_star
DECL|function|bond_get_next_slave
id|bond_get_next_slave
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|slave
op_star
id|slave
)paren
(brace
multiline_comment|/* If we have reached the last slave return NULL */
r_if
c_cond
(paren
id|slave-&gt;next
op_eq
id|bond-&gt;next
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|slave-&gt;next
suffix:semicolon
)brace
multiline_comment|/**&n; * Returns NULL if the net_device does not belong to any of the bond&squot;s slaves&n; *&n; * Caller must hold bond lock for read&n; */
r_extern
r_inline
r_struct
id|slave
op_star
DECL|function|bond_get_slave_by_dev
id|bond_get_slave_by_dev
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|net_device
op_star
id|slave_dev
)paren
(brace
r_struct
id|slave
op_star
id|our_slave
op_assign
id|bond-&gt;next
suffix:semicolon
multiline_comment|/* check if the list of slaves is empty */
r_if
c_cond
(paren
id|our_slave
op_eq
(paren
id|slave_t
op_star
)paren
id|bond
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|our_slave
suffix:semicolon
id|our_slave
op_assign
id|bond_get_next_slave
c_func
(paren
id|bond
comma
id|our_slave
)paren
)paren
(brace
r_if
c_cond
(paren
id|our_slave-&gt;dev
op_eq
id|slave_dev
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
id|our_slave
suffix:semicolon
)brace
r_extern
r_inline
r_struct
id|bonding
op_star
DECL|function|bond_get_bond_by_slave
id|bond_get_bond_by_slave
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|slave
op_logical_or
op_logical_neg
id|slave-&gt;dev-&gt;master
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
r_struct
id|bonding
op_star
)paren
(paren
id|slave-&gt;dev-&gt;master-&gt;priv
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_BONDING_H */
eof
