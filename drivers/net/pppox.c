multiline_comment|/** -*- linux-c -*- ***********************************************************&n; * Linux PPP over X/Ethernet (PPPoX/PPPoE) Sockets&n; *&n; * PPPoX --- Generic PPP encapsulation socket family&n; * PPPoE --- PPP over Ethernet (RFC 2516)&n; *&n; *&n; * Version:&t;0.5.2&n; *&n; * Author:&t;Michal Ostrowski &lt;mostrows@speakeasy.net&gt;&n; *&n; * 051000 :&t;Initialization cleanup&n; *&n; * License:&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/if_pppox.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/if_ppp.h&gt;
macro_line|#include &lt;linux/ppp_channel.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|pppox_protos
r_static
r_struct
id|pppox_proto
op_star
id|pppox_protos
(braket
id|PX_MAX_PROTO
op_plus
l_int|1
)braket
suffix:semicolon
DECL|function|register_pppox_proto
r_int
id|register_pppox_proto
c_func
(paren
r_int
id|proto_num
comma
r_struct
id|pppox_proto
op_star
id|pp
)paren
(brace
r_if
c_cond
(paren
id|proto_num
template_param
id|PX_MAX_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pppox_protos
(braket
id|proto_num
)braket
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|pppox_protos
(braket
id|proto_num
)braket
op_assign
id|pp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_pppox_proto
r_void
id|unregister_pppox_proto
c_func
(paren
r_int
id|proto_num
)paren
(brace
r_if
c_cond
(paren
id|proto_num
op_ge
l_int|0
op_logical_and
id|proto_num
op_le
id|PX_MAX_PROTO
)paren
id|pppox_protos
(braket
id|proto_num
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|pppox_unbind_sock
r_void
id|pppox_unbind_sock
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
multiline_comment|/* Clear connection to ppp device, if attached. */
r_if
c_cond
(paren
id|sk-&gt;sk_state
op_amp
(paren
id|PPPOX_BOUND
op_or
id|PPPOX_ZOMBIE
)paren
)paren
(brace
id|ppp_unregister_channel
c_func
(paren
op_amp
id|pppox_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|chan
)paren
suffix:semicolon
id|sk-&gt;sk_state
op_assign
id|PPPOX_DEAD
suffix:semicolon
)brace
)brace
DECL|variable|register_pppox_proto
id|EXPORT_SYMBOL
c_func
(paren
id|register_pppox_proto
)paren
suffix:semicolon
DECL|variable|unregister_pppox_proto
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_pppox_proto
)paren
suffix:semicolon
DECL|variable|pppox_unbind_sock
id|EXPORT_SYMBOL
c_func
(paren
id|pppox_unbind_sock
)paren
suffix:semicolon
DECL|function|pppox_ioctl
r_static
r_int
id|pppox_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|sock-&gt;sk
suffix:semicolon
r_struct
id|pppox_sock
op_star
id|po
op_assign
id|pppox_sk
c_func
(paren
id|sk
)paren
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|PPPIOCGCHAN
suffix:colon
(brace
r_int
id|index
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOTCONN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sk-&gt;sk_state
op_amp
id|PPPOX_CONNECTED
)paren
)paren
r_break
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|index
op_assign
id|ppp_channel_index
c_func
(paren
op_amp
id|po-&gt;chan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|index
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_break
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|sk-&gt;sk_state
op_or_assign
id|PPPOX_BOUND
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|pppox_protos
(braket
id|sk-&gt;sk_protocol
)braket
op_member_access_from_pointer
id|ioctl
)paren
id|rc
op_assign
id|pppox_protos
(braket
id|sk-&gt;sk_protocol
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|sock
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|pppox_create
r_static
r_int
id|pppox_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
(brace
r_int
id|rc
op_assign
op_minus
id|EPROTOTYPE
suffix:semicolon
r_if
c_cond
(paren
id|protocol
template_param
id|PX_MAX_PROTO
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pppox_protos
(braket
id|protocol
)braket
op_logical_or
op_logical_neg
id|try_module_get
c_func
(paren
id|pppox_protos
(braket
id|protocol
)braket
op_member_access_from_pointer
id|owner
)paren
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
id|pppox_protos
(braket
id|protocol
)braket
op_member_access_from_pointer
id|create
c_func
(paren
id|sock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
multiline_comment|/* We get to set the ioctl handler. */
multiline_comment|/* For everything else, pppox is just a shell. */
id|sock-&gt;ops-&gt;ioctl
op_assign
id|pppox_ioctl
suffix:semicolon
)brace
id|module_put
c_func
(paren
id|pppox_protos
(braket
id|protocol
)braket
op_member_access_from_pointer
id|owner
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|pppox_proto_family
r_static
r_struct
id|net_proto_family
id|pppox_proto_family
op_assign
(brace
dot
id|family
op_assign
id|PF_PPPOX
comma
dot
id|create
op_assign
id|pppox_create
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|pppox_init
r_static
r_int
id|__init
id|pppox_init
c_func
(paren
r_void
)paren
(brace
r_return
id|sock_register
c_func
(paren
op_amp
id|pppox_proto_family
)paren
suffix:semicolon
)brace
DECL|function|pppox_exit
r_static
r_void
id|__exit
id|pppox_exit
c_func
(paren
r_void
)paren
(brace
id|sock_unregister
c_func
(paren
id|PF_PPPOX
)paren
suffix:semicolon
)brace
DECL|variable|pppox_init
id|module_init
c_func
(paren
id|pppox_init
)paren
suffix:semicolon
DECL|variable|pppox_exit
id|module_exit
c_func
(paren
id|pppox_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michal Ostrowski &lt;mostrows@speakeasy.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PPP over Ethernet driver (generic socket layer)&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
