multiline_comment|/*&n; * net/sched/cls_api.c&t;Packet classifier API.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; * Changes:&n; *&n; * Eduardo J. Blanco &lt;ejbs@netlabs.com.uy&gt; :990222: kmod support&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/* The list of all installed classifier types */
DECL|variable|tcf_proto_base
r_static
r_struct
id|tcf_proto_ops
op_star
id|tcf_proto_base
suffix:semicolon
multiline_comment|/* Protects list of registered TC modules. It is pure SMP lock. */
DECL|variable|cls_mod_lock
r_static
id|rwlock_t
id|cls_mod_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Find classifier type by string name */
DECL|function|tcf_proto_lookup_ops
r_struct
id|tcf_proto_ops
op_star
id|tcf_proto_lookup_ops
c_func
(paren
r_struct
id|rtattr
op_star
id|kind
)paren
(brace
r_struct
id|tcf_proto_ops
op_star
id|t
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|kind
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|cls_mod_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|t
op_assign
id|tcf_proto_base
suffix:semicolon
id|t
suffix:semicolon
id|t
op_assign
id|t-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|rtattr_strcmp
c_func
(paren
id|kind
comma
id|t-&gt;kind
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|cls_mod_lock
)paren
suffix:semicolon
)brace
r_return
id|t
suffix:semicolon
)brace
multiline_comment|/* Register(unregister) new classifier type */
DECL|function|register_tcf_proto_ops
r_int
id|register_tcf_proto_ops
c_func
(paren
r_struct
id|tcf_proto_ops
op_star
id|ops
)paren
(brace
r_struct
id|tcf_proto_ops
op_star
id|t
comma
op_star
op_star
id|tp
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|EEXIST
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|cls_mod_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tp
op_assign
op_amp
id|tcf_proto_base
suffix:semicolon
(paren
id|t
op_assign
op_star
id|tp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|tp
op_assign
op_amp
id|t-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ops-&gt;kind
comma
id|t-&gt;kind
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ops-&gt;next
op_assign
l_int|NULL
suffix:semicolon
op_star
id|tp
op_assign
id|ops
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|cls_mod_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|unregister_tcf_proto_ops
r_int
id|unregister_tcf_proto_ops
c_func
(paren
r_struct
id|tcf_proto_ops
op_star
id|ops
)paren
(brace
r_struct
id|tcf_proto_ops
op_star
id|t
comma
op_star
op_star
id|tp
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|cls_mod_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tp
op_assign
op_amp
id|tcf_proto_base
suffix:semicolon
(paren
id|t
op_assign
op_star
id|tp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|tp
op_assign
op_amp
id|t-&gt;next
)paren
r_if
c_cond
(paren
id|t
op_eq
id|ops
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_goto
id|out
suffix:semicolon
op_star
id|tp
op_assign
id|t-&gt;next
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
id|cls_mod_lock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
id|tfilter_notify
c_func
(paren
r_struct
id|sk_buff
op_star
id|oskb
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|fh
comma
r_int
id|event
)paren
suffix:semicolon
multiline_comment|/* Select new prio value from the range, managed by kernel. */
DECL|function|tcf_auto_prio
r_static
id|__inline__
id|u32
id|tcf_auto_prio
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
id|u32
id|first
op_assign
id|TC_H_MAKE
c_func
(paren
l_int|0xC0000000U
comma
l_int|0U
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp
)paren
id|first
op_assign
id|tp-&gt;prio
op_minus
l_int|1
suffix:semicolon
r_return
id|first
suffix:semicolon
)brace
multiline_comment|/* Add/change/delete/get a filter node */
DECL|function|tc_ctl_tfilter
r_static
r_int
id|tc_ctl_tfilter
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|rtattr
op_star
op_star
id|tca
op_assign
id|arg
suffix:semicolon
r_struct
id|tcmsg
op_star
id|t
op_assign
id|NLMSG_DATA
c_func
(paren
id|n
)paren
suffix:semicolon
id|u32
id|protocol
op_assign
id|TC_H_MIN
c_func
(paren
id|t-&gt;tcm_info
)paren
suffix:semicolon
id|u32
id|prio
op_assign
id|TC_H_MAJ
c_func
(paren
id|t-&gt;tcm_info
)paren
suffix:semicolon
id|u32
id|nprio
op_assign
id|prio
suffix:semicolon
id|u32
id|parent
op_assign
id|t-&gt;tcm_parent
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|Qdisc
op_star
id|q
suffix:semicolon
r_struct
id|tcf_proto
op_star
op_star
id|back
comma
op_star
op_star
id|chain
suffix:semicolon
r_struct
id|tcf_proto
op_star
id|tp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|tcf_proto_ops
op_star
id|tp_ops
suffix:semicolon
r_struct
id|Qdisc_class_ops
op_star
id|cops
suffix:semicolon
r_int
r_int
id|cl
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|fh
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|prio
op_eq
l_int|0
)paren
(brace
multiline_comment|/* If no priority is given, user wants we allocated it. */
r_if
c_cond
(paren
id|n-&gt;nlmsg_type
op_ne
id|RTM_NEWTFILTER
op_logical_or
op_logical_neg
(paren
id|n-&gt;nlmsg_flags
op_amp
id|NLM_F_CREATE
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|prio
op_assign
id|TC_H_MAKE
c_func
(paren
l_int|0x80000000U
comma
l_int|0U
)paren
suffix:semicolon
)brace
multiline_comment|/* Find head of filter chain. */
multiline_comment|/* Find link */
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|__dev_get_by_index
c_func
(paren
id|t-&gt;tcm_ifindex
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Find qdisc */
r_if
c_cond
(paren
op_logical_neg
id|parent
)paren
(brace
id|q
op_assign
id|dev-&gt;qdisc_sleeping
suffix:semicolon
id|parent
op_assign
id|q-&gt;handle
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|q
op_assign
id|qdisc_lookup
c_func
(paren
id|dev
comma
id|TC_H_MAJ
c_func
(paren
id|t-&gt;tcm_parent
)paren
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Is it classful? */
r_if
c_cond
(paren
(paren
id|cops
op_assign
id|q-&gt;ops-&gt;cl_ops
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Do we search for filter, attached to class? */
r_if
c_cond
(paren
id|TC_H_MIN
c_func
(paren
id|parent
)paren
)paren
(brace
id|cl
op_assign
id|cops
op_member_access_from_pointer
id|get
c_func
(paren
id|q
comma
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
op_eq
l_int|0
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/* And the last stroke */
id|chain
op_assign
id|cops
op_member_access_from_pointer
id|tcf_chain
c_func
(paren
id|q
comma
id|cl
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|chain
op_eq
l_int|NULL
)paren
r_goto
id|errout
suffix:semicolon
multiline_comment|/* Check the chain for existence of proto-tcf with this priority */
r_for
c_loop
(paren
id|back
op_assign
id|chain
suffix:semicolon
(paren
id|tp
op_assign
op_star
id|back
)paren
op_ne
l_int|NULL
suffix:semicolon
id|back
op_assign
op_amp
id|tp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;prio
op_ge
id|prio
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;prio
op_eq
id|prio
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nprio
op_logical_or
(paren
id|tp-&gt;protocol
op_ne
id|protocol
op_logical_and
id|protocol
)paren
)paren
r_goto
id|errout
suffix:semicolon
)brace
r_else
id|tp
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tp
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Proto-tcf does not exist, create new one */
r_if
c_cond
(paren
id|tca
(braket
id|TCA_KIND
op_minus
l_int|1
)braket
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|protocol
)paren
r_goto
id|errout
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;nlmsg_type
op_ne
id|RTM_NEWTFILTER
op_logical_or
op_logical_neg
(paren
id|n-&gt;nlmsg_flags
op_amp
id|NLM_F_CREATE
)paren
)paren
r_goto
id|errout
suffix:semicolon
multiline_comment|/* Create new proto tcf */
id|err
op_assign
op_minus
id|ENOBUFS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tp
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|errout
suffix:semicolon
id|tp_ops
op_assign
id|tcf_proto_lookup_ops
c_func
(paren
id|tca
(braket
id|TCA_KIND
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|tp_ops
op_eq
l_int|NULL
op_logical_and
id|tca
(braket
id|TCA_KIND
op_minus
l_int|1
)braket
op_ne
l_int|NULL
)paren
(brace
r_struct
id|rtattr
op_star
id|kind
op_assign
id|tca
(braket
id|TCA_KIND
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|kind
)paren
op_le
id|IFNAMSIZ
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;cls_%s&quot;
comma
(paren
r_char
op_star
)paren
id|RTA_DATA
c_func
(paren
id|kind
)paren
)paren
suffix:semicolon
id|tp_ops
op_assign
id|tcf_proto_lookup_ops
c_func
(paren
id|kind
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|tp_ops
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|kfree
c_func
(paren
id|tp
)paren
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|memset
c_func
(paren
id|tp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tp
)paren
)paren
suffix:semicolon
id|tp-&gt;ops
op_assign
id|tp_ops
suffix:semicolon
id|tp-&gt;protocol
op_assign
id|protocol
suffix:semicolon
id|tp-&gt;prio
op_assign
id|nprio
ques
c_cond
suffix:colon
id|tcf_auto_prio
c_func
(paren
op_star
id|back
)paren
suffix:semicolon
id|tp-&gt;q
op_assign
id|q
suffix:semicolon
id|tp-&gt;classify
op_assign
id|tp_ops-&gt;classify
suffix:semicolon
id|tp-&gt;classid
op_assign
id|parent
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|tp_ops-&gt;owner
)paren
op_logical_or
(paren
id|err
op_assign
id|tp_ops
op_member_access_from_pointer
id|init
c_func
(paren
id|tp
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|tp
)paren
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|tp-&gt;next
op_assign
op_star
id|back
suffix:semicolon
op_star
id|back
op_assign
id|tp
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tca
(braket
id|TCA_KIND
op_minus
l_int|1
)braket
op_logical_and
id|rtattr_strcmp
c_func
(paren
id|tca
(braket
id|TCA_KIND
op_minus
l_int|1
)braket
comma
id|tp-&gt;ops-&gt;kind
)paren
)paren
r_goto
id|errout
suffix:semicolon
id|fh
op_assign
id|tp-&gt;ops
op_member_access_from_pointer
id|get
c_func
(paren
id|tp
comma
id|t-&gt;tcm_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fh
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|n-&gt;nlmsg_type
op_eq
id|RTM_DELTFILTER
op_logical_and
id|t-&gt;tcm_handle
op_eq
l_int|0
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
op_star
id|back
op_assign
id|tp-&gt;next
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;queue_lock
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|tp-&gt;ops
op_member_access_from_pointer
id|destroy
c_func
(paren
id|tp
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|tp-&gt;ops-&gt;owner
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tp
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;nlmsg_type
op_ne
id|RTM_NEWTFILTER
op_logical_or
op_logical_neg
(paren
id|n-&gt;nlmsg_flags
op_amp
id|NLM_F_CREATE
)paren
)paren
r_goto
id|errout
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|n-&gt;nlmsg_type
)paren
(brace
r_case
id|RTM_NEWTFILTER
suffix:colon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|n-&gt;nlmsg_flags
op_amp
id|NLM_F_EXCL
)paren
r_goto
id|errout
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RTM_DELTFILTER
suffix:colon
id|err
op_assign
id|tp-&gt;ops
op_member_access_from_pointer
r_delete
(paren
id|tp
comma
id|fh
)paren
suffix:semicolon
r_goto
id|errout
suffix:semicolon
r_case
id|RTM_GETTFILTER
suffix:colon
id|err
op_assign
id|tfilter_notify
c_func
(paren
id|skb
comma
id|n
comma
id|tp
comma
id|fh
comma
id|RTM_NEWTFILTER
)paren
suffix:semicolon
r_goto
id|errout
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
)brace
id|err
op_assign
id|tp-&gt;ops
op_member_access_from_pointer
id|change
c_func
(paren
id|tp
comma
id|cl
comma
id|t-&gt;tcm_handle
comma
id|tca
comma
op_amp
id|fh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
id|tfilter_notify
c_func
(paren
id|skb
comma
id|n
comma
id|tp
comma
id|fh
comma
id|RTM_NEWTFILTER
)paren
suffix:semicolon
id|errout
suffix:colon
r_if
c_cond
(paren
id|cl
)paren
id|cops
op_member_access_from_pointer
id|put
c_func
(paren
id|q
comma
id|cl
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|tcf_fill_node
id|tcf_fill_node
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|fh
comma
id|u32
id|pid
comma
id|u32
id|seq
comma
r_int
id|flags
comma
r_int
id|event
)paren
(brace
r_struct
id|tcmsg
op_star
id|tcm
suffix:semicolon
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
id|nlh
op_assign
id|NLMSG_PUT
c_func
(paren
id|skb
comma
id|pid
comma
id|seq
comma
id|event
comma
r_sizeof
(paren
op_star
id|tcm
)paren
)paren
suffix:semicolon
id|nlh-&gt;nlmsg_flags
op_assign
id|flags
suffix:semicolon
id|tcm
op_assign
id|NLMSG_DATA
c_func
(paren
id|nlh
)paren
suffix:semicolon
id|tcm-&gt;tcm_family
op_assign
id|AF_UNSPEC
suffix:semicolon
id|tcm-&gt;tcm_ifindex
op_assign
id|tp-&gt;q-&gt;dev-&gt;ifindex
suffix:semicolon
id|tcm-&gt;tcm_parent
op_assign
id|tp-&gt;classid
suffix:semicolon
id|tcm-&gt;tcm_handle
op_assign
l_int|0
suffix:semicolon
id|tcm-&gt;tcm_info
op_assign
id|TC_H_MAKE
c_func
(paren
id|tp-&gt;prio
comma
id|tp-&gt;protocol
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_KIND
comma
id|IFNAMSIZ
comma
id|tp-&gt;ops-&gt;kind
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;ops-&gt;dump
op_logical_and
id|tp-&gt;ops
op_member_access_from_pointer
id|dump
c_func
(paren
id|tp
comma
id|fh
comma
id|skb
comma
id|tcm
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
id|nlh-&gt;nlmsg_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|nlmsg_failure
suffix:colon
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
DECL|function|tfilter_notify
r_static
r_int
id|tfilter_notify
c_func
(paren
r_struct
id|sk_buff
op_star
id|oskb
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|fh
comma
r_int
id|event
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u32
id|pid
op_assign
id|oskb
ques
c_cond
id|NETLINK_CB
c_func
(paren
id|oskb
)paren
dot
id|pid
suffix:colon
l_int|0
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|NLMSG_GOODSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
r_if
c_cond
(paren
id|tcf_fill_node
c_func
(paren
id|skb
comma
id|tp
comma
id|fh
comma
id|pid
comma
id|n-&gt;nlmsg_seq
comma
l_int|0
comma
id|event
)paren
op_le
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|rtnetlink_send
c_func
(paren
id|skb
comma
id|pid
comma
id|RTMGRP_TC
comma
id|n-&gt;nlmsg_flags
op_amp
id|NLM_F_ECHO
)paren
suffix:semicolon
)brace
DECL|struct|tcf_dump_args
r_struct
id|tcf_dump_args
(brace
DECL|member|w
r_struct
id|tcf_walker
id|w
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|cb
r_struct
id|netlink_callback
op_star
id|cb
suffix:semicolon
)brace
suffix:semicolon
DECL|function|tcf_node_dump
r_static
r_int
id|tcf_node_dump
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|n
comma
r_struct
id|tcf_walker
op_star
id|arg
)paren
(brace
r_struct
id|tcf_dump_args
op_star
id|a
op_assign
(paren
r_void
op_star
)paren
id|arg
suffix:semicolon
r_return
id|tcf_fill_node
c_func
(paren
id|a-&gt;skb
comma
id|tp
comma
id|n
comma
id|NETLINK_CB
c_func
(paren
id|a-&gt;cb-&gt;skb
)paren
dot
id|pid
comma
id|a-&gt;cb-&gt;nlh-&gt;nlmsg_seq
comma
id|NLM_F_MULTI
comma
id|RTM_NEWTFILTER
)paren
suffix:semicolon
)brace
DECL|function|tc_dump_tfilter
r_static
r_int
id|tc_dump_tfilter
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
(brace
r_int
id|t
suffix:semicolon
r_int
id|s_t
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|Qdisc
op_star
id|q
suffix:semicolon
r_struct
id|tcf_proto
op_star
id|tp
comma
op_star
op_star
id|chain
suffix:semicolon
r_struct
id|tcmsg
op_star
id|tcm
op_assign
(paren
r_struct
id|tcmsg
op_star
)paren
id|NLMSG_DATA
c_func
(paren
id|cb-&gt;nlh
)paren
suffix:semicolon
r_int
r_int
id|cl
op_assign
l_int|0
suffix:semicolon
r_struct
id|Qdisc_class_ops
op_star
id|cops
suffix:semicolon
r_struct
id|tcf_dump_args
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;nlh-&gt;nlmsg_len
OL
id|NLMSG_LENGTH
c_func
(paren
r_sizeof
(paren
op_star
id|tcm
)paren
)paren
)paren
r_return
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|dev_get_by_index
c_func
(paren
id|tcm-&gt;tcm_ifindex
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
id|skb-&gt;len
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tcm-&gt;tcm_parent
)paren
id|q
op_assign
id|dev-&gt;qdisc_sleeping
suffix:semicolon
r_else
id|q
op_assign
id|qdisc_lookup
c_func
(paren
id|dev
comma
id|TC_H_MAJ
c_func
(paren
id|tcm-&gt;tcm_parent
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|q
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cops
op_assign
id|q-&gt;ops-&gt;cl_ops
)paren
op_eq
l_int|NULL
)paren
r_goto
id|errout
suffix:semicolon
r_if
c_cond
(paren
id|TC_H_MIN
c_func
(paren
id|tcm-&gt;tcm_parent
)paren
)paren
(brace
id|cl
op_assign
id|cops
op_member_access_from_pointer
id|get
c_func
(paren
id|q
comma
id|tcm-&gt;tcm_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
op_eq
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
)brace
id|chain
op_assign
id|cops
op_member_access_from_pointer
id|tcf_chain
c_func
(paren
id|q
comma
id|cl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chain
op_eq
l_int|NULL
)paren
r_goto
id|errout
suffix:semicolon
id|s_t
op_assign
id|cb-&gt;args
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|tp
op_assign
op_star
id|chain
comma
id|t
op_assign
l_int|0
suffix:semicolon
id|tp
suffix:semicolon
id|tp
op_assign
id|tp-&gt;next
comma
id|t
op_increment
)paren
(brace
r_if
c_cond
(paren
id|t
OL
id|s_t
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|TC_H_MAJ
c_func
(paren
id|tcm-&gt;tcm_info
)paren
op_logical_and
id|TC_H_MAJ
c_func
(paren
id|tcm-&gt;tcm_info
)paren
op_ne
id|tp-&gt;prio
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|TC_H_MIN
c_func
(paren
id|tcm-&gt;tcm_info
)paren
op_logical_and
id|TC_H_MIN
c_func
(paren
id|tcm-&gt;tcm_info
)paren
op_ne
id|tp-&gt;protocol
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
id|s_t
)paren
id|memset
c_func
(paren
op_amp
id|cb-&gt;args
(braket
l_int|1
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|cb-&gt;args
)paren
op_minus
r_sizeof
(paren
id|cb-&gt;args
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cb-&gt;args
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tcf_fill_node
c_func
(paren
id|skb
comma
id|tp
comma
l_int|0
comma
id|NETLINK_CB
c_func
(paren
id|cb-&gt;skb
)paren
dot
id|pid
comma
id|cb-&gt;nlh-&gt;nlmsg_seq
comma
id|NLM_F_MULTI
comma
id|RTM_NEWTFILTER
)paren
op_le
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
id|cb-&gt;args
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;ops-&gt;walk
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|arg.w.fn
op_assign
id|tcf_node_dump
suffix:semicolon
id|arg.skb
op_assign
id|skb
suffix:semicolon
id|arg.cb
op_assign
id|cb
suffix:semicolon
id|arg.w.stop
op_assign
l_int|0
suffix:semicolon
id|arg.w.skip
op_assign
id|cb-&gt;args
(braket
l_int|1
)braket
op_minus
l_int|1
suffix:semicolon
id|arg.w.count
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;ops
op_member_access_from_pointer
id|walk
c_func
(paren
id|tp
comma
op_amp
id|arg.w
)paren
suffix:semicolon
id|cb-&gt;args
(braket
l_int|1
)braket
op_assign
id|arg.w.count
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|arg.w.stop
)paren
r_break
suffix:semicolon
)brace
id|cb-&gt;args
(braket
l_int|0
)braket
op_assign
id|t
suffix:semicolon
id|errout
suffix:colon
r_if
c_cond
(paren
id|cl
)paren
id|cops
op_member_access_from_pointer
id|put
c_func
(paren
id|q
comma
id|cl
)paren
suffix:semicolon
id|out
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|qdisc_tree_lock
)paren
suffix:semicolon
id|dev_put
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
)brace
DECL|function|tc_filter_init
r_int
id|__init
id|tc_filter_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtnetlink_link
op_star
id|link_p
op_assign
id|rtnetlink_links
(braket
id|PF_UNSPEC
)braket
suffix:semicolon
multiline_comment|/* Setup rtnetlink links. It is made here to avoid&n;&t;   exporting large number of public symbols.&n;&t; */
r_if
c_cond
(paren
id|link_p
)paren
(brace
id|link_p
(braket
id|RTM_NEWTFILTER
op_minus
id|RTM_BASE
)braket
dot
id|doit
op_assign
id|tc_ctl_tfilter
suffix:semicolon
id|link_p
(braket
id|RTM_DELTFILTER
op_minus
id|RTM_BASE
)braket
dot
id|doit
op_assign
id|tc_ctl_tfilter
suffix:semicolon
id|link_p
(braket
id|RTM_GETTFILTER
op_minus
id|RTM_BASE
)braket
dot
id|doit
op_assign
id|tc_ctl_tfilter
suffix:semicolon
id|link_p
(braket
id|RTM_GETTFILTER
op_minus
id|RTM_BASE
)braket
dot
id|dumpit
op_assign
id|tc_dump_tfilter
suffix:semicolon
)brace
DECL|macro|INIT_TC_FILTER
mdefine_line|#define INIT_TC_FILTER(name) { &bslash;&n;          extern struct tcf_proto_ops cls_##name##_ops; &bslash;&n;          register_tcf_proto_ops(&amp;cls_##name##_ops); &bslash;&n;&t;}
macro_line|#ifdef CONFIG_NET_CLS_U32
id|INIT_TC_FILTER
c_func
(paren
id|u32
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_ROUTE4
id|INIT_TC_FILTER
c_func
(paren
id|route4
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_FW
id|INIT_TC_FILTER
c_func
(paren
id|fw
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_RSVP
id|INIT_TC_FILTER
c_func
(paren
id|rsvp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_TCINDEX
id|INIT_TC_FILTER
c_func
(paren
id|tcindex
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_RSVP6
id|INIT_TC_FILTER
c_func
(paren
id|rsvp6
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
