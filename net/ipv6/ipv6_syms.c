macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/addrconf.h&gt;
macro_line|#include &lt;net/ip6_route.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
DECL|variable|ipv6_addr_type
id|EXPORT_SYMBOL
c_func
(paren
id|ipv6_addr_type
)paren
suffix:semicolon
DECL|variable|icmpv6_send
id|EXPORT_SYMBOL
c_func
(paren
id|icmpv6_send
)paren
suffix:semicolon
DECL|variable|icmpv6_statistics
id|EXPORT_SYMBOL
c_func
(paren
id|icmpv6_statistics
)paren
suffix:semicolon
DECL|variable|icmpv6_err_convert
id|EXPORT_SYMBOL
c_func
(paren
id|icmpv6_err_convert
)paren
suffix:semicolon
DECL|variable|ndisc_mc_map
id|EXPORT_SYMBOL
c_func
(paren
id|ndisc_mc_map
)paren
suffix:semicolon
DECL|variable|register_inet6addr_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|register_inet6addr_notifier
)paren
suffix:semicolon
DECL|variable|unregister_inet6addr_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_inet6addr_notifier
)paren
suffix:semicolon
DECL|variable|ip6_route_output
id|EXPORT_SYMBOL
c_func
(paren
id|ip6_route_output
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER
DECL|variable|ip6_route_me_harder
id|EXPORT_SYMBOL
c_func
(paren
id|ip6_route_me_harder
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|addrconf_lock
id|EXPORT_SYMBOL
c_func
(paren
id|addrconf_lock
)paren
suffix:semicolon
DECL|variable|ipv6_setsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|ipv6_setsockopt
)paren
suffix:semicolon
DECL|variable|ipv6_getsockopt
id|EXPORT_SYMBOL
c_func
(paren
id|ipv6_getsockopt
)paren
suffix:semicolon
DECL|variable|inet6_register_protosw
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_register_protosw
)paren
suffix:semicolon
DECL|variable|inet6_unregister_protosw
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_unregister_protosw
)paren
suffix:semicolon
DECL|variable|inet6_add_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_add_protocol
)paren
suffix:semicolon
DECL|variable|inet6_del_protocol
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_del_protocol
)paren
suffix:semicolon
DECL|variable|ip6_xmit
id|EXPORT_SYMBOL
c_func
(paren
id|ip6_xmit
)paren
suffix:semicolon
DECL|variable|inet6_release
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_release
)paren
suffix:semicolon
DECL|variable|inet6_bind
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_bind
)paren
suffix:semicolon
DECL|variable|inet6_getname
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_getname
)paren
suffix:semicolon
DECL|variable|inet6_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|inet6_ioctl
)paren
suffix:semicolon
DECL|variable|ipv6_get_saddr
id|EXPORT_SYMBOL
c_func
(paren
id|ipv6_get_saddr
)paren
suffix:semicolon
DECL|variable|ipv6_chk_addr
id|EXPORT_SYMBOL
c_func
(paren
id|ipv6_chk_addr
)paren
suffix:semicolon
DECL|variable|in6_dev_finish_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|in6_dev_finish_destroy
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XFRM
DECL|variable|xfrm6_rcv
id|EXPORT_SYMBOL
c_func
(paren
id|xfrm6_rcv
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|rt6_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|rt6_lookup
)paren
suffix:semicolon
DECL|variable|fl6_sock_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|fl6_sock_lookup
)paren
suffix:semicolon
DECL|variable|ipv6_push_nfrag_opts
id|EXPORT_SYMBOL
c_func
(paren
id|ipv6_push_nfrag_opts
)paren
suffix:semicolon
eof
