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
DECL|struct|tcf_exts
r_struct
id|tcf_exts
(brace
macro_line|#ifdef CONFIG_NET_CLS_ACT
DECL|member|action
r_struct
id|tc_action
op_star
id|action
suffix:semicolon
macro_line|#elif defined CONFIG_NET_CLS_POLICE
r_struct
id|tcf_police
op_star
id|police
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Map to export classifier specific extension TLV types to the&n; * generic extensions API. Unsupported extensions must be set to 0.&n; */
DECL|struct|tcf_ext_map
r_struct
id|tcf_ext_map
(brace
DECL|member|action
r_int
id|action
suffix:semicolon
DECL|member|police
r_int
id|police
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * tcf_exts_is_predicative - check if a predicative extension is present&n; * @exts: tc filter extensions handle&n; *&n; * Returns 1 if a predicative extension is present, i.e. an extension which&n; * might cause further actions and thus overrule the regular tcf_result.&n; */
r_static
r_inline
r_int
DECL|function|tcf_exts_is_predicative
id|tcf_exts_is_predicative
c_func
(paren
r_struct
id|tcf_exts
op_star
id|exts
)paren
(brace
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_return
op_logical_neg
op_logical_neg
id|exts-&gt;action
suffix:semicolon
macro_line|#elif defined CONFIG_NET_CLS_POLICE
r_return
op_logical_neg
op_logical_neg
id|exts-&gt;police
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/**&n; * tcf_exts_is_available - check if at least one extension is present&n; * @exts: tc filter extensions handle&n; *&n; * Returns 1 if at least one extension is present.&n; */
r_static
r_inline
r_int
DECL|function|tcf_exts_is_available
id|tcf_exts_is_available
c_func
(paren
r_struct
id|tcf_exts
op_star
id|exts
)paren
(brace
multiline_comment|/* All non-predicative extensions must be added here. */
r_return
id|tcf_exts_is_predicative
c_func
(paren
id|exts
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * tcf_exts_exec - execute tc filter extensions&n; * @skb: socket buffer&n; * @exts: tc filter extensions handle&n; * @res: desired result&n; *&n; * Executes all configured extensions. Returns 0 on a normal execution,&n; * a negative number if the filter must be considered unmatched or&n; * a positive action code (TC_ACT_*) which must be returned to the&n; * underlying layer.&n; */
r_static
r_inline
r_int
DECL|function|tcf_exts_exec
id|tcf_exts_exec
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_exts
op_star
id|exts
comma
r_struct
id|tcf_result
op_star
id|res
)paren
(brace
macro_line|#ifdef CONFIG_NET_CLS_ACT
r_if
c_cond
(paren
id|exts-&gt;action
)paren
r_return
id|tcf_action_exec
c_func
(paren
id|skb
comma
id|exts-&gt;action
comma
id|res
)paren
suffix:semicolon
macro_line|#elif defined CONFIG_NET_CLS_POLICE
r_if
c_cond
(paren
id|exts-&gt;police
)paren
r_return
id|tcf_police
c_func
(paren
id|skb
comma
id|exts-&gt;police
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|tcf_exts_validate
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
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
id|rate_tlv
comma
r_struct
id|tcf_exts
op_star
id|exts
comma
r_struct
id|tcf_ext_map
op_star
id|map
)paren
suffix:semicolon
r_extern
r_void
id|tcf_exts_destroy
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_exts
op_star
id|exts
)paren
suffix:semicolon
r_extern
r_void
id|tcf_exts_change
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_exts
op_star
id|dst
comma
r_struct
id|tcf_exts
op_star
id|src
)paren
suffix:semicolon
r_extern
r_int
id|tcf_exts_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_exts
op_star
id|exts
comma
r_struct
id|tcf_ext_map
op_star
id|map
)paren
suffix:semicolon
r_extern
r_int
id|tcf_exts_dump_stats
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_exts
op_star
id|exts
comma
r_struct
id|tcf_ext_map
op_star
id|map
)paren
suffix:semicolon
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
id|rtattr_strlcpy
c_func
(paren
id|indev
comma
id|indev_tlv
comma
id|IFNAMSIZ
)paren
op_ge
id|IFNAMSIZ
)paren
r_return
op_minus
id|EINVAL
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
macro_line|#endif
eof
