multiline_comment|/*&n; *&t;Device event handling&n; *&t;Linux ethernet bridge&n; *&n; *&t;Authors:&n; *&t;Lennert Buytenhek&t;&t;&lt;buytenh@gnu.org&gt;&n; *&n; *&t;$Id: br_notify.c,v 1.2 2000/02/21 15:51:34 davem Exp $&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;br_private.h&quot;
r_static
r_int
id|br_device_event
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
suffix:semicolon
DECL|variable|br_device_notifier
r_struct
id|notifier_block
id|br_device_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|br_device_event
)brace
suffix:semicolon
DECL|function|br_device_event
r_static
r_int
id|br_device_event
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
suffix:semicolon
r_struct
id|net_bridge_port
op_star
id|p
suffix:semicolon
r_struct
id|net_bridge
op_star
id|br
suffix:semicolon
id|dev
op_assign
id|ptr
suffix:semicolon
id|p
op_assign
id|dev-&gt;br_port
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
id|NOTIFY_DONE
suffix:semicolon
id|br
op_assign
id|p-&gt;br
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
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_fdb_changeaddr
c_func
(paren
id|p
comma
id|dev-&gt;dev_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|br-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
id|br_stp_recalculate_bridge_id
c_func
(paren
id|br
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_CHANGEMTU
suffix:colon
id|br-&gt;dev-&gt;mtu
op_assign
id|br_min_mtu
c_func
(paren
id|br
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NETDEV_DOWN
suffix:colon
r_if
c_cond
(paren
id|br-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_disable_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UP
suffix:colon
r_if
c_cond
(paren
id|br-&gt;dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
id|spin_lock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
id|br_stp_enable_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|br-&gt;lock
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|NETDEV_UNREGISTER
suffix:colon
id|br_del_if
c_func
(paren
id|br
comma
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
eof
