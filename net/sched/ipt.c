multiline_comment|/*&n; * net/sched/ipt.c&t;iptables target interface&n; *&n; *TODO: Add other tables. For now we only support the ipv4 table targets&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Copyright:&t;Jamal Hadi Salim (2002-4)&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
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
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;linux/tc_act/tc_ipt.h&gt;
macro_line|#include &lt;net/tc_act/tc_ipt.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_tables.h&gt;
multiline_comment|/* use generic hash table */
DECL|macro|MY_TAB_SIZE
mdefine_line|#define MY_TAB_SIZE     16
DECL|macro|MY_TAB_MASK
mdefine_line|#define MY_TAB_MASK     15
DECL|variable|idx_gen
r_static
id|u32
id|idx_gen
suffix:semicolon
DECL|variable|tcf_ipt_ht
r_static
r_struct
id|tcf_ipt
op_star
id|tcf_ipt_ht
(braket
id|MY_TAB_SIZE
)braket
suffix:semicolon
multiline_comment|/* ipt hash table lock */
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|ipt_lock
)paren
suffix:semicolon
multiline_comment|/* ovewrride the defaults */
DECL|macro|tcf_st
mdefine_line|#define tcf_st&t;&t;tcf_ipt
DECL|macro|tcf_t_lock
mdefine_line|#define tcf_t_lock&t;ipt_lock
DECL|macro|tcf_ht
mdefine_line|#define tcf_ht&t;&t;tcf_ipt_ht
DECL|macro|CONFIG_NET_ACT_INIT
mdefine_line|#define CONFIG_NET_ACT_INIT
macro_line|#include &lt;net/pkt_act.h&gt;
r_static
r_int
DECL|function|ipt_init_target
id|ipt_init_target
c_func
(paren
r_struct
id|ipt_entry_target
op_star
id|t
comma
r_char
op_star
id|table
comma
r_int
r_int
id|hook
)paren
(brace
r_struct
id|ipt_target
op_star
id|target
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|target
op_assign
id|ipt_find_target
c_func
(paren
id|t-&gt;u.user.name
comma
id|t-&gt;u.user.revision
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;ipt_init_target: found %s&bslash;n&quot;
comma
id|target-&gt;name
)paren
suffix:semicolon
id|t-&gt;u.kernel.target
op_assign
id|target
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;u.kernel.target-&gt;checkentry
op_logical_and
op_logical_neg
id|t-&gt;u.kernel.target
op_member_access_from_pointer
id|checkentry
c_func
(paren
id|table
comma
l_int|NULL
comma
id|t-&gt;data
comma
id|t-&gt;u.target_size
op_minus
r_sizeof
(paren
op_star
id|t
)paren
comma
id|hook
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;ipt_init_target: check failed for `%s&squot;.&bslash;n&quot;
comma
id|t-&gt;u.kernel.target-&gt;name
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|t-&gt;u.kernel.target-&gt;me
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|ipt_destroy_target
id|ipt_destroy_target
c_func
(paren
r_struct
id|ipt_entry_target
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;u.kernel.target-&gt;destroy
)paren
id|t-&gt;u.kernel.target
op_member_access_from_pointer
id|destroy
c_func
(paren
id|t-&gt;data
comma
id|t-&gt;u.target_size
op_minus
r_sizeof
(paren
op_star
id|t
)paren
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|t-&gt;u.kernel.target-&gt;me
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_ipt_release
id|tcf_ipt_release
c_func
(paren
r_struct
id|tcf_ipt
op_star
id|p
comma
r_int
id|bind
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|bind
)paren
id|p-&gt;bindcnt
op_decrement
suffix:semicolon
id|p-&gt;refcnt
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bindcnt
op_le
l_int|0
op_logical_and
id|p-&gt;refcnt
op_le
l_int|0
)paren
(brace
id|ipt_destroy_target
c_func
(paren
id|p-&gt;t
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p-&gt;tname
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p-&gt;t
)paren
suffix:semicolon
id|tcf_hash_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
id|ret
op_assign
id|ACT_P_DELETED
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_ipt_init
id|tcf_ipt_init
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
id|TCA_IPT_MAX
)braket
suffix:semicolon
r_struct
id|tcf_ipt
op_star
id|p
suffix:semicolon
r_struct
id|ipt_entry_target
op_star
id|td
comma
op_star
id|t
suffix:semicolon
r_char
op_star
id|tname
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|err
suffix:semicolon
id|u32
id|hook
op_assign
l_int|0
suffix:semicolon
id|u32
id|index
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rta
op_eq
l_int|NULL
op_logical_or
id|rtattr_parse_nested
c_func
(paren
id|tb
comma
id|TCA_IPT_MAX
comma
id|rta
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_IPT_HOOK
op_minus
l_int|1
)braket
op_eq
l_int|NULL
op_logical_or
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_IPT_HOOK
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
id|u32
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_IPT_TARG
op_minus
l_int|1
)braket
op_eq
l_int|NULL
op_logical_or
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_IPT_TARG
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
op_star
id|t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|td
op_assign
(paren
r_struct
id|ipt_entry_target
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_IPT_TARG
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_IPT_TARG
op_minus
l_int|1
)braket
)paren
OL
id|td-&gt;u.target_size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_IPT_INDEX
op_minus
l_int|1
)braket
op_ne
l_int|NULL
op_logical_and
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_IPT_INDEX
op_minus
l_int|1
)braket
)paren
op_ge
r_sizeof
(paren
id|u32
)paren
)paren
id|index
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_IPT_INDEX
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|p
op_assign
id|tcf_hash_check
c_func
(paren
id|index
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
id|p
op_eq
l_int|NULL
)paren
(brace
id|p
op_assign
id|tcf_hash_create
c_func
(paren
id|index
comma
id|est
comma
id|a
comma
r_sizeof
(paren
op_star
id|p
)paren
comma
id|ovr
comma
id|bind
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
id|ACT_P_CREATED
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|ovr
)paren
(brace
id|tcf_ipt_release
c_func
(paren
id|p
comma
id|bind
)paren
suffix:semicolon
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
)brace
id|hook
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_IPT_HOOK
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|tname
op_assign
id|kmalloc
c_func
(paren
id|IFNAMSIZ
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tname
op_eq
l_int|NULL
)paren
r_goto
id|err1
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_IPT_TABLE
op_minus
l_int|1
)braket
op_eq
l_int|NULL
op_logical_or
id|rtattr_strlcpy
c_func
(paren
id|tname
comma
id|tb
(braket
id|TCA_IPT_TABLE
op_minus
l_int|1
)braket
comma
id|IFNAMSIZ
)paren
op_ge
id|IFNAMSIZ
)paren
id|strcpy
c_func
(paren
id|tname
comma
l_string|&quot;mangle&quot;
)paren
suffix:semicolon
id|t
op_assign
id|kmalloc
c_func
(paren
id|td-&gt;u.target_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
l_int|NULL
)paren
r_goto
id|err2
suffix:semicolon
id|memcpy
c_func
(paren
id|t
comma
id|td
comma
id|td-&gt;u.target_size
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ipt_init_target
c_func
(paren
id|t
comma
id|tname
comma
id|hook
)paren
)paren
OL
l_int|0
)paren
r_goto
id|err3
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|ACT_P_CREATED
)paren
(brace
id|ipt_destroy_target
c_func
(paren
id|p-&gt;t
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p-&gt;tname
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p-&gt;t
)paren
suffix:semicolon
)brace
id|p-&gt;tname
op_assign
id|tname
suffix:semicolon
id|p-&gt;t
op_assign
id|t
suffix:semicolon
id|p-&gt;hook
op_assign
id|hook
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|ACT_P_CREATED
)paren
id|tcf_hash_insert
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
id|err3
suffix:colon
id|kfree
c_func
(paren
id|t
)paren
suffix:semicolon
id|err2
suffix:colon
id|kfree
c_func
(paren
id|tname
)paren
suffix:semicolon
id|err1
suffix:colon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_ipt_cleanup
id|tcf_ipt_cleanup
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
id|tcf_ipt
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|a
comma
id|ipt
)paren
suffix:semicolon
r_return
id|tcf_ipt_release
c_func
(paren
id|p
comma
id|bind
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_ipt
id|tcf_ipt
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
r_int
id|ret
op_assign
l_int|0
comma
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|tcf_ipt
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|a
comma
id|ipt
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
op_star
id|pskb
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
id|p-&gt;tm.lastuse
op_assign
id|jiffies
suffix:semicolon
id|p-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|p-&gt;bstats.packets
op_increment
suffix:semicolon
multiline_comment|/* yes, we have to worry about both in and out dev&n;&t; worry later - danger - this API seems to have changed&n;&t; from earlier kernels */
id|ret
op_assign
id|p-&gt;t-&gt;u.kernel.target
op_member_access_from_pointer
id|target
c_func
(paren
op_amp
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
comma
id|p-&gt;hook
comma
id|p-&gt;t-&gt;data
comma
l_int|NULL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
id|NF_ACCEPT
suffix:colon
id|result
op_assign
id|TC_ACT_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NF_DROP
suffix:colon
id|result
op_assign
id|TC_ACT_SHOT
suffix:semicolon
id|p-&gt;qstats.drops
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPT_CONTINUE
suffix:colon
id|result
op_assign
id|TC_ACT_PIPE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
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
l_string|&quot;Bogus netfilter code %d assume ACCEPT&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|result
op_assign
id|TC_POLICE_OK
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|p-&gt;lock
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_ipt_dump
id|tcf_ipt_dump
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
r_struct
id|ipt_entry_target
op_star
id|t
suffix:semicolon
r_struct
id|tcf_t
id|tm
suffix:semicolon
r_struct
id|tc_cnt
id|c
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|tcf_ipt
op_star
id|p
op_assign
id|PRIV
c_func
(paren
id|a
comma
id|ipt
)paren
suffix:semicolon
multiline_comment|/* for simple targets kernel size == user size&n;&t;** user name = target name&n;&t;** for foolproof you need to not assume this&n;&t;*/
id|t
op_assign
id|kmalloc
c_func
(paren
id|p-&gt;t-&gt;u.user.target_size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
l_int|NULL
)paren
r_goto
id|rtattr_failure
suffix:semicolon
id|c.bindcnt
op_assign
id|p-&gt;bindcnt
op_minus
id|bind
suffix:semicolon
id|c.refcnt
op_assign
id|p-&gt;refcnt
op_minus
id|ref
suffix:semicolon
id|memcpy
c_func
(paren
id|t
comma
id|p-&gt;t
comma
id|p-&gt;t-&gt;u.user.target_size
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|t-&gt;u.user.name
comma
id|p-&gt;t-&gt;u.kernel.target-&gt;name
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;&bslash;ttcf_ipt_dump tablename %s length %d&bslash;n&quot;
comma
id|p-&gt;tname
comma
id|strlen
c_func
(paren
id|p-&gt;tname
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;&bslash;tdump target name %s size %d size user %d &quot;
l_string|&quot;data[0] %x data[1] %x&bslash;n&quot;
comma
id|p-&gt;t-&gt;u.kernel.target-&gt;name
comma
id|p-&gt;t-&gt;u.target_size
comma
id|p-&gt;t-&gt;u.user.target_size
comma
id|p-&gt;t-&gt;data
(braket
l_int|0
)braket
comma
id|p-&gt;t-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_IPT_TARG
comma
id|p-&gt;t-&gt;u.user.target_size
comma
id|t
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_IPT_INDEX
comma
l_int|4
comma
op_amp
id|p-&gt;index
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_IPT_HOOK
comma
l_int|4
comma
op_amp
id|p-&gt;hook
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_IPT_CNT
comma
r_sizeof
(paren
r_struct
id|tc_cnt
)paren
comma
op_amp
id|c
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_IPT_TABLE
comma
id|IFNAMSIZ
comma
id|p-&gt;tname
)paren
suffix:semicolon
id|tm.install
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|jiffies
op_minus
id|p-&gt;tm.install
)paren
suffix:semicolon
id|tm.lastuse
op_assign
id|jiffies_to_clock_t
c_func
(paren
id|jiffies
op_minus
id|p-&gt;tm.lastuse
)paren
suffix:semicolon
id|tm.expires
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
id|TCA_IPT_TM
comma
r_sizeof
(paren
id|tm
)paren
comma
op_amp
id|tm
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
DECL|variable|act_ipt_ops
r_static
r_struct
id|tc_action_ops
id|act_ipt_ops
op_assign
(brace
dot
id|kind
op_assign
l_string|&quot;ipt&quot;
comma
dot
id|type
op_assign
id|TCA_ACT_IPT
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
id|tcf_ipt
comma
dot
id|dump
op_assign
id|tcf_ipt_dump
comma
dot
id|cleanup
op_assign
id|tcf_ipt_cleanup
comma
dot
id|lookup
op_assign
id|tcf_hash_search
comma
dot
id|init
op_assign
id|tcf_ipt_init
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
l_string|&quot;Iptables target actions&quot;
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
DECL|function|ipt_init_module
id|ipt_init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|tcf_register_action
c_func
(paren
op_amp
id|act_ipt_ops
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|ipt_cleanup_module
id|ipt_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|tcf_unregister_action
c_func
(paren
op_amp
id|act_ipt_ops
)paren
suffix:semicolon
)brace
DECL|variable|ipt_init_module
id|module_init
c_func
(paren
id|ipt_init_module
)paren
suffix:semicolon
DECL|variable|ipt_cleanup_module
id|module_exit
c_func
(paren
id|ipt_cleanup_module
)paren
suffix:semicolon
eof
