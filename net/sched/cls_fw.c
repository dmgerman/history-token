multiline_comment|/*&n; * net/sched/cls_fw.c&t;Classifier mapping ipchains&squot; fwmark to traffic class.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; * Changes:&n; * Karlis Peisenieks &lt;karlis@mt.lv&gt; : 990415 : fw_walk off by one&n; * Karlis Peisenieks &lt;karlis@mt.lv&gt; : 990415 : fw_delete killed all the filter (and kernel).&n; * Alex &lt;alex@pilotsoft.com&gt; : 2004xxyy: Added Action extension&n; *&n; * JHS: We should remove the CONFIG_NET_CLS_IND from here&n; * eventually when the meta match extension is made available&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
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
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/netfilter.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/act_api.h&gt;
macro_line|#include &lt;net/pkt_cls.h&gt;
DECL|struct|fw_head
r_struct
id|fw_head
(brace
DECL|member|ht
r_struct
id|fw_filter
op_star
id|ht
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fw_filter
r_struct
id|fw_filter
(brace
DECL|member|next
r_struct
id|fw_filter
op_star
id|next
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|res
r_struct
id|tcf_result
id|res
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_IND
DECL|member|indev
r_char
id|indev
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_IND */
macro_line|#ifdef CONFIG_NET_CLS_ACT
DECL|member|action
r_struct
id|tc_action
op_star
id|action
suffix:semicolon
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
DECL|member|police
r_struct
id|tcf_police
op_star
id|police
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
)brace
suffix:semicolon
DECL|function|fw_hash
r_static
id|__inline__
r_int
id|fw_hash
c_func
(paren
id|u32
id|handle
)paren
(brace
r_return
id|handle
op_amp
l_int|0xFF
suffix:semicolon
)brace
DECL|function|fw_classify
r_static
r_int
id|fw_classify
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
r_struct
id|tcf_result
op_star
id|res
)paren
(brace
r_struct
id|fw_head
op_star
id|head
op_assign
(paren
r_struct
id|fw_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|fw_filter
op_star
id|f
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER
id|u32
id|id
op_assign
id|skb-&gt;nfmark
suffix:semicolon
macro_line|#else
id|u32
id|id
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|head
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|f
op_assign
id|head-&gt;ht
(braket
id|fw_hash
c_func
(paren
id|id
)paren
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;id
op_eq
id|id
)paren
(brace
op_star
id|res
op_assign
id|f-&gt;res
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_IND
r_if
c_cond
(paren
op_logical_neg
id|tcf_match_indev
c_func
(paren
id|skb
comma
id|f-&gt;indev
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_IND */
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|f-&gt;action
)paren
(brace
r_int
id|act_res
op_assign
id|tcf_action_exec
c_func
(paren
id|skb
comma
id|f-&gt;action
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|act_res
op_ge
l_int|0
)paren
r_return
id|act_res
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|f-&gt;police
)paren
r_return
id|tcf_police
c_func
(paren
id|skb
comma
id|f-&gt;police
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* old method */
r_if
c_cond
(paren
id|id
op_logical_and
(paren
id|TC_H_MAJ
c_func
(paren
id|id
)paren
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
id|TC_H_MAJ
c_func
(paren
id|id
op_xor
id|tp-&gt;q-&gt;handle
)paren
)paren
)paren
)paren
(brace
id|res-&gt;classid
op_assign
id|id
suffix:semicolon
id|res
op_member_access_from_pointer
r_class
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|fw_get
r_static
r_int
r_int
id|fw_get
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
id|u32
id|handle
)paren
(brace
r_struct
id|fw_head
op_star
id|head
op_assign
(paren
r_struct
id|fw_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|fw_filter
op_star
id|f
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|head-&gt;ht
(braket
id|fw_hash
c_func
(paren
id|handle
)paren
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;id
op_eq
id|handle
)paren
r_return
(paren
r_int
r_int
)paren
id|f
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fw_put
r_static
r_void
id|fw_put
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|f
)paren
(brace
)brace
DECL|function|fw_init
r_static
r_int
id|fw_init
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fw_destroy
r_static
r_void
id|fw_destroy
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
)paren
(brace
r_struct
id|fw_head
op_star
id|head
op_assign
(paren
r_struct
id|fw_head
op_star
)paren
id|xchg
c_func
(paren
op_amp
id|tp-&gt;root
comma
l_int|NULL
)paren
suffix:semicolon
r_struct
id|fw_filter
op_star
id|f
suffix:semicolon
r_int
id|h
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
l_int|256
suffix:semicolon
id|h
op_increment
)paren
(brace
r_while
c_loop
(paren
(paren
id|f
op_assign
id|head-&gt;ht
(braket
id|h
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|head-&gt;ht
(braket
id|h
)braket
op_assign
id|f-&gt;next
suffix:semicolon
id|tcf_unbind_filter
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|f-&gt;action
)paren
id|tcf_action_destroy
c_func
(paren
id|f-&gt;action
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|f-&gt;police
)paren
id|tcf_police_release
c_func
(paren
id|f-&gt;police
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|head
)paren
suffix:semicolon
)brace
DECL|function|fw_delete
r_static
r_int
id|fw_delete
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|fw_head
op_star
id|head
op_assign
(paren
r_struct
id|fw_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|fw_filter
op_star
id|f
op_assign
(paren
r_struct
id|fw_filter
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|fw_filter
op_star
op_star
id|fp
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
op_logical_or
id|f
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|fp
op_assign
op_amp
id|head-&gt;ht
(braket
id|fw_hash
c_func
(paren
id|f-&gt;id
)paren
)braket
suffix:semicolon
op_star
id|fp
suffix:semicolon
id|fp
op_assign
op_amp
(paren
op_star
id|fp
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_if
c_cond
(paren
op_star
id|fp
op_eq
id|f
)paren
(brace
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
op_star
id|fp
op_assign
id|f-&gt;next
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tcf_unbind_filter
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|f-&gt;action
)paren
id|tcf_action_destroy
c_func
(paren
id|f-&gt;action
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
id|tcf_police_release
c_func
(paren
id|f-&gt;police
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|out
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|fw_change_attrs
id|fw_change_attrs
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|fw_filter
op_star
id|f
comma
r_struct
id|rtattr
op_star
op_star
id|tb
comma
r_struct
id|rtattr
op_star
op_star
id|tca
comma
r_int
r_int
id|base
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_FW_CLASSID
op_minus
l_int|1
)braket
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|tb
(braket
id|TCA_FW_CLASSID
op_minus
l_int|1
)braket
)paren
op_ne
r_sizeof
(paren
id|u32
)paren
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;res.classid
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
id|TCA_FW_CLASSID
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|tcf_bind_filter
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;res
comma
id|base
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_IND
r_if
c_cond
(paren
id|tb
(braket
id|TCA_FW_INDEV
op_minus
l_int|1
)braket
)paren
(brace
id|err
op_assign
id|tcf_change_indev
c_func
(paren
id|tp
comma
id|f-&gt;indev
comma
id|tb
(braket
id|TCA_FW_INDEV
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NET_CLS_IND */
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|tb
(braket
id|TCA_FW_POLICE
op_minus
l_int|1
)braket
)paren
(brace
id|err
op_assign
id|tcf_change_act_police
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;action
comma
id|tb
(braket
id|TCA_FW_POLICE
op_minus
l_int|1
)braket
comma
id|tca
(braket
id|TCA_RATE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tb
(braket
id|TCA_FW_ACT
op_minus
l_int|1
)braket
)paren
(brace
id|err
op_assign
id|tcf_change_act
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;action
comma
id|tb
(braket
id|TCA_FW_ACT
op_minus
l_int|1
)braket
comma
id|tca
(braket
id|TCA_RATE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
)brace
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|tb
(braket
id|TCA_FW_POLICE
op_minus
l_int|1
)braket
)paren
(brace
id|err
op_assign
id|tcf_change_police
c_func
(paren
id|tp
comma
op_amp
id|f-&gt;police
comma
id|tb
(braket
id|TCA_FW_POLICE
op_minus
l_int|1
)braket
comma
id|tca
(braket
id|TCA_RATE
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
id|err
op_assign
l_int|0
suffix:semicolon
id|errout
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|fw_change
r_static
r_int
id|fw_change
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|base
comma
id|u32
id|handle
comma
r_struct
id|rtattr
op_star
op_star
id|tca
comma
r_int
r_int
op_star
id|arg
)paren
(brace
r_struct
id|fw_head
op_star
id|head
op_assign
(paren
r_struct
id|fw_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_struct
id|fw_filter
op_star
id|f
op_assign
(paren
r_struct
id|fw_filter
op_star
)paren
op_star
id|arg
suffix:semicolon
r_struct
id|rtattr
op_star
id|opt
op_assign
id|tca
(braket
id|TCA_OPTIONS
op_minus
l_int|1
)braket
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_FW_MAX
)braket
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opt
)paren
r_return
id|handle
ques
c_cond
op_minus
id|EINVAL
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_FW_MAX
comma
id|RTA_DATA
c_func
(paren
id|opt
)paren
comma
id|RTA_PAYLOAD
c_func
(paren
id|opt
)paren
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
id|f
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;id
op_ne
id|handle
op_logical_and
id|handle
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|fw_change_attrs
c_func
(paren
id|tp
comma
id|f
comma
id|tb
comma
id|tca
comma
id|base
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
(brace
id|head
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|fw_head
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|memset
c_func
(paren
id|head
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|head
)paren
)paren
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tp-&gt;root
op_assign
id|head
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|f
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|fw_filter
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|f-&gt;id
op_assign
id|handle
suffix:semicolon
id|err
op_assign
id|fw_change_attrs
c_func
(paren
id|tp
comma
id|f
comma
id|tb
comma
id|tca
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
id|f-&gt;next
op_assign
id|head-&gt;ht
(braket
id|fw_hash
c_func
(paren
id|handle
)paren
)braket
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|head-&gt;ht
(braket
id|fw_hash
c_func
(paren
id|handle
)paren
)braket
op_assign
id|f
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
op_star
id|arg
op_assign
(paren
r_int
r_int
)paren
id|f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|errout
suffix:colon
r_if
c_cond
(paren
id|f
)paren
id|kfree
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|fw_walk
r_static
r_void
id|fw_walk
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_walker
op_star
id|arg
)paren
(brace
r_struct
id|fw_head
op_star
id|head
op_assign
(paren
r_struct
id|fw_head
op_star
)paren
id|tp-&gt;root
suffix:semicolon
r_int
id|h
suffix:semicolon
r_if
c_cond
(paren
id|head
op_eq
l_int|NULL
)paren
id|arg-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|arg-&gt;stop
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
l_int|256
suffix:semicolon
id|h
op_increment
)paren
(brace
r_struct
id|fw_filter
op_star
id|f
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|head-&gt;ht
(braket
id|h
)braket
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|arg-&gt;count
OL
id|arg-&gt;skip
)paren
(brace
id|arg-&gt;count
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
op_member_access_from_pointer
id|fn
c_func
(paren
id|tp
comma
(paren
r_int
r_int
)paren
id|f
comma
id|arg
)paren
OL
l_int|0
)paren
(brace
id|arg-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|arg-&gt;count
op_increment
suffix:semicolon
)brace
)brace
)brace
DECL|function|fw_dump
r_static
r_int
id|fw_dump
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
id|fh
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcmsg
op_star
id|t
)paren
(brace
r_struct
id|fw_filter
op_star
id|f
op_assign
(paren
r_struct
id|fw_filter
op_star
)paren
id|fh
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|rtattr
op_star
id|rta
suffix:semicolon
r_if
c_cond
(paren
id|f
op_eq
l_int|NULL
)paren
r_return
id|skb-&gt;len
suffix:semicolon
id|t-&gt;tcm_handle
op_assign
id|f-&gt;id
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f-&gt;res.classid
macro_line|#ifdef CONFIG_NET_CLS_ACT
op_logical_and
op_logical_neg
id|f-&gt;action
macro_line|#else
macro_line|#ifdef CONFIG_NET_CLS_POLICE
op_logical_and
op_logical_neg
id|f-&gt;police
macro_line|#endif
macro_line|#endif
)paren
r_return
id|skb-&gt;len
suffix:semicolon
id|rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|b
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_OPTIONS
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;res.classid
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_FW_CLASSID
comma
l_int|4
comma
op_amp
id|f-&gt;res.classid
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_IND
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|f-&gt;indev
)paren
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_FW_INDEV
comma
id|IFNAMSIZ
comma
id|f-&gt;indev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_IND */
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|tcf_dump_act
c_func
(paren
id|skb
comma
id|f-&gt;action
comma
id|TCA_FW_ACT
comma
id|TCA_FW_POLICE
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|tcf_dump_police
c_func
(paren
id|skb
comma
id|f-&gt;police
comma
id|TCA_FW_POLICE
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
id|rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
id|b
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|f-&gt;action
op_logical_and
id|f-&gt;action-&gt;type
op_eq
id|TCA_OLD_COMPAT
)paren
(brace
r_if
c_cond
(paren
id|tcf_action_copy_stats
c_func
(paren
id|skb
comma
id|f-&gt;action
)paren
)paren
r_goto
id|rtattr_failure
suffix:semicolon
)brace
macro_line|#else /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|f-&gt;police
)paren
r_if
c_cond
(paren
id|tcf_police_dump_stats
c_func
(paren
id|skb
comma
id|f-&gt;police
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif /* CONFIG_NET_CLS_ACT */
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
DECL|variable|cls_fw_ops
r_static
r_struct
id|tcf_proto_ops
id|cls_fw_ops
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
l_string|&quot;fw&quot;
comma
dot
id|classify
op_assign
id|fw_classify
comma
dot
id|init
op_assign
id|fw_init
comma
dot
id|destroy
op_assign
id|fw_destroy
comma
dot
id|get
op_assign
id|fw_get
comma
dot
id|put
op_assign
id|fw_put
comma
dot
id|change
op_assign
id|fw_change
comma
dot
r_delete
op_assign
id|fw_delete
comma
dot
id|walk
op_assign
id|fw_walk
comma
dot
id|dump
op_assign
id|fw_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|init_fw
r_static
r_int
id|__init
id|init_fw
c_func
(paren
r_void
)paren
(brace
r_return
id|register_tcf_proto_ops
c_func
(paren
op_amp
id|cls_fw_ops
)paren
suffix:semicolon
)brace
DECL|function|exit_fw
r_static
r_void
id|__exit
id|exit_fw
c_func
(paren
r_void
)paren
(brace
id|unregister_tcf_proto_ops
c_func
(paren
op_amp
id|cls_fw_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|init_fw
)paren
id|module_exit
c_func
(paren
id|exit_fw
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
