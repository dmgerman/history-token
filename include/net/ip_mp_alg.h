multiline_comment|/* ip_mp_alg.h: IPV4 multipath algorithm support.&n; *&n; * Copyright (C) 2004, 2005 Einar Lueck &lt;elueck@de.ibm.com&gt;&n; * Copyright (C) 2005 David S. Miller &lt;davem@davemloft.net&gt;&n; */
macro_line|#ifndef _IP_MP_ALG_H
DECL|macro|_IP_MP_ALG_H
mdefine_line|#define _IP_MP_ALG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/flow.h&gt;
DECL|function|multipath_comparekeys
r_static
r_int
r_inline
id|multipath_comparekeys
c_func
(paren
r_const
r_struct
id|flowi
op_star
id|flp1
comma
r_const
r_struct
id|flowi
op_star
id|flp2
)paren
(brace
r_return
id|flp1-&gt;fl4_dst
op_eq
id|flp2-&gt;fl4_dst
op_logical_and
id|flp1-&gt;fl4_src
op_eq
id|flp2-&gt;fl4_src
op_logical_and
id|flp1-&gt;oif
op_eq
id|flp2-&gt;oif
op_logical_and
macro_line|#ifdef CONFIG_IP_ROUTE_FWMARK
id|flp1-&gt;fl4_fwmark
op_eq
id|flp2-&gt;fl4_fwmark
op_logical_and
macro_line|#endif
op_logical_neg
(paren
(paren
id|flp1-&gt;fl4_tos
op_xor
id|flp2-&gt;fl4_tos
)paren
op_amp
(paren
id|IPTOS_RT_MASK
op_or
id|RTO_ONLINK
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* _IP_MP_ALG_H */
eof
