multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;This file implements the various access functions for the&n; *&t;&t;PROC file system.  It is mainly used for debugging and&n; *&t;&t;statistics.&n; *&n; * Version:&t;$Id: proc.c,v 1.45 2001/05/16 16:45:35 davem Exp $&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Gerald J. Heim, &lt;heim@peanuts.informatik.uni-tuebingen.de&gt;&n; *&t;&t;Fred Baumgarten, &lt;dc6iq@insu1.etec.uni-karlsruhe.de&gt;&n; *&t;&t;Erik Schoenfelder, &lt;schoenfr@ibr.cs.tu-bs.de&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;UDP sockets show the rxqueue/txqueue&n; *&t;&t;&t;&t;&t;using hint flag for the netinfo.&n; *&t;Pauline Middelink&t;:&t;identd support&n; *&t;&t;Alan Cox&t;:&t;Make /proc safer.&n; *&t;Erik Schoenfelder&t;:&t;/proc/net/snmp&n; *&t;&t;Alan Cox&t;:&t;Handle dead sockets properly.&n; *&t;Gerhard Koerting&t;:&t;Show both timers&n; *&t;&t;Alan Cox&t;:&t;Allow inode to be NULL (kernel socket)&n; *&t;Andi Kleen&t;&t;:&t;Add support for open_requests and&n; *&t;&t;&t;&t;&t;split functions for more readibility.&n; *&t;Andi Kleen&t;&t;:&t;Add support for /proc/net/netstat&n; *&t;Arnaldo C. Melo&t;&t;:&t;Convert to seq_file&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/raw.h&gt;
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
multiline_comment|/*&n; *&t;Report socket allocation statistics [mea@utu.fi]&n; */
DECL|function|sockstat_seq_show
r_static
r_int
id|sockstat_seq_show
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
multiline_comment|/* From net/socket.c */
r_extern
r_void
id|socket_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
)paren
suffix:semicolon
id|socket_seq_show
c_func
(paren
id|seq
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;TCP: inuse %d orphan %d tw %d alloc %d mem %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|tcp_prot
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|tcp_orphan_count
)paren
comma
id|tcp_tw_count
comma
id|atomic_read
c_func
(paren
op_amp
id|tcp_sockets_allocated
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|tcp_memory_allocated
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;UDP: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|udp_prot
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;RAW: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|raw_prot
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;FRAG: inuse %d memory %d&bslash;n&quot;
comma
id|ip_frag_nqueues
comma
id|atomic_read
c_func
(paren
op_amp
id|ip_frag_mem
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sockstat_seq_open
r_static
r_int
id|sockstat_seq_open
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
id|sockstat_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|sockstat_seq_fops
r_static
r_struct
id|file_operations
id|sockstat_seq_fops
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
id|sockstat_seq_open
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
id|nr
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
r_sizeof
(paren
r_int
r_int
)paren
op_star
id|nr
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
r_sizeof
(paren
r_int
r_int
)paren
op_star
id|nr
)paren
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Called from the PROCfs module. This outputs /proc/net/snmp.&n; */
DECL|function|snmp_seq_show
r_static
r_int
id|snmp_seq_show
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
r_int
id|i
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;Ip: Forwarding DefaultTTL InReceives InHdrErrors &quot;
l_string|&quot;InAddrErrors ForwDatagrams InUnknownProtos &quot;
l_string|&quot;InDiscards InDelivers OutRequests OutDiscards &quot;
l_string|&quot;OutNoRoutes ReasmTimeout ReasmReqds ReasmOKs &quot;
l_string|&quot;ReasmFails FragOKs FragFails FragCreates&bslash;nIp: %d %d&quot;
comma
id|ipv4_devconf.forwarding
ques
c_cond
l_int|1
suffix:colon
l_int|2
comma
id|sysctl_ip_default_ttl
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
m_offsetof
(paren
r_struct
id|ip_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|ip_statistics
comma
id|i
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nIcmp: InMsgs InErrors InDestUnreachs InTimeExcds &quot;
l_string|&quot;InParmProbs InSrcQuenchs InRedirects InEchos &quot;
l_string|&quot;InEchoReps InTimestamps InTimestampReps InAddrMasks &quot;
l_string|&quot;InAddrMaskReps OutMsgs OutErrors OutDestUnreachs &quot;
l_string|&quot;OutTimeExcds OutParmProbs OutSrcQuenchs OutRedirects &quot;
l_string|&quot;OutEchos OutEchoReps OutTimestamps OutTimestampReps &quot;
l_string|&quot;OutAddrMasks OutAddrMaskReps&bslash;nIcmp:&quot;
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
m_offsetof
(paren
r_struct
id|icmp_mib
comma
id|dummy
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|icmp_statistics
comma
id|i
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nTcp: RtoAlgorithm RtoMin RtoMax MaxConn ActiveOpens &quot;
l_string|&quot;PassiveOpens AttemptFails EstabResets CurrEstab &quot;
l_string|&quot;InSegs OutSegs RetransSegs InErrs OutRsts&bslash;nTcp:&quot;
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
m_offsetof
(paren
r_struct
id|tcp_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
(paren
m_offsetof
(paren
r_struct
id|tcp_mib
comma
id|TcpMaxConn
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
multiline_comment|/* MaxConn field is negative, RFC 2012 */
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %ld&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|tcp_statistics
comma
id|i
)paren
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|tcp_statistics
comma
id|i
)paren
)paren
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nUdp: InDatagrams NoPorts InErrors OutDatagrams&bslash;n&quot;
l_string|&quot;Udp:&quot;
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
m_offsetof
(paren
r_struct
id|udp_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|udp_statistics
comma
id|i
)paren
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snmp_seq_open
r_static
r_int
id|snmp_seq_open
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
id|snmp_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|snmp_seq_fops
r_static
r_struct
id|file_operations
id|snmp_seq_fops
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
id|snmp_seq_open
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
multiline_comment|/*&n; *&t;Output /proc/net/netstat&n; */
DECL|function|netstat_seq_show
r_static
r_int
id|netstat_seq_show
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
r_int
id|i
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;TcpExt: SyncookiesSent SyncookiesRecv SyncookiesFailed&quot;
l_string|&quot; EmbryonicRsts PruneCalled RcvPruned OfoPruned&quot;
l_string|&quot; OutOfWindowIcmps LockDroppedIcmps ArpFilter&quot;
l_string|&quot; TW TWRecycled TWKilled&quot;
l_string|&quot; PAWSPassive PAWSActive PAWSEstab&quot;
l_string|&quot; DelayedACKs DelayedACKLocked DelayedACKLost&quot;
l_string|&quot; ListenOverflows ListenDrops&quot;
l_string|&quot; TCPPrequeued TCPDirectCopyFromBacklog&quot;
l_string|&quot; TCPDirectCopyFromPrequeue TCPPrequeueDropped&quot;
l_string|&quot; TCPHPHits TCPHPHitsToUser&quot;
l_string|&quot; TCPPureAcks TCPHPAcks&quot;
l_string|&quot; TCPRenoRecovery TCPSackRecovery&quot;
l_string|&quot; TCPSACKReneging&quot;
l_string|&quot; TCPFACKReorder TCPSACKReorder TCPRenoReorder&quot;
l_string|&quot; TCPTSReorder&quot;
l_string|&quot; TCPFullUndo TCPPartialUndo TCPDSACKUndo TCPLossUndo&quot;
l_string|&quot; TCPLoss TCPLostRetransmit&quot;
l_string|&quot; TCPRenoFailures TCPSackFailures TCPLossFailures&quot;
l_string|&quot; TCPFastRetrans TCPForwardRetrans TCPSlowStartRetrans&quot;
l_string|&quot; TCPTimeouts&quot;
l_string|&quot; TCPRenoRecoveryFail TCPSackRecoveryFail&quot;
l_string|&quot; TCPSchedulerFailed TCPRcvCollapsed&quot;
l_string|&quot; TCPDSACKOldSent TCPDSACKOfoSent TCPDSACKRecv&quot;
l_string|&quot; TCPDSACKOfoRecv&quot;
l_string|&quot; TCPAbortOnSyn TCPAbortOnData TCPAbortOnClose&quot;
l_string|&quot; TCPAbortOnMemory TCPAbortOnTimeout TCPAbortOnLinger&quot;
l_string|&quot; TCPAbortFailed TCPMemoryPressures&bslash;n&quot;
l_string|&quot;TcpExt:&quot;
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
m_offsetof
(paren
r_struct
id|linux_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|net_statistics
comma
id|i
)paren
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netstat_seq_open
r_static
r_int
id|netstat_seq_open
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
id|netstat_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|netstat_seq_fops
r_static
r_struct
id|file_operations
id|netstat_seq_fops
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
id|netstat_seq_open
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
DECL|function|ip_misc_proc_init
r_int
id|__init
id|ip_misc_proc_init
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
l_string|&quot;netstat&quot;
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
id|out_netstat
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|netstat_seq_fops
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;snmp&quot;
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
id|out_snmp
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|snmp_seq_fops
suffix:semicolon
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;sockstat&quot;
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
id|out_sockstat
suffix:semicolon
id|p-&gt;proc_fops
op_assign
op_amp
id|sockstat_seq_fops
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_sockstat
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;snmp&quot;
comma
id|proc_net
)paren
suffix:semicolon
id|out_snmp
suffix:colon
id|remove_proc_entry
c_func
(paren
l_string|&quot;netstat&quot;
comma
id|proc_net
)paren
suffix:semicolon
id|out_netstat
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
DECL|function|ip_seq_release
r_int
id|ip_seq_release
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
op_assign
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|kfree
c_func
(paren
id|seq
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
r_return
id|seq_release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
eof
