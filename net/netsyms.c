multiline_comment|/*&n; *  linux/net/netsyms.c&n; *&n; *  Symbol table for the linux networking subsystem. Moved here to&n; *  make life simpler in ksyms.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/fcdevice.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#ifdef CONFIG_HIPPI
macro_line|#include &lt;linux/hippidevice.h&gt;
macro_line|#endif
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/if_vlan.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#ifdef CONFIG_INET
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#if defined(CONFIG_INET_AH) || defined(CONFIG_INET_AH_MODULE) || defined(CONFIG_INET6_AH) || defined(CONFIG_INET6_AH_MODULE)
macro_line|#include &lt;net/ah.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_INET_ESP) || defined(CONFIG_INET_ESP_MODULE) || defined(CONFIG_INET6_ESP) || defined(CONFIG_INET6_ESP_MODULE)
macro_line|#include &lt;net/esp.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_IPX_MODULE
r_extern
r_struct
id|datalink_proto
op_star
id|make_EII_client
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|datalink_proto
op_star
id|make_8023_client
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|destroy_EII_client
c_func
(paren
r_struct
id|datalink_proto
op_star
)paren
suffix:semicolon
r_extern
r_void
id|destroy_8023_client
c_func
(paren
r_struct
id|datalink_proto
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATALK_MODULE
macro_line|#include &lt;net/sock.h&gt;
macro_line|#endif
multiline_comment|/* Needed by unix.o */
DECL|variable|files_stat
id|EXPORT_SYMBOL
c_func
(paren
id|files_stat
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IPX_MODULE
DECL|variable|make_8023_client
id|EXPORT_SYMBOL
c_func
(paren
id|make_8023_client
)paren
suffix:semicolon
DECL|variable|destroy_8023_client
id|EXPORT_SYMBOL
c_func
(paren
id|destroy_8023_client
)paren
suffix:semicolon
DECL|variable|make_EII_client
id|EXPORT_SYMBOL
c_func
(paren
id|make_EII_client
)paren
suffix:semicolon
DECL|variable|destroy_EII_client
id|EXPORT_SYMBOL
c_func
(paren
id|destroy_EII_client
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_INET
DECL|variable|ip_options_compile
id|EXPORT_SYMBOL
c_func
(paren
id|ip_options_compile
)paren
suffix:semicolon
DECL|variable|ip_options_undo
id|EXPORT_SYMBOL
c_func
(paren
id|ip_options_undo
)paren
suffix:semicolon
DECL|variable|in_aton
id|EXPORT_SYMBOL
c_func
(paren
id|in_aton
)paren
suffix:semicolon
DECL|variable|ip_defrag
id|EXPORT_SYMBOL
c_func
(paren
id|ip_defrag
)paren
suffix:semicolon
DECL|variable|inet_peer_idlock
id|EXPORT_SYMBOL
c_func
(paren
id|inet_peer_idlock
)paren
suffix:semicolon
multiline_comment|/* Route manipulation */
multiline_comment|/* needed for ip_gre -cw */
DECL|variable|ip_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|ip_statistics
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_INET_ESP) || defined(CONFIG_INET_ESP_MODULE) || defined(CONFIG_INET6_ESP) || defined(CONFIG_INET6_ESP_MODULE)
DECL|variable|skb_cow_data
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|skb_cow_data
)paren
suffix:semicolon
DECL|variable|pskb_put
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|pskb_put
)paren
suffix:semicolon
DECL|variable|skb_to_sgvec
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|skb_to_sgvec
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined (CONFIG_IPV6_MODULE) || defined (CONFIG_IP_SCTP_MODULE)
multiline_comment|/* inet functions common to v4 and v6 */
multiline_comment|/* UDP/TCP exported functions for TCPv6 */
DECL|variable|net_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|net_statistics
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Used by at least ipip.c.  */
DECL|variable|ipv4_config
id|EXPORT_SYMBOL
c_func
(paren
id|ipv4_config
)paren
suffix:semicolon
DECL|variable|ip_rcv
id|EXPORT_SYMBOL
c_func
(paren
id|ip_rcv
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_INET */
macro_line|#ifdef CONFIG_TR
DECL|variable|tr_source_route
id|EXPORT_SYMBOL
c_func
(paren
id|tr_source_route
)paren
suffix:semicolon
DECL|variable|tr_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|tr_type_trans
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* support for loadable net drivers */
macro_line|#ifdef CONFIG_NET
DECL|variable|loopback_dev
id|EXPORT_SYMBOL
c_func
(paren
id|loopback_dev
)paren
suffix:semicolon
DECL|variable|eth_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|eth_type_trans
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FDDI
DECL|variable|fddi_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|fddi_type_trans
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FDDI */
DECL|variable|dev_base
id|EXPORT_SYMBOL
c_func
(paren
id|dev_base
)paren
suffix:semicolon
DECL|variable|dev_base_lock
id|EXPORT_SYMBOL
c_func
(paren
id|dev_base_lock
)paren
suffix:semicolon
DECL|variable|__kill_fasync
id|EXPORT_SYMBOL
c_func
(paren
id|__kill_fasync
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIPPI
DECL|variable|hippi_type_trans
id|EXPORT_SYMBOL
c_func
(paren
id|hippi_type_trans
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET_SCHED
id|PSCHED_EXPORTLIST
suffix:semicolon
DECL|variable|pfifo_qdisc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|pfifo_qdisc_ops
)paren
suffix:semicolon
DECL|variable|bfifo_qdisc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|bfifo_qdisc_ops
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_ESTIMATOR
DECL|variable|qdisc_new_estimator
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_new_estimator
)paren
suffix:semicolon
DECL|variable|qdisc_kill_estimator
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_kill_estimator
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_NET_CLS
DECL|variable|register_tcf_proto_ops
id|EXPORT_SYMBOL
c_func
(paren
id|register_tcf_proto_ops
)paren
suffix:semicolon
DECL|variable|unregister_tcf_proto_ops
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_tcf_proto_ops
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|softnet_data
id|EXPORT_PER_CPU_SYMBOL
c_func
(paren
id|softnet_data
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_NET */
eof
