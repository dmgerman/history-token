multiline_comment|/* ip_nat_mangle.c - generic support functions for NAT helpers &n; *&n; * (C) 2000-2002 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * distributed under the terms of GNU GPL&n; *&n; * &t;14 Jan 2002 Harald Welte &lt;laforge@gnumonks.org&gt;:&n; *&t;&t;- add support for SACK adjustment &n; *&t;14 Mar 2002 Harald Welte &lt;laforge@gnumonks.org&gt;:&n; *&t;&t;- merge SACK support into newnat API&n; *&t;16 Aug 2002 Brian J. Murrell &lt;netfilter@interlinx.bc.ca&gt;:&n; *&t;&t;- make ip_nat_resize_packet more generic (TCP and UDP)&n; *&t;&t;- add ip_nat_mangle_udp_packet&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_nat_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_nat_lock)
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_conntrack_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_protocol.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_core.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/ip_nat_helper.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4/listhelp.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
mdefine_line|#define DUMP_OFFSET(x)&t;printk(&quot;offset_before=%d, offset_after=%d, correction_pos=%u&bslash;n&quot;, x-&gt;offset_before, x-&gt;offset_after, x-&gt;correction_pos);
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(format, args...)
DECL|macro|DUMP_OFFSET
mdefine_line|#define DUMP_OFFSET(x)
macro_line|#endif
DECL|variable|ip_nat_seqofs_lock
id|DECLARE_LOCK
c_func
(paren
id|ip_nat_seqofs_lock
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|ip_nat_resize_packet
id|ip_nat_resize_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
id|new_size
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_int
id|dir
suffix:semicolon
r_struct
id|ip_nat_seq
op_star
id|this_way
comma
op_star
id|other_way
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_resize_packet: old_size = %u, new_size = %u&bslash;n&quot;
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
id|new_size
)paren
suffix:semicolon
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
id|this_way
op_assign
op_amp
id|ct-&gt;nat.info.seq
(braket
id|dir
)braket
suffix:semicolon
id|other_way
op_assign
op_amp
id|ct-&gt;nat.info.seq
(braket
op_logical_neg
id|dir
)braket
suffix:semicolon
r_if
c_cond
(paren
id|new_size
OG
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
op_plus
id|skb_tailroom
c_func
(paren
op_star
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|newskb
suffix:semicolon
id|newskb
op_assign
id|skb_copy_expand
c_func
(paren
op_star
id|skb
comma
id|skb_headroom
c_func
(paren
op_star
id|skb
)paren
comma
id|new_size
op_minus
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newskb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ip_nat_resize_packet: oom&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|kfree_skb
c_func
(paren
op_star
id|skb
)paren
suffix:semicolon
op_star
id|skb
op_assign
id|newskb
suffix:semicolon
)brace
)brace
id|iph
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_TCP
)paren
(brace
r_struct
id|tcphdr
op_star
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_resize_packet: Seq_offset before: &quot;
)paren
suffix:semicolon
id|DUMP_OFFSET
c_func
(paren
id|this_way
)paren
suffix:semicolon
id|LOCK_BH
c_func
(paren
op_amp
id|ip_nat_seqofs_lock
)paren
suffix:semicolon
multiline_comment|/* SYN adjust. If it&squot;s uninitialized, of this is after last &n;&t;&t; * correction, record it: we don&squot;t handle more than one &n;&t;&t; * adjustment in the window, but do deal with common case of a &n;&t;&t; * retransmit */
r_if
c_cond
(paren
id|this_way-&gt;offset_before
op_eq
id|this_way-&gt;offset_after
op_logical_or
id|before
c_func
(paren
id|this_way-&gt;correction_pos
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
)paren
)paren
(brace
id|this_way-&gt;correction_pos
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
suffix:semicolon
id|this_way-&gt;offset_before
op_assign
id|this_way-&gt;offset_after
suffix:semicolon
id|this_way-&gt;offset_after
op_assign
(paren
r_int32
)paren
id|this_way-&gt;offset_before
op_plus
id|new_size
op_minus
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
suffix:semicolon
)brace
id|UNLOCK_BH
c_func
(paren
op_amp
id|ip_nat_seqofs_lock
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_resize_packet: Seq_offset after: &quot;
)paren
suffix:semicolon
id|DUMP_OFFSET
c_func
(paren
id|this_way
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Generic function for mangling variable-length address changes inside&n; * NATed TCP connections (like the PORT XXX,XXX,XXX,XXX,XXX,XXX&n; * command in FTP).&n; *&n; * Takes care about all the nasty sequence number changes, checksumming,&n; * skb enlargement, ...&n; *&n; * */
r_int
DECL|function|ip_nat_mangle_tcp_packet
id|ip_nat_mangle_tcp_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|match_offset
comma
r_int
r_int
id|match_len
comma
r_char
op_star
id|rep_buffer
comma
r_int
r_int
id|rep_len
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
id|u_int32_t
id|tcplen
comma
id|newlen
comma
id|newtcplen
suffix:semicolon
id|tcplen
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|newtcplen
op_assign
id|tcplen
op_minus
id|match_len
op_plus
id|rep_len
suffix:semicolon
id|newlen
op_assign
id|iph-&gt;ihl
op_star
l_int|4
op_plus
id|newtcplen
suffix:semicolon
r_if
c_cond
(paren
id|newlen
OG
l_int|65535
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
l_string|&quot;ip_nat_mangle_tcp_packet: nat&squot;ed packet &quot;
l_string|&quot;exceeds maximum packet size&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
op_ne
id|newlen
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_resize_packet
c_func
(paren
id|skb
comma
id|ct
comma
id|ctinfo
comma
id|newlen
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;resize_packet failed!!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* Alexey says: if a hook changes _data_ ... it can break&n;&t;   original packet sitting in tcp queue and this is fatal */
r_if
c_cond
(paren
id|skb_cloned
c_func
(paren
op_star
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
op_assign
id|skb_copy
c_func
(paren
op_star
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
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
l_string|&quot;Out of memory cloning TCP packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Rest of kernel will get very unhappy if we pass it&n;&t;&t;   a suddenly-orphaned skbuff */
r_if
c_cond
(paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|sk
)paren
id|skb_set_owner_w
c_func
(paren
id|nskb
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
op_star
id|skb
)paren
suffix:semicolon
op_star
id|skb
op_assign
id|nskb
suffix:semicolon
)brace
multiline_comment|/* skb may be copied !! */
id|iph
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|data
op_assign
(paren
r_void
op_star
)paren
id|tcph
op_plus
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|rep_len
op_ne
id|match_len
)paren
multiline_comment|/* move post-replacement */
id|memmove
c_func
(paren
id|data
op_plus
id|match_offset
op_plus
id|rep_len
comma
id|data
op_plus
id|match_offset
op_plus
id|match_len
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|tail
op_minus
(paren
id|data
op_plus
id|match_offset
op_plus
id|match_len
)paren
)paren
suffix:semicolon
multiline_comment|/* insert data from buffer */
id|memcpy
c_func
(paren
id|data
op_plus
id|match_offset
comma
id|rep_buffer
comma
id|rep_len
)paren
suffix:semicolon
multiline_comment|/* update skb info */
r_if
c_cond
(paren
id|newlen
OG
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_mangle_tcp_packet: Extending packet by &quot;
l_string|&quot;%u to %u bytes&bslash;n&quot;
comma
id|newlen
op_minus
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
id|newlen
)paren
suffix:semicolon
id|skb_put
c_func
(paren
op_star
id|skb
comma
id|newlen
op_minus
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_mangle_tcp_packet: Shrinking packet from &quot;
l_string|&quot;%u to %u bytes&bslash;n&quot;
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
id|newlen
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
op_star
id|skb
comma
id|newlen
)paren
suffix:semicolon
)brace
multiline_comment|/* fix checksum information */
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|newlen
)paren
suffix:semicolon
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|csum
op_assign
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|tcph
op_plus
id|tcph-&gt;doff
op_star
l_int|4
comma
id|newtcplen
op_minus
id|tcph-&gt;doff
op_star
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;check
op_assign
id|tcp_v4_check
c_func
(paren
id|tcph
comma
id|newtcplen
comma
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|tcph
comma
id|tcph-&gt;doff
op_star
l_int|4
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|csum
)paren
)paren
suffix:semicolon
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Generic function for mangling variable-length address changes inside&n; * NATed UDP connections (like the CONNECT DATA XXXXX MESG XXXXX INDEX XXXXX&n; * command in the Amanda protocol)&n; *&n; * Takes care about all the nasty sequence number changes, checksumming,&n; * skb enlargement, ...&n; *&n; * XXX - This function could be merged with ip_nat_mangle_tcp_packet which&n; *       should be fairly easy to do.&n; */
r_int
DECL|function|ip_nat_mangle_udp_packet
id|ip_nat_mangle_udp_packet
c_func
(paren
r_struct
id|sk_buff
op_star
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_int
r_int
id|match_offset
comma
r_int
r_int
id|match_len
comma
r_char
op_star
id|rep_buffer
comma
r_int
r_int
id|rep_len
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
r_struct
id|udphdr
op_star
id|udph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
r_int
r_char
op_star
id|data
suffix:semicolon
id|u_int32_t
id|udplen
comma
id|newlen
comma
id|newudplen
suffix:semicolon
id|udplen
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|newudplen
op_assign
id|udplen
op_minus
id|match_len
op_plus
id|rep_len
suffix:semicolon
id|newlen
op_assign
id|iph-&gt;ihl
op_star
l_int|4
op_plus
id|newudplen
suffix:semicolon
r_if
c_cond
(paren
id|newlen
OG
l_int|65535
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
l_string|&quot;ip_nat_mangle_udp_packet: nat&squot;ed packet &quot;
l_string|&quot;exceeds maximum packet size&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
op_ne
id|newlen
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ip_nat_resize_packet
c_func
(paren
id|skb
comma
id|ct
comma
id|ctinfo
comma
id|newlen
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;resize_packet failed!!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* Alexey says: if a hook changes _data_ ... it can break&n;&t;   original packet sitting in tcp queue and this is fatal */
r_if
c_cond
(paren
id|skb_cloned
c_func
(paren
op_star
id|skb
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|nskb
op_assign
id|skb_copy
c_func
(paren
op_star
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nskb
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
l_string|&quot;Out of memory cloning TCP packet&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Rest of kernel will get very unhappy if we pass it&n;&t;&t;   a suddenly-orphaned skbuff */
r_if
c_cond
(paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|sk
)paren
id|skb_set_owner_w
c_func
(paren
id|nskb
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|sk
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
op_star
id|skb
)paren
suffix:semicolon
op_star
id|skb
op_assign
id|nskb
suffix:semicolon
)brace
multiline_comment|/* skb may be copied !! */
id|iph
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|nh.iph
suffix:semicolon
id|udph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|data
op_assign
(paren
r_void
op_star
)paren
id|udph
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rep_len
op_ne
id|match_len
)paren
multiline_comment|/* move post-replacement */
id|memmove
c_func
(paren
id|data
op_plus
id|match_offset
op_plus
id|rep_len
comma
id|data
op_plus
id|match_offset
op_plus
id|match_len
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|tail
op_minus
(paren
id|data
op_plus
id|match_offset
op_plus
id|match_len
)paren
)paren
suffix:semicolon
multiline_comment|/* insert data from buffer */
id|memcpy
c_func
(paren
id|data
op_plus
id|match_offset
comma
id|rep_buffer
comma
id|rep_len
)paren
suffix:semicolon
multiline_comment|/* update skb info */
r_if
c_cond
(paren
id|newlen
OG
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_mangle_udp_packet: Extending packet by &quot;
l_string|&quot;%u to %u bytes&bslash;n&quot;
comma
id|newlen
op_minus
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
id|newlen
)paren
suffix:semicolon
id|skb_put
c_func
(paren
op_star
id|skb
comma
id|newlen
op_minus
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;ip_nat_mangle_udp_packet: Shrinking packet from &quot;
l_string|&quot;%u to %u bytes&bslash;n&quot;
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
comma
id|newlen
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
op_star
id|skb
comma
id|newlen
)paren
suffix:semicolon
)brace
multiline_comment|/* update the length of the UDP and IP packets to the new values*/
id|udph-&gt;len
op_assign
id|htons
c_func
(paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|len
op_minus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|newlen
)paren
suffix:semicolon
multiline_comment|/* fix udp checksum if udp checksum was previously calculated */
r_if
c_cond
(paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|csum
op_ne
l_int|0
)paren
(brace
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|csum
op_assign
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|udph
op_plus
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
id|newudplen
op_minus
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
l_int|0
)paren
suffix:semicolon
id|udph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|udph-&gt;check
op_assign
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
id|newudplen
comma
id|IPPROTO_UDP
comma
id|csum_partial
c_func
(paren
(paren
r_char
op_star
)paren
id|udph
comma
r_sizeof
(paren
r_struct
id|udphdr
)paren
comma
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|csum
)paren
)paren
suffix:semicolon
)brace
id|ip_send_check
c_func
(paren
id|iph
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Adjust one found SACK option including checksum correction */
r_static
r_void
DECL|function|sack_adjust
id|sack_adjust
c_func
(paren
r_struct
id|tcphdr
op_star
id|tcph
comma
r_int
r_char
op_star
id|ptr
comma
r_struct
id|ip_nat_seq
op_star
id|natseq
)paren
(brace
r_struct
id|tcp_sack_block
op_star
id|sp
op_assign
(paren
r_struct
id|tcp_sack_block
op_star
)paren
(paren
id|ptr
op_plus
l_int|2
)paren
suffix:semicolon
r_int
id|num_sacks
op_assign
(paren
id|ptr
(braket
l_int|1
)braket
op_minus
id|TCPOLEN_SACK_BASE
)paren
op_rshift
l_int|3
suffix:semicolon
r_int
id|i
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
id|num_sacks
suffix:semicolon
id|i
op_increment
comma
id|sp
op_increment
)paren
(brace
id|u_int32_t
id|new_start_seq
comma
id|new_end_seq
suffix:semicolon
r_if
c_cond
(paren
id|after
c_func
(paren
id|ntohl
c_func
(paren
id|sp-&gt;start_seq
)paren
op_minus
id|natseq-&gt;offset_before
comma
id|natseq-&gt;correction_pos
)paren
)paren
id|new_start_seq
op_assign
id|ntohl
c_func
(paren
id|sp-&gt;start_seq
)paren
op_minus
id|natseq-&gt;offset_after
suffix:semicolon
r_else
id|new_start_seq
op_assign
id|ntohl
c_func
(paren
id|sp-&gt;start_seq
)paren
op_minus
id|natseq-&gt;offset_before
suffix:semicolon
id|new_start_seq
op_assign
id|htonl
c_func
(paren
id|new_start_seq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|after
c_func
(paren
id|ntohl
c_func
(paren
id|sp-&gt;end_seq
)paren
op_minus
id|natseq-&gt;offset_before
comma
id|natseq-&gt;correction_pos
)paren
)paren
id|new_end_seq
op_assign
id|ntohl
c_func
(paren
id|sp-&gt;end_seq
)paren
op_minus
id|natseq-&gt;offset_after
suffix:semicolon
r_else
id|new_end_seq
op_assign
id|ntohl
c_func
(paren
id|sp-&gt;end_seq
)paren
op_minus
id|natseq-&gt;offset_before
suffix:semicolon
id|new_end_seq
op_assign
id|htonl
c_func
(paren
id|new_end_seq
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;sack_adjust: start_seq: %d-&gt;%d, end_seq: %d-&gt;%d&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|sp-&gt;start_seq
)paren
comma
id|new_start_seq
comma
id|ntohl
c_func
(paren
id|sp-&gt;end_seq
)paren
comma
id|new_end_seq
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|sp-&gt;start_seq
comma
id|new_start_seq
comma
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|sp-&gt;end_seq
comma
id|new_end_seq
comma
id|tcph-&gt;check
)paren
)paren
suffix:semicolon
id|sp-&gt;start_seq
op_assign
id|new_start_seq
suffix:semicolon
id|sp-&gt;end_seq
op_assign
id|new_end_seq
suffix:semicolon
)brace
)brace
multiline_comment|/* TCP SACK sequence number adjustment, return 0 if sack found and adjusted */
r_static
r_inline
r_int
DECL|function|ip_nat_sack_adjust
id|ip_nat_sack_adjust
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_int
id|length
comma
id|dir
comma
id|sack_adjusted
op_assign
l_int|0
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|length
op_assign
(paren
id|tcph-&gt;doff
op_star
l_int|4
)paren
op_minus
r_sizeof
(paren
r_struct
id|tcphdr
)paren
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|tcph
op_plus
l_int|1
)paren
suffix:semicolon
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
r_int
id|opcode
op_assign
op_star
id|ptr
op_increment
suffix:semicolon
r_int
id|opsize
suffix:semicolon
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|TCPOPT_EOL
suffix:colon
r_return
op_logical_neg
id|sack_adjusted
suffix:semicolon
r_case
id|TCPOPT_NOP
suffix:colon
id|length
op_decrement
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
id|opsize
op_assign
op_star
id|ptr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|opsize
OG
id|length
)paren
multiline_comment|/* no partial opts */
r_return
op_logical_neg
id|sack_adjusted
suffix:semicolon
r_if
c_cond
(paren
id|opcode
op_eq
id|TCPOPT_SACK
)paren
(brace
multiline_comment|/* found SACK */
r_if
c_cond
(paren
(paren
id|opsize
op_ge
(paren
id|TCPOLEN_SACK_BASE
op_plus
id|TCPOLEN_SACK_PERBLOCK
)paren
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|opsize
op_minus
id|TCPOLEN_SACK_BASE
)paren
op_mod
id|TCPOLEN_SACK_PERBLOCK
)paren
)paren
(brace
id|sack_adjust
c_func
(paren
id|tcph
comma
id|ptr
op_minus
l_int|2
comma
op_amp
id|ct-&gt;nat.info.seq
(braket
op_logical_neg
id|dir
)braket
)paren
suffix:semicolon
)brace
id|sack_adjusted
op_assign
l_int|1
suffix:semicolon
)brace
id|ptr
op_add_assign
id|opsize
op_minus
l_int|2
suffix:semicolon
id|length
op_sub_assign
id|opsize
suffix:semicolon
)brace
)brace
r_return
op_logical_neg
id|sack_adjusted
suffix:semicolon
)brace
multiline_comment|/* TCP sequence number adjustment */
r_int
DECL|function|ip_nat_seq_adjust
id|ip_nat_seq_adjust
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ip_conntrack
op_star
id|ct
comma
r_enum
id|ip_conntrack_info
id|ctinfo
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_int
id|dir
comma
id|newseq
comma
id|newack
suffix:semicolon
r_struct
id|ip_nat_seq
op_star
id|this_way
comma
op_star
id|other_way
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|tcph
op_assign
(paren
r_void
op_star
)paren
id|iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
id|dir
op_assign
id|CTINFO2DIR
c_func
(paren
id|ctinfo
)paren
suffix:semicolon
id|this_way
op_assign
op_amp
id|ct-&gt;nat.info.seq
(braket
id|dir
)braket
suffix:semicolon
id|other_way
op_assign
op_amp
id|ct-&gt;nat.info.seq
(braket
op_logical_neg
id|dir
)braket
suffix:semicolon
r_if
c_cond
(paren
id|after
c_func
(paren
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|this_way-&gt;correction_pos
)paren
)paren
id|newseq
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|this_way-&gt;offset_after
suffix:semicolon
r_else
id|newseq
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
op_plus
id|this_way-&gt;offset_before
suffix:semicolon
id|newseq
op_assign
id|htonl
c_func
(paren
id|newseq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|after
c_func
(paren
id|ntohl
c_func
(paren
id|tcph-&gt;ack_seq
)paren
op_minus
id|other_way-&gt;offset_before
comma
id|other_way-&gt;correction_pos
)paren
)paren
id|newack
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;ack_seq
)paren
op_minus
id|other_way-&gt;offset_after
suffix:semicolon
r_else
id|newack
op_assign
id|ntohl
c_func
(paren
id|tcph-&gt;ack_seq
)paren
op_minus
id|other_way-&gt;offset_before
suffix:semicolon
id|newack
op_assign
id|htonl
c_func
(paren
id|newack
)paren
suffix:semicolon
id|tcph-&gt;check
op_assign
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|tcph-&gt;seq
comma
id|newseq
comma
id|ip_nat_cheat_check
c_func
(paren
op_complement
id|tcph-&gt;ack_seq
comma
id|newack
comma
id|tcph-&gt;check
)paren
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Adjusting sequence number from %u-&gt;%u, ack from %u-&gt;%u&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|tcph-&gt;seq
)paren
comma
id|ntohl
c_func
(paren
id|newseq
)paren
comma
id|ntohl
c_func
(paren
id|tcph-&gt;ack_seq
)paren
comma
id|ntohl
c_func
(paren
id|newack
)paren
)paren
suffix:semicolon
id|tcph-&gt;seq
op_assign
id|newseq
suffix:semicolon
id|tcph-&gt;ack_seq
op_assign
id|newack
suffix:semicolon
id|ip_nat_sack_adjust
c_func
(paren
id|skb
comma
id|ct
comma
id|ctinfo
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|helper_cmp
id|helper_cmp
c_func
(paren
r_const
r_struct
id|ip_nat_helper
op_star
id|helper
comma
r_const
r_struct
id|ip_conntrack_tuple
op_star
id|tuple
)paren
(brace
r_return
id|ip_ct_tuple_mask_cmp
c_func
(paren
id|tuple
comma
op_amp
id|helper-&gt;tuple
comma
op_amp
id|helper-&gt;mask
)paren
suffix:semicolon
)brace
DECL|function|ip_nat_helper_register
r_int
id|ip_nat_helper_register
c_func
(paren
r_struct
id|ip_nat_helper
op_star
id|me
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|me-&gt;me
op_logical_and
op_logical_neg
(paren
id|me-&gt;flags
op_amp
id|IP_NAT_HELPER_F_STANDALONE
)paren
)paren
(brace
r_struct
id|ip_conntrack_helper
op_star
id|ct_helper
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ct_helper
op_assign
id|ip_ct_find_helper
c_func
(paren
op_amp
id|me-&gt;tuple
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|ct_helper-&gt;me
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We are a NAT helper for protocol X.  If we need&n;&t;&t;&t; * respective conntrack helper for protoccol X, compute&n;&t;&t;&t; * conntrack helper name and try to load module */
r_char
id|name
(braket
id|MODULE_NAME_LEN
)braket
suffix:semicolon
r_const
r_char
op_star
id|tmp
op_assign
id|module_name
c_func
(paren
id|me-&gt;me
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|tmp
)paren
op_plus
l_int|6
OG
id|MODULE_NAME_LEN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to &quot;
l_string|&quot;compute conntrack helper name &quot;
l_string|&quot;from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|tmp
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|tmp
op_add_assign
l_int|6
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;ip_conntrack%s&quot;
comma
id|tmp
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
op_logical_neg
id|request_module
c_func
(paren
id|name
)paren
op_logical_and
(paren
id|ct_helper
op_assign
id|ip_ct_find_helper
c_func
(paren
op_amp
id|me-&gt;tuple
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|ct_helper-&gt;me
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;unable to load module %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;unable to load module %s automatically &quot;
l_string|&quot;because kernel was compiled without kernel &quot;
l_string|&quot;module loader support&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
macro_line|#endif
)brace
)brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|LIST_FIND
c_func
(paren
op_amp
id|helpers
comma
id|helper_cmp
comma
r_struct
id|ip_nat_helper
op_star
comma
op_amp
id|me-&gt;tuple
)paren
)paren
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_else
id|list_prepend
c_func
(paren
op_amp
id|helpers
comma
id|me
)paren
suffix:semicolon
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|kill_helper
id|kill_helper
c_func
(paren
r_const
r_struct
id|ip_conntrack
op_star
id|i
comma
r_void
op_star
id|helper
)paren
(brace
r_int
id|ret
suffix:semicolon
id|READ_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|i-&gt;nat.info.helper
op_eq
id|helper
)paren
suffix:semicolon
id|READ_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ip_nat_helper_unregister
r_void
id|ip_nat_helper_unregister
c_func
(paren
r_struct
id|ip_nat_helper
op_star
id|me
)paren
(brace
id|WRITE_LOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* Autoloading conntrack helper might have failed */
r_if
c_cond
(paren
id|LIST_FIND
c_func
(paren
op_amp
id|helpers
comma
id|helper_cmp
comma
r_struct
id|ip_nat_helper
op_star
comma
op_amp
id|me-&gt;tuple
)paren
)paren
(brace
id|LIST_DELETE
c_func
(paren
op_amp
id|helpers
comma
id|me
)paren
suffix:semicolon
)brace
id|WRITE_UNLOCK
c_func
(paren
op_amp
id|ip_nat_lock
)paren
suffix:semicolon
multiline_comment|/* Someone could be still looking at the helper in a bh. */
id|br_write_lock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
id|br_write_unlock_bh
c_func
(paren
id|BR_NETPROTO_LOCK
)paren
suffix:semicolon
multiline_comment|/* Find anything using it, and umm, kill them.  We can&squot;t turn&n;&t;   them into normal connections: if we&squot;ve adjusted SYNs, then&n;&t;   they&squot;ll ackstorm.  So we just drop it.  We used to just&n;&t;   bump module count when a connection existed, but that&n;&t;   forces admins to gen fake RSTs or bounce box, either of&n;&t;   which is just a long-winded way of making things&n;&t;   worse. --RR */
id|ip_ct_selective_cleanup
c_func
(paren
id|kill_helper
comma
id|me
)paren
suffix:semicolon
multiline_comment|/* If we are no standalone NAT helper, we need to decrement usage count&n;&t; * on our conntrack helper */
r_if
c_cond
(paren
id|me-&gt;me
op_logical_and
op_logical_neg
(paren
id|me-&gt;flags
op_amp
id|IP_NAT_HELPER_F_STANDALONE
)paren
)paren
(brace
r_struct
id|ip_conntrack_helper
op_star
id|ct_helper
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ct_helper
op_assign
id|ip_ct_find_helper
c_func
(paren
op_amp
id|me-&gt;tuple
)paren
)paren
)paren
id|module_put
c_func
(paren
id|ct_helper-&gt;me
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
r_else
id|printk
c_func
(paren
l_string|&quot;%s: unable to decrement usage count&quot;
l_string|&quot; of conntrack helper %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|me-&gt;me-&gt;name
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
eof
