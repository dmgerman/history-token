multiline_comment|/*&n; * sysctl_net_ipv4.c: sysctl interface to net IPV4 subsystem.&n; *&n; * $Id: sysctl_net_ipv4.c,v 1.50 2001/10/20 00:00:11 davem Exp $&n; *&n; * Begun April 1, 1996, Mike Shaver.&n; * Added /proc/sys/net/ipv4 directory entry (empty =) ). [MS]&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
multiline_comment|/* From af_inet.c */
r_extern
r_int
id|sysctl_ip_nonlocal_bind
suffix:semicolon
multiline_comment|/* From icmp.c */
r_extern
r_int
id|sysctl_icmp_echo_ignore_all
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_echo_ignore_broadcasts
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_ignore_bogus_error_responses
suffix:semicolon
multiline_comment|/* From ip_fragment.c */
r_extern
r_int
id|sysctl_ipfrag_low_thresh
suffix:semicolon
r_extern
r_int
id|sysctl_ipfrag_high_thresh
suffix:semicolon
r_extern
r_int
id|sysctl_ipfrag_time
suffix:semicolon
r_extern
r_int
id|sysctl_ipfrag_secret_interval
suffix:semicolon
multiline_comment|/* From ip_output.c */
r_extern
r_int
id|sysctl_ip_dynaddr
suffix:semicolon
multiline_comment|/* From icmp.c */
r_extern
r_int
id|sysctl_icmp_ratelimit
suffix:semicolon
r_extern
r_int
id|sysctl_icmp_ratemask
suffix:semicolon
multiline_comment|/* From igmp.c */
r_extern
r_int
id|sysctl_igmp_max_memberships
suffix:semicolon
r_extern
r_int
id|sysctl_igmp_max_msf
suffix:semicolon
multiline_comment|/* From inetpeer.c */
r_extern
r_int
id|inet_peer_threshold
suffix:semicolon
r_extern
r_int
id|inet_peer_minttl
suffix:semicolon
r_extern
r_int
id|inet_peer_maxttl
suffix:semicolon
r_extern
r_int
id|inet_peer_gc_mintime
suffix:semicolon
r_extern
r_int
id|inet_peer_gc_maxtime
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
DECL|variable|tcp_retr1_max
r_static
r_int
id|tcp_retr1_max
op_assign
l_int|255
suffix:semicolon
DECL|variable|ip_local_port_range_min
r_static
r_int
id|ip_local_port_range_min
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|ip_local_port_range_max
r_static
r_int
id|ip_local_port_range_max
(braket
)braket
op_assign
(brace
l_int|65535
comma
l_int|65535
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|ipv4_config
r_struct
id|ipv4_config
id|ipv4_config
suffix:semicolon
r_extern
id|ctl_table
id|ipv4_route_table
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
r_static
DECL|function|ipv4_sysctl_forward
r_int
id|ipv4_sysctl_forward
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
id|__user
op_star
id|buffer
comma
r_int
op_star
id|lenp
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|val
op_assign
id|ipv4_devconf.forwarding
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|proc_dointvec
c_func
(paren
id|ctl
comma
id|write
comma
id|filp
comma
id|buffer
comma
id|lenp
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
op_logical_and
id|ipv4_devconf.forwarding
op_ne
id|val
)paren
id|inet_forward_change
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ipv4_sysctl_forward_strategy
r_static
r_int
id|ipv4_sysctl_forward_strategy
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|__user
op_star
id|name
comma
r_int
id|nlen
comma
r_void
id|__user
op_star
id|oldval
comma
r_int
id|__user
op_star
id|oldlenp
comma
r_void
id|__user
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
(brace
r_int
op_star
id|valp
op_assign
id|table-&gt;data
suffix:semicolon
r_int
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newval
op_logical_or
op_logical_neg
id|newlen
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|newlen
op_ne
r_sizeof
(paren
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
r_new
comma
(paren
r_int
id|__user
op_star
)paren
id|newval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
op_star
id|valp
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|oldval
op_logical_and
id|oldlenp
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|len
comma
id|oldlenp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
OG
id|table-&gt;maxlen
)paren
id|len
op_assign
id|table-&gt;maxlen
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|oldval
comma
id|valp
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|len
comma
id|oldlenp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
op_star
id|valp
op_assign
r_new
suffix:semicolon
id|inet_forward_change
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ipv4_table
id|ctl_table
id|ipv4_table
(braket
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_TIMESTAMPS
comma
dot
id|procname
op_assign
l_string|&quot;tcp_timestamps&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_timestamps
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_WINDOW_SCALING
comma
dot
id|procname
op_assign
l_string|&quot;tcp_window_scaling&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_window_scaling
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_SACK
comma
dot
id|procname
op_assign
l_string|&quot;tcp_sack&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_sack
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_RETRANS_COLLAPSE
comma
dot
id|procname
op_assign
l_string|&quot;tcp_retrans_collapse&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_retrans_collapse
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_FORWARD
comma
dot
id|procname
op_assign
l_string|&quot;ip_forward&quot;
comma
dot
id|data
op_assign
op_amp
id|ipv4_devconf.forwarding
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|ipv4_sysctl_forward
comma
dot
id|strategy
op_assign
op_amp
id|ipv4_sysctl_forward_strategy
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_DEFAULT_TTL
comma
dot
id|procname
op_assign
l_string|&quot;ip_default_ttl&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ip_default_ttl
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|ipv4_doint_and_flush
comma
dot
id|strategy
op_assign
op_amp
id|ipv4_doint_and_flush_strategy
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_AUTOCONFIG
comma
dot
id|procname
op_assign
l_string|&quot;ip_autoconfig&quot;
comma
dot
id|data
op_assign
op_amp
id|ipv4_config.autoconfig
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NO_PMTU_DISC
comma
dot
id|procname
op_assign
l_string|&quot;ip_no_pmtu_disc&quot;
comma
dot
id|data
op_assign
op_amp
id|ipv4_config.no_pmtu_disc
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_NONLOCAL_BIND
comma
dot
id|procname
op_assign
l_string|&quot;ip_nonlocal_bind&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ip_nonlocal_bind
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_SYN_RETRIES
comma
dot
id|procname
op_assign
l_string|&quot;tcp_syn_retries&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_syn_retries
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_SYNACK_RETRIES
comma
dot
id|procname
op_assign
l_string|&quot;tcp_synack_retries&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_synack_retries
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_MAX_ORPHANS
comma
dot
id|procname
op_assign
l_string|&quot;tcp_max_orphans&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_max_orphans
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_MAX_TW_BUCKETS
comma
dot
id|procname
op_assign
l_string|&quot;tcp_max_tw_buckets&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_max_tw_buckets
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_IPFRAG_HIGH_THRESH
comma
dot
id|procname
op_assign
l_string|&quot;ipfrag_high_thresh&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ipfrag_high_thresh
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_IPFRAG_LOW_THRESH
comma
dot
id|procname
op_assign
l_string|&quot;ipfrag_low_thresh&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ipfrag_low_thresh
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_DYNADDR
comma
dot
id|procname
op_assign
l_string|&quot;ip_dynaddr&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ip_dynaddr
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_IPFRAG_TIME
comma
dot
id|procname
op_assign
l_string|&quot;ipfrag_time&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ipfrag_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_KEEPALIVE_TIME
comma
dot
id|procname
op_assign
l_string|&quot;tcp_keepalive_time&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_keepalive_time
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_KEEPALIVE_PROBES
comma
dot
id|procname
op_assign
l_string|&quot;tcp_keepalive_probes&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_keepalive_probes
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_KEEPALIVE_INTVL
comma
dot
id|procname
op_assign
l_string|&quot;tcp_keepalive_intvl&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_keepalive_intvl
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_RETRIES1
comma
dot
id|procname
op_assign
l_string|&quot;tcp_retries1&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_retries1
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra2
op_assign
op_amp
id|tcp_retr1_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_RETRIES2
comma
dot
id|procname
op_assign
l_string|&quot;tcp_retries2&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_retries2
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_TCP_FIN_TIMEOUT
comma
dot
id|procname
op_assign
l_string|&quot;tcp_fin_timeout&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_fin_timeout
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
macro_line|#ifdef CONFIG_SYN_COOKIES
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_SYNCOOKIES
comma
dot
id|procname
op_assign
l_string|&quot;tcp_syncookies&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_syncookies
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_TW_RECYCLE
comma
dot
id|procname
op_assign
l_string|&quot;tcp_tw_recycle&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_tw_recycle
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_ABORT_ON_OVERFLOW
comma
dot
id|procname
op_assign
l_string|&quot;tcp_abort_on_overflow&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_abort_on_overflow
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_STDURG
comma
dot
id|procname
op_assign
l_string|&quot;tcp_stdurg&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_stdurg
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_RFC1337
comma
dot
id|procname
op_assign
l_string|&quot;tcp_rfc1337&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_rfc1337
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_MAX_SYN_BACKLOG
comma
dot
id|procname
op_assign
l_string|&quot;tcp_max_syn_backlog&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_max_syn_backlog
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_LOCAL_PORT_RANGE
comma
dot
id|procname
op_assign
l_string|&quot;ip_local_port_range&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_local_port_range
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
id|sysctl_local_port_range
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_minmax
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_intvec
comma
dot
id|extra1
op_assign
id|ip_local_port_range_min
comma
dot
id|extra2
op_assign
id|ip_local_port_range_max
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_ICMP_ECHO_IGNORE_ALL
comma
dot
id|procname
op_assign
l_string|&quot;icmp_echo_ignore_all&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_icmp_echo_ignore_all
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_ICMP_ECHO_IGNORE_BROADCASTS
comma
dot
id|procname
op_assign
l_string|&quot;icmp_echo_ignore_broadcasts&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_icmp_echo_ignore_broadcasts
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_ICMP_IGNORE_BOGUS_ERROR_RESPONSES
comma
dot
id|procname
op_assign
l_string|&quot;icmp_ignore_bogus_error_responses&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_icmp_ignore_bogus_error_responses
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_ROUTE
comma
dot
id|procname
op_assign
l_string|&quot;route&quot;
comma
dot
id|maxlen
op_assign
l_int|0
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|ipv4_route_table
)brace
comma
macro_line|#ifdef CONFIG_IP_MULTICAST
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_IGMP_MAX_MEMBERSHIPS
comma
dot
id|procname
op_assign
l_string|&quot;igmp_max_memberships&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_igmp_max_memberships
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
macro_line|#endif
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_IGMP_MAX_MSF
comma
dot
id|procname
op_assign
l_string|&quot;igmp_max_msf&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_igmp_max_msf
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_INET_PEER_THRESHOLD
comma
dot
id|procname
op_assign
l_string|&quot;inet_peer_threshold&quot;
comma
dot
id|data
op_assign
op_amp
id|inet_peer_threshold
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_INET_PEER_MINTTL
comma
dot
id|procname
op_assign
l_string|&quot;inet_peer_minttl&quot;
comma
dot
id|data
op_assign
op_amp
id|inet_peer_minttl
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_INET_PEER_MAXTTL
comma
dot
id|procname
op_assign
l_string|&quot;inet_peer_maxttl&quot;
comma
dot
id|data
op_assign
op_amp
id|inet_peer_maxttl
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_INET_PEER_GC_MINTIME
comma
dot
id|procname
op_assign
l_string|&quot;inet_peer_gc_mintime&quot;
comma
dot
id|data
op_assign
op_amp
id|inet_peer_gc_mintime
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_INET_PEER_GC_MAXTIME
comma
dot
id|procname
op_assign
l_string|&quot;inet_peer_gc_maxtime&quot;
comma
dot
id|data
op_assign
op_amp
id|inet_peer_gc_maxtime
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_ORPHAN_RETRIES
comma
dot
id|procname
op_assign
l_string|&quot;tcp_orphan_retries&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_orphan_retries
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_FACK
comma
dot
id|procname
op_assign
l_string|&quot;tcp_fack&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_fack
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_REORDERING
comma
dot
id|procname
op_assign
l_string|&quot;tcp_reordering&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_reordering
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_ECN
comma
dot
id|procname
op_assign
l_string|&quot;tcp_ecn&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_ecn
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_DSACK
comma
dot
id|procname
op_assign
l_string|&quot;tcp_dsack&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_dsack
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_MEM
comma
dot
id|procname
op_assign
l_string|&quot;tcp_mem&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_mem
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
id|sysctl_tcp_mem
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_WMEM
comma
dot
id|procname
op_assign
l_string|&quot;tcp_wmem&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_wmem
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
id|sysctl_tcp_wmem
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_RMEM
comma
dot
id|procname
op_assign
l_string|&quot;tcp_rmem&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_rmem
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
id|sysctl_tcp_rmem
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_APP_WIN
comma
dot
id|procname
op_assign
l_string|&quot;tcp_app_win&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_app_win
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_ADV_WIN_SCALE
comma
dot
id|procname
op_assign
l_string|&quot;tcp_adv_win_scale&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_adv_win_scale
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_ICMP_RATELIMIT
comma
dot
id|procname
op_assign
l_string|&quot;icmp_ratelimit&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_icmp_ratelimit
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_ICMP_RATEMASK
comma
dot
id|procname
op_assign
l_string|&quot;icmp_ratemask&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_icmp_ratemask
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_TW_REUSE
comma
dot
id|procname
op_assign
l_string|&quot;tcp_tw_reuse&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_tw_reuse
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_FRTO
comma
dot
id|procname
op_assign
l_string|&quot;tcp_frto&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_frto
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_LOW_LATENCY
comma
dot
id|procname
op_assign
l_string|&quot;tcp_low_latency&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_low_latency
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_IPV4_IPFRAG_SECRET_INTERVAL
comma
dot
id|procname
op_assign
l_string|&quot;ipfrag_secret_interval&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_ipfrag_secret_interval
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec_jiffies
comma
dot
id|strategy
op_assign
op_amp
id|sysctl_jiffies
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_NO_METRICS_SAVE
comma
dot
id|procname
op_assign
l_string|&quot;tcp_no_metrics_save&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_nometrics_save
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_WESTWOOD
comma
dot
id|procname
op_assign
l_string|&quot;tcp_westwood&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_westwood
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_VEGAS
comma
dot
id|procname
op_assign
l_string|&quot;tcp_vegas_cong_avoid&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_vegas_cong_avoid
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_VEGAS_ALPHA
comma
dot
id|procname
op_assign
l_string|&quot;tcp_vegas_alpha&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_vegas_alpha
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_VEGAS_BETA
comma
dot
id|procname
op_assign
l_string|&quot;tcp_vegas_beta&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_vegas_beta
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_VEGAS_GAMMA
comma
dot
id|procname
op_assign
l_string|&quot;tcp_vegas_gamma&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_vegas_gamma
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_BIC
comma
dot
id|procname
op_assign
l_string|&quot;tcp_bic&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_bic
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_BIC_FAST_CONVERGENCE
comma
dot
id|procname
op_assign
l_string|&quot;tcp_bic_fast_convergence&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_bic_fast_convergence
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_BIC_LOW_WINDOW
comma
dot
id|procname
op_assign
l_string|&quot;tcp_bic_low_window&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_bic_low_window
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
id|NET_TCP_MODERATE_RCVBUF
comma
dot
id|procname
op_assign
l_string|&quot;tcp_moderate_rcvbuf&quot;
comma
dot
id|data
op_assign
op_amp
id|sysctl_tcp_moderate_rcvbuf
comma
dot
id|maxlen
op_assign
r_sizeof
(paren
r_int
)paren
comma
dot
id|mode
op_assign
l_int|0644
comma
dot
id|proc_handler
op_assign
op_amp
id|proc_dointvec
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_SYSCTL */
DECL|variable|ipv4_config
id|EXPORT_SYMBOL
c_func
(paren
id|ipv4_config
)paren
suffix:semicolon
eof
