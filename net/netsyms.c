multiline_comment|/*&n; *  linux/net/netsyms.c&n; *&n; *  Symbol table for the linux networking subsystem. Moved here to&n; *  make life simpler in ksyms.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/fcdevice.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#ifdef CONFIG_HIPPI
macro_line|#include &lt;linux/hippidevice.h&gt;
macro_line|#endif
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;net/scm.h&gt;
macro_line|#include &lt;linux/if_bridge.h&gt;
macro_line|#include &lt;linux/if_vlan.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#ifdef CONFIG_NET_DIVERT
macro_line|#include &lt;linux/divert.h&gt;
macro_line|#endif /* CONFIG_NET_DIVERT */
macro_line|#ifdef CONFIG_INET
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/inet_common.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;linux/igmp.h&gt;
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
multiline_comment|/* Socket layer support routines */
DECL|variable|memcpy_fromiovec
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_fromiovec
)paren
suffix:semicolon
DECL|variable|memcpy_tokerneliovec
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_tokerneliovec
)paren
suffix:semicolon
DECL|variable|skb_recv_datagram
id|EXPORT_SYMBOL
c_func
(paren
id|skb_recv_datagram
)paren
suffix:semicolon
DECL|variable|skb_free_datagram
id|EXPORT_SYMBOL
c_func
(paren
id|skb_free_datagram
)paren
suffix:semicolon
DECL|variable|skb_copy_datagram
id|EXPORT_SYMBOL
c_func
(paren
id|skb_copy_datagram
)paren
suffix:semicolon
DECL|variable|skb_copy_datagram_iovec
id|EXPORT_SYMBOL
c_func
(paren
id|skb_copy_datagram_iovec
)paren
suffix:semicolon
DECL|variable|skb_copy_and_csum_datagram_iovec
id|EXPORT_SYMBOL
c_func
(paren
id|skb_copy_and_csum_datagram_iovec
)paren
suffix:semicolon
DECL|variable|datagram_poll
id|EXPORT_SYMBOL
c_func
(paren
id|datagram_poll
)paren
suffix:semicolon
DECL|variable|put_cmsg
id|EXPORT_SYMBOL
c_func
(paren
id|put_cmsg
)paren
suffix:semicolon
DECL|variable|sk_run_filter
id|EXPORT_SYMBOL
c_func
(paren
id|sk_run_filter
)paren
suffix:semicolon
DECL|variable|sk_chk_filter
id|EXPORT_SYMBOL
c_func
(paren
id|sk_chk_filter
)paren
suffix:semicolon
multiline_comment|/*&t;dst_entry&t;*/
DECL|variable|dst_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|dst_alloc
)paren
suffix:semicolon
DECL|variable|__dst_free
id|EXPORT_SYMBOL
c_func
(paren
id|__dst_free
)paren
suffix:semicolon
DECL|variable|dst_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|dst_destroy
)paren
suffix:semicolon
multiline_comment|/*&t;misc. support routines */
DECL|variable|net_ratelimit
id|EXPORT_SYMBOL
c_func
(paren
id|net_ratelimit
)paren
suffix:semicolon
DECL|variable|net_random
id|EXPORT_SYMBOL
c_func
(paren
id|net_random
)paren
suffix:semicolon
DECL|variable|net_srandom
id|EXPORT_SYMBOL
c_func
(paren
id|net_srandom
)paren
suffix:semicolon
multiline_comment|/* Needed by smbfs.o */
DECL|variable|__scm_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|__scm_destroy
)paren
suffix:semicolon
DECL|variable|__scm_send
id|EXPORT_SYMBOL
c_func
(paren
id|__scm_send
)paren
suffix:semicolon
multiline_comment|/* Needed by unix.o */
DECL|variable|scm_fp_dup
id|EXPORT_SYMBOL
c_func
(paren
id|scm_fp_dup
)paren
suffix:semicolon
DECL|variable|files_stat
id|EXPORT_SYMBOL
c_func
(paren
id|files_stat
)paren
suffix:semicolon
DECL|variable|memcpy_toiovec
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_toiovec
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
DECL|variable|scm_detach_fds
id|EXPORT_SYMBOL
c_func
(paren
id|scm_detach_fds
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_DIVERT
DECL|variable|alloc_divert_blk
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_divert_blk
)paren
suffix:semicolon
DECL|variable|free_divert_blk
id|EXPORT_SYMBOL
c_func
(paren
id|free_divert_blk
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_NET_DIVERT */
macro_line|#ifdef CONFIG_INET
multiline_comment|/* Internet layer registration */
DECL|variable|inet_add_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet_add_protocol
)paren
suffix:semicolon
DECL|variable|inet_del_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet_del_protocol
)paren
suffix:semicolon
DECL|variable|ip_route_output_key
id|EXPORT_SYMBOL
c_func
(paren
id|ip_route_output_key
)paren
suffix:semicolon
DECL|variable|ip_route_input
id|EXPORT_SYMBOL
c_func
(paren
id|ip_route_input
)paren
suffix:semicolon
DECL|variable|icmp_send
id|EXPORT_SYMBOL
c_func
(paren
id|icmp_send
)paren
suffix:semicolon
DECL|variable|icmp_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|icmp_statistics
)paren
suffix:semicolon
DECL|variable|icmp_err_convert
id|EXPORT_SYMBOL
c_func
(paren
id|icmp_err_convert
)paren
suffix:semicolon
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
DECL|variable|__ip_select_ident
id|EXPORT_SYMBOL
c_func
(paren
id|__ip_select_ident
)paren
suffix:semicolon
DECL|variable|in_aton
id|EXPORT_SYMBOL
c_func
(paren
id|in_aton
)paren
suffix:semicolon
DECL|variable|ip_mc_inc_group
id|EXPORT_SYMBOL
c_func
(paren
id|ip_mc_inc_group
)paren
suffix:semicolon
DECL|variable|ip_mc_dec_group
id|EXPORT_SYMBOL
c_func
(paren
id|ip_mc_dec_group
)paren
suffix:semicolon
DECL|variable|ip_mc_join_group
id|EXPORT_SYMBOL
c_func
(paren
id|ip_mc_join_group
)paren
suffix:semicolon
DECL|variable|inet_addr_type
id|EXPORT_SYMBOL
c_func
(paren
id|inet_addr_type
)paren
suffix:semicolon
DECL|variable|ip_dev_find
id|EXPORT_SYMBOL
c_func
(paren
id|ip_dev_find
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
DECL|variable|ip_rt_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|ip_rt_ioctl
)paren
suffix:semicolon
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
DECL|variable|flow_cache_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|flow_cache_lookup
)paren
suffix:semicolon
DECL|variable|flow_cache_genid
id|EXPORT_SYMBOL
c_func
(paren
id|flow_cache_genid
)paren
suffix:semicolon
macro_line|#if defined (CONFIG_IPV6_MODULE) || defined (CONFIG_IP_SCTP_MODULE)
multiline_comment|/* inet functions common to v4 and v6 */
multiline_comment|/* Socket demultiplexing. */
DECL|variable|memcpy_fromiovecend
id|EXPORT_SYMBOL
c_func
(paren
id|memcpy_fromiovecend
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_fromiovecend
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_fromiovecend
)paren
suffix:semicolon
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
multiline_comment|/* Used by other modules */
DECL|variable|xrlim_allow
id|EXPORT_SYMBOL
c_func
(paren
id|xrlim_allow
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
multiline_comment|/* Device callback registration */
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
macro_line|#if 0
id|EXPORT_SYMBOL
c_func
(paren
id|eth_copy_and_sum
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|dev_mc_add
id|EXPORT_SYMBOL
c_func
(paren
id|dev_mc_add
)paren
suffix:semicolon
DECL|variable|dev_mc_delete
id|EXPORT_SYMBOL
c_func
(paren
id|dev_mc_delete
)paren
suffix:semicolon
DECL|variable|dev_mc_upload
id|EXPORT_SYMBOL
c_func
(paren
id|dev_mc_upload
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
DECL|variable|register_qdisc
id|EXPORT_SYMBOL
c_func
(paren
id|register_qdisc
)paren
suffix:semicolon
DECL|variable|unregister_qdisc
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_qdisc
)paren
suffix:semicolon
DECL|variable|qdisc_get_rtab
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_get_rtab
)paren
suffix:semicolon
DECL|variable|qdisc_put_rtab
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_put_rtab
)paren
suffix:semicolon
DECL|variable|qdisc_copy_stats
id|EXPORT_SYMBOL
c_func
(paren
id|qdisc_copy_stats
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
DECL|variable|linkwatch_fire_event
id|EXPORT_SYMBOL
c_func
(paren
id|linkwatch_fire_event
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_NET */
eof
