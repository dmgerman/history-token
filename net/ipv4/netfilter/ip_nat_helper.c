multiline_comment|/* ip_nat_mangle.c - generic support functions for NAT helpers &n; *&n; * (C) 2000 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; *&n; * distributed under the terms of GNU GPL&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;linux/brlock.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
DECL|macro|ASSERT_READ_LOCK
mdefine_line|#define ASSERT_READ_LOCK(x) MUST_BE_READ_LOCKED(&amp;ip_nat_lock)
DECL|macro|ASSERT_WRITE_LOCK
mdefine_line|#define ASSERT_WRITE_LOCK(x) MUST_BE_WRITE_LOCKED(&amp;ip_nat_lock)
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
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_void
op_star
id|data
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
multiline_comment|/* SYN adjust. If it&squot;s uninitialized, of this is after last &n;&t; * correction, record it: we don&squot;t handle more than one &n;&t; * adjustment in the window, but do deal with common case of a &n;&t; * retransmit */
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
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Generic function for mangling variable-length address changes inside&n; * NATed connections (like the PORT XXX,XXX,XXX,XXX,XXX,XXX command in FTP).&n; *&n; * Takes care about all the nasty sequence number changes, checksumming,&n; * skb enlargement, ...&n; *&n; * */
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Grrr... SACK.  Fuck me even harder.  Don&squot;t want to fix it on the&n;   fly, so blow it away. */
r_void
DECL|function|ip_nat_delete_sack
id|ip_nat_delete_sack
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|tcphdr
op_star
id|tcph
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|u_int8_t
op_star
id|opt
op_assign
(paren
id|u_int8_t
op_star
)paren
id|tcph
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Seeking SACKPERM in SYN packet (doff = %u).&bslash;n&quot;
comma
id|tcph-&gt;doff
op_star
l_int|4
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
r_sizeof
(paren
r_struct
id|tcphdr
)paren
suffix:semicolon
id|i
OL
id|tcph-&gt;doff
op_star
l_int|4
suffix:semicolon
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;%u &quot;
comma
id|opt
(braket
id|i
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|opt
(braket
id|i
)braket
)paren
(brace
r_case
id|TCPOPT_NOP
suffix:colon
r_case
id|TCPOPT_EOL
suffix:colon
id|i
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TCPOPT_SACK_PERM
suffix:colon
r_goto
id|found_opt
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Worst that can happen: it will take us over. */
id|i
op_add_assign
id|opt
(braket
id|i
op_plus
l_int|1
)braket
ques
c_cond
suffix:colon
l_int|1
suffix:semicolon
)brace
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
id|found_opt
suffix:colon
id|DEBUGP
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Found SACKPERM at offset %u.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* Must be within TCP header, and valid SACK perm. */
r_if
c_cond
(paren
id|i
op_plus
id|opt
(braket
id|i
op_plus
l_int|1
)braket
op_le
id|tcph-&gt;doff
op_star
l_int|4
op_logical_and
id|opt
(braket
id|i
op_plus
l_int|1
)braket
op_eq
l_int|2
)paren
(brace
multiline_comment|/* Replace with NOPs. */
id|tcph-&gt;check
op_assign
id|ip_nat_cheat_check
c_func
(paren
op_star
(paren
(paren
id|u_int16_t
op_star
)paren
(paren
id|opt
op_plus
id|i
)paren
)paren
op_xor
l_int|0xFFFF
comma
(paren
id|TCPOPT_NOP
op_lshift
l_int|8
)paren
op_or
id|TCPOPT_NOP
comma
id|tcph-&gt;check
)paren
suffix:semicolon
id|opt
(braket
id|i
)braket
op_assign
id|opt
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|TCPOPT_NOP
suffix:semicolon
)brace
r_else
id|DEBUGP
c_func
(paren
l_string|&quot;Something wrong with SACK_PERM.&bslash;n&quot;
)paren
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
(brace
id|list_prepend
c_func
(paren
op_amp
id|helpers
comma
id|me
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
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
id|LIST_DELETE
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
eof
