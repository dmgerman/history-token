multiline_comment|/*&n; * Equalizer Load-balancer for serial network interfaces.&n; *&n; * (c) Copyright 1995 Simon &quot;Guru Aleph-Null&quot; Janes&n; * NCM: Network and Communications Management, Inc.&n; *&n; * (c) Copyright 2002 David S. Miller (davem@redhat.com)&n; *&n; *&t;This software may be used and distributed according to the terms&n; *&t;of the GNU General Public License, incorporated herein by reference.&n; * &n; * The author may be reached as simon@ncm.com, or C/O&n; *    NCM&n; *    Attn: Simon Janes&n; *    6803 Whittier Ave&n; *    McLean VA 22101&n; *    Phone: 1-703-847-0040 ext 103&n; */
multiline_comment|/*&n; * Sources:&n; *   skeleton.c by Donald Becker.&n; * Inspirations:&n; *   The Harried and Overworked Alan Cox&n; * Conspiracies:&n; *   The Alan Cox and Mike McLagan plot to get someone else to do the code, &n; *   which turned out to be me.&n; */
multiline_comment|/*&n; * $Log: eql.c,v $&n; * Revision 1.2  1996/04/11 17:51:52  guru&n; * Added one-line eql_remove_slave patch.&n; *&n; * Revision 1.1  1996/04/11 17:44:17  guru&n; * Initial revision&n; *&n; * Revision 3.13  1996/01/21  15:17:18  alan&n; * tx_queue_len changes.&n; * reformatted.&n; *&n; * Revision 3.12  1995/03/22  21:07:51  anarchy&n; * Added capable() checks on configuration.&n; * Moved header file.&n; *&n; * Revision 3.11  1995/01/19  23:14:31  guru&n; * &t;&t;      slave_load = (ULONG_MAX - (ULONG_MAX / 2)) -&n; * &t;&t;&t;(priority_Bps) + bytes_queued * 8;&n; *&n; * Revision 3.10  1995/01/19  23:07:53  guru&n; * back to&n; * &t;&t;      slave_load = (ULONG_MAX - (ULONG_MAX / 2)) -&n; * &t;&t;&t;(priority_Bps) + bytes_queued;&n; *&n; * Revision 3.9  1995/01/19  22:38:20  guru&n; * &t;&t;      slave_load = (ULONG_MAX - (ULONG_MAX / 2)) -&n; * &t;&t;&t;(priority_Bps) + bytes_queued * 4;&n; *&n; * Revision 3.8  1995/01/19  22:30:55  guru&n; *       slave_load = (ULONG_MAX - (ULONG_MAX / 2)) -&n; * &t;&t;&t;(priority_Bps) + bytes_queued * 2;&n; *&n; * Revision 3.7  1995/01/19  21:52:35  guru&n; * printk&squot;s trimmed out.&n; *&n; * Revision 3.6  1995/01/19  21:49:56  guru&n; * This is working pretty well. I gained 1 K/s in speed.. now it&squot;s just&n; * robustness and printk&squot;s to be diked out.&n; *&n; * Revision 3.5  1995/01/18  22:29:59  guru&n; * still crashes the kernel when the lock_wait thing is woken up.&n; *&n; * Revision 3.4  1995/01/18  21:59:47  guru&n; * Broken set-bit locking snapshot&n; *&n; * Revision 3.3  1995/01/17  22:09:18  guru&n; * infinite sleep in a lock somewhere..&n; *&n; * Revision 3.2  1995/01/15  16:46:06  guru&n; * Log trimmed of non-pertinent 1.x branch messages&n; *&n; * Revision 3.1  1995/01/15  14:41:45  guru&n; * New Scheduler and timer stuff...&n; *&n; * Revision 1.15  1995/01/15  14:29:02  guru&n; * Will make 1.14 (now 1.15) the 3.0 branch, and the 1.12 the 2.0 branch, the one&n; * with the dumber scheduler&n; *&n; * Revision 1.14  1995/01/15  02:37:08  guru&n; * shock.. the kept-new-versions could have zonked working&n; * stuff.. shudder&n; *&n; * Revision 1.13  1995/01/15  02:36:31  guru&n; * big changes&n; *&n; * &t;scheduler was torn out and replaced with something smarter&n; *&n; * &t;global names not prefixed with eql_ were renamed to protect&n; * &t;against namespace collisions&n; *&n; * &t;a few more abstract interfaces were added to facilitate any&n; * &t;potential change of datastructure.  the driver is still using&n; * &t;a linked list of slaves.  going to a heap would be a bit of&n; * &t;an overkill.&n; *&n; * &t;this compiles fine with no warnings.&n; *&n; * &t;the locking mechanism and timer stuff must be written however,&n; * &t;this version will not work otherwise&n; *&n; * Sorry, I had to rewrite most of this for 2.5.x -DaveM&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_eql.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_static
r_int
id|eql_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|eql_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|eql_ioctl
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
r_static
r_int
id|eql_slave_xmit
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
r_static
r_struct
id|net_device_stats
op_star
id|eql_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|eql_is_slave
mdefine_line|#define eql_is_slave(dev)&t;((dev-&gt;flags &amp; IFF_SLAVE) == IFF_SLAVE)
DECL|macro|eql_is_master
mdefine_line|#define eql_is_master(dev)&t;((dev-&gt;flags &amp; IFF_MASTER) == IFF_MASTER)
r_static
r_void
id|eql_kill_one_slave
c_func
(paren
id|slave_t
op_star
id|slave
)paren
suffix:semicolon
DECL|function|eql_timer
r_static
r_void
id|eql_timer
c_func
(paren
r_int
r_int
id|param
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
(paren
id|equalizer_t
op_star
)paren
id|param
suffix:semicolon
r_struct
id|list_head
op_star
id|this
comma
op_star
id|tmp
comma
op_star
id|head
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|eql-&gt;queue.all_slaves
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|this
comma
id|tmp
comma
id|head
)paren
(brace
id|slave_t
op_star
id|slave
op_assign
id|list_entry
c_func
(paren
id|this
comma
id|slave_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slave-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
op_eq
id|IFF_UP
)paren
(brace
id|slave-&gt;bytes_queued
op_sub_assign
id|slave-&gt;priority_Bps
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;bytes_queued
OL
l_int|0
)paren
id|slave-&gt;bytes_queued
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|eql_kill_one_slave
c_func
(paren
id|slave
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
id|eql-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|EQL_DEFAULT_RESCHED_IVAL
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|eql-&gt;timer
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;Equalizer2002: Simon Janes (simon@ncm.com) and David S. Miller (davem@redhat.com)&bslash;n&quot;
suffix:semicolon
DECL|function|eql_setup
r_static
r_void
id|__init
id|eql_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|eql-&gt;timer
)paren
suffix:semicolon
id|eql-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|dev-&gt;priv
suffix:semicolon
id|eql-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|EQL_DEFAULT_RESCHED_IVAL
suffix:semicolon
id|eql-&gt;timer.function
op_assign
id|eql_timer
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|eql-&gt;queue.all_slaves
)paren
suffix:semicolon
id|eql-&gt;queue.master_dev
op_assign
id|dev
suffix:semicolon
id|dev-&gt;open
op_assign
id|eql_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|eql_close
suffix:semicolon
id|dev-&gt;do_ioctl
op_assign
id|eql_ioctl
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|eql_slave_xmit
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|eql_get_stats
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now we undo some of the things that eth_setup does&n;&t; * &t;that we don&squot;t like &n;&t; */
id|dev-&gt;mtu
op_assign
id|EQL_DEFAULT_MTU
suffix:semicolon
multiline_comment|/* set to 576 in if_eql.h */
id|dev-&gt;flags
op_assign
id|IFF_MASTER
suffix:semicolon
id|dev-&gt;type
op_assign
id|ARPHRD_SLIP
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* Hands them off fast */
)brace
DECL|function|eql_open
r_static
r_int
id|eql_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* XXX We should force this off automatically for the user. */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: remember to turn off Van-Jacobson compression on &quot;
l_string|&quot;your slave devices.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|eql-&gt;queue.all_slaves
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|eql-&gt;min_slaves
op_assign
l_int|1
suffix:semicolon
id|eql-&gt;max_slaves
op_assign
id|EQL_DEFAULT_MAX_SLAVES
suffix:semicolon
multiline_comment|/* 4 usually... */
id|add_timer
c_func
(paren
op_amp
id|eql-&gt;timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|eql_kill_one_slave
r_static
r_void
id|eql_kill_one_slave
c_func
(paren
id|slave_t
op_star
id|slave
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|slave-&gt;list
)paren
suffix:semicolon
id|slave-&gt;dev-&gt;flags
op_and_assign
op_complement
id|IFF_SLAVE
suffix:semicolon
id|dev_put
c_func
(paren
id|slave-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slave
)paren
suffix:semicolon
)brace
DECL|function|eql_kill_slave_queue
r_static
r_void
id|eql_kill_slave_queue
c_func
(paren
id|slave_queue_t
op_star
id|queue
)paren
(brace
r_struct
id|list_head
op_star
id|head
comma
op_star
id|tmp
comma
op_star
id|this
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|queue-&gt;lock
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|queue-&gt;all_slaves
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|this
comma
id|tmp
comma
id|head
)paren
(brace
id|slave_t
op_star
id|s
op_assign
id|list_entry
c_func
(paren
id|this
comma
id|slave_t
comma
id|list
)paren
suffix:semicolon
id|eql_kill_one_slave
c_func
(paren
id|s
)paren
suffix:semicolon
id|queue-&gt;num_slaves
op_decrement
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|queue-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|eql_close
r_static
r_int
id|eql_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The timer has to be stopped first before we start hacking away&n;&t; *&t;at the data structure it scans every so often... &n;&t; */
id|del_timer_sync
c_func
(paren
op_amp
id|eql-&gt;timer
)paren
suffix:semicolon
id|eql_kill_slave_queue
c_func
(paren
op_amp
id|eql-&gt;queue
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|eql_enslave
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|slaving_request_t
id|__user
op_star
id|srq
)paren
suffix:semicolon
r_static
r_int
id|eql_emancipate
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|slaving_request_t
id|__user
op_star
id|srq
)paren
suffix:semicolon
r_static
r_int
id|eql_g_slave_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|slave_config_t
id|__user
op_star
id|sc
)paren
suffix:semicolon
r_static
r_int
id|eql_s_slave_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|slave_config_t
id|__user
op_star
id|sc
)paren
suffix:semicolon
r_static
r_int
id|eql_g_master_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|master_config_t
id|__user
op_star
id|mc
)paren
suffix:semicolon
r_static
r_int
id|eql_s_master_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|master_config_t
id|__user
op_star
id|mc
)paren
suffix:semicolon
DECL|function|eql_ioctl
r_static
r_int
id|eql_ioctl
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
(brace
r_if
c_cond
(paren
id|cmd
op_ne
id|EQL_GETMASTRCFG
op_logical_and
id|cmd
op_ne
id|EQL_GETSLAVECFG
op_logical_and
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|EQL_ENSLAVE
suffix:colon
r_return
id|eql_enslave
c_func
(paren
id|dev
comma
id|ifr-&gt;ifr_data
)paren
suffix:semicolon
r_case
id|EQL_EMANCIPATE
suffix:colon
r_return
id|eql_emancipate
c_func
(paren
id|dev
comma
id|ifr-&gt;ifr_data
)paren
suffix:semicolon
r_case
id|EQL_GETSLAVECFG
suffix:colon
r_return
id|eql_g_slave_cfg
c_func
(paren
id|dev
comma
id|ifr-&gt;ifr_data
)paren
suffix:semicolon
r_case
id|EQL_SETSLAVECFG
suffix:colon
r_return
id|eql_s_slave_cfg
c_func
(paren
id|dev
comma
id|ifr-&gt;ifr_data
)paren
suffix:semicolon
r_case
id|EQL_GETMASTRCFG
suffix:colon
r_return
id|eql_g_master_cfg
c_func
(paren
id|dev
comma
id|ifr-&gt;ifr_data
)paren
suffix:semicolon
r_case
id|EQL_SETMASTRCFG
suffix:colon
r_return
id|eql_s_master_cfg
c_func
(paren
id|dev
comma
id|ifr-&gt;ifr_data
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* queue-&gt;lock must be held */
DECL|function|__eql_schedule_slaves
r_static
id|slave_t
op_star
id|__eql_schedule_slaves
c_func
(paren
id|slave_queue_t
op_star
id|queue
)paren
(brace
r_int
r_int
id|best_load
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_struct
id|list_head
op_star
id|this
comma
op_star
id|tmp
comma
op_star
id|head
suffix:semicolon
id|slave_t
op_star
id|best_slave
suffix:semicolon
id|best_slave
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Make a pass to set the best slave. */
id|head
op_assign
op_amp
id|queue-&gt;all_slaves
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|this
comma
id|tmp
comma
id|head
)paren
(brace
id|slave_t
op_star
id|slave
op_assign
id|list_entry
c_func
(paren
id|this
comma
id|slave_t
comma
id|list
)paren
suffix:semicolon
r_int
r_int
id|slave_load
comma
id|bytes_queued
comma
id|priority_Bps
suffix:semicolon
multiline_comment|/* Go through the slave list once, updating best_slave&n;&t;&t; * whenever a new best_load is found.&n;&t;&t; */
id|bytes_queued
op_assign
id|slave-&gt;bytes_queued
suffix:semicolon
id|priority_Bps
op_assign
id|slave-&gt;priority_Bps
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slave-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
op_eq
id|IFF_UP
)paren
(brace
id|slave_load
op_assign
(paren
op_complement
l_int|0UL
op_minus
(paren
op_complement
l_int|0UL
op_div
l_int|2
)paren
)paren
op_minus
(paren
id|priority_Bps
)paren
op_plus
id|bytes_queued
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|slave_load
OL
id|best_load
)paren
(brace
id|best_load
op_assign
id|slave_load
suffix:semicolon
id|best_slave
op_assign
id|slave
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* We found a dead slave, kill it. */
id|eql_kill_one_slave
c_func
(paren
id|slave
)paren
suffix:semicolon
)brace
)brace
r_return
id|best_slave
suffix:semicolon
)brace
DECL|function|eql_slave_xmit
r_static
r_int
id|eql_slave_xmit
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
id|equalizer_t
op_star
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
id|slave_t
op_star
id|slave
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
id|slave
op_assign
id|__eql_schedule_slaves
c_func
(paren
op_amp
id|eql-&gt;queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave
)paren
(brace
r_struct
id|net_device
op_star
id|slave_dev
op_assign
id|slave-&gt;dev
suffix:semicolon
id|skb-&gt;dev
op_assign
id|slave_dev
suffix:semicolon
id|skb-&gt;priority
op_assign
l_int|1
suffix:semicolon
id|slave-&gt;bytes_queued
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|dev_queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
id|eql-&gt;stats.tx_packets
op_increment
suffix:semicolon
)brace
r_else
(brace
id|eql-&gt;stats.tx_dropped
op_increment
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|eql_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|eql_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|eql-&gt;stats
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Private ioctl functions&n; */
multiline_comment|/* queue-&gt;lock must be held */
DECL|function|__eql_find_slave_dev
r_static
id|slave_t
op_star
id|__eql_find_slave_dev
c_func
(paren
id|slave_queue_t
op_star
id|queue
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|list_head
op_star
id|this
comma
op_star
id|head
suffix:semicolon
id|head
op_assign
op_amp
id|queue-&gt;all_slaves
suffix:semicolon
id|list_for_each
c_func
(paren
id|this
comma
id|head
)paren
(brace
id|slave_t
op_star
id|slave
op_assign
id|list_entry
c_func
(paren
id|this
comma
id|slave_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave-&gt;dev
op_eq
id|dev
)paren
r_return
id|slave
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|eql_is_full
r_static
r_inline
r_int
id|eql_is_full
c_func
(paren
id|slave_queue_t
op_star
id|queue
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|queue-&gt;master_dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;num_slaves
op_ge
id|eql-&gt;max_slaves
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* queue-&gt;lock must be held */
DECL|function|__eql_insert_slave
r_static
r_int
id|__eql_insert_slave
c_func
(paren
id|slave_queue_t
op_star
id|queue
comma
id|slave_t
op_star
id|slave
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|eql_is_full
c_func
(paren
id|queue
)paren
)paren
(brace
id|slave_t
op_star
id|duplicate_slave
op_assign
l_int|0
suffix:semicolon
id|duplicate_slave
op_assign
id|__eql_find_slave_dev
c_func
(paren
id|queue
comma
id|slave-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|duplicate_slave
op_ne
l_int|0
)paren
id|eql_kill_one_slave
c_func
(paren
id|duplicate_slave
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|slave-&gt;list
comma
op_amp
id|queue-&gt;all_slaves
)paren
suffix:semicolon
id|queue-&gt;num_slaves
op_increment
suffix:semicolon
id|slave-&gt;dev-&gt;flags
op_or_assign
id|IFF_SLAVE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
DECL|function|eql_enslave
r_static
r_int
id|eql_enslave
c_func
(paren
r_struct
id|net_device
op_star
id|master_dev
comma
id|slaving_request_t
id|__user
op_star
id|srqp
)paren
(brace
r_struct
id|net_device
op_star
id|slave_dev
suffix:semicolon
id|slaving_request_t
id|srq
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|srq
comma
id|srqp
comma
r_sizeof
(paren
id|slaving_request_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|slave_dev
op_assign
id|dev_get_by_name
c_func
(paren
id|srq.slave_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave_dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|master_dev-&gt;flags
op_amp
id|IFF_UP
)paren
op_eq
id|IFF_UP
)paren
(brace
multiline_comment|/* slave is not a master &amp; not already a slave: */
r_if
c_cond
(paren
op_logical_neg
id|eql_is_master
c_func
(paren
id|slave_dev
)paren
op_logical_and
op_logical_neg
id|eql_is_slave
c_func
(paren
id|slave_dev
)paren
)paren
(brace
id|slave_t
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|equalizer_t
op_star
id|eql
op_assign
id|master_dev-&gt;priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
(brace
id|dev_put
c_func
(paren
id|slave_dev
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|s
)paren
)paren
suffix:semicolon
id|s-&gt;dev
op_assign
id|slave_dev
suffix:semicolon
id|s-&gt;priority
op_assign
id|srq.priority
suffix:semicolon
id|s-&gt;priority_bps
op_assign
id|srq.priority
suffix:semicolon
id|s-&gt;priority_Bps
op_assign
id|srq.priority
op_div
l_int|8
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
id|ret
op_assign
id|__eql_insert_slave
c_func
(paren
op_amp
id|eql-&gt;queue
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|dev_put
c_func
(paren
id|slave_dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
id|dev_put
c_func
(paren
id|slave_dev
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|eql_emancipate
r_static
r_int
id|eql_emancipate
c_func
(paren
r_struct
id|net_device
op_star
id|master_dev
comma
id|slaving_request_t
id|__user
op_star
id|srqp
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|master_dev-&gt;priv
suffix:semicolon
r_struct
id|net_device
op_star
id|slave_dev
suffix:semicolon
id|slaving_request_t
id|srq
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|srq
comma
id|srqp
comma
r_sizeof
(paren
id|slaving_request_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|slave_dev
op_assign
id|dev_get_by_name
c_func
(paren
id|srq.slave_name
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
id|slave_dev
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eql_is_slave
c_func
(paren
id|slave_dev
)paren
)paren
(brace
id|slave_t
op_star
id|slave
op_assign
id|__eql_find_slave_dev
c_func
(paren
op_amp
id|eql-&gt;queue
comma
id|slave_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave
)paren
(brace
id|eql_kill_one_slave
c_func
(paren
id|slave
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|dev_put
c_func
(paren
id|slave_dev
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|eql_g_slave_cfg
r_static
r_int
id|eql_g_slave_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|slave_config_t
id|__user
op_star
id|scp
)paren
(brace
id|equalizer_t
op_star
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
id|slave_t
op_star
id|slave
suffix:semicolon
r_struct
id|net_device
op_star
id|slave_dev
suffix:semicolon
id|slave_config_t
id|sc
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sc
comma
id|scp
comma
r_sizeof
(paren
id|slave_config_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|slave_dev
op_assign
id|dev_get_by_name
c_func
(paren
id|sc.slave_name
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eql_is_slave
c_func
(paren
id|slave_dev
)paren
)paren
(brace
id|slave
op_assign
id|__eql_find_slave_dev
c_func
(paren
op_amp
id|eql-&gt;queue
comma
id|slave_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave
)paren
(brace
id|sc.priority
op_assign
id|slave-&gt;priority
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|slave_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|copy_to_user
c_func
(paren
id|scp
comma
op_amp
id|sc
comma
r_sizeof
(paren
id|slave_config_t
)paren
)paren
)paren
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|eql_s_slave_cfg
r_static
r_int
id|eql_s_slave_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|slave_config_t
id|__user
op_star
id|scp
)paren
(brace
id|slave_t
op_star
id|slave
suffix:semicolon
id|equalizer_t
op_star
id|eql
suffix:semicolon
r_struct
id|net_device
op_star
id|slave_dev
suffix:semicolon
id|slave_config_t
id|sc
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sc
comma
id|scp
comma
r_sizeof
(paren
id|slave_config_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
id|slave_dev
op_assign
id|dev_get_by_name
c_func
(paren
id|sc.slave_name
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eql_is_slave
c_func
(paren
id|slave_dev
)paren
)paren
(brace
id|slave
op_assign
id|__eql_find_slave_dev
c_func
(paren
op_amp
id|eql-&gt;queue
comma
id|slave_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slave
)paren
(brace
id|slave-&gt;priority
op_assign
id|sc.priority
suffix:semicolon
id|slave-&gt;priority_bps
op_assign
id|sc.priority
suffix:semicolon
id|slave-&gt;priority_Bps
op_assign
id|sc.priority
op_div
l_int|8
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|eql-&gt;queue.lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|eql_g_master_cfg
r_static
r_int
id|eql_g_master_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|master_config_t
id|__user
op_star
id|mcp
)paren
(brace
id|equalizer_t
op_star
id|eql
suffix:semicolon
id|master_config_t
id|mc
suffix:semicolon
r_if
c_cond
(paren
id|eql_is_master
c_func
(paren
id|dev
)paren
)paren
(brace
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
id|mc.max_slaves
op_assign
id|eql-&gt;max_slaves
suffix:semicolon
id|mc.min_slaves
op_assign
id|eql-&gt;min_slaves
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|mcp
comma
op_amp
id|mc
comma
r_sizeof
(paren
id|master_config_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|eql_s_master_cfg
r_static
r_int
id|eql_s_master_cfg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|master_config_t
id|__user
op_star
id|mcp
)paren
(brace
id|equalizer_t
op_star
id|eql
suffix:semicolon
id|master_config_t
id|mc
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|mc
comma
id|mcp
comma
r_sizeof
(paren
id|master_config_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|eql_is_master
c_func
(paren
id|dev
)paren
)paren
(brace
id|eql
op_assign
id|dev-&gt;priv
suffix:semicolon
id|eql-&gt;max_slaves
op_assign
id|mc.max_slaves
suffix:semicolon
id|eql-&gt;min_slaves
op_assign
id|mc.min_slaves
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|dev_eql
r_static
r_struct
id|net_device
op_star
id|dev_eql
suffix:semicolon
DECL|function|eql_init_module
r_static
r_int
id|__init
id|eql_init_module
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
id|version
)paren
suffix:semicolon
id|dev_eql
op_assign
id|alloc_netdev
c_func
(paren
r_sizeof
(paren
id|equalizer_t
)paren
comma
l_string|&quot;eql&quot;
comma
id|eql_setup
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_eql
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev_eql
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|free_netdev
c_func
(paren
id|dev_eql
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|eql_cleanup_module
r_static
r_void
id|__exit
id|eql_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_netdev
c_func
(paren
id|dev_eql
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev_eql
)paren
suffix:semicolon
)brace
DECL|variable|eql_init_module
id|module_init
c_func
(paren
id|eql_init_module
)paren
suffix:semicolon
DECL|variable|eql_cleanup_module
id|module_exit
c_func
(paren
id|eql_cleanup_module
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
