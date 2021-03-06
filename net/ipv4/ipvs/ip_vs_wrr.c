multiline_comment|/*&n; * IPVS:        Weighted Round-Robin Scheduling module&n; *&n; * Version:     $Id: ip_vs_wrr.c,v 1.12 2002/09/15 08:14:08 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *     Wensong Zhang            :     changed the ip_vs_wrr_schedule to return dest&n; *     Wensong Zhang            :     changed some comestics things for debugging&n; *     Wensong Zhang            :     changed for the d-linked destination list&n; *     Wensong Zhang            :     added the ip_vs_wrr_update_svc&n; *     Julian Anastasov         :     fixed the bug of returning destination&n; *                                    with weight 0 when all weights are zero&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/*&n; * current destination pointer for weighted round-robin scheduling&n; */
DECL|struct|ip_vs_wrr_mark
r_struct
id|ip_vs_wrr_mark
(brace
DECL|member|cl
r_struct
id|list_head
op_star
id|cl
suffix:semicolon
multiline_comment|/* current list head */
DECL|member|cw
r_int
id|cw
suffix:semicolon
multiline_comment|/* current weight */
DECL|member|mw
r_int
id|mw
suffix:semicolon
multiline_comment|/* maximum weight */
DECL|member|di
r_int
id|di
suffix:semicolon
multiline_comment|/* decreasing interval */
)brace
suffix:semicolon
multiline_comment|/*&n; *    Get the gcd of server weights&n; */
DECL|function|gcd
r_static
r_int
id|gcd
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_int
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
id|a
op_mod
id|b
)paren
)paren
(brace
id|a
op_assign
id|b
suffix:semicolon
id|b
op_assign
id|c
suffix:semicolon
)brace
r_return
id|b
suffix:semicolon
)brace
DECL|function|ip_vs_wrr_gcd_weight
r_static
r_int
id|ip_vs_wrr_gcd_weight
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|dest
suffix:semicolon
r_int
id|weight
suffix:semicolon
r_int
id|g
op_assign
l_int|0
suffix:semicolon
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
id|weight
op_assign
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
suffix:semicolon
r_if
c_cond
(paren
id|weight
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|g
OG
l_int|0
)paren
id|g
op_assign
id|gcd
c_func
(paren
id|weight
comma
id|g
)paren
suffix:semicolon
r_else
id|g
op_assign
id|weight
suffix:semicolon
)brace
)brace
r_return
id|g
ques
c_cond
id|g
suffix:colon
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *    Get the maximum weight of the service destinations.&n; */
DECL|function|ip_vs_wrr_max_weight
r_static
r_int
id|ip_vs_wrr_max_weight
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_dest
op_star
id|dest
suffix:semicolon
r_int
id|weight
op_assign
l_int|0
suffix:semicolon
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
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
OG
id|weight
)paren
id|weight
op_assign
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
suffix:semicolon
)brace
r_return
id|weight
suffix:semicolon
)brace
DECL|function|ip_vs_wrr_init_svc
r_static
r_int
id|ip_vs_wrr_init_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_wrr_mark
op_star
id|mark
suffix:semicolon
multiline_comment|/*&n;&t; *    Allocate the mark variable for WRR scheduling&n;&t; */
id|mark
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ip_vs_wrr_mark
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mark
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_wrr_init_svc(): no memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|mark-&gt;cl
op_assign
op_amp
id|svc-&gt;destinations
suffix:semicolon
id|mark-&gt;cw
op_assign
l_int|0
suffix:semicolon
id|mark-&gt;mw
op_assign
id|ip_vs_wrr_max_weight
c_func
(paren
id|svc
)paren
suffix:semicolon
id|mark-&gt;di
op_assign
id|ip_vs_wrr_gcd_weight
c_func
(paren
id|svc
)paren
suffix:semicolon
id|svc-&gt;sched_data
op_assign
id|mark
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_vs_wrr_done_svc
r_static
r_int
id|ip_vs_wrr_done_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
multiline_comment|/*&n;&t; *    Release the mark variable&n;&t; */
id|kfree
c_func
(paren
id|svc-&gt;sched_data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_vs_wrr_update_svc
r_static
r_int
id|ip_vs_wrr_update_svc
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_wrr_mark
op_star
id|mark
op_assign
id|svc-&gt;sched_data
suffix:semicolon
id|mark-&gt;cl
op_assign
op_amp
id|svc-&gt;destinations
suffix:semicolon
id|mark-&gt;mw
op_assign
id|ip_vs_wrr_max_weight
c_func
(paren
id|svc
)paren
suffix:semicolon
id|mark-&gt;di
op_assign
id|ip_vs_wrr_gcd_weight
c_func
(paren
id|svc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mark-&gt;cw
OG
id|mark-&gt;mw
)paren
id|mark-&gt;cw
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *    Weighted Round-Robin Scheduling&n; */
r_static
r_struct
id|ip_vs_dest
op_star
DECL|function|ip_vs_wrr_schedule
id|ip_vs_wrr_schedule
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
suffix:semicolon
r_struct
id|ip_vs_wrr_mark
op_star
id|mark
op_assign
id|svc-&gt;sched_data
suffix:semicolon
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;ip_vs_wrr_schedule(): Scheduling...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This loop will always terminate, because mark-&gt;cw in (0, max_weight]&n;&t; * and at least one server has its weight equal to max_weight.&n;&t; */
id|write_lock
c_func
(paren
op_amp
id|svc-&gt;sched_lock
)paren
suffix:semicolon
id|p
op_assign
id|mark-&gt;cl
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|mark-&gt;cl
op_eq
op_amp
id|svc-&gt;destinations
)paren
(brace
multiline_comment|/* it is at the head of the destination list */
r_if
c_cond
(paren
id|mark-&gt;cl
op_eq
id|mark-&gt;cl-&gt;next
)paren
(brace
multiline_comment|/* no dest entry */
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|mark-&gt;cl
op_assign
id|svc-&gt;destinations.next
suffix:semicolon
id|mark-&gt;cw
op_sub_assign
id|mark-&gt;di
suffix:semicolon
r_if
c_cond
(paren
id|mark-&gt;cw
op_le
l_int|0
)paren
(brace
id|mark-&gt;cw
op_assign
id|mark-&gt;mw
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Still zero, which means no available servers.&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|mark-&gt;cw
op_eq
l_int|0
)paren
(brace
id|mark-&gt;cl
op_assign
op_amp
id|svc-&gt;destinations
suffix:semicolon
id|IP_VS_INFO
c_func
(paren
l_string|&quot;ip_vs_wrr_schedule(): &quot;
l_string|&quot;no available servers&bslash;n&quot;
)paren
suffix:semicolon
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
r_else
id|mark-&gt;cl
op_assign
id|mark-&gt;cl-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|mark-&gt;cl
op_ne
op_amp
id|svc-&gt;destinations
)paren
(brace
multiline_comment|/* not at the head of the list */
id|dest
op_assign
id|list_entry
c_func
(paren
id|mark-&gt;cl
comma
r_struct
id|ip_vs_dest
comma
id|n_list
)paren
suffix:semicolon
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
op_ge
id|mark-&gt;cw
)paren
(brace
multiline_comment|/* got it */
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mark-&gt;cl
op_eq
id|p
op_logical_and
id|mark-&gt;cw
op_eq
id|mark-&gt;di
)paren
(brace
multiline_comment|/* back to the start, and no dest is found.&n;&t;&t;&t;   It is only possible when all dests are OVERLOADED */
id|dest
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|IP_VS_DBG
c_func
(paren
l_int|6
comma
l_string|&quot;WRR: server %u.%u.%u.%u:%u &quot;
l_string|&quot;activeconns %d refcnt %d weight %d&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|dest-&gt;addr
)paren
comma
id|ntohs
c_func
(paren
id|dest-&gt;port
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;activeconns
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;refcnt
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|dest-&gt;weight
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|svc-&gt;sched_lock
)paren
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|variable|ip_vs_wrr_scheduler
r_static
r_struct
id|ip_vs_scheduler
id|ip_vs_wrr_scheduler
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;wrr&quot;
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
id|ip_vs_wrr_init_svc
comma
dot
id|done_service
op_assign
id|ip_vs_wrr_done_svc
comma
dot
id|update_service
op_assign
id|ip_vs_wrr_update_svc
comma
dot
id|schedule
op_assign
id|ip_vs_wrr_schedule
comma
)brace
suffix:semicolon
DECL|function|ip_vs_wrr_init
r_static
r_int
id|__init
id|ip_vs_wrr_init
c_func
(paren
r_void
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|ip_vs_wrr_scheduler.n_list
)paren
suffix:semicolon
r_return
id|register_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_wrr_scheduler
)paren
suffix:semicolon
)brace
DECL|function|ip_vs_wrr_cleanup
r_static
r_void
id|__exit
id|ip_vs_wrr_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_ip_vs_scheduler
c_func
(paren
op_amp
id|ip_vs_wrr_scheduler
)paren
suffix:semicolon
)brace
DECL|variable|ip_vs_wrr_init
id|module_init
c_func
(paren
id|ip_vs_wrr_init
)paren
suffix:semicolon
DECL|variable|ip_vs_wrr_cleanup
id|module_exit
c_func
(paren
id|ip_vs_wrr_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
