macro_line|#ifndef _LINUX_INETDEVICE_H
DECL|macro|_LINUX_INETDEVICE_H
mdefine_line|#define _LINUX_INETDEVICE_H
macro_line|#ifdef __KERNEL__
DECL|struct|ipv4_devconf
r_struct
id|ipv4_devconf
(brace
DECL|member|accept_redirects
r_int
id|accept_redirects
suffix:semicolon
DECL|member|send_redirects
r_int
id|send_redirects
suffix:semicolon
DECL|member|secure_redirects
r_int
id|secure_redirects
suffix:semicolon
DECL|member|shared_media
r_int
id|shared_media
suffix:semicolon
DECL|member|accept_source_route
r_int
id|accept_source_route
suffix:semicolon
DECL|member|rp_filter
r_int
id|rp_filter
suffix:semicolon
DECL|member|proxy_arp
r_int
id|proxy_arp
suffix:semicolon
DECL|member|bootp_relay
r_int
id|bootp_relay
suffix:semicolon
DECL|member|log_martians
r_int
id|log_martians
suffix:semicolon
DECL|member|forwarding
r_int
id|forwarding
suffix:semicolon
DECL|member|mc_forwarding
r_int
id|mc_forwarding
suffix:semicolon
DECL|member|tag
r_int
id|tag
suffix:semicolon
DECL|member|arp_filter
r_int
id|arp_filter
suffix:semicolon
DECL|member|arp_announce
r_int
id|arp_announce
suffix:semicolon
DECL|member|arp_ignore
r_int
id|arp_ignore
suffix:semicolon
DECL|member|medium_id
r_int
id|medium_id
suffix:semicolon
DECL|member|no_xfrm
r_int
id|no_xfrm
suffix:semicolon
DECL|member|no_policy
r_int
id|no_policy
suffix:semicolon
DECL|member|force_igmp_version
r_int
id|force_igmp_version
suffix:semicolon
DECL|member|sysctl
r_void
op_star
id|sysctl
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|ipv4_devconf
id|ipv4_devconf
suffix:semicolon
DECL|struct|in_device
r_struct
id|in_device
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|dead
r_int
id|dead
suffix:semicolon
DECL|member|ifa_list
r_struct
id|in_ifaddr
op_star
id|ifa_list
suffix:semicolon
multiline_comment|/* IP ifaddr chain&t;&t;*/
DECL|member|mc_list
r_struct
id|ip_mc_list
op_star
id|mc_list
suffix:semicolon
multiline_comment|/* IP multicast filter chain    */
DECL|member|mc_lock
id|rwlock_t
id|mc_lock
suffix:semicolon
multiline_comment|/* for mc_tomb */
DECL|member|mc_tomb
r_struct
id|ip_mc_list
op_star
id|mc_tomb
suffix:semicolon
DECL|member|mr_v1_seen
r_int
r_int
id|mr_v1_seen
suffix:semicolon
DECL|member|mr_v2_seen
r_int
r_int
id|mr_v2_seen
suffix:semicolon
DECL|member|mr_maxdelay
r_int
r_int
id|mr_maxdelay
suffix:semicolon
DECL|member|mr_qrv
r_int
r_char
id|mr_qrv
suffix:semicolon
DECL|member|mr_gq_running
r_int
r_char
id|mr_gq_running
suffix:semicolon
DECL|member|mr_ifc_count
r_int
r_char
id|mr_ifc_count
suffix:semicolon
DECL|member|mr_gq_timer
r_struct
id|timer_list
id|mr_gq_timer
suffix:semicolon
multiline_comment|/* general query timer */
DECL|member|mr_ifc_timer
r_struct
id|timer_list
id|mr_ifc_timer
suffix:semicolon
multiline_comment|/* interface change timer */
DECL|member|arp_parms
r_struct
id|neigh_parms
op_star
id|arp_parms
suffix:semicolon
DECL|member|cnf
r_struct
id|ipv4_devconf
id|cnf
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IN_DEV_FORWARD
mdefine_line|#define IN_DEV_FORWARD(in_dev)&t;&t;((in_dev)-&gt;cnf.forwarding)
DECL|macro|IN_DEV_MFORWARD
mdefine_line|#define IN_DEV_MFORWARD(in_dev)&t;&t;(ipv4_devconf.mc_forwarding &amp;&amp; (in_dev)-&gt;cnf.mc_forwarding)
DECL|macro|IN_DEV_RPFILTER
mdefine_line|#define IN_DEV_RPFILTER(in_dev)&t;&t;(ipv4_devconf.rp_filter &amp;&amp; (in_dev)-&gt;cnf.rp_filter)
DECL|macro|IN_DEV_SOURCE_ROUTE
mdefine_line|#define IN_DEV_SOURCE_ROUTE(in_dev)&t;(ipv4_devconf.accept_source_route &amp;&amp; (in_dev)-&gt;cnf.accept_source_route)
DECL|macro|IN_DEV_BOOTP_RELAY
mdefine_line|#define IN_DEV_BOOTP_RELAY(in_dev)&t;(ipv4_devconf.bootp_relay &amp;&amp; (in_dev)-&gt;cnf.bootp_relay)
DECL|macro|IN_DEV_LOG_MARTIANS
mdefine_line|#define IN_DEV_LOG_MARTIANS(in_dev)&t;(ipv4_devconf.log_martians || (in_dev)-&gt;cnf.log_martians)
DECL|macro|IN_DEV_PROXY_ARP
mdefine_line|#define IN_DEV_PROXY_ARP(in_dev)&t;(ipv4_devconf.proxy_arp || (in_dev)-&gt;cnf.proxy_arp)
DECL|macro|IN_DEV_SHARED_MEDIA
mdefine_line|#define IN_DEV_SHARED_MEDIA(in_dev)&t;(ipv4_devconf.shared_media || (in_dev)-&gt;cnf.shared_media)
DECL|macro|IN_DEV_TX_REDIRECTS
mdefine_line|#define IN_DEV_TX_REDIRECTS(in_dev)&t;(ipv4_devconf.send_redirects || (in_dev)-&gt;cnf.send_redirects)
DECL|macro|IN_DEV_SEC_REDIRECTS
mdefine_line|#define IN_DEV_SEC_REDIRECTS(in_dev)&t;(ipv4_devconf.secure_redirects || (in_dev)-&gt;cnf.secure_redirects)
DECL|macro|IN_DEV_IDTAG
mdefine_line|#define IN_DEV_IDTAG(in_dev)&t;&t;((in_dev)-&gt;cnf.tag)
DECL|macro|IN_DEV_MEDIUM_ID
mdefine_line|#define IN_DEV_MEDIUM_ID(in_dev)&t;((in_dev)-&gt;cnf.medium_id)
DECL|macro|IN_DEV_RX_REDIRECTS
mdefine_line|#define IN_DEV_RX_REDIRECTS(in_dev) &bslash;&n;&t;((IN_DEV_FORWARD(in_dev) &amp;&amp; &bslash;&n;&t;  (ipv4_devconf.accept_redirects &amp;&amp; (in_dev)-&gt;cnf.accept_redirects)) &bslash;&n;&t; || (!IN_DEV_FORWARD(in_dev) &amp;&amp; &bslash;&n;&t;  (ipv4_devconf.accept_redirects || (in_dev)-&gt;cnf.accept_redirects)))
DECL|macro|IN_DEV_ARPFILTER
mdefine_line|#define IN_DEV_ARPFILTER(in_dev)&t;(ipv4_devconf.arp_filter || (in_dev)-&gt;cnf.arp_filter)
DECL|macro|IN_DEV_ARP_ANNOUNCE
mdefine_line|#define IN_DEV_ARP_ANNOUNCE(in_dev)&t;(max(ipv4_devconf.arp_announce, (in_dev)-&gt;cnf.arp_announce))
DECL|macro|IN_DEV_ARP_IGNORE
mdefine_line|#define IN_DEV_ARP_IGNORE(in_dev)&t;(max(ipv4_devconf.arp_ignore, (in_dev)-&gt;cnf.arp_ignore))
DECL|struct|in_ifaddr
r_struct
id|in_ifaddr
(brace
DECL|member|ifa_next
r_struct
id|in_ifaddr
op_star
id|ifa_next
suffix:semicolon
DECL|member|ifa_dev
r_struct
id|in_device
op_star
id|ifa_dev
suffix:semicolon
DECL|member|ifa_local
id|u32
id|ifa_local
suffix:semicolon
DECL|member|ifa_address
id|u32
id|ifa_address
suffix:semicolon
DECL|member|ifa_mask
id|u32
id|ifa_mask
suffix:semicolon
DECL|member|ifa_broadcast
id|u32
id|ifa_broadcast
suffix:semicolon
DECL|member|ifa_anycast
id|u32
id|ifa_anycast
suffix:semicolon
DECL|member|ifa_scope
r_int
r_char
id|ifa_scope
suffix:semicolon
DECL|member|ifa_flags
r_int
r_char
id|ifa_flags
suffix:semicolon
DECL|member|ifa_prefixlen
r_int
r_char
id|ifa_prefixlen
suffix:semicolon
DECL|member|ifa_label
r_char
id|ifa_label
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_inetaddr_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_int
id|unregister_inetaddr_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|ip_dev_find
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|inet_addr_onlink
c_func
(paren
r_struct
id|in_device
op_star
id|in_dev
comma
id|u32
id|a
comma
id|u32
id|b
)paren
suffix:semicolon
r_extern
r_int
id|devinet_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
id|__user
op_star
)paren
suffix:semicolon
r_extern
r_void
id|devinet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|in_device
op_star
id|inetdev_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_struct
id|in_device
op_star
id|inetdev_by_index
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
id|u32
id|inet_select_addr
c_func
(paren
r_const
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|dst
comma
r_int
id|scope
)paren
suffix:semicolon
r_extern
id|u32
id|inet_confirm_addr
c_func
(paren
r_const
r_struct
id|net_device
op_star
id|dev
comma
id|u32
id|dst
comma
id|u32
id|local
comma
r_int
id|scope
)paren
suffix:semicolon
r_extern
r_struct
id|in_ifaddr
op_star
id|inet_ifa_byprefix
c_func
(paren
r_struct
id|in_device
op_star
id|in_dev
comma
id|u32
id|prefix
comma
id|u32
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|inet_forward_change
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|inet_ifa_match
r_static
id|__inline__
r_int
id|inet_ifa_match
c_func
(paren
id|u32
id|addr
comma
r_struct
id|in_ifaddr
op_star
id|ifa
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|addr
op_xor
id|ifa-&gt;ifa_address
)paren
op_amp
id|ifa-&gt;ifa_mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Check if a mask is acceptable.&n; */
DECL|function|bad_mask
r_static
id|__inline__
r_int
id|bad_mask
c_func
(paren
id|u32
id|mask
comma
id|u32
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_amp
(paren
id|mask
op_assign
op_complement
id|mask
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|mask
op_assign
id|ntohl
c_func
(paren
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
(paren
id|mask
op_plus
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|for_primary_ifa
mdefine_line|#define for_primary_ifa(in_dev)&t;{ struct in_ifaddr *ifa; &bslash;&n;  for (ifa = (in_dev)-&gt;ifa_list; ifa &amp;&amp; !(ifa-&gt;ifa_flags&amp;IFA_F_SECONDARY); ifa = ifa-&gt;ifa_next)
DECL|macro|for_ifa
mdefine_line|#define for_ifa(in_dev)&t;{ struct in_ifaddr *ifa; &bslash;&n;  for (ifa = (in_dev)-&gt;ifa_list; ifa; ifa = ifa-&gt;ifa_next)
DECL|macro|endfor_ifa
mdefine_line|#define endfor_ifa(in_dev) }
r_extern
id|rwlock_t
id|inetdev_lock
suffix:semicolon
r_static
id|__inline__
r_struct
id|in_device
op_star
DECL|function|in_dev_get
id|in_dev_get
c_func
(paren
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
id|in_dev
op_assign
id|dev-&gt;ip_ptr
suffix:semicolon
r_if
c_cond
(paren
id|in_dev
)paren
id|atomic_inc
c_func
(paren
op_amp
id|in_dev-&gt;refcnt
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|inetdev_lock
)paren
suffix:semicolon
r_return
id|in_dev
suffix:semicolon
)brace
r_static
id|__inline__
r_struct
id|in_device
op_star
DECL|function|__in_dev_get
id|__in_dev_get
c_func
(paren
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|in_device
op_star
)paren
id|dev-&gt;ip_ptr
suffix:semicolon
)brace
r_extern
r_void
id|in_dev_finish_destroy
c_func
(paren
r_struct
id|in_device
op_star
id|idev
)paren
suffix:semicolon
r_static
id|__inline__
r_void
DECL|function|in_dev_put
id|in_dev_put
c_func
(paren
r_struct
id|in_device
op_star
id|idev
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|idev-&gt;refcnt
)paren
)paren
id|in_dev_finish_destroy
c_func
(paren
id|idev
)paren
suffix:semicolon
)brace
DECL|macro|__in_dev_put
mdefine_line|#define __in_dev_put(idev)  atomic_dec(&amp;(idev)-&gt;refcnt)
DECL|macro|in_dev_hold
mdefine_line|#define in_dev_hold(idev)   atomic_inc(&amp;(idev)-&gt;refcnt)
macro_line|#endif /* __KERNEL__ */
DECL|function|inet_make_mask
r_static
id|__inline__
id|__u32
id|inet_make_mask
c_func
(paren
r_int
id|logmask
)paren
(brace
r_if
c_cond
(paren
id|logmask
)paren
r_return
id|htonl
c_func
(paren
op_complement
(paren
(paren
l_int|1
op_lshift
(paren
l_int|32
op_minus
id|logmask
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inet_mask_len
r_static
id|__inline__
r_int
id|inet_mask_len
c_func
(paren
id|__u32
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_assign
id|ntohl
c_func
(paren
id|mask
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|32
op_minus
id|ffz
c_func
(paren
op_complement
id|mask
)paren
suffix:semicolon
)brace
macro_line|#endif /* _LINUX_INETDEVICE_H */
eof
