multiline_comment|/*&n; * DECnet       An implementation of the DECnet protocol suite for the LINUX&n; *              operating system.  DECnet is implemented using the  BSD Socket&n; *              interface as the means of communication with the user level.&n; *&n; *              DECnet Neighbour Functions (Adjacency Database and &n; *                                                        On-Ethernet Cache)&n; *&n; * Author:      Steve Whitehouse &lt;SteveW@ACM.org&gt;&n; *&n; *&n; * Changes:&n; *     Steve Whitehouse     : Fixed router listing routine&n; *     Steve Whitehouse     : Added error_report functions&n; *     Steve Whitehouse     : Added default router detection&n; *     Steve Whitehouse     : Hop counts in outgoing messages&n; *     Steve Whitehouse     : Fixed src/dst in outgoing messages so&n; *                            forwarding now stands a good chance of&n; *                            working.&n; *     Steve Whitehouse     : Fixed neighbour states (for now anyway).&n; *     Steve Whitehouse     : Made error_report functions dummies. This&n; *                            is not the right place to return skbs.&n; *     Steve Whitehouse     : Convert to seq_file&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/netfilter_decnet.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;net/neighbour.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/flow.h&gt;
macro_line|#include &lt;net/dn.h&gt;
macro_line|#include &lt;net/dn_dev.h&gt;
macro_line|#include &lt;net/dn_neigh.h&gt;
macro_line|#include &lt;net/dn_route.h&gt;
r_static
id|u32
id|dn_neigh_hash
c_func
(paren
r_const
r_void
op_star
id|pkey
comma
r_const
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|dn_neigh_construct
c_func
(paren
r_struct
id|neighbour
op_star
)paren
suffix:semicolon
r_static
r_void
id|dn_long_error_report
c_func
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_void
id|dn_short_error_report
c_func
(paren
r_struct
id|neighbour
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|dn_long_output
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|dn_short_output
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_static
r_int
id|dn_phase3_output
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * For talking to broadcast devices: Ethernet &amp; PPP&n; */
DECL|variable|dn_long_ops
r_static
r_struct
id|neigh_ops
id|dn_long_ops
op_assign
(brace
dot
id|family
op_assign
id|AF_DECnet
comma
dot
id|error_report
op_assign
id|dn_long_error_report
comma
dot
id|output
op_assign
id|dn_long_output
comma
dot
id|connected_output
op_assign
id|dn_long_output
comma
dot
id|hh_output
op_assign
id|dev_queue_xmit
comma
dot
id|queue_xmit
op_assign
id|dev_queue_xmit
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * For talking to pointopoint and multidrop devices: DDCMP and X.25&n; */
DECL|variable|dn_short_ops
r_static
r_struct
id|neigh_ops
id|dn_short_ops
op_assign
(brace
dot
id|family
op_assign
id|AF_DECnet
comma
dot
id|error_report
op_assign
id|dn_short_error_report
comma
dot
id|output
op_assign
id|dn_short_output
comma
dot
id|connected_output
op_assign
id|dn_short_output
comma
dot
id|hh_output
op_assign
id|dev_queue_xmit
comma
dot
id|queue_xmit
op_assign
id|dev_queue_xmit
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * For talking to DECnet phase III nodes&n; */
DECL|variable|dn_phase3_ops
r_static
r_struct
id|neigh_ops
id|dn_phase3_ops
op_assign
(brace
dot
id|family
op_assign
id|AF_DECnet
comma
dot
id|error_report
op_assign
id|dn_short_error_report
comma
multiline_comment|/* Can use short version here */
dot
id|output
op_assign
id|dn_phase3_output
comma
dot
id|connected_output
op_assign
id|dn_phase3_output
comma
dot
id|hh_output
op_assign
id|dev_queue_xmit
comma
dot
id|queue_xmit
op_assign
id|dev_queue_xmit
)brace
suffix:semicolon
DECL|variable|dn_neigh_table
r_struct
id|neigh_table
id|dn_neigh_table
op_assign
(brace
dot
id|family
op_assign
id|PF_DECnet
comma
dot
id|entry_size
op_assign
r_sizeof
(paren
r_struct
id|dn_neigh
)paren
comma
dot
id|key_len
op_assign
r_sizeof
(paren
id|dn_address
)paren
comma
dot
id|hash
op_assign
id|dn_neigh_hash
comma
dot
id|constructor
op_assign
id|dn_neigh_construct
comma
dot
id|id
op_assign
l_string|&quot;dn_neigh_cache&quot;
comma
dot
id|parms
op_assign
(brace
dot
id|tbl
op_assign
op_amp
id|dn_neigh_table
comma
dot
id|entries
op_assign
l_int|0
comma
dot
id|base_reachable_time
op_assign
l_int|30
op_star
id|HZ
comma
dot
id|retrans_time
op_assign
l_int|1
op_star
id|HZ
comma
dot
id|gc_staletime
op_assign
l_int|60
op_star
id|HZ
comma
dot
id|reachable_time
op_assign
l_int|30
op_star
id|HZ
comma
dot
id|delay_probe_time
op_assign
l_int|5
op_star
id|HZ
comma
dot
id|queue_len
op_assign
l_int|3
comma
dot
id|ucast_probes
op_assign
l_int|0
comma
dot
id|app_probes
op_assign
l_int|0
comma
dot
id|mcast_probes
op_assign
l_int|0
comma
dot
id|anycast_delay
op_assign
l_int|0
comma
dot
id|proxy_delay
op_assign
l_int|0
comma
dot
id|proxy_qlen
op_assign
l_int|0
comma
dot
id|locktime
op_assign
l_int|1
op_star
id|HZ
comma
)brace
comma
dot
id|gc_interval
op_assign
l_int|30
op_star
id|HZ
comma
dot
id|gc_thresh1
op_assign
l_int|128
comma
dot
id|gc_thresh2
op_assign
l_int|512
comma
dot
id|gc_thresh3
op_assign
l_int|1024
comma
)brace
suffix:semicolon
DECL|function|dn_neigh_hash
r_static
id|u32
id|dn_neigh_hash
c_func
(paren
r_const
r_void
op_star
id|pkey
comma
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|u32
id|hash_val
suffix:semicolon
id|hash_val
op_assign
op_star
(paren
id|dn_address
op_star
)paren
id|pkey
suffix:semicolon
id|hash_val
op_xor_assign
(paren
id|hash_val
op_rshift
l_int|10
)paren
suffix:semicolon
id|hash_val
op_xor_assign
(paren
id|hash_val
op_rshift
l_int|3
)paren
suffix:semicolon
r_return
id|hash_val
op_amp
id|NEIGH_HASHMASK
suffix:semicolon
)brace
DECL|function|dn_neigh_construct
r_static
r_int
id|dn_neigh_construct
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_struct
id|dn_dev
op_star
id|dn_db
op_assign
(paren
r_struct
id|dn_dev
op_star
)paren
id|dev-&gt;dn_ptr
suffix:semicolon
r_if
c_cond
(paren
id|dn_db
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dn_db-&gt;neigh_parms
)paren
id|neigh-&gt;parms
op_assign
id|dn_db-&gt;neigh_parms
suffix:semicolon
r_if
c_cond
(paren
id|dn_db-&gt;use_long
)paren
id|neigh-&gt;ops
op_assign
op_amp
id|dn_long_ops
suffix:semicolon
r_else
id|neigh-&gt;ops
op_assign
op_amp
id|dn_short_ops
suffix:semicolon
r_if
c_cond
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_P3
)paren
id|neigh-&gt;ops
op_assign
op_amp
id|dn_phase3_ops
suffix:semicolon
id|neigh-&gt;nud_state
op_assign
id|NUD_NOARP
suffix:semicolon
id|neigh-&gt;output
op_assign
id|neigh-&gt;ops-&gt;connected_output
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_IPGRE
)paren
op_logical_or
(paren
id|dev-&gt;flags
op_amp
id|IFF_POINTOPOINT
)paren
)paren
id|memcpy
c_func
(paren
id|neigh-&gt;ha
comma
id|dev-&gt;broadcast
comma
id|dev-&gt;addr_len
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_ETHER
)paren
op_logical_or
(paren
id|dev-&gt;type
op_eq
id|ARPHRD_LOOPBACK
)paren
)paren
id|dn_dn2eth
c_func
(paren
id|neigh-&gt;ha
comma
id|dn-&gt;addr
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Trying to create neigh for hw %d&bslash;n&quot;
comma
id|dev-&gt;type
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make an estimate of the remote block size by assuming that its&n;&t; * two less then the device mtu, which it true for ethernet (and&n;&t; * other things which support long format headers) since there is&n;&t; * an extra length field (of 16 bits) which isn&squot;t part of the&n;&t; * ethernet headers and which the DECnet specs won&squot;t admit is part&n;&t; * of the DECnet routing headers either.&n;&t; *&n;&t; * If we over estimate here its no big deal, the NSP negotiations&n;&t; * will prevent us from sending packets which are too large for the&n;&t; * remote node to handle. In any case this figure is normally updated&n;&t; * by a hello message in most cases.&n;&t; */
id|dn-&gt;blksize
op_assign
id|dev-&gt;mtu
op_minus
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_long_error_report
r_static
r_void
id|dn_long_error_report
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dn_long_error_report: called&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_short_error_report
r_static
r_void
id|dn_short_error_report
c_func
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dn_short_error_report: called&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dn_neigh_output_packet
r_static
r_int
id|dn_neigh_output_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|dn_route
op_star
id|rt
op_assign
(paren
r_struct
id|dn_route
op_star
)paren
id|dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|mac_addr
comma
id|rt-&gt;rt_local_src
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;hard_header
op_logical_or
id|dev
op_member_access_from_pointer
id|hard_header
c_func
(paren
id|skb
comma
id|dev
comma
id|ntohs
c_func
(paren
id|skb-&gt;protocol
)paren
comma
id|neigh-&gt;ha
comma
id|mac_addr
comma
id|skb-&gt;len
)paren
op_ge
l_int|0
)paren
r_return
id|neigh-&gt;ops
op_member_access_from_pointer
id|queue_xmit
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;dn_neigh_output_packet: oops, can&squot;t send packet&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dn_long_output
r_static
r_int
id|dn_long_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_int
id|headroom
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|dn_long_packet
)paren
op_plus
l_int|3
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|dn_long_packet
op_star
id|lp
suffix:semicolon
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
id|DN_SKB_CB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;dn_long_output: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skb2
suffix:semicolon
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;dn_long_output: Increasing headroom&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|dn_long_packet
)paren
op_plus
l_int|3
)paren
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|dn_long_packet
op_star
)paren
(paren
id|data
op_plus
l_int|3
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
op_star
(paren
id|data
op_plus
l_int|2
)paren
op_assign
l_int|1
op_or
id|DN_RT_F_PF
suffix:semicolon
multiline_comment|/* Padding */
id|lp-&gt;msgflg
op_assign
id|DN_RT_PKT_LONG
op_or
(paren
id|cb-&gt;rt_flags
op_amp
(paren
id|DN_RT_F_IE
op_or
id|DN_RT_F_RQR
op_or
id|DN_RT_F_RTS
)paren
)paren
suffix:semicolon
id|lp-&gt;d_area
op_assign
id|lp-&gt;d_subarea
op_assign
l_int|0
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|lp-&gt;d_id
comma
id|dn_ntohs
c_func
(paren
id|cb-&gt;dst
)paren
)paren
suffix:semicolon
id|lp-&gt;s_area
op_assign
id|lp-&gt;s_subarea
op_assign
l_int|0
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|lp-&gt;s_id
comma
id|dn_ntohs
c_func
(paren
id|cb-&gt;src
)paren
)paren
suffix:semicolon
id|lp-&gt;nl2
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;visit_ct
op_assign
id|cb-&gt;hops
op_amp
l_int|0x3f
suffix:semicolon
id|lp-&gt;s_class
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;pt
op_assign
l_int|0
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|NF_HOOK
c_func
(paren
id|PF_DECnet
comma
id|NF_DN_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|neigh-&gt;dev
comma
id|dn_neigh_output_packet
)paren
suffix:semicolon
)brace
DECL|function|dn_short_output
r_static
r_int
id|dn_short_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_int
id|headroom
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
suffix:semicolon
r_struct
id|dn_short_packet
op_star
id|sp
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
id|DN_SKB_CB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;dn_short_output: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skb2
suffix:semicolon
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;dn_short_output: Increasing headroom&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|sp
op_assign
(paren
r_struct
id|dn_short_packet
op_star
)paren
(paren
id|data
op_plus
l_int|2
)paren
suffix:semicolon
id|sp-&gt;msgflg
op_assign
id|DN_RT_PKT_SHORT
op_or
(paren
id|cb-&gt;rt_flags
op_amp
(paren
id|DN_RT_F_RQR
op_or
id|DN_RT_F_RTS
)paren
)paren
suffix:semicolon
id|sp-&gt;dstnode
op_assign
id|cb-&gt;dst
suffix:semicolon
id|sp-&gt;srcnode
op_assign
id|cb-&gt;src
suffix:semicolon
id|sp-&gt;forward
op_assign
id|cb-&gt;hops
op_amp
l_int|0x3f
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|NF_HOOK
c_func
(paren
id|PF_DECnet
comma
id|NF_DN_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|neigh-&gt;dev
comma
id|dn_neigh_output_packet
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Phase 3 output is the same is short output, execpt that&n; * it clears the area bits before transmission.&n; */
DECL|function|dn_phase3_output
r_static
r_int
id|dn_phase3_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
op_assign
id|dst-&gt;neighbour
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|neigh-&gt;dev
suffix:semicolon
r_int
id|headroom
op_assign
id|dev-&gt;hard_header_len
op_plus
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
suffix:semicolon
r_struct
id|dn_short_packet
op_star
id|sp
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
r_struct
id|dn_skb_cb
op_star
id|cb
op_assign
id|DN_SKB_CB
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
id|skb
)paren
OL
id|headroom
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_realloc_headroom
c_func
(paren
id|skb
comma
id|headroom
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;dn_phase3_output: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|skb2
suffix:semicolon
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;dn_phase3_output: Increasing headroom&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|data
op_assign
id|skb_push
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|dn_short_packet
)paren
op_plus
l_int|2
)paren
suffix:semicolon
(paren
(paren
r_int
r_int
op_star
)paren
id|data
)paren
op_assign
id|dn_htons
c_func
(paren
id|skb-&gt;len
op_minus
l_int|2
)paren
suffix:semicolon
id|sp
op_assign
(paren
r_struct
id|dn_short_packet
op_star
)paren
(paren
id|data
op_plus
l_int|2
)paren
suffix:semicolon
id|sp-&gt;msgflg
op_assign
id|DN_RT_PKT_SHORT
op_or
(paren
id|cb-&gt;rt_flags
op_amp
(paren
id|DN_RT_F_RQR
op_or
id|DN_RT_F_RTS
)paren
)paren
suffix:semicolon
id|sp-&gt;dstnode
op_assign
id|cb-&gt;dst
op_amp
id|dn_htons
c_func
(paren
l_int|0x03ff
)paren
suffix:semicolon
id|sp-&gt;srcnode
op_assign
id|cb-&gt;src
op_amp
id|dn_htons
c_func
(paren
l_int|0x03ff
)paren
suffix:semicolon
id|sp-&gt;forward
op_assign
id|cb-&gt;hops
op_amp
l_int|0x3f
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
id|NF_HOOK
c_func
(paren
id|PF_DECnet
comma
id|NF_DN_POST_ROUTING
comma
id|skb
comma
l_int|NULL
comma
id|neigh-&gt;dev
comma
id|dn_neigh_output_packet
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Unfortunately, the neighbour code uses the device in its hash&n; * function, so we don&squot;t get any advantage from it. This function&n; * basically does a neigh_lookup(), but without comparing the device&n; * field. This is required for the On-Ethernet cache&n; */
DECL|function|dn_neigh_lookup
r_struct
id|neighbour
op_star
id|dn_neigh_lookup
c_func
(paren
r_struct
id|neigh_table
op_star
id|tbl
comma
r_const
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
id|u32
id|hash_val
suffix:semicolon
id|hash_val
op_assign
id|tbl
op_member_access_from_pointer
id|hash
c_func
(paren
id|ptr
comma
l_int|NULL
)paren
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|neigh
op_assign
id|tbl-&gt;hash_buckets
(braket
id|hash_val
)braket
suffix:semicolon
id|neigh
op_ne
l_int|NULL
suffix:semicolon
id|neigh
op_assign
id|neigh-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|neigh-&gt;primary_key
comma
id|ptr
comma
id|tbl-&gt;key_len
)paren
op_eq
l_int|0
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|neigh-&gt;refcnt
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
id|neigh
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Any traffic on a pointopoint link causes the timer to be reset&n; * for the entry in the neighbour table.&n; */
DECL|function|dn_neigh_pointopoint_notify
r_void
id|dn_neigh_pointopoint_notify
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Pointopoint link receives a hello message&n; */
DECL|function|dn_neigh_pointopoint_hello
r_void
id|dn_neigh_pointopoint_hello
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ethernet router hello message received&n; */
DECL|function|dn_neigh_router_hello
r_int
id|dn_neigh_router_hello
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|rtnode_hello_message
op_star
id|msg
op_assign
(paren
r_struct
id|rtnode_hello_message
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
suffix:semicolon
r_struct
id|dn_dev
op_star
id|dn_db
suffix:semicolon
id|dn_address
id|src
suffix:semicolon
id|src
op_assign
id|dn_htons
c_func
(paren
id|dn_eth2dn
c_func
(paren
id|msg-&gt;id
)paren
)paren
suffix:semicolon
id|neigh
op_assign
id|__neigh_lookup
c_func
(paren
op_amp
id|dn_neigh_table
comma
op_amp
id|src
comma
id|skb-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_if
c_cond
(paren
id|neigh
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh-&gt;used
op_assign
id|jiffies
suffix:semicolon
id|dn_db
op_assign
(paren
r_struct
id|dn_dev
op_star
)paren
id|neigh-&gt;dev-&gt;dn_ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|neigh-&gt;nud_state
op_amp
id|NUD_PERMANENT
)paren
)paren
(brace
id|neigh-&gt;updated
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|neigh-&gt;dev-&gt;type
op_eq
id|ARPHRD_ETHER
)paren
id|memcpy
c_func
(paren
id|neigh-&gt;ha
comma
op_amp
id|skb-&gt;mac.ethernet-&gt;h_source
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|dn-&gt;blksize
op_assign
id|dn_ntohs
c_func
(paren
id|msg-&gt;blksize
)paren
suffix:semicolon
id|dn-&gt;priority
op_assign
id|msg-&gt;priority
suffix:semicolon
id|dn-&gt;flags
op_and_assign
op_complement
id|DN_NDFLAG_P3
suffix:semicolon
r_switch
c_cond
(paren
id|msg-&gt;iinfo
op_amp
id|DN_RT_INFO_TYPE
)paren
(brace
r_case
id|DN_RT_INFO_L1RT
suffix:colon
id|dn-&gt;flags
op_and_assign
op_complement
id|DN_NDFLAG_R2
suffix:semicolon
id|dn-&gt;flags
op_or_assign
id|DN_NDFLAG_R1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DN_RT_INFO_L2RT
suffix:colon
id|dn-&gt;flags
op_or_assign
id|DN_NDFLAG_R2
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|dn_db-&gt;router
)paren
(brace
id|dn_db-&gt;router
op_assign
id|neigh_clone
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|msg-&gt;priority
OG
(paren
(paren
r_struct
id|dn_neigh
op_star
)paren
id|dn_db-&gt;router
)paren
op_member_access_from_pointer
id|priority
)paren
id|neigh_release
c_func
(paren
id|xchg
c_func
(paren
op_amp
id|dn_db-&gt;router
comma
id|neigh_clone
c_func
(paren
id|neigh
)paren
)paren
)paren
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh_release
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Endnode hello message received&n; */
DECL|function|dn_neigh_endnode_hello
r_int
id|dn_neigh_endnode_hello
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|endnode_hello_message
op_star
id|msg
op_assign
(paren
r_struct
id|endnode_hello_message
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
suffix:semicolon
id|dn_address
id|src
suffix:semicolon
id|src
op_assign
id|dn_htons
c_func
(paren
id|dn_eth2dn
c_func
(paren
id|msg-&gt;id
)paren
)paren
suffix:semicolon
id|neigh
op_assign
id|__neigh_lookup
c_func
(paren
op_amp
id|dn_neigh_table
comma
op_amp
id|src
comma
id|skb-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_if
c_cond
(paren
id|neigh
)paren
(brace
id|write_lock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh-&gt;used
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|neigh-&gt;nud_state
op_amp
id|NUD_PERMANENT
)paren
)paren
(brace
id|neigh-&gt;updated
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|neigh-&gt;dev-&gt;type
op_eq
id|ARPHRD_ETHER
)paren
id|memcpy
c_func
(paren
id|neigh-&gt;ha
comma
op_amp
id|skb-&gt;mac.ethernet-&gt;h_source
comma
id|ETH_ALEN
)paren
suffix:semicolon
id|dn-&gt;flags
op_and_assign
op_complement
(paren
id|DN_NDFLAG_R1
op_or
id|DN_NDFLAG_R2
)paren
suffix:semicolon
id|dn-&gt;blksize
op_assign
id|dn_ntohs
c_func
(paren
id|msg-&gt;blksize
)paren
suffix:semicolon
id|dn-&gt;priority
op_assign
l_int|0
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|neigh-&gt;lock
)paren
suffix:semicolon
id|neigh_release
c_func
(paren
id|neigh
)paren
suffix:semicolon
)brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_find_slot
r_static
r_char
op_star
id|dn_find_slot
c_func
(paren
r_char
op_star
id|base
comma
r_int
id|max
comma
r_int
id|priority
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
op_star
id|min
op_assign
l_int|NULL
suffix:semicolon
id|base
op_add_assign
l_int|6
suffix:semicolon
multiline_comment|/* skip first id */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|min
op_logical_or
(paren
op_star
id|base
OL
op_star
id|min
)paren
)paren
id|min
op_assign
id|base
suffix:semicolon
id|base
op_add_assign
l_int|7
suffix:semicolon
multiline_comment|/* find next priority */
)brace
r_if
c_cond
(paren
op_logical_neg
id|min
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
(paren
op_star
id|min
OL
id|priority
)paren
ques
c_cond
(paren
id|min
op_minus
l_int|6
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|dn_neigh_elist
r_int
id|dn_neigh_elist
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_char
op_star
id|ptr
comma
r_int
id|n
)paren
(brace
r_int
id|t
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|neighbour
op_star
id|neigh
suffix:semicolon
r_struct
id|dn_neigh
op_star
id|dn
suffix:semicolon
r_struct
id|neigh_table
op_star
id|tbl
op_assign
op_amp
id|dn_neigh_table
suffix:semicolon
r_int
r_char
op_star
id|rs
op_assign
id|ptr
suffix:semicolon
r_struct
id|dn_dev
op_star
id|dn_db
op_assign
(paren
r_struct
id|dn_dev
op_star
)paren
id|dev-&gt;dn_ptr
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NEIGH_HASHMASK
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|neigh
op_assign
id|tbl-&gt;hash_buckets
(braket
id|i
)braket
suffix:semicolon
id|neigh
op_ne
l_int|NULL
suffix:semicolon
id|neigh
op_assign
id|neigh-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|neigh-&gt;dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|neigh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dn-&gt;flags
op_amp
(paren
id|DN_NDFLAG_R1
op_or
id|DN_NDFLAG_R2
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dn_db-&gt;parms.forwarding
op_eq
l_int|1
op_logical_and
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_R2
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
id|n
)paren
id|rs
op_assign
id|dn_find_slot
c_func
(paren
id|ptr
comma
id|n
comma
id|dn-&gt;priority
)paren
suffix:semicolon
r_else
id|t
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rs
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|dn_dn2eth
c_func
(paren
id|rs
comma
id|dn-&gt;addr
)paren
suffix:semicolon
id|rs
op_add_assign
l_int|6
suffix:semicolon
op_star
id|rs
op_assign
id|neigh-&gt;nud_state
op_amp
id|NUD_CONNECTED
ques
c_cond
l_int|0x80
suffix:colon
l_int|0x0
suffix:semicolon
op_star
id|rs
op_or_assign
id|dn-&gt;priority
suffix:semicolon
id|rs
op_increment
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|tbl-&gt;lock
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|struct|dn_neigh_iter_state
r_struct
id|dn_neigh_iter_state
(brace
DECL|member|bucket
r_int
id|bucket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|neigh_get_first
r_static
r_struct
id|neighbour
op_star
id|neigh_get_first
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
)paren
(brace
r_struct
id|dn_neigh_iter_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|neighbour
op_star
id|n
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|state-&gt;bucket
op_assign
l_int|0
suffix:semicolon
id|state-&gt;bucket
op_le
id|NEIGH_HASHMASK
suffix:semicolon
op_increment
id|state-&gt;bucket
)paren
(brace
id|n
op_assign
id|dn_neigh_table.hash_buckets
(braket
id|state-&gt;bucket
)braket
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
r_break
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|neigh_get_next
r_static
r_struct
id|neighbour
op_star
id|neigh_get_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|neighbour
op_star
id|n
)paren
(brace
r_struct
id|dn_neigh_iter_state
op_star
id|state
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
id|n
op_assign
id|n-&gt;next
suffix:semicolon
id|try_again
suffix:colon
r_if
c_cond
(paren
id|n
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|state-&gt;bucket
OG
id|NEIGH_HASHMASK
)paren
r_goto
id|out
suffix:semicolon
id|n
op_assign
id|dn_neigh_table.hash_buckets
(braket
id|state-&gt;bucket
)braket
suffix:semicolon
r_goto
id|try_again
suffix:semicolon
id|out
suffix:colon
r_return
id|n
suffix:semicolon
)brace
DECL|function|neigh_get_idx
r_static
r_struct
id|neighbour
op_star
id|neigh_get_idx
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|neighbour
op_star
id|n
op_assign
id|neigh_get_first
c_func
(paren
id|seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
)paren
r_while
c_loop
(paren
op_star
id|pos
op_logical_and
(paren
id|n
op_assign
id|neigh_get_next
c_func
(paren
id|seq
comma
id|n
)paren
)paren
)paren
(brace
op_decrement
op_star
id|pos
suffix:semicolon
)brace
r_return
op_star
id|pos
ques
c_cond
l_int|NULL
suffix:colon
id|n
suffix:semicolon
)brace
DECL|function|dn_neigh_get_idx
r_static
r_void
op_star
id|dn_neigh_get_idx
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
id|pos
)paren
(brace
r_void
op_star
id|rc
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
id|rc
op_assign
id|neigh_get_idx
c_func
(paren
id|seq
comma
op_amp
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|read_unlock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|function|dn_neigh_seq_start
r_static
r_void
op_star
id|dn_neigh_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_return
op_star
id|pos
ques
c_cond
id|dn_neigh_get_idx
c_func
(paren
id|seq
comma
op_star
id|pos
op_minus
l_int|1
)paren
suffix:colon
(paren
r_void
op_star
)paren
l_int|1
suffix:semicolon
)brace
DECL|function|dn_neigh_seq_next
r_static
r_void
op_star
id|dn_neigh_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_void
op_star
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
id|rc
op_assign
id|dn_neigh_get_idx
c_func
(paren
id|seq
comma
l_int|0
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|rc
op_assign
id|neigh_get_next
c_func
(paren
id|seq
comma
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
id|out
suffix:colon
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|dn_neigh_seq_stop
r_static
r_void
id|dn_neigh_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
op_logical_and
id|v
op_ne
(paren
r_void
op_star
)paren
l_int|1
)paren
id|read_unlock_bh
c_func
(paren
op_amp
id|dn_neigh_table.lock
)paren
suffix:semicolon
)brace
DECL|function|dn_neigh_format_entry
r_static
r_inline
r_void
id|dn_neigh_format_entry
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_struct
id|neighbour
op_star
id|n
)paren
(brace
r_struct
id|dn_neigh
op_star
id|dn
op_assign
(paren
r_struct
id|dn_neigh
op_star
)paren
id|n
suffix:semicolon
r_char
id|buf
(braket
id|DN_ASCBUF_LEN
)braket
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|n-&gt;lock
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-7s %s%s%s   %02x    %02d  %07ld %-8s&bslash;n&quot;
comma
id|dn_addr2asc
c_func
(paren
id|dn_ntohs
c_func
(paren
id|dn-&gt;addr
)paren
comma
id|buf
)paren
comma
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_R1
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;-&quot;
comma
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_R2
)paren
ques
c_cond
l_string|&quot;2&quot;
suffix:colon
l_string|&quot;-&quot;
comma
(paren
id|dn-&gt;flags
op_amp
id|DN_NDFLAG_P3
)paren
ques
c_cond
l_string|&quot;3&quot;
suffix:colon
l_string|&quot;-&quot;
comma
id|dn-&gt;n.nud_state
comma
id|atomic_read
c_func
(paren
op_amp
id|dn-&gt;n.refcnt
)paren
comma
id|dn-&gt;blksize
comma
(paren
id|dn-&gt;n.dev
)paren
ques
c_cond
id|dn-&gt;n.dev-&gt;name
suffix:colon
l_string|&quot;?&quot;
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|n-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|dn_neigh_seq_show
r_static
r_int
id|dn_neigh_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|v
op_eq
(paren
r_void
op_star
)paren
l_int|1
)paren
(brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Addr    Flags State Use Blksize Dev&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dn_neigh_format_entry
c_func
(paren
id|seq
comma
id|v
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dn_neigh_seq_ops
r_static
r_struct
id|seq_operations
id|dn_neigh_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|dn_neigh_seq_start
comma
dot
id|next
op_assign
id|dn_neigh_seq_next
comma
dot
id|stop
op_assign
id|dn_neigh_seq_stop
comma
dot
id|show
op_assign
id|dn_neigh_seq_show
comma
)brace
suffix:semicolon
DECL|function|dn_neigh_seq_open
r_static
r_int
id|dn_neigh_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|seq_file
op_star
id|seq
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_struct
id|dn_neigh_iter_state
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_goto
id|out
suffix:semicolon
id|rc
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|dn_neigh_seq_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_goto
id|out_kfree
suffix:semicolon
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
id|s
suffix:semicolon
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|s
)paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_kfree
suffix:colon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|variable|dn_neigh_seq_fops
r_static
r_struct
id|file_operations
id|dn_neigh_seq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|dn_neigh_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release_private
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|dn_neigh_init
r_void
id|__init
id|dn_neigh_init
c_func
(paren
r_void
)paren
(brace
id|neigh_table_init
c_func
(paren
op_amp
id|dn_neigh_table
)paren
suffix:semicolon
id|proc_net_fops_create
c_func
(paren
l_string|&quot;decnet_neigh&quot;
comma
id|S_IRUGO
comma
op_amp
id|dn_neigh_seq_fops
)paren
suffix:semicolon
)brace
DECL|function|dn_neigh_cleanup
r_void
id|__exit
id|dn_neigh_cleanup
c_func
(paren
r_void
)paren
(brace
id|proc_net_remove
c_func
(paren
l_string|&quot;decnet_neigh&quot;
)paren
suffix:semicolon
id|neigh_table_clear
c_func
(paren
op_amp
id|dn_neigh_table
)paren
suffix:semicolon
)brace
eof
