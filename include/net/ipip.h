macro_line|#ifndef __NET_IPIP_H
DECL|macro|__NET_IPIP_H
mdefine_line|#define __NET_IPIP_H 1
macro_line|#include &lt;linux/if_tunnel.h&gt;
multiline_comment|/* Keep error state on tunnel for 30 sec */
DECL|macro|IPTUNNEL_ERR_TIMEO
mdefine_line|#define IPTUNNEL_ERR_TIMEO&t;(30*HZ)
DECL|struct|ip_tunnel
r_struct
id|ip_tunnel
(brace
DECL|member|next
r_struct
id|ip_tunnel
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|stat
r_struct
id|net_device_stats
id|stat
suffix:semicolon
DECL|member|recursion
r_int
id|recursion
suffix:semicolon
multiline_comment|/* Depth of hard_start_xmit recursion */
DECL|member|err_count
r_int
id|err_count
suffix:semicolon
multiline_comment|/* Number of arrived ICMP errors */
DECL|member|err_time
r_int
r_int
id|err_time
suffix:semicolon
multiline_comment|/* Time when the last ICMP error arrived */
multiline_comment|/* These four fields used only by GRE */
DECL|member|i_seqno
id|__u32
id|i_seqno
suffix:semicolon
multiline_comment|/* The last seen seqno&t;*/
DECL|member|o_seqno
id|__u32
id|o_seqno
suffix:semicolon
multiline_comment|/* The last output seqno */
DECL|member|hlen
r_int
id|hlen
suffix:semicolon
multiline_comment|/* Precalculated GRE header length */
DECL|member|mlink
r_int
id|mlink
suffix:semicolon
DECL|member|parms
r_struct
id|ip_tunnel_parm
id|parms
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPTUNNEL_XMIT
mdefine_line|#define IPTUNNEL_XMIT() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int pkt_len = skb-&gt;len;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;skb-&gt;ip_summed = CHECKSUM_NONE;&t;&t;&t;&t;&t;&bslash;&n;&t;iph-&gt;tot_len = htons(skb-&gt;len);&t;&t;&t;&t;&t;&bslash;&n;&t;ip_select_ident(iph, &amp;rt-&gt;u.dst, NULL);&t;&t;&t;&t;&bslash;&n;&t;ip_send_check(iph);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err = NF_HOOK(PF_INET, NF_IP_LOCAL_OUT, skb, NULL, rt-&gt;u.dst.dev, do_ip_send); &bslash;&n;&t;if (err == NET_XMIT_SUCCESS || err == NET_XMIT_CN) {&t;&t;&bslash;&n;&t;&t;stats-&gt;tx_bytes += pkt_len;&t;&t;&t;&t;&bslash;&n;&t;&t;stats-&gt;tx_packets++;&t;&t;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;stats-&gt;tx_errors++;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;stats-&gt;tx_aborted_errors++;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
r_extern
r_int
id|ipip_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ipgre_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sit_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sit_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
