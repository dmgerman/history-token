multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;This file implements the various access functions for the&n; *&t;&t;PROC file system.  This is very similar to the IPv4 version,&n; *&t;&t;except it reports the sockets in the INET6 address family.&n; *&n; * Version:&t;$Id: proc.c,v 1.17 2002/02/01 22:01:04 davem Exp $&n; *&n; * Authors:&t;David S. Miller (davem@caip.rutgers.edu)&n; * &t;&t;YOSHIFUJI Hideaki &lt;yoshfuji@linux-ipv6.org&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/transp_v6.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|proc_net_devsnmp6
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_net_devsnmp6
suffix:semicolon
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
DECL|function|sockstat6_seq_show
r_static
r_int
id|sockstat6_seq_show
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
id|seq_printf
c_func
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snmp6_ipstats_list
r_static
r_struct
id|snmp_mib
id|snmp6_ipstats_list
(braket
)braket
op_assign
(brace
multiline_comment|/* ipv6 mib according to RFC 2465 */
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InReceives&quot;
comma
id|IPSTATS_MIB_INRECEIVES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InHdrErrors&quot;
comma
id|IPSTATS_MIB_INHDRERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InTooBigErrors&quot;
comma
id|IPSTATS_MIB_INTOOBIGERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InNoRoutes&quot;
comma
id|IPSTATS_MIB_INNOROUTES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InAddrErrors&quot;
comma
id|IPSTATS_MIB_INADDRERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InUnknownProtos&quot;
comma
id|IPSTATS_MIB_INUNKNOWNPROTOS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InTruncatedPkts&quot;
comma
id|IPSTATS_MIB_INTRUNCATEDPKTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InDiscards&quot;
comma
id|IPSTATS_MIB_INDISCARDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InDelivers&quot;
comma
id|IPSTATS_MIB_INDELIVERS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6OutForwDatagrams&quot;
comma
id|IPSTATS_MIB_OUTFORWDATAGRAMS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6OutRequests&quot;
comma
id|IPSTATS_MIB_OUTREQUESTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6OutDiscards&quot;
comma
id|IPSTATS_MIB_OUTDISCARDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6OutNoRoutes&quot;
comma
id|IPSTATS_MIB_OUTNOROUTES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6ReasmTimeout&quot;
comma
id|IPSTATS_MIB_REASMTIMEOUT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6ReasmReqds&quot;
comma
id|IPSTATS_MIB_REASMREQDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6ReasmOKs&quot;
comma
id|IPSTATS_MIB_REASMOKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6ReasmFails&quot;
comma
id|IPSTATS_MIB_REASMFAILS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6FragOKs&quot;
comma
id|IPSTATS_MIB_FRAGOKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6FragFails&quot;
comma
id|IPSTATS_MIB_FRAGFAILS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6FragCreates&quot;
comma
id|IPSTATS_MIB_FRAGCREATES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6InMcastPkts&quot;
comma
id|IPSTATS_MIB_INMCASTPKTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Ip6OutMcastPkts&quot;
comma
id|IPSTATS_MIB_OUTMCASTPKTS
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp6_icmp6_list
r_static
r_struct
id|snmp_mib
id|snmp6_icmp6_list
(braket
)braket
op_assign
(brace
multiline_comment|/* icmpv6 mib according to RFC 2466&n;&n;   Exceptions:  {In|Out}AdminProhibs are removed, because I see&n;                no good reasons to account them separately&n;&t;&t;of another dest.unreachs.&n;&t;&t;OutErrs is zero identically.&n;&t;&t;OutEchos too.&n;&t;&t;OutRouterAdvertisements too.&n;&t;&t;OutGroupMembQueries too.&n; */
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InMsgs&quot;
comma
id|ICMP6_MIB_INMSGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InErrors&quot;
comma
id|ICMP6_MIB_INERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InDestUnreachs&quot;
comma
id|ICMP6_MIB_INDESTUNREACHS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InPktTooBigs&quot;
comma
id|ICMP6_MIB_INPKTTOOBIGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InTimeExcds&quot;
comma
id|ICMP6_MIB_INTIMEEXCDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InParmProblems&quot;
comma
id|ICMP6_MIB_INPARMPROBLEMS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InEchos&quot;
comma
id|ICMP6_MIB_INECHOS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InEchoReplies&quot;
comma
id|ICMP6_MIB_INECHOREPLIES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InGroupMembQueries&quot;
comma
id|ICMP6_MIB_INGROUPMEMBQUERIES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InGroupMembResponses&quot;
comma
id|ICMP6_MIB_INGROUPMEMBRESPONSES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InGroupMembReductions&quot;
comma
id|ICMP6_MIB_INGROUPMEMBREDUCTIONS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InRouterSolicits&quot;
comma
id|ICMP6_MIB_INROUTERSOLICITS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InRouterAdvertisements&quot;
comma
id|ICMP6_MIB_INROUTERADVERTISEMENTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InNeighborSolicits&quot;
comma
id|ICMP6_MIB_INNEIGHBORSOLICITS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InNeighborAdvertisements&quot;
comma
id|ICMP6_MIB_INNEIGHBORADVERTISEMENTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6InRedirects&quot;
comma
id|ICMP6_MIB_INREDIRECTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutMsgs&quot;
comma
id|ICMP6_MIB_OUTMSGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutDestUnreachs&quot;
comma
id|ICMP6_MIB_OUTDESTUNREACHS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutPktTooBigs&quot;
comma
id|ICMP6_MIB_OUTPKTTOOBIGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutTimeExcds&quot;
comma
id|ICMP6_MIB_OUTTIMEEXCDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutParmProblems&quot;
comma
id|ICMP6_MIB_OUTPARMPROBLEMS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutEchoReplies&quot;
comma
id|ICMP6_MIB_OUTECHOREPLIES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutRouterSolicits&quot;
comma
id|ICMP6_MIB_OUTROUTERSOLICITS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutNeighborSolicits&quot;
comma
id|ICMP6_MIB_OUTNEIGHBORSOLICITS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutNeighborAdvertisements&quot;
comma
id|ICMP6_MIB_OUTNEIGHBORADVERTISEMENTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutRedirects&quot;
comma
id|ICMP6_MIB_OUTREDIRECTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutGroupMembResponses&quot;
comma
id|ICMP6_MIB_OUTGROUPMEMBRESPONSES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Icmp6OutGroupMembReductions&quot;
comma
id|ICMP6_MIB_OUTGROUPMEMBREDUCTIONS
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp6_udp6_list
r_static
r_struct
id|snmp_mib
id|snmp6_udp6_list
(braket
)braket
op_assign
(brace
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Udp6InDatagrams&quot;
comma
id|UDP_MIB_INDATAGRAMS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Udp6NoPorts&quot;
comma
id|UDP_MIB_NOPORTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Udp6InErrors&quot;
comma
id|UDP_MIB_INERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;Udp6OutDatagrams&quot;
comma
id|UDP_MIB_OUTDATAGRAMS
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
r_static
r_int
r_int
DECL|function|fold_field
id|fold_field
c_func
(paren
r_void
op_star
id|mib
(braket
)braket
comma
r_int
id|offt
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
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|res
op_add_assign
op_star
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|per_cpu_ptr
c_func
(paren
id|mib
(braket
l_int|0
)braket
comma
id|i
)paren
)paren
op_plus
id|offt
)paren
suffix:semicolon
id|res
op_add_assign
op_star
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|per_cpu_ptr
c_func
(paren
id|mib
(braket
l_int|1
)braket
comma
id|i
)paren
)paren
op_plus
id|offt
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|snmp6_seq_show_item
id|snmp6_seq_show_item
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
op_star
id|mib
comma
r_struct
id|snmp_mib
op_star
id|itemlist
)paren
(brace
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
id|itemlist
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-32s&bslash;t%lu&bslash;n&quot;
comma
id|itemlist
(braket
id|i
)braket
dot
id|name
comma
id|fold_field
c_func
(paren
id|mib
comma
id|itemlist
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
)brace
DECL|function|snmp6_seq_show
r_static
r_int
id|snmp6_seq_show
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
r_struct
id|inet6_dev
op_star
id|idev
op_assign
(paren
r_struct
id|inet6_dev
op_star
)paren
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|idev
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%-32s&bslash;t%u&bslash;n&quot;
comma
l_string|&quot;ifIndex&quot;
comma
id|idev-&gt;dev-&gt;ifindex
)paren
suffix:semicolon
id|snmp6_seq_show_item
c_func
(paren
id|seq
comma
(paren
r_void
op_star
op_star
)paren
id|idev-&gt;stats.icmpv6
comma
id|snmp6_icmp6_list
)paren
suffix:semicolon
)brace
r_else
(brace
id|snmp6_seq_show_item
c_func
(paren
id|seq
comma
(paren
r_void
op_star
op_star
)paren
id|ipv6_statistics
comma
id|snmp6_ipstats_list
)paren
suffix:semicolon
id|snmp6_seq_show_item
c_func
(paren
id|seq
comma
(paren
r_void
op_star
op_star
)paren
id|icmpv6_statistics
comma
id|snmp6_icmp6_list
)paren
suffix:semicolon
id|snmp6_seq_show_item
c_func
(paren
id|seq
comma
(paren
r_void
op_star
op_star
)paren
id|udp_stats_in6
comma
id|snmp6_udp6_list
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sockstat6_seq_open
r_static
r_int
id|sockstat6_seq_open
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
r_return
id|single_open
c_func
(paren
id|file
comma
id|sockstat6_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|sockstat6_seq_fops
r_static
r_struct
id|file_operations
id|sockstat6_seq_fops
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
id|sockstat6_seq_open
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
id|single_release
comma
)brace
suffix:semicolon
DECL|function|snmp6_seq_open
r_static
r_int
id|snmp6_seq_open
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
r_return
id|single_open
c_func
(paren
id|file
comma
id|snmp6_seq_show
comma
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
)paren
suffix:semicolon
)brace
DECL|variable|snmp6_seq_fops
r_static
r_struct
id|file_operations
id|snmp6_seq_fops
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
id|snmp6_seq_open
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
id|single_release
comma
)brace
suffix:semicolon
DECL|function|snmp6_register_dev
r_int
id|snmp6_register_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idev
op_logical_or
op_logical_neg
id|idev-&gt;dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_devsnmp6
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
id|idev-&gt;dev-&gt;name
comma
id|S_IRUGO
comma
id|proc_net_devsnmp6
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|p-&gt;data
op_assign
id|idev
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|snmp6_seq_fops
suffix:semicolon
id|idev-&gt;stats.proc_dir_entry
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snmp6_unregister_dev
r_int
id|snmp6_unregister_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|proc_net_devsnmp6
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idev
op_logical_or
op_logical_neg
id|idev-&gt;stats.proc_dir_entry
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|idev-&gt;stats.proc_dir_entry-&gt;name
comma
id|proc_net_devsnmp6
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipv6_misc_proc_init
r_int
id|__init
id|ipv6_misc_proc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;snmp6&quot;
comma
id|S_IRUGO
comma
op_amp
id|snmp6_seq_fops
)paren
)paren
r_goto
id|proc_snmp6_fail
suffix:semicolon
id|proc_net_devsnmp6
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;dev_snmp6&quot;
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_devsnmp6
)paren
r_goto
id|proc_dev_snmp6_fail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;sockstat6&quot;
comma
id|S_IRUGO
comma
op_amp
id|sockstat6_seq_fops
)paren
)paren
r_goto
id|proc_sockstat6_fail
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|proc_sockstat6_fail
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;dev_snmp6&quot;
)paren
suffix:semicolon
id|proc_dev_snmp6_fail
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;snmp6&quot;
)paren
suffix:semicolon
id|proc_snmp6_fail
suffix:colon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|ipv6_misc_proc_exit
r_void
id|ipv6_misc_proc_exit
c_func
(paren
r_void
)paren
(brace
id|proc_net_remove
c_func
(paren
l_string|&quot;sockstat6&quot;
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;dev_snmp6&quot;
)paren
suffix:semicolon
id|proc_net_remove
c_func
(paren
l_string|&quot;snmp6&quot;
)paren
suffix:semicolon
)brace
macro_line|#else&t;/* CONFIG_PROC_FS */
DECL|function|snmp6_register_dev
r_int
id|snmp6_register_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snmp6_unregister_dev
r_int
id|snmp6_unregister_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_PROC_FS */
DECL|function|snmp6_alloc_dev
r_int
id|snmp6_alloc_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idev
op_logical_or
op_logical_neg
id|idev-&gt;dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|snmp6_mib_init
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|idev-&gt;stats.icmpv6
comma
r_sizeof
(paren
r_struct
id|icmpv6_mib
)paren
comma
id|__alignof__
c_func
(paren
r_struct
id|icmpv6_mib
)paren
)paren
OL
l_int|0
)paren
r_goto
id|err_icmp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_icmp
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|snmp6_free_dev
r_int
id|snmp6_free_dev
c_func
(paren
r_struct
id|inet6_dev
op_star
id|idev
)paren
(brace
id|snmp6_mib_free
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|idev-&gt;stats.icmpv6
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
