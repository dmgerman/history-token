macro_line|#ifndef _INET_ECN_H_
DECL|macro|_INET_ECN_H_
mdefine_line|#define _INET_ECN_H_
macro_line|#include &lt;linux/ip.h&gt;
r_enum
(brace
DECL|enumerator|INET_ECN_NOT_ECT
id|INET_ECN_NOT_ECT
op_assign
l_int|0
comma
DECL|enumerator|INET_ECN_ECT_1
id|INET_ECN_ECT_1
op_assign
l_int|1
comma
DECL|enumerator|INET_ECN_ECT_0
id|INET_ECN_ECT_0
op_assign
l_int|2
comma
DECL|enumerator|INET_ECN_CE
id|INET_ECN_CE
op_assign
l_int|3
comma
DECL|enumerator|INET_ECN_MASK
id|INET_ECN_MASK
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|function|INET_ECN_is_ce
r_static
r_inline
r_int
id|INET_ECN_is_ce
c_func
(paren
id|__u8
id|dsfield
)paren
(brace
r_return
(paren
id|dsfield
op_amp
id|INET_ECN_MASK
)paren
op_eq
id|INET_ECN_CE
suffix:semicolon
)brace
DECL|function|INET_ECN_is_not_ect
r_static
r_inline
r_int
id|INET_ECN_is_not_ect
c_func
(paren
id|__u8
id|dsfield
)paren
(brace
r_return
(paren
id|dsfield
op_amp
id|INET_ECN_MASK
)paren
op_eq
id|INET_ECN_NOT_ECT
suffix:semicolon
)brace
DECL|function|INET_ECN_is_capable
r_static
r_inline
r_int
id|INET_ECN_is_capable
c_func
(paren
id|__u8
id|dsfield
)paren
(brace
r_return
(paren
id|dsfield
op_amp
id|INET_ECN_ECT_0
)paren
suffix:semicolon
)brace
DECL|function|INET_ECN_encapsulate
r_static
r_inline
id|__u8
id|INET_ECN_encapsulate
c_func
(paren
id|__u8
id|outer
comma
id|__u8
id|inner
)paren
(brace
id|outer
op_and_assign
op_complement
id|INET_ECN_MASK
suffix:semicolon
id|outer
op_or_assign
(paren
id|inner
op_amp
id|INET_ECN_MASK
)paren
ques
c_cond
suffix:colon
id|INET_ECN_ECT_0
suffix:semicolon
r_return
id|outer
suffix:semicolon
)brace
DECL|macro|INET_ECN_xmit
mdefine_line|#define&t;INET_ECN_xmit(sk) do { inet_sk(sk)-&gt;tos |= INET_ECN_ECT_0; } while (0)
DECL|macro|INET_ECN_dontxmit
mdefine_line|#define&t;INET_ECN_dontxmit(sk) &bslash;&n;&t;do { inet_sk(sk)-&gt;tos &amp;= ~INET_ECN_MASK; } while (0)
DECL|macro|IP6_ECN_flow_init
mdefine_line|#define IP6_ECN_flow_init(label) do {&t;&t;&bslash;&n;      (label) &amp;= ~htonl(INET_ECN_MASK &lt;&lt; 20);&t;&bslash;&n;    } while (0)
DECL|macro|IP6_ECN_flow_xmit
mdefine_line|#define&t;IP6_ECN_flow_xmit(sk, label) do {&t;&t;&t;&t;&bslash;&n;&t;if (INET_ECN_is_capable(inet_sk(sk)-&gt;tos))&t;&t;&t;&bslash;&n;&t;&t;(label) |= __constant_htons(INET_ECN_ECT_0 &lt;&lt; 4);&t;&bslash;&n;    } while (0)
DECL|function|IP_ECN_set_ce
r_static
r_inline
r_void
id|IP_ECN_set_ce
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
id|u32
id|check
op_assign
id|iph-&gt;check
suffix:semicolon
r_switch
c_cond
(paren
id|iph-&gt;tos
op_amp
id|INET_ECN_MASK
)paren
(brace
r_default
suffix:colon
r_case
id|INET_ECN_NOT_ECT
suffix:colon
r_case
id|INET_ECN_CE
suffix:colon
r_return
suffix:semicolon
r_case
id|INET_ECN_ECT_1
suffix:colon
id|check
op_add_assign
id|__constant_htons
c_func
(paren
l_int|0xFFFD
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INET_ECN_ECT_0
suffix:colon
id|check
op_add_assign
id|__constant_htons
c_func
(paren
l_int|0xFFFE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|iph-&gt;check
op_assign
id|check
op_plus
(paren
id|check
op_ge
l_int|0xFFFF
)paren
suffix:semicolon
id|iph-&gt;tos
op_or_assign
id|INET_ECN_CE
suffix:semicolon
)brace
DECL|function|IP_ECN_clear
r_static
r_inline
r_void
id|IP_ECN_clear
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
)paren
(brace
id|iph-&gt;tos
op_and_assign
op_complement
id|INET_ECN_MASK
suffix:semicolon
)brace
DECL|macro|ip6_get_dsfield
mdefine_line|#define ip6_get_dsfield(iph) ((ntohs(*(u16*)(iph)) &gt;&gt; 4) &amp; 0xFF)
r_struct
id|ipv6hdr
suffix:semicolon
DECL|function|IP6_ECN_set_ce
r_static
r_inline
r_void
id|IP6_ECN_set_ce
c_func
(paren
r_struct
id|ipv6hdr
op_star
id|iph
)paren
(brace
r_if
c_cond
(paren
id|INET_ECN_is_not_ect
c_func
(paren
id|ip6_get_dsfield
c_func
(paren
id|iph
)paren
)paren
)paren
r_return
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|iph
op_or_assign
id|htonl
c_func
(paren
id|INET_ECN_CE
op_lshift
l_int|20
)paren
suffix:semicolon
)brace
DECL|function|IP6_ECN_clear
r_static
r_inline
r_void
id|IP6_ECN_clear
c_func
(paren
r_struct
id|ipv6hdr
op_star
id|iph
)paren
(brace
op_star
(paren
id|u32
op_star
)paren
id|iph
op_and_assign
op_complement
id|htonl
c_func
(paren
id|INET_ECN_MASK
op_lshift
l_int|20
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
