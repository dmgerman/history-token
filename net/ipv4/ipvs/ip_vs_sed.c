multiline_comment|/*&n; * IPVS:        Shortest Expected Delay scheduling module&n; *&n; * Version:     $Id: ip_vs_sed.c,v 1.1 2003/05/10 03:06:08 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
multiline_comment|/*&n; * The SED algorithm attempts to minimize each job&squot;s expected delay until&n; * completion. The expected delay that the job will experience is&n; * (Ci + 1) / Ui if sent to the ith server, in which Ci is the number of&n; * jobs on the the ith server and Ui is the fixed service rate (weight) of&n; * the ith server. The SED algorithm adopts a greedy policy that each does&n; * what is in its own best interest, i.e. to join the queue which would&n; * minimize its expected delay of completion.&n; *&n; * See the following paper for more information:&n; * A. Weinrib and S. Shenker, Greed is not enough: Adaptive load sharing&n; * in large heterogeneous systems. In Proceedings IEEE INFOCOM&squot;88,&n; * pages 986-994, 1988.&n; *&n; * Thanks must go to Marko Buuri &lt;marko@buuri.name&gt; for talking SED to me.&n; *&n; * The difference between SED and WLC is that SED includes the incoming&n; * job in the cost function (the increment of 1). SED may outperform&n; * WLC, while scheduling big jobs under larger heterogeneous systems&n; * (the server weight varies a lot).&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
r_static
r_int
DECL|function|ip_vs_sed_init_svc
id|ip_vs_sed_init_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ip_vs_sed_done_svc
id|ip_vs_sed_done_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ip_vs_sed_update_svc
id|ip_vs_sed_update_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|ip_vs_sed_dest_overhead
id|ip_vs_sed_dest_overhead
c_func
(paren
r_struct
id|ip_vs_dest
op_star
id|dest
)paren
(brace
multiline_comment|/*&n;&t; * We only use the active connection number in the cost&n;&t; * calculation here.&n;&t; */
r_return
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;activeconns
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Weighted Least Connection scheduling&n; */
r_static
r_struct
id|ip_vs_dest
op_star
DECL|function|ip_vs_sed_schedule
id|ip_vs_sed_schedule
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
comma
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|dest
comma
op_star
id|least
suffix:semicolon
r_int
r_int
id|loh
comma
id|doh
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;ip_vs_sed_schedule(): Scheduling...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We calculate the load of each dest server as follows:&n;&t; *&t;(server expected overhead) / dest-&gt;weight&n;&t; *&n;&t; * Remember -- no floats in kernel mode!!!&n;&t; * The comparison of h1*w2 &gt; h2*w1 is equivalent to that of&n;&t; *&t;&t;  h1/w1 &gt; h2/w2&n;&t; * if every weight is larger than zero.&n;&t; *&n;&t; * The server with weight=0 is quiesced and will not receive any&n;&t; * new connections.&n;&t; */
id|list_for_each_entry
c_func
(paren
id|dest
comma
op_amp
id|svc-&gt;destinations
comma
id|n_list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|dest-&gt;flags
op_amp
id|IP_VS_DEST_F_OVERLOAD
)paren
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
OG
l_int|0
)paren
(brace
id|least
op_assign
id|dest
suffix:semicolon
id|loh
op_assign
id|ip_vs_sed_dest_overhead
c_func
(paren
id|least
)paren
suffix:semicolon
r_goto
id|nextstage
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *    Find the destination with the least load.&n;&t; */
id|nextstage
suffix:colon
id|list_for_each_entry_continue
c_func
(paren
id|dest
comma
op_amp
id|svc-&gt;destinations
comma
id|n_list
)paren
(brace
r_if
c_cond
(paren
id|dest-&gt;flags
op_amp
id|IP_VS_DEST_F_OVERLOAD
)paren
r_continue
suffix:semicolon
id|doh
op_assign
id|ip_vs_sed_dest_overhead
c_func
(paren
id|dest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loh
op_star
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
OG
id|doh
op_star
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;weight
)paren
)paren
(brace
id|least
op_assign
id|dest
suffix:semicolon
id|loh
op_assign
id|doh
suffix:semicolon
)brace
)brace
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;SED: server %u.%u.%u.%u:%u &quot;
l_string|&quot;activeconns %d refcnt %d weight %d overhead %d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|least-&gt;addr
)paren
comma
id|ntohs
c_func
(paren
id|least-&gt;port
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;activeconns
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;refcnt
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|least-&gt;weight
)paren
comma
id|loh
)paren
suffix:semicolon
r_return
id|least
suffix:semicolon
)brace
DECL|variable|ip_vs_sed_scheduler
r_static
r_struct
id|ip_vs_scheduler
id|ip_vs_sed_scheduler
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sed&quot;
comma
dot
id|refcnt
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|init_service
op_assign
id|ip_vs_sed_init_svc
comma
dot
id|done_service
op_assign
id|ip_vs_sed_done_svc
comma
dot
id|update_service
op_assign
id|ip_vs_sed_update_svc
comma
dot
id|schedule
op_assign
id|ip_vs_sed_schedule
comma
)brace
suffix:semicolon
DECL|function|ip_vs_sed_init
r_static
r_int
id|__init
id|ip_vs_sed_init
c_func
(paren
r_void
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ip_vs_sed_scheduler.n_list
)paren
suffix:semicolon
r_return
id|register_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_sed_scheduler
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_sed_cleanup
r_static
r_void
id|__exit
id|ip_vs_sed_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_sed_scheduler
)paren
suffix:semicolon
)brace
DECL|variable|ip_vs_sed_init
id|module_init
c_func
(paren
id|ip_vs_sed_init
)paren
suffix:semicolon
DECL|variable|ip_vs_sed_cleanup
id|module_exit
c_func
(paren
id|ip_vs_sed_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
