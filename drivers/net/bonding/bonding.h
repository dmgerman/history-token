multiline_comment|/*&n; * Bond several ethernet interfaces into a Cisco, running &squot;Etherchannel&squot;.&n; *&n; * Portions are (c) Copyright 1995 Simon &quot;Guru Aleph-Null&quot; Janes&n; * NCM: Network and Communications Management, Inc.&n; *&n; * BUT, I&squot;m the one who modified it for ethernet, so:&n; * (c) Copyright 1999, Thomas Davis, tadavis@lbl.gov&n; *&n; *&t;This software may be used and distributed according to the terms&n; *&t;of the GNU Public License, incorporated herein by reference.&n; *&n; *&n; * 2003/03/18 - Amir Noam &lt;amir.noam at intel dot com&gt;,&n; *&t;&t;Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Added support for IEEE 802.3ad Dynamic link aggregation mode.&n; *&n; * 2003/05/01 - Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Amir Noam &lt;amir.noam at intel dot com&gt;&n; *&t;- Code beautification and style changes (mainly in comments).&n; *&n; * 2003/05/01 - Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Added support for Transmit load balancing mode.&n; *&n; * 2003/09/24 - Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Code cleanup and style changes&n; */
macro_line|#ifndef _LINUX_BONDING_H
DECL|macro|_LINUX_BONDING_H
mdefine_line|#define _LINUX_BONDING_H
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/if_bonding.h&gt;
macro_line|#include &quot;bond_3ad.h&quot;
macro_line|#include &quot;bond_alb.h&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;2.5.0&quot;
DECL|macro|DRV_RELDATE
mdefine_line|#define DRV_RELDATE&t;&quot;December 1, 2003&quot;
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
mdefine_line|#define IS_UP(dev)&t;&t;&t;&t;&t;   &bslash;&n;&t;      ((((dev)-&gt;flags &amp; IFF_UP) == IFF_UP)&t;&amp;&amp; &bslash;&n;&t;       netif_running(dev)&t;&t;&t;&amp;&amp; &bslash;&n;&t;       netif_carrier_ok(dev))
multiline_comment|/*&n; * Checks whether bond is ready for transmit.&n; *&n; * Caller must hold bond-&gt;lock&n; */
DECL|macro|BOND_IS_OK
mdefine_line|#define BOND_IS_OK(bond)&t;&t;&t;     &bslash;&n;&t;&t;   (((bond)-&gt;dev-&gt;flags &amp; IFF_UP) &amp;&amp; &bslash;&n;&t;&t;    netif_running((bond)-&gt;dev)&t;  &amp;&amp; &bslash;&n;&t;&t;    ((bond)-&gt;slave_cnt &gt; 0))
multiline_comment|/*&n; * Checks whether slave is ready for transmit.&n; */
DECL|macro|SLAVE_IS_OK
mdefine_line|#define SLAVE_IS_OK(slave)&t;&t;&t;        &bslash;&n;&t;&t;    (((slave)-&gt;dev-&gt;flags &amp; IFF_UP)  &amp;&amp; &bslash;&n;&t;&t;     netif_running((slave)-&gt;dev)     &amp;&amp; &bslash;&n;&t;&t;     ((slave)-&gt;link == BOND_LINK_UP) &amp;&amp; &bslash;&n;&t;&t;     ((slave)-&gt;state == BOND_STATE_ACTIVE))
DECL|macro|USES_PRIMARY
mdefine_line|#define USES_PRIMARY(mode)&t;&t;&t;&t;&bslash;&n;&t;&t;(((mode) == BOND_MODE_ACTIVEBACKUP) ||&t;&bslash;&n;&t;&t; ((mode) == BOND_MODE_TLB)          ||&t;&bslash;&n;&t;&t; ((mode) == BOND_MODE_ALB))
multiline_comment|/*&n; * Less bad way to call ioctl from within the kernel; this needs to be&n; * done some other way to get the call out of interrupt context.&n; * Needs &quot;ioctl&quot; variable to be supplied by calling context.&n; */
DECL|macro|IOCTL
mdefine_line|#define IOCTL(dev, arg, cmd) ({&t;&t;&bslash;&n;&t;int res = 0;&t;&t;&t;&bslash;&n;&t;mm_segment_t fs = get_fs();&t;&bslash;&n;&t;set_fs(get_ds());&t;&t;&bslash;&n;&t;res = ioctl(dev, arg, cmd);&t;&bslash;&n;&t;set_fs(fs);&t;&t;&t;&bslash;&n;&t;res; })
multiline_comment|/**&n; * bond_for_each_slave_from - iterate the slaves list from a starting point&n; * @bond:&t;the bond holding this list.&n; * @pos:&t;current slave.&n; * @cnt:&t;counter for max number of moves&n; * @start:&t;starting point.&n; *&n; * Caller must hold bond-&gt;lock&n; */
DECL|macro|bond_for_each_slave_from
mdefine_line|#define bond_for_each_slave_from(bond, pos, cnt, start)&t;&bslash;&n;&t;for (cnt = 0, pos = start;&t;&t;&t;&t;&bslash;&n;&t;     cnt &lt; (bond)-&gt;slave_cnt;&t;&t;&t;&t;&bslash;&n;             cnt++, pos = (pos)-&gt;next)
multiline_comment|/**&n; * bond_for_each_slave_from_to - iterate the slaves list from start point to stop point&n; * @bond:&t;the bond holding this list.&n; * @pos:&t;current slave.&n; * @cnt:&t;counter for number max of moves&n; * @start:&t;start point.&n; * @stop:&t;stop point.&n; *&n; * Caller must hold bond-&gt;lock&n; */
DECL|macro|bond_for_each_slave_from_to
mdefine_line|#define bond_for_each_slave_from_to(bond, pos, cnt, start, stop)&t;&bslash;&n;&t;for (cnt = 0, pos = start;&t;&t;&t;&t;&t;&bslash;&n;&t;     ((cnt &lt; (bond)-&gt;slave_cnt) &amp;&amp; (pos != (stop)-&gt;next));&t;&bslash;&n;             cnt++, pos = (pos)-&gt;next)
multiline_comment|/**&n; * bond_for_each_slave - iterate the slaves list from head&n; * @bond:&t;the bond holding this list.&n; * @pos:&t;current slave.&n; * @cnt:&t;counter for max number of moves&n; *&n; * Caller must hold bond-&gt;lock&n; */
DECL|macro|bond_for_each_slave
mdefine_line|#define bond_for_each_slave(bond, pos, cnt)&t;&bslash;&n;&t;&t;bond_for_each_slave_from(bond, pos, cnt, (bond)-&gt;first_slave)
DECL|struct|slave
r_struct
id|slave
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* first - usefull for panic debug */
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
DECL|member|delay
id|s16
id|delay
suffix:semicolon
DECL|member|jiffies
id|u32
id|jiffies
suffix:semicolon
DECL|member|link
id|s8
id|link
suffix:semicolon
multiline_comment|/* one of BOND_LINK_XXXX */
DECL|member|state
id|s8
id|state
suffix:semicolon
multiline_comment|/* one of BOND_STATE_XXXX */
DECL|member|original_flags
id|u32
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
)brace
suffix:semicolon
multiline_comment|/*&n; * Here are the locking policies for the two bonding locks:&n; *&n; * 1) Get bond-&gt;lock when reading/writing slave list.&n; * 2) Get bond-&gt;curr_slave_lock when reading/writing bond-&gt;curr_active_slave.&n; *    (It is unnecessary when the write-lock is put with bond-&gt;lock.)&n; * 3) When we lock with bond-&gt;curr_slave_lock, we must lock with bond-&gt;lock&n; *    beforehand.&n; */
DECL|struct|bonding
r_struct
id|bonding
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* first - usefull for panic debug */
DECL|member|first_slave
r_struct
id|slave
op_star
id|first_slave
suffix:semicolon
DECL|member|curr_active_slave
r_struct
id|slave
op_star
id|curr_active_slave
suffix:semicolon
DECL|member|current_arp_slave
r_struct
id|slave
op_star
id|current_arp_slave
suffix:semicolon
DECL|member|primary_slave
r_struct
id|slave
op_star
id|primary_slave
suffix:semicolon
DECL|member|slave_cnt
id|s32
id|slave_cnt
suffix:semicolon
multiline_comment|/* never change this value outside the attach/detach wrappers */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|curr_slave_lock
id|rwlock_t
id|curr_slave_lock
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
DECL|member|kill_timers
id|s8
id|kill_timers
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
DECL|member|proc_file_name
r_char
id|proc_file_name
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
DECL|member|mc_list
r_struct
id|dev_mc_list
op_star
id|mc_list
suffix:semicolon
DECL|member|flags
id|u16
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
)brace
suffix:semicolon
multiline_comment|/**&n; * Returns NULL if the net_device does not belong to any of the bond&squot;s slaves&n; *&n; * Caller must hold bond lock for read&n; */
DECL|function|bond_get_slave_by_dev
r_extern
r_inline
r_struct
id|slave
op_star
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
id|slave
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bond_for_each_slave
c_func
(paren
id|bond
comma
id|slave
comma
id|i
)paren
(brace
r_if
c_cond
(paren
id|slave-&gt;dev
op_eq
id|slave_dev
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
id|slave
suffix:semicolon
)brace
DECL|function|bond_get_bond_by_slave
r_extern
r_inline
r_struct
id|bonding
op_star
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
id|slave-&gt;dev-&gt;master-&gt;priv
suffix:semicolon
)brace
DECL|function|bond_set_slave_inactive_flags
r_extern
r_inline
r_void
id|bond_set_slave_inactive_flags
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
(brace
id|slave-&gt;state
op_assign
id|BOND_STATE_BACKUP
suffix:semicolon
id|slave-&gt;dev-&gt;flags
op_or_assign
id|IFF_NOARP
suffix:semicolon
)brace
DECL|function|bond_set_slave_active_flags
r_extern
r_inline
r_void
id|bond_set_slave_active_flags
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
(brace
id|slave-&gt;state
op_assign
id|BOND_STATE_ACTIVE
suffix:semicolon
id|slave-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_NOARP
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_BONDING_H */
eof
