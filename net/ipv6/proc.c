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
macro_line|#endif
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
DECL|struct|snmp6_item
r_struct
id|snmp6_item
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNMP6_SENTINEL
mdefine_line|#define SNMP6_SENTINEL&t;{ .name = NULL, .offset = 0 }
DECL|variable|snmp6_ipv6_list
r_static
r_struct
id|snmp6_item
id|snmp6_ipv6_list
(braket
)braket
op_assign
(brace
multiline_comment|/* ipv6 mib according to RFC 2465 */
DECL|macro|SNMP6_GEN
mdefine_line|#define SNMP6_GEN(x) { .name = #x , .offset = offsetof(struct ipv6_mib, x) }
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
id|SNMP6_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp6_icmp6_list
r_static
r_struct
id|snmp6_item
id|snmp6_icmp6_list
(braket
)braket
op_assign
(brace
multiline_comment|/* icmpv6 mib according to RFC 2466&n;&n;   Exceptions:  {In|Out}AdminProhibs are removed, because I see&n;                no good reasons to account them separately&n;&t;&t;of another dest.unreachs.&n;&t;&t;OutErrs is zero identically.&n;&t;&t;OutEchos too.&n;&t;&t;OutRouterAdvertisements too.&n;&t;&t;OutGroupMembQueries too.&n; */
DECL|macro|SNMP6_GEN
mdefine_line|#define SNMP6_GEN(x) { .name = #x , .offset = offsetof(struct icmpv6_mib, x) }
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
id|SNMP6_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp6_udp6_list
r_static
r_struct
id|snmp6_item
id|snmp6_udp6_list
(braket
)braket
op_assign
(brace
DECL|macro|SNMP6_GEN
mdefine_line|#define SNMP6_GEN(x) { .name = &quot;Udp6&quot; #x , .offset = offsetof(struct udp_mib, Udp##x) }
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
comma
DECL|macro|SNMP6_GEN
macro_line|#undef SNMP6_GEN
id|SNMP6_SENTINEL
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
r_int
r_int
op_star
)paren
(paren
(paren
(paren
r_void
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
)paren
suffix:semicolon
id|res
op_add_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
(paren
(paren
(paren
r_void
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
id|snmp6_item
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
id|offset
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
id|snmp6_ipv6_list
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
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
macro_line|#endif
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
)paren
OL
l_int|0
)paren
r_goto
id|err_icmp
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
op_logical_neg
id|proc_net_devsnmp6
)paren
(brace
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_goto
id|err_proc
suffix:semicolon
)brace
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
r_goto
id|err_proc
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
macro_line|#endif
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|err_proc
suffix:colon
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
macro_line|#endif
id|err_icmp
suffix:colon
r_return
id|err
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
macro_line|#ifdef CONFIG_PROC_FS
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
macro_line|#endif
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
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;snmp6&quot;
comma
id|S_IRUGO
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|proc_snmp6_fail
suffix:semicolon
r_else
id|p-&gt;proc_fops
op_assign
op_amp
id|snmp6_seq_fops
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
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;sockstat6&quot;
comma
id|S_IRUGO
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|proc_sockstat6_fail
suffix:semicolon
r_else
id|p-&gt;proc_fops
op_assign
op_amp
id|sockstat6_seq_fops
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|proc_sockstat6_fail
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;dev_snmp6&quot;
comma
id|proc_net
)paren
suffix:semicolon
id|proc_dev_snmp6_fail
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;snmp6&quot;
comma
id|proc_net
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
eof
