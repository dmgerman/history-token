multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the Forwarding Information Base.&n; *&n; * Authors:&t;A.N.Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _NET_IP_FIB_H
DECL|macro|_NET_IP_FIB_H
mdefine_line|#define _NET_IP_FIB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
DECL|struct|kern_rta
r_struct
id|kern_rta
(brace
DECL|member|rta_dst
r_void
op_star
id|rta_dst
suffix:semicolon
DECL|member|rta_src
r_void
op_star
id|rta_src
suffix:semicolon
DECL|member|rta_iif
r_int
op_star
id|rta_iif
suffix:semicolon
DECL|member|rta_oif
r_int
op_star
id|rta_oif
suffix:semicolon
DECL|member|rta_gw
r_void
op_star
id|rta_gw
suffix:semicolon
DECL|member|rta_priority
id|u32
op_star
id|rta_priority
suffix:semicolon
DECL|member|rta_prefsrc
r_void
op_star
id|rta_prefsrc
suffix:semicolon
DECL|member|rta_mx
r_struct
id|rtattr
op_star
id|rta_mx
suffix:semicolon
DECL|member|rta_mp
r_struct
id|rtattr
op_star
id|rta_mp
suffix:semicolon
DECL|member|rta_protoinfo
r_int
r_char
op_star
id|rta_protoinfo
suffix:semicolon
DECL|member|rta_flow
r_int
r_char
op_star
id|rta_flow
suffix:semicolon
DECL|member|rta_ci
r_struct
id|rta_cacheinfo
op_star
id|rta_ci
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fib_nh
r_struct
id|fib_nh
(brace
DECL|member|nh_dev
r_struct
id|net_device
op_star
id|nh_dev
suffix:semicolon
DECL|member|nh_flags
r_int
id|nh_flags
suffix:semicolon
DECL|member|nh_scope
r_int
r_char
id|nh_scope
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_MULTIPATH
DECL|member|nh_weight
r_int
id|nh_weight
suffix:semicolon
DECL|member|nh_power
r_int
id|nh_power
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
DECL|member|nh_tclassid
id|__u32
id|nh_tclassid
suffix:semicolon
macro_line|#endif
DECL|member|nh_oif
r_int
id|nh_oif
suffix:semicolon
DECL|member|nh_gw
id|u32
id|nh_gw
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure contains data shared by many of routes.&n; */
DECL|struct|fib_info
r_struct
id|fib_info
(brace
DECL|member|fib_next
r_struct
id|fib_info
op_star
id|fib_next
suffix:semicolon
DECL|member|fib_prev
r_struct
id|fib_info
op_star
id|fib_prev
suffix:semicolon
DECL|member|fib_treeref
r_int
id|fib_treeref
suffix:semicolon
DECL|member|fib_clntref
id|atomic_t
id|fib_clntref
suffix:semicolon
DECL|member|fib_dead
r_int
id|fib_dead
suffix:semicolon
DECL|member|fib_flags
r_int
id|fib_flags
suffix:semicolon
DECL|member|fib_protocol
r_int
id|fib_protocol
suffix:semicolon
DECL|member|fib_prefsrc
id|u32
id|fib_prefsrc
suffix:semicolon
DECL|member|fib_priority
id|u32
id|fib_priority
suffix:semicolon
DECL|member|fib_metrics
r_int
id|fib_metrics
(braket
id|RTAX_MAX
)braket
suffix:semicolon
DECL|macro|fib_mtu
mdefine_line|#define fib_mtu fib_metrics[RTAX_MTU-1]
DECL|macro|fib_window
mdefine_line|#define fib_window fib_metrics[RTAX_WINDOW-1]
DECL|macro|fib_rtt
mdefine_line|#define fib_rtt fib_metrics[RTAX_RTT-1]
DECL|macro|fib_advmss
mdefine_line|#define fib_advmss fib_metrics[RTAX_ADVMSS-1]
DECL|member|fib_nhs
r_int
id|fib_nhs
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_MULTIPATH
DECL|member|fib_power
r_int
id|fib_power
suffix:semicolon
macro_line|#endif
DECL|member|fib_nh
r_struct
id|fib_nh
id|fib_nh
(braket
l_int|0
)braket
suffix:semicolon
DECL|macro|fib_dev
mdefine_line|#define fib_dev&t;&t;fib_nh[0].nh_dev
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
r_struct
id|fib_rule
suffix:semicolon
macro_line|#endif
DECL|struct|fib_result
r_struct
id|fib_result
(brace
DECL|member|prefixlen
r_int
r_char
id|prefixlen
suffix:semicolon
DECL|member|nh_sel
r_int
r_char
id|nh_sel
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|scope
r_int
r_char
id|scope
suffix:semicolon
DECL|member|fi
r_struct
id|fib_info
op_star
id|fi
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
DECL|member|r
r_struct
id|fib_rule
op_star
id|r
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_IP_ROUTE_MULTIPATH
DECL|macro|FIB_RES_NH
mdefine_line|#define FIB_RES_NH(res)&t;&t;((res).fi-&gt;fib_nh[(res).nh_sel])
DECL|macro|FIB_RES_RESET
mdefine_line|#define FIB_RES_RESET(res)&t;((res).nh_sel = 0)
macro_line|#else /* CONFIG_IP_ROUTE_MULTIPATH */
DECL|macro|FIB_RES_NH
mdefine_line|#define FIB_RES_NH(res)&t;&t;((res).fi-&gt;fib_nh[0])
DECL|macro|FIB_RES_RESET
mdefine_line|#define FIB_RES_RESET(res)
macro_line|#endif /* CONFIG_IP_ROUTE_MULTIPATH */
DECL|macro|FIB_RES_PREFSRC
mdefine_line|#define FIB_RES_PREFSRC(res)&t;&t;((res).fi-&gt;fib_prefsrc ? : __fib_res_prefsrc(&amp;res))
DECL|macro|FIB_RES_GW
mdefine_line|#define FIB_RES_GW(res)&t;&t;&t;(FIB_RES_NH(res).nh_gw)
DECL|macro|FIB_RES_DEV
mdefine_line|#define FIB_RES_DEV(res)&t;&t;(FIB_RES_NH(res).nh_dev)
DECL|macro|FIB_RES_OIF
mdefine_line|#define FIB_RES_OIF(res)&t;&t;(FIB_RES_NH(res).nh_oif)
DECL|struct|fib_table
r_struct
id|fib_table
(brace
DECL|member|tb_id
r_int
r_char
id|tb_id
suffix:semicolon
DECL|member|tb_stamp
r_int
id|tb_stamp
suffix:semicolon
DECL|member|tb_lookup
r_int
(paren
op_star
id|tb_lookup
)paren
(paren
r_struct
id|fib_table
op_star
id|tb
comma
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
DECL|member|tb_insert
r_int
(paren
op_star
id|tb_insert
)paren
(paren
r_struct
id|fib_table
op_star
id|table
comma
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|kern_rta
op_star
id|rta
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_struct
id|netlink_skb_parms
op_star
id|req
)paren
suffix:semicolon
DECL|member|tb_delete
r_int
(paren
op_star
id|tb_delete
)paren
(paren
r_struct
id|fib_table
op_star
id|table
comma
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|kern_rta
op_star
id|rta
comma
r_struct
id|nlmsghdr
op_star
id|n
comma
r_struct
id|netlink_skb_parms
op_star
id|req
)paren
suffix:semicolon
DECL|member|tb_dump
r_int
(paren
op_star
id|tb_dump
)paren
(paren
r_struct
id|fib_table
op_star
id|table
comma
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
suffix:semicolon
DECL|member|tb_flush
r_int
(paren
op_star
id|tb_flush
)paren
(paren
r_struct
id|fib_table
op_star
id|table
)paren
suffix:semicolon
DECL|member|tb_select_default
r_void
(paren
op_star
id|tb_select_default
)paren
(paren
r_struct
id|fib_table
op_star
id|table
comma
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
DECL|member|tb_data
r_int
r_char
id|tb_data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef CONFIG_IP_MULTIPLE_TABLES
r_extern
r_struct
id|fib_table
op_star
id|ip_fib_local_table
suffix:semicolon
r_extern
r_struct
id|fib_table
op_star
id|ip_fib_main_table
suffix:semicolon
DECL|function|fib_get_table
r_static
r_inline
r_struct
id|fib_table
op_star
id|fib_get_table
c_func
(paren
r_int
id|id
)paren
(brace
r_if
c_cond
(paren
id|id
op_ne
id|RT_TABLE_LOCAL
)paren
r_return
id|ip_fib_main_table
suffix:semicolon
r_return
id|ip_fib_local_table
suffix:semicolon
)brace
DECL|function|fib_new_table
r_static
r_inline
r_struct
id|fib_table
op_star
id|fib_new_table
c_func
(paren
r_int
id|id
)paren
(brace
r_return
id|fib_get_table
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
DECL|function|fib_lookup
r_static
r_inline
r_int
id|fib_lookup
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
id|ip_fib_local_table
op_member_access_from_pointer
id|tb_lookup
c_func
(paren
id|ip_fib_local_table
comma
id|flp
comma
id|res
)paren
op_logical_and
id|ip_fib_main_table
op_member_access_from_pointer
id|tb_lookup
c_func
(paren
id|ip_fib_main_table
comma
id|flp
comma
id|res
)paren
)paren
r_return
op_minus
id|ENETUNREACH
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fib_select_default
r_static
r_inline
r_void
id|fib_select_default
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
id|FIB_RES_GW
c_func
(paren
op_star
id|res
)paren
op_logical_and
id|FIB_RES_NH
id|res.nh_scope
op_eq
id|RT_SCOPE_LINK
)paren
id|ip_fib_main_table
op_member_access_from_pointer
id|tb_select_default
c_func
(paren
id|ip_fib_main_table
comma
id|flp
comma
id|res
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_IP_MULTIPLE_TABLES */
DECL|macro|ip_fib_local_table
mdefine_line|#define ip_fib_local_table (fib_tables[RT_TABLE_LOCAL])
DECL|macro|ip_fib_main_table
mdefine_line|#define ip_fib_main_table (fib_tables[RT_TABLE_MAIN])
r_extern
r_struct
id|fib_table
op_star
id|fib_tables
(braket
id|RT_TABLE_MAX
op_plus
l_int|1
)braket
suffix:semicolon
r_extern
r_int
id|fib_lookup
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
r_extern
r_struct
id|fib_table
op_star
id|__fib_new_table
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
r_extern
r_void
id|fib_rule_put
c_func
(paren
r_struct
id|fib_rule
op_star
id|r
)paren
suffix:semicolon
DECL|function|fib_get_table
r_static
r_inline
r_struct
id|fib_table
op_star
id|fib_get_table
c_func
(paren
r_int
id|id
)paren
(brace
r_if
c_cond
(paren
id|id
op_eq
l_int|0
)paren
id|id
op_assign
id|RT_TABLE_MAIN
suffix:semicolon
r_return
id|fib_tables
(braket
id|id
)braket
suffix:semicolon
)brace
DECL|function|fib_new_table
r_static
r_inline
r_struct
id|fib_table
op_star
id|fib_new_table
c_func
(paren
r_int
id|id
)paren
(brace
r_if
c_cond
(paren
id|id
op_eq
l_int|0
)paren
id|id
op_assign
id|RT_TABLE_MAIN
suffix:semicolon
r_return
id|fib_tables
(braket
id|id
)braket
ques
c_cond
suffix:colon
id|__fib_new_table
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
r_extern
r_void
id|fib_select_default
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IP_MULTIPLE_TABLES */
multiline_comment|/* Exported by fib_frontend.c */
r_extern
r_void
id|ip_fib_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fib_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|inet_rtm_delroute
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
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet_rtm_newroute
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
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet_rtm_getroute
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
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet_dump_fib
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
suffix:semicolon
r_extern
r_int
id|fib_validate_source
c_func
(paren
id|u32
id|src
comma
id|u32
id|dst
comma
id|u8
id|tos
comma
r_int
id|oif
comma
r_struct
id|net_device
op_star
id|dev
comma
id|u32
op_star
id|spec_dst
comma
id|u32
op_star
id|itag
)paren
suffix:semicolon
r_extern
r_void
id|fib_select_multipath
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp
comma
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
multiline_comment|/* Exported by fib_semantics.c */
r_extern
r_int
id|ip_fib_check_default
c_func
(paren
id|u32
id|gw
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|fib_release_info
c_func
(paren
r_struct
id|fib_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|fib_semantic_match
c_func
(paren
r_int
id|type
comma
r_struct
id|fib_info
op_star
comma
r_const
r_struct
id|flowi
op_star
comma
r_struct
id|fib_result
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|fib_info
op_star
id|fib_create_info
c_func
(paren
r_const
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|kern_rta
op_star
id|rta
comma
r_const
r_struct
id|nlmsghdr
op_star
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_extern
r_int
id|fib_nh_match
c_func
(paren
r_struct
id|rtmsg
op_star
id|r
comma
r_struct
id|nlmsghdr
op_star
comma
r_struct
id|kern_rta
op_star
id|rta
comma
r_struct
id|fib_info
op_star
id|fi
)paren
suffix:semicolon
r_extern
r_int
id|fib_dump_info
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|pid
comma
id|u32
id|seq
comma
r_int
id|event
comma
id|u8
id|tb_id
comma
id|u8
id|type
comma
id|u8
id|scope
comma
r_void
op_star
id|dst
comma
r_int
id|dst_len
comma
id|u8
id|tos
comma
r_struct
id|fib_info
op_star
id|fi
)paren
suffix:semicolon
r_extern
r_int
id|fib_sync_down
c_func
(paren
id|u32
id|local
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|force
)paren
suffix:semicolon
r_extern
r_int
id|fib_sync_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|fib_convert_rtentry
c_func
(paren
r_int
id|cmd
comma
r_struct
id|nlmsghdr
op_star
id|nl
comma
r_struct
id|rtmsg
op_star
id|rtm
comma
r_struct
id|kern_rta
op_star
id|rta
comma
r_struct
id|rtentry
op_star
id|r
)paren
suffix:semicolon
r_extern
r_void
id|fib_node_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_int
id|type
comma
r_int
id|dead
comma
r_struct
id|fib_info
op_star
id|fi
comma
id|u32
id|prefix
comma
id|u32
id|mask
)paren
suffix:semicolon
r_extern
id|u32
id|__fib_res_prefsrc
c_func
(paren
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
multiline_comment|/* Exported by fib_hash.c */
r_extern
r_struct
id|fib_table
op_star
id|fib_hash_init
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
multiline_comment|/* Exported by fib_rules.c */
r_extern
r_int
id|inet_rtm_delrule
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
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet_rtm_newrule
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
id|nlh
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|inet_dump_rules
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
suffix:semicolon
r_extern
id|u32
id|fib_rules_map_destination
c_func
(paren
id|u32
id|daddr
comma
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
r_extern
id|u32
id|fib_rules_tclass
c_func
(paren
r_struct
id|fib_result
op_star
id|res
)paren
suffix:semicolon
macro_line|#endif
r_extern
id|u32
id|fib_rules_policy
c_func
(paren
id|u32
id|saddr
comma
r_struct
id|fib_result
op_star
id|res
comma
r_int
op_star
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|fib_rules_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|fib_combine_itag
r_static
r_inline
r_void
id|fib_combine_itag
c_func
(paren
id|u32
op_star
id|itag
comma
r_struct
id|fib_result
op_star
id|res
)paren
(brace
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
id|u32
id|rtag
suffix:semicolon
macro_line|#endif
op_star
id|itag
op_assign
id|FIB_RES_NH
id|res.nh_tclassid
op_lshift
l_int|16
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
id|rtag
op_assign
id|fib_rules_tclass
c_func
(paren
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|itag
op_eq
l_int|0
)paren
op_star
id|itag
op_assign
(paren
id|rtag
op_lshift
l_int|16
)paren
suffix:semicolon
op_star
id|itag
op_or_assign
(paren
id|rtag
op_rshift
l_int|16
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
r_extern
r_void
id|free_fib_info
c_func
(paren
r_struct
id|fib_info
op_star
id|fi
)paren
suffix:semicolon
DECL|function|fib_info_put
r_static
r_inline
r_void
id|fib_info_put
c_func
(paren
r_struct
id|fib_info
op_star
id|fi
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|fi-&gt;fib_clntref
)paren
)paren
id|free_fib_info
c_func
(paren
id|fi
)paren
suffix:semicolon
)brace
DECL|function|fib_res_put
r_static
r_inline
r_void
id|fib_res_put
c_func
(paren
r_struct
id|fib_result
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
id|res-&gt;fi
)paren
id|fib_info_put
c_func
(paren
id|res-&gt;fi
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTIPLE_TABLES
r_if
c_cond
(paren
id|res-&gt;r
)paren
id|fib_rule_put
c_func
(paren
id|res-&gt;r
)paren
suffix:semicolon
macro_line|#endif
)brace
r_extern
r_int
id|fib_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fib_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif  /* _NET_FIB_H */
eof
