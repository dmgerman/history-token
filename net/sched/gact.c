multiline_comment|/*&n; * net/sched/gact.c&t;Generic actions&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * copyright &t;Jamal Hadi Salim (2002-4)&n; *&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/rtnetlink.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;linux/tc_act/tc_gact.h&gt;
macro_line|#include &lt;net/tc_act/tc_gact.h&gt;
multiline_comment|/* use generic hash table */
DECL|macro|MY_TAB_SIZE
mdefine_line|#define MY_TAB_SIZE&t;16
DECL|macro|MY_TAB_MASK
mdefine_line|#define MY_TAB_MASK&t;15
DECL|variable|idx_gen
r_static
id|u32
id|idx_gen
suffix:semicolon
DECL|variable|tcf_gact_ht
r_static
r_struct
id|tcf_gact
op_star
id|tcf_gact_ht
(braket
id|MY_TAB_SIZE
)braket
suffix:semicolon
DECL|variable|gact_lock
r_static
id|rwlock_t
id|gact_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* ovewrride the defaults */
DECL|macro|tcf_st
mdefine_line|#define tcf_st  tcf_gact
DECL|macro|tc_st
mdefine_line|#define tc_st  tc_gact
DECL|macro|tcf_t_lock
mdefine_line|#define tcf_t_lock   gact_lock
DECL|macro|tcf_ht
mdefine_line|#define tcf_ht tcf_gact_ht
DECL|macro|CONFIG_NET_ACT_INIT
mdefine_line|#define CONFIG_NET_ACT_INIT 1
macro_line|#include &lt;net/pkt_act.h&gt;
macro_line|#ifdef CONFIG_GACT_PROB
DECL|typedef|g_rand
r_typedef
r_int
(paren
op_star
id|g_rand
)paren
(paren
r_struct
id|tcf_gact
op_star
id|p
)paren
suffix:semicolon
r_static
r_int
DECL|function|gact_net_rand
id|gact_net_rand
c_func
(paren
r_struct
id|tcf_gact
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|net_random
c_func
(paren
)paren
op_mod
id|p-&gt;pval
)paren
r_return
id|p-&gt;action
suffix:semicolon
r_return
id|p-&gt;paction
suffix:semicolon
)brace
r_static
r_int
DECL|function|gact_determ
id|gact_determ
c_func
(paren
r_struct
id|tcf_gact
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;bstats.packets
op_mod
id|p-&gt;pval
)paren
r_return
id|p-&gt;action
suffix:semicolon
r_return
id|p-&gt;paction
suffix:semicolon
)brace
DECL|variable|gact_rand
r_static
id|g_rand
id|gact_rand
(braket
id|MAX_RAND
)braket
op_assign
(brace
l_int|NULL
comma
id|gact_net_rand
comma
id|gact_determ
)brace
suffix:semicolon
macro_line|#endif
r_static
r_int
DECL|function|tcf_gact_init
id|tcf_gact_init
c_func
(paren
r_struct
id|rtattr
op_star
id|rta
comma
r_struct
id|rtattr
op_star
id|est
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|ovr
comma
r_int
id|bind
)paren
(brace
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_GACT_MAX
)braket
suffix:semicolon
r_struct
id|tc_gact
op_star
id|parm
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
r_struct
id|tc_gact_p
op_star
id|p_parm
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_struct
id|tcf_gact
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|size
op_assign
r_sizeof
(paren
op_star
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_GACT_MAX
comma
id|RTA_DATA
c_func
(paren
id|rta
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|a
op_logical_or
l_int|NULL
op_eq
id|tb
(braket
id|TCA_GACT_PARMS
op_minus
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;BUG: tcf_gact_init called with NULL params&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|parm
op_assign
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_GACT_PARMS
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
r_if
c_cond
(paren
l_int|NULL
op_ne
id|tb
(braket
id|TCA_GACT_PROB
op_minus
l_int|1
)braket
)paren
(brace
id|p_parm
op_assign
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_GACT_PROB
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
id|p
op_assign
id|tcf_hash_check
c_func
(paren
id|parm
comma
id|a
comma
id|ovr
comma
id|bind
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|p
)paren
(brace
id|p
op_assign
id|tcf_hash_create
c_func
(paren
id|parm
comma
id|est
comma
id|a
comma
id|size
comma
id|ovr
comma
id|bind
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|p
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;refcnt
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
r_goto
id|override
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ovr
)paren
(brace
id|override
suffix:colon
id|p-&gt;action
op_assign
id|parm-&gt;action
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
r_if
c_cond
(paren
l_int|NULL
op_ne
id|p_parm
)paren
(brace
id|p-&gt;paction
op_assign
id|p_parm-&gt;paction
suffix:semicolon
id|p-&gt;pval
op_assign
id|p_parm-&gt;pval
suffix:semicolon
id|p-&gt;ptype
op_assign
id|p_parm-&gt;ptype
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;paction
op_assign
id|p-&gt;pval
op_assign
id|p-&gt;ptype
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_gact_cleanup
id|tcf_gact_cleanup
c_func
(paren
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|bind
)paren
(brace
r_struct
id|tcf_gact
op_star
id|p
suffix:semicolon
id|p
op_assign
id|PRIV
c_func
(paren
id|a
comma
id|gact
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_ne
id|p
)paren
r_return
id|tcf_hash_release
c_func
(paren
id|p
comma
id|bind
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_gact
id|tcf_gact
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_struct
id|tc_action
op_star
id|a
)paren
(brace
r_struct
id|tcf_gact
op_star
id|p
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|pskb
suffix:semicolon
r_int
id|action
op_assign
id|TC_ACT_SHOT
suffix:semicolon
id|p
op_assign
id|PRIV
c_func
(paren
id|a
comma
id|gact
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|p
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;BUG: tcf_gact called with NULL params&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
r_if
c_cond
(paren
id|p-&gt;ptype
op_logical_and
l_int|NULL
op_ne
id|gact_rand
(braket
id|p-&gt;ptype
)braket
)paren
id|action
op_assign
id|gact_rand
(braket
id|p-&gt;ptype
)braket
(paren
id|p
)paren
suffix:semicolon
r_else
id|action
op_assign
id|p-&gt;action
suffix:semicolon
macro_line|#else
id|action
op_assign
id|p-&gt;action
suffix:semicolon
macro_line|#endif
id|p-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|p-&gt;bstats.packets
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|TC_ACT_SHOT
op_eq
id|action
)paren
id|p-&gt;qstats.drops
op_increment
suffix:semicolon
id|p-&gt;tm.lastuse
op_assign
id|jiffies
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_return
id|action
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_gact_dump
id|tcf_gact_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tc_action
op_star
id|a
comma
r_int
id|bind
comma
r_int
id|ref
)paren
(brace
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|tc_gact
id|opt
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
r_struct
id|tc_gact_p
id|p_opt
suffix:semicolon
macro_line|#endif
r_struct
id|tcf_gact
op_star
id|p
suffix:semicolon
r_struct
id|tcf_t
id|t
suffix:semicolon
id|p
op_assign
id|PRIV
c_func
(paren
id|a
comma
id|gact
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|p
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;BUG: tcf_gact_dump called with NULL params&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|rtattr_failure
suffix:semicolon
)brace
id|opt.index
op_assign
id|p-&gt;index
suffix:semicolon
id|opt.refcnt
op_assign
id|p-&gt;refcnt
op_minus
id|ref
suffix:semicolon
id|opt.bindcnt
op_assign
id|p-&gt;bindcnt
op_minus
id|bind
suffix:semicolon
id|opt.action
op_assign
id|p-&gt;action
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_GACT_PARMS
comma
r_sizeof
(paren
id|opt
)paren
comma
op_amp
id|opt
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GACT_PROB
r_if
c_cond
(paren
id|p-&gt;ptype
)paren
(brace
id|p_opt.paction
op_assign
id|p-&gt;paction
suffix:semicolon
id|p_opt.pval
op_assign
id|p-&gt;pval
suffix:semicolon
id|p_opt.ptype
op_assign
id|p-&gt;ptype
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_GACT_PROB
comma
r_sizeof
(paren
id|p_opt
)paren
comma
op_amp
id|p_opt
)paren
suffix:semicolon
)brace
macro_line|#endif
id|t.install
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|jiffies
op_minus
id|p-&gt;tm.install
)paren
suffix:semicolon
id|t.lastuse
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|jiffies
op_minus
id|p-&gt;tm.lastuse
)paren
suffix:semicolon
id|t.expires
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|p-&gt;tm.expires
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_GACT_TM
comma
r_sizeof
(paren
id|t
)paren
comma
op_amp
id|t
)paren
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|act_gact_ops
r_static
r_struct
id|tc_action_ops
id|act_gact_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|kind
op_assign
l_string|&quot;gact&quot;
comma
dot
id|type
op_assign
id|TCA_ACT_GACT
comma
dot
id|capab
op_assign
id|TCA_CAP_NONE
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|act
op_assign
id|tcf_gact
comma
dot
id|dump
op_assign
id|tcf_gact_dump
comma
dot
id|cleanup
op_assign
id|tcf_gact_cleanup
comma
dot
id|lookup
op_assign
id|tcf_hash_search
comma
dot
id|init
op_assign
id|tcf_gact_init
comma
dot
id|walk
op_assign
id|tcf_generic_walker
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jamal Hadi Salim(2002-4)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic Classifier actions&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_int
id|__init
DECL|function|gact_init_module
id|gact_init_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_GACT_PROB
id|printk
c_func
(paren
l_string|&quot;GACT probability on&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;GACT probability NOT on&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|tcf_register_action
c_func
(paren
op_amp
id|act_gact_ops
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|gact_cleanup_module
id|gact_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|tcf_unregister_action
c_func
(paren
op_amp
id|act_gact_ops
)paren
suffix:semicolon
)brace
DECL|variable|gact_init_module
id|module_init
c_func
(paren
id|gact_init_module
)paren
suffix:semicolon
DECL|variable|gact_cleanup_module
id|module_exit
c_func
(paren
id|gact_cleanup_module
)paren
suffix:semicolon
eof
