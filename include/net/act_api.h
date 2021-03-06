macro_line|#ifndef __NET_ACT_API_H
DECL|macro|__NET_ACT_API_H
mdefine_line|#define __NET_ACT_API_H
multiline_comment|/*&n; * Public police action API for classifiers/qdiscs&n; */
macro_line|#include &lt;net/sch_generic.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
DECL|macro|tca_gen
mdefine_line|#define tca_gen(name) &bslash;&n;struct tcf_##name *next; &bslash;&n;&t;u32 index; &bslash;&n;&t;int refcnt; &bslash;&n;&t;int bindcnt; &bslash;&n;&t;u32 capab; &bslash;&n;&t;int action; &bslash;&n;&t;struct tcf_t tm; &bslash;&n;&t;struct gnet_stats_basic bstats; &bslash;&n;&t;struct gnet_stats_queue qstats; &bslash;&n;&t;struct gnet_stats_rate_est rate_est; &bslash;&n;&t;spinlock_t *stats_lock; &bslash;&n;&t;spinlock_t lock
DECL|struct|tcf_police
r_struct
id|tcf_police
(brace
id|tca_gen
c_func
(paren
id|police
)paren
suffix:semicolon
DECL|member|result
r_int
id|result
suffix:semicolon
DECL|member|ewma_rate
id|u32
id|ewma_rate
suffix:semicolon
DECL|member|burst
id|u32
id|burst
suffix:semicolon
DECL|member|mtu
id|u32
id|mtu
suffix:semicolon
DECL|member|toks
id|u32
id|toks
suffix:semicolon
DECL|member|ptoks
id|u32
id|ptoks
suffix:semicolon
DECL|member|t_c
id|psched_time_t
id|t_c
suffix:semicolon
DECL|member|R_tab
r_struct
id|qdisc_rate_table
op_star
id|R_tab
suffix:semicolon
DECL|member|P_tab
r_struct
id|qdisc_rate_table
op_star
id|P_tab
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ACT
DECL|macro|ACT_P_CREATED
mdefine_line|#define ACT_P_CREATED 1
DECL|macro|ACT_P_DELETED
mdefine_line|#define ACT_P_DELETED 1
DECL|struct|tcf_act_hdr
r_struct
id|tcf_act_hdr
(brace
id|tca_gen
c_func
(paren
id|act_hdr
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_action
r_struct
id|tc_action
(brace
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
DECL|member|ops
r_struct
id|tc_action_ops
op_star
id|ops
suffix:semicolon
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* for backward compat(TCA_OLD_COMPAT) */
DECL|member|order
id|__u32
id|order
suffix:semicolon
DECL|member|next
r_struct
id|tc_action
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TCA_CAP_NONE
mdefine_line|#define TCA_CAP_NONE 0
DECL|struct|tc_action_ops
r_struct
id|tc_action_ops
(brace
DECL|member|next
r_struct
id|tc_action_ops
op_star
id|next
suffix:semicolon
DECL|member|kind
r_char
id|kind
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* TBD to match kind */
DECL|member|capab
id|__u32
id|capab
suffix:semicolon
multiline_comment|/* capabilities includes 4 bit version */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|act
r_int
(paren
op_star
id|act
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
DECL|member|get_stats
r_int
(paren
op_star
id|get_stats
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
DECL|member|dump
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|cleanup
r_int
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|tc_action
op_star
comma
r_int
id|bind
)paren
suffix:semicolon
DECL|member|lookup
r_int
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|tc_action
op_star
comma
id|u32
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|rtattr
op_star
comma
r_struct
id|rtattr
op_star
comma
r_struct
id|tc_action
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|walk
r_int
(paren
op_star
id|walk
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|netlink_callback
op_star
comma
r_int
comma
r_struct
id|tc_action
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|tcf_register_action
c_func
(paren
r_struct
id|tc_action_ops
op_star
id|a
)paren
suffix:semicolon
r_extern
r_int
id|tcf_unregister_action
c_func
(paren
r_struct
id|tc_action_ops
op_star
id|a
)paren
suffix:semicolon
r_extern
r_void
id|tcf_action_destroy
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
suffix:semicolon
r_extern
r_int
id|tcf_action_exec
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
r_struct
id|tcf_result
op_star
id|res
)paren
suffix:semicolon
r_extern
r_struct
id|tc_action
op_star
id|tcf_action_init
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
r_char
op_star
id|n
comma
r_int
id|ovr
comma
r_int
id|bind
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_extern
r_struct
id|tc_action
op_star
id|tcf_action_init_1
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
r_char
op_star
id|n
comma
r_int
id|ovr
comma
r_int
id|bind
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_dump
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_dump_old
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_dump_1
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
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tcf_action_copy_stats
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tc_action
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_ACT */
r_extern
r_int
id|tcf_police
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
id|p
)paren
suffix:semicolon
r_extern
r_void
id|tcf_police_destroy
c_func
(paren
r_struct
id|tcf_police
op_star
id|p
)paren
suffix:semicolon
r_extern
r_struct
id|tcf_police
op_star
id|tcf_police_locate
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
)paren
suffix:semicolon
r_extern
r_int
id|tcf_police_dump
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
id|p
)paren
suffix:semicolon
r_extern
r_int
id|tcf_police_dump_stats
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
id|p
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|tcf_police_release
id|tcf_police_release
c_func
(paren
r_struct
id|tcf_police
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
macro_line|#ifdef CONFIG_NET_CLS_ACT
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
(brace
id|p-&gt;bindcnt
op_decrement
suffix:semicolon
)brace
id|p-&gt;refcnt
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;refcnt
op_le
l_int|0
op_logical_and
op_logical_neg
id|p-&gt;bindcnt
)paren
(brace
id|tcf_police_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#else
r_if
c_cond
(paren
id|p
op_logical_and
op_decrement
id|p-&gt;refcnt
op_eq
l_int|0
)paren
id|tcf_police_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_CLS_ACT */
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
eof
