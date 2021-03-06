multiline_comment|/*&n; *  ebtable_broute&n; *&n; *&t;Authors:&n; *&t;Bart De Schuymer &lt;bdschuym@pandora.be&gt;&n; *&n; *  April, 2002&n; *&n; *  This table lets you choose between routing and bridging for frames&n; *  entering on a bridge enslaved nic. This table is traversed before any&n; *  other ebtables table. See net/bridge/br_input.c.&n; */
macro_line|#include &lt;linux/netfilter_bridge/ebtables.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
multiline_comment|/* EBT_ACCEPT means the frame will be bridged&n; * EBT_DROP means the frame will be routed&n; */
DECL|variable|initial_chain
r_static
r_struct
id|ebt_entries
id|initial_chain
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;BROUTING&quot;
comma
dot
id|policy
op_assign
id|EBT_ACCEPT
comma
)brace
suffix:semicolon
DECL|variable|initial_table
r_static
r_struct
id|ebt_replace
id|initial_table
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;broute&quot;
comma
dot
id|valid_hooks
op_assign
l_int|1
op_lshift
id|NF_BR_BROUTING
comma
dot
id|entries_size
op_assign
r_sizeof
(paren
r_struct
id|ebt_entries
)paren
comma
dot
id|hook_entry
op_assign
(brace
(braket
id|NF_BR_BROUTING
)braket
op_assign
op_amp
id|initial_chain
comma
)brace
comma
dot
id|entries
op_assign
(paren
r_char
op_star
)paren
op_amp
id|initial_chain
comma
)brace
suffix:semicolon
DECL|function|check
r_static
r_int
id|check
c_func
(paren
r_const
r_struct
id|ebt_table_info
op_star
id|info
comma
r_int
r_int
id|valid_hooks
)paren
(brace
r_if
c_cond
(paren
id|valid_hooks
op_amp
op_complement
(paren
l_int|1
op_lshift
id|NF_BR_BROUTING
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|broute_table
r_static
r_struct
id|ebt_table
id|broute_table
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;broute&quot;
comma
dot
id|table
op_assign
op_amp
id|initial_table
comma
dot
id|valid_hooks
op_assign
l_int|1
op_lshift
id|NF_BR_BROUTING
comma
dot
id|lock
op_assign
id|RW_LOCK_UNLOCKED
comma
dot
id|check
op_assign
id|check
comma
dot
id|me
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|ebt_broute
r_static
r_int
id|ebt_broute
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ebt_do_table
c_func
(paren
id|NF_BR_BROUTING
comma
id|pskb
comma
(paren
op_star
id|pskb
)paren
op_member_access_from_pointer
id|dev
comma
l_int|NULL
comma
op_amp
id|broute_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|NF_DROP
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* route it */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* bridge it */
)brace
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
id|ret
suffix:semicolon
id|ret
op_assign
id|ebt_register_table
c_func
(paren
op_amp
id|broute_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* see br_input.c */
id|br_should_route_hook
op_assign
id|ebt_broute
suffix:semicolon
r_return
id|ret
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
id|br_should_route_hook
op_assign
l_int|NULL
suffix:semicolon
id|synchronize_net
c_func
(paren
)paren
suffix:semicolon
id|ebt_unregister_table
c_func
(paren
op_amp
id|broute_table
)paren
suffix:semicolon
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
