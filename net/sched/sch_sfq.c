multiline_comment|/*&n; * net/sched/sch_sfq.c&t;Stochastic Fairness Queueing discipline.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Authors:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
multiline_comment|/*&t;Stochastic Fairness Queuing algorithm.&n;&t;=======================================&n;&n;&t;Source:&n;&t;Paul E. McKenney &quot;Stochastic Fairness Queuing&quot;,&n;&t;IEEE INFOCOMM&squot;90 Proceedings, San Francisco, 1990.&n;&n;&t;Paul E. McKenney &quot;Stochastic Fairness Queuing&quot;,&n;&t;&quot;Interworking: Research and Experience&quot;, v.2, 1991, p.113-131.&n;&n;&n;&t;See also:&n;&t;M. Shreedhar and George Varghese &quot;Efficient Fair&n;&t;Queuing using Deficit Round Robin&quot;, Proc. SIGCOMM 95.&n;&n;&n;&t;This is not the thing that is usually called (W)FQ nowadays. &n;&t;It does not use any timestamp mechanism, but instead&n;&t;processes queues in round-robin order.&n;&n;&t;ADVANTAGE:&n;&n;&t;- It is very cheap. Both CPU and memory requirements are minimal.&n;&n;&t;DRAWBACKS:&n;&n;&t;- &quot;Stochastic&quot; -&gt; It is not 100% fair. &n;&t;When hash collisions occur, several flows are considered as one.&n;&n;&t;- &quot;Round-robin&quot; -&gt; It introduces larger delays than virtual clock&n;&t;based schemes, and should not be used for isolating interactive&n;&t;traffic&t;from non-interactive. It means, that this scheduler&n;&t;should be used as leaf of CBQ or P3, which put interactive traffic&n;&t;to higher priority band.&n;&n;&t;We still need true WFQ for top level CSZ, but using WFQ&n;&t;for the best effort traffic is absolutely pointless:&n;&t;SFQ is superior for this purpose.&n;&n;&t;IMPLEMENTATION:&n;&t;This implementation limits maximal queue length to 128;&n;&t;maximal mtu to 2^15-1; number of hash buckets to 1024.&n;&t;The only goal of this restrictions was that all data&n;&t;fit into one 4K page :-). Struct sfq_sched_data is&n;&t;organized in anti-cache manner: all the data for a bucket&n;&t;are scattered over different locations. This is not good,&n;&t;but it allowed me to put it into 4K.&n;&n;&t;It is easy to increase these values, but not in flight.  */
DECL|macro|SFQ_DEPTH
mdefine_line|#define SFQ_DEPTH&t;&t;128
DECL|macro|SFQ_HASH_DIVISOR
mdefine_line|#define SFQ_HASH_DIVISOR&t;1024
multiline_comment|/* This type should contain at least SFQ_DEPTH*2 values */
DECL|typedef|sfq_index
r_typedef
r_int
r_char
id|sfq_index
suffix:semicolon
DECL|struct|sfq_head
r_struct
id|sfq_head
(brace
DECL|member|next
id|sfq_index
id|next
suffix:semicolon
DECL|member|prev
id|sfq_index
id|prev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sfq_sched_data
r_struct
id|sfq_sched_data
(brace
multiline_comment|/* Parameters */
DECL|member|perturb_period
r_int
id|perturb_period
suffix:semicolon
DECL|member|quantum
r_int
id|quantum
suffix:semicolon
multiline_comment|/* Allotment per round: MUST BE &gt;= MTU */
DECL|member|limit
r_int
id|limit
suffix:semicolon
multiline_comment|/* Variables */
DECL|member|perturb_timer
r_struct
id|timer_list
id|perturb_timer
suffix:semicolon
DECL|member|perturbation
r_int
id|perturbation
suffix:semicolon
DECL|member|tail
id|sfq_index
id|tail
suffix:semicolon
multiline_comment|/* Index of current slot in round */
DECL|member|max_depth
id|sfq_index
id|max_depth
suffix:semicolon
multiline_comment|/* Maximal depth */
DECL|member|ht
id|sfq_index
id|ht
(braket
id|SFQ_HASH_DIVISOR
)braket
suffix:semicolon
multiline_comment|/* Hash table */
DECL|member|next
id|sfq_index
id|next
(braket
id|SFQ_DEPTH
)braket
suffix:semicolon
multiline_comment|/* Active slots link */
DECL|member|allot
r_int
id|allot
(braket
id|SFQ_DEPTH
)braket
suffix:semicolon
multiline_comment|/* Current allotment per slot */
DECL|member|hash
r_int
r_int
id|hash
(braket
id|SFQ_DEPTH
)braket
suffix:semicolon
multiline_comment|/* Hash value indexed by slots */
DECL|member|qs
r_struct
id|sk_buff_head
id|qs
(braket
id|SFQ_DEPTH
)braket
suffix:semicolon
multiline_comment|/* Slot queue */
DECL|member|dep
r_struct
id|sfq_head
id|dep
(braket
id|SFQ_DEPTH
op_star
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Linked list of slots, indexed by depth */
)brace
suffix:semicolon
DECL|function|sfq_fold_hash
r_static
id|__inline__
r_int
id|sfq_fold_hash
c_func
(paren
r_struct
id|sfq_sched_data
op_star
id|q
comma
id|u32
id|h
comma
id|u32
id|h1
)paren
(brace
r_int
id|pert
op_assign
id|q-&gt;perturbation
suffix:semicolon
multiline_comment|/* Have we any rotation primitives? If not, WHY? */
id|h
op_xor_assign
(paren
id|h1
op_lshift
id|pert
)paren
op_xor
(paren
id|h1
op_rshift
(paren
l_int|0x1F
op_minus
id|pert
)paren
)paren
suffix:semicolon
id|h
op_xor_assign
id|h
op_rshift
l_int|10
suffix:semicolon
r_return
id|h
op_amp
l_int|0x3FF
suffix:semicolon
)brace
DECL|function|sfq_hash
r_static
r_int
id|sfq_hash
c_func
(paren
r_struct
id|sfq_sched_data
op_star
id|q
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u32
id|h
comma
id|h2
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;protocol
)paren
(brace
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IP
)paren
suffix:colon
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|h
op_assign
id|iph-&gt;daddr
suffix:semicolon
id|h2
op_assign
id|iph-&gt;saddr
op_xor
id|iph-&gt;protocol
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
)paren
op_logical_and
(paren
id|iph-&gt;protocol
op_eq
id|IPPROTO_TCP
op_logical_or
id|iph-&gt;protocol
op_eq
id|IPPROTO_UDP
op_logical_or
id|iph-&gt;protocol
op_eq
id|IPPROTO_ESP
)paren
)paren
id|h2
op_xor_assign
op_star
(paren
(paren
(paren
id|u32
op_star
)paren
id|iph
)paren
op_plus
id|iph-&gt;ihl
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|__constant_htons
c_func
(paren
id|ETH_P_IPV6
)paren
suffix:colon
(brace
r_struct
id|ipv6hdr
op_star
id|iph
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|h
op_assign
id|iph-&gt;daddr.s6_addr32
(braket
l_int|3
)braket
suffix:semicolon
id|h2
op_assign
id|iph-&gt;saddr.s6_addr32
(braket
l_int|3
)braket
op_xor
id|iph-&gt;nexthdr
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;nexthdr
op_eq
id|IPPROTO_TCP
op_logical_or
id|iph-&gt;nexthdr
op_eq
id|IPPROTO_UDP
op_logical_or
id|iph-&gt;nexthdr
op_eq
id|IPPROTO_ESP
)paren
id|h2
op_xor_assign
op_star
(paren
id|u32
op_star
)paren
op_amp
id|iph
(braket
l_int|1
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|h
op_assign
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
id|skb-&gt;dst
op_xor
id|skb-&gt;protocol
suffix:semicolon
id|h2
op_assign
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
id|skb-&gt;sk
suffix:semicolon
)brace
r_return
id|sfq_fold_hash
c_func
(paren
id|q
comma
id|h
comma
id|h2
)paren
suffix:semicolon
)brace
DECL|function|sfq_link
r_static
r_inline
r_void
id|sfq_link
c_func
(paren
r_struct
id|sfq_sched_data
op_star
id|q
comma
id|sfq_index
id|x
)paren
(brace
id|sfq_index
id|p
comma
id|n
suffix:semicolon
r_int
id|d
op_assign
id|q-&gt;qs
(braket
id|x
)braket
dot
id|qlen
op_plus
id|SFQ_DEPTH
suffix:semicolon
id|p
op_assign
id|d
suffix:semicolon
id|n
op_assign
id|q-&gt;dep
(braket
id|d
)braket
dot
id|next
suffix:semicolon
id|q-&gt;dep
(braket
id|x
)braket
dot
id|next
op_assign
id|n
suffix:semicolon
id|q-&gt;dep
(braket
id|x
)braket
dot
id|prev
op_assign
id|p
suffix:semicolon
id|q-&gt;dep
(braket
id|p
)braket
dot
id|next
op_assign
id|q-&gt;dep
(braket
id|n
)braket
dot
id|prev
op_assign
id|x
suffix:semicolon
)brace
DECL|function|sfq_dec
r_static
r_inline
r_void
id|sfq_dec
c_func
(paren
r_struct
id|sfq_sched_data
op_star
id|q
comma
id|sfq_index
id|x
)paren
(brace
id|sfq_index
id|p
comma
id|n
suffix:semicolon
id|n
op_assign
id|q-&gt;dep
(braket
id|x
)braket
dot
id|next
suffix:semicolon
id|p
op_assign
id|q-&gt;dep
(braket
id|x
)braket
dot
id|prev
suffix:semicolon
id|q-&gt;dep
(braket
id|p
)braket
dot
id|next
op_assign
id|n
suffix:semicolon
id|q-&gt;dep
(braket
id|n
)braket
dot
id|prev
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
id|p
op_logical_and
id|q-&gt;max_depth
op_eq
id|q-&gt;qs
(braket
id|x
)braket
dot
id|qlen
op_plus
l_int|1
)paren
id|q-&gt;max_depth
op_decrement
suffix:semicolon
id|sfq_link
c_func
(paren
id|q
comma
id|x
)paren
suffix:semicolon
)brace
DECL|function|sfq_inc
r_static
r_inline
r_void
id|sfq_inc
c_func
(paren
r_struct
id|sfq_sched_data
op_star
id|q
comma
id|sfq_index
id|x
)paren
(brace
id|sfq_index
id|p
comma
id|n
suffix:semicolon
r_int
id|d
suffix:semicolon
id|n
op_assign
id|q-&gt;dep
(braket
id|x
)braket
dot
id|next
suffix:semicolon
id|p
op_assign
id|q-&gt;dep
(braket
id|x
)braket
dot
id|prev
suffix:semicolon
id|q-&gt;dep
(braket
id|p
)braket
dot
id|next
op_assign
id|n
suffix:semicolon
id|q-&gt;dep
(braket
id|n
)braket
dot
id|prev
op_assign
id|p
suffix:semicolon
id|d
op_assign
id|q-&gt;qs
(braket
id|x
)braket
dot
id|qlen
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;max_depth
OL
id|d
)paren
id|q-&gt;max_depth
op_assign
id|d
suffix:semicolon
id|sfq_link
c_func
(paren
id|q
comma
id|x
)paren
suffix:semicolon
)brace
DECL|function|sfq_drop
r_static
r_int
r_int
id|sfq_drop
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|sfq_index
id|d
op_assign
id|q-&gt;max_depth
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Queue is full! Find the longest slot and&n;&t;   drop a packet from it */
r_if
c_cond
(paren
id|d
OG
l_int|1
)paren
(brace
id|sfq_index
id|x
op_assign
id|q-&gt;dep
(braket
id|d
op_plus
id|SFQ_DEPTH
)braket
dot
id|next
suffix:semicolon
id|skb
op_assign
id|q-&gt;qs
(braket
id|x
)braket
dot
id|prev
suffix:semicolon
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
id|__skb_unlink
c_func
(paren
id|skb
comma
op_amp
id|q-&gt;qs
(braket
id|x
)braket
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sfq_dec
c_func
(paren
id|q
comma
id|x
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
op_eq
l_int|1
)paren
(brace
multiline_comment|/* It is difficult to believe, but ALL THE SLOTS HAVE LENGTH 1. */
id|d
op_assign
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
suffix:semicolon
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
op_assign
id|q-&gt;next
(braket
id|d
)braket
suffix:semicolon
id|q-&gt;allot
(braket
id|q-&gt;next
(braket
id|d
)braket
)braket
op_add_assign
id|q-&gt;quantum
suffix:semicolon
id|skb
op_assign
id|q-&gt;qs
(braket
id|d
)braket
dot
id|prev
suffix:semicolon
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
id|__skb_unlink
c_func
(paren
id|skb
comma
op_amp
id|q-&gt;qs
(braket
id|d
)braket
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|sfq_dec
c_func
(paren
id|q
comma
id|d
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
id|q-&gt;ht
(braket
id|q-&gt;hash
(braket
id|d
)braket
)braket
op_assign
id|SFQ_DEPTH
suffix:semicolon
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|sfq_enqueue
id|sfq_enqueue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|hash
op_assign
id|sfq_hash
c_func
(paren
id|q
comma
id|skb
)paren
suffix:semicolon
id|sfq_index
id|x
suffix:semicolon
id|x
op_assign
id|q-&gt;ht
(braket
id|hash
)braket
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
id|SFQ_DEPTH
)paren
(brace
id|q-&gt;ht
(braket
id|hash
)braket
op_assign
id|x
op_assign
id|q-&gt;dep
(braket
id|SFQ_DEPTH
)braket
dot
id|next
suffix:semicolon
id|q-&gt;hash
(braket
id|x
)braket
op_assign
id|hash
suffix:semicolon
)brace
id|__skb_queue_tail
c_func
(paren
op_amp
id|q-&gt;qs
(braket
id|x
)braket
comma
id|skb
)paren
suffix:semicolon
id|sfq_inc
c_func
(paren
id|q
comma
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;qs
(braket
id|x
)braket
dot
id|qlen
op_eq
l_int|1
)paren
(brace
multiline_comment|/* The flow is new */
r_if
c_cond
(paren
id|q-&gt;tail
op_eq
id|SFQ_DEPTH
)paren
(brace
multiline_comment|/* It is the first flow */
id|q-&gt;tail
op_assign
id|x
suffix:semicolon
id|q-&gt;next
(braket
id|x
)braket
op_assign
id|x
suffix:semicolon
id|q-&gt;allot
(braket
id|x
)braket
op_assign
id|q-&gt;quantum
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;next
(braket
id|x
)braket
op_assign
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
suffix:semicolon
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
op_assign
id|x
suffix:semicolon
id|q-&gt;tail
op_assign
id|x
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_increment
id|sch-&gt;q.qlen
OL
id|q-&gt;limit
op_minus
l_int|1
)paren
(brace
id|sch-&gt;bstats.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|sch-&gt;bstats.packets
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sfq_drop
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|NET_XMIT_CN
suffix:semicolon
)brace
r_static
r_int
DECL|function|sfq_requeue
id|sfq_requeue
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|hash
op_assign
id|sfq_hash
c_func
(paren
id|q
comma
id|skb
)paren
suffix:semicolon
id|sfq_index
id|x
suffix:semicolon
id|x
op_assign
id|q-&gt;ht
(braket
id|hash
)braket
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
id|SFQ_DEPTH
)paren
(brace
id|q-&gt;ht
(braket
id|hash
)braket
op_assign
id|x
op_assign
id|q-&gt;dep
(braket
id|SFQ_DEPTH
)braket
dot
id|next
suffix:semicolon
id|q-&gt;hash
(braket
id|x
)braket
op_assign
id|hash
suffix:semicolon
)brace
id|__skb_queue_head
c_func
(paren
op_amp
id|q-&gt;qs
(braket
id|x
)braket
comma
id|skb
)paren
suffix:semicolon
id|sfq_inc
c_func
(paren
id|q
comma
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;qs
(braket
id|x
)braket
dot
id|qlen
op_eq
l_int|1
)paren
(brace
multiline_comment|/* The flow is new */
r_if
c_cond
(paren
id|q-&gt;tail
op_eq
id|SFQ_DEPTH
)paren
(brace
multiline_comment|/* It is the first flow */
id|q-&gt;tail
op_assign
id|x
suffix:semicolon
id|q-&gt;next
(braket
id|x
)braket
op_assign
id|x
suffix:semicolon
id|q-&gt;allot
(braket
id|x
)braket
op_assign
id|q-&gt;quantum
suffix:semicolon
)brace
r_else
(brace
id|q-&gt;next
(braket
id|x
)braket
op_assign
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
suffix:semicolon
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
op_assign
id|x
suffix:semicolon
id|q-&gt;tail
op_assign
id|x
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_increment
id|sch-&gt;q.qlen
OL
id|q-&gt;limit
op_minus
l_int|1
)paren
(brace
id|sch-&gt;qstats.requeues
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sch-&gt;qstats.drops
op_increment
suffix:semicolon
id|sfq_drop
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|NET_XMIT_CN
suffix:semicolon
)brace
r_static
r_struct
id|sk_buff
op_star
DECL|function|sfq_dequeue
id|sfq_dequeue
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|sfq_index
id|a
comma
id|old_a
suffix:semicolon
multiline_comment|/* No active slots */
r_if
c_cond
(paren
id|q-&gt;tail
op_eq
id|SFQ_DEPTH
)paren
r_return
l_int|NULL
suffix:semicolon
id|a
op_assign
id|old_a
op_assign
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
suffix:semicolon
multiline_comment|/* Grab packet */
id|skb
op_assign
id|__skb_dequeue
c_func
(paren
op_amp
id|q-&gt;qs
(braket
id|a
)braket
)paren
suffix:semicolon
id|sfq_dec
c_func
(paren
id|q
comma
id|a
)paren
suffix:semicolon
id|sch-&gt;q.qlen
op_decrement
suffix:semicolon
multiline_comment|/* Is the slot empty? */
r_if
c_cond
(paren
id|q-&gt;qs
(braket
id|a
)braket
dot
id|qlen
op_eq
l_int|0
)paren
(brace
id|q-&gt;ht
(braket
id|q-&gt;hash
(braket
id|a
)braket
)braket
op_assign
id|SFQ_DEPTH
suffix:semicolon
id|a
op_assign
id|q-&gt;next
(braket
id|a
)braket
suffix:semicolon
r_if
c_cond
(paren
id|a
op_eq
id|old_a
)paren
(brace
id|q-&gt;tail
op_assign
id|SFQ_DEPTH
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
id|q-&gt;next
(braket
id|q-&gt;tail
)braket
op_assign
id|a
suffix:semicolon
id|q-&gt;allot
(braket
id|a
)braket
op_add_assign
id|q-&gt;quantum
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|q-&gt;allot
(braket
id|a
)braket
op_sub_assign
id|skb-&gt;len
)paren
op_le
l_int|0
)paren
(brace
id|q-&gt;tail
op_assign
id|a
suffix:semicolon
id|a
op_assign
id|q-&gt;next
(braket
id|a
)braket
suffix:semicolon
id|q-&gt;allot
(braket
id|a
)braket
op_add_assign
id|q-&gt;quantum
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
r_static
r_void
DECL|function|sfq_reset
id|sfq_reset
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|sfq_dequeue
c_func
(paren
id|sch
)paren
)paren
op_ne
l_int|NULL
)paren
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|sfq_perturbation
r_static
r_void
id|sfq_perturbation
c_func
(paren
r_int
r_int
id|arg
)paren
(brace
r_struct
id|Qdisc
op_star
id|sch
op_assign
(paren
r_struct
id|Qdisc
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|q-&gt;perturbation
op_assign
id|net_random
c_func
(paren
)paren
op_amp
l_int|0x1F
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;perturb_period
)paren
(brace
id|q-&gt;perturb_timer.expires
op_assign
id|jiffies
op_plus
id|q-&gt;perturb_period
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|q-&gt;perturb_timer
)paren
suffix:semicolon
)brace
)brace
DECL|function|sfq_change
r_static
r_int
id|sfq_change
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|rtattr
op_star
id|opt
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_struct
id|tc_sfq_qopt
op_star
id|ctl
op_assign
id|RTA_DATA
c_func
(paren
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;rta_len
OL
id|RTA_LENGTH
c_func
(paren
r_sizeof
(paren
op_star
id|ctl
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sch_tree_lock
c_func
(paren
id|sch
)paren
suffix:semicolon
id|q-&gt;quantum
op_assign
id|ctl-&gt;quantum
ques
c_cond
suffix:colon
id|psched_mtu
c_func
(paren
id|sch-&gt;dev
)paren
suffix:semicolon
id|q-&gt;perturb_period
op_assign
id|ctl-&gt;perturb_period
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|ctl-&gt;limit
)paren
id|q-&gt;limit
op_assign
id|min_t
c_func
(paren
id|u32
comma
id|ctl-&gt;limit
comma
id|SFQ_DEPTH
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sch-&gt;q.qlen
op_ge
id|q-&gt;limit
op_minus
l_int|1
)paren
id|sfq_drop
c_func
(paren
id|sch
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|q-&gt;perturb_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;perturb_period
)paren
(brace
id|q-&gt;perturb_timer.expires
op_assign
id|jiffies
op_plus
id|q-&gt;perturb_period
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|q-&gt;perturb_timer
)paren
suffix:semicolon
)brace
id|sch_tree_unlock
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sfq_init
r_static
r_int
id|sfq_init
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|rtattr
op_star
id|opt
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|q-&gt;perturb_timer
)paren
suffix:semicolon
id|q-&gt;perturb_timer.data
op_assign
(paren
r_int
r_int
)paren
id|sch
suffix:semicolon
id|q-&gt;perturb_timer.function
op_assign
id|sfq_perturbation
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
id|SFQ_HASH_DIVISOR
suffix:semicolon
id|i
op_increment
)paren
id|q-&gt;ht
(braket
id|i
)braket
op_assign
id|SFQ_DEPTH
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
id|SFQ_DEPTH
suffix:semicolon
id|i
op_increment
)paren
(brace
id|skb_queue_head_init
c_func
(paren
op_amp
id|q-&gt;qs
(braket
id|i
)braket
)paren
suffix:semicolon
id|q-&gt;dep
(braket
id|i
op_plus
id|SFQ_DEPTH
)braket
dot
id|next
op_assign
id|i
op_plus
id|SFQ_DEPTH
suffix:semicolon
id|q-&gt;dep
(braket
id|i
op_plus
id|SFQ_DEPTH
)braket
dot
id|prev
op_assign
id|i
op_plus
id|SFQ_DEPTH
suffix:semicolon
)brace
id|q-&gt;limit
op_assign
id|SFQ_DEPTH
suffix:semicolon
id|q-&gt;max_depth
op_assign
l_int|0
suffix:semicolon
id|q-&gt;tail
op_assign
id|SFQ_DEPTH
suffix:semicolon
r_if
c_cond
(paren
id|opt
op_eq
l_int|NULL
)paren
(brace
id|q-&gt;quantum
op_assign
id|psched_mtu
c_func
(paren
id|sch-&gt;dev
)paren
suffix:semicolon
id|q-&gt;perturb_period
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
id|err
op_assign
id|sfq_change
c_func
(paren
id|sch
comma
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SFQ_DEPTH
suffix:semicolon
id|i
op_increment
)paren
id|sfq_link
c_func
(paren
id|q
comma
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sfq_destroy
r_static
r_void
id|sfq_destroy
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|q-&gt;perturb_timer
)paren
suffix:semicolon
)brace
DECL|function|sfq_dump
r_static
r_int
id|sfq_dump
c_func
(paren
r_struct
id|Qdisc
op_star
id|sch
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sfq_sched_data
op_star
id|q
op_assign
id|qdisc_priv
c_func
(paren
id|sch
)paren
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
id|skb-&gt;tail
suffix:semicolon
r_struct
id|tc_sfq_qopt
id|opt
suffix:semicolon
id|opt.quantum
op_assign
id|q-&gt;quantum
suffix:semicolon
id|opt.perturb_period
op_assign
id|q-&gt;perturb_period
op_div
id|HZ
suffix:semicolon
id|opt.limit
op_assign
id|q-&gt;limit
suffix:semicolon
id|opt.divisor
op_assign
id|SFQ_HASH_DIVISOR
suffix:semicolon
id|opt.flows
op_assign
id|q-&gt;limit
suffix:semicolon
id|RTA_PUT
c_func
(paren
id|skb
comma
id|TCA_OPTIONS
comma
r_sizeof
(paren
id|opt
)paren
comma
op_amp
id|opt
)paren
suffix:semicolon
r_return
id|skb-&gt;len
suffix:semicolon
id|rtattr_failure
suffix:colon
id|skb_trim
c_func
(paren
id|skb
comma
id|b
op_minus
id|skb-&gt;data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|sfq_qdisc_ops
r_static
r_struct
id|Qdisc_ops
id|sfq_qdisc_ops
op_assign
(brace
dot
id|next
op_assign
l_int|NULL
comma
dot
id|cl_ops
op_assign
l_int|NULL
comma
dot
id|id
op_assign
l_string|&quot;sfq&quot;
comma
dot
id|priv_size
op_assign
r_sizeof
(paren
r_struct
id|sfq_sched_data
)paren
comma
dot
id|enqueue
op_assign
id|sfq_enqueue
comma
dot
id|dequeue
op_assign
id|sfq_dequeue
comma
dot
id|requeue
op_assign
id|sfq_requeue
comma
dot
id|drop
op_assign
id|sfq_drop
comma
dot
id|init
op_assign
id|sfq_init
comma
dot
id|reset
op_assign
id|sfq_reset
comma
dot
id|destroy
op_assign
id|sfq_destroy
comma
dot
id|change
op_assign
l_int|NULL
comma
dot
id|dump
op_assign
id|sfq_dump
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|sfq_module_init
r_static
r_int
id|__init
id|sfq_module_init
c_func
(paren
r_void
)paren
(brace
r_return
id|register_qdisc
c_func
(paren
op_amp
id|sfq_qdisc_ops
)paren
suffix:semicolon
)brace
DECL|function|sfq_module_exit
r_static
r_void
id|__exit
id|sfq_module_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_qdisc
c_func
(paren
op_amp
id|sfq_qdisc_ops
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|sfq_module_init
)paren
id|module_exit
c_func
(paren
id|sfq_module_exit
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
