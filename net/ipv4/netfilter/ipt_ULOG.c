multiline_comment|/*&n; * netfilter module for userspace packet logging daemons&n; *&n; * (C) 2000-2002 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * 2000/09/22 ulog-cprange feature added&n; * 2001/01/04 in-kernel queue as proposed by Sebastian Zander &n; * &t;&t;&t;&t;&t;&t;&lt;zander@fokus.gmd.de&gt;&n; * 2001/01/30 per-rule nlgroup conflicts with global queue. &n; *            nlgroup now global (sysctl)&n; * 2001/04/19 ulog-queue reworked, now fixed buffer size specified at&n; * &t;      module loadtime -HW&n; * 2002/07/07 remove broken nflog_rcv() function -HW&n; * 2002/08/29 fix shifted/unshifted nlgroup bug -HW&n; * 2002/10/30 fix uninitialized mac_len field - &lt;Anders K. Pedersen&gt;&n; *&n; * Released under the terms of the GPL&n; *&n; * This module accepts two parameters: &n; * &n; * nlbufsiz:&n; *   The parameter specifies how big the buffer for each netlink multicast&n; * group is. e.g. If you say nlbufsiz=8192, up to eight kb of packets will&n; * get accumulated in the kernel until they are sent to userspace. It is&n; * NOT possible to allocate more than 128kB, and it is strongly discouraged,&n; * because atomically allocating 128kB inside the network rx softirq is not&n; * reliable. Please also keep in mind that this buffer size is allocated for&n; * each nlgroup you are using, so the total kernel memory usage increases&n; * by that factor.&n; *&n; * flushtimeout:&n; *   Specify, after how many clock ticks (intel: 100 per second) the queue&n; * should be flushed even if it is not full yet.&n; *&n; * ipt_ULOG.c,v 1.22 2002/10/30 09:07:31 laforge Exp&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ipt_ULOG.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Harald Welte &lt;laforge@gnumonks.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IP tables userspace logging module&quot;
)paren
suffix:semicolon
DECL|macro|ULOG_NL_EVENT
mdefine_line|#define ULOG_NL_EVENT&t;&t;111&t;&t;/* Harald&squot;s favorite number */
DECL|macro|ULOG_MAXNLGROUPS
mdefine_line|#define ULOG_MAXNLGROUPS&t;32&t;&t;/* numer of nlgroups */
macro_line|#if 0
mdefine_line|#define DEBUGP(format, args...)&t;printk(__FILE__ &quot;:&quot; __FUNCTION__ &quot;:&quot; &bslash;&n;&t;&t;&t;&t;       format, ## args)
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
macro_line|#endif
DECL|macro|PRINTR
mdefine_line|#define PRINTR(format, args...) do { if (net_ratelimit()) printk(format, ## args); } while (0)
DECL|variable|nlbufsiz
r_static
r_int
r_int
id|nlbufsiz
op_assign
l_int|4096
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|nlbufsiz
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nlbufsiz
comma
l_string|&quot;netlink buffer size&quot;
)paren
suffix:semicolon
DECL|variable|flushtimeout
r_static
r_int
r_int
id|flushtimeout
op_assign
l_int|10
op_star
id|HZ
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|flushtimeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|flushtimeout
comma
l_string|&quot;buffer flush timeout&quot;
)paren
suffix:semicolon
multiline_comment|/* global data structures */
r_typedef
r_struct
(brace
DECL|member|qlen
r_int
r_int
id|qlen
suffix:semicolon
multiline_comment|/* number of nlmsgs&squot; in the skb */
DECL|member|lastnlh
r_struct
id|nlmsghdr
op_star
id|lastnlh
suffix:semicolon
multiline_comment|/* netlink header of last msg in skb */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* the pre-allocated skb */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* the timer function */
DECL|typedef|ulog_buff_t
)brace
id|ulog_buff_t
suffix:semicolon
DECL|variable|ulog_buffers
r_static
id|ulog_buff_t
id|ulog_buffers
(braket
id|ULOG_MAXNLGROUPS
)braket
suffix:semicolon
multiline_comment|/* array of buffers */
DECL|variable|nflognl
r_static
r_struct
id|sock
op_star
id|nflognl
suffix:semicolon
multiline_comment|/* our socket */
DECL|variable|qlen
r_static
r_int
id|qlen
suffix:semicolon
multiline_comment|/* current length of multipart-nlmsg */
DECL|variable|ulog_lock
id|DECLARE_LOCK
c_func
(paren
id|ulog_lock
)paren
suffix:semicolon
multiline_comment|/* spinlock */
multiline_comment|/* send one ulog_buff_t to userspace */
DECL|function|ulog_send
r_static
r_void
id|ulog_send
c_func
(paren
r_int
r_int
id|nlgroupnum
)paren
(brace
id|ulog_buff_t
op_star
id|ub
op_assign
op_amp
id|ulog_buffers
(braket
id|nlgroupnum
)braket
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|ub-&gt;timer
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: ulog_send: timer was pending, deleting&bslash;n&quot;
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|ub-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/* last nlmsg needs NLMSG_DONE */
r_if
c_cond
(paren
id|ub-&gt;qlen
OG
l_int|1
)paren
id|ub-&gt;lastnlh-&gt;nlmsg_type
op_assign
id|NLMSG_DONE
suffix:semicolon
id|NETLINK_CB
c_func
(paren
id|ub-&gt;skb
)paren
dot
id|dst_groups
op_assign
(paren
l_int|1
op_lshift
id|nlgroupnum
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: throwing %d packets to netlink mask %u&bslash;n&quot;
comma
id|ub-&gt;qlen
comma
id|nlgroup
)paren
suffix:semicolon
id|netlink_broadcast
c_func
(paren
id|nflognl
comma
id|ub-&gt;skb
comma
l_int|0
comma
(paren
l_int|1
op_lshift
id|nlgroupnum
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|ub-&gt;qlen
op_assign
l_int|0
suffix:semicolon
id|ub-&gt;skb
op_assign
l_int|NULL
suffix:semicolon
id|ub-&gt;lastnlh
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* timer function to flush queue in ULOG_FLUSH_INTERVAL time */
DECL|function|ulog_timer
r_static
r_void
id|ulog_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: timer function called, calling ulog_send&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* lock to protect against somebody modifying our structure&n;&t; * from ipt_ulog_target at the same time */
id|LOCK_BH
c_func
(paren
op_amp
id|ulog_lock
)paren
suffix:semicolon
id|ulog_send
c_func
(paren
id|data
)paren
suffix:semicolon
id|UNLOCK_BH
c_func
(paren
op_amp
id|ulog_lock
)paren
suffix:semicolon
)brace
DECL|function|ulog_alloc_skb
r_struct
id|sk_buff
op_star
id|ulog_alloc_skb
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* alloc skb which should be big enough for a whole&n;&t; * multipart message. WARNING: has to be &lt;= 131000&n;&t; * due to slab allocator restrictions */
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|nlbufsiz
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|PRINTR
c_func
(paren
l_string|&quot;ipt_ULOG: can&squot;t alloc whole buffer %ub!&bslash;n&quot;
comma
id|nlbufsiz
)paren
suffix:semicolon
multiline_comment|/* try to allocate only as much as we need for &n;&t;&t; * current packet */
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
id|PRINTR
c_func
(paren
l_string|&quot;ipt_ULOG: can&squot;t even allocate %ub&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
DECL|function|ipt_ulog_target
r_static
r_int
r_int
id|ipt_ulog_target
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_const
r_struct
id|net_device
op_star
id|in
comma
r_const
r_struct
id|net_device
op_star
id|out
comma
r_int
r_int
id|hooknum
comma
r_const
r_void
op_star
id|targinfo
comma
r_void
op_star
id|userinfo
)paren
(brace
id|ulog_buff_t
op_star
id|ub
suffix:semicolon
id|ulog_packet_msg_t
op_star
id|pm
suffix:semicolon
r_int
id|size
comma
id|copy_len
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_struct
id|ipt_ulog_info
op_star
id|loginfo
op_assign
(paren
r_struct
id|ipt_ulog_info
op_star
)paren
id|targinfo
suffix:semicolon
multiline_comment|/* ffs == find first bit set, necessary because userspace&n;&t; * is already shifting groupnumber, but we need unshifted.&n;&t; * ffs() returns [1..32], we need [0..31] */
r_int
r_int
id|groupnum
op_assign
id|ffs
c_func
(paren
id|loginfo-&gt;nl_group
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* calculate the size of the skb needed */
r_if
c_cond
(paren
(paren
id|loginfo-&gt;copy_range
op_eq
l_int|0
)paren
op_logical_or
(paren
id|loginfo-&gt;copy_range
OG
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
)paren
)paren
(brace
id|copy_len
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|len
suffix:semicolon
)brace
r_else
(brace
id|copy_len
op_assign
id|loginfo-&gt;copy_range
suffix:semicolon
)brace
id|size
op_assign
id|NLMSG_SPACE
c_func
(paren
r_sizeof
(paren
op_star
id|pm
)paren
op_plus
id|copy_len
)paren
suffix:semicolon
id|ub
op_assign
op_amp
id|ulog_buffers
(braket
id|groupnum
)braket
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ulog_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ub-&gt;skb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ub-&gt;skb
op_assign
id|ulog_alloc_skb
c_func
(paren
id|size
)paren
)paren
)paren
r_goto
id|alloc_failure
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ub-&gt;qlen
op_ge
id|loginfo-&gt;qthreshold
op_logical_or
id|size
OG
id|skb_tailroom
c_func
(paren
id|ub-&gt;skb
)paren
)paren
(brace
multiline_comment|/* either the queue len is too high or we don&squot;t have &n;&t;&t; * enough room in nlskb left. send it to userspace. */
id|ulog_send
c_func
(paren
id|groupnum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ub-&gt;skb
op_assign
id|ulog_alloc_skb
c_func
(paren
id|size
)paren
)paren
)paren
r_goto
id|alloc_failure
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: qlen %d, qthreshold %d&bslash;n&quot;
comma
id|ub-&gt;qlen
comma
id|loginfo-&gt;qthreshold
)paren
suffix:semicolon
multiline_comment|/* NLMSG_PUT contains a hidden goto nlmsg_failure !!! */
id|nlh
op_assign
id|NLMSG_PUT
c_func
(paren
id|ub-&gt;skb
comma
l_int|0
comma
id|ub-&gt;qlen
comma
id|ULOG_NL_EVENT
comma
id|size
op_minus
r_sizeof
(paren
op_star
id|nlh
)paren
)paren
suffix:semicolon
id|ub-&gt;qlen
op_increment
suffix:semicolon
id|pm
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
multiline_comment|/* copy hook, prefix, timestamp, payload, etc. */
id|pm-&gt;data_len
op_assign
id|copy_len
suffix:semicolon
id|pm-&gt;timestamp_sec
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|stamp.tv_sec
suffix:semicolon
id|pm-&gt;timestamp_usec
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|stamp.tv_usec
suffix:semicolon
id|pm-&gt;mark
op_assign
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nfmark
suffix:semicolon
id|pm-&gt;hook
op_assign
id|hooknum
suffix:semicolon
r_if
c_cond
(paren
id|loginfo-&gt;prefix
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|strncpy
c_func
(paren
id|pm-&gt;prefix
comma
id|loginfo-&gt;prefix
comma
r_sizeof
(paren
id|pm-&gt;prefix
)paren
)paren
suffix:semicolon
r_else
op_star
(paren
id|pm-&gt;prefix
)paren
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|in
op_logical_and
id|in-&gt;hard_header_len
OG
l_int|0
op_logical_and
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|mac.raw
op_ne
(paren
r_void
op_star
)paren
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|nh.iph
op_logical_and
id|in-&gt;hard_header_len
op_le
id|ULOG_MAC_LEN
)paren
(brace
id|memcpy
c_func
(paren
id|pm-&gt;mac
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|mac.raw
comma
id|in-&gt;hard_header_len
)paren
suffix:semicolon
id|pm-&gt;mac_len
op_assign
id|in-&gt;hard_header_len
suffix:semicolon
)brace
r_else
id|pm-&gt;mac_len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|in
)paren
id|strncpy
c_func
(paren
id|pm-&gt;indev_name
comma
id|in-&gt;name
comma
r_sizeof
(paren
id|pm-&gt;indev_name
)paren
)paren
suffix:semicolon
r_else
id|pm-&gt;indev_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|out
)paren
id|strncpy
c_func
(paren
id|pm-&gt;outdev_name
comma
id|out-&gt;name
comma
r_sizeof
(paren
id|pm-&gt;outdev_name
)paren
)paren
suffix:semicolon
r_else
id|pm-&gt;outdev_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* copy_len &lt;= (*pskb)-&gt;len, so can&squot;t fail. */
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
op_star
id|pskb
comma
l_int|0
comma
id|pm-&gt;payload
comma
id|copy_len
)paren
OL
l_int|0
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* check if we are building multi-part messages */
r_if
c_cond
(paren
id|ub-&gt;qlen
OG
l_int|1
)paren
(brace
id|ub-&gt;lastnlh-&gt;nlmsg_flags
op_or_assign
id|NLM_F_MULTI
suffix:semicolon
)brace
multiline_comment|/* if threshold is reached, send message to userspace */
r_if
c_cond
(paren
id|qlen
op_ge
id|loginfo-&gt;qthreshold
)paren
(brace
r_if
c_cond
(paren
id|loginfo-&gt;qthreshold
OG
l_int|1
)paren
id|nlh-&gt;nlmsg_type
op_assign
id|NLMSG_DONE
suffix:semicolon
)brace
id|ub-&gt;lastnlh
op_assign
id|nlh
suffix:semicolon
multiline_comment|/* if timer isn&squot;t already running, start it */
r_if
c_cond
(paren
op_logical_neg
id|timer_pending
c_func
(paren
op_amp
id|ub-&gt;timer
)paren
)paren
(brace
id|ub-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|flushtimeout
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ub-&gt;timer
)paren
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ulog_lock
)paren
suffix:semicolon
r_return
id|IPT_CONTINUE
suffix:semicolon
id|nlmsg_failure
suffix:colon
id|PRINTR
c_func
(paren
l_string|&quot;ipt_ULOG: error during NLMSG_PUT&bslash;n&quot;
)paren
suffix:semicolon
id|alloc_failure
suffix:colon
id|PRINTR
c_func
(paren
l_string|&quot;ipt_ULOG: Error building netlink message&bslash;n&quot;
)paren
suffix:semicolon
id|UNLOCK_BH
c_func
(paren
op_amp
id|ulog_lock
)paren
suffix:semicolon
r_return
id|IPT_CONTINUE
suffix:semicolon
)brace
DECL|function|ipt_ulog_checkentry
r_static
r_int
id|ipt_ulog_checkentry
c_func
(paren
r_const
r_char
op_star
id|tablename
comma
r_const
r_struct
id|ipt_entry
op_star
id|e
comma
r_void
op_star
id|targinfo
comma
r_int
r_int
id|targinfosize
comma
r_int
r_int
id|hookmask
)paren
(brace
r_struct
id|ipt_ulog_info
op_star
id|loginfo
op_assign
(paren
r_struct
id|ipt_ulog_info
op_star
)paren
id|targinfo
suffix:semicolon
r_if
c_cond
(paren
id|targinfosize
op_ne
id|IPT_ALIGN
c_func
(paren
r_sizeof
(paren
r_struct
id|ipt_ulog_info
)paren
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: targinfosize %u != 0&bslash;n&quot;
comma
id|targinfosize
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loginfo-&gt;prefix
(braket
r_sizeof
(paren
id|loginfo-&gt;prefix
)paren
op_minus
l_int|1
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: prefix term %i&bslash;n&quot;
comma
id|loginfo-&gt;prefix
(braket
r_sizeof
(paren
id|loginfo-&gt;prefix
)paren
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loginfo-&gt;qthreshold
OG
id|ULOG_MAX_QLEN
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: queue threshold %i &gt; MAX_QLEN&bslash;n&quot;
comma
id|loginfo-&gt;qthreshold
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ipt_ulog_reg
r_static
r_struct
id|ipt_target
id|ipt_ulog_reg
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ULOG&quot;
comma
dot
id|target
op_assign
id|ipt_ulog_target
comma
dot
id|checkentry
op_assign
id|ipt_ulog_checkentry
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init
r_static
r_int
id|__init
id|init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: init module&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlbufsiz
op_ge
l_int|128
op_star
l_int|1024
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Netlink buffer has to be &lt;= 128kB&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* initialize ulog_buffers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ULOG_MAXNLGROUPS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|memset
c_func
(paren
op_amp
id|ulog_buffers
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|ulog_buff_t
)paren
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|ulog_buffers
(braket
id|i
)braket
dot
id|timer
)paren
suffix:semicolon
id|ulog_buffers
(braket
id|i
)braket
dot
id|timer.function
op_assign
id|ulog_timer
suffix:semicolon
id|ulog_buffers
(braket
id|i
)braket
dot
id|timer.data
op_assign
id|i
suffix:semicolon
)brace
id|nflognl
op_assign
id|netlink_kernel_create
c_func
(paren
id|NETLINK_NFLOG
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nflognl
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|ipt_register_target
c_func
(paren
op_amp
id|ipt_ulog_reg
)paren
op_ne
l_int|0
)paren
(brace
id|sock_release
c_func
(paren
id|nflognl-&gt;socket
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fini
r_static
r_void
id|__exit
id|fini
c_func
(paren
r_void
)paren
(brace
id|ulog_buff_t
op_star
id|ub
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ipt_ULOG: cleanup_module&bslash;n&quot;
)paren
suffix:semicolon
id|ipt_unregister_target
c_func
(paren
op_amp
id|ipt_ulog_reg
)paren
suffix:semicolon
id|sock_release
c_func
(paren
id|nflognl-&gt;socket
)paren
suffix:semicolon
multiline_comment|/* remove pending timers and free allocated skb&squot;s */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ULOG_MAXNLGROUPS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ub
op_assign
op_amp
id|ulog_buffers
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|timer_pending
c_func
(paren
op_amp
id|ub-&gt;timer
)paren
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;timer was pending, deleting&bslash;n&quot;
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|ub-&gt;timer
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ub-&gt;skb
)paren
(brace
id|kfree_skb
c_func
(paren
id|ub-&gt;skb
)paren
suffix:semicolon
id|ub-&gt;skb
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
DECL|variable|init
id|module_init
c_func
(paren
id|init
)paren
suffix:semicolon
DECL|variable|fini
id|module_exit
c_func
(paren
id|fini
)paren
suffix:semicolon
eof
