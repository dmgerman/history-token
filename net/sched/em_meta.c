multiline_comment|/*&n; * net/sched/em_meta.c&t;Metadata ematch&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Thomas Graf &lt;tgraf@suug.ch&gt;&n; *&n; * ==========================================================================&n; * &n; * &t;The metadata ematch compares two meta objects where each object&n; * &t;represents either a meta value stored in the kernel or a static&n; * &t;value provided by userspace. The objects are not provided by&n; * &t;userspace itself but rather a definition providing the information&n; * &t;to build them. Every object is of a certain type which must be&n; * &t;equal to the object it is being compared to.&n; *&n; * &t;The definition of a objects conists of the type (meta type), a&n; * &t;identifier (meta id) and additional type specific information.&n; * &t;The meta id is either TCF_META_TYPE_VALUE for values provided by&n; * &t;userspace or a index to the meta operations table consisting of&n; * &t;function pointers to type specific meta data collectors returning&n; * &t;the value of the requested meta value.&n; *&n; * &t;         lvalue                                   rvalue&n; * &t;      +-----------+                           +-----------+&n; * &t;      | type: INT |                           | type: INT |&n; * &t; def  | id: INDEV |                           | id: VALUE |&n; * &t;      | data:     |                           | data: 3   |&n; * &t;      +-----------+                           +-----------+&n; * &t;            |                                       |&n; * &t;            ---&gt; meta_ops[INT][INDEV](...)          |&n; *                            |                            |&n; * &t;            -----------                             |&n; * &t;            V                                       V&n; * &t;      +-----------+                           +-----------+&n; * &t;      | type: INT |                           | type: INT |&n; * &t; obj  | id: INDEV |                           | id: VALUE |&n; * &t;      | data: 2   |&lt;--data got filled out     | data: 3   |&n; * &t;      +-----------+                           +-----------+&n; * &t;            |                                         |&n; * &t;            --------------&gt; 2  equals 3 &lt;--------------&n; *&n; * &t;This is a simplified schema, the complexity varies depending&n; * &t;on the meta type. Obviously, the length of the data must also&n; * &t;be provided for non-numeric types.&n; *&n; * &t;Additionaly, type dependant modifiers such as shift operators&n; * &t;or mask may be applied to extend the functionaliy. As of now,&n; * &t;the variable length type supports shifting the byte string to&n; * &t;the right, eating up any number of octets and thus supporting&n; * &t;wildcard interface name comparisons such as &quot;ppp%&quot; matching&n; * &t;ppp0..9.&n; *&n; * &t;NOTE: Certain meta values depend on other subsystems and are&n; * &t;      only available if that subsytem is enabled in the kernel.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/tc_ematch/tc_em_meta.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/pkt_cls.h&gt;
DECL|struct|meta_obj
r_struct
id|meta_obj
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|meta_value
r_struct
id|meta_value
(brace
DECL|member|hdr
r_struct
id|tcf_meta_val
id|hdr
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|meta_match
r_struct
id|meta_match
(brace
DECL|member|lvalue
r_struct
id|meta_value
id|lvalue
suffix:semicolon
DECL|member|rvalue
r_struct
id|meta_value
id|rvalue
suffix:semicolon
)brace
suffix:semicolon
DECL|function|meta_id
r_static
r_inline
r_int
id|meta_id
c_func
(paren
r_struct
id|meta_value
op_star
id|v
)paren
(brace
r_return
id|TCF_META_ID
c_func
(paren
id|v-&gt;hdr.kind
)paren
suffix:semicolon
)brace
DECL|function|meta_type
r_static
r_inline
r_int
id|meta_type
c_func
(paren
r_struct
id|meta_value
op_star
id|v
)paren
(brace
r_return
id|TCF_META_TYPE
c_func
(paren
id|v-&gt;hdr.kind
)paren
suffix:semicolon
)brace
DECL|macro|META_COLLECTOR
mdefine_line|#define META_COLLECTOR(FUNC) static void meta_##FUNC(struct sk_buff *skb, &bslash;&n;&t;struct tcf_pkt_info *info, struct meta_value *v, &bslash;&n;&t;struct meta_obj *dst, int *err)
multiline_comment|/**************************************************************************&n; * System status &amp; misc&n; **************************************************************************/
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_random
)paren
(brace
id|get_random_bytes
c_func
(paren
op_amp
id|dst-&gt;value
comma
r_sizeof
(paren
id|dst-&gt;value
)paren
)paren
suffix:semicolon
)brace
DECL|function|fixed_loadavg
r_static
r_inline
r_int
r_int
id|fixed_loadavg
c_func
(paren
r_int
id|load
)paren
(brace
r_int
id|rnd_load
op_assign
id|load
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
r_int
id|rnd_frac
op_assign
(paren
(paren
id|rnd_load
op_amp
(paren
id|FIXED_1
op_minus
l_int|1
)paren
)paren
op_star
l_int|100
)paren
op_rshift
id|FSHIFT
suffix:semicolon
r_return
(paren
(paren
id|rnd_load
op_rshift
id|FSHIFT
)paren
op_star
l_int|100
)paren
op_plus
id|rnd_frac
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_loadavg_0
)paren
(brace
id|dst-&gt;value
op_assign
id|fixed_loadavg
c_func
(paren
id|avenrun
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_loadavg_1
)paren
(brace
id|dst-&gt;value
op_assign
id|fixed_loadavg
c_func
(paren
id|avenrun
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_loadavg_2
)paren
(brace
id|dst-&gt;value
op_assign
id|fixed_loadavg
c_func
(paren
id|avenrun
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; * Device names &amp; indices&n; **************************************************************************/
DECL|function|int_dev
r_static
r_inline
r_int
id|int_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|meta_obj
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|dev
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dst-&gt;value
op_assign
id|dev-&gt;ifindex
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|var_dev
r_static
r_inline
r_int
id|var_dev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|meta_obj
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|dev
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dst-&gt;value
op_assign
(paren
r_int
r_int
)paren
id|dev-&gt;name
suffix:semicolon
id|dst-&gt;len
op_assign
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_dev
)paren
(brace
op_star
id|err
op_assign
id|int_dev
c_func
(paren
id|skb-&gt;dev
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|var_dev
)paren
(brace
op_star
id|err
op_assign
id|var_dev
c_func
(paren
id|skb-&gt;dev
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_indev
)paren
(brace
op_star
id|err
op_assign
id|int_dev
c_func
(paren
id|skb-&gt;input_dev
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|var_indev
)paren
(brace
op_star
id|err
op_assign
id|var_dev
c_func
(paren
id|skb-&gt;input_dev
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_realdev
)paren
(brace
op_star
id|err
op_assign
id|int_dev
c_func
(paren
id|skb-&gt;real_dev
comma
id|dst
)paren
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|var_realdev
)paren
(brace
op_star
id|err
op_assign
id|var_dev
c_func
(paren
id|skb-&gt;real_dev
comma
id|dst
)paren
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; * skb attributes&n; **************************************************************************/
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_priority
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;priority
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_protocol
)paren
(brace
multiline_comment|/* Let userspace take care of the byte ordering */
id|dst-&gt;value
op_assign
id|skb-&gt;protocol
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_security
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;security
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_pkttype
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;pkt_type
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_pktlen
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;len
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_datalen
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;data_len
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_maclen
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;mac_len
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; * Netfilter&n; **************************************************************************/
macro_line|#ifdef CONFIG_NETFILTER
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_nfmark
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;nfmark
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/**************************************************************************&n; * Traffic Control&n; **************************************************************************/
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_tcindex
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;tc_index
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_ACT
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_tcverd
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;tc_verd
suffix:semicolon
)brace
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_tcclassid
)paren
(brace
id|dst-&gt;value
op_assign
id|skb-&gt;tc_classid
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/**************************************************************************&n; * Routing&n; **************************************************************************/
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_rtclassid
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|skb-&gt;dst
op_eq
l_int|NULL
)paren
)paren
op_star
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|dst-&gt;value
op_assign
id|skb-&gt;dst-&gt;tclassid
suffix:semicolon
)brace
macro_line|#endif
DECL|function|META_COLLECTOR
id|META_COLLECTOR
c_func
(paren
id|int_rtiif
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|skb-&gt;dst
op_eq
l_int|NULL
)paren
)paren
op_star
id|err
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|dst-&gt;value
op_assign
(paren
(paren
r_struct
id|rtable
op_star
)paren
id|skb-&gt;dst
)paren
op_member_access_from_pointer
id|fl.iif
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; * Meta value collectors assignment table&n; **************************************************************************/
DECL|struct|meta_ops
r_struct
id|meta_ops
(brace
DECL|member|get
r_void
(paren
op_star
id|get
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|tcf_pkt_info
op_star
comma
r_struct
id|meta_value
op_star
comma
r_struct
id|meta_obj
op_star
comma
r_int
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Meta value operations table listing all meta value collectors and&n; * assigns them to a type and meta id. */
DECL|variable|__meta_ops
r_static
r_struct
id|meta_ops
id|__meta_ops
(braket
id|TCF_META_TYPE_MAX
op_plus
l_int|1
)braket
(braket
id|TCF_META_ID_MAX
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|TCF_META_TYPE_VAR
)braket
op_assign
(brace
(braket
id|TCF_META_ID_DEV
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_var_dev
)brace
comma
(braket
id|TCF_META_ID_INDEV
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_var_indev
)brace
comma
(braket
id|TCF_META_ID_REALDEV
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_var_realdev
)brace
)brace
comma
(braket
id|TCF_META_TYPE_INT
)braket
op_assign
(brace
(braket
id|TCF_META_ID_RANDOM
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_random
)brace
comma
(braket
id|TCF_META_ID_LOADAVG_0
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_loadavg_0
)brace
comma
(braket
id|TCF_META_ID_LOADAVG_1
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_loadavg_1
)brace
comma
(braket
id|TCF_META_ID_LOADAVG_2
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_loadavg_2
)brace
comma
(braket
id|TCF_META_ID_DEV
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_dev
)brace
comma
(braket
id|TCF_META_ID_INDEV
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_indev
)brace
comma
(braket
id|TCF_META_ID_REALDEV
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_realdev
)brace
comma
(braket
id|TCF_META_ID_PRIORITY
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_priority
)brace
comma
(braket
id|TCF_META_ID_PROTOCOL
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_protocol
)brace
comma
(braket
id|TCF_META_ID_SECURITY
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_security
)brace
comma
(braket
id|TCF_META_ID_PKTTYPE
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_pkttype
)brace
comma
(braket
id|TCF_META_ID_PKTLEN
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_pktlen
)brace
comma
(braket
id|TCF_META_ID_DATALEN
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_datalen
)brace
comma
(braket
id|TCF_META_ID_MACLEN
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_maclen
)brace
comma
macro_line|#ifdef CONFIG_NETFILTER
(braket
id|TCF_META_ID_NFMARK
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_nfmark
)brace
comma
macro_line|#endif
(braket
id|TCF_META_ID_TCINDEX
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_tcindex
)brace
comma
macro_line|#ifdef CONFIG_NET_CLS_ACT
(braket
id|TCF_META_ID_TCVERDICT
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_tcverd
)brace
comma
(braket
id|TCF_META_ID_TCCLASSID
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_tcclassid
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
(braket
id|TCF_META_ID_RTCLASSID
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_rtclassid
)brace
comma
macro_line|#endif
(braket
id|TCF_META_ID_RTIIF
)braket
op_assign
(brace
dot
id|get
op_assign
id|meta_int_rtiif
)brace
)brace
)brace
suffix:semicolon
DECL|function|meta_ops
r_static
r_inline
r_struct
id|meta_ops
op_star
id|meta_ops
c_func
(paren
r_struct
id|meta_value
op_star
id|val
)paren
(brace
r_return
op_amp
id|__meta_ops
(braket
id|meta_type
c_func
(paren
id|val
)paren
)braket
(braket
id|meta_id
c_func
(paren
id|val
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; * Type specific operations for TCF_META_TYPE_VAR&n; **************************************************************************/
DECL|function|meta_var_compare
r_static
r_int
id|meta_var_compare
c_func
(paren
r_struct
id|meta_obj
op_star
id|a
comma
r_struct
id|meta_obj
op_star
id|b
)paren
(brace
r_int
id|r
op_assign
id|a-&gt;len
op_minus
id|b-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|0
)paren
id|r
op_assign
id|memcmp
c_func
(paren
(paren
r_void
op_star
)paren
id|a-&gt;value
comma
(paren
r_void
op_star
)paren
id|b-&gt;value
comma
id|a-&gt;len
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|meta_var_change
r_static
r_int
id|meta_var_change
c_func
(paren
r_struct
id|meta_value
op_star
id|dst
comma
r_struct
id|rtattr
op_star
id|rta
)paren
(brace
r_int
id|len
op_assign
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
suffix:semicolon
id|dst-&gt;val
op_assign
(paren
r_int
r_int
)paren
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dst-&gt;val
op_eq
l_int|0UL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|dst-&gt;val
comma
id|RTA_DATA
c_func
(paren
id|rta
)paren
comma
id|len
)paren
suffix:semicolon
id|dst-&gt;len
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|meta_var_destroy
r_static
r_void
id|meta_var_destroy
c_func
(paren
r_struct
id|meta_value
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v-&gt;val
)paren
id|kfree
c_func
(paren
(paren
r_void
op_star
)paren
id|v-&gt;val
)paren
suffix:semicolon
)brace
DECL|function|meta_var_apply_extras
r_static
r_void
id|meta_var_apply_extras
c_func
(paren
r_struct
id|meta_value
op_star
id|v
comma
r_struct
id|meta_obj
op_star
id|dst
)paren
(brace
r_int
id|shift
op_assign
id|v-&gt;hdr.shift
suffix:semicolon
r_if
c_cond
(paren
id|shift
op_logical_and
id|shift
OL
id|dst-&gt;len
)paren
id|dst-&gt;len
op_sub_assign
id|shift
suffix:semicolon
)brace
DECL|function|meta_var_dump
r_static
r_int
id|meta_var_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|meta_value
op_star
id|v
comma
r_int
id|tlv
)paren
(brace
r_if
c_cond
(paren
id|v-&gt;val
op_logical_and
id|v-&gt;len
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|tlv
comma
id|v-&gt;len
comma
(paren
r_void
op_star
)paren
id|v-&gt;val
)paren
suffix:semicolon
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
multiline_comment|/**************************************************************************&n; * Type specific operations for TCF_META_TYPE_INT&n; **************************************************************************/
DECL|function|meta_int_compare
r_static
r_int
id|meta_int_compare
c_func
(paren
r_struct
id|meta_obj
op_star
id|a
comma
r_struct
id|meta_obj
op_star
id|b
)paren
(brace
multiline_comment|/* Let gcc optimize it, the unlikely is not really based on&n;&t; * some numbers but jump free code for mismatches seems&n;&t; * more logical. */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|a
op_eq
id|b
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|a
OL
id|b
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|meta_int_change
r_static
r_int
id|meta_int_change
c_func
(paren
r_struct
id|meta_value
op_star
id|dst
comma
r_struct
id|rtattr
op_star
id|rta
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
op_ge
r_sizeof
(paren
r_int
r_int
)paren
)paren
(brace
id|dst-&gt;val
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|RTA_DATA
c_func
(paren
id|rta
)paren
suffix:semicolon
id|dst-&gt;len
op_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
op_eq
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|dst-&gt;val
op_assign
op_star
(paren
id|u32
op_star
)paren
id|RTA_DATA
c_func
(paren
id|rta
)paren
suffix:semicolon
id|dst-&gt;len
op_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|meta_int_apply_extras
r_static
r_void
id|meta_int_apply_extras
c_func
(paren
r_struct
id|meta_value
op_star
id|v
comma
r_struct
id|meta_obj
op_star
id|dst
)paren
(brace
r_if
c_cond
(paren
id|v-&gt;hdr.shift
)paren
id|dst-&gt;value
op_rshift_assign
id|v-&gt;hdr.shift
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;val
)paren
id|dst-&gt;value
op_and_assign
id|v-&gt;val
suffix:semicolon
)brace
DECL|function|meta_int_dump
r_static
r_int
id|meta_int_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|meta_value
op_star
id|v
comma
r_int
id|tlv
)paren
(brace
r_if
c_cond
(paren
id|v-&gt;len
op_eq
r_sizeof
(paren
r_int
r_int
)paren
)paren
id|RTA_PUT
c_func
(paren
id|skb
comma
id|tlv
comma
r_sizeof
(paren
r_int
r_int
)paren
comma
op_amp
id|v-&gt;val
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|v-&gt;len
op_eq
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|u32
id|d
op_assign
id|v-&gt;val
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|tlv
comma
r_sizeof
(paren
id|d
)paren
comma
op_amp
id|d
)paren
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
multiline_comment|/**************************************************************************&n; * Type specific operations table&n; **************************************************************************/
DECL|struct|meta_type_ops
r_struct
id|meta_type_ops
(brace
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|meta_value
op_star
)paren
suffix:semicolon
DECL|member|compare
r_int
(paren
op_star
id|compare
)paren
(paren
r_struct
id|meta_obj
op_star
comma
r_struct
id|meta_obj
op_star
)paren
suffix:semicolon
DECL|member|change
r_int
(paren
op_star
id|change
)paren
(paren
r_struct
id|meta_value
op_star
comma
r_struct
id|rtattr
op_star
)paren
suffix:semicolon
DECL|member|apply_extras
r_void
(paren
op_star
id|apply_extras
)paren
(paren
r_struct
id|meta_value
op_star
comma
r_struct
id|meta_obj
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
id|meta_value
op_star
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__meta_type_ops
r_static
r_struct
id|meta_type_ops
id|__meta_type_ops
(braket
id|TCF_META_TYPE_MAX
op_plus
l_int|1
)braket
op_assign
(brace
(braket
id|TCF_META_TYPE_VAR
)braket
op_assign
(brace
dot
id|destroy
op_assign
id|meta_var_destroy
comma
dot
id|compare
op_assign
id|meta_var_compare
comma
dot
id|change
op_assign
id|meta_var_change
comma
dot
id|apply_extras
op_assign
id|meta_var_apply_extras
comma
dot
id|dump
op_assign
id|meta_var_dump
)brace
comma
(braket
id|TCF_META_TYPE_INT
)braket
op_assign
(brace
dot
id|compare
op_assign
id|meta_int_compare
comma
dot
id|change
op_assign
id|meta_int_change
comma
dot
id|apply_extras
op_assign
id|meta_int_apply_extras
comma
dot
id|dump
op_assign
id|meta_int_dump
)brace
)brace
suffix:semicolon
DECL|function|meta_type_ops
r_static
r_inline
r_struct
id|meta_type_ops
op_star
id|meta_type_ops
c_func
(paren
r_struct
id|meta_value
op_star
id|v
)paren
(brace
r_return
op_amp
id|__meta_type_ops
(braket
id|meta_type
c_func
(paren
id|v
)paren
)braket
suffix:semicolon
)brace
multiline_comment|/**************************************************************************&n; * Core&n; **************************************************************************/
DECL|function|meta_get
r_static
r_inline
r_int
id|meta_get
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_pkt_info
op_star
id|info
comma
r_struct
id|meta_value
op_star
id|v
comma
r_struct
id|meta_obj
op_star
id|dst
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|meta_id
c_func
(paren
id|v
)paren
op_eq
id|TCF_META_ID_VALUE
)paren
(brace
id|dst-&gt;value
op_assign
id|v-&gt;val
suffix:semicolon
id|dst-&gt;len
op_assign
id|v-&gt;len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|meta_ops
c_func
(paren
id|v
)paren
op_member_access_from_pointer
id|get
c_func
(paren
id|skb
comma
id|info
comma
id|v
comma
id|dst
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|meta_type_ops
c_func
(paren
id|v
)paren
op_member_access_from_pointer
id|apply_extras
)paren
id|meta_type_ops
c_func
(paren
id|v
)paren
op_member_access_from_pointer
id|apply_extras
c_func
(paren
id|v
comma
id|dst
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|em_meta_match
r_static
r_int
id|em_meta_match
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_ematch
op_star
id|m
comma
r_struct
id|tcf_pkt_info
op_star
id|info
)paren
(brace
r_int
id|r
suffix:semicolon
r_struct
id|meta_match
op_star
id|meta
op_assign
(paren
r_struct
id|meta_match
op_star
)paren
id|m-&gt;data
suffix:semicolon
r_struct
id|meta_obj
id|l_value
comma
id|r_value
suffix:semicolon
r_if
c_cond
(paren
id|meta_get
c_func
(paren
id|skb
comma
id|info
comma
op_amp
id|meta-&gt;lvalue
comma
op_amp
id|l_value
)paren
OL
l_int|0
op_logical_or
id|meta_get
c_func
(paren
id|skb
comma
id|info
comma
op_amp
id|meta-&gt;rvalue
comma
op_amp
id|r_value
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|r
op_assign
id|meta_type_ops
c_func
(paren
op_amp
id|meta-&gt;lvalue
)paren
op_member_access_from_pointer
id|compare
c_func
(paren
op_amp
id|l_value
comma
op_amp
id|r_value
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|meta-&gt;lvalue.hdr.op
)paren
(brace
r_case
id|TCF_EM_OPND_EQ
suffix:colon
r_return
op_logical_neg
id|r
suffix:semicolon
r_case
id|TCF_EM_OPND_LT
suffix:colon
r_return
id|r
OL
l_int|0
suffix:semicolon
r_case
id|TCF_EM_OPND_GT
suffix:colon
r_return
id|r
OG
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|meta_delete
r_static
r_inline
r_void
id|meta_delete
c_func
(paren
r_struct
id|meta_match
op_star
id|meta
)paren
(brace
r_struct
id|meta_type_ops
op_star
id|ops
op_assign
id|meta_type_ops
c_func
(paren
op_amp
id|meta-&gt;lvalue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_logical_and
id|ops-&gt;destroy
)paren
(brace
id|ops
op_member_access_from_pointer
id|destroy
c_func
(paren
op_amp
id|meta-&gt;lvalue
)paren
suffix:semicolon
id|ops
op_member_access_from_pointer
id|destroy
c_func
(paren
op_amp
id|meta-&gt;rvalue
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|meta
)paren
suffix:semicolon
)brace
DECL|function|meta_change_data
r_static
r_inline
r_int
id|meta_change_data
c_func
(paren
r_struct
id|meta_value
op_star
id|dst
comma
r_struct
id|rtattr
op_star
id|rta
)paren
(brace
r_if
c_cond
(paren
id|rta
)paren
(brace
r_if
c_cond
(paren
id|RTA_PAYLOAD
c_func
(paren
id|rta
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|meta_type_ops
c_func
(paren
id|dst
)paren
op_member_access_from_pointer
id|change
c_func
(paren
id|dst
comma
id|rta
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|meta_is_supported
r_static
r_inline
r_int
id|meta_is_supported
c_func
(paren
r_struct
id|meta_value
op_star
id|val
)paren
(brace
r_return
(paren
op_logical_neg
id|meta_id
c_func
(paren
id|val
)paren
op_logical_or
id|meta_ops
c_func
(paren
id|val
)paren
op_member_access_from_pointer
id|get
)paren
suffix:semicolon
)brace
DECL|function|em_meta_change
r_static
r_int
id|em_meta_change
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
r_struct
id|tcf_ematch
op_star
id|m
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|rtattr
op_star
id|tb
(braket
id|TCA_EM_META_MAX
)braket
suffix:semicolon
r_struct
id|tcf_meta_hdr
op_star
id|hdr
suffix:semicolon
r_struct
id|meta_match
op_star
id|meta
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|rtattr_parse
c_func
(paren
id|tb
comma
id|TCA_EM_META_MAX
comma
id|data
comma
id|len
)paren
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
r_if
c_cond
(paren
id|tb
(braket
id|TCA_EM_META_HDR
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
id|TCA_EM_META_HDR
op_minus
l_int|1
)braket
)paren
OL
r_sizeof
(paren
op_star
id|hdr
)paren
)paren
r_goto
id|errout
suffix:semicolon
id|hdr
op_assign
id|RTA_DATA
c_func
(paren
id|tb
(braket
id|TCA_EM_META_HDR
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TCF_META_TYPE
c_func
(paren
id|hdr-&gt;left.kind
)paren
op_ne
id|TCF_META_TYPE
c_func
(paren
id|hdr-&gt;right.kind
)paren
op_logical_or
id|TCF_META_TYPE
c_func
(paren
id|hdr-&gt;left.kind
)paren
OG
id|TCF_META_TYPE_MAX
op_logical_or
id|TCF_META_ID
c_func
(paren
id|hdr-&gt;left.kind
)paren
OG
id|TCF_META_ID_MAX
op_logical_or
id|TCF_META_ID
c_func
(paren
id|hdr-&gt;right.kind
)paren
OG
id|TCF_META_ID_MAX
)paren
r_goto
id|errout
suffix:semicolon
id|meta
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|meta
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|meta
op_eq
l_int|NULL
)paren
r_goto
id|errout
suffix:semicolon
id|memset
c_func
(paren
id|meta
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|meta
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|meta-&gt;lvalue.hdr
comma
op_amp
id|hdr-&gt;left
comma
r_sizeof
(paren
id|hdr-&gt;left
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|meta-&gt;rvalue.hdr
comma
op_amp
id|hdr-&gt;right
comma
r_sizeof
(paren
id|hdr-&gt;right
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|meta_is_supported
c_func
(paren
op_amp
id|meta-&gt;lvalue
)paren
op_logical_or
op_logical_neg
id|meta_is_supported
c_func
(paren
op_amp
id|meta-&gt;rvalue
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
r_if
c_cond
(paren
id|meta_change_data
c_func
(paren
op_amp
id|meta-&gt;lvalue
comma
id|tb
(braket
id|TCA_EM_META_LVALUE
op_minus
l_int|1
)braket
)paren
OL
l_int|0
op_logical_or
id|meta_change_data
c_func
(paren
op_amp
id|meta-&gt;rvalue
comma
id|tb
(braket
id|TCA_EM_META_RVALUE
op_minus
l_int|1
)braket
)paren
OL
l_int|0
)paren
r_goto
id|errout
suffix:semicolon
id|m-&gt;datalen
op_assign
r_sizeof
(paren
op_star
id|meta
)paren
suffix:semicolon
id|m-&gt;data
op_assign
(paren
r_int
r_int
)paren
id|meta
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|errout
suffix:colon
r_if
c_cond
(paren
id|err
op_logical_and
id|meta
)paren
id|meta_delete
c_func
(paren
id|meta
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|em_meta_destroy
r_static
r_void
id|em_meta_destroy
c_func
(paren
r_struct
id|tcf_proto
op_star
id|tp
comma
r_struct
id|tcf_ematch
op_star
id|m
)paren
(brace
r_if
c_cond
(paren
id|m
)paren
id|meta_delete
c_func
(paren
(paren
r_struct
id|meta_match
op_star
)paren
id|m-&gt;data
)paren
suffix:semicolon
)brace
DECL|function|em_meta_dump
r_static
r_int
id|em_meta_dump
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcf_ematch
op_star
id|em
)paren
(brace
r_struct
id|meta_match
op_star
id|meta
op_assign
(paren
r_struct
id|meta_match
op_star
)paren
id|em-&gt;data
suffix:semicolon
r_struct
id|tcf_meta_hdr
id|hdr
suffix:semicolon
r_struct
id|meta_type_ops
op_star
id|ops
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|hdr
comma
l_int|0
comma
r_sizeof
(paren
id|hdr
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|hdr.left
comma
op_amp
id|meta-&gt;lvalue.hdr
comma
r_sizeof
(paren
id|hdr.left
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|hdr.right
comma
op_amp
id|meta-&gt;rvalue.hdr
comma
r_sizeof
(paren
id|hdr.right
)paren
)paren
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_EM_META_HDR
comma
r_sizeof
(paren
id|hdr
)paren
comma
op_amp
id|hdr
)paren
suffix:semicolon
id|ops
op_assign
id|meta_type_ops
c_func
(paren
op_amp
id|meta-&gt;lvalue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ops
op_member_access_from_pointer
id|dump
c_func
(paren
id|skb
comma
op_amp
id|meta-&gt;lvalue
comma
id|TCA_EM_META_LVALUE
)paren
OL
l_int|0
op_logical_or
id|ops
op_member_access_from_pointer
id|dump
c_func
(paren
id|skb
comma
op_amp
id|meta-&gt;rvalue
comma
id|TCA_EM_META_RVALUE
)paren
OL
l_int|0
)paren
r_goto
id|rtattr_failure
suffix:semicolon
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
DECL|variable|em_meta_ops
r_static
r_struct
id|tcf_ematch_ops
id|em_meta_ops
op_assign
(brace
dot
id|kind
op_assign
id|TCF_EM_META
comma
dot
id|change
op_assign
id|em_meta_change
comma
dot
id|match
op_assign
id|em_meta_match
comma
dot
id|destroy
op_assign
id|em_meta_destroy
comma
dot
id|dump
op_assign
id|em_meta_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|link
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|em_meta_ops.link
)paren
)brace
suffix:semicolon
DECL|function|init_em_meta
r_static
r_int
id|__init
id|init_em_meta
c_func
(paren
r_void
)paren
(brace
r_return
id|tcf_em_register
c_func
(paren
op_amp
id|em_meta_ops
)paren
suffix:semicolon
)brace
DECL|function|exit_em_meta
r_static
r_void
id|__exit
id|exit_em_meta
c_func
(paren
r_void
)paren
(brace
id|tcf_em_unregister
c_func
(paren
op_amp
id|em_meta_ops
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|init_em_meta
id|module_init
c_func
(paren
id|init_em_meta
)paren
suffix:semicolon
DECL|variable|exit_em_meta
id|module_exit
c_func
(paren
id|exit_em_meta
)paren
suffix:semicolon
eof
