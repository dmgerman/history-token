multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;This file implements the various access functions for the&n; *&t;&t;PROC file system.  This is very similar to the IPv4 version,&n; *&t;&t;except it reports the sockets in the INET6 address family.&n; *&n; * Version:&t;$Id: proc.c,v 1.17 2002/02/01 22:01:04 davem Exp $&n; *&n; * Authors:&t;David S. Miller (davem@caip.rutgers.edu)&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
DECL|function|fold_prot_inuse
r_static
r_int
id|fold_prot_inuse
c_func
(paren
r_struct
id|proto
op_star
id|proto
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
id|res
op_add_assign
id|proto-&gt;stats
(braket
id|cpu
)braket
dot
id|inuse
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|afinet6_get_info
r_int
id|afinet6_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;TCP6: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|tcpv6_prot
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;UDP6: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|udpv6_prot
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;RAW6: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|rawv6_prot
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;FRAG6: inuse %d memory %d&bslash;n&quot;
comma
id|ip6_frag_nqueues
comma
id|atomic_read
c_func
(paren
op_amp
id|ip6_frag_mem
)paren
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|struct|snmp6_item
r_struct
id|snmp6_item
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|ptr
r_int
r_int
op_star
id|ptr
suffix:semicolon
DECL|member|mibsize
r_int
id|mibsize
suffix:semicolon
DECL|variable|snmp6_list
)brace
id|snmp6_list
(braket
)braket
op_assign
(brace
multiline_comment|/* ipv6 mib according to draft-ietf-ipngwg-ipv6-mib-04 */
DECL|macro|SNMP6_GEN
mdefine_line|#define SNMP6_GEN(x) { #x , &amp;ipv6_statistics[0].x, sizeof(struct ipv6_mib)/sizeof(unsigned long) }
id|SNMP6_GEN
c_func
(paren
id|Ip6InReceives
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InHdrErrors
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InTooBigErrors
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InNoRoutes
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InAddrErrors
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InUnknownProtos
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InTruncatedPkts
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InDiscards
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InDelivers
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6OutForwDatagrams
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6OutRequests
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6OutDiscards
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6OutNoRoutes
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6ReasmTimeout
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6ReasmReqds
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6ReasmOKs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6ReasmFails
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6FragOKs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6FragFails
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6FragCreates
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6InMcastPkts
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Ip6OutMcastPkts
)paren
comma
DECL|macro|SNMP6_GEN
macro_line|#undef SNMP6_GEN
multiline_comment|/* icmpv6 mib according to draft-ietf-ipngwg-ipv6-icmp-mib-02&n;&n;   Exceptions:  {In|Out}AdminProhibs are removed, because I see&n;                no good reasons to account them separately&n;&t;&t;of another dest.unreachs.&n;&t;&t;OutErrs is zero identically.&n;&t;&t;OutEchos too.&n;&t;&t;OutRouterAdvertisements too.&n;&t;&t;OutGroupMembQueries too.&n; */
DECL|macro|SNMP6_GEN
mdefine_line|#define SNMP6_GEN(x) { #x , &amp;icmpv6_statistics[0].x, sizeof(struct icmpv6_mib)/sizeof(unsigned long) }
id|SNMP6_GEN
c_func
(paren
id|Icmp6InMsgs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InErrors
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InDestUnreachs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InPktTooBigs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InTimeExcds
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InParmProblems
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InEchos
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InEchoReplies
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InGroupMembQueries
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InGroupMembResponses
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InGroupMembReductions
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InRouterSolicits
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InRouterAdvertisements
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InNeighborSolicits
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InNeighborAdvertisements
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6InRedirects
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutMsgs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutDestUnreachs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutPktTooBigs
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutTimeExcds
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutParmProblems
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutEchoReplies
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutRouterSolicits
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutNeighborSolicits
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutNeighborAdvertisements
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutRedirects
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutGroupMembResponses
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|Icmp6OutGroupMembReductions
)paren
comma
DECL|macro|SNMP6_GEN
macro_line|#undef SNMP6_GEN
DECL|macro|SNMP6_GEN
mdefine_line|#define SNMP6_GEN(x) { &quot;Udp6&quot; #x , &amp;udp_stats_in6[0].Udp##x, sizeof(struct udp_mib)/sizeof(unsigned long) }
id|SNMP6_GEN
c_func
(paren
id|InDatagrams
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|NoPorts
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|InErrors
)paren
comma
id|SNMP6_GEN
c_func
(paren
id|OutDatagrams
)paren
DECL|macro|SNMP6_GEN
macro_line|#undef SNMP6_GEN
)brace
suffix:semicolon
DECL|function|fold_field
r_static
r_int
r_int
id|fold_field
c_func
(paren
r_int
r_int
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|res
op_assign
l_int|0
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|res
op_add_assign
id|ptr
(braket
l_int|2
op_star
id|i
op_star
id|size
)braket
suffix:semicolon
id|res
op_add_assign
id|ptr
(braket
(paren
l_int|2
op_star
id|i
op_plus
l_int|1
)paren
op_star
id|size
)braket
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|afinet6_get_snmp
r_int
id|afinet6_get_snmp
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_int
id|len
op_assign
l_int|0
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
r_sizeof
(paren
id|snmp6_list
)paren
op_div
r_sizeof
(paren
id|snmp6_list
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-32s&bslash;t%ld&bslash;n&quot;
comma
id|snmp6_list
(braket
id|i
)braket
dot
id|name
comma
id|fold_field
c_func
(paren
id|snmp6_list
(braket
id|i
)braket
dot
id|ptr
comma
id|snmp6_list
(braket
id|i
)braket
dot
id|mibsize
)paren
)paren
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
