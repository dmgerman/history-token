multiline_comment|/*&n; * IPVS         An implementation of the IP virtual server support for the&n; *              LINUX operating system.  IPVS is now implemented as a module&n; *              over the Netfilter framework. IPVS can be used to build a&n; *              high-performance and highly available server based on a&n; *              cluster of servers.&n; *&n; * Version:     $Id: ip_vs_sched.c,v 1.13 2003/05/10 03:05:23 wensong Exp $&n; *&n; * Authors:     Wensong Zhang &lt;wensong@linuxvirtualserver.org&gt;&n; *              Peter Kese &lt;peter.kese@ijs.si&gt;&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Changes:&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/string.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;net/ip_vs.h&gt;
multiline_comment|/*&n; *  IPVS scheduler list&n; */
r_static
id|LIST_HEAD
c_func
(paren
id|ip_vs_schedulers
)paren
suffix:semicolon
multiline_comment|/* lock for service table */
DECL|variable|__ip_vs_sched_lock
r_static
id|rwlock_t
id|__ip_vs_sched_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *  Bind a service with a scheduler&n; */
DECL|function|ip_vs_bind_scheduler
r_int
id|ip_vs_bind_scheduler
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
comma
r_struct
id|ip_vs_scheduler
op_star
id|scheduler
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|svc
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_bind_scheduler(): svc arg NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scheduler
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_bind_scheduler(): scheduler arg NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|svc-&gt;scheduler
op_assign
id|scheduler
suffix:semicolon
r_if
c_cond
(paren
id|scheduler-&gt;init_service
)paren
(brace
id|ret
op_assign
id|scheduler
op_member_access_from_pointer
id|init_service
c_func
(paren
id|svc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_bind_scheduler(): init error&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Unbind a service with its scheduler&n; */
DECL|function|ip_vs_unbind_scheduler
r_int
id|ip_vs_unbind_scheduler
c_func
(paren
r_struct
id|ip_vs_service
op_star
id|svc
)paren
(brace
r_struct
id|ip_vs_scheduler
op_star
id|sched
suffix:semicolon
r_if
c_cond
(paren
id|svc
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_unbind_scheduler(): svc arg NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|sched
op_assign
id|svc-&gt;scheduler
suffix:semicolon
r_if
c_cond
(paren
id|sched
op_eq
l_int|NULL
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_unbind_scheduler(): svc isn&squot;t bound&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sched-&gt;done_service
)paren
(brace
r_if
c_cond
(paren
id|sched
op_member_access_from_pointer
id|done_service
c_func
(paren
id|svc
)paren
op_ne
l_int|0
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;ip_vs_unbind_scheduler(): done error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
id|svc-&gt;scheduler
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get scheduler in the scheduler list by name&n; */
DECL|function|ip_vs_sched_getbyname
r_static
r_struct
id|ip_vs_scheduler
op_star
id|ip_vs_sched_getbyname
c_func
(paren
r_const
r_char
op_star
id|sched_name
)paren
(brace
r_struct
id|ip_vs_scheduler
op_star
id|sched
suffix:semicolon
id|IP_VS_DBG
c_func
(paren
l_int|2
comma
l_string|&quot;ip_vs_sched_getbyname(): sched_name &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|sched_name
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|sched
comma
op_amp
id|ip_vs_schedulers
comma
id|n_list
)paren
(brace
multiline_comment|/*&n;&t;&t; * Test and get the modules atomically&n;&t;&t; */
r_if
c_cond
(paren
id|sched-&gt;module
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|sched-&gt;module
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This scheduler is just deleted&n;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|sched_name
comma
id|sched-&gt;name
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* HIT */
id|read_unlock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
r_return
id|sched
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sched-&gt;module
)paren
id|module_put
c_func
(paren
id|sched-&gt;module
)paren
suffix:semicolon
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *  Lookup scheduler and try to load it if it doesn&squot;t exist&n; */
DECL|function|ip_vs_scheduler_get
r_struct
id|ip_vs_scheduler
op_star
id|ip_vs_scheduler_get
c_func
(paren
r_const
r_char
op_star
id|sched_name
)paren
(brace
r_struct
id|ip_vs_scheduler
op_star
id|sched
suffix:semicolon
multiline_comment|/*&n;&t; *  Search for the scheduler by sched_name&n;&t; */
id|sched
op_assign
id|ip_vs_sched_getbyname
c_func
(paren
id|sched_name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  If scheduler not found, load the module and search again&n;&t; */
r_if
c_cond
(paren
id|sched
op_eq
l_int|NULL
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;ip_vs_%s&quot;
comma
id|sched_name
)paren
suffix:semicolon
id|sched
op_assign
id|ip_vs_sched_getbyname
c_func
(paren
id|sched_name
)paren
suffix:semicolon
)brace
r_return
id|sched
suffix:semicolon
)brace
DECL|function|ip_vs_scheduler_put
r_void
id|ip_vs_scheduler_put
c_func
(paren
r_struct
id|ip_vs_scheduler
op_star
id|scheduler
)paren
(brace
r_if
c_cond
(paren
id|scheduler-&gt;module
)paren
id|module_put
c_func
(paren
id|scheduler-&gt;module
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Register a scheduler in the scheduler list&n; */
DECL|function|register_ip_vs_scheduler
r_int
id|register_ip_vs_scheduler
c_func
(paren
r_struct
id|ip_vs_scheduler
op_star
id|scheduler
)paren
(brace
r_struct
id|ip_vs_scheduler
op_star
id|sched
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scheduler
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;register_ip_vs_scheduler(): NULL arg&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|scheduler-&gt;name
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;register_ip_vs_scheduler(): NULL scheduler_name&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* increase the module use count */
id|ip_vs_use_count_inc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Make sure that the scheduler with this name doesn&squot;t exist&n;&t; *  in the scheduler list.&n;&t; */
id|sched
op_assign
id|ip_vs_sched_getbyname
c_func
(paren
id|scheduler-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sched
)paren
(brace
id|ip_vs_scheduler_put
c_func
(paren
id|sched
)paren
suffix:semicolon
id|ip_vs_use_count_dec
c_func
(paren
)paren
suffix:semicolon
id|IP_VS_ERR
c_func
(paren
l_string|&quot;register_ip_vs_scheduler(): [%s] scheduler &quot;
l_string|&quot;already existed in the system&bslash;n&quot;
comma
id|scheduler-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|write_lock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scheduler-&gt;n_list.next
op_ne
op_amp
id|scheduler-&gt;n_list
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
id|ip_vs_use_count_dec
c_func
(paren
)paren
suffix:semicolon
id|IP_VS_ERR
c_func
(paren
l_string|&quot;register_ip_vs_scheduler(): [%s] scheduler &quot;
l_string|&quot;already linked&bslash;n&quot;
comma
id|scheduler-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Add it into the d-linked scheduler list&n;&t; */
id|list_add
c_func
(paren
op_amp
id|scheduler-&gt;n_list
comma
op_amp
id|ip_vs_schedulers
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
id|IP_VS_INFO
c_func
(paren
l_string|&quot;[%s] scheduler registered.&bslash;n&quot;
comma
id|scheduler-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Unregister a scheduler from the scheduler list&n; */
DECL|function|unregister_ip_vs_scheduler
r_int
id|unregister_ip_vs_scheduler
c_func
(paren
r_struct
id|ip_vs_scheduler
op_star
id|scheduler
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|scheduler
)paren
(brace
id|IP_VS_ERR
c_func
(paren
l_string|&quot;unregister_ip_vs_scheduler(): NULL arg&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|write_lock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scheduler-&gt;n_list.next
op_eq
op_amp
id|scheduler-&gt;n_list
)paren
(brace
id|write_unlock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
id|IP_VS_ERR
c_func
(paren
l_string|&quot;unregister_ip_vs_scheduler(): [%s] scheduler &quot;
l_string|&quot;is not in the list. failed&bslash;n&quot;
comma
id|scheduler-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Remove it from the d-linked scheduler list&n;&t; */
id|list_del
c_func
(paren
op_amp
id|scheduler-&gt;n_list
)paren
suffix:semicolon
id|write_unlock_bh
c_func
(paren
op_amp
id|__ip_vs_sched_lock
)paren
suffix:semicolon
multiline_comment|/* decrease the module use count */
id|ip_vs_use_count_dec
c_func
(paren
)paren
suffix:semicolon
id|IP_VS_INFO
c_func
(paren
l_string|&quot;[%s] scheduler unregistered.&bslash;n&quot;
comma
id|scheduler-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
