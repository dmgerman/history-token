multiline_comment|/*&n; *              Round robin policy for multipath.&n; *&n; *&n; * Version:&t;$Id: multipath_rr.c,v 1.1.2.2 2004/09/16 07:42:34 elueck Exp $&n; *&n; * Authors:&t;Einar Lueck &lt;elueck@de.ibm.com&gt;&lt;lkml@einar-lueck.de&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/raw.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/ipip.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/ip_mp_alg.h&gt;
DECL|macro|RTprint
mdefine_line|#define RTprint(a...)&t;
singleline_comment|// printk(KERN_DEBUG a)
DECL|macro|MULTIPATH_MAX_CANDIDATES
mdefine_line|#define MULTIPATH_MAX_CANDIDATES 40
DECL|variable|last_used
r_static
r_struct
id|rtable
op_star
id|last_used
op_assign
l_int|NULL
suffix:semicolon
DECL|function|__multipath_remove
r_void
id|__multipath_remove
c_func
(paren
r_struct
id|rtable
op_star
id|rt
)paren
(brace
r_if
c_cond
(paren
id|last_used
op_eq
id|rt
)paren
id|last_used
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|__multipath_selectroute
r_void
id|__multipath_selectroute
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|rtable
op_star
id|first
comma
r_struct
id|rtable
op_star
op_star
id|rp
)paren
(brace
r_struct
id|rtable
op_star
id|nh
comma
op_star
id|result
comma
op_star
id|min_use_cand
op_assign
l_int|NULL
suffix:semicolon
r_int
id|min_use
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* if necessary and possible utilize the old alternative */
r_if
c_cond
(paren
(paren
id|flp-&gt;flags
op_amp
id|FLOWI_FLAG_MULTIPATHOLDROUTE
)paren
op_ne
l_int|0
op_logical_and
id|last_used
op_ne
l_int|NULL
)paren
(brace
id|RTprint
c_func
(paren
id|KERN_CRIT
l_string|&quot;%s: holding route &bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|result
op_assign
id|last_used
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* 1. make sure all alt. nexthops have the same GC related data&n;&t; * 2. determine the new candidate to be returned&n;&t; */
id|result
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|nh
op_assign
id|rcu_dereference
c_func
(paren
id|first
)paren
suffix:semicolon
id|nh
suffix:semicolon
id|nh
op_assign
id|rcu_dereference
c_func
(paren
id|nh-&gt;u.rt_next
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|nh-&gt;u.dst.flags
op_amp
id|DST_BALANCED
)paren
op_ne
l_int|0
op_logical_and
id|multipath_comparekeys
c_func
(paren
op_amp
id|nh-&gt;fl
comma
id|flp
)paren
)paren
(brace
id|nh-&gt;u.dst.lastuse
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|min_use
op_eq
op_minus
l_int|1
op_logical_or
id|nh-&gt;u.dst.__use
OL
id|min_use
)paren
(brace
id|min_use
op_assign
id|nh-&gt;u.dst.__use
suffix:semicolon
id|min_use_cand
op_assign
id|nh
suffix:semicolon
)brace
id|RTprint
c_func
(paren
id|KERN_CRIT
l_string|&quot;%s: found balanced entry&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
)brace
id|result
op_assign
id|min_use_cand
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
id|result
op_assign
id|first
suffix:semicolon
id|out
suffix:colon
id|last_used
op_assign
id|result
suffix:semicolon
id|result-&gt;u.dst.__use
op_increment
suffix:semicolon
op_star
id|rp
op_assign
id|result
suffix:semicolon
)brace
eof
