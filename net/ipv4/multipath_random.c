multiline_comment|/*&n; *              Random policy for multipath.&n; *&n; *&n; * Version:&t;$Id: multipath_random.c,v 1.1.2.3 2004/09/21 08:42:11 elueck Exp $&n; *&n; * Authors:&t;Einar Lueck &lt;elueck@de.ibm.com&gt;&lt;lkml@einar-lueck.de&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
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
DECL|macro|MULTIPATH_MAX_CANDIDATES
mdefine_line|#define MULTIPATH_MAX_CANDIDATES 40
multiline_comment|/* interface to random number generation */
DECL|variable|RANDOM_SEED
r_static
r_int
r_int
id|RANDOM_SEED
op_assign
l_int|93186752
suffix:semicolon
DECL|function|random
r_static
r_inline
r_int
r_int
id|random
c_func
(paren
r_int
r_int
id|ubound
)paren
(brace
r_static
r_int
r_int
id|a
op_assign
l_int|1588635695
comma
id|q
op_assign
l_int|2
comma
id|r
op_assign
l_int|1117695901
suffix:semicolon
id|RANDOM_SEED
op_assign
id|a
op_star
(paren
id|RANDOM_SEED
op_mod
id|q
)paren
op_minus
id|r
op_star
(paren
id|RANDOM_SEED
op_div
id|q
)paren
suffix:semicolon
r_return
id|RANDOM_SEED
op_mod
id|ubound
suffix:semicolon
)brace
DECL|function|random_select_route
r_static
r_void
id|random_select_route
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
id|rt
suffix:semicolon
r_struct
id|rtable
op_star
id|decision
suffix:semicolon
r_int
r_char
id|candidate_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* count all candidate */
r_for
c_loop
(paren
id|rt
op_assign
id|rcu_dereference
c_func
(paren
id|first
)paren
suffix:semicolon
id|rt
suffix:semicolon
id|rt
op_assign
id|rcu_dereference
c_func
(paren
id|rt-&gt;u.rt_next
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|rt-&gt;u.dst.flags
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
id|rt-&gt;fl
comma
id|flp
)paren
)paren
op_increment
id|candidate_count
suffix:semicolon
)brace
multiline_comment|/* choose a random candidate */
id|decision
op_assign
id|first
suffix:semicolon
r_if
c_cond
(paren
id|candidate_count
OG
l_int|1
)paren
(brace
r_int
r_char
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|candidate_no
op_assign
(paren
r_int
r_char
)paren
id|random
c_func
(paren
id|candidate_count
)paren
suffix:semicolon
multiline_comment|/* find chosen candidate and adjust GC data for all candidates&n;&t;&t; * to ensure they stay in cache&n;&t;&t; */
r_for
c_loop
(paren
id|rt
op_assign
id|first
suffix:semicolon
id|rt
suffix:semicolon
id|rt
op_assign
id|rt-&gt;u.rt_next
)paren
(brace
r_if
c_cond
(paren
(paren
id|rt-&gt;u.dst.flags
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
id|rt-&gt;fl
comma
id|flp
)paren
)paren
(brace
id|rt-&gt;u.dst.lastuse
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|candidate_no
)paren
id|decision
op_assign
id|rt
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|candidate_count
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
)brace
id|decision-&gt;u.dst.__use
op_increment
suffix:semicolon
op_star
id|rp
op_assign
id|decision
suffix:semicolon
)brace
DECL|variable|random_ops
r_static
r_struct
id|ip_mp_alg_ops
id|random_ops
op_assign
(brace
dot
id|mp_alg_select_route
op_assign
id|random_select_route
comma
)brace
suffix:semicolon
DECL|function|random_init
r_static
r_int
id|__init
id|random_init
c_func
(paren
r_void
)paren
(brace
r_return
id|multipath_alg_register
c_func
(paren
op_amp
id|random_ops
comma
id|IP_MP_ALG_RANDOM
)paren
suffix:semicolon
)brace
DECL|function|random_exit
r_static
r_void
id|__exit
id|random_exit
c_func
(paren
r_void
)paren
(brace
id|multipath_alg_unregister
c_func
(paren
op_amp
id|random_ops
comma
id|IP_MP_ALG_RANDOM
)paren
suffix:semicolon
)brace
DECL|variable|random_init
id|module_init
c_func
(paren
id|random_init
)paren
suffix:semicolon
DECL|variable|random_exit
id|module_exit
c_func
(paren
id|random_exit
)paren
suffix:semicolon
eof
