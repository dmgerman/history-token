multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;The Internet Protocol (IP) module.&n; *&n; * Version:&t;$Id: ip_input.c,v 1.55 2002/01/12 07:39:45 davem Exp $&n; *&n; * Authors:&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Donald Becker, &lt;becker@super.org&gt;&n; *&t;&t;Alan Cox, &lt;Alan.Cox@linux.org&gt;&n; *&t;&t;Richard Underwood&n; *&t;&t;Stefan Becker, &lt;stefanb@yello.ping.de&gt;&n; *&t;&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;Commented a couple of minor bits of surplus code&n; *&t;&t;Alan Cox&t;:&t;Undefining IP_FORWARD doesn&squot;t include the code&n; *&t;&t;&t;&t;&t;(just stops a compiler warning).&n; *&t;&t;Alan Cox&t;:&t;Frames with &gt;=MAX_ROUTE record routes, strict routes or loose routes&n; *&t;&t;&t;&t;&t;are junked rather than corrupting things.&n; *&t;&t;Alan Cox&t;:&t;Frames to bad broadcast subnets are dumped&n; *&t;&t;&t;&t;&t;We used to process them non broadcast and&n; *&t;&t;&t;&t;&t;boy could that cause havoc.&n; *&t;&t;Alan Cox&t;:&t;ip_forward sets the free flag on the&n; *&t;&t;&t;&t;&t;new frame it queues. Still crap because&n; *&t;&t;&t;&t;&t;it copies the frame but at least it&n; *&t;&t;&t;&t;&t;doesn&squot;t eat memory too.&n; *&t;&t;Alan Cox&t;:&t;Generic queue code and memory fixes.&n; *&t;&t;Fred Van Kempen :&t;IP fragment support (borrowed from NET2E)&n; *&t;&t;Gerhard Koerting:&t;Forward fragmented frames correctly.&n; *&t;&t;Gerhard Koerting: &t;Fixes to my fix of the above 8-).&n; *&t;&t;Gerhard Koerting:&t;IP interface addressing fix.&n; *&t;&t;Linus Torvalds&t;:&t;More robustness checks&n; *&t;&t;Alan Cox&t;:&t;Even more checks: Still not as robust as it ought to be&n; *&t;&t;Alan Cox&t;:&t;Save IP header pointer for later&n; *&t;&t;Alan Cox&t;:&t;ip option setting&n; *&t;&t;Alan Cox&t;:&t;Use ip_tos/ip_ttl settings&n; *&t;&t;Alan Cox&t;:&t;Fragmentation bogosity removed&n; *&t;&t;&t;&t;&t;(Thanks to Mark.Bush@prg.ox.ac.uk)&n; *&t;&t;Dmitry Gorodchanin :&t;Send of a raw packet crash fix.&n; *&t;&t;Alan Cox&t;:&t;Silly ip bug when an overlength&n; *&t;&t;&t;&t;&t;fragment turns up. Now frees the&n; *&t;&t;&t;&t;&t;queue.&n; *&t;&t;Linus Torvalds/ :&t;Memory leakage on fragmentation&n; *&t;&t;Alan Cox&t;:&t;handling.&n; *&t;&t;Gerhard Koerting:&t;Forwarding uses IP priority hints&n; *&t;&t;Teemu Rantanen&t;:&t;Fragment problems.&n; *&t;&t;Alan Cox&t;:&t;General cleanup, comments and reformat&n; *&t;&t;Alan Cox&t;:&t;SNMP statistics&n; *&t;&t;Alan Cox&t;:&t;BSD address rule semantics. Also see&n; *&t;&t;&t;&t;&t;UDP as there is a nasty checksum issue&n; *&t;&t;&t;&t;&t;if you do things the wrong way.&n; *&t;&t;Alan Cox&t;:&t;Always defrag, moved IP_FORWARD to the config.in file&n; *&t;&t;Alan Cox&t;: &t;IP options adjust sk-&gt;priority.&n; *&t;&t;Pedro Roque&t;:&t;Fix mtu/length error in ip_forward.&n; *&t;&t;Alan Cox&t;:&t;Avoid ip_chk_addr when possible.&n; *&t;Richard Underwood&t;:&t;IP multicasting.&n; *&t;&t;Alan Cox&t;:&t;Cleaned up multicast handlers.&n; *&t;&t;Alan Cox&t;:&t;RAW sockets demultiplex in the BSD style.&n; *&t;&t;Gunther Mayer&t;:&t;Fix the SNMP reporting typo&n; *&t;&t;Alan Cox&t;:&t;Always in group 224.0.0.1&n; *&t;Pauline Middelink&t;:&t;Fast ip_checksum update when forwarding&n; *&t;&t;&t;&t;&t;Masquerading support.&n; *&t;&t;Alan Cox&t;:&t;Multicast loopback error for 224.0.0.1&n; *&t;&t;Alan Cox&t;:&t;IP_MULTICAST_LOOP option.&n; *&t;&t;Alan Cox&t;:&t;Use notifiers.&n; *&t;&t;Bjorn Ekwall&t;:&t;Removed ip_csum (from slhc.c too)&n; *&t;&t;Bjorn Ekwall&t;:&t;Moved ip_fast_csum to ip.h (inline!)&n; *&t;&t;Stefan Becker   :       Send out ICMP HOST REDIRECT&n; *&t;Arnt Gulbrandsen&t;:&t;ip_build_xmit&n; *&t;&t;Alan Cox&t;:&t;Per socket routing cache&n; *&t;&t;Alan Cox&t;:&t;Fixed routing cache, added header cache.&n; *&t;&t;Alan Cox&t;:&t;Loopback didn&squot;t work right in original ip_build_xmit - fixed it.&n; *&t;&t;Alan Cox&t;:&t;Only send ICMP_REDIRECT if src/dest are the same net.&n; *&t;&t;Alan Cox&t;:&t;Incoming IP option handling.&n; *&t;&t;Alan Cox&t;:&t;Set saddr on raw output frames as per BSD.&n; *&t;&t;Alan Cox&t;:&t;Stopped broadcast source route explosions.&n; *&t;&t;Alan Cox&t;:&t;Can disable source routing&n; *&t;&t;Takeshi Sone    :&t;Masquerading didn&squot;t work.&n; *&t;Dave Bonn,Alan Cox&t;:&t;Faster IP forwarding whenever possible.&n; *&t;&t;Alan Cox&t;:&t;Memory leaks, tramples, misc debugging.&n; *&t;&t;Alan Cox&t;:&t;Fixed multicast (by popular demand 8))&n; *&t;&t;Alan Cox&t;:&t;Fixed forwarding (by even more popular demand 8))&n; *&t;&t;Alan Cox&t;:&t;Fixed SNMP statistics [I think]&n; *&t;Gerhard Koerting&t;:&t;IP fragmentation forwarding fix&n; *&t;&t;Alan Cox&t;:&t;Device lock against page fault.&n; *&t;&t;Alan Cox&t;:&t;IP_HDRINCL facility.&n; *&t;Werner Almesberger&t;:&t;Zero fragment bug&n; *&t;&t;Alan Cox&t;:&t;RAW IP frame length bug&n; *&t;&t;Alan Cox&t;:&t;Outgoing firewall on build_xmit&n; *&t;&t;A.N.Kuznetsov&t;:&t;IP_OPTIONS support throughout the kernel&n; *&t;&t;Alan Cox&t;:&t;Multicast routing hooks&n; *&t;&t;Jos Vos&t;&t;:&t;Do accounting *before* call_in_firewall&n; *&t;Willy Konynenberg&t;:&t;Transparent proxying support&n; *&n; *  &n; *&n; * To Fix:&n; *&t;&t;IP fragmentation wants rewriting cleanly. The RFC815 algorithm is much more efficient&n; *&t;&t;and could be made very efficient with the addition of some virtual memory hacks to permit&n; *&t;&t;the allocation of a buffer that can then be &squot;grown&squot; by twiddling page tables.&n; *&t;&t;Output fragmentation wants updating along with the buffer management to use a single &n; *&t;&t;interleaved copy algorithm so that fragmenting has a one copy overhead. Actual packet&n; *&t;&t;output should probably do its own fragmentation at the UDP/RAW layer. TCP shouldn&squot;t cause&n; *&t;&t;fragmentation anyway.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;net/snmp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/raw.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/netfilter_ipv4.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;linux/mroute.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
multiline_comment|/*&n; *&t;SNMP management statistics&n; */
id|DEFINE_SNMP_STAT
c_func
(paren
r_struct
id|ip_mib
comma
id|ip_statistics
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Process Router Attention IP option&n; */
DECL|function|ip_call_ra_chain
r_int
id|ip_call_ra_chain
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ip_ra_chain
op_star
id|ra
suffix:semicolon
id|u8
id|protocol
op_assign
id|skb-&gt;nh.iph-&gt;protocol
suffix:semicolon
r_struct
id|sock
op_star
id|last
op_assign
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ra
op_assign
id|ip_ra_chain
suffix:semicolon
id|ra
suffix:semicolon
id|ra
op_assign
id|ra-&gt;next
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
id|ra-&gt;sk
suffix:semicolon
multiline_comment|/* If socket is bound to an interface, only report&n;&t;&t; * the packet if it came  from that interface.&n;&t;&t; */
r_if
c_cond
(paren
id|sk
op_logical_and
id|inet_sk
c_func
(paren
id|sk
)paren
op_member_access_from_pointer
id|num
op_eq
id|protocol
op_logical_and
(paren
op_logical_neg
id|sk-&gt;sk_bound_dev_if
op_logical_or
id|sk-&gt;sk_bound_dev_if
op_eq
id|skb-&gt;dev-&gt;ifindex
)paren
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
)paren
(brace
id|skb
op_assign
id|ip_defrag
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|last
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb2
op_assign
id|skb_clone
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb2
)paren
id|raw_rcv
c_func
(paren
id|last
comma
id|skb2
)paren
suffix:semicolon
)brace
id|last
op_assign
id|sk
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|last
)paren
(brace
id|raw_rcv
c_func
(paren
id|last
comma
id|skb
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|ip_ra_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ip_local_deliver_finish
r_static
r_inline
r_int
id|ip_local_deliver_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|ihl
op_assign
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
id|nf_debug_ip_local_deliver
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb-&gt;nf_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /*CONFIG_NETFILTER_DEBUG*/
id|__skb_pull
c_func
(paren
id|skb
comma
id|ihl
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NETFILTER
multiline_comment|/* Free reference early: we don&squot;t need it any more, and it may&n;           hold ip_conntrack module loaded indefinitely. */
id|nf_conntrack_put
c_func
(paren
id|skb-&gt;nfct
)paren
suffix:semicolon
id|skb-&gt;nfct
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif /*CONFIG_NETFILTER*/
multiline_comment|/* Point into the IP datagram, just past the header. */
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|rcu_read_lock
c_func
(paren
)paren
suffix:semicolon
(brace
multiline_comment|/* Note: See raw.c and net/raw.h, RAWV4_HTABLE_SIZE==MAX_INET_PROTOS */
r_int
id|protocol
op_assign
id|skb-&gt;nh.iph-&gt;protocol
suffix:semicolon
r_int
id|hash
suffix:semicolon
r_struct
id|sock
op_star
id|raw_sk
suffix:semicolon
r_struct
id|inet_protocol
op_star
id|ipprot
suffix:semicolon
id|resubmit
suffix:colon
id|hash
op_assign
id|protocol
op_amp
(paren
id|MAX_INET_PROTOS
op_minus
l_int|1
)paren
suffix:semicolon
id|raw_sk
op_assign
id|sk_head
c_func
(paren
op_amp
id|raw_v4_htable
(braket
id|hash
)braket
)paren
suffix:semicolon
multiline_comment|/* If there maybe a raw socket we must check - if not we&n;&t;&t; * don&squot;t care less&n;&t;&t; */
r_if
c_cond
(paren
id|raw_sk
)paren
id|raw_v4_input
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph
comma
id|hash
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ipprot
op_assign
id|inet_protos
(braket
id|hash
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
r_int
id|ret
suffix:semicolon
id|smp_read_barrier_depends
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ipprot-&gt;no_policy
op_logical_and
op_logical_neg
id|xfrm4_policy_check
c_func
(paren
l_int|NULL
comma
id|XFRM_POLICY_IN
comma
id|skb
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|ipprot
op_member_access_from_pointer
id|handler
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|protocol
op_assign
op_minus
id|ret
suffix:semicolon
r_goto
id|resubmit
suffix:semicolon
)brace
id|IP_INC_STATS_BH
c_func
(paren
id|IpInDelivers
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|raw_sk
)paren
(brace
r_if
c_cond
(paren
id|xfrm4_policy_check
c_func
(paren
l_int|NULL
comma
id|XFRM_POLICY_IN
comma
id|skb
)paren
)paren
(brace
id|IP_INC_STATS_BH
c_func
(paren
id|IpInUnknownProtos
)paren
suffix:semicolon
id|icmp_send
c_func
(paren
id|skb
comma
id|ICMP_DEST_UNREACH
comma
id|ICMP_PROT_UNREACH
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
id|IP_INC_STATS_BH
c_func
(paren
id|IpInDelivers
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|rcu_read_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;Deliver IP Packets to the higher protocol layers.&n; */
DECL|function|ip_local_deliver
r_int
id|ip_local_deliver
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
multiline_comment|/*&n;&t; *&t;Reassemble IP fragments.&n;&t; */
r_if
c_cond
(paren
id|skb-&gt;nh.iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
)paren
(brace
id|skb
op_assign
id|ip_defrag
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|NF_HOOK
c_func
(paren
id|PF_INET
comma
id|NF_IP_LOCAL_IN
comma
id|skb
comma
id|skb-&gt;dev
comma
l_int|NULL
comma
id|ip_local_deliver_finish
)paren
suffix:semicolon
)brace
DECL|function|ip_rcv_finish
r_static
r_inline
r_int
id|ip_rcv_finish
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|skb-&gt;dev
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Initialise the virtual path cache for the packet. It describes&n;&t; *&t;how the packet travels inside Linux networking.&n;&t; */
r_if
c_cond
(paren
id|skb-&gt;dst
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ip_route_input
c_func
(paren
id|skb
comma
id|iph-&gt;daddr
comma
id|iph-&gt;saddr
comma
id|iph-&gt;tos
comma
id|dev
)paren
)paren
r_goto
id|drop
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_CLS_ROUTE
r_if
c_cond
(paren
id|skb-&gt;dst-&gt;tclassid
)paren
(brace
r_struct
id|ip_rt_acct
op_star
id|st
op_assign
id|ip_rt_acct
op_plus
l_int|256
op_star
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|u32
id|idx
op_assign
id|skb-&gt;dst-&gt;tclassid
suffix:semicolon
id|st
(braket
id|idx
op_amp
l_int|0xFF
)braket
dot
id|o_packets
op_increment
suffix:semicolon
id|st
(braket
id|idx
op_amp
l_int|0xFF
)braket
dot
id|o_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|st
(braket
(paren
id|idx
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)braket
dot
id|i_packets
op_increment
suffix:semicolon
id|st
(braket
(paren
id|idx
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)braket
dot
id|i_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|iph-&gt;ihl
OG
l_int|5
)paren
(brace
r_struct
id|ip_options
op_star
id|opt
suffix:semicolon
multiline_comment|/* It looks as overkill, because not all&n;&t;&t;   IP options require packet mangling.&n;&t;&t;   But it is the easiest for now, especially taking&n;&t;&t;   into account that combination of IP options&n;&t;&t;   and running sniffer is extremely rare condition.&n;&t;&t;                                      --ANK (980813)&n;&t;&t;*/
r_if
c_cond
(paren
id|skb_cow
c_func
(paren
id|skb
comma
id|skb_headroom
c_func
(paren
id|skb
)paren
)paren
)paren
(brace
id|IP_INC_STATS_BH
c_func
(paren
id|IpInDiscards
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|ip_options_compile
c_func
(paren
l_int|NULL
comma
id|skb
)paren
)paren
r_goto
id|inhdr_error
suffix:semicolon
id|opt
op_assign
op_amp
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opt-&gt;srr
)paren
(brace
r_struct
id|in_device
op_star
id|in_dev
op_assign
id|in_dev_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|IN_DEV_SOURCE_ROUTE
c_func
(paren
id|in_dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|IN_DEV_LOG_MARTIANS
c_func
(paren
id|in_dev
)paren
op_logical_and
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;source route option %u.%u.%u.%u -&gt; %u.%u.%u.%u&bslash;n&quot;
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;saddr
)paren
comma
id|NIPQUAD
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
id|in_dev_put
c_func
(paren
id|in_dev
)paren
suffix:semicolon
r_goto
id|drop
suffix:semicolon
)brace
id|in_dev_put
c_func
(paren
id|in_dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ip_options_rcv_srr
c_func
(paren
id|skb
)paren
)paren
r_goto
id|drop
suffix:semicolon
)brace
)brace
r_return
id|dst_input
c_func
(paren
id|skb
)paren
suffix:semicolon
id|inhdr_error
suffix:colon
id|IP_INC_STATS_BH
c_func
(paren
id|IpInHdrErrors
)paren
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;Main IP Receive routine.&n; */
DECL|function|ip_rcv
r_int
id|ip_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
multiline_comment|/* When the interface is in promisc. mode, drop all the crap&n;&t; * that it receives, do not try to analyse it.&n;&t; */
r_if
c_cond
(paren
id|skb-&gt;pkt_type
op_eq
id|PACKET_OTHERHOST
)paren
r_goto
id|drop
suffix:semicolon
id|IP_INC_STATS_BH
c_func
(paren
id|IpInReceives
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_share_check
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|IP_INC_STATS_BH
c_func
(paren
id|IpInDiscards
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
)paren
r_goto
id|inhdr_error
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
multiline_comment|/*&n;&t; *&t;RFC1122: 3.1.2.2 MUST silently discard any IP frame that fails the checksum.&n;&t; *&n;&t; *&t;Is the datagram acceptable?&n;&t; *&n;&t; *&t;1.&t;Length at least the size of an ip header&n;&t; *&t;2.&t;Version of 4&n;&t; *&t;3.&t;Checksums correctly. [Speed optimisation for later, skip loopback checksums]&n;&t; *&t;4.&t;Doesn&squot;t have a bogus length&n;&t; */
r_if
c_cond
(paren
id|iph-&gt;ihl
OL
l_int|5
op_logical_or
id|iph-&gt;version
op_ne
l_int|4
)paren
r_goto
id|inhdr_error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
)paren
r_goto
id|inhdr_error
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|ip_fast_csum
c_func
(paren
(paren
id|u8
op_star
)paren
id|iph
comma
id|iph-&gt;ihl
)paren
op_ne
l_int|0
)paren
r_goto
id|inhdr_error
suffix:semicolon
(brace
id|__u32
id|len
op_assign
id|ntohs
c_func
(paren
id|iph-&gt;tot_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OL
id|len
op_logical_or
id|len
OL
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
r_goto
id|inhdr_error
suffix:semicolon
multiline_comment|/* Our transport medium may have padded the buffer out. Now we know it&n;&t;&t; * is IP we can trim to the true length of the frame.&n;&t;&t; * Note this now means skb-&gt;len holds ntohs(iph-&gt;tot_len).&n;&t;&t; */
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|len
)paren
(brace
id|__pskb_trim
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
)brace
)brace
r_return
id|NF_HOOK
c_func
(paren
id|PF_INET
comma
id|NF_IP_PRE_ROUTING
comma
id|skb
comma
id|dev
comma
l_int|NULL
comma
id|ip_rcv_finish
)paren
suffix:semicolon
id|inhdr_error
suffix:colon
id|IP_INC_STATS_BH
c_func
(paren
id|IpInHdrErrors
)paren
suffix:semicolon
id|drop
suffix:colon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|NET_RX_DROP
suffix:semicolon
)brace
eof
