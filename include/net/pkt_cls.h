macro_line|#ifndef __NET_PKT_CLS_H
DECL|macro|__NET_PKT_CLS_H
mdefine_line|#define __NET_PKT_CLS_H
macro_line|#include &lt;linux/pkt_cls.h&gt;
macro_line|#include &lt;net/sch_generic.h&gt;
macro_line|#include &lt;net/act_api.h&gt;
multiline_comment|/* Basic packet classifier frontend definitions. */
DECL|struct|tcf_walker
r_struct
id|tcf_walker
(brace
DECL|member|stop
r_int
id|stop
suffix:semicolon
DECL|member|skip
r_int
id|skip
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|tcf_proto
op_star
comma
r_int
r_int
id|node
comma
r_struct
id|tcf_walker
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_tcf_proto_ops
c_func
(paren
r_struct
id|tcf_proto_ops
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_int
id|unregister_tcf_proto_ops
c_func
(paren
r_struct
id|tcf_proto_ops
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_int
id|ing_filter
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_static
r_inline
r_int
r_int
DECL|function|__cls_set_class
id|__cls_set_class
c_func
(paren
r_int
r_int
op_star
id|clp
comma
r_int
r_int
id|cl
)paren
(brace
r_int
r_int
id|old_cl
suffix:semicolon
id|old_cl
op_assign
op_star
id|clp
suffix:semicolon
op_star
id|clp
op_assign
id|cl
suffix:semicolon
r_return
id|old_cl
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|cls_set_class
id|cls_set_class
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_int
r_int
op_star
id|clp
comma
r_int
r_int
id|cl
)paren
(brace
r_int
r_int
id|old_cl
suffix:semicolon
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|old_cl
op_assign
id|__cls_set_class
c_func
(paren
id|clp
comma
id|cl
)paren
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
r_return
id|old_cl
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tcf_bind_filter
id|tcf_bind_filter
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_result
op_star
id|r
comma
r_int
r_int
id|base
)paren
(brace
r_int
r_int
id|cl
suffix:semicolon
id|cl
op_assign
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|bind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|base
comma
id|r-&gt;classid
)paren
suffix:semicolon
id|cl
op_assign
id|cls_set_class
c_func
(paren
id|tp
comma
op_amp
id|r
op_member_access_from_pointer
r_class
comma
id|cl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cl
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|tcf_unbind_filter
id|tcf_unbind_filter
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_result
op_star
id|r
)paren
(brace
r_int
r_int
id|cl
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cl
op_assign
id|__cls_set_class
c_func
(paren
op_amp
id|r
op_member_access_from_pointer
r_class
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
id|tp-&gt;q-&gt;ops-&gt;cl_ops
op_member_access_from_pointer
id|unbind_tcf
c_func
(paren
id|tp-&gt;q
comma
id|cl
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_static
r_inline
r_int
DECL|function|tcf_change_act_police
id|tcf_change_act_police
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tc_action
op_star
op_star
id|action
comma
r_struct
id|rtattr
op_star
id|act_police_tlv
comma
r_struct
id|rtattr
op_star
id|rate_tlv
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|tc_action
op_star
id|act
suffix:semicolon
id|act
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|act
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|act
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|act
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|tcf_action_init_1
c_func
(paren
id|act_police_tlv
comma
id|rate_tlv
comma
id|act
comma
l_string|&quot;police&quot;
comma
id|TCA_ACT_NOREPLACE
comma
id|TCA_ACT_BIND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|tcf_action_destroy
c_func
(paren
id|act
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|act-&gt;type
op_assign
id|TCA_OLD_COMPAT
suffix:semicolon
r_if
c_cond
(paren
op_star
id|action
)paren
(brace
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|act
op_assign
id|xchg
c_func
(paren
id|action
comma
id|act
)paren
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tcf_action_destroy
c_func
(paren
id|act
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
)brace
r_else
op_star
id|action
op_assign
id|act
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tcf_change_act
id|tcf_change_act
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tc_action
op_star
op_star
id|action
comma
r_struct
id|rtattr
op_star
id|act_tlv
comma
r_struct
id|rtattr
op_star
id|rate_tlv
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|tc_action
op_star
id|act
suffix:semicolon
id|act
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|act
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|act
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|act
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|tcf_action_init
c_func
(paren
id|act_tlv
comma
id|rate_tlv
comma
id|act
comma
l_int|NULL
comma
id|TCA_ACT_NOREPLACE
comma
id|TCA_ACT_BIND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|tcf_action_destroy
c_func
(paren
id|act
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|action
)paren
(brace
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|act
op_assign
id|xchg
c_func
(paren
id|action
comma
id|act
)paren
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tcf_action_destroy
c_func
(paren
id|act
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
)brace
r_else
op_star
id|action
op_assign
id|act
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tcf_dump_act
id|tcf_dump_act
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
id|action
comma
r_int
id|act_type
comma
r_int
id|compat_type
)paren
(brace
multiline_comment|/*&n;&t; * again for backward compatible mode - we want&n;&t; * to work with both old and new modes of entering&n;&t; * tc data even if iproute2  was newer - jhs&n;&t; */
r_if
c_cond
(paren
id|action
)paren
(brace
r_struct
id|rtattr
op_star
id|p_rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;type
op_ne
id|TCA_OLD_COMPAT
)paren
(brace
id|RTA_PUT
c_func
(paren
id|skb
comma
id|act_type
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcf_action_dump
c_func
(paren
id|skb
comma
id|action
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
)brace
r_else
(brace
id|RTA_PUT
c_func
(paren
id|skb
comma
id|compat_type
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcf_action_dump_old
c_func
(paren
id|skb
comma
id|action
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
)brace
id|p_rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|p_rta
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|rtattr_failure
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NET_CLS_ACT */
macro_line|#ifdef CONFIG_NET_CLS_IND
r_static
r_inline
r_int
DECL|function|tcf_change_indev
id|tcf_change_indev
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_char
op_star
id|indev
comma
r_struct
id|rtattr
op_star
id|indev_tlv
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|indev_tlv
)paren
op_ge
id|IFNAMSIZ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cls: bad indev name %s&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|RTA_DATA
c_func
(paren
id|indev_tlv
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|indev
comma
l_int|0
comma
id|IFNAMSIZ
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|indev
comma
l_string|&quot;%s&quot;
comma
(paren
r_char
op_star
)paren
id|RTA_DATA
c_func
(paren
id|indev_tlv
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tcf_match_indev
id|tcf_match_indev
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_char
op_star
id|indev
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
id|indev
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|skb-&gt;input_dev
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0
op_ne
id|strcmp
c_func
(paren
id|indev
comma
id|skb-&gt;input_dev-&gt;name
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NET_CLS_IND */
macro_line|#ifdef CONFIG_NET_CLS_POLICE
r_static
r_inline
r_int
DECL|function|tcf_change_police
id|tcf_change_police
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_police
op_star
op_star
id|police
comma
r_struct
id|rtattr
op_star
id|police_tlv
comma
r_struct
id|rtattr
op_star
id|rate_tlv
)paren
(brace
r_struct
id|tcf_police
op_star
id|p
op_assign
id|tcf_police_locate
c_func
(paren
id|police_tlv
comma
id|rate_tlv
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|police
)paren
(brace
id|tcf_tree_lock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|p
op_assign
id|xchg
c_func
(paren
id|police
comma
id|p
)paren
suffix:semicolon
id|tcf_tree_unlock
c_func
(paren
id|tp
)paren
suffix:semicolon
id|tcf_police_release
c_func
(paren
id|p
comma
id|TCA_ACT_UNBIND
)paren
suffix:semicolon
)brace
r_else
op_star
id|police
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tcf_dump_police
id|tcf_dump_police
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_police
op_star
id|police
comma
r_int
id|police_type
)paren
(brace
r_if
c_cond
(paren
id|police
)paren
(brace
r_struct
id|rtattr
op_star
id|p_rta
op_assign
(paren
r_struct
id|rtattr
op_star
)paren
id|skb-&gt;tail
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|police_type
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcf_police_dump
c_func
(paren
id|skb
comma
id|police
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
id|p_rta-&gt;rta_len
op_assign
id|skb-&gt;tail
op_minus
(paren
id|u8
op_star
)paren
id|p_rta
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|rtattr_failure
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_NET_CLS_POLICE */
macro_line|#endif
eof
